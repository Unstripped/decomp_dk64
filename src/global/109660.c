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

#ifdef NON_MATCHING
typedef struct {
    s8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} R1F109660aRect;

extern R1F109660aRect D_80750840[];
extern u8 D_80750AB8;
extern u8 D_80750ABC;
extern u8 D_8074450C;

Gfx *func_80704960(Gfx *dl) {
    s32 i;

    gDPPipeSync(dl++);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0);
    gDPSetCycleType(dl++, G_CYC_FILL);
    gDPSetFillColor(dl++, 0x10001);
    for (i = 0; D_80750840[i].unk0 != -1; i++) {
        if (((D_80750840[i].unk0 == 2) && ((s32)D_807FC928 >= 2) && (D_80750840[i].unk2 & D_80750ABC)) || ((D_807FC928 == D_80750840[i].unk0) && (D_80750AB8 == D_80750840[i].unk1) && (D_80750840[i].unk2 & D_80750ABC))) {
            Gfx *_g = (Gfx *)(dl++);
            _g->words.w0 = 0xF6000000 | (((((D_80750840[i].unk8 + 1) * D_8074450C) - 1) & 0x3FF) << 14) | (((((D_80750840[i].unkA + 1) * D_8074450C) - 1) & 0x3FF) << 2);
            _g->words.w1 = ((((D_80750840[i].unk4 * D_8074450C) & 0x3FF)) << 14) | ((((D_80750840[i].unk6 * D_8074450C) & 0x3FF)) << 2);
        }
    }
    gDPPipeSync(dl++);
    return dl;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_80704960.s")
#endif


extern f32 D_807FD968;
extern f32 D_807FD96C;
extern f32 D_807FD970;

void func_80704AFC(f32 arg0, f32 arg1, f32 arg2) {
    D_807FD968 = arg0;
    D_807FD96C = arg1;
    D_807FD970 = arg2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_80704B20.s")

typedef struct {
    u8 unk0[0xC];
    s8 unkC;
    s8 unkD;
    s8 unkE;
} R1F109660aArgs;

void func_80705B14(R1F109660aArgs *arg0, s8 arg1, s8 arg2, s8 arg3) {
    arg0->unkC = arg1;
    arg0->unkD = arg2;
    arg0->unkE = arg3;
}

extern s32 D_807FD8A0;
extern Mtx D_807FD928;
extern s32 D_807FD978;

void func_80705B30(void) {
    D_807FD8A0 = 0;
    guOrtho(&D_807FD928, 0.0f, (f32)((f64)((f32)D_80744490 * 16.0f) - 1.0), (f32)((f64)((f32)D_80744494 * 16.0f) - 1.0), 0.0f, -20000.0f, 20000.0f, 1.0f);
    D_807FD968 = -1.0f;
    D_807FD978 = 0;
}

typedef struct {
    u8 unk0[0x2CA];
    s16 unk2CA;
} R1F109660aPlayerView;

f32 func_80612790(s16);
f32 func_80612794(s16);
void func_8070033C(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32);
void lightGetColor(f32 *, f32 *, f32 *, s16);

void func_80705C00(s16 arg0, s16 arg1, u8 arg2) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s16 sp42;
    s16 sp40;
    s16 sp3E;
    s32 unused;

    sp42 = (s16)(s32)((f64)func_80612794(arg0) * 32767.0);
    sp3E = (s16)(s32)((f64)func_80612790(arg0) * 32767.0);
    sp40 = (s16)(s32)((f64)arg1 - (8.0 * (f64)((R1F109660aPlayerView *)D_807FC924)->unk2CA));
    if (arg2 != 0) {
        if (arg2 == 1) {
            lightGetColor(&sp4C, &sp48, &sp44, *(s16 *)D_807FBB4C->unk12C);
            if ((f64)sp4C > 0.5) {
                func_8070033C((f32)sp42, (f32)sp40, (f32)sp3E, 0.0f, 0.0f, 0.0f, 0.0f, (u32)(sp4C * 255.0f), (u32)(sp48 * 255.0f), (u32)(sp44 * 255.0f));
            }
        }
    } else {
        func_8070033C((f32)sp42, (f32)sp40, (f32)sp3E, 0.0f, 0.0f, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF);
    }
}

