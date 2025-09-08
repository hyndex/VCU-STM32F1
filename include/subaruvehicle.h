/*
 * File: include/subaruvehicle.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef SUBARUVEHICLE_H
#define SUBARUVEHICLE_H

#include <vehicle.h>
#include "utils.h"

class SubaruVehicle : public Vehicle
{
   public:
      /** Default constructor */
      SubaruVehicle();
      void SetCanInterface(CanHardware* c);
      bool GetGear(gear& gear);
      bool Ready() { return true; }
      void SetRevCounter(int speed);
      void SetTemperatureGauge(float temp);
      void SetFuelGauge(float level);
      float GetFrontRearBalance();
      int GetCruiseState();
      bool EnableTractionControl();

   protected:

   private:
      gear lastGear;
      int timerPeriod;
      float frontRearBalance;
      bool tcOn;
      bool ccOn;
};

#endif // SUBARUVEHICLE_H
