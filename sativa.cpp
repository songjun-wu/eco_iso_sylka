/*
 * sativa.cpp
 *
 *  Created on: Feb 19, 2010
 *      Author: Marco Maneta
 */

/*
 * main.cpp
 *
 *  Created on: May 21, 2009
 *      Author: Marco Maneta
 */

#include "Sativa.h"

int main(int argc, char* argv[])
{
try{
	Splash(argc, argv);
	CreateWorld(argv);

	while (oControl->current_t_step <= oControl->endtime)
	{

		//cout << "\nstart time step " << oControl->current_ts_count << "\n";


		SolveTimeStep();

		CalculateBudgets();

		Report2Screen();

		Report2Maps();

		cout << "\nEnd time step " << oControl->current_ts_count;
		cout << "\nSimulation time " << oControl->current_t_step << " seconds (" << oControl->current_t_step / 86400 << " days)\n\n";

		oControl->AdvanceTimeStep();
		oAtmosphere->AdvanceClimateMaps();



	}

}
catch(...){
	cerr << "Something bad happened that I cannot really handle until I have a better exception management" << endl;
	CrunchWorld();
	return 0;
}

	  CrunchWorld();


	return 0;

}
