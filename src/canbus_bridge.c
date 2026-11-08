
#include "canbus.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

int bridge_init(void) {

    int sock_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (sock_fd < 0) {
        perror("Failed to create SocketCAN socket");
        return -1;
    }

    unsigned int ifindex = if_nametoindex("vcan0");

    if (ifindex == 0) {
        perror("Failed to locate vcan0");
        close(sock_fd);
        return -1;
    }

    struct sockaddr_can local_addr = {0};

    local_addr.can_family = AF_CAN;
    local_addr.can_ifindex = (int)ifindex;

    if (bind(sock_fd,
             (struct sockaddr *)&local_addr,
             sizeof(local_addr)) < 0) {

        perror("Failed to bind SocketCAN socket");
        close(sock_fd);
        return -1;
    }

    return sock_fd;
}

int bridge_recvfrom(int sock_fd, ecm_canframe_t *frame) {

    struct can_frame linux_frame = {0};

    ssize_t bytes_received = read(
        sock_fd,
        &linux_frame,
        sizeof(linux_frame)
    );

    if (bytes_received < 0) {
        perror("Failed to receive CAN frame");
        return -1;
    }

    if (bytes_received != sizeof(linux_frame)) {
        fprintf(stderr, "Invalid CAN frame size\n");
        return -1;
    }

    if (linux_frame.can_id & CAN_ERR_FLAG) {
        fprintf(stderr, "CAN error frame received\n");
        return -1;
    }

    frame->id = (linux_frame.can_id & CAN_EFF_FLAG)
        ? (linux_frame.can_id & CAN_EFF_MASK)
        : (linux_frame.can_id & CAN_SFF_MASK);

    frame->dlc = linux_frame.len;

    if (frame->dlc > 8) {
        fprintf(stderr, "Invalid CAN DLC\n");
        return -1;
    }

    memcpy(frame->data, linux_frame.data, frame->dlc);

    printf("Received CAN ID: 0x%08X | DLC: %u\n",
           (unsigned int)frame->id, frame->dlc);

    return 0;
}

int main(void) {

    printf("Starting Linux SocketCAN receiver...\n");

    int can_fd = bridge_init();

    if (can_fd < 0) {
        return 1;
    }

    printf("Listening on vcan0...\n");

    ecm_canframe_t frame = {0};

    if (bridge_recvfrom(can_fd, &frame) != 0) {
        close(can_fd);
        return 1;
    }

    printf("CAN frame received successfully!\n");

    for (unsigned int i = 0; i < frame.dlc; i++) {
        printf("%02X ", frame.data[i]);
    }

    printf("\n");

    close(can_fd);
    return 0;
}
