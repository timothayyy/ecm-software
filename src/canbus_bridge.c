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

int bridge_tcp_init(void) {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd < 0) {
        perror("Failed to create bridge socket");
        return -1;
    }

    struct sockaddr_in local_addr = {0};

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(5001);
    local_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) {
        perror("Failed to bind socket");
        close(sock_fd);
        return -1;
    }

    if (listen(sock_fd, SOMAXCONN) < 0) {
        perror("Failed to listen on socket");
        close(sock_fd);
        return -1;
    }

    return sock_fd;
}

int main(void) {

    printf("Starting UDP receiver...\n");
    fflush(stdout);

    int udp_fd = bridge_init();

    if (udp_fd < 0) {
        return 1;
    }

    ecm_canframe_t frame = {0};

    printf("Waiting for CAN frame from ECM...\n");
    fflush(stdout);

    if (bridge_recvfrom(udp_fd, &frame) != 0) {
        close(udp_fd);
        return 1;
    }

    printf("CAN frame received successfully!\n");
    fflush(stdout);

    printf("Starting TCP server...\n");
    fflush(stdout);

    int listen_fd = bridge_tcp_init();

    if (listen_fd < 0) {
        close(udp_fd);
        return 1;
    }

    printf("Waiting for SavvyCAN connection...\n");
    fflush(stdout);

    if (accept(listen_fd, NULL, NULL) < 0) {
        close(listen_fd);
        close(udp_fd);
        return 1;
    }

    printf("SavvyCAN connected!\n");

    close(listen_fd);
    close(udp_fd);

    return 0;
}