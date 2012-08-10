//*****************************************************************************
//
//! \file xpwm.c
//! \brief Driver for the PWM
//! \version V2.1.1.1
//! \date 07/15/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
//!
//!     * Redistributions of source code must retain the above copyright
//! notice, this list of conditions and the following disclaimer.
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution.
//!     * Neither the name of the <ORGANIZATION> nor the names of its
//! contributors may be used to endorse or promote products derived
//! from this software without specific prior written permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_pwm.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xpwm.h"





typedef struct
{
    //
    // PWM Interrupt channel type.
    // whick is assigned in the startup code.
    //
    unsigned long   IntType;

    //
    // Pwm Callback function.
    //
    xtEventCallback pfnPWMIntHandlerCallback;
}tCALL_BACK;

tCALL_BACK g_psPWMIntHandlerTable[] =
{
    { PWM_INT_GEN_0 , (xtEventCallback)0 },
    { PWM_INT_GEN_1 , (xtEventCallback)0 },
    { PWM_INT_GEN_2 , (xtEventCallback)0 },
    { PWM_INT_GEN_3 , (xtEventCallback)0 },
    { PWM_INT_FAULT , (xtEventCallback)0 },
};

//*****************************************************************************
//
// this is used to select the external crystal actually used in the system.
//
// /note: Only used for interal purpose ,  MUST not used by user.
//
//*****************************************************************************
static const unsigned long ValueToClockTbl[] =
{
    1000000  ,
    1843200  ,
    2000000  ,
    2457600  ,
    3579545  ,
    3686400  ,
    4000000  ,
    4096000  ,
    4915200  ,
    5000000  ,
    5120000  ,
    6000000  ,
    6144000  ,
    7372800  ,
    8000000  ,
    8192000  ,
    10000000 ,
    12000000 ,
    12288000 ,
    13560000 ,
    14318180 ,
    16000000 ,
    16384000 ,
};

//*****************************************************************************
//
// Misc macros for manipulating the encoded generator and output defines used
// by the API.
//
//*****************************************************************************
#define PWM_GEN_BADDR(_mod_, _gen_)                                           \
                                ((_mod_) + (_gen_))
#define PWM_GEN_EXT_BADDR(_mod_, _gen_)                                       \
                                ((_mod_) + PWM_GEN_EXT_0 +                    \
                                 ((_gen_) - PWM_GEN_0) * 2)
#define PWM_OUT_BADDR(_mod_, _out_)                                           \
                                ((_mod_) + ((_out_) & 0xFFFFFFC0))
#define PWM_IS_OUTPUT_ODD(_out_)                                              \
                                ((_out_) & 0x00000001)


//*****************************************************************************
//
//! \brief The PWM Fault Int default IRQ, declared in start up code.
//!
//! \param None.
//!
//! This function is to give a default PWM Fault Int IRQ service.
//!
//! \note
//!
//! \return None.
//
//*****************************************************************************
void PWMFaultIntHandler(void)
{
    unsigned long TblSize = 0;
    unsigned long i       = 0;

    TblSize = sizeof(g_psPWMIntHandlerTable)/sizeof(g_psPWMIntHandlerTable[0]);

    //
    // Find the Entery
    //
    for(i = 0; i < TblSize; i++)
    {
        if(PWM_INT_FAULT == g_psPWMIntHandlerTable[i].IntType)
        {
            g_psPWMIntHandlerTable[i].pfnPWMIntHandlerCallback(0,0,0,0);
            break;
        }
    }
}


//*****************************************************************************
//
//! \brief The PWM0 default IRQ, declared in start up code.
//!
//! \param None.
//!
//! This function is to give a default PWM0 IRQ service.
//!
//! \note
//!
//! \return None.
//
//*****************************************************************************
void PWM0IntHandler(void)
{
    unsigned long TblSize = 0;
    unsigned long i       = 0;

    TblSize = sizeof(g_psPWMIntHandlerTable)/sizeof(g_psPWMIntHandlerTable[0]);

    //
    // Find the Entery
    //
    for(i = 0; i < TblSize; i++)
    {
        if(PWM_INT_GEN_0 == g_psPWMIntHandlerTable[i].IntType)
        {
            g_psPWMIntHandlerTable[i].pfnPWMIntHandlerCallback(0,0,0,0);
            break;
        }
    }
}

//*****************************************************************************
//
//! \brief The PWM1 default IRQ, declared in start up code.
//!
//! \param None.
//!
//! This function is to give a default PWM1 IRQ service.
//!
//! \note
//!
//! \return None.
//
//*****************************************************************************
void PWM1IntHandler(void)
{
    unsigned long TblSize = 0;
    unsigned long i       = 0;

    TblSize = sizeof(g_psPWMIntHandlerTable)/sizeof(g_psPWMIntHandlerTable[0]);

    //
    // Find the Entery
    //
    for(i = 0; i < TblSize; i++)
    {
        if(PWM_INT_GEN_1 == g_psPWMIntHandlerTable[i].IntType)
        {
            g_psPWMIntHandlerTable[i].pfnPWMIntHandlerCallback(0,0,0,0);
            break;
        }
    }
}

//*****************************************************************************
//
//! \brief The PWM2 default IRQ, declared in start up code.
//!
//! \param None.
//!
//! This function is to give a default PWM2 IRQ service.
//!
//! \note
//!
//! \return None.
//
//*****************************************************************************
void PWM2IntHandler(void)
{
    unsigned long TblSize = 0;
    unsigned long i       = 0;

    TblSize = sizeof(g_psPWMIntHandlerTable)/sizeof(g_psPWMIntHandlerTable[0]);

    //
    // Find the Entery
    //
    for(i = 0; i < TblSize; i++)
    {
        if(PWM_INT_GEN_2 == g_psPWMIntHandlerTable[i].IntType)
        {
            g_psPWMIntHandlerTable[i].pfnPWMIntHandlerCallback(0,0,0,0);
            break;
        }
    }
}

