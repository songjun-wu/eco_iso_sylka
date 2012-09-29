/*
 * Exfiltration.cpp
 *
 *  Created on: Jul 13, 2010
 *      Author: Marco.Maneta
 */

#include "Basin.h"

REAL8 Basin::ExfiltrationCapacity(	REAL8 theta,//soil moisture
									REAL8 dt,
									UINT4 r,
									UINT4 c)

{

	REAL8 S; //relative soil moisture
	REAL8 thetar = _theta_r->matrix[r][c];
	REAL8 poros = _porosity->matrix[r][c];
	REAL8 Ksat = _Ksat->matrix[r][c];
	REAL8 psiae = _psi_ae->matrix[r][c];
	REAL8 poresizeind = _BClambda->matrix[r][c];


	S = (theta - thetar)/(poros - thetar);
	if (S<=0)
		S = 0.01;

	REAL8 num = 8 * poros * Ksat * 86400 * psiae; //m2d-1
	REAL8 denom = 3 * (1 + 3*poresizeind) * (1 + 4*poresizeind); //dimensionless


	return (powl(S, 1/(2*poresizeind) + 2) * sqrt(num/denom) * sqrt(1/86400)) / sqrt(1/dt); // returns water limited exfiltration volume in ms-1


}
