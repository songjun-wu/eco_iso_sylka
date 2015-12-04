/*
 * SolveEnergyBalance.cpp
 *
 *  Created on: Jul 9, 2010
 *      Author: Marco.Maneta
 */
#define ARMA_NO_DEBUG //disables armadillo bound checks for speed optimization
#include <armadillo>
#include "Forest.h"

using namespace arma;

UINT4 Forest::SolveCanopyEnergyBalance(Basin &bas, Atmosphere &atm,
		Control &ctrl, REAL8 theta, REAL8 thetar, REAL8 poros, REAL8 rootdepth,
		REAL8 Keff, REAL8 psiae, REAL8 bclambda,
		REAL8 ra, REAL8 gc, REAL8 &DelCanStor, REAL8 &evap_a, REAL8 &transp_a,
		UINT4 s, UINT4 r, UINT4 c) {

	//energy balance parameters
	REAL8 dt = ctrl.dt;
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

	// variables for Sperry's model
	REAL8 Sold = 0;  // Soil Saturation at beginning of t
	REAL8 gp = 0; //plant conductance
	REAL8 gsr = 0; //soil conductance
	REAL8 gsrp = 0; //grs + gp
	REAL8 E = 0; // Temporary calculatio of transpiration
	REAL8 RAI = 0; // Potential Root Area Index, which is maximum active RAI under current root density
	//auxiliary functions to group common terms in derivatives
	REAL8 PIZ = 0; // pi times root depth
	REAL8 df2dS_numfac = 0;
	REAL8 denfac = 0;
	REAL8 dF2dS_num = 0;
	REAL8 dF2dS_term = 0;

	UINT4 nsp = getNumSpecies();

	psiae= 0.4;
	bclambda = 4.3;

	if (s == nsp - 1) //for bare soil, water reaching the ground is pp times its proportion of the cell
		evap_a = transp_a = 0;
	else {

		ea = AirEmissivity(atm.getTemperature()->matrix[r][c]);
		rho_a = AirDensity(atm.getTemperature()->matrix[r][c]); //kgm-3
		z = bas.getDEM()->matrix[r][c];
		gamma = PsychrometricConst(101325, z);
		airRH = atm.getRelativeHumidty()->matrix[r][c];

		albedo = _species[s].albedo;
		emissivity = _species[s].emissivity;
		BeerK = _species[s].KBeers;
		LAI = _species[s]._LAI->matrix[r][c];

		CanStor = getIntercWater(s, r, c);
		MaxCanStor = getMaxCanopyStorage(s, r, c);

		soilRH = 1; //min<REAL8>(1.0,Calculate_gs_theta(theta, fc, _species[s].WiltingPoint, 2.0)); //calculates soil pore relative humidity
		leavesurfRH = airRH + ((1 - airRH) / MaxCanStor) * CanStor;

		ra_t = ra + (1 / gc);

		fA = -4 * emissivity * stefboltz;//pools together net radiation factors
		fB = (-1 / (ra * gamma)) * rho_a * spec_heat_air; // pools together the latent heat factors
		fC = (-1 / (ra)) * rho_a * spec_heat_air; // pools together the sensible heat factors
		fD = (-1 / (ra_t * gamma)) * rho_a * spec_heat_air; // pools together the latent heat factors

		evap_a =
				CanStor < MaxCanStor ?
						-CanStor / ctrl.dt * powl((CanStor / MaxCanStor), 0.6) :
						-CanStor / ctrl.dt;

		// Calculation of conductances necessary for the implementation of Sperry's model
		// to calculate leaf water potential.

		// Soil to root conductance. Adapted from Rodriguez-Iturbe and Porporato (eq 6.4, page 181) for
		// units of hydraulic head

		Sold = (theta - thetar) / (poros - thetar);

		RAI = 100;
		REAL8 sperry_c = 1.9;
		REAL8 sperry_d = 204;
		REAL8 sperry_ks = 11.7;
		REAL8 root_a = 8;

		// derivative of F[2] calculated in Wolfram using:
		// derivative k*sqrt(R*x^-a)/(pi*Z) * L*g*exp(-(p/d)^c) / (k*sqrt(R*x^-a)/(pi*Z) +  L*g*exp(-(p/d)^c))
		df2dS_numfac = 0.5 * root_a *  Keff * Keff * LAI * RAI;
		PIZ = PI * rootdepth;

		int k = 0;


		//state variables:
		// x[0]: S - (degree of saturation at time t+1)
		// x[1]: psi_s - soil water potential
		// x[2]: psi_l  leaf water potential
		// x[3]: Ts - Leaf temperature

		colvec x(4);
		colvec deltax(4);
		colvec F(4);
		mat J = zeros<mat>(4,4);

		x[0] = Sold;
		x[1] = psiae / powl(x[0], bclambda);
		x[2] = x[1];
		x[3] = _species[s]._Temp_c->matrix[r][c];

		do {

			lambda = x[3] < 0 ? lat_heat_vap + lat_heat_fus : lat_heat_vap;

			//x[3] = _species[s]._Temp_c->matrix[r][c];

			desdTs = 611
					* ((17.3 / (x[3] + 237.7))
							- ((17.3 * x[3]) / (powl(x[3] + 237.2, 2))))
					* expl(17.3 * x[3] / (x[3] + 237.7));
			//LE_lim = evap_a * rho_w * lambda;
			//LE_unlim = LatHeatCanopy(atm, leavesurfRH, ra, Ts, r, c);

			LE = LatHeatCanopy(bas, atm, leavesurfRH, ra, x[3], r, c); /*LE = LE_unlim;   max<REAL8>(LE_lim, LE_unlim);
			 if(LE == LE_lim)
			 fB = 0;*/
			LET = LatHeatCanopy(bas, atm, soilRH, ra_t, x[3], r, c);
			H = SensHeatCanopy(atm, ra, x[3], r, c);

			// Sperry stuff
			gsr = Keff * sqrt(RAI * powl(x[0], -root_a)) / ( PI * rootdepth);
			gp = sperry_ks * expl(-powl(x[2] / sperry_d, sperry_c));
			denfac = gsr + gp * LAI;
			gsrp = LAI * gsr * gp / denfac;

			E = -LET / (rho_w * lambda);
			E= max(0.0,E);

			dF2dS_num = df2dS_numfac * gp * powl(x[0], -root_a - 1)* (x[2] - x[1]);
			dF2dS_term = (dF2dS_num / (PIZ * PIZ * denfac * denfac));

			F[0] = ((x[0] - Sold) * (poros - thetar) + thetar) * rootdepth / dt + E;
			F[1] = psiae / powl(x[0], bclambda) - x[1];
			F[2] = gsrp * (x[2] - x[1]) - E;
			F[3] = NetRadCanopy(atm, x[3], emissivity, albedo, BeerK, LAI, r, c)
					+ LE + H + LET;

			// Fill out the jacobian
			J(0,0) = rootdepth * (poros - thetar) / dt;
		//	J(0,3) = fB * desdTs / (rho_w * lambda);

			J(1,0) = -bclambda * psiae * powl(x[0], -(bclambda + 1));
			J(1,1) = -1;

			J(2,0) = dF2dS_term - (dF2dS_term / gsr);
			J(2,1) = -gsrp;
			J(2,2) = -gsrp * sperry_c * powl(x[2] / sperry_d, sperry_c)* (x[2] - x[1]) / x[2] + gsrp
					+ gsrp * gsrp * sperry_c * powl(x[2] / sperry_d, sperry_c) * (x[2] - x[1]) / (x[2] * gsr);
		//	J(2,3) = -fB * desdTs / (rho_w * lambda);

			J(3,2) = 0;
			J(3,3) = fA * powl(x[3] + 273.2, 3) + fB * desdTs * leavesurfRH
					+ fC + fD * desdTs * soilRH;

			// solve system
			if (!solve(deltax, J, -F)) {
				cout
						<< "Singular Jacobian found in Newton solver for canopy balance.\n";
				return 1;
			}
			//	        cout <<"x: " <<  x << endl;
			x += deltax;

			cout << " x: " << std::endl << x;
			cout << " x2-x1: " << std::endl << x[2] - x[1];
			cout << " deltax: " << std::endl << deltax;
			cout << " F: " << std::endl << F;
			cout << " norm x: " << std::endl << norm(deltax,2);
			cout << " J: " << std::endl << J;


			//_species[s]._Temp_c->matrix[r][c] = x[3];



			k++;
		} while (norm(deltax, 2) > 0.0001 && k < MAX_ITER);

		if (k >= MAX_ITER)
			std::cout
					<< "WARNING: non-convergence in canopy energy balance at cell row: "
					<< r << " col: " << c << " closure err: " << (Ts1 - Ts)
					<< endl;

		if (Ts1 < atm.getTemperature()->matrix[r][c]) { //if teh calcualted canopy temperature is lower than air temperature make it air temperature
			Ts1 = atm.getTemperature()->matrix[r][c];
			LET = LatHeatCanopy(bas, atm, soilRH, ra_t, Ts, r, c);
			LE = LatHeatCanopy(bas, atm, leavesurfRH, ra, Ts, r, c);
			_species[s]._Temp_c->matrix[r][c] = Ts1;
		}

		evap_a = std::min<REAL8>(-evap_a, fabs(-LE / (rho_w * lambda))); //swap sign since outgoing evaporation is negative and we accumulate it as positive. Also checks for negative evap
		transp_a = std::max<REAL8>(0.0, -LET / (rho_w * lambda)); //swap sign since outgoing evaporation is negative and we accumulate it as positive. Also checks for negative evap

		DelCanStor -= evap_a * ctrl.dt;

		_species[s]._NetR_Can->matrix[r][c] = NetRadCanopy(atm, Ts1, emissivity,
				albedo, BeerK, LAI, r, c);
		_species[s]._LatHeat_Can->matrix[r][c] = LE + LET; //LatHeatCanopy(atm, ra, Ts1, r, c);
		_species[s]._SensHeat_Can->matrix[r][c] = SensHeatCanopy(atm, ra, Ts1,
				r, c);

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

