#include "canbus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int canbus_init(int *sock_fd, struct sockaddr_in *target_addr,
    const char *ip, int port) {

    *sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (*sock_fd < 0) {
        perror("Can't create socket");
        return -1;
    }

    memset(target_addr, 0, sizeof(struct sockaddr_in));

    target_addr->sin_family = AF_INET;
    target_addr->sin_port = htons(port);
    target_addr->sin_addr.s_addr = inet_addr(ip);

    return 0;
}

int canbus_send(int sock_fd, struct ecm_canframe_t *frame, struct sockaddr_in *target_addr) {

    ssize_t bytes_sent = sendto(
        sock_fd,
        frame,
        sizeof(ecm_canframe_t),
        0,
        (struct sockaddr *) target_addr,
        sizeof(struct sockaddr_in)
        );

    if (bytes_sent < 0) {
        perror("Can't send frame");
        return -1;
    }

    if (bytes_sent != sizeof(ecm_canframe_t)) {
        perror("Can't send frame");
    }

    return 0;
}

void canbus_close(int *sock_fd) {

    if (*sock_fd >= 0) {
        close(*sock_fd);
        
        *sock_fd = -1;
    }
}
