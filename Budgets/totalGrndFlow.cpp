/*
 * totalGrndFlow.cpp
 *
 *  Created on: Dec 10, 2010
 *      Author: Marco.Maneta
 */

#include "Budget.h"

void Budget::TotalGrndFlow(const vectCells *timeseries, const Basin *b)
{
	gwtrflow += AccountFluxes(timeseries, b);
}
