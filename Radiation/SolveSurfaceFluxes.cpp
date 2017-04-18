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
 *    Marco Maneta, Sylain Kuppel
 *******************************************************************************/
/*
 * SolveEnergyBalance.cpp
 *
 *  Created on: Nov 20, 2009
 *      Author: marco.maneta
 */

#include"Basin.h"

int Basin::SolveSurfaceFluxes(Atmosphere &atm, Control &ctrl, Tracking &trck) {

	int r, c;
	float dt = ctrl.dt; //time step


	//energy balance parameters

	REAL8 ra; //soil aerodynamic resistance
	REAL8 rs; //bare soil resistance (a function of soil moisture)
	REAL8 Ts = 0; //
	REAL8 Tsold = 0; //old surface temperature
	REAL8 Tdold = 0; //temperature of lower soil thermal layer

	REAL8 LAI = 0;
	REAL8 BeersK = 0;
	REAL8 Temp_can = 0; //temperature of the canopy
	REAL8 emis_can = 0; //emissivity of the canopy

	REAL8 evap = 0; //evaporation

	//infiltration parameters
	REAL8 infcap = 0;
	REAL8 accinf = 0;
	REAL8 theta = 0; //soil moisture for entire soil profile or for first soil layer
	REAL8 theta2 = 0; //for second and third soil moisture
	REAL8 theta3 = 0; //layers in case Richard's equation is chosen
	REAL8 ponding = 0;
	REAL8 gw = 0; //gravitational water
	REAL8 leak = 0; //bedrock leakage flux;

	//aerodynamic resistance parameters
	REAL8 za; //height of wind speed measurements
	REAL8 z0u; // roughness length for understory
	REAL8 zdu; //zero plane displacement for understory
	REAL8 z0o; // roughness length for overrstory
	REAL8 zdo; //zero plane displacement for overstory

	REAL8 wind; //wind speed
	REAL8 treeheight;

	REAL8 nr, le, sens, grndh, snowh, mltht, dh_snow;

	UINT4 nsp;
	REAL8 p;//fraction of species s

	//needed in the water routing routines
	_dailyOvlndOutput.cells.clear();
	_dailyGwtrOutput.cells.clear();
	_GWupstreamBC->reset();
	_Disch_upstreamBC->reset();
	// Set EvapS to zero before looping over baresoil/understory
	_EvaporationS->reset();

#pragma omp parallel default(shared) private(r, c, ra, rs, Ts, Tsold, Tdold, LAI, BeersK, Temp_can, emis_can,\
		evap, infcap, accinf, theta, theta2, theta3, ponding,leak,  gw, za, z0u, zdu, z0o, zdo, wind, treeheight,\
		nr, le, sens, grndh, snowh, mltht, dh_snow, p) //shared(ctrl, atm, nsp, dt)
{
//thre = omp_get_num_threads();
//#pragma omp single
//printf("\nnum threads %d: ", thre);
#pragma omp for nowait
	for (unsigned int j = 0; j < _vSortedGrid.cells.size() ; j++)
	{
					r = _vSortedGrid.cells[j].row;
					c = _vSortedGrid.cells[j].col;


					wind = atm.getWindSpeed()->matrix[r][c];

					theta = _soilmoist1->matrix[r][c]; //soil moisture at time t
					theta2 = _soilmoist2->matrix[r][c];
					theta3 = _soilmoist3->matrix[r][c];
					ponding = _ponding->matrix[r][c]; //surface ponding at time t
					gw = _GravityWater->matrix[r][c]; //gravity water at time t
					leak = 0;

					nr = 0;
					le = 0;
					sens = 0;
					grndh = 0;
					snowh = 0;
					mltht = 0;
					Ts = _Temp_s->matrix[r][c];
					Tsold = 0;
					Tdold = 0;
					dh_snow = 0;

					Infilt_GreenAmpt(ctrl, trck, infcap, accinf, theta, theta2, theta3, ponding, gw, dt, r, c); //updates soil moisture

					// Flux tracking: back up new pool water content for use together with temporary variables in SoilWaterRedistribution
					if(ctrl.sw_trck){
						_soilmoist1->matrix[r][c] = theta;
						_soilmoist2->matrix[r][c] = theta2;
						_soilmoist3->matrix[r][c] = theta3;
						_ponding->matrix[r][c] = ponding;
						_GrndWater->matrix[r][c] = gw;
					}

			        SoilWaterRedistribution(ctrl, trck, accinf, theta, theta2, theta3, ponding, gw, leak, dt, r, c);

					_ponding->matrix[r][c] = ponding;
					_GravityWater->matrix[r][c] = gw;
					_GrndWater->matrix[r][c] = gw;
					_BedrockLeakageFlux->matrix[r][c] = leak;


					/*//this calculates the soil moisture profile to evaluate soil moisture of the top 10 cms of the soil
					if(ctrl.sw_soil_water_profile == 1)
						CalcSoilMoistureProfile(atm, ctrl, theta, r,c);
					else
						_soilmoist10cm->matrix[r][c] = _soilmoist->matrix[r][c]; //if no calculation of the soil moisture profile, soil moist at 10 equals average soil moisture

					theta10cm = _soilmoist10cm->matrix[r][c];*/


					nsp = fForest->getNumSpecies();
					treeheight = 0;

		for(UINT4 s = 0; s < nsp ; s++)
		{
				p = fForest->getPropSpecies(s, r, c);
				if(p == 0)
					continue;//if no species j present, continue

				if(s == nsp -1){ //for bare soil, water reaching the ground is pp times its proportion of the cell
					LAI = 0;
					emis_can = 0;
					Temp_can = 0;
					za = _random_roughness->matrix[r][c] + 2;
					z0u = max<REAL8>(0.000005,_random_roughness->matrix[r][c] * 0.1);
					zdu = _random_roughness->matrix[r][c] * 0.7;
					z0o = 0; //no overstory
					zdo = 0;
				}
				else
				{
					treeheight = max<REAL8>(0.01,fForest->getTreeHeight(s, r, c)); //equations only apply to 40% of the tree as per Campbell and Norman 1998
					LAI = fForest->getLAISpecies(s, r, c);
					BeersK = fForest->getBeersCoeff(s, r, c);
					Temp_can = fForest->getCanopyTemp(s, r, c);
					emis_can = fForest->getCanopyEmissivity(s, r, c);
					za = treeheight + 2;
					z0o = powl(treeheight,1.19)*0.057544;     //treeheight > 1 ? 0.1 : treeheight * 0.1;
					zdo = powl(treeheight,0.98)*0.707946; //treeheight > 1 ? 0.1 : treeheight * 0.7;
					zdu = min<double>(_random_roughness->matrix[r][c], zdo * 0.1);//min<double>(treeheight * 0.1, zdo * 0.1);
					z0u = 0.1*zdu/0.7;

				}


				ra = CalcAerodynResist(wind, za, z0u, zdu, z0o, zdo, treeheight,
									LAI, Ts, atm.getTemperature()->matrix[r][c], ctrl.toggle_ra,
									true);
				rs = CalcSoilResist(theta, r, c, ctrl.toggle_rs);
				//rs =  1/max<double>( 0.0000000000001, ExfiltrationCapacity(theta, dt, r, c) );

				SolveSurfaceEnergyBalance(atm, ctrl, ra, rs, 0.0, BeersK, LAI,
						emis_can, Temp_can, nr, le, sens, grndh, snowh, mltht,
						Tsold, evap, ponding, theta, Ts, Tdold, p, r, c, s);

				//For soil hydrology option 0 theta1 is the total soil layer
				_soilmoist1->matrix[r][c] = theta; //soil moisture at t=t+1
				_soilmoist2->matrix[r][c] = theta2;
				_soilmoist3->matrix[r][c] = theta3;


				_Evaporation->matrix[r][c] += evap; //evaporation at t=t+1
				_EvaporationS->matrix[r][c] += evap; //soil evaporation at t=t+1

				// Soil evaporation tracking
				if(ctrl.sw_trck){					
					// Isotopes: for now no fractionation taken into account -> signature of first layer
					if(ctrl.sw_dD)
						trck.setdDevapS(r, c, trck.getdDsoil1()->matrix[r][c]);
					if(ctrl.sw_d18O)
						trck.setd18OevapS(r, c, trck.getd18Osoil1()->matrix[r][c]);
					// Water age: as if uniformly evaporated from first layer
					// TODO: recent (rain) water evaporated first?
					if(ctrl.sw_Age)
						trck.setAgeevapS(r, c, trck.getAgesoil1()->matrix[r][c]);
				}

		}//for


		_Rn->matrix[r][c] = nr;
		_latheat->matrix[r][c] = le;
		_sensheat->matrix[r][c] = sens;
		_grndheat->matrix[r][c] = grndh;
		_snwheat->matrix[r][c] = snowh;
		_Temp_s_old->matrix[r][c] = Tsold;
		_Temp_s->matrix[r][c] = Tsold; //

		_Temp_d->matrix[r][c] = Tdold;

		dh_snow = SnowOutput(atm, ctrl, mltht, r, c);

		// Flux tracking: 
		// - in snowpack (snowfall in + snowmelt out), considering that snowmelt "flushes" the most recent snowfall first, without mixing
		// - in the surface pool, mixing of snowmelt
		if(ctrl.sw_trck){
			// Case where there is more snowfall than snowmelt: snowpack mixed, snowmelt has snowfall signature
			if(_FluxUptoSnow->matrix[r][c] > dh_snow){
				if(ctrl.sw_dD){
					// Snowpack: last (same timestep) in, first melt
					trck.setdDsnowpack(r, c,
						trck.InputMix(_snow->matrix[r][c], trck.getdDsnowpack()->matrix[r][c],
							_FluxUptoSnow->matrix[r][c] - dh_snow, atm.getdDprecip()->matrix[r][c]));
					// Surface: snowfall (=rain) signature
					trck.setdDsurface(r, c,
						trck.InputMix(_ponding->matrix[r][c], trck.getdDsurface()->matrix[r][c],
							dh_snow, atm.getdDprecip()->matrix[r][c]));
				}
				if(ctrl.sw_d18O){
					// Snowpack: last (same timestep) in, first melt
					trck.setd18Osnowpack(r, c,
						trck.InputMix(_snow->matrix[r][c], trck.getd18Osnowpack()->matrix[r][c],
							_FluxUptoSnow->matrix[r][c] - dh_snow, atm.getd18Oprecip()->matrix[r][c]));
					// Surface: snowfall (=rain) signature
					trck.setd18Osurface(r, c,
						trck.InputMix(_ponding->matrix[r][c], trck.getd18Osurface()->matrix[r][c],
							dh_snow, atm.getd18Oprecip()->matrix[r][c]));
				}
				if(ctrl.sw_Age){
					// Snowpack: last (same timestep) in, first melt
					trck.setAgesnowpack(r, c,
						trck.InputMix(_snow->matrix[r][c], trck.getAgesnowpack()->matrix[r][c],
							_FluxUptoSnow->matrix[r][c] - dh_snow,	0.0));
					// Surface: snowfall (=rain) signature
					trck.setAgesurface(r, c,
						trck.InputMix(_ponding->matrix[r][c], trck.getAgesurface()->matrix[r][c],
							dh_snow, 0.0));
				}
			} else {
			// Case where there is more snowmelt than snowfall: no mixing in snowpack, snowmelt has mixed signature
				if(ctrl.sw_dD){
					// Snowpack: no change (all recent snow has melted)
					// Surface: weighted snowfall (=rain) signature and previous snowpack
					trck.setdDsurface(r, c,
						trck.InputMix(_ponding->matrix[r][c], trck.getdDsurface()->matrix[r][c],
							dh_snow,
							// Ugly and "convoluted", but no waste of temp variables
							trck.InputMix(dh_snow - _FluxUptoSnow->matrix[r][c], trck.getdDsnowpack()->matrix[r][c],
								_FluxUptoSnow->matrix[r][c], atm.getdDprecip()->matrix[r][c])));
				}
				if(ctrl.sw_d18O){
					// Snowpack: no change (all recent snow has melted)
					// Surface: weighted snowfall (=rain) signature and previous snowpack
					trck.setd18Osurface(r, c,
						trck.InputMix(_ponding->matrix[r][c], trck.getd18Osurface()->matrix[r][c],
							dh_snow,
							// Ugly and "convoluted", but no waste of temp variables
							trck.InputMix(dh_snow - _FluxUptoSnow->matrix[r][c], trck.getd18Osnowpack()->matrix[r][c],
								_FluxUptoSnow->matrix[r][c], atm.getd18Oprecip()->matrix[r][c])));
				}
				if(ctrl.sw_Age){
					// Snowpack: no change (all snow in melted)
					// Surface: weighted snowfall (=rain) signature and previous snowpack
					trck.setAgesurface(r, c,
						trck.InputMix(_ponding->matrix[r][c], trck.getAgesurface()->matrix[r][c],
							dh_snow,
							// Ugly and "convoluted", but no waste of temp variables
							trck.InputMix(dh_snow - _FluxUptoSnow->matrix[r][c], trck.getAgesnowpack()->matrix[r][c],
								_FluxUptoSnow->matrix[r][c], 0.0)));
				}
			}

		}
		// Update surface pool
		_ponding->matrix[r][c] += dh_snow;
		// Back up before routing
		_GrndWaterOld->matrix[r][c] = _GrndWater->matrix[r][c];

	}//for
}//end omp parallel block

	return EXIT_SUCCESS;
}
