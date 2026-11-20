#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/104F0.h"
#include "proto/global/109660.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/1295B0.h"
#include "proto/global/1332B0.h"
#include "proto/global/135D30.h"
#include "proto/global/13A7A0.h"
#include "proto/global/13C920.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/5E2F0.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/8F050.h"
#include "proto/global/90D80.h"
#include "proto/global/ACDC0.h"
#include "proto/global/C4620.h"
#include "proto/global/F56F0.h"
#include "proto/global/F600.h"
#include "proto/menu/3E10.h"


typedef struct MenuScreenState {
    f32 fade;
    f32 scroll;
    char pad8[4];
    s16 scrollY;
    s16 scrollTargetY;
    s16 unk10;
    s8 screen;
    s8 nextScreen;
    char pad14;
    s8 offsetIndex;
    s8 transitionPhase;
    s8 selection;
} MenuScreenState;


typedef struct MenuEffectTarget {
    f32 kind;
    f32 offsetIndex;
    f32 spawnX;
    f32 spawnY;
    f32 slideXOrScale;
    f32 slideY;
    f32 spawnScaleX;
} MenuEffectTarget;

typedef struct {
    s32 unk0;
    s32 unk4;
} BonusMenu_Pair;

typedef struct MenuMapExit { // map/exit pair of a cheats-menu warp
    s16 map;
    s16 exit;
} MenuMapExit;

typedef struct MenuMapCharacter { // map/character pair passed to menuSetupPlayerInventory
    s16 map;
    s16 characterId;
} MenuMapCharacter;

typedef struct MenuMapLoadout { // full menuSetupPlayerInventory argument row
    s16 map;
    s16 characterId;
    s8 inventory0;
    s8 inventory1;
    s8 inventory4;
    s8 shared;
} MenuMapLoadout;

typedef struct MenuUiRgba {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} MenuUiRgba;

extern const u8 D_80033BE0[];
extern const u8 D_80033BE4[];
extern const u8 D_80033BE8[];

s16 sMenuLastButtons = 0;
s16 D_80033674 = 250;
f32 D_80033678[8] = { 0.0f, -0.02f, 0.04f, -0.04f, 0.06f, 0.06f, -0.06f, -0.06f };
s8 D_80033698 = 0;
f32 D_8003369C = 0.0f;
s16 D_800336A0 = 0;
// Main-screen camera script: path/duration pairs, negative opcodes, -1 ends each sequence.
s16 sMenuMainCameraScript[64] = {
    -10, 150, -1, 9, 90, -7, 170, -6, 150, -1, -10, 150, -1, 1, 55, -13,
    450, -1, 2, 25, -13, 390, -1, 3, 300, -1, 4, 280, -13, 330, -1, 5,
    210, -9, 165, -13, 450, -1, 6, 80, -13, 95, -11, 420, -1, -4, 180, -12,
    604, -5, 150, -1, -2, 30, -8, 300, -3, 150, -1, -1, -1, -1, -1, 0,
};
s16 D_80033724[8] = { 0x34B, 0x34C, 0x34D, 0x34E, 0x34F, 0x350, 0x351, 0x352 };
s8 D_80033734 = 0;
s8 D_80033738 = 0;
f32 gSelectorSplineX[20] = {
    0.0f, 100.0f, 0.0f, 0.0f,
    100.0f, 85.0f, 0.0f, 0.0f,
    85.0f, -85.0f, 0.0f, 0.0f,
    -85.0f, -100.0f, 0.0f, 0.0f,
    -100.0f, 0.0f, 0.0f, 0.0f,
};
f32 gSelectorSplineY[20] = {
    -60.0f, -10.0f, 0.0f, 0.0f,
    -10.0f, 60.0f, 0.0f, 0.0f,
    60.0f, 60.0f, 0.0f, 0.0f,
    60.0f, -10.0f, 0.0f, 0.0f,
    -10.0f, -60.0f, 0.0f, 0.0f,
};
MenuUiRgba sMenuKongColors[5] = { { 0xFF, 0x00, 0x00, 0xFF }, { 0xFF, 0x00, 0x00, 0xFF }, { 0x16, 0x99, 0xFF, 0xFF }, { 0xB0, 0x45, 0xFF, 0xFF }, { 0x41, 0xFF, 0x25, 0xFF } };
s8 D_800337F0 = 0;
s8 D_800337F4 = 0;
s8 D_800337F8 = 0;
BonusMenu_Pair D_800337FC = { 0x3FFFF, 0xC80000 };
s8 sMenuKongUnlocked[5] = { 1, 0, 0, 0, 0 };
s32 D_8003380C = 0;
s32 D_80033810 = 0;
s32 D_80033814 = 0;
u8 sMenuCheatCodePos = 0;
u16 sMenuCheatCodeButtons[7] = { 0x800, 0x200, 0x800, 0x400, 0x100, 0x400, 0x2000 };
s32 D_8003382C[2] = { 1, 0 };
s32 D_80033834[6] = { 4, 2, 1, 0, 3, 5 };
u8 D_8003384C[4] = { 2, 1, 4 };
s8 D_80033850[8] = { 0, 1, 3, 1, 1, 2 };
s32 sMenuPrevButtons = 0;
s32 sMenuPrevStickBits[4] = { 0 };
s16 gMenuKongModelIds[6] = { 4, 1, 6, 9, 0xC, 0xDB };
u8 sMenuResultsPlayerCount = 0;
u8 sMenuResultsCharacters[24] = { 0 };
f32 gMenuKongSlotPositions[8] = { 160.0f, 70.0f, 210.0f, 120.0f, 160.0f, 170.0f, 110.0f, 120.0f }; // (x, y) screen position of each character-select kong slot
s32 gMenuKongScriptIds[18] = {
    0x6F, 0x133, 0x16C, 0x19E, 0x1DB, 0x1DC,
    0x42F, 0x430, 0x431, 0x432, 0x433, 0x434,
    0x435, 0x436, 0x437, 0x438, 0x439, 0x43A,
};
s8 D_800338FC = 4;
MenuMapExit gMenuCheatWarps[14] = {
    { 0x4C, 0 }, { 0x99, 0 }, { 0x1C, 0xF }, { 0x1C, 0x10 }, { 0x1C, 0x11 }, { 0x1C, 0x12 }, { 0x1C, 0x13 },
    { 0x1C, 0x14 }, { 0x1C, 0x15 }, { 0x1C, 0x16 }, { 0x1C, 0x18 }, { 0x99, 9 }, { 0x1C, 0x17 }, { 0x99, 0xB },
};
MenuMapLoadout gMenuCheatLoadouts[8] = {
    { 8, 0, 1, 3, 1, 1 }, { 0xC5, 1, 1, 3, 1, 2 }, { 0x9A, 3, 2, 3, 1, 2 }, { 0x6F, 2, 1, 3, 1, 2 },
    { 0x53, 4, 3, 3, 1, 2 }, { 0xC4, 0, 1, 3, 1, 3 }, { 0xC7, 2, 1, 3, 1, 3 }, { 0xCB, 0, 3, 3, 1, 3 },
};
MenuMapCharacter gMenuCheatMapCharacters[4] = { { 0xBF, 6 }, { 0xB8, 7 }, { 2, 0 }, { 9, 0 } };
s8 sMenuCheatOptionCounts[5] = { 0xE, 4, 8, 1, 7 };
s8 D_80033990[5] = { 2, 6, 10, 15, 20 };
s16 sMenuCheatOptionMasks[5] = { 0 };
s16 sMenuCheatRowMask = -1;
s8 gMenuHighScoreGame = 0;
const u8 *D_800339AC[3] = { D_80033BE0, D_80033BE4, D_80033BE8 };
MenuMapCharacter gMenuHighScoreGames[2] = { { 0xBF, 6 }, { 0xB8, 7 } };
s8 sMenuHighScoreHoldFrames = 0;
u8 D_800339C4[4] = "???";


extern s8 gAudioOutputMode;

void menuSetAudioMode(void) {
    u8 val = 1;
    switch (gAudioOutputMode) {
    case 0:
        val = 2;
        break;
    case 2:
        val = 4;
        break;
    }
    configureCSPOutputMode(val);
}


void menuTitleScreenHandleInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;
    s32 trigger = 0;

    if (D_80033734 != 0) {
        D_80033734++;
        if (D_80033734 >= 0xB) {
            trigger = 1;
        }
    }
    if (state->fade == 0.0 && (trigger != 0 || (buttons & 1))) {
        state->screen = 1;
        state->transitionPhase = -1;
        state->fade = 1.0f;
        menuUpdateStateDispatch(actor, 0, 0, 0);
        camEndPath(gCamActor);
        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        D_80033734 = 0;
    }
}

Gfx *menuTitleScreenDraw(void *actor, Gfx *dl) {
    return dl;
}

typedef struct MenuModelActor { // menu actors carry an extra pointer past Actor
    /* 0x000 */ Actor base;
    /* 0x178 */ s32 pad178;
    /* 0x17C */ s16 *model;
} MenuModelActor;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;

void menuResetCameraAndFlags(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    gPrimaryPlayerActor->x = 109.0f;
    gPrimaryPlayerActor->y = 6.0f;
    gPrimaryPlayerActor->z = 55.0f;
    state->fade = 0.0f;
    D_80033734 = 0;
    gGlobalPauseFlags |= 0x10000;
}


extern f32 D_80033F3C;
extern f32 D_80033F40;
extern s16 sMenuCameraScriptTimer;
extern s8 sMenuCameraScriptPos;
extern s8 D_80033F55;
extern s8 D_80033F56;
extern f32 D_80033F58;
extern f32 D_80033F5C;
extern s8 gMenuScreenSelection[]; // saved selection of each menu screen, indexed by MenuScreenState.screen
extern s8 D_8076A0D2;


void menuUpdateMainScreen(Actor *actor, s32 buttons) {
    MenuScreenState *state;
    BonusMenu_Pair pair;
    Actor *camTargetActor;
    s8 camAction;
    f32 targetBrightness;
    s32 camParam;
    s16 sel;
    s16 idxCounter;
    s16 startRandIdx;
    s16 randIdx;

    state = actor->customState;
    pair = D_800337FC;
    camAction = 0;
    if (D_800337F4 > 0) {
        D_800337F4 -= 1;
    } else {
        D_800337F4 = 0;
    }
    D_800337F0 = 0;
    if (state->fade == 0.0f && D_80033F3C == 0.0f && D_800337F4 == 0) {
        if (state->scroll == 0.0f) {
            D_800337F0 = 1;
            switch (state->selection) {
            case 2:
                if (flagGet(0x1C, 1) == 0) {
                    D_800337F0 = -1;
                }
                break;
            case 3:
                if (flagGet(0, 1) == 0) {
                    D_800337F0 = -1;
                }
                break;
            }
            menuHandleScrollInput(state, 5, buttons);
        }
        menuUpdateScrollAnimation(state, 5);
    }
    gMenuScreenSelection[2] = 0;
    if (D_80033F40 != 0.0f) {
        D_80033F3C += D_80033F40;
        if (D_80033F3C > 1.0f) {
            D_80033F3C = 1.0f;
            state->transitionPhase = 0;
            switch (state->selection) {
            default:
                state->nextScreen = 2;
                break;
            case 1:
                state->nextScreen = 8;
                break;
            case 2:
                state->nextScreen = 6;
                break;
            case 3:
                state->nextScreen = 0xA;
                break;
            case 4:
                state->nextScreen = 9;
                break;
            }
            if (camIsCutsceneActive() != 0) {
                camEndPath(gCamActor);
            }
            spawnNodesSetActorStateByFlag(0x40, 0x3C);
            if (D_80033F55 != 0) {
                camAction = -1;
            }
            D_80033F56 = 0;
        }
    }
    menuUpdateItemTransition(actor, state, 0);
    sMenuCameraScriptTimer -= 1;
    if (sMenuCameraScriptTimer <= 0) {
        switch (sMenuMainCameraScript[sMenuCameraScriptPos]) {
        case -2:
            sMenuCameraScriptTimer = sMenuMainCameraScript[sMenuCameraScriptPos + 1];
            sMenuCameraScriptPos += 2;
            camAction = 1;
            break;
        case -3:
            sMenuCameraScriptTimer = sMenuMainCameraScript[sMenuCameraScriptPos + 1];
            sMenuCameraScriptPos += 2;
            camAction = -1;
            break;
        case -4:
            sMenuCameraScriptTimer = sMenuMainCameraScript[sMenuCameraScriptPos + 1];
            sMenuCameraScriptPos += 2;
            D_80033F56 = 1;
            break;
        case -5:
            sMenuCameraScriptTimer = sMenuMainCameraScript[sMenuCameraScriptPos + 1];
            sMenuCameraScriptPos += 2;
            D_80033F56 = 0;
            break;
        default:
            if (sMenuMainCameraScript[sMenuCameraScriptPos] < -5) {
                sel = -6 - sMenuMainCameraScript[sMenuCameraScriptPos];
                if (D_800337F4 == 0) {
                    actorScriptStart(gPrimaryPlayerActor, D_80033724[sel]);
                }
                sMenuCameraScriptTimer = sMenuMainCameraScript[sMenuCameraScriptPos + 1];
                sMenuCameraScriptPos += 2;
            } else if (sMenuMainCameraScript[sMenuCameraScriptPos] >= 0) {
                camStartPath(0, sMenuMainCameraScript[sMenuCameraScriptPos], 1);
                sMenuCameraScriptTimer = sMenuMainCameraScript[sMenuCameraScriptPos + 1];
                sMenuCameraScriptPos += 2;
            } else {
                idxCounter = 0;
                randIdx = randomFloat() * 10.0f;
                sMenuCameraScriptTimer = (randomLcgNext() & 0x7F) + 0x12C;
                sMenuCameraScriptPos = 0;
                if (randIdx >= 0xB) {
                    randIdx = 0;
                }
                startRandIdx = randIdx;
                if (D_800336A0 & (1 << randIdx)) {
                    do {
                        randIdx += 1;
                        if (randIdx == 0xB) {
                            randIdx = 0;
                        }
                        if (randIdx == startRandIdx) {
                            D_800336A0 = 0;
                        }
                    } while (D_800336A0 & (1 << randIdx));
                }
                D_800336A0 |= 1 << randIdx;
                if (randIdx != 0) {
                    do {
                        if (sMenuMainCameraScript[sMenuCameraScriptPos] != -1) {
                            do {
                                sMenuCameraScriptPos += 1;
                            } while (sMenuMainCameraScript[sMenuCameraScriptPos] != -1);
                        }
                        sMenuCameraScriptPos += 1;
                        idxCounter += 1;
                    } while (idxCounter != randIdx);
                }
            }
        }
    }
    if (camAction != 0) {
        actorFindActiveByType(0xC, &camTargetActor);
        if (camAction < 0) {
            D_80033F55 = 0;
            camParam = 2;
        } else {
            D_80033F55 = 1;
            camParam = 1;
        }
        actorAppendCallbackMemcpy8(gCamActor, camTargetActor, 0x01000000, camParam, &pair, 0);
    }
    if (D_80033F56 != 0) {
        targetBrightness = 0.0f;
        D_80033F5C += 0.005;
        if (D_80033F5C > 1.0) {
            D_80033F5C = 1;
        }
    } else {
        targetBrightness = 1;
        if (D_80033F5C > 0.0) {
            D_80033F5C -= 0.005;
        } else if (D_80033F55 != 0) {
            targetBrightness = 0.45f;
        }
    }
    D_80033F58 += (targetBrightness - D_80033F58) * 0.01;
    lightSetColor(D_80033F58 * 0.83 + 0.17, D_80033F58 * 0.8 + 0.2, D_80033F58 * 0.6 + 0.4, -1);
    gfxSetBackgroundBlend(D_80033F5C);
}

extern u8 **sMenuTextTable;


