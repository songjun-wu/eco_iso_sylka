/*
 * KinematicWave.cpp
 *
 *  Created on: Aug 6, 2015
 *      Author: marco
 */


#include "Basin.h"



void Basin::KinematicWave(REAL8 &Qk1,  REAL8 &Qij1,  REAL8 &qall,  REAL8 dt, UINT4 r, UINT4 c)
{

	REAL8 C = 0; //rhs of kinematic wave equation
	REAL8 Qi1j = 0; //old discharge at the beginning of time step

	REAL8 a, n, w,  sqrtS, abQ, Qk,  fQj1i1, dfQj1i1; //kinematic wave factors
	REAL8 dtdx = dt/_dx;


	 //kinematic wave
			    Qi1j = _Disch_old->matrix[r][c]; //Q at the beginning of time step
			    Qij1 = _Disch_upstreamBC->matrix[r][c]; //Q at the upstream end of the channel at t+1

			    if(Qi1j+qall+Qij1 > 0){ //if there is water to route
				sqrtS = powl(_slope->matrix[r][c], 0.5);

				w = _channelwidth->matrix[r][c];
	            n = _Manningn->matrix[r][c];
				a = powl(powl(w,0.67)*n/sqrtS, 0.6); //wetted perimeter is approximated with channel width
				//initial guess through solution of linear kw
				REAL8 avQ = 0.5*(Qi1j+Qij1);
				if (avQ==0) abQ=0;
				else abQ = a*0.6*powl(avQ, 0.6-1);
				Qk = ((dtdx*Qij1)+(abQ*Qi1j) + dt*qall)/(dtdx+abQ);

				if(Qk<1e6)
					Qk1 = Qij1+qall*_dx;
				else{

				C =  dtdx * Qij1 + a * powl(Qi1j,0.6) + dt*qall;

				uint count = 0;
				do{
					   Qk=Qk1;
					      fQj1i1 = dtdx*Qk+a*powl(Qk, 0.6)-C;
					      dfQj1i1 = dtdx+a*0.6*powl(Qk, 0.6-1);
					      Qk1 = Qk - (fQj1i1/dfQj1i1);
					      Qk1 = max<double>(Qk1, 1e-6); //avoids powl illegal operation
					      fQj1i1 = dtdx*Qk+a*powl(Qk, 0.6)-C;
					      count++;
				}while(fabs(fQj1i1)>0.00001 && count < MAX_ITER);}


				}


				//end kinematic wave

}


