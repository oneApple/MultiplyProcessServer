################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/messagehandle/handleReqCloseMsg.cpp \
../src/messagehandle/handleReqSendfdMsg.cpp \
../src/messagehandle/handleSendMsgMsg.cpp \
../src/messagehandle/handleSendfdMsg.cpp \
../src/messagehandle/messageHandle.cpp 

OBJS += \
./src/messagehandle/handleReqCloseMsg.o \
./src/messagehandle/handleReqSendfdMsg.o \
./src/messagehandle/handleSendMsgMsg.o \
./src/messagehandle/handleSendfdMsg.o \
./src/messagehandle/messageHandle.o 

CPP_DEPS += \
./src/messagehandle/handleReqCloseMsg.d \
./src/messagehandle/handleReqSendfdMsg.d \
./src/messagehandle/handleSendMsgMsg.d \
./src/messagehandle/handleSendfdMsg.d \
./src/messagehandle/messageHandle.d 


# Each subdirectory must supply rules for building sources it contributes
src/messagehandle/%.o: ../src/messagehandle/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/keym/github/MultiplyProcessServer/header" -I/usr/include/c++/4.6 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


