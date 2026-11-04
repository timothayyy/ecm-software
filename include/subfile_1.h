#ifndef ECM_SUBFILE_1_H
#define ECM_SUBFILE_1_H

#include <stdint.h>

typedef enum {
    COLD_BOOT                  = 1 << 0, // 00000001
    WARM_BOOT                  = 1 << 1, // 00000010
    WATCHDOG_TIMEOUT_RESET     = 1 << 2, // 00000100
    SOFTWARE_RESET             = 1 << 3, // 00001000
    BROWNOUT_RESET             = 1 << 4, // 00010000
    SERVICE_REQUEST            = 1 << 5  // 00100000
} BootReason;

typedef enum {
    VSS_MAGNETIC = 0,
    VSS_J1939 = 1
} VSS_SensorType;

typedef enum {
    XMSN_MANUAL = 0,
    XMSN_AUTO = 1,
    XMSN_AMT = 2
} XMSN_Type;

typedef enum {
    EB_LEVEL_NONE = 0,
    EB_LEVEL_LOW = 1,
    EB_LEVEL_MEDIUM = 2,
    EB_LEVEL_HIGH = 3
} EB_LevelConfig;

typedef struct {
    uint32_t T_CRC_CHECKSUM[6];
    uint32_t T_SECURITY_SEED_KEY_SALT;
    uint16_t SC_OPTION_NUM;
    uint16_t DO_OPTION_NUM;
    uint8_t T_BOOT_REASON_FLAG;
    uint16_t CC_Max_Vehicle_Speed_Set_Limit;
    uint16_t CC_Minimum_Engage_Speed;
    uint16_t CC_Max_Vehicle_Speed;
    uint16_t VSS_Tire_Revolution_Per_Mile;
    double Axle_Primary_Ratio;
    VSS_SensorType VSS_Sensor_Type_Config;
    uint16_t ISD_Idle_Shutdown_Time_Delay;
    double ISD_Ambient_Air_Temp_Low_Override;
    double ISD_Ambient_Air_Temp_High_Override;
    uint16_t ENG_Base_Target_Idle_Speed;
    bool ENG_Battery_Voltage_Low_Idle_Up_Enable;
    XMSN_Type XMSN_Type_Selection;
    uint16_t XMSN_Tailshaft_Teeth_Count;
    uint16_t ENG_Torque_Limit_Gear_1;
    uint16_t ENG_Torque_Limit_Gear_2;
    uint8_t DRV_Powertrain_Style_Config;
    uint16_t ENG_Max_Governor_Speed_Limit;
    double PROT_Coolant_Temp_Warning_Threshold;
    double PROT_Coolant_Temp_Derate_Threshold;
    bool PROT_Oil_Pressure_Low_Shutoff_Enable;
    uint8_t ENG_Cylinder_Count_Config;
    uint8_t PTO_Governor_Type_Config;
    uint16_t PTO_Max_Engine_Speed;
    EB_LevelConfig EB_Engine_Brake_Level_Config;
    bool ATS_DPF_Regen_In_Transit_Permit;
    double ATS_DEF_Tank_Volume_Capacity;
    bool cruise_active;
} Subfile1;

bool checkCRC(const uint32_t calculatedCRC[6], const Subfile1 *sf1);
void checkBootReason(const Subfile1 *sf1);
void checkSaltKey(const Subfile1 *sf1, uint32_t providedSalt);

#endif //ECM_SUBFILE_1_H
