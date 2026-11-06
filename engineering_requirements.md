ECM Software Simulator
Engineering Requirements Document
Document ID: ECM-REQ-001
Version: 0.1
Status: Baseline Draft
Purpose: Define the initial system, functional, software, and
verification requirements for the educational ECM software simulator.
Disclaimer: This is an educational simulator. All calibration
values and control strategies are illustrative and are not validated
for production engines, vehicles, or safety-critical applications.

1. System Requirements
    ---
   ID                                  Requirement
   SYS-001                             The system shall simulate an
   electronic engine control module
   (ECM).

SYS-002                             The system shall maintain a
centralized runtime state
representing current engine and
vehicle operating conditions.

SYS-003                             The system shall support
configurable engine and vehicle
operating parameters.

SYS-004                             The system shall evaluate operating
conditions and execute
corresponding control functions.

SYS-005                             The system shall distinguish
between calibration parameters and
mutable runtime data.
SYS-006                             The system shall provide a modular
software architecture that supports
independent development and testing
of control features.

2. Cruise-Control Requirements
    ---
   2.1 Engagement Eligibility
   ID                                  Requirement
   CC-001                              The ECM shall prevent
   cruise-control engagement below the
   configured minimum engagement
   speed.

CC-002                              The ECM shall prevent
cruise-control engagement above the
configured maximum engagement
speed.

CC-003                              The ECM shall permit cruise-control
engagement when vehicle speed is
within the configured engagement
range.
CC-004                              The ECM shall maintain cruise
engagement eligibility separately
from the active cruise-control
state.
2.2 Maximum Set Speed
ID                                  Requirement
CC-005                              The ECM shall prevent the driver
from selecting a cruise speed above
the configured maximum set-speed
limit.
CC-006                              The ECM shall prevent the driver
from selecting a cruise speed below
the configured minimum set-speed
limit.
2.3 Overspeed Protection
ID                                  Requirement
CC-007                              The ECM shall monitor vehicle speed
while cruise control is active.

CC-008                              The ECM shall calculate the
difference between actual vehicle
speed and the driver's cruise set
speed.

CC-009                              The ECM shall activate fuel-cut
functionality when actual vehicle
speed exceeds the cruise set speed
by a positive overspeed delta.

CC-010                              The ECM shall progressively
increase engine braking based on
the calculated overspeed delta.

CC-011                              The ECM shall deactivate overspeed
intervention when vehicle speed
returns to or below the cruise set
speed.
CC-012                              The ECM shall restore normal
engine-braking commands when cruise
control is inactive.
3. Engine-Braking Requirements
    ---
   ID                                  Requirement
   EB-001                              The ECM shall support three
   engine-braking levels: LOW, MEDIUM,
   and HIGH.

EB-002                              LOW engine braking shall activate
two engine-braking cylinders.

EB-003                              MEDIUM engine braking shall
activate four engine-braking
cylinders.

EB-004                              HIGH engine braking shall activate
six engine-braking cylinders.

EB-005                              The ECM shall adjust VGT target
duty cycle according to the active
engine-braking level.

EB-006                              The ECM shall command a normal VGT
target duty cycle when engine
braking is inactive.
EB-007                              The ECM shall reset engine-braking
runtime state when overspeed
intervention is no longer required.
3.1 Illustrative Calibration Values
These values represent the current simulator concept. They are examples
for software behavior and are not production calibration
recommendations.

State      Active Cylinders   VGT Target Duty Cycle
Normal                    0                     40%
LOW                       2                     75%
MEDIUM                    4                     85%
HIGH                      6                     95%
3.2 Illustrative Overspeed Thresholds
Overspeed Delta Expected Engine-Braking Level

     0 or below No engine braking
          1--15 LOW
         16--30 MEDIUM
31 or greater HIGH
These thresholds may be revised as the control strategy and test
coverage develop.

4. Fuel-Management Requirements
    ---
   ID                                  Requirement
   FUEL-001                            The ECM shall maintain a calculated
   requested fuel-mass value.

FUEL-002                            The ECM shall set requested fuel
mass to zero when fuel cut is
active.

FUEL-003                            The ECM shall restore normal
fuel-request calculations when fuel
cut is inactive.
FUEL-004                            The ECM shall prevent fuel-cut
state and requested fuel-mass state
from becoming inconsistent.
5. Runtime and Software Architecture Requirements
    ---
   ID                                  Requirement
   SW-001                              Shared runtime data shall be
   maintained within the ECM runtime
   structure.

