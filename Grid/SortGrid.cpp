/*
 * SortGrid.cpp
 *
 *  Created on: Oct 17, 2009
 *      Author: Marco Maneta
 */

#include "Atmosphere.h"

vectCells Atmosphere::SortGrid(int zoneId){

    REAL4 value = 0;

    UINT4 r,c;
    UINT4 nr = _zones->r;
    UINT4 nc = _zones->c;

    vectCells NotSortedArray; //array to hold the non-mv cells as read left to right and top to bottom

/*
    for(r=1; r < nr-1; r++)
    {
     for(c=1; c < nc-1; c++)
     {
      value = (int)_zones->matrix[r][c];
      if (value != _zones->nodata)
          NotSortedArray.cells.push_back(cell(r, c, (int)value));
     }
    }
*/
    for(r=1; r < nr-1; r++)
    {
     for(c=1; c < nc-1; c++)
     {
    	value = (int)_zones->matrix[r][c];
    	 if (value == zoneId)
          NotSortedArray.cells.push_back(cell(r, c, (int)value));
     }
    }

   return NotSortedArray;

}
