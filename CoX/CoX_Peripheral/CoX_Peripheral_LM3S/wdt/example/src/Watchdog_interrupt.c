#include <stdint.h>
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xhw_wdt.h"
#include "xhw_nvic.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xwdt.h"

//
// Here is your interrupt Handler code for watchdog 0
//
static unsigned long WatchDog_0_Handler(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    // your code 
}

void Watchdog_Interrupt(void)
{
    unsigned long WdtBase = WATCHDOG0_BASE ; 
    unsigned long ReloadValue = 0xFFFF;

    //
    // Configure System Clock to 80MHz
    //
    SysCtlClockSet( SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | 
                    SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN );

    //
    // Enable watchdog clock
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);

    //
    // Ensure watchdog is unlocked.
    //
    if(WatchdogLockState(WdtBase))
    {
        WatchdogUnlock(WdtBase);
    }

    //
    // don't reset mcu, when watchdog count reach to zero once again.
    //
    WatchdogResetDisable(WdtBase);

    //
    // set reload value and stop watchdog when in debug mode.
    //
    WatchdogReloadSet(WdtBase, ReloadValue);
    WatchdogStallEnable(WdtBase);
    
    //
    // register the user's handler routine
    //
    xWDTIntCallbackInit(WdtBase, WatchDog_0_Handler);

    //
    // configure interrupt
    // 
    WatchdogIntEnable(WdtBase);
    WatchdogEnable(WdtBase);
    xIntEnable(INT_WATCHDOG);
    xIntMasterEnable();

    while(1);
}

