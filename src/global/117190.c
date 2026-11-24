#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/boot/3630_string.h"
#include "proto/boot/3D20_sprintf.h"
#include "proto/global/100180.h"
#include "proto/global/10130.h"
#include "proto/global/103AB0.h"
#include "proto/global/104F0.h"
#include "proto/global/10D2D0.h"
#include "proto/global/10E1D0.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/2F550.h"
#include "proto/global/3C10.h"
#include "proto/global/450.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/ACDC0.h"
#include "proto/global/CC800.h"
#include "proto/global/F600.h"

extern PlayerStruct *gPlayerSlots;
extern s32 gCurrentMap;
extern u32 gGlobalCutsceneFlags;
extern s8 gBannerTextStepIndex;

// Bonus countdown started by menuTimerInit; remaining is in seconds, index the next gMenuBonusTimerThresholds threshold.
typedef struct MenuBonusTimer {
    u64 time;
    s32 remaining;
    s32 duration;
    u8 active;
    u8 index;
} MenuBonusTimer;

typedef struct {
    s32 ids[2];
} TextIdPair;

// Attract-mode demo: an input recording replayed in mode 3, cycled by gMenuDemoIndex.
typedef struct DemoEntry {
    /* 0x0 */ u8 recordingIndex; // input-recording asset (table 0x11) loaded by demoPlaybackLoad
    /* 0x1 */ u8 pad1;
    /* 0x2 */ u16 maxTime; // caps gMenuStateTimer
} DemoEntry; // size = 0x4

s8 gDebugSecurityCode = 0;
MpSettings gMpSettings = { 0, 0, 0, 3, { 0, 0, 0, 0 }, 0 };
u16 gControllerButtonMask = 0;
u8 gControllerStickXMask = 0;
u8 gControllerStickYMask = 0;
u8 gMenuCurrentMode = 0;
u8 gMenuTargetMode = 0;
u16 gMenuStateTimer = 0;
u32 gMenuDemoOverlayFrames = 0;
u8 gMenuDemoActive = 0;
u8 gMenuDemoIndex = 0;
u8 gMenuTransitionCounter = 0;
s8 gMenuTransitionFlag = 0;
s32 gMenuFramesSinceLoad = 0;
s32 gMenuEntryCutscenePending = 1;
s32 gMenuEntryCutscene = 0;
MenuBonusTimer gMenuBonusTimer = { 0 };
u16 gMenuBonusTimerThresholds[10] = { 1800, 1200, 900, 600, 300, 180, 120, 60, 30, 10 };
s8 gMenuNextExit = 0;
TextIdPair gMenuPromptTextIds = { { 3, 2 } };
u8 gGameOverText[12] = "GAME OVER";
s32 gMpMatchMaps[3] = { 0x6D, 0xBE, 0xC0 };
const DemoEntry gMenuDemoEntries[5] = {
    { 4, 0, 0x1E0 }, { 0, 0, 0x294 }, { 1, 0, 0x1E0 }, { 3, 0, 0x258 }, { 2, 0, 0x258 },
};

void menuTransitionWithState(s32 map, s32 exit, u8 mode) {
    mapRequestTransition(map, exit);
    gMenuTargetMode = mode;
}


void menuTransitionRequest(s32 map, s32 cutscene, u8 mode) {
    if (menuIsTransitionActive() == 0) {
        screenSetTransitionFadeType(0);
        menuTransitionWithState(map, gMenuNextExit, mode);
        gMenuEntryCutscenePending = 1;
        gMenuEntryCutscene = cutscene;
        gMenuNextExit = 0;
    }
}

void menuTransitionToMap(s32 map, s32 cutscene) {
    menuTransitionRequest(map, cutscene, gMenuTargetMode);
}

s32 menuCalculateBonusDuration(void) {
    return flagCountRange(0x1FD, 0x28, 0) + 0xA;
}

void menuTimerInit(void) {
    s32 i;
    s32 found = 0;

    gMenuBonusTimer.active = 1;
    gMenuBonusTimer.index = 0;
    gMenuBonusTimer.time = osGetTime();
    gMenuBonusTimer.duration = menuCalculateBonusDuration() * 60;
    for (i = 0; (i < sizeof(gMenuBonusTimerThresholds) / sizeof(gMenuBonusTimerThresholds[0])) && (found == 0); i++) {
        if (gMenuBonusTimerThresholds[i] < gMenuBonusTimer.duration) {
            gMenuBonusTimer.index = i;
            found = 1;
        }
    }
}

