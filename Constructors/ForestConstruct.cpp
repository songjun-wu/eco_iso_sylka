/*
 * ForestConstruct.cpp
 *
 *  Created on: May 5, 2010
 *      Author: Marco.Maneta
 */

#include "Forest.h"

Forest::Forest(Control &ctrl)
{
	try{

	//Read the base map and writes the dimensions of the grid
		_patches = new grid(ctrl.path_BasinFolder + ctrl.fn_patches, ctrl.MapType);
		_NRows = _patches->r;
		_NCols = _patches->c;
		_dx = _patches->dx;
		_Nsp = ctrl.NumSpecs + 1; //num of species plus bare soil

		/*sorts the basin with data cells according
		 * to the ldd after _DEM and _ldd have been created*/
		_vSortedGrid = SortGrid();

		_species = new Grove[_Nsp]; //creates Grove array with default constructor

		for (UINT4 i = 0; i < _Nsp; i++) //initializes the grids in each Grove object
			_species[i].CreateGrids(_patches);

		SetSpeciesParameters(ctrl);

		if(!ctrl.ForestStateVarsInputType.compare("tables"))
			SetStateVarsTabs(ctrl);
		else if(!ctrl.ForestStateVarsInputType.compare("maps"))
			SetStateVarsMaps(ctrl);
		else{
			cerr << "Illegal type " << ctrl.ForestStateVarsInputType << endl;
			throw;
		}

		//SetSpeciesParameters(ctrl);

        checkForestDatabase(); //check the sanity of the database


	}catch (std::bad_alloc &)
	  { cerr << "Cleaning up the forest..." << "\n";
		if(_patches)
			delete _patches;
		if(_species)
			delete[] _species;

	  throw;
	  }

}
