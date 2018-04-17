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
  double L2toGW = bsn.getFluxL2toGW()->matrix[r][c];
  
  // == 2H ------------------------------------------------------------------------------------------
  if(ctrl.sw_2H){
      // Update layer 1
      _d2Hsoil1->matrix[r][c] = InOutMix(theta1_old*d1, _d2Hsoil1->matrix[r][c],
					 SrftoL1, _d2Hsurface->matrix[r][c], L1toL2);
      // Update layer 2
      _d2Hsoil2->matrix[r][c] = InOutMix(theta2_old*d2, _d2Hsoil2->matrix[r][c],
					 L1toL2, _d2Hsoil1->matrix[r][c], L2toL3+L2toGW);
      // Update layer 3 (vadose)
      _d2Hsoil3->matrix[r][c] = InputMix(NS3_old, _d2Hsoil3->matrix[r][c],
					 L2toL3, _d2Hsoil2->matrix[r][c]);

      // Groundwater (layer 3)
      _d2Hgroundwater->matrix[r][c] = GW_old + L2toGW > RNDOFFERR ?
	InputMix(GW_old, _d2Hgroundwater->matrix[r][c], L2toGW, _d2Hsoil2->matrix[r][c]) : -1000;

      // Leakage: in all cases, groundwater signature
      _d2Hleakage->matrix[r][c] = _d2Hgroundwater->matrix[r][c];

  }
  // == 18O -----------------------------------------------------------------------------------------
  if(ctrl.sw_18O){
      // Update layer 1
      _d18Osoil1->matrix[r][c] = InOutMix(theta1_old*d1, _d18Osoil1->matrix[r][c],
					 SrftoL1, _d18Osurface->matrix[r][c], L1toL2);
      // Update layer 2
      _d18Osoil2->matrix[r][c] = InOutMix(theta2_old*d2, _d18Osoil2->matrix[r][c],
					 L1toL2, _d18Osoil1->matrix[r][c], L2toL3+L2toGW);
      // Update layer 3 (vadose)
      _d18Osoil3->matrix[r][c] = InputMix(NS3_old, _d18Osoil3->matrix[r][c],
					 L2toL3, _d18Osoil2->matrix[r][c]);

      // Groundwater (layer 3)
      _d18Ogroundwater->matrix[r][c] = GW_old + L2toGW > RNDOFFERR ?
	InputMix(GW_old, _d18Ogroundwater->matrix[r][c], L2toGW, _d18Osoil2->matrix[r][c]) : -1000;

      // Leakage: in all cases, groundwater signature
      _d18Oleakage->matrix[r][c] = _d18Ogroundwater->matrix[r][c];

  }

  // == Age -----------------------------------------------------------------------------------------
  if(ctrl.sw_Age){
      // Update layer 1
      _Agesoil1->matrix[r][c] = InOutMix(theta1_old*d1, _Agesoil1->matrix[r][c],
					 SrftoL1, _Agesurface->matrix[r][c], L1toL2);
      // Update layer 2
      _Agesoil2->matrix[r][c] = InOutMix(theta2_old*d2, _Agesoil2->matrix[r][c],
					 L1toL2, _Agesoil1->matrix[r][c], L2toL3+L2toGW);
      // Update layer 3 (vadose)
      _Agesoil3->matrix[r][c] = InputMix(NS3_old, _Agesoil3->matrix[r][c],
					 L2toL3, _Agesoil2->matrix[r][c]);

      // Groundwater (layer 3)
      _Agegroundwater->matrix[r][c] = GW_old + L2toGW > RNDOFFERR ?
	InputMix(GW_old, _Agegroundwater->matrix[r][c], L2toGW, _Agesoil2->matrix[r][c]) : 0;
      
      // Leakage: in all cases, groundwater signature
    _Ageleakage->matrix[r][c] = _Agegroundwater->matrix[r][c];
  }
}


