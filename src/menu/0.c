#include "common.h"
#define PROTO_SKIP_effectCreateAtPosition // FAKE: callee prototype steer
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/104F0.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/7130.h"
#include "proto/global/90D80.h"
#include "proto/global/ACDC0.h"
#include "proto/global/C4620.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"
#include "proto/menu/0.h"

typedef struct {
    char pad0[0x340];
    f32 x;
    f32 y;
    f32 z;
} MenuActor_340;

typedef struct MenuStruct_80024000 {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ char pad3[3];
    /* 0x06 */ u8 unk6;
    /* 0x07 */ char pad7[1];
    /* 0x08 */ MenuActor_340 *unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char pad18;
    /* 0x19 */ s8 unk19;
    /* 0x1A */ u8 unk1A;
} MenuStruct_80024000;

typedef struct {
    s16 unk0;
    s16 unk2;
} MenuStruct_30A2;

extern u8 gCurrentWorldId;
extern s32 D_80032F48[][6];
extern MenuStruct_30A2 D_800330A2[];


void menuPlaySoundFromTable(MenuStruct_80024000 *menu) {
    s32 soundId = D_80032F48[mapGetHubWorldIndex(gCurrentWorldId, 0)][menu->unk1];

    if (soundId == 0) {
        csModelStateSetFirstByte(D_800330A2[menu->unk1A].unk0, 9);
        menu->unk0 = 4;
        menu->unk1 = 0;
        return;
    }
    if (soundId == 4) {
        menu->unk6 = 1;
    }
    camStartPath(0, (s16)soundId, 1);
    menu->unk1++;
}


extern u8 D_80720268;
MenuActor_340 *effectCreateAtPosition(void *, s32, s32, s32, f32);

void menuSpawnPositionalActor(MenuStruct_80024000 *menu) {
    menu->unk10 = 11.35f;
    menu->unkC = -6.55f;
    menu->unk14 = 6.6f;
    menu->unk6 = 0;
    effectSetMode(0);
    effectSetDepth(1);
    effectSetDuration(-1);
    effectSetMode(0);
    menu->unk8 = effectCreateAtPosition(&D_80720268, 0x3E99999A, 0x43350000, 0x40400000, 82.0f);
}


void menuUpdateFallingActor(MenuStruct_80024000 *menu) {
    MenuActor_340 *actor = menu->unk8;
    actor->x += menu->unkC;
    actor->z += menu->unk14;
    menu->unk10 += -1.0f;
    actor->y += menu->unk10;
    menu->unk6++;
    if (menu->unk6 >= 0x16) {
        menu->unk6 = 0;
        effectFreeAndUnlink(menu->unk8);
        menu->unk8 = NULL;
    }
}

extern void *gPrimaryPlayerActor;

void menuResetAudioState(void) {
    playerResumeLocomotion(gPrimaryPlayerActor);
    mapTransitionToPreviousOrExit();
    camStartPath(0, 7, 1);
}

typedef struct {
    char pad0[1];
    u8 unk1;
    char pad2[0x17];
    s8 unk19;
} MenuSubStruct_180;

typedef struct MenuRenderActor {
    char pad0[0x60];
    s32 unk60;
    char pad64[0xF0];
    u8 unk154;
    char pad155[0xA];
    u8 unk15F;
    char pad160[0x14];
    s16 *unk174;
    char pad178[8];
    MenuStruct_80024000 *unk180;
} MenuRenderActor;
extern MenuRenderActor *gCurrentActor;
extern s16 D_80750AC8;


void menuMainStateStep(MenuStruct_80024000 *menu, s32 playVoice) {
    s32 mode;

    switch (menu->unk1) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            if (playVoice != 0) {
                currentActorClearFlag();
                resQueueAttachActor(gCurrentActor, 0xB, 0);
                if ((mode = menu->unk1A) == 1) {
                    mode = 1;
                } else if (mode >= 2) {
                    mode = 2;
                } else {
                    mode = 3;
                }
                D_80750AC8 = menu->unk1A;
                resQueueAttachActor(gCurrentActor, 0xB, mode);
            } else {
                if (menu->unk1A == 1) {
                    mode = 5;
                } else {
                    mode = 6;
                }
                D_80750AC8 = menu->unk1A;
                resQueueAttachActor(gCurrentActor, 0xB, mode);
            }
            menu->unk1++;
        }
        break;
    case 1:
        if (!(gCurrentActor->unk60 & 0x02000000)) {
            camResumePath();
            menu->unk1++;
        }
        break;
    case 2:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            if (menu->unk1A != 0) {
                camStartPath(0, 5, 1);
                menu->unk1++;
            } else {
                menu->unk0 = 4;
                menu->unk1 = 0;
            }
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        if (menu->unk6 != 0) {
            if (menu->unk6 == 1) {
                if (currentActorTestClearFlag() != 0) {
                    currentActorClearFlag();
                    menu->unk6 = 2;
                }
            } else {
                menuUpdateFallingActor(menu);
            }
        }
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            menuPlaySoundFromTable(menu);
        }
        break;
    }
}

