/*
 * File: src/ac_charger_a.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include "ac_charger_a.h"


bool AcChargerA::ControlCharge(bool RunCh, bool ACReq)
{
if(ACReq)
{
bool dummy=RunCh;
dummy=dummy;
}

return false;
}
