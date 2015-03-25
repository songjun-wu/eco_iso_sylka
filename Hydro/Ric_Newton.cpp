/*
 * Ric_ModifiedPicard.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: marco
 */

#define ARMA_NO_DEBUG //disables armadillo bound checks for speed optimization
#include <armadillo>
#include "Basin.h"

using namespace arma;

int Ric_Newton(colvec &x, double &Qout, double &K1, double &K12, double &K23, double &K3,
		double &theta11, double &theta21,double &theta31, double &infilt, double &pond, double &leak,
		const double &dt, const double &Ks, const double &d1, const double &d2,
		const double &d3, const double &psiae, const double &lam, const double &thetas,
		const double &thetar, const double &theta1,	const double &theta2, const double &theta3,
		const double &d3dxslope, const double &L, const double &Qin) //time step
		{

	double invdt = 1/dt;


	double p = 2*lam + 3;

	//derivatives of relative saturation with respect to soil tension
	double dS1dpsi1=0;
	double dS2dpsi2=0;
	double dS3dpsi3=0;

	//Distance between soil nodes
	double D1 = d1 * 0.5;
	double D2 = D1 + d2 * 0.5;
	double D3 = (D2 + d3) * 0.5;

    //derivatives of K with respect to soil tension
	double dK1dpsi1=0;
	double dK12dpsi1=0;
	double dK12dpsi2=0;
	double dK23dpsi2=0;
	double dK23dpsi3=0;
	double dK3dpsi3=0;


	double dinfiltdpsi1=0;


	colvec Fun(3);
	mat J = zeros<mat>(3,3);
	colvec deltax(3);


	double S1 = (theta1 - thetar)/(thetas - thetar);
	double S2 = (theta2 - thetar)/(thetas - thetar);
	double S3 = (theta3 - thetar)/(thetas - thetar);

	//Initial guess of psi is current initial soil moisture content
    x[0] = psiae*powl(S1,-lam);
    x[1] = psiae*powl(S2,-lam);
    x[2] = psiae*powl(S3,-lam);

    double f_p = Ks * powl(S1, p) * (x[0] + 0) / D1; //potential infiltration
    double i_p = pond * invdt; //available infiltration rate
    bool BC = 0; //type of BC 0=Dirichtlet; 1=Neumann
    if (i_p < f_p)
    	BC = 1;
    else
        BC=0;

	int k = 0;
	   do{

			K1 = Ks * powl(S1,p);
			K12 = Ks/(d1+d2) * (d1*powl(S1,p) + d2*powl(S2,p)  );
			K23 = Ks/(d2+d3) * (d2*powl(S2,p) + d3*powl(S3,p)  );
			K3 = Ks * powl(S3,p);

			if(BC){
				infilt = i_p;
				K1=0;
			}
			else
				infilt = K1 * (x[0] + pond) / D1;

			Qout = K3*d3dxslope;

			Fun[0] = d1*(theta1*invdt) - d1*(theta11*invdt) + infilt - K12*(1 + (x[1] - x[0])/D2 ) ;
			Fun[1] = d2*(theta2*invdt) - d2*(theta21*invdt) + K12*(1 + (x[1] - x[0])/D2 ) - K23*(1 + (x[2] - x[1])/D3 );
			Fun[2] = d3*(theta3*invdt) - d3*(theta31*invdt) + K23*(1 + (x[2] - x[1])/D3 )+ Qin - Qout - L*K3;

			dS1dpsi1 = x[0]<psiae ? 0 : -powl(psiae/x[0],1/lam)/(lam*x[0]);
			dS2dpsi2 = x[1]<psiae ? 0 : -powl(psiae/x[1],1/lam)/(lam*x[1]);
			dS3dpsi3 = x[2]<psiae ? 0 : -powl(psiae/x[2],1/lam)/(lam*x[2]);

			dK1dpsi1  = x[0]<psiae ? 0 : Ks*p*powl(S1,p-1)*dS1dpsi1;
			dK12dpsi1 = x[0]<psiae ? 0 : Ks*d1/(d1+d2)*p*powl(S1,p-1)*dS1dpsi1;
			dK12dpsi2 = x[1]<psiae ? 0 : Ks*d2/(d1+d2)*p*powl(S2,p-1)*dS2dpsi2;
			dK23dpsi2 = x[1]<psiae ? 0 : Ks*d2/(d2+d3)*p*powl(S2,p-1)*dS2dpsi2;
			dK23dpsi3 = x[2]<psiae ? 0 : Ks*d3/(d2+d3)*p*powl(S3,p-1)*dS3dpsi3;
			dK3dpsi3  = x[2]<psiae ? 0 : Ks*p*powl(S3,p-1)*dS3dpsi3;


			dinfiltdpsi1 = !BC * dK1dpsi1* (x[0] + pond)/D1 + (K1/D1);


			// Fill the Jacobian
			J(0,0) = -d1*invdt*(thetas-thetar)*dS1dpsi1 + dinfiltdpsi1 - dK12dpsi1*(1 + (x[1] - x[0])/D2 ) +(K12/D2);
			J(0,1) = -dK12dpsi2*( 1 + (x[1] - x[0])/D2 ) - (K12/D2);
			//J(0,2) = 0; // Just to remember that this is element of the Jacobian is zero
			J(1,0) = dK12dpsi1*( 1 + (x[1] - x[0])/D2 ) - (K12/D2);
			J(1,1) = -d2*invdt*(thetas-thetar)*dS2dpsi2 + dK12dpsi2*(1+(x[1]-x[0])/D2) + (K12/D2) - dK23dpsi2*(1+(x[2]-x[1])/D3)+(K23/D3);
			J(1,2) = -dK23dpsi3*(1+(x[2]-x[1])/D3)-(K23/D3);
			//J(2,0) = 0; // Just to remember that this is element of the Jacobian is zero
			J(2,1) = dK23dpsi2*(1+(x[2]-x[1])/D3) - (K12/D3);
			J(2,2) = -d3*invdt*(thetas-thetar)*dS3dpsi3 + dK23dpsi3*(1+ (x[2]-x[1])/D3) + (K23/D3) - d3dxslope*dK3dpsi3 - L*dK3dpsi3;

	        if(!solve(deltax, J, -Fun)){
	        	cout << "Singular Jacobian found in Newton solver. Switching to Picard...\n";
	        	return 1;
	        }
//	        cout <<"x: " <<  x << endl;
	        x += deltax;
//	        cout << deltax << endl;
//	        cout << -Fun << endl;
//	        cout << J << endl;

		    S1 = x[0]<psiae ? 1 : powl(psiae/x[0], 1/lam);
		    S2 = x[1]<psiae ? 1 : powl(psiae/x[1], 1/lam);
		    S3 = x[2]<psiae ? 1 : powl(psiae/x[2], 1/lam);

		    theta11 = S1*(thetas - thetar) + thetar;
		    theta21 = S2*(thetas - thetar) + thetar;
		    theta31 = S3*(thetas - thetar) + thetar;

	       	k++;

		}while(norm(deltax, 2) > 0.00000001 && k < MAX_ITER);
	if (k >= MAX_ITER){
		cout << "Newton Solver failed to converge. Switching to Picard...\n ";
		return 1;
	}
	//update qout with last estimte of tension
	K1 = Ks * powl(S1,p);
	K3 = Ks * powl(S3,p);

	infilt = BC ? i_p : K1 * (x[0] + pond) / D1;

	Qout = K3*d3dxslope;
	leak = L*K3;
 return 0;
}



