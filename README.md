# ESP32_S2_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP32_S2_TimerInterrupt.svg?)](https://www.ardu-badge.com/ESP32_S2_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP32_S2_TimerInterrupt.svg)](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP32_S2_TimerInterrupt.svg)](http://github.com/khoih-prog/ESP32_S2_TimerInterrupt/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents

* [Important Change from v1.5.0](#Important-Change-from-v150)
* [Why do we need this ESP32_S2_TimerInterrupt library](#why-do-we-need-this-esp32_s2_timerinterrupt-library)
  * [Features](#features)
  * [Why using ISR-based Hardware Timer Interrupt is better](#why-using-isr-based-hardware-timer-interrupt-is-better)
  * [Currently supported Boards](#currently-supported-boards)
  * [Important Notes about ISR](#important-notes-about-isr)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [More useful Information](#more-useful-information)
* [How to use](#how-to-use)
* [Examples](#examples)
  * [  1. Argument_None](examples/Argument_None)
  * [  2. Change_Interval](examples/Change_Interval).
  * [  3. RPM_Measure](examples/RPM_Measure)
  * [  4. SwitchDebounce](examples/SwitchDebounce)
  * [  5. TimerInterruptTest](examples/TimerInterruptTest)
  * [  6. ISR_16_Timers_Array](examples/ISR_16_Timers_Array)
  * [  7. ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)
  * [  8. **multiFileProject**](examples/multiFileProject) **New**
* [Example ISR_16_Timers_Array_Complex](#example-ISR_16_Timers_Array_Complex)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. TimerInterruptTest on ESP32_S2_DEV](#1-timerinterrupttest-on-esp32_s2_dev)
  * [2. Change_Interval on ESP32_S2_DEV](#2-change_interval-on-esp32_s2_dev)
  * [3. Argument_None on ESP32_S2_DEV](#3-argument_none-on-esp32_s2_dev)
  * [4. ISR_16_Timers_Array_Complex on ESP32_S2_DEV](#4-isr_16_timers_array_complex-on-esp32_s2_dev)
  * [5. ISR_16_Timers_Array on ESP32_S2_DEV](#5-isr_16_timers_array-on-esp32_s2_dev)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Change from v1.5.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)

### Why do we need this [ESP32_S2_TimerInterrupt library](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt)

## Features

This library enables you to use Interrupt from Hardware Timers on an ESP32-S2-based board.

The ESP32-S2 timer Interrupt control is different from that of ESP32, at least with the ESP32-S2 core v1.0.6. While the examples of current [ESP32TimerInterrupt library](https://github.com/khoih-prog/ESP32TimerInterrupt) can be compiled OK, they can't run yet. That's why this new [ESP32_S2_TimerInterrupt library](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt) has been created.

---

As **Hardware Timers are rare, and very precious assets** of any board, this library now enables you to use up to **16 ISR-based Timers, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**).

Now with these new **16 ISR-based timers**, the maximum interval is **practically unlimited** (limited only by unsigned long milliseconds) while **the accuracy is nearly perfect** compared to software timers. 

The most important feature is they're ISR-based timers. Therefore, their executions are **not blocked by bad-behaving functions / tasks**. This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_Timer_Complex**](examples/ISR_Timer_Complex) example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.

Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

### Why using ISR-based Hardware Timer Interrupt is better

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware timers, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software timers, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

### Currently supported Boards

1. ESP32_S2-based boards, such as `ESP32S2_DEV`, `ESP32_S2 Saola`, Adafruit QTPY_ESP32S2, ESP32S2 Native USB, UM FeatherS2 Neo, UM TinyS2, UM RMP, microS2, etc.

---

### Important Notes about ISR

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.


---
---

## Prerequisites

1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
2. [`ESP32 Core 2.0.5+`](https://github.com/espressif/arduino-esp32) for ESP32-S2-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/).
3. [`SimpleTimer library`](https://github.com/jfturcot/SimpleTimer) to use with some examples.

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**ESP32_S2_TimerInterrupt**](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP32_S2_TimerInterrupt.svg?)](https://www.ardu-badge.com/ESP32_S2_TimerInterrupt) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**ESP32_S2_TimerInterrupt**](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt) page.
2. Download the latest release `ESP32_S2_TimerInterrupt-main.zip`.
3. Extract the zip file to `ESP32_S2_TimerInterrupt-main` directory 
4. Copy whole `ESP32_S2_TimerInterrupt-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**ESP32_S2_TimerInterrupt** library](https://registry.platformio.org/libraries/khoih-prog/ESP32_S2_TimerInterrupt) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/ESP32_S2_TimerInterrupt/installation). Search for **ESP32_S2_TimerInterrupt** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---


### Note for Platform IO using ESP32 LittleFS

#### Necessary only for esp32 core v1.0.6-

From esp32 core v1.0.6+, [`LittleFS_esp32 v1.0.6`](https://github.com/lorol/LITTLEFS) has been included and this step is not necessary anymore.

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```cpp
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```cpp
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include these `.hpp` or `.h` files

```cpp
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "ESP32_S2_TimerInterrupt.h"     //https://github.com/khoih-prog/ESP32_S2_TimerInterrupt

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "ESP32_S2_ISR_Timer.hpp"         //https://github.com/khoih-prog/ESP32_S2_TimerInterrupt
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "ESP32_S2_ISR_Timer.h"           //https://github.com/khoih-prog/ESP32_S2_TimerInterrupt
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- `ADC1` controls ADC function for pins **GPIO32-GPIO39**
- `ADC2` controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c)

> In `ADC2`, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the `ADC2`, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the `ADC2`, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use `ADC2` for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use `ADC2` with WiFi/BlueTooth (BT/BLE).
- Use `ADC1`, and pins `GPIO32-GPIO39`
- If somehow it's a must to use those pins serviced by `ADC2` (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).

---
---

## More useful Information

The ESP32 has two timer groups, each one with two general purpose hardware timers.  All the timers are based on 64 bits counters and 16 bit prescalers. 

The timer counters can be configured to count up or down and support automatic reload and software reload.

They can also generate alarms when they reach a specific value, defined by the software. The value of the counter can be read by 
the software program.

---

Now with these new `16 ISR-based timers` (while consuming only **1 hardware timer**), the maximum interval is practically unlimited (limited only by unsigned long milliseconds). The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers Therefore, their executions are not blocked by bad-behaving functions / tasks.
This important feature is absolutely necessary for mission-critical tasks. 

The `ISR_Timer_Complex` example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.
Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.
This non-being-blocked important feature is absolutely necessary for mission-critical tasks. 
You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

---
---

## How to use

Before using any Timer, you have to make sure the Timer has not been used by any other purpose.

`Timer0, Timer1, Timer2 and Timer3` are supported for ESP32-S2.

---
---

### Examples: 

 1. [Argument_None](examples/Argument_None)
 2. [RPM_Measure](examples/RPM_Measure)
 3. [SwitchDebounce](examples/SwitchDebounce)
 4. [TimerInterruptTest](examples/TimerInterruptTest)
 5. [**Change_Interval**](examples/Change_Interval).
 6. [**ISR_16_Timers_Array**](examples/ISR_16_Timers_Array)
 7. [**ISR_16_Timers_Array_Complex**](examples/ISR_16_Timers_Array_Complex)
 8. [**multiFileProject**](examples/multiFileProject). **New**

---
---

### Example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)


https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/blob/eb0da8213869167cb2de5a07eb84d261a9fb47fb/examples/ISR_16_Timers_Array_Complex/ISR_16_Timers_Array_Complex.ino#L40-L384

---
---

### Debug Terminal Output Samples

### 1. TimerInterruptTest on ESP32_S2_DEV

The following is the sample terminal output when running example [TimerInterruptTest](examples/TimerInterruptTest) to demonstrate how to start/stop Hardware Timers.

```
Starting TimerInterruptTest on ESP32S2_DEV
ESP32_S2_TimerInterrupt v1.8.0
CPU Frequency = 240 MHz
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 0, TIM_CLOCK_FREQ = 1000000.00
[TISR] TIMER_BASE_CLK = 80000000, TIMER_DIVIDER = 80
[TISR] _timerIndex = 0, _timerGroup = 0
[TISR] Timer freq = 1.00, _count = 0-1000000
[TISR] timer_set_alarm_value = 1000000.00
Starting  ITimer0 OK, millis() = 670
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 1, TIM_CLOCK_FREQ = 1000000.00
[TISR] TIMER_BASE_CLK = 80000000, TIMER_DIVIDER = 80
[TISR] _timerIndex = 1, _timerGroup = 0
[TISR] Timer freq = 0.33, _count = 0-3000000
[TISR] timer_set_alarm_value = 3000000.00
Starting  ITimer1 OK, millis() = 691
Stop ITimer0, millis() = 5001
Start ITimer0, millis() = 10002
Stop ITimer1, millis() = 15001
Stop ITimer0, millis() = 15003
Start ITimer0, millis() = 20004
Stop ITimer0, millis() = 25005
Start ITimer1, millis() = 30002
Start ITimer0, millis() = 30006
```

---


### 2. Change_Interval on ESP32_S2_DEV

The following is the sample terminal output when running example [Change_Interval](examples/Change_Interval) to demonstrate how to change Timer Interval on-the-fly

```
Starting Change_Interval on ESP32S2_DEV
ESP32_S2_TimerInterrupt v1.8.0
CPU Frequency = 240 MHz
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 0, TIM_CLOCK_FREQ = 1000000.00
[TISR] TIMER_BASE_CLK = 80000000, TIMER_DIVIDER = 80
[TISR] _timerIndex = 0, _timerGroup = 0
[TISR] Timer freq = 0.50, _count = 0-2000000
[TISR] timer_set_alarm_value = 2000000.00
Starting  ITimer0 OK, millis() = 677
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 1, TIM_CLOCK_FREQ = 1000000.00
[TISR] TIMER_BASE_CLK = 80000000, TIMER_DIVIDER = 80
[TISR] _timerIndex = 1, _timerGroup = 0
[TISR] Timer freq = 0.20, _count = 0-5000000
[TISR] timer_set_alarm_value = 5000000.00
Starting  ITimer1 OK, millis() = 698
Time = 10001, Timer0Count = 5, Timer1Count = 2
Time = 20002, Timer0Count = 10, Timer1Count = 4
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 0, TIM_CLOCK_FREQ = 1000000.00
[TISR] TIMER_BASE_CLK = 80000000, TIMER_DIVIDER = 80
[TISR] _timerIndex = 0, _timerGroup = 0
[TISR] Timer freq = 0.25, _count = 0-4000000
[TISR] timer_set_alarm_value = 4000000.00
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 1, TIM_CLOCK_FREQ = 1000000.00
[TISR] TIMER_BASE_CLK = 80000000, TIMER_DIVIDER = 80
[TISR] _timerIndex = 1, _timerGroup = 0
[TISR] Timer freq = 0.10, _count = 0-10000000
[TISR] timer_set_alarm_value = 10000000.00
Changing Interval, Timer0 = 4000,  Timer1 = 10000
Time = 30003, Timer0Count = 12, Timer1Count = 4
```

---

### 3. Argument_None on ESP32_S2_DEV

The following is the sample terminal output when running example [Argument_None](examples/Argument_None)

```
Starting Argument_None on ESP32S2_DEV
ESP32_S2_TimerInterrupt v1.8.0
CPU Frequency = 240 MHz
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 0, TIM_CLOCK_FREQ = 1000000.00
[TISR] TIMER_BASE_CLK = 80000000, TIMER_DIVIDER = 80
[TISR] _timerIndex = 0, _timerGroup = 0
[TISR] Timer freq = 1.00, _count = 0-1000000
[TISR] timer_set_alarm_value = 1000000.00
Starting  ITimer0 OK, millis() = 669
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 1, TIM_CLOCK_FREQ = 1000000.00
[TISR] TIMER_BASE_CLK = 80000000, TIMER_DIVIDER = 80
[TISR] _timerIndex = 1, _timerGroup = 0
[TISR] Timer freq = 0.20, _count = 0-5000000
[TISR] timer_set_alarm_value = 5000000.00
Starting  ITimer1 OK, millis() = 690
```

---

### 4. ISR_16_Timers_Array_Complex on ESP32_S2_DEV

The following is the sample terminal output when running example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex) on **ESP32S2_DEV** to demonstrate of ISR Hardware Timer, especially when system is very busy or blocked. The 16 independent ISR timers are programmed to be activated repetitively after certain intervals, is activated exactly after that programmed interval !!!

```
Starting ISR_16_Timers_Array_Complex on ESP32S2_DEV
ESP32_S2_TimerInterrupt v1.8.0
CPU Frequency = 240 MHz
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 1, TIM_CLOCK_FREQ = 1000000.00
[TISR] TIMER_BASE_CLK = 80000000, TIMER_DIVIDER = 80
[TISR] _timerIndex = 1, _timerGroup = 0
[TISR] Timer freq = 100.00, _count = 0-10000
[TISR] timer_set_alarm_value = 10000.00
Starting ITimer OK, millis() = 2569
SimpleTimer : 2, ms : 12584, Dms : 10005
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 0
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 22651, Dms : 10067
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 32718, Dms : 10067
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 42785, Dms : 10067
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 52852, Dms : 10067
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 62919, Dms : 10067
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 55000
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 72986, Dms : 10067
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 55000
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 65000
Timer : 13, programmed : 70000, actual : 70000
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 83053, Dms : 10067
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 55000
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 65000
Timer : 13, programmed : 70000, actual : 70000
Timer : 14, programmed : 75000, actual : 75000
Timer : 15, programmed : 80000, actual : 80000
```

---

### 5. ISR_16_Timers_Array on ESP32_S2_DEV

The following is the sample terminal output when running example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) on **ESP32S2_DEV** to demonstrate of ISR Hardware Timer, especially when system is very busy or blocked. The 16 independent ISR timers are programmed to be activated repetitively after certain intervals, is activated exactly after that programmed interval !!!


```
Starting ISR_16_Timers_Array on ESP32S2_DEV
ESP32_S2_TimerInterrupt v1.8.0
CPU Frequency = 240 MHz
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 1, TIM_CLOCK_FREQ = 1000000.00
[TISR] TIMER_BASE_CLK = 80000000, TIMER_DIVIDER = 80
[TISR] _timerIndex = 1, _timerGroup = 0
[TISR] Timer freq = 1000.00, _count = 0-1000
[TISR] timer_set_alarm_value = 1000.00
Starting ITimer OK, millis() = 2565
simpleTimerDoingSomething2s: Delta programmed ms = 2000, actual = 10015
simpleTimerDoingSomething2s: Delta programmed ms = 2000, actual = 10005
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level (_TIMERINTERRUPT_LOGLEVEL_) from 0 to 4

```cpp
// These define's must be placed at the beginning before #include "ESP32_S2_TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---


### Issues

Submit issues to: [ESP32_S2_TimerInterrupt issues](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/issues)

---

## TO DO

1. Search for bug and improvement.



## DONE

 1. Basic hardware timers for ESP32-S2.
 2. More hardware-initiated software-enabled timers
 3. Longer time interval
 4. Similar features for remaining Arduino boards such as SAMD21, SAMD51, SAM-DUE, nRF52, ESP8266, STM32, etc.
 5. Fix compiler errors due to conflict to some libraries.
 6. Add complex examples.
 7. Fix `multiple-definitions` linker error. Drop `src_cpp` and `src_h` directories
 8. Avoid deprecated functions.
 9. Optimize library code by using `reference-passing` instead of `value-passing`
10. Add support to many more boards, such as
  - ESP32_S2 : ESP32S2 Native USB, UM FeatherS2 Neo, UM TinyS2, UM RMP, microS2, LOLIN_S2_MINI, LOLIN_S2_PICO, ADAFRUIT_FEATHER_ESP32S2, ADAFRUIT_FEATHER_ESP32S2_TFT, ATMegaZero ESP32-S2, Deneyap Mini, FRANZININHO_WIFI, FRANZININHO_WIFI_MSC
11. Use `allman astyle` and add `utils`


---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.


---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/blob/main/LICENSE)

---

## Copyright

Copyright (C) 2021- Khoi Hoang


