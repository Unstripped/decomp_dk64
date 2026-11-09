#include "common.h"
#include "actor.h"
#define PROTO_SKIP_lightAdd // FAKE: callee prototype steer
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
extern u8 D_80033FB0;
extern u8 D_80033FB1;
extern u8 D_80033FB2;


void menuLightSpotlightActorUpdate(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->state = 0;
        gCurrentActor->unk155[0] = 0;
        gCurrentActor->unkCD = 1;
        gCurrentActor->flags &= ~4;
    }
    if (gCurrentActor->flags & 4) {
        lightUpdateFromActorLighting(&D_80033FB0, &D_80033FB1, &D_80033FB2);
    }
    switch (gCurrentActor->state) {
    case 0:
        switch (gCurrentActor->unk155[0]) {
        case 0:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                actorScriptStart(gCurrentActor, 0x2A7);
                gCurrentActor->unk155[0]++;
            }
            break;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u8 D_800339D0;
extern s32 gGlobalPauseFlags;
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32); // FAKE: callee prototype steer

void menuUpdateLightFadeActor(void) {
    s32 d;
    s32 cur;

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
            gCurrentActor->unk155[0] = 0;
            gGlobalPauseFlags &= ~0x30;
        }
        break;
    case 1:
        lightSetFovAngles(20.0f, 40.0f);
        cur = gCurrentActor->unk15F;
        if (gCurrentActor->unk15F != 0xFF) {
            d = (0xFF - cur < 3) ? 0xFF - cur : 3;
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
            D_800339D0 = 0;
        }
        break;
    case 3:
        if (D_800339D0 < 0xFF) {
            D_800339D0++;
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
    yo = (s32)(((f32)gScreenHeight - 82.0f) * 0.5f);
    y = 0; do {  // LAYOUT: one source line removes a scheduling barrier before the loop.
        xo = (s32)(((f32)gScreenWidth - 204.0f) * 0.5f);
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
    xo = (s32)((f32)(gScreenWidth - textGetStringWidth(1, headerStr)) * 0.5f);
    yo = (s32)((((f32)gScreenHeight - 82.0f) * 0.5f) - (f32)fontHeight);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    loadTilePacket = dl++; loadTilePacket->words.w0 = 0xE200001C; loadTilePacket->words.w1 = 0x504240; // FAKE: reuse the t1 load-tile range for this packet.
    actor = dl++; ((Gfx *)actor)->words.w0 = 0xFCFF97FF; ((Gfx *)actor)->words.w1 = 0xFF2CFE7F; // FAKE: reuse the consumed parameter's packet home.
    dl = textDrawStringVtx(dl, 1, (s16)(xo * 4), (s16)(yo * 4), headerStr, 0);
    x = (s32)((f32)gScreenWidth * 0.5f);
    actor = &off;  // FAKE: address-taken offset retains its stack home across the first text draw.
    off = gHiResScale * 0xC8;
    xx = x * 4;
    dl = hudDrawScaledText(dl, xx, (s16)(*(s32 *)actor * 4), .5f, descStr1);  // FAKE: .5f spells a separate constant web (argument via lui a3, no mfc1).
    xo = (s32)((f64)off + (f64)fontHeight * 0.5);
    fontHeight = xx; // FAKE: reuse the consumed font-height local to evaluate final y before the call arguments.
    return hudDrawScaledText(dl, (s16)fontHeight, (s16)(xo * 4), .5f, descStr2);
}
