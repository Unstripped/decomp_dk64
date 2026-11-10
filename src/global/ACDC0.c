#include "common.h"
#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_mapGetHubWorldIndex // FAKE: callee prototype steer
#define PROTO_SKIP_mapGetWorldIndex // FAKE: callee prototype steer
#define PROTO_SKIP_renderRotatedSprite // FAKE: callee prototype steer
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
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s8 unk10;
    /* 0x11 */ u8 unk11[7];
} HudTextEntry; // size = 0x18

typedef struct HudEntry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8[2];
    /* 0x0C */ s16 unkC[2];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s8 unk12;
    /* 0x13 */ s8 unk13;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
    /* 0x16 */ s8 unk16;
    /* 0x17 */ s8 unk17;
    /* 0x18 */ u8 unk18;
} HudEntry;

typedef struct HudTextObj {
    /* 0x000 */ u8 pad0[0x340];
    /* 0x340 */ f32 unk340;
    /* 0x344 */ f32 unk344;
    /* 0x348 */ u8 pad348[0x18];
    /* 0x360 */ f32 unk360;
    /* 0x364 */ f32 unk364;
    /* 0x368 */ u8 pad368[2];
    /* 0x36A */ u8 unk36A;
    /* 0x36B */ u8 unk36B;
    /* 0x36C */ u8 unk36C;
    /* 0x36D */ u8 pad36D[0x17];
    /* 0x384 */ f32 *unk384;
} HudTextObj;

typedef struct HudCountEntry {
    /* 0x00 */ u8 pad0[0x42];
    /* 0x42 */ u16 unk42[14];
} HudCountEntry; // size = 0x5E

#define HUD_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern Gfx D_1000118;
extern Mtx D_2000180;
extern Mtx D_20000C0;

extern s8 D_80750560[9];
extern HudTextEntry *D_807FC7F0[2];
extern s8 D_807FC7F8[2];
extern u32 gGlobalPauseFlags;
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;
extern u8 **D_807FC7E0;
extern void **D_807FC7E8;
extern s8 D_807FC80F;
extern u8 D_807FC810;
extern f32 D_807FC808;
extern s8 D_8075052C;
extern s8 D_807505D0;
extern s16 D_807FC828;
extern s16 D_807FC82A;
extern s16 D_807FC82C;
extern s16 D_807FC82E;
extern s16 D_807FC830;
extern s16 D_807FC832;
extern s16 D_807FC834;
extern s16 D_807FC836;
extern s16 D_807FC838;
extern HudCountEntry gPlayerInventoryTable[];
extern HudCountEntry D_807FCB26[];
extern s16 D_80744710[];
extern s16 D_80744720[];
extern s16 D_807505B2[];
extern s16 D_807505B8[];
extern s16 D_807505CC[];
extern s8 D_80750530[5];
extern u8 D_80750531[];
extern u16 D_807ECD58;
extern s32 gCurrentMap;
extern u8 D_807505F8[];
extern s8 D_807FC80E;
extern s8 gPausingPlayer;
extern PlayerStruct *gPlayerSlots;
extern s8 D_8076A105;

Gfx *renderRotatedSprite(Gfx *, s32, s32, u8, s32, s32, s32, s32, f32, f32, s32, f32); // FAKE: callee prototype steer
f32 sqrtf(f32);

s32 hudFindItemIndex(s8 itemId) {
    s32 i;

    for (i = 0; i < 9; i++) {
        if (itemId == D_80750560[i]) {
            return i;
        }
    }
    return 0;
}


extern OSContPad *D_807ECDEC;
extern u8 D_807467E4;
extern s32 D_8076A098;
extern u8 gCurrentWorldId;
extern s32 gGlobalOverlayFlags;
extern f32 D_807FC7FC;
extern s8 D_807505D4;
extern s8 D_80750580;
extern s16 D_807505A4[];
extern f32 D_80750584[];
extern s8 D_807FC800;
extern s16 D_807FC802;
extern f32 D_807FC804;
extern s8 D_807FC80C;
extern s8 D_807FC80D;
extern s16 D_807FC83A;
extern s8 D_807FC83C;
extern s8 D_807FC8B8;

s32 mapGetWorldIndex(); // FAKE: callee prototype steer
s32 mapGetHubWorldIndex(); // FAKE: callee prototype steer

#define HUD_PAUSE_MODE (*(s8 *)D_807505CC)

