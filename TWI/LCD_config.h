

/******************************************************/
/******   AUTHOR      : Fady Maged               ******/
/******   Description : KPD Configuration File   ******/
/******   DATE        : 10 SEP 2023              ******/
/******   VERSION     : v1.0                     ******/
/******************************************************/


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_



/*********************************************/
/*            Control Port Selection         */
/* Options : PORTA, PORTB, PORTC, PORTD      */
/*********************************************/
#define ControlPort      DIO_u8PORTA


/************************************************************/
/*                Control Pins Selection                    */
/* Options : PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7 */
/************************************************************/
#define RS      DIO_u8PIN0
#define RW 		DIO_u8PIN1
#define E		DIO_u8PIN2


/********************************************/
/*          Data Port Selection             */
/* Options : PORTA, PORTB, PORTC, PORTD     */
/********************************************/
#define DataPort     DIO_u8PORTA



/************************************************************/
/*                   COLs Pins Selection                    */
/* Options : PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7 */
/************************************************************/




#endif /* LCD_CONFIG_H_ */
