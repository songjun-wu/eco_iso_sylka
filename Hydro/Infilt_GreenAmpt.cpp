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
 *    Marco Maneta
 *******************************************************************************/
/*
 * Infilt_GreenAmpt.cpp
 *
 *  Created on: Oct 12, 2009
 *      Author: Marco Maneta
 */

#include "Basin.h"

void Basin::Infilt_GreenAmpt(Control &ctrl, Tracking &trck, double &f, double &F, double &theta,
		double &theta2, double &theta3, double &pond, double &gw,
		double dt, int r, int c, UINT4 option) //time step
{

	double fF, dfF = 0;
	double ef_poros, thetar, S, Ks, psi, inp, depth, depth2, depth3;
	double DT = dt; //secs
	double tp = 0; //ponding time in secs
	int k = 0;

	if(ctrl.sw_trck){
		_FluxSrftoL1->matrix[r][c] = 0;
		_FluxL1toL2->matrix[r][c] = 0;
		_FluxL2toL3->matrix[r][c] = 0;
		_FluxL3toGW->matrix[r][c] = 0;
	}

	double KvKh = _KvKs->matrix[r][c];
	double fc = _fieldcap->matrix[r][c];

	ef_poros = _porosity->matrix[r][c];
	thetar = _theta_r->matrix[r][c];
	psi = _psi_ae->matrix[r][c];
	Ks = _Ksat->matrix[r][c] * KvKh;

	inp = pond / dt; //inp is potential water input in ms-1
	if (inp < RNDOFFERR)
		return;

	depth = _depth_layer1->matrix[r][c]; //_soildepth->matrix[r][c];
	depth2 = _depth_layer2->matrix[r][c];
	depth3 = this->_soildepth->matrix[r][c] - depth - depth2;

	S = (theta - thetar) / (ef_poros - thetar);

	double dtheta = (1 - S) * ef_poros;
	if (dtheta < RNDOFFERR) { //if there is no room for more water
		f = 0;
		return;
	}

	double F1, Fp;
	double psidtheta = fabs(psi) * dtheta;

	double deltaF = 0;
	double i = 0;

	F = theta * depth; // / ef_poros;
	f = Ks * ((psidtheta / F) + 1); //infiltration capacity at time t

	if (inp <= Ks) {
		F += inp * DT;
		theta = F / depth; //* ef_poros / depth; //cf. line 27 of this file
		pond = 0;

		// Tracking
		if(ctrl.sw_trck)
			_FluxSrftoL1->matrix[r][c] = inp * DT;

		if (theta > ef_poros) {
			// Tracking
			if(ctrl.sw_trck)
				_FluxL1toL2->matrix[r][c] = (theta - ef_poros) * depth;

			theta2 += (theta - ef_poros) * depth / depth2;
			theta = ef_poros;
		}
		if (theta2 > ef_poros) {
			// Tracking
			if(ctrl.sw_trck){
				_FluxL2toL3->matrix[r][c] = (theta2 - ef_poros) * depth2;
				if(theta3 >= fc)
					_FluxL3toGW->matrix[r][c] = (theta2 - ef_poros) * depth2;
				else
					_FluxL3toGW->matrix[r][c] = \
					max<double>(0,(theta2 - ef_poros) * depth2 - (fc - theta3)*depth3);
			}
			theta3 += (theta2 - ef_poros) * depth2 / depth3;
			theta2 = ef_poros;
		}
		if (theta3 > ef_poros) {
			pond += (theta3 - ef_poros) * depth3;
			// Tracking
			if(ctrl.sw_trck){
				// Subtract the "excess" infiltration" (as seen by L3)
				// it is OK because here SrftoL1>=L1toL2>=L2toL3
				_FluxSrftoL1->matrix[r][c] -= (theta3 - ef_poros) * depth3;
				_FluxL1toL2->matrix[r][c] -= (theta3 - ef_poros) * depth3;
				_FluxL2toL3->matrix[r][c] -= (theta3 - ef_poros) * depth3;
				_FluxL3toGW->matrix[r][c] -= (theta3 - ef_poros) * depth3;
			}
			theta3 = ef_poros;
		}

		gw = max<double>(0,(theta3 - fc) * depth3);

		return;

	} else if (inp > Ks) {
		i = min<double>(inp, f);
		tp = (Ks * psidtheta) / (i * (i - Ks));

		if (tp > DT) { //if time to ponding does not happen within the time step everything infiltrates
			deltaF = i * DT;
		} else {
			//if(inp >= f) //if input intensity is larger than infiltration capacity at time 0, ponding occurs the entire time step
			//tp = 0;

			Fp = i * tp;

			//S = (theta + (Fp / depth)  - thetar)/(ef_poros - thetar); //updates relative soil moisture with moisture infiltrated before ponding
			//psidtheta = fabs(psi) * (1 - S) * ef_poros;//to recalculate infiltration after ponding using N-R with correct suction forces

			F1 = Ks * DT; //initial guess
			k = 0;

			do {
				deltaF = F1;
				fF = deltaF - Fp - Ks * (DT - tp)
																- psidtheta
																* log((psidtheta + deltaF) / (psidtheta + Fp));
				dfF = deltaF / (psidtheta + deltaF);
				F1 -= fF / dfF;
				k++;
			} while (fabs(deltaF - F1) > 0.00001 && k < MAX_ITER);

			if (k >= MAX_ITER)
				cout << "WARNING: Max no iterations reached for G&A solution "
				<< endl;
			//deltaF += Fp;
			//		cout << "GA case 1 or 2 ocurring " << Fp << " " << deltaF << endl;
		}

	}
	F += deltaF;
	f = Ks * ((psidtheta / F) + 1);
	theta = F / depth;			//* ef_poros / depth; //cf. line 27 of this file
	pond -= deltaF;

	// Tracking
	if(ctrl.sw_trck)
		_FluxSrftoL1->matrix[r][c] = deltaF;

	if (theta > ef_poros) {
		theta2 += (theta - ef_poros) * depth / depth2;
		// Tracking
		if(ctrl.sw_trck)
			_FluxL1toL2->matrix[r][c] = (theta - ef_poros) * depth;
		theta = ef_poros;
	}
	if (theta2 > ef_poros) {
		if(ctrl.sw_trck){
			_FluxL2toL3->matrix[r][c] = (theta2 - ef_poros) * depth2;
			// Check if adding to GW pool
			if(theta3 >= fc)
				_FluxL3toGW->matrix[r][c] = (theta2 - ef_poros) * depth2;
			else
				_FluxL3toGW->matrix[r][c] = \
				max<double>(0,(theta2 - ef_poros) * depth2 - (fc - theta3)*depth3);
		}
		theta3 += (theta2 - ef_poros) * depth2 / depth3;
		theta2 = ef_poros;
	}
	if (theta3 > ef_poros) {
		pond += (theta3 - ef_poros) * depth3;
		// Tracking
		if(ctrl.sw_trck){
			// Subtract the "excess" infiltration" (as seen by L3)
			// it is OK because here SrftoL1>=L1toL2>=L2toL3
			_FluxSrftoL1->matrix[r][c] -= (theta3 - ef_poros) * depth3;
			_FluxL1toL2->matrix[r][c] -= (theta3 - ef_poros) * depth3;
			_FluxL2toL3->matrix[r][c] -= (theta3 - ef_poros) * depth3;
			_FluxL3toGW->matrix[r][c] -= (theta3 - ef_poros) * depth3;
		}
		theta3 = ef_poros;
	}

	// Gravity water (for tracking)
	gw = max<double>(0,(theta3 - fc) * depth3);

	// Mixing only if reinfiltration (option 1), otherwise (infiltration) it is done in
	// SoilWateredistribution.cpp
	if(ctrl.sw_trck and option==0){
		if(ctrl.sw_dD){
			// Update layer 1
			trck.setdDsoil1(r, c,
					trck.InOutMix(_soilmoist1->matrix[r][c]*depth,
							trck.getdDsoil1()->matrix[r][c],
							_FluxSrftoL1->matrix[r][c],
							trck.getdDsurface()->matrix[r][c],
							_FluxL1toL2->matrix[r][c]));
			// Update layer 2
			trck.setdDsoil2(r, c,
					trck.InOutMix(_soilmoist2->matrix[r][c]*depth2,
							trck.getdDsoil2()->matrix[r][c],
							_FluxL1toL2->matrix[r][c],
							trck.getdDsoil1()->matrix[r][c],
							_FluxL2toL3->matrix[r][c] ));
			// Update layer 3 (vadose)
			trck.setdDsoil3(r, c,
					trck.InOutMix(std::min<double>(fc,_soilmoist3->matrix[r][c])*depth3,
							trck.getdDsoil3()->matrix[r][c],
							_FluxL2toL3->matrix[r][c],
							trck.getdDsoil2()->matrix[r][c],
							_FluxL3toGW->matrix[r][c] ));
			// Update layer 3 (gw)
			trck.setdDgroundwater(r, c,
					trck.InputMix(_GrndWater->matrix[r][c],
							trck.getdDgroundwater()->matrix[r][c],
							_FluxL3toGW->matrix[r][c],
							trck.getdDsoil3()->matrix[r][c]));
		}
		if(ctrl.sw_d18O){
			// Update layer 1
			trck.setd18Osoil1(r, c,
					trck.InOutMix(_soilmoist1->matrix[r][c]*depth,
							trck.getd18Osoil1()->matrix[r][c],
							_FluxSrftoL1->matrix[r][c],
							trck.getd18Osurface()->matrix[r][c],
							_FluxL1toL2->matrix[r][c] ));
			// Update layer 2
			trck.setd18Osoil2(r, c,
					trck.InOutMix(_soilmoist2->matrix[r][c]*depth2,
							trck.getd18Osoil2()->matrix[r][c],
							_FluxL1toL2->matrix[r][c],
							trck.getd18Osoil1()->matrix[r][c],
							_FluxL2toL3->matrix[r][c] ));
			// Update layer 3 (vadose)
			trck.setd18Osoil3(r, c,
					trck.InOutMix(std::min<double>(fc,_soilmoist3->matrix[r][c])*depth3,
							trck.getd18Osoil3()->matrix[r][c],
							_FluxL2toL3->matrix[r][c],
							trck.getd18Osoil2()->matrix[r][c],
							_FluxL3toGW->matrix[r][c] ));
			// Update layer 3 (gw)
			trck.setd18Ogroundwater(r, c,
					trck.InputMix(_GrndWater->matrix[r][c],
							trck.getd18Ogroundwater()->matrix[r][c],
							_FluxL3toGW->matrix[r][c],
							trck.getd18Osoil3()->matrix[r][c]));
		}
		if(ctrl.sw_Age){
			// Update layer 1
			trck.setAgesoil1(r, c,
					trck.InOutMix(_soilmoist1->matrix[r][c]*depth,
							trck.getAgesoil1()->matrix[r][c],
							_FluxSrftoL1->matrix[r][c],
							trck.getAgesurface()->matrix[r][c],
							_FluxL1toL2->matrix[r][c] ));
			// Update layer 2
			trck.setAgesoil2(r, c,
					trck.InOutMix(_soilmoist2->matrix[r][c]*depth2,
							trck.getAgesoil2()->matrix[r][c],
							_FluxL1toL2->matrix[r][c],
							trck.getAgesoil1()->matrix[r][c],
							_FluxL2toL3->matrix[r][c] ));
			// Update layer 3 (vadose)
			trck.setAgesoil3(r, c,
					trck.InOutMix(std::min<double>(fc,_soilmoist3->matrix[r][c])*depth3,
							trck.getAgesoil3()->matrix[r][c],
							_FluxL2toL3->matrix[r][c],
							trck.getAgesoil2()->matrix[r][c],
							_FluxL3toGW->matrix[r][c] ));
			// Update layer 3 (gw)
			trck.setAgegroundwater(r, c,
					trck.InputMix(_GrndWater->matrix[r][c],
							trck.getAgegroundwater()->matrix[r][c],
							_FluxL3toGW->matrix[r][c],
							trck.getAgesoil3()->matrix[r][c]));
		}
	}

}
