# Linux Hardware Monitor

A lightweight C++ hardware and thermal monitor for Linux AI infrastructure, utilizing direct kernel file parsing for near-zero resource overhead.

## Features
* **Direct Kernel Parsing:** Reads `/sys` and `/proc` virtual files directly, bypassing bloated third-party system libraries.
* **Thermal Tracking:** Monitors CPU core temperatures with built-in critical threshold warnings to protect hardware during heavy ML training workloads.
* **Memory Allocation:** Tracks real-time RAM usage (Total vs. Used/Free).
* **High Efficiency:** Utilizes C++ standard thread sleeping to maintain a near-zero performance footprint.

## Prerequisites
* A Linux-based operating system (Ubuntu/Debian recommended)
* GCC Compiler (`g++`)
* `make` build automation tool

## Installation & Build

1. Clone the repository:
   ```bash
   git clone [https://github.com/1chinousa1/linux-hardware-monitor.git](https://github.com/1chinousa1/linux-hardware-monitor.git)
   cd linux-hardware-monitor
   
