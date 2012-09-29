/*
 * SortedGrid.h
 *
 *  Created on: May 23, 2009
 *      Author: Marco Maneta
 */

#ifndef SORTEDGRID_H_
#define SORTEDGRID_H_

#include "Grid.h"
#include <vector>
//#define nodata (REAL8)-999.000000000000000000000000000000000

struct cell{
  UINT4 row, col;
  int dir;
  REAL8 val;

  //ctor
  cell(){};
  cell (UINT4 Row, UINT4 Col, int Dir) : row(Row), col(Col), dir(Dir){};
  cell (UINT4 Row, UINT4 Col, REAL8 Val) : row(Row), col(Col), val(Val){};
};

struct vectCells{
	UINT4 zone;
	UINT4 numCells;
	vector<cell> cells;
	//ctor
	vectCells(){};
	vectCells(UINT4 Zone) : zone(Zone){};

};


vectCells SortLdd (grid *ldd, vectCells &nonsorted, REAL8 nd);

#endif /* SORTEDGRID_H_ */