Gfx *menuDrawMainScreenTitle(Actor *actor, Gfx *dl) {
    Gfx *g;
    s32 strIdx;
    s32 padCC;
    s32 padC8;
    f32 posX;
    f32 posY;
    s32 padBC;
    f32 mScale[4][4];
    f32 mTrans[4][4];
    Mtx *mtx;
    MenuScreenState *state = actor->customState;

    gGlobalPauseFlags |= 0x10;
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    strIdx = menuComputeElementPosition(state, 160.0f, 20.0f, &posX, &posY, 5, 1, 0.3f);
    mtx = heapAlloc(0x40);
    heapFreeDeferred(mtx);
    guScaleF(mScale, 0.7f, 0.7f, 1.0f);
    guTranslateF(mTrans, posX * 4.0, posY * 4.0, 0.0f);
    guMtxCatF(mScale, mTrans, mScale);
    guMtxF2L(mScale, mtx);
    g = dl++; g->words.w0 = 0xDA380003; g->words.w1 = (u32)mtx;
    return textDrawStringVtx(dl, 1, 0, 0, sMenuTextTable[strIdx], 0x80);
}

extern s8 D_80033F38;
extern u8 D_8072052C;
extern u8 D_80720C34;
extern u8 D_80720CF0;
extern u8 D_80721094;
extern u8 D_807210EC;
extern u8 D_80721170;
extern u8 D_807211D0;
extern u8 D_80721444;

void menuInitMainScreen(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;

    D_800337F8 = 0;
    D_800337F4 = 0;
    gPrimaryPlayerActor->state = 0x85;
    gPrimaryPlayerActor->unk155 = 0;
    gAudioOutputMode = eepromGetField(0x1E, 0, 0, 0);
    menuSetAudioMode();
    state->selection = gMenuScreenSelection[1];
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 0, 0, 1.2f, 2, 0x12); // FAKE: (void *)(s32) makes the address one ucvt CSE value, spilled at 0x30(sp) (sw a1 at 0xae4) and reloaded per call; an s32 asset parameter does this implicitly but draws cfe Warning 712 at every other call (Q0704)
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 1, 0, 1.2f, 2, 0x12); // FAKE: same ucvt CSE value, reloaded by lw a1,48(sp) at 0xb18
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 2, 0, 1.2f, 2, 0x12); // FAKE: same ucvt CSE value, reloaded by lw a1,48(sp) at 0xb48
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 3, 0, 1.2f, 2, 0x12); // FAKE: same ucvt CSE value, reloaded by lw a1,48(sp) at 0xb78
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 4, 0, 1.2f, 2, 0x12); // FAKE: same ucvt CSE value, reloaded by lw a1,48(sp) at 0xba8
    menuSpawnUiElementEffect(state, &D_8072052C, 0, 0, 0.6f, 2, 6);
    menuSpawnUiElementEffect(state, &D_807211D0, 1, 0, 0.8f, 2, 6);
    if (flagGet(0, 1) == 0) {
        D_80033F38 = 0;
    }
    menuSpawnUiElementEffect(state, &D_80721094, 2, 0, 0.8f, 2, 7);
    if (flagGet(0x1C, 1) == 0) {
        D_80033F38 = 0;
    }
    menuSpawnUiElementEffect(state, &D_807210EC, 3, 0, 0.6f, 2, 6);
    menuSpawnUiElementEffect(state, &D_80721170, 4, 0, 0.6f, 2, 6);
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    gPrimaryPlayerActor->x = 700.0f;
    gPrimaryPlayerActor->y = 100.0f;
    gPrimaryPlayerActor->z = 70.0f;
    sMenuCameraScriptPos = 0;
    while (sMenuMainCameraScript[sMenuCameraScriptPos] != -1) {
        sMenuCameraScriptPos++;
    }
    sMenuCameraScriptTimer = 0x1E;
    D_80033F55 = 0;
    D_80033F56 = 0;
    D_80033F5C = 0.0f;
    D_80033F58 = 1.0f;
    gGlobalPauseFlags &= 0xFFFEFFFF;
}

void menuMainScreenNoop(void) {
}

extern s8 sMenuSelectedFile;

void menuHandleSelectionInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;

    if (state->fade == 0.0f) {
        if (state->scroll == 0.0f) {
            if (buttons & 1) {
                state->transitionPhase = 0;
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                switch (state->selection) {
                case 2:
                    state->nextScreen = 4;
                    break;
                default:
                    sMenuSelectedFile = state->selection;
                    if (sMenuSelectedFile == 3) {
                        sMenuSelectedFile = 2;
                    }
                    state->nextScreen = 3;
                    break;
                }
            } else if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->transitionPhase = 0;
                state->nextScreen = 1;
            } else {
                menuHandleScrollInput(state, 4, buttons);
            }
        }
        menuUpdateScrollAnimation(state, 4);
    }
    menuUpdateItemTransition(actor, state, 1);
}


Gfx *menuDrawAdventureFileSelectTitle(Actor *actor, Gfx *dl) {
    MenuScreenState *state = actor->customState;
    s32 idx;
    f32 posX;
    f32 posY;
    u8 strBuf[204];

    gGlobalPauseFlags &= ~0x10;
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    idx = menuComputeElementPosition(state, 160.0f, 15.0f, &posX, &posY, 4, 1, 0.3f);
    if (idx == 2) {
        _sprintf(strBuf, "%s", sMenuTextTable[5]);
    } else {
        if (idx == 3) {
            idx = 2;
        }
        if (menuCheckSaveFile(idx) != 0) {
            _sprintf(strBuf, "%s", sMenuTextTable[6]);
        } else {
            _sprintf(strBuf, "%s %d", sMenuTextTable[7], idx + 1);
        }
    }
    return hudDrawScaledText(dl, posX * 4.0f, posY * 4.0f, 0.6f, strBuf);
}

extern u8 D_80720D14;
extern u8 D_807204BC;

void menuInitAdventureFileSelect(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;

    state->selection = D_8076A0D2;
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0x78, 0.75f, 2, 4);
    if (menuCheckSaveFile(0) != 0) {
        D_80033F38 = 0;
    }
    menuSpawnUiElementEffect(state, (void *)(s32)&D_8072052C, 0, 0, 1.0f, 2, 2); // FAKE: (void *)(s32) address cast keeps the lui/addiu pair scheduled before the arg loads
    if (menuCheckSaveFile(1) != 0) {
        D_80033F38 = 0;
    }
    menuSpawnUiElementEffect(state, (void *)(s32)&D_8072052C, 1, 0, 1.0f, 2, 2); // FAKE: (void *)(s32) address cast keeps the lui/addiu pair scheduled before the arg loads
    if (menuCheckSaveFile(2) != 0) {
        D_80033F38 = 0;
    }
    menuSpawnUiElementEffect(state, (void *)(s32)&D_8072052C, 3, 0, 1.0f, 2, 2); // FAKE: (void *)(s32) address cast keeps the lui/addiu pair scheduled before the arg loads
    menuSpawnUiElementEffect(state, &D_807204BC, 2, 0, 1.0f, 2, 2);
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
}


extern s8 gFaultScreenEnabled;

void menuCheckCheatCodeSequence(void) {
    if (sMenuCheatCodeButtons[sMenuCheatCodePos] == gPadPressedButtons[0]) {
        sMenuCheatCodePos++;
        if (sMenuCheatCodePos >= 7U) {
            gFaultScreenEnabled = 1;
            sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
            sMenuCheatCodePos = 0;
        }
    } else if (gPadPressedButtons[0] != 0) {
        sMenuCheatCodePos = 0;
    }
}

extern s8 sMenuSelectedFile;

void menuHandleConfirmationInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;

    if (state->fade == 0.0f && state->scroll == 0.0f) {
        if (buttons & 1) {
            controllerSetActiveMask(1);
            menuStartGameFromSave(sMenuSelectedFile);
        } else if (buttons & 2) {
            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            state->transitionPhase = 0;
            state->nextScreen = 2;
        }
    }
    menuUpdateItemTransition(actor, state, 1);
}

extern f32 D_80033F4C;
extern s8 D_80033F51;

Gfx *menuDrawFileSummary(Actor *actor, Gfx *dl) {
    f32 iconX = 66.0f;
    s16 textX;
    s16 textY;
    MenuScreenState *state = actor->customState;
    s8 *iconFlag = sMenuKongUnlocked;
    s32 i = 0;
    f32 iconScale = 3.0f;
    f32 scale;
    f32 posX;
    f32 posY;
    s32 ang;
    f32 bob;
    s32 angle;
    f32 scaleY;
    u8 strBuf[0x18];

    do {
        menuComputeElementPosition(state, iconX, 85.0f, &posX, &posY, 4, 0, 1.5f);
        if (*iconFlag != 0) {
            dl = menuSetElementCoordinates(dl, i, posX, posY, iconScale * 0.85);
        } else {
            dl = menuSetElementCoordinates(dl, i | 0x80, posX, posY, iconScale);
        }
        i++;
        iconFlag++;
        iconX += 55.0f;
    } while (i != 5);
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    menuComputeElementPosition(state, 160.0f, 180.0f, &posX, &posY, 5, 1, 2.0f);
    D_80033F4C = posY * 4.0f;
    textY = D_80033F4C;
    textY -= 0x140;
    _sprintf(strBuf, "%d%%", D_80033F51);
    dl = textDrawStringVtx(dl, 1, 0x280, textY, strBuf, 0x81);
    textY += 0x8C;
    _sprintf(strBuf, "%03d", D_8003380C);
    dl = textDrawStringVtx(dl, 1, 0x280, textY, strBuf, 0x81);
    textY += 0x8C;
    _sprintf(strBuf, "%03d:%02d", D_80033810, D_80033814);
    dl = textDrawStringVtx(dl, 1, 0x280, textY, strBuf, 0x81);
    scale = 0.5f;
    ang = (gFrameCounter * 0x78) & 0xFFF;
    bob = mathSinF(ang) * 0.1f + 0.5f;
    textY += 40.0f;
    posY = textY * 0.25f + 32.0f * bob;
    posX = 85;
    posX *= 4.0f;
    scale *= 4.0f;
    posY *= 4.0f;
    dl = renderRotatedSprite(dl, 0xA1, 3, 0, 0x40, 0x40, posX, posY, scale, -(bob * 4.0f), 0, 0.0f);
    gDPPipeSync(dl++);
    posY = textY;
    scale *= 0.75f;
    scaleY = -scale;
    posX = 340.0f;
    angle = gFrameCounter % 360U;
    dl = renderRotatedSprite(dl, 0xA0, 3, 0, 0x20, 0x20, posX, posY, scale, scaleY * 0.5f, angle, 0.0f);
    gDPPipeSync(dl++);
    angle = (gFrameCounter * 0xC) % 360U;
    dl = renderRotatedSprite(dl, 0xA0, 3, 0, 0x20, 0x20, posX, posY, scale, scaleY, angle, 0.0f);
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    menuComputeElementPosition(state, 160.0f, 15.0f, &posX, &posY, 5, 1, 0.3f);
    textX = posX * 4.0f;
    textY = posY * 4.0f;
    _sprintf(strBuf, "%s %d", sMenuTextTable[7], sMenuSelectedFile + 1);
    return hudDrawScaledText(dl, textX, textY, 0.6f, strBuf);
}

s32 menuDecodePiAddressConstant(s32 offset) {
    return offset + 0x1EFF0;
}

extern u8 D_80720CF0;
extern u8 D_80720D14;
extern u8 D_80720C34;
extern void *gKongIconSprites[];
extern s16 D_807505B2[];
extern u32 gPlayTimeBaseSeconds;
extern f32 D_80033F4C;
extern s8 D_80033F51;

void menuInitFileSummary(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    KongInventory *row = gPlayerInventoryTable[0].kong;
    s16 *flagIds;
    s32 pad;
    u32 expected;
    u8 flag;
    u32 ioVal;
    s32 i;
    s32 k;
    s32 j;

    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_8072052C, 0x76, 0x91, 0.6f, 2, 9);
    D_80033F4C = 1600.0f;
    eepromLoadPlayerData(sMenuSelectedFile, 0);
    sMenuKongUnlocked[0] = 1;
    for (i = 1, flagIds = D_807505B2; i < 5; i++, flagIds++) {
        flag = flagGet(flagIds[-1], 0);
        sMenuKongUnlocked[i] = flag;
    }
    for (i = 0; i < 5; i++) {
        menuSpawnUiElementEffect(state, sMenuKongUnlocked[i] != 0 ? gKongIconSprites[i] : &D_807211D0, i, i, 0.8f, 2, 0xF);
    }
    osPiReadIo(menuDecodePiAddressConstant(0xAFFE1464), &ioVal);
    expected = menuDecodePiAddressConstant(0x0107183B);
    if (ioVal != expected) {
        *(u32 *)actorUpdateCollisionSpheres = 0x03E00008;
    }
    D_8003380C = 0;
    for (k = 0; k < 5; k++) {
        for (j = 0; j < 8; j++) {
            D_8003380C += row->goldenBananas[j];
        }
        row++;
    }
    D_80033814 = gPlayTimeBaseSeconds / 60;
    D_80033810 = D_80033814 / 60;
    D_80033814 -= D_80033810 * 60;
    D_80033F51 = menuCalculateGamePercentage();
}


void menuHandleFileSelectInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;

    if (state->fade == 0.0f) {
        if (state->scroll == 0.0f) {
            if (buttons & 1) {
                if (menuCheckSaveFile(state->selection) == 0) {
                    state->transitionPhase = 0;
                    state->nextScreen = 5;
                    sMenuSelectedFile = state->selection;
                } else {
                    sfxPlayOnFreeSlot(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
            } else if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->transitionPhase = 0;
                state->nextScreen = 2;
            } else {
                menuHandleScrollInput(state, 3, buttons);
            }
        }
        menuUpdateScrollAnimation(state, 3);
    }
    menuUpdateItemTransition(actor, state, 1);
}



Gfx *menuDrawFileSlotLabel(Actor *actor, Gfx *dl) {
    MenuScreenState *state = actor->customState;
    s32 fileIdx;
    s32 pad0;
    s32 pad;
    f32 pad1;
    f32 textX;
    f32 textY;
    f32 pad2;
    f32 pad3;
    f32 pad4;
    s16 posX;
    s16 y;
    u8 strBuf[200];

    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    fileIdx = menuComputeElementPosition(state, 160.0f, 25.0f, &textX, &textY, 3, 1, 0.45f);
    posX = (s16)(textX * 4.0f);
    y = (s16)(textY * 4.0f);
    if (menuCheckSaveFile(fileIdx) != 0) {
        _sprintf(strBuf, "%s", sMenuTextTable[6]);
    } else {
        _sprintf(strBuf, "%s %d", sMenuTextTable[7], fileIdx + 1);
    }
    dl = hudDrawScaledText(dl, posX, y, 0.6f, strBuf);
    y -= 0x3C;
    return hudDrawScaledText(dl, (s16)(textX * 4.0f), y, 0.6f, sMenuTextTable[8]);
}


void menuInitFileSelect(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    void *assetPtr;

    state->selection = 0;
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    if (menuCheckSaveFile(0) != 0) {
        D_80033F38 = 0;
    }
    assetPtr = (void *)(s32)&D_8072052C; // FAKE: (void *)(s32) address cast keeps the lui/addiu pair scheduled before the arg loads
    menuSpawnUiElementEffect(state, assetPtr, 0, 0, 1.0f, 2, 3);
    if (menuCheckSaveFile(1) != 0) {
        D_80033F38 = 0;
    }
    menuSpawnUiElementEffect(state, assetPtr, 1, 0, 1.0f, 2, 3);
    if (menuCheckSaveFile(2) != 0) {
        D_80033F38 = 0;
    }
    menuSpawnUiElementEffect(state, assetPtr, 2, 0, 1.0f, 2, 3);
    menuSpawnUiElementEffect(state, &D_807204BC, 0xA0, 0x78, 1.0f, 2, 4);
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
}

extern u8 D_8071FBC8;
extern EffectGridAsset D_8071FE08;
extern s8 D_80033FAC;

void menuMysteryHandleInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;

    if (state->fade == 0.0f && state->scroll == 0.0f) {
        if (buttons & 1) {
            if ((buttons & 8) && (D_80033FAC != 0)) {
                effectEnableFade();
                effectCreateAtPosition(&D_8071FBC8, 10.3f, 240.0f, 120.0f, -10.0f);
                effectEnableFade();
                effectCreateAtPosition(&D_8071FE08, 10.3f, 240.0f, 120.0f, -10.0f);
                sfxPlayOnFreeSlot(0xF6, 0x7FFF, 63.0f, 1.0f, 0, 0);
                eepromSetCurrentSlot(sMenuSelectedFile, 1);
                state->transitionPhase = 0;
                state->nextScreen = 2;
            } else if ((buttons & 4) && (D_80033FAC != 0)) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->transitionPhase = 0;
                state->nextScreen = 2;
            }
        } else if (buttons & 2) {
            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            state->transitionPhase = 0;
            state->nextScreen = 2;
        }
    }
    menuUpdateItemTransition(actor, state, 1);
}


Gfx *menuMysteryDrawFileSlotLabel(Actor *actor, Gfx *dl) {
    MenuScreenState *state = actor->customState;
    s32 pad;
    f32 pad1;
    Gfx *g;
    f32 pad2;
    f32 textX;
    f32 textY;
    f32 pad3;
    f32 pad4;
    f32 pad5;
    s16 posX;
    s16 y;
    u8 strBuf[200];

    g = dl++; g->words.w0 = 0xFA000000; g->words.w1 = -1;
    menuComputeElementPosition(state, 160.0f, 25.0f, &textX, &textY, 5, 0, 0.45f);
    posX = (s16)(textX * 4.0f);
    y = (s16)(textY * 4.0f);
    if (menuCheckSaveFile(sMenuSelectedFile) != 0) {
        _sprintf(strBuf, "%s", sMenuTextTable[6]);
    } else {
        _sprintf(strBuf, "%s %d", sMenuTextTable[7], sMenuSelectedFile + 1);
    }
    dl = hudDrawScaledText(dl, posX, y, 0.6f, strBuf);
    y -= 0x3C;
    dl = hudDrawScaledText(dl, (s16)(textX * 4.0f), y, 0.6f, sMenuTextTable[8]);
    menuComputeElementPosition(state, 160.0f, 80.0f, &textX, &textY, 5, 0, 2.0f);
    dl = hudDrawScaledText(dl, (s16)(textX * 4.0f), (s16)(textY * 4.0f), 0.6f, sMenuTextTable[9]);
    menuComputeElementPosition(state, 80.0f, 120.0f, &textX, &textY, 5, 0, 2.0f);
    return hudDrawScaledText(hudDrawScaledText(dl, (s16)(textX * 4.0f), (s16)(textY * 4.0f), 0.6f, sMenuTextTable[10]), 0x500 - (s16)(textX * 4.0f), (s16)(textY * 4.0f), 0.6f, sMenuTextTable[11]);
}

extern s8 D_80033FAC;

void menuMysteryInit(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;

    D_80033FAC = 0;
    state->selection = 0;
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_807204BC, 0xA0, 0x80, 1.0f, 2, 8);
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
}

extern s8 D_80744538;
extern s8 D_8076A104;

void menuBossReplayHandleInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;

    if (state->fade == 0.0f) {
        if (state->scroll == 0.0f) {
            if (buttons & 1) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->transitionPhase = 0;
                state->nextScreen = 7;
            } else if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->transitionPhase = 0;
                state->nextScreen = 1;
                D_80033698 = 3;
            } else {
                menuHandleScrollInput(state, 2, buttons);
            }
            if (state->selection == 0) {
                if (!(sMenuLastButtons & 0x10) && (buttons & 0x10)) {
                    sfxPlayOnFreeSlot(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    D_80744538++;
                    if (D_80744538 >= 3) {
                        D_80744538 = 0;
                    }
                } else if (!(sMenuLastButtons & 0x20) && (buttons & 0x20)) {
                    sfxPlayOnFreeSlot(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    D_80744538--;
                    if (D_80744538 < 0) {
                        D_80744538 = 2;
                    }
                }
            }
        }
        menuUpdateScrollAnimation(state, 2);
    }
    D_8076A104 = state->selection;
    menuUpdateItemTransition(actor, state, 1);
}


Gfx *menuDrawSubmenuRing(Actor *actor, Gfx *dl) {
    MenuScreenState *state = actor->customState;
    s32 pad;
    s32 idx;
    s32 i;
    s32 id;
    s32 ang;
    f32 posX;
    f32 posY;
    u8 strBuf[0xD8];

    gGlobalPauseFlags &= ~0x10;
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    idx = menuComputeElementPosition(state, 160.0f, 20.0f, &posX, &posY, 2, 1, 0.7f);
    dl = textDrawStringVtx(dl, 1, posX * 4.0f, posY * 4.0f, sMenuTextTable[idx + 12], 0x81);
    if (idx == 0) {
        _sprintf(strBuf, "%s %d", sMenuTextTable[14], D_80744538 + 1);
        menuComputeElementPosition(state, 160.0f, 207.0f, &posX, &posY, 2, 0, 0.7f);
        dl = hudDrawScaledText(dl, posX * 4.0f, posY * 4.0f, 0.6f, strBuf);
    }
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    for (i = 0; i != 0x1000; i += 0x800) {
        ang = i - (state->selection << 11);
        ang -= (s32)(state->scroll * 2048.0);
        posX = 160.0 - mathSinF((s16)ang) * 50.0;
        posY = 120.0 - mathCosF((s16)ang) * 50.0;
        menuComputeElementPosition(state, posX, posY, &posX, &posY, 2, 0, 1.5f);
        posX += 12.0;
        posX *= 4.0f;
        posY += 28.0;
        posY *= 4.0f;
        if (i == 0) {
            id = D_80744538 + 0xB2;
        } else {
            id = 0xB1;
        }
        dl = renderRotatedSprite(
            renderRotatedSprite(dl, id, 0, 2, 0x20, 0x40, posX - 96.0, posY, 3.0f, -3.0f, 0, 0.0f),
            id + 4, 0, 2, 0x20, 0x40, posX, posY, 3.0f, -3.0f, 0, 0.0f);
    }
    return dl;
}

extern s8 D_8076A100[];
extern s8 gMenuPlayerCharacterSel[];
extern s8 D_8076A0E8[][4];

void menuAssignPlayerControllerSlot(s32 playerIdx, s32 slotIdx) {
    s8 prevSlot = gMenuPlayerCharacterSel[playerIdx];
    s32 found = 0;
    s8 *assignedSlotPtr = &D_8076A100[playerIdx];
    s8 prevSubSlot = *assignedSlotPtr;
    s32 subSlot;

    if (prevSubSlot >= 0) {
        D_8076A0E8[prevSlot][prevSubSlot] = -1;
    }
    for (subSlot = 0; (subSlot < 4) && (found == 0); subSlot++) {
        if (D_8076A0E8[slotIdx][subSlot] == -1) {
            found = 1;
            *assignedSlotPtr = subSlot;
            D_8076A0E8[slotIdx][subSlot] = playerIdx;
        }
    }
    gMenuPlayerCharacterSel[playerIdx] = slotIdx;
}

void menuReleasePlayerControllerSlot(s32 playerIdx) {
    s8 slot = gMenuPlayerCharacterSel[playerIdx];
    s8 *assignedSlotPtr = &D_8076A100[playerIdx];
    s8 subSlot = *assignedSlotPtr;

    if ((subSlot >= 0) && !(slot & 0x80)) {
        D_8076A0E8[slot][subSlot] = -1;
    }
    *assignedSlotPtr = -1;
    gMenuPlayerCharacterSel[playerIdx] = -0x80;
}


void menuInitControllerSlots(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    s32 i;
    s32 j;

    state->selection = gMenuScreenSelection[6];
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0x78, 0.75f, 2, 4);
    for (i = 0; i < 6; i++) {
        j = 0;
        do {
            D_8076A0E8[i][j] = -1;
            j++;
        } while (j < 4);
    }
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            menuAssignPlayerControllerSlot(i, i);
        } else {
            gMenuPlayerCharacterSel[i] = -0x80;
            menuReleasePlayerControllerSlot(i);
        }
    }
}

s32 menuNextFreeControllerSlot(s32 playerIdx) {
    s8 slot = gMenuPlayerCharacterSel[playerIdx];
    s8 *row;
    s32 idx;
    s32 flag;

    idx = D_8076A100[playerIdx];
    flag = 0;
    row = D_8076A0E8[slot];
    row[idx] = -1;
    do {
        idx += 1;
        if (idx >= 4) {
            idx = 0;
        }
        if (row[idx] == -1) {
            flag = 1;
            D_8076A100[playerIdx] = idx;
            row[idx] = playerIdx;
        }
    } while (flag == 0);
    return idx;
}

s32 menuPrevFreeControllerSlot(s32 playerIdx) {
    s8 slot = gMenuPlayerCharacterSel[playerIdx];
    s8 *row;
    s32 idx;
    s32 flag;

    idx = D_8076A100[playerIdx];
    flag = 0;
    row = D_8076A0E8[slot];
    row[idx] = -1;
    do {
        idx -= 1;
        if (idx < 0) {
            idx = 3;
        }
        if (row[idx] == -1) {
            flag = 1;
            D_8076A100[playerIdx] = idx;
            row[idx] = playerIdx;
        }
    } while (flag == 0);
    return idx;
}

extern s8 sMenuJoinedPlayerCount;
extern s8 D_80744520;
extern s8 D_80744534;
extern s8 sMenuMatchStarting;
extern s8 D_80033F50;
extern u8 gMenuReturnContext;
extern s8 sMenuCharacterAvailMask;
extern s8 D_8074451C;
extern u8 gSplitScreenViewMask;
extern u8 gActivePlayerCount;
extern u8 gControllerConnectedMask;
extern OSContPad gControllerPads[];

void menuHandleControllerSlotInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;
    s32 step;
    s32 rest;
    s32 i;
    s32 j;
    s32 edge;
    s32 bits;
    s32 idx;
    s32 itemCount;
    s32 cap;
    s32 lim;
    u8 mask;
    s32 pressed;

    step = state->scrollTargetY - state->scrollY;
    if (step > 0x14) {
        step = 0x14;
    }
    if (step < -0x14) {
        step = -0x14;
    }
    state->scrollY += step;
    rest = state->scrollTargetY - state->scrollY;
    if (step != 0 && rest == 0) {
        sfxPlayOnFreeSlot(0x3C, 0x4E20, 63.0f, 1.0f, 0, 0);
        D_80033F50 = 3;
    }
    if (sMenuMatchStarting != 0) {
        buttons = 0;
    }
    if (state->fade == 0.0f && rest == 0) {
        itemCount = 5;
        if (D_8076A104 == 0) {
            itemCount = 6;
        }
        if (state->scroll == 0.0f) {
            if ((buttons & 1) && sMenuJoinedPlayerCount >= 2) {
                mask = 0;
                gActivePlayerCount = 0;
                for (j = 0; j != 4; j++) {
                    bits = 1 << j;
                    if (!(gMenuPlayerCharacterSel[j] & 0x80)) {
                        gPlayerCharacterId[j] = gMenuPlayerCharacterSel[j];
                        mask |= bits;
                        gMpSettings.playerControllerSlots[gActivePlayerCount] = D_8076A100[j];
                        gActivePlayerCount++;
                    }
                }
                controllerSetActiveMask(mask);
                gMpSettings.unk0 = D_8003382C[D_8076A104];
                gMpSettings.gameMode = D_80033834[D_8074451C];
                gMpSettings.limit = D_80744520;
                gMpSettings.mapIndex = D_80744538;
                gSplitScreenViewMask = D_8003384C[D_80744534];
                sMenuMatchStarting = 1;
                gMenuReturnContext = 2;
                mpStartMatch();
            } else if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                state->transitionPhase = 0;
                state->nextScreen = 6;
            } else if (buttons & 0x40) {
                state->scrollTargetY -= 0xF0;
                if ((sMenuJoinedPlayerCount == 2 || sMenuJoinedPlayerCount == 3) && D_8076A104 != 1) {
                    lim = -0x1E0;
                } else {
                    lim = -0xF0;
                }
                if (state->scrollTargetY < lim) {
                    state->scrollTargetY = lim;
                } else {
                    sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                }
            } else if (buttons & 0x80) {
                state->scrollTargetY += 0xF0;
                if (state->scrollTargetY > 0) {
                    state->scrollTargetY = 0;
                } else {
                    sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                }
            }
            pressed = BUTTONS_PRESSED(buttons, sMenuPrevButtons);
            if (state->scrollY == 0 && sMenuMatchStarting == 0) {
                for (i = 0; i != 4; i++) {
                    bits = 0;
                    if (gControllerConnectedMask & (1 << i)) {
                        if (gControllerPads[i].stick_x < -0x28) {
                            bits = 4;
                        } else if (gControllerPads[i].stick_x > 0x28) {
                            bits = 8;
                        }
                        if (gControllerPads[i].stick_y < -0x28) {
                            bits |= 0x20;
                        } else if (gControllerPads[i].stick_y > 0x28) {
                            bits |= 0x10;
                        }
                        edge = BUTTONS_PRESSED(bits, sMenuPrevStickBits[i]);
                        sMenuPrevStickBits[i] = bits;
                        if (gMenuPlayerCharacterSel[i] & 0x80) {
                            if (gPadPressedButtons[i] & 0x1000) {
                                sfxPlayOnFreeSlot(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                menuAssignPlayerControllerSlot(i, 0);
                            }
                        } else {
                            if (edge & 8) {
                                sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                idx = gMenuPlayerCharacterSel[i] + 1;
                                if (idx >= 6) {
                                    idx = 0;
                                }
                                while (!(sMenuCharacterAvailMask & (1 << idx))) {
                                    idx++;
                                    if (idx >= 6) {
                                        idx = 0;
                                    }
                                }
                                menuAssignPlayerControllerSlot(i, idx);
                            }
                            if (edge & 4) {
                                sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                idx = gMenuPlayerCharacterSel[i] - 1;
                                if (idx < 0) {
                                    idx = 5;
                                }
                                while (!(sMenuCharacterAvailMask & (1 << idx))) {
                                    idx--;
                                    if (idx < 0) {
                                        idx = 5;
                                    }
                                }
                                menuAssignPlayerControllerSlot(i, idx);
                            }
                            if (edge & 0x10) {
                                sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                menuNextFreeControllerSlot(i);
                            }
                            if (edge & 0x20) {
                                sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                menuPrevFreeControllerSlot(i);
                            }
                            if (i != 0 && (gPadPressedButtons[i] & 0x1000)) {
                                sfxPlayOnFreeSlot(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                menuReleasePlayerControllerSlot(i);
                            }
                        }
                    }
                }
            } else if (state->scrollY == -0xF0) {
                if (BUTTONS_PRESSED(buttons, sMenuPrevButtons) & 0x10) {
                    cap = 5;
                    if (D_80033834[D_8074451C] == 5) {
                        cap = 4;
                    }
                    if (D_80744520 < cap) {
                        D_80744520++;
                        sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    }
                } else if ((BUTTONS_PRESSED(buttons, sMenuPrevButtons) & 0x20) && D_80744520 >= 2) {
                    D_80744520--;
                    sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
                menuHandleScrollInput(state, itemCount, pressed);
            } else if (state->scrollY == -0x1E0) {
                if (BUTTONS_PRESSED(buttons, sMenuPrevButtons) & 0x10) {
                    D_80744534++;
                    if (D_80744534 >= 3) {
                        D_80744534 = 0;
                    }
                    sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                } else if (BUTTONS_PRESSED(buttons, sMenuPrevButtons) & 0x20) {
                    D_80744534--;
                    if (D_80744534 < 0) {
                        D_80744534 = 2;
                    }
                    sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
            }
        }
        menuUpdateScrollAnimation(state, itemCount);
    }
    sMenuPrevButtons = buttons;
    D_8074451C = state->selection;
    if (D_80033834[D_8074451C] == 5 && D_80744520 >= 5) {
        D_80744520 = 4;
    }
    menuUpdateItemTransition(actor, state, 1);
    gGlobalPauseFlags |= 0x10000;
    menuUpdateCameraPositions();
    sMenuJoinedPlayerCount = 0;
    for (i = 0; i < 4; i++) {
        if (!(gMenuPlayerCharacterSel[i] & 0x80)) {
            sMenuJoinedPlayerCount++;
        }
    }
}


extern f32 D_80033F44;
extern s8 sMenuJoinedPlayerCount;
extern s8 D_80744520;
extern s8 D_80744534;

Gfx *menuDrawCharacterSelect(Actor *actor, Gfx *dl) {
    MenuScreenState *state = actor->customState;
    s32 pad0;
    s32 idx;
    s32 id;
    f32 posX;
    f32 posY;
    f64 offset;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s16 pad4;
    s16 textY;
    u8 strBuf[0xC8];
    f32 slide;

    if (state->scrollY > -239.0) {
        if (gMenuPlayerCharacterSel[1] & 0x80) {
            menuComputeElementPosition(state, 210.0f, 120.0f, &posX, &posY, 2, 0, 1.8f);
            dl = menuSetElementCoordinates(dl, 0x81, posX + 8.0, posY + 32.0f, 3.0f);
        }
        if (gMenuPlayerCharacterSel[2] & 0x80) {
            menuComputeElementPosition(state, 160.0f, 170.0f, &posX, &posY, 2, 0, 1.8f);
            dl = menuSetElementCoordinates(dl, 0x82, posX + 8.0, posY + 32.0f, 3.0f);
        }
        if (gMenuPlayerCharacterSel[3] & 0x80) {
            menuComputeElementPosition(state, 110.0f, 120.0f, &posX, &posY, 2, 0, 1.8f);
            dl = menuSetElementCoordinates(dl, 0x83, posX + 8.0, posY + 32.0f, 3.0f);
        }
        gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
        menuComputeElementPosition(state, 160.0f, 25.0f, &posX, &posY, 2, 0, 0.6f);
        dl = textDrawStringVtx(dl, 1, posX * 4.0f, posY * 4.0f, sMenuTextTable[D_8076A104 + 12], 0x81);
    }
    if (state->scrollY < -1.0f && state->scrollY > -479.0f) {
        gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
        menuComputeElementPosition(state, 160.0f, 30.0f, &posX, &posY, 2, 0, 1.5f);
        posY += 240.0f;
        dl = textDrawStringVtx(dl, 1, 0x280, posY * 4.0f, sMenuTextTable[15], 0x81);
        idx = state->selection;
        if (state->scroll != 0.0f) {
            if (state->scroll > 0.5f) {
                idx++;
            }
            if (idx >= 4) {
                idx = 0;
            }
        }
        slide = state->scroll - 0.5f;
        if (slide < 0.0f) {
            slide = -slide;
        }
        slide = 0.5f - slide;
        slide *= 700.0f;
        if (D_80033F44 < 0.0f) {
            slide = -slide;
        }
        offset = slide;
        menuComputeElementPosition(state, offset + 160.0, 80.0f, &posX, &posY, 2, 0, 2.0f);
        posY += 240.0f;
        dl = textDrawStringVtx(dl, 1, posX * 4.0f, posY * 4.0f, sMenuTextTable[idx + 16], 0x81);
        menuComputeElementPosition(state, 160.0 - offset, 160.0f, &posX, &posY, 2, 0, 1.5f);
        posY += 240.0f;
        textY = (s16)(posY * 4.0f);
        switch (D_80033850[idx]) {
        case 0:
            if (D_80744520 >= 2) {
                _sprintf(strBuf, "%d %s", D_80744520, sMenuTextTable[23]);
            } else {
                _sprintf(strBuf, "%d %s", D_80744520, sMenuTextTable[22]);
            }
            break;
        case 1:
            if (D_80744520 >= 2) {
                _sprintf(strBuf, "%d %s", D_80744520, sMenuTextTable[25]);
            } else {
                _sprintf(strBuf, "%d %s", D_80744520, sMenuTextTable[24]);
            }
            break;
        case 2:
            if (D_80744520 >= 2) {
                _sprintf(strBuf, "%d %s", D_80744520, sMenuTextTable[27]);
            } else {
                _sprintf(strBuf, "%d %s", D_80744520, sMenuTextTable[26]);
            }
            break;
        case 3:
            _sprintf(strBuf, "%d", D_80744520);
            break;
        }
        dl = textDrawStringVtx(dl, 1, posX * 4.0f, textY, strBuf, 0x81);
    }
    if (state->scrollY < -241.0f) {
        gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
        menuComputeElementPosition(state, 160.0f, 40.0f, &posX, &posY, 2, 0, 1.5f);
        posY += 480.0f;
        dl = textDrawStringVtx(dl, 1, 0x280, posY * 4.0f, sMenuTextTable[28], 0x81);
        menuComputeElementPosition(state, 160.0f, 180.0f, &posX, &posY, 2, 0, 1.5f);
        posY = (posY + 480.0f) * 4.0f;
        posX = (posX + 16.0f) * 4.0f;
        id = sMenuJoinedPlayerCount * 6 + D_80744534 * 2 + 0x98;
        gDPPipeSync(dl++);
        gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
        dl = renderRotatedSprite(dl, id, 0, 2, 0x20, 0x40, posX - 128.0, posY, 4.0f, -4.0f, 0, 0.0f);
        gDPPipeSync(dl++);
        dl = renderRotatedSprite(dl, ++id, 0, 2, 0x20, 0x40, posX, posY, 4.0f, -4.0f, 0, 0.0f);
    }
    return dl;
}

typedef struct MenuCharacterKongState { // customState of the character-select kong actors
    Actor *parent; // parent menu actor
    s32 animFrame;
    s8 animSet;
} MenuCharacterKongState;
extern s8 sMenuMatchStarting;
extern s8 sMenuCharacterAvailMask;
extern s8 D_8074451C;
extern s16 D_80744544;
extern u8 D_80720D5C;
extern u8 D_80720D80;
extern u8 D_807211AC;

void menuInitCharacterSelect(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    s32 flag;
    s32 i;
    MenuCharacterKongState *sub;
    s16 *model;

    menuUpdateCameraPositions();
    sMenuCharacterAvailMask = 1;
    flag = 0x1D;
    for (i = 1; i < 5; i++) {
        if (flagGet(flag, 1) != 0) {
            sMenuCharacterAvailMask |= 1 << i;
        }
        flag += 1;
    }
    if (D_80744544 & 1) {
        sMenuCharacterAvailMask |= 0x20;
    }
    sMenuMatchStarting = 0;
    sMenuJoinedPlayerCount = 0;
    if (D_8076A104 != 0 && D_8074451C >= 5) {
        D_8074451C = 0;
    }
    state->selection = D_8074451C;
    for (i = 0; i != 4; i++) {
        actorSpawn(0x151, gMenuKongModelIds[gMenuPlayerCharacterSel[i] & 0x7F]);
        model = ((MenuModelActor *)gSpawnedActor)->model;
        *model = gMenuKongModelIds[gMenuPlayerCharacterSel[i] & 0x7F];
        gSpawnedActor->state = i;
        gSpawnedActor->unk155 = gMenuPlayerCharacterSel[i] & 0x7F;
        sub = gSpawnedActor->customState;
        sub->parent = actor;
        sub->animSet = 0;
    }
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0x7D, 0.75f, 2, 4);
    menuSpawnUiElementEffect(state, &D_80720D80, 0xA0, 0x10, 0.5f, 2, 0);
    menuSpawnUiElementEffect(state, &D_807211AC, 0xA0, 0xDC, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_807211D0, 1, 1, 0.8f, 2, 0xF);
    menuSpawnUiElementEffect(state, &D_807211D0, 2, 2, 0.8f, 2, 0xF);
    menuSpawnUiElementEffect(state, &D_807211D0, 3, 3, 0.8f, 2, 0xF);
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0xB);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0xB);
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0x16D, 0.75f, 2, 4);
    menuSpawnUiElementEffect(state, &D_80720D5C, 0xA0, 0xDC, 0.5f, 2, 0xB);
    menuSpawnUiElementEffect(state, &D_80720D80, 0xA0, 0x10, 0.5f, 2, 0x13);
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0xD);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0xD);
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0x23F, 0.75f, 2, 4);
    menuSpawnUiElementEffect(state, &D_80720D5C, 0xA0, 0xDC, 0.5f, 2, 0xD);
}


void menuMultiplayerResultsHandleInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;

    if (state->fade == 0.0 && (buttons & 1)) {
        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
        state->transitionPhase = 0;
        state->nextScreen = 7;
    }
    menuUpdateItemTransition(actor, state, 0);
    menuUpdateCameraPositions();
    gGlobalPauseFlags &= ~0x10;
    gGlobalPauseFlags |= 0x10000;
}

extern u8 D_80033F20[];
extern s16 D_80744524[];
extern s8 gMpWinnerIndex;

Gfx *menuDrawMultiplayerResults(Actor *actor, Gfx *dl) {
    MenuScreenState *state;
    s32 step;
    s32 i;
    s16 x;
    f32 textX;
    f32 textY1;
    f32 textY2;
    u8 *player;
    s16 scaledY1;
    s16 scaledY2;
    u8 strBuf[200];
    s32 isWinner;

    state = actor->customState;
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    menuComputeElementPosition(state, 160.0f, 45.0f, &textX, &textY1, 2, 0, 1.8f);
    menuComputeElementPosition(state, 160.0f, 185.0f, &textX, &textY2, 2, 0, 1.8f);
    scaledY1 = textY1 * 4.0;
    scaledY2 = textY2 * 4.0;
    step = 0x11D / sMenuResultsPlayerCount;
    x = step * 2 + 0x46;
    step *= 4;
    for (i = 0, player = D_80033F20; i < sMenuResultsPlayerCount; i++, player++) {
        _sprintf(strBuf, "P %d", *player + 1);
        dl = hudDrawScaledText(dl, x, scaledY1, 0.6f, strBuf);
        isWinner = i == gMpWinnerIndex;
        dl = hudDrawScaledText(dl, x, scaledY1 + 0x30, 0.6f, sMenuTextTable[0x1D + isWinner]);
        _sprintf(strBuf, "%d", D_80744524[*player]);
        dl = hudDrawScaledText(dl, x, scaledY2, 0.6f, strBuf);
        x += step;
    }
    return hudDrawScaledText(dl, 0x280, scaledY2 - 0x50, 0.6f, sMenuTextTable[0x1F]);
}


extern u8 D_80033F24[];

void menuInitMultiplayerResults(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    s32 i;
    s8 charSel;
    MenuCharacterKongState *sub;
    s16 *model;

    for (i = 0; i < 4; i++) {
        charSel = gMenuPlayerCharacterSel[i];
        if (!(charSel & 0x80)) {
            sMenuResultsCharacters[sMenuResultsPlayerCount] = charSel & 0x7F;
            D_80033F20[sMenuResultsPlayerCount] = i;
            D_80033F24[i] = sMenuResultsPlayerCount;
            if (sMenuResultsPlayerCount == gMpWinnerIndex) {
                D_80744524[i] += 1;
            }
            sMenuResultsPlayerCount++;
        }
    }
    menuUpdateCameraPositions();
    state->selection = 0;
    for (i = 0; i < sMenuResultsPlayerCount; i++) {
        actorSpawn(0x151, gMenuKongModelIds[sMenuResultsCharacters[i]]);
        model = ((MenuModelActor *)gSpawnedActor)->model;
        *model = gMenuKongModelIds[sMenuResultsCharacters[i]];
        gSpawnedActor->state = D_80033F20[i] | 0x80;
        gSpawnedActor->unk155 = sMenuResultsCharacters[i];
        sub = gSpawnedActor->customState;
        sub->parent = actor;
        sub->animSet = (i == gMpWinnerIndex) + 1;
    }
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
}


