/*
 * NetRad.cpp
 *
 *  Created on: Nov 18, 2009
 *      Author: marco.maneta
 */

#include"Basin.h"

double Basin::NetRad(Atmosphere &atm, const double &Ts, REAL8 Kbeers, REAL8 lai, REAL8 ec, REAL8 Tc, int row, int col){

	//	double ea = 0; //emissivity of air
		double es = 0; //emisivity of surface
		double albedo = 0;
	//		ea = AirEmissivity(atm.getTemperature()->matrix[row][col]);
			es = _emiss_surf->matrix[row][col];
			albedo = _snow->matrix[row][col] > RNDOFFERR ? max_snow_albedo : _albedo->matrix[row][col]; //TODO: include albedo decay with time and with covered area (covered area a function of snowdepth?)

					return	atm.getIncomingShortWave()->matrix[row][col] * (1 - albedo) * ( expl(-1*Kbeers * lai) )
							+ es * (1 - ec) * atm.getIncomingLongWave()->matrix[row][col]
							+ es * ec * stefboltz * powl(Tc + 273.2, 4)
							- es * stefboltz * powl(Ts + 273.2, 4);
					        /*- (1 - es) * ( (1 - ec) * atm.getIncomingLongWave()->matrix[row][col]
							                  + ec * stefboltz * powl(Tc + 273.2, 4) );*/



}
