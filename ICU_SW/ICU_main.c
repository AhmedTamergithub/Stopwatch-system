/*
 * ICU_main.c
 *
 *  Created on: Aug 12, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include "ICU_interface.h"
#include "GPIO_interface.h"
#include "GIE_interface.h"
#include "LCD_interface.h"
#include <util/delay.h>

// Global Variables
static s32 PeriodTicks = 0;
static s32 ONTICKS = 0;

void ICU_SW(void);

void main(void) {
	DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN3, DIO_u8PIN_OUTPUT); // Generate PWM signal
	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN2, DIO_u8PIN_INPUT);  // Input triggered by PWM signal edges
	DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN2, 0);



	TIMER1_voidInit();
	TIMER0_voidInit();


	EXTI_voidInt0init(rising_edge); // Initialize INT0 with rising edge trigger
			EXTI_u8INT0SetCallBack(&ICU_SW); // Set ICU_SW as the callback for INT0
			GIE_voidEnable();
	LCD_voidInit();


	while (1) {
		while (PeriodTicks == 0 && ONTICKS == 0); // Wait until both are non-zero


		// Display PeriodTicks on the LCD
		LCD_voidSetPos(0, 0);
		LCD_voidSendString("PeriodTicks:");
		LCD_voidSendNumber(PeriodTicks);

		// Display ONTICKS on the LCD
		LCD_voidSetPos(1, 0);
		LCD_voidSendString("ONTICKS:");
		LCD_voidSendNumber(ONTICKS);
		ONTICKS=0;


	}
}

void ICU_SW(void) {
	static u8 FSM_FLAG = 0; // State machine flag, initially zero
	FSM_FLAG++;
	LCD_voidSendString("AHMED");
	if (FSM_FLAG == 1) {
		Timer1_setTimerValue(0); // Start counting the period
	}
	else if (FSM_FLAG == 2) {
		PeriodTicks = Timer1_GetTimerReading(); // Record the period duration

		INT0_settrigger(falling_edge); // Switch to falling edge detection
	}
	else if (FSM_FLAG == 3) {
		ONTICKS = Timer1_GetTimerReading();
		// Record the on-time

		ONTICKS -= PeriodTicks; // Calculate the on-duration

		EXTI_DisableInterrupt(INT0); // Disable further interrupts

	}
}
