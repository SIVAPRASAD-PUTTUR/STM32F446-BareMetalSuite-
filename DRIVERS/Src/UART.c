/*
 * UART.c
 *
 *  Created on: Mar 8, 2025
 *      Author: sivap
 */

#include "UART.h"

void del(){
	for(int i=0;i<10000;i++);
}

void USART_EN(USART_TypeDef *USART){
	if(USART == USART1) RCC->APB2ENR |= (1<<4);
	else if (USART == USART2) RCC->APB1ENR |= (1<<17);
	else if (USART == USART3) RCC->APB1ENR |= (1<<18);
	else if (USART == UART4) RCC->APB1ENR |= (1<<19);
	else if (USART == UART5) RCC->APB1ENR |= (1<<20);
	else if (USART == USART6) RCC->APB2ENR |= (1<<5);
}

void USART_init(USART_TypeDef *USART, GPIO_TypeDef *PORT, uint8_t RX, uint8_t TX,uint8_t AF_NUM, uint8_t WORD_LENGTH,uint8_t PARITY,uint8_t STOP_BIT, uint32_t BAUDRATE)
{
	USART_EN(USART);
	setPin(PORT, RX, AF);
	setPin(PORT, TX, AF);
	setAF(PORT, RX, AF_NUM);
	setAF(PORT, TX, AF_NUM);

	USART->CR1 |= (1<<13);
	USART->CR1 |= (1<<2) | (1<<3);
	USART->BRR = (16000000 / BAUDRATE);

	// TO SET PARITY
	if(PARITY == EVEN){
		USART->CR1 |= (1<<10);
		USART->CR1 &= ~(1<<9);
	}
	else if(PARITY == ODD) USART->CR1 |= (1<<10)|(1<<9);
	else if(PARITY == NOP) USART->CR1 &= ~(1<<10);

	// TO SET WORD LENGTH
	if(WORD_LENGTH == 8)USART->CR1 &= ~(1<<12);
	else if(WORD_LENGTH == 9)USART->CR1 |= (1<<12);

	// TO SET STOP BITS
	USART->CR2 &= ~(3 << 12);  // Clear previous stop bit setting
	USART->CR2 |= (STOP_BIT << 12);

}

void USART_sendChar(USART_TypeDef *USART,char data){
	while(!(USART->SR & (1<<7)));
	USART->DR = data;
	while(!(USART->SR & (1<<6)));
}



char USART_readChar(USART_TypeDef *USART){
	while(!(USART->SR & (1<<5)));
	char ch = USART->DR;
	return ch ;
}

void USART_sendString(USART_TypeDef *USART,char *data, uint32_t size){
	for(int i = 0; i<size;i++){
		while (!(USART->SR & (1 << 7)));
		USART->DR = *data++ ;
	}
}

void USART_readString(USART_TypeDef *USART, char *buffer, uint16_t max_length) {
    uint16_t i = 0;
    uint32_t timeout_count = 10;
    uint32_t timeout = 0;

    while (i < (max_length - 1)) {
        if (USART->SR & (1 << 5)) {  // Check if data is available (RXNE set)
            buffer[i++] = USART_readChar(USART);  // Read data
            timeout = 0;  // Reset timeout when new data is received
        } else {
            timeout++;  // Increment timeout counter if no data

        }

        if (timeout > timeout_count) {  // Break if timeout reaches limit
            break;
        }
    }

    buffer[i] = '\0';  // Null terminate the string
}

void Serial_begin(uint32_t BAUDRATE){
	USART_init(USART3, PD, 9, 8, 7, 8, NOP, STOP_1, BAUDRATE);
}


void Serial_print(char *data){
	uint32_t siz = strlen(data);
	USART_sendString(USART3, data, siz);
}

void Serial_println(char *data){
	USART_sendString(USART3, data, strlen(data));
	USART_sendString(USART3, "\n", strlen("\n"));
}








