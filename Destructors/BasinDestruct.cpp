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
	if(_soilmoist)
		delete _soilmoist;
	if(_AccumInfilt)
		delete _AccumInfilt;
	if(_soildepth)
		delete _soildepth;
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
	if(_SoilWaterDepth)
		delete _SoilWaterDepth;
	if(_SoilSatDeficit)
		delete _SoilSatDeficit;
	if(_psi)
		delete _psi;
	if(_CanopyStorage)
		delete _CanopyStorage;
	if(_Disch)
		delete _Disch;
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
	if(_channelmask)
		delete _channelmask;
	if(_chGWparam)
		delete _chGWparam;
	if(_soilmoist10cm)
		delete _soilmoist10cm;
	if(_soilmoist2)
		delete _soilmoist2;
	if(_soilmoist3)
		delete _soilmoist3;
	if(_EquivDepth2Sat)
		delete _EquivDepth2Sat;


	if(fForest)
		delete fForest;
}
