/*
 * ICU_program.c
 *
 *  Created on: Aug 11, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include "ICU_config.h"
#include "ICU_private.h"
#include "ICU_interface.h"


/*
 * This implements an system where:
 *  Timer0=====> Generate PWM Signal with the following characteristics:
 *  FastPWM Mode,Non-inverted Mode,CompareMatchValue(64 ms),Prescalar (divide by 8),PeriodTime=256us
 *  Timer1=====> Read PWM(ICU Function)
 *  in Normal Mode
 *  EXTI
 *
 *No interrupts needed in both Timer0 or Timer1 , we will use external interrupt driver
 *
 */

//Global Pointers to hold address of ISR of INT0
void (*EXTI_pvInt0) (void)=NULL;


void TIMER0_voidInit(void){

	//Waveform Generation Mode
	Set_Bit(TCCR0,TCCR0_WGM00);
	Set_Bit(TCCR0,TCCR0_WGM01);

	//Slect Compare OutputMode (Non-inverted Mode)
	Set_Bit(TCCR0,TCCR0_COM01);
	Clr_Bit(TCCR0,TCCR0_COM00);


	// Prescalar :(Division by 8)
	Clr_Bit(TCCR0,TCCR0_CS02);
	Set_Bit(TCCR0,TCCR0_CS01);
	Clr_Bit(TCCR0,TCCR0_CS00);
	//Dutycycle=25%
	OCR0=64;

}


void TIMER1_voidInit(void){

	//set Timer1 in Normal Mode and in ChannelA
	Clr_Bit(TCCR1A,TCCR1A_COM1A1);
	Clr_Bit(TCCR1A,TCCR1A_COM1A0);

	//Set Waveform Generation Mode

	Clr_Bit(TCCR1A,TCCR1A_WGM10);
	Clr_Bit(TCCR1A,TCCR1A_WGM11);
	Clr_Bit(TCCR1B,TCCR1B_WGM12);
	Clr_Bit(TCCR1B,TCCR1B_WGM13);

	//Set Prescalar
	Clr_Bit(TCCR1B,TCCR1B_CS12);
	Set_Bit(TCCR1B,TCCR1B_CS11);
	Clr_Bit(TCCR1B,TCCR1B_CS10);


}
void Timer1_setTimerValue(u16 Copy_u16value){
	TCNT1=Copy_u16value;
}
u16  Timer1_GetTimerReading (void){
	return TCNT1;
}

void EXTI_voidInt0init(u8 Copy_u8InterruptMode) {

	switch(Copy_u8InterruptMode) {
	case low_level : {
		// Set sense control to low level
		Clr_Bit(MCUCR, MCUCR_ISC01);
		Clr_Bit(MCUCR, MCUCR_ISC00);

		// Set PIE for INT0
		Set_Bit(GICR, GICR_INT0);
		break;
	}

	case on_change: {
		// Set sense control to any logical change
		Clr_Bit(MCUCR, MCUCR_ISC01);
		Set_Bit(MCUCR, MCUCR_ISC00);

		// Set PIE for INT0
		Set_Bit(GICR, GICR_INT0);
		break;
	}

	case falling_edge: {
		// Set sense control to falling edge
		Set_Bit(MCUCR, MCUCR_ISC01);
		Clr_Bit(MCUCR, MCUCR_ISC00);

		// Set PIE for INT0
		Set_Bit(GICR, GICR_INT0);
		break;
	}

	case rising_edge: {
		// Set sense control to rising edge
		Set_Bit(MCUCR, MCUCR_ISC01);
		Set_Bit(MCUCR, MCUCR_ISC00);

		// Set PIE for INT0
		Set_Bit(GICR, GICR_INT0);
		break;
	}

	default: {
		// Handle invalid interrupt mode if necessary
		break;
	}
	}
}



void INT0_settrigger(u8 Copy_u8edge){
	if(Copy_u8edge==falling_edge){
		// Set sense control to falling edge
		Set_Bit(MCUCR, MCUCR_ISC01);
		Clr_Bit(MCUCR, MCUCR_ISC00);

		// Set PIE for INT0
		Set_Bit(GICR, GICR_INT0);
	}
	else if(Copy_u8edge==rising_edge){
		// Set sense control to rising edge
		Set_Bit(MCUCR, MCUCR_ISC01);
		Set_Bit(MCUCR, MCUCR_ISC00);

		// Set PIE for INT0
		Set_Bit(GICR, GICR_INT0);
	}

}
u8 EXTI_DisableInterrupt(u8 Copy_u8Interruptnumber){
	u8 Local_u8ErrorStatus=0;
	if(Copy_u8Interruptnumber==INT0){
		Clr_Bit(GICR, GICR_INT0);
	}
	else if(Copy_u8Interruptnumber==INT1){
		Clr_Bit(GICR, GICR_INT1);
	}
	else if(Copy_u8Interruptnumber==INT2){
		Clr_Bit(GICR, GICR_INT2);
	}
	else{
		 Local_u8ErrorStatus=1;

	}
	return Local_u8ErrorStatus;
}

u8 EXTI_u8INT0SetCallBack(void (*Copy_pvINT0Func)(void)){
	u8 Local_u8ErrorState=0;
	if(Copy_pvINT0Func!=NULL){
		EXTI_pvInt0=Copy_pvINT0Func;
	}
	else{
		Local_u8ErrorState=1;
	}
	return Local_u8ErrorState;
}




void __vector_1 (void) __attribute__((signal));
void __vector_1 (void){
	EXTI_pvInt0(); //name of function is already pointer to function
}
