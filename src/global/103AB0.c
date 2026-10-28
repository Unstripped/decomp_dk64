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

extern Gfx D_1000118;
extern Mtx D_2000080;

typedef struct {
    u8 unk0[0x250];
    u8 unk250[2][0x10];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 unk278[0x78];
} AaView;

#define AA_VIEW(i) ((AaView *)((u8 *)D_807FC924 + (i) * 0x2F0))

Gfx *func_806FEDB0(Gfx *arg0, u8 arg1) {
    gDPPipeSync(arg0++);
    gSPViewport(arg0++, osVirtualToPhysical(((AaView *)D_807FC924)[arg1].unk250[D_807444FC]));
    {
        Gfx *_g = (Gfx *)(arg0++);
        _g->words.w0 = ((s32)((f32)AA_VIEW(arg1)->unk272 * 4.0f) & 0xFFF) | 0xED000000 |
                       (((s32)((f32)AA_VIEW(arg1)->unk270 * 4.0f) & 0xFFF) << 12);
        _g->words.w1 = ((s32)((f32)AA_VIEW(arg1)->unk276 * 4.0f) & 0xFFF) |
                       (((s32)((f32)AA_VIEW(arg1)->unk274 * 4.0f) & 0xFFF) << 12);
    }
    gSPDisplayList(arg0++, &D_1000118);
    gDPSetCombineMode(arg0++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gSPMatrix(arg0++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    return arg0;
}

typedef struct {
    u8 unk0[0x1A4];
    u8 unk1A4;
} R1F103AB0aState;

Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

Gfx *func_806FEF7C(Gfx *arg0, Actor *arg1) {
    arg0 = func_806FEDB0(arg0, ((R1F103AB0aState *)arg1->unk174)->unk1A4);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gDPSetPrimColor(arg0++, 0, 0, 0, 0, 0, 0xFF);
    return func_8068C5A8(arg0, 0x3C, 3, 1, 0x40, 0x40, 0xA0, 0x78, 5.0f, 5.0f, 0, 0.001f);
}

extern u8 *D_807FD568;
s32 func_806F8AD4(s32, u8);
s32 func_80690F30(s32, void *, Actor *, s32, s32, s32, void *, void *, void *);

Gfx *func_806FF01C(Gfx *arg0, Actor *arg1) {
    u8 player;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    Gfx *dl;

    player = ((R1F103AB0aState *)arg1->unk174)->unk1A4;
    dl = func_806FEDB0(arg0, player);
    if ((D_807FD568[2] & 2) && func_806F8AD4(3, player) &&
        func_80690F30(2, &sp58, arg1, 1, 0, 0, &sp54, &sp50, &sp4C)) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xC8, 0, 0xFF);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 0xC8, 0, 0, 0xFF);
    }
    return func_8068C5A8(dl, 0x38, 3, 1, 0x40, 0x40, 0xA0, 0x78, 0.5f, 0.5f, 0x2D, 0.0f);
}