//*****************************************************************************
//
//! \brief The PWM3 default IRQ, declared in start up code.
//!
//! \param None.
//!
//! This function is to give a default PWM3 IRQ service.
//!
//! \note
//!
//! \return None.
//
//*****************************************************************************
void PWM3IntHandler(void)
{
    unsigned long TblSize = 0;
    unsigned long i       = 0;

    TblSize = sizeof(g_psPWMIntHandlerTable)/sizeof(g_psPWMIntHandlerTable[0]);

    //
    // Find the Entery
    //
    for(i = 0; i < TblSize; i++)
    {
        if(PWM_INT_GEN_3 == g_psPWMIntHandlerTable[i].IntType)
        {
            g_psPWMIntHandlerTable[i].pfnPWMIntHandlerCallback(0,0,0,0);
            break;
        }
    }
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the PWM timer.
//!
//! \param ulBase is the PWM Int handler Entry decleard in the startup code.
//!
//! \param xtPortCallback is callback for the PWM timer.
//!
//! \note \b ulBase must be one of the following value:
//! \b PWM_INT_GEN_0  , \b PWM_INT_GEN_1  ,
//! \b PWM_INT_GEN_2  , \b PWM_INT_GEN_3  ,
//! \b PWM_INT_FAULT
//!
//! This function is to init interrupts callback for the PWM Controler.
//!
//! \return None.
//
//*****************************************************************************
void xPWMIntCallbackInit(unsigned long ulBase,
                         xtEventCallback xtPWMCallback)
{
    unsigned long TblSize = 0;
    unsigned long i       = 0;
    xASSERT((ulBase == PWM_INT_GEN_0) || (ulBase == PWM_INT_GEN_1) ||
            (ulBase == PWM_INT_GEN_2) || (ulBase == PWM_INT_GEN_3) ||
            (ulBase == PWM_INT_FAULT) );

    TblSize = sizeof(g_psPWMIntHandlerTable)/sizeof(g_psPWMIntHandlerTable[0]);

    //
    // Find the Entery
    //
    for(i = 0; i < TblSize; i++)
    {
        if(ulBase == g_psPWMIntHandlerTable[i].IntType)
        {
            g_psPWMIntHandlerTable[i].pfnPWMIntHandlerCallback = xtPWMCallback;
            break;
        }
    }
}

//*****************************************************************************
//
//! Configures a PWM generator.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator to configure.  This parameter must be one
//! of \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2, or \b PWM_GEN_3.
//! \param ulConfig is the configuration for the PWM generator.
//!
//! This function is used to set the mode of operation for a PWM generator.
//! The counting mode, synchronization mode, and debug behavior are all
//! configured.  After configuration, the generator is left in the disabled
//! state.
//!
//! A PWM generator can count in two different modes:  count down mode or count
//! up/down mode.  In count down mode, it counts from a value down to zero,
//! and then resets to the preset value, producing left-aligned PWM
//! signals (that is, the rising edge of the two PWM signals produced by the
//! generator occur at the same time).  In count up/down mode, it counts up
//! from zero to the preset value, counts back down to zero, and then repeats
//! the process, producing center-aligned PWM signals (that is,
//! the middle of the high/low period of the PWM signals produced by the
//! generator occurs at the same time).
//!
//! When the PWM generator parameters (period and pulse width) are modified,
//! their effect on the output PWM signals can be delayed.  In synchronous
//! mode, the parameter updates are not applied until a synchronization event
//! occurs.  This mode allows multiple parameters to be modified and take
//! effect simultaneously, instead of one at a time.  Additionally, parameters
//! to multiple PWM generators in synchronous mode can be updated
//! simultaneously, allowing them to be treated as if they were a unified
//! generator.  In non-synchronous mode, the parameter updates are not delayed
//! until a synchronization event.  In either mode, the parameter updates only
//! occur when the counter is at zero to help prevent oddly formed PWM signals
//! during the update (that is, a PWM pulse that is too short or too long).
//!
//! The PWM generator can either pause or continue running when the processor
//! is stopped via the debugger.  If configured to pause, it continues to
//! count until it reaches zero, at which point it pauses until the
//! processor is restarted.  If configured to continue running, it keeps
//! counting as if nothing had happened.
//!
//! The \e ulConfig parameter contains the desired configuration.  It is the
//! logical OR of the following:
//!
//! - \b PWM_GEN_MODE_DOWN or \b PWM_GEN_MODE_UP_DOWN to specify the counting
//!   mode
//! - \b PWM_GEN_MODE_SYNC or \b PWM_GEN_MODE_NO_SYNC to specify the counter
//!   load and comparator update synchronization mode
//! - \b PWM_GEN_MODE_DBG_RUN or \b PWM_GEN_MODE_DBG_STOP to specify the debug
//!   behavior
//! - \b PWM_GEN_MODE_GEN_NO_SYNC, \b PWM_GEN_MODE_GEN_SYNC_LOCAL, or
//!   \b PWM_GEN_MODE_GEN_SYNC_GLOBAL to specify the update synchronization
//!   mode for generator counting mode changes
//! - \b PWM_GEN_MODE_DB_NO_SYNC, \b PWM_GEN_MODE_DB_SYNC_LOCAL, or
//!   \b PWM_GEN_MODE_DB_SYNC_GLOBAL to specify the deadband parameter
//!   synchronization mode
//! - \b PWM_GEN_MODE_FAULT_LATCHED or \b PWM_GEN_MODE_FAULT_UNLATCHED to
//!   specify whether fault conditions are latched or not
//! - \b PWM_GEN_MODE_FAULT_MINPER or \b PWM_GEN_MODE_FAULT_NO_MINPER to
//!   specify whether minimum fault period support is required
//! - \b PWM_GEN_MODE_FAULT_EXT or \b PWM_GEN_MODE_FAULT_LEGACY to specify
//!   whether extended fault source selection support is enabled or not
//!
//! Setting \b PWM_GEN_MODE_FAULT_MINPER allows an application to set the
//! minimum duration of a PWM fault signal.  Faults are signaled for at
//! least this time even if the external fault pin deasserts earlier.  Care
//! should be taken when using this mode because during the fault signal
//! period, the fault interrupt from the PWM generator remains asserted.  The
//! fault interrupt handler may, therefore, reenter immediately if it exits
//! prior to expiration of the fault timer.
//!
//! \note Changes to the counter mode affect the period of the PWM signals
//! produced.  PWMGenPeriodSet() and PWMPulseWidthSet() should be called after
//! any changes to the counter mode of a generator.
//!
//! \return None.
//
//*****************************************************************************
void
PWMGenConfigure(unsigned long ulBase, unsigned long ulGen,
                unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );


    //
    // Compute the generator's base address.
    //
    ulGen = PWM_GEN_BADDR(ulBase, ulGen);

    //
    // Change the global configuration of the generator.
    //
    xHWREG(ulGen + PWM_O_X_CTL) = ((xHWREG(ulGen + PWM_O_X_CTL) &
                                   ~(PWM_X_CTL_MODE | PWM_X_CTL_DEBUG |
                                     PWM_X_CTL_LATCH | PWM_X_CTL_MINFLTPER |
                                     PWM_X_CTL_FLTSRC | PWM_X_CTL_DBFALLUPD_M |
                                     PWM_X_CTL_DBRISEUPD_M |
                                     PWM_X_CTL_DBCTLUPD_M |
                                     PWM_X_CTL_GENBUPD_M |
                                     PWM_X_CTL_GENAUPD_M |
                                     PWM_X_CTL_LOADUPD | PWM_X_CTL_CMPAUPD |
                                     PWM_X_CTL_CMPBUPD)) | ulConfig);

    //
    // Set the individual PWM generator controls.
    //
    if(ulConfig & PWM_X_CTL_MODE)
    {
        //
        // In up/down count mode, set the signal high on up count comparison
        // and low on down count comparison (that is, center align the
        // signals).
        //
        xHWREG(ulGen + PWM_O_X_GENA) = (PWM_X_GENA_ACTCMPAU_ONE |
                                       PWM_X_GENA_ACTCMPAD_ZERO);
        xHWREG(ulGen + PWM_O_X_GENB) = (PWM_X_GENB_ACTCMPBU_ONE |
                                       PWM_X_GENB_ACTCMPBD_ZERO);
    }
    else
    {
        //
        // In down count mode, set the signal high on load and low on count
        // comparison (that is, left align the signals).
        //
        xHWREG(ulGen + PWM_O_X_GENA) = (PWM_X_GENA_ACTLOAD_ONE |
                                       PWM_X_GENA_ACTCMPAD_ZERO);
        xHWREG(ulGen + PWM_O_X_GENB) = (PWM_X_GENB_ACTLOAD_ONE |
                                       PWM_X_GENB_ACTCMPBD_ZERO);
    }
}

//*****************************************************************************
//
//! Sets the period of a PWM generator.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator to be modified.  This parameter must be
//! one of \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2, or \b PWM_GEN_3.
//! \param ulPeriod specifies the period of PWM generator output, measured
//! in clock ticks.
//!
//! This function sets the period of the specified PWM generator block, where
//! the period of the generator block is defined as the number of PWM clock
//! ticks between pulses on the generator block zero signal.
//!
//! \note Any subsequent calls made to this function before an update occurs
//! cause the previous values to be overwritten.
//!
//! \return None.
//
//*****************************************************************************
void
PWMGenPeriodSet(unsigned long ulBase, unsigned long ulGen,
                unsigned long ulPeriod)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );

    //
    // Compute the generator's base address.
    //
    ulGen = PWM_GEN_BADDR(ulBase, ulGen);

    //
    // Set the reload register based on the mode.
    //
    if(xHWREG(ulGen + PWM_O_X_CTL) & PWM_X_CTL_MODE)
    {
        //
        // In up/down count mode, set the reload register to half the requested
        // period.
        //
        xASSERT((ulPeriod / 2) < 65536);
        xHWREG(ulGen + PWM_O_X_LOAD) = ulPeriod / 2;
    }
    else
    {
        //
        // In down count mode, set the reload register to the requested period
        // minus one.
        //
        xASSERT((ulPeriod <= 65536) && (ulPeriod != 0));
        xHWREG(ulGen + PWM_O_X_LOAD) = ulPeriod - 1;
    }
}

//*****************************************************************************
//
//! Gets the period of a PWM generator block.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator to query.  This parameter must be one of
//! \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2, or \b PWM_GEN_3.
//!
//! This function gets the period of the specified PWM generator block.  The
//! period of the generator block is defined as the number of PWM clock ticks
//! between pulses on the generator block zero signal.
//!
//! If the update of the counter for the specified PWM generator has yet
//! to be completed, the value returned may not be the active period.  The
//! value returned is the programmed period, measured in PWM clock ticks.
//!
//! \return Returns the programmed period of the specified generator block
//! in PWM clock ticks.
//
//*****************************************************************************
unsigned long
PWMGenPeriodGet(unsigned long ulBase, unsigned long ulGen)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );

    //
    // Compute the generator's base address.
    //
    ulGen = PWM_GEN_BADDR(ulBase, ulGen);

    //
    // Figure out the counter mode.
    //
    if(xHWREG(ulGen + PWM_O_X_CTL) & PWM_X_CTL_MODE)
    {
        //
        // The period is twice the reload register value.
        //
        return(xHWREG(ulGen + PWM_O_X_LOAD) * 2);
    }
    else
    {
        //
        // The period is the reload register value plus one.
        //
        return(xHWREG(ulGen + PWM_O_X_LOAD) + 1);
    }
}

//*****************************************************************************
//
//! Enables the timer/counter for a PWM generator block.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator to be enabled.  This parameter must be
//! one of \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2, or \b PWM_GEN_3.
//!
//! This function allows the PWM clock to drive the timer/counter for the
//! specified generator block.
//!
//! \return None.
//
//*****************************************************************************
void
PWMGenEnable(unsigned long ulBase, unsigned long ulGen)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );

    //
    // Enable the PWM generator.
    //
    xHWREG(PWM_GEN_BADDR(ulBase, ulGen) + PWM_O_X_CTL) |= PWM_X_CTL_ENABLE;
}

//*****************************************************************************
//
//! Disables the timer/counter for a PWM generator block.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator to be disabled.  This parameter must be
//! one of \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2, or \b PWM_GEN_3.
//!
//! This function blocks the PWM clock from driving the timer/counter for the
//! specified generator block.
//!
//! \return None.
//
//*****************************************************************************
void
PWMGenDisable(unsigned long ulBase, unsigned long ulGen)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );

    //
    // Disable the PWM generator.
    //
    xHWREG(PWM_GEN_BADDR(ulBase, + ulGen) + PWM_O_X_CTL) &= ~(PWM_X_CTL_ENABLE);
}

//*****************************************************************************
//
//! Sets the pulse width for the specified PWM output.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulPWMOut is the PWM output to modify.  This parameter must be one
//! of \b PWM_OUT_0, \b PWM_OUT_1, \b PWM_OUT_2, \b PWM_OUT_3, \b PWM_OUT_4,
//! \b PWM_OUT_5, \b PWM_OUT_6, or \b PWM_OUT_7.
//! \param ulWidth specifies the width of the positive portion of the pulse.
//!
//! This function sets the pulse width for the specified PWM output, where the
//! pulse width is defined as the number of PWM clock ticks.
//!
//! \note Any subsequent calls made to this function before an update occurs
//! cause the previous values to be overwritten.
//!
//! \return None.
//
//*****************************************************************************
void
PWMPulseWidthSet(unsigned long ulBase, unsigned long ulPWMOut,
                 unsigned long ulWidth)
{
    unsigned long ulGenBase, ulReg;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulPWMOut == PWM_OUT_0) || (ulPWMOut == PWM_OUT_1) ||
             (ulPWMOut == PWM_OUT_2) || (ulPWMOut == PWM_OUT_3) ||
             (ulPWMOut == PWM_OUT_4) || (ulPWMOut == PWM_OUT_5) ||
             (ulPWMOut == PWM_OUT_6) || (ulPWMOut == PWM_OUT_7) );
    //
    // Compute the generator's base address.
    //
    ulGenBase = PWM_OUT_BADDR(ulBase, ulPWMOut);

    //
    // If the counter is in up/down count mode, divide the width by two.
    //
    if(xHWREG(ulGenBase + PWM_O_X_CTL) & PWM_X_CTL_MODE)
    {
        ulWidth /= 2;
    }

    //
    // Get the period.
    //
    ulReg = xHWREG(ulGenBase + PWM_O_X_LOAD);

    //
    // Make sure the width is not too large.
    //
    xASSERT(ulWidth < ulReg);

    //
    // Compute the compare value.
    //
    ulReg = ulReg - ulWidth;

    //
    // Write to the appropriate registers.
    //
    if(PWM_IS_OUTPUT_ODD(ulPWMOut))
    {
        xHWREG(ulGenBase + PWM_O_X_CMPB) = ulReg;
    }
    else
    {
        xHWREG(ulGenBase + PWM_O_X_CMPA) = ulReg;
    }
}

