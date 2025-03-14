/*
 * ADC.h
 *
 *  Created on: Mar 5, 2025
 *      Author: sivap
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm32f446xx.h"

#define C3 0
#define C15 1
#define C28 2
#define C56 3
#define C84 4
#define C112 5
#define C144 6
#define C480 7



void ADC_init_Single(ADC_TypeDef *ADCx, uint8_t CHANNEL);
void ADC_set_STime(ADC_TypeDef *ADCx, uint8_t CHANNEL,uint8_t SAMPLETIME);
uint16_t ADC_Read_single(ADC_TypeDef *ADCx, uint8_t CHANNEL);
void ADC_Stop_Single(ADC_TypeDef *ADCx);


void ADC_init_Cont(ADC_TypeDef *ADCx, uint8_t CHANNEL);
uint16_t ADC_Read_Cont(ADC_TypeDef *ADCx, uint8_t CHANNEL);
void ADC_Start_Cont(ADC_TypeDef *ADCx);
void ADC_Stop_Cont(ADC_TypeDef *ADCx);





#endif /* INC_ADC_H_ */








