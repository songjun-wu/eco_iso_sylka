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

grid *Basin::getCanopyLatHeat(UINT4 n) const {
	return fForest->getCanopyLatHeatSpeciesMap(n);
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
