/*
 * File: src/classic_io_vehicle.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include "classic_io_vehicle.h"
#include "hwinit.h"
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/gpio.h>
#include "my_math.h"


//We use this as an init function
void ClassicIoVehicle::SetCanInterface(CanHardware* c)//Abusing the SetCanInterface as a initializer function on start up
{
    can = c;
    utils::SpeedoStart();
}


void ClassicIoVehicle::SetRevCounter(int speed)
{
    uint16_t speed_input = speed;
    speed_input = MAX(750, speed_input);//
    speed_input = MIN(7500, speed_input);

    utils::SpeedoSet(speed_input);//Moved pwm control into Utils
}


void ClassicIoVehicle::SetTemperatureGauge(float temp)
{
    float dc = temp * 10; //TODO find right factor for value like 0..0.5 or so
    //Would like to use digi pots here
    dc = dc;
}

void ClassicIoVehicle::Task1Ms()
{

}


void ClassicIoVehicle::Task10Ms()
{

}


void ClassicIoVehicle::Task100Ms()
{
    if (!Param::GetInt(Param::T15Stat))
    {
        utils::SpeedoSet(0);//set speedo off
    }
}


bool ClassicIoVehicle::Ready()
{
    return DigIo::t15_digi.Get();
}

bool ClassicIoVehicle::Start()
{
    return Param::GetBool(Param::din_start);
}
