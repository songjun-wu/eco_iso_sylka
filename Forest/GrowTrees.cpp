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
 * AllocateCarbon.cpp
 *
 *  Created on: Jun 29, 2010
 *      Author: Marco.Maneta
 */

#include "Forest.h"

int Forest::GrowTrees(UINT4 j, UINT4 r, UINT4 c, REAL8 dt, REAL8 fa, REAL8 ft, REAL8 fw, REAL8 T, REAL8 usablewater){

	REAL8 Fprn, Fpra, Sprn, Spra;
	REAL8 pfs;
	REAL8 nr, ns, nf, nrmin, nsmin, nsvar;
	REAL8 DBH;

            if (_species[j].vegtype == 0){
		   	
                Fprn = _species[j].Fprn;
                Fpra = _species[j].Fpra;
                Sprn = _species[j].Sprn;
                Spra = _species[j].Spra;

                DBH = 2 * powl(_species[j]._BasalArea->matrix[r][c] / PI, 0.5);

                pfs = ( (Fprn*Fpra) / (Sprn*Spra) ) * powl( DBH ,(Fprn - Sprn) );

                nr = 0.5 / (1 + 2.5 * fa * ft * fw);
                ns = (1 - nr) / (1 + pfs);
                nf = 1 - nr - ns;


            }
            if (_species[j].vegtype == 2){
                
                nrmin = _species[j].Fprn;
                nsmin = _species[j].Fpra;
                nsvar = _species[j].Sprn;
                
                //nr = 0.5 / (1 + 2.5 * fa * ft * fw);
                nr = (nrmin+nrmin*(1-fw))/( 1+ nrmin*(1-fw));
            
                ns = (nsmin + nsvar * (1-ft));
                ns = min<double>(1-nr, ns);
                nf = 1 - nr - ns;


          
            }
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
