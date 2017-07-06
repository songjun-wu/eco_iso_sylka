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
 * Splash.cpp
 *
 *  Created on: Sep 2, 2010
 *      Author: Marco.Maneta
 */

#include "Sativa.h"
#include <string.h>

void message(){
	cout << "USAGE: ech2o <config.ini>" << endl;
	cout << "\twhere config.ini is a valid ech2o configuration file" << endl;
	cout << "OR: ech2o -g <output_file>" << endl;
	cout << "\tto write a configuration file template." << endl;
}

void Splash(int argc, char* argv[]){

cout << " ______________________________________________________________________________|                                                                              ||                                                                              ||    888888888888888  888888888888888   888      888        888888888888888    ||    888888888888888  888888888888888   888      888        888888888888888    ||    8888             888               888      888        888         888    ||    8888             888               888      888        888         888    ||    88888888888      888               888888888888        888         888    ||    88888888888      888               888888888888        888         888    ||    8888             888               888      888 888888 888         888    ||    8888             888               888      888    888 888         888    ||    888888888888888  888888888888888   888      888    888 888888888888888    ||    888888888888888  888888888888888   888      888  888   888888888888888    ||                                                   8888888                    ||                                                                              ||    ECHOHYDROLOGICAL MODEL (ECH2O)                                            ||    Watershed Hydrology Lab - University of Montana                           ||    " << VERSION << "                                                                 ||______________________________________________________________________________|" <<endl;


     if (argc==3 && strcmp(argv[1],"-g")==0 ){
    	GenerateConfigTemplate(argv[2]);
		cout << "Writing configuration file template in" << argv[2] << endl;
		exit(EXIT_SUCCESS);
     }

    if (argc!=2 || strcmp(argv[1],"-g") == 0){
		message();
		exit(EXIT_SUCCESS);
	}




}
