/*
 * MassBalanceError.cpp
 *
 *  Created on: Mar 18, 2010
 *      Author: Marco Maneta
 */

#include "Budget.h"

void Budget::MassBalanceError()
{
	double inputs = 0.0;
	double outputs = 0.0;
	double ds = 0.0;

	inputs = precipitation + initsnowpack + initponding + initvadose + initgravwater + initgrndwater;
	outputs = evaporation + ovlndflow + gwtrflow + leakage;
	ds = canopy + snowpack + ponding + vadose + gravwater + grndwater;

	if(inputs>0) MBErr = 100/inputs*(inputs-outputs - ds);
	        else MBErr = 0;


}
