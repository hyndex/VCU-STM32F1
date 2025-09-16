/*
 * File: include/heater_lin_a.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef HEATER_LIN_A_H
#define HEATER_LIN_A_H

//#include <libopencm3/stm32/usart.h>
#include <heater.h>
#include "linbus.h"


class HeaterLinA : public Heater
{
   public:
      void SetTargetTemperature(float temp) { (void)temp; } //Not supported (yet)?
      void SetPower(uint16_t power, bool HeatReq);
      void SetLinInterface(LinBus* l);

   private:
      bool isAwake=false;
      LinBus* lin;
};

#endif // HEATER_LIN_A_H
