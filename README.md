# ECM Software Simulator

A modular Engine Control Module (ECM) software simulation written in C, designed to model engine calibration parameters, runtime memory, and control logic for a heavy-duty diesel engine.

This project is inspired by real-world engine calibration and manufacturing processes, with an emphasis on understanding how calibration data interacts with executable control software.

The simulator is an independent educational project and is not affiliated with Cummins, John Deere, or any other engine manufacturer.

## Project Overview

The objective is to build a simplified ECM software environment that separates three key elements:

1. **Calibration data:** Parameters that define how the engine and its supporting systems are configured.
2. **Runtime memory:** Live operating values and control states that change while the engine is running.
3. **Control logic:** Functions that evaluate calibration parameters and operating conditions to determine how the ECM responds.

The project uses eight calibration subfiles, independent C source modules, and a shared runtime memory structure.

Development is iterative. Functions are implemented individually, tested, and revised as additional systems and dependencies are introduced.

## Technology Stack

- **Language:** C (C23)
- **IDE:** JetBrains CLion
- **Build system:** CMake
- **Compiler:** C23-compatible C compiler
- **Version control:** Git
- **Repository hosting:** GitHub
- **Development environment:** macOS / Apple Silicon

## Project Structure

```text
ecm-software/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── main.c
│
├── include/
│   ├── ecm_RAM.h
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
    ├── ecm_RAM.c
    ├── subfile_1.c
    ├── subfile_2.c
    ├── subfile_3.c
    ├── subfile_4.c
    ├── subfile_5.c
    ├── subfile_6.c
    ├── subfile_7.c
    └── subfile_8.c
```

### Header Files

Header files in `include/` contain structure definitions, enumerations, and function declarations.

### Source Files

Source files in `src/` contain function implementations for individual calibration subfiles and shared runtime functionality.

### Main Program

`main.c` serves as the application's entry point, initializes the required data structures, and invokes ECM functions for testing.

## Calibration Architecture

The project uses an eight-subfile architecture to organize ECM configuration and control functionality.

| Subfile | Implementation status |
|---|---|
| Subfile 1 | Active development — initial calibration and control functions implemented |
| Subfile 2 | Reserved for future development |
| Subfile 3 | Reserved for future development |
| Subfile 4 | Reserved for future development |
| Subfile 5 | Reserved for future development |
| Subfile 6 | Reserved for future development |
| Subfile 7 | Reserved for future development |
| Subfile 8 | Reserved for future development |

The architecture is inspired by multi-subfile engine calibration systems, but its implementation is simplified for educational use.

The planned division of responsibilities may evolve as the project grows.

## Subfile 1 — Configuration and Control Parameters

`subfile_1.h` defines the `Subfile1` structure and supporting enumerations.

Subfile 1 currently includes parameters related to:

- Calibration integrity and checksum storage
- Security seed/key salt
- Software and diagnostic option identification
- Boot and reset reasons
- Cruise control and vehicle speed limits
- Vehicle speed sensor configuration
- Tire revolutions per mile and axle ratio
- Idle shutdown configuration
- Base engine idle speed
- Low-voltage idle-up enablement
- Transmission configuration
- Engine torque limits
- Engine governor speed
- Coolant temperature protection thresholds
- Oil pressure shutdown configuration
- Engine cylinder count
- Power takeoff configuration
- Engine braking configuration
- Aftertreatment and DPF regeneration settings
- DEF tank capacity

Calibration values are maintained separately from runtime operating data.

### Boot Reason Enumeration

The `BootReason` enumeration defines flags for:

```c
COLD_BOOT
WARM_BOOT
WATCHDOG_TIMEOUT_RESET
SOFTWARE_RESET
BROWNOUT_RESET
SERVICE_REQUEST
```

Bitwise flags allow multiple boot/reset indicators to be represented and evaluated.

### Engine Braking Configuration

The `EB_LevelConfig` enumeration defines four braking levels:

```c
typedef enum {
    EB_LEVEL_NONE = 0,
    EB_LEVEL_LOW = 1,
    EB_LEVEL_MEDIUM = 2,
    EB_LEVEL_HIGH = 3
} EB_LevelConfig;
```

These values are used in the engine braking control logic to represent commanded braking stages.

