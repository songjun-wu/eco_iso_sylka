/*
 * TotalLeakage.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: marco
 */

#include "Budget.h"

void Budget::TotalBedrockLeakage(const grid* map, const Basin *b)
{
	leakage += AccountFluxes(map, b);
}


