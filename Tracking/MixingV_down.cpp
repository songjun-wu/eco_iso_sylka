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
 * MixingV_down.cpp
 *
 *  Created on: Jun 21, 2017
 *      Author: Sylvain Kuppel
 */

#include "Basin.h"

void Tracking::MixingV_down(Basin &bsn, Control &ctrl,
			    double &d1, double &d2, double &d3, double &fc,
			    double &leak, int r, int c, bool reinf) //time step
{

  double theta1_old = bsn.getSoilMoist1()->matrix[r][c];
  double theta2_old = bsn.getSoilMoist2()->matrix[r][c];
  double theta3_old = bsn.getSoilMoist3()->matrix[r][c];
  double NS3_old = std::min<double>(fc,theta3_old)*d3; //non-saturated part of L3
  double GW_old = std::max<double>(0,theta3_old -fc)*d3;

  double SrftoL1 = bsn.getFluxSrftoL1()->matrix[r][c];
  double L1toL2 = bsn.getFluxL1toL2()->matrix[r][c];
  double L2toL3 = bsn.getFluxL2toL3()->matrix[r][c];
  double L3toGW = bsn.getFluxL3toGW()->matrix[r][c];
  
  if(ctrl.sw_lifo and ctrl.sw_dD)
    _dDlifo->reset();
  if(ctrl.sw_lifo and ctrl.sw_d18O)
    _d18Olifo->reset();
  if(ctrl.sw_lifo and ctrl.sw_Age)
    _Agelifo->reset();

  // == dD ------------------------------------------------------------------------------------------
  if(ctrl.sw_dD){
    // Update layer 1

    if(!ctrl.sw_lifo || reinf)
      // If LIFO activated, no mixing in L1 before soil evap,
      // L2 sees signature from previous timestep
      _dDsoil1->matrix[r][c] = InOutMix(theta1_old*d1, _dDsoil1->matrix[r][c],
					SrftoL1, _dDsurface->matrix[r][c], L1toL2);
    // Update layer 2: if LIFO use unmixed in L1 except if L1toL2 > theta1_old*d1
    // in which case the "percolation excess" (L1toL2t-theta1_old) has surface signature
    if(ctrl.sw_lifo && L1toL2 > theta1_old*d1) 
      _dDsoil2->matrix[r][c] = InOutMix(theta2_old*d2, _dDsoil2->matrix[r][c],
					L1toL2, 
					InputMix(theta1_old*d1, _dDsoil1->matrix[r][c],
						 L1toL2-theta1_old*d1, _dDsurface->matrix[r][c]),
					L2toL3);
    else
      _dDsoil2->matrix[r][c] = InOutMix(theta2_old*d2, _dDsoil2->matrix[r][c],
					L1toL2, _dDsoil1->matrix[r][c], L2toL3);
    // Update layer 3 (vadose)
    _dDsoil3->matrix[r][c] = InOutMix(NS3_old, _dDsoil3->matrix[r][c],
				      L2toL3, _dDsoil2->matrix[r][c], L3toGW+leak);
    // Update layer 3 (gw)
    _dDgroundwater->matrix[r][c] = InputMix(GW_old, _dDgroundwater->matrix[r][c],
					    L3toGW,	_dDsoil3->matrix[r][c]);
  }

  // == d18O -----------------------------------------------------------------------------------------
  if(ctrl.sw_d18O){
    // Update layer 1

    if(!ctrl.sw_lifo || reinf)
      // Mixing only if no LIFO or reinfiltration, otherwise soil evap later,
      // so that L2 sees signature from previous timestep
      _d18Osoil1->matrix[r][c] = InOutMix(theta1_old*d1, _d18Osoil1->matrix[r][c],
					  SrftoL1, _d18Osurface->matrix[r][c], L1toL2);

    // Update layer 2: if LIFO use unmixed in L1 except if L1toL2 > theta1_old*d1
    // in which case the "percolation excess" (L1toL2t-theta1_old) has surface signature
    if(ctrl.sw_lifo && L1toL2 > theta1_old*d1) 
      _d18Osoil2->matrix[r][c] = InOutMix(theta2_old*d2, _d18Osoil2->matrix[r][c],
					  L1toL2, 
					  InputMix(theta1_old*d1, _d18Osoil1->matrix[r][c],
						   L1toL2-theta1_old*d1, _d18Osurface->matrix[r][c]),
					  L2toL3);
    else
      _d18Osoil2->matrix[r][c] = InOutMix(theta2_old*d2, _d18Osoil2->matrix[r][c],
					  L1toL2, _d18Osoil1->matrix[r][c],L2toL3);

    // Update layer 3 (vadose)
    _d18Osoil3->matrix[r][c] = InOutMix(NS3_old, _d18Osoil3->matrix[r][c],
					L2toL3, _d18Osoil2->matrix[r][c], L3toGW+leak);
    // Update layer 3 (gw)
    _d18Ogroundwater->matrix[r][c] = InputMix(GW_old, _d18Ogroundwater->matrix[r][c],
					      L3toGW, _d18Osoil3->matrix[r][c]);
  }

  // == Age -----------------------------------------------------------------------------------------
  if(ctrl.sw_Age){
    // Update layer 1
    if(!ctrl.sw_lifo || reinf)
      // If LIFO activated, no mixing in L1 before soil evap,
      // L2 sees signature from previous timestep
      _Agesoil1->matrix[r][c] = InOutMix(theta1_old*d1, _Agesoil1->matrix[r][c],
					 SrftoL1, _Agesurface->matrix[r][c], L1toL2);
    // Update layer 2: if LIFO use unmixed in L1 except if L1toL2 > theta1_old*d1
    // in which case the "percolation excess" (L1toL2t-theta1_old) has surface signature
    if(ctrl.sw_lifo && L1toL2 > theta1_old*d1) 
      _Agesoil2->matrix[r][c] = InOutMix(theta2_old*d2, _Agesoil2->matrix[r][c],
					 L1toL2, 
					 InputMix(theta1_old*d1, _Agesoil1->matrix[r][c],
						  L1toL2-theta1_old*d1, _Agesurface->matrix[r][c]),
					 L2toL3);
    else
      _Agesoil2->matrix[r][c] = InOutMix(theta2_old*d2, _Agesoil2->matrix[r][c],
				       L1toL2, _Agesoil1->matrix[r][c], L2toL3);
    // Update layer 3 (vadose)
    _Agesoil3->matrix[r][c] = InOutMix(NS3_old, _Agesoil3->matrix[r][c],
				       L2toL3, _Agesoil2->matrix[r][c], L3toGW+leak);
    // Update layer 3 (gw)
    _Agegroundwater->matrix[r][c] = InputMix(GW_old, _Agegroundwater->matrix[r][c],
					     L3toGW, _Agesoil3->matrix[r][c]);
  }
}