void menuCharacterSelectUpdateActor(void) {
    s32 step;
    f32 *row;
    MenuScreenState *parentState;
    s32 sel;
    f32 posX;
    f32 posY;
    s8 shouldDespawn;
    s8 kong;
    s16 idx;
    s16 *actorTypePtr;
    MenuCharacterKongState *kongState;
    s16 *model;
    MenuCharacterKongState *spawnedState;

    kongState = gCurrentActor->customState;
    parentState = kongState->parent->customState;
    shouldDespawn = 0;
    actorKongChainUpdate();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->sub4->scaleX *= 2.0f;
        gCurrentActor->sub4->scaleY *= 2.0f;
        gCurrentActor->sub4->scaleZ *= 2.0f;
        kong = kongState->animSet;
        actorScriptStart(gCurrentActor, gMenuKongScriptIds[(s16)(kong * 6) + (gCurrentActor->unk155 & 0xF)]);
        playerKongHolsterGun(gCurrentActor);
        gCurrentActor->flags |= 0x1000;
        kongState->animFrame = D_8076A100[gCurrentActor->state & 0xF];
        actorConfigApplyAnimFrameByType(gCurrentActor, gCurrentActor->unk155 + 2, D_8076A100[gCurrentActor->state & 0xF]);
    }
    sel = gCurrentActor->state;
    if (!(sel & 0x80)) {
        if (kongState->animFrame != D_8076A100[gCurrentActor->state]) {
            actorConfigApplyAnimFrameByType(gCurrentActor, gCurrentActor->unk155 + 2, D_8076A100[gCurrentActor->state]);
            kongState->animFrame = D_8076A100[gCurrentActor->state];
        }
        idx = gMenuPlayerCharacterSel[gCurrentActor->state] & 0x7F;
        if (idx != gCurrentActor->unk155) {
            actorTypePtr = &gMenuKongModelIds[idx];
            actorSpawn(0x151, *actorTypePtr);
            model = ((MenuModelActor *)gSpawnedActor)->model;
            *model = *actorTypePtr;
            gSpawnedActor->state = gCurrentActor->state;
            gSpawnedActor->unk155 = idx;
            spawnedState = gSpawnedActor->customState;
            spawnedState->parent = kongState->parent;
            shouldDespawn = 1;
        }
        row = &gMenuKongSlotPositions[gCurrentActor->state * 2];
        menuComputeElementPosition(parentState, row[0], row[1], &posX, &posY, 2, 0, 1.8f);
        gCurrentActor->x = gPrimaryPlayerActor->x + (posX - 160.0f);
        gCurrentActor->y = (gPrimaryPlayerActor->y - (posY - 120.0f)) - 20.0f;
        gCurrentActor->z = gPrimaryPlayerActor->z - 300.0f;
        if (gMenuPlayerCharacterSel[gCurrentActor->state] & 0x80) {
            gCurrentActor->flags &= ~4;
        } else {
            gCurrentActor->flags |= 4;
        }
    } else {
        idx = D_80033F24[sel & 0xF];
        step = 0x140 / sMenuResultsPlayerCount;
        menuComputeElementPosition(parentState, 160.0f, 150.0f, &posX, &posY, 2, 0, 1.8f);
        posX = (idx * step + (step >> 1)) - 0xA0;
        posX *= 0.78;
        gCurrentActor->x = gPrimaryPlayerActor->x + posX;
        gCurrentActor->y = (gPrimaryPlayerActor->y - (posY - 120.0f)) + 16.0f;
        gCurrentActor->z = gPrimaryPlayerActor->z - 300.0f;
    }
    if (parentState->fade > 1.0f) {
        shouldDespawn = 1;
    }
    if (shouldDespawn != 0) {
        actorDespawn(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s8 gSfxVolume;
extern s8 gMusicVolume;

void menuHandleSoundOptionsInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;
    s8 changed = 0;

    menuCheckCheatCodeSequence();
    if (state->fade == 0.0f) {
        if (state->scroll == 0.0f) {
            switch (state->selection) {
            case 0:
                if (!(sMenuLastButtons & 0x10) && (buttons & 0x10)) {
                    gAudioOutputMode++;
                    if (gAudioOutputMode >= 3) {
                        gAudioOutputMode = 0;
                    }
                    changed = 1;
                } else if (!(sMenuLastButtons & 0x20) && (buttons & 0x20)) {
                    gAudioOutputMode--;
                    if (gAudioOutputMode < 0) {
                        gAudioOutputMode = 2;
                    }
                    changed = 1;
                }
                if (changed != 0) {
                    menuSetAudioMode();
                }
                break;
            case 1:
                if (buttons & 0x10) {
                    gSfxVolume++;
                    sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    if (gSfxVolume > 0x28) {
                        gSfxVolume = 0x28;
                    }
                } else if (buttons & 0x20) {
                    gSfxVolume--;
                    sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    if (gSfxVolume < 0) {
                        gSfxVolume = 0;
                    }
                }
                n_alSndpSetGroupVol(0, gSfxVolume * 25000 / 40);
                n_alSndpSetGroupVol(1, gSfxVolume * 25000 / 40);
                n_alSndpSetGroupVol(2, gSfxVolume * 25000 / 40);
                n_alSndpSetGroupVol(3, gSfxVolume * 25000 / 40);
                break;
            case 2:
                if (buttons & 0x10) {
                    gMusicVolume++;
                    if (gMusicVolume > 0x28) {
                        gMusicVolume = 0x28;
                    }
                } else if (buttons & 0x20) {
                    gMusicVolume--;
                    if (gMusicVolume < 0) {
                        gMusicVolume = 0;
                    }
                }
                seqUpdateVolume(0);
                seqUpdateVolume(2);
                break;
            case 3:
                if (buttons & 0x100) {
                    gAudioOutputMode = 0;
                    gSfxVolume = 0x28;
                    gMusicVolume = 0x28;
                    n_alSndpSetGroupVol(0, gSfxVolume * 25000 / 40);
                    n_alSndpSetGroupVol(1, gSfxVolume * 25000 / 40);
                    n_alSndpSetGroupVol(2, gSfxVolume * 25000 / 40);
                    n_alSndpSetGroupVol(3, gSfxVolume * 25000 / 40);
                    seqUpdateVolume(0);
                    seqUpdateVolume(2);
                    changed = 1;
                    menuSetAudioMode();
                }
                break;
            }
            if (buttons & 2) {
                if (eepromGetField(0x1E, 0, 0, 0) != gAudioOutputMode) {
                    eepromSetField(0x1E, 0, 0, 0, gAudioOutputMode);
                    func_8060DEA8();
                }
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->transitionPhase = 0;
                state->nextScreen = 1;
            } else {
                menuHandleScrollInput(state, 4, buttons);
            }
        }
        menuUpdateScrollAnimation(state, 4);
    }
    menuUpdateItemTransition(actor, state, 1);
    if (changed != 0) {
        sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
}

extern s8 gAudioOutputMode;

Gfx *menuFormatOptionValues(Actor *actor, Gfx *dl) {
    MenuScreenState *state;
    u32 selectedOption;
    f32 pad0;
    f32 posX;
    f32 posY;
    f32 scrollOffset;
    s16 pad1;
    s16 y;
    u8 strBuf[12];

    state = actor->customState;
    gGlobalPauseFlags &= ~0x10;
    menuComputeElementPosition(state, 160.0f, 20.0f, &posX, &posY, 2, 0, 1.5f);
    dl = menuDrawScrollSelector(
        textDrawStringVtx(dl, 1, 0x280, posY * 4.0f, sMenuTextTable[0x20], 0x81),
        state,
        sMenuTextTable + 0x21,
        4,
        &selectedOption,
        1,
        &scrollOffset,
        80.0f,
        -1
    );
    D_80033674 = 0x3E8;
    menuComputeElementPosition(state, 160.0f, 150.0f, &posX, &posY, 2, 0, 1.5f);
    y = (s16)(posY * 4.0f);
    posX = (posX - scrollOffset) * 4.0f;

    switch (selectedOption) {
    case 0:
        dl = textDrawStringVtx(dl, 1, posX, y, sMenuTextTable[gAudioOutputMode + 0x25], 0x81);
        break;
    case 1:
    case 2:
        dl = textDrawStringVtx(dl, 1, posX, y, sMenuTextTable[0x28], 0x81);
        _sprintf(strBuf, "%d", ((selectedOption == 1 ? gSfxVolume : gMusicVolume) + 1) >> 1);
        dl = textDrawStringVtx(dl, 1, posX, y + 0x78, strBuf, 0x81);
        break;
    case 3:
        D_80033674 = 0;
        break;
    }

    return dl;
}

extern u8 D_80720D38;

void menuInitSoundOptions(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;

    state->selection = 0;
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0x7D, 0.75f, 2, 4);
    menuSpawnUiElementEffect(state, &D_80720D38, 0xA0, 0xC8, 1.0f, 2, 0xC);
}

extern s8 D_807444C0;
extern s8 D_8074452C;
extern u8 D_80744530;
extern u8 sLanguageIndex;
extern u16 gButtonsPressed;

void menuHandleGameOptionsInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;
    s8 changed = 0;
    s32 i;

    if (state->fade == 0.0f) {
        if (state->scroll == 0.0f) {
            switch (state->selection) {
            case 0:
                if ((buttons & 0x30) && !(sMenuLastButtons & 0x30)) {
                    D_807444C0 = 1 - D_807444C0;
                    changed = 1;
                }
                break;
            case 1:
                if ((buttons & 0x30) && !(sMenuLastButtons & 0x30)) {
                    D_8074452C = 1 - D_8074452C;
                    changed = 1;
                }
                break;
            case 2:
                if (buttons & 0x100) {
                    eepromInitConfigs(0xFF);
                    sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
                break;
            case 3:
                if ((buttons & 0x30) && !(sMenuLastButtons & 0x30)) {
                    D_80744530 = 1 - D_80744530;
                    changed = 1;
                }
                break;
            case 4:
                if ((buttons & 0x10) && !(sMenuLastButtons & 0x10)) {
                    sLanguageIndex += 1;
                    changed = 1;
                }
                if ((buttons & 0x20) && !(sMenuLastButtons & 0x20)) {
                    sLanguageIndex -= 1;
                    changed = 1;
                }
                sLanguageIndex &= 3;
                if (changed != 0) {
                    for (i = 0; i != 0x65; i++) {
                        heapFreeDeferred(sMenuTextTable[i]);
                    }
                    heapFreeDeferred(sMenuTextTable);
                    menuLoadTextTable();
                }
                break;
            }
            if (buttons & 2) {
                eepromSetField(0x1F, 0, 0, 0, sLanguageIndex);
                eepromSetField(0x20, 0, 0, 0, D_80744530);
                func_8060DEA8();
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->transitionPhase = 0;
                state->nextScreen = 1;
            } else {
                menuHandleScrollInput(state, D_800338FC, buttons);
            }
        }
        menuUpdateScrollAnimation(state, D_800338FC);
    }
    menuUpdateItemTransition(actor, state, 1);
    if (gButtonsPressed & 0xC) {
        D_80744544 ^= 0x100;
    }
    if (changed != 0) {
        sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
}


Gfx *menuDrawGameOptions(Actor *actor, Gfx *dl) {
    MenuScreenState *state = actor->customState;
    u32 selectedOption;
    f32 posX;
    f32 posY;
    f32 scrollOffset;
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 pad4;
    s32 pad5;
    s16 y;

    gGlobalPauseFlags &= ~0x10;
    menuComputeElementPosition(state, 160.0f, 20.0f, &posX, &posY, D_800338FC, 0, 1.5f);
    dl = menuDrawScrollSelector(
        textDrawStringVtx(dl, 1, 0x280, posY * 4.0f, sMenuTextTable[0x29], 0x81),
        state,
        sMenuTextTable + 0x2A,
        D_800338FC,
        &selectedOption,
        1,
        &scrollOffset,
        80.0f,
        -1
    );
    D_80033674 = 0x3E8;
    menuComputeElementPosition(state, 160.0f, 150.0f, &posX, &posY, 2, 0, 1.5f);
    y = (s16)(posY * 4.0f);
    posX = (posX - scrollOffset) * 4.0f;

    switch (selectedOption) {
    case 0:
        dl = textDrawStringVtx(dl, 1, posX, y + 0x40, sMenuTextTable[D_807444C0 + 0x2F], 0x81);
        break;
    case 1:
        dl = textDrawStringVtx(dl, 1, posX, y + 0x40, sMenuTextTable[D_8074452C + 0x31], 0x81);
        break;
    case 2:
        D_80033674 = 0;
        break;
    case 3:
        dl = textDrawStringVtx(dl, 1, posX, y + 0x40, sMenuTextTable[D_80744530 + 0x34], 0x81);
        break;
    case 4:
        dl = textDrawStringVtx(dl, 1, posX, y + 0x40, sMenuTextTable[0x33], 0x81);
        break;
    }

    return dl;
}

void menuInitGameOptions(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;

    state->selection = 0;
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0x7D, 0.75f, 2, 4);
    menuSpawnUiElementEffect(state, &D_80720D38, 0xA0, 0xC8, 1.0f, 2, 0xC);
}


extern s8 D_8074453C[];


void menuHandleCheatsInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;
    s8 changed = 0;
    s8 optionCount;
    s8 choice;
    s8 row;
    s8 *pad;

    if (state->fade == 0.0f) {
        if (state->scroll == 0.0f) {
            row = state->selection;
            optionCount = sMenuCheatOptionCounts[row];
            if (optionCount > 0) {
                if ((buttons & 0x10) && !(sMenuLastButtons & 0x10) && optionCount != 1) {
                    changed = 1;
                    do {
                        D_8074453C[row] += 1;
                        if (D_8074453C[row] >= optionCount) {
                            D_8074453C[row] = 0;
                        }
                    } while (!(sMenuCheatOptionMasks[row] & (1 << D_8074453C[row])));
                }
                if ((buttons & 0x20) && !(sMenuLastButtons & 0x20) && optionCount != 1) {
                    do {
                        D_8074453C[row] -= 1;
                        if (D_8074453C[row] < 0) {
                            D_8074453C[row] = optionCount - 1;
                        }
                    } while (!(sMenuCheatOptionMasks[row] & (1 << D_8074453C[row])));
                    changed = 1;
                }
                choice = D_8074453C[row];
                if (buttons & 1) {
                    switch (row) {
                    case 0:
                        if (choice != 0xD) {
                            menuTransitionRequestTypeB(gMenuCheatWarps[choice].map, gMenuCheatWarps[choice].exit);
                        } else {
                            menuTransitionToCreditsOrMap28(1);
                        }
                        gMenuReturnContext = 3;
                        break;
                    case 1:
                        switch (gMenuCheatMapCharacters[choice].map) {
                        case 0xBF:
                            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                            state->transitionPhase = 0;
                            state->nextScreen = 0xC;
                            gMenuHighScoreGame = 0;
                            break;
                        case 0xB8:
                            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                            state->transitionPhase = 0;
                            state->nextScreen = 0xC;
                            gMenuHighScoreGame = 1;
                            break;
                        default:
                            menuSetupPlayerInventory(gMenuCheatMapCharacters[choice].map, 0, gMenuCheatMapCharacters[choice].characterId, 3, 3, 1, 3);
                            gMenuReturnContext = 5;
                            break;
                        }
                        break;
                    case 2:
                        menuSetupPlayerInventory(gMenuCheatLoadouts[choice].map, 0, gMenuCheatLoadouts[choice].characterId, gMenuCheatLoadouts[choice].inventory0, gMenuCheatLoadouts[choice].inventory1, gMenuCheatLoadouts[choice].inventory4, gMenuCheatLoadouts[choice].shared);
                        gMenuReturnContext = 4;
                        break;
                    }
                }
                if (buttons & 0x100) {
                    if (row == 3) {
                        D_80744544 ^= 1;
                        changed = 1;
                    } else if (row == 4) {
                        changed = 1;
                        D_80744544 ^= 1 << (choice + 1);
                        if (choice == 6) {
                            if (D_80744544 & (1 << (choice + 1))) {
                                D_80744544 |= 0xFEFE;
                            } else {
                                D_80744544 &= 1;
                            }
                        }
                    }
                }
            }
            if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->transitionPhase = 0;
                state->nextScreen = 1;
                D_80033698 = 3;
            } else {
                menuHandleScrollInput(state, 5, buttons);
            }
        }
        menuUpdateScrollAnimation(state, 5);
    }
    menuUpdateItemTransition(actor, state, 1);
    if (changed != 0) {
        sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
}


Gfx *menuDrawCheats(Actor *actor, Gfx *dl) {
    MenuScreenState *state = actor->customState;
    u32 row;
    f32 posX;
    f32 posY;
    f32 scrollOffset;
    s16 cheat;
    s16 y;
    u8 strBuf[0xC8];

    gGlobalPauseFlags &= ~0x10;
    menuComputeElementPosition(state, 160.0f, 20.0f, &posX, &posY, 2, 0, 1.5f);
    y = (s16)(posY * 4.0f);
    dl = menuDrawScrollSelector(
        textDrawStringVtx(dl, 1, 0x280, y, sMenuTextTable[0x36], 0x81),
        state,
        sMenuTextTable + 0x37,
        5,
        &row,
        1,
        &scrollOffset,
        140.0f,
        sMenuCheatRowMask
    );
    _sprintf(strBuf, "%d", D_80033990[row]);
    dl = textDrawStringVtx(dl, 3, 0x2A8, y + 0xC8, strBuf, 1);
    D_80033674 = 0x3E8;
    menuComputeElementPosition(state, 160.0f, 160.0f, &posX, &posY, 1, 0, 1.5f);
    y = (s16)(posY * 4.0f);
    posX = (posX - scrollOffset) * 4.0f;

    if (sMenuCheatOptionCounts[row] > 0) {
        switch (row) {
        case 0:
            dl = textDrawStringVtx(dl, 1, posX, y + 0x40, sMenuTextTable[D_8074453C[0] + 0x3C], 0x81);
            break;
        case 1:
            dl = textDrawStringVtx(dl, 1, posX, y + 0x40, sMenuTextTable[D_8074453C[1] + 0x52], 0x81);
            break;
        case 2:
            dl = textDrawStringVtx(dl, 1, posX, y + 0x40, sMenuTextTable[D_8074453C[2] + 0x4A], 0x81);
            break;
        case 3:
            _sprintf(strBuf, "%s:%s", sMenuTextTable[0x5E], sMenuTextTable[(D_80744544 & 1) + 0x31]);
            dl = textDrawStringVtx(dl, 1, posX, y + 0x40, strBuf, 0x81);
            break;
        case 4:
            cheat = D_8074453C[4];
            _sprintf(strBuf, "%s:%s", sMenuTextTable[cheat + 0x56], sMenuTextTable[(((1 << (cheat + 1)) & D_80744544) != 0) + 0x31]);
            dl = textDrawStringVtx(dl, 1, posX, y + 0x40, strBuf, 0x81);
            break;
        }
    } else {
        dl = textDrawStringVtx(dl, 1, posX, y + 0x40, (u8 *)"???", 0x81);
    }
    return dl;
}


