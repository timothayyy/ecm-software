#include <stdio.h>
#include "../include/subfile_1.h"
#include "../include/ecm_RAM.h"

#include <sys/resource.h>

uint32_t calculatedCRC[6] = {0, 0, 0, 0, 0, 0};
uint8_t bootReason = 0;

Subfile1 sf1 = {
    .T_SECURITY_SEED_KEY_SALT = 0,
    .SC_OPTION_NUM = 1001,
    .DO_OPTION_NUM = 1002,
    .CC_Max_Vehicle_Speed_Set_Limit = 680,
    .CC_Minimum_Engage_Speed = 300,
    .CC_OEM_Max_Vehicle_Speed_Limit = 750,
    .VSS_Tire_Revolution_Per_Mile = 504,
    .Axle_Primary_Ratio = 2.64,
    .VSS_Sensor_Type_Config = VSS_J1939,
    .ISD_Idle_Shutdown_Time_Delay = 5,
    .ISD_Ambient_Air_Temp_Low_Override = 35.0,
    .ISD_Ambient_Air_Temp_High_Override = 80.0,
    .ENG_Base_Target_Idle_Speed = 650,
    .ENG_Battery_Voltage_Low_Idle_Up_Enable = true,
    .XMSN_Type_Selection = XMSN_AMT,   // amt transmission
    .XMSN_Tailshaft_Teeth_Count = 16,
    .ENG_Torque_Limit_Gear_1 = 1450,    // 1450 Lb-Ft
    .ENG_Torque_Limit_Gear_2 = 1650,    // 1650 Lb-Ft
    .DRV_Powertrain_Style_Config = 0,
    .ENG_Max_Governor_Speed_Limit = 2100,
    .PROT_Coolant_Temp_Warning_Threshold = 215.0,
    .PROT_Coolant_Temp_Derate_Threshold = 225.0,
    .PROT_Oil_Pressure_Low_Shutoff_Enable = true,
    .ENG_Cylinder_Count_Config = 6,
    .PTO_Governor_Type_Config = 1,
    .PTO_Max_Engine_Speed = 1100,
    .EB_Engine_Brake_Level_Config = EB_LEVEL_NONE,
    .ATS_DPF_Regen_In_Transit_Permit = true,
    .ATS_DEF_Tank_Volume_Capacity = 15.0
};

bool checkCRC(const uint32_t calculatedCRC[6], const Subfile1 *sf1)
{
    for (int i = 0; i < 6; i++) {

        printf("Index %d: calculated = %u, expected = %u\n",
               i, calculatedCRC[i], sf1->T_CRC_CHECKSUM[i]);

        if (calculatedCRC[i] != sf1->T_CRC_CHECKSUM[i]) {
            printf("CRC mismatch at index %d\n", i);
            return false;
        }
    }

    return true;
}

void checkBootReason(const Subfile1 *sf1)
{
    // key on ignition cold
    if (sf1->T_BOOT_REASON_FLAG & COLD_BOOT) {
        printf("Cold boot detected.\n");
    }

    // key on ignition warm
    if (sf1->T_BOOT_REASON_FLAG & WARM_BOOT) {
        printf("Warm boot detected.\n");
    }

    if (sf1->T_BOOT_REASON_FLAG & WATCHDOG_TIMEOUT_RESET) {
        printf("WATCHDOG TIMEOUT detected.\n");
    }

    if (sf1->T_BOOT_REASON_FLAG & SOFTWARE_RESET) {
        printf("SOFTWARE RESET detected.\n");
    }

    if (sf1->T_BOOT_REASON_FLAG & BROWNOUT_RESET) {
        printf("BROWNOUT RESET detected.\n");
    }

    if (sf1->T_BOOT_REASON_FLAG & SERVICE_REQUEST) {
        printf("SERVICE_REQUEST detected.\n");
    }

}