void menuClearTimerFlag(void) {
    gMenuBonusTimer.active = 0;
}

s32 menuGetTimerFlag(void) {
    return gMenuBonusTimer.active;
}

void menuTransitionRequestTypeB(s32 map, s32 cutscene) {
    menuTransitionRequest(map, cutscene, 0xB);
    gMenuTransitionFlag = 0;
}

s32 menuIsTransitionTypeB(void) {
    s32 match;

    match = gMenuCurrentMode == 0xB;
    if (match == 0) {
        return gMenuTargetMode == 0xB;
    }
}

void menuSetTransitionTypeBFlag(void) {
    if (gMenuCurrentMode == 0xB) {
        gMenuTransitionFlag = 1;
    }
}


void menuSetupPlayerInventory(s32 map, s32 exit, s32 characterId, s8 moveLevel, s8 slamLevel, s8 instrumentFlags, s8 melons) {
    s32 i;

    gPlayerCharacterId[0] = characterId;
    gPlayerInventoryTable[0].melons = melons;
    gPlayerInventoryTable[0].health = melons * 4;
    for (i = 0; i < 5; i++) {
        gPlayerInventoryTable[0].kong[i].moveLevel = moveLevel;
        gPlayerInventoryTable[0].kong[i].slamLevel = slamLevel;
        gPlayerInventoryTable[0].kong[i].instrumentFlags = instrumentFlags;
    }
    menuTransitionWithState(map, exit, 12);
}

void menuTransitionWithStateD(s32 map) {
    menuTransitionWithState(map, 0, 0xD);
}

s32 menuIsTransitionActive(void) {
    return gMenuCurrentMode != gMenuTargetMode;
}

void menuResetAndTransitionToCredits(void) {
    mapSlotArrayResetAll();
    flagSet(0x314, 1, 0);
    menuTransitionRequest(0x1C, 0x17, 7);
}

void menuTransitionToCreditsOrMap28(s32 toCredits) {
    u8 mode;

    if (toCredits == 0) {
        mode = 0xA;
    } else {
        mode = 0xE;
    }
    menuTransitionRequest(0x99, 0xB, mode);
    gBannerTextStepIndex = -2;
}

extern u8 gPlayerCount;
void func_80026D40(Actor *, s32);

void playerRefillHealth(Actor *player, s32 playerIndex) {
    s32 map;
    s32 exit;
    s32 pad;
    s32 savedMap;
    s32 savedExit;

    healthRefill(playerIndex);
    if (gGlobalOverlayFlags & 1) {
        player->subState++;
        if (gGlobalCutsceneFlags & 2) {
            flagSet(0x5C, 1, 2);
            map = 0x22;
            exit = 0xC;
        } else {
            if (gCurrentMap == 0x3C) {
                map = 0x3E;
                exit = 1;
            } else {
                map = 0x2A;
                exit = 2;
            }
        }
        mapRequestTransition(map, exit);
        return;
    }
    if (gGlobalOverlayFlags & 0x400) {
        player->subState++;
        mapFindPreviousSavedMap(&savedMap, &savedExit);
        mapRequestTransition(savedMap, savedExit);
        return;
    }
    if (gPlayerCount >= 2) {
        func_80026D40(player, playerIndex);
        return;
    }
    mapExecuteDeathTransition(playerIndex);
}

void controllerFilterInput(OSContPad *pads) {
    s32 i;

    controllerGetReadData(pads);
    for (i = 0; i < 4; i++) {
        pads[i].stick_x &= gControllerStickXMask;
        pads[i].stick_y &= gControllerStickYMask;
        pads[i].button &= gControllerButtonMask;
    }
}

extern u64 gPauseTimeTotal;
extern u64 gPauseStartTime;
extern u8 gDemoFixedAnimRate;

void menuSeedRandom(void) {
    u64 elapsed;

    demoPlaybackReset();
    if ((gMenuTargetMode == 3) || (gMenuTargetMode == 4)) {
        setRandomSeed(0x8E32B6F7U);
        gDemoFixedAnimRate = 1;
    } else {
        setRandomSeed(osGetTime());
        gDemoFixedAnimRate = 0;
    }
    gControllerStickXMask = 0;
    gControllerStickYMask = 0;
    gMenuCurrentMode = gMenuTargetMode;
    gMenuDemoActive = 0;
    gMenuDemoOverlayFrames = 0;
    if (gGlobalPauseFlags & 2) {
        elapsed = osGetTime() - gPauseStartTime;
        gPauseTimeTotal += elapsed;
        if (gMenuBonusTimer.active != 0) {
            gMenuBonusTimer.time += elapsed;
        }
    }
}

