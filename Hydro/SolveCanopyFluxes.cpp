/*
 * SolveCanopyFluxes.cpp
 *
 *  Created on: Jul 9, 2010
 *      Author: Marco.Maneta
 */

#include"Basin.h"

int Basin::SolveCanopyFluxes(Atmosphere &atm, Control &ctrl) {

	UINT4 r, c;
	REAL8 dt = ctrl.dt;

	REAL8 Tp = 0;
	REAL8 maxTp = 0;
	REAL8 minTp = 0;
	REAL8 snow = 0; //amount of snow reaching the ground ms-1
	REAL8 rain = 0;//amount of rain reaching the ground ms-1
	REAL8 sno_rain_thres = 0; //temperature threshold for snow rain transition, degC

	REAL8 ra; //soil aerodynamic resistance
	REAL8 gc; //canopy resistance

	REAL8 evap = 0; //evaporation for the tree groves
	REAL8 transp = 0; //transpiratin for the tree groves
	REAL8 evap_f = 0; //total evaporation for the entire cell
	REAL8 transp_f = 0; //total transpiration for the entire cell
	//REAL8 ETP;

	//canopy storage parameters
	REAL8 D = 0; //canopy trascolation
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
#pragma omp parallel default(none)\
		private( s, r,c, p, gc, treeheight, wind, za, z0o, zdo, \
							Tp, maxTp, minTp, snow, rain, sno_rain_thres, evap, \
							transp, evap_f, transp_f, D, DelCanStor, theta, theta2, theta3, theta_available, ra, \
							rootdepth, froot1, froot2, froot3, d1, d2, d3, thetar, fc) \
					shared(nsp, atm, ctrl, dt, thre)
{
	thre = omp_get_num_threads();
    #pragma omp single
	printf("\nnum threads %d: ", thre);
    #pragma omp for nowait
	for (unsigned int j = 0; j < _vSortedGrid.cells.size(); j++) {


		r = _vSortedGrid.cells[j].row;
		c = _vSortedGrid.cells[j].col;

		/*--------*/
		nsp = fForest->getNumSpecies();
		gc = 0;
		treeheight = 0;
		evap_f = 0;
		transp_f = 0;

		thetar = _theta_r->matrix[r][c];
		fc = _fieldcap->matrix[r][c];
		poros = _porosity->matrix[r][c];
		Keff = _Ksat->matrix[r][c];
		psi_ae = _psi_ae->matrix[r][c];
		bclambda = _BClambda->matrix[r][c];


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

				fForest->CalculateCanopyConduct(*this, atm, ctrl, theta_available, fc, s,
										r, c);

				ra = CalcAerodynResist(wind, za, 0, 0, z0o, zdo, treeheight,
						fForest->getLAISpecies(s, r, c),
						getCanopyTemp(s)->matrix[r][c],
						atm.getTemperature()->matrix[r][c], ctrl.toggle_ra,
						false);
				gc = fForest->getCanopyConductance(s, r, c);

				fForest->CanopyInterception(atm, ctrl, DelCanStor, D, s, r, c); //calculates canopy interception and trascolation

				fForest->SolveCanopyEnergyBalance(*this, atm, ctrl, theta_available,
						thetar, poros, rootdepth, Keff, psi_ae, bclambda, ra, gc, DelCanStor, evap, transp,
						s, r, c);

				_CanopyStorage->matrix[r][c] += DelCanStor * p;

				if (_CanopyStorage->matrix[r][c] < RNDOFFERR)
					_CanopyStorage->matrix[r][c] = 0.0;

				transp_f += transp * p;
				evap_f += evap * p; //evaporation at t=t+1

				theta  -= transp * p * dt * ((theta-thetar)*froot1) / (d1*theta_available); //soil moisture at t=t+1
				theta2 -= transp * p * dt * ((theta2-thetar)*froot2) / (d2*theta_available); //soil moisture at t=t+1
				theta3 -= transp * p * dt * ((theta3-thetar)*froot3) / (d3*theta_available); //soil moisture at t=t+1

				_soilmoist1->matrix[r][c] = theta;
				_soilmoist2->matrix[r][c] = theta2;
				_soilmoist3->matrix[r][c] = theta3;


			}


					Tp = atm.getTemperature()->matrix[r][c];
					maxTp = atm.getMaxTemperature()->matrix[r][c];
					minTp = atm.getMinTemperature()->matrix[r][c];
					sno_rain_thres = atm.getRainSnowTempThreshold()->matrix[r][c];

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


			_snow->matrix[r][c] +=  snow * dt * p;
			_ponding->matrix[r][c] += rain * dt * p;

		} //end for

		_Evaporation->matrix[r][c] = evap_f + transp_f; //total evaporation for the entire cell

	}//end for
}//end omp parallel


	return EXIT_SUCCESS;
}
