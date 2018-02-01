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
 * GenerateConfigTemplateTrck.cpp
 *
 *  Created on: Jan 30, 2018
 *      Author: Sylvain Kuppel
 */

#include  <fstream>
#include <unistd.h>

#include "Sativa.h"

void GenerateConfigTrckTemplate(const char *fn){
  
  ofstream ofOut;
      
  try {

    ofOut.open(fn);
    if(!ofOut)
      throw std::ios::failure("Error opening file ");
    
    
    ofOut << "# == EcH2O-iso tracking configuration file v1.0 ==" << endl;
    ofOut << "# ----------------                ----------------" << endl;
    ofOut << "# " << endl << "Units (inputs and outputs): " << endl;
    ofOut << "# - Deuterium ratios (dD):   permille" << endl;
    ofOut << "# - Oxygen 18 ratios (d18O): permille" << endl;
    ofOut << "# - Water age:               days" << endl << endl;
    
    ofOut << "## Boolean switches" << endl;
    ofOut << "water_dD = 1 # Deuterium tracking" << endl;
    ofOut << "water_d18O = 0 # Oxygen-18 tracking" << endl;
    ofOut << "water_Age = 1 # Age tracking" << endl;
    ofOut << "# Isotopic fractionation from soil evaporation" << endl;
    ofOut << "water_frac = 1" << endl;
    ofOut << "# Last-In-First-Out (LIFO) option: if activated, infiltrated water mixes in topsoil only after evaporation" << endl;
    ofOut << "water_lifo = 0" << endl << endl;
    
    ofOut << "## Toggles switches (only used of water_frac = 1)" << endl;
    ofOut << "# Surface relative humidity - taking into account air space between pores" << endl;
    ofOut << "# 0--> soilRH=1, 1--> soilRH follows Lee and Pielke 1992 (consistent with the evaporation routine)"<< endl;
    ofOut << "# 2--> soilRH follows Sorderberg et al. (2012)" << endl;
    ofOut << "Fractionation_surface_relhum = 1" << endl; 
    ofOut << "# Turbulent factor in kinetic fractionation (n)" << endl;
    ofOut << "# 0--> n=1, 1--> n depends on soil water content, following Mathieu and Bariac (1996)" << endl;
    ofOut << "Fractionation_turbulent_factor = 1" << endl << endl;
    
    ofOut << "# -- Inputs files (only necessary if the corresponding switch is =1)" << endl;
    ofOut << "#" << endl;
    ofOut << "# Climate input for isotopes" << endl;
    ofOut << "# bin files to be contained in folder pointed by Clim_Maps_Folder (see main config file)" << endl;
    ofOut << "dD_precip = d2H.bin" << endl;
    ofOut << "d18O_precip = d18O.bin" << endl;
    ofOut << "#" << endl;
    ofOut << "# Initial states: " << endl;
    ofOut << "# map files to be contained in folder pointed by Maps_Folder (see main config file)" << endl;
    ofOut << "#" << endl;
    ofOut << "init_dD_snowpack = dD_snowpack.map" << endl;
    ofOut << "init_dD_surface = dD_surface.map" << endl;
    ofOut << "init_dD_soil1 = dD_soilL1.map" << endl;
    ofOut << "init_dD_soil2 = dD_soilL2.map" << endl;
    ofOut << "init_dD_soil3 = dD_soilL3.map" << endl;
    ofOut << "init_dD_groundwater = dD_groundwater.map" << endl << endl ;

    ofOut << "init_d18O_snowpack = d18O_snowpack.map" << endl;
    ofOut << "init_d18O_surface = d18O_surface.map" << endl;
    ofOut << "init_d18O_soil1 = d18O_soilL1.map" << endl;
    ofOut << "init_d18O_soil2 = d18O_soilL2.map" << endl;
    ofOut << "init_d18O_soil3 = d18O_soilL3.map" << endl;
    ofOut << "init_d18O_groundwater = d18O_groundwater.map" << endl << endl;

    ofOut << "init_Age_snowpack = Age_snowpack.map" << endl;
    ofOut << "init_Age_surface = Age_surface.map" << endl;
    ofOut << "init_Age_soil1 = Age_soilL1.map" << endl;
    ofOut << "init_Age_soil2 = Age_soilL2.map" << endl;
    ofOut << "init_Age_soil3 = Age_soilL3.map" << endl;
    ofOut << "init_Age_groundwater = Age_groundwater.map" << endl << endl;

    ofOut << "#   " << endl;
    ofOut << "#Report map section " << endl;
    ofOut << "#   " << endl << endl ;
    ofOut << "Rep_dDprecip = 0" << endl;
    ofOut << "#Rep_dDcanopy = 0" << endl;
    ofOut << "Rep_dDsnowpack = 0" << endl;
    ofOut << "Rep_dDsurface = 0" << endl;
    ofOut << "Rep_dDsoil1 = 0" << endl;
    ofOut << "Rep_dDsoil2 = 0" << endl;
    ofOut << "Rep_dDsoilUp = 0" << endl;
    ofOut << "Rep_dDsoil3 = 0" << endl;
    ofOut << "Rep_dDsoilAv = 0" << endl;
    ofOut << "Rep_dDgroundwater = 0" << endl;
    ofOut << "Rep_dDevapS = 0" << endl;
    ofOut << "Rep_dDevapS_sum = 0" << endl;
    ofOut << "Rep_dDevapI = 0" << endl;
    ofOut << "Rep_dDevapI_sum = 0" << endl;
    ofOut << "Rep_dDevapT = 0" << endl;
    ofOut << "Rep_dDevapT_sum = 0" << endl << endl;

    ofOut << "Rep_d18Oprecip = 0" << endl;
    ofOut << "#Rep_d18Ocanopy = 0" << endl;
    ofOut << "Rep_d18Osnowpack = 0" << endl;
    ofOut << "Rep_d18Osurface = 0" << endl;
    ofOut << "Rep_d18Osoil1 = 0" << endl;
    ofOut << "Rep_d18Osoil2 = 0" << endl;
    ofOut << "Rep_d18OsoilUp = 0" << endl;
    ofOut << "Rep_d18Osoil3 = 0" << endl;
    ofOut << "Rep_d18OsoilAv = 0" << endl;
    ofOut << "Rep_d18Ogroundwater = 0" << endl;
    ofOut << "Rep_d18OevapS = 0" << endl;
    ofOut << "Rep_d18OevapS_sum = 0" << endl;
    ofOut << "Rep_d18OevapI = 0" << endl;
    ofOut << "Rep_d18OevapI_sum = 0" << endl;
    ofOut << "Rep_d18OevapT = 0" << endl;
    ofOut << "Rep_d18OevapT_sum = 0" << endl << endl;

    ofOut << "#Rep_Agecanopy = 0" << endl;
    ofOut << "Rep_Agesnowpack = 0" << endl;
    ofOut << "Rep_Agesurface = 0" << endl;
    ofOut << "Rep_Agesoil1 = 0" << endl;
    ofOut << "Rep_Agesoil2 = 0" << endl;
    ofOut << "Rep_AgesoilUp = 0" << endl;
    ofOut << "Rep_Agesoil3 = 0" << endl;
    ofOut << "Rep_AgesoilAv = 0" << endl;
    ofOut << "Rep_Agegroundwater = 0" << endl;
    ofOut << "Rep_AgeevapS = 0" << endl;
    ofOut << "Rep_AgeevapS_sum = 0" << endl;
    ofOut << "Rep_AgeevapI = 0" << endl;
    ofOut << "Rep_AgeevapI_sum = 0" << endl;
    ofOut << "Rep_AgeevapT = 0" << endl;
    ofOut << "Rep_AgeevapT_sum = 0" << endl << endl;

    ofOut << "#   " << endl;
    ofOut << "#Report time series section " << endl;
    ofOut << "#(locations specified in TS_mask map, see main config file)" << endl;
    ofOut << "#   " << endl << endl;

    ofOut << "# -- Report time series" << endl;
    ofOut << "Ts_dDprecip = 0" << endl;
    ofOut << "#Ts_dDcanopy = 0" << endl;
    ofOut << "Ts_dDsnowpack = 0" << endl;
    ofOut << "Ts_dDsurface = 1" << endl;
    ofOut << "Ts_dDsoil1 = 1" << endl;
    ofOut << "Ts_dDsoil2 = 1" << endl;
    ofOut << "Ts_dDsoilUp = 0" << endl;
    ofOut << "Ts_dDsoil3 = 0" << endl;
    ofOut << "Ts_dDsoilAv = 0" << endl;
    ofOut << "Ts_dDgroundwater = 1" << endl;
    ofOut << "Ts_dDevapS = 0" << endl;
    ofOut << "Ts_dDevapS_sum = 1" << endl;
    ofOut << "Ts_dDevapI = 0" << endl;
    ofOut << "Ts_dDevapI_sum = 0" << endl;
    ofOut << "Ts_dDevapT = 1" << endl;
    ofOut << "Ts_dDevapT_sum = 0" << endl << endl;

    ofOut << "Ts_d18Oprecip = 0" << endl;
    ofOut << "#Ts_d18Ocanopy = 0" << endl;
    ofOut << "Ts_d18Osnowpack = 0 " << endl;
    ofOut << "Ts_d18Osurface = 1" << endl;
    ofOut << "Ts_d18Osoil1 = 1" << endl;
    ofOut << "Ts_d18Osoil2 = 1" << endl;
    ofOut << "Ts_d18OsoilUp = 0" << endl;
    ofOut << "Ts_d18Osoil3 = 0" << endl;
    ofOut << "Ts_d18OsoilAv = 0" << endl;
    ofOut << "Ts_d18Ogroundwater = 1" << endl;
    ofOut << "Ts_d18OevapS = 0" << endl;
    ofOut << "Ts_d18OevapS_sum = 1" << endl;
    ofOut << "Ts_d18OevapI = 0" << endl;
    ofOut << "Ts_d18OevapI_sum = 0" << endl;
    ofOut << "Ts_d18OevapT = 1" << endl;
    ofOut << "Ts_d18OevapT_sum = 0" << endl << endl;

    ofOut << "#Ts_Agecanopy = 0" << endl;
    ofOut << "Ts_Agesnowpack = 1" << endl;
    ofOut << "Ts_Agesurface = 1" << endl;
    ofOut << "Ts_Agesoil1 = 1" << endl;
    ofOut << "Ts_Agesoil2 = 1" << endl;
    ofOut << "Ts_AgesoilUp = 0" << endl;
    ofOut << "Ts_Agesoil3 = 0" << endl;
    ofOut << "Ts_AgesoilAv = 0" << endl;
    ofOut << "Ts_Agegroundwater = 1" << endl;
    ofOut << "Ts_AgeevapS = 0" << endl;
    ofOut << "Ts_AgeevapS_sum = 0" << endl;
    ofOut << "Ts_AgeevapI = 1" << endl;
    ofOut << "Ts_AgeevapI_sum = 0" << endl;
    ofOut << "Ts_AgeevapT = 0" << endl;
    ofOut << "Ts_AgeevapT_sum = 1" << endl << endl;


   if (ofOut)
	   ofOut.close();
}
catch(const std::exception &e){
	cout << "Failure writing configuration template file with  " << e.what() << endl;
	exit(EXIT_FAILURE);
}
}