void menuInitCheats(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    s32 flagId;
    s32 i;
    s8 optionCount;

    state->selection = gMenuScreenSelection[10];
    switch (gMenuReturnContext) {
    case 0:
        break;
    default:
        state->selection = 0;
        break;
    case 4:
        state->selection = 2;
        break;
    case 5:
        state->selection = 1;
        break;
    }
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0x78, 0.75f, 2, 4);
    menuSpawnUiElementEffect(state, &D_80721094, 0x78, 0x50, 1.25f, 2, 0xE);
    menuSpawnUiElementEffect(state, &D_80720D38, 0x11D, 0xD2, 0.75f, 2, 0x11);
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x11D, 0xD2, 0.75f, 2, 0x10);
    sMenuCheatOptionCounts[0] = 0xE;
    sMenuCheatOptionCounts[1] = 4;
    sMenuCheatOptionCounts[2] = 8;
    sMenuCheatOptionCounts[3] = 1;
    sMenuCheatOptionCounts[4] = 7;
    sMenuCheatOptionMasks[0] = -1;
    sMenuCheatOptionMasks[1] = -1;
    sMenuCheatOptionMasks[2] = -1;
    sMenuCheatOptionMasks[3] = -1;
    sMenuCheatOptionMasks[4] = -1;
    sMenuCheatRowMask = 0;
    if (flagGet(1, 1) != 0) {
        sMenuCheatRowMask |= 1;
        sMenuCheatOptionMasks[0] = 3;
        i = 4;
        flagId = 2;
        do {
            if (flagGet(flagId, 1) != 0) {
                sMenuCheatOptionMasks[0] |= i;
            }
            i *= 2;
            flagId += 1;
        } while (flagId != 0xE);
    } else {
        sMenuCheatOptionCounts[0] = 0;
    }
    if (flagGet(0xE, 1) != 0) {
        flagId = 0xF;
        sMenuCheatRowMask |= 2;
        sMenuCheatOptionMasks[1] = 0;
        i = 1;
        do {
            if (flagGet(flagId, 1) != 0) {
                sMenuCheatOptionMasks[1] |= i;
            }
            i *= 2;
            flagId += 1;
        } while (flagId != 0x13);
    } else {
        sMenuCheatOptionCounts[1] = 0;
    }
    if (flagGet(0x13, 1) != 0) {
        flagId = 0x14;
        sMenuCheatRowMask |= 4;
        sMenuCheatOptionMasks[2] = 0;
        i = 1;
        do {
            if (flagGet(flagId, 1) != 0) {
                sMenuCheatOptionMasks[2] |= i;
            }
            i *= 2;
            flagId += 1;
        } while (flagId != 0x1C);
    } else {
        sMenuCheatOptionCounts[2] = 0;
    }
    if (flagGet(0x21, 1) == 0) {
        sMenuCheatOptionCounts[3] = 0;
    } else {
        sMenuCheatRowMask |= 8;
    }
    if (flagGet(0x22, 1) == 0) {
        sMenuCheatOptionCounts[4] = 0;
    } else {
        sMenuCheatRowMask |= 0x10;
    }
    for (i = 0; i != 5; i++) {
        optionCount = sMenuCheatOptionCounts[i];
        if (optionCount > 0) {
            s16 enabledMask = sMenuCheatOptionMasks[i];
            if (!((1 << D_8074453C[i]) & enabledMask)) {
                do {
                    D_8074453C[i] += 1;
                    if (D_8074453C[i] >= optionCount) {
                        sMenuCheatOptionCounts[i] = 0;
                        D_8074453C[i] = 0;
                        optionCount = sMenuCheatOptionCounts[i];
                    }
                } while (optionCount > 0 && !((1 << D_8074453C[i]) & enabledMask));
            }
        }
    }
}

extern MenuHighScoreEntry D_80744548[];
extern MenuHighScoreEntry D_80744568[];


void menuLoadHighScores(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        D_80744548[i].score = eepromGetField(0x19, 0, i, 0);
        D_80744548[i].initials[0] = eepromGetField(0x16, 0, i, 0);
        D_80744548[i].initials[1] = eepromGetField(0x17, 0, i, 0);
        D_80744548[i].initials[2] = eepromGetField(0x18, 0, i, 0);
        D_80744548[i].initials[3] = 0;
        D_80744568[i].score = eepromGetField(0x1D, 0, i, 0);
        D_80744568[i].initials[0] = eepromGetField(0x1A, 0, i, 0);
        D_80744568[i].initials[1] = eepromGetField(0x1B, 0, i, 0);
        D_80744568[i].initials[2] = eepromGetField(0x1C, 0, i, 0);
        D_80744568[i].initials[3] = 0;
    }
}

void menuSaveHighScores(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        eepromSetField(0x19, 0, i, 0, D_80744548[i].score);
        eepromSetField(0x16, 0, i, 0, D_80744548[i].initials[0]);
        eepromSetField(0x17, 0, i, 0, D_80744548[i].initials[1]);
        eepromSetField(0x18, 0, i, 0, D_80744548[i].initials[2]);
        eepromSetField(0x1D, 0, i, 0, D_80744568[i].score);
        eepromSetField(0x1A, 0, i, 0, D_80744568[i].initials[0]);
        eepromSetField(0x1B, 0, i, 0, D_80744568[i].initials[1]);
        eepromSetField(0x1C, 0, i, 0, D_80744568[i].initials[2]);
    }
    func_8060DEA8();
}

extern s8 sMenuHighScoreEditRow;
extern s8 sMenuHighScoreEditChar;

void menuHandleHighScoreNameEntryInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;
    s8 holdFrames;
    MenuHighScoreEntry *table;
    u32 pressed;
    u8 *p;

    if (gMenuHighScoreGame == 0) {
        table = D_80744548;
    } else {
        table = D_80744568;
    }
    if (state->fade == 0.0f) {
        s8 row = sMenuHighScoreEditRow;
        if (row < 0) {
            if (buttons & 1) {
                menuSetupPlayerInventory(gMenuHighScoreGames[gMenuHighScoreGame].map, 0, gMenuHighScoreGames[gMenuHighScoreGame].characterId, 3, 3, 1, 3);
                gMenuReturnContext = gMenuHighScoreGame + 6;
            }
            if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->transitionPhase = 0;
                state->nextScreen = 0xA;
            }
        } else {
            if (buttons & 0xC) {
                holdFrames = sMenuHighScoreHoldFrames + 1;
            } else {
                holdFrames = 0;
            }
            pressed = 0;
            if (holdFrames == 1 || (sMenuHighScoreHoldFrames = holdFrames, holdFrames >= 0x10)) { // ORIG: the target stores the counter on the holdFrames != 1 path before the 0x10 test (sb v1 at 0x7290, slti at,v1,16 at 0x7294) and again at the block head (sb v1 at 0x72a0); (sMenuHighScoreHoldFrames = holdFrames) >= 0x10 reloads the byte for the test
                if (sMenuHighScoreEditChar) {} // FAKE: same-value dead read splits the block head: the store below stays a direct sb (sMenuHighScoreHoldFrames address uncoloured), the column address is hoisted to a1 (0x7264) and the column value takes v0 ahead of holdFrames (v1); if (1) here gives the shape but rotates every register
                sMenuHighScoreHoldFrames = holdFrames;
                pressed = buttons;
                if (holdFrames >= 0x10) {
                    holdFrames = 0xF;
                    if (row == 0xF) {} // FAKE: splits the block before the 15 store so it stays a direct sb (sMenuHighScoreHoldFrames address uncoloured, else sb t8,0(a3)); with the next test, constant 15 gets v1 (li v1,15 at 0x72b8)
                    sMenuHighScoreHoldFrames = holdFrames;
                    if (row == 0xF) {} // FAKE: second compare of the constant-15 pair
                    if (!(gFrameCounter & 1)) {
                        pressed = 0;
                    }
                }
            }
            p = &table[row].initials[sMenuHighScoreEditChar];
            if (pressed & 4) {
                switch (*p) {
                case 0x20:
                    *p = 0x2E;
                    break;
                case 0x2E:
                    *p = 0x5A;
                    break;
                case 0x41:
                    *p = 0x20;
                    break;
                default:
                    *p = *p - 1;
                    break;
                }
            } else if (pressed & 8) {
                switch (*p) {
                case 0x20:
                    *p = 0x41;
                    break;
                case 0x2E:
                    *p = 0x20;
                    break;
                case 0x5A:
                    *p = 0x2E;
                    break;
                default:
                    *p = *p + 1;
                    break;
                }
            }
            if (buttons & 1) {
                sMenuHighScoreEditChar += 1;
                if (sMenuHighScoreEditChar == 3) {
                    sMenuHighScoreEditRow = -1;
                    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
                    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
                    menuSaveHighScores();
                }
            } else if ((buttons & 2) && sMenuHighScoreEditChar > 0) {
                sMenuHighScoreEditChar -= 1;
            }
        }
    }
    menuUpdateItemTransition(actor, state, 1);
}

const u8 D_80033BE0[4] = "-";
const u8 D_80033BE4[4] = "  -";
const u8 D_80033BE8[8] = "    -";

extern s8 sMenuHighScoreEditRow;
extern s8 sMenuHighScoreEditChar;
extern s16 D_80744518;

Gfx *menuDrawHighScoreTable(Actor *actor, Gfx *dl) {
    MenuScreenState *state;
    f32 posX;
    f32 posY;
    s32 xBase;
    s32 pad;
    MenuHighScoreEntry *scoreTable;
    u8 strBuf[0xC8];
    s16 yPos;
    s16 i;

    state = actor->customState;
    gGlobalPauseFlags &= ~0x10;
    menuComputeElementPosition(state, 160.0f, 20.0f, &posX, &posY, 2, 0, 1.0f);
    dl = textDrawStringVtx(dl, 1, 0x280, posY * 4.0, sMenuTextTable[gMenuHighScoreGame + 0x5F], 0x81);
    menuComputeElementPosition(state, 160.0f, 205.0f, &posX, &posY, 2, 0, 1.0f);
    i = 0; // FAKE: loop counter i doubles as the message-drawn flag; a separate flag local recolours
    yPos = (s16)(posY * 4.0);
    if (sMenuHighScoreEditRow >= 0) {
        _sprintf(strBuf, "%s", sMenuTextTable[0x63]);
        i = 1;
    } else if (sMenuHighScoreEditRow == -2) {
        _sprintf(strBuf, "%s %d.", sMenuTextTable[0x64], D_80744518);
        i = 1;
    }
    if (i != 0) {
        dl = hudDrawScaledText(dl, 0x280, yPos, 0.6f, strBuf);
    }
    menuComputeElementPosition(state, 20.0f, 120.0f, &posX, &posY, 2, 0, 2.0f);
    yPos = 0xC8;
    xBase = (s16)(posX * 4.0f);
    if (gMenuHighScoreGame == 0) {
        scoreTable = D_80744548;
    } else {
        scoreTable = D_80744568;
    }
    for (i = 0; i < 5; i++) {
        _sprintf(strBuf, "%d.", i + 1);
        dl = textDrawStringVtx(dl, 1, xBase + 0x50, yPos, strBuf, 1);
        _sprintf(strBuf, "%c %c %c", scoreTable[i].initials[0], scoreTable[i].initials[1], scoreTable[i].initials[2]);
        dl = textDrawStringVtx(dl, 0x81, xBase + 0x118, yPos, strBuf, 1);
        _sprintf(strBuf, "%d", scoreTable[i].score);
        dl = textDrawStringVtx(dl, 0x81, 0x3E8 - xBase, yPos, strBuf, 1);
        if (i == sMenuHighScoreEditRow && (gFrameCounter & 0x1F) < 0x14) {
            dl = textDrawStringVtx(dl, 0x81, xBase + 0x118, yPos + 0x34, D_800339AC[sMenuHighScoreEditChar], 1);
        }
        yPos += 0x6C;
    }
    return dl;
}

extern s8 sMenuHighScoreEditRow;

void menuInitHighScores(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;

    if (sMenuHighScoreEditRow == -1) {
        menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
        menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    }
}

extern s8 sMenuHighScoreEditChar;
extern s16 D_80744518;

void menuInsertHighScore(void) {
    MenuHighScoreEntry *table;
    s32 i;
    s32 j;

    if (gMenuHighScoreGame == 0) {
        table = D_80744548;
    } else {
        table = D_80744568;
    }

    for (i = 0; i < 5; i++) {
        if (D_80744518 >= table[i].score) {
            j = 4;
            if (i < 4) {
                do {
                    table[j].score = table[j - 1].score;
                    table[j].initials[0] = table[j - 1].initials[0];
                    table[j].initials[1] = table[j - 1].initials[1];
                    table[j].initials[2] = table[j - 1].initials[2];
                    j--;
                } while (j > i);
            }
            table[i].score = D_80744518;
            table[i].initials[0] = 0x2E;
            table[i].initials[1] = 0x2E;
            table[i].initials[2] = 0x2E;
            sMenuHighScoreEditRow = i;
            sMenuHighScoreEditChar = 0;
            return;
        }
    }
    sMenuHighScoreEditRow = -1;
}


extern PlayerStruct *gPlayerSlots;

void menuUpdateCameraPositions(void) {
    gPlayerSlots->camX = gPrimaryPlayerActor->x;
    gPlayerSlots->camY = gPrimaryPlayerActor->y + 13.1f;
    gPlayerSlots->camZ = gPrimaryPlayerActor->z - 50.0f;
    gPlayerSlots->focusX = gPrimaryPlayerActor->x;
    gPlayerSlots->focusY = gPlayerSlots->camY;
    gPlayerSlots->focusZ = gPrimaryPlayerActor->z - 100.0f;
}

extern f32 D_80033F44;

Gfx *menuDrawScrollSelector(Gfx *dl, MenuScreenState *state, u8 **strTable, s32 itemCount, u32 *outIdx, s16 textFlag, f32 *outOffset, f32 posY, s16 enabledMask) {
    s32 idx = state->selection;
    f32 offset;
    f32 posX;
    f32 itemY;
    s16 y;

    if (state->scroll != 0.0f) {
        if (state->scroll > 0.5f) {
            idx++;
        }
        if (idx >= itemCount) {
            idx = 0;
        }
    }
    offset = state->scroll - 0.5f;
    if (offset < 0.0f) {
        offset = -offset;
    }
    offset = 0.5f - offset;
    offset *= 800.0f;
    if (D_80033F44 < 0.0f) {
        offset = -offset;
    }
    menuComputeElementPosition(state, offset + 160.0, posY, &posX, &itemY, 2, 0, 2.0f);
    y = (s16)(itemY * 4.0f);
    if (enabledMask & (1 << idx)) {
        dl = textDrawStringVtx(dl, textFlag, posX * 4.0f, y, strTable[idx], 0x81);
    } else {
        dl = textDrawStringVtx(dl, textFlag, posX * 4.0f, y, D_800339C4, 0x81);
    }
    *outOffset = offset;
    *outIdx = idx;
    return dl;
}

extern f32 sMenuElementX[];
extern f32 sMenuElementY[];
extern f32 sMenuElementScale[];

Gfx *menuSetElementCoordinates(Gfx *dl, s32 elemIdx, f32 posX, f32 posY, f32 scale) {
    elemIdx &= 0x7F;
    posX *= 4.0f;
    posY *= 4.0f;
    sMenuElementX[elemIdx] = posX - 32.0;
    sMenuElementY[elemIdx] = posY - 100.0;
    sMenuElementScale[elemIdx] = scale * 1.333;
    return dl;
}

extern s8 D_80033F50;

void menuUpdateItemTransition(void *actor, MenuScreenState *state, s32 hasSfx) {
    if (!state->transitionPhase) {
        state->fade += 0.13f;
        if (state->fade > 1.3f) {
            state->fade = 1.0f;
            state->screen = state->nextScreen;
            state->transitionPhase = -1;
            menuUpdateStateDispatch(actor, 0, 0, 0);
            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        }
    } else {
        if (state->fade > 0.0f) {
            state->fade -= 0.2f;
            if (state->fade < 0.0f) {
                state->fade = 0.0f;
                if (hasSfx != 0) {
                    sfxPlayOnFreeSlot(0x3C, 0x61A8, 63.0f, 1.0f, 0, 0);
                    D_80033F50 = 3;
                }
            }
        }
    }
}



void menuHandleScrollInput(MenuScreenState *state, s32 itemCount, s32 buttons) {
    if (buttons & 4) {
        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        D_80033F44 = -0.1f;
        state->selection--;
        state->scroll = 1.0f;
        if (state->selection < 0) {
            state->selection += itemCount;
        }
        D_800337F0 = 0;
    } else if (buttons & 8) {
        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        D_80033F44 = 0.1f;
        D_800337F0 = 0;
    }
}


void menuUpdateScrollAnimation(MenuScreenState *state, s32 itemCount) {
    if (D_80033F44 > 0.0f) {
        state->scroll += D_80033F44;
        if (state->scroll >= 1.0f) {
            state->scroll = 0.0f;
            state->selection++;
            if (state->selection >= itemCount) {
                state->selection -= itemCount;
            }
            D_80033F44 = 0.0f;
        }
    } else if (D_80033F44 < 0.0f) {
        state->scroll += D_80033F44;
        if (state->scroll <= 0.0f) {
            D_80033F44 = 0.0f;
            state->scroll = 0.0f;
        }
    }
}

