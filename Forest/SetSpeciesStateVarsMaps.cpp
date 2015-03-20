/*
 * SetSpeciesStateVarsMaps.cpp
 *
 *  Created on: Sep 20, 2011
 *      Author: Marco.Maneta
 */

#include "Forest.h"

void Forest::SetStateVarsMaps(Control &ctrl){

	UINT4 r,c;
	stringstream fn;


 //for PCRASTER maps

	try{
	if (!ctrl.MapType.compare("csf")) {
			for (unsigned int j = 0; j < _Nsp - 1; j++) { //loads all species expect
				//loads the maps to their respective grids
				fn.str(""); fn << "p[" << j << "].map";
				if(_species[j]._fraction->PCRMap2grid(ctrl.path_BasinFolder + fn.str())==-1)
					throw fn.str();
				fn.str(""); fn << "lai[" << j << "].map";
				if(_species[j]._LAI->PCRMap2grid(ctrl.path_BasinFolder + fn.str())==-1)
					throw fn.str();
				*_species[j]._grassLAI_g = *_species[j]._LAI; //needed to initialize lai for grasses
				fn.str(""); fn << "age[" << j << "].map";
				if(_species[j]._AGE->PCRMap2grid(ctrl.path_BasinFolder + fn.str())==-1)
					throw fn.str();
				fn.str(""); fn << "bas[" << j << "].map";
				if(_species[j]._BasalArea->PCRMap2grid(ctrl.path_BasinFolder + fn.str())==-1)
					throw fn.str();
				fn.str(""); fn << "hgt[" << j << "].map";
				if(_species[j]._Height->PCRMap2grid(ctrl.path_BasinFolder + fn.str())==-1)
					throw fn.str();
				fn.str(""); fn << "ntr[" << j << "].map";
				if(_species[j]._StemDensity->PCRMap2grid(ctrl.path_BasinFolder + fn.str())==-1)
					throw fn.str();
				fn.str(""); fn << "root[" << j << "].map";
				if(_species[j]._RootMass->PCRMap2grid(ctrl.path_BasinFolder + fn.str())==-1)
					throw fn.str();

			}
		}
		else{

			cerr << "Reading forest state vars from maps not implemented yet for ascii maps. Pleas, use csf (PCRASTER) maps" << endl;
			exit(EXIT_FAILURE);
		}
	}catch(string &e){
		cerr << "Initial forest map " << e << " not found" << endl;
				exit(EXIT_FAILURE);
	}


		//calculate proportion of of bare soil

			   for (UINT4 k = 0; k < _vSortedGrid.cells.size() ; k++)
			   {
			   	    	r = _vSortedGrid.cells[k].row;
			   	    	c = _vSortedGrid.cells[k].col;
			   	    	_species[_Nsp-1]._fraction->matrix[r][c] = 1;

			   	 for(UINT4 j = 0; j < _Nsp - 1; j++)
			       		_species[_Nsp-1]._fraction->matrix[r][c] -= _species[j]._fraction->matrix[r][c];

			   	 if(_species[_Nsp-1]._fraction->matrix[r][c] < 0){
			   		 cerr << "Proportion of species is larger than 1 in cell row: " << r << " col: " << c << endl;
			   		 exit(EXIT_FAILURE);
			   	 }

			   }



}
