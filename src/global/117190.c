#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern void *gPlayerSlots;
extern s32 gCurrentMap;
extern u32 gGlobalCutsceneFlags;
extern u8 gMenuCurrentMode;
extern u8 gMenuTargetMode;

extern s32 flagCountRange(s32, s32, u8);
extern s8 D_8075536C;
extern s32 D_80755338;
extern s32 D_8075533C;
extern u8 D_80755350;
extern s8 gMenuTransitionFlag;
extern s8 D_80750754;




void mapRequestTransition(s32, s32);

void menuTransitionWithState(s32 arg0, s32 arg1, u8 arg2) {
    mapRequestTransition(arg0, arg1);
    gMenuTargetMode = arg2;
}

void screenSetTransitionFadeType(u8);
s32 menuIsTransitionActive(void);

void menuTransitionRequest(s32 arg0, s32 arg1, u8 arg2) {
    if (menuIsTransitionActive() == 0) {
        screenSetTransitionFadeType(0);
        menuTransitionWithState(arg0, D_8075536C, arg2);
        D_80755338 = 1;
        D_8075533C = arg1;
        D_8075536C = 0;
    }
}

void menuTransitionToMap(s32 arg0, s32 arg1) {
    menuTransitionRequest(arg0, arg1, gMenuTargetMode);
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
    D_80755350 = 0;
}

s32 menuGetTimerFlag(void) {
    return D_80755350;
}

void menuTransitionRequestTypeB(s32 arg0, s32 arg1) {
    menuTransitionRequest(arg0, arg1, 0xB);
    gMenuTransitionFlag = 0;
}

