/*
 * DAC.c
 *
 *  Created on: Mar 14, 2025
 *      Author: sivap
 */

#include "DAC.h"
#include "stm32f446xx.h"

void DAC_Init(void) {
    // Enable clocks for DAC and GPIOA
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;   // Enable DAC clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock

    // Configure PA4 (DAC Channel 1) and PA5 (DAC Channel 2) as analog mode
    GPIOA->MODER |= (3 << (4 * 2)) | (3 << (5 * 2)); // Analog mode for PA4 and PA5
    GPIOA->PUPDR &= ~((3 << (4 * 2)) | (3 << (5 * 2))); // No pull-up/pull-down
}

void DAC_Enable(uint8_t channel) {
    if (channel == DAC_CHANNEL_1) {
        DAC->CR |= DAC_CR_EN1; // Enable DAC Channel 1
    } else if (channel == DAC_CHANNEL_2) {
        DAC->CR |= DAC_CR_EN2; // Enable DAC Channel 2
    }
}

void DAC_Disable(uint8_t channel) {
    if (channel == DAC_CHANNEL_1) {
        DAC->CR &= ~DAC_CR_EN1; // Disable DAC Channel 1
    } else if (channel == DAC_CHANNEL_2) {
        DAC->CR &= ~DAC_CR_EN2; // Disable DAC Channel 2
    }
}

void DAC_SetValue(uint8_t channel, uint16_t value) {
    // Limit value to 12 bits
    if (value > 4095) value = 4095;

    if (channel == DAC_CHANNEL_1) {
        DAC->DHR12R1 = value; // Set value for DAC Channel 1
    } else if (channel == DAC_CHANNEL_2) {
        DAC->DHR12R2 = value; // Set value for DAC Channel 2
    }
}