void hudPauseMenuUpdate(void) {
    HudEntry *hud;
    s32 i;
    s32 diff;
    s32 flag;
    s32 moved;
    s32 buttons;
    s32 x;
    s32 a2;
    s32 lim;
    s16 half;
    if (D_807505D4) {} // FAKE: dead read, splits the D_807505D4 address web

    hud = gCurrentActor->customState;
    i = gCurrentMap;
    switch (i) {
        case 0x6:
        case 0xE:
        case 0x1B:
        case 0x27:
        case 0x37:
        case 0x52:
        case 0x6A:
        case 0xB9:
            HUD_PAUSE_MODE = 1;
            break;
        default:
            if (mapGetWorldIndex(gCurrentMap & 0xFF) == 9 || (gGlobalOverlayFlags & 0x10000000)) {
                HUD_PAUSE_MODE = 2;
            } else {
                HUD_PAUSE_MODE = 0;
            }
            break;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        D_807FC7E0 = heapAlloc(0x6C);
        for (i = 0; i < 0x1B; i++) {
            D_807FC7E0[i] = textTableGetString(0x24, i, 0);
        }
        D_807FC7E8 = heapAlloc(0x24);
        for (i = 0; i < 9; i++) {
            D_807FC7E8[i] = textTableGetString(0x23, i, 0);
        }
        D_8076A098++;
        D_807FC7FC = gPlayerSlots->camY;
        D_807505D4 = 0;
        D_807FC8B8 = 0;
        D_80750580 = 1;
        D_807505D0 = 7;
        while (D_807505D0 >= 0 && flagGet(D_807505D0 + 0x1C5, 0) == 0) {
            D_807505D0--;
        }
        D_807505D0++;
        hud->unk12 = 0;
        hud->unk17 = 0;
        hud->unk16 = -1;
        hud->unk0 = 1.0f;
        hud->unk4 = 0.0f;
        hud->unk14 = playerGetResolvedKongId(0);
        hud->unk8[0] = hudFindItemIndex(mapGetHubWorldIndex(gCurrentWorldId, 1));
        if (D_807505D0 < hud->unk8[0]) {
            hud->unk8[0] = 0;
        }
        hud->unk8[1] = hud->unk8[0];
        hud->unkC[0] = 0;
        hud->unkC[1] = 0xF0;
        hud->unk15 = 0;
        hud->unk10 = D_807505A4[hud->unk14];
        D_807FC800 = hud->unk14;
        D_807FC802 = 0;
        D_807FC804 = 0.0f;
        D_807FC808 = 0.0f;
        D_807FC80C = 0;
        D_807FC80D = D_807FC80C;
        D_807FC7F0[0] = heapAlloc(0x1E0);
        D_807FC7F0[1] = D_807FC7F0[0] + 10;
        D_807FC7F8[0] = 0;
        D_807FC7F8[1] = 0;
        D_8075052C = 0;
        D_807FC80E = 1;
        hudPauseMenuRefreshTotals();
        hudPauseMenuBuildPage(hud, 0);
        gGlobalPauseFlags &= 0xFFFEFFCF;
        screenWipeStart(7);
    }
    if (hud->unk0 == 0.0f && D_807FC8B8 == 0) {
        moved = hud->unk8[hud->unk15] != hud->unk8[1 - hud->unk15];
        buttons = *gPlayerSlots->heldButtonsPtr;
        if (moved == 0 && hud->unk4 == 0.0f && D_807FC80C == D_807FC80D) {
            if (buttons & 0x5000) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                if (hud->unk12 == 0 && hud->unk17 == 3) {
                    hud->unk17 = 2;
                } else {
                    hud->unk16 = 1;
                    hud->unk13 = -1;
                }
                buttons = 0;
            }
            if (D_807FC828 > 0) {
                flag = 0;
                if (buttons & 0x10) {
                    hud->unk13 = hud->unk12 + 1;
                    if (hud->unk13 >= 4) {
                        hud->unk13 = 0;
                    }
                    flag = 1;
                } else if (buttons & 0x2000) {
                    hud->unk13 = hud->unk13 - 1;
                    if (hud->unk13 < 0) {
                        hud->unk13 = 3;
                    }
                    flag = 1;
                }
                if (flag != 0) {
                    hud->unk16 = 1;
                    D_8075052C = 0;
                    buttons = 0;
                    sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
            }
        }
        i = hud->unk12;
        switch (i) {
            case 0:
                if (hud->unk17 != 3) {
                    lim = D_807ECDEC->stick_y;
                    if (lim < -0x32) {
                        if (D_807FC80E == 0) {
                            hud->unk17 = hud->unk17 + 1;
                            buttons = 0;
                            if (hud->unk17 >= 3) {
                                hud->unk17 = 0;
                            }
                            sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
                        }
                        D_807FC80E = 1;
                    } else if (lim >= 0x33) {
                        if (D_807FC80E == 0) {
                            hud->unk17 = hud->unk17 - 1;
                            buttons = 0;
                            if (hud->unk17 < 0) {
                                hud->unk17 = 2;
                            }
                            sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
                        }
                        D_807FC80E = 1;
                    } else {
                        D_807FC80E = 0;
                    }
                    if (buttons & 0x8000) {
                        if (hud->unk17 == 2) {
                            hud->unk17 = 3;
                        } else if (hud->unk17 == 1) {
                            if (HUD_PAUSE_MODE != 0) {
                                mapRequestTransition(gCurrentMap, 0);
                            } else if (hud->unk18 == 0) {
                                eepromSavePlayerData();
                                hud->unk18 = 1;
                            } else if (D_807505D4 == 0) {
                                sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                D_807505D4 = 0x2D;
                            }
                        } else {
                            hud->unk16 = 1;
                            hud->unk13 = -1;
                        }
                    }
                } else if (buttons & 0x8000) {
                    i = (a2 = mapGetHubWorldIndex(gCurrentWorldId, 1)) == 8;
                    if (D_807FC8B8 && D_807FC8B8) {} // FAKE: steers seq temp register (a0 not v1)
                    if (i) {
                        i = menuGetTimerFlag() != 0;
                    }
                    D_807FC8B8 = 1;
                    if (HUD_PAUSE_MODE == 0 && a2 != 7 && a2 != 0xD && a2 != 9 && i == 0) {
                        if (a2 == 0xA) {
                            menuReturnToTitle();
                        } else if (func_805FEF74(gCurrentMap) == 0) {
                            x = gGlobalOverlayFlags & 1;
                            if (x != 0 && a2 == 8) {
                                flagSet(0x5C, 1, 2);
                                mapRequestTransition(0x22, 0xC);
                            } else if (x != 0 && gCurrentMap != 0x3C) {
                                mapRequestTransition(0x2A, 2);
                            } else {
                                mapTransitionToWorldHub(a2);
                            }
                        }
                    } else if (HUD_PAUSE_MODE != 0) {
                        if (HUD_PAUSE_MODE == 2) {
                            mapTransitionToPreviousOrExit();
                        } else {
                            mapCheckAutoTransition();
                        }
                    } else if (a2 == 7 || i != 0) {
                        menuResetAndTransitionToCredits();
                    }
                }
                break;
            case 1:
                hud->unk10 = D_807505A4[D_807FC800] + (s16)(D_807FC804 * 0.5f * D_807FC802);
                hud->unk10 = hud->unk10 & 0xFFF;
                if (D_807FC804 == 0.0f) {
                    D_807FC802 = 0;
                    if (moved == 0) {
                        x = D_807ECDEC->stick_x;
                        if (x < -0x28) {
                            do {
                                D_807FC802 -= 0x333;
                                D_807FC800 += 1;
                                if (D_807FC800 >= 5) {
                                    D_807FC800 = 0;
                                }
                            } while (D_80750530[D_807FC800] == 0);
                        } else if (x >= 0x29) {
                            do {
                                D_807FC802 += 0x333;
                                D_807FC800 -= 1;
                                if (D_807FC800 < 0) {
                                    D_807FC800 = 4;
                                }
                            } while (D_80750530[D_807FC800] == 0);
                        }
                        if (D_807FC800 != hud->unk14) {
                            D_807FC804 = 2.0f;
                            sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                        }
                    }
                } else {
                    D_807FC804 -= 0.125f;
                    if (D_807FC804 < 0.0f) {
                        D_807FC804 = 0.0f;
                    }
                    hud->unk4 = D_807FC804 - 1.0f;
                    if (hud->unk4 < 0.0f) {
                        hud->unk4 = -hud->unk4;
                    }
                    hud->unk4 = 1.0f - hud->unk4;
                    hud->unk4 = hud->unk4 * 1.3f;
                    if (hud->unk4 > 1.2f && D_807FC800 != hud->unk14) {
                        hud->unk14 = D_807FC800;
                        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
                        hudPauseMenuBuildPage(hud, 1);
                    }
                    if (D_807FC800 == hud->unk14 && hud->unk4 > 1.0f) {
                        hud->unk4 = 1.0f;
                    }
                }
                hudPauseMenuSlidePage(hud, moved, buttons);
                break;
            case 2:
                hud->unk10 = hud->unk10 + 0x28;
                hud->unk10 = hud->unk10 & 0xFFF;
                hudPauseMenuSlidePage(hud, moved, buttons);
                break;
            case 3:
                diff = i = -mathAngleSignedDistance(D_807FC80D * D_807FC83A, hud->unk10);
                flag = D_807FC83A / 10;
                if (diff > 0) {
                    if (flag < diff) {
                        i = flag;
                    }
                    hud->unk10 = hud->unk10 + i;
                } else if (diff < 0) {
                    if (diff < -flag) {
                        i = -flag;
                    }
                    hud->unk10 = hud->unk10 + i;
                } else {
                    flag = 0;
                    x = D_807ECDEC->stick_x;
                    if (x < -0x28) {
                        D_807FC80D += 1;
                        if (D_807FC80D >= D_807FC83C) {
                            D_807FC80D = 0;
                        }
                        flag = 1;
                    } else if (x >= 0x29) {
                        D_807FC80D -= 1;
                        if (D_807FC80D < 0) {
                            D_807FC80D = D_807FC83C - 1;
                        }
                        flag = 1;
                    }
                    if (flag != 0 && D_807FC80D != D_807FC80C) {
                        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    }
                }
                hud->unk10 = hud->unk10 & 0xFFF;
                flag = D_807FC83A >> 1;
                if (diff < 0) {
                    diff = -diff;
                }
                diff = diff - flag;
                if (diff < 0) {
                    diff = -diff;
                }
                if (flag < diff) {
                    diff = flag;
                }
                diff = flag - diff;
                hud->unk4 = (f32)diff / (f32)((f64)(f32)flag * 0.9);
                if (hud->unk4 > 1.0f && D_807FC80D != D_807FC80C) {
                    D_807FC80C = D_807FC80D;
                }
                break;
        }
    }
    if (hud->unk16 == 1) {
        hud->unk0 = hud->unk0 + 0.13f;
        if (hud->unk0 > 1.3f) {
            hud->unk0 = 1.0f;
            if (hud->unk13 == -1) {
                hudFreeBuffers();
            } else {
                hud->unk12 = hud->unk13;
                hud->unk16 = -1;
                hudPauseMenuBuildPage(hud, 0);
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
            }
        }
    } else if (hud->unk0 > 0.0f && D_8075052C == 0) {
        hud->unk0 = hud->unk0 - 0.2f;
        if (hud->unk0 < 0.0f) {
            hud->unk0 = 0.0f;
            D_8075052C = 3;
            sfxPlayOnFreeSlot(0x3C, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
    }
    D_807505D4--;
    if (D_807505D4 < 0) {
        D_807505D4 = 0;
    }
    if (D_807467E4 == 0x1C) {
        sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
    if (D_8075052C != 0) {
        D_8075052C -= 1;
        hud->unk0 = D_80750584[D_8075052C];
        gPlayerSlots->camY = D_807FC7FC + hud->unk0 * 100.0;
    }
    renderCallbacksRegister(hudDrawDimOverlay, gCurrentActor, 1);
    renderCallbacksRegister(hudPauseMenuRender, gCurrentActor, 5);
}

#undef HUD_PAUSE_MODE

void hudFreeBuffers(void) {
    s32 i;
    PlayerState *ps;

    ps = gPrimaryPlayerActor->customState;
    gGlobalPauseFlags |= 0x40;
    if (!(ps->stateFlags & 0x20000000)) {
        gGlobalPauseFlags |= 0x10030;
    }
    heapFree(D_807FC7F0[0]);
    D_807FC7F0[0] = NULL;
    D_807FC7F0[1] = NULL;
    D_807FC7F8[0] = 0;
    D_807FC7F8[1] = 0;
    for (i = 0; i < 0x1B; i++) {
        heapFreeDeferred(D_807FC7E0[i]);
    }
    heapFreeDeferred(D_807FC7E0);
    for (i = 0; i < 9; i++) {
        heapFreeDeferred(D_807FC7E8[i]);
    }
    heapFreeDeferred(D_807FC7E8);
}

Gfx *hudSetupTextState(Gfx *dl) {
    gSPDisplayList(dl++, &D_1000118);
    gSPMatrix(dl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(dl++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    HUD_WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
    return dl;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA94.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AABC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AACC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AADC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAE4.s")


f32 mathCosF(s16);
f32 mathSinF(s16);
extern s16 D_807FC992[];
extern u8 D_807FCC4C;
extern s8 D_807FCC4B;
extern s32 gFrameCounter;
extern u8 gCurrentWorldId;
extern s8 D_80750538;
extern s16 D_8075056C[];
extern s8 D_807FC80C;
extern s8 D_807FC818[];
extern f32 D_807FC840[];
extern f32 D_807FC868[];
extern f32 D_807FC890[];

Gfx *hudPauseMenuRender(Gfx *dl, Actor *actor) {
    u8 buf[0x40];
    HudEntry *hud;
    s16 j;
    s16 i;
    s16 y;
    s32 off;
    s32 t0;
    HudTextEntry *it;
    HudCountEntry *tab;
    Gfx *ret;
    Gfx *list;
    s32 hubWorld;
    s16 ang;
    s16 y0;
    s8 s2;
    u8 ph;
    f32 fa;
    f32 fb;
    f32 fc;
    f32 fd;
    f32 fadeInput0;
    f32 fadeInput4;
    s32 cnt;
    u8 framePad[4];

    hud = actor->customState;
    fadeInput0 = hud->unk0;
    tab = gPlayerInventoryTable;
    hubWorld = mapGetHubWorldIndex(gCurrentWorldId, 1);
    list = heapAlloc(0x1F40);
    heapFreeDeferred(list);
    gSPDisplayList(dl++, list);
    ret = dl;
    dl = hudSetupTextState(list);
    for (i = 0; i < 2; i++) {
        it = D_807FC7F0[i];
        if (it != NULL) {
            for (j = 0; j < D_807FC7F8[i]; j++) {
                fa = hud->unk0;
                if (((HudTextEntry *)((u8 *)it + j * 0x18))->unk10 == 2) {
                    fa += hud->unk4;
                }
                off = ((HudTextEntry *)((u8 *)it + j * 0x18))->unk8; // FAKE: byte-offset entry spelling (all 8 reads in this loop) instead of it[j] steers the ugen scratch ring
                y = ((HudTextEntry *)((u8 *)it + j * 0x18))->unkA;
                off = (u16)(off * 4) + (s16)(s64)(s32)((f32)fa * ((HudTextEntry *)((u8 *)it + j * 0x18))->unk0); // FAKE: narrow through a 64-bit pair to preserve the ugen scratch-register order.
                y *= 4;
                y += (u16)(s32)(fa * ((HudTextEntry *)((u8 *)it + j * 0x18))->unk4);
                off = (s16)((u32)off + ((HudTextEntry *)((u8 *)it + j * 0x18))->unkC * 4);
                y += ((HudTextEntry *)((u8 *)it + j * 0x18))->unkE * 4;
                y += hud->unkC[i] * 4;
                dl = textDrawStringVtx(dl, 1, off, y, ((HudTextEntry *)((u8 *)it + j * 0x18))->unk11, 1);
            }
        }
    }

    if (list == NULL) {} // FAKE: keeps list in memory
    switch (hud->unk12) {
        case 0:
            ph = ((u8 *)tab)[0x2FC] * 0x34 - 0x34;
            s2 = D_807FCC4B;
            y0 = 0x140;
            y0 = 0xA0 - (s16)((f32)y0 * hud->unk0);
            for (j = 0; j < ((u8 *)tab)[0x2FC]; j++) {
                s32 off;
                f32 fa;
                f32 fc;
                f32 fd;
                f32 fe;
                f32 fh;
                s16 y;
                fb = (f32)(u32)ph;
                off = (j << 10) + gFrameCounter * 200;
                ang = off;
                fa = mathSinF(ang) * 0.3f + 3.0f;
                fc = mathSinF(off + 0x800) * 0.3f + 3.0f;
                fd = mathSinF((off >> 1) + 0x200) * 10.0f;
                fe = mathSinF(ang);
                fa = fa * 0.75f;
                fd = fd * 0.75f;
                fc = fc * 0.75f;
                fe = (fe * 0.5f + 0.5f) * 30.0f * 0.75f;
                gDPPipeSync(dl++);
                gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0x50);
                y = (s32)((f32)(j * 0x69 + 0x280) + fd - fb);
                fh = -fc;
                dl = renderRotatedSprite(dl, 0x5D, 0, 2, 0x30, 0x2A, y, y0 + (s16)(s32)fe, fa, fh, 0, 0.0f);
                gDPPipeSync(dl++);
                (dl++)->words.w1 = 0xFFFFFFFF; // FAKE: raw SetPrimColor words, w1 first through dl[-1], steer the store order (gDPSetPrimColor mismatches)
                dl[-1].words.w0 = 0xFA000000;
                if (s2 > 0) {
                    s32 m;
                    off = s2 - 1;
                    if (off < 3) {
                        m = off;
                    } else {
                        m = 3;
                    }
                    dl = renderRotatedSprite(dl, (u16)(m + 0x5A), 0, 2, 0x30, 0x2A, y, (s32)((f32)y0 + fe), fa, fh, 0, 0.0f);
                }
                if (s2 - 4 < 0) {
                    s2 = 0;
                } else {
                    s2 = s2 - 4;
                }
            }
            gDPPipeSync(dl++);
            y = 0x198;
            ang = (s32)((1.0f - hud->unk0) * 255.0f);
            if (ang < 0) {
                ang = 0;
            }
            if (ang >= 0x100) {
                ang = 0xFF;
            }
            if (hud->unk17 != 3) {
                for (j = 0; j < 3; j++) {
                    if (j == hud->unk17) {
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang);
                    } else {
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang >> 1);
                    }
                    if (j == 2 && (hubWorld == 7 || (hubWorld == 8 && menuGetTimerFlag() != 0 && *(s8 *)D_807505CC == 0))) {
                        j++;
                    }
                    i = j;
                    if (j == 1 && *(s8 *)D_807505CC != 0) {
                        i = 4;
                    }
                    if (i == 2 && *(s8 *)D_807505CC != 0) {
                        i = 5;
                    }
                    dl = hudDrawScaledText(dl, 0x280, y, 0.7f, D_807FC7E0[i]);
                    y += 0x44;
                }
            } else {
                gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang);
                dl = hudDrawScaledText(dl, 0x280, 0x198, 0.7f, D_807FC7E0[7]);
                _sprintf(buf, "q %s", D_807FC7E0[16]);
                dl = hudDrawScaledText(dl, 0x280, 0x1E8, 1.0, buf);
                _sprintf(buf, "b %s", D_807FC7E0[17]);
                dl = hudDrawScaledText(dl, 0x280, 0x238, 1.0, buf);
            }
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                s32 angv;
                actor = (Actor *)(hud->unkC[i] * 4); // FAKE: reuse the consumed parameter to remove off1's stack home.
                angv = -hud->unk10;
                fa = 1.0f - hud->unk0;
                if ((s32)actor < 0x3B6 && (s32)actor >= -0x3B5) {
                    if (fa > 0.05f) {
                        f32 fc;
                        f32 fe;
                        f32 ff;
                        s16 sa;
                        s16 yy;
                        t0 = i * 5;
                        fb = 180.0f * fa;
                        fa = fa * 3.0f;
                        fc = 32.0f * fa;
                        fc = 480.0f + fc;
                        fd = 6.0f * fa;
                        fe = 30.0f * fa;
                        ff = (f32)((f64)fa * 1.33);
                        for (j = 0; j < 5; j++) {
                            sa = angv;
                            yy = (s32)(mathSinF(sa) * fb);
                            yy += 0x280;
                            y0 = (s32)(mathCosF(sa) * fb);
                            yy += 0x20;
                            off = j + t0;
                            D_807FC840[off] = (f32)yy - fd;
                            D_807FC868[off] = (f32)(s16)((s16)(fc - (f32)y0) + (s32)actor) - fe; // FAKE: narrow before the row offset to steer conversion temporaries.
                            D_807FC890[off] = ff;
                            if (D_80750530[j] != 0) {
                                D_807FC890[off] = (f32)((f64)D_807FC890[off] * 0.75);
                            }
                            angv += 0x333;
                        }
                        gDPPipeSync(dl++);
                    }
                    dl = hudDrawItemLabel(dl, hud, i);
                }
                if (hud->unk8[i] != 8) {
                    f32 fc;
                    fd = (hud->unk4 < hud->unk0) ? hud->unk0 : hud->unk4;
                    fc = 780.0f;
                    if ((s32)actor == 0) {
                        fc = fc + fd * 400.0;
                    }
                    j = gPlayerInventoryTable[hud->unk14].unk42[D_80750560[hud->unk8[i]]];
                    dl = hudDrawCountPair(0x2A8, (s32)((f32)(s32)actor + fc), j, 5, dl, 0, 0.8f);
                }
            }
            D_80750538++;
            if (D_80750538 >= 0xE) {
                D_80750538 = 0;
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                off = hud->unkC[i] * 4;
                if (off < 0x3B6 && off >= -0x3B5) {
                    dl = hudDrawItemLabel(dl, hud, i);
                }
                cnt = 0;
                for (j = 0; j < 5; j++) {
                    cnt += gPlayerInventoryTable[j].unk42[D_80750560[hud->unk8[i]]];
                }
                if (hud->unk8[i] != 8) {
                    fadeInput4 = hud->unk4;
                    fadeInput0 = hud->unk0;
                    if (fadeInput4 < fadeInput0) {
                        fd = fadeInput0;
                    } else {
                        fd = fadeInput4;
                    }
                    fc = 780.0f;
                    if (off == 0) {
                        fc = fc + fd * 400.0;
                    }
                    dl = hudDrawCountPair(0x2B0, (s32)((f32)off + fc), cnt, 0x19, dl, 0, 0.8f);
                }
            }
            break;
        case 3:
            dl = hudDrawScaledText(hudDrawScaledText(dl, 0x280, 0x74, 0.5f, D_807FC7E0[D_807FC818[D_807FC80C] + 18]), 0x280, 0x3C, 0.65, D_807FC7E0[6]);
            {
                f32 fb;
                fadeInput4 = hud->unk4;
                fadeInput0 = hud->unk0;
                if (fadeInput4 < fadeInput0) {
                    fc = fadeInput0;
                } else {
                    fc = fadeInput4;
                }
                fb = (1.0f - fc) * 0.65f;
                if (fb < 0.01f) {
                    fb = 0.01f;
                }
                dl = hudDrawCountPair(0x280, 0x33C, (&D_807FC828)[D_807FC818[D_807FC80C]], D_8075056C[D_807FC818[D_807FC80C]], dl, 1, fb);
            }
            break;
    }
    dl->words.w0 = 0xDF000000; // FAKE: raw EndDisplayList words (gSPEndDisplayList mismatches)
    dl->words.w1 = 0;
    if (D_80750530 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    return ret;
}

Gfx *hudDrawCountPair(s16 x, s16 y, s16 n1, s16 n2, Gfx *dl, s8 flag, f32 scale) {
    Mtx *mtx;
    s32 w;
    f32 m1[4][4];
    f32 m2[4][4];
    u8 buf1[8];
    u8 buf2[8];

    mtx = heapAlloc(0x40);
    heapFreeDeferred(mtx);
    if (n1 >= 0x64) {
        w = 0x7C;
    } else if (n1 >= 10) {
        w = 0x5C;
    } else {
        w = 0x3C;
    }
    if (flag != 0) {
        x = (f32)x - (f32)w * scale;
    }
    guScaleF(m1, scale, scale, 1.0f);
    guTranslateF(m2, x, y, 0.0f);
    guMtxCatF(m1, m2, m1);
    guMtxF2L(m1, mtx);
    gSPMatrix(dl++, mtx, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    _sprintf(buf1, "%d", n1);
    _sprintf(buf2, "%d", n2);
    dl = textDrawStringVtx(textDrawStringVtx(dl, 1, 0, -0x28, buf1, 0x80), 1, w, 0x28, buf2, 0);
    gSPPopMatrix(dl++, G_MTX_MODELVIEW);
    dl->words.w0 = 0xE7000000; // FAKE: raw PipeSync words with a separate dl++ (gDPPipeSync(dl++) mismatches)
    dl->words.w1 = 0;
    dl++;
    return renderRotatedSprite(dl, 0x9F, 0, 2, 0x20, 0x20, (s32)((f32)x + (f32)(w - 0x10) * scale), (s32)((f32)y + 45.0f * scale), scale * 3.125, scale * 3.125, 0, 0.0f);
}

typedef struct {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA[14];
    /* 0x26 */ u16 unk26[14];
    /* 0x42 */ u16 unk42[14];
} HudPauseCountEntry;

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[2];
} HudPauseFlagEntry;

extern u8 gPlayerCharacterId;
#define HUD_PAUSE_COUNT(i) ((HudPauseCountEntry *)((u8 *)gPlayerInventoryTable + (i) * 0x5E))
extern HudPauseFlagEntry D_80755DA8[];
extern s8 D_807FC800;
extern f32 D_807FC804;
extern s8 D_807FC80D;
extern s8 D_807FC818[];
extern s16 D_807FC83A;
extern s8 D_807FC83C;
extern u16 D_807FCC40;
extern u16 D_807FCC44;
extern u16 D_807FCC46;
extern u16 D_807FCC48;
extern void *D_80750518[];
extern s16 D_807505A4[];
extern s16 D_807505CA;
extern void *D_807505D8[];
extern s32 D_80720C34;
extern s32 D_80720D38;
extern s32 D_80720D5C;
extern s32 D_80720D80;
extern s32 D_8072104C;
extern s32 D_80721094;
extern s32 D_807210EC;
extern s32 D_807211D0;
extern s32 D_80721474;
extern s32 D_80721518;


void hudPauseMenuBuildPage(HudEntry *iconObj, s32 refresh) {
    s32 saved;
    HudPauseCountEntry *e2;
    HudPauseCountEntry *ent;
    s32 i;
    s32 idx;
    s8 *fp;
    s32 sum;
    f32 f;
    s32 sum3;
    s8 cnt8;
    s16 xs;
    s8 found[4];
    s32 flag;
    void *s;
    s32 j;
    HudPauseFlagEntry *q;
    s32 x;
    s32 cnt;
    HudEntry *hud;

    hud = iconObj; // FAKE: redundant copy of the parameter steers regalloc (iconObj-> everywhere mismatches)
    saved = gPlayerCharacterId;
    e2 = HUD_PAUSE_COUNT(playerGetResolvedKongId(0));
    gPlayerCharacterId = hud->unk14;
    ent = HUD_PAUSE_COUNT(hud->unk14);
    idx = hud->unk8[hud->unk15];
    D_807FC7F8[hud->unk15] = 0;
    idx = D_80750560[idx];
    if (refresh == 0) {
        D_807FC800 = hud->unk14;
        D_807FC80D = D_807FC80C;
        hud->unk10 = 0;
        hud->unk4 = 0.0f;
        D_807FC804 = 0.0f;
    }
    D_807FC80F = 1;
    switch (hud->unk12) {
    case 0:
        gPlayerCharacterId = saved;
        idx = mapGetHubWorldIndex(gCurrentWorldId, 1);
        if (idx >= 9) {
            idx = 7;
        }
        if (idx != 7 && flagGet(0x18B, 0)) {
            hudPauseMenuAddCounter(iconObj, 0x1E, 0x1E, 0xC, -0xA, e2->unkA[idx], 1, 0);
            hudPauseMenuSpawnIcon(iconObj, 0, 0x1E, 0x1E, 0.75f, 2, 1);
        }
        if (flagGet(0x184, 0)) {
            hudPauseMenuAddCounter(iconObj, 0x1E, 0x5A, 0xC, -0xA, D_807FCC44, 1, 1);
            hudPauseMenuSpawnIcon(iconObj, 4, 0x1E, 0x5A, 0.75f, 2, 1);
        }
        if (e2->unk2 != 0) {
            hudPauseMenuAddCounter(iconObj, 0x1E, 0x7D, 0xC, -0xA, D_807FCC40, 1, 1);
            hudPauseMenuSpawnIcon(iconObj, 2, 0x1E, 0x7D, 0.65f, 2, 1);
        }
        if (func_806F6E58(gPlayerCharacterId)) {
            f = slotQueueGetCountStep(5);
            hudPauseMenuAddCounter(iconObj, 0x1E, 0xA0, 0xC, -0xA, (s32)floatCeil((f32)(u32)D_807FCC46 / f), 1, 1);
            hudPauseMenuSpawnIcon(iconObj, 5, 0x1E, 0xA0, 0.65f, 2, 1);
        }
        if (flagGet(0x18C, 0)) {
            hudPauseMenuAddCounter(iconObj, 0x122, 0x5A, -0xF, -0xA, e2->unk6, 1, 0x80);
            hudPauseMenuSpawnIcon(iconObj, 1, 0x122, 0x5A, 0.75f, 2, 1);
        }
        if (ent->unk4 & 1) {
            hudPauseMenuAddCounter(iconObj, 0x122, 0x7D, -0xC, -0xA, ent->unk8, 2, 0x81);
            hudPauseMenuSpawnIcon(iconObj, 7, 0x122, 0x7D, 0.75f, 2, 7);
        }
        if (flagGet(0x179, 0)) {
            hudPauseMenuAddCounter(iconObj, 0x122, 0xA0, -0xC, -0xA, D_807FCC48, 1, 0x81);
            hudPauseMenuSpawnIcon(iconObj, 6, 0x122, 0xA0, 0.65f, 2, 1);
        }
        if (D_807FC828 > 0) {
            hudPauseMenuAddCounter(iconObj, 0x91, 0xBE, 0xF, -0xA, D_807FC828, 1, 0);
            hudPauseMenuSpawnIcon(iconObj, 9, 0x91, 0xBE, 1.0f, 2, 1);
        }
        gPlayerCharacterId = hud->unk14;
        break;
    case 1:
        if (idx != 7) {
            i = idx;
            if (idx != 8) {
                hudPauseMenuAddCounter(iconObj, 0x1E, 0x2A, 0xC, -0xA, ent->unkA[idx] + ent->unk26[idx], 2, 0);
                hudPauseMenuSpawnIcon(iconObj, 0, 0x1E, 0x2A, 0.75f, 2, 2);
            } else {
                i = 7;
            }
            if (D_807FC82E > 0) {
                if (idx != 8) {
                    D_807FC80F = (HUD_PAUSE_COUNT(gPlayerCharacterId)->unkA[idx] + HUD_PAUSE_COUNT(gPlayerCharacterId)->unk26[idx]) >= 0x4B;
                } else {
                    D_807FC80F = flagGridSumRows(0x225, i, i, gPlayerCharacterId);
                }
                hudPauseMenuSpawnIcon(iconObj, 0xA, 0x113, 0x7D, 0.75f, 2, 2);
                if (flagGridSumRows(0x225, i, i, gPlayerCharacterId)) {
                    hudPauseMenuSpawnIcon(iconObj, (s32)&D_80721518, 0x113, 0x7D, 0.35f, 2, 0xD);
                }
            }
        }
        if (refresh == 0) {
            for (i = 0; i < 5; i++) {
                if (D_80750530[i]) {
                    s = D_80750518[i];
                } else {
                    s = &D_807211D0;
                }
                hudPauseMenuSpawnIcon(iconObj, (s32)s, i, i, 0.75f, 2, 0xA);
                hudPauseMenuSpawnIcon(iconObj, (s32)s, i + 5, i + 5, 0.75f, 2, 0xA);
            }
        }
        if (idx != 8) {
            hudPauseMenuSpawnIcon(iconObj, 9, 0x91, 0xCB, 1.0f, 2, 2);
            sum = 0;
            for (i = 0; i < 5; i++) {
                if (flagGridSumRows(0x1D5, 0, 7, i)) {
                    sum = 1;
                }
            }
            if (sum) {
                D_807FC80F = flagGet(flagGridIndex(0x1D5, idx, gPlayerCharacterId), 0);
                i = 0;
                hudPauseMenuSpawnIcon(iconObj, 0xC, 0x26, 0x7D, 0.75f, 2, 2);
                if (flagGet(flagGridIndex(0x1FD, idx, gPlayerCharacterId), 0)) {
                    hudPauseMenuSpawnIcon(iconObj, (s32)&D_80721518, 0x26, 0x7D, 0.35f, 2, 0xD);
                }
            }
        }
        if (refresh == 0) {
            hud->unk10 = D_807505A4[hud->unk14];
            hudPauseMenuSpawnIcon(iconObj, (s32)&D_80720C34, 0xA0, 0x78, 0.75f, 2, 0);
            if (D_807505D0 > 0) {
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_80720D80, 0xA0, 0x19, 0.5f, 2, 0xB);
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_80720D5C, 0xA0, 0x19, 0.5f, 2, 0xC);
            }
        }
        break;
    case 2:
        sum = 0;
        sum3 = 0;
        for (i = 0; i < 5; i++) {
            sum += HUD_PAUSE_COUNT(i)->unkA[idx] + HUD_PAUSE_COUNT(i)->unk26[idx];
            sum3 += HUD_PAUSE_COUNT(i)->unk42[idx];
        }
        cnt8 = 0;
        for (i = 0; i < 4; i++) {
            found[i] = 0;
        }
        for (i = 0; D_80755DA8[i].unk0 != 0xFF; i++) {
            j = mapGetHubWorldIndex(D_80755DA8[i].unk0, 1);
            if (idx == j) {
                xs = D_80755DA8[i].unk4;
                if (xs >= 0x24D && xs < 0x261 && cnt8 < 4) {
                    found[cnt8++] = flagGet(xs, 0);
                }
            }
        }
        if (idx != 7) {
            j = idx;
            if (idx != 8) {
                hudPauseMenuAddCounter(iconObj, 0x24, 0x2A, 0xC, -0xA, sum, 1, 0);
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_80721474, 0x24, 0x2A, 0.75f, 2, 1);
            } else {
                j = 7;
            }
            i = 0;
            do {
                if (idx != 8) {
                    D_807FC80F = (HUD_PAUSE_COUNT(i)->unkA[idx] + HUD_PAUSE_COUNT(i)->unk26[idx]) >= 0x4B;
                } else {
                    D_807FC80F = flagGridSumRows(0x225, j, j, i);
                }
                hudPauseMenuSpawnIcon(iconObj, 0xA, D_807505A4[i], 0, 0.75f, 2, 3);
                if (flagGridSumRows(0x225, j, j, i)) {
                    hudPauseMenuSpawnIcon(iconObj, (s32)&D_80721518, D_807505A4[i], 0, 0.35f, 2, 0xE);
                }
                i++;
            } while (i != 5);
            if (D_807FC82A > 0) {
                D_807FC80F = flagGet(D_807505B8[idx], 0);
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_807210EC, 0xA0, 0x78, 1.0f, 2, 4);
            }
            if (flagGet(0x179, 0)) {
                D_807FC80F = found[0];
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_80721094, 0x3C, 0x78, 1.0f, 2, 6);
                D_807FC80F = found[1];
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_80721094, 0x104, 0x78, 1.0f, 2, 6);
            }
        } else {
            if (D_807FC82A > 0) {
                D_807FC80F = flagGet(D_807505B8[idx], 0);
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_807210EC, 0xA0, 0x55, 1.0f, 2, 4);
                D_807FC80F = flagGet(D_807505CA, 0);
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_807210EC, 0xA0, 0x91, 1.0f, 2, 4);
            }
            if (flagGet(0x179, 0)) {
                D_807FC80F = found[0];
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_80721094, 0x3C, 0x5A, 1.0f, 2, 6);
                D_807FC80F = found[1];
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_80721094, 0x46, 0x96, 1.0f, 2, 6);
                D_807FC80F = found[2];
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_80721094, 0x104, 0x5A, 1.0f, 2, 6);
                D_807FC80F = found[3];
                hudPauseMenuSpawnIcon(iconObj, (s32)&D_80721094, 0xFA, 0x96, 1.0f, 2, 6);
            }
        }
        if (idx != 8) {
            hudPauseMenuSpawnIcon(iconObj, 9, 0x91, 0xCB, 1.0f, 2, 2);
        }
        if (refresh == 0 && D_807505D0 > 0) {
            hudPauseMenuSpawnIcon(iconObj, (s32)&D_80720D80, 0xA0, 0x19, 0.5f, 2, 0xB);
            hudPauseMenuSpawnIcon(iconObj, (s32)&D_80720D5C, 0xA0, 0x19, 0.5f, 2, 0xC);
        }
        break;
    case 3:
        D_807FC83C = 0;
        for (i = 0; i < 8; i++) {
            if ((&D_807FC828)[i] > 0) {
                D_807FC83C++;
            }
        }
        D_807FC83A = 0x1000 / D_807FC83C;
        x = 0;
        cnt = 0;
        for (i = 0; i < 8; i++) {
            if ((&D_807FC828)[i] > 0) {
                if (i != 5) {
                    f = 0.75f;
                    flag = 5;
                } else {
                    f = 1.0f;
                    flag = 8;
                }
                hudPauseMenuSpawnIcon(iconObj, (s32)D_807505D8[i], x, 0, f, 2, flag);
                x += D_807FC83A;
                D_807FC818[cnt] = i;
                cnt++;
            }
        }
        hud->unk10 = D_807FC83A * D_807FC80C;
        hudPauseMenuSpawnIcon(iconObj, (s32)&D_80720C34, 0xA0, 0x78, 0.75f, 2, 0);
        break;
    }
    if (refresh == 0 && D_807FC828 > 0) {
        hudPauseMenuSpawnIcon(iconObj, (s32)&D_80720D38, 0x2D, 0xC8, 1.0f, 2, 1);
        hudPauseMenuSpawnIcon(iconObj, (s32)&D_8072104C, 0x113, 0xC8, 1.0f, 2, 1);
    }
    gPlayerCharacterId = saved;
}

