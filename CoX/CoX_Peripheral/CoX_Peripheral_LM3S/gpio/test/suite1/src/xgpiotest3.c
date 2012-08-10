//*****************************************************************************
//
//! @page xgpio_testcase xgpio interrupt test
//!
//! File: @ref xgpiotest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xgpio sub component.<br><br>
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
//! - \subpage test_xgpio_interrupt
//! .
//! \file xgpiotest2.c
//! \brief xgpio test source file
//! \brief xgpio test header file <br>
//
//*****************************************************************************

#include "test.h"

//*****************************************************************************
//
//!\page test_xgpio_interrupt test_xgpio_interrupt
//!
//!<h2>Description</h2>
//!Test xgpio interrupt. <br>
//!
//
//*****************************************************************************

//
//  PinType function prototype
//

//
// Following function is tested in this file
// However it's checked manually
//

// static void          xtest_GPIOPinTypeADC           (void);
// static void          xtest_GPIOPinTypeCAN           (void);
// static void          xtest_GPIOPinTypeACMPAnalog    (void);
// static void          xtest_GPIOPinTypeACMPDigital   (void);
// static void          xtest_GPIOPinTypeEPI           (void);
// static void          xtest_GPIOPinTypeEthernetLED   (void);
// static void          xtest_GPIOPinTypeGPIOInput     (void);
// static void          xtest_GPIOPinTypeGPIOOutput    (void);
// static void          xtest_GPIOPinTypeGPIOOutputOD  (void);
// static void          xtest_GPIOPinTypeI2C           (void);
// static void          xtest_GPIOPinTypeI2S           (void);
// static void          xtest_GPIOPinTypePWM           (void);
// static void          xtest_GPIOPinTypeQEI           (void);
// static void          xtest_GPIOPinTypeSPI           (void);
// static void          xtest_GPIOPinTypeTimer         (void);
// static void          xtest_GPIOPinTypeUART          (void);
// static void          xtest_GPIOPinTypeUSBAnalog     (void);
// static void          xtest_GPIOPinTypeUSBDigital    (void);

//*****************************************************************************
//
//! \brief Get the Test description of xgpio003 interrupt test.
//!
//! \return the desccription of the xgpio003 test.
//
//*****************************************************************************
static char* xgpio003GetTest(void)
{
    return "xgpio, 003, xgpio interrupt test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xgpio003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio003Setup(void)
{
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xgpio003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio003TearDown(void)
{

}

//*****************************************************************************
//
//! \brief xgpio003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio003Execute(void)
{
}

//
// xgpio003 interrupt test case struct.
//
const tTestCase sTestxGpio003Interrupt = {
    xgpio003GetTest,
    xgpio003Setup,
    xgpio003TearDown,
    xgpio003Execute
};

//
// Xgpio test suits.
//
const tTestCase * const psPatternxgpio2[] =
{
    &sTestxGpio003Interrupt,
    0
};

