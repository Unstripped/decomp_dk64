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
s32 func_80609140(s32, s32, f32, f32, s32, s32);
extern s8 D_80033734;
extern s32 gCamActor;

void func_80027E60(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_v0 = arg0->unk174;
    s32 var_v1 = 0;

    if (D_80033734 != 0) {
        D_80033734++;
        if (D_80033734 >= 0xB) {
            var_v1 = 1;
        }
    }
    if (temp_v0->unk0 == 0.0 && (var_v1 != 0 || (arg1 & 1))) {
        temp_v0->unk12 = 1;
        temp_v0->unk16 = -1;
        temp_v0->unk0 = 1.0f;
        menuUpdateStateDispatch(arg0, 0, 0, 0);
        camEndPath(gCamActor);
        func_80609140(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        D_80033734 = 0;
    }
}

Gfx *func_80027F34(void *arg0, Gfx *arg1) {
    return arg1;
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

extern MenuActor *D_807FBB40;
extern MenuActor *D_807FBB44;
extern MenuActor *D_807FBB4C;
extern s8 D_80033734;
extern s32 D_807FBB60;

void menuResetCameraAndFlags(MenuScreenActor *arg0, s32 arg1) {
    f32 *temp_v0 = arg0->unk174;
    D_807FBB4C->unk7C = 109.0f;
    D_807FBB4C->unk80 = 6.0f;
    D_807FBB4C->unk84 = 55.0f;
    *temp_v0 = 0.0f;
    D_80033734 = 0;
    D_807FBB60 |= 0x10000;
}

#ifdef NON_MATCHING
typedef struct {
    s32 unk0;
    s32 unk4;
} MenuL1b_Pair;

typedef struct {
    f32 unk0;
    f32 unk4;
    char pad8[0xB];
    s8 unk13;
    char pad14[2];
    s8 unk16;
    s8 unk17;
} MenuL1b_S174;

extern s16 D_800336A0;
extern s16 D_800336A4[];
extern s16 D_80033724[];
extern s8 D_800337F0;
extern s8 D_800337F4;
extern MenuL1b_Pair D_800337FC;
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
s32 func_806119A0();
f32 func_806119FC();
void func_8067AB20(s32, s32, s32, s32, void *, s32);
void gfxSetBackgroundBlend(f32);
void lightSetColor(f32, f32, f32, s32);
void menuHandleScrollInput();
void menuUpdateItemTransition(void *, MenuScreenState *, s32);
void menuUpdateScrollAnimation();
void spawnNodesSetActorStateByFlag(s32, s32);

void func_80027FAC(void *arg0, s32 arg1) {
    MenuL1b_S174 *var_a3;
    MenuL1b_Pair sp54;
    s32 sp50;
    s8 sp4F;
    s16 *var_a0;
    s16 var_a1;
    s16 var_a0_2;
    s16 temp_t2;
    s32 var_v0;
    f32 var_ft4;

    var_a3 = *(MenuL1b_S174 **)((u8 *)arg0 + 0x174);
    sp54 = D_800337FC;
    sp4F = 0;
    if (D_800337F4 > 0) {
        D_800337F4 -= 1;
    } else {
        D_800337F4 = 0;
    }
    D_800337F0 = 0;
    if (var_a3->unk0 == 0.0f && D_80033F3C == 0.0f && D_800337F4 == 0) {
        if (var_a3->unk4 == 0.0f) {
            D_800337F0 = 1;
            switch (var_a3->unk17) {
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
            menuHandleScrollInput(var_a3, 5, arg1);
        }
        menuUpdateScrollAnimation(var_a3, 5);
    }
    D_8076A0D2 = 0;
    if (D_80033F40 != 0.0f) {
        D_80033F3C += D_80033F40;
        if (D_80033F3C > 1.0f) {
            D_80033F3C = 1.0f;
            var_a3->unk16 = 0;
            switch (var_a3->unk17) {
            default:
                var_a3->unk13 = 2;
                break;
            case 1:
                var_a3->unk13 = 8;
                break;
            case 2:
                var_a3->unk13 = 6;
                break;
            case 3:
                var_a3->unk13 = 0xA;
                break;
            case 4:
                var_a3->unk13 = 9;
                break;
            }
            if (camIsCutsceneActive() != 0) {
                camEndPath(gCamActor);
            }
            spawnNodesSetActorStateByFlag(0x40, 0x3C);
            if (D_80033F55 != 0) {
                sp4F = -1;
            }
            D_80033F56 = 0;
        }
    }
    menuUpdateItemTransition(arg0, var_a3, 0);
    D_80033F52 -= 1;
    if (D_80033F52 <= 0) {
        var_a0 = &D_800336A4[D_80033F54];
        if (*var_a0 != -5) {
            if (*var_a0 != -4) {
                if (*var_a0 != -3) {
                    if (*var_a0 == -2) {
                        D_80033F54 += 2;
                        sp4F = 1;
                        D_80033F52 = var_a0[1];
                    } else if (*var_a0 < -5) {
                        var_a1 = -6 - *var_a0;
                        if (D_800337F4 == 0) {
                            actorScriptStart(D_807FBB4C, D_80033724[(s16)var_a1]);
                            var_a0 = &D_800336A4[D_80033F54];
                        }
                        D_80033F54 += 2;
                        D_80033F52 = var_a0[1];
                    } else if (*var_a0 >= 0) {
                        camStartPath(0, *var_a0, 1);
                        D_80033F52 = D_800336A4[D_80033F54 + 1];
                        D_80033F54 += 2;
                    } else {
                        var_a1 = 0;
                        var_a0_2 = (s32)(func_806119FC(0) * 10.0f);
                        D_80033F52 = (func_806119A0() & 0x7F) + 0x12C;
                        D_80033F54 = 0;
                        if (var_a0_2 >= 0xB) {
                            var_a0_2 = 0;
                        }
                        var_v0 = 1 << var_a0_2;
                        temp_t2 = var_a0_2;
                        if (D_800336A0 & var_v0) {
                            do {
                                var_a0_2 += 1;
                                if (var_a0_2 == 0xB) {
                                    var_a0_2 = 0;
                                }
                                var_v0 = 1 << var_a0_2;
                                if (var_a0_2 == temp_t2) {
                                    D_800336A0 = 0;
                                }
                            } while (D_800336A0 & var_v0);
                        }
                        D_800336A0 |= var_v0;
                        if (var_a0_2 != 0) {
                            do {
                                if (D_800336A4[D_80033F54] != -1) {
                                    do {
                                        D_80033F54 += 1;
                                    } while (D_800336A4[D_80033F54] != -1);
                                }
                                var_a1 += 1;
                                D_80033F54 += 1;
                            } while (var_a1 != var_a0_2);
                        }
                    }
                } else {
                    D_80033F54 += 2;
                    sp4F = -1;
                    D_80033F52 = var_a0[1];
                }
            } else {
                D_80033F54 += 2;
                D_80033F52 = var_a0[1];
                D_80033F56 = 1;
            }
        } else {
            D_80033F54 += 2;
            D_80033F52 = var_a0[1];
            D_80033F56 = 0;
        }
    }
    if (sp4F != 0) {
        actorFindActiveByType(0xC, &sp50);
        if (sp4F < 0) {
            D_80033F55 = 0;
            var_v0 = 2;
        } else {
            D_80033F55 = 1;
            var_v0 = 1;
        }
        func_8067AB20(gCamActor, sp50, 0x01000000, var_v0 & 0xFF, &sp54, 0);
    }
    if (D_80033F56 != 0) {
        var_ft4 = 0.0f;
        D_80033F5C += 0.005;
        if (D_80033F5C > 1.0) {
            D_80033F5C = 1;
        }
    } else {
        var_ft4 = 1;
        if (D_80033F5C > 0.0) {
            D_80033F5C -= 0.005;
        } else if (D_80033F55 != 0) {
            var_ft4 = 0.45f;
        }
    }
    D_80033F58 += (var_ft4 - D_80033F58) * 0.01;
    lightSetColor(D_80033F58 * 0.83 + 0.17, D_80033F58 * 0.8 + 0.2, D_80033F58 * 0.6 + 0.4, -1);
    gfxSetBackgroundBlend(D_80033F5C);
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80027FAC.s")
#endif

extern char **D_80033F28;
s32 func_800317E8(MenuScreenState *, f32, f32, f32 *, f32 *, s32, s8, f32);

void *func_80610FE8(s32);
void heapFreeDeferred(void *);
Gfx *textDrawStringVtx(Gfx *, s16, s16, s16, void *, s32);

Gfx *func_800286C8(MenuScreenActor *arg0, Gfx *arg1) {
    Gfx *g;
    s32 spD0;
    s32 padCC;
    s32 padC8;
    f32 spC4;
    f32 spC0;
    s32 padBC;
    f32 sp7C[4][4];
    f32 sp3C[4][4];
    Mtx *sp38;
    void *temp_a0 = arg0->unk174;

    D_807FBB60 |= 0x10;
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    spD0 = func_800317E8(temp_a0, 160.0f, 20.0f, &spC4, &spC0, 5, 1, 0.3f);
    sp38 = func_80610FE8(0x40);
    heapFreeDeferred(sp38);
    guScaleF(sp7C, 0.7f, 0.7f, 1.0f);
    guTranslateF(sp3C, spC4 * 4.0, spC0 * 4.0, 0.0f);
    guMtxCatF(sp7C, sp3C, sp7C);
    guMtxF2L(sp7C, sp38);
    g = arg1++; g->words.w0 = 0xDA380003; g->words.w1 = (u32)sp38;
    return textDrawStringVtx(arg1, 1, 0, 0, D_80033F28[spD0], 0x80);
}

extern s8 D_800337F4;
extern s8 D_800337F8;
extern s8 D_8076A0D1[];
extern s8 D_80033F38;
extern s8 D_80033F54;
extern s8 D_80033F55;
extern s8 D_80033F56;
extern s16 D_80033F52;
extern s16 D_800336A4[];
extern f32 D_80033F58;
extern f32 D_80033F5C;
extern u8 D_8072052C;
extern u8 D_80720C34;
extern u8 D_80720CF0;
extern u8 D_80721094;
extern u8 D_807210EC;
extern u8 D_80721170;
extern u8 D_807211D0;
extern u8 D_80721444;
void func_80030894(MenuScreenState *, void *, s32, s32, f32, s32, s32);
s32 func_8060C6B8(s32, s32, u8, s32);
s32 flagGet(s16, u8);

void func_80028834(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;

    D_800337F8 = 0;
    D_800337F4 = 0;
    D_807FBB4C->unk154 = 0x85;
    D_807FBB4C->unk155 = 0;
    D_80745844 = func_8060C6B8(0x1E, 0, 0, 0);
    menuSetAudioMode();
    temp_s0->unk17 = D_8076A0D1[0];
    func_80030894(temp_s0, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, (void *)(s32)&D_80721444, 0, 0, 1.2f, 2, 0x12);
    func_80030894(temp_s0, (void *)(s32)&D_80721444, 1, 0, 1.2f, 2, 0x12);
    func_80030894(temp_s0, (void *)(s32)&D_80721444, 2, 0, 1.2f, 2, 0x12);
    func_80030894(temp_s0, (void *)(s32)&D_80721444, 3, 0, 1.2f, 2, 0x12);
    func_80030894(temp_s0, (void *)(s32)&D_80721444, 4, 0, 1.2f, 2, 0x12);
    func_80030894(temp_s0, &D_8072052C, 0, 0, 0.6f, 2, 6);
    func_80030894(temp_s0, &D_807211D0, 1, 0, 0.8f, 2, 6);
    if (flagGet(0, 1) == 0) {
        D_80033F38 = 0;
    }
    func_80030894(temp_s0, &D_80721094, 2, 0, 0.8f, 2, 7);
    if (flagGet(0x1C, 1) == 0) {
        D_80033F38 = 0;
    }
    func_80030894(temp_s0, &D_807210EC, 3, 0, 0.6f, 2, 6);
    func_80030894(temp_s0, &D_80721170, 4, 0, 0.6f, 2, 6);
    func_80030894(temp_s0, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
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

void func_80028C18(void) {
}

void menuHandleScrollInput();
void menuUpdateScrollAnimation();
void menuUpdateItemTransition(void *, MenuScreenState *, s32);
extern s8 D_80033F48;

void menuHandleSelectionInput(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;

    if (temp_s0->unk0 == 0.0f) {
        if (temp_s0->unk4 == 0.0f) {
            if (arg1 & 1) {
                temp_s0->unk16 = 0;
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                switch (temp_s0->unk17) {
                case 2:
                    temp_s0->unk13 = 4;
                    break;
                default:
                    D_80033F48 = temp_s0->unk17;
                    if (D_80033F48 == 3) {
                        D_80033F48 = 2;
                    }
                    temp_s0->unk13 = 3;
                    break;
                }
            } else if (arg1 & 2) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 1;
            } else {
                menuHandleScrollInput(temp_s0, 4, arg1);
            }
        }
        menuUpdateScrollAnimation(temp_s0, 4);
    }
    menuUpdateItemTransition(arg0, temp_s0, 1);
}

int _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);
s32 menuCheckSaveFile();

Gfx *func_80028D3C(MenuScreenActor *arg0, Gfx *arg1) {
    void *temp_a0 = arg0->unk174;
    s32 idx;
    f32 spFC;
    f32 spF8;
    char sp2C[204];

    D_807FBB60 &= ~0x10;
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    idx = func_800317E8(temp_a0, 160.0f, 15.0f, &spFC, &spF8, 4, 1, 0.3f);
    if (idx == 2) {
        _sprintf(sp2C, "%s", D_80033F28[5]);
    } else {
        if (idx == 3) {
            idx = 2;
        }
        if (menuCheckSaveFile(idx) != 0) {
            _sprintf(sp2C, "%s", D_80033F28[6]);
        } else {
            _sprintf(sp2C, "%s %d", D_80033F28[7], idx + 1);
        }
    }
    return hudDrawScaledText(arg1, spFC * 4.0f, spF8 * 4.0f, 0.6f, sp2C);
}

extern s8 D_8076A0D2;
extern u8 D_80720D14;
extern u8 D_807204BC;

void func_80028EA8(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;

    temp_s0->unk17 = D_8076A0D2;
    func_80030894(temp_s0, &D_80720C34, 0xA0, 0x78, 0.75f, 2, 4);
    if (menuCheckSaveFile(0) != 0) {
        D_80033F38 = 0;
    }
    func_80030894(temp_s0, (void *)(s32)&D_8072052C, 0, 0, 1.0f, 2, 2);
    if (menuCheckSaveFile(1) != 0) {
        D_80033F38 = 0;
    }
    func_80030894(temp_s0, (void *)(s32)&D_8072052C, 1, 0, 1.0f, 2, 2);
    if (menuCheckSaveFile(2) != 0) {
        D_80033F38 = 0;
    }
    func_80030894(temp_s0, (void *)(s32)&D_8072052C, 3, 0, 1.0f, 2, 2);
    func_80030894(temp_s0, &D_807204BC, 2, 0, 1.0f, 2, 2);
    func_80030894(temp_s0, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
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
            func_80609140(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
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

void menuHandleConfirmationInput(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;

    if (temp_s0->unk0 == 0.0f && temp_s0->unk4 == 0.0f) {
        if (arg1 & 1) {
            controllerSetActiveMask(1);
            func_807144B8(D_80033F48);
        } else if (arg1 & 2) {
            func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            temp_s0->unk16 = 0;
            temp_s0->unk13 = 2;
        }
    }
    menuUpdateItemTransition(arg0, temp_s0, 1);
}

#ifdef NON_MATCHING
extern s8 D_80033804;
extern s32 D_8003380C;
extern s32 D_80033810;
extern u32 D_80033814;
extern f32 D_80033F4C;
extern s8 D_80033F51;
extern u32 D_8076A064;
Gfx *menuSetElementCoordinates(Gfx *, s32, f32, f32, f32);
Gfx *renderRotatedSprite(Gfx *, u16, s32, s32, s32, s32, s16, s32, f32, f32, s32, f32);
f32 func_80612794(s16);

s32 menuDrawFileSummary(void *arg0, Gfx *arg1) {
    f32 x = 66.0f;
    s16 y;
    s16 py;
    void *temp_s4 = *(void **)((u8 *)arg0 + 0x174);
    s32 i = 0;
    s8 *p = &D_80033804;
    f32 sc = 3.0f;
    f32 four;
    f32 spCC;
    f32 spD0;
    char spA4[0x20];
    f32 fv1;

    do {
        func_800317E8(temp_s4, x, 85.0f, &spD0, &spCC, 4, 0, 1.5f);
        if (*p != 0) {
            arg1 = (Gfx *)menuSetElementCoordinates((s32)arg1, i, spD0, spCC, sc * 0.85);
        } else {
            arg1 = (Gfx *)menuSetElementCoordinates((s32)arg1, i | 0x80, spD0, spCC, sc);
        }
        i++;
        p++;
        x += 55.0f;
    } while (i != 5);
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    func_800317E8(temp_s4, 160.0f, 180.0f, &spD0, &spCC, 5, 1, 2.0f);
    four = 4.0f;
    D_80033F4C = spCC * four;
    y = D_80033F4C;
    y -= 0x140;
    _sprintf(spA4, "%d%%", D_80033F51);
    arg1 = (Gfx *)textDrawStringVtx((s32)arg1, 1, 0x280, y, spA4, 0x81);
    y += 0x8C;
    _sprintf(spA4, "%03d", D_8003380C);
    arg1 = (Gfx *)textDrawStringVtx((s32)arg1, 1, 0x280, y, spA4, 0x81);
    y += 0x8C;
    _sprintf(spA4, "%03d:%02d", D_80033810, D_80033814);
    arg1 = (Gfx *)textDrawStringVtx((s32)arg1, 1, 0x280, y, spA4, 0x81);
    fv1 = func_80612794((s16)((D_8076A064 * 0x78) & 0xFFF)) * 0.1f + 0.5f;
    y = (s32)((f32)y + 40.0f);
    sc = y;
    x = 0.5f * four;
    spCC = (sc * 0.25f + 32.0f * fv1) * four;
    spD0 = 85 * four;
    arg1 = renderRotatedSprite(arg1, 0xA1, 3, 0, 0x40, 0x40, (s32)spD0, (s32)spCC, x, -(fv1 * four), 0, 0.0f);
    gDPPipeSync(arg1++);
    spCC = sc;
    x = x * 0.75f;
    sc = -x;
    spD0 = 340.0f;
    arg1 = renderRotatedSprite(arg1, 0xA0, 3, 0, 0x20, 0x20, (s32)spD0, (s32)spCC, x, sc * 0.5f, D_8076A064 % 360U, 0.0f);
    gDPPipeSync(arg1++);
    arg1 = renderRotatedSprite(arg1, 0xA0, 3, 0, 0x20, 0x20, (s32)spD0, (s32)spCC, x, sc, (D_8076A064 * 0xC) % 360U, 0.0f);
    gDPPipeSync(arg1++);
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    func_800317E8(temp_s4, 160.0f, 15.0f, &spD0, &spCC, 5, 1, 0.3f);
    y = spD0 * four;
    py = spCC * four;
    _sprintf(spA4, "%s %d", (char *)D_80033F28[7], D_80033F48 + 1);
    return (s32)hudDrawScaledText(arg1, y, py, 0.6f, spA4);
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/menuDrawFileSummary.s")
#endif

s32 func_800297A8(s32 arg0) {
    return arg0 + 0x1EFF0;
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
void func_8060DC3C(s32, s32);
s32 menuCalculateGamePercentage(void);

#ifdef NON_MATCHING
extern s8 D_80033809;
void menuInitFileSummary(void *arg0, s32 arg1) {
    MenuScreenState *temp_s6 = *(MenuScreenState **)((u8 *)arg0 + 0x174);
    u8 *row = D_807FC950[0];
    s8 *p;
    s16 *q;
    s8 *p2;
    void *a1;
    u32 sp64;
    s32 i;
    s32 k;
    s32 j;

    func_80030894(temp_s6, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s6, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s6, &D_8072052C, 0x76, 0x91, 0.6f, 2, 9);
    D_80033F4C = 1600.0f;
    func_8060DC3C((u8)D_80033F48, 0);
    D_80033804 = 1;
    q = &D_807505B2;
    p = &D_80033805;
    do {
        k = flagGet(q[-1], 0);
        q++;
        *p++ = k;
    } while (p < &D_80033809);
    for (p2 = &D_80033804, i = 0; i != 5; i++) {
        if (*p2 != 0) {
            a1 = D_80750518[i];
        } else {
            a1 = &D_807211D0;
        }
        func_80030894(temp_s6, a1, i, i, 0.8f, 2, 0xF);
        p2++;
    }
    osPiReadIo(func_800297A8(0xAFFE1464), &sp64);
    if (func_800297A8(0x0107183B) != sp64) {
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
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/menuInitFileSummary.s")
#endif


void menuHandleFileSelectInput(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;

    if (temp_s0->unk0 == 0.0f) {
        if (temp_s0->unk4 == 0.0f) {
            if (arg1 & 1) {
                if (menuCheckSaveFile(temp_s0->unk17) == 0) {
                    temp_s0->unk16 = 0;
                    temp_s0->unk13 = 5;
                    D_80033F48 = temp_s0->unk17;
                } else {
                    func_80609140(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
            } else if (arg1 & 2) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 2;
            } else {
                menuHandleScrollInput(temp_s0, 3, arg1);
            }
        }
        menuUpdateScrollAnimation(temp_s0, 3);
    }
    menuUpdateItemTransition(arg0, temp_s0, 1);
}


#ifdef NON_MATCHING
Gfx *menuDrawFileSlotLabel(void *arg0, Gfx *arg1) {
    void *temp_a0 = *(void **)((u8 *)arg0 + 0x174);
    s32 sp120;
    Gfx *g;
    int ty;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    f32 sp100;
    s16 spFE;
    s16 y;
    char sp34[200];

    g = arg1++; g->words.w0 = 0xFA000000; g->words.w1 = -1;
    sp120 = func_800317E8(temp_a0, 160.0f, 25.0f, &sp110, &sp10C, 3, 1, 0.45f);
    spFE = (s16)(sp110 * 4.0f);
    y = (s16)(sp10C * 4.0f);
    if (menuCheckSaveFile(sp120) != 0) {
        _sprintf(sp34, "%s", (char *)D_80033F28[6]);
    } else {
        _sprintf(sp34, "%s %d", (char *)D_80033F28[7], sp120 + 1);
    }
    ty = (s16)(y - 0x3C);
    return hudDrawScaledText(
        hudDrawScaledText(arg1, spFE, y, 0.6f, sp34),
        (s16)(sp110 * 4.0f),
        (u16)ty,
        0.6f,
        (char *)D_80033F28[8]
    );
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/menuDrawFileSlotLabel.s")
#endif


void menuInitFileSelect(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;
    void *sp34;

    temp_s0->unk17 = 0;
    func_80030894(temp_s0, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    if (menuCheckSaveFile(0) != 0) {
        D_80033F38 = 0;
    }
    sp34 = (void *)(s32)&D_8072052C;
    func_80030894(temp_s0, sp34, 0, 0, 1.0f, 2, 3);
    if (menuCheckSaveFile(1) != 0) {
        D_80033F38 = 0;
    }
    func_80030894(temp_s0, sp34, 1, 0, 1.0f, 2, 3);
    if (menuCheckSaveFile(2) != 0) {
        D_80033F38 = 0;
    }
    func_80030894(temp_s0, sp34, 2, 0, 1.0f, 2, 3);
    func_80030894(temp_s0, &D_807204BC, 0xA0, 0x78, 1.0f, 2, 4);
    func_80030894(temp_s0, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
}

extern u8 D_8071FBC8;
extern u8 D_8071FE08;
void func_8071495C(void);
void *func_80714CC0(void *, f32, f32, f32, f32);
void func_8060C830(u8, s32);
extern s8 D_80033FAC;

void menuMysteryHandleInput(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;

    if (temp_s0->unk0 == 0.0f && temp_s0->unk4 == 0.0f) {
        if (arg1 & 1) {
            if ((arg1 & 8) && (D_80033FAC != 0)) {
                func_8071495C();
                func_80714CC0(&D_8071FBC8, 10.3f, 240.0f, 120.0f, -10.0f);
                func_8071495C();
                func_80714CC0(&D_8071FE08, 10.3f, 240.0f, 120.0f, -10.0f);
                func_80609140(0xF6, 0x7FFF, 63.0f, 1.0f, 0, 0);
                func_8060C830(D_80033F48, 1);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 2;
            } else if ((arg1 & 4) && (D_80033FAC != 0)) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 2;
            }
        } else if (arg1 & 2) {
            func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            temp_s0->unk16 = 0;
            temp_s0->unk13 = 2;
        }
    }
    menuUpdateItemTransition(arg0, temp_s0, 1);
}


#ifdef NON_MATCHING
Gfx *func_8002A088(void *arg0, Gfx *arg1) {
    void *temp_a0 = *(void **)((u8 *)arg0 + 0x174);
    int ty;
    f32 sp11C;
    Gfx *g;
    f32 sp120;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    s16 sp106;
    s16 y;
    char sp3C[200];

    g = arg1++; g->words.w0 = 0xFA000000; g->words.w1 = -1;
    func_800317E8(temp_a0, 160.0f, 25.0f, &sp118, &sp114, 5, 0, 0.45f);
    sp106 = (s16)(sp118 * 4.0f);
    y = (s16)(sp114 * 4.0f);
    if (menuCheckSaveFile(D_80033F48) != 0) {
        _sprintf(sp3C, "%s", (char *)D_80033F28[6]);
    } else {
        _sprintf(sp3C, "%s %d", (char *)D_80033F28[7], D_80033F48 + 1);
    }
    ty = (s16)(y - 0x3C);
    arg1 = hudDrawScaledText(hudDrawScaledText(arg1, sp106, y, 0.6f, sp3C), (s16)(sp118 * 4.0f), (u16)ty, 0.6f, (char *)D_80033F28[8]);
    func_800317E8(temp_a0, 160.0f, 80.0f, &sp118, &sp114, 5, 0, 2.0f);
    arg1 = hudDrawScaledText(arg1, (s16)(sp118 * 4.0f), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[9]);
    func_800317E8(temp_a0, 80.0f, 120.0f, &sp118, &sp114, 5, 0, 2.0f);
    return hudDrawScaledText(hudDrawScaledText(arg1, (s16)(sp118 * 4.0f), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[10]), (s16)(0x500 - (s32)(sp118 * 4.0f)), (s16)(sp114 * 4.0f), 0.6f, (char *)D_80033F28[11]);
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002A088.s")
#endif

extern s8 D_80033FAC;

void func_8002A36C(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;

    D_80033FAC = 0;
    temp_s0->unk17 = 0;
    func_80030894(temp_s0, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_807204BC, 0xA0, 0x80, 1.0f, 2, 8);
    func_80030894(temp_s0, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
}

extern s16 D_80033670;
extern s8 D_80033698;
extern s8 D_80744538;
extern s8 D_8076A104;

void menuBossReplayHandleInput(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;

    if (temp_s0->unk0 == 0.0f) {
        if (temp_s0->unk4 == 0.0f) {
            if (arg1 & 1) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 7;
            } else if (arg1 & 2) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 1;
                D_80033698 = 3;
            } else {
                menuHandleScrollInput(temp_s0, 2, arg1);
            }
            if (temp_s0->unk17 == 0) {
                if (!(D_80033670 & 0x10) && (arg1 & 0x10)) {
                    func_80609140(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    D_80744538++;
                    if (D_80744538 >= 3) {
                        D_80744538 = 0;
                    }
                } else if (!(D_80033670 & 0x20) && (arg1 & 0x20)) {
                    func_80609140(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    D_80744538--;
                    if (D_80744538 < 0) {
                        D_80744538 = 2;
                    }
                }
            }
        }
        menuUpdateScrollAnimation(temp_s0, 2);
    }
    D_8076A104 = temp_s0->unk17;
    menuUpdateItemTransition(arg0, temp_s0, 1);
}

Gfx *renderRotatedSprite(Gfx *, u16, s32, s32, s32, s32, s16, s32, f32, f32, s32, f32);
f32 func_80612790(s16);
f32 func_80612794(s16);

Gfx *menuDrawSubmenuRing(MenuScreenActor *arg0, Gfx *arg1) {
    MenuScreenState *temp_s2 = arg0->unk174;
    s32 padx;
    s32 idx;
    s32 i;
    s32 id;
    s32 ang;
    f32 sp174;
    f32 sp170;
    char sp98[0xD8];

    D_807FBB60 &= ~0x10;
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    idx = func_800317E8(temp_s2, 160.0f, 20.0f, &sp174, &sp170, 2, 1, 0.7f);
    arg1 = textDrawStringVtx(arg1, 1, sp174 * 4.0f, sp170 * 4.0f, D_80033F28[idx + 12], 0x81);
    if (idx == 0) {
        _sprintf(sp98, "%s %d", D_80033F28[14], D_80744538 + 1);
        func_800317E8(temp_s2, 160.0f, 207.0f, &sp174, &sp170, 2, 0, 0.7f);
        arg1 = hudDrawScaledText(arg1, sp174 * 4.0f, sp170 * 4.0f, 0.6f, sp98);
    }
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    for (i = 0; i != 0x1000; i += 0x800) {
        ang = i - (temp_s2->unk17 << 11);
        ang -= (s32)(temp_s2->unk4 * 2048.0);
        sp174 = 160.0 - func_80612794((s16)ang) * 50.0;
        sp170 = 120.0 - func_80612790((s16)ang) * 50.0;
        func_800317E8(temp_s2, sp174, sp170, &sp174, &sp170, 2, 0, 1.5f);
        sp174 += 12.0;
        sp174 *= 4.0f;
        sp170 += 28.0;
        sp170 *= 4.0f;
        if (i == 0) {
            id = D_80744538 + 0xB2;
        } else {
            id = 0xB1;
        }
        arg1 = renderRotatedSprite(
            renderRotatedSprite(arg1, id, 0, 2, 0x20, 0x40, sp174 - 96.0, sp170, 3.0f, -3.0f, 0, 0.0f),
            id + 4, 0, 2, 0x20, 0x40, sp174, sp170, 3.0f, -3.0f, 0, 0.0f);
    }
}

extern s8 D_8076A100[];
extern s8 D_8076A0E4[];
extern s8 D_8076A0E8[][4];

void menuAssignPlayerControllerSlot(s32 arg0, s32 arg1) {
    s8 temp_v0 = D_8076A0E4[arg0];
    s32 var_a2 = 0;
    s8 *temp_a3 = &D_8076A100[arg0];
    s8 temp_t0 = *temp_a3;
    s32 var_v0;

    if (temp_t0 >= 0) {
        D_8076A0E8[temp_v0][temp_t0] = -1;
    }
    for (var_v0 = 0; (var_v0 < 4) && (var_a2 == 0); var_v0++) {
        if (D_8076A0E8[arg1][var_v0] == -1) {
            var_a2 = 1;
            *temp_a3 = var_v0;
            D_8076A0E8[arg1][var_v0] = arg0;
        }
    }
    D_8076A0E4[arg0] = arg1;
}

void menuReleasePlayerControllerSlot(s32 arg0) {
    s8 temp_v0 = D_8076A0E4[arg0];
    s8 *temp_a1 = &D_8076A100[arg0];
    s8 temp_a2 = *temp_a1;

    if ((temp_a2 >= 0) && !(temp_v0 & 0x80)) {
        D_8076A0E8[temp_v0][temp_a2] = -1;
    }
    *temp_a1 = -1;
    D_8076A0E4[arg0] = -0x80;
}


extern s8 D_8076A0D6;

void menuInitControllerSlots(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;
    s32 i;
    s32 j;

    temp_s0->unk17 = D_8076A0D6;
    func_80030894(temp_s0, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720C34, 0xA0, 0x78, 0.75f, 2, 4);
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

s32 menuNextFreeControllerSlot(s32 arg0) {
    s8 temp_v0 = D_8076A0E4[arg0];
    s8 *row;
    s32 idx;
    s32 flag;

    idx = D_8076A100[arg0];
    flag = 0;
    row = D_8076A0E8[temp_v0];
    row[idx] = -1;
    do {
        idx += 1;
        if (idx >= 4) {
            idx = 0;
        }
        if (row[idx] == -1) {
            flag = 1;
            D_8076A100[arg0] = idx;
            row[idx] = arg0;
        }
    } while (flag == 0);
    return idx;
}

s32 menuPrevFreeControllerSlot(s32 arg0) {
    s8 temp_v0 = D_8076A0E4[arg0];
    s8 *row;
    s32 idx;
    s32 flag;

    idx = D_8076A100[arg0];
    flag = 0;
    row = D_8076A0E8[temp_v0];
    row[idx] = -1;
    do {
        idx -= 1;
        if (idx < 0) {
            idx = 3;
        }
        if (row[idx] == -1) {
            flag = 1;
            D_8076A100[arg0] = idx;
            row[idx] = arg0;
        }
    } while (flag == 0);
    return idx;
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/menuHandleControllerSlotInput.s")

extern f32 D_80033F44;
extern s8 D_80033FAD;
extern s8 D_80033850[];
extern s8 D_80744520;
extern s8 D_80744534;
extern s8 D_8076A0E5;
extern s8 D_8076A0E6;
extern s8 D_8076A0E7;
Gfx *menuSetElementCoordinates(Gfx *, s32, f32, f32, f32);

Gfx *func_8002B708(MenuScreenActor *arg0, Gfx *arg1) {
    MenuScreenState *sp164 = arg0->unk174;
    s32 padA0;
    s32 idx;
    s32 id;
    f32 sp154;
    f32 sp150;
    f64 sp40;
    s32 padB0;
    s32 padB1;
    s32 padB2;
    s16 pad13A;
    s16 sp138;
    char sp70[0xC8];
    f32 v;

    if (sp164->unkC > -239.0) {
        if (D_8076A0E5 & 0x80) {
            func_800317E8(sp164, 210.0f, 120.0f, &sp154, &sp150, 2, 0, 1.8f);
            arg1 = menuSetElementCoordinates(arg1, 0x81, sp154 + 8.0, sp150 + 32.0f, 3.0f);
        }
        if (D_8076A0E6 & 0x80) {
            func_800317E8(sp164, 160.0f, 170.0f, &sp154, &sp150, 2, 0, 1.8f);
            arg1 = menuSetElementCoordinates(arg1, 0x82, sp154 + 8.0, sp150 + 32.0f, 3.0f);
        }
        if (D_8076A0E7 & 0x80) {
            func_800317E8(sp164, 110.0f, 120.0f, &sp154, &sp150, 2, 0, 1.8f);
            arg1 = menuSetElementCoordinates(arg1, 0x83, sp154 + 8.0, sp150 + 32.0f, 3.0f);
        }
        gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
        func_800317E8(sp164, 160.0f, 25.0f, &sp154, &sp150, 2, 0, 0.6f);
        arg1 = textDrawStringVtx(arg1, 1, sp154 * 4.0f, sp150 * 4.0f, D_80033F28[D_8076A104 + 12], 0x81);
    }
    if (sp164->unkC < -1.0f && sp164->unkC > -479.0f) {
        gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
        func_800317E8(sp164, 160.0f, 30.0f, &sp154, &sp150, 2, 0, 1.5f);
        sp150 = sp150 + 240.0f;
        arg1 = textDrawStringVtx(arg1, 1, 0x280, sp150 * 4.0f, D_80033F28[15], 0x81);
        idx = sp164->unk17;
        if (sp164->unk4 != 0.0f) {
            if (sp164->unk4 > 0.5f) {
                idx++;
            }
            if (idx >= 4) {
                idx = 0;
            }
        }
        v = sp164->unk4 - 0.5f;
        if (v < 0.0f) {
            v = -v;
        }
        v = 0.5f - v;
        v = v * 700.0f;
        if (D_80033F44 < 0.0f) {
            v = -v;
        }
        sp40 = v;
        func_800317E8(sp164, sp40 + 160.0, 80.0f, &sp154, &sp150, 2, 0, 2.0f);
        sp150 = sp150 + 240.0f;
        arg1 = textDrawStringVtx(arg1, 1, sp154 * 4.0f, sp150 * 4.0f, D_80033F28[idx + 16], 0x81);
        func_800317E8(sp164, 160.0 - sp40, 160.0f, &sp154, &sp150, 2, 0, 1.5f);
        sp150 = sp150 + 240.0f;
        sp138 = (s16)(sp150 * 4.0f);
        switch (D_80033850[idx]) {
        case 0:
            if (D_80744520 >= 2) {
                _sprintf(sp70, "%d %s", D_80744520, D_80033F28[23]);
            } else {
                _sprintf(sp70, "%d %s", D_80744520, D_80033F28[22]);
            }
            break;
        case 1:
            if (D_80744520 >= 2) {
                _sprintf(sp70, "%d %s", D_80744520, D_80033F28[25]);
            } else {
                _sprintf(sp70, "%d %s", D_80744520, D_80033F28[24]);
            }
            break;
        case 2:
            if (D_80744520 >= 2) {
                _sprintf(sp70, "%d %s", D_80744520, D_80033F28[27]);
            } else {
                _sprintf(sp70, "%d %s", D_80744520, D_80033F28[26]);
            }
            break;
        case 3:
            _sprintf(sp70, "%d", D_80744520);
            break;
        }
        arg1 = textDrawStringVtx(arg1, 1, sp154 * 4.0f, sp138, sp70, 0x81);
    }
    if (sp164->unkC < -241.0f) {
        gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
        func_800317E8(sp164, 160.0f, 40.0f, &sp154, &sp150, 2, 0, 1.5f);
        sp150 = sp150 + 480.0f;
        arg1 = textDrawStringVtx(arg1, 1, 0x280, sp150 * 4.0f, D_80033F28[28], 0x81);
        func_800317E8(sp164, 160.0f, 180.0f, &sp154, &sp150, 2, 0, 1.5f);
        sp150 = (sp150 + 480.0f) * 4.0f;
        sp154 = (sp154 + 16.0f) * 4.0f;
        id = D_80033FAD * 6 + D_80744534 * 2 + 0x98;
        gDPPipeSync(arg1++);
        gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
        arg1 = renderRotatedSprite(arg1, id, 0, 2, 0x20, 0x40, sp154 - 128.0, sp150, 4.0f, -4.0f, 0, 0.0f);
        gDPPipeSync(arg1++);
        arg1 = renderRotatedSprite(arg1, ++id, 0, 2, 0x20, 0x40, sp154, sp150, 4.0f, -4.0f, 0, 0.0f);
    }
    return arg1;
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

void func_8002C0C8(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s6 = arg0->unk174;
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
    temp_s6->unk17 = D_8074451C;
    do {
        actorSpawn(0x151, D_8003386C[D_8076A0E4[i] & 0x7F]);
        {
            s16 *q = D_807FBB44->unk17C;
            *q = D_8003386C[D_8076A0E4[i] & 0x7F];
        }
        D_807FBB44->unk154 = i;
        i += 1;
        D_807FBB44->unk155 = D_8076A0E4[i - 1] & 0x7F;
        sub = D_807FBB44->unk174;
        sub->unk0 = arg0;
        sub->unk8 = 0;
    } while (i != 4);
    func_80030894(temp_s6, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s6, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s6, &D_80720C34, 0xA0, 0x7D, 0.75f, 2, 4);
    func_80030894(temp_s6, &D_80720D80, 0xA0, 0x10, 0.5f, 2, 0);
    func_80030894(temp_s6, &D_807211AC, 0xA0, 0xDC, 0.75f, 2, 0);
    func_80030894(temp_s6, &D_807211D0, 1, 1, 0.8f, 2, 0xF);
    func_80030894(temp_s6, &D_807211D0, 2, 2, 0.8f, 2, 0xF);
    func_80030894(temp_s6, &D_807211D0, 3, 3, 0.8f, 2, 0xF);
    func_80030894(temp_s6, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0xB);
    func_80030894(temp_s6, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0xB);
    func_80030894(temp_s6, &D_80720C34, 0xA0, 0x16D, 0.75f, 2, 4);
    func_80030894(temp_s6, &D_80720D5C, 0xA0, 0xDC, 0.5f, 2, 0xB);
    func_80030894(temp_s6, &D_80720D80, 0xA0, 0x10, 0.5f, 2, 0x13);
    func_80030894(temp_s6, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0xD);
    func_80030894(temp_s6, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0xD);
    func_80030894(temp_s6, &D_80720C34, 0xA0, 0x23F, 0.75f, 2, 4);
    func_80030894(temp_s6, &D_80720D5C, 0xA0, 0xDC, 0.5f, 2, 0xD);
}


void func_8002C584(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;

    if (temp_s0->unk0 == 0.0 && (arg1 & 1)) {
        func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
        temp_s0->unk16 = 0;
        temp_s0->unk13 = 7;
    }
    menuUpdateItemTransition(arg0, temp_s0, 0);
    menuUpdateCameraPositions();
    D_807FBB60 &= ~0x10;
    D_807FBB60 |= 0x10000;
}

#ifdef NON_MATCHING
extern u8 D_80033878;
extern u8 D_80033F20[];
extern s16 D_80744524[];
extern s8 D_8076A105;

s32 func_8002C634(arg0, arg1)
void *arg0;
Gfx *arg1;
{
    void *temp_s0;
    s32 step;
    s32 i;
    s16 x;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    u8 *q;
    s16 y;
    s16 sp12C;
    char sp64[200];
    s32 sel;

    temp_s0 = *(void **)((u8 *)arg0 + 0x174);
    gDPSetPrimColor(arg1++, 0, 0, 255, 255, 255, 255);
    func_800317E8(temp_s0, 160.0f, 45.0f, &sp13C, &sp138, 2, 0, 1.8f);
    func_800317E8(temp_s0, 160.0f, 185.0f, &sp13C, &sp134, 2, 0, 1.8f);
    y = (s32)(sp138 * 4.0);
    sp12C = (s32)(sp134 * 4.0);
    step = 0x11D / D_80033878;
    x = step * 2 + 0x46;
    step *= 4;
    q = D_80033F20;
    i = 0;
    if (D_80033878 > 0) {
        do {
            _sprintf(sp64, "P %d", *q + 1);
            arg1 = hudDrawScaledText(arg1, x, y, 0.6f, sp64);
            sel = i == D_8076A105;
            arg1 = hudDrawScaledText(arg1, x, (s16)(y + 0x30), 0.6f, (char *)D_80033F28[0x1D + sel]);
            _sprintf(sp64, "%d", D_80744524[*q]);
            arg1 = hudDrawScaledText(arg1, x, sp12C, 0.6f, sp64);
            i += 1;
            q += 1;
            x += step;
        } while (i < D_80033878);
    }
    return (s32)hudDrawScaledText(arg1, 0x280, (s16)(sp12C - 0x50), 0.6f, (char *)D_80033F28[0x1F]);
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002C634.s")
#endif

extern u8 D_80033878;
extern u8 D_80033F20[];
extern s16 D_80744524[];
extern s8 D_8076A105;
extern u8 D_8003387C[];
extern u8 D_80033F24[];

void func_8002C91C(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *sp4C = arg0->unk174;
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
    sp4C->unk17 = 0;
    for (i = 0; i < D_80033878; i++) {
        actorSpawn(0x151, D_8003386C[D_8003387C[i]]);
        {
            s16 *q = D_807FBB44->unk17C;
            *q = D_8003386C[D_8003387C[i]];
        }
        D_807FBB44->unk154 = D_80033F20[i] | 0x80;
        D_807FBB44->unk155 = D_8003387C[i];
        sub = D_807FBB44->unk174;
        sub->unk0 = arg0;
        sub->unk8 = (i == D_8076A105) + 1;
    }
    func_80030894(sp4C, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
}

#ifdef NON_MATCHING
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
#define Menu6B_A ((Menu6B_Actor *)D_807FBB40)
#define Menu6B_N ((Menu6B_Actor *)D_807FBB44)
extern s32 D_800338B4[];
extern Menu6B_Pair D_80033894[];
void actorScriptStart(void *, s32);
void actorDespawn(void *);
void actorUpdateModelMatrix(void *, s32);
void func_806BF920(void);
void func_806F0C18(void *);
void func_8068A4C8(void *, s32, s32);

void func_8002CB18(void) {
    s32 temp_s1_2;
    Menu6B_Pair *row;
    f32 *sp5C;
    s32 sel;
    f32 sp54;
    f32 sp50;
    s8 sp4F;
    s16 idx;
    s32 a2;
    s16 *sp38;
    Menu6B_Sub174 *temp_s1;
    s8 m8;

    temp_s1 = Menu6B_A->unk174;
    sp5C = temp_s1->unk0->unk174;
    sp4F = 0;
    func_806BF920();
    if (!(Menu6B_A->unk60 & 0x10)) {
        Menu6B_A->unk4->unk34 = 2.0f * Menu6B_A->unk4->unk34;
        Menu6B_A->unk4->unk38 = 2.0f * Menu6B_A->unk4->unk38;
        Menu6B_A->unk4->unk3C = 2.0f * Menu6B_A->unk4->unk3C;
        m8 = temp_s1->unk8;
        actorScriptStart(Menu6B_A, D_800338B4[(s16)(m8 * 6) + (Menu6B_A->unk155 & 0xF)]);
        func_806F0C18(Menu6B_A);
        Menu6B_A->unk60 |= 0x1000;
        temp_s1->unk4 = D_8076A100[Menu6B_A->unk154 & 0xF];
        func_8068A4C8(Menu6B_A, Menu6B_A->unk155 + 2, D_8076A100[Menu6B_A->unk154 & 0xF]);
    }
    sel = Menu6B_A->unk154;
    if (!(Menu6B_A->unk154 & 0x80)) {
        if (temp_s1->unk4 != a2) {
            func_8068A4C8(Menu6B_A, Menu6B_A->unk155 + 2, a2);
            temp_s1->unk4 = D_8076A100[Menu6B_A->unk154];
        a2 = D_8076A100[Menu6B_A->unk154];
        }
        idx = D_8076A0E4[Menu6B_A->unk154] & 0x7F;
        if (idx != Menu6B_A->unk155) {
            sp38 = &D_8003386C[idx];
            actorSpawn(0x151, *sp38);
            *Menu6B_N->unk17C = *sp38;
            Menu6B_N->unk154 = Menu6B_A->unk154;
            Menu6B_N->unk155 = idx;
            *(Menu6B_Actor **)Menu6B_N->unk174 = temp_s1->unk0;
            sp4F = 1;
        }
        row = &D_80033894[Menu6B_A->unk154];
        func_800317E8(sp5C, row->a, row->b, &sp54, &sp50, 2, 0, 1.8f);
        Menu6B_A->unk7C = D_807FBB4C->unk7C + (sp54 - 160.0f);
        Menu6B_A->unk80 = (D_807FBB4C->unk80 - (sp50 - 120.0f)) - 20.0f;
        Menu6B_A->unk84 = D_807FBB4C->unk84 - 300.0f;
        if (D_8076A0E4[Menu6B_A->unk154] & 0x80) {
            Menu6B_A->unk60 &= ~4;
        } else {
            Menu6B_A->unk60 |= 4;
        }
    } else {
        idx = D_80033F24[sel & 0xF];
        temp_s1_2 = 0x140 / D_80033878;
        func_800317E8(sp5C, 160.0f, 150.0f, &sp54, &sp50, 2, 0, 1.8f);
        sp54 = (idx * temp_s1_2 + (temp_s1_2 >> 1)) - 0xA0;
        sp54 = sp54 * 0.78;
        Menu6B_A->unk7C = D_807FBB4C->unk7C + sp54;
        Menu6B_A->unk80 = (D_807FBB4C->unk80 - (sp50 - 120.0f)) + 16.0f;
        Menu6B_A->unk84 = D_807FBB4C->unk84 - 300.0f;
    }
    if (*sp5C > 1.0f) {
        sp4F = 1;
    }
    if (sp4F != 0) {
        actorDespawn(Menu6B_A);
    }
    actorUpdateModelMatrix(Menu6B_A, 0);
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8002CB18.s")
#endif

extern s8 D_8074583C;
extern s8 D_80745840;
void n_alSndpSetGroupVol(u8, u16);
void seqUpdateVolume(s32);
s32 func_8060C648(s32, s32, u8, s32, s32);
void func_8060DEA8(void);

void menuHandleSoundOptionsInput(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;
    s8 flag = 0;

    menuCheckCheatCodeSequence();
    if (temp_s0->unk0 == 0.0f) {
        if (temp_s0->unk4 == 0.0f) {
            switch (temp_s0->unk17) {
            case 0:
                if (!(D_80033670 & 0x10) && (arg1 & 0x10)) {
                    D_80745844++;
                    if (D_80745844 >= 3) {
                        D_80745844 = 0;
                    }
                    flag = 1;
                } else if (!(D_80033670 & 0x20) && (arg1 & 0x20)) {
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
                if (arg1 & 0x10) {
                    D_8074583C++;
                    func_80609140(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    if (D_8074583C > 0x28) {
                        D_8074583C = 0x28;
                    }
                } else if (arg1 & 0x20) {
                    D_8074583C--;
                    func_80609140(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
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
                if (arg1 & 0x10) {
                    D_80745840++;
                    if (D_80745840 > 0x28) {
                        D_80745840 = 0x28;
                    }
                } else if (arg1 & 0x20) {
                    D_80745840--;
                    if (D_80745840 < 0) {
                        D_80745840 = 0;
                    }
                }
                seqUpdateVolume(0);
                seqUpdateVolume(2);
                break;
            case 3:
                if (arg1 & 0x100) {
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
            if (arg1 & 2) {
                if (func_8060C6B8(0x1E, 0, 0, 0) != D_80745844) {
                    func_8060C648(0x1E, 0, 0, 0, D_80745844);
                    func_8060DEA8();
                }
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s0->unk16 = 0;
                temp_s0->unk13 = 1;
            } else {
                menuHandleScrollInput(temp_s0, 4, arg1);
            }
        }
        menuUpdateScrollAnimation(temp_s0, 4);
    }
    menuUpdateItemTransition(arg0, temp_s0, 1);
    if (flag != 0) {
        func_80609140(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
}

extern s16 D_80033674;
extern s8 D_80745844;
Gfx *menuDrawScrollSelector(Gfx *, MenuScreenState *, char **, s32, u32 *, s16, f32 *, f32, s16);

Gfx *menuFormatOptionValues(MenuScreenActor *arg0, Gfx *arg1) {
    void *sp64;
    u32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s16 pad;
    s16 sp4C;
    char sp40[12];

    sp64 = arg0->unk174;
    D_807FBB60 &= ~0x10;
    func_800317E8(sp64, 160.0f, 20.0f, &sp58, &sp54, 2, 0, 1.5f);
    arg1 = menuDrawScrollSelector(
        textDrawStringVtx(arg1, 1, 0x280, sp54 * 4.0f, D_80033F28[0x20], 0x81),
        sp64,
        D_80033F28 + 0x21,
        4,
        &sp60,
        1,
        &sp50,
        80.0f,
        -1
    );
    D_80033674 = 0x3E8;
    func_800317E8(sp64, 160.0f, 150.0f, &sp58, &sp54, 2, 0, 1.5f);
    sp4C = (s16)(sp54 * 4.0f);
    sp58 = (sp58 - sp50) * 4.0f;

    switch (sp60) {
    case 0:
        arg1 = textDrawStringVtx(arg1, 1, sp58, sp4C, D_80033F28[D_80745844 + 0x25], 0x81);
        break;
    case 1:
    case 2:
        arg1 = textDrawStringVtx(arg1, 1, sp58, sp4C, D_80033F28[0x28], 0x81);
        _sprintf(sp40, "%d", ((sp60 == 1 ? D_8074583C : D_80745840) + 1) >> 1);
        arg1 = textDrawStringVtx(arg1, 1, sp58, sp4C + 0x78, sp40, 0x81);
        break;
    case 3:
        D_80033674 = 0;
        break;
    }

    return arg1;
}

extern u8 D_80720D38;

void func_8002D7EC(MenuScreenActor *arg0, s32 arg1) {

    MenuScreenState *temp_a0 = arg0->unk174;
    temp_a0->unk17 = 0;
    func_80030894(temp_a0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_a0, &D_80720C34, 0xA0, 0x7D, 0.75f, 2, 4);
    func_80030894(temp_a0, &D_80720D38, 0xA0, 0xC8, 1.0f, 2, 0xC);
}

extern s8 D_800338FC;
extern s8 D_807444C0;
extern s8 D_8074452C;
extern u8 D_80744530;
extern u8 D_807550C8;
extern u16 D_807ECD66;
void heapFreeDeferred(void *);
void func_8060C8AC(s32);
void menuLoadTextTable(void);

void func_8002D8AC(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s1 = arg0->unk174;
    s8 flag = 0;
    s32 i;

    if (temp_s1->unk0 == 0.0f) {
        if (temp_s1->unk4 == 0.0f) {
            switch (temp_s1->unk17) {
            case 0:
                if ((arg1 & 0x30) && !(D_80033670 & 0x30)) {
                    D_807444C0 = 1 - D_807444C0;
                    flag = 1;
                }
                break;
            case 1:
                if ((arg1 & 0x30) && !(D_80033670 & 0x30)) {
                    D_8074452C = 1 - D_8074452C;
                    flag = 1;
                }
                break;
            case 2:
                if (arg1 & 0x100) {
                    func_8060C8AC(0xFF);
                    func_80609140(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
                break;
            case 3:
                if ((arg1 & 0x30) && !(D_80033670 & 0x30)) {
                    D_80744530 = 1 - D_80744530;
                    flag = 1;
                }
                break;
            case 4:
                if ((arg1 & 0x10) && !(D_80033670 & 0x10)) {
                    D_807550C8 += 1;
                    flag = 1;
                }
                if ((arg1 & 0x20) && !(D_80033670 & 0x20)) {
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
            if (arg1 & 2) {

                func_8060C648(0x1F, 0, 0, 0, D_807550C8);
                func_8060C648(0x20, 0, 0, 0, D_80744530);
                func_8060DEA8();
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s1->unk16 = 0;
                temp_s1->unk13 = 1;
            } else {
                menuHandleScrollInput(temp_s1, D_800338FC, arg1);
            }
        }
        menuUpdateScrollAnimation(temp_s1, D_800338FC);
    }
    menuUpdateItemTransition(arg0, temp_s1, 1);
    if (D_807ECD66 & 0xC) {
        D_80744544 ^= 0x100;
    }
    if (flag != 0) {
        func_80609140(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
}


extern s16 D_80033674;

Gfx *func_8002DBDC(MenuScreenActor *arg0, Gfx *arg1) {
    void *sp6C = arg0->unk174;
    u32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 pad4;
    s32 pad5;
    s16 y;

    D_807FBB60 &= ~0x10;
    func_800317E8(sp6C, 160.0f, 20.0f, &sp64, &sp60, D_800338FC, 0, 1.5f);
    arg1 = menuDrawScrollSelector(
        textDrawStringVtx(arg1, 1, 0x280, sp60 * 4.0f, D_80033F28[0x29], 0x81),
        sp6C,
        D_80033F28 + 0x2A,
        D_800338FC,
        &sp68,
        1,
        &sp5C,
        80.0f,
        -1
    );
    D_80033674 = 0x3E8;
    func_800317E8(sp6C, 160.0f, 150.0f, &sp64, &sp60, 2, 0, 1.5f);
    y = (s16)(sp60 * 4.0f);
    sp64 = (sp64 - sp5C) * 4.0f;

    switch (sp68) {
    case 0:
        arg1 = textDrawStringVtx(arg1, 1, sp64, y + 0x40, D_80033F28[D_807444C0 + 0x2F], 0x81);
        break;
    case 1:
        arg1 = textDrawStringVtx(arg1, 1, sp64, y + 0x40, D_80033F28[D_8074452C + 0x31], 0x81);
        break;
    case 2:
        D_80033674 = 0;
        break;
    case 3:
        arg1 = textDrawStringVtx(arg1, 1, sp64, y + 0x40, D_80033F28[D_80744530 + 0x34], 0x81);
        break;
    case 4:
        arg1 = textDrawStringVtx(arg1, 1, sp64, y + 0x40, D_80033F28[0x33], 0x81);
        break;
    }

    return arg1;
}

void func_8002DEE8(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_a0 = arg0->unk174;
    temp_a0->unk17 = 0;
    func_80030894(temp_a0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_a0, &D_80720C34, 0xA0, 0x7D, 0.75f, 2, 4);
    func_80030894(temp_a0, &D_80720D38, 0xA0, 0xC8, 1.0f, 2, 0xC);
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

void func_8002DFA8(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s1 = arg0->unk174;
    s8 flag = 0;
    s8 cnt;
    s8 sel;
    s8 idx;
    s8 *p;

    if (temp_s1->unk0 == 0.0f) {
        if (temp_s1->unk4 == 0.0f) {
            idx = temp_s1->unk17;
            cnt = D_80033988[idx];
            if (cnt > 0) {
                if ((arg1 & 0x10) && !(D_80033670 & 0x10) && cnt != 1) {
                    flag = 1;
                    do {
                        D_8074453C[idx] += 1;
                        if (D_8074453C[idx] >= cnt) {
                            D_8074453C[idx] = 0;
                        }
                    } while (!(D_80033998[idx] & (1 << D_8074453C[idx])));
                }
                if ((arg1 & 0x20) && !(D_80033670 & 0x20) && cnt != 1) {
                    do {
                        D_8074453C[idx] -= 1;
                        if (D_8074453C[idx] < 0) {
                            D_8074453C[idx] = cnt - 1;
                        }
                    } while (!(D_80033998[idx] & (1 << D_8074453C[idx])));
                    flag = 1;
                }
                sel = D_8074453C[idx];
                if (arg1 & 1) {
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
                            func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                            temp_s1->unk16 = 0;
                            temp_s1->unk13 = 0xC;
                            D_800339A8 = 0;
                            break;
                        case 0xB8:
                            func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                            temp_s1->unk16 = 0;
                            temp_s1->unk13 = 0xC;
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
                if (arg1 & 0x100) {
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
            if (arg1 & 2) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                temp_s1->unk16 = 0;
                temp_s1->unk13 = 1;
                D_80033698 = 3;
            } else {
                menuHandleScrollInput(temp_s1, 5, arg1);
            }
        }
        menuUpdateScrollAnimation(temp_s1, 5);
    }
    menuUpdateItemTransition(arg0, temp_s1, 1);
    if (flag != 0) {
        func_80609140(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
}

extern s8 D_80033990[];
extern s16 D_800339A4;
extern s8 D_8074453D;
extern s8 D_8074453E;

Gfx *func_8002E420(MenuScreenActor *arg0, Gfx *arg1) {
    void *sp11C = arg0->unk174;
    u32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    s16 sel;
    s16 y;
    char sp40[0xC8];

    D_807FBB60 &= ~0x10;
    func_800317E8(sp11C, 160.0f, 20.0f, &sp114, &sp110, 2, 0, 1.5f);
    y = (s16)(sp110 * 4.0f);
    arg1 = menuDrawScrollSelector(
        textDrawStringVtx(arg1, 1, 0x280, y, D_80033F28[0x36], 0x81),
        sp11C,
        D_80033F28 + 0x37,
        5,
        &sp118,
        1,
        &sp10C,
        140.0f,
        D_800339A4
    );
    _sprintf(sp40, "%d", D_80033990[sp118]);
    arg1 = textDrawStringVtx(arg1, 3, 0x2A8, y + 0xC8, sp40, 1);
    D_80033674 = 0x3E8;
    func_800317E8(sp11C, 160.0f, 160.0f, &sp114, &sp110, 1, 0, 1.5f);
    y = (s16)(sp110 * 4.0f);
    sp114 = (sp114 - sp10C) * 4.0f;

    if (D_80033988[sp118] > 0) {
        switch (sp118) {
        case 0:
            arg1 = textDrawStringVtx(arg1, 1, sp114, y + 0x40, D_80033F28[D_8074453C[0] + 0x3C], 0x81);
            break;
        case 1:
            arg1 = textDrawStringVtx(arg1, 1, sp114, y + 0x40, D_80033F28[D_8074453D + 0x52], 0x81);
            break;
        case 2:
            arg1 = textDrawStringVtx(arg1, 1, sp114, y + 0x40, D_80033F28[D_8074453E + 0x4A], 0x81);
            break;
        case 3:
            _sprintf(sp40, "%s:%s", D_80033F28[0x5E], D_80033F28[(D_80744544 & 1) + 0x31]);
            arg1 = textDrawStringVtx(arg1, 1, sp114, y + 0x40, sp40, 0x81);
            break;
        case 4:
            sel = D_80744540;
            _sprintf(sp40, "%s:%s", D_80033F28[sel + 0x56], D_80033F28[(((1 << (sel + 1)) & D_80744544) != 0) + 0x31]);
            arg1 = textDrawStringVtx(arg1, 1, sp114, y + 0x40, sp40, 0x81);
            break;
        }
    } else {
        arg1 = textDrawStringVtx(arg1, 1, sp114, y + 0x40, "???", 0x81);
    }
    return arg1;
}

extern s8 D_8076A0DA;


void func_8002E8B8(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *temp_s0 = arg0->unk174;
    s32 j;
    s32 i;
    s8 n;

    temp_s0->unk17 = D_8076A0DA;
    switch (D_80744514) {
    case 0:
        break;
    default:
        temp_s0->unk17 = 0;
        break;
    case 4:
        temp_s0->unk17 = 2;
        break;
    case 5:
        temp_s0->unk17 = 1;
        break;
    }
    func_80030894(temp_s0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720C34, 0xA0, 0x78, 0.75f, 2, 4);
    func_80030894(temp_s0, &D_80721094, 0x78, 0x50, 1.25f, 2, 0xE);
    func_80030894(temp_s0, &D_80720D38, 0x11D, 0xD2, 0.75f, 2, 0x11);
    func_80030894(temp_s0, &D_80720CF0, 0x11D, 0xD2, 0.75f, 2, 0x10);
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
        D_80744548[i].unk0 = func_8060C6B8(0x19, 0, i, 0);
        D_80744548[i].unk2 = func_8060C6B8(0x16, 0, i, 0);
        D_80744548[i].unk3 = func_8060C6B8(0x17, 0, i, 0);
        D_80744548[i].unk4 = func_8060C6B8(0x18, 0, i, 0);
        D_80744548[i].unk5 = 0;
        D_80744568[i].unk0 = func_8060C6B8(0x1D, 0, i, 0);
        D_80744568[i].unk2 = func_8060C6B8(0x1A, 0, i, 0);
        D_80744568[i].unk3 = func_8060C6B8(0x1B, 0, i, 0);
        D_80744568[i].unk4 = func_8060C6B8(0x1C, 0, i, 0);
        D_80744568[i].unk5 = 0;
    }
}

void menuSaveHighScores(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        func_8060C648(0x19, 0, i, 0, D_80744548[i].unk0);
        func_8060C648(0x16, 0, i, 0, D_80744548[i].unk2);
        func_8060C648(0x17, 0, i, 0, D_80744548[i].unk3);
        func_8060C648(0x18, 0, i, 0, D_80744548[i].unk4);
        func_8060C648(0x1D, 0, i, 0, D_80744568[i].unk0);
        func_8060C648(0x1A, 0, i, 0, D_80744568[i].unk2);
        func_8060C648(0x1B, 0, i, 0, D_80744568[i].unk3);
        func_8060C648(0x1C, 0, i, 0, D_80744568[i].unk4);
    }
    func_8060DEA8();
}

#ifdef NON_MATCHING
typedef struct MenuM8_PosPair {
    s16 unk0;
    s16 unk2;
} MenuM8_PosPair;

extern s8 D_80033F60;
extern s8 D_800339A8;
extern s8 D_80033F61;
extern s8 D_800339C0;
extern u32 D_8076A064;
extern MenuM8_PosPair D_800339B8[];

void menuHandleHighScoreNameEntryInput(void *arg0, s32 arg1) {
    MenuScreenState *sp2C = *(MenuScreenState **)((u8 *)arg0 + 0x174);
    MenuHighScoreEntry *table;
    s8 v1;
    s32 v0;
    u8 *p;

    if (D_800339A8 == 0) {
        table = D_80744548;
    } else {
        table = D_80744568;
    }

    if (sp2C->unk0 == 0.0f) {
        if (D_80033F60 < 0) {
            if (arg1 & 1) {
                func_807126B0(D_800339B8[D_800339A8].unk0, 0, D_800339B8[D_800339A8].unk2, 3, 3, 1, 3);
                D_80744514 = D_800339A8 + 6;
            }
            if (arg1 & 2) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                sp2C->unk16 = 0;
                sp2C->unk13 = 0xA;
            }
        } else {
            if (arg1 & 0xC) {
                v1 = D_800339C0 + 1;
            } else {
                v1 = 0;
            }
            v0 = 0;
            D_800339C0 = v1;
            if (v1 == 1 || v1 >= 0x10) {
                v0 = arg1;
                if (v1 >= 0x10) {
                    D_800339C0 = 0xF;
                    if (!(D_8076A064 & 1)) {
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
            if (arg1 & 1) {
                D_80033F61 += 1;
                if (D_80033F61 == 3) {
                    D_80033F60 = -1;
                    func_80030894(sp2C, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
                    func_80030894(sp2C, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
                    menuSaveHighScores();
                }
            } else if ((arg1 & 2) && D_80033F61 > 0) {
                D_80033F61 -= 1;
            }
        }
    }
    menuUpdateItemTransition(arg0, sp2C, 1);
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/menuHandleHighScoreNameEntryInput.s")
#endif

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/D_80033BE0.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/D_80033BE4.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/D_80033BE8.s")

#ifdef NON_MATCHING
extern s8 D_80033F60;
extern s8 D_80033F61;
extern s16 D_80744518;
extern char *D_800339AC[];
extern u32 D_8076A064;

s32 menuDrawHighScoreTable(void *arg0, s32 arg1) {
    void *temp_s0;
    f32 sp140;
    f32 sp13C;
    s32 ft4;
    MenuHighScoreEntry *e;
    MenuHighScoreEntry *sp130;
    char sp68[0xC8];
    s16 var_s3;
    s16 i;

    temp_s0 = *(void **)((u8 *)arg0 + 0x174);
    D_807FBB60 &= ~0x10;
    func_800317E8(temp_s0, 160.0f, 20.0f, &sp140, &sp13C, 2, 0, 1.0f);
    arg1 = textDrawStringVtx(arg1, 1, 0x280, (s16)(sp13C * 4.0), ((void **)D_80033F28)[D_800339A8 + 0x5F], 0x81);
    func_800317E8(temp_s0, 160.0f, 205.0f, &sp140, &sp13C, 2, 0, 1.0f);
    i = 0;
    var_s3 = (s16)(sp13C * 4.0);
    if (D_80033F60 >= 0) {
        _sprintf(sp68, "%s", ((void **)D_80033F28)[0x63]);
        i = 1;
    } else if (D_80033F60 == -2) {
        _sprintf(sp68, "%s %d.", ((void **)D_80033F28)[0x64], D_80744518);
        i = 1;
    }
    if (i != 0) {
        arg1 = (s32)hudDrawScaledText((Gfx *)arg1, 0x280, var_s3, 0.6f, sp68);
    }
    i = 0;
    func_800317E8(temp_s0, 20.0f, 120.0f, &sp140, &sp13C, 2, 0, 2.0f);
    var_s3 = 0xC8;
    ft4 = (s16)(s32)(sp140 * 4.0f);
    if (D_800339A8 == 0) {
        sp130 = D_80744548;
    } else {
        sp130 = D_80744568;
    }
    do {
        _sprintf(sp68, "%d.", i + 1);
        e = (MenuHighScoreEntry *)((u8 *)sp130 + i * 6);
        arg1 = textDrawStringVtx(arg1, 1, (s16)(ft4 + 0x50), var_s3, sp68, 1);
        _sprintf(sp68, "%c %c %c", e->unk2, e->unk3, e->unk4);
        arg1 = textDrawStringVtx(arg1, 0x81, (s16)(ft4 + 0x118), var_s3, sp68, 1);
        _sprintf(sp68, "%d", e->unk0);
        arg1 = textDrawStringVtx(arg1, 0x81, (s16)(0x3E8 - ft4), var_s3, sp68, 1);
        if (i == D_80033F60 && (D_8076A064 & 0x1F) < 0x14) {
            arg1 = textDrawStringVtx(arg1, 0x81, (s16)(ft4 + 0x118), var_s3 + 0x34, D_800339AC[D_80033F61], 1);
        }
        var_s3 += 0x6C;
    } while (++i < 5);
    return arg1;
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/menuDrawHighScoreTable.s")
#endif

extern s8 D_80033F60;

void func_8002F6C8(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *sp2C = arg0->unk174;

    if (D_80033F60 == -1) {
        func_80030894(sp2C, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
        func_80030894(sp2C, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
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

extern Menu3B_Struct_C924 *D_807FC924;

void menuUpdateCameraPositions(void) {
    D_807FC924->unk210 = D_807FBB4C->unk7C;
    D_807FC924->unk214 = D_807FBB4C->unk80 + 13.1f;
    D_807FC924->unk218 = D_807FBB4C->unk84 - 50.0f;
    D_807FC924->unk228 = D_807FBB4C->unk7C;
    D_807FC924->unk22C = D_807FC924->unk214;
    D_807FC924->unk230 = D_807FBB4C->unk84 - 100.0f;
}

extern char D_800339C4[];
extern f32 D_80033F44;

Gfx *menuDrawScrollSelector(Gfx *arg0, MenuScreenState *arg1, char **arg2, s32 arg3, u32 *arg4, s16 arg5, f32 *arg6, f32 arg7, s16 arg8) {
    s32 idx = arg1->unk17;
    f32 v;
    f32 sp3C;
    f32 sp38;
    s16 y;

    if (arg1->unk4 != 0.0f) {
        if (arg1->unk4 > 0.5f) {
            idx++;
        }
        if (idx >= arg3) {
            idx = 0;
        }
    }
    v = arg1->unk4 - 0.5f;
    if (v < 0.0f) {
        v = -v;
    }
    v = 0.5f - v;
    v = v * 800.0f;
    if (D_80033F44 < 0.0f) {
        v = -v;
    }
    func_800317E8(arg1, v + 160.0, arg7, &sp3C, &sp38, 2, 0, 2.0f);
    y = (s16)(sp38 * 4.0f);
    if (arg8 & (1 << idx)) {
        arg0 = textDrawStringVtx(arg0, arg5, sp3C * 4.0f, y, arg2[idx], 0x81);
    } else {
        arg0 = textDrawStringVtx(arg0, arg5, sp3C * 4.0f, y, D_800339C4, 0x81);
    }
    *arg6 = v;
    *arg4 = idx;
    return arg0;
}

extern f32 D_80033F68[];
extern f32 D_80033F80[];
extern f32 D_80033F98[];

Gfx *menuSetElementCoordinates(Gfx *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    arg1 &= 0x7F;
    arg2 *= 4.0f;
    arg3 *= 4.0f;
    D_80033F68[arg1] = arg2 - 32.0;
    D_80033F80[arg1] = arg3 - 100.0;
    D_80033F98[arg1] = arg4 * 1.333;
    return arg0;
}

extern s8 D_80033F50;

void menuUpdateItemTransition(void *arg0, MenuScreenState *arg1, s32 arg2) {
    if (!arg1->unk16) {
        arg1->unk0 += 0.13f;
        if (arg1->unk0 > 1.3f) {
            arg1->unk0 = 1.0f;
            arg1->unk12 = arg1->unk13;
            arg1->unk16 = -1;
            menuUpdateStateDispatch(arg0, 0, 0, 0);
            func_80609140(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        }
    } else {
        if (arg1->unk0 > 0.0f) {
            arg1->unk0 -= 0.2f;
            if (arg1->unk0 < 0.0f) {
                arg1->unk0 = 0.0f;
                if (arg2 != 0) {
                    func_80609140(0x3C, 0x61A8, 63.0f, 1.0f, 0, 0);
                    D_80033F50 = 3;
                }
            }
        }
    }
}

extern s8 D_800337F0;


void menuHandleScrollInput(MenuScreenState *arg0, s32 arg1, s32 arg2) {
    if (arg2 & 4) {
        func_80609140(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        D_80033F44 = -0.1f;
        arg0->unk17--;
        arg0->unk4 = 1.0f;
        if (arg0->unk17 < 0) {
            arg0->unk17 += arg1;
        }
        D_800337F0 = 0;
    } else if (arg2 & 8) {
        func_80609140(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
        D_80033F44 = 0.1f;
        D_800337F0 = 0;
    }
}


void menuUpdateScrollAnimation(MenuScreenState *arg0, s32 arg1) {
    if (D_80033F44 > 0.0f) {
        arg0->unk4 += D_80033F44;
        if (arg0->unk4 >= 1.0f) {
            arg0->unk4 = 0.0f;
            arg0->unk17++;
            if (arg0->unk17 >= arg1) {
                arg0->unk17 -= arg1;
            }
            D_80033F44 = 0.0f;
        }
    } else if (D_80033F44 < 0.0f) {
        arg0->unk4 += D_80033F44;
        if (arg0->unk4 <= 0.0f) {
            D_80033F44 = 0.0f;
            arg0->unk4 = 0.0f;
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
extern f32 D_80033F3C;
extern void *D_80033F34;
extern s8 D_80033F30;
void actorScriptStart(void *, s32);
void func_8061B650(s32);
void func_8060CB9C(void);
void menuInsertHighScore(void);
void renderCallbacksRegister(void *, void *, s32);
void *func_80610FE8(s32);
void menuInitGfxState(Gfx *, s32);

void menuInit(void) {
    MenuScreenState *sub = D_807FBB40->unk174;
    Menu10_Sub174 *sp20 = D_807FBB4C->unk174;
    s32 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
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
        D_807FBB44->unk7C = D_807FBB4C->unk7C;
        D_807FBB44->unk80 = D_807FBB4C->unk80;
        D_807FBB44->unk84 = D_807FBB4C->unk84;
        D_807FBB44->unkE6 = D_807FBB4C->unkE6;
        if (D_80744514 != 0) {
            D_80033738 = 0x15;
            D_807FBB4C->unk154 = 0x85;
            D_807FBB4C->unk155 = 0;
            actorScriptStart(D_807FBB4C, 0x347);
            D_807FBB4C->unk155 = 6;
            func_8061B650(gCamActor);
            D_80033F3C = 1.0f;
            sp20->unk23C = 0x50;
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
            actorScriptStart(D_807FBB44, 0x349);
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
        D_80033F34 = func_80610FE8(0x80);
        D_80033F30 = 0;
        menuUpdateStateDispatch(D_807FBB40, 0, 0, 0);
        D_80744514 = 0;
        controllerSetActiveMask(0xFF);
        func_8060CB9C();
    }
    menuUpdateStateDispatch(D_807FBB40, 2, 0, 0);
    renderCallbacksRegister(menuInitGfxState, D_807FBB40, 3);
}

static void func_8003026C(void) {
}

extern Gfx D_1000118;
extern Mtx D_20000C0;


void menuInitGfxState(Gfx *glistp, s32 arg1) {
    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_1000118);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetRenderMode(glistp++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 255);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    menuUpdateStateDispatch(arg1, 1, glistp, 0);
}

extern f32 D_80033F40;
typedef struct MenuStickAxis {
    char pad0[2];
    s8 unk2;
    s8 unk3;
} MenuStickAxis;

extern MenuStickAxis *D_807ECDEC;
void func_80027FAC();
Gfx *func_800286C8();
void func_80028834();
Gfx *func_80028D3C();
void func_80028EA8();
s32 menuDrawFileSummary();
void menuInitFileSummary();
Gfx *menuDrawFileSlotLabel();
void menuInitFileSelect();
Gfx *func_8002A088();
Gfx *menuDrawSubmenuRing();
void menuInitControllerSlots();
void menuHandleControllerSlotInput();
Gfx *func_8002B708();
void func_8002C0C8();
s32 func_8002C634();
void func_8002C91C();
void menuHandleSoundOptionsInput();
void func_8002D8AC();
void func_8002DFA8();
Gfx *func_8002E420();
void func_8002E8B8();
void menuHandleHighScoreNameEntryInput();
void lightSetColor(f32, f32, f32, s32);

Gfx *menuUpdateStateDispatch(MenuScreenActor *arg0, s32 arg1, Gfx *arg2, s32 arg3) {
    MenuScreenState *temp_t0 = arg0->unk174;
    s32 sp18 = 0;

    if (*D_807FC924->unk298 & 0x8000) {
        sp18 = 1;
    }
    if (*D_807FC924->unk298 & 0x4000) {
        sp18 |= 2;
    }
    if (*D_807FC924->unk298 & 8) {
        sp18 |= 0x40;
    }
    if (*D_807FC924->unk298 & 4) {
        sp18 |= 0x80;
    }
    if (*D_807FC924->unk298 & 0x2000) {
        sp18 |= 0x100;
    }
    if (D_807ECDEC->unk2 < -0x28) {
        sp18 |= 4;
    } else if (D_807ECDEC->unk2 >= 0x29) {
        sp18 |= 8;
    }
    if (D_807ECDEC->unk3 < -0x28) {
        sp18 |= 0x20;
    } else if (D_807ECDEC->unk3 >= 0x29) {
        sp18 |= 0x10;
    }
    switch (arg1) {
    case 0:
        D_80033F38 = 1;
        D_80033F44 = 0.0f;
        D_80033F40 = 0.0f;
        D_80033F3C = 0.0f;
        D_807FBB60 &= 0xFFFEFFFF;
        temp_t0->unkC = 0;
        temp_t0->unkE = 0;
        D_800337F8 = 1;
        break;
    case 1:
        break;
    case 2:
        D_8076A0D0[temp_t0->unk12] = temp_t0->unk17;
        lightSetColor(1.0f, 1.0f, 1.0f, 0);
        break;
    }
    switch (temp_t0->unk12) {
    case 0:
        if (arg1 == 1) {
            return func_80027F34(arg0, arg2);
        }
        if (arg1 == 2) {
            func_80027E60(arg0, sp18);
        } else {
            menuResetCameraAndFlags(arg0, arg3);
        }
        break;
    case 1:
        if (arg1 == 1) {
            return func_800286C8(arg0, arg2);
        }
        if (arg1 == 2) {
            func_80027FAC(arg0, sp18);
        } else {
            func_80028834(arg0, arg3);
        }
        break;
    case 2:
        if (arg1 == 1) {
            return func_80028D3C(arg0, arg2);
        }
        if (arg1 == 2) {
            menuHandleSelectionInput(arg0, sp18);
        } else {
            func_80028EA8(arg0, arg3);
        }
        break;
    case 3:
        if (arg1 == 1) {
            return (Gfx *)menuDrawFileSummary(arg0, arg2);
        }
        if (arg1 == 2) {
            menuHandleConfirmationInput(arg0, sp18);
        } else {
            menuInitFileSummary(arg0, arg3);
        }
        break;
    case 4:
        if (arg1 == 1) {
            return menuDrawFileSlotLabel(arg0, arg2);
        }
        if (arg1 == 2) {
            menuHandleFileSelectInput(arg0, sp18);
        } else {
            menuInitFileSelect(arg0, arg3);
        }
        break;
    case 5:
        if (arg1 == 1) {
            return func_8002A088(arg0, arg2);
        }
        if (arg1 == 2) {
            menuMysteryHandleInput(arg0, sp18);
        } else {
            func_8002A36C(arg0, arg3);
        }
        break;
    case 6:
        if (arg1 == 1) {
            return menuDrawSubmenuRing(arg0, arg2);
        }
        if (arg1 == 2) {
            menuBossReplayHandleInput(arg0, sp18);
        } else {
            menuInitControllerSlots(arg0, arg3);
        }
        break;
    case 7:
        if (arg1 == 1) {
            return func_8002B708(arg0, arg2);
        }
        if (arg1 == 2) {
            menuHandleControllerSlotInput(arg0, sp18);
        } else {
            func_8002C0C8(arg0, arg3);
        }
        break;
    case 11:
        if (arg1 == 1) {
            return (Gfx *)func_8002C634(arg0, arg2);
        }
        if (arg1 == 2) {
            func_8002C584(arg0, sp18);
        } else {
            func_8002C91C(arg0, arg3);
        }
        break;
    case 8:
        if (arg1 == 1) {
            return menuFormatOptionValues(arg0, arg2);
        }
        if (arg1 == 2) {
            menuHandleSoundOptionsInput(arg0, sp18);
        } else {
            func_8002D7EC(arg0, arg3);
        }
        break;
    case 9:
        if (arg1 == 1) {
            return func_8002DBDC(arg0, arg2);
        }
        if (arg1 == 2) {
            func_8002D8AC(arg0, sp18);
        } else {
            func_8002DEE8(arg0, arg3);
        }
        break;
    case 10:
        if (arg1 == 1) {
            return func_8002E420(arg0, arg2);
        }
        if (arg1 == 2) {
            func_8002DFA8(arg0, sp18);
        } else {
            func_8002E8B8(arg0, arg3);
        }
        break;
    case 12:
        if (arg1 == 1) {
            return (Gfx *)menuDrawHighScoreTable(arg0, arg2);
        }
        if (arg1 == 2) {
            menuHandleHighScoreNameEntryInput(arg0, sp18);
        } else {
            func_8002F6C8(arg0, arg3);
        }
        break;
    }
    if (D_80033F50 > 0) {
        D_80033F50--;
    }
    D_80033670 = sp18;
    return arg2;
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
void func_80030C14();
f32 sqrtf(f32);

void func_80030894(MenuScreenState *arg0, void *arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5, s32 arg6) {
    Menu10_Fx *sp3C;
    Menu10_Burst *sp38;
    f32 sp34;
    f32 sp30;
    f32 dist;
    f32 scale;

    func_80714998(arg5);
    func_8071495C();
    func_807149FC(-1);
    func_80714950(arg0);
    func_8071498C(func_80030C14);
    func_80714A28(1);
    sp3C = func_80714CC0(arg1, arg4, arg2, arg3, -10.0f);
    sp38 = func_80610FE8(0x28);
    sp3C->unk384 = sp38;
    sp38->unk0 = arg6;
    sp38->unk4 = arg0->unk15;
    sp38->unk8 = sp3C->unk340;
    sp38->unkC = sp3C->unk344;
    switch (arg6) {
    case 14:
        sp3C->unk360 = -sp3C->unk360;
    case 0:
    case 1:
    case 11:
    case 12:
    case 13:
    case 16:
    case 17:
    case 19:
        sp34 = 640.0f - sp38->unk8;
        sp30 = 480.0f - sp38->unkC;
        dist = sqrtf((sp34 * sp34) + (sp30 * sp30));
        scale = 1040.0f - dist;
        sp38->unk10 = -(sp34 / dist) * scale;
        sp38->unk14 = -(sp30 / dist) * scale;
        sp38->unk18 = sp3C->unk360;
        break;
    case 2:
    case 3:
    case 10:
        sp38->unk8 = arg2;
        sp38->unk10 = arg4;
        sp38->unk14 = 0.0f;
        break;
    case 15:
        sp38->unk8 = arg2;
        break;
    default:
        sp38->unk10 = arg4;
        sp38->unk14 = 0.0f;
        break;
    }
    if (D_80033F38 == 0) {
        sp3C->unk36A = 0x80;
        sp3C->unk36B = 0x80;
        sp3C->unk36C = 0x80;
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
f32 func_806119FC();

void func_80030A90(Menu10_Spinner *arg0, s32 arg1) {
    Menu10_Spin *p;
    s16 sp72;
    f32 sp30[4][4];
    if (arg0->unk384 == NULL) {
        p = arg0->unk384 = func_80610FE8(0x10);
        sp72 = func_806119A0() * 0x10;
        p->vx = func_80612794(sp72) * 60.0f;
        p->vy = func_80612790(sp72) * 60.0f;
        p->ang = func_806119FC() * 3.141f;
        arg0->unk340 = arg0->unk340 + p->vx * 3.0f;
        arg0->unk344 = arg0->unk344 + p->vy * 3.0f;
        if (p->vx > 0) {
            p->dir = 0.3f;
        } else {
            p->dir = -0.3f;
        }
    }
    p = arg0->unk384;
    arg0->unk340 = arg0->unk340 + p->vx;
    arg0->unk344 = arg0->unk344 + p->vy;
    p->ang = p->ang + p->dir;
    guRotateF(sp30, p->ang, 0.0f, 0.0f, 1.0f);
    guMtxF2L(sp30, &arg0->mtx[D_807444FC]);
}

#ifdef NON_MATCHING
typedef struct MenuRgba {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} MenuRgba;

typedef struct MenuL5_Cfg {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC[5];
    char padC[1];
    s8 unk17;
} MenuL5_Cfg;

typedef struct MenuL5_Tgt {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} MenuL5_Tgt;

typedef struct MenuL5_Actor {
    char pad0[0x340];
    f32 unk340;
    f32 unk344;
    char pad348[0x14];
    MenuL5_Cfg *unk35C;
    f32 unk360;
    f32 unk364;
    char pad368[2];
    u8 unk36A;
    u8 unk36B;
    u8 unk36C;
    u8 unk36D;
    char pad36E[0x16];
    MenuL5_Tgt *unk384;
    char pad388[6];
    s16 unk38E;
    char pad390[2];
    s16 unk392;
} MenuL5_Actor;

extern MenuRgba D_800337DC[];
s32 func_8003155C(void *, s32, f32 *, f32 *, f32 *, s16 *, s16 *);

void func_80030C14(MenuL5_Actor *arg0, u8 *arg1) {
    MenuL5_Cfg *p = arg0->unk35C;
    MenuL5_Tgt *c;
    f32 f;
    f32 sp68;
    f32 sp64;
    s32 off;
    s32 type;
    s32 t;
    s32 idx;
    s32 r;
    s32 sp4C;
    s16 sp4A;
    s16 sp48;

    if (arg0->unk384 != NULL) {
        c = arg0->unk384;
        f = p->unk0;
        off = (s32)((f64)p->unkC[(s32)c->unk4] * 4.0);
        type = (s32)c->unk0;

        switch (type) {
        case 6:
        case 7:
        case 18: {
            r = func_8003155C(p, (s32)c->unk8 >> 2, &arg0->unk340, &arg0->unk344, &sp64, &sp4A, &sp48);
            arg0->unk360 = c->unk10 * sp64 * 4.0f;
            arg0->unk364 = arg0->unk360;
            if (type == 7) {
                t = (D_8076A064 * 0x78) & 0xFFF;
                arg0->unk344 += func_80612794(t) * 10.0f;
            }
            if (type == 0x12) {
                arg0->unk36A = sp4A;
                arg0->unk36B = sp4A;
                arg0->unk36C = sp4A;
                arg0->unk36D = sp48;
                arg0->unk38E = D_807FC924->unk270;
                arg0->unk392 = D_807FC924->unk274;
                if (arg0->unk344 < 360.0) {
                    if ((f64)arg0->unk340 < 640) {
                        arg0->unk392 = 0x78;
                    } else {
                        arg0->unk38E = 0xC8;
                    }
                }
                if (D_80033F3C != 0.0 && r == 0) {
                    arg0->unk392 = 0;
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
            arg0->unk36D = (s32)(f * 255.0f);
            if (type == 4) {
                arg0->unk360 = (f64)(c->unk10 * f) * 4.0;
                arg0->unk364 = arg0->unk360;
            }
            f = 0;
            arg0->unk344 = c->unkC + (f32)off;
            if (type == 8) {
                D_80033FAC = 0;
                t = D_807ECDEC->unk2;
                if (t >= 0xB) {
                    arg0->unk340 += (f32)t;
                    if (arg0->unk340 > 960.0f) {
                        arg0->unk340 = 960.0f;
                        D_80033FAC = 1;
                    }
                } else if (t < -0xA) {
                    arg0->unk340 += (f32)t;
                    if (arg0->unk340 < 320.0f) {
                        arg0->unk340 = 320.0f;
                        D_80033FAC = 1;
                    }
                } else {
                    arg0->unk340 = (arg0->unk340 - 640.0) * 0.9 + 640.0;
                }
            } else {
                arg0->unk340 = c->unk8;
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
            arg0->unk340 = c->unk10 * f + c->unk8;
            arg0->unk344 = c->unk14 * f + c->unkC + (f32)off;
            if (type == 9) {
                arg0->unk344 = D_80033F4C - 140.0f;
            }
            if (type == 0xC) {
                arg0->unk344 += (f32)D_80033674;
            }
            if (type == 0) {
                if (off < -0x3BC) {
                    arg0->unk364 = 0.0f;
                } else {
                    arg0->unk364 = arg0->unk360;
                }
            }
            if (type == 0xB || type == 0x13) {
                arg0->unk344 += 960;
                if (off >= -3 || off < -0x77C) {
                    arg0->unk364 = 0.0f;
                } else {
                    arg0->unk364 = arg0->unk360;
                }
            }
            if (type == 0xD) {
                arg0->unk344 += 1920.0f;
                if (off >= -0x3C3) {
                    arg0->unk364 = 0.0f;
                } else {
                    arg0->unk364 = arg0->unk360;
                }
            }
            if (type == 0xE) {
                t = (D_8076A064 * 0x78) & 0xFFF;
                arg0->unk344 += func_80612794(t) * 10.0f;
            }
            if (type == 0x13 && (D_80033FAD == 4 || D_80033FAD == 1 || D_8076A104 == 1)) {
                arg0->unk340 = -400.0f;
            }
            if (type == 0x10 && p->unk17 >= 3) {
                arg0->unk340 = -400.0f;
            }
            if (type == 0x11 && p->unk17 < 3) {
                arg0->unk340 = -400.0f;
            }
            break;
        case 2:
        case 3:
        case 10: {
            idx = (s32)c->unk8;
            switch (type) {
            case 2:
                sp4C = 4;
                sp64 = 1024.0f;
                sp68 = 65.0f;
                break;
            case 3:
                sp4C = 3;
                sp64 = 1365.0f;
                sp68 = 55.0f;
                break;
            case 10:
                sp4C = 2;
                sp64 = 2048.0f;
                sp68 = 50.0f;
                break;
            }
            idx = idx * (s32)sp64 - p->unk17 * (s32)sp64 - (s32)(p->unk4 * sp64);
            t = (s16)idx;
            arg0->unk340 = 160.0f - func_80612794(t) * sp68;
            arg0->unk344 = 120.0f - func_80612790(t) * sp68;
            if (func_800317E8(p, arg0->unk340, arg0->unk344, &arg0->unk340, &arg0->unk344, sp4C, 0, 1.0f) == (s32)c->unk8) {
                sp64 = 1.1f;
            } else {
                sp64 = 0.825f;
            }
            f = 0.0f;
            arg0->unk340 *= 4.0f;
            arg0->unk344 *= 4.0f;
            arg0->unk360 = c->unk10 * 4.0f * sp64;
            arg0->unk364 = arg0->unk360;
            break;
        }
        case 15: {
            idx = (s32)c->unk8;
            arg0->unk340 = D_80033F68[idx];
            arg0->unk344 = D_80033F80[idx];
            arg0->unk360 = D_80033F98[idx];
            arg0->unk364 = D_80033F98[idx];
            D_80033F68[idx] = -200.0f;
            D_80033F80[idx] = -200.0f;
            if (*(&D_80033804 + idx) == 0) {
                arg0->unk36A = *((u8 *)D_800337DC + (idx << 2));
                arg0->unk36B = *((u8 *)D_800337DC + (idx << 2) + 1);
                arg0->unk36C = *((u8 *)D_800337DC + (idx << 2) + 2);
            }
            break;
        }
        }
        if (f > 1.0f || p->unk0 > 1.0f) {
            *arg1 = 1;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_80030C14.s")
#endif

#ifdef NON_MATCHING
typedef struct MenuNM2_Sel {
    f32 unk0;
    f32 unk4;
    char pad8[4];
    s16 unkC;
    char padE[9];
    s8 unk17;
} MenuNM2_Sel;

extern f32 D_8003373C[];
extern f32 D_8003378C[];
f32 menuEvaluateSpline(f32 *, f32, f32 *);

s32 func_8003155C(void *arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5, s16 *arg6) {
    f32 v;
    volatile s32 ret;
    arg1 += ((MenuNM2_Sel *)arg0)->unk17;
    if (arg1 >= 5) {
        arg1 -= 5;
    }
    ret = arg1;
    D_8003378C[arg1 * 4 + 2] = D_8003373C[arg1 * 4];
    D_8003373C[arg1 * 4 + 2] = -D_8003378C[arg1 * 4];
    D_8003378C[arg1 * 4 + 3] = D_8003373C[arg1 * 4 + 1];
    D_8003373C[arg1 * 4 + 3] = -D_8003378C[arg1 * 4 + 1];
    *arg2 = menuEvaluateSpline((f32 *)((u8 *)D_8003373C + ((arg1 * 4) << 2)), ((MenuNM2_Sel *)arg0)->unk4, NULL);
    *arg3 = menuEvaluateSpline((f32 *)((u8 *)D_8003378C + ((arg1 * 4) << 2)), ((MenuNM2_Sel *)arg0)->unk4, NULL);
    if (*arg3 < -40.0f) {
        v = -*arg3 - 40.0f;
        if (v > 20.0f) {
            v = 20.0f;
        }
        *arg4 = (v / 60.0f) + 1.0f;
        *arg5 = (s32)(v * 6.2f) + 0x80;
    } else {
        *arg4 = 1.0f;
        *arg5 = 0x80;
    }
    *arg6 = 0xFF;
    if (&D_8003373C[arg1 * 4] == D_8003373C) {
        *arg3 *= 1.0f - D_80033F3C;
        *arg4 += D_80033F3C * 3.5f;
        if (D_80033F3C != 0.0f) {
            *arg6 = 0xFF - (s32)(((MenuNM2_Sel *)arg0)->unk0 * 255.0f);
            if (*arg6 < 0) {
                *arg6 = 0;
            }
        }
    }
    *arg2 *= 4.0f + (((MenuNM2_Sel *)arg0)->unk0 * 4.0f);
    *arg3 *= 4.0f + (((MenuNM2_Sel *)arg0)->unk0 * 4.0f);
    *arg2 += 640.0f;
    *arg3 += 480.0f;
    return ret;
}
#else

#pragma GLOBAL_ASM("asm/menu/nonmatchings/3E10/func_8003155C.s")
#endif

s32 func_800317E8(MenuScreenState *arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, s32 arg5, s8 arg6, f32 arg7) {
    f32 dist;
    f32 f;
    f32 t;
    s32 idx;

    arg1 = arg1 - 160.0f;
    t = 0.0f;
    arg2 = arg2 - 120.0f;
    dist = sqrtf((arg1 * arg1) + (arg2 * arg2));
    if (dist < 20.0f) {
        dist = 20.0f;
    }
    f = arg0->unk4;
    idx = arg0->unk17;
    if (t != f) {
        if (f > 0.5f) {
            idx += 1;
        }
        if (idx >= arg5) {
            idx -= arg5;
        }
    }
    t = arg0->unk0 * 0.5f;
    if (arg6 == 1) {
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
    t = ((100.0f / dist) * t * arg7) + 1.0f;
    *arg3 = (arg1 * t) + 160.0f;
    *arg4 = (arg2 * t) + 120.0f;
    *arg4 = *arg4 + arg0->unkC;
    return idx;
}

f32 menuEvaluateSpline(f32 *arg0, f32 arg1, f32 *arg2) {
    f32 sp[4];

    sp[0] = (arg0[0] + arg0[0] + -2.0f * arg0[1] + arg0[2]) + arg0[3];
    sp[1] = (-3.0f * arg0[0] + 3.0f * arg0[1] + -2.0f * arg0[2]) - arg0[3];
    sp[2] = arg0[2];
    sp[3] = arg0[0];
    if (arg2 != NULL) {
        *arg2 = ((((3.0f * sp[0]) * arg1) + (sp[1] + sp[1])) * arg1) + sp[2];
    }
    return (((((sp[0] * arg1) + sp[1]) * arg1) + sp[2]) * arg1) + sp[3];
}

extern s8 D_80033734;
void camStartPath(void *, s32, s32);

void menuActorStateDispatch(void) {
    MenuActor *actor = D_807FBB40;

    switch (actor->unk155) {
    case 0:
        actorScriptStart(actor, 0x345);
        D_807FBB40->unkE6 = 0;
        D_807FBB40->unk155 = 1;
        camStartPath(D_807FBB40, 0x13, 5);
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

void func_80031B08(void) {
    Menu10_Sub174 *temp_v1;
    s32 i;

    temp_v1 = D_807FBB40->unk174;
    D_8003369C += 4.5f;
    if (D_8003369C > 0.0f) {
        D_8003369C = 0.0f;
    }
    switch (D_807FBB40->unk155) {
    case 0:
        D_807FBB40->unkE6 = 0x800;
        D_807FBB40->unk155 = 1;
        actorScriptStart(D_807FBB40, 0x346);
        func_8061B650(gCamActor);
        D_8003369C = -35.0f;
        break;
    case 1:
        if (D_8003369C == 0.0f) {
            actorScriptStart(D_807FBB40, 0x347);
            D_807FBB40->unk155 = 2;
            temp_v1->unk23C = 0;
        }
        break;
    case 2:
        temp_v1->unk23C += 1;
        if (temp_v1->unk23C == 3) {
            func_80609140(0x3C, 0x61A8, 63.0f, 1.0f, 0, 0);
            D_80033F50 = 3;
        }
        break;
    case 3:
        if (*D_807FC924->unk298 & 0x8000) {
            if (D_800337F0 == 1) {
                actorScriptStart(D_807FBB40, 0x348);
                D_807FBB40->unk155 = 4;
                D_800337F4 = 0x3C;
            } else if (D_800337F0 == -1) {
                func_80609140(0x98, 0x61A8, 63.0f, 1.0f, 0, 0);
            }
        }
        break;
    case 5:
        D_80033F40 = 0.1f;
        D_80033F3C = D_80033F40;
        D_800337F4 = 0;
        temp_v1->unk23C = 0;
        D_807FBB40->unk155 = 6;
        break;
    case 6:
    case 7:
    case 8:
        temp_v1->unk23C += 1;
        if (temp_v1->unk23C >= 0x3E9) {
            temp_v1->unk23C = 0x3E8;
        }
        if (temp_v1->unk23C == 8) {
            func_8071495C();
            func_80714CC0(&D_8071FE08, 8.3f, 160.0f, 120.0f, -10.0f);
            func_80609140(0x23, 0x7FFF, 63.0f, 1.0f, 0, 0);
            func_80609140(0x17, 0x7FFF, 63.0f, 1.0f, 0, 0);
            for (i = 0; i != 5; i++) {
                func_8071498C(func_80030A90);
                func_8071495C();
                func_80714CC0(&D_8071FE64, 1.8f, 160.0f, 120.0f, -10.0f);
            }
        }
        if (temp_v1->unk23C >= 0xC) {
            D_807FBB60 &= 0xFFFEFFFF;
        }
        break;
    }
    if (D_80033698 != 0) {
        D_80033698 -= 1;
    }
    if (D_807FBB40->unk155 < 6) {
        if (D_8003369C > -30.0) {
            D_807FBB60 |= 0x10000;
        } else {
            D_80033698 = 3;
        }
    }
    D_80033738 = 0x14;
    D_807FBB40->unk80 = -D_8003369C;
    D_807FC924->unk210 = D_807FBB40->unk7C;
    D_807FC924->unk214 = (D_80033678[D_80033F50] * 50.0) + (D_807FBB40->unk80 + 13.1f + D_8003369C) - 0.1;
    D_807FC924->unk218 = D_807FBB40->unk84 - 50.0f;
    D_807FC924->unk228 = D_807FBB40->unk7C;
    D_807FC924->unk22C = D_807FC924->unk214;
    D_807FC924->unk230 = 10020.0f;
    D_80754CE0 = D_80033678[D_80033F50] * 400.0f;
    actorUpdateModelMatrix(D_807FBB40, 0);
}

extern f32 D_8003378C[];
void actorDespawn(void *);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

void func_80032024(void) {
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

    pos = D_807FBB40->unk174;
    if (D_807FBB4C->unk155 < 6) {
        if (D_80033738 == 0x14) {
            actorDespawn(D_807FBB40);
            D_80033738 += 1;
            actorSpawn(0x14D, 0xD7);
            D_807FBB44->unk4->unk34 = 0.14f;
            D_807FBB44->unk4->unk38 = 0.14f;
            D_807FBB44->unk4->unk3C = 0.14f;
        } else if (D_80033738 == 0x15) {
            actorGetNodePos(D_807FBB4C, 2, &x[0], &y[0], &z[0]);
            actorGetNodePos(D_807FBB4C, 3, &x[1], &y[1], &z[1]);
            cx = (x[0] + x[1]) * 0.5f;
            cy = y[0];
            cz = (z[0] + z[1]) * 0.5f;
            D_807FBB40->unk7C = cx;
            D_807FBB40->unk80 = cy;
            D_807FBB40->unk84 = cz;
            pos->unk0 = D_807FBB40->unk7C;
            pos->unk4 = D_807FBB40->unk80;
            pos->unk8 = D_807FBB40->unk84;
            D_807FBB40->unkE6 = 0;
            D_807FBB40->unkE8 = 0x400;
            camProjectToScreen(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, &s[1], &s[0], 0, 1.0f, 0);
            s[0] = s[0] - 120.0f;
            if (s[0] < -35.0f) {
                if (s[0] > -75.0f) {
                    D_8003378C[0] = s[0];
                    D_8003378C[0x11] = s[0];
                }
            }
        }
    } else {
        D_807FBB40->unk7C = pos->unk0;
        D_807FBB40->unk80 = pos->unk4 - (D_80033F3C * 19.0f);
        D_807FBB40->unk84 = pos->unk8 - (D_80033F3C * 50.0f);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    if (D_80033698 != 0) {
        D_807FBB40->unk60 &= ~4;
    } else {
        D_807FBB40->unk60 |= 4;
    }
}


s32 menuCheckSaveFile(arg0)
    u8 arg0;
{
    return func_8060C6B8(0xD, 0, 0, arg0) == 0;
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
void func_806ABE3C(void);

s32 menuCalculateGamePercentage(void) {
    f32 pct;

    func_806ABE3C();
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

char *func_8070E750(s32, s32, s32);

void menuLoadTextTable(void) {
    s32 i;

    D_80033F28 = func_80610FE8(0x194);
    i = 0;
    do {
        D_80033F28[i] = func_8070E750(0x25, i, 0);
        i++;
    } while (i != 0x65);
}
