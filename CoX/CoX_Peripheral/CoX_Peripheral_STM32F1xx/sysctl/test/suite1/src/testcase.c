//*****************************************************************************
//
//
//! \file testcase.c
//! \brief add new testcases.
//! \version 1.0
//! \date 5/13/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#include "test.h"
#include "testcase.h"

//*****************************************************************************
//
// Array of all the test.
//
//*****************************************************************************
const tTestCase * const* g_psPatterns[] =  {
    //
    // xcore test
    //
    //psPatternXsysctl,
    psPatternXsysctl01,
    psPatternXsysctl02,
    psPatternXsysctl03,
    psPatternXsysctl04,
    psPatternXsysctl05,
    psPatternXsysctl06,
    psPatternXsysctl07,
    //
    // end
    //
    0
};