Gfx *func_806FF144(Gfx *arg0) {
    gDPSetPrimColor(arg0++, 0, 0, 0, 0, 0, 0xFF);
    gDPSetCombineMode(arg0++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gSPMatrix(arg0++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    arg0 = func_8068C5A8(arg0, 0x3A, 3, 1, 0x40, 0x40, 0x3E, 0x3E, 2.0f, 2.0f, 0, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x3A, 3, 1, 0x40, 0x40, D_80744490 - 0x3E, 0x3E, 2.0f, 2.0f, 0x5A, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x3A, 3, 1, 0x40, 0x40, D_80744490 - 0x3E, D_80744494 - 0x3E, 2.0f, 2.0f, 0xB4, 0.0f);
    return func_8068C5A8(arg0, 0x3A, 3, 1, 0x40, 0x40, 0x3E, D_80744494 - 0x3E, 2.0f, 2.0f, 0x10E, 0.0f);
}

void func_806FF32C(s32 arg0, Actor *arg1) {
    func_806FF144(func_806FEDB0(arg0, ((R1F103AB0aState *)arg1->unk174)->unk1A4));
}

typedef struct {
    u8 unk0[0x1EC];
    u8 unk1EC;
    u8 unk1ED[3];
    s32 unk1F0;
} AaFF358State;

Gfx *func_806FF358(Gfx *arg0, Actor *arg1) {
    AaFF358State *state;

    state = (AaFF358State *)((Actor **)D_807FC924)[1]->unk174;
    gDPSetPrimColor(arg0++, 0, 0, 0xFF, 0xFF, 0xFF, 0xC8);
    arg0 = func_8068C5A8(arg0, 0x39, 3, 1, 0x40, 0x40, 0x50, 0x50, 0.5f, 0.5f, 0, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x39, 3, 1, 0x40, 0x40, 0xF0, 0x50, 0.5f, 0.5f, 0x5A, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x39, 3, 1, 0x40, 0x40, 0xF0, 0xA0, 0.5f, 0.5f, 0xB4, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x39, 3, 1, 0x40, 0x40, 0x50, 0xA0, 0.5f, 0.5f, 0x10E, 0.0f);
    arg0 = func_8068C5A8(arg0, 0x3B, 3, 1, 0x30, 0x30, 0xA0, 0x78, 1.0f, 1.0f, 0, 0.0f);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    if (!(state->unk1F0 & 0x8000)) {
        if (state->unk1EC == 2) {
            gDPSetPrimColor(arg0++, 0, 0, 0xFF, 0, 0, 0xFF);
            arg0 = func_8068C5A8(arg0, 0x43, 3, 1, 0x40, 0x40, 0x118, 0x28, 0.5f, 0.5f, 0, 0.0f);
        } else if (state->unk1EC == 1) {
            gDPSetPrimColor(arg0++, 0, 0, 0, 0xFF, 0, 0xFF);
            arg0 = func_8068C5A8(arg0, 0x2F, 3, 1, 0x40, 0x40, 0x118, 0x28, 0.5f, 0.5f, 0, 0.0f);
        }
    }
    return arg0;
}

Gfx *func_806FF628(Gfx *arg0, Actor *arg1) {
    AaFF358State *state;

    state = (AaFF358State *)((Actor **)D_807FC924)[1]->unk174;
    arg0 = func_806FEDB0(arg0, ((R1F103AB0aState *)state)->unk1A4);
    if (state->unk1EC == 2) {
        gDPSetPrimColor(arg0++, 0, 0, 0xFF, 0, 0, 0x64);
        arg0 = func_8068C5A8(arg0, 0x45, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
    } else if (state->unk1EC == 1) {
        gDPSetPrimColor(arg0++, 0, 0, 0, 0xFF, 0, 0x64);
        arg0 = func_8068C5A8(arg0, 0x44, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
    }
    return arg0;
}


Gfx *func_806FF75C(Gfx *dl, Actor *arg1) {
    u8 sp77;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;

    sp6C = 2;
    sp77 = ((R1F103AB0aState *)arg1->unk174)->unk1A4;
    if (D_807FC928 >= 2) {
        sp6C = 3;
    }
    dl = (Gfx *)func_806FEDB0((s32)dl, sp77);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x100, 0x40, 3.0f, 2.0f, 0, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x40, 0x40, 2.0f, 3.0f, 0x5A, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x100, 0xB0, 2.0f, 3.0f, 0x10E, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x40, 0xB0, 3.0f, 2.0f, 0xB4, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x60, 0x60, 3.0f, 3.0f, 0, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0xE0, 0x60, 3.0f, 3.0f, 0x5A, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0xE0, 0x90, 3.0f, 3.0f, 0xB4, 0.0f);
    dl = func_8068C5A8(dl, 0x3A, 3, 1, 0x40, 0x40, 0x60, 0x90, 3.0f, 3.0f, 0x10E, 0.0f);
    if (func_806F8AD4(3, sp77) && func_80690F30((u16)sp6C, &sp70, arg1, 1, 0, 0, &sp68, &sp64, &sp60)) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xC8, 0, 0xFF);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 0xC8, 0, 0, 0xFF);
    }
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    return func_8068C5A8(dl, 0x38, 3, 1, 0x40, 0x40, 0xA0, 0x78, 0.5f, 0.5f, 0x2D, 0.0f);
}

