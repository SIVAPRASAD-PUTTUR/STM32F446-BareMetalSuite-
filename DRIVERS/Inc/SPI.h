/*
 * SPI.h
 *
 *  Created on: Mar 10, 2025
 *      Author: sivap
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_
#include "stm32f446xx.h"
#include "GPIO.h"

typedef enum{
	MASTER,
	SLAVE
}DEV_MODE;

typedef  enum{
	INVERT,
	NON_INV
}Phase;

typedef enum{
	ZERO,
	ONE
}Polarity;

typedef enum{
	MOTO,
	TI
}Mode;

void SPI_init(SPI_TypeDef *SPI, uint8_t MOSI, uint8_t MISO, uint8_t SCK, uint8_t CS, GPIO_TypeDef *PORT);
void SPI_config(SPI_TypeDef *SPI,DEV_MODE DMODE, Polarity CPOL, Phase CPHA, Mode MODE, uint8_t BITS);
uint32_t SPI_send(SPI_TypeDef *SPI, GPIO_TypeDef *PORT, uint8_t CS, uint32_t data) ;


#endif /* INC_SPI_H_ */
