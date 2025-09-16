/*
 * File: include/ac_charger_a.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef AC_CHARGER_A_H
#define AC_CHARGER_A_H

/*  TODO: Add can info for control of Chevy Volt , Opel/Vauxhaul Ampera charger here. */

#include <stdint.h>
#include "my_fp.h"
#include "chargerhw.h"

class AcChargerA: public Chargerhw
{
public:
  bool ControlCharge(bool RunCh, bool ACreq);
};

#endif /* AC_CHARGER_A_H */


