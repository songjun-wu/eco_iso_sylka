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
	@echo 'Invoking: Cross G++ Compiler'
	x86_64-w64-mingw32-g++ -DCPU_LITTLE_ENDIAN -I"/home/marco/workspace/ech2o/includes" -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


