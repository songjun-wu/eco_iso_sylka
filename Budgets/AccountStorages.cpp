/*
 * AccountStorages.cpp
 *
 *  Created on: Mar 22, 2010
 *      Author: Marco Maneta
 */
#include "Budget.h"

double Budget::AccountStorages(const grid *map, const Basin *b)
{

			UINT4 length = b->getSortedGrid().cells.size();
	        UINT4 r, c;
	        REAL8 result = 0;
	        REAL8 dx = b->getCellSize();

	        for (UINT4 i = 0; i< length; i++){

	         r = b->getSortedGrid().cells[i].row;
	         c = b->getSortedGrid().cells[i].col;

	          result += (map->matrix[r][c]*dx*dx);
	        }

	        return result;
}
