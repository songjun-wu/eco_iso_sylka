/*
 * SensHeat.cpp
 *
 *  Created on: Nov 20, 2009
 *      Author: marco.maneta
 */

#include"Basin.h"

double Basin::SensHeat(Atmosphere &atm, double ra, const double &Ts, int row, int col){

	double airdens = 0; //density of air in kgm-3
	double Ta = 0; //temperature of air

					airdens = AirDensity(atm.getTemperature()->matrix[row][col]); //kgm-3
					Ta = atm.getTemperature()->matrix[row][col];

					return
							(1/(ra)) * airdens * spec_heat_air *(Ta - Ts);

}
