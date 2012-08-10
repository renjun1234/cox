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


//
// Used in the SysCtl Function
//
static const unsigned long SysPerGpioTbl[] = 
{
    SYSCTL_PERIPH_GPIOA,
    SYSCTL_PERIPH_GPIOB,
    SYSCTL_PERIPH_GPIOC,
    SYSCTL_PERIPH_GPIOD,
    SYSCTL_PERIPH_GPIOE,
    SYSCTL_PERIPH_GPIOF,
    SYSCTL_PERIPH_GPIOG,
    SYSCTL_PERIPH_GPIOH,
    SYSCTL_PERIPH_GPIOJ,
};

//
// GPIO APB Register Base
//
static const unsigned long Port_P_Tbl[] = 
{
  GPIO_PORTA_BASE,
  GPIO_PORTB_BASE,
  GPIO_PORTC_BASE,
  GPIO_PORTD_BASE,
  GPIO_PORTE_BASE,
  GPIO_PORTF_BASE,
  GPIO_PORTG_BASE,
  GPIO_PORTH_BASE,
  GPIO_PORTJ_BASE,
};

//
// GPIO Pin Num
// Used in the function whick has a input paramter "unsigned char ucPins"
//
static const unsigned long GpioPinTbl[]=
{
    GPIO_PIN_0, 
    GPIO_PIN_1, 
    GPIO_PIN_2, 
    GPIO_PIN_3, 
    GPIO_PIN_4, 
    GPIO_PIN_5, 
    GPIO_PIN_6, 
    GPIO_PIN_7, 
};

//
// GPIO Pin ID
// Used in the function whick has a input paramter "unsigned char ucPin"
// Most likely , it a xxxGet function, ie: GPIOIntTypeGet
static const unsigned long GpioPinIDTbl[]=
{
    0x00000000, 
    0x00000001, 
    0x00000002, 
    0x00000003, 
    0x00000004, 
    0x00000005, 
    0x00000006, 
    0x00000007, 
};


//*****************************************************************************
//
//!\page test_xgpio_interrupt test_xgpio_interrupt
//!
//!<h2>Description</h2>
//!Test xgpio interrupt. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Emit Token '0'~'7' to TestTokenBuffer
//!
//! \return 0, this value has no effect but to avoid warnning producted by
//   compiler.
//
//*****************************************************************************
unsigned long Test_GpioHandler(void *pvCBData, 
                               unsigned long ulEvent,
                               unsigned long ulMsgParam,
                               void *pvMsgData)
{
    static unsigned long Count = 0;
    GPIOPinIntClear(GPIO_PORTJ_BASE, GPIO_PIN_7);
    if(Count <= 7) 
    {
        TestEmitToken(Count + '0');
        Count++;
    }
    
    return 0;
}


//*****************************************************************************
//
//! \brief Get the Test description of xgpio0021 interrupt test.
//!
//! \return the desccription of the xgpio0021 test.
//
//*****************************************************************************
static char* xgpio0021GetTest(void)
{
    return "gpio, 0021, gpio int enable/disable test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xgpio0021 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio0021Setup(void)
{   
    unsigned long i                 = 0;
    unsigned long SysPerGpioTblSize = 0;

    //
    // Enable GPIO Port and Disable master interrupt
    //
    SysPerGpioTblSize = sizeof(SysPerGpioTbl) / sizeof(SysPerGpioTbl[0]);
    for(i = 0; i < SysPerGpioTblSize; i++)
    {
        SysCtlPeripheralEnable(SysPerGpioTbl[i]);
    }
    
    xIntMasterDisable();
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xgpio0021 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio0021TearDown(void)
{
    unsigned long i                 = 0;
    unsigned long SysPerGpioTblSize = 0;

    //
    // Enable GPIO Port and Disable master interrupt
    //
    SysPerGpioTblSize = sizeof(SysPerGpioTbl) / sizeof(SysPerGpioTbl[0]);
    for(i = 0; i < SysPerGpioTblSize; i++)
    {
        SysCtlPeripheralDisable(SysPerGpioTbl[i]);
    }
    
    xIntMasterEnable();
}

//*****************************************************************************
//
//! \brief xgpio0021 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio0021Execute(void)
{
    unsigned long i               = 0;
    unsigned long j               = 0;
    unsigned long tmp             = 0;
    unsigned long GpioPortTblSize = sizeof(Port_P_Tbl)/sizeof(Port_P_Tbl[0]);
    unsigned long GpioPinTblSize  = sizeof(GpioPinTbl)/sizeof(GpioPinTbl[0]);

    for(i = 0; i < GpioPortTblSize; i++)
    {
        for(j = 0; j < GpioPinTblSize; j++)
        {
            //
            // Interrupt Enable Test
            //
            GPIOPinIntEnable(Port_P_Tbl[i], GpioPinTbl[j]);
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IM) & GpioPinTbl[j];
            TestAssert((0 != tmp),
                    "Test 00211: Gpio Int Enable Failed\r\n");

            //
            // Interrupt Disable Test
            //
            GPIOPinIntDisable(Port_P_Tbl[i], GpioPinTbl[j]);
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IM) & GpioPinTbl[j];
            TestAssert((0 == tmp),
                    "Test 0021: Gpio Int Disable Failed\r\n");
        }
    }
}


