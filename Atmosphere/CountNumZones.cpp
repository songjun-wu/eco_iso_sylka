/*
 * CountNumZones.cpp
 *
 *  Created on: Oct 15, 2009
 *      Author: Marco Maneta
 */

#include "Atmosphere.h"

void Atmosphere::CountNumZones(){

	unsigned int r,c,i;
	bool found = false;
	_nzones = 0;
	int *zone = new int[_NRows*_NCols]; //makes space for potentially as many zones as number of cells in the map

	for (unsigned int i = 0; i<_NRows*_NCols; i++) //initialization to prevent valgrind form complaining on uninitialized variables
		zone[i] = 0;

	// check nr of zones
	zone[0] =(int)_zones->nodata;
	    for ( r = 0; r < _NRows; r++)
	      for ( c = 0; c < _NCols; c++)
	        if (_zones->matrix[r][c] != _zones->nodata){
	          found = false;
	          for( i = 0; i <= _nzones; i++)
	             if (zone[i] == _zones->matrix[r][c]) found = true;

	          if(!found && i < _NRows*_NCols){
	              zone[_nzones] = (int)_zones->matrix[r][c];
	              _vSortedGrid.push_back(vectCells(zone[_nzones]));
	              _nzones++;
	          }
	        }

		_zoneId = new UINT4[_nzones]; //will be destroyed in Atmosphere destructor

	//	for(unsigned int i = 0; i < _nzones; i++) //loop to add the zone ids to _zoneId
	//		_zoneId[i] = zone[i];


	    delete[] zone;
}
