/*
 * File: include/notused.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef notused_h
#define notused_h

/*  Dummy library for whrn no charge interface is used. */

#include <stdint.h>
#include "chargerint.h"

class notused: public Chargerint
{

public:
bool ACRequest(bool RunCh){return RunCh;};

private:

};

#endif /* notused_h */
