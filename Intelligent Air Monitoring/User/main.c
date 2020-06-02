#include "stm32f10x.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "systick.h"
#include "usart.h"
#include "led.h"
#include "ili9341_lcd.h"
#include "fonts.h"	
#include "beep.h"
#include "bsp_fan.h" 
#include "dht11.h"
#include "adc.h"
#include "bsp_esp8266.h"
#include "upload.h"
#include "bsp_GeneralTim.h" 
#include "cJSON.h"

void LCD_UI_Init(void);

extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];
float ADC_ConvertedValueLocal[NOFCHANEL];
float PPM_Value[NOFCHANEL];
char Buff[100];
DHT11_Data_TypeDef DHT11_Data;
float TandH_Value[2];
int FAN_Gear = 0;
uint8_t FAN_Status = 0;
uint8_t Alarm_Status = 0;
uint8_t WARN_Status = 0;
uint32_t time = 0;         // ms 计时变量 
char cStr [ 100 ] = { 0 };
char pStr [ 100 ] = { 0 };
char * gStr;
char dStr [ 100 ] = { 0 };

int main(void)
{
	SysTick_Init();
	BEEP_Config();
	FAN_GENERAL_TIM_Init();
	LCD_UI_Init();
	LED_Config();
	UASRT_1_Config();
	printf("串口初始化成功！\n");
	DHT11_GPIO_Config();
	ADCx_Init();
	ESP8266_Init();
	ESP8266_Config();
	GENERAL_TIM_Init();
	
	while (1)
	{
		/*===========================温度湿度================================*/
		if( Read_DHT11(&DHT11_Data)==SUCCESS)
		{
			sprintf(Buff,"%d.%d",DHT11_Data.temp_int,DHT11_Data.temp_deci);
			TandH_Value[0] = (float)(DHT11_Data.temp_int + 0.1 * DHT11_Data.temp_deci);
			ILI9341_DisplayStringEx(60,70,18,18,(uint8_t *)Buff,0);
			
			sprintf(Buff,"%d.%d",DHT11_Data.humi_int,DHT11_Data.humi_deci);
			TandH_Value[1] = (float)(DHT11_Data.humi_int + 0.1 * DHT11_Data.humi_deci);
			ILI9341_DisplayStringEx(60,100,18,18,(uint8_t *)Buff,0);		
		}
		
		/*==============================亮度================================*/
		ADC_ConvertedValueLocal[0] = (float)Get_Light_Average(10)/4096*3.3;
		PPM_Value[0] = (float)((3.3-ADC_ConvertedValueLocal[0])/(3.3/160));    		//工作电压：3.3~5V  接3.3V  10K光敏电阻测得光照强度范围为0~160Lux
		
		sprintf(Buff,"%5.1f",PPM_Value[0]);
		ILI9341_DisplayStringEx(60,130,18,18,(uint8_t *)Buff,0);
		/*=======亮度阈值报警======*/
		if(PPM_Value[0] >= 130.0)
		{
			if(Alarm_Status == 0)
			{	
				LED_RED_TOGGLE;
				BEEP_TOGGLE;
				LCD_SetTextColor(RED);
				ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"Light Alarm!    ",0);
				LCD_SetTextColor(WHITE);
				ILI9341_DisplayStringEx(135,220,18,18,(uint8_t *)"THREE             ",0);
				FAN_GEAR_THREE;
				FAN_Status = 3;
				WARN_Status = 3;
				Alarm_Status = 1;
			}else if((Alarm_Status == 1) && (WARN_Status == 3)){
				LED_RED_TOGGLE;
				BEEP_TOGGLE;
				LCD_SetTextColor(RED);
				ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"Light Alarm!    ",0);
				LCD_SetTextColor(WHITE);
				ILI9341_DisplayStringEx(135,220,18,18,(uint8_t *)"THREE             ",0);
				FAN_GEAR_THREE;
				FAN_Status = 3;
				WARN_Status = 3;
				Alarm_Status = 1;
			}
		}
		
		/*==========================可燃气体================================*/
		ADC_ConvertedValueLocal[1] = (float)Get_MQ2_Average(10)/4096*5.0;
		PPM_Value[1] = (float)(ADC_ConvertedValueLocal[1]/(5.0/5000));     	//工作电压：5V  探测浓度范围为100~10000ppm
		
		sprintf(Buff,"%4.f ppm",PPM_Value[1]);
		ILI9341_DisplayStringEx(96,160,18,18,(uint8_t *)Buff,0);
		/*=======可燃气体阈值报警======*/
		if(PPM_Value[1] >= 3000.0)
		{
			if(Alarm_Status == 0)
			{	
				LED_RED_TOGGLE;
				BEEP_TOGGLE;
				LCD_SetTextColor(RED);
				ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"Smoke Alarm!    ",0);
				LCD_SetTextColor(WHITE);
				ILI9341_DisplayStringEx(135,220,18,18,(uint8_t *)"THREE             ",0);
				FAN_GEAR_THREE;
				FAN_Status = 3;
				WARN_Status = 4;
				Alarm_Status = 1;
			}else if((Alarm_Status == 1) && (WARN_Status == 4)){
				LED_RED_TOGGLE;
				BEEP_TOGGLE;
				LCD_SetTextColor(RED);
				ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"Smoke Alarm!    ",0);
				LCD_SetTextColor(WHITE);
				ILI9341_DisplayStringEx(135,220,18,18,(uint8_t *)"THREE             ",0);
				FAN_GEAR_THREE;
				FAN_Status = 3;
				WARN_Status = 4;
				Alarm_Status = 1;
			}
		}
		
		/*==========================PM2.5浓度===============================*/
		ADC_ConvertedValueLocal[2] = (float)Get_DUST_Average(20)/4096*5.0;
		PPM_Value[2] = (float)(ADC_ConvertedValueLocal[2]/(5.0/3000));
		
