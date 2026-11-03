# ECM Software Simulator

A C23-based educational project exploring the architecture and core software logic of an automotive diesel Engine Control Module (ECM).

## Overview

This project is being developed to better understand how embedded engine control software is structured, how it processes operating data, and how different software components interact.

The simulation is inspired by real-world diesel engine control systems and professional experience working with engine calibrations, software releases, and calibration validation.

The primary focus is **core ECM software development**, rather than creating or tuning production engine calibrations.

The project is a work in progress and will evolve as new C programming concepts are learned and implemented.

## Project Structure

The software is organized into eight subfiles, each with a corresponding header file.

```text
ecm-software/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── main.c
│
├── include/
│   ├── subfile_1.h
│   ├── subfile_2.h
│   ├── subfile_3.h
│   ├── subfile_4.h
│   ├── subfile_5.h
│   ├── subfile_6.h
│   ├── subfile_7.h
│   └── subfile_8.h
│
└── src/
    ├── subfile_1.c
    ├── subfile_2.c
    ├── subfile_3.c
    ├── subfile_4.c
    ├── subfile_5.c
    ├── subfile_6.c
    ├── subfile_7.c
    └── subfile_8.c
```

This is the intended project structure. Not all files or functionality have been implemented.

## Software Architecture

The project uses eight subfiles to organize engine control functionality and parameter definitions.

Each subfile consists of:

- **`.h` file:** Contains structures, type definitions, constants, and function declarations.
- **`.c` file:** Contains the corresponding function implementations and software logic.

`main.c` serves as the application's entry point and coordinates the execution of the simulation.

The subfile system is inspired by ECM software and calibration architectures encountered in industrial engine development. It is not intended to reproduce any manufacturer's proprietary implementation.

## Development Focus

The project will explore several aspects of embedded software engineering:

- Data structures and memory management
- Sensor input processing
- Engine operating states
- Fueling and torque control logic
- Engine protection and fault detection
- Diagnostic and shutdown conditions
- Parameter validation and integrity checking
- Potential simulated CAN bus and SAE J1939 communication

Features will be added incrementally as development progresses.

### Calibration Parameters

The software will define parameter structures and implement functions that use those parameters.

Calibration values will initially use simplified defaults or test data. Developing realistic engine calibration maps and performing engine tuning are outside the current project scope.

### CRC Validation

One of the initial exercises involves implementing checksum comparison logic using:

- Fixed-width integer types
- Arrays
- Structures
- Pointers
- Functions
- Conditional statements
- Loops

The initial implementation compares placeholder checksum values. It is not yet a complete CRC calculation algorithm.

## Technologies

- **Language:** C23
- **IDE:** JetBrains CLion
- **Build System:** CMake
- **Version Control:** Git / GitHub
- **Development Platform:** macOS

## Build Instructions

The project uses CMake and a C23-compatible compiler.

```bash
cmake -S . -B build
cmake --build build
```

Run the executable from the build directory. Its name and location depend on the configured CMake target and platform.

## Project Goals

The primary goal is to develop a deeper understanding of C programming through practical applications related to engine control systems.

Rather than focusing on building a production-ready ECM, the project emphasizes understanding:

1. How C source and header files work together.
2. How structures organize engine-related data.
3. How functions process and modify operating states.
4. How pointers allow functions to access shared data.
5. How software logic evaluates operating conditions.
6. How larger embedded software systems can be organized into separate components.

## Disclaimer

This project is an independent educational simulation.

It is not affiliated with, endorsed by, or derived from proprietary source code belonging to Cummins Inc. or any other engine manufacturer.

All implemented algorithms, test values, and simulated operating conditions are intended for educational use only.

**This software is not designed or validated to control a physical engine or vehicle.**

## Status

**Early Development — Work in Progress**

The project is being developed incrementally as part of learning C programming and embedded software concepts.