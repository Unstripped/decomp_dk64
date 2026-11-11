#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/boot/3630.h"
#include "proto/boot/3D20.h"
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

extern Actor *gCurrentActor;
extern PlayerStruct *gPlayerSlots;
extern s32 gCurrentMap;
extern u32 gGlobalCutsceneFlags;
extern u8 gMenuCurrentMode;
extern u8 gMenuTargetMode;

extern s8 D_8075536C;
extern s32 D_80755338;
extern s32 D_8075533C;
extern s8 gMenuTransitionFlag;
extern s8 D_80750754;

void menuTransitionWithState(s32 map, s32 exit, u8 mode) {
    mapRequestTransition(map, exit);
    gMenuTargetMode = mode;
}


void menuTransitionRequest(s32 map, s32 exit, u8 mode) {
    if (menuIsTransitionActive() == 0) {
        screenSetTransitionFadeType(0);
        menuTransitionWithState(map, D_8075536C, mode);
        D_80755338 = 1;
        D_8075533C = exit;
        D_8075536C = 0;
    }
}

void menuTransitionToMap(s32 map, s32 exit) {
    menuTransitionRequest(map, exit, gMenuTargetMode);
}

s32 menuCalculateBonusDuration(void) {
    return flagCountRange(0x1FD, 0x28, 0) + 0xA;
}

typedef struct R117gTimedState {
    u64 time;
    s32 unk8;
    s32 duration;
    u8 active;
    u8 index;
} R117gTimedState;

extern R117gTimedState D_80755340;
extern u16 D_80755358[];

void menuTimerInit(void) {
    u32 i;
    s32 found = 0;

    D_80755340.active = 1;
    D_80755340.index = 0;
    D_80755340.time = osGetTime();
    D_80755340.duration = menuCalculateBonusDuration() * 60;
    for (i = 0; (i < 10) && (found == 0); i++) {
        if (D_80755358[i] < D_80755340.duration) {
            D_80755340.index = i;
            found = 1;
        }
    }
}

void menuClearTimerFlag(void) {
    D_80755340.active = 0;
}

s32 menuGetTimerFlag(void) {
    return D_80755340.active;
}