//*****************************************************************************
//
//! Gets the pulse width of a PWM output.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulPWMOut is the PWM output to query.  This parameter must be one of
//! \b PWM_OUT_0, \b PWM_OUT_1, \b PWM_OUT_2, \b PWM_OUT_3, \b PWM_OUT_4,
//! \b PWM_OUT_5, \b PWM_OUT_6, or \b PWM_OUT_7.
//!
//! This function gets the currently programmed pulse width for the specified
//! PWM output.  If the update of the comparator for the specified output has
//! yet to be completed, the value returned may not be the active pulse width.
//! The value returned is the programmed pulse width, measured in PWM clock
//! ticks.
//!
//! \return Returns the width of the pulse in PWM clock ticks.
//
//*****************************************************************************
unsigned long
PWMPulseWidthGet(unsigned long ulBase, unsigned long ulPWMOut)
{
    unsigned long ulGenBase, ulReg, ulLoad;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulPWMOut == PWM_OUT_0) || (ulPWMOut == PWM_OUT_1) ||
             (ulPWMOut == PWM_OUT_2) || (ulPWMOut == PWM_OUT_3) ||
             (ulPWMOut == PWM_OUT_4) || (ulPWMOut == PWM_OUT_5) ||
             (ulPWMOut == PWM_OUT_6) || (ulPWMOut == PWM_OUT_7) );

    //
    // Compute the generator's base address.
    //
    ulGenBase = PWM_OUT_BADDR(ulBase, ulPWMOut);

    //
    // Then compute the pulse width.  If mode is UpDown, set
    // width = (load - compare) * 2.  Otherwise, set width = load - compare.
    //
    ulLoad = xHWREG(ulGenBase + PWM_O_X_LOAD);
    if(PWM_IS_OUTPUT_ODD(ulPWMOut))
    {
        ulReg = xHWREG(ulGenBase + PWM_O_X_CMPB);
    }
    else
    {
        ulReg = xHWREG(ulGenBase + PWM_O_X_CMPA);
    }
    ulReg = ulLoad - ulReg;

    //
    // If in up/down count mode, double the pulse width.
    //
    if(xHWREG(ulGenBase + PWM_O_X_CTL) & PWM_X_CTL_MODE)
    {
        ulReg = ulReg * 2;
    }

    //
    // Return the pulse width.
    //
    return(ulReg);
}

//*****************************************************************************
//
//! Enables the PWM dead band output and sets the dead band delays.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator to modify.  This parameter must be one
//! of \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2, or \b PWM_GEN_3.
//! \param usRise specifies the width of delay from the rising edge.
//! \param usFall specifies the width of delay from the falling edge.
//!
//! This function sets the dead bands for the specified PWM generator,
//! where the dead bands are defined as the number of \b PWM clock ticks
//! from the rising or falling edge of the generator's \b OutA signal.
//! Note that this function causes the coupling of \b OutB to \b OutA.
//!
//! \return None.
//
//****************************************************************************
void
PWMDeadBandEnable(unsigned long ulBase, unsigned long ulGen,
                  unsigned short usRise, unsigned short usFall)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );
    xASSERT(usRise < 4096);
    xASSERT(usFall < 4096);

    //
    // Compute the generator's base address.
    //
    ulGen = PWM_GEN_BADDR(ulBase, ulGen);

    //
    // Write the dead band delay values.
    //
    xHWREG(ulGen + PWM_O_X_DBRISE) = usRise;
    xHWREG(ulGen + PWM_O_X_DBFALL) = usFall;

    //
    // Enable the deadband functionality.
    //
    xHWREG(ulGen + PWM_O_X_DBCTL) |= PWM_X_DBCTL_ENABLE;
}

//*****************************************************************************
//
//! Disables the PWM dead band output.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator to modify. This parameter must be one of
//! \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2, or \b PWM_GEN_3.
//!
//! This function disables the dead band mode for the specified PWM generator.
//! Doing so decouples the \b OutA and \b OutB signals.
//!
//! \return None.
//
//*****************************************************************************
void
PWMDeadBandDisable(unsigned long ulBase, unsigned long ulGen)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );

    //
    // Disable the deadband functionality.
    //
    xHWREG(PWM_GEN_BADDR(ulBase, ulGen) + PWM_O_X_DBCTL) &=
        ~(PWM_X_DBCTL_ENABLE);
}

//*****************************************************************************
//
//! Synchronizes all pending updates.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGenBits are the PWM generator blocks to be updated.  This
//! parameter must be the logical OR of any of \b PWM_GEN_0_BIT,
//! \b PWM_GEN_1_BIT, \b PWM_GEN_2_BIT, or \b PWM_GEN_3_BIT.
//!
//! For the selected PWM generators, this function causes all queued updates to
//! the period or pulse width to be applied the next time the corresponding
//! counter becomes zero.
//!
//! \return None.
//
//*****************************************************************************
void
PWMSyncUpdate(unsigned long ulBase, unsigned long ulGenBits)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT(!(ulGenBits & ~(PWM_GEN_0_BIT | PWM_GEN_1_BIT | PWM_GEN_2_BIT |
                           PWM_GEN_3_BIT)));

    //
    // Synchronize pending PWM register changes.
    //
    xHWREG(ulBase + PWM_O_CTL) = ulGenBits;
}

//*****************************************************************************
//
//! Synchronizes the counters in one or multiple PWM generator blocks.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGenBits are the PWM generator blocks to be synchronized.  This
//! parameter must be the logical OR of any of \b PWM_GEN_0_BIT,
//! \b PWM_GEN_1_BIT, \b PWM_GEN_2_BIT, or \b PWM_GEN_3_BIT.
//!
//! For the selected PWM module, this function synchronizes the time base
//! of the generator blocks by causing the specified generator counters to be
//! reset to zero.
//!
//! \return None.
//
//*****************************************************************************
void
PWMSyncTimeBase(unsigned long ulBase, unsigned long ulGenBits)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT(!(ulGenBits & ~(PWM_GEN_0_BIT | PWM_GEN_1_BIT | PWM_GEN_2_BIT |
                           PWM_GEN_3_BIT)));

    //
    // Synchronize the counters in the specified generators by writing to the
    // module's synchronization register.
    //
    xHWREG(ulBase + PWM_O_SYNC) = ulGenBits;
}

//*****************************************************************************
//
//! Enables or disables PWM outputs.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulPWMOutBits are the PWM outputs to be modified.  This parameter
//! must be the logical OR of any of \b PWM_OUT_0_BIT, \b PWM_OUT_1_BIT,
//! \b PWM_OUT_2_BIT, \b PWM_OUT_3_BIT, \b PWM_OUT_4_BIT, \b PWM_OUT_5_BIT,
//! \b PWM_OUT_6_BIT, or \b PWM_OUT_7_BIT.
//! \param bEnable determines if the signal is enabled or disabled.
//!
//! This function enables or disables the selected PWM outputs.  The
//! outputs are selected using the parameter \e ulPWMOutBits.  The parameter
//! \e bEnable determines the state of the selected outputs.  If \e bEnable is
//! \b xtrue, then the selected PWM outputs are enabled, or placed in the active
//! state.  If \e bEnable is \b xfalse, then the selected outputs are disabled
//! or placed in the inactive state.
//!
//! \return None.
//
//*****************************************************************************
void
PWMOutputState(unsigned long ulBase, unsigned long ulPWMOutBits,
               xtBoolean bEnable)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT(!(ulPWMOutBits & ~(PWM_OUT_0_BIT | PWM_OUT_1_BIT | PWM_OUT_2_BIT |
                              PWM_OUT_3_BIT | PWM_OUT_4_BIT | PWM_OUT_5_BIT |
                              PWM_OUT_6_BIT | PWM_OUT_7_BIT)));

    //
    // Read the module's ENABLE output control register and set or clear the
    // requested bits.
    //
    if(bEnable == xtrue)
    {
        xHWREG(ulBase + PWM_O_ENABLE) |= ulPWMOutBits;
    }
    else
    {
        xHWREG(ulBase + PWM_O_ENABLE) &= ~(ulPWMOutBits);
    }
}

//*****************************************************************************
//
//! Selects the inversion mode for PWM outputs.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulPWMOutBits are the PWM outputs to be modified.  This parameter
//! must be the logical OR of any of \b PWM_OUT_0_BIT, \b PWM_OUT_1_BIT,
//! \b PWM_OUT_2_BIT, \b PWM_OUT_3_BIT, \b PWM_OUT_4_BIT, \b PWM_OUT_5_BIT,
//! \b PWM_OUT_6_BIT, or \b PWM_OUT_7_BIT.
//! \param bInvert determines if the signal is inverted or passed through.
//!
//! This function is used to select the inversion mode for the selected PWM
//! outputs.  The outputs are selected using the parameter \e ulPWMOutBits.
//! The parameter \e bInvert determines the inversion mode for the selected
//! outputs.  If \e bInvert is \b xtrue, this function causes the specified
//! PWM output signals to be inverted or made active low.  If \e bInvert is
//! \b xfalse, the specified outputs are passed through as is or made active
//! high.
//!
//! \return None.
//
//*****************************************************************************
void
PWMOutputInvert(unsigned long ulBase, unsigned long ulPWMOutBits,
                xtBoolean bInvert)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT(!(ulPWMOutBits & ~(PWM_OUT_0_BIT | PWM_OUT_1_BIT | PWM_OUT_2_BIT |
                              PWM_OUT_3_BIT | PWM_OUT_4_BIT | PWM_OUT_5_BIT |
                              PWM_OUT_6_BIT | PWM_OUT_7_BIT)));

    //
    // Read the module's INVERT output control register and set or clear the
    // requested bits.
    //
    if(bInvert == xtrue)
    {
        xHWREG(ulBase + PWM_O_INVERT) |= ulPWMOutBits;
    }
    else
    {
        xHWREG(ulBase + PWM_O_INVERT) &= ~(ulPWMOutBits);
    }
}

