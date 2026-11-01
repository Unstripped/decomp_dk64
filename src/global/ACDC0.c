#include "common.h"
#include "actor.h"

typedef struct HudTextEntry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ char unk11[7];
} HudTextEntry; // size = 0x18

typedef struct HudEntry {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s16 unk8[2];
    /* 0x0C */ s16 unkC[2];
    /* 0x10 */ u8 pad10[2];
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 pad13;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
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

typedef struct HudAxis {
    u8 pad0[3];
    s8 unk3;
} HudAxis;

typedef struct HudPlayerView {
    u8 pad0[0x294];
    HudAxis *unk294;
    u16 *unk298;
    u8 pad29C[0x2F0 - 0x29C];
} HudPlayerView;

#define HUD_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern Gfx D_1000118;
extern Mtx D_2000180;
extern Mtx D_20000C0;

extern s8 D_80750560[9];
extern HudTextEntry *D_807FC7F0[2];
extern s8 D_807FC7F8[2];
extern u32 D_807FBB60;
extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB4C;
extern char **D_807FC7E0;
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
extern HudCountEntry D_807FC950[];
extern HudCountEntry D_807FCB26[];
extern s16 D_80744710[];
extern s16 D_80744720[];
extern s16 D_807505B2[];
extern s16 D_807505B8[];
extern s16 D_807505CC[];
extern s8 D_80750530[5];
extern u8 D_80750531[];
extern u16 D_807ECD58;
extern s32 D_8076A0A8;
extern u8 D_807505F8[];
extern u8 D_807505F9[];
extern s8 D_807FC80E;
extern s8 D_807FC8B9;
extern HudPlayerView *D_807FC924;
extern s8 D_8076A105;

void heapFree(void *);
void heapFreeDeferred(void *);
void *heapAlloc(s32);
s32 _sprintf(char *, const char *, ...);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s32, void *, s32);
s32 textGetStringWidth();
Gfx *renderRotatedSprite(Gfx *, s32, s32, u8, s32, s32, s32, s32, f32, f32, s32, f32);
Gfx *gfxFillScreenColor(Gfx *, s32, s32, s32, s32);
Gfx *hudSetupTextState(Gfx *);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, void *);
void hudPauseMenuBuildPage();
void hudPauseMenuIconUpdate();
void func_80714998(u8);
void func_8071495C(void);
void func_807149FC(s32);
void func_80714950(void *);
void func_8071498C(void (*)());
void func_80714A28(s32);
HudTextObj *func_80714CC0(s32, f32, f32, f32, f32);
s32 slotQueueGetSpriteAsset(s32);
f32 randomFloat(void);
f32 sqrtf(f32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
s32 flagGet(s16, s32);
s32 flagCountRange(s32, s32, s32);
void actorSpawn(s32, s32);
void actorDespawn(Actor *);
char *textTableGetString(s32, s32, s32);
void camStartPath(s32, s32, s32);
void func_80724994(s32, s32, s32, s32, s32);
void func_805FF378(s32, s32);
void func_805FF544(void);
void func_805FF898(void);
void screenWipeStart(s32);
void func_80714638(void);
void renderCallbacksRegister(void *, void *, s32);

s32 hudFindItemIndex(s8 arg0) {
    s32 i;

    if (arg0 == D_80750560[0]) {
        return 0;
    }
    for (i = 1; i < 9; i++) {
        if (arg0 == D_80750560[i]) {
            return i;
        }
    }
    return 0;
}

#ifdef NON_MATCHING
typedef struct HudPauseState {
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
} HudPauseState;

typedef struct HudPauseAxis {
    u8 pad0[2];
    s8 unk2;
    s8 unk3;
} HudPauseAxis;

typedef struct HudPauseCamera {
    u8 pad0[0x214];
    f32 unk214;
} HudPauseCamera;

extern HudPauseAxis *D_807ECDEC;
extern u8 D_807467E4;
extern s32 D_8076A098;
extern u8 D_8076A0AB;
extern s32 D_807FBB64;
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

s32 func_805FF000();
s32 func_805FF030();
s32 func_805FEF74();
s32 func_80712628();
void eepromSavePlayerData();
void func_80712EDC();
void func_807127B4();
s32 func_806C8DE0();
s32 func_806CC10C(s16, s16);
void func_80600044();
void flagSet(s32, s32, s32);
void hudPauseMenuRefreshTotals();
s32 hudPauseMenuSlidePage();
Gfx *hudDrawDimOverlay(Gfx *, Actor *);
Gfx *hudPauseMenuRender(Gfx *, Actor *);
void hudFreeBuffers(void);

#define HUD_PAUSE_MODE (*(s8 *)D_807505CC)
#define HUD_PAUSE_LIST ((s8 *)&D_80750530)

void hudPauseMenuUpdate(void) {
    HudPauseState *hud;
    s32 i;
    s32 diff;
    s32 flag;
    s32 moved;
    s32 buttons;
    s32 x;
    s32 a2;
    s32 lim;
    s32 half;

    hud = D_807FBB40->unk174;
    i = D_8076A0A8;
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
            if (func_805FF000(D_8076A0A8 & 0xFF) == 9 || (D_807FBB64 & 0x10000000)) {
                HUD_PAUSE_MODE = 2;
            } else {
                HUD_PAUSE_MODE = 0;
            }
            break;
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FC7E0 = heapAlloc(0x6C);
        for (i = 0; i < 0x1B; i++) {
            D_807FC7E0[i] = textTableGetString(0x24, i, 0);
        }
        D_807FC7E8 = heapAlloc(0x24);
        for (i = 0; i < 9; i++) {
            D_807FC7E8[i] = textTableGetString(0x23, i, 0);
        }
        D_8076A098++;
        D_807FC7FC = ((HudPauseCamera *)D_807FC924)->unk214;
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
        hud->unk14 = func_806C8DE0(0);
        hud->unk8[0] = hudFindItemIndex(func_805FF030(D_8076A0AB, 1));
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
        hudPauseMenuRefreshTotals(D_807FC7F8);
        hudPauseMenuBuildPage(hud, 0);
        D_807FBB60 &= 0xFFFEFFCF;
        screenWipeStart(7);
    }
    if (hud->unk0 == 0.0f && D_807FC8B8 == 0) {
        moved = hud->unk8[hud->unk15] != hud->unk8[1 - hud->unk15];
        buttons = *D_807FC924->unk298;
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
                    lim = D_807ECDEC->unk3;
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
                                func_805FF378(D_8076A0A8, 0);
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
                    i = (a2 = func_805FF030(D_8076A0AB, 1)) == 8;
                    if (D_807FC8B8 && D_807FC8B8) {} // FAKE: steers seq temp register (a0 not v1)
                    if (i) {
                        i = func_80712628() != 0;
                    }
                    D_807FC8B8 = 1;
                    if (HUD_PAUSE_MODE == 0 && a2 != 7 && a2 != 0xD && a2 != 9 && i == 0) {
                        if (a2 == 0xA) {
                            func_80712EDC();
                        } else if (func_805FEF74(D_8076A0A8) == 0) {
                            x = D_807FBB64 & 1;
                            if (x != 0 && a2 == 8) {
                                flagSet(0x5C, 1, 2);
                                func_805FF378(0x22, 0xC);
                            } else if (x != 0 && D_8076A0A8 != 0x3C) {
                                func_805FF378(0x2A, 2);
                            } else {
                                func_80600044(a2);
                            }
                        }
                    } else if (HUD_PAUSE_MODE != 0) {
                        if (HUD_PAUSE_MODE == 2) {
                            func_805FF898();
                        } else {
                            func_805FF544();
                        }
                    } else if (a2 == 7 || i != 0) {
                        func_807127B4();
                    }
                }
                break;
            case 1:
                hud->unk10 = D_807505A4[D_807FC800] + (s16)(D_807FC804 * 0.5f * D_807FC802);
                hud->unk10 = hud->unk10 & 0xFFF;
                if (D_807FC804 == 0.0f) {
                    D_807FC802 = 0;
                    if (moved == 0) {
                        x = D_807ECDEC->unk2;
                        if (x < -0x28) {
                            do {
                                D_807FC802 -= 0x333;
                                D_807FC800 += 1;
                                if (D_807FC800 >= 5) {
                                    D_807FC800 = 0;
                                }
                            } while (HUD_PAUSE_LIST[D_807FC800] == 0);
                        } else if (x >= 0x29) {
                            do {
                                D_807FC802 += 0x333;
                                D_807FC800 -= 1;
                                if (D_807FC800 < 0) {
                                    D_807FC800 = 4;
                                }
                            } while (HUD_PAUSE_LIST[D_807FC800] == 0);
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
                diff = i = -func_806CC10C(D_807FC80D * D_807FC83A, hud->unk10);
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
                    x = D_807ECDEC->unk2;
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
                if (hud->unk4 > 1.0f && D_807FC80C != D_807FC80D) {
                    D_807FC80C = D_807FC80D;
                }
                break;
        }
    }
    if (hud->unk16 == 1) {
        hud->unk0 = hud->unk0 + 0.13f;
        if (hud->unk0 > 1.3f) {
            if (D_807505D4) {} // FAKE: steers D_807505D4 address hoist
            x = hud->unk13;
            hud->unk0 = 1.0f;
            if (-1 == x) {
                hudFreeBuffers();
            } else {
                hud->unk12 = x;
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
    half = D_807505D4 - 1;
    D_807505D4 = half;
    if ((s8)half < 0) {
        D_807505D4 = 0;
    }
    if (D_807467E4 == 0x1C) {
        sfxPlayOnFreeSlot(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
    if (D_8075052C != 0) {
        D_8075052C -= 1;
        hud->unk0 = D_80750584[D_8075052C];
        ((HudPauseCamera *)D_807FC924)->unk214 = D_807FC7FC + hud->unk0 * 100.0;
    }
    renderCallbacksRegister(hudDrawDimOverlay, D_807FBB40, 1);
    renderCallbacksRegister(hudPauseMenuRender, D_807FBB40, 5);
}

#undef HUD_PAUSE_MODE
#undef HUD_PAUSE_LIST
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/hudPauseMenuUpdate.s")
#endif

void hudFreeBuffers(void) {
    s32 i;
    u8 *sub;

    sub = D_807FBB4C->unk174;
    D_807FBB60 |= 0x40;
    if (!(*(s32 *)(sub + 0x1F0) & 0x20000000)) {
        D_807FBB60 |= 0x10030;
    }
    heapFree(D_807FC7F0[0]);
    D_807FC7F8[1] = D_807FC7F8[0] = (s32)(D_807FC7F0[1] = D_807FC7F0[0] = 0);
    for (i = 0; i < 0x6C; i += 4) {
        heapFreeDeferred(*(void **)((u8 *)D_807FC7E0 + i));
    }
    heapFreeDeferred(D_807FC7E0);
    for (i = 0; i < 0x24; i += 4) {
        heapFreeDeferred(*(void **)((u8 *)D_807FC7E8 + i));
    }
    heapFreeDeferred(D_807FC7E8);
}

Gfx *hudSetupTextState(Gfx *dl) {
    HUD_WRITE_GFX(dl++, 0xDE000000, (u32)&D_1000118);
    HUD_WRITE_GFX(dl++, 0xDA380003, (u32)&D_2000180);
    HUD_WRITE_GFX(dl++, 0xDA380007, (u32)&D_20000C0);
    HUD_WRITE_GFX(dl++, 0xE7000000, 0);
    HUD_WRITE_GFX(dl++, 0xFA000000, 0xFFFFFFFF);
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

#ifdef NON_MATCHING
typedef struct {
    f32 unk0;
    f32 unk4;
    s16 unk8[2];
    s16 unkC[2];
    s16 unk10;
    s8 unk12;
    u8 pad13;
    s8 unk14;
    u8 pad15[2];
    s8 unk17;
} HudPauseRenderState;

f32 func_80612790(s16);
f32 func_80612794(s16);
s32 func_805FF030(s32, s32);
s32 func_80712628(void);
Gfx *hudDrawCountPair(s16, s16, s16, s16, Gfx *, s8, f32);
Gfx *hudDrawItemLabel(Gfx *, HudEntry *, s32);
extern s16 D_807FC992[];
extern u8 D_807FCC4C;
extern s8 D_807FCC4B;
extern s32 D_8076A064;
extern u8 D_8076A0AB;
extern s8 D_80750538;
extern s16 D_8075056C[];
extern s8 D_807FC80C;
extern s8 D_807FC818[];
extern f32 D_807FC840[];
extern f32 D_807FC868[];
extern f32 D_807FC890[];

Gfx *hudPauseMenuRender(Gfx *dl, Actor *actor) {
    char buf[0x40];
    HudPauseRenderState *hud;
    s16 j;
    s16 i;
    s32 y;
    s32 off;
    s32 t0;
    HudTextEntry *it;
    HudCountEntry *tab;
    Gfx *ret;
    Gfx *list;
    s32 sp138;
    s16 ang;
    s16 y0;
    s8 s2;
    s32 x; /* unused: reserves the frame slot the target has */
    f32 fa;
    f32 fb;
    f32 fc;
    f32 fd;

    hud = actor->unk174;
    tab = (HudCountEntry *)((u8 *)D_807FC7F8 + 0x158);
    sp138 = func_805FF030(D_8076A0AB, 1);
    list = heapAlloc(0x1F40);
    heapFreeDeferred(list);
    gSPDisplayList(dl++, list);
    ret = dl;
    dl = hudSetupTextState(list);
    for (i = 0; i < 2; i++) {
        it = D_807FC7F0[i];
        if (it != 0) {
            for (j = 0; j < D_807FC7F8[i]; j++) {
                fa = hud->unk0;
                if ((s8)it[j].unk10 == 2) {
                    fa += hud->unk4;
                }
                off = it[j].unk8;
                y = it[j].unkA;
                off = off * 4 + (s32)(fa * it[j].unk0);
                y = y * 4 + (s32)(fa * it[j].unk4);
                off = off + it[j].unkC * 4;
                y = y + it[j].unkE * 4 + hud->unkC[i] * 4;
                dl = textDrawStringVtx(dl, 1, (s16)off, (s16)y, it[j].unk11, 1);
            }
        }
    }
    switch (hud->unk12) {
        case 0:
            s2 = D_807FCC4B;
            y0 = 0x140; /* narrow var: keeps (f32)0x140 unfolded */
            y0 = 0xA0 - (s32)((f32)y0 * hud->unk0);
            j = 0;
            if (D_807FCC4C > 0) {
                f32 fb;
                fb = (f32)(u32)((D_807FCC4C * 0x34 - 0x34) & 0xFF);
                do {
                    s32 off;
                    s16 ang;
                    f32 fa;
                    f32 fc;
                    f32 fd;
                    f32 fe;
                    f32 fh;
                    s16 y;
                    off = (j << 10) + D_8076A064 * 200;
                    ang = off;
                    fa = func_80612794(ang) * 0.3f + 3.0f;
                    fc = func_80612794(off + 0x800) * 0.3f + 3.0f;
                    fd = func_80612794((off >> 1) + 0x200) * 10.0f;
                    fa = fa * 0.75f;
                    fd = fd * 0.75f;
                    fc = fc * 0.75f;
                    fe = (func_80612794(ang) * 0.5f + 0.5f) * 30.0f * 0.75f;
                    gDPPipeSync(dl++);
                    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0x50);
                    y = (s32)((f32)(j * 0x69 + 0x280) + fd - fb);
                    fh = -fc;
                    dl = renderRotatedSprite(dl, 0x5D, 0, 2, 0x30, 0x2A, y, y0 + (s16)(s32)fe, fa, fh, 0, 0.0f);
                    gDPPipeSync(dl++);
                    dl->words.w1 = 0xFFFFFFFF;
                    dl->words.w0 = 0xFA000000;
                    dl++;
                    if (s2 > 0) {
                        off = s2 - 1;
                        if (off < 3) {
                            t0 = off;
                        } else {
                            t0 = 3;
                        }
                        dl = renderRotatedSprite(dl, (u16)(t0 + 0x5A), 0, 2, 0x30, 0x2A, y, (s32)((f32)y0 + fe), fa, fh, 0, 0.0f);
                    }
                    if (s2 - 4 < 0) {
                        s2 = 0;
                    } else {
                        s2 = s2 - 4;
                    }
                    j++;
                } while (j < ((u8 *)tab)[0x2FC]);
            }
            gDPPipeSync(dl++);
            y = 0x198;
            j = 0;
            off = (s32)((1.0f - hud->unk0) * 255.0f);
            ang = off;
            if (ang < 0) {
                ang = 0;
            }
            if (ang >= 0x100) {
                ang = 0xFF;
            }
            if (hud->unk17 != 3) {
                do {
                    if (j == hud->unk17) {
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang);
                    } else {
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang >> 1);
                    }
                    if (j == 2 && (sp138 == 7 || (sp138 == 8 && func_80712628() != 0 && *(s8 *)D_807505CC == 0))) {
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
                    j++;
                    y += 0x44;
                } while (j < 3);
            } else {
                gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang);
                dl = hudDrawScaledText(dl, 0x280, 0x198, 0.7f, D_807FC7E0[7]);
                _sprintf(buf, "q %s", D_807FC7E0[16]);
                dl = hudDrawScaledText(dl, 0x280, 0x1E8, 1.0f, buf);
                _sprintf(buf, "b %s", D_807FC7E0[17]);
                dl = hudDrawScaledText(dl, 0x280, 0x238, 1.0f, buf);
            }
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                off = hud->unkC[i] * 4;
                ang = -hud->unk10;
                fa = 1.0f - hud->unk0;
                if (off < 0x3B6 && off >= -0x3B5) {
                    if (fa > 0.05f) {
                        f32 fb;
                        f32 fc;
                        f32 fd;
                        f32 fe;
                        f32 ff;
                        fb = 180.0f * fa;
                        fa = fa * 3.0f;
                        fc = 32.0f * fa;
                        if (dl) {} // FAKE: keeps dl (param) above hoisted D_807FC840 for s7
                        fd = 6.0f * fa;
                        fe = 30.0f * fa;
                        fc = 480.0f + fc;
                        ff = (f32)((f64)fa * 1.33);
                        j = 0;
                        do {
                            y = (s32)(func_80612794(ang) * fb) + 0x280;
                            y0 = (s32)(func_80612790(ang) * fb);
                            D_807FC840[j + i * 5] = (f32)(s16)(y + 0x20) - fd;
                            D_807FC868[j + i * 5] = (f32)(s16)((s32)(fc - (f32)y0) + off) - fe;
                            D_807FC890[j + i * 5] = ff;
                            if (((s8 *)&D_80750530)[j] != 0) {
                                D_807FC890[j + i * 5] = (f32)((f64)D_807FC890[j + i * 5] * 0.75);
                            }
                            j++;
                            ang += 0x333;
                        } while (j < 5);
                        gDPPipeSync(dl++);
                    }
                    dl = hudDrawItemLabel(dl, (HudEntry *)hud, i);
                }
                j = hud->unk8[i];
                if (j != 8) {
                    f32 fa;
                    f32 fb;
                    f32 fc;
                    f32 fd;
                    fa = hud->unk4;
                    fb = hud->unk0;
                    fc = 780.0f;
                    if (fa < fb) {
                        fd = fb;
                    } else {
                        fd = fa;
                    }
                    if (off == 0) {
                        fc = fc + fd * 400.0;
                    }
                    dl = hudDrawCountPair(0x2A8, (s32)((f32)off + fc), *(s16 *)((u8 *)D_807FC992 + hud->unk14 * 0x5E + D_80750560[j] * 2), 5, dl, 0, 0.8f);
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
                    dl = hudDrawItemLabel(dl, (HudEntry *)hud, i);
                }
                y = hud->unk8[i];
                t0 = 0;
                j = 0;
                do {
                    t0 += D_807FC950[j].unk42[D_80750560[y]];
                    j++;
                } while (j < 5);
                if (y != 8) {
                    f32 fa;
                    f32 fb;
                    fa = hud->unk4;
                    fb = hud->unk0;
                    fc = 780.0f;
                    if (fa < fb) {
                        fd = fb;
                    } else {
                        fd = fa;
                    }
                    if (off == 0) {
                        fc = fc + fd * 400.0;
                    }
                    dl = hudDrawCountPair(0x2B0, (s32)((f32)off + fc), t0, 0x19, dl, 0, 0.8f);
                }
            }
            break;
        case 3:
            dl = hudDrawScaledText(hudDrawScaledText(dl, 0x280, 0x74, 0.5f, D_807FC7E0[D_807FC818[D_807FC80C] + 18]), 0x280, 0x3C, 0.65, D_807FC7E0[6]);
            fa = hud->unk4;
            fb = hud->unk0;
            if (fa < fb) {
                fd = fb;
            } else {
                fd = fa;
            }
            fc = (1.0f - fd) * 0.65f;
            if (fc < 0.01f) {
                fc = 0.01f;
            }
            dl = hudDrawCountPair(0x280, 0x33C, (&D_807FC828)[D_807FC818[D_807FC80C]], D_8075056C[D_807FC818[D_807FC80C]], dl, 1, fc);
            break;
    }
    dl->words.w0 = 0xDF000000;
    dl->words.w1 = 0;
    return ret;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/hudPauseMenuRender.s")
#endif

Gfx *hudDrawCountPair(s16 x, s16 y, s16 n1, s16 n2, Gfx *dl, s8 flag, f32 scale) {
    Mtx *mtx;
    s32 w;
    f32 m1[4][4];
    f32 m2[4][4];
    char buf1[8];
    char buf2[8];

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
    HUD_WRITE_GFX(dl++, 0xDA380002, (u32)mtx);
    _sprintf(buf1, "%d", n1);
    _sprintf(buf2, "%d", n2);
    dl = textDrawStringVtx(textDrawStringVtx(dl, 1, 0, -0x28, buf1, 0x80), 1, w, 0x28, buf2, 0);
    HUD_WRITE_GFX(dl++, 0xD8380002, 0x40);
    dl->words.w0 = 0xE7000000;
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
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8[4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 pad13;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
} HudPausePage;

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[2];
} HudPauseFlagEntry;

extern u8 D_8074E77C;
extern u8 D_8076A0AB;
#define HUD_PAUSE_COUNT(i) ((HudPauseCountEntry *)((u8 *)D_807FC950 + (i) * 0x5E))
extern HudPauseFlagEntry D_80755DA8[];
extern s8 D_807FC800;
extern f32 D_807FC804;
extern s8 D_807FC80C;
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

s32 func_805FF030(s32, s32);
f32 floatCeil(f32);
s32 func_806C8DE0(s32);
s32 func_806F6E58(s32);
s32 slotQueueGetCountStep(s32);
s32 flagGridIndex(s32, s32, s32);
s32 flagGridSumRows(s32, s32, s32, s32);
void hudPauseMenuSpawnIcon(HudEntry *, s32, s32, s32, f32, u8, s32);
void hudPauseMenuAddCounter(HudEntry *, s16, s16, s16, s16, s32, s32, s32);

void hudPauseMenuBuildPage(arg0, arg1)
    HudEntry *arg0;
    s32 arg1;
{
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
    HudPausePage *hud;

    hud = (HudPausePage *)arg0;
    saved = D_8074E77C;
    e2 = HUD_PAUSE_COUNT(func_806C8DE0(0));
    D_8074E77C = hud->unk14;
    ent = HUD_PAUSE_COUNT(hud->unk14);
    idx = hud->unk8[hud->unk15];
    D_807FC7F8[hud->unk15] = 0;
    idx = D_80750560[idx];
    if (arg1 == 0) {
        D_807FC800 = hud->unk14;
        D_807FC80D = D_807FC80C;
        hud->unk10 = 0;
        hud->unk4 = 0.0f;
        D_807FC804 = 0.0f;
    }
    D_807FC80F = 1;
    switch (hud->unk12) {
    case 0:
        D_8074E77C = saved;
        idx = func_805FF030(D_8076A0AB, 1);
        if (idx >= 9) {
            idx = 7;
        }
        if (idx != 7 && flagGet(0x18B, 0)) {
            hudPauseMenuAddCounter(arg0, 0x1E, 0x1E, 0xC, -0xA, e2->unkA[idx], 1, 0);
            hudPauseMenuSpawnIcon(arg0, 0, 0x1E, 0x1E, 0.75f, 2, 1);
        }
        if (flagGet(0x184, 0)) {
            hudPauseMenuAddCounter(arg0, 0x1E, 0x5A, 0xC, -0xA, D_807FCC44, 1, 1);
            hudPauseMenuSpawnIcon(arg0, 4, 0x1E, 0x5A, 0.75f, 2, 1);
        }
        if (e2->unk2 != 0) {
            hudPauseMenuAddCounter(arg0, 0x1E, 0x7D, 0xC, -0xA, D_807FCC40, 1, 1);
            hudPauseMenuSpawnIcon(arg0, 2, 0x1E, 0x7D, 0.65f, 2, 1);
        }
        if (func_806F6E58(D_8074E77C)) {
            f = slotQueueGetCountStep(5);
            hudPauseMenuAddCounter(arg0, 0x1E, 0xA0, 0xC, -0xA, (s32)floatCeil((f32)(u32)D_807FCC46 / f), 1, 1);
            hudPauseMenuSpawnIcon(arg0, 5, 0x1E, 0xA0, 0.65f, 2, 1);
        }
        if (flagGet(0x18C, 0)) {
            hudPauseMenuAddCounter(arg0, 0x122, 0x5A, -0xF, -0xA, e2->unk6, 1, 0x80);
            hudPauseMenuSpawnIcon(arg0, 1, 0x122, 0x5A, 0.75f, 2, 1);
        }
        if (ent->unk4 & 1) {
            hudPauseMenuAddCounter(arg0, 0x122, 0x7D, -0xC, -0xA, ent->unk8, 2, 0x81);
            hudPauseMenuSpawnIcon(arg0, 7, 0x122, 0x7D, 0.75f, 2, 7);
        }
        if (flagGet(0x179, 0)) {
            hudPauseMenuAddCounter(arg0, 0x122, 0xA0, -0xC, -0xA, D_807FCC48, 1, 0x81);
            hudPauseMenuSpawnIcon(arg0, 6, 0x122, 0xA0, 0.65f, 2, 1);
        }
        if (D_807FC828 > 0) {
            hudPauseMenuAddCounter(arg0, 0x91, 0xBE, 0xF, -0xA, D_807FC828, 1, 0);
            hudPauseMenuSpawnIcon(arg0, 9, 0x91, 0xBE, 1.0f, 2, 1);
        }
        D_8074E77C = hud->unk14;
        break;
    case 1:
        if (idx != 7) {
            i = idx;
            if (idx != 8) {
                hudPauseMenuAddCounter(arg0, 0x1E, 0x2A, 0xC, -0xA, ent->unkA[idx] + ent->unk26[idx], 2, 0);
                hudPauseMenuSpawnIcon(arg0, 0, 0x1E, 0x2A, 0.75f, 2, 2);
            } else {
                i = 7;
            }
            if (D_807FC82E > 0) {
                if (idx != 8) {
                    D_807FC80F = (HUD_PAUSE_COUNT(D_8074E77C)->unkA[idx] + HUD_PAUSE_COUNT(D_8074E77C)->unk26[idx]) >= 0x4B;
                } else {
                    D_807FC80F = flagGridSumRows(0x225, i, i, D_8074E77C);
                }
                hudPauseMenuSpawnIcon(arg0, 0xA, 0x113, 0x7D, 0.75f, 2, 2);
                if (flagGridSumRows(0x225, i, i, D_8074E77C)) {
                    hudPauseMenuSpawnIcon(arg0, (s32)&D_80721518, 0x113, 0x7D, 0.35f, 2, 0xD);
                }
            }
        }
        if (arg1 == 0) {
            for (i = 0; i < 5; i++) {
                if (D_80750530[i]) {
                    s = D_80750518[i];
                } else {
                    s = &D_807211D0;
                }
                hudPauseMenuSpawnIcon(arg0, (s32)s, i, i, 0.75f, 2, 0xA);
                hudPauseMenuSpawnIcon(arg0, (s32)s, i + 5, i + 5, 0.75f, 2, 0xA);
            }
        }
        if (idx != 8) {
            hudPauseMenuSpawnIcon(arg0, 9, 0x91, 0xCB, 1.0f, 2, 2);
            sum = 0;
            for (i = 0; i < 5; i++) {
                if (flagGridSumRows(0x1D5, 0, 7, i)) {
                    sum = 1;
                }
            }
            if (sum) {
                D_807FC80F = flagGet(flagGridIndex(0x1D5, idx, D_8074E77C), 0);
                i = 0;
                hudPauseMenuSpawnIcon(arg0, 0xC, 0x26, 0x7D, 0.75f, 2, 2);
                if (flagGet(flagGridIndex(0x1FD, idx, D_8074E77C), 0)) {
                    hudPauseMenuSpawnIcon(arg0, (s32)&D_80721518, 0x26, 0x7D, 0.35f, 2, 0xD);
                }
            }
        }
        if (arg1 == 0) {
            hud->unk10 = D_807505A4[hud->unk14];
            hudPauseMenuSpawnIcon(arg0, (s32)&D_80720C34, 0xA0, 0x78, 0.75f, 2, 0);
            if (D_807505D0 > 0) {
                hudPauseMenuSpawnIcon(arg0, (s32)&D_80720D80, 0xA0, 0x19, 0.5f, 2, 0xB);
                hudPauseMenuSpawnIcon(arg0, (s32)&D_80720D5C, 0xA0, 0x19, 0.5f, 2, 0xC);
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
            j = func_805FF030(D_80755DA8[i].unk0, 1);
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
                hudPauseMenuAddCounter(arg0, 0x24, 0x2A, 0xC, -0xA, sum, 1, 0);
                hudPauseMenuSpawnIcon(arg0, (s32)&D_80721474, 0x24, 0x2A, 0.75f, 2, 1);
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
                hudPauseMenuSpawnIcon(arg0, 0xA, D_807505A4[i], 0, 0.75f, 2, 3);
                if (flagGridSumRows(0x225, j, j, i)) {
                    hudPauseMenuSpawnIcon(arg0, (s32)&D_80721518, D_807505A4[i], 0, 0.35f, 2, 0xE);
                }
                i++;
            } while (i != 5);
            if (D_807FC82A > 0) {
                D_807FC80F = flagGet(D_807505B8[idx], 0);
                hudPauseMenuSpawnIcon(arg0, (s32)&D_807210EC, 0xA0, 0x78, 1.0f, 2, 4);
            }
            if (flagGet(0x179, 0)) {
                D_807FC80F = found[0];
                hudPauseMenuSpawnIcon(arg0, (s32)&D_80721094, 0x3C, 0x78, 1.0f, 2, 6);
                D_807FC80F = found[1];
                hudPauseMenuSpawnIcon(arg0, (s32)&D_80721094, 0x104, 0x78, 1.0f, 2, 6);
            }
        } else {
            if (D_807FC82A > 0) {
                D_807FC80F = flagGet(D_807505B8[idx], 0);
                hudPauseMenuSpawnIcon(arg0, (s32)&D_807210EC, 0xA0, 0x55, 1.0f, 2, 4);
                D_807FC80F = flagGet(D_807505CA, 0);
                hudPauseMenuSpawnIcon(arg0, (s32)&D_807210EC, 0xA0, 0x91, 1.0f, 2, 4);
            }
            if (flagGet(0x179, 0)) {
                D_807FC80F = found[0];
                hudPauseMenuSpawnIcon(arg0, (s32)&D_80721094, 0x3C, 0x5A, 1.0f, 2, 6);
                D_807FC80F = found[1];
                hudPauseMenuSpawnIcon(arg0, (s32)&D_80721094, 0x46, 0x96, 1.0f, 2, 6);
                D_807FC80F = found[2];
                hudPauseMenuSpawnIcon(arg0, (s32)&D_80721094, 0x104, 0x5A, 1.0f, 2, 6);
                D_807FC80F = found[3];
                hudPauseMenuSpawnIcon(arg0, (s32)&D_80721094, 0xFA, 0x96, 1.0f, 2, 6);
            }
        }
        if (idx != 8) {
            hudPauseMenuSpawnIcon(arg0, 9, 0x91, 0xCB, 1.0f, 2, 2);
        }
        if (arg1 == 0 && D_807505D0 > 0) {
            hudPauseMenuSpawnIcon(arg0, (s32)&D_80720D80, 0xA0, 0x19, 0.5f, 2, 0xB);
            hudPauseMenuSpawnIcon(arg0, (s32)&D_80720D5C, 0xA0, 0x19, 0.5f, 2, 0xC);
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
                hudPauseMenuSpawnIcon(arg0, (s32)D_807505D8[i], x, 0, f, 2, flag);
                x += D_807FC83A;
                D_807FC818[cnt] = i;
                cnt++;
            }
        }
        hud->unk10 = D_807FC83A * D_807FC80C;
        hudPauseMenuSpawnIcon(arg0, (s32)&D_80720C34, 0xA0, 0x78, 0.75f, 2, 0);
        break;
    }
    if (arg1 == 0 && D_807FC828 > 0) {
        hudPauseMenuSpawnIcon(arg0, (s32)&D_80720D38, 0x2D, 0xC8, 1.0f, 2, 1);
        hudPauseMenuSpawnIcon(arg0, (s32)&D_8072104C, 0x113, 0xC8, 1.0f, 2, 1);
    }
    D_8074E77C = saved;
}

void hudPauseMenuSpawnIcon(HudEntry *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, u8 arg5, s32 arg6) {
    HudTextObj *obj;
    f32 *buf;
    f32 dx;
    f32 dy;
    f32 len;
    f32 fy;

    func_80714998(arg5);
    func_8071495C();
    func_807149FC(-1);
    func_80714950(arg0);
    func_8071498C(hudPauseMenuIconUpdate);
    func_80714A28(0x101);
    if (arg1 < 0) {
        fy = arg2;
        obj = func_80714CC0(arg1, arg4, fy, (f32)arg3, -10.0f);
    } else {
        fy = arg2;
        obj = func_80714CC0(slotQueueGetSpriteAsset(arg1), arg4, fy, (f32)arg3, -10.0f);
    }
    arg1 = 7;
    if (arg6 == 6) {
        arg1 = 10;
    }
    buf = heapAlloc(arg1 * 4);
    obj->unk384 = buf;
    if (arg6 == 9) {
        arg6 = 7;
        obj->unk360 = -obj->unk360;
    }
    buf[0] = arg6;
    buf[1] = arg0->unk15;
    buf[2] = obj->unk340;
    buf[3] = obj->unk344;
    switch (arg6) {
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
        if (arg6 == 13) {
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
        if (arg2 < 0xA0) {
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
        buf[4] = arg4;
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

void hudPauseMenuAddCounter(HudEntry *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s32 arg5, s32 arg6, s32 arg7) {
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
    if (arg7 & 0x80) {
        flag = 1;
        arg7 &= ~0x80;
    }
    switch (arg7) {
    case 1:
        _sprintf((char *)buf, "%02d", arg5);
        break;
    case 2:
        _sprintf((char *)buf, "%d", arg5);
        arg3 -= textGetStringWidth(1, buf) >> 1;
        break;
    default:
        _sprintf((char *)buf, "%d", arg5);
        break;
    }
    if (flag != 0) {
        arg3 -= textGetStringWidth(1, buf);
    }
    D_807FC810 = textGetStringWidth(1, buf);
    idx = D_807FC7F8[arg0->unk15];
    list = D_807FC7F0[arg0->unk15];
    len = sqrtf((640.0f - (f32)(arg1 * 4)) * (640.0f - (f32)(arg1 * 4)) + (480.0f - (f32)(arg2 * 4)) * (480.0f - (f32)(arg2 * 4)));
    list[idx].unk0 = -((640.0f - (f32)(arg1 * 4)) / len) * (1040.0f - len);
    list[idx].unk4 = -((480.0f - (f32)(arg2 * 4)) / len) * (1040.0f - len);
    list[idx].unk8 = arg1;
    list[idx].unkA = arg2;
    list[idx].unkC = arg3;
    list[idx].unkE = arg4;
    list[idx].unk10 = arg6;
    for (i = 0; buf[i] != 0; i++) {
        list[idx].unk11[i] = buf[i];
    }
    list[idx].unk11[i] = 0;
    D_807FC7F8[arg0->unk15]++;
}

Gfx *hudDrawItemLabel(Gfx *dl, HudEntry *arg1, s32 arg2) {
    u8 padHi[0xC];
    s32 col;
    void *tex;
    u8 pad[0x1C];
    s32 y2;
    s32 y;

    y = arg1->unkC[arg2] * 4;
    tex = D_807FC7E8[D_80750560[arg1->unk8[arg2]]];
    if (arg1->unk12 == 1) {
        col = arg1->unk14;
    } else {
        col = 5;
    }
    HUD_WRITE_GFX(dl++, 0xFA000000, 0xFFFFFFFF);
    y2 = y + 0x40;
    dl = hudDrawScaledText(hudDrawScaledText(dl, 0x280, y2, 0.7f, tex), 0x280, y2 + 0x38, 0.5f, D_807FC7E0[col + 9]);
    D_807FC808 = (f32)textGetStringWidth(1, tex) * 1.4;
    return dl;
}

Gfx *hudDrawScaledText(Gfx *dl, s16 arg1, s16 arg2, f32 scale, void *arg4) {
    f32 m1[4][4];
    f32 m2[4][4];
    Mtx *mtx;

    mtx = heapAlloc(0x40);
    heapFreeDeferred(mtx);
    guScaleF(m1, scale, scale, 1.0f);
    guTranslateF(m2, arg1, arg2, 0.0f);
    guMtxCatF(m1, m2, m1);
    guMtxF2L(m1, mtx);
    HUD_WRITE_GFX(dl++, 0xDA380002, (u32)mtx);
    dl = textDrawStringVtx(dl, 1, 0, 0, arg4, 0x80);
    HUD_WRITE_GFX(dl++, 0xD8380002, 0x40);
    return dl;
}

#ifdef NON_MATCHING
extern s8 D_807FC7F9;

s32 hudPauseMenuSlidePage(HudEntry *arg0, s32 arg1, s32 arg2) {
    s32 dir;
    s32 idx;
    s32 v;
    s32 d;

    if (arg1 == 0) {
        dir = 0;
        if (arg2 & 8) {
            dir = 1;
        } else if (arg2 & 4) {
            dir = -1;
        }
        if (dir != 0) {
            idx = arg0->unk15;
            v = arg0->unk8[idx] + dir;
            if (dir) {
            }
            if (v < 0) {
                v = D_807505D0;
            }
            if (D_807505D0 < v) {
                v = 0;
            }
            if (v != arg0->unk8[idx]) {
                arg0->unk15 = 1 - idx;
                arg0->unk8[arg0->unk15] = v;
                arg0->unkC[arg0->unk15] = dir * 0xFA;
                hudPauseMenuBuildPage(arg0, 0, idx);
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
    }
    if (arg1 != 0) {
        d = arg0->unkC[arg0->unk15];
        if (d >= 0x15) {
            d = 0x14;
        }
        if (d < -0x14) {
            d = -0x14;
        }
        arg0->unkC[0] -= d;
        arg0->unkC[1] -= d;
        if (arg0->unkC[arg0->unk15] == 0) {
            arg0->unk8[1 - arg0->unk15] = arg0->unk8[arg0->unk15];
            (&D_807FC7F9)[-arg0->unk15] = 0;
            arg1 = 0;
            sfxPlayOnFreeSlot(0x97, 0x4650, 63.0f, 1.0f, 0, 0);
            D_8075052C = 3;
        }
    }
    return arg1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/hudPauseMenuSlidePage.s")
#endif


void hudPauseMenuRefreshTotals(void) {
    s16 *p;
    s16 *p0;
    HudCountEntry *e;
    s32 n;
    s32 i;
    s32 k;
    s32 m;

    p0 = (s16 *)((u8 *)&D_807FC82A - 2); do {
        *p0++ = 0;
    } while (p0 < (s16 *)((u8 *)&D_807FC82A + 12));
    n = 0;
    k = 0; e = D_807FC950; do { n += D_807FC950[k].unk42[0]; n += D_807FC950[k].unk42[1];
        for (i = 2; i < 14; i++) {
            n += e->unk42[i];
        }
        e++;
        k++;
    } while (&D_807FC950[k] < D_807FCB26);
    D_807FC828 = n;
    n = 0;
    p = D_80744710; do {
        if (flagGet(*p, 0) != 0) {
            n++;
        }
        p++;
    } while (p < D_80744720);
    D_807FC82C = n;
    D_807FC832 = flagCountRange(0x24D, 0x14, 0);
    D_807FC82E = flagCountRange(0x225, 0x28, 0);
    m = 0;
    p = D_807505B8; do {
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

typedef struct {
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

f32 func_80612790(s16);
f32 func_80612794(s16);
extern f32 D_807FC840[];
extern f32 D_807FC868[];
extern f32 D_807FC890[];
extern u8 D_8075054C[][4];
extern s32 D_8076A064;

void hudPauseMenuIconUpdate(HudIconObj *arg0, s8 *arg1) {
    HudIconSource *src;
    HudIconState *item;
    f32 t;
    f32 sc;
    s32 type;
    s32 sp40;
    s32 ang;
    s32 i;
    s16 five;

    src = arg0->unk35C;
    if (arg0->unk384 != NULL) {
        t = src->unk0;
        item = arg0->unk384;
        sp40 = (f64)src->tbl[(s32)item->unk4] * 4.0;
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
            arg0->unk36D = (s32)(t * 255.0f);
            if (type == 4) {
                arg0->unk360 = (f64)(item->unk10 * t) * 4.0;
                arg0->unk364 = arg0->unk360;
            }
            arg0->unk340 = item->unk8;
            arg0->unk344 = item->unkC + (f32)sp40;
            if (type == 0xB) {
                arg0->unk340 = 600.0 - D_807FC808;
            }
            if (type == 0xC) {
                arg0->unk340 = D_807FC808 + 680.0;
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
                ang = (D_8076A064 * 0x78) & 0xFFF;
                arg0->unk364 = (f64)func_80612794(ang) * 0.35 + item->unk18;
            }
            arg0->unk340 = item->unk10 * t + item->unk8;
            arg0->unk344 = item->unk14 * t + item->unkC + (f32)sp40;
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
            arg0->unk360 = (f64)(item->unk10 * t) * 4.0;
            arg0->unk364 = arg0->unk360;
            t = 0.0;
            arg0->unk340 = (f64)(func_80612794(ang) * sc) + 640.0;
            arg0->unk344 = (480.0 - (f64)(func_80612790(ang) * sc)) + (f64)sp40;
            if (type == 8) {
                ang = (D_8076A064 * 0x78) & 0xFFF;
                sc = func_80612794(ang);
                arg0->unk344 = arg0->unk344 + sc * 10.0f;
            }
            if (type == 0xF) {
                ang = (D_8076A064 * 0x78) & 0xFFF;
                sc = func_80612794(ang);
                arg0->unk364 = arg0->unk364 * (1.0 + (f64)sc * 0.2);
            }
            if (type == 5 || type == 8 || type == 0xF) {
                i = 0xFF - (s32)(((f64)arg0->unk344 - 240.0) * 1.5);
                if (i < 0x5F) {
                    i = 0x5F;
                }
                if (i >= 0x100) {
                    i = 0xFF;
                }
                arg0->unk36A = i;
                arg0->unk36B = i;
                arg0->unk36C = i;
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
                    item->unk18 = (f64)func_80612794(ang) * ((f64)sc * 0.8);
                    item->unk1C = func_80612790(ang) * sc;
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
            ang = (D_8076A064 * 0x78) & 0xFFF;
            arg0->unk340 = item->unk10 + item->unk8;
            sc = func_80612794(ang);
            arg0->unk344 = sc * 10.0f + (item->unkC + item->unk14 + (f32)sp40 + 960.0f * t);
            t = 0.0f;
            break;
        case 10:
            i = (s32)item->unk8;
            arg0->unk340 = D_807FC840[i];
            arg0->unk344 = D_807FC868[i];
            arg0->unk360 = D_807FC890[i];
            arg0->unk364 = D_807FC890[i];
            D_807FC840[i] = -200.0f;
            D_807FC868[i] = -200.0f;
            five = 5;
            if (i >= five) {
                i -= five;
            }
            if (((s8 *)&D_80750530)[i] == 0) {
                arg0->unk36A = D_8075054C[i][0];
                arg0->unk36B = D_8075054C[i][1];
                arg0->unk36C = D_8075054C[i][2];
            }
            break;
        }
        if ((s32)item->unk4 != src->unk15 && (sp40 < -0x3C0 || sp40 >= 0x3C1)) {
            *arg1 = 1;
        }
        if (t > 1.0f || src->unk0 > 1.0f) {
            *arg1 = 1;
        }
    }
}

Gfx *hudDrawTextScreen(Gfx *dl, Actor *actor) {
    char buf[0x28];
    s32 remaining;
    s32 val;

    remaining = 0xFF - actor->unk128;
    if (remaining >= 9) {
        val = 8;
    } else {
        val = remaining;
    }
    actor->unk128 += val;
    if (actor->unk128 >= 0x80) {
        val = 0x7F;
    } else {
        val = actor->unk128;
    }
    dl = hudSetupTextState(gfxFillScreenColor(dl, 0, 0, 0, val));
    gDPSetCombineLERP(dl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    dl->words.w0 = 0xFA000000;
    dl->words.w1 = (actor->unk128 & 0xFF) | 0xFFFFFF00;
    dl++;
    dl = textDrawStringVtx(dl, 1, 0x168, 0x104, D_807FC7E0[0], 1);
    _sprintf(buf, "q %s", D_807FC7E0[1]);
    dl = textDrawStringVtx(dl, 1, 0x208, 0x190, buf, 1);
    _sprintf(buf, "b %s", D_807FC7E0[2]);
    return textDrawStringVtx(dl, 1, 0x208, 0x21C, buf, 1);
}

void hudSpawnTextScreen(u8 arg0) {
    actorSpawn(0x156, 0);
    D_807FBB44->unk15F = arg0;
    D_807FBB44->unk64 |= 2;
    D_807FBB60 |= 0x40001;
}

void hudFreeTextAndDespawn(void) {
    s16 i;

    D_807FBB60 |= 0x40;
    for (i = 0; i < 3; i++) {
        heapFreeDeferred(D_807FC7E0[i]);
    }
    heapFreeDeferred(D_807FC7E0);
    actorDespawn(D_807FBB40);
}

void hudTextScreenUpdate(void) {
    s32 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk168 = 0x1E;
        D_807FBB40->unk128 = 0;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FC7E0 = heapAlloc(0xC);
        for (i = 0; i < 3; i++) {
            D_807FC7E0[i] = textTableGetString(0x24, i + 0xF, 0);
        }
    }
    if (D_807FBB40->unk168 != 0) {
        D_807FBB40->unk168--;
    } else if (D_807FBB40->unk154 == 0) {
        if (D_807ECD58 & 0x8000) {
            switch (D_807FBB40->unk15F) {
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
                    func_805FF378(D_8076A0A8, 0);
                    break;
            }
            D_807FBB40->unk154 = 1;
        } else if (D_807ECD58 & 0x4000) {
            switch (D_807FBB40->unk15F) {
                case 3:
                case 4:
                    func_80724994(3, 7, 0x3C, 0, 0);
                case 2:
                    hudFreeTextAndDespawn();
                    break;
                case 1:
                    func_805FF544();
                    break;
                default:
                    func_805FF898();
                    break;
            }
            D_807FBB40->unk154 = 1;
        }
    }
    renderCallbacksRegister(hudDrawTextScreen, D_807FBB40, 5);
}

Gfx *hudDrawTwoOptionMenu(Gfx *dl, Actor *actor) {
    u8 sel;
    u8 c;

    dl = hudSetupTextState(dl);
    sel = actor->unk155[0] == 0;
    c = D_807505F8[sel];
    gDPSetPrimColor(dl++, 0, 0, c, c, c, 255);
    dl = hudDrawScaledText(dl, 0x280, 0x1B8, 0.7f, D_807FC7E0[0]);
    c = D_807505F9[-sel];
    gDPSetPrimColor(dl++, 0, 0, c, c, c, 255);
    return hudDrawScaledText(dl, 0x280, 0x208, 0.7f, D_807FC7E0[3]);
}

void hudTwoOptionMenuUpdate(void) {
    s32 i;
    s32 off;
    u16 btn;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FC7E0 = heapAlloc(0x10);
        i = 0;
        do {
            D_807FC7E0[i] = textTableGetString(0x24, i, 0);
            i++;
        } while (i != 4);
        D_807FBB60 &= ~0x10030;
        screenWipeStart(7);
        D_807FC80E = 0;
        D_807FBB40->unk155[0] = 0;
    }
    i = D_807FC8B9;
    off = i * 0x2F0;
    if (((HudPlayerView *)((u8 *)D_807FC924 + off))->unk294->unk3 >= 0x33 || ((HudPlayerView *)((u8 *)D_807FC924 + off))->unk294->unk3 < -0x32) {
        if (!(D_807FC80E & 1)) {
            D_807FBB40->unk155[0] = 1 - D_807FBB40->unk155[0];
            D_807FC80E |= 1;
            sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
    } else {
        D_807FC80E &= 0xFFFE;
    }
    btn = *((HudPlayerView *)((u8 *)D_807FC924 + off))->unk298;
    if (btn & 0x8000) {
        if (D_807FBB40->unk155[0] == 0) {
            D_807FBB60 |= 0x10070;
            for (i = 0; i < 4; i++) {
                heapFreeDeferred(D_807FC7E0[i]);
            }
            heapFreeDeferred(D_807FC7E0);
        } else if (D_807FBB40->unk155[0] == 1) {
            D_8076A105 = -1;
            func_80714638();
            D_807FBB40->unk155[0] = 2;
        }
    }
    renderCallbacksRegister(hudDrawDimOverlay, D_807FBB40, 1);
    renderCallbacksRegister(hudDrawTwoOptionMenu, D_807FBB40, 5);
}
