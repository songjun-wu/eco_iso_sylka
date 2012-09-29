/*
 * TotalStorage.cpp
 *
 *  Created on: Mar 18, 2010
 *      Author: Marco Maneta
 */

#include "Budget.h"

void Budget::TotalStorage( const grid *Canopy,
		const grid *Snow,
		const grid *Ponding,
		const grid *Vadose,
		const grid *GravWater,
		const grid *GrndWater,
		const Basin *b)
{
	canopy = AccountStorages(Canopy, b);
	snowpack = AccountStorages(Snow, b);
	ponding = AccountStorages(Ponding, b);
	vadose = AccountStorages(Vadose, b);
	gravwater = AccountStorages(GravWater, b);
	grndwater = AccountStorages(GrndWater, b);

}
