/*
 * File: include/JLR_G1.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef JLR_G1_h
#define JLR_G1_h

#include "shifter.h"

class JLR_G1: public Shifter
{
public:


   void Task10Ms();
   void Task100Ms();
   void DecodeCAN(int, uint32_t*);
   bool GetGear(Shifter::Sgear& outGear);//if shifter class knows gear return true and set dir
   void SetCanInterface(CanHardware* c);

private:
   void sendcan();
   Shifter::Sgear gear;
};


#endif


