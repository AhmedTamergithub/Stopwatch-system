/*
 * UART_interface.h
 *
 *  Created on: Aug 3, 2024
 *      Author: Ahmed
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_init(void);
void UART_voidsend(u8 Copy_u8data);
u8 UART_voidreceive(void);



#endif /* UART_INTERFACE_H_ */
