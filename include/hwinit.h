/*
 * File: include/hwinit.h
 * Project: STM32 VCU Firmware
 * Author: Chinmoy Bhuyan
 * Copyright (C) 2025 Joulepoint Private Limited
 * Note: This file may include modifications; original notices are preserved.
 */



#ifndef HWINIT_H_INCLUDED
#define HWINIT_H_INCLUDED


#ifdef __cplusplus
extern "C"
{
#endif

void clock_setup(void);
void usart_setup(void);
void usart2_setup(void);
void usart1_setup(void);
void nvic_setup(void);
void rtc_setup(void);
void tim_setup(void);
void tim2_setup(void);
void tim3_setup(void);
void spi2_setup(void);
void spi3_setup(void);

#ifdef __cplusplus
}
#endif

#endif // HWINIT_H_INCLUDED
