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
 * IsotopeConstruct.cpp
 *
 *  Created on: Nov 14, 2016
 *      Author: Sylvain Kuppel
 */

#include "Tracking.h"

Tracking::Tracking(Control &ctrl, Basin &bsn)
{

	// Construct NULL pointer in case the object is not fully constructed
	// (avoids memory leak)
	_d2Hcanopy_sum = NULL;
	_d2Hsnowpack = NULL;
	_d2Hsurface = NULL;
	_d2Hsoil1 = NULL;
	_d2Hsoil2 = NULL;
	_d2Hsoil_12 = NULL;
	_d2Hsoil3 = NULL;
	_d2HsoilAv = NULL;
	_d2Hgroundwater = NULL;
	_d2HevapS_sum = NULL;
	_d2HevapI_sum = NULL;
	_d2HevapT_sum = NULL;
	_d2Hleakage = NULL;

	_d18Ocanopy_sum = NULL;
	_d18Osnowpack = NULL;
	_d18Osurface = NULL;
	_d18Osoil1 = NULL;
	_d18Osoil2 = NULL;
	_d18Osoil_12 = NULL;
	_d18Osoil3 = NULL;
	_d18OsoilAv = NULL;
	_d18Ogroundwater = NULL;
	_d18OevapS_sum = NULL;
	_d18OevapI_sum = NULL;
	_d18OevapT_sum = NULL;
	_d18Oleakage = NULL;

	_Agecanopy_sum = NULL;
	_Agesnowpack = NULL;
	_Agesurface = NULL;
	_Agesoil1 = NULL;
	_Agesoil2 = NULL;
	_Agesoil_12 = NULL;
	_Agesoil3 = NULL;
	_AgesoilAv = NULL;
	_Agegroundwater = NULL;
	_AgeevapS_sum = NULL;
	_AgeevapI_sum = NULL;
	_AgeevapT_sum = NULL;
	_Ageleakage = NULL;

	if(!ctrl.sw_trck){
		ctrl.sw_2H = 0;
		ctrl.sw_18O = 0;
		ctrl.sw_Age = 0;
	}

	try{
	  if(ctrl.sw_2H){
	    /*state variables initialized with the base map*/
	    _d2Hcanopy_sum = new grid(*bsn.getDEM());
	    _d2Hsnowpack = new grid(ctrl.path_BasinFolder+ctrl.fn_d2Hsnowpack, ctrl.MapType);
	    _d2Hsurface = new grid(ctrl.path_BasinFolder + ctrl.fn_d2Hsurface, ctrl.MapType);
	    _d2Hsoil1 = new grid(ctrl.path_BasinFolder + ctrl.fn_d2Hsoil1, ctrl.MapType);
	    _d2Hsoil2 = new grid(ctrl.path_BasinFolder + ctrl.fn_d2Hsoil2, ctrl.MapType);
	    _d2Hsoil_12 = new grid(*bsn.getDEM());
	    _d2Hsoil3 = new grid(ctrl.path_BasinFolder + ctrl.fn_d2Hsoil3, ctrl.MapType);
	    _d2HsoilAv = new grid(*bsn.getDEM());
	    _d2Hgroundwater = new grid(ctrl.path_BasinFolder + ctrl.fn_d2Hgroundwater, ctrl.MapType);
	    _d2HevapS_sum = new grid(*bsn.getDEM());
	    _d2HevapI_sum = new grid(*bsn.getDEM());
	    _d2HevapT_sum = new grid(*bsn.getDEM());
	    _d2Hleakage = new grid(*bsn.getDEM());
	  }
	  
	  if(ctrl.sw_18O){
	    //_d18Oinput = new grid(*bsn.getDEM(), -60);
	    _d18Ocanopy_sum = new grid(*bsn.getDEM());
	    _d18Osnowpack = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Osnowpack, ctrl.MapType);
	    _d18Osurface = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Osurface, ctrl.MapType);
	    _d18Osoil1 = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Osoil1, ctrl.MapType);
	    _d18Osoil2 = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Osoil2, ctrl.MapType);
	    _d18Osoil3 = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Osoil3, ctrl.MapType);
	    _d18Ogroundwater = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Ogroundwater, ctrl.MapType);
	    _d18OevapS_sum = new grid(*bsn.getDEM());
	    _d18OevapI_sum = new grid(*bsn.getDEM());
	    _d18OevapT_sum = new grid(*bsn.getDEM());
	    _d18Oleakage = new grid(*bsn.getDEM());	    
	  }
	  
	  if(ctrl.sw_Age){
	    //_Ageinput = new grid(*bsn.getDEM(), -60);
	    _Agecanopy_sum = new grid(*bsn.getDEM());
	    _Agesnowpack = new grid(ctrl.path_BasinFolder + ctrl.fn_Agesnowpack, ctrl.MapType);
	    _Agesurface = new grid(ctrl.path_BasinFolder + ctrl.fn_Agesurface, ctrl.MapType);
	    _Agesoil1 = new grid(ctrl.path_BasinFolder + ctrl.fn_Agesoil1, ctrl.MapType);
	    _Agesoil2 = new grid(ctrl.path_BasinFolder + ctrl.fn_Agesoil2, ctrl.MapType);
	    _Agesoil_12 = new grid(*bsn.getDEM());
	    _Agesoil3 = new grid(ctrl.path_BasinFolder + ctrl.fn_Agesoil3, ctrl.MapType);
	    _AgesoilAv = new grid(*bsn.getDEM());
	    _Agegroundwater = new grid(ctrl.path_BasinFolder + ctrl.fn_Agegroundwater, ctrl.MapType);
	    _AgeevapS_sum = new grid(*bsn.getDEM());
	    _AgeevapI_sum = new grid(*bsn.getDEM());
	    _AgeevapT_sum = new grid(*bsn.getDEM());
	    _Ageleakage = new grid(*bsn.getDEM());
	  }
	  
	  //Partial check of maps mainly to make sure no no data is written within the valid domain
	  CheckMapsTrck(ctrl, bsn);
	  
	}catch (std::bad_alloc &)
	  { cerr << " Cleaning tracking objects..." << "\n";
	    
	    // Ratios
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
	    	    
	    throw;
	  }
	
}
