/*
 * GroveDestruct.cpp
 *
 *  Created on: Jun 17, 2010
 *      Author: marco
 */

#include "Grove.h"

Grove::~Grove(){

	if(_fraction)
		delete _fraction;
	if(_StemDensity)
		delete _StemDensity;
	if(_LAI)
		delete _LAI;
	if(_AGE)
		delete _AGE;
	if(_CanopyConductance)
		delete _CanopyConductance;
	if(_GPP)
		delete _GPP;
	if(_NPP)
		delete _NPP;
	if(_BasalArea)
		delete _BasalArea;
	if(_Height)
		delete _Height;
	if(_RootMass)
		delete _RootMass;
	if(_Del_FoliageMass)
		delete _Del_FoliageMass;
	if(_Del_StemMass)
		delete _Del_StemMass;
	if(_Del_RootMass)
		delete _Del_RootMass;
	if(_Temp_c)
		delete _Temp_c;
	if(_NetR_Can)
		delete _NetR_Can;
	if(_LatHeat_Can)
		delete _LatHeat_Can;
	if(_SensHeat_Can)
		delete _SensHeat_Can;
	if(_WaterStorage)
		delete _WaterStorage;
	if(_ET)
		delete _ET;
	if(_Transpiration)
		delete _Transpiration;


}
