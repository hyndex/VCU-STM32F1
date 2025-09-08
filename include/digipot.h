/*
 * File: include/digipot.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef DIGIPOT_H
#define DIGIPOT_H
#include "params.h"
#include "digio.h"
#include <libopencm3/stm32/spi.h>

namespace DigiPot
{
    void SetPot1Step();
    void SetPot2Step();
}
#endif // DIGIPOT_H