typedef struct MenuKioskState { // customState of the menu kiosk actors (gPrimaryPlayerActor and the kiosk pod)
    f32 homeX;
    f32 homeY;
    f32 homeZ;
    char padC[0x23C - 0xC];
    u16 phaseFrames;
} MenuKioskState;

extern void *D_80033F34;
extern s8 D_80033F30;

void menuInit(void) {
    MenuScreenState *state = gCurrentActor->customState;
    MenuKioskState *kioskState = gPrimaryPlayerActor->customState;
    s32 i;

    if (!(gCurrentActor->flags & 0x10)) {
        gGlobalPauseFlags |= 0x10;
        menuLoadTextTable();
        menuLoadHighScores();
        if (gMenuReturnContext == 0) {
            i = 0;
            do {
                gMenuScreenSelection[i] = 0;
                i++;
            } while (i < 13);
        } else {
            gPrimaryPlayerActor->x = 700.0f;
            gPrimaryPlayerActor->y = 0.0f;
            gPrimaryPlayerActor->z = 70.0f;
        }
        D_80033F50 = 0;
        D_80033738 = 0;
        sMenuHighScoreEditRow = -1;
        D_8003369C = 0.0f;
        actorSpawn(0x14D, 0xD7);
        gSpawnedActor->x = gPrimaryPlayerActor->x;
        gSpawnedActor->y = gPrimaryPlayerActor->y;
        gSpawnedActor->z = gPrimaryPlayerActor->z;
        gSpawnedActor->yaw = gPrimaryPlayerActor->yaw;
        if (gMenuReturnContext != 0) {
            D_80033738 = 0x15;
            gPrimaryPlayerActor->state = 0x85;
            gPrimaryPlayerActor->unk155 = 0;
            actorScriptStart(gPrimaryPlayerActor, 0x347);
            gPrimaryPlayerActor->unk155 = 6;
            func_8061B650(gCamActor);
            D_80033F3C = 1.0f;
            kioskState->phaseFrames = 0x50;
        }
        switch (gMenuReturnContext) {
        case 1:
            state->screen = 1;
            break;
        case 2:
            state->screen = 0xB;
            break;
        case 3:
        case 4:
        case 5:
            state->screen = 0xA;
            break;
        case 6:
        case 7:
            state->screen = 0xC;
            gMenuHighScoreGame = gMenuReturnContext - 6;
            menuInsertHighScore();
            break;
        default:
            actorScriptStart(gSpawnedActor, 0x349);
            gPrimaryPlayerActor->state = 0x86;
            gPrimaryPlayerActor->unk155 = 0;
            state->screen = 0;
            break;
        }
        gPrimaryPlayerActor->sub4->scaleX *= 0.8;
        gPrimaryPlayerActor->sub4->scaleY *= 0.8;
        gPrimaryPlayerActor->sub4->scaleZ *= 0.8;
        state->selection = 0;
        state->scrollY = 0;
        state->scrollTargetY = 0;
        state->transitionPhase = 1;
        state->unk10 = 0;
        state->fade = 1.0f;
        state->scroll = 0.0f;
        D_80033F34 = heapAlloc(0x80);
        D_80033F30 = 0;
        menuUpdateStateDispatch(gCurrentActor, 0, 0, 0);
        gMenuReturnContext = 0;
        controllerSetActiveMask(0xFF);
        func_8060CB9C();
    }
    menuUpdateStateDispatch(gCurrentActor, 2, 0, 0);
    renderCallbacksRegister(menuInitGfxState, gCurrentActor, 3);
}

static void func_8003026C(void) {
}

extern Gfx D_1000118;
extern Mtx D_20000C0;


void menuInitGfxState(Gfx *glistp, Actor *menuActor) {
    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_1000118);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetRenderMode(glistp++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 255);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    menuUpdateStateDispatch(menuActor, 1, glistp, 0);
}


extern OSContPad *gCurrentContPad;

Gfx *menuUpdateStateDispatch(Actor *actor, s32 opMode, Gfx *dl, s32 subArg) {
    MenuScreenState *state = actor->customState;
    s32 buttons = 0;

    if (*gPlayerSlots->heldButtonsPtr & 0x8000) {
        buttons = 1;
    }
    if (*gPlayerSlots->heldButtonsPtr & 0x4000) {
        buttons |= 2;
    }
    if (*gPlayerSlots->heldButtonsPtr & 8) {
        buttons |= 0x40;
    }
    if (*gPlayerSlots->heldButtonsPtr & 4) {
        buttons |= 0x80;
    }
    if (*gPlayerSlots->heldButtonsPtr & 0x2000) {
        buttons |= 0x100;
    }
    if (gCurrentContPad->stick_x < -0x28) {
        buttons |= 4;
    } else if (gCurrentContPad->stick_x >= 0x29) {
        buttons |= 8;
    }
    if (gCurrentContPad->stick_y < -0x28) {
        buttons |= 0x20;
    } else if (gCurrentContPad->stick_y >= 0x29) {
        buttons |= 0x10;
    }
    switch (opMode) {
    case 0:
        D_80033F38 = 1;
        D_80033F44 = 0.0f;
        D_80033F40 = 0.0f;
        D_80033F3C = 0.0f;
        gGlobalPauseFlags &= 0xFFFEFFFF;
        state->scrollY = 0;
        state->scrollTargetY = 0;
        D_800337F8 = 1;
        break;
    case 1:
        break;
    case 2:
        gMenuScreenSelection[state->screen] = state->selection;
        lightSetColor(1.0f, 1.0f, 1.0f, 0);
        break;
    }
    switch (state->screen) {
    case 0:
        if (opMode == 1) {
            return menuTitleScreenDraw(actor, dl);
        }
        if (opMode == 2) {
            menuTitleScreenHandleInput(actor, buttons);
        } else {
            menuResetCameraAndFlags(actor, subArg);
        }
        break;
    case 1:
        if (opMode == 1) {
            return menuDrawMainScreenTitle(actor, dl);
        }
        if (opMode == 2) {
            menuUpdateMainScreen(actor, buttons);
        } else {
            menuInitMainScreen(actor, subArg);
        }
        break;
    case 2:
        if (opMode == 1) {
            return menuDrawAdventureFileSelectTitle(actor, dl);
        }
        if (opMode == 2) {
            menuHandleSelectionInput(actor, buttons);
        } else {
            menuInitAdventureFileSelect(actor, subArg);
        }
        break;
    case 3:
        if (opMode == 1) {
            return menuDrawFileSummary(actor, dl);
        }
        if (opMode == 2) {
            menuHandleConfirmationInput(actor, buttons);
        } else {
            menuInitFileSummary(actor, subArg);
        }
        break;
    case 4:
        if (opMode == 1) {
            return menuDrawFileSlotLabel(actor, dl);
        }
        if (opMode == 2) {
            menuHandleFileSelectInput(actor, buttons);
        } else {
            menuInitFileSelect(actor, subArg);
        }
        break;
    case 5:
        if (opMode == 1) {
            return menuMysteryDrawFileSlotLabel(actor, dl);
        }
        if (opMode == 2) {
            menuMysteryHandleInput(actor, buttons);
        } else {
            menuMysteryInit(actor, subArg);
        }
        break;
    case 6:
        if (opMode == 1) {
            return menuDrawSubmenuRing(actor, dl);
        }
        if (opMode == 2) {
            menuBossReplayHandleInput(actor, buttons);
        } else {
            menuInitControllerSlots(actor, subArg);
        }
        break;
    case 7:
        if (opMode == 1) {
            return menuDrawCharacterSelect(actor, dl);
        }
        if (opMode == 2) {
            menuHandleControllerSlotInput(actor, buttons);
        } else {
            menuInitCharacterSelect(actor, subArg);
        }
        break;
    case 11:
        if (opMode == 1) {
            return menuDrawMultiplayerResults(actor, dl);
        }
        if (opMode == 2) {
            menuMultiplayerResultsHandleInput(actor, buttons);
        } else {
            menuInitMultiplayerResults(actor, subArg);
        }
        break;
    case 8:
        if (opMode == 1) {
            return menuFormatOptionValues(actor, dl);
        }
        if (opMode == 2) {
            menuHandleSoundOptionsInput(actor, buttons);
        } else {
            menuInitSoundOptions(actor, subArg);
        }
        break;
    case 9:
        if (opMode == 1) {
            return menuDrawGameOptions(actor, dl);
        }
        if (opMode == 2) {
            menuHandleGameOptionsInput(actor, buttons);
        } else {
            menuInitGameOptions(actor, subArg);
        }
        break;
    case 10:
        if (opMode == 1) {
            return menuDrawCheats(actor, dl);
        }
        if (opMode == 2) {
            menuHandleCheatsInput(actor, buttons);
        } else {
            menuInitCheats(actor, subArg);
        }
        break;
    case 12:
        if (opMode == 1) {
            return menuDrawHighScoreTable(actor, dl);
        }
        if (opMode == 2) {
            menuHandleHighScoreNameEntryInput(actor, buttons);
        } else {
            menuInitHighScores(actor, subArg);
        }
        break;
    }
    if (D_80033F50 > 0) {
        D_80033F50--;
    }
    sMenuLastButtons = buttons;
    return dl;
}

f32 sqrtf(f32);

void menuSpawnUiElementEffect(MenuScreenState *state, void *assetPtr, s32 posX, s32 posY, f32 elemScale, s32 flags, s32 fxType) {
    EffectNode *fx;
    MenuEffectTarget *target;
    f32 dx;
    f32 dy;
    f32 dist;
    f32 scale;

    effectSetFrameDelay(flags);
    effectEnableFade();
    effectSetDuration(-1);
    effectSetSpeed((s32)state);
    effectSetCallback(menuUpdateElementTargetAndColor);
    effectSetFlags(1);
    fx = effectCreateAtPosition(assetPtr, elemScale, posX, posY, -10.0f);
    target = heapAlloc(0x28);
    fx->allocation = target;
    target->kind = fxType;
    target->offsetIndex = state->offsetIndex;
    target->spawnX = fx->x;
    target->spawnY = fx->y;
    switch (fxType) {
    case 14:
        fx->scaleX = -fx->scaleX; // mirrored, then slides in like the cases below
    case 0:
    case 1:
    case 11:
    case 12:
    case 13:
    case 16:
    case 17:
    case 19:
        dx = 640.0f - target->spawnX;
        dy = 480.0f - target->spawnY;
        dist = sqrtf((dx * dx) + (dy * dy));
        scale = 1040.0f - dist;
        target->slideXOrScale = -(dx / dist) * scale;
        target->slideY = -(dy / dist) * scale;
        target->spawnScaleX = fx->scaleX;
        break;
    case 2:
    case 3:
    case 10:
        target->spawnX = posX;
        target->slideXOrScale = elemScale;
        target->slideY = 0.0f;
        break;
    case 15:
        target->spawnX = posX;
        break;
    default:
        target->slideXOrScale = elemScale;
        target->slideY = 0.0f;
        break;
    }
    if (D_80033F38 == 0) {
        fx->red = 0x80;
        fx->green = 0x80;
        fx->blue = 0x80;
    }
    D_80033F38 = 1;
}

typedef struct MenuSparkleState { // heapAlloc'd allocation of a menuSparkleParticleUpdate effect
    f32 vx;
    f32 vy;
    f32 ang;
    f32 dir;
} MenuSparkleState;

extern u8 gGfxBufferIndex;

void menuSparkleParticleUpdate(EffectNode *spinner, s32 unused) {
    MenuSparkleState *sparkle;
    s16 randAngle;
    f32 rotMatrix[4][4];
    if (spinner->allocation == NULL) {
        sparkle = spinner->allocation = heapAlloc(sizeof(MenuSparkleState));
        randAngle = randomLcgNext() * 0x10;
        sparkle->vx = mathSinF(randAngle) * 60.0f;
        sparkle->vy = mathCosF(randAngle) * 60.0f;
        sparkle->ang = randomFloat() * 3.141f;
        spinner->x = spinner->x + sparkle->vx * 3.0f;
        spinner->y = spinner->y + sparkle->vy * 3.0f;
        if (sparkle->vx > 0) {
            sparkle->dir = 0.3f;
        } else {
            sparkle->dir = -0.3f;
        }
    }
    sparkle = spinner->allocation;
    spinner->x = spinner->x + sparkle->vx;
    spinner->y = spinner->y + sparkle->vy;
    sparkle->ang = sparkle->ang + sparkle->dir;
    guRotateF(rotMatrix, sparkle->ang, 0.0f, 0.0f, 1.0f);
    guMtxF2L(rotMatrix, &spinner->matrices[0][gGfxBufferIndex]);
}


