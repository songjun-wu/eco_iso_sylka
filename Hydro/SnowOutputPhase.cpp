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
