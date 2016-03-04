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
		REAL8 ra, REAL8 &DelCanStor, REAL8 &evap_a, REAL8 &transp_a,
		UINT4 s, UINT4 r, UINT4 c) {

	//some constants
	const REAL8 grav = 9.8;
	const REAL8 Vw = 18e-6; // partial molal volume of water m3 mol-1
	const REAL8 Rbar = 8.31446; // Universal gas constant in J K-1 mol-1
	//energy balance parameters
	REAL8 dt = ctrl.dt;
	REAL8 fA, fB, fC, fD; //pooling factors
	REAL8 temp = 0;
	REAL8 rho_a; //density of air
	REAL8 airRH; //air humidity
	REAL8 airTp; // air temperature
	REAL8 es; // saturated vapor pressure
	REAL8 ea;
	REAL8 desdTs; // derivative of saturation vapor pressure function with respect to Ts
	REAL8 emissivity; //canopy emissivity
	REAL8 albedo; //canopy albedo
	REAL8 LAI;
	REAL8 BeerK; //Beers-Lambert coefficient
	REAL8 LE, H;
	REAL8 z; //terrain height
	REAL8 gamma; //psychrometric constant

	REAL8 sperry_c;
	REAL8 sperry_d;
	REAL8 sperry_ks;
	REAL8 root_a;

	REAL8 lambda = lat_heat_vap;
	REAL8 ra_t; //resistance to transpiration ra_t = ra + 1/gc
	REAL8 LET; //latent heat of transpiration
	REAL8 CanStor = 0;
	REAL8 MaxCanStor = 0;

	REAL8 leafRH; //soil relative humidty use in teh calculation of soil vapor pressure for latent heat exchanges
	REAL8 leavesurfRH; //relative humidity of the leave surface. 1 when leave is saturated with intercepted water, airRH when no water
	REAL8 dleafRHdT = 0;
	REAL8 dleafRHdpsi_l = 0;
	REAL8 dgcdlwp = 0;
	REAL8 dEdlwp = 0;
	REAL8 dEdT = 0;
	REAL8 dLETdlwp =0;
	REAL8 dLETdT =0;


	// variables for Sperry's model
	REAL8 Sold = 0;  // Soil Saturation at beginning of t
	REAL8 gp = 0; //plant conductance
	REAL8 gsr = 0; //soil conductance
	REAL8 gsrp = 0; //grs + gp
	REAL8 E = 0; // Temporary calculatio of transpiration
	REAL8 RAI = 0; // Potential Root Area Index, which is maximum active RAI under current root density
	//auxiliary functions to group common terms in derivatives
	REAL8 denfac = 0;


	REAL8 gc = 0;
	REAL8 lwp_den, lwp_c; //denominator and exponent of lwp stomatal model
	REAL8 dgcdfgspsi = 0;



	UINT4 nsp = getNumSpecies();

	if (s == nsp - 1) //for bare soil, water reaching the ground is pp times its proportion of the cell
		evap_a = transp_a = 0;
	else {



		airTp = atm.getTemperature()->matrix[r][c];
		rho_a = AirDensity(airTp); //kgm-3
		z = bas.getDEM()->matrix[r][c];
		gamma = PsychrometricConst(101325, z);
		airRH = atm.getRelativeHumidty()->matrix[r][c];

		ea = SatVaporPressure(airTp) * airRH;


		albedo = _species[s].albedo;
		emissivity = _species[s].emissivity;
		BeerK = _species[s].KBeers;
		LAI = _species[s]._LAI->matrix[r][c];

		RAI = 5.5; //_species[s]._RootMass->matrix[r][c] * _species[s].SRA;
		root_a = _species[s].RAI_a;
		sperry_c = _species[s].sperry_c;
		sperry_d = _species[s].sperry_d;
		sperry_ks = _species[s].sperry_Kp / _species[s]._Height->matrix[r][c];

		lwp_den = _species[s].lwp_d;
		lwp_c = _species[s].lwp_c;


		CanStor = getIntercWater(s, r, c);
		MaxCanStor = getMaxCanopyStorage(s, r, c);

		leafRH = 1; //min<REAL8>(1.0,Calculate_gs_theta(theta, fc, _species[s].WiltingPoint, 2.0)); //calculates soil pore relative humidity
		leavesurfRH = airRH + ((1 - airRH) / MaxCanStor) * CanStor;

		LE = LatHeatCanopy(bas, atm, leavesurfRH, ra, airTp, r, c);



		fA =  -4 * emissivity * stefboltz;//pools together net radiation factors
		fB = 0;// (-1 / (ra * gamma)) * rho_a * spec_heat_air; // pools together the latent heat factors
		fC = (-1 / (ra)) * rho_a * spec_heat_air; // pools together the sensible heat factors


		evap_a =
				CanStor < MaxCanStor ?
						-CanStor / ctrl.dt * powl((CanStor / MaxCanStor), 0.6) :
						-CanStor / ctrl.dt;

		// Calculation of conductances necessary for the implementation of Sperry's model
		// to calculate leaf water potential.

		// Soil to root conductance. Adapted from Rodriguez-Iturbe and Porporato (eq 6.4, page 181) for
		// units of hydraulic head

		Sold = (theta - thetar) / (poros - thetar);

		int k = 0;


		/***
		* state variables:
		* x[0]: S - (degree of saturation at time t+1)
		* x[1]: psi_s - soil water potential
		* x[2]: psi_l  leaf water potential
		* x[3]: Ts - Leaf temperature
		***/

		colvec x(4);
		colvec deltax(4);
		colvec F(4);
		mat J = zeros<mat>(4,4);

		mat D = eye(4,4);

		//provide initial guess  for loop
		x[0] = Sold;
		x[1] = psiae / powl(x[0], bclambda);
		x[2] = x[1];
		x[3] = airTp;

		//used to calculate the gc factors other than f_lwp
		// this information is contained in dgcdfgspsi and is used to calculate gc in the solution scheme below
		CalculateCanopyConduct(bas, atm, ctrl, x[2], dgcdfgspsi, s, r, c);

		do {

			lambda = x[3] < 0 ? lat_heat_vap + lat_heat_fus : lat_heat_vap;

			gc = dgcdfgspsi * 1 / (1 + powl(x[2]/lwp_den, lwp_c));

			if (gc < 1e-13)
				gc = 1e-13;

			ra_t = ra + (1 / gc);

			if(x[0]<0)
				x[0] = 0.01;
			temp = -x[2] * rho_w * grav * Vw / (Rbar*(x[3]+273.15));
			if (temp >-708.4)
				leafRH = std::min<REAL8>(1,expl(temp));
			else
				leafRH = 0;

			leafRH = 1;


			LET = LatHeatCanopy(bas, atm, leafRH, ra_t, airTp, r, c);
			H = SensHeatCanopy(atm, ra, x[3], r, c);

			E = -LET / (rho_w * lambda);
		//	E= std::max<REAL8>(0.0,E);

			// Sperry stuff

			gsr = Keff *powl(x[0],2*bclambda+3)* sqrt(RAI) / ( PI * rootdepth);;

			if(x[2]<0)
				temp = -powl(x[1] / sperry_d, sperry_c);
			else
				temp = -powl(x[2] / sperry_d, sperry_c);
			if (temp <-708.4) // here to prevent setting the perror underflow flag
				gp = 0;
			else
				gp = sperry_ks * expl(temp);

			denfac = gsr + gp * LAI;
			gsrp = LAI * gsr * gp / denfac;

/*
			if (gsrp< 1e-13 || x[2]<0)
				LET = E =leafRH= gsrp = 0;
*/



			dleafRHdT = leafRH *  x[2] * rho_w * grav * Vw / (Rbar*(x[3]+273.15)*(x[3]+273.15));

			if(leafRH == 1)
				dleafRHdpsi_l =dleafRHdT = 0;
			else
				dleafRHdpsi_l = - rho_w * grav * Vw * leafRH  / (Rbar*(x[3]+273.15));

			es = SatVaporPressure(x[3]);
			desdTs = es *  237.15 * 17.3 / (powl(x[3] + 237.2, 2));

			dgcdlwp = gc == 1e-13 ? 0 :  - dgcdfgspsi * lwp_c * powl(x[2]/lwp_den, lwp_c) / (x[2] * ( powl(x[2]/lwp_den, lwp_c) + 1) * ( powl(x[2]/lwp_den, lwp_c) + 1));
			dLETdlwp = 0;//LET / (ra_t * gc * gc) * dgcdlwp;
			dLETdT = - rho_a * spec_heat_air / (ra_t * gamma) * (desdTs*leafRH + es*dleafRHdT);

		    dEdlwp = - dLETdlwp / (rho_w * lambda);
		    dEdT = 0;//E == 0 ? 0 : - dLETdT / (rho_w * lambda);

			F[0] = (x[0] - Sold) * (poros - thetar) * rootdepth / dt + E;
			F[1] = psiae / powl(x[0], bclambda) - x[1];
			F[2] = gsrp * (x[2] - x[1]) - E;
			F[3] = NetRadCanopy(atm, airTp, emissivity, albedo, BeerK, LAI, r, c)
					+ LE + H + LET;

			// Fill out the jacobian
			J(0,0) = rootdepth * (poros - thetar) / dt;
			J(0,2) = dEdlwp;
			J(0,3) =  dEdT;

			J(1,0) = -bclambda * psiae * powl(x[0], -(bclambda + 1));
			J(1,1) = -1;

			J(2, 0) = gp * LAI * (x[2] - x[1]) * powl(x[0], 2 + 2 * bclambda)
					* Keff * sqrt(RAI) * (3 + 2 * bclambda)
					/ (PI * rootdepth * denfac)
					- gp * LAI * (x[2] - x[1]) * powl(x[0], 5 + 4 * bclambda)
							* Keff * Keff * RAI * (3 + 2 * bclambda)
							/ powl((PI * rootdepth * denfac), 2);
			J(2, 1) = -gsrp;
			J(2, 2) = -sperry_c * powl(x[2] / sperry_d, sperry_c) * gsrp
					* (x[2] - x[1]) / x[2] + gsrp
					+ gsrp * gsrp * PI * rootdepth * sperry_c
							* powl(x[2] / sperry_d, sperry_c) * (x[2] - x[1])
							/ (x[2] * Keff * powl(x[0], 2 * bclambda + 3)
									* sqrt(RAI)) - dEdlwp;
			J(2, 3) = -dEdT;

/*			if(E==0)
				J(2,2) = 1;*/


			J(3,2) = dLETdlwp;
			J(3,3) = fA * powl(x[3] + 273.2, 3)*0 + fB * desdTs * leavesurfRH
					+ fC + dLETdT;

			// solve system
			if (!solve(deltax, J, -F)) {
				cout << "Singular Jacobian found in Newton solver for canopy balance.\n";
				//return 1;
			}

			if(k>100){
				cout << "E: ";
			cout << E << endl;
			cout << "x: " << x << endl;
			cout << "F " << F << endl << endl;
			cout << gsrp * (x[2] - x[1]) << endl << endl;
			cout << J << endl << endl;
			}

			x += deltax;

			k++;




		} while (norm(F, "inf") > 0.000001 && k < MAX_ITER);

		if (k >= MAX_ITER)
			std::cout
					<< "WARNING: non-convergence in canopy energy balance at cell row: "
					<< r << " col: " << c << " closure err: " << norm(deltax, 2)
					<< endl;

		if (x[3] < atm.getTemperature()->matrix[r][c]) { //if the calculated canopy temperature is lower than air temperature make it air temperature
			LET = LatHeatCanopy(bas, atm, leafRH, ra_t, x[3], r, c);
			LE = LatHeatCanopy(bas, atm, leavesurfRH, ra, x[3], r, c);
			x[3] = atm.getTemperature()->matrix[r][c];
			_species[s]._Temp_c->matrix[r][c] = x[3];
		}

		evap_a = std::min<REAL8>(-evap_a, fabs(-LE / (rho_w * lambda))); //swap sign since outgoing evaporation is negative and we accumulate it as positive. Also checks for negative evap
		transp_a = std::max<REAL8>(0.0, -LET / (rho_w * lambda)); //swap sign since outgoing evaporation is negative and we accumulate it as positive. Also checks for negative evap

		DelCanStor -= evap_a * ctrl.dt;

		_species[s]._NetR_Can->matrix[r][c] = NetRadCanopy(atm, x[3], emissivity,
				albedo, BeerK, LAI, r, c);
		_species[s]._LatHeat_Can->matrix[r][c] = LE + LET; //LatHeatCanopy(atm, ra, Ts1, r, c);
		_species[s]._SensHeat_Can->matrix[r][c] = SensHeatCanopy(atm, ra, x[3],
				r, c);
		_species[s]._LeafWatPot->matrix[r][c] = -(x[2] - x[1])*0.0098;

		CalculateCanopyConduct(bas, atm, ctrl, x[2], dgcdfgspsi, s, r, c); //Updates canopy conductance with final values of lwp

		///////////this chunk of code is to make sure we are not transpiring below residual moisture content
        /////////// Probably not needed anymore since mass balance is enforced in the system of eqs.
		/////////// solved in this function
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

