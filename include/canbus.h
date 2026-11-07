#ifndef ECM_CANBUS_H
#define ECM_CANBUS_H

#include <stdint.h>

#pragma pack(push, 1)

typedef struct {
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];
} ecm_canframe_t;

#pragma pack(pop)

#endif //ECM_CANBUS_H
