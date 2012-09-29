/*
 * SensHeatCanopy.cpp
 *
 *  Created on: Jul 9, 2010
 *      Author: Marco.Maneta
 */

#include"Forest.h"

double Forest::SensHeatCanopy(Atmosphere &atm, double ra, const double &Ts, int row, int col){

	double airdens = 0; //density of air in kgm-3
	double Ta = 0; //temperature of air

					airdens = AirDensity(atm.getTemperature()->matrix[row][col]); //kgm-3
					Ta = atm.getTemperature()->matrix[row][col];

					return
							(1/(ra)) * airdens * spec_heat_air *(Ta - Ts);

}
