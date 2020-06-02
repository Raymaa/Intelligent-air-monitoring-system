#include "led.h"

void LED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	
	RCC_APB2PeriphClockCmd(LED_R_GPIO_CLK | LED_G_GPIO_CLK | LED_B_GPIO_CLK, ENABLE);

	GPIO_InitStruction.GPIO_Pin = LED_R_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruction);
	
	GPIO_InitStruction.GPIO_Pin = LED_G_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruction);
	
	GPIO_InitStruction.GPIO_Pin = LED_B_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruction);
	
	GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);
	GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
	GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
}


