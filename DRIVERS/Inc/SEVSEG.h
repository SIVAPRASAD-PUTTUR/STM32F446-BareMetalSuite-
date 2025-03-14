/*
 * SEVSEG.h
 *
 *  Created on: Mar 6, 2025
 *      Author: sivap
 */

#ifndef INC_SEVSEG_H_
#define INC_SEVSEG_H_
#include "stm32f446xx.h"
#include "GPIO.h"

typedef struct{

	GPIO_TypeDef *PORT[8];
	uint8_t PIN[8];
	uint8_t DP_PORT ;
	uint8_t DP_PIN;

}SSDISPLAY;

void SevSeg_init(SSDISPLAY *DISPLAY);
void SevSeg_disp(SSDISPLAY *DISPLAY, uint8_t VAL);

#endif /* INC_SEVSEG_H_ */