//*****************************************************************************
//
//! Specifies the level of PWM outputs suppressed in response to a fault
//! condition.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulPWMOutBits are the PWM outputs to be modified.  This parameter
//! must be the logical OR of any of \b PWM_OUT_0_BIT, \b PWM_OUT_1_BIT,
//! \b PWM_OUT_2_BIT, \b PWM_OUT_3_BIT, \b PWM_OUT_4_BIT, \b PWM_OUT_5_BIT,
//! \b PWM_OUT_6_BIT, or \b PWM_OUT_7_BIT.
//! \param bDriveHigh determines if the signal is driven high or low during an
//! active fault condition.
//!
//! This function determines whether a PWM output pin that is suppressed in
//! response to a fault condition is driven high or low.  The affected outputs
//! are selected using the parameter \e ulPWMOutBits.  The parameter
//! \e bDriveHigh determines the output level for the pins identified by
//! \e ulPWMOutBits.  If \e bDriveHigh is \b xtrue then the selected outputs are
//! driven high when a fault is detected.  If it is \e xfalse, the pins are
//! driven low.
//!
//! In a fault condition, pins which have not been configured to be suppressed
//! via a call to PWMOutputFault() are unaffected by this function.
//!
//! \note This function is available only on devices which support extended
//! PWM fault handling.
//!
//! \return None.
//
//*****************************************************************************
void
PWMOutputFaultLevel(unsigned long ulBase, unsigned long ulPWMOutBits,
                    xtBoolean bDriveHigh)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT(!(ulPWMOutBits & ~(PWM_OUT_0_BIT | PWM_OUT_1_BIT | PWM_OUT_2_BIT |
                              PWM_OUT_3_BIT | PWM_OUT_4_BIT | PWM_OUT_5_BIT |
                              PWM_OUT_6_BIT | PWM_OUT_7_BIT)));

    //
    // Read the module's FAULT output control register and set or clear the
    // requested bits.
    //
    if(bDriveHigh == xtrue)
    {
        xHWREG(ulBase + PWM_O_FAULTVAL) |= ulPWMOutBits;
    }
    else
    {
        xHWREG(ulBase + PWM_O_FAULTVAL) &= ~(ulPWMOutBits);
    }
}

//*****************************************************************************
//
//! Specifies the state of PWM outputs in response to a fault condition.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulPWMOutBits are the PWM outputs to be modified.  This parameter
//! must be the  logical OR of any of \b PWM_OUT_0_BIT, \b PWM_OUT_1_BIT,
//! \b PWM_OUT_2_BIT, \b PWM_OUT_3_BIT, \b PWM_OUT_4_BIT, \b PWM_OUT_5_BIT,
//! \b PWM_OUT_6_BIT, or \b PWM_OUT_7_BIT.
//! \param bFaultSuppress determines if the signal is suppressed or passed
//! through during an active fault condition.
//!
//! This function sets the fault handling characteristics of the selected PWM
//! outputs.  The outputs are selected using the parameter \e ulPWMOutBits.
//! The parameter \e bFaultSuppress determines the fault handling
//! characteristics for the selected outputs.  If \e bFaultSuppress is \b xtrue,
//! then the selected outputs are made inactive.  If \e bFaultSuppress is
//! \b xfalse, then the selected outputs are unaffected by the detected fault.
//!
//! On devices supporting extended PWM fault handling, the state the affected
//! output pins are driven to can be configured with PWMOutputFaultLevel().  If
//! not configured, or if the device does not support extended PWM fault
//! handling, affected outputs are driven low on a fault condition.
//!
//! \return None.
//
//*****************************************************************************
void
PWMOutputFault(unsigned long ulBase, unsigned long ulPWMOutBits,
               xtBoolean bFaultSuppress)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT(!(ulPWMOutBits & ~(PWM_OUT_0_BIT | PWM_OUT_1_BIT | PWM_OUT_2_BIT |
                              PWM_OUT_3_BIT | PWM_OUT_4_BIT | PWM_OUT_5_BIT |
                              PWM_OUT_6_BIT | PWM_OUT_7_BIT)));

    //
    // Read the module's FAULT output control register and set or clear the
    // requested bits.
    //
    if(bFaultSuppress == xtrue)
    {
        xHWREG(ulBase + PWM_O_FAULT) |= ulPWMOutBits;
    }
    else
    {
        xHWREG(ulBase + PWM_O_FAULT) &= ~(ulPWMOutBits);
    }
}


//*****************************************************************************
//
//! Enables interrupts and triggers for the specified PWM generator block.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator to have interrupts and triggers enabled.
//! This parameter must be one of \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2, or
//! \b PWM_GEN_3.
//! \param ulIntTrig specifies the interrupts and triggers to be enabled.
//!
//! This function unmasks the specified interrupt(s) and trigger(s) by setting
//! the specified bits of the interrupt/trigger enable register for the
//! specified PWM generator.  The \e ulIntTrig parameter is the logical OR of
//! \b PWM_INT_CNT_ZERO, \b PWM_INT_CNT_LOAD, \b PWM_INT_CNT_AU,
//! \b PWM_INT_CNT_AD, \b PWM_INT_CNT_BU, \b PWM_INT_CNT_BD,
//! \b PWM_TR_CNT_ZERO, \b PWM_TR_CNT_LOAD, \b PWM_TR_CNT_AU, \b PWM_TR_CNT_AD,
//! \b PWM_TR_CNT_BU, or \b PWM_TR_CNT_BD.
//!
//! \return None.
//
//*****************************************************************************
void
PWMGenIntTrigEnable(unsigned long ulBase, unsigned long ulGen,
                    unsigned long ulIntTrig)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );
    xASSERT((ulIntTrig & ~(PWM_INT_CNT_ZERO | PWM_INT_CNT_LOAD |
                          PWM_INT_CNT_AU | PWM_INT_CNT_AD | PWM_INT_CNT_BU |
                          PWM_INT_CNT_BD | PWM_TR_CNT_ZERO | PWM_TR_CNT_LOAD |
                          PWM_TR_CNT_AU | PWM_TR_CNT_AD | PWM_TR_CNT_BU |
                          PWM_TR_CNT_BD)) == 0);

    //
    // Enable the specified interrupts/triggers.
    //
    xHWREG(PWM_GEN_BADDR(ulBase, ulGen) + PWM_O_X_INTEN) |= ulIntTrig;
}

//*****************************************************************************
//
//! Disables interrupts for the specified PWM generator block.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator to have interrupts and triggers disabled.
//! This parameter must be one of \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2, or
//! \b PWM_GEN_3.
//! \param ulIntTrig specifies the interrupts and triggers to be disabled.
//!
//! This function masks the specified interrupt(s) and trigger(s) by clearing
//! the specified bits of the interrupt/trigger enable register for the
//! specified PWM generator.  The \e ulIntTrig parameter is the logical OR of
//! \b PWM_INT_CNT_ZERO, \b PWM_INT_CNT_LOAD, \b PWM_INT_CNT_AU,
//! \b PWM_INT_CNT_AD, \b PWM_INT_CNT_BU, \b PWM_INT_CNT_BD,
//! \b PWM_TR_CNT_ZERO, \b PWM_TR_CNT_LOAD, \b PWM_TR_CNT_AU, \b PWM_TR_CNT_AD,
//! \b PWM_TR_CNT_BU, or \b PWM_TR_CNT_BD.
//!
//! \return None.
//
//*****************************************************************************
void
PWMGenIntTrigDisable(unsigned long ulBase, unsigned long ulGen,
                     unsigned long ulIntTrig)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );
    xASSERT((ulIntTrig & ~(PWM_INT_CNT_ZERO | PWM_INT_CNT_LOAD |
                          PWM_INT_CNT_AU | PWM_INT_CNT_AD | PWM_INT_CNT_BU |
                          PWM_INT_CNT_BD | PWM_TR_CNT_ZERO | PWM_TR_CNT_LOAD |
                          PWM_TR_CNT_AU | PWM_TR_CNT_AD | PWM_TR_CNT_BU |
                          PWM_TR_CNT_BD)) == 0);

    //
    // Disable the specified interrupts/triggers.
    //
    xHWREG(PWM_GEN_BADDR(ulBase, ulGen) + PWM_O_X_INTEN) &= ~(ulIntTrig);
}

//*****************************************************************************
//
//! Gets interrupt status for the specified PWM generator block.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator to query.  This parameter must be one of
//! \b PWM_GEN_0,  \b PWM_GEN_1, \b PWM_GEN_2, or \b PWM_GEN_3.
//! \param bMasked specifies whether masked or raw interrupt status is
//! returned.
//!
//! If \e bMasked is set as \b xtrue, then the masked interrupt status is
//! returned; otherwise, the raw interrupt status is returned.
//!
//! \return Returns the contents of the interrupt status register or the
//! contents of the raw interrupt status register for the specified
//! PWM generator.
//
//*****************************************************************************
unsigned long
PWMGenIntStatus(unsigned long ulBase, unsigned long ulGen, xtBoolean bMasked)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );

    //
    // Compute the generator's base address.
    //
    ulGen = PWM_GEN_BADDR(ulBase, ulGen);

    //
    // Read and return the specified generator's raw or enabled interrupt
    // status.
    //
    if(bMasked == xtrue)
    {
        return(xHWREG(ulGen + PWM_O_X_ISC));
    }
    else
    {
        return(xHWREG(ulGen + PWM_O_X_RIS));
    }
}

