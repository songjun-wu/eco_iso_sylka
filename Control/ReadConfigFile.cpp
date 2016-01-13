/*
 * initConf.cpp
 *
 *  Created on: Oct 13, 2009
 *      Author: Marco Maneta
 *
 *      Reads the configuration file (default name 'config.ini')
 *      and places the file names and control data in the Control object
 */
#include <stdexcept>   // for exception, runtime_error, out_of_range
#include <iostream>
#include <sys/stat.h>
#include <stdlib.h>
#include "ConfigFile.h"
#include "InitConf.h"
using namespace std;

int Control::ReadConfigFile(string confilename /*= "config.ini"*/)
{

	struct stat info; //needed to check the status of the folders

	try{
	ConfigFile Config(confilename);

	Config.readInto(path_BasinFolder, "Maps_Folder");
	//check for slash \ at the end of the path string and if there is none appends it
	if(path_BasinFolder.at(path_BasinFolder.length()-1) != '/')
		path_BasinFolder.append("/");
	if(stat(path_BasinFolder.c_str(), &info)!=0)
				throw std::runtime_error(string("Folder not found: ") + path_BasinFolder);

	Config.readInto(path_ClimMapsFolder, "Clim_Maps_Folder");
	if(path_ClimMapsFolder.at(path_ClimMapsFolder.length()-1) != '/')
		path_ClimMapsFolder.append("/");
	if(stat(path_ClimMapsFolder.c_str(), &info)!=0)
			throw std::runtime_error(string("Folder not found: ") + path_ClimMapsFolder);

	Config.readInto(path_ResultsFolder, "Output_Folder");
	if(path_ResultsFolder.at(path_ResultsFolder.length()-1) != '/')
		path_ResultsFolder.append("/");
	if(stat(path_ResultsFolder.c_str(), &info)!=0)
		throw std::runtime_error(string("Folder not found: ") + path_ResultsFolder);


	sw_reinfilt = Config.read<bool>("Reinfiltration");
	sw_channel = Config.read<bool>("Channel");

	//toggle_soil_water_profile = Config.read<int>("Soil_water_profile_opt");
	toggle_ra = Config.read<int>("Aerodyn_resist_opt");
	toggle_rs = Config.read<int>("Soil_resistance_opt");



	starttime = Config.read<float>("Simul_start");
	endtime = Config.read<float>("Simul_end");
	dt = Config.read<float>("Simul_tstep");
	BC_dt = Config.read<float>("Clim_input_tstep");
	report_times = Config.read<float>("Report_interval");

	if(report_times < dt){
		cout << "WARNING: Report time step less than simulation time step. Changing report time step to simulation time step" << endl;
		report_times = dt;
	}

	Config.readInto(MapType, "MapTypes" );
	Config.readInto(ForestStateVarsInputType, "Species_State_Variable_Input_Method");

	NumSpecs = Config.read<int>("Number_of_Species");

	Config.readInto(fn_dem, "DEM");
	Config.readInto(fn_climzones, "ClimateZones");
	Config.readInto(fn_patches, "ForestPatches");

	Config.readInto(fn_ksat, "Hydraulic_Conductivity");
	Config.readInto(fn_randrough, "Terrain_Random_Roughness");
	Config.readInto(fn_slope, "Slope");
	Config.readInto(fn_poros, "Porosity");
	Config.readInto(fn_psi_ae, "Air_entry_pressure");
	Config.readInto(fn_BClambda, "Brooks_Corey_lambda");
	Config.readInto(fn_theta_r, "Residual_soil_moisture");
	Config.readInto(fn_soildepth, "Soil_depth");
	Config.readInto(fn_paramWc, "Veget_water_use_param1");
	Config.readInto(fn_paramWp, "Veget_water_use_param2");
	Config.readInto(fn_snowCf, "Snow_Melt_Coeff");

	Config.readInto(fn_isohyet, "Isohyet_map");
	Config.readInto(fn_snow_rain_temp, "Snow_rain_temp_threshold");
	Config.readInto(fn_Ldown, "IncomingLongWave");
	Config.readInto(fn_Sdown, "IncomingShortWave");
	Config.readInto(fn_temp, "AirTemperature");
	Config.readInto(fn_maxTemp, "MaxAirTemp");
	Config.readInto(fn_minTemp, "MinAirTemp");
	Config.readInto(fn_precip, "Precipitation");
	Config.readInto(fn_rel_humid, "RelativeHumidity");
	Config.readInto(fn_wind_speed, "WindSpeed");

	Config.readInto(fn_ldd, "local_drain_direc");
	Config.readInto(fn_chwidth, "channel_width");
	Config.readInto(fn_chgwparam, "channel_gw_transfer_param");
	Config.readInto(fn_chmanningn, "mannings_n");

	/*Basin state variables section*/
	Config.readInto(fn_swe, "snow_water_equivalent");
	Config.readInto(fn_albedo, "Albedo");
	Config.readInto(fn_emiss, "Surface_emissivity");
	Config.readInto(fn_soilheatcap, "Dry_Soil_Heat_Capacity");
	Config.readInto(fn_soilthermcond, "Dry_Soil_Therm_Cond");
	Config.readInto(fn_dampdepth, "Damping_depth");
	Config.readInto(fn_tempdamp, "Temp_at_damp_depth");
	Config.readInto(fn_streamflow, "Streamflow");
	Config.readInto(fn_soilmoist, "Soil_moisture_1");

	Config.readInto(fn_depth_layer1, "Depth_soil_layer_1");
	Config.readInto(fn_depth_layer2, "Depth_soil_layer_2");
	Config.readInto(fn_root_fraction_lay1, "Fraction_roots_soil_layer_1");
	Config.readInto(fn_root_fraction_lay2, "Fraction_roots_soil_layer_2");
	Config.readInto(fn_soilmoist2, "Soil_moisture_2");
	Config.readInto(fn_soilmoist3, "Soil_moisture_3");
	Config.readInto(fn_bedrock_leak, "Soil_bedrock_leakance");

	Config.readInto(fn_soiltemp, "Soil_temperature");


	Config.readInto(fn_paramtable, "Species_Parameters");

	if(!ForestStateVarsInputType.compare("tables")){
		Config.readInto(fn_proptable, "Species_Proportion_Table");
		Config.readInto(fn_LAItable, "Species_LAI_Table");
		Config.readInto(fn_AGEtable, "Species_AGE_Table");
		Config.readInto(fn_BasalAreatable, "Species_BasalArea_Table");
		Config.readInto(fn_Heighttable, "Species_Height_table");
		Config.readInto(fn_RootMasstable, "Species_RootMass_table");
		Config.readInto(fn_StemDenstable, "Species_StemDensity_Table");
	}

	current_t_step = current_ts_count * dt;

	Rep_Long_Rad_Down = Config.read<bool>("Report_Long_Rad_Down");
	Rep_Short_Rad_Down = Config.read<bool>("Report_Short_Rad_Down");
	Rep_Precip = Config.read<bool>("Report_Precip");
	Rep_Rel_Humidity = Config.read<bool>("Report_Rel_Humidity");
	Rep_Wind_Speed = Config.read<bool>("Report_Wind_Speed");
	Rep_AvgAir_Temperature = Config.read<bool>("Report_AvgAir_Temperature");
	Rep_MinAir_Temperature = Config.read<bool>("Report_MinAir_Temperature");
	Rep_MaxAir_Temperature = Config.read<bool>("Report_MaxAir_Temperature");
	Rep_SWE = Config.read<bool>("Report_SWE");
	Rep_Infilt_Cap = Config.read<bool>("Report_Infilt_Cap");
	Rep_Streamflow = Config.read<bool>("Report_Streamflow");
	Rep_Soil_Water_Content_Average = Config.read<bool>("Report_Soil_Water_Content_Average");
	Rep_Soil_Water_Content_L1 = Config.read<bool>("Report_Soil_Water_Content_L1");
	Rep_Soil_Water_Content_L2 = Config.read<bool>("Report_Soil_Water_Content_L2");
	Rep_Soil_Water_Content_L3 = Config.read<bool>("Report_Soil_Water_Content_L3");
	Rep_Soil_Sat_Deficit = Config.read<bool>("Report_Soil_Sat_Deficit");
	Rep_GWater = Config.read<bool>("Report_Ground_Water");
	Rep_Soil_ETP = Config.read<bool>("Report_Soil_ETP");
	Rep_Soil_Net_Rad = Config.read<bool>("Report_Soil_Net_Rad");
	Rep_Soil_LE = Config.read<bool>("Report_Soil_LE");
	Rep_Sens_Heat = Config.read<bool>("Report_Sens_Heat");
	Rep_Grnd_Heat = Config.read<bool>("Report_Grnd_Heat");
	Rep_Snow_Heat = Config.read<bool>("Report_Snow_Heat");
	Rep_Soil_Temperature = Config.read<bool>("Report_Soil_Temperature");
	Rep_Skin_Temperature = Config.read<bool>("Report_Skin_Temperature");
	Rep_Veget_frac = Config.read<bool>("Report_Veget_frac");
	Rep_Stem_Density = Config.read<bool>("Report_Stem_Density");
	Rep_Leaf_Area_Index = Config.read<bool>("Report_Leaf_Area_Index");
	Rep_Stand_Age = Config.read<bool>("Report_Stand_Age");
	Rep_Canopy_Conductance = Config.read<bool>("Report_Canopy_Conductance");
	Rep_GPP = Config.read<bool>("Report_GPP");
	Rep_NPP = Config.read<bool>("Report_NPP");
	Rep_Basal_Area = Config.read<bool>("Report_Basal_Area");
	Rep_Tree_Height = Config.read<bool>("Report_Tree_Height");
	Rep_Root_Mass = Config.read<bool>("Report_Root_Mass");
	Rep_Canopy_Temp = Config.read<bool>("Report_Canopy_Temp");
	Rep_Canopy_NetR = Config.read<bool>("Report_Canopy_NetR");
	Rep_Canopy_LE = Config.read<bool>("Report_Canopy_LE");
	Rep_Canopy_Sens_Heat = Config.read<bool>("Report_Canopy_Sens_Heat");
	Rep_Canopy_Water_Stor = Config.read<bool>("Report_Canopy_Water_Stor");
	Rep_Transpiration = Config.read<bool>("Report_Transpiration");
	Rep_LeafWaterPotential = Config.read<bool>("Report_LeafWaterPotential");

	Config.readInto(fn_rep_mask, "TS_mask");

	RepTs_OutletDischarge = Config.read<bool>("Ts_OutletDischarge");
	RepTs_Long_Rad_Down = Config.read<bool>("Ts_Long_Rad_Down");
	RepTs_Short_Rad_Down = Config.read<bool>("Ts_Short_Rad_Down");
	RepTs_Precip = Config.read<bool>("Ts_Precip");
	RepTs_Rel_Humidity = Config.read<bool>("Ts_Rel_Humidity");
	RepTs_Wind_Speed = Config.read<bool>("Ts_Wind_Speed");
	RepTs_AvgAir_Temperature = Config.read<bool>("Ts_AvgAir_Temperature");
	RepTs_MinAir_Temperature = Config.read<bool>("Ts_MinAir_Temperature");
	RepTs_MaxAir_Temperature = Config.read<bool>("Ts_MaxAir_Temperature");
	RepTs_SWE = Config.read<bool>("Ts_SWE");
	RepTs_Infilt_Cap = Config.read<bool>("Ts_Infilt_Cap");
	RepTs_Streamflow = Config.read<bool>("Ts_Streamflow");
	RepTs_Soil_Water_Content_Average = Config.read<bool>("Ts_Soil_Water_Content_Average");
	RepTs_Soil_Water_Content_L1 = Config.read<bool>("Ts_Soil_Water_Content_L1");
	RepTs_Soil_Water_Content_L2 = Config.read<bool>("Ts_Soil_Water_Content_L2");
	RepTs_Soil_Water_Content_L3 = Config.read<bool>("Ts_Soil_Water_Content_L3");
	RepTs_Soil_Sat_Deficit = Config.read<bool>("Ts_Soil_Sat_Deficit");
	RepTs_GroundWater = Config.read<bool>("Ts_Ground_Water");
	RepTs_Soil_ETP = Config.read<bool>("Ts_Soil_ETP");
	RepTs_Soil_Net_Rad = Config.read<bool>("Ts_Soil_Net_Rad");
	RepTs_Soil_LE = Config.read<bool>("Ts_Soil_LE");
	RepTs_Sens_Heat = Config.read<bool>("Ts_Sens_Heat");
	RepTs_Grnd_Heat = Config.read<bool>("Ts_Grnd_Heat");
	RepTs_Snow_Heat = Config.read<bool>("Ts_Snow_Heat");
	RepTs_Soil_Temperature = Config.read<bool>("Ts_Soil_Temperature");
	RepTs_Skin_Temperature = Config.read<bool>("Ts_Skin_Temperature");
	RepTs_Veget_frac = Config.read<bool>("Ts_Veget_frac");
	RepTs_Stem_Density = Config.read<bool>("Ts_Stem_Density");
	RepTs_Leaf_Area_Index = Config.read<bool>("Ts_Leaf_Area_Index");
	RepTs_Canopy_Conductance = Config.read<bool>("Ts_Canopy_Conductance");
	RepTs_GPP = Config.read<bool>("Ts_GPP");
	RepTs_NPP = Config.read<bool>("Ts_NPP");
	RepTs_Basal_Area = Config.read<bool>("Ts_Basal_Area");
	RepTs_Tree_Height = Config.read<bool>("Ts_Tree_Height");
	RepTs_Root_Mass = Config.read<bool>("Ts_Root_Mass");
	RepTs_Canopy_Temp = Config.read<bool>("Ts_Canopy_Temp");
	RepTs_Canopy_NetR = Config.read<bool>("Ts_Canopy_NetR");
	RepTs_Canopy_LE = Config.read<bool>("Ts_Canopy_LE");
	RepTs_Canopy_Sens_Heat = Config.read<bool>("Ts_Canopy_Sens_Heat");
	RepTs_Canopy_Water_Stor = Config.read<bool>("Ts_Canopy_Water_Stor");
	RepTs_Transpiration = Config.read<bool>("Ts_Transpiration");
	RepTs_LeafWaterPotential = Config.read<bool>("Ts_LeafWaterPotential");


	}
	catch(ConfigFile::file_not_found &fn){
		cout << "File " << fn.filename << " not found\n";
		exit(EXIT_SUCCESS);
	}
	catch(ConfigFile::key_not_found &fn){
			cout << "Key " << fn.key << " not found\n";
			exit(EXIT_SUCCESS);
	}
	catch(std::exception &e){
				cout << e.what();
				exit(EXIT_SUCCESS);
		}




	return 1;
}
