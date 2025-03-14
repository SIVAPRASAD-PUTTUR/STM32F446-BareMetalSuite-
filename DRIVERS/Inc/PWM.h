/*
 * PWM.h
 *
 *  Created on: Mar 3, 2025
 *      Author: sivap
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "stm32f446xx.h"
#define SystemCoreClock 16000000

void PWM_init(TIM_TypeDef *TIMx, uint8_t CHANNEL, uint16_t PSC, uint16_t ARR, uint8_t DUTY);
void PWM_SetFrequency(TIM_TypeDef *TIMx, uint32_t channel, uint32_t frequency);
void PWM_SetDutyCycle(TIM_TypeDef *TIMx, uint32_t channel, uint32_t dutyCycle);
void PWM_Start(TIM_TypeDef *TIMx, uint32_t channel);
void PWM_Stop(TIM_TypeDef *TIMx, uint32_t channel);


#endif /* INC_PWM_H_ */
