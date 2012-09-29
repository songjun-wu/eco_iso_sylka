/*
 * CrunchWorld.cpp
 *
 *  Created on: Jul 30, 2010
 *      Author: Marco.Maneta
 */

#include "Sativa.h"

int CrunchWorld(){

	if(oControl)
		delete oControl;
	if(oBasin)
		delete oBasin;
	if(oAtmosphere)
		delete oAtmosphere;
	if(oBudget)
		delete oBudget;
	if(oReport)
		delete oReport;

	if(ofSummary.is_open())
		ofSummary.close();

		return EXIT_SUCCESS;
}
