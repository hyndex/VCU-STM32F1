/*
 * File: src/amperacharger.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include "amperacharger.h"


bool amperaCharger::ControlCharge(bool RunCh, bool ACReq)
{
if(ACReq)
{
bool dummy=RunCh;
dummy=dummy;
}

return false;
}
