/*
 * TotalPrecipitation.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: Marco Maneta
 */

#include "Budget.h"

void Budget::TotalPrecipitation(const grid* map, const Atmosphere *b)
{
	precipitation += AccountFluxes(map, b);
}
