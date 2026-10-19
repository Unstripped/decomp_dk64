#include "PR/os_internal.h"

#if BUILD_VERSION >= VERSION_J

#define ADDRESS_CRC_MESSAGE_LENGTH 10
#define ADDRESS_CRC_LENGTH 5
#define ADDRESS_CRC_GENERATOR 0x15
#define ADDRESS_CRC_MASK ((1 << ADDRESS_CRC_LENGTH) - 1)

u8 __osContAddressCrc(u16 addr) {
    u32 temp = 0;
    u32 i = (1 << ADDRESS_CRC_MESSAGE_LENGTH);

    do {
        temp <<= 1;

        if ((u32)addr & i) {
            if (temp & (1 << ADDRESS_CRC_LENGTH)) {
                temp ^= ADDRESS_CRC_GENERATOR - 1;
            } else {
                ++temp;
            }
        } else if (temp & (1 << ADDRESS_CRC_LENGTH)) {
            temp ^= ADDRESS_CRC_GENERATOR;
        }

        i >>= 1;
    } while (i != 0);

    i = ADDRESS_CRC_LENGTH;
    do {
        temp <<= 1;
        if (temp & (1 << ADDRESS_CRC_LENGTH)) {
            temp ^= ADDRESS_CRC_GENERATOR;
        }
    } while (--i != 0);

    return temp & ADDRESS_CRC_MASK;
}

#define DATA_CRC_MESSAGE_BYTES 32
#define DATA_CRC_LENGTH 8
#define DATA_CRC_GENERATOR 0x85

u8 __osContDataCrc(u8* data) {
    u32 temp = 0;
    u32 i;
    u32 j;

    for (i = DATA_CRC_MESSAGE_BYTES; i; --i) {
        for (j = (1 << (DATA_CRC_LENGTH - 1)); j; j >>= 1) {
            temp <<= 1;

            if ((*data & j) != 0) {
                if ((temp & (1 << DATA_CRC_LENGTH)) != 0) {
                    temp ^= DATA_CRC_GENERATOR - 1;
                } else {
                    ++temp;
                }
            } else if (temp & (1 << DATA_CRC_LENGTH)) {
                temp ^= DATA_CRC_GENERATOR;
            }
        }

        data++;
    }
    do {
        temp <<= 1;

        if (temp & (1 << DATA_CRC_LENGTH)) {
            temp ^= DATA_CRC_GENERATOR;
        }
    } while (++i < DATA_CRC_LENGTH);

    return temp;
}

#else

u8 __osContAddressCrc(u16 addr) {
    u8 temp = 0;
    u8 temp2;
    int i;
    
    for (i = 0; i < 16; i++) {
        temp2 = (temp & 0x10) ? 0x15 : 0;

        temp <<= 1;
        temp |= (u8)((addr & 0x400) ? 1 : 0);
        addr <<= 1;
        temp ^= temp2;
    }
    
    return temp & 0x1f;
}

u8 __osContDataCrc(u8 *data) {
    u8 temp = 0;
    u8 temp2;
    int i;
    int j;
    
    for (i = 0; i < 32; i++) {
        for (j = 7; j > -1; j--) {
            temp2 = (temp & 0x80) ? 0x85 : 0;
            
            temp <<= 1;
            
            if (i == 32) {
                temp &= -1;
            } else {
                temp |= ((*data & (1 << j)) ? 1 : 0);
            }
            
            temp ^= temp2;
        }
        data++;
    }
    return temp;
}

#endif
