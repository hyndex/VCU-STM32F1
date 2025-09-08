/*
 * File: src/OutlanderHeartBeat.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include <OutlanderHeartBeat.h>

/* Control of the Mitsubishi Outlander PHEV on board charger (OBC) and DCDC Converter. */

bool EnableEVSE = false;
bool CanConfigure = false;
bool DualCan = false;

CanHardware* can1;
CanHardware* can2;

void OutlanderHeartBeat::SetCanInterface(CanHardware* c)
{
    if(CanConfigure == false)
    {
        can1 = c;
        CanConfigure = true;
    }
    else if(can1 != c)
    {
        can2 = c;
        DualCan = true;
    }
}

void OutlanderHeartBeat::Task100Ms()
{
    int opmode = Param::GetInt(Param::opmode);

    uint8_t bytes[8];
    bytes[0] = 0x00;
    bytes[1] = 0x00;
    bytes[2] = 0x00;
    bytes[3] = 0x00;
    bytes[4] = 0x00;
    bytes[5] = 0x00;
    bytes[6] = 0x00;
    bytes[7] = 0x00;

    if (MOD_CHARGE == opmode)
    {
        if (EnableEVSE)
        {
            bytes[2] = 0xB6;//oxb6 in byte 3 enables charger
        }
    }
    else if (MOD_RUN == opmode)
    {

        bytes[2] = 0x14;
        bytes[3] = 0x39;
        bytes[4] = 0x8F;
        bytes[5] = 0xFE;
        bytes[6] = 0xC;
        bytes[7] = 0x10;
    }

    if (MOD_CHARGE == opmode || MOD_RUN == opmode)
    {
        can1->Send(0x285, (uint32_t*)bytes, 8);

        if(DualCan)
        {
            can2->Send(0x285, (uint32_t*)bytes, 8);
        }
    }
}

void OutlanderHeartBeat::SetPullInEVSE(bool pullInEVSE)
{
    EnableEVSE = pullInEVSE;
}