//*****************************************************************************
//
//! Clears the specified interrupt(s) for the specified PWM generator block.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator to query.  This parameter must be one of
//! \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2, or \b PWM_GEN_3.
//! \param ulInts specifies the interrupts to be cleared.
//!
//! This funciton clears the specified interrupt(s) by writing a 1 to the
//! specified bits of the interrupt status register for the specified PWM
//! generator.  The \e ulInts parameter is the logical OR of
//! \b PWM_INT_CNT_ZERO, \b PWM_INT_CNT_LOAD, \b PWM_INT_CNT_AU,
//! \b PWM_INT_CNT_AD, \b PWM_INT_CNT_BU, or \b PWM_INT_CNT_BD.
//!
//! \note Because there is a write buffer in the Cortex-M processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
void
PWMGenIntClear(unsigned long ulBase, unsigned long ulGen, unsigned long ulInts)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );
    xASSERT((ulInts & ~(PWM_INT_CNT_ZERO | PWM_INT_CNT_LOAD | PWM_INT_CNT_AU |
                       PWM_INT_CNT_AD | PWM_INT_CNT_BU | PWM_INT_CNT_BD)) ==
           0);

    //
    // Clear the requested interrupts by writing ones to the specified bit
    // of the module's interrupt enable register.
    //
    xHWREG(PWM_GEN_BADDR(ulBase, ulGen) + PWM_O_X_ISC) = ulInts;
}

//*****************************************************************************
//
//! Enables generator and fault interrupts for a PWM module.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGenFault contains the interrupts to be enabled.  This parameter
//! must be a logical OR of any of \b PWM_INT_GEN_0, \b PWM_INT_GEN_1,
//! \b PWM_INT_GEN_2, \b PWM_INT_GEN_3, \b PWM_INT_FAULT0, \b PWM_INT_FAULT1,
//! \b PWM_INT_FAULT2, or \b PWM_INT_FAULT3.
//!
//! This function unmasks the specified interrupt(s) by setting the specified
//! bits of the interrupt enable register for the selected PWM module.
//!
//! \return None.
//
//*****************************************************************************
void
PWMIntEnable(unsigned long ulBase, unsigned long ulGenFault)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT((ulGenFault & ~(PWM_INT_GEN_0 | PWM_INT_GEN_1 | PWM_INT_GEN_2 |
                           PWM_INT_GEN_3 | PWM_INT_FAULT0 | PWM_INT_FAULT1 |
                           PWM_INT_FAULT2 | PWM_INT_FAULT3)) == 0);

    //
    // Read the module's interrupt enable register and enable interrupts
    // for the specified PWM generators.
    //
    xHWREG(ulBase + PWM_O_INTEN) |= ulGenFault;
}

//*****************************************************************************
//
//! Disables generator and fault interrupts for a PWM module.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGenFault contains the interrupts to be disabled.  This parameter
//! must be a logical OR of any of \b PWM_INT_GEN_0, \b PWM_INT_GEN_1,
//! \b PWM_INT_GEN_2, \b PWM_INT_GEN_3, \b PWM_INT_FAULT0, \b PWM_INT_FAULT1,
//! \b PWM_INT_FAULT2, or \b PWM_INT_FAULT3.
//!
//! This function masks the specified interrupt(s) by clearing the specified
//! bits of the interrupt enable register for the selected PWM module.
//!
//! \return None.
//
//*****************************************************************************
void
PWMIntDisable(unsigned long ulBase, unsigned long ulGenFault)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT((ulGenFault & ~(PWM_INT_GEN_0 | PWM_INT_GEN_1 | PWM_INT_GEN_2 |
                           PWM_INT_GEN_3 | PWM_INT_FAULT0 | PWM_INT_FAULT1 |
                           PWM_INT_FAULT2 | PWM_INT_FAULT3)) == 0);

    //
    // Read the module's interrupt enable register and disable interrupts
    // for the specified PWM generators.
    //
    xHWREG(ulBase + PWM_O_INTEN) &= ~(ulGenFault);
}

//*****************************************************************************
//
//! Clears the fault interrupt for a PWM module.
//!
//! \param ulBase is the base address of the PWM module.
//!
//! This function clears the fault interrupt by writing to the appropriate bit
//! of the interrupt status register for the selected PWM module.
//!
//! This function clears only the FAULT0 interrupt and is retained for
//! backwards compatibility.  It is recommended that PWMFaultIntClearExt() be
//! used instead because it supports all fault interrupts supported on devices
//! with and without extended PWM fault handling support.
//!
//! \note Because there is a write buffer in the Cortex-M processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
void
PWMFaultIntClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));

    //
    // Write the only writeable bit in the module's interrupt register.
    //
    xHWREG(ulBase + PWM_O_ISC) = PWM_ISC_INTFAULT0;
}

//*****************************************************************************
//
//! Gets the interrupt status for a PWM module.
//!
//! \param ulBase is the base address of the PWM module.
//! \param bMasked specifies whether masked or raw interrupt status is
//! returned.
//!
//! If \e bMasked is set as \b xtrue, then the masked interrupt status is
//! returned; otherwise, the raw interrupt status is returned.
//!
//! \return The current interrupt status, enumerated as a bit field of
//! \b PWM_INT_GEN_0, \b PWM_INT_GEN_1, \b PWM_INT_GEN_2, \b PWM_INT_GEN_3,
//! \b PWM_INT_FAULT0, \b PWM_INT_FAULT1, \b PWM_INT_FAULT2, and
//! \b PWM_INT_FAULT3.
//!
//*****************************************************************************
unsigned long
PWMIntStatus(unsigned long ulBase, xtBoolean bMasked)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));

    //
    // Read and return either the module's raw or enabled interrupt status.
    //
    if(bMasked == xtrue)
    {
        return(xHWREG(ulBase + PWM_O_ISC));
    }
    else
    {
        return(xHWREG(ulBase + PWM_O_RIS));
    }
}

//*****************************************************************************
//
//! Clears the fault interrupt for a PWM module.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulFaultInts specifies the fault interrupts to clear.
//!
//! This function clears one or more fault interrupts by writing to the
//!  appropriate bit of the PWM interrupt status register.  The parameter
//! \e ulFaultInts must be the logical OR of any of \b PWM_INT_FAULT0,
//! \b PWM_INT_FAULT1, \b PWM_INT_FAULT2, or \b PWM_INT_FAULT3.
//!
//! When running on a device supporting extended PWM fault handling, the fault
//! interrupts are derived by performing a logical OR of each of the configured
//! fault trigger signals for a given generator.  Therefore, these interrupts
//! are not directly related to the four possible FAULTn inputs to the device
//! but indicate that a fault has been signaled to one of the four possible PWM
//! generators.  On a device without extended PWM fault handling, the interrupt
//! is directly related to the state of the single FAULT pin.
//!
//! \note Because there is a write buffer in the Cortex-M processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
void
PWMFaultIntClearExt(unsigned long ulBase, unsigned long ulFaultInts)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT((ulFaultInts & ~(PWM_INT_FAULT0 | PWM_INT_FAULT1 |
                            PWM_INT_FAULT2 | PWM_INT_FAULT3)) == 0);

    //
    // Clear the supplied fault bits.
    //
    xHWREG(ulBase + PWM_O_ISC) = ulFaultInts;
}

//*****************************************************************************
//
//! Configures the minimum fault period and fault pin senses for a given
//! PWM generator.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator for which fault configuration is being
//! set. This function must be one of \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2,
//! or \b PWM_GEN_3.
//! \param ulMinFaultPeriod is the minimum fault active period expressed in
//! PWM clock cycles.
//! \param ulFaultSenses indicates which sense of each FAULT input should be
//! considered the ``asserted'' state.  Valid values are logical OR
//! combinations of \b PWM_FAULTn_SENSE_HIGH and \b PWM_FAULTn_SENSE_LOW.
//!
//! This function configures the minimum fault period for a given generator
//! along with the sense of each of the 4 possible fault inputs.  The minimum
//! fault period is expressed in PWM clock cycles and takes effect only if
//! PWMGenConfigure() is called with flag \b PWM_GEN_MODE_FAULT_PER set in the
//! \e ulConfig parameter.  When a fault input is asserted, the minimum fault
//! period timer ensures that it remains asserted for at least the number of
//! clock cycles specified.
//!
//! \note This function is only available on devices supporting extended PWM
//! fault handling.
//!
//! \return None.
//
//*****************************************************************************
void
PWMGenFaultConfigure(unsigned long ulBase, unsigned long ulGen,
                     unsigned long ulMinFaultPeriod,
                     unsigned long ulFaultSenses)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );
    xASSERT(ulMinFaultPeriod < PWM_X_MINFLTPER_M);
    xASSERT((ulFaultSenses & ~(PWM_FAULT0_SENSE_HIGH | PWM_FAULT0_SENSE_LOW |
                              PWM_FAULT1_SENSE_HIGH | PWM_FAULT1_SENSE_LOW |
                              PWM_FAULT2_SENSE_HIGH | PWM_FAULT2_SENSE_LOW |
                              PWM_FAULT3_SENSE_HIGH | PWM_FAULT3_SENSE_LOW)) ==
           0);

    //
    // Write the minimum fault period.
    //
    xHWREG(PWM_GEN_BADDR(ulBase, ulGen) + PWM_O_X_MINFLTPER) = ulMinFaultPeriod;

    //
    // Write the fault senses.
    //
    xHWREG(PWM_GEN_EXT_BADDR(ulBase, ulGen) + PWM_O_X_FLTSEN) = ulFaultSenses;
}

