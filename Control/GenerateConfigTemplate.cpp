/*
 * GenerateConfigTemplate.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: marcomaneta
 */

#include  <fstream>
#include <unistd.h>

#include "Sativa.h"

void GenerateConfigTemplate(const char *fn){

	ofstream ofOut;

try{

		if (access(fn, F_OK) != -1) {

			cout << "File exists. Do you want to overwrite? (y, n):  " << endl;
			char c;
			cin.get(c);
			switch (c) {
			case 'y':
				break;
			case 'n':
				exit(EXIT_SUCCESS);
				break;
			default:
				cout << "Not a valid option. Bye" << endl;
				exit(EXIT_SUCCESS);

			}
		}

		ofOut.open(fn);
		if(!ofOut)
			throw std::ios::failure("Error opening file ");





	ofOut << "#ECH2O configuration file v1.6b" << std::endl << std::endl;

    ofOut << "#" << endl << "#Folder section" << endl << "#" << endl << endl;

    ofOut << "Maps_Folder = ./Spatial" << endl;
    ofOut << "Clim_Maps_Folder = ./Climate" << endl;
    ofOut << "Output_Folder = ./Results" << endl << endl;

    ofOut << "MapTypes = csf" << endl;
    ofOut << "Species_State_Variable_Input_Method = tables # maps or tables" << endl << endl;

    ofOut << "#" << endl << "# Options section" << endl << "#" << endl << endl;

    ofOut << "# Boolean switches" << endl;
    ofOut << "Reinfiltration = 1" << endl;
    ofOut << "Channel = 1" << endl << endl;

    ofOut << "# TOGGLE SWITCHES:" << endl;
    ofOut << "# Aerodynamic resistance choices: " << endl;
    ofOut << "# 0 = Penman Monteith option " << endl;
    ofOut << "# 1 = Thom and Oliver 1977 " << endl;
    ofOut << "Aerodyn_resist_opt = 0 " << endl << endl;

    ofOut << "# Soil resistance to vapor diffusion choices: " << endl;
    ofOut << "# 0 = No resistance: " << endl;
    ofOut << "# 1 = Passerat de Silans et al 1989 " << endl;
    ofOut << "# 2 = Thom and Oliver 1977 " << endl;
    ofOut << "# 3 = Sakaguchi and Zeng 2009 " << endl;
    ofOut << "Soil_resistance_opt = 2 " << endl << endl;

    ofOut << "#" << endl << "# Time variables section" << endl << "#" << endl;
    ofOut << "Simul_start = 0 # always 0" << endl;
    ofOut << "Simul_end = 31536000 # seconds" << endl;
    ofOut << "Simul_tstep = 86400 # seconds" << endl;
    ofOut << "Clim_input_tstep = 86400  " << endl;
    ofOut << "Report_interval = 86400" << endl << endl;

    ofOut << "#" << endl << "# Base map section" << endl << "#" << endl;
    ofOut << "DEM = DEM.map" << endl;
    ofOut << "ClimateZones = ClimZones.map" << endl;
    ofOut << "ForestPatches = patches.map" << endl << endl;

    ofOut << "#" << endl;
    ofOut << "# Climate input information" << endl;
    ofOut << "# Maps in this section to be contained in folder pointed by Clim_Maps_Folder" << endl;
    ofOut << "#" << endl;
    ofOut << "Snow_rain_temp_threshold = 2 " << "# Snow to rain temperatures threshold in degC" << endl;
    ofOut << "Isohyet_map = isohyet.map" << "# Precipitation multiplier map"<< endl;
    ofOut << "Precipitation = Precip.bin" << "# Precip rate in meters/second"<< endl;
    ofOut << "AirTemperature = Tavg.bin" << "# Average air temperature in degC" << endl;
    ofOut << "MaxAirTemp = Tmax.bin" << "# Maximum air temperature in degC" << endl;
    ofOut << "MinAirTemp = Tmin.bin" << "# Minimum air temperature in degC"<< endl;
    ofOut << "RelativeHumidity = RH.bin" << "# air relative humidity in kPa/kPa"<< endl;
    ofOut << "WindSpeed = windspeed.bin" << "# Wind speed in meters/second" << endl;
    ofOut << "IncomingLongWave = Ldown.bin" << "# Downwelling longwave radiation in W/sq.meter" << endl;
    ofOut << "IncomingShortWave = Sdown.bin" << "# Solar radiation in W/sq.meter" << endl << endl;

    ofOut << "#" << endl;
    ofOut << "# Spatial input information" << endl;
    ofOut << "# Maps below this lineto be contained in folder pointed by Maps_Folder" << endl;
    ofOut << "#" << endl;

    ofOut << "Albedo = albedo.map" << endl;
    ofOut << "Surface_emissivity = emissivity.map" << endl;
    ofOut << "Dry_Soil_Heat_Capacity = soilheatcap.map" << endl;
    ofOut << "Dry_Soil_Therm_Cond = soilthermalK.map" << endl;
    ofOut << "Damping_depth = dampdepth.map" << endl;
    ofOut << "Temp_at_damp_depth = temp_damp.map" << endl;
    ofOut << "Snow_Melt_Coeff = snowmeltCoeff.map" << endl << endl;

    ofOut << "#" << endl << "# Drainage network" << endl << "#" << endl;
    ofOut << "local_drain_direc = ldd.map" << endl;
    ofOut << "channel_width = chanwidth.map" << endl;
    ofOut << "channel_gw_transfer_param = chanparam.map" << endl;
    ofOut << "mannings_n = chanmanningn.map" << endl;

    ofOut << "#   " << endl;
    ofOut << "# Hydrologic Initial Conditions  " << endl;
    ofOut << "# Forest Initial states are included as maps or tables" << endl;
    ofOut << "#   " << endl;
    ofOut << "Streamflow = streamflow.map " << endl;
    ofOut << "snow_water_equivalent = swe.map " << endl;
    ofOut << "Soil_moisture_1 = soilmoist.map " << endl;
    ofOut << "Soil_moisture_2 = soilmoist.map " << endl;
    ofOut << "Soil_moisture_3 = soilmoist.map " << endl;
    ofOut << "Soil_temperature = soiltemp.map " << endl << endl;

    ofOut << "#   " << endl;
    ofOut << "#Soil parameters  " << endl;
    ofOut << "#   " << endl;
    ofOut << "Slope = slope.map " << endl;
    ofOut << "Horiz_Hydraulic_Conductivity = Keff.map " << endl;
    ofOut << "Vert_Horz_Anis_ratio = KvKh.map " << endl;
    ofOut << "Terrain_Random_Roughness = randrough.map " << endl;
    ofOut << "Porosity = poros.map " << endl;
    ofOut << "Air_entry_pressure = psi_ae.map " << endl;
    ofOut << "Brooks_Corey_lambda = BClambda.map " << endl;
    ofOut << "Residual_soil_moisture = theta_r.map " << endl;
    ofOut << "Soil_depth = soildepth.map " << endl;
    ofOut << "Depth_soil_layer_1 = depth_soil1.map " << endl;
    ofOut << "Depth_soil_layer_2 = depth_soil2.map " << endl;
    ofOut << "Veget_water_use_param1 = Wc.map " << endl;
    ofOut << "Veget_water_use_param2 = Wp.map " << endl;
    ofOut << "Fraction_roots_soil_layer_1 = rootfrac1.map " << endl;
    ofOut << "Fraction_roots_soil_layer_2 = rootfrac2.map " << endl;
    ofOut << "Soil_bedrock_leakance = leakance.map " << endl << endl;

    ofOut << "#   " << endl;
    ofOut << "#Forest Parameters and initial states " << endl;
    ofOut << "#   " << endl;
    ofOut << "Number_of_Species = 1 " << endl;
    ofOut << "Species_Parameters = SpeciesParams.tab " << endl;
    ofOut << "#Tables below are only needed if Species_State_Variable_Input_Method = tables " << endl;
    ofOut << "Species_Proportion_Table = SpecsProp.tab " << endl;
    ofOut << "Species_StemDensity_Table = SpecsStemDens.tab " << endl;
    ofOut << "Species_LAI_Table = SpecsLAI.tab " << endl;
    ofOut << "Species_AGE_Table = SpecsAge.tab " << endl;
    ofOut << "Species_BasalArea_Table = SpeciesBasalArea.tab " << endl;
    ofOut << "Species_Height_table = SpeciesHeight.tab " << endl;
    ofOut << "Species_RootMass_table = SpecsRootDensity.tab " << endl << endl;

    ofOut << "#   " << endl;
    ofOut << "#Report map section " << endl;
    ofOut << "#   " << endl;
    ofOut << "Report_Long_Rad_Down = 0 " << endl;
    ofOut << "Report_Short_Rad_Down = 0 " << endl;
    ofOut << "Report_Precip = 0 " << endl;
    ofOut << "Report_Rel_Humidity = 0 " << endl;
    ofOut << "Report_Wind_Speed = 0 " << endl;
    ofOut << "Report_AvgAir_Temperature = 0 " << endl;
    ofOut << "Report_MinAir_Temperature = 0 " << endl;
    ofOut << "Report_MaxAir_Temperature = 0 " << endl << endl;

    ofOut << "Report_SWE = 1 " << endl;
    ofOut << "Report_Infilt_Cap = 0 " << endl;
    ofOut << "Report_Streamflow = 1 " << endl;
    ofOut << "Report_Soil_Water_Content_Average = 1 " << endl;
    ofOut << "Report_Soil_Water_Content_L1 = 1 " << endl;
    ofOut << "Report_Soil_Water_Content_L2 = 1 " << endl;
    ofOut << "Report_Soil_Water_Content_L3 = 1 " << endl;
    ofOut << "Report_Soil_Sat_Deficit = 1 " << endl;
    ofOut << "Report_Ground_Water = 0 " << endl;
    ofOut << "Report_Soil_ETP = 1 " << endl;
    ofOut << "Report_Soil_Net_Rad = 0 " << endl;
    ofOut << "Report_Soil_LE = 0 " << endl;
    ofOut << "Report_Sens_Heat = 0 " << endl;
    ofOut << "Report_Grnd_Heat = 0 " << endl;
    ofOut << "Report_Snow_Heat = 0 " << endl;
    ofOut << "Report_Soil_Temperature = 1 " << endl;
    ofOut << "Report_Skin_Temperature = 1 " << endl << endl;

    ofOut << "Report_Veget_frac = 1 " << endl;
    ofOut << "Report_Stem_Density = 1 " << endl;
    ofOut << "Report_Leaf_Area_Index = 1 " << endl;
    ofOut << "Report_Stand_Age = 0 " << endl;
    ofOut << "Report_Canopy_Conductance = 0 " << endl;
    ofOut << "Report_GPP = 0 " << endl;
    ofOut << "Report_NPP = 1 " << endl;
    ofOut << "Report_Basal_Area = 1 " << endl;
    ofOut << "Report_Tree_Height = 1 " << endl;
    ofOut << "Report_Root_Mass = 1 " << endl;
    ofOut << "Report_Canopy_Temp = 0 " << endl;
    ofOut << "Report_Canopy_NetR = 0 " << endl;
    ofOut << "Report_Canopy_LE = 0 " << endl;
    ofOut << "Report_Canopy_Sens_Heat = 0 " << endl;
    ofOut << "Report_Canopy_Water_Stor = 0 " << endl;
    ofOut << "Report_Transpiration = 1 " << endl;

    ofOut << "#   " << endl;
    ofOut << "#Report time series section " << endl;
    ofOut << "#   " << endl << endl;

    ofOut << "Ts_OutletDischarge = 1 " << endl;

    ofOut << "TS_mask = Tsmask.map " << endl;

    ofOut << "Ts_Long_Rad_Down = 0 " << endl;
    ofOut << "Ts_Short_Rad_Down = 0 " << endl;
    ofOut << "Ts_Precip = 0 " << endl;
    ofOut << "Ts_Rel_Humidity = 0 " << endl;
    ofOut << "Ts_Wind_Speed = 0 " << endl;
    ofOut << "Ts_AvgAir_Temperature = 0 " << endl;
    ofOut << "Ts_MinAir_Temperature = 0 " << endl;
    ofOut << "Ts_MaxAir_Temperature = 0 " << endl;
    ofOut << "Ts_SWE = 1 " << endl;
    ofOut << "Ts_Infilt_Cap = 0 " << endl;
    ofOut << "Ts_Streamflow = 1 " << endl;
    ofOut << "Ts_Soil_Water_Content_Average = 1 " << endl;
    ofOut << "Ts_Soil_Water_Content_L1 = 1 " << endl;
    ofOut << "Ts_Soil_Water_Content_L2 = 1 " << endl;
    ofOut << "Ts_Soil_Water_Content_L3 = 1 " << endl;
    ofOut << "Ts_Soil_Sat_Deficit = 0 " << endl;
    ofOut << "Ts_Soil_ETP = 1 " << endl;
    ofOut << "Ts_Soil_Net_Rad = 0 " << endl;
    ofOut << "Ts_Soil_LE = 1 " << endl;
    ofOut << "Ts_Sens_Heat = 0 " << endl;
    ofOut << "Ts_Grnd_Heat = 0 " << endl;
    ofOut << "Ts_Snow_Heat = 0 " << endl;
    ofOut << "Ts_Soil_Temperature = 0 " << endl;
    ofOut << "Ts_Skin_Temperature = 0 " << endl;
    ofOut << "Ts_Veget_frac = 0 " << endl;
    ofOut << "Ts_Stem_Density = 0 " << endl;
    ofOut << "Ts_Leaf_Area_Index = 1 " << endl;
    ofOut << "Ts_Stand_Age = 0 " << endl;
    ofOut << "Ts_Canopy_Conductance = 1 " << endl;
    ofOut << "Ts_GPP = 0 " << endl;
    ofOut << "Ts_NPP = 1 " << endl;
    ofOut << "Ts_Basal_Area = 0 " << endl;
    ofOut << "Ts_Tree_Height = 0 " << endl;
    ofOut << "Ts_Root_Mass = 0 " << endl;
    ofOut << "Ts_Canopy_Temp = 0 " << endl;
    ofOut << "Ts_Canopy_NetR = 0 " << endl;
    ofOut << "Ts_Canopy_LE = 0 " << endl;
    ofOut << "Ts_Canopy_Sens_Heat = 0 " << endl;
    ofOut << "Ts_Canopy_Water_Stor = 0 " << endl;
    ofOut << "Ts_Transpiration = 1 " << endl;



   if (ofOut)
	   ofOut.close();
}
catch(const std::exception &e){
	cout << "Failure writing configuration template file with  " << e.what() << endl;
	exit(EXIT_FAILURE);
}
}

