/*
 * SolveEnergyBalance.cpp
 *
 *  Created on: Nov 20, 2009
 *      Author: marco.maneta
 */

#include"Basin.h"

int Basin::SolveSurfaceFluxes(Atmosphere &atm, Control &ctrl){

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
	REAL8 theta = 0;
	REAL8 theta10cm = 0;
	REAL8 theta2 = 0;//for second and third soil moisture
	REAL8 theta3 = 0;//layers in case Richard's equation is chosen
	REAL8 ponding = 0;
	REAL8 gw = 0; //gravitational water


	//aerodynamic resistance parameters
	REAL8 za; //height of wind speed measurements
	REAL8 z0u; // roughness length for understory
	REAL8 zdu; //zero plane displacement for understory
	REAL8 z0o; // roughness length for overrstory
	REAL8 zdo; //zero plane displacement for overstory

	REAL8 wind; //wind speed
	REAL8 treeheight;

	REAL8 nr, le, sens, grndh, snowh, mltht;

	UINT4 nsp;
	REAL8 p;//fraction of species s


	for (unsigned int j = 0; j < _vSortedGrid.cells.size() ; j++)
	{
					r = _vSortedGrid.cells[j].row;
					c = _vSortedGrid.cells[j].col;


					wind = atm.getWindSpeed()->matrix[r][c];

					theta = _soilmoist->matrix[r][c]; //average soil moisture at time t
					ponding = _ponding->matrix[r][c]; //surface ponding at time t
					gw = _GravityWater->matrix[r][c]; //gravity water at time t

					nr = 0;
					le = 0;
					sens = 0;
					grndh = 0;
					snowh = 0;
					mltht = 0;
					Ts = _Temp_s->matrix[r][c];
					Tsold = 0;
					Tdold = 0;


					if(ctrl.toggle_soil_water_profile == 1){
						Infilt_GreenAmpt(infcap, accinf, theta, ponding, gw, dt, r, c); //updates soil moisture
						CalcSoilMoistureProfile(atm, ctrl, theta, r,c);
						theta10cm = _soilmoist10cm->matrix[r][c];
					}
					if(ctrl.toggle_soil_water_profile == 2){
						theta10cm = _soilmoist10cm->matrix[r][c];
						theta2 = _soilmoist2->matrix[r][c];
						theta3 = _soilmoist3->matrix[r][c];
						Infilt_Richards(infcap, accinf, theta, theta10cm,  theta2, theta3, ponding, gw, dt, r, c); //updates soil moisture
					}
					else{
						Infilt_GreenAmpt(infcap, accinf, theta, ponding, gw, dt, r, c); //updates soil moisture
						_soilmoist10cm->matrix[r][c] = _soilmoist->matrix[r][c];
						theta10cm = _soilmoist10cm->matrix[r][c];
					}


					_ponding->matrix[r][c] = ponding;
					_GravityWater->matrix[r][c] = gw;

/*					//this calculates the soil moisture profile to evaluate soil moisture of the top 10 cms of the soil
					if(ctrl.toggle_soil_water_profile == 1)
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


					ra = CalcAerodynResist(wind, za, z0u, zdu, z0o, zdo, treeheight, LAI, Ts, atm.getTemperature()->matrix[r][c], ctrl.toggle_ra, true);
					rs = CalcSoilResist(theta10cm, r, c, ctrl.toggle_rs);
					//rs =  1/max<double>( 0.0000000000001, ExfiltrationCapacity(theta, dt, r, c) );

					SolveSurfaceEnergyBalance(atm, ctrl, ra, rs, 0.0, BeersK, LAI, emis_can, Temp_can, nr, le, sens, grndh, snowh, mltht, Tsold, evap, ponding, theta, Ts, Tdold, p, r, c);

					_soilmoist->matrix[r][c] = theta; //soil moisture at t=t+1

					_Evaporation->matrix[r][c] += evap; //evaporation at t=t+1




		}

		_Rn->matrix[r][c] = nr;
		_latheat->matrix[r][c] = le;
		_sensheat->matrix[r][c] = sens;
		_grndheat->matrix[r][c] = grndh;
		_snwheat->matrix[r][c] = snowh;
		_Temp_s_old->matrix[r][c] = Tsold;
		_Temp_s->matrix[r][c] = Tsold; //

		_Temp_d->matrix[r][c] = Tdold;

		_ponding->matrix[r][c] += SnowOutput(atm, ctrl, mltht, r, c);

	}

	return EXIT_SUCCESS;
}
