/*
 * snwwheat.cpp
 *
 *  Created on: Nov 20, 2009
 *      Author: marco.maneta
 */

#include"Basin.h"

double Basin::SnowHeat(Atmosphere &atm, Control &ctrl, const double &Ts, int row, int col){

	double Ts_old = 0; // temperature of surface at time step t-1
	double h = 0; // depth of snow water equivalent
	double R = 0; // energy advected by rain Wm-2
	float dt = ctrl.dt;

					Ts_old = _Temp_s_old->matrix[row][col];
					h = _snow->matrix[row][col];

					return
						 	-spec_heat_ice * rho_w * h * (Ts - Ts_old) * (1 / dt) - R; // TODO: solve the energy advected by rain
																					   //TODO: change the energy differential to include temperature of snowpack

}
