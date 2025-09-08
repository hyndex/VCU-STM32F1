/*
 * File: src/leafinv.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include "leafinv.h"
#include "my_fp.h"
#include "my_math.h"
#include "stm32_can.h"
#include "params.h"
#include "utils.h"
#include "NissLeafMng.h"

/*Info on running Leaf Gen 2 PDM
IDs required :
0x1D4 VCM (10ms)
0x1DB LBC (10ms)
0x1DC LBC (10ms)
0x1F2 VCM (10ms)
0x50B VCM (100ms)
0x55B LBC (100ms)
0x59E LBC (500ms)
0x5BC LBC (100ms)
PDM sends:
0x390 (100ms)
0x393 (100ms)
0x679 on evse plug insert

*/

void LeafINV::SetCanInterface(CanHardware* c)
{
    NissLeafMng::SetCanInterface(c);//set Leaf VCM messages on same bus as Inverter
    can = c;

    can->RegisterUserMessage(0x1DA);//Leaf inv msg
    can->RegisterUserMessage(0x55A);//Leaf inv msg
}

void LeafINV::DecodeCAN(int id, uint32_t data[2])
{
    uint8_t* bytes = (uint8_t*)data;// arrgghhh this converts the two 32bit array into bytes. See comments are useful:)

    if (id == 0x1DA)// THIS MSG CONTAINS INV VOLTAGE, MOTOR SPEED AND ERROR STATE
    {
        voltage = ((bytes[0] << 2) | (bytes[1] >> 6)) * 0.5;//MEASURED VOLTAGE FROM LEAF INVERTER

        if (Param::GetInt(Param::ShuntType) == 0 && voltage < 420)//Only populate if no shunt is used and voltage is under 420
        {
            Param::SetFloat(Param::udc, voltage);
        }

        int16_t parsed_speed = (bytes[4] << 7) | bytes[5]>>1;
        if(parsed_speed> 0x3fff)parsed_speed -=0x7fff;//15 bit signed conversion
        //speed = (parsed_speed == 0x7fff ? 0 : parsed_speed);//LEAF MOTOR RPM
        speed = parsed_speed;
        error = (bytes[6] & 0xb0) != 0x00;//INVERTER ERROR STATE

    }
    else if (id == 0x55A)// THIS MSG CONTAINS INV TEMP AND MOTOR TEMP
    {
        inv_temp = fahrenheit_to_celsius(bytes[2]);//INVERTER TEMP
        motor_temp = fahrenheit_to_celsius(bytes[1]);//MOTOR TEMP
    }
}


void LeafINV::SetTorque(float torquePercent)
{
    final_torque_request = (torquePercent * 2047) / 100.0f;

    if(Param::GetInt(Param::reversemotor) == 1)
    {
        final_torque_request *= -1;//reverse torque request to flip motor rotation
    }

    Param::SetInt(Param::torque,final_torque_request);//post processed final torque value sent to inv to web interface
}

void LeafINV::Task10Ms()//ONLY RAN IN RUNMODE
{

    NissLeafMng::Task10Ms(final_torque_request);//This is only called when in run mode, send torque request with it
}

void LeafINV::Task100Ms() //Always ran
{
    //Inverter calling of 100ms VCM task takes precedences over PDM
    NissLeafMng::Task100Ms();
}


int8_t LeafINV::fahrenheit_to_celsius(uint16_t fahrenheit)
{
    int16_t result = ((int16_t)fahrenheit - 32) * 5 / 9;
    if(result < -128)
        return -128;
    if(result > 127)
        return 127;
    return result;
}
