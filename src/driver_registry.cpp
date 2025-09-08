/*
 * File: src/driver_registry.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */

/*
 * Generic driver registry for selecting active drivers by parameter mode.
 */
#include "driver_registry.h"

namespace DriverRegistry {

// Keep small arrays; indices correspond to Param enums.
static Inverter*   inverterCandidates[16]   = {0};
static Vehicle*    vehicleCandidates[16]    = {0};
static Chargerhw*  chargerCandidates[16]    = {0};
static Chargerint* dcfcIfCandidates[16]     = {0};
static Shifter*    shifterCandidates[16]    = {0};
static Heater*     heaterCandidates[16]     = {0};
static BMS*        bmsCandidates[16]        = {0};
static DCDC*       dcdcCandidates[16]       = {0};

template<typename T, size_t N>
static inline void setCandidate(T** arr, int mode, T* ptr)
{
    if (mode >= 0 && mode < (int)N) arr[mode] = ptr;
}

template<typename T, size_t N>
static inline T* getCandidate(T** arr, int mode)
{
    if (mode >= 0 && mode < (int)N && arr[mode]) return arr[mode];
    return (T*)0;
}

void SetInverterCandidate(int mode, Inverter* inv)   { setCandidate(inverterCandidates, mode, inv); }
void SetVehicleCandidate(int mode, Vehicle* veh)     { setCandidate(vehicleCandidates, mode, veh); }
void SetChargerCandidate(int mode, Chargerhw* chg)   { setCandidate(chargerCandidates, mode, chg); }
void SetDcfcInterfaceCandidate(int mode, Chargerint* ci){ setCandidate(dcfcIfCandidates, mode, ci); }
void SetShifterCandidate(int mode, Shifter* sh)      { setCandidate(shifterCandidates, mode, sh); }
void SetHeaterCandidate(int mode, Heater* ht)        { setCandidate(heaterCandidates, mode, ht); }
void SetBmsCandidate(int mode, BMS* bms)             { setCandidate(bmsCandidates, mode, bms); }
void SetDcdcCandidate(int mode, DCDC* dcdc)          { setCandidate(dcdcCandidates, mode, dcdc); }

Inverter*   GetInverter(int mode)    { return getCandidate(inverterCandidates, mode); }
Vehicle*    GetVehicle(int mode)     { return getCandidate(vehicleCandidates, mode); }
Chargerhw*  GetCharger(int mode)     { return getCandidate(chargerCandidates, mode); }
Chargerint* GetDcfcInterface(int mode){ return getCandidate(dcfcIfCandidates, mode); }
Shifter*    GetShifter(int mode)     { return getCandidate(shifterCandidates, mode); }
Heater*     GetHeater(int mode)      { return getCandidate(heaterCandidates, mode); }
BMS*        GetBms(int mode)         { return getCandidate(bmsCandidates, mode); }
DCDC*       GetDcdc(int mode)        { return getCandidate(dcdcCandidates, mode); }

} // namespace DriverRegistry

