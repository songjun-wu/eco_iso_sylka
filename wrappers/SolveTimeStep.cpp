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
 * SolveTimeStep.cpp
 *
 *  Created on: Aug 2, 2010
 *      Author: Marco.Maneta
 */
#include <iostream>
#include "Sativa.h"


int SolveTimeStep(){


	//oBasin->UpdateSnowPack(*oAtmosphere, *oControl);
	oBasin->SolveCanopyFluxes(*oAtmosphere, *oControl);
	oBasin->SolveSurfaceFluxes(*oAtmosphere, *oControl);
	oBasin->CalculateGrowForest(*oAtmosphere, *oControl);
	//oBasin->DailySurfaceRouting(*oAtmosphere, *oControl);
	//if(oControl->toggle_soil_water_profile < 2)
	oBasin->DailyGWRouting(*oAtmosphere, *oControl);
	oBasin->CalculateSatArea(*oAtmosphere, *oControl);

		return EXIT_SUCCESS;
}
