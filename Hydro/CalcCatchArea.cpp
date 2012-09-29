/*
 * CalcCatchArea.cpp
 *
 *  Created on: Jul 29, 2010
 *      Author: Marco.Maneta
 */

#include "Basin.h"


int Basin::CalcCatchArea(){

	UINT4 r, c, d, length;
	REAL8 area;

	length = _vSortedGrid.cells.size();

	for (UINT4 j = 0; j < length ; j++)
	{
					r = _vSortedGrid.cells[j].row;
					c = _vSortedGrid.cells[j].col;
					d = _vSortedGrid.cells[j].dir;

					area = _catcharea->matrix[r][c] + _dx * _dx;

					          switch (d) //add the previously calculated discharge to the downstream cell
					          {
								case 1:   _catcharea->matrix[r+1][c-1] = area; break;
					            case 2:   _catcharea->matrix[r+1][c]= area; break;
					            case 3:   _catcharea->matrix[r+1][c+1]= area; break;
					            case 4:   _catcharea->matrix[r][c-1]= area; break;
					            case 5: _catcharea->matrix[r][c] = area; break;//adds the area of the outlet cell
					            case 6:   _catcharea->matrix[r][c+1]= area; break;
					            case 7:   _catcharea->matrix[r-1][c-1]= area; break;
					            case 8:   _catcharea->matrix[r-1][c]= area; break;
					            case 9:   _catcharea->matrix[r-1][c+1]+= area; break;
					            default: return -1;
					          }

	}



	return EXIT_SUCCESS;
}
