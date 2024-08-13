/*
 * WDT_program.c
 *
 *  Created on: Aug 12, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include "WDT_private.h"
#include "WDT_interface.h"



void WDT_voidSleep(u8 Copy_u8SleepTime){

	//Set Timeout to 1 second according to our application
if(Copy_u8SleepTime==1){
	Set_Bit(WDTCR,WDTCR_WDP2);
	Set_Bit(WDTCR,WDTCR_WDP1);
	Clr_Bit(WDTCR,WDTCR_WDP0);
}
}
void WDT_Disable(void){
	/* Write logical one to WDTOE and WDE */
	WDTCR = (1<<WDTCR_WDTOE) | (1<<WDTCR_WDE);
	/* Turn off WDT */
	WDTCR = 0x00;
}
void WDT_Enable(void){
Set_Bit(WDTCR,WDTCR_WDE);

}
