/*******************************************************************************
 * Ech2o, a spatially-distributed, ecohydrologic simulator
 * Copyright (c) 2016 Marco Maneta <marco.maneta@umontana.edu>
 *
 *     This file is part of ech2o, a hydrologic model developed at the 
 *     University of Montana.
 *
 *     Ech2o is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     Ech2o is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with Ech2o.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contributors:
 *    Marco Maneta, Sylvain Kuppel
 *******************************************************************************/
/*
 * Tracking.h
 *
 *  Created on: Nov 14, 2016
 *      Author: Sylvain Kuppel
 *
 */

#ifndef TRACKING_H_
#define TRACKING_H_

#include "Grid.h"
#include "SortGrid.h"
#include "Basin.h"
#include "Atmosphere.h"
#include "InitConf.h"

#include <omp.h>
#include <errno.h>

using namespace std;

class Basin;
class Tracking {

	//Spatial distribution of tracked signatures (dD, d18O, age) in the compartments
	grid *_dDcanopy, *_d18Ocanopy, *_Agecanopy; // Snowpack
	grid *_dDsnowpack, *_d18Osnowpack, *_Agesnowpack; // Snowpack
	grid *_dDsurface,  *_d18Osurface, *_Agesurface; // Ponding
	grid *_dDsoil1,    *_d18Osoil1, *_Agesoil1; // Vadose layer 1
	grid *_dDsoil2,    *_d18Osoil2, *_Agesoil2; // Vadose layer 2
	grid *_dDsoil3,    *_d18Osoil3, *_Agesoil3; // Vadose layer 3
	//grid *_dDsoilAv,   *_d18OsoilAv, *_AgesoilAv; // Vadose average
	grid *_dDgroundwater, *_d18Ogroundwater, *_Agegroundwater; // Groundwater
	// Signature of outgoing water
	grid *_dDevapS_sum, *_d18OevapS_sum, *_AgeevapS_sum;
	grid *_dDevapI_sum, *_d18OevapI_sum, *_AgeevapI_sum;
	grid *_dDtranspi_sum, *_d18Otranspi_sum, *_Agetranspi_sum;

	//check maps mainly to make sure no nodata values are in the domain.
	void CheckMapsTrck(Control &ctrl, Basin &bsn);

public:

	//Constructors
	Tracking();
	Tracking(Control &ctrl, Basin &bsn);

	//Destructor
	~Tracking();

	int dDfrac_E(Atmosphere &atm, Basin &bsn, Control &ctrl,
			REAL8 V_old, REAL8 V_new, REAL8 &dD_old, REAL8 &dD_new, REAL8 &dDevap,
			int r, int c);
	int d18Ofrac_E(Atmosphere &atm, Basin &bsn, Control &ctrl,
			REAL8 V_old, REAL8 V_new, REAL8 &d18O_old, REAL8 &d18O_new, REAL8 &d18Oevap,
			int r, int c);

	int IncrementAge(Basin &bsn, Control &ctrl);

	//int ReadConfigTrck(Control &ctrl, string confilename = "configTrck.ini");

	//Getters
	grid *getdDsnowpack() const {
		return _dDsnowpack;
	}
	grid *getdDsurface() const {
		return _dDsurface;
	}
	grid *getdDsoil1() const {
		return _dDsoil1;
	}
	grid *getdDsoil2() const {
		return _dDsoil2;
	}
	grid *getdDsoil3() const {
		return _dDsoil3;
	}
	/*	grid *getdDsoilAv(Basin &bsn) const {

		double depth;
		double d1, d2, d3;
		int r, c;
#pragma omp parallel for\
		default(none) private(r,c,depth, d1, d2, d3)
		for (unsigned int j = 0; j < bsn.getSortedGrid().cells.size(); j++) {
			r = bsn.getSortedGrid().cells[j].row;
			c = bsn.getSortedGrid().cells[j].col;
			depth = bsn.getSoilDepth()->matrix[r][c];
			d1 = bsn.getSoilDepth1()->matrix[r][c];
			d2 = bsn.getSoilDepth1()->matrix[r][c];
			d3 = depth - d1 - d2;
			_dDsoilAv->matrix[r][c] = (_dDsoil1->matrix[r][c] * d1
					+ _dDsoil2->matrix[r][c] * d2
					+ _dDsoil3->matrix[r][c] * d3) / depth;
		}

		return _dDsoilAv;
	}*/

