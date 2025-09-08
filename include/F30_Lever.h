/*
 * File: include/F30_Lever.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef F30_Lever_h
#define F30_Lever_h

#include "shifter.h"
#define POLYNOMIAL 0x1D /* CRC8_CCITT -- this polynomial needs to match choice on javascript end */
#define WIDTH (8 * sizeof(uint8_t))
#define TOPBIT (1 << (WIDTH - 1))

class F30_Lever: public Shifter
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


#endif // F30_Lever_INCLUDED


