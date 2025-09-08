/*
 * File: include/Can_OI.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef CAN_OI_H
#define CAN_OI_H

#include "inverter.h"
#include "canhardware.h"
#include <stdint.h>

class Can_OI: public Inverter
{
public:
   void Task100Ms() override;
   void DecodeCAN(int, uint32_t*) override;
   void SetTorque(float torquePercent) override;
   float GetMotorTemperature() override { return motor_temp; }
   float GetInverterTemperature() override { return inv_temp; }
   float GetInverterVoltage() override { return voltage; }
   float GetMotorSpeed() override { return speed; }
   int GetInverterState() override;
   void SetCanInterface(CanHardware* c) override;

private:
   static int16_t speed;
   static int16_t inv_temp;
   static int16_t motor_temp;
   static uint16_t voltage;
   static int16_t final_torque_request;
};

#endif // CAN_OI_H
