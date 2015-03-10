/*
 * BasinConstruct.cpp
 *
 *  Created on: Oct 9, 2009
 *      Author: Marco Maneta
 */

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

		/*sorts the basin with data cells according
		 * to the ldd after _DEM and _ldd have been created*/
		_vSortedGrid = Basin::SortGridLDD();

		fForest = new Forest(ctrl); //constructs the Forest object

		/*basin parameters and properties*/
		_slope = new grid(ctrl.path_BasinFolder + ctrl.fn_slope, ctrl.MapType);
		_Ksat = new grid(ctrl.path_BasinFolder + ctrl.fn_ksat, ctrl.MapType);
		_random_roughness = new grid(ctrl.path_BasinFolder + ctrl.fn_randrough, ctrl.MapType);
		_porosity = new grid(ctrl.path_BasinFolder + ctrl.fn_poros, ctrl.MapType);
		_psi_ae = new grid(ctrl.path_BasinFolder + ctrl.fn_psi_ae, ctrl.MapType);
		_BClambda = new grid(ctrl.path_BasinFolder + ctrl.fn_BClambda, ctrl.MapType);
		_theta_r = new grid(ctrl.path_BasinFolder + ctrl.fn_theta_r, ctrl.MapType);
		_soildepth = new grid(ctrl.path_BasinFolder + ctrl.fn_soildepth, ctrl.MapType);
		_paramWc = new grid(ctrl.path_BasinFolder + ctrl.fn_paramWc, ctrl.MapType);
		_paramWp = new grid(ctrl.path_BasinFolder + ctrl.fn_paramWp, ctrl.MapType);
		_meltCoeff = new grid(ctrl.path_BasinFolder + ctrl.fn_snowCf, ctrl.MapType);

		_snow = new grid(ctrl.path_BasinFolder + ctrl.fn_swe, ctrl.MapType);
		_albedo = new grid(ctrl.path_BasinFolder + ctrl.fn_albedo, ctrl.MapType);
		_emiss_surf = new grid(ctrl.path_BasinFolder + ctrl.fn_emiss, ctrl.MapType);
		_soil_dry_heatcap = new grid(ctrl.path_BasinFolder + ctrl.fn_soilheatcap, ctrl.MapType);
		_soil_dry_thermcond = new grid(ctrl.path_BasinFolder + ctrl.fn_soilthermcond, ctrl.MapType);
		_dampdepth = new grid(ctrl.path_BasinFolder + ctrl.fn_dampdepth, ctrl.MapType);
		_Temp_d = new grid(ctrl.path_BasinFolder + ctrl.fn_tempdamp, ctrl.MapType);

		_channelmask = new grid(ctrl.path_BasinFolder + ctrl.fn_chmask, ctrl.MapType);
		_chGWparam = new grid(ctrl.path_BasinFolder + ctrl.fn_chgwparam, ctrl.MapType);

		/*state variables initialized with user map*/
		_soilmoist = new grid(ctrl.path_BasinFolder + ctrl.fn_soilmoist, ctrl.MapType);  //soil moisture volumetric
		_Temp_s_old = new grid(ctrl.path_BasinFolder + ctrl.fn_soiltemp, ctrl.MapType);  //initial soil temperature C

		/*
		 * This sections is for maps that are dependent on the runtime options
		 */

		//set to NULL all pointers that may never be allocated to avoid deletion attempt in the destructor
		_soilmoist10cm = NULL;
		_EquivDepth2Sat = NULL;
		_soilmoist2 = NULL;
		_soilmoist3 = NULL;
		_bedrock_leak = NULL;
		//Allocate memory for calculation of hydrostatic soil moisture profile
		if(ctrl.toggle_soil_water_profile==1){
			_soilmoist10cm = new grid(*_DEM); //average volumetric soil moisture of the first 10 cm of the soil as calculated using a hydrstatic equilibrium moisture profile
			_EquivDepth2Sat = new grid(*_DEM); //Equivalent depth to saturation as calculated from average soil moisture and hydrstatic equilibrium (m)
		}

		if(ctrl.toggle_soil_water_profile==2)
		{
			_soilmoist10cm = new grid(ctrl.path_BasinFolder + ctrl.fn_soilmoist, ctrl.MapType);  //soil moisture 1st layer volumetric
			_soilmoist2 = new grid(ctrl.path_BasinFolder + ctrl.fn_soilmoist2, ctrl.MapType);  //soil moisture 2nd layer volumetric
			_soilmoist3 = new grid(ctrl.path_BasinFolder + ctrl.fn_soilmoist3, ctrl.MapType);  //soil moisture 3rd layer volumetric
			_bedrock_leak = new grid(ctrl.path_BasinFolder + ctrl.fn_bedrock_leak, ctrl.MapType);  //soil moisture 3rd layer volumetric
		}
		else{
			_soilmoist10cm = new grid(*_DEM);
		}

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
		_Disch = new grid(*_DEM);

		_ponding = new grid(*_DEM);
		_infilt_cap = new grid(*_DEM); //infilt cap m h-1
		_AccumInfilt = new grid(*_DEM); //accumulated infiltration in meters
		_Evaporation = new grid(*_DEM); //actual evaporation in m h-1
		_SoilWaterDepth = new grid(*_DEM); //soil moisture depth m
		_SoilSatDeficit = new grid(*_DEM); //soil moisture including water below and above field capacity
		_psi = new grid(*_DEM); //soil tension (m) calculated with B&C formula
		_GravityWater = new grid(*_DEM); //soil water storage beyond
		_GrndWaterOld = new grid(*_DEM); //groundwater storage at teh beginning of the time step
		_GrndWater = new grid(*_DEM); //groundwater storage at the end of the time step



	}catch (std::bad_alloc &)
	  { cerr << "Couldn't allocate memory..." << "\n";
		cin.get(); throw;
	  }

	CalcCatchArea(); //Fills-in the _catcharea map with the upstream catchment area of each cell
	CalcFieldCapacity(); //calcualte the value of field capacity using the Brooks and Corey Formula

/*	for(unsigned int r = 0; r <  _NRows; r++)//remove!!!!!
	      for(unsigned int c = 0; c <  _NCols; c++)
	      {
	        _Temp_s->matrix[r][c] = 2;
	        _Temp_s_old->matrix[r][c] = 1;
	      }*/
}
