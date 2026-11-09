#include "common.h"
#include "proto/global/13C920.h"

extern u8 D_807FF0F0;
extern u8 D_807FF0F1;
extern u8 D_807FF0F2;
extern u8 D_807FF0F4;
extern u8 D_807FF0F6;
extern u8 D_807FF0F8;


void configureCSPOutputMode(u8 mode) {
    s32 i;

    D_807FF0F0 = 0;
    D_807FF0F1 = 0;
    D_807FF0F2 = 0;
    switch (mode) {
        case 1:
            D_807FF0F1 = 1;
            break;
        case 3:
            D_807FF0F2 = 1;
            break;
        case 4:
            D_807FF0F0 = 1;
            break;
    }
    i = 0;
    do {
        updateCSPOutputChannelMode(i, 0);
    } while ((i += 1) < 2);
}

void updateCSPOutputChannelMode(s32 chan, s32 outputMode) {
    if (outputMode == 0) {
        outputMode = *(&D_807FF0F8 + chan);
    }
    *(&D_807FF0F4 + chan) = 0;
    *(&D_807FF0F6 + chan) = 0;
    switch (outputMode) {
        case 2:
            if (D_807FF0F0 != 0) {
                *(&D_807FF0F6 + chan) = 1;
            }
            break;
        case 3:
            if (D_807FF0F0 != 0) {
                *(&D_807FF0F4 + chan) = 1;
            }
            break;
        case 4:
            if (D_807FF0F1 == 0) {
                *(&D_807FF0F4 + chan) = 1;
            }
            break;
        case 5:
            if (D_807FF0F1 == 0) {
                *(&D_807FF0F4 + chan) = 1;
                *(&D_807FF0F6 + chan) = 1;
            }
            break;
    }
    *(&D_807FF0F8 + chan) = outputMode;
}