s32 menuIsTransitionTypeB(void) {
    s32 var_v0;

    var_v0 = gMenuCurrentMode == 0xB;
    if (var_v0 == 0) {
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

void menuSetupPlayerInventory(s32 arg0, s32 arg1, s32 arg2, s8 arg3, s8 arg4, s8 arg5, s8 arg6) {
    s32 i;

    gPlayerCharacterId = arg2;
    gPlayerInventoryTable[8][0xC] = arg6;
    gPlayerInventoryTable[8][0xB] = arg6 * 4;
    for (i = 0; i < 5; i++) {
        gPlayerInventoryTable[i][0] = arg3;
        gPlayerInventoryTable[i][1] = arg4;
        gPlayerInventoryTable[i][4] = arg5;
    }
    menuTransitionWithState(arg0, arg1, 12);
}

void menuTransitionWithStateD(s32 arg0) {
    menuTransitionWithState(arg0, 0, 0xD);
}

s32 menuIsTransitionActive(void) {
    return gMenuCurrentMode != gMenuTargetMode;

}
void mapSlotArrayResetAll(void);
void flagSet(s16, u8, u8);

void menuResetAndTransitionToCredits(void) {
    mapSlotArrayResetAll();
    flagSet(0x314, 1, 0);
    menuTransitionRequest(0x1C, 0x17, 7);
}

void menuTransitionToCreditsOrMap28(s32 arg0) {
    u8 temp;

    if (arg0 == 0) {
        temp = 0xA;
    } else {
        temp = 0xE;
    }
    menuTransitionRequest(0x99, 0xB, temp);
    D_80750754 = -2;
}

typedef struct R117d2MenuObject {
    u8 unk0[0x155];
    u8 unk155;
} R117d2MenuObject;

extern s32 gGlobalOverlayFlags;
extern u8 gPlayerCount;
void healthRefill(u8);
s32 mapFindPreviousSavedMap(s32 *, s32 *);
void func_80026D40(void *);
void mapExecuteDeathTransition(s32);

void playerRefillHealth(R117d2MenuObject *arg0, s32 arg1) {
    s32 var_a0;
    s32 var_a1;
    s32 pad;
    s32 sp20;
    s32 sp1C;

    healthRefill((u8) arg1);
    if (arg1 == 0) {} // FAKE: keeps arg1 in a1 with an eager restore after healthRefill
    if (gGlobalOverlayFlags & 1) {
        arg0->unk155++;
        if (gGlobalCutsceneFlags & 2) {
            flagSet(0x5C, 1, 2);
            var_a0 = 0x22;
            var_a1 = 0xC;
        } else {
            if (gCurrentMap == 0x3C) {
                var_a0 = 0x3E;
                var_a1 = 1;
            } else {
                var_a0 = 0x2A;
                var_a1 = 2;
            }
        }
        mapRequestTransition(var_a0, var_a1);
        return;
    }
    if (gGlobalOverlayFlags & 0x400) {
        arg0->unk155++;
        mapFindPreviousSavedMap(&sp20, &sp1C);
        mapRequestTransition(sp20, sp1C);
        return;
    }
    if (gPlayerCount >= 2) {
        func_80026D40(arg0);
        return;
    }
    mapExecuteDeathTransition(arg1);
}

extern u16 gControllerButtonMask;
extern u8 gControllerStickXMask;
extern u8 gControllerStickYMask;

void controllerFilterInput(OSContPad *arg0) {
    s32 i;

    controllerGetReadData();
    for (i = 0; i < 4; i++) {
        arg0[i].stick_x &= gControllerStickXMask;
        arg0[i].stick_y &= gControllerStickYMask;
        arg0[i].button &= gControllerButtonMask;
    }
}
extern u8 gMenuDemoActive;


extern u64 D_807445B8;
extern u64 D_807445C0;
extern s8 D_80746B60;
extern u32 gGlobalPauseFlags;
extern s32 D_80755320;

void func_8060B6CC(void);
void setRandomSeed(u32);

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

void func_8060B750(s32);
u8 func_8060B7C4(void);

void menuSetupBonusCharacter(void) {
    if (gMenuTargetMode == 3) {
        func_8060B750(D_8075E5C0[gMenuBonusStageIndex * 4]);
        gPlayerCharacterId = func_8060B7C4();
    }
}

typedef struct R117iPlayerView {
    s32 unk0;
    s32 unk4;
} R117iPlayerView;

extern u16 D_8075E5C2[];

extern u8 D_807467CC;
extern u8 gCurrentWorldId;
extern u8 gMenuTransitionCounter;
extern s32 D_80755334;
extern s32 D_807552EC;
extern Mtx D_807FDAC0;
u8 flagGet(s16, u8);
u8 mapGetHubWorldIndex(u8, u8);
s32 func_8060B49C(s32, s32);
void eepromInit(void);
void menuTimerInit(void);
void eepromSavePlayerData(void);
s32 actorSpawn(s32, s32);

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
        gMenuStateTimer = func_8060B49C(((R117iPlayerView *)gPlayerSlots)->unk4, D_8075E5C0[gMenuBonusStageIndex * 4]);
        if (gMenuStateTimer < *(u16 *) ((u8 *) D_8075E5C2 + gMenuBonusStageIndex * 4)) {
            gMenuStateTimer = gMenuStateTimer;
        } else {
            gMenuStateTimer = *(u16 *) ((u8 *) D_8075E5C2 + gMenuBonusStageIndex * 4);
        }
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

void menuCheckCutsceneTransition(s32 *arg0, s32 *arg1) {
    if (gMenuCurrentMode == 0xC) {
        if (((gGlobalCutsceneFlags & 2) == 0) || (gCurrentMap == 0xCF) || (*arg0 == 0x22)) {
            *arg0 = 0x50;
            *arg1 = 0;
            gMenuTargetMode = 5;
            return;
        }
    }
    if ((gMenuCurrentMode == 0xD) && (gCurrentMap != *arg0)) {
        *arg0 = 0xF;
        *arg1 = 0;
        gMenuTargetMode = 6;
        return;
    }
    if (gMenuTransitionFlag != 0) {
        *arg0 = -1;
    }
}


void func_8060B7D0(s32 *, s32 *);
extern u16 D_807ECD48;
void menuUpdateTitleOrTransition(void) {
    s32 arg0;
    s32 arg1;

    if ((D_80755334 >= 0x5A) && (D_807ECD48 & 0x1000)) {
        menuReturnToTitle();
    } else if (gMenuStateTimer == 0) {
        if (gMenuTransitionCounter >= 3) {
            menuTransitionRequest(0x28, 0, 1);
        } else {
            func_8060B750(D_8075E5C0[gMenuBonusStageIndex * 4]);
            func_8060B7D0(&arg0, &arg1);
            screenSetTransitionFadeType(1);
            mapRequestTransition(arg0, arg1);
        }
    }
}

void transitionSetState(u8);

void menuHandleTitleScreenTransition(void) {
    gMenuStateTimer = 0x1E;
    if (D_807ECD66 & 0x8000) {
        transitionSetState(0);
        menuTransitionWithState(0x50, 0, 5);
    }
}

u8 camIsCutsceneActive(void);

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
    s32 arg0;
    s32 arg1;

    gMenuTransitionCounter = 0;
    func_8060B750(D_8075E5C0[gMenuBonusStageIndex * 4]);
    func_8060B7D0(&arg0, &arg1);
    screenSetTransitionFadeType(1);
    menuTransitionWithState(arg0, arg1, 3);
}
void menuStartSelectedBonusStage(void);

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
Gfx *gfxInit2DDisplayList(void);

void *func_807132DC() {
    Gfx *gfx = gfxInit2DDisplayList();

    R117D_WRITE_GFX(gfx++, 0xDE000000, &D_1000118);
    R117D_WRITE_GFX(gfx++, 0xDA380007, &D_20000C0);
    R117D_WRITE_GFX(gfx++, 0xDA380003, &D_2000180);
    R117D_WRITE_GFX(gfx++, 0xE7000000, 0);
    R117D_WRITE_GFX(gfx++, 0xFC11FE23, 0xFFFFF7FB);
    R117D_WRITE_GFX(gfx++, 0xFA000000, 0xFFFFFFFF);
    R117D_WRITE_GFX(gfx++, 0xED028028, 0x4D4394);
    return gfx;
}
void *textTableGetString(s32, s32, s32);
Gfx * textDrawStringVtx(Gfx *, s16, s16, s16, u8 *, u8);

Gfx *func_8071338C(Gfx *arg0) {
    f32 temp_f0 = 20.0f;
    void *temp_v0;

    temp_v0 = textTableGetString(0xC, 0, 1);
    R117D_WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFCF279);
    R117D_WRITE_GFX(arg0++, 0xDA380003, &D_807FDAC0);
    return textDrawStringVtx(arg0, 1, 0x118, (s16) ((temp_f0 + temp_f0) * 4.0f), temp_v0, 4);
}


