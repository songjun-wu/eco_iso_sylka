/*
 * CalculateForestGrowth.cpp
 *
 *  Created on: Jul 12, 2010
 *      Author: Marco.Maneta
 */

#include "Basin.h"

int Basin::CalculateGrowForest(const Atmosphere &atm, const Control &ctrl){
		fForest->GrowForest(*this, atm, ctrl);
		return EXIT_SUCCESS;
	}
