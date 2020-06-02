#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"
#include <stdio.h>

void SysTick_Init(void);
void Delay_us(__IO uint32_t nTime);

#define 	Delay_ms(a)		Delay_us(1000*a);
#define 	Delay_s(a)		Delay_us(1000000*a);

#endif /*__SYSTICK_H*/
