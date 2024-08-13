/*
 * main.c
 *
 *  Created on: Aug 7, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include "EEPROM_interface.h"
#include "TWI_interface.h"
#include "GPIO_interface.h"
#include  <util/delay.h>
void main(void){
	u8 Var;
	u16 byte_accessed=0b01010101;
	DIO_u8SetPortDirection(DIO_u8PORTA, DIO_u8PORT_OUTPUT);
	while(1){
	EEPROM_sendDataByte(0,byte_accessed);
	_delay_ms(10);
	EEPROM_readDataByte(byte_accessed,&Var);
	DIO_u8SetPortValue (DIO_u8PORTA, Var );
	}
}
