/*
 * File: include/outlanderCharger.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef OUTLANDERCHARGER_H
#define OUTLANDERCHARGER_H

/* Control of the Mitsubishi Outlander PHEV on board charger (OBC) and DCDC Converter. */

#include <stdint.h>
#include "my_fp.h"
#include "my_math.h"
#include "hwinit.h"
#include "params.h"
#include "chargerhw.h"
#include <libopencm3/stm32/timer.h>

class outlanderCharger: public Chargerhw
{

public:
void DecodeCAN(int id, uint32_t data[2]);
void Task100Ms();
bool ControlCharge(bool RunCh, bool ACReq);
void SetCanInterface(CanHardware* c);


private:
int opmode;
uint16_t setVolts , actVolts , termAmps;
int16_t actAmps;
uint8_t currentRamp;
bool clearToStart=false , shutDownReq=false, pwmON=false;
static uint8_t chgStatus , evseDuty;
static float dcBusV , temp_1 , temp_2 , ACVolts , DCAmps , ACAmps;
static float LV_Volts , LV_Amps;
static uint16_t batteryVolts;

static void handle377(uint32_t data[2]);
static void handle389(uint32_t data[2]);
static void handle38A(uint32_t data[2]);
};

#endif // OUTLANDERCHARGER_H
