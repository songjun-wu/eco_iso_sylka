/*
 * SoilWaterRedistribution.cpp
 *
 *  Created on: Jul 22, 2015
 *      Author: marco
 */

#define ARMA_NO_DEBUG //disables armadillo bound checks for speed optimization
//#include <armadillo>
#include"Basin.h"

//using namespace arma;

int Basin::SoilWaterRedistribution(const double &F, double &theta1,
		double &theta2, double &theta3, double &pond, double &leak,  double dt,
		int r, int c) {



	double K1, K12, K2, K23, K3;
	double thetar = _theta_r->matrix[r][c];
	double thetafc = _fieldcap->matrix[r][c];
	double thetas = _porosity->matrix[r][c];
	double Ks = _Ksat->matrix[r][c];
	double L = _bedrock_leak->matrix[r][c];

//depth of soil layers
	double depth = _soildepth->matrix[r][c];
	double d1 = _depth_layer1->matrix[r][c];
	double d2 = _depth_layer2->matrix[r][c];
	double d3 = depth - d1 - d2;

	double  x[3] = {};

	double L1 = theta1*d1;
	double L2 = theta2*d2;
	double L3 = theta3*d3;

    x[0] = L1;
    x[1] = L2;
    x[2] = L3;

	double a = dt*Ks/(thetas-thetar);

	if(x[0]/d1>thetafc){
		x[0] =( L1 + a* thetar) / (1 + a/d1);
	//check if too much drainage
	if(x[0]/d1 < thetafc)
		x[0] = thetafc * d1;

	L2 += L1 - x[0];
	x[1]=L2;}

	if(L2/d2>thetafc){
		x[1] =(L2 + a* thetar) / (1 + a/d2);
	//check if too much drainage
	if(x[1]/d2 < thetafc)
		x[1] = thetafc * d2;

	L3 += L2 - x[1];
	x[2]=L3;}

	if(L3/d3>thetafc){
		x[2] =(L3 + L*a* thetar) / (1 +L* a/d3);
	//check if too much drainage
	if(x[2]/d3 < thetafc)
		x[2] = thetafc * d3;}


		theta1 = x[0]/d1;
		theta2 = x[1]/d2;
		theta3 = x[2]/d3;

		//pond -=F;
		if(theta3>thetas){
					theta2 += (theta3 - thetas) * d3/d2;
					theta3 = thetas;}
		if(theta2>thetas){
							theta1 += (theta2 - thetas) * d2/d1;
							theta2 = thetas;}
		if(theta1>thetas){
			pond += -(thetas - theta1) * d1;
			theta1 = thetas;}

		leak = std::max<double>(0,(L3 - x[2])/dt);



}

