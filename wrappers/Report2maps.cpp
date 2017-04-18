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
 *    Marco Maneta, Sylvain Kuppel
 *******************************************************************************/
/*
 * Report2maps.cpp
 *
 *  Created on: Aug 19, 2010
 *      Author: Marco.Maneta
 */

#include "Sativa.h"

int Report2Maps(){

	if(oControl->Rep_Long_Rad_Down)
		WriteMapSeries(oAtmosphere->getIncomingLongWave(), "Ldown", oControl->current_ts_count);
	if(oControl->Rep_Short_Rad_Down)
		WriteMapSeries(oAtmosphere->getIncomingShortWave(), "Sdown", oControl->current_ts_count);
	if(oControl->Rep_Precip)
		WriteMapSeries(oAtmosphere->getPrecipitation(), "Pp", oControl->current_ts_count);
	if(oControl->Rep_Rel_Humidity)
		WriteMapSeries(oAtmosphere->getRelativeHumidty(), "RH", oControl->current_ts_count);
	if(oControl->Rep_Wind_Speed)
		WriteMapSeries(oAtmosphere->getWindSpeed(), "WndSp", oControl->current_ts_count);
	if(oControl->Rep_AvgAir_Temperature)
		WriteMapSeries(oAtmosphere->getTemperature(), "Tp", oControl->current_ts_count);
	if(oControl->Rep_MinAir_Temperature)
		WriteMapSeries(oAtmosphere->getMinTemperature(), "TpMin", oControl->current_ts_count);
	if(oControl->Rep_MaxAir_Temperature)
		WriteMapSeries(oAtmosphere->getMaxTemperature(), "TpMax", oControl->current_ts_count);

	if (oControl->Rep_SWE)
		WriteMapSeries(oBasin->getSnowWaterEquiv(), "SWE", oControl->current_ts_count);
	if (oControl->Rep_Infilt_Cap)
		WriteMapSeries(oBasin->getInfiltCap(), "If", oControl->current_ts_count);
    if (oControl->Rep_Streamflow)
    	WriteMapSeries(oBasin->getStreamflow(), "Q", oControl->current_ts_count);
    if (oControl->Rep_Saturation_Area)
		WriteMapSeries(oBasin->getSatArea(), "SatArea_", oControl->current_ts_count);
	if (oControl->Rep_Ponding)
		WriteMapSeries(oBasin->getPondingWater(), "Ponding_", oControl->current_ts_count);
	if (oControl->Rep_Soil_Water_Content_Average)
		WriteMapSeries(oBasin->getSoilMoist_av(), "SWCav", oControl->current_ts_count);
	if (oControl->Rep_Soil_Water_Content_12)
		WriteMapSeries(oBasin->getSoilMoist_12(), "SWCup", oControl->current_ts_count);
	if (oControl->Rep_Soil_Water_Content_L1)
			WriteMapSeries(oBasin->getSoilMoist1(), "SWC1_", oControl->current_ts_count);
	if (oControl->Rep_Soil_Water_Content_L2)
				WriteMapSeries(oBasin->getSoilMoist2(), "SWC2_", oControl->current_ts_count);
	if (oControl->Rep_Soil_Water_Content_L3)
				WriteMapSeries(oBasin->getSoilMoist3(), "SWC3_", oControl->current_ts_count);
	if (oControl->Rep_WaterTableDepth)
		WriteMapSeries(oBasin->getWaterTableDepth(), "WTD_", oControl->current_ts_count);
	if (oControl->Rep_Soil_Sat_Deficit)
		WriteMapSeries(oBasin->getSaturationDeficit(), "SatDef", oControl->current_ts_count);
	if (oControl->Rep_GWater)
			WriteMapSeries(oBasin->getGrndWaterOld(), "GW", oControl->current_ts_count);
	if (oControl->Rep_Soil_ETP)
		WriteMapSeries(oBasin->getEvaporationS(), "EvapS", oControl->current_ts_count);
	if (oControl->Rep_Soil_Net_Rad)
		WriteMapSeries(oBasin->getNetRad(), "NetR", oControl->current_ts_count);
	if (oControl->Rep_Soil_LE)
		WriteMapSeries(oBasin->getLatheat(), "LE", oControl->current_ts_count);
	if (oControl->Rep_Sens_Heat)
		WriteMapSeries(oBasin->getSensHeat(), "SensH", oControl->current_ts_count);
	if (oControl->Rep_Grnd_Heat)
		WriteMapSeries(oBasin->getGrndHeat(), "GrndH", oControl->current_ts_count);
	if (oControl->Rep_Snow_Heat)
		WriteMapSeries(oBasin->getSnwHeat(), "SnowH", oControl->current_ts_count);
	if (oControl->Rep_Soil_Temperature)
		WriteMapSeries(oBasin->getSoilTemp(), "Ts", oControl->current_ts_count);
	if (oControl->Rep_Skin_Temperature)
			WriteMapSeries(oBasin->getSkinTemp(), "Tskin", oControl->current_ts_count);

	if (oControl->Rep_Total_ET)
		WriteMapSeries(oBasin->getEvaporation(), "Evap", oControl->current_ts_count);
	if (oControl->Rep_Transpiration_ToC)
		WriteMapSeries(oBasin->getTranspiration_all(), "EvapT", oControl->current_ts_count);
	if (oControl->Rep_Einterception_ToC)
		WriteMapSeries(oBasin->getEvaporationI_all(), "EvapI", oControl->current_ts_count);

	if (oControl->Rep_Net_Rad_ToC)
		WriteMapSeries(oBasin->getNetRadToC(), "NetRToC", oControl->current_ts_count);

	// Tracking maps
	if(oControl->sw_trck && oControl->sw_dD){
		if (oControl->Rep_dDprecip)
			WriteMapSeries(oAtmosphere->getdDprecip(), "dD_precip", oControl->current_ts_count);
		if (oControl->Rep_dDsnowpack)
			WriteMapSeries(oTracking->getdDsnowpack(), "dD_snowpack", oControl->current_ts_count);
		if (oControl->Rep_dDsurface)
			WriteMapSeries(oTracking->getdDsurface(), "dD_surface", oControl->current_ts_count);
		if (oControl->Rep_dDsoil1)
			WriteMapSeries(oTracking->getdDsoil1(), "dD_soilL1", oControl->current_ts_count);
		if (oControl->Rep_dDsoil2)
			WriteMapSeries(oTracking->getdDsoil2(), "dD_soilL2", oControl->current_ts_count);
		if (oControl->Rep_dDsoil3)
			WriteMapSeries(oTracking->getdDsoil3(), "dD_soilL3", oControl->current_ts_count);
		//	if (oControl->Rep_dDsoilAv)
		//			WriteMapSeries(oTracking->getdDsoilAv(), "dD_soilAv", oControl->current_ts_count);
		if (oControl->Rep_dDgroundwater)
			WriteMapSeries(oTracking->getdDgroundwater(), "dD_groundwater", oControl->current_ts_count);
		if (oControl->Rep_dDevapS)
			WriteMapSeries(oTracking->getdDevapS(), "dD_evapS", oControl->current_ts_count);
		if (oControl->Rep_dDevapI_ToC)
			WriteMapSeries(oTracking->getdDevapI_ToC(), "dD_evapI_ToC", oControl->current_ts_count);
		if (oControl->Rep_dDtranspi_ToC)
			WriteMapSeries(oTracking->getdDtranspi_ToC(), "dD_transpi_ToC", oControl->current_ts_count);

	}

	if(oControl->sw_trck && oControl->sw_d18O){
		if (oControl->Rep_d18Oprecip)
			WriteMapSeries(oAtmosphere->getd18Oprecip(), "d18O_precip", oControl->current_ts_count);
		if (oControl->Rep_d18Osnowpack)
			WriteMapSeries(oTracking->getd18Osnowpack(), "d18O_snowpack", oControl->current_ts_count);
		if (oControl->Rep_d18Osurface)
			WriteMapSeries(oTracking->getd18Osurface(), "d18O_surface", oControl->current_ts_count);
		if (oControl->Rep_d18Osoil1)
			WriteMapSeries(oTracking->getd18Osoil1(), "d18O_soilL1", oControl->current_ts_count);
		if (oControl->Rep_d18Osoil2)
			WriteMapSeries(oTracking->getd18Osoil2(), "d18O_soilL2", oControl->current_ts_count);
		if (oControl->Rep_d18Osoil3)
			WriteMapSeries(oTracking->getd18Osoil3(), "d18O_soilL3", oControl->current_ts_count);
		//	if (oControl->Rep_d18OsoilAv)
		//			WriteMapSeries(oTracking->getd18OsoilAv(), "d18O_soilAv", oControl->current_ts_count);
		if (oControl->Rep_d18Ogroundwater)
			WriteMapSeries(oTracking->getd18Ogroundwater(), "d18O_groundwater", oControl->current_ts_count);
		if (oControl->Rep_d18OevapS)
			WriteMapSeries(oTracking->getd18OevapS(), "d18O_evapS", oControl->current_ts_count);
		if (oControl->Rep_d18OevapI_ToC)
			WriteMapSeries(oTracking->getd18OevapI_ToC(), "d18O_evapI_ToC", oControl->current_ts_count);
		if (oControl->Rep_d18Otranspi_ToC)
			WriteMapSeries(oTracking->getd18Otranspi_ToC(), "d18O_transpi_ToC", oControl->current_ts_count);
	}
	if(oControl->sw_trck && oControl->sw_Age){
		if (oControl->Rep_Agesnowpack)
			WriteMapSeries(oTracking->getAgesnowpack(), "Age_snowpack", oControl->current_ts_count);
		if (oControl->Rep_Agesurface)
			WriteMapSeries(oTracking->getAgesurface(), "Age_surface", oControl->current_ts_count);
		if (oControl->Rep_Agesoil1)
			WriteMapSeries(oTracking->getAgesoil1(), "Age_soilL1", oControl->current_ts_count);
		if (oControl->Rep_Agesoil2)
			WriteMapSeries(oTracking->getAgesoil2(), "Age_soilL2", oControl->current_ts_count);
		if (oControl->Rep_Agesoil3)
			WriteMapSeries(oTracking->getAgesoil3(), "Age_soilL3", oControl->current_ts_count);
		//	if (oControl->Rep_AgesoilAv)
		//			WriteMapSeries(oTracking->getAgesoilAv(), "Age_soilAv", oControl->current_ts_count);
		if (oControl->Rep_Agegroundwater)
			WriteMapSeries(oTracking->getAgegroundwater(), "Age_groundwater", oControl->current_ts_count);
		if (oControl->Rep_AgeevapS)
			WriteMapSeries(oTracking->getAgeevapS(), "Age_evapS", oControl->current_ts_count);
		if (oControl->Rep_AgeevapI_ToC)
			WriteMapSeries(oTracking->getAgeevapI_ToC(), "Age_evapI_ToC", oControl->current_ts_count);
		if (oControl->Rep_Agetranspi_ToC)
			WriteMapSeries(oTracking->getAgetranspi_ToC(), "Age_transpi_ToC", oControl->current_ts_count);
	}

	for (int i = 0; i < oControl->NumSpecs; i++) {
		stringstream name;

		if (oControl->Rep_Veget_frac) {
			name << "p_" << i << "_";
			WriteMapSeries(oBasin->getVegetFrac(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Stem_Density) {
			name << "ntr_" << i << "_";
			WriteMapSeries(oBasin->getStemDensity(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Leaf_Area_Index) {
			name << "lai_" << i << "_";
			WriteMapSeries(oBasin->getLAI(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Stand_Age) {
			name << "age_" << i << "_";
			WriteMapSeries(oBasin->getStandAge(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_Conductance) {
			name << "gc_" << i << "_";
			WriteMapSeries(oBasin->getCanopyCond(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_GPP) {
			name << "gpp_" << i << "_";
			WriteMapSeries(oBasin->getGPP(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_NPP) {
			name << "npp_" << i << "_";
			WriteMapSeries(oBasin->getNPP(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Basal_Area) {
			name << "bas_" << i << "_";
			WriteMapSeries(oBasin->getBasalArea(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Tree_Height) {
			name << "hgt_" << i << "_";
			WriteMapSeries(oBasin->getTreeHeight(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Root_Mass) {
			name << "root_" << i << "_";
			WriteMapSeries(oBasin->getRootMass(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_Temp) {
			name << "Tc_" << i << "_";
			WriteMapSeries(oBasin->getCanopyTemp(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_NetR) {
			name << "RNc_" << i << "_";
			WriteMapSeries(oBasin->getCanopyNetRad(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_LE_E) {
			name << "LEEi_" << i << "_";
			WriteMapSeries(oBasin->getCanopyLatHeatE(i), name.str() , oControl->current_ts_count);
			name.str("");
		}
		if (oControl->Rep_Canopy_LE_T) {
			name << "LETr_" << i << "_";
			WriteMapSeries(oBasin->getCanopyLatHeatT(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_Sens_Heat) {
			name << "Hc_" << i << "_";
			WriteMapSeries(oBasin->getCanopySensHeat(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_Water_Stor) {
			name << "Cs_" << i << "_";
			WriteMapSeries(oBasin->getCanopyWaterStor(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Transpiration) {
			name << "Trp_" << i << "_";
			WriteMapSeries(oBasin->getTranspiration(i), name.str() , oControl->current_ts_count);
			name.str("");
		}
		if (oControl->Rep_Einterception) {
			name << "Eint_" << i << "_";
			WriteMapSeries(oBasin->getEinterception(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		// Tracking
		if(oControl->sw_trck){
//			if (oControl->sw_dD && oControl->Rep_dDcanopy) {
//				name << "dDCnp_" << i << "_";
//				WriteMapSeries(oBasin->getdDcanopy(i), name.str() , oControl->current_ts_count);
//				name.str("");
//			}
//
//			if (oControl->sw_d18O && oControl->Rep_d18Ocanopy) {
//				name << "d18OCnp_" << i << "_";
//				WriteMapSeries(oBasin->getd18Ocanopy(i), name.str() , oControl->current_ts_count);
//				name.str("");
//			}
//
//			if (oControl->sw_Age && oControl->Rep_Agecanopy) {
//				name << "AgeCnp_" << i << "_";
//				WriteMapSeries(oBasin->getAgecanopy(i), name.str() , oControl->current_ts_count);
//				name.str("");
//			}
			if (oControl->sw_dD && oControl->Rep_dDevapI) {
				name << "dDEvapI_" << i << "_";
				WriteMapSeries(oBasin->getdDevapI(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->sw_d18O && oControl->Rep_d18OevapI) {
				name << "d18OEvapI_" << i << "_";
				WriteMapSeries(oBasin->getd18OevapI(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->sw_Age && oControl->Rep_AgeevapI) {
				name << "AgeEvapI_" << i << "_";
				WriteMapSeries(oBasin->getAgeevapI(i), name.str() , oControl->current_ts_count);
				name.str("");
			}
			if (oControl->sw_dD && oControl->Rep_dDtranspi) {
				name << "dDTrp_" << i << "_";
				WriteMapSeries(oBasin->getdDtranspi(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->sw_d18O && oControl->Rep_d18Otranspi) {
				name << "d18OTrp_" << i << "_";
				WriteMapSeries(oBasin->getd18Otranspi(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->sw_Age && oControl->Rep_Agetranspi) {
				name << "AgeTrp_" << i << "_";
				WriteMapSeries(oBasin->getAgetranspi(i), name.str() , oControl->current_ts_count);
				name.str("");
			}
		}

	}
////////////////////////////////////////Time series output section/////////////////////////////////////////



	if(oControl->RepTs_OutletDischarge){
		if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(oControl->path_ResultsFolder + "OutletDisch.tab");
				oReport->ReportVectCells(oBasin->getDailyOvlndOutput(),
						oControl->path_ResultsFolder + "OutletDisch.tab",
						oControl->current_ts_count);
	}

	if (oControl->RepTs_Long_Rad_Down){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "Ldown.tab");
		oReport->ReportTimeSeries(oAtmosphere->getIncomingLongWave(),
				oControl->path_ResultsFolder + "Ldown.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_Short_Rad_Down){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "Sdown.tab");
		oReport->ReportTimeSeries(oAtmosphere->getIncomingShortWave(),
				oControl->path_ResultsFolder + "Sdown.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_Precip){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "Precip.tab");
		oReport->ReportTimeSeries(oAtmosphere->getPrecipitation(),
				oControl->path_ResultsFolder + "Precip.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_Rel_Humidity){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "RelHumid.tab");
		oReport->ReportTimeSeries(oAtmosphere->getRelativeHumidty(),
				oControl->path_ResultsFolder + "RelHumid.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_Wind_Speed){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "WindSpeed.tab");
		oReport->ReportTimeSeries(oAtmosphere->getWindSpeed(),
				oControl->path_ResultsFolder + "WindSpeed.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_AvgAir_Temperature){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "AvgTemp.tab");
		oReport->ReportTimeSeries(oAtmosphere->getTemperature(),
				oControl->path_ResultsFolder + "AvgTemp.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_MinAir_Temperature){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "MinTemp.tab");
		oReport->ReportTimeSeries(oAtmosphere->getMinTemperature(),
				oControl->path_ResultsFolder + "MinTemp.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_MaxAir_Temperature){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "MaxTemp.tab");
		oReport->ReportTimeSeries(oAtmosphere->getMaxTemperature(),
				oControl->path_ResultsFolder + "MaxTemp.tab",
				oControl->current_ts_count);
	}


	if (oControl->RepTs_SWE){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "SWE.tab");
		oReport->ReportTimeSeries(oBasin->getSnowWaterEquiv(),
						oControl->path_ResultsFolder + "SWE.tab",
						oControl->current_ts_count);
	}
	if (oControl->RepTs_Infilt_Cap){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "InfiltCap.tab");
		oReport->ReportTimeSeries(oBasin->getInfiltCap(),
						oControl->path_ResultsFolder + "InfiltCap.tab",
						oControl->current_ts_count);
	}
	if (oControl->RepTs_Streamflow){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "Streamflow.tab");
		oReport->ReportTimeSeries(oBasin->getStreamflow(),
						oControl->path_ResultsFolder + "Streamflow.tab",
						oControl->current_ts_count);
	}
	if (oControl->RepTs_Ponding){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "Ponding.tab");
		oReport->ReportTimeSeries(oBasin->getPondingWater(),
				oControl->path_ResultsFolder + "Ponding.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_Soil_Water_Content_Average){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "SoilMoistureAv.tab");
		oReport->ReportTimeSeries(oBasin->getSoilMoist_av(),
						oControl->path_ResultsFolder + "SoilMoistureAv.tab",
						oControl->current_ts_count);
	}
	if (oControl->RepTs_Soil_Water_Content_12){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "SoilMoistureUp.tab");
		oReport->ReportTimeSeries(oBasin->getSoilMoist_12(),
				oControl->path_ResultsFolder + "SoilMoistureUp.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_Soil_Water_Content_L1){
		if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "SoilMoistureL1.tab");
			oReport->ReportTimeSeries(oBasin->getSoilMoist1(),
							oControl->path_ResultsFolder + "SoilMoistureL1.tab",
							oControl->current_ts_count);
	}
	if (oControl->RepTs_Soil_Water_Content_L2){
		if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(oControl->path_ResultsFolder + "SoilMoistureL2.tab");
				oReport->ReportTimeSeries(oBasin->getSoilMoist2(),
								oControl->path_ResultsFolder + "SoilMoistureL2.tab",
								oControl->current_ts_count);
	}
	if (oControl->RepTs_Soil_Water_Content_L3){
		if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(oControl->path_ResultsFolder + "SoilMoistureL3.tab");
				oReport->ReportTimeSeries(oBasin->getSoilMoist3(),
								oControl->path_ResultsFolder + "SoilMoistureL3.tab",
								oControl->current_ts_count);
	}
	if (oControl->RepTs_WaterTableDepth){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "WaterTableDepth.tab");
		oReport->ReportTimeSeries(oBasin->getWaterTableDepth(),
				oControl->path_ResultsFolder + "WaterTableDepth.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_Soil_Sat_Deficit){
		if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "SoilSatDef.tab");
			oReport->ReportTimeSeries(oBasin->getSaturationDeficit(),
							oControl->path_ResultsFolder + "SoilSatDef.tab",
							oControl->current_ts_count);
	}
	if (oControl->RepTs_GroundWater) {
		if (oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "GroundWater.tab");
		oReport->ReportTimeSeries(oBasin->getGrndWaterOld(),
				oControl->path_ResultsFolder + "GroundWater.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_Soil_ETP){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "EvapS.tab");
		oReport->ReportTimeSeries(oBasin->getEvaporationS(),
						oControl->path_ResultsFolder + "EvapS.tab",
						oControl->current_ts_count);
	}
	if (oControl->RepTs_Soil_Net_Rad){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "NetRad.tab");
		oReport->ReportTimeSeries(oBasin->getNetRad(),
						oControl->path_ResultsFolder + "NetRad.tab",
						oControl->current_ts_count);
	}
	if (oControl->RepTs_Soil_LE){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "LatHeat.tab");
		oReport->ReportTimeSeries(oBasin->getLatheat(),
						oControl->path_ResultsFolder + "LatHeat.tab",
						oControl->current_ts_count);
	}
	if (oControl->RepTs_Sens_Heat){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "SensHeat.tab");
		oReport->ReportTimeSeries(oBasin->getSensHeat(),
						oControl->path_ResultsFolder + "SensHeat.tab",
						oControl->current_ts_count);
	}
	if (oControl->RepTs_Grnd_Heat){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "GrndHeat.tab");
		oReport->ReportTimeSeries(oBasin->getGrndHeat(),
						oControl->path_ResultsFolder + "GrndHeat.tab",
						oControl->current_ts_count);
	}
	if (oControl->RepTs_Snow_Heat){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "SnowHeat.tab");
		oReport->ReportTimeSeries(oBasin->getSnwHeat(),
						oControl->path_ResultsFolder + "SnowHeat.tab",
						oControl->current_ts_count);
	}
	if (oControl->RepTs_Soil_Temperature){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "SoilTemp.tab");
		oReport->ReportTimeSeries(oBasin->getSoilTemp(),
						oControl->path_ResultsFolder + "SoilTemp.tab",
						oControl->current_ts_count);
	}

	if (oControl->RepTs_Skin_Temperature){
		if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "SkinTemp.tab");
			oReport->ReportTimeSeries(oBasin->getSkinTemp(),
						oControl->path_ResultsFolder + "SkinTemp.tab",
						oControl->current_ts_count);
	}

	if (oControl->RepTs_Total_ET){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "Evap.tab");
		oReport->ReportTimeSeries(oBasin->getEvaporation(),
				oControl->path_ResultsFolder + "Evap.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_Transpiration_ToC){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "EvapT.tab");
		oReport->ReportTimeSeries(oBasin->getTranspiration_all(),
				oControl->path_ResultsFolder + "EvapT.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_Einterception_ToC){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "EvapI.tab");
		oReport->ReportTimeSeries(oBasin->getEvaporationI_all(),
				oControl->path_ResultsFolder + "EvapI.tab",
				oControl->current_ts_count);
	}
	if (oControl->RepTs_Net_Rad_ToC){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "NetRadToC.tab");
		oReport->ReportTimeSeries(oBasin->getNetRadToC(),
				oControl->path_ResultsFolder + "NetRadToC.tab",
				oControl->current_ts_count);
	}

	// Tracking
	if(oControl->sw_trck && oControl->sw_dD){
		if (oControl->RepTs_dDprecip){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "dD_precip.tab");
			oReport->ReportTimeSeries(oAtmosphere->getdDprecip(),
					oControl->path_ResultsFolder + "dD_precip.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_dDsnowpack){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "dD_snowpack.tab");
			oReport->ReportTimeSeries(oTracking->getdDsnowpack(),
					oControl->path_ResultsFolder + "dD_snowpack.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_dDsurface){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "dD_surface.tab");
			oReport->ReportTimeSeries(oTracking->getdDsurface(),
					oControl->path_ResultsFolder + "dD_surface.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_dDsoil1){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "dD_soilL1.tab");
			oReport->ReportTimeSeries(oTracking->getdDsoil1(),
					oControl->path_ResultsFolder + "dD_soilL1.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_dDsoil2){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "dD_soilL2.tab");
			oReport->ReportTimeSeries(oTracking->getdDsoil2(),
					oControl->path_ResultsFolder + "dD_soilL2.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_dDsoil3){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "dD_soilL3.tab");
			oReport->ReportTimeSeries(oTracking->getdDsoil3(),
					oControl->path_ResultsFolder + "dD_soilL3.tab",
					oControl->current_ts_count);
		}

		//	if (oControl->RepTs_dDsoilAv){
		//	  if(oControl->GetTimeStep() <= oControl->report_times)
		//	    oReport->RenameFile(oControl->path_ResultsFolder + "dD_soilAv.tab");
		//	  oReport->ReportTimeSeries(oTracking->getdDsoilAv(),
		//				    oControl->path_ResultsFolder + "dD_soilAv.tab",
		//				    oControl->current_ts_count);
		//	}

		if (oControl->RepTs_dDgroundwater){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "dD_groundwater.tab");
			oReport->ReportTimeSeries(oTracking->getdDgroundwater(),
					oControl->path_ResultsFolder + "dD_groundwater.tab",
					oControl->current_ts_count);
		}
		if (oControl->RepTs_dDevapS){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "dD_evapS.tab");
			oReport->ReportTimeSeries(oTracking->getdDevapS(),
					oControl->path_ResultsFolder + "dD_evapS.tab",
					oControl->current_ts_count);
		}
		if (oControl->RepTs_dDevapI_ToC){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "dD_evapI_ToC.tab");
			oReport->ReportTimeSeries(oTracking->getdDevapI_ToC(),
					oControl->path_ResultsFolder + "dD_evapI_ToC.tab",
					oControl->current_ts_count);
		}
		if (oControl->RepTs_dDtranspi_ToC){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "dD_transpi_ToC.tab");
			oReport->ReportTimeSeries(oTracking->getdDtranspi_ToC(),
					oControl->path_ResultsFolder + "dD_transpi_ToC.tab",
					oControl->current_ts_count);
		}
	}

	if(oControl->sw_trck && oControl->sw_d18O){
		if (oControl->RepTs_d18Oprecip){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "d18O_precip.tab");
			oReport->ReportTimeSeries(oAtmosphere->getd18Oprecip(),
					oControl->path_ResultsFolder + "d18O_precip.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_d18Osnowpack){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "d18O_snowpack.tab");
			oReport->ReportTimeSeries(oTracking->getd18Osnowpack(),
					oControl->path_ResultsFolder + "d18O_snowpack.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_d18Osurface){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "d18O_surface.tab");
			oReport->ReportTimeSeries(oTracking->getd18Osurface(),
					oControl->path_ResultsFolder + "d18O_surface.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_d18Osoil1){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "d18O_soilL1.tab");
			oReport->ReportTimeSeries(oTracking->getd18Osoil1(),
					oControl->path_ResultsFolder + "d18O_soilL1.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_d18Osoil2){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "d18O_soilL2.tab");
			oReport->ReportTimeSeries(oTracking->getd18Osoil2(),
					oControl->path_ResultsFolder + "d18O_soilL2.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_d18Osoil3){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "d18O_soilL3.tab");
			oReport->ReportTimeSeries(oTracking->getd18Osoil3(),
					oControl->path_ResultsFolder + "d18O_soilL3.tab",
					oControl->current_ts_count);
		}

		//	if (oControl->RepTs_d18OsoilAv){
		//	  if(oControl->GetTimeStep() <= oControl->report_times)
		//	    oReport->RenameFile(oControl->path_ResultsFolder + "d18O_soilAv.tab");
		//	  oReport->ReportTimeSeries(oTracking->getd18OsoilAv(),
		//				    oControl->path_ResultsFolder + "d18O_soilAv.tab",
		//				    oControl->current_ts_count);
		//	}

		if (oControl->RepTs_d18Ogroundwater){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "d18O_groundwater.tab");
			oReport->ReportTimeSeries(oTracking->getd18Ogroundwater(),
					oControl->path_ResultsFolder + "d18O_groundwater.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_d18OevapS){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "d18O_evapS.tab");
			oReport->ReportTimeSeries(oTracking->getd18OevapS(),
					oControl->path_ResultsFolder + "d18O_evapS.tab",
					oControl->current_ts_count);
		}
		if (oControl->RepTs_d18OevapI_ToC){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "d18O_evapI_ToC.tab");
			oReport->ReportTimeSeries(oTracking->getd18OevapI_ToC(),
					oControl->path_ResultsFolder + "d18O_evapI_ToC.tab",
					oControl->current_ts_count);
		}
		if (oControl->RepTs_d18Otranspi_ToC){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "d18O_transpi_ToC.tab");
			oReport->ReportTimeSeries(oTracking->getd18Otranspi_ToC(),
					oControl->path_ResultsFolder + "d18O_transpi_ToC.tab",
					oControl->current_ts_count);
		}
	}

	if(oControl->sw_trck && oControl->sw_Age){
		if (oControl->RepTs_Agesnowpack){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "Age_snowpack.tab");
			oReport->ReportTimeSeries(oTracking->getAgesnowpack(),
					oControl->path_ResultsFolder + "Age_snowpack.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_Agesurface){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "Age_surface.tab");
			oReport->ReportTimeSeries(oTracking->getAgesurface(),
					oControl->path_ResultsFolder + "Age_surface.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_Agesoil1){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "Age_soilL1.tab");
			oReport->ReportTimeSeries(oTracking->getAgesoil1(),
					oControl->path_ResultsFolder + "Age_soilL1.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_Agesoil2){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "Age_soilL2.tab");
			oReport->ReportTimeSeries(oTracking->getAgesoil2(),
					oControl->path_ResultsFolder + "Age_soilL2.tab",
					oControl->current_ts_count);
		}

		if (oControl->RepTs_Agesoil3){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "Age_soilL3.tab");
			oReport->ReportTimeSeries(oTracking->getAgesoil3(),
					oControl->path_ResultsFolder + "Age_soilL3.tab",
					oControl->current_ts_count);
		}

		//	if (oControl->RepTs_AgesoilAv){
		//	  if(oControl->GetTimeStep() <= oControl->report_times)
		//	    oReport->RenameFile(oControl->path_ResultsFolder + "Age_soilAv.tab");
		//	  oReport->ReportTimeSeries(oTracking->getAgesoilAv(),
		//				    oControl->path_ResultsFolder + "Age_soilAv.tab",
		//				    oControl->current_ts_count);
		//	}

		if (oControl->RepTs_Agegroundwater){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "Age_groundwater.tab");
			oReport->ReportTimeSeries(oTracking->getAgegroundwater(),
					oControl->path_ResultsFolder + "Age_groundwater.tab",
					oControl->current_ts_count);
		}
		if (oControl->RepTs_AgeevapS){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "Age_evapS.tab");
			oReport->ReportTimeSeries(oTracking->getAgeevapS(),
					oControl->path_ResultsFolder + "Age_evapS.tab",
					oControl->current_ts_count);
		}
		if (oControl->RepTs_AgeevapI_ToC){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "Age_evapI_ToC.tab");
			oReport->ReportTimeSeries(oTracking->getAgeevapI_ToC(),
					oControl->path_ResultsFolder + "Age_evapI_ToC.tab",
					oControl->current_ts_count);
		}
		if (oControl->RepTs_Agetranspi_ToC){
			if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "Age_transpi_ToC.tab");
			oReport->ReportTimeSeries(oTracking->getAgetranspi_ToC(),
					oControl->path_ResultsFolder + "Age_transpi_ToC.tab",
					oControl->current_ts_count);
		}
	}

	for (int i = 0; i < oControl->NumSpecs; i++) {
			stringstream name;

			if (oControl->RepTs_Veget_frac) {
				name << oControl->path_ResultsFolder << "p_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getVegetFrac(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Stem_Density) {
				name << oControl->path_ResultsFolder << "num_of_tress_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getStemDensity(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Leaf_Area_Index) {
				name << oControl->path_ResultsFolder << "lai_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getLAI(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_Conductance) {
				name << oControl->path_ResultsFolder << "CanopyConduct_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopyCond(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_GPP) {
				name << oControl->path_ResultsFolder << "GPP_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getGPP(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_NPP) {
				name << oControl->path_ResultsFolder << "NPP_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getNPP(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Basal_Area) {
				name << oControl->path_ResultsFolder << "BasalArea_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getBasalArea(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Tree_Height) {
				name << oControl->path_ResultsFolder << "ThreeHeight_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getTreeHeight(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Root_Mass) {
				name << oControl->path_ResultsFolder << "RootMass_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getRootMass(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_Temp) {
				name << oControl->path_ResultsFolder << "CanopyTemp_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopyTemp(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_NetR) {
				name << oControl->path_ResultsFolder << "CanopyNetRad_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopyNetRad(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_LE_E) {
				name << oControl->path_ResultsFolder << "CanopyLatHeatEi_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopyLatHeatE(i), name.str() , oControl->current_ts_count);
				name.str("");
			}
			if (oControl->RepTs_Canopy_LE_T) {
				name << oControl->path_ResultsFolder << "CanopyLatHeatTr_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopyLatHeatT(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_Sens_Heat) {
				name << oControl->path_ResultsFolder << "CanopySensHeat_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopySensHeat(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_Water_Stor) {
				name << oControl->path_ResultsFolder << "CanopyWaterStor_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopyWaterStor(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Transpiration) {
				name << oControl->path_ResultsFolder << "Transpiration_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getTranspiration(i), name.str() , oControl->current_ts_count);
				name.str("");
			}
			if (oControl->RepTs_Einterception) {
				name << oControl->path_ResultsFolder << "Einterception_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getEinterception(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

		// Tracking
			if(oControl->sw_trck){
			//			if (oControl->sw_dD && oControl->RepTs_dDcanopy) {
			//				name << oControl->path_ResultsFolder << "dDcanopy_" << i << ".tab";
			//				if(oControl->GetTimeStep() <= oControl->report_times)
			//					oReport->RenameFile(name.str());
			//				oReport->ReportTimeSeries(oBasin->getdDcanopy(i), name.str() , oControl->current_ts_count);
			//				name.str("");
			//			}
			//
			//			if (oControl->sw_d18O && oControl->RepTs_d18Ocanopy) {
			//				name << oControl->path_ResultsFolder << "d18Ocanopy_" << i << ".tab";
			//				if(oControl->GetTimeStep() <= oControl->report_times)
			//					oReport->RenameFile(name.str());
			//				oReport->ReportTimeSeries(oBasin->getd18Ocanopy(i), name.str() , oControl->current_ts_count);
			//				name.str("");
			//			}
			//
			//			if (oControl->sw_Age && oControl->RepTs_Agecanopy) {
			//				name << oControl->path_ResultsFolder << "Agecanopy_" << i << ".tab";
			//				if(oControl->GetTimeStep() <= oControl->report_times)
			//					oReport->RenameFile(name.str());
			//				oReport->ReportTimeSeries(oBasin->getAgecanopy(i), name.str() , oControl->current_ts_count);
			//				name.str("");
			//			}
				if (oControl->sw_dD && oControl->RepTs_dDevapI) {
					name << oControl->path_ResultsFolder << "dDevapI_" << i << ".tab";
					if(oControl->GetTimeStep() <= oControl->report_times)
						oReport->RenameFile(name.str());
					oReport->ReportTimeSeries(oBasin->getdDevapI(i), name.str() , oControl->current_ts_count);
					name.str("");
				}

				if (oControl->sw_d18O && oControl->RepTs_d18OevapI) {
					name << oControl->path_ResultsFolder << "d18OevapI_" << i << ".tab";
					if(oControl->GetTimeStep() <= oControl->report_times)
						oReport->RenameFile(name.str());
					oReport->ReportTimeSeries(oBasin->getd18OevapI(i), name.str() , oControl->current_ts_count);
					name.str("");
				}

				if (oControl->sw_Age && oControl->RepTs_AgeevapI) {
					name << oControl->path_ResultsFolder << "AgeevapI_" << i << ".tab";
					if(oControl->GetTimeStep() <= oControl->report_times)
						oReport->RenameFile(name.str());
					oReport->ReportTimeSeries(oBasin->getAgeevapI(i), name.str() , oControl->current_ts_count);
					name.str("");
				}
				if (oControl->sw_dD && oControl->RepTs_dDtranspi) {
					name << oControl->path_ResultsFolder << "dDtranspi_" << i << ".tab";
					if(oControl->GetTimeStep() <= oControl->report_times)
						oReport->RenameFile(name.str());
					oReport->ReportTimeSeries(oBasin->getdDtranspi(i), name.str() , oControl->current_ts_count);
					name.str("");
				}

				if (oControl->sw_d18O && oControl->RepTs_d18Otranspi) {
					name << oControl->path_ResultsFolder << "d18Otranspi_" << i << ".tab";
					if(oControl->GetTimeStep() <= oControl->report_times)
						oReport->RenameFile(name.str());
					oReport->ReportTimeSeries(oBasin->getd18Otranspi(i), name.str() , oControl->current_ts_count);
					name.str("");
				}

				if (oControl->sw_Age && oControl->RepTs_Agetranspi) {
					name << oControl->path_ResultsFolder << "Agetranspi_" << i << ".tab";
					if(oControl->GetTimeStep() <= oControl->report_times)
						oReport->RenameFile(name.str());
					oReport->ReportTimeSeries(oBasin->getAgetranspi(i), name.str() , oControl->current_ts_count);
					name.str("");
				}
			}
		}

		/*			if (oControl->RepTs_dDcanopy) {
				name << oControl->path_ResultsFolder << "dDcanopy_" << i << ".tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oTracking->getdDcanopy(i), name.str() , oControl->current_ts_count);
				name.str("");*/

		return EXIT_SUCCESS;
}
