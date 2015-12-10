/*
 * grove.h
 *
 *  Created on: Jun 17, 2010
 *      Author: marco
 */

#ifndef GROVE_H_
#define GROVE_H_

#include "Grid.h"

struct Grove {

	/*Constant parameters*/
	REAL8 ID; //species ID
	REAL8 GPP2NPP; //GPP to NPP ratio
	REAL8 alpha; //Canopy quantum efficiency (g C J-1)
	REAL8 gsmax; //maximum stomatal conductance (m s-1)
	REAL8 MaxAge; //maximum age of species
	REAL8 TempOpt; //optimal temperature of species degC
	REAL8 TempMax; //maximum temperature in which specie can grow degC
	REAL8 TempMin; //maximum temperature in which specie can grow degC
	REAL8 Fprn; //coefficient n for allocation of NPP to foliage or dead grass leaf turnover rate if is_grass = 1
	REAL8 Fpra; //coefficient a for allocation of NPP to foliage or dead grass leaf turnover adjustment rate if is_grass = 1
	REAL8 Sprn; //coefficient n for allocation of NPP to stems
	REAL8 Spra; //coefficient a for allocation of NPP to stems
	REAL8 gs_light_coeff; //curvature coefficient for light factor in stomatal conductance
	REAL8 gs_vpd_coeff; //curvature coefficient for vapor pressure deficit factor in stomatal conductance
	REAL8 lwp_low; //lwp level for complete closure on stomatal conductance (- m of head)
	REAL8 lwp_high; //lwp level for no hydrologic control on stomatal conductance (- m of head)
	REAL8 WiltingPoint; //volumetric soil moisture at wilting point for the species
	REAL8 SLA; //specific leaf area (m2 g-1)
	REAL8 SRA; //specific root area (m2 g-1)
	REAL8 Crown2Stem; //crown to stem diameter ratio (m m-1)
	REAL8 TreeShapePar; //tree shape parameter from TREEDYN3
	REAL8 WoodDensity; //wood density (gC m-3)
	REAL8 Fhdmin; //minimum tree growth factor [0,1]
	REAL8 Fhdmax; //maximum tree growth factor [0,1]
	REAL8 LeafTurnover; //leaf turnover rate (s-1)
	REAL8 RootTurnover; //root turnover rate (s-1)
	REAL8 MaxCanStorageParamt; //parameter to calcualte maximum canopy storage (after Dickinson 1984 via Liang et al. 1994)
	REAL8 albedo; //albedo of dry canopy
	REAL8 emissivity; //emissivity of dry canopy
	REAL8 KBeers; //Extinction coefficient in Beers law of light extinction
	REAL8 beta; //canopy water efficiency (gC m-1)
	// Sperry parameters
	REAL8 sperry_d; // Sperry model scaling parameter (m)
	REAL8 sperry_c; // Sperry model shape exponent (m)
	REAL8 sperry_Kp; // Sperry model hydraulic conductivity tissue (ms-1) used to calculate conductaance using DBH and plant height
	REAL8 RAI_a; // parameter to scale effective RAI as per Daly et al. (2004). Coupled Dynamics of Photosynthesis,.... J Hydromet.
	bool is_grass; //switch to indicate the species is of type grass
	REAL8 MaxLeafTurnoverWaterStress; //maximum leaf turnover rate due to water stress (s-1)
	REAL8 LeafTurnoverWaterStressShpParam; //Shape parameter leaf turnover rate due to water stress (-)
	REAL8 MaxLeafTurnoverColdStress; //maximum leaf turnover rate due to cold stress (s-1)
	REAL8 ColdStressTemp; //maximum leaf turnover rate due to cold stress (C)
	REAL8 LeafTurnoverColdStressShpParam; //Shape  parameter leaf turnover rate due to cold stress (-)

	/*state variables*/
	grid *_fraction;
	grid *_StemDensity; //number of trees per square meter (trees m-2)
	grid *_LAI;
	grid *_grassLAI_g;//Leaf area index of green grass
	grid *_grassLAI_d;//Leaf area index of dry grass
	grid *_AGE; //stand age in years
	grid *_CanopyConductance;//canopy conductance in m s-1
	grid *_GPP; //gross primary production in gCm-2
	grid *_NPP; //net primary production in gCm-2
	grid *_BasalArea; //Average stem cross-sectional area (m2)
	grid *_Height; //tree height (m)
	grid *_RootMass; //density of roots gC m-2
	grid *_Del_FoliageMass; //increment of leaf mass gCm-2
	grid *_Del_StemMass; //increment of stem mass gCm-2
	grid *_Del_RootMass; //increment of root mass gCm-2
	grid *_Temp_c; //canopy temperature C
	grid *_NetR_Can;//canopy net radiation Wm-2
	grid *_LatHeat_Can;//Canopy latent heat Wm-2
	grid *_SensHeat_Can;//Canopy sensible heat Wm-2
	grid *_WaterStorage; //current water stored in canopy m
	grid *_ET; //Actual evapotranspiration ms-1
	grid *_Transpiration; //transpiration component ms-1
	grid *_LeafWatPot; // leaf water potential (positive m of head)



	Grove();
	~Grove();

	int CreateGrids(grid *base);

};




#endif /* GROVE_H_ */
