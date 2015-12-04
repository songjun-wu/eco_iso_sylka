/*
 * Forest.h
 *
 *  Created on: May 5, 2010
 *      Author: Marco.Maneta
 */

#ifndef FOREST_H_
#define FOREST_H_

#include "Grid.h"
#include "InitConf.h"
#include "ConstAndFuncs.h"
#include "SortGrid.h"
#include "Grove.h"
#include "Atmosphere.h"
#include "Basin.h"


using namespace std;
class Basin;
class Forest {

			UINT4 _NRows;
			UINT4 _NCols;
			REAL8 _dx;
			UINT4 _Nsp; //number of species included in the simulation including clear cut (bare) soil
			grid *_patches; //map with forest patches
			vectCells _vSortedGrid;

			Grove *_species;


			vectCells SortGrid();

			void checkForestDatabase();

			int SetStateVarsTabs(Control &ctrl);
			void SetStateVarsMaps(Control &ctrl);
			int SetSpeciesParameters(Control &ctrl);

			/*State variables*/

			int GrowTrees(UINT4 j, UINT4 r, UINT4 c, REAL8 dt, REAL8 fa, REAL8 ft, REAL8 fw, REAL8 T, REAL8 usablewater);
			int GrowStem(UINT4 spec, UINT4 row, UINT4 col);
			int GrowLAI(UINT4 spec, UINT4 row, UINT4 col, REAL8 T, REAL8 waterusable, REAL8 dt);
			int GrowRoots(UINT4 spec, UINT4 row, UINT4 col, REAL8 dt);

			int GrowGrass(UINT4 j, UINT4 r, UINT4 c, REAL8 dt);
			int GrowGrassLAI(UINT4 spec, UINT4 row, UINT4 col, REAL8 dt);

			double NetRadCanopy(Atmosphere &atm, const double &Ts, REAL8 emiss, REAL8 albedo, REAL8 Kbeers, REAL8 lai, int row, int col);
			double LatHeatCanopy(Basin &bas, Atmosphere &atm, double soilrelhumid, double ra, const double &Ts, int row, int col);
			double SensHeatCanopy(Atmosphere &atm, double ra, const double &Ts, int row, int col);

public:

	Forest();
	Forest(Control & ctrl);
    ~Forest();

   int CalculateCanopyConduct(const Basin &bas, const Atmosphere &atm, const Control &ctrl, const double &theta,const double &fc, UINT4 j, UINT4 r, UINT4 c);
   UINT4 SolveCanopyEnergyBalance(Basin &bas, Atmosphere &atm,
			Control &ctrl, REAL8 theta, REAL8 thetar, REAL8 poros, REAL8 rootdepth,
			REAL8 Keff, REAL8 psiae, REAL8 bclambda,
			REAL8 ra, REAL8 gc, REAL8 &DelCanStor, REAL8 &evap_a, REAL8 &transp_a,
			UINT4 s, UINT4 r, UINT4 c);
   int CanopyInterception(Atmosphere &atm, Control &ctrl, REAL8 &DelCanStor, REAL8 &D, UINT4 s, UINT4 r, UINT4 c);
   int GrowForest(Basin &bas, const Atmosphere &atm, const Control &ctrl);


    //getters
    UINT4 getNumSpecies() const {
   		return _Nsp;
    }

    REAL8 getPropSpecies(UINT4 n, UINT4 row, UINT4 col) const {
   		return _species[n]._fraction->matrix[row][col];
    }

    REAL8 getLAISpecies(UINT4 n, UINT4 row, UINT4 col) const {
    	return _species[n]._LAI->matrix[row][col];
    }

    REAL8 getMaxCanopyStorage(UINT4 n, UINT4 row, UINT4 col) const {
    	Grove *spe = &_species[n]; //ACHTUNG ACHTUNG! MEMORY LEAK??!?!?!
    	return spe->MaxCanStorageParamt * spe->_LAI->matrix[row][col];
    }

    REAL8 getCanopyConductance(UINT4 n, UINT4 row, UINT4 col) const {
       	Grove *spe = &_species[n]; //ACHTUNG ACHTUNG! MEMORY LEAK??!?!?!
       	return spe->_CanopyConductance->matrix[row][col];
    }
    REAL8 getTreeHeight(UINT4 n, UINT4 row, UINT4 col) const {
          	Grove *spe = &_species[n]; //ACHTUNG ACHTUNG! MEMORY LEAK??!?!?!
          	return spe->_Height->matrix[row][col];
    }

