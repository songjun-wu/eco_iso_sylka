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
 *    Marco Maneta, Sylvain Kuppel
 *******************************************************************************/
/*
 * IncrementAge.cpp
 *
 *  Created on: Nov 15, 2016
 *      Author: Sylvain Kuppel
 */

#include "Tracking.h"

int Tracking::IncrementAge(Basin &bsn, Control &ctrl){

	UINT4 r, c;
	REAL8 dt = ctrl.dt / 86400 ; // units: days

#pragma omp parallel default(shared) private(r,c)
	{

#pragma omp for nowait
		for (unsigned int j = 0; j < bsn.getSortedGrid().cells.size(); j++) {

			r = bsn.getSortedGrid().cells[j].row;
			c = bsn.getSortedGrid().cells[j].col;

			//_Agecanopy->matrix[r][c] += dt; // Canopy interception storage

			if(fabs(bsn.getSnowWaterEquiv()->matrix[r][c])>RNDOFFERR)
				_Agesnowpack->matrix[r][c] += dt; // Snowpack
			else
				_Agesnowpack->matrix[r][c] = 0;

			if(fabs(bsn.getPondingWater()->matrix[r][c])>RNDOFFERR)
				_Agesurface->matrix[r][c] += dt; // Ponding
			else
				_Agesurface->matrix[r][c] = 0;

			_Agesoil1->matrix[r][c] += dt; // Vadose layer 1
			_Agesoil2->matrix[r][c] += dt; // Vadose layer 2
			_Agesoil3->matrix[r][c] += dt; // Vadose layer 3
			//_AgesoilAv->matrix[r][c] += dt; // Vadose average

			if(fabs(bsn.getGrndWater()->matrix[r][c])>RNDOFFERR)
				_Agegroundwater->matrix[r][c] += dt; // Groundwater
			else
				_Agegroundwater->matrix[r][c] = 0;

//			if (ctrl.sw_channel && bsn.getChannelWidth()->matrix[r][c] > 0)
//				_Agechannel->matrix[r][c] += dt; // Channel

		}
	}
	return EXIT_SUCCESS;
}
