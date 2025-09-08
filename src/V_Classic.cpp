/*
 * File: src/V_Classic.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include "V_Classic.h"
#include "hwinit.h"
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/gpio.h>
#include "my_math.h"


//We use this as an init function
void V_Classic::SetCanInterface(CanHardware* c)//Abusing the SetCanInterface as a initializer function on start up
{
    can = c;
    utils::SpeedoStart();
}


void V_Classic::SetRevCounter(int speed)
{
    uint16_t speed_input = speed;
    speed_input = MAX(750, speed_input);//
    speed_input = MIN(7500, speed_input);

    utils::SpeedoSet(speed_input);//Moved pwm control into Utils
}


void V_Classic::SetTemperatureGauge(float temp)
{
    float dc = temp * 10; //TODO find right factor for value like 0..0.5 or so
    //Would like to use digi pots here
    dc = dc;
}

void V_Classic::Task1Ms()
{

}


void V_Classic::Task10Ms()
{

}


void V_Classic::Task100Ms()
{
    if (!Param::GetInt(Param::T15Stat))
    {
        utils::SpeedoSet(0);//set speedo off
    }
}


bool V_Classic::Ready()
{
    return DigIo::t15_digi.Get();
}

bool V_Classic::Start()
{
    return Param::GetBool(Param::din_start);
}
