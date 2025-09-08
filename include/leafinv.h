/*
 * File: include/leafinv.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef LEAFINV_H
#define LEAFINV_H

#include <stdint.h>
#include "my_fp.h"
#include "inverter.h"

class LeafINV: public Inverter
{
public:
   void DecodeCAN(int id, uint32_t data[2]);
   void Task10Ms();
   void Task100Ms();
   static bool ControlCharge(bool RunCh);
   void SetTorque(float torque);
   float GetMotorTemperature() { return motor_temp; }
   float GetInverterTemperature() { return inv_temp; }
   float GetInverterVoltage() { return voltage; }
   float GetMotorSpeed() { return speed; }
   int GetInverterState() { return error; }
   void SetCanInterface(CanHardware* c);
private:
   uint8_t nissan_crc(uint8_t *data);
   static int8_t fahrenheit_to_celsius(uint16_t fahrenheit);
   uint32_t lastRecv;
   int16_t speed;
   int16_t inv_temp;
   int16_t motor_temp;
   bool error;
   uint16_t voltage;
   int16_t final_torque_request;
};

#endif // LEAFINV_H
