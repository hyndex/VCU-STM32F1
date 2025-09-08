/*
 * File: include/BMW_E31.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef BMW_E31_h
#define BMW_E31_h

/*  This library supports the BMW E31 8 series. Will include some EGS/DME Can and driving analog instruments

*/

#include <stdint.h>
#include "vehicle.h"
#include "digio.h"
#include "utils.h"
#include "stm32_can.h"

class BMW_E31: public Vehicle
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

#endif /* BMW_E31_h */


