//*****************************************************************************
//
//! @page xgpio_testcase xgpio register test
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
//! - \subpage test_xgpio_register
//! .
//! \file xgpiotest1.c
//! \brief xgpio test source file
//! \brief xgpio test header file <br>
//
//*****************************************************************************

#include "test.h"

//*****************************************************************************
//
//!\page test_xgpio_register test_xgpio_register
//!
//!<h2>Description</h2>
//!Test xgpio register. <br>
//!
//
//*****************************************************************************

#define SIZEOF(Tbl) (sizeof(Tbl)/sizeof(Tbl[0]))
#define PINNUM 8

#define GPIO_APB 0
#define GPIO_AHB 1
//
// GPIO configure function prototype
//
static unsigned long GetGpioBase(unsigned long ID);
static void          xtest_GPIODirModeSet_Get (unsigned long ulConfig);
static void          xtest_GPIOPadConfigSet_Get(void);

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

static const unsigned long Port_H_Tbl[] = 
{
  GPIO_PORTA_AHB_BASE,
  GPIO_PORTB_AHB_BASE,
  GPIO_PORTC_AHB_BASE,
  GPIO_PORTD_AHB_BASE,
  GPIO_PORTE_AHB_BASE,
  GPIO_PORTF_AHB_BASE,
  GPIO_PORTG_AHB_BASE,
  GPIO_PORTH_AHB_BASE,
  GPIO_PORTJ_AHB_BASE,
};

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

typedef struct
{
    unsigned long Port;
    unsigned long Pin;
    unsigned long Strength;
    unsigned long PinType;
}tPadConfigInput;

typedef struct
{
    unsigned long Base;
    unsigned long Mask;
    unsigned long Shift;
    unsigned long Expect;
}tPadConfigOutput;

typedef struct
{
    tPadConfigInput  *Input;
    tPadConfigOutput *Output;
}tPadConfig;


tPadConfigInput MyPadConfigInput_1 = 
{
    GPIO_PORTA_BASE,
    GPIO_PIN_0,
    GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD,
};



tPadConfigOutput MyPadConfigOutput_1[] =
{
    {
        GPIO_PORTA_BASE + GPIO_DR2R,
        GPIO_PIN_0,
        0,
        0x00000001,
    },
    {
        GPIO_PORTA_BASE + GPIO_DEN,
        GPIO_PIN_0,
        0,
        0x00000001,
    },
    
    //
    // End Flag
    //    
    {
        0,
    },
};

tPadConfigInput MyPadConfigInput_2 = 
{
    GPIO_PORTA_BASE,
    GPIO_PIN_5,
    GPIO_STRENGTH_8MA_SC,
    GPIO_PIN_TYPE_OD_WPU,
};

tPadConfigOutput MyPadConfigOutput_2[] =
{
    {
        GPIO_PORTA_BASE + GPIO_DEN,
        GPIO_PIN_5,
        5,
        0x00000001,
    },
    {
        GPIO_PORTA_BASE + GPIO_PUR,
        GPIO_PIN_5,
        5,
        0x00000001,
    },
    {
        GPIO_PORTA_BASE + GPIO_DR8R,
        GPIO_PIN_5,
        5,
        0x00000001,
    },
    {
        GPIO_PORTA_BASE + GPIO_SLR,
        GPIO_PIN_5,
        5,
        0x00000001,
    },
    //
    // End Flag
    //    
    {
        0,
    },
};

tPadConfig MyPadConfig[]=
{
    {
        &MyPadConfigInput_1,
        &MyPadConfigOutput_1[0],
    },
    {
        &MyPadConfigInput_2,
        &MyPadConfigOutput_2[0],
    },
    {
        0,
    },
};

tPadConfigInput MyPadConfigInput_1_AHB = 
{
    GPIO_PORTA_AHB_BASE,
    GPIO_PIN_0,
    GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD,
};

tPadConfigOutput MyPadConfigOutput_1_AHB[] =
{
    {
        GPIO_PORTA_AHB_BASE + GPIO_DR2R,
        GPIO_PIN_0,
        0,
        0x00000001,
    },
    {
        GPIO_PORTA_AHB_BASE + GPIO_DEN,
        GPIO_PIN_0,
        0,
        0x00000001,
    },
    
    //
    // End Flag
    //    
    {
        0,
    },
};

tPadConfigInput MyPadConfigInput_2_AHB = 
{
    GPIO_PORTA_AHB_BASE,
    GPIO_PIN_5,
    GPIO_STRENGTH_8MA_SC,
    GPIO_PIN_TYPE_OD_WPU,
};

