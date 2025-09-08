/*
 * File: include/noHeater.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef NOHEATER_H
#define NOHEATER_H

#include <heater.h>


class noHeater: public Heater
{

public:
      void SetTargetTemperature(float temp) { (void)temp; } //Not supported (yet)?
      void SetPower(uint16_t, bool){};

private:

};

#endif // NOHEATER_H
