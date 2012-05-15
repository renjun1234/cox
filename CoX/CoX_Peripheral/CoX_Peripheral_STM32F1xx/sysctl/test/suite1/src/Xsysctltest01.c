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
#include "STM32F1XX.h"
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

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl011Register = {
		xSysctl011GetTest,
		xSysctl011Setup,
		xSysctl011TearDown,
		xSysctl011Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl01[] =
{
    &sTestXSysctl011Register,
    0
};
