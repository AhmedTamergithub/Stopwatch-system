/*
 * TWI_program.c
 *
 *  Created on: Aug 6, 2024
 *      Author: Ahmed
 */

#include "BIT_Calc.h"
#include "STD_Types.h"
#include"TWI_interface.h"
#include"TWI_config.h"
#include"TWI_private.h"


/*Important Note: In any function with retutn type error status if there is error it will return the corresponding enum value
and if there is no value it will return 0(No Error)

If there is no error u call the next expected function in main.c

 */
void TWI_voidMasterInit(u8 Copy_u8SlaveAddress){

//Enable TWI
	Set_Bit(TWCR,TWCR_TWEN);

	//Set TWBR TO 2
	TWBR=2;
	//Set Clock Frequency to 400kbps
    Clr_Bit(TWSR,TWSR_TWPS1);
    Clr_Bit(TWSR,TWSR_TWPS0);
// Enable Acknowledge Bit
		Set_Bit(TWCR,TWCR_TWEA);
//initialize address
		if(Copy_u8SlaveAddress!=0){
			TWAR=Copy_u8SlaveAddress<<1;
		}
}

void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress){
	//initialize address
			if(Copy_u8SlaveAddress!=0){
				TWAR=Copy_u8SlaveAddress<<1;
			}


	//Enable TWI
		Set_Bit(TWCR,TWCR_TWEN);

		// Enable Acknowledge Bit
		Set_Bit(TWCR,TWCR_TWEA);
}


TWI_ErrorStatus TWI_SendStartCondition(void){

TWI_ErrorStatus Local_ErrStatus=NoError;

//Enable Start Condition
Set_Bit(TWCR,TWCR_TWSTA);


//Clear Flag of TWINT by writing 1 in it
	Set_Bit(TWCR,TWCR_TWINT);

//TWI Check that HW raised the TWINT FLAG indicating start condition is sent
while(Get_Bit(TWCR, TWCR_TWINT )!=1);

//Checking status of bus after sending start condition
if ((TWSR & 0xF8) != START_ACK){
   return  Start_Error ;
}
else {return NoError;}
//Ask in main.c if return equal to Send Start Condition then call send slave address with write(VERY IMPORTANT)
//and according to R/W bit Call Slave_address_read or slave_address_write function
}





TWI_ErrorStatus TWI_SendRepeatedStart(void){
	TWI_ErrorStatus Local_ErrStatus=NoError;

	//Enable Start Condition
	Set_Bit(TWCR,TWCR_TWSTA);


	//Clear Flag of TWINT by writing 1 in it
		Set_Bit(TWCR,TWCR_TWINT);

	//TWI Check that HW raised the TWINT FLAG indicating start condition is sent
	while(Get_Bit(TWCR, TWCR_TWINT )!=1);

	//Checking status of bus after sending start condition
	if ((TWSR & 0xF8) != REP_START_ACK){
	   return  Start_Error ;
	}
	else {return NoError;}
}




TWI_ErrorStatus TWI_SendRSlaveAddressWithWrite(u8 Copy_u8SlaveAddress){
	//TWI_ErrorStatus Local_ErrStatus=NoError;
	//clear TWSTA Flag by writing zero in it
		Clr_Bit(TWCR,TWCR_TWSTA);
    //Set Slave Address in 7 MOST SIGNIFICANT BITS Data Register
	TWDR=Copy_u8SlaveAddress<<1;
	Clr_Bit(TWDR,0);//ENSURE WRITE SIGNAL
	//Clear Flag of TWINT by writing 1 in it
	Set_Bit(TWCR,TWCR_TWINT);




	//TWI Check that HW raised the TWINT FLAG indicating slave address is written with ack
			while(Get_Bit(TWCR, TWCR_TWINT )!=1);

	if ((TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK)
			   {return SlaveAddressandWriteAck_Error;}
			   else
			   {return NoError;}
			   //If return value=0 go to function of master write databyte


}

TWI_ErrorStatus TWI_SendRSlaveAddressWithRead(u8 Copy_u8SlaveAddress){
	   //TWI_ErrorStatus Local_ErrStatus=NoError;
	   //clear TWSTA Flag by writing zero in it
			Clr_Bit(TWCR,TWCR_TWSTA);
	   //Set Slave Address in 7 MOST SIGNIFICANT BITS Data Register
		TWDR=Copy_u8SlaveAddress<<1;
		Set_Bit(TWDR,0);//ENSURE READ SIGNAL
		//Clear Flag of TWINT by writing 1 in it
		Set_Bit(TWCR,TWCR_TWINT);


		//TWI Check that HW raised the TWINT FLAG indicating slave address is read with ack
		while(Get_Bit(TWCR, TWCR_TWINT )!=1);



		if ((TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK)
		  {return SlaveAddressandReadAck_Error;}

		  else {return NoError;}
		  //If return value=0 go to function of master read databyte

}

TWI_ErrorStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte){

	//TWI_ErrorStatus Local_ErrStatus=NoError;
	//Write in TWDR
	TWDR=Copy_u8DataByte;

	//Clear Flag of TWINT by writing 1 in it
			Set_Bit(TWCR,TWCR_TWINT);

	while (Get_Bit(TWCR, TWCR_TWINT )!=1);
	if ((TWSR & 0xF8) != MSTR_WR_BYTE_ACK){
return MasterWriteDataByte_Error;
	}
	else {return NoError;}
}

TWI_ErrorStatus TWI_MasterReadDataByte(u8 *Copy_u8DataByte){
	TWI_ErrorStatus Local_ErrStatus=NoError;
	//reading the content
	*Copy_u8DataByte=TWDR;

	//Clear Flag of TWINT by writing 1 in it
	Set_Bit(TWCR,TWCR_TWINT);

	while (Get_Bit(TWCR, TWCR_TWINT)!=1);
		if ((TWSR & 0xF8)!=MSTR_RD_BYTE_WITH_ACK){
			return  MasterReadDataByte_Error;

		}
		else {return NoError;}
		// if return value=0,then go to stop condition function
}



void TWI_SendStopCondition(void){

Set_Bit(TWCR,TWCR_TWSTO);

//Clear Flag of TWINT by writing 1 in it
	Set_Bit(TWCR,TWCR_TWINT);

}

