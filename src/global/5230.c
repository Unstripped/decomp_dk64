#include "common.h"

extern u16 D_80744734[];
extern s32 D_8076A0A8;
extern s32 D_80767CC4;

// .bss 0x8076AF00-0x8076AF20
s16 D_8076AF00[7];
u16 D_8076AF0E;
s32 D_8076AF10;
u8 D_8076AF14;
u8 D_8076AF15;
u16 D_8076AF16;
u8 D_8076AF18[8];

s32 func_80600530(void) {
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    while (!found && i < 8) {
        if (D_8076A0A8 == D_80744734[i]) {
            found = 1;
        } else {
            i++;
        }
    }
    if (!found) {
        i = 0;
    }
    return i;
}

void frameTimingReset(s32 arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_8076AF00[i] = 2;
    }

    D_8076AF10 = D_80767CC4;
    switch (arg0) {
    case 0x6:
    case 0x1B:
    case 0x27:
    case 0x28:
    case 0x37:
    case 0x4C:
    case 0x6A:
    case 0x98:
    case 0x99:
    case 0xAC:
    case 0xD0:
        D_8076AF14 = 0;
        break;
    default:
        D_8076AF14 = 1;
        break;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/5230/frameTimingUpdate.s")
