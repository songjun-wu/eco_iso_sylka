/*
 * Basin.h
 *
 *  Created on: Oct 9, 2009
 *      Author: Marco Maneta
 *
 */

#ifndef BASIN_H_
#define BASIN_H_

#include "Atmosphere.h"
#include "ConstAndFuncs.h"
#include "Forest.h"
#include "Grid.h"
#include "InitConf.h"
#include "SortGrid.h"

#include <errno.h>


using namespace std;
class Forest;
class Basin {

	/*Properties of the simulation*/

	UINT4 _NRows;
	UINT4 _NCols;
	REAL8 _dx;

	//DEM map, which acts as the base map setting the geometry of the basin
	grid *_DEM;

	vectCells _vSortedGrid;

	Forest *fForest;

	/*Spatial properties of the basin*/
	grid *_porosity; //volumetric
	grid *_Ksat; //saturated hydraulic conductivity in m s-1
	grid *_random_roughness; //terrain roughness to calculate aerodynamic resistance (m)
	grid *_theta_r; //residual soil moisture volumetric
	grid *_psi_ae; // soil air entry pressure in m
	grid *_BClambda; //Brooks and Corey lambda parameter
	grid *_soildepth; //soil depth m
	grid *_fieldcap; //field capacity volumetric
	grid *_paramWc; //empirical parameter in water efficiency function for GPP calculation (see Landsberg and Waring, 1997 or TRIPLEX paper)
	grid *_paramWp; ////empirical parameter in water efficiency function for GPP calculation (see Landsberg and Waring, 1997 or TRIPLEX paper)
	grid *_meltCoeff; //snowmelt coefficient m s-1 C-1
	grid *_channelmask; //mask indicating the cells with a channel. boolean
	grid *_chGWparam; //subsurface to channel water transfer parameter [dimensionless]



	grid *_ldd; //local drain direction (steepest 8 neighbor algorithm)
	grid *_catcharea; //catchment area (m2)
	grid *_slope; //slope in mm-1
	//grid *_rr; //random roughness
	//grid *_n; //manning's n

	grid *_dampdepth; // soil depth at which there is no diurnal temperature variation
	grid *_Temp_d; //temperature at damping depth

	grid *_soilmoist10cm; //average volumetric soil moisture of the first 10 cm of the soil as calculated using a hydrstatic equilibrium moisture profile
	grid *_EquivDepth2Sat; //Equivalent depth to saturation as calculated from average soil moisture and hydrstatic equilibrium (m)

	/*State variables*/

	grid *_albedo; //surface albedo, no units
	grid *_emiss_surf; //emissivity of surface, no units
	grid *_soil_dry_heatcap; //dry soil heat capacity Jm-3C-1
	grid *_soil_dry_thermcond; //dry soil thermal conductivity Wm-1C-1
	grid *_snow; //snow water equivalent in m
	grid *_ponding; // water ponding on the soil surface in m
	grid *_infilt_cap; //infilt capacity m s-1
	grid *_soilmoist; // volumetric soil moisture
	grid *_SoilWaterDepth;//soil moisture depth (m)
	grid *_SoilSatDeficit; //soil saturation deficit (1 full deficit - 0 saturation)
	grid *_psi; //soil water potential in m
	grid *_AccumInfilt; //Accumulated infiltration m
	grid *_Evaporation; //actual evaporation and transpiration in m s-1
	grid *_CanopyStorage;//current water stored in the canopy (m)
	grid *_GravityWater; //current water stored in the soil beyond field capacity (m) (percolation or water traveling in the vadose zone)
	grid *_GrndWaterOld; //water stored in the gw system at the beginning of the time step (m)
	grid *_GrndWater; //water stored in the gw system at the end of the time step (m)

	grid *_Rn; //Net radiation for the soil surface Wm-2
	grid *_latheat; //latent heat flux into the atmosphere Wm-2
	grid *_sensheat; //sensible heat into the atmosphere Wm-2
	grid *_grndheat; //ground heat flux Wm-2
	grid *_snwheat; //snow heat flux Wm-2
	grid *_Temp_s; //temperature of the surface in dg C
	grid *_Temp_s_old; //temperature of the surface in dg C in the previous time step

