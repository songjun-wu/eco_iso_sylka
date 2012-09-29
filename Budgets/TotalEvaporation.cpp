/*
 * TotalEvaporation.cpp
 *
 *  Created on: Mar 17, 2010
 *      Author: Marco Maneta
 */

#include "Budget.h"

void Budget::TotalEvaporation(const grid* map, const Basin *b)
{
	evaporation += AccountFluxes(map, b);
}
