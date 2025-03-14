/*
 * GPIO.c
 *
 *  Created on: Feb 24, 2025
 *      Author: sivap
 */

#include "GPIO.h"

void deelay(){
	for(int i =0;i<1000000;i++);
}

void setPin(GPIO_TypeDef *PORT,uint8_t PIN,uint8_t MODE){

	if(PORT == GPIOA) RCC->AHB1ENR |= ( 1 << 0);
	else if(PORT == GPIOB) RCC->AHB1ENR |= ( 1 << 1);
	else if(PORT == GPIOC) RCC->AHB1ENR |= ( 1 << 2);
	else if(PORT == GPIOD) RCC->AHB1ENR |= ( 1 << 3);
	else if(PORT == GPIOE) RCC->AHB1ENR |= ( 1 << 4);
	else if(PORT == GPIOF) RCC->AHB1ENR |= ( 1 << 5);
	else if(PORT == GPIOG) RCC->AHB1ENR |= ( 1 << 6);
	else if(PORT == GPIOH) RCC->AHB1ENR |= ( 1 << 7);

	PORT->MODER &= ~( 3 << ( PIN * 2 ) );

	PORT->MODER |= ( MODE << ( PIN * 2 ) );

}

void pinWrite(GPIO_TypeDef *PORT,uint8_t PIN, uint8_t STATE){

	if(STATE){
		PORT->ODR |= ( 1 << PIN );
	}
	else{
		PORT->ODR &= ~( 1 << PIN );
	}
}

int pinRead(GPIO_TypeDef *PORT,uint8_t PIN){

	if(PORT->IDR & ( 1 << PIN )){

		return 1 ;
	}
	else{

		return 0 ;
	}
}

void setAF(GPIO_TypeDef *PORT,uint8_t PIN,uint16_t AFNUM){
	if(PIN <= 7){
		PORT->AFR[0] |= (AFNUM << ( PIN * 4 ));
	}
	else{
		PORT->AFR[1] |= (AFNUM << ( (PIN-8)* 4 ));
	}
}

void setPUPDR(GPIO_TypeDef *PORT,uint8_t PIN,uint8_t MODE){

	PORT->PUPDR |= ( MODE << ( PIN * 2 ));

}

void setOPSPEEDR(GPIO_TypeDef *PORT,uint8_t PIN,uint8_t SPEED){

	PORT->OSPEEDR |= ( SPEED << ( PIN * 2));
}


void togglePin(GPIO_TypeDef *PORT,uint8_t PIN){
	while(1){
	PORT->ODR |= (1<<PIN);
	deelay();
	PORT->ODR &= ~(1<<PIN);
	deelay();
	}
}







































