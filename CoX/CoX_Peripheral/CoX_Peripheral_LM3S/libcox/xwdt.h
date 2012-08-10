//*****************************************************************************
//
//! \file xwdt.h
//! \brief Prototypes for the watchdog timer Driver.
//! \version V2.1.1.1
//! \date 07/29/2012
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

#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup WDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Function_Type xWDT Function Type
//! \brief Values that show xWDT Function Type
//! \n
//! \section xWDT_Function_Type_Section 1. Where to use this group
//! Values that can be passed to xWDTFunctionEnable(),
//! xWDTFunctionDisable() as the ulFunction parameter.
//! \n
//! \section xWDT_Function_Type_CoX 2. CoX Port Details
//! \verbatim
//! +------------------------ +----------------+------------------------+
//! |xWDT Function Type       |       CoX      |        LM3Sxxxx        |
//! |------------------------ |----------------|------------------------|
//! |xWDT_INT_FUNCTION        |    Mandatory   |            Y           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_RESET_FUNCTION      |    Mandatory   |            Y           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_WAKEUP_FUNCTION     |  Non-Mandatory |            N           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_HOLD_IN_ICE         |  Non-Mandatory |            N           |
//! +------------------------ +----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Generate Interrupt when watch dog time out
//
#define xWDT_INT_FUNCTION       WDT_CTL_INTEN

//
//! Reset CPU when watch dog time out
//
#define xWDT_RESET_FUNCTION     WDT_CTL_RESEN


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Clock_Config xWDT Clock Configuration
//! \brief Values that show xWDT Clock Configuration
//! \n
//! \section xWDT_Clock_Config_Section 1. Where to use this group
//! Watch dog clock Configs. Such as clock source, Prescaler divider.
//! Values that can be passed to xWDTInit as the ulConfig parameter
//! \n
//! \section xWDT_Clock_Config_CoX 2.CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |Clock Configuration     |       CoX      |        LM3Sxxxx        |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_INTSL            |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_EXTSL            |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_HCLK_DIV         |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Time_Reload_Config xWDT Time Reload Configuration
//! \brief Values that show xWDT Time Reload Configuration
//! \n
//! \section xWDT_Time_Reload_Config_Section 1. Where to use this group
//! Values that can be passed to xWDTimerInit() as the ulConfig parameter
//! \n
//! \section xWDT_Time_Reload_Config_CoX 2.CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |Time Reload Config      |       CoX      |        LM3Sxxxx        |
//! |------------------------|----------------|------------------------|
//! |                        |                |                        |
//! |                        |                |                        |
//! |  unsigned long value   |  Non-Mandatory |   unsigned long value  |
//! |                        |                |                        |
//! |                        |                |                        |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Exported_APIs xWDT API
//! \brief xWDT API Reference.
//!
//! \section xWDT_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xWDT API                |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xWDTInit                |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTEnable              |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTIntCallbackInit     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTDisable             |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTRestart             |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTFunctionEnable      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTFunctionDisable     |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Configurate The WatchDog Timer(WDT)'s Timer.
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param ulConfig is the Timer's Prescaler divider and clock source
//! \param ulReload is the Timer's reload value.
//!
//! This function is to configureThe WatchDog Timer(WDT)'s Timer Interrupt Type
//! and Set Reload value.
//! There are three factors to determine the Timer Interval, they are:
//! - Interrupt mode   
//! - reload value
//!
//! The \e ulConfig parameter is used to Configure watchdog interrupt type.
//! When being used,this parameter can be OR of the following two values.
//! \b xWDT_INT_FUNCTION \b xWDT_RESET_FUNCTION
//!
//! The \e ulReload parameter is the value which will reload the counter when
//! feeding the watch dog.The value range depends on the number of bits of
//! corresponding counter.
//!
//! \return None.
//
//*****************************************************************************

extern void xWDTInit(unsigned long ulBase,
                     unsigned long ulConfig, 
                     unsigned long ulReload);

//*****************************************************************************
//
//! \brief Enable the Watchdog timer interrupt.
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//!
//! This function is to Enable the Watchdog timer interrupt.
//!
//! \note When use watch dog xWDTimerEnable() should be called after call
//! xWDTInit(ulBase, ulConfig, ulReload).
//!
//! \return None.
//
//*****************************************************************************
#define xWDTEnable(ulBase) WatchdogIntEnable(ulBase)


