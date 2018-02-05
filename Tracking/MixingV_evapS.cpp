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
			     double &d1, double &theta_lifo, double &theta_new,
			     double Ts, double &etp, double &beta,
			     double &dDevap, double &d18Oevap, double &Ageevap,
			     int r, int c)
{

  double evapS   = etp > RNDOFFERR ? etp * ctrl.dt : 0.0 ;
  double etotS   = bsn.getEvaporationS_all()->matrix[r][c] * ctrl.dt; //vegetation-summed Es (until this p)
  double SrftoL1 = bsn.getFluxSrftoL1()->matrix[r][c];

  double V_old, V_new;
  double dD_new, d18O_new, Age_new;

  // useful effective volume
  if(ctrl.sw_lifo){
    // If Evap < Infiltration: then only non-mixed rain evap/fractio, then mixes
    if(evapS <= SrftoL1){
      V_old = SrftoL1 > RNDOFFERR ? SrftoL1 : theta_lifo*d1 ;
      V_new = V_old - evapS;
    }
    else {
      V_old = theta_lifo*d1;
      V_new = V_old - (evapS - SrftoL1);
    }
  } else {
    V_new = theta_new*d1;
    V_old = V_new + evapS;
  }

  // -- dD ----------------------------------------------------------------------------
  if(ctrl.sw_dD){
    
    // LIFO: last in first out -------------------------
    if(ctrl.sw_lifo and SrftoL1>RNDOFFERR){
      // If Evap < Infiltration: then only non-mixed rain evap/fractionationes
      if(evapS <= SrftoL1){

	// Fractionation: check if there is evaporation!
	if(ctrl.sw_frac and evapS > RNDOFFERR)
	  Frac_Esoil(atm, bsn, ctrl, V_old, V_new, beta, 
		   _dDsurface->matrix[r][c], dD_new, dDevap, 
		     Ts, r, c, 0);
	else {
	  dD_new = _dDsurface->matrix[r][c];
	  dDevap = evapS > RNDOFFERR ? _dDsurface->matrix[r][c] : 0;
	}

	// Update 
	_dDlifo->matrix[r][c] = dD_new;
	_dDevapS_sum->matrix[r][c] = InputMix(etotS, _dDevapS_sum->matrix[r][c],
					      evapS, dDevap);

      } else {

	// If Evap > Infilt: whole infiltr evaporates and soil fractionates
	// with evap - infilt, dDevap is a weighted average
	if(ctrl.sw_frac)
	  Frac_Esoil(atm, bsn, ctrl, V_old, V_new, beta,
		   _dDsoil1->matrix[r][c], dD_new, dDevap, 
		     Ts, r, c, 0);
	else {
	  // ...all infiltr evap + part of evap takes L1 water
	  dD_new = _dDsoil1->matrix[r][c];
	  dDevap = InputMix(SrftoL1, _dDsurface->matrix[r][c],  evapS - SrftoL1, dD_new);
	}
	// Update: now only the topsoil is left
	_dDsoil1->matrix[r][c] = InputMix(theta_lifo*d1, _dDsoil1->matrix[r][c], V_new, dD_new);
	_dDevapS_sum->matrix[r][c] = InputMix(etotS, _dDevapS_sum->matrix[r][c], evapS, dDevap);
      }
      
      // No LIFO ------------------------------------
    } else {

      // If fractionation and no lifo, fractio acts over the whole L1
      // Safeguard with minimum E value: avoids diverging dD_E values
      if(ctrl.sw_frac and V_new/V_old<0.999)
	Frac_Esoil(atm, bsn, ctrl, V_old, V_new, beta,
		 _dDsoil1->matrix[r][c], dD_new, dDevap, 
		   Ts, r, c, 0);
      // If no fractionation (or negligible E) and no lifo, all from L1
      else {
	dD_new = _dDsoil1->matrix[r][c];
	dDevap = evapS > RNDOFFERR ? _dDsoil1->matrix[r][c] : 0;
      }
      // Finally, update
      _dDsoil1->matrix[r][c] = dD_new;
      _dDevapS_sum->matrix[r][c] = InputMix(etotS, _dDevapS_sum->matrix[r][c], evapS, dDevap);
    }
  }
  // -----------------------------------------------------------------------------------

  // -- d18O ---------------------------------------------------------------------------
  if(ctrl.sw_d18O){
    
    // LIFO: last in first out -------------------------
    if(ctrl.sw_lifo and SrftoL1>RNDOFFERR){
      // If Evap < Infiltration: then only non-mixed rain evap/fractionationes
      if(evapS <= SrftoL1){
	// Fractionation: check if there is evaporation!
	if(ctrl.sw_frac and evapS > RNDOFFERR){
	  Frac_Esoil(atm, bsn, ctrl, V_old, V_new, beta,
		     _d18Olifo->matrix[r][c], d18O_new, d18Oevap, 
		     Ts, r, c, 1);
	  _d18Olifo->matrix[r][c] = d18O_new;
	} else
	  d18Oevap = evapS > RNDOFFERR ? _d18Olifo->matrix[r][c] : 0;
	
      } else {
	// If Evap > Infilt: whole infiltr evaporates and soil fractionates
	// with evap - infilt, dDevap is a weighted average
	if(ctrl.sw_frac){
	  Frac_Esoil(atm, bsn, ctrl, V_old, V_new, beta,
		     _d18Osoil1->matrix[r][c], d18O_new, d18Oevap, 
		     Ts, r, c, 1);
	  _d18Osoil1->matrix[r][c] = d18O_new;
	} else
	  // ...all infiltr evap + part of evap takes L1 water
	  d18Oevap = InputMix(SrftoL1, _d18Olifo->matrix[r][c],  
			      evapS - SrftoL1, _d18Osoil1->matrix[r][c]);
      }
    
      // No LIFO ------------------------------------
    } else {
      // If fractionation and no lifo, fractio acts over the whole L1
      // Safeguard with minimum E value: avoids diverging d18O_E values
      if(ctrl.sw_frac and V_new/V_old<0.999){
	Frac_Esoil(atm, bsn, ctrl, V_old, V_new, beta,
		   _d18Osoil1->matrix[r][c], d18O_new, d18Oevap, 
		   Ts, r, c, 1);
	_d18Osoil1->matrix[r][c] = d18O_new;
      } else 
	// If no fractionation (or negligible E) and no lifo, all from L1
	d18Oevap = evapS > 0 ? _d18Osoil1->matrix[r][c] : 0;
    }
    
    // Finally, update
    _d18OevapS_sum->matrix[r][c] = InputMix(etotS, _d18OevapS_sum->matrix[r][c], evapS, d18Oevap);
  }
  // ----------------------------------------------------------------------------------
  
  // -- Water age ----------------------------------------------------------------------
  if(ctrl.sw_Age){

    // Last in first out: depends on how evap compares to infitlration
    if(ctrl.sw_lifo and SrftoL1>RNDOFFERR){
      if(evapS <= SrftoL1) {
	// ...the remainder of infiltration mixes now
	_Agelifo->matrix[r][c] = _Agesurface->matrix[r][c];
	Ageevap = evapS > RNDOFFERR ? _Agesurface->matrix[r][c] : 0;
      } else {
	// ...all infiltr evap + part of evap takes L1 water
	Ageevap = InputMix(SrftoL1, _Agesurface->matrix[r][c], 
			   evapS-SrftoL1, _Agesoil1->matrix[r][c]);
	
      }
      _AgeevapS_sum->matrix[r][c] = InputMix(etotS, _AgeevapS_sum->matrix[r][c], evapS, Ageevap);

      // No LIFO ------------------------------------
    } else {
      // All from L1: ages don't change from earlier mixing
      Ageevap = evapS > RNDOFFERR ? _Agesoil1->matrix[r][c] : 0 ;
      _AgeevapS_sum->matrix[r][c] = Ageevap;
    }
  }
  // -----------------------------------------------------------------------------------
  
}


