/*
 * UpdateClimateMap.cpp
 *
 *  Created on: Oct 17, 2009
 *      Author: Marco Maneta
 */

#include "Atmosphere.h"

int Atmosphere::UpdateClimateMap(ifstream &ifHandle, grid &ClimMap){

		float *data;
		int data_written = 0;

		data = new float[_NZns]; //creates the array to hold the data

		ifHandle.read((char *)data, sizeof(float)*_NZns); //reads data for all zones

		int r, c;

	//	for (unsigned int a = 0; a < _nzones; a++ ) //loops only over the number of zones in the climate zone map, not in the climate dataset
			for (unsigned int i = 0; i < _vSortedGrid.size() ; i++)
				//if(_vSortedGrid[i].zone == _zoneId[a])
				//{
					for (unsigned int j = 0; j < _vSortedGrid[i].cells.size() ; j++)
					{
						r = _vSortedGrid[i].cells[j].row;
						c = _vSortedGrid[i].cells[j].col;

							ClimMap.matrix[r][c] = data[_zoneId[i]];
							data_written++;
					}
		//		}


		delete[] data;

		return data_written;

}
