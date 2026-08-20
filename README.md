# CalmNest Beta ESP32 PICO D4 Audio Controller

## Purpose

This project implements the secondary controller baseline for wireless audio. It receives PCM audio through I2S and provides that stream to an ESP32 Bluetooth A2DP source.

## Implemented baseline

* I2S receiver configuration
* 44.1 kHz, 16 bit, stereo stream configuration
* Bluetooth A2DP source startup
* Bluetooth connection state monitoring
* Automatic reconnect option provided by the A2DP library
* Centralized board and stream constants in `include/BoardConfig.h`

## Not claimed as completed

The current source does not claim completion of persistent pairing storage, S3 command protocol, physical power gating, or hardware validated reconnect timing. Those behaviors require additional implementation or board testing.

## Build

From this folder:

```bash
pio run -e pico32
```

Full instructions are in the package root at `docs/BUILD_INSTRUCTIONS.md`.
