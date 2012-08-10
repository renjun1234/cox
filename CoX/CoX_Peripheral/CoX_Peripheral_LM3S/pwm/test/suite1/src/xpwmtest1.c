//*****************************************************************************
//
//! @page xpwm_testcase xpwm register test
//!
//! File: @ref xpwmtest1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xpwm sub component.<br><br>
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
//! - \subpage test_xpwm_register
//! .
//! \file xpwmtest1.c
//! \brief xpwm test source file
//! \brief xpwm test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xpwm.h"
#include "xhw_pwm.h"

//*****************************************************************************
//
//!\page test_xpwm_register test_xpwm_register
//!
//!<h2>Description</h2>
//!Test xpwm register. <br>
//!
//
//*****************************************************************************

#define PWM_GEN_NUM 4

static const unsigned long PwmGenTbl[PWM_GEN_NUM] =
{
    PWM_GEN_0,
    PWM_GEN_1,
    PWM_GEN_2,
    PWM_GEN_3,
};

typedef struct
{
    unsigned long param;
    unsigned long mask;
    unsigned long check;
}tPwmMode;

static const tPwmMode PwmModeTbl[] =
{
    {
        PWM_GEN_MODE_FAULT_LATCHED,
        PWM_X_CTL_LATCH,
        PWM_X_CTL_LATCH,
    },

    {
        PWM_GEN_MODE_FAULT_UNLATCHED,
        PWM_X_CTL_LATCH,
        !PWM_X_CTL_LATCH,
    },

    {
        PWM_GEN_MODE_FAULT_MINPER,
        PWM_X_CTL_MINFLTPER,
        PWM_X_CTL_MINFLTPER,
    },

    {
        PWM_GEN_MODE_FAULT_NO_MINPER,
        PWM_X_CTL_MINFLTPER,
        !PWM_X_CTL_MINFLTPER,
    },

    {
        PWM_GEN_MODE_FAULT_EXT,
        PWM_X_CTL_FLTSRC,
        PWM_X_CTL_FLTSRC,
    },

    {
        PWM_GEN_MODE_FAULT_LEGACY,
        PWM_X_CTL_FLTSRC,
        !PWM_X_CTL_FLTSRC,
    },

    {
        PWM_GEN_MODE_DB_NO_SYNC,
        (PWM_X_CTL_DBFALLUPD_M | PWM_X_CTL_DBRISEUPD_M | PWM_X_CTL_DBCTLUPD_M),
        (PWM_X_CTL_DBFALLUPD_I | PWM_X_CTL_DBRISEUPD_I | PWM_X_CTL_DBCTLUPD_I),
    },

    {
        PWM_GEN_MODE_DB_SYNC_LOCAL,
        (PWM_X_CTL_DBFALLUPD_M  | PWM_X_CTL_DBRISEUPD_M  | PWM_X_CTL_DBCTLUPD_M ),
        (PWM_X_CTL_DBFALLUPD_LS | PWM_X_CTL_DBRISEUPD_LS | PWM_X_CTL_DBCTLUPD_LS),
    },

    {
        PWM_GEN_MODE_DB_SYNC_GLOBAL,
        (PWM_X_CTL_DBFALLUPD_M  | PWM_X_CTL_DBRISEUPD_M  | PWM_X_CTL_DBCTLUPD_M ),
        (PWM_X_CTL_DBFALLUPD_GS | PWM_X_CTL_DBRISEUPD_GS | PWM_X_CTL_DBCTLUPD_GS),
    },

    {
        PWM_GEN_MODE_GEN_NO_SYNC,
        (PWM_X_CTL_GENAUPD_M | PWM_X_CTL_GENBUPD_M),
        (PWM_X_CTL_GENAUPD_I | PWM_X_CTL_GENBUPD_I),
    },

    {
        PWM_GEN_MODE_GEN_SYNC_LOCAL,
        (PWM_X_CTL_GENAUPD_M  | PWM_X_CTL_GENBUPD_M ),
        (PWM_X_CTL_GENAUPD_LS | PWM_X_CTL_GENBUPD_LS),
    },

    {
        PWM_GEN_MODE_GEN_SYNC_GLOBAL,
        (PWM_X_CTL_GENAUPD_M  | PWM_X_CTL_GENBUPD_M ),
        (PWM_X_CTL_GENAUPD_GS | PWM_X_CTL_GENBUPD_GS),
    },

    {
        PWM_GEN_MODE_SYNC,
        (PWM_X_CTL_CMPBUPD | PWM_X_CTL_CMPAUPD | PWM_X_CTL_LOADUPD),
        (PWM_X_CTL_CMPBUPD | PWM_X_CTL_CMPAUPD | PWM_X_CTL_LOADUPD),
    },

    {
        PWM_GEN_MODE_NO_SYNC,
        (PWM_X_CTL_CMPBUPD    | PWM_X_CTL_CMPAUPD    | PWM_X_CTL_LOADUPD   ),
        ((!PWM_X_CTL_CMPBUPD) | (!PWM_X_CTL_CMPAUPD) | (!PWM_X_CTL_LOADUPD)),
    },

    {
        PWM_GEN_MODE_DBG_RUN,
        PWM_X_CTL_DEBUG,
        PWM_X_CTL_DEBUG,
    },

    {
        PWM_GEN_MODE_DBG_STOP,
        PWM_X_CTL_DEBUG,
        !PWM_X_CTL_DEBUG,
    },

    {
        PWM_GEN_MODE_DOWN,
        PWM_X_CTL_MODE,
        !PWM_X_CTL_MODE,

    },

    {
        PWM_GEN_MODE_UP_DOWN,
        PWM_X_CTL_MODE,
        PWM_X_CTL_MODE,
    },

};

