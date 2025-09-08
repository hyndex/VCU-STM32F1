/*
 * File: test/test_list.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */


#ifndef TEST_LIST_H_INCLUDED
#define TEST_LIST_H_INCLUDED

#include "test.h"

class ThrottleTest: public IUnitTest
{
   public:
      virtual void RunTest();
};

#ifdef EXPORT_TESTLIST
IUnitTest* testList[] =
{
   new ThrottleTest(),
   NULL
};
#endif

#endif // TEST_LIST_H_INCLUDED
