/*
 * File: include/NissLeafMng.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef NISSLEAFMNG_H
#define NISSLEAFMNG_H

#include <stdint.h>
#include "params.h"
#include "canhardware.h"
#include "my_fp.h"
#include "my_math.h"
#include "utils.h"

class NissLeafMng
{

public:
static void Task10Ms(int16_t final_torque_request);
static void Task100Ms();
static void SetCanInterface(CanHardware* c);
static void SetPullInEVSE(bool pullInEVSE);
static void nissan_crc(uint8_t *data, uint8_t polynomial);


protected:

};

#endif