void menuTransitionStep(menu, targetState)
MenuStruct_80024000 *menu;
u8 targetState;
{
    switch (menu->unk1) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            resQueueAttachActor(gCurrentActor, 0xB, targetState);
            menu->unk1++;
        }
        break;
    case 1:
        if (!(gCurrentActor->unk60 & 0x02000000)) {
            camResumePath();
            menu->unk1++;
        }
        break;
    case 2:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            menu->unk0 = 4;
            menu->unk1 = 0;
        }
        break;
    }
}

#ifndef WRITE_GFX
#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }
#endif

extern u8 D_1000118[];
extern u8 D_20000C0[];
extern u8 D_2000180[];


Gfx *menuDrawOptionsOverlay(Gfx *glist, MenuRenderActor *actor) {
    s32 y;
    MenuStruct_80024000 *menu = actor->unk180;
    char textBuf[0x28];

    WRITE_GFX(glist++, 0xDE000000, D_1000118);
    WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);
    if (menu->unk1 >= 4) {
        s32 i;
        WRITE_GFX(glist++, 0xDA380003, D_2000180);
        WRITE_GFX(glist++, 0xDA380007, D_20000C0);
        WRITE_GFX(glist++, 0xE7000000, 0);
        y = 0xF0;
        for (i = 0; i < 8; i++) {
            if (i + 4 == menu->unk1) {
                WRITE_GFX(glist++, 0xFA000000, -1);
            } else {
                WRITE_GFX(glist++, 0xFA000000, -0x80);
            }
            glist = hudDrawScaledText(glist, 0x280, y, 0.6f, textTableGetString(0x2A, i + 3, 1));
            y += 0x3C;
        }
    } else {
        WRITE_GFX(glist++, 0xFA000000, (actor->unk15F & 0xFF) | ~0xFF);
        _sprintf(textBuf, "q %s", textTableGetString(0x2A, 0, 1));
        glist = textDrawStringVtx(glist, 1, 0x15E, 0x190, textBuf, 1);
        _sprintf(textBuf, "b %s", textTableGetString(0x2A, 1, 1));
        glist = textDrawStringVtx(glist, 1, 0x15E, 0x1F4, textBuf, 1);
        if (menu->unk19 != 0) {
            _sprintf(textBuf, "n %s", textTableGetString(0x2A, 2, 1));
            glist = textDrawStringVtx(glist, 1, 0x15E, 0x258, textBuf, 1);
        }
    }
    return glist;
}

typedef struct {
    char pad0[0x2C];
    u16 unk2C;
    char pad2E[6];
} MenuControllerPad;

typedef struct {
    char pad0[3];
    s8 unk3;
} MenuStickAxis;

#define MenuM0_X18(p) (((s8 *)(p))[0x18])

extern MenuControllerPad gPlayerPadState[];
extern MenuStickAxis *D_807ECDEC;
extern u8 gCurrentPlayerIndex;
extern u8 gPlayerInventoryTable[][0x5E];
extern u8 gPlayerCharacterId;
extern u8 D_800330C0[];
extern u8 D_80032F50;
extern s16 D_800330D8;


