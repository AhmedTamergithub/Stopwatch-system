/*
 * sevensegment_program.c
 *
 *  Created on: Aug 13, 2024
 *      Author: Ahmed
 */




#include "BIT_Calc.h"
#include "STD_Types.h"
#include"sevensegment_interface.h"
u8 SevenSegmentArr[10]={
		0b00111111, //0
		0b00000110, //1
		0b01011011, //2
		0b01001111,//3
		0b01100110,//4
		0b01101101,//5
		0b11111101,//6
		0b00000111,//7
		0b01111111,//8
		0b01101111//9
};
u8 sevensegmentinit(u8 Copy_u8number){

switch(Copy_u8number) {
case 0 : {
	return SevenSegmentArr[0];

}

case 1: {
	return SevenSegmentArr[1];


}

case 2: {
	return SevenSegmentArr[2];

}

case 3: {
	return SevenSegmentArr[3];

}

case 4: {
	return SevenSegmentArr[4];

}
case 5: {
	return SevenSegmentArr[5];

}
case 6: {
	return SevenSegmentArr[6];

}
case 7: {
	return SevenSegmentArr[7];

}
case 8: {
	return SevenSegmentArr[8];

}
case 9: {
	return SevenSegmentArr[9];

}
default: {

	return 0;
}
}


}

