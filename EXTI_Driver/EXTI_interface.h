/*
 * EXTI_interface.h
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
#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

// defining interrupt events
#define low_level    0
#define on_change    1
#define falling_edge 2
#define rising_edge  3




void GIE_voidEnable(void);
void GIE_voidDisable(void);
void EXTI_voidInt0init(u8 Copy_u8InterruptMode);
void EXTI_voidInt1init(u8 Copy_u8InterruptMode);
u8 EXTI_u8INT0SetCallBack(void (*Copy_pvINT0Func)(void)); //PV REPRESENTS POINTER TO function retrns a void argument
u8 EXTI_u8INT1SetCallBack(void (*Copy_pfINT1Func)(void));
u8 EXTI_u8INT2SetCallBack(void (*Copy_pfINT2Func)(void));




#endif /* EXTI_INTERFACE_H_ */
