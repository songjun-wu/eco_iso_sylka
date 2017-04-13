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
 * MapGetters.cpp
 *
 *  Created on: Aug 19, 2010
 *      Author: Marco.Maneta
 */

#include "Basin.h"

grid *Basin::getVegetFrac(UINT4 n) const {
		return fForest->getPropSpeciesMap(n);
}

grid *Basin::getLAI(UINT4 n) const {
		return fForest->getLAISpeciesMap(n);
}

grid *Basin::getStemDensity(UINT4 n) const {
		return fForest->getStemDensSpeciesMap(n);
}

grid *Basin::getStandAge(UINT4 n) const {
	return fForest->getAgeSpeciesMap(n);
}

grid *Basin::getCanopyCond(UINT4 n) const {
	return fForest->getCanopyConductSpeciesMap(n);
}

grid *Basin::getGPP(UINT4 n) const {
	return fForest->getGPPSpeciesMap(n);
}

grid *Basin::getNPP(UINT4 n) const {
	return fForest->getNPPSpeciesMap(n);
}

grid *Basin::getBasalArea(UINT4 n) const {
	return fForest->getBasalAreaSpeciesMap(n);
}

grid *Basin::getTreeHeight(UINT4 n) const {
	return fForest->getTreeHeightSpeciesMap(n);
}

grid *Basin::getRootMass(UINT4 n) const {
	return fForest->getRootMassSpeciesMap(n);
}

grid *Basin::getCanopyTemp(UINT4 n) const {
	return fForest->getCanopyTempSpeciesMap(n);
}

grid *Basin::getCanopyNetRad(UINT4 n) const {
	return fForest->getCanopyNetRadSpeciesMap(n);
}

grid *Basin::getCanopyLatHeatE(UINT4 n) const {
	return fForest->getCanopyLatHeatESpeciesMap(n);
}

grid *Basin::getCanopyLatHeatT(UINT4 n) const {
	return fForest->getCanopyLatHeatTSpeciesMap(n);
}

grid *Basin::getCanopySensHeat(UINT4 n) const {
	return fForest->getCanopySensHeatSpeciesMap(n);
}

grid *Basin::getCanopyWaterStor(UINT4 n) const {
	return fForest->getCanopyWaterStorSpeciesMap(n);
}

grid *Basin::getTranspiration(UINT4 n) const {
	return fForest->getTranspirationSpeciesMap(n);
}

grid *Basin::getEinterception(UINT4 n) const {
	return fForest->getEinterceptionSpeciesMap(n);
}

grid *Basin::getLeafWaterPotential(UINT4 n) const {
	return fForest->getLeafWaterPotSpeciesMap(n);
}
