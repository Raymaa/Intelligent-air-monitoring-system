#include "mq2.h"

void MQ2_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	
	RCC_APB2PeriphClockCmd(MQ2_AO_GPIO_CLK, ENABLE);

	GPIO_InitStruction.GPIO_Pin = MQ2_AO_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(MQ2_AO_GPIO_PORT, &GPIO_InitStruction);
}

void PHOTORESISTOR_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	
	RCC_APB2PeriphClockCmd(PHOTORESISTOR_AO_GPIO_CLK, ENABLE);

	GPIO_InitStruction.GPIO_Pin = PHOTORESISTOR_AO_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(PHOTORESISTOR_AO_GPIO_PORT, &GPIO_InitStruction);
}

void ADC_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStruction;
	
	RCC_APB2PeriphClockCmd(ADC_CLK, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
	
	ADC_InitStruction.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruction.ADC_ScanConvMode = ENABLE;
	ADC_InitStruction.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruction.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruction.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruction.ADC_NbrOfChannel = 2;
	ADC_Init(ADC_x, &ADC_InitStruction);
	
	ADC_ExternalTrigInjectedConvConfig(ADC_x, ADC_ExternalTrigInjecConv_None);
	ADC_InjectedSequencerLengthConfig(ADC_x, 2);
	ADC_InjectedChannelConfig(ADC_x,MQ2_ADC_CHANNEL, 1, ADC_SampleTime_239Cycles5);
	ADC_InjectedChannelConfig(ADC_x,PHOTORESISTOR_ADC_CHANNEL, 2, ADC_SampleTime_239Cycles5);
	ADC_SetInjectedOffset(ADC_x,ADC_InjectedChannel_1,0);
	ADC_SetInjectedOffset(ADC_x,ADC_InjectedChannel_2,0);
	
	ADC_Cmd(ADC_x,ENABLE);
}

void MQ2_PHOTORESISTOR_Init(void)
{
	MQ2_GPIO_Config();
	PHOTORESISTOR_GPIO_Config();
	ADC_Configuration();
}

uint16_t Get_Gas(void)
{
	uint16_t Gas_Buff = 0;
	
	ADC_SoftwareStartInjectedConvCmd(ADC_x,ENABLE);
	while(!ADC_GetFlagStatus(ADC_x,ADC_FLAG_EOC));
	Gas_Buff=ADC_GetInjectedConversionValue(ADC_x, ADC_InjectedChannel_1);
	
	return Gas_Buff;
}

uint16_t Get_Light(void)
{
	uint16_t Light_Buff = 0;
	
	ADC_SoftwareStartInjectedConvCmd(ADC_x,ENABLE);
	while(!ADC_GetFlagStatus(ADC_x,ADC_FLAG_EOC));
	Light_Buff=ADC_GetInjectedConversionValue(ADC_x, ADC_InjectedChannel_2);
	
	return Light_Buff;
}

//uint16_t Get_MQ2_Average(uint8_t times)
//{
//	uint16_t mq2_val = 0;
//	uint8_t t;
//	for(t=0;t<times;t++)
//	{
//		mq2_val += MQ2_ADC_ConvertedValue;
//		Delay_ms(5);
//	}
//	
//	return mq2_val/times;
//}

