/*
 * File: include/amperaheater.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef AMPERAHEATER_H
#define AMPERAHEATER_H

#include <heater.h>


class AmperaHeater : public Heater
{
   public:
      /** Default constructor */
      AmperaHeater();
      void SetTargetTemperature(float temp) { (void)temp; } //Not supported (yet)?
      void SetPower(uint16_t power, bool HeatReq);

   private:
      bool isAwake=false;
      void SendWakeup();
};

#endif // AMPERAHEATER_H
