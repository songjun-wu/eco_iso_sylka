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
#include <time.h>
#include "Sativa.h"

clock_t start;
int main(int argc, char* argv[])
{
try{
	start = clock();
	Splash(argc,  argv);
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

    int tot_sec = ((float)(clock() - start))/CLOCKS_PER_SEC;
    printf("\nTotal run time elapsed (seconds): %i", tot_sec);

    int dd = tot_sec/86400;
    tot_sec = tot_sec%86400;
    int hh = tot_sec/3600;
    tot_sec = tot_sec%3600;
    int mm = tot_sec/60;
    tot_sec = tot_sec%60;
    int ss = tot_sec;
    printf("\nTotal run time elapsed: days: %i hh:mm:ss: %i:%i:%i  ", dd, hh, mm, ss);

	return 0;

}
