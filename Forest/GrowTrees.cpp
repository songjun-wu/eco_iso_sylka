/*
 * AllocateCarbon.cpp
 *
 *  Created on: Jun 29, 2010
 *      Author: Marco.Maneta
 */

#include "Forest.h"

int Forest::GrowTrees(UINT4 j, UINT4 r, UINT4 c, REAL8 dt, REAL8 fa, REAL8 ft, REAL8 fw, REAL8 T, REAL8 usablewater){

	REAL8 Fprn, Fpra, Sprn, Spra;
	REAL8 pfs;
	REAL8 nr, ns, nf;
	REAL8 DBH;


		   	Fprn = _species[j].Fprn;
		   	Fpra = _species[j].Fpra;
		   	Sprn = _species[j].Sprn;
		   	Spra = _species[j].Spra;

		   	DBH = 2 * powl(_species[j]._BasalArea->matrix[r][c] / PI, 0.5);

		   	pfs = ( (Fprn*Fpra) / (Sprn*Spra) ) * powl( DBH ,(Fprn - Sprn) );

		   	nr = 0.5 / (1 + 2.5 * fa * ft * fw);
		   	ns = (1 - nr) / (1 + pfs);
		   	nf = 1 - nr - ns;

		   	//Increase root Mass
		   	_species[j]._Del_RootMass->matrix[r][c] = _species[j]._NPP->matrix[r][c] * nr;

		   	//Increase Stem Mass
		   	_species[j]._Del_StemMass->matrix[r][c] = _species[j]._NPP->matrix[r][c] * ns;

		   	//IncraseFoliageMass
		   	_species[j]._Del_FoliageMass->matrix[r][c] = _species[j]._NPP->matrix[r][c] * nf;


		   	GrowStem(j, r, c); //Increase average height and basal area of species j in r,c cell
		   	GrowLAI(j, r, c, T,usablewater, dt); //Increase LAI of species j in r,c cell
		   	GrowRoots(j, r, c, dt); //Increase root density of species j in r,c cell

	return EXIT_SUCCESS;
}
