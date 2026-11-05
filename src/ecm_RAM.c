#include "ecm_RAM.h"

ECMRuntimeState initializeECMRuntime(void) {

    ECMRuntimeState runtime = {
        .current_engine_speed = 0,
        .current_vehicle_speed = 0,
        .calculated_engine_torque = 0.0,

        .raw_accel_pedal_voltage = 0,
        .calculated_pedal_percent = 0,
        .cruise_control_active_switch = false,
        .cruise_control_engage_permitted = false,

        .dynamic_requested_fuel_mass = 0,
        .is_fuel_cut_active = false,
        .VGT_Vane_Target_Duty_Cycle = 0,
        .jake_brake_active = false,
        .active_engine_brake_cylinders = 0,

        .current_coolant_temperatures = 0.0,
        .current_oil_temperatures = 0.0
    };

    return runtime;
}
