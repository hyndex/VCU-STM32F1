/*
 * File: include/Preheater.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */


#ifndef PREHEATER_H
#define PREHEATER_H
#include <stdint.h>
#include "params.h"

class Preheater 
{
public:
   Preheater();
    void Task200Ms(int opmode, unsigned hours, unsigned minutes);
    void Ms10Task();
    void ParamsChange();
    void SetInitByPreHeat(bool initbyPH);

    bool GetRunPreHeat();
    bool GetInitByPreHeat();

private:
    //Preheat matching the charger timer
    uint8_t PreHeatSet;
    bool RunPreHeat;
    uint32_t PreheatTicks;
    uint32_t PreheatTicks_1Min;
    uint8_t PreHeatHrs_tmp;
    uint8_t PreHeatMins_tmp;
    uint16_t PreHeatDur_tmp;
    bool initbyPreHeat;
};

#endif // PREHEATER_H
