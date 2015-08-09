/*
 * CalculateInitialStreamStorage.cpp
 *
 *  Created on: Aug 8, 2015
 *      Author: marco
 */


#include "Basin.h"

int Basin::CalcInitialStreamStorage(){

	UINT4 r, c, length;
	REAL8 w, n, a, sqrtS, Q;

	length = _vSortedGrid.cells.size();

#pragma omp parallel default(none)\
		private(  r,c,length, w, n, a, sqrtS,Q)
	for (UINT4 j = 0; j < length ; j++)
	{
					r = _vSortedGrid.cells[j].row;
					c = _vSortedGrid.cells[j].col;

					sqrtS = powl(_slope->matrix[r][c], 0.5);

					w = _channelwidth->matrix[r][c];
			        n = _Manningn->matrix[r][c];
					a = powl(powl(w,0.67)*n/sqrtS, 0.6); //wetted perimeter is approximated with channel width
					Q = _Disch_old->matrix[r][c];

					_ponding->matrix[r][c] = (w > 0) && (Q > 0) ? a * powl(Q, 0.6)/_dx : 0.0;

	}



	return EXIT_SUCCESS;
}
