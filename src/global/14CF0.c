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

extern s8 D_80746834;
extern OSMesgQueue D_807659E8;
extern u8 D_807F059C[];

void func_80610268(s32 arg0) {
    void *sp34;
    s32 temp_t8;

    do {
        D_80746834 = 8;
        osRecvMesg(&D_807659E8, &sp34, 1);
        D_80746834 = 0;
        D_807F059C[(u32)sp34 >> 0x10] = 0;
        temp_t8 = ((s32)sp34 & 0xFFFF) & 0xFFFF;
        sp34 = (void *)temp_t8;
    } while (temp_t8 != arg0);
}