#pragma GLOBAL_ASM("asm/global/nonmatchings/117190/D_8075E5C0.s")

extern s16 gScreenWidth;

s32 heapAlloc(s32);
void heapFreeDeferred(void *);
s32 textGetStringWidth(s16, s32);
s32 strlen(char *);
s32 _sprintf(char *, const char *, ...);

Gfx *func_80713438(Gfx *arg0, u8 arg1) {
    s32 sp34;
    s32 sp30;
    f32 y;
    f32 sp28;
    s16 new_var2;
    f64 temp_ft4;
    s32 temp_a0;

    sp30 = (s32) textTableGetString(0xC, 1, 1);
    temp_a0 = strlen((char *) sp30) + 2;
    sp28 = (f32) ((f64) gScreenWidth * 0.5 * 2.0f);
    y = 418.0f;
    sp34 = heapAlloc(temp_a0);
    heapFreeDeferred((void *) sp34);
    _sprintf((char *) sp34, "%c%s", 0x63, sp30);
    temp_ft4 = (f64) textGetStringWidth(1, sp34);
    temp_ft4 = 0.5 * temp_ft4;
    sp28 = (f32) (((f64) sp28) - temp_ft4);
    new_var2 = (s16) ((s32) (sp28 * 4.0f));
    R117D_WRITE_GFX(arg0++, 0xE200001C, 0x504240);
    R117D_WRITE_GFX(arg0++, 0xFA000000, arg1 & 0xFF);
    R117D_WRITE_GFX(arg0++, 0xFCFF97FF, 0xFF2CFE7F);
    return textDrawStringVtx(arg0, 1, new_var2, (s16) ((s32) (y * 4.0f)), (void *) sp34, 4);
}


