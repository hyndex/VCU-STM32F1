/*
 * File: include/dcdc_module_a.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef DCDC_MODULE_A_H
#define DCDC_MODULE_A_H
#include <stdint.h>
#include "dcdc.h"

/* This is an interface for The Tesla GEN2 DCDC converter
 * https://openinverter.org/wiki/Tesla_Model_S/X_DC/DC_Converter
 */

class DcdcModuleA: public DCDC
{
   public:
      void DecodeCAN(int, uint8_t *);
      void DeInit() {};
      void Task100Ms();
      void SetCanInterface(CanHardware* c);
   protected:
      CanHardware* can;
   private:
      uint8_t timer500=0;
};
#endif // DCDC_MODULE_A_H

