#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;

#pragma GLOBAL_ASM("asm/global/nonmatchings/1135F0/func_8070E8F0.s")

extern s16 D_807FD9D0;
extern s16 D_807FD9D2;
extern u8 D_807FD9D4;
extern u8 D_807FD9D5;

void func_8070F2C8(s16 arg0, s16 arg1, s8 arg2, s8 arg3) {
    D_807FD9D0 = arg0;
    D_807FD9D2 = arg1;
    D_807FD9D4 = arg2;
    D_807FD9D5 = arg3;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/1135F0/func_8070F2FC.s")
