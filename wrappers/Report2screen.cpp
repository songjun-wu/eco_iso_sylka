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
 * Report2screen.cpp
 *
 *  Created on: Aug 2, 2010
 *      Author: Marco.Maneta
 */

#include "Sativa.h"

int Report2Screen(){

	printf("\nTotal Precipitation (m3):  %.2f \t", oBudget->precipitation);
	//cout << "Total Precipitation (m3): " << oBudget->precipitation << "\t";
	ofSummary << oBudget->precipitation << "\t";

	printf("SWE (m3): %.2f \n", oBudget->snowpack);
	//cout << "SWE (m3): " << oBudget->snowpack << "\t";
	ofSummary << oBudget->snowpack << "\t";

	printf("Canopy Storage (m3): %.2f \t", oBudget->canopy);
	//cout << "Canopy Storage (m3): " << oBudget->canopy << "\n";
	ofSummary << oBudget->canopy << "\t";

	printf("Ponding (m3): %.2f \n", oBudget->ponding);
	//cout << "Ponding: " << oBudget->ponding << "\t";
	ofSummary << oBudget->ponding << "\t";

	printf("Soil water (m3): %.2f \t", oBudget->vadose);
	//cout << "Soil water (m3): " << oBudget->vadose << "\n";
	ofSummary << oBudget->vadose << "\t";

	printf("of which Groundwater (m3): %.2f \n", oBudget->grndwater);
	//cout << "Groundwater: " << oBudget->grndwater << "\n";
	ofSummary << oBudget->grndwater << "\t";

	/*printf("Gravity Water (m3): %.2f \n", oBudget->gravwater);
	//cout << "Gravity Water: " << oBudget->gravwater << "\t";
	ofSummary << oBudget->gravwater << "\t";*/

	printf("Total Evapotranspiration (m3): %.2f \t", oBudget->evaporation);
	//cout << "Total Evapotranspiration (m3): " << oBudget->evaporation << "\n";
	ofSummary << oBudget->evaporation << "\t";

	 printf("Total Soil Evaporation (m3): %.2f \n", oBudget->evaporationS);
  	//cout << "Total Evapotranspiration (m3): " << oBudget->evaporation << "\n";
  	ofSummary << oBudget->evaporationS << "\t";

  	printf("Total Canopy Evaporation (m3): %.2f \t", oBudget->evaporationI);
  	ofSummary << oBudget->evaporationI << "\t";

  	printf("Total Transpiration (m3): %.2f \n", oBudget->transpiration);
  	ofSummary << oBudget->transpiration << "\t";

	printf("Bedrock Leak (m3): %.2f \n", oBudget->leakage);
	ofSummary << oBudget->leakage << "\t";

	printf("Total OvlndFlow output (m3): %.2f \t", oBudget->ovlndflow);
	//cout << "Total OvlndFlow output (m3): " << oBudget->ovlndflow << "\n";
	ofSummary << oBudget->ovlndflow << "\t";

	printf("Total GWFlow output (m3): %.2f \n", oBudget->gwtrflow);
	ofSummary << oBudget->gwtrflow << "\t";

	// Saturated area (% of the catchment)
	printf("Saturated area fraction: %.2f \n", oBudget->satarea);
	ofSummary << oBudget->satarea << "\t";

	printf("Run-off to channel (m3): %.2f \t", oBudget->srftochn);
	ofSummary << oBudget->srftochn << "\t";

	printf("GW to channel (m3): %.2f \n", oBudget->gwtochn);
	ofSummary << oBudget->gwtochn << "\t";

	printf("Mass Balance Error (%): %e \n", oBudget->MBErr);
	ofSummary << oBudget->MBErr << "\n";


	return EXIT_SUCCESS;
}
