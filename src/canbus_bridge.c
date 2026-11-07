#include "canbus.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int bridge_init(void) {

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock_fd < 0) {
        perror("Failed to create bridge socket");
        return -1;
    }

    struct sockaddr_in local_addr = {0};

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(5000);
    local_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) {
        perror("Failed to bind socket");
        close(sock_fd);
        return -1;
    }
    return sock_fd;
}

int bridge_recvfrom(int sock_fd, ecm_canframe_t *frame) {

    ssize_t bytes_received = recvfrom(
        sock_fd,
        frame,
        sizeof(ecm_canframe_t),
        0,
        NULL,
        NULL
    );

    if (bytes_received < 0) {
        perror("Failed to receive frame");
        return -1;
    }

    if (bytes_received != sizeof(ecm_canframe_t)) {
        fprintf(stderr, "Invalid CAN frame size: %zd bytes\n", bytes_received);
        return -1;
    }

    if (frame->dlc > 8) {
        fprintf(stderr, "Invalid received CAN DLC\n");
        return -1;
    }

printf("Received CAN ID: 0x%08X | DLC: %u\n",
    frame->id, frame->dlc);

return 0;
}

int main(void) {

    int sock_fd = bridge_init();

    if (sock_fd < 0) {
        return 1;
    }

    ecm_canframe_t frame = {0};

    if (bridge_recvfrom(sock_fd, &frame) != 0) {
        close(sock_fd);
        return 1;
    }

    close(sock_fd);

    return 0;
}
