/*-------------------------------------------------------------------------------
** 名称：rcc.h
** 版本：V0.0.1
** 时间：2017.4.10
** 作者：lucien
** 描述：RCC时钟设置
-------------------------------------------------------------------------------*/


/*--头文件---------------------------------------------------------------------*/
#include "rcc.h"

/*--自定义同义关键字-----------------------------------------------------------*/

/*--自定义参数宏---------------------------------------------------------------*/

/*--自定义函数-----------------------------------------------------------------*/

/*--自定义变量-----------------------------------------------------------------*/


//////////////////////////////////////开 始\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

/*------------------------------------------------------------------------------
** 函数：RCC_Reset
** 时间：2017.4.10
** 作者：lucien
** 描述：RCC时钟复位函数
** 输入：无
** 输出：无
** 返回：无
-------------------------------------------------------------------------------*/

static void RCC_Reset(void)
{
  /* 设置 HSION 位 */
  RCC->CR |= (uint32_t)0x00000001;

  /* 重置 SW, HPRE, PPRE1, PPRE2, ADCPRE, MCO 位 */
  RCC->CFGR &= (uint32_t)0xF0FF0000;
  
  /* 重置 HSEON, CSSON, PLLON 位 */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* 重置 HSEBYP 位 */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* 重置 PLLSRC, PLLXTPRE, PLLMU, USBPRE/OTGFSPRE 位 */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

  /* 清除全部中断 并且 清除等待位  */
  RCC->CIR = 0x009F0000;

}


/*------------------------------------------------------------------------------
** 函数：RCC_SetClock
** 时间：2017.4.10
** 作者：lucien
** 描述：设置RCC时钟频率
** 输入：freq
** 输出：无
** 返回：无
-------------------------------------------------------------------------------*/
u8 RCC_SetClock(u8 freq)
{
    u32 rccCrHserdy = 0;
    u32 faultTime = 0, RCC_CFGR_PLL;

    /* 选择倍频系数 */
    switch(freq)
    {
        case(32):
            RCC_CFGR_PLL = RCC_CFGR_PLLMULL4;
            break;
        case(40):
            RCC_CFGR_PLL = RCC_CFGR_PLLMULL5;
            break;
        case(48):
            RCC_CFGR_PLL = RCC_CFGR_PLLMULL6;
            break;
        case(56):
            RCC_CFGR_PLL = RCC_CFGR_PLLMULL7;
            break;
        case(64):
            RCC_CFGR_PLL = RCC_CFGR_PLLMULL8;
            break;
        case(72):
            RCC_CFGR_PLL = RCC_CFGR_PLLMULL9;
            break;
        default:
            return 0xFF;
    }

    /*复位RCC_CR寄存器*/
    RCC_Reset();

    /*开启外部时钟*/
    RCC->CR &= (~RCC_CR_HSEON);
    RCC->CR |= RCC_CR_HSEON;//设置第16位

    /*检测外部时钟开启成功*/
    do
    {
        rccCrHserdy = RCC->CR & RCC_CR_HSERDY;//检测第17位是否为1
        faultTime++;//检测时间
    }
    while ((faultTime<0x0FFFFFFF) && (rccCrHserdy==0));
    /* 如果外部时钟开启成功*/
    if ((RCC->CR & RCC_CR_HSERDY) != 0)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 2 wait state */
        FLASH->ACR &= (~(uint32_t)FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_2;  

        /*AHB（0000）、APB2（000）不分频（即PLL输出时钟）*/
        /*APB1（100）要2分频（因最大只能36MHZ）*/
        RCC->CFGR &= (~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2));
        RCC->CFGR |= (RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2
                      | RCC_CFGR_PPRE2_DIV1);

        /*设置HSE为输入时钟，同事HSE不分频*/
        RCC->CFGR &= (~(uint32_t)(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE ));
        RCC->CFGR |= (RCC_CFGR_PLLSRC);

        /*设置PLL倍频系数为9倍*/
        RCC->CFGR &= (~RCC_CFGR_PLLMULL);//先清除原来的设置
        RCC->CFGR |= (RCC_CFGR_PLL);//设置倍频系数

        /*打开PLL使能*/
        RCC->CR |= RCC_CR_PLLON;

        /*等待开启PLL开启成功*/
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /*将PLL作为SYSCLK的时候来源*/
        RCC->CFGR &= (~RCC_CFGR_SW);//先清除先前的设置
        RCC->CFGR |= RCC_CFGR_SW_PLL;

        /*等待PLL作为SYSCLK时钟启动成功*/
        while ((RCC->CFGR & RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
        {
        }
    }/*end of if((RCC->CR & RCC_CR_HSERDY) != 0)*/
    /*如果外部时钟开启失败*/
    else
    {
        RCC_Reset();
        return 0xFF;
    }

    return 0;   
}

#endif


/*------------------------------------------------------------------------------
** 函数：APB2Clock
** 时间：2017.4.10
** 作者：lucien
** 描述：设置APB2ENR总线外设的时钟
** 输入：Periph, State
** 输出：无
** 返回：无
-------------------------------------------------------------------------------*/
u8 APB2Clock(APB2ENR_Bits Periph, FlagStatus State)
{
    if (State != RESET)
    {
        RCC->APB2ENR |= Periph;
    }
    else
    {
        RCC->APB2ENR &= ~Periph;
    }
}
