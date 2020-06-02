#ifndef __ADC_H
#define	__ADC_H

#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>

// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC1输入通道（引脚）配置**************************/
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOC

// 注意
// 1-PC0 在指南者里面接的是蜂鸣器，默认被拉低
// 2-PC0 在指南者里面接的是SPI FLASH的 片选，默认被拉高
// 所以 PC0 做 ADC 转换通道的时候，结果可能会有误差

// 转换通道个数
#define     NOFCHANEL							3

#define		PHOTORESISTOR_AO_GPIO_PORT			GPIOC
#define		PHOTORESISTOR_AO_GPIO_PIN			GPIO_Pin_2
#define		PHOTORESISTOR_AO_GPIO_CLK			RCC_APB2Periph_GPIOC
#define   	PHOTORESISTOR_ADC_CHANNEL			ADC_Channel_12

#define		MQ2_AO_GPIO_PORT					GPIOA
#define		MQ2_AO_GPIO_PIN						GPIO_Pin_4
#define		MQ2_AO_GPIO_CLK						RCC_APB2Periph_GPIOA
#define   	MQ2_ADC_CHANNEL						ADC_Channel_4

#define		DUST_AO_GPIO_PORT					GPIOC
#define		DUST_AO_GPIO_PIN					GPIO_Pin_4
#define		DUST_AO_GPIO_CLK					RCC_APB2Periph_GPIOC
#define   	DUST_ADC_CHANNEL					ADC_Channel_14


// ADC1 对应 DMA1通道1，ADC3对应DMA2通道5，ADC2没有DMA功能
#define		DUST_LED_GPIO_PORT			GPIOC
#define		DUST_LED_GPIO_PIN			GPIO_Pin_6
#define		DUST_LED_GPIO_CLK			RCC_APB2Periph_GPIOC

#define		DUST_LED_HIGH 				GPIO_SetBits(DUST_LED_GPIO_PORT,DUST_LED_GPIO_PIN);
#define 	DUST_LED_LOW 				GPIO_ResetBits(DUST_LED_GPIO_PORT,DUST_LED_GPIO_PIN);


// ADC1 对应 DMA1通道1，ADC3对应DMA2通道5，ADC2没有DMA功能
#define    ADC_x                         ADC1
#define    ADC_DMA_CHANNEL               DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA1


/**************************函数声明********************************/
void ADCx_Init(void);
uint16_t Get_DUST(void);
uint16_t Get_DUST_Average(uint8_t times);
uint16_t Get_MQ2_Average(uint8_t times);
uint16_t Get_Light_Average(uint8_t times);

#endif /* __ADC_H */

