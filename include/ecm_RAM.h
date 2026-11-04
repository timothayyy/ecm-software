#ifndef ECM_ECM_RAM_H
#define ECM_ECM_RAM_H

#include <stdint.h>

typedef struct {
    uint16_t current_engine_speed;
    uint16_t current_vehicle_speed;
    double calculated_engine_torque;

    uint16_t raw_accel_pedal_voltage;
    uint8_t calculated_pedal_percent;
    bool cruise_control_active_switch;

    uint16_t dynamic_requested_fuel_mass;
    bool is_fuel_cut_active;
    uint8_t VGT_Vane_Target_Duty_Cycle;
    uint8_t active_engine_brake_cylinders;

    double current_coolant_temperatures;
    double current_oil_temperatures;
} ECMRuntimeState;

ECMRuntimeState initializeECMRuntimeState(void);


#endif //ECM_ECM_RAM_H
