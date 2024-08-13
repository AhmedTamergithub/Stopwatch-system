/*
 * SPI_Master.c
 *
 *  Created on: Aug 4, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include "SPI_interface.h"
#include "GPIO_interface.h"
#include  <util/delay.h>



void main (void){
DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN5, DIO_u8PIN_OUTPUT );  //MOSI
DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN6, DIO_u8PIN_INPUT );   //MISO
DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN7, DIO_u8PIN_OUTPUT);   //SCLK
DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN4, DIO_u8PIN_INPUT);   //SS

//Internal Pull Up value=1
DIO_u8SetPinValue(DIO_u8PORTB ,  DIO_u8PIN4, DIO_u8PIN_HIGH);


SPI_voidMasterInit();
while(1){
	SPI_u8Transceive(1);
	_delay_ms(100);
}
}