typedef struct {
    s32 unk0;
    s32 unk4;
} R117fPair;

extern u8 gHiResScale;
extern R117fPair D_80755370;
extern s32 gFrameCounter;
extern u8 D_807ECD09;
u8 textGetFontHeight(s16);
s32 func_807142D8();
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, void *);

Gfx *func_807135B4(Gfx *arg0) {
    s32 temp_v0;
    s32 var_v1;
    R117fPair sp38;
    f32 sp34;
    f32 sp30;

    temp_v0 = gFrameCounter - 0x5A;
    if ((temp_v0 >= 0) && !(temp_v0 & 0x10)) {
        sp38 = D_80755370;
        var_v1 = 0;
        sp34 = (f32) gScreenWidth;
        sp30 = (f32) (0xBD - textGetFontHeight(6));
        if ((D_807ECD09 != 0) && ((func_807142D8() == 0) || (var_v1 = 1, (gCurrentMap == 0x4C)))) {
            return arg0;
        }
        if (&D_80755370 && &D_80755370 && &D_80755370) {}  // FAKE: dead address test, steers as1 delay-slot fill (bne+nop instead of bnel)
        sp34 = (f32) ((f64) sp34 * 0.5);
        R117D_WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFCF279);
        arg0 = hudDrawScaledText(arg0, (s16) (s32) (sp34 * 4.0f), (s16) (s32) ((f32) gHiResScale * sp30 * 4.0f), 0.7f, textTableGetString(0xC, (s32) (&sp38.unk0)[var_v1], 1));
    }
    return arg0;
}

s32 mathIdentityS32(s32 arg0) {
    return arg0;
}
extern s16 gScreenHeight;
Gfx * renderRotatedSprite(Gfx *, u16, s32, s32, u8, u8, s16, s16, f32, f32, s32, f32);

Gfx *func_80713764(Gfx *arg0, u8 arg1, f32 arg2) {
    f32 x;
    f32 y;

    x = (f32) ((f64) gScreenWidth * 0.5);
    y = (f32) (((f64) gScreenHeight * 0.5) + -20.0 + (f64) arg2);
    R117D_WRITE_GFX(arg0++, 0xE200001C, 0x504240);
    gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, arg1);
    R117D_WRITE_GFX(arg0++, 0xFCFF97FF, 0xFF2CFE7F);
    R117D_WRITE_GFX(arg0++, 0xE3001201, 0);
    return renderRotatedSprite(arg0, 0x2C, 0, 2, 0xE0, 0x80, (s32) x, (s32) y, 1.0f, 1.0f, 0, 0.0f);
}

void *func_807132DC();
Gfx *func_807135B4(Gfx *);

Gfx *func_807138A4(Gfx *arg0) {
    return func_807135B4(func_807132DC(arg0));
}
void viewportSetFromRect(void *, s32, s32, s32, s32);
Gfx *func_806FF144(void *);

Gfx *func_807138CC(Gfx *arg0) {
    void *sp3C;
    f32 temp_fv0;
    Gfx *g;

    sp3C = (void *)heapAlloc(0x10);
    heapFreeDeferred(sp3C);
    viewportSetFromRect(sp3C, 0xA, 0xA, 0x135, 0xE5);
    arg0 = func_807135B4(func_807132DC(arg0));
    arg0 = func_8071338C(arg0);
    if ((u32)++D_80755320 < 0xD3U) {
        temp_fv0 = (f32) (0xD2U - D_80755320) * 0.03333333507f;
        temp_fv0 = (temp_fv0 < 0.0f) ? 0.0f : ((temp_fv0 > 1.0f) ? 1.0f : temp_fv0);
        arg0 = func_80713764(func_80713438(arg0, (u32) (255.0f * temp_fv0)), (u32) (255.0f * temp_fv0), 0);
    }
    g = arg0++; g->words.w0 = 0xDC080008; // LAYOUT: same-line pointer-copy and first store steers as1 move/ori order
    g->words.w1 = (u32)sp3C;
    return func_806FF144(arg0);
}


