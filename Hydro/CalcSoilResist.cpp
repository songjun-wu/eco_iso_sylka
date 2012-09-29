/*
 * CalcSoilResist.cpp
 *
 *  Created on: Mar 5, 2010
 *      Author: Marco Maneta
 */

#include"Basin.h"

REAL8 Basin::CalcSoilResist(double &theta, int row, int col, UINT4 option){


	const double rmin = 3.8113e4; //minimum soil resistance in sm-1 PETERS-LIDARD et al 1997
	const double Cs = 13.515; //empirical parameter, no dimensions PETERS-LIDARD et al 1997

	double thetafc = _fieldcap->matrix[row][col];
	double thetar = _theta_r->matrix[row][col];

	double S = (theta - thetar) / (thetafc - thetar);

	if (theta < RNDOFFERR || thetafc < RNDOFFERR)
		return 0;

	if (option == 0)
		return rmin * exp(-Cs*(S));
	else if (option == 1)
		return ( expl(8.206-4.255*S) );
	else{
		cout << "Wrong option in the Soil_resistance_opt toggle switch. Please verify the configuration file" << endl;
		exit(EXIT_FAILURE);
	}



}
