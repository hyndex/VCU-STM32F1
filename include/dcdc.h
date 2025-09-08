/*
 * File: include/dcdc.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef DCDC_H
#define DCDC_H
#include <stdint.h>
#include "canhardware.h"
#include "params.h"

class DCDC
{
   public:
      virtual void DecodeCAN(int, uint8_t *) {};
      virtual void DeInit() {};
      virtual void Task1Ms() {};
      virtual void Task10Ms() {};
      virtual void Task100Ms() {};
      virtual void SetCanInterface(CanHardware* c) { can = c; }
   protected:
      CanHardware* can;
};
#endif // DCDC_H

