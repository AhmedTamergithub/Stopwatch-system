/*
 * TWI_main.c
 *
 *  Created on: Aug 6, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include"TWI_interface.h"
#include "GPIO_interface.h"
#include <util/delay.h>
void main(void){
	TWI_voidMasterInit(0);
	TWI_SendStartCondition();
	TWI_SendRSlaveAddressWithWrite(40);//40
	TWI_MasterWriteDataByte(0);
	TWI_SendStopCondition;
	//_delay_ms(100);
	while(1){

	}






}
