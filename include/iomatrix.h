/*
 * File: include/iomatrix.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef IOMATRIX_H
#define IOMATRIX_H

#include "digio.h"
#include "params.h"
#include "anain.h"

class IOMatrix
{
   public://order of these matters!
      enum pinfuncs
      {
         NONE, CHADEMOALLOW, OBCENABLE, HEATERENABLE, RUNINDICATION, WARNINDICATION,
         COOLANTPUMP, NEGCONTACTOR, BRAKELIGHT, REVERSELIGHT, HEATREQ, HVREQ,
         DCFCREQUEST, BRAKEVACPUMP, COOLINGFAN, HVACTIVE, PWM_TIM3,CP_SPOOF,
         GS450HOIL, LAST
      };
            //order of these matters!
      enum analoguepinfuncs
      {
         NONE_ANAL, PILOT_PROX, VAC_SENSOR, LAST_ANAL
      };

      static void AssignFromParams();
      static void AssignFromParamsAnalogue();
      static DigIo* GetPin(pinfuncs f) { return functionToPin[f]; }
      static AnaIn* GetAnaloguePin(analoguepinfuncs f) { return functionToPinAnalgoue[f]; }

   private:
      static DigIo* functionToPin[LAST];
      static const int numPins = 13;
      static DigIo* const paramToPin[numPins];

      static AnaIn* functionToPinAnalgoue[LAST_ANAL];
      static const int numAnaloguePins = 2;
      static AnaIn* const paramToPinAnalgue[numAnaloguePins];
};

#endif // IOMATRIX_H
