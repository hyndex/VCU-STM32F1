/*
 * File: src/outlanderinverter.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include "outlanderinverter.h"
#include "my_math.h"
#include "params.h"

OutlanderInverter::OutlanderInverter()
{
   //ctor
}

void OutlanderInverter::SetCanInterface(CanHardware* c)
{
   can = c;

   can->RegisterUserMessage(0x289);//Outlander Inv Msg
   can->RegisterUserMessage(0x299);//Outlander Inv Msg
   can->RegisterUserMessage(0x733);//Outlander Inv Msg
}

void OutlanderInverter::DecodeCAN(int id, uint32_t data[2])
{
   switch (id)
   {
   case 0x289:
      speed = (data[0] >> 16) - 20000;
      voltage = data[1] & 0xFFFF;
      break;
   case 0x299:
      inv_temp = MAX((data[1] & 0xFF), ((data[0] >> 8) & 0xFF)) - 40;
      break;
   case 0x733:
      motor_temp = MAX((data[0] & 0xFF), ((data[0] >> 16) & 0xFF)) - 40;
      break;
   }
}

void OutlanderInverter::SetTorque(float torquePercent)
{
   final_torque_request = (torquePercent * 2000) / 100.0f + 10000;

   Param::SetInt(Param::torque,final_torque_request);//post processed final torque value sent to inv to web interface
}

void OutlanderInverter::Task10Ms()
{
   run10ms++;

   //Run every 50 ms
   if (run10ms == 5)
   {
      uint32_t data[2];
      run10ms = 0;

      data[0] = final_torque_request << 16;
      data[1] = 0;

      can->Send(0x287, data, 8);
   }
}

void OutlanderInverter::Task100Ms()
{
   uint32_t data[2];

   data[0] = 48;

   can->Send(0x371, data, 8);

   data[0] = 0x39100000;
   data[1] = 0x100CFE8F;

   can->Send(0x285, data, 8);

   data[0] = 0x3D000000;
   data[1] = 0x00210000;

   can->Send(0x286, data, 8);
}