extern u8 gActivePlayerCount;
extern u16 gButtonsPressed;

void menuSetupDemoPlayback(void) {
    if (gMenuTargetMode == 3) {
        demoPlaybackLoad(gMenuDemoEntries[gMenuDemoIndex].recordingIndex);
        gPlayerCharacterId[0] = demoGetStartKong();
    }
}

extern u8 gEepromLoaded;
extern u8 gCurrentWorldId;
extern Mtx gMenuHalfScaleMtx;

void menuCheckMapTransitionOnLoad(void) {
    u8 blocked;

    blocked = flagGet(0x302, 0);
    gMenuFramesSinceLoad = 0;
    gMenuTransitionFlag = 0;
    if (gEepromLoaded == 0) {
        eepromInit();
    }
    if (mapGetHubWorldIndex(gCurrentWorldId, 1) == 8 && !(gGlobalCutsceneFlags & 2) && gCurrentMap != 0xD6
        && menuGetTimerFlag() == 0 && blocked == 0) {
        menuTimerInit();
    }
    guScale(&gMenuHalfScaleMtx, 0.5f, 0.5f, 1.0f);
    switch (gMenuCurrentMode) {
    case 0:
        gMenuStateTimer = 0x708;
        gControllerButtonMask = 0;
        gMenuEntryCutscenePending = 1;
        gMenuEntryCutscene = 0;
        break;
    case 1:
        gMenuStateTimer = 0x708;
        gControllerButtonMask = 0x1000;
        gMenuEntryCutscenePending = 1;
        gMenuEntryCutscene = 0;
        break;
    case 2:
        gMenuStateTimer = 0x1644;
        gControllerButtonMask = 0x1000;
        gMenuEntryCutscenePending = 1;
        gMenuEntryCutscene = 0;
        break;
    case 3:
        gMenuTransitionCounter++;
        gMenuStateTimer = demoPlaybackStart(gPlayerSlots->actor, gMenuDemoEntries[gMenuDemoIndex].recordingIndex);
        gMenuStateTimer = MIN(gMenuStateTimer, gMenuDemoEntries[gMenuDemoIndex].maxTime);
        gMenuDemoIndex++;
        gMenuDemoIndex %= sizeof(gMenuDemoEntries) / sizeof(gMenuDemoEntries[0]);
        gControllerButtonMask = 0x1000;
        break;
    case 7:
        gMenuStateTimer = 0x410;
        gMenuTargetMode = gMenuCurrentMode = 9;
    case 9:
        gControllerButtonMask = 0x9000;
        break;
    case 5:
        gMpSettings.matchPhase = 0;
    case 6:
    case 12:
    case 13:
        gMenuStateTimer = 1;
        gControllerButtonMask = 0xFFFF;
        gControllerStickXMask = 0xFF;
        gControllerStickYMask = 0xFF;
        break;
    case 10:
        gMenuStateTimer = 1;
        gControllerStickXMask = 0;
        gControllerStickYMask = 0;
        gControllerButtonMask = 0;
        actorSpawn(0x152, 0);
        break;
    case 14:
        actorSpawn(0x152, 0);
    case 11:
        gMenuStateTimer = 0x1E;
        break;
    }
    eepromSavePlayerData();
}

void menuReturnToTitle(void) {
    gActivePlayerCount = 1;
    menuTransitionWithState(0x50, 0, 5);
}

void menuCheckCutsceneTransition(s32 *map, s32 *exit) {
    if ((gMenuCurrentMode == 0xC) && (!(gGlobalCutsceneFlags & 2) || (gCurrentMap == 0xCF) || (*map == 0x22))) {
        *map = 0x50;
        *exit = 0;
        gMenuTargetMode = 5;
        return;
    }
    if ((gMenuCurrentMode == 0xD) && (gCurrentMap != *map)) {
        *map = 0xF;
        *exit = 0;
        gMenuTargetMode = 6;
        return;
    }
    if (gMenuTransitionFlag != 0) {
        *map = -1;
    }
}


