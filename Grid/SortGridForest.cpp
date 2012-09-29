/*
 * SortGridForest.cpp
 *
 *  Created on: May 20, 2010
 *      Author: Marco.Maneta
 */

#include "Forest.h"

vectCells Forest::SortGrid(){

    REAL4 value = 0;

    UINT4 r,c;
    UINT4 nr = _patches->r;
    UINT4 nc = _patches->c;

    vectCells NotSortedArray; //array to hold the non-mv cells as read left to right and top to bottom

    for(r=1; r < nr-1; r++)
    {
     for(c=1; c < nc-1; c++)
     {
      value = (int)_patches->matrix[r][c];
      if (value != _patches->nodata)
          NotSortedArray.cells.push_back(cell(r, c, (int)value));
     }
    }

   return NotSortedArray;

}
