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
	oBasin->DailyGWRouting(*oAtmosphere, *oControl);

		return EXIT_SUCCESS;
}
