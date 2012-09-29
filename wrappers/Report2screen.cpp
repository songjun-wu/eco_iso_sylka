/*
 * Report2screen.cpp
 *
 *  Created on: Aug 2, 2010
 *      Author: Marco.Maneta
 */

#include "Sativa.h"

int Report2Screen(){

			cout << "Total Precipitation (m3): " << oBudget->precipitation << "\t";
			ofSummary << oBudget->precipitation << "\t";
			cout << "Canopy Storage (m3): " << oBudget->canopy << "\n";
			ofSummary << oBudget->canopy << "\t";
			cout << "SWE (m3): " << oBudget->snowpack << "\t";
			ofSummary << oBudget->snowpack << "\t";
			//cout << "Ponding: " << oBudget->ponding << "\t";
			//ofSummary << oBudget->ponding << "\t";
			cout << "Soil water (m3): " << oBudget->vadose << "\n";
			ofSummary << oBudget->vadose << "\t";
			//cout << "Groundwater: " << oBudget->grndwater << "\n";
			//ofSummary << oBudget->grndwater << "\t";
			//cout << "Gravity Water: " << oBudget->gravwater << "\t";
			//ofSummary << oBudget->gravwater << "\t";
			cout << "Total Evapotranspiration (m3): " << oBudget->evaporation << "\n";
			ofSummary << oBudget->evaporation << "\t";
			cout << "Total OvlndFlow output (m3): " << oBudget->ovlndflow << "\n";
			ofSummary << oBudget->ovlndflow << "\t";
			cout << "Total GWFlow output (m3): " << oBudget->gwtrflow << "\n";
			ofSummary << oBudget->gwtrflow << "\t";
			cout << "Mass Balance Error (%): " << oBudget->MBErr << "\n";
			ofSummary << oBudget->MBErr << "\n";


		return EXIT_SUCCESS;
}
