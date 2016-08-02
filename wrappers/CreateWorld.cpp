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

try{
		ofSummary.open("BasinSummary.txt");
		if(!ofSummary)
			throw std::ios::failure("Error opening Summary.txt buffer\n");

}catch(const std::exception &e){
	cout << e.what() << endl;
	throw;
}
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
