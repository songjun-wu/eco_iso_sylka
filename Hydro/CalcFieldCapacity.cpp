/*
 * CalcFieldCapacity.cpp
 *
 *  Created on: Aug 20, 2010
 *      Author: Marco.Maneta
 */

#include "Basin.h"


int Basin::CalcFieldCapacity(){

	UINT4 r, c, length;

	length = _vSortedGrid.cells.size();

#pragma omp parallel default(none)\
		private(  r,c,length)
	for (UINT4 j = 0; j < length ; j++)
	{
					r = _vSortedGrid.cells[j].row;
					c = _vSortedGrid.cells[j].col;

					_fieldcap->matrix[r][c] =
							powl(_psi_ae->matrix[r][c] / 3.36 ,1/_BClambda->matrix[r][c])
							* (_porosity->matrix[r][c] - _theta_r->matrix[r][c])
							+ _theta_r->matrix[r][c];

	}



	return EXIT_SUCCESS;
}
