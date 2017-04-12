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

	printf("Total Precipitation (m3):  %.2f \t", oBudget->precipitation);
		//cout << "Total Precipitation (m3): " << oBudget->precipitation << "\t";
	ofSummary << oBudget->precipitation << "\t";
	printf("Canopy Storage (m3): %.2f \n", oBudget->canopy);
				//cout << "Canopy Storage (m3): " << oBudget->canopy << "\n";
	ofSummary << oBudget->canopy << "\t";
	printf("SWE (m3): %.2f \t", oBudget->snowpack);
				//cout << "SWE (m3): " << oBudget->snowpack << "\t";
	ofSummary << oBudget->snowpack << "\t";
				//cout << "Ponding: " << oBudget->ponding << "\t";
				//ofSummary << oBudget->ponding << "\t";
	printf("Soil water (m3): %.2f \n", oBudget->vadose);
				//cout << "Soil water (m3): " << oBudget->vadose << "\n";
	ofSummary << oBudget->vadose << "\t";
				//cout << "Groundwater: " << oBudget->grndwater << "\n";
				//ofSummary << oBudget->grndwater << "\t";
				//cout << "Gravity Water: " << oBudget->gravwater << "\t";
				//ofSummary << oBudget->gravwater << "\t";
	printf("Total Evapotranspiration (m3): %.2f \t", oBudget->evaporation);
				//cout << "Total Evapotranspiration (m3): " << oBudget->evaporation << "\n";
	ofSummary << oBudget->evaporation << "\t";
	printf("Bedrock Leak (m3): %.2f \n", oBudget->leakage);
				//cout << "Bedrock Leak (m3): " << oBudget->leakage << "\n";
	ofSummary << oBudget->leakage << "\t";
	printf("Total OvlndFlow output (m3): %.2f \n", oBudget->ovlndflow);
				//cout << "Total OvlndFlow output (m3): " << oBudget->ovlndflow << "\n";
	ofSummary << oBudget->ovlndflow << "\t";
	printf("Total GWFlow output (m3): %.2f \n", oBudget->gwtrflow);
	ofSummary << oBudget->gwtrflow << "\t";

	// Saturated area (% of the catchment)
	printf("Saturated area fraction: %.2f \t", oBudget->satarea);
	ofSummary << oBudget->satarea << "\t";

	printf("Mass Balance Error (%): %e \n", oBudget->MBErr);
	ofSummary << oBudget->MBErr << "\n";


	return EXIT_SUCCESS;
}
