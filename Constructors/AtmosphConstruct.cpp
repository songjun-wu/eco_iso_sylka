/*
 * AtmosphConstruct.cpp
 *
 *  Created on: Oct 14, 2009
 *      Author: Marco Maneta
 */

#include <errno.h>
#include "Atmosphere.h"

Atmosphere::Atmosphere(Control &ctrl){

	try{

		//Read the zones map and writes the dimensions of the grid
			_zones = new grid(ctrl.path_ClimMapsFolder + ctrl.fn_climzones, ctrl.MapType);
			_NRows = _zones->r;
			_NCols = _zones->c;
			_dx = _zones->dx;
			CountNumZones(); //Reads the _zones grid and fills variable _nzones with the number of zones. This is the number of zones in the zone map
			_NZns = 0; //set to zero the initial zones in the climate time series files. This is the number of zones in the climate time series


			_vSsortedGridTotalCellNumber = 0;
			for(unsigned int i = 0; i < _nzones; i++){
				_vSortedGrid[i].cells = SortGrid(_vSortedGrid[i].zone).cells; // fills the vectCells with actual domain cells (no nodata)
				_vSsortedGridTotalCellNumber += _vSortedGrid[i].cells.size();
			}






			/*constructs the object using the basemap so
			attributes (lat, long, nodata...) are copied*/
			_Ldown = new grid(*_zones);
			_Sdown = new grid (*_zones);
			_Tp = new grid (*_zones);
			_MaxTp = new grid (*_zones);
			_MinTp = new grid (*_zones);
			_Precip = new grid (*_zones);
			_Rel_humid = new grid (*_zones);
			_Wind_speed = new grid (*_zones);

			*_Ldown = *_zones;
			*_Sdown = *_zones;
			*_Tp = *_zones;
			*_MaxTp = *_zones;
			*_MinTp = *_zones;
			*_Precip = *_zones;
			*_Rel_humid = *_zones;
			*_Wind_speed = *_zones;

			_isohyet = new grid(ctrl.path_ClimMapsFolder + ctrl.fn_isohyet, ctrl.MapType);

			/*open climate data files*/


			try {
				ifLdown.open((ctrl.path_ClimMapsFolder + ctrl.fn_Ldown).c_str(), ios::binary);
					if(errno!=0) throw ctrl.fn_Ldown;  //echo_filenotfound_exception(ctrl.fn_Ldown.c_str(), "Dang! File not found: ");
				ifSdown.open((ctrl.path_ClimMapsFolder + ctrl.fn_Sdown).c_str(), ios::binary);
					if(errno!=0) throw ctrl.fn_Sdown;//echo_filenotfound_exception(ctrl.fn_Sdown.c_str(), "Dang! File not found: ");
				ifTp.open((ctrl.path_ClimMapsFolder + ctrl.fn_temp).c_str(), ios::binary);
					if(errno!=0) throw ctrl.fn_temp;
				ifMaxTp.open((ctrl.path_ClimMapsFolder + ctrl.fn_maxTemp).c_str(), ios::binary);
					if(errno!=0) throw ctrl.fn_maxTemp;
				ifMinTp.open((ctrl.path_ClimMapsFolder + ctrl.fn_minTemp).c_str(), ios::binary);
					if(errno!=0) throw ctrl.fn_minTemp;
				ifPrecip.open((ctrl.path_ClimMapsFolder + ctrl.fn_precip).c_str(), ios::binary);
					if(errno!=0) throw ctrl.fn_precip;
				ifRelHumid.open((ctrl.path_ClimMapsFolder + ctrl.fn_rel_humid).c_str(), ios::binary);
					if(errno!=0) throw ctrl.fn_rel_humid;
				ifWindSpeed.open((ctrl.path_ClimMapsFolder + ctrl.fn_wind_speed).c_str(), ios::binary);
					if(errno!=0) throw ctrl.fn_wind_speed;
			}
			catch (string e){
							cout << "Dang!!: cannot open " << e << "  file " << endl;
							throw;
			}



			//Initiate Climate map returns the number of data written
			try{
			if(InitiateClimateMap(ifLdown, *_Ldown) != _vSsortedGridTotalCellNumber)
				throw string("incoming longwave");
			if(InitiateClimateMap(ifSdown, *_Sdown)!= _vSsortedGridTotalCellNumber)
				throw string("short wave");
			if(InitiateClimateMap(ifTp, *_Tp)!= _vSsortedGridTotalCellNumber)
				throw string("average air temperature");
			if(InitiateClimateMap(ifMaxTp, *_MaxTp)!= _vSsortedGridTotalCellNumber)
				throw string("maximum air temperature");
			if(InitiateClimateMap(ifMinTp, *_MinTp)!= _vSsortedGridTotalCellNumber)
				throw string("minimum air temperature");
			if(InitiateClimateMap(ifPrecip, *_Precip)!= _vSsortedGridTotalCellNumber)
				throw string("precipitation");
			AdjustPrecip();// adjust precipitation with the isohyet map
			if(InitiateClimateMap(ifRelHumid, *_Rel_humid)!= _vSsortedGridTotalCellNumber)
				throw string("relative humidity");
			if(InitiateClimateMap(ifWindSpeed, *_Wind_speed)!= _vSsortedGridTotalCellNumber)
				throw string("windspeed");
			}catch (string e){
				cout << "Error: some sections of the domain was not filled with " << e << " data." << endl;
				cout << "Please verify that all the climate zones in the map are presented in the binary climate data file " << endl;
				cout << "and that the n climate zones present are the first n zones in the binary climate data file " << endl;
				throw;
			}


		}catch (...)
		  { cerr << "Cleaning the atmosphere..." << "\n";

		  //clean up the mess...
		  if (_zones)
			  delete _zones;
		  if (_zoneId)
			  delete[] _zoneId;

		  delete _Ldown;
		  delete _Sdown;
		  delete _Tp;
		  delete _MaxTp;
		  delete _MinTp;
		  delete _Precip;
		  delete _Rel_humid;
		  delete _Wind_speed;

		  if (_isohyet)
			  delete _isohyet;

		  throw;
		  }
}
