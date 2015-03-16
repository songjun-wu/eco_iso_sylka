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

void Basin::Infilt_Richards(double &f, double &F, double &theta, double &theta1, double &theta2, double &theta3, double &pond, double &percolat, double dt, int r, int c, int flowdir) //time step
{



	double Ks = _Ksat->matrix[r][c];
	double psiae = _psi_ae->matrix[r][c];
	double lam = _BClambda->matrix[r][c];
	double thetar = _theta_r->matrix[r][c];
	double thetas = _porosity->matrix[r][c];

	double L = _bedrock_leak->matrix[r][c];

	//depth of soil layers
	double depth = _soildepth->matrix[r][c];
	double d1 = 0.1;
	double d2 = (depth - 0.1)/2;
	double d3 = d2;

	//Distance between soil nodes
	double D1 = d1 * 0.5;
	double D2 = D1 + d2 * 0.5;
	double D3 = D2 + d3 * 0.5;

	double d3dxslope = d3*sin(atan(_slope->matrix[r][c]))/_dx;
	double Qin=_GWupstreamBC->matrix[r][c]; //gw upstream flux BC

	double Qout=0; // gw flow leaving the cell populated upon solution of Richard's equation
	colvec x(3);


   double initstor = theta1*d1 + theta2*d2 + theta3*d3;

   Ric_Newton(x, Qout, dt, Ks, d1, d2, d3, D1, D2, D3, psiae, lam, thetas, thetar, theta1,
			theta2, theta3, d3dxslope, L, Qin);


/*   if(x[2] > thetas){
	   x[2]-= (thetas - x[2]);
	   x[1]+= (thetas - x[2])*d3/d2;
   }
   if(x[1] > thetas){
   	   x[1]-= (thetas - x[1]);
   	   x[0]+= (thetas - x[1])*d2/d3;
   }
   if(x[0] > thetas){
   	   x[0]-= (thetas - x[0]);
   	   pond+= (thetas - x[0])*d1;
   }*/



    F += infilt;
    f = K1*(1 + (x[0] - pond)/D1 );
   	theta1 =theta11;
   	theta2 = theta21;
   	theta3 = theta31;
   	pond -= infilt;

    //calculate average moisture for entire soil profile
    theta = (d1*theta1 + d2*theta2 + d3*theta3)/depth;
    double endstor = theta1*d1 + theta2*d2 + theta3*d3;

    double mberr =  (endstor-initstor - infilt*dt + - Qin*dt +  K3*d3dxslope*dt)*100/(endstor + infilt*dt + Qin*dt);
    cout << mberr;
   switch (flowdir) //add the previously calculated *discharge* (not elevation) to the downstream cell
	{
	case 1:
		_GWupstreamBC->matrix[r + 1][c - 1] += K3*d3dxslope;;
//		_ponding->matrix[r + 1][c - 1] += pond;
		break;
	case 2:
		_GWupstreamBC->matrix[r + 1][c] += K3*d3dxslope;;
//		_ponding->matrix[r + 1][c] += pond;
		break;
	case 3:
		_GWupstreamBC->matrix[r + 1][c + 1] += K3*d3dxslope;;
//		_ponding->matrix[r + 1][c + 1] += pond;
		break;
	case 4:
		_GWupstreamBC->matrix[r][c - 1] += K3*d3dxslope;;
//		_ponding->matrix[r][c - 1] += pond;
		break;
	case 5:
		_dailyGwtrOutput.cells.push_back(cell(r, c, (K3*d3dxslope * _dx)));
//		_dailyOvlndOutput.cells.push_back(cell(r, c, pond * _dx * _dx / dt));
		break; //if it is an outlet store the outflow m3s-1
	case 6:
		_GWupstreamBC->matrix[r][c + 1] += K3*d3dxslope;;
//		_ponding->matrix[r][c + 1] += pond;
		break;
	case 7:
		_GWupstreamBC->matrix[r - 1][c - 1] += K3*d3dxslope;;
//		_ponding->matrix[r - 1][c - 1] += pond;
		break;
	case 8:
		_GWupstreamBC->matrix[r - 1][c] += K3*d3dxslope;;
//		_ponding->matrix[r - 1][c] += pond;
		break;
	case 9:
		_GWupstreamBC->matrix[r - 1][c + 1] += K3*d3dxslope;;
//		_ponding->matrix[r - 1][c + 1] += pond;
		break;
	default:
		throw -1;
	}

   pond=0;


}
