################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Functions/ConstAndFuncs.cpp 

OBJS += \
./Functions/ConstAndFuncs.o 

CPP_DEPS += \
./Functions/ConstAndFuncs.d 


# Each subdirectory must supply rules for building sources it contributes
Functions/%.o: ../Functions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	x86_64-w64-mingw32-g++ -DCPU_LITTLE_ENDIAN -I"/home/marco/workspace/ech2o/includes" -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


