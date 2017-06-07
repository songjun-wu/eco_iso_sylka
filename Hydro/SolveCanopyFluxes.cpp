/*******************************************************************************
 * Ech2o, a spatially-distributed, ecohydrologic simulator
 * Copyright (c) 2016 Marco Maneta <marco.maneta@umontana.edu>
 *
 *     This file is part of ech2o, a hydrologic model developed at the 
 *     University of Montana.
 *
 *     Ech2o is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     Ech2o is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with Ech2o.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contributors:
 *    Marco Maneta, Sylvain Kuppel
 *******************************************************************************/
/*
 * SolveCanopyFluxes.cpp
 *
 *  Created on: Jul 9, 2010
 *      Author: Marco.Maneta
 */

#include"Basin.h"

int Basin::SolveCanopyFluxes(Atmosphere &atm, Control &ctrl, Tracking &trck) {

	UINT4 r, c;
	REAL8 dt = ctrl.dt;

	REAL8 Tp = 0;
	REAL8 maxTp = 0;
	REAL8 minTp = 0;
	REAL8 snow = 0; //amount of snow reaching the ground ms-1
	REAL8 rain = 0;//amount of rain reaching the ground ms-1
	REAL8 sno_rain_thres = 0; //temperature threshold for snow rain transition, degC

	REAL8 ra; //soil aerodynamic resistance


	REAL8 evap = 0; //evaporation for the tree groves
	REAL8 transp = 0; //transpiratin for the tree groves
	REAL8 netR = 0; //net radiation for the tree groves
	REAL8 evap_f = 0; //total evaporation for the entire cell
	REAL8 transp_f = 0; //total transpiration for the entire cell
	//REAL8 ETP;

	//canopy storage parameters
	REAL8 D = 0; //canopy trascolation (amount of water that actually reach the ground)
	REAL8 DelCanStor = 0; //Canopy Storage

	//soil parameters
	REAL8 rootdepth;
	REAL8 thetar;
	REAL8 fc;
	REAL8 poros;
	REAL8 Keff;
	REAL8 psi_ae;
	REAL8 bclambda;

	REAL8 froot1;
	REAL8 froot2;
	REAL8 froot3;
	//soil layer depths
	REAL8 d1;
	REAL8 d2;
	REAL8 d3;

	//aerodynamic resistance parameters
	REAL8 za; //height of wind speed measurements
	REAL8 z0o; // roughness length
	REAL8 zdo; //zero plane displacement
	REAL8 wind; //wind speed
	REAL8 treeheight;

	REAL8 theta = 0;
	REAL8 theta2 = 0;
	REAL8 theta3 = 0;
	REAL8 theta_available=0; //water available to roots

	UINT4 nsp;
	REAL8 p; //fraction of species s

	//unsigned int j;
	UINT4 s;
	int  thre=0;

	// Tracking: contribution of each layer to transpiration
	REAL8 pTrp1, pTrp2, pTrp3;
	REAL8 dDtranspi_f, d18Otranspi_f, Agetranspi_f;
	REAL8 dDevapI_f, d18OevapI_f, AgeevapI_f;
	REAL8 dDnew, d18Onew, Agenew;

	// Initialize to zero
	_Rn_sum->reset();
	if(ctrl.sw_trck){
		//For tracking
		_FluxUptoSnow->reset(); // canopy/sky to snowpack
	}

#pragma omp parallel default(none)\
		private( s, r,c, p,  treeheight, wind, za, z0o, zdo, \
				Tp, maxTp, minTp, snow, rain, sno_rain_thres, evap, \
				transp, netR, evap_f, transp_f, D, DelCanStor, theta, theta2, theta3, theta_available, ra, \
				poros, psi_ae, Keff, bclambda, rootdepth, froot1, froot2, froot3, d1, d2, d3, thetar, fc, \
				pTrp1, pTrp2, pTrp3, dDtranspi_f, d18Otranspi_f, Agetranspi_f,\
				dDevapI_f, d18OevapI_f, AgeevapI_f, dDnew, d18Onew, Agenew) \
		shared(nsp, atm, ctrl, trck, dt, thre)
{
	thre = omp_get_num_threads();
    #pragma omp single
	printf("\nnum threads %d: \n", thre);
    #pragma omp for nowait
	for (unsigned int j = 0; j < _vSortedGrid.cells.size(); j++) {


		r = _vSortedGrid.cells[j].row;
		c = _vSortedGrid.cells[j].col;

		/*--------*/
		nsp = fForest->getNumSpecies();

		treeheight = 0;
		evap_f = 0;
		transp_f = 0;

		thetar = _theta_r->matrix[r][c];
		fc = _fieldcap->matrix[r][c];
		poros = _porosity->matrix[r][c];
		Keff = 2* _Ksat->matrix[r][c]*_KvKs->matrix[r][c] / (1 +_KvKs->matrix[r][c]) ; // harmonic mean of vertical and horizontal ksats
		psi_ae = _psi_ae->matrix[r][c];
		bclambda = _BClambda->matrix[r][c];

		// Tracking: initialize summed values
		dDtranspi_f = 0;
		d18Otranspi_f = 0;
		Agetranspi_f = 0;
		dDevapI_f = 0;
		d18OevapI_f = 0;
		AgeevapI_f = 0;

		d1 = _depth_layer1->matrix[r][c];
		d2 = _depth_layer2->matrix[r][c];
		d3 = _soildepth->matrix[r][c] - d1 - d2;


		for (s = 0; s < nsp; s++) {
			p = fForest->getPropSpecies(s, r, c);
			if (p == 0)
				continue; //if no species j present, continue

			DelCanStor = 0;
			D = 0;
			evap = 0;
			transp = 0;
			netR = 0;

			if (s == nsp - 1) { //if this is bare ground set D to precip and skip the tree stuff

				D = atm.getPrecipitation()->matrix[r][c];
			} else {

				wind = atm.getWindSpeed()->matrix[r][c];

				treeheight = max<REAL8>(0.01, fForest->getTreeHeight(s, r, c));

				/*TODO: Tentative relationship between forest height and wind velocity profile parameters*/
				za = treeheight + 2;
				z0o = powl(treeheight, 1.19) * 0.057544; //powl( 10, -1.24+1.19*log10l(treeheight) );     //treeheight > 1 ? 0.1 : treeheight * 0.1;
				zdo = powl(treeheight, 0.98) * 0.707946; //powl( 10, 0.98*log10l(treeheight)-0.15); //treeheight > 1 ? 0.1 : treeheight * 0.7;

				rootdepth = _soildepth->matrix[r][c];
				theta = _soilmoist1->matrix[r][c]; //soil moisture at time t
				theta2 = _soilmoist2->matrix[r][c];
				theta3 = _soilmoist3->matrix[r][c];
				froot1 = _rootfrac1->matrix[r][c];
				froot2 = _rootfrac2->matrix[r][c];
				froot3 = 1 - froot1 - froot2;
				theta_available = (theta-thetar) * froot1 + (theta2-thetar) * froot2 + (theta3-thetar) * froot3;
				//root depth is the depth of layers that contain 95% of roots
				if (froot1 > 0.95)
					rootdepth = froot1 > d1;
				else if ((froot1 + froot2) > 0.95)
					rootdepth = d1 + d2;



				ra = CalcAerodynResist(wind, za, 0, 0, z0o, zdo, treeheight,
						fForest->getLAISpecies(s, r, c),
						getCanopyTemp(s)->matrix[r][c],
						atm.getTemperature()->matrix[r][c], ctrl.toggle_ra,
						false);

				fForest->CanopyInterception(atm, ctrl, DelCanStor, D, s, r, c); //calculates canopy interception and trascolation

				fForest->SolveCanopyEnergyBalance(*this, atm, ctrl, theta_available+thetar,
						thetar, poros, rootdepth, Keff, psi_ae, bclambda, ra, DelCanStor, evap, transp, netR,
						s, r, c);

				_CanopyStorage->matrix[r][c] += DelCanStor * p;

				_Rn_sum->matrix[r][c] += netR * p ;

				if (_CanopyStorage->matrix[r][c] < RNDOFFERR)
					_CanopyStorage->matrix[r][c] = 0.0;

				transp_f += transp * p;
				evap_f += evap * p; //evaporation at t=t+1
					
				pTrp1 = ((theta-thetar)*froot1) / theta_available;
				pTrp2 = ((theta2-thetar)*froot2) / theta_available;
				pTrp3 = ((theta3-thetar)*froot3) / theta_available;

				theta  -= transp * p * dt * pTrp1 /d1; //soil moisture at t=t+1
				theta2 -= transp * p * dt * pTrp2 /d2; //soil moisture at t=t+1
				theta3 -= transp * p * dt * pTrp3 /d3; //soil moisture at t=t+1

				// Transpiration tracking: assumes total mixing of the water pulled from each soil layer
				if(ctrl.sw_trck){

					if(ctrl.sw_dD){
						fForest->setdDtranspi(s, r, c,
							pTrp1*trck.getdDsoil1()->matrix[r][c]+
							pTrp2*trck.getdDsoil2()->matrix[r][c]+
							pTrp3*trck.getdDsoil3()->matrix[r][c]);
						dDtranspi_f += fForest->getdDtranspi(s)->matrix[r][c] * p ;
					}
					if(ctrl.sw_d18O){
						fForest->setd18Otranspi(s, r, c,
							pTrp1*trck.getd18Osoil1()->matrix[r][c]+
							pTrp2*trck.getd18Osoil2()->matrix[r][c]+
							pTrp3*trck.getd18Osoil3()->matrix[r][c]);
						d18Otranspi_f += fForest->getd18Otranspi(s)->matrix[r][c] * p ;
					}
					if(ctrl.sw_Age){
						fForest->setAgetranspi(s, r, c,
							pTrp1*trck.getAgesoil1()->matrix[r][c]+
							pTrp2*trck.getAgesoil2()->matrix[r][c]+
							pTrp3*trck.getAgesoil3()->matrix[r][c]);
						Agetranspi_f += fForest->getAgetranspi(s)->matrix[r][c] * p ;
					}
				}

				// Update soil moisture objects after tracking
				_soilmoist1->matrix[r][c] = theta;
				_soilmoist2->matrix[r][c] = theta2;
				_soilmoist3->matrix[r][c] = theta3;


			}


			Tp = atm.getTemperature()->matrix[r][c];
			maxTp = atm.getMaxTemperature()->matrix[r][c];
			minTp = atm.getMinTemperature()->matrix[r][c];
			sno_rain_thres = atm.getRainSnowTempThreshold();

			if(maxTp <= sno_rain_thres){
				snow = D;
				rain = 0;
			}
			else if(minTp > sno_rain_thres){
				rain = D;
				snow = 0;
			}
			else{
				snow = D * max<REAL8>(0.0, (sno_rain_thres - minTp) /(maxTp - minTp));
				rain = D - snow;
			}

			// Water tracking
			if(ctrl.sw_trck){

				// Used later in SolveSurfaceFluxes
				_FluxUptoSnow->matrix[r][c] += snow * p * dt;

				// Mix in surface pool from rain throughfall
				if(ctrl.sw_dD)
					trck.setdDsurface(r, c,
						trck.InputMix(_ponding->matrix[r][c],
							trck.getdDsurface()->matrix[r][c],
							rain*p*dt,atm.getdDprecip()->matrix[r][c]));
				if(ctrl.sw_d18O)
					trck.setd18Osurface(r, c,
						trck.InputMix(_ponding->matrix[r][c],
							trck.getd18Osurface()->matrix[r][c],
							rain*p*dt,atm.getd18Oprecip()->matrix[r][c]));
				
				// This assumes that throughfall has age 0, i.e., there is no spill-over 
				// from previously stored intercepted water
				if(ctrl.sw_Age)
					trck.setAgesurface(r, c,
						trck.InputMix(_ponding->matrix[r][c],
							trck.getAgesurface()->matrix[r][c],
							rain*p*dt,0.0));
			}

			_snow->matrix[r][c] +=  snow * dt * p;
			_ponding->matrix[r][c] += rain * dt * p;

		} //end for

		_Evaporation->matrix[r][c] = evap_f + transp_f; //total evaporation for the entire cell
		// Vegetation-summed values
		_Transpiration_all->matrix[r][c]  = transp_f ;
		_EvaporationI_all->matrix[r][c] = evap_f ;
		// applies for tracking as well
		if(ctrl.sw_trck && ctrl.sw_dD)
			trck.setdDtranspi_sum(r ,c, dDtranspi_f);
		if(ctrl.sw_trck && ctrl.sw_d18O)
			trck.setd18Otranspi_sum(r ,c, d18Otranspi_f);
		if(ctrl.sw_trck && ctrl.sw_Age)
			trck.setAgetranspi_sum(r ,c, Agetranspi_f);

	}//end for
}//end omp parallel


return EXIT_SUCCESS;
}
