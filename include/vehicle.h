/*
 * File: include/vehicle.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

#include "canhardware.h"
#include "params.h"

class Vehicle
{
public:
   enum gear { PARK, REVERSE, NEUTRAL, DRIVE };
   enum cruise { CC_NONE = 0, CC_ON = 1, CC_CANCEL = 2, CC_SET = 4, CC_RESUME = 8 };

   virtual void Task1Ms() {} //Default does nothing
   virtual void Task10Ms() {} //Default does nothing
   virtual void Task100Ms() {} //Default does nothing
   virtual void Task200Ms() {} //Default does nothing
   virtual void DecodeCAN(int, uint32_t*) {};
   virtual void DashOff() {}
   virtual void SetRevCounter(int speed) = 0;
   virtual void SetTemperatureGauge(float temp) = 0;
   virtual void SetFuelGauge(float level) { (void)level; }; //SoC 0-100%
   virtual bool GetGear(gear&) { return false; } //if vehicle class knows gear return true and set dir
   virtual int GetCruiseState() { return CC_NONE; }
   virtual float GetFrontRearBalance() { return 50; } //100% - all front, 0% all rear
   virtual bool EnableTractionControl() { return false; }
   virtual bool Ready() = 0;
   virtual bool Start() { return Param::GetBool(Param::din_start); }
   virtual void SetCanInterface(CanHardware* c) { can = c; }

protected:
   CanHardware* can;
};

#endif // VEHICLE_H_INCLUDED
