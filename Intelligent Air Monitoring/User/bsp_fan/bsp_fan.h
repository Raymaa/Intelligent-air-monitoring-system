#ifndef __BSP_FAN_H
#define __BSP_FAN_H

#include "stm32f10x.h"


/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM3

#define            FAN_GENERAL_TIM                   TIM2
#define            FAN_GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            FAN_GENERAL_TIM_CLK               RCC_APB1Periph_TIM2
#define            FAN_GENERAL_TIM_Period            999
#define            FAN_GENERAL_TIM_Prescaler         0
// TIM3 ����Ƚ�ͨ��1
#define            FAN_ENA_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            FAN_ENA_PORT          GPIOA
#define            FAN_ENA_PIN           GPIO_Pin_3

#define            FAN_IN1_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            FAN_IN1_PORT          GPIOC
#define            FAN_IN1_PIN           GPIO_Pin_3

#define            FAN_IN2_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            FAN_IN2_PORT          GPIOC
#define            FAN_IN2_PIN           GPIO_Pin_5

#define		FAN_GEAR_OFF		TIM_SetCompare4(FAN_GENERAL_TIM,0);\
								GPIO_SetBits(FAN_IN1_PORT, FAN_IN1_PIN);\
								GPIO_SetBits(FAN_IN2_PORT, FAN_IN2_PIN);
								
#define		FAN_GEAR_ONE		TIM_SetCompare4(FAN_GENERAL_TIM,599);\
								GPIO_ResetBits(FAN_IN1_PORT, FAN_IN1_PIN);\
								GPIO_SetBits(FAN_IN2_PORT, FAN_IN2_PIN);
								
#define		FAN_GEAR_TWO		TIM_SetCompare4(FAN_GENERAL_TIM,749);\
								GPIO_ResetBits(FAN_IN1_PORT, FAN_IN1_PIN);\
								GPIO_SetBits(FAN_IN2_PORT, FAN_IN2_PIN);

#define		FAN_GEAR_THREE		TIM_SetCompare4(FAN_GENERAL_TIM,999);\
								GPIO_ResetBits(FAN_IN1_PORT, FAN_IN1_PIN);\
								GPIO_SetBits(FAN_IN2_PORT, FAN_IN2_PIN);
								
/**************************��������********************************/

void FAN_GENERAL_TIM_Init(void);


#endif	/* __BSP_FAN_H */


