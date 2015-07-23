/*
 * UpdateSoilMoist.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: Marco Maneta
 */
#include "Basin.h"

void Basin::SoilEvapotranspiration(REAL8 LE, //input latent heat
									REAL8 Ts, //input surface temperature
									REAL8 lambda,
									REAL8 rs,// input the potential exfiltration capacity
									REAL8 &etp, //output updated evapotranspiration
									REAL8 &theta,//output updated soil moisture
									REAL8 dt, //time step
									UINT4 r,
									UINT4 c)
{
	REAL8 ETP;
	REAL8 thetar = _theta_r->matrix[r][c];
	//REAL8 sd = _soildepth->matrix[r][c];
	REAL8 sd = _depth_layer1->matrix[r][c];
	REAL8 le = lambda; //Ts < 0 ?  lat_heat_vap + lat_heat_fus : lat_heat_vap;

	if(LE<0){
		etp = 0;
		return;
	}
	etp = min<REAL8>(1/rs , LE/(rho_w*le));
	ETP = etp * dt;

	if ((theta - thetar) * sd < ETP){ //makes sure we are not evaporating more that it is available above residual theta
		ETP = (theta - thetar) * sd;
		etp = ETP / dt;
	}



	theta -= ETP / sd;
}
