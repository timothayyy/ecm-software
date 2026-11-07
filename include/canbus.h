#ifndef ECM_CANBUS_H
#define ECM_CANBUS_H

#include <stdint.h>
#include <netinet/in.h>

#pragma pack(push, 1)

typedef struct {
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];
} ecm_canframe_t;

#pragma pack(pop)

int canbus_init(int *sock_fd, struct sockaddr_in *taget_addr,
    const char *ip, int port);

int canbus_send(int sock_fd, ecm_canframe_t *frame,
    struct sockaddr_in *target_addr);

void canbus_close(int *sock_fd);


#endif //ECM_CANBUS_H
