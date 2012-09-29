/*
 * CalculateCanopyConduct.cpp
 *
 *  Created on: Jun 23, 2010
 *      Author: Marco.Maneta
 */

#include "Forest.h"

int Forest::CalculateCanopyConduct(Basin &bas, const Atmosphere &atm, const Control &ctrl, UINT4 j, UINT4 r, UINT4 c){

		REAL8 sw_rad;
		REAL8 gsmax;
		REAL8 f_light_coeff, f_vpd_coeff, f_theta_coeff;
		REAL8 lai;
		REAL8 airTemp, optTemp, maxTemp, minTemp;
		REAL8 es, ea, vpd;
		REAL8 theta, fc, wp;
		REAL8 f_light, f_temp, f_vpd, f_theta;
		REAL8 shelter_factor;
		REAL8 gs;
		REAL8 gsmin = 0.00000000000001; //arbitrary number to set as minimum canopy conductance so its inverse (resistance) doesn't explode when divided by zero conductance

		shelter_factor = .8; //account to the shading effect of leaves

			    	sw_rad = atm.getIncomingShortWave()->matrix[r][c];
			    	gsmax = _species[j].gsmax;
			    	lai = _species[j]._LAI->matrix[r][c];
			    	airTemp = atm.getTemperature()->matrix[r][c];
			    	optTemp = _species[j].TempOpt;
			    	maxTemp = _species[j].TempMax;
			    	minTemp = _species[j].TempMin;

			    	f_light_coeff = _species[j].gs_light_coeff;

			    	f_vpd_coeff = _species[j].gs_vpd_coeff;
			    	es = SatVaporPressure(airTemp);//todo urgent: calculate vapor pressure deficit with respect to soil
			    	ea = es * atm.getRelativeHumidty()->matrix[r][c];
			    	vpd = es - ea;

			    	f_theta_coeff = _species[j].gs_theta_coeff;
			    	theta = bas.getSoilMoist()->matrix[r][c]; //TODO: include here total soil moisture
			    	fc = bas.getFieldCapacity()->matrix[r][c];
			    	wp = _species[j].WiltingPoint;


					f_light = Calculate_gs_light(sw_rad, f_light_coeff); //TODO: implement light extinction factor when other species in the same cell is taller and has large LAI
					f_temp = Calculate_ft(airTemp, maxTemp, minTemp, optTemp);
			    	f_vpd = Calculate_gs_vpd(vpd, f_vpd_coeff);
			    	f_theta = Calculate_gs_theta(theta, fc, wp, f_theta_coeff);

			    	gs = gsmax * lai * shelter_factor * f_light * f_temp * f_vpd * f_theta;

			    	_species[j]._CanopyConductance->matrix[r][c] = gs < gsmin ? gsmin :
			    		gsmax * lai * shelter_factor * f_light * f_temp * f_vpd * f_theta;


	return EXIT_SUCCESS;
}
