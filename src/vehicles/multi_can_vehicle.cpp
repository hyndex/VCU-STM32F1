/*
 * File: src/multi_can_vehicle.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include "multi_can_vehicle.h"
#include "params.h"

void MultiCanVehicle::Task100Ms()
{
   static int seqCtr = 0;
   static uint8_t ctr = 0;

   const uint8_t seq1[] = { 0x0f, 0x28, 0x7f, 0x28 };
   const uint8_t seq2[] = { 0x1e, 0x10, 0x00, 0x10 };
   const uint8_t seq3[] = { 0x70, 0x56, 0xf0, 0x56 };
   const uint8_t seq4[] = { 0x0c, 0x48, 0xa7, 0x48 };
   const uint8_t seq5[] = { 0x46, 0x90, 0x28, 0x90 };

   uint8_t canData[8] = { (uint8_t)(0x80 | ctr), 0, 0, seq1[seqCtr], seq2[seqCtr], seq3[seqCtr], seq4[seqCtr], seq5[seqCtr] };

   can->Send(0x580, canData,8); //Send on CAN2
   seqCtr = (seqCtr + 1) & 0x3;
   ctr = (ctr + 1) & 0xF;
}

void MultiCanVehicle::Task10Ms()
{
   rpm = (rpm < 750) ? 750 : rpm;
   rpm = (rpm > 7000) ? 7000 : rpm;

   uint8_t byte3 = ((rpm * 4) >> 8) & 0xFF;
   uint8_t byte4 = (rpm * 4) & 0xFF;
   uint8_t canData[8] = { 0, 0, 0, byte3, byte4, 0, 0, 0 };
   can->Send(0x280, canData, 8); //Send on CAN2

   //contains temperature, traction control light was on without the message, content doesnt
   //seem to matter.
   canData[3] = 0;
   canData[4] = 0;
   can->Send(0x288, canData, 8); //Send on CAN2
}

bool MultiCanVehicle::Start()
{
   //TODO the start signal can be found on CAN bus, use it!
   //return Param::GetBool(Param::din_start);
   return Param::GetBool(Param::din_start);
}

bool MultiCanVehicle::Ready()
{
   return DigIo::t15_digi.Get();
}
