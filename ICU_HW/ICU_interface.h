/*
 * ICU_interface.h
 *
 *  Created on: Aug 11, 2024
 *      Author: Ahmed
 */

#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_


//Defining Interrupt Modes to be passes in Function INT0_SETTRIGGER
#define low_level    0
#define on_change    1
#define falling_edge 2
#define rising_edge  3


#define ENABLE  1
#define DISABLE 0

//Defining 3 interrupts of system to be passed in Function EXTI_DisableInterrupt
#define INT0 0
#define INT1 1
#define INT2 2


//Timer0 Functions
void TIMER0_voidInit(void);

//Timer1 Functions
void TIMER1_voidInit(void);
void Timer1_setTimerValue(u16 Copy_u16value);//Function to set value of timer value inside register(for example setting timer register=0 at first positive edge)
u16  Timer1_GetTimerReading (void);//Function to get reading of timer at 2nd positive edge to calculate Period Time


//ICU
void ICU_voidInit(void);
void ICU_SetTriggerEdge(u8 Copy_u8edge);
void ICU_EnableorDisable(u8 Copy_u8Enable);
u8 ICU_setCallBack(void (*Copy_pvICUFunc)(void));
u16 ICU_u16ReadICR1 (void);


#endif /* ICU_INTERFACE_H_ */
