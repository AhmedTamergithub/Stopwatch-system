/*
 * ADC_main.c
 *
 *  Created on: Aug 10, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include "ADC_interface.h"
#include "GPIO_interface.h"


void main(void){
	u8 Reading;
	 DIO_u8SetPortDirection(DIO_u8PORTA,DIO_u8PORT_INPUT);
	 DIO_u8SetPortDirection(DIO_u8PORTC,DIO_u8PORT_OUTPUT);
	 ADC_voidInit();


	 while(1){
		 Reading=ADC_u8GetChannelReading(0);
		 DIO_u8SetPortValue(DIO_u8PORTC,Reading);
	 }


}
