/*
 * File: src/iomatrix.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include "iomatrix.h"

DigIo* const IOMatrix::paramToPin[] = { &DigIo::gp_out1, &DigIo::gp_out2, &DigIo::gp_out3,
                                        &DigIo::SL1_out, &DigIo::SL2_out,
                                        &DigIo::PWM1, &DigIo::PWM2, &DigIo::PWM3,&DigIo::gp_12Vin,
                                        &DigIo::HV_req,&DigIo::gear1_in,&DigIo::gear2_in,&DigIo::gear3_in};
                                        //order of these matters!

AnaIn* const IOMatrix::paramToPinAnalgue[] = {
   &AnaIn::GP_analog1, &AnaIn::GP_analog2
};

DigIo* IOMatrix::functionToPin[];

void IOMatrix::AssignFromParams()
{
   for (int i = 0; i < LAST; i++)
   {
      functionToPin[i] = &DigIo::dummypin;
   }

   for (int i = 0; i < 10; i++)//First orignal IO pin params
   {
      functionToPin[Param::GetInt((Param::PARAM_NUM)(FIRST_IO_PARAM + i))] = paramToPin[i]; //Hard coded so hard coded bodge to fix
   }

   for (int i = 10; i < numPins; i++)//PB1 PB2 PB3 params
   {
      functionToPin[Param::GetInt((Param::PARAM_NUM)(SEC_IO_PARAM + i-10))] = paramToPin[i]; //Hard coded so hard coded bodge to fix
   }
}

AnaIn* IOMatrix::functionToPinAnalgoue[];

void IOMatrix::AssignFromParamsAnalogue()
{
   for (int i = 0; i < LAST_ANAL; i++)
   {
      functionToPinAnalgoue[i] = &AnaIn::dummyAnal;
   }

   for (int i = 0; i < numAnaloguePins; i++)
   {
      functionToPinAnalgoue[Param::GetInt((Param::PARAM_NUM)(FIRST_AI_PARAM + i))] = paramToPinAnalgue[i];
   }
}
