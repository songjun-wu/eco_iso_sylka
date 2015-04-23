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
			printf("Total Evapotranspiration (m3): %.2f \n", oBudget->evaporation);
			//cout << "Total Evapotranspiration (m3): " << oBudget->evaporation << "\n";
			ofSummary << oBudget->evaporation << "\t";
			printf("Total OvlndFlow output (m3): %.2f \n", oBudget->ovlndflow);
			//cout << "Total OvlndFlow output (m3): " << oBudget->ovlndflow << "\n";
			ofSummary << oBudget->ovlndflow << "\t";
			printf("Total GWFlow output (m3): %.2f \n", oBudget->gwtrflow);
			ofSummary << oBudget->gwtrflow << "\t";
			printf("Mass Balance Error (%): %e \n", oBudget->MBErr);
			ofSummary << oBudget->MBErr << "\n";


		return EXIT_SUCCESS;
}
