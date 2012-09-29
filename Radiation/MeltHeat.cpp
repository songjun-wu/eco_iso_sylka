/*
 * MeltHeat.cpp
 *
 *  Created on: Oct 1, 2010
 *      Author: Marco.Maneta
 */

#include"Basin.h"

double Basin::MeltHeat(Atmosphere &atm, Control &ctrl, const double &Ts, const double &swe, const double &M, int row, int col){


	double Ta = 0; // temperature of air

	Ta = atm.getTemperature()->matrix[row][col];

					return
							Ts < 0.0 ?
									0.0 :
									-1*min<double>(rho_w * lat_heat_fus * swe / ctrl.dt, rho_w * lat_heat_fus * M * Ts);

}
