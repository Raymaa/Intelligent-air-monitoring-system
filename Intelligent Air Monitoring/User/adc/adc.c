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
	
	// 复位DMA控制器
	DMA_DeInit(ADC_DMA_CHANNEL);
	
	// 配置 DMA 初始化结构体
	// 外设基址为：ADC 数据寄存器地址
	DMA_InitStruction.DMA_PeripheralBaseAddr = (uint32_t) ( & ( ADC_x->DR ) );
	
	// 存储器地址
	DMA_InitStruction.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue;
	
	// 数据源来自外设
	DMA_InitStruction.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// 缓冲区大小，应该等于数据目的地的大小
	DMA_InitStruction.DMA_BufferSize = NOFCHANEL;
	
	// 外设寄存器只有一个，地址不用递增
	DMA_InitStruction.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// 存储器地址递增
	DMA_InitStruction.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	
	// 外设数据大小为半字，即两个字节
	DMA_InitStruction.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// 内存数据大小也为半字，跟外设数据大小相同
	DMA_InitStruction.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// 循环传输模式
	DMA_InitStruction.DMA_Mode = DMA_Mode_Circular;	

	// DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStruction.DMA_Priority = DMA_Priority_High;
	
	// 禁止存储器到存储器模式，因为是从外设到存储器
	DMA_InitStruction.DMA_M2M = DMA_M2M_Disable;
	
	// 初始化DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStruction);
	
	// 使能 DMA 通道
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	// ADC 模式配置
	// 只使用一个ADC，属于单模式
	ADC_InitStruction.ADC_Mode = ADC_Mode_Independent;
	
	// 扫描模式
	ADC_InitStruction.ADC_ScanConvMode = ENABLE ; 

	// 连续转换模式
	ADC_InitStruction.ADC_ContinuousConvMode = ENABLE;

	// 不用外部触发转换，软件开启即可
	ADC_InitStruction.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;

	// 转换结果右对齐
	ADC_InitStruction.ADC_DataAlign = ADC_DataAlign_Right;
	
	// 转换通道个数
	ADC_InitStruction.ADC_NbrOfChannel = NOFCHANEL;	
		
	// 初始化ADC
	ADC_Init(ADC_x, &ADC_InitStruction);
	
	// 配置ADC时钟Ｎ狿CLK2的8分频，即9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	// 配置ADC 通道的转换顺序和采样时间
	ADC_RegularChannelConfig(ADC_x, PHOTORESISTOR_ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, MQ2_ADC_CHANNEL, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, DUST_ADC_CHANNEL, 3, ADC_SampleTime_55Cycles5);
	
	// 使能ADC DMA 请求
	ADC_DMACmd(ADC_x, ENABLE);
	
	// 开启ADC ，并开始转换
	ADC_Cmd(ADC_x, ENABLE);
	
	// 初始化ADC 校准寄存器  
	ADC_ResetCalibration(ADC_x);
	// 等待校准寄存器初始化完成
	while(ADC_GetResetCalibrationStatus(ADC_x));
	
	// ADC开始校准
	ADC_StartCalibration(ADC_x);
	// 等待校准完成
	while(ADC_GetCalibrationStatus(ADC_x));
	
	// 由于没有采用外部触发，所以使用软件触发ADC转换 
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
//	pm = 0.17 * AD_PM - 0.1; //转换公式
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


