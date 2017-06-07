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
 *    Marco Maneta, Sylvain Kuppel
 *******************************************************************************/
/*
 * GWrouting.cpp
 *
 *  Created on: Dec 2, 2010
 *      Author: Marco.Maneta
 */

#include"Basin.h"

int Basin::DailyGWRouting(Atmosphere &atm, Control &ctrl, Tracking &trck) {

	int r, c, d;
	int rr, cc;
	bool dwn_ok;
	REAL8 dtdx;
	REAL8 alpha;
	REAL8 qj1i;
	REAL8 hji1;
	REAL8 hj1i1;
	REAL8 R;
	REAL8 dt = ctrl.dt;
	REAL8 poros; //porosity
	REAL8 soildepth, d1, d2, d3; //guess
	REAL8 fc; //field capacity
	REAL8 deficit; //soil water deficit to reach field capacity in m

	//surface routing parameters
	REAL8 ponding = 0;
	REAL8 theta1 = 0;
	REAL8 theta2 = 0;
	REAL8 theta3 = 0;
	REAL8 f = 0;
	REAL8 F = 0;
	//REAL8 ca = 0; //catchment area
	REAL8 gw = 0; //gravitational water
	REAL8 returnflow = 0; //flow from gw in excess of the available soil storage
	//REAL8 maxR = 0; //maximum gravitational water possible
	REAL8 qc = 0; // water transfered from the subsurface system to the channel
	REAL8 qall = 0; //lateral inflows to channel
	REAL8 Qij1 = 0; //new discharge from the upstream boundary
	REAL8 Qk1 = 0; //new discharge out of the cell
	REAL8 Si1j1 = 0; //storage in channel at the end of time step

//	grid *upstreamBC = new grid(*_GrndWater); //holds the upstream boundary conditions

	dtdx = dt / _dx;

	if(ctrl.sw_trck){
		// Reinitialize to zero the fluxes upwards modified in the previous time step
		_FluxL1toSrf->reset();
		_FluxL2toL1->reset();
		_FluxL3toL2->reset();
		_FluxGWtoL3->reset();
	}

	for (unsigned int j = 0; j < _vSortedGrid.cells.size(); j++) {
		r = _vSortedGrid.cells[j].row;
		c = _vSortedGrid.cells[j].col;
		d = _vSortedGrid.cells[j].dir;

		//surface routing stuff
		returnflow = 0;
		Qij1 = _Disch_upstreamBC->matrix[r][c];
		qall = 0;
		ponding = _ponding->matrix[r][c];
		theta1 = _soilmoist1->matrix[r][c];
		theta2 = _soilmoist2->matrix[r][c];
		theta3 = _soilmoist3->matrix[r][c];
		//ca = _catcharea->matrix[r][c];
		gw = _GravityWater->matrix[r][c];

		fc = _fieldcap->matrix[r][c];
		soildepth = _soildepth->matrix[r][c];
		d1 = _depth_layer1->matrix[r][c];
		d2 = _depth_layer2->matrix[r][c];
		d3 = soildepth - d1 - d2;

		//if reinfiltration switch is on is not a channel cell or the channel switch is off
		if (ctrl.sw_reinfilt && !(ctrl.sw_channel && _channelwidth->matrix[r][c] > 0))
			Infilt_GreenAmpt(ctrl, trck, f, F, theta1, theta2, theta3, ponding, gw, dt, r,	c, 1);

		if (theta3 > fc) {
			gw = (theta3 - fc) * d3;
			theta3 = fc;
		} else
			gw = 0;

		if (ctrl.sw_channel && _channelwidth->matrix[r][c] > 0) { //if this is a channel cell and channels are activated
		//maxR = ( _porosity->matrix[r][c] - fc ) * soildepth; //calculates the maximum gravitational water that can go
			qc = _Ksat->matrix[r][c] * gw
					* (1 - expl(-_chGWparam->matrix[r][c] * gw));
			gw -= qc * dtdx;

			// Tracking
			if(ctrl.sw_trck){
				//_FluxGWtoChn->matrix[r][c] = qc * dtdx;
				if(ctrl.sw_dD)
					trck.setdDsurface(r, c,
						trck.InputMix(ponding, trck.getdDsurface()->matrix[r][c],
							qc*dtdx, trck.getdDgroundwater()->matrix[r][c]));
				if(ctrl.sw_d18O)
					trck.setd18Osurface(r, c,
						trck.InputMix(ponding, trck.getd18Osurface()->matrix[r][c],
							qc*dtdx, trck.getd18Ogroundwater()->matrix[r][c]));
				if(ctrl.sw_Age)
					trck.setAgesurface(r, c,
						trck.InputMix(ponding, trck.getAgesurface()->matrix[r][c],
							qc*dtdx, trck.getAgegroundwater()->matrix[r][c]));
			}
		}

		// Tracking
		if(ctrl.sw_trck){
			// L3 to GW only if the theta > fc exceeds previous GW storage
			_FluxL3toGW->matrix[r][c] = std::max<double>(0,gw - _GrndWaterOld->matrix[r][c]);
			// Back up soil moisture before vertical redistrib
			_soilmoist1->matrix[r][c] = theta1; //soil moisture at t=t+1
			_soilmoist2->matrix[r][c] = theta2;
			_soilmoist3->matrix[r][c] = theta3;
			// Back up ponding before adding GW seepage (for rivers)
			_ponding->matrix[r][c] = ponding;
		}

		_GravityWater->matrix[r][c] = gw;

		///enter groundwater
		poros = _porosity->matrix[r][c];
		alpha = _Ksat->matrix[r][c] * sin(atan(_slope->matrix[r][c]));
		
		deficit = 0;
		if (fabs(fc - theta3) > RNDOFFERR) {
			deficit = (fc - theta3) * d3;
		}

		qj1i = _GWupstreamBC->matrix[r][c];	// discharge (j is timestep) so j1i is total discharge per unit width from upstream at t+1
		hji1 = 0; //Not used since local GW head is embedded in the updated theta3 portion which becomes R
		R = _GravityWater->matrix[r][c]; //recharge to the groundwater system at the end of the time step in meters
		_GravityWater->matrix[r][c] = 0; //gravity water becomes groundwater

		hj1i1 = (dtdx * qj1i + hji1 + R - returnflow - deficit)
				/ (1 + alpha * dtdx); //R is in meters so no need to multiply times dt here

		if (deficit > 0 && hj1i1 < 0) {
			theta3 += (dtdx * qj1i + hji1 + R - returnflow) / d3;
			hj1i1 = 0;

			// Tracking
			if(ctrl.sw_trck)
				_FluxGWtoL3->matrix[r][c] = dtdx * qj1i + hji1 + R - returnflow;

		} else if (deficit > 0 && hj1i1 >= 0){
			theta3 += (dtdx * qj1i + hji1 + R - returnflow
					- hj1i1 * (1 + alpha * dtdx)) / d3;

			// Tracking
			if(ctrl.sw_trck)
				_FluxGWtoL3->matrix[r][c] = dtdx * qj1i + hji1 + R - returnflow - hj1i1 * (1 + alpha * dtdx);
		}

		//if the new amount of water in the cell is larger than the soil storage solve for return flow
		if (((poros - theta3) * d3) < hj1i1) {
			returnflow = -(poros - theta3) * d3 * (1 + alpha * dtdx)
					+ (dtdx * qj1i) + hji1 + R - deficit;
			theta2 += returnflow / d2;

			// Tracking
			if(ctrl.sw_trck){
				_FluxGWtoL3->matrix[r][c] += returnflow ;
				_FluxL3toL2->matrix[r][c] = returnflow ;
			}

			if (theta2 > poros) {
				theta1 += (theta2 - poros) * d2 / d1;
				// Tracking
				if(ctrl.sw_trck)
					_FluxL2toL1->matrix[r][c] = (theta2 - poros) * d2 ;
				theta2 = poros;
			}
			if (theta1 > poros) {
				ponding += (theta1 - poros) * d1;
				// Tracking
				if(ctrl.sw_trck)
					_FluxL1toSrf->matrix[r][c] = (theta1 - poros) * d1 ;
				theta1 = poros;
			}

			//ponding += returnflow;
			hj1i1 = (poros - theta3) * d3;
		}

		//channel routing
		if (ctrl.sw_channel && _channelwidth->matrix[r][c] > 0) {

			ponding += qc * dtdx;

			qall = ponding * _dx / dt;

			KinematicWave(Qk1, Si1j1, Qij1, qall, dt, r, c);

			//Qk1 = ponding * _dx*_dx/dt  + Qij1 ;
			ponding = 0;

		}

		// Tracking
		if(ctrl.sw_trck){
			if(ctrl.sw_dD){
				// Only consider vertical movement (lateral in the loop below)
				// Update layer 3 (vadose)
				trck.setdDsoil3(r, c,
						trck.InOutMix(std::min<double>(fc,_soilmoist3->matrix[r][c])*d3,
								trck.getdDsoil3()->matrix[r][c],
								_FluxGWtoL3->matrix[r][c],
								trck.getdDgroundwater()->matrix[r][c],
								_FluxL3toL2->matrix[r][c] ));
				// Update layer 2
				trck.setdDsoil2(r, c,
						trck.InOutMix(_soilmoist2->matrix[r][c]*d2,
								trck.getdDsoil2()->matrix[r][c],
								_FluxL3toL2->matrix[r][c],
								trck.getdDsoil3()->matrix[r][c],
								_FluxL2toL1->matrix[r][c] ));
				// Update layer 1
				trck.setdDsoil1(r, c,
						trck.InOutMix(_soilmoist1->matrix[r][c]*d1,
								trck.getdDsoil1()->matrix[r][c],
								_FluxL2toL1->matrix[r][c],
								trck.getdDsoil2()->matrix[r][c],
								_FluxL1toSrf->matrix[r][c] ));
				// Update surface
				trck.setdDsurface(r, c,
						trck.InOutMix(_ponding->matrix[r][c]+qc*dtdx,
								trck.getdDsurface()->matrix[r][c],
								_FluxL1toSrf->matrix[r][c],
								trck.getdDsoil1()->matrix[r][c],
								Qk1 * dtdx / _dx));
			}
			if(ctrl.sw_d18O){
				// Only consider vertical movement (lateral in the loop below)
				// Update layer 3 (vadose)
				trck.setd18Osoil3(r, c,
						trck.InOutMix(std::min<double>(fc,_soilmoist3->matrix[r][c])*d3,
								trck.getd18Osoil3()->matrix[r][c],
								_FluxGWtoL3->matrix[r][c],
								trck.getd18Ogroundwater()->matrix[r][c],
								_FluxL3toL2->matrix[r][c] ));
				// Update layer 2
				trck.setd18Osoil2(r, c,
						trck.InOutMix(_soilmoist2->matrix[r][c]*d2,
								trck.getd18Osoil2()->matrix[r][c],
								_FluxL3toL2->matrix[r][c],
								trck.getd18Osoil3()->matrix[r][c],
								_FluxL2toL1->matrix[r][c] ));
				// Update layer 1
				trck.setd18Osoil1(r, c,
						trck.InOutMix(_soilmoist1->matrix[r][c]*d1,
								trck.getd18Osoil1()->matrix[r][c],
								_FluxL2toL1->matrix[r][c],
								trck.getd18Osoil2()->matrix[r][c],
								_FluxL1toSrf->matrix[r][c] ));
				// Update surface
				trck.setd18Osurface(r, c,
						trck.InOutMix(_ponding->matrix[r][c]+qc*dtdx,
								trck.getd18Osurface()->matrix[r][c],
								_FluxL1toSrf->matrix[r][c],
								trck.getd18Osoil1()->matrix[r][c],
								Qk1 * dtdx / _dx));
			}
			if(ctrl.sw_Age){
				// Only consider vertical movement (lateral in the loop below)
				// Update layer 3 (vadose)
				trck.setAgesoil3(r, c,
						trck.InOutMix(std::min<double>(fc,_soilmoist3->matrix[r][c])*d3,
								trck.getAgesoil3()->matrix[r][c],
								_FluxGWtoL3->matrix[r][c],
								trck.getAgegroundwater()->matrix[r][c],
								_FluxL3toL2->matrix[r][c] ));
				// Update layer 2
				trck.setAgesoil2(r, c,
						trck.InOutMix(_soilmoist2->matrix[r][c]*d2,
								trck.getAgesoil2()->matrix[r][c],
								_FluxL3toL2->matrix[r][c],
								trck.getAgesoil3()->matrix[r][c],
								_FluxL2toL1->matrix[r][c] ));
				// Update layer 1
				trck.setAgesoil1(r, c,
						trck.InOutMix(_soilmoist1->matrix[r][c]*d1,
								trck.getAgesoil1()->matrix[r][c],
								_FluxL2toL1->matrix[r][c],
								trck.getAgesoil2()->matrix[r][c],
								_FluxL1toSrf->matrix[r][c] ));
				// Update surface
				trck.setAgesurface(r, c,
						trck.InOutMix(_ponding->matrix[r][c]+qc*dtdx,
								trck.getAgesurface()->matrix[r][c],
								_FluxL1toSrf->matrix[r][c],
								trck.getAgesoil1()->matrix[r][c],
								Qk1 * dtdx / _dx));
			}
		}


		_soilmoist1->matrix[r][c] = theta1;
		_soilmoist2->matrix[r][c] = theta2;
		_soilmoist3->matrix[r][c] = theta3 + hj1i1 / d3;
		_GrndWater->matrix[r][c] = hj1i1;

		// Locate downstream cell (if it exists)
		dwn_ok = 0;
		switch (d) 
		{
		case 1:
			rr = r+1;
			cc = c-1;
			dwn_ok = 1;
			break;
		case 2:
			rr = r+1;
			cc = c;
			dwn_ok = 1;
			break;
		case 3:
			rr = r+1;
			cc = c+1;
			dwn_ok = 1;
			break;
		case 4:
			rr = r;
			cc = c-1;
			dwn_ok = 1;
			break;
		case 5:
			_dailyGwtrOutput.cells.push_back(cell(r, c, (alpha * hj1i1 * _dx)));
			_dailyOvlndOutput.cells.push_back(cell(r, c, Qk1+ponding * _dx *_dx / dt)); //second term needed to account for outer at outlets with no channel
			//_dailyOvlndOutput.cells.push_back(cell(r, c, ponding * _dx *_dx / dt));
			break; //if it is an outlet store the outflow m3s-1
		case 6:
			rr = r;
			cc = c+1;
			dwn_ok = 1;
			break;
		case 7:
			rr = r-1;
			cc = c-1;
			dwn_ok = 1;
			break;
		case 8:
			rr = r-1;
			cc = c;
			dwn_ok = 1;
			break;
		case 9:
			rr = r-1;
			cc = c+1;
			dwn_ok = 1;
			break;
		default:
			return -1;
		}

		// Check there is downstream cell
		if(dwn_ok){
			
			// Tracking lateral inputs to the downstream cell
			if(ctrl.sw_trck){
				if(ctrl.sw_dD){
					trck.setdDgroundwater(rr, cc,
						trck.InputMix(_GrndWater->matrix[rr][cc], trck.getdDgroundwater()->matrix[rr][cc],
							hj1i1 * alpha * dtdx, trck.getdDgroundwater()->matrix[r][c]));
					trck.setdDsurface(rr, cc,
						trck.InputMix(_ponding->matrix[rr][cc], trck.getdDsurface()->matrix[rr][cc],
							ponding + Qk1 * dtdx / _dx,	trck.getdDsurface()->matrix[r][c]));
				}
				if(ctrl.sw_d18O){
					trck.setd18Ogroundwater(rr, cc,
						trck.InputMix(_GrndWater->matrix[rr][cc], trck.getd18Ogroundwater()->matrix[rr][cc],
							hj1i1 * alpha * dtdx, trck.getd18Ogroundwater()->matrix[r][c]));
					trck.setd18Osurface(rr, cc,
						trck.InputMix(_ponding->matrix[rr][cc], trck.getd18Osurface()->matrix[rr][cc],
							ponding + Qk1 * dtdx / _dx,	trck.getd18Osurface()->matrix[r][c]));
				}
				if(ctrl.sw_Age){
					trck.setAgegroundwater(rr, cc,
						trck.InputMix(_GrndWater->matrix[rr][cc], trck.getAgegroundwater()->matrix[rr][cc],
							hj1i1 * alpha * dtdx, trck.getAgegroundwater()->matrix[r][c]));
					trck.setAgesurface(rr, cc,
						trck.InputMix(_ponding->matrix[rr][cc], trck.getAgesurface()->matrix[rr][cc],
							ponding + Qk1 * dtdx / _dx,	trck.getAgesurface()->matrix[r][c]));
				}
			}

			// Add the previously calculated *discharge* (not elevation) to the downstream cell
			_GWupstreamBC->matrix[rr][cc] += hj1i1 * alpha;
			_Disch_upstreamBC->matrix[rr][cc] += Qk1;
			_ponding->matrix[rr][cc] += ponding;	
		}


		
		if (ctrl.sw_channel && _channelwidth->matrix[r][c] > 0)
			_ponding->matrix[r][c] = Si1j1 / (_dx * _dx);
		else
			_ponding->matrix[r][c] = 0.0;

		// Save river discharge
		_Disch_old->matrix[r][c] = Qk1;
		Qk1 = 0;

	}

	// Save previous GW and surface state
	*_GrndWaterOld = *_GrndWater;
	*_PondingOld = *_ponding;

	return EXIT_SUCCESS;
}
