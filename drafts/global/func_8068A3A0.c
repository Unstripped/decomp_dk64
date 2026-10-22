// func_8068A3A0 (src/global/8F050.c): Closest diff: loop structure matches; IDO swaps a0 and a2 in leaf register allocation
#include "common.h"

extern u8 D_80750100[];

s32 func_8068A3A0(s32 arg0, u32 *arg1) {
    s32 found = 0;
    u32 i = 0;

    *arg1 = 0;
    do {
        if (arg0 == *(s16 *)(D_80750100 + i * 20)) {
            *arg1 = i;
            found = 1;
        } else {
            *arg1 = ++i;
        }
    } while (!found && *arg1 < 7);
    return found;
}
