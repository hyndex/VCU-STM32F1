/*
 * File: include/ac_charger_e.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef AC_CHARGER_E_H
#define AC_CHARGER_E_H

/*  This library supports the various Elcon charger protocol based chargers */

#include <stdint.h>
#include "my_fp.h"
#include "params.h"
#include "chargerhw.h"
#include "my_math.h"

class AcChargerE: public Chargerhw
{

public:
void DecodeCAN(int id, uint32_t data[2]);
void Task200Ms();
bool ControlCharge(bool RunCh, bool ACReq);
void SetCanInterface(CanHardware* c);
void handle18FF50E5(uint32_t data[2]);
/*
static void handle108(uint32_t data[2]);
static bool HVreq;
static void Send100msMessages(bool ChRun, CanHardware* can);
*/
private:

};

#endif /* AC_CHARGER_E_H */
