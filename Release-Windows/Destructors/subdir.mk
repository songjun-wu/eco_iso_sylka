################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Destructors/AtmosphDesctruct.cpp \
../Destructors/BasinDestruct.cpp \
../Destructors/ForestDestruct.cpp \
../Destructors/GroveDestruct.cpp 

OBJS += \
./Destructors/AtmosphDesctruct.o \
./Destructors/BasinDestruct.o \
./Destructors/ForestDestruct.o \
./Destructors/GroveDestruct.o 

CPP_DEPS += \
./Destructors/AtmosphDesctruct.d \
./Destructors/BasinDestruct.d \
./Destructors/ForestDestruct.d \
./Destructors/GroveDestruct.d 


# Each subdirectory must supply rules for building sources it contributes
Destructors/%.o: ../Destructors/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	x86_64-w64-mingw32-g++ -DCPU_LITTLE_ENDIAN -I"/home/marco/workspace/ech2o/includes" -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


