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

void Ric_ModifiedPicard(colvec &x, const double &pond, const double dt, double &Ks, double &d1, double &d2,
		double &d3, double &psiae, double &lam, double &theta1, double &theta2, double &theta3) //time step
		{
	double invdt = 1/dt;
	//Unsaturated Hydr Cond
	double K1=0, K12=0, K23=0, K3=0;

	double p = 2*lam + 3;

	colvec Fun(3);
	colvec deltax(3);

	int k = 0;
	do {

		K1 = Ks * powl(S1, p);
		K12 = Ks / (d1 + d2) * (d1 * powl(S1, p) + d2 * powl(S2, p));
		K23 = Ks / (d2 + d3) * (d2 * powl(S2, p) + d3 * powl(S3, p));
		K3 = Ks * powl(S3, p);

		infilt = std::min<double>(K1 * (1 + (x[0] + pond) / D1), pond * invdt);
		if (S1 == 1)
			infilt = 0;
		Qout = K3 * d3dxslope;

		Fun[0] = d1 * (theta1 * invdt) - d1 * (theta11 * invdt) + infilt
				- K12 * (1 + (x[1] - x[0]) / D2);
		Fun[1] = d2 * (theta2 * invdt) - d2 * (theta21 * invdt)
				+ K12 * (1 + (x[1] - x[0]) / D2)
				- K23 * (1 + (x[2] - x[1]) / D3);
		Fun[2] = d3 * (theta3 * invdt) - d3 * (theta31 * invdt)
				+ K23 * (1 + (x[2] - x[1]) / D3) + Qin - Qout - d3 * S3 * L;




		if (!solve(deltax, J, -Fun))
			cout << "no solution";
		cout << "x: " << x << endl;
		x += deltax;
		cout << deltax << endl;
		cout << -Fun << endl;
		cout << J << endl;

		S1 = x[0] < psiae ? 1 : powl(psiae / x[0], 1 / lam);
		S2 = x[1] < psiae ? 1 : powl(psiae / x[1], 1 / lam);
		S3 = x[2] < psiae ? 1 : powl(psiae / x[2], 1 / lam);

		theta11 = S1 * (thetas - thetar) + thetar;
		theta21 = S2 * (thetas - thetar) + thetar;
		theta31 = S3 * (thetas - thetar) + thetar;

		k++;

	} while (norm(deltax, 2) > 0.00001 && k < MAX_ITER);
	if (k >= MAX_ITER)
		cout << "WARNING: Max no iterations reached for Richards solution "
				<< endl;

}

