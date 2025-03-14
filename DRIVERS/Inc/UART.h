/*
 * UART.h
 *
 *  Created on: Mar 8, 2025
 *      Author: sivap
 */

#ifndef INC_UART_H_
#define INC_UART_H_
#include "stm32f446xx.h"
#include "GPIO.h"
#include <string.h>

#define NOP 3
#define EVEN 0
#define  ODD 1

#define STOP_1   0
#define STOP_0_5 1
#define STOP_2   2
#define STOP_1_5 3


void USART_init(USART_TypeDef *USART, GPIO_TypeDef *PORT, uint8_t RX, uint8_t TX,uint8_t AF_NUM, uint8_t WORD_LENGTH,uint8_t PARITY,uint8_t STOP_BIT, uint32_t BAUDRATE);
void USART_sendChar(USART_TypeDef *USART,char data);
void USART_sendString(USART_TypeDef *USART,char *data,uint32_t size);
char USART_readChar(USART_TypeDef *USART);
void USART_readString(USART_TypeDef *USART,char *buffer, uint16_t max_length);

void Serial_begin(uint32_t BAUDRATE);
void Serial_print(char *data);
void Serial_println(char *data);
#endif /* INC_UART_H_ */
