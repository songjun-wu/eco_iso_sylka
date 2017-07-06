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
			     int r, int c)
{

  double evapS_f = bsn.getEvaporationS_all()->matrix[r][c] * ctrl.dt;
  double SrftoL1 = bsn.getFluxSrftoL1()->matrix[r][c];

  double V_new;
  double dD_new, d18O_new, Age_new;
  double dDevap, d18Oevap, Ageevap;

  // useful effective volume
  if(ctrl.sw_lifo){
    // If Evap < Infiltration: then only non-mixed rain evap/fractio, then mixes
    if(evapS_f < SrftoL1)
      V_new = SrftoL1 - evapS_f;
    else
      V_new = theta_lifo*d1 - (evapS_f - SrftoL1);
  }

  // -- dD
  if(ctrl.sw_dD){
    // Fractionation and last in first out
    if(ctrl.sw_frac and ctrl.sw_lifo){
      // If Evap < Infiltration: then only non-mixed rain evap/fractio, then mixes
      if(evapS_f < SrftoL1){
	dDfrac_E(atm, bsn, ctrl, SrftoL1, V_new,
		      _dDsurface->matrix[r][c], dD_new, dDevap, r, c);
	dD_new = InputMix(theta_lifo*d1, _dDsoil1->matrix[r][c], V_new, dD_new);
      } else {
	// If Evap > Infilt: whole infiltr evaporates and soil fractionates
	// with evap - infilt, dDevap is a weighted average
	dDfrac_E(atm, bsn, ctrl, theta_lifo*d1, V_new,
		      _dDsoil1->matrix[r][c], dD_new, dDevap, r, c);
	dDevap = (SrftoL1*_dDsurface->matrix[r][c] + (evapS_f - SrftoL1)*dDevap)/ evapS_f ;
      }
    }

    // If fractionation and no lifo, fractio acts over the whole L1
    if(ctrl.sw_frac and !ctrl.sw_lifo)
      dDfrac_E(atm, bsn, ctrl, bsn.getSoilMoist1()->matrix[r][c], theta_new,
		    _dDsoil1->matrix[r][c], dD_new, dDevap, r, c);

    // If no fractionation and lifo, either...
    if(!ctrl.sw_frac and ctrl.sw_lifo){
      if(evapS_f < SrftoL1) {
	// ...the remainder of infiltration mixes now
	dD_new = InputMix(theta_lifo*d1, _dDsoil1->matrix[r][c], V_new, 
			       _dDsurface->matrix[r][c]);
	dDevap = _dDsurface->matrix[r][c];
      } else {
	// ...all infiltr evap + part of evap takes L1 water
	dD_new = _dDsoil1->matrix[r][c];
	dDevap = (SrftoL1*_dDsurface->matrix[r][c] + (evapS_f - SrftoL1)*dD_new)/ evapS_f	;
	
      }
    }

    // If no fractionation and no lifo, all from L1
    if(!ctrl.sw_frac and !ctrl.sw_lifo){
      dD_new = _dDsoil1->matrix[r][c];
      dDevap = _dDsoil1->matrix[r][c];
    }

    // Finally, update
    _dDsoil1->matrix[r][c] = dD_new;
    _dDevapS_sum->matrix[r][c] = dDevap;
  }

  // -- d18O
  if(ctrl.sw_d18O){

    // Fractionation and last in first out
    if(ctrl.sw_frac and ctrl.sw_lifo){
      // If Evap < Infiltration: then only non-mixed rain evap/fractio, then mixes
      if(evapS_f < SrftoL1){
	d18Ofrac_E(atm, bsn, ctrl, SrftoL1, V_new,
			_d18Osurface->matrix[r][c], d18O_new, d18Oevap, r, c);
	d18O_new = InputMix(theta_lifo*d1, _d18Osoil1->matrix[r][c], V_new, d18O_new);
      } else {
	// If Evap > Infilt: whole infiltr evaporates and soil fractionates
	// with evap - infilt, d18Oevap is a weighted average
	d18Ofrac_E(atm, bsn, ctrl, theta_lifo*d1,
			V_new,	_d18Osoil1->matrix[r][c], d18O_new, d18Oevap, r, c);
	d18Oevap = (SrftoL1*_d18Osurface->matrix[r][c] + (evapS_f - SrftoL1)*d18Oevap)/ evapS_f ;
      }
    }

    // If fractionation and no lifo, fractio acts over the whole L1
    if(ctrl.sw_frac and !ctrl.sw_lifo)
      d18Ofrac_E(atm, bsn, ctrl, bsn.getSoilMoist1()->matrix[r][c], theta_new,
		      _d18Osoil1->matrix[r][c], d18O_new, d18Oevap, r, c);

    // If no fractionation and lifo, either...
    if(!ctrl.sw_frac and ctrl.sw_lifo){
      if(evapS_f<SrftoL1) {
	// ...the remainder of infiltration mixes now
	d18O_new = InputMix(theta_lifo*d1, _d18Osoil1->matrix[r][c],
				 V_new, _d18Osurface->matrix[r][c]);
	d18Oevap = _d18Osurface->matrix[r][c];
      } else {
	// ...all infiltr evap + part of evap takes L1 water
	d18O_new = _d18Osoil1->matrix[r][c];
	d18Oevap = (SrftoL1*_d18Osurface->matrix[r][c] + (evapS_f - SrftoL1)*d18O_new)/ evapS_f ;
      }
    }

    // If no fractionation and no lifo, all from L1
    if(!ctrl.sw_frac and !ctrl.sw_lifo){
      d18O_new = _d18Osoil1->matrix[r][c];
      d18Oevap = _d18Osoil1->matrix[r][c];
    }
    
    // Finally, update
    _d18Osoil1->matrix[r][c] = d18O_new;
    _d18OevapS_sum->matrix[r][c] = d18Oevap;
  }
  
  // Water age
  if(ctrl.sw_Age){

    // Last in first out: depends on how evap compares to infitlration
    if(ctrl.sw_lifo){
      if(evapS_f<SrftoL1) {
	// ...the remainder of infiltration mixes now
	Age_new = InputMix(theta_lifo*d1, _Agesoil1->matrix[r][c],
				V_new, _Agesurface->matrix[r][c]);
	Ageevap = _Agesurface->matrix[r][c];
      } else {
	// ...all infiltr evap + part of evap takes L1 water
	Age_new = _Agesoil1->matrix[r][c];
	Ageevap = (SrftoL1*_Agesurface->matrix[r][c] + (evapS_f - SrftoL1)*Age_new)/ evapS_f	;
	
      }
    } else {
      // If no fractionation and no lifo, all from L1:
      // ages don't change from earlier mixing
      Age_new = _Agesoil1->matrix[r][c];
      Ageevap = _Agesoil1->matrix[r][c];
    }
    // Finally, update
    _Agesoil1->matrix[r][c] = Age_new;
    _AgeevapS_sum->matrix[r][c] = Ageevap;
  }
  
}


