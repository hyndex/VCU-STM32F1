/*
 * File: src/CanShifterD.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include "can_shifter_d.h"

static uint8_t shiftPos=0xe1; //contains byte to display gear position on dash.default to park
static uint8_t gear_BA=0x03; //set to park as initial condition
static int8_t opmodeSh = 0;

void CanShifterD::SetCanInterface(CanHardware* c)
{
    can = c;
    can->RegisterUserMessage(0x192);//GWS status msg. Contains info on buttons pressed and lever location.
}

void CanShifterD::DecodeCAN(int id, uint32_t* data)
{
    if (id == 0x192)
    {
        uint32_t GLeaver = data[0] & 0x00ffffff;  //unsigned int to contain result of message 0x192. Gear selector lever position

        switch (GLeaver)
        {
        case 0x80506a:  //park button pressed
            this->gear = PARK;
            gear_BA = 0x03;
            shiftPos = 0xe1;
            break;
        case 0x80042d: //R+ position
            this->gear = REVERSE;
            gear_BA = 0x02;
            shiftPos = 0xd2;
            break;
        case 0x800374:  //D+ pressed
            this->gear = DRIVE;
            gear_BA = 0x08;
            shiftPos = 0x78;
            break;
        case 0x80006a:  //not pressed
        case 0x800147:  //R position
        case 0x800259:  //D pressed
        case 0x81006a:  //Left Back button pressed
        case 0x82006a:  //Left Front button pressed
        case 0x84006a:  //right Back button pressed
        case 0x88006a:  //right Front button pressed
        case 0xa0006a:  //  S-M-D button pressed
            break;
        }
    }
}


void CanShifterD::Task10Ms()
{

}


void CanShifterD::Task100Ms()
{
    opmodeSh = Param::GetInt(Param::opmode);
    if(opmodeSh==MOD_OFF) this->gear = NEUTRAL;
}

bool CanShifterD::GetGear(Shifter::Sgear& outGear)
{
    outGear = gear;    //send the shifter pos
    return true; //Let caller know we set a valid gear
}
