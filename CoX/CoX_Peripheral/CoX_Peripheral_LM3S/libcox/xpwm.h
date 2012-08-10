//*****************************************************************************
//
//! \file xpwm.h
//! \brief Prototypes for the PWM Driver.
//! \version V2.1.1.1
//! \date 07/15/2012
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

#ifndef __xPWM_H__
#define __xPWM_H__

#include "xhw_types.h"
#include "xdebug.h"
#include "xcore.h"


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
//! \addtogroup PWM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Int_Type xPWM Interrupt Type
//! \brief Values that show xPWM Interrupt Type
//! \n
//! \section xPWM_Int_Type_Section 1. Where to use this group
//! Values that can be passed to xPWMIntEnable(),xPWMIntDisable()
//! as the ulIntType parameter.
//! \n
//! \section xPWM_Int_Type_CoX 2.CoX Mandatory and CoX Non-mandatory
//! \verbatim
//! +------------------------+----------------+----------+
//! |xPWM Interrupt Source   |       CoX      | LM3Sxxxx |
//! |------------------------|----------------|----------|
//! |xPWM_INT_PWM            |    Mandatory   |     Y    |
//! |------------------------|----------------|----------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! PWM channels Interrupt
//
#define xPWM_INT_PWM            PWM_INT_PWM

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Event_Type xPWM Event Type
//! \brief Values that show xPWM Event Type
//! \n
//! \section xPWM_Event_Type_Section 1. Where to use this group
//! PWM Event/Error Flag, Used by IntHandle's Event Callback Function as
//! ulEvent parmeter. User Callback function can user this to detect what
//! event happened.
//! \n
//! \section xPWM_Event_Type_CoX 2.CoX Mandatory and CoX Non-mandatory
//! \verbatim
//! +------------------------+----------------+----------+
//! |xPWM Event Source       |       CoX      | LM3Sxxxx |
//! |------------------------|----------------|----------|
//! |xPWM_EVENT_PWM          |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWM_EVENT_CAP          |  non-Mandatory |    Y     |
//! |------------------------|----------------|----------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! The Interrupt event is PWM
//
#define xPWM_EVENT_PWM          PWM_EVENT_PWM

//
//! The Interrupt event is Capture
//
#define xPWM_EVENT_CAP          PWM_EVENT_CAP


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Freq_Config xPWM Frequency Configure
//! \brief xPWM Frequency Configure
//! \n
//! \section xPWM_Event_Type_Section 1. Where to use this group
//! Values that can be passed to xPWMFrequencyConfig() as ulConfig parameter.
//! \n
//! \section xPWM_Event_Type_CoX 2.CoX Mandatory and CoX Non-mandatory
//! \verbatim
//! +------------------------+----------------+----------+
//! |xPWM Freq Config        |       CoX      | LM3Sxxxx |
//! |------------------------|----------------|----------|
//! |xPWM_FREQ_CONFIG(a,b,c) |                |          |
//! |a is The Divider value  |                |          |
//! |b is The PreScale value |    Mandatory   |    Y     |
//! |c is PWM Counter value  |                |          |
//! |------------------------|----------------|----------|
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xPWM_FREQ_CONFIG(a,b,c) (( a<<24 ) | ( b<<16 ) | c)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Channel xPWM Channel
//! \brief Values that show xPWM Channel
//! \n
//! \section xPWM_Channel_Section 1. Where to use this group Values that can be
//!  passed to all the function in xpwm.c as the ulChannel parameter.
//!
//! PWM Event Channel Flag, Used by IntHandle's Event Callback Function as
//! ulMsgParam parmeter. User Callback function can user this to detect what
//! Channel event happened.
//! \n
//! \section xPWM_Channel_CoX 2.CoX Mandatory and CoX Non-mandatory
//! \verbatim
//! +------------------------+----------------+---------------+
//! |xPWM Channel Number     |       CoX      |    LM3Sxxxx   |
//! |------------------------|----------------|---------------|
//! |xPWM_CHANNEL$x$         |  Non-Mandatory | xPWM_CHANNEL0 |
//! |                        |                |---------------|
//! |                        |                | xPWM_CHANNEL1 |
//! |                        |                |---------------|
//! |                        |                | xPWM_CHANNEL2 |
//! |                        |                |---------------|
//! |                        |                | xPWM_CHANNEL3 |
//! |                        |                |---------------|
//! |                        |                | xPWM_CHANNEL4 |
//! |                        |                |---------------|
//! |                        |                | xPWM_CHANNEL5 |
//! |                        |                |---------------|
//! |                        |                | xPWM_CHANNEL6 |
//! |                        |                |---------------|
//! |                        |                | xPWM_CHANNEL7 |
//! |------------------------|----------------|---------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Channel 0
//
#define xPWM_CHANNEL0           PWM_CHANNEL0

