#include "photoresistor.h"

__IO uint16_t PHOTORESISTOR_ADC_ConvertedValue;

static void PHOTORESISTOR_ADC_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruction;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruction.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_InitStruction.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruction.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStruction.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruction);
}

void PHOTORESISTOR1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	
	RCC_APB2PeriphClockCmd(PHOTORESISTOR_AO_GPIO_CLK, ENABLE);

	GPIO_InitStruction.GPIO_Pin = PHOTORESISTOR_AO_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(PHOTORESISTOR_AO_GPIO_PORT, &GPIO_InitStruction);
}

void PHOTORESISTOR_ADC_Config(void)
{
	ADC_InitTypeDef ADC_InitStruction;
	
	RCC_APB2PeriphClockCmd(PHOTORESISTOR_ADC_CLK, ENABLE);
	
	ADC_InitStruction.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruction.ADC_ScanConvMode = DISABLE;
	ADC_InitStruction.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruction.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruction.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruction.ADC_NbrOfChannel = 1;
	
	ADC_Init(PHOTORESISTOR_ADC_x, &ADC_InitStruction);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	ADC_RegularChannelConfig(PHOTORESISTOR_ADC_x, PHOTORESISTOR_ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	
	ADC_ITConfig(PHOTORESISTOR_ADC_x, ADC_IT_EOC, ENABLE);
	
	ADC_Cmd(PHOTORESISTOR_ADC_x, ENABLE);
	
	ADC_ResetCalibration(PHOTORESISTOR_ADC_x);
	
	while(ADC_GetResetCalibrationStatus(PHOTORESISTOR_ADC_x));
	
	ADC_StartCalibration(PHOTORESISTOR_ADC_x);
	
	while(ADC_GetCalibrationStatus(PHOTORESISTOR_ADC_x));
	
	ADC_SoftwareStartConvCmd(PHOTORESISTOR_ADC_x, ENABLE);
}

void PHOTORESISTOR_ADC_Init(void)
{
	PHOTORESISTOR_GPIO_Config();
	PHOTORESISTOR_ADC_NVIC_Config();
	PHOTORESISTOR_ADC_Config();
}

