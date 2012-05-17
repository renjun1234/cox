//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: MCBSTM32 <br><br>
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

#define STM32F103VB
#include "STM32F1XX_TEST.h"
//*****************************************************************************
//
//!\page test_xsysctl_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xsysctl register. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl03 register test.
//!
//! \return the desccription of the xsysctl03 test.
//
//*****************************************************************************
static char* xSysctl03GetTest(void)
{
    return "xsysctl, 03, xsysctl register and api test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl03 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl03Setup(void)
{
    //
    // Setup PWR BKP Clock Source and Reset Backup Domain
    // 
    //

    xHWREG(RCC_APB1ENR)   |= (RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN);    
    xHWREG(PWR_CR)   &=  ~PWR_CR_DBP;
    xHWREG(PWR_CR)   |=   PWR_CR_DBP;   
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl03 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl03TearDown(void)
{   
     volatile unsigned long i = 0;
     
    //
    // Reset Backup Domain and Disable PWR BKP Clock source
    //
    xHWREG(PWR_CR)   |=  PWR_CR_DBP;
    
    xHWREG(RCC_BDCR) |=  RCC_BDCR_BDRST;
    while(i++ < 5);
    xHWREG(RCC_BDCR) &=  ~RCC_BDCR_BDRST;
    xHWREG(PWR_CR)   &=  ~PWR_CR_DBP;
    xHWREG(RCC_APB1ENR)  &= (RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN);
}

//*****************************************************************************
//
//! \brief xsysctl 03 test of Peripheral Clock Source Set test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralClockSourceSet_test(void)
{
    unsigned long i,ulTemp;
    volatile unsigned long ulWait = 0;
    unsigned long ulArraySize = 0;
    

    //
    // Test for RTC source
    //   
    ulArraySize = sizeof(ulRTCSource)/sizeof(ulRTCSource[0]);
    for(i = 0; i < ulArraySize; i++)
    {
        //
        // Reset Backup Domain
        //
        
        xHWREG(RCC_BDCR) |=  (RCC_BDCR_BDRST);
        //
        // 0 <= Wait state <= 3
        // Idle loop 
        for(ulWait = 0; ulWait < 3; ulWait++)
        {
            ;
        }
        xHWREG(RCC_BDCR) &= ~(RCC_BDCR_BDRST);
        
        //
        // Select RTC source, 
        // note: once selected , it cannot be change anymore unless RESET Backup
        //       Domain
        //
        SysCtlPeripheralClockSourceSet(ulRTCSource[i]);

        //
        // 0 <= Wait state <= 3
        // Idle loop 
        for(ulWait = 0; ulWait < 3; ulWait++)
        {
            ;
        }
        ulTemp = xHWREG(RCC_BDCR);
        TestAssert(((i+1) == ((ulTemp & RCC_BDCR_RTCSEL_M) >> RCC_BDCR_RTCSEL_S)),
                   "xsysctl API error!");
    }



    //
    // Test for MCO source
    //
    ulArraySize = sizeof(ulMCOClkSource)/sizeof(ulMCOClkSource[0]);
    for(i = 0; i < ulArraySize; i++)
    {
        xHWREG(RCC_CFGR) &= ~(RCC_CFGR_MCO_M);
        for(ulWait = 0; ulWait < 3; ulWait++) 
        {
            ;
        }

        //
        // Select MCO Clock Source
        // Note: 0 <= waitstate <= 3
        //
        SysCtlPeripheralClockSourceSet(ulMCOClkSource[i]);
        for(ulWait = 0; ulWait < 3; ulWait++) 
        {
            ;
        }
        ulTemp = xHWREG(RCC_CFGR);
        TestAssert((i+4) == (((ulTemp & RCC_CFGR_MCO_M) >> RCC_CFGR_MCO_S)),
                   "xsysctl API error!");
    }


    //
    // Test for I2S2, 
    // note : optional, this test is only for the mcu that have I2S2 interface
    //
    #if defined (I2S_2)
    // 
    // Select System Clock as I2S2 clock source
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_I2S2_SYSCLK);
    ulTemp = xHWREG(RCC_CFGR2);
    TestAssert(((ulTemp&RCC_CFGR2_I2S2SRC) == 0), "xsysctl API error!");

    // 
    // Select PLL3 VCO clock as I2S2 clock source
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_I2S2_PLL3);
    ulTemp = xHWREG(RCC_CFGR2);
    TestAssert(((ulTemp&RCC_CFGR2_I2S2SRC) != 0), "xsysctl API error!");

    #endif


    #if defined (I2S_3)
    // 
    // Select System Clock as I2S3 clock source
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_I2S3_SYSCLK);
    ulTemp = xHWREG(RCC_CFGR2);
    TestAssert(((ulTemp&RCC_CFGR2_I2S3SRC) == 0), "xsysctl API error!");

    // 
    // Select PLL3 VCO clock as I2S2 clock source
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_I2S3_PLL3);
    ulTemp = xHWREG(RCC_CFGR2);
    TestAssert(((ulTemp&RCC_CFGR2_I2S3SRC) != 0), "xsysctl API error!");

    #endif


}

//*****************************************************************************
//
//! \brief xsysctl 03 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl03Execute(void)
{
    xsysctl_SysCtlPeripheralClockSourceSet_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl03Register = {
    xSysctl03GetTest,
    xSysctl03Setup,
    xSysctl03TearDown,
    xSysctl03Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl03[] =
{
    &sTestXSysctl03Register,
    0
};
