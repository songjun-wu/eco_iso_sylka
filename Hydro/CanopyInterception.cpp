/*
 * Intercep_Rutter.cpp
 *
 *  Created on: Oct 12, 2009
 *      Author: Marco Maneta
 */

#include "Forest.h"

int Forest::CanopyInterception(Atmosphere &atm, Control &ctrl, REAL8 &DelCanStor, REAL8 &D, UINT4 s, UINT4 r, UINT4 c)
{

    REAL8 S=0, C=0, Pp=0;
    REAL8 dC=0;
    REAL8 dt = ctrl.dt;

    Pp = atm.getPrecipitation()->matrix[r][c];

    UINT4 nsp = getNumSpecies();

	  if(s == nsp -1) //for bare soil, water reaching the ground is pp times its proportion of the cell
		  D = Pp;
	  else{

	  S = getMaxCanopyStorage(s, r, c); //returns max canopy storage as calculated with current LAI
	  C = this->getIntercWater(s, r, c); //holds current water storage in the canopy

	  if(fabs(C) < RNDOFFERR){
		  _species[s]._WaterStorage->matrix[r][c] = 0.0;
		  C = 0.0;
	  }

         dC = Pp * dt;
         D = C+dC <= S ? 0.0 : (C+dC - S);
         D = min<REAL8>(D, C+dC);

         DelCanStor = Pp * dt - D;
         D /=dt; //make D into flux ms-1

         if(fabs(DelCanStor) < RNDOFFERR)
                 	 DelCanStor = 0;

         _species[s]._WaterStorage->matrix[r][c] += DelCanStor;


	  }



	return EXIT_SUCCESS;
}