//
//! Channel 1
//
#define xPWM_CHANNEL1           PWM_CHANNEL1

//
//! Channel 2
//
#define xPWM_CHANNEL2           PWM_CHANNEL2

//
//! Channel 3
//
#define xPWM_CHANNEL3           PWM_CHANNEL3

//
//! Channel 4
//
#define xPWM_CHANNEL4           PWM_CHANNEL4

//
//! Channel 5
//
#define xPWM_CHANNEL5           PWM_CHANNEL5

//
//! Channel 6
//
#define xPWM_CHANNEL6           PWM_CHANNEL6

//
//! Channel 7
//
#define xPWM_CHANNEL7           PWM_CHANNEL7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Config xPWM Configuration
//! \brief Values that show xPWM Configuration
//! Values that can be passed to PWMConfigure().
//! \n
//! \section xPWM_Config_Section 1. Where to use this group
//! Values that can be passed to xPWMInitConfigure()
//! as the ulConfig parameter.
//! \n
//! \section xPWM_Config_CoX 2.CoX Mandatory and CoX Non-mandatory
//! \verbatim
//! +------------------------+----------------+----------+
//! |xPWM Config             |       CoX      | LM3Sxxxx |
//! |------------------------|----------------|----------|
//! |xPWM_ONE_SHOT_MODE      |    Mandatory   |    N     |
//! |------------------------|----------------|----------|
//! |xPWM_TOGGLE_MODE        |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWM_OUTPUT_INVERTER_EN |  Non-Mandatory |    Y     |
//! |------------------------|----------------|----------|
//! |xPWM_OUTPUT_INVERTER_DIS|  Non-Mandatory |    Y     |
//! |------------------------|----------------|----------|
//! |xPWM_DEAD_ZONE_EN       |  Non-Mandatory |    Y     |
//! |------------------------|----------------|----------|
//! |xPWM_DEAD_ZONE_DIS      |  Non-Mandatory |    Y     |
//! |------------------------|----------------|----------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! One-Shot Mode
//
#define xPWM_ONE_SHOT_MODE         PWM_ONE_SHOT_MODE

//
//! Auto-reload Mode
//
#define xPWM_TOGGLE_MODE           PWM_TOGGLE_MODE

//
//! Inverter enable
//
#define xPWM_OUTPUT_INVERTER_EN    PWM_OUTPUT_INVERTER_EN

//
//! Inverter disable
//
#define xPWM_OUTPUT_INVERTER_DIS   PWM_OUTPUT_INVERTER_DIS

//
//! Dead-Zone 0 Generator enable
//
#define xPWM_DEAD_ZONE_EN          PWM_DEAD_ZONE_EN

