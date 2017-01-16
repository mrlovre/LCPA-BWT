################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Alphabet.cpp \
../src/BWTree.cpp \
../src/algorithms.cpp \
../src/main.cpp 

C_SRCS += \
../src/divsufsort.c 

OBJS += \
./src/Alphabet.o \
./src/BWTree.o \
./src/algorithms.o \
./src/divsufsort.o \
./src/main.o 

CPP_DEPS += \
./src/Alphabet.d \
./src/BWTree.d \
./src/algorithms.d \
./src/main.d 

C_DEPS += \
./src/divsufsort.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


