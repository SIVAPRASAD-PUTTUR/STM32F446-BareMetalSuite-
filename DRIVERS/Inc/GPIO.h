/*
 * GPIO.h
 *
 *  Created on: Feb 24, 2025
 *      Author: sivap
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_
#include <stm32f446xx.h>

//OUTPUT MODES
#define NPUPD 0
#define PLU 1
#define PLD 2
#define RES 3

//GPIOX MODES
#define IP 0
#define OP 1
#define AF 2
#define AM 3

//SPEED MODES
#define LS 0
#define MS 1
#define FS 2
#define HS 3

//PIN STATES
#define OFF 0
#define ON 1

#define PA  GPIOA
#define PB  GPIOB
#define PC  GPIOC
#define PD  GPIOD
#define PE  GPIOE
#define PF  GPIOF
#define PG  GPIOG
#define PH  GPIOH


void setPin(GPIO_TypeDef *PORT,uint8_t PIN,uint8_t MODE);
void pinWrite(GPIO_TypeDef *PORT,uint8_t PIN, uint8_t STATE);
int pinRead(GPIO_TypeDef *PORT,uint8_t PIN);
void setAF(GPIO_TypeDef *PORT,uint8_t PIN,uint16_t AFNUM);
void setPUPDR(GPIO_TypeDef *PORT,uint8_t PIN,uint8_t MODE);
void setOPSPEEDR(GPIO_TypeDef *PORT,uint8_t PIN,uint8_t SPEED);
void togglePin(GPIO_TypeDef *PORT,uint8_t PIN);

#endif /* INC_GPIO_H_ */
