/*
 * File: include/outlanderinverter.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef OUTLANDERINVERTER_H
#define OUTLANDERINVERTER_H

#include <inverter.h>

class OutlanderInverter : public Inverter
{
public:
   OutlanderInverter();
   void SetCanInterface(CanHardware* c);
   void DecodeCAN(int id, uint32_t data[2]);
   void Task10Ms();
   void Task100Ms();
   void SetTorque(float torque);
   float GetMotorTemperature() { return motor_temp; }
   float GetInverterTemperature() { return inv_temp; }
   float GetInverterVoltage() { return voltage; }
   float GetMotorSpeed() { return speed; }
   int GetInverterState() { return error; }

private:
   uint8_t run10ms;
   uint32_t lastRecv;
   int16_t speed;
   int16_t inv_temp;
   int16_t motor_temp;
   bool error;
   uint16_t voltage;
   uint32_t final_torque_request;
};

#endif // OUTLANDERINVERTER_H