	grid *getdDgroundwater() const {
		return _dDgroundwater;
	}
	grid *getdDevapS_sum() const {
		return _dDevapS_sum;
	}
	grid *getdDevapI_sum() const {
		return _dDevapI_sum;
	}
	grid *getdDtranspi_sum() const {
		return _dDtranspi_sum;
	}

	// 18O
	grid *getd18Osnowpack() const {
		return _d18Osnowpack;
	}
	grid *getd18Osurface() const {
		return _d18Osurface;
	}
	grid *getd18Osoil1() const {
		return _d18Osoil1;
	}
	grid *getd18Osoil2() const {
		return _d18Osoil2;
	}
	grid *getd18Osoil3() const {
		return _d18Osoil3;
	}
	/*	grid *getd18OsoilAv(Basin &bsn) const {

		double depth;
		double d1, d2, d3;
		int r, c;
#pragma omp parallel for\
		default(none) private(r,c,depth, d1, d2, d3)
		for (unsigned int j = 0; j < bsn.getSortedGrid().cells.size(); j++) {
			r = bsn.getSortedGrid().cells[j].row;
			c = bsn.getSortedGrid().cells[j].col;
			depth = bsn.getSoilDepth()->matrix[r][c];
			d1 = bsn.getSoilDepth1()->matrix[r][c];
			d2 = bsn.getSoilDepth1()->matrix[r][c];
			d3 = depth - d1 - d2;
			_d18OsoilAv->matrix[r][c] = (_d18Osoil1->matrix[r][c] * d1
					+ _d18Osoil2->matrix[r][c] * d2
					+ _d18Osoil3->matrix[r][c] * d3) / depth;
		}
		return _d18OsoilAv;
	}*/
	grid *getd18Ogroundwater() const {
		return _d18Ogroundwater;
	}
	grid *getd18OevapS_sum() const {
		return _d18OevapS_sum;
	}
	grid *getd18OevapI_sum() const {
		return _d18OevapI_sum;
	}
	grid *getd18Otranspi_sum() const {
		return _d18Otranspi_sum;
	}

	// Age
	grid *getAgesnowpack() const {
		return _Agesnowpack;
	}
	grid *getAgesurface() const {
		return _Agesurface;
	}
	grid *getAgesoil1() const {
		return _Agesoil1;
	}
	grid *getAgesoil2() const {
		return _Agesoil2;
	}
	grid *getAgesoil3() const {
		return _Agesoil3;
	}
	/*	grid *getAgesoilAv(Basin &bsn) const {

		double depth;
		double d1, d2, d3;
		int r, c;
#pragma omp parallel for\
		default(none) private(r,c,depth, d1, d2, d3)
		for (unsigned int j = 0; j < bsn.getSortedGrid().cells.size(); j++) {
			r = bsn.getSortedGrid().cells[j].row;
			c = bsn.getSortedGrid().cells[j].col;
			depth = bsn.getSoilDepth()->matrix[r][c];
			d1 = bsn.getSoilDepth1()->matrix[r][c];
			d2 = bsn.getSoilDepth1()->matrix[r][c];
			d3 = depth - d1 - d2;
			_AgesoilAv->matrix[r][c] = (_Agesoil1->matrix[r][c] * d1
					+ _Agesoil2->matrix[r][c] * d2
					+ _Agesoil3->matrix[r][c] * d3) / depth;
		}
		return _AgesoilAv;
	}*/
	grid *getAgegroundwater() const {
		return _Agegroundwater;
	}
	grid *getAgeevapS_sum() const {
		return _AgeevapS_sum;
	}
	grid *getAgeevapI_sum() const {
		return _AgeevapI_sum;
	}
	grid *getAgetranspi_sum() const {
		return _Agetranspi_sum;
	}

