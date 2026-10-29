#include "common.h"

typedef struct {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xCD - 0x88];
    u8 unkCD;
    char padCE[0x154 - 0xCE];
    u8 unk154;
    u8 unk155;
    char pad156[0x15F - 0x156];
    u8 unk15F;
    char pad160[0x16A - 0x160];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
} MenuLightFadeActor;

extern MenuLightFadeActor *D_807FBB40;
extern u8 D_80033FB0;
extern u8 D_80033FB1;
extern u8 D_80033FB2;

void behaviourFrameBegin(void);
void func_8068A858(u8 *, u8 *, u8 *);
s32 currentActorTestClearFlag(void);
void currentActorClearFlag(void);
void actorScriptStart(MenuLightFadeActor *, s32);
void actorUpdateModelMatrix(MenuLightFadeActor *, s32);

void func_80032550(void) {
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk154 = 0;
        D_807FBB40->unk155 = 0;
        D_807FBB40->unkCD = 1;
        D_807FBB40->unk60 &= ~4;
    }
    if (D_807FBB40->unk60 & 4) {
        func_8068A858(&D_80033FB0, &D_80033FB1, &D_80033FB2);
    }
    if (D_807FBB40->unk154 == 0 && D_807FBB40->unk155 == 0) {
        do {
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                actorScriptStart(D_807FBB40, 0x2A7);
                D_807FBB40->unk155++;
            }
        } while (0);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

extern u8 D_800339D0;
extern s32 D_807FBB60;
void lightSetFovAngles(f32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void func_807145F8(void);
void renderCallbacksRegister(void *, void *, s32);
Gfx *func_8003292C(Gfx *, void *);

void menuUpdateLightFadeActor(void) {
    s32 d;
    s32 cur;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk15F = 0;
        currentActorClearFlag();
        D_807FBB40->unk154 = 0;
    }
    behaviourFrameBegin();
    switch (D_807FBB40->unk154) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            actorScriptStart(D_807FBB40, 0x2D6);
            D_807FBB40->unk154++;
            D_807FBB40->unk155 = 0;
            D_807FBB60 &= ~0x30;
        }
        break;
    case 1:
        lightSetFovAngles(20.0f, 40.0f);
        cur = D_807FBB40->unk15F;
        if (D_807FBB40->unk15F != 0xFF) {
            d = (0xFF - cur < 3) ? 0xFF - cur : 3;
            D_807FBB40->unk15F = cur + d;
        }
        lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80 + 20.0f, D_807FBB40->unk84, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0.0f, 1, D_807FBB40->unk15F, D_807FBB40->unk15F, D_807FBB40->unk15F);
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            D_807FBB40->unk60 |= 0x800000;
            D_807FBB40->unk154 = 2;
        }
        break;
    case 2:
        D_807FBB40->unk16A -= 8;
        D_807FBB40->unk16B -= 8;
        D_807FBB40->unk16C -= 8;
        if (D_807FBB40->unk16A < 9) {
            D_807FBB40->unk16A = 0;
            D_807FBB40->unk16B = 0;
            D_807FBB40->unk16C = 0;
            D_807FBB40->unk154 = 3;
            D_800339D0 = 0;
        }
        break;
    case 3:
        if (D_800339D0 < 0xFF) {
            D_800339D0++;
        }
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            D_807FBB40->unk154 = 4;
        }
        break;
    case 4:
        func_807145F8();
        D_807FBB40->unk154++;
        break;
    }
    if (D_807FBB40->unk154 >= 3) {
        renderCallbacksRegister(func_8003292C, D_807FBB40, 3);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}


#ifdef NON_MATCHING
extern Gfx D_1000118[];
extern Mtx D_20000C0;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_8074450C;
char *func_8070E750(s32, s32, s32);
s32 textGetFontHeight(s32);
s32 texCacheFindOrLoad(s32);
s32 textGetStringWidth(s32, char *);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, char *, s32);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);

Gfx *func_8003292C(Gfx *dl, void *arg1) {
    s32 off;
    u16 x;
    s32 y;
    s32 xo;
    s32 yo;
    u32 tex;
    char *spCC;
    char *spC8;
    char *spC4;
    s32 spC0;
    s32 alpha;
    s16 yy;
    s16 yyo;

    spCC = func_8070E750(0xD, 0, 1);
    spC8 = func_8070E750(0xD, 1, 1);
    spC4 = func_8070E750(0xD, 2, 1);
    spC0 = textGetFontHeight(1);
    gDPPipeSync(dl++);
    gSPDisplayList(dl++, D_1000118);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, 3, 29, 0x0F0A4000);
    gDPSetCombine(dl++, 0x119623, 0xFF2FFFFF);
    gSPMatrix(dl++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    alpha = D_800339D0 * 15;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    gDPSetPrimColor(dl++, 0, 0, alpha, alpha, alpha, 0xFF);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0);
    tex = texCacheFindOrLoad(0xB0);
    yo = (s32)(((f32)D_80744494 - 82.0f) * 0.5f);
    y = 0;
    do {
        xo = (s32)(((f32)D_80744490 - 204.0f) * 0.5f);
        yy = y + 0x29;
        yyo = yo + 0x29;
        x = 0;
        do {
            gDPLoadTextureTile_4b(dl++, tex, G_IM_FMT_I, 204, 82, x, y, x + 0x66, yy, 0,
                                  G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            gSPTextureRectangle(dl++, xo << 2, yo << 2, (xo + 0x66) << 2, yyo << 2, 0, x << 5, y << 5, 0x400, 0x400);
            x += 0x66;
            xo += 0x66;
        } while (x != 0xCC);
        y += 0x29;
        yo += 0x29;
    } while (y != 0x52);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0x2000);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0x80000);
    x = (s32)((f32)(D_80744490 - textGetStringWidth(1, spCC)) * 0.5f);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, 3, 29, 0x504240);
    gDPSetCombine(dl++, 0xFF97FF, 0xFF2CFE7F);
    dl = textDrawStringVtx(dl, 1, (s16)(x * 4), (s16)((s32)((((f32)D_80744494 - 82.0f) * 0.5f) - (f32)spC0) * 4), spCC, 0);
    x = (s32)((f32)D_80744490 * 0.5f) * 4;
    off = D_8074450C * 0xC8;
    return hudDrawScaledText(hudDrawScaledText(dl, (s16)x, (s16)(off * 4), 0.5f, spC8), (s16)x, (s16)((s32)((f64)off + (f64)spC0 * 0.5) * 4), 0.5f, spC4);
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/E550/func_8003292C.s")
#endif
