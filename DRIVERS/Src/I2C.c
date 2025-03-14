#include "I2C.h"

void I2C_Init(uint8_t instance, GPIO_TypeDef *PORT_SCL, uint8_t PIN_SCL, GPIO_TypeDef *PORT_SDA, uint8_t PIN_SDA, uint32_t clockSpeed) {
    if (instance == I2C_INSTANCE_1) {
        // Enable I2C1 clock
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

        // Configure GPIOs for I2C (using your GPIO library)
        setPin(PORT_SCL, PIN_SCL, AF); // Alternate function mode for SCL
        setPin(PORT_SDA, PIN_SDA, AF); // Alternate function mode for SDA
        setAF(PORT_SCL, PIN_SCL, 4);   // AF4 for I2C1 SCL
        setAF(PORT_SDA, PIN_SDA, 4);   // AF4 for I2C1 SDA
        setPUPDR(PORT_SCL, PIN_SCL, PLU); // Pull-up for SCL
        setPUPDR(PORT_SDA, PIN_SDA, PLU); // Pull-up for SDA
        setOPSPEEDR(PORT_SCL, PIN_SCL, HS); // High-speed for SCL
        setOPSPEEDR(PORT_SDA, PIN_SDA, HS); // High-speed for SDA

        // Configure I2C1 peripheral
        I2C1->CR1 &= ~I2C_CR1_PE; // Disable I2C1 before configuration
        I2C1->CR2 = (clockSpeed / 1000000U) & 0x3F; // Set APB1 clock frequency in MHz
        I2C1->CCR = (clockSpeed / 2 / 100000);      // Configure clock control for 100 kHz
        I2C1->TRISE = (clockSpeed / 1000000U) + 1;  // Max rise time
        I2C1->CR1 |= I2C_CR1_PE; // Enable I2C1
    }
}

void I2C_Start(uint8_t instance) {
    if (instance == I2C_INSTANCE_1) {
        I2C1->CR1 |= I2C_CR1_START; // Send START condition
        while (!(I2C1->SR1 & I2C_SR1_SB)); // Wait for START condition to be set
    }
}

void I2C_Stop(uint8_t instance) {
    if (instance == I2C_INSTANCE_1) {
        I2C1->CR1 |= I2C_CR1_STOP; // Send STOP condition
    }
}

void I2C_Write(uint8_t instance, uint8_t address, uint8_t data) {
    if (instance == I2C_INSTANCE_1) {
        // Send slave address
        I2C1->DR = address & 0xFE; // Write operation (clear LSB)
        while (!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait for address to be acknowledged
        (void)I2C1->SR2; // Clear ADDR flag

        // Send data
        I2C1->DR = data;
        while (!(I2C1->SR1 & I2C_SR1_TXE)); // Wait for data transmission

        // Send STOP condition
        I2C_Stop(I2C_INSTANCE_1);
    }
}

uint8_t I2C_Read(uint8_t instance, uint8_t address, uint8_t ack) {
    uint8_t receivedData = 0;

    if (instance == I2C_INSTANCE_1) {
        // Send slave address with read bit
        I2C1->DR = address | 0x01; // Read operation (set LSB)
        while (!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait for address to be acknowledged
        (void)I2C1->SR2; // Clear ADDR flag

        // Enable/Disable ACK
        if (ack) {
            I2C1->CR1 |= I2C_CR1_ACK;
        } else {
            I2C1->CR1 &= ~I2C_CR1_ACK;
        }

        // Wait for data reception
        while (!(I2C1->SR1 & I2C_SR1_RXNE));
        receivedData = I2C1->DR;

        // Send STOP condition
        I2C_Stop(I2C_INSTANCE_1);
    }

    return receivedData;
}
