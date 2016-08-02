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
 * CalculateBudgets.cpp
 *
 *  Created on: Aug 2, 2010
 *      Author: Marco.Maneta
 */

#include "Sativa.h"

int CalculateBudgets(){

			oBudget->TotalPrecipitation(oAtmosphere->getPrecipitation(), oAtmosphere);
			oBudget->TotalEvaporation(oBasin->getEvaporation(), oBasin);
			oBudget->TotalBedrockLeakage(oBasin->getBedrockLeakage(), oBasin);
			oBudget->TotalOvlndFlow(oBasin->getDailyOvlndOutput(), oBasin);
			oBudget->TotalGrndFlow(oBasin->getDailyGwtrOutput(), oBasin);
			oBudget->TotalStorage(	oBasin->getCanopyStorage(),
									oBasin->getSnowWaterEquiv(),
									oBasin->getPondingWater(),
									oBasin->getSoilWaterDepth(),
									oBasin->getGravityWater(),
									oBasin->getGrndWater(),
									oBasin);
			oBudget->MassBalanceError();

		return EXIT_SUCCESS;
}