Gfx *func_80713AA8(Gfx *arg0) {
    R117D_WRITE_GFX(arg0++, 0xE7000000, 0);
    R117D_WRITE_GFX(arg0++, 0xDE000000, &D_1000118);
    R117D_WRITE_GFX(arg0++, 0xE3000A01, 0);
    R117D_WRITE_GFX(arg0++, 0xE200001C, 0x504240);
    R117D_WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    R117D_WRITE_GFX(arg0++, 0xDA380007, &D_20000C0);
    return arg0;
}

extern u8 D_80755378[];

Gfx *func_80713B40(Gfx *arg0) {
    s16 temp_t0;
    s16 pad0;
    s16 var_v1;
    temp_t0 = gMenuStateTimer - 0x8C;
    if (temp_t0 >= 0) {
        if (temp_t0 < 0x96) {
            var_v1 = temp_t0 - 0x5A;
            if (var_v1 < 0) {
                var_v1 = 0xFF;
            } else {
                var_v1 = 0x3C - var_v1;
                var_v1 = var_v1 * 5;
            }
            if (temp_t0 < 0x3C) {
                var_v1 = temp_t0 * 5;
            }
            if (var_v1 >= 0x100) {
                var_v1 = 0xFF;
            }
            arg0 = func_80713AA8(arg0);
            gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, var_v1);
            arg0 = hudDrawScaledText(arg0, 0x280, (s16)(s32)(480.0 - ((f64)(f32)((f64)(0x96 - temp_t0) / 40.0) * 32.0)), (f32)((f64)(0x96 - temp_t0) / 40.0), D_80755378);
        }
    }
    return arg0;
}



extern u64 D_807445B0;
void sfxAllocateChannel(s32, f32);
s16 sfxPlayOnFreeSlot(s16, s32, f32, f32, u8, u8);

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

extern s32 D_80755348;
Gfx *renderTimerMinutesSecondsHUD(Gfx *, f32, f32, s32);

Gfx *hudDrawCountdownTimer(Gfx *dl) {
    s32 pad[8];
    f32 timerX;
    Gfx *dlCur;

    if ((menuGetTimerFlag() != 0) && !(gGlobalPauseFlags & 3)) {
        timerX = (f32) gScreenWidth * 0.5f;
        dlCur = func_807132DC(dl);
        R117D_WRITE_GFX(dlCur++, 0xFC119623, 0xFF2FFFFF);
        R117D_WRITE_GFX(dlCur++, 0xFA000000, 0xFFFFFFFF);
        dl = renderTimerMinutesSecondsHUD(dlCur, timerX, 214.0f, D_80755348);
    }
    return dl;
}

s32 mathIdentityS32B(s32 arg0) {
    return arg0;
}

extern s16 D_807FC828[];
void hudPauseMenuRefreshTotals();

