#include "common.h"

typedef struct MenuScreenActor {
    char pad0[0x174];
    void *unk174;
} MenuScreenActor;

typedef struct MenuScreenState {
    f32 unk0;
    f32 unk4;
    char pad8[4];
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s8 unk12;
    s8 unk13;
    char pad14;
    s8 unk15;
    s8 unk16;
    s8 unk17;
} MenuScreenState;

extern s8 D_80745844;
void configureCSPOutputMode(s32);

void menuSetAudioMode(void) {
    s32 val = 1;
    switch (D_80745844) {
    case 0:
        val = 2;
        break;
    case 2:
        val = 4;
        break;
    }
    configureCSPOutputMode(val);
}

Gfx *menuUpdateStateDispatch();
void camEndPath(s32);
s32 sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
extern s8 D_80033734;
extern s32 gCamActor;

void menuTitleScreenHandleInput(MenuScreenActor *actor, s32 buttons) {
    MenuScreenState *state = actor->unk174;
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

typedef struct MenuActorNode {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} MenuActorNode;

typedef struct MenuActor {
    char pad0[4];
    MenuActorNode *unk4;
    char pad8[0x60 - 8];
    u32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xE6 - 0x88];
    s16 unkE6;
    s16 unkE8;
    char padEA[0x154 - 0xEA];
    u8 unk154;
    u8 unk155;
    char pad156[0x174 - 0x156];
    void *unk174;
    char pad178[4];
    s16 *unk17C;
} MenuActor;

extern MenuActor *gCurrentActor;
extern MenuActor *gSpawnedActor;
extern MenuActor *D_807FBB4C;
extern s8 D_80033734;
extern s32 D_807FBB60;

void menuResetCameraAndFlags(MenuScreenActor *actor, s32 unused) {
    f32 *stateVal = actor->unk174;
    D_807FBB4C->unk7C = 109.0f;
    D_807FBB4C->unk80 = 6.0f;
    D_807FBB4C->unk84 = 55.0f;
    *stateVal = 0.0f;
    D_80033734 = 0;
    D_807FBB60 |= 0x10000;
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

void actorFindActiveByType(s32, s32 *);
void actorScriptStart(void *, s32);
s32 camIsCutsceneActive();
void camStartPath(void *, s32, s32);
s32 flagGet(s16, u8);
s32 randomLcgNext();
f32 randomFloat();
void func_8067AB20(s32, s32, s32, s32, void *, s32);
void gfxSetBackgroundBlend(f32);
void lightSetColor(f32, f32, f32, s32);
void menuHandleScrollInput();
void menuUpdateItemTransition(void *, MenuScreenState *, s32);
void menuUpdateScrollAnimation();
void spawnNodesSetActorStateByFlag(s32, s32);

void menuUpdateMainScreen(void *actor, s32 buttons) {
    MenuScreenState *state;
    BonusMenu_Pair pair;
    s32 camTargetActor;
    s8 camAction;
    f32 targetBrightness;
    s32 camParam;
    s16 sel;
    s16 idxCounter;
    s16 startRandIdx;
    s16 randIdx;

    state = *(MenuScreenState **)((u8 *)actor + 0x174);
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
            switch (state->unk17) {
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
            switch (state->unk17) {
            default:
                state->unk13 = 2;
                break;
            case 1:
                state->unk13 = 8;
                break;
            case 2:
                state->unk13 = 6;
                break;
            case 3:
                state->unk13 = 0xA;
                break;
            case 4:
                state->unk13 = 9;
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
                actorScriptStart(D_807FBB4C, D_80033724[(s16)sel]);
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
                    if (D_800336A0 && D_800336A0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
                            if (D_800337F0 && D_800337F0) {}  // FAKE: deadsweep: steers uopt colouring of the address/const webs
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
        func_8067AB20(gCamActor, camTargetActor, 0x01000000, camParam & 0xFF, &pair, 0);
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

extern char **D_80033F28;
s32 menuComputeElementPosition(MenuScreenState *, f32, f32, f32 *, f32 *, s32, s8, f32);

void *heapAlloc(s32);
void heapFreeDeferred(void *);
Gfx *textDrawStringVtx(Gfx *, s16, s16, s16, void *, s32);

Gfx *menuDrawMainScreenTitle(MenuScreenActor *actor, Gfx *dl) {
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
    void *state = actor->unk174;

    D_807FBB60 |= 0x10;
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
void menuSpawnUiElementEffect(MenuScreenState *, void *, s32, s32, f32, s32, s32);
s32 eepromGetField(s32, s32, u8, s32);

void menuInitMainScreen(MenuScreenActor *actor, s32 unused) {
    MenuScreenState *state = actor->unk174;

    D_800337F8 = 0;
    D_800337F4 = 0;
    D_807FBB4C->unk154 = 0x85;
    D_807FBB4C->unk155 = 0;
    D_80745844 = eepromGetField(0x1E, 0, 0, 0);
    menuSetAudioMode();
    state->unk17 = D_8076A0D1[0];
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 0, 0, 1.2f, 2, 0x12);
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 1, 0, 1.2f, 2, 0x12);
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 2, 0, 1.2f, 2, 0x12);
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 3, 0, 1.2f, 2, 0x12);
    menuSpawnUiElementEffect(state, (void *)(s32)&D_80721444, 4, 0, 1.2f, 2, 0x12);
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
    D_807FBB4C->unk7C = 700.0f;
    D_807FBB4C->unk80 = 100.0f;
    D_807FBB4C->unk84 = 70.0f;
    D_80033F54 = 0;
    while (D_800336A4[D_80033F54] != -1) {
        D_80033F54++;
    }
    D_80033F52 = 0x1E;
    D_80033F55 = 0;
    D_80033F56 = 0;
    D_80033F5C = 0.0f;
    D_80033F58 = 1.0f;
    D_807FBB60 &= 0xFFFEFFFF;
}

void menuMainScreenNoop(void) {
}

extern s8 D_80033F48;

void menuHandleSelectionInput(MenuScreenActor *actor, s32 buttons) {
    MenuScreenState *state = actor->unk174;

    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            if (buttons & 1) {
                state->unk16 = 0;
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                switch (state->unk17) {
                case 2:
                    state->unk13 = 4;
                    break;
                default:
                    D_80033F48 = state->unk17;
                    if (D_80033F48 == 3) {
                        D_80033F48 = 2;
                    }
                    state->unk13 = 3;
                    break;
                }
            } else if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->unk13 = 1;
            } else {
                menuHandleScrollInput(state, 4, buttons);
            }
        }
        menuUpdateScrollAnimation(state, 4);
    }
    menuUpdateItemTransition(actor, state, 1);
}

int _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);
s32 menuCheckSaveFile();

Gfx *menuDrawAdventureFileSelectTitle(MenuScreenActor *actor, Gfx *dl) {
    void *state = actor->unk174;
    s32 idx;
    f32 posX;
    f32 posY;
    char strBuf[204];

    D_807FBB60 &= ~0x10;
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

void menuInitAdventureFileSelect(MenuScreenActor *actor, s32 unused) {
    MenuScreenState *state = actor->unk174;

    state->unk17 = D_8076A0D2;
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0x78, 0.75f, 2, 4);
    if (menuCheckSaveFile(0) != 0) {
        D_80033F38 = 0;
    }
    menuSpawnUiElementEffect(state, (void *)(s32)&D_8072052C, 0, 0, 1.0f, 2, 2);
    if (menuCheckSaveFile(1) != 0) {
        D_80033F38 = 0;
    }
    menuSpawnUiElementEffect(state, (void *)(s32)&D_8072052C, 1, 0, 1.0f, 2, 2);
    if (menuCheckSaveFile(2) != 0) {
        D_80033F38 = 0;
    }
    menuSpawnUiElementEffect(state, (void *)(s32)&D_8072052C, 3, 0, 1.0f, 2, 2);
    menuSpawnUiElementEffect(state, &D_807204BC, 2, 0, 1.0f, 2, 2);
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
}


extern u8 D_80033818;
extern u16 D_8003381C[];
extern s8 D_807563B4;
extern u16 D_807ECD48;

void menuCheckCheatCodeSequence(void) {
    if (D_8003381C[D_80033818] == *(u16 *)&D_807ECD48) {
        D_80033818++;
        if (D_80033818 >= 7U) {
            D_807563B4 = 1;
            sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
            D_80033818 = 0;
        }
    } else if (D_807ECD48 != 0) {
        D_80033818 = 0;
    }
}

void menuUpdateCameraPositions(void);
void controllerSetActiveMask(s32);
void func_807144B8(s8);
extern s8 D_80033F48;

