/*
 * NetRadCanopy.cpp
 *
 *  Created on: Jul 9, 2010
 *      Author: Marco.Maneta
 */

#include"Forest.h"

double Forest::NetRadCanopy(Atmosphere &atm, const double &Ts, REAL8 emiss, REAL8 albedo, REAL8 Kbeers, REAL8 lai, int row, int col){

	//	double ea = 0; //emissivity of air
	//		ea = AirEmissivity(atm.getTemperature()->matrix[row][col]);

					return	atm.getIncomingShortWave()->matrix[row][col] * (1 - albedo) * ( 1 - expl(-Kbeers * lai) ) +
							emiss*atm.getIncomingLongWave()->matrix[row][col] -
							emiss * stefboltz * powl(Ts + 273.2, 4);/* - (1 - emiss)* atm.getIncomingLongWave()->matrix[row][col];*/

}