//
//! Dead-Zone 0 Generator disable
//
#define xPWM_DEAD_ZONE_DIS         PWM_DEAD_ZONE_DIS

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Exported_APIs xPWM APIs
//! \brief xPWM API Reference.
//! \verbatim
//! +------------------------+----------------+----------+
//! |xPWM API                |       CoX      | LM3Sxxxx |
//! |------------------------|----------------|----------|
//! |xPWMInitConfigure       |    Mandatory   |    N     |
//! |------------------------|----------------|----------|
//! |xPWMFrequencySet        |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWMFrequencyConfig     |    Mandatory   |    N     |
//! |------------------------|----------------|----------|
//! |xPWMFrequencyGet        |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWMOutputEnable        |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWMOutputDisable       |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWMStart               |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWMStop                |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWMDutySet             |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWMDutyGet             |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWMIntEnable           |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWMIntDisable          |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWMIntFlagGet          |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! |xPWMIntCallbackInit     |    Mandatory   |    Y     |
//! |------------------------|----------------|----------|
//! \endverbatim
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! \brief Initialize and configure the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulGen is the PWM channel.
//! \param ulConfig is the configuration of PWM channel.
//! Details please refer to \ref xPWM_Config.
//!
//! This function is to initialize and configure channel of the PWM module.
//!
//! The \e ulGen parameter can be values:0~7
//! when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value 0~3.
//! when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value 4~7.
//!
//! The \e ulConfig parameter is the logical OR of four values: The PWM mode,
//! Inverter or not,and use dead zero or not and dead zone length.
//! \b xPWM_ONE_SHOT_MODE,\b xPWM_TOGGLE_MODE is the mode selecet.
//! \b xPWM_OUTPUT_INVERTER_EN,
//! \b xPWM_OUTPUT_INVERTER_DIS is to enable Inverter or not.
//! \b xPWM_DEAD_ZONE_EN
//! \b xPWM_DEAD_ZONE_DIS is to enable dead zone Generator or not.
//! The dead zone length will be set at the 0~11 and 12~23 bits of the ulConfig.
//! Details please refer to \ref xPWM_Config_CoX.
//!
//! \note for LM3Sxxxx product: 
//!  -# When Dead-Zone Generator is enabled, the pair of (PWM0  & PWM1) 
//!     (PWM2  & PWM3) (PWM4  & PWM5) (PWM6  & PWM7) each becomes a complementary
//!      pair.\n
//!  -# now , LM3S only Supply dead zero configure, CAN NOT Config Pwm mode ,
//!     inverter, if you want to use this feature, use LM3S special API instead.
//! 
//!
//! \return None.
//
//*****************************************************************************
#define xPWMInitConfigure(ulBase, ulGen, ulConfig)                            \
    {}

//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulFrequency is the PWM frequency of PWM channel.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~7
//! when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value 0~3.
//! when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value 4~7.
//!
//! The \e ulFrequency parameter can be values:  0 ~ PWM module input clock.
//!
//! \note if input value of Frequency or the Channel is invaild, then the function
//!       will return ERROR(0) .
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
extern unsigned long  xPWMFrequencySet(unsigned long ulBase,
                                       unsigned long ulChannel,
                                       unsigned long ulFrequency);

//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulConfig is the configuration of PWM channel' frequency.
//! Details please refer to \ref xPWM_Freq_Config.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~7
//! when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value 0~3.
//! when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value 4~7.
//!
//! The \e ulConfig parameter is the logical OR of three values: The PreScale
//! value, The Divider value and the PWM Counter Register value.
//! Details please refer to \ref xPWM_Freq_Config_CoX.
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
#define xPWMFrequencyConfig(ulBase, ulChannel, ulConfig)                      \
{}

//*****************************************************************************
//
//! \brief get the PWM frequency of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to get the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~7
//! when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value 0~3.
//! when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value 4~7.
//!
//! \note None
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
extern unsigned long xPWMFrequencyGet(unsigned long ulBase,
                                      unsigned long ulChannel);

//*****************************************************************************
//
//! \brief Enable the PWM output of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to enable the PWM output of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMOutputEnable(ulBase, ulChannel)                                   \
         PWMOutputState(ulBase, ulChannel, true)

//*****************************************************************************
//
//! \brief Disable the PWM output of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to disable the PWM output of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMOutputDisable(ulBase, ulChannel)                                  \
         PWMOutputState(ulBase, ulChannel, false)

//*****************************************************************************
//
//! \brief Start the PWM of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to start the PWM of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define  xPWMStart(ulBase, ulChannel)                                          \
          PWMGenEnable(ulBase, ulChannel)

//*****************************************************************************
//
//! \brief Stop the PWM of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to stop the PWM of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define  xPWMStop(ulBase, ulChannel)                                          \
          PWMGenDisable(ulBase, ulChannel)

//*****************************************************************************
//
//! \brief Set the PWM duty of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulDuty is the duty of PWM channel.
//!
//! This function is to set the PWM duty of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~7
//! when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value 0~3.
//! when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value 4~7.
//!
//! The \e ulDuty parameter can be values:  duty > 0 && duty <= 100.
//!
//! \note Duty should not be 0.
//!
//! \return None.
//
//*****************************************************************************
extern void xPWMDutySet(unsigned long ulBase,
                        unsigned long ulChannel,
                        unsigned long ulDuty);

