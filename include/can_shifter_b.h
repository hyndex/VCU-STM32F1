/*
 * File: include/can_shifter_b.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef CAN_SHIFTER_B_H
#define CAN_SHIFTER_B_H

#include "shifter.h"

class CanShifterB: public Shifter
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


#endif // CAN_SHIFTER_B_H

