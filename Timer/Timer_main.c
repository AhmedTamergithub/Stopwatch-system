/*
 * Timer_main.c
 *
 *  Created on: Aug 9, 2024
 *      Author: Ahmed
 */

#include "BIT_Calc.h"
#include "STD_Types.h"
#include "Timer_interface.h"
#include "GIE_interface.h"
#include "GPIO_interface.h"
#include  <util/delay.h>
/*
void PWM(void);
*/
void main(void){

DIO_u8SetPinDirection(DIO_u8PORTB,DIO_u8PIN3 ,DIO_u8PIN_OUTPUT);


TIMER0_voidInit();

u8 counter;
/*
GIE_voidEnable();
TIMER0_u8SetCallBack(&PWM);
*/
	while(1){
		counter=0;

 for(counter=0;counter<256;counter++)
 {
	 Timer0_voidSetCompareMatchValue(counter);
	_delay_ms(10);
	if(counter==255){
		for(counter=255;counter>0;counter--)
		  {
		 	 Timer0_voidSetCompareMatchValue(counter);
		 	_delay_ms(10);

		 	}
	}

	}





}
}
/*
void PWM(void){
	static  u16 Local_u16counter=0; //so it isn't overwritted when the function is called again
	Local_u16counter++;

	if(Local_u16counter==99)
		//Setpin High for 5 ms
		Local_u16counter=0;

	}

	else if(Local_u16counter==12){
			//et Pin High for 10 ms
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN1,  DIO_u8PIN_LOW);

		}
	else if(Local_u16counter==15){
				//set pin High with 15 ms
				DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2,  DIO_u8PIN_LOW);

			}


	else if(Local_u16counter==20){
		//set pin low with remaining time
		DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0,  DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN1,  DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2,  DIO_u8PIN_HIGH);
		Local_u16counter=0;
	}

}
*/
