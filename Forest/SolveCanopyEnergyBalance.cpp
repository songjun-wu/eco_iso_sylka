/*
 * SolveEnergyBalance.cpp
 *
 *  Created on: Jul 9, 2010
 *      Author: Marco.Maneta
 */

#include "Forest.h"

UINT4 Forest::SolveCanopyEnergyBalance(Basin &bas, Atmosphere &atm, Control &ctrl, REAL8 theta, REAL8 thetar, REAL8 fc, REAL8 rootdepth, REAL8 ra, REAL8 gc, REAL8 &DelCanStor, REAL8 &evap_a, REAL8 &transp_a, UINT4 s, UINT4 r, UINT4 c){

	//energy balance parameters
	REAL8 fA, fB, fC, fD; //pooling factors
	REAL8 ea; //emissivity of air
	REAL8 rho_a; //density of air
	REAL8 airRH; //air humidity
	REAL8 desdTs; // derivative of saturation vapor pressure function with respect to Ts
	REAL8 emissivity; //canopy emissivity
	REAL8 albedo; //canopy albedo
	REAL8 LAI;
	REAL8 BeerK; //Beers-Lambert coefficient
	REAL8 fTs;
	REAL8 dfTs;
	REAL8 LE, H;
	REAL8 z; //terrain height
	REAL8 gamma; //psychrometric constant
	REAL8 Ts = 0;
	REAL8 Ts1 = 0; //Canopy temperature at NR iteration +1

	REAL8 lambda = lat_heat_vap;
	REAL8 ra_t; //resistance to transpiration ra_t = ra + 1/gc
	REAL8 LET; //latent heat of transpiration
	REAL8 CanStor = 0;
	REAL8 MaxCanStor = 0;

	REAL8 soilRH; //soil relative humidty use in teh calculation of soil vapor pressure for latent heat exchanges
	REAL8 leavesurfRH; //relative humidity of the leave surface. 1 when leave is saturated with intercepted water, airRH when no water


		UINT4 nsp = getNumSpecies();

		  if(s == nsp -1) //for bare soil, water reaching the ground is pp times its proportion of the cell
			  evap_a = transp_a = 0;
		  else{


						ea = AirEmissivity(atm.getTemperature()->matrix[r][c]);
						rho_a = AirDensity(atm.getTemperature()->matrix[r][c]); //kgm-3
						z = bas.getDEM()->matrix[r][c];
						gamma =PsychrometricConst(101325, z);
						airRH = atm.getRelativeHumidty()->matrix[r][c];

						albedo = _species[s].albedo;
						emissivity = _species[s].emissivity;
						BeerK = _species[s].KBeers;
						LAI = _species[s]._LAI->matrix[r][c];

						CanStor = getIntercWater(s, r, c);
						MaxCanStor = getMaxCanopyStorage(s, r, c);

						soilRH = 1; //min<REAL8>(1.0,Calculate_gs_theta(theta, fc, _species[s].WiltingPoint, 2.0)); //calculates soil pore relative humidity
						leavesurfRH = airRH + ( (1 - airRH) / MaxCanStor ) * CanStor;

						ra_t = ra + (1/gc);


						fA = -4 * emissivity * stefboltz;	//pools together net radiation factors
						fB = (-1/ (ra * gamma)) * rho_a * spec_heat_air; // pools together the latent heat factors
						fC = (-1/(ra)) * rho_a * spec_heat_air; // pools together the sensible heat factors
						fD = (-1/ (ra_t * gamma)) * rho_a * spec_heat_air; // pools together the latent heat factors


						evap_a = CanStor < MaxCanStor ? -CanStor/ctrl.dt * powl( (CanStor/MaxCanStor), 0.6 ) : -CanStor/ctrl.dt;

						int k = 0;

						do{

							lambda = Ts1 < 0 ?  lat_heat_vap + lat_heat_fus : lat_heat_vap;

							Ts = _species[s]._Temp_c->matrix[r][c];

							desdTs = 611 * ( (17.3/( Ts + 237.7)) - ((17.3 * Ts)/(powl(Ts + 237.2 , 2))) )
														* expl(17.3 * Ts /( Ts + 237.7));
							//LE_lim = evap_a * rho_w * lambda;
							//LE_unlim = LatHeatCanopy(atm, leavesurfRH, ra, Ts, r, c);

							LE = LatHeatCanopy(bas, atm, leavesurfRH, ra, Ts, r, c); /*LE = LE_unlim;   max<REAL8>(LE_lim, LE_unlim);
								if(LE == LE_lim)
									fB = 0;*/
							LET = LatHeatCanopy(bas, atm, soilRH, ra_t, Ts, r, c);
							H = SensHeatCanopy(atm, ra, Ts, r, c);

							fTs = NetRadCanopy(atm, Ts, emissivity, albedo, BeerK, LAI, r, c) + LE + H + LET;
							dfTs = fA*powl(Ts + 273.2, 3) + fB * desdTs * leavesurfRH + fC + fD * desdTs * soilRH;

							Ts1 = Ts - (fTs/dfTs);
							_species[s]._Temp_c->matrix[r][c] = Ts1;



							k++;
						}while(fabs(Ts1 - Ts) > 0.0001 && k < MAX_ITER);


						if (k>=MAX_ITER)
							std::cout << "WARNING: non-convergence in canopy energy balance at cell row: " << r << " col: " << c << " closure err: " << (Ts1 - Ts) << endl;


						if(Ts1 < atm.getTemperature()->matrix[r][c]){ //if teh calcualted canopy temperature is lower than air temperature make it air temperature
							Ts1 = atm.getTemperature()->matrix[r][c];
							LET = LatHeatCanopy(bas, atm, soilRH, ra_t, Ts, r, c);
							LE = LatHeatCanopy(bas, atm, leavesurfRH, ra, Ts, r, c);
							_species[s]._Temp_c->matrix[r][c] = Ts1;
						}


						evap_a = min<REAL8>(-evap_a,fabs(-LE/(rho_w*lambda))); //swap sign since outgoing evaporation is negative and we accumulate it as positive. Also checks for negative evap
						transp_a = max<REAL8>(0.0,-LET/(rho_w*lambda)); //swap sign since outgoing evaporation is negative and we accumulate it as positive. Also checks for negative evap

						DelCanStor -= evap_a * ctrl.dt;


						_species[s]._NetR_Can->matrix[r][c] = NetRadCanopy(atm, Ts1, emissivity, albedo, BeerK, LAI, r, c);
						_species[s]._LatHeat_Can->matrix[r][c] = LE+LET;//LatHeatCanopy(atm, ra, Ts1, r, c);
						_species[s]._SensHeat_Can->matrix[r][c] = SensHeatCanopy(atm, ra, Ts1, r, c);


						///////////this chunk of code is to make sure we are not transpiring below residual moisture content

						REAL8 Tp;
						Tp = transp_a * ctrl.dt;

						if ((theta - thetar) * rootdepth < Tp) { ///TODO: change to wilting point (not residual water content)
							Tp = (theta - thetar) * rootdepth;
							transp_a = Tp / ctrl.dt;
						}


						//////////////////////////////////////////


						_species[s]._ET->matrix[r][c] = evap_a + transp_a;
						_species[s]._Transpiration->matrix[r][c] = transp_a;

						_species[s]._WaterStorage->matrix[r][c] -= evap_a * ctrl.dt;


		  }

						return EXIT_SUCCESS;
}