tPadConfigOutput MyPadConfigOutput_2_AHB[] =
{
    {
        GPIO_PORTA_AHB_BASE + GPIO_DEN,
        GPIO_PIN_5,
        5,
        0x00000001,
    },
    {
        GPIO_PORTA_AHB_BASE + GPIO_PUR,
        GPIO_PIN_5,
        5,
        0x00000001,
    },
    {
        GPIO_PORTA_AHB_BASE + GPIO_DR8R,
        GPIO_PIN_5,
        5,
        0x00000001,
    },
    {
        GPIO_PORTA_AHB_BASE + GPIO_SLR,
        GPIO_PIN_5,
        5,
        0x00000001,
    },
    //
    // End Flag
    //    
    {
        0,
    },
};

tPadConfig MyPadConfig_AHB[]=
{
    {
        &MyPadConfigInput_1_AHB,
        &MyPadConfigOutput_1_AHB[0],
    },
    {
        &MyPadConfigInput_2_AHB,
        &MyPadConfigOutput_2_AHB[0],
    },
    {
        0,
    },
};



//*****************************************************************************
//
//! \brief Get the Test description of xgpio001 register test.
//!
//! \return the desccription of the xgpio001 test.
//
//*****************************************************************************

static char* xgpio001GetTest(void)
{
    return "xgpio, 001, xgpio configure test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xgpio001 test.
//!
//! \return None.
//
//*****************************************************************************

static void xgpio001Setup(void)
{
    unsigned long i       = 0;
    unsigned long TblSize = 0;

    TblSize = SIZEOF(SysPerGpioTbl);
    for(i = 0; i < TblSize; i++)
    {
        //
        // Enable GPIO Clock
        //
        SysCtlPeripheralEnable(SysPerGpioTbl[i]);

        //
        // Reset GPIO registers
        //
        SysCtlPeripheralReset(SysPerGpioTbl[i]);
    }
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xgpio001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio001TearDown(void)
{
    unsigned long i       = 0;
    unsigned long TblSize = 0;

    TblSize = SIZEOF(SysPerGpioTbl);
    for(i = 0; i < TblSize; i++)
    {
        //
        // Disable GPIO Clock
        //
        SysCtlPeripheralDisable(SysPerGpioTbl[i]);
        SysCtlGPIOAHBDisable(SysPerGpioTbl[i]);
    }
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOA);

    xSPinTypeUART(UART0RX, PA0);
    xSPinTypeUART(UART0TX, PA1);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);

    UARTConfigSetExpClk(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 |
                UART_CONFIG_STOP_1 | UART_CONFIG_PAR_NONE));
    UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
    
    SysCtlDelay(0xFFFFF);    
}


//*****************************************************************************
//
//! \brief xgpio001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio001Execute(void)
{
    
    //
    // GPIO Direct and Mode Set test
    //
    xtest_GPIODirModeSet_Get(GPIO_APB);
    //xtest_GPIODirModeSet_Get(GPIO_AHB);

    //
    //  GPIO pad set test
    //
    xtest_GPIOPadConfigSet_Get();

#if 0
    //
    // GPIO Pin Configure test
    //
    xtest_GPIOPinConfigure();

    //
    // GPIO Pin Read test
    //
    xtest_GPIOPinRead();

    //
    // GPIO Pin Write test
    //
    xtest_GPIOPinWrite();
#endif

}

//
// xgpio001 register test case struct.
//
const tTestCase sTestxGpio001Register = {
    xgpio001GetTest,
    xgpio001Setup,
    xgpio001TearDown,
    xgpio001Execute
};

//
// Xgpio test suits.
//
const tTestCase * const psPatternxgpio001[] =
{
    &sTestxGpio001Register,
    0
};

static unsigned long GetGpioBase(unsigned long ID)
{
    unsigned long Flag = 0;

    xASSERT((ID >= 0) && (ID < 8));
        
    Flag = xHWREG(SYSCTL_GPIOHBCTL) & (1<<ID);
    if(Flag != 0) //AHB
    {
        return Port_H_Tbl[ID];
    }
    else //APB
    {
        return Port_P_Tbl[ID];
    }
}

