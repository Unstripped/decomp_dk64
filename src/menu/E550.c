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
void lightUpdateFromActorLighting(u8 *, u8 *, u8 *);
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
        lightUpdateFromActorLighting(&D_80033FB0, &D_80033FB1, &D_80033FB2);
    }
    if (D_807FBB40->unk154 == 0 && D_807FBB40->unk155 == 0) {
        do {
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                actorScriptStart(D_807FBB40, 0x2A7);
                D_807FBB40->unk155++;
            }
        } while (0); // FAKE: do/while(0) wrapper steers branch codegen
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

extern u8 D_800339D0;
extern s32 D_807FBB60;
void lightSetFovAngles(f32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void func_807145F8(void);
void renderCallbacksRegister(void *, void *, s32);
Gfx *menuRenderOptionDescription(Gfx *, void *);

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
        renderCallbacksRegister(menuRenderOptionDescription, D_807FBB40, 3);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}



extern Gfx D_1000118[];
extern Mtx D_20000C0;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_8074450C;
char *textTableGetString(s32, s32, s32);
s32 textGetFontHeight(s32);
s32 texCacheFindOrLoad(s32);
s32 textGetStringWidth(s32, char *);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, char *, s32);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);

Gfx *menuRenderOptionDescription(Gfx *dl, void *actor) {
    u32 tex;
    s32 alpha;
    s32 y;
    s32 xo;
    s32 off;
    s32 x;
    char *headerStr;
    char *descStr1;
    char *descStr2;
    s32 fontHeight;
    s16 xx;
    s32 yo;
    Gfx *loadTilePacket;

    headerStr = textTableGetString(0xD, 0, 1);
    descStr1 = textTableGetString(0xD, 1, 1);
    descStr2 = textTableGetString(0xD, 2, 1);
    fontHeight = textGetFontHeight(1);
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
    y = 0; do {  // FAKE: one source line removes a scheduling barrier before the loop.
        xo = (s32)(((f32)D_80744490 - 204.0f) * 0.5f);
        for (x = 0; x != 0xCC; x += 0x66) { // LAYOUT: keep the induction update on the loop-header line.
            if (x) {} // FAKE: shorten the full-width induction range and raise its colouring priority.
            { gDPSetTextureImage(dl++, G_IM_FMT_I, G_IM_SIZ_8b, 102, tex); \
              gDPSetTile(dl++, G_IM_FMT_I, G_IM_SIZ_8b, (((((x + 0x66) - x + 1) >> 1) + 7) >> 3), 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0); \
              gDPLoadSync(dl++); \
              loadTilePacket = dl++; \
              loadTilePacket->words.w0 = _SHIFTL(G_LOADTILE, 24, 8) | _SHIFTL(x << 1, 12, 12) | _SHIFTL(y << 2, 0, 12); \
              loadTilePacket->words.w1 = _SHIFTL(G_TX_LOADTILE, 24, 3) | _SHIFTL((x + 0x66) << 1, 12, 12) | _SHIFTL((y + 0x29) << 2, 0, 12); \
              gDPPipeSync(dl++); \
              gDPSetTile(dl++, G_IM_FMT_I, G_IM_SIZ_4b, (((((x + 0x66) - x + 1) >> 1) + 7) >> 3), 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0); \
              gDPSetTileSize(dl++, G_TX_RENDERTILE, x << 2, y << 2, (x + 0x66) << 2, (y + 0x29) << 2); \
              } // FAKE: expanded GBI packet reuse; continuations retain macro scheduling.
            gSPTextureRectangle(dl++, xo << 2, yo << 2, (xo + 0x66) << 2, (yo + 0x29) << 2, 0, x << 5, y << 5, 0x400, 0x400);
            xo += 0x66;
        }
        y += 0x29;
        yo += 0x29;
    } while (y != 0x52);
    if ((s8)D_800339D0 && xo) {}  // FAKE: keep xo below the row-mask priority while merging the post-loop packet block.
    if ((s8)D_800339D0 && xo) {}  // FAKE: preserve xo's range length and the Combine packet's v0/v1 interference.
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0x2000);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0x80000);
    xo = (s32)((f32)(D_80744490 - textGetStringWidth(1, headerStr)) * 0.5f);
    yo = (s32)((((f32)D_80744494 - 82.0f) * 0.5f) - (f32)fontHeight);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    loadTilePacket = dl++; loadTilePacket->words.w0 = 0xE200001C; loadTilePacket->words.w1 = 0x504240; // FAKE: reuse the t1 load-tile range for this packet.
    actor = dl++; ((Gfx *)actor)->words.w0 = 0xFCFF97FF; ((Gfx *)actor)->words.w1 = 0xFF2CFE7F; // FAKE: reuse the consumed parameter's packet home.
    dl = textDrawStringVtx(dl, 1, (s16)(xo * 4), (s16)(yo * 4), headerStr, 0);
    x = (s32)((f32)D_80744490 * 0.5f);
    actor = &off;  // FAKE: address-taken offset retains its stack home across the first text draw.
    off = D_8074450C * 0xC8;
    xx = x * 4;
    xx = xx | 0;  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    dl = hudDrawScaledText(dl, xx, (s16)(*(s32 *)actor * 4), .5f, descStr1);  // FAKE: .5f spells a separate constant web (argument via lui a3, no mfc1).
    xo = (s32)((f64)off + (f64)fontHeight * 0.5);
    fontHeight = xx; // FAKE: reuse the consumed font-height local to evaluate final y before the call arguments.
    return hudDrawScaledText(dl, (s16)fontHeight, (s16)(xo * 4), .5f, descStr2);
}