	void setdDsnowpack(UINT4 row, UINT4 col, REAL8 value) {
		_dDsnowpack->matrix[row][col] = value;
		}
	void setdDsurface(UINT4 row, UINT4 col, REAL8 value) {
		_dDsurface->matrix[row][col] = value;
	}
	void setdDsoil1(UINT4 row, UINT4 col, REAL8 value) {
		_dDsoil1->matrix[row][col] = value;
	}
	void setdDsoil2(UINT4 row, UINT4 col, REAL8 value) {
		_dDsoil2->matrix[row][col] = value;
	}
	void setdDsoil3(UINT4 row, UINT4 col, REAL8 value) {
		_dDsoil3->matrix[row][col] = value;
	}
	void setdDgroundwater(UINT4 row, UINT4 col, REAL8 value) {
		_dDgroundwater->matrix[row][col] = value;
	}
	void setdDevapS_sum(UINT4 row, UINT4 col, REAL8 value) {
		_dDevapS_sum->matrix[row][col] = value;
	}
	void setdDevapI_sum(UINT4 row, UINT4 col, REAL8 value) {
		_dDevapI_sum->matrix[row][col] = value;
	}
	void setdDtranspi_sum(UINT4 row, UINT4 col, REAL8 value) {
		_dDtranspi_sum->matrix[row][col] = value;
	}

	void setd18Osnowpack(UINT4 row, UINT4 col, REAL8 value) {
		_d18Osnowpack->matrix[row][col] = value;
		}
	void setd18Osurface(UINT4 row, UINT4 col, REAL8 value) {
		_d18Osurface->matrix[row][col] = value;
	}
	void setd18Osoil1(UINT4 row, UINT4 col, REAL8 value) {
		_d18Osoil1->matrix[row][col] = value;
	}
	void setd18Osoil2(UINT4 row, UINT4 col, REAL8 value) {
		_d18Osoil2->matrix[row][col] = value;
	}
	void setd18Osoil3(UINT4 row, UINT4 col, REAL8 value) {
		_d18Osoil3->matrix[row][col] = value;
	}
	void setd18Ogroundwater(UINT4 row, UINT4 col, REAL8 value) {
		_d18Ogroundwater->matrix[row][col] = value;
	}
	void setd18OevapS_sum(UINT4 row, UINT4 col, REAL8 value) {
		_d18OevapS_sum->matrix[row][col] = value;
	}
	void setd18OevapI_sum(UINT4 row, UINT4 col, REAL8 value) {
		_d18OevapI_sum->matrix[row][col] = value;
	}
	void setd18Otranspi_sum(UINT4 row, UINT4 col, REAL8 value) {
		_d18Otranspi_sum->matrix[row][col] = value;
	}

	void setAgesnowpack(UINT4 row, UINT4 col, REAL8 value) {
		_Agesnowpack->matrix[row][col] = value;
		}
	void setAgesurface(UINT4 row, UINT4 col, REAL8 value) {
		_Agesurface->matrix[row][col] = value;
	}
	void setAgesoil1(UINT4 row, UINT4 col, REAL8 value) {
		_Agesoil1->matrix[row][col] = value;
	}
	void setAgesoil2(UINT4 row, UINT4 col, REAL8 value) {
		_Agesoil2->matrix[row][col] = value;
	}
	void setAgesoil3(UINT4 row, UINT4 col, REAL8 value) {
		_Agesoil3->matrix[row][col] = value;
	}
	void setAgegroundwater(UINT4 row, UINT4 col, REAL8 value) {
		_Agegroundwater->matrix[row][col] = value;
	}
	void setAgeevapS_sum(UINT4 row, UINT4 col, REAL8 value) {
		_AgeevapS_sum->matrix[row][col] = value;
	}
	void setAgeevapI_sum(UINT4 row, UINT4 col, REAL8 value) {
		_AgeevapI_sum->matrix[row][col] = value;
	}
	void setAgetranspi_sum(UINT4 row, UINT4 col, REAL8 value) {
		_Agetranspi_sum->matrix[row][col] = value;
	}

	// When there's only input
	double InputMix(double hold, double iold, double qin, double iin){
		double inew;
		// Assign fluxes
		if(hold + qin > 0)
			inew = (iold*hold + iin*qin)/ (hold + qin);
		else
			inew = iold;
		return inew;
	}

	// When one input one output
	double InOutMix(double hold, double iold, double qin, double iin, double qout){
		double inew;
		// Assign fluxes: implicit ??
		if(hold + qin > 0)
			inew = (iold*hold + iin*qin)/ (hold + qin);// + qout);
		else
			inew = iold;
		return inew;
	}

};

#endif /* TRACKING_H_ */
