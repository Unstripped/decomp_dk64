#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/103AB0.h"
#include "proto/global/104F0.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/1295B0.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B40.h"
#include "proto/global/201B0.h"
#include "proto/global/2DE90.h"
#include "proto/global/3C10.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/ACDC0.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"

typedef struct HudTextEntry {
    /* 0x00 */ f32 flyX;
    /* 0x04 */ f32 flyY;
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
    /* 0x0C */ s16 offsetX;
    /* 0x0E */ s16 offsetY;
    /* 0x10 */ s8 style;
    /* 0x11 */ u8 text[7];
} HudTextEntry; // size = 0x18

typedef struct HudTextList {
    /* 0x00 */ HudTextEntry entries[10];
} HudTextList; // size = 0xF0

typedef struct HudEntry {
    /* 0x00 */ f32 fade;
    /* 0x04 */ f32 carouselProgress;
    /* 0x08 */ s16 worldIndex[2];
    /* 0x0C */ s16 slideY[2];
    /* 0x10 */ s16 carouselAngle;
    /* 0x12 */ s8 page;
    /* 0x13 */ s8 nextPage;
    /* 0x14 */ s8 kong;
    /* 0x15 */ s8 buffer;
    /* 0x16 */ s8 fadeDir;
    /* 0x17 */ s8 menuRow;
    /* 0x18 */ u8 saved;
} HudEntry;


extern Gfx D_1000118;
extern Mtx D_2000180;
extern Mtx D_20000C0;

extern HudTextList *sPauseTextLists[2];
extern s8 sPauseTextCounts[2];
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;
extern u8 **sPauseMenuStrings;
extern u8 **sPauseLevelNames;
extern s8 sPauseIconList;
extern u8 D_807FC810;
extern f32 sPauseLevelLabelHalfWidth;
extern s8 sPauseBumpStep;
extern s8 sPauseLastLevelSlot;
extern s16 D_807FC82A;
extern s16 D_807FC82C;
extern s16 D_807FC82E;
extern s16 D_807FC830;
extern s16 D_807FC832;
extern s16 D_807FC834;
extern s16 D_807FC836;
extern s16 D_807FC838;
extern s16 gWorldClearedFlags[];
extern s16 D_80744720[];
extern s16 D_807505B2[];
extern s8 gPauseMenuMode;
extern s8 sPauseKongUnlocked[5];
extern u8 D_80750531[];
extern s32 gCurrentMap;
extern s8 sPauseStickHeld;
extern s8 gPausingPlayer;
extern PlayerStruct *gPlayerSlots;
extern s8 gMpWinnerIndex;

f32 sqrtf(f32);

extern const char sLevelNameJungle[], sLevelNameTemple[], sLevelNameToy[], sLevelNameWreck[], sLevelNameForest[], sLevelNameCrystal[], sLevelNameSpooky[];
extern const char sLevelNameWorld[], sLevelNameHideout[], sLevelNameBonus[], sLevelNameMulti[], sLevelNameStory[], sLevelNameTest[], sLevelNameShared[];
extern s32 D_807214A0, D_807214B8, D_807214D0, D_807214E8, D_80721500;

const char *sLevelNames[14] = {
    sLevelNameJungle, sLevelNameTemple, sLevelNameToy, sLevelNameWreck, sLevelNameForest, sLevelNameCrystal, sLevelNameSpooky,
    sLevelNameWorld, sLevelNameHideout, sLevelNameBonus, sLevelNameMulti, sLevelNameStory, sLevelNameTest, sLevelNameShared,
};
void *gKongIconSprites[5] = { &D_807214A0, &D_807214B8, &D_807214D0, &D_807214E8, &D_80721500 };
s8 sPauseBumpStep = 0;
s8 sPauseKongUnlocked[5] = { 1, 1, 0, 0, 0 };
// counts 0..13 while the kong carousel page renders (never read in C; its period is the length of sPausePulseTable)
s8 sPauseCarouselFrame = 0;
u8 sPausePulseTable[14] = { 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1 };
// rgb(a) tint of the locked kong icons on the carousel, per kong
u8 sPauseKongColors[5][4] = {
    { 0xFF, 0x00, 0x00, 0xFF }, { 0xFF, 0x00, 0x00, 0xFF }, { 0x16, 0x99, 0xFF, 0xFF },
    { 0xB0, 0x45, 0xFF, 0xFF }, { 0x41, 0xFF, 0x25, 0xFF },
};
// level index shown at each pause page slot: Isles (7), the seven worlds (0..6), Helm (8)
s8 sPauseLevelOrder[9] = { 7, 0, 1, 2, 3, 4, 5, 6, 8 };
// totals page: the maximum shown beside each gPauseCollectibleCounts[] entry
s16 sPauseCollectibleTotals[10] = { 0xC8, 0xA, 8, 0x28, 1, 0x14, 1, 0x28, 1, 0 };
s8 D_80750580 = 0;
f32 sPauseBumpFade[8] = { 0.0f, -0.02f, 0.04f, -0.04f, 0.06f, 0.06f, -0.06f, -0.06f };
// Two per-kong tables in one object (a separate s16[5] would start 4-aligned at 0xD0, not 0xCE); 478F0, FCCD0,
// menu/3E10 and hudPauseMenuRefreshTotals read unlockFlag through the interior labels D_807505AE / D_807505B2.
typedef struct PauseKongTables {
    /* 0x00 */ s16 carouselAngle[5]; // carousel angle of each kong's icon (steps of 0x333 around the 0x1000 turn)
    /* 0x0A */ s16 unlockFlag[5]; // flag set once each kong is freed (sPauseKongUnlocked); DK's 0 is never read
} PauseKongTables; // size = 0x14
PauseKongTables sPauseKongTables = { { 0, 0x333, 0x666, 0x999, 0xCCC }, { 0, 6, 0x46, 0x42, 0x75 } };
// battle crown flag per level index (0..8); [9] is the Isles' second crown
s16 sPauseCrownFlags[10] = { 0x261, 0x262, 0x263, 0x264, 0x265, 0x268, 0x269, 0x266, 0x26A, 0x267 };
s8 gPauseMenuMode = 0;
s8 sPauseLastLevelSlot = 0;

s32 hudFindLevelSlot(s8 levelId) {
    s32 i;

    for (i = 0; i < 9; i++) {
        if (levelId == sPauseLevelOrder[i]) {
            return i;
        }
    }
    return 0;
}


extern OSContPad *gCurrentContPad;
extern u8 gSaveIconTimer;
extern s32 gMapPauseCount;
extern u8 gCurrentWorldId;
extern f32 sPauseBaseCamY;
extern s8 D_80750580;
extern f32 sPauseBumpFade[];
extern s8 sPauseCarouselKong;
extern s16 sPauseCarouselTurnDelta;
extern f32 sPauseCarouselTimer;
extern s8 sPauseCarouselIndex;
extern s8 sPauseCarouselTarget;
extern s16 sPauseCarouselSpacing;
extern s8 sPauseCarouselCount;
extern s8 sPauseExitRequested;