extern f32 D_80754CE8;
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
Gfx *func_806FEDB0(Gfx *, u8);
extern u8 D_2000100[];

Gfx *func_80705F5C(Gfx *dl, s16 arg1, s16 arg2, u8 mode) {
    s16 sp76;
    Gfx *g;
    f32 sp6C, sp68;
    u8 alpha;
    f32 sp60, sp5C, sp58;
    s16 b;
    s16 c;

    alpha = 0xFF;
    if (mode == 1) {
        lightGetColor(&sp60, &sp5C, &sp58, *(s16 *)D_807FBB4C->unk12C);
        sp60 = (f32)(1.0 < ((1.0 - (f64)sp5C) / 0.7) ? 1.0 : ((1.0 - (f64)sp5C) / 0.7));
        alpha = (u32)((f64)sp60 * 255.0);
    } else if (mode == 2) {
        sp60 = (f32)((f64)D_80754CE8 - 0.5);
        if (sp60 < 0.0) {
            sp60 = 0.0f;
        }
        sp60 = (f32)((f64)sp60 * 512.0);
        if (sp60 > 255.0) {
            sp60 = 255.0f;
        }
        alpha = (u32)sp60;
    }
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    sp76 = (s16)(s32)((f64)func_80612794(arg1) * 32767.0);
    c = (s16)(s32)((f64)func_80612790(arg1) * 32767.0);
    b = (s16)(s32)((f64)arg2 - (8.0 * (f64)((R1F109660aPlayerView *)D_807FC924)->unk2CA));
    camProjectToScreen((f32)sp76, (f32)b, (f32)c, &sp6C, &sp68, 0, 4.0f, 0);
    if ((sp6C > -320.0f) && (sp6C < 1600.0f) && (sp68 > -240.0f) && (sp68 < 1200.0f)) {
        g = func_806FEDB0(dl, 0);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
        g->words.w0 = 0xDA380007; g->words.w1 = (u32)&D_2000100; dl = func_8068C5A8(g + 1, 0x35, 3, 1, 0x40, 0x40, (s32)sp6C, (s32)sp68, 4.0f, 4.0f, 0, 0.0f);
    }
    return dl;
}

typedef struct {
    f32 v[3][2];
} BaSpan;

void func_807063B8(BaSpan *arg0, u8 *arg1, u8 arg2, f32 arg3) {
    BaSpan temp[4];
    s32 i;
    u8 o;
    f32 f;
    f32 g;

    o = 0;
    for (i = 0; i < *arg1; i++) {
        temp[i] = arg0[i];
    }
    for (i = 0; i < *arg1; i++) {
        if ((temp[i].v[0][arg2] < 0.0f) || (arg3 < temp[i].v[1][arg2])) {
            f = (temp[i].v[0][arg2] < 0.0f) ? temp[i].v[0][arg2] + arg3 : temp[i].v[0][arg2];
            arg0[o].v[0][arg2] = f;
            arg0[o].v[0][arg2 ^ 1] = temp[i].v[0][arg2 ^ 1];
            arg0[o].v[1][arg2] = arg3;
            arg0[o].v[1][arg2 ^ 1] = temp[i].v[1][arg2 ^ 1];
            arg0[o].v[2][arg2] = temp[i].v[2][arg2];
            arg0[o].v[2][arg2 ^ 1] = temp[i].v[2][arg2 ^ 1];
            g = arg0[o].v[2][arg2] + (arg3 - f);
            o++;
            f = (temp[i].v[0][arg2] < 0.0f) ? temp[i].v[1][arg2] : temp[i].v[1][arg2] - arg3;
            arg0[o].v[0][arg2] = 0.0f;
            arg0[o].v[0][arg2 ^ 1] = temp[i].v[0][arg2 ^ 1];
            arg0[o].v[1][arg2] = f;
            arg0[o].v[1][arg2 ^ 1] = temp[i].v[1][arg2 ^ 1];
            arg0[o].v[2][arg2] = g;
            arg0[o].v[2][arg2 ^ 1] = temp[i].v[2][arg2 ^ 1];
            o++;
        } else {
            arg0[o] = temp[i];
            o++;
        }
    }
    *arg1 = o;
}

