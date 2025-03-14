/*
 * SPI.c
 *
 *  Created on: Mar 10, 2025
 *      Author: sivap
 */
#include "SPI.h"


void spi_en(SPI_TypeDef *SPI){
	if(SPI==SPI1) RCC->APB2ENR |= (1<<12);
	else if(SPI == SPI2) RCC->APB1ENR |= (1<<14);
	else if(SPI == SPI3) RCC->AHB1ENR |= (1<<15);
	else if(SPI == SPI4) RCC->AHB2ENR |= (1<<13);
}
void SPI_init(SPI_TypeDef *SPI, uint8_t MOSI, uint8_t MISO, uint8_t SCK, uint8_t CS, GPIO_TypeDef *PORT){
	spi_en(SPI);
	setPin(PORT, MISO, AF);
	setPin(PORT, MISO, AF);
	setPin(PORT, SCK, AF);
	setPin(PORT, CS, OP);

	setAF(PORT, MOSI, 5);
	setAF(PORT, MISO, 5);
	setAF(PORT, SCK, 5);

}

void SPI_config(SPI_TypeDef *SPI,DEV_MODE DMODE, Polarity CPOL, Phase CPHA, Mode MODE, uint8_t BITS){
	if(DMODE == MASTER) SPI->CR1 |= (1<<2);
	else if(DMODE == SLAVE) SPI->CR1 &= ~(1<<2);

	if(CPOL == ZERO) SPI->CR1 &= ~(1<<1);
	else if(CPOL == ONE) SPI->CR1 |= (1<<1);

	if(CPHA==INVERT) SPI->CR1 &= ~(1<<0);
	else if(CPHA == NON_INV) SPI->CR1 |= (1<<0);

	if(MODE == MOTO) SPI->CR2 &= ~(1<<4);
	else if(MODE == TI) SPI->CR2 |= (1<<4);

	SPI->CR1 &= ~(1<<7);
	SPI->CR1 |= (2<<3);
	SPI->CR1 |= (1<<9) | (1<<8);

	if(BITS==8) SPI->CR1 &= ~(1<<11);
	else if(BITS==9) SPI->CR1 |= (1<<11);

	SPI->CR1 |= (1<<6);

}

uint32_t SPI_send(SPI_TypeDef *SPI, GPIO_TypeDef *PORT, uint8_t CS, uint32_t data) {
    pinWrite(PORT, CS, 0);  // Pull CS LOW (Select Slave)

    while(!(SPI->SR & (1<<1))); // Wait until TXE (Transmit Buffer Empty)
    SPI->DR = data; // Send data

    while(!(SPI->SR & (1<<0))); // Wait until RXNE (Receive Buffer Full)
    uint32_t received = SPI->DR; // Read received data

    pinWrite(PORT, CS, 1);  // Pull CS HIGH (Deselect Slave)
    return received;
}
















