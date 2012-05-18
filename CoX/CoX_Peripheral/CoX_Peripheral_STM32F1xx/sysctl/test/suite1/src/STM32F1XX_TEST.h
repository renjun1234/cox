//*****************************************************************************
//
//! \file STM32F1XX_TEST.h
//! \brief Define STM32F1XXX MCU special register groups for test purposes .
//! \version 1.0
//! \date 5/13/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#ifndef __STM32F1XX_TEST_H_
#define __STM32F1XX_TEST_H_

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include "xhw_memmap.h"




//*****************************************************************************
//
//! \brief  Define your STM32F1XX MCU platform
//
//*****************************************************************************
    
#if defined  STM32F103VB

//
// below for test 002 
//
unsigned long ulSYSCTL_AHB_Periph[] = 
{ 
    SYSCTL_PERIPH_CRC,  
    SYSCTL_PERIPH_FLITF,
    SYSCTL_PERIPH_SRAM,
    SYSCTL_PERIPH_DMA1, 
};

unsigned long ulSYSCTL_AHB_EnableMask[] = 
{
    RCC_AHBENR_CRCEN,
    RCC_AHBENR_FLITFEN,
    RCC_AHBENR_SRAMEN,
    RCC_AHBENR_DMA1EN,
};




unsigned long ulSYSCTL_APB1_Periph[] = 
{ 
    SYSCTL_PERIPH_PWR,
    SYSCTL_PERIPH_BKP,
    SYSCTL_PERIPH_CAN1,
    SYSCTL_PERIPH_USB,
    SYSCTL_PERIPH_I2C2,
    SYSCTL_PERIPH_I2C1,
    SYSCTL_PERIPH_USART3,
    SYSCTL_PERIPH_USART2,
    SYSCTL_PERIPH_SPI2,
    SYSCTL_PERIPH_WWDG, 
    SYSCTL_PERIPH_TIM4,
    SYSCTL_PERIPH_TIM3,
    SYSCTL_PERIPH_TIM2,
};



unsigned long ulSYSCTL_APB1_EnableMask[] = 
{
    RCC_APB1ENR_PWREN,
    RCC_APB1ENR_BKPEN,
    RCC_APB1ENR_CAN1EN,
    RCC_APB1ENR_USBEN,
    RCC_APB1ENR_I2C2EN,
    RCC_APB1ENR_I2C1EN,
    RCC_APB1ENR_USART3EN,
    RCC_APB1ENR_USART2EN,
    RCC_APB1ENR_SPI2EN,
    RCC_APB1ENR_WWDGEN,
    RCC_APB1ENR_TIM4EN,
    RCC_APB1ENR_TIM3EN,
    RCC_APB1ENR_TIM2EN,
};

unsigned long ulSYSCTL_APB2_Periph[] = 
{ 
    SYSCTL_PERIPH_USART1,
    SYSCTL_PERIPH_SPI1,
    SYSCTL_PERIPH_TIM1,
    SYSCTL_PERIPH_ADC2,
    SYSCTL_PERIPH_ADC1,
    SYSCTL_PERIPH_IOPE, 
    SYSCTL_PERIPH_IOPD,
    SYSCTL_PERIPH_IOPC,
    SYSCTL_PERIPH_IOPB,
    SYSCTL_PERIPH_IOPA,
    SYSCTL_PERIPH_AFIO, 
};

unsigned long ulSYSCTL_APB2_EnableMask[] = 
{
    RCC_APB2ENR_USART1EN,
    RCC_APB2ENR_SPI1EN,
    RCC_APB2ENR_TIM1EN,
    RCC_APB2ENR_ADC2EN,
    RCC_APB2ENR_ADC1EN,
    RCC_APB2ENR_IOPEEN,
    RCC_APB2ENR_IOPDEN,
    RCC_APB2ENR_IOPCEN,
    RCC_APB2ENR_IOPBEN,
    RCC_APB2ENR_IOPAEN,
    RCC_APB2ENR_AFIOEN,

};


unsigned long ulPERIPHER_AHB_Addr[] =
{ 
    xDMA1_BASE,
};
unsigned long ulxPERIPHERE_AHB_EnableMask[] = 
{
    RCC_AHBENR_DMA1EN
};



unsigned long ulPERIPHER_APB1_Addr[] =
{ 
    xTIMER2_BASE,
    xTIMER3_BASE,
    xTIMER4_BASE,
    xWDT_BASE,
    xSPI2_BASE,
    xUART2_BASE,
    xUART3_BASE,
    xI2C1_BASE,
    xI2C2_BASE,
};
unsigned long ulxPERIPHERE_APB1_EnableMask[] = 
{
    RCC_APB1ENR_TIM2EN,
    RCC_APB1ENR_TIM3EN,
    RCC_APB1ENR_TIM4EN,
    RCC_APB1ENR_WWDGEN,
    RCC_APB1ENR_SPI2EN,
    RCC_APB1ENR_USART2EN,
    RCC_APB1ENR_USART3EN,
    RCC_APB1ENR_I2C1EN,
    RCC_APB1ENR_I2C2EN
};


unsigned long ulPERIPHER_APB2_Addr[] =
{ 
    xADC2_BASE,
    xADC1_BASE,
    xTIMER1_BASE,
    xSPI1_BASE, 
    xUART1_BASE,
    xGPIO_PORTA_BASE,
    xGPIO_PORTB_BASE,
    xGPIO_PORTC_BASE,
    xGPIO_PORTD_BASE,
    xGPIO_PORTE_BASE,
    
};

unsigned long ulxPERIPHERE_APB2_EnableMask[] = 
{
    RCC_APB2ENR_ADC2EN,
    RCC_APB2ENR_ADC1EN,
    RCC_APB2ENR_TIM1EN,
    RCC_APB2ENR_SPI1EN,
    RCC_APB2ENR_USART1EN,
    RCC_APB2ENR_IOPAEN,
    RCC_APB2ENR_IOPBEN, 
    RCC_APB2ENR_IOPCEN,
    RCC_APB2ENR_IOPDEN,
    RCC_APB2ENR_IOPEEN,  
    
};

//
// Below  for test 003
unsigned long ulRTCSource[] = 
{
    SYSCTL_RTC_LSE, 
    SYSCTL_RTC_LSI,
    SYSCTL_RTC_LSE_128,
};


unsigned long ulMCOClkSource[] = 
{
    SYSCTL_MCO_SYSCLK,
    SYSCTL_MCO_HSI,  
    SYSCTL_MCO_HSE,
    SYSCTL_MCO_PLL_2,
};


//#define I2S_2
//#define I2S_3

//
// Below for test 001
// note: the element of array must in special order
// 1:   SYSCTL_INT_LSI,
// 2:   SYSCTL_INT_LSE,
// 3:   SYSCTL_INT_HSI,
// 4:   SYSCTL_INT_HSE,
// 5:   SYSCTL_INT_PLL,
// 6:   SYSCTL_INT_PLL2
// 7:   SYSCTL_INT_PLL3
//
unsigned long ulSysCtlIntPara[] = 
{
    SYSCTL_INT_LSI,
    SYSCTL_INT_LSE,
    SYSCTL_INT_HSI,
    SYSCTL_INT_HSE,
    SYSCTL_INT_PLL,
    //SYSCTL_INT_PLL2
    //SYSCTL_INT_PLL3
};

#ifndef STM32F10X_MD
#define STM32F10X_MD
#endif

#else // else mcu
#error Please select your mcu first,thank you 

#endif



//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif /* end of include guard: __STM32F1XX_TEST_H_ */
