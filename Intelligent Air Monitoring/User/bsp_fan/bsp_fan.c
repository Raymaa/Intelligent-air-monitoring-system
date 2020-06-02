#include "bsp_fan.h" 

static void FAN_GENERAL_TIM_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// 输出比较通道1 GPIO 初始化
	RCC_APB2PeriphClockCmd(FAN_ENA_GPIO_CLK|FAN_IN1_GPIO_CLK|FAN_IN2_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  FAN_ENA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FAN_ENA_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  FAN_IN1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FAN_IN1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  FAN_IN2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FAN_IN2_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(FAN_IN1_PORT, FAN_IN1_PIN);
	GPIO_SetBits(FAN_IN2_PORT, FAN_IN2_PIN);
}


///*
// * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
// * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
// * 另外三个成员是通用定时器和高级定时器才有.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            都有
// *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
// *  TIM_Period               都有
// *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM信号 周期和占空比的计算--------------- */
// ARR ：自动重装载寄存器的值
// CLK_cnt：计数器的时钟，等于 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 信号的周期 T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)

static void FAN_GENERAL_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 开启定时器时钟,即内部时钟CK_INT=72M
	FAN_GENERAL_TIM_APBxClock_FUN(FAN_GENERAL_TIM_CLK,ENABLE);

	/*--------------------时基结构体初始化-------------------------*/
	// 配置周期，这里配置为100K

	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=FAN_GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= FAN_GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(FAN_GENERAL_TIM, &TIM_TimeBaseStructure);

	/*--------------------输出比较结构体初始化-------------------*/	
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(FAN_GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(FAN_GENERAL_TIM, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(FAN_GENERAL_TIM, ENABLE);
}

void FAN_GENERAL_TIM_Init(void)
{
	FAN_GENERAL_TIM_GPIO_Config();
	FAN_GENERAL_TIM_Mode_Config();		
}

/*********************************************END OF FILE**********************/