void hudPauseMenuUpdate(void) {
    static s8 sPauseSaveCooldown = 0;
    HudEntry *hud;
    s32 i;
    s32 diff;
    s32 flag;
    s32 moved;
    s32 buttons;
    s8 x;
    s8 stickY;
    s32 hubWorld;
    s32 step;
    s32 sel;

    hud = gCurrentActor->customState;
    sel = gCurrentMap;
    switch (sel) {
        case 0x6:
        case 0xE:
        case 0x1B:
        case 0x27:
        case 0x37:
        case 0x52:
        case 0x6A:
        case 0xB9:
            gPauseMenuMode = 1;
            break;
        default:
            if (mapGetWorldIndex(gCurrentMap) == 9 || (gGlobalOverlayFlags & 0x10000000)) {
                gPauseMenuMode = 2;
            } else {
                gPauseMenuMode = 0;
            }
            break;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        sPauseMenuStrings = heapAlloc(0x6C);
        for (i = 0; i < 0x1B; i++) {
            sPauseMenuStrings[i] = textTableGetString(0x24, i, 0);
        }
        sPauseLevelNames = heapAlloc(0x24);
        for (i = 0; i < 9; i++) {
            sPauseLevelNames[i] = textTableGetString(0x23, i, 0);
        }
        gMapPauseCount++;
        sPauseBaseCamY = gPlayerSlots->camY;
        sPauseSaveCooldown = 0;
        sPauseExitRequested = 0;
        D_80750580 = 1;
        sPauseLastLevelSlot = 7;
        while (sPauseLastLevelSlot >= 0 && flagGet(sPauseLastLevelSlot + 0x1C5, 0) == 0) {
            sPauseLastLevelSlot--;
        }
        sPauseLastLevelSlot++;
        hud->page = 0;
        hud->menuRow = 0;
        hud->fadeDir = -1;
        hud->fade = 1.0f;
        hud->carouselProgress = 0.0f;
        hud->kong = playerGetResolvedKongId(0);
        hubWorld = mapGetHubWorldIndex(gCurrentWorldId, 1);
        hud->worldIndex[0] = hudFindLevelSlot(hubWorld);
        if (sPauseLastLevelSlot < hud->worldIndex[0]) {
            hud->worldIndex[0] = 0;
        }
        hud->worldIndex[1] = hud->worldIndex[0];
        hud->slideY[0] = 0;
        hud->slideY[1] = 0xF0;
        hud->buffer = 0;
        hud->carouselAngle = sPauseKongTables.carouselAngle[hud->kong];
        sPauseCarouselKong = hud->kong;
        sPauseCarouselTurnDelta = 0;
        sPauseCarouselTimer = 0.0f;
        sPauseLevelLabelHalfWidth = 0.0f;
        sPauseCarouselTarget = sPauseCarouselIndex = 0;
        sPauseTextLists[0] = heapAlloc(sizeof(HudTextList) * 2);
        sPauseTextLists[1] = sPauseTextLists[0] + 1;
        sPauseTextCounts[0] = 0;
        sPauseTextCounts[1] = 0;
        sPauseBumpStep = 0;
        sPauseStickHeld = 1;
        hudPauseMenuRefreshTotals();
        hudPauseMenuBuildPage(hud, 0);
        gGlobalPauseFlags &= 0xFFFEFFCF;
        screenWipeStart(7);
    }
    if (hud->fade == 0.0f && sPauseExitRequested == 0) {
        moved = hud->worldIndex[hud->buffer] != hud->worldIndex[1 - hud->buffer];
        buttons = *gPlayerSlots->heldButtonsPtr;
        if (moved == 0 && hud->carouselProgress == 0.0f && sPauseCarouselIndex == sPauseCarouselTarget) {
            if (buttons & 0x5000) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                if (hud->page == 0 && hud->menuRow == 3) {
                    hud->menuRow = 2;
                } else {
                    hud->fadeDir = 1;
                    hud->nextPage = -1;
                }
                buttons = 0;
            }
            if (gPauseCollectibleCounts[0] > 0) {
                flag = 0;
                if (buttons & 0x10) {
                    hud->nextPage = hud->page + 1;
                    if (hud->nextPage >= 4) {
                        hud->nextPage = 0;
                    }
                    flag = 1;
                } else if (buttons & 0x2000) {
                    hud->nextPage--;
                    if (hud->nextPage < 0) {
                        hud->nextPage = 3;
                    }
                    flag = 1;
                }
                if (flag != 0) {
                    hud->fadeDir = 1;
                    sPauseBumpStep = 0;
                    buttons = 0;
                    sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
            }
        }
        sel = hud->page; // FAKE: page selector reuses the map selector sel (a1, lb a1,18(s0) at 0x61c); a dedicated page local is coloured v0 (Q1200) and a separate s32 one grows frame 0x58->0x60
        switch (sel) {
            case 0:
                if (hud->menuRow != 3) {
                    stickY = gCurrentContPad->stick_y;
                    if (stickY < -0x32) {
                        if (sPauseStickHeld == 0) {
                            hud->menuRow++;
                            buttons = 0;
                            if (hud->menuRow >= 3) {
                                hud->menuRow = 0;
                            }
                            sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
                        }
                        sPauseStickHeld = 1;
                    } else if (stickY >= 0x33) {
                        if (sPauseStickHeld == 0) {
                            hud->menuRow--;
                            buttons = 0;
                            if (hud->menuRow < 0) {
                                hud->menuRow = 2;
                            }
                            sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
                        }
                        sPauseStickHeld = 1;
                    } else {
                        sPauseStickHeld = 0;
                    }
                    if (buttons & 0x8000) {
                        if (hud->menuRow == 2) {
                            hud->menuRow = 3;
                        } else if (hud->menuRow == 1) {
                            if (gPauseMenuMode != 0) {
                                mapRequestTransition(gCurrentMap, 0);
                            } else if (hud->saved == 0) {
                                eepromSavePlayerData();
                                hud->saved = 1;
                            } else if (sPauseSaveCooldown == 0) {
                                sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                sPauseSaveCooldown = 0x2D;
                            }
                        } else {
                            hud->fadeDir = 1;
                            hud->nextPage = -1;
                        }
                    }
                } else if (buttons & 0x8000) {
                    hubWorld = mapGetHubWorldIndex(gCurrentWorldId, 1);
                    sel = hubWorld == 8; // FAKE: credits flag reuses the selector sel (a1 at 0x814/0x82c); a dedicated credits local swaps a1/a2 with hubWorld and a separate s32 one grows frame 0x58->0x60
                    if (sel) {
                        sel = menuGetTimerFlag() != 0;
                    }
                    sPauseExitRequested = 1;
                    if (gPauseMenuMode == 0 && hubWorld != 7 && hubWorld != 0xD && hubWorld != 9 && sel == 0) {
                        if (hubWorld == 0xA) {
                            menuReturnToTitle();
                        } else if (mapIsLobby(gCurrentMap) == 0) {
                            if ((gGlobalOverlayFlags & 1) && hubWorld == 8) {
                                flagSet(0x5C, 1, 2);
                                mapRequestTransition(0x22, 0xC);
                            } else if ((gGlobalOverlayFlags & 1) && gCurrentMap != 0x3C) {
                                mapRequestTransition(0x2A, 2);
                            } else {
                                mapTransitionToWorldHub(hubWorld);
                            }
                        }
                    } else if (gPauseMenuMode != 0) {
                        if (gPauseMenuMode == 2) {
                            mapTransitionToPreviousOrExit();
                        } else {
                            mapCheckAutoTransition();
                        }
                    } else if (hubWorld == 7 || sel != 0) {
                        menuResetAndTransitionToCredits();
                    }
                }
                break;
            case 1:
                hud->carouselAngle = sPauseKongTables.carouselAngle[sPauseCarouselKong] + (s16)(sPauseCarouselTimer * 0.5f * sPauseCarouselTurnDelta);
                hud->carouselAngle &= 0xFFF;
                if (sPauseCarouselTimer == 0.0f) {
                    sPauseCarouselTurnDelta = 0;
                    if (moved == 0) {
                        x = gCurrentContPad->stick_x;
                        if (x < -0x28) {
                            do {
                                sPauseCarouselTurnDelta -= 0x333;
                                sPauseCarouselKong += 1;
                                if (sPauseCarouselKong >= 5) {
                                    sPauseCarouselKong = 0;
                                }
                            } while (sPauseKongUnlocked[sPauseCarouselKong] == 0);
                        } else if (x >= 0x29) {
                            do {
                                sPauseCarouselTurnDelta += 0x333;
                                sPauseCarouselKong -= 1;
                                if (sPauseCarouselKong < 0) {
                                    sPauseCarouselKong = 4;
                                }
                            } while (sPauseKongUnlocked[sPauseCarouselKong] == 0);
                        }
                        if (sPauseCarouselKong != hud->kong) {
                            sPauseCarouselTimer = 2.0f;
                            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                        }
                    }
                } else {
                    sPauseCarouselTimer -= 0.125f;
                    if (sPauseCarouselTimer < 0.0f) {
                        sPauseCarouselTimer = 0.0f;
                    }
                    hud->carouselProgress = sPauseCarouselTimer - 1.0f;
                    if (hud->carouselProgress < 0.0f) {
                        hud->carouselProgress = -hud->carouselProgress;
                    }
                    hud->carouselProgress = 1.0f - hud->carouselProgress;
                    hud->carouselProgress *= 1.3f;
                    if (hud->carouselProgress > 1.2f && sPauseCarouselKong != hud->kong) {
                        hud->kong = sPauseCarouselKong;
                        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
                        hudPauseMenuBuildPage(hud, 1);
                    }
                    if (sPauseCarouselKong == hud->kong && hud->carouselProgress > 1.0f) {
                        hud->carouselProgress = 1.0f;
                    }
                }
                hudPauseMenuSlidePage(hud, moved, buttons);
                break;
            case 2:
                hud->carouselAngle += 0x28;
                hud->carouselAngle &= 0xFFF;
                hudPauseMenuSlidePage(hud, moved, buttons);
                break;
            case 3:
                diff = step = -mathAngleSignedDistance(sPauseCarouselTarget * sPauseCarouselSpacing, hud->carouselAngle);
                flag = sPauseCarouselSpacing / 10; // FAKE: step limit reuses flag (a0, move a0,t5 at 0xc94); a dedicated limit local moves the flag bools to v1, and with sel in the freed word it grows frame 0x58->0x60
                if (diff > 0) {
                    if (flag < diff) {
                        step = flag;
                    }
                    hud->carouselAngle += step;
                } else if (diff < 0) {
                    if (diff < -flag) {
                        step = -flag;
                    }
                    hud->carouselAngle += step;
                } else {
                    flag = 0;
                    x = gCurrentContPad->stick_x;
                    if (x < -0x28) {
                        sPauseCarouselTarget += 1;
                        if (sPauseCarouselTarget >= sPauseCarouselCount) {
                            sPauseCarouselTarget = 0;
                        }
                        flag = 1;
                    } else if (x >= 0x29) {
                        sPauseCarouselTarget -= 1;
                        if (sPauseCarouselTarget < 0) {
                            sPauseCarouselTarget = sPauseCarouselCount - 1;
                        }
                        flag = 1;
                    }
                    if (flag != 0 && sPauseCarouselTarget != sPauseCarouselIndex) {
                        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    }
                }
                hud->carouselAngle &= 0xFFF;
                flag = sPauseCarouselSpacing >> 1; // FAKE: half span reuses flag (a0, move a0,t9 at 0xdc0); a dedicated half local is coloured v0, and with sel in the freed word it grows frame 0x58->0x60
                if (diff < 0) {
                    diff = -diff;
                }
                diff -= flag;
                if (diff < 0) {
                    diff = -diff;
                }
                if (flag < diff) {
                    diff = flag;
                }
                diff = flag - diff;
                hud->carouselProgress = diff / (f32)((f32)flag * 0.9);
                if (hud->carouselProgress > 1.0f && sPauseCarouselTarget != sPauseCarouselIndex) {
                    sPauseCarouselIndex = sPauseCarouselTarget;
                }
                break;
        }
    }
    if (hud->fadeDir == 1) {
        hud->fade += 0.13f;
        if (hud->fade > 1.3f) {
            hud->fade = 1.0f;
            if (hud->nextPage == -1) {
                hudFreeBuffers();
            } else {
                hud->page = hud->nextPage;
                hud->fadeDir = -1;
                hudPauseMenuBuildPage(hud, 0);
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
            }
        }
    } else if (hud->fade > 0.0f && sPauseBumpStep == 0) {
        hud->fade -= 0.2f;
        if (hud->fade < 0.0f) {
            hud->fade = 0.0f;
            sPauseBumpStep = 3;
            sfxPlayOnFreeSlot(0x3C, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
    }
    sPauseSaveCooldown--;
    if (sPauseSaveCooldown < 0) {
        sPauseSaveCooldown = 0;
    }
    if (gSaveIconTimer == 0x1C) {
        sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
    if (sPauseBumpStep != 0) {
        sPauseBumpStep -= 1;
        hud->fade = sPauseBumpFade[sPauseBumpStep];
        gPlayerSlots->camY = sPauseBaseCamY + hud->fade * 100.0;
    }
    renderCallbacksRegister(hudDrawDimOverlay, gCurrentActor, 1);
    renderCallbacksRegister(hudPauseMenuRender, gCurrentActor, 5);
}


void hudFreeBuffers(void) {
    s32 i;
    PlayerState *ps;

    ps = gPrimaryPlayerActor->customState;
    gGlobalPauseFlags |= 0x40;
    if (!(ps->stateFlags & 0x20000000)) {
        gGlobalPauseFlags |= 0x10030;
    }
    heapFree(sPauseTextLists[0]);
    sPauseTextLists[0] = NULL;
    sPauseTextLists[1] = NULL;
    sPauseTextCounts[0] = 0;
    sPauseTextCounts[1] = 0;
    for (i = 0; i < 0x1B; i++) {
        heapFreeDeferred(sPauseMenuStrings[i]);
    }
    heapFreeDeferred(sPauseMenuStrings);
    for (i = 0; i < 9; i++) {
        heapFreeDeferred(sPauseLevelNames[i]);
    }
    heapFreeDeferred(sPauseLevelNames);
}

Gfx *hudSetupTextState(Gfx *dl) {
    gSPDisplayList(dl++, &D_1000118);
    gSPMatrix(dl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(dl++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPSetCombineMode(dl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    return dl;
}

const char sLevelNameJungle[7] = "JUNGLE";
const char sLevelNameTemple[7] = "TEMPLE";
const char sLevelNameToy[4] = "TOY";
const char sLevelNameWreck[6] = "WRECK";
const char sLevelNameForest[7] = "FOREST";
const char sLevelNameCrystal[8] = "CRYSTAL";
const char sLevelNameSpooky[7] = "SPOOKY";
const char sLevelNameWorld[6] = "WORLD";
const char sLevelNameHideout[8] = "HIDEOUT";
const char sLevelNameBonus[6] = "BONUS";
const char sLevelNameMulti[6] = "MULTI";
const char sLevelNameStory[6] = "STORY";
const char sLevelNameTest[5] = "TEST";
const char sLevelNameShared[7] = "SHARED";


extern u8 gCurrentWorldId;
extern s8 sPauseCollectibleSlots[];
extern f32 sPauseCarouselSlotX[];
extern f32 sPauseCarouselSlotY[];
extern f32 sPauseCarouselSlotScale[];

Gfx *hudPauseMenuRender(Gfx *dl, Actor *actor) {
    u8 buf[0x40];
    HudEntry *hud;
    s16 j;
    s16 i;
    s16 y;
    s32 off;
    s32 slotBase;
    HudTextList *it;
    PlayerInventory *tab;
    Gfx *ret;
    Gfx *list;
    s32 hubWorld;
    s16 ang;
    s16 alpha;
    s16 y0;
    s8 pips;
    u8 centerX;
    f32 fa;
    f32 fb;
    f32 fc;
    f32 fd;
    f32 fadeInput0 = 0.0f; // FAKE: dead initializer; first appearance orders fadeInput0 ahead of fadeInput4 for uopt colouring (Q0584)
    f32 fadeInput4;
    s32 cnt;

    hud = actor->customState;
    tab = gPlayerInventoryTable;
    hubWorld = mapGetHubWorldIndex(gCurrentWorldId, 1);
    list = heapAlloc(0x1F40);
    heapFreeDeferred(list);
    gSPDisplayList(dl++, list);
    ret = dl;
    dl = hudSetupTextState(list);
    for (i = 0; i < 2; i++) {
        it = sPauseTextLists[i];
        if (it != NULL) {
            for (j = 0; j < sPauseTextCounts[i]; j++) {
                fa = hud->fade;
                if ((it->entries + j)->style == 2) {
                    fa += hud->carouselProgress;
                }
                off = (it->entries + j)->x; // FAKE: (it->entries + j)->f member-access spelling (all 8 reads in this loop) keeps mul.s $f8,$f0,$f6 at 0x131c and lh t6,12(v0) at 0x132c; it->entries[j] flips the mul.s operands and rotates the loop-1 ring (272) (Q0816)
                y = (it->entries + j)->y;
                off = (u16)(off * 4) + (s16)(s64)(s32)(fa * (it->entries + j)->flyX); // FAKE: narrow through a 64-bit pair to preserve the ugen scratch-register order.
                y *= 4;
                y += (u16)(s32)(fa * (it->entries + j)->flyY); // FAKE: no-op (u16) (y is s16) keeps mfc1 t4 / addu t9,t7,t4 at 0x1350/0x1358 in the ugen scratch ring
                off = (s16)((u32)off + (it->entries + j)->offsetX * 4); // FAKE: no-op (u32)off orders addu t8,s0,t7 at 0x1364; the (s16) store gives its move s0,t8 (Q0374)
                y += (it->entries + j)->offsetY * 4;
                y += hud->slideY[i] * 4;
                dl = textDrawStringVtx(dl, 1, off, y, (it->entries + j)->text, 1);
            }
        }
    }

    if (list == NULL) {} // FAKE: keeps list in memory
    switch (hud->page) {
        case 0:
            centerX = tab->melons * 0x34 - 0x34;
            pips = tab->health;
            y0 = 0xA0;
            y0 -= (s16)(y0 * 2 * hud->fade);
            for (j = 0; j < tab->melons; j++) {
                s32 off;
                f32 fa;
                f32 fc;
                f32 fd;
                f32 fe;
                f32 fh;
                s16 y;
                fb = centerX;
                off = (j << 10) + gFrameCounter * 200;
                ang = off;
                fa = mathSinF(ang) * 0.3f + 3.0f;
                fc = mathSinF(off + 0x800) * 0.3f + 3.0f;
                fd = mathSinF((off >> 1) + 0x200) * 10.0f;
                fe = mathSinF(ang);
                fa *= 0.75f;
                fd *= 0.75f;
                fc *= 0.75f;
                fe = (fe * 0.5f + 0.5f) * 30.0f * 0.75f;
                gDPPipeSync(dl++);
                gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0x50);
                y = (j * 0x69 + 0x280) + fd - fb;
                fh = -fc;
                dl = renderRotatedSprite(dl, 0x5D, 0, 2, 0x30, 0x2A, y, y0 + (s16)fe, fa, fh, 0, 0.0f);
                gDPPipeSync(dl++);
                gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                if (pips > 0) {
                    s32 m;
                    if (pips - 1 < 3) {
                        m = pips - 1;
                    } else {
                        m = 3;
                    }
                    dl = renderRotatedSprite(dl, m + 0x5A, 0, 2, 0x30, 0x2A, y, y0 + fe, fa, fh, 0, 0.0f);
                }
                if (pips - 4 < 0) {
                    pips = 0;
                } else {
                    pips -= 4;
                }
            }
            gDPPipeSync(dl++);
            y = 0x198;
            alpha = (1.0f - hud->fade) * 255.0f;
            if (alpha < 0) {
                alpha = 0;
            }
            if (alpha >= 0x100) {
                alpha = 0xFF;
            }
            if (hud->menuRow != 3) {
                for (j = 0; j < 3; j++) {
                    if (j == hud->menuRow) {
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
                    } else {
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha >> 1);
                    }
                    if (j == 2 && (hubWorld == 7 || (hubWorld == 8 && menuGetTimerFlag() != 0 && gPauseMenuMode == 0))) {
                        j++;
                    }
                    i = j; // ORIG: i's own home 0x158(sp) holds the string index (sh at 0x1858/0x186c/0x1894); a dedicated local gives 228
                    if (j == 1 && gPauseMenuMode != 0) {
                        i = 4;
                    }
                    if (i == 2 && gPauseMenuMode != 0) {
                        i = 5;
                    }
                    dl = hudDrawScaledText(dl, 0x280, y, 0.7f, sPauseMenuStrings[i]);
                    y += 0x44;
                }
            } else {
                gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
                dl = hudDrawScaledText(dl, 0x280, 0x198, 0.7f, sPauseMenuStrings[7]);
                _sprintf(buf, "q %s", sPauseMenuStrings[16]);
                dl = hudDrawScaledText(dl, 0x280, 0x1E8, 1.0, buf);
                _sprintf(buf, "b %s", sPauseMenuStrings[17]);
                dl = hudDrawScaledText(dl, 0x280, 0x238, 1.0, buf);
            }
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                s32 angv;
                s32 slide;
                slide = hud->slideY[i] * 4;
                angv = -hud->carouselAngle;
                fa = 1.0f - hud->fade;
                if (slide < 0x3B6 && slide >= -0x3B5) {
                    if (fa > 0.05f) {
                        f32 fe;
                        f32 ff;
                        s16 sa;
                        s16 yy;
                        slotBase = i * 5;
                        fb = 180.0f * fa;
                        fa *= 3.0f;
                        fc = 32.0f * fa;
                        fc = 480.0f + fc;
                        fd = 6.0f * fa;
                        fe = 30.0f * fa;
                        ff = fa * 1.33;
                        for (j = 0; j < 5; j++) {
                            sa = angv;
                            yy = mathSinF(sa) * fb;
                            yy += 0x280;
                            y0 = mathCosF(sa) * fb;
                            yy += 0x20;
                            off = j + slotBase;
                            sPauseCarouselSlotX[off] = yy - fd;
                            sPauseCarouselSlotY[off] = (s16)((s16)(fc - y0) + slide) - fe;
                            sPauseCarouselSlotScale[off] = ff;
                            if (sPauseKongUnlocked[j] != 0) {
                                sPauseCarouselSlotScale[off] *= 0.75;
                            }
                            angv += 0x333;
                        }
                        gDPPipeSync(dl++);
                    }
                    dl = hudDrawItemLabel(dl, hud, i);
                }
                if (hud->worldIndex[i] != 8) {
                    fd = (hud->carouselProgress < hud->fade) ? hud->fade : hud->carouselProgress;
                    fc = 780.0f;
                    if (slide == 0) {
                        fc += fd * 400.0;
                    }
                    j = tab->kong[hud->kong].goldenBananas[sPauseLevelOrder[hud->worldIndex[i]]]; // FAKE: reuses the loop index j for the golden-banana count; a dedicated s16 local or the read inlined into hudDrawCountPair fails fdiff
                    dl = hudDrawCountPair(0x2A8, slide + fc, j, 5, dl, 0, 0.8f);
                }
            }
            sPauseCarouselFrame++;
            if (sPauseCarouselFrame >= 0xE) {
                sPauseCarouselFrame = 0;
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                off = hud->slideY[i] * 4;
                if (off < 0x3B6 && off >= -0x3B5) {
                    dl = hudDrawItemLabel(dl, hud, i);
                }
                cnt = 0;
                for (j = 0; j < 5; j++) {
                    cnt += tab->kong[j].goldenBananas[sPauseLevelOrder[hud->worldIndex[i]]];
                }
                if (hud->worldIndex[i] != 8) {
                    fadeInput4 = hud->carouselProgress;
                    fadeInput0 = hud->fade;
                    if (fadeInput4 < fadeInput0) {
                        fd = fadeInput0;
                    } else {
                        fd = fadeInput4;
                    }
                    fc = 780.0f;
                    if (off == 0) {
                        fc += fd * 400.0;
                    }
                    dl = hudDrawCountPair(0x2B0, off + fc, cnt, 0x19, dl, 0, 0.8f);
                }
            }
            break;
        case 3:
            dl = hudDrawScaledText(hudDrawScaledText(dl, 0x280, 0x74, 0.5f, sPauseMenuStrings[sPauseCollectibleSlots[sPauseCarouselIndex] + 18]), 0x280, 0x3C, 0.65, sPauseMenuStrings[6]);
            {
                f32 fb;
                fadeInput4 = hud->carouselProgress;
                fadeInput0 = hud->fade;
                if (fadeInput4 < fadeInput0) {
                    fc = fadeInput0;
                } else {
                    fc = fadeInput4;
                }
                fb = (1.0f - fc) * 0.65f;
                if (fb < 0.01f) {
                    fb = 0.01f;
                }
                dl = hudDrawCountPair(0x280, 0x33C, gPauseCollectibleCounts[sPauseCollectibleSlots[sPauseCarouselIndex]], sPauseCollectibleTotals[sPauseCollectibleSlots[sPauseCarouselIndex]], dl, 1, fb);
            }
            break;
    }
    gSPEndDisplayList(dl);
    if (sPauseKongUnlocked == 0) {}  // FAKE: block split at the function end (if (1) {} matches): uopt colours the case-2 gPlayerInventoryTable address in $t2 (lui t2 at 0x1408); without it $t1, and $t2 joins the loop-1 ugen ring (347)
    return ret;
}

Gfx *hudDrawCountPair(s16 x, s16 y, s16 n1, s16 n2, Gfx *dl, s8 flag, f32 scale) {
    Mtx *mtx;
    s32 w;
    f32 m1[4][4];
    f32 m2[4][4];
    u8 buf1[8];
    u8 buf2[8];

    mtx = heapAlloc(sizeof(Mtx));
    heapFreeDeferred(mtx);
    if (n1 >= 0x64) {
        w = 0x7C;
    } else if (n1 >= 10) {
        w = 0x5C;
    } else {
        w = 0x3C;
    }
    if (flag != 0) {
        x = x - w * scale;
    }
    guScaleF(m1, scale, scale, 1.0f);
    guTranslateF(m2, x, y, 0.0f);
    guMtxCatF(m1, m2, m1);
    guMtxF2L(m1, mtx);
    gSPMatrix(dl++, mtx, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    _sprintf(buf1, "%d", n1);
    _sprintf(buf2, "%d", n2);
    dl = textDrawStringVtx(dl, 1, 0, -0x28, buf1, 0x80);
    dl = textDrawStringVtx(dl, 1, w, 0x28, buf2, 0);
    gSPPopMatrix(dl++, G_MTX_MODELVIEW);
    gDPPipeSync(dl++);
    return renderRotatedSprite(dl, 0x9F, 0, 2, 0x20, 0x20, x + (w - 0x10) * scale, y + 45.0f * scale, scale * 3.125, scale * 3.125, 0, 0.0f);
}

extern s8 sPauseCarouselKong;
extern f32 sPauseCarouselTimer;
extern s8 sPauseCarouselTarget;
extern s16 sPauseCarouselSpacing;
extern s8 sPauseCarouselCount;
extern void *gKongIconSprites[];
extern EffectGridAsset gControlStickSprite;
extern EffectGridAsset gZButtonSprite;
extern EffectGridAsset gCDownButtonSprite;
extern EffectGridAsset gCUpButtonSprite;
extern EffectGridAsset D_8072104C;
extern EffectGridAsset gFairySprite;
extern EffectGridAsset D_807210B8;
extern EffectGridAsset gCrownSprite;
extern EffectGridAsset D_80721110;
extern EffectGridAsset D_80721134;
extern EffectGridAsset gEffectSpriteQuestionMark;
extern EffectGridAsset D_80721474;
extern EffectGridAsset gCheckMarkSprite;



void hudPauseMenuBuildPage(HudEntry *hud, s32 refresh) {
    // per collectible: a slotQueue sprite index (small ints) or a sprite sheet of 124780.c
    static void *sTotalsPageIcons[8] = { (void *)9, &gCrownSprite, &D_807210B8, (void *)0xA, &D_80721110, &gFairySprite, &D_80721134, (void *)0xC };
    s32 saved;
    KongInventory *playerKong;
    KongInventory *pageKong;
    s32 i;
    s32 idx;
    s32 pad1;
    s32 sum;
    f32 f;
    s32 goldenSum;
    s8 foundCount;
    s16 flagId;
    s8 found[4];
    s32 kind;
    void *kongIcon;
    s32 j;
    s32 pad2;
    s32 x;
    s32 cnt;
    KongInventory *inv;

    saved = gPlayerCharacterId[0];
    playerKong = &gPlayerInventoryTable[0].kong[playerGetResolvedKongId(0)];
    gPlayerCharacterId[0] = hud->kong;
    pageKong = &gPlayerInventoryTable[0].kong[hud->kong];
    idx = hud->worldIndex[hud->buffer];
    sPauseTextCounts[hud->buffer] = 0;
    idx = sPauseLevelOrder[idx];
    if (refresh == 0) {
        sPauseCarouselKong = hud->kong;
        sPauseCarouselTarget = sPauseCarouselIndex;
        hud->carouselAngle = 0;
        hud->carouselProgress = 0.0f;
        sPauseCarouselTimer = 0.0f;
    }
    sPauseIconList = 1;
    switch (hud->page) {
    case 0:
        gPlayerCharacterId[0] = saved;
        idx = mapGetHubWorldIndex(gCurrentWorldId, 1);
        if (idx >= 9) {
            idx = 7;
        }
        if (idx != 7 && flagGet(0x18B, 0)) {
            hudPauseMenuAddCounter(hud, 0x1E, 0x1E, 0xC, -0xA, playerKong->coloredBananas[idx], 1, 0);
            hudPauseMenuSpawnIcon(hud, 0, 0x1E, 0x1E, 0.75f, 2, 1);
        }
        if (flagGet(0x184, 0)) {
            hudPauseMenuAddCounter(hud, 0x1E, 0x5A, 0xC, -0xA, gPlayerInventoryTable[0].throwAmmo, 1, 1);
            hudPauseMenuSpawnIcon(hud, 4, 0x1E, 0x5A, 0.75f, 2, 1);
        }
        if (playerKong->weaponFlags != 0) {
            hudPauseMenuAddCounter(hud, 0x1E, 0x7D, 0xC, -0xA, gPlayerInventoryTable[0].ammo, 1, 1);
            hudPauseMenuSpawnIcon(hud, 2, 0x1E, 0x7D, 0.65f, 2, 1);
        }
        if (kongUsesAbilityEnergy(gPlayerCharacterId[0])) {
            f = slotQueueGetCountStep(5);
            hudPauseMenuAddCounter(hud, 0x1E, 0xA0, 0xC, -0xA, (s32)floatCeil(gPlayerInventoryTable[0].abilityEnergy / f), 1, 1);
            hudPauseMenuSpawnIcon(hud, 5, 0x1E, 0xA0, 0.65f, 2, 1);
        }
        if (flagGet(0x18C, 0)) {
            hudPauseMenuAddCounter(hud, 0x122, 0x5A, -0xF, -0xA, playerKong->coins, 1, 0x80);
            hudPauseMenuSpawnIcon(hud, 1, 0x122, 0x5A, 0.75f, 2, 1);
        }
        if (pageKong->instrumentFlags & 1) {
            hudPauseMenuAddCounter(hud, 0x122, 0x7D, -0xC, -0xA, pageKong->instrumentEnergy, 2, 0x81);
            hudPauseMenuSpawnIcon(hud, 7, 0x122, 0x7D, 0.75f, 2, 7);
        }
        if (flagGet(0x179, 0)) {
            hudPauseMenuAddCounter(hud, 0x122, 0xA0, -0xC, -0xA, gPlayerInventoryTable[0].cameraFilm, 1, 0x81);
            hudPauseMenuSpawnIcon(hud, 6, 0x122, 0xA0, 0.65f, 2, 1);
        }
        if (gPauseCollectibleCounts[0] > 0) {
            hudPauseMenuAddCounter(hud, 0x91, 0xBE, 0xF, -0xA, gPauseCollectibleCounts[0], 1, 0);
            hudPauseMenuSpawnIcon(hud, 9, 0x91, 0xBE, 1.0f, 2, 1);
        }
        gPlayerCharacterId[0] = hud->kong;
        break;
    case 1:
        if (idx != 7) {
            i = idx;
            if (idx != 8) {
                hudPauseMenuAddCounter(hud, 0x1E, 0x2A, 0xC, -0xA, pageKong->coloredBananas[idx] + pageKong->bananasDelivered[idx], 2, 0);
                hudPauseMenuSpawnIcon(hud, 0, 0x1E, 0x2A, 0.75f, 2, 2);
            } else {
                i = 7;
            }
            if (D_807FC82E > 0) {
                if (idx != 8) {
                    sPauseIconList = (gPlayerInventoryTable[0].kong[gPlayerCharacterId[0]].coloredBananas[idx] + gPlayerInventoryTable[0].kong[gPlayerCharacterId[0]].bananasDelivered[idx]) >= 0x4B;
                } else {
                    sPauseIconList = flagGridSumRows(0x225, i, i, gPlayerCharacterId[0]);
                }
                hudPauseMenuSpawnIcon(hud, 0xA, 0x113, 0x7D, 0.75f, 2, 2);
                if (flagGridSumRows(0x225, i, i, gPlayerCharacterId[0])) {
                    hudPauseMenuSpawnIcon(hud, (s32)&gCheckMarkSprite, 0x113, 0x7D, 0.35f, 2, 0xD);
                }
            }
        }
        if (refresh == 0) {
            for (i = 0; i < 5; i++) {
                if (sPauseKongUnlocked[i]) {
                    kongIcon = gKongIconSprites[i];
                } else {
                    kongIcon = &gEffectSpriteQuestionMark;
                }
                hudPauseMenuSpawnIcon(hud, (s32)kongIcon, i, i, 0.75f, 2, 0xA);
                hudPauseMenuSpawnIcon(hud, (s32)kongIcon, i + 5, i + 5, 0.75f, 2, 0xA);
            }
        }
        if (idx != 8) {
            hudPauseMenuSpawnIcon(hud, 9, 0x91, 0xCB, 1.0f, 2, 2);
            sum = 0;
            for (i = 0; i < 5; i++) {
                if (flagGridSumRows(0x1D5, 0, 7, i)) {
                    sum = 1;
                }
            }
            if (sum) {
                i = idx;
                sPauseIconList = flagGet(flagGridIndex(0x1D5, i, gPlayerCharacterId[0]), 0);
                hudPauseMenuSpawnIcon(hud, 0xC, 0x26, 0x7D, 0.75f, 2, 2);
                if (flagGet(flagGridIndex(0x1FD, i, gPlayerCharacterId[0]), 0)) {
                    hudPauseMenuSpawnIcon(hud, (s32)&gCheckMarkSprite, 0x26, 0x7D, 0.35f, 2, 0xD);
                }
            }
        }
        if (refresh == 0) {
            hud->carouselAngle = sPauseKongTables.carouselAngle[hud->kong];
            hudPauseMenuSpawnIcon(hud, (s32)&gControlStickSprite, 0xA0, 0x78, 0.75f, 2, 0);
            if (sPauseLastLevelSlot > 0) {
                hudPauseMenuSpawnIcon(hud, (s32)&gCUpButtonSprite, 0xA0, 0x19, 0.5f, 2, 0xB);
                hudPauseMenuSpawnIcon(hud, (s32)&gCDownButtonSprite, 0xA0, 0x19, 0.5f, 2, 0xC);
            }
        }
        break;
    case 2:
        sum = 0;
        goldenSum = 0;
        for (i = 0; i < 5; i++) {
            sum += gPlayerInventoryTable[0].kong[i].coloredBananas[idx] + gPlayerInventoryTable[0].kong[i].bananasDelivered[idx];
            goldenSum += gPlayerInventoryTable[0].kong[i].goldenBananas[idx];
        }
        foundCount = 0;
        for (i = 0; i < 4; i++) {
            found[i] = 0;
        }
        for (i = 0; gSpawnFlagConditions[i].map != 0xFF; i++) {
            j = mapGetHubWorldIndex(gSpawnFlagConditions[i].map, 1);
            if (idx == j) {
                flagId = gSpawnFlagConditions[i].flag;
                if (flagId >= 0x24D && flagId < 0x261 && foundCount < 4) {
                    found[foundCount++] = flagGet(flagId, 0);
                }
            }
        }
        if (idx != 7) {
            j = idx;
            if (idx != 8) {
                hudPauseMenuAddCounter(hud, 0x24, 0x2A, 0xC, -0xA, sum, 1, 0);
                hudPauseMenuSpawnIcon(hud, (s32)&D_80721474, 0x24, 0x2A, 0.75f, 2, 1);
            } else {
                j = 7;
            }
            for (i = 0; i < 5; i++) {
                if (idx != 8) {
                    inv = &gPlayerInventoryTable[0].kong[i];
                    sPauseIconList = (inv->coloredBananas[idx] + inv->bananasDelivered[idx]) >= 0x4B;
                } else {
                    sPauseIconList = flagGridSumRows(0x225, j, j, i);
                }
                hudPauseMenuSpawnIcon(hud, 0xA, sPauseKongTables.carouselAngle[i], 0, 0.75f, 2, 3);
                if (flagGridSumRows(0x225, j, j, i)) {
                    hudPauseMenuSpawnIcon(hud, (s32)&gCheckMarkSprite, sPauseKongTables.carouselAngle[i], 0, 0.35f, 2, 0xE);
                }
            }
            if (D_807FC82A > 0) {
                sPauseIconList = flagGet(sPauseCrownFlags[idx], 0);
                hudPauseMenuSpawnIcon(hud, (s32)&gCrownSprite, 0xA0, 0x78, 1.0f, 2, 4);
            }
            if (flagGet(0x179, 0)) {
                sPauseIconList = found[0];
                hudPauseMenuSpawnIcon(hud, (s32)&gFairySprite, 0x3C, 0x78, 1.0f, 2, 6);
                sPauseIconList = found[1];
                hudPauseMenuSpawnIcon(hud, (s32)&gFairySprite, 0x104, 0x78, 1.0f, 2, 6);
            }
        } else {
            if (D_807FC82A > 0) {
                sPauseIconList = flagGet(sPauseCrownFlags[idx], 0);
                hudPauseMenuSpawnIcon(hud, (s32)&gCrownSprite, 0xA0, 0x55, 1.0f, 2, 4);
                sPauseIconList = flagGet(sPauseCrownFlags[9], 0);
                hudPauseMenuSpawnIcon(hud, (s32)&gCrownSprite, 0xA0, 0x91, 1.0f, 2, 4);
            }
            if (flagGet(0x179, 0)) {
                sPauseIconList = found[0];
                hudPauseMenuSpawnIcon(hud, (s32)&gFairySprite, 0x3C, 0x5A, 1.0f, 2, 6);
                sPauseIconList = found[1];
                hudPauseMenuSpawnIcon(hud, (s32)&gFairySprite, 0x46, 0x96, 1.0f, 2, 6);
                sPauseIconList = found[2];
                hudPauseMenuSpawnIcon(hud, (s32)&gFairySprite, 0x104, 0x5A, 1.0f, 2, 6);
                sPauseIconList = found[3];
                hudPauseMenuSpawnIcon(hud, (s32)&gFairySprite, 0xFA, 0x96, 1.0f, 2, 6);
            }
        }
        if (idx != 8) {
            hudPauseMenuSpawnIcon(hud, 9, 0x91, 0xCB, 1.0f, 2, 2);
        }
        if (refresh == 0 && sPauseLastLevelSlot > 0) {
            hudPauseMenuSpawnIcon(hud, (s32)&gCUpButtonSprite, 0xA0, 0x19, 0.5f, 2, 0xB);
            hudPauseMenuSpawnIcon(hud, (s32)&gCDownButtonSprite, 0xA0, 0x19, 0.5f, 2, 0xC);
        }
        break;
    case 3:
        sPauseCarouselCount = 0;
        for (i = 0; i < 8; i++) {
            if (gPauseCollectibleCounts[i] > 0) {
                sPauseCarouselCount++;
            }
        }
        sPauseCarouselSpacing = 0x1000 / sPauseCarouselCount;
        x = 0;
        cnt = 0;
        for (i = 0; i < 8; i++) {
            if (gPauseCollectibleCounts[i] > 0) {
                if (i != 5) {
                    f = 0.75f;
                    kind = 5;
                } else {
                    f = 1.0f;
                    kind = 8;
                }
                hudPauseMenuSpawnIcon(hud, (s32)sTotalsPageIcons[i], x, 0, f, 2, kind);
                x += sPauseCarouselSpacing;
                sPauseCollectibleSlots[cnt] = i;
                cnt++;
            }
        }
        hud->carouselAngle = sPauseCarouselSpacing * sPauseCarouselIndex;
        hudPauseMenuSpawnIcon(hud, (s32)&gControlStickSprite, 0xA0, 0x78, 0.75f, 2, 0);
        break;
    }
    if (refresh == 0 && gPauseCollectibleCounts[0] > 0) {
        hudPauseMenuSpawnIcon(hud, (s32)&gZButtonSprite, 0x2D, 0xC8, 1.0f, 2, 1);
        hudPauseMenuSpawnIcon(hud, (s32)&D_8072104C, 0x113, 0xC8, 1.0f, 2, 1);
    }
    gPlayerCharacterId[0] = saved;
}

void hudPauseMenuSpawnIcon(HudEntry *hud, s32 sprite, s32 x, s32 y, f32 scale, u8 mode, s32 kind) {
    EffectNode *obj;
    f32 *buf;
    f32 dx;
    f32 dy;
    f32 len;
    f32 fy;

    effectSetFrameDelay(mode);
    effectEnableFade();
    effectSetDuration(-1);
    effectSetSpeed((s32)hud);
    effectSetCallback(hudPauseMenuIconUpdate);
    effectSetFlags(0x101);
    fy = x;
    if (sprite < 0) {
        obj = effectCreateAtPosition((void *)sprite, scale, fy, (f32)y, -10.0f);
    } else {
        obj = effectCreateAtPosition(slotQueueGetSpriteAsset(sprite), scale, fy, (f32)y, -10.0f);
    }
    sprite = 7;
    if (kind == 6) {
        sprite = 10;
    }
    buf = heapAlloc(sprite * 4);
    obj->allocation = buf;
    if (kind == 9) {
        kind = 7;
        obj->scaleX = -obj->scaleX;
    }
    buf[0] = kind;
    buf[1] = hud->buffer;
    buf[2] = obj->x;
    buf[3] = obj->y;
    switch (kind) {
    case 1:
    case 2:
    case 7:
    case 13:
        dx = 640.0f - buf[2];
        dy = 480.0f - buf[3];
        len = sqrtf(dx * dx + dy * dy);
        buf[4] = -(dx / len) * (1040.0f - len);
        buf[5] = -(dy / len) * (1040.0f - len);
        buf[6] = obj->scaleY;
        if (kind == 13) {
            buf[0] = 2.0f;
            obj->blue = 0;
            obj->green = 0;
            obj->red = 0xFF;
        }
        break;
    case 6:
        buf[4] = 0.0f;
        buf[5] = 0.0f;
        buf[6] = 0.0f;
        buf[7] = 0.0f;
        buf[8] = randomFloat() * 4096.0f;
        if (x < 0xA0) {
            obj->scaleX = -obj->scaleX;
        }
        buf[9] = 0.0f;
        break;
    case 10:
        buf[2] = fy;
        break;
    case 14:
        buf[0] = 3.0f;
        obj->blue = 0;
        obj->green = 0;
        obj->red = 0xFF;
    default:
        buf[4] = scale;
        buf[5] = 0.0f;
        break;
    }
    if (sPauseIconList == 0) {
        obj->red = 0x64;
        obj->green = 0x64;
        obj->blue = 0x64;
    }
    sPauseIconList = 1;
}

void hudPauseMenuAddCounter(HudEntry *hud, s16 x, s16 y, s16 dx, s16 dy, s32 value, s32 style, s32 format) {
    f32 fx;
    s32 idx;
    f32 fy;
    s32 pad3;
    s32 i;
    f32 len;
    s32 pad4;
    HudTextEntry *list;
    s8 rightAlign;
    u8 buf[11];

    rightAlign = 0;
    if (format & 0x80) {
        rightAlign = 1;
        format &= ~0x80;
    }
    switch (format) {
    case 1:
        _sprintf(buf, "%02d", value);
        break;
    case 2:
        _sprintf(buf, "%d", value);
        dx -= textGetStringWidth(1, buf) >> 1;
        break;
    default:
        _sprintf(buf, "%d", value);
        break;
    }
    if (rightAlign != 0) {
        dx -= textGetStringWidth(1, buf);
    }
    D_807FC810 = textGetStringWidth(1, buf);
    idx = sPauseTextCounts[hud->buffer];
    list = sPauseTextLists[hud->buffer]->entries;
    fx = 640.0f - (f32)(x * 4);
    fy = 480.0f - (f32)(y * 4);
    len = sqrtf(fx * fx + fy * fy);
    list[idx].flyX = -(fx / len) * (1040.0f - len);
    list[idx].flyY = -(fy / len) * (1040.0f - len);
    list[idx].x = x;
    list[idx].y = y;
    list[idx].offsetX = dx;
    list[idx].offsetY = dy;
    list[idx].style = style;
    for (i = 0; buf[i] != 0; i++) {
        list[idx].text[i] = buf[i];
    }
    list[idx].text[i] = 0;
    sPauseTextCounts[hud->buffer]++;
}

Gfx *hudDrawItemLabel(Gfx *dl, HudEntry *entry, s32 itemIndex) {
    u8 padHi[0xC];
    s32 kong;
    u8 *label;
    u8 pad[0x1C];
    s32 y2;
    s32 y;

    y = entry->slideY[itemIndex] * 4;
    label = sPauseLevelNames[sPauseLevelOrder[entry->worldIndex[itemIndex]]];
    if (entry->page == 1) {
        kong = entry->kong;
    } else {
        kong = 5;
    }
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    y2 = y + 0x40;
    dl = hudDrawScaledText(hudDrawScaledText(dl, 0x280, y2, 0.7f, label), 0x280, y2 + 0x38, 0.5f, sPauseMenuStrings[kong + 9]);
    sPauseLevelLabelHalfWidth = (f32)textGetStringWidth(1, label) * 1.4;
    return dl;
}

Gfx *hudDrawScaledText(Gfx *dl, s16 x, s16 y, f32 scale, void *text) {
    f32 m1[4][4];
    f32 m2[4][4];
    Mtx *mtx;

    mtx = heapAlloc(0x40);
    heapFreeDeferred(mtx);
    guScaleF(m1, scale, scale, 1.0f);
    guTranslateF(m2, x, y, 0.0f);
    guMtxCatF(m1, m2, m1);
    guMtxF2L(m1, mtx);
    gSPMatrix(dl++, mtx, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    dl = textDrawStringVtx(dl, 1, 0, 0, text, 0x80);
    gSPPopMatrix(dl++, G_MTX_MODELVIEW);
    return dl;
}


s32 hudPauseMenuSlidePage(HudEntry *hud, s32 sliding, s32 buttons) {
    s32 idx;
    s32 slot;
    s32 delta;

    if (sliding == 0) {
        delta = 0;
        if (buttons & U_CBUTTONS) {
            delta = 1;
        } else if (buttons & D_CBUTTONS) {
            delta = -1;
        }
        if (delta != 0) {
            idx = hud->buffer;
            slot = hud->worldIndex[idx];
            slot += delta;
            if (slot < 0) {
                slot = sPauseLastLevelSlot;
            }
            if (slot > sPauseLastLevelSlot) {
                slot = 0;
            }
            if (slot != hud->worldIndex[idx]) {
                hud->buffer = 1 - idx;
                hud->worldIndex[hud->buffer] = slot;
                hud->slideY[hud->buffer] = delta * 0xFA;
                hudPauseMenuBuildPage(hud, 0);
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
    }
    if (sliding != 0) {
        delta = hud->slideY[hud->buffer];
        if (delta > 0x14) {
            delta = 0x14;
        }
        if (delta < -0x14) {
            delta = -0x14;
        }
        hud->slideY[0] -= delta;
        hud->slideY[1] -= delta;
        if (hud->slideY[hud->buffer] == 0) {
            hud->worldIndex[1 - hud->buffer] = hud->worldIndex[hud->buffer];
            sPauseTextCounts[1 - hud->buffer] = 0;
            sliding = 0;
            sfxPlayOnFreeSlot(0x97, 0x4650, 63.0f, 1.0f, 0, 0);
            sPauseBumpStep = 3;
        }
    }
    return sliding;
}


void hudPauseMenuRefreshTotals(void) {
    s16 *p;
    s16 *p0;
    s32 n;
    s32 i;
    s32 k;
    s32 m;

    p0 = &D_807FC82A - 1; do { // LAYOUT: one-line loop setup steers as1 lui/addiu order (Q0149)
        *p0++ = 0;
    } while (p0 < &D_807FC82A + 6);
    n = 0;
    for (k = 0; k < 5; k++) {
        for (i = 0; i < 14; i++) {
            n += gPlayerInventoryTable[0].kong[k].goldenBananas[i];
        }
    }
    gPauseCollectibleCounts[0] = n;
    n = 0;
    p = gWorldClearedFlags; do { // LAYOUT: one-line loop setup steers as1 lui/addiu order (Q0149)
        if (flagGet(*p, 0) != 0) {
            n++;
        }
        p++;
    } while (p < D_80744720);
    D_807FC82C = n;
    D_807FC832 = flagCountRange(0x24D, 0x14, 0);
    D_807FC82E = flagCountRange(0x225, 0x28, 0);
    m = 0;
    p = sPauseCrownFlags; do { // LAYOUT: one-line loop setup steers as1 lui/addiu order (Q0149)
        if (*p >= 0 && flagGet(*p, 0) != 0) {
            m++;
        }
        p++;
    } while (p < sPauseCrownFlags + 10);
    D_807FC82A = m;
    D_807FC834 = flagGet(0x84, 0);
    D_807FC830 = flagGet(0x17B, 0);
    D_807FC836 = flagCountRange(0x1FD, 0x28, 0);
    sPauseKongUnlocked[0] = 1;
    for (i = 0; i < 4; i++) {
        D_80750531[i] = flagGet(D_807505B2[i - 1], 0);
    }
    D_807FC838 = 1;
}

Gfx *hudDrawDimOverlay(Gfx *dl, Actor *actor) {
    return gfxFillScreenColor(dl, 0, 0, 0, 0x46);
}

// Per-icon state hudPauseMenuSpawnIcon heapAllocs into the icon effect's allocation (f32 slots).
typedef struct {
    f32 kind;
    f32 buffer;
    f32 startX;
    f32 startY;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 wanderTargetY;
    f32 wanderAngle;
    f32 wanderPause;
} HudIconState;


void hudPauseMenuIconUpdate(EffectNode *effect, s8 *done) {
    HudEntry *src;
    HudIconState *item;
    f32 t;
    f32 radius;
    s32 type;
    s32 bounceStep;
    s32 ang;
    s32 i;
    s32 kongCount = sizeof(sPauseKongColors) / sizeof(sPauseKongColors[0]);

    src = effect->data;
    if (effect->allocation != NULL) {
        t = src->fade;
        item = effect->allocation;
        bounceStep = src->slideY[(s32)item->buffer] * 4.0;
        type = (s32)item->kind;
        switch (type) {
        case 0:
        case 4:
        case 11:
        case 12:
            t = 1.0 - src->fade;
            if (t < 0.0f) {
                t = 0.0f;
            }
            if (t > 1.0f) {
                t = 1.0f;
            }
            effect->alpha = (s32)(t * 255.0f);
            if (type == 4) {
                effect->scaleX = item->unk10 * t * 4.0;
                effect->scaleY = effect->scaleX;
            }
            effect->x = item->startX;
            effect->y = item->startY + bounceStep;
            if (type == 0xB) {
                effect->x = 600.0 - sPauseLevelLabelHalfWidth;
            }
            if (type == 0xC) {
                effect->x = sPauseLevelLabelHalfWidth + 680.0;
            }
            t = 0.0f;
            break;
        case 1:
        case 2:
        case 7:
            if (type != 1) {
                t += src->carouselProgress;
            }
            if (type == 7) {
                ang = (gFrameCounter * 0x78) & 0xFFF;
                effect->scaleY = mathSinF(ang) * 0.35 + item->unk18;
            }
            effect->x = item->unk10 * t + item->startX;
            effect->y = item->unk14 * t + item->startY + bounceStep;
            break;
        case 3:
        case 5:
        case 8:
        case 15:
            t = 1.0 - src->fade;
            if (t < 0.0f) {
                t = 0.0f;
            }
            if (t > 1.0f) {
                t = 1.0f;
            }
            ang = (s32)(item->startX * 0.25) - src->carouselAngle;
            radius = 180.0f;
            if (type != 3) {
                radius = 240.0f;
            }
            radius *= t;
            effect->scaleX = item->unk10 * t * 4.0;
            effect->scaleY = effect->scaleX;
            t = 0.0;
            effect->x = mathSinF(ang) * radius + 640.0;
            effect->y = (480.0 - mathCosF(ang) * radius) + bounceStep;
            if (type == 8) {
                ang = (gFrameCounter * 0x78) & 0xFFF;
                radius = mathSinF(ang); // FAKE: radius holds the type-8 wobble sine (used from $f0, mul.s $f10,$f0,$f6 at 0x43d4; never stored to its home sp+0x48): the compound `effect->y += mathSinF(ang) * 10.0f` takes a cfe hidden temp word (Q0487, Q1537) and a dedicated f32 (any slot or block scope) a home word, either moving the uopt spill temps sp+0x24/0x30 -> 0x20/0x2c (10)
                effect->y += radius * 10.0f;
            }
            if (type == 0xF) {
                ang = (gFrameCounter * 0x78) & 0xFFF;
                radius = mathSinF(ang); // FAKE: radius holds the type-15 scale sine (used from $f0, cvt.d.s $f6,$f0 at 0x442c; never stored to sp+0x48): `effect->scaleY *= 1.0 + mathSinF(ang) * 0.2` or a dedicated f32 adds a word (spill temps sp+0x24/0x30 -> 0x20/0x2c, 10); the call inlined in the product loads scaleY before it (192)
                effect->scaleY = effect->scaleY * (1.0 + radius * 0.2);
            }
            if (type == 5 || type == 8 || type == 0xF) {
                i = 0xFF - (s32)((effect->y - 240.0) * 1.5); // FAKE: the slot index i holds the brightness (v0: subu at 0x44b8, sb at 0x44d4-0x44e4; i's home sp+0x38 unused): a dedicated s32 shade or slot adds a word and moves the case-10 slot v0 -> v1 (mfc1 at 0x48b0, 23)
                if (i < 0x5F) {
                    i = 0x5F;
                }
                if (i >= 0x100) {
                    i = 0xFF;
                }
                effect->red = i;
                effect->green = i;
                effect->blue = i;
            }
            break;
        case 6:
            radius = (item->unk14 - item->wanderTargetY) * (item->unk14 - item->wanderTargetY) + (item->unk10 - item->unk18) * (item->unk10 - item->unk18); // FAKE: radius holds the squared target distance (add.s $f2 at 0x4528, c.lt.s at 0x452c, never stored): a dedicated f32 adds a word and takes $f12 (14), the sum inlined in the test 200
            if (radius < 400.0f) {
                item->wanderPause = item->wanderPause - 1.0;
                if (item->wanderPause < 0.0) {
                    radius = randomFloat(); // FAKE: radius holds the heading-step draw (used from $f0, cvt.d.s $f8,$f0 at 0x458c): a dedicated f32 or `wanderAngle += 1000.0 + randomFloat() * 2000.0` adds a word (spill temps sp+0x24/0x30 -> 0x20/0x2c, 10), the call inlined in the plain sum swaps the add.d operands at 0x45a4 (92)
                    item->wanderAngle = item->wanderAngle + (1000.0 + radius * 2000.0);
                    ang = (s32)item->wanderAngle & 0xFFF;
                    item->wanderAngle = ang;
                    radius = (randomFloat() * 40.0 + 20.0) * 4.0;
                    item->unk18 = mathSinF(ang) * (radius * 0.8);
                    item->wanderTargetY = mathCosF(ang) * radius;
                    if (randomFloat() < 0.25) {
                        item->wanderPause = randomFloat() * 40.0 + 15.0;
                    } else {
                        item->wanderPause = 0;
                    }
                }
            }
            radius = (item->unk18 - item->unk10) * 0.1; // FAKE: radius holds the clamped x and y steps ($f2: cvt.s.d at 0x4728/0x47a0, add.s at 0x4770/0x47e8, never stored): a dedicated f32 step adds a word (spill temps sp+0x24/0x30 -> 0x20/0x2c, 10)
            if (radius < -8.0) radius = -8.0f; // LAYOUT: one-line if steers as1 scheduling of the hoisted item->unk14 load
            if (radius > 8.0) {
                radius = 8.0f;
            }
            item->unk10 += radius;
            radius = (item->wanderTargetY - item->unk14) * 0.1;
            if (radius < -8.0) {
                radius = -8.0f;
            }
            if (radius > 8.0) {
                radius = 8.0f;
            }
            item->unk14 += radius;
            ang = (gFrameCounter * 0x78) & 0xFFF;
            effect->x = item->unk10 + item->startX;
            effect->y = mathSinF(ang) * 10.0f + (item->startY + item->unk14 + bounceStep + 960.0f * t);
            t = 0.0f;
            break;
        case 10:
            i = (s32)item->startX;
            effect->x = sPauseCarouselSlotX[i];
            effect->y = sPauseCarouselSlotY[i];
            effect->scaleX = sPauseCarouselSlotScale[i];
            effect->scaleY = sPauseCarouselSlotScale[i];
            sPauseCarouselSlotX[i] = -200.0f;
            sPauseCarouselSlotY[i] = -200.0f;
            if (i >= kongCount) {
                i -= kongCount;
            }
            if (sPauseKongUnlocked[i] == 0) {
                effect->red = sPauseKongColors[i][0];
                effect->green = sPauseKongColors[i][1];
                effect->blue = sPauseKongColors[i][2];
            }
            break;
        }
        if ((s32)item->buffer != src->buffer && (bounceStep < -0x3C0 || bounceStep >= 0x3C1)) {
            *done = 1;
        }
        if (t > 1.0f || src->fade > 1.0f) {
            *done = 1;
        }
    }
}

Gfx *hudDrawTextScreen(Gfx *dl, Actor *actor) {
    u8 buf[0x28];
    s32 remaining;
    s32 val;

    remaining = 0xFF - actor->alpha;
    if (remaining >= 9) {
        val = 8;
    } else {
        val = remaining;
    }
    actor->alpha += val;
    if (actor->alpha >= 0x80) {
        val = 0x7F;
    } else {
        val = actor->alpha;
    }
    dl = hudSetupTextState(gfxFillScreenColor(dl, 0, 0, 0, val));
    gDPSetCombineLERP(dl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, actor->alpha);
    dl = textDrawStringVtx(dl, 1, 0x168, 0x104, sPauseMenuStrings[0], 1);
    _sprintf(buf, "q %s", sPauseMenuStrings[1]);
    dl = textDrawStringVtx(dl, 1, 0x208, 0x190, buf, 1);
    _sprintf(buf, "b %s", sPauseMenuStrings[2]);
    return textDrawStringVtx(dl, 1, 0x208, 0x21C, buf, 1);
}

void hudSpawnTextScreen(u8 textId) {
    actorSpawn(0x156, 0);
    gSpawnedActor->textScreenId = textId;
    gSpawnedActor->renderFlags |= 2;
    gGlobalPauseFlags |= 0x40001;
}

void hudFreeTextAndDespawn(void) {
    s16 i;

    gGlobalPauseFlags |= 0x40;
    for (i = 0; i < 3; i++) {
        heapFreeDeferred(sPauseMenuStrings[i]);
    }
    heapFreeDeferred(sPauseMenuStrings);
    actorDespawn(gCurrentActor);
}

void hudTextScreenUpdate(void) {
    s32 i;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->yawSpeed = 0x1E;
        gCurrentActor->alpha = 0;
        gCurrentActor->flags &= ~0x8000;
        sPauseMenuStrings = heapAlloc(0xC);
        for (i = 0; i < 3; i++) {
            sPauseMenuStrings[i] = textTableGetString(0x24, i + 0xF, 0);
        }
    }
    if (gCurrentActor->yawSpeed != 0) {
        gCurrentActor->yawSpeed--;
    } else if (gCurrentActor->state == 0) {
        if (gContPadCur.button & 0x8000) {
            switch (gCurrentActor->textScreenId) {
                case 2:
                    camStartPath(0, 0x20, 1);
                    hudFreeTextAndDespawn();
                    break;
                case 3:
                case 4:
                    spawnNodesSendVolumeTrigger(3, 7, 0x30, 0, 0);
                    hudFreeTextAndDespawn();
                    break;
                default:
                    mapRequestTransition(gCurrentMap, 0);
                    break;
            }
            gCurrentActor->state = 1;
        } else if (gContPadCur.button & 0x4000) {
            switch (gCurrentActor->textScreenId) {
                case 3:
                case 4:
                    spawnNodesSendVolumeTrigger(3, 7, 0x3C, 0, 0);
                case 2:
                    hudFreeTextAndDespawn();
                    break;
                case 1:
                    mapCheckAutoTransition();
                    break;
                default:
                    mapTransitionToPreviousOrExit();
                    break;
            }
            gCurrentActor->state = 1;
        }
    }
    renderCallbacksRegister(hudDrawTextScreen, gCurrentActor, 5);
}

Gfx *hudDrawTwoOptionMenu(Gfx *dl, Actor *actor) {
    static u8 sOptionShades[2] = { 0x80, 0xFF };
    u8 sel;
    u8 c;

    dl = hudSetupTextState(dl);
    sel = actor->optionCursor == 0;
    c = sOptionShades[sel];
    gDPSetPrimColor(dl++, 0, 0, c, c, c, 255);
    dl = hudDrawScaledText(dl, 0x280, 0x1B8, 0.7f, sPauseMenuStrings[0]);
    c = sOptionShades[1 - sel];
    gDPSetPrimColor(dl++, 0, 0, c, c, c, 255);
    return hudDrawScaledText(dl, 0x280, 0x208, 0.7f, sPauseMenuStrings[3]);
}

void hudTwoOptionMenuUpdate(void) {
    s32 i;
    u16 btn;

    if (!(gCurrentActor->flags & 0x10)) {
        sPauseMenuStrings = heapAlloc(0x10);
        i = 0;
        do {
            sPauseMenuStrings[i] = textTableGetString(0x24, i, 0);
            i++;
        } while (i != 4);
        gGlobalPauseFlags &= ~0x10030;
        screenWipeStart(7);
        sPauseStickHeld = 0;
        gCurrentActor->optionCursor = 0;
    }
    i = gPausingPlayer;
    if (gPlayerSlots[i].contPad->stick_y >= 0x33 || gPlayerSlots[i].contPad->stick_y < -0x32) {
        if (!(sPauseStickHeld & 1)) {
            gCurrentActor->optionCursor = 1 - gCurrentActor->optionCursor;
            sPauseStickHeld |= 1;
            sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
    } else {
        sPauseStickHeld &= ~1;
    }
    btn = *gPlayerSlots[i].heldButtonsPtr;
    if (btn & 0x8000) {
        if (gCurrentActor->optionCursor == 0) {
            gGlobalPauseFlags |= 0x10070;
            for (i = 0; i < 4; i++) {
                heapFreeDeferred(sPauseMenuStrings[i]);
            }
            heapFreeDeferred(sPauseMenuStrings);
        } else if (gCurrentActor->optionCursor == 1) {
            gMpWinnerIndex = -1;
            menuReturnToTitleWithMode3();
            gCurrentActor->optionCursor = 2;
        }
    }
    renderCallbacksRegister(hudDrawDimOverlay, gCurrentActor, 1);
    renderCallbacksRegister(hudDrawTwoOptionMenu, gCurrentActor, 5);
}
