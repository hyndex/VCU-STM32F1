/*
 * File: include/bms_controller_a.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef BMS_CONTROLLER_A_H
#define BMS_CONTROLLER_A_H

#include "bms.h"
#include "canhardware.h"
#include <stdint.h>

class BmsControllerA: public BMS
{
   public:
      void SetCanInterface(CanHardware* c) override;
      void DecodeCAN(int id, uint8_t * data) override;
      float MaxChargeCurrent() override;
      void Task100Ms() override;
   private:
      bool BMSDataValid();
      bool ChargeAllowed();
      int chargeCurrentLimit = 0;  // Sent by Simp as 0.1A per digit and stored the same way.
      int timeoutCounter = 0;
      float minCellV = 0;
      float maxCellV = 0;
      float minTempC = 0;
      float maxTempC = 0;
};
#endif // BMS_CONTROLLER_A_H