void menuUpdateOptionsState(MenuStruct_80024000 *menu) {
    s32 i;
    s32 changed;
    u8 *playerSaveData;
    s32 temp;

    changed = 0;
    D_800330D8 = 0;
    switch (menu->unk1) {
    case 2:
    case 0x37:
        break;
    case 0:
        if (listContainsS16(4) != 0) {
            playerSaveData = gPlayerInventoryTable[gPlayerCharacterId];
            for (i = 0; i < 8; i++) {
                if (flagGet((s16)flagGridIndex(0x1D5, i, gPlayerCharacterId), 0) != 0) {
                    temp = flagGridIndex(0x1FD, i, gPlayerCharacterId);
                    if (flagGet((s16)temp, 0) == 0) {
                        flagSet((s16)temp, 1, 0);
                        ((u16 *)(playerSaveData + i * 2))[0x21]++;
                        changed = 1;
                    }
                }
            }
            func_806F8278(0);
        }
        if (changed != 0) {
            eepromSavePlayerData();
        }
        if (camIsCutsceneActive() == 0) {
            menu->unk1++;
            playerStateQueueCallback(0x55, 0, 0);
        }
        break;
    case 1:
        if (gPlayerPadState[gCurrentPlayerIndex].unk2C & 0x8000) {
            gCurrentActor->unk15F = 0;
            menu->unk1 = 3;
        } else {
            menu->unk19 = 1;
            i = 0x1FD;
            do {
                if (flagGet((s16)i, 0) == 0) {
                    menu->unk19 = 0;
                    i = 0x224;
                }
                i++;
            } while (i < 0x225);
            {
                u8 a3 = gCurrentActor->unk15F;
                s32 d = 0xFF - a3;
                s32 inc;
                if (d >= 9) {
                    inc = 8;
                } else {
                    inc = d;
                }
                gCurrentActor->unk15F = a3 + inc;
            }
            renderCallbacksRegister(menuDrawOptionsOverlay, gCurrentActor, 3);
            if (gPlayerPadState[gCurrentPlayerIndex].unk2C & 0x4000) {
                menuResetAudioState();
                menu->unk1 = 2;
            } else if (menu->unk19 != 0 && (gPlayerPadState[gCurrentPlayerIndex].unk2C & 8)) {
                menu->unk1 = 4;
            }
        }
        break;
    case 3:
        D_800330D8 = 1;
        if (gPlayerPadState[gCurrentPlayerIndex].unk2C & 0xC000) {
            menu->unk1 = 1;
        }
        break;
    default:
        if (gPlayerPadState[gCurrentPlayerIndex].unk2C & 0x4000) {
            menu->unk1 = 1;
        } else {
            s8 v1 = D_807ECDEC->unk3;
            if (v1 >= 0x29 && MenuM0_X18(menu) < 0x29) {
                menu->unk1--;
                sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 64.0f, 1.0f, 0, 0);
                v1 = D_807ECDEC->unk3;
            }
            if (v1 < -0x28 && MenuM0_X18(menu) >= -0x28) {
                menu->unk1++;
                sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 64.0f, 1.0f, 0, 0);
            }
            menu->unk1 = ((menu->unk1 - 4) & 7) + 4;
        }
        if (gPlayerPadState[gCurrentPlayerIndex].unk2C & 0x8000) {
            menuTransitionWithStateD(D_800330C0[menu->unk1]);
            D_80032F50 = 1;
            menu->unk1 = 0x37;
        }
        renderCallbacksRegister(menuDrawOptionsOverlay, gCurrentActor, 3);
        break;
    }
    MenuM0_X18(menu) = D_807ECDEC->unk3;
}


void menuProcessOptionInput(MenuStruct_80024000 *menu) {
    switch (menu->unk1) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            menu->unk1++;
            D_80750AC8 = menuCalculateBonusDuration();
            resQueueAttachActor(gCurrentActor, 0xB, 8);
        }
        break;
    case 1:
        if (!(gCurrentActor->unk60 & 0x02000000)) {
            camResumePath();
            menu->unk1++;
        }
        break;
    }
}

extern s16 D_8076AEF2;


