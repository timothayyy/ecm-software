#ifndef ECM_SUBFILE_1_H
#define ECM_SUBFILE_1_H

#include <stdint.h>

typedef struct {
    uint32_t T_CRC_CHECKSUM[6];
    uint32_t T_SECURITY_SEED_KEY_SALT;
    uint16_t SC_OPTION_NUM;
    uint16_t DO_OPTION_NUM;
    uint8_t  T_BOOT_REASON_FLAG;
} Subfile1;

typedef enum {
    COLD_BOOT                  = 1 << 0, // 00000001
    WARM_BOOT                  = 1 << 1, // 00000010
    WATCHDOG_TIMEOUT_RESET     = 1 << 2, // 00000100
    SOFTWARE_RESET             = 1 << 3, // 00001000
    BROWNOUT_RESET             = 1 << 4, // 00010000
} BootReason;

bool checkCRC(uint32_t calculatedCRC[6], const Subfile1 *sf1);
void checkBootReason(const Subfile1 *sf1);

#endif //ECM_SUBFILE_1_H
