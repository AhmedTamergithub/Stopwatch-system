/*
 * Timer_interface.h
 *
 *  Created on: Aug 9, 2024
 *      Author: Ahmed
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void TIMER0_voidInit(void);

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));
void Timer0_voidSetCompareMatchValue(u8 Copy_u8Value);
#endif /* TIMER_INTERFACE_H_ */
