/*
 * File: include/chademo.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef CHADEMO_H
#define CHADEMO_H
#include <libopencm3/stm32/rtc.h>
#include <stdint.h>
#include "my_math.h"
#include "my_fp.h"
#include "CANSPI.h"
#include "chargerint.h"
#include "params.h"
#include "iomatrix.h"

class FCChademo: public Chargerint
{
   public:
      void DecodeCAN(int id, uint32_t data[2]);
      void Task100Ms();//Must be called every 100ms
      void Task200Ms();
      bool DCFCRequest(bool RunCh);
      bool ACRequest(bool RunCh){return RunCh;};

   protected:

   private:
      static void Process108Message(uint32_t data[2]);
      static void Process109Message(uint32_t data[2]);
      static bool chargeEnabled;
      static bool parkingPosition;
      static bool fault;
      static bool contactorOpen;
      static uint8_t chargerStatus;
      static uint8_t chargerMaxCurrent;
      static uint16_t chargerMaxVoltage;
      static uint8_t chargeCurrentRequest;
      static uint32_t rampedCurReq;
      static uint16_t targetBatteryVoltage;
      static uint16_t chargerOutputVoltage;
      static uint8_t chargerOutputCurrent;
      static uint8_t soc;
      static uint32_t vtgTimeout;
      static uint32_t curTimeout;
      static void SetTargetBatteryVoltage(uint16_t vtg) { targetBatteryVoltage = vtg; }
      static void SetChargeCurrent(uint8_t cur);
      static void SetEnabled(bool enabled);

      static void SetParkPosition(bool pos) { parkingPosition = !pos; }//Set vehicle in parking position, true=yes, 0=false
      static void SetContactor(bool state) { contactorOpen = !state; }
      static void SetGeneralFault() { fault = true; }

      static void SetSoC(float soC) { soc = soC * 2; }//Set current state of charge
      static int GetChargerOutputVoltage() { return chargerOutputVoltage; }
      static int GetChargerOutputCurrent() { return chargerOutputCurrent; }
      static int GetChargerMaxCurrent() { return chargerMaxCurrent; }
      static int GetChargerMaxVoltage() { return chargerMaxVoltage; }
      static int GetChargerStatus() { return chargerStatus; }
      static bool ConnectorLocked() { return (chargerStatus & 0x4) != 0; }
      static bool ChargerStopRequest() { return (chargerStatus & 0x2A) != 0; }
      static uint8_t GetRampedCurrentRequest() { return rampedCurReq; }

      static void CheckSensorDeviation(uint16_t internalVoltage);//Must be called every 100 ms
};

#endif // CHADEMO_H