void menuUpdateTitleOrTransition(void) {
    s32 map;
    s32 exit;

    if ((gMenuFramesSinceLoad >= 0x5A) && (gPadPressedButtons[0] & 0x1000)) {
        menuReturnToTitle();
    } else if (gMenuStateTimer == 0) {
        if (gMenuTransitionCounter >= 3) {
            menuTransitionRequest(0x28, 0, 1);
        } else {
            demoPlaybackLoad(gMenuDemoEntries[gMenuDemoIndex].recordingIndex);
            demoGetStartMap(&map, &exit);
            screenSetTransitionFadeType(1);
            mapRequestTransition(map, exit);
        }
    }
}


void menuHandleTitleScreenTransition(void) {
    gMenuStateTimer = 0x1E;
    if (gButtonsPressed & 0x8000) {
        transitionSetState(0);
        menuTransitionWithState(0x50, 0, 5);
    }
}


void menuHandleCutsceneScreenTransition(void) {
    if (camIsCutsceneActive()) {
        gMenuStateTimer = 0x1E;
    }
    if ((gMenuTransitionFlag == 1) || (gMenuStateTimer == 0) || (gButtonsPressed & 0x8000)) {
        transitionSetState(0);
        gMenuTransitionFlag = 0;
        menuTransitionWithState(0x50, 0, 5);
        gMenuTransitionFlag = 2;
    }
}
void menuHandleIntroScreenTransition(void) {
    if ((gMenuFramesSinceLoad >= 0x1E && (gButtonsPressed & 0x9000)) || gMenuStateTimer == 0) {
        menuTransitionRequest(0x28, 0, 1);
    }
}


void menuStartDemo(void) {
    s32 map;
    s32 exit;

    gMenuTransitionCounter = 0;
    demoPlaybackLoad(gMenuDemoEntries[gMenuDemoIndex].recordingIndex);
    demoGetStartMap(&map, &exit);
    screenSetTransitionFadeType(1);
    menuTransitionWithState(map, exit, 3);
}

void menuHandleBonusStageTransition(void) {
    if ((gMenuStateTimer == 0) || ((gMenuFramesSinceLoad >= 0xA) && (gPadPressedButtons[0] & 0x1000))) {
        menuStartDemo();
    }
}

void menuHandleDemoModeTransition(void) {
    if ((gMenuDemoActive != 0)
        || ((gMenuCurrentMode == 1) && (gMenuFramesSinceLoad >= 0x5A) && (gPadPressedButtons[0] & 0x1000))) {
        menuTransitionRequest(0x4C, 0, 2);
    }
}
extern Gfx D_1000118;
extern Mtx D_20000C0;
extern Mtx D_2000180;

Gfx *menuOverlayGfxInit(Gfx *gfx) {
    gfx = gfxInit2DDisplayList(gfx);

    gSPDisplayList(gfx++, &D_1000118);
    gSPMatrix(gfx++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 10, 10, 309, 229);
    return gfx;
}

