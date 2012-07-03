//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: MCBSTM32<br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xsysctl_register
//! .
//! \file xsysctltest.c
//! \brief xsysctl test source file
//! \brief xsysctl test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_memmap.h"

#include "stm32f10xx_reg.h"




typedef struct 
{
    unsigned long ulPeripheralBase;
    unsigned long ulPeripheralID;
    unsigned long ulPeripheralIntNum;
}
tPeripheralTable;

//*****************************************************************************
//
// An array that maps the peripheral base and peripheral ID and interrupt number
// together to enablea peripheral or peripheral interrupt by a peripheral base.
//
//*****************************************************************************
static const tPeripheralTable g_pPeripherals[] =
{
    {ADC1_BASE,        xSYSCTL_PERIPH_ADC1,    xINT_ADC0},
    {ADC2_BASE,        xSYSCTL_PERIPH_ADC2,    xINT_ADC0},
    {DMA1_BASE,        xSYSCTL_PERIPH_DMA1,    xINT_DMA1},
    {DMA2_BASE,        xSYSCTL_PERIPH_DMA2,    xINT_DMA2},
    {GPIOA_BASE,       xSYSCTL_PERIPH_GPIOA,   xINT_GPIOA},
    {GPIOB_BASE,       xSYSCTL_PERIPH_GPIOB,   xINT_GPIOA},
    {GPIOC_BASE,       xSYSCTL_PERIPH_GPIOC,   xINT_GPIOA},
    {GPIOD_BASE,       xSYSCTL_PERIPH_GPIOD,   xINT_GPIOA},
    {GPIOE_BASE,       xSYSCTL_PERIPH_GPIOE,   xINT_GPIOA},
    {GPIOF_BASE,       xSYSCTL_PERIPH_GPIOF,   xINT_GPIOA},
    {GPIOG_BASE,       xSYSCTL_PERIPH_GPIOG,   xINT_GPIOA},
    {I2C1_BASE,        xSYSCTL_PERIPH_I2C1,    xINT_I2C1},
    {I2C2_BASE,        xSYSCTL_PERIPH_I2C2,    xINT_I2C2},
    {RTC_BASE,         xSYSCTL_PERIPH_RTC,     xINT_RTC},
    {SPI1_BASE,        xSYSCTL_PERIPH_SPI1,    xINT_SPI1},
    {SPI2_BASE,        xSYSCTL_PERIPH_SPI2,    xINT_SPI2},
    {SPI3_BASE,        xSYSCTL_PERIPH_SPI3,    xINT_SPI3},
    {TIM1_BASE,        xSYSCTL_PERIPH_TIMER1,  xINT_TIMER1},
    {TIM2_BASE,        xSYSCTL_PERIPH_TIMER2,  xINT_TIMER2},
    {TIM3_BASE,        xSYSCTL_PERIPH_TIMER3,  xINT_TIMER3},
    {TIM4_BASE,        xSYSCTL_PERIPH_TIMER4,  xINT_TIMER4},
    {TIM5_BASE,        xSYSCTL_PERIPH_TIMER5,  xINT_TIMER5},
    {TIM6_BASE,        xSYSCTL_PERIPH_TIMER6,  xINT_TIMER6},
    {TIM7_BASE,        xSYSCTL_PERIPH_TIMER7,  xINT_TIMER7},
    {TIM8_BASE,        xSYSCTL_PERIPH_TIMER8,  0},
    {TIM9_BASE,        xSYSCTL_PERIPH_TIMER9,  0},
    {TIM10_BASE,       xSYSCTL_PERIPH_TIMER10, 0},
    {TIM11_BASE,       xSYSCTL_PERIPH_TIMER11, 0},
    {TIM12_BASE,       xSYSCTL_PERIPH_TIMER12, 0},
    {TIM13_BASE,       xSYSCTL_PERIPH_TIMER13, 0},
    {TIM14_BASE,       xSYSCTL_PERIPH_TIMER14, 0},
    {USART1_BASE,      xSYSCTL_PERIPH_UART1,   xINT_UART1},
    {USART2_BASE,      xSYSCTL_PERIPH_UART2,   xINT_UART2},
    {USART3_BASE,      xSYSCTL_PERIPH_UART3,   xINT_UART3},
    {USART4_BASE,      xSYSCTL_PERIPH_UART4,   xINT_UART4},
    {USART5_BASE,      xSYSCTL_PERIPH_UART5,   xINT_UART5},
    {WWDG_BASE,        xSYSCTL_PERIPH_WDOG,    xINT_WDT},
};

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl004 register test.
//!
//! \return the desccription of the xcore004 test.
//
//*****************************************************************************
static char* xSysctl006GetTest(void)
{
    return "xsysctl, 006, xSysCtlPeripheraIntNumGet function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl006 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl006Setup(void)
{
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl006TearDown(void)
{   

}


//*****************************************************************************
//
//! \brief xsysctl 006 test of xSysCtlPeripheraIntNumGet function test
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_xSysCtlPeripheraIntNumGet_test(void)
{
    unsigned long ulSize = 0;
    unsigned long i = 0;
    unsigned long ulTmp = 0;
    
    ulSize = sizeof(g_pPeripherals)/sizeof(g_pPeripherals[0]);
    for(i = 0; i < ulSize; i++) 
    {
        ulTmp = xSysCtlPeripheraIntNumGet(g_pPeripherals[i].ulPeripheralBase);
        TestAssert((ulTmp == g_pPeripherals[i].ulPeripheralIntNum),
                            "xSysCtl Function xSysCtlPeripheraIntNumGet Error");
    }

}
//*****************************************************************************
//
//! \brief xsysctl 006 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl006Execute(void)
{
    xsysctl_xSysCtlPeripheraIntNumGet_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl006Register = {
    xSysctl006GetTest,
    xSysctl006Setup,
    xSysctl006TearDown,
    xSysctl006Execute,
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl06[] =
{
    &sTestXSysctl006Register,
    0
};