## ECM Runtime Memory

The ECM runtime memory system is defined in:

- `include/ecm_RAM.h`
- `src/ecm_RAM.c`

The `ECMRuntimeState` structure contains live operating values and control states.

Unlike calibration values, runtime variables are expected to change as the simulated engine operates.

### Runtime Parameters

Current runtime data includes:

| Parameter | Description |
|---|---|
| `current_engine_speed` | Current engine RPM |
| `current_vehicle_speed` | Current vehicle speed |
| `calculated_engine_torque` | Calculated engine torque |
| `raw_accel_pedal_voltage` | Accelerator pedal sensor voltage |
| `calculated_pedal_percent` | Calculated accelerator pedal position |
| `cruise_control_active_switch` | Cruise control active status |
| `dynamic_requested_fuel_mass` | Requested fuel quantity |
| `is_fuel_cut_active` | Fuel cut activation status |
| `current_engine_brake_level` | Current engine braking stage |
| `active_engine_brake_cylinders` | Number of active engine braking cylinders |
| `VGT_Vane_Target_Duty_Cycle` | Commanded VGT duty cycle |
| `current_coolant_temperatures` | Current coolant temperature |
| `current_oil_temperatures` | Current oil temperature |

### Runtime Initialization

The function:

```c
ECMRuntimeState initializeECMRuntime(void);
```

initializes the ECM runtime structure with default values.

The runtime structure is then passed to control functions using pointers, allowing the functions to read and modify operating states.

## Implemented Functionality

### 1. Calibration Checksum Verification

**Function:** `checkCRC()`

Compares six calculated checksum values against the corresponding values stored in Subfile 1.

The function:

- Iterates through the checksum array.
- Compares the calculated and stored values.
- Reports the index of a detected mismatch.
- Returns `false` when a mismatch occurs.
- Returns `true` when all values match.

**Current limitation:** This is checksum comparison logic, not a complete CRC-generation algorithm.

### 2. Boot Reason Detection

**Function:** `checkBootReason()`

Evaluates the configured boot reason flags using bitwise operations.

Supported conditions include cold boot, warm boot, watchdog timeout, software reset, brownout reset, and service request.

Multiple flags may be detected during a single evaluation.

### 3. Security Salt Comparison

**Function:** `checkSaltKey()`

Compares a supplied value against the configured security seed/key salt.

The function reports whether the two values match.

**Current limitation:** This is a basic comparison for learning purposes, not a production-grade seed/key authentication implementation.

### 4. Cruise Overspeed and Progressive Engine Braking

**Function:** `maxVehicleSetLimit()`

This function evaluates vehicle speed against the configured maximum cruise set-speed limit while checking cruise control status.

When the simulated overspeed condition is satisfied, the function activates fuel cut and advances through progressive engine braking stages.

#### Activation Conditions

The control sequence begins when:

- Current vehicle speed exceeds the configured limit.
- Cruise control is active.

#### Braking Progression

| Stage | Fuel cut | Engine brake level | Active cylinders | VGT target |
|---|---|---|---|---|
| Initial | Active | NONE | 0 | 0% |
| Low | Active | LOW | 2 | 75% |
| Medium | Active | MEDIUM | 4 | 85% |
| High | Active | HIGH | 6 | 95% |

Compression-release engine braking and VGT braking operate together at each braking level.

The active braking stage is stored in ECM runtime memory.

#### Conditional Progression

The function uses an `if / else if` structure to prevent all braking levels from being selected during the same function invocation.

While the overspeed condition remains active:

- `EB_LEVEL_NONE` advances to `EB_LEVEL_LOW`.
- `EB_LEVEL_LOW` advances to `EB_LEVEL_MEDIUM`.
- `EB_LEVEL_MEDIUM` advances to `EB_LEVEL_HIGH`.
- `EB_LEVEL_HIGH` remains active until the reset condition is satisfied.

Each invocation advances the braking sequence by at most one level.

#### Reset Behavior

When vehicle speed returns to or below the configured limit, or cruise control becomes inactive, the function resets:

```c
runtime->is_fuel_cut_active = false;
runtime->active_engine_brake_cylinders = 0;
runtime->VGT_Vane_Target_Duty_Cycle = 0;
runtime->current_engine_brake_level = EB_LEVEL_NONE;
```

