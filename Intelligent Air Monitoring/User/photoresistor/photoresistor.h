#ifndef __PHOTORESISTOR_H
#define __PHOTORESISTOR_H

#include "stm32f10x.h"
#include <stdio.h>

#define		PHOTORESISTOR_AO_GPIO_PORT			GPIOA
#define		PHOTORESISTOR_AO_GPIO_PIN			GPIO_Pin_5
#define		PHOTORESISTOR_AO_GPIO_CLK			RCC_APB2Periph_GPIOA

#define   	PHOTORESISTOR_ADC_x					ADC2
#define   	PHOTORESISTOR_ADC_CLK				RCC_APB2Periph_ADC2
#define   	PHOTORESISTOR_ADC_CHANNEL			ADC_Channel_5

static void PHOTORESISTOR_ADC_NVIC_Config(void);
void PHOTORESISTOR_GPIO_Config(void);
void PHOTORESISTOR_ADC_Config(void);
void PHOTORESISTOR_ADC_Init(void);

#endif /*__PHOTORESISTOR_H*/
