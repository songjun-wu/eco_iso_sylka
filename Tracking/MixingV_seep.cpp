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
 * MixingV_seep.cpp
 *
 *  Created on: Jun 21, 2017
 *      Author: Sylvain Kuppel
 */

#include "Basin.h"

void Tracking::MixingV_seep(Basin &bsn, Control &ctrl,
			    double &ponding, double &qc, int r, int c)
{

  REAL8 dtdx = ctrl.dt / bsn.getCellSize();

  if(ctrl.sw_2H)
    _d2Hsurface->matrix[r][c] = InputMix(ponding, _d2Hsurface->matrix[r][c],
					qc*dtdx, _d2Hgroundwater->matrix[r][c]);

  if(ctrl.sw_18O)
    _d18Osurface->matrix[r][c] = InputMix(ponding, _d18Osurface->matrix[r][c],
					qc*dtdx, _d18Ogroundwater->matrix[r][c]);

  if(ctrl.sw_Age)
    _Agesurface->matrix[r][c] = InputMix(ponding, _Agesurface->matrix[r][c],
					 qc*dtdx, _Agegroundwater->matrix[r][c]);
  
}


