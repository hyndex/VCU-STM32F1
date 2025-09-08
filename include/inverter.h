/*
 * File: include/inverter.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef INVERTER_H_INCLUDED
#define INVERTER_H_INCLUDED

#include "canhardware.h"

class Inverter
{
public:
   virtual void Task1Ms() {} //Default does nothing
   virtual void Task10Ms() {} //Default does nothing
   virtual void Task100Ms() {} //Default does nothing
   virtual void DecodeCAN(int, uint32_t*) {};
   virtual void SetTorque(float torquePercent) = 0;
   virtual float GetMotorTemperature() = 0;
   virtual float GetInverterTemperature() = 0;
   virtual float GetInverterVoltage() = 0;
   virtual float GetMotorSpeed() = 0;
   virtual int GetInverterState() = 0;
   virtual void DeInit() {} //called when switching to another inverter, similar to a destructor
   virtual void SetCanInterface(CanHardware* c) { can = c; }

protected:
   CanHardware* can;
};

#endif // INVERTER_H_INCLUDED
