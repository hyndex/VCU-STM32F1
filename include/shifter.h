/*
 * File: include/shifter.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef SHIFTER_H_INCLUDED
#define SHIFTER_H_INCLUDED
#include <stdint.h>
#include "canhardware.h"
#include "params.h"

class Shifter
{
public:
   enum Sgear { PARK, REVERSE, NEUTRAL, DRIVE };

   virtual void Task1Ms() {} //Default does nothing
   virtual void Task10Ms() {} //Default does nothing
   virtual void Task100Ms() {} //Default does nothing
   virtual void Task200Ms() {} //Default does nothing
   virtual void DecodeCAN(int, uint32_t*) {};
   virtual bool GetGear(Sgear&) { return false; } //if shifter class knows gear return true and set dir
   virtual void SetCanInterface(CanHardware* c) { can = c; }

protected:
   CanHardware* can;
};

#endif // SHIFTER_H_INCLUDED

