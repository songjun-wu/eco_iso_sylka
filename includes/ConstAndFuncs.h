/*
 * PhysConst.h
 *
 *  Created on: Oct 22, 2009
 *      Author: Marco Maneta
 */

#ifndef PHYSCONST_H_
#define PHYSCONST_H_
#include<algorithm>
#include<cmath>
#include <iostream>
#include <string>

#define MAX_ITER 150
#define PI 3.14159
#define RNDOFFERR 1e-12
#define MIN_SLOPE 0.000001

const double rho_w = 1000; //density of water Kgm-3
const double Ra = 287.05; // gas constant for dry air in JKg-1C-1
const double Rv = 463; // gas constant for water vapor in JKg-1C-1
const double stefboltz = 5.67040040e-8; //stefan-Boltzmann constant in Wm-2K-4
const double spec_heat_air = 1005; // specific heat of air in Jkg-1C-1
const double spec_heat_water = 4186; // specific heat of water in Jkg-1C-1
const double spec_heat_ice = 2050; //specific heat of ice in Jkg-1C-1
const double lat_heat_vap = 2260000; //latent heat of vaporization J kg-1
const double lat_heat_fus = 334000; //latent heat of fussion J kg-1
const float vonkarman = 0.4;
const double thermal_conduct_water = 0.58;//thermal conductivity of water Wm-1C-1
const double thermal_conduct_air = 0.024; //thermal conductivity of air Wm-1C-1
const double max_snow_albedo = 0.8; //maximum albedo of snow



//Calculates density of air
extern double AirDensity(const double &T /*, const double &P*/);


/*Calculates air emissivity using Swinbank(1963) empirical formula with Air Temperature in Celsius*/
extern double AirEmissivity(const double &AirTemperature);

/*calculates the vapor pressure for a given temperature.
T in C and returns vapor pressure in kPa*/
extern double SatVaporPressure(const double &T);
extern double PsychrometricConst(const double &P); //psychrometric constant air pressure P in Pa

//Calculates soil heat capacity as the sum of the heat capacity of the fractions of soil, water and air
// returns current soil heat capacity in Joules m-3 C-1
extern double SoilHeatCapacity(const double &DrySoilHeatCap,
								const double &Porosity,
								const double &Theta,
								const double &SoilTemp);

//Calculates soil heat conductivity as the sum of the conductivity of the fractions of soil, water and air
// returns current soil heat conductivity in Wm-1C-1
extern double SoilHeatConductivity(const double &DrySoilHeatCond,
								const double &Porosity,
								const double &Theta);

/*Calculates the age efficiency factor fa needed in the calculation of GPP
 * returns dimensionless factor [0-1], MAxAge in years, Age in years*/
extern double Calculate_fa(const double &MaxAge, const double &Age);

/*Calculates the temperature efficiency factor ft needed in the calculation of GPP
 * returns dimensionless factor [0-1], Ta is current air temperature,
 * Tmax and Tmin are monthly min and max air temperatures and Topt is the optimal
 * temperature for the growth of the tree species. All temperatures in C*/
extern double Calculate_ft(const double &Ta, const double &Tmax, const double &Tmin, const double &Topt );

/*Calculates the soil water efficiency factor fw needed in the calculation of GPP
 * returns a dimensionless factor [0,1]. fgc is the calculated stomatal conductance efficiency [0-1]
 * most probably derived from the Jarvis model, Wr is the proportion of available water for trees
 * in the root zone, Wc and Wp are empirical coefficients that are soil dependent*/
extern double Calculate_fw(const double &fgc, const double &gsmax, const double &Wr, const double &Wc, const double &Wp);

/*Calculates the soil frost efficiency factor fd needed in the calculation of GPP
 * returns a dimensionless factor [0,1]. */
extern double Calculate_fd(const double &PropFrostDays);

/*Calculates the light efficiency in Jarvis' model of stomatal conductance. Solar radiation input units are irrelevant,
 *  function coefficient (dimensionless) represents the radiation value at which 0.5 light efficiency is attained*/
extern double Calculate_gs_light(const double &SolarRadiation, const double &Coeff);

/*Calculates the effect of humidity in Jarvis' model of stomatal conductance. vpd is vapor pressure deficit,
 *  function coefficient (dimensionless) is the exponential decay value with increasing vapor pressure deficit*/
extern double Calculate_gs_vpd(const double &vpd, const double &Coeff);

/*Calculates the effect of soil tension in Jarvis' model of stomatal conductance.theta is is volumetric soil moisture, fieldcap is
 * field capacity (volumetric) and wiltpnt is the wilting point (volumetric).
 * After
 * Representation of the Canopy Conductance in Modeling the Surface Energy Budget for Low Vegetation
 * R. J. Ronda, H. A. R. de Bruin, A. A. M. Holtslag
 * Journal of Applied Meteorology 2001 40:8, 1431-1444 */
extern double Calculate_gs_theta(const double &theta, const double &fieldcap, const double &wiltpnt, const double &Coeff);

extern double rlog(double u_za, double z_a, double z_d, double z_0, int option);

/*Calculates parameter beta to evalute relative humidity of soil pore space used in the calcualtion of soil vapor pressure
after Lee and Pielke, 1992 Journal of Applied Meteorology, 31(5): 480-484*/
extern double Calculate_soil_RH(const double &theta, const double &fieldcap);

#endif /* PHYSCONST_H_ */
