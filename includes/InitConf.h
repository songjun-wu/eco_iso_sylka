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
  float report_times; //times at which report outputs time series
  float reportMap_times; //times at which report outputs maps
  
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
  bool Rep_Soil_Net_Rad;
  bool Rep_Soil_LE;
  bool Rep_Sens_Heat;
  bool Rep_Grnd_Heat;
  bool Rep_Snow_Heat;
  bool Rep_Soil_Temperature;
  bool Rep_Skin_Temperature;
  
  bool Rep_GWtoChn;
  bool Rep_SrftoChn;
  bool Rep_L1toSrf;
  bool Rep_Net_Rad_sum;
  bool Rep_Total_ET;
  bool Rep_Transpiration_sum;
  bool Rep_Einterception_sum;
  bool Rep_Esoil_sum;
  
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
  bool Rep_ETspecies;
  bool Rep_Transpiration;
  bool Rep_Einterception;
  bool Rep_Esoil;
  
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
  bool RepTs_Soil_Net_Rad;
  bool RepTs_Soil_LE;
  bool RepTs_Sens_Heat;
  bool RepTs_Grnd_Heat;
  bool RepTs_Snow_Heat;
  bool RepTs_Soil_Temperature;
  bool RepTs_Skin_Temperature;

  bool RepTs_GWtoChn;
  bool RepTs_SrftoChn;
  bool RepTs_L1toSrf;
  
  bool RepTs_Net_Rad_sum;
  bool RepTs_Total_ET;
  bool RepTs_Transpiration_sum;
  bool RepTs_Einterception_sum;
  bool RepTs_Esoil_sum;
  
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
  bool RepTs_ETspecies;
  bool RepTs_Transpiration;
  bool RepTs_Einterception;
  bool RepTs_Esoil;
  
  // Tracking  -------------------------------------------------
  // Tracking inputs
  string fn_tracking;
  bool sw_trck; //switch to turn on and off the tracking option
  bool sw_frac; //switch to turn on and off fractionation in soil evap
  bool sw_lifo; //switch to turn "last in last, first out" for topsoil evaporation (last = same tstep precip/melt)
  bool sw_dD; //switch to turn on and off the dD tracking option (if sw_trck = 1)
  bool sw_d18O; //switch to turn on and off the d18O tracking option (if sw_trck = 1)
  bool sw_Age; //switch to turn on and off the age tracking option (if sw_trck = 1)
  
  /* input maps for initial values*/
  string fn_dDprecip; // deuterium signature in precipitations (dD, per mil)
  //string fn_dDcanopy;
  string fn_dDsnowpack;
  string fn_dDsurface;
  string fn_dDsoil1;
  string fn_dDsoil2;
  string fn_dDsoil3;
  string fn_dDgroundwater;
  //string fn_dDchannel;
  
  string fn_d18Oprecip; // O eighteen signature in precipitations (d18O, per mil)
  //string fn_dDcanopy;
  string fn_d18Osnowpack;
  string fn_d18Osurface;
  string fn_d18Osoil1;
  string fn_d18Osoil2;
  string fn_d18Osoil3;
  string fn_d18Ogroundwater;
  //string fn_d18Ochannel;
  
  //string fn_Agecanopy;
  string fn_Agesnowpack;
  string fn_Agesurface;
  string fn_Agesoil1;
  string fn_Agesoil2;
  string fn_Agesoil3;
  string fn_Agegroundwater;
  //string fn_Agechannel;
  
  /* maps report */
  bool Rep_dDprecip;
  bool Rep_dDcanopy;
  bool Rep_dDsnowpack;
  bool Rep_dDsurface;
  bool Rep_dDsoil1;
  bool Rep_dDsoil2;
  bool Rep_dDsoilUp;
  bool Rep_dDsoil3;
  //bool Rep_dDsoilAv;
  bool Rep_dDgroundwater;
  bool Rep_dDevapS;
  bool Rep_dDevapS_sum;
  bool Rep_dDevapI;
  bool Rep_dDevapI_sum;
  bool Rep_dDtranspi;
  bool Rep_dDtranspi_sum;
  
  bool Rep_d18Oprecip;
  bool Rep_d18Ocanopy;
  bool Rep_d18Osnowpack;
  bool Rep_d18Osurface;
  bool Rep_d18Osoil1;
  bool Rep_d18Osoil2;
  bool Rep_d18OsoilUp;
  bool Rep_d18Osoil3;
  //bool Rep_d18OsoilAv;
  bool Rep_d18Ogroundwater;
  bool Rep_d18OevapS;
  bool Rep_d18OevapS_sum;
  bool Rep_d18OevapI;
  bool Rep_d18OevapI_sum;
  bool Rep_d18Otranspi;
  bool Rep_d18Otranspi_sum;
  
  bool Rep_Agecanopy;
  bool Rep_Agesnowpack;
  bool Rep_Agesurface;
  bool Rep_Agesoil1;
  bool Rep_Agesoil2;
  bool Rep_AgesoilUp;
  bool Rep_Agesoil3;
  //bool Rep_AgesoilAv;
  bool Rep_Agegroundwater;
  bool Rep_AgeevapS;
  bool Rep_AgeevapS_sum;
  bool Rep_AgeevapI;
  bool Rep_AgeevapI_sum;
  bool Rep_Agetranspi;
  bool Rep_Agetranspi_sum;
  
  // Time series
  bool RepTs_dDprecip;
  //bool RepTs_dDcanopy;
  bool RepTs_dDsnowpack;
  bool RepTs_dDsurface;
  bool RepTs_dDsoil1;
  bool RepTs_dDsoil2;
  bool RepTs_dDsoilUp;
  bool RepTs_dDsoil3;
  //bool RepTs_dDsoilAv;
  bool RepTs_dDgroundwater;
  bool RepTs_dDevapS;
  bool RepTs_dDevapS_sum;
  bool RepTs_dDevapI;
  bool RepTs_dDevapI_sum;
  bool RepTs_dDtranspi;
  bool RepTs_dDtranspi_sum;
  
  bool RepTs_d18Oprecip;
  //bool RepTs_d18Ocanopy;
  bool RepTs_d18Osnowpack;
  bool RepTs_d18Osurface;
  bool RepTs_d18Osoil1;
  bool RepTs_d18Osoil2;
  bool RepTs_d18OsoilUp;
  bool RepTs_d18Osoil3;
  //bool RepTs_d18OsoilAv;
  bool RepTs_d18Ogroundwater;
  bool RepTs_d18OevapS;
  bool RepTs_d18OevapS_sum;
  bool RepTs_d18OevapI;
  bool RepTs_d18OevapI_sum;
  bool RepTs_d18Otranspi;
  bool RepTs_d18Otranspi_sum;
  
  //bool RepTs_Agecanopy;
  bool RepTs_Agesnowpack;
  bool RepTs_Agesurface;
  bool RepTs_Agesoil1;
  bool RepTs_Agesoil2;
  bool RepTs_AgesoilUp;
  bool RepTs_Agesoil3;
  //bool RepTs_AgesoilAv;
  bool RepTs_Agegroundwater;
  bool RepTs_AgeevapS;
  bool RepTs_AgeevapS_sum;
  bool RepTs_AgeevapI;
  bool RepTs_AgeevapI_sum;
  bool RepTs_Agetranspi;
  bool RepTs_Agetranspi_sum;
  // --------------------------
  
  
  Control(){ 	current_ts_count = 1;
    toggle_ra = 0;
  };
  
  int ReadConfigFile(string confilename = "config.ini");
  
  int ReadConfigTrck(string confilename = "configTrck.ini");
  
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
