/****************************************************************************************************************************
  Argument_None.ino
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

  Version: 1.4.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.3.0   K Hoang      06/05/2019 Initial coding. Sync with ESP32TimerInterrupt v1.3.0
  1.4.0   K.Hoang      01/06/2021 Add complex examples. Fix compiler errors due to conflict to some libraries.
*****************************************************************************************************************************/

/*
   Notes:
   Special design is necessary to share data between interrupt code and the rest of your program.
   Variables usually need to be "volatile" types. Volatile tells the compiler to avoid optimizations that assume
   variable can not spontaneously change. Because your function may change variables while your program is using them,
   the compiler needs this hint. But volatile alone is often not enough.
   When accessing shared variables, usually interrupts must be disabled. Even with volatile,
   if the interrupt changes a multi-byte variable between a sequence of instructions, it can be read incorrectly.
   If your data is multiple variables, such as an array and a count, usually interrupts need to be disabled
   or the entire sequence of your code which accesses the data.
*/

#if !( ARDUINO_ESP32S2_DEV || ARDUINO_FEATHERS2 || ARDUINO_ESP32S2_THING_PLUS || ARDUINO_MICROS2 || \
       ARDUINO_METRO_ESP32S2 || ARDUINO_MAGTAG29_ESP32S2 || ARDUINO_FUNHOUSE_ESP32S2 || \
       ARDUINO_ADAFRUIT_FEATHER_ESP32S2_NOPSRAM )
  #error This code is intended to run on the ESP32-S2 platform! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "TimerInterrupt_Generic.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         1
#define _TIMERINTERRUPT_LOGLEVEL_     4

#include "ESP32_S2_TimerInterrupt.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN       2         // Pin D2 mapped to pin GPIO2/ADC12 of ESP32, control on-board LED
#endif

#define PIN_D1            1         // Pin D1 mapped to pin GPIO1 of ESP32-S2


void IRAM_ATTR TimerHandler0(void * timerNo)
{
  /////////////////////////////////////////////////////////
  // Always call this for ESP32-S2 before processing ISR
  TIMER_ISR_START(timerNo);
  /////////////////////////////////////////////////////////
  
  static bool toggle0 = false;
  static bool started = false;

#if (TIMER_INTERRUPT_DEBUG > 0)
  Serial.print("ITimer0: millis() = "); Serial.println(millis());
#endif

  //timer interrupt toggles pin LED_BUILTIN
  digitalWrite(LED_BUILTIN, toggle0);
  toggle0 = !toggle0;

  /////////////////////////////////////////////////////////
  // Always call this for ESP32-S2 after processing ISR
  TIMER_ISR_END(timerNo);
  /////////////////////////////////////////////////////////
}

void IRAM_ATTR TimerHandler1(void * timerNo)
{
  /////////////////////////////////////////////////////////
  // Always call this for ESP32-S2 before processing ISR
  TIMER_ISR_START(timerNo);
  /////////////////////////////////////////////////////////

  static bool toggle1 = false;
  static bool started = false;
  
#if (TIMER_INTERRUPT_DEBUG > 0)
  Serial.print("ITimer1: millis() = "); Serial.println(millis());
#endif

  //timer interrupt toggles outputPin
  digitalWrite(PIN_D1, toggle1);
  toggle1 = !toggle1;

  /////////////////////////////////////////////////////////
  // Always call this for ESP32-S2 after processing ISR
  TIMER_ISR_END(timerNo);
  /////////////////////////////////////////////////////////
}

#define TIMER0_INTERVAL_MS        1000

#define TIMER1_INTERVAL_MS        5000

// Init ESP32 timer 0 and 1
ESP32Timer ITimer0(0);
ESP32Timer ITimer1(1);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_D1,      OUTPUT);
  
  Serial.begin(115200);
  while (!Serial);

  delay(100);

  Serial.print(F("\nStarting Argument_None on ")); Serial.println(ARDUINO_BOARD);
  Serial.println(ESP32_S2_TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));

  // Using ESP32  => 80 / 160 / 240MHz CPU clock ,
  // For 64-bit timer counter
  // For 16-bit timer prescaler up to 1024

  // Interval in microsecs
  if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0))
  //if (ITimer0.attachInterrupt(1, TimerHandler0))
  {
    Serial.print(F("Starting  ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer0. Select another Timer, freq. or timer"));


  // Interval in microsecs
  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS * 1000, TimerHandler1))
  //if (ITimer1.attachInterrupt(2, TimerHandler1))
  {
    Serial.print(F("Starting  ITimer1 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer1. Select another Timer, freq. or timer"));
}

void loop()
{

}
