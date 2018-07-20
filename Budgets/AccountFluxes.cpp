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
 * AccountInputFluxes.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: Marco Maneta
 */
#include "Budget.h"

double Budget::AccountFluxes(const grid *map, const Basin *b) {

	UINT4 length = b->getSortedGrid().cells.size();
	UINT4 r, c;
	REAL8 result = 0;
	REAL8 dx = b->getCellSize();

	#pragma omp parallel for\
		default(shared) private(r,c) \
		reduction (+:result)

	for (UINT4 i = 0; i < length; i++) {

		r = b->getSortedGrid().cells[i].row;
		c = b->getSortedGrid().cells[i].col;

		result += (map->matrix[r][c] * dx * dx * dt);
	}

	return result;
}

double Budget::AccountFluxes(const grid *map, const Atmosphere *b) {

	UINT4 zones = b->getSortedGrid().size();
	UINT4 r, c;
	REAL8 result = 0;
	REAL8 dx = b->getCellSize();

	#pragma omp parallel for\
		default(shared) private(r,c) \
		reduction (+:result)

	for (UINT4 i = 0; i < zones; i++)
		for (UINT4 j = 0; j < b->getSortedGrid()[i].cells.size(); j++) {

			r = b->getSortedGrid()[i].cells[j].row;
			c = b->getSortedGrid()[i].cells[j].col;

			result += (map->matrix[r][c] * dx * dx * dt);
		}

	return result;
}

double Budget::AccountFluxes(const vectCells *timeseries, const Basin *b) {

	UINT4 length = timeseries->cells.size(); //b->getSortedGrid().cells.size();

	REAL8 result = 0;

	#pragma omp parallel for \
		reduction (+:result)

	for (UINT4 i = 0; i < length; i++) {

		result += timeseries->cells[i].val * dt;
	}

	return result;
}

// ---------------------------------------------------------------------------------------------
