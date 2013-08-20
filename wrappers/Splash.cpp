/*
 * Splash.cpp
 *
 *  Created on: Sep 2, 2010
 *      Author: Marco.Maneta
 */

#include "Sativa.h"

void Splash(int argc, char* argv[]){

cout << " ______________________________________________________________________________|                                                                              ||                                                                              ||    888888888888888  888888888888888   888      888        888888888888888    ||    888888888888888  888888888888888   888      888        888888888888888    ||    8888             888               888      888        888         888    ||    8888             888               888      888        888         888    ||    88888888888      888               888888888888        888         888    ||    88888888888      888               888888888888        888         888    ||    8888             888               888      888 888888 888         888    ||    8888             888               888      888    888 888         888    ||    888888888888888  888888888888888   888      888    888 888888888888888    ||    888888888888888  888888888888888   888      888  888   888888888888888    ||                                                   8888888                    ||                                                                              ||    ECHOHYDROLOGICAL MODEL (ECH2O)                                            ||    Watershed Hydrology Lab - University of Montana                           ||    V 4.3.1beta2                                                                 ||______________________________________________________________________________|" <<endl;


	if (argc!=2){
		cout << "USAGE: ech20 config.ini" << endl;
		cout << "\twhere config.ini is a valid ech20 configuration file" << endl;
		exit(EXIT_SUCCESS);
	}


}
