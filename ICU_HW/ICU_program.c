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
 * This implements an ICU HW-Based system where:
 *  Timer0=====> Generate PWM Signal with the following characteristics:
 *  FastPWM Mode,Non-inverted Mode,CompareMatchValue(64 ms),Prescalar (divide by 8),PeriodTime=256us
 *  Timer1=====> Read PWM(ICU Function) in Normal Mode ,
 *  ALSO Set ICU By Hardware
 *  Enabling Interrupt of ICU
 *
 *
 *
 */

//Global Pointers to hold address of ISR of ICU
void (*pvICUFunc) (void)=NULL;


void TIMER0_voidInit(void){

	//Waveform Generation Mode
	Set_Bit(TCCR0,TCCR0_WGM00);
	Set_Bit(TCCR0,TCCR0_WGM01);

	//Select Compare OutputMode (Non-inverted Mode)
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

	//Set Prescalar to 8
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

//ICU FUNCTIONS

void ICU_voidInit(void){
	//Set Input Capture Noise Canceler
	Set_Bit(TCCR1B,TCCR1B_ICNC1);
	//Set Trigger initaially to rising edge
	Set_Bit(TCCR1B,TCCR1B_ICES1);
	//Enable Interrupt
	Set_Bit(TIMSK,TIMSK_TICIE1);

}
void ICU_SetTriggerEdge(u8 Copy_u8edge){
	if(Copy_u8edge==falling_edge){
		Clr_Bit(TCCR1B,TCCR1B_ICES1);
	}
	else if(Copy_u8edge==rising_edge){
		Set_Bit(TCCR1B,TCCR1B_ICES1);
	}
}

void ICU_EnableorDisable(u8 Copy_u8Enable){
	if(Copy_u8Enable==ENABLE){
		Set_Bit(TIMSK,TIMSK_TICIE1);


	}
	else if(Copy_u8Enable==DISABLE){
		Clr_Bit(TIMSK,TIMSK_TICIE1);
	}
}




u16 ICU_u16ReadICR1 (void){
	return ICR1;
}

u8 ICU_setCallBack(void (*Copy_pvICUFunc)(void)){

	u8 Local_u8ErrorState=0;
	if(Copy_pvICUFunc!=NULL){
		pvICUFunc=Copy_pvICUFunc;
	}
	else{
		Local_u8ErrorState=1;
	}
	return Local_u8ErrorState;
}




void __vector_6 (void) __attribute__((signal));
void __vector_6 (void){
	pvICUFunc(); //name of function is already pointer to function
}







