/*
 * WritePCRMap.cpp
 *
 *  Created on: Oct 13, 2009
 *      Author: Marco Maneta
 */

#include <fstream>
#include "Grid.h"

int grid::grid2PCRMap(std::string fname,
                        CSF_CR cellRepr,
                        CSF_VS dataType)
{
	MAP *out; REAL4 data = 0; UINT4 nrCells = 0; CSF_PT proj;

	if (north > south)
		proj = PT_YDECT2B;
	else
		proj = PT_YINCT2B;

	out = Rcreate(fname.c_str(), r, c, cellRepr, dataType, proj, west, north,0, dx);

	 if (Merrno != 0)
		 {cout << MstrError(); return -1;}
	RuseAs(out, CR_REAL4);

	for(unsigned i = 0; i < r; i++)
	{
	    for(unsigned j = 0; j < c; j++)
	    {
	    data = (REAL4)matrix[i][j];
	    if (data == nodata) SET_MV_REAL4(&data);
	     nrCells += RputCell(out, i, j, &data);
	    }
	}
	RuseAs(out, cellRepr);
	Mclose(out);
	return nrCells;
}
