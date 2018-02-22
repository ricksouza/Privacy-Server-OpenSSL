################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Cipher.cpp \
../Cipher2.cpp \
../server2.cpp \
../systemparam.cpp 

C_SRCS += \
../server.c \
../thread.c 

OBJS += \
./Cipher.o \
./Cipher2.o \
./server.o \
./server2.o \
./systemparam.o \
./thread.o 

C_DEPS += \
./server.d \
./thread.d 

CPP_DEPS += \
./Cipher.d \
./Cipher2.d \
./server2.d \
./systemparam.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


