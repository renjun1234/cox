//*****************************************************************************
//
//! \file Blinky.c
//! \brief Blinky test.
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

static void _delay(unsigned long tick);

void Blinky(void)
{
    unsigned long TimeTick = 0xFFFFF;

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    while (1)
    {
        //
        // Turn On Led
        //
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 1<<3);
        _delay(TimeTick);

        //
        // Turn Off Led
        //
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0<<3);
        _delay(TimeTick);
    }
}

static void _delay(unsigned long tick)
{
    volatile unsigned long _tick = tick;
    while(_tick--);
}

