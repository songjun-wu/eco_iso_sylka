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
 * ReadConfigTrck.cpp
 *
 *  Created on: Feb 28, 2017
 *      Author: Sylvain Kuppel
 *
 *      Reads the configuration file for tracking (default name 'configTrck.ini')
 *      and places the file names and control data in the Control object
 */
#include <stdexcept>   // for exception, runtime_error, out_of_range
#include <iostream>
#include <sys/stat.h>
#include <stdlib.h>
#include "ConfigFile.h"
#include "InitConf.h"
using namespace std;

int Control::ReadConfigTrck(string confilename /*= "configTrck.ini"*/)
{

	struct stat info; //needed to check the status of the folders

	try{
		ConfigFile ConfigTrck(confilename);

		sw_dD = ConfigTrck.read<bool>("water_dD");
		sw_d18O = ConfigTrck.read<bool>("water_d18O");
		sw_frac = ConfigTrck.read<bool>("water_frac");
		sw_Age = ConfigTrck.read<bool>("water_Age");
		sw_lifo = ConfigTrck.read<bool>("water_lifo");

		if(sw_frac){
		  toggle_hs = ConfigTrck.read<bool>("Fractionation_surface_relhum");
		  toggle_n = ConfigTrck.read<bool>("Fractionation_turbulent_factor");
		}
		// Put here because _FluxL1toSrf is calculated only if tracking is active
		Rep_SrftoL1 = ConfigTrck.read<bool>("Report_Infiltration");
		Rep_L1toSrf = ConfigTrck.read<bool>("Report_Return_Flow_Surface");
		Rep_LattoSrf = ConfigTrck.read<bool>("Report_Overland_Inflow");
		Rep_LattoGW = ConfigTrck.read<bool>("Report_Groundwater_Inflow");
		Rep_SrftoLat = ConfigTrck.read<bool>("Report_Overland_Outflow");
		Rep_LattoChn = ConfigTrck.read<bool>("Report_Stream_Inflow");
		Rep_SrftoL1acc = ConfigTrck.read<bool>("Report_Infiltration_acc");
		Rep_L1toSrfacc = ConfigTrck.read<bool>("Report_Return_Flow_Surface_acc");
		Rep_LattoSrfacc = ConfigTrck.read<bool>("Report_Overland_Inflow_acc");
		Rep_LattoGWacc = ConfigTrck.read<bool>("Report_Groundwater_Inflow_acc");
		Rep_SrftoLatacc = ConfigTrck.read<bool>("Report_Overland_Outflow_acc");
		Rep_LattoChnacc = ConfigTrck.read<bool>("Report_Stream_Inflow_acc");

		RepTs_SrftoL1 = ConfigTrck.read<bool>("Ts_Infiltration");
		RepTs_L1toSrf = ConfigTrck.read<bool>("Ts_Return_Flow_Surface");
		RepTs_LattoSrf = ConfigTrck.read<bool>("Ts_Overland_Inflow");
		RepTs_LattoGW = ConfigTrck.read<bool>("Ts_Groundwater_Inflow");
		RepTs_SrftoLat = ConfigTrck.read<bool>("Ts_Overland_Outflow");
		RepTs_LattoChn = ConfigTrck.read<bool>("Ts_Stream_Inflow");
		RepTs_SrftoL1acc = ConfigTrck.read<bool>("Ts_Infiltration_acc");
		RepTs_L1toSrfacc = ConfigTrck.read<bool>("Ts_Return_Flow_Surface_acc");
		RepTs_LattoSrfacc = ConfigTrck.read<bool>("Ts_Overland_Inflow_acc");
		RepTs_LattoGWacc = ConfigTrck.read<bool>("Ts_Groundwater_Inflow_acc");
		RepTs_SrftoLatacc = ConfigTrck.read<bool>("Ts_Overland_Outflow_acc");
		RepTs_LattoChnacc = ConfigTrck.read<bool>("Ts_Stream_Inflow_acc");

		if(sw_dD){

			// Precipitation input
			ConfigTrck.readInto(fn_dDprecip, "dD_precip");
			// Initial values
			//ConfigTrck.readInto(fn_dDcanopy, "init_dD_canopy");
			ConfigTrck.readInto(fn_dDsnowpack, "init_dD_snowpack");
			ConfigTrck.readInto(fn_dDsurface, "init_dD_surface");
			ConfigTrck.readInto(fn_dDsoil1, "init_dD_soil1");
			ConfigTrck.readInto(fn_dDsoil2, "init_dD_soil2");
			ConfigTrck.readInto(fn_dDsoil3, "init_dD_soil3");
			ConfigTrck.readInto(fn_dDgroundwater, "init_dD_groundwater");
			//			ConfigTrck.readInto(fn_dDchannel, "init_dD_channel");
			// Report maps
			Rep_dDprecip = ConfigTrck.read<bool>("Rep_dDprecip");
			//Rep_dDcanopy = ConfigTrck.read<bool>("Rep_dDcanopy");
			Rep_dDsnowpack = ConfigTrck.read<bool>("Rep_dDsnowpack");
			Rep_dDsurface = ConfigTrck.read<bool>("Rep_dDsurface");
			Rep_dDsoil1 = ConfigTrck.read<bool>("Rep_dDsoil1");
			Rep_dDsoil2 = ConfigTrck.read<bool>("Rep_dDsoil2");
			Rep_dDsoilUp = ConfigTrck.read<bool>("Rep_dDsoilUp");
			Rep_dDsoil3 = ConfigTrck.read<bool>("Rep_dDsoil3");
			//Rep_dDsoilAv = ConfigTrck.read<bool>("Rep_dDsoilAv");
			Rep_dDgroundwater = ConfigTrck.read<bool>("Rep_dDgroundwater");
			Rep_dDevapS = ConfigTrck.read<bool>("Rep_dDevapS");
			Rep_dDevapS_sum = ConfigTrck.read<bool>("Rep_dDevapS_sum");
			Rep_dDevapI = ConfigTrck.read<bool>("Rep_dDevapI");
			Rep_dDevapI_sum = ConfigTrck.read<bool>("Rep_dDevapI_sum");
			Rep_dDevapT = ConfigTrck.read<bool>("Rep_dDevapT");
			Rep_dDevapT_sum = ConfigTrck.read<bool>("Rep_dDevapT_sum");
			// Report time series
			RepTs_dDprecip = ConfigTrck.read<bool>("Ts_dDprecip");
			//RepTs_dDcanopy = ConfigTrck.read<bool>("Ts_dDcanopy");
			RepTs_dDsnowpack = ConfigTrck.read<bool>("Ts_dDsnowpack");
			RepTs_dDsurface = ConfigTrck.read<bool>("Ts_dDsurface");
			RepTs_dDsoil1 = ConfigTrck.read<bool>("Ts_dDsoil1");
			RepTs_dDsoil2 = ConfigTrck.read<bool>("Ts_dDsoil2");
			RepTs_dDsoilUp = ConfigTrck.read<bool>("Ts_dDsoilUp");
			RepTs_dDsoil3 = ConfigTrck.read<bool>("Ts_dDsoil3");
			//RepTs_dDsoilAv = ConfigTrck.read<bool>("Ts_dDsoilAv");
			RepTs_dDgroundwater = ConfigTrck.read<bool>("Ts_dDgroundwater");
			RepTs_dDevapS = ConfigTrck.read<bool>("Ts_dDevapS");
			RepTs_dDevapS_sum = ConfigTrck.read<bool>("Ts_dDevapS_sum");
			RepTs_dDevapI = ConfigTrck.read<bool>("Ts_dDevapI");
			RepTs_dDevapI_sum = ConfigTrck.read<bool>("Ts_dDevapI_sum");
			RepTs_dDevapT = ConfigTrck.read<bool>("Ts_dDevapT");
			RepTs_dDevapT_sum = ConfigTrck.read<bool>("Ts_dDevapT_sum");
		}

		if(sw_d18O){
			// Precipitation input
			ConfigTrck.readInto(fn_d18Oprecip, "d18O_precip");
			// Initial values
			//ConfigTrck.readInto(fn_d18Ocanopy, "init_d18O_canopy");
			ConfigTrck.readInto(fn_d18Osnowpack, "init_d18O_snowpack");
			ConfigTrck.readInto(fn_d18Osurface, "init_d18O_surface");
			ConfigTrck.readInto(fn_d18Osoil1, "init_d18O_soil1");
			ConfigTrck.readInto(fn_d18Osoil2, "init_d18O_soil2");
			ConfigTrck.readInto(fn_d18Osoil3, "init_d18O_soil3");
			ConfigTrck.readInto(fn_d18Ogroundwater, "init_d18O_groundwater");
			//			ConfigTrck.readInto(fn_d18Ochannel, "init_d18O_channel");
			// Report maps
			Rep_d18Oprecip = ConfigTrck.read<bool>("Rep_d18Oprecip");
			//Rep_d18Ocanopy = ConfigTrck.read<bool>("Rep_d18Ocanopy");
			Rep_d18Osnowpack = ConfigTrck.read<bool>("Rep_d18Osnowpack");
			Rep_d18Osurface = ConfigTrck.read<bool>("Rep_d18Osurface");
			Rep_d18Osoil1 = ConfigTrck.read<bool>("Rep_d18Osoil1");
			Rep_d18Osoil2 = ConfigTrck.read<bool>("Rep_d18Osoil2");
			Rep_d18OsoilUp = ConfigTrck.read<bool>("Rep_d18OsoilUp");
			Rep_d18Osoil3 = ConfigTrck.read<bool>("Rep_d18Osoil3");
			//Rep_d18OsoilAv = ConfigTrck.read<bool>("Rep_d18OsoilAv");
			Rep_d18Ogroundwater = ConfigTrck.read<bool>("Rep_d18Ogroundwater");
			Rep_d18OevapS = ConfigTrck.read<bool>("Rep_d18OevapS");
			Rep_d18OevapS_sum = ConfigTrck.read<bool>("Rep_d18OevapS_sum");
			Rep_d18OevapI = ConfigTrck.read<bool>("Rep_d18OevapI");
			Rep_d18OevapI_sum = ConfigTrck.read<bool>("Rep_d18OevapI_sum");
			Rep_d18OevapT = ConfigTrck.read<bool>("Rep_d18OevapT");
			Rep_d18OevapT_sum = ConfigTrck.read<bool>("Rep_d18OevapT_sum");
			// Report time series
			RepTs_d18Oprecip = ConfigTrck.read<bool>("Ts_d18Oprecip");
			//RepTs_d18Ocanopy = ConfigTrck.read<bool>("Ts_d18Ocanopy");
			RepTs_d18Osnowpack = ConfigTrck.read<bool>("Ts_d18Osnowpack");
			RepTs_d18Osurface = ConfigTrck.read<bool>("Ts_d18Osurface");
			RepTs_d18Osoil1 = ConfigTrck.read<bool>("Ts_d18Osoil1");
			RepTs_d18Osoil2 = ConfigTrck.read<bool>("Ts_d18Osoil2");
			RepTs_d18OsoilUp = ConfigTrck.read<bool>("Ts_d18OsoilUp");
			RepTs_d18Osoil3 = ConfigTrck.read<bool>("Ts_d18Osoil3");
			//RepTs_d18OsoilAv = ConfigTrck.read<bool>("Ts_d18OsoilAv");
			RepTs_d18Ogroundwater = ConfigTrck.read<bool>("Ts_d18Ogroundwater");
			RepTs_d18OevapS = ConfigTrck.read<bool>("Ts_d18OevapS");
			RepTs_d18OevapS_sum = ConfigTrck.read<bool>("Ts_d18OevapS_sum");
			RepTs_d18OevapI = ConfigTrck.read<bool>("Ts_d18OevapI");
			RepTs_d18OevapI_sum = ConfigTrck.read<bool>("Ts_d18OevapI_sum");
			RepTs_d18OevapT = ConfigTrck.read<bool>("Ts_d18OevapT");
			RepTs_d18OevapT_sum = ConfigTrck.read<bool>("Ts_d18OevapT_sum");
		}

		if(sw_Age){

			// Initial values
			//ConfigTrck.readInto(fn_Agecanopy, "init_Age_canopy");
			ConfigTrck.readInto(fn_Agesnowpack, "init_Age_snowpack");
			ConfigTrck.readInto(fn_Agesurface, "init_Age_surface");
			ConfigTrck.readInto(fn_Agesoil1, "init_Age_soil1");
			ConfigTrck.readInto(fn_Agesoil2, "init_Age_soil2");
			ConfigTrck.readInto(fn_Agesoil3, "init_Age_soil3");
			ConfigTrck.readInto(fn_Agegroundwater, "init_Age_groundwater");
			//ConfigTrck.readInto(fn_Agechannel, "init_Age_channel");
			// Report maps
			//Rep_Agecanopy = ConfigTrck.read<bool>("Rep_Agecanopy");
			Rep_Agesnowpack = ConfigTrck.read<bool>("Rep_Agesnowpack");
			Rep_Agesurface = ConfigTrck.read<bool>("Rep_Agesurface");
			Rep_Agesoil1 = ConfigTrck.read<bool>("Rep_Agesoil1");
			Rep_Agesoil2 = ConfigTrck.read<bool>("Rep_Agesoil2");
			Rep_AgesoilUp = ConfigTrck.read<bool>("Rep_AgesoilUp");
			Rep_Agesoil3 = ConfigTrck.read<bool>("Rep_Agesoil3");
			//Rep_AgesoilAv = ConfigTrck.read<bool>("Rep_AgesoilAv");
			Rep_Agegroundwater = ConfigTrck.read<bool>("Rep_Agegroundwater");
			Rep_AgeevapS = ConfigTrck.read<bool>("Rep_AgeevapS");
			Rep_AgeevapS_sum = ConfigTrck.read<bool>("Rep_AgeevapS_sum");
			Rep_AgeevapI = ConfigTrck.read<bool>("Rep_AgeevapI");
			Rep_AgeevapI_sum = ConfigTrck.read<bool>("Rep_AgeevapI_sum");
			Rep_AgeevapT = ConfigTrck.read<bool>("Rep_AgeevapT");
			Rep_AgeevapT_sum = ConfigTrck.read<bool>("Rep_AgeevapT_sum");
			// Report time series
			//RepTs_Agecanopy = ConfigTrck.read<bool>("Ts_Agecanopy");
			RepTs_Agesnowpack = ConfigTrck.read<bool>("Ts_Agesnowpack");
			RepTs_Agesurface = ConfigTrck.read<bool>("Ts_Agesurface");
			RepTs_Agesoil1 = ConfigTrck.read<bool>("Ts_Agesoil1");
			RepTs_Agesoil2 = ConfigTrck.read<bool>("Ts_Agesoil2");
			RepTs_AgesoilUp = ConfigTrck.read<bool>("Ts_AgesoilUp");
			RepTs_Agesoil3 = ConfigTrck.read<bool>("Ts_Agesoil3");
			//RepTs_AgesoilAv = ConfigTrck.read<bool>("Ts_AgesoilAv");
			RepTs_Agegroundwater = ConfigTrck.read<bool>("Ts_Agegroundwater");
			RepTs_AgeevapS = ConfigTrck.read<bool>("Ts_AgeevapS");
			RepTs_AgeevapS_sum = ConfigTrck.read<bool>("Ts_AgeevapS_sum");
			RepTs_AgeevapI = ConfigTrck.read<bool>("Ts_AgeevapI");
			RepTs_AgeevapI_sum = ConfigTrck.read<bool>("Ts_AgeevapI_sum");
			RepTs_AgeevapT = ConfigTrck.read<bool>("Ts_AgeevapT");
			RepTs_AgeevapT_sum = ConfigTrck.read<bool>("Ts_AgeevapT_sum");
		}
	}
	catch(ConfigFile::file_not_found &fn){
		cout << "Tracking file " << fn.filename << " not found\n";
		exit(EXIT_SUCCESS);
	}
	catch(ConfigFile::key_not_found &fn){
		cout << "Tracking key " << fn.key << " not found\n";
		exit(EXIT_SUCCESS);
	}
	catch(std::exception &e){
		cout << e.what();
		exit(EXIT_SUCCESS);
	}



	return 1;
}
