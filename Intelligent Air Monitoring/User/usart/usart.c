#include "usart.h"

static void USART_1_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruction;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStruction.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruction.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruction.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruction.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruction);
}

void UASRT_1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	USART_InitTypeDef USART_InitStruction;
	
	RCC_APB2PeriphClockCmd(USART_1_CLK | USART_1_Tx_GPIO_CLK | USART_1_Rx_GPIO_CLK, ENABLE);

	GPIO_InitStruction.GPIO_Pin = USART_1_Tx_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_1_Tx_GPIO_PORT, &GPIO_InitStruction);
	
	GPIO_InitStruction.GPIO_Pin = USART_1_Rx_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_1_Rx_GPIO_PORT, &GPIO_InitStruction);
	
	USART_InitStruction.USART_BaudRate = 115200;
	USART_InitStruction.USART_WordLength = USART_WordLength_8b;
	USART_InitStruction.USART_StopBits = USART_StopBits_1;
	USART_InitStruction.USART_Parity = USART_Parity_No;
	USART_InitStruction.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART_1, &USART_InitStruction);
	
	USART_1_NVIC_Config();
		
	USART_ITConfig(USART_1, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART_1, ENABLE);
}

int fputc(int ch, FILE *f)
{
	USART_SendData(USART_1, (uint8_t)ch);
	
	while(USART_GetFlagStatus(USART_1, USART_FLAG_TXE) == RESET);  //USART_FLAG_TC
	
	return ch;
}

int fgetc(FILE *f)
{
	while(USART_GetFlagStatus(USART_1, USART_FLAG_RXNE) == RESET);
	
	return (int)USART_ReceiveData(USART_1);
}

