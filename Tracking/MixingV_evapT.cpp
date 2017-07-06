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
 * MixingV_evapT.cpp
 *
 *  Created on: Jun 22, 2017
 *      Author: Sylvain Kuppel
 */

#include "Basin.h"

int Tracking::MixingV_evapT(Basin &bsn, Control &ctrl,
			     REAL8 &pTrp1, REAL8 &pTrp2, REAL8 &pTrp3,
			     REAL8 &dDevapT_f, REAL8 &d18OevapT_f, REAL8 &AgeevapT_f, 
			     REAL8 &p, int s, int r, int c)
{

  if(ctrl.sw_dD){
    bsn.fForest->setdDtranspi(s, r, c,
			      pTrp1*_dDsoil1->matrix[r][c]+
			      pTrp2*_dDsoil2->matrix[r][c]+
			      pTrp3*_dDsoil3->matrix[r][c]);
    dDevapT_f += bsn.fForest->getdDtranspi(s)->matrix[r][c] * p ;
  }

  if(ctrl.sw_d18O){
    bsn.fForest->setd18Otranspi(s, r, c,
				pTrp1*_d18Osoil1->matrix[r][c]+
				pTrp2*_d18Osoil2->matrix[r][c]+
				pTrp3*_d18Osoil3->matrix[r][c]);
    d18OevapT_f += bsn.fForest->getd18Otranspi(s)->matrix[r][c] * p ;
  }

  if(ctrl.sw_Age){
    bsn.fForest->setAgetranspi(s, r, c,
			       pTrp1*_Agesoil1->matrix[r][c]+
			       pTrp2*_Agesoil2->matrix[r][c]+
			       pTrp3*_Agesoil3->matrix[r][c]);
    AgeevapT_f += bsn.fForest->getAgetranspi(s)->matrix[r][c] * p ;
  }

  return EXIT_SUCCESS;
}


