/*
 * Budget.h
 *
 *  Created on: Mar 8, 2010
 *      Author: Marco Maneta
 */

#ifndef BUDGET_H_
#define BUDGET_H_

#include "Basin.h"
#include "Atmosphere.h"
#include "InitConf.h"

struct Budget {


	double dt;
	double MBErr;

	//init storages
	double initsnowpack; //m3
	double initponding; //m3
	double initvadose; //m3
	double initgravwater; //m3
	double initgrndwater; //m3

	//storages
	REAL8 canopy; //m3
	double snowpack; //m3
	double ponding; //m3
	double vadose; //m3
	double gravwater; //m3
	double grndwater; //m3


	//water inputs
	double precipitation;
	double snowfall;


	//water outputs
	double evaporation; //m3s-1
	double ovlndflow; //m3s-1
	double gwtrflow; //m3s-1



	double AccountFluxes(const grid *map, const Basin *b);
	double AccountFluxes(const grid *map, const Atmosphere *b);
	double AccountFluxes(const vectCells *timeseries, const Basin *b);
	double AccountStorages(const grid *map, const Basin *b);

	void TotalPrecipitation(const grid* map, const Atmosphere *b);
	void TotalEvaporation(const grid* map, const Basin *b);
	void TotalOvlndFlow(const vectCells *timeseries, const Basin *b);
	void TotalGrndFlow(const vectCells *timeseries, const Basin*b);
	void TotalStorage(	const grid *Canopy,
						const grid *Snow,
						const grid *Ponding,
						const grid *Vadose,
						const grid *GravWater,
						const grid *GrndWater,
						const Basin *b);

	void MassBalanceError();

	//constructor inline
	Budget(const Basin *b, const Control *ctrl)
	{
		dt = ctrl->dt;
		snowpack = 0;
		ponding = 0;
		vadose = 0;
		gravwater = 0;

		precipitation = 0;
		snowfall = 0;

		evaporation = 0;
		ovlndflow = 0;
		gwtrflow = 0;

		//calculate initial storages
		initsnowpack = AccountStorages(b->getSnowWaterEquiv(), b);
		initponding = AccountStorages(b->getPondingWater(), b);
		initvadose = AccountStorages(b->getSoilWaterDepth(), b);
		initgravwater = AccountStorages(b->getGravityWater(), b);
		initgrndwater = AccountStorages(b->getGrndWater(),b);

	}

};

#endif /* BUDGET_H_ */