//*****************************************************************************
//
//! \brief Init interrupts callback for the Watchdog timer.
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param xtPortCallback is callback for the Watchdog timer.
//!
//! Init interrupts callback for the Watchdog timer.
//!
//! \return None.
//
//*****************************************************************************
extern void xWDTIntCallbackInit(unsigned long ulBase,
                                xtEventCallback xtWDTCallback);

//*****************************************************************************
//
//! \brief Disable the Watchdog timer interrupt.
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//!
//! This function is to disable the Watchdog timer interrupt.
//! \note for LM3Sxxxx MCU, once enable interrupt, user can't disable it unless
//! reset the mcu.
//!
//! \return None.
//
//*****************************************************************************
#define xWDTDisable(ulBase)

//*****************************************************************************
//
//! \brief Restart the Watchdog timer interrupt.
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//!
//! This function is to restart the Watchdog timer interrupt.
//!
//! \note this is use to feed the watch dog.
//!
//! \return None.
//
//*****************************************************************************
#define xWDTRestart(ulBase)

//*****************************************************************************
//
//! \brief Enable the watch dog timer's function.
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param ulFunction is the watch dog timer's function.
//! Details please refer to \ref xWDT_Function_Type.
//!
//! This function is to enable the watch dog timer's function such as Interrupt
//! reset\wake up \stop in ICE mode.
//!
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b xWDT_INT_FUNCTION,\b xWDT_RESET_FUNCTION,
//! \b xWDT_WAKEUP_FUNCTION,\b xWDT_HOLD_IN_ICE.
//! Details please refer to \ref xWDT_Function_Type_CoX.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
#define xWDTFunctionEnable(ulBase, ulFunction)

//*****************************************************************************
//
//! \brief Disable the watch dog timer's function.
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param ulFunction is the watch dog timer's function.
//! Details please refer to \ref xWDT_Function_Type.
//!
//! This function is to disable the watch dog timer's function such as Interrupt
//! reset\wake up \stop in ICE mode.
//!
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b xWDT_INT_FUNCTION,\b xWDT_RESET_FUNCTION,
//! \b xWDT_WAKEUP_FUNCTION,\b xWDT_HOLD_IN_ICE.
//! Details please refer to \ref xWDT_Function_Type_CoX.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
#define xWDTFunctionDisable(ulBase, ulFunction)


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup WDT_Interrupt_Type WDT Interrupt Type
//! \brief Values that show WDT Interrupt Type
//! Values that can be passed to WatchdogIntTypeSet().
//! @{
//
//*****************************************************************************

#define WATCHDOG_INT_TYPE_INT   0x00000000
#define WATCHDOG_INT_TYPE_NMI   0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LM3Sxxxx_WDT_Exported_APIs LM3Sxxxx WDT API
//! \brief LM3Sxxxx WDT API Reference.
//! @{
//
//*****************************************************************************

extern xtBoolean     WatchdogRunning      (unsigned long ulBase);

extern void          WatchdogEnable       (unsigned long ulBase);

extern void          WatchdogResetEnable  (unsigned long ulBase);

extern void          WatchdogResetDisable (unsigned long ulBase);

extern void          WatchdogLock         (unsigned long ulBase);

extern void          WatchdogUnlock       (unsigned long ulBase);

extern xtBoolean     WatchdogLockState    (unsigned long ulBase);

extern void          WatchdogReloadSet    (unsigned long ulBase,
                                           unsigned long ulLoadVal);

extern unsigned long WatchdogReloadGet    (unsigned long ulBase);

extern unsigned long WatchdogValueGet     (unsigned long ulBase);

extern void          WatchdogIntEnable    (unsigned long ulBase);

extern unsigned long WatchdogIntStatus    (unsigned long ulBase,
                                           xtBoolean     bMasked);

extern void          WatchdogIntClear     (unsigned long ulBase);

extern void          WatchdogIntTypeSet   (unsigned long ulBase,
                                           unsigned long ulType);

extern void          WatchdogStallEnable  (unsigned long ulBase);

extern void          WatchdogStallDisable (unsigned long ulBase);

extern void          Watchdog1WriteSync   (void);
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************




//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __WATCHDOG_H__
