/*
 * UART_main.c
 *
 *  Created on: Aug 3, 2024
 *      Author: Ahmed
 */

#include "BIT_Calc.h"
#include "STD_Types.h"
#include "UART_interface.h"
#include "GPIO_interface.h"
#include <util/delay.h>
void main(void){
	u8 Local_u8Data;
u8 entry;
	//Set Rx as input
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_INPUT);
    //Set Tx as output
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN1,DIO_u8PIN_OUTPUT);


	//Set Led as output on port A
	DIO_u8SetPortDirection(DIO_u8PORTA,DIO_u8PORT_OUTPUT);

	UART_init();

	while(1){

		entry=UART_voidreceive();
     if(entry=='1')
     {
    	 DIO_u8SetPortValue(DIO_u8PORTA,DIO_u8PORT_HIGH);

	}
     else if(entry=='2'){
    	 DIO_u8SetPortValue(DIO_u8PORTA,DIO_u8PORT_LOW);
     }
     UART_voidsend(entry);



}
}
