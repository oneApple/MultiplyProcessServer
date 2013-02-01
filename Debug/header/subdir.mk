################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../header/localSocketFun.cpp 

OBJS += \
./header/localSocketFun.o 

CPP_DEPS += \
./header/localSocketFun.d 


# Each subdirectory must supply rules for building sources it contributes
header/%.o: ../header/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/keym/workspace/MultiplyProcessServer/header" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


