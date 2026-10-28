#include "common.h"

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

extern u8 D_8076A0AB;
extern s32 D_80032F48[][6];
extern MenuStruct_30A2 D_800330A2[];

s32 func_805FF030(s32, s32);
void func_8063DA40(s16, s32);
void camStartPath(s32, s32, s32);

void menuPlaySoundFromTable(MenuStruct_80024000 *arg0) {
    s32 temp_v1 = D_80032F48[func_805FF030(D_8076A0AB, 0)][arg0->unk1];

    if (temp_v1 == 0) {
        func_8063DA40(D_800330A2[arg0->unk1A].unk0, 9);
        arg0->unk0 = 4;
        arg0->unk1 = 0;
        return;
    }
    if (temp_v1 == 4) {
        arg0->unk6 = 1;
    }
    camStartPath(0, (s16)temp_v1, 1);
    arg0->unk1++;
}


extern u8 D_80720268;
void func_80714998(s32);
void func_807149B8(s32);
void func_807149FC(s32);
MenuActor_340 *func_80714CC0(void *, s32, s32, s32, f32);

void menuSpawnPositionalActor(MenuStruct_80024000 *arg0) {
    arg0->unk10 = 11.35f;
    arg0->unkC = -6.55f;
    arg0->unk14 = 6.6f;
    arg0->unk6 = 0;
    func_80714998(0);
    func_807149B8(1);
    func_807149FC(-1);
    func_80714998(0);
    arg0->unk8 = func_80714CC0(&D_80720268, 0x3E99999A, 0x43350000, 0x40400000, 82.0f);
}

void effectFreeAndUnlink(MenuActor_340 *);

void menuUpdateFallingActor(MenuStruct_80024000 *arg0) {
    MenuActor_340 *temp_v0 = arg0->unk8;
    temp_v0->x += arg0->unkC;
    temp_v0->z += arg0->unk14;
    arg0->unk10 += -1.0f;
    temp_v0->y += arg0->unk10;
    arg0->unk6++;
    if (arg0->unk6 >= 0x16) {
        arg0->unk6 = 0;
        effectFreeAndUnlink(arg0->unk8);
        arg0->unk8 = NULL;
    }
}

extern void *D_807FBB4C;
void func_806CFF9C(void *);
void func_805FF898(void);

void menuResetAudioState(void) {
    func_806CFF9C(D_807FBB4C);
    func_805FF898();
    camStartPath(0, 7, 1);
}

typedef struct {
    char pad0[1];
    u8 unk1;
    char pad2[0x17];
    s8 unk19;
} MenuSubStruct_180;

typedef struct {
    char pad0[0x60];
    s32 unk60;
    char pad64[0xFB];
    u8 unk15F;
    char pad160[0x20];
    MenuStruct_80024000 *unk180;
} MenuRenderActor;
extern MenuRenderActor *D_807FBB40;
extern s16 D_80750AC8;
s32 currentActorTestClearFlag(void);
void func_8070D8C0(void *, s32, u8);
void camResumePath(void);
void currentActorClearFlag();

void menuPlaySoundFromTable(MenuStruct_80024000 *);
void menuUpdateFallingActor(MenuStruct_80024000 *);

void menuMainStateStep(MenuStruct_80024000 *arg0, s32 arg1) {
    s32 var_v0;

    switch (arg0->unk1) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            if (arg1 != 0) {
                currentActorClearFlag();
                func_8070D8C0(D_807FBB40, 0xB, 0);
                if ((var_v0 = arg0->unk1A) == 1) {
                    var_v0 = 1;
                } else if (var_v0 >= 2) {
                    var_v0 = 2;
                } else {
                    var_v0 = 3;
                }
                D_80750AC8 = arg0->unk1A;
                func_8070D8C0(D_807FBB40, 0xB, var_v0);
            } else {
                if (arg0->unk1A == 1) {
                    var_v0 = 5;
                } else {
                    var_v0 = 6;
                }
                D_80750AC8 = arg0->unk1A;
                func_8070D8C0(D_807FBB40, 0xB, var_v0);
            }
            arg0->unk1++;
        }
        break;
    case 1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            camResumePath();
            arg0->unk1++;
        }
        break;
    case 2:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            if (arg0->unk1A != 0) {
                camStartPath(0, 5, 1);
                arg0->unk1++;
            } else {
                arg0->unk0 = 4;
                arg0->unk1 = 0;
            }
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        if (arg0->unk6 != 0) {
            if (arg0->unk6 == 1) {
                if (currentActorTestClearFlag() != 0) {
                    currentActorClearFlag();
                    arg0->unk6 = 2;
                }
            } else {
                menuUpdateFallingActor(arg0);
            }
        }
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            menuPlaySoundFromTable(arg0);
        }
        break;
    }
}

