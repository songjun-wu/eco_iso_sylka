/*
 * UpdateSnowPack.cpp
 *
 *  Created on: Nov 24, 2009
 *      Author: marco.maneta
 */

#include"Basin.h"

int Basin::UpdateSnowPack(Atmosphere &atm, Control &ctrl){

	int r, c;
	double dt = ctrl.dt; //secs

	for (unsigned int j = 0; j < _vSortedGrid.cells.size() ; j++)
	{
					r = _vSortedGrid.cells[j].row;
					c = _vSortedGrid.cells[j].col;

					if(atm.getTemperature()->matrix[r][c] < 0)
						_snow->matrix[r][c] += atm.getPrecipitation()->matrix[r][c] * dt;
					else
						_ponding->matrix[r][c] += atm.getPrecipitation()->matrix[r][c] * dt;


	}
	return EXIT_SUCCESS;
}
