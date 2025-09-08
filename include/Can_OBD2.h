/*
 * File: include/Can_OBD2.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef Can_OBD2_h
#define Can_OBD2_h

#include "stm32_can.h"

class Can_OBD2
{
public:
  void SetCanInterface(CanHardware *c);
  void DecodeCAN(int id, uint32_t data[2]);

protected:
  CanHardware *can;
};

#endif /* Can_OBD2_h */