//*****************************************************************************
//
//! \brief Get the PWM duty of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to get the PWM duty of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~7
//! when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value 0~3.
//! when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value 4~7.
//!
//! \note if input paramter is invaild, the function will return with ERROR(0)
//!
//! \return the Actual duty of PWM.
//
//*****************************************************************************
extern unsigned long xPWMDutyGet(unsigned long ulBase,
                                 unsigned long ulChannel);

//*****************************************************************************
//
//! \brief Enable the PWM interrupt of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//! Details please refer to \ref xPWM_Int_Type.
//!
//! This function is to enable the PWM interrupt of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulIntType parameter can be values:
//! \b xPWM_INT_PWM.
//! Details please refer to \ref xPWM_Int_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMIntEnable(ulBase, ulChannel, ulIntType)                            \
         PWMGenIntTrigEnable(ulBase, ulChannel, ulIntType)


//*****************************************************************************
//
//! \brief Disable the PWM interrupt of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//! Details please refer to \ref xPWM_Int_Type.
//!
//! This function is to disable the PWM interrupt of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulIntType parameter can be values:
//! \b xPWM_INT_PWM.
//! Details please refer to \ref xPWM_Int_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMIntDisable(ulBase, ulChannel, ulIntType)                           \
         PWMGenIntTrigDisable(ulBase, ulChannel, ulIntType)


//*****************************************************************************
//
//! \brief Get the PWM interrupt flag of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//! Details please refer to \ref xPWM_Int_Type.
//!
//! This function is to get the PWM interrupt flag of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulIntType parameter can be values:
//! \b xPWM_INT_PWM.
//! Details please refer to \ref xPWM_Int_Type_CoX
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
extern unsigned long xPWMIntFlagGet(unsigned long ulBase,
                                    unsigned long ulChannel,
                                    unsigned long ulIntType);

//*****************************************************************************
//
//! \brief Init interrupts callback for the PWM timer.
//!
//! \param ulBase is the PWM Int handler Entry decleard in the startup code.
//!
//! \param xtPortCallback is callback for the PWM timer.
//!
//! \note \b ulBase must be one of the following value:
//! \b PWM_INT_GEN_0  , \b PWM_INT_GEN_1  ,
//! \b PWM_INT_GEN_2  , \b PWM_INT_GEN_3  ,
//! \b PWM_INT_FAULT
//!
//! This function is to init interrupts callback for the PWM Controler.
//!
//! \return None.
//
//*****************************************************************************
extern void xPWMIntCallbackInit(unsigned long ulBase,
                                xtEventCallback xtPWMCallback);

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
//! \addtogroup LM3Sxxxx_PWM
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup LM3Sxxxx_PWM_Config LM3Sxxxx PWM Configuration
//! \brief Values that show LM3Sxxxx PWM Configuration
//! Values that can be passed to PWMGenConfigure().
//! @{
//
//*****************************************************************************

//
// Down count mode
//
#define PWM_GEN_MODE_DOWN             0x00000000

//
// Up/Down count mode
//
#define PWM_GEN_MODE_UP_DOWN          0x00000002

//
// Synchronous updates
//
#define PWM_GEN_MODE_SYNC             0x00000038

//
// Immediate updates
//
#define PWM_GEN_MODE_NO_SYNC          0x00000000

//
// Continue running in debug mode
//
#define PWM_GEN_MODE_DBG_RUN          0x00000004

//
// Stop running in debug mode
//
#define PWM_GEN_MODE_DBG_STOP         0x00000000

//
// Fault is latched
//
#define PWM_GEN_MODE_FAULT_LATCHED    0x00040000

//
// Fault is not latched
//
#define PWM_GEN_MODE_FAULT_UNLATCHED  0x00000000

//
// Enable min fault period
//
#define PWM_GEN_MODE_FAULT_MINPER     0x00020000

//
// Disable min fault period
//
#define PWM_GEN_MODE_FAULT_NO_MINPER  0x00000000