void menuHandleConfirmationInput(MenuScreenActor *actor, s32 buttons) {
    MenuScreenState *state = actor->unk174;

    if (state->unk0 == 0.0f && state->unk4 == 0.0f) {
        if (buttons & 1) {
            controllerSetActiveMask(1);
            func_807144B8(D_80033F48);
        } else if (buttons & 2) {
            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            state->unk16 = 0;
            state->unk13 = 2;
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
extern u32 gFrameCounter;
Gfx *menuSetElementCoordinates(Gfx *, s32, f32, f32, f32);
Gfx *renderRotatedSprite(Gfx *, u16, s32, s32, s32, s32, s16, s32, f32, f32, s32, f32);
f32 func_80612794(s16);

s32 menuDrawFileSummary(void *actor, Gfx *dl) {
    f32 x = 66.0f;
    s16 y;
    s16 py;
    void *state = *(void **)((u8 *)actor + 0x174);
    s8 *p = &D_80033804;
    s32 i = 0;
    f32 sc = 3.0f;
    f32 four;
    f32 posX;
    f32 posY;
    s32 ang;
    f32 fv1;
    char strBuf[0x20];

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
    four = 4.0f;
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
    x = 0.5f;
    ang = (gFrameCounter * 0x78) & 0xFFF;
    fv1 = func_80612794(ang) * 0.1f + 0.5f;
    py = (s32)((f32)py + 40.0f);
    sc = py;
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
    i = gFrameCounter % 360U;
    dl = renderRotatedSprite(dl, 0xA0, 3, 0, 0x20, 0x20, (s32)posX, (s32)posY, x, sc * 0.5f, i, 0.0f);
    gDPPipeSync(dl++);
    i = (gFrameCounter * 0xC) % 360U;
    dl = renderRotatedSprite(dl, 0xA0, 3, 0, 0x20, 0x20, (s32)posX, (s32)posY, x, sc, i, 0.0f);
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    menuComputeElementPosition(state, 160.0f, 15.0f, &posX, &posY, 5, 1, 0.3f);
    y = posX * four;
    py = posY * four;
    _sprintf(strBuf, "%s %d", (char *)D_80033F28[7], D_80033F48 + 1);
    return (s32)hudDrawScaledText(dl, y, py, 0.6f, strBuf);
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
extern u8 D_807FC950[][0x5E];
extern s8 D_80033804;
extern s8 D_80033805;
extern s32 D_8003380C;
extern s32 D_80033810;
extern u32 D_80033814;
extern f32 D_80033F4C;
extern s8 D_80033F51;
extern u32 actorUpdateCollisionSpheres;
void eepromLoadPlayerData(s32, s32);
s32 menuCalculateGamePercentage(void);

extern s8 D_80033809;
void menuInitFileSummary(void *actor, s32 unused) {
    MenuScreenState *state = *(MenuScreenState **)((u8 *)actor + 0x174);
    u8 *row = D_807FC950[0];
    s8 *p;
    s16 *q;
    s32 pad;
    void *a1;
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
    q = &D_807505B2; p = &D_80033805; i = (s32)&D_80033809; // LAYOUT: keep the three address initializers in one as1 scheduling group
    do {
        k = flagGet(q[-1], 0);
        q++;
        *p++ = k;
    } while (p < (s8 *)i);
    for (p = &D_80033805 - 1, i = 0; i != 5; i++) {
        if (*p != 0) {
            a1 = D_80750518[i];
        } else {
            a1 = &D_807211D0;
        }
        menuSpawnUiElementEffect(state, a1, i, i, 0.8f, 2, 0xF);
        p++;
    }
    osPiReadIo(menuDecodePiAddressConstant(0xAFFE1464), &ioVal);
    if ((menuDecodePiAddressConstant(0x0107183B) ^ 0) != ioVal) { // FAKE: ^ 0 flips the commutative bne/beq operand order
        *(u32 *)(s32)&actorUpdateCollisionSpheres = 0x03E00008;
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


void menuHandleFileSelectInput(MenuScreenActor *actor, s32 buttons) {
    MenuScreenState *state = actor->unk174;

    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            if (buttons & 1) {
                if (menuCheckSaveFile(state->unk17) == 0) {
                    state->unk16 = 0;
                    state->unk13 = 5;
                    D_80033F48 = state->unk17;
                } else {
                    sfxPlayOnFreeSlot(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
            } else if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->unk13 = 2;
            } else {
                menuHandleScrollInput(state, 3, buttons);
            }
        }
        menuUpdateScrollAnimation(state, 3);
    }
    menuUpdateItemTransition(actor, state, 1);
}



Gfx *menuDrawFileSlotLabel(void *actor, Gfx *dl) {
    void *state = *(void **)((u8 *)actor + 0x174);
    s32 fileIdx;
    Gfx *g;
    int ty;
    f32 unusedF32_1;
    f32 textX;
    f32 textY;
    f32 unusedF32_2;
    f32 unusedF32_3;
    f32 unusedF32_4;
    s16 posX;
    s16 y;
    char strBuf[200];

    g = dl++; g->words.w0 = 0xFA000000; g->words.w1 = -1;
    fileIdx = menuComputeElementPosition(state, 160.0f, 25.0f, &textX, &textY, 3, 1, 0.45f);
    posX = (s16)(textX * 4.0f);
    y = (s16)(textY * 4.0f);
    if (menuCheckSaveFile(fileIdx) != 0) {
        _sprintf(strBuf, "%s", (char *)D_80033F28[6]);
    } else {
        _sprintf(strBuf, "%s %d", (char *)D_80033F28[7], fileIdx + 1);
    }
    dl = hudDrawScaledText(dl, posX, y, 0.6f, strBuf);
    y -= 0x3C;
    return hudDrawScaledText(dl, (s16)(textX * 4.0f), y, 0.6f, (char *)D_80033F28[8]);
}


void menuInitFileSelect(MenuScreenActor *actor, s32 unused) {
    MenuScreenState *state = actor->unk174;
    void *assetPtr;

    state->unk17 = 0;
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    if (menuCheckSaveFile(0) != 0) {
        D_80033F38 = 0;
    }
    assetPtr = (void *)(s32)&D_8072052C;
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
void func_8071495C(void);
void *func_80714CC0(void *, f32, f32, f32, f32);
void eepromSetCurrentSlot(u8, s32);
extern s8 D_80033FAC;

void menuMysteryHandleInput(MenuScreenActor *actor, s32 buttons) {
    MenuScreenState *state = actor->unk174;

    if (state->unk0 == 0.0f && state->unk4 == 0.0f) {
        if (buttons & 1) {
            if ((buttons & 8) && (D_80033FAC != 0)) {
                func_8071495C();
                func_80714CC0(&D_8071FBC8, 10.3f, 240.0f, 120.0f, -10.0f);
                func_8071495C();
                func_80714CC0(&D_8071FE08, 10.3f, 240.0f, 120.0f, -10.0f);
                sfxPlayOnFreeSlot(0xF6, 0x7FFF, 63.0f, 1.0f, 0, 0);
                eepromSetCurrentSlot(D_80033F48, 1);
                state->unk16 = 0;
                state->unk13 = 2;
            } else if ((buttons & 4) && (D_80033FAC != 0)) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->unk13 = 2;
            }
        } else if (buttons & 2) {
            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            state->unk16 = 0;
            state->unk13 = 2;
        }
    }
    menuUpdateItemTransition(actor, state, 1);
}


Gfx *menuMysteryDrawFileSlotLabel(void *actor, Gfx *dl) {
    void *state = *(void **)((u8 *)actor + 0x174);
    s32 pad;
    f32 unusedF32_1;
    Gfx *g;
    f32 unusedF32_2;
    f32 textX;
    f32 textY;
    f32 unusedF32_3;
    f32 unusedF32_4;
    f32 unusedF32_5;
    s16 posX;
    s16 y;
    char strBuf[200];

    g = dl++; g->words.w0 = 0xFA000000; g->words.w1 = -1;
    menuComputeElementPosition(state, 160.0f, 25.0f, &textX, &textY, 5, 0, 0.45f);
    posX = (s16)(textX * 4.0f);
    y = (s16)(textY * 4.0f);
    if (menuCheckSaveFile(D_80033F48) != 0) {
        _sprintf(strBuf, "%s", (char *)D_80033F28[6]);
    } else {
        _sprintf(strBuf, "%s %d", (char *)D_80033F28[7], D_80033F48 + 1);
    }
    dl = hudDrawScaledText(dl, posX, y, 0.6f, strBuf);
    y -= 0x3C;
    dl = hudDrawScaledText(dl, (s16)(textX * 4.0f), y, 0.6f, (char *)D_80033F28[8]);
    menuComputeElementPosition(state, 160.0f, 80.0f, &textX, &textY, 5, 0, 2.0f);
    dl = hudDrawScaledText(dl, (s16)(textX * 4.0f), (s16)(textY * 4.0f), 0.6f, (char *)D_80033F28[9]);
    menuComputeElementPosition(state, 80.0f, 120.0f, &textX, &textY, 5, 0, 2.0f);
    return hudDrawScaledText(hudDrawScaledText(dl, (s16)(textX * 4.0f), (s16)(textY * 4.0f), 0.6f, D_80033F28[10]), 0x500 - (s16)(textX * 4.0f), (s16)(textY * 4.0f), 0.6f, D_80033F28[11]);
}

extern s8 D_80033FAC;

void menuMysteryInit(MenuScreenActor *actor, s32 unused) {
    MenuScreenState *state = actor->unk174;

    D_80033FAC = 0;
    state->unk17 = 0;
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_807204BC, 0xA0, 0x80, 1.0f, 2, 8);
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
}

extern s16 D_80033670;
extern s8 D_80033698;
extern s8 D_80744538;
extern s8 D_8076A104;

void menuBossReplayHandleInput(MenuScreenActor *actor, s32 buttons) {
    MenuScreenState *state = actor->unk174;

    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            if (buttons & 1) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->unk13 = 7;
            } else if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->unk13 = 1;
                D_80033698 = 3;
            } else {
                menuHandleScrollInput(state, 2, buttons);
            }
            if (state->unk17 == 0) {
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
    D_8076A104 = state->unk17;
    menuUpdateItemTransition(actor, state, 1);
}

Gfx *renderRotatedSprite(Gfx *, u16, s32, s32, s32, s32, s16, s32, f32, f32, s32, f32);
f32 func_80612790(s16);
f32 func_80612794(s16);

Gfx *menuDrawSubmenuRing(MenuScreenActor *actor, Gfx *dl) {
    MenuScreenState *state = actor->unk174;
    s32 padx;
    s32 idx;
    s32 i;
    s32 id;
    s32 ang;
    f32 posX;
    f32 posY;
    char strBuf[0xD8];

    D_807FBB60 &= ~0x10;
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
        ang = i - (state->unk17 << 11);
        ang -= (s32)(state->unk4 * 2048.0);
        posX = 160.0 - func_80612794((s16)ang) * 50.0;
        posY = 120.0 - func_80612790((s16)ang) * 50.0;
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

void menuInitControllerSlots(MenuScreenActor *actor, s32 unused) {
    MenuScreenState *state = actor->unk174;
    s32 i;
    s32 j;

    state->unk17 = D_8076A0D6;
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
extern u8 D_80750AC0;
extern s32 D_807552E4[];
extern u8 D_807ECD09;
extern OSContPad D_807ECD10[];
void func_8071458C(void);

void menuHandleControllerSlotInput(MenuScreenActor *actor, s32 buttons) {
    MenuScreenState *state = actor->unk174;
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
                D_80750AC0 = 0;
                for (j = 0; j != 4; j++) {
                    bits = 1 << j;
                    if (!(D_8076A0E4[j] & 0x80)) {
                        gPlayerCharacterId[j] = D_8076A0E4[j];
                        mask = (mask | bits) & 0xFF;
                        D_807552E4[4 + D_80750AC0] = D_8076A100[j];
                        D_80750AC0 += 1;
                    }
                }
                controllerSetActiveMask(mask & 0xFF);
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
                    state->unk13 = 6;
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
            i = (buttons ^ D_80033858) & buttons; // tests below re-spell the mask: uopt CSEs it into v0, i stays the s0 copy
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
                            if (((u16 *)&D_807ECD48)[i] & 0x1000) {
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
                            if (i != 0 && (((u16 *)&D_807ECD48)[i] & 0x1000)) {
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
    {
        D_8074451C = state->unk17;
        if (D_80033834[D_8074451C] == 5 && D_80744520 >= 5) {
            D_80744520 = 4;
        }
    }
    menuUpdateItemTransition(actor, state, 1);
    D_807FBB60 |= 0x10000;
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
Gfx *menuSetElementCoordinates(Gfx *, s32, f32, f32, f32);

Gfx *menuDrawCharacterSelect(MenuScreenActor *actor, Gfx *dl) {
    MenuScreenState *state = actor->unk174;
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
    char strBuf[0xC8];
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
        idx = state->unk17;
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

typedef struct Menu6_Sub174 {
    void *unk0;
    char pad4[4];
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
s32 actorSpawn(s32, s32);

void menuInitCharacterSelect(MenuScreenActor *actor, s32 unused) {
    MenuScreenState *state = actor->unk174;
    s32 flag;
    s32 i;
    Menu6_Sub174 *sub;

    menuUpdateCameraPositions();
    D_80033FAF = 1;
    flag = 0x1D;
    i = 1;
    do {
        if (flagGet(flag, 1) != 0) {
            D_80033FAF |= 1 << i;
        }
        i += 1;
        flag += 1;
    } while (i < 5);
    if (D_80744544 & 1) {
        D_80033FAF |= 0x20;
    }
    D_80033FAE = 0;
    D_80033FAD = 0;
    if (D_8076A104 != 0 && D_8074451C >= 5) {
        D_8074451C = 0;
    }
    i = 0;
    state->unk17 = D_8074451C;
    do {
        actorSpawn(0x151, D_8003386C[D_8076A0E4[i] & 0x7F]);
        {
            s16 *q = gSpawnedActor->unk17C;
            *q = D_8003386C[D_8076A0E4[i] & 0x7F];
        }
        gSpawnedActor->unk154 = i;
        i += 1;
        gSpawnedActor->unk155 = D_8076A0E4[i - 1] & 0x7F;
        sub = gSpawnedActor->unk174;
        sub->unk0 = actor;
        sub->unk8 = 0;
    } while (i != 4);
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


void menuMultiplayerResultsHandleInput(MenuScreenActor *actor, s32 buttons) {
    MenuScreenState *state = actor->unk174;

    if (state->unk0 == 0.0 && (buttons & 1)) {
        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
        state->unk16 = 0;
        state->unk13 = 7;
    }
    menuUpdateItemTransition(actor, state, 0);
    menuUpdateCameraPositions();
    D_807FBB60 &= ~0x10;
    D_807FBB60 |= 0x10000;
}

extern u8 D_80033878;
extern u8 D_80033F20[];
extern s16 D_80744524[];
extern s8 D_8076A105;

s32 menuDrawMultiplayerResults(actor, dl)
void *actor;
Gfx *dl;
{
    void *state;
    s32 step;
    s32 i;
    s16 x;
    f32 textX;
    f32 textY1;
    f32 textY2;
    u8 *q;
    s16 y;
    s16 scaledY2;
    char strBuf[200];
    s32 sel;

    state = *(void **)((u8 *)actor + 0x174);
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
            dl = hudDrawScaledText(dl, x, (s16)(y + 0x30), 0.6f, (char *)D_80033F28[0x1D + sel]);
            _sprintf(strBuf, "%d", D_80744524[*q]);
            dl = hudDrawScaledText(dl, x, scaledY2, 0.6f, strBuf);
            i += 1;
            q += 1;
            dl = dl; // FAKE: no-op self-assignment steers as1 order of q++ vs dl move
            x += step;
        } while (i < D_80033878);
        if (i) {} // FAKE: dead if keeps loop counter live after the loop (as1 order)
    }
    return (s32)hudDrawScaledText(dl, 0x280, (s16)(scaledY2 - 0x50), 0.6f, (char *)D_80033F28[0x1F]);
}


extern u8 D_80033878;
extern u8 D_80033F20[];
extern s16 D_80744524[];
extern s8 D_8076A105;
extern u8 D_8003387C[];
extern u8 D_80033F24[];

void menuInitMultiplayerResults(MenuScreenActor *actor, s32 unused) {
    MenuScreenState *state = actor->unk174;
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
    state->unk17 = 0;
    for (i = 0; i < D_80033878; i++) {
        actorSpawn(0x151, D_8003386C[D_8003387C[i]]);
        {
            s16 *q = gSpawnedActor->unk17C;
            *q = D_8003386C[D_8003387C[i]];
        }
        gSpawnedActor->unk154 = D_80033F20[i] | 0x80;
        gSpawnedActor->unk155 = D_8003387C[i];
        sub = gSpawnedActor->unk174;
        sub->unk0 = actor;
        sub->unk8 = (i == D_8076A105) + 1;
    }
    menuSpawnUiElementEffect(state, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
}


typedef struct MenuModelScale {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} MenuModelScale;
typedef struct Menu6B_Actor {
    char pad0[4];
    MenuModelScale *unk4;
    char pad8[0x60 - 8];
    u32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x154 - 0x88];
    u8 unk154;
    u8 unk155;
    char pad156[0x174 - 0x156];
    void *unk174;
    char pad178[4];
    s16 *unk17C;
} Menu6B_Actor;
typedef struct Menu6B_Sub174 {
    Menu6B_Actor *unk0;
    s32 unk4;
    s8 unk8;
} Menu6B_Sub174;
typedef struct Menu6B_Pair {
    f32 a;
    f32 b;
} Menu6B_Pair;
#define Menu6B_A ((Menu6B_Actor *)gCurrentActor)
#define Menu6B_N ((Menu6B_Actor *)gSpawnedActor)
extern s32 D_800338B4[];
extern Menu6B_Pair D_80033894[];
void actorDespawn(void *);
void actorUpdateModelMatrix(void *, s32);
void func_806BF920(void);
void func_806F0C18(void *);
void actorConfigApplyAnimFrameByType(void *, s32, s32);

void menuCharacterSelectUpdateActor(void) {
    s32 step;
    Menu6B_Pair *row;
    f32 *parentStateVal;
    s32 sel;
    f32 posX;
    f32 posY;
    s8 shouldDespawn;
    s8 m8;
    s16 idx;
    s16 *actorTypePtr;
    Menu6B_Sub174 *sub174;

    sub174 = Menu6B_A->unk174;
    parentStateVal = sub174->unk0->unk174;
    shouldDespawn = 0;
    func_806BF920();
    if (!(Menu6B_A->unk60 & 0x10)) {
        Menu6B_A->unk4->unk34 = 2.0f * Menu6B_A->unk4->unk34;
        Menu6B_A->unk4->unk38 = 2.0f * Menu6B_A->unk4->unk38;
        Menu6B_A->unk4->unk3C = 2.0f * Menu6B_A->unk4->unk3C;
        m8 = sub174->unk8;
        actorScriptStart(Menu6B_A, D_800338B4[(s16)(m8 * 6) + (Menu6B_A->unk155 & 0xF)]);
        func_806F0C18(Menu6B_A);
        Menu6B_A->unk60 |= 0x1000;
        sub174->unk4 = D_8076A100[Menu6B_A->unk154 & 0xF];
        actorConfigApplyAnimFrameByType(Menu6B_A, Menu6B_A->unk155 + 2, D_8076A100[Menu6B_A->unk154 & 0xF]);
    }
    sel = Menu6B_A->unk154;
    if (!(Menu6B_A->unk154 & 0x80)) {
        if (sub174->unk4 != D_8076A100[Menu6B_A->unk154]) {
            actorConfigApplyAnimFrameByType(Menu6B_A, Menu6B_A->unk155 + 2, D_8076A100[Menu6B_A->unk154]);
            sub174->unk4 = D_8076A100[Menu6B_A->unk154];
        }
        idx = D_8076A0E4[Menu6B_A->unk154] & 0x7F;
        if (idx != Menu6B_A->unk155) {
            actorTypePtr = &D_8003386C[idx];
            actorSpawn(0x151, *actorTypePtr);
            {
                s16 *q = Menu6B_N->unk17C;
                *q = *actorTypePtr;
            }
            Menu6B_N->unk154 = Menu6B_A->unk154;
            Menu6B_N->unk155 = (s16)idx; // FAKE: no-op narrowing cast, burns one ugen t-ring temp
            {
                Menu6_Sub174 *sub = Menu6B_N->unk174;
                sub->unk0 = sub174->unk0;
            }
            shouldDespawn = 1;
            if (Menu6B_A->unk154 != 0) {} // FAKE: extra reference of the unk154 value; recolours the shared A->unk154 candidate (t0) and the PRE reload position
            if (sub174->unk0->unk60 && sub174->unk0->unk60) {} // FAKE: repeated dead load steers uopt lifetimes and the ugen temporary ring
        }
        row = &D_80033894[Menu6B_A->unk154];
        menuComputeElementPosition((MenuScreenState *)parentStateVal, row->a, row->b, &posX, &posY, 2, 0, 1.8f);
        Menu6B_A->unk7C = D_807FBB4C->unk7C + (posX - 160.0f);
        Menu6B_A->unk80 = (D_807FBB4C->unk80 - (posY - 120.0f)) - 20.0f;
        Menu6B_A->unk84 = D_807FBB4C->unk84 - 300.0f;
        if (D_8076A0E4[Menu6B_A->unk154] & 0x80) {
            Menu6B_A->unk60 &= ~4;
        } else {
            Menu6B_A->unk60 |= 4;
        }
    } else {
        idx = D_80033F24[sel & 0xF];
        step = 0x140 / D_80033878;
        menuComputeElementPosition((MenuScreenState *)parentStateVal, 160.0f, 150.0f, &posX, &posY, 2, 0, 1.8f);
        posX = (idx * step + (step >> 1)) - 0xA0;
        posX = posX * 0.78;
        Menu6B_A->unk7C = D_807FBB4C->unk7C + posX;
        Menu6B_A->unk80 = (D_807FBB4C->unk80 - (posY - 120.0f)) + 16.0f;
        Menu6B_A->unk84 = D_807FBB4C->unk84 - 300.0f;
    }
    if (*parentStateVal > 1.0f) {
        shouldDespawn = 1;
    }
    if (shouldDespawn != 0) {
        actorDespawn(Menu6B_A);
    }
    actorUpdateModelMatrix(Menu6B_A, 0);
}

extern s8 D_8074583C;
extern s8 D_80745840;
void n_alSndpSetGroupVol(u8, u16);
void seqUpdateVolume(s32);
s32 eepromSetField(s32, s32, u8, s32, s32);
void func_8060DEA8(void);

void menuHandleSoundOptionsInput(MenuScreenActor *actor, s32 buttons) {
    MenuScreenState *state = actor->unk174;
    s8 flag = 0;

    menuCheckCheatCodeSequence();
    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            switch (state->unk17) {
            case 0:
                if (!(D_80033670 & 0x10) && (buttons & 0x10)) {
                    D_80745844++;
                    if (D_80745844 >= 3) {
                        D_80745844 = 0;
                    }
                    flag = 1;
                } else if (!(D_80033670 & 0x20) && (buttons & 0x20)) {
                    D_80745844--;
                    if (D_80745844 < 0) {
                        D_80745844 = 2;
                    }
                    flag = 1;
                }
                if (flag != 0) {
                    menuSetAudioMode();
                }
                break;
            case 1:
                if (buttons & 0x10) {
                    D_8074583C++;
                    sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    if (D_8074583C > 0x28) {
                        D_8074583C = 0x28;
                    }
                } else if (buttons & 0x20) {
                    D_8074583C--;
                    sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    if (D_8074583C < 0) {
                        D_8074583C = 0;
                    }
                }
                n_alSndpSetGroupVol(0, D_8074583C * 25000 / 40);
                n_alSndpSetGroupVol(1, D_8074583C * 25000 / 40);
                n_alSndpSetGroupVol(2, D_8074583C * 25000 / 40);
                n_alSndpSetGroupVol(3, D_8074583C * 25000 / 40);
                break;
            case 2:
                if (buttons & 0x10) {
                    D_80745840++;
                    if (D_80745840 > 0x28) {
                        D_80745840 = 0x28;
                    }
                } else if (buttons & 0x20) {
                    D_80745840--;
                    if (D_80745840 < 0) {
                        D_80745840 = 0;
                    }
                }
                seqUpdateVolume(0);
                seqUpdateVolume(2);
                break;
            case 3:
                if (buttons & 0x100) {
                    D_80745844 = 0;
                    D_8074583C = 0x28;
                    D_80745840 = 0x28;
                    n_alSndpSetGroupVol(0, D_8074583C * 25000 / 40);
                    n_alSndpSetGroupVol(1, D_8074583C * 25000 / 40);
                    n_alSndpSetGroupVol(2, D_8074583C * 25000 / 40);
                    n_alSndpSetGroupVol(3, D_8074583C * 25000 / 40);
                    seqUpdateVolume(0);
                    seqUpdateVolume(2);
                    flag = 1;
                    menuSetAudioMode();
                }
                break;
            }
            if (buttons & 2) {
                if (eepromGetField(0x1E, 0, 0, 0) != D_80745844) {
                    eepromSetField(0x1E, 0, 0, 0, D_80745844);
                    func_8060DEA8();
                }
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->unk13 = 1;
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
extern s8 D_80745844;
Gfx *menuDrawScrollSelector(Gfx *, MenuScreenState *, char **, s32, u32 *, s16, f32 *, f32, s16);

Gfx *menuFormatOptionValues(MenuScreenActor *actor, Gfx *dl) {
    void *state;
    u32 selectedOption;
    f32 pad5C;
    f32 posX;
    f32 posY;
    f32 offsetVal;
    s16 pad;
    s16 posYShort;
    char strBuf[12];

    state = actor->unk174;
    D_807FBB60 &= ~0x10;
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
        dl = textDrawStringVtx(dl, 1, posX, posYShort, D_80033F28[D_80745844 + 0x25], 0x81);
        break;
    case 1:
    case 2:
        dl = textDrawStringVtx(dl, 1, posX, posYShort, D_80033F28[0x28], 0x81);
        _sprintf(strBuf, "%d", ((selectedOption == 1 ? D_8074583C : D_80745840) + 1) >> 1);
        dl = textDrawStringVtx(dl, 1, posX, posYShort + 0x78, strBuf, 0x81);
        break;
    case 3:
        D_80033674 = 0;
        break;
    }

    return dl;
}

extern u8 D_80720D38;

void menuInitSoundOptions(MenuScreenActor *actor, s32 unused) {

    MenuScreenState *state = actor->unk174;
    state->unk17 = 0;
    menuSpawnUiElementEffect(state, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    menuSpawnUiElementEffect(state, &D_80720C34, 0xA0, 0x7D, 0.75f, 2, 4);
    menuSpawnUiElementEffect(state, &D_80720D38, 0xA0, 0xC8, 1.0f, 2, 0xC);
}

extern s8 D_800338FC;
extern s8 D_807444C0;
extern s8 D_8074452C;
extern u8 D_80744530;
extern u8 D_807550C8;
extern u16 D_807ECD66;
void heapFreeDeferred(void *);
void eepromInitConfigs(s32);
void menuLoadTextTable(void);

void menuHandleGameOptionsInput(MenuScreenActor *actor, s32 buttons) {
    MenuScreenState *state = actor->unk174;
    s8 flag = 0;
    s32 i;

    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            switch (state->unk17) {
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
                    D_807550C8 += 1;
                    flag = 1;
                }
                if ((buttons & 0x20) && !(D_80033670 & 0x20)) {
                    D_807550C8 -= 1;
                    flag = 1;
                }
                D_807550C8 &= 3;
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

                eepromSetField(0x1F, 0, 0, 0, D_807550C8);
                eepromSetField(0x20, 0, 0, 0, D_80744530);
                func_8060DEA8();
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->unk13 = 1;
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

Gfx *menuDrawGameOptions(MenuScreenActor *actor, Gfx *dl) {
    void *state = actor->unk174;
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

    D_807FBB60 &= ~0x10;
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

void menuInitGameOptions(MenuScreenActor *actor, s32 unused) {
    MenuScreenState *state = actor->unk174;
    state->unk17 = 0;
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
void func_80712634(s32, s32);
void func_807127F4(s32);
void func_807126B0(s16, s32, s16, s8, s32, s32, s32);

void menuHandleCheatsInput(MenuScreenActor *actor, s32 buttons) {
    MenuScreenState *state = actor->unk174;
    s8 flag = 0;
    s8 cnt;
    s8 sel;
    s8 idx;
    s8 *p;

    if (state->unk0 == 0.0f) {
        if (state->unk4 == 0.0f) {
            idx = state->unk17;
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
                            func_80712634(D_80033900[sel][0], D_80033900[sel][1]);
                        } else {
                            func_807127F4(1);
                        }
                        D_80744514 = 3;
                        break;
                    case 1:
                        switch (D_80033978[sel][0]) {
                        case 0xBF:
                            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                            state->unk16 = 0;
                            state->unk13 = 0xC;
                            D_800339A8 = 0;
                            break;
                        case 0xB8:
                            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                            state->unk16 = 0;
                            state->unk13 = 0xC;
                            D_800339A8 = 1;
                            break;
                        default:
                            func_807126B0(D_80033978[sel][0], 0, D_80033978[sel][1], 3, 3, 1, 3);
                            D_80744514 = 5;
                            break;
                        }
                        break;
                    case 2:
                        func_807126B0(D_80033938[sel].a, 0, D_80033938[sel].b, D_80033938[sel].c, D_80033938[sel].d, D_80033938[sel].e, D_80033938[sel].f);
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
                state->unk13 = 1;
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

Gfx *menuDrawCheats(MenuScreenActor *actor, Gfx *dl) {
    void *state = actor->unk174;
    u32 optIdx;
    f32 posX;
    f32 posY;
    f32 scrollOffset;
    s16 sel;
    s16 y;
    char strBuf[0xC8];

    D_807FBB60 &= ~0x10;
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
        dl = textDrawStringVtx(dl, 1, posX, y + 0x40, "???", 0x81);
    }
    return dl;
}

extern s8 D_8076A0DA;


void menuInitCheats(MenuScreenActor *actor, s32 unused) {
    MenuScreenState *state = actor->unk174;
    s32 j;
    s32 i;
    s8 n;

    state->unk17 = D_8076A0DA;
    switch (D_80744514) {
    case 0:
        break;
    default:
        state->unk17 = 0;
        break;
    case 4:
        state->unk17 = 2;
        break;
    case 5:
        state->unk17 = 1;
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
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
} MenuHighScoreEntry;

extern MenuHighScoreEntry D_80744548[];
extern MenuHighScoreEntry D_80744568[];


void menuLoadHighScores(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        D_80744548[i].unk0 = eepromGetField(0x19, 0, i, 0);
        D_80744548[i].unk2 = eepromGetField(0x16, 0, i, 0);
        D_80744548[i].unk3 = eepromGetField(0x17, 0, i, 0);
        D_80744548[i].unk4 = eepromGetField(0x18, 0, i, 0);
        D_80744548[i].unk5 = 0;
        D_80744568[i].unk0 = eepromGetField(0x1D, 0, i, 0);
        D_80744568[i].unk2 = eepromGetField(0x1A, 0, i, 0);
        D_80744568[i].unk3 = eepromGetField(0x1B, 0, i, 0);
        D_80744568[i].unk4 = eepromGetField(0x1C, 0, i, 0);
        D_80744568[i].unk5 = 0;
    }
}

void menuSaveHighScores(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        eepromSetField(0x19, 0, i, 0, D_80744548[i].unk0);
        eepromSetField(0x16, 0, i, 0, D_80744548[i].unk2);
        eepromSetField(0x17, 0, i, 0, D_80744548[i].unk3);
        eepromSetField(0x18, 0, i, 0, D_80744548[i].unk4);
        eepromSetField(0x1D, 0, i, 0, D_80744568[i].unk0);
        eepromSetField(0x1A, 0, i, 0, D_80744568[i].unk2);
        eepromSetField(0x1B, 0, i, 0, D_80744568[i].unk3);
        eepromSetField(0x1C, 0, i, 0, D_80744568[i].unk4);
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
extern u32 gFrameCounter;
extern MenuM8_PosPair D_800339B8[];

void menuHandleHighScoreNameEntryInput(void *actor, s32 buttons) {
    MenuScreenState *state = *(MenuScreenState **)((u8 *)actor + 0x174);
    s8 v1;
    MenuHighScoreEntry *table;
    u32 v0;
    s32 tmp;
    u8 *p;
    if (D_800339A8 == 0) {
        table = D_80744548;
    } else {
        table = D_80744568;
    }
    if (state->unk0 == 0.0f) {
        if (D_80033F60 < 0) {
            if (buttons & 1) {
                func_807126B0(D_800339B8[D_800339A8].unk0, 0, D_800339B8[D_800339A8].unk2, 3, 3, 1, 3);
                D_80744514 = D_800339A8 + 6;
            }
            if (buttons & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                state->unk16 = 0;
                state->unk13 = 0xA;
            }
        } else {
            if (buttons & 0xC) {
                v1 = D_800339C0 + 1;
            } else {
                v1 = 0;
            }
            v0 = 0;
            if (v1 == 1 || (D_800339C0 = v1, v1 >= 0x10)) {
                if (D_80033F61 && D_80033F61) {} // FAKE: dead test steers register colouring (frame counter / D_80033F61 candidates)
                D_800339C0 = v1;
                v0 = buttons;
                if (v1 >= 0x10) {
                    v1 = 0xF;
                    if (D_80033F60 == 0xF) {} // FAKE: constant 15 becomes a coloured web (v1), leaving gFrameCounter a ring temp
                    D_800339C0 = v1;
                    if (D_80033F60 == 0xF) {} // FAKE: second reference to the 15 web
                    if (!(gFrameCounter & 1)) {
                        v0 = 0;
                    }
                }
            }
            p = (u8 *)table + D_80033F60 * 6 + D_80033F61 + 2;
            if (v0 & 4) {
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
            } else if (v0 & 8) {
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
extern char *D_800339AC[];
extern u32 gFrameCounter;

Gfx *menuDrawHighScoreTable(void *actor, Gfx *dl) {
    void *state;
    f32 posX;
    f32 posY;
    s32 ft4;
    MenuHighScoreEntry *e;
    MenuHighScoreEntry *scoreTable;
    char strBuf[0xC8];
    s16 yPos;
    s16 i;

    state = *(void **)((u8 *)actor + 0x174);
    D_807FBB60 &= ~0x10;
    menuComputeElementPosition(state, 160.0f, 20.0f, &posX, &posY, 2, 0, 1.0f);
    dl = textDrawStringVtx(dl, 1, 0x280, (s16)(posY * 4.0), ((void **)D_80033F28)[D_800339A8 + 0x5F], 0x81);
    menuComputeElementPosition(state, 160.0f, 205.0f, &posX, &posY, 2, 0, 1.0f);
    i = 0;
    yPos = (s16)(posY * 4.0);
    if (D_80033F60 >= 0) {
        _sprintf(strBuf, "%s", ((void **)D_80033F28)[0x63]);
        i = 1;
    } else if (D_80033F60 == -2) {
        _sprintf(strBuf, "%s %d.", ((void **)D_80033F28)[0x64], D_80744518);
        i = 1;
    }
    if (i != 0) {
        dl = hudDrawScaledText(dl, 0x280, yPos, 0.6f, strBuf);
    }
    i = 0;
    menuComputeElementPosition(state, 20.0f, 120.0f, &posX, &posY, 2, 0, 2.0f);
    yPos = 0xC8;
    ft4 = (s16)(s32)(posX * 4.0f);
    if (D_800339A8 == 0) {
        scoreTable = D_80744548;
    } else {
        scoreTable = D_80744568;
    }
    for (i = 0; i < 5; i++) {
        _sprintf(strBuf, "%d.", i + 1);
        e = (MenuHighScoreEntry *)((u8 *)scoreTable + i * 6);
        dl = textDrawStringVtx(dl, 1, (s16)(ft4 + 0x50), yPos, strBuf, 1);
        _sprintf(strBuf, "%c %c %c", e->unk2, e->unk3, e->unk4);
        dl = textDrawStringVtx(dl, 0x81, (s16)(ft4 + 0x118), yPos, strBuf, 1);
        _sprintf(strBuf, "%d", e->unk0);
        dl = textDrawStringVtx(dl, 0x81, (s16)(0x3E8 - ft4), yPos, strBuf, 1);
        if (i == D_80033F60 && (gFrameCounter & 0x1F) < 0x14) {
            dl = textDrawStringVtx(dl, 0x81, (s16)(ft4 + 0x118), yPos + 0x34, D_800339AC[D_80033F61], 1);
        }
        yPos += 0x6C;
    }
    return dl;
}

extern s8 D_80033F60;

void menuInitHighScores(MenuScreenActor *actor, s32 unused) {
    MenuScreenState *state = actor->unk174;

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
        if (D_80744518 >= table[i].unk0) {
            j = 4;
            if (i < 4) {
                do {
                    table[j].unk0 = table[j - 1].unk0;
                    table[j].unk2 = table[j - 1].unk2;
                    table[j].unk3 = table[j - 1].unk3;
                    table[j].unk4 = table[j - 1].unk4;
                    j--;
                } while (j > i);
            }
            table[i].unk0 = D_80744518;
            table[i].unk2 = 0x2E;
            table[i].unk3 = 0x2E;
            table[i].unk4 = 0x2E;
            D_80033F60 = i;
            D_80033F61 = 0;
            return;
        }
    }
    D_80033F60 = -1;
}

typedef struct Menu3B_Struct_C924 {
    char pad[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad2[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
    char pad234[0x270 - 0x234];
    s16 unk270;
    char pad272[2];
    s16 unk274;
    char pad276[0x298 - 0x276];
    u16 *unk298;
} Menu3B_Struct_C924;

extern Menu3B_Struct_C924 *gPlayerSlots;

void menuUpdateCameraPositions(void) {
    gPlayerSlots->unk210 = D_807FBB4C->unk7C;
    gPlayerSlots->unk214 = D_807FBB4C->unk80 + 13.1f;
    gPlayerSlots->unk218 = D_807FBB4C->unk84 - 50.0f;
    gPlayerSlots->unk228 = D_807FBB4C->unk7C;
    gPlayerSlots->unk22C = gPlayerSlots->unk214;
    gPlayerSlots->unk230 = D_807FBB4C->unk84 - 100.0f;
}

extern char D_800339C4[];
extern f32 D_80033F44;

Gfx *menuDrawScrollSelector(Gfx *dl, MenuScreenState *state, char **strTable, s32 itemCount, u32 *outIdx, s16 textFlag, f32 *outOffset, f32 posY, s16 enabledMask) {
    s32 idx = state->unk17;
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
            state->unk12 = state->unk13;
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
        state->unk17--;
        state->unk4 = 1.0f;
        if (state->unk17 < 0) {
            state->unk17 += itemCount;
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
            state->unk17++;
            if (state->unk17 >= itemCount) {
                state->unk17 -= itemCount;
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
void func_8061B650(s32);
void func_8060CB9C(void);
void menuInsertHighScore(void);
void renderCallbacksRegister(void *, void *, s32);
void *heapAlloc(s32);
void menuInitGfxState(Gfx *, s32);

void menuInit(void) {
    MenuScreenState *sub = gCurrentActor->unk174;
    Menu10_Sub174 *actorState = D_807FBB4C->unk174;
    s32 i;

    if (!(gCurrentActor->unk60 & 0x10)) {
        D_807FBB60 |= 0x10;
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
            D_807FBB4C->unk7C = 700.0f;
            D_807FBB4C->unk80 = 0.0f;
            D_807FBB4C->unk84 = 70.0f;
        }
        D_80033F50 = 0;
        D_80033738 = 0;
        D_80033F60 = -1;
        D_8003369C = 0.0f;
        actorSpawn(0x14D, 0xD7);
        gSpawnedActor->unk7C = D_807FBB4C->unk7C;
        gSpawnedActor->unk80 = D_807FBB4C->unk80;
        gSpawnedActor->unk84 = D_807FBB4C->unk84;
        gSpawnedActor->unkE6 = D_807FBB4C->unkE6;
        if (D_80744514 != 0) {
            D_80033738 = 0x15;
            D_807FBB4C->unk154 = 0x85;
            D_807FBB4C->unk155 = 0;
            actorScriptStart(D_807FBB4C, 0x347);
            D_807FBB4C->unk155 = 6;
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
            D_807FBB4C->unk154 = 0x86;
            D_807FBB4C->unk155 = 0;
            sub->unk12 = 0;
            break;
        }
        D_807FBB4C->unk4->unk34 = D_807FBB4C->unk4->unk34 * 0.8;
        D_807FBB4C->unk4->unk38 = D_807FBB4C->unk4->unk38 * 0.8;
        D_807FBB4C->unk4->unk3C = D_807FBB4C->unk4->unk3C * 0.8;
        sub->unk17 = 0;
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


void menuInitGfxState(Gfx *glistp, s32 menuActor) {
    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_1000118);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetRenderMode(glistp++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 255);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    menuUpdateStateDispatch(menuActor, 1, glistp, 0);
}

typedef struct MenuStickAxis {
    char pad0[2];
    s8 unk2;
    s8 unk3;
} MenuStickAxis;

extern MenuStickAxis *D_807ECDEC;
void menuUpdateMainScreen();
Gfx *menuDrawMainScreenTitle();
void menuInitMainScreen();
Gfx *menuDrawAdventureFileSelectTitle();
void menuInitAdventureFileSelect();
s32 menuDrawFileSummary();
void menuInitFileSummary();
Gfx *menuDrawFileSlotLabel();
void menuInitFileSelect();
Gfx *menuMysteryDrawFileSlotLabel();
Gfx *menuDrawSubmenuRing();
void menuInitControllerSlots();
void menuHandleControllerSlotInput();
Gfx *menuDrawCharacterSelect();
void menuInitCharacterSelect();
s32 menuDrawMultiplayerResults();
void menuInitMultiplayerResults();
void menuHandleSoundOptionsInput();
void menuHandleGameOptionsInput();
void menuHandleCheatsInput();
Gfx *menuDrawCheats();
void menuInitCheats();
void menuHandleHighScoreNameEntryInput();

Gfx *menuUpdateStateDispatch(MenuScreenActor *actor, s32 opMode, Gfx *dl, s32 subArg) {
    MenuScreenState *state = actor->unk174;
    s32 buttons = 0;

    if (*gPlayerSlots->unk298 & 0x8000) {
        buttons = 1;
    }
    if (*gPlayerSlots->unk298 & 0x4000) {
        buttons |= 2;
    }
    if (*gPlayerSlots->unk298 & 8) {
        buttons |= 0x40;
    }
    if (*gPlayerSlots->unk298 & 4) {
        buttons |= 0x80;
    }
    if (*gPlayerSlots->unk298 & 0x2000) {
        buttons |= 0x100;
    }
    if (D_807ECDEC->unk2 < -0x28) {
        buttons |= 4;
    } else if (D_807ECDEC->unk2 >= 0x29) {
        buttons |= 8;
    }
    if (D_807ECDEC->unk3 < -0x28) {
        buttons |= 0x20;
    } else if (D_807ECDEC->unk3 >= 0x29) {
        buttons |= 0x10;
    }
    switch (opMode) {
    case 0:
        D_80033F38 = 1;
        D_80033F44 = 0.0f;
        D_80033F40 = 0.0f;
        D_80033F3C = 0.0f;
        D_807FBB60 &= 0xFFFEFFFF;
        state->unkC = 0;
        state->unkE = 0;
        D_800337F8 = 1;
        break;
    case 1:
        break;
    case 2:
        D_8076A0D0[state->unk12] = state->unk17;
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
            return (Gfx *)menuDrawFileSummary(actor, dl);
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
            return (Gfx *)menuDrawMultiplayerResults(actor, dl);
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

typedef struct Menu10_Burst {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
} Menu10_Burst;

typedef struct Menu10_Fx {
    char pad0[0x340];
    f32 unk340;
    f32 unk344;
    char pad348[0x360 - 0x348];
    f32 unk360;
    char pad364[0x36A - 0x364];
    u8 unk36A;
    u8 unk36B;
    u8 unk36C;
    char pad36D[0x384 - 0x36D];
    Menu10_Burst *unk384;
} Menu10_Fx;

void func_80714950(void *);
void func_8071498C(void *);
void func_80714998(u8);
void func_807149FC(s32);
void func_80714A28(s32);
void menuUpdateElementTargetAndColor();
f32 sqrtf(f32);

void menuSpawnUiElementEffect(MenuScreenState *state, void *assetPtr, s32 posX, s32 posY, f32 elemScale, s32 flags, s32 fxType) {
    Menu10_Fx *fx;
    Menu10_Burst *burst;
    f32 dx;
    f32 dy;
    f32 dist;
    f32 scale;

    func_80714998(flags);
    func_8071495C();
    func_807149FC(-1);
    func_80714950(state);
    func_8071498C(menuUpdateElementTargetAndColor);
    func_80714A28(1);
    fx = func_80714CC0(assetPtr, elemScale, posX, posY, -10.0f);
    burst = heapAlloc(0x28);
    fx->unk384 = burst;
    burst->unk0 = fxType;
    burst->unk4 = state->unk15;
    burst->unk8 = fx->unk340;
    burst->unkC = fx->unk344;
    switch (fxType) {
    case 14:
        fx->unk360 = -fx->unk360;
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
        burst->unk18 = fx->unk360;
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
        fx->unk36A = 0x80;
        fx->unk36B = 0x80;
        fx->unk36C = 0x80;
    }
    D_80033F38 = 1;
}

typedef struct Menu10_Spin {
    f32 vx;
    f32 vy;
    f32 ang;
    f32 dir;
} Menu10_Spin;

typedef struct Menu10_Spinner {
    char pad0[0x128];
    Mtx mtx[8];
    char pad328[0x18];
    f32 unk340;
    f32 unk344;
    char pad348[0x384 - 0x348];
    Menu10_Spin *unk384;
} Menu10_Spinner;

extern u8 D_807444FC;

void menuSparkleParticleUpdate(Menu10_Spinner *spinner, s32 unused) {
    Menu10_Spin *p;
    s16 randAngle;
    f32 rotMatrix[4][4];
    if (spinner->unk384 == NULL) {
        p = spinner->unk384 = heapAlloc(0x10);
        randAngle = randomLcgNext() * 0x10;
        p->vx = func_80612794(randAngle) * 60.0f;
        p->vy = func_80612790(randAngle) * 60.0f;
        p->ang = randomFloat() * 3.141f;
        spinner->unk340 = spinner->unk340 + p->vx * 3.0f;
        spinner->unk344 = spinner->unk344 + p->vy * 3.0f;
        if (p->vx > 0) {
            p->dir = 0.3f;
        } else {
            p->dir = -0.3f;
        }
    }
    p = spinner->unk384;
    spinner->unk340 = spinner->unk340 + p->vx;
    spinner->unk344 = spinner->unk344 + p->vy;
    p->ang = p->ang + p->dir;
    guRotateF(rotMatrix, p->ang, 0.0f, 0.0f, 1.0f);
    guMtxF2L(rotMatrix, &spinner->mtx[D_807444FC]);
}

typedef struct MenuUiRgba {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} MenuUiRgba;

typedef struct MenuUiElemCfg {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC[5];
    char padC[1];
    s8 unk17;
} MenuUiElemCfg;

typedef struct MenuUiElemTarget {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} MenuUiElemTarget;

typedef struct MenuUiElemActor {
    char pad0[0x340];
    f32 unk340;
    f32 unk344;
    char pad348[0x14];
    MenuUiElemCfg *unk35C;
    f32 unk360;
    f32 unk364;
    char pad368[2];
    u8 unk36A;
    u8 unk36B;
    u8 unk36C;
    u8 unk36D;
    char pad36E[0x16];
    MenuUiElemTarget *unk384;
    char pad388[6];
    s16 unk38E;
    char pad390[2];
    s16 unk392;
} MenuUiElemActor;

extern MenuUiRgba D_800337DC[];
s32 menuEvaluateSelectorSpline(void *, s32, f32 *, f32 *, f32 *, s16 *, s16 *);

void menuUpdateElementTargetAndColor(MenuUiElemActor *elemActor, u8 *outFlag) {
    MenuUiElemCfg *p = elemActor->unk35C;
    MenuUiElemTarget *c;
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

    if (elemActor->unk384 != NULL) {
        c = elemActor->unk384;
        f = p->unk0;
        off = (s32)((f64)p->unkC[(s32)c->unk4] * 4.0);
        type = (s32)c->unk0;

        switch (type) {
        case 6:
        case 7:
        case 18: {
            r = menuEvaluateSelectorSpline(p, (s32)c->unk8 >> 2, &elemActor->unk340, &elemActor->unk344, &stepOrScale, &colorComponent, &alphaVal);
            elemActor->unk360 = c->unk10 * stepOrScale * 4.0f;
            elemActor->unk364 = elemActor->unk360;
            if (type == 7) {
                t = (gFrameCounter * 0x78) & 0xFFF;
                elemActor->unk344 += func_80612794(t) * 10.0f;
            }
            if (type == 0x12) {
                elemActor->unk36A = colorComponent;
                elemActor->unk36B = colorComponent;
                elemActor->unk36C = colorComponent;
                elemActor->unk36D = alphaVal;
                elemActor->unk38E = gPlayerSlots->unk270;
                elemActor->unk392 = gPlayerSlots->unk274;
                if (elemActor->unk344 < 360.0) {
                    if ((f64)elemActor->unk340 < 640) {
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
            elemActor->unk36D = (s32)(f * 255.0f);
            if (type == 4) {
                elemActor->unk360 = (f64)(c->unk10 * f) * 4.0;
                elemActor->unk364 = elemActor->unk360;
            }
            f = 0;
            elemActor->unk344 = c->unkC + (f32)off;
            if (type == 8) {
                D_80033FAC = 0;
                t = D_807ECDEC->unk2;
                if (t >= 0xB) {
                    elemActor->unk340 += (f32)t;
                    if (elemActor->unk340 > 960.0f) {
                        elemActor->unk340 = 960.0f;
                        D_80033FAC = 1;
                    }
                } else if (t < -0xA) {
                    elemActor->unk340 += (f32)t;
                    if (elemActor->unk340 < 320.0f) {
                        elemActor->unk340 = 320.0f;
                        D_80033FAC = 1;
                    }
                } else {
                    elemActor->unk340 = (elemActor->unk340 - 640.0) * 0.9 + 640.0;
                }
            } else {
                elemActor->unk340 = c->unk8;
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
            elemActor->unk340 = c->unk10 * f + c->unk8;
            elemActor->unk344 = c->unk14 * f + c->unkC + (f32)off;
            if (type == 9) {
                elemActor->unk344 = D_80033F4C - 140.0f;
            }
            if (type == 0xC) {
                elemActor->unk344 += (f32)D_80033674;
            }
            if (type == 0) {
                if (off < -0x3BC) {
                    elemActor->unk364 = 0.0f;
                } else {
                    elemActor->unk364 = elemActor->unk360;
                }
            }
            if (type == 0xB || type == 0x13) {
                elemActor->unk344 += 960;
                if (off >= -3 || off < -0x77C) {
                    elemActor->unk364 = 0.0f;
                } else {
                    elemActor->unk364 = elemActor->unk360;
                }
            }
            if (type == 0xD) {
                elemActor->unk344 += 1920.0f;
                if (off >= -0x3C3) {
                    elemActor->unk364 = 0.0f;
                } else {
                    elemActor->unk364 = elemActor->unk360;
                }
            }
            if (type == 0xE) {
                t = (gFrameCounter * 0x78) & 0xFFF;
                elemActor->unk344 += func_80612794(t) * 10.0f;
            }
            if (type == 0x13 && (D_80033FAD == 4 || D_80033FAD == 1 || D_8076A104 == 1)) {
                elemActor->unk340 = -400.0f;
            }
            if (type == 0x10 && p->unk17 >= 3) {
                elemActor->unk340 = -400.0f;
            }
            if (type == 0x11 && p->unk17 < 3) {
                elemActor->unk340 = -400.0f;
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
            idx -= p->unk17 * (s32)stepOrScale;
            idx -= (s32)(p->unk4 * stepOrScale);
            t = (s16)idx;
            if (D_80033804 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            elemActor->unk340 = 160.0f - func_80612794(t) * radius;
            elemActor->unk344 = 120.0f - func_80612790(t) * radius;
            if (menuComputeElementPosition(p, elemActor->unk340, elemActor->unk344, &elemActor->unk340, &elemActor->unk344, splineStep, 0, 1.0f) == (s32)c->unk8) {
                stepOrScale = 1.1f;
            } else {
                stepOrScale = 0.825f;
            }
            f = 0.0f;
            elemActor->unk340 *= 4.0f;
            elemActor->unk344 *= 4.0f;
            elemActor->unk360 = c->unk10 * 4.0f * stepOrScale;
            elemActor->unk364 = elemActor->unk360;
            break;
        }
        case 15: {
            idx = (s32)c->unk8;
            elemActor->unk340 = D_80033F68[idx];
            elemActor->unk344 = D_80033F80[idx];
            elemActor->unk360 = D_80033F98[idx];
            if (outFlag != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            elemActor->unk364 = D_80033F98[idx];
            D_80033F68[idx] = -200.0f;
            D_80033F80[idx] = -200.0f;
            if (*(&D_80033804 + idx) == 0) {
                elemActor->unk36A = *((u8 *)D_800337DC + (idx << 2));
                elemActor->unk36B = *((u8 *)D_800337DC + (idx << 2) + 1);
                elemActor->unk36C = *((u8 *)D_800337DC + (idx << 2) + 2);
            }
            break;
        }
        }
        if (f > 1.0f || p->unk0 > 1.0f) {
            *outFlag = 1;
        }
    }
}


typedef struct MenuA_SelectorView {
    f32 unk0;
    f32 unk4;
    char pad8[4];
    s16 unkC;
    char padE[9];
    s8 unk17;
} MenuA_SelectorView;

extern f32 D_8003373C[];
extern f32 D_8003378C[];
f32 menuEvaluateSpline(f32 *, f32, f32 *);

s32 menuEvaluateSelectorSpline(void *view, s32 index, f32 *outPosX, f32 *outPosY, f32 *outScale, s16 *outColor, s16 *outAlpha) {
    f32 v;
    s32 ret;
    index += ((MenuA_SelectorView *)view)->unk17;
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
    *outPosX = menuEvaluateSpline((f32 *)((u8 *)D_8003373C + (index << 2)), ((MenuA_SelectorView *)view)->unk4, NULL);
    *outPosY = menuEvaluateSpline((f32 *)((u8 *)D_8003378C + (index << 2)), ((MenuA_SelectorView *)view)->unk4, NULL);
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
            *outAlpha = 0xFF - (s32)(((MenuA_SelectorView *)view)->unk0 * 255.0f);
            if (*outAlpha < 0) {
                *outAlpha = 0;
            }
        }
    }
    *outPosX *= 4.0f + (((MenuA_SelectorView *)view)->unk0 * 4.0f);
    *outPosY *= 4.0f + (((MenuA_SelectorView *)view)->unk0 * 4.0f);
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
    idx = state->unk17;
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
    f32 sp[4];

    sp[0] = (coeffs[0] + coeffs[0] + -2.0f * coeffs[1] + coeffs[2]) + coeffs[3];
    sp[1] = (-3.0f * coeffs[0] + 3.0f * coeffs[1] + -2.0f * coeffs[2]) - coeffs[3];
    sp[2] = coeffs[2];
    sp[3] = coeffs[0];
    if (outDeriv != NULL) {
        *outDeriv = ((((3.0f * sp[0]) * t) + (sp[1] + sp[1])) * t) + sp[2];
    }
    return (((((sp[0] * t) + sp[1]) * t) + sp[2]) * t) + sp[3];
}

extern s8 D_80033734;

void menuActorStateDispatch(void) {
    MenuActor *actor = gCurrentActor;

    switch (actor->unk155) {
    case 0:
        actorScriptStart(actor, 0x345);
        gCurrentActor->unkE6 = 0;
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


void actorUpdateModelMatrix(void *, s32);

extern f32 D_80033678[];
extern s16 D_80754CE0;
extern u8 D_8071FE64;

void menuUpdateKioskActor(void) {
    Menu10_Sub174 *subState;
    s32 i;

    subState = gCurrentActor->unk174;
    D_8003369C += 4.5f;
    if (D_8003369C > 0.0f) {
        D_8003369C = 0.0f;
    }
    switch (gCurrentActor->unk155) {
    case 0:
        gCurrentActor->unkE6 = 0x800;
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
        if (*gPlayerSlots->unk298 & 0x8000) {
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
            func_8071495C();
            func_80714CC0(&D_8071FE08, 8.3f, 160.0f, 120.0f, -10.0f);
            sfxPlayOnFreeSlot(0x23, 0x7FFF, 63.0f, 1.0f, 0, 0);
            sfxPlayOnFreeSlot(0x17, 0x7FFF, 63.0f, 1.0f, 0, 0);
            for (i = 0; i != 5; i++) {
                func_8071498C(menuSparkleParticleUpdate);
                func_8071495C();
                func_80714CC0(&D_8071FE64, 1.8f, 160.0f, 120.0f, -10.0f);
            }
        }
        if (subState->unk23C >= 0xC) {
            D_807FBB60 &= 0xFFFEFFFF;
        }
        break;
    }
    if (D_80033698 != 0) {
        D_80033698 -= 1;
    }
    if (gCurrentActor->unk155 < 6) {
        if (D_8003369C > -30.0) {
            D_807FBB60 |= 0x10000;
        } else {
            D_80033698 = 3;
        }
    }
    D_80033738 = 0x14;
    gCurrentActor->unk80 = -D_8003369C;
    gPlayerSlots->unk210 = gCurrentActor->unk7C;
    gPlayerSlots->unk214 = (D_80033678[D_80033F50] * 50.0) + (gCurrentActor->unk80 + 13.1f + D_8003369C) - 0.1;
    gPlayerSlots->unk218 = gCurrentActor->unk84 - 50.0f;
    gPlayerSlots->unk228 = gCurrentActor->unk7C;
    gPlayerSlots->unk22C = gPlayerSlots->unk214;
    gPlayerSlots->unk230 = 10020.0f;
    D_80754CE0 = D_80033678[D_80033F50] * 400.0f;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 D_8003378C[];
void actorDespawn(void *);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

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

    pos = gCurrentActor->unk174;
    if (D_807FBB4C->unk155 < 6) {
        if (D_80033738 == 0x14) {
            actorDespawn(gCurrentActor);
            D_80033738 += 1;
            actorSpawn(0x14D, 0xD7);
            gSpawnedActor->unk4->unk34 = 0.14f;
            gSpawnedActor->unk4->unk38 = 0.14f;
            gSpawnedActor->unk4->unk3C = 0.14f;
        } else if (D_80033738 == 0x15) {
            actorGetNodePos(D_807FBB4C, 2, &x[0], &y[0], &z[0]);
            actorGetNodePos(D_807FBB4C, 3, &x[1], &y[1], &z[1]);
            cx = (x[0] + x[1]) * 0.5f;
            cy = y[0];
            cz = (z[0] + z[1]) * 0.5f;
            gCurrentActor->unk7C = cx;
            gCurrentActor->unk80 = cy;
            gCurrentActor->unk84 = cz;
            pos->unk0 = gCurrentActor->unk7C;
            pos->unk4 = gCurrentActor->unk80;
            pos->unk8 = gCurrentActor->unk84;
            gCurrentActor->unkE6 = 0;
            gCurrentActor->unkE8 = 0x400;
            camProjectToScreen(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, &s[1], &s[0], 0, 1.0f, 0);
            s[0] = s[0] - 120.0f;
            if (s[0] < -35.0f) {
                if (s[0] > -75.0f) {
                    D_8003378C[0] = s[0];
                    D_8003378C[0x11] = s[0];
                }
            }
        }
    } else {
        gCurrentActor->unk7C = pos->unk0;
        gCurrentActor->unk80 = pos->unk4 - (D_80033F3C * 19.0f);
        gCurrentActor->unk84 = pos->unk8 - (D_80033F3C * 50.0f);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (D_80033698 != 0) {
        gCurrentActor->unk60 &= ~4;
    } else {
        gCurrentActor->unk60 |= 4;
    }
}


s32 menuCheckSaveFile(fileSlot)
    u8 fileSlot;
{
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
void hudPauseMenuRefreshTotals(void);

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

char *textTableGetString(s32, s32, s32);

void menuLoadTextTable(void) {
    s32 i;

    D_80033F28 = heapAlloc(0x194);
    i = 0;
    do {
        D_80033F28[i] = textTableGetString(0x25, i, 0);
        i++;
    } while (i != 0x65);
}
