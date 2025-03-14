/*
 * SEVSEG.c
 *
 *  Created on: Mar 6, 2025
 *      Author: sivap
 */
#include "SEVSEG.h"
const uint8_t segmentValues[11] = {

		0x7E,	//0
		0X30,	//1
		0X6D,	//2
		0X79,	//3
		0X33,	//4
		0X5B, 	//5
		0X5F,	//6
		0X70, 	//7
		0X7F,	//8
		0X7B,	//9
	    0b00000001  // POINT only (for 10)
};

void SevSeg_init(SSDISPLAY *DISPLAY){
	for(int i=0; i<8; i++){
		setPin(DISPLAY->PORT[i], DISPLAY->PIN[i], OP);//SETS THE PINS AS OPs
	}
}

void SevSeg_disp(SSDISPLAY *DISPLAY, uint8_t VAL){
    if (VAL > 10) return; // Prevent out-of-bounds access

    uint8_t TEXT = segmentValues[VAL]; // Get the segment pattern

    for(int i = 0; i < 8; i++){  // Only iterate for A-G (7 segments)
    	if(i<7){
    		pinWrite(DISPLAY->PORT[i], DISPLAY->PIN[i], (TEXT >> (6 - i)) & 1);
    	}
    	else{
            pinWrite(DISPLAY->PORT[7], DISPLAY->PIN[7], (VAL == 10) ? 1 : 0& 1);
    	}
    }

}


















