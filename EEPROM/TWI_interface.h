/*
 * TWI_interface.h
 *
 *  Created on: Aug 6, 2024
 *      Author: Ahmed
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_
#include "BIT_Calc.h"
#include "STD_Types.h"



//Error Status Enum for differntiating location of errors where in sequence of I2C operation

 typedef enum {
	 NoError,
    Start_Error = 4,          // Explicitly assign value 4
    SlaveAddressandWriteAck_Error,      // Automatically assigned value 5
    SlaveAddressandReadAck_Error,       // Automatically assigned value 6
    MasterWriteDataByte_Error,          // Automatically assigned value 7
    MasterReadDataByte_Error            // Automatically assigned value 8
} TWI_ErrorStatus;



/*pass 0 in the slave address argument if master will not become a reciever*/


void TWI_voidMasterInit(u8 Copy_u8SlaveAddress);

void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress);

TWI_ErrorStatus TWI_SendStartCondition(void);
TWI_ErrorStatus TWI_SendRepeatedStart(void);
TWI_ErrorStatus TWI_SendRSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);//Pass 0 if write in Lsb
TWI_ErrorStatus TWI_SendRSlaveAddressWithRead(u8 Copy_u8SlaveAddress);//Pass 1 if read in LSB
TWI_ErrorStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte);
TWI_ErrorStatus TWI_MasterReadDataByte(u8 *Copy_u8DataByte);


void TWI_SendStopCondition(void);
#endif /* TWI_INTERFACE_H_ */
