#ifndef ECM_SUBFILE_1_H
#define ECM_SUBFILE_1_H

#include <stdint.h>

typedef struct {
    uint32_t T_CRC_CHECKSUM[6];
    uint8_t T_BOOT_REASON_FLAG;
    uint32_t T_SECURITY_SEED_KEY_SALT;
} Subfile1;

bool checkCRC(uint32_t calculatedCRC[6], const Subfile1 *sf1);

#endif //ECM_SUBFILE_1_H
