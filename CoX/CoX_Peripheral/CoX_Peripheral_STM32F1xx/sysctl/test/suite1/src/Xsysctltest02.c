//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: MCBSTM32 <br><br>
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
//! - \subpage test_xsysctl_register
//! .
//! \file xsysctltest.c
//! \brief xsysctl test source file
//! \brief xsysctl test header file <br>
//
//*****************************************************************************


#define  STM32F103VB  //select special mcu  for test
#include "test.h"
#include "STM32F1XX_TEST.h"
#include "xhw_memmap.h"

//*****************************************************************************
//
//!\page test_xsysctl_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xsysctl register. <br>
//!
//
//*****************************************************************************


//*****************************************************************************
//
//! \brief Get the Test description of xsysctl002 register test.
//!
//! \return the desccription of the xsysctl002 test.
//
//*****************************************************************************
static char* xSysctl002GetTest(void)
{
    return "xsysctl, 002, xsysctl register and api test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl002Setup(void)
{

}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl002TearDown(void)
{   
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_FLITF);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_SRAM);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    xSPinTypeUART(UART1RX,PA10);
    xSPinTypeUART(UART1TX,PA9);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    //SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    xUARTConfigSet(USART1_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                        UART_CONFIG_STOP_ONE | 
                                        UART_CONFIG_PAR_NONE));

    xUARTEnable(USART1_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
    TestIOPut('\r');
    TestIOPut('\n');
}

//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral Disable test .
//!
//! \return None.
//
//*****************************************************************************

static void xsysctl_SysCtlPeripheralDisable_test(void)
{
    unsigned long ulTemp,ulRegVal,i;
    unsigned long ulSize = 0;
    
    // test SysCtlPeripheralDisable function
    ulSize = sizeof(ulSYSCTL_AHB_Periph)/sizeof(ulSYSCTL_AHB_Periph[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_AHBENR);
        SysCtlPeripheralDisable(ulSYSCTL_AHB_Periph[i]);
        ulRegVal = xHWREG(RCC_AHBENR);
        TestAssert((0 == (ulRegVal & ulSYSCTL_AHB_EnableMask[i]) && 
                ((ulTemp & (~ulSYSCTL_AHB_EnableMask[i]))== ulRegVal)),
                 "xsysctl API error!");
        
    }


    ulSize = sizeof(ulSYSCTL_APB1_Periph)/sizeof(ulSYSCTL_APB1_Periph[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_APB1ENR);
        SysCtlPeripheralDisable(ulSYSCTL_APB1_Periph[i]);
        ulRegVal = xHWREG(RCC_APB1ENR);
        TestAssert((0 == (ulRegVal & ulSYSCTL_APB1_EnableMask[i]) && 
                ((ulTemp & (~ulSYSCTL_APB1_EnableMask[i]))== ulRegVal)),
                 "xsysctl API error!");
        
    }

    ulSize = sizeof(ulSYSCTL_APB2_Periph)/sizeof(ulSYSCTL_APB2_Periph[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_APB2ENR);
        SysCtlPeripheralDisable(ulSYSCTL_APB2_Periph[i]);
        ulRegVal = xHWREG(RCC_APB2ENR);
        TestAssert((0 == (ulRegVal & ulSYSCTL_APB2_EnableMask[i]) && 
                ((ulTemp & (~ulSYSCTL_APB2_EnableMask[i]))== ulRegVal)),
                 "xsysctl API error!");
        
    }



    // test xSysCtlPeripheralDisable2 function
    ulSize = sizeof(ulPERIPHER_AHB_Addr)/sizeof(ulPERIPHER_AHB_Addr[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_AHBENR);
        xSysCtlPeripheralDisable2(ulxPERIPHERE_AHB_EnableMask[i]);
        ulRegVal = xHWREG(RCC_AHBENR);
        TestAssert((0 == (ulRegVal & ulxPERIPHERE_AHB_EnableMask[i]) && 
            ((ulTemp & (~ulxPERIPHERE_AHB_EnableMask[i]))== ulRegVal)),
                                                    "xsysctl API error!"); 
    }

    ulSize = sizeof(ulPERIPHER_APB1_Addr)/sizeof(ulPERIPHER_APB1_Addr[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_APB1ENR);
        xSysCtlPeripheralDisable2(ulxPERIPHERE_APB1_EnableMask[i]);
        ulRegVal = xHWREG(RCC_APB1ENR);
        TestAssert((0 == (ulRegVal & ulxPERIPHERE_APB1_EnableMask[i]) && 
            ((ulTemp & (~ulxPERIPHERE_APB1_EnableMask[i]))== ulRegVal)),
                                                    "xsysctl API error!"); 
    }

    ulSize = sizeof(ulPERIPHER_APB2_Addr)/sizeof(ulPERIPHER_APB2_Addr[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_APB2ENR);
        xSysCtlPeripheralDisable2(ulxPERIPHERE_APB2_EnableMask[i]);
        ulRegVal = xHWREG(RCC_APB2ENR);
        TestAssert((0 == (ulRegVal & ulxPERIPHERE_APB2_EnableMask[i]) && 
            ((ulTemp & (~ulxPERIPHERE_APB2_EnableMask[i]))== ulRegVal)),
                                                    "xsysctl API error!"); 
    }

}





//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral reset test .
//!
//! \return None.
//
//*****************************************************************************