//
// Enable extended fault support
//
#define PWM_GEN_MODE_FAULT_EXT        0x00010000

//
// Disable extended fault support
//
#define PWM_GEN_MODE_FAULT_LEGACY     0x00000000

//
// Deadband updates occur immediately
//
#define PWM_GEN_MODE_DB_NO_SYNC       0x00000000

//
// Deadband updates locally synchronized
//
#define PWM_GEN_MODE_DB_SYNC_LOCAL    0x0000A800

//
// Deadband updates globally synchronized
//
#define PWM_GEN_MODE_DB_SYNC_GLOBAL   0x0000FC00

//
// Generator mode updates occur immediately
//
#define PWM_GEN_MODE_GEN_NO_SYNC      0x00000000

//
// Generator mode updates locally synchronized
//
#define PWM_GEN_MODE_GEN_SYNC_LOCAL   0x00000280

//
// Generator mode updates globally synchronized
//
#define PWM_GEN_MODE_GEN_SYNC_GLOBAL  0x000003C0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Defines for enabling, disabling, and clearing PWM generator interrupts and
// triggers.
//
//*****************************************************************************

//
// Int if COUNT = 0
//
#define PWM_INT_CNT_ZERO        0x00000001

//
// Int if COUNT = LOAD
//
#define PWM_INT_CNT_LOAD        0x00000002

//
// Int if COUNT = CMPA U
//
#define PWM_INT_CNT_AU          0x00000004

//
// Int if COUNT = CMPA D
//
#define PWM_INT_CNT_AD          0x00000008

//
// Int if COUNT = CMPA U
//
#define PWM_INT_CNT_BU          0x00000010

//
// Int if COUNT = CMPA D
//
#define PWM_INT_CNT_BD          0x00000020

//
// Trig if COUNT = 0
//
#define PWM_TR_CNT_ZERO         0x00000100

//
// Trig if COUNT = LOAD
//
#define PWM_TR_CNT_LOAD         0x00000200

//
// Trig if COUNT = CMPA U
//
#define PWM_TR_CNT_AU           0x00000400

//
// Trig if COUNT = CMPA D
//
#define PWM_TR_CNT_AD           0x00000800

//
// Trig if COUNT = CMPA U
//
#define PWM_TR_CNT_BU           0x00001000

//
// Trig if COUNT = CMPA D
//
#define PWM_TR_CNT_BD           0x00002000





//*****************************************************************************
//
// Defines for enabling, disabling, and clearing PWM interrupts.
//
//*****************************************************************************

//
// Generator 0 interrupt
//
#define PWM_INT_GEN_0           0x00000001

//
// Generator 1 interrupt
//
#define PWM_INT_GEN_1           0x00000002

//
// Generator 2 interrupt
//
#define PWM_INT_GEN_2           0x00000004

//
// Generator 3 interrupt
//
#define PWM_INT_GEN_3           0x00000008


#ifndef DEPRECATED

//
// Fault interrupt
//
#define PWM_INT_FAULT           0x00010000

#endif


//
// Fault0 interrupt
//
#define PWM_INT_FAULT0          0x00010000

//
// Fault1 interrupt
//
#define PWM_INT_FAULT1          0x00020000

//
// Fault2 interrupt
//
#define PWM_INT_FAULT2          0x00040000

//
// Fault3 interrupt
//
#define PWM_INT_FAULT3          0x00080000

//
// Fault interrupt source mask
//
#define PWM_INT_FAULT_M         0x000F0000

//*****************************************************************************
//
// Defines to identify the generators within a module.
//
//*****************************************************************************

//
// Offset address of Gen0
//
#define PWM_GEN_0               0x00000040

//
// Offset address of Gen1
//
#define PWM_GEN_1               0x00000080

//
// Offset address of Gen2
//
#define PWM_GEN_2               0x000000C0

//
// Offset address of Gen3
//
#define PWM_GEN_3               0x00000100


//
// Bit-wise ID for Gen0
//
#define PWM_GEN_0_BIT           0x00000001

//
// Bit-wise ID for Gen1
//
#define PWM_GEN_1_BIT           0x00000002

//
// Bit-wise ID for Gen2
//
#define PWM_GEN_2_BIT           0x00000004

