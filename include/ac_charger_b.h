/*
 * File: include/ac_charger_b.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef AC_CHARGER_B_H
#define AC_CHARGER_B_H

#include <stdint.h>
#include "my_fp.h"
#include "chargerhw.h"

class AcChargerB: public Chargerhw
{
public:
   void DecodeCAN(int id, uint32_t data[2]);
   void Task10Ms();
   void Task100Ms();
   bool ControlCharge(bool RunCh, bool ACReq);
//   void SetTorque(float torque);
//   float GetMotorTemperature() { return motor_temp; }
//   float GetInverterTemperature() { return inv_temp; }
//   float GetInverterVoltage() { return voltage / 2; }
//   float GetMotorSpeed() { return speed / 2; }
//   int GetInverterState() { return error; }
   void SetCanInterface(CanHardware* c);

private:
   static void nissan_crc(uint8_t *data, uint8_t polynomial);
   static int8_t fahrenheit_to_celsius(uint16_t fahrenheit);
//   uint32_t lastRecv;
//   int16_t speed;
//   int16_t inv_temp;
//   int16_t motor_temp;
//   bool error;
//   uint16_t voltage;
//   int16_t final_torque_request;
};

#endif // AC_CHARGER_B_H
