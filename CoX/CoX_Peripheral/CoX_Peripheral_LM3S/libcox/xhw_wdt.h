//*****************************************************************************
//
// hw_watchdog.h - Macros used when accessing the Watchdog Timer hardware.
//
// Copyright (c) 2005-2012 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 8555 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#ifndef __HW_WATCHDOG_H__
#define __HW_WATCHDOG_H__

//*****************************************************************************
//
// The following are defines for the Watchdog Timer register offsets.
//
//*****************************************************************************

//
// Watchdog Load
//
#define WDT_O_LOAD              0x00000000  

//
// Watchdog Value
//
#define WDT_O_VALUE             0x00000004  

//
// Watchdog Control
//
#define WDT_O_CTL               0x00000008  

//
// Watchdog Interrupt Clear
//
#define WDT_O_ICR               0x0000000C  

//
// Watchdog Raw Interrupt Status
//
#define WDT_O_RIS               0x00000010  

//
// Watchdog Masked Interrupt Status
//
#define WDT_O_MIS               0x00000014  

//
// Watchdog Test
//
#define WDT_O_TEST              0x00000418  

//
// Watchdog Lock
//
#define WDT_O_LOCK              0x00000C00  


//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_LOAD register.
//
//*****************************************************************************

//
// Watchdog Load Value Mask
//
#define WDT_LOAD_M              0xFFFFFFFF  

//
// Watchdog Load Value Shift
//
#define WDT_LOAD_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_VALUE register.
//
//*****************************************************************************

//
// Watchdog Value Mask
//
#define WDT_VALUE_M             0xFFFFFFFF  

//
// Watchdog Value Shift
//
#define WDT_VALUE_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_CTL register.
//
//*****************************************************************************

//
// Write Complete
//
#define WDT_CTL_WRC             0x80000000  

//
// Watchdog Interrupt Type
//
#define WDT_CTL_INTTYPE         0x00000004  

//
// Watchdog Reset Enable
//
#define WDT_CTL_RESEN           0x00000002  

//
// Watchdog Interrupt Enable
//
#define WDT_CTL_INTEN           0x00000001  


//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_ICR register.
//
//*****************************************************************************

//
// Watchdog Interrupt Clear Mask
//
#define WDT_ICR_M               0xFFFFFFFF  

//
// Watchdog Interrupt Clear Shift
//
#define WDT_ICR_S               0

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_RIS register.
//
//*****************************************************************************

//
// Watchdog Raw Interrupt Status
//
#define WDT_RIS_WDTRIS          0x00000001  


//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_MIS register.
//
//*****************************************************************************

//
// Watchdog Masked Interrupt Status
//
#define WDT_MIS_WDTMIS          0x00000001  


//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_TEST register.
//
//*****************************************************************************

//
// Watchdog Stall Enable
//
#define WDT_TEST_STALL          0x00000100  


//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_LOCK register.
//
//*****************************************************************************

//
// Watchdog Lock
//
#define WDT_LOCK_M              0xFFFFFFFF  

//
// Unlocked
//
#define WDT_LOCK_UNLOCKED       0x00000000  

//
// Locked
//
#define WDT_LOCK_LOCKED         0x00000001  

//
// Unlocks the watchdog timer
//
#define WDT_LOCK_UNLOCK         0x1ACCE551  


//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_ISR, WDT_RIS, and
// WDT_MIS registers.
//
//*****************************************************************************

//
// Watchdog timer expired
//
#define WDT_INT_TIMEOUT         0x00000001  

#endif // __HW_WATCHDOG_H__