    REAL8 getCanopyTemp(UINT4 n, UINT4 row, UINT4 col) const {
           	Grove *spe = &_species[n]; //ACHTUNG ACHTUNG! MEMORY LEAK??!?!?!
           	return spe->_Temp_c->matrix[row][col];
    }
    REAL8 getCanopyNetRad(UINT4 n, UINT4 row, UINT4 col) const {
           	Grove *spe = &_species[n]; //ACHTUNG ACHTUNG! MEMORY LEAK??!?!?!
           	return spe->_NetR_Can->matrix[row][col];
    }

    REAL8 getCanopyLatHeat(UINT4 n, UINT4 row, UINT4 col) const {
           	Grove *spe = &_species[n]; //ACHTUNG ACHTUNG! MEMORY LEAK??!?!?!
           	return spe->_LatHeat_Can->matrix[row][col];
    }

    REAL8 getCanopySensHeat(UINT4 n, UINT4 row, UINT4 col) const {
          	Grove *spe = &_species[n]; //ACHTUNG ACHTUNG! MEMORY LEAK??!?!?!
          	return spe->_SensHeat_Can->matrix[row][col];
    }

    REAL8 getIntercWater(UINT4 n, UINT4 row, UINT4 col) const {
           	Grove *spe = &_species[n]; //ACHTUNG ACHTUNG! MEMORY LEAK??!?!?!
           	return spe->_WaterStorage->matrix[row][col];
    }

    REAL8 getBeersCoeff(UINT4 n, UINT4 row, UINT4 col) const {
			return _species[n].KBeers;
    }

    REAL8 getCanopyEmissivity(UINT4 n, UINT4 row, UINT4 col) const {
        	return _species[n].emissivity;
    }

    REAL8 getEvapoTransp(UINT4 n, UINT4 row, UINT4 col) const {
    	return _species[n]._ET->matrix[row][col];
    }

    REAL8 getTranspiration(UINT4 n, UINT4 row, UINT4 col) const {
       	return _species[n]._Transpiration->matrix[row][col];
    }


    grid *getLAISpeciesMap(UINT4 n) const {
    		return _species[n]._LAI;
    }

    grid *getPropSpeciesMap(UINT4 n) const {
        	return _species[n]._fraction;
    }

    grid *getStemDensSpeciesMap(UINT4 n) const {
           	return _species[n]._StemDensity;
    }

    grid *getAgeSpeciesMap(UINT4 n) const {
           	return _species[n]._AGE;
    }

    grid *getCanopyConductSpeciesMap(UINT4 n) const {
          	return _species[n]._CanopyConductance;
    }

    grid *getGPPSpeciesMap(UINT4 n) const {
           	return _species[n]._GPP;
    }

    grid *getNPPSpeciesMap(UINT4 n) const {
           	return _species[n]._NPP;
    }

    grid *getBasalAreaSpeciesMap(UINT4 n) const {
           	return _species[n]._BasalArea;
    }

    grid *getTreeHeightSpeciesMap(UINT4 n) const {
           	return _species[n]._Height;
    }

    grid *getRootMassSpeciesMap(UINT4 n) const {
           	return _species[n]._RootMass;
    }

    grid *getCanopyTempSpeciesMap(UINT4 n) const {
           	return _species[n]._Temp_c;
    }

    grid *getCanopyNetRadSpeciesMap(UINT4 n) const {
           	return _species[n]._NetR_Can;
    }

    grid *getCanopyLatHeatSpeciesMap(UINT4 n) const {
           	return _species[n]._LatHeat_Can;
    }

    grid *getCanopySensHeatSpeciesMap(UINT4 n) const {
           	return _species[n]._SensHeat_Can;
    }

    grid *getCanopyWaterStorSpeciesMap(UINT4 n) const {
           	return _species[n]._WaterStorage;
    }

    grid *getTranspirationSpeciesMap(UINT4 n) const {
       	return _species[n]._Transpiration;
    }

  /*  //setters
    void setEvapoTransp(REAL8 ET, UINT4 n, UINT4 row, UINT4 col){
    	_species[n]._ET->matrix[row][col] = ET;
    }*/
};

#endif /* FOREST_H_ */