//
// Bit-wise ID for Gen3
//
#define PWM_GEN_3_BIT           0x00000008


//
// Offset of Gen0 ext address range
//
#define PWM_GEN_EXT_0           0x00000800

//
// Offset of Gen1 ext address range
//
#define PWM_GEN_EXT_1           0x00000880

//
// Offset of Gen2 ext address range
//
#define PWM_GEN_EXT_2           0x00000900

//
// Offset of Gen3 ext address range
//
#define PWM_GEN_EXT_3           0x00000980

//*****************************************************************************
//
// Defines to identify the outputs within a module.
//
//*****************************************************************************

//
// Encoded offset address of PWM0
//
#define PWM_OUT_0               0x00000040

//
// Encoded offset address of PWM1
//
#define PWM_OUT_1               0x00000041

//
// Encoded offset address of PWM2
//
#define PWM_OUT_2               0x00000082

//
// Encoded offset address of PWM3
//
#define PWM_OUT_3               0x00000083

//
// Encoded offset address of PWM4
//
#define PWM_OUT_4               0x000000C4

//
// Encoded offset address of PWM5
//
#define PWM_OUT_5               0x000000C5

//
// Encoded offset address of PWM6
//
#define PWM_OUT_6               0x00000106

//
// Encoded offset address of PWM7
//
#define PWM_OUT_7               0x00000107


//
// Bit-wise ID for PWM0
//
#define PWM_OUT_0_BIT           0x00000001

//
// Bit-wise ID for PWM1
//
#define PWM_OUT_1_BIT           0x00000002

//
// Bit-wise ID for PWM2
//
#define PWM_OUT_2_BIT           0x00000004

//
// Bit-wise ID for PWM3
//
#define PWM_OUT_3_BIT           0x00000008

//
// Bit-wise ID for PWM4
//
#define PWM_OUT_4_BIT           0x00000010

//
// Bit-wise ID for PWM5
//
#define PWM_OUT_5_BIT           0x00000020

//
// Bit-wise ID for PWM6
//
#define PWM_OUT_6_BIT           0x00000040

//
// Bit-wise ID for PWM7
//
#define PWM_OUT_7_BIT           0x00000080

//*****************************************************************************
//
// Defines to identify each of the possible fault trigger conditions in
// PWM_FAULT_GROUP_0.
//
//*****************************************************************************
#define PWM_FAULT_GROUP_0       0

#define PWM_FAULT_FAULT0        0x00000001
#define PWM_FAULT_FAULT1        0x00000002
#define PWM_FAULT_FAULT2        0x00000004
#define PWM_FAULT_FAULT3        0x00000008
#define PWM_FAULT_ACMP0         0x00010000
#define PWM_FAULT_ACMP1         0x00020000
#define PWM_FAULT_ACMP2         0x00040000

//*****************************************************************************
//
// Defines to identify each of the possible fault trigger conditions in
// PWM_FAULT_GROUP_1.
//
//*****************************************************************************
#define PWM_FAULT_GROUP_1       1

#define PWM_FAULT_DCMP0         0x00000001
#define PWM_FAULT_DCMP1         0x00000002
#define PWM_FAULT_DCMP2         0x00000004
#define PWM_FAULT_DCMP3         0x00000008
#define PWM_FAULT_DCMP4         0x00000010
#define PWM_FAULT_DCMP5         0x00000020
#define PWM_FAULT_DCMP6         0x00000040
#define PWM_FAULT_DCMP7         0x00000080

//*****************************************************************************
//
// Defines to identify the sense of each of the external FAULTn signals
//
//*****************************************************************************
#define PWM_FAULT0_SENSE_HIGH   0x00000000
#define PWM_FAULT0_SENSE_LOW    0x00000001
#define PWM_FAULT1_SENSE_HIGH   0x00000000
#define PWM_FAULT1_SENSE_LOW    0x00000002
#define PWM_FAULT2_SENSE_HIGH   0x00000000
#define PWM_FAULT2_SENSE_LOW    0x00000004
#define PWM_FAULT3_SENSE_HIGH   0x00000000
#define PWM_FAULT3_SENSE_LOW    0x00000008

