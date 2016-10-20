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
	if (oControl->Rep_Soil_Water_Content_Average)
		WriteMapSeries(oBasin->getSoilMoist_av(), "SWCav", oControl->current_ts_count);
	if (oControl->Rep_Soil_Water_Content_L1)
			WriteMapSeries(oBasin->getSoilMoist1(), "SWC1_", oControl->current_ts_count);
	if (oControl->Rep_Soil_Water_Content_L2)
				WriteMapSeries(oBasin->getSoilMoist2(), "SWC2_", oControl->current_ts_count);
	if (oControl->Rep_Soil_Water_Content_L3)
				WriteMapSeries(oBasin->getSoilMoist3(), "SWC3_", oControl->current_ts_count);
	if (oControl->Rep_Soil_Sat_Deficit)
		WriteMapSeries(oBasin->getSaturationDeficit(), "SatDef", oControl->current_ts_count);
	/*if (oControl->Rep_GWater)
			WriteMapSeries(oBasin->getGrndWater(), "GW", oControl->current_ts_count);*/
	if (oControl->Rep_Soil_ETP)
		WriteMapSeries(oBasin->getEvaporation(), "Evap", oControl->current_ts_count);
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

	for (int i = 0; i < oControl->NumSpecs; i++) {
		stringstream name;

		if (oControl->Rep_Veget_frac) {
			name << "p[" << i << "]";
			WriteMapSeries(oBasin->getVegetFrac(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Stem_Density) {
			name << "ntr[" << i << "]";
			WriteMapSeries(oBasin->getStemDensity(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Leaf_Area_Index) {
			name << "lai[" << i << "]";
			WriteMapSeries(oBasin->getLAI(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Stand_Age) {
			name << "age[" << i << "]";
			WriteMapSeries(oBasin->getStandAge(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_Conductance) {
			name << "gc[" << i << "]";
			WriteMapSeries(oBasin->getCanopyCond(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_GPP) {
			name << "gpp[" << i << "]";
			WriteMapSeries(oBasin->getGPP(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_NPP) {
			name << "npp[" << i << "]";
			WriteMapSeries(oBasin->getNPP(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Basal_Area) {
			name << "bas[" << i << "]";
			WriteMapSeries(oBasin->getBasalArea(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Tree_Height) {
			name << "hgt[" << i << "]";
			WriteMapSeries(oBasin->getTreeHeight(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Root_Mass) {
			name << "root[" << i << "]";
			WriteMapSeries(oBasin->getRootMass(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_Temp) {
			name << "Tc[" << i << "]";
			WriteMapSeries(oBasin->getCanopyTemp(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_NetR) {
			name << "RNc[" << i << "]";
			WriteMapSeries(oBasin->getCanopyNetRad(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_LE) {
			name << "LEc[" << i << "]";
			WriteMapSeries(oBasin->getCanopyLatHeat(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_Sens_Heat) {
			name << "Hc[" << i << "]";
			WriteMapSeries(oBasin->getCanopySensHeat(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Canopy_Water_Stor) {
			name << "Cs[" << i << "]";
			WriteMapSeries(oBasin->getCanopyWaterStor(i), name.str() , oControl->current_ts_count);
			name.str("");
		}

		if (oControl->Rep_Transpiration) {
			name << "Trp[" << i << "]";
			WriteMapSeries(oBasin->getTranspiration(i), name.str() , oControl->current_ts_count);
			name.str("");
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
	if (oControl->RepTs_Soil_Water_Content_Average){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "SoilMoistureAv.tab");
		oReport->ReportTimeSeries(oBasin->getSoilMoist_av(),
						oControl->path_ResultsFolder + "SoilMoistureAv.tab",
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
	if (oControl->RepTs_Soil_Sat_Deficit){
		if(oControl->GetTimeStep() <= oControl->report_times)
				oReport->RenameFile(oControl->path_ResultsFolder + "SoilSatDef.tab");
			oReport->ReportTimeSeries(oBasin->getSaturationDeficit(),
							oControl->path_ResultsFolder + "SoilSatDef.tab",
							oControl->current_ts_count);
	}
/*	if (oControl->RepTs_GroundWater) {
		if (oControl->current_ts_count == 1)
			oReport->RenameFile(oControl->path_ResultsFolder + "GroundWater.tab");
		oReport->ReportTimeSeries(oBasin->getSoilMoist_av(),
				oControl->path_ResultsFolder + "GroundWater.tab",
				oControl->current_ts_count);
	}*/
	if (oControl->RepTs_Soil_ETP){
		if(oControl->GetTimeStep() <= oControl->report_times)
			oReport->RenameFile(oControl->path_ResultsFolder + "Evap.tab");
		oReport->ReportTimeSeries(oBasin->getEvaporation(),
						oControl->path_ResultsFolder + "Evap.tab",
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

	for (int i = 0; i < oControl->NumSpecs; i++) {
			stringstream name;

			if (oControl->RepTs_Veget_frac) {
				name << oControl->path_ResultsFolder << "p[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getVegetFrac(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Stem_Density) {
				name << oControl->path_ResultsFolder << "num_of_tress[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getStemDensity(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Leaf_Area_Index) {
				name << oControl->path_ResultsFolder << "lai[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getLAI(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_Conductance) {
				name << oControl->path_ResultsFolder << "CanopyConduct[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopyCond(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_GPP) {
				name << oControl->path_ResultsFolder << "GPP[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getGPP(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_NPP) {
				name << oControl->path_ResultsFolder << "NPP[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getNPP(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Basal_Area) {
				name << oControl->path_ResultsFolder << "BasalArea[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getBasalArea(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Tree_Height) {
				name << oControl->path_ResultsFolder << "ThreeHeight[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getTreeHeight(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Root_Mass) {
				name << oControl->path_ResultsFolder << "RootMass[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getRootMass(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_Temp) {
				name << oControl->path_ResultsFolder << "CanopyTemp[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopyTemp(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_NetR) {
				name << oControl->path_ResultsFolder << "CanopyNetRad[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopyNetRad(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_LE) {
				name << oControl->path_ResultsFolder << "CanopyLatHeat[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopyLatHeat(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_Sens_Heat) {
				name << oControl->path_ResultsFolder << "CanopySensHeat[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopySensHeat(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Canopy_Water_Stor) {
				name << oControl->path_ResultsFolder << "CanopyWaterStor[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getCanopyWaterStor(i), name.str() , oControl->current_ts_count);
				name.str("");
			}

			if (oControl->RepTs_Transpiration) {
				name << oControl->path_ResultsFolder << "Transpiration[" << i << "].tab";
				if(oControl->GetTimeStep() <= oControl->report_times)
					oReport->RenameFile(name.str());
				oReport->ReportTimeSeries(oBasin->getTranspiration(i), name.str() , oControl->current_ts_count);
				name.str("");
			}
		}





		return EXIT_SUCCESS;
}
