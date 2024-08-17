/*
 * EXTI_program.c
 *
 *  Created on: Jul 23, 2024
 *      Author: Ahmed
 */
/****************************************************************/
/****************************************************************/
/*****************   Author: Ahmed Tamer   **********************/
/*****************    Layer: MCAL          **********************/
/*****************    Driver:EXTI           **********************/
/*****************   Version 1.0.0         **********************/
/****************************************************************/
/****************************************************************/

#include "BIT_Calc.h"
#include "STD_Types.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

//Global Pointers to hold address of ISR of INT0
void (*EXTI_pvInt0) (void)=NULL;
void (*EXTI_pvInt1) (void)=NULL;
void (*EXTI_pvInt2) (void)=NULL;
/*
void GIE_voidEnable(void){
	Set_Bit(SREG,SREG_I);
}
void GIE_voidDisable(void){
	Clr_Bit(SREG,SREG_I);
}
*/
void EXTI_voidInt0init(u8 Copy_u8InterruptMode) {

	switch(Copy_u8InterruptMode) {
	case low_level : {
		// Set sense control to low level
		Clr_Bit(MCUCR, MCUCR_ISC01);
		Clr_Bit(MCUCR, MCUCR_ISC00);

		// Set PIE for INT0
		Set_Bit(GICR, GICR_INT0);
		break;
	}

	case on_change: {
		// Set sense control to any logical change
		Clr_Bit(MCUCR, MCUCR_ISC01);
		Set_Bit(MCUCR, MCUCR_ISC00);

		// Set PIE for INT0
		Set_Bit(GICR, GICR_INT0);
		break;
	}

	case falling_edge: {
		// Set sense control to falling edge
		Set_Bit(MCUCR, MCUCR_ISC01);
		Clr_Bit(MCUCR, MCUCR_ISC00);

		// Set PIE for INT0
		Set_Bit(GICR, GICR_INT0);
		break;
	}

	case rising_edge: {
		// Set sense control to rising edge
		Set_Bit(MCUCR, MCUCR_ISC01);
		Set_Bit(MCUCR, MCUCR_ISC00);

		// Set PIE for INT0
		Set_Bit(GICR, GICR_INT0);
		break;
	}

	default: {
		// Handle invalid interrupt mode if necessary
		break;
	}
	}
}


void EXTI_voidInt1init(u8 Copy_u8InterruptMode){
	switch(Copy_u8InterruptMode) {
		case low_level : {
			// Set sense control to low level
			Clr_Bit(MCUCR, MCUCR_ISC10);
			Clr_Bit(MCUCR, MCUCR_ISC11);

			// Set PIE for INT1
			Set_Bit(GICR, GICR_INT1);
			break;
		}

		case on_change: {
			// Set sense control to any logical change
			Clr_Bit(MCUCR, MCUCR_ISC11);
			Set_Bit(MCUCR, MCUCR_ISC10);

			// Set PIE for INT1
			Set_Bit(GICR, GICR_INT1);
			break;
		}

		case falling_edge: {
			// Set sense control to falling edge
			Set_Bit(MCUCR, MCUCR_ISC11);
			Clr_Bit(MCUCR, MCUCR_ISC10);

			// Set PIE for INT1
			Set_Bit(GICR, GICR_INT1);
			break;
		}

		case rising_edge: {
			// Set sense control to rising edge
			Set_Bit(MCUCR, MCUCR_ISC11);
			Set_Bit(MCUCR, MCUCR_ISC10);

			// Set PIE for INT1
			Set_Bit(GICR, GICR_INT1);
			break;
		}

		default: {
			// Handle invalid interrupt mode if necessary
			break;
		}
		}

}





//INT2 has falling edge and rising edge  modes only
void EXTI_voidInt2init(u8 Copy_u8InterruptMode){
	switch(Copy_u8InterruptMode) {

		case falling_edge: {
			// Set sense control to falling edge
			Clr_Bit(MCUCSR, MCUCSR_ISC2);


			// Set PIE for INT2
			Set_Bit(GICR,  GICR_INT2);
			break;
		}

		case rising_edge: {
			// Set sense control to rising edge
			Set_Bit(MCUCSR, MCUCSR_ISC2);


			// Set PIE for INT2
			Set_Bit(GICR,  GICR_INT2);
			break;
		}

		default: {
			// Handle invalid interrupt mode if necessary
			break;
		}
		}

}


u8 EXTI_u8INT0SetCallBack(void (*Copy_pvINT0Func)(void)){
	u8 Local_u8ErrorState=0;
	if(Copy_pvINT0Func!=NULL){
		EXTI_pvInt0=Copy_pvINT0Func;
	}
	else{
		Local_u8ErrorState=1;
	}
	return Local_u8ErrorState;
}

u8 EXTI_u8INT1SetCallBack(void (*Copy_pvINT1Func)(void)){
	u8 Local_u8ErrorState=0;
	if(Copy_pvINT1Func!=NULL){
		EXTI_pvInt1=Copy_pvINT1Func;
	}
	else{
		Local_u8ErrorState=1;
	}
	return Local_u8ErrorState;
}
u8 EXTI_u8INT2SetCallBack(void (*Copy_pvINT2Func)(void)){
	u8 Local_u8ErrorState=0;
	if(Copy_pvINT2Func!=NULL){
		EXTI_pvInt2=Copy_pvINT2Func;
	}
	else{
		Local_u8ErrorState=1;
	}
	return Local_u8ErrorState;
}




void __vector_1 (void) __attribute__((signal));
void __vector_1 (void){
	EXTI_pvInt0(); //name of function is already pointer to function
}

void __vector_2 (void) __attribute__((signal));
void __vector_2 (void){
	EXTI_pvInt1(); //name of function is already pointer to function
}
void __vector_3 (void) __attribute__((signal));
void __vector_3 (void){
	EXTI_pvInt2(); //name of function is already pointer to function
}
