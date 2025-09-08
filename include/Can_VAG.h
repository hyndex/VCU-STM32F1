/*
 * File: include/Can_VAG.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef Can_VAG_h
#define Can_VAG_h

/*  This library supports the Powertrain CAN messages for VAG cars for driving dash gauges, putting out malf lights etc

*/

#include <stdint.h>
#include "my_fp.h"
#include "stm32_can.h"
#include "vehicle.h"
#include "digio.h"

class Can_VAG: public Vehicle
{
public:
   void Task10Ms();
   void Task100Ms();
   void SetRevCounter(int s) { rpm = s; }
   void SetTemperatureGauge(float) { } //TODO
   bool Ready();// { return true; }
   bool Start();

private:
   uint16_t rpm;
};

#endif /* Can_VAG_h */
