#include "adc.h"

__IO uint16_t ADC_ConvertedValue[NOFCHANEL]={0,0,0};


static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	
	RCC_APB2PeriphClockCmd(MQ2_AO_GPIO_CLK | PHOTORESISTOR_AO_GPIO_CLK | DUST_AO_GPIO_CLK | DUST_LED_GPIO_CLK, ENABLE);
	
	GPIO_InitStruction.GPIO_Pin = MQ2_AO_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(MQ2_AO_GPIO_PORT, &GPIO_InitStruction);	

	GPIO_InitStruction.GPIO_Pin = PHOTORESISTOR_AO_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(PHOTORESISTOR_AO_GPIO_PORT, &GPIO_InitStruction);	
	
	GPIO_InitStruction.GPIO_Pin = DUST_AO_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(DUST_AO_GPIO_PORT, &GPIO_InitStruction);	
	
	GPIO_InitStruction.GPIO_Pin = DUST_LED_GPIO_PIN;
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DUST_LED_GPIO_PORT, &GPIO_InitStruction);	
}

static void ADCx_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStruction;
	ADC_InitTypeDef ADC_InitStruction;
	
	RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(ADC_CLK, ENABLE);
	
	// ��λDMA������
	DMA_DeInit(ADC_DMA_CHANNEL);
	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStruction.DMA_PeripheralBaseAddr = (uint32_t) ( & ( ADC_x->DR ) );
	
	// �洢����ַ
	DMA_InitStruction.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue;
	
	// ����Դ��������
	DMA_InitStruction.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// ��������С��Ӧ�õ�������Ŀ�ĵصĴ�С
	DMA_InitStruction.DMA_BufferSize = NOFCHANEL;
	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStruction.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// �洢����ַ����
	DMA_InitStruction.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	
	// �������ݴ�СΪ���֣��������ֽ�
	DMA_InitStruction.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// �ڴ����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStruction.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// ѭ������ģʽ
	DMA_InitStruction.DMA_Mode = DMA_Mode_Circular;	

	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStruction.DMA_Priority = DMA_Priority_High;
	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStruction.DMA_M2M = DMA_M2M_Disable;
	
	// ��ʼ��DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStruction);
	
	// ʹ�� DMA ͨ��
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	// ADC ģʽ����
	// ֻʹ��һ��ADC�����ڵ�ģʽ
	ADC_InitStruction.ADC_Mode = ADC_Mode_Independent;
	
	// ɨ��ģʽ
	ADC_InitStruction.ADC_ScanConvMode = ENABLE ; 

	// ����ת��ģʽ
	ADC_InitStruction.ADC_ContinuousConvMode = ENABLE;

	// �����ⲿ����ת���������������
	ADC_InitStruction.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;

	// ת������Ҷ���
	ADC_InitStruction.ADC_DataAlign = ADC_DataAlign_Right;
	
	// ת��ͨ������
	ADC_InitStruction.ADC_NbrOfChannel = NOFCHANEL;	
		
	// ��ʼ��ADC
	ADC_Init(ADC_x, &ADC_InitStruction);
	
	// ����ADCʱ�ӣΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	// ����ADC ͨ����ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC_x, PHOTORESISTOR_ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, MQ2_ADC_CHANNEL, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, DUST_ADC_CHANNEL, 3, ADC_SampleTime_55Cycles5);
	
	// ʹ��ADC DMA ����
	ADC_DMACmd(ADC_x, ENABLE);
	
	// ����ADC ������ʼת��
	ADC_Cmd(ADC_x, ENABLE);
	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADC_x);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADC_x));
	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADC_x);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADC_x));
	
	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}

void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
}

uint16_t Get_Light_Average(uint8_t times)
{
	uint32_t pm_val = 0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		pm_val += ADC_ConvertedValue[0];
		Delay_ms(5);
	}
	
	return pm_val/times;
}

uint16_t Get_MQ2_Average(uint8_t times)
{
	uint8_t t;
	uint32_t pm_val = 0;
	for(t=0;t<times;t++)
	{
		pm_val += ADC_ConvertedValue[1];
		Delay_ms(5);
	}
	
	return pm_val/times;
}

uint16_t Get_DUST(void)
{
    float AD_PM;  
//	double pm; 
	
    DUST_LED_LOW;
    Delay_us(280);
    AD_PM = ADC_ConvertedValue[2];
    Delay_us(40);
    DUST_LED_HIGH;
    Delay_us(9680);
//	pm = 0.17 * AD_PM - 0.1; //ת����ʽ
//	printf("AD_PM = %f\n",AD_PM);

	return AD_PM;
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


