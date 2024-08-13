/*
 * Timer_main.c
 *
 * Created on: Aug 13, 2024
 * Author: Ahmed
 */

#include "BIT_Calc.h"
#include "STD_Types.h"
#include "Timer0_interface.h"
#include "GIE_interface.h"
#include "GPIO_interface.h"
#include <util/delay.h>
#include "sevensegment_interface.h"

void SSD(void);

void main(void) {
    DIO_u8SetPortDirection(DIO_u8PORTC, DIO_u8PORT_OUTPUT); // Data lines to the 7-segment display
    DIO_u8SetPortDirection(DIO_u8PORTD, DIO_u8PORT_OUTPUT); // Control lines if needed (e.g., for enabling the display)
 DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_LOW);
    TIMER0_voidInit();
    GIE_voidEnable();
    Timer0_voidSetCompareMatchValue(250);
    sevensegmentinit(1);
    _delay_ms(1000);
    sevensegmentinit(2);
    TIMER0_u8SetCallBack(&SSD);

    while(1) {
        // Main loop remains empty; all work is done in the interrupt service routine
    }
}

void SSD(void) {
    static u8 Local_u8Digit = 0; // Counter for the displayed digit
    static  u16 Local_u16counter=0; //Compare Match Event Counter
    	Local_u16counter++;
if(Local_u16counter==4){
	for(int i=0;i<10;i++){
    // Update the 7-segment display
    DIO_u8SetPortValue(DIO_u8PORTC, sevensegmentinit(i)); // Display the current digit
    _delay_ms(1000);

	}

}
    // Increment digit for next display
   // Local_u8Digit++;
    //if (Local_u8Digit >= 10) {
      //  Local_u8Digit = 0; // Reset to 0 after displaying 9
    }

