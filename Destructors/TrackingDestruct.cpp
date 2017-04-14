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
	if(_dDsoil3)
		delete _dDsoil3;
	//	if(_dDsoilAv)
	//		delete _dDsoilAv;
	if(_dDgroundwater)
		delete _dDgroundwater;
	if(_dDevapS)
		delete _dDevapS;
	if(_dDevapI_ToC)
		delete _dDevapI_ToC;
	if(_dDtranspi_ToC)
		delete _dDtranspi_ToC;

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
	if(_d18Osoil3)
		delete _d18Osoil3;
	//	if(_d18OsoilAv)
	//		delete _d18OsoilAv;
	if(_d18Ogroundwater)
		delete _d18Ogroundwater;
	if(_d18OevapS)
		delete _d18OevapS;
	if(_d18OevapI_ToC)
		delete _d18OevapI_ToC;
	if(_d18Otranspi_ToC)
		delete _d18Otranspi_ToC;

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
	if(_Agesoil3)
		delete _Agesoil3;
	//	if(_AgesoilAv)
	//		delete _AgesoilAv;
	if(_Agegroundwater)
		delete _Agegroundwater;
	if(_AgeevapS)
		delete _AgeevapS;
	if(_AgeevapI_ToC)
		delete _AgeevapI_ToC;
	if(_Agetranspi_ToC)
		delete _Agetranspi_ToC;
}
