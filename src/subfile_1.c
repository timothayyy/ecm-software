#include <stdio.h>
#include "../include/subfile_1.h"

uint32_t calculatedCRC[6] = {0, 0, 0, 0, 0, 0};
uint8_t bootReason = 0;

Subfile1 sf1 = {
    .SC_OPTION_NUM = 1001,
    .DO_OPTION_NUM = 1002
};

bool checkCRC(uint32_t calculatedCRC[6], const Subfile1 *sf1)
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


}