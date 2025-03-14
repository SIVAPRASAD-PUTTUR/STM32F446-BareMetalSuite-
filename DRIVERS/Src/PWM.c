/*
 * PWM.c
 *
 *  Created on: Mar 3, 2025
 *      Author: sivap
 */
#include "PWM.h"

void Timer_EN(TIM_TypeDef *TIMx){
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

void PWM_init(TIM_TypeDef *TIMx, uint8_t CHANNEL, uint16_t PSC, uint16_t ARR, uint8_t DUTY){

	Timer_EN(TIMx);
	TIMx->CR1 &=~(1<<0);
	TIMx->PSC = PSC-1;
	TIMx->ARR = ARR-1;



	if(CHANNEL == 1 ){
		TIMx->CCMR1 &= ~(7<<4);
		TIMx->CCMR1 |= (6<<4);
		TIMx->CCMR1 |= (1<<3);
		TIMx->CCR1 |= (TIMx->ARR * DUTY)/100;
		TIMx->CCER |= (1<<0);
		}
	else if(CHANNEL == 2){
		TIMx->CCMR1 &= ~(7<<12);
		TIMx->CCMR1 |= (6<<12);
		TIMx->CCMR1 |= (1<<11);
		TIMx->CCR2 |= (TIMx->ARR * DUTY)/100;
		TIMx->CCER |= (1<<4);
		}
	else if(CHANNEL==3){
		TIMx->CCMR2 &= ~(7<<4);
		TIMx->CCMR2 |= (6<<4);
		TIMx->CCMR2 |= (1<<3);
		TIMx->CCR3 |= (TIMx->ARR * DUTY)/100;
		TIMx->CCER |= (1<<8);
		}
	else if(CHANNEL == 2){
		TIMx->CCMR2 &= ~(7<<12);
		TIMx->CCMR2 |= (6<<12);
		TIMx->CCMR2 |= (1<<11);
		TIMx->CCR4 |= (TIMx->ARR * DUTY)/100;
		TIMx->CCER |= (1<<12);
		}
	TIMx->CR1 |= (1<<0);
}

void PWM_SetFrequency(TIM_TypeDef *TIMx, uint32_t channel, uint32_t frequency)
{
    // Get the APB timer clock (depends on whether the timer is on APB1 or APB2)
    uint32_t timerClock = (TIMx == TIM1 || TIMx == TIM8 || TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11 || TIMx == TIM4) ?
                          SystemCoreClock : (SystemCoreClock / 2);  // APB1 timers run at half the system clock

    // Calculate new prescaler and ARR values
    uint32_t prescaler = (timerClock / (frequency * 1000)) - 1;
    uint32_t period = 1000;  // Keep a fixed 1000-step period

    // Update prescaler and ARR (frequency setting)
    TIMx->PSC = prescaler;
    TIMx->ARR = period - 1;

    // Force an update to apply the changes immediately
    TIMx->EGR |= TIM_EGR_UG;
}

void PWM_SetDutyCycle(TIM_TypeDef *TIMx, uint32_t channel, uint32_t dutyCycle) {
    // Ensure duty cycle is within valid range (0 - 100%)
    if (dutyCycle > 100) dutyCycle = 100;

    // Get current ARR value (used to calculate CCR value)
    uint32_t period = TIMx->ARR + 1;
    uint32_t pulse = (period * dutyCycle) / 100;

    // Update CCRx based on channel
    switch (channel) {
        case 1: TIMx->CCR1 = pulse; break;
        case 2: TIMx->CCR2 = pulse; break;
        case 3: TIMx->CCR3 = pulse; break;
        case 4: TIMx->CCR4 = pulse; break;
        default: return;  // Invalid channel, do nothing
    }
}

void PWM_Start(TIM_TypeDef *TIMx, uint32_t channel) {
    // Enable the corresponding output channel
    switch (channel) {
        case 1: TIMx->CCER |= TIM_CCER_CC1E; break;
        case 2: TIMx->CCER |= TIM_CCER_CC2E; break;
        case 3: TIMx->CCER |= TIM_CCER_CC3E; break;
        case 4: TIMx->CCER |= TIM_CCER_CC4E; break;
        default: return;  // Invalid channel, do nothing
    }

    // Enable counter (start the timer)
    TIMx->CR1 |= TIM_CR1_CEN;
}

void PWM_Stop(TIM_TypeDef *TIMx, uint32_t channel) {
    // Disable the corresponding output channel
    switch (channel) {
        case 1: TIMx->CCER &= ~TIM_CCER_CC1E; break;
        case 2: TIMx->CCER &= ~TIM_CCER_CC2E; break;
        case 3: TIMx->CCER &= ~TIM_CCER_CC3E; break;
        case 4: TIMx->CCER &= ~TIM_CCER_CC4E; break;
        default: return;  // Invalid channel, do nothing
    }

    // If all channels are disabled, stop the timer
    if ((TIMx->CCER & (TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E)) == 0) {
        TIMx->CR1 &= ~TIM_CR1_CEN;  // Stop the timer
    }
}
























