/*
 * ICUHW_main.c
 *
 *  Created on: Aug 12, 2024
 *      Author: Ahmed
 */

#include "BIT_Calc.h"
#include "STD_Types.h"
#include "ICU_config.h"
#include "ICU_private.h"
#include "ICU_interface.h"
#include"GPIO_interface.h"
#include"LCD_interface.h"
#include"GIE_interface.h"
u16 PeriodTicks=0;
u16 ONTicks=0;
void ICU_HW(void);
void main(void){
	DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN3, DIO_u8PIN_OUTPUT); // Generate PWM signal on OCR0
	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN6, DIO_u8PIN_INPUT); //ICP PIN
	//DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN6,DIO_u8PIN_LOW );//To ensure Pin has floating value

	ICU_voidInit();
	ICU_setCallBack(&ICU_HW);
	TIMER1_voidInit();
	TIMER0_voidInit();
	LCD_voidInit();

	GIE_voidEnable();




	while(1){

		while (PeriodTicks == 0 && ONTicks == 0); // Wait until both are non-zero
		// Display PeriodTicks on the LCD

		LCD_voidSetPos(0, 0);
		LCD_voidSendString("PeriodTicks:");
		LCD_voidSendNumber(PeriodTicks);

		// Display ONTICKS on the LCD
		LCD_voidSetPos(1, 0);
		LCD_voidSendString("ONTICKS:");
		LCD_voidSendNumber(ONTicks);


	}
}
void ICU_HW(void){
	static u8 counter=0;
	static u16 Reading1,Reading2,Reading3;

	counter++;
	if(counter==1){
		Reading1=ICU_u16ReadICR1();
	}
	else if(counter==2){
		Reading2=ICU_u16ReadICR1();
		PeriodTicks=Reading2-Reading1;
		ICU_SetTriggerEdge(falling_edge);
	}
	else if(counter==3){
		Reading3=ICU_u16ReadICR1();
		ONTicks=Reading3-Reading2;
		ICU_EnableorDisable(DISABLE);
	}
}

