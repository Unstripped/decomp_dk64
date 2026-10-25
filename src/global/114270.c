#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern void *D_807FC924;
extern s32 D_8076A0A8;
extern u8 D_80755314;
extern u8 D_80755318;

extern u16 *D_807550E0;
extern u8 D_807FDA1A;
extern u8 D_807FDA1C;
extern u8 D_807FDA28;
extern u8 D_807FDA30;

void func_8070F570(void) {
    s16 i;

    *D_807550E0 = 0;
    D_807FDA1C = 6;
    for (i = 0; i < 0x80; i++) {
        (&D_807FDA30)[i] = i;
    }
    D_807FDA1A = 0x7F;
    D_807FDA28 = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_8070F5CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_8070FA58.s")

typedef struct M114aAngle {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 unk14[0x9C];
    u8 unkB0;
    u8 unkB1;
} M114aAngle;

void func_8070FC40(M114aAngle *arg0) {
    if (315.0f < arg0->unk4) {
        arg0->unk4 = arg0->unk4 - 315.0f + 2.0f;
    }
    if (arg0->unk4 < 2.0f) {
        arg0->unk4 = 315.0f - arg0->unk4;
    }
    arg0->unk4 = (s32)arg0->unk4 % 320;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_8070FCCC.s")

void func_8070FA58(M114aAngle *);

s32 func_8071006C(M114aAngle *arg0) {
    s32 var_v1;
    f32 new_var;
    s32 temp_v0;
    u8 temp_v0_2;

    func_8070FA58(arg0);
    func_8070FC40(arg0);
    temp_v0 = arg0->unkB0;
    var_v1 = (s32)temp_v0 < 0xF;
    arg0->unkB0 = (u8)(temp_v0 + 1);
    arg0->unk8 = (f32)arg0->unk4;
    temp_v0 = 0x50;
    if (var_v1 == 0) {
        temp_v0_2 = arg0->unkB1;
        if ((s32)temp_v0_2 >= 0x50) {
            arg0->unkB1 = (u8)(temp_v0_2 - temp_v0);
        }
    }
    new_var = (f32)((1.0 / ((f64)arg0->unk10 * 4.0)) * 60.0);
    var_v1 = 0;
    arg0->unkC = (f32)((f64)arg0->unkC + ((f64)((30.0f - (new_var - 30.0f)) + 30.0f) * 0.2));
    if (arg0->unkC > 240.0f) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        var_v1 = (s32)arg0->unkB1 < 0x50;
    }
    return var_v1 & 0xFF;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_80710174.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_807102AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_807103E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_807105D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_80710CA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_80711410.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_80711950.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_80711BD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_80711F90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_807122B4.s")
