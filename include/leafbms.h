/*
 * File: include/leafbms.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef LEAFBMS_H
#define LEAFBMS_H
#include "bms.h"

class LeafBMS: public BMS
{
public:
    void SetCanInterface(CanHardware* can) override;
    void DecodeCAN(int id, uint8_t * data) override;
private:
    bool isMessageCorrupt(uint8_t *data);
};

#endif // LEAFBMS_H
