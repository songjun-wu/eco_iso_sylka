/*******************************************************************************
 * Ech2o, a spatially-distributed, ecohydrologic simulator
 * Copyright (c) 2016 Marco Maneta <marco.maneta@umontana.edu>
 *
 *     This file is part of ech2o, a hydrologic model developed at the 
 *     University of Montana.
 *
 *     Ech2o is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     Ech2o is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with Ech2o.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contributors:
 *    Marco Maneta
 *******************************************************************************/
/*
 * CalcFieldCapacity.cpp
 *
 *  Created on: Aug 20, 2010
 *      Author: Marco.Maneta
 */

#include "Basin.h"


int Basin::CalcFieldCapacity(){

	UINT4 r, c;

	UINT4 length = _vSortedGrid.cells.size();

#pragma omp parallel default(none)\
		private(  r,c), shared(length)
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
