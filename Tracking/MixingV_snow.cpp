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
 * MixingV_snow.cpp
 *
 *  Created on: Jun 21, 2017
 *      Author: Sylvain Kuppel
 */

#include "Basin.h"

void Tracking::MixingV_snow(Atmosphere &atm, Basin &bsn, Control &ctrl,
			    double &dh_snow, int r, int c) //time step
{
  
  double V_new;
  double snow_old = bsn.getSnowWaterEquiv()->matrix[r][c];
  double snow_in = bsn.getFluxUptoSnow()->matrix[r][c];
  double pond_old = bsn.getPondingWater()->matrix[r][c];
  
  // - in snowpack (snowfall in + snowmelt out), considering that snowmelt "flushes" the most recent snowfall first, without mixing
  // - in the surface pool, mixing of snowmelt
  
  // Case where there is more snowfall than snowmelt: snowpack mixed, snowmelt has snowfall signature
  if(snow_in > dh_snow){

    V_new = snow_in - dh_snow;

    if(ctrl.sw_dD){
      // Snowpack: last (same timestep) in, first melt
      _dDsnowpack->matrix[r][c] = InputMix(snow_old, _dDsnowpack->matrix[r][c],
					   V_new, atm.getdDprecip()->matrix[r][c]);
      // Surface: snowfall (=rain) signature
      _dDsurface->matrix[r][c] = InputMix(pond_old, _dDsurface->matrix[r][c],
					  dh_snow, atm.getdDprecip()->matrix[r][c]);
    }
    if(ctrl.sw_d18O){
      // Snowpack: last (same timestep) in, first melt
      _d18Osnowpack->matrix[r][c] = InputMix(snow_old, _d18Osnowpack->matrix[r][c],
					     V_new, atm.getd18Oprecip()->matrix[r][c]);
      // Surface: snowfall (=rain) signature
      _d18Osurface->matrix[r][c] = InputMix(pond_old, _d18Osurface->matrix[r][c],
					    dh_snow, atm.getd18Oprecip()->matrix[r][c]);
    }
    if(ctrl.sw_Age){
      // Snowpack: last (same timestep) in, first melt
      _Agesnowpack->matrix[r][c] = InputMix(snow_old, _Agesnowpack->matrix[r][c],
					    V_new, 0.0);
      // Surface: snowfall (=rain) signature
      _Agesurface->matrix[r][c] = InputMix(pond_old, _Agesurface->matrix[r][c],
					   dh_snow, 0.0);
    }

  } else {

    // Case where there is more snowmelt than snowfall: no mixing in snowpack, snowmelt has mixed signature
    V_new = dh_snow - snow_in;

    if(ctrl.sw_dD){
      // Snowpack: no change (all recent snow has melted)
      // Surface: weighted snowfall (=rain) signature and previous snowpack
      _dDsurface->matrix[r][c] = InputMix(pond_old, _dDsurface->matrix[r][c], dh_snow,
					  // Ugly and "convoluted", but no waste of temp variables
					  InputMix(V_new, _dDsnowpack->matrix[r][c],
						   snow_in, atm.getdDprecip()->matrix[r][c]));
    }
    if(ctrl.sw_d18O){
      // Snowpack: no change (all recent snow has melted)
      // Surface: weighted snowfall (=rain) signature and previous snowpack
      _d18Osurface->matrix[r][c] = InputMix(pond_old, _d18Osurface->matrix[r][c], dh_snow,
					    // Ugly and "convoluted", but no waste of temp variables
					    InputMix(V_new, _d18Osnowpack->matrix[r][c],
						     snow_in, atm.getd18Oprecip()->matrix[r][c]));
    }
    if(ctrl.sw_Age){
      // Snowpack: no change (all snow in melted)
      // Surface: weighted snowfall (=rain) signature and previous snowpack
      _Agesurface->matrix[r][c] = InputMix(pond_old, _Agesurface->matrix[r][c], dh_snow,
					   // Ugly and "convoluted", but no waste of temp variables
					   InputMix(V_new, _Agesnowpack->matrix[r][c],
						    snow_in, 0.0));
    }
  }
  
}