//*****************************************************************************
//
//! \brief Get the Test description of xgpio0022 interrupt test.
//!
//! \return the desccription of the xgpio0022 test.
//
//*****************************************************************************
static char* xgpio0022GetTest(void)
{
    return "gpio, 0022, gpio int type set/get test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xgpio0022 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio0022Setup(void)
{   
    unsigned long i                 = 0;
    unsigned long SysPerGpioTblSize = 0;

    //
    // Enable GPIO Port and Disable master interrupt
    //
    SysPerGpioTblSize = sizeof(SysPerGpioTbl) / sizeof(SysPerGpioTbl[0]);
    for(i = 0; i < SysPerGpioTblSize; i++)
    {
        SysCtlPeripheralEnable(SysPerGpioTbl[i]);
    }
    
    xIntMasterDisable();
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xgpio0022 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio0022TearDown(void)
{
    unsigned long i                 = 0;
    unsigned long SysPerGpioTblSize = 0;

    //
    // Enable GPIO Port and Disable master interrupt
    //
    SysPerGpioTblSize = sizeof(SysPerGpioTbl) / sizeof(SysPerGpioTbl[0]);
    for(i = 0; i < SysPerGpioTblSize; i++)
    {
        SysCtlPeripheralDisable(SysPerGpioTbl[i]);
    }
    
    xIntMasterEnable();
}

//*****************************************************************************
//
//! \brief xgpio0022 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio0022Execute(void)
{
    unsigned long i                   = 0;
    unsigned long j                   = 0;
    unsigned long tmp                 = 0;
    unsigned long GpioPortTblSize     = 0;
    unsigned long GpioPinTblSize      = 0;

    GpioPortTblSize     = sizeof(Port_P_Tbl)/sizeof(Port_P_Tbl[0]);
    GpioPinTblSize      = sizeof(GpioPinTbl)/sizeof(GpioPinTbl[0]);

    for(i = 0; i < GpioPortTblSize; i++)
    {
        for(j = 0; j < GpioPinTblSize; j++)
        {

            //
            // 1: Falling Edge Set
            //
            GPIOIntTypeSet(Port_P_Tbl[i], GpioPinTbl[j], GPIO_FALLING_EDGE);

            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IBE) & GpioPinTbl[j];
            TestAssert((0 == tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IS) & GpioPinTbl[j];
            TestAssert((0 == tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IEV) & GpioPinTbl[j];
            TestAssert((0 == tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            // Falling Edge Get
            tmp = GPIOIntTypeGet(Port_P_Tbl[i], GpioPinIDTbl[j]);
            TestAssert((GPIO_FALLING_EDGE == tmp),
                    "Test 00221: Gpio Int type get Failed\r\n");


            //
            // 2: Rasing Edge Set
            //
            GPIOIntTypeSet(Port_P_Tbl[i], GpioPinTbl[j], GPIO_RISING_EDGE);

            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IBE) & GpioPinTbl[j];
            TestAssert((0 == tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IS) & GpioPinTbl[j];
            TestAssert((0 == tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IEV) & GpioPinTbl[j];
            TestAssert((0 != tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            // Rasing Edge Get
            tmp = GPIOIntTypeGet(Port_P_Tbl[i], GpioPinIDTbl[j]);
            TestAssert((GPIO_RISING_EDGE == tmp),
                    "Test 00221: Gpio Int type get Failed\r\n");


            //
            //3: Falling and rising edge Set
            //
            GPIOIntTypeSet(Port_P_Tbl[i], GpioPinTbl[j], GPIO_BOTH_EDGES);

            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IBE) & GpioPinTbl[j];
            TestAssert((0 != tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IS) & GpioPinTbl[j];
            TestAssert((0 == tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IEV) & GpioPinTbl[j];
            TestAssert((0 == tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            // Falling and Rising Edge Get
            tmp = GPIOIntTypeGet(Port_P_Tbl[i], GpioPinIDTbl[j]);
            TestAssert((GPIO_BOTH_EDGES == tmp),
                    "Test 00221: Gpio Int type get Failed\r\n");

            //
            //4: Low level Set
            //
            GPIOIntTypeSet(Port_P_Tbl[i], GpioPinTbl[j], GPIO_LOW_LEVEL);

            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IBE) & GpioPinTbl[j];
            TestAssert((0 == tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IS) & GpioPinTbl[j];
            TestAssert((0 != tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IEV) & GpioPinTbl[j];
            TestAssert((0 == tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            // Low level Get
            tmp = GPIOIntTypeGet(Port_P_Tbl[i], GpioPinIDTbl[j]);
            TestAssert((GPIO_LOW_LEVEL == tmp),
                    "Test 00221: Gpio Int type get Failed\r\n");

            //
            //5: High level Set
            //
            GPIOIntTypeSet(Port_P_Tbl[i], GpioPinTbl[j], GPIO_HIGH_LEVEL);

            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IBE) & GpioPinTbl[j];
            TestAssert((0 != tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IS) & GpioPinTbl[j];
            TestAssert((0 != tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            tmp = xHWREG(Port_P_Tbl[i] + GPIO_IEV) & GpioPinTbl[j];
            TestAssert((0 != tmp),
                    "Test 00221: Gpio Int type set Failed\r\n");
            // High level Get
            tmp = GPIOIntTypeGet(Port_P_Tbl[i], GpioPinIDTbl[j]);
            TestAssert((GPIO_HIGH_LEVEL == tmp),
                    "Test 00221: Gpio Int type get Failed\r\n");

        }
    }
}


//*****************************************************************************
//
//! \brief Get the Test description of xgpio0023 interrupt test.
//!
//! \return the desccription of the xgpio0023 test.
//
//*****************************************************************************
static char* xgpio0023GetTest(void)
{
    return "gpio, 0023, gpio interrupt register function test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xgpio0023 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio0023Setup(void)
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
    GPIOPinIntCallbackInit(GPIO_PORTJ_BASE, GPIO_PIN_7, Test_GpioHandler);

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
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xgpio0023 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio0023TearDown(void)
{
    //
    // Disable Master Interrupt and GPIO J Channel Interrupt
    //
    xIntDisable(INT_GPIOJ);
    xIntMasterDisable();

    //
    // Reset GPIO J
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOJ);

    //
    // Disable GPIO J Clock
    //
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOJ);
}

//*****************************************************************************
//
//! \brief xgpio0023 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio0023Execute(void)
{
    char *ExpectToken = "01234567";
    TestAssertQBreak(ExpectToken, "Interrupt Hander Failed\r\n", -1);
}

//
// xgpio0021 test case struct.
//
const tTestCase sTestxGpio0021 = {
    xgpio0021GetTest,
    xgpio0021Setup,
    xgpio0021TearDown,
    xgpio0021Execute
};

//
// xgpio0022 test case struct.
//
const tTestCase sTestxGpio0022 = {
    xgpio0022GetTest,
    xgpio0022Setup,
    xgpio0022TearDown,
    xgpio0022Execute
};

//
// xgpio0023 test case struct.
//
const tTestCase sTestxGpio0023 = {
    xgpio0023GetTest,
    xgpio0023Setup,
    xgpio0023TearDown,
    xgpio0023Execute
};

//
// Xgpio test suits.
//
const tTestCase * const psPatternxgpio002[] =
{
    &sTestxGpio0021,
    &sTestxGpio0022,
    &sTestxGpio0023,
    0
};

