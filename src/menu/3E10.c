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
    f32 unk0;
    f32 unk4;
    char pad8[4];
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s8 unk12;
    s8 nextScreen;
    char pad14;
    s8 unk15;
    s8 unk16;
    s8 selection;
} MenuScreenState;


typedef struct MenuEffect { // effect objects created by effectCreateAtPosition for the menu
    /* 0x000 */ char pad0[0x128];
    /* 0x128 */ Mtx mtx[8];
    /* 0x328 */ char pad328[0x18];
    /* 0x340 */ f32 posX;
    /* 0x344 */ f32 posY;
    /* 0x348 */ char pad348[0x14];
    /* 0x35C */ MenuScreenState *cfg;
    /* 0x360 */ f32 scaleX;
    /* 0x364 */ f32 scaleY;
    /* 0x368 */ char pad368[2];
    /* 0x36A */ u8 colorR;
    /* 0x36B */ u8 colorG;
    /* 0x36C */ u8 colorB;
    /* 0x36D */ u8 colorA;
    /* 0x36E */ char pad36E[0x16];
    /* 0x384 */ void *data;
    /* 0x388 */ char pad388[6];
    /* 0x38E */ s16 unk38E;
    /* 0x390 */ char pad390[2];
    /* 0x392 */ s16 unk392;
} MenuEffect;

typedef struct MenuEffectTarget {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
} MenuEffectTarget;


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

extern s8 D_80033734;
extern Actor *gCamActor;

void menuTitleScreenHandleInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;
    s32 trigger = 0;

    if (D_80033734 != 0) {
        D_80033734++;
        if (D_80033734 >= 0xB) {
            trigger = 1;
        }
    }
    if (state->unk0 == 0.0 && (trigger != 0 || (buttons & 1))) {
        state->unk12 = 1;
        state->unk16 = -1;
        state->unk0 = 1.0f;
        menuUpdateStateDispatch(actor, 0, 0, 0);
        camEndPath(gCamActor);
        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        D_80033734 = 0;
    }
}

Gfx *menuTitleScreenDraw(void *actor, Gfx *dl) {
    return dl;
}

typedef struct MenuActorExt { // menu actors carry an extra pointer past Actor
    /* 0x000 */ Actor base;
    /* 0x178 */ s32 pad178;
    /* 0x17C */ s16 *unk17C;
} MenuActorExt;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;
extern s8 D_80033734;

void menuResetCameraAndFlags(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    gPrimaryPlayerActor->x = 109.0f;
    gPrimaryPlayerActor->y = 6.0f;
    gPrimaryPlayerActor->z = 55.0f;
    state->unk0 = 0.0f;
    D_80033734 = 0;
    gGlobalPauseFlags |= 0x10000;
}


typedef struct {
    s32 unk0;
    s32 unk4;
} BonusMenu_Pair;

extern s16 D_800336A0;
extern s16 D_800336A4[];
extern s16 D_80033724[];
extern s8 D_800337F0;
extern s8 D_800337F4;
extern BonusMenu_Pair D_800337FC;
extern f32 D_80033F3C;
extern f32 D_80033F40;
extern s16 D_80033F52;
extern s8 D_80033F54;
extern s8 D_80033F55;
extern s8 D_80033F56;
extern f32 D_80033F58;
extern f32 D_80033F5C;
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
    if (state->unk0 == 0.0f && D_80033F3C == 0.0f && D_800337F4 == 0) {
        if (state->unk4 == 0.0f) {
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
    D_8076A0D2 = 0;
    if (D_80033F40 != 0.0f) {
        D_80033F3C += D_80033F40;
        if (D_80033F3C > 1.0f) {
            D_80033F3C = 1.0f;
            state->unk16 = 0;
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
    D_80033F52 -= 1;
    if (D_80033F52 <= 0) {
        switch (D_800336A4[D_80033F54]) {
        case -2:
            D_80033F52 = D_800336A4[D_80033F54 + 1];
            D_80033F54 += 2;
            camAction = 1;
            break;
        case -3:
            D_80033F52 = D_800336A4[D_80033F54 + 1];
            D_80033F54 += 2;
            camAction = -1;
            break;
        case -4:
            D_80033F52 = D_800336A4[D_80033F54 + 1];
            D_80033F54 += 2;
            D_80033F56 = 1;
            break;
        case -5:
            D_80033F52 = D_800336A4[D_80033F54 + 1];
            D_80033F54 += 2;
            D_80033F56 = 0;
            break;
        default:
        if (D_800336A4[D_80033F54] < -5) {
            sel = -6 - D_800336A4[D_80033F54];
            if (D_800337F4 == 0) {
                actorScriptStart(gPrimaryPlayerActor, D_80033724[(s16)sel]);
            }
            D_80033F52 = D_800336A4[D_80033F54 + 1];
            D_80033F54 += 2;
        } else if (D_800336A4[D_80033F54] >= 0) {
            camStartPath(0, D_800336A4[D_80033F54], 1);
            D_80033F52 = D_800336A4[D_80033F54 + 1];
            D_80033F54 += 2;
        } else {
            idxCounter = 0;
            randIdx = (s32)(randomFloat() * 10.0f);
            D_80033F52 = (randomLcgNext() & 0x7F) + 0x12C;
            D_80033F54 = 0;
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
                    if (D_800336A4[D_80033F54] != -1) {
                        do {
                            D_80033F54 += 1;
                        } while (D_800336A4[D_80033F54] != -1);
                    }
                    D_80033F54 += 1;
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

extern u8 **D_80033F28;


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
    return textDrawStringVtx(dl, 1, 0, 0, D_80033F28[strIdx], 0x80);
}

extern s8 D_800337F8;
extern s8 D_8076A0D1[];
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
    state->selection = D_8076A0D1[0];
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 0, 0, 1.2f, 2, 0x12); // FAKE: (void *)(s32) address cast keeps the lui/addiu pair scheduled before the arg loads
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 1, 0, 1.2f, 2, 0x12); // FAKE: (void *)(s32) address cast keeps the lui/addiu pair scheduled before the arg loads
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 2, 0, 1.2f, 2, 0x12); // FAKE: (void *)(s32) address cast keeps the lui/addiu pair scheduled before the arg loads
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 3, 0, 1.2f, 2, 0x12); // FAKE: (void *)(s32) address cast keeps the lui/addiu pair scheduled before the arg loads
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 4, 0, 1.2f, 2, 0x12); // FAKE: (void *)(s32) address cast keeps the lui/addiu pair scheduled before the arg loads
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
    D_80033F54 = 0;
    while (D_800336A4[D_80033F54] != -1) {
        D_80033F54++;
    }
    D_80033F52 = 0x1E;
    D_80033F55 = 0;
    D_80033F56 = 0;
    D_80033F5C = 0.0f;
    D_80033F58 = 1.0f;
    gGlobalPauseFlags &= 0xFFFEFFFF;
}

void menuMainScreenNoop(void) {
}

extern s8 D_80033F48;

void menuHandleSelectionInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;

    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            if (buttons & 1) {
                state->unk16 = 0;
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                switch (state->selection) {
                case 2:
                    state->nextScreen = 4;
                    break;
                default:
                    D_80033F48 = state->selection;
                    if (D_80033F48 == 3) {
                        D_80033F48 = 2;
                    }
                    state->nextScreen = 3;
                    break;
                }
            } else if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
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
        _sprintf(strBuf, "%s", D_80033F28[5]);
    } else {
        if (idx == 3) {
            idx = 2;
        }
        if (menuCheckSaveFile(idx) != 0) {
            _sprintf(strBuf, "%s", D_80033F28[6]);
        } else {
            _sprintf(strBuf, "%s %d", D_80033F28[7], idx + 1);
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


extern u8 D_80033818;
extern u16 D_8003381C[];
extern s8 D_807563B4;
extern u16 D_807ECD48[];

void menuCheckCheatCodeSequence(void) {
    u16 *pressed;

    pressed = D_807ECD48;
    if (D_8003381C[D_80033818] == *pressed) {
        D_80033818++;
        if (D_80033818 >= 7U) {
            D_807563B4 = 1;
            sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
            D_80033818 = 0;
        }
    } else if (D_807ECD48[0] != 0) {
        D_80033818 = 0;
    }
}

extern s8 D_80033F48;

void menuHandleConfirmationInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;

    if (state->unk0 == 0.0f && state->unk4 == 0.0f) {
        if (buttons & 1) {
            controllerSetActiveMask(1);
            func_807144B8(D_80033F48);
        } else if (buttons & 2) {
            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            state->unk16 = 0;
            state->nextScreen = 2;
        }
    }
    menuUpdateItemTransition(actor, state, 1);
}

extern s8 D_80033804;
extern s32 D_8003380C;
extern s32 D_80033810;
extern u32 D_80033814;
extern f32 D_80033F4C;
extern s8 D_80033F51;

Gfx *menuDrawFileSummary(Actor *actor, Gfx *dl) {
    f32 x = 66.0f;
    s16 y;
    s16 py;
    MenuScreenState *state = actor->customState;
    s8 *p = &D_80033804;
    s32 i = 0;
    f32 sc = 3.0f;
    f32 four;
    f32 posX;
    f32 posY;
    s32 ang;
    f32 fv1;
    u8 strBuf[0x20];

    do {
        menuComputeElementPosition(state, x, 85.0f, &posX, &posY, 4, 0, 1.5f);
        if (*p != 0) {
            dl = menuSetElementCoordinates(dl, i, posX, posY, sc * 0.85);
        } else {
            dl = menuSetElementCoordinates(dl, i | 0x80, posX, posY, sc);
        }
        i++;
        p++;
        x += 55.0f;
    } while (i != 5);
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    menuComputeElementPosition(state, 160.0f, 180.0f, &posX, &posY, 5, 1, 2.0f);
    four = 4.0f; // FAKE: value-named constant local holds 4.0f in one FP register
    D_80033F4C = posY * four;
    py = D_80033F4C;
    py -= 0x140;
    _sprintf(strBuf, "%d%%", D_80033F51);
    dl = textDrawStringVtx(dl, 1, 0x280, py, strBuf, 0x81);
    py += 0x8C;
    _sprintf(strBuf, "%03d", D_8003380C);
    dl = textDrawStringVtx(dl, 1, 0x280, py, strBuf, 0x81);
    py += 0x8C;
    _sprintf(strBuf, "%03d:%02d", D_80033810, D_80033814);
    dl = textDrawStringVtx(dl, 1, 0x280, py, strBuf, 0x81);
    x = 0.5f; // FAKE: x reused as the sprite scale; a separate scale variable fails fdiff
    ang = (gFrameCounter * 0x78) & 0xFFF;
    fv1 = mathSinF(ang) * 0.1f + 0.5f;
    py = (s32)((f32)py + 40.0f);
    sc = py; // FAKE: sc reused as the sprite base y; a separate variable fails fdiff
    posY = sc * 0.25f + 32.0f * fv1;
    posX = 85 * four;
    x *= four;
    posY *= four;
    dl = renderRotatedSprite(dl, 0xA1, 3, 0, 0x40, 0x40, (s32)posX, (s32)posY, x, -(fv1 * four), 0, 0.0f);
    gDPPipeSync(dl++);
    posY = sc;
    x = x * 0.75f;
    sc = -x;
    posX = 340.0f;
    i = gFrameCounter % 360U; // FAKE: loop counter i reused as the sprite angle; a separate angle variable fails fdiff
    dl = renderRotatedSprite(dl, 0xA0, 3, 0, 0x20, 0x20, (s32)posX, (s32)posY, x, sc * 0.5f, i, 0.0f);
    gDPPipeSync(dl++);
    i = (gFrameCounter * 0xC) % 360U;
    dl = renderRotatedSprite(dl, 0xA0, 3, 0, 0x20, 0x20, (s32)posX, (s32)posY, x, sc, i, 0.0f);
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    menuComputeElementPosition(state, 160.0f, 15.0f, &posX, &posY, 5, 1, 0.3f);
    y = posX * four;
    py = posY * four;
    _sprintf(strBuf, "%s %d", D_80033F28[7], D_80033F48 + 1);
    return hudDrawScaledText(dl, y, py, 0.6f, strBuf);
}

s32 menuDecodePiAddressConstant(s32 offset) {
    return offset + 0x1EFF0;
}

extern u8 D_80720CF0;
extern u8 D_80720D14;
extern u8 D_80720C34;
extern void *D_80750518[];
extern s16 D_807505B2;
extern u32 D_80750AB0;
extern u8 gPlayerInventoryTable[][0x5E];
extern s8 D_80033804;
extern s8 D_80033805;
extern s32 D_8003380C;
extern s32 D_80033810;
extern u32 D_80033814;
extern f32 D_80033F4C;
extern s8 D_80033F51;

extern s8 D_80033809;
void menuInitFileSummary(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    u8 *row = gPlayerInventoryTable[0];
    s8 *p;
    s16 *q;
    s32 pad;
    void *asset;
    u32 ioVal;
    s32 i;
    s32 k;
    s32 j;

    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_8072052C, 0x76, 0x91, 0.6f, 2, 9);
    D_80033F4C = 1600.0f;
    eepromLoadPlayerData((u8)D_80033F48, 0);
    D_80033804 = 1;
    q = &D_807505B2; p = &D_80033805; i = (s32)&D_80033809; // FAKE: loop counter i holds the end address (s32); an s8 *end local swaps s1/s2 between q and the end (as1 group kept on one line)
    do {
        k = flagGet(q[-1], 0);
        q++;
        *p++ = k;
    } while (p < (s8 *)i);
    for (p = &D_80033805 - 1, i = 0; i != 5; i++) {
        if (*p != 0) {
            asset = D_80750518[i];
        } else {
            asset = &D_807211D0;
        }
        menuSpawnUiElementEffect(state, asset, i, i, 0.8f, 2, 0xF);
        p++;
    }
    osPiReadIo(menuDecodePiAddressConstant(0xAFFE1464), &ioVal);
    if ((menuDecodePiAddressConstant(0x0107183B) ^ 0) != ioVal) { // FAKE: ^ 0 flips the commutative bne/beq operand order
        *(u32 *)actorUpdateCollisionSpheres = 0x03E00008;
    }
    D_8003380C = 0;
    for (k = 0; k != 5; k++) {
        for (j = 0; j != 8; j++) {
            D_8003380C += *(u16 *)(row + 0x42 + j * 2);
        }
        row += 0x5E;
    }
    D_80033814 = D_80750AB0 / 60;
    D_80033810 = (s32)D_80033814 / 60;
    D_80033814 = D_80033814 - D_80033810 * 60;
    D_80033F51 = menuCalculateGamePercentage();
}


void menuHandleFileSelectInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;

    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            if (buttons & 1) {
                if (menuCheckSaveFile(state->selection) == 0) {
                    state->unk16 = 0;
                    state->nextScreen = 5;
                    D_80033F48 = state->selection;
                } else {
                    sfxPlayOnFreeSlot(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
            } else if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
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
        _sprintf(strBuf, "%s", D_80033F28[6]);
    } else {
        _sprintf(strBuf, "%s %d", D_80033F28[7], fileIdx + 1);
    }
    dl = hudDrawScaledText(dl, posX, y, 0.6f, strBuf);
    y -= 0x3C;
    return hudDrawScaledText(dl, (s16)(textX * 4.0f), y, 0.6f, D_80033F28[8]);
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
extern u8 D_8071FE08;
extern s8 D_80033FAC;

void menuMysteryHandleInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;

    if (state->unk0 == 0.0f && state->unk4 == 0.0f) {
        if (buttons & 1) {
            if ((buttons & 8) && (D_80033FAC != 0)) {
                effectEnableFade();
                effectCreateAtPosition(&D_8071FBC8, 10.3f, 240.0f, 120.0f, -10.0f);
                effectEnableFade();
                effectCreateAtPosition(&D_8071FE08, 10.3f, 240.0f, 120.0f, -10.0f);
                sfxPlayOnFreeSlot(0xF6, 0x7FFF, 63.0f, 1.0f, 0, 0);
                eepromSetCurrentSlot(D_80033F48, 1);
                state->unk16 = 0;
                state->nextScreen = 2;
            } else if ((buttons & 4) && (D_80033FAC != 0)) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->nextScreen = 2;
            }
        } else if (buttons & 2) {
            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            state->unk16 = 0;
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
    if (menuCheckSaveFile(D_80033F48) != 0) {
        _sprintf(strBuf, "%s", D_80033F28[6]);
    } else {
        _sprintf(strBuf, "%s %d", D_80033F28[7], D_80033F48 + 1);
    }
    dl = hudDrawScaledText(dl, posX, y, 0.6f, strBuf);
    y -= 0x3C;
    dl = hudDrawScaledText(dl, (s16)(textX * 4.0f), y, 0.6f, D_80033F28[8]);
    menuComputeElementPosition(state, 160.0f, 80.0f, &textX, &textY, 5, 0, 2.0f);
    dl = hudDrawScaledText(dl, (s16)(textX * 4.0f), (s16)(textY * 4.0f), 0.6f, D_80033F28[9]);
    menuComputeElementPosition(state, 80.0f, 120.0f, &textX, &textY, 5, 0, 2.0f);
    return hudDrawScaledText(hudDrawScaledText(dl, (s16)(textX * 4.0f), (s16)(textY * 4.0f), 0.6f, D_80033F28[10]), 0x500 - (s16)(textX * 4.0f), (s16)(textY * 4.0f), 0.6f, D_80033F28[11]);
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

extern s16 D_80033670;
extern s8 D_80033698;
extern s8 D_80744538;
extern s8 D_8076A104;

void menuBossReplayHandleInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;

    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            if (buttons & 1) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->nextScreen = 7;
            } else if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->nextScreen = 1;
                D_80033698 = 3;
            } else {
                menuHandleScrollInput(state, 2, buttons);
            }
            if (state->selection == 0) {
                if (!(D_80033670 & 0x10) && (buttons & 0x10)) {
                    sfxPlayOnFreeSlot(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    D_80744538++;
                    if (D_80744538 >= 3) {
                        D_80744538 = 0;
                    }
                } else if (!(D_80033670 & 0x20) && (buttons & 0x20)) {
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
    dl = textDrawStringVtx(dl, 1, posX * 4.0f, posY * 4.0f, D_80033F28[idx + 12], 0x81);
    if (idx == 0) {
        _sprintf(strBuf, "%s %d", D_80033F28[14], D_80744538 + 1);
        menuComputeElementPosition(state, 160.0f, 207.0f, &posX, &posY, 2, 0, 0.7f);
        dl = hudDrawScaledText(dl, posX * 4.0f, posY * 4.0f, 0.6f, strBuf);
    }
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    for (i = 0; i != 0x1000; i += 0x800) {
        ang = i - (state->selection << 11);
        ang -= (s32)(state->unk4 * 2048.0);
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
extern s8 D_8076A0E4[];
extern s8 D_8076A0E8[][4];

void menuAssignPlayerControllerSlot(s32 playerIdx, s32 slotIdx) {
    s8 prevSlot = D_8076A0E4[playerIdx];
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
    D_8076A0E4[playerIdx] = slotIdx;
}

void menuReleasePlayerControllerSlot(s32 playerIdx) {
    s8 slot = D_8076A0E4[playerIdx];
    s8 *assignedSlotPtr = &D_8076A100[playerIdx];
    s8 subSlot = *assignedSlotPtr;

    if ((subSlot >= 0) && !(slot & 0x80)) {
        D_8076A0E8[slot][subSlot] = -1;
    }
    *assignedSlotPtr = -1;
    D_8076A0E4[playerIdx] = -0x80;
}


extern s8 D_8076A0D6;

void menuInitControllerSlots(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    s32 i;
    s32 j;

    state->selection = D_8076A0D6;
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
            D_8076A0E4[i] = -0x80;
            menuReleasePlayerControllerSlot(i);
        }
    }
}

s32 menuNextFreeControllerSlot(s32 playerIdx) {
    s8 slot = D_8076A0E4[playerIdx];
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
    s8 slot = D_8076A0E4[playerIdx];
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

extern s8 D_80033FAD;
extern s8 D_80744520;
extern s8 D_80744534;
extern s8 D_80033FAE;
extern s8 D_80033F50;
extern u8 D_80744514;
extern s8 D_80033FAF;
extern s8 D_8074451C;
extern s32 D_8003382C[];
extern s32 D_80033834[];
extern u8 D_8003384C[];
extern s32 D_80033858;
extern s32 D_8003385C[];
extern s8 gPlayerCharacterId[];
extern u8 D_80750ABC;
extern u8 gActivePlayerCount;
extern s32 D_807552E4[];
extern u8 D_807ECD09;
extern OSContPad D_807ECD10[];

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
    s32 mask;
    s16 cur;

    step = state->unkC;
    step = state->unkE - step;
    if (step >= 0x15) {
        step = 0x14;
    }
    if (step < -0x14) {
        step = -0x14;
    }
    state->unkC += step;
    rest = state->unkE - state->unkC;
    if (step != 0 && rest == 0) {
        sfxPlayOnFreeSlot(0x3C, 0x4E20, 63.0f, 1.0f, 0, 0);
        D_80033F50 = 3;
    }
    if (D_80033FAE != 0) {
        buttons = 0;
    }
    if (state->unk0 == 0.0f && rest == 0) {
        itemCount = 5;
        if (D_8076A104 == 0) {
            itemCount = 6;
        }
        if (state->unk4 == 0.0f) {
            if ((buttons & 1) && D_80033FAD >= 2) {
                mask = 0;
                gActivePlayerCount = 0;
                for (j = 0; j != 4; j++) {
                    bits = 1 << j;
                    if (!(D_8076A0E4[j] & 0x80)) {
                        gPlayerCharacterId[j] = D_8076A0E4[j];
                        mask = (mask | bits) & 0xFF;
                        D_807552E4[4 + gActivePlayerCount] = D_8076A100[j];
                        gActivePlayerCount += 1;
                    }
                }
                controllerSetActiveMask(mask);
                D_807552E4[0] = D_8003382C[D_8076A104];
                D_807552E4[1] = D_80033834[D_8074451C];
                D_807552E4[3] = D_80744520;
                D_807552E4[8] = D_80744538;
                D_80750ABC = D_8003384C[D_80744534];
                D_80033FAE = 1;
                D_80744514 = 2;
                func_8071458C();
            } else {
                if (buttons & 2) {
                    sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                    state->unk16 = 0;
                    state->nextScreen = 6;
                } else if (buttons & 0x40) {
                    state->unkE = state->unkE - 0xF0;
                    if ((D_80033FAD == 2 || D_80033FAD == 3) && D_8076A104 != 1) {
                        lim = -0x1E0;
                    } else {
                        lim = -0xF0;
                    }
                    if (state->unkE < lim) {
                        state->unkE = lim;
                    } else {
                        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                    }
                } else if (buttons & 0x80) {
                    state->unkE += 0xF0;
                    if (state->unkE > 0) {
                        state->unkE = 0;
                    } else {
                        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                    }
                }
            }
            i = (buttons ^ D_80033858) & buttons; // FAKE: loop counter i reused as the pressed mask; a separate local recolours (uopt CSEs the re-spelled tests into v0, i stays the s0 copy)
            cur = state->unkC;
            if (cur == 0 && D_80033FAE == 0) {
                i = 0;
                do {
                    bits = 0;
                    if (D_807ECD09 & (1 << i)) {
                        if (D_807ECD10[i].stick_x < -0x28) {
                            bits = 4;
                        } else if (D_807ECD10[i].stick_x >= 0x29) {
                            bits = 8;
                        }
                        if (D_807ECD10[i].stick_y < -0x28) {
                            bits |= 0x20;
                        } else if (D_807ECD10[i].stick_y >= 0x29) {
                            bits |= 0x10;
                        }
                        edge = (D_8003385C[i] ^ bits) & bits;
                        D_8003385C[i] = bits;
                        if (D_8076A0E4[i] & 0x80) {
                            if (D_807ECD48[i] & 0x1000) {
                                sfxPlayOnFreeSlot(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                menuAssignPlayerControllerSlot(i, 0);
                            }
                        } else {
                            if (edge & 8) {
                                sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                idx = D_8076A0E4[i] + 1;
                                if (idx >= 6) {
                                    idx = 0;
                                }
                                while (!(D_80033FAF & (1 << idx))) {
                                    idx += 1;
                                    if (idx >= 6) {
                                        idx = 0;
                                    }
                                }
                                menuAssignPlayerControllerSlot(i, idx);
                            }
                            if (edge & 4) {
                                sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                idx = D_8076A0E4[i] - 1;
                                if (idx < 0) {
                                    idx = 5;
                                }
                                while (!(D_80033FAF & (1 << idx))) {
                                    idx -= 1;
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
                            if (i != 0 && (D_807ECD48[i] & 0x1000)) {
                                sfxPlayOnFreeSlot(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                menuReleasePlayerControllerSlot(i);
                            }
                        }
                    }
                    i += 1;
                } while (i != 4);
            } else if (cur == -0xF0) {
                if (((buttons ^ D_80033858) & buttons) & 0x10) {
                    cap = 5;
                    if (D_80033834[D_8074451C] == 5) {
                        cap = 4;
                    }
                    if (D_80744520 < cap) {
                        D_80744520 += 1;
                        sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    }
                } else if ((((buttons ^ D_80033858) & buttons) & 0x20) && D_80744520 >= 2) {
                    D_80744520 -= 1;
                    sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
                menuHandleScrollInput(state, itemCount, i);
            } else if (cur == -0x1E0) {
                if (((buttons ^ D_80033858) & buttons) & 0x10) {
                    D_80744534 += 1;
                    if (D_80744534 >= 3) {
                        D_80744534 = 0;
                    }
                    sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                } else if (((buttons ^ D_80033858) & buttons) & 0x20) {
                    D_80744534 -= 1;
                    if (D_80744534 < 0) {
                        D_80744534 = 2;
                    }
                    sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
            }
        }
        menuUpdateScrollAnimation(state, itemCount);
    }
    D_80033858 = buttons;
    D_8074451C = state->selection;
    if (D_80033834[D_8074451C] == 5 && D_80744520 >= 5) {
        D_80744520 = 4;
    }
    menuUpdateItemTransition(actor, state, 1);
    gGlobalPauseFlags |= 0x10000;
    menuUpdateCameraPositions();
    D_80033FAD = 0;
    for (i = 0; i < 4; i++) {
        if (!(D_8076A0E4[i] & 0x80)) {
            D_80033FAD += 1;
        }
    }
}


extern f32 D_80033F44;
extern s8 D_80033FAD;
extern s8 D_80033850[];
extern s8 D_80744520;
extern s8 D_80744534;
extern s8 D_8076A0E5;
extern s8 D_8076A0E6;
extern s8 D_8076A0E7;

Gfx *menuDrawCharacterSelect(Actor *actor, Gfx *dl) {
    MenuScreenState *state = actor->customState;
    s32 padA0;
    s32 idx;
    s32 id;
    f32 posX;
    f32 posY;
    f64 offset;
    s32 padB0;
    s32 padB1;
    s32 padB2;
    s16 pad13A;
    s16 textY;
    u8 strBuf[0xC8];
    f32 v;

    if (state->unkC > -239.0) {
        if (D_8076A0E5 & 0x80) {
            menuComputeElementPosition(state, 210.0f, 120.0f, &posX, &posY, 2, 0, 1.8f);
            dl = menuSetElementCoordinates(dl, 0x81, posX + 8.0, posY + 32.0f, 3.0f);
        }
        if (D_8076A0E6 & 0x80) {
            menuComputeElementPosition(state, 160.0f, 170.0f, &posX, &posY, 2, 0, 1.8f);
            dl = menuSetElementCoordinates(dl, 0x82, posX + 8.0, posY + 32.0f, 3.0f);
        }
        if (D_8076A0E7 & 0x80) {
            menuComputeElementPosition(state, 110.0f, 120.0f, &posX, &posY, 2, 0, 1.8f);
            dl = menuSetElementCoordinates(dl, 0x83, posX + 8.0, posY + 32.0f, 3.0f);
        }
        gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
        menuComputeElementPosition(state, 160.0f, 25.0f, &posX, &posY, 2, 0, 0.6f);
        dl = textDrawStringVtx(dl, 1, posX * 4.0f, posY * 4.0f, D_80033F28[D_8076A104 + 12], 0x81);
    }
    if (state->unkC < -1.0f && state->unkC > -479.0f) {
        gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
        menuComputeElementPosition(state, 160.0f, 30.0f, &posX, &posY, 2, 0, 1.5f);
        posY = posY + 240.0f;
        dl = textDrawStringVtx(dl, 1, 0x280, posY * 4.0f, D_80033F28[15], 0x81);
        idx = state->selection;
        if (state->unk4 != 0.0f) {
            if (state->unk4 > 0.5f) {
                idx++;
            }
            if (idx >= 4) {
                idx = 0;
            }
        }
        v = state->unk4 - 0.5f;
        if (v < 0.0f) {
            v = -v;
        }
        v = 0.5f - v;
        v = v * 700.0f;
        if (D_80033F44 < 0.0f) {
            v = -v;
        }
        offset = v;
        menuComputeElementPosition(state, offset + 160.0, 80.0f, &posX, &posY, 2, 0, 2.0f);
        posY = posY + 240.0f;
        dl = textDrawStringVtx(dl, 1, posX * 4.0f, posY * 4.0f, D_80033F28[idx + 16], 0x81);
        menuComputeElementPosition(state, 160.0 - offset, 160.0f, &posX, &posY, 2, 0, 1.5f);
        posY = posY + 240.0f;
        textY = (s16)(posY * 4.0f);
        switch (D_80033850[idx]) {
        case 0:
            if (D_80744520 >= 2) {
                _sprintf(strBuf, "%d %s", D_80744520, D_80033F28[23]);
            } else {
                _sprintf(strBuf, "%d %s", D_80744520, D_80033F28[22]);
            }
            break;
        case 1:
            if (D_80744520 >= 2) {
                _sprintf(strBuf, "%d %s", D_80744520, D_80033F28[25]);
            } else {
                _sprintf(strBuf, "%d %s", D_80744520, D_80033F28[24]);
            }
            break;
        case 2:
            if (D_80744520 >= 2) {
                _sprintf(strBuf, "%d %s", D_80744520, D_80033F28[27]);
            } else {
                _sprintf(strBuf, "%d %s", D_80744520, D_80033F28[26]);
            }
            break;
        case 3:
            _sprintf(strBuf, "%d", D_80744520);
            break;
        }
        dl = textDrawStringVtx(dl, 1, posX * 4.0f, textY, strBuf, 0x81);
    }
    if (state->unkC < -241.0f) {
        gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
        menuComputeElementPosition(state, 160.0f, 40.0f, &posX, &posY, 2, 0, 1.5f);
        posY = posY + 480.0f;
        dl = textDrawStringVtx(dl, 1, 0x280, posY * 4.0f, D_80033F28[28], 0x81);
        menuComputeElementPosition(state, 160.0f, 180.0f, &posX, &posY, 2, 0, 1.5f);
        posY = (posY + 480.0f) * 4.0f;
        posX = (posX + 16.0f) * 4.0f;
        id = D_80033FAD * 6 + D_80744534 * 2 + 0x98;
        gDPPipeSync(dl++);
        gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
        dl = renderRotatedSprite(dl, id, 0, 2, 0x20, 0x40, posX - 128.0, posY, 4.0f, -4.0f, 0, 0.0f);
        gDPPipeSync(dl++);
        dl = renderRotatedSprite(dl, ++id, 0, 2, 0x20, 0x40, posX, posY, 4.0f, -4.0f, 0, 0.0f);
    }
    return dl;
}

typedef struct Menu6_Sub174 { // customState of the character-select kong actors
    Actor *unk0; // parent menu actor
    s32 unk4;
    s8 unk8;
} Menu6_Sub174;
extern s16 D_8003386C[];
extern s8 D_80033FAE;
extern s8 D_80033FAF;
extern s8 D_8074451C;
extern s16 D_80744544;
extern u8 D_80720D5C;
extern u8 D_80720D80;
extern u8 D_807211AC;

void menuInitCharacterSelect(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    s32 flag;
    s32 i;
    Menu6_Sub174 *sub;

    menuUpdateCameraPositions();
    D_80033FAF = 1;
    flag = 0x1D;
    for (i = 1; i < 5; i++) {
        if (flagGet(flag, 1) != 0) {
            D_80033FAF |= 1 << i;
        }
        flag += 1;
    }
    if (D_80744544 & 1) {
        D_80033FAF |= 0x20;
    }
    D_80033FAE = 0;
    D_80033FAD = 0;
    if (D_8076A104 != 0 && D_8074451C >= 5) {
        D_8074451C = 0;
    }
    state->selection = D_8074451C;
    for (i = 0; i != 4; i++) {
        actorSpawn(0x151, D_8003386C[D_8076A0E4[i] & 0x7F]);
        {
            s16 *q = ((MenuActorExt *)gSpawnedActor)->unk17C;
            *q = D_8003386C[D_8076A0E4[i] & 0x7F];
        }
        gSpawnedActor->state = i;
        gSpawnedActor->unk155 = D_8076A0E4[i] & 0x7F;
        sub = gSpawnedActor->customState;
        sub->unk0 = actor;
        sub->unk8 = 0;
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

    if (state->unk0 == 0.0 && (buttons & 1)) {
        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
        state->unk16 = 0;
        state->nextScreen = 7;
    }
    menuUpdateItemTransition(actor, state, 0);
    menuUpdateCameraPositions();
    gGlobalPauseFlags &= ~0x10;
    gGlobalPauseFlags |= 0x10000;
}

extern u8 D_80033878;
extern u8 D_80033F20[];
extern s16 D_80744524[];
extern s8 D_8076A105;

Gfx *menuDrawMultiplayerResults(Actor *actor, Gfx *dl) {
    MenuScreenState *state;
    s32 step;
    s32 i;
    s16 x;
    f32 textX;
    f32 textY1;
    f32 textY2;
    u8 *q;
    s16 y;
    s16 scaledY2;
    u8 strBuf[200];
    s32 sel;

    state = actor->customState;
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    menuComputeElementPosition(state, 160.0f, 45.0f, &textX, &textY1, 2, 0, 1.8f);
    menuComputeElementPosition(state, 160.0f, 185.0f, &textX, &textY2, 2, 0, 1.8f);
    y = (s32)(textY1 * 4.0);
    scaledY2 = (s32)(textY2 * 4.0);
    step = 0x11D / D_80033878;
    x = step * 2 + 0x46;
    step *= 4;
    q = D_80033F20;
    i = 0;
    if (D_80033878 > 0) {
        do {
            _sprintf(strBuf, "P %d", *q + 1);
            dl = hudDrawScaledText(dl, x, y, 0.6f, strBuf);
            sel = i == D_8076A105;
            dl = hudDrawScaledText(dl, x, (s16)(y + 0x30), 0.6f, D_80033F28[0x1D + sel]);
            _sprintf(strBuf, "%d", D_80744524[*q]);
            dl = hudDrawScaledText(dl, x, scaledY2, 0.6f, strBuf);
            i += 1;
            q += 1;
            dl = dl; // FAKE: no-op self-assignment steers as1 order of q++ vs dl move
            x += step;
        } while (i < D_80033878);
        if (i) {} // FAKE: dead if keeps loop counter live after the loop (as1 order)
    }
    return hudDrawScaledText(dl, 0x280, (s16)(scaledY2 - 0x50), 0.6f, D_80033F28[0x1F]);
}


extern u8 D_8003387C[];
extern u8 D_80033F24[];

void menuInitMultiplayerResults(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    s32 i;
    s8 t;
    s32 n;
    Menu6_Sub174 *sub;

    for (i = 0; i < 4; i++) {
        t = D_8076A0E4[i];
        if (!(t & 0x80)) {
            n = D_80033878;
            D_8003387C[n] = t & 0x7F;
            D_80033F20[n] = i;
            D_80033F24[i] = n;
            if ((n ^ 0) == D_8076A105) { // FAKE: no-op `^ 0` steers codegen
                D_80744524[i] += 1;
            }
            D_80033878 = n + 1;
        }
    }
    menuUpdateCameraPositions();
    state->selection = 0;
    for (i = 0; i < D_80033878; i++) {
        actorSpawn(0x151, D_8003386C[D_8003387C[i]]);
        {
            s16 *q = ((MenuActorExt *)gSpawnedActor)->unk17C;
            *q = D_8003386C[D_8003387C[i]];
        }
        gSpawnedActor->state = D_80033F20[i] | 0x80;
        gSpawnedActor->unk155 = D_8003387C[i];
        sub = gSpawnedActor->customState;
        sub->unk0 = actor;
        sub->unk8 = (i == D_8076A105) + 1;
    }
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
}


typedef struct Menu6B_Pair {
    f32 a;
    f32 b;
} Menu6B_Pair;
extern s32 D_800338B4[];
extern Menu6B_Pair D_80033894[];


void menuCharacterSelectUpdateActor(void) {
    s32 step;
    Menu6B_Pair *row;
    MenuScreenState *parentState;
    s32 sel;
    f32 posX;
    f32 posY;
    s8 shouldDespawn;
    s8 kong;
    s16 idx;
    s16 *actorTypePtr;
    Menu6_Sub174 *sub174;

    sub174 = gCurrentActor->customState;
    parentState = sub174->unk0->customState;
    shouldDespawn = 0;
    func_806BF920();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->sub4->scaleX = 2.0f * gCurrentActor->sub4->scaleX;
        gCurrentActor->sub4->scaleY = 2.0f * gCurrentActor->sub4->scaleY;
        gCurrentActor->sub4->scaleZ = 2.0f * gCurrentActor->sub4->scaleZ;
        kong = sub174->unk8;
        actorScriptStart(gCurrentActor, D_800338B4[(s16)(kong * 6) + (gCurrentActor->unk155 & 0xF)]);
        playerKongStopSoundByState(gCurrentActor);
        gCurrentActor->flags |= 0x1000;
        sub174->unk4 = D_8076A100[gCurrentActor->state & 0xF];
        actorConfigApplyAnimFrameByType(gCurrentActor, gCurrentActor->unk155 + 2, D_8076A100[gCurrentActor->state & 0xF]);
    }
    sel = gCurrentActor->state;
    if (!(gCurrentActor->state & 0x80)) {
        if (sub174->unk4 != D_8076A100[gCurrentActor->state]) {
            actorConfigApplyAnimFrameByType(gCurrentActor, gCurrentActor->unk155 + 2, D_8076A100[gCurrentActor->state]);
            sub174->unk4 = D_8076A100[gCurrentActor->state];
        }
        idx = D_8076A0E4[gCurrentActor->state] & 0x7F;
        if (idx != gCurrentActor->unk155) {
            actorTypePtr = &D_8003386C[idx];
            actorSpawn(0x151, *actorTypePtr);
            {
                s16 *q = ((MenuActorExt *)gSpawnedActor)->unk17C;
                *q = *actorTypePtr;
            }
            gSpawnedActor->state = gCurrentActor->state;
            gSpawnedActor->unk155 = idx;
            {
                Menu6_Sub174 *sub = gSpawnedActor->customState;
                sub->unk0 = sub174->unk0;
            }
            shouldDespawn = 1;
            if (gCurrentActor->state != 0) {} // FAKE: extra reference of the unk154 value; recolours the shared A->unk154 candidate (t0) and the PRE reload position
            if (sub174->unk0->flags && sub174->unk0->flags) {} // FAKE: repeated dead load steers uopt lifetimes and the ugen temporary ring
        }
        row = &D_80033894[gCurrentActor->state];
        menuComputeElementPosition(parentState, row->a, row->b, &posX, &posY, 2, 0, 1.8f);
        gCurrentActor->x = gPrimaryPlayerActor->x + (posX - 160.0f);
        gCurrentActor->y = (gPrimaryPlayerActor->y - (posY - 120.0f)) - 20.0f;
        gCurrentActor->z = gPrimaryPlayerActor->z - 300.0f;
        if (D_8076A0E4[gCurrentActor->state] & 0x80) {
            gCurrentActor->flags &= ~4;
        } else {
            gCurrentActor->flags |= 4;
        }
    } else {
        idx = D_80033F24[sel & 0xF];
        step = 0x140 / D_80033878;
        menuComputeElementPosition(parentState, 160.0f, 150.0f, &posX, &posY, 2, 0, 1.8f);
        posX = (idx * step + (step >> 1)) - 0xA0;
        posX = posX * 0.78;
        gCurrentActor->x = gPrimaryPlayerActor->x + posX;
        gCurrentActor->y = (gPrimaryPlayerActor->y - (posY - 120.0f)) + 16.0f;
        gCurrentActor->z = gPrimaryPlayerActor->z - 300.0f;
    }
    if (parentState->unk0 > 1.0f) {
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
    s8 flag = 0;

    menuCheckCheatCodeSequence();
    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            switch (state->selection) {
            case 0:
                if (!(D_80033670 & 0x10) && (buttons & 0x10)) {
                    gAudioOutputMode++;
                    if (gAudioOutputMode >= 3) {
                        gAudioOutputMode = 0;
                    }
                    flag = 1;
                } else if (!(D_80033670 & 0x20) && (buttons & 0x20)) {
                    gAudioOutputMode--;
                    if (gAudioOutputMode < 0) {
                        gAudioOutputMode = 2;
                    }
                    flag = 1;
                }
                if (flag != 0) {
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
                    flag = 1;
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
                state->unk16 = 0;
                state->nextScreen = 1;
            } else {
                menuHandleScrollInput(state, 4, buttons);
            }
        }
        menuUpdateScrollAnimation(state, 4);
    }
    menuUpdateItemTransition(actor, state, 1);
    if (flag != 0) {
        sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
}

extern s16 D_80033674;
extern s8 gAudioOutputMode;

Gfx *menuFormatOptionValues(Actor *actor, Gfx *dl) {
    MenuScreenState *state;
    u32 selectedOption;
    f32 pad5C;
    f32 posX;
    f32 posY;
    f32 offsetVal;
    s16 pad;
    s16 posYShort;
    u8 strBuf[12];

    state = actor->customState;
    gGlobalPauseFlags &= ~0x10;
    menuComputeElementPosition(state, 160.0f, 20.0f, &posX, &posY, 2, 0, 1.5f);
    dl = menuDrawScrollSelector(
        textDrawStringVtx(dl, 1, 0x280, posY * 4.0f, D_80033F28[0x20], 0x81),
        state,
        D_80033F28 + 0x21,
        4,
        &selectedOption,
        1,
        &offsetVal,
        80.0f,
        -1
    );
    D_80033674 = 0x3E8;
    menuComputeElementPosition(state, 160.0f, 150.0f, &posX, &posY, 2, 0, 1.5f);
    posYShort = (s16)(posY * 4.0f);
    posX = (posX - offsetVal) * 4.0f;

    switch (selectedOption) {
    case 0:
        dl = textDrawStringVtx(dl, 1, posX, posYShort, D_80033F28[gAudioOutputMode + 0x25], 0x81);
        break;
    case 1:
    case 2:
        dl = textDrawStringVtx(dl, 1, posX, posYShort, D_80033F28[0x28], 0x81);
        _sprintf(strBuf, "%d", ((selectedOption == 1 ? gSfxVolume : gMusicVolume) + 1) >> 1);
        dl = textDrawStringVtx(dl, 1, posX, posYShort + 0x78, strBuf, 0x81);
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

extern s8 D_800338FC;
extern s8 D_807444C0;
extern s8 D_8074452C;
extern u8 D_80744530;
extern u8 sLanguageIndex;
extern u16 D_807ECD66;

void menuHandleGameOptionsInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;
    s8 flag = 0;
    s32 i;

    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            switch (state->selection) {
            case 0:
                if ((buttons & 0x30) && !(D_80033670 & 0x30)) {
                    D_807444C0 = 1 - D_807444C0;
                    flag = 1;
                }
                break;
            case 1:
                if ((buttons & 0x30) && !(D_80033670 & 0x30)) {
                    D_8074452C = 1 - D_8074452C;
                    flag = 1;
                }
                break;
            case 2:
                if (buttons & 0x100) {
                    eepromInitConfigs(0xFF);
                    sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
                break;
            case 3:
                if ((buttons & 0x30) && !(D_80033670 & 0x30)) {
                    D_80744530 = 1 - D_80744530;
                    flag = 1;
                }
                break;
            case 4:
                if ((buttons & 0x10) && !(D_80033670 & 0x10)) {
                    sLanguageIndex += 1;
                    flag = 1;
                }
                if ((buttons & 0x20) && !(D_80033670 & 0x20)) {
                    sLanguageIndex -= 1;
                    flag = 1;
                }
                sLanguageIndex &= 3;
                if (flag != 0) {
                    for (i = 0; i != 0x65; i++) {
                        heapFreeDeferred(D_80033F28[i]);
                    }
                    heapFreeDeferred(D_80033F28);
                    menuLoadTextTable();
                }
                break;
            }
            if (buttons & 2) {
                eepromSetField(0x1F, 0, 0, 0, sLanguageIndex);
                eepromSetField(0x20, 0, 0, 0, D_80744530);
                func_8060DEA8();
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->nextScreen = 1;
            } else {
                menuHandleScrollInput(state, D_800338FC, buttons);
            }
        }
        menuUpdateScrollAnimation(state, D_800338FC);
    }
    menuUpdateItemTransition(actor, state, 1);
    if (D_807ECD66 & 0xC) {
        D_80744544 ^= 0x100;
    }
    if (flag != 0) {
        sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
}


extern s16 D_80033674;

Gfx *menuDrawGameOptions(Actor *actor, Gfx *dl) {
    MenuScreenState *state = actor->customState;
    u32 selectedOption;
    f32 posX;
    f32 posY;
    f32 offsetVal;
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
        textDrawStringVtx(dl, 1, 0x280, posY * 4.0f, D_80033F28[0x29], 0x81),
        state,
        D_80033F28 + 0x2A,
        D_800338FC,
        &selectedOption,
        1,
        &offsetVal,
        80.0f,
        -1
    );
    D_80033674 = 0x3E8;
    menuComputeElementPosition(state, 160.0f, 150.0f, &posX, &posY, 2, 0, 1.5f);
    y = (s16)(posY * 4.0f);
    posX = (posX - offsetVal) * 4.0f;

    switch (selectedOption) {
    case 0:
        dl = textDrawStringVtx(dl, 1, posX, y + 0x40, D_80033F28[D_807444C0 + 0x2F], 0x81);
        break;
    case 1:
        dl = textDrawStringVtx(dl, 1, posX, y + 0x40, D_80033F28[D_8074452C + 0x31], 0x81);
        break;
    case 2:
        D_80033674 = 0;
        break;
    case 3:
        dl = textDrawStringVtx(dl, 1, posX, y + 0x40, D_80033F28[D_80744530 + 0x34], 0x81);
        break;
    case 4:
        dl = textDrawStringVtx(dl, 1, posX, y + 0x40, D_80033F28[0x33], 0x81);
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

typedef struct Menu3M7_Row8 {
    s16 a;
    s16 b;
    s8 c;
    s8 d;
    s8 e;
    s8 f;
} Menu3M7_Row8;

extern s8 D_800339A8;
extern u8 D_80744514;
extern s16 D_80033900[][2];
extern Menu3M7_Row8 D_80033938[];
extern s16 D_80033978[][2];
extern s8 D_80033988[];
extern s16 D_80033998[];
extern s8 D_8074453C[];

extern s8 D_80744540;

void menuHandleCheatsInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;
    s8 flag = 0;
    s8 cnt;
    s8 sel;
    s8 idx;
    s8 *p;

    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            idx = state->selection;
            cnt = D_80033988[idx];
            if (cnt > 0) {
                if ((buttons & 0x10) && !(D_80033670 & 0x10) && cnt != 1) {
                    flag = 1;
                    do {
                        D_8074453C[idx] += 1;
                        if (D_8074453C[idx] >= cnt) {
                            D_8074453C[idx] = 0;
                        }
                    } while (!(D_80033998[idx] & (1 << D_8074453C[idx])));
                }
                if ((buttons & 0x20) && !(D_80033670 & 0x20) && cnt != 1) {
                    do {
                        D_8074453C[idx] -= 1;
                        if (D_8074453C[idx] < 0) {
                            D_8074453C[idx] = cnt - 1;
                        }
                    } while (!(D_80033998[idx] & (1 << D_8074453C[idx])));
                    flag = 1;
                }
                sel = D_8074453C[idx];
                if (buttons & 1) {
                    switch (idx) {
                    case 0:
                        if (sel != 0xD) {
                            menuTransitionRequestTypeB(D_80033900[sel][0], D_80033900[sel][1]);
                        } else {
                            menuTransitionToCreditsOrMap28(1);
                        }
                        D_80744514 = 3;
                        break;
                    case 1:
                        switch (D_80033978[sel][0]) {
                        case 0xBF:
                            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                            state->unk16 = 0;
                            state->nextScreen = 0xC;
                            D_800339A8 = 0;
                            break;
                        case 0xB8:
                            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                            state->unk16 = 0;
                            state->nextScreen = 0xC;
                            D_800339A8 = 1;
                            break;
                        default:
                            menuSetupPlayerInventory(D_80033978[sel][0], 0, D_80033978[sel][1], 3, 3, 1, 3);
                            D_80744514 = 5;
                            break;
                        }
                        break;
                    case 2:
                        menuSetupPlayerInventory(D_80033938[sel].a, 0, D_80033938[sel].b, D_80033938[sel].c, D_80033938[sel].d, D_80033938[sel].e, D_80033938[sel].f);
                        D_80744514 = 4;
                        break;
                    }
                }
                if (buttons & 0x100) {
                    if (idx == 3) {
                        D_80744544 ^= 1;
                        flag = 1;
                    } else if (idx == 4) {
                        flag = 1;
                        D_80744544 ^= 1 << (sel + 1);
                        if (sel == 6) {
                            if (D_80744544 & (1 << (sel + 1))) {
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
                state->unk16 = 0;
                state->nextScreen = 1;
                D_80033698 = 3;
            } else {
                menuHandleScrollInput(state, 5, buttons);
            }
        }
        menuUpdateScrollAnimation(state, 5);
    }
    menuUpdateItemTransition(actor, state, 1);
    if (flag != 0) {
        sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
}

extern s8 D_80033990[];
extern s16 D_800339A4;
extern s8 D_8074453D;
extern s8 D_8074453E;

Gfx *menuDrawCheats(Actor *actor, Gfx *dl) {
    MenuScreenState *state = actor->customState;
    u32 optIdx;
    f32 posX;
    f32 posY;
    f32 scrollOffset;
    s16 sel;
    s16 y;
    u8 strBuf[0xC8];

    gGlobalPauseFlags &= ~0x10;
    menuComputeElementPosition(state, 160.0f, 20.0f, &posX, &posY, 2, 0, 1.5f);
    y = (s16)(posY * 4.0f);
    dl = menuDrawScrollSelector(
        textDrawStringVtx(dl, 1, 0x280, y, D_80033F28[0x36], 0x81),
        state,
        D_80033F28 + 0x37,
        5,
        &optIdx,
        1,
        &scrollOffset,
        140.0f,
        D_800339A4
    );
    _sprintf(strBuf, "%d", D_80033990[optIdx]);
    dl = textDrawStringVtx(dl, 3, 0x2A8, y + 0xC8, strBuf, 1);
    D_80033674 = 0x3E8;
    menuComputeElementPosition(state, 160.0f, 160.0f, &posX, &posY, 1, 0, 1.5f);
    y = (s16)(posY * 4.0f);
    posX = (posX - scrollOffset) * 4.0f;

    if (D_80033988[optIdx] > 0) {
        switch (optIdx) {
        case 0:
            dl = textDrawStringVtx(dl, 1, posX, y + 0x40, D_80033F28[D_8074453C[0] + 0x3C], 0x81);
            break;
        case 1:
            dl = textDrawStringVtx(dl, 1, posX, y + 0x40, D_80033F28[D_8074453D + 0x52], 0x81);
            break;
        case 2:
            dl = textDrawStringVtx(dl, 1, posX, y + 0x40, D_80033F28[D_8074453E + 0x4A], 0x81);
            break;
        case 3:
            _sprintf(strBuf, "%s:%s", D_80033F28[0x5E], D_80033F28[(D_80744544 & 1) + 0x31]);
            dl = textDrawStringVtx(dl, 1, posX, y + 0x40, strBuf, 0x81);
            break;
        case 4:
            sel = D_80744540;
            _sprintf(strBuf, "%s:%s", D_80033F28[sel + 0x56], D_80033F28[(((1 << (sel + 1)) & D_80744544) != 0) + 0x31]);
            dl = textDrawStringVtx(dl, 1, posX, y + 0x40, strBuf, 0x81);
            break;
        }
    } else {
        dl = textDrawStringVtx(dl, 1, posX, y + 0x40, (u8 *)"???", 0x81);
    }
    return dl;
}

extern s8 D_8076A0DA;


void menuInitCheats(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;
    s32 j;
    s32 i;
    s8 n;

    state->selection = D_8076A0DA;
    switch (D_80744514) {
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
    D_80033988[0] = 0xE;
    D_80033988[1] = 4;
    D_80033988[2] = 8;
    D_80033988[3] = 1;
    D_80033988[4] = 7;
    D_80033998[0] = -1;
    D_80033998[1] = -1;
    D_80033998[2] = -1;
    D_80033998[3] = -1;
    D_80033998[4] = -1;
    D_800339A4 = 0;
    if (flagGet(1, 1) != 0) {
        D_800339A4 |= 1;
        D_80033998[0] = 3;
        i = 4;
        j = 2;
        do {
            if (flagGet(j, 1) != 0) {
                D_80033998[0] |= i;
            }
            i *= 2;
            j += 1;
        } while (j != 0xE);
    } else {
        D_80033988[0] = 0;
    }
    if (flagGet(0xE, 1) != 0) {
        j = 0xF;
        D_800339A4 |= 2;
        D_80033998[1] = 0;
        i = 1;
        do {
            if (flagGet(j, 1) != 0) {
                D_80033998[1] |= i;
            }
            i *= 2;
            j += 1;
        } while (j != 0x13);
    } else {
        D_80033988[1] = 0;
    }
    if (flagGet(0x13, 1) != 0) {
        j = 0x14;
        D_800339A4 |= 4;
        D_80033998[2] = 0;
        i = 1;
        do {
            if (flagGet(j, 1) != 0) {
                D_80033998[2] |= i;
            }
            i *= 2;
            j += 1;
        } while (j != 0x1C);
    } else {
        D_80033988[2] = 0;
    }
    if (flagGet(0x21, 1) == 0) {
        D_80033988[3] = 0;
    } else {
        D_800339A4 |= 8;
    }
    if (flagGet(0x22, 1) == 0) {
        D_80033988[4] = 0;
    } else {
        D_800339A4 |= 0x10;
    }
    for (i = 0; i != 5; i++) {
        n = D_80033988[i];
        if (n > 0) {
            s16 m = D_80033998[i];
            if (!((1 << D_8074453C[i]) & m)) {
                do {
                    D_8074453C[i] += 1;
                    if (D_8074453C[i] >= n) {
                        D_80033988[i] = 0;
                        D_8074453C[i] = 0;
                        n = D_80033988[i];
                    }
                } while (n > 0 && !((1 << D_8074453C[i]) & m));
            }
        }
    }
}

typedef struct MenuHighScoreEntry {
    s16 score;
    u8 initial0;
    u8 initial1;
    u8 initial2;
    u8 initial3;
} MenuHighScoreEntry;

extern MenuHighScoreEntry D_80744548[];
extern MenuHighScoreEntry D_80744568[];


void menuLoadHighScores(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        D_80744548[i].score = eepromGetField(0x19, 0, i, 0);
        D_80744548[i].initial0 = eepromGetField(0x16, 0, i, 0);
        D_80744548[i].initial1 = eepromGetField(0x17, 0, i, 0);
        D_80744548[i].initial2 = eepromGetField(0x18, 0, i, 0);
        D_80744548[i].initial3 = 0;
        D_80744568[i].score = eepromGetField(0x1D, 0, i, 0);
        D_80744568[i].initial0 = eepromGetField(0x1A, 0, i, 0);
        D_80744568[i].initial1 = eepromGetField(0x1B, 0, i, 0);
        D_80744568[i].initial2 = eepromGetField(0x1C, 0, i, 0);
        D_80744568[i].initial3 = 0;
    }
}

void menuSaveHighScores(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        eepromSetField(0x19, 0, i, 0, D_80744548[i].score);
        eepromSetField(0x16, 0, i, 0, D_80744548[i].initial0);
        eepromSetField(0x17, 0, i, 0, D_80744548[i].initial1);
        eepromSetField(0x18, 0, i, 0, D_80744548[i].initial2);
        eepromSetField(0x1D, 0, i, 0, D_80744568[i].score);
        eepromSetField(0x1A, 0, i, 0, D_80744568[i].initial0);
        eepromSetField(0x1B, 0, i, 0, D_80744568[i].initial1);
        eepromSetField(0x1C, 0, i, 0, D_80744568[i].initial2);
    }
    func_8060DEA8();
}

typedef struct MenuM8_PosPair {
    s16 unk0;
    s16 unk2;
} MenuM8_PosPair;

extern s8 D_80033F60;
extern s8 D_800339A8;
extern s8 D_80033F61;
extern s8 D_800339C0;
extern MenuM8_PosPair D_800339B8[];

void menuHandleHighScoreNameEntryInput(Actor *actor, s32 buttons) {
    MenuScreenState *state = actor->customState;
    s8 holdFrames;
    MenuHighScoreEntry *table;
    u32 pressed;
    s32 pad;
    u8 *p;
    if (D_800339A8 == 0) {
        table = D_80744548;
    } else {
        table = D_80744568;
    }
    if (state->unk0 == 0.0f) {
        if (D_80033F60 < 0) {
            if (buttons & 1) {
                menuSetupPlayerInventory(D_800339B8[D_800339A8].unk0, 0, D_800339B8[D_800339A8].unk2, 3, 3, 1, 3);
                D_80744514 = D_800339A8 + 6;
            }
            if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->nextScreen = 0xA;
            }
        } else {
            if (buttons & 0xC) {
                holdFrames = D_800339C0 + 1;
            } else {
                holdFrames = 0;
            }
            pressed = 0;
            if (holdFrames == 1 || (D_800339C0 = holdFrames, holdFrames >= 0x10)) { // FAKE: comma stores the counter only on the second test; a separate if reorders the store
                if (D_80033F61 && D_80033F61) {} // FAKE: dead test steers register colouring (frame counter / D_80033F61 candidates)
                D_800339C0 = holdFrames;
                pressed = buttons;
                if (holdFrames >= 0x10) {
                    holdFrames = 0xF;
                    if (D_80033F60 == 0xF) {} // FAKE: constant 15 becomes a coloured web (v1), leaving gFrameCounter a ring temp
                    D_800339C0 = holdFrames;
                    if (D_80033F60 == 0xF) {} // FAKE: second reference to the 15 web
                    if (!(gFrameCounter & 1)) {
                        pressed = 0;
                    }
                }
            }
            p = (u8 *)table + D_80033F60 * 6 + D_80033F61 + 2; // FAKE: byte-offset name pointer keeps the multu-free address chain (Q0303)
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
                D_80033F61 += 1;
                if (D_80033F61 == 3) {
                    D_80033F60 = -1;
                    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
                    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
                    menuSaveHighScores();
                }
            } else if ((buttons & 2) && D_80033F61 > 0) {
                D_80033F61 -= 1;
            }
        }
    }
    menuUpdateItemTransition(actor, state, 1);
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/D_80033BE0.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/D_80033BE4.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/D_80033BE8.s")

extern s8 D_80033F60;
extern s8 D_80033F61;
extern s16 D_80744518;
extern u8 *D_800339AC[];

Gfx *menuDrawHighScoreTable(Actor *actor, Gfx *dl) {
    MenuScreenState *state;
    f32 posX;
    f32 posY;
    s32 ft4;
    s32 pad;
    MenuHighScoreEntry *scoreTable;
    u8 strBuf[0xC8];
    s16 yPos;
    s16 i;

    state = actor->customState;
    gGlobalPauseFlags &= ~0x10;
    menuComputeElementPosition(state, 160.0f, 20.0f, &posX, &posY, 2, 0, 1.0f);
    dl = textDrawStringVtx(dl, 1, 0x280, (s16)(posY * 4.0), D_80033F28[D_800339A8 + 0x5F], 0x81);
    menuComputeElementPosition(state, 160.0f, 205.0f, &posX, &posY, 2, 0, 1.0f);
    i = 0; // FAKE: loop counter i doubles as the message-drawn flag; a separate flag local recolours
    yPos = (s16)(posY * 4.0);
    if (D_80033F60 >= 0) {
        _sprintf(strBuf, "%s", D_80033F28[0x63]);
        i = 1;
    } else if (D_80033F60 == -2) {
        _sprintf(strBuf, "%s %d.", D_80033F28[0x64], D_80744518);
        i = 1;
    }
    if (i != 0) {
        dl = hudDrawScaledText(dl, 0x280, yPos, 0.6f, strBuf);
    }
    menuComputeElementPosition(state, 20.0f, 120.0f, &posX, &posY, 2, 0, 2.0f);
    yPos = 0xC8;
    ft4 = (s16)(posX * 4.0f);
    if (D_800339A8 == 0) {
        scoreTable = D_80744548;
    } else {
        scoreTable = D_80744568;
    }
    for (i = 0; i < 5; i++) {
        _sprintf(strBuf, "%d.", i + 1);
        dl = textDrawStringVtx(dl, 1, (s16)(ft4 + 0x50), yPos, strBuf, 1);
        _sprintf(strBuf, "%c %c %c", scoreTable[i].initial0, scoreTable[i].initial1, scoreTable[i].initial2);
        dl = textDrawStringVtx(dl, 0x81, (s16)(ft4 + 0x118), yPos, strBuf, 1);
        _sprintf(strBuf, "%d", scoreTable[i].score);
        dl = textDrawStringVtx(dl, 0x81, (s16)(0x3E8 - ft4), yPos, strBuf, 1);
        if (i == D_80033F60 && (gFrameCounter & 0x1F) < 0x14) {
            dl = textDrawStringVtx(dl, 0x81, (s16)(ft4 + 0x118), yPos + 0x34, D_800339AC[D_80033F61], 1);
        }
        yPos += 0x6C;
    }
    return dl;
}

extern s8 D_80033F60;

void menuInitHighScores(Actor *actor, s32 unused) {
    MenuScreenState *state = actor->customState;

    if (D_80033F60 == -1) {
        menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
        menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    }
}

extern s8 D_80033F61;
extern s16 D_80744518;

void menuInsertHighScore(void) {
    MenuHighScoreEntry *table;
    s32 i;
    s32 j;

    if (D_800339A8 == 0) {
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
                    table[j].initial0 = table[j - 1].initial0;
                    table[j].initial1 = table[j - 1].initial1;
                    table[j].initial2 = table[j - 1].initial2;
                    j--;
                } while (j > i);
            }
            table[i].score = D_80744518;
            table[i].initial0 = 0x2E;
            table[i].initial1 = 0x2E;
            table[i].initial2 = 0x2E;
            D_80033F60 = i;
            D_80033F61 = 0;
            return;
        }
    }
    D_80033F60 = -1;
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

extern u8 D_800339C4[];
extern f32 D_80033F44;

Gfx *menuDrawScrollSelector(Gfx *dl, MenuScreenState *state, u8 **strTable, s32 itemCount, u32 *outIdx, s16 textFlag, f32 *outOffset, f32 posY, s16 enabledMask) {
    s32 idx = state->selection;
    f32 v;
    f32 posX;
    f32 posYLocal;
    s16 y;

    if (state->unk4 != 0.0f) {
        if (state->unk4 > 0.5f) {
            idx++;
        }
        if (idx >= itemCount) {
            idx = 0;
        }
    }
    v = state->unk4 - 0.5f;
    if (v < 0.0f) {
        v = -v;
    }
    v = 0.5f - v;
    v = v * 800.0f;
    if (D_80033F44 < 0.0f) {
        v = -v;
    }
    menuComputeElementPosition(state, v + 160.0, posY, &posX, &posYLocal, 2, 0, 2.0f);
    y = (s16)(posYLocal * 4.0f);
    if (enabledMask & (1 << idx)) {
        dl = textDrawStringVtx(dl, textFlag, posX * 4.0f, y, strTable[idx], 0x81);
    } else {
        dl = textDrawStringVtx(dl, textFlag, posX * 4.0f, y, D_800339C4, 0x81);
    }
    *outOffset = v;
    *outIdx = idx;
    return dl;
}

extern f32 D_80033F68[];
extern f32 D_80033F80[];
extern f32 D_80033F98[];

Gfx *menuSetElementCoordinates(Gfx *dl, s32 elemIdx, f32 posX, f32 posY, f32 scale) {
    elemIdx &= 0x7F;
    posX *= 4.0f;
    posY *= 4.0f;
    D_80033F68[elemIdx] = posX - 32.0;
    D_80033F80[elemIdx] = posY - 100.0;
    D_80033F98[elemIdx] = scale * 1.333;
    return dl;
}

extern s8 D_80033F50;

void menuUpdateItemTransition(void *actor, MenuScreenState *state, s32 hasSfx) {
    if (!state->unk16) {
        state->unk0 += 0.13f;
        if (state->unk0 > 1.3f) {
            state->unk0 = 1.0f;
            state->unk12 = state->nextScreen;
            state->unk16 = -1;
            menuUpdateStateDispatch(actor, 0, 0, 0);
            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        }
    } else {
        if (state->unk0 > 0.0f) {
            state->unk0 -= 0.2f;
            if (state->unk0 < 0.0f) {
                state->unk0 = 0.0f;
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
        state->unk4 = 1.0f;
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
        state->unk4 += D_80033F44;
        if (state->unk4 >= 1.0f) {
            state->unk4 = 0.0f;
            state->selection++;
            if (state->selection >= itemCount) {
                state->selection -= itemCount;
            }
            D_80033F44 = 0.0f;
        }
    } else if (D_80033F44 < 0.0f) {
        state->unk4 += D_80033F44;
        if (state->unk4 <= 0.0f) {
            D_80033F44 = 0.0f;
            state->unk4 = 0.0f;
        }
    }
}

typedef struct Menu10_Sub174 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char padC[0x23C - 0xC];
    u16 unk23C;
} Menu10_Sub174;

extern u8 D_8076A0D0[];
extern s8 D_80033738;
extern f32 D_8003369C;
extern void *D_80033F34;
extern s8 D_80033F30;

void menuInit(void) {
    MenuScreenState *sub = gCurrentActor->customState;
    Menu10_Sub174 *actorState = gPrimaryPlayerActor->customState;
    s32 i;

    if (!(gCurrentActor->flags & 0x10)) {
        gGlobalPauseFlags |= 0x10;
        menuLoadTextTable();
        menuLoadHighScores();
        if (D_80744514 == 0) {
            for (D_8076A0D0[0] = 0, i = 0; i < 12; i += 4) {
                D_8076A0D1[i] = 0;
                D_8076A0D1[i + 1] = 0;
                D_8076A0D1[i + 2] = 0;
                D_8076A0D1[i + 3] = 0;
            }
        } else {
            gPrimaryPlayerActor->x = 700.0f;
            gPrimaryPlayerActor->y = 0.0f;
            gPrimaryPlayerActor->z = 70.0f;
        }
        D_80033F50 = 0;
        D_80033738 = 0;
        D_80033F60 = -1;
        D_8003369C = 0.0f;
        actorSpawn(0x14D, 0xD7);
        gSpawnedActor->x = gPrimaryPlayerActor->x;
        gSpawnedActor->y = gPrimaryPlayerActor->y;
        gSpawnedActor->z = gPrimaryPlayerActor->z;
        gSpawnedActor->yaw = gPrimaryPlayerActor->yaw;
        if (D_80744514 != 0) {
            D_80033738 = 0x15;
            gPrimaryPlayerActor->state = 0x85;
            gPrimaryPlayerActor->unk155 = 0;
            actorScriptStart(gPrimaryPlayerActor, 0x347);
            gPrimaryPlayerActor->unk155 = 6;
            func_8061B650(gCamActor);
            D_80033F3C = 1.0f;
            actorState->unk23C = 0x50;
        }
        switch (D_80744514) {
        case 1:
            sub->unk12 = 1;
            break;
        case 2:
            sub->unk12 = 0xB;
            break;
        case 3:
        case 4:
        case 5:
            sub->unk12 = 0xA;
            break;
        case 6:
        case 7:
            sub->unk12 = 0xC;
            D_800339A8 = D_80744514 - 6;
            menuInsertHighScore();
            break;
        default:
            actorScriptStart(gSpawnedActor, 0x349);
            gPrimaryPlayerActor->state = 0x86;
            gPrimaryPlayerActor->unk155 = 0;
            sub->unk12 = 0;
            break;
        }
        gPrimaryPlayerActor->sub4->scaleX = gPrimaryPlayerActor->sub4->scaleX * 0.8;
        gPrimaryPlayerActor->sub4->scaleY = gPrimaryPlayerActor->sub4->scaleY * 0.8;
        gPrimaryPlayerActor->sub4->scaleZ = gPrimaryPlayerActor->sub4->scaleZ * 0.8;
        sub->selection = 0;
        sub->unkC = 0;
        sub->unkE = 0;
        sub->unk16 = 1;
        sub->unk10 = 0;
        sub->unk0 = 1.0f;
        sub->unk4 = 0.0f;
        D_80033F34 = heapAlloc(0x80);
        D_80033F30 = 0;
        menuUpdateStateDispatch(gCurrentActor, 0, 0, 0);
        D_80744514 = 0;
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


extern OSContPad *D_807ECDEC;

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
    if (D_807ECDEC->stick_x < -0x28) {
        buttons |= 4;
    } else if (D_807ECDEC->stick_x >= 0x29) {
        buttons |= 8;
    }
    if (D_807ECDEC->stick_y < -0x28) {
        buttons |= 0x20;
    } else if (D_807ECDEC->stick_y >= 0x29) {
        buttons |= 0x10;
    }
    switch (opMode) {
    case 0:
        D_80033F38 = 1;
        D_80033F44 = 0.0f;
        D_80033F40 = 0.0f;
        D_80033F3C = 0.0f;
        gGlobalPauseFlags &= 0xFFFEFFFF;
        state->unkC = 0;
        state->unkE = 0;
        D_800337F8 = 1;
        break;
    case 1:
        break;
    case 2:
        D_8076A0D0[state->unk12] = state->selection;
        lightSetColor(1.0f, 1.0f, 1.0f, 0);
        break;
    }
    switch (state->unk12) {
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
    D_80033670 = buttons;
    return dl;
}

f32 sqrtf(f32);

void menuSpawnUiElementEffect(MenuScreenState *state, void *assetPtr, s32 posX, s32 posY, f32 elemScale, s32 flags, s32 fxType) {
    MenuEffect *fx;
    MenuEffectTarget *burst;
    f32 dx;
    f32 dy;
    f32 dist;
    f32 scale;

    effectSetMode(flags);
    effectEnableFade();
    effectSetDuration(-1);
    effectSetSpeed((s32)state);
    effectSetCallback(menuUpdateElementTargetAndColor);
    effectSetFlags(1);
    fx = effectCreateAtPosition(assetPtr, elemScale, posX, posY, -10.0f);
    burst = heapAlloc(0x28);
    fx->data = burst;
    burst->unk0 = fxType;
    burst->unk4 = state->unk15;
    burst->unk8 = fx->posX;
    burst->unkC = fx->posY;
    switch (fxType) {
    case 14:
        fx->scaleX = -fx->scaleX;
    case 0:
    case 1:
    case 11:
    case 12:
    case 13:
    case 16:
    case 17:
    case 19:
        dx = 640.0f - burst->unk8;
        dy = 480.0f - burst->unkC;
        dist = sqrtf((dx * dx) + (dy * dy));
        scale = 1040.0f - dist;
        burst->unk10 = -(dx / dist) * scale;
        burst->unk14 = -(dy / dist) * scale;
        burst->unk18 = fx->scaleX;
        break;
    case 2:
    case 3:
    case 10:
        burst->unk8 = posX;
        burst->unk10 = elemScale;
        burst->unk14 = 0.0f;
        break;
    case 15:
        burst->unk8 = posX;
        break;
    default:
        burst->unk10 = elemScale;
        burst->unk14 = 0.0f;
        break;
    }
    if (D_80033F38 == 0) {
        fx->colorR = 0x80;
        fx->colorG = 0x80;
        fx->colorB = 0x80;
    }
    D_80033F38 = 1;
}

typedef struct Menu10_Spin {
    f32 vx;
    f32 vy;
    f32 ang;
    f32 dir;
} Menu10_Spin;

extern u8 gGfxBufferIndex;

void menuSparkleParticleUpdate(MenuEffect *spinner, s32 unused) {
    Menu10_Spin *p;
    s16 randAngle;
    f32 rotMatrix[4][4];
    if (spinner->data == NULL) {
        p = spinner->data = heapAlloc(0x10);
        randAngle = randomLcgNext() * 0x10;
        p->vx = mathSinF(randAngle) * 60.0f;
        p->vy = mathCosF(randAngle) * 60.0f;
        p->ang = randomFloat() * 3.141f;
        spinner->posX = spinner->posX + p->vx * 3.0f;
        spinner->posY = spinner->posY + p->vy * 3.0f;
        if (p->vx > 0) {
            p->dir = 0.3f;
        } else {
            p->dir = -0.3f;
        }
    }
    p = spinner->data;
    spinner->posX = spinner->posX + p->vx;
    spinner->posY = spinner->posY + p->vy;
    p->ang = p->ang + p->dir;
    guRotateF(rotMatrix, p->ang, 0.0f, 0.0f, 1.0f);
    guMtxF2L(rotMatrix, &spinner->mtx[gGfxBufferIndex]);
}

typedef struct MenuUiRgba {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} MenuUiRgba;

extern MenuUiRgba D_800337DC[];

void menuUpdateElementTargetAndColor(MenuEffect *elemActor, u8 *outFlag) {
    MenuScreenState *p = elemActor->cfg;
    MenuEffectTarget *c;
    f32 f;
    f32 radius;
    f32 stepOrScale;
    s32 off;
    s32 type;
    s32 t;
    s32 idx;
    s32 r;
    s32 splineStep;
    s16 colorComponent;
    s16 alphaVal;

    if (elemActor->data != NULL) {
        c = elemActor->data;
        f = p->unk0;
        off = (s32)((f64)(&p->unkC)[(s32)c->unk4] * 4.0);
        type = (s32)c->unk0;

        switch (type) {
        case 6:
        case 7:
        case 18: {
            r = menuEvaluateSelectorSpline(p, (s32)c->unk8 >> 2, &elemActor->posX, &elemActor->posY, &stepOrScale, &colorComponent, &alphaVal);
            elemActor->scaleX = c->unk10 * stepOrScale * 4.0f;
            elemActor->scaleY = elemActor->scaleX;
            if (type == 7) {
                t = (gFrameCounter * 0x78) & 0xFFF;
                elemActor->posY += mathSinF(t) * 10.0f;
            }
            if (type == 0x12) {
                elemActor->colorR = colorComponent;
                elemActor->colorG = colorComponent;
                elemActor->colorB = colorComponent;
                elemActor->colorA = alphaVal;
                elemActor->unk38E = gPlayerSlots->rect[0];
                elemActor->unk392 = gPlayerSlots->rect[2];
                if (elemActor->posY < 360.0) {
                    if ((f64)elemActor->posX < 640) {
                        elemActor->unk392 = 0x78;
                    } else {
                        elemActor->unk38E = 0xC8;
                    }
                }
                if (D_80033F3C != 0.0 && r == 0) {
                    elemActor->unk392 = 0;
                }
            }
            break;
        }
        case 4:
        case 5:
        case 8:
            f = 1.0 - p->unk0;
            if (f < 0.0f) {
                f = 0.0f;
            }
            if (f > 1.0f) {
                f = 1.0f;
            }
            elemActor->colorA = (s32)(f * 255.0f);
            if (type == 4) {
                elemActor->scaleX = (f64)(c->unk10 * f) * 4.0;
                elemActor->scaleY = elemActor->scaleX;
            }
            f = 0;
            elemActor->posY = c->unkC + (f32)off;
            if (type == 8) {
                D_80033FAC = 0;
                t = D_807ECDEC->stick_x;
                if (t >= 0xB) {
                    elemActor->posX += (f32)t;
                    if (elemActor->posX > 960.0f) {
                        elemActor->posX = 960.0f;
                        D_80033FAC = 1;
                    }
                } else if (t < -0xA) {
                    elemActor->posX += (f32)t;
                    if (elemActor->posX < 320.0f) {
                        elemActor->posX = 320.0f;
                        D_80033FAC = 1;
                    }
                } else {
                    elemActor->posX = (elemActor->posX - 640.0) * 0.9 + 640.0;
                }
            } else {
                elemActor->posX = c->unk8;
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
                f *= 0.5f;
                f += p->unk4;
                f = 2.0f * f - 1.0f;
                if (f < 0.0f) {
                    f = -f;
                }
                f = 1.0f - f;
                if (f < 0.0f) {
                    f = 0.0f;
                }
            }
            elemActor->posX = c->unk10 * f + c->unk8;
            elemActor->posY = c->unk14 * f + c->unkC + (f32)off;
            if (type == 9) {
                elemActor->posY = D_80033F4C - 140.0f;
            }
            if (type == 0xC) {
                elemActor->posY += (f32)D_80033674;
            }
            if (type == 0) {
                if (off < -0x3BC) {
                    elemActor->scaleY = 0.0f;
                } else {
                    elemActor->scaleY = elemActor->scaleX;
                }
            }
            if (type == 0xB || type == 0x13) {
                elemActor->posY += 960;
                if (off >= -3 || off < -0x77C) {
                    elemActor->scaleY = 0.0f;
                } else {
                    elemActor->scaleY = elemActor->scaleX;
                }
            }
            if (type == 0xD) {
                elemActor->posY += 1920.0f;
                if (off >= -0x3C3) {
                    elemActor->scaleY = 0.0f;
                } else {
                    elemActor->scaleY = elemActor->scaleX;
                }
            }
            if (type == 0xE) {
                t = (gFrameCounter * 0x78) & 0xFFF;
                elemActor->posY += mathSinF(t) * 10.0f;
            }
            if (type == 0x13 && (D_80033FAD == 4 || D_80033FAD == 1 || D_8076A104 == 1)) {
                elemActor->posX = -400.0f;
            }
            if (type == 0x10 && p->selection >= 3) {
                elemActor->posX = -400.0f;
            }
            if (type == 0x11 && p->selection < 3) {
                elemActor->posX = -400.0f;
            }
            break;
        case 2:
        case 3:
        case 10: {
            idx = (s32)c->unk8;
            switch (type) {
            case 2:
                splineStep = 4;
                stepOrScale = 1024.0f;
                radius = 65.0f;
                break;
            case 3:
                if (elemActor && elemActor && elemActor) {} // FAKE: lowers idx colouring priority below the case-15 address temps
                splineStep = 3;
                stepOrScale = 1365.0f;
                radius = 55.0f;
                break;
            case 10:
                splineStep = 2;
                if (D_80033804 && D_80033804) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                stepOrScale = 2048.0f;
                radius = 50.0f;
                break;
            }
            idx *= (s32)stepOrScale;
            idx -= p->selection * (s32)stepOrScale;
            idx -= (s32)(p->unk4 * stepOrScale);
            t = (s16)idx;
            if (D_80033804 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            elemActor->posX = 160.0f - mathSinF(t) * radius;
            elemActor->posY = 120.0f - mathCosF(t) * radius;
            if (menuComputeElementPosition(p, elemActor->posX, elemActor->posY, &elemActor->posX, &elemActor->posY, splineStep, 0, 1.0f) == (s32)c->unk8) {
                stepOrScale = 1.1f;
            } else {
                stepOrScale = 0.825f;
            }
            f = 0.0f;
            elemActor->posX *= 4.0f;
            elemActor->posY *= 4.0f;
            elemActor->scaleX = c->unk10 * 4.0f * stepOrScale;
            elemActor->scaleY = elemActor->scaleX;
            break;
        }
        case 15: {
            idx = (s32)c->unk8;
            elemActor->posX = D_80033F68[idx];
            elemActor->posY = D_80033F80[idx];
            elemActor->scaleX = D_80033F98[idx];
            if (outFlag != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            elemActor->scaleY = D_80033F98[idx];
            D_80033F68[idx] = -200.0f;
            D_80033F80[idx] = -200.0f;
            if (*(&D_80033804 + idx) == 0) {
                elemActor->colorR = *((u8 *)D_800337DC + (idx << 2)); // FAKE: byte-offset rgba read keeps the shared idx << 2 (array form recolours)
                elemActor->colorG = *((u8 *)D_800337DC + (idx << 2) + 1); // FAKE: byte-offset rgba read keeps the shared idx << 2 (array form recolours)
                elemActor->colorB = *((u8 *)D_800337DC + (idx << 2) + 2); // FAKE: byte-offset rgba read keeps the shared idx << 2 (array form recolours)
            }
            break;
        }
        }
        if (f > 1.0f || p->unk0 > 1.0f) {
            *outFlag = 1;
        }
    }
}


extern f32 D_8003373C[];
extern f32 D_8003378C[];

s32 menuEvaluateSelectorSpline(MenuScreenState *view, s32 index, f32 *outPosX, f32 *outPosY, f32 *outScale, s16 *outColor, s16 *outAlpha) {
    f32 v;
    s32 ret;
    index += view->selection;
    if (index >= 5) {
        index -= 5;
    }
    ret = index;
    if (index << 2) {} // FAKE: orders the byte-offset spill before the spline-pointer spill.
    index *= 4;
    (&D_8003378C[index])[2] = D_8003373C[index];
    D_8003373C[index + 2] = -D_8003378C[index];
    D_8003378C[index + 3] = D_8003373C[1 + index];
    (&D_8003373C[index])[3] = -D_8003378C[1 + index];
    *outPosX = menuEvaluateSpline((f32 *)((u8 *)D_8003373C + (index << 2)), view->unk4, NULL); // FAKE: byte-offset spline pointer pairs with the index << 2 spill
    *outPosY = menuEvaluateSpline((f32 *)((u8 *)D_8003378C + (index << 2)), view->unk4, NULL); // FAKE: byte-offset spline pointer pairs with the index << 2 spill
    if (*outPosY < -40.0f) {
        v = -*outPosY - 40.0f;
        if (v > 20.0f) {
            v = 20.0f;
        }
        *outScale = (v / 60.0f) + 1.0f;
        *outColor = (s16)(v * 6.2f) + 0x80;
    } else {
        *outScale = 1.0f;
        *outColor = 0x80;
    }
    *outAlpha = 0xFF;
    if (D_8003373C == &D_8003373C[index]) {
        *outPosY *= 1.0f - D_80033F3C;
        *outScale += D_80033F3C * 3.5f;
        if (D_80033F3C != 0.0f) {
            *outAlpha = 0xFF - (s32)(view->unk0 * 255.0f);
            if (*outAlpha < 0) {
                *outAlpha = 0;
            }
        }
    }
    *outPosX *= 4.0f + (view->unk0 * 4.0f);
    *outPosY *= 4.0f + (view->unk0 * 4.0f);
    *outPosX += 640.0f;
    *outPosY += 480.0f;
    return ret;
}

s32 menuComputeElementPosition(MenuScreenState *state, f32 baseX, f32 baseY, f32 *outPosX, f32 *outPosY, s32 count, s8 mode, f32 factor) {
    f32 dist;
    f32 f;
    f32 t;
    s32 idx;

    baseX = baseX - 160.0f;
    t = 0.0f;
    baseY = baseY - 120.0f;
    dist = sqrtf((baseX * baseX) + (baseY * baseY));
    if (dist < 20.0f) {
        dist = 20.0f;
    }
    f = state->unk4;
    idx = state->selection;
    if (t != f) {
        if (f > 0.5f) {
            idx += 1;
        }
        if (idx >= count) {
            idx -= count;
        }
    }
    t = state->unk0 * 0.5f;
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
    *outPosY = *outPosY + state->unkC;
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

extern s8 D_80033734;

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



extern f32 D_80033678[];
extern s16 D_80754CE0;
extern u8 D_8071FE64;

void menuUpdateKioskActor(void) {
    Menu10_Sub174 *subState;
    s32 i;

    subState = gCurrentActor->customState;
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
            subState->unk23C = 0;
        }
        break;
    case 2:
        subState->unk23C += 1;
        if (subState->unk23C == 3) {
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
        subState->unk23C = 0;
        gCurrentActor->unk155 = 6;
        break;
    case 6:
    case 7:
    case 8:
        subState->unk23C += 1;
        if (subState->unk23C >= 0x3E9) {
            subState->unk23C = 0x3E8;
        }
        if (subState->unk23C == 8) {
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
        if (subState->unk23C >= 0xC) {
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

extern f32 D_8003378C[];

void menuUpdateKioskPodActor(void) {
    Menu10_Sub174 *pos;
    f32 x[2];
    f32 y[2];
    f32 z[2];
    f32 cx;
    f32 s[2];
    f32 cy;
    f32 cz;
    s32 pad0;
    s32 pad1;
    s32 pad2;

    pos = gCurrentActor->customState;
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
            pos->unk0 = gCurrentActor->x;
            pos->unk4 = gCurrentActor->y;
            pos->unk8 = gCurrentActor->z;
            gCurrentActor->yaw = 0;
            gCurrentActor->roll = 0x400;
            camProjectToScreen(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, &s[1], &s[0], 0, 1.0f, 0);
            s[0] = s[0] - 120.0f;
            if (s[0] < -35.0f) {
                if (s[0] > -75.0f) {
                    D_8003378C[0] = s[0];
                    D_8003378C[0x11] = s[0];
                }
            }
        }
    } else {
        gCurrentActor->x = pos->unk0;
        gCurrentActor->y = pos->unk4 - (D_80033F3C * 19.0f);
        gCurrentActor->z = pos->unk8 - (D_80033F3C * 50.0f);
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

typedef struct Menu3R3_StructC828 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
} Menu3R3_StructC828;

extern Menu3R3_StructC828 D_807FC828;

s32 menuCalculateGamePercentage(void) {
    f32 pct;

    hudPauseMenuRefreshTotals();
    pct = 0.0f;
    pct += (f32)D_807FC828.unk0 * 0.4;
    pct += (f32)D_807FC828.unk4 * 0.25;
    pct += (f32)D_807FC828.unkA * 0.2;
    pct += (f32)D_807FC828.unk6 * 0.2;
    pct += (f32)D_807FC828.unk2 * 0.5;
    pct += (f32)D_807FC828.unk8 * 0.5;
    pct += (f32)D_807FC828.unkC * 0.5;

    if (D_807FC828.unk0 == 0xC9) {
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

    D_80033F28 = heapAlloc(0x194);
    i = 0;
    do {
        D_80033F28[i] = textTableGetString(0x25, i, 0);
        i++;
    } while (i != 0x65);
}
