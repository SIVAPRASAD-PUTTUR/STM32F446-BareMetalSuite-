/*
 * ADC.c
 *
 *  Created on: Mar 5, 2025
 *      Author: sivap
 */

#include "ADC.h"

void ADC_EN(ADC_TypeDef *ADCx){
	if(ADCx == ADC1)RCC->APB2ENR |= (1<<8);
	else if(ADCx == ADC2)RCC->APB2ENR |= (1<<9);
	else if(ADCx == ADC3)RCC->APB2ENR |= (1<<10);
}

void ADC_init_Single(ADC_TypeDef *ADCx, uint8_t CHANNEL){

	ADC_EN(ADCx);

	ADCx->CR2 &= ~(1<<0);
	ADCx->SQR1 |= (0<<20);
	ADCx->SQR3 = (CHANNEL << 0);
	ADCx->CR2 |= (1<<0);

}

void ADC_set_STime(ADC_TypeDef *ADCx, uint8_t CHANNEL,uint8_t SAMPLETIME){

	if (CHANNEL < 10) ADCx->SMPR2 |= (SAMPLETIME << (3 * CHANNEL));
	else ADCx->SMPR1 |= (SAMPLETIME << (3 * (CHANNEL - 10)));

}

uint16_t ADC_Read_single(ADC_TypeDef *ADCx, uint8_t CHANNEL){

	ADCx->SQR3 = (CHANNEL << 0);
	ADCx->CR2 |= (1<<30);
	while(!(ADCx->SR & (1<<1)));
	uint16_t value = ADCx->DR; // Read ADC value (This also clears EOC flag)
	ADCx->SR &= ~(1 << 1); // Clear EOC manually (optional)
	return value;
}

void ADC_Stop_Single(ADC_TypeDef *ADCx){
	ADCx->CR2 &= ~(1<<30);
}



void ADC_init_Cont(ADC_TypeDef *ADCx, uint8_t CHANNEL){
	ADC_EN(ADCx);
	ADCx->CR2 &= ~(1<<0);
	ADCx->CR2 |= (1<<1); //enable the cont mode
	ADCx->SQR1 |= (0<<20);
	ADCx->SQR3 = (CHANNEL << 0);
	ADCx->CR2 |= (1<<0);
}

uint16_t ADC_Read_Cont(ADC_TypeDef *ADCx, uint8_t CHANNEL){
	ADCx->SQR3 = (CHANNEL << 0);
	while(!(ADCx->SR & (1<<1)));
	return ADCx->DR ;

}
void ADC_Start_Cont(ADC_TypeDef *ADCx) {
    ADCx->CR2 |= (1<<30);
}

void ADC_Stop_Cont(ADC_TypeDef *ADCx){

	ADCx->CR2 &= ~(1 << 1);
	ADCx->CR2 &= ~(1<<30);
}



