void menuTransitionStep(arg0, arg1)
MenuStruct_80024000 *arg0;
u8 arg1;
{
    switch (arg0->unk1) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            func_8070D8C0(D_807FBB40, 0xB, arg1);
            arg0->unk1++;
        }
        break;
    case 1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            camResumePath();
            arg0->unk1++;
        }
        break;
    case 2:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            arg0->unk0 = 4;
            arg0->unk1 = 0;
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

s32 _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s32, s16, f32, char *);
Gfx *func_806FC530(Gfx *, s32, s32, s32, char *, s32);
char *func_8070E750(s32, s32, s32);

Gfx *menuDrawOptionsOverlay(Gfx *arg0, MenuRenderActor *arg1) {
    s32 y;
    MenuStruct_80024000 *temp_s7 = arg1->unk180;
    char sp70[0x28];

    WRITE_GFX(arg0++, 0xDE000000, D_1000118);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    if (temp_s7->unk1 >= 4) {
        s32 i;
        WRITE_GFX(arg0++, 0xDA380003, D_2000180);
        WRITE_GFX(arg0++, 0xDA380007, D_20000C0);
        WRITE_GFX(arg0++, 0xE7000000, 0);
        y = 0xF0;
        for (i = 0; i < 8; i++) {
            if (i + 4 == temp_s7->unk1) {
                WRITE_GFX(arg0++, 0xFA000000, -1);
            } else {
                WRITE_GFX(arg0++, 0xFA000000, -0x80);
            }
            arg0 = hudDrawScaledText(arg0, 0x280, y, 0.6f, func_8070E750(0x2A, i + 3, 1));
            y += 0x3C;
        }
    } else {
        WRITE_GFX(arg0++, 0xFA000000, (arg1->unk15F & 0xFF) | ~0xFF);
        _sprintf(sp70, "q %s", func_8070E750(0x2A, 0, 1));
        arg0 = func_806FC530(arg0, 1, 0x15E, 0x190, sp70, 1);
        _sprintf(sp70, "b %s", func_8070E750(0x2A, 1, 1));
        arg0 = func_806FC530(arg0, 1, 0x15E, 0x1F4, sp70, 1);
        if (temp_s7->unk19 != 0) {
            _sprintf(sp70, "n %s", func_8070E750(0x2A, 2, 1));
            arg0 = func_806FC530(arg0, 1, 0x15E, 0x258, sp70, 1);
        }
    }
    return arg0;
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

extern MenuControllerPad D_807FD610[];
extern MenuStickAxis *D_807ECDEC;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern u8 D_8074E77C;
extern u8 D_800330C0[];
extern u8 D_80032F50;
extern s16 D_800330D8;

s32 listContainsS16(s32, s16 *);
s32 flagGridIndex();
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
void func_806F8278(s32);
void func_8060DEC8(void);
s32 camIsCutsceneActive(void);
void playerStateQueueCallback(s32, void *, s32);
void func_80712774(u8);
s32 func_80609140(s32, s32, f32, f32, s32, s32);
void renderCallbacksRegister(void *, void *, s32);

void menuUpdateOptionsState(MenuStruct_80024000 *arg0) {
    s32 i;
    s32 sp40;
    u8 *sp3C;
    s32 temp;

    sp40 = 0;
    D_800330D8 = 0;
    switch (arg0->unk1) {
    case 2:
    case 0x37:
        break;
    case 0:
        if (listContainsS16(4, &D_800330D8) != 0) {
            sp3C = D_807FC950[D_8074E77C];
            for (i = 0; i < 8; i++) {
                if (flagGet((s16)flagGridIndex(0x1D5, i, D_8074E77C), 0) != 0) {
                    temp = flagGridIndex(0x1FD, i, D_8074E77C);
                    if (flagGet((s16)temp, 0) == 0) {
                        flagSet((s16)temp, 1, 0);
                        ((u16 *)(sp3C + i * 2))[0x21]++;
                        sp40 = 1;
                    }
                }
            }
            func_806F8278(0);
        }
        if (sp40 != 0) {
            func_8060DEC8();
        }
        if (camIsCutsceneActive() == 0) {
            arg0->unk1++;
            playerStateQueueCallback(0x55, 0, 0);
        }
        break;
    case 1:
        if (D_807FD610[D_807FC929].unk2C & 0x8000) {
            D_807FBB40->unk15F = 0;
            arg0->unk1 = 3;
        } else {
            arg0->unk19 = 1;
            i = 0x1FD;
            do {
                if (flagGet((s16)i, 0) == 0) {
                    arg0->unk19 = 0;
                    i = 0x224;
                }
                i++;
            } while (i < 0x225);
            {
                u8 a3 = D_807FBB40->unk15F;
                s32 d = 0xFF - a3;
                s32 inc;
                if (d >= 9) {
                    inc = 8;
                } else {
                    inc = d;
                }
                D_807FBB40->unk15F = a3 + inc;
            }
            renderCallbacksRegister(menuDrawOptionsOverlay, D_807FBB40, 3);
            if (D_807FD610[D_807FC929].unk2C & 0x4000) {
                menuResetAudioState();
                arg0->unk1 = 2;
            } else if (arg0->unk19 != 0 && (D_807FD610[D_807FC929].unk2C & 8)) {
                arg0->unk1 = 4;
            }
        }
        break;
    case 3:
        D_800330D8 = 1;
        if (D_807FD610[D_807FC929].unk2C & 0xC000) {
            arg0->unk1 = 1;
        }
        break;
    default:
        if (D_807FD610[D_807FC929].unk2C & 0x4000) {
            arg0->unk1 = 1;
        } else {
            s8 v1 = D_807ECDEC->unk3;
            if (v1 >= 0x29 && MenuM0_X18(arg0) < 0x29) {
                arg0->unk1--;
                func_80609140(0x2A0, 0x7FFF, 64.0f, 1.0f, 0, 0);
                v1 = D_807ECDEC->unk3;
            }
            if (v1 < -0x28 && MenuM0_X18(arg0) >= -0x28) {
                arg0->unk1++;
                func_80609140(0x2A0, 0x7FFF, 64.0f, 1.0f, 0, 0);
            }
            arg0->unk1 = ((arg0->unk1 - 4) & 7) + 4;
        }
        if (D_807FD610[D_807FC929].unk2C & 0x8000) {
            func_80712774(D_800330C0[arg0->unk1]);
            D_80032F50 = 1;
            arg0->unk1 = 0x37;
        }
        renderCallbacksRegister(menuDrawOptionsOverlay, D_807FBB40, 3);
        break;
    }
    MenuM0_X18(arg0) = D_807ECDEC->unk3;
}

s16 func_80712548(MenuStruct_80024000 *);

void menuProcessOptionInput(MenuStruct_80024000 *arg0) {
    switch (arg0->unk1) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag(arg0);
            arg0->unk1++;
            D_80750AC8 = func_80712548(arg0);
            func_8070D8C0(D_807FBB40, 0xB, 8);
        }
        break;
    case 1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            camResumePath();
            arg0->unk1++;
        }
        break;
    }
}

