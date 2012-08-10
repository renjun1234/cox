//*****************************************************************************
//
//! @page xwdt_testcase xwdt register test
//!
//! File: @ref wdttest001.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xwdt sub component.<br><br>
//! - \p Board: LM3S9B96 <br><br>
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

#define WDT_NUM 2

static const unsigned long WdtBaseTbl[WDT_NUM] =
{
     WATCHDOG0_BASE,
     WATCHDOG1_BASE,
};

static const unsigned long ReloadValueTbl[] =
{
    100,
    122,
    12345,
    0xFFFFFFF,
};

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
//! \brief Get the Test description of xwdt001 register test.
//!
//! \return the desccription of the xwdt001 test.
//
//*****************************************************************************
static char* xwdt001GetTest(void)
{
    return " Wdt API Test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xwdt001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt001Setup(void)
{
    //
    // Enable WDT
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG1);
}

//*****************************************************************************
//
//! \brief xwdt001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt001Execute(void)
{
    unsigned long i       = 0;
    unsigned long tmp     = 0;
    unsigned long WdtBase = 0;

    //
    // Reset Enable/Disable Test
    //
    for(i = 0; i < WDT_NUM; i++)
    {
        WdtBase = WdtBaseTbl[i];

        //
        // Reset Enable Test
        //
        if(WdtBase == WATCHDOG1_BASE)
        {
            Watchdog1WriteSync();
        }
        WatchdogResetEnable(WdtBase);
        tmp = xHWREG(WdtBase + WDT_O_CTL) & WDT_CTL_RESEN;
        TestAssert((0 != tmp),
                "WDT Test 001: Res%set Enable Failed");

        //
        // Reset Disable Test
        //

        if(WdtBase == WATCHDOG1_BASE)
        {
            Watchdog1WriteSync();
        }
        WatchdogResetDisable(WdtBase);
        tmp = xHWREG(WdtBase + WDT_O_CTL) & WDT_CTL_RESEN;
        TestAssert((0 == tmp),
                "WDT Test 001: Reset Disable Failed");
    }

    //
    // Lock/Unlock/GetState Test
    //
    for(i = 0; i < WDT_NUM; i++)
    {
        WdtBase = WdtBaseTbl[i];

        //
        // Lock Test
        //
        if(WdtBase == WATCHDOG1_BASE)
        {
            Watchdog1WriteSync();
        }
        WatchdogLock(WdtBase);
        tmp = xHWREG(WdtBase + WDT_O_LOCK);
        TestAssert((tmp == WDT_LOCK_LOCKED),
                "WDT Test 001: Lock Failed");

        //
        // Get Lock State Test
        //
        tmp = WatchdogLockState(WdtBase);
        TestAssert((tmp == xtrue),
                "WDT Test 001: Get Lock State Failed");

        //
        // Unlock Test
        //
        if(WdtBase == WATCHDOG1_BASE)
        {
            Watchdog1WriteSync();
        }
        WatchdogUnlock(WdtBase);
        tmp = xHWREG(WdtBase + WDT_O_LOCK);
        TestAssert((tmp == WDT_LOCK_UNLOCKED),
                "WDT Test 001: Unlock Failed");

        //
        // Get Lock State Test
        //
        tmp = WatchdogLockState(WdtBase);
        TestAssert((tmp == xfalse),
                "WDT Test 001: Get Lock State Failed");
    }


    //
    // Reload Set/Get Test
    //

    for(i = 0; i < 1; i++)
    {
        unsigned long j       = 0;
        unsigned long TblSize = 0;

        WdtBase = WdtBaseTbl[i];
        TblSize = sizeof(ReloadValueTbl) / sizeof(ReloadValueTbl[0]);
        for(j = 0; j < TblSize; j++)
        {
            //
            // Reload Set Test
            //
            if(WdtBase == WATCHDOG1_BASE)
            {
                Watchdog1WriteSync();
            }
            WatchdogReloadSet(WdtBase, ReloadValueTbl[j]);

            tmp = xHWREG(WdtBase + WDT_O_LOAD);
            TestAssert((ReloadValueTbl[j] == tmp),
                    "WDT Test 001: Wdt Reload Set Failed");

            //
            // Reload Get Test
            //
            tmp = WatchdogReloadGet(WdtBase);
            TestAssert((ReloadValueTbl[j] == tmp),
                    "WDT Test 001: Wdt Reload Get Failed");
        }
    }

    //
    // Stall Enable/Disable Test
    //
    for(i = 0; i < WDT_NUM; i++)
    {
        WdtBase = WdtBaseTbl[i];
        //
        // Stall Enable Test
        //
        if(WdtBase == WATCHDOG1_BASE)
        {
            Watchdog1WriteSync();
        }
        WatchdogStallEnable(WdtBase);
        tmp = xHWREG(WdtBase + WDT_O_TEST) & WDT_TEST_STALL;
        TestAssert((0 != tmp),
                "WDT Test 001: Stall Enable Failed");

        //
        // Stall Disable Test
        //
        if(WdtBase == WATCHDOG1_BASE)
        {
            Watchdog1WriteSync();
        }
        WatchdogStallDisable(WdtBase);
        tmp = xHWREG(WdtBase + WDT_O_TEST) & WDT_TEST_STALL;
        TestAssert((0 == tmp),
                "WDT Test 001: Stall Disable Failed");
    }

    //
    // Enable/Running Test
    //
    for(i = 0; i < WDT_NUM; i++)
    {
        WdtBase = WdtBaseTbl[i];
        //
        // Enable Test
        //
        WatchdogEnable(WdtBase);
        tmp = xHWREG(WdtBase + WDT_O_CTL) & WDT_CTL_INTEN;
        TestAssert((0 != tmp),
                "WDT Test 001: Enable Failed");

        //
        // IsRunning Test
        //
        tmp = WatchdogRunning(WdtBase);
        TestAssert((0 != tmp),
                "WDT Test 001: IsRunning Failed");
    }

}


//*****************************************************************************
//
//! \brief something should do after the test execute of xwdt001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt001TearDown(void)
{
    //
    // Disable Wdt
    //
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG1);
}

//
// wdt001 register test case struct.
//
const tTestCase sTestXWdt001Register = {
    xwdt001GetTest,	
    xwdt001Setup,
    xwdt001TearDown,
    xwdt001Execute
};

//
// wdt test suits.
//
const tTestCase * const psPatternXwdt001[] =
{
    &sTestXWdt001Register,
    0
};
