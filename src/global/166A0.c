#include "common.h"

extern s32 D_80746A40;

#pragma GLOBAL_ASM("asm/global/nonmatchings/166A0/func_806119A0.s")

void func_806119F0(s32 arg0) {
    D_80746A40 = arg0;
}

s32 func_806119A0(void);

#pragma GLOBAL_ASM("asm/global/nonmatchings/166A0/func_806119FC.s")

s32 func_80611A44(void) {
    return func_806119A0() & 0x7FFFFFFF;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/166A0/func_80611A70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/166A0/func_80611BB4.s")
