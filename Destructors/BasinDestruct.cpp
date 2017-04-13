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
 * BasinDestruct.cpp
 *
 *  Created on: Oct 13, 2009
 *      Author: Marco Maneta
 */

#include "Basin.h"

Basin::~Basin(){

	if(_DEM)
		delete _DEM;
	if(_ldd)
		delete _ldd;
	if(_snow)
		delete _snow;
	if(_Rn)
		delete _Rn;
	if(_RnToC)
		delete _RnToC;
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
	if(_rootfrac1)
		delete _rootfrac1;
	if(_rootfrac2)
		delete _rootfrac2;
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
	if(_WaterTableDepth)
		delete _WaterTableDepth;
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
	if(_PondingOld)
		delete _PondingOld;
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
	if(_soilmoist_12)
		delete _soilmoist_12;
	if(_soilmoist2)
		delete _soilmoist2;
	if(_soilmoist3)
		delete _soilmoist3;
	if(_bedrock_leak)
		delete _bedrock_leak;
	if(_IsSaturated)
		delete _IsSaturated;
	if(_EvaporationS)
		delete _EvaporationS;
	if(_EvaporationI_all)
		delete _EvaporationI_all;
	if(_Transpiration_all)
		delete _Transpiration_all;


	if(fForest)
		delete fForest;
}