typedef struct {
    s16 pos;
    u8 r;
    u8 g;
    u8 b;
    u8 pad;
} BaKey;

extern BaKey D_80754F58[];

void func_807065F8(s16 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 idx;
    BaKey *p;
    f32 t;

    switch (D_8076A0A8) {
        case 0xE:
            idx = 0;
            if (arg0 < D_80754F58[1].pos) {
                do {
                    idx++;
                } while (arg0 < D_80754F58[idx + 1].pos);
            }
            p = &D_80754F58[idx];
            t = (f32)(arg0 - D_80754F58[idx + 1].pos) / (f32)(p->pos - D_80754F58[idx + 1].pos);
            *arg1 = D_80754F58[idx + 1].r + (f32)(p->r - D_80754F58[idx + 1].r) * t;
            *arg2 = D_80754F58[idx + 1].g + (f32)(p->g - D_80754F58[idx + 1].g) * t;
            *arg3 = D_80754F58[idx + 1].b + (f32)(p->b - D_80754F58[idx + 1].b) * t;
            return;
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x4A:
        case 0x4B:
        case 0x7C:
        case 0x7D:
        case 0x7E:
        case 0x7F:
        case 0x80:
            *arg1 = 0x3F;
            *arg2 = 0x3F;
            *arg3 = 0x3F;
            return;
        default:
            *arg1 = 0xFF;
            *arg2 = 0xFF;
            *arg3 = 0xFF;
            return;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_807069A4.s")

#ifdef NON_MATCHING
extern s16 D_80754CE0;
extern s16 D_80754CEC[];
extern s16 D_80754F70;
extern s16 D_80754F74;
s32 func_8066B0F8(s32, s32, s32, s32);

Gfx *func_80706F90(Gfx *dl) {
    s32 tv;
    s32 n;
    s32 x;
    s32 i;
    s32 j;
    s16 ps;
    s32 y;
    s32 y2;
    u16 k;
    s16 scroll;

    gSPClearGeometryMode(dl++, 0xFFFFFF);
    gSPSetGeometryMode(dl++, G_SHADE | G_SHADING_SMOOTH);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    { Gfx *_g = (Gfx *)(dl++); _g->words.w0 = 0xFC11FE23; _g->words.w1 = 0xFFFFF3F9; }
    gDPSetTexturePersp(dl++, G_TP_NONE);
    gDPSetTextureFilter(dl++, G_TF_POINT);
    gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPPipeSync(dl++);
    scroll = D_80754F74 + D_80754CE0;
    if (scroll < 0) {
        scroll += 0x200;
    }
    if (scroll >= 0x200) {
        scroll -= 0x200;
    }
    if (D_807FD978 == 0) {
        for (n = 0; n < 8; n++) {
            (&D_807FD978)[n] = func_8066B0F8(0x19, D_80754CEC[n], 0, 0);
        }
    }
    k = 0;
    j = 0x40;
    do {
        i = 0;
        y = (j << 2) - scroll;
        do {
            gDPPipeSync(dl++);
            tv = (&D_807FD978)[k];
            gDPLoadTextureBlock(dl++, (u32)tv + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            x = (i << 2) - D_80754F70;
            for (n = 0; n != 4; n++) {
                y2 = y;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                y2 += 0x200;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                y2 += 0x200;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                x += 0x200;
            }
            k++;
            i += 0x20;
        } while (i != 0x80);
        j -= 0x40;
    } while (j >= 0);
    ps = D_80754F70 + 4;
    D_80754F74 += 4;
    D_80754F70 = ps;
    if (ps >= 0x200) {
        D_80754F70 = 0;
    }
    if (D_80754F74 >= 0x200) {
        D_80754F74 = 0;
    }
    gDPPipeSync(dl++);
    gDPSetTexturePersp(dl++, G_TP_PERSP);
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    return dl;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_80706F90.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_8070770C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_80707980.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_8070835C.s")


void func_80708574(f32 arg0) {
    f64 var_fv0;

    var_fv0 = (f64)arg0;
    if (var_fv0 < 0.0) {
        arg0 = 0.0f;
        var_fv0 = (f64)arg0;
    }
    if (var_fv0 > 1.0) {
        arg0 = 1.0f;
    }
    D_80754CE8 = arg0;
}
