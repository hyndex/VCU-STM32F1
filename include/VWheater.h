/*
 * File: include/VWheater.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef VWHEATER_H
#define VWHEATER_H

//#include <libopencm3/stm32/usart.h>
#include <heater.h>
#include "linbus.h"


class vwHeater : public Heater
{
   public:
      void SetTargetTemperature(float temp) { (void)temp; } //Not supported (yet)?
      void SetPower(uint16_t power, bool HeatReq);
      void SetLinInterface(LinBus* l);

   private:
      bool isAwake=false;
      LinBus* lin;
};

#endif // VWHEATER_H
