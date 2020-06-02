#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"
#include <stdio.h>

#define		LED_R_GPIO_PORT			GPIOB
#define		LED_R_GPIO_PIN			GPIO_Pin_5
#define		LED_R_GPIO_CLK			RCC_APB2Periph_GPIOB

#define		LED_G_GPIO_PORT			GPIOB
#define		LED_G_GPIO_PIN			GPIO_Pin_0
#define		LED_G_GPIO_CLK			RCC_APB2Periph_GPIOB

#define		LED_B_GPIO_PORT			GPIOB
#define		LED_B_GPIO_PIN			GPIO_Pin_1
#define		LED_B_GPIO_CLK			RCC_APB2Periph_GPIOB

#define 	ON		1
#define 	OFF		0

#define		LED_RED_TOGGLE		 	LED_R_GPIO_PORT->ODR ^= LED_R_GPIO_PIN
#define		LED_GREEN_TOGGLE		LED_G_GPIO_PORT->ODR ^= LED_G_GPIO_PIN
#define		LED_BLUE_TOGGLE		 	LED_B_GPIO_PORT->ODR ^= LED_B_GPIO_PIN

#define		LED_RED(a)		if(a)\
							{\
								GPIO_ResetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);\
								GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);\
								GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);\
							}\
							else\
							{\
								GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);\
								GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);\
								GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);\
							}
#define		LED_GREEN(a)	if(a)\
							{\
								GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);\
								GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);\
								GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);\
							}\
							else\
							{\
								GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);\
								GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);\
								GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);\
							}
#define		LED_BLUE(a)		if(a)\
							{\
								GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);\
								GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);\
								GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);\
							}\
							else\
							{\
								GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);\
								GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);\
								GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);\
							}
							
void LED_Config(void);

#endif /*__LED_H*/
