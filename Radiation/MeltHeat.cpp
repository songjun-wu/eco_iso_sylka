/*
 * MeltHeat.cpp
 *
 *  Created on: Oct 1, 2010
 *      Author: Marco.Maneta
 */

#include"Basin.h"

double Basin::MeltHeat(Atmosphere &atm, Control &ctrl, const double &Ts, const double &swe, const double &M, int row, int col){


	double Ta = 0; // temperature of air
	double L1 = 0;
	double L2 = 0;

	Ta = atm.getTemperature()->matrix[row][col];

	if (Ts < 0)
		return 0.0;

	L1 = rho_w * lat_heat_fus * swe / ctrl.dt;
	L2 = rho_w * lat_heat_fus * M * Ts;

	if (L1 < L2)
		return -L1;
	else
		return -L2;

								//	-1*min<double>(rho_w * lat_heat_fus * swe / ctrl.dt, rho_w * lat_heat_fus * M * Ts);

}
