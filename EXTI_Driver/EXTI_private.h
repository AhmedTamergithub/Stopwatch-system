/*
 * EXTI_private.h
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
#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_





//Defining SREG register that stores flags in ALU
#define SREG   *((volatile u8*)  0x5F)
//Defining the 4 registers of EXTI
#define GICR   *((volatile u8*)  0x5B)
#define GIFR   *((volatile u8*)  0x5A)
#define MCUCR  *((volatile u8*)  0x55)
#define MCUCSR *((volatile u8*)  0x54)

//Defining GICR bits
#define GICR_INT1 7
#define GICR_INT0 6
#define GICR_INT2 5

//Defining MCUCR bits
#define MCUCR_ISC00 0
#define MCUCR_ISC01 1
#define MCUCR_ISC10 2
#define MCUCR_ISC11 3
//defining MCUCSR bit
#define MCUCSR_ISC2 6
//defining SREG bits for GIE
#define SREG_I 7








#endif /* EXTI_PRIVATE_H_ */
