/*
 * File: include/chargerint.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef CHARGERINT_H_INCLUDED
#define CHARGERINT_H_INCLUDED

#include "canhardware.h"

class Chargerint
{
public:
   virtual void Task1Ms() {} //Default does nothing
   virtual void Task10Ms() {} //Default does nothing
   virtual void Task100Ms() {} //Default does nothing
   virtual void Task200Ms() {} //Default does nothing
   virtual void DecodeCAN(int, uint32_t*) {};
   virtual bool DCFCRequest(bool) {return false;};
   virtual bool ACRequest(bool) {return true;};
   virtual void DeInit() {} //called when switching to another charger, similar to a destructor
   virtual void SetCanInterface(CanHardware* c) { can = c; }

protected:
   CanHardware* can;
};

#endif // CHARGERINT_H_INCLUDED


