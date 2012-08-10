//*****************************************************************************
//
//! @page xwdt_testcase xwdt register test
//!
//! File: @ref wdttest002.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xwdt sub component.<br><br>
//! - \p Board: LM3S9B96 <br><br>
//! - \p Last-Time(about): 3s <br><br>
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
//! - \subpage test_xgpio_register
//! .
//! \file wdttest00.c
//! \brief xwdt test source file
//! \brief xwdt test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_wdt.h"
#include "xwdt.h"

#define TBL_SIZE 10

static volatile unsigned long WatchDogTestTbl_0[TBL_SIZE];
static volatile unsigned long WatchDogTestTbl_1[TBL_SIZE];

static unsigned long WatchDog_0_Handler(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    unsigned long i = 0;

    for(i = 0; i < TBL_SIZE; i++)
    {
        WatchDogTestTbl_0[i] = 1;
    }
    
    return 0;
}

static unsigned long WatchDog_1_Handler(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    unsigned long i = 0;

    for(i = 0; i < TBL_SIZE; i++)
    {
        WatchDogTestTbl_1[i] = 2;
    }
    
    return 0;
}
//*****************************************************************************
//
//!\page test_xwdt_register test_xwdt_register
//!
//!<h2>Description</h2>
//!Test xwdt register. <br>
//!
//
//*****************************************************************************


//*****************************************************************************
//
//! \brief Get the Test description of xwdt002 register test.
//!
//! \return the desccription of the xwdt002 test.
//
//*****************************************************************************
static char* xwdt002GetTest(void)
{
    return " Wdt Interrupt Function Test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xwdt002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt002Setup(void)
{
    //
    // Enable WDT
    //
    xIntMasterEnable();
    xIntEnable(INT_WATCHDOG);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG1);
}

//*****************************************************************************
//
//! \brief xwdt002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt002Execute(void)
{
    unsigned long WdtBase = 0 ; 
    unsigned long ReloadValue = 0xFFFF;
    unsigned long i = 0;

    //
    // Configure WatchDog 0
    //
    WdtBase = WATCHDOG0_BASE;
    if(WatchdogLockState(WdtBase))
    {
        WatchdogUnlock(WdtBase);
    }
    WatchdogResetDisable(WdtBase);
    WatchdogReloadSet(WdtBase, ReloadValue);
    WatchdogStallEnable(WdtBase);
    xWDTIntCallbackInit(WdtBase, WatchDog_0_Handler);
    WatchdogIntEnable(WdtBase);
    WatchdogEnable(WdtBase);

    //
    // Configure WatchDog 1
    //
    WdtBase = WATCHDOG1_BASE;
    if(WatchdogLockState(WdtBase))
    {
        WatchdogUnlock(WdtBase);
    }
    WatchdogResetDisable(WdtBase);
    WatchdogReloadSet(WdtBase, ReloadValue/3);
    WatchdogStallEnable(WdtBase);
    xWDTIntCallbackInit(WdtBase, WatchDog_1_Handler);
    WatchdogIntEnable(WdtBase);
    WatchdogEnable(WdtBase);

    //
    // Wait about 2s
    // 
    SysCtlDelay( 2*SysCtlClockGet() );

    //
    // Disable Int
    //
    xIntMasterDisable();

    //
    // Check watchdog 0  interrupt status
    //
    for(i = 0; i < TBL_SIZE; i++)
    {
        TestAssert((WatchDogTestTbl_0[i] == 1),
                "WDT Test 002: Watchdog Int 0 Failed");
    }

    //
    // Check watchdog 1  interrupt status
    //
    for(i = 0; i < TBL_SIZE; i++)
    {
        TestAssert((WatchDogTestTbl_1[i] == 2),
                "WDT Test 002: Watchdog Int 1 Failed");
    }

}


//*****************************************************************************
//
//! \brief something should do after the test execute of xwdt002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt002TearDown(void)
{
    //
    // Disable Wdt
    //
    xIntMasterDisable();
    xIntDisable(INT_WATCHDOG);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG1);
}

//
// wdt002 register test case struct.
//
const tTestCase sTestXWdt002Register = {
    xwdt002GetTest,	
    xwdt002Setup,
    xwdt002TearDown,
    xwdt002Execute
};

//
// wdt test suits.
//
const tTestCase * const psPatternXwdt002[] =
{
    &sTestXWdt002Register,
    0
};
