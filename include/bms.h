/*
 * File: include/bms.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef BMS_H
#define BMS_H
#include <stdint.h>
#include "canhardware.h"
#include "params.h"

/* This is an interface for a BMS to provide minimal data required
 * for safe battery charging.  The BMS must be able to provide the
 * following data:
 *   1. Maximum and minimum cell voltages
 *   2. Maximum and minimum cell or module temperatures
 * Each BMS module must log the above data as well as provide a
 * function to return whether charging is permitted and the maximum
 * charge current.
 * The function Task100Ms() will be called every 100ms and should
 * be used to implement a timeout for receiving fata from the BMS.
 */

class BMS
{
   public:
      virtual void DecodeCAN(int, uint8_t *) {};
      virtual void DeInit() {};
      virtual float MaxChargeCurrent() { return 9999.0; };
      virtual void Task100Ms() {
            Param::SetInt(Param::BMS_ChargeLim, MaxChargeCurrent());
            Param::SetFloat(Param::BMS_Vmin, 0);
            Param::SetFloat(Param::BMS_Vmax, 0);
            Param::SetFloat(Param::BMS_Tmin, 0);
            Param::SetFloat(Param::BMS_Tmax, 0);
      };
      virtual void SetCanInterface(CanHardware* c) { can = c; }
   protected:
      CanHardware* can;
};
#endif // BMS_H
