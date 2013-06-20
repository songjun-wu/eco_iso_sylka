/*
 * LatHeat.cpp
 *
 *  Created on: Nov 19, 2009
 *      Author: marco.maneta
 */

#include"Basin.h"

double Basin::LatHeat(Atmosphere &atm, double soilrelhumid, double ra, double rs, double rc, const double &Ts, int row, int col){

	double airdens = 0; //density of air in kgm-3
	double es = 0; //saturated vapor pressure at temperature Ts
	double ea = 0; //vapor pressure at air temperature
	double gamma = 0;
	double z = 0;

					airdens = AirDensity(atm.getTemperature()->matrix[row][col]); //kgm-3
					es = SatVaporPressure(Ts); //vapor pressure at temp Ts in Pa
					ea = SatVaporPressure(atm.getTemperature()->matrix[row][col]) * atm.getRelativeHumidty()->matrix[row][col]; //vapor pressure at air temp in Pa
					z = _DEM->matrix[row][col];
					gamma = PsychrometricConst(101325, z); //todo: replace with Pressure when implemented

					return
							(1/gamma) * (1/(ra + rs) + rc) * airdens * spec_heat_air * soilrelhumid *(ea - es);
						//	(1/((ra + rs + rc) * gamma)) * airdens * spec_heat_air *(ea - es);

}