void func_806FFB2C(s32 arg0, Actor *arg1) {
    f32 sp3C;
    Gfx *dl;

    sp3C = arg1->unk155[0] * 1.4;
    dl = (Gfx *)func_806FEDB0(arg0, ((R1F103AB0aState *)arg1->unk174)->unk1A4);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    func_8068C5A8(dl, 0x3C, 3, 1, 0x40, 0x40, 0xA0, 0x78, 5.0f, 5.0f, 0, sp3C);
}

u16 func_806FFC04(u16 arg0) {
    u16 sum;
    u8 a;
    f32 f;
    u8 lsb;

    sum = (u8)((arg0 & 0xF800) >> 11) + (u8)((arg0 & 0x7C0) >> 6) + (u8)((arg0 & 0x3E) >> 1);
    lsb = arg0 & 1;
    if (sum >= 0x30) {
        a = (sum - 0x30) / 45.0 * 18.0;
    } else {
        a = 0;
    }
    f = sum / 93.0;
    return ((u8)(28.0f * f + 3.0f) << 11) + ((u8)(19.0f * f + 3.0f) << 6) + (a << 1) + lsb;
}

s16 *func_806FFEAC(s16 *arg0, s32 arg1) {
    s16 i;
    s16 j;

    for (i = 0; i < 0x40; i++) {
        for (j = 0; j < 0x20; j++) {
            *arg0++ = func_806FFC04(((u16 *)arg1)[j + i * D_80744490]);
        }
    }
    return arg0;
}

void func_8066B0F8();

void func_806FFF5C(void) {
    func_8066B0F8(0x19, 0x138B, 1, 1);
}

#ifdef NON_MATCHING
extern void *D_80744470[];
s32 func_80610FE8(s32);

s32 func_806FFF88(void) {
    s32 sp34;
    s16 var_s0;
    s16 var_s3;
    s32 var_s1;
    s32 var_s2;

    if (D_807FBB40->unk58 == 0xD9) {
        func_806FFF5C();
        return;
    }
    sp34 = func_80610FE8(0xA000);
    var_s1 = sp34;
    var_s2 = (s32)D_80744470[D_807444FC] + (D_80744490 * 7 << 4) + 0xA0;
    var_s3 = 0;
    do {
        var_s0 = 0;
        do {
            var_s1 = (s32)func_806FFEAC((s16 *)var_s1, (var_s0 << 6) + var_s2);
            var_s0++;
        } while (var_s0 < 5);
        var_s3++;
        var_s2 += D_80744490 << 7;
    } while (var_s3 < 2);
    return sp34;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_806FFF88.s")
#endif

u16 func_80700088(f32 arg0, u16 arg1) {
    u8 lsb;

    lsb = arg1 & 1;
    return ((u8)((((arg1 & 0xF800) >> 11) - 0x1F) * arg0 + 31.0f) << 11) + ((u8)((((arg1 & 0x7C0) >> 6) - 0x1F) * arg0 + 31.0f) << 6) + ((u8)((((arg1 & 0x3E) >> 1) - 0x1F) * arg0 + 31.0f) << 1) + lsb;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_807002AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_8070033C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_8070068C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_807007B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_807009F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80700AE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80700BF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80701098.s")

extern s8 D_807FD890;

void func_80701C90(void) {
    D_807FD890 = 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80701CA0.s")

void func_807024E0(Gfx **, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_807023E8(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12) {
    func_807024E0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, 1, 0x10, 0, 0);
}

void func_80702464(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, u8 arg13, u8 arg14) {
    func_807024E0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, 0, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_807024E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80703374.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_807035C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80703850.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80703AB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80703CF8.s")

extern s16 D_807FD892;

void func_807040D0(s16 arg0) {
    D_807FD892 = arg0;
}

extern s8 D_807FD894;
extern s8 D_807FD895;
extern s8 D_807FD896;

void func_807040E0(s8 arg0, s8 arg1, s8 arg2) {
    D_807FD894 = arg0;
    D_807FD895 = arg1;
    D_807FD896 = arg2;
}

extern s8 D_807FD897;
extern s8 D_807FD898;
extern s8 D_807FD899;

void func_80704108(s8 arg0, s8 arg1, s8 arg2) {
    D_807FD897 = arg0;
    D_807FD898 = arg1;
    D_807FD899 = arg2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80704130.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80704298.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80704444.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/103AB0/func_80704484.s")
