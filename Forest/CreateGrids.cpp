/*
 * CreateGroves.cpp
 *
 *  Created on: Jun 18, 2010
 *      Author: marco
 */

#include "Grove.h"

int Grove::CreateGrids(grid *base){

	try{
		_fraction = new grid (*base);
		_StemDensity = new grid (*base);
		_LAI = new grid (*base);
		_grassLAI_g = new grid (*base);
		_grassLAI_d = new grid (*base);
		_AGE = new grid (*base);
		_CanopyConductance = new grid (*base);
		_GPP = new grid (*base);
		_NPP = new grid (*base);
		_BasalArea = new grid (*base);
		_Height = new grid (*base);
		_RootMass = new grid (*base);
		_Del_FoliageMass = new grid (*base);
		_Del_StemMass = new grid (*base);
		_Del_RootMass = new grid (*base);
		_Temp_c = new grid(*base);
		_NetR_Can = new grid (*base);
		_LatHeat_Can = new grid (*base);
		_SensHeat_Can = new grid (*base);
		_WaterStorage = new grid (*base);
		_ET = new grid (*base);
		_Transpiration = new grid (*base);
		_LeafWatPot = new grid (*base);


	}catch(const exception& e){

		cerr << "Failed allocate memory for Grove grid object \n" << e.what() << endl;
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
