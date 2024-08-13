/*
 * gpio_main.c
 *
 *  Created on: Jul 15, 2024
 *      Author: Ahmed
 */


/*
 * main.c
 *
 *  Created on: Jul 15, 2024
 *      Author: Ahmed
 */

#include "GPIO_interface.h"
#include "BIT_Calc.h"
#include "STD_Types.h"
#include  <util/delay.h>
void main(void){
//DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_OUTPUT);
//DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);

DIO_u8SetPortDirection(DIO_u8PORTA,DIO_u8PORT_OUTPUT );
while(1){
DIO_u8SetPortValue(DIO_u8PORTA,DIO_u8PORT_HIGH);
_delay_us(50);
DIO_u8SetPortValue(DIO_u8PORTA,DIO_u8PORT_LOW);
_delay_us(2);
}
}
