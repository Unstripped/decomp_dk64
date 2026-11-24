#include "common.h"
#include "actor.h"
#include "proto/global/100180_text_font.h"
#include "proto/global/112080_resource_parse.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/12E800_behaviour.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/2C910.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/8F4B0.h"
#include "proto/global/90D80_render_callbacks.h"
#include "proto/global/ACDC0_pause_menu.h"
#include "proto/menu/E550.h"


extern Actor *gCurrentActor;
extern u8 menuSpotlightR;
extern u8 menuSpotlightG;
extern u8 menuSpotlightB;


void menuLightSpotlightActorUpdate(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->state = 0;
        gCurrentActor->subState = 0;
        gCurrentActor->lightNodeId = 1;
        gCurrentActor->flags &= ~4;
    }
    if (gCurrentActor->flags & 4) {
        lightUpdateFromActorLighting(&menuSpotlightR, &menuSpotlightG, &menuSpotlightB);
    }
    switch (gCurrentActor->state) {
    case 0:
        switch (gCurrentActor->subState) {
        case 0:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                actorScriptStart(gCurrentActor, 0x2A7);
                gCurrentActor->subState++;
            }
            break;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

u8 menuOptionDescFade = 0;

void menuUpdateLightFadeActor(void) {
    s32 d;
    s32 cur;
    s32 maxLevel = 0xFF; // FAKE: constant-valued limit local; a 0xFF literal in its compares flips the beq operand order (target beq a0,v0 at 0x1f8)

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->fadeValue = 0;
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
            gCurrentActor->subState = 0;
            gGlobalPauseFlags &= ~0x30;
        }
        break;
    case 1:
        lightSetFovAngles(20.0f, 40.0f);
        cur = gCurrentActor->fadeValue;
        if (maxLevel != cur) {
            d = (maxLevel - cur < 3) ? maxLevel - cur : 3;
            gCurrentActor->fadeValue = cur + d;
        }
        lightAdd(gCurrentActor->x, gCurrentActor->y + 20.0f, gCurrentActor->z, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 1, gCurrentActor->fadeValue, gCurrentActor->fadeValue, gCurrentActor->fadeValue);
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
        menuSetDemoActive();
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
    s32 yo;
    s32 x;
    u8 *headerStr;
    u8 *descStr1;
    u8 *descStr2;
    s32 fontHeight;

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
    yo = (gScreenHeight - 82.0f) * 0.5f;
    y = 0; do {  // LAYOUT: one source line removes a scheduling barrier before the loop.
        xo = (gScreenWidth - 204.0f) * 0.5f;
        for (x = 0; x != 0xCC; x += 0x66) { // LAYOUT: keep the induction update on the loop-header line.
            gDPLoadTextureTile_4b(dl++, tex, G_IM_FMT_I, 204, 0, x, y, x + 0x66, y + 0x29, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            gSPTextureRectangle(dl++, xo << 2, yo << 2, (xo + 0x66) << 2, (yo + 0x29) << 2, 0, x << 5, y << 5, 0x400, 0x400);
            xo += 0x66;
        }
        y += 0x29;
        yo += 0x29;
    } while (y != 0x52);
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    gDPSetTexturePersp(dl++, G_TP_PERSP);
    xo = (gScreenWidth - textGetStringWidth(1, headerStr)) * 0.5f;
    yo = (gScreenHeight - 82.0f) * 0.5f - fontHeight;
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    gDPSetCombine(dl++, 0xFF97FF, 0xFF2CFE7F);
    dl = textDrawStringVtx(dl, 1, xo * 4, yo * 4, headerStr, 0);
    xo = gScreenWidth * 0.5f;
    yo = gHiResScale * 0xC8;
    dl = hudDrawScaledText(dl, xo * 4, yo * 4, 0.5, descStr1);
    yo += fontHeight * 0.5;
    return hudDrawScaledText(dl, xo * 4, yo * 4, 0.5, descStr2);
}
