################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../IO/CSF2Grid.cpp \
../IO/Grass2grid.cpp \
../IO/PCRMap2grid.cpp \
../IO/Table2grid.cpp \
../IO/WriteASCIImap.cpp \
../IO/WritePCRMap.cpp 

OBJS += \
./IO/CSF2Grid.o \
./IO/Grass2grid.o \
./IO/PCRMap2grid.o \
./IO/Table2grid.o \
./IO/WriteASCIImap.o \
./IO/WritePCRMap.o 

CPP_DEPS += \
./IO/CSF2Grid.d \
./IO/Grass2grid.d \
./IO/PCRMap2grid.d \
./IO/Table2grid.d \
./IO/WriteASCIImap.d \
./IO/WritePCRMap.d 


# Each subdirectory must supply rules for building sources it contributes
IO/%.o: ../IO/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	x86_64-w64-mingw32-g++ -DCPU_LITTLE_ENDIAN -I"/home/marco/workspace/ech2o/includes" -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

