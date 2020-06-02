#include "beep.h"

void BEEP_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	
	RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK, ENABLE);

	GPIO_InitStruction.GPIO_Pin = BEEP_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStruction);
	
	GPIO_ResetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN);
}


