# ESP32_S2_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP32_S2_TimerInterrupt.svg?)](https://www.ardu-badge.com/ESP32_S2_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP32_S2_TimerInterrupt.svg)](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP32_S2_TimerInterrupt/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP32_S2_TimerInterrupt.svg)](http://github.com/khoih-prog/ESP32_S2_TimerInterrupt/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.5.1](#releases-v151)
  * [Releases v1.5.0](#releases-v150)
  * [Releases v1.4.0](#releases-v140)
  * [Releases v1.3.0](#releases-v130)

---
---

## Changelog

### Releases v1.5.1

1. Add support to new Adafruit board QTPY_ESP32S2
2. Update examples

### Releases v1.5.0

1. Fix `multiple-definitions` linker error. Drop `src_cpp` and `src_h` directories
2. Avoid deprecated functions.
3. Add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project.
4. Optimize library code by using `reference-passing` instead of `value-passing`
5. Update all examples


### Releases v1.4.0

1. Fix compiler errors due to conflict to some libraries.
2. Add complex examples.

### Releases v1.3.0

1. Initial coding to support ESP32-S2
2. Sync with [ESP32TimerInterrupt library v1.3.0](https://github.com/khoih-prog/ESP32TimerInterrupt)

