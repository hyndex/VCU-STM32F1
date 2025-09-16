/*
 * File: include/multi_can_vehicle.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



// Generic mid-2000s CAN cluster support (previously Can_VAG)

#ifndef MULTI_CAN_VEHICLE_H
#define MULTI_CAN_VEHICLE_H

/*  This module publishes powertrain CAN messages for miscellaneous CAN
    gauge clusters. */

#include <stdint.h>
#include "my_fp.h"
#include "stm32_can.h"
#include "vehicle.h"
#include "digio.h"

class MultiCanVehicle: public Vehicle
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

#endif /* MULTI_CAN_VEHICLE_H */
