/*
 * SoilWaterRedistribution.cpp
 *
 *  Created on: Jul 22, 2015
 *      Author: marco
 */

#define ARMA_NO_DEBUG //disables armadillo bound checks for speed optimization
#include <armadillo>
#include"Basin.h"

using namespace arma;

int Basin::SoilWaterRedistribution(const double &F, double &theta1,
		double &theta2, double &theta3, double &pond, double &leak,  double dt,
		int r, int c) {



	double K1, K12, K2, K23, K3;
	double thetar = _theta_r->matrix[r][c];
	double thetas = _porosity->matrix[r][c];
	double Ks = _Ksat->matrix[r][c];
	double L = _bedrock_leak->matrix[r][c];

//depth of soil layers
	double depth = _soildepth->matrix[r][c];
	double d1 = _depth_layer1->matrix[r][c];
	double d2 = _depth_layer2->matrix[r][c];
	double d3 = depth - d1 - d2;

	colvec x(3);

	double L1 = theta1*d1;
	double L2 = theta2*d2;
	double L3 = theta3*d3;

    x[0] = L1;
    x[1] = L2;
    x[2] = L3;

	double a = dt*Ks/(thetas-thetar);

	colvec Fun(3);
	mat J = zeros < mat > (3, 3);
	colvec deltax(3);


	Fun[0] = L1 + a*thetar;
	Fun[1] = L2;
	Fun[2] = L3 + (L - 1)*a*thetar;

	//cout << "Fun: " << Fun << endl;

	J(0, 0) = 1 + a/(d1+d2);
	J(0, 1) =  a/(d1+d2);
	J(0, 2) = 0;
	J(1, 0) = -a/(d1+d2);
	J(1, 1) = 1 - a/(d1+d2) + a/(d2+d3);
	J(1, 2) = a/(d2+d3);
	J(2, 0) = 0;
	J(2, 1) = -a/(d2+d3);
	J(2, 2) = 1 - a/(d2+d3) + L * a/d3;
    cout << "J" << J << endl;

	if (!solve(x, J, Fun)) {
		cout << "Singular matrix in  soil water redistribution routine\n";
		return EXIT_FAILURE;
	}

	cout <<"x: " <<  x << endl;

	K1 = Ks * (x[0]/d1 - thetar)/(thetas - thetar);
	K2 = Ks * (x[1]/d2 - thetar)/(thetas - thetar);
	K3 = Ks * (x[2]/d3 - thetar)/(thetas - thetar);



		theta1 = x[0]/d1;
		theta2 = x[1]/d2;
		theta3 = x[2]/d3;

		//pond -=F;
		if(theta3>thetas){
					theta2 += (theta3 - thetas) * d1/d2;
					theta3 = thetas;}
		if(theta2>thetas){
							theta1 += (theta2 - thetas) * d2/d1;
							theta2 = thetas;}
		if(theta1>thetas){
			pond += -(thetas - theta1) * d1;
			theta1 = thetas;}

		K3 = Ks * (x[2]/d3 - thetar)/(thetas - thetar);
        leak =   L * K3;


}

