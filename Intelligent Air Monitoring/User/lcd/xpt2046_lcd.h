#ifndef __BSP_XPT2046_LCD_H
#define	__BSP_XPT2046_LCD_H


#include "stm32f10x.h"



/******************************* XPT2046 �������ж����Ŷ��� ***************************/
#define             macXPT2046_EXTI_GPIO_CLK                        RCC_APB2Periph_GPIOF   
#define             macXPT2046_EXTI_GPIO_PORT                       GPIOF
#define             macXPT2046_EXTI_GPIO_PIN                        GPIO_Pin_9
#define             macXPT2046_EXTI_SOURCE_PORT                     GPIO_PortSourceGPIOF
#define             macXPT2046_EXTI_SOURCE_PIN                      GPIO_PinSource9
#define             macXPT2046_EXTI_LINE                            EXTI_Line9
#define             macXPT2046_EXTI_IRQ                             EXTI9_5_IRQn
#define             macXPT2046_EXTI_INT_FUNCTION                    EXTI9_5_IRQHandler

#define             macXPT2046_EXTI_ActiveLevel                     0
#define             macXPT2046_EXTI_Read()                          GPIO_ReadInputDataBit ( macXPT2046_EXTI_GPIO_PORT, macXPT2046_EXTI_GPIO_PIN )



/******************************* XPT2046 ������ģ��SPI���Ŷ��� ***************************/
#define             macXPT2046_SPI_GPIO_CLK                         RCC_APB2Periph_GPIOF| RCC_APB2Periph_GPIOG

#define             macXPT2046_SPI_CS_PIN		                        GPIO_Pin_10
#define             macXPT2046_SPI_CS_PORT		                      GPIOF

#define	            macXPT2046_SPI_CLK_PIN	                        GPIO_Pin_7
#define             macXPT2046_SPI_CLK_PORT	                        GPIOG

#define	            macXPT2046_SPI_MOSI_PIN	                        GPIO_Pin_11
#define	            macXPT2046_SPI_MOSI_PORT	                      GPIOF

#define	            macXPT2046_SPI_MF103-ָ����_PIN	                        GPIO_Pin_6
#define	            macXPT2046_SPI_MF103-ָ����_PORT	                      GPIOF


#define             macXPT2046_CS_ENABLE()                          GPIO_SetBits ( macXPT2046_SPI_CS_PORT, macXPT2046_SPI_CS_PIN )    
#define             macXPT2046_CS_DISABLE()                         GPIO_ResetBits ( macXPT2046_SPI_CS_PORT, macXPT2046_SPI_CS_PIN )  

#define             macXPT2046_CLK_HIGH()                           GPIO_SetBits ( macXPT2046_SPI_CLK_PORT, macXPT2046_SPI_CLK_PIN )    
#define             macXPT2046_CLK_LOW()                            GPIO_ResetBits ( macXPT2046_SPI_CLK_PORT, macXPT2046_SPI_CLK_PIN ) 

#define             macXPT2046_MOSI_1()                             GPIO_SetBits ( macXPT2046_SPI_MOSI_PORT, macXPT2046_SPI_MOSI_PIN ) 
#define             macXPT2046_MOSI_0()                             GPIO_ResetBits ( macXPT2046_SPI_MOSI_PORT, macXPT2046_SPI_MOSI_PIN )

#define             macXPT2046_MF103-ָ����()                               GPIO_ReadInputDataBit ( macXPT2046_SPI_MF103-ָ����_PORT, macXPT2046_SPI_MF103-ָ����_PIN )



/******************************* XPT2046 �������������� ***************************/
#define             macXPT2046_Coordinate_GramScan                  2               //ѡ�� XPT2046 ����������������ں���ɨ�跽��
#define             macXPT2046_THRESHOLD_CalDiff                    2               //У׼������ʱ���������ADֵ������� 

#define	            macXPT2046_CHANNEL_X 	                          0x90 	          //ͨ��Y+��ѡ�������	
#define	            macXPT2046_CHANNEL_Y 	                          0xd0	          //ͨ��X+��ѡ�������



/******************************* ���� XPT2046 ��ص��������� ***************************/
typedef	struct          //Һ������ṹ�� 
{
   uint16_t x;		
   uint16_t y;
	
} strType_XPT2046_Coordinate;   


typedef struct         //У׼���ӽṹ�� 
{
	long double An,  		 //ע:sizeof(long double) = 8
              Bn,     
              Cn,   
              Dn,    
              En,    
              Fn,     
              Divider;
	
} strType_XPT2046_Calibration;


typedef struct         //У׼ϵ���ṹ�壨����ʹ�ã�
{
	long double dX_X,  			 
              dX_Y,     
              dX,   
              dY_X,    
              dY_Y,    
              dY;

} strType_XPT2046_TouchPara;



/******************************* ���� XPT2046 ��ص��ⲿȫ�ֱ��� ***************************/
extern volatile uint8_t               ucXPT2046_TouchFlag;

extern strType_XPT2046_TouchPara      strXPT2046_TouchPara;



/******************************** XPT2046 �������������� **********************************/
void                     XPT2046_Init                    ( void );

uint8_t                  XPT2046_Touch_Calibrate         ( void );
uint8_t                  XPT2046_Get_TouchedPoint        ( strType_XPT2046_Coordinate * displayPtr, strType_XPT2046_TouchPara * para );
 


#endif /* __BSP_TOUCH_H */

