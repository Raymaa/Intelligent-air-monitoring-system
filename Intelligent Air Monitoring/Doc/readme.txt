��ҵ���
https://blog.csdn.net/GSH_Hello_World/article/details/72627990

******************************************************************����*******************************************************************

	������			VCC			GND			AO/DATA                         ����
		
	 DHT11 			3.3						  PC7						
	 ����			3.3						  PC2							ģ�ⱨ��
	 MQ-2			5.0						  PA4							��Χ0~5000 ����3000����
	 PM2.5			5.0						  PC4( LED PC6 )				��Χ0~3000 ����1050����
	��������         5.0                       ENA->PA3
											  IN1->PC3
											  IN2->PC5

*****************************************************************************************************************************************

DHT11
while(1)
{
	if( Read_DHT11(&DHT11_Data)==SUCCESS)
	{
		printf("\r\n�¶ȣ�%d.%d ��  ʪ�ȣ�%d.%d ��RH\r\n",DHT11_Data.temp_int,DHT11_Data.temp_deci,DHT11_Data.humi_int,DHT11_Data.humi_deci);
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

GP2Y1010AU0F�ҳ�������

  ͼ1Ϊ�������벨�Σ�����Ϊ10ms���ߵ�ƽΪ0.32ms

  ͼ2ΪAD����ʱ����ͼ��֪�������������ص�����ķ�ֵ��ʱ��Ϊ280us���ң����ڴ�ʱ���в�������Ϊ�����ߵ�ƽ������ʱ��Ϊ320us��
  �����ڴ򿪺��ⷢ�������280us�������Ȼ����ʱ40us��رպ��ⷢ������ܣ��������ʱ9680us(���벨�ε�����Ϊ10ms)�����ʵ����һ�������Ĺ���
  
��ͼ���� datasheet������Կ����۳��������������ѹ�Ǽ��������Եġ�dustDensity = 0.17 * calcVoltage - 0.1; 
�����ʽ���߽���ת�������ģ�����Chris Nafis����
����dustDensity�Ƿ۳��ܶ�ֵ����λmg/m3��calcVoltage�������ѹֵ��
while (1)
{
	pm=Get_DUST_Average(10);
	printf("\r\n The current AD value = 0x%04X \r\n",DUST_ADC_ConvertedValue); 
	printf("\t PM2.5 = %f ug/m3",(float)pm);
	Delay_ms(500);
}


����
http://tieba.baidu.com/p/4238265567#81394034746l
����+��ֱ�ӽ���5v�ϣ�-�����������ܼ��缫C��
�����ܷ��伫E��0V,����B��һ��gpio
���ݽ��ڷ���-����0v��5v���ˣ�����õ�����ע�⼫�ԡ