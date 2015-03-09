/*
 * Infilt_Richards.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: marco
 */

#define ARMA_NO_DEBUG //disables armadillo bound checks for speed optimization
#include <armadillo>
#include "Basin.h"

using namespace arma;

inline double Kij(double Ksat,
		double theta1,
		double theta2,
		double thetar,
		double thetas,
		double d1,
		double d2,
		double c){

	return Ksat/(d1+d2) * (d1*powl((theta1-thetar )/(thetas - thetar),c) + d2*powl((theta2-thetar )/(thetas - thetar),c)  );
}

inline double psi_i(double Ksat,
		double theta1,
		double theta2,
		double thetar,
		double thetas,
		double d1,
		double d2,
		double c){

	return Ksat/(d1+d2) * (d1*powl((theta1-thetar )/(thetas - thetar),c) + d2*powl((theta2-thetar )/(thetas - thetar),c)  );
}

void Basin::Infilt_Richards(double &f, double &F, double &theta, double &pond, double &percolat, double dt, int r, int c) //time step
{



	double Ks = _Ksat->matrix[r][c];
	double psiae = _psi_ae->matrix[r][c];
	double lam = _BClambda->matrix[r][c];
	double thetar = _theta_r->matrix[r][c];
	double thetas = Basin::_porosity[r][c];

	double p = 2 +3*lam;

	double depth = _soildepth->matrix[r][c];

	//depth of soil layers
	double d1 = 0.1;
	double d2 = Basin::;
	double d3 = _soildepth->matrix[r][c] - (d1 + d2);

	//Distance between soil nodes
	double D1 = d1 * 0.5;
	double D2 = D1 + d2 * 0.5;
	double D3 = D2 + d3 * 0.5;

	//Relative water contents
	double S1=0, S2=0, S3=0;
	//Unsaturated Hydr Cond
	double K12=0, K23=0;
	//Soil suction head
	double psi1=0, psi2=0, psi3=0;


	f = K * (1 + (psi_1 - psi_s)/D1);

	rowvec Fun(3);
	mat J = zeros<mat>(3,3);
	rowvec x(3);

	//Initial guess is initial soil moisture content
   x[0] = theta1;
   x[1] = theta2;
   x[2] = theta3;

	do{

		S1 = (x[0] - thetar)/(thetas - thetar);
		S2 = (x[1] - thetar)/(thetas - thetar);
		S3 = (x[2] - thetar)/(thetas - thetar);

		K12 = Ks/(d1+d2) * (d1*powl(S1,c) + d2*powl(S2,c)  );
		K23 = Ks/(d2+d3) * (d2*powl(S2,c) + d3*powl(S3,c)  );

		psi1 = psiae * powl(S1, -lam);
		psi2 = psiae * powl(S1, -lam);
		psi3 = psiae * powl(S1, -lam);

		Fun[0] = d1*(theta1/dt) + d1*(x[0]/dt) + infilt - K12*(1 + (psi2 - psi1)/D2 ) ;
		Fun[1] = d2*(theta2/dt) + d2*(x[1/dt]) + K12*(1 + (psi2 - psi1)/D2 ) - K23*(1 + (psi3 - psi2)/D3 );
		Fun[0] = d3*(theta3/dt) + d3*(x[2]/dt) + K23*(1 + (psi3 - psi2)/D3 ) - d3*S3*L;

		deltaF = F1;
			fF = deltaF - Fp - Ks*(DT - tp) - psidtheta * log((psidtheta + deltaF) /(psidtheta + Fp));
			dfF = deltaF / (psidtheta + deltaF);
			F1 -= fF/dfF;
			k++;
	}while(fabs(deltaF - F1) > 0.00001 && k < MAX_ITER);

}
