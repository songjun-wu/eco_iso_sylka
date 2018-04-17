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
 * CalculateBudgets.cpp
 *
 *  Created on: Aug 2, 2010
 *      Author: Marco.Maneta
 */

#include "Sativa.h"

int CalculateBudgets(){

  // Tracking input/output age (Accumulated) ----------------------------------------------------
  // place before the actual fluxes because these age calculation requires previous-step 
  // in/out flux budgets
  // Tracking -------------------------------------------------------------------------------------
  if(oControl->sw_trck){
    // Deuterium
    if (oControl->sw_2H){
      oBudget->TotalPrecipitation_d2H(oAtmosphere->getPrecipitation(), oAtmosphere->getd2Hprecip(), 
				     oAtmosphere);
      oBudget->TotalEvaporationS_d2H(oBasin->getEvaporationS_all(), oTracking->getd2HevapS_sum(), 
				    oBasin);
      oBudget->TotalEvaporationI_d2H(oBasin->getEvaporationI_all(), oTracking->getd2HevapI_sum(), 
				    oBasin);
      oBudget->TotalTranspiration_d2H(oBasin->getTranspiration_all(), oTracking->getd2HevapT_sum(), 
				     oBasin);
      oBudget->TotalBedrockLeakage_d2H(oBasin->getBedrockLeakage(), oTracking->getd2Hleakage(), oBasin);
      oBudget->TotalOvlndFlow_d2H(oBasin->getDailyOvlndOutput(), oTracking->getd2HOvlndOutput());
      oBudget->TotalGrndFlow_d2H(oBasin->getDailyGwtrOutput(), oTracking->getd2HGwtrOutput());
      oBudget->TotalStorage_d2H(oBasin->getCanopyStorage(), oTracking->getd2Hcanopy_sum(),
			       oBasin->getSnowWaterEquiv(),  oTracking->getd2Hsnowpack(),
			       oBasin->getPondingWater(), oTracking->getd2Hsurface(),
			       oBasin->getSoilWaterDepthL1(), oTracking->getd2Hsoil1(),
			       oBasin->getSoilWaterDepthL2(), oTracking->getd2Hsoil2(),
			       oBasin->getSoilWaterDepthL3(), oTracking->getd2Hsoil3(),
			       oBasin->getGrndWater(), oTracking->getd2Hgroundwater(),
			       oBasin);//, oControl);
    }
    // Oxygen 18
    if (oControl->sw_18O){
      oBudget->TotalPrecipitation_d18O(oAtmosphere->getPrecipitation(), oAtmosphere->getd18Oprecip(), 
				       oAtmosphere);
      oBudget->TotalEvaporationS_d18O(oBasin->getEvaporationS_all(), oTracking->getd18OevapS_sum(), 
					oBasin);
      oBudget->TotalEvaporationI_d18O(oBasin->getEvaporationI_all(), oTracking->getd18OevapI_sum(), 
				      oBasin);
      oBudget->TotalTranspiration_d18O(oBasin->getTranspiration_all(), oTracking->getd18OevapT_sum(), 
				       oBasin);
      oBudget->TotalBedrockLeakage_d18O(oBasin->getBedrockLeakage(), oTracking->getd18Oleakage(), 
					oBasin);
      oBudget->TotalOvlndFlow_d18O(oBasin->getDailyOvlndOutput(), oTracking->getd18OOvlndOutput());
      oBudget->TotalGrndFlow_d18O(oBasin->getDailyGwtrOutput(), oTracking->getd18OGwtrOutput());
      oBudget->TotalStorage_d18O(oBasin->getCanopyStorage(), oTracking->getd18Ocanopy_sum(),
				 oBasin->getSnowWaterEquiv(),  oTracking->getd18Osnowpack(),
				 oBasin->getPondingWater(), oTracking->getd18Osurface(),
				 oBasin->getSoilWaterDepthL1(), oTracking->getd18Osoil1(),
				 oBasin->getSoilWaterDepthL2(), oTracking->getd18Osoil2(),
				 oBasin->getSoilWaterDepthL3(), oTracking->getd18Osoil3(),
				 oBasin->getGrndWater(), oTracking->getd18Ogroundwater(),
				 oBasin);//, oControl);
    }
    // Age
    if (oControl->sw_Age){
      oBudget->TotalPrecipitation_Age();
      //oAtmosphere->getPrecipitation(), oAtmosphere);//, oControl);
      //oBudget->precipitation_Age += oBudget
      oBudget->TotalEvaporationS_Age(oBasin->getEvaporationS_all(), oTracking->getAgeevapS_sum(), 
				     oBasin);
      oBudget->TotalEvaporationI_Age(oBasin->getEvaporationI_all(), oTracking->getAgeevapI_sum(), 
				     oBasin);
      oBudget->TotalTranspiration_Age(oBasin->getTranspiration_all(), oTracking->getAgeevapT_sum(), 
				      oBasin);
      oBudget->TotalBedrockLeakage_Age(oBasin->getBedrockLeakage(), oTracking->getAgeleakage(), 
				       oBasin);
      oBudget->TotalOvlndFlow_Age(oBasin->getDailyOvlndOutput(), oTracking->getAgeOvlndOutput());
      oBudget->TotalGrndFlow_Age(oBasin->getDailyGwtrOutput(), oTracking->getAgeGwtrOutput());
      oBudget->TotalStorage_Age(oBasin->getCanopyStorage(), oTracking->getAgecanopy_sum(),
				oBasin->getSnowWaterEquiv(),  oTracking->getAgesnowpack(),
				oBasin->getPondingWater(), oTracking->getAgesurface(),
				oBasin->getSoilWaterDepthL1(), oTracking->getAgesoil1(),
				oBasin->getSoilWaterDepthL2(), oTracking->getAgesoil2(),
				oBasin->getSoilWaterDepthL3(), oTracking->getAgesoil3(),
				oBasin->getGrndWater(), oTracking->getAgegroundwater(),
				oBasin);//, oControl);
    }

    oBudget->TrckBalanceError(oControl);
  } // ---------------------------------------------------------------------------------------------

  oBudget->TotalPrecipitation(oAtmosphere->getPrecipitation(), oAtmosphere);
  oBudget->TotalEvaporation(oBasin->getEvaporation(), oBasin);
  oBudget->TotalEvaporationS(oBasin->getEvaporationS_all(), oBasin);
  oBudget->TotalEvaporationI(oBasin->getEvaporationI_all(), oBasin);
  oBudget->TotalTranspiration(oBasin->getTranspiration_all(), oBasin);
  oBudget->TotalBedrockLeakage(oBasin->getBedrockLeakage(), oBasin);
  oBudget->TotalOvlndFlow(oBasin->getDailyOvlndOutput(), oBasin);
  oBudget->TotalGrndFlow(oBasin->getDailyGwtrOutput(), oBasin);
  oBudget->TotalStorage(	oBasin->getCanopyStorage(),
				oBasin->getSnowWaterEquiv(),
				oBasin->getPondingWater(),
				//oBasin->getSoilWaterDepth(),
				oBasin->getSoilWaterDepthL1(),
				oBasin->getSoilWaterDepthL2(),
				oBasin->getSoilWaterDepthL3(),
				//oBasin->getGravityWater(),
				oBasin->getGrndWater(),
				oBasin);
  oBudget->TotalSaturationArea(oBasin->getSatArea(), oBasin);
  oBudget->TotalGWtoChn(oBasin->getFluxGWtoChn(), oBasin);
  oBudget->TotalSrftoChn(oBasin->getFluxSrftoChn(), oBasin);

  oBudget->MassBalanceError();
  
  return EXIT_SUCCESS;
}
