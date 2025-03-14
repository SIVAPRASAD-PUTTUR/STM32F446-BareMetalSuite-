/*
 * TIMERS.h
 *
 *  Created on: Feb 24, 2025
 *      Author: sivap
 */

#ifndef INC_TIMERS_H_
#define INC_TIMERS_H_
#include "stm32f4xx.h"

//void  Timer_ENCLK(TIM_TypeDef *TIMx);
void Tim_init(TIM_TypeDef *TIMx,uint16_t PSC, uint16_t ARR);
void Tim_delay(TIM_TypeDef *TIMx,uint16_t delay_ms);
void start_Tim(TIM_TypeDef *TIMx);
uint32_t getCounter(TIM_TypeDef *TIMx);
void detDutycycle(TIM_TypeDef *TIMx, uint32_t CHANNEL, uint32_t DUTY);
void Tim_IPC_init(TIM_TypeDef *TIMx, uint32_t CHANNEL);
uint32_t Tim_GetCapVal(TIM_TypeDef *TIMx, uint32_t CHANNEL);
void Timer_OutputCompare_Init(TIM_TypeDef *TIMx, uint8_t channel, uint32_t compareValue);
void Timer_SetCompareValue(TIM_TypeDef *TIMx, uint8_t channel, uint32_t compareValue);


#endif /* INC_TIMERS_H_ */
