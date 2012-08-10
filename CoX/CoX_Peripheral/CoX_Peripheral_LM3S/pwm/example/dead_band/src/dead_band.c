//*****************************************************************************
//
//! \file deadband.c
//! \brief show how to use PWM module to output signal with deadband
//! \version V2.1.1.1
//! \date 7/29/2012
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

#include "hw_memmap.h"
#include "hw_types.h"
#include "pwm.h"
#include "gpio.h"
#include "sysctl.h"


//*****************************************************************************
//
// Configure the PWM0 block with dead-band generation.  The example configures
// the PWM0 block to generate a 25% duty cycle signal on PD0 with dead-band
// generation.  This will produce a complement of PD0 on PD1 (75% duty cycle).
// The dead-band generator is set to have a 10us or 160 cycle delay
// (160cycles / 16Mhz = 10us) on the rising and falling edges of the PD0 PWM
// signal.
//
//*****************************************************************************
void dead_band(void)
{
    //
    // Set the clocking to run directly from the external crystal/oscillator.
    // TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
    // crystal on your board.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

    //
    // Set the PWM clock to the system clock.
    //
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    //
    // The PWM peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);

    //
    // For this example PWM0 is used with PortD Pins 0 and 1.  The actual port
    // and pins used may be different on your part, consult the data sheet for
    // more information.  GPIO port D needs to be enabled so these pins can be
    // used.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    //
    // Configure the GPIO pin muxing to select PWM functions for these pins.
    // This step selects which alternate function is available for these pins.
    // This is necessary if your part supports GPIO pin function muxing.
    // Consult the data sheet to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PD0_PWM0);
    GPIOPinConfigure(GPIO_PD1_PWM1);

    //
    // Configure the GPIO pad for PWM function on pins PD0 and PD1.  Consult
    // the data sheet to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);

    //
    // Configure the PWM0 to count up/down without synchronization.
    // Note: Enabling the dead-band generator automatically couples the 2
    // outputs from the PWM block so we don't use the PWM synchronization.
    //
    PWMGenConfigure(PWM_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN |
                    PWM_GEN_MODE_NO_SYNC);

    //
    // Set the PWM period to 250Hz.  To calculate the appropriate parameter
    // use the following equation: N = (1 / f) * SysClk.  Where N is the
    // function parameter, f is the desired frequency, and SysClk is the
    // system clock frequency.
    // In this case you get: (1 / 250Hz) * 16MHz = 64000 cycles.  Note that
    // the maximum period you can set is 2^16 - 1.
    // TODO: modify this calculation to use the clock frequency that you are
    // using.
    //
    PWMGenPeriodSet(PWM_BASE, PWM_GEN_0, 64000);

    //
    // Set PWM0 PD0 to a duty cycle of 25%.  You set the duty cycle as a
    // function of the period.  Since the period was set above, you can use the
    // PWMGenPeriodGet() function.  For this example the PWM will be high for
    // 25% of the time or 16000 clock cycles (64000 / 4).
    //
    PWMPulseWidthSet(PWM_BASE, PWM_OUT_0,
                     PWMGenPeriodGet(PWM_BASE, PWM_OUT_0) / 4);

    //
    // Enable the dead-band generation on the PWM0 output signal.  PWM bit 0
    // (PD0), will have a duty cycle of 25% (set above) and PWM bit 1 will have
    // a duty cycle of 75%.  These signals will have a 10us gap between the
    // rising and falling edges.  This means that before PWM bit 1 goes high,
    // PWM bit 0 has been low for at LEAST 160 cycles (or 10us) and the same
    // before PWM bit 0 goes high.  The dead-band generator lets you specify
    // the width of the "dead-band" delay, in PWM clock cycles, before the PWM
    // signal goes high and after the PWM signal falls.  For this example we
    // will use 160 cycles (or 10us) on both the rising and falling edges of
    // PD0.  Reference the datasheet for more information on dead-band
    // generation.
    //
    PWMDeadBandEnable(PWM_BASE, PWM_GEN_0, 160, 160);

    //
    // Enable the PWM0 Bit 0 (PD0) and Bit 1 (PD1) output signals.
    //
    PWMOutputState(PWM_BASE, PWM_OUT_1_BIT | PWM_OUT_0_BIT, true);

    //
    // Enables the counter for a PWM generator block.
    //
    PWMGenEnable(PWM_BASE, PWM_GEN_0);

    //
    // Loop forever while the PWM signals are generated.
    //
    while(1)
    {
    }
}

