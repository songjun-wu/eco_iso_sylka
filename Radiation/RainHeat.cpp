/*
 * RainHeat.cpp
 *
 *  Created on: Jun 22, 2011
 *      Author: Marco.Maneta
 */

#include"Basin.h"

double Basin::RainHeat(Atmosphere &atm, double R, int row, int col){


	double Ta = 0; // temperature of air

	Ta = atm.getTemperature()->matrix[row][col];

					return
						rho_w * spec_heat_water * R * Ta;  //returns heat advected by rain in Wm-2. R is rainfall intensity in ms-1

}
