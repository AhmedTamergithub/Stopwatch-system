################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GIE_program.c \
../GPIO_program.c \
../Timer0_progam.c \
../main.c \
../sevensegment_program.c 

OBJS += \
./GIE_program.o \
./GPIO_program.o \
./Timer0_progam.o \
./main.o \
./sevensegment_program.o 

C_DEPS += \
./GIE_program.d \
./GPIO_program.d \
./Timer0_progam.d \
./main.d \
./sevensegment_program.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


