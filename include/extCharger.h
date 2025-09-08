/*
 * File: include/extCharger.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */




#ifndef EXTCHARGER_H
#define EXTCHARGER_H

/*  This library supports the various opensource tesla charger controllers e.g. PCS , Gen2/3 etc. */

#include <stdint.h>
#include "digio.h"
#include "iomatrix.h"
#include "chargerhw.h"

class extCharger: public Chargerhw
{

public:
bool ControlCharge(bool RunCh, bool ACReq);



private:

};

#endif /* EXTCHARGER_H */

