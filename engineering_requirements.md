ECM Software Simulator
ENGINEERING REQUIREMENTS DOCUMENT · VERSION 0.1
1. System requirements
   
   ID	Requirement
   SYS-001	The system shall simulate an electronic engine control module (ECM).
   SYS-002	The system shall maintain a centralized runtime state representing current engine and vehicle operating conditions.
   SYS-003	The system shall support configurable engine and vehicle operating parameters.
   SYS-004	The system shall evaluate operating conditions and execute corresponding control functions.
   SYS-005	The system shall distinguish between calibration parameters and mutable runtime data.
   SYS-006	The system shall provide a modular software architecture that supports independent development and testing of control features.

2. Cruise control requirements
  
   Engagement eligibility
   ID	Requirement
   CC-001	The ECM shall prevent cruise control engagement below the configured minimum engagement speed.
   CC-002	The ECM shall prevent cruise control engagement above the configured maximum engagement speed.
   CC-003	The ECM shall permit cruise control engagement when vehicle speed is within the configured engagement range.
   CC-004	The ECM shall maintain cruise engagement eligibility separately from the active cruise-control state.

Maximum set speed
ID	Requirement
CC-005	The ECM shall prevent the driver from selecting a cruise speed above the configured maximum set-speed limit.
CC-006	The ECM shall prevent the driver from selecting a cruise speed below the configured minimum set-speed limit.

Overspeed protection
ID	Requirement
CC-007	The ECM shall monitor vehicle speed while cruise control is active.
CC-008	The ECM shall calculate the difference between actual vehicle speed and the driver's cruise set speed.
CC-009	The ECM shall activate fuel-cut functionality when actual vehicle speed exceeds the cruise set speed by a positive overspeed delta.
CC-010	The ECM shall progressively increase engine braking based on the calculated overspeed delta.
CC-011	The ECM shall deactivate overspeed intervention when vehicle speed returns to or below the cruise set speed.
CC-012	The ECM shall restore normal engine-braking commands when cruise control is inactive.

3. Engine-braking requirements
   ID	Requirement
   EB-001	The ECM shall support three configurable engine-braking levels: LOW, MEDIUM, and HIGH.
   EB-002	LOW engine braking shall activate two engine-braking cylinders.
   EB-003	MEDIUM engine braking shall activate four engine-braking cylinders.
   EB-004	HIGH engine braking shall activate six engine-braking cylinders.
   EB-005	The ECM shall adjust VGT target duty cycle according to the active engine-braking level.
   EB-006	The ECM shall command a normal VGT target duty cycle when engine braking is inactive.
   EB-007	The ECM shall reset engine-braking runtime state when overspeed intervention is no longer required.

State	VGT target
Normal	40%
LOW	75%
MEDIUM	85%
HIGH	95%

These are simulation values, not validated production calibrations.
4. Fuel management requirements
   ID	Requirement
   FUEL-001	The ECM shall maintain a calculated requested fuel-mass value.
   FUEL-002	The ECM shall set requested fuel mass to zero when fuel cut is active.
   FUEL-003	The ECM shall restore normal fuel-request calculations when fuel cut is inactive.
   FUEL-004	The ECM shall prevent fuel-cut state and requested fuel-mass state from becoming inconsistent.

5. Runtime and software architecture requirements
  
   ID	Requirement
   SW-001	Shared runtime data shall be maintained within the ECM runtime structure.
   SW-002	Calibration data shall be passed to control functions as read-only data where appropriate.
   SW-003	Control functions shall modify runtime state rather than directly modifying calibration parameters.
   SW-004	Enumerations shall be used for discrete operating states where appropriate.
   SW-005	Boolean variables shall represent binary operating conditions.
   SW-006	Control functions shall have clearly defined inputs, outputs, and responsibilities.
   SW-007	The software shall use explicit data types appropriate to the represented values.
   SW-008	The software shall initialize runtime state to defined startup values.
   SW-009	The software shall detect and safely handle invalid or out-of-range input values.

6. Verification and testing requirements
   
   ID	Requirement
   TEST-001	Each control function shall have corresponding unit tests.
   TEST-002	Each configured operating threshold shall be tested at its lower boundary, exact boundary, and upper boundary.
   TEST-003	The simulator shall test transitions between all engine-braking levels.
   TEST-004	The simulator shall test cruise-control activation and deactivation conditions.
   TEST-005	The simulator shall verify that fuel cut is activated and deactivated under the correct conditions.
   TEST-006	The simulator shall verify that runtime state is correctly reset when intervention ends.
   TEST-007	The project shall build successfully using its configured compiler and build system.
   TEST-008	Software changes shall be regression-tested against previously implemented functionality.

Phase 1: Core ECM architecture
In progress

- [x] Runtime state structure
- [x] Calibration structure
- [x] Modular source/header organization
- [ ] Runtime initialization validation
- [ ] Input validation


Phase 2: Engine and vehicle control
- [ ] Cruise-control engagement logic
- [ ] Maximum set-speed enforcement
- [ ] Overspeed detection
- [ ] Progressive engine braking
- [ ] Fuel management


Phase 3: Embedded communications
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


Phase 5: Advanced embedded concepts
- [ ] State machines
- [ ] Timing and task scheduling
- [ ] Simulink/Stateflow modeling
- [ ] Hardware abstraction
- [ ] Real-time operating system concepts