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
 *    Marco Maneta
 *******************************************************************************/
/*
 * GroveConstruct.cpp
 *
 *  Created on: Jun 17, 2010
 *      Author: marco
 */

#include "Grove.h"

Grove::Grove(){

	_fraction = NULL;
	_StemDensity = NULL;
	_LAI = NULL;
	_grassLAI_g = NULL;
	_grassLAI_d = NULL;
	_AGE = NULL;
	_CanopyConductance = NULL;
	_GPP = NULL;
	_NPP = NULL;
	_BasalArea = NULL;
	_Height = NULL;
	_RootMass = NULL;
	_Del_FoliageMass = NULL;
	_Del_StemMass = NULL;
	_Del_RootMass = NULL;
	_Temp_c = NULL;
	_NetR_Can = NULL;
	_LatHeat_Can = NULL;
	_SensHeat_Can = NULL;
	_WaterStorage = NULL;
	_ET = NULL;
	_Transpiration = NULL;
	_LeafWatPot = NULL;


}
