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
 * TotalTrckStorage.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: Sylvain Kuppel
 */

#include "Budget.h"

void Budget::TotalStorage_d2H( const grid *Canopy, const grid *Canopy_d2H,
			      const grid *Snow, const grid *Snow_d2H,
			      const grid *Ponding, const grid *Ponding_d2H,
			      const grid *SoilL1, const grid *SoilL1_d2H,
			      const grid *SoilL2, const grid *SoilL2_d2H,
			      const grid *SoilL3, const grid *SoilL3_d2H,
			      const grid *GWater, const grid *GWater_d2H,
			      const Basin *b)//, const Control *ctrl)
{
  canopy_d2H = AccountTrckStorages(Canopy, Canopy_d2H, b);
  snowpack_d2H = AccountTrckStorages(Snow, Snow_d2H, b);
  ponding_d2H = AccountTrckStorages(Ponding, Ponding_d2H, b);
  soilL1_d2H = AccountTrckStorages(SoilL1, SoilL1_d2H, b);
  soilL2_d2H = AccountTrckStorages(SoilL2, SoilL2_d2H, b);
  soilL3_d2H = AccountTrckStorages(SoilL3, SoilL3_d2H, b);
  grndwater_d2H = AccountTrckStorages(GWater, GWater_d2H, b);
}

void Budget::TotalStorage_d18O( const grid *Canopy, const grid *Canopy_d18O,
			      const grid *Snow, const grid *Snow_d18O,
			      const grid *Ponding, const grid *Ponding_d18O,
			      const grid *SoilL1, const grid *SoilL1_d18O,
			      const grid *SoilL2, const grid *SoilL2_d18O,
			      const grid *SoilL3, const grid *SoilL3_d18O,
			      const grid *GWater, const grid *GWater_d18O,
				const Basin *b)//, const Control *ctrl)
{
  canopy_d18O = AccountTrckStorages(Canopy, Canopy_d18O, b);
  snowpack_d18O = AccountTrckStorages(Snow, Snow_d18O, b);
  ponding_d18O = AccountTrckStorages(Ponding, Ponding_d18O, b);
  soilL1_d18O = AccountTrckStorages(SoilL1, SoilL1_d18O, b);
  soilL2_d18O = AccountTrckStorages(SoilL2, SoilL2_d18O, b);
  soilL3_d18O = AccountTrckStorages(SoilL3, SoilL3_d18O, b);
  grndwater_d18O = AccountTrckStorages(GWater, GWater_d18O, b);
}

void Budget::TotalStorage_Age( const grid *Canopy, const grid *Canopy_Age,
			      const grid *Snow, const grid *Snow_Age,
			      const grid *Ponding, const grid *Ponding_Age,
			      const grid *SoilL1, const grid *SoilL1_Age,
			      const grid *SoilL2, const grid *SoilL2_Age,
			      const grid *SoilL3, const grid *SoilL3_Age,
			      const grid *GWater, const grid *GWater_Age,
			       const Basin *b)//, const Control *ctrl)
{
  canopy_Age = AccountTrckStorages(Canopy, Canopy_Age, b);
  snowpack_Age = AccountTrckStorages(Snow, Snow_Age, b);
  ponding_Age = AccountTrckStorages(Ponding, Ponding_Age, b);
  soilL1_Age = AccountTrckStorages(SoilL1, SoilL1_Age, b);
  soilL2_Age = AccountTrckStorages(SoilL2, SoilL2_Age, b);
  soilL3_Age = AccountTrckStorages(SoilL3, SoilL3_Age, b);
  grndwater_Age = AccountTrckStorages(GWater, GWater_Age, b);
}
