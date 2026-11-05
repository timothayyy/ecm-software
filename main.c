#include <stdio.h>

#include "ecm_RAM.h"
#include "include/subfile_1.h"

int main(void) {

    Subfile1 sf1 = {0};

    uint32_t calculatedCRC[6] = {0, 0, 0, 0, 0, 0}; // default values

    sf1.T_BOOT_REASON_FLAG = COLD_BOOT | WATCHDOG_TIMEOUT_RESET;
    sf1.T_SECURITY_SEED_KEY_SALT = 1234;

    bool result = checkCRC(calculatedCRC, &sf1);
    checkBootReason(&sf1);
    checkSaltKey(&sf1, 1234);
    ECMRuntimeState runtime = initializeECMRuntimeState();
    void maxVehicleSetLimit(const Subfile1 *sf1,
                            const ECMRuntimeState *state);

    if (result) {
        printf("CRC value matches expected CRC value\n");
    }

    return 0;
}
