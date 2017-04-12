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
 * BasinConstruct.cpp
 *
 *  Created on: Oct 9, 2009
 *      Author: Marco Maneta
 */
#include <unistd.h>
#include  <fstream>
#include "Basin.h"

Basin::Basin(Control &ctrl)
{
	try{

	//Read the base map and writes the dimensions of the grid
		_DEM = new grid(ctrl.path_BasinFolder + ctrl.fn_dem, ctrl.MapType);
		_NRows = _DEM->r;
		_NCols = _DEM->c;
		_dx = _DEM->dx;

		_ldd = new grid(ctrl.path_BasinFolder + ctrl.fn_ldd, ctrl.MapType);

		printf("Checking if file %s exists...\n", (ctrl.path_BasinFolder + ctrl.fn_dem + ".serialized.svf").c_str());
		/*
		 * Checks if there is a _vSordtedGrid object with the correct name in the spatial folder
		 */
		if (access((ctrl.path_BasinFolder + ctrl.fn_dem + ".serialized.svf").c_str(), F_OK) != -1) {
			printf("File Found!. Loading object...\n");
			loadSortedGrid(_vSortedGrid, (ctrl.path_BasinFolder + ctrl.fn_dem + ".serialized.svf").c_str());
		}
		else{
			printf("File not found!. Initializing and sorting grid...\n");

		/*sorts the basin with data cells according
		 * to the ldd after _DEM and _ldd have been created*/
		_vSortedGrid = Basin::SortGridLDD();

		printf("Sorting done. Saving serialized sorted grid object for subsequent runs...\n");

		saveSortedGrid(_vSortedGrid, (ctrl.path_BasinFolder + ctrl.fn_dem + ".serialized.svf").c_str());
		}

		fForest = new Forest(ctrl); //constructs the Forest object

		/*basin parameters and properties*/
		_slope = new grid(ctrl.path_BasinFolder + ctrl.fn_slope, ctrl.MapType);
		_Ksat = new grid(ctrl.path_BasinFolder + ctrl.fn_ksat, ctrl.MapType);
		_KvKs = new grid(ctrl.path_BasinFolder + ctrl.fn_kvkh, ctrl.MapType);
		_random_roughness = new grid(ctrl.path_BasinFolder + ctrl.fn_randrough, ctrl.MapType);
		_porosity = new grid(ctrl.path_BasinFolder + ctrl.fn_poros, ctrl.MapType);
		_psi_ae = new grid(ctrl.path_BasinFolder + ctrl.fn_psi_ae, ctrl.MapType);
		_BClambda = new grid(ctrl.path_BasinFolder + ctrl.fn_BClambda, ctrl.MapType);
		_theta_r = new grid(ctrl.path_BasinFolder + ctrl.fn_theta_r, ctrl.MapType);
		_soildepth = new grid(ctrl.path_BasinFolder + ctrl.fn_soildepth, ctrl.MapType);
		_depth_layer1 = new grid(ctrl.path_BasinFolder + ctrl.fn_depth_layer1, ctrl.MapType);
		_depth_layer2 = new grid(ctrl.path_BasinFolder + ctrl.fn_depth_layer2, ctrl.MapType);
		_bedrock_leak = new grid(ctrl.path_BasinFolder + ctrl.fn_bedrock_leak, ctrl.MapType);  //soil moisture 3rd layer volumetric
		_paramWc = new grid(ctrl.path_BasinFolder + ctrl.fn_paramWc, ctrl.MapType);
		_paramWp = new grid(ctrl.path_BasinFolder + ctrl.fn_paramWp, ctrl.MapType);
		_meltCoeff = new grid(ctrl.path_BasinFolder + ctrl.fn_snowCf, ctrl.MapType);

		//_rootfrac1 = new grid(ctrl.path_BasinFolder + ctrl.fn_root_fraction_lay1, ctrl.MapType);
		//_rootfrac2 = new grid(ctrl.path_BasinFolder + ctrl.fn_root_fraction_lay2, ctrl.MapType);
		_Kroot = new grid(ctrl.path_BasinFolder + ctrl.fn_Kroot, ctrl.MapType);

		_snow = new grid(ctrl.path_BasinFolder + ctrl.fn_swe, ctrl.MapType);
		_albedo = new grid(ctrl.path_BasinFolder + ctrl.fn_albedo, ctrl.MapType);
		_emiss_surf = new grid(ctrl.path_BasinFolder + ctrl.fn_emiss, ctrl.MapType);
		_soil_dry_heatcap = new grid(ctrl.path_BasinFolder + ctrl.fn_soilheatcap, ctrl.MapType);
		_soil_dry_thermcond = new grid(ctrl.path_BasinFolder + ctrl.fn_soilthermcond, ctrl.MapType);
		_dampdepth = new grid(ctrl.path_BasinFolder + ctrl.fn_dampdepth, ctrl.MapType);
		_Temp_d = new grid(ctrl.path_BasinFolder + ctrl.fn_tempdamp, ctrl.MapType);

		_channelwidth = new grid(ctrl.path_BasinFolder + ctrl.fn_chwidth, ctrl.MapType);
		_chGWparam = new grid(ctrl.path_BasinFolder + ctrl.fn_chgwparam, ctrl.MapType);
		_Manningn = new grid(ctrl.path_BasinFolder + ctrl.fn_chmanningn, ctrl.MapType);

		/*state variables initialized with user map*/
		_soilmoist1 = new grid(ctrl.path_BasinFolder + ctrl.fn_soilmoist, ctrl.MapType);  //soil moisture volumetric
		_soilmoist2 = new grid(ctrl.path_BasinFolder + ctrl.fn_soilmoist2, ctrl.MapType);  //soil moisture 2nd layer volumetric
		_soilmoist3 = new grid(ctrl.path_BasinFolder + ctrl.fn_soilmoist3, ctrl.MapType);  //soil moisture 3rd layer volumetric
		_Temp_s_old = new grid(ctrl.path_BasinFolder + ctrl.fn_soiltemp, ctrl.MapType);  //initial soil temperature C
		_Disch_old =  new grid(ctrl.path_BasinFolder + ctrl.fn_streamflow, ctrl.MapType);  //initial soil temperature C


		//Partial check of maps mainly to make sure no nodata is written within the valid domain
		CheckMaps(ctrl);

		/*state variables initialized with the base map*/
		_catcharea = new grid(*_DEM);
		_fieldcap = new grid(*_DEM);
		_Rn = new grid(*_DEM);
		_latheat = new grid(*_DEM);
		_sensheat = new grid(*_DEM);
		_grndheat = new grid(*_DEM);
		_snwheat = new grid(*_DEM);
		_Temp_s = new grid(*_DEM);
		//_Temp_s_old = new grid(*_DEM);
		_CanopyStorage = new grid(*_DEM);

		_IsSaturated = new grid(*_DEM);  //saturation map
		_soilmoist_av = new grid(*_DEM); //average volumetric soil moisture of the first 10 cm of the soil as calculated using a hydrstatic equilibrium moisture profile
		_ponding = new grid(*_DEM);
		_infilt_cap = new grid(*_DEM); //infilt cap m h-1
		_AccumInfilt = new grid(*_DEM); //accumulated infiltration in meters
		_Evaporation = new grid(*_DEM); //actual evaporation in m s-1
		_BedrockLeakageFlux = new grid(*_DEM); //bedrock leakage flux in m s-1
		_SoilWaterDepth = new grid(*_DEM); //soil moisture depth m
		_SoilSatDeficit = new grid(*_DEM); //soil moisture including water below and above field capacity
		_GravityWater = new grid(*_DEM); //soil water storage beyond
		_GrndWaterOld = new grid(*_DEM); //groundwater storage at teh beginning of the time step
		_GrndWater = new grid(*_DEM); //groundwater storage at the end of the time step
		_GWupstreamBC = new grid(*_DEM); //gw flux upstream boundary conditin (ms-1)
		_Disch_upstreamBC = new grid(*_DEM);



	}catch (std::bad_alloc &)
	  { cerr << " Cleaning basin objects..." << "\n";
		if(_DEM)
			delete _DEM;
		if(_ldd)
			delete _ldd;
		if(_snow)
			delete _snow;
		if(_Rn)
			delete _Rn;
		if(_latheat)
			delete _latheat;
		if(_sensheat)
			delete _sensheat;
		if(_grndheat)
			delete _grndheat;
		if(_snwheat)
			delete _snwheat;
		if(_Temp_s)
			delete _Temp_s;
		if(_Temp_s_old)
			delete _Temp_s_old;
		if(_albedo)
			delete _albedo;
		if(_emiss_surf)
			delete _emiss_surf;
		if(_soil_dry_heatcap)
			delete _soil_dry_heatcap;
		if(_soil_dry_thermcond)
			delete _soil_dry_thermcond;
		if(_dampdepth)
			delete _dampdepth;
		if(_Temp_d)
			delete _Temp_d;
		if(_ponding)
			delete _ponding;
		if(_Ksat)
			delete _Ksat;
		if(_KvKs)
			delete _KvKs;
		if(_random_roughness)
			delete _random_roughness;
		if(_slope)
			delete _slope;
		if(_porosity)
			delete _porosity;
		if(_psi_ae)
			delete _psi_ae;
		if(_BClambda)
			delete _BClambda;
		if(_theta_r)
			delete _theta_r;
		if(_infilt_cap)
			delete _infilt_cap;
		if(_soilmoist1)
			delete _soilmoist1;
		if(_AccumInfilt)
			delete _AccumInfilt;
		if(_soildepth)
			delete _soildepth;
		if(_depth_layer1)
			delete _depth_layer1;
		if(_depth_layer2)
			delete _depth_layer2;
		// if(_rootfrac1)
		// 	delete _rootfrac1;
		// if(_rootfrac2)
		// 	delete _rootfrac2;
		if(_Kroot)
			delete _Kroot;
		if(_fieldcap)
			delete _fieldcap;
		if(_paramWc)
			delete _paramWc;
		if(_paramWp)
			delete _paramWp;
		if(_meltCoeff)
			delete _meltCoeff;
		if(_Evaporation)
			delete _Evaporation;
		if(_BedrockLeakageFlux)
			delete _BedrockLeakageFlux;
		if(_SoilWaterDepth)
			delete _SoilWaterDepth;
		if(_SoilSatDeficit)
			delete _SoilSatDeficit;
		if(_CanopyStorage)
			delete _CanopyStorage;
		if(_Disch_old)
			delete _Disch_old;
		if(_Disch_upstreamBC)
			delete _Disch_upstreamBC;
		if(_catcharea)
			delete _catcharea;
		if(_GravityWater)
			delete _GravityWater;
		if(_GrndWaterOld)
			delete _GrndWaterOld;
		if(_GrndWater)
			delete _GrndWater;
		if(_GWupstreamBC)
			delete _GWupstreamBC;
		if(_channelwidth)
			delete _channelwidth;
		if(_chGWparam)
			delete _chGWparam;
		if(_Manningn)
			delete _Manningn;
		if(_soilmoist_av)
			delete _soilmoist_av;
		if(_soilmoist2)
			delete _soilmoist2;
		if(_soilmoist3)
			delete _soilmoist3;
		if(_bedrock_leak)
			delete _bedrock_leak;
		if(_IsSaturated)
			delete _IsSaturated;


		if(fForest)
			delete fForest;

	    throw;
	  }

	CalcCatchArea(); //Fills-in the _catcharea map with the upstream catchment area of each cell
	CalcFieldCapacity(); //calcualte the value of field capacity using the Brooks and Corey Formula
	CalcInitialStreamStorage(); //Reads initial streamflow map and populate _ponding variable with initial storage in stream
	CalcRootDistrib(); //from the species root profile and layer depth --> root frac in each layer

/*	for(unsigned int r = 0; r <  _NRows; r++)//remove!!!!!
	      for(unsigned int c = 0; c <  _NCols; c++)
	      {
	        _Temp_s->matrix[r][c] = 2;
	        _Temp_s_old->matrix[r][c] = 1;
	      }*/
}
