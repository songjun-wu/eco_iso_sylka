/*
 * GWrouting.cpp
 *
 *  Created on: Dec 2, 2010
 *      Author: Marco.Maneta
 */

#include"Basin.h"

int Basin::DailyGWRouting(Atmosphere &atm, Control &ctrl){

	int r,c,d;
	REAL8 dtdx;
	REAL8 alpha;
	REAL8 qj1i;
	REAL8 hji1;
	REAL8 hj1i1;
	REAL8 R;
	REAL8 dt = ctrl.dt;
	REAL8 poros; //porosity
	REAL8 soildepth; //guess
	REAL8  fc; //field capacity
	REAL8 deficit; //soil water deficit to reach field capacity in m

	//surface routing parameters
		REAL8 ponding = 0;
		REAL8 theta = 0;
		REAL8 f = 0;
		REAL8 F = 0;
		REAL8 ca = 0; //catchment area
		REAL8 gw = 0; //gravitational water
		REAL8 returnflow = 0; //flow from gw in excess of the available soil storage
		//REAL8 maxR = 0; //maximum gravitational water possible
		REAL8 qc = 0; // water transfered from the subsurface system to the channel

	grid *upstreamBC = new grid(*_GrndWater); //holds the upstream boundary conditions

	 dtdx = dt / _dx;

	_dailyOvlndOutput.cells.clear();
	_dailyGwtrOutput.cells.clear();

	for (unsigned int j = 0; j < _vSortedGrid.cells.size() ; j++)
	{
					r = _vSortedGrid.cells[j].row;
					c = _vSortedGrid.cells[j].col;
					d = _vSortedGrid.cells[j].dir;

		//surface routing stuff
		returnflow = 0;
		ponding = _ponding->matrix[r][c];
		theta = _soilmoist->matrix[r][c];
		ca = _catcharea->matrix[r][c];
		gw = _GravityWater->matrix[r][c];

		fc = _fieldcap->matrix[r][c];
		soildepth = _soildepth->matrix[r][c];

		if(ctrl.sw_reinfilt && !(ctrl.sw_channel && _channelmask->matrix[r][c] == 1) ) //if reinfiltration switch is on is not a channel cell or the channel switch is off
				Infilt_GreenAmpt(f, F, theta, ponding, gw, dt, r, c);



		if(theta > fc){
			gw = (theta - fc) * soildepth;
				theta = fc;
		}


		if (ctrl.sw_channel && _channelmask->matrix[r][c] == 1){ //if this is a channel cell and channels are activated
			//maxR = ( _porosity->matrix[r][c] - fc ) * soildepth; //calculates the maximum gravitational water that can go
			qc = _Ksat->matrix[r][c] * gw * ( 1 - expl(- _chGWparam->matrix[r][c] * gw) );
			gw -= qc * dtdx;
			ponding += qc * dtdx;
		}


		_soilmoist->matrix[r][c] = theta;
		_GravityWater->matrix[r][c] = gw;

		///enter groundwater
			poros = _porosity->matrix[r][c];
			//soildepth = _soildepth->matrix[r][c];
			alpha = _Ksat->matrix[r][c] * sin(atan(_slope->matrix[r][c]));
			//fc = _fieldcap->matrix[r][c];
			deficit = 0;
			if (fabs(fc - theta) > RNDOFFERR){
					deficit = (fc - theta) * soildepth;
			}



			qj1i = upstreamBC->matrix[r][c];// discharge (j is timestep) so j1i is total discharge per unit width from upstream at t+1
			hji1 = _GrndWaterOld->matrix[r][c]; //head at the cell itself (end of it so j+1) at t
			R =_GravityWater->matrix[r][c]; //recharge to the groundwater system at the end of the time step in meters
			_GravityWater->matrix[r][c] = 0; //gravity water becomes groundwater

			hj1i1 = ( dtdx * qj1i + hji1 + R  - returnflow - deficit) / ( 1 + alpha * dtdx); //R is in meters so no need to multiply times dt here

			if ( deficit > 0 && hj1i1 < 0){
					theta += ( dtdx * qj1i + hji1 + R  - returnflow ) / soildepth;
					hj1i1 = 0;
			}
			else if (deficit > 0 && hj1i1 >= 0)
				theta += ( dtdx * qj1i + hji1 + R  - returnflow - hj1i1*( 1 + alpha * dtdx) ) / soildepth;

			//if the new amount of water in the cell is larger than the soil storage solve for return flow
			if ( (  (poros - theta) * soildepth  )  < hj1i1 ){
				 returnflow = -(poros - theta) * soildepth * ( 1 + alpha * dtdx)   + (dtdx * qj1i) +  hji1 + R - deficit ;
				ponding += returnflow;
				hj1i1 = (poros - theta) * soildepth;
			}

			_soilmoist->matrix[r][c] = theta + hj1i1 / soildepth;
			_GrndWater->matrix[r][c]= hj1i1;

			switch (d) //add the previously calculated *discharge* (not elevation) to the downstream cell
								{
									case 1:   upstreamBC->matrix[r+1][c-1]+= hj1i1 * alpha;
														_ponding->matrix[r+1][c-1] += ponding;
														break;
									case 2:   upstreamBC->matrix[r+1][c]+= hj1i1 * alpha;
									 	 	 	 	 	 _ponding->matrix[r+1][c]+= ponding;
									 	 	 	 	 	 break;
									case 3:   upstreamBC->matrix[r+1][c+1]+= hj1i1* alpha;
														_ponding->matrix[r+1][c+1]+= ponding;
														break;
									case 4:   upstreamBC->matrix[r][c-1]+= hj1i1* alpha;
														_ponding->matrix[r][c-1]+= ponding;
														break;
									case 5: _dailyGwtrOutput.cells.push_back(cell(r, c, (alpha * hj1i1 * _dx) ));
													_dailyOvlndOutput.cells.push_back(cell(r, c, ponding * _dx *_dx / dt));
														break; //if it is an outlet store the outflow m3s-1
									case 6:   upstreamBC->matrix[r][c+1]+= hj1i1* alpha;
														_ponding->matrix[r][c+1]+= ponding;
														break;
									case 7:   upstreamBC->matrix[r-1][c-1]+= hj1i1* alpha;
														_ponding->matrix[r-1][c-1]+= ponding;
														break;
									case 8:   upstreamBC->matrix[r-1][c]+= hj1i1* alpha;
														_ponding->matrix[r-1][c]+= ponding;
														break;
									case 9:   upstreamBC->matrix[r-1][c+1]+= hj1i1* alpha;
									 	 	 	 	 	_ponding->matrix[r-1][c+1]+= ponding;
									 	 	 	 	 	break;
									default: return -1;
								}

			 _ponding->matrix[r][c] = 0.0;
			 _GrndWater->matrix[r][c] = 0.0;

	}

//	*_GrndWaterOld = *_GrndWater;

	if(upstreamBC)
		delete upstreamBC;

	return EXIT_SUCCESS;
}