static void xtest_GPIODirModeSet_Get(unsigned long ulConfig)
{
    unsigned long i        = 0;
    unsigned long j        = 0;
    unsigned long TblSize  = 0;
    unsigned long GpioBase = 0;
    unsigned long tmp      = 0;

    TblSize = SIZEOF(SysPerGpioTbl);
    for(i = 0; i < TblSize; i++)
    {
        //
        // Set GPIO To APB/AHB Mode
        //
        if(GPIO_APB == ulConfig)
        {
            SysCtlGPIOAHBDisable(SysPerGpioTbl[i]);
        }
        else if(GPIO_AHB == ulConfig)
        {
            SysCtlGPIOAHBEnable(SysPerGpioTbl[i]);
        }



        GpioBase = GetGpioBase(i);
        for(j = 0; j < PINNUM; j++)
        {

            //
            // Set In Mode Test
            //
            SysCtlPeripheralReset(SysPerGpioTbl[i]);
            GPIODirModeSet(GpioBase, GpioPinTbl[j], GPIO_DIR_MODE_IN);
            tmp = xHWREG(GpioBase + GPIO_DIR) & GpioPinTbl[j];
            TestAssert((0 == tmp),
                    "Gpio Test 001: direct and mode set IN failed! ");

            //
            // Get In Mode Test
            //
            tmp = GPIODirModeGet(GpioBase, j);
            TestAssert((0 == tmp),
                    "Gpio Test 001: Mode Get failed! ");

            //
            // Set Out Mode Test
            //
            SysCtlPeripheralReset(SysPerGpioTbl[i]);
            GPIODirModeSet(GpioBase, GpioPinTbl[j], GPIO_DIR_MODE_OUT);
            tmp = xHWREG(GpioBase + GPIO_DIR) & GpioPinTbl[j];
            TestAssert((0 != tmp),
                    "Gpio Test 001: direct and mode set OUT failed! ");

            //
            // Get In Mode Test
            //
            tmp = GPIODirModeGet(GpioBase, j);
            TestAssert((1 == tmp),
                    "Gpio Test 001: Mode Get failed! ");

            //
            // Set Hardware Mode Test
            //
            SysCtlPeripheralReset(SysPerGpioTbl[i]);
            GPIODirModeSet(GpioBase, GpioPinTbl[j], GPIO_DIR_MODE_HW);
            tmp = xHWREG(GpioBase + GPIO_AFSEL) & GpioPinTbl[j];
            TestAssert((0 != tmp),
                    "Gpio Test 001: direct and mode set Hardware failed! ");

            //
            // Get Hardware Mode Test
            //
            tmp = GPIODirModeGet(GpioBase, j);
            TestAssert((2 == tmp),
                    "Gpio Test 001: Mode Get failed! ");
           
        }
    }
}

void xtest_GPIOPadConfigSet_Get(void)
{

    //
    // APB GPIO Test
    //

    tPadConfig       *Config = 0;
    tPadConfigInput  *Input  = 0;
    tPadConfigOutput *Output = 0;
    unsigned long tmp = 0;

    SysCtlGPIOAHBDisable(SYSCTL_PERIPH_GPIOA);
    //SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOA);

    Config = &MyPadConfig[0];
    while(0 != Config->Input)
    {
        Input = Config->Input;
        Output = Config->Output;

        GPIOPadConfigSet(Input->Port,
                Input->Pin,
                Input->Strength,
                Input->PinType);    

        while(0 != Output->Base)
        {
            tmp = ((xHWREG(Output->Base) & Output->Mask) >> Output->Shift);
            TestAssert((tmp == Output->Expect),
                    "PadConfig Failed\r\n");
            Output++;
        }    
        Config++;
    }

    //
    // AHB GPIO Test
    //

    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOA);
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOA);

    Config = &MyPadConfig_AHB[0];
    while(0 != Config->Input)
    {
        Input = Config->Input;
        Output = Config->Output;

        GPIOPadConfigSet(Input->Port,
                Input->Pin,
                Input->Strength,
                Input->PinType);    

        while(0 != Output->Base)
        {
            tmp = ((xHWREG(Output->Base) & Output->Mask) >> Output->Shift);
            TestAssert((tmp == Output->Expect),
                    "PadConfig Failed\r\n");
            Output++;
        }    
        Config++;
    }
    
}

void xtest_GPIOPinConfigure(void)
{

}

void xtest_GPIOPinWrite_Read(void)
{
    unsigned long tmp = 0;
    
    //
    // PD1 = 1
    //
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0xFF);
    tmp = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1);
    TestAssert((0 != (tmp & GPIO_PIN_1)),
            "GPIO Test 001 : write/read failed\r\n");

    //
    // PD1 = 0
    //
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x00);
    tmp = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1);
    TestAssert((0 == (tmp & GPIO_PIN_1)),
            "GPIO Test 001 : write/read failed\r\n");

    //
    // PF3 = 1
    //
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0xFF);
    tmp = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3);
    TestAssert((0 != (tmp & GPIO_PIN_3)),
            "GPIO Test 001 : write/read failed\r\n");

    //
    // PF3 = 0
    //
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
    tmp = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3);
    TestAssert((0 == (tmp & GPIO_PIN_3)),
            "GPIO Test 001 : write/read failed\r\n");


}

