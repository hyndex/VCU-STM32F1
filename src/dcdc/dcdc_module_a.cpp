/*
 * File: src/dcdc_module_a.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include "dcdc_module_a.h"

/* This is an interface for The Tesla GEN2 DCDC converter
 * https://openinverter.org/wiki/Tesla_Model_S/X_DC/DC_Converter
 */

 void DcdcModuleA::SetCanInterface(CanHardware* c)
{
   can = c;
   can->RegisterUserMessage(0x210);
}

// Process voltage , current and temperature message from the Model s/x DCDC converter.
void DcdcModuleA::DecodeCAN(int id, uint8_t *data)
{
   if (id == 0x210)
   {
       Param::SetFloat(Param::U12V,data[5]*0.1);//Display 12v system voltage as read from the dcdc
       Param::SetFloat(Param::I12V,data[4]);//Display 12v system current as read from the dcdc
       Param::SetFloat(Param::ChgTemp,(data[2]*0.5)-40);//Display dcdc coolant temp

   }

}

void DcdcModuleA::Task100Ms() {

int opmode = Param::GetInt(Param::opmode);
//static float DCSetVal=Param::GetFloat(Param::DCSetPnt);
//static float Payload;
// Declare data frame array.
uint8_t bytes[8];

   if(opmode==MOD_RUN || opmode==MOD_CHARGE)
   {
   timer500++;
   if(timer500==5)
   {
//   Payload=(byteswap((DCSetVal-9)*146)+0x4)<<8;//prob going to not work :)
   bytes[0]=0x15;//just bodge it to 14.4v for getting running
   bytes[1]=0x07;
   bytes[2]=0x00;
   can->Send(0x3D8, bytes, 3);
   timer500=0;
   }

   }


}

