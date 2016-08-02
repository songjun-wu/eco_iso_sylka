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

time_t start, end;
int main(int argc, char* argv[])
{
# ifdef _OPENMP
 printf("Compiled by an OpenMP-compliant implementation.\n");
# endif
try{
	time(&start);
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
    time(&end);
    int tot_sec = difftime(end, start);


    int dd = tot_sec/86400;
    tot_sec = tot_sec%86400;
    int hh = tot_sec/3600;
    tot_sec = tot_sec%3600;
    int mm = tot_sec/60;
    tot_sec = tot_sec%60;
    int ss = tot_sec;
    printf("\nTotal run time elapsed:  %i (days) %02i:%02i:%02i (hh:mm:ss)", dd, hh, mm, ss);

	return 0;

}
