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
 *    Marco Maneta
 *******************************************************************************/
/*
 * InitConf.h
 *
 *  Created on: Oct 13, 2009
 *      Author: Marco Maneta
 */

#ifndef INITCONF_H_
#define INITCONF_H_

#include "ParsingFunctions.h"

struct Control{

		/*Folder paths*/
		string path_BasinFolder; //folder where basin property maps are located
		string path_ClimMapsFolder; //folder where weather maps series are located
		string path_ResultsFolder; //folder where results will be placed

		/*Time control variables*/

		float starttime; //simulation start time (seconds)
		float endtime; //simulation end time (seconds)
		float dt; //simulation time step (seconds)
		float BC_dt; // time step for spatial climatic inputs (seconds)
		float report_times; //times at which report outputs

		float current_t_step; //current time step (seconds)
		unsigned int current_ts_count; //current count of time step


		/*Control switches*/
		string MapType; //indicates if the maps to be read are ASCII (grass) or PCRASTER (csf)
		string ForestStateVarsInputType; //indicates if the forest state variables are input as tables (tables) or maps (maps)

		/*Option switches*/
		bool sw_veg_dyn; //switch to turn on and off the dynamic vegetation module (allocation and lai calculation)
		bool sw_reinfilt; //switch to turn on and off the reinfiltration option
		bool sw_channel; //switch to turn on and off the channel option

		/*multiple option switches*/
		//int toggle_soil_water_profile; //toggle between different soil moisture profile calculation
		int toggle_ra; //toggle between aerodynamic resistance options
		int toggle_rs; //toggle between different soil resistance option


		/*Base maps filenames*/
		string fn_dem; //local base dem filename that forces grid geometry
		string fn_ldd; //local drain direction map filename
		string fn_chwidth; //channel width (m)
		string fn_chgwparam; //channel water transfer parameter
		string fn_chmanningn; //channel roughness parameter

		/*Soil properties and parameters*/
		string fn_ksat; //soil hydraulic conductivity mh-1
		string fn_kvkh; //vertical to horizontal ksat anisotropy ratio
		string fn_randrough; //terrain base random roughness to calcualte aerodynamic resistance (m)
		string fn_slope; //surface slope m m-1
		string fn_poros; //volumetric
		string fn_psi_ae; //soil air entry pressure m
		string fn_BClambda; //brooks and corey lambda param
		string fn_theta_r; //residual soil moisture
		string fn_soildepth; //soil depth in m
		string fn_depth_layer1; //depth of layer 1 in m
		string fn_depth_layer2;  //depth of layer 2 in m. Layer 3 evaluated from soil depth
		string fn_root_fraction_lay1; //fraction of roots in soil layer 1
		string fn_root_fraction_lay2; // fraction of roots in soil layer 2. Soil layer 3 implied
		string fn_Kroot; // coefficient for exponential root profile, in m-1
		string fn_bedrock_leak; //bedrock leakance in s-1
		string fn_paramWc; //empirical parameter in water efficiency function for GPP calculation (see Landsber and Waring, 1997 or TRIPLEX paper
		string fn_paramWp;//empirical parameter in water efficiency function for GPP calculation (see Landsber and Waring, 1997 or TRIPLEX paper
		string fn_snowCf; //empirical parameter that controls the snowmelt rates m s-1 C-1

		/*Basin state variables*/
		string fn_swe;
		string fn_albedo;
		string fn_emiss;
		string fn_soilheatcap;
		string fn_soilthermcond;
		string fn_dampdepth;
		string fn_tempdamp;
		string fn_streamflow;
		string fn_soilmoist;
		string fn_soilmoist2;
		string fn_soilmoist3;
		string fn_soiltemp;

		/*Climate zones and climate input files*/
		float snow_rain_temp; //threshold temp for snow rain transition, degC
		string fn_climzones; //base climatic zones map with the grid geometry
		string fn_isohyet; //map with rainfall multipliers
		string fn_Ldown; //Incoming longwave radiation Wm-2
		string fn_Sdown; //Incoming shortwave radiation Wm-2
		string fn_temp; //average air temperature C
		string fn_maxTemp; //max air temp C
		string fn_minTemp; //min air temp C
		string fn_precip; //
		string fn_rel_humid; //relative humidity
		string fn_wind_speed; //wind speed ms-1

		/*Forest patches and forest input files*/
		int NumSpecs; //number of tree species in the simulation
		string fn_patches;
		string fn_paramtable;
		string fn_proptable;
		string fn_StemDenstable;
		string fn_LAItable;
		string fn_AGEtable;
		string fn_BasalAreatable;
		string fn_Heighttable;
		string fn_RootMasstable;

