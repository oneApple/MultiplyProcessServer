################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/commonfunction/localSocketFun.cpp \
../src/commonfunction/netSocketFun.cpp \
../src/commonfunction/signalHandleFun.cpp 

OBJS += \
./src/commonfunction/localSocketFun.o \
./src/commonfunction/netSocketFun.o \
./src/commonfunction/signalHandleFun.o 

CPP_DEPS += \
./src/commonfunction/localSocketFun.d \
./src/commonfunction/netSocketFun.d \
./src/commonfunction/signalHandleFun.d 


# Each subdirectory must supply rules for building sources it contributes
src/commonfunction/%.o: ../src/commonfunction/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/keym/github/MultiplyProcessServer/header" -I/usr/include/c++/4.6 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


