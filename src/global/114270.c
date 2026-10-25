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
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    s16 unk20;
    f32 unk24;
    f32 unk28;
    u8 unk2C[0x84];
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
f32 func_80612794(s16);


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

s32 func_80710174(M114aAngle *arg0) {
    f32 new_var2;
    s32 var_v1;
    f32 new_var;
    s32 temp_v0;
    u8 temp_v0_2;

    func_8070FA58(arg0);
    new_var2 = func_80612794(arg0->unk20);
    arg0->unk4 = (f32)(arg0->unk4 + (new_var2 * arg0->unk28));
    func_8070FC40(arg0);
    arg0->unk8 = (f32)arg0->unk4;
    new_var = (f32)((1.0 / ((f64)arg0->unk10 * 4.0)) * 8.0);
    temp_v0 = arg0->unkB0;
    var_v1 = 0x3D;
    var_v1 = (s32)temp_v0 < var_v1;
    arg0->unk20 = (s16)(arg0->unk20 + 0x14);
    arg0->unkB0 = (u8)(temp_v0 + 1);
    arg0->unkC = (f32)((f64)arg0->unkC + ((f64)((10.0f - (new_var - 10.0f)) + 10.0f) * 0.25));
    temp_v0 = 0xA;
    if (var_v1 == 0) {
        temp_v0_2 = arg0->unkB1;
        if ((s32)temp_v0_2 >= 0xA) {
            arg0->unkB1 = (u8)(temp_v0_2 - temp_v0);
        }
    }
    var_v1 = 0;
    if (arg0->unkC > 240.0f) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        var_v1 = (s32)arg0->unkB1 < 0xA;
    }
    return var_v1 & 0xFF;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_807102AC.s")


#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_807103E0.s")

#ifdef NON_MATCHING
typedef struct L105D4TextureDescriptor {
    u8 unk0[8];
    u8 format;
    u8 type;
    u8 unkA[0xA];
} L105D4TextureDescriptor;

extern u8 D_80755264;
extern u32 D_807FD9F0[];
extern u8 D_807FDA18;
extern u8 D_807FDA19;

#define L105D4_TEXTURE ((L105D4TextureDescriptor *)((u8 *)&D_80755264 + (D_807FDA1C * 0x14)))

Gfx *func_807105D4(Gfx *arg0, s32 arg1) {
    arg1 &= 0xFF;
    switch (L105D4_TEXTURE->type) {
    case 1:
        gDPLoadTextureBlock(arg0++, D_807FD9F0[arg1], L105D4_TEXTURE->format, G_IM_SIZ_8b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 2:
        gDPLoadTextureBlock(arg0++, D_807FD9F0[arg1], L105D4_TEXTURE->format, G_IM_SIZ_16b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 3:
        gDPLoadTextureBlock(arg0++, D_807FD9F0[arg1], L105D4_TEXTURE->format, G_IM_SIZ_32b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    }
    return arg0;
}

#undef L105D4_TEXTURE
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_807105D4.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_80710CA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_80711410.s")

typedef struct R114cPlayerView {
    u8 pad0[0x2C4];
    f32 unk2C4;
} R114cPlayerView;

extern s32 D_807FBB60;
extern s16 D_807FDA1E;
extern u8 D_807FDA1B;
u32 func_806119A0(void);
f32 func_80612D10(f32);
void func_8070F5CC(u8, s16, f32, s16, s32, s32);
void func_80710CA0(void);
void renderCallbacksRegister(void *, void *, s32);

void func_80711950(f32 arg0, s16 arg1, s16 arg2) {
    s32 random;
    s32 count;
    s32 i;
    f32 value;

    if (D_807FBB60 & 0x10) {
        D_807FDA1E = (s16)(func_80612D10(((R114cPlayerView *)D_807FC924)->unk2C4) * arg1);
        if (arg0 < 1.0) {
            arg0 *= 100.0f;
            random = func_806119A0() / 10000;
            if ((f32)(s32)((u32)random % 100U) < arg0) {
                count = 1;
            } else {
                count = 0;
            }
        } else {
            count = (s32)arg0;
        }
        D_807FDA1B = 0xFF;
        for (i = 0; i < count; i++) {
            random = func_806119A0() / 10000;
            value = (f32)((f64)((u32)random % 125U) / 1000.0);
            random = func_806119A0() / 10000;
            func_8070F5CC(1, arg2, (f32)((f64)value + 0.075), (s16)(s32)((u32)random % 320U), -10, 200);
        }
        if (*D_807550E0 != 0) {
            renderCallbacksRegister(&func_80710CA0, 0, 1);
        }
    }
}




#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_80711BD0.s")


void func_80711F90(f32 arg0, s16 arg1, s32 arg2, s16 arg3, f32 arg4) {
    f32 temp_fs1;
    s32 var_s0;
    s32 var_s4;

    D_807FDA1E = (s16)(s32)(func_80612D10(((R114cPlayerView *)D_807FC924)->unk2C4) * (f32)arg1);
    if ((f64)arg0 < 1.0) {
        arg0 *= 100.0f;
        if ((f32)((s32)((s32)(func_80611A44() >> 0xF) % 32767) % 100) < arg0) {
            var_s4 = 1;
        } else {
            var_s4 = 0;
        }
    } else {
        var_s4 = (s32)arg0;
    }
    D_807FDA1B = 0xFF;
    var_s0 = 0;
    if (var_s4 > 0) {
        do {
            temp_fs1 = (f32)((s32)((s32)(func_80611A44() >> 0xF) % 32767) % 320);
            func_8070F5CC(2, arg3, (f32)(((f64)(f32)((f64)((s32)((s32)(func_80611A44() >> 0xF) % 32767) % 125) / 800.0) + 0.1) * 2.5 * (f64)arg4), (s16)(s32)temp_fs1, -10, 0xFF);
            var_s0 += 1;
        } while (var_s0 != var_s4);
    }
    if (*D_807550E0 != 0) {
        renderCallbacksRegister(&func_80710CA0, 0, 1);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/114270/func_807122B4.s")
