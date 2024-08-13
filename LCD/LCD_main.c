/*
 * LCD_main.c
 *
 *  Created on: Aug 11, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include "LCD_interface.h"
#include <util/delay.h>
#include "GPIO_Interface.h"

int main(void) {
	DIO_u8SetPortDirection(DIO_u8PORTA, DIO_u8PORT_OUTPUT);
    // Initialize the LCD
    LCD_voidInit();

    // Clear the LCD screen
    LCD_voidClear();

    // Set position to the first line, first column
    LCD_voidSetPos(0, 0);

    // Send the string "AHMED TAMER" to the LCD
    //LCD_voidSendString("AHMED TAMER ");
    s32 number=444;
    LCD_voidSendNumber(number);
    LCD_voidSetPos(1, 0);
    LCD_voidSendString("PASSED FROM HERE");
    // Keep the string displayed
    while (1) {
        // Infinite loop to keep the string displayed
        _delay_ms(1000); // Delay to prevent excessive CPU usage
    }

    return 0;
}
