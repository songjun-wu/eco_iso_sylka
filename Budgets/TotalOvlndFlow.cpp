/*
 * TotalOvlndFlow.cpp
 *
 *  Created on: Jul 29, 2010
 *      Author: Marco.Maneta
 */

#include "Budget.h"

void Budget::TotalOvlndFlow(const vectCells *timeseries, const Basin *b)
{
	ovlndflow += AccountFluxes(timeseries, b);
}
