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