static void xsysctl_SysCtlPeripheralReset_test(void)
{
    unsigned long i = 0;
    unsigned long ulSize  = 0;

    ulSize = sizeof(ulSYSCTL_AHB_Periph)/sizeof(ulSYSCTL_AHB_Periph[0]);
    for(i = 0; i < ulSize; i++)
    {
        xSysCtlPeripheralReset(ulSYSCTL_AHB_Periph[i]);
        TestAssert(0 == xHWREG(RCC_AHBRSTR), "xsysctl API error!" );
    }
    
    ulSize = sizeof(ulSYSCTL_APB1_Periph)/sizeof(ulSYSCTL_APB1_Periph[0]);
    for(i = 0; i < ulSize; i++)
    {
        xSysCtlPeripheralReset(ulSYSCTL_APB1_Periph[i]);
        TestAssert(0 == xHWREG(RCC_APB1RSTR), "xsysctl API error!" );
    }
  
    ulSize = sizeof(ulSYSCTL_APB2_Periph)/sizeof(ulSYSCTL_APB2_Periph[0]);
    for(i = 0; i < ulSize; i++)
    {
        xSysCtlPeripheralReset(ulSYSCTL_APB2_Periph[i]);
        TestAssert(0 == xHWREG(RCC_APB2RSTR), "xsysctl API error!" );
    }


}

//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral Enable test .
//!
//! \return None.
//
//*****************************************************************************


static void xsysctl_SysCtlPeripheralEnable_test(void)
{
    unsigned long i = 0;
    unsigned long ulTemp = 0;
    unsigned long ulRegVal = 0;
    unsigned long ulSize = 0;

    // test the function SysCtlPeripheralEnable 
    ulSize = sizeof(ulSYSCTL_AHB_Periph)/sizeof(ulSYSCTL_AHB_Periph[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_AHBENR);
        SysCtlPeripheralEnable(ulSYSCTL_AHB_Periph[i]);
        ulRegVal = xHWREG(RCC_AHBENR);
        TestAssert((ulSYSCTL_AHB_EnableMask[i] == (ulRegVal & 
                           ulSYSCTL_AHB_EnableMask[i])),"xsysctl API error!"); 
    }

    ulSize = sizeof(ulSYSCTL_APB1_Periph)/sizeof(ulSYSCTL_APB1_Periph[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_APB1ENR);
        SysCtlPeripheralEnable(ulSYSCTL_APB1_Periph[i]);
        ulRegVal = xHWREG(RCC_APB1ENR);
        TestAssert((ulSYSCTL_APB1_EnableMask[i] == (ulRegVal & 
                           ulSYSCTL_APB1_EnableMask[i])),"xsysctl API error!"); 
    }

    ulSize = sizeof(ulSYSCTL_APB2_Periph)/sizeof(ulSYSCTL_APB2_Periph[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_APB2ENR);
        SysCtlPeripheralEnable(ulSYSCTL_APB2_Periph[i]);
        ulRegVal = xHWREG(RCC_APB2ENR);
        TestAssert((ulSYSCTL_APB2_EnableMask[i] == (ulRegVal & 
                           ulSYSCTL_APB2_EnableMask[i])),"xsysctl API error!"); 
    }  



    // test the function xSysCtlPeripheralEnable2

    ulSize = sizeof(ulPERIPHER_AHB_Addr)/sizeof(ulPERIPHER_AHB_Addr[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_AHBENR);
        xSysCtlPeripheralEnable2(ulPERIPHER_AHB_Addr[i]);
        ulRegVal = xHWREG(RCC_AHBENR);
        TestAssert((ulxPERIPHERE_AHB_EnableMask[i] == (ulRegVal & 
                        ulxPERIPHERE_AHB_EnableMask[i])), "xsysctl API error!"); 
    }

    ulSize = sizeof(ulPERIPHER_APB1_Addr)/sizeof(ulPERIPHER_APB1_Addr[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_APB1ENR);
        xSysCtlPeripheralEnable2(ulPERIPHER_APB1_Addr[i]);
        ulRegVal = xHWREG(RCC_APB1ENR);
        TestAssert((ulxPERIPHERE_APB1_EnableMask[i] == (ulRegVal & 
                        ulxPERIPHERE_APB1_EnableMask[i])), "xsysctl API error!"); 
    }

    ulSize = sizeof(ulPERIPHER_APB2_Addr)/sizeof(ulPERIPHER_APB2_Addr[0]);
    for(i = 0; i < ulSize; i++)
    {
        ulTemp = xHWREG(RCC_APB2ENR);
        xSysCtlPeripheralEnable2(ulPERIPHER_APB2_Addr[i]);
        ulRegVal = xHWREG(RCC_APB2ENR);
        TestAssert((ulxPERIPHERE_APB2_EnableMask[i] == (ulRegVal & 
                        ulxPERIPHERE_APB2_EnableMask[i])), "xsysctl API error!"); 
    }

}
//*****************************************************************************
//
//! \brief xsysctl 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl002Execute(void)
{
    SysCtlDelay(100000);
    xsysctl_SysCtlPeripheralEnable_test();
    xsysctl_SysCtlPeripheralDisable_test();
    xsysctl_SysCtlPeripheralReset_test();

}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl002Register = {
    xSysctl002GetTest,
    xSysctl002Setup,
    xSysctl002TearDown,
    xSysctl002Execute,
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl02[] =
{
    &sTestXSysctl002Register,
    0
};
