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

	// Values for CLM model formulation as per Sakaguchi and Zeng (2009), Effects of soil wetness, plant litter, and under-canopy atmospheric
	// stability on ground evaporation in the Community Land Model, JGR
	const double Do = 2.2e-5; //Molecular Diffusion coefficient of water vapor in the air (m2s-1), Sakaguchi and Zeng 2009, JGR
	const double w = 5; //empirical shape parameter
	const double e = 2.718; //empirical shape parameter
	double D = 0;
	double L = 0;

	double d1 = 0;

	double thetas = _porosity->matrix[row][col];
	double thetafc = _fieldcap->matrix[row][col];
	double thetar = _theta_r->matrix[row][col];


	double S = (theta - thetar) / (thetafc - thetar);

	if (theta < RNDOFFERR || thetafc < RNDOFFERR)
		return 0;

	if (option == 0)
		return 0;
	if (option == 1)
		return rmin * expl(-Cs*(S));
	else if (option == 2)
		return ( expl(8.206-4.255*S) );
	else if (option == 3){
		 d1 = _depth_layer1->matrix[row][col];
		 L = d1 * ( ( expl(powl(1 - (theta/thetas),w) ) - 1 ) / (e - 1) );
	     D = Do*thetas*thetas* powl(1 - (thetar/thetas), 2+3 * _BClambda->matrix[row][col]);
	     return L/D;
	}
	else{
		cout << "Wrong option in the Soil_resistance_opt toggle switch. Please verify the configuration file" << endl;
		exit(EXIT_FAILURE);
	}



}
