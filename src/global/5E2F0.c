#include "common.h"
#include "actor.h"

extern u8 D_807F7EF8;
extern s16 D_807F7EFA;
extern s16 D_807F7EFC;

void func_806595F0(u8 arg0) {
    D_807F7EF8 = arg0;
}

void func_80659600(s16 arg0) {
    D_807F7EFA = arg0;
}

void func_80659610(s16 arg0) {
    D_807F7EFC = arg0;
}

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;

void func_80659620(f32 *arg0, f32 *arg1, f32 *arg2, s16 arg3) {
    *arg0 = D_8076A0B4[arg3];
    *arg1 = D_8076A0B8[arg3];
    *arg2 = D_8076A0BC[arg3];
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_80659670.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065996C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_80659DB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_80659F7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065A570.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065A648.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065A654.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065A660.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065A6F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065A708.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065A884.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065BAA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065BE74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065BF18.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065C240.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/func_8065C334.s")
