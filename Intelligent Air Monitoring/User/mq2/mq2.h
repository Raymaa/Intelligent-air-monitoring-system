#ifndef __MQ2_H
#define __MQ2_H

#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>

#define		PHOTORESISTOR_AO_GPIO_PORT			GPIOB
#define		PHOTORESISTOR_AO_GPIO_PIN			GPIO_Pin_1
#define		PHOTORESISTOR_AO_GPIO_CLK			RCC_APB2Periph_GPIOB
#define   	PHOTORESISTOR_ADC_CHANNEL			ADC_Channel_9

#define		MQ2_AO_GPIO_PORT					GPIOA
#define		MQ2_AO_GPIO_PIN						GPIO_Pin_4
#define		MQ2_AO_GPIO_CLK						RCC_APB2Periph_GPIOA
#define   	MQ2_ADC_CHANNEL						ADC_Channel_4

#define   	ADC_x								ADC1
#define   	ADC_CLK								RCC_APB2Periph_ADC1



void MQ2_GPIO_Config(void);
void PHOTORESISTOR_GPIO_Config(void);
void ADC_Configuration(void);
void MQ2_PHOTORESISTOR_Init(void);
uint16_t Get_Gas(void);
uint16_t Get_Light(void);

#endif /*__MQ2_H*/
