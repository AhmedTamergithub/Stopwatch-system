/*
 * ICU_private.h
 *
 *  Created on: Aug 11, 2024
 *      Author: Ahmed
 */

#ifndef ICU_PRIVATE_H_
#define ICU_PRIVATE_H_
#define TCCR0  *((volatile u8*)  0x53)
//TCCR0
#define TCCR0_FOC0  7
#define TCCR0_WGM00 6
#define TCCR0_COM01 5
#define TCCR0_COM00 4  /* Bits of Compare Output Register*/
#define TCCR0_WGM01 3
/*Bits of Prescalar as a timer  or using an external event as counter*/
#define TCCR0_CS02  2
#define TCCR0_CS01  1
#define TCCR0_CS00  0



#define TCNT0  *((volatile u8*)  0x52)

#define OCR0  *((volatile u8*)  0x5C)

#define TIMSK  *((volatile u8*)  0x59)

#define TIMSK_TICIE1 5
#define TIMSK_OCIE1A 4
#define TIMSK_OCIE1B 3
#define TIMSK_TOIE1  2
#define TIMSK_OCIE0  1
#define TIMSK_TOIE0  0

#define TIFR   *((volatile u8*)  0x58)

#define TIFR_OCF0 1
#define TIFR_TOV0 0



//Timer1
#define TCCR1A   *((volatile u8*)  0x4F)
#define TCCR1A_COM1A1  7
#define TCCR1A_COM1A0  6
#define TCCR1A_COM1B1  5
#define TCCR1A_COM1B0  4
#define TCCR1A_FOC1A   3
#define TCCR1A_FOC1B   2
#define TCCR1A_WGM11   1
#define TCCR1A_WGM10   0



#define TCCR1B   *((volatile u8*)  0x4E)
#define TCCR1B_ICNC1   7
#define TCCR1B_ICES1   6
#define TCCR1B_WGM13   4
#define TCCR1B_WGM12   3
#define TCCR1B_CS12    2
#define TCCR1B_CS11    1
#define TCCR1B_CS10    0


#define TCNT1   *((volatile u16*)  0x4C)

#define OCR1A   *((volatile u16*)  0x4A)

#define OCR1B    *((volatile u16*)  0x48)

#define ICR1    *((volatile u16*)  0x46)




//Defining Interrupts register and its bits
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


#endif /* ICU_PRIVATE_H_ */
