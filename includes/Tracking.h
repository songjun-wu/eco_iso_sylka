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

  //Spatial distribution of tracked signatures (d2H, d18O, age) in the compartments
  grid *_d2Hprecip, *_d18Oprecip;
  grid *_d2Hcanopy_sum, *_d18Ocanopy_sum, *_Agecanopy_sum; // Canopy (avg over veg fractions)
  grid *_d2Hsnowpack, *_d18Osnowpack, *_Agesnowpack; // Snowpack
  grid *_d2Hsurface,  *_d18Osurface, *_Agesurface; // Ponding
  grid *_d2Hsoil1,    *_d18Osoil1, *_Agesoil1; // Vadose layer 1
  grid *_d2Hsoil2,    *_d18Osoil2, *_Agesoil2; // Vadose layer 2
  grid *_d2Hsoil_12,  *_d18Osoil_12, *_Agesoil_12; // Weighted average L1+L2
  grid *_d2Hsoil3,    *_d18Osoil3, *_Agesoil3; // Vadose layer 3
  grid *_d2HsoilAv,   *_d18OsoilAv, *_AgesoilAv; // Vadose weighted average
  grid *_d2Hgroundwater, *_d18Ogroundwater, *_Agegroundwater; // Groundwater
  // Signature of outgoing water
  grid *_d2HevapS_sum, *_d18OevapS_sum, *_AgeevapS_sum;
  grid *_d2HevapI_sum, *_d18OevapI_sum, *_AgeevapI_sum;
  grid *_d2HevapT_sum, *_d18OevapT_sum, *_AgeevapT_sum;
  grid *_d2Hleakage, *_d18Oleakage, *_Ageleakage; // Groundwater

  //vectors containing signature of water output for each cell with no drainage (ldd value of 5). 
  // The vectCell structure contains the row and col  
  //of that cell with no output and the area draining to that cell
  vectCells _d2HOvlndOutput, _d18OOvlndOutput, _AgeOvlndOutput; // surface output
  vectCells _d2HGwtrOutput, _d18OGwtrOutput, _AgeGwtrOutput; // groundwater output

  
  //check maps mainly to make sure no nodata values are in the domain.
  void CheckMapsTrck(Control &ctrl, Basin &bsn);

 public:
  
  //Constructors
  Tracking();
  Tracking(Control &ctrl, Basin &bsn);
  
  //Destructor
  ~Tracking();
  
  /*int MixingV_evapT(Basin &bsn, Control &ctrl,
    REAL8 &pTrp1, REAL8 &pTrp2, REAL8 &pTrp3,
    REAL8 &2HevapT_f, REAL8 &18OevapT_f, REAL8 &AgeevapT_f, 
    REAL8 &p, int s, int r, int c);*/
  
  void MixingV_down(Basin &bsn, Control &ctrl, 
		    double &d1, double &d2, double &d3, double &fc,
		    double &leak, int r, int c, bool reinf);
  
  void MixingV_up(Basin &bsn, Control &ctrl, 
		  double &d1, double &d2, double &d3, double &fc,
		  int r, int c);
  
  void MixingV_evapS(Atmosphere &atm, Basin &bsn, Control &ctrl, 
		     double &d1, double &theta_new,
		     double Ts, double &etp, double &beta,
		     double &d2Hevap, double &d18Oevap, double &Agevap,
		     int r, int c);
  
  void MixingV_seep(Basin &bsn, Control &ctrl, double &ponding, double &qc, int r, int c);
  
  void MixingV_snow(Atmosphere &atm, Basin &bsn, Control &ctrl, double &dh_snow, int r, int c);
  
  void MixingV_through(Atmosphere &atm, Basin &bsn, Control &ctrl, double &rain, double &p, int r, int c);
  
  void MixingH(Basin &bsn, Control &ctrl, 
	       double &hj1i1, double &alpha, double &ponding, double &Qk1,
	       double &dtdx, double &dx, int r, int c, int rr, int cc);

  // Outlet lateral fluxes' signatures
  void OutletVals(Control &ctrl, int mode, int r, int c);

  // Generic function for both isotopes, using the 'iso' toggle: 0=deuterium, 1=oxygen18
  int Frac_Esoil(Atmosphere &atm, Basin &bsn, Control &ctrl,
		 REAL8 V_old, REAL8 V_new, REAL8 &theta,
		 REAL8 &di_old, REAL8 &di_new, REAL8 &di_evap,
		 REAL8 &Ts, int r, int c, int iso);
  
  // Age increment at end of tiem step
  int IncrementAge(Basin &bsn, Control &ctrl);
  
  // Soil averaged quantities
  int Calcd2Hsoil_12(Basin &bsn);
  int Calcd18Osoil_12(Basin &bsn);
  int CalcAgesoil_12(Basin &bsn);
  int Calcd2Hsoil_Av(Basin &bsn);
  int Calcd18Osoil_Av(Basin &bsn);
  int CalcAgesoil_Av(Basin &bsn);

  // Convert grid from isotopic ratios to isotopic deltas
  void Ratio2DeltaGrid(const Basin &bsn, const grid &m, grid &mO, int iso);
  void Ratio2DeltaGrid_L1L2(const Basin &bsn, const grid &mL1, const grid &mL2, grid &mO, int iso);
  void Ratio2DeltaGrid_SoilAv(const Basin &bsn, const grid &mL1, const grid &mL2,
			      const grid &mL3, const grid &mGW, grid &mO, int iso);
  //int ReadConfigTrck(Control &ctrl, string confilename = "configTrck.ini");
  
  //Getters 2H (ratios)
  grid *getd2Hprecip() const {
    return _d2Hprecip;
  }
  grid *getd2Hcanopy_sum() const {
    return _d2Hcanopy_sum;
  }
  grid *getd2Hsnowpack() const {
    return _d2Hsnowpack;
  }
  grid *getd2Hsurface() const {
    return _d2Hsurface;
  }
  grid *getd2Hsoil1() const {
    return _d2Hsoil1;
  }
  grid *getd2Hsoil2() const {
    return _d2Hsoil2;
  }
  grid *getd2Hsoil_12() const {
    return _d2Hsoil_12;
  }
  grid *getd2Hsoil3() const {
    return _d2Hsoil3;
  }
  grid *getd2Hsoil_Av() {
    return _d2HsoilAv;
  }
  grid *getd2Hgroundwater() const {
    return _d2Hgroundwater;
  }
  grid *getd2HevapS_sum() const {
    return _d2HevapS_sum;
  }
  grid *getd2HevapI_sum() const {
    return _d2HevapI_sum;
  }
  grid *getd2HevapT_sum() const {
    return _d2HevapT_sum;
  }
  grid *getd2Hleakage() const {
    return _d2Hleakage;
  }
  const vectCells *getd2HOvlndOutput() const {
    return &_d2HOvlndOutput;
  }  
  const vectCells *getd2HGwtrOutput() const {
    return &_d2HGwtrOutput;
  }
  // -------
  
  
  // 18O
  grid *getd18Oprecip() const {
    return _d18Oprecip;
  }
  grid *getd18Ocanopy_sum() const {
    return _d18Ocanopy_sum;
  }
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
  grid *getd18Osoil_12() const {
    return _d18Osoil_12;
  }
  grid *getd18Osoil3() const {
    return _d18Osoil3;
  }
  grid *getd18Osoil_Av() const {
    return _d18OsoilAv;
  }
  grid *getd18Ogroundwater() const {
    return _d18Ogroundwater;
  }
  grid *getd18OevapS_sum() const {
    return _d18OevapS_sum;
  }
  grid *getd18OevapI_sum() const {
    return _d18OevapI_sum;
  }
  grid *getd18OevapT_sum() const {
    return _d18OevapT_sum;
  }
  grid *getd18Oleakage() const {
    return _d18Oleakage;
  }
  const vectCells *getd18OOvlndOutput() const {
    return &_d18OOvlndOutput;
  }  
  const vectCells *getd18OGwtrOutput() const {
    return &_d18OGwtrOutput;
  }
  // -------
    
  // Age
  grid *getAgecanopy_sum() const {
    return _Agecanopy_sum;
  }
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
  grid *getAgesoil_12() const {
    return _Agesoil_12;
  }
  grid *getAgesoil3() const {
    return _Agesoil3;
  }
  grid *getAgesoil_Av() const {
    return _AgesoilAv;
  }
  grid *getAgegroundwater() const {
    return _Agegroundwater;
  }
  grid *getAgeevapS_sum() const {
    return _AgeevapS_sum;
  }
  grid *getAgeevapI_sum() const {
    return _AgeevapI_sum;
  }
  grid *getAgeevapT_sum() const {
    return _AgeevapT_sum;
  }
  grid *getAgeleakage() const {
    return _Ageleakage;
  }
  const vectCells *getAgeOvlndOutput() const {
    return &_AgeOvlndOutput;
  }  
  const vectCells *getAgeGwtrOutput() const {
    return &_AgeGwtrOutput;
  }
  // ---
  
  // --- Setters
  // - 2H
  void setd2Hcanopy_sum(UINT4 row, UINT4 col, REAL8 value) {
    _d2Hcanopy_sum->matrix[row][col] = value;
  }
  void setd2Hsnowpack(UINT4 row, UINT4 col, REAL8 value) {
    _d2Hsnowpack->matrix[row][col] = value;
  }
  void setd2Hsurface(UINT4 row, UINT4 col, REAL8 value) {
    _d2Hsurface->matrix[row][col] = value;
  }
  void setd2Hsoil1(UINT4 row, UINT4 col, REAL8 value) {
    _d2Hsoil1->matrix[row][col] = value;
  }
  void setd2Hsoil2(UINT4 row, UINT4 col, REAL8 value) {
    _d2Hsoil2->matrix[row][col] = value;
  }
  void setd2Hsoil3(UINT4 row, UINT4 col, REAL8 value) {
    _d2Hsoil3->matrix[row][col] = value;
  }
  void setd2Hgroundwater(UINT4 row, UINT4 col, REAL8 value) {
    _d2Hgroundwater->matrix[row][col] = value;
  }
  void setd2HevapS_sum(UINT4 row, UINT4 col, REAL8 value) {
    _d2HevapS_sum->matrix[row][col] = value;
  }
  void setd2HevapI_sum(UINT4 row, UINT4 col, REAL8 value) {
    _d2HevapI_sum->matrix[row][col] = value;
  }
  void setd2HevapT_sum(UINT4 row, UINT4 col, REAL8 value) {
    _d2HevapT_sum->matrix[row][col] = value;
  }

  // - 18O
  void setd18Ocanopy_sum(UINT4 row, UINT4 col, REAL8 value) {
    _d18Ocanopy_sum->matrix[row][col] = value;
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
  void setd18OevapT_sum(UINT4 row, UINT4 col, REAL8 value) {
    _d18OevapT_sum->matrix[row][col] = value;
  }

  // - Age
  void setAgecanopy_sum(UINT4 row, UINT4 col, REAL8 value) {
    _Agecanopy_sum->matrix[row][col] = value;
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
  void setAgeevapT_sum(UINT4 row, UINT4 col, REAL8 value) {
    _AgeevapT_sum->matrix[row][col] = value;
  }
  
  // When there's only input
  double InputMix(double hold, double iold, double qin, double iin){
    double inew;
    // Assign fluxes
    if(hold + qin > RNDOFFERR)
      inew = (iold*hold + iin*qin)/ (hold + qin);
    else
      inew = iold;
    return inew;
  }
  
  // When one input one output
  double InOutMix(double hold, double iold, double qin, double iin, double qout){
    double inew;
    // Assign fluxes: implicit ??
    if(hold + qin > RNDOFFERR)
      inew = (iold*hold + iin*qin)/ (hold + qin);// + qout);
    else
      inew = iold;
    return inew;
  }
  
};

#endif /* TRACKING_H_ */
