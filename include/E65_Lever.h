/*
 * File: include/E65_Lever.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef E65_Lever_h
#define E65_Lever_h

#include "shifter.h"


class E65_Lever: public Shifter
{
public:


   void Task10Ms();
   void Task100Ms();
   void DecodeCAN(int, uint32_t*);
   bool GetGear(Shifter::Sgear& outGear);//if shifter class knows gear return true and set dir
   void SetCanInterface(CanHardware* c);

private:
   Shifter::Sgear gear;
};


#endif // E65_Lever_INCLUDED


