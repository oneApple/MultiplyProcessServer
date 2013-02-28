################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/childProcess.cpp \
../src/handleEpollSocket.cpp \
../src/parentProcess.cpp \
../src/processManage.cpp 

OBJS += \
./src/childProcess.o \
./src/handleEpollSocket.o \
./src/parentProcess.o \
./src/processManage.o 

CPP_DEPS += \
./src/childProcess.d \
./src/handleEpollSocket.d \
./src/parentProcess.d \
./src/processManage.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/keym/github/MultiplyProcessServer/header" -I/usr/include/c++/4.6 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


