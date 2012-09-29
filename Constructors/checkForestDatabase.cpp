/*
 * checkForestDatabase.cpp
 *
 *  Created on: Mar 29, 2012
 *      Author: marco
 */

#include "Forest.h"

void Forest::checkForestDatabase()
{
	UINT4 i = 0;
	try{
	for(i = 0; i < _Nsp-1; i++){ // substract 1 because _Nsp includes bare soil

		/*
		 * PARAMETER FILE CHECKS
		 */

		//Checks if tmax is larger than tmin and that topt is in between
		if(_species[i].TempMax < _species[i].TempMin)
			throw("Parameter TMin is larger than TMax for species ");
		if( (_species[i].TempOpt > _species[i].TempMax) || (_species[i].TempOpt < _species[i].TempMin) )
			throw("Optimal temperature parameter is out of the Tmin - Tmax range given for species ");


		/*
		 * STATE VARIABLE CHECKS
		 *
		 */

	}
	}catch(std::string &e){

		cerr << "error: " << e << i;
		throw;

	}


}
