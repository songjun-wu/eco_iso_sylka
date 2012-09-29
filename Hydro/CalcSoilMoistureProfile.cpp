/*
 * CalcSoilMoistureProfile.cpp
 *
 *  Created on: Jul 26, 2011
 *      Author: Marco.Maneta
 *
 *      This function derives a soil moisture profile from the average soil moisture assuming the soil is at hydrostatic equilibrium (except when it is raining).
 *      Hydrolstatic equilibrium depends on soil characteristics as per the Brooks and Corey Formula. Average soil moisture is calculated by integrating the hydrostatic
 *      moisture profile and solving for the equivalent depth to saturation (H) that corresponds to the calculated average soil moisture content
 *
 *      Returns the average soil moisture of the first 10 cms of the soil and by reference the equivalent depth to saturation
 *
 */

#include"Basin.h"

void Basin::CalcSoilMoistureProfile(Atmosphere &atm, Control &ctrl, REAL8 theta, UINT4 row, UINT4 col){

	REAL8 d =_soildepth->matrix[row][col];
	REAL8 poros = _porosity->matrix[row][col];
	REAL8 theta_r = _theta_r->matrix[row][col];
	REAL8 psi = _psi_ae->matrix[row][col];
	REAL8 lambda = _BClambda->matrix[row][col];
	REAL8 psilam = powl(psi,lambda);
	REAL8 H = _EquivDepth2Sat->matrix[row][col]+0.1; //equivalent depth to saturation (m). Initial estimate is the old value for H + 0.1 to avoid initial value of 0
	REAL8 H1 = H; //updated equivalent depth to saturation (m)
	REAL8 u = d; // depth of the unsaturated layer needed to integrate the piecewise function
	REAL8 fH, dfH;
	UINT4 k = 0;

	//TODO: prepare case of lambda = 1, which results in a different integrated function for soil moisture
	//for the time being, if lambda =1 change it to 0.95 (lambda shouldnt be that high anyway)

	if (lambda == 1) lambda = 0.95;

	//if we have a fully saturated soil, then there is no point in calculating any soil moisture profile

	if ( ( (poros - theta) * d ) < (psi + H)) {
		_soilmoist10cm->matrix[row][col] = theta;
		_EquivDepth2Sat->matrix[row][col] = (poros - theta) * d;
		return;
	}



	do{ //uses N-R to calculate the corresponding depth to the equivalent water table for the given average soil moisture

    H = H1;
    if (H==d) H+=0.01; //in the unlikely case H equals d, make it 1 cm deeper to avoid division by zero
    if( H > 1000){ //if the depth water table is larger than some large arbitrary depth (m), assume soil moisture at the topsoil equals average soil moisture and return
    	_soilmoist10cm->matrix[row][col]=theta;
  		_EquivDepth2Sat->matrix[row][col] = H1;
  		return;
    }
	u = ((H - d) > psi) ? d : H - psi;

	fH = (1/d) * ((
			( ( (poros - theta_r) * psilam * ( (H - u) * pow(H,lambda) - H * pow(H-u, lambda) )  ) /
			  ( (lambda - 1) * pow(H-u, lambda) * pow(H, lambda) )
			) + theta_r * u )
			 + poros * (d - u) ) - theta ;
	dfH =  ((H-d) > psi) ? (1/d) * -( (poros - theta_r) * ( pow(psi/(H-u), lambda) - pow(psi/(H), lambda)) ) : -poros/d;

	H1 = H - fH / dfH;

	k++;

	}while (fabs(H-H1) > 0.01 && k < MAX_ITER);

	if (k>=MAX_ITER)
			std::cout << "WARNING: non-convergence soil moisture profile at cell row: " << row << " col: " << col << " closure err: " << (H1 - H) << endl;


	//calculates average soil moisture of first 10 cm of soil given teh calculated depth to the water table
	d = 0.1;
	u = ((H1 - d) > psi) ? d : H1 - psi; //

	 _soilmoist10cm->matrix[row][col] =
			(1 / d) * (((((poros - theta_r) * psilam * ((H1 - u) * powl(H1,
			lambda) - H1 * powl(H1 - u, lambda))) / ((lambda - 1) * powl(H1 - u,
			lambda) * powl(H1, lambda))) + theta_r * u) + poros * (u - d));

	 //stores the calculated depth to saturation in case we need it
	 _EquivDepth2Sat->matrix[row][col] = H1;


}