void checkSaltKey(const Subfile1 *sf1, uint32_t providedSalt) {
    if (sf1->T_SECURITY_SEED_KEY_SALT != providedSalt) {
        printf("Security key does not match.\n");
    } else {
        printf("Success! Security key does match.\n");
    }
}

void maxVehicleSetLimit(const Subfile1 *sf1, ECMRuntimeState *runtime) {

    if (runtime->current_vehicle_speed > sf1->CC_Max_Vehicle_Speed_Set_Limit
        && runtime->cruise_control_active_switch == true) {
        runtime->is_fuel_cut_active = true;

        if (runtime->current_engine_brake_level == EB_LEVEL_NONE) {
            runtime->current_engine_brake_level = EB_LEVEL_LOW;
            runtime->active_engine_brake_cylinders = 2;
            runtime->VGT_Vane_Target_Duty_Cycle = 75;
        }
        else if (runtime->current_engine_brake_level == EB_LEVEL_LOW) {
            runtime->current_engine_brake_level = EB_LEVEL_MEDIUM;
            runtime->active_engine_brake_cylinders = 4;
            runtime->VGT_Vane_Target_Duty_Cycle = 85;
        }
        else if (runtime->current_engine_brake_level == EB_LEVEL_MEDIUM) {
            runtime->current_engine_brake_level = EB_LEVEL_HIGH;
            runtime->active_engine_brake_cylinders = 6;
            runtime->VGT_Vane_Target_Duty_Cycle = 95;
        } else {
            runtime->is_fuel_cut_active = false;
            runtime->current_engine_brake_level = EB_LEVEL_NONE;
            runtime->active_engine_brake_cylinders = 0;
            runtime->VGT_Vane_Target_Duty_Cycle = 40;
        }
    }
}

void minimumEngageSpeed(const Subfile1 *sf1, ECMRuntimeState *runtime) {

    runtime->cruise_control_engage_permitted =
        runtime->current_vehicle_speed >= sf1->CC_Minimum_Engage_Speed;
}

void maxEngageSpeed(const Subfile1 *sf1, ECMRuntimeState *runtime) {

    runtime->cruise_control_engage_permitted =
        runtime->current_vehicle_speed <= sf1->CC_Max_Vehicle_Speed_Set_Limit;

    if (runtime->cruise_control_active_switch && runtime->cruise_control_latched) {

        int16_t speed_delta = (int16_t)runtime->current_vehicle_speed -
        (int16_t)sf1->CC_Max_Vehicle_Speed_Set_Limit;

        if (speed_delta > 0) {

            runtime->is_fuel_cut_active = true;
            runtime->dynamic_requested_fuel_mass = 0;

            uint16_t overshoot_delta = (uint16_t)speed_delta;

            if (overshoot_delta <= 15) {
                runtime->current_engine_brake_level = EB_LEVEL_LOW;
                runtime->active_engine_brake_cylinders = 2;
                runtime->VGT_Vane_Target_Duty_Cycle = 75;
            }
            else if (overshoot_delta <= 30) {
                runtime->current_engine_brake_level = EB_LEVEL_MEDIUM;
                runtime->active_engine_brake_cylinders = 4;
                runtime->VGT_Vane_Target_Duty_Cycle = 85;
            } else {
                runtime->current_engine_brake_level = EB_LEVEL_HIGH;
                runtime->active_engine_brake_cylinders = 6;
                runtime->VGT_Vane_Target_Duty_Cycle = 95;
            }
        } else {
            runtime->is_fuel_cut_active = false;
            runtime->current_engine_brake_level = EB_LEVEL_NONE;
            runtime->active_engine_brake_cylinders = 0;
            runtime->VGT_Vane_Target_Duty_Cycle = 40;
        }
    } else {
        runtime->is_fuel_cut_active = false;
        runtime->current_engine_brake_level = EB_LEVEL_NONE;
        runtime->active_engine_brake_cylinders = 0;
    }
}