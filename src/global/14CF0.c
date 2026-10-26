#include "common.h"

extern u8 D_80741F40[];
extern u8 D_807432D0[];
extern u8 D_80760840[];
extern u8 D_80760C60[];
extern void *D_807F0570[];
extern void *D_807F0588[];

void func_8060FFF0(void) {
    D_807F0570[0] = D_807432D0;
    D_807F0588[0] = D_80760C60;
    D_807F0570[1] = D_80741F40;
    D_807F0588[1] = D_80760840;
    D_807F0570[2] = D_80741F40;
    D_807F0588[2] = D_80760840;
    D_807F0570[3] = D_80741F40;
    D_807F0588[3] = D_80760840;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/14CF0/func_80610044.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/14CF0/func_80610268.s")