typedef struct
{
    unsigned long Mode;
    unsigned long PeriodSet;
    unsigned long PeriodExpect;
}tPeriod;

static const tPeriod PeriodTbl[] =
{
    //
    // Count Down mode
    //
    {
        PWM_GEN_MODE_DOWN,
        2,
        2-1,
    },

    {
        PWM_GEN_MODE_DOWN,
        2000,
        2000-1,
    },

    {
        PWM_GEN_MODE_DOWN,
        23456,
        23456-1,
    },

    {
        PWM_GEN_MODE_DOWN,
        65500,
        65500-1,
    },

    //
    // Count Up and Down Mode
    //
    {
        PWM_GEN_MODE_UP_DOWN,
        2,
        2/2,
    },

    {
        PWM_GEN_MODE_UP_DOWN,
        2000,
        2000/2,
    },

    {
        PWM_GEN_MODE_UP_DOWN,
        23456,
        23456/2,
    },

    {
        PWM_GEN_MODE_UP_DOWN,
        65500,
        65500/2,
    },
};

typedef struct
{
    //
    // Note: Rise/Fall Value must be smaller than 4096
    //
    unsigned long RiseValue;
    unsigned long FallValue;
}tDeadBand;

static const tDeadBand DeadBandTbl[]=
{
    {
        1,
        1,
    },
    {
        2,
        1,
    },
    {
        56,
        56,
    },
    {
        100,
        100,
    },
    {
        1234,
        1234,
    },
    {
        2345,
        3243,
    },
    {
        4000,
        4000,
    },
    {
        4095,
        4095,
    },
};

static const unsigned long GenBitTbl[]=
{
    PWM_GEN_0_BIT,
    PWM_GEN_1_BIT,
    PWM_GEN_2_BIT,
    PWM_GEN_3_BIT,
};

static const unsigned long PwmOutBitTbl[] =
{
    PWM_OUT_0_BIT,
    PWM_OUT_1_BIT,
    PWM_OUT_2_BIT,
    PWM_OUT_3_BIT,
    PWM_OUT_4_BIT,
    PWM_OUT_5_BIT,
    PWM_OUT_6_BIT,
    PWM_OUT_7_BIT,
};

