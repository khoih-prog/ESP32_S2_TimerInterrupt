/****************************************************************************************************************************
  ESP32_S2_ISR_Timer.h
  For ESP32_S2 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ESP32_S2_TimerInterrupt
  Licensed under MIT license

  The ESP32-S2 has two timer groups, each one with two general purpose hardware timers. All the timers are based on 64 bits
  counters and 16 bit prescalers. The timer counters can be configured to count up or down and support automatic reload
  and software reload. They can also generate alarms when they reach a specific value, defined by the software. The value
  of the counter can be read by the software program.

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one ESP32-S2 timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.

  Based on SimpleTimer - A timer library for Arduino.
  Author: mromani@ottotecnica.com
  Copyright (c) 2010 OTTOTECNICA Italy

  Based on BlynkTimer.h
  Author: Volodymyr Shymanskyy

  Version: 1.7.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.3.0   K Hoang      06/05/2019 Initial coding. Sync with ESP32TimerInterrupt v1.3.0
  1.4.0   K Hoang      01/06/2021 Add complex examples. Fix compiler errors due to conflict to some libraries.
  1.5.0   K.Hoang      23/01/2022 Avoid deprecated functions. Fix `multiple-definitions` linker error
  1.5.1   K Hoang      16/06/2022 Add support to new Adafruit board QTPY_ESP32S2
  1.6.0   K Hoang      10/08/2022 Suppress errors and warnings for new ESP32 core
  1.7.0   K Hoang      11/08/2022 Suppress warnings and add support for more ESP32_S2 boards
*****************************************************************************************************************************/

#pragma once

#ifndef ISR_TIMER_GENERIC_H
#define ISR_TIMER_GENERIC_H

#include "ESP32_S2_ISR_Timer.hpp"
#include "ESP32_S2_ISR_Timer-Impl.h"

#endif    // ISR_TIMER_GENERIC_H


