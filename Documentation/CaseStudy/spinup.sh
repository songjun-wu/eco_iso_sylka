#!/bin/bash

COUNT=1
NITER=11

while [ $COUNT -lt $NITER ]
do
	echo "Running iteration ${COUNT}"
	xterm -e ech2o config.ini
	
	echo "finished run, copying files"
	cp -f ./Results/root[0]0.365 ./Spatial/root[0].map
	#cp -f ./Results/p[0]0000.365 ./Spatial/p[0].map
	cp -f ./Results/ntr[0]00.365 ./Spatial/ntr[0].map
	cp -f ./Results/lai[0]00.365 ./Spatial/lai[0].map
	#cp -f ./Results/hgt[0]00.365 ./Spatial/hgt[0].map
	#cp -f ./Results/bas[0]00.365 ./Spatial/bas[0].map
	#cp -f ./Results/age[0]00.365 ./Spatial/age[0].map

	cp -f ./Results/SWE00000.365 ./Spatial/SWE.map
	cp -f ./Results/SWC1_000.365 ./Spatial/Soil_moisture_1.map
	cp -f ./Results/SWC2_000.365 ./Spatial/Soil_moisture_2.map
	cp -f ./Results/SWC3_000.365 ./Spatial/Soil_moisture_3.map
	cp -f ./Results/Ts000000.365 ./Spatial/soiltemp.map
	cp -f ./Results/Q0000000.365 ./Spatial/streamflow.map

	cat ./Results/lai[0].tab >> ./Results/laiacum.txt
	cat ./Results/NPP[0].tab >> ./Results/NPPacum.txt
	cat ./Results/SoilMoistureAv.tab >> ./Results/SWCacum.txt


	let "COUNT++"
done
	echo "Finished simulation\n"


