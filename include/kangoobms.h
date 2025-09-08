/*
 * File: include/kangoobms.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef KANGOOBMS_H
#define KANGOOBMS_H

#include "bms.h"
#include "canhardware.h"
#include <stdint.h>


class KangooBMS: public BMS
{
   public:
      void SetCanInterface(CanHardware* c) override;
      void DecodeCAN(int id, uint8_t * data) override;
      float MaxChargeCurrent() override;
      void Task100Ms() override;

   private:
      bool BMSDataValid();
      int messageCounter = 0;
      int chargeCurrentLimit = 0;
      int timeoutCounter = 0;
      uint16_t maxChargeAllowed = 0;
      uint8_t maxInput = 0;
      uint8_t maxOutput = 0;
      uint16_t isolationResistance = 0;
      float minCellV = 0;
      float maxCellV = 0;
      float minTempC = 0;
      float maxTempC = 0;
      float stateOfCharge = 0;
      float current = 0;
      float remainingKHW = 0;
      float batteryVoltage = 500; //higher than possible so cannot complete precharge until BMS reports battery voltage 
};
#endif // SIMPBMS_H