//*****************************************************************************
//
//! Configures the set of fault triggers for a given PWM generator.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator for which fault triggers are being set.
//! This parameter must be one of \b PWM_GEN_0, \b PWM_GEN_1, \b PWM_GEN_2, or
//! \b PWM_GEN_3.
//! \param ulGroup indicates the subset of possible faults that are to be
//! configured.  This parameter must be \b PWM_FAULT_GROUP_0 or
//! \b PWM_FAULT_GROUP_1.
//! \param ulFaultTriggers defines the set of inputs that are to contribute
//! towards generation of the fault signal to the given PWM generator.  For
//! \b PWM_FAULT_GROUP_0, this is the logical OR of \b PWM_FAULT_FAULT0,
//! \b PWM_FAULT_FAULT1, \b PWM_FAULT_FAULT2, or \b PWM_FAULT_FAULT3.  For
//! \b PWM_FAULT_GROUP_1, this is the logical OR of \b PWM_FAULT_DCMP0,
//! \b PWM_FAULT_DCMP1, \b PWM_FAULT_DCMP2, \b PWM_FAULT_DCMP3,
//! \b PWM_FAULT_DCMP4, \b PWM_FAULT_DCMP5, \b PWM_FAULT_DCMP6, or
//! \b PWM_FAULT_DCMP7.
//!
//! This function allows selection of the set of fault inputs that is combined
//! to generate a fault condition to a given PWM generator.  By default, all
//! generators use only FAULT0 (for backwards compatibility) but if
//! PWMGenConfigure() is called with flag \b PWM_GEN_MODE_FAULT_SRC in the
//! \e ulConfig parameter, extended fault handling is enabled and this function
//! must be called to configure the fault triggers.
//!
//! The fault signal to the PWM generator is generated by ORing together each
//! of the signals specified in the \e ulFaultTriggers parameter after having
//! adjusted the sense of each FAULTn input based on the configuration
//! previously set using a call to PWMGenFaultConfigure().
//!
//! \note This function is only available on devices supporting extended PWM
//! fault handling.
//!
//! \return None.
//
//*****************************************************************************
void
PWMGenFaultTriggerSet(unsigned long ulBase, unsigned long ulGen,
                      unsigned long ulGroup, unsigned long ulFaultTriggers)
{
    //
    // Check for valid parameters.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );
    xASSERT((ulGroup == PWM_FAULT_GROUP_0) || (ulGroup == PWM_FAULT_GROUP_1));
    xASSERT((ulGroup == PWM_FAULT_GROUP_0) &&
           ((ulFaultTriggers & ~(PWM_FAULT_FAULT0 | PWM_FAULT_FAULT1 |
                                 PWM_FAULT_FAULT2 | PWM_FAULT_FAULT3)) == 0));
    xASSERT((ulGroup == PWM_FAULT_GROUP_1) &&
           ((ulFaultTriggers & ~(PWM_FAULT_DCMP0 | PWM_FAULT_DCMP1 |
                                 PWM_FAULT_DCMP2 | PWM_FAULT_DCMP3 |
                                 PWM_FAULT_DCMP4 | PWM_FAULT_DCMP5 |
                                 PWM_FAULT_DCMP6 | PWM_FAULT_DCMP7)) == 0));

    //
    // Write the fault triggers to the appropriate register.
    //
    if(ulGroup == PWM_FAULT_GROUP_0)
    {
        xHWREG(PWM_GEN_BADDR(ulBase, ulGen) + PWM_O_X_FLTSRC0) =
            ulFaultTriggers;
    }
    else
    {
        xHWREG(PWM_GEN_BADDR(ulBase, ulGen) + PWM_O_X_FLTSRC1) =
            ulFaultTriggers;
    }
}

//*****************************************************************************
//
//! Returns the set of fault triggers currently configured for a given PWM
//! generator.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator for which fault triggers are being
//! queried. This parameter must be one of \b PWM_GEN_0, \b PWM_GEN_1,
//! \b PWM_GEN_2, or \b PWM_GEN_3.
//! \param ulGroup indicates the subset of faults that are being queried.  This
//! parameter must be \b PWM_FAULT_GROUP_0 or \b PWM_FAULT_GROUP_1.
//!
//! This function allows an application to query the current set of inputs that
//! contribute to the generation of a fault condition to a given PWM generator.
//!
//! \note This function is only available on devices supporting extended PWM
//! fault handling.
//!
//! \return Returns the current fault triggers configured for the fault group
//! provided.  For \b PWM_FAULT_GROUP_0, the returned value is a logical OR of
//! \b PWM_FAULT_FAULT0, \b PWM_FAULT_FAULT1, \b PWM_FAULT_FAULT2, or
//! \b PWM_FAULT_FAULT3.  For \b PWM_FAULT_GROUP_1, the return value is the
//! logical OR of \b PWM_FAULT_DCMP0, \b PWM_FAULT_DCMP1,
//! \b PWM_FAULT_DCMP2, \b PWM_FAULT_DCMP3, \b PWM_FAULT_DCMP4,
//! \b PWM_FAULT_DCMP5, \b PWM_FAULT_DCMP6, or \b PWM_FAULT_DCMP7.
//
//*****************************************************************************
unsigned long
PWMGenFaultTriggerGet(unsigned long ulBase, unsigned long ulGen,
                      unsigned long ulGroup)
{
    //
    // Check for valid parameters.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );
    xASSERT((ulGroup == PWM_FAULT_GROUP_0) || (ulGroup == PWM_FAULT_GROUP_1));

    //
    // Return the current fault triggers.
    //
    if(ulGroup == PWM_FAULT_GROUP_0)
    {
        return(xHWREG(PWM_GEN_BADDR(ulBase, ulGen) + PWM_O_X_FLTSRC0));
    }
    else
    {
        return(xHWREG(PWM_GEN_BADDR(ulBase, ulGen) + PWM_O_X_FLTSRC1));
    }
}

//*****************************************************************************
//
//! Returns the current state of the fault triggers for a given PWM generator.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator for which fault trigger states are being
//! queried.  This parameter must be one of \b PWM_GEN_0, \b PWM_GEN_1,
//! \b PWM_GEN_2, or \b PWM_GEN_3.
//! \param ulGroup indicates the subset of faults that are being queried.  This
//! parameter must be \b PWM_FAULT_GROUP_0 or \b PWM_FAULT_GROUP_1.
//!
//! This function allows an application to query the current state of each of
//! the fault trigger inputs to a given PWM generator.  The current state of
//! each fault trigger input is returned unless PWMGenConfigure() has
//! previously been called with flag \b PWM_GEN_MODE_LATCH_FAULT in the
//! \e ulConfig parameter, in which case the returned status is the latched
//! fault trigger status.
//!
//! If latched faults are configured, the application must call
//! PWMGenFaultClear() to clear each trigger.
//!
//! \note This function is only available on devices supporting extended PWM
//! fault handling.
//!
//! \return Returns the current state of the fault triggers for the given PWM
//! generator.  A set bit indicates that the associated trigger is active.  For
//! \b PWM_FAULT_GROUP_0, the returned value is a logical OR of
//! \b PWM_FAULT_FAULT0, \b PWM_FAULT_FAULT1, \b PWM_FAULT_FAULT2, or
//! \b PWM_FAULT_FAULT3.  For \b PWM_FAULT_GROUP_1, the return value is the
//! logical OR of \b PWM_FAULT_DCMP0, \b PWM_FAULT_DCMP1,
//! \b PWM_FAULT_DCMP2, \b PWM_FAULT_DCMP3, \b PWM_FAULT_DCMP4,
//! \b PWM_FAULT_DCMP5, \b PWM_FAULT_DCMP6, or \b PWM_FAULT_DCMP7.
//
//*****************************************************************************
unsigned long
PWMGenFaultStatus(unsigned long ulBase, unsigned long ulGen,
                  unsigned long ulGroup)
{
    //
    // Check for valid parameters.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );
    xASSERT((ulGroup == PWM_FAULT_GROUP_0) || (ulGroup == PWM_FAULT_GROUP_1));

    //
    // Return the current fault status.
    //
    if(ulGroup == PWM_FAULT_GROUP_0)
    {
        return(xHWREG(PWM_GEN_EXT_BADDR(ulBase, ulGen) + PWM_O_X_FLTSTAT0));
    }
    else
    {
        return(xHWREG(PWM_GEN_EXT_BADDR(ulBase, ulGen) + PWM_O_X_FLTSTAT1));
    }
}

//*****************************************************************************
//
//! Clears one or more latched fault triggers for a given PWM generator.
//!
//! \param ulBase is the base address of the PWM module.
//! \param ulGen is the PWM generator for which fault trigger states are being
//! queried.  This parameter must be one of \b PWM_GEN_0, \b PWM_GEN_1,
//! \b PWM_GEN_2, or \b PWM_GEN_3.
//! \param ulGroup indicates the subset of faults that are being queried.  This
//! parameter must be \b PWM_FAULT_GROUP_0 or \b PWM_FAULT_GROUP_1.
//! \param ulFaultTriggers is the set of fault triggers which are to be
//! cleared.
//!
//! This function allows an application to clear the fault triggers for a given
//! PWM generator.  This function is only required if PWMGenConfigure() has
//! previously been called with flag \b PWM_GEN_MODE_LATCH_FAULT in parameter
//! \e ulConfig.
//!
//! \note This function is only available on devices supporting extended PWM
//! fault handling.
//!
//! \return None.
//
//*****************************************************************************
void
PWMGenFaultClear(unsigned long ulBase, unsigned long ulGen,
                 unsigned long ulGroup, unsigned long ulFaultTriggers)
{
    //
    // Check for valid parameters.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen == PWM_GEN_1) ||
             (ulGen == PWM_GEN_2) || (ulGen == PWM_GEN_3) );
    xASSERT((ulGroup == PWM_FAULT_GROUP_0) || (ulGroup == PWM_FAULT_GROUP_1));
    xASSERT((ulGroup == PWM_FAULT_GROUP_0) &&
           ((ulFaultTriggers & ~(PWM_FAULT_FAULT0 | PWM_FAULT_FAULT1 |
                                 PWM_FAULT_FAULT2 | PWM_FAULT_FAULT3)) == 0));
    xASSERT((ulGroup == PWM_FAULT_GROUP_1) &&
           ((ulFaultTriggers & ~(PWM_FAULT_DCMP0 | PWM_FAULT_DCMP1 |
                                 PWM_FAULT_DCMP2 | PWM_FAULT_DCMP3 |
                                 PWM_FAULT_DCMP4 | PWM_FAULT_DCMP5 |
                                 PWM_FAULT_DCMP6 | PWM_FAULT_DCMP7)) == 0));

    //
    // Clear the given faults.
    //
    if(ulGroup == PWM_FAULT_GROUP_0)
    {
        xHWREG(PWM_GEN_EXT_BADDR(ulBase, ulGen) + PWM_O_X_FLTSTAT0) =
            ulFaultTriggers;
    }
    else
    {
        xHWREG(PWM_GEN_EXT_BADDR(ulBase, ulGen) + PWM_O_X_FLTSTAT1) =
            ulFaultTriggers;
    }
}


