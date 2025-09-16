/*
 * File: include/bms_controller_c.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef BMS_CONTROLLER_C_H
#define BMS_CONTROLLER_C_H

#include "bms.h"
#include "canhardware.h"
#include <stdint.h>

class BmsControllerC: public BMS
{
   public:
      void SetCanInterface(CanHardware* c) override;
      void DecodeCAN(int id, uint8_t * data) override;
      float MaxChargeCurrent() override;
      void Task100Ms() override;
   private:
      bool BMSDataValid();
      bool ChargeAllowed();
      float temperature(uint16_t adc);
      int timeoutCounter[2];
      uint16_t minCell[2] = {0, 0};
      uint16_t maxCell[2] = {0, 0};
      uint16_t minTemp[2] = {0, 0};
      uint16_t maxTemp[2] = {0, 0};
      float minCellV = 0;
      float maxCellV = 0;
      float minTempC = 0;
      float maxTempC = 0;
};
#endif // BMS_CONTROLLER_C_H
