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

    double invdt = 1/dt;

	double Ks = _Ksat->matrix[r][c];
	double psiae = _psi_ae->matrix[r][c];
	double lam = _BClambda->matrix[r][c];
	double thetar = _theta_r->matrix[r][c];
	double thetas = _porosity->matrix[r][c];

	double p = 2*lam + 3;

	//double depth = _soildepth->matrix[r][c];

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

	//Relative water contents
	double S1=0, S2=0, S3=0;
	//Unsaturated Hydr Cond
	double K1=0, K12=0, K23=0, K3=0;
	//Soil suction head
	double psi1=0, psi2=0, psi3=0;

	//derivatives of suction with respect to soil moisture
	double dpsi1dO1=0;
	double dpsi2dO2=0;
	double dpsi3dO3=0;

    //derivatives of K with respect to soil moisture
	double dK1dO1=0;
	double dK12dO1=0;
	double dK12dO2=0;
	double dK23dO2=0;
	double dK23dO3=0;
	double dK3dO3=0;

	double infilt=0;
	double dinfiltdO1=0;

	double d3dxslope = d3*sin(atan(_slope->matrix[r][c]))/_dx;
	double Qout=0; // gw flow leaving the cell
	double Qin=_GWupstreamBC->matrix[r][c]; //gw upstream flux BC


	colvec Fun(3);
	mat J = zeros<mat>(3,3);
	colvec x(3);
	colvec deltax(3);

	//Initial guess is initial soil moisture content
   x[0] = theta1;
   x[1] = theta2;
   x[2] = theta3;



	int k = 0;
   do{

		S1 = (x[0] - thetar)/(thetas - thetar);
		S2 = (x[1] - thetar)/(thetas - thetar);
		S3 = (x[2] - thetar)/(thetas - thetar);

		K1 = Ks * powl(S1,p);
		K12 = Ks/(d1+d2) * (d1*powl(S1,p) + d2*powl(S2,p)  );
		K23 = Ks/(d2+d3) * (d2*powl(S2,p) + d3*powl(S3,p)  );
		K3 = Ks * powl(S3,p);

		psi1 = psiae * powl(S1, -lam);
		psi2 = psiae * powl(S2, -lam);
		psi3 = psiae * powl(S3, -lam);

		infilt = std::min<double> (K1*(1 + (psi1 + pond)/D1 ), pond*invdt );
		Qout = K3*d3dxslope;

		if (infilt>0)
			cout << "tetet";

		Fun[0] = d1*(theta1*invdt) - d1*(x[0]*invdt) + infilt - K12*(1 + (psi2 - psi1)/D2 ) ;
		Fun[1] = d2*(theta2*invdt) - d2*(x[1]*invdt) + K12*(1 + (psi2 - psi1)/D2 ) - K23*(1 + (psi3 - psi2)/D3 );
		Fun[2] = d3*(theta3*invdt) - d3*(x[2]*invdt) + K23*(1 + (psi3 - psi2)/D3 )+ Qin - Qout - d3*S3*L;

		dK1dO1  = Ks*p*powl(S1,p) / (x[0] - thetar);
		dK12dO1 = Ks*d1*p*powl(S1,p)/( (d1+d2)*(x[0] - thetar) );
		dK12dO2 = Ks*d2*p*powl(S2,p)/( (d1+d2)*(x[1] - thetar) );
		dK23dO2 = Ks*d2*p*powl(S2,p)/( (d2+d3)*(x[1] - thetar) );
		dK23dO3 = Ks*d3*p*powl(S3,p)/( (d2+d3)*(x[2] - thetar) );
		dK3dO3  = Ks*p*powl(S3,p) / (x[2] - thetar);

		dpsi1dO1 = lam*psiae*powl(S1,-lam)/ (thetar - x[0]);
		dpsi2dO2 = lam*psiae*powl(S2,-lam)/ (thetar - x[1]);
		dpsi3dO3 = lam*psiae*powl(S3,-lam)/ (thetar - x[2]);

		if(infilt < K1*(1 + (psi1 + pond)/D1 ))
			dinfiltdO1 = 0;
		else
			dinfiltdO1 = dK1dO1*(1 + (psi1 + pond)/D1) + (K1/D1)*dpsi1dO1;


		// Fill the Jacobian
		J(0,0) = -d1*invdt + dinfiltdO1 - dK12dO1*(1 + (psi2 - psi1)/D2 ) +(K12/D2)*dpsi1dO1;
		J(0,1) = -dK12dO2*( 1 + (psi2 - psi1)/D2 ) - (K12/D2)*dpsi2dO2;
		//J(0,2) = 0; // Just to remember that this is element of the Jacobian is zero
		J(1,0) = dK12dO1*( 1 + (psi2 - psi1)/D2 ) - (K12/D2)*dpsi1dO1;
		J(1,1) = -d2*invdt + dK12dO2*(1+(psi2-psi1)/D2) + (K12/D2)*dpsi2dO2 - dK23dO2*(1+(psi3-psi2)/D3)+(K23/D3)*dpsi2dO2;
		J(1,2) = -dK23dO3*(1+(psi3-psi2)/D3)-(K23/D3)*dpsi3dO3;
		//J(2,0) = 0; // Just to remember that this is element of the Jacobian is zero
		J(2,1) = dK23dO2*(1+(psi3-psi2)/D3) - (K12/D3)*dpsi2dO2;
		J(2,2) = -d3*invdt + dK23dO3*(1+ (psi3-psi2)/D3) + (K23/D3)*dpsi3dO3 - d3dxslope*dK3dO3 - d3*L/(thetas-thetar);

        if(!solve(deltax, J, -Fun))
        	cout << "no solution";
        cout <<"x: " <<  x << endl;
        x += deltax;
        if(x[2]<=thetar || S1>1)
        	cout << "bad";
        cout << deltax << endl;
        cout << -Fun << endl;
        cout << J << endl;

       	k++;

	}while(norm(deltax, 2) > 0.00001 && k < MAX_ITER);
   if (k >= MAX_ITER)
   					cout << "WARNING: Max no iterations reached for Richards solution " << endl;

   if(x[2] > thetas){
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
   }

   //calculate average moisture for entire soil profile
   theta = (d1*x[0] + d2*x[1] + d3*x[2])/depth;

    F += infilt;
    f = K1*(1 + (psi1 - pond)/D1 );
   	theta1 = x[0];
   	theta2 = x[1];
   	theta2 = x[2];
   	pond -= infilt;

   switch (flowdir) //add the previously calculated *discharge* (not elevation) to the downstream cell
	{
	case 1:
		_GWupstreamBC->matrix[r + 1][c - 1] += K3*d3dxslope;;
		_ponding->matrix[r + 1][c - 1] += pond;
		break;
	case 2:
		_GWupstreamBC->matrix[r + 1][c] += K3*d3dxslope;;
		_ponding->matrix[r + 1][c] += pond;
		break;
	case 3:
		_GWupstreamBC->matrix[r + 1][c + 1] += K3*d3dxslope;;
		_ponding->matrix[r + 1][c + 1] += pond;
		break;
	case 4:
		_GWupstreamBC->matrix[r][c - 1] += K3*d3dxslope;;
		_ponding->matrix[r][c - 1] += pond;
		break;
	case 5:
		_dailyGwtrOutput.cells.push_back(cell(r, c, (K3*d3dxslope * _dx)));
		_dailyOvlndOutput.cells.push_back(cell(r, c, pond * _dx * _dx / dt));
		break; //if it is an outlet store the outflow m3s-1
	case 6:
		_GWupstreamBC->matrix[r][c + 1] += K3*d3dxslope;;
		_ponding->matrix[r][c + 1] += pond;
		break;
	case 7:
		_GWupstreamBC->matrix[r - 1][c - 1] += K3*d3dxslope;;
		_ponding->matrix[r - 1][c - 1] += pond;
		break;
	case 8:
		_GWupstreamBC->matrix[r - 1][c] += K3*d3dxslope;;
		_ponding->matrix[r - 1][c] += pond;
		break;
	case 9:
		_GWupstreamBC->matrix[r - 1][c + 1] += K3*d3dxslope;;
		_ponding->matrix[r - 1][c + 1] += pond;
		break;
	default:
		throw -1;
	}

   pond=0;


}