void menuDispatchAction(void) {
    s32 pad;
    s32 targetState;
    s32 pad2;
    s32 camPathIndex;
    u8 isSessionActive;
    MenuStruct_80024000 *menu;

    targetState = -1;
    isSessionActive = 0;
    menu = gCurrentActor->unk180;
    if (!(gCurrentActor->unk60 & 0x10)) {
        camPathIndex = 1;
        menu->unk2 = flagCountRange(0x1FD, 0x28, 0);
        menu->unk1A = flagGridSumRows(0x1D5, 0, 7, gPlayerCharacterId);
        menu->unk1A -= flagGridSumRows(0x1FD, 0, 7, gPlayerCharacterId);
        if (D_8076AEF2 != 0x1C) {
            if (flagGet(0x174, 0) == 0) {
                menu->unk0 = 0;
                menu->unk1 = 0;
                camPathIndex = 0;
                playerWaypointPathStartPacked(gPrimaryPlayerActor, 0, 0, 0);
                flagSet(0x174, 1, 0);
            } else {
                if (menu->unk2 == 0x28) {
                    menu->unk0 = 2;
                    menu->unk1 = 0;
                } else {
                    if (menu->unk1A == 0) {
                        menu->unk0 = 1;
                        menu->unk1 = 0;
                    } else {
                        menu->unk0 = 3;
                        menu->unk1 = 0;
                    }
                }
            }
            camStartPath(0, (s16)camPathIndex, 1);
        } else {
            menu->unk0 = 5;
            menu->unk1 = 0;
        }
        currentActorClearFlag();
        menuSpawnPositionalActor(menu);
        isSessionActive = D_80032F50;
        D_80032F50 = 0;
    }
    switch (menu->unk0) {
    case 0:
        menuMainStateStep(menu, 1);
        break;
    case 3:
        menuMainStateStep(menu, 0);
        break;
    case 1:
        targetState = 4;
        /* fallthrough */
    case 2:
        if (targetState < 0) {
            targetState = 7;
        }
        if (isSessionActive != 0) {
            targetState = 0xB;
        }
        menuTransitionStep(menu, targetState);
        break;
    case 4:
        menuUpdateOptionsState(menu);
        break;
    case 5:
        menuProcessOptionInput(menu);
        break;
    }
    behaviourFrameBegin();
    actorScriptedCommandUpdate();
    actorUpdateModelMatrix(gCurrentActor, 0);
}
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
} MenuProgressGridVtx;

extern s32 D_800330D0;
extern void *D_800330D4;
extern u8 D_800330E0[];
extern s16 D_80033220[];
extern u8 D_80033228[];
extern s8 D_80033258;
extern MenuProgressGridVtx *D_80033F10;

void *memcpy(void *, const void *, s32);

