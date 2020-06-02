毕业设计
https://blog.csdn.net/GSH_Hello_World/article/details/72627990

******************************************************************接线*******************************************************************

	传感器			VCC			GND			AO/DATA                         描述
		
	 DHT11 			3.3						  PC7						
	 亮度			3.3						  PC2							模拟报警
	 MQ-2			5.0						  PA4							范围0~5000 超过3000报警
	 PM2.5			5.0						  PC4( LED PC6 )				范围0~3000 超过1050报警
	驱动风扇         5.0                       ENA->PA3
											  IN1->PC3
											  IN2->PC5

*****************************************************************************************************************************************

DHT11
while(1)
{
	if( Read_DHT11(&DHT11_Data)==SUCCESS)
	{
		printf("\r\n温度：%d.%d ℃  湿度：%d.%d ％RH\r\n",DHT11_Data.temp_int,DHT11_Data.temp_deci,DHT11_Data.humi_int,DHT11_Data.humi_deci);
	}
	else
	{
		printf("Read DHT11 ERROR\r\n");
	}
	Delay_ms(2000);
}

MQ2
while (1)
{
	MQ2_Value = (float)MQ2_ADC_ConvertedValue/4096*3.3;
	MQ2_PPM = (float)(((MQ2_Value - 1) / 0.1) * 200);
	
	printf("\r\n The current AD value = 0x%04X \r\n",MQ2_ADC_ConvertedValue); 
	printf("\r\n The current AD value = %f V \r\n",MQ2_Value); 
	printf("\r\n The current AD value = %.2f ppm \r\n",MQ2_PPM);
	printf("\r\n\r\n");

	Delay_ms(2000);
}

PHOTORESISTOR
while (1)
{
	PHOTORESISTOR_Value = (float)PHOTORESISTOR_ADC_ConvertedValue/4096*3.3;
	PHOTORESISTOR_PPM = (float)(((PHOTORESISTOR_Value - 1) / 0.1) * 200);
	
	printf("\r\n The current AD value = 0x%04X \r\n",PHOTORESISTOR_ADC_ConvertedValue); 
	printf("\r\n The current AD value = %f V \r\n",PHOTORESISTOR_Value); 
	printf("\r\n The current AD value = %.2f ppm \r\n",PHOTORESISTOR_PPM);
	printf("\r\n\r\n");

	Delay_ms(2000);
}

GP2Y1010AU0F灰尘传感器

  图1为脉冲输入波形，周期为10ms，高电平为0.32ms

  图2为AD采样时序，由图可知，在输入上升沿到输出的峰值，时间为280us左右，就在此时进行采样，因为整个高电平持续的时间为320us，
  所以在打开红外发光二极管280us后采样，然后延时40us后关闭红外发光二极管，最后再延时9680us(输入波形的周期为10ms)，这就实现了一次完整的工作
  
下图截自 datasheet，你可以看出粉尘传感器的输出电压是几乎呈线性的。dustDensity = 0.17 * calcVoltage - 0.1; 
这个公式曲线近似转换过来的（来自Chris Nafis）。
这里dustDensity是粉尘密度值，单位mg/m3。calcVoltage是输出电压值。
while (1)
{
	pm=Get_DUST_Average(10);
	printf("\r\n The current AD value = 0x%04X \r\n",DUST_ADC_ConvertedValue); 
	printf("\t PM2.5 = %f ug/m3",(float)pm);
	Delay_ms(500);
}


风扇
http://tieba.baidu.com/p/4238265567#81394034746l
风扇+极直接接在5v上，-极接在三极管集电极C。
三极管发射极E接0V,基极B接一个gpio
电容接在风扇-极和0v或5v两端，如果用电解电容注意极性。