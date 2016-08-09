################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Budgets/AccountFluxes.cpp \
../Budgets/AccountStorages.cpp \
../Budgets/MassBalanceError.cpp \
../Budgets/TotalEvaporation.cpp \
../Budgets/TotalLeakage.cpp \
../Budgets/TotalOvlndFlow.cpp \
../Budgets/TotalPrecipitation.cpp \
../Budgets/TotalStorage.cpp \
../Budgets/totalGrndFlow.cpp 

OBJS += \
./Budgets/AccountFluxes.o \
./Budgets/AccountStorages.o \
./Budgets/MassBalanceError.o \
./Budgets/TotalEvaporation.o \
./Budgets/TotalLeakage.o \
./Budgets/TotalOvlndFlow.o \
./Budgets/TotalPrecipitation.o \
./Budgets/TotalStorage.o \
./Budgets/totalGrndFlow.o 

CPP_DEPS += \
./Budgets/AccountFluxes.d \
./Budgets/AccountStorages.d \
./Budgets/MassBalanceError.d \
./Budgets/TotalEvaporation.d \
./Budgets/TotalLeakage.d \
./Budgets/TotalOvlndFlow.d \
./Budgets/TotalPrecipitation.d \
./Budgets/TotalStorage.d \
./Budgets/totalGrndFlow.d 


# Each subdirectory must supply rules for building sources it contributes
Budgets/%.o: ../Budgets/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DCPU_LITTLE_ENDIAN -I"/home/marco/workspace/ech2o/includes" -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