extern s16 D_8076AEF2;

void func_806F397C(void *, s32, s32, s32);
u8 flagCountRange(s32, s32, s32);
u8 flagGridSumRows(s32, s32, s32, u8);
void menuUpdateOptionsState(MenuStruct_80024000 *);
void behaviourFrameBegin(void);
void func_806BFBF4(void);
void actorUpdateModelMatrix(void *, s32);

void menuDispatchAction(void) {
    s32 pad;
    s32 var_a3;
    s32 pad2;
    s32 sp20;
    register u8 var_v1;
    MenuStruct_80024000 *temp_s0;

    var_a3 = -1;
    var_v1 = 0;
    temp_s0 = D_807FBB40->unk180;
    if (!(D_807FBB40->unk60 & 0x10)) {
        sp20 = 1;
        temp_s0->unk2 = flagCountRange(0x1FD, 0x28, 0);
        temp_s0->unk1A = flagGridSumRows(0x1D5, 0, 7, D_8074E77C);
        temp_s0->unk1A -= flagGridSumRows(0x1FD, 0, 7, D_8074E77C);
        if (D_8076AEF2 != 0x1C) {
            if (flagGet(0x174, 0) == 0) {
                temp_s0->unk0 = 0;
                temp_s0->unk1 = 0;
                sp20 = 0;
                func_806F397C(D_807FBB4C, 0, 0, 0);
                flagSet(0x174, 1, 0);
            } else {
                if (temp_s0->unk2 == 0x28) {
                    temp_s0->unk0 = 2;
                    temp_s0->unk1 = 0;
                } else {
                    if (temp_s0->unk1A == 0) {
                        temp_s0->unk0 = 1;
                        temp_s0->unk1 = 0;
                    } else {
                        temp_s0->unk0 = 3;
                        temp_s0->unk1 = 0;
                    }
                }
            }
            camStartPath(0, (s16)sp20, 1);
        } else {
            temp_s0->unk0 = 5;
            temp_s0->unk1 = 0;
        }
        currentActorClearFlag();
        menuSpawnPositionalActor(temp_s0);
        var_v1 = D_80032F50;
        D_80032F50 = 0;
    }
    switch (temp_s0->unk0) {
    case 0:
        menuMainStateStep(temp_s0, 1);
        break;
    case 3:
        menuMainStateStep(temp_s0, 0);
        break;
    case 1:
        var_a3 = 4;
        /* fallthrough */
    case 2:
        if (var_a3 < 0) {
            var_a3 = 7;
        }
        if (var_v1 != 0) {
            var_a3 = 0xB;
        }
        menuTransitionStep(temp_s0, var_a3);
        break;
    case 4:
        menuUpdateOptionsState(temp_s0);
        break;
    case 5:
        menuProcessOptionInput(temp_s0);
        break;
    }
    behaviourFrameBegin();
    func_806BFBF4();
    actorUpdateModelMatrix(D_807FBB40, 0);
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
extern u8 D_80033258;
extern MenuProgressGridVtx *D_80033F10;

void *func_80610FE8(s32);
Gfx *menuDrawProgressGrid(Gfx *, MenuRenderActor *);
void *memcpy(void *, const void *, s32);

void menuUpdateProgressGrid(void) {
    s16 *var_s0;
    s32 flag;
    s32 n;
    s32 r;
    s32 j;
    s32 k;
    s32 idx;

    var_s0 = *(s16 **)((u8 *)D_807FBB40 + 0x174);
    if (!(D_807FBB40->unk60 & 0x10)) {
        *var_s0 = 0xF0;
        *((u8 *)D_807FBB40 + 0x154) = 0;
        D_800330D0 = (s32)func_80610FE8(0x80);
        D_800330D4 = func_80610FE8(0x140);
        memcpy(D_800330D4, D_800330E0, 0x140);
        *var_s0 = -0x3E8;
        D_80033F10 = func_80610FE8(0x1400);
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
                    idx += 1;
                    idx += 1;
                    D_80033F10[n].unkC = D_80033228[idx - 2];
                    D_80033F10[n].unkD = D_80033228[idx - 1];
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
        if (*var_s0 == -0x3E8) {
            func_80609140(0x2A3, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        *var_s0 += 0x80;
        if (*var_s0 > 0) {
            *var_s0 = 0;
        }
    } else {
        if (*var_s0 == 0) {
            func_80609140(0x2A3, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        *var_s0 -= 0x80;
        if (*var_s0 < -0x3E8) {
            *var_s0 = -0x3E8;
        }
    }
    D_800330D8 = 0;
    if (*var_s0 >= -0x3E7) {
        renderCallbacksRegister(menuDrawProgressGrid, D_807FBB40, 3);
    }
}

extern u8 D_807444FC;
extern s32 D_8076A064;
s32 texCacheFindOrLoad(s32);

Gfx *menuDrawProgressGrid(Gfx *g, MenuRenderActor *arg1) {
    s32 pad;
    s32 tex;
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    s16 *var_p = *(s16 **)((u8 *)arg1 + 0x174);
    MenuProgressGridVtx *v;
    s32 k;
    f32 mf[4][4];
    s8 sp12B;

    gDPPipeSync(g++);
    gSPDisplayList(g++, D_1000118);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x03024000);
    gDPSetPrimColor(g++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPSetCombine(g++, 0x121803, 0xFF0FFFFF);
    gSPMatrix(g++, D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    guTranslateF(mf, 8.0f, (f32) *var_p, 0.0f);
    guMtxF2L(mf, (Mtx *)((D_807444FC << 6) + D_800330D0));
    gSPMatrix(g++, (D_807444FC << 6) + D_800330D0, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 12, 2, 0);
    tex = texCacheFindOrLoad(0xA3);
    v = D_80033F10;
    i = 0;
    sp12B = 1;
    for (y = 0; y < 150; y += 30, i++) {
        j = 0;
        for (x = 0; x < 240; x += 30) {
            gDPPipeSync(g++);
            if (flagGet((s16)flagGridIndex(0x1FD, j, i), 0) != 0) {
                gDPSetPrimColor(g++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                sp12B = 0;
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
    if (sp12B != 0 && (D_8076A064 & 0x1F) < 0x14U) {
        tex = texCacheFindOrLoad(0x44);
        gDPSetPrimColor(g++, 0, 0, 0, 0xFF, 0, 0xFF);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x504240);
        gDPLoadTextureBlock(g++, tex, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP | G_TX_NOMIRROR,
                            G_TX_WRAP | G_TX_NOMIRROR, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
        gSP2Triangles(g++, 16, 17, 18, 0, 16, 18, 19, 0);
        if (*(s8 *)&D_80033258 == 0) {
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

void func_80025AE0(void) {
}
