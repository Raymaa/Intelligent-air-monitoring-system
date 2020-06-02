#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

#define 	USART_1					USART1
#define		USART_1_CLK				RCC_APB2Periph_USART1

#define		USART_1_Tx_GPIO_PORT	GPIOA
#define		USART_1_Tx_GPIO_PIN		GPIO_Pin_9
#define		USART_1_Tx_GPIO_CLK		RCC_APB2Periph_GPIOA

#define		USART_1_Rx_GPIO_PORT	GPIOA
#define		USART_1_Rx_GPIO_PIN		GPIO_Pin_10
#define		USART_1_Rx_GPIO_CLK		RCC_APB2Periph_GPIOA

static void USART_1_NVIC_Config(void);
void UASRT_1_Config(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif /*__USART_H*/
