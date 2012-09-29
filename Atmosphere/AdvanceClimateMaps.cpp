/*
 * AdvanceClimateMaps.cpp
 *
 *  Created on: Oct 18, 2009
 *      Author: Marco Maneta
 */

#include "Atmosphere.h"

int Atmosphere::AdvanceClimateMaps(){


	if(UpdateClimateMap(ifLdown, *_Ldown)!=_vSsortedGridTotalCellNumber)
		throw;
	if(UpdateClimateMap(ifSdown, *_Sdown)!=_vSsortedGridTotalCellNumber)
		throw;
	if(UpdateClimateMap(ifTp, *_Tp)!=_vSsortedGridTotalCellNumber)
		throw;
	if(UpdateClimateMap(ifMaxTp, *_MaxTp)!=_vSsortedGridTotalCellNumber)
		throw;
	if(UpdateClimateMap(ifMinTp, *_MinTp)!=_vSsortedGridTotalCellNumber)
		throw;
	if(UpdateClimateMap(ifPrecip, *_Precip)!=_vSsortedGridTotalCellNumber)
		throw;
	AdjustPrecip(); // adjust precipitation with the isohyet map
	if(UpdateClimateMap(ifRelHumid, *_Rel_humid)!=_vSsortedGridTotalCellNumber)
		throw;
	if(UpdateClimateMap(ifWindSpeed, *_Wind_speed)!=_vSsortedGridTotalCellNumber)
		throw;

	return EXIT_SUCCESS;

}
