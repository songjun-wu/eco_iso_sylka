/*
 * SolveCanopyFluxes.cpp
 *
 *  Created on: Jul 9, 2010
 *      Author: Marco.Maneta
 */

#include"Basin.h"

int Basin::SolveCanopyFluxes(Atmosphere &atm, Control &ctrl){

	UINT4 r, c;
	REAL8 dt = ctrl.dt;

	REAL8 Tp = 0;
	REAL8 maxTp = 0;
	REAL8 minTp = 0;
	REAL8 snow = 0; //amount of snow reaching the ground ms-1
	REAL8 rain = 0;//amount of rain reaching the ground ms-1

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
	REAL8 soildepth;
	REAL8 thetar;
	REAL8 fc;

	//aerodynamic resistance parameters
	REAL8 za; //height of wind speed measurements
	REAL8 z0o; // roughness length
	REAL8 zdo; //zero plane displacement
	REAL8 wind; //wind speed
	REAL8 treeheight;

	REAL8 theta;

	UINT4 nsp;
	REAL8 p;//fraction of species s

	unsigned int j;
	UINT4 s;
	int  thre;
//double init = omp_get_wtime();

#pragma omp parallel for default(none) \
			private(j, s, r,c, p, gc, treeheight, wind, za, z0o, zdo, \
					Tp, maxTp, minTp, snow, rain, evap, \
					transp, evap_f, transp_f, D, DelCanStor, theta, ra, \
					soildepth, thetar, fc) \
			shared(nsp, atm, ctrl, dt, thre)

	for (j = 0; j < _vSortedGrid.cells.size() ; j++)
	{
//		 thre = omp_get_num_threads();


					r = _vSortedGrid.cells[j].row;
					c = _vSortedGrid.cells[j].col;


					/*--------*/
					nsp = fForest->getNumSpecies();
					gc = 0;
					treeheight = 0;
					evap_f = 0;
					transp_f = 0;


		for(s = 0; s < nsp ; s++)
		{
				p = fForest->getPropSpecies(s, r, c);
					if(p == 0) continue;//if no species j present, continue

					DelCanStor = 0;
					D = 0;
					evap = 0;
					transp = 0;


				if(s == nsp-1){ //if this is bare ground set D to precip and skip the tree stuff

					D = atm.getPrecipitation()->matrix[r][c];
				}
				else{

					wind = atm.getWindSpeed()->matrix[r][c];

					treeheight = max<REAL8>(0.01,fForest->getTreeHeight(s, r, c));

					fForest->CalculateCanopyConduct(*this, atm, ctrl, s, r, c);


					/*TODO: Tentative relationship between forest height and wind velocity profile parameters*/
					za = treeheight + 2;
					z0o = powl(treeheight,1.19)*0.057544;//powl( 10, -1.24+1.19*log10l(treeheight) );     //treeheight > 1 ? 0.1 : treeheight * 0.1;
					zdo = powl(treeheight,0.98)*0.707946;//powl( 10, 0.98*log10l(treeheight)-0.15); //treeheight > 1 ? 0.1 : treeheight * 0.7;

					theta = _soilmoist1->matrix[r][c]; //soil moisture at time t

					ra = CalcAerodynResist(wind, za, 0, 0, z0o, zdo, treeheight, fForest->getLAISpecies(s, r, c), getCanopyTemp(s)->matrix[r][c], atm.getTemperature()->matrix[r][c], ctrl.toggle_ra, false);
					gc = fForest->getCanopyConductance(s, r, c);
					soildepth = _soildepth->matrix[r][c];
					thetar = _theta_r->matrix[r][c];
					fc = _fieldcap->matrix[r][c];

					fForest->CanopyInterception(atm, ctrl, DelCanStor, D, s, r, c); //calculates canopy interception and trascolation

					fForest->SolveCanopyEnergyBalance(*this, atm, ctrl, theta, thetar, fc, soildepth, ra, gc, DelCanStor, evap, transp, s, r, c);

					_CanopyStorage->matrix[r][c] += DelCanStor * p;

					if (_CanopyStorage->matrix[r][c] < RNDOFFERR)
						_CanopyStorage->matrix[r][c] = 0.0;



/*
					///////////this chunk of code is to make sure we are not transpiring below residual moisture content

					ETP = transp * dt * p;

					if ((theta - thetar) * soildepth < ETP) { ///TODO: change to wilting point (not residual water content)
						ETP = (theta - thetar) * soildepth * p;
						transp = ETP / dt;
						theta -= ETP / soildepth;
						transp_f += transp;
					}
					else{
						theta -= ETP / soildepth;
						transp_f += transp * p;
						_soilmoist->matrix[r][c] = theta; //soil moisture at t=t+1
					}

					evap_f += evap * p; //evaporation at t=t+1

					//////////////////////////////////////////
*/
					transp_f += transp * p;
					theta -= transp * p * dt / soildepth;
					evap_f += evap * p; //evaporation at t=t+1

					_soilmoist1->matrix[r][c] = theta; //soil moisture at t=t+1

				}


					Tp = atm.getTemperature()->matrix[r][c];
					maxTp = atm.getMaxTemperature()->matrix[r][c];
					minTp = atm.getMinTemperature()->matrix[r][c];

					if(maxTp <= 1){
						snow = D;
						rain = 0;
					}
					else if(minTp > 1){
						rain = D;
						snow = 0;
					}
					else{
					snow = D * max<REAL8>(0.0, (1 - minTp) /(maxTp - minTp));
					rain = D - snow;
					}


						_snow->matrix[r][c] +=  snow * dt * p;

						_ponding->matrix[r][c] += rain * dt * p;



		}//end for

		_Evaporation->matrix[r][c] = evap_f + transp_f; //total evaporation for the entire cell
	}//end for

	return EXIT_SUCCESS;
}
