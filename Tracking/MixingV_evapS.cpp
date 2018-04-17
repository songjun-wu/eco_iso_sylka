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
 * MixingV_evapS.cpp
 *
 *  Created on: Jun 21, 2017
 *      Author: Sylvain Kuppel
 */

#include "Basin.h"

void Tracking::MixingV_evapS(Atmosphere &atm, Basin &bsn, Control &ctrl, 
			     double &d1, double &theta_new,
			     double Ts, double &etp, double &beta,
			     double &d2H_evap, double &d18O_evap, double &Age_evap,
			     int r, int c)
{

  double evapS   = etp > RNDOFFERR ? etp * ctrl.dt : 0.0 ;
  double etotS   = bsn.getEvaporationS_all()->matrix[r][c] * ctrl.dt; //vegetation-summed Es (until this p)
  //double SrftoL1 = bsn.getFluxSrftoL1()->matrix[r][c];

  // useful effective volume
  double V_new = theta_new*d1;
  double V_old = V_new + evapS;

  double d2H_new, d18O_new;//, Age_new;
  
  // -- 2H ----------------------------------------------------------------------------
  if(ctrl.sw_2H){
    
    // If fractionation, fractio acts over the whole L1
    // Safeguard with minimum E value: avoids diverging d2H_evap values
    if(ctrl.sw_frac and evapS > 1e-6)
      Frac_Esoil(atm, bsn, ctrl, V_old, V_new, beta, 
		 _d2Hsoil1->matrix[r][c], d2H_new, d2H_evap, Ts, r, c, 0);
    else {
      // If no fractionation (or negligible E), all from L1
      d2H_new = _d2Hsoil1->matrix[r][c];
      d2H_evap = evapS > RNDOFFERR ? _d2Hsoil1->matrix[r][c] : -1000;
    }
    // Finally, update
    _d2Hsoil1->matrix[r][c] = d2H_new;
    _d2HevapS_sum->matrix[r][c] = InputMix(etotS, _d2HevapS_sum->matrix[r][c], evapS, d2H_evap);
  }

  // -----------------------------------------------------------------------------------
  
  // -- 18O ---------------------------------------------------------------------------
  if(ctrl.sw_18O){
    
    // If fractionation, fractio acts over the whole L1
    // Safeguard with minimum E value: avoids diverging d18O_E values
    if(ctrl.sw_frac and evapS > 1e-6){
      Frac_Esoil(atm, bsn, ctrl, V_old, V_new, beta, 
		 _d18Osoil1->matrix[r][c], d18O_new, d18O_evap, Ts, r, c, 1);
    } else {
      // If no fractionation (or negligible E), all from L1
      d18O_new = _d18Osoil1->matrix[r][c];
      d18O_evap = evapS > RNDOFFERR ? _d18Osoil1->matrix[r][c] : -1000;
    }    
    // Finally, update
    _d18Osoil1->matrix[r][c] = d18O_new;
    _d18OevapS_sum->matrix[r][c] = InputMix(etotS, _d18OevapS_sum->matrix[r][c], evapS, d18O_evap);
  }
  // ----------------------------------------------------------------------------------
  
  // -- Water age ----------------------------------------------------------------------
  if(ctrl.sw_Age){
    // All from L1: ages don't change from earlier mixing
    _AgeevapS_sum->matrix[r][c] = evapS > RNDOFFERR ? _Agesoil1->matrix[r][c] : 0 ;
  }
  // -----------------------------------------------------------------------------------
  
}


