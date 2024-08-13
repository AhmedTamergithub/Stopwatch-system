/*
 * WDTmain.c
 *
 *  Created on: Aug 12, 2024
 *      Author: Ahmed
 */

#include "BIT_Calc.h"
#include "STD_Types.h"
#include "GPIO_interface.h"
#include "WDT_interface.h"
#include "util/delay.h"



void main(void){

DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN0, DIO_u8PIN_OUTPUT);
DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0, DIO_u8PIN_HIGH);
_delay_ms(1000);
DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0, DIO_u8PIN_LOW);
WDT_Enable();
WDT_voidSleep(1);
//WDT_Disable();





	while(1);
}
