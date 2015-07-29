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


	double temp_pnd = pond;
	double K1, K12, K2, K23, K3;
	double Ss = 0.0;//0005;
	double thetafc = _fieldcap->matrix[r][c];
	double thetas = _porosity->matrix[r][c];
	double Ks = _Ksat->matrix[r][c];
	double L = _bedrock_leak->matrix[r][c];
	double psiae = _psi_ae->matrix[r][c];
	double lam = _BClambda->matrix[r][c];
	double p = 2 * lam + 3;
	double pnd = 0;

//depth of soil layers
	double depth = _soildepth->matrix[r][c];
	double d1 = _depth_layer1->matrix[r][c];
	double d2 = _depth_layer2->matrix[r][c];
	double d3 = depth - d1 - d2;

	double dK12dL1 = 0;
	double dK12dL2 = 0;
	double dK23dL2 = 0;
	double dK23dL3 = 0;
	double dK3dL3 = 0;

	colvec x(3);

	double L1 = theta1*d1;
	double L2 = theta2*d2;
	double L3 = theta3*d3;

	double Keff1 = 0;
	double Keff2 = 0;
	double Keff3 = 0;

    x[0] = L1;
    x[1] = L2;
    x[2] = L3;

    double S1 =std::max<double>(0, (L1/d1 - thetafc)/(thetas - thetafc));
    double S2 = std::max<double>(0, (L2/d2 - thetafc)/(thetas - thetafc));
    double S3 = std::max<double>(0, (L3/d3 - thetafc)/(thetas - thetafc));


	double dS1L1 = 1/(d1*(thetas - thetafc));
	double dS2L2 = 1/(d2*(thetas - thetafc));
	double dS3L3 = 1/(d3*(thetas - thetafc));

	colvec Fun(3);
	mat J = zeros < mat > (3, 3);
	colvec deltax(3);

	int k = 0;

	do {

	Keff1 = std::fabs(x[0] - thetafc*d1)/dt;
	Keff2 = std::fabs(x[1] - thetafc*d2)/dt;
	Keff3 = std::fabs(x[2] - thetafc*d3)/dt;

	K1 = std::min<double>(Ks * powl(S1, p), Keff1);
	K2 = std::min<double>(Ks * powl(S2, p), Keff2);
	K3 = std::min<double>(Ks * powl(S3, p), Keff3);
	K12 =  std::min<double>((d1 * K1 + d2 * K2)/(d1 + d2), Keff1);
	K23 =  std::min<double>((d2 * K2 + d3 * K3)/(d2 + d3), Keff1);

	dK12dL1 =  S1> 1 ? 0 : Ks*d1/(d1+d2)*p*powl(S1,p-1)*dS1L1;
	dK12dL2 =  S2> 1 ? 0 : Ks*d2/(d1+d2)*p*powl(S2,p-1)*dS2L2;
	dK23dL2 =  S2> 1 ? 0 : Ks*d2/(d2+d3)*p*powl(S2,p-1)*dS2L2;
	dK23dL3 =  S3> 1 ? 0 : Ks*d3/(d2+d3)*p*powl(S3,p-1)*dS3L3;
	dK3dL3  =  S3> 1 ? 0 : Ks*p*powl(S3,p-1)*dS3L3;

	if(K1 == Keff1)
		dK12dL1 = 1/dt;
	if(K2 == Keff2){
		dK12dL2 = 1/dt;
		dK23dL2 = 1/dt;}
	if(K3 == Keff3){
		dK23dL3 = 1/dt;
		dK3dL3 = 1/dt;}


	Fun[0] = x[0] - L1  - (0  - K12 * dt);
	Fun[1] = x[1] - L2  - (K12 - K23) * dt;
	Fun[2] = x[2] - L3  - (K23 - L * K3) * dt;

	//cout << "Fun: " << Fun << endl;

	J(0, 0) = 1 + dt * dK12dL1;
	J(0, 1) = dt * dK12dL2;
	J(0, 2) = 0;
	J(1, 0) = -dt  * dK12dL1;
	J(1, 1) = 1 - dt * (dK12dL2 - dK23dL2);
	J(1, 2) = dt * dK23dL3;
	J(2, 0) = 0;
	J(2, 1) = -dt * dK23dL2;
	J(2, 2) = 1 - dt * (dK23dL3 - L * dK3dL3);
    cout << "J" << J << endl;

	if (!solve(deltax, J, -Fun)) {
		cout << "Singular Jacobian found in Newton solver - soil water redistribution routine\n";
		return EXIT_FAILURE;
	}
	//	        cout <<"x: " <<  x << endl;
	x += deltax;

	S1 = std::max<double>(0,(x[0]/d1 - thetafc)/(thetas - thetafc));
	S2 =std::max<double>(0, (x[1]/d2 - thetafc)/(thetas - thetafc));
	S3 = std::max<double>(0,(x[2]/d3 - thetafc)/(thetas - thetafc));

	k++;
//	cout << x << endl << deltax << endl;
	} while (norm(deltax, 2) > 0.00000001 && k < MAX_ITER);
	if (k >= MAX_ITER)
							cout << "WARNING: Max no iterations reached for G&A solution " << endl;


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

		K3 = Ks * powl(std::max<double>(0,S3), p);
        leak =   L * K3;


}

