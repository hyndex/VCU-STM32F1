/*
 * File: src/OutlanderCanHeater.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include <OutlanderCanHeater.h>
#include "OutlanderHeartBeat.h"

void OutlanderCanHeater::SetPower(uint16_t power, bool HeatReq)
{
    shouldHeat = HeatReq;
    power = power;//mask warning
}

void OutlanderCanHeater::SetCanInterface(CanHardware* c)
{
    OutlanderHeartBeat::SetCanInterface(c);//set Outlander Heartbeat on same CAN

    can = c;
    can->RegisterUserMessage(0x398);
}

void OutlanderCanHeater::Task100Ms()
{
    if (shouldHeat)
    {
        uint8_t bytes[8];

        bytes[0] = 0x03;
        bytes[1] = 0x50;
        bytes[2] = 0x00;
        bytes[3] = 0x4D;
        bytes[4] = 0x00;
        bytes[5] = 0x00;
        bytes[6] = 0x00;
        bytes[7] = 0x00;

        currentTemperature = Param::GetInt(Param::tmpheater);
        if (currentTemperature < desiredTemperature - 5) {
            bytes[2] = 0xA2;
            Param::SetInt(Param::powerheater, 3000);
        } else if (currentTemperature < desiredTemperature) {
            bytes[2] = 0x32;
            Param::SetInt(Param::powerheater, 1500);
        } else {
            Param::SetInt(Param::powerheater, 0);
        }


        can->Send(0x188, (uint32_t*)bytes, 8);
    }
}

void OutlanderCanHeater::SetTargetTemperature(float temp)
{
    desiredTemperature = temp;
}

void OutlanderCanHeater::DecodeCAN(int id, uint32_t data[2])
{
    switch (id)
    {
    case 0x398:
        OutlanderCanHeater::handle398(data);
        break;
    }
}

void OutlanderCanHeater::handle398(uint32_t data[2])
{
    uint8_t* bytes = (uint8_t*)data;// arrgghhh this converts the two 32bit array into bytes. See comments are useful:)
    unsigned int temp1 = bytes[3] - 40;
    unsigned int temp2 = bytes[4] - 40;
    if (temp2 > temp1)
    {
        Param::SetInt(Param::tmpheater, temp2);
    }
    else
    {
        Param::SetInt(Param::tmpheater, temp1);
    }

    if (bytes[6] == 0x09)
    {
        Param::SetInt(Param::udcheater, 0);
    }
    else
    {
        Param::SetInt(Param::udcheater, Param::GetInt(Param::udc));
    }

}
