################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hw5-free.c \
../hw5-load.c \
../hw5-main.c \
../hw5-scan.c \
../hw5-search.c \
../hw8-CollinFerguson-3.c 

OBJS += \
./hw5-free.o \
./hw5-load.o \
./hw5-main.o \
./hw5-scan.o \
./hw5-search.o \
./hw8-CollinFerguson-3.o 

C_DEPS += \
./hw5-free.d \
./hw5-load.d \
./hw5-main.d \
./hw5-scan.d \
./hw5-search.d \
./hw8-CollinFerguson-3.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


