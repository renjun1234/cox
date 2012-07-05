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
//! \brief Get the Test description of xsysctl0701 register test.
//!
//! \return the desccription of the xsysctl0701 test.
//
//*****************************************************************************
static char* xSysctl0701GetTest(void)
{
    return "xsysctl, 0701, SysCtlPVDLevelConfig test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl0701 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0701Setup(void)
{
    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_PWREN;
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xsysctl0701 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0701TearDown(void)
{   
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_PWREN;
}

//*****************************************************************************
//
//! \brief xsysctl 0701 test of Set PVD level test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPVDLevelConfig_test(void)
{
    unsigned long ulPVDLevel[] = 
    {
        SYSCTL_PVDLEVEL_2V2,
        SYSCTL_PVDLEVEL_2V3,
        SYSCTL_PVDLEVEL_2V4,
        SYSCTL_PVDLEVEL_2V5,
        SYSCTL_PVDLEVEL_2V6,
        SYSCTL_PVDLEVEL_2V7,
        SYSCTL_PVDLEVEL_2V8,
        SYSCTL_PVDLEVEL_2V9,
    };
    
    unsigned long Size = sizeof(ulPVDLevel)/sizeof(ulPVDLevel[0]);
    unsigned long i = 0;
    unsigned long tmp = 0;

    for(i = 0; i < Size; i++)
    {
        SysCtlPVDLevelConfig(ulPVDLevel[i] | SYSCTL_PVD_EN);
        tmp = (xHWREG(PWR_CR) & PWR_CR_PLS_M) >> PWR_CR_PLS_S;
        TestAssert((tmp == i), "xSysCtl Test 0701 : SysCtlPVDLevelConfig failed"); 

        tmp = xHWREG(PWR_CR) & PWR_CR_PVDE;
        TestAssert((tmp != 0), "xSysCtl Test 0701 : SysCtlPVDLevelConfig failed"); 
    }

    for(i = 0; i < Size; i++)
    {
        SysCtlPVDLevelConfig(ulPVDLevel[i] | SYSCTL_PVD_DIS);
        tmp = (xHWREG(PWR_CR) & PWR_CR_PLS_M) >> PWR_CR_PLS_S;
        TestAssert((tmp == i), "xSysCtl Test 0701 : SysCtlPVDLevelConfig failed"); 

        tmp = xHWREG(PWR_CR) & PWR_CR_PVDE;
        TestAssert((tmp == 0), "xSysCtl Test 0701 : SysCtlPVDLevelConfig failed"); 
    }

}


//*****************************************************************************
//
//! \brief xsysctl 0701 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0701Execute(void)
{
    xsysctl_SysCtlPVDLevelConfig_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl0701Register = 
{
    xSysctl0701GetTest,
    xSysctl0701Setup,
    xSysctl0701TearDown,
    xSysctl0701Execute,
    
};




//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl07[] =
{
    &sTestXSysctl0701Register,
    0,
};