		/*report flags*/
		bool Rep_Long_Rad_Down;
		bool Rep_Short_Rad_Down;
		bool Rep_Precip;
		bool Rep_Rel_Humidity;
		bool Rep_Wind_Speed;
		bool Rep_AvgAir_Temperature;
		bool Rep_MinAir_Temperature;
		bool Rep_MaxAir_Temperature;
		bool Rep_SWE;
		bool Rep_Infilt_Cap;
		bool Rep_Streamflow;
		bool Rep_Saturation_Area;
		bool Rep_Ponding;
		bool Rep_Soil_Water_Content_Average;
		bool Rep_Soil_Water_Content_12;
		bool Rep_Soil_Water_Content_L1;
		bool Rep_Soil_Water_Content_L2;
		bool Rep_Soil_Water_Content_L3;
		bool Rep_WaterTableDepth;
		bool Rep_Soil_Sat_Deficit;
		bool Rep_GWater;
		bool Rep_Total_ET;
		bool Rep_Soil_ETP;
		bool Rep_Soil_Net_Rad;
		bool Rep_Soil_LE;
		bool Rep_Sens_Heat;
		bool Rep_Grnd_Heat;
		bool Rep_Snow_Heat;
		bool Rep_Soil_Temperature;
		bool Rep_Skin_Temperature;

		bool Rep_Net_Rad_ToC;
		bool Rep_Transpiration_ToC;
		bool Rep_Einterception_ToC;

		bool Rep_Veget_frac;
		bool Rep_Stem_Density;
		bool Rep_Leaf_Area_Index;
		bool Rep_Stand_Age;
		bool Rep_Canopy_Conductance;
		bool Rep_GPP;
		bool Rep_NPP;
		bool Rep_Basal_Area;
		bool Rep_Tree_Height;
		bool Rep_Root_Mass;
		bool Rep_Canopy_Temp;
		bool Rep_Canopy_NetR;
		bool Rep_Canopy_LE_E;
		bool Rep_Canopy_LE_T;
		bool Rep_Canopy_Sens_Heat;
		bool Rep_Canopy_Water_Stor;
		bool Rep_Transpiration;
		bool Rep_Einterception;

		/*time series reporting input files*/
		string fn_rep_mask;

		bool RepTs_OutletDischarge; //only reported at the outlets
		bool RepTs_Long_Rad_Down;
		bool RepTs_Short_Rad_Down;
		bool RepTs_Precip;
		bool RepTs_Rel_Humidity;
		bool RepTs_Wind_Speed;
		bool RepTs_AvgAir_Temperature;
		bool RepTs_MinAir_Temperature;
		bool RepTs_MaxAir_Temperature;
		bool RepTs_SWE;
		bool RepTs_Infilt_Cap;
		bool RepTs_Streamflow;
		bool RepTs_Ponding;
		bool RepTs_Soil_Water_Content_Average;
		bool RepTs_Soil_Water_Content_12;
		bool RepTs_Soil_Water_Content_L1;
		bool RepTs_Soil_Water_Content_L2;
		bool RepTs_Soil_Water_Content_L3;
		bool RepTs_WaterTableDepth;
		bool RepTs_Soil_Sat_Deficit;
		bool RepTs_GroundWater;
		bool RepTs_Total_ET;
		bool RepTs_Soil_ETP;
		bool RepTs_Soil_Net_Rad;
		bool RepTs_Soil_LE;
		bool RepTs_Sens_Heat;
		bool RepTs_Grnd_Heat;
		bool RepTs_Snow_Heat;
		bool RepTs_Soil_Temperature;
		bool RepTs_Skin_Temperature;

		bool RepTs_Net_Rad_ToC;
		bool RepTs_Transpiration_ToC;
		bool RepTs_Einterception_ToC;

		bool RepTs_Veget_frac;
		bool RepTs_Stem_Density;
		bool RepTs_Leaf_Area_Index;
		bool RepTs_Canopy_Conductance;
		bool RepTs_GPP;
		bool RepTs_NPP;
		bool RepTs_Basal_Area;
		bool RepTs_Tree_Height;
		bool RepTs_Root_Mass;
		bool RepTs_Canopy_Temp;
		bool RepTs_Canopy_NetR;
		bool RepTs_Canopy_LE_E;
		bool RepTs_Canopy_LE_T;
		bool RepTs_Canopy_Sens_Heat;
		bool RepTs_Canopy_Water_Stor;
		bool RepTs_Transpiration;
		bool RepTs_Einterception;



		Control(){ 	current_ts_count = 1;
					toggle_ra = 0;
		};

		int ReadConfigFile(string confilename = "config.ini");

		void AdvanceTimeStep(){
			current_ts_count++;
			current_t_step = current_ts_count * dt;
		}

		float GetTimeStep() {
			return current_t_step;
		}

		unsigned int GetTimeStepCount() {
			return current_ts_count;
		}
};

#endif /* INITCONF_H_ */
