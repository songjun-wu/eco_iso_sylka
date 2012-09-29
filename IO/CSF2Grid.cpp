/*
 * CSF2Grid.cpp
 *
 *  Created on: Oct 13, 2009
 *      Author: Marco Maneta
 */

#include <fstream>
#include <cmath>
#include "Grid.h"

int CSF2Grid(std::string fname, grid *pnt){

		UINT4 cells = 0; REAL8 data;
		MAP *pcrMap = Mopen(fname.c_str(), M_READ);

		if (Merrno != 0)
				 {cerr << MstrError() << ": " << fname << endl; exit(-1);}

		    RuseAs(pcrMap, CR_REAL8);

		    pnt->c = RgetNrCols(pcrMap);
		    pnt->r = RgetNrRows(pcrMap);
		    pnt->dx = RgetCellSize(pcrMap);
		    pnt->nodata = -9999;
		    pnt->north = RgetYUL(pcrMap);
		    pnt->west = RgetXUL(pcrMap);
		    pnt->east = pnt->west + (pnt->dx * pnt->c);

		    if (MgetProjection(pcrMap) == PT_YINCT2B)
		    	pnt->south = pnt->north + (pnt->dx * pnt->r);
		    if (MgetProjection(pcrMap) == PT_YDECT2B)
		    	pnt->south = pnt->north - (pnt->dx * pnt->r);

		    //initializes the grid matrix
		    	  try{
		    	      pnt->matrix = new REAL8*[pnt->r];
		    	      for (UINT4 i=0; i < pnt->r; i++)
		    	    	  pnt->matrix[i] = new REAL8[pnt->c];
		    	      }catch(std::bad_alloc){cerr << "unable to allocate memory...";
		    	      cin.get(); exit(-1);}

		    for (UINT4 i=0; i<pnt->r; i++)
		    {
		        for (UINT4 j=0; j<pnt->c; j++)
		        {
		           cells +=RgetCell(pcrMap, i, j, &data);
		           if(IsMV(pcrMap, &data)) data = pnt->nodata;
		           pnt->matrix[i][j] = data;
		        }
		    }
		 Mclose(pcrMap);

		    if(cells!=(pnt->r*pnt->c)) return -1;
		    return cells;
}
