/*
 * Atmosphere.h
 *
 *  Created on: Oct 14, 2009
 *      Author: Marco Maneta
 */

#ifndef ATMOSPHERE_H_
#define ATMOSPHERE_H_

#include <fstream>
#include "Grid.h"
#include "InitConf.h"
#include "SortGrid.h"
//#include "exceptions_echo.h"

using namespace std;

class Atmosphere{

		UINT4 _NRows;
		UINT4 _NCols;
		REAL8 _dx;
		grid *_zones; //map with the zone extents and identifiers
		UINT4 _nzones; // number of zones in map
		UINT4 _NZns; //number of zones in binary data time series
		UINT4 *_zoneId; // array with zone identifiers from the climate dataset
		vector<vectCells> _vSortedGrid;
		grid *_isohyet; //map with rainfall multipliers to spatially distribute precipitation
		UINT4 _vSsortedGridTotalCellNumber;

		grid *_rain_snow_temp; //scalar with air temperature threshold for rain-snow partition

		grid *_Ldown; //longwave downward radiation Wm-2
		grid *_Sdown; //shortwave downward radiation Wm-2
		grid *_Tp; //Average air temperature C
		grid *_MaxTp; //Maximum air temperature C
		grid *_MinTp; //Minimum air temperature C
		grid *_Precip; // Precipitation intensity ms-1
		grid *_Rel_humid; //relative humidity of air [0-1]
		grid *_Wind_speed; //windspeed in ms-1

		void CountNumZones();
		vectCells SortGrid(int zoneId);
		UINT4 InitiateClimateMap(ifstream & ifHandle, grid & ClimMap);
		int UpdateClimateMap(ifstream & ifHandle, grid & ClimMap);// internal function that updates a climate map
		int AdjustPrecip();

		//climate data file handles
		ifstream ifLdown;
		ifstream ifSdown;
		ifstream ifTp;
		ifstream ifMaxTp;
		ifstream ifMinTp;
		ifstream ifPrecip;
		ifstream ifRelHumid;
		ifstream ifWindSpeed;



public:

	Atmosphere();
    Atmosphere(Control & ctrl);
    ~Atmosphere();


    int AdvanceClimateMaps(); //external interface that updates all climate maps by calling UpdateClimateMap



    /*Getters and setters*/
    //get methods (inline)

	REAL8 getCellSize() const {
			return _dx;
	}

	const vector<vectCells> &getSortedGrid() const {
		return _vSortedGrid;
	}

    grid *getRainSnowTempThreshold() const{
    	return _rain_snow_temp;
    }
	grid *getIncomingLongWave() const
    {
        return _Ldown;
    }

    grid *getIncomingShortWave() const
    {
        return _Sdown;
    }

    grid *getTemperature() const
    {
        return _Tp;
    }
    grid *getMaxTemperature() const
	{
		return _MaxTp;
	}
    grid *getMinTemperature() const
	{
		return _MinTp;
	}
    grid *getPrecipitation() const
    {
        return _Precip;
    }

    grid *getRelativeHumidty() const
    {
        return _Rel_humid;
    }

    grid *getWindSpeed() const
    {
            return _Wind_speed;
    }

    //setter
    void setPrecip(UINT4 row, UINT4 col, REAL8 value)
    {
           this->_Precip->matrix[row][col] = value;
    }
};
#endif /* ATMOSPHERE_H_ */
