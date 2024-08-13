/*
 * main.c
 *
 *  Created on: Jul 23, 2024
 *      Author: Ahmed
 */

#include"STD_Types.h"
#include"BIT_Calc.h"
#include"EXTI_interface.h"
#include"GPIO_interface.h"
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void main(void){

   u8 *x=1;

   DIO_u8SetPinDirection (DIO_u8PORTB, DIO_u8PIN2, DIO_u8PIN_INPUT);
   		 	DIO_u8SetPinValue (DIO_u8PORTB, DIO_u8PIN2,DIO_u8PIN_HIGH);

   		 		EXTI_voidInt2init(falling_edge);

   		 	    GIE_voidEnable();
   		 	EXTI_u8INT2SetCallBack(&INT2_ISR);



	 while(1){


	 }
}

void INT0_ISR(void){


}

void INT1_ISR(void)
{

}

void INT2_ISR(void){

	DIO_u8SetPinDirection (DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_OUTPUT);
				    DIO_u8SetPinValue (DIO_u8PORTD, DIO_u8PIN0,DIO_u8PIN_HIGH);
}
