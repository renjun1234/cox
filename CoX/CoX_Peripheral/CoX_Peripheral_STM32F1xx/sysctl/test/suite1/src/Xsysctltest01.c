//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: MCRSTM32 <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. 
//!    <br><br>
//! 
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
#include "stm32f10xx_reg.h"
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
//! \brief Get the Test description of xsysctl011 register test.
//!
//! \return the desccription of the xcore011 test.
//
//*****************************************************************************
static char* xSysctl011GetTest(void)
{
    return "xsysctl, 011, SysCtl Peripheral Int Enable/Disable test";
}


//*****************************************************************************
//
//! \brief Get the Test description of xsysctl012 register test.
//!
//! \return the desccription of the xcore012 test.
//
//*****************************************************************************

static char* xSysctl012GetTest(void)
{
    return "xsysctl, 012, SysCtl Peripheral Int Flag Clear/Get test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl011 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl011Setup(void)
{

}


//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl012 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl012Setup(void)
{
    //
    // Reset HSI Clock Param
    //
    xHWREG(RCC_CR)  &= ~RCC_CR_HSION;    
    xHWREG(RCC_CIR) &= ~RCC_CIR_HSIRDYIE;
    xHWREG(RCC_CIR) |=  RCC_CIR_HSIRDYC;
    while((xHWREG(RCC_CR) & RCC_CR_HSIRDY) != 0);
    xHWREG(RCC_CIR) &=  ~RCC_CIR_HSIRDYC;
    
    //
    // Reset LSI Clock Param
    //
    xHWREG(RCC_CSR) &= ~RCC_CSR_LSION;
    xHWREG(RCC_CIR) &= ~RCC_CIR_LSIRDYIE;
    xHWREG(RCC_CIR) |=  RCC_CIR_LSIRDYC;
    while((xHWREG(RCC_CSR) & RCC_CSR_LSIRDY) != 0);
    xHWREG(RCC_CIR) &=  ~RCC_CIR_LSIRDYC;

    //
    // Reset LSE Clock Param
    //

    xHWREG(RCC_APB1ENR)   |= (RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN);
    xHWREG(PWR_CR)   &=  ~PWR_CR_DBP;
    xHWREG(PWR_CR)   |=  PWR_CR_DBP;
    
    xHWREG(RCC_BDCR) |=  RCC_BDCR_BDRST;
    SysCtlDelay(5);
    xHWREG(RCC_BDCR) &=  ~RCC_BDCR_BDRST;
    
    xHWREG(RCC_BDCR) &= ~RCC_BDCR_LSEON;
    xHWREG(RCC_CIR)  &= ~RCC_CIR_LSERDYIE;
    xHWREG(RCC_CIR)  |=  RCC_CIR_LSERDYC;
    while((xHWREG(RCC_BDCR) & RCC_BDCR_LSERDY) != 0);
    xHWREG(RCC_CIR)  &=  ~RCC_CIR_LSERDYC;

    //
    //In order to test PLL and HSE Clock successfuly, you must conform PLL HSE
    //interrupt enable bits have been set.
    //for example : add xHWREG(RCC_CIR) |= 0x00001800; in SysCtlClockSet function
    //

    // PLL HSE IS ALREADY SET IN SysCtlClockSet FUNCTION
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl011 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl011TearDown(void)
{   

}



//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl012 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl012TearDown(void)
{   
    
    //
    // Reset HSI Clock Param
    //
    xHWREG(RCC_CR)  &= ~RCC_CR_HSION;    
    xHWREG(RCC_CIR) &= ~RCC_CIR_HSIRDYIE;
    xHWREG(RCC_CIR) |=  RCC_CIR_HSIRDYC;
    while((xHWREG(RCC_CR) & RCC_CR_HSIRDY) != 0);
    xHWREG(RCC_CIR) &=  ~RCC_CIR_HSIRDYC;    
    //
    // Reset LSI Clock Param
    //
    xHWREG(RCC_CSR) &= ~RCC_CSR_LSION;
    xHWREG(RCC_CIR) &= ~RCC_CIR_LSIRDYIE;
    xHWREG(RCC_CIR) |=  RCC_CIR_LSIRDYC;
    while((xHWREG(RCC_CSR) & RCC_CSR_LSIRDY) != 0);
    xHWREG(RCC_CIR) &=  ~RCC_CIR_LSIRDYC;

    //
    // Reset LSE Clock Param
    //
    xHWREG(PWR_CR)   |=  PWR_CR_DBP;
    
    xHWREG(RCC_BDCR) |=  RCC_BDCR_BDRST;
    SysCtlDelay(5);
    xHWREG(RCC_BDCR) &=  ~RCC_BDCR_BDRST;
    
    xHWREG(RCC_BDCR) &= ~RCC_BDCR_LSEON;
    xHWREG(RCC_CIR)  &= ~RCC_CIR_LSERDYIE;
    xHWREG(RCC_CIR)  |=  RCC_CIR_LSERDYC;
    while((xHWREG(RCC_BDCR) & RCC_BDCR_LSERDY) != 0);
    xHWREG(RCC_CIR)  &=  ~RCC_CIR_LSERDYC;
    xHWREG(RCC_APB1ENR)  &= (RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN);

}

//*****************************************************************************
//
//! \brief xsysctl 011 test of Enable the system control interrrupts 
//! \param void
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlIntEnable_test(void)
{
    unsigned long i = 0;
    unsigned long ulSize = sizeof(ulSysCtlIntPara)/sizeof(ulSysCtlIntPara[0]);
    unsigned long ulTemp = 0;

    for(i = 0; i < ulSize; i++)
    {
        SysCtlIntEnable(ulSysCtlIntPara[i]);
        ulTemp = xHWREG(RCC_CIR);
        TestAssert((0 != (ulTemp & (1UL << (8 + i)))), 
                "xsysctl API SysCtlIntEnable error!");
    }
}


//*****************************************************************************
//
//! \brief xsysctl 011 test of Disable the system control interrrupts 
//! \param void
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlIntDisable_test(void)
{
    unsigned long i = 0;
    unsigned long ulSize = sizeof(ulSysCtlIntPara)/sizeof(ulSysCtlIntPara[0]);
    unsigned long ulTemp = 0;

    for(i = 0; i < ulSize; i++)
    {
        SysCtlIntDisable(ulSysCtlIntPara[i]);
        ulTemp = xHWREG(RCC_CIR);
        TestAssert((0 == (ulTemp & (1UL << (8 + i)))), 
                "xsysctl API SysCtlIntDisable error!");
    }
}


//*****************************************************************************
//
//! \brief xsysctl 012 test of Get system control interrrupts Flag
//! \param void
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlIntFlagGet_test(void)
{
    unsigned long ulTmp = 0;

    xHWREG(RCC_CIR) |= RCC_CIR_HSIRDYIE;
    xHWREG(RCC_CR)  |= RCC_CR_HSION;
    while((xHWREG(RCC_CR) & RCC_CR_HSIRDY) == 0);
    ulTmp = SysCtlIntFlagGet();
    TestAssert((0 != (ulTmp & RCC_CIR_HSIRDYF)),
            "xsysctl API SysCtlIntFlagGet error!");


    xHWREG(RCC_CIR) |= RCC_CIR_LSIRDYIE;
    xHWREG(RCC_CSR) |= RCC_CSR_LSION;
    while((xHWREG(RCC_CSR) & RCC_CSR_LSIRDY) == 0);
    ulTmp = SysCtlIntFlagGet();
    TestAssert((0 != (ulTmp & RCC_CIR_LSIRDYF)),
            "xsysctl API SysCtlIntFlagGet error!");

    xHWREG(PWR_CR)   &=  ~PWR_CR_DBP;
    xHWREG(PWR_CR)   |= PWR_CR_DBP;
    xHWREG(RCC_CIR)  |= RCC_CIR_LSERDYIE;
    xHWREG(RCC_BDCR) |= RCC_BDCR_LSEON;
    while((xHWREG(RCC_BDCR) & RCC_BDCR_LSERDY) == 0);
    ulTmp = SysCtlIntFlagGet();
    TestAssert((0 != (ulTmp & RCC_CIR_LSERDYF)),
            "xsysctl API SysCtlIntFlagGet error!");

    ulTmp = SysCtlIntFlagGet();
    TestAssert((0 != (ulTmp & RCC_CIR_PLLRDYF)),
            "xsysctl API SysCtlIntFlagGet error!");

    ulTmp = SysCtlIntFlagGet();
    TestAssert((0 != (ulTmp & RCC_CIR_HSERDYF)),
            "xsysctl API SysCtlIntFlagGet error!");
}

//*****************************************************************************
//
//! \brief xsysctl 012 test of Clear system control interrrupts Flag
//! \param void
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlIntFlagClear_test(void)
{
    unsigned long ulTmp = 0;
    SysCtlIntFlagClear(SYSCTL_INT_HSI);
    TestAssert((0 == (ulTmp & RCC_CIR_HSIRDYF)),
            "xsysctl API SysCtlIntFlagClear error!");


    SysCtlIntFlagClear(SYSCTL_INT_LSI);
    TestAssert((0 == (ulTmp & RCC_CIR_LSIRDYF)),
            "xsysctl API SysCtlIntFlagClear error!");

    SysCtlIntFlagClear(SYSCTL_INT_LSE);
    TestAssert((0 == (ulTmp & RCC_CIR_LSERDYF)),
            "xsysctl API SysCtlIntFlagClear error!");

    SysCtlIntFlagClear(SYSCTL_INT_PLL);
    TestAssert((0 == (ulTmp & RCC_CIR_PLLRDYF)),
            "xsysctl API SysCtlIntFlagClear error!");

    SysCtlIntFlagClear(SYSCTL_INT_HSE);
    TestAssert((0 == (ulTmp & RCC_CIR_HSERDYF)),
            "xsysctl API SysCtlIntFlagClear error!");

}
//*****************************************************************************
//
//! \brief xsysctl 011 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl011Execute(void)
{
    xsysctl_SysCtlIntEnable_test();    
    xsysctl_SysCtlIntDisable_test();    
}

//*****************************************************************************
//
//! \brief xsysctl 012 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl012Execute(void)
{
    xsysctl_SysCtlIntFlagGet_test();
    xsysctl_SysCtlIntFlagClear_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl011Register = {
    xSysctl011GetTest,
    xSysctl011Setup,
    xSysctl011TearDown,
    xSysctl011Execute,
};


const tTestCase sTestXSysctl012Register = {
    xSysctl012GetTest,
    xSysctl012Setup,    
    xSysctl012TearDown,
    xSysctl012Execute,
};
//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl01[] =
{
    &sTestXSysctl011Register,
    &sTestXSysctl012Register,
    0
};
