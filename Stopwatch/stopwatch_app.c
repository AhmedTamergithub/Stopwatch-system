/*
 *
 *  Created on: Aug 11, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include "Timer1_interface.h"
#include"GPIO_interface.h"
#include "GIE_interface.h"
#include"EXTI_interface.h"
#include"sevensegment_interface.h"
#include <util/delay.h>
// Define stopwatch states
#define RUNNING 2
#define PAUSED  1
#define RESET   0
//Global Variables
u8 stopwatch_state=RUNNING;
u16 current_state;
u8 INT2_flag=0;
u8 INT1_flag=0;
u8 INT0_flag=0;
u8 int2_state=0;





void SSD(void);
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void Resuming(void);
void main(void) {


	DIO_u8SetPortDirection(DIO_u8PORTC, DIO_u8PORT_OUTPUT); // Data lines to the 7-segment display
	DIO_u8SetPortDirection(DIO_u8PORTA, DIO_u8PORT_OUTPUT);// Enable Pins of SSD


	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);//Enable A0
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN4,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_HIGH);







	//Push Button for interrupt0 to reset SSD
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_HIGH);


	//Push Button for interrupt1 to resume countin
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN3,DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN3,DIO_u8PIN_LOW);

	//Push Button for interrupt2 to start counting again
	DIO_u8SetPinDirection(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_HIGH);

	TIMER1_voidInit();




	TIMER1_u8SetCallBack(SSD);

	GIE_voidEnable();
	EXTI_voidInt0init(falling_edge);
	EXTI_u8INT0SetCallBack(&INT0_ISR);


	EXTI_voidInt1init(rising_edge);
	EXTI_u8INT1SetCallBack(&INT1_ISR);



	EXTI_voidInt2init(falling_edge);
	EXTI_u8INT2SetCallBack(&INT2_ISR);
	//Resuming;


	while(1) {



		// Main loop remains empty; all work is done in the interrupt service routine
	}
}






void SSD(void) {
	static u16 counter = 0;
	static u8 i=0;
	static u8 second_digit = 0;
	static u8 third_digit = 0;
	static u8 fourth_digit = 0;
	static u8 fifth_digit = 0;
	static u8 sixth_digit = 0;
	counter++;

	if (stopwatch_state == RESET) {
		// Reset the digits
		DIO_u8SetPortValue(DIO_u8PORTC, 0);

		_delay_ms(1000);
		stopwatch_state = RUNNING;
		i=0;
		second_digit = 0;
		third_digit = 0;
		fourth_digit = 0;
		fifth_digit = 0;
		sixth_digit = 0;
		//_delay_ms(1000);
	}


	if (counter == 50) {
		if (stopwatch_state == RUNNING) {
			// Increment digits based on the value of digit_index
			// Update digits based on the value of i
			if ((i >= 10) && (i % 10 == 0)) second_digit++;
			if ((i >= 60) && (i % 60 == 0)) third_digit++;
			if ((i >= 960) && (i % 960 == 0)) fourth_digit++;
			if ((i >= 6000) && (i % 6000 == 0)) fifth_digit++;
			if ((i >= 96000) && (i % 96000 == 0)) sixth_digit++;



			// Multiplexing the displays

			// Display the first digit
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_HIGH);  // Enable display 1
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN1, DIO_u8PIN_LOW);   // Disable display 2
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2, DIO_u8PIN_LOW);   // Disable display 3
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN3, DIO_u8PIN_LOW);   // Disable display 4
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN4, DIO_u8PIN_LOW);   // Disable display 5
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN5, DIO_u8PIN_LOW);   // Disable display 6
			DIO_u8SetPortValue(DIO_u8PORTC, i % 10);                     // Set value for the first digit
			_delay_ms(5);                                               // Hold the value

			// Display the second digit (Maximum 5)
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_LOW);   // Disable display 1
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN1, DIO_u8PIN_HIGH);  // Enable display 2
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2, DIO_u8PIN_LOW);   // Disable display 3
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN3, DIO_u8PIN_LOW);   // Disable display 4
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN4, DIO_u8PIN_LOW);   // Disable display 5
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN5, DIO_u8PIN_LOW);   // Disable display 6
			DIO_u8SetPortValue(DIO_u8PORTC, second_digit);               // Set value for the second digit
			_delay_ms(5);                                               // Hold the value

			// Display the third digit
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_LOW);  // Enable display 1
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN1, DIO_u8PIN_LOW);   // Disable display 2
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2, DIO_u8PIN_HIGH);   // Disable display 3
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN3, DIO_u8PIN_LOW);   // Disable display 4
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN4, DIO_u8PIN_LOW);   // Disable display 5
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN5, DIO_u8PIN_LOW);   // Disable display 6
			DIO_u8SetPortValue(DIO_u8PORTC, third_digit);                     // Set value for the third digit
			_delay_ms(5);                                               // Hold the value

			// Display the fourth digit
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_LOW);  // Disable display 1
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN1, DIO_u8PIN_LOW);   // Disable display 2
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2, DIO_u8PIN_LOW);   // Disable display 3
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN3, DIO_u8PIN_HIGH);   // Enable display 4
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN4, DIO_u8PIN_LOW);   // Disable display 5
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN5, DIO_u8PIN_LOW);   // Disable display 6
			DIO_u8SetPortValue(DIO_u8PORTC, fourth_digit);                  // Set value for the fouth digit
			_delay_ms(5);                                               // Hold the value

			// Display the fifth digit
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_LOW);  // Enable display 1
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN1, DIO_u8PIN_LOW);   // Disable display 2
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2, DIO_u8PIN_LOW);   // Disable display 3
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN3, DIO_u8PIN_LOW);   // Disable display 4
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN4, DIO_u8PIN_HIGH);   // Enable display 5
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN5, DIO_u8PIN_LOW);   // Disable display 6
			DIO_u8SetPortValue(DIO_u8PORTC, fifth_digit);                     // Set value for the fifth digit
			_delay_ms(5);                                               // Hold the value

			// Display the sixth digit
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_LOW);  // Enable display 1
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN1, DIO_u8PIN_LOW);   // Disable display 2
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2, DIO_u8PIN_LOW);   // Disable display 3
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN3, DIO_u8PIN_LOW);   // Disable display 4
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN4, DIO_u8PIN_LOW);   // Disable display 5
			DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN5, DIO_u8PIN_HIGH);   // Enable display 6
			DIO_u8SetPortValue(DIO_u8PORTC, sixth_digit);                     // Set value for the sixth digit
			_delay_ms(5);                                               // Hold the value




			// Ensure digits don't overflow
			if (second_digit > 5) second_digit = 0;
			if (third_digit > 9) third_digit = 0;
			if (fourth_digit > 5) fourth_digit = 0;
			if (fifth_digit > 9) fifth_digit = 0;
			if (sixth_digit > 9) sixth_digit = 0;



			i++;

		}


		counter = 0;
	}
}

// PAUSED state doesn't change the counter


void INT0_ISR(void) {
	stopwatch_state = RESET;
	INT0_flag=1;
}

void INT1_ISR(void) {
	_delay_ms(50);//for debouncing
	if (stopwatch_state == RUNNING) {
		stopwatch_state = PAUSED;
		INT1_flag=1;
	}

}

void INT2_ISR(void) {
	_delay_ms(50);
	if (  stopwatch_state == PAUSED) {
		stopwatch_state = RUNNING;
		INT2_flag=1;
	}
}
