/*
 * ForestDestruct.cpp
 *
 *  Created on: May 5, 2010
 *      Author: Marco.Maneta
 */

#include "Forest.h"


Forest::~Forest(){

	if(_patches)
		delete _patches;

	if(_species)
		delete[] _species;




}
