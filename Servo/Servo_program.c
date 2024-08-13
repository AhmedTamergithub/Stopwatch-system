
#include "BIT_Calc.h"
#include "STD_Types.h"
#include "Servo_config.h"
#include "Servo_private.h"
#include "Servo_interface.h"




/*
 * This is a configured program.c for a special timer app that makes a HW PWM Signal   and here are the details:
 *
 * A PWM Signal THAT rotates the servo motor
 *
 * System Freq= 8MHZ
 * PreScalar=8
 * Number of bits=16 (Timer1)
 * Tick time= 1 microsecond
 * Required Time=5 millisec
 * OverFlow Time=Period Time= 20 ms
 * Overflow Ticks=20000
 * Compare Match Value chosen= ON TIME=1 to 2 ms
 * ONTime_Ticks=1000 --> 2000
 * Duty Cycle=5% to 10%
 * No interrupts,bec it is genereated by HW
 * Non-inverted Mode(Set on Top , Clear on Compare)
 */



//Global pointer to function holding address of ISR
static void (*Timer1_pvCallBackFunc) (void)=NULL;

void TIMER1_voidInit(void){

	//Choosing Compare Output Mode for ChannelA
	Set_Bit(TCCR1A,TCCR1A_COM1A1);
	Clr_Bit(TCCR1A,TCCR1A_COM1A0);

    //Choose Waveform Generation Mode
	Set_Bit(TCCR1A,TCCR1A_WGM11);
	Clr_Bit(TCCR1A,TCCR1A_WGM10);
	Set_Bit(TCCR1B,TCCR1B_WGM12);
	Set_Bit(TCCR1B,TCCR1B_WGM13);

    // Prescalar :(Division by 8)
	Clr_Bit(TCCR1B,TCCR1B_CS12);
	Set_Bit(TCCR1B,TCCR1B_CS11);
	Clr_Bit(TCCR1B,TCCR1B_CS10);

}

void Timer1_voidSetCompareMatchValue(u16 Copy_u16Value){

		OCR1A=Copy_u16Value;
}

void Timer1_voidSetICR (u16 Copy_u16ICRValue){

	ICR1=Copy_u16ICRValue;
}
u8 TIMER1_u8SetCallBack(void (*Copy_pvCallBackFunc)(void)){

		u8 Local_u8ErrorState=0;
		if(Copy_pvCallBackFunc!=NULL){
			Timer1_pvCallBackFunc=*Copy_pvCallBackFunc;
		}
		else{
			Local_u8ErrorState=1;
		}
		return Local_u8ErrorState;
	}



void __vector_10(void) __attribute__((signal));
void __vector_10(void){
	Timer1_pvCallBackFunc(); //name of function is already pointer to function
}

