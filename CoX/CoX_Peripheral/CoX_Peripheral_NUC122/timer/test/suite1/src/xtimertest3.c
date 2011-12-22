//*****************************************************************************
//
//! @page xtimer_testcase xtimer event counting and input capture function test
//!
//! File: @ref xtimertest3.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xtimer sub component.<br><br>
//! - \p Board: NUC140VE3CN board <br><br>
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
//! - \subpage test_xtimer_EventCount_InputCapture_test
//! .
//! \file xtimertest3.c
//! \brief xtimer test source file
//! \brief xtimer test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_timer.h"
#include "xtimer.h"

//*****************************************************************************
//
//!\page test_xtimer_EventCount_InputCapture_test test_xtimer_EventCount_InputCapture_test
//!
//!<h2>Description</h2>
//!Test xtimer event counting and input capture test. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Define The 4 timer base address array, and Peripheral ID array.
//
//*****************************************************************************

//
// Timer base array
//
static unsigned long ulTimerBase[4] = {TIMER0_BASE, TIMER1_BASE,
                                       TIMER2_BASE, TIMER3_BASE};

//
// Timer ID array
//
static unsigned long ulTimerID[4] = {xSYSCTL_PERIPH_TIMER0,
                                     xSYSCTL_PERIPH_TIMER1,
                                     xSYSCTL_PERIPH_TIMER2,
                                     xSYSCTL_PERIPH_TIMER3};

//
// Timer interrupt ID
//
static unsigned long ulTimerIntID[4] = {xINT_TIMER0, xINT_TIMER1,
                                        xINT_TIMER2, xINT_TIMER3};

//
// Install callback function
//
static unsigned long Timer0Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('b'); 
     return 0;
}
static unsigned long Timer1Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('b'); 
     return 0;
}
static unsigned long Timer2Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('b');
     return 0;
}
static unsigned long Timer3Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('b'); 
     return 0;
}

//
// Callback function
//
static xtEventCallback TimerCallbackFunc[4] = {Timer0Callback,
                                               Timer1Callback,
                                               Timer2Callback,
                                               Timer3Callback};


//*****************************************************************************
//
//! \breif This function is used to generate a falling edge, as the of
//! Timer counting source.
//!
//! \return
//
//*****************************************************************************
void EdgeGenerate(void)                                       
{
    int i;
    //
    // Set the  pin to high
    //
    xGPIOSPinWrite(PC12, 0);
    
    //
    // Add a small delay
    //
    for(i = 0; i < 5; i++);
    
    //
    // Set the  pin to low
    //
    xGPIOSPinWrite(PC12, 1);
    
    for(i = 0; i < 5; i++);
    
}

//*****************************************************************************
//
//! \brief gpio init ,Set the GPC12 as gpio output. 
//!
//! \return none
//!
//
//*****************************************************************************
void GPIOInit()
{
    //
    // PC12 used to output falling edge as the timer count source.
    //
    xGPIODirModeSet(GPIO_PORTC_BASE, GPIO_BIT_12, GPIO_DIR_MODE_OUT);
    xGPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_12, 1);
    
}

//*****************************************************************************
//
//! \brief Get the Test description of xtimer001 event counting and input capture test.
//!
//! \return the desccription of the xtimer001 test.
//
//*****************************************************************************
static char* xTimer001GetTest(void)
{
    return "xTimer [001]: xtimer count and capture mode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001Setup(void)
{
    int i;
    //
    //Set the external 12MHZ clock as system clock 
    //
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_6MHZ | xSYSCTL_OSC_MAIN);
    
    //
    // Set the timer clock, in event counting mode, the timer source clock should
    // be HCLK.
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR0_S_HCLK);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR1_S_HCLK);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR2_S_HCLK);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR3_S_HCLK);
    
    //
    // Turn a pin to an GPIO Timer input or output pin.
    //
    xSPinTypeTimer(TIMCCP0, PB8);
    xSPinTypeTimer(TIMCCP1, PB9);
    xSPinTypeTimer(TIMCCP2, PB10);
    
    GPIOInit();
    
    //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 4; i++)
    {   
        
        xSysCtlPeripheralEnable(ulTimerID[i]);  
       
    }
    
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001TearDown(void)
{
    int i;
    //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 4; i++)
    {
        xSysCtlPeripheralDisable(ulTimerID[i]);  
    }
}

//*****************************************************************************
//
//! \brief xtimer 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001Execute(void)
{
    unsigned long ulBase;
    int i;
    
    //
    // Test the event count function test. You should connect the pc12 to the
    // corresponding TM pin as the count source.
    //   
    for(i = 0; i < 3; i++)
    {
        ulBase = ulTimerBase[i];
        
        TimerIntClear(ulBase, TIMER_INT_MATCH);
        TimerCounterEnable(ulBase);
        // 
        // Mode set test
        //
        TimerCounterInitConfig(ulBase, TIMER_MODE_CONTINUOUS, 10000);
        
        TimerMatchSet(ulBase, 5);
        
        //
        // Set prescale value 0
        //
        TimerPrescaleSet(ulBase, 0);
        
        TimerIntEnable(ulBase, TIMER_INT_MATCH);
        
        //
        // Enable event count mode
        //
        TimerStart(ulBase);
        
        while(!TimerIntStatus(ulBase, TIMER_INT_MATCH))
        {
            EdgeGenerate();
        }
        TimerIntClear(ulBase, TIMER_INT_MATCH);
        
        TimerCounterDisable(ulBase);
    }   
    
}

//
// xtimer register test case struct.
//
const tTestCase sTestxTimer001Function = {
		xTimer001GetTest,
		xTimer001Setup,
		xTimer001TearDown,
		xTimer001Execute
};

//
// xtimer test suits.
//
const tTestCase * const psPatternXtimer003[] =
{
    &sTestxTimer001Function,
    0
};

