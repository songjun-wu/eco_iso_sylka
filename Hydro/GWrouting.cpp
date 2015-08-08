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
	REAL8 soildepth, d1, d2, d3; //guess
	REAL8  fc; //field capacity
	REAL8 deficit; //soil water deficit to reach field capacity in m

	//surface routing parameters
		REAL8 ponding = 0;
		REAL8 theta1 = 0;
		REAL8 theta2 = 0;
		REAL8 theta3 = 0;
		REAL8 f = 0;
		REAL8 F = 0;
		REAL8 ca = 0; //catchment area
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



	for (unsigned int j = 0; j < _vSortedGrid.cells.size() ; j++)
	{
					r = _vSortedGrid.cells[j].row;
					c = _vSortedGrid.cells[j].col;
					d = _vSortedGrid.cells[j].dir;

		//surface routing stuff
		returnflow = 0;
		Qij1 = _Disch_upstreamBC->matrix[r][c];
		qall=0;
		ponding = _ponding->matrix[r][c];
		theta1 = _soilmoist1->matrix[r][c];
		theta2 = _soilmoist2->matrix[r][c];
		theta3 = _soilmoist3->matrix[r][c];
		ca = _catcharea->matrix[r][c];
		gw = _GravityWater->matrix[r][c];

		fc = _fieldcap->matrix[r][c];
		soildepth = _soildepth->matrix[r][c];
		d1 = _depth_layer1->matrix[r][c];
		d2 = _depth_layer2->matrix[r][c];
		d3 = soildepth - d1 - d2;


		if(ctrl.sw_reinfilt && !(ctrl.sw_channel && _channelwidth->matrix[r][c] > 0) ) //if reinfiltration switch is on is not a channel cell or the channel switch is off
				Infilt_GreenAmpt(f, F, theta1,theta2, theta3, ponding, gw, dt, r, c);



		if(theta3 > fc){
			gw = (theta3 - fc) * d3;
				theta3 = fc;
		}


		if (ctrl.sw_channel && _channelwidth->matrix[r][c] > 0){ //if this is a channel cell and channels are activated
			//maxR = ( _porosity->matrix[r][c] - fc ) * soildepth; //calculates the maximum gravitational water that can go
			qc = _Ksat->matrix[r][c] * gw * ( 1 - expl(- _chGWparam->matrix[r][c] * gw) );
			gw -= qc * dtdx;
		}


	//	_soilmoist1->matrix[r][c] = theta1;
	//	_soilmoist2->matrix[r][c] = theta2;
	//	_soilmoist3->matrix[r][c] = theta3;
		_GravityWater->matrix[r][c] = gw;



		///enter groundwater
			poros = _porosity->matrix[r][c];
			//soildepth = _soildepth->matrix[r][c];
			alpha = _Ksat->matrix[r][c] * sin(atan(_slope->matrix[r][c]));
			//fc = _fieldcap->matrix[r][c];
			deficit = 0;
			if (fabs(fc - theta3) > RNDOFFERR){
					deficit = (fc - theta3) * d3;
			}



			qj1i = _GWupstreamBC->matrix[r][c];// discharge (j is timestep) so j1i is total discharge per unit width from upstream at t+1
			hji1 = _GrndWaterOld->matrix[r][c]; //head at the cell itself (end of it so j+1) at t
			R =_GravityWater->matrix[r][c]; //recharge to the groundwater system at the end of the time step in meters
			_GravityWater->matrix[r][c] = 0; //gravity water becomes groundwater

			hj1i1 = ( dtdx * qj1i + hji1 + R  - returnflow - deficit) / ( 1 + alpha * dtdx); //R is in meters so no need to multiply times dt here

			if ( deficit > 0 && hj1i1 < 0){
					theta3 += ( dtdx * qj1i + hji1 + R  - returnflow ) / d3;
					hj1i1 = 0;
			}
			else if (deficit > 0 && hj1i1 >= 0)
				theta3 += ( dtdx * qj1i + hji1 + R  - returnflow - hj1i1*( 1 + alpha * dtdx) ) / d3;

			//if the new amount of water in the cell is larger than the soil storage solve for return flow
			if ( (  (poros - theta3) * d3  )  < hj1i1 ){
				 returnflow = -(poros - theta3) * d3 * ( 1 + alpha * dtdx)   + (dtdx * qj1i) +  hji1 + R - deficit ;
				 theta2 += returnflow/d2;
				 if(theta2>poros){
					theta1 += (theta2 - poros) * d2/d1;
					theta2 = poros;}
				if(theta1>poros){
					ponding += (theta1 - poros) * d1;
					theta1 = poros;}


				//ponding += returnflow;
				hj1i1 = (poros - theta3) * d3;
			}



           //channe routing
			if (ctrl.sw_channel && _channelwidth->matrix[r][c] > 0) {

				ponding += qc * dtdx;

				qall = ponding*_dx/dt;

				KinematicWave(Qk1, Si1j1, Qij1,  qall,  dt, r, c);

				//Qk1 = ponding * _dx*_dx/dt  + Qij1 ;
				ponding = 0;

			}

			_soilmoist1->matrix[r][c] = theta1;
			_soilmoist2->matrix[r][c] = theta2;
			_soilmoist3->matrix[r][c] = theta3 + hj1i1 / d3;
			_GrndWater->matrix[r][c]= hj1i1;

			switch (d) //add the previously calculated *discharge* (not elevation) to the downstream cell
								{
									case 1:   _GWupstreamBC->matrix[r+1][c-1]+= hj1i1 * alpha;
											  _Disch_upstreamBC->matrix[r+1][c-1] += Qk1;
														_ponding->matrix[r+1][c-1] += ponding;
														break;
									case 2:   _GWupstreamBC->matrix[r+1][c]+= hj1i1 * alpha;
									          _Disch_upstreamBC->matrix[r+1][c] += Qk1;
									 	 	 	 	 	 _ponding->matrix[r+1][c]+= ponding;
									 	 	 	 	 	 break;
									case 3:   _GWupstreamBC->matrix[r+1][c+1]+= hj1i1* alpha;
									          _Disch_upstreamBC->matrix[r+1][c+1] += Qk1;
														_ponding->matrix[r+1][c+1]+= ponding;
														break;
									case 4:   _GWupstreamBC->matrix[r][c-1]+= hj1i1* alpha;
									          _Disch_upstreamBC->matrix[r][c-1] += Qk1;
														_ponding->matrix[r][c-1]+= ponding;
														break;
									case 5: _dailyGwtrOutput.cells.push_back(cell(r, c, (alpha * hj1i1 * _dx) ));
									        _dailyOvlndOutput.cells.push_back(cell(r, c, Qk1));
									        //_dailyOvlndOutput.cells.push_back(cell(r, c, ponding * _dx *_dx / dt));
														break; //if it is an outlet store the outflow m3s-1
									case 6:   _GWupstreamBC->matrix[r][c+1]+= hj1i1* alpha;
									          _Disch_upstreamBC->matrix[r][c+1] += Qk1;
														_ponding->matrix[r][c+1]+= ponding;
														break;
									case 7:   _GWupstreamBC->matrix[r-1][c-1]+= hj1i1* alpha;
									          _Disch_upstreamBC->matrix[r-1][c-1] += Qk1;
														_ponding->matrix[r-1][c-1]+= ponding;
														break;
									case 8:   _GWupstreamBC->matrix[r-1][c]+= hj1i1* alpha;
									          _Disch_upstreamBC->matrix[r-1][c] += Qk1;
														_ponding->matrix[r-1][c]+= ponding;
														break;
									case 9:   _GWupstreamBC->matrix[r-1][c+1]+= hj1i1* alpha;
									          _Disch_upstreamBC->matrix[r-1][c+1] += Qk1;
									 	 	 	 	 	_ponding->matrix[r-1][c+1]+= ponding;
									 	 	 	 	 	break;
									default: return -1;
								}

			if(ctrl.sw_channel && _channelwidth->matrix[r][c] > 0)
				_ponding->matrix[r][c] = Si1j1/(_dx*_dx);
			else
				_ponding->matrix[r][c] = 0.0;

			_GrndWater->matrix[r][c] = 0.0;
			_Disch_old->matrix[r][c] = Qk1;
			Qk1=0;


	}

//	*_GrndWaterOld = *_GrndWater;

//	if(upstreamBC)
//		delete upstreamBC;

	return EXIT_SUCCESS;
}
