/*
 * Servo_main.c
 *
 *  Created on: Aug 11, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include "Servo_interface.h"
#include"GPIO_interface.h"
#include "ADC_interface.h"
#include <util/delay.h>


s32 Map(s32 InputMin,s32 InputMax,s32 OutputMin,s32 OutputMax,s32 InputValue);


void main(void){
u32 Reading;
s32 Output_Mapped;
DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN5 ,DIO_u8PIN_OUTPUT);
DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_INPUT);

TIMER1_voidInit();
ADC_voidInit();

Timer1_voidSetICR(20000);
u16 counter;
//Input is ADC Reading (0 to 255)
//Output is PWM ON TIMES (750 microsec to 2000 microsec)

//Assigning 16 bits in 8 bits;


//Timer1_voidSetCompareMatchValue(750);
	while(1){
		Reading=ADC_u8GetChannelReading(0);
		Output_Mapped=Map(0,255,750,2500,Reading);
      //for (Output_Mapped=750;Output_Mapped<2500;Output_Mapped++){
    	 Timer1_voidSetCompareMatchValue(Output_Mapped);
           _delay_ms(10);
      }


	}

s32 Map(s32 InputMin,s32 InputMax,s32 OutputMin,s32 OutputMax,s32 InputValue){
	/*
	 * OutputValue==>y
	 * InputValue==>x
	 * InputMin==>x1
	 * InputMax==>x2
	 * OutputMin==>y1
	 * OutputMax==>y2
	 *
	 *Mapping for making a relation between 2 entities and ecah entity has seperate difeerent range of values
	 */



	s32 OutputValue;

	OutputValue = ((InputValue - InputMin) * (OutputMax - OutputMin)) / (InputMax - InputMin) + OutputMin;

	return OutputValue;


}


