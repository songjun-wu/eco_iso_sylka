/*
 * GrowRoots.cpp
 *
 *  Created on: Jul 1, 2010
 *      Author: Marco.Maneta
 */

#include "Forest.h"

int Forest::GrowRoots(UINT4 spec, UINT4 row, UINT4 col, REAL8 dt,
		bool suppress) {

	if (!suppress)
		_species[spec]._RootMass->matrix[row][col] += max<REAL8>(
				-0.95 * _species[spec]._Del_RootMass->matrix[row][col],
				_species[spec]._Del_RootMass->matrix[row][col]
						- _species[spec]._RootMass->matrix[row][col]
								* _species[spec].RootTurnover * dt);

	return EXIT_SUCCESS;

}
