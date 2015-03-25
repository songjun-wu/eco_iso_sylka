/*
 * Infilt_Richards.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: marco
 */

#define ARMA_NO_DEBUG //disables armadillo bound checks for speed optimization
#include <armadillo>
#include "Basin.h"

using namespace arma;

inline int Ric_Newton(colvec &x, double &Qout, double &K1, double &K12, double &K23, double &K3,
		double &theta11, double &theta21,double &theta31, double &infilt, double &pond, double &leak,
		const double &dt, const double &Ks, const double &d1, const double &d2,
		const double &d3, const double &psiae, const double &lam, const double &thetas,
		const double &thetar, const double &theta1,	const double &theta2, const double &theta3,
		const double &d3dxslope, const double &L, const double &Qin);

inline int Ric_ModifiedPicard(colvec &x, double &Qout, double &K1, double &K12, double &K23, double &K3,
		double &theta11, double &theta21,double &theta31, double &infilt, double &pond, double &leak,
		const double &dt, const double &Ks, const double &d1, const double &d2,
		const double &d3, const double &psiae, const double &lam, const double &thetas,
		const double &thetar, const double &theta1,	const double &theta2, const double &theta3,
		const double &d3dxslope, const double &L, const double &Qin);

void Basin::Infilt_Richards(Control &ctrl, double &f, double &F,  double &theta1, double &theta2, double &theta3, double &leak, double &pond, double &percolat, double dt, int r, int c, int flowdir) //time step
{



	double Ks = _Ksat->matrix[r][c];
	double psiae = _psi_ae->matrix[r][c];
	double lam = _BClambda->matrix[r][c];
	double thetar = _theta_r->matrix[r][c];
	double thetas = _porosity->matrix[r][c];

	double L = _bedrock_leak->matrix[r][c];

	//depth of soil layers
	double depth = _soildepth->matrix[r][c];
	double d1 = _depth_layer1->matrix[r][c];
	double d2 = _depth_layer2->matrix[r][c];
	double d3 = depth - d1 - d2;


	double d3dxslope = d3*sin(atan(_slope->matrix[r][c]))/_dx;
	double Qin=_GWupstreamBC->matrix[r][c]; //gw upstream flux BC

	//This variables are state variables that will be returned by the solution of Richards equation
	//Unsaturated Hydr Cond
	double K1=0, K12=0, K23=0, K3=0;
	double infilt=0;
	double Qout=0; // gw flow leaving the cell populated upon solution of Richard's equation
	//Initial guess for soil moisture at t+1 is current initial soil moisture content
	double theta11=theta1;
	double theta21=theta2;
	double theta31=theta3;
	//soil hydraulic head for the three soil layers
	colvec x(3);

   double initstor = theta1*d1 + theta2*d2 + theta3*d3;

	if (ctrl.toggle_soil_water_profile == 2){
		if (Ric_Newton(x, Qout, K1, K12, K23, K3, theta11, theta21, theta31,
				infilt, pond, leak, dt, Ks, d1, d2, d3, psiae, lam, thetas, thetar,
				theta1, theta2, theta3, d3dxslope, L, Qin)) {
			//If newton iteration fails, restore original initial guess for moisture and try Picard
			double theta11 = theta1;
			double theta21 = theta2;
			double theta31 = theta3;
			Ric_ModifiedPicard(x, Qout, K1, K12, K23, K3, theta11, theta21,
					theta31, infilt, pond, leak, dt, Ks, d1, d2, d3, psiae, lam,
					thetas, thetar, theta1, theta2, theta3, d3dxslope, L, Qin);
		}
		} else {
			if(Ric_ModifiedPicard(x, Qout, K1, K12, K23, K3, theta11, theta21,
					theta31, infilt, pond, leak, dt, Ks, d1, d2, d3, psiae, lam,
					thetas, thetar, theta1, theta2, theta3, d3dxslope, L, Qin)){
				Ric_Newton(x, Qout, K1, K12, K23, K3, theta11, theta21,
									theta31, infilt, pond, leak, dt, Ks, d1, d2, d3, psiae, lam,
									thetas, thetar, theta1, theta2, theta3, d3dxslope, L, Qin);

			}

		}

   _psi->matrix[r][c] = x[0]; //Hydraulic potential of the topmost layer

    F += infilt * dt;
  //  f = K1*(1 + (x[0] - pond)/D1 );
   	theta1 =theta11;
   	theta2 = theta21;
   	theta3 = theta31;
   	pond -= infilt*dt;
   	if(pond<0)
   		cout << "pond negative\n";



    double endstor = theta1*d1 + theta2*d2 + theta3*d3;

    double mberr =  (endstor-initstor - infilt*dt - Qin*dt + K3*d3dxslope*dt + leak*dt)*100/(endstor + infilt*dt + Qin*dt);
    cout << mberr << " ";
   switch (flowdir) //add the previously calculated *discharge* (not elevation) to the downstream cell
	{
	case 1:
		_GWupstreamBC->matrix[r + 1][c - 1] += K3*d3dxslope;;
		_ponding->matrix[r + 1][c - 1] += pond;
		break;
	case 2:
		_GWupstreamBC->matrix[r + 1][c] += K3*d3dxslope;;
		_ponding->matrix[r + 1][c] += pond;
		break;
	case 3:
		_GWupstreamBC->matrix[r + 1][c + 1] += K3*d3dxslope;;
		_ponding->matrix[r + 1][c + 1] += pond;
		break;
	case 4:
		_GWupstreamBC->matrix[r][c - 1] += K3*d3dxslope;;
		_ponding->matrix[r][c - 1] += pond;
		break;
	case 5:
		_dailyGwtrOutput.cells.push_back(cell(r, c, (K3*d3dxslope * _dx * _dx)));
		_dailyOvlndOutput.cells.push_back(cell(r, c, pond * _dx * _dx / dt));
		break; //if it is an outlet store the outflow m3s-1
	case 6:
		_GWupstreamBC->matrix[r][c + 1] += K3*d3dxslope;;
		_ponding->matrix[r][c + 1] += pond;
		break;
	case 7:
		_GWupstreamBC->matrix[r - 1][c - 1] += K3*d3dxslope;;
		_ponding->matrix[r - 1][c - 1] += pond;
		break;
	case 8:
		_GWupstreamBC->matrix[r - 1][c] += K3*d3dxslope;;
		_ponding->matrix[r - 1][c] += pond;
		break;
	case 9:
		_GWupstreamBC->matrix[r - 1][c + 1] += K3*d3dxslope;;
		_ponding->matrix[r - 1][c + 1] += pond;
		break;
	default:
		throw -1;
	}

   pond=0;


}
