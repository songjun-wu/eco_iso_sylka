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
 * TotalStorage.cpp
 *
 *  Created on: Mar 18, 2010
 *      Author: Marco Maneta
 */

#include "Budget.h"

void Budget::TotalStorage( const grid *Canopy,
		const grid *Snow,
		const grid *Ponding,
		//const grid *Vadose,
		const grid *SoilL1,
		const grid *SoilL2,
		const grid *SoilL3,
		//const grid *GravWater,
		const grid *GrndWater,
		const Basin *b)
{
	canopy = AccountStorages(Canopy, b);
	snowpack = AccountStorages(Snow, b);
	ponding = AccountStorages(Ponding, b);
	//vadose = AccountStorages(Vadose, b);
	soilL1 = AccountStorages(SoilL1, b);
	soilL2 = AccountStorages(SoilL2, b);
	soilL3 = AccountStorages(SoilL3, b);
	//gravwater = AccountStorages(GravWater, b);
	grndwater = AccountStorages(GrndWater, b);
	vadose = soilL1 + soilL2 + soilL3 + grndwater;
}
