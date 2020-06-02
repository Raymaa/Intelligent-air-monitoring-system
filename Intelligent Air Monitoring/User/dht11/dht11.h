#ifndef __DHT11_H
#define	__DHT11_H

#include "stm32f10x.h"
#include "systick.h"

#define HIGH  1
#define LOW   0

#define DHT11_CLK       RCC_APB2Periph_GPIOC
#define DHT11_PIN     	GPIO_Pin_7                
#define DHT11_PORT		GPIOC

//带参宏，可以像内联函数一样使用,输出高电平或低电平
#define DHT11_DATA_OUT(a)	if (a)	\
								GPIO_SetBits(DHT11_PORT,DHT11_PIN);\
							else		\
								GPIO_ResetBits(DHT11_PORT,DHT11_PIN)
 //读取引脚的电平
#define  DHT11_DATA_IN()	GPIO_ReadInputDataBit(DHT11_PORT,DHT11_PIN)

typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
		                 
}DHT11_Data_TypeDef;

void DHT11_GPIO_Config(void);
static void DHT11_Mode_IPU(void);
static void DHT11_Mode_Out_PP(void);
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
static uint8_t Read_Byte(void);

#endif /* __DHT11_H */







