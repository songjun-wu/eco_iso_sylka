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
 * TrackingDestruct.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: Sylvain Kuppel
 */

#include "Tracking.h"

Tracking::~Tracking(){
  
	    if(_d2Hcanopy_sum)
	      delete _d2Hcanopy_sum;
	    if(_d2Hsnowpack)
	      delete _d2Hsnowpack;
	    if(_d2Hsurface)
	      delete _d2Hsurface;
	    if(_d2Hsoil1)
	      delete _d2Hsoil1;
	    if(_d2Hsoil2)
	      delete _d2Hsoil2;
	    if(_d2Hsoil_12)
	      delete _d2Hsoil_12;
	    if(_d2Hsoil3)
	      delete _d2Hsoil3;
	    if(_d2HsoilAv)
	      delete _d2HsoilAv;
	    if(_d2Hgroundwater)
	      delete _d2Hgroundwater;
	    if(_d2HevapS_sum)
	      delete _d2HevapS_sum;
	    if(_d2HevapI_sum)
	      delete _d2HevapI_sum;
	    if(_d2HevapT_sum)
	      delete _d2HevapT_sum;
	    if(_d2Hleakage)
	      delete _d2Hleakage;
	    
	    if(_d18Ocanopy_sum)
	      delete _d18Ocanopy_sum;
	    if(_d18Osnowpack)
	      delete _d18Osnowpack;
	    if(_d18Osurface)
	      delete _d18Osurface;
	    if(_d18Osoil1)
	      delete _d18Osoil1;
	    if(_d18Osoil2)
	      delete _d18Osoil2;
	    if(_d18Osoil_12)
	      delete _d18Osoil_12;
	    if(_d18Osoil3)
	      delete _d18Osoil3;
	    if(_d18OsoilAv)
	      delete _d18OsoilAv;
	    if(_d18Ogroundwater)
	      delete _d18Ogroundwater;
	    if(_d18OevapS_sum)
	      delete _d18OevapS_sum;
	    if(_d18OevapI_sum)
	      delete _d18OevapI_sum;
	    if(_d18OevapT_sum)
	      delete _d18OevapT_sum;
	    if(_d18Oleakage)
	      delete _d18Oleakage;
	    
	    if(_Agecanopy_sum)
	      delete _Agecanopy_sum;
	    if(_Agesnowpack)
	      delete _Agesnowpack;
	    if(_Agesurface)
	      delete _Agesurface;
	    if(_Agesoil1)
	      delete _Agesoil1;
	    if(_Agesoil2)
	      delete _Agesoil2;
	    if(_Agesoil_12)
	      delete _Agesoil_12;
	    if(_Agesoil3)
	      delete _Agesoil3;
	    if(_AgesoilAv)
	      delete _AgesoilAv;
	    if(_Agegroundwater)
	      delete _Agegroundwater;
	    if(_AgeevapS_sum)
	      delete _AgeevapS_sum;
	    if(_AgeevapI_sum)
	      delete _AgeevapI_sum;
	    if(_AgeevapT_sum)
	      delete _AgeevapT_sum;
	    if(_Ageleakage)
	      delete _Ageleakage;
}
