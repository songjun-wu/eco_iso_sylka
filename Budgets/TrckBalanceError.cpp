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
 *    Marco Maneta
 *******************************************************************************/
/*
 * MassBalanceError.cpp
 *
 *  Created on: Mar 18, 2010
 *      Author: Marco Maneta
 */

#include "Budget.h"

void Budget::TrckBalanceError(const Control *ctrl)
{
	double inputs = 0.0;
	double outputs = 0.0;
	double Snew = 0.0;
	
	// Tracking -------------
	double inputs_d2H = 0.0;
	double outputs_d2H = 0.0;
	double Snew_d2H = 0.0;
	double inputs_d18O = 0.0;
	double outputs_d18O = 0.0;
	double Snew_d18O = 0.0;
	double inputs_Age = 0.0;
	double outputs_Age = 0.0;
	double Snew_Age = 0.0;

	/* inputs = precipitation + initsnowpack + initponding + initvadose;
	// + initgravwater + initgrndwater; -> obsolete: gravity and groundwater embedded in vadose...	
	outputs = evaporation + ovlndflow + gwtrflow + leakage;
	
	ds = canopy + snowpack + ponding + vadose;*/
	//+ gravwater + grndwater;  -> obsolete: gravity and groundwater embedded in vadose...

	inputs = precipitation + initsnowpack + initponding + initL1 + initL2 + initL3 + initGW;
	
	outputs = evaporationS + evaporationI + transpiration + ovlndflow + gwtrflow + leakage;
	
	Snew = canopy + snowpack + ponding + soilL1 + soilL2 + soilL3 + grndwater;

	if(inputs>0) 
	  MBErr = 100/inputs*(inputs-outputs - Snew);
	else 
	  MBErr = 0;

	//Deuterium mass balance
	if(ctrl->sw_2H){
	  inputs_d2H = precipitation_d2H + initcanopy_d2H + initsnowpack_d2H + initponding_d2H + 
	    initL1_d2H + initL2_d2H + initL3_d2H + initGW_d2H;
	  
	  outputs_d2H = evaporationS_d2H + evaporationI_d2H + transpiration_d2H +
	      ovlndflow_d2H + gwtrflow_d2H + leakage_d2H;
	  
	  Snew_d2H = canopy_d2H + snowpack_d2H + ponding_d2H + soilL1_d2H + soilL2_d2H + soilL3_d2H + 
	    grndwater_d2H;
	  
	  if(abs(inputs_d2H)>0) 
	    MBErr_d2H = 100/inputs_d2H*(inputs_d2H-outputs_d2H - Snew_d2H);
	  else 
	    MBErr_d2H = 0;

	  // save last time step storage
	  initcanopy_d2H = canopy_d2H;
	  initsnowpack_d2H = snowpack_d2H;
	  initponding_d2H = ponding_d2H;
	  initL1_d2H = soilL1_d2H;
	  initL2_d2H = soilL2_d2H;
	  initL3_d2H = soilL3_d2H;
	  initGW_d2H = grndwater_d2H;
	  
	}
	
	// Oxygen 18 mass balance
	if(ctrl->sw_18O){
	  inputs_d18O = precipitation_d18O + initcanopy_d18O + initsnowpack_d18O + initponding_d18O + 
	    initL1_d18O + initL2_d18O + initL3_d18O + initGW_d18O;
	    
	    outputs_d18O = evaporationS_d18O + evaporationI_d18O + transpiration_d18O +
	      ovlndflow_d18O + gwtrflow_d18O + leakage_d18O;
	    
	    Snew_d18O = canopy_d18O + snowpack_d18O + ponding_d18O + soilL1_d18O + soilL2_d18O + soilL3_d18O + grndwater_d18O;
	    
	    
	    if(abs(inputs_d18O)>0) 
	      MBErr_d18O = 100/inputs_d18O*(inputs_d18O-outputs_d18O - Snew_d18O);
	    else 
	      MBErr_d18O = 0;

	    // save last time step storage
	    initcanopy_d18O = canopy_d18O;
	    initsnowpack_d18O = snowpack_d18O;
	    initponding_d18O = ponding_d18O;
	    initL1_d18O = soilL1_d18O;
	    initL2_d18O = soilL2_d18O;
	    initL3_d18O = soilL3_d18O;
	    initGW_d18O = grndwater_d18O;
	}
	
	// Age mass balance
	if(ctrl->sw_Age){
	  inputs_Age = precipitation_Age + // gradually aging precip  
	    initcanopy_Age + initsnowpack_Age + initponding_Age +
	    initL1_Age + initL2_Age + initL3_Age + initGW_Age + // init storage  age
	    (canopy + snowpack + ponding + vadose) * dt / 86400; // Aging water stored of beginning-of-time-step
	    //  (initsnowpack + initponding + initL1 + initL2 + initL3 + initGW) * 
	  //  (ctrl->current_ts_count-1) * dt / 86400; // Aging initial water, but use beg-time-step
	  
	  outputs_Age = evaporationS_Age + evaporationI_Age + transpiration_Age +
	    ovlndflow_Age + gwtrflow_Age + leakage_Age;
	  
	  Snew_Age = canopy_Age + snowpack_Age + ponding_Age + soilL1_Age + soilL2_Age + soilL3_Age + grndwater_Age;
	  
	  if(inputs_Age>0) 
	    MBErr_Age = 100/inputs_Age*(inputs_Age-outputs_Age - Snew_Age);
	  else 
	    MBErr_Age = 0;

	    // save last time step storage
	    initcanopy_Age = canopy_Age;
	    initsnowpack_Age = snowpack_Age;
	    initponding_Age = ponding_Age;
	    initL1_Age = soilL1_Age;
	    initL2_Age = soilL2_Age;
	    initL3_Age = soilL3_Age;
	    initGW_Age = grndwater_Age;	  
	}

	/*
	// Debugging verbose
	cout << endl << "sum(precip): " << precipitation << 
	  ", sum(Isnow): " << initsnowpack << 
	  ", sum(Isurf): " << initponding << 
	  //", sum(Ivadose): " << initvadose << endl;
	  ", sum(IsoilL1): " << initL1 << 
	  ", sum(IsoilL2): " << initL2 << 	
	  ", sum(IsoilL3): " << initL3 << 
	  ", sum(IGW): " << initGW << endl;
	
	cout << "sum(evapS): " << evaporationS << 
	  ", sum(evapI): " << evaporationI << 
	  ", sum(evapT): " << transpiration << 
	  ", sum(OutSurf): " << ovlndflow << 
	  ", sum(OutGW): " << gwtrflow << 
	  ", sum(OutLeak): " << leakage << endl;
	
	cout << "sum(canopy): " << canopy << 
	  ", sum(snowpack): " << snowpack << 
	  ", sum(ponding): " << ponding << 
	  //", sum(vadose): " << vadose << endl << endl;
	  ", sum(soilL1): " << soilL1 << 
	  ", sum(soilL2): " << soilL2 << 	
	  ", sum(soilL3): " << soilL3 << 
	  ", sum(GW): " << grndwater << endl << endl;
	
	cout << "sum(inputs): " << inputs << 
	  ", sum(outputs): " << outputs <<
	  ", sum(S) : " << Snew <<endl;
	    	

	if(ctrl->sw_2H){
	  
	  cout << endl << "sum(precip.D): " << precipitation_d2H << 
	    ", sum(Icanopy.D): " << initcanopy_d2H << 
	    ", sum(Isnow.D): " << initsnowpack_d2H << 
	    ", sum(Isurf.D): " << initponding_d2H << 
	    ", sum(IsoilL1.D): " << initL1_d2H << 
	    ", sum(IsoilL2.D): " << initL2_d2H << 	
	    ", sum(IsoilL3.D): " << initL3_d2H << 
	    ", sum(IGW.D): " << initGW_d2H << endl;
	  
	  cout << "sum(evapS.D): " << evaporationS_d2H << 
	    ", sum(evapI.D): " << evaporationI_d2H << 
	    ", sum(evapT.D): " << transpiration_d2H << 
	    ", sum(OutSurf.D): " << ovlndflow_d2H << 
	    ", sum(OutGW.D): " << gwtrflow_d2H << 
	    ", sum(OutLeak.D): " << leakage_d2H << endl;
	  
	  cout << "sum(canopy.D): " << canopy_d2H << 
	    ", sum(snowpack.D): " << snowpack_d2H << 
	    ", sum(ponding.D): " << ponding_d2H << 
	    ", sum(soilL1.D): " << soilL1_d2H << 
	    ", sum(soilL2.D): " << soilL2_d2H << 
	    ", sum(soilL3.D): " << soilL3_d2H << 
	    ", sum(GW.D): " << grndwater_d2H << endl << endl;
	  
	  cout << "sum(inputs.D/inputs): " << inputs_d2H/inputs << ", sum(outputs.D/outputs): " << 
	    outputs_d2H/outputs << ", sum(dS.D/dS) : " << Snew_d2H/Snew <<endl;
	  cout << "sum(inputs.D): " << inputs_d2H << ", sum(outputs.D): " << 
	    outputs_d2H << ", sum(dS.D) : " << Snew_d2H <<endl;
	  
	}
	
	if(ctrl->sw_18O){
	  
	  cout << endl << "sum(precip.18O): " << precipitation_d18O << 
	    ", sum(Icanopy.18O): " << initcanopy_d18O << 
	    ", sum(Isnow.18O): " << initsnowpack_d18O << 
	    ", sum(Isurf.18O): " << initponding_d18O << 
	    ", sum(IsoilL1.18O): " << initL1_d18O << 
	    ", sum(IsoilL2.18O): " << initL2_d18O << 	
	    ", sum(IsoilL3.18O): " << initL3_d18O << 
	    ", sum(IGW.18O): " << initGW_d18O << endl;
	  
	  cout << "sum(evapS.18O): " << evaporationS_d18O << 
	    ", sum(evapI.18O): " << evaporationI_d18O << 
	    ", sum(evapT.18O): " << transpiration_d18O << 
	    ", sum(OutSurf.18O): " << ovlndflow_d18O << 
	    ", sum(OutGW.18O): " << gwtrflow_d18O << 
	    ", sum(OutLeak.18O): " << leakage_d18O << endl;
	  
	  cout << "sum(canopy.18O): " << canopy_d18O << 
	    ", sum(snowpack.18O): " << snowpack_d18O << 
	    ", sum(pondingT.18O): " << ponding_d18O << 
	    ", sum(soilL1.18O): " << soilL1_d18O << 
	    ", sum(soilL2.18O): " << soilL2_d18O << 
	    ", sum(soilL3.18O): " << soilL3_d18O << 
	    ", sum(GW.18O): " << grndwater_d18O << endl << endl;
	  
	  cout << "sum(inputs.18O/inputs): " << inputs_d18O/inputs << 
	    ", sum(outputs.18O/outputs): " << outputs_d18O/outputs <<
	    ", sum(dS.18O/dS) : " << Snew_d18O/Snew <<endl << endl;
	  cout << "sum(inputs.18O): " << inputs_d18O << ", sum(outputs.18O): " << 
	    outputs_d18O << ", sum(dS.18O) : " << Snew_d18O <<endl;
	  
	}
	
	if(ctrl->sw_Age){
	  
	  cout << endl << "sum(precip.Age): " << precipitation_Age << 
	    ", sum(Isnow.Age): " << initsnowpack_Age+initsnowpack*(ctrl->current_ts_count-1)*dt/86400 << 
	    ", sum(Isurf.Age): " << initponding_Age+initponding*(ctrl->current_ts_count-1)*dt/86400 << 
	    ", sum(IsoilL1.Age): " << initL1_Age+initL1*(ctrl->current_ts_count-1)*dt/86400 << 
	    ", sum(IsoilL2.Age): " << initL2_Age+initL2*(ctrl->current_ts_count-1)*dt/86400 << 	
	    ", sum(IsoilL3.Age): " << initL3_Age+initL3*(ctrl->current_ts_count-1)*dt/86400 << 
	    ", sum(IGW.Age): " << initGW_Age+initGW*(ctrl->current_ts_count-1)*dt/86400 << endl;
	  
	  cout << "sum(evapS.Age): " << evaporationS_Age << 
	    ", sum(evapI.Age): " << evaporationI_Age << 
	    ", sum(evapT.Age): " << transpiration_Age << 
	    ", sum(OutSurf.Age): " << ovlndflow_Age << 
	    ", sum(OutGW.Age): " << gwtrflow_Age << 
	    ", sum(OutLeak.Age): " << leakage_Age << endl;
	  
	  cout << "sum(canopy.Age): " << canopy_Age << 
	    ", sum(snowpack.Age): " << snowpack_Age << 
	    ", sum(pondingT.Age): " << ponding_Age << 
	    ", sum(soilL1.Age): " << soilL1_Age << 
	    ", sum(soilL2.Age): " << soilL2_Age << 
	    ", sum(soilL3.Age): " << soilL3_Age << 
	    ", sum(GW.Age): " << grndwater_Age << endl << endl;
	  
	  cout << "sum(inputs.Age/inputs): " << inputs_Age/inputs << 
	    ", sum(outputs.Age/outputs): " << outputs_Age/outputs <<
	    ", sum(dS.Age/dS) : " << Snew_Age/Snew <<endl;
	  cout << "sum(inputs.Age): " << inputs_Age << 
	    ", sum(outputs.Age): " << outputs_Age <<
	    ", sum(dS.Age) : " << Snew_Age <<endl;
	    }
	*/
	
}