void menuTransitionRequestTypeB(s32 map, s32 exit) {
    menuTransitionRequest(map, exit, 0xB);
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

extern u8 gPlayerInventoryTable[][0x5E];
extern s8 gPlayerCharacterId;

void menuSetupPlayerInventory(s32 map, s32 exit, s32 characterId, s8 inventory0, s8 inventory1, s8 inventory4, s8 shared) {
    s32 i;

    gPlayerCharacterId = characterId;
    gPlayerInventoryTable[8][0xC] = shared;
    gPlayerInventoryTable[8][0xB] = shared * 4;
    for (i = 0; i < 5; i++) {
        gPlayerInventoryTable[i][0] = inventory0;
        gPlayerInventoryTable[i][1] = inventory1;
        gPlayerInventoryTable[i][4] = inventory4;
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
    u8 temp;

    if (toCredits == 0) {
        temp = 0xA;
    } else {
        temp = 0xE;
    }
    menuTransitionRequest(0x99, 0xB, temp);
    D_80750754 = -2;
}

extern s32 gGlobalOverlayFlags;
extern u8 gPlayerCount;
void func_80026D40(void *);

void playerRefillHealth(Actor *player, s32 playerIndex) {
    s32 map;
    s32 exit;
    s32 pad;
    s32 savedMap;
    s32 savedExit;

    healthRefill((u8) playerIndex);
    if (playerIndex == 0) {} // FAKE: keeps playerIndex in a1 with an eager restore after healthRefill
    if (gGlobalOverlayFlags & 1) {
        player->unk155++;
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
        player->unk155++;
        mapFindPreviousSavedMap(&savedMap, &savedExit);
        mapRequestTransition(savedMap, savedExit);
        return;
    }
    if (gPlayerCount >= 2) {
        func_80026D40(player);
        return;
    }
    mapExecuteDeathTransition(playerIndex);
}

extern u16 gControllerButtonMask;
extern u8 gControllerStickXMask;
extern u8 gControllerStickYMask;

void controllerFilterInput(OSContPad *pads) {
    s32 i;

    controllerGetReadData(pads);
    for (i = 0; i < 4; i++) {
        pads[i].stick_x &= gControllerStickXMask;
        pads[i].stick_y &= gControllerStickYMask;
        pads[i].button &= gControllerButtonMask;
    }
}
extern u8 gMenuDemoActive;


extern u64 D_807445B8;
extern u64 D_807445C0;
extern s8 D_80746B60;
extern u32 gGlobalPauseFlags;
extern s32 D_80755320;


void menuSeedRandom(void) {
    u64 elapsed;

    func_8060B6CC();
    if ((gMenuTargetMode == 3) || (gMenuTargetMode == 4)) {
        setRandomSeed(0x8E32B6F7U);
        D_80746B60 = 1;
    } else {
        setRandomSeed((u32)osGetTime());
        D_80746B60 = 0;
    }
    gControllerStickXMask = 0;
    gControllerStickYMask = 0;
    gMenuCurrentMode = gMenuTargetMode;
    gMenuDemoActive = 0;
    D_80755320 = 0;
    if (gGlobalPauseFlags & 2) {
        elapsed = osGetTime() - D_807445C0;
        D_807445B8 += elapsed;
        if (D_80755340.active != 0) {
            D_80755340.time += elapsed;
        }
    }
}

extern u8 gMenuBonusStageIndex;
extern u8 gActivePlayerCount;
extern u16 gMenuStateTimer;
extern u16 D_807ECD66;
extern u8 D_8075E5C0[];


void menuSetupBonusCharacter(void) {
    if (gMenuTargetMode == 3) {
        func_8060B750(D_8075E5C0[gMenuBonusStageIndex * 4]);
        gPlayerCharacterId = func_8060B7C4();
    }
}

extern u16 D_8075E5C2[];

extern u8 D_807467CC;
extern u8 gCurrentWorldId;
extern u8 gMenuTransitionCounter;
extern s32 D_80755334;
extern s32 D_807552EC;
extern Mtx D_807FDAC0;

void menuCheckMapTransitionOnLoad(void) {
    u8 blocked;

    blocked = flagGet(0x302, 0);
    D_80755334 = 0;
    gMenuTransitionFlag = 0;
    if (D_807467CC == 0) {
        eepromInit();
    }
    if (mapGetHubWorldIndex(gCurrentWorldId, 1) == 8) {
        if ((gGlobalCutsceneFlags & 2) == 0) {
            if (gCurrentMap != 0xD6) {
                if (menuGetTimerFlag() == 0) {
                    if (blocked == 0) {
                        menuTimerInit();
                    }
                }
            }
        }
    }
    guScale(&D_807FDAC0, 0.5f, 0.5f, 1.0f);
    switch (gMenuCurrentMode) {
    case 0:
        gMenuStateTimer = 0x708;
        gControllerButtonMask = 0;
        D_80755338 = 1;
        D_8075533C = 0;
        break;
    case 1:
        gMenuStateTimer = 0x708;
        gControllerButtonMask = 0x1000;
        D_80755338 = 1;
        D_8075533C = 0;
        break;
    case 2:
        gMenuStateTimer = 0x1644;
        gControllerButtonMask = 0x1000;
        D_80755338 = 1;
        D_8075533C = 0;
        break;
    case 3:
        gMenuTransitionCounter++;
        gMenuStateTimer = func_8060B49C(gPlayerSlots->actor, D_8075E5C0[gMenuBonusStageIndex * 4]);
        gMenuStateTimer = MIN(gMenuStateTimer, *(u16 *) ((u8 *) D_8075E5C2 + gMenuBonusStageIndex * 4));
        gMenuBonusStageIndex++;
        gMenuBonusStageIndex = (u32) gMenuBonusStageIndex % 5U;
        gControllerButtonMask = 0x1000;
        break;
    case 7:
        gMenuStateTimer = 0x410;
        gMenuTargetMode = gMenuCurrentMode = 9;
    case 9:
        gControllerButtonMask = 0x9000;
        break;
    case 5:
        D_807552EC = 0;
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
    if (gMenuCurrentMode == 0xC) {
        if (((gGlobalCutsceneFlags & 2) == 0) || (gCurrentMap == 0xCF) || (*map == 0x22)) {
            *map = 0x50;
            *exit = 0;
            gMenuTargetMode = 5;
            return;
        }
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


extern u16 D_807ECD48;
void menuUpdateTitleOrTransition(void) {
    s32 map;
    s32 exit;

    if ((D_80755334 >= 0x5A) && (D_807ECD48 & 0x1000)) {
        menuReturnToTitle();
    } else if (gMenuStateTimer == 0) {
        if (gMenuTransitionCounter >= 3) {
            menuTransitionRequest(0x28, 0, 1);
        } else {
            func_8060B750(D_8075E5C0[gMenuBonusStageIndex * 4]);
            func_8060B7D0(&map, &exit);
            screenSetTransitionFadeType(1);
            mapRequestTransition(map, exit);
        }
    }
}


void menuHandleTitleScreenTransition(void) {
    gMenuStateTimer = 0x1E;
    if (D_807ECD66 & 0x8000) {
        transitionSetState(0);
        menuTransitionWithState(0x50, 0, 5);
    }
}


void menuHandleCutsceneScreenTransition(void) {
    if (camIsCutsceneActive()) {
        gMenuStateTimer = 0x1E;
    }
    if ((gMenuTransitionFlag == 1) || (gMenuStateTimer == 0) || (D_807ECD66 & 0x8000)) {
        transitionSetState(0);
        gMenuTransitionFlag = 0;
        menuTransitionWithState(0x50, 0, 5);
        gMenuTransitionFlag = 2;
    }
}
void menuHandleIntroScreenTransition(void) {
    if ((D_80755334 >= 0x1E && (D_807ECD66 & 0x9000)) || gMenuStateTimer == 0) {
        menuTransitionRequest(0x28, 0, 1);
    }
}


void menuStartSelectedBonusStage(void) {
    s32 map;
    s32 exit;

    gMenuTransitionCounter = 0;
    func_8060B750(D_8075E5C0[gMenuBonusStageIndex * 4]);
    func_8060B7D0(&map, &exit);
    screenSetTransitionFadeType(1);
    menuTransitionWithState(map, exit, 3);
}

void menuHandleBonusStageTransition(void) {
    if ((gMenuStateTimer == 0) || ((D_80755334 >= 0xA) && (D_807ECD48 & 0x1000))) {
        menuStartSelectedBonusStage();
    }
}

void menuHandleDemoModeTransition(void) {
    if (gMenuDemoActive == 0) {
        if (gMenuCurrentMode != 1) {
            return;
        }
        if (D_80755334 < 0x5A) {
            return;
        }
        if ((D_807ECD48 & 0x1000) == 0) {
            return;
        }
    }
    menuTransitionRequest(0x4C, 0, 2);
}
#define R117D_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }
extern Gfx D_1000118;
extern Mtx D_20000C0;
extern Mtx D_2000180;

Gfx *func_807132DC(Gfx *gfx) {
    gfx = gfxInit2DDisplayList(gfx);

    R117D_WRITE_GFX(gfx++, 0xDE000000, &D_1000118);
    R117D_WRITE_GFX(gfx++, 0xDA380007, &D_20000C0);
    R117D_WRITE_GFX(gfx++, 0xDA380003, &D_2000180);
    R117D_WRITE_GFX(gfx++, 0xE7000000, 0);
    R117D_WRITE_GFX(gfx++, 0xFC11FE23, 0xFFFFF7FB);
    R117D_WRITE_GFX(gfx++, 0xFA000000, 0xFFFFFFFF);
    R117D_WRITE_GFX(gfx++, 0xED028028, 0x4D4394);
    return gfx;
}

Gfx *func_8071338C(Gfx *dl) {
    f32 y = 20.0f;
    void *text;

    text = textTableGetString(0xC, 0, 1);
    R117D_WRITE_GFX(dl++, 0xFCFFFFFF, 0xFFFCF279);
    R117D_WRITE_GFX(dl++, 0xDA380003, &D_807FDAC0);
    return textDrawStringVtx(dl, 1, 0x118, (s16) ((y + y) * 4.0f), text, 4);
}


#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/D_8075E5C0.s")

extern s16 gScreenWidth;


Gfx *func_80713438(Gfx *dl, u8 alpha) {
    u8 *str;
    u8 *text;
    f32 y;
    f32 x;
    s16 xFixed;
    f64 halfWidth;
    s32 len;

    text = textTableGetString(0xC, 1, 1);
    len = strlen(text) + 2;
    x = (f32) ((f64) gScreenWidth * 0.5 * 2.0f);
    y = 418.0f;
    str = heapAlloc(len);
    heapFreeDeferred(str);
    _sprintf(str, "%c%s", 0x63, text);
    halfWidth = (f64) textGetStringWidth(1, str);
    halfWidth = 0.5 * halfWidth;
    x = x - halfWidth;
    xFixed = (s16) ((s32) (x * 4.0f));
    R117D_WRITE_GFX(dl++, 0xE200001C, 0x504240);
    R117D_WRITE_GFX(dl++, 0xFA000000, alpha & 0xFF);
    R117D_WRITE_GFX(dl++, 0xFCFF97FF, 0xFF2CFE7F);
    return textDrawStringVtx(dl, 1, xFixed, (s16) ((s32) (y * 4.0f)), str, 4);
}


typedef struct {
    s32 unk0;
    s32 unk4;
} R117fPair;

extern u8 gHiResScale;
extern R117fPair D_80755370;
extern s32 gFrameCounter;
extern u8 D_807ECD09;

Gfx *func_807135B4(Gfx *dl) {
    s32 elapsed;
    s32 textIndex;
    R117fPair textIds;
    f32 x;
    f32 y;

    elapsed = gFrameCounter - 0x5A;
    if ((elapsed >= 0) && !(elapsed & 0x10)) {
        textIds = D_80755370;
        textIndex = 0;
        x = (f32) gScreenWidth;
        y = (f32) (0xBD - textGetFontHeight(6));
        if ((D_807ECD09 != 0) && ((func_807142D8() == 0) || (textIndex = 1, (gCurrentMap == 0x4C)))) {
            return dl;
        }
        if (&D_80755370 && &D_80755370 && &D_80755370) {}  // FAKE: dead address test, steers as1 delay-slot fill (bne+nop instead of bnel)
        x = (f32) ((f64) x * 0.5);
        R117D_WRITE_GFX(dl++, 0xFCFFFFFF, 0xFFFCF279);
        dl = hudDrawScaledText(dl, (s16) (s32) (x * 4.0f), (s16) (s32) ((f32) gHiResScale * y * 4.0f), 0.7f, textTableGetString(0xC, (s32) (&textIds.unk0)[textIndex], 1));
    }
    return dl;
}

s32 mathIdentityS32(s32 value) {
    return value;
}
extern s16 gScreenHeight;

Gfx *func_80713764(Gfx *dl, u8 alpha, f32 yOffset) {
    f32 x;
    f32 y;

    x = (f32) ((f64) gScreenWidth * 0.5);
    y = (f32) (((f64) gScreenHeight * 0.5) + -20.0 + (f64) yOffset);
    R117D_WRITE_GFX(dl++, 0xE200001C, 0x504240);
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, alpha);
    R117D_WRITE_GFX(dl++, 0xFCFF97FF, 0xFF2CFE7F);
    R117D_WRITE_GFX(dl++, 0xE3001201, 0);
    return renderRotatedSprite(dl, 0x2C, 0, 2, 0xE0, 0x80, (s32) x, (s32) y, 1.0f, 1.0f, 0, 0.0f);
}


Gfx *func_807138A4(Gfx *dl) {
    return func_807135B4(func_807132DC(dl));
}

Gfx *func_807138CC(Gfx *dl) {
    void *rect;
    f32 fade;
    Gfx *g;

    rect = (void *)heapAlloc(0x10);
    heapFreeDeferred(rect);
    viewportSetFromRect(rect, 0xA, 0xA, 0x135, 0xE5);
    dl = func_807135B4(func_807132DC(dl));
    dl = func_8071338C(dl);
    if ((u32)++D_80755320 < 0xD3U) {
        fade = (f32) (0xD2U - D_80755320) * 0.03333333507f;
        fade = (fade < 0.0f) ? 0.0f : ((fade > 1.0f) ? 1.0f : fade);
        dl = func_80713764(func_80713438(dl, (u32) (255.0f * fade)), (u32) (255.0f * fade), 0);
    }
    g = dl++; g->words.w0 = 0xDC080008; // LAYOUT: same-line pointer-copy and first store steers as1 move/ori order
    g->words.w1 = (u32)rect;
    return func_806FF144(dl);
}


Gfx *func_80713AA8(Gfx *dl) {
    R117D_WRITE_GFX(dl++, 0xE7000000, 0);
    R117D_WRITE_GFX(dl++, 0xDE000000, &D_1000118);
    R117D_WRITE_GFX(dl++, 0xE3000A01, 0);
    R117D_WRITE_GFX(dl++, 0xE200001C, 0x504240);
    R117D_WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
    R117D_WRITE_GFX(dl++, 0xDA380007, &D_20000C0);
    return dl;
}

extern u8 D_80755378[];

Gfx *func_80713B40(Gfx *dl) {
    s16 remaining;
    s16 pad0;
    s16 alpha;
    remaining = gMenuStateTimer - 0x8C;
    if (remaining >= 0) {
        if (remaining < 0x96) {
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
            dl = func_80713AA8(dl);
            gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, alpha);
            dl = hudDrawScaledText(dl, 0x280, (s16)(s32)(480.0 - ((f64)(f32)((f64)(0x96 - remaining) / 40.0) * 32.0)), (f32)((f64)(0x96 - remaining) / 40.0), D_80755378);
        }
    }
    return dl;
}



extern u64 D_807445B0;

void func_80713C8C(void) {
    u64 elapsed;

    gMenuStateTimer = 1;
    if (D_80755340.active != 0) {
        if (flagGet(0x302, 0) != 0) {
            menuClearTimerFlag();
            sfxAllocateChannel(0x74, 1.0f);
            return;
        }
        D_80755340.time += D_807445B0;
        if (!(gGlobalPauseFlags & 2)) {
            elapsed = (osGetTime() - D_80755340.time) * 64;
            D_80755340.unk8 = D_80755340.duration - (u32)(elapsed / 3000 / 1000000);
            if (((u32)D_80755340.index < 0xA) && (D_80755340.unk8 == D_80755358[D_80755340.index])) {
                sfxPlayOnFreeSlot(0x2D4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                D_80755340.index++;
            }
            if (D_80755340.unk8 <= 0) {
                menuResetAndTransitionToCredits();
            }
        }
    }
}


Gfx *hudDrawCountdownTimer(Gfx *dl) {
    s32 pad[8];
    f32 timerX;
    Gfx *dlCur;

    if ((menuGetTimerFlag() != 0) && !(gGlobalPauseFlags & 3)) {
        timerX = (f32) gScreenWidth * 0.5f;
        dlCur = func_807132DC(dl);
        R117D_WRITE_GFX(dlCur++, 0xFC119623, 0xFF2FFFFF);
        R117D_WRITE_GFX(dlCur++, 0xFA000000, 0xFFFFFFFF);
        dl = renderTimerMinutesSecondsHUD(dlCur, timerX, 214.0f, D_80755340.unk8);
    }
    return dl;
}

s32 mathIdentityS32B(s32 value) {
    return value;
}

extern s16 D_807FC828[];

void func_80713EB0(s32 map, s32 exit, s32 gate) {
    s32 savedExit;
    s32 total;
    s32 i;

    if (map >= 0) {
        if (gMenuCurrentMode == 0xE) {
            if (gate == 1) {
                if (flagGet(0x2A, 1) == 0) {
                    map = -1;
                }
            }
            if (gate == 2) {
                if (flagGet(0x2B, 1) == 0) {
                    map = -1;
                }
            }
        } else {
            hudPauseMenuRefreshTotals();
            total = 0; for (i = 0; i < 7; i++) { total += D_807FC828[i]; } if (gate == 1) { // LAYOUT: one source line lets as1 reorder the unrolled loads
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
            menuTransitionToMap(map, exit);
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

extern s8 D_807552E0;

Gfx *screenStateTickAndDraw(Gfx *dl) {
    char buffer[40];

    if ((D_80755338 != 0) && (gFrameCounter == 1)) {
        D_80755338 = 0;
        if (D_8075533C >= 0) {
            camStartPath(0, (s16)D_8075533C, 1);
        }
    }
    if (D_807552E0 != 0) {
        dl = func_807132DC(dl);
        _sprintf(buffer, "SECURITY %d", D_807552E0);
        dl = hudDrawScaledText(dl, 0x280, 0x1E0, 1.0f, buffer);
    }
    D_807552E0 = 0;
    R117D_WRITE_GFX(dl++, 0xE7000000, 0);
    if (D_80755334 < 0x5A) {
        D_80755334++;
    }
    if ((menuGetTimerFlag() != 0) && (gMenuCurrentMode != 6)) {
        menuClearTimerFlag();
    }
    if (gMenuStateTimer != 0) {
        if (gMenuCurrentMode == gMenuTargetMode) {
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
            case 6: func_80713C8C(); break;
            }
        }
    }
    switch (gMenuCurrentMode) {
    case 0:
    case 1: dl = (Gfx *)mathIdentityS32((s32)dl); break;
    case 2: dl = func_807138A4(dl); break;
    case 3: dl = func_807138CC(dl); break;
    case 7:
    case 9: dl = func_80713B40(dl); break;
    case 6: dl = hudDrawCountdownTimer(dl); break;
    case 5: dl = (Gfx *)mathIdentityS32B((s32)dl); break;
    case 11: break;
    }
    return dl;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
} R117cState;

extern s32 D_807552E4;
extern s32 D_80755384[];
extern s8 gSplitScreenMode;
#define R117c_STATE ((R117cState *) &D_807552E4)


s32 func_807142D8(void) {
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

extern s8 D_8074452C;
extern u8 D_807467C8;

void func_807144B8(s8 saveSlot) {
    s32 map;
    s32 exit;

    D_807445B8 = osGetTime();
    D_80755340.active = 0;
    playerResetSpawnGlobals();
    flagsClearAllBank2();
    eepromLoadPlayerData(saveSlot, 1);
    gPlayerCharacterId = 0;
    if ((eepromGetField(0xD, 0, 0, D_807467C8) != 0) || (D_8074452C != 0)) {
        if (flagGet(0x186, 0) != 0) {
            map = 0x22;
            exit = 0;
        } else {
            map = 0xB0;
            exit = 1;
        }
    } else {
        D_80755338 = 1;
        D_8075533C = 0;
        map = 0x99;
        exit = 0;
    }
    mapRequestTransitionFast(map, exit);
    gMenuTargetMode = 6;
}



void func_8071458C(void) {
    s32 map;

    playerResetSpawnGlobals();
    gSplitScreenMode = 0;
    if (R117c_STATE->unk0 == 0) {
        gSplitScreenMode = 1;
        map = 0x6B;
    } else {
        map = D_80755384[R117c_STATE->unk20];
    }
    menuTransitionWithState(map, 0, 6);
}

void menuSetFlag5324(void) {
    gMenuDemoActive = 1;
}


s32 func_80714608(s32 value) {
    s32 isMultiplayer;

    isMultiplayer = (s32) gPlayerCount >= 2;
    if (isMultiplayer != 0) {
        return value == D_807552E4;
    }
}

void menuReturnToTitleWithMode3(void) {
    menuReturnToTitle();
    D_807552EC = 3;
}

void menuNoop714660(void) {
}
