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

typedef struct NmF10D2D0b_PlayerState {
    u8 unk0;
    u8 pad1[0x2E1];
    u16 unk2E2;
    u8 unk2E4;
} NmF10D2D0b_PlayerState;

extern s8 D_80744504;
s32 func_80708DA4(s32, s16, s32, s32);

s32 func_80709344(s32 arg0) {
    s16 var_s0;
    s32 temp_lo;
    u16 temp_v1;
    s32 temp_v0;

    arg0 = arg0;
    var_s0 = 0;
    if ((s32)D_807FC928 > 0) {
        do {
            temp_lo = var_s0 * 0x2F0;
            temp_v0 = (s32)D_807FC924 + temp_lo;
            if (((NmF10D2D0b_PlayerState *)temp_v0)->unk0 != 0) {
                temp_v1 = ((NmF10D2D0b_PlayerState *)temp_v0)->unk2E2;
                if (!(temp_v1 & 0x20) && (((((NmF10D2D0b_PlayerState *)temp_v0)->unk2E4 != 0 || temp_v1 != 0) &&
                                           D_80744504 == 0) ||
                                          temp_v1 & 0x10)) {
                    arg0 = func_80708DA4(arg0, var_s0, (temp_lo ^ 0) + (s32)D_807FC924,
                                          (s32)D_807FC924);
                }
            }
            var_s0 += 1;
        } while (var_s0 < (s32)D_807FC928);
    }
    return arg0;
}


s32 func_8070943C(void) {
    s32 ret;

    ret = 4;
    return ((s32) D_807FC928 >= 2) ? 0xA : ret;
}



void func_80709464(u8 arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 product_factor;

    temp_v0 = func_8070943C();
    temp_v1 = (arg0 * 0x306) + (s32)D_807FC950;
    *(u8 *)(temp_v1 + 0x2FD) = 0;
    *(s8 *)(temp_v1 + 0x2FB) = (s8)(*(u8 *)(temp_v1 + 0x2FC) * (product_factor = temp_v0));
}


