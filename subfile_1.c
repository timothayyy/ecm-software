#include <stdio.h>
#include "subfile_1.h"

Subfile1 sf1 = {0};
uint32_t calculatedCRC[6] = {0, 0, 0, 0, 0, 0};

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