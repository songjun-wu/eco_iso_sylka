/*
 * Splash.cpp
 *
 *  Created on: Sep 2, 2010
 *      Author: Marco.Maneta
 */

#include "Sativa.h"
#include <string.h>

void message(){
	cout << "USAGE: ech2o config.ini" << endl;
	cout << "\twhere config.ini is a valid ech2o configuration file" << endl;
	cout << "OR: ech2o -g out_tpl_config.ini" << endl;
	cout << "\tto write a configuration file template with name out_tpl_config.ini" << endl;
}

void Splash(int argc, char* argv[]){

cout << " ______________________________________________________________________________|                                                                              ||                                                                              ||    888888888888888  888888888888888   888      888        888888888888888    ||    888888888888888  888888888888888   888      888        888888888888888    ||    8888             888               888      888        888         888    ||    8888             888               888      888        888         888    ||    88888888888      888               888888888888        888         888    ||    88888888888      888               888888888888        888         888    ||    8888             888               888      888 888888 888         888    ||    8888             888               888      888    888 888         888    ||    888888888888888  888888888888888   888      888    888 888888888888888    ||    888888888888888  888888888888888   888      888  888   888888888888888    ||                                                   8888888                    ||                                                                              ||    ECHOHYDROLOGICAL MODEL (ECH2O)                                            ||    Watershed Hydrology Lab - University of Montana                           ||    " << VERSION << "                                                                 ||______________________________________________________________________________|" <<endl;


     if (argc==3 && strcmp(argv[1],"-g")==0 ){
    	GenerateConfigTemplate(argv[2]);
		cout << "Writing configuration file template in" << argv[2] << endl;
		exit(EXIT_SUCCESS);
     }

    if (argc!=2){
		message();
		exit(EXIT_SUCCESS);
	}




}
