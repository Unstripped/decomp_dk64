#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

#pragma GLOBAL_ASM("asm/global/nonmatchings/10D2D0/func_807085D0.s")

typedef struct R1F10D2D0_InitData {
    f32 unk0;
    s16 unk4;
    s16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} R1F10D2D0_InitData;

extern s32 D_807FBB64;
extern s32 func_807142D8();

void func_80708BB8(R1F10D2D0_InitData *arg0) {
    if (D_807FBB64 & 0x800) {
        arg0->unk6 = 0x20;
    } else {
        arg0->unk6 = 1;
    }
    if (func_807142D8() != 0) {
        arg0->unk6 = 0x20;
    }
    arg0->unkA = 0;
    arg0->unk8 = 0;
    arg0->unk4 = 0;
    arg0->unk0 = 4.0f;
}



#pragma GLOBAL_ASM("asm/global/nonmatchings/10D2D0/func_80708C24.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/10D2D0/func_80708DA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/10D2D0/func_80709344.s")



s32 func_8070943C(void) {
    s32 ret;

    ret = 4;
    return ((s32) D_807FC928 >= 2) ? 0xA : ret;
}



#pragma GLOBAL_ASM("asm/global/nonmatchings/10D2D0/func_80709464.s")


