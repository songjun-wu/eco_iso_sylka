/*
 * AdjustPrecip.cpp
 *
 *  Created on: Aug 20, 2010
 *      Author: Marco.Maneta
 */

#include "Atmosphere.h"

int Atmosphere::AdjustPrecip(){

	UINT4 r, c;


	for(UINT4 i = 0; i < _vSortedGrid.size(); i++)
		for (UINT4 j = 0; j < _vSortedGrid[i].cells.size() ; j++)
		{
			r = _vSortedGrid[i].cells[j].row;
			c = _vSortedGrid[i].cells[j].col;

			_Precip->matrix[r][c] *= _isohyet->matrix[r][c];
		}


	return EXIT_SUCCESS;

}
