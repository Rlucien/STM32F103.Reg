/*-------------------------------------------------------------------------------
** 名称：rcc.h
** 版本：V0.0.1
** 时间：2017.4.10
** 作者：lucien
** 描述：RCC时钟设置
-------------------------------------------------------------------------------*/
#ifndef __RCC_H
#define __RCC_H

/*--头文件---------------------------------------------------------------------*/
#include "stm32f10x.h"

/*--自定义同义关键字-----------------------------------------------------------*/

/*--自定义参数宏---------------------------------------------------------------*/

/*--自定义函数-----------------------------------------------------------------*/
static void RCC_Reset(void);
u8 RCC_SetClock(u8 freq);
u8 APB2Clock(APB2ENR_Bits Periph, FlagStatus State);
/*--自定义变量-----------------------------------------------------------------*/

typedef enum 
{
    AFIO    =    0x0001,    //APB2EN Bit0
    //RES1  =    0x0002,    //APB2EN Bit1
    IOPA    =    0x0004,    //APB2EN Bit2
    IOPB    =    0x0008,    //APB2EN Bit3
    IOPC    =    0x0010,    //APB2EN Bit4
    IOPD    =    0x0020,    //APB2EN Bit5
    IOPE    =    0x0040,    //APB2EN Bit6
    IOPF    =    0x0080,    //APB2EN Bit7
    IOPG    =    0x0100,    //APB2EN Bit8
    ADC1    =    0x0200,    //APB2EN Bit9
    ADC2    =    0x0400,    //APB2EN Bit10
    TIM1    =    0x0800,    //APB2EN Bit11
    SPI1    =    0x1000,    //APB2EN Bit12
    TIM8    =    0x2000,    //APB2EN Bit13
    USART1  =    0x4000,    //APB2EN Bit14
    ADC3    =    0x8000,    //APB2EN Bit15
} APB2ENR_Bits;


typedef enum 
{
    TIM2    =    0x00000001,    //APB1EN Bit0
    TIM3    =    0x00000002,    //APB1EN Bit1
    TIM4    =    0x00000004,    //APB1EN Bit2
    TIM5    =    0x00000008,    //APB1EN Bit3
    TIM6    =    0x00000010,    //APB1EN Bit4
    TIM7    =    0x00000020,    //APB1EN Bit5
    IOPE    =    0x00000040,    //APB1EN Bit6
    IOPF    =    0x00000080,    //APB1EN Bit7
    IOPG    =    0x00000100,    //APB1EN Bit8
    ADC1    =    0x00000200,    //APB1EN Bit9
    ADC2    =    0x00000400,    //APB1EN Bit10
    TIM1    =    0x00000800,    //APB1EN Bit11
    SPI1    =    0x00001000,    //APB1EN Bit12
    TIM8    =    0x00002000,    //APB1EN Bit13
    USART1  =    0x00004000,    //APB1EN Bit14
    ADC3    =    0x00008000,    //APB1EN Bit15
} APBE1NR_TypeDef;

