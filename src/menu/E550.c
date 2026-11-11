#include "common.h"
#include "actor.h"
#include "proto/global/100180.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/12E800.h"
#include "proto/global/19A00.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/5E2F0.h"
#include "proto/global/8F4B0.h"
#include "proto/global/90D80.h"
#include "proto/global/ACDC0.h"
#include "proto/menu/E550.h"


extern Actor *gCurrentActor;
extern u8 menuSpotlightR;
extern u8 menuSpotlightG;
extern u8 menuSpotlightB;


void menuLightSpotlightActorUpdate(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->state = 0;
        gCurrentActor->unk155 = 0;
        gCurrentActor->unkCD = 1;
        gCurrentActor->flags &= ~4;
    }
    if (gCurrentActor->flags & 4) {
        lightUpdateFromActorLighting(&menuSpotlightR, &menuSpotlightG, &menuSpotlightB);
    }
    switch (gCurrentActor->state) {
    case 0:
        switch (gCurrentActor->unk155) {
        case 0:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                actorScriptStart(gCurrentActor, 0x2A7);
                gCurrentActor->unk155++;
            }
            break;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u8 menuOptionDescFade;
extern s32 gGlobalPauseFlags;

void menuUpdateLightFadeActor(void) {
    s32 d;
    s32 cur;
    s32 maxLevel = 0xFF;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk15F = 0;
        currentActorClearFlag();
        gCurrentActor->state = 0;
    }
    behaviourFrameBegin();
    switch (gCurrentActor->state) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            actorScriptStart(gCurrentActor, 0x2D6);
            gCurrentActor->state++;
            gCurrentActor->unk155 = 0;
            gGlobalPauseFlags &= ~0x30;
        }
        break;
    case 1:
        lightSetFovAngles(20.0f, 40.0f);
        cur = gCurrentActor->unk15F;
        if (maxLevel != cur) {
            d = (maxLevel - cur < 3) ? maxLevel - cur : 3;
            gCurrentActor->unk15F = cur + d;
        }
        lightAdd(gCurrentActor->x, gCurrentActor->y + 20.0f, gCurrentActor->z, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 1, gCurrentActor->unk15F, gCurrentActor->unk15F, gCurrentActor->unk15F);
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            gCurrentActor->flags |= 0x800000;
            gCurrentActor->state = 2;
        }
        break;
    case 2:
        gCurrentActor->tintR -= 8;
        gCurrentActor->tintG -= 8;
        gCurrentActor->tintB -= 8;
        if (gCurrentActor->tintR < 9) {
            gCurrentActor->tintR = 0;
            gCurrentActor->tintG = 0;
            gCurrentActor->tintB = 0;
            gCurrentActor->state = 3;
            menuOptionDescFade = 0;
        }
        break;
    case 3:
        if (menuOptionDescFade < maxLevel) {
            menuOptionDescFade++;
        }
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            gCurrentActor->state = 4;
        }
        break;
    case 4:
        menuSetFlag5324();
        gCurrentActor->state++;
        break;
    }
    if (gCurrentActor->state >= 3) {
        renderCallbacksRegister(menuRenderOptionDescription, gCurrentActor, 3);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}



extern Gfx D_1000118[];
extern Mtx D_20000C0;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gHiResScale;

Gfx *menuRenderOptionDescription(Gfx *dl, void *actor) {
    void *tex;
    s32 alpha;
    s32 y;
    s32 xo;
    s32 off;
    s32 x;
    u8 *headerStr;
    u8 *descStr1;
    u8 *descStr2;
    s32 fontHeight;
    s32 yo;

    headerStr = textTableGetString(0xD, 0, 1);
    descStr1 = textTableGetString(0xD, 1, 1);
    descStr2 = textTableGetString(0xD, 2, 1);
    fontHeight = textGetFontHeight(1);
    gDPPipeSync(dl++);
    gSPDisplayList(dl++, D_1000118);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x0F0A4000);
    gDPSetCombine(dl++, 0x119623, 0xFF2FFFFF);
    gSPMatrix(dl++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    alpha = menuOptionDescFade * 15;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    gDPSetPrimColor(dl++, 0, 0, alpha, alpha, alpha, 0xFF);
    gDPSetTextureFilter(dl++, G_TF_POINT);
    gDPSetTexturePersp(dl++, G_TP_NONE);
    tex = texCacheFindOrLoad(0xB0);
    yo = (s32)(((f32)gScreenHeight - 82.0f) * 0.5f);
    y = 0; do {  // LAYOUT: one source line removes a scheduling barrier before the loop.
        xo = (s32)(((f32)gScreenWidth - 204.0f) * 0.5f);
        for (x = 0; x != 0xCC; x += 0x66) { // LAYOUT: keep the induction update on the loop-header line.
            if (x) {} // FAKE: shorten the full-width induction range and raise its colouring priority.
            gDPLoadTextureTile_4b(dl++, tex, G_IM_FMT_I, 204, 0, x, y, x + 0x66, y + 0x29, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            gSPTextureRectangle(dl++, xo << 2, yo << 2, (xo + 0x66) << 2, (yo + 0x29) << 2, 0, x << 5, y << 5, 0x400, 0x400);
            xo += 0x66;
        }
        y += 0x29;
        yo += 0x29;
    } while (y != 0x52);
    if ((s8)menuOptionDescFade && xo) {}  // FAKE: keep xo below the row-mask priority while merging the post-loop packet block.
    if ((s8)menuOptionDescFade && xo) {}  // FAKE: preserve xo's range length and the Combine packet's v0/v1 interference.
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    gDPSetTexturePersp(dl++, G_TP_PERSP);
    xo = (s32)((f32)(gScreenWidth - textGetStringWidth(1, headerStr)) * 0.5f);
    yo = (s32)((((f32)gScreenHeight - 82.0f) * 0.5f) - (f32)fontHeight);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    actor = dl++; ((Gfx *)actor)->words.w0 = 0xFCFF97FF; ((Gfx *)actor)->words.w1 = 0xFF2CFE7F; // FAKE: the consumed parameter carries this Combine packet so it takes no block-local _g home (frame 0xE8).
    dl = textDrawStringVtx(dl, 1, (s16)(xo * 4), (s16)(yo * 4), headerStr, 0);
    x = (s32)((f32)gScreenWidth * 0.5f);
    actor = &off;  // FAKE: address-taken offset retains its stack home across the first text draw.
    off = gHiResScale * 0xC8;
    dl = hudDrawScaledText(dl, x * 4, (s16)(off * 4), 0.5, descStr1);
    xo = (s32)((f64)off + (f64)fontHeight * 0.5);
    fontHeight = x * 4; // FAKE: reuse the consumed font-height local to evaluate final y before the call arguments.
    return hudDrawScaledText(dl, (s16)fontHeight, (s16)(xo * 4), 0.5, descStr2);
}
