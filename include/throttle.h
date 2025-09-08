/*
 * File: include/throttle.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef THROTTLE_H
#define THROTTLE_H

#include "my_fp.h"
#include "utils.h"

class Throttle
{
public:
    static bool CheckAndLimitRange(int* potval, int potIdx);
    static float NormalizeThrottle(int potval, int potIdx);
    static float CalcThrottle(int potval, int potIdx, bool brkpedal);
    static float CalcIdleSpeed(int speed);
    static float CalcCruiseSpeed(int speed);
    static bool TemperatureDerate(float tmp, float tmpMax, float& finalSpnt);
    static void UdcLimitCommand(float& finalSpnt, float udc);
    static void IdcLimitCommand(float& finalSpnt, float idc);
    static void SpeedLimitCommand(float& finalSpnt, int speed);
    static float RampThrottle(float finalSpnt);
    static int potmin[2];
    static int potmax[2];
    static float regenRpm;
    static float brknompedal;
    static float regenmax;
    static float regenBrake;
    static float brkcruise;
    static float throtmax;
    static float throtmaxRev;
    static float throtmin;
    static float throtdead;
    static int idleSpeed;
    static int cruiseSpeed;
    static float speedkp;
    static int speedflt;
    static float idleThrotLim;
    static float regenRamp;
    static float throttleRamp;
    static int bmslimhigh;
    static int bmslimlow;
    static int accelmax;
    static int accelflt;
    static float udcmin;
    static float udcmax;
    static float idcmin;
    static float idcmax;
    static int speedLimit;
    static float regenendRpm;
    static float ThrotRpmFilt;

private:
    static int speedFiltered;
    static float potnomFiltered;
    static float brkRamped;
    static float AveragePos(float Pos);
};

#endif // THROTTLE_H
