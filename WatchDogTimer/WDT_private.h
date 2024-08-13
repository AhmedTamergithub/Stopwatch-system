/*
 * WDT_private.h
 *
 *  Created on: Aug 12, 2024
 *      Author: Ahmed
 */

#ifndef WDT_PRIVATE_H_
#define WDT_PRIVATE_H_

#define WDTCR   *((volatile u8*)  0x41)
#define WDTCR_WDTOE 4
#define WDTCR_WDE   3
#define WDTCR_WDP2  2
#define WDTCR_WDP1  1
#define WDTCR_WDP0  0

#endif /* WDT_PRIVATE_H_ */
