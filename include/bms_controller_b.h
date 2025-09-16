/*
 * File: include/bms_controller_b.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef BMS_CONTROLLER_B_H
#define BMS_CONTROLLER_B_H
#include "bms.h"

class BmsControllerB: public BMS
{
public:
    void SetCanInterface(CanHardware* can) override;
    void DecodeCAN(int id, uint8_t * data) override;
private:
    bool isMessageCorrupt(uint8_t *data);
};

#endif // BMS_CONTROLLER_B_H
