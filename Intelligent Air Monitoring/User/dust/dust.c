#include "dust.h"

__IO uint32_t DUST_ADC_ConvertedValue;

static void DUST_ADC_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruction;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruction.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_InitStruction.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruction.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStruction.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruction);
}

void DUST_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	
	RCC_APB2PeriphClockCmd(DUST_LED_GPIO_CLK | DUST_AO_GPIO_CLK, ENABLE);

	GPIO_InitStruction.GPIO_Pin = DUST_LED_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DUST_LED_GPIO_PORT, &GPIO_InitStruction);
	
	GPIO_InitStruction.GPIO_Pin = DUST_AO_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(DUST_AO_GPIO_PORT, &GPIO_InitStruction);
	
	DUST_LED_HIGH;
}

void DUST_ADC_Config(void)
{
	ADC_InitTypeDef ADC_InitStruction;
	
	RCC_APB2PeriphClockCmd(DUST_ADC_CLK, ENABLE);
	
	ADC_InitStruction.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruction.ADC_ScanConvMode = DISABLE;
	ADC_InitStruction.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruction.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruction.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruction.ADC_NbrOfChannel = 1;
	
	ADC_Init(DUST_ADC_x, &ADC_InitStruction);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	ADC_RegularChannelConfig(DUST_ADC_x, DUST_ADC_CHANNEL, 1, ADC_SampleTime_239Cycles5);
	
	ADC_ITConfig(DUST_ADC_x, ADC_IT_EOC, ENABLE);
	
	ADC_Cmd(DUST_ADC_x, ENABLE);
	
	ADC_ResetCalibration(DUST_ADC_x);
	
	while(ADC_GetResetCalibrationStatus(DUST_ADC_x));
	
	ADC_StartCalibration(DUST_ADC_x);
	
	while(ADC_GetCalibrationStatus(DUST_ADC_x));
	
	ADC_SoftwareStartConvCmd(DUST_ADC_x, ENABLE);
} 

void DUST_ADC_Init(void)
{
	DUST_GPIO_Config();
	DUST_ADC_NVIC_Config();
	DUST_ADC_Config();
}


float Get_DUST(void)
{
    uint32_t AD_PM;  
	double pm; 
	
    DUST_LED_LOW;
    Delay_us(280);
    AD_PM = DUST_ADC_ConvertedValue;	//PA0
    Delay_us(40);
    DUST_LED_HIGH;
    Delay_us(9680);
    pm = 0.17 * AD_PM - 0.1; //×ª»»¹«Ê½
//    printf("%f\n",pm);
	
	return pm;
} 

uint16_t Get_DUST_Average(uint8_t times)
{
	uint32_t pm_val = 0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		pm_val += Get_DUST();
		Delay_ms(5);
	}
	
	return pm_val/times;
}


