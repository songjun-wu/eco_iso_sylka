/*
 * AtmosphDesctruct.cpp
 *
 *  Created on: Oct 15, 2009
 *      Author: Marco Maneta
 */

#include "Atmosphere.h"

Atmosphere::~Atmosphere(){

	if(_zones)
		delete _zones;
	if(_Ldown)
		delete _Ldown;
	if(_Sdown)
		delete _Sdown;
	if(_Tp)
		delete _Tp;
	if(_MaxTp)
		delete _MaxTp;
	if(_MinTp)
		delete _MinTp;
	if(_Precip)
		delete _Precip;
	if(_Rel_humid)
		delete _Rel_humid;
	if(_Wind_speed)
		delete _Wind_speed;
	if(_zoneId)
		delete[] _zoneId;
	if(_isohyet)
		delete _isohyet;


	if(ifLdown.is_open())
		ifLdown.close();
	if(ifSdown.is_open())
		ifSdown.close();
	if(ifTp.is_open())
		ifTp.close();
	if(ifMaxTp.is_open())
		ifMaxTp.close();
	if(ifMinTp.is_open())
		ifMinTp.close();
	if(ifPrecip.is_open())
		ifPrecip.close();
	if(ifRelHumid.is_open())
		ifRelHumid.close();
	if(ifWindSpeed.is_open())
		ifWindSpeed.close();
}