void hudPauseMenuSpawnIcon(HudEntry *iconObj, s32 sprite, s32 x, s32 y, f32 scale, u8 mode, s32 kind) {
    HudTextObj *obj;
    f32 *buf;
    f32 dx;
    f32 dy;
    f32 len;
    f32 fy;

    effectSetMode(mode);
    effectEnableFade();
    effectSetDuration(-1);
    effectSetSpeed((s32)iconObj);
    effectSetCallback(hudPauseMenuIconUpdate);
    effectSetFlags(0x101);
    if (sprite < 0) {
        fy = x;
        obj = effectCreateAtPosition((void *)sprite, scale, fy, (f32)y, -10.0f);
    } else {
        fy = x;
        obj = effectCreateAtPosition(slotQueueGetSpriteAsset(sprite), scale, fy, (f32)y, -10.0f);
    }
    sprite = 7;
    if (kind == 6) {
        sprite = 10;
    }
    buf = heapAlloc(sprite * 4);
    obj->unk384 = buf;
    if (kind == 9) {
        kind = 7;
        obj->unk360 = -obj->unk360;
    }
    buf[0] = kind;
    buf[1] = iconObj->unk15;
    buf[2] = obj->unk340;
    buf[3] = obj->unk344;
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
        buf[6] = obj->unk364;
        if (kind == 13) {
            buf[0] = 2.0f;
            obj->unk36C = 0;
            obj->unk36B = 0;
            obj->unk36A = 0xFF;
        }
        break;
    case 6:
        buf[4] = 0.0f;
        buf[5] = 0.0f;
        buf[6] = 0.0f;
        buf[7] = 0.0f;
        buf[8] = randomFloat() * 4096.0f;
        if (x < 0xA0) {
            obj->unk360 = -obj->unk360;
        }
        buf[9] = 0.0f;
        break;
    case 10:
        buf[2] = fy;
        break;
    case 14:
        buf[0] = 3.0f;
        obj->unk36C = 0;
        obj->unk36B = 0;
        obj->unk36A = 0xFF;
    default:
        buf[4] = scale;
        buf[5] = 0.0f;
        break;
    }
    if (D_807FC80F == 0) {
        obj->unk36A = 0x64;
        obj->unk36B = 0x64;
        obj->unk36C = 0x64;
    }
    D_807FC80F = 1;
}

