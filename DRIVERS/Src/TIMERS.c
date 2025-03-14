/*
 * TIMERS.c
 *
 *  Created on: Feb 24, 2025
 *      Author: sivap
 */

#include "TIMERS.h"

void Timer_ENCLK(TIM_TypeDef *TIMx){
    if(TIMx == TIM1) RCC->APB2ENR |= (1 << 0);
    else if(TIMx == TIM2) RCC->APB1ENR |= (1 << 0);
    else if(TIMx == TIM3) RCC->APB1ENR |= (1 << 1);
    else if(TIMx == TIM4) RCC->APB1ENR |= (1 << 2);
    else if(TIMx == TIM5) RCC->APB1ENR |= (1 << 3);
    else if(TIMx == TIM6) RCC->APB1ENR |= (1 << 4);
    else if(TIMx == TIM7) RCC->APB1ENR |= (1 << 5);
    else if(TIMx == TIM8) RCC->APB2ENR |= (1 << 1);
    else if(TIMx == TIM9) RCC->APB2ENR |= (1 << 16);
    else if(TIMx == TIM10) RCC->APB2ENR |= (1 << 17);
    else if(TIMx == TIM11) RCC->APB2ENR |= (1 << 18);
    else if(TIMx == TIM12) RCC->APB1ENR |= (1 << 6);
    else if(TIMx == TIM13) RCC->APB1ENR |= (1 << 7);
    else if(TIMx == TIM14) RCC->APB1ENR |= (1 << 8);
}

void Tim_init(TIM_TypeDef *TIMx, uint16_t PSC, uint16_t ARR){
    Timer_ENCLK(TIMx);
    TIMx->CR1 &= ~(1 << 0);  // Disable Timer before setting
    TIMx->PSC = PSC - 1;      // Set prescaler
    TIMx->ARR = ARR - 1;      // Set auto-reload
    TIMx->CNT = 0;            // Reset counter
    TIMx->CR1 |= (1 << 0);    // Enable Timer
}

void Tim_delay(TIM_TypeDef *TIMx, uint16_t delay_ms){
    Timer_ENCLK(TIMx);
    TIMx->CR1 &= ~(1 << 0);  // Stop timer
    TIMx->PSC = 16000 - 1;   // Assuming 16 MHz clock
    TIMx->ARR = delay_ms - 1;
    TIMx->CNT = 0;
    TIMx->SR &= ~(1 << 0);   // Clear update flag
    TIMx->CR1 |= (1 << 0);   // Start timer

    uint32_t timeout = 1000000; // Add timeout to prevent infinite loop
    while (!(TIMx->SR & (1 << 0)) && --timeout);
    TIMx->CR1 &= ~(1 << 0);
    TIMx->SR &= ~(1 << 0);
}



void start_Tim(TIM_TypeDef *TIMx){
	TIMx->CR1 &= ~(1<<0);
}

uint32_t getCounter(TIM_TypeDef *TIMx){
	return TIMx->CNT ;
}

void detDutycycle(TIM_TypeDef *TIMx, uint32_t CHANNEL, uint32_t DUTY){
	if(CHANNEL == 1) TIMx->CCR1 = (TIMx->ARR * DUTY)/100;
	else if(CHANNEL == 2) TIMx->CCR2 = (TIMx->ARR * DUTY)/100;
	else if(CHANNEL == 3) TIMx->CCR3 = (TIMx->ARR * DUTY)/100;
	else if(CHANNEL == 4) TIMx->CCR4 = (TIMx->ARR * DUTY)/100;
}

void Tim_IPC_init(TIM_TypeDef *TIMx, uint32_t CHANNEL){
	Timer_ENCLK(TIMx);

	TIMx->PSC = 15 ;
	TIMx->ARR = 0xFFFF;

	switch (CHANNEL) {
		case 1:
			TIMx->CCMR1 |= (1<<0) ;
			TIMx->CCMR1 |= (1<<2) ;
			TIMx->CCER |= (1<<0) ;
			break;
		case 2:
			TIMx->CCMR1 |= (1<<8) ;
			TIMx->CCMR1 |= (1<<10) ;
			TIMx->CCER |= (1<<4) ;
			break;
		case 3:
			TIMx->CCMR2 |= (1<<0) ;
			TIMx->CCMR2 |= (1<<2) ;
			TIMx->CCER |= (1<<8) ;
			break;
		case 4:
			TIMx->CCMR2 |= (1<<8) ;
			TIMx->CCMR2 |= (1<<10) ;
			TIMx->CCER |= (1<<12) ;
			break;
	}
	TIMx->DIER |= (1<< CHANNEL);
	TIMx->CR1 |=(1<<0);
}

uint32_t Tim_GetCapVal(TIM_TypeDef *TIMx, uint32_t CHANNEL){
	switch (CHANNEL) {
		case 1: return TIMx->CCR1;
		case 2: return TIMx->CCR2;
		case 3: return TIMx->CCR3;
		case 4: return TIMx->CCR4;
		default : return 0;
	}
}

void Timer_OutputCompare_Init(TIM_TypeDef *TIMx, uint8_t channel, uint32_t compareValue) {
    Timer_ENCLK(TIMx);

    // Configure the timer prescaler and auto-reload (ARR)
    TIMx->PSC = 15;       // Set prescaler to divide 16 MHz clock by 16 → 1 MHz timer clock
    TIMx->ARR = 0xFFFF;   // Set max auto-reload value

    // Configure the selected output compare channel
    switch (channel) {
        case 1:
            TIMx->CCMR1 &= ~(3 << 0);  // Clear OC1M bits
            TIMx->CCMR1 |= (6 << 4);   // Select OC1M = 110 (Toggle mode)
            TIMx->CCR1 = compareValue; // Set compare value
            TIMx->CCER |= (1 << 0);    // Enable output on channel 1
            break;
        case 2:
            TIMx->CCMR1 &= ~(3 << 8);
            TIMx->CCMR1 |= (6 << 12);
            TIMx->CCR2 = compareValue;
            TIMx->CCER |= (1 << 4);
            break;
        case 3:
            TIMx->CCMR2 &= ~(3 << 0);
            TIMx->CCMR2 |= (6 << 4);
            TIMx->CCR3 = compareValue;
            TIMx->CCER |= (1 << 8);
            break;
        case 4:
            TIMx->CCMR2 &= ~(3 << 8);
            TIMx->CCMR2 |= (6 << 12);
            TIMx->CCR4 = compareValue;
            TIMx->CCER |= (1 << 12);
            break;
        default:
            return; // Invalid channel
    }

    // Enable the timer
    TIMx->CR1 |= (1 << 0);  // CEN = 1 (Start Timer)
}

void Timer_SetCompareValue(TIM_TypeDef *TIMx, uint8_t channel, uint32_t compareValue) {
    switch (channel) {
        case 1:
            TIMx->CCR1 = compareValue;
            break;
        case 2:
            TIMx->CCR2 = compareValue;
            break;
        case 3:
            TIMx->CCR3 = compareValue;
            break;
        case 4:
            TIMx->CCR4 = compareValue;
            break;
        default:
            return; // Invalid channel
    }
}







