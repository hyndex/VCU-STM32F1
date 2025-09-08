/*
 * File: test/test_main.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */


#include <iostream>
#include "test.h"
#define EXPORT_TESTLIST
#include "test_list.h"

using namespace std;

int _failedAssertions = 0;

int main()
{
   int dummy;
   IUnitTest** currentTest = testList;

   cout << "Starting unit Tests" << endl;

   while (*currentTest)
   {
      (*currentTest)->RunTest();
      currentTest++;
   }

   if (_failedAssertions > 0)
   {
      cout << _failedAssertions << " assertions failed" << endl;
      return -1;
   }

   cout << "All tests passed" << endl;

   return 0;
}