void func_80713EB0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp18;
    s32 sum;
    s32 i;

    if (arg0 >= 0) {
        if (gMenuCurrentMode == 0xE) {
            if (arg2 == 1) {
                if (flagGet(0x2A, 1) == 0) {
                    arg0 = -1;
                }
            }
            if (arg2 == 2) {
                if (flagGet(0x2B, 1) == 0) {
                    arg0 = -1;
                }
            }
        } else {
            hudPauseMenuRefreshTotals();
            sum = 0; for (i = 0; i < 7; i++) { sum += D_807FC828[i]; } if (arg2 == 1) { // LAYOUT: one source line lets as1 reorder the unrolled loads
                if (sum < 0x118) {
                    arg0 = -1;
                } else {
                    flagSet(0x2A, 1, 1);
                }
            }
            if (arg2 == 2) {
                if (sum < 0x119) {
                    arg0 = -1;
                } else {
                    flagSet(0x2B, 1, 1);
                }
            }
        }
        if (arg0 >= 0) {
            menuTransitionToMap(arg0, arg1);
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

Gfx *func_807138CC(Gfx *);
Gfx *func_80713B40(Gfx *);
extern s8 D_807552E0;
u16 camStartPath(void *, s16, u8);

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
    s32 var_v0;

    var_v0 = gMenuTargetMode == 3;
    if (var_v0 == 0) {
        var_v0 = gMenuTargetMode == 4;
        if (var_v0 == 0) {
            var_v0 = gMenuCurrentMode == 3;
            if (var_v0 == 0) {
                return gMenuCurrentMode == 4;
            }
        }
    }
}

s32 menuIsTransitionType6(void) {
    s32 var_v0;

    var_v0 = gMenuCurrentMode == 6;
    if (var_v0 == 0) {
        return gMenuTargetMode == 6;
    }
}

s32 menuIsTransitionType8(void) {
    s32 var_v0;

    var_v0 = gMenuCurrentMode == 8;
    if (var_v0 == 0) {
        return gMenuTargetMode == 8;
    }
}

s32 menuIsTransitionType7Or9(void) {
    s32 var_v0;

    var_v0 = gMenuCurrentMode == 7;
    if (var_v0 == 0) {
        var_v0 = gMenuTargetMode == 7;
        if (var_v0 == 0) {
            var_v0 = gMenuCurrentMode == 9;
            if (var_v0 == 0) {
                return gMenuTargetMode == 9;
            }
        }
    }
}

s32 menuIsTransitionTypeD(void) {
    s32 var_v0;

    var_v0 = gMenuCurrentMode == 0xD;
    if (var_v0 == 0) {
        return gMenuTargetMode == 0xD;
    }
}

s32 menuIsTransitionTypeC(void) {
    s32 var_v0;

    var_v0 = gMenuCurrentMode == 0xC;
    if (var_v0 == 0) {
        return gMenuTargetMode == 0xC;
    }
}

s32 menuIsTransitionType5(void) {
    return gMenuCurrentMode == 5;
}

s32 menuIsTransitionTypeAOrE(void) {
    s32 var_v0;

    var_v0 = gMenuCurrentMode == 0xA;
    if (var_v0 == 0) {
        var_v0 = gMenuCurrentMode == 0xE;
        if (var_v0 == 0) {
            var_v0 = gMenuTargetMode == 0xA;
            if (var_v0 == 0) {
                return gMenuTargetMode == 0xE;
            }
        }
    }
}

extern s8 D_8074452C;
extern u8 D_807467C8;
void playerResetSpawnGlobals(void);
void flagsClearAllBank2(void);
void eepromLoadPlayerData(u8, s32);
s32 eepromGetField(s32, u8, u8, u8);
void mapRequestTransitionFast(s32, s32);

void func_807144B8(u8 arg0) {
    s32 var_a0;
    s32 var_a1;

    D_807445B8 = osGetTime();
    D_80755350 = 0;
    playerResetSpawnGlobals();
    flagsClearAllBank2();
    eepromLoadPlayerData(arg0, 1);
    gPlayerCharacterId = 0;
    if ((eepromGetField(0xD, 0, 0, D_807467C8) != 0) || (D_8074452C != 0)) {
        if (flagGet(0x186, 0) != 0) {
            var_a0 = 0x22;
            var_a1 = 0;
        } else {
            var_a0 = 0xB0;
            var_a1 = 1;
        }
    } else {
        D_80755338 = 1;
        D_8075533C = 0;
        var_a0 = 0x99;
        var_a1 = 0;
    }
    mapRequestTransitionFast(var_a0, var_a1);
    gMenuTargetMode = 6;
}



void func_8071458C(void) {
    s32 var_a0;

    playerResetSpawnGlobals();
    gSplitScreenMode = 0;
    if (R117c_STATE->unk0 == 0) {
        gSplitScreenMode = 1;
        var_a0 = 0x6B;
    } else {
        var_a0 = D_80755384[R117c_STATE->unk20];
    }
    menuTransitionWithState(var_a0, 0, 6);
}

void menuSetFlag5324(void) {
    gMenuDemoActive = 1;
}


s32 func_80714608(s32 arg0) {
    s32 var_v0;

    var_v0 = (s32) gPlayerCount >= 2;
    if (var_v0 != 0) {
        return arg0 == D_807552E4;
    }
}

void menuReturnToTitleWithMode3(void) {
    menuReturnToTitle();
    D_807552EC = 3;
}

void menuNoop714660(void) {
}
