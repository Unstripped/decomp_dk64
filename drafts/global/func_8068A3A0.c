// func_8068A3A0 (src/global/8F050.c): Closest diff: all 25 insns, loop, delay slot store, dead store match; IDO swaps a0 and a2 in leaf register allocation
#include "common.h"

typedef struct Act8CA_Struct_8F050 {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    u8 unk8;
    u8 unk9;
    s16 unkA;
    s32 unkC[2];
} Act8CA_Struct_8F050;

extern Act8CA_Struct_8F050 D_80750100[];

s32 func_8068A3A0(s32 arg0, s32 *arg1) {
    s32 found = 0;
    u32 i = 0;
    u32 next;

    *arg1 = 0;
    do {
        next = i + 1;
        if (arg0 == D_80750100[i].unk0) {
            found = 1;
            next = i;
        } else {
            *arg1 = next;
            i = next;
        }
    } while (next < 7 && !found);
    return found;
}
