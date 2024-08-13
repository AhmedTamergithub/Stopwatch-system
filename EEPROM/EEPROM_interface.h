/*
 * EEPROM_interface.h
 *
 *  Created on: Aug 7, 2024
 *      Author: Ahmed
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_



void EEPROM_sendDataByte(u8 DataByte,u16 Address);
void EEPROM_readDataByte(u16 Address,u8 *Databyte);

#endif /* EEPROM_INTERFACE_H_ */
