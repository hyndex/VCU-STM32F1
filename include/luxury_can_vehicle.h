/*
 * File: include/luxury_can_vehicle.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



// Premium/luxury CAN-driven cluster profile (previously BMW_E65)

#ifndef LUXURY_CAN_VEHICLE_H
#define LUXURY_CAN_VEHICLE_H

/*  This module supports powertrain CAN messaging for large luxury
    platforms, including cluster and gear selector handling. */

#include <stdint.h>
#include "vehicle.h"
#include "my_math.h"

class LuxuryCanVehicle: public Vehicle
{
public:
   LuxuryCanVehicle() : terminal15On(false), dashInit(false), gear(PARK) { }
   void SetCanInterface(CanHardware*);
   void Task10Ms();
   void Task100Ms();
   void Task200Ms();
   void SetRevCounter(int speed) { revCounter = speed; }
   void SetTemperatureGauge(float temp) { temperature = temp; }
   void DecodeCAN(int, uint32_t* data);
   bool Ready() { return terminal15On; }
   bool Start() { return terminal15On; }
   void DashOff();
   void handle130(uint32_t data[2]);
   void handle1A0(uint32_t data[2]);
   void handle2FC(uint32_t data[2]);
   void handle480(uint32_t data[2]);
   void SetAlternateTrim(bool enable) { alternateTrim = enable; }
   void Engine_Data();
   void SetFuelGauge(float level);

private:
   void SendAbsDscMessages(bool Brake_In);

   bool terminal15On;
   bool terminalROn;
   bool terminal50On;
   bool dashInit;
   Vehicle::gear gear;
   int revCounter;
   float temperature;
   bool  CANWake;
   bool  StartButt;
   bool alternateTrim = false;
};

#endif /* LUXURY_CAN_VEHICLE_H */
