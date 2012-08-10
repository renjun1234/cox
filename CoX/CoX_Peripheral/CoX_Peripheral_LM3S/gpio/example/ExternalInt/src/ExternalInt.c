//*****************************************************************************
//
//! \file  ExternalInt.c
//! \brief ExternalInt test.
//! \version 1.0
//! \date 08/07/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2012 CooCox.  All rights reserved.
//
//*****************************************************************************

#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xsysctl.h"
#include "xgpio.h"


//
// User's interrupt handler
//
unsigned long UserGpioHandler(void          *pvCBData, 
                               unsigned long ulEvent,
                               unsigned long ulMsgParam,
                               void          *pvMsgData)
{
    static unsigned long Count = 0;

    //
    // Clear GPIO Pending bit
    //
    GPIOPinIntClear(GPIO_PORTJ_BASE, GPIO_PIN_7);
    
    //
    // Here is your code.
    //

    return 0;
}

void ExternalInt(void)
{
    //
    // Use PJ7 as a test for interrupt function
    //

    //
    // Enable GPIO J Module Clock
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    //
    // Reset GPIO J Module
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOJ);

    //
    // Register ISR Function
    //
    GPIOPinIntCallbackInit(GPIO_PORTJ_BASE, GPIO_PIN_7, UserGpioHandler);

    //
    // Configure PJ7 Mode : digital input
    //
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_7);

    //
    // Configure PJ7 Int type: Rising Edge
    //
    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_7, GPIO_RISING_EDGE);

    //
    // Enable PJ7 interrupt
    //
    GPIOPinIntEnable(GPIO_PORTJ_BASE, GPIO_PIN_7);

    //
    // Enable GPIO J Channel Interrupt and Master Interrupt
    //
    xIntEnable(INT_GPIOJ);
    xIntMasterEnable();

    while(1)
    {
        ; //do nothing, wait for interrupt
    }

}

