#include "sevensegment_interface.h"
#include "GPIO_interface.h"
#include "BIT_Calc.h"
#include "STD_Types.h"
#include "util/delay.h"

void main(void) {
	static u8 x;
	u8 i;
	static u8 counter=1;
	DIO_u8SetPortDirection(DIO_u8PORTC, DIO_u8PORT_OUTPUT);
	DIO_u8SetPortDirection(DIO_u8PORTD, DIO_u8PORT_OUTPUT);
	while (1) {
		for (i = 0; i <10 ; i++) {
			// Display on the first 7-segment display
			DIO_u8SetPinValue(DIO_u8PORTD, 0, 0);  // Enable display 1 (common line 1)
			DIO_u8SetPinValue(DIO_u8PORTD, 1, 1);  // Disable display 2 (common line 2)
			x = sevensegmentinit(i);               // Get the segment value for the digit
			DIO_u8SetPortValue(DIO_u8PORTC, x);    // Set segment values on PORTC
			_delay_ms(100);                        // Hold the value for some time
		}
		for (i = 0; i < 100; i++) {

			if(i==10||i==20||i==30||i==40||i==50||i==60||i==70||i==80||i==90){
				counter++;
			}
			DIO_u8SetPinValue(DIO_u8PORTD, 0, 1);  // Disable display 1
			DIO_u8SetPinValue(DIO_u8PORTD, 1, 0);  // Enable display 2
			x = sevensegmentinit(counter);         // Get the segment value for the next digit
			DIO_u8SetPortValue(DIO_u8PORTC, x);    // Set segment values on PORTC
			_delay_ms(100);                        // Hold the value for some time
			DIO_u8SetPinValue(DIO_u8PORTD, 0, 0);  // Enable display 1 (common line 1)
			DIO_u8SetPinValue(DIO_u8PORTD, 1, 1);  // Disable display 2 (common line 2)
			x = sevensegmentinit((i%10));          // Get the segment value for the digit
			DIO_u8SetPortValue(DIO_u8PORTC, x);    // Set segment values on PORTC
			_delay_ms(100);                        // Hold the value for some time
		}
	}
}

