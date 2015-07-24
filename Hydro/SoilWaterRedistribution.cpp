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
		double &theta2, double &theta3, double &pond, double dt,
		int r, int c) {


	double K12, K23, K3;
	double thetar = _theta_r->matrix[r][c];
	double thetas = _porosity->matrix[r][c];
	double Ks = _Ksat->matrix[r][c];
	double L = _bedrock_leak->matrix[r][c];
	double p = 2 * _BClambda->matrix[r][c] + 3;

//depth of soil layers
	double depth = _soildepth->matrix[r][c];
	double d1 = _depth_layer1->matrix[r][c];
	double d2 = _depth_layer2->matrix[r][c];
	double d3 = depth - d1 - d2;

	double S1 = 0;
	double S2 = 0;
	double S3 = 0;

	double dK12dx1 = 0;
	double dK12dx2 = 0;
	double dK23dx2 = 0;
	double dK23dx3 = 0;
	double dK3dx3 = 0;

	colvec x(3);

	x[0] = theta1;
	x[1] = theta2;
	x[2] = theta3;

	colvec Fun(3);
	mat J = zeros < mat > (3, 3);
	colvec deltax(3);

	int k = 0;

	do {



	S1 = (x[0] - thetar) / (thetas - thetar);
	S2 = (x[1] - thetar) / (thetas - thetar);
	S3 = (x[2] - thetar) / (thetas - thetar);

	K12 = Ks / (d1 + d2) * (d1 * powl(S1, p) + d2 * powl(S2, p));
	K23 = Ks / (d2 + d3) * (d2 * powl(S2, p) + d3 * powl(S3, p));
	K3 = Ks * powl(S3, p);

	dK12dx1 = Ks * d1 * p * powl(S1, p - 1) / ((d1 + d2) * (thetas - thetar));
	dK12dx2 = Ks * d2 * p * powl(S2, p - 1) / ((d1 + d2) * (thetas - thetar));
	dK23dx2 = Ks * d2 * p * powl(S2, p - 1) / ((d2 + d3) * (thetas - thetar));
	dK23dx3 = Ks * d3 * p * powl(S3, p - 1) / ((d2 + d3) * (thetas - thetar));
	dK3dx3 = Ks * p * powl(S3, p - 1) / (thetas - thetar);

	Fun[0] = x[0] - theta1 - (F - K12 * dt) / d1;
	Fun[1] = x[1] - theta2 - (K12 - K23) * dt / d2;
	Fun[2] = x[2] - theta3 - (K23 - L * K3) * dt / d3;

	J(0, 0) = 1 + dt / d1 * dK12dx1;
	J(0, 1) = dt / d1 * dK12dx2;
	J(0, 2) = 0;
	J(1, 0) = -dt / d2 * dK12dx1;
	J(1, 1) = 1 - dt / d2 * (dK12dx2 - dK23dx2);
	J(1, 2) = dt / d2 * dK23dx3;
	J(2, 0) = 0;
	J(2, 1) = -dt / d3 * dK23dx2;
	J(2, 2) = 1 - dt / d3 * (dK23dx3 - L * dK3dx3);

	if (!solve(deltax, J, -Fun)) {
		cout << "Singular Jacobian found in Newton solver - soil water redistribution routine\n";
		return 1;
	}
	//	        cout <<"x: " <<  x << endl;
	x += deltax;
	} while (norm(deltax, 2) > 0.00000001 && k < MAX_ITER);
}

