/*
 * EEPROM_program.c
 *
 *  Created on: Aug 7, 2024
 *      Author: Ahmed
 */


#include "BIT_Calc.h"
#include "STD_Types.h"
#include "TWI_interface.h"
#include "EEPROM_confg.h"
#include "EEPROM_interface.h"


void EEPROM_sendDataByte(u8 DataByte,u16 Address){
	 TWI_SendStartCondition();  //Start Condition
	 TWI_SendRSlaveAddressWithWrite(1010|A2<<2|Address>>8);
	 TWI_MasterWriteDataByte((u8)Address);
	 TWI_MasterWriteDataByte(DataByte);
	 TWI_SendStopCondition();
}



void EEPROM_readDataByte(u16 Address,u8 *Databyte){
	 TWI_SendStartCondition();
	 TWI_SendRSlaveAddressWithWrite(1010|A2<<2|Address>>8);
	 TWI_MasterWriteDataByte((u8)Address);
	 TWI_SendRepeatedStart();
	 TWI_SendRSlaveAddressWithRead(1010|A2<<2|Address>>8);
	 TWI_MasterReadDataByte(Databyte);
	 TWI_SendStopCondition();
}
