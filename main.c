#include <stdio.h>

#include "include/ecm_RAM.h"
#include "include/subfile_1.h"
#include "include/canbus.h"


int main(void) {

    Subfile1 sf1 = {0};

    uint32_t calculatedCRC[6] = {0, 0, 0, 0, 0, 0}; // default values

    sf1.T_BOOT_REASON_FLAG = COLD_BOOT | WATCHDOG_TIMEOUT_RESET;
    sf1.T_SECURITY_SEED_KEY_SALT = 1234;

    bool result = checkCRC(calculatedCRC, &sf1);
    checkBootReason(&sf1);
    checkSaltKey(&sf1, 1234);
    ECMRuntimeState runtime = initializeECMRuntime();
    maxVehicleSetLimit(&sf1, &runtime);
    minimumEngageSpeed(&sf1, &runtime);
    maxEngageSpeed(&sf1, &runtime);

    if (result) {
        printf("CRC value matches expected CRC value\n");
    }

    int sock_fd = -1;
    struct sockaddr_in target_addr;

    if (canbus_init(&sock_fd, &target_addr, "127.0.0.1", 5000) != 0) {
        return 1;
    }

    ecm_canframe_t frame = {
        .id = 0x0CF00400,
        .dlc = 8,
        .data = {0}
    };

    if (canbus_send(sock_fd, &frame, &target_addr) != 0) {
        canbus_close(&sock_fd);
        return 1;
    }

    printf("CAN frame transmitted successfully.\n");

    canbus_close(&sock_fd);

    return 0;
}
