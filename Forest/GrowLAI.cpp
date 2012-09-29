/*
 * GrowLAI.cpp
 *
 *  Created on: Jul 1, 2010
 *      Author: Marco.Maneta
 */

#include "Forest.h"

int Forest::GrowLAI(UINT4 spec, UINT4 row, UINT4 col, REAL8 dt){

	REAL8 SLA = _species[spec].SLA;

	_species[spec]._LAI->matrix[row][col] += max<REAL8>(-0.95*_species[spec]._LAI->matrix[row][col],_species[spec]._Del_FoliageMass->matrix[row][col] * SLA -
			_species[spec].LeafTurnover * dt * _species[spec]._LAI->matrix[row][col]);

	return EXIT_SUCCESS;

}