//		printf("adc: %f ppm: %f\n",ADC_ConvertedValueLocal[2],PPM_Value[2]);
//		sprintf(Buff,"%5.f ug/m3",PPM_Value[2]);
		
		sprintf(Buff,"%4.f ppm",PPM_Value[2]);
		ILI9341_DisplayStringEx(105,190,18,18,(uint8_t *)Buff,0);
		/*=======PM2.5浓度阈值报警======*/
		if(PPM_Value[2] >= 1050.0)
		{
			if(Alarm_Status == 0)
			{	
				LED_RED_TOGGLE;
				BEEP_TOGGLE;
				LCD_SetTextColor(RED);
				ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"PM2.5 Alarm!    ",0);
				LCD_SetTextColor(WHITE);
				ILI9341_DisplayStringEx(135,220,18,18,(uint8_t *)"THREE             ",0);
				FAN_GEAR_THREE;
				FAN_Status = 3;
				WARN_Status = 5;
				Alarm_Status = 1;
			}else if((Alarm_Status == 1) && (WARN_Status == 5)){
				LED_RED_TOGGLE;
				BEEP_TOGGLE;
				LCD_SetTextColor(RED);
				ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"PM2.5 Alarm!    ",0);
				LCD_SetTextColor(WHITE);
				ILI9341_DisplayStringEx(135,220,18,18,(uint8_t *)"THREE             ",0);
				FAN_GEAR_THREE;
				FAN_Status = 3;
				WARN_Status = 5;
				Alarm_Status = 1;
			}
		}
		
		/*==========================恢复初始状态============================*/
		if((PPM_Value[0] < 130.0) && (PPM_Value[1] < 3000.0) && (PPM_Value[2] < 1050.0) && (Alarm_Status == 1))
		{	
			LED_RED(OFF);
			BEEP(OFF);
			ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"Normal          ",0);
			ILI9341_DisplayStringEx(135,220,18,18,(uint8_t *)"OFF            ",0);
			FAN_GEAR_OFF;
			FAN_Status = 0;
			WARN_Status = 0;
			Alarm_Status = 0;
		}
		
		/*==========================上传数据|查询数据==========================*/
		printf("%d\n",time);
		if(time >= 899)
		{
			sprintf ( cStr, "GET /IAMSServer/UploadDataServlet?temp=%3.1f&hum=%d&smoke=%d&bright=%d&pm2_5=%d&fan=%d&warn=%d HTTP/1.1\r\nHost:192.168.1.105:8080\r\n\r\n",TandH_Value[0],(int)TandH_Value[1],(int)PPM_Value[1],(int)PPM_Value[0],(int)PPM_Value[2],FAN_Status,WARN_Status );
//			ESP8266_Upload(cStr);
//			sprintf ( pStr, "POST /IAMSServer/SystemMode HTTP/1.1\r\nConnection:keep-alive\r\nHost:192.168.1.105:8080\r\nContent-Length:2\r\n\r\n{}");
			gStr = ESP8266_Query(cStr);
			gStr = gStr+strlen(gStr)-11;
			strncpy(dStr, gStr, 1);
			dStr[1] = '\0';
			FAN_Gear = dStr[0] - '0';
			printf("GEAR = %d\n",FAN_Gear);
		
			time = 0;
		}
		
		/*===============================换档================================*/
		if(Alarm_Status == 0)
		{	
			if(FAN_Gear == 0)
			{
				LED_RED(OFF);
				BEEP(OFF);
				ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"Normal          ",0);
				ILI9341_DisplayStringEx(135,220,18,18,(uint8_t *)"OFF            ",0);
				FAN_GEAR_OFF;
				FAN_Status = 0;
				WARN_Status = 0;
				Alarm_Status = 0;
			}
			if(FAN_Gear == 1)
			{
				LED_RED(OFF);
				BEEP(OFF);
				ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"Normal          ",0);
				ILI9341_DisplayStringEx(135,220,18,18,(uint8_t *)"ONE            ",0);
				FAN_GEAR_ONE;
				FAN_Status = 1;
				WARN_Status = 0;
				Alarm_Status = 0;
			}
			if(FAN_Gear == 2)
			{
				LED_RED(OFF);
				BEEP(OFF);
				ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"Normal          ",0);
				ILI9341_DisplayStringEx(135,220,18,18,(uint8_t *)"TWO            ",0);
				FAN_GEAR_TWO;
				FAN_Status = 2;
				WARN_Status = 0;
				Alarm_Status = 0;
			}
			if(FAN_Gear == 3)
			{
				LED_RED(OFF);
				BEEP(OFF);
				ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"Normal          ",0);
				ILI9341_DisplayStringEx(135,220,18,18,(uint8_t *)"THREE            ",0);
				FAN_GEAR_THREE;
				FAN_Status = 3;
				WARN_Status = 0;
				Alarm_Status = 0;
			}
		}
	}

}

void LCD_UI_Init(void)
{
	ILI9341_Init(); 
	
	LCD_SetFont(&Font8x16);
	LCD_SetColors(RED,BLACK);

	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);

	ILI9341_DisplayStringEx(40,10,20,20,(uint8_t *)"智能空气监控系统",0);
	LCD_SetTextColor(WHITE);
	ILI9341_DisplayStringEx(15,70,18,18,(uint8_t *)"温度：    ℃",0);
	ILI9341_DisplayStringEx(15,100,18,18,(uint8_t *)"湿度：    %",0);
	ILI9341_DisplayStringEx(15,130,18,18,(uint8_t *)"亮度：     lx",0);
	ILI9341_DisplayStringEx(15,160,18,18,(uint8_t *)"可燃气体：",0);
	ILI9341_DisplayStringEx(15,190,18,18,(uint8_t *)"PM2.5浓度：",0);
	ILI9341_DisplayStringEx(15,220,18,18,(uint8_t *)"风扇运行状态：OFF     ",0);
	ILI9341_DisplayStringEx(15,250,18,18,(uint8_t *)"报警情况：      ",0);
	ILI9341_DisplayStringEx(15,280,18,18,(uint8_t *)"Normal                   ",0);
}


