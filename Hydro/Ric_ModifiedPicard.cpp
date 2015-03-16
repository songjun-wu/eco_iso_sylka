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

void Ric_ModifiedPicard(double &Ks, double &d1, double &d2, double &d3, double &psiae, double & ) //time step
{


   int k = 0;
   do{

		K1 = Ks * powl(S1,p);
		K12 = Ks/(d1+d2) * (d1*powl(S1,p) + d2*powl(S2,p)  );
		K23 = Ks/(d2+d3) * (d2*powl(S2,p) + d3*powl(S3,p)  );
		K3 = Ks * powl(S3,p);

		infilt = std::min<double> (K1*(1 + (psi1 + pond)/D1 ), pond*invdt );
		Qout = K3*d3dxslope;

		Fun[0] = d1*(theta1*invdt) - d1*(theta11*invdt) + infilt - K12*(1 + (psi2 - psi1)/D2 ) ;
		Fun[1] = d2*(theta2*invdt) - d2*(theta21*invdt) + K12*(1 + (psi2 - psi1)/D2 ) - K23*(1 + (psi3 - psi2)/D3 );
		Fun[2] = d3*(theta3*invdt) - d3*(theta31*invdt) + K23*(1 + (psi3 - psi2)/D3 )+ Qin - Qout - d3*S3*L;

		dS1dpsi1 = x[0]<psiae ? 0 : -powl(psiae/x[0],1/lam)/(lam*x[0]);
		dS2dpsi2 = x[1]<psiae ? 0 : -powl(psiae/x[1],1/lam)/(lam*x[1]);
		dS3dpsi3 = x[2]<psiae ? 0 : -powl(psiae/x[2],1/lam)/(lam*x[2]);

		dK1dpsi1  = x[0]<psiae ? 0 : Ks*p*powl(S1,p-1)*dS1dpsi1;
		dK12dpsi1 = x[0]<psiae ? 0 : Ks*d1/(d1+d2)*p*powl(S1,p-1)*dS1dpsi1;
		dK12dpsi2 = x[1]<psiae ? 0 : Ks*d2/(d1+d2)*p*powl(S2,p-1)*dS2dpsi2;
		dK23dpsi2 = x[1]<psiae ? 0 : Ks*d2/(d2+d3)*p*powl(S2,p-1)*dS2dpsi2;
		dK23dpsi3 = x[2]<psiae ? 0 : Ks*d3/(d2+d3)*p*powl(S3,p-1)*dS3dpsi3;
		dK3dpsi3  = x[2]<psiae ? 0 : Ks*p*powl(S3,p-1)*dS3dpsi3;

		if(infilt < K1*(1 + (psi1 + pond)/D1 ))
			dinfiltdpsi1 = 0;
		else
			dinfiltdpsi1 = dK1dpsi1*(1 + (psi1 + pond)/D1) + (K1/D1);


		// Fill the Jacobian
		J(0,0) = -d1*invdt*(thetas-thetar)*dS1dpsi1 + dinfiltdpsi1 - dK12dpsi1*(1 + (psi2 - psi1)/D2 ) +(K12/D2);
		J(0,1) = -dK12dpsi2*( 1 + (psi2 - psi1)/D2 ) - (K12/D2);
		//J(0,2) = 0; // Just to remember that this is element of the Jacobian is zero
		J(1,0) = dK12dpsi1*( 1 + (psi2 - psi1)/D2 ) - (K12/D2);
		J(1,1) = -d2*invdt*(thetas-thetar)*dS2dpsi2 + dK12dpsi2*(1+(psi2-psi1)/D2) + (K12/D2) - dK23dpsi2*(1+(psi3-psi2)/D3)+(K23/D3);
		J(1,2) = -dK23dpsi3*(1+(psi3-psi2)/D3)-(K23/D3);
		//J(2,0) = 0; // Just to remember that this is element of the Jacobian is zero
		J(2,1) = dK23dpsi2*(1+(psi3-psi2)/D3) - (K12/D3);
		J(2,2) = -d3*invdt*(thetas-thetar)*dS3dpsi3 + dK23dpsi3*(1+ (psi3-psi2)/D3) + (K23/D3) - d3dxslope*dK3dpsi3 - d3*L*dS3dpsi3;

        if(!solve(deltax, J, -Fun))
        	cout << "no solution";
        cout <<"x: " <<  x << endl;
        x += deltax;
        if(x[2]<=thetar || S1>1)
        	cout << "bad";
        cout << deltax << endl;
        cout << -Fun << endl;
        cout << J << endl;

	    S1 = x[0]<psiae ? 1 : powl(psiae/x[0], 1/lam);
	    S1 = x[1]<psiae ? 1 : powl(psiae/x[1], 1/lam);
	    S1 = x[2]<psiae ? 1 : powl(psiae/x[2], 1/lam);

	    theta11 = S1*(thetas - thetar) + thetar;
	    theta21 = S2*(thetas - thetar) + thetar;
	    theta31 = S3*(thetas - thetar) + thetar;

       	k++;

	}while(norm(deltax, 2) > 0.00001 && k < MAX_ITER);
   if (k >= MAX_ITER)
   					cout << "WARNING: Max no iterations reached for Richards solution " << endl;

   if(x[2] > thetas){
	   x[2]-= (thetas - x[2]);
	   x[1]+= (thetas - x[2])*d3/d2;
   }
   if(x[1] > thetas){
   	   x[1]-= (thetas - x[1]);
   	   x[0]+= (thetas - x[1])*d2/d3;
   }
   if(x[0] > thetas){
   	   x[0]-= (thetas - x[0]);
   	   pond+= (thetas - x[0])*d1;
   }

   //calculate average moisture for entire soil profile
   theta = (d1*x[0] + d2*x[1] + d3*x[2])/depth;

    F += infilt;
    f = K1*(1 + (psi1 - pond)/D1 );
   	theta1 = x[0];
   	theta2 = x[1];
   	theta2 = x[2];
   	pond -= infilt;

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
		_dailyGwtrOutput.cells.push_back(cell(r, c, (K3*d3dxslope * _dx)));
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


