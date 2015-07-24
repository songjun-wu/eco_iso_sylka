/*
 * Infilt_GreenAmpt.cpp
 *
 *  Created on: Oct 12, 2009
 *      Author: Marco Maneta
 */

#include "Basin.h"

void Basin::Infilt_GreenAmpt(double &f, double &F, double &theta, double &pond, double &percolat, double dt, int r, int c) //time step
{

	double fF, dfF = 0;
	double ef_poros, thetar, S, Ks, psi, inp, depth, fc;
	double DT = dt; //secs
	double tp = 0; //ponding time in secs
	int k = 0;


		ef_poros = _porosity->matrix[r][c];
		thetar = _theta_r->matrix[r][c];
		psi = _psi_ae->matrix[r][c];
		Ks = _Ksat->matrix[r][c];
		inp = pond/dt; //inp is potential water input in ms-1
			if(inp < RNDOFFERR)
				return;
		depth = _depth_layer1->matrix[r][c];//_soildepth->matrix[r][c];
		fc = _fieldcap->matrix[r][c];

		S = (theta - thetar)/(ef_poros - thetar);


		double dtheta = (1 - S) * ef_poros;
		if(dtheta < RNDOFFERR){//if there is no room for more water
			f = 0;
			return;
		}

        double F1, Fp;
        double psidtheta = fabs(psi) * dtheta;

        double deltaF = 0;
        double i = 0;

        F = theta * depth;// / ef_poros;
        f = Ks * ( ( psidtheta / F) + 1 ); //infiltration capacity at time t

        if (inp <= Ks){
        	F += inp * DT;
        	//theta = F / depth;//* ef_poros / depth; //cf. line 27 of this file
        	pond = 0;

      //  	if(theta > fc){
      //  		percolat += (theta - fc) * depth;
      //  		theta = fc;
      //  	}
        	return;

        }
        else if (inp > Ks){
        	i = min<double>(inp, f);
        	tp = (Ks * psidtheta) / (i * (i - Ks));

				if(tp > DT){ //if time to ponding does not happen within the time step everything infiltrates
					deltaF = i * DT;
				}
				else{
					//if(inp >= f) //if input intensity is larger than infiltration capacity at time 0, ponding occurs the entire time step
						//tp = 0;

					Fp = i * tp;

					//S = (theta + (Fp / depth)  - thetar)/(ef_poros - thetar); //updates relative soil moisture with moisture infiltrated before ponding
					//psidtheta = fabs(psi) * (1 - S) * ef_poros;//to recalculate infiltration after ponding using N-R with correct suction forces

					F1 = Ks*DT; //initial guess
					k = 0;

						do{
							deltaF = F1;
							fF = deltaF - Fp - Ks*(DT - tp) - psidtheta * log((psidtheta + deltaF) /(psidtheta + Fp));
							dfF = deltaF / (psidtheta + deltaF);
							F1 -= fF/dfF;
							k++;
						}while(fabs(deltaF - F1) > 0.00001 && k < MAX_ITER);

					if (k >= MAX_ITER)
						cout << "WARNING: Max no iterations reached for G&A solution " << endl;
					//deltaF += Fp;
			//		cout << "GA case 1 or 2 ocurring " << Fp << " " << deltaF << endl;
				}

        }
        	F += deltaF;
        	f = Ks * ( ( psidtheta / F) + 1 );
		//	theta = F / depth;//* ef_poros / depth; //cf. line 27 of this file
			pond -= deltaF ;

		//	if(theta > fc){
		//		percolat += (theta - fc) * depth;
		//		theta = fc;
		//	}
}
