#ifndef __ADC_H
#define	__ADC_H

#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOC

// ע��
// 1-PC0 ��ָ��������ӵ��Ƿ�������Ĭ�ϱ�����
// 2-PC0 ��ָ��������ӵ���SPI FLASH�� Ƭѡ��Ĭ�ϱ�����
// ���� PC0 �� ADC ת��ͨ����ʱ�򣬽�����ܻ������

// ת��ͨ������
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


// ADC1 ��Ӧ DMA1ͨ��1��ADC3��ӦDMA2ͨ��5��ADC2û��DMA����
#define		DUST_LED_GPIO_PORT			GPIOC
#define		DUST_LED_GPIO_PIN			GPIO_Pin_6
#define		DUST_LED_GPIO_CLK			RCC_APB2Periph_GPIOC

#define		DUST_LED_HIGH 				GPIO_SetBits(DUST_LED_GPIO_PORT,DUST_LED_GPIO_PIN);
#define 	DUST_LED_LOW 				GPIO_ResetBits(DUST_LED_GPIO_PORT,DUST_LED_GPIO_PIN);


// ADC1 ��Ӧ DMA1ͨ��1��ADC3��ӦDMA2ͨ��5��ADC2û��DMA����
#define    ADC_x                         ADC1
#define    ADC_DMA_CHANNEL               DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA1


/**************************��������********************************/
void ADCx_Init(void);
uint16_t Get_DUST(void);
uint16_t Get_DUST_Average(uint8_t times);
uint16_t Get_MQ2_Average(uint8_t times);
uint16_t Get_Light_Average(uint8_t times);

#endif /* __ADC_H */

