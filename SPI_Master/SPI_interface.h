/*
 * SPI_interface.h
 *
 *  Created on: Aug 4, 2024
 *      Author: Ahmed
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_
#include "BIT_Calc.h"
#include "STD_Types.h"


void SPI_voidMasterInit(void);
void SPI_voidSlaveInit(void);
u8 SPI_u8Transceive(u8 Data);



#endif /* SPI_INTERFACE_H_ */
