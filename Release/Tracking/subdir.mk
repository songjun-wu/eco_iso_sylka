################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Tracking/CheckMapsTrck.cpp \
../Tracking/IncrementAge.cpp

OBJS += \
./Tracking/CheckMapsTrck.o\
./Tracking/IncrementAge.o

CPP_DEPS += \
./Tracking/CheckMapsTrck.d \
./Tracking/IncrementAge.d 

# Each subdirectory must supply rules for building sources it contributes
Tracking/%.o: ../Tracking/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DCPU_LITTLE_ENDIAN -I"../includes" -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


