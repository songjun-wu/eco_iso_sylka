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

int Ric_ModifiedPicard(colvec &x, double &Qout, double &K1, double &K12, double &K23, double &K3,
		double &theta11, double &theta21,double &theta31, double &infilt, double &pond,  double &leak,
		const double &dt, const double &Ks, const double &d1, const double &d2,
		const double &d3, const double &psiae, const double &lam, const double &thetas,
		const double &thetar, const double &theta1,	const double &theta2, const double &theta3,
		const double &d3dxslope, const double &L, const double &Qin) //time step
		{
	double invdt = 1/dt;

	double p = 2*lam + 3;

	//Distance between soil nodes
	double D1 = d1 * 0.5;
	double D2 = D1 + d2 * 0.5;
	double D3 = (D2 + d3) * 0.5;

	//derivatives of relative saturation with respect to soil tension
	double dS1dpsi1=0;
	double dS2dpsi2=0;
	double dS3dpsi3=0;

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

    //Surface Boundary condition
    /* 1st calculate potential infiltration rate
     * 2nd compare that with available water rate
     * 3rd if available water rate < potential all water in as Neumann BC
     * 4th if available water rate > potential Dirichlet BC with pressure = pond
     * */

    double f_p = Ks * powl(S1, p) *  (x[0] + pond) / D1; //potential infiltration
    double i_p = pond * invdt; //available infiltration rate
    bool BC = 0; //type of BC 0=Dirichtlet; 1=Neumann
    if (i_p < f_p)
    	BC = 1;
    else
        BC=0;

	int k = 0;
	do {

		K1 = Ks * powl(S1, p);
		K12 = Ks / (d1 + d2) * (d1 * powl(S1, p) + d2 * powl(S2, p));
		K23 = Ks / (d2 + d3) * (d2 * powl(S2, p) + d3 * powl(S3, p));
		K3 = Ks * powl(S3, p);

		if(BC){
			infilt = i_p;
			K1=0;
		}
		else
			infilt = K1 * (x[0] + pond) / D1;




		Qout = K3 * d3dxslope;

		Fun[0] = d1 * (theta1 * invdt) - d1 * (theta11 * invdt) + infilt
				- K12 * (1 + (x[1] - x[0]) / D2);
		Fun[1] = d2 * (theta2 * invdt) - d2 * (theta21 * invdt)
				+ K12 * (1 + (x[1] - x[0]) / D2)
				- K23 * (1 + (x[2] - x[1]) / D3);
		Fun[2] = d3 * (theta3 * invdt) - d3 * (theta31 * invdt)
				+ K23 * (1 + (x[2] - x[1]) / D3) + Qin - Qout - L*K3;

		dS1dpsi1 = x[0]<psiae ? 0 : -powl(psiae/x[0],1/lam)/(lam*x[0]);
		dS2dpsi2 = x[1]<psiae ? 0 : -powl(psiae/x[1],1/lam)/(lam*x[1]);
		dS3dpsi3 = x[2]<psiae ? 0 : -powl(psiae/x[2],1/lam)/(lam*x[2]);

/*
		if(infilt < K1*(1 + (x[0] + pond)/D1 ) || infilt ==0)
			K1 = 0;
*/

		J(0,0) = d1*invdt*(thetas-thetar)*dS1dpsi1 -K1/D1 - K12/D2;
		J(0,1) = K12/D2;
		J(0,2) = 0;
		J(1,0) = K12/D2;
		J(1,1) = d2*invdt*(thetas-thetar)*dS2dpsi2 - K12/D2 - K23/D3;
		J(1,2) = K23/D3;
		J(2,0) = 0;
		J(2,1) = K23/D3;
		J(2,2) = d3*invdt*(thetas-thetar)*dS3dpsi3 - K23/D3;


		if (!solve(deltax, J, Fun))
			cout << "no solution";
		cout << "x: " << x << endl;
		x += deltax;
/*		cout << deltax << endl;
		cout << Fun << endl;
		cout << J << endl;*/

		S1 = x[0] < psiae ? 1 : powl(psiae / x[0], 1 / lam);
		S2 = x[1] < psiae ? 1 : powl(psiae / x[1], 1 / lam);
		S3 = x[2] < psiae ? 1 : powl(psiae / x[2], 1 / lam);

		theta11 = S1 * (thetas - thetar) + thetar;
		theta21 = S2 * (thetas - thetar) + thetar;
		theta31 = S3 * (thetas - thetar) + thetar;

/*		if((min(x) < -1) || (max(x) > 1000000)){ //if the search goes stray restart it
			x.randu();
			continue;
		}*/

		k++;

	} while (norm(deltax, 2) > 0.000001 && k < MAX_ITER);
	if (k >= MAX_ITER){
		cout << "WARNING: Max no iterations reached for Richards solution "
				<< endl;}
/*	cout << "x: " << x << endl;
	cout << deltax << endl;
	cout << Fun << endl;
	cout << J << endl;*/
	//update qout with last estimte of tension
	K1 = Ks * powl(S1,p);
	K3 = Ks * powl(S3,p);

	infilt =std::min<double>(infilt, f_p);
	if(x[0]<0)
		pond+= -x[0];
	if(infilt*dt>pond)
		cout << "infilt larger than pond\n";



	leak = L*K3;

	Qout = K3*d3dxslope;
return 0;
}
