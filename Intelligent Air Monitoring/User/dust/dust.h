#ifndef __DUST_H
#define __DUST_H

#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>

#define		DUST_LED_GPIO_PORT			GPIOA
#define		DUST_LED_GPIO_PIN			GPIO_Pin_6
#define		DUST_LED_GPIO_CLK			RCC_APB2Periph_GPIOA

#define		DUST_LED_HIGH 				GPIO_SetBits(DUST_LED_GPIO_PORT,DUST_LED_GPIO_PIN);
#define 	DUST_LED_LOW 				GPIO_ResetBits(DUST_LED_GPIO_PORT,DUST_LED_GPIO_PIN);

#define		DUST_AO_GPIO_PORT			GPIOA
#define		DUST_AO_GPIO_PIN			GPIO_Pin_7
#define		DUST_AO_GPIO_CLK			RCC_APB2Periph_GPIOA

#define   	DUST_ADC_x					ADC1
#define   	DUST_ADC_CLK				RCC_APB2Periph_ADC1
#define   	DUST_ADC_CHANNEL			ADC_Channel_7

static void DUST_ADC_NVIC_Config(void);
void DUST_GPIO_Config(void);
void DUST_ADC_Config(void);
void DUST_ADC_Init(void);
float Get_DUST(void);
uint16_t Get_DUST_Average(uint8_t times);

#endif /*__DUST_H*/
