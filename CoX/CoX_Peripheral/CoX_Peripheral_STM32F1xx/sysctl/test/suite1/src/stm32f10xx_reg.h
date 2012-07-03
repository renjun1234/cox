//*****************************************************************************
//
//! \file stm32f10xx_reg.h
//! \brief Define STM32F1XXX MCU special register groups for test purposes .
//! \version 1.0
//! \date 5/18/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2012 CooCox.  All rights reserved.
//
//*****************************************************************************

#ifndef __STM32F10XX_REG_H_
#define __STM32F10XX_REG_H_

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

#define STM32F103VB



#if defined(STM32F103VB)
#ifndef STM32F10X_MD
#define STM32F10X_MD
#endif
    
#else // else mcu
#error Please select your mcu first,thank you 
#endif

//
// below for test 002 
//
extern unsigned long ulSYSCTL_AHB_Periph[];
extern unsigned long ulSYSCTL_APB1_EnableMask[] ; 
extern unsigned long ulSYSCTL_APB2_Periph[] ; 
extern unsigned long ulSYSCTL_APB2_EnableMask[] ; 
extern unsigned long ulPERIPHER_AHB_Addr[] ;
extern unsigned long ulxPERIPHERE_AHB_EnableMask[] ; 
extern unsigned long ulPERIPHER_APB1_Addr[] ;
extern unsigned long ulxPERIPHERE_APB1_EnableMask[] ; 
extern unsigned long ulPERIPHER_APB2_Addr[] ;
extern unsigned long ulxPERIPHERE_APB2_EnableMask[] ; 
extern unsigned long ulRTCSource[] ; 
extern unsigned long ulMCOClkSource[] ; 


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
// 6:   SYSCTL_INT_PLL2,
// 7:   SYSCTL_INT_PLL3,
//
extern unsigned long ulSysCtlIntPara[];







//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif /* end of include guard: __STM32F1XX_TEST_H_ */
