/*
 * File: include/cluster_can_vehicle.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



// Generic cluster CAN driver (previously BMW_E39)

#ifndef CLUSTER_CAN_VEHICLE_H
#define CLUSTER_CAN_VEHICLE_H

/*  This module publishes powertrain CAN messages suited for analog gauge
    clusters. */

#include <stdint.h>
#include "vehicle.h"


class ClusterCanVehicle: public Vehicle
{

public:
   void SetCanInterface(CanHardware* c);
   void Task10Ms();
   void Task100Ms();
   void SetRevCounter(int s) { speed = s; }
   void SetTemperatureGauge(float temp);
   void DecodeCAN(int id, uint32_t* data);
   bool Ready();
   bool Start();
   void SetAlternateCluster(bool useAlternateCluster) { alternateCluster = useAlternateCluster; }

private:
   void Msg316();
   void Msg329();
   void Msg545();
   void Msg43F(int8_t gear);
   void Msg43B();

   uint16_t speed;
   bool alternateCluster = false;
   bool AbsCANalive;
   bool SendCAN;
};

#endif /* CLUSTER_CAN_VEHICLE_H */
