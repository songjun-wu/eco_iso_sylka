/*
 * Infilt_Richards.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: marco
 */

#include "Basin.h"

void Basin::Infilt_Richards(double &f, double &F, double &theta, double &pond, double &percolat, double dt, int r, int c) //time step
{

	double psi_s = 0; //initial value of head at the surfce to calculate potential infiltration
	Ks =
	K1 = _Ksat->matrix[r][c] * {}

	f = K * (1 + (psi_1 - psi_s)/D1);

}