Gfx *menuDrawDemoHeaderText(Gfx *dl) {
    f32 y = 20.0f;
    u8 *text;

    text = textTableGetString(0xC, 0, 1);
    gDPSetCombineMode(dl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gSPMatrix(dl++, &gMenuHalfScaleMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return textDrawStringVtx(dl, 1, 0x118, y * 2.0f * 4.0f, text, 4);
}

extern s16 gScreenWidth;


Gfx *menuDrawDemoCaption(Gfx *dl, u8 alpha) {
    u8 *str;
    u8 *text;
    f32 y;
    f32 x;
    s16 xFixed;
    f64 halfWidth;
    s32 len;

    text = textTableGetString(0xC, 1, 1);
    len = strlen(text) + 2;
    x = gScreenWidth * 0.5 * 2.0f;
    y = 418.0f;
    str = heapAlloc(len);
    heapFreeDeferred(str);
    _sprintf(str, "%c%s", 0x63, text);
    halfWidth = textGetStringWidth(1, str);
    halfWidth = 0.5 * halfWidth;
    x = x - halfWidth;
    xFixed = x * 4.0f;
    gDPSetRenderMode(dl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, alpha);
    gDPSetCombineLERP(dl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    return textDrawStringVtx(dl, 1, xFixed, y * 4.0f, str, 4);
}

extern u8 gHiResScale;
extern u8 gControllerConnectedMask;

Gfx *menuDrawBlinkingPromptText(Gfx *dl) {
    s32 elapsed;
    s32 textIndex;
    TextIdPair textIds;
    f32 x;
    f32 y;

    elapsed = gFrameCounter - 0x5A;
    if ((elapsed >= 0) && !(elapsed & 0x10)) {
        textIds = gMenuPromptTextIds;
        textIndex = 0;
        x = gScreenWidth;
        y = 0xBD - textGetFontHeight(6);
        if (gControllerConnectedMask != 0) {
            if ((menuIsTransitionType3Or4() == 0) || (gCurrentMap == 0x4C)) {
                return dl;
            }
            textIndex = 1;
        }
        x = x * 0.5;
        gDPSetCombineMode(dl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        dl = hudDrawScaledText(dl, x * 4.0f, gHiResScale * y * 4.0f, 0.7f, textTableGetString(0xC, textIds.ids[textIndex], 1));
    }
    return dl;
}

Gfx *mathIdentityS32(Gfx *dl) {
    return dl;
}
extern s16 gScreenHeight;

Gfx *menuDrawDemoSprite(Gfx *dl, u8 alpha, f32 yOffset) {
    f32 x;
    f32 y;

    x = gScreenWidth * 0.5;
    y = gScreenHeight * 0.5 + -20.0 + yOffset;
    gDPSetRenderMode(dl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, alpha);
    gDPSetCombineLERP(dl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetTextureFilter(dl++, G_TF_POINT);
    return renderRotatedSprite(dl, 0x2C, 0, 2, 0xE0, 0x80, x, y, 1.0f, 1.0f, 0, 0.0f);
}


Gfx *menuDrawPromptOverlay(Gfx *dl) {
    return menuDrawBlinkingPromptText(menuOverlayGfxInit(dl));
}

Gfx *menuDrawDemoOverlay(Gfx *dl) {
    Vp *rect;
    f32 fade;
    Gfx *g;

    rect = heapAlloc(sizeof(Vp));
    heapFreeDeferred(rect);
    viewportSetFromRect(rect->vp.vscale, 10, 10, 309, 229);
    dl = menuDrawBlinkingPromptText(menuOverlayGfxInit(dl));
    dl = menuDrawDemoHeaderText(dl);
    if (++gMenuDemoOverlayFrames < 0xD3) {
        fade = (0xD2 - gMenuDemoOverlayFrames) * (1.0f / 30.0f);
        fade = (fade < 0.0f) ? 0.0f : ((fade > 1.0f) ? 1.0f : fade);
        dl = menuDrawDemoSprite(menuDrawDemoCaption(dl, 255.0f * fade), 255.0f * fade, 0);
    }
    g = dl++; g->words.w0 = 0xDC080008; // LAYOUT: same-line pointer-copy and first store steers as1 move/ori order
    g->words.w1 = (u32)rect;
    return playerViewDrawCornerMasks(dl);
}


Gfx *menuGameOverGfxInit(Gfx *dl) {
    gDPPipeSync(dl++);
    gSPDisplayList(dl++, &D_1000118);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    gDPSetRenderMode(dl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineMode(dl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gSPMatrix(dl++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    return dl;
}

Gfx *menuDrawGameOverText(Gfx *dl) {
    s16 remaining;
    s16 pad0;
    s16 alpha;
    f32 scale;

    remaining = gMenuStateTimer - 0x8C;
    if ((remaining >= 0) && (remaining < 0x96)) {
        alpha = remaining - 0x5A;
        if (alpha < 0) {
            alpha = 0xFF;
        } else {
            alpha = 0x3C - alpha;
            alpha = alpha * 5;
        }
        if (remaining < 0x3C) {
            alpha = remaining * 5;
        }
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        dl = menuGameOverGfxInit(dl);
        gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, alpha);
        scale = (0x96 - remaining) / 40.0;
        dl = hudDrawScaledText(dl, 0x280, 480.0 - scale * 32.0, scale, gGameOverText);
    }
    return dl;
}



extern u64 gLastPauseDuration;

void menuTimerUpdateCountdown(void) {
    u64 elapsed;

    gMenuStateTimer = 1;
    if (gMenuBonusTimer.active != 0) {
        if (flagGet(0x302, 0) != 0) {
            menuClearTimerFlag();
            sfxAllocateChannel(0x74, 1.0f);
            return;
        }
        gMenuBonusTimer.time += gLastPauseDuration;
        if (!(gGlobalPauseFlags & 2)) {
            elapsed = OS_CYCLES_TO_USEC(osGetTime() - gMenuBonusTimer.time);
            gMenuBonusTimer.remaining = gMenuBonusTimer.duration - (u32)(elapsed / 1000000);
            if ((gMenuBonusTimer.index < sizeof(gMenuBonusTimerThresholds) / sizeof(gMenuBonusTimerThresholds[0]))
                && (gMenuBonusTimer.remaining == gMenuBonusTimerThresholds[gMenuBonusTimer.index])) {
                sfxPlayOnFreeSlot(0x2D4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                gMenuBonusTimer.index++;
            }
            if (gMenuBonusTimer.remaining <= 0) {
                menuResetAndTransitionToCredits();
            }
        }
    }
}


Gfx *hudDrawCountdownTimer(Gfx *dl) {
    s32 pad[8];
    f32 timerX;

    if ((menuGetTimerFlag() != 0) && !(gGlobalPauseFlags & 3)) {
        timerX = gScreenWidth * 0.5f;
        dl = menuOverlayGfxInit(dl);
        gDPSetCombineMode(dl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
        dl = renderTimerMinutesSecondsHUD(dl, timerX, 214.0f, gMenuBonusTimer.remaining);
    }
    return dl;
}

Gfx *mathIdentityS32B(Gfx *dl) {
    return dl;
}

void menuTransitionToMapIfUnlocked(s32 map, s32 cutscene, s32 gate) {
    s32 pad;
    s32 total;
    s32 i;

    if (map >= 0) {
        if (gMenuCurrentMode == 0xE) {
            if ((gate == 1) && (flagGet(0x2A, 1) == 0)) {
                map = -1;
            }
            if ((gate == 2) && (flagGet(0x2B, 1) == 0)) {
                map = -1;
            }
        } else {
            hudPauseMenuRefreshTotals();
            total = 0; for (i = 0; i < 7; i++) { total += gPauseCollectibleCounts[i]; } if (gate == 1) { // LAYOUT: one source line lets as1 reorder the unrolled loads
                if (total < 0x118) {
                    map = -1;
                } else {
                    flagSet(0x2A, 1, 1);
                }
            }
            if (gate == 2) {
                if (total < 0x119) {
                    map = -1;
                } else {
                    flagSet(0x2B, 1, 1);
                }
            }
        }
        if (map >= 0) {
            menuTransitionToMap(map, cutscene);
            return;
        }
    }
    if (gMenuCurrentMode == 0xE) {
        transitionSetState(0);
        menuTransitionWithState(0x50, 0, 5);
        return;
    }
    menuTransitionRequest(0x28, 0, 1);
}

Gfx *screenStateTickAndDraw(Gfx *dl) {
    char buffer[40];

    if ((gMenuEntryCutscenePending != 0) && (gFrameCounter == 1)) {
        gMenuEntryCutscenePending = 0;
        if (gMenuEntryCutscene >= 0) {
            camStartPath(NULL, gMenuEntryCutscene, 1);
        }
    }
    if (gDebugSecurityCode != 0) {
        dl = menuOverlayGfxInit(dl);
        _sprintf(buffer, "SECURITY %d", gDebugSecurityCode);
        dl = hudDrawScaledText(dl, 0x280, 0x1E0, 1.0f, buffer);
    }
    gDebugSecurityCode = 0;
    gDPPipeSync(dl++);
    if (gMenuFramesSinceLoad < 0x5A) {
        gMenuFramesSinceLoad++;
    }
    if ((menuGetTimerFlag() != 0) && (gMenuCurrentMode != 6)) {
        menuClearTimerFlag();
    }
    if ((gMenuStateTimer != 0) && (gMenuCurrentMode == gMenuTargetMode)) {
        gMenuStateTimer--;
        switch (gMenuCurrentMode) {
        case 0:
        case 1: menuHandleDemoModeTransition(); break;
        case 2: menuHandleBonusStageTransition(); break;
        case 3: menuUpdateTitleOrTransition(); break;
        case 7:
        case 9: menuHandleIntroScreenTransition(); break;
        case 14: menuHandleTitleScreenTransition(); break;
        case 11: menuHandleCutsceneScreenTransition(); break;
        case 6: menuTimerUpdateCountdown(); break;
        }
    }
    switch (gMenuCurrentMode) {
    case 0:
    case 1: dl = mathIdentityS32(dl); break;
    case 2: dl = menuDrawPromptOverlay(dl); break;
    case 3: dl = menuDrawDemoOverlay(dl); break;
    case 7:
    case 9: dl = menuDrawGameOverText(dl); break;
    case 6: dl = hudDrawCountdownTimer(dl); break;
    case 5: dl = mathIdentityS32B(dl); break;
    case 11: break;
    }
    return dl;
}

extern s8 gSplitScreenMode;

s32 menuIsTransitionType3Or4(void) {
    s32 match;

    match = gMenuTargetMode == 3;
    if (match == 0) {
        match = gMenuTargetMode == 4;
        if (match == 0) {
            match = gMenuCurrentMode == 3;
            if (match == 0) {
                return gMenuCurrentMode == 4;
            }
        }
    }
}

s32 menuIsTransitionType6(void) {
    s32 match;

    match = gMenuCurrentMode == 6;
    if (match == 0) {
        return gMenuTargetMode == 6;
    }
}

s32 menuIsTransitionType8(void) {
    s32 match;

    match = gMenuCurrentMode == 8;
    if (match == 0) {
        return gMenuTargetMode == 8;
    }
}

s32 menuIsTransitionType7Or9(void) {
    s32 match;

    match = gMenuCurrentMode == 7;
    if (match == 0) {
        match = gMenuTargetMode == 7;
        if (match == 0) {
            match = gMenuCurrentMode == 9;
            if (match == 0) {
                return gMenuTargetMode == 9;
            }
        }
    }
}

s32 menuIsTransitionTypeD(void) {
    s32 match;

    match = gMenuCurrentMode == 0xD;
    if (match == 0) {
        return gMenuTargetMode == 0xD;
    }
}

s32 menuIsTransitionTypeC(void) {
    s32 match;

    match = gMenuCurrentMode == 0xC;
    if (match == 0) {
        return gMenuTargetMode == 0xC;
    }
}

s32 menuIsTransitionType5(void) {
    return gMenuCurrentMode == 5;
}

s32 menuIsTransitionTypeAOrE(void) {
    s32 match;

    match = gMenuCurrentMode == 0xA;
    if (match == 0) {
        match = gMenuCurrentMode == 0xE;
        if (match == 0) {
            match = gMenuTargetMode == 0xA;
            if (match == 0) {
                return gMenuTargetMode == 0xE;
            }
        }
    }
}

extern s8 gSkipCutscenes;
extern u8 gEepromCurrentSlot;

void menuStartGameFromSave(s8 saveSlot) {
    s32 map;
    s32 exit;

    gPauseTimeTotal = osGetTime();
    gMenuBonusTimer.active = 0;
    playerResetSpawnGlobals();
    flagsClearAllBank2();
    eepromLoadPlayerData(saveSlot, 1);
    gPlayerCharacterId[0] = 0;
    if ((eepromGetField(0xD, 0, 0, gEepromCurrentSlot) != 0) || (gSkipCutscenes != 0)) {
        if (flagGet(0x186, 0) != 0) {
            map = 0x22;
            exit = 0;
        } else {
            map = 0xB0;
            exit = 1;
        }
    } else {
        gMenuEntryCutscenePending = 1;
        gMenuEntryCutscene = 0;
        map = 0x99;
        exit = 0;
    }
    mapRequestTransitionFast(map, exit);
    gMenuTargetMode = 6;
}



void mpStartMatch(void) {
    s32 map;

    playerResetSpawnGlobals();
    gSplitScreenMode = 0;
    if (gMpSettings.matchType == 0) {
        gSplitScreenMode = 1;
        map = 0x6B;
    } else {
        map = gMpMatchMaps[gMpSettings.mapIndex];
    }
    menuTransitionWithState(map, 0, 6);
}

void menuSetDemoActive(void) {
    gMenuDemoActive = 1;
}


s32 mpIsMatchType(s32 value) {
    s32 isMultiplayer;

    isMultiplayer = gPlayerCount >= 2;
    if (isMultiplayer) {
        return value == gMpSettings.matchType;
    }
}

void menuReturnToTitleWithMode3(void) {
    menuReturnToTitle();
    gMpSettings.matchPhase = 3;
}

void menuNoop714660(void) {
}
