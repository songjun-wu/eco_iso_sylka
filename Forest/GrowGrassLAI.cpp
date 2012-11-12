/*
 * GrowGrassLAI.cpp
 *
 *  Created on: Nov 11, 2012
 *      Author: marco
 */

#include "Forest.h"

int Forest::GrowGrassLAI(UINT4 spec, UINT4 row, UINT4 col, REAL8 dt){

	REAL8 SLA_g = _species[spec].SLA;

	REAL8 DryLeafTurnoverRate = _species[spec].Fprn;
	REAL8 DryLeafTurnoverRateAdjustmentParam = _species[spec].Fpra;
	REAL8 DryDecayAdjustment = min<REAL8>(_species[spec]._Temp_c->matrix[row][col] / DryLeafTurnoverRateAdjustmentParam, 1);

	REAL8 GreenLaiDecay;
	REAL8 DryLaiDecay;

	GreenLaiDecay = _species[spec].LeafTurnover * dt * _species[spec]._grassLAI_g->matrix[row][col];

	DryLaiDecay = DryLeafTurnoverRate * DryDecayAdjustment * dt * _species[spec]._grassLAI_d->matrix[row][col];

	_species[spec]._grassLAI_g->matrix[row][col] += max<REAL8>(-0.95*_species[spec]._grassLAI_g->matrix[row][col],
			_species[spec]._Del_FoliageMass->matrix[row][col] * SLA_g - GreenLaiDecay);

    _species[spec]._grassLAI_d->matrix[row][col] += GreenLaiDecay - DryLaiDecay;


	_species[spec]._LAI->matrix[row][col] =
			_species[spec]._grassLAI_g->matrix[row][col] +
			_species[spec]._grassLAI_d->matrix[row][col];


		return EXIT_SUCCESS;
}


