/*
 * File: include/OutlanderCanHeater.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef OUTLANDERCANHEATER_H
#define OUTLANDERCANHEATER_H

//#include <libopencm3/stm32/usart.h>
#include <heater.h>


class OutlanderCanHeater : public Heater
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

#endif // OUTLANDERCANHEATER_H
