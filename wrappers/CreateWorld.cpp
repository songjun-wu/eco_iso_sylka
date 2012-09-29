/*
 * CreateWorld.cpp
 *
 *  Created on: Jul 30, 2010
 *      Author: Marco.Maneta
 */

#include "Sativa.h"

int CreateWorld(char* argv[]){

		oControl = new Control;
		cout << "Control created ok... " << "\n";
		oControl->ReadConfigFile(argv[1]);
		cout << "Config.ini read ok... " << "\n";

		oBasin = new Basin(*oControl);
		cout << "Basin created ok... " << "\n";

		oAtmosphere = new Atmosphere(*oControl);
		cout << "Atmosphere created ok... " << "\n";

		oBudget = new Budget(oBasin, oControl);
		cout << "Budget created ok... " << "\n";



		oReport = new Report(*oControl);
		cout << "Report created ok... " << "\n";


		ofSummary.open("BasinSummary.txt");

		ofSummary << "Precipitation\t";
		ofSummary << "Canopy Storage\t";
		ofSummary << "SWE\t";
		ofSummary << "Soil water < fc\t";
		ofSummary << "Evapotranspiration\t";
		ofSummary << "Overland flow\t";
		ofSummary << "Groundwater flow\t";
		ofSummary << "Mass Balance Error\n";


		return EXIT_SUCCESS;
}
