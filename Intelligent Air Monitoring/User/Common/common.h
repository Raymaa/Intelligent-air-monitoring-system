#ifndef __COMMON_H
#define __COMMON_H



#include "stm32f10x.h"



/******************************* �궨�� ***************************/
#define            macNVIC_PriorityGroup_x                     NVIC_PriorityGroup_2



/********************************** �������� ***************************************/
void                     USART_printf                       ( USART_TypeDef * USARTx, char * Data, ... );



#endif /* __COMMON_H */

