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

int Tracking::dDfrac_Esoil(Atmosphere &atm, Basin &bsn, Control &ctrl, REAL8 theta_new,
		int r, int c){

	REAL8 alpha_p; // equilibrium isotope fractionation factor (fraction)
	REAL8 eps_p; // equilibrium isotope fractionation factor (per mil)
	REAL8 eps_k; // kinetic isotope fractionation factor (per mil)
	REAL8 eps; // total isotope fractionation factor (per mil)
	REAL8 dD_atm, dD_old; // Isotopic signatures (permil)
	REAL8 dD_star; // Limiting isotopic composition (per mil)
	REAL8 m; // Calculation factor (-)
	REAL8 T; // Air temperature (K)
	REAL8 h; // Relative humidity (fraction)
	REAL8 f; // Water loss fraction after evaporation (fraction)

	// Use soil temperature and relative humidity
	T = bsn.getSoilTemp()->matrix[r][c] + 273.15 ;
	h = atm.getRelativeHumidty()->matrix[r][c];
	dD_old = _dDsoil1->matrix[r][c];///1000;


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

	eps = eps_p/alpha_p + eps_k;

	// (Gat and Levy, 1978) + (Gat, 1981)
	dD_star = (h*dD_atm + eps) /	(h - eps/1000);

	// (Welhan and Fritz, 1977) + (Allison and Leaney, 1982)
	m = (h - eps/1000) / (1 - h + eps_k/1000);

	// Evaporative loss fraction
	f = theta_new/bsn.getSoilMoist1()->matrix[r][c];

	// (Hamilton et al., 2005)
	// New isotopic signature in topsoil
	_dDsoil1->matrix[r][c] = dD_star + (dD_old - dD_star) * powl(f,m);
	// Isotopic signature of evaporated water
	_dDevapS->matrix[r][c] = (_dDsoil1->matrix[r][c] - h*dD_atm - eps)/ (1-h-eps_k/1000);

	return EXIT_SUCCESS;

}

int Tracking::d18Ofrac_Esoil(Atmosphere &atm, Basin &bsn, Control &ctrl, REAL8 theta_new,
		int r, int c){

	REAL8 alpha_p; // equilibrium isotope fractionation factor (fraction)
	REAL8 eps_p; // equilibrium isotope fractionation factor (per mil)
	REAL8 eps_k; // kinetic isotope fractionation factor (per mil)
	REAL8 eps; // total isotope fractionation factor (per mil)
	REAL8 d18O_atm, d18O_old; // Isotopic signatures (permil)
	REAL8 d18O_star; // Limiting isotopic composition (per mil)
	REAL8 m; // Calculation factor (-)
	REAL8 T; // Air temperature (K)
	REAL8 h; // Relative humidity (fraction)
	REAL8 f; // Water loss fraction after evaporation (fraction)

	// Use soil temperature and relative humidity
	T = bsn.getSoilTemp()->matrix[r][c] + 273.15 ;
	h = atm.getRelativeHumidty()->matrix[r][c];
	d18O_old = _d18Osoil1->matrix[r][c];///1000;


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
	f = theta_new/bsn.getSoilMoist1()->matrix[r][c];

	// (Hamilton et al., 2005)
	// New isotopic signature in topsoil
	_d18Osoil1->matrix[r][c] = d18O_star + (d18O_old - d18O_star) * powl(f,m);
	// Isotopic signature of evaporated water
	_d18OevapS->matrix[r][c] = (_d18Osoil1->matrix[r][c] - h*d18O_atm - eps)/ (1-h-eps_k/1000);

	return EXIT_SUCCESS;

}
