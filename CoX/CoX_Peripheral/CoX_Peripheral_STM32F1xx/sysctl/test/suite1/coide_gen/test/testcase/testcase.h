//*****************************************************************************
//
//! \file testcase.h
//! \brief Add new testcases.
//! \version 1.0
//! \date 5/13/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#ifndef __TESTCASE_H__
#define __TESTCASE_H__

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
//! \brief   User define.
//
//*****************************************************************************
//
//! \brief Test component libray name
//
#define TEST_COMPONENTS_NAME    "ST STM32F1xx COX Packet"

//
//! \brief Test component version
//
#define TEST_COMPONENTS_VERSION "V1.0.0"

//
//! \brief Evkit name
//
#define TEST_BOARD_NAME         "MCBSTM32 board"


//
// Test Suites Buffer
//
extern const tTestCase * const* g_psPatterns[];


//*****************************************************************************
//
// testcases(extern the testcases)
//
//*****************************************************************************
//extern const tTestCase * const psPatternXsysctl[];
//extern const tTestCase * const psPatternXsysctl01[];
extern const tTestCase * const psPatternXsysctl02[];
extern const tTestCase * const psPatternXsysctl03[];
//extern const tTestCase * const psPatternXsysctl04[];
//extern const tTestCase * const psPatternXsysctl05[];

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // __TESTCASE_H__

