/*
 * File: include/analog_can_vehicle.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



// Generic analog cluster vehicle implementation (previously BMW_E31)

#ifndef ANALOG_CAN_VEHICLE_H
#define ANALOG_CAN_VEHICLE_H

/*  This module supports analog-instrument clusters driven via CAN and
    provides EGS/DME message publishing for compatibility with legacy
    drivetrains. */

#include <stdint.h>
#include "vehicle.h"
#include "digio.h"
#include "utils.h"
#include "stm32_can.h"

class AnalogCanVehicle: public Vehicle
{

public:
   void SetCanInterface(CanHardware* c);
   void Task10Ms();
   void Task100Ms();
   void Task1Ms();
   void SetRevCounter(int s);
   void SetTemperatureGauge(float temp);
   void DecodeCAN(int id, uint32_t* data);
   bool Ready();
   bool Start();


private:
   uint16_t speed;
   uint32_t timerPeriod;
   bool timerIsRunning=false;
   void EGSMsg43F(int8_t gear);
   void EGSMsg43B();

};

#endif /* ANALOG_CAN_VEHICLE_H */