//*****************************************************************************
//
//! \brief Get the other input clock frequency.
//!
//! \param None.
//!
//! This function is to get the System Other input frequency.
//!
//! \note this function is only called by GetSysClock function.
//!       other input clock indicates that all other input source except PLL.
//!
//! \return The Others Input Clock Frequency.
//
//*****************************************************************************

static unsigned long GetOtherOscClock(void)
{
    const unsigned long ERROR = 0;
    unsigned long OscSrc     = 0;
    unsigned long OtherClock = 0;

    // get other osc clock
    if(xHWREG(SYSCTL_RCC2) & SYSCTL_RCC2_USERCC2 != 0)           // Use RCC2
    {
        OscSrc = xHWREG(SYSCTL_RCC2) & SYSCTL_RCC2_OSCSRC2_M ;
        switch (OscSrc)
        {
            case SYSCTL_RCC2_OSCSRC2_MO :
                {
                    unsigned long tmp = xHWREG(SYSCTL_RCC) & SYSCTL_RCC_XTAL_M;
                    OtherClock = ValueToClockTbl[tmp];
                    break;
                }
            case SYSCTL_RCC2_OSCSRC2_IO :
                {
                    OtherClock = 16000000;
                    break;
                }
            case SYSCTL_RCC2_OSCSRC2_IO4:
                {
                    OtherClock = 4000000;
                    break;
                }
            case SYSCTL_RCC2_OSCSRC2_30 :
                {
                    OtherClock = 30000;
                    break;
                }
            case SYSCTL_RCC2_OSCSRC2_419:
                {
                    OtherClock = 4194304;
                    break;
                }
            case SYSCTL_RCC2_OSCSRC2_32 :
                {
                    OtherClock = 32768;
                    break;
                }
            default:                                          // Unknown Config
                {
                    return ERROR;
                }
        }
    }
    else                                                      // Use RCC
    {
        OscSrc = xHWREG(SYSCTL_RCC) & SYSCTL_RCC_OSCSRC_M;
        switch(OscSrc)
        {
            case SYSCTL_RCC_OSCSRC_MAIN:
                {
                    unsigned long tmp = xHWREG(SYSCTL_RCC) & SYSCTL_RCC_XTAL_M;
                    OtherClock = ValueToClockTbl[tmp];
                    break;
                }
            case SYSCTL_RCC_OSCSRC_INT:
                {
                    OtherClock = 16000000;
                    break;
                }
            case SYSCTL_RCC_OSCSRC_INT4:
                {
                    OtherClock = 4000000;
                    break;
                }
            case SYSCTL_RCC_OSCSRC_30:
                {
                    OtherClock = 30000;
                    break;
                }
            default:                                          // Unknown Config
                {
                    return ERROR;
                }
        }
    }

    return OtherClock;
}


//*****************************************************************************
//
//! \brief Get the system clock frequency.
//!
//! \param None.
//!
//! This function is to get the System clock frequency.
//!
//! \note
//!  -# this function is only used in this file.
//!  -# if occur error,then function will return ERROR(0).
//!
//! \return The System Clock Frequency.
//
//
//*****************************************************************************

static unsigned long GetSysClock(void)
{
    const unsigned long ERROR                 = 0;
    const unsigned long PLL400M               = 400000000UL;
    const unsigned long PLL200M               = 200000000UL;

    unsigned long SysDiv    = 0;
    unsigned long SysClock  = 0;

    unsigned long tRCC      = xHWREG(SYSCTL_RCC);
    unsigned long tRCC2     = xHWREG(SYSCTL_RCC2);

    if((tRCC2 & SYSCTL_RCC2_USERCC2) != 0)                   // Use RCC2
    {
        if((tRCC2 & SYSCTL_RCC2_BYPASS2) != 0)               // Use Other Osc
        {
            if((tRCC & SYSCTL_RCC_USEPWMDIV) != 0)           // Divide Clock
            {
                SysDiv   = tRCC2 & SYSCTL_RCC2_SYSDIV2_M;
                SysDiv   = SysDiv >> SYSCTL_RCC2_SYSDIV2_S;
                if(SysDiv != 0)
                {
                    SysClock = GetOtherOscClock() / (SysDiv + 1);
                }
                else
                {
                    SysClock = GetOtherOscClock() / 2;        // Special case
                }
            }
            else
            {
                SysClock = GetOtherOscClock();
            }
        }
        else                                                  // Use PLL Source
        {
            if((tRCC2 & SYSCTL_RCC2_DIV400) != 0)             // PLL 400MHz
            {
                SysDiv = tRCC2 & (SYSCTL_RCC2_SYSDIV2_M
                                            | SYSCTL_RCC2_SYSDIV2LSB);
                SysDiv = SysDiv >> (SYSCTL_RCC2_SYSDIV2_S - 1);
                if(SysDiv <= 3)
                {
                    return ERROR;
                }
                else
                {
                    SysClock = PLL400M / (SysDiv + 1);
                }
            }
            else                                                 // 200MHz
            {
                SysDiv = tRCC2 & SYSCTL_RCC2_SYSDIV2_M;
                SysDiv = SysDiv >> SYSCTL_RCC2_SYSDIV2_S;

                //When PLL is configured to 200MHz , SysDiv MUST NOT set 0/1
                if((SysDiv == 0) || (SysDiv == 1))
                {
                    return ERROR;
                }
                else
                {
                    SysClock = PLL200M / (SysDiv + 1);
                }
            }

        }
    }
    else                                                        // Use RCC
    {
        if (((tRCC & SYSCTL_RCC_BYPASS)) != 0)                  // Use Other Osc
        {
            if((tRCC & SYSCTL_RCC_USEPWMDIV) != 0)              // Divide Clock
            {
                SysDiv   = tRCC & SYSCTL_RCC_SYSDIV_M;
                SysDiv   = SysDiv >> SYSCTL_RCC_SYSDIV_S;
                if(SysDiv != 0)
                {
                    SysClock = GetOtherOscClock() / (SysDiv + 1);
                }
                else
                {
                    SysClock = GetOtherOscClock() / 2;          // Special case
                }
            }
            else
            {
                SysClock = GetOtherOscClock();
            }
        }
        else                                                    // Use PLL
        {
            SysDiv = tRCC & SYSCTL_RCC_SYSDIV_M;
            SysDiv = SysDiv >> SYSCTL_RCC_SYSDIV_S;

            //When PLL is configured to 200MHz , SysDiv MUST NOT set 0/1
            if((SysDiv == 0) || (SysDiv == 1))
            {
                return ERROR;
            }
            else
            {
                SysClock = PLL200M / (SysDiv + 1);
            }
        }

    }

    return SysClock;
}


//*****************************************************************************
//
//! \brief Get the PWM module input clock frequency.
//!
//! \param None.
//!
//! This function is to get the PWM module input frequency,
//!
//! \note this function is called by PWMFrequencyxxx function, only used in this
//!   file.
//!
//! \return The Input Clock Frequency.
//
//*****************************************************************************

static unsigned long PwmClockGet(void)
{

    unsigned long SysClock  = GetSysClock();
    unsigned long PwmClock  = 0;
    unsigned long PwmDiv    = 0;
    unsigned long UsePwmDiv = 0;
    const unsigned long FreDivTbl[8] =
    {
        1 ,        // 2  = 2^1
        2 ,        // 4  = 2^2
        3 ,        // 8  = 2^3
        4 ,        // 16 = 2^4
        5 ,        // 32 = 2^5
        6 ,        // 64 = 2^6
        6 ,        // 64 = 2^6
        6 ,        // 64 = 2^6
    };

    UsePwmDiv = xHWREG(SYSCTL_RCC) & SYSCTL_RCC_USEPWMDIV;

    if(UsePwmDiv != 0)             //Use Pwm Divide as the PWM Clock Source
    {
        //
        // Get Pwm Divisor
        //
        PwmDiv = xHWREG(SYSCTL_RCC) & SYSCTL_RCC_PWMDIV_M;
        PwmDiv = FreDivTbl[ PwmDiv >> SYSCTL_RCC_PWMDIV_S ];

        //
        // Get Pwm Clock Frequency
        //
        PwmClock = SysClock >> PwmDiv;
    }
    else                           //Use System Clock as the PWM Clock Source
    {
        //
        // Get Pwm Clock Frequency
        //
        PwmClock = SysClock;
    }

    return PwmClock;
}

//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulFrequency is the PWM frequency of PWM channel.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~7
//! when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value 0~3.
//! when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value 4~7.
//!
//! The \e ulFrequency parameter can be values:  0 ~ PWM module input clock.
//!
//! \note if input value of Frequency or the Channel is invaild, then the function
//!       will return ERROR(0) .
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long  xPWMFrequencySet(unsigned long ulBase,
                                unsigned long ulChannel,
                                unsigned long ulFrequency)
{
    const unsigned long ERROR = 0;

    unsigned long PwmGen    = 0;
    unsigned long ActualFre = 0;
    unsigned long PwmClock  = PwmClockGet();


    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulChannel == PWM_OUT_0_BIT) || (ulChannel == PWM_OUT_1_BIT) ||
            (ulChannel == PWM_OUT_2_BIT) || (ulChannel == PWM_OUT_3_BIT) ||
            (ulChannel == PWM_OUT_4_BIT) || (ulChannel == PWM_OUT_5_BIT) ||
            (ulChannel == PWM_OUT_6_BIT) || (ulChannel == PWM_OUT_7_BIT) );

    if(ulFrequency >= PwmClock)
    {
        return ERROR;
    }

    ulFrequency = PwmClock / ulFrequency;

    switch(ulChannel)
    {

        //
        // PWM Generator 0
        //
        case PWM_OUT_0_BIT:
        case PWM_OUT_1_BIT:
            {
                PwmGen = PWM_GEN_0;
                break;
            }
        //
        // PWM Generator 1
        //
        case PWM_OUT_2_BIT:
        case PWM_OUT_3_BIT:
            {
                PwmGen = PWM_GEN_1;
                break;
            }
        //
        // PWM Generator 2
        //
        case PWM_OUT_4_BIT:
        case PWM_OUT_5_BIT:
            {
                PwmGen = PWM_GEN_2;
                break;
            }
        //
        // PWM Generator 3
        //
        case PWM_OUT_6_BIT:
        case PWM_OUT_7_BIT:
            {
                PwmGen = PWM_GEN_3;
                break;
            }
        default:
            {
                return ERROR;
            }
    }

   PWMGenPeriodSet(PWM_BASE, PwmGen, ulFrequency);
   ActualFre = PWMGenPeriodGet(PWM_BASE, PwmGen);

   return PwmClock / ActualFre;
}

