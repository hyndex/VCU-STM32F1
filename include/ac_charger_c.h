/*
 * File: include/ac_charger_c.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef AC_CHARGER_C_H
#define AC_CHARGER_C_H

/*  This library supports the various opensource tesla charger controllers e.g. PCS , Gen2/3 etc. */

#include "chargerhw.h"
#include "canhardware.h"
#include <stdint.h>

class AcChargerC: public Chargerhw
{
public:
    void DecodeCAN(int id, uint32_t data[2]) override;
    void Task100Ms() override;
    bool ControlCharge(bool RunCh, bool ACReq) override;
    void SetCanInterface(CanHardware* c) override;
};

#endif /* AC_CHARGER_C_H */
