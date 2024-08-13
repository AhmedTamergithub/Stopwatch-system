/*
 * Timer0_progam.c
 *
 *  Created on: Aug 13, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include "Timer0_config.h"
#include "Timer0_private.h"
#include "Timer0_interface.h"




/*
 * This is a configured program.c for a special timer app that makes generates a timer for 7 segment  and here are the details:
 *
 *
 *
 * System Freq= 8MHZ
 * PreScalar=8
 * Number of bits=8
 * Tick time= 1 microsecond
 * Required Time=1 sec
 * OverFlow Time 1 *256 Microsecond
 * Compare Match Value chosen=250 Microsecond
 * Number of compare match events to reach 1 second =4
 * increment state of SSD
 */



//Global pointer to function holding address of ISR
static void (*Timer0_pvCallBackFunc) (void)=NULL;

void TIMER0_voidInit(void){

	//Choosing WaveForm Generation MOde to CTC
	Set_Bit(TCCR0,TCCR0_WGM01);
	Clr_Bit(TCCR0,TCCR0_WGM00);

    //Action on OCO pin
	//Clr_Bit(TCCR0,TCCR0_COM01);
	//Clr_Bit(TCCR0,TCCR0_COM00);

   //Enable Compare Match Interrupt Enable
	Set_Bit(TIMSK,TIMSK_OCIE0);




    // Prescalar :(Division by 8)
	Clr_Bit(TCCR0,TCCR0_CS02);
	Set_Bit(TCCR0,TCCR0_CS01);
	Clr_Bit(TCCR0,TCCR0_CS00);


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

