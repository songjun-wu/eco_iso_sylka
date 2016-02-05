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


	if(fForest)
		delete fForest;
}
