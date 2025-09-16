/*
 * File: include/classic_io_vehicle.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



// Classic IO-based vehicle integration (previously V_Classic)

#ifndef CLASSIC_IO_VEHICLE_H
#define CLASSIC_IO_VEHICLE_H


#include <stdint.h>
#include "vehicle.h"
#include "digio.h"
#include "utils.h"
#include "stm32_can.h"

class ClassicIoVehicle: public Vehicle
{

public:
   void SetCanInterface(CanHardware* c);
   void Task10Ms();
   void Task100Ms();
   void Task1Ms();
   void SetRevCounter(int s);
   void SetTemperatureGauge(float temp);
   bool Ready();
   bool Start();


private:
   uint16_t speed;

};

#endif /* CLASSIC_IO_VEHICLE_H */

