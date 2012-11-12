/*
 * SetGroveProportions.cpp
 *
 *  Created on: Jun 17, 2010
 *      Author: marco
 */

#include "Forest.h"

int Forest::SetStateVarsTabs(Control &ctrl){

		int r, c, id = -1;
		REAL8 frac = 0;
		REAL8 stemdens = 0;
		REAL8 lai = 0;
		REAL8 age = 0;
		REAL8 basal = 0;
		REAL8 height = 0;
		REAL8 roots = 0;


		grid *tableFrac = new grid(ctrl.path_BasinFolder + ctrl.fn_proptable, "table");
		grid *tableStemDens = new grid(ctrl.path_BasinFolder + ctrl.fn_StemDenstable, "table");
		grid *tableLAI = new grid(ctrl.path_BasinFolder + ctrl.fn_LAItable, "table");
		grid *tableAGE = new grid(ctrl.path_BasinFolder + ctrl.fn_AGEtable, "table");
		grid *tableBasalArea = new grid(ctrl.path_BasinFolder + ctrl.fn_BasalAreatable, "table");
		grid *tableHeight = new grid(ctrl.path_BasinFolder + ctrl.fn_Heighttable, "table");
		grid *tableRootDens = new grid(ctrl.path_BasinFolder + ctrl.fn_RootMasstable, "table");

		if(_Nsp < tableFrac->c ){ //works because the table has one extra column with species ID and NSP is +1 because of bare soil
			cout << "ERROR: number of species in config.ini less than species in table " << ctrl.fn_proptable << endl;
			throw(EXIT_FAILURE);
		}
		if(_Nsp > tableFrac->c){
			cout << "ERROR: number of species in config.ini larger than species provided in table " << ctrl.fn_proptable << endl;
			throw(EXIT_FAILURE);
		}


	   for(UINT4 i = 0; i < tableFrac->r; i++)
	   {
		for(UINT4 j = 0; j < tableFrac->c; j++)
		{
		    if (j == 0)
		    {
				id = (int)tableFrac->matrix[i][j];
				continue;
		    }
		    else{
		    	frac = tableFrac->matrix[i][j];
				lai =  tableLAI->matrix[i][j];
				basal = tableBasalArea->matrix[i][j];
				age = tableAGE->matrix[i][j];
				height = tableHeight->matrix[i][j];
				stemdens = tableStemDens->matrix[i][j];
				roots = tableRootDens->matrix[i][j];
		    }
		 for (unsigned int k = 0; k < _vSortedGrid.cells.size() ; k++)
	     {
	    	r = _vSortedGrid.cells[k].row;
	    	c = _vSortedGrid.cells[k].col;

	    	if(_patches->matrix[r][c] == id){
	    		_species[j-1]._fraction->matrix[r][c] = frac;
				if(_species[j-1].is_grass){ //needed to initialize green and total lai of grass
					_species[j-1]._grassLAI_g->matrix[r][c] = lai;
					_species[j-1]._LAI->matrix[r][c] = lai;
				}
				else
					_species[j-1]._LAI->matrix[r][c] = lai;
				_species[j-1]._AGE->matrix[r][c] = age;
				_species[j-1]._BasalArea->matrix[r][c] = basal;
				_species[j-1]._Height->matrix[r][c] = height;
				_species[j-1]._StemDensity->matrix[r][c] = stemdens;
				_species[j-1]._RootMass->matrix[r][c] = roots;
	    	}
	     }
		}
	   }

	   //calcualte percentage of bare soil

	   for (UINT4 k = 0; k < _vSortedGrid.cells.size() ; k++)
	   {
	   	    	r = _vSortedGrid.cells[k].row;
	   	    	c = _vSortedGrid.cells[k].col;
	   	    	_species[_Nsp-1]._fraction->matrix[r][c] = 1;

	   	 for(UINT4 j = 0; j < tableFrac->c - 1; j++)
	       		_species[_Nsp-1]._fraction->matrix[r][c] -= _species[j]._fraction->matrix[r][c];

	   }
	        if (tableFrac)
	        	delete tableFrac;
	        if (tableStemDens)
	        	delete tableStemDens;
	        if (tableLAI)
	        	delete tableLAI;
	        if (tableAGE)
	        	delete tableAGE;
	        if (tableBasalArea)
	        	delete tableBasalArea;
	        if (tableHeight)
	        	delete tableHeight;
	        if (tableRootDens)
	        	delete tableRootDens;

	    return EXIT_SUCCESS;
}
