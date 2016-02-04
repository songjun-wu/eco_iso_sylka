/*
 * SolveSurfaceEnergyBalance.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: Marco.Maneta
 */

#include "Basin.h"

int Basin::SolveSurfaceEnergyBalance(Atmosphere &atm,
									Control &ctrl,
									REAL8 ra,
									REAL8 rs,
									REAL8 rc,
									REAL8 Kbeers,
									REAL8 lai,
									REAL8 emis_can,
									REAL8 Temp_can,
									REAL8 &nrad,
									REAL8 &latheat,
									REAL8 &sensheat,
									REAL8 &grndheat,
									REAL8 &snowheat,
									REAL8 &meltheat,
									REAL8 &Tsold,
									REAL8 &etp,
									REAL8 &pond,
									REAL8 &theta10cm,
									REAL8 &Ts1,
									REAL8 &Tdold,
									REAL8 p,
									UINT4 r,
									UINT4 c){

	float dt = ctrl.dt; //time step
	REAL8 fA, fB, fC, fD, fG, fH; //pooling factors
	REAL8 C; // soil heat capacity
	REAL8 K; // soil thermal heat conductivity
	REAL8 Pe = dt < 86400 ? 86400 : 31536000; //period is daily if time step is less than a day adn yearly if time step is daily or larger
	REAL8 Ts = _Temp_s->matrix[r][c];
	REAL8 Td = _Temp_d->matrix[r][c];
	REAL8 fTs;
	REAL8 dfTs;
	REAL8 desdTs;
	REAL8 d; // temperature fluctuation damping depth
	REAL8 d0; //bottom depth of bottom thermal layer
	REAL8 z;
	REAL8 gamma;
	REAL8 LE, H, G, S, LM, R; // the last two variables are the latent heat of melt and the heat advected by rain
	REAL8 MeltFac; //snowmelt factor
	REAL8 h; //snow water equivalent
	REAL8 n; //porosity
	REAL8 fc; //field capacity
	REAL8 thetar; //residual moisture content
	REAL8 SoilRH; //soil relative humidity
	REAL8 ea; //emissivity of air
	REAL8 rho_a; //density of air
	REAL8 RainIntensity; //ms-1
	//REAL8 exfilt;
	REAL8 lambda = Ts1 < 0 ?  lat_heat_vap + lat_heat_fus : lat_heat_vap;


	z = _DEM->matrix[r][c];
	gamma =PsychrometricConst(101325, z);
	d0 = _dampdepth->matrix[r][c];

	MeltFac = _meltCoeff->matrix[r][c];

	//REAL8 temp = (-38113*(_fieldcap->matrix[r][c]/13.515)*expl(-13.515*theta/_fieldcap->matrix[r][c])+193.880417969279)/(38113*(_fieldcap->matrix[r][c]/13.515)*(expl(-13.515*_theta_r->matrix[r][c]/_fieldcap->matrix[r][c])-expl(-13.515)));//rs/(-3.8113e4*(_fieldcap->matrix[r][c]/13.515)*(expl(-13.515) - expl(-13.515*_theta_r->matrix[r][c]/_fieldcap->matrix[r][c])));

	h = _snow->matrix[r][c];
	n = _porosity->matrix[r][c];
	ea = AirEmissivity(atm.getTemperature()->matrix[r][c]);
	rho_a = AirDensity(atm.getTemperature()->matrix[r][c]); //kgm-3

	C = SoilHeatCapacity(_soil_dry_heatcap->matrix[r][c],  n, theta10cm, Ts1);
	K = SoilHeatConductivity(_soil_dry_thermcond->matrix[r][c], n, 	theta10cm);

	//d = sqrt((K/C) * Pe / PI);
	d = sqrt( (K/C) / ( 2 * ( 2 * PI / Pe) ) );

	fc = _fieldcap->matrix[r][c];
	thetar = _theta_r->matrix[r][c];
	if (h>0.005){
		SoilRH = 1; //relative humidity in snow pores is assumed to be saturated. Switch when there is at least 1 cms of snow
		rs = 0; //no extra resistance to evaporation
	}
	else
		//SoilRH = min<REAL8>( 1.0, Calculate_gs_theta(theta10cm, fc, thetar, 2.0) ); //calculates soil pore relative humidity
		SoilRH = Calculate_soil_RH(theta10cm, fc);




	//energy balance factors that do not need updating in the N-R loop
	fA = -4*_emiss_surf->matrix[r][c] * stefboltz;	//pools together net radiation factors
	fB = (-1/gamma) * (1/(ra + rs) + rc) * rho_a * spec_heat_air; //(-1/((ra + rs + rc) * gamma)) * rho_a * spec_heat_air; // pools together the latent heat factors
	fC = (-1/(ra)) * rho_a * spec_heat_air; // pools together the sensible heat factors
	fD =  -(d * C /(2*dt)) - PI * d * C / Pe ; //same for ground heat flux (both terms). Assumes C does not depend on Ts (tiny dependency does nto affect derivative)
	//fE = 0;// -( ((n - theta)*spec_heat_air*101325)/Ra ) * dampdepth / (2*dt);      //dampdepth * 101325 / (dt * Ra); // continued storage term because C depends on Ts
	//fF = 0;//-(PI*dampdepth/Pe) * ((n - theta)*spec_heat_air*101325)/Ra; // second term of ground heat flux
	fG = -spec_heat_ice * rho_w * h * (1 / dt); //and heat fluxes into the snow
	fH = -1*lat_heat_fus * rho_w * MeltFac; // last value is M factor

	//exfilt = ExfiltrationCapacity(theta, dt, r, c);

	RainIntensity = pond * p / dt;
	R = 0; //h > 0 ? RainHeat(atm, RainIntensity, r, c) : 0.0; //heat advected by rain only if there is snowpack present



	int k = 0;

	do{

		Ts = _Temp_s->matrix[r][c];
		Td = _Temp_d->matrix[r][c];
		desdTs = 611 * ( (17.3/( Ts + 237.7)) - ((17.3 * Ts)/(powl(Ts + 237.2 , 2))) )
									* exp(17.3 * Ts /( Ts + 237.7));

		Td = -( ((d/d0) * 2 * PI * (Td - Ts) / Pe) * dt ) + Td;


		H = SensHeat(atm, ra, Ts, r, c);
		if (h > 0.005){
		 LE = fB = 0;
		 G = 0;
		}
		else{
		 G = GrndHeat(atm, ctrl, theta10cm, Ts, Td, r, c);
		 LE = LatHeat(atm, SoilRH, ra, rs, rc, Ts, r, c);// * temp;
		}
		S = SnowHeat(atm, ctrl, Ts, r, c);
		LM = MeltHeat(atm, ctrl, Ts, h, MeltFac, r, c);
		if(LM == 0)
			fH = 0;

		fTs = NetRad(atm, Ts, Kbeers, lai, emis_can, Temp_can,  r, c) + LE + H + G + S + LM + R;
		dfTs = fA*powl(Ts + 273.2, 3) + fB * desdTs * SoilRH + fC + ((G==0)? 0 : fD) + fG + fH;

		Ts1 = Ts - (fTs/dfTs);
		_Temp_s->matrix[r][c] = Ts1;

		lambda = Ts1 < 0 ?  lat_heat_vap + lat_heat_fus : lat_heat_vap;

		k++;
	}while(fabs(Ts1 - Ts) > 0.00001 && k < MAX_ITER);

	if (k>=MAX_ITER)
		std::cout << "WARNING: non-convergence in surface energy balance at cell row: " << r << " col: " << c << " closure err: " << (Ts1 - Ts) << endl;

	//Td = -G/( C* (d + d0) )* dt + Td;



	nrad += NetRad(atm, Ts1, Kbeers, lai, emis_can, Temp_can, r, c) * p;
	latheat += LE * p;
	sensheat += SensHeat(atm, ra, Ts1, r, c) * p; //SensHeat(atm, ra, Ts1, r, c) * p;
	grndheat += GrndHeat(atm, ctrl, theta10cm, Ts1, Td, r, c) * p;
	snowheat += SnowHeat(atm, ctrl, Ts1, r, c) * p;
	meltheat += MeltHeat(atm, ctrl, Ts1, h, MeltFac, r, c) * p;
	Tsold += Ts1 * p;
	Tdold += Td * p;



	SoilEvapotranspiration(-LE*p, Ts1, lambda, rs, etp, theta10cm, dt, r, c);

	return EXIT_SUCCESS;
}
