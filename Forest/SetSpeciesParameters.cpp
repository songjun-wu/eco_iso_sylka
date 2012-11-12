/*
 * SetSpeciesParameters.cpp
 *
 *  Created on: Jun 19, 2010
 *      Author: marco
 */

#include "Forest.h"

int Forest::SetSpeciesParameters(Control &ctrl){


	grid *_tableParams; //table holding parameters of species conforming the forest

	try{
		_tableParams = new grid(ctrl.path_BasinFolder + ctrl.fn_paramtable, "table");
	}catch(...){
		cout << "ERROR: failed to allocate memory for the table of forest parameters" << endl;
		throw;

	}
			if(_Nsp - 1 < _tableParams->r)
				cout << "WARNING: number of species in config.ini less than species in table " << ctrl.fn_paramtable << endl;
			if(_Nsp - 1 > _tableParams->r){
				cout << "ERROR: number of species in config.ini larger than species provided in table " << ctrl.fn_paramtable << endl;
				throw(EXIT_FAILURE);
			}
			if(_tableParams->c !=30){
				cout << "ERROR: number of parameters in " << ctrl.fn_paramtable << " is different from the 30 parameters expected"  << endl;
				throw(EXIT_FAILURE);
			}


			 for(UINT4 i = 0; i < _tableParams->r; i++){
				 _species[i].ID = _tableParams->matrix[i][0];
				 _species[i].GPP2NPP = _tableParams->matrix[i][1];
				 _species[i].gsmax = _tableParams->matrix[i][2];
				 _species[i].alpha = _tableParams->matrix[i][3];
				 _species[i].MaxAge = _tableParams->matrix[i][4];
				 _species[i].TempOpt = _tableParams->matrix[i][5];
				 _species[i].TempMax = _tableParams->matrix[i][6];
				 _species[i].TempMin = _tableParams->matrix[i][7];
				 _species[i].Fprn = _tableParams->matrix[i][8];
				 _species[i].Fpra = _tableParams->matrix[i][9];
				 _species[i].Sprn = _tableParams->matrix[i][10];
				 _species[i].Spra = _tableParams->matrix[i][11];
				 _species[i].gs_light_coeff = _tableParams->matrix[i][12];
				 _species[i].gs_vpd_coeff = _tableParams->matrix[i][13];
				 _species[i].gs_theta_coeff = _tableParams->matrix[i][14];
				 _species[i].WiltingPoint = _tableParams->matrix[i][15];
				 _species[i].SLA = _tableParams->matrix[i][16];
				 _species[i].Crown2Stem = _tableParams->matrix[i][17];
				 _species[i].TreeShapePar = _tableParams->matrix[i][18];
				 _species[i].WoodDensity = _tableParams->matrix[i][19];
				 _species[i].Fhdmax = _tableParams->matrix[i][20];
				 _species[i].Fhdmin = _tableParams->matrix[i][21];
				 _species[i].LeafTurnover = _tableParams->matrix[i][22];
				 _species[i].RootTurnover = _tableParams->matrix[i][23];
				 _species[i].MaxCanStorageParamt = _tableParams->matrix[i][24];
				 _species[i].albedo = _tableParams->matrix[i][25];
				 _species[i].emissivity = _tableParams->matrix[i][26];
				 _species[i].KBeers = _tableParams->matrix[i][27];
				 _species[i].beta = _tableParams->matrix[i][28];
				 _species[i].is_grass = _tableParams->matrix[i][29];

			 }


	if(_tableParams)
		delete _tableParams;

	return EXIT_SUCCESS;
}
