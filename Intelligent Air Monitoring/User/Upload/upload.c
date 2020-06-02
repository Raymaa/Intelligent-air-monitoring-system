#include "upload.h"
#include "bsp_esp8266.h"
#include "systick.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>

volatile uint8_t ucTcpClosedFlag = 0;
uint8_t ucStatus;


void ESP8266_Config(void)
{
	printf ( "\r\n正在配置 ESP8266 ......\r\n" );

	macESP8266_CH_ENABLE();
	
	ESP8266_AT_Test ();
	
	ESP8266_Net_Mode_Choose ( STA );

	while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	
	
	ESP8266_Enable_MultipleId ( DISABLE );
	
	while ( ! ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	
	while ( ! ESP8266_UnvarnishSend () );
	
	printf ( "\r\n配置 ESP8266 完毕\r\n" );
}

void ESP8266_Upload(char *str)
{
//	printf ( "%s\r\n", str );                                             //打印读取 DHT11 温湿度信息
//	printf ( "\r\n" );

	ESP8266_SendString ( ENABLE, str, 0, Single_ID_0 );               //发送 DHT11 温湿度信息到网络调试助手
	
	Delay_ms ( 50 );
	
	if ( ucTcpClosedFlag )                                             //检测是否失去连接
	{
		ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
		
		do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
		while ( ! ucStatus );
		
		if ( ucStatus == 4 )                                             //确认失去连接后重连
		{
			printf ( "\r\n正在重连热点和服务器 ......\r\n" );
			
			while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
			
			while ( ! ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
			
			printf ( "\r\n重连热点和服务器成功\r\n" );

		}
			
		while ( ! ESP8266_UnvarnishSend () );		
		
	}
}

char * ESP8266_Query(char *str)
{
	char * pStr;
	
//	printf ( "%s", str );                                             //打印读取 DHT11 温湿度信息
//	printf ( "\r\n" );

	ESP8266_SendString ( ENABLE, str, 0, Single_ID_0 );               //发送 DHT11 温湿度信息到网络调试助手
	
	Delay_ms ( 50 );
	
	pStr = ESP8266_ReceiveString(ENABLE);
	Delay_ms ( 50 );
	
//	printf("%s\n",pStr);
	
	if ( ucTcpClosedFlag )                                             //检测是否失去连接
	{
		ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
		
		do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
		while ( ! ucStatus );
		
		if ( ucStatus == 4 )                                             //确认失去连接后重连
		{
			printf ( "\r\n正在重连热点和服务器 ......\r\n" );
			
			while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
			
			while ( ! ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
			
			printf ( "\r\n重连热点和服务器成功\r\n" );

		}
			
		while ( ! ESP8266_UnvarnishSend () );		
		
	}
	
	return pStr;
}


