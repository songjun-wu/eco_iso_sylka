/*
 * PCRIO.cpp
 *
 *  Created on: Oct 9, 2009
 *      Author: Marco Maneta
 *
 *      Functions implemented in this file:
 *      PCRMap2grid
 *      grid2PCRMap
 *
 *      These are routines to read and write pcraster maps.
 *      Note that they are not constructors, the grid object must exist and have the same
 *      number of columns and rows as the pcraster map to be imported.
 */

#include <fstream>
#include "Grid.h"


int grid::PCRMap2grid(std::string fname)
{
	UINT4 cells = 0; REAL8 data;
	MAP *pcrMap = Mopen(fname.c_str(), M_READ);

	if (Merrno != 0)
			 {cout << MstrError(); return -1;}

	    RuseAs(pcrMap, CR_REAL8);

	if((RgetNrCols(pcrMap)!= c)||(RgetNrRows(pcrMap)!= r))
	{
		cout << "PCRaster map " << fname << " has different dimensions than the grid";
		exit(-1);
	}

	    dx = RgetCellSize(pcrMap);
	    north = RgetYUL(pcrMap);
	    west = RgetXUL(pcrMap);
	    east = west + (dx * c);

	    if (MgetProjection(pcrMap) == PT_YINCT2B)
	    	south = north + (dx * r);
	    if (MgetProjection(pcrMap) == PT_YDECT2B)
	    	south = north - (dx * r);

	    for (UINT4 i=0; i<r; i++)
	    {
	        for (UINT4 j=0; j<c; j++)
	        {
	           cells +=RgetCell(pcrMap, i, j, &data);
	           if(IsMV(pcrMap, &data)) data = nodata;
	           matrix[i][j] = data;
	        }
	    }
	 Mclose(pcrMap);

	    if(cells!=(r*c)) return -1;
	    return cells;
}


