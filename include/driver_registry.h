/*
 * File: include/driver_registry.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */

/*
 * Generic driver registry for selecting active drivers by parameter mode.
 * Non-invasive: existing modules can register their instances and query
 * the selected one based on Param values.
 */
#ifndef DRIVER_REGISTRY_H
#define DRIVER_REGISTRY_H

#include <cstdint>

// Forward declarations to avoid heavy includes here
class Inverter;
class Vehicle;
class Chargerhw;
class Chargerint;
class Shifter;
class Heater;
class BMS;
class DCDC;

namespace DriverRegistry {

// Registration APIs (call once during startup to register candidates)
void SetInverterCandidate(int mode, Inverter* inv);     // modes from InvModes
void SetVehicleCandidate(int mode, Vehicle* veh);       // modes from vehicles
void SetChargerCandidate(int mode, Chargerhw* chg);     // modes from ChargeModes
void SetDcfcInterfaceCandidate(int mode, Chargerint* ci);// modes from ChargeInterfaces
void SetShifterCandidate(int mode, Shifter* sh);
void SetHeaterCandidate(int mode, Heater* ht);
void SetBmsCandidate(int mode, BMS* bms);
void SetDcdcCandidate(int mode, DCDC* dcdc);

// Selection APIs (retrieve candidate by param mode)
Inverter*    GetInverter(int mode);
Vehicle*     GetVehicle(int mode);
Chargerhw*   GetCharger(int mode);
Chargerint*  GetDcfcInterface(int mode);
Shifter*     GetShifter(int mode);
Heater*      GetHeater(int mode);
BMS*         GetBms(int mode);
DCDC*        GetDcdc(int mode);

}

#endif // DRIVER_REGISTRY_H

