/*
 * LatHeatCanopy.cpp
 *
 *  Created on: Jul 9, 2010
 *      Author: Marco.Maneta
 */

#include "Forest.h"

double Forest::LatHeatCanopy(Atmosphere &atm, double soilrelhumid, double ra, const double &Ts, int row, int col){

	double airdens = 0; //density of air in kgm-3
	double es = 0; //saturated vapor pressure at temperature Ts
	double ea = 0; //vapor pressure at air temperature
	double gamma = 0;

					airdens = AirDensity(atm.getTemperature()->matrix[row][col]); //kgm-3
					es = SatVaporPressure(Ts) * soilrelhumid; //saturated vapor pressure at temp Ts in Pa
					ea = SatVaporPressure(atm.getTemperature()->matrix[row][col]) * atm.getRelativeHumidty()->matrix[row][col]; //vapor pressure at air temp in Pa
					gamma = PsychrometricConst(101325); // replace with Pressure when implemented

					return
							(1/(ra * gamma)) * airdens * spec_heat_air *(ea - es);

}
