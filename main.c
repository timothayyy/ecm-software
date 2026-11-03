#include <stdio.h>
#include "subfile_1.h"

int main(void) {

    Subfile1 sf1 = {0};

    uint32_t calculatedCRC[6] = {0, 0, 0, 0, 0, 0}; // default values

    bool result = checkCRC(calculatedCRC, &sf1);

    if (result) {
        printf("CRC value matches expected CRC value\n");
    }

    return 0;
}