static const unsigned long IntTrigTbl[]=
{
    PWM_INT_CNT_ZERO,
    PWM_INT_CNT_LOAD,
    PWM_INT_CNT_AU,
    PWM_INT_CNT_AD,
    PWM_INT_CNT_BU,
    PWM_INT_CNT_BD,
    PWM_TR_CNT_ZERO,
    PWM_TR_CNT_LOAD,
    PWM_TR_CNT_AU,
    PWM_TR_CNT_AD,
    PWM_TR_CNT_BU,
    PWM_TR_CNT_BD,
};

static const unsigned long IntTbl[] =
{
    PWM_INT_GEN_0 ,
    PWM_INT_GEN_1 ,
    PWM_INT_GEN_2 ,
    PWM_INT_GEN_3 ,
    PWM_INT_FAULT0,
    PWM_INT_FAULT1,
    PWM_INT_FAULT2,
    PWM_INT_FAULT3,
};
//*****************************************************************************
//
//! \brief Get the Test description of xpwm001 register test.
//!
//! \return the desccription of the xpwm001 test.
//
//*****************************************************************************
static char* xpwm001GetTest(void)
{
    return "xpwm 001, ";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xpwm001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm001Setup(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
}

//*****************************************************************************
//
//! \brief xpwm001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm001Execute(void)
{
    unsigned long TblSize = 0;
    unsigned long i       = 0;
    unsigned long j       = 0;
    unsigned long tmp     = 0;

    //
    // PWM Module Enable/Disable Test
    //
    for(i = 0; i < PWM_GEN_NUM; i++)
    {
        unsigned long PwmGen = PwmGenTbl[i];
        //
        // PWM Enable test
        //
        PWMGenEnable(PWM_BASE, PwmGenTbl[i]);
        tmp = xHWREG(PWM_BASE + PwmGen + PWM_O_X_CTL) & PWM_X_CTL_ENABLE;
        TestAssert( (0 != tmp),
                "PWM Test 001:  Pwm Enable Failed!\n" );
        //
        // PWM Disable test
        //
        PWMGenDisable(PWM_BASE, PwmGenTbl[i]);
        tmp = xHWREG(PWM_BASE + PwmGen + PWM_O_X_CTL) & PWM_X_CTL_ENABLE;
        TestAssert( (0 == tmp),
                "PWM Test 001:  Pwm Disable Failed!\n" );
    }

    //
    // PWM Configure test
    //
    for(i = 0; i < PWM_GEN_NUM; i++)
    {
        unsigned long PwmGen = PwmGenTbl[i];
        TblSize =  sizeof(PwmModeTbl) / sizeof(PwmModeTbl[0]);

        for(j = 0; j < TblSize; j++)
        {
            xHWREG(PWM_BASE + PwmGen + PWM_O_X_CTL) &= ~PwmModeTbl[j].mask;
            PWMGenConfigure(PWM_BASE, PwmGen, PwmModeTbl[j].param);
            tmp = xHWREG(PWM_BASE + PwmGen + PWM_O_X_CTL) & PwmModeTbl[j].mask;
            TestAssert((tmp == PwmModeTbl[j].check),
                    "PWM Test 001 : Pwm configure Failed!\n");
        }
    }

    //
    // PWM Period set/get test
    //
    for(i = 0; i < PWM_GEN_NUM; i++)
    {
        unsigned long PwmGen    = PwmGenTbl[i];

        TblSize = sizeof(PeriodTbl) / sizeof(PeriodTbl[0]);

        for(j = 0; j < TblSize; j++)
        {
            //
            // Configure Pwm Mode: Down/Down_Up
            //
            PWMGenConfigure(PWM_BASE, PwmGen, PeriodTbl[j].Mode);
            PWMGenPeriodSet(PWM_BASE, PwmGen, PeriodTbl[j].PeriodSet);
            tmp = xHWREG(PWM_BASE + PwmGen + PWM_O_X_LOAD);
            TestAssert((tmp == PeriodTbl[j].PeriodExpect),
                    "PWM Test 001 : Pwm Period Set Failed!\n");

            //
            // Pwm Period Get test
            //
            tmp = PWMGenPeriodGet(PWM_BASE, PwmGen);
            TestAssert((tmp == PeriodTbl[j].PeriodSet),
                    "PWM Test 001 : Pwm Period Get Failed!\n");
        }
    }

    //
    // DeadBand Enable/Disable Test
    //
    for(i = 0; i < PWM_GEN_NUM; i++)
    {
        unsigned long PwmGen = PwmGenTbl[i];
        TblSize = sizeof(DeadBandTbl) / sizeof(DeadBandTbl[0]);

        for(j = 0; j < TblSize; j++)
        {
            PWMDeadBandEnable(PWM_BASE, PwmGen,
                    DeadBandTbl[j].RiseValue, DeadBandTbl[j].FallValue);
            //
            // Check Rise Value
            //
            tmp = xHWREG(PWM_BASE + PwmGen + PWM_O_X_DBRISE);
            TestAssert((tmp == DeadBandTbl[j].RiseValue),
                    "PWM Test 001 : Pwm DeadBand Set RiseValue Failed!\n");

            //
            // Check Fall Value
            //
            tmp = xHWREG(PWM_BASE + PwmGen + PWM_O_X_DBFALL);
            TestAssert((tmp == DeadBandTbl[j].FallValue),
                    "PWM Test 001 : Pwm DeadBand Set FallValue Failed!\n");

            //
            // Check DeadBand Enable Status
            //
            tmp = xHWREG(PWM_BASE + PwmGen + PWM_O_X_DBCTL) & PWM_X_DBCTL_ENABLE;
            TestAssert((0 != tmp),
                    "PWM Test 001 : Pwm DeadBand Enable Failed!\n");
            //
            // DeadBand Disable Test
            //
            PWMDeadBandDisable(PWM_BASE, PwmGen);

            //
            // Check DeadBand Disable Status
            //
            tmp = xHWREG(PWM_BASE + PwmGen + PWM_O_X_DBCTL) & PWM_X_DBCTL_ENABLE;
            TestAssert((0 == tmp),
                    "PWM Test 001 : Pwm DeadBand Disable Failed!\n");
        }

    }

    //
    // PWM Synchronous Update Test
    //
    for(i = 0; i < PWM_GEN_NUM; i++)
    {
        //
        // Sync Update Test
        //
        PWMSyncUpdate(PWM_BASE, GenBitTbl[i]);
        tmp = xHWREG(PWM_BASE + PWM_O_CTL) & GenBitTbl[i];
        TestAssert((0 != tmp),
                "PWM Test 001 : Sync Update Failed!\n");
    }

    //
    // PWM Output State/Invert/Fault/FaultLevel Test
    //
    TblSize = sizeof(PwmOutBitTbl) / sizeof(PwmOutBitTbl[0]);
    for(i = 0; i < TblSize; i++)
    {
        //
        // Output Enable
        //
        PWMOutputState(PWM_BASE, PwmOutBitTbl[i], xtrue);
        tmp = xHWREG(PWM_BASE + PWM_O_ENABLE) & PwmOutBitTbl[i];
        TestAssert((0 != tmp),
                "PWM Test 001 : Output Enable Failed!\n");

        //
        // Output Disable
        //
        PWMOutputState(PWM_BASE, PwmOutBitTbl[i], xfalse);
        tmp = xHWREG(PWM_BASE + PWM_O_ENABLE) & PwmOutBitTbl[i];
        TestAssert((0 == tmp),
                "PWM Test 001 : Output Disable Failed!\n");

        //
        // Output Invert Enable
        //
        PWMOutputInvert(PWM_BASE, PwmOutBitTbl[i], xtrue);
        tmp = xHWREG(PWM_BASE + PWM_O_INVERT) & PwmOutBitTbl[i];
        TestAssert((0 != tmp),
                "PWM Test 001 : Output Invert Enable Failed!\n");

        //
        // Output Invert Disable
        //
        PWMOutputInvert(PWM_BASE, PwmOutBitTbl[i], xfalse);
        tmp = xHWREG(PWM_BASE + PWM_O_INVERT) & PwmOutBitTbl[i];
        TestAssert((0 == tmp),
                "PWM Test 001 : Output Invert Disable Failed!\n");
        //
        // PWMOutputFaultLevel High
        //
        PWMOutputFaultLevel(PWM_BASE, PwmOutBitTbl[i], xtrue);
        tmp = xHWREG(PWM_BASE + PWM_O_FAULTVAL) & PwmOutBitTbl[i];
        TestAssert((0 != tmp),
                "PWM Test 001 : Fault Output High Failed!\n");
        //
        // PWMOutputFaultLevel Low
        //
        PWMOutputFaultLevel(PWM_BASE, PwmOutBitTbl[i], xfalse);
        tmp = xHWREG(PWM_BASE + PWM_O_FAULTVAL) & PwmOutBitTbl[i];
        TestAssert((0 == tmp),
                "PWM Test 001 : Fault Output Low Failed!\n");

        //
        //  PWM Output Fault
        //
        PWMOutputFault(PWM_BASE, PwmOutBitTbl[i], xtrue);
        tmp = xHWREG(PWM_BASE + PWM_O_FAULT) & PwmOutBitTbl[i];
        TestAssert((0 != tmp),
                "PWM Test 001 : Fault Output Failed!\n");
        //
        //  PWM Output Fault
        //
        PWMOutputFault(PWM_BASE, PwmOutBitTbl[i], xfalse);
        tmp = xHWREG(PWM_BASE + PWM_O_FAULT) & PwmOutBitTbl[i];
        TestAssert((0 == tmp),
                "PWM Test 001 : Fault Output Failed!\n");
    }

    //
    // PWMGenIntTrig Enable/Disable Test
    //
    TblSize = sizeof(IntTrigTbl) / sizeof(IntTrigTbl[0]);
    for(i = 0; i < PWM_GEN_NUM; i++)
    {
        unsigned long PwmGen = PwmGenTbl[i];

        for(j = 0; j < TblSize; j++)
        {
            //
            // Int Triggle Enable
            //
            PWMGenIntTrigEnable(PWM_BASE, PwmGen, IntTrigTbl[j]);
            tmp = xHWREG(PWM_BASE + PwmGen + PWM_O_X_INTEN) & IntTrigTbl[j];
            TestAssert((0 != tmp),
                    "PWM Test 001 : Int Triggle Enable Failed!\n");
            //
            // Int Triggle Disable
            //
            PWMGenIntTrigDisable(PWM_BASE, PwmGen, IntTrigTbl[j]);
            tmp = xHWREG(PWM_BASE + PwmGen + PWM_O_X_INTEN) & IntTrigTbl[j];
            TestAssert((0 == tmp),
                    "PWM Test 001 : Int Triggle Disable Failed!\n");
        }
    }

    //
    // Int Enable/Disable Test
    //
    TblSize = sizeof(IntTbl) / sizeof(IntTbl[0]);
    for(i = 0; i < TblSize; i++)
    {
        //
        // Int Enable
        //
        PWMIntEnable(PWM_BASE, IntTbl[i]);
        tmp = xHWREG(PWM_BASE + PWM_O_INTEN) & IntTbl[i];
        TestAssert((0 != tmp),
                "PWM Test 001 : Int Enable Failed!\n");

        //
        // Int Disable
        //
        PWMIntDisable(PWM_BASE, IntTbl[i]);
        tmp = xHWREG(PWM_BASE + PWM_O_INTEN) & IntTbl[i];
        TestAssert((0 == tmp),
                "PWM Test 001 : Int Disable Failed!\n");
    }
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xpwm001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm001TearDown(void)
{

}

//
// xpwm001 register test case struct.
//
const tTestCase sTestxpwm001Register = {
    xpwm001GetTest,
    xpwm001Setup,
    xpwm001TearDown,
    xpwm001Execute
};

//
// Xpwm test suits.
//
const tTestCase * const psPatternxpwm1[] =
{
    &sTestxpwm001Register,
    0
};

