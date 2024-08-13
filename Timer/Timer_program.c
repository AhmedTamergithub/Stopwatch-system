/*
 * Timer_program.c
 *
 *  Created on: Aug 9, 2024
 *      Author: Ahmed
 */

#include "BIT_Calc.h"
#include "STD_Types.h"
#include "Timer_config.h"
#include "Timer_private.h"
#include "Timer_interface.h"




/*
 * This is a configured program.c for a special timer app that makes a HW PWM Signal   and here are the details:
 *
 * A PWM Signal with 5 ms high and 15 ms low
 *
 * System Freq= 8MHZ
 * PreScalar=64
 * Number of bits=8
 * Tick time= 8 microsecond
 * Required Time=5 millisec
 * OverFlow Time 8 *256 Microsecond
 * Compare Match Value chosen=64
 * Duty Cycle=25%
 * No interrupts,bec it is genereated by HW
 * Non-inverted Mode(Set on Top , Clear on Compare)
 */



//Global pointer to function holding address of ISR
static void (*Timer0_pvCallBackFunc) (void)=NULL;

void TIMER0_voidInit(void){

	//Choosing WaveForm Generation MOde
	Set_Bit(TCCR0,TCCR0_WGM01);
	Set_Bit(TCCR0,TCCR0_WGM00);

    //Action on OCO pin
	Set_Bit(TCCR0,TCCR0_COM01);
	Clr_Bit(TCCR0,TCCR0_COM00);

   //Enable Compare Match Interrupt Enable
	//Set_Bit(TIMSK,TIMSK_OCIE0);




    // Prescalar :(Division by 64)
	Clr_Bit(TCCR0,TCCR0_CS02);
	Set_Bit(TCCR0,TCCR0_CS01);
	Set_Bit(TCCR0,TCCR0_CS00);


}

void Timer0_voidSetCompareMatchValue(u8 Copy_u8Value){

		OCR0=Copy_u8Value;
}


u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void)){

		u8 Local_u8ErrorState=0;
		if(Copy_pvCallBackFunc!=NULL){
			Timer0_pvCallBackFunc=*Copy_pvCallBackFunc;
		}
		else{
			Local_u8ErrorState=1;
		}
		return Local_u8ErrorState;
	}



void __vector_10(void) __attribute__((signal));
void __vector_10(void){
	Timer0_pvCallBackFunc(); //name of function is already pointer to function
}

