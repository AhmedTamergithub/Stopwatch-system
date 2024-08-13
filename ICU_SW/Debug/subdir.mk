################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GIE_program.c \
../GPIO_program.c \
../ICU_main.c \
../ICU_program.c \
../LCD_program.c 

OBJS += \
./GIE_program.o \
./GPIO_program.o \
./ICU_main.o \
./ICU_program.o \
./LCD_program.o 

C_DEPS += \
./GIE_program.d \
./GPIO_program.d \
./ICU_main.d \
./ICU_program.d \
./LCD_program.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


