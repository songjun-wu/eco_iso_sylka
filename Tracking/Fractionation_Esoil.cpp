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
 * Fractionation_Esoil.cpp
 *
 *  Created on: Apr 5, 2017
 *      Author: Sylvain Kuppel
 */

#include "Tracking.h"

int Tracking::dDfrac_E(Atmosphere &atm, Basin &bsn, Control &ctrl,
		REAL8 V_old, REAL8 V_new, REAL8 &dD_old, REAL8 &dD_new, REAL8 &dDevap,
		int r, int c){

	REAL8 alpha_p; // equilibrium isotope fractionation factor (fraction)
	REAL8 eps_p; // equilibrium isotope fractionation factor (per mil)
	REAL8 eps_k; // kinetic isotope fractionation factor (per mil)
	REAL8 eps; // total isotope fractionation factor (per mil)
	REAL8 dD_atm; // Isotopic signatures (permil)
	REAL8 dD_star; // Limiting isotopic composition (per mil)
	REAL8 m; // Calculation factor (-)
	REAL8 T; // Air temperature (K)
	REAL8 h; // Relative humidity (fraction)
	REAL8 f; // Water loss fraction after evaporation (fraction)

	// Use soil temperature and relative humidity
	T = bsn.getSoilTemp()->matrix[r][c] + 273.15 ;
	h = atm.getRelativeHumidty()->matrix[r][c];

	// Horita and Wesolowski (1994)
	alpha_p = expl((1158.8*powl(T,3)*1e-9 - 1620.1*powl(T,2)*1e-6 + 794.84*T*1e-3 -\
			161.04 + 2.9992*1e9/powl(T,3))/1000);

	// Skrzypek et al. (2015)
	eps_p = (alpha_p - 1)*1000;

	// (Gat, 1995) + (Gibson and Reid, 2014)
	dD_atm = (atm.getdDprecip()->matrix[r][c] - eps_p)/ alpha_p;

	// Gonfiantini (1986) + Araguas-Araguas et al. (2000)
	// for soil (n=1, open water n=0.5))
	eps_k = (1-h)*25.0;

	// Gibson and Reid (2010)
	eps = eps_p/alpha_p + eps_k;

	// (Gat and Levy, 1978) + (Gat, 1981)
	dD_star = (h*dD_atm + eps) /	(h - eps/1000);

	// (Welhan and Fritz, 1977) + (Allison and Leaney, 1982)
	m = (h - eps/1000) / (1 - h + eps_k/1000);

	// Evaporative loss fraction
	f = V_new/V_old;

	// (Hamilton et al., 2005)
	// New isotopic signature in topsoil
	dD_new = dD_star + (dD_old - dD_star) * powl(f,m);
	if(abs(dD_new)>1e3)
		cout << r << " " << c << " : dDsoil_new ->" << dD_new << " dDold ->" << dD_old <<
		" dDstar ->" << dD_star << " f ->" << f <<" m ->" << m << endl;
	// Isotopic signature of evaporated water
	dDevap = (dD_old - h*dD_atm - eps)/ (1-h+eps_k/1000);

	return EXIT_SUCCESS;

}

int Tracking::d18Ofrac_E(Atmosphere &atm, Basin &bsn, Control &ctrl,
		REAL8 V_old, REAL8 V_new, REAL8 &d18O_old, REAL8 &d18O_new, REAL8 &d18Oevap,
		int r, int c){

	REAL8 alpha_p; // equilibrium isotope fractionation factor (fraction)
	REAL8 eps_p; // equilibrium isotope fractionation factor (per mil)
	REAL8 eps_k; // kinetic isotope fractionation factor (per mil)
	REAL8 eps; // total isotope fractionation factor (per mil)
	REAL8 d18O_atm; // Isotopic signatures (permil)
	REAL8 d18O_star; // Limiting isotopic composition (per mil)
	REAL8 m; // Calculation factor (-)
	REAL8 T; // Air temperature (K)
	REAL8 h; // Relative humidity (fraction)
	REAL8 f; // Water loss fraction after evaporation (fraction)

	// Use soil temperature and relative humidity
	T = bsn.getSoilTemp()->matrix[r][c] + 273.15 ;
	h = atm.getRelativeHumidty()->matrix[r][c];


	// Horita and Wesolowski (1994)
	alpha_p = expl((-7.685 + 6.7123*1000/T - 1.6664*1e6/powl(T,2) +
			0.35041*1e9/powl(T,3))/1000);

	// Skrzypek et al. (2015)
	eps_p = (alpha_p - 1)*1000;

	// (Gat, 1995) + (Gibson and Reid, 2014)
	d18O_atm = (atm.getd18Oprecip()->matrix[r][c] - eps_p)/ alpha_p;

	// Gonfiantini (1986) + Araguas-Araguas et al. (2000)
	// for soil (n=1, open water n=0.5))
	eps_k = (1-h)*28.4;

	// Gibson and Reid (2010)
	eps = eps_p/alpha_p + eps_k;

	// (Gat and Levy, 1978) + (Gat, 1981)
	d18O_star = (h*d18O_atm + eps) /	(h - eps/1000);

	// (Welhan and Fritz, 1977) + (Allison and Leaney, 1982)
	m = (h - eps/1000) / (1 - h + eps_k/1000);

	// Evaporative loss fraction
	f = V_new/V_old;

	// (Hamilton et al., 2005)
	// New isotopic signature in topsoil
	d18O_new = d18O_star + (d18O_old - d18O_star) * powl(f,m);
	// Isotopic signature of evaporated water
	d18Oevap = (d18O_old - h*d18O_atm - eps)/ (1-h-eps_k/1000);

	return EXIT_SUCCESS;

}
