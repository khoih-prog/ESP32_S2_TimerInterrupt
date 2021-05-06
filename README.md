# ESP32_S2_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP32_S2_TimerInterrupt.svg?)](https://www.ardu-badge.com/ESP32_S2_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP32_S2_TimerInterrupt.svg)](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP32_S2_TimerInterrupt.svg)](http://github.com/khoih-prog/ESP32_S2_TimerInterrupt/issues)

---
---

## Table of Contents

* [Why do we need this ESP32_S2_TimerInterrupt library](#why-do-we-need-this-esp32_s2_timerinterrupt-library)
  * [Features](#features)
  * [Why using ISR-based Hardware Timer Interrupt is better](#why-using-isr-based-hardware-timer-interrupt-is-better)
  * [Currently supported Boards](#currently-supported-boards)
  * [Important Notes about ISR](#important-notes-about-isr)
* [Changelog](#changelog)
  * [Releases v1.3.0](#releases-v130)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [HOWTO Install esp32 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) and ESP32-C3 boards into Arduino IDE](#howto-install-esp32-core-for-esp32-s2-saola-ai-thinker-esp-12k-and-esp32-c3-boards-into-arduino-ide)
  * [1. Save the original esp32 core](#1-save-the-original-esp32-core)
  * [2. Install esp32 core v1.0.6](#2-install-esp32-core-v106)
    * [2.1 Install esp32 core](#21-install-esp32-core)
    * [2.2 Download latest zip with esp32-s2 support](#22-download-latest-zip-with-esp32-s2-support)
    * [2.3 Unzip](#23-unzip)
    * [2.3 Update esp32 core directories](#24-update-esp32-core-directories)
  * [3. Download tools for ESP32-S2](#3-download-tools-for-esp32-s2) 
    * [3.1 Download Toolchain for Xtensa (ESP32-S2) based on GCC](#31-download-toolchain-for-xtensa-esp32-s2-based-on-gcc)
    * [3.2 Download esptool](#32-download-esptool)
    * [3.3 Unzip](#33-unzip)
  * [4. Update tools](#4-update-tools)
    * [4.1 Update Toolchain](#41-update-toolchain)
    * [4.2 Update esptool](#42-update-esptool)
  * [5. Download tools for ESP32-C3](#5-download-tools-for-esp32-c3)
  * [6. esp32-s2 WebServer Library Patch](#6-esp32-s2-webserver-library-patch)
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
  * [  2. **Change_Interval**](examples/Change_Interval). New.
  * [  3. ISR_RPM_Measure](examples/ISR_RPM_Measure)
  * [  4. ISR_Switch](examples/ISR_Switch)
  * [  5. ISR_Timer_Complex](examples/ISR_Timer_Complex)
  * [  6. ISR_Timer_Switch](examples/ISR_Timer_Switch)
  * [  7. ISR_Timer_4_Switches](examples/ISR_Timer_4_Switches)
  * [  8. ISR_Timer_Switches](examples/ISR_Timer_Switches)
  * [  9. RPM_Measure](examples/RPM_Measure)
  * [ 10. SwitchDebounce](examples/SwitchDebounce)
  * [ 11. TimerInterruptTest](examples/TimerInterruptTest)
* [Example ISR_Timer_Complex](#example-isr_timer_complex)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ISR_Timer_Complex on ESP32_S2_DEV](#1-isr_timer_complex-on-esp32_s2_dev)
  * [2. TimerInterruptTest on ESP32_S2_DEV](#2-timerinterrupttest-on-esp32_s2_dev)
  * [3. Change_Interval on ESP32_S2_DEV](#3-change_interval-on-esp32_s2_dev)
  * [4. Argument_None on ESP32_S2_DEV](#4-argument_none-on-esp32_s2_dev)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [ESP32_S2_TimerInterrupt library](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt)

## Features

This library enables you to use Interrupt from Hardware Timers on an ESP32-S2-based board.

The ESP32-S2 timer Interrupt control is different from that of ESP32, at least with the ESP32-S2 core v1.0.6. While the examples of current [ESP32TimerInterrupt library](https://github.com/khoih-prog/ESP32TimerInterrupt) can be compiled OK, they can't run yet. That's why this new [ESP32_S2_TimerInterrupt library](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt) has been created.

---

As **Hardware Timers are rare, and very precious assets** of any board, this library now enables you to use up to **16 ISR-based Timers, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**).

Now with these new **16 ISR-based timers**, the maximum interval is **practically unlimited** (limited only by unsigned long miliseconds) while **the accuracy is nearly perfect** compared to software timers. 

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

1. ESP32-S2-based boards, such as ESP32_S2_DEV, ESP32_S2 Saola, etc

---

### Important Notes about ISR

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.


---
---

## Changelog

### Releases v1.3.0

1. Initial coding to support ESP32-S2
2. Sync with [ESP32TimerInterrupt library v1.3.0](https://github.com/khoih-prog/ESP32TimerInterrupt)


---
---

## Prerequisites

1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
2. [`ESP32-S2/C3 Core 1.0.6+`](https://github.com/espressif/arduino-esp32) for ESP32-S2/C3-based boards. Must follow [HOWTO Install esp32 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) and ESP32-C3 boards into Arduino IDE](#howto-install-esp32-core-for-esp32-s2-saola-ai-thinker-esp-12k-and-esp32-c3-boards-into-arduino-ide).

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**ESP32_S2_TimerInterrupt**](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP32_S2_TimerInterrupt.svg?)](https://www.ardu-badge.com/ESP32_S2_TimerInterrupt) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**ESP32_S2_TimerInterrupt**](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt) page.
2. Download the latest release `ESP32_S2_TimerInterrupt-master.zip`.
3. Extract the zip file to `ESP32_S2_TimerInterrupt-master` directory 
4. Copy whole `ESP32_S2_TimerInterrupt-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**ESP32_S2_TimerInterrupt** library](https://platformio.org/lib/show/xxxxx/ESP32_S2_TimerInterrupt) by using [Library Manager](https://platformio.org/lib/show/xxxxx/ESP32_S2_TimerInterrupt/installation). Search for **ESP32_S2_TimerInterrupt** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

## HOWTO Install esp32 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) and ESP32-C3 boards into Arduino IDE


These are instructions demonstrating the steps to install esp32-s2/c3 core on Ubuntu machines. For Windows or other OS'es, just follow the the similar principles and steps.

* Windows 10, follows these steps in [Steps to install Arduino ESP32 support on Windows](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/windows.md) 

* Mac OS, follows these steps in [Installation instructions for Mac OS](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/mac.md)

* Fedora, follows these steps in [Installation instructions for Fedora](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/fedora.md)

* openSUSE, follows these steps in [Installation instructions for openSUSE](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/opensuse.md)

* You can also try to add [package_esp32_dev_index.json](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json) into Arduino IDE `File - Preferences - Additional Boards Manager URLs` 


```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
```

and have Board Manager auto-install the **development** esp32 core. For example : esp32 core `v2.0.0-alpha1`


---

If you're already successful in testing the core, after installing by using the above procedures, you don't need to follows the hereafter manual steps.

---

Assuming you already installed Arduino IDE ESP32 core and the installed directory is

`/home/your_account/.arduino15/packages/esp32`


### 1. Save the original esp32 core

First, copy the whole original esp32 core to another safe place. Then delete all the sub-directories of

`/home/your_account/.arduino15/packages/esp32/hardware/esp32/1.0.4`

---


### 2. Install esp32 core v1.0.6

#### 2.1 Install esp32 core

Just use Arduino IDE Board Manager to install [ESP32 Arduino Release 1.0.6 based on ESP-IDF v3.3.5](https://github.com/espressif/arduino-esp32/releases/tag/1.0.6). This official v1.06 core doesn't have esp32-s2/s3 support. You have to download and use the latest master branch.


#### 2.2 Download latest zip with esp32-s2 support

As of **April 16th 2021**, the **esp32-s2/c3** board support has been included in master branch of esp32 core. Download [**esp32 core, master branch**](https://github.com/espressif/arduino-esp32) in the zip format.

#### 2.3 Unzip

<p align="center">
    <img src="https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/blob/main/pics/esp32_s2_Core_Unzipped.png">
</p>

#### 2.4 Update esp32 core directories

Copy all subdirectories of esp32 core into `/home/your_account/.arduino15/packages/esp32/hardware/esp32/1.0.6`


---

### 3 Download tools for ESP32-S2


#### 3.1 Download Toolchain for Xtensa (ESP32-S2) based on GCC

Download [**esp32-s2 Toolchain**](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/api-guides/tools/idf-tools.html#xtensa-esp32s2-elf) corresponding to your environment (linux-amd64, win64, etc.).

For example `xtensa-esp32s2-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz`, then un-archive.


<p align="center">
    <img src="https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/blob/main/pics/esp32_s2_Toolchain.png">
</p>

#### 3.2 Download esptool


Download [esptool](https://github.com/espressif/esptool/releases) int the `zip` format:

`esptool-3.0.zip`

#### 3.3 Unzip

<p align="center">
    <img src="https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/blob/main/pics/esp32_s2_esptool.png">
</p>

---

### 4. Update tools

#### 4.1 Update Toolchain

Copy whole `xtensa-esp32s2-elf` directory into `/home/your_account/.arduino15/packages/esp32/hardware/esp32/1.0.6/tools`


#### 4.2 Update esptool

Rename `esptool-3.0` directory to `esptool`


Copy whole `esptool` directory into `/home/your_account/.arduino15/packages/esp32/hardware/esp32/1.0.6/tools`


<p align="center">
    <img src="https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/blob/main/pics/esp32_s2_tools.png">
</p>


### 5 Download tools for ESP32-C3

Download [**esp32-c3 Toolchain**](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/api-guides/tools/idf-tools.html#riscv32-esp-elf) corresponding to your environment (linux-amd64, win64, etc.).

For example`riscv32-esp-elf-gcc8_4_0-crosstool-ng-1.24.0-123-g64eb9ff-linux-amd64.tar.gz`, then un-archive.

Then using the similar steps as in

* [3. Download tools for ESP32-S2](#3-download-tools-for-esp32-s2) 
  * [3.1 Download Toolchain for Xtensa (ESP32-S2) based on GCC](#31-download-toolchain-for-xtensa-esp32-s2-based-on-gcc)
  * [3.2 Download esptool](#32-download-esptool)
  * [3.3 Unzip](#33-unzip)
* [4. Update tools](#4-update-tools)
  * [4.1 Update Toolchain](#41-update-toolchain)
  * [4.2 Update esptool](#42-update-esptool)

then copy whole `riscv32-esp-elf` directory into `/home/your_account/.arduino15/packages/esp32/hardware/esp32/1.0.6/tools`


### 6. esp32-s2 WebServer Library Patch

#### Necessary only for esp32 core v1.0.6-

If you haven't installed a new version with [WebServer.handleClient delay PR #4350](https://github.com/espressif/arduino-esp32/pull/4350) or haven't applied the above mentioned PR, you have to use the following patch.


**To be able to run Config Portal on ESP32-S2 boards**, you have to copy the files in [esp32-s2 WebServer Patch](esp32s2_WebServer_Patch/) directory into esp32-s2 WebServer library directory (~/.arduino15/packages/esp32/hardware/esp32/1.0.4/libraries/WebServer).

Supposing the esp32-s2 version is 1.0.4, these files `WebServer.h/cpp` must be copied into the directory to replace:

- `~/.arduino15/packages/esp32/hardware/esp32/1.0.4/libraries/WebServer/src/WebServer.h`
- `~/.arduino15/packages/esp32/hardware/esp32/1.0.4/libraries/WebServer/src/WebServer.cpp`


---

That's it. You're now ready to compile and test for **ESP32-S2 and ESP32-C3** now

---
---

### Note for Platform IO using ESP32 LittleFS

#### Necessary only for esp32 core v1.0.6-

From esp32 core v1.0.6+, [`LittleFS_esp32 v1.0.6`](https://github.com/lorol/LITTLEFS) has been included and this step is not necessary anymore.

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using **xyz-Impl.h instead of standard xyz.cpp**, possibly creates certain `Multiple Definitions` Linker error in certain use cases. Although it's simple to just modify several lines of code, either in the library or in the application, the library is adding 2 more source directories

1. **scr_h** for new h-only files
2. **src_cpp** for standard h/cpp files

besides the standard **src** directory.

To use the **old standard cpp** way, locate this library' directory, then just 

1. **Delete the all the files in src directory.**
2. **Copy all the files in src_cpp directory into src.**
3. Close then reopen the application code in Arduino IDE, etc. to recompile from scratch.

To re-use the **new h-only** way, just 

1. **Delete the all the files in src directory.**
2. **Copy the files in src_h directory into src.**
3. Close then reopen the application code in Arduino IDE, etc. to recompile from scratch.

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).

---
---

## More useful Information

The ESP32 has two timer groups, each one with two general purpose hardware timers.  All the timers are based on 64 bits counters and 16 bit prescalers. 

The timer counters can be configured to count up or down and support automatic reload and software reload.

They can also generate alarms when they reach a specific value, defined by the software. The value of the counter can be read by 
the software program.

---

Now with these new `16 ISR-based timers` (while consuming only **1 hardware timer**), the maximum interval is practically unlimited (limited only by unsigned long miliseconds). The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers Therefore, their executions are not blocked by bad-behaving functions / tasks.
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
 2. [ISR_RPM_Measure](examples/ISR_RPM_Measure)
 3. [ISR_Switch](examples/ISR_Switch) 
 4. [ISR_Timer_4_Switches](examples/ISR_Timer_4_Switches) 
 5. [ISR_Timer_Complex](examples/ISR_Timer_Complex)
 6. [ISR_Timer_Switch](examples/ISR_Timer_Switch)
 7. [ISR_Timer_Switches](examples/ISR_Timer_Switches) 
 8. [RPM_Measure](examples/RPM_Measure)
 9. [SwitchDebounce](examples/SwitchDebounce)
10. [TimerInterruptTest](examples/TimerInterruptTest)
11. [**Change_Interval**](examples/Change_Interval). New.


---
---

### Example [ISR_Timer_Complex](examples/ISR_Timer_Complex)

```
#if !( ARDUINO_ESP32S2_DEV || ARDUINO_FEATHERS2 || ARDUINO_ESP32S2_THING_PLUS || ARDUINO_MICROS2 || \
       ARDUINO_METRO_ESP32S2 || ARDUINO_MAGTAG29_ESP32S2 || ARDUINO_FUNHOUSE_ESP32S2 || \
       ARDUINO_ADAFRUIT_FEATHER_ESP32S2_NOPSRAM )
  #error This code is intended to run on the ESP32-S2 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_PRINT Serial

//#define BLYNK_DEBUG
#ifdef BLYNK_DEBUG
  #undef BLYNK_DEBUG
#endif

#include <WiFi.h>

#define USE_SSL     false

#if USE_SSL
  #include <BlynkSimpleEsp32_SSL.h>
  #define BLYNK_HARDWARE_PORT     9443
#else
  #include <BlynkSimpleEsp32.h>
  #define BLYNK_HARDWARE_PORT     8080
#endif

#define USE_LOCAL_SERVER    true

// If local server
#if USE_LOCAL_SERVER
  //char blynk_server[]   = "account.duckdns.org";
  char blynk_server[]   = "192.168.2.110";
#else
  char blynk_server[]   = "";
#endif

char auth[]     = "****";
char ssid[]     = "****";
char pass[]     = "****";

// These define's must be placed at the beginning before #include "TimerInterrupt_Generic.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         1
#define _TIMERINTERRUPT_LOGLEVEL_     0

#include "ESP32_S2_TimerInterrupt.h"
#include "ESP32_S2_ISR_Timer.h"

#define TIMER_INTERVAL_MS         100
#define HW_TIMER_INTERVAL_MS      50

#define WIFI_TIMEOUT              20000L

volatile uint32_t lastMillis = 0;

// Init ESP32 timer 1
ESP32Timer ITimer(1);

// Init ESP32_ISR_Timer
ESP32_ISR_Timer ISR_Timer;

// Ibit Blynk Timer
BlynkTimer blynkTimer;

#ifndef LED_BUILTIN
  #define LED_BUILTIN       2         // Pin D2 mapped to pin GPIO2/ADC12 of ESP32, control on-board LED
#endif

#define LED_TOGGLE_INTERVAL_MS        5000L

void IRAM_ATTR TimerHandler(void * timerNo)
{
  /////////////////////////////////////////////////////////
  // Always call this for ESP32-S2 before processing ISR
  TIMER_ISR_START(timerNo);
  /////////////////////////////////////////////////////////
  
  static bool toggle  = false;
  static bool started = false;
  static int timeRun  = 0;

  ISR_Timer.run();

  // Toggle LED every LED_TOGGLE_INTERVAL_MS = 5000ms = 5s
  if (++timeRun == (LED_TOGGLE_INTERVAL_MS / HW_TIMER_INTERVAL_MS) )
  {
    timeRun = 0;

    if (!started)
    {
      started = true;
      pinMode(LED_BUILTIN, OUTPUT);
    }

    //timer interrupt toggles pin LED_BUILTIN
    digitalWrite(LED_BUILTIN, toggle);
    toggle = !toggle;
  }

  /////////////////////////////////////////////////////////
  // Always call this for ESP32-S2 after processing ISR
  TIMER_ISR_END(timerNo);
  /////////////////////////////////////////////////////////
}

// In ESP32, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash : "Guru Meditation Error: Core 1 panic'ed (Cache disabled but cached memory region accessed)"
void IRAM_ATTR doingSomething2s()
{
#if (TIMER_INTERRUPT_DEBUG > 0)  
  static unsigned long previousMillis = lastMillis;
  unsigned long deltaMillis = millis() - previousMillis;
  
  Serial.print("2s: D ms = "); Serial.println(deltaMillis);
  
  previousMillis = millis();
#endif

#if (TIMER_INTERRUPT_DEBUG > 1)
  Serial.print("2s: core "); Serial.println(xPortGetCoreID());
#endif
}

// In ESP32, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash : "Guru Meditation Error: Core 1 panic'ed (Cache disabled but cached memory region accessed)"
void IRAM_ATTR doingSomething5s()
{
#if (TIMER_INTERRUPT_DEBUG > 0)  
  static unsigned long previousMillis = lastMillis;
  unsigned long deltaMillis = millis() - previousMillis;
  
  Serial.print("5s: D ms = "); Serial.println(deltaMillis);
  
  previousMillis = millis();
#endif
  
#if (TIMER_INTERRUPT_DEBUG > 1)
  Serial.print("5s: core "); Serial.println(xPortGetCoreID());
#endif
}

// In ESP32, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash : "Guru Meditation Error: Core 1 panic'ed (Cache disabled but cached memory region accessed)"
void IRAM_ATTR doingSomething11s()
{
#if (TIMER_INTERRUPT_DEBUG > 0)  
  static unsigned long previousMillis = lastMillis;
  unsigned long deltaMillis = millis() - previousMillis;
  
  Serial.print("11s: D ms = "); Serial.println(deltaMillis);

  previousMillis = millis();
#endif
}

// In ESP32, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash : "Guru Meditation Error: Core 1 panic'ed (Cache disabled but cached memory region accessed)"
void IRAM_ATTR doingSomething101s()
{
#if (TIMER_INTERRUPT_DEBUG > 0)  
  static unsigned long previousMillis = lastMillis;
  unsigned long deltaMillis = millis() - previousMillis;
  
  Serial.print("101s: D ms = "); Serial.println(deltaMillis);

  previousMillis = millis();
#endif
}

#define BLYNK_TIMER_MS        2000L

// Here is software Timer, you can do somewhat fancy stuffs without many issues.
// But always avoid
// 1. Long delay() it just doing nothing and pain-without-gain wasting CPU power.Plan and design your code / strategy ahead
// 2. Very long "do", "while", "for" loops without predetermined exit time.
void blynkDoingSomething2s()
{
  static unsigned long previousMillis = lastMillis;
  
  Serial.print(F("blynkDoingSomething2s: Delta programmed ms = ")); Serial.print(BLYNK_TIMER_MS);
  Serial.print(F(", actual = ")); Serial.println(millis() - previousMillis);
  
  previousMillis = millis();
}

void setup()
{
  // Just a temporary hack
  // ESP32 WiFi is still buggy. By moving it up here, we can avoid interfering / interacting problem with other ISRs
  WiFi.begin(ssid, pass);

  delay(2000);

  Serial.begin(115200);
  while (!Serial);

  Serial.print(F("\nStarting ISR_Timer_Complex on ")); Serial.println(ARDUINO_BOARD);
  Serial.println(ESP32_S2_TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));
  
  // You need this timer for non-critical tasks. Avoid abusing ISR if not absolutely necessary.
  blynkTimer.setInterval(BLYNK_TIMER_MS, blynkDoingSomething2s);


  // Using ESP32  => 80 / 160 / 240MHz CPU clock ,
  // For 64-bit timer counter
  // For 16-bit timer prescaler up to 1024

  // Interval in microsecs
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
    lastMillis = millis();
    Serial.print(F("Starting ITimer OK, millis() = ")); Serial.println(lastMillis);
  }
  else
    Serial.println(F("Can't set ITimer correctly. Select another freq. or interval"));


  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  ISR_Timer.setInterval(2000L, doingSomething2s);
  ISR_Timer.setInterval(5000L, doingSomething5s);
  ISR_Timer.setInterval(11000L, doingSomething11s);
  ISR_Timer.setInterval(101000L, doingSomething101s);

  unsigned long startWiFi = millis();

  do
  {
    delay(200);
    if ( (WiFi.status() == WL_CONNECTED) || (millis() > startWiFi + WIFI_TIMEOUT) )
      break;
  } while (WiFi.status() != WL_CONNECTED);

  Blynk.config(auth, blynk_server, BLYNK_HARDWARE_PORT);
  Blynk.connect();

  if (Blynk.connected())
    Serial.println(F("Blynk connected"));
  else
    Serial.println(F("Blynk not connected yet"));
}

#define BLOCKING_TIME_MS      5000L

void loop()
{
  static bool needWiFiBegin = true;

  Blynk.run();

  // Blynk.run() in ESP32 doesn't reconnect automatically without below code with WiFi.begin(ssid, pass);
  if (!Blynk.connected())
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      unsigned long startWiFi = millis();
      Serial.println(F("WiFi not connected. Reconnect"));

      // Need to run again once per conn. lost
      if (needWiFiBegin)
      {
        Serial.println(F("WiFi begin again"));
        WiFi.begin(ssid, pass);
        needWiFiBegin = false;
      }

      do
      {
        delay(200);
        if ( (WiFi.status() == WL_CONNECTED) || (millis() > startWiFi + WIFI_TIMEOUT) )
        {
          // There is ESP32 bug, if WiFi+Blynk connected, then lost WiFi+ Internet
          // ESP32 can't reconect, even if we place WiFi.begin() again in loop()
          // The _network_event_task(void * arg) in WiFiGeneric.cpp is just waiting forever for data
          ESP.restart();
        }
      } while (WiFi.status() != WL_CONNECTED);
    }
    else
    {
      // Ready for next conn. lost
      Serial.println(F("reset needWiFiBegin"));
      needWiFiBegin = true;
      Blynk.config(auth, blynk_server, BLYNK_HARDWARE_PORT);
      Blynk.connect();
    }
  }
  else
  {
    // Ready for next conn. lost
    //needWiFiBegin = true;
  }

  // This unadvised blocking task is used to demonstrate the blocking effects onto the execution and accuracy to Software timer
  // You see the time elapse of ESP32_ISR_Timer still accurate, whereas very unaccurate for Software Timer
  // The time elapse for 2000ms software timer now becomes 3000ms (BLOCKING_TIME_MS)
  // While that of ESP32_ISR_Timer is still prefect.
  delay(BLOCKING_TIME_MS);

  // You need this Software timer for non-critical tasks. Avoid abusing ISR if not absolutely necessary
  // You don't need to and never call ISR_Timer.run() here in the loop(). It's already handled by ISR timer.
  blynkTimer.run();
}
```
---
---

### Debug Terminal Output Samples

### 1. ISR_Timer_Complex on ESP32_S2_DEV

The following is the sample terminal output when running example [ISR_Timer_Complex](examples/ISR_Timer_Complex) to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy**.  The ISR timer is **programmed for 2s, is activated exactly after 2.000s !!!**

While software timer, **programmed for 2s, is activated after 3.435s !!!**

```
Starting ISR_Timer_Complex on ESP32S2_DEV
ESP32_S2_TimerInterrupt v1.3.0
CPU Frequency = 240 MHz
Starting ITimer OK, millis() = 3015
[4415] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[4450] Ready (ping: 4ms).
Blynk connected
2s: D ms = 2000
2s: D ms = 2000
5s: D ms = 5000
2s: D ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 6508
2s: D ms = 2000
2s: D ms = 2000
5s: D ms = 5000
11s: D ms = 11000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 5005
2s: D ms = 2000
2s: D ms = 2000
5s: D ms = 5000
2s: D ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 5006
2s: D ms = 2000
2s: D ms = 2000
5s: D ms = 5000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 5005
2s: D ms = 2000
11s: D ms = 11000
2s: D ms = 2000
5s: D ms = 5000
2s: D ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 5006
2s: D ms = 2000
2s: D ms = 2000
5s: D ms = 5000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 5005
2s: D ms = 2000
11s: D ms = 11000
```

---

### 2. TimerInterruptTest on ESP32_S2_DEV

The following is the sample terminal output when running example [TimerInterruptTest](examples/TimerInterruptTest) to demonstrate how to start/stop Hardware Timers.

```
Starting TimerInterruptTest on ESP32S2_DEV
ESP32_S2_TimerInterrupt v1.3.0
CPU Frequency = 240 MHz
ITimer0 called, millis() = 699
Starting  ITimer0 OK, millis() = 702
ITimer1 called, millis() = 705
Starting  ITimer1 OK, millis() = 708
ITimer0 called, millis() = 1699
ITimer0 called, millis() = 2699
ITimer0 called, millis() = 3699
ITimer1 called, millis() = 3702
ITimer0 called, millis() = 4699
Stop ITimer0, millis() = 5001
ITimer1 called, millis() = 6702
ITimer1 called, millis() = 9702
Start ITimer0, millis() = 10002
ITimer0 called, millis() = 11002
ITimer0 called, millis() = 12002
ITimer1 called, millis() = 12702
ITimer0 called, millis() = 13002
ITimer0 called, millis() = 14002
Stop ITimer1, millis() = 15001
ITimer0 called, millis() = 15002
Stop ITimer0, millis() = 15003
Start ITimer0, millis() = 20004
ITimer0 called, millis() = 21004
ITimer0 called, millis() = 22004
ITimer0 called, millis() = 23004
ITimer0 called, millis() = 24004
ITimer0 called, millis() = 25004
Stop ITimer0, millis() = 25005
Start ITimer1, millis() = 30002
Start ITimer0, millis() = 30006
ITimer0 called, millis() = 31006
ITimer0 called, millis() = 32006
ITimer1 called, millis() = 33002
ITimer0 called, millis() = 33006
ITimer0 called, millis() = 34006
ITimer0 called, millis() = 35006
```

---


### 3. Change_Interval on ESP32_S2_DEV

The following is the sample terminal output when running example [Change_Interval](examples/Change_Interval) to demonstrate how to change Timer Interval on-the-fly

```
Starting Change_Interval on ESP32S2_DEV
ESP32_S2_TimerInterrupt v1.3.0
CPU Frequency = 240 MHz
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 0 , _fre = 1000000
[TISR] TIMER_BASE_CLK = 80000000 , TIMER_DIVIDER = 80
[TISR] _timerIndex = 0 , _timerGroup = 0
[TISR] _count = 0 - 2000000
[TISR] timer_set_alarm_value = 2000000.00
ITimer0: millis() = 720
Starting  ITimer0 OK, millis() = 724
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 1 , _fre = 1000000
[TISR] TIMER_BASE_CLK = 80000000 , TIMER_DIVIDER = 80
[TISR] _timerIndex = 1 , _timerGroup = 0
[TISR] _count = 0 - 5000000
[TISR] timer_set_alarm_value = 5000000.00
ITimer1: millis() = 746
Starting  ITimer1 OK, millis() = 749
ITimer0: millis() = 2715
ITimer0: millis() = 4715
ITimer1: millis() = 5741
ITimer0: millis() = 6715
ITimer0: millis() = 8715
Time = 10001, Timer0Count = 5, Timer1Count = 2
ITimer0: millis() = 10715
ITimer1: millis() = 10741
ITimer0: millis() = 12715
ITimer0: millis() = 14715
ITimer1: millis() = 15741
ITimer0: millis() = 16715
ITimer0: millis() = 18715
Time = 20002, Timer0Count = 10, Timer1Count = 4
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 0 , _fre = 1000000
[TISR] TIMER_BASE_CLK = 80000000 , TIMER_DIVIDER = 80
[TISR] _timerIndex = 0 , _timerGroup = 0
[TISR] _count = 0 - 4000000
[TISR] timer_set_alarm_value = 4000000.00
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 1 , _fre = 1000000
[TISR] TIMER_BASE_CLK = 80000000 , TIMER_DIVIDER = 80
[TISR] _timerIndex = 1 , _timerGroup = 0
[TISR] _count = 0 - 10000000
[TISR] timer_set_alarm_value = 10000000.00
Changing Interval, Timer0 = 4000,  Timer1 = 10000
ITimer0: millis() = 24011
ITimer0: millis() = 28011
Time = 30003, Timer0Count = 12, Timer1Count = 4
ITimer1: millis() = 30031
ITimer0: millis() = 32011
ITimer0: millis() = 36011

```

---

### 4. Argument_None on ESP32_S2_DEV

The following is the sample terminal output when running example [Argument_None](examples/Argument_None)

```
Starting Argument_None on ESP32S2_DEV
ESP32_S2_TimerInterrupt v1.3.0
CPU Frequency = 240 MHz
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 0 , _fre = 1000000
[TISR] TIMER_BASE_CLK = 80000000 , TIMER_DIVIDER = 80
[TISR] _timerIndex = 0 , _timerGroup = 0
[TISR] _count = 0 - 1000000
[TISR] timer_set_alarm_value = 1000000.00
ITimer0: millis() = 713
Starting  ITimer0 OK, millis() = 717
[TISR] ESP32_S2_TimerInterrupt: _timerNo = 1 , _fre = 1000000
[TISR] TIMER_BASE_CLK = 80000000 , TIMER_DIVIDER = 80
[TISR] _timerIndex = 1 , _timerGroup = 0
[TISR] _count = 0 - 5000000
[TISR] timer_set_alarm_value = 5000000.00
ITimer1: millis() = 739
Starting  ITimer1 OK, millis() = 742
ITimer0: millis() = 1708
ITimer0: millis() = 2708
ITimer0: millis() = 3708
ITimer0: millis() = 4708
ITimer0: millis() = 5708
ITimer1: millis() = 5733
ITimer0: millis() = 6708
ITimer0: millis() = 7708
ITimer0: millis() = 8708
ITimer0: millis() = 9708
ITimer0: millis() = 10708
ITimer1: millis() = 10733
ITimer0: millis() = 11708
ITimer0: millis() = 12708
ITimer0: millis() = 13708
ITimer0: millis() = 14708
ITimer0: millis() = 15708
ITimer1: millis() = 15733
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

## Releases

### Releases v1.3.0

1. Initial coding to support ESP32-S2
2. Sync with [ESP32TimerInterrupt library v1.3.0](https://github.com/khoih-prog/ESP32TimerInterrupt)
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

- The library is licensed under [MIT](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/blob/master/LICENSE)

---

## Copyright

Copyright 2021- Khoi Hoang


