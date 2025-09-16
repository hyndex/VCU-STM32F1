/*
 * File: include/can_shifter_a.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef CAN_SHIFTER_A_H
#define CAN_SHIFTER_A_H

#include "shifter.h"
#define POLYNOMIAL 0x1D /* CRC8_CCITT -- this polynomial needs to match choice on javascript end */
#define WIDTH (8 * sizeof(uint8_t))
#define TOPBIT (1 << (WIDTH - 1))

class CanShifterA: public Shifter
{
public:


   void Task10Ms();
   void Task100Ms();
   void DecodeCAN(int, uint32_t*);
   bool GetGear(Shifter::Sgear& outGear);//if shifter class knows gear return true and set dir
   void SetCanInterface(CanHardware* c);

private:
   void UpdateShifter();
   void sendcan();
   Shifter::Sgear gear;
   void CRC8_begin(void);
   uint8_t get_crc8(uint8_t const message[], int nBytes, uint8_t final, uint8_t skip);
   uint8_t crcTable[256];
};


#endif // CAN_SHIFTER_A_H

