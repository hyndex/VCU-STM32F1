/*
 * File: include/V_Classic.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef V_Classic_h
#define V_Classic_h


#include <stdint.h>
#include "vehicle.h"
#include "digio.h"
#include "utils.h"
#include "stm32_can.h"

class V_Classic: public Vehicle
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

#endif /* BMW_E31_h */


