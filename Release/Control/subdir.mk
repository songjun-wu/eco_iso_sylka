################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/GenerateConfigTemplate.cpp \
../Control/ReadConfigFile.cpp 

OBJS += \
./Control/GenerateConfigTemplate.o \
./Control/ReadConfigFile.o 

CPP_DEPS += \
./Control/GenerateConfigTemplate.d \
./Control/ReadConfigFile.d 


# Each subdirectory must supply rules for building sources it contributes
Control/%.o: ../Control/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DCPU_LITTLE_ENDIAN -I"../includes" -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