This returns the simulated braking system to its initial inactive state.

#### Current Limitations

The braking progression is based on consecutive function invocations rather than elapsed time or additional overspeed thresholds.

Future development may introduce:

- Time-based progression between braking stages
- Speed-error thresholds
- Engine speed restrictions
- Brake availability and protection conditions
- Additional cruise control operating states
- Coordination with other ECM protection functions

The configured maximum cruise set speed is being used as a simplified activation threshold. A production ECM would typically distinguish between maximum selectable cruise speed, the driver-selected cruise setpoint, and road-speed governing thresholds.

VGT duty targets and braking cylinder assignments are simulation values, not validated engine hardware control commands.

## Software Design Principles

### Separation of Calibration and Runtime Data

Calibration parameters are accessed through the `Subfile1` structure.

```c
sf1->CC_Max_Vehicle_Speed_Set_Limit
```

Live operating values are accessed through `ECMRuntimeState`.

```c
runtime->current_vehicle_speed
```

Control functions can read calibration settings while updating runtime states.

### Pointer-Based Data Access

Functions receive pointers to the appropriate structures.

Example:

```c
void maxVehicleSetLimit(
    const Subfile1 *sf1,
    ECMRuntimeState *runtime);
```

The `const` qualifier protects calibration data from modification within the function.

The mutable runtime pointer allows live control values to be updated.

### Modular Development

Each calibration subfile has a dedicated header and source file.

Runtime state management is implemented separately to allow multiple control functions to operate on shared engine data.

### Incremental Implementation

The project intentionally uses an iterative development process.

Initial functions are developed to satisfy specific requirements. As new control systems are introduced, existing functions may be refactored to accommodate additional dependencies and interactions.

## Building the Project

The project uses CMake for compilation.

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

The executable can also be built and run using JetBrains CLion.

All required `.c` files must be included in the CMake build target, and the `include/` directory must be configured as an include path.

## Development Status

**Status: Active development**

### Implemented or integrated

- [x] Eight-subfile project structure
- [x] Separate header and source directories
- [x] Subfile 1 calibration structure
- [x] Calibration parameter default initialization
- [x] Boot reason enumeration and flag evaluation
- [x] Checksum comparison function
- [x] Security salt comparison function
- [x] ECM runtime memory structure
- [x] Runtime initialization function
- [x] Cruise overspeed condition evaluation
- [x] Fuel cut activation
- [x] Progressive LOW / MEDIUM / HIGH braking logic
- [x] Coordinated VGT braking targets
- [x] Reset logic for braking and fuel cut
- [x] Main program integration

### Future development

- [ ] Time-based or threshold-based braking escalation
- [ ] Additional runtime state validation
- [ ] Functional tests for braking progression and reset conditions
- [ ] Calibration parameter range validation
- [ ] Actual CRC calculation
- [ ] Expanded engine protection logic
- [ ] Engine speed governing
- [ ] Idle shutdown logic
- [ ] Accelerator pedal interpretation
- [ ] Transmission-related control logic
- [ ] PTO control behavior
- [ ] Aftertreatment control logic
- [ ] Development of Subfiles 2–8
- [ ] Additional integration testing

This roadmap is subject to change as the ECM architecture develops.

## Project Goals

The primary goals are to:

- Improve proficiency in C programming.
- Gain practical experience with structures, pointers, enums, arrays, and conditional logic.
- Develop familiarity with modular embedded-style software architecture.
- Model the relationship between engine calibration and runtime control software.
- Practice debugging and validating control behavior.
- Explore interactions between engine subsystems.
- Build a progressively more capable ECM simulation.

## Disclaimer

This project is for educational and experimental purposes only.

It does not interface with a physical engine or ECM and is not intended for vehicle installation, engine tuning, emissions-system modification, or safety-critical applications.

All control strategies and calibration values should be considered simulated unless independently validated.

## Author

**Timothy Long**

Background in heavy-duty diesel engine calibration, manufacturing quality, product design support, and software validation.

## Repository

[github.com/timothayyy/ecm-software](https://github.com/timothayyy/ecm-software)
