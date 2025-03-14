#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>
#include "stm32f446xx.h"
#include "GPIO.h" // Include your GPIO library

// I2C instances
#define I2C_INSTANCE_1 1 // I2C1

// Function prototypes
void I2C_Init(uint8_t instance, GPIO_TypeDef *PORT_SCL, uint8_t PIN_SCL, GPIO_TypeDef *PORT_SDA, uint8_t PIN_SDA, uint32_t clockSpeed);
void I2C_Start(uint8_t instance);
void I2C_Stop(uint8_t instance);
void I2C_Write(uint8_t instance, uint8_t address, uint8_t data);
uint8_t I2C_Read(uint8_t instance, uint8_t address, uint8_t ack);

#endif // I2C_DRIVER_H
