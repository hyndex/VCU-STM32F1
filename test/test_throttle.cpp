/*
 * File: test/test_throttle.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include "my_fp.h"
#include "my_math.h"
#include "test_list.h"
#include "throttle.h"

using namespace std;

void Param::Change(Param::PARAM_NUM p)
{
   // Dummy function - we ignore parameter changes in these tests
}

// Include a dummy error list to allow the tests to link. It is unused.
const char* errorListString = "";

static void TestSetup()
{
   //percentage of deadzone
   Throttle::throtdead = 5;
   Throttle::potmin[0] = 100;
   Throttle::potmax[0] = 4000;
   Throttle::throtmax = 100;
   Param::SetInt(Param::dir, 1);
}

// TEMPERATURE DERATING
static void TestThrottleTemperateOverMaxThrottleTo0() {
   float temp = 60;
   float tempMax = 50;
   float finalSpnt = 100;
   ASSERT(Throttle::TemperatureDerate(temp, tempMax, finalSpnt) && finalSpnt == 0);
}

static void TestThrottleTemperateInDerateZoneThrottleTo50Percent() {
   float temp = 61;
   float tempMax = 60;
   float finalSpnt = 100;
   ASSERT(Throttle::TemperatureDerate(temp, tempMax, finalSpnt) && finalSpnt == 50);
}

static void TestThrottleUnderTemperateNoDeRate() {
   float temp = 30;
   float tempMax = 60;
   float finalSpnt = 100;
   ASSERT(Throttle::TemperatureDerate(temp, tempMax, finalSpnt) == false && finalSpnt == 100);
}

static void TestThrottleTemperateInDerateZoneThrottleButThrottleUnderLimit() {
   float temp = 61;
   float tempMax = 60;
   float finalSpnt = 49;
   ASSERT(Throttle::TemperatureDerate(temp, tempMax, finalSpnt) && finalSpnt == 49);
}

// CALC THROTTLE
static void TestCalcThrottleIs0WhenThrottleAndBrakePressed() {


   ASSERT(Throttle::CalcThrottle(3000, 0, true) == 0);
}

static void TestCalcThrottleIs0WhenNoThrottleAndBrakePressed() {

   ASSERT(Throttle::CalcThrottle(0, 0, true) == 0);
}

static void TestCalcThrottleIs0WhenInDeadZone() {
   //deadzone is first 5% of travel between 100 and 4000
   ASSERT(Throttle::CalcThrottle(295, 0, false) == 0);
}

static void TestCalcThrottleIsAbove0WhenJustOutOfDeadZone() {
   //deadzone is first 5% of travel between 100 and 4000
   ASSERT(Throttle::CalcThrottle(496, 0, false) > 0);
}

static void TestCalcThrottleIs100WhenMax() {
   //deadzone is first 5% of travel between 100 and 4000
   //cheat a little and force it to round 99.9999999
   int throtVal = Throttle::CalcThrottle(4000, 0, false);
   ASSERT(throtVal ==  100);
}

static void TestCalcThrottleIs100WhenOverMax() {
   //deadzone is first 5% of travel between 100 and 4000
   int throtVal = Throttle::CalcThrottle(4001, 0, false);
   ASSERT(throtVal ==  100);
}

static void TestNormalizeThrottleHandlesInvertedCalibration() {
   // Inverted calibration: potmin > potmax
   Throttle::potmin[0] = 4000;
   Throttle::potmax[0] = 100;

   // At physical low end, normalized should be ~0
   float n0 = Throttle::NormalizeThrottle(100, 0);
   ASSERT(n0 == 0);

   // At physical high end, normalized should be ~100
   float n1 = Throttle::NormalizeThrottle(4000, 0);
   ASSERT(n1 == 100);

   // Mid point
   float mid = Throttle::NormalizeThrottle(2050, 0);
   ASSERT(mid > 45 && mid < 55);

   // Restore normal calibration for subsequent tests
   Throttle::potmin[0] = 100;
   Throttle::potmax[0] = 4000;
}

static void TestUdcLimitDeratesPositiveTorqueWhenBelowMin() {
   // Setup
   Throttle::udcmin = 400; // not used directly; function reads Param values
   Param::SetFloat(Param::udcmin, 400);
   Param::SetFloat(Param::udclim, 520);
   float sp = 100; // request positive torque
   Throttle::UdcLimitCommand(sp, /*udc=*/380);
   ASSERT(sp == 0);
}

static void TestIdcLimitDeratesNegativeTorqueWhenBelowMin() {
   // Negative torque request limited by idcmin
   Param::SetFloat(Param::idcmax, 5000);
   Param::SetFloat(Param::idcmin, -50);
   Param::SetFloat(Param::idcKp, 1.0);
   float sp = -80; // request strong regen
   // idcFiltered starts at 0 in function scope; using idc=0 keeps IDCres = idcmin
   Throttle::IdcLimitCommand(sp, /*idc=*/0);
   ASSERT(sp == -50);
}

static void TestSpeedLimitReducesPositiveTorque() {
   // With speed well above limit, positive torque should be limited to 0
   Throttle::speedLimit = 1000; // limit
   float sp = 80;
   // Advance filter until it clamps
   for (int i = 0; i < 40; i++) {
      Throttle::SpeedLimitCommand(sp, /*speed*/ 6000);
   }
   ASSERT(sp == 0);
}

static void TestUdcKpAffectsTorqueLimit() {
   // With higher UDC Kp, torque ceiling should be higher for same error
   Param::SetFloat(Param::udcmin, 400);
   Param::SetFloat(Param::udclim, 520);
   // Error = udc - udcmin = 10V
   float sp = 100;
   Param::SetFloat(Param::udcKp, 1.0);
   Throttle::UdcLimitCommand(sp, /*udc*/410);
   ASSERT(sp == 10);

   sp = 100;
   Param::SetFloat(Param::udcKp, 3.5);
   Throttle::UdcLimitCommand(sp, /*udc*/410);
   ASSERT(sp == 35);
}


void ThrottleTest::RunTest()
{
   TestSetup();
   TestThrottleTemperateOverMaxThrottleTo0();
   TestThrottleTemperateInDerateZoneThrottleTo50Percent();
   TestThrottleUnderTemperateNoDeRate();
   TestThrottleTemperateInDerateZoneThrottleButThrottleUnderLimit();
   TestCalcThrottleIs0WhenThrottleAndBrakePressed();
   TestCalcThrottleIs0WhenNoThrottleAndBrakePressed();
   TestCalcThrottleIs0WhenInDeadZone();
   TestCalcThrottleIsAbove0WhenJustOutOfDeadZone();
   TestCalcThrottleIs100WhenMax();
   TestCalcThrottleIs100WhenOverMax();
   TestNormalizeThrottleHandlesInvertedCalibration();
   TestUdcLimitDeratesPositiveTorqueWhenBelowMin();
   TestIdcLimitDeratesNegativeTorqueWhenBelowMin();
   TestSpeedLimitReducesPositiveTorque();
   TestUdcKpAffectsTorqueLimit();
}