//*****************************************************************************
//
//! \brief get the PWM frequency of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to get the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~7
//! when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value 0~3.
//! when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value 4~7.
//!
//! \note None
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long xPWMFrequencyGet(unsigned long ulBase, unsigned long ulChannel)
{

    const unsigned long ERROR = 0;
    unsigned long PwmGen      = 0;
    unsigned long PwmClock    = 0;
    unsigned long ChannelFre  = 0;
    //
    // Check for valid parameters.
    //

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulChannel == PWM_OUT_0_BIT) || (ulChannel == PWM_OUT_1_BIT) ||
            (ulChannel == PWM_OUT_2_BIT) || (ulChannel == PWM_OUT_3_BIT) ||
            (ulChannel == PWM_OUT_4_BIT) || (ulChannel == PWM_OUT_5_BIT) ||
            (ulChannel == PWM_OUT_6_BIT) || (ulChannel == PWM_OUT_7_BIT) );

    switch(ulChannel)
    {
        //
        // PWM Generator 0
        //
        case PWM_OUT_0_BIT:
        case PWM_OUT_1_BIT:
            {
                PwmGen = PWM_GEN_0;
                break;
            }

        //
        // PWM Generator 1
        //
        case PWM_OUT_2_BIT:
        case PWM_OUT_3_BIT:
            {
                PwmGen = PWM_GEN_1;
                break;
            }

        //
        // PWM Generator 2
        //
        case PWM_OUT_4_BIT:
        case PWM_OUT_5_BIT:
            {
                PwmGen = PWM_GEN_2;
                break;
            }

        //
        // PWM Generator 3
        //
        case PWM_OUT_6_BIT:
        case PWM_OUT_7_BIT:
            {
                PwmGen = PWM_GEN_3;
                break;
            }
        default:
            {
                return ERROR;
            }

    }

    PwmClock   = PwmClockGet();
    ChannelFre = PWMGenPeriodGet(PWM_BASE, PwmGen);

    return (PwmClock/ChannelFre);
}

//*****************************************************************************
//
//! \brief Set the PWM duty of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulDuty is the duty of PWM channel.
//!
//! This function is to set the PWM duty of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~7
//! when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value 0~3.
//! when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value 4~7.
//!
//! The \e ulDuty parameter can be values:  duty > 0 && duty <= 100.
//!
//! \note Duty should not be 0.
//!
//! \return None.
//
//*****************************************************************************
void xPWMDutySet(unsigned long ulBase,
                 unsigned long ulChannel,
                 unsigned long ulDuty)
{
    unsigned long PwmPeriod = 0;
    unsigned long PwmGen    = 0;
    unsigned long PwmChl    = 0;

    //
    // check the arguments
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulChannel == PWM_OUT_0_BIT) || (ulChannel == PWM_OUT_1_BIT) ||
            (ulChannel == PWM_OUT_2_BIT) || (ulChannel == PWM_OUT_3_BIT) ||
            (ulChannel == PWM_OUT_4_BIT) || (ulChannel == PWM_OUT_5_BIT) ||
            (ulChannel == PWM_OUT_6_BIT) || (ulChannel == PWM_OUT_7_BIT) );
    xASSERT((ulDuty >= 0) && (ulDuty <= 100));

    switch(ulChannel)
    {
        //
        // PWM Generator 0
        //

        case PWM_OUT_0_BIT:
            {
                PwmChl = PWM_OUT_0;
                PwmGen = PWM_GEN_0;
                break;
            }
        case PWM_OUT_1_BIT:
            {
                PwmChl = PWM_OUT_1;
                PwmGen = PWM_GEN_0;
                break;
            }
        //
        // PWM Generator 1
        //
        case PWM_OUT_2_BIT:
            {
                PwmChl = PWM_OUT_2;
                PwmGen = PWM_GEN_1;
                break;
            }
        case PWM_OUT_3_BIT:
            {
                PwmChl = PWM_OUT_3;
                PwmGen = PWM_GEN_1;
                break;
            }
        //
        // PWM Generator 2
        //
        case PWM_OUT_4_BIT:
            {
                PwmChl = PWM_OUT_4;
                PwmGen = PWM_GEN_2;
                break;
            }
        case PWM_OUT_5_BIT:
            {
                PwmChl = PWM_OUT_5;
                PwmGen = PWM_GEN_2;
                break;
            }
        //
        // PWM Generator 3
        //
        case PWM_OUT_6_BIT:
             {
                PwmChl = PWM_OUT_6;
                PwmGen = PWM_GEN_3;
                break;
            }
        case PWM_OUT_7_BIT:
            {
                PwmChl = PWM_OUT_7;
                PwmGen = PWM_GEN_3;
                break;
            }
        default:
            {
                return ;
            }
    }

    PwmPeriod = PWMGenPeriodGet(ulBase, PwmGen);
    ulDuty = (ulDuty * PwmPeriod) / 100;
    PWMPulseWidthSet(ulBase, PwmChl, ulDuty);
}

//*****************************************************************************
//
//! \brief Get the PWM duty of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to get the PWM duty of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~7
//! when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value 0~3.
//! when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value 4~7.
//!
//! \note if input paramter is invaild, the function will return with ERROR(0)
//!
//! \return the Actual duty of PWM.
//
//*****************************************************************************

unsigned long xPWMDutyGet(unsigned long ulBase,
                          unsigned long ulChannel)
{
    const unsigned long ERROR = 0;

    unsigned long PwmPeriod = 0;
    unsigned long PwmWidth  = 0;
    unsigned long PwmGen    = 0;
    unsigned long PwmChl    = 0;

    //
    // check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulChannel == PWM_OUT_0_BIT) || (ulChannel == PWM_OUT_1_BIT) ||
            (ulChannel == PWM_OUT_2_BIT) || (ulChannel == PWM_OUT_3_BIT) ||
            (ulChannel == PWM_OUT_4_BIT) || (ulChannel == PWM_OUT_5_BIT) ||
            (ulChannel == PWM_OUT_6_BIT) || (ulChannel == PWM_OUT_7_BIT) );

    switch(ulChannel)
    {

        //
        // PWM Generator 0
        //

        case PWM_OUT_0_BIT:
            {
                PwmChl = PWM_OUT_0;
                PwmGen = PWM_GEN_0;
                break;
            }
        case PWM_OUT_1_BIT:
            {
                PwmChl = PWM_OUT_1;
                PwmGen = PWM_GEN_0;
                break;
            }
        //
        // PWM Generator 1
        //
        case PWM_OUT_2_BIT:
            {
                PwmChl = PWM_OUT_2;
                PwmGen = PWM_GEN_1;
                break;
            }
        case PWM_OUT_3_BIT:
            {
                PwmChl = PWM_OUT_3;
                PwmGen = PWM_GEN_1;
                break;
            }
        //
        // PWM Generator 2
        //
        case PWM_OUT_4_BIT:
            {
                PwmChl = PWM_OUT_4;
                PwmGen = PWM_GEN_2;
                break;
            }
        case PWM_OUT_5_BIT:
            {
                PwmChl = PWM_OUT_5;
                PwmGen = PWM_GEN_2;
                break;
            }
        //
        // PWM Generator 3
        //
        case PWM_OUT_6_BIT:
             {
                PwmChl = PWM_OUT_6;
                PwmGen = PWM_GEN_3;
                break;
            }
        case PWM_OUT_7_BIT:
            {
                PwmChl = PWM_OUT_7;
                PwmGen = PWM_GEN_3;
                break;
            }
        default:
            {
                return ERROR;
            }
    }

    PwmPeriod = PWMGenPeriodGet(ulBase, PwmGen);
    PwmWidth  = PWMPulseWidthGet(ulBase, PwmChl);

    return ((PwmWidth * 100) / PwmPeriod);
}

//*****************************************************************************
//
//! \brief Get the PWM interrupt flag of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulGen  is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//! Details please refer to \ref xPWM_Int_Type.
//!
//! This function is to get the PWM interrupt flag of the PWM module.
//!
//! The \e ulGen parameter can be values: 0~7
//! when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value 0~3
//! when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value 4~7
//!
//!
//! The \e ulIntType parameter can be values: \b xPWM_INT_PWM.
//! Details please refer to \ref xPWM_Int_Type_CoX
//!
//! \note None
//!
//! \return The checked flag status.
//
//*****************************************************************************

unsigned long xPWMIntFlagGet(unsigned long ulBase,
                             unsigned long ulGen,
                             unsigned long ulIntType)
{
    unsigned long PwmIntFlag = 0;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWM0_BASE) || (ulBase == PWM1_BASE));
    xASSERT( (ulGen == PWM_GEN_0) || (ulGen  == PWM_GEN_1) ||
            (ulGen == PWM_GEN_2) || (ulGen  == PWM_GEN_3) );

    //
    // Get the interrupt flag that sent to the interrupt controler
    //
    PwmIntFlag = xHWREG(ulBase + ulGen + PWM_O_X_ISC);

    //
    // return the user checked interrupt flag
    //
    return (PwmIntFlag & ulIntType);
}

