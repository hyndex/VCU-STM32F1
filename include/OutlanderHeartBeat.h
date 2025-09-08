/*
 * File: include/OutlanderHeartBeat.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef OUTLANDERHEARTBEAT_H
#define OUTLANDERHEARTBEAT_H

#include <stdint.h>
#include "params.h"
#include "canhardware.h"

class OutlanderHeartBeat
{

public:
static void Task100Ms();
static void SetCanInterface(CanHardware* c);
static void SetPullInEVSE(bool pullInEVSE);


protected:

};

#endif // OUTLANDERHEARTBEAT_H
