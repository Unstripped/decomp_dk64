#include "common.h"
#include "actor.h"

void *func_80610FE8(s32);
s32 func_8066B0F8(s32, s32, s32, s32);
extern u8 *D_807FC7C0;

#pragma GLOBAL_ASM("asm/global/nonmatchings/9BF30/func_80697230.s")

void func_806978FC(void) {
    s16 i;
    s16 j;

    i = 0;
    D_807FC7C0 = func_80610FE8(0xC0);
    for (j = 0; j < 0x30; j++) {
        ((s32 *)D_807FC7C0)[i++] = func_8066B0F8(0x19, i + 0x1654, 1, 1);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/9BF30/func_80697988.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/9BF30/func_80697CEC.s")
