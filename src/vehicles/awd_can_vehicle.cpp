/*
 * File: src/awd_can_vehicle.cpp
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/gpio.h>
#include "awd_can_vehicle.h"
#include "anain.h"
#include "my_math.h"

#define IS_IN_RANGE(v, r)           (v < (r + 40) && v > (r - 40))
#define IS_GEARSEL_NONE(v)          v < 50
#define IS_GEARSEL_RESET_BALANCE(v) IS_IN_RANGE(v, 1172)
#define IS_GEARSEL_FRONT_PLUS(v)    IS_IN_RANGE(v, 605)
#define IS_GEARSEL_FRONT_MINUS(v)   IS_IN_RANGE(v, 497)
#define IS_GEARSEL_REVERSE(v)       IS_IN_RANGE(v, 1449)
#define IS_GEARSEL_DRIVE(v)         IS_IN_RANGE(v, 776)
#define IS_GEARSEL_TCTOGGLE(v)      IS_IN_RANGE(v, 422)
#define IS_CC_RESUME(v)             IS_IN_RANGE(v, 1768)
#define IS_CC_SET(v)                IS_IN_RANGE(v, 2725)
#define IS_CC_CANCEL(v)             IS_IN_RANGE(v, 3063)
#define IS_CC_ON(v)                 IS_IN_RANGE(v, 2922)
#define IS_CC_NONE(v)               IS_IN_RANGE(v, 1019)

AwdCanVehicle::AwdCanVehicle()
    : lastGear(NEUTRAL), timerPeriod(10000)
{
}

//We use this as an init function
void AwdCanVehicle::SetCanInterface(CanHardware* c)
{
    Vehicle::SetCanInterface(c);
    utils::SpeedoStart();//kick start speedo timer if selected
    //Connect PWM outputs to timer hardware
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO6 | GPIO7);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO0);
}

void AwdCanVehicle::SetRevCounter(int speed)
{
    //This will also shortly change the value of temp and fuel gauge but we assume
    //they are updated soon after and their inertia keeps them stationary
    //Subaru speedo displays 250 km/h for a timer value of 600 or 166 Hz.
    uint16_t speed_input = speed;
    speed_input = MAX(750, speed_input);//
    speed_input = MIN(7500, speed_input);

    utils::SpeedoSet(speed_input);//Moved pwm control into Utils
}

void AwdCanVehicle::SetTemperatureGauge(float temp)
{
    float dc = temp * 10; //TODO find right factor for value like 0..0.5 or so
    dc *= timerPeriod;
    timer_set_oc_value(TIM3, TIM_OC3, dc);
}

void AwdCanVehicle::SetFuelGauge(float level)
{
    float dc = 0.2f + level * 10; //TODO find right factor for value like 0.5..0.8 or so
    dc *= timerPeriod;
    timer_set_oc_value(TIM3, TIM_OC2, dc);
}

bool AwdCanVehicle::GetGear(gear& gear)
{
    int gearsel = AnaIn::GP_analog2.Get();

    if (IS_GEARSEL_REVERSE(gearsel))
    {
        gear = REVERSE;
    }
    else if (IS_GEARSEL_DRIVE(gearsel))
    {
        gear = DRIVE;
    }
    else
    {
        gear = lastGear;
    }
    lastGear = gear;

    return true;
}

int AwdCanVehicle::GetCruiseState()
{
    static int prevSel = 0;
    int cruisesel = AnaIn::GP_analog1.Get();
    int result = CC_NONE;

    if (IS_CC_RESUME(cruisesel))
    {
        result = CC_RESUME;
    }
    else if (IS_CC_SET(cruisesel))
    {
        result = CC_SET;
    }
    else if (IS_CC_CANCEL(cruisesel))
    {
        result = CC_CANCEL;
    }
    else if (IS_CC_ON(cruisesel) && IS_CC_NONE(prevSel))
    {
        ccOn = !ccOn;
    }

    prevSel = cruisesel;
    result |= ccOn ? CC_ON : CC_NONE;

    return result;
}

float AwdCanVehicle::GetFrontRearBalance()
{
    static int prevSel = 0;
    int sel = AnaIn::GP_analog2.Get();

    if (IS_GEARSEL_RESET_BALANCE(sel))
    {
        frontRearBalance = 50;
    }
    else if (IS_GEARSEL_FRONT_PLUS(sel) && IS_GEARSEL_NONE(prevSel)) //Only trigger when nothing was previously pushed
    {
        frontRearBalance += 16.66f;
        frontRearBalance = MIN(frontRearBalance, 100);
    }
    else if (IS_GEARSEL_FRONT_MINUS(sel) && IS_GEARSEL_NONE(prevSel)) //Only trigger when nothing was previously pushed
    {
        frontRearBalance -= 16.66f;
        frontRearBalance = MAX(frontRearBalance, 0);
    }

    prevSel = sel;

    return frontRearBalance;
}

bool AwdCanVehicle::EnableTractionControl()
{
    static int prevSel = 0;
    int sel = AnaIn::GP_analog2.Get();

    if (IS_GEARSEL_TCTOGGLE(sel) && IS_GEARSEL_NONE(prevSel))
    {
        tcOn = !tcOn;
    }

    prevSel = sel;

    return tcOn;
}