void hudPauseMenuAddCounter(HudEntry *iconObj, s16 x, s16 y, s16 dx, s16 dy, s32 value, s32 style, s32 format) {
    s32 pad;
    s32 idx;
    s32 pad2;
    s32 pad3;
    s32 i;
    f32 len;
    s32 pad4;
    HudTextEntry *list;
    s8 flag;
    u8 buf[11];

    flag = 0;
    if (format & 0x80) {
        flag = 1;
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
    if (flag != 0) {
        dx -= textGetStringWidth(1, buf);
    }
    D_807FC810 = textGetStringWidth(1, buf);
    idx = D_807FC7F8[iconObj->unk15];
    list = D_807FC7F0[iconObj->unk15];
    len = sqrtf((640.0f - (f32)(x * 4)) * (640.0f - (f32)(x * 4)) + (480.0f - (f32)(y * 4)) * (480.0f - (f32)(y * 4)));
    list[idx].unk0 = -((640.0f - (f32)(x * 4)) / len) * (1040.0f - len);
    list[idx].unk4 = -((480.0f - (f32)(y * 4)) / len) * (1040.0f - len);
    list[idx].unk8 = x;
    list[idx].unkA = y;
    list[idx].unkC = dx;
    list[idx].unkE = dy;
    list[idx].unk10 = style;
    for (i = 0; buf[i] != 0; i++) {
        list[idx].unk11[i] = buf[i];
    }
    list[idx].unk11[i] = 0;
    D_807FC7F8[iconObj->unk15]++;
}

Gfx *hudDrawItemLabel(Gfx *dl, HudEntry *entry, s32 itemIndex) {
    u8 padHi[0xC];
    s32 col;
    void *tex;
    u8 pad[0x1C];
    s32 y2;
    s32 y;

    y = entry->unkC[itemIndex] * 4;
    tex = D_807FC7E8[D_80750560[entry->unk8[itemIndex]]];
    if (entry->unk12 == 1) {
        col = entry->unk14;
    } else {
        col = 5;
    }
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    y2 = y + 0x40;
    dl = hudDrawScaledText(hudDrawScaledText(dl, 0x280, y2, 0.7f, tex), 0x280, y2 + 0x38, 0.5f, D_807FC7E0[col + 9]);
    D_807FC808 = (f32)textGetStringWidth(1, tex) * 1.4;
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
    s32 v;
    s32 d;

    if (sliding == 0) {
        d = 0;
        if (buttons & 8) {
            d = 1;
        } else if (buttons & 4) {
            d = -1;
        }
        if (d != 0) {
            idx = hud->unk15;
            v = hud->unk8[idx];
            v += d;
            if (v < 0) {
                v = D_807505D0;
            }
            if (D_807505D0 < v) {
                v = 0;
            }
            if (v != hud->unk8[idx]) {
                hud->unk15 = 1 - idx;
                hud->unk8[hud->unk15] = v;
                hud->unkC[hud->unk15] = d * 0xFA;
                hudPauseMenuBuildPage(hud, 0);
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
    }
    if (sliding != 0) {
        d = hud->unkC[hud->unk15];
        if (d >= 0x15) {
            d = 0x14;
        }
        if (d < -0x14) {
            d = -0x14;
        }
        hud->unkC[0] -= d;
        hud->unkC[1] -= d;
        if (hud->unkC[hud->unk15] == 0) {
            hud->unk8[1 - hud->unk15] = hud->unk8[hud->unk15];
            D_807FC7F8[1 - hud->unk15] = 0;
            sliding = 0;
            sfxPlayOnFreeSlot(0x97, 0x4650, 63.0f, 1.0f, 0, 0);
            D_8075052C = 3;
        }
    }
    return sliding;
}


void hudPauseMenuRefreshTotals(void) {
    s16 *p;
    s16 *p0;
    HudCountEntry *e;
    s32 n;
    s32 i;
    s32 k;
    s32 m;

    p0 = (s16 *)((u8 *)&D_807FC82A - 2); do { // LAYOUT: one-line loop setup steers as1 lui/addiu order (Q0149)
        *p0++ = 0;
    } while (p0 < (s16 *)((u8 *)&D_807FC82A + 12));
    n = 0;
    k = 0; e = gPlayerInventoryTable; do { n += gPlayerInventoryTable[k].unk42[0]; n += gPlayerInventoryTable[k].unk42[1]; // LAYOUT: one-line loop setup (Q0149)
        for (i = 2; i < 14; i++) { // FAKE: first two terms re-read through gPlayerInventoryTable[k] instead of e, loop from 2
            n += e->unk42[i];
        }
        e++;
        k++;
    } while (&gPlayerInventoryTable[k] < D_807FCB26);
    D_807FC828 = n;
    n = 0;
    p = D_80744710; do { // LAYOUT: one-line loop setup steers as1 lui/addiu order (Q0149)
        if (flagGet(*p, 0) != 0) {
            n++;
        }
        p++;
    } while (p < D_80744720);
    D_807FC82C = n;
    D_807FC832 = flagCountRange(0x24D, 0x14, 0);
    D_807FC82E = flagCountRange(0x225, 0x28, 0);
    m = 0;
    p = D_807505B8; do { // LAYOUT: one-line loop setup steers as1 lui/addiu order (Q0149)
        if (*p >= 0 && flagGet(*p, 0) != 0) {
            m++;
        }
        p++;
    } while (p < D_807505CC);
    D_807FC82A = m;
    D_807FC834 = flagGet(0x84, 0);
    D_807FC830 = flagGet(0x17B, 0);
    D_807FC836 = flagCountRange(0x1FD, 0x28, 0);
    D_80750530[0] = 1;
    for (i = 0; i < 4; i++) {
        D_80750531[i] = flagGet(D_807505B2[i - 1], 0);
    }
    D_807FC838 = 1;
}

Gfx *hudDrawDimOverlay(Gfx *dl, Actor *actor) {
    return gfxFillScreenColor(dl, 0, 0, 0, 0x46);
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
} HudIconState;

typedef struct {
    f32 unk0;
    f32 unk4;
    u8 pad8[4];
    s16 tbl[4];
    u8 pad14;
    s8 unk15;
} HudIconSource;

typedef struct HudIconObj {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    u8 pad348[0x35C - 0x348];
    HudIconSource *unk35C;
    f32 unk360;
    f32 unk364;
    u8 pad368[2];
    u8 unk36A;
    u8 unk36B;
    u8 unk36C;
    u8 unk36D;
    u8 pad36E[0x384 - 0x36E];
    HudIconState *unk384;
} HudIconObj;

f32 mathCosF(s16);
f32 mathSinF(s16);
extern f32 D_807FC840[];
extern f32 D_807FC868[];
extern f32 D_807FC890[];
extern u8 D_8075054C[][4];
extern s32 gFrameCounter;

void hudPauseMenuIconUpdate(HudIconObj *iconObj, s8 *done) {
    HudIconSource *src;
    HudIconState *item;
    f32 t;
    f32 sc;
    s32 type;
    s32 bounceStep;
    s32 ang;
    s32 i;
    s16 five;

    src = iconObj->unk35C;
    if (iconObj->unk384 != NULL) {
        t = src->unk0;
        item = iconObj->unk384;
        bounceStep = (f64)src->tbl[(s32)item->unk4] * 4.0;
        type = (s32)item->unk0;
        switch (type) {
        case 0:
        case 4:
        case 11:
        case 12:
            t = 1.0 - src->unk0;
            if (t < 0.0f) {
                t = 0.0f;
            }
            if (t > 1.0f) {
                t = 1.0f;
            }
            iconObj->unk36D = (s32)(t * 255.0f);
            if (type == 4) {
                iconObj->unk360 = (f64)(item->unk10 * t) * 4.0;
                iconObj->unk364 = iconObj->unk360;
            }
            iconObj->unk340 = item->unk8;
            iconObj->unk344 = item->unkC + (f32)bounceStep;
            if (type == 0xB) {
                iconObj->unk340 = 600.0 - D_807FC808;
            }
            if (type == 0xC) {
                iconObj->unk340 = D_807FC808 + 680.0;
            }
            t = 0.0f;
            break;
        case 1:
        case 2:
        case 7:
            if (type != 1) {
                t += src->unk4;
            }
            if (type == 7) {
                ang = (gFrameCounter * 0x78) & 0xFFF;
                iconObj->unk364 = (f64)mathSinF(ang) * 0.35 + item->unk18;
            }
            iconObj->unk340 = item->unk10 * t + item->unk8;
            iconObj->unk344 = item->unk14 * t + item->unkC + (f32)bounceStep;
            break;
        case 3:
        case 5:
        case 8:
        case 15:
            t = 1.0 - src->unk0;
            if (t < 0.0f) {
                t = 0.0f;
            }
            if (t > 1.0f) {
                t = 1.0f;
            }
            ang = (s32)((f64)item->unk8 * 0.25) - src->tbl[2];
            sc = 180.0f;
            if (type != 3) {
                sc = 240.0f;
            }
            sc = sc * t;
            iconObj->unk360 = (f64)(item->unk10 * t) * 4.0;
            iconObj->unk364 = iconObj->unk360;
            t = 0.0;
            iconObj->unk340 = (f64)(mathSinF(ang) * sc) + 640.0;
            iconObj->unk344 = (480.0 - (f64)(mathCosF(ang) * sc)) + (f64)bounceStep;
            if (type == 8) {
                ang = (gFrameCounter * 0x78) & 0xFFF;
                sc = mathSinF(ang);
                iconObj->unk344 = iconObj->unk344 + sc * 10.0f;
            }
            if (type == 0xF) {
                ang = (gFrameCounter * 0x78) & 0xFFF;
                sc = mathSinF(ang);
                iconObj->unk364 = iconObj->unk364 * (1.0 + (f64)sc * 0.2);
            }
            if (type == 5 || type == 8 || type == 0xF) {
                i = 0xFF - (s32)(((f64)iconObj->unk344 - 240.0) * 1.5);
                if (i < 0x5F) {
                    i = 0x5F;
                }
                if (i >= 0x100) {
                    i = 0xFF;
                }
                iconObj->unk36A = i;
                iconObj->unk36B = i;
                iconObj->unk36C = i;
            }
            break;
        case 6:
            sc = (item->unk14 - item->unk1C) * (item->unk14 - item->unk1C) + (item->unk10 - item->unk18) * (item->unk10 - item->unk18);
            if (sc < 400.0f) {
                item->unk24 = (f64)item->unk24 - 1.0;
                if ((f64)item->unk24 < 0.0) {
                    sc = randomFloat();
                    item->unk20 = (f64)item->unk20 + (1000.0 + (f64)sc * 2000.0);
                    ang = (s32)item->unk20 & 0xFFF;
                    item->unk20 = ang;
                    sc = ((f64)randomFloat() * 40.0 + 20.0) * 4.0;
                    item->unk18 = (f64)mathSinF(ang) * ((f64)sc * 0.8);
                    item->unk1C = mathCosF(ang) * sc;
                    if ((f64)randomFloat() < 0.25) {
                        item->unk24 = (f64)randomFloat() * 40.0 + 15.0;
                    } else {
                        item->unk24 = 0;
                    }
                }
            }
            sc = (f64)(item->unk18 - item->unk10) * 0.1;
            if (sc < -8.0) sc = -8.0f; // LAYOUT: one-line if steers as1 scheduling of the hoisted item->unk14 load
            if (sc > 8.0) {
                sc = 8.0f;
            }
            item->unk10 = item->unk10 + sc;
            sc = (f64)(item->unk1C - item->unk14) * 0.1;
            if (sc < -8.0) {
                sc = -8.0f;
            }
            if (sc > 8.0) {
                sc = 8.0f;
            }
            item->unk14 = item->unk14 + sc;
            ang = (gFrameCounter * 0x78) & 0xFFF;
            iconObj->unk340 = item->unk10 + item->unk8;
            sc = mathSinF(ang);
            iconObj->unk344 = sc * 10.0f + (item->unkC + item->unk14 + (f32)bounceStep + 960.0f * t);
            t = 0.0f;
            break;
        case 10:
            i = (s32)item->unk8;
            iconObj->unk340 = D_807FC840[i];
            iconObj->unk344 = D_807FC868[i];
            iconObj->unk360 = D_807FC890[i];
            iconObj->unk364 = D_807FC890[i];
            D_807FC840[i] = -200.0f;
            D_807FC868[i] = -200.0f;
            five = 5; // FAKE: value-named constant local steers the compare/subtract operands
            if (i >= five) {
                i -= five;
            }
            if (D_80750530[i] == 0) {
                iconObj->unk36A = D_8075054C[i][0];
                iconObj->unk36B = D_8075054C[i][1];
                iconObj->unk36C = D_8075054C[i][2];
            }
            break;
        }
        if ((s32)item->unk4 != src->unk15 && (bounceStep < -0x3C0 || bounceStep >= 0x3C1)) {
            *done = 1;
        }
        if (t > 1.0f || src->unk0 > 1.0f) {
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
    dl = textDrawStringVtx(dl, 1, 0x168, 0x104, D_807FC7E0[0], 1);
    _sprintf(buf, "q %s", D_807FC7E0[1]);
    dl = textDrawStringVtx(dl, 1, 0x208, 0x190, buf, 1);
    _sprintf(buf, "b %s", D_807FC7E0[2]);
    return textDrawStringVtx(dl, 1, 0x208, 0x21C, buf, 1);
}

void hudSpawnTextScreen(u8 textId) {
    actorSpawn(0x156, 0);
    gSpawnedActor->unk15F = textId;
    gSpawnedActor->renderFlags |= 2;
    gGlobalPauseFlags |= 0x40001;
}

void hudFreeTextAndDespawn(void) {
    s16 i;

    gGlobalPauseFlags |= 0x40;
    for (i = 0; i < 3; i++) {
        heapFreeDeferred(D_807FC7E0[i]);
    }
    heapFreeDeferred(D_807FC7E0);
    actorDespawn(gCurrentActor);
}

void hudTextScreenUpdate(void) {
    s32 i;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->yawSpeed = 0x1E;
        gCurrentActor->alpha = 0;
        gCurrentActor->flags &= ~0x8000;
        D_807FC7E0 = heapAlloc(0xC);
        for (i = 0; i < 3; i++) {
            D_807FC7E0[i] = textTableGetString(0x24, i + 0xF, 0);
        }
    }
    if (gCurrentActor->yawSpeed != 0) {
        gCurrentActor->yawSpeed--;
    } else if (gCurrentActor->state == 0) {
        if (D_807ECD58 & 0x8000) {
            switch (gCurrentActor->unk15F) {
                case 2:
                    camStartPath(0, 0x20, 1);
                    hudFreeTextAndDespawn();
                    break;
                case 3:
                case 4:
                    func_80724994(3, 7, 0x30, 0, 0);
                    hudFreeTextAndDespawn();
                    break;
                default:
                    mapRequestTransition(gCurrentMap, 0);
                    break;
            }
            gCurrentActor->state = 1;
        } else if (D_807ECD58 & 0x4000) {
            switch (gCurrentActor->unk15F) {
                case 3:
                case 4:
                    func_80724994(3, 7, 0x3C, 0, 0);
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
    u8 sel;
    u8 c;

    dl = hudSetupTextState(dl);
    sel = actor->unk155 == 0;
    c = D_807505F8[sel];
    gDPSetPrimColor(dl++, 0, 0, c, c, c, 255);
    dl = hudDrawScaledText(dl, 0x280, 0x1B8, 0.7f, D_807FC7E0[0]);
    c = D_807505F8[1 - sel];
    gDPSetPrimColor(dl++, 0, 0, c, c, c, 255);
    return hudDrawScaledText(dl, 0x280, 0x208, 0.7f, D_807FC7E0[3]);
}

void hudTwoOptionMenuUpdate(void) {
    s32 i;
    u16 btn;

    if (!(gCurrentActor->flags & 0x10)) {
        D_807FC7E0 = heapAlloc(0x10);
        i = 0;
        do {
            D_807FC7E0[i] = textTableGetString(0x24, i, 0);
            i++;
        } while (i != 4);
        gGlobalPauseFlags &= ~0x10030;
        screenWipeStart(7);
        D_807FC80E = 0;
        gCurrentActor->unk155 = 0;
    }
    i = gPausingPlayer;
    if (gPlayerSlots[i].contPad->stick_y >= 0x33 || gPlayerSlots[i].contPad->stick_y < -0x32) {
        if (!(D_807FC80E & 1)) {
            gCurrentActor->unk155 = 1 - gCurrentActor->unk155;
            D_807FC80E |= 1;
            sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
    } else {
        D_807FC80E &= 0xFFFE;
    }
    btn = *gPlayerSlots[i].heldButtonsPtr;
    if (btn & 0x8000) {
        if (gCurrentActor->unk155 == 0) {
            gGlobalPauseFlags |= 0x10070;
            for (i = 0; i < 4; i++) {
                heapFreeDeferred(D_807FC7E0[i]);
            }
            heapFreeDeferred(D_807FC7E0);
        } else if (gCurrentActor->unk155 == 1) {
            D_8076A105 = -1;
            menuReturnToTitleWithMode3();
            gCurrentActor->unk155 = 2;
        }
    }
    renderCallbacksRegister(hudDrawDimOverlay, gCurrentActor, 1);
    renderCallbacksRegister(hudDrawTwoOptionMenu, gCurrentActor, 5);
}
