################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Forest/CalculateCanopyConduct.cpp \
../Forest/CreateGrids.cpp \
../Forest/GrowForest.cpp \
../Forest/GrowGrass.cpp \
../Forest/GrowGrassLAI.cpp \
../Forest/GrowLAI.cpp \
../Forest/GrowRoots.cpp \
../Forest/GrowStem.cpp \
../Forest/GrowTrees.cpp \
../Forest/LatHeatCanopy.cpp \
../Forest/MapGetters.cpp \
../Forest/NetRadCanopy.cpp \
../Forest/SensHeatCanopy.cpp \
../Forest/SetSpeciesParameters.cpp \
../Forest/SetSpeciesStateVars.cpp \
../Forest/SetSpeciesStateVarsMaps.cpp \
../Forest/SolveCanopyEnergyBalance.cpp 

OBJS += \
./Forest/CalculateCanopyConduct.o \
./Forest/CreateGrids.o \
./Forest/GrowForest.o \
./Forest/GrowGrass.o \
./Forest/GrowGrassLAI.o \
./Forest/GrowLAI.o \
./Forest/GrowRoots.o \
./Forest/GrowStem.o \
./Forest/GrowTrees.o \
./Forest/LatHeatCanopy.o \
./Forest/MapGetters.o \
./Forest/NetRadCanopy.o \
./Forest/SensHeatCanopy.o \
./Forest/SetSpeciesParameters.o \
./Forest/SetSpeciesStateVars.o \
./Forest/SetSpeciesStateVarsMaps.o \
./Forest/SolveCanopyEnergyBalance.o 

CPP_DEPS += \
./Forest/CalculateCanopyConduct.d \
./Forest/CreateGrids.d \
./Forest/GrowForest.d \
./Forest/GrowGrass.d \
./Forest/GrowGrassLAI.d \
./Forest/GrowLAI.d \
./Forest/GrowRoots.d \
./Forest/GrowStem.d \
./Forest/GrowTrees.d \
./Forest/LatHeatCanopy.d \
./Forest/MapGetters.d \
./Forest/NetRadCanopy.d \
./Forest/SensHeatCanopy.d \
./Forest/SetSpeciesParameters.d \
./Forest/SetSpeciesStateVars.d \
./Forest/SetSpeciesStateVarsMaps.d \
./Forest/SolveCanopyEnergyBalance.d 


# Each subdirectory must supply rules for building sources it contributes
Forest/%.o: ../Forest/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	x86_64-w64-mingw32-g++ -DCPU_LITTLE_ENDIAN -I"/home/marco/workspace/ech2o/includes" -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


