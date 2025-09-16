/*
 * File: include/heater_can_a.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef HEATER_CAN_A_H
#define HEATER_CAN_A_H

#include <heater.h>


class HeaterCanA : public Heater
{
   public:
      /** Default constructor */
      HeaterCanA();
      void SetTargetTemperature(float temp) { (void)temp; } //Not supported (yet)?
      void SetPower(uint16_t power, bool HeatReq);

   private:
      bool isAwake=false;
      void SendWakeup();
};

#endif // HEATER_CAN_A_H
