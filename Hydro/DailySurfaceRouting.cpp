/*
 * DailySurfaceRouting.cpp
 *
 *  Created on: Jul 28, 2010
 *      Author: Marco.Maneta
 */

#include "Basin.h"


int Basin::DailySurfaceRouting(Atmosphere &atm, Control &ctrl){

	UINT4 r, c, d, length;
	REAL4 dt = ctrl.dt; //time step
	REAL8 ponding = 0;
	REAL8 theta = 0;
	REAL8 f = 0;
	REAL8 F = 0;
	REAL8 ca = 0; //catchment area
	REAL8 gw = 0; //gravitatinoal water

	length = _vSortedGrid.cells.size();
	_dailyOvlndOutput.cells.clear();

	for (UINT4 j = 0; j < length ; j++)
	{
					r = _vSortedGrid.cells[j].row;
					c = _vSortedGrid.cells[j].col;
					d = _vSortedGrid.cells[j].dir;

					ponding = _ponding->matrix[r][c];
					theta = _soilmoist->matrix[r][c];
					ca = _catcharea->matrix[r][c];
					gw = _GravityWater->matrix[r][c];

					Infilt_GreenAmpt(f, F, theta, ponding, gw, dt, r, c);

					_soilmoist->matrix[r][c] = theta;
					_GravityWater->matrix[r][c] = gw;

					          switch (d) //add the previously calculated discharge to the downstream cell
					          {
								case 1:   _ponding->matrix[r+1][c-1] += ponding; break;
					            case 2:   _ponding->matrix[r+1][c]+= ponding; break;
					            case 3:   _ponding->matrix[r+1][c+1]+= ponding; break;
					            case 4:   _ponding->matrix[r][c-1]+= ponding; break;
					            case 5: _dailyOvlndOutput.cells.push_back(cell(r, c, ponding * _dx *_dx / dt)); break;//if it is the outlet store the overland water output
					            case 6:   _ponding->matrix[r][c+1]+= ponding; break;
					            case 7:   _ponding->matrix[r-1][c-1]+= ponding; break;
					            case 8:   _ponding->matrix[r-1][c]+= ponding; break;
					            case 9:   _ponding->matrix[r-1][c+1]+= ponding; break;
					            default: return -1;
					          }

					   _ponding->matrix[r][c] = 0.0;

	}



	return EXIT_SUCCESS;
}

