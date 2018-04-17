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
 * MixingH.cpp
 *
 *  Created on: Jun 21, 2017
 *      Author: Sylvain Kuppel
 */

#include "Basin.h"

void Tracking::MixingH(Basin &bsn, Control &ctrl,
		       double &hj1i1, double &alpha, double &ponding, double &Qk1, 
		       double &dtdx, double &dx, int r, int c, int rr, int cc)
{

  // Deuterium
  if(ctrl.sw_2H){
    _d2Hgroundwater->matrix[rr][cc] = InputMix(bsn.getGrndWater()->matrix[rr][cc], 
					      _d2Hgroundwater->matrix[rr][cc], 
					      hj1i1 * alpha * dtdx, 
					      _d2Hgroundwater->matrix[r][c]);

    _d2Hsurface->matrix[rr][cc] = InputMix(bsn.getPondingWater()->matrix[rr][cc], 
					  _d2Hsurface->matrix[rr][cc],
					  ponding + Qk1 * dtdx / dx,
					  _d2Hsurface->matrix[r][c]);
  }

  // Oxygen 18
  if(ctrl.sw_18O){
    _d18Ogroundwater->matrix[rr][cc] = InputMix(bsn.getGrndWater()->matrix[rr][cc], 
						_d18Ogroundwater->matrix[rr][cc],
						hj1i1 * alpha * dtdx, 
						_d18Ogroundwater->matrix[r][c]);
    
    _d18Osurface->matrix[rr][cc] = InputMix(bsn.getPondingWater()->matrix[rr][cc], 
					    _d18Osurface->matrix[rr][cc],
					    ponding + Qk1 * dtdx / dx,	
					    _d18Osurface->matrix[r][c]);
  }

  // Water age
  if(ctrl.sw_Age){
    _Agegroundwater->matrix[rr][cc] = InputMix(bsn.getGrndWater()->matrix[rr][cc],
					       _Agegroundwater->matrix[rr][cc],
					       hj1i1 * alpha * dtdx, 
					       _Agegroundwater->matrix[r][c]);
    
    _Agesurface->matrix[rr][cc] = InputMix(bsn.getPondingWater()->matrix[rr][cc], 
					   _Agesurface->matrix[rr][cc],
					   ponding + Qk1 * dtdx / dx,	
					   _Agesurface->matrix[r][c]);
  }
  
}


