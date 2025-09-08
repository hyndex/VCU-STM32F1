/*
 * File: include/BMW_E39.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef BMW_E39_h
#define BMW_E39_h

/*  This library supports the Powertrain CAN messages for the BMW E39 for driving dash gauges, putting out malf lights etc

*/

#include <stdint.h>
#include "vehicle.h"


class BMW_E39: public Vehicle
{

public:
   void SetCanInterface(CanHardware* c);
   void Task10Ms();
   void Task100Ms();
   void SetRevCounter(int s) { speed = s; }
   void SetTemperatureGauge(float temp);
   void DecodeCAN(int id, uint32_t* data);
   bool Ready();
   bool Start();
   void SetE46(bool e46) { isE46 = e46; }

private:
   void Msg316();
   void Msg329();
   void Msg545();
   void Msg43F(int8_t gear);
   void Msg43B();

   uint16_t speed;
   bool isE46;
   bool AbsCANalive;
   bool SendCAN;
};

#endif /* Can_E39_h */

