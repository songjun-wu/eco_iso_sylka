/*
 * GrowLAI.cpp
 *
 *  Created on: Jul 1, 2010
 *      Author: Marco.Maneta
 */

#include "Forest.h"

int Forest::GrowLAI(UINT4 spec, UINT4 row, UINT4 col, REAL8 T, REAL8 WatUsable, REAL8 dt){

	REAL8 SLA = _species[spec].SLA;
	REAL8 tp_ltf = 0; //leaf turnover factor due to temperature stress
	REAL8 wt_ltf = 0; //leaf turnover factor due to water stress

	REAL8 beta1 =  _species[spec].LeafTurnoverColdStressShpParam;
	REAL8 beta2 =  _species[spec].LeafTurnoverWaterStressShpParam;
	REAL8 Tcold = _species[spec].ColdStressTemp;
	REAL8 maxtemprate = _species[spec].MaxLeafTurnoverColdStress;
	REAL8 maxwaterrate = _species[spec].MaxLeafTurnoverWaterStress;

	tp_ltf = Calculate_leaf_turnover_TempStress(maxtemprate, beta1, Tcold, T);
	wt_ltf = Calculate_leaf_turnover_WaterStress(maxwaterrate, beta2, WatUsable);

	_species[spec]._LAI->matrix[row][col] += max<REAL8>(-0.95*_species[spec]._LAI->matrix[row][col],_species[spec]._Del_FoliageMass->matrix[row][col] * SLA -
			(_species[spec].LeafTurnover + tp_ltf + wt_ltf) * dt * _species[spec]._LAI->matrix[row][col]);

	return EXIT_SUCCESS;

}
