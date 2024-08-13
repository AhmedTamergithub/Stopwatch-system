

/******************************************************/
/******   AUTHOR      : Fady Maged               ******/
/******   Description : KPD Program Source File  ******/
/******   DATE        : 10 SEP 2023              ******/
/******   VERSION     : v1.0                     ******/
/******************************************************/

#include "STD_Types.h"
#include "BIT_Calc.h"

#include "GPIO_Interface.h"
#include <util/delay.h>


#include "LCD_Config.h"
#include "LCD_Interface.h"
#include "LCD_Private.h"





void LCD_voidWriteCMD(u8 A_u8CMD){

	/* RS = 0 */
	DIO_u8SetPinValue(ControlPort , RS , DIO_u8PIN_LOW);

	/* RW = 0 */
	DIO_u8SetPinValue(ControlPort , RW , DIO_u8PIN_LOW);

	/* DataPins = CMD */
	DIO_u8SetPortValue(DataPort , A_u8CMD);

	/* E = 1 */
	DIO_u8SetPinValue(ControlPort , E , DIO_u8PIN_HIGH);

	/* Delay = 1 ms */
	_delay_ms(1);

	/* E = 0 */
	DIO_u8SetPinValue(ControlPort , E , DIO_u8PIN_LOW);

	/* Delay = 1 ms */
	_delay_ms(1);
}

void LCD_voidWriteDATA(u8 A_u8DATA){

	/* RS = 1 */
	DIO_u8SetPinValue(ControlPort , RS , DIO_u8PIN_HIGH);

	/* RW = 0 */
	DIO_u8SetPinValue(ControlPort , RW , DIO_u8PIN_LOW);

	/* DataPins = CMD */
	DIO_u8SetPortValue(DataPort , A_u8DATA);

	/* E = 1 */
	DIO_u8SetPinValue(ControlPort , E , DIO_u8PIN_HIGH);

	/* Delay = 1 ms */
	_delay_ms(1);

	/* E = 0 */
	DIO_u8SetPinValue(ControlPort , E , DIO_u8PIN_LOW);

	/* Delay = 1 ms */
	_delay_ms(1);
}

void LCD_voidINIT(void){

	DIO_u8SetPinDirection(ControlPort , RS ,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(ControlPort , RW , DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(ControlPort , E , DIO_u8PIN_OUTPUT);

	DIO_u8SetPortDirection(DataPort , 255);


	_delay_ms(50);

	LCD_voidWriteCMD(CMD_FunctionSet);

	_delay_us(50);

	LCD_voidWriteCMD(CMD_DisplayONOFF);

	_delay_us(50);

	LCD_voidWriteCMD(CMD_DisplayClear);

	_delay_ms(2);

	LCD_voidWriteCMD(CMD_EntryModeSet);

	_delay_ms(2);

}

void LCD_voidGoTo(u8 A_u8YPos , u8 A_u8XPos){

	u8 L_u8AddressCounter = 0 ;

	if( (A_u8YPos < ROW1) || (A_u8YPos > ROW2)){

		/* Y-Pos Error */
	}else if ( (A_u8XPos < COL1) || (A_u8XPos > COL16)){

		/* X-Pos Error */
	}else{

		L_u8AddressCounter = A_u8XPos + (A_u8YPos * 0x40);

		Set_Bit(L_u8AddressCounter , 7);

		LCD_voidWriteCMD(L_u8AddressCounter);
	}

}

void LCD_voidWriteString(u8 A_u8YPos , u8 A_u8XPos, u8* AP_u8STRING){

	u8 L_u8AddressCounter = A_u8XPos + (A_u8YPos * 0x40);
	u8 L_u8Iterator = 0;

	LCD_voidGoTo(A_u8YPos , A_u8XPos);

	while(AP_u8STRING[L_u8Iterator] != '\0'){


		if (L_u8AddressCounter == 0x10){

			LCD_voidGoTo(ROW2 ,COL1 );

		}else if (L_u8AddressCounter == 0x50){

			LCD_voidGoTo(ROW1 ,COL1 );
		}

		LCD_voidWriteDATA(AP_u8STRING[L_u8Iterator]);
		L_u8Iterator++;
		L_u8AddressCounter++;
	}


}