void menuUpdateElementTargetAndColor(EffectNode *elemActor, u8 *outFlag) {
    MenuScreenState *state = elemActor->data;
    MenuEffectTarget *target;
    f32 progress;
    f32 radius;
    f32 stepOrScale;
    s32 offsetY;
    s32 type;
    s32 t;
    s32 idx;
    s32 slot;
    s32 splineStep;
    s16 colorComponent;
    s16 alphaVal;

    if (elemActor->allocation != NULL) {
        target = elemActor->allocation;
        progress = state->fade;
        offsetY = (s32)((&state->scrollY)[(s32)target->offsetIndex] * 4.0);
        type = (s32)target->kind;

        switch (type) {
        case 6:
        case 7:
        case 18: {
            idx = (s32)target->spawnX >> 2;
            slot = menuEvaluateSelectorSpline(state, idx, &elemActor->x, &elemActor->y, &stepOrScale, &colorComponent, &alphaVal);
            elemActor->scaleX = target->slideXOrScale * stepOrScale * 4.0f;
            elemActor->scaleY = elemActor->scaleX;
            if (type == 7) {
                t = (gFrameCounter * 0x78) & 0xFFF;
                radius = mathSinF(t); // FAKE: radius holds the sine: the compound += mathSinF(t) takes a cfe hidden temp word (Q0487) that the case-15 color pointer needs (frame 120, spill temps sp+52/sp+60); ACDC0 hudPauseMenuIconUpdate routes its wobble sine through its radius local sc the same way
                elemActor->y += radius * 10.0f;
            }
            if (type == 0x12) {
                elemActor->red = colorComponent;
                elemActor->green = colorComponent;
                elemActor->blue = colorComponent;
                elemActor->alpha = alphaVal;
                elemActor->minX = gPlayerSlots->rect[0];
                elemActor->maxX = gPlayerSlots->rect[2];
                if (elemActor->y < 360.0) {
                    if ((f64)elemActor->x < 640) {
                        elemActor->maxX = 0x78;
                    } else {
                        elemActor->minX = 0xC8;
                    }
                }
                if (D_80033F3C != 0.0 && slot == 0) {
                    elemActor->maxX = 0;
                }
            }
            break;
        }
        case 4:
        case 5:
        case 8:
            progress = 1.0 - state->fade;
            if (progress < 0.0f) {
                progress = 0.0f;
            }
            if (progress > 1.0f) {
                progress = 1.0f;
            }
            elemActor->alpha = (s32)(progress * 255.0f);
            if (type == 4) {
                elemActor->scaleX = target->slideXOrScale * progress * 4.0;
                elemActor->scaleY = elemActor->scaleX;
            }
            progress = 0;
            elemActor->y = target->spawnY + (f32)offsetY;
            if (type == 8) {
                D_80033FAC = 0;
                t = gCurrentContPad->stick_x;
                if (t >= 0xB) {
                    elemActor->x += (f32)t;
                    if (elemActor->x > 960.0f) {
                        elemActor->x = 960.0f;
                        D_80033FAC = 1;
                    }
                } else if (t < -0xA) {
                    elemActor->x += (f32)t;
                    if (elemActor->x < 320.0f) {
                        elemActor->x = 320.0f;
                        D_80033FAC = 1;
                    }
                } else {
                    elemActor->x = (elemActor->x - 640.0) * 0.9 + 640.0;
                }
            } else {
                elemActor->x = target->spawnX;
            }
            break;
        case 0:
        case 1:
        case 9:
        case 11:
        case 12:
        case 13:
        case 14:
        case 16:
        case 17:
        case 19:
            if (type != 0 && type != 0xB && type != 0x13 && type != 0xD && type != 0xE) {
                progress *= 0.5f;
                progress += state->scroll;
                progress = 2.0f * progress - 1.0f;
                if (progress < 0.0f) {
                    progress = -progress;
                }
                progress = 1.0f - progress;
                if (progress < 0.0f) {
                    progress = 0.0f;
                }
            }
            elemActor->x = target->slideXOrScale * progress + target->spawnX;
            elemActor->y = target->slideY * progress + target->spawnY + (f32)offsetY;
            if (type == 9) {
                elemActor->y = D_80033F4C - 140.0f;
            }
            if (type == 0xC) {
                elemActor->y += (f32)D_80033674;
            }
            if (type == 0) {
                if (offsetY < -0x3BC) {
                    elemActor->scaleY = 0.0f;
                } else {
                    elemActor->scaleY = elemActor->scaleX;
                }
            }
            if (type == 0xB || type == 0x13) {
                elemActor->y += 960;
                if (offsetY >= -3 || offsetY < -0x77C) {
                    elemActor->scaleY = 0.0f;
                } else {
                    elemActor->scaleY = elemActor->scaleX;
                }
            }
            if (type == 0xD) {
                elemActor->y += 1920.0f;
                if (offsetY >= -0x3C3) {
                    elemActor->scaleY = 0.0f;
                } else {
                    elemActor->scaleY = elemActor->scaleX;
                }
            }
            if (type == 0xE) {
                t = (gFrameCounter * 0x78) & 0xFFF;
                radius = mathSinF(t); // FAKE: radius holds the sine: the compound += mathSinF(t) takes a cfe hidden temp word (Q0487) that the case-15 color pointer needs (frame 120, spill temps sp+52/sp+60); ACDC0 hudPauseMenuIconUpdate routes its wobble sine through its radius local sc the same way
                elemActor->y += radius * 10.0f;
            }
            if (type == 0x13 && (sMenuJoinedPlayerCount == 4 || sMenuJoinedPlayerCount == 1 || D_8076A104 == 1)) {
                elemActor->x = -400.0f;
            }
            if (type == 0x10 && state->selection >= 3) {
                elemActor->x = -400.0f;
            }
            if (type == 0x11 && state->selection < 3) {
                elemActor->x = -400.0f;
            }
            break;
        case 2:
        case 3:
        case 10: {
            idx = (s32)target->spawnX;
            switch (type) {
            case 2:
                splineStep = 4;
                stepOrScale = 1024.0f;
                radius = 65.0f;
                break;
            case 3:
                splineStep = 3;
                stepOrScale = 1365.0f;
                radius = 55.0f;
                break;
            case 10:
                splineStep = 2;
                stepOrScale = 2048.0f;
                radius = 50.0f;
                break;
            }
            idx *= (s32)stepOrScale;
            idx -= state->selection * (s32)stepOrScale;
            idx -= (s32)(state->scroll * stepOrScale);
            t = (s16)idx;
            elemActor->x = 160.0f - mathSinF(t) * radius;
            elemActor->y = 120.0f - mathCosF(t) * radius;
            if (menuComputeElementPosition(state, elemActor->x, elemActor->y, &elemActor->x, &elemActor->y, splineStep, 0, 1.0f) == (s32)target->spawnX) {
                stepOrScale = 1.1f;
            } else {
                stepOrScale = 0.825f;
            }
            progress = 0.0f;
            elemActor->x *= 4.0f;
            elemActor->y *= 4.0f;
            elemActor->scaleX = target->slideXOrScale * 4.0f * stepOrScale;
            elemActor->scaleY = elemActor->scaleX;
            break;
        }
        case 15: {
            idx = (s32)target->spawnX;
            elemActor->x = sMenuElementX[idx];
            elemActor->y = sMenuElementY[idx];
            elemActor->scaleX = sMenuElementScale[idx];
            elemActor->scaleY = sMenuElementScale[idx];
            sMenuElementX[idx] = -200.0f;
            sMenuElementY[idx] = -200.0f;
            if (sMenuKongUnlocked[idx] == 0) {
                MenuUiRgba *color = sMenuKongColors + idx;

                elemActor->red = color->r;
                elemActor->green = color->g;
                elemActor->blue = color->b;
            }
            break;
        }
        }
        if (progress > 1.0f || state->fade > 1.0f) {
            *outFlag = 1;
        }
    }
}


s32 menuEvaluateSelectorSpline(MenuScreenState *state, s32 index, f32 *outPosX, f32 *outPosY, f32 *outScale, s16 *outColor, s16 *outAlpha) {
    f32 depth;
    s32 slot;

    index += state->selection;
    if (index >= 5) {
        index -= 5;
    }
    slot = index;
    index <<= 2;
    gSelectorSplineY[index + 2] = gSelectorSplineX[index];
    gSelectorSplineX[index + 2] = -gSelectorSplineY[index];
    gSelectorSplineY[index + 3] = gSelectorSplineX[index + 1];
    gSelectorSplineX[index + 3] = -gSelectorSplineY[index + 1];
    *outPosX = menuEvaluateSpline(gSelectorSplineX + index, state->scroll, NULL);
    *outPosY = menuEvaluateSpline(gSelectorSplineY + index, state->scroll, NULL);
    if (*outPosY < -40.0f) {
        depth = -*outPosY - 40.0f;
        if (depth > 20.0f) {
            depth = 20.0f;
        }
        *outScale = (depth / 60.0f) + 1.0f;
        *outColor = (s16)(depth * 6.2f) + 0x80;
    } else {
        *outScale = 1.0f;
        *outColor = 0x80;
    }
    *outAlpha = 0xFF;
    if (index == 0) {
        *outPosY *= 1.0f - D_80033F3C;
        *outScale += D_80033F3C * 3.5f;
        if (D_80033F3C != 0.0f) {
            *outAlpha = 0xFF - (s32)(state->fade * 255.0f);
            if (*outAlpha < 0) {
                *outAlpha = 0;
            }
        }
    }
    *outPosX *= 4.0f + (state->fade * 4.0f);
    *outPosY *= 4.0f + (state->fade * 4.0f);
    *outPosX += 640.0f;
    *outPosY += 480.0f;
    return slot;
}

s32 menuComputeElementPosition(MenuScreenState *state, f32 baseX, f32 baseY, f32 *outPosX, f32 *outPosY, s32 count, s8 mode, f32 factor) {
    f32 dist;
    f32 f;
    f32 t = 0.0f;
    s32 idx;

    baseX = baseX - 160.0f;
    baseY = baseY - 120.0f;
    dist = sqrtf((baseX * baseX) + (baseY * baseY));
    if (dist < 20.0f) {
        dist = 20.0f;
    }
    f = state->scroll;
    idx = state->selection;
    if (t != f) {
        if (f > 0.5f) {
            idx += 1;
        }
        if (idx >= count) {
            idx -= count;
        }
    }
    t = state->fade * 0.5f;
    if (mode == 1) {
        t += f;
    }
    t = (2.0f * t) - 1.0f;
    if (t < 0.0f) {
        t = -t;
    }
    t = 1.0f - t;
    if (t < 0.0f) {
        t = 0.0f;
    }
    t = ((100.0f / dist) * t * factor) + 1.0f;
    *outPosX = (baseX * t) + 160.0f;
    *outPosY = (baseY * t) + 120.0f;
    *outPosY = *outPosY + state->scrollY;
    return idx;
}

f32 menuEvaluateSpline(f32 *coeffs, f32 t, f32 *outDeriv) {
    f32 poly[4];

    poly[0] = (coeffs[0] + coeffs[0] + -2.0f * coeffs[1] + coeffs[2]) + coeffs[3];
    poly[1] = (-3.0f * coeffs[0] + 3.0f * coeffs[1] + -2.0f * coeffs[2]) - coeffs[3];
    poly[2] = coeffs[2];
    poly[3] = coeffs[0];
    if (outDeriv != NULL) {
        *outDeriv = ((((3.0f * poly[0]) * t) + (poly[1] + poly[1])) * t) + poly[2];
    }
    return (((((poly[0] * t) + poly[1]) * t) + poly[2]) * t) + poly[3];
}


void menuActorStateDispatch(void) {
    Actor *actor = gCurrentActor;

    switch (actor->unk155) {
    case 0:
        actorScriptStart(actor, 0x345);
        gCurrentActor->yaw = 0;
        gCurrentActor->unk155 = 1;
        camStartPath(gCurrentActor, 0x13, 5);
        break;
    case 2:
        actor->unk155++;
        break;
    case 4:
        if (D_80033734 == 0) {
            D_80033734 = 1;
        }
        break;
    case 1:
    case 3:
    default:
        break;
    }
}



extern s16 D_80754CE0;
extern u8 D_8071FE64;

void menuUpdateKioskActor(void) {
    MenuKioskState *kioskState;
    s32 i;

    kioskState = gCurrentActor->customState;
    D_8003369C += 4.5f;
    if (D_8003369C > 0.0f) {
        D_8003369C = 0.0f;
    }
    switch (gCurrentActor->unk155) {
    case 0:
        gCurrentActor->yaw = 0x800;
        gCurrentActor->unk155 = 1;
        actorScriptStart(gCurrentActor, 0x346);
        func_8061B650(gCamActor);
        D_8003369C = -35.0f;
        break;
    case 1:
        if (D_8003369C == 0.0f) {
            actorScriptStart(gCurrentActor, 0x347);
            gCurrentActor->unk155 = 2;
            kioskState->phaseFrames = 0;
        }
        break;
    case 2:
        kioskState->phaseFrames += 1;
        if (kioskState->phaseFrames == 3) {
            sfxPlayOnFreeSlot(0x3C, 0x61A8, 63.0f, 1.0f, 0, 0);
            D_80033F50 = 3;
        }
        break;
    case 3:
        if (*gPlayerSlots->heldButtonsPtr & 0x8000) {
            if (D_800337F0 == 1) {
                actorScriptStart(gCurrentActor, 0x348);
                gCurrentActor->unk155 = 4;
                D_800337F4 = 0x3C;
            } else if (D_800337F0 == -1) {
                sfxPlayOnFreeSlot(0x98, 0x61A8, 63.0f, 1.0f, 0, 0);
            }
        }
        break;
    case 5:
        D_80033F40 = 0.1f;
        D_80033F3C = D_80033F40;
        D_800337F4 = 0;
        kioskState->phaseFrames = 0;
        gCurrentActor->unk155 = 6;
        break;
    case 6:
    case 7:
    case 8:
        kioskState->phaseFrames += 1;
        if (kioskState->phaseFrames >= 0x3E9) {
            kioskState->phaseFrames = 0x3E8;
        }
        if (kioskState->phaseFrames == 8) {
            effectEnableFade();
            effectCreateAtPosition(&D_8071FE08, 8.3f, 160.0f, 120.0f, -10.0f);
            sfxPlayOnFreeSlot(0x23, 0x7FFF, 63.0f, 1.0f, 0, 0);
            sfxPlayOnFreeSlot(0x17, 0x7FFF, 63.0f, 1.0f, 0, 0);
            for (i = 0; i != 5; i++) {
                effectSetCallback(menuSparkleParticleUpdate);
                effectEnableFade();
                effectCreateAtPosition(&D_8071FE64, 1.8f, 160.0f, 120.0f, -10.0f);
            }
        }
        if (kioskState->phaseFrames >= 0xC) {
            gGlobalPauseFlags &= 0xFFFEFFFF;
        }
        break;
    }
    if (D_80033698 != 0) {
        D_80033698 -= 1;
    }
    if (gCurrentActor->unk155 < 6) {
        if (D_8003369C > -30.0) {
            gGlobalPauseFlags |= 0x10000;
        } else {
            D_80033698 = 3;
        }
    }
    D_80033738 = 0x14;
    gCurrentActor->y = -D_8003369C;
    gPlayerSlots->camX = gCurrentActor->x;
    gPlayerSlots->camY = (D_80033678[D_80033F50] * 50.0) + (gCurrentActor->y + 13.1f + D_8003369C) - 0.1;
    gPlayerSlots->camZ = gCurrentActor->z - 50.0f;
    gPlayerSlots->focusX = gCurrentActor->x;
    gPlayerSlots->focusY = gPlayerSlots->camY;
    gPlayerSlots->focusZ = 10020.0f;
    D_80754CE0 = D_80033678[D_80033F50] * 400.0f;
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void menuUpdateKioskPodActor(void) {
    MenuKioskState *podState;
    f32 x[2];
    f32 y[2];
    f32 z[2];
    f32 cx;
    f32 screenX;
    f32 screenY;
    f32 cy;
    f32 cz;
    s32 pad0;
    s32 pad1;
    s32 pad2;

    podState = gCurrentActor->customState;
    if (gPrimaryPlayerActor->unk155 < 6) {
        if (D_80033738 == 0x14) {
            actorDespawn(gCurrentActor);
            D_80033738 += 1;
            actorSpawn(0x14D, 0xD7);
            gSpawnedActor->sub4->scaleX = 0.14f;
            gSpawnedActor->sub4->scaleY = 0.14f;
            gSpawnedActor->sub4->scaleZ = 0.14f;
        } else if (D_80033738 == 0x15) {
            actorGetNodePos(gPrimaryPlayerActor, 2, &x[0], &y[0], &z[0]);
            actorGetNodePos(gPrimaryPlayerActor, 3, &x[1], &y[1], &z[1]);
            cx = (x[0] + x[1]) * 0.5f;
            cy = y[0];
            cz = (z[0] + z[1]) * 0.5f;
            gCurrentActor->x = cx;
            gCurrentActor->y = cy;
            gCurrentActor->z = cz;
            podState->homeX = gCurrentActor->x;
            podState->homeY = gCurrentActor->y;
            podState->homeZ = gCurrentActor->z;
            gCurrentActor->yaw = 0;
            gCurrentActor->roll = 0x400;
            camProjectToScreen(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, &screenX, &screenY, 0, 1.0f, 0);
            screenY -= 120.0f;
            if (screenY < -35.0f) {
                if (screenY > -75.0f) {
                    gSelectorSplineY[0] = screenY;
                    gSelectorSplineY[0x11] = screenY;
                }
            }
        }
    } else {
        gCurrentActor->x = podState->homeX;
        gCurrentActor->y = podState->homeY - (D_80033F3C * 19.0f);
        gCurrentActor->z = podState->homeZ - (D_80033F3C * 50.0f);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (D_80033698 != 0) {
        gCurrentActor->flags &= ~4;
    } else {
        gCurrentActor->flags |= 4;
    }
}


s32 menuCheckSaveFile(s32 fileSlot) {
    return eepromGetField(0xD, 0, 0, fileSlot) == 0;
}

s32 menuCalculateGamePercentage(void) {
    f32 pct;

    hudPauseMenuRefreshTotals();
    pct = 0.0f;
    pct += (f32)gPauseCollectibleCounts[0] * 0.4;
    pct += (f32)gPauseCollectibleCounts[2] * 0.25;
    pct += (f32)gPauseCollectibleCounts[5] * 0.2;
    pct += (f32)gPauseCollectibleCounts[3] * 0.2;
    pct += (f32)gPauseCollectibleCounts[1] * 0.5;
    pct += (f32)gPauseCollectibleCounts[4] * 0.5;
    pct += (f32)gPauseCollectibleCounts[6] * 0.5;

    if (gPauseCollectibleCounts[0] == 0xC9) {
        pct -= 0.4;
    }

    if (pct == 100.0) {
        if (flagGet(0x12D, 0) != 0 && flagGet(0x12D, 0) != 0) {
            pct += 1.0;
        }
    }

    return pct;
}


void menuLoadTextTable(void) {
    s32 i;

    sMenuTextTable = heapAlloc(0x194);
    i = 0;
    do {
        sMenuTextTable[i] = textTableGetString(0x25, i, 0);
        i++;
    } while (i != 0x65);
}
