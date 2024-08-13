/*
 * SPI_program.c
 *
 *  Created on: Aug 4, 2024
 *      Author: Ahmed
 */

#ifndef SPI_PROGRAM_C_
#define SPI_PROGRAM_C_

#include "BIT_Calc.h"
#include "STD_Types.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

void SPI_voidMasterInit(void){


//Set Pins direction
	/*
	MOSI--->output
	MISO--->input
	SCLK--->output
	SS----->output
    */
	/*
DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN5, DIO_u8PIN_OUTPUT );  //MOSI
DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN6, DIO_u8PIN_INPUT );   //MISO
DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN7, DIO_u8PIN_OUTPUT);   //SCLK
DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN4, DIO_u8PIN_INPUT);   //SS

*/
//Master Select
Set_Bit(SPCR,SPCR_MSTR);
//SPI Enable
Set_Bit(SPCR,SPCR_SPE);
//Set Clock to setup(send) at first rising edge (MUST ADJUST THE SAME IN BOTH MASTERS AND SLAVES)
/*
Clr_Bit(SPCR,SPCR_CPOL);
Set_Bit(SPCR,SPCR_CPHA);
*/
//set clock speed f/16
Set_Bit(SPCR,SPCR_SPR0);
Clr_Bit(SPCR,SPCR_SPR1);
Clr_Bit(SPSR,SPSR_SPI2X);


}
void SPI_voidSlaveInit(void){
	/*
		MOSI--->input
		MISO--->output
		SCLK--->input
		SS----->input
	    */
	DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN5, DIO_u8PIN_INPUT );  //MOSI
	DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN6, DIO_u8PIN_OUTPUT );   //MISO
	DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN7, DIO_u8PIN_INPUT);   //SCLK
	DIO_u8SetPinDirection (DIO_u8PORTB ,  DIO_u8PIN4, DIO_u8PIN_INPUT);   //SS

	//Slave Select
	Clr_Bit(SPCR,SPCR_MSTR);
	//SPI Enable
	Set_Bit(SPCR,SPCR_SPE);


}

u8 SPI_u8Transceive(u8 Data){


	//choose Data Order that MSB is sent firstly (The default)
	Clr_Bit(SPCR,SPCR_DORD);

	//Sending

		SPDR=Data;
		while(Get_Bit(SPSR , SPSR_SPIF) == 0);
        return SPDR;
}


#endif /* SPI_PROGRAM_C_ */
