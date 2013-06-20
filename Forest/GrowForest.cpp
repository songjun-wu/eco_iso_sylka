/*
 * CalculateGPP.cpp
 *
 *  Created on: Jun 20, 2010
 *      Author: marco
 */

#include "Forest.h"

int Forest::GrowForest(Basin &bas, const Atmosphere &atm, const Control &ctrl) {

	UINT4 r, c;
	REAL8 dt;
	REAL8 alpha = 0; //canopy quantum efficiency
	REAL8 beta = 0; //canopy water efficiency
	REAL8 par = 0;
	REAL8 lai = 0;
	REAL8 forestAge = 0;
	REAL8 airTemp, optTemp, maxTemp, minTemp;
	REAL8 Wc, Wp, UsableTheta, Wr, gsmax;
	REAL8 fa, ft, fw;
	REAL8 E;
	unsigned int k;
	unsigned int j;

	dt = ctrl.dt;

	for (j = 0; j < _Nsp - 1; j++) //grow forest up to Nsp -1 because Nsp is bare soil

#pragma omp parallel for default(none) \
			private( k, r, c, alpha, beta, par, E, lai, forestAge, \
					airTemp, optTemp, maxTemp, minTemp, Wc, Wp, gsmax,\
					UsableTheta, Wr, fa, ft ,fw ) \
					shared(j,bas, atm, ctrl,dt)

		for (k = 0; k < _vSortedGrid.cells.size(); k++) {
			r = _vSortedGrid.cells[k].row;
			c = _vSortedGrid.cells[k].col;

			if (_species[j]._fraction->matrix[r][c] < RNDOFFERR) //if there are no trees of teh species there is nothign to grow
				continue;

			alpha = _species[j].alpha;
			beta = _species[j].beta;
			par = atm.getIncomingShortWave()->matrix[r][c] * dt * 0.47; //dt to convert watts to joules. Assume 47% of incoming solar radiation is par
			E = _species[j]._Transpiration->matrix[r][c] * dt; //total amount of transpiration for the time period (m)
			lai = _species[j]._LAI->matrix[r][c];
			forestAge = _species[j]._AGE->matrix[r][c];
			airTemp = atm.getTemperature()->matrix[r][c];
			optTemp = _species[j].TempOpt;
			maxTemp = _species[j].TempMax;
			minTemp = _species[j].TempMin;
			Wc = bas.getParamWc()->matrix[r][c];
			Wp = bas.getParamWp()->matrix[r][c];
			gsmax = _species[j].gsmax;

			if (bas.getSoilMoist()->matrix[r][c] < _species[j].WiltingPoint)
				UsableTheta = 0;
			else {
				UsableTheta =
						bas.getSoilMoist()->matrix[r][c]
								> bas.getFieldCapacity()->matrix[r][c] ?
								1 :
								(bas.getFieldCapacity()->matrix[r][c]
										- bas.getSoilMoist()->matrix[r][c])
										/ (bas.getFieldCapacity()->matrix[r][c]
												- _species[j].WiltingPoint);
			}

			Wr = /*_species[j]._fraction->matrix[r][c] **/UsableTheta; //TODO: URGENT: improve competition for water. no competition now*/

			fa = Calculate_fa(_species[j].MaxAge, forestAge);
			ft = Calculate_ft(airTemp, maxTemp, minTemp, optTemp);

			fw = Calculate_fw(_species[j]._CanopyConductance->matrix[r][c],
					gsmax, Wr, Wc, Wp);

			_species[j]._GPP->matrix[r][c] = sqrtl(alpha * par * beta * E) * fa
					* ft; // * fw;
			_species[j]._NPP->matrix[r][c] = _species[j]._GPP->matrix[r][c]
					* _species[j].GPP2NPP;

			if (_species[j].is_grass)
				GrowGrass(j, r, c, dt);
			else
				GrowTrees(j, r, c, dt, fa, ft, fw, atm.getMinTemperature()->matrix[r][c], UsableTheta);

		}
	return EXIT_SUCCESS;
}
