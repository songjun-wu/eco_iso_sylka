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
	_dDcanopy = NULL;
	_dDsnowpack = NULL;
	_dDsurface = NULL;
	_dDsoil1 = NULL;
	_dDsoil2 = NULL;
	_dDsoil_12 = NULL;
	_dDsoil3 = NULL;
	//_dDsoilAv = NULL;
	_dDgroundwater = NULL;
	_dDevapS_sum = NULL;
	_dDevapI_sum = NULL;
	_dDtranspi_sum = NULL;

	_d18Ocanopy = NULL;
	_d18Osnowpack = NULL;
	_d18Osurface = NULL;
	_d18Osoil1 = NULL;
	_d18Osoil2 = NULL;
	_d18Osoil_12 = NULL;
	_d18Osoil3 = NULL;
	//_d18OsoilAv = NULL;
	_d18Ogroundwater = NULL;
	_d18OevapS_sum = NULL;
	_d18OevapI_sum = NULL;
	_d18Otranspi_sum = NULL;

	_Agecanopy = NULL;
	_Agesnowpack = NULL;
	_Agesurface = NULL;
	_Agesoil1 = NULL;
	_Agesoil2 = NULL;
	_Agesoil_12 = NULL;
	_Agesoil3 = NULL;
	//_AgesoilAv = NULL;
	_Agegroundwater = NULL;
	_AgeevapS_sum = NULL;
	_AgeevapI_sum = NULL;
	_Agetranspi_sum = NULL;

	if(!ctrl.sw_trck){
		ctrl.sw_dD = 0;
		ctrl.sw_d18O = 0;
		ctrl.sw_Age = 0;
	}

	try{
		if(ctrl.sw_dD){
			/*state variables initialized with the base map*/
			//_dDinput = new grid(*bsn.getDEM(), -60);
			//_dDcanopy = new grid(*bsn.getDEM(), -60);
			_dDsnowpack = new grid(ctrl.path_BasinFolder + ctrl.fn_dDsnowpack, ctrl.MapType);
			_dDsurface = new grid(ctrl.path_BasinFolder + ctrl.fn_dDsurface, ctrl.MapType);
			_dDsoil1 = new grid(ctrl.path_BasinFolder + ctrl.fn_dDsoil1, ctrl.MapType);
			_dDsoil2 = new grid(ctrl.path_BasinFolder + ctrl.fn_dDsoil2, ctrl.MapType);
			_dDsoil_12 = new grid(*bsn.getDEM());
			_dDsoil3 = new grid(ctrl.path_BasinFolder + ctrl.fn_dDsoil3, ctrl.MapType);
			//_dDsoilAv = new grid(*bsn.getDEM(), -60);
			_dDgroundwater = new grid(ctrl.path_BasinFolder + ctrl.fn_dDgroundwater, ctrl.MapType);
			_dDevapS_sum = new grid(*bsn.getDEM());
			_dDevapI_sum = new grid(*bsn.getDEM());
			_dDtranspi_sum = new grid(*bsn.getDEM());
		}

		if(ctrl.sw_d18O){
			//_d18Oinput = new grid(*bsn.getDEM(), -60);
			//_d18Ocanopy = new grid(*bsn.getDEM(), -60);
			_d18Osnowpack = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Osnowpack, ctrl.MapType);
			_d18Osurface = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Osurface, ctrl.MapType);
			_d18Osoil1 = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Osoil1, ctrl.MapType);
			_d18Osoil2 = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Osoil2, ctrl.MapType);
			_d18Osoil_12 = new grid(*bsn.getDEM());
			_d18Osoil3 = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Osoil3, ctrl.MapType);
			//_d18OsoilAv = new grid(*bsn.getDEM(), -60);
			_d18Ogroundwater = new grid(ctrl.path_BasinFolder + ctrl.fn_d18Ogroundwater, ctrl.MapType);
			_d18OevapS_sum = new grid(*bsn.getDEM());
			_d18OevapI_sum = new grid(*bsn.getDEM());
			_d18Otranspi_sum = new grid(*bsn.getDEM());
		}

		if(ctrl.sw_Age){
			//_Ageinput = new grid(*bsn.getDEM(), -60);
			//_Agecanopy = new grid(*bsn.getDEM(), -60);
			_Agesnowpack = new grid(ctrl.path_BasinFolder + ctrl.fn_Agesnowpack, ctrl.MapType);
			_Agesurface = new grid(ctrl.path_BasinFolder + ctrl.fn_Agesurface, ctrl.MapType);
			_Agesoil1 = new grid(ctrl.path_BasinFolder + ctrl.fn_Agesoil1, ctrl.MapType);
			_Agesoil2 = new grid(ctrl.path_BasinFolder + ctrl.fn_Agesoil2, ctrl.MapType);
			_Agesoil_12 = new grid(*bsn.getDEM());
			_Agesoil3 = new grid(ctrl.path_BasinFolder + ctrl.fn_Agesoil3, ctrl.MapType);
			//_AgesoilAv = new grid(*bsn.getDEM(), -60);
			_Agegroundwater = new grid(ctrl.path_BasinFolder + ctrl.fn_Agegroundwater, ctrl.MapType);
			_AgeevapS_sum = new grid(*bsn.getDEM());
			_AgeevapI_sum = new grid(*bsn.getDEM());
			_Agetranspi_sum = new grid(*bsn.getDEM());
		}

		//Partial check of maps mainly to make sure no no data is written within the valid domain
		CheckMapsTrck(ctrl, bsn);

	}catch (std::bad_alloc &)
	{ cerr << " Cleaning tracking objects..." << "\n";
	//	if(_dDinput)
	//		delete _dDinput;
	//	if(_dDcanopy)
	//		delete _dDcanopy;
	if(_dDsnowpack)
		delete _dDsnowpack;
	if(_dDsurface)
		delete _dDsurface;
	if(_dDsoil1)
		delete _dDsoil1;
	if(_dDsoil2)
		delete _dDsoil2;
	if(_dDsoil_12)
		delete _dDsoil_12;
	if(_dDsoil3)
		delete _dDsoil3;
	//	if(_dDsoilAv)
	//		delete _dDsoilAv;
	if(_dDgroundwater)
		delete _dDgroundwater;
	if(_dDevapS_sum)
		delete _dDevapS_sum;
	if(_dDevapI_sum)
		delete _dDevapI_sum;
	if(_dDtranspi_sum)
		delete _dDtranspi_sum;

	//	if(_d18Oinput)
	//		delete _d18Oinput;
	//	if(_d18Ocanopy)
	//		delete _d18Ocanopy;
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
	//	if(_d18OsoilAv)
	//		delete _d18OsoilAv;
	if(_d18Ogroundwater)
		delete _d18Ogroundwater;
	if(_d18OevapS_sum)
		delete _d18OevapS_sum;
	if(_d18OevapI_sum)
		delete _d18OevapI_sum;
	if(_d18Otranspi_sum)
		delete _d18Otranspi_sum;

	//	if(_Agecanopy)
	//		delete _Agecanopy;
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
	//	if(_AgesoilAv)
	//		delete _AgesoilAv;
	if(_Agegroundwater)
		delete _Agegroundwater;
	if(_AgeevapS_sum)
		delete _AgeevapS_sum;
	if(_AgeevapI_sum)
		delete _AgeevapI_sum;
	if(_Agetranspi_sum)
		delete _Agetranspi_sum;

	throw;
	}

}
