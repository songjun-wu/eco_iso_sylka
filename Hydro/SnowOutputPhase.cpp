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
 * SnowOutputPhase.cpp
 *
 *  Created on: Nov 25, 2009
 *      Author: marco.maneta
 */

#include"Basin.h"

double Basin::SnowOutput(Atmosphere &atm, Control &ctrl, const double &meltheat, int row, int col) {

	double h = 0; // depth of snow water equivalent
	double dh = 0; // depth of snow output - decrease in snow water equivalent depth

	h = _snow->matrix[row][col] < RNDOFFERR ? 0.0 : _snow->matrix[row][col];

		_snow->matrix[row][col] = h;

	if (h > RNDOFFERR && meltheat < RNDOFFERR) //if there is snow pack and latent heat of melt
		_Temp_s->matrix[row][col];//_Temp_s->matrix[row][col] = 0;
	else
		return 0.0;

		dh = -meltheat * ctrl.dt / (lat_heat_fus*rho_w); //transform latent heat of melt into snowmelt depth

	if (dh > h)//if this water energy equivalent is larger than the available snow pack
		dh = h; //the water output equals the water in the remaining snowpack


	_snow->matrix[row][col] -= dh;

	return dh;

}