	grid *_Disch; //discharge out of each cell in the basin (m s-1)
	vectCells _dailyOvlndOutput; //vector containing water output for each cell with no drainage (ldd value of 5). The vectCell structure contains the row and col
								//of the cell with no output and the area draining to that cell m3s-1
	vectCells _dailyGwtrOutput; //vector containing water output for each cell with no drainage (ldd value of 5). The vectCell structure contains the row and col
								//of the cell with no output and the area draining to that cell m3s-1 ???


		vectCells SortGridLDD();

		void CheckMaps(); //check maps mainly to make sure no nodata values are in the domain. Also sets slope to MIN_SLOPE for pixels with 0 slope.

		int CalcCatchArea();
		int CalcFieldCapacity();


		double NetRad(Atmosphere &atm, const double &Ts, REAL8 Kbeers, REAL8 lai, REAL8 ec, REAL8 Tc, int row, int col);
		double LatHeat(Atmosphere &atm, double soilrelhumid, double ra, double rs, double rc, const double &Ts, int row, int col);
		double SensHeat(Atmosphere &atm,  double ra, const double &Ts, int row, int col);
		double GrndHeat(Atmosphere &atm, Control &ctrl, const double &theta, const double &Ts, const double &Td, int row,
				int col);
		double SnowHeat(Atmosphere &atm, Control &ctrl, const double &Ts, int row,
				int col);
		double MeltHeat(Atmosphere &atm, Control &ctrl, const double &Ts,const double &swe, const double &M, int row, int col);
		double RainHeat(Atmosphere &atm, double R, int row, int col);
		double SnowOutput(Atmosphere &atm, Control &ctrl, const double &meltheat, int row, int col);

		REAL8 CalcAerodynResist(REAL8 u_za, REAL8 z_a, REAL8 z_0u, REAL8 z_du, REAL8 z_0o, REAL8 z_do, REAL8 Ht, REAL8 LAI,
				REAL8 Ts, REAL8 Ta, INT4 option, bool surface);
		REAL8 CalcSoilResist(double &theta, int row, int col, UINT4 option);

		//Hydrologic processes

		void Infilt_GreenAmpt(double &f, double &F, double &theta, double &pond, double &percolat, double dt, int r, int c);
		int SolveSurfaceEnergyBalance(Atmosphere &atm,
										Control &ctrl,
										REAL8 ra,
										REAL8 rs,
										REAL8 rc,
										REAL8 Kbeers,
										REAL8 lai,
										REAL8 emis_can,
										REAL8 Temp_can,
										REAL8 &nrad,
										REAL8 &latheat,
										REAL8 &sensheat,
										REAL8 &grndheat,
										REAL8 &snowheat,
										REAL8 &meltheat,
										REAL8 &Tsold,
										REAL8 &etp,
										REAL8 &pond,
										REAL8 &theta,
										REAL8 &Ts1,
										REAL8 &Tdold,
										REAL8 p,
										UINT4 r,
										UINT4 c);

		//This functions updates soil moisture by solving the local soil water balance
		void SoilEvapotranspiration(REAL8 LE, //input latent heat
									REAL8 Ts, //input surface temperature
									REAL8 lambda, //input the latent heat (either latent heat of vaporization or of sublimation)
									REAL8 rs,// input the potential exfiltration capacity
									REAL8 &etp, //output updated evapotranspiration
									REAL8 &theta,//output updated soil moisture
									REAL8 dt, //time step
									UINT4 r,
									UINT4 c);

		REAL8 ExfiltrationCapacity(	REAL8 theta,//soil moisture
									REAL8 dt,
									UINT4 r,
									UINT4 c);

		void CalcSoilMoistureProfile(Atmosphere &atm, Control &ctrl, REAL8 theta, UINT4 row, UINT4 col);


		//This function updates _psi with the soil tension corresponding to the current soil moisture status
		void UpdateSoilWaterPotential(){
			int r, c;
			double S;
			for (unsigned int j = 0; j < _vSortedGrid.cells.size() ; j++)
			{
				r = _vSortedGrid.cells[j].row;
				c = _vSortedGrid.cells[j].col;
				S = (_soilmoist->matrix[r][c] - _theta_r->matrix[r][c])/(_porosity->matrix[r][c] - _theta_r->matrix[r][c]);

				_psi->matrix[r][c] =
				fabs(_psi_ae->matrix[r][c]) / pow(S, _BClambda->matrix[r][c]);
			}
		}



public:

	//Constructors
	Basin();
	Basin(Control &ctrl);

	//dtor
	~Basin();

	int UpdateSnowPack(Atmosphere &atm, Control &ctrl);