void menuUpdateProgressGrid(void) {
    s16 *pSlideY;
    s32 flag;
    s32 n;
    s32 r;
    s32 j;
    s32 k;
    s32 idx;

    pSlideY = gCurrentActor->unk174;
    if (!(gCurrentActor->unk60 & 0x10)) {
        *pSlideY = 0xF0;
        gCurrentActor->unk154 = 0;
        D_800330D0 = (s32)heapAlloc(0x80);
        D_800330D4 = heapAlloc(0x140);
        memcpy(D_800330D4, D_800330E0, 0x140);
        *pSlideY = -0x3E8;
        D_80033F10 = heapAlloc(0x1400);
        flag = flagCountRange(0x1FD, 0x28, 0) == 0x28;
        n = 0;
        for (r = 0; r < 5; r++) {
            for (j = 0; j < 8; j++) {
                idx = r * 9;
                for (k = 0; k < 4; k++) {
                    if (flag != 0) {
                        idx = 0x15;
                    }
                    D_80033F10[n].unk0 = (j * 30 + 40) << 2;
                    D_80033F10[n].unk2 = (D_80033220[k] + r * 30 + 0x2D) << 2;
                    D_80033F10[n].unk4 = -0xA;
                    D_80033F10[n].unk8 = (j * 30) << 6;
                    D_80033F10[n].unkA = (D_80033220[k] + r * 30) << 6;
                    D_80033F10[n].unkC = D_80033228[idx];
                    D_80033F10[n].unkD = D_80033228[idx + 1];
                    D_80033F10[n].unkE = D_80033228[idx + 2];
                    D_80033F10[n].unkF = 0xFF;
                    D_80033F10[n].unk6 = 0;
                    n++;
                    D_80033F10[n].unk0 = (j * 30 + 70) << 2;
                    D_80033F10[n].unk2 = (D_80033220[k] + r * 30 + 0x2D) << 2;
                    D_80033F10[n].unk4 = 0x16;
                    D_80033F10[n].unk8 = (j * 30 + 30) << 6;
                    D_80033F10[n].unkA = (D_80033220[k] + r * 30) << 6;
                    D_80033F10[n].unkC = D_80033228[idx++];
                    D_80033F10[n].unkD = D_80033228[idx++];
                    D_80033F10[n].unkE = D_80033228[idx];
                    D_80033F10[n].unkF = 0xFF;
                    D_80033F10[n].unk6 = 0;
                    n++;
                    idx++;
                }
            }
        }
        D_80033258 = flag;
    }
    if (D_800330D8 != 0) {
        if (*pSlideY == -0x3E8) {
            sfxPlayOnFreeSlot(0x2A3, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        *pSlideY += 0x80;
        if (*pSlideY > 0) {
            *pSlideY = 0;
        }
    } else {
        if (*pSlideY == 0) {
            sfxPlayOnFreeSlot(0x2A3, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        *pSlideY -= 0x80;
        if (*pSlideY < -0x3E8) {
            *pSlideY = -0x3E8;
        }
    }
    D_800330D8 = 0;
    if (*pSlideY >= -0x3E7) {
        renderCallbacksRegister(menuDrawProgressGrid, gCurrentActor, 3);
    }
}

extern u8 gGfxBufferIndex;
extern s32 gFrameCounter;

Gfx *menuDrawProgressGrid(Gfx *g, MenuRenderActor *actor) {
    s32 pad;
    s32 tex;
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    s16 *pSlideY = actor->unk174;
    MenuProgressGridVtx *v;
    s32 k;
    f32 mf[4][4];
    s8 allCollected;

    gDPPipeSync(g++);
    gSPDisplayList(g++, D_1000118);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x03024000);
    gDPSetPrimColor(g++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPSetCombine(g++, 0x121803, 0xFF0FFFFF);
    gSPMatrix(g++, D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    guTranslateF(mf, 8.0f, (f32) *pSlideY, 0.0f);
    guMtxF2L(mf, (Mtx *)((gGfxBufferIndex << 6) + D_800330D0));
    gSPMatrix(g++, (gGfxBufferIndex << 6) + D_800330D0, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 12, 2, 0);
    tex = texCacheFindOrLoad(0xA3);
    v = D_80033F10;
    i = 0;
    allCollected = 1;
    for (y = 0; y < 150; y += 30, i++) {
        j = 0;
        for (x = 0; x < 240; x += 30) {
            gDPPipeSync(g++);
            if (flagGet((s16)flagGridIndex(0x1FD, j, i), 0) != 0) {
                gDPSetPrimColor(g++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                allCollected = 0;
                gDPSetPrimColor(g++, 0, 0, 0, 0, 0, 0);
            }
            gDPLoadTextureTile_4b(g++, tex, G_IM_FMT_I, 240, 150, x, y, x + 30, y + 30, 0,
                                  G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            gSPVertex(g++, osVirtualToPhysical(v), 8, 0);
            gSP2Triangles(g++, 0, 1, 2, 0, 1, 3, 2, 0);
            gSP2Triangles(g++, 2, 3, 4, 0, 3, 5, 4, 0);
            gSP2Triangles(g++, 4, 5, 6, 0, 5, 7, 6, 0);
            v += 8;
            j++;
        }
    }
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0);
    gDPSetCombine(g++, 0x119623, 0xFF2FFFFF);
    gDPSetPrimColor(g++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 12, 2, 0x2000);
    tex = texCacheFindOrLoad(0xA2);
    gDPLoadTextureBlock(g++, tex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP | G_TX_NOMIRROR,
                        G_TX_WRAP | G_TX_NOMIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gSPVertex(g++, osVirtualToPhysical(D_800330D4), 20, 0);
    gSP2Triangles(g++, 0, 1, 2, 0, 0, 2, 3, 0);
    gSP2Triangles(g++, 4, 5, 6, 0, 4, 6, 7, 0);
    gSP2Triangles(g++, 8, 9, 10, 0, 8, 10, 11, 0);
    gSP2Triangles(g++, 12, 13, 14, 0, 12, 14, 15, 0);
    gDPPipeSync(g++);
    if (allCollected != 0 && (gFrameCounter & 0x1F) < 0x14U) {
        tex = texCacheFindOrLoad(0x44);
        gDPSetPrimColor(g++, 0, 0, 0, 0xFF, 0, 0xFF);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x504240);
        gDPLoadTextureBlock(g++, tex, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP | G_TX_NOMIRROR,
                            G_TX_WRAP | G_TX_NOMIRROR, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
        gSP2Triangles(g++, 16, 17, 18, 0, 16, 18, 19, 0);
        if (D_80033258 == 0) {
            for (k = 0; k < 0x140; k++) {
                D_80033F10[k].unkC = 0;
                D_80033F10[k].unkD = 0xFF;
                D_80033F10[k].unkE = 0xFF;
            }
            D_80033258 = 1;
        }
    }
    gSPMatrix(g++, D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    return g;
}

void menuProgressGridNoop(void) {
}
