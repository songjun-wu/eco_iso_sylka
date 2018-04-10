/*******************************************************************************
 * Ech2o, a spatially-distributed, ecohydrologic simulator
 * Copyright (c) 2016 Marco Maneta <marco.maneta@umontana.edu>
 *
 *     This file is part of ech2o, a hydrologic model developed at the 
 *     University of Montana.
 *
 *     Ech2o is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     Ech2o is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with Ech2o.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contributors:
 *    Marco Maneta, Sylvain Kuppel
 *******************************************************************************/
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

void Basin::SoilWaterRedistribution(Control &ctrl, const double &F, double &theta1,
		double &theta2, double &theta3, double &pond, double &gw, double &leak,  double dt,
		int r, int c) {


	//double K1, K12, K2, K23, K3;
	double thetar = _theta_r->matrix[r][c];
	double thetafc = _fieldcap->matrix[r][c];
	double thetas = _porosity->matrix[r][c];
	double KvKh = _KvKs->matrix[r][c];
	double Ks = _Ksat->matrix[r][c] * KvKh;
	double L = _bedrock_leak->matrix[r][c];
	double fc = _fieldcap->matrix[r][c];

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

		// Tracking
		if(ctrl.sw_trck)
			_FluxL1toL2->matrix[r][c] += max<REAL8>(0,L1 - x[0]);

		x[1]=L2;
	}

	if(L2/d2>thetafc){
		x[1] =(L2 + a* thetar) / (1 + a/d2);
		//check if too much drainage
		if(x[1]/d2 < thetafc)
			x[1] = thetafc * d2;

		L3 += L2 - x[1];

		// Tracking
		if(ctrl.sw_trck){
			_FluxL2toL3->matrix[r][c] += max<REAL8>(0,L2 - x[1]);
			// Check if adding to GW
			if(x[2]/d3 >= fc)
				_FluxL3toGW->matrix[r][c] += max<REAL8>(0,L2 - x[1]);
			else
				_FluxL3toGW->matrix[r][c] += max<REAL8>(0,L2 - x[1] - (fc*d3 - x[2]));
		}

		x[2]=L3;
	}

	if(L3/d3>thetafc){
		x[2] =(L3 + L*a* thetar) / (1 +L* a/d3);
		//check if too much drainage
		if(x[2]/d3 < thetafc)
			x[2] = thetafc * d3;

		// Tracking
		// if(ctrl.sw_trck)
		//	_FluxL3toGW->matrix[r][c] -= max<REAL8>(0,L3 - x[2]);
	}

	theta1 = x[0]/d1;
	theta2 = x[1]/d2;
	theta3 = x[2]/d3;

	//pond -=F;
	if(theta3>thetas){
		theta2 += (theta3 - thetas) * d3/d2;

		// Tracking
		if(ctrl.sw_trck){
			_FluxL2toL3->matrix[r][c] -= (theta3 - thetas) * d3;
			_FluxL3toGW->matrix[r][c] -= (theta3 - thetas) * d3;
		}

		theta3 = thetas;
	}
	if(theta2>thetas){
		theta1 += (theta2 - thetas) * d2/d1;

		// Tracking
		if(ctrl.sw_trck)
			_FluxL1toL2->matrix[r][c] -= (theta2 - thetas) * d2;

		theta2 = thetas;
	}
	if(theta1>thetas){
		pond += -(thetas - theta1) * d1;

		_FluxSrftoL1->matrix[r][c] -= (theta1 - thetas) * d1;

		theta1 = thetas;
	}

	gw = max<double>(0,(theta3 - fc) * d3);
	leak = std::max<double>(0,(L3 - x[2])/dt);

}