//*****************************************************************************
//
//! \addtogroup LM3Sxxxx_PWM_Exported_APIs LM3Sxxxx PWM API
//! \brief LM3Sxxxx PWM API Reference.
//! @{
//
//*****************************************************************************

extern void          PWMGenConfigure       (unsigned long ulBase,
                                            unsigned long ulGen,
                                            unsigned long ulConfig);

extern void          PWMGenPeriodSet       (unsigned long ulBase,
                                            unsigned long ulGen,
                                            unsigned long ulPeriod);

extern unsigned long PWMGenPeriodGet       (unsigned long ulBase,
                                            unsigned long ulGen);

extern void          PWMGenEnable          (unsigned long ulBase,
                                            unsigned long ulGen);

extern void          PWMGenDisable         (unsigned long ulBase,
                                            unsigned long ulGen);

extern void          PWMPulseWidthSet      (unsigned long ulBase,
                                            unsigned long ulPWMOut,
                                            unsigned long ulWidth);

extern unsigned long PWMPulseWidthGet      (unsigned long ulBase,
                                            unsigned long ulPWMOut);

extern void          PWMDeadBandEnable     (unsigned long ulBase,
                                            unsigned long ulGen,
                                            unsigned short usRise,
                                            unsigned short usFall);

extern void          PWMDeadBandDisable    (unsigned long ulBase,
                                            unsigned long ulGen);

extern void          PWMSyncUpdate         (unsigned long ulBase,
                                            unsigned long ulGenBits);

extern void          PWMSyncTimeBase       (unsigned long ulBase,
                                            unsigned long ulGenBits);

extern void          PWMOutputState        (unsigned long ulBase,
                                            unsigned long ulPWMOutBits,
                                            xtBoolean     bEnable);

extern void          PWMOutputInvert       (unsigned long ulBase,
                                            unsigned long ulPWMOutBits,
                                            xtBoolean     bInvert);

extern void          PWMOutputFaultLevel   (unsigned long ulBase,
                                            unsigned long ulPWMOutBits,
                                            xtBoolean     bDriveHigh);

extern void          PWMOutputFault        (unsigned long ulBase,
                                            unsigned long ulPWMOutBits,
                                            xtBoolean     bFaultSuppress);

extern void          PWMGenIntTrigEnable   (unsigned long ulBase,
                                            unsigned long ulGen,
                                            unsigned long ulIntTrig);

extern void          PWMGenIntTrigDisable  (unsigned long ulBase,
                                            unsigned long ulGen,
                                            unsigned long ulIntTrig);

extern unsigned long PWMGenIntStatus       (unsigned long ulBase,
                                            unsigned long ulGen,
                                            xtBoolean     bMasked);

extern void          PWMGenIntClear        (unsigned long ulBase,
                                            unsigned long ulGen,
                                            unsigned long ulInts);

extern void          PWMIntEnable          (unsigned long ulBase,
                                            unsigned long ulGenFault);

extern void          PWMIntDisable         (unsigned long ulBase,
                                            unsigned long ulGenFault);

extern void          PWMFaultIntClear      (unsigned long ulBase);

extern unsigned long PWMIntStatus          (unsigned long ulBase,
                                            xtBoolean     bMasked);

extern void          PWMFaultIntClearExt   (unsigned long ulBase,
                                            unsigned long ulFaultInts);

extern void          PWMGenFaultConfigure  (unsigned long ulBase,
                                            unsigned long ulGen,
                                            unsigned long ulMinFaultPeriod,
                                            unsigned long ulFaultSenses);

extern void          PWMGenFaultTriggerSet (unsigned long ulBase,
                                            unsigned long ulGen,
                                            unsigned long ulGroup,
                                            unsigned long ulFaultTriggers);

extern unsigned long PWMGenFaultTriggerGet (unsigned long ulBase,
                                            unsigned long ulGen,
                                            unsigned long ulGroup);

extern unsigned long PWMGenFaultStatus     (unsigned long ulBase,
                                            unsigned long ulGen,
                                            unsigned long ulGroup);

extern void          PWMGenFaultClear      (unsigned long ulBase,
                                            unsigned long ulGen,
                                            unsigned long ulGroup,
                                            unsigned long ulFaultTriggers);

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

#endif // __xPWM_H__

