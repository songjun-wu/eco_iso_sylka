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
	double psiae = _psi_ae->matrix[r][c];
	double lam = _BClambda->matrix[r][c];
	double p = 2 * lam + 3;
	double pnd = 0;

//depth of soil layers
	double depth = _soildepth->matrix[r][c];
	double d1 = _depth_layer1->matrix[r][c];
	double d2 = _depth_layer2->matrix[r][c];
	double d3 = depth - d1 - d2;

	double dS1dpsi1;
	double dS2dpsi2;
	double dS3dpsi3;

	double dK12dpsi1 = 0;
	double dK12dpsi2 = 0;
	double dK23dpsi2 = 0;
	double dK23dpsi3 = 0;
	double dK3dpsi3 = 0;

	colvec x(3);

	double S1 = (theta1 - thetar) / (thetas - thetar);
	double S2 = (theta2 - thetar) / (thetas - thetar);
	double S3 = (theta3 - thetar) / (thetas - thetar);

	double theta11 = S1*(thetas - thetar) + thetar;
	double theta21 = S2*(thetas - thetar) + thetar;
	double theta31 = S3*(thetas - thetar) + thetar;

	double Stg1 = 0;
	double Stg2 = 0;
	double Stg3 = 0;

	double dStg1 = 0;
	double dStg2 = 0;
	double dStg3 = 0;

    x[0] = psiae*powl(S1,-lam);
    x[1] = psiae*powl(S2,-lam);
    x[2] = psiae*powl(S3,-lam);

	colvec Fun(3);
	mat J = zeros < mat > (3, 3);
	colvec deltax(3);

	int k = 0;

	do {

	K1 = Ks * powl(S1, p);
	K2 = Ks * powl(S2, p);
	K3 = Ks * powl(S3, p);
	K12 =  (d1 * K1 + d2 * K2)/(d1 + d2);
	K23 =  (d2 * K2 + d3 * K3)/(d2 + d3);


	dS1dpsi1 = x[0]<psiae ? 0 : -powl(psiae/x[0],1/lam)/(lam*x[0]);
	dS2dpsi2 = x[1]<psiae ? 0 : -powl(psiae/x[1],1/lam)/(lam*x[1]);
	dS3dpsi3 = x[2]<psiae ? 0 : -powl(psiae/x[2],1/lam)/(lam*x[2]);


	dK12dpsi1 =  Ks*d1/(d1+d2)*p*powl(S1,p-1)*dS1dpsi1;
	dK12dpsi2 =  Ks*d2/(d1+d2)*p*powl(S2,p-1)*dS2dpsi2;
	dK23dpsi2 =  Ks*d2/(d2+d3)*p*powl(S2,p-1)*dS2dpsi2;
	dK23dpsi3 =  Ks*d3/(d2+d3)*p*powl(S3,p-1)*dS3dpsi3;
	dK3dpsi3  =  Ks*p*powl(S3,p-1)*dS3dpsi3;


	Fun[0] = theta11 + Stg1 - theta1 - (F  - K12 * dt) / d1;
	Fun[1] = theta21 + Stg2 - theta2 - (K12 - K23) * dt / d2;
	Fun[2] = theta31 + Stg3 - theta3 - (K23 - L * K3) * dt / d3;

	cout << "Fun: " << Fun << endl;

	J(0, 0) = dS1dpsi1*(thetas - thetar) + dStg1 + dt / d1 * dK12dpsi1;
	J(0, 1) = dt / d1 * dK12dpsi2;
	J(0, 2) = 0;
	J(1, 0) = -dt / d2 * dK12dpsi1;
	J(1, 1) = dS2dpsi2*(thetas - thetar) + dStg2 - dt / d2 * (dK12dpsi2 - dK23dpsi2);
	J(1, 2) = dt / d2 * dK23dpsi3;
	J(2, 0) = 0;
	J(2, 1) = -dt / d3 * dK23dpsi2;
	J(2, 2) = dS3dpsi3*(thetas - thetar) + dStg3 - dt / d3 * (dK23dpsi3 - L * dK3dpsi3);
    cout << "J" << J << endl;
	if (!solve(deltax, J, -Fun)) {
		cout << "Singular Jacobian found in Newton solver - soil water redistribution routine\n";
		return EXIT_FAILURE;
	}
	//	        cout <<"x: " <<  x << endl;
	x += deltax;

	S1 = x[0]<psiae ? 1 : powl(psiae/x[0], 1/lam);
	S2 = x[1]<psiae ? 1 : powl(psiae/x[1], 1/lam);
	S3 = x[2]<psiae ? 1 : powl(psiae/x[2], 1/lam);

	if(x[0]<psiae){
		Stg1 = 0.005*(psiae - x[0]);
	    dStg1 = 0.005;}
	else {Stg1=0;
	      dStg1=0;}
	if(x[1]<psiae){
			Stg1 = 0.005*(psiae - x[1]);
		    dStg1 = 0.005;}
	else {Stg2=0;
		      dStg2=0;}
	if(x[2]<psiae){
			Stg1 = 0.005*(psiae - x[2]);
		    dStg1 = 0.005;}
	else {Stg3=0;
		      dStg3=0;}




	theta11 = S1*(thetas - thetar) + thetar;// + std::max<double>(0, 0.005*(psiae - x[0]) );
	theta21 = S2*(thetas - thetar) + thetar;// +std::max<double>(0, 0.005*(psiae - x[1]) );
	theta31 = S3*(thetas - thetar) + thetar;// + std::max<double>(0, 0.005*(psiae - x[2]) );

	k++;
	cout << x << endl << deltax << endl;
	} while (norm(deltax, 2) > 0.00000001 && k < MAX_ITER);


		theta1 = theta11;
		theta2 = theta21;
		theta3 = theta31;

		K3 = Ks * powl(S3, p);
        leak =   L * K3;
}

