/*
 * File: include/heater_can_b.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef HEATER_CAN_B_H
#define HEATER_CAN_B_H

//#include <libopencm3/stm32/usart.h>
#include <heater.h>


class HeaterCanB : public Heater
{
   public:
      void SetTargetTemperature(float temp);
      void SetCanInterface(CanHardware* c);
      void DecodeCAN(int id, uint32_t data[2]);
      void SetPower(uint16_t power, bool HeatReq);
      void Task100Ms();

   private:
      int8_t currentTemperature;
      int8_t desiredTemperature;

      bool shouldHeat;
      static void handle398(uint32_t data[2]);

};

#endif // HEATER_CAN_B_H
