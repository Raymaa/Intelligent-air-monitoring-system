#ifndef  __TEST_H
#define	 __TEST_H



#include "stm32f10x.h"



/********************************** 用户需要设置的参数**********************************/
//要连接的热点的名称，即WIFI名称
#define      macUser_ESP8266_ApSsid           "1000004" 

//要连接的热点的密钥
#define      macUser_ESP8266_ApPwd            "wu486579123." 

//要连接的服务器的 IP，即电脑的IP
#define      macUser_ESP8266_TcpServer_IP     "192.168.1.101" 

//要连接的服务器的端口
#define      macUser_ESP8266_TcpServer_Port    "8080"         



/********************************** 外部全局变量 ***************************************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** 测试函数声明 ***************************************/
void ESP8266_Config(void);
void ESP8266_Upload(char *str);
char * ESP8266_Query(char *str);



#endif