SW-002                              Calibration data shall be passed to
control functions as read-only data
where appropriate.

SW-003                              Control functions shall modify
runtime state rather than directly
modifying calibration parameters.

SW-004                              Enumerations shall be used for
discrete operating states where
appropriate.

SW-005                              Boolean variables shall represent
binary operating conditions.

SW-006                              Control functions shall have
clearly defined inputs, outputs,
and responsibilities.

SW-007                              The software shall use explicit
data types appropriate to the
represented values.

SW-008                              The software shall initialize
runtime state to defined startup
values.
SW-009                              The software shall detect and
safely handle invalid or
out-of-range input values.
6. Verification and Testing Requirements
    ---
   ID                                  Requirement
   TEST-001                            Each control function shall have
   corresponding unit tests.

TEST-002                            Each configured operating threshold
shall be tested at its lower
boundary, exact boundary, and upper
boundary.

TEST-003                            The simulator shall test
transitions between all
engine-braking levels.

TEST-004                            The simulator shall test
cruise-control activation and
deactivation conditions.

TEST-005                            The simulator shall verify that
fuel cut is activated and
deactivated under the correct
conditions.

TEST-006                            The simulator shall verify that
runtime state is correctly reset
when intervention ends.

TEST-007                            The project shall build
successfully using its configured
compiler and build system.
TEST-008                            Software changes shall be
regression-tested against
previously implemented
functionality.
7. Development Roadmap
    ---
   Phase 1: Core ECM Architecture
- [x] Runtime state structure
- [x] Calibration structure
- [x] Modular source/header organization
- [ ] Runtime initialization validation
- [ ] Input validation
  Phase 2: Engine and Vehicle Control
- [ ] Cruise-control engagement logic
- [ ] Maximum set-speed enforcement
- [ ] Overspeed detection
- [ ] Progressive engine braking
- [ ] Fuel management
  Phase 3: Embedded Communications
- [ ] CAN fundamentals
- [ ] J1939 message structure
- [ ] PGN/SPN interpretation
- [ ] Simulated sensor messages
- [ ] Simulated actuator commands
  Phase 4: Verification
- [ ] Unit testing
- [ ] Boundary-condition testing
- [ ] Fault injection
- [ ] Regression testing
- [ ] Integration testing
  Phase 5: Advanced Embedded Concepts
- [ ] State machines
- [ ] Timing and task scheduling
- [ ] Simulink/Stateflow modeling
- [ ] Hardware abstraction
- [ ] Real-time operating system concepts
8. Requirements Traceability
   Each engineering requirement should connect to:
1. A software function that implements it.
2. One or more test cases that verify it.
3. A test result indicating whether it passed.
   8.1 Traceability Example: CC-010
   Engineering Requirement

The ECM shall progressively increase engine braking based on overspeed
delta.

Implementation

The overspeed-control function currently being developed in Subfile 1.

Verification Cases
Overspeed Delta Expected Result

              0 No engine braking
             10 LOW
             20 MEDIUM
             35 HIGH
             -5 No engine braking
8.2 Traceability Record
Use this table to track implementation and verification progress.
Requirement ID Implementation   Test Case      Status         Notes
Location         ID(s)                         
CC-001         TBD              TBD            Not Started

CC-002         TBD              TBD            Not Started    
CC-010         TBD              TBD            Not Started
Suggested status values:
- Not Started
- In Progress
- Implemented
- Verified
- Blocked
9. Change Management
    ---
- Assign a unique ID to every requirement.
- Keep each requirement specific, measurable, and testable.
- Update the requirement when the intended system behavior changes.
- Review affected implementation and test cases whenever a requirement
  changes.
- Record significant design decisions and the reasoning behind them.
- Do not mark a requirement as verified solely because the project
  compiles. Verification requires evidence that the specified behavior
  was tested.
10. Project Development Principle
    ---
    Develop the simulator incrementally. Treat each feature as an
    engineering requirement, implement it, and create tests that demonstrate
    the required behavior.

Prioritize correctness, traceability, and understanding over adding
features quickly.

This document is a living baseline and should evolve alongside the
simulator.