	int SolveCanopyFluxes(Atmosphere &atm, Control &ctrl);
	int SolveSurfaceFluxes(Atmosphere &atm, Control &ctrl);
	int CalculateGrowForest(const Atmosphere &atm, const Control &ctrl);

	int DailySurfaceRouting(Atmosphere &atm, Control &ctrl);
	int DailyGWRouting(Atmosphere &atm, Control &ctrl);

	//Getters

	REAL8 getCellSize() const {
			return _dx;
	}

	const vectCells &getSortedGrid() const {
		return _vSortedGrid;
	}

	const vectCells *getDailyOvlndOutput() const {
		return &_dailyOvlndOutput;
	}

	const vectCells *getDailyGwtrOutput() const {
			return &_dailyGwtrOutput;
	}

	grid *getNetRad() const {
		return _Rn;
	}

	grid *getLatheat() const {
		return _latheat;
	}

	grid *getSensHeat() const {
		return _sensheat;
	}

	grid *getGrndHeat() const {
		return _grndheat;
	}

	grid *getSnwHeat() const {
		return _snwheat;
	}

	grid *getSoilTemp() const {
		//return _Temp_s;
		return _Temp_d;
	}

	grid *getSkinTemp() const {
		return _Temp_s;
	}

	grid *getCanopyStorage() const {
		return _CanopyStorage;
	}
	grid *getSnowWaterEquiv() const {
		return _snow;
	}

	grid *getPondingWater() const {
		return _ponding;
	}

	grid *getSoilMoist() const {
			return _soilmoist;
	}

	grid *getSoilMoist10cm() const {
			return _soilmoist10cm;
	}

	grid *getEquivDepth2Saturation() const {
				return _EquivDepth2Sat;
	}

	grid *getSoilWaterDepth() const {

		int r, c;
			for (unsigned int j = 0; j < _vSortedGrid.cells.size() ; j++)
			{
							r = _vSortedGrid.cells[j].row;
							c = _vSortedGrid.cells[j].col;
				_SoilWaterDepth->matrix[r][c] =
					_soilmoist->matrix[r][c] * _soildepth->matrix[r][c];
			}

		return _SoilWaterDepth;
	}

	grid * getSaturationDeficit() const {

		int r, c;
		for (unsigned int j = 0; j < _vSortedGrid.cells.size(); j++) {
			r = _vSortedGrid.cells[j].row;
			c = _vSortedGrid.cells[j].col;
			_SoilSatDeficit->matrix[r][c] = 1 - ( (_soilmoist->matrix[r][c] - _theta_r->matrix[r][c]) /
					(_porosity->matrix[r][c] - _theta_r->matrix[r][c]) );
		}

		return _SoilSatDeficit;

	}

	grid *getSoilWaterPotential() const {

		return _psi;
		}
	grid *getInfiltCap() const {
			return _infilt_cap;
	}

	grid *getEvaporation() const {
		return _Evaporation;
		}

	grid *getParamWc() const {
		return _paramWc;
	}

	grid *getParamWp() const {
		return _paramWp;
	}

	grid *getPorosity() const {
		return _porosity;
	}

	grid *getFieldCapacity() const {
		return _fieldcap;
	}

	grid *getCatchmentArea() const {
		return _catcharea;
	}

	grid *getGravityWater() const {
			return _GravityWater;
		}

	grid *getGrndWater() const {
			return _GrndWater;
	}

	grid *getVegetFrac(UINT4 n) const ;

	grid *getLAI(UINT4 n) const ;

	grid *getStemDensity(UINT4 n) const ;

	grid *getStandAge(UINT4 n) const ;

	grid *getCanopyCond(UINT4 n) const ;

	grid *getGPP(UINT4 n) const ;

	grid *getNPP(UINT4 n) const ;

	grid *getBasalArea(UINT4 n) const ;

	grid *getTreeHeight(UINT4 n) const ;

	grid *getRootMass(UINT4 n) const ;

	grid *getCanopyTemp(UINT4 n) const ;

	grid *getCanopyNetRad(UINT4 n) const ;

	grid *getCanopyLatHeat(UINT4 n) const ;

	grid *getCanopySensHeat(UINT4 n) const ;

	grid *getCanopyWaterStor(UINT4 n) const ;

	grid *getTranspiration(UINT4 n) const ;



	//setters

};

#endif /* BASIN_H_ */