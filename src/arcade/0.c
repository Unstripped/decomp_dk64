#include "common.h"

typedef struct ArcadeEntity {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    void *unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
} ArcadeEntity;

extern ArcadeEntity D_8004BCD0[];
extern ArcadeEntity D_8004C6D0;

extern s8 D_8004C71E;
extern u8 D_8004C71D;
extern u8 D_8004C71F;
extern u8 D_8004C721;
extern u8 D_8004C722;
extern u8 D_8004C724;
extern s32 D_8004C708;
extern s32 D_8004C6DC;
extern u8 D_8004A740;
extern u8 D_8004A76C;
extern s32 D_8004A308[];

void arcadeInitTitleScreen(void);
void arcadeDispatchEntities(void);
void arcadeDrawBackground(Gfx **);
void arcadeRenderEntities(Gfx **);
void arcadeRenderEntity(Gfx **, s32);
void arcadeInitStage(void);
#define ArcR1_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
Gfx *textDrawString(Gfx *, s32, s16, s16, char *);
extern s16 D_8004C72E;
extern s16 D_8004C732;
extern u8 D_8004C725;
extern u8 D_8004C726;
extern u8 D_8004C727;
extern u8 D_8004C728;

void controllerStartRead(void);
void controllerUpdate(void);
void schedSubmitGfxTask(Gfx *, s32, s32, s32, s32, s32);
Gfx *screenFadeUpdate(Gfx *, s32);
void func_805FE71C(Gfx *, u8, s32 *, s32);
void func_805FE7B4(Gfx *, u8 *, s32 *, s32);
Gfx *func_805FE4D4(Gfx *);
void arcadeDispatchState(Gfx **);
void arcadeBuildDisplayList(u8 *, Gfx **);

extern u8 D_807444FC;
extern Gfx *D_8076A050[];
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern s32 D_8076A064;
extern u8 *D_8076A048;
extern u8 D_80767CE8;
extern u8 D_8076A0B1;
extern f32 gScreenFadeProgress;
extern u8 D_807444EC;
extern void *D_8076A080;
extern Gfx D_1000090;
extern Gfx D_1000040;

void arcadeRunFrame(void) {
    Gfx *sp2C;
    u8 *sp28;

    controllerStartRead();
    schedSubmitGfxTask(D_8076A050[D_807444FC], D_8076A088, 3, 1, 0x4D2, 1);
    D_807444FC ^= 1;
    D_8076A064++;
    D_8076A048 = (u8 *)&D_80767CE8 + D_807444FC * 0x11B0;
    controllerUpdate();
    if ((D_8076A0B1 & 1) && gScreenFadeProgress == 31.0f) {
        sp2C = D_8076A050[D_807444FC];
    } else {
        arcadeBuildDisplayList(D_8076A048, &sp2C);
    }
    sp2C = screenFadeUpdate(sp2C, 0);
    if (D_807444EC != 3) {
        sp28 = D_8076A048 + 0xDB0;
        func_805FE71C(sp2C, D_807444FC, &D_8076A088, 0);
        func_805FE7B4((Gfx *)sp28, D_8076A048, &D_8076A08C, 1);
    } else {
        func_805FE71C(sp2C, D_807444FC, &D_8076A088, 1);
    }
}

void arcadeBuildDisplayList(u8 *arg0, Gfx **arg1) {
    Gfx *glist = D_8076A050[D_807444FC];

    gSPSegment(glist++, 0, 0);
    gSPSegment(glist++, 2, osVirtualToPhysical(arg0));
    gSPSegment(glist++, 1, osVirtualToPhysical(D_8076A080));
    gSPDisplayList(glist++, &D_1000090);
    gSPDisplayList(glist++, &D_1000040);
    gDPPipeSync(glist++);
    glist = func_805FE4D4(glist);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 6, 2, 0);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 4, 2, 0);
    gDPSetFillColor(glist++, 0x00050005);
    gDPFillRectangle(glist++, 0, 0, 319, 239);
    arcadeDispatchState(&glist);
    *arg1 = glist;
}
void func_8060C648(s32, s32, u8, s32, s32);
s32 func_8060C6B8(s32, s32, u8, s32);
void func_8060DEA8(void);
extern s32 D_8004A74C[5];
extern u8 D_8004A778[5][3];
extern s32 D_8004A760;

void arcadeSaveHighScores(void) {
    s32 i;
    u8 temp;

    for (i = 0; i < 5; i++) {
        temp = i;
        func_8060C648(0x15, 0, temp, 0, D_8004A74C[i]);
        func_8060C648(0x12, 0, temp, 0, D_8004A778[i][0]);
        func_8060C648(0x13, 0, temp, 0, D_8004A778[i][1]);
        func_8060C648(0x14, 0, temp, 0, D_8004A778[i][2]);
    }
    D_8004A760 = D_8004A74C[0];
    func_8060DEA8();
}

void arcadeLoadHighScores(void) {
    s32 i;
    u8 temp;

    for (i = 0; i < 5; i++) {
        temp = i;
        D_8004A74C[i] = func_8060C6B8(0x15, 0, temp, 0);
        D_8004A778[i][0] = func_8060C6B8(0x12, 0, temp, 0);
        D_8004A778[i][1] = func_8060C6B8(0x13, 0, temp, 0);
        D_8004A778[i][2] = func_8060C6B8(0x14, 0, temp, 0);
    }
    D_8004A760 = D_8004A74C[0];
}

extern u8 D_8004C725;
extern u8 D_8004C726;
extern u8 D_8004C727;
extern u8 D_8004C728;
void arcadeSetTextColor(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_8004C725 = arg0;
    D_8004C726 = arg1;
    D_8004C727 = arg2;
    D_8004C728 = arg3;
}

extern s32 D_8004C72C;
extern s32 D_8004C730;
void arcadeSetTextPosition(s32 arg0, s32 arg1) {
    D_8004C72C = arg0;
    D_8004C730 = arg1;
}

void arcadeDrawString(Gfx **arg0, char *arg1) {
    Gfx *g = *arg0;

    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200004);
    gDPSetPrimColor(g++, 0, 0, D_8004C725, D_8004C726, D_8004C727, D_8004C728);
    ArcR1_WRITE_GFX(g++, 0xFC119623, 0xFF2FFFFF);
    ArcR1_WRITE_GFX(g++, 0xE200001C, 0x00504240);
    *arg0 = textDrawString(g, 2, D_8004C72E, D_8004C732, arg1);
}

extern u32 D_8004A738;
s32 arcadeRand(void) {
    D_8004A738 = D_8004A738 * 0x41C64E6D + 0x3039;
    return (D_8004A738 >> 16) & 0x7FFF;
}

extern s32 D_8004A748;
extern u8 D_8004C71B;
extern u8 D_8004C71C;
void arcadeAddScore(s32 arg0) {
    s32 old = D_8004A748;
    D_8004A748 += arg0;
    if (D_8004A748 >= 0x2710 && old < 0x2710) {
        D_8004C71B++;
        D_8004C71C++;
    }
}

f32 arcadeMinFloat(f32 arg0, f32 arg1) {
    if (arg1 < arg0) {
        return arg1;
    }
    return arg0;
}


s32 arcadeFindFreeEntity(void) {
    s32 i;
    for (i = 0; i < 0x50; i++) {
        if (D_8004BCD0[i].unk18 == 0) {
            return i;
        }
    }
    return 0;
}

s32 arcadeFindFreeEntityAfterPlayer(void) {
    s32 i;
    for (i = D_8004C71F + 1; i < 0x50; i++) {
        if (D_8004BCD0[i].unk18 == 0) {
            return i;
        }
    }
    return 0;
}
s32 arcadeFindFreeEntityReverse(void) {
    s32 i;
    for (i = 0x4F; i >= 0; i--) {
        if (D_8004BCD0[i].unk18 == 0) {
            return i;
        }
    }
    return 0;
}

s32 func_800247F0(void) {
    s32 i;
    for (i = 0x27; i >= 0; i--) {
        if (D_8004BCD0[i].unk18 == 0) {
            return i;
        }
    }
    return 0;
}

s32 func_80024828(void) {
    s32 i;
    for (i = 0x24; i >= 0; i--) {
        if (D_8004BCD0[i].unk18 == 0) {
            return i;
        }
    }
    return 0;
}

s32 arcadeFindEntityByType(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x50; i++) {
        if (arg0 == D_8004BCD0[i].unk18) {
            return i;
        }
    }
    return -1;
}

s32 arcadeCountEntitiesByType(s32 arg0) {
    s32 i;
    s32 count = 0;
    for (i = 0; i < 0x50; i++) {
        if (arg0 == D_8004BCD0[i].unk18) {
            count++;
        }
    }
    return count;
}
void arcadeTitleLoop(Gfx **);
void arcadeStageIntroLoop(Gfx **);
void arcadeGameplayLoop(Gfx **);
void arcadePauseMenuLoop(Gfx **);
void arcadeAttractLoop(Gfx **);
void arcadeDemoLoop(Gfx **);
void arcadeDrawHud(Gfx **);
extern s32 D_8004A78C[];
extern s32 D_8004A790;
extern s32 D_8004C6D8;

void arcadeDispatchState(Gfx **arg0) {
    Gfx *sp1C = *arg0;

    if (D_8004A78C[0] != 0) {
        D_8004A78C[0] = 0;
        D_8004C722 = 1;
        arcadeInitTitleScreen();
        arcadeLoadHighScores();
    }
    switch (D_8004C724) {
    case 0:
        arcadeTitleLoop(&sp1C);
        break;
    case 1:
        arcadeStageIntroLoop(&sp1C);
        break;
    case 5:
        arcadeGameplayLoop(&sp1C);
        break;
    case 4:
        arcadePauseMenuLoop(&sp1C);
        break;
    case 3:
        arcadeAttractLoop(&sp1C);
        break;
    default:
        arcadeDemoLoop(&sp1C);
        break;
    }
    arcadeDrawHud(&sp1C);
    D_8004C6D8++;
    sp1C--;
    *arg0 = sp1C;
    D_8004A78C[1]++;
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80024A50.s")

extern ArcadeEntity D_8004A698;
extern u8 D_8004A774[3];
extern u8 D_8004C720;
void func_80024A50(s32);
void arcadeCheckGameOver(void) {
    u8 rank;
    u8 i;

    for (rank = 0; rank < 5; rank++) {
        if (D_8004A74C[rank] < D_8004A748) {
            func_80024A50(rank);
            break;
        }
    }
    for (i = 0; i < 3; i++) {
        D_8004A774[i] = 0x20;
    }
    D_8004C724 = 3;
    D_8004C722 = 0;
    D_8004C6DC = 0;
    for (i = 0; i < 0x50; i++) {
        D_8004C720 = 0;
        D_8004BCD0[i].unk18 = 0;
        D_8004BCD0[0] = D_8004A698;
        D_8004BCD0[0].unk1C = rank;
    }
}

s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
void func_805FF898(void);
void func_805FF378(s32, s32);
extern u8 D_8004A73C;
extern u8 D_8004A770;
void arcadeExit(void) {
    if (D_8004A73C == 0) {
        if (D_8004A770 != 0 && D_8004A740 != 0 && flagGet(0x84, 0) == 0) {
            if (flagGet(0x82, 0) != 0) {
                flagSet(0x11, 1, 2);
            } else {
                flagSet(0x10, 1, 2);
            }
        }
        if (D_8004A740 != 0) {
            func_805FF898();
        } else {
            func_805FF378(0x50, 0);
        }
        D_8004A73C = 1;
    }
}
void arcadeAttractLoop(Gfx **arg0) {
    Gfx *sp1C = *arg0;
    D_8004C6DC++;
    arcadeDrawBackground(&sp1C);
    arcadeDispatchEntities();
    arcadeRenderEntities(&sp1C);
    if (D_8004C6DC >= 0x7BD) {
        if (D_8004A740 != 0) {
            arcadeExit();
        } else {
            arcadeInitTitleScreen();
        }
    }
    *arg0 = sp1C;
}
extern ArcadeEntity D_8004A538;
extern u8 D_800424D0[];
void arcadeInitTitleScreen(void) {
    ArcadeEntity *e;
    s32 idx;

    D_8004C724 = 0;
    D_8004A740 = flagGet(0x63, 2);
    D_8004C722 = 0;
    D_8004C6DC = 0x200;
    D_8004C71D = 1;
    for (e = D_8004BCD0;;) {
        e->unk18 = 0;
        e++;
        if (e >= &D_8004C6D0) {
            break;
        }
    }
    idx = arcadeFindFreeEntity();
    D_8004BCD0[idx] = D_8004A538;
    D_8004BCD0[idx].unk14 = D_800424D0;
    D_8004BCD0[idx].unk0 = 138.0f;
    D_8004BCD0[idx].unk4 = 180.0f;
}

extern ArcadeEntity D_8004A4B8;
extern ArcadeEntity D_8004A4D8;
extern ArcadeEntity D_8004A4F8;
extern u8 D_8004C723;
extern u16 D_807ECD48;
void arcadeTitleLoop(Gfx **arg0) {
    Gfx *sp24;
    s32 i;
    s32 idx;

    sp24 = *arg0;
    D_8004C6DC++;
    arcadeDrawBackground(&sp24);
    if (D_8004C6DC & 0x200) {
        arcadeRenderEntities(&sp24);
    }
    if ((D_8004A740 != 0 && D_8004C6DC == 0x5FE) || (D_807ECD48 & 0x9000)) {
        D_8004A748 = 0;
        D_8004C723 = 0;
        D_8004C71B = 2;
        if (D_8004A740 != 0) {
            D_8004C71B = 0;
            if (flagGet(0x84, 0) != 0) {
                D_8004C723 = 8;
            } else if (flagGet(0x82, 0) != 0) {
                D_8004C723 = 4;
            }
        }
        if (D_8004C723 / 4 + 1 >= 10) {
            D_8004A76C = 9;
        } else {
            D_8004A76C = D_8004C723 / 4 + 1;
        }
        D_8004C71C = D_8004C71B + 1;
        D_8004C722 = 1;
        D_8004C724 = 1;
        D_8004C6DC = 0;
        D_8004C71D = 1;
        D_8004C721 = 0;
        for (i = 0; i < 0x50; i++) {
            D_8004BCD0[i].unk18 = 0;
        }
        idx = arcadeFindFreeEntity();
        D_8004BCD0[idx] = D_8004A4D8;
        idx = arcadeFindFreeEntity();
        D_8004BCD0[idx] = D_8004A4B8;
        idx = arcadeFindFreeEntity();
        D_8004BCD0[idx] = D_8004A538;
        if (D_8004A76C == 2 && D_8004A740 != 0) {
            idx = arcadeFindFreeEntity();
            D_8004BCD0[idx] = D_8004A4F8;
        }
        D_8004C708 = 0;
    }
    *arg0 = sp24;
}

void arcadeFinishStageIntro(void);
void arcadeStageIntroLoop(Gfx **arg0) {
    Gfx *sp1C = *arg0;
    arcadeDispatchEntities();
    arcadeDrawBackground(&sp1C);
    arcadeRenderEntities(&sp1C);
    if (D_8004C6DC++ >= 0x2F9) {
        arcadeFinishStageIntro();
    }
    *arg0 = sp1C;
}

extern s32 D_8004C714;
void arcadeSetStageMusic(void) {
    if (D_8004C722 == 1) {
        D_8004C714 = 0x4D;
    } else if (D_8004C722 == 2) {
        D_8004C714 = 0x4F;
    } else if (D_8004C722 == 4) {
        D_8004C714 = 0x4E;
    } else {
        D_8004C714 = -1;
    }
}

void n_alSndpStop(s32);
extern s32 D_80770DF8;
void arcadeStopSound(s32 arg0) {
    D_8004C714 = arg0;
    if (D_80770DF8 != 0) {
        n_alSndpStop(D_80770DF8);
    }
}

extern u8 D_8004BCE9[];
extern s32 D_8076D1F8;
s32 n_alSndpPlay(s32, s32, s32, s32, f32, s32, s32);
void arcadeOpenPauseMenu(void);
void arcadeSpawnStage4Enemies(void);
void arcadeSpawnStage2Enemies(void);
void arcadeGameplayLoop(Gfx **arg0) {
    Gfx *sp34 = *arg0;

    arcadeDrawBackground(&sp34);
    if ((D_8004C71E < 0xA) && ((D_8004C714 == 0x4D) || (D_8004C714 == 0x4E) || (D_8004C714 == 0x4F) || (D_8004C714 == -1))) {
        arcadeStopSound(0x48);
    }
    if ((D_80770DF8 == 0) && (D_8004C714 > 0)) {
        n_alSndpPlay(D_8076D1F8, (s16)D_8004C714, 0x7FFF, 0x3F, 1.0f, 0, (s32)&D_80770DF8);
    }
    if (D_8004A760 < D_8004A748) {
        D_8004A760 = D_8004A748;
    }
    if (D_8004C6DC++ == 0x3C) {
        D_8004C71C = D_8004C71B;
        D_8004C71D = 0;
        D_8004BCD0[arcadeFindEntityByType(0xD)].unk19 = 2;
    }
    arcadeDispatchEntities();
    arcadeRenderEntities(&sp34);
    if (D_8004C71D == 0) {
        if (D_8004C722 == 2) {
            arcadeSpawnStage2Enemies();
        }
        if (D_8004C722 == 4) {
            arcadeSpawnStage4Enemies();
        }
        if (D_807ECD48 & 0x1000) {
            arcadeOpenPauseMenu();
            D_8004C724 = 4;
        }
    }
    *arg0 = sp34;
}
extern ArcadeEntity D_8004A6B8;
extern u8 *D_807ECDE8;
extern s8 D_8004A768;
extern s32 D_8004C70C;
extern u8 D_8004A744;
s32 arcadeFindFreeEntityReverse(void);

void arcadeOpenPauseMenu(void) {
    s32 s4;
    s32 s0;
    f32 fs0;

    for (s4 = 0x60; s4 != 0xE0; s4 += 0x10) {
        fs0 = s4;
        for (s0 = 0x8C; s0 != 0xCC; s0 += 0x10) {
            s32 index = arcadeFindFreeEntityReverse();
            D_8004BCD0[index] = D_8004A6B8;
            D_8004BCD0[index].unk0 = fs0;
            D_8004BCD0[index].unk4 = s0;
        }
    }
    D_8004A768 = 0;
    D_8004C70C = (s8)D_807ECDE8[3];
    D_8004A744 = 0;
}

void arcadeClearEntitiesByType1C(void) {
    s32 index;
    do {
        index = arcadeFindEntityByType(0x1C);
        if (index >= 0) {
            D_8004BCD0[index].unk18 = 0;
        }
    } while (index >= 0);
}

void eepromInitConfigs(s32);
void arcadePauseMenuLoop(Gfx **arg0) {
    Gfx *sp2C;

    sp2C = *arg0;
    arcadeDrawBackground(&sp2C);
    arcadeRenderEntities(&sp2C);
    if ((D_807ECD48 & 0x800) || ((s8)D_807ECDE8[3] >= 0x1F && D_8004C70C < 0x1F)) {
        D_8004A768--;
    }
    if ((D_807ECD48 & 0x400) || ((s8)D_807ECDE8[3] < -0x1E && D_8004C70C >= -0x1E)) {
        D_8004A768++;
    }
    if (D_8004A768 >= 3) {
        D_8004A768 = 0;
    }
    if (D_8004A768 < 0) {
        D_8004A768 = 2;
    }
    D_8004C70C = (s8)D_807ECDE8[3];
    if (D_807ECD48 & 0x1000) {
        arcadeClearEntitiesByType1C();
        D_8004C724 = 5;
    }
    if (D_807ECD48 & 0xC000) {
        switch (D_8004A768) {
        case 0:
            arcadeClearEntitiesByType1C();
            D_8004C724 = 5;
            break;
        case 1:
            if (D_8004A744 == 0) {
                eepromInitConfigs(2);
                arcadeLoadHighScores();
                arcadeSaveHighScores();
                if (D_8004A760 < D_8004A748) {
                    D_8004A760 = D_8004A748;
                }
                D_8004A744 = 1;
            }
            break;
        case 2:
            arcadeExit();
            break;
        }
    }
    *arg0 = sp2C;
}

extern ArcadeEntity D_8004A5D8;
extern f32 D_8004BCD4;
extern s32 D_8004C6D4;
void arcadeFinishStageIntro(void) {
    ArcadeEntity *e;
    s32 i;
    s32 idx;
    s32 rank;

    for (e = (ArcadeEntity *)((u8 *)&D_8004BCD4 - 4);;) {
        e->unk18 = 0;
        e++;
        if ((u8 *)e >= (u8 *)&D_8004C6D4 - 4) {
            break;
        }
    }
    for (i = 0; i < (D_8004C723 & 3) + 1; i++) {
        idx = arcadeFindFreeEntity();
        D_8004BCD0[idx] = D_8004A5D8;
        D_8004BCD0[idx].unk4 -= i * 0x20;
    }
    D_8004C6DC = 0;
    rank = D_8004C723 / 4 + 1;
    if (rank >= 10) {
        D_8004A76C = 9;
    } else {
        D_8004A76C = rank;
    }
    n_alSndpPlay(D_8076D1F8, 0x47, 0x7FFF, 0x3F, 1.0f, 0, 0);
    D_8004C724 = 2;
    D_8004C71D = 1;
}

void arcadeDemoLoop(Gfx **arg0) {
    Gfx *sp1C = *arg0;
    arcadeDrawBackground(&sp1C);
    arcadeRenderEntities(&sp1C);
    if (D_8004C6DC++ >= 0xA1) {
        arcadeInitStage();
        D_8004C724 = 5;
    }
    *arg0 = sp1C;
}

extern s16 D_8004C6D6;
extern u8 D_80032B48[];
extern u8 D_80032B90[];
extern u8 D_80032BD8[];
extern u8 D_8004BB30[];
extern u8 D_8004BB60[];
extern u8 D_8004BB90[];
extern u8 D_8004BBC0[];
#define ArcR2_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
void arcadeDrawTitleText(Gfx **);
void arcadeDrawStage1Background(Gfx **);
void arcadeDrawStage2Background(Gfx **);
void func_800275E8(Gfx **);
void arcadeDrawStage4Background(Gfx **);
typedef struct ArcR2_Entity {
    void *ptr;
} ArcR2_Entity;
typedef struct ArcadeTitleBitmap {
    s32 words[12];
} ArcadeTitleBitmap;
extern ArcadeTitleBitmap D_8004A798;
extern u8 D_8004C719;
extern u8 D_8004C71A;
extern u8 D_807444FC;
extern u8 D_8004BB00[];
extern u8 D_80032C20[];
extern u8 D_80032DF8[];
void func_80005A90(void *, void *, s32, u8, u8, u8, s32, s32, s32, s32);
void dlAppendTextureLoad(Gfx **, void *);
void func_8070F2C8(s32, s16, s32, u8);
void arcadeDrawLadder(Gfx **, s32, s32, s32);
void dlAppendTextureRectangle(Gfx **, s16, s16);
void arcadeStopSound(s32);
extern s32 D_8076D1F8;
void arcadeDrawBackground(Gfx **arg0) {
    Gfx *sp4C;

    sp4C = *arg0;
    ArcR2_WRITE_GFX(sp4C++, 0xE2001E01, 0);
    ArcR2_WRITE_GFX(sp4C++, 0xE3000C00, 0);
    ArcR2_WRITE_GFX(sp4C++, 0xE3001201, 0x2000);
    ArcR2_WRITE_GFX(sp4C++, 0xE3001402, 0xC00);
    ArcR2_WRITE_GFX(sp4C++, 0xE3000D01, 0);
    ArcR2_WRITE_GFX(sp4C++, 0xE3000F00, 0);
    ArcR2_WRITE_GFX(sp4C++, 0xE3001001, 0);
    ArcR2_WRITE_GFX(sp4C++, 0xFA000000, 0xFFFFFFFF);
    ArcR2_WRITE_GFX(sp4C++, 0xE200001C, 0x504240);
    ArcR2_WRITE_GFX(sp4C++, 0xFC11FE23, 0xFFFFF3F9);
    ArcR2_WRITE_GFX(sp4C++, 0xED0C0090, 0x4403A0);

    switch (D_8004C724) {
    case 0:
        if (D_8004C6DC & 0x200) {
            arcadeDrawTitleText(&sp4C);
        }
        break;
    case 1:
    case 4:
    case 5:
        switch (D_8004C722) {
        case 1:
            arcadeDrawStage1Background(&sp4C);
            break;
        case 2:
            arcadeDrawStage2Background(&sp4C);
            break;
        case 3:
            func_800275E8(&sp4C);
            break;
        default:
            arcadeDrawStage4Background(&sp4C);
            break;
        }
        break;
    }
    *arg0 = sp4C;
}

#define ArcA1_D6D0 (*(void **)&D_8004C6D0)
void arcadeDrawLadder(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    Gfx *sp60;

    D_8004C719 = 8;
    D_8004C71A = 4;
    D_8004C6D4 = 0x400;
    if (D_8004C722 == 2) ArcA1_D6D0 = D_80032B90;
    else if (D_8004C722 == 4) ArcA1_D6D0 = D_80032BD8;
    else ArcA1_D6D0 = D_80032B48;
    func_80005A90(D_8004BB30 + D_807444FC * 0x18, ArcA1_D6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_80005A90(D_8004BB60 + D_807444FC * 0x18, ArcA1_D6D0, 0, D_8004C719, D_8004C719, 1, 0, 2, 0, 0);
    func_80005A90(D_8004BB90 + D_807444FC * 0x18, ArcA1_D6D0, 0, D_8004C719, D_8004C719, 2, 0, 2, 0, 0);
    func_80005A90(D_8004BBC0 + D_807444FC * 0x18, ArcA1_D6D0, 0, D_8004C719, D_8004C719, 3, 0, 2, 0, 0);
    sp60 = *arg0;
    dlAppendTextureLoad(&sp60, D_8004BB30 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    for (i = 0; i < arg3 / 4; i++) {
        dlAppendTextureRectangle(&sp60, arg1 * 4, (s32)((f64)(i * 4 + arg2 + 8) * 4.0));
    }
    D_8004C71A = arg3 % 4;
    if (D_8004C71A != 0) {
        switch (D_8004C71A) {
        case 1:
            dlAppendTextureLoad(&sp60, D_8004BB60 + D_807444FC * 0x18);
            break;
        case 2:
            dlAppendTextureLoad(&sp60, D_8004BB90 + D_807444FC * 0x18);
            break;
        case 3:
            dlAppendTextureLoad(&sp60, D_8004BBC0 + D_807444FC * 0x18);
            break;
        }
        func_8070F2C8(0x400, D_8004C6D6, 0, 0);
        dlAppendTextureRectangle(&sp60, arg1 * 4, (s32)((f64)(i * 4 + arg2 + 8) * 4.0));
    }
    *arg0 = sp60;
}

void arcadeDrawStage1Ladders(Gfx **arg0) {
    Gfx *sp2C;
    s32 sp28;

    sp2C = *arg0;
    arcadeDrawLadder(&sp2C, 0x70, 0x1C, 0x2E);
    arcadeDrawLadder(&sp2C, 0x80, 0x1C, 0x2E);
    arcadeDrawLadder(&sp2C, 0xB0, 0x38, 0x12);
    if (D_8004C724 == 1) {
        if (D_8004C6DC < 0x190) {
            sp28 = 0x82 - (((s32) (D_8004C6DC - 0x3C) / 20) * 8);
            if (sp28 >= 0x83) {
                sp28 = 0x82;
            }
            if (sp28 < 0x22) {
                sp28 = 0x22;
            }
            arcadeDrawLadder(&sp2C, 0xA0, 0x51, sp28);
            arcadeDrawLadder(&sp2C, 0xB0, 0x51, sp28);
        }
    } else {
        arcadeDrawLadder(&sp2C, 0x88, 0x50, 4);
        arcadeDrawLadder(&sp2C, 0x88, 0x5B, 0xC);
        arcadeDrawLadder(&sp2C, 0xE8, 0x53, 0xE);
        arcadeDrawLadder(&sp2C, 0x50, 0x70, 0xE);
        arcadeDrawLadder(&sp2C, 0x78, 0x6E, 0x12);
        arcadeDrawLadder(&sp2C, 0xD8, 0x69, 8);
        arcadeDrawLadder(&sp2C, 0xD8, 0x7D, 8);
        arcadeDrawLadder(&sp2C, 0x70, 0x87, 5);
        arcadeDrawLadder(&sp2C, 0x70, 0x99, 8);
        arcadeDrawLadder(&sp2C, 0xA8, 0x89, 0x16);
        arcadeDrawLadder(&sp2C, 0xE8, 0x8D, 0xE);
        arcadeDrawLadder(&sp2C, 0x50, 0xAA, 0xE);
        arcadeDrawLadder(&sp2C, 0x90, 0xA6, 0x15);
        arcadeDrawLadder(&sp2C, 0x80, 0xC1, 4);
        arcadeDrawLadder(&sp2C, 0x80, 0xD1, 8);
        arcadeDrawLadder(&sp2C, 0xE8, 0xC7, 0xE);
    }
    *arg0 = sp2C;
}

void arcadeDrawStage2Ladders(Gfx **arg0) {
    Gfx *sp24;

    sp24 = *arg0;
    arcadeDrawLadder(&sp24, 0x38, 0xBD, 0x1C);
    arcadeDrawLadder(&sp24, 0x100, 0xBD, 0x1C);
    arcadeDrawLadder(&sp24, 0x40, 0x9B, 0x1C);
    arcadeDrawLadder(&sp24, 0xF8, 0x9B, 0x1C);
    arcadeDrawLadder(&sp24, 0x48, 0x7A, 0x1A);
    arcadeDrawLadder(&sp24, 0xF0, 0x7A, 0x1A);
    arcadeDrawLadder(&sp24, 0x50, 0x58, 0x1C);
    arcadeDrawLadder(&sp24, 0xE8, 0x58, 0x1C);
    if (D_8004C708 == 0) {
        arcadeDrawLadder(&sp24, 0x98, 0xBD, 0x1C);
        arcadeDrawLadder(&sp24, 0x78, 0x9B, 0x1C);
        arcadeDrawLadder(&sp24, 0xC0, 0x9B, 0x1C);
        arcadeDrawLadder(&sp24, 0x98, 0x7A, 0x1A);
        arcadeDrawLadder(&sp24, 0x70, 0x58, 0x1C);
        arcadeDrawLadder(&sp24, 0xC8, 0x58, 0x1C);
    }
    *arg0 = sp24;
}

void arcadeDrawStage3Ladders(Gfx **arg0) {
    Gfx *sp24;

    sp24 = *arg0;
    arcadeDrawLadder(&sp24, 0x70, 0x1C, 0x31);
    arcadeDrawLadder(&sp24, 0x80, 0x1C, 0x31);
    arcadeDrawLadder(&sp24, 0xB0, 0x38, 0x15);
    arcadeDrawLadder(&sp24, 0xD0, 0x54, 0x15);
    arcadeDrawLadder(&sp24, 0x100, 0x62, 0x1C);
    arcadeDrawLadder(&sp24, 0xB8, 0x77, 0x15);
    arcadeDrawLadder(&sp24, 0x40, 0x7E, 0x2A);
    arcadeDrawLadder(&sp24, 0x70, 0x7E, 0x38);
    arcadeDrawLadder(&sp24, 0x80, 0x7E, 0x38);
    arcadeDrawLadder(&sp24, 0xE8, 0x85, 0x15);
    arcadeDrawLadder(&sp24, 0x100, 0xA8, 0xE);
    arcadeDrawLadder(&sp24, 0x38, 0xAF, 0x1C);
    *arg0 = sp24;
}

void arcadeDrawStage4Ladders(Gfx **arg0) {
    Gfx *sp24;

    sp24 = *arg0;
    arcadeDrawLadder(&sp24, 0x70, 0x1C, 0x31);
    arcadeDrawLadder(&sp24, 0x80, 0x1C, 0x31);
    arcadeDrawLadder(&sp24, 0xB0, 0x38, 0x15);
    arcadeDrawLadder(&sp24, 0x48, 0xBD, 0x1C);
    arcadeDrawLadder(&sp24, 0x80, 0xBD, 0x1C);
    arcadeDrawLadder(&sp24, 0xB8, 0xBD, 0x1C);
    arcadeDrawLadder(&sp24, 0xF0, 0xBD, 0x1C);
    arcadeDrawLadder(&sp24, 0x70, 0x9A, 0x1C);
    arcadeDrawLadder(&sp24, 0xC0, 0x9A, 0x1C);
    arcadeDrawLadder(&sp24, 0x48, 0x77, 0x1C);
    arcadeDrawLadder(&sp24, 0x80, 0x77, 0x1C);
    arcadeDrawLadder(&sp24, 0xB8, 0x77, 0x1C);
    arcadeDrawLadder(&sp24, 0xF0, 0x77, 0x1C);
    arcadeDrawLadder(&sp24, 0x40, 0x62, 0xE);
    arcadeDrawLadder(&sp24, 0xF8, 0x62, 0xE);
    *arg0 = sp24;
}

#define ArcA1_P6D0 (*(void **)&D_8004C6D0)
void arcadeDrawTitleText(Gfx **arg0) {
    s32 row;
    s32 j;
    Gfx *sp94;
    ArcadeTitleBitmap sp64;
    s32 i;

    sp64 = D_8004A798;
    sp94 = *arg0;
    D_8004C719 = 8;
    D_8004C71A = 8;
    D_8004C6D4 = 0x400;
    if (D_8004C6DC & 0x182) ArcA1_P6D0 = D_80032C20;
    else ArcA1_P6D0 = D_80032DF8;
    func_80005A90(D_8004BB00 + D_807444FC * 0x18, ArcA1_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&sp94, D_8004BB00 + D_807444FC * 0x18);
    func_8070F2C8(0x400, ((s16 *)&D_8004C6D4)[1], 0, 0);
    for (i = 0; i < 12; i++) {
        row = sp64.words[i];
        for (j = 0; j < 25; j++) {
            if ((1 << j) & row) {
                dlAppendTextureRectangle(&sp94, 0x3E0 - (j << 5), (s32)((f64)(i * 8 + 0x3F) * 4.0));
            }
        }
    }
    *arg0 = sp94;
}

#define ArcL1_P6D0 (*(void **)&D_8004C6D0)
extern u8 D_80034568[];
void arcadeDrawStage1Background(Gfx **arg0) {
    s32 i;
    Gfx *sp68;

    D_8004C719 = 8;
    D_8004C71A = 0xA;
    D_8004C6D4 = 0x492;
    ArcL1_P6D0 = D_80034568;
    func_80005A90(D_8004BB00 + D_807444FC * 0x18, ArcL1_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    sp68 = *arg0;
    dlAppendTextureLoad(&sp68, D_8004BB00 + D_807444FC * 0x18);
    func_8070F2C8(0x400, ((s16 *)&D_8004C6D4)[1], 0, 0);
    for (i = 0; i < 6; i++) {
        dlAppendTextureRectangle(&sp68, i * 0x20 + 0x220, 0xE0);
    }
    if (D_8004C708 >= 6) {
        for (i = 0; i < 0xE; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, 0x380);
        }
        for (i = 0xE; i < 0x1C; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, (s32)((((f64)(0xF7 - ((i - 0xC) / 2)) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 0; i < 0x1C; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, 0x368);
        }
    }
    if (D_8004C708 >= 5) {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, (s32)((((f64)((i / 2) + 0xCF) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, 0x2F4);
        }
    }
    if (D_8004C708 >= 4) {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, (s32)((((f64)(0xBB - (i / 2)) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, 0x281);
        }
    }
    if (D_8004C708 >= 3) {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, (s32)((((f64)((i / 2) + 0x8D) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, 0x20D);
        }
    }
    if (D_8004C708 >= 2) {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, (s32)((((f64)(0x79 - (i / 2)) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 2; i < 0x1C; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, 0x19A);
        }
    }
    if (D_8004C708 > 0) {
        for (i = 0; i < 0x12; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, 0x142);
        }
        for (i = 0x12; i < 0x1A; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, (s32)((((f64)(((i - 0x10) / 2) + 0x53) * 0.875) + 8.0) * 4.0));
        }
    } else {
        for (i = 0; i < 0x1A; i++) {
            dlAppendTextureRectangle(&sp68, i * 0x20 + 0xC0, 0x142);
        }
    }
    arcadeDrawStage1Ladders(&sp68);
    *arg0 = sp68;
}

#define ArcA1_P6D0 (*(void **)&D_8004C6D0)
extern u8 D_80032F18[];
extern u8 D_8004BC50[];
void arcadeDrawStage2Background(Gfx **arg0) {
    s32 i;
    Gfx *sp60;

    sp60 = *arg0;
    if (D_8004C708 < 2) {
        D_8004C719 = 2;
        D_8004C71A = 8;
        D_8004C6D4 = 0x400;
        ArcA1_P6D0 = D_80032F18;
        func_80005A90(D_8004BC50 + (D_807444FC * 3 * 8), ArcA1_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
        dlAppendTextureLoad(&sp60, D_8004BC50 + (D_807444FC * 3 * 8));
        func_8070F2C8(0x400, D_8004C6D6, 0, 0);
        for (i = 0; i < 4; i++) {
            dlAppendTextureRectangle(&sp60, 0x1DC, (s32)((f64)(s32)((f64)(i * 8) + 51.625 + 8.0) * 4.0));
        }
        for (i = 0; i < 4; i++) {
            dlAppendTextureRectangle(&sp60, 0x31C, (s32)((f64)(s32)((f64)(i * 8) + 51.625 + 8.0) * 4.0));
        }
    }
    D_8004C719 = 8;
    D_8004C71A = 8;
    D_8004C6D4 = 0x400;
    ArcA1_P6D0 = D_80032C20;
    func_80005A90(D_8004BB00 + (D_807444FC * 3 * 8), ArcA1_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&sp60, D_8004BB00 + (D_807444FC * 3 * 8));
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    for (i = 0; i < 0x1C; i++) {
        dlAppendTextureRectangle(&sp60, i * 0x20 + 0xC0, 0x380);
    }
    if (D_8004C708 == 0) {
        for (i = 1; i < 0x1B; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&sp60, (i << 5) + 0xC0, 0x2F8);
            }
        }
        for (i = 2; i < 0x1A; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&sp60, (i << 5) + 0xC0, 0x270);
            }
        }
        for (i = 3; i < 0x19; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&sp60, (i << 5) + 0xC0, 0x1EC);
            }
        }
        for (i = 4; i < 0x18; i++) {
            if (i != 7 && i != 0x14) {
                dlAppendTextureRectangle(&sp60, (i << 5) + 0xC0, 0x164);
            }
        }
    } else {
        for (i = 8; i < 0x14; i++) {
            dlAppendTextureRectangle(&sp60, i * 0x20 + 0xC0, 0x360);
            dlAppendTextureRectangle(&sp60, i * 0x20 + 0xC0, 0x340);
            dlAppendTextureRectangle(&sp60, i * 0x20 + 0xC0, 0x320);
            dlAppendTextureRectangle(&sp60, i * 0x20 + 0xC0, 0x300);
        }
        for (i = 1; i < 0x1B; i++) {
            if (i < 7 || i >= 0x15) {
                dlAppendTextureRectangle(&sp60, (i << 5) + 0xC0, 0x2F8);
            }
        }
        for (i = 2; i < 0x1A; i++) {
            if (i < 7 || i >= 0x15) {
                dlAppendTextureRectangle(&sp60, (i << 5) + 0xC0, 0x270);
            }
        }
        for (i = 3; i < 0x19; i++) {
            if (i < 7 || i >= 0x15) {
                dlAppendTextureRectangle(&sp60, (i << 5) + 0xC0, 0x1EC);
            }
        }
        for (i = 4; i < 0x18; i++) {
            if (i < 7 || i >= 0x15 || D_8004C708 == 2) {
                dlAppendTextureRectangle(&sp60, (i << 5) + 0xC0, 0x164);
            }
        }
    }
    if (D_8004C708 < 2) {
        for (i = 0; i < 0xE; i++) {
            dlAppendTextureRectangle(&sp60, i * 0x20 + 0x1A0, 0xD8);
        }
    }
    arcadeDrawStage2Ladders(&sp60);
    *arg0 = sp60;
}

void arcadeDrawGirderSpan(Gfx **arg0, u8 arg1, u8 arg2, s16 arg3) {
    u8 i;
    Gfx *sp40;

    sp40 = *arg0;
    for (i = arg1; i < arg2; i++) {
        dlAppendTextureRectangle(&sp40, ((i << 5) + 0xC0), (s32)((((f64) arg3 * 0.875) + 8.0) * 4.0));
    }
    *arg0 = sp40;
}

#ifdef NON_MATCHING
#define ArcA1_P6D0 (*(void **)&D_8004C6D0)
typedef struct ArcadeGirderSpan {
    u8 x;
    u8 y;
    s16 z;
} ArcadeGirderSpan;
typedef struct ArcA1_Bar {
    f32 x;
    f32 y;
    f32 vy;
} ArcA1_Bar;
extern ArcA1_Bar D_8004BC88[];
extern u8 D_80032F40[];
extern ArcadeGirderSpan D_8004A7C8[];
extern u8 D_8004BC50[];
void func_800275E8(Gfx **arg0) {
    s32 i;
    s32 j;
    s32 n;
    Gfx *sp90;
    ArcadeGirderSpan *pt;
    ArcA1_Bar *bar;

    sp90 = *arg0;
    D_8004C719 = 2;
    D_8004C71A = 8;
    D_8004C6D4 = 0x400;
    ArcA1_P6D0 = D_80032F40;
    func_80005A90(D_8004BC50 + D_807444FC * 0x18, ArcA1_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&sp90, D_8004BC50 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    for (j = 5; j < 0x14; j++) {
        dlAppendTextureRectangle(&sp90, 0x15C, (s32)((f64)(s32)((f64)(j * 8) + 51.625 + 8.0) * 4.0));
    }
    for (j = 5; j < 0x14; j++) {
        dlAppendTextureRectangle(&sp90, 0x25C, (s32)((f64)(s32)((f64)(j * 8) + 51.625 + 8.0) * 4.0));
    }
    D_8004C719 = 8;
    D_8004C71A = 0xA;
    D_8004C6D4 = 0x492;
    ArcA1_P6D0 = D_80034568;
    func_80005A90(D_8004BB00 + D_807444FC * 0x18, ArcA1_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&sp90, D_8004BB00 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    n = 21;
    pt = D_8004A7C8;
    for (i = 0; i < n; i++) {
        arcadeDrawGirderSpan(&sp90, pt[i].x, pt[i].y, pt[i].z);
    }
    for (bar = D_8004BC88;;) {
        if (D_8004C71D == 0 && D_8004C724 == 5) {
            bar->y = bar->y + bar->vy;
            if (bar->y < 99.0f) {
                bar->y = bar->y + 144.0f;
            }
            if (bar->y > 243.0f) {
                bar->y = bar->y - 144.0f;
            }
        }
        for (j = 0; j < 2; j++) {
            dlAppendTextureRectangle(&sp90, (s32)((bar->x + 40.0f + (f32)(j * 8)) * 4.0f), (s32)(((f64)bar->y * 0.875 + 8.0) * 4.0));
        }
        bar++;
        if (bar == (ArcA1_Bar *)D_8004BCD0) break;
    }
    arcadeDrawStage3Ladders(&sp90);
    *arg0 = sp90;
}
#else

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800275E8.s")
#endif

#define ArcA3_P6D0 (*(void **)&D_8004C6D0)
extern u8 D_80032CA8[];
extern u8 D_80032D50[];
extern u8 D_800342B8[];
extern u8 D_8004BC20[];
void arcadeDrawStage4Background(Gfx **arg0) {
    s32 step;
    s32 one;
    Gfx *sp6C;
    s32 x;
    s32 i;

    sp6C = *arg0;
    step = 0x20;
    one = 1;
    D_8004C719 = 8;
    D_8004C71A = 0xA;
    D_8004C6D4 = 0x492;
    ArcA3_P6D0 = D_80032D50;
    func_80005A90(D_8004BB00 + D_807444FC * 0x18, ArcA3_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&sp6C, D_8004BB00 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    x = 0x220;
    do {
        dlAppendTextureRectangle(&sp6C, x, 0xE0);
        x += step;
    } while (x < 0x2E0);
    x = 0xC0;
    do {
        dlAppendTextureRectangle(&sp6C, x, 0x380);
        x += step;
    } while (x < 0x440);
    i = 1;
    do {
        if (i != 6 && i != 7 && i != 0x13 && i != 0x14) {
            dlAppendTextureRectangle(&sp6C, ((i << 5) + 0xC0), 0x268);
        }
        i += one;
    } while (i < 0x1B);
    ArcA3_P6D0 = D_80032CA8;
    func_80005A90(D_8004BC20 + D_807444FC * 0x18, ArcA3_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&sp6C, D_8004BC20 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    x = 0xE0;
    do {
        dlAppendTextureRectangle(&sp6C, x, 0x150);
        x += step;
    } while (x < 0x420);
    i = 0;
    do {
        if (i < 0xC || i >= 0x10) {
            dlAppendTextureRectangle(&sp6C, ((i << 5) + 0xC0), 0x1DC);
        }
        i += one;
    } while (i < 0x1C);
    x = 0xE0;
    do {
        dlAppendTextureRectangle(&sp6C, x, 0x2F4);
        x += step;
    } while (x < 0x420);
    ArcA3_P6D0 = D_800342B8;
    func_80005A90(D_8004BC50 + D_807444FC * 0x18, ArcA3_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&sp6C, D_8004BC50 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    x = 0x240;
    do {
        for (i = 0x9F; (i ^ 0) != 0x87; i -= 8) { // FAKE: no-op `^ 0` steers codegen
            dlAppendTextureRectangle(&sp6C, x, (s32)((((f64)i * 0.875) + 8.0) * 4.0));
        }
        x += step;
    } while (x != 0x2C0);
    arcadeDrawStage4Ladders(&sp6C);
    *arg0 = sp6C;
}

void arcadeKillPlayer(void) {
    arcadeStopSound(0);
    n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
    D_8004BCD0[D_8004C71F].unk19 = 8;
    D_8004BCD0[D_8004C71F].unk8 = 0.0f;
    D_8004BCD0[D_8004C71F].unk10 = 0.0f;
    D_8004C71D = 1;
}

extern ArcadeEntity D_8004A398;
extern ArcadeEntity D_8004A438;
extern ArcadeEntity D_8004A458;
extern ArcadeEntity D_8004A518;
extern ArcadeEntity D_8004A558;
extern ArcadeEntity D_8004A638;
extern ArcadeEntity D_8004A718;
extern ArcadeEntity D_8004C170;
void arcadeSpawnStage1Entities(void) {
    float new_var;
    s32 i;

    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4D8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4B8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A518;
    new_var = 110.0f;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A558;
    if (D_8004A76C == 2 && D_8004A740 != 0) {
        D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4F8;
    }
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A438;
    D_8004C71F = arcadeFindFreeEntity();
    D_8004BCD0[D_8004C71F] = D_8004A398;
    D_8004C170 = D_8004A458;
    i = D_8004C71F & 0; // FAKE: `& 0` load steers codegen (i = 0)
    i = i + 0x24;
    D_8004BCD0[i--] = D_8004A638;
    D_8004BCD0[i] = D_8004A638;
    D_8004BCD0[i].unk0 = 68.0f;
    D_8004BCD0[i].unk4 = new_var;
    i--;
    D_8004BCD0[i] = D_8004A718;
    i--;
    D_8004BCD0[i] = D_8004A718;
    D_8004BCD0[i].unk1C = 1;
    D_8004BCD0[i].unk0 = 48.0f;
    i--;
    D_8004BCD0[i] = D_8004A718;
    D_8004BCD0[i].unk1C = 2; D_8004BCD0[i].unk4 = 65.0f; i--;
    D_8004BCD0[i] = D_8004A718;
    D_8004BCD0[i].unk1C = 3;
    D_8004BCD0[i].unk0 = 48.0f;
    D_8004BCD0[i].unk4 = 65.0f;
    D_8004C708 = 7;
}

typedef struct ArcadePosTable {
    u8 b[16];
} ArcadePosTable;
extern ArcadePosTable D_8004A81C;
extern ArcadeEntity D_8004A578;
extern ArcadeEntity D_8004A618;
extern ArcadeEntity D_8004A658;
extern ArcadeEntity D_8004C150;
extern ArcadeEntity D_8004C130;
extern ArcadeEntity D_8004C110;
extern ArcadeEntity D_8004C0F0;
extern u8 D_800335D8[];
extern u8 D_80038FE8[];
extern u8 D_800391F0[];
void arcadeSpawnStage2Entities(void) {
    s32 bit;
    s32 idx;
    s32 i;
    ArcadePosTable tbl;

    tbl = D_8004A81C;
    bit = 1;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4D8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4B8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A518;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A578;
    if (D_8004A76C == 2 && D_8004A740 != 0) {
        D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4F8;
    }
    for (i = 0; i < 8; i++) {
        idx = arcadeFindFreeEntity();
        D_8004BCD0[idx] = D_8004A658;
        D_8004BCD0[idx].unk0 = (u32)tbl.b[i * 2];
        D_8004BCD0[idx].unk4 = (u32)tbl.b[i * 2 + 1];
        D_8004BCD0[idx].unk1C = bit;
        bit = bit * 2;
    }
    idx = arcadeFindFreeEntity();
    D_8004BCD0[idx] = D_8004A438;
    D_8004BCD0[idx].unk14 = D_800335D8;
    D_8004C71F = arcadeFindFreeEntity();
    D_8004BCD0[D_8004C71F] = D_8004A398;
    D_8004C170 = D_8004A618;
    D_8004BCD0[0x25].unk14 = D_80038FE8;
    D_8004C150 = D_8004A618;
    D_8004BCD0[0x24].unk0 = 252.0f;
    D_8004BCD0[0x24].unk4 = 208.0f;
    D_8004C130 = D_8004A618;
    D_8004BCD0[0x23].unk14 = D_800391F0;
    D_8004BCD0[0x23].unk0 = 84.0f;
    D_8004BCD0[0x23].unk4 = 93.0f;
    D_8004C110 = D_8004A638;
    D_8004BCD0[0x22].unk0 = 60.0f;
    D_8004BCD0[0x22].unk4 = 152.0f;
    D_8004C0F0 = D_8004A638;
    D_8004BCD0[0x21].unk0 = 156.0f;
    D_8004BCD0[0x21].unk4 = 114.0f;
}

extern s32 D_8004C6E0;
extern s32 D_8004C6E4;
extern s32 D_8004C6E8;
extern s32 D_8004C6EC;
extern s32 D_8004C6F0;
extern s32 D_8004C6F4;
extern s32 D_8004C6F8;


s32 arcadeCheckStage1Collision(s32, s32);
s32 arcadeCheckStage2Collision(s32, s32);
s32 arcadeCheckStage3Collision(s32, s32);
s32 arcadeCheckStage4Collision(s32, s32);


s32 arcadeCheckStage1Ladders(s32, s32);
s32 arcadeCheckStage2Ladders(s32, s32);
s32 arcadeCheckStage3Ladders(s32, s32);
s32 arcadeCheckStage4Ladders(s32, s32);


void func_80005A90(void *, void *, s32, u8, u8, u8, s32, s32, s32, s32);
void func_8070F2C8(s32, s16, s32, u8);
extern u8 D_8004A338[];
extern u8 D_8004A358[];
extern u8 D_8004A378[];
extern u8 D_8004AC00[];
extern u8 D_807444FC;

extern f32 D_8004BCF4;

extern u8 D_80034610[];
extern u8 D_80034818[];
extern u8 D_80034A20[];
extern u8 D_80034C28[];
extern u8 D_80034E30[];
extern u8 D_80035038[];
extern u8 D_80035240[];
extern u8 D_80035448[];
extern u8 D_80035650[];
extern u8 D_80035898[];
extern u8 D_80035AE0[];
extern u8 D_80035CE8[];


extern u8 D_8004A788[];
extern s32 D_8004C710;
extern u8 D_8004C718;
extern u8 D_8004A764;

void arcadeSpawnStage1Entities(void);
void arcadeSpawnStage2Entities(void);
void arcadeSpawnStage3Entities(void);
void arcadeSpawnStage4Entities(void);

extern ArcadeEntity D_8004A478;
extern ArcadeEntity D_8004A598;
extern ArcadeEntity D_8004A3D8;
typedef struct ArcadeLift {
    f32 x;
    f32 y;
    f32 vy;
} ArcadeLift;
#ifndef NON_MATCHING
extern ArcadeLift D_8004BC88[];
#endif
void arcadeSpawnStage3Entities(void) {
    s32 i;
    ArcadeEntity *p;
    f32 t;

    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4D8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4B8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A518;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A598;
    if (D_8004A76C == 2 && D_8004A740 != 0) {
        D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4F8;
    }
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A438;
    D_8004C71F = arcadeFindFreeEntity();
    D_8004BCD0[D_8004C71F] = D_8004A398;
    D_8004BCD0[D_8004C71F].unk0 = 56.0f;
    D_8004BCD0[D_8004C71F].unk4 = 231.0f;
    D_8004C170 = D_8004A478;
    i = D_8004C71F & 0; // FAKE: `& 0` load steers codegen (i = 0)
    i = i + 0x24;
    p = &D_8004BCD0[i];
    *p = D_8004A478;
    p->unk0 = 144.0f;
    i--;
    p = &D_8004BCD0[i];
    *p = D_8004A478;
    p->unk1B = 1;
    p->unk4 = 238.0f;
    i--;
    p = &D_8004BCD0[i];
    *p = D_8004A478;
    p->unk1B = 1;
    p->unk0 = 144.0f;
    p->unk4 = 238.0f;
    i--;
    p = &D_8004BCD0[i];
    *p = D_8004A618;
    p->unk14 = D_80038FE8;
    p->unk0 = 260.0f;
    p->unk4 = 103.0f;
    i--;
    p = &D_8004BCD0[i];
    *p = D_8004A618;
    p->unk14 = D_800391F0;
    p->unk0 = 60.0f;
    p->unk4 = 135.0f;
    i = arcadeFindFreeEntity();
    p = &D_8004BCD0[i];
    *p = D_8004A3D8;
    p->unk1A = 1;
    p->unk8 = 0.5f;
    p->unk0 = 114.0f;
    p->unk4 = 135.0f;
    i = arcadeFindFreeEntity();
    p = &D_8004BCD0[i];
    *p = D_8004A3D8;
    p->unk1A = 1;
    p->unk8 = 0.5f;
    p->unk0 = 260.0f;
    p->unk4 = 103.0f;
    D_8004BC88[0].x = 40.0f;
    D_8004BC88[1].x = 40.0f;
    D_8004BC88[2].x = 40.0f;
    D_8004BC88[3].x = 104.0f;
    D_8004BC88[4].x = 104.0f;
    D_8004BC88[5].x = 104.0f;
    D_8004BC88[0].y = 95.0f;
    D_8004BC88[3].y = 95.0f;
    D_8004BC88[1].y = 143.0f;
    D_8004BC88[4].y = 143.0f;
    D_8004BC88[2].y = 191.0f;
    D_8004BC88[5].y = 191.0f;
    t = (arcadeMinFloat((f32)(u32)D_8004A76C, 4.0f) - 2.0) / 16 + 0.5;
    D_8004BC88[3].vy = t;
    D_8004BC88[0].vy = -t;
    D_8004BC88[1].vy = -t;
    D_8004BC88[2].vy = -t;
    D_8004BC88[4].vy = t;
    D_8004BC88[5].vy = t;
}

extern ArcadeEntity D_8004A678;
extern ArcadeEntity D_8004A5B8;
extern ArcadeEntity D_8004A3F8;
extern ArcadeEntity D_8004A498;
extern ArcadeEntity D_8004C0D0;
extern ArcadeEntity D_8004C0B0;
extern ArcadeEntity D_8004C090;
extern ArcadeEntity D_8004C070;
extern ArcadeEntity D_8004C050;
extern ArcadeEntity D_8004C030;
extern ArcadeEntity D_8004C010;
extern ArcadeEntity D_8004BFF0;
extern u8 D_80033C48[];
void arcadeSpawnStage4Entities(void) {
    s32 idx;

    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A678;
    idx = arcadeFindFreeEntity();
    D_8004BCD0[idx] = D_8004A678;
    D_8004BCD0[idx].unk0 = 244.0f;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4D8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4B8;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A518;
    D_8004BCD0[arcadeFindFreeEntity()] = D_8004A5B8;
    if (D_8004A76C == 2 && D_8004A740 != 0) {
        D_8004BCD0[arcadeFindFreeEntity()] = D_8004A4F8;
    }
    idx = arcadeFindFreeEntity();
    D_8004BCD0[idx] = D_8004A438;
    D_8004BCD0[idx].unk14 = D_80033C48;
    D_8004C71F = arcadeFindFreeEntity();
    D_8004BCD0[D_8004C71F] = D_8004A398;
    D_8004C170 = D_8004A458;
    D_8004BCD0[0x25].unk0 = 152.0f;
    D_8004BCD0[0x25].unk4 = 127.0f;
    D_8004C150 = D_8004A3F8;
    D_8004BCD0[0x24].unk0 = 152.0f;
    D_8004BCD0[0x24].unk4 = 113.0f;
    D_8004C130 = D_8004A618;
    D_8004BCD0[0x23].unk14 = D_80038FE8;
    D_8004BCD0[0x23].unk0 = 172.0f;
    D_8004C110 = D_8004A618;
    D_8004BCD0[0x22].unk4 = 167.0f;
    D_8004BCD0[0x22].unk0 = 116.0f;
    D_8004C0F0 = D_8004A618;
    D_8004BCD0[0x21].unk14 = D_800391F0;
    D_8004BCD0[0x21].unk4 = 167.0f;
    D_8004BCD0[0x21].unk0 = 252.0f;
    D_8004C0D0 = D_8004A638;
    D_8004BCD0[0x20].unk0 = 68.0f;
    D_8004BCD0[0x20].unk4 = 148.0f;
    D_8004C0B0 = D_8004A638;
    D_8004BCD0[0x1F].unk0 = 156.0f;
    D_8004BCD0[0x1F].unk4 = 188.0f;
    D_8004C090 = D_8004A498;
    D_8004C070 = D_8004A498;
    D_8004BCD0[0x1D].unk1A = 1;
    D_8004BCD0[0x1D].unk1B = 1;
    D_8004BCD0[0x1D].unk1C = 0;
    D_8004BCD0[0x1D].unk0 = 256.0f;
    D_8004BCD0[0x1D].unk4 = 84.0f;
    D_8004C050 = D_8004A498;
    D_8004BCD0[0x1C].unk1A = 1;
    D_8004BCD0[0x1C].unk1B = 1;
    D_8004BCD0[0x1C].unk1C = 1;
    D_8004BCD0[0x1C].unk4 = 124.0f;
    D_8004BCD0[0x1C].unk0 = 139.0f;
    D_8004C030 = D_8004A498;
    D_8004BCD0[0x1B].unk4 = 124.0f;
    D_8004BCD0[0x1B].unk1C = 2;
    D_8004BCD0[0x1B].unk0 = 165.0f;
    D_8004C010 = D_8004A498;
    D_8004BCD0[0x1A].unk4 = 204.0f;
    D_8004BCD0[0x1A].unk1C = 3;
    D_8004BCD0[0x1A].unk0 = 48.0f;
    D_8004BFF0 = D_8004A498;
    D_8004BCD0[0x19].unk1A = 1;
    D_8004BCD0[0x19].unk1B = 1;
    D_8004BCD0[0x19].unk0 = 256.0f;
    D_8004BCD0[0x19].unk4 = 204.0f;
    D_8004BCD0[0x19].unk1C = 3;
}

void arcadeInitStage(void) {
    s32 i;
    s32 temp;

    D_8004C708 = 0;
    D_8004C722 = D_8004A788[D_8004C723 & 3];
    for (i = 0; i < 80; i++) {
        D_8004BCD0[i].unk18 = 0;
    }
    switch (D_8004C722) {
    case 1:
        arcadeSpawnStage1Entities();
        break;
    case 2:
        arcadeSpawnStage2Entities();
        break;
    case 3:
        arcadeSpawnStage3Entities();
        break;
    default:
        arcadeSpawnStage4Entities();
        break;
    }
    arcadeSetStageMusic();
    temp = D_8004A76C * 10 + 40;
    if (temp >= 91) {
        D_8004C71E = 90;
    } else {
        D_8004C71E = temp;
    }
    D_8004C710 = 0;
    D_8004C718 = 0xFF;
    D_8004A764 = 0;
    D_8004C6DC = 0;
    D_8004C71D = 1;
    D_8004C6F8 = 1;
    D_8004C721 = 1;
    D_8004A308[0] = 0;
    D_8004A308[1] = 0;
    D_8004A308[2] = 0;
    D_8004A308[3] = 0;
}

s32 arcadeCheckStage1Collision(s32 arg0, s32 arg1) {
    s32 ret;
    s32 temp;

    if (arg1 < 0x5D) {
        D_8004C6F0 = 0x88;
    } else {
        D_8004C6F0 = 0x36;
    }
    D_8004C6F4 = 0x10A;

    if (arg1 < 0x3F) {
        D_8004C6F8 = 0;
        if (arg0 >= 0x85 && arg0 < 0xBC) {
            ret = 0x37;
        } else {
            ret = 0xF8;
        }
    } else if (arg1 < 0x5D) {
        D_8004C6F8 = 1;
        temp = arg0 / 16;
        ret = temp;
        if (temp < 0xB) {
            ret = 0xB;
        }
        ret += 0x48;
        if (arg0 >= 0x105) {
            ret = 0xF8;
        }
    } else if (arg1 < 0x7F) {
        D_8004C6F8 = 2;
        ret = 0x7C - (arg0 / 16);
        if (arg0 < 0x3C) {
            ret = 0xF8;
        }
    } else if (arg1 < 0xA0) {
        D_8004C6F8 = 3;
        ret = (arg0 / 16) + 0x8A;
        if (arg0 >= 0x105) {
            ret = 0xF8;
        }
    } else if (arg1 < 0xC3) {
        D_8004C6F8 = 4;
        ret = 0xBE - (arg0 / 16);
        if (arg0 < 0x3C) {
            ret = 0xF8;
        }
    } else if (arg1 < 0xE1) {
        D_8004C6F8 = 5;
        ret = (arg0 / 16) + 0xCC;
        if (arg0 >= 0x105) {
            ret = 0xF8;
        }
    } else {
        D_8004C6F8 = 6;
        ret = 0x100 - (arg0 / 16);
        if (ret >= 0xF8) {
            ret = 0xF7;
        }
    }

    if (ret < arg1) {
        D_8004C6F8++;
    }
    return ret;
}

s32 arcadeCheckStage2Collision(s32 arg0, s32 arg1) {
    s32 ret;

    D_8004C6F0 = 0x36;
    D_8004C6F4 = 0x10A;
    if (arg1 < 0x6E) {
        D_8004C6F8 = 1;
        if (arg0 >= 0x4D && arg0 < 0xF4 &&
            (arg0 < 0x6C || arg0 >= 0x6D || (D_8004C718 & 0x40)) &&
            (arg0 < 0xD4 || arg0 >= 0xD5 || (D_8004C718 & 0x80))) {
            ret = 0x5D;
        } else {
            ret = 0xF7;
        }
    } else if (arg1 < 0x8C) {
        D_8004C6F8 = 2;
        if (arg0 >= 0x45 && arg0 < 0xFC &&
            (arg0 < 0x6C || arg0 >= 0x6D || (D_8004C718 & 0x10)) &&
            (arg0 < 0xD4 || arg0 >= 0xD5 || (D_8004C718 & 0x20))) {
            ret = 0x84;
        } else {
            ret = 0xF7;
        }
    } else if (arg1 < 0xBE) {
        D_8004C6F8 = 3;
        if (arg0 >= 0x3D && arg0 < 0x104 &&
            (arg0 < 0x6C || arg0 >= 0x6D || (D_8004C718 & 4)) &&
            (arg0 < 0xD4 || arg0 >= 0xD5 || (D_8004C718 & 8))) {
            ret = 0xAA;
        } else {
            ret = 0xF7;
        }
    } else if (arg1 < 0xDC) {
        D_8004C6F8 = 4;
        if ((arg0 < 0x6C || arg0 >= 0x6D || (D_8004C718 & 1)) &&
            (arg0 < 0xD4 || arg0 >= 0xD5 || (D_8004C718 & 2))) {
            ret = 0xD0;
        } else {
            ret = 0xF7;
        }
    } else {
        D_8004C6F8 = 5;
        ret = 0xF7;
    }

    if (ret < arg1) {
        D_8004C6F8++;
    }
    return ret;
}

extern ArcadeLift D_8004BCAC[];

s32 arcadeCheckStage3Collision(s32 arg0, s32 arg1) {
    s32 ret;
    ArcadeLift *bar;
    ArcadeLift *end;

    if (arg1 < 0x5D) {
        D_8004C6F0 = 0x88;
    } else {
        D_8004C6F0 = 0x36;
    }
    D_8004C6F4 = 0x10A;
    D_8004C6F8 = 1;
    if (arg1 < 0x3F) {
        if (arg0 >= 0x85 && arg0 < 0xBC) {
            ret = 0x37;
            D_8004C6F8 = 0;
        } else {
            ret = 0xF8;
        }
    } else if (arg1 < 0x62) {
        if (arg0 < 0xDC) {
            ret = 0x57;
        } else {
            ret = 0xF8;
        }
    } else if (arg1 < 0x8C) {
        if (arg0 >= 0xFD) {
            ret = 0x67;
        } else if (arg0 >= 0xE5 && arg0 < 0xFC) {
            ret = 0x6F;
        } else if (arg0 >= 0xCD && arg0 < 0xE4) {
            ret = 0x77;
        } else if (arg0 >= 0xAD && arg0 < 0xCC) {
            ret = 0x7F;
        } else if ((arg0 >= 0x65 && arg0 < 0x8C) || arg0 < 0x4C) {
            ret = 0x87;
        } else {
            ret = 0xF8;
        }
    } else if (arg1 < 0x94) {
        if (arg0 >= 0xE5) {
            ret = 0x8F;
        } else {
            ret = 0xF7;
        }
    } else if (arg1 < 0xC6) {
        if (arg0 >= 0xFD) {
            ret = 0xB7;
        } else if (arg0 >= 0xE5 && arg0 < 0xFC) {
            ret = 0xAF;
        } else if (arg0 >= 0xCD && arg0 < 0xE4) {
            ret = 0xA7;
        } else if (arg0 >= 0xB5 && arg0 < 0xCC) {
            ret = 0x9F;
        } else if (arg0 < 0x4C) {
            ret = 0xBF;
        } else {
            ret = 0xF8;
        }
    } else {
        if (arg1 < 0xF0) {
            if ((arg0 >= 0x6D && arg0 < 0x8C) || arg0 >= 0xF5) {
                ret = 0xCF;
            } else if (arg0 >= 0xDD && arg0 < 0xF4) {
                ret = 0xD7;
            } else if (arg0 >= 0xC5 && arg0 < 0xDC) {
                ret = 0xDF;
            } else if ((arg0 >= 0xA5 && arg0 < 0xC4) || arg0 < 0x4C) {
                ret = 0xE7;
            } else {
                ret = 0xF8;
            }
        } else {
            ret = 0xF7;
        }
    }
    if (arg0 >= 0x4D && arg0 < 0x64) {
        end = (ArcadeLift *)(s32)&D_8004BCAC;
        for (bar = D_8004BC88; ; ) {
            f32 y = bar->y;
            bar++;
            if (y < (f32)(arg1 + 4) && (f32)(arg1 - 0x10) < y) {
                ret = (s32)y;
            }
            if (bar == end) {
                break;
            }
        }
    }
    if (arg0 >= 0x8D && arg0 < 0xA4) {
        end = &D_8004BC88[6];
        for (bar = D_8004BCAC; ; ) {
            f32 y = bar->y;
            bar++;
            if (y < (f32)(arg1 + 4) && (f32)(arg1 - 0x10) < y) {
                ret = (s32)y;
            }
            if (bar == end) {
                break;
            }
        }
    }
    return ret;
}

s32 arcadeCheckStage4Collision(s32 arg0, s32 arg1) {
    s32 ret;

    D_8004C6F0 = 0x36;
    D_8004C6F4 = 0x10A;
    if (arg1 < 0x6E) {
        D_8004C6F8 = 0;
        ret = 0x57;
    } else if (arg1 < 0x8C) {
        if (arg0 < 0x9C) {
            ret = 0x7F;
            D_8004C6F8 = 1;
        } else if (arg0 >= 0xA5) {
            ret = 0x7F;
            D_8004C6F8 = 2;
        } else {
            ret = 0xF7;
        }
    } else if (arg1 < 0xBE) {
        D_8004C6F8 = 4;
        if ((arg0 < 0x64 || arg0 >= 0x6D) && (arg0 < 0xCC || arg0 >= 0xD5)) {
            ret = 0xA7;
        } else {
            ret = 0xF7;
        }
    } else if (arg1 < 0xDC) {
        D_8004C6F8 = 3;
        ret = 0xCF;
    } else {
        D_8004C6F8 = 5;
        ret = 0xF7;
    }
    if (ret < arg1) {
        D_8004C6F8++;
    }
    return ret;
}

s32 arcadeCheckPlayerCollision(s32 arg0, s32 arg1) {
    if (D_8004C722 == 1) {
        return arcadeCheckStage1Collision(arg0, arg1);
    } else if (D_8004C722 == 2) {
        return arcadeCheckStage2Collision(arg0, arg1);
    } else if (D_8004C722 == 3) {
        return arcadeCheckStage3Collision(arg0, arg1);
    } else {
        return arcadeCheckStage4Collision(arg0, arg1);
    }
}

s32 arcadeCheckLadderBounds(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if ((arg1 >= arg3) & (arg5 >= arg1) & ((arg2 - 4) < arg0) & (arg0 < (arg2 + 3))) {
        D_8004C6E0 = arg2;
        D_8004C6E4 = arg3;
        D_8004C6E8 = arg5;
        D_8004C6EC = arg4;
        return 1;
    }
    return 0;
}

s32 arcadeCheckStage1Ladders(s32 arg0, s32 arg1) {
    if (arcadeCheckLadderBounds(arg0, arg1, 0x84, 0xD4, 0xEB, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xEC, 0xDA, 0xDA, 0xF2)) {
        return 2;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x94, 0xB5, 0xB5, 0xD5)) {
        return 3;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x54, 0xB9, 0xB9, 0xD1)) {
        return 4;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x74, 0x91, 0xAB, 0xB7)) {
        return 5;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xAC, 0x94, 0x94, 0xB4)) {
        return 6;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xEC, 0x98, 0x98, 0xB0)) {
        return 7;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xDC, 0x6F, 0x8B, 0x97)) {
        return 8;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x7C, 0x75, 0x75, 0x91)) {
        return 9;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x54, 0x77, 0x77, 0x8F)) {
        return 10;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x8C, 0x53, 0x64, 0x74)) {
        return 11;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xEC, 0x56, 0x56, 0x6E)) {
        return 12;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xB4, 0x37, 0x37, 0x53)) {
        return 13;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 arcadeCheckStage2Ladders(s32 arg0, s32 arg1) {
    if (arcadeCheckLadderBounds(arg0, arg1, 0x3C, 0xD0, 0xD0, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x9C, 0xD0, 0xD0, 0xF7)) {
        return 2;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x104, 0xD0, 0xD0, 0xF7)) {
        return 3;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x44, 0xAA, 0xAA, 0xD0)) {
        return 4;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x7C, 0xAA, 0xAA, 0xD0)) {
        return 5;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xC4, 0xAA, 0xAA, 0xD0)) {
        return 6;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xFC, 0xAA, 0xAA, 0xD0)) {
        return 7;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x4C, 0x84, 0x84, 0xAA)) {
        return 8;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x9C, 0x84, 0x84, 0xAA)) {
        return 9;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xF4, 0x84, 0x84, 0xAA)) {
        return 10;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x54, 0x5D, 0x5D, 0x84)) {
        return 11;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x74, 0x5D, 0x5D, 0x84)) {
        return 12;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xCC, 0x5D, 0x5D, 0x84)) {
        return 13;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xEC, 0x5D, 0x5D, 0x84)) {
        return 14;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 arcadeCheckStage3Ladders(s32 arg0, s32 arg1) {
    if (arcadeCheckLadderBounds(arg0, arg1, 0xB4, 0x37, 0x37, 0x57)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xD4, 0x57, 0x57, 0x77)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x104, 0x67, 0x67, 0x8F)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xBC, 0x7F, 0x7F, 0x9F)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xEC, 0x8F, 0x8F, 0xAF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x104, 0xB7, 0xB7, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x44, 0x87, 0x87, 0xBF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x74, 0x87, 0x87, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x84, 0x87, 0x87, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x3C, 0xBF, 0xBF, 0xE7)) {
        return 1;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 arcadeCheckStage4Ladders(s32 arg0, s32 arg1) {
    s32 var_v0;
    if (arcadeCheckLadderBounds(arg0, arg1, 0x4C, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x84, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xBC, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xF4, 0xCF, 0xCF, 0xF7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x74, 0xA7, 0xA7, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xC4, 0xA7, 0xA7, 0xCF)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x4C, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x84, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xBC, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xF4, 0x7F, 0x7F, 0xA7)) {
        return 1;
    }
    var_v0 = (s32)D_8004BCD0[0].unk4;
    if (var_v0 == 0x61) {
        var_v0 = 0x57;
    } else {
        var_v0 = 0x74;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x44, 0x57, var_v0, 0x7F)) {
        return 1;
    }
    var_v0 = (s32)D_8004BCD0[1].unk4;
    if (var_v0 == 0x61) {
        var_v0 = 0x57;
    } else {
        var_v0 = 0x74;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0xFC, 0x57, var_v0, 0x7F)) {
        return 1;
    }
    D_8004C6E0 = 0;
    D_8004C6E4 = 0x12C;
    D_8004C6EC = 0x12C;
    D_8004C6E8 = 1;
    return 0;
}

s32 arcadeCheckStageLadders(s32 arg0, s32 arg1) {
    if (D_8004C722 == 1) {
        return arcadeCheckStage1Ladders(arg0, arg1);
    } else if (D_8004C722 == 2) {
        return arcadeCheckStage2Ladders(arg0, arg1);
    } else if (D_8004C722 == 3) {
        return arcadeCheckStage3Ladders(arg0, arg1);
    } else {
        return arcadeCheckStage4Ladders(arg0, arg1);
    }
}

void arcadeRenderEntity(Gfx **arg0, s32 arg1) {
    Gfx *sp4C;
    s32 off;
    f32 scale;

    if (D_8004A338[D_8004BCD0[arg1].unk18] & 1) {
        scale = 1024.0f;
    } else {
        scale = 1170.2858f;
    }
    off = arg1 * 0x18;
    func_80005A90(D_8004AC00 + D_807444FC * 0x780 + off, D_8004BCD0[arg1].unk14, 0, D_8004BCD0[arg1].unk1E, D_8004BCD0[arg1].unk1E, D_8004BCD0[arg1].unk1F, 0, 2, 0, 0);
    sp4C = *arg0;
    dlAppendTextureLoad(&sp4C, D_8004AC00 + D_807444FC * 0x780 + off);
    func_8070F2C8(0x400, (s32)scale, (u8)(D_8004BCD0[arg1].unk1A & 1), D_8004BCD0[arg1].unk1B);
    if (D_8004A338[D_8004BCD0[arg1].unk18] & 2) {
        dlAppendTextureRectangle(&sp4C, (s32)(D_8004BCD0[arg1].unk0 - (f32)(u32)D_8004A358[D_8004BCD0[arg1].unk18]) * 4, (s32)((f64)(D_8004BCD0[arg1].unk4 - (f32)(u32)D_8004A378[D_8004BCD0[arg1].unk18]) * 0.875 + 8.0) * 4);
    } else {
        if (D_8004BCD0[arg1].unk18 == 2) {
            off = (s32)D_8004BCD0[arg1].unk10;
            if (off >= 3) {
                off = 5 - off;
            }
        } else {
            off = 0;
        }
        dlAppendTextureRectangle(&sp4C, (s32)(D_8004BCD0[arg1].unk0 - (f32)(u32)D_8004A358[D_8004BCD0[arg1].unk18]) * 4, (s32)(((f64)(D_8004BCD0[arg1].unk4 - (f32)off - (f32)(u32)D_8004A378[D_8004BCD0[arg1].unk18]) * 0.875 + 8.0) * 4.0));
    }
    *arg0 = sp4C;
}

void arcadeRenderEntities(Gfx **arg0) {
    s32 i;
    Gfx *sp38;
    sp38 = *arg0;
    for (i = 0; i < 80; i++) {
        if (D_8004BCD0[i].unk18 != 0 && D_8004BCD0[i].unk14 != 0) {
            if (D_8004BCD0[i].unk18 >= 8 || D_8004C71D < 2) {
                arcadeRenderEntity(&sp38, i);
            }
        }
    }
    *arg0 = sp38;
}

s32 arcadeAbs(s32 arg0) {
    if (arg0 >= 0) {
        return arg0;
    }
    return -arg0;
}

extern u8 D_8003B180[];
extern u8 D_8003B3C8[];
extern u8 D_8003B610[];
extern u8 D_8003B858[];
extern u8 D_8003BAA0[];
extern u8 D_8003BCE8[];
extern u8 D_8003BF30[];
extern u8 D_8003C178[];
extern u8 D_8003C3C0[];
extern u8 D_8003C608[];
extern u8 D_8003C850[];
extern u8 D_8003CA98[];
extern u8 D_8003CCE0[];
extern u8 D_8003CF28[];
extern u8 D_8003D170[];
extern u8 D_8003D3B8[];
extern u8 D_8003D600[];
extern u8 D_8003D848[];
extern s32 D_8004A75C;

void arcadeUpdatePlayerAnimation(s32 arg0) {
    s32 val;
    s32 b;
    s32 s4;
    s32 s0;
    f32 fs0;
    f32 y;

    b = D_8004BCD0[arg0].unk1A & 2;
    D_8004BCD0[arg0].unk1A = b / 2 | b;
    D_8004BCD0[arg0].unk1B = 0;
    val = (s32)D_8004BCD0[arg0].unk10;
    if (D_8004BCD0[arg0].unk19 == 2) {
        if (D_8004A764 && D_8004A764) {} // FAKE: empty guard steers regalloc
        if (D_8004C710 != 0) {
            if (D_8004C710 & 8) {
                switch (val & 3) {
                case 0:
                case 2:
                    D_8004BCD0[arg0].unk14 = D_8003C178;
                    break;
                case 1:
                    D_8004BCD0[arg0].unk14 = D_8003C608;
                    break;
                case 3:
                    D_8004BCD0[arg0].unk14 = D_8003CA98;
                    break;
                }
            } else {
                switch (val & 3) {
                case 0:
                case 2:
                    D_8004BCD0[arg0].unk14 = D_8003C3C0;
                    break;
                case 1:
                    D_8004BCD0[arg0].unk14 = D_8003C850;
                    break;
                case 3:
                    D_8004BCD0[arg0].unk14 = D_8003CCE0;
                    break;
                }
            }
        } else {
            switch (val & 3) {
            case 0:
            case 2:
                D_8004BCD0[arg0].unk14 = D_8003B180;
                break;
            case 1:
                D_8004BCD0[arg0].unk14 = D_8003B3C8;
                break;
            case 3:
                D_8004BCD0[arg0].unk14 = D_8003B610;
                break;
            }
        }
    } else if (D_8004BCD0[arg0].unk19 == 3) {
        D_8004BCD0[arg0].unk14 = D_8003CF28;
    } else if (D_8004BCD0[arg0].unk19 == 5) {
        y = D_8004BCD0[arg0].unk4;
        if ((f32)D_8004C6E8 - y < 1.0f || (y - (f32)D_8004C6E4 < 1.0f)) {
            D_8004BCD0[arg0].unk14 = D_8003BF30;
        } else if (y - (f32)D_8004C6E4 < 6.0f) {
            D_8004BCD0[arg0].unk14 = D_8003B858;
        } else if (y - (f32)D_8004C6E4 < 10.0f) {
            D_8004BCD0[arg0].unk14 = D_8003BCE8;
        } else if (y - (f32)D_8004C6E4 < 14.0f) {
            D_8004BCD0[arg0].unk14 = D_8003BAA0;
        } else {
            D_8004BCD0[arg0].unk14 = D_8003B858;
        }
        D_8004BCD0[arg0].unk1A = (s32)((f64)D_8004BCD0[arg0].unk10 / 4.5) & 1;
    } else if (D_8004BCD0[arg0].unk19 == 8) {
        if (D_8004BCD0[arg0].unk10 > 38.0f) {
            if (D_8004C71B == 0) {
                if (D_8004BCD0[arg0].unk10 > 48.0f) {
                    if (D_8004A75C < D_8004A748) {
                        arcadeCheckGameOver();
                        return;
                    }
                    if (D_8004A740 != 0) {
                        arcadeExit();
                        return;
                    }
                    arcadeInitTitleScreen();
                    return;
                }
                if (D_8004A764 == 0) {
                    D_8004A764 = 1;
                    for (s4 = 0x6C; s4 != 0xCC; s4 += 0x10) {
                        fs0 = s4;
                        for (s0 = 0xA6; s0 != 0xC6; s0 += 0x10) {
                            s32 index = func_800247F0();
                            D_8004BCD0[index] = D_8004A6B8;
                            D_8004BCD0[index].unk0 = fs0;
                            D_8004BCD0[index].unk4 = s0;
                        }
                    }
                }
            } else {
                D_8004C71B--;
                arcadeFinishStageIntro();
            }
        } else if (D_8004BCD0[arg0].unk10 > 20.0f) {
            D_8004BCD0[arg0].unk14 = D_8003D848;
        } else if (D_8004BCD0[arg0].unk10 > 8.0f) {
            D_8004C71D = 2;
            if ((s32)D_8004BCD0[arg0].unk10 & 1) {
                D_8004BCD0[arg0].unk14 = D_8003D3B8;
            } else {
                D_8004BCD0[arg0].unk14 = D_8003D600;
            }
            if (((s32)D_8004BCD0[arg0].unk10 & 3) == 2) {
                D_8004BCD0[arg0].unk1A ^= 1;
            }
            if (((s32)D_8004BCD0[arg0].unk10 & 3) == 1) {
                D_8004BCD0[arg0].unk1B = !D_8004BCD0[arg0].unk1B;
            }
        }
    } else {
        D_8004BCD0[arg0].unk14 = D_8003D170;
    }
}

extern s32 D_8004BC80;
extern s32 D_8004BC84;
extern s32 D_8004C6FC;
extern s32 D_8004C700;
extern s32 D_8004C704;
extern s32 D_80770DFC;
extern ArcadeEntity D_8004A5F8;
extern u8 D_800383B8[];
extern u8 D_800385C0[];
extern u8 D_8003B180[];
void arcadeUpdatePlayerAnimation(s32);
void n_alSndpPostEvent(s32, s32, s32);
#define E D_8004BCD0[arg0]
#define P D_8004BCD0[D_8004C71F]
void arcadeUpdatePlayerEntity(s32 arg0) {
    f32 sp44;
    s32 coll;
    s32 i;
    s32 n;
    s32 phase;

    if (E.unk19 == 8 || D_8004C71D == 0) {
        if (D_8004BC84 == 0) {} // FAKE: empty guard steers regalloc
        if (E.unk19 == 2) {
            arcadeCheckPlayerCollision((s32)E.unk0, (s32)E.unk4);
            if (E.unk8 < 0.0f) {
                E.unk1A = E.unk1A & 1;
            } else if (E.unk8 > 0.0f) {
                E.unk1A = E.unk1A | 2;
            }
            if (((*(u16 *)D_807ECDE8 & 0x200) || (s8)D_807ECDE8[2] < -0x14) && (f32)D_8004C6F0 < E.unk0) {
                D_8004BC80 += 3;
                E.unk8 = -0.7f;
                E.unk10 = (f32)((f64)E.unk10 + 0.3);
            } else if (((*(u16 *)D_807ECDE8 & 0x100) || (s8)D_807ECDE8[2] >= 0x15) && E.unk0 < (f32)D_8004C6F4) {
                D_8004BC80 += 3;
                E.unk8 = 0.7f;
                E.unk10 = (f32)((f64)E.unk10 + 0.3);
            } else {
                E.unk8 = 0.0f;
            }
            if ((D_807ECD48 & 0xE000) && D_8004C710 == 0) {
                n_alSndpPlay(D_8076D1F8, 0x41, 0x7FFF, 0x3F, 1.0f, 0, 0);
                E.unk10 = 0.0f;
                E.unkC = -1.2f;
                E.unk8 = (f32)((f64)E.unk8 * 0.65);
                E.unk1D = (u32)E.unk4;
                E.unk19 = 3;
            }
        }
        if (E.unk4 < (f32)(arcadeCheckPlayerCollision((s32)(E.unk0 + E.unk8), (s32)E.unk4) + 3)) {
            E.unk0 = E.unk8 + E.unk0;
        } else {
            E.unk8 = 0.0f;
        }
        if (E.unk19 != 8 && D_8004C722 == 3 &&
            ((76.0f < E.unk0 && E.unk0 < 100.0f) || (140.0f < E.unk0 && E.unk0 < 164.0f)) &&
            ((E.unk4 < 116.0f && 90.0f < E.unk4) || 239.0f < E.unk4)) {
            arcadeKillPlayer();
            return;
        }
        D_8004C700 = arcadeCheckStageLadders((s32)E.unk0, (s32)E.unk4);
        coll = arcadeCheckPlayerCollision((s32)E.unk0, (s32)E.unk4);
        D_8004C6FC = D_8004C6F8;
        switch (E.unk19) {
        case 2:
            for (i = 0; i < 4; i++) {
                if (D_8004C6F8 == i) {
                    P.unk0 += (f32)D_8004A308[i];
                }
            }
            if (E.unk0 <= (f32)(D_8004C6F0 - 1)) {
                E.unk0 = (f32)D_8004C6F0;
            }
            if ((f32)(D_8004C6F4 + 1) <= E.unk0) {
                E.unk0 = (f32)D_8004C6F4;
            }
            if ((f32)D_8004C6EC < E.unk4 &&
                ((((s8)D_807ECDE8[3] >= 0x15) | (*(u16 *)D_807ECDE8 & 0x800)) != 0) &&
                (s8)D_807ECDE8[2] < 0x29 && (s8)D_807ECDE8[2] >= -0x28 &&
                !(*(u16 *)D_807ECDE8 & 0x300) && D_8004C710 == 0) {
                E.unk19 = 5;
                E.unk8 = 0.0f;
                E.unk4 = E.unk4 - 1.0f;
                E.unk0 = (f32)D_8004C6E0;
                break;
            } else if (E.unk4 < (f32)D_8004C6E8 && (f32)D_8004C6EC <= E.unk4 &&
                       !(*(u16 *)D_807ECDE8 & 0x300) &&
                       (s8)D_807ECDE8[2] < 0x29 && (s8)D_807ECDE8[2] >= -0x28 &&
                       ((((s8)D_807ECDE8[3] < -0x14) | (*(u16 *)D_807ECDE8 & 0x400)) != 0) &&
                       D_8004C710 == 0) {
                E.unk19 = 5;
                E.unk8 = 0.0f;
                E.unk4 = E.unk4 + 1.0f;
                E.unk0 = (f32)D_8004C6E0;
                break;
            } else {
                if ((f32)coll - E.unk4 < 2.0f) {
                    E.unk4 = (f32)coll;
                } else {
                    E.unk19 = 3;
                    E.unk8 = 0.0f;
                    E.unkC = 0.0f;
                    E.unk1D = (u32)E.unk4;
                }
            }
            break;
        case 5:
            if ((f32)coll == E.unk4 &&
                (((((s8)D_807ECDE8[2] >= 0x15) | ((s8)D_807ECDE8[2] < -0x14)) | (*(u16 *)D_807ECDE8 & 0x300)) ||
                 (D_8004C6F8 == 2 && D_8004A308[2] != 0) ||
                 (D_8004C6F8 == 1 && D_8004A308[1] != 0) ||
                 (D_8004C6F8 == 3 && D_8004A308[3] != 0))) {
                E.unk19 = 2;
            } else if ((f32)coll == E.unk4 && (D_807ECD48 & 0xE000)) {
                n_alSndpPlay(D_8076D1F8, 0x41, 0x7FFF, 0x3F, 1.0f, 0, 0);
                E.unk10 = 0.0f;
                E.unkC = -1.2f;
                E.unk8 = (f32)((f64)E.unk8 * 0.65);
                E.unk19 = 3;
                E.unk1D = (u32)E.unk4;
            } else {
                if (E.unk4 < (f32)D_8004C6EC) {
                    E.unk4 = (f32)((f64)E.unk4 + 0.2);
                    if ((f32)D_8004C6EC - E.unk4 > 10.0f) {
                        E.unk4 = (f32)(D_8004C6EC - 10);
                    }
                    if ((f32)D_8004C6EC < E.unk4) {
                        E.unk4 = (f32)D_8004C6EC;
                    }
                } else {
                    if ((f32)D_8004C6EC < E.unk4 &&
                        ((((s8)D_807ECDE8[3] >= 0x15) | (*(u16 *)D_807ECDE8 & 0x800)) != 0)) {
                        E.unkC = -0.5f;
                        D_8004BC80 += 2;
                    } else if (E.unk4 < (f32)D_8004C6E8 &&
                               ((((s8)D_807ECDE8[3] < -0x14) | (*(u16 *)D_807ECDE8 & 0x400)) != 0)) {
                        E.unkC = 0.5f;
                        D_8004BC80 += 2;
                    } else {
                        E.unkC = 0.0f;
                    }
                    E.unk4 = E.unkC + E.unk4;
                    E.unk10 = E.unkC + E.unk10;
                }
            }
            break;
        case 3:
            if ((f32)D_8004C6F4 < E.unk0) {
                E.unk0 = (f32)D_8004C6F4;
                if ((f64)E.unkC < 1.8) {
                    E.unk1A = E.unk1A & 1;
                    E.unk8 = -E.unk8;
                    E.unkC = -E.unkC;
                }
            } else if (E.unk0 < (f32)D_8004C6F0) {
                E.unk0 = (f32)D_8004C6F0;
                if ((f64)E.unkC < 1.8) {
                    E.unk1A = E.unk1A | 2;
                    E.unk8 = -E.unk8;
                    E.unkC = -E.unkC;
                }
            }
            E.unk4 = E.unkC + E.unk4;
            E.unkC = (f32)((f64)E.unkC + 0.06);
            if (0.0f <= E.unkC && (f64)E.unkC < 0.06) {
                n = 0;
                for (i = 0; i < 0x50; i++) {
                    if (D_8004BCD0[i].unk18 == 1 || D_8004BCD0[i].unk18 == 2) {
                        if (arcadeAbs((s32)(D_8004BCD0[i].unk0 - E.unk0)) < 0xD) {
                            if (D_8004BCD0[i].unk4 - E.unk4 < 24.0f && E.unk4 < D_8004BCD0[i].unk4) {
                                n++;
                            }
                        }
                    }
                }
                if (n != 0) {
                    i = func_800247F0();
                    D_8004BCD0[i] = D_8004A5F8;
                    D_8004BCD0[i].unk0 = E.unk0;
                    D_8004BCD0[i].unk4 = E.unk4 + 9.0f;
                    if (n == 1) {
                        arcadeAddScore(0x64);
                    } else if (n == 2) {
                        D_8004BCD0[i].unk14 = D_800383B8;
                        arcadeAddScore(0x12C);
                    } else {
                        D_8004BCD0[i].unk14 = D_800385C0;
                        arcadeAddScore(0x1F4);
                    }
                }
            }
            if (E.unk4 - (f32)(u32)E.unk1D > 15.0f) {
                n_alSndpPlay(D_8076D1F8, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
                E.unk1D = 0xFF;
            }
            if ((f64)E.unkC > 2.5) {
                E.unkC = 2.5f;
            }
            if ((f32)coll < E.unk4 && E.unk4 - (f32)coll < 3.0f) {
                E.unk4 = (f32)coll;
                if (E.unk1D == 0xFF) {
                    arcadeKillPlayer();
                } else {
                    E.unk19 = 4;
                    E.unkC = 0.0f;
                    E.unk8 = 0.0f;
                    E.unk10 = 4.0f;
                }
            }
            break;
        case 4:
            E.unk4 = (f32)coll;
            E.unk10 = E.unk10 - 1.0f;
            if (E.unk10 == 0.0f) {
                E.unk19 = 2;
            }
            break;
        case 8:
            E.unk10 = (f32)((f64)E.unk10 + 0.125);
            if (E.unk10 == 8.0f) {
                n_alSndpPlay(D_8076D1F8, 0x54, 0x7FFF, 0x3F, 1.0f, 0, 0);
            }
            break;
        }
        if (D_8004BC80 >= 0x24) {
            D_8004BC80 = 0;
            phase = D_8004BC84 + 1;
            if (phase == 7) {
                phase = 0;
            }
            D_8004BC84 = phase;
            if (phase & 1) {
                sp44 = 1.0f;
            } else {
                sp44 = 0.7071120143f;
            }
            n_alSndpPlay(D_8076D1F8, 0x40, 0x7FFF, 0x3F, 1.0f, 0, (s32)&D_80770DFC);
            n_alSndpPostEvent(D_80770DFC, 0x10, *(s32 *)&sp44);
        }
        coll = arcadeCheckPlayerCollision((s32)E.unk0, (s32)E.unk4);
        if (D_8004BC80 && D_8004BC80) {} // FAKE: empty guard steers regalloc
        E.unk1C = D_8004C6F8;
        D_8004C704 = (s32)(E.unk4 - (f32)D_8004C6E4);
        if (D_8004C71E < 0 && E.unk19 != 8) {
            arcadeKillPlayer();
        }
        if (D_8004C6F8 == 0 && (f32)coll == E.unk4) {
            n_alSndpPlay(D_8076D1F8, 0x4C, 0x7FFF, 0x3F, 1.0f, 0, 0);
            arcadeStopSound(0);
            if (D_8004C722 == 1) {
                i = arcadeFindEntityByType(0x16);
            } else if (D_8004C722 == 3) {
                i = arcadeFindEntityByType(0x18);
            } else if (D_8004C722 == 4) {
                i = arcadeFindEntityByType(0x19);
            }
            D_8004BCD0[i].unk19 = 5;
            if (D_8004C722 != 4) {
                D_8004BCD0[i].unk18 = 0x16;
            }
            D_8004BCD0[i].unk10 = 0.0f;
            D_8004C71D = 3;
            E.unk14 = D_8003B180;
            E.unk1A = 0;
            return;
        }
        if (E.unk19 != 0) {
            arcadeUpdatePlayerAnimation(arg0);
        }
    }
}
#undef E
#undef P

void arcadeUpdateEntitySprite(s32 arg0) {
    ArcadeEntity *ptr = &D_8004BCD0[arg0];
    s32 val = (s32)ptr->unk10;

    if (ptr->unk19 == 5 || ptr->unk19 == 7 || ptr->unk19 == 1) {
        if (ptr->unk1D != 0) {
            switch (val & 1) {
            case 0:
                ptr->unk14 = D_80035AE0;
                return;
            case 1:
                ptr->unk14 = D_80035CE8;
                return;
            }
        } else {
            switch (val & 1) {
            case 0:
                ptr->unk14 = D_80035650;
                return;
            case 1:
                ptr->unk14 = D_80035898;
                return;
            }
        }
    } else {
        if (ptr->unk1D != 0) {
            switch (val & 3) {
            case 0:
                ptr->unk14 = D_80035448;
                return;
            case 1:
                ptr->unk14 = D_80035240;
                return;
            case 2:
                ptr->unk14 = D_80035038;
                return;
            case 3:
                ptr->unk14 = D_80034E30;
                return;
            }
        } else {
            switch (val & 3) {
            case 0:
                ptr->unk14 = D_80034C28;
                return;
            case 1:
                ptr->unk14 = D_80034A20;
                return;
            case 2:
                ptr->unk14 = D_80034818;
                return;
            case 3:
                ptr->unk14 = D_80034610;
                return;
            }
        }
    }
}

#ifdef NON_MATCHING
extern s32 D_8004C6FC;
extern s32 D_8004C704;
void func_8002CD64(s32 arg0) {
    s32 sp3C;
    s32 v;

    if (D_8004C71D == 0) {
        if (D_8004BCD0[arg0].unk19 == 0 || D_8004BCD0[arg0].unk19 == 1) {
            arcadeUpdateEntitySprite(arg0);
            return;
        }
        D_8004BCD0[arg0].unk0 += D_8004BCD0[arg0].unk8;
        sp3C = arcadeCheckPlayerCollision((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
        arcadeCheckStageLadders((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
        switch (D_8004BCD0[arg0].unk19) {
        case 2:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.2);
            D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            if (D_8004BCD0[arg0].unk4 < (f32)D_8004C6E8 &&
                (D_8004C6F8 + 1 < D_8004C6FC ||
                 (D_8004C6FC == D_8004C6F8 + 1 && (D_8004C704 >= 0x12 || D_8004BCE9[D_8004C71F << 5] != 5)))) {
                if (!(D_8004BCD0[arg0].unk1C & 0x80)) {
                    D_8004BCD0[arg0].unk1C = D_8004BCD0[arg0].unk1C & 0xF;
                    if (D_8004BCD0[arg0].unk1C > 0) {
                        D_8004BCD0[arg0].unk1C = D_8004BCD0[arg0].unk1C - 1;
                        D_8004BCD0[arg0].unk19 = 5;
                        D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + 1.0f;
                        D_8004BCD0[arg0].unkC = 1.0f;
                        D_8004BCD0[arg0].unk8 = 0.0f;
                        D_8004BCD0[arg0].unk0 = (f32)D_8004C6E0;
                    } else {
                        D_8004BCD0[arg0].unk1C = D_8004BCD0[arg0].unk1C | 0x80;
                        goto L_tail2;
                    }
                }
            } else {
                if (!(D_8004BCD0[arg0].unk1C & 0x47)) {
                    v = 4096.0f + arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * 1512.0f > (f32)arcadeRand();
                    D_8004BCD0[arg0].unk1C = v | 0x40;
                }
            L_tail2:
                if ((f32)sp3C - D_8004BCD0[arg0].unk4 < 3.0f) {
                    D_8004BCD0[arg0].unk4 = (f32)sp3C;
                } else {
                    D_8004BCD0[arg0].unk19 = 3;
                    D_8004BCD0[arg0].unkC = 0.0f;
                    D_8004BCD0[arg0].unk8 = D_8004BCD0[arg0].unk8 / 2;
                }
            }
            break;
        case 3:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.2);
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            D_8004BCD0[arg0].unkC = (f32)((f64)D_8004BCD0[arg0].unkC + 0.06);
            if ((f32)sp3C < D_8004BCD0[arg0].unk4 && D_8004BCD0[arg0].unk4 - (f32)sp3C < 3.0f) {
                D_8004BCD0[arg0].unk4 = (f32)sp3C;
                D_8004BCD0[arg0].unkC = -D_8004BCD0[arg0].unkC / 3.0f;
                if ((f64)D_8004BCD0[arg0].unkC > -0.2) {
                    D_8004BCD0[arg0].unk19 = 2;
                }
            }
            break;
        case 5:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.3);
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            if ((f32)(D_8004C6E8 - 1) < D_8004BCD0[arg0].unk4) {
                v = 1 - D_8004BCD0[arg0].unk1A;
                D_8004BCD0[arg0].unk1A = v;
                D_8004BCD0[arg0].unk19 = 2;
                D_8004BCD0[arg0].unk4 = (f32)sp3C;
                D_8004BCD0[arg0].unk8 = (f32)(1 - (u8)v * 2);
            }
            break;
        case 7:
            D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.3);
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            D_8004BCD0[arg0].unkC = (f32)((f64)D_8004BCD0[arg0].unkC + 0.06);
            sp3C = arcadeCheckPlayerCollision((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
            if ((f32)sp3C < D_8004BCD0[arg0].unk4 && D_8004BCD0[arg0].unk4 - (f32)sp3C < 8.0f && D_8004BCD0[arg0].unk1C < D_8004C6F8) {
                D_8004BCD0[arg0].unk1C = D_8004C6F8;
                D_8004BCD0[arg0].unk4 = (f32)sp3C;
                D_8004BCD0[arg0].unkC = 0.0f;
                if (D_8004BCD0[arg0].unk1D != 2) {
                    D_8004BCD0[arg0].unk8 = (f32)((arcadeMinFloat(3.0f, (f32)(u32)D_8004A76C) * ((f64)arcadeRand() - 16384.0)) / 40000.0 + (f64)(-D_8004BCD0[arg0].unk8) * 0.2);
                }
                if (D_8004BCD0[arg0].unk4 > 230.0f) {
                    D_8004BCD0[arg0].unk19 = 3;
                    D_8004BCD0[arg0].unk1A = 1;
                    D_8004BCD0[arg0].unk8 = -1.0f;
                    D_8004BCD0[arg0].unkC = -0.7f;
                }
            }
            break;
        }
        if (D_8004BCD0[D_8004C71F].unk1C >= D_8004C6F8 || D_8004BCD0[arg0].unk1D != 0) {
            if (270.0f < D_8004BCD0[arg0].unk0) {
                D_8004BCD0[arg0].unk1A = 1;
                D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            } else if (D_8004BCD0[arg0].unk0 < 50.0f) {
                D_8004BCD0[arg0].unk1A = 0;
                D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            }
        }
        if (278.0f < D_8004BCD0[arg0].unk0 || D_8004BCD0[arg0].unk0 < 2.0f) {
            D_8004BCD0[arg0].unk18 = 0;
        }
        if ((D_8004BCD0[arg0].unk4 > 242.0f) & (D_8004BCD0[arg0].unk0 < 74.0f)) {
            if (D_8004BCD0[arg0].unk1D != 0) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                v = arcadeFindEntityByType(0x13);
                if (v < 0) {
                    v = arcadeFindFreeEntity();
                    D_8004BCD0[v] = D_8004A3F8;
                }
                D_8004BCE9[v << 5] = 3;
                D_8004BCD0[arg0].unk18 = 0;
            } else {
                D_8004BCD0[arg0].unk18 = 0;
            }
        }
        if (D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0 < 8.0f && D_8004BCD0[D_8004C71F].unk0 - D_8004BCD0[arg0].unk0 < 8.0f) {
            if (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 < 3.0f && D_8004BCD0[D_8004C71F].unk4 - D_8004BCD0[arg0].unk4 < 8.0f) {
                arcadeKillPlayer();
            }
        }
        arcadeUpdateEntitySprite(arg0);
    }
}
#else

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002CD64.s")
#endif

extern s8 D_8004A768;
extern u8 D_80037B98[];
extern u8 D_80037DA0[];
extern u8 D_80037FA8[];
extern u8 D_8003E438[];
extern u8 D_800383B8[];
extern u8 D_800385C0[];
extern u8 D_800387C8[];
extern u8 D_80039D18[];
extern u8 D_80039F60[];
extern u8 D_8003A1A8[];
extern u8 D_8003A3F0[];
extern u8 D_8003AE58[];
extern u8 D_800389D0[];
extern u8 D_8003DB18[];
extern u8 D_8003DD60[];
extern u8 D_80038BD8[];
extern u8 D_8003E680[];
extern u8 D_8003E868[];
extern s32 D_8076D1F8;
/* ArcR4 declarations */
extern ArcadeEntity D_8004A5F8;
extern s32 D_8004A318[];
extern u8 D_8004BCE9[];

#ifdef NON_MATCHING
extern u8 D_80035EF0[];
extern u8 D_80036138[];
extern u8 D_80036380[];
extern u8 D_800365C8[];
extern u8 D_80036810[];
extern u8 D_80036A58[];
extern u8 D_80036CA0[];
extern u8 D_80036EE8[];
void func_8002D6FC(s32 arg0) {
    s32 sp2C;
    s32 a0;
    s32 sp20;

    if (D_8004C71D == 0) {
        D_8004BCD0[arg0].unk10 = (f32)((f64)D_8004BCD0[arg0].unk10 + 0.15);
        if (D_8004BCD0[arg0].unk10 >= 5.0f) {
            D_8004BCD0[arg0].unk10 = D_8004BCD0[arg0].unk10 - 5.0f;
        }
        if (D_8004C722 == 2) {
            if (D_8004C710 != 0) {
                if ((D_8004C6DC / 4) & 1) {
                    D_8004BCD0[arg0].unk14 = D_80036810;
                } else {
                    D_8004BCD0[arg0].unk14 = D_80036A58;
                }
            } else if ((D_8004C6DC / 4) & 1) {
                D_8004BCD0[arg0].unk14 = D_80036380;
            } else {
                D_8004BCD0[arg0].unk14 = D_800365C8;
            }
        } else if (D_8004C710 != 0) {
            if ((D_8004C6DC / 4) & 1) {
                D_8004BCD0[arg0].unk14 = D_80036CA0;
            } else {
                D_8004BCD0[arg0].unk14 = D_80036EE8;
            }
        } else if ((D_8004C6DC / 4) & 1) {
            D_8004BCD0[arg0].unk14 = D_80035EF0;
        } else {
            D_8004BCD0[arg0].unk14 = D_80036138;
        }
        sp2C = arcadeCheckPlayerCollision((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
        arcadeCheckStageLadders((s32)D_8004BCD0[arg0].unk0, (s32)D_8004BCD0[arg0].unk4);
        switch (D_8004BCD0[arg0].unk19) {
        case 2:
            sp20 = arcadeRand();
            if ((f32)sp20 < arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * 60.0f + 256.0f) {
                a0 = D_8004BCD0[arg0].unk0 < D_8004BCD0[D_8004C71F].unk0;
                a0 += ((D_8004BCD0[D_8004C71F].unk1A & 2) * 3) / 2;
                D_8004BCD0[arg0].unk1A = (arcadeRand() + a0 * 0xFB8) - 0x1F70 >= 0x4001;
            }
            if ((f32)arcadeCheckPlayerCollision((s32)(D_8004BCD0[arg0].unk0 + D_8004BCD0[arg0].unk8 * 8.0f), (s32)D_8004BCD0[arg0].unk4) - D_8004BCD0[arg0].unk4 > 5.0f) {
                D_8004BCD0[arg0].unk1A = D_8004BCD0[arg0].unk1A == 0;
            } else {
                D_8004BCD0[arg0].unk0 += D_8004BCD0[arg0].unk8;
            }
            D_8004BCD0[arg0].unk8 = (f32)((((f64)arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) / 15.0) + 1.0) * ((f64)(u32)D_8004BCD0[arg0].unk1A - 0.5));
            a0 = (s32)(arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) * (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4) * 3.0f);
            if (D_8004BCD0[arg0].unk4 < (f32)D_8004C6E8 && arcadeRand() < 0x400 - a0) {
                D_8004BCD0[arg0].unk19 = 5;
                D_8004BCD0[arg0].unk8 = 0.0f;
                D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + 1.0f;
                D_8004BCD0[arg0].unkC = (f32)(2.0 * (((f64)arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) / 30.0) + 0.2));
                D_8004BCD0[arg0].unk0 = (f32)D_8004C6E0;
            } else if ((f32)D_8004C6E4 < D_8004BCD0[arg0].unk4 && arcadeRand() < a0 + 0x400) {
                D_8004BCD0[arg0].unk19 = 6;
                D_8004BCD0[arg0].unk8 = 0.0f;
                D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 - 1.0f;
                D_8004BCD0[arg0].unkC = (f32)-(((f64)arcadeMinFloat((f32)(u32)D_8004A76C, 5.0f) / 30.0) + 0.2);
                D_8004BCD0[arg0].unk0 = (f32)D_8004C6E0;
            } else if ((f32)sp2C - D_8004BCD0[arg0].unk4 < 3.0f) {
                D_8004BCD0[arg0].unk4 = (f32)sp2C;
            } else {
                D_8004BCD0[arg0].unk1A = D_8004BCD0[arg0].unk1A == 0;
            }
            break;
        case 3:
            D_8004BCD0[arg0].unk0 = D_8004BCD0[arg0].unk0 + D_8004BCD0[arg0].unk8;
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            D_8004BCD0[arg0].unkC = (f32)((f64)D_8004BCD0[arg0].unkC + 0.06);
            if ((f32)sp2C < D_8004BCD0[arg0].unk4 && D_8004BCD0[arg0].unk4 - (f32)sp2C < 3.0f) {
                D_8004BCD0[arg0].unk4 = (f32)sp2C;
                D_8004BCD0[arg0].unkC = -D_8004BCD0[arg0].unkC / 3.0f;
                if ((f64)D_8004BCD0[arg0].unkC > -0.2) {
                    D_8004BCD0[arg0].unk19 = 2;
                }
            }
            break;
        case 5:
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            if ((f32)(D_8004C6E8 - 1) < D_8004BCD0[arg0].unk4) {
                D_8004BCD0[arg0].unk1A = 1 - D_8004BCD0[arg0].unk1A;
                D_8004BCD0[arg0].unk19 = 2;
                D_8004BCD0[arg0].unk4 = (f32)sp2C;
                D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            }
            break;
        case 6:
            D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 + D_8004BCD0[arg0].unkC;
            if (D_8004BCD0[arg0].unk4 < (f32)(D_8004C6E4 + 1)) {
                D_8004BCD0[arg0].unk1A = 1 - D_8004BCD0[arg0].unk1A;
                D_8004BCD0[arg0].unk19 = 2;
                D_8004BCD0[arg0].unk4 = (f32)sp2C;
                D_8004BCD0[arg0].unk8 = (f32)(1 - D_8004BCD0[arg0].unk1A * 2);
            }
            break;
        }
        if (270.0f < D_8004BCD0[arg0].unk0) {
            D_8004BCD0[arg0].unk1A = 0;
            D_8004BCD0[arg0].unk8 = (f32)((f64)(u32)D_8004BCD0[arg0].unk1A - 0.5);
        } else if (D_8004BCD0[arg0].unk0 < 50.0f) {
            D_8004BCD0[arg0].unk1A = 1;
            D_8004BCD0[arg0].unk8 = (f32)((f64)(u32)D_8004BCD0[arg0].unk1A - 0.5);
        }
        if (D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0 < 8.0f && D_8004BCD0[D_8004C71F].unk0 - D_8004BCD0[arg0].unk0 < 8.0f) {
            if (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 < 3.0f && D_8004BCD0[D_8004C71F].unk4 - D_8004BCD0[arg0].unk4 < 8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002D6FC.s")
#endif

extern u8 D_80037788[];
extern u8 D_80037990[];

void func_8002E158(s32 arg0) {
    s32 sw;

    if (D_8004C71D == 0) {
        D_8004BCD0[arg0].unk0 += D_8004BCD0[arg0].unk8;
        D_8004BCD0[arg0].unk10 += 0.1;
        sw = (s32)D_8004BCD0[arg0].unk10;
        switch (sw & 1) {
        case 0:
            D_8004BCD0[arg0].unk14 = D_80037788;
            break;
        case 1:
            D_8004BCD0[arg0].unk14 = D_80037990;
            break;
        }
        D_8004BCD0[arg0].unk4 += D_8004BCD0[arg0].unkC;
        if (D_8004BCD0[arg0].unkC < 5.0f) {
            D_8004BCD0[arg0].unkC += 0.3;
        }
        if (D_8004BCD0[arg0].unk4 > 81.0f) {
            if (D_8004BCD0[arg0].unk0 < 220.0f) {
                D_8004BCD0[arg0].unk4 = 81.0f;
                D_8004BCD0[arg0].unkC = -3.5f;
                if (D_8004BCD0[arg0].unk0 > 40.0f) {
                    n_alSndpPlay(D_8076D1F8, 0x43, 0x7FFF, 0x3F, 1.0f, 0, 0);
                }
            } else if (D_8004BCD0[arg0].unk8 != 0.0f) {
                D_8004BCD0[arg0].unk8 = 0.0f;
                n_alSndpPlay(D_8076D1F8, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
            }
        }
        if (D_8004BCD0[arg0].unk4 > 271.0f) {
            D_8004BCD0[arg0].unk18 = 0;
        }
        if (arcadeAbs(D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0) < 7) {
            if (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 < 4.0f && D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 > -8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}

extern u8 D_80032228[];
extern u8 D_80032470[];
extern u8 D_800326B8[];
extern u8 D_80032900[];

void func_8002E3D4(s32 arg0) {
    s32 n;

    if (D_8004C71D == 0) {
        if (--D_8004BCD0[arg0].unk1C >= 0x15) {
            D_8004BCD0[arg0].unk1C = arcadeRand() & 0xF;
            D_8004BCD0[arg0].unk1D = !D_8004BCD0[arg0].unk1D;
        }
        switch (D_8004BCD0[arg0].unk19) {
        case 2:
            switch (D_8004BCD0[arg0].unk1D) {
            case 0:
                D_8004BCD0[arg0].unk14 = D_80032228;
                break;
            case 1:
                D_8004BCD0[arg0].unk14 = D_80032470;
                break;
            }
            n = arcadeMinFloat((u32)D_8004A76C, 5.0f);
            if (D_8004C722 == 4) {
                if ((f32)(0x64 - n * 0x14) == D_8004BCD0[arg0].unk10++) {
                    if (arcadeCountEntitiesByType(2) < n) {
                        D_8004BCD0[arg0].unk19 = 3;
                        D_8004BCD0[arg0].unk10 = 0.0f;
                    }
                }
            }
            break;
        case 3:
            if (D_8004BCD0[arg0].unk10++ > 40.0f) {
                D_8004BCD0[arg0].unk19 = 2;
                D_8004BCD0[arg0].unk10 = 0.0f;
                n = func_80024828();
                D_8004BCD0[n] = D_8004A3D8;
                D_8004BCD0[n].unk19 = 3;
                D_8004BCD0[n].unkC = -1.0f;
                if (D_8004C722 == 1) {
                    D_8004BCD0[n].unk8 = 0.4f;
                } else {
                    if (D_8004BCD0[D_8004C71F].unk0 < 160.0f) {
                        D_8004BCD0[n].unk8 = -0.5f;
                    } else {
                        D_8004BCD0[n].unk8 = 0.5f;
                    }
                    D_8004BCD0[n].unk1A = 0;
                    D_8004BCD0[n].unk0 = 160.0f;
                    D_8004BCD0[n].unk4 = 135.0f;
                }
            }
            switch (D_8004BCD0[arg0].unk1D) {
            case 0:
                D_8004BCD0[arg0].unk14 = D_800326B8;
                return;
            case 1:
                D_8004BCD0[arg0].unk14 = D_80032900;
                break;
            }
            break;
        }
    }
}

void func_8002E6E0(s32 arg0) {
    ArcadeEntity *entry = &D_8004BCD0[arg0];

    if (D_8004C722 == 2) {
        entry->unk1A = D_8004BCD0[D_8004C71F].unk0 < 160.0f;
        entry->unk0 = 152.0f;
        if (D_8004C708 == 2) {
            entry->unk1A = 0;
            entry->unk4 = 63.0f;
        }
    }
    if (D_8004C721 == 0) {
        entry->unk14 = NULL;
    } else {
        entry->unk14 = D_8003E438;
    }
}

void func_8002E794(s32 arg0) {
    ArcadeEntity *entry = &D_8004BCD0[arg0];

    if (D_8004C722 == 2) {
        entry->unk1A = D_8004BCD0[D_8004C71F].unk0 < 160.0f;
        entry->unk0 = 152.0f;
        if (D_8004C708 == 2) {
            entry->unk1A = 0;
            entry->unk4 = 79.0f;
        }
    }
    if (D_8004C721 == 0) {
        entry->unk14 = NULL;
        return;
    }
    if (entry->unk14 == NULL) {
        entry->unk14 = D_8003DB18;
    }
    if (D_8004C71D == 0) {
        if ((entry->unk1C++ & 0xC8) || (D_8004C724 == 1)) {
            entry->unk14 = D_8003DB18;
        } else {
            entry->unk14 = D_8003DD60;
        }
    }
}

void func_8002E8A0(s32 arg0) {
    D_8004BCD0[arg0].unk14 = D_8003AE58;
    if (D_8004C721 != 0) {
        D_8004BCD0[arg0].unk4 = D_8004BCD0[arcadeFindEntityByType(0x1A)].unk4 - 8.0f;
        D_8004BCD0[arg0].unk0 = D_8004BCD0[arcadeFindEntityByType(0x1A)].unk0;
    } else {
        if (D_8004BCD0[arg0 - 1].unk14 == NULL) {
            D_8004BCD0[arg0].unk14 = NULL;
        }
        D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0 - 1].unk4 + 20.0f;
        D_8004BCD0[arg0].unk0 = D_8004BCD0[arg0 - 1].unk0 + 30.0f;
    }
    D_8004BCD0[arcadeFindEntityByType(0x1A)].unk14 = NULL;
    D_8004BCD0[arcadeFindEntityByType(0x1B)].unk14 = NULL;
    if (arcadeFindEntityByType(0x1D) >= 0 && D_8004BCD0[arcadeFindEntityByType(0x1D)].unk14 != D_800389D0) {
        D_8004BCD0[arcadeFindEntityByType(0x1D)].unk14 = NULL;
    }
}

void func_8002E9DC(s32 arg0) {
    if (D_8004C722 == 2) {
        D_8004BCD0[arg0].unk0 = (D_8004BCD0[D_8004C71F].unk0 >= 160.0f) * 0x28 + 0x80;
        if (D_8004C708 == 2) {
            D_8004BCD0[arg0].unk1A = 0;
            D_8004BCD0[arg0].unk4 = 63.0f;
        }
    }
    if (D_8004C71D == 3) {
        if (D_8004C721 == 0) {
            D_8004BCD0[arg0].unk14 = D_80038BD8;
        } else {
            D_8004BCD0[arg0].unk14 = D_800389D0;
        }
        D_8004BCD0[arg0].unk1E = 0x10;
        D_8004BCD0[arg0].unk1F = 0x10;
        return;
    }
    if (D_8004C721 == 0) {
        D_8004BCD0[arg0].unk14 = NULL;
        return;
    }
    if (D_8004C71D == 0) {
        if (!(D_8004BCD0[arg0].unk1C++ & 0xC0)) {
            if (D_8004C722 == 2 || D_8004C722 == 4) {
                D_8004BCD0[arg0].unk14 = D_8003E868;
                return;
            }
            D_8004BCD0[arg0].unk14 = D_8003E680;
            return;
        }
        D_8004BCD0[arg0].unk14 = NULL;
    }
}

void func_8002EB40(s32 arg0) {
    s32 val;
    ArcadeEntity *entity;

    if (D_8004C71D == 0) {
        entity = &D_8004BCD0[arg0];
        entity->unk1D += D_8004A308[entity->unk1C];
        val = entity->unk1D;
        if (val < 0) {
            entity->unk1D = val + 0x2EE00;
            val = entity->unk1D;
        }
        switch ((val / 8) % 3) {
        case 0:
            entity->unk14 = D_80037B98;
            return;
        case 1:
            entity->unk14 = D_80037DA0;
            return;
        case 2:
            entity->unk14 = D_80037FA8;
            break;
        }
    }
}
extern u8 D_80041508[];
extern u8 D_80040540[];
extern u8 D_80044460[];
extern u8 D_80045428[];

void func_8002EC04(s32 arg0) {
    if (D_8004C6DC == 0x3C) {
        n_alSndpPlay(D_8076D1F8, 0x46, 0x7FFF, 0x3F, 1.0f, 0, 0);
    }
    if (D_8004C6DC >= 0x3C) {
        if (D_8004C6DC >= 0x169) {
            D_8004BCD0[arg0].unkC += 0.05;
            D_8004BCD0[arg0].unk4 += D_8004BCD0[arg0].unkC;
            D_8004BCD0[arg0].unk0 += D_8004BCD0[arg0].unk8;
            if (D_8004BCD0[arg0].unkC > 0.0f && D_8004BCD0[arg0].unk4 >= 38.0f) {
                D_8004C721 = 1;
                D_8004BCD0[arg0].unk4 = 38.0f;
                if (D_8004C6DC == 0x26C) {
                    n_alSndpPlay(D_8076D1F8, 0x53, 0x7FFF, 0x3F, 1.0f, 0, 0);
                    D_8004BCD0[arg0].unk14 = D_80041508;
                }
                if (D_8004C6DC == 0x2D0 || D_8004C6DC < 0x26C) {
                    D_8004BCD0[arg0].unk14 = D_80040540;
                }
                if (D_8004BCD0[arg0].unkC > 0.06) {
                    D_8004C708 += 1;
                    n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                }
                if (D_8004BCD0[arg0].unk0 > 74.0f && D_8004C6DC >= 0x1A5) {
                    D_8004BCD0[arg0].unk8 = -0.5f;
                    D_8004BCD0[arg0].unkC = -0.81f;
                    return;
                }
                D_8004BCD0[arg0].unk8 = 0.0f;
                D_8004BCD0[arg0].unkC = 0.0f;
            }
        } else {
            if (D_8004BCD0[arg0].unk4 > 74.0f) {
                D_8004BCD0[arg0].unkC = -2.0f;
                D_8004BCD0[arg0].unk8 = 0.0f;
                D_8004BCD0[arg0].unk4 = 0xC5 - ((D_8004C6DC - 0x3C) / 2);
                if (D_8004C6DC & 8) {
                    D_8004BCD0[arg0].unk14 = D_80044460;
                    return;
                }
                D_8004BCD0[arg0].unk14 = D_80045428;
            }
        }
    }
}

extern u8 D_8003E9F0[];
extern u8 D_80043498[];
extern u8 D_800463F0[];
extern ArcadeEntity D_8004A3B8;
void func_8002EEB8(s32 arg0) {
    s32 idx;
    s32 n;

    if (D_8004C71D == 0 || D_8004BCD0[arg0].unk19 == 5) {
        switch (D_8004BCD0[arg0].unk19) {
        case 12:
            D_8004BCD0[arg0].unk1C -= 1;
            if (D_8004BCD0[arg0].unk1C == 0) {
                D_8004BCD0[arg0].unk1C = 0x14;
                D_8004BCD0[arg0].unk19 = 9;
                D_8004BCD0[arg0].unk14 = D_8003E9F0;
                D_8004BCD0[arg0].unk1A = 0;
                idx = arcadeFindFreeEntity();
                D_8004BCD0[arg0].unk1D = idx;
                n = (s32)D_8004BCD0[arg0].unk10++;
                D_8004BCD0[idx] = D_8004A3B8;
                if (!(n & 7)) {
                    D_8004BCD0[idx].unk1D = 1;
                }
                if (n == 2 && D_8004C723 != 0) {
                    D_8004BCD0[idx].unk1C = 2;
                    return;
                }
                if (n == 1) {
                    if (D_8004C723 == 0) {
                        D_8004BCD0[idx].unk1C = 2;
                        return;
                    }
                    D_8004BCD0[idx].unk1C = 5;
                    return;
                }
                if (n != 0) {
                    if (!((f32)arcadeRand() < arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 2000.0f + 2048.0f)) {
                        return;
                    }
                }
                D_8004BCD0[idx].unk10 = 1.0f;
                if (n == 0) {
                    D_8004BCD0[idx].unk1D = 2;
                    if (D_8004A76C == 1) {
                        D_8004BCD0[idx].unk8 = 0.0f;
                        return;
                    }
                    if (D_8004A76C == 2) {
                        D_8004BCD0[idx].unk8 = 0.65f;
                        return;
                    }
                    D_8004BCD0[idx].unk8 = 0.77f;
                    return;
                }
                D_8004BCD0[idx].unk8 = (((f64)D_8004BCD0[D_8004C71F].unk0 - 92.0) / 200.0 + ((f64)arcadeRand() - 16384.0) / 30000.0) * arcadeMinFloat(3.0f, (f32)D_8004A76C);
                if ((f32)arcadeRand() < arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 2000.0f + 4096.0f) {
                    D_8004BCD0[idx].unk1C = 6;
                    if (D_80040540 == 0) {} // FAKE: empty guard steers regalloc
                    return;
                }
            } else if (D_8004BCD0[arg0].unk1C == 0x14) {
                D_8004C71E -= 1;
                return;
            }
            break;
        case 9:
            D_8004BCD0[arg0].unk1C -= 1;
            if (D_8004BCD0[arg0].unk1C == 0) {
                idx = D_8004BCD0[arg0].unk1D;
                D_8004BCD0[idx].unk0 = 92.0f;
                if (D_8004BCD0[idx].unk10 != 0.0f) {
                    D_8004BCD0[arg0].unk1C = 0x1E;
                    D_8004BCD0[arg0].unk19 = 0xB;
                    D_8004BCD0[arg0].unk14 = D_80040540;
                    D_8004BCD0[arg0].unk1A = 0;
                    D_8004BCD0[idx].unk19 = 7;
                    D_8004BCD0[idx].unk1C = 2;
                    return;
                }
                D_8004BCD0[arg0].unk1C = 0x3C;
                D_8004BCD0[arg0].unk19 = 0xA;
                D_8004BCD0[arg0].unk14 = D_80043498;
                D_8004BCD0[arg0].unk1A = 0;
                D_8004BCD0[idx].unk19 = 1;
                if (D_80040540 == 0) {} // FAKE: empty guard steers regalloc
                return;
            }
            break;
        case 11:
            D_8004BCD0[arg0].unk1C -= 1;
            if (D_8004BCD0[arg0].unk1C == 0) {
                D_8004BCD0[arg0].unk1C = (u8)(u32)((51.0f - arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 5.0f) + (f32)(arcadeRand() & 0xF));
                D_8004BCD0[arg0].unk19 = 0xC;
                D_8004BCD0[arg0].unk14 = D_800424D0;
                D_8004BCD0[arg0].unk1A = 0;
                if (D_80040540 == 0) {} // FAKE: empty guard steers regalloc
                return;
            }
            break;
        case 10:
            idx = D_8004BCD0[arg0].unk1D;
            D_8004BCD0[arg0].unk1C -= 1;
            if ((f32)(u32)D_8004BCD0[arg0].unk1C == arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 3.0f) {
                D_8004BCD0[arg0].unk1C = (u8)(u32)((51.0f - arcadeMinFloat((f32)(u32)D_8004A76C, 3.0f) * 5.0f) + (f32)(arcadeRand() & 0xF));
                D_8004BCD0[arg0].unk19 = 0xC;
                D_8004BCD0[arg0].unk14 = D_80040540;
                D_8004BCD0[arg0].unk1A = 0;
                return;
            }
            if (D_8004BCD0[arg0].unk1C == 0x28) {
                D_8004BCD0[arg0].unk14 = D_8003E9F0;
                D_8004BCD0[arg0].unk1A = 1;
                D_8004BCD0[idx].unk19 = 0;
                D_8004BCD0[idx].unk0 = 122.0f;
                D_8004BCD0[idx].unk4 = 83.0f;
                return;
            }
            if (D_8004BCD0[arg0].unk1C == 0x14) {
                D_8004BCD0[idx].unk19 = 2;
                return;
            }
            break;
        case 5:
            if (D_8004BCD0[arg0].unk10++ > 60.0f) {
                if (D_8004C721 != 0) {
                    D_8004BCD0[arg0].unk14 = D_800463F0;
                    D_8004BCD0[arg0].unk1A = (s32)(D_8004BCD0[arg0].unk10 / 8) & 1;
                } else {
                    D_8004BCD0[arg0].unk1A = 0;
                    if ((s32)(D_8004BCD0[arg0].unk10 / 8) & 1) {
                        D_8004BCD0[arg0].unk14 = D_80045428;
                    } else {
                        D_8004BCD0[arg0].unk14 = D_80044460;
                    }
                }
                if (D_8004C722 != 4) {
                    D_8004BCD0[arg0].unk0 = 100.0f;
                }
                D_8004BCD0[arg0].unk4 = D_8004BCD0[arg0].unk4 - 0.4;
                if (D_8004BCD0[arg0].unk4 < 23.0f) {
                    D_8004C721 = 0;
                }
                if (D_8004BCD0[arg0].unk10 > 280.0f) {
                    D_8004C723 += 1;
                    arcadeFinishStageIntro();
                    return;
                }
                if (D_8004BCD0[arg0].unk10 == 200.0f && D_8004C71E > 0) {
                    arcadeAddScore(D_8004C71E * 0x64);
                    return;
                }
            } else {
                D_8004BCD0[arg0].unk1A = 1;
                D_8004BCD0[arg0].unk14 = D_8003E9F0;
            }
            break;
        }
    }
}

extern u8 D_800473B8[];
extern u8 D_80048380[];
extern u8 D_80049348[];
extern s32 D_8004A75C;
extern ArcadeEntity D_8004A6F8;

void func_8002F82C(s32 arg0) {
    s32 cnt;

    switch (D_8004BCD0[arg0].unk19) {
    case 2:
        if (D_8004C71D == 0) {
            if (D_8004C6DC % 120 == 0) {
                D_8004C71E -= 1;
            }
            if (D_8004BCD0[D_8004C71F].unk4 < 95.0f && D_8004BCD0[D_8004C71F].unk4 > 76.0f) {
                if (D_8004BCD0[D_8004C71F].unk0 > 135.0f && D_8004BCD0[D_8004C71F].unk0 < 186.0f) {
                    arcadeKillPlayer();
                }
            }
            cnt = ++D_8004BCD0[arg0].unk1C;
            if ((u8)cnt < 0xA0) {
                D_8004BCD0[arg0].unk14 = D_80040540;
                return;
            }
            if (!(cnt & 0x1F)) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                cnt = D_8004BCD0[arg0].unk1C;
            }
            D_8004BCD0[arg0].unk14 = D_800424D0;
            D_8004BCD0[arg0].unk1A = ((cnt & 0x20) / 32) == (((cnt & 0x20) / 32) * 0); // FAKE: `x == x * 0` steers scheduling (x == 0)
        }
        break;
    case 8:
        if (D_8004BCD0[arg0].unk10++ == 720.0f) {
            D_8004C723 += 1;
            if (D_8004A740 != 0) {
                D_8004A770 = 1;
                if (D_8004A75C < D_8004A748) {
                    arcadeCheckGameOver();
                } else {
                    arcadeExit();
                }
            } else {
                arcadeFinishStageIntro();
            }
        } else {
            if (D_8004BCD0[arg0].unk10 > 480.0f) {
                break;
            }
            if (D_8004BCD0[arg0].unk10 == 400.0f) {
                if (D_8004C71E > 0) {
                    arcadeAddScore(D_8004C71E * 0x64);
                }
            } else if (D_8004BCD0[arg0].unk10 > 200.0f) {
                if (D_8004BCD0[arg0].unk4 < 178.0f) {
                    D_8004BCD0[arg0].unk1B = 1;
                    D_8004BCD0[arg0].unk4 += 1.0f;
                    if (D_8004BCD0[arg0].unk4 >= 178.0f) {
                        D_8004BCD0[arcadeFindFreeEntity()] = D_8004A6F8;
                    }
                } else {
                    if (D_8004C708 != 2) {
                        D_8004C708 = 2;
                        n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                    }
                    D_8004BCD0[arg0].unk4 = 178.0f;
                    D_8004BCD0[arg0].unk1A = 0;
                    if (((s32)(D_8004BCD0[arg0].unk10 / 6.0f) % 3) == 0) {
                        D_8004BCD0[arg0].unk14 = D_800473B8;
                    } else if (((s32)(D_8004BCD0[arg0].unk10 / 6.0f) % 3) == 1) {
                        D_8004BCD0[arg0].unk14 = D_80048380;
                    } else if (((s32)(D_8004BCD0[arg0].unk10 / 6.0f) % 3) == (0, 2)) {
                        D_8004BCD0[arg0].unk14 = D_80049348;
                    }
                    if (D_8004BCD0[arg0].unk10 == 350.0f) {
                        n_alSndpPlay(D_8076D1F8, 0x50, 0x7FFF, 0x3F, 1.0f, 0, 0);
                        D_8004BCD0[D_8004C71F].unk14 = D_8003B180;
                        D_8004BCD0[D_8004C71F].unk1A = 0;
                        D_8004BCD0[D_8004C71F].unk0 = 190.0f;
                        D_8004BCD0[D_8004C71F].unk4 = 93.0f;
                        D_8004C71D = 3;
                    }
                }
            } else if (D_8004BCD0[arg0].unk10 > 180.0f) {
                D_8004BCD0[arg0].unk1A = 0;
                D_8004BCD0[arg0].unk14 = D_80040540;
            } else if (D_8004BCD0[arg0].unk10 > 30.0f) {
                D_8004BCD0[arg0].unk1A = (s32)(D_8004BCD0[arg0].unk10 / 6.0f) & 1;
                D_8004BCD0[arg0].unk14 = D_800424D0;
            }
        }
        if (D_8004BCD0[arg0].unk10 == 2.0f) {
            n_alSndpPlay(D_8076D1F8, 0x52, 0x7FFF, 0x3F, 1.0f, 0, 0);
        }
        if (D_8004BCD0[arg0].unk10 == 200.0f) {
            n_alSndpPlay(D_8076D1F8, 0x44, 0x7FFF, 0x3F, 1.0f, 0, 0);
        }
        break;
    }
}

extern ArcadeEntity D_8004A418;

void func_8002FE28(s32 arg0) {
    s32 cnt;

    if (D_8004C71D == 0) {
        D_8004BCD0[arg0].unk10 += 1.0f;
        cnt = (s32)D_8004BCD0[arg0].unk10;
        if ((u8)cnt < 0xA0) {
            D_8004BCD0[arg0].unk14 = D_80040540;
        } else {
            if (!(cnt & 0x1F)) {
                n_alSndpPlay(D_8076D1F8, 0x42, 0x7FFF, 0x3F, 1.0f, 0, 0);
                cnt = (s32)D_8004BCD0[arg0].unk10;
            }
            D_8004BCD0[arg0].unk14 = D_800424D0;
            D_8004BCD0[arg0].unk1A = ((cnt & 0x20) / 32) == (((cnt & 0x20) / 32) * 0); // FAKE: `x == x * 0` steers scheduling (x == 0)
        }
        if ((s32)D_8004BCD0[arg0].unk10 % (0x72 - (s32)arcadeMinFloat((u32)D_8004A76C, 4.0f) * 0xC) == 0) {
            D_8004C71E -= 1;
            arg0 = arcadeFindFreeEntity();
            D_8004BCD0[arg0] = D_8004A418;
            D_8004BCD0[arg0].unk0 = (arcadeRand() & 0xF) - 0x1C;
            D_8004BCD0[arg0].unk19 = 2;
        }
    }
}

void func_80030044(s32 arg0) {
    s32 tmp;

    switch (D_8004BCD0[arg0].unk19) {
    case 2:
        tmp = 0;
        if (D_8004C71D != tmp) {
            return;
        }
        if (D_8004C6DC % 120 == 0) {
            D_8004C71E -= 1;
        }
        if (D_8004BCD0[arg0].unk0 > 204.0f) {
            D_8004BCD0[arg0].unk8 = -1.0f;
        }
        if (D_8004BCD0[arg0].unk0 < 68.0f) {
            D_8004BCD0[arg0].unk8 = 1.0f;
        }
        D_8004BCD0[arg0].unk10 += 1.0f;
        if ((u8)(s32)(tmp = D_8004BCD0[arg0].unk10) < 0xA0) {
            D_8004BCD0[arg0].unk14 = D_80040540;
        } else {
            D_8004BCD0[arg0].unk14 = D_800424D0;
            D_8004BCD0[arg0].unk1A = (((s32)D_8004BCD0[arg0].unk10 & 0x20) / 32) == ((((s32)D_8004BCD0[arg0].unk10 & 0x20) / 32) * 0); // FAKE: `x == x * 0` steers scheduling (x == 0)
        }
        break;
    case 5:
        if (D_8004BCD0[arg0].unk0 > 100.0f) {
            D_8004BCD0[arg0].unk8 = -1.0f;
        } else if (D_8004BCD0[arg0].unk0 < 100.0f) {
            D_8004BCD0[arg0].unk8 = 1.0f;
        } else {
            D_8004BCD0[arg0].unk18 = 0x16;
            D_8004BCD0[arg0].unk8 = 0.0f;
            D_8004BCD0[arg0].unk10 = 41.0f;
        }
        break;
    }
    if (!(D_8004C6DC & 1)) {
        D_8004A308[0] = (s32)D_8004BCD0[arg0].unk8;
        D_8004BCD0[arg0].unk0 += D_8004BCD0[arg0].unk8;
    }
}

void func_80030210(s32 arg0) {
    if (0.0f == D_8004BCD0[arg0].unk10) {
        n_alSndpPlay(D_8076D1F8, 0x45, 0x7FFF, 0x3F, 1.0f, 0, 0);
    }
    if (D_8004BCD0[arg0].unk10++ > 40.0f) {
        D_8004BCD0[arg0].unk18 = 0;
    }
}

void func_800302B4(s32 arg0) {
    if (D_8004BCD0[arg0].unk0 == (f32)(s32)D_8004BCD0[D_8004C71F].unk0 &&
        D_8004BCD0[arg0].unk4 == (f32)(s32)D_8004BCD0[D_8004C71F].unk4) {
        D_8004BCD0[arg0].unk18 = 0x14;
        if (D_8004A76C == 1) {
            D_8004BCD0[arg0].unk14 = D_800383B8;
            arcadeAddScore(0x12C);
        } else if (D_8004A76C == 2) {
            D_8004BCD0[arg0].unk14 = D_800385C0;
            arcadeAddScore(0x1F4);
        } else {
            D_8004BCD0[arg0].unk14 = D_800387C8;
            arcadeAddScore(0x320);
        }
    }
}

extern u8 D_800393F8[];
extern u8 D_80039640[];
extern u8 D_80039888[];
extern u8 D_80039AD0[];

void func_800303B8(u8 arg0) {
    s32 i;
    s32 idx;

    if (D_8004C71D == 0) {
        switch (D_8004BCD0[arg0].unk19) {
        case 0:
            if (D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0 < 8.0f && D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0 > -8.0f) {
                if (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 < 8.0f && D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 > -8.0f) {
                    arcadeStopSound(0x49);
                    D_8004C710 = 0x258;
                    D_8004BCD0[arg0].unk19 = 2;
                }
            }
            break;
        case 2:
            D_8004BCD0[arg0].unk1A = D_8004BCD0[D_8004C71F].unk1A;
            if ((D_8004C710 & 8) || D_8004BCD0[D_8004C71F].unk19 != 2) {
                if (D_8004C710 >= 0xF1 || (D_8004C710 & 4)) {
                    D_8004BCD0[arg0].unk14 = D_800393F8;
                } else {
                    D_8004BCD0[arg0].unk14 = D_80039888;
                }
                D_8004BCD0[arg0].unk0 = D_8004BCD0[D_8004C71F].unk0;
                D_8004BCD0[arg0].unk4 = D_8004BCD0[D_8004C71F].unk4 - 16.0f;
            } else {
                if (D_8004C710 >= 0xF1 || (D_8004C710 & 4)) {
                    D_8004BCD0[arg0].unk14 = D_80039640;
                } else {
                    D_8004BCD0[arg0].unk14 = D_80039AD0;
                }
                if (D_8004BCD0[arg0].unk1A != 0) {
                    D_8004BCD0[arg0].unk0 = D_8004BCD0[D_8004C71F].unk0 + 15.0f;
                } else {
                    D_8004BCD0[arg0].unk0 = D_8004BCD0[D_8004C71F].unk0 - 15.0f;
                }
                D_8004BCD0[arg0].unk4 = D_8004BCD0[D_8004C71F].unk4;
            }
            i = 0;
            do {
                if (D_8004BCD0[i].unk18 == 1 || D_8004BCD0[i].unk18 == 4 || D_8004BCD0[i].unk18 == 2) {
                    if (arcadeAbs(D_8004BCD0[i].unk0 - D_8004BCD0[arg0].unk0) < 0xD) {
                        if (arcadeAbs(D_8004BCD0[i].unk4 - D_8004BCD0[arg0].unk4) < 8) {
                            n_alSndpPlay(D_8076D1F8, 0x4B, 0x7FFF, 0x3F, 1.0f, 0, 0);
                            idx = (u8)func_800247F0();
                            D_8004BCD0[idx] = D_8004A618;
                            D_8004BCD0[idx].unk18 = 7;
                            D_8004BCD0[idx].unk1D = D_8004BCD0[i].unk18;
                            D_8004BCD0[idx].unk0 = D_8004BCD0[arg0].unk0;
                            D_8004BCD0[idx].unk4 = D_8004BCD0[arg0].unk4;
                            D_8004BCD0[i].unk18 = 0;
                            D_8004C71D = 1;
                        }
                    }
                }
            } while ((i = (u8)(i + 1)) < 0x50);
            if (D_8004C710-- == 1) {
                D_8004BCD0[arg0].unk18 = 0;
                arcadeStopSound(0);
                arcadeSetStageMusic();
            }
            break;
        }
    }
}

void func_80030734(u8 arg0) {
    ArcadeEntity *entity = &D_8004BCD0[arg0];
    u8 temp;
    u8 rand;

    if (entity->unk1C >= 0x37) {
        entity->unk14 = D_8003A3F0;
    } else {
        temp = (entity->unk1C / 6) % 3;
        if (temp == 0) {
            entity->unk14 = D_80039D18;
        } else if (temp == 1) {
            entity->unk14 = D_80039F60;
        } else {
            entity->unk14 = D_8003A1A8;
        }
    }
    if (entity->unk1C++ == 0x42) {
        entity->unk18 = 0x14;
        rand = arcadeRand();
        if (entity->unk1D == 2 && (rand & 3) == 0) {
            entity->unk14 = D_800387C8;
            arcadeAddScore(0x320);
        } else if (entity->unk1D == 2 && (rand & 3) == 1) {
            entity->unk14 = D_800385C0;
            arcadeAddScore(0x1F4);
        } else {
            entity->unk14 = D_800383B8;
            arcadeAddScore(0x12C);
        }
        entity->unk10 = 0.0f;
        D_8004C71D = 0;
    }
}

void func_80030880(u8 arg0) {
    if (D_8004BCD0[arg0].unk0 == (f32)(s32)D_8004BCD0[D_8004C71F].unk0) {
        f32 diff = D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4;
        if (diff < 20.0f && diff > -2.0f) {
            D_8004BCD0[arg0].unk1D = 1;
            return;
        }
    }
    if (D_8004BCD0[arg0].unk1D != 0) {
        D_8004BCD0[arg0].unk18 = 0;
        D_8004C718 = D_8004BCD0[arg0].unk1C ^ D_8004C718;
        if (D_8004C718) {
            ArcadeEntity *new_entity = &D_8004BCD0[(u8)func_800247F0()];
            *new_entity = D_8004A5F8;
            new_entity->unk0 = D_8004BCD0[D_8004C71F].unk0;
            new_entity->unk4 = D_8004BCD0[D_8004C71F].unk4 + 14.0f;
            new_entity->unk10 = 0.0f;
            arcadeAddScore(0x64);
        }
    }
}

void func_80030A04(u8 arg0) {
    f32 new_var;

    if (D_8004C71D == 0) {
        D_8004BCD0[arg0].unk10 -= 1.0f;
        new_var = D_8004BCD0[arg0].unk10;
        if (new_var < 0.0f) {
            D_8004BCD0[arg0].unk10 = (arcadeRand() & 0x7F) + 0x1C2;
        }
        new_var = D_8004BCD0[arg0].unk10 < 200.0f ? 0.2f : -0.2f;
        D_8004BCD0[arg0].unk4 += new_var;
        if (D_8004BCD0[arg0].unk4 < 97.0f) {
            D_8004BCD0[arg0].unk4 = 97.0f;
        }
        if (D_8004BCD0[arg0].unk4 > 110.0f) {
            D_8004BCD0[arg0].unk4 = 110.0f;
        }
    }
}

void func_80030B08(u8 arg0) {
    if (D_8004C71D == 0) {
        D_8004BCD0[arg0].unk0 += D_8004A308[D_8004BCD0[arg0].unk1C];
        if (D_8004BCD0[arg0].unk0 > 288.0f || D_8004BCD0[arg0].unk0 < 32.0f || (D_8004BCD0[arg0].unk0 == 160.0f && D_8004BCD0[arg0].unk4 == 127.0f)) {
            D_8004BCD0[arg0].unk18 = 0;
        }
        if (arcadeAbs(D_8004BCD0[arg0].unk0 - D_8004BCD0[D_8004C71F].unk0) < 12) {
            if (D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 < 4.0f && D_8004BCD0[arg0].unk4 - D_8004BCD0[D_8004C71F].unk4 > -8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}

void func_80030C70(u8 arg0) {
    if (460.0f < D_8004BCD0[arcadeFindEntityByType(0x17)].unk10) {
        return;
    }
    D_8004BCD0[arg0].unk1A = (D_8004BCD0[arg0].unk1C++ / 8) & 1;
}

extern u8 *D_80746800;

void arcadeUpdateNameEntryCursor(u8 arg0) {
    if (D_8004BCD0[arg0].unk19 != 4) {
        if ((*(u16 *)D_807ECDE8 & 0x200) || (s8)D_807ECDE8[2] < -0x14) {
            switch (--D_8004C720) {
            case 0:
                D_8004C720 = 8;
            case 0xB:
                D_8004BCD0[arg0].unk1D--;
                if (D_8004BCD0[arg0].unk1D >= 0x29) {
                    D_8004BCD0[arg0].unk1D = 0x1D;
                }
                break;
            }
        } else if ((*(u16 *)D_807ECDE8 & 0x100) || (s8)D_807ECDE8[2] >= 0x15) {
            switch (--D_8004C720) {
            case 0:
                D_8004C720 = 8;
            case 0xB:
                D_8004BCD0[arg0].unk1D++;
                if (D_8004BCD0[arg0].unk1D >= 0x1E) {
                    D_8004BCD0[arg0].unk1D -= 0x1E;
                }
                break;
            }
        } else {
            D_8004C720 = 0xC;
        }
        D_8004BCD0[arg0].unk0 = (D_8004BCD0[arg0].unk1D % 10) * 0x10 + 0x54;
        D_8004BCD0[arg0].unk4 = ((D_8004BCD0[arg0].unk1D / 10) << 7) / 7 + 0x4A;
        if (D_807ECD48 & 0x8000) {
            if (D_8004BCD0[arg0].unk1D == 0x1D || D_8004C6DC == 0x708) {
                D_8004C6DC = 0x744;
                D_8004A778[D_8004BCD0[arg0].unk1C][0] = D_8004A774[0];
                D_8004A778[D_8004BCD0[arg0].unk1C][1] = D_8004A774[1];
                D_8004A778[D_8004BCD0[arg0].unk1C][2] = D_8004A774[2];
                D_8004BCD0[arg0].unk19 = 4;
                arcadeSaveHighScores();
                return;
            }
            if (D_8004BCD0[arg0].unk1D == 0x1C) {
                if (D_8004BCD0[arg0].unk19 != 0) {
                    D_8004A774[--D_8004BCD0[arg0].unk19] = D_80746800[0x1C];
                    return;
                }
            }
            if (D_8004BCD0[arg0].unk19 < 3) {
                D_8004A774[D_8004BCD0[arg0].unk19] = D_80746800[D_8004BCD0[arg0].unk1D];
                D_8004BCD0[arg0].unk19++;
            }
        }
    }
}

void func_80030FB0(u8 arg0) {
    if (D_8004BCD0[arg0].unk1C >= D_8004C71E) {
        D_8004BCD0[arg0].unk18 = 0;
    }
}

/* ArcS2 declarations */
void func_8002CD64(s32);
void func_8002D6FC(s32);
void func_8002E158(s32);
void func_8002E3D4(s32);
void arcadeUpdatePlayerEntity(s32);
void func_8002E794(s32);
void func_8002E8A0(s32);
void func_8002E9DC(s32);
void func_8002E6E0(s32);
void func_8002EB40(s32);
void func_8002EC04(s32);
void func_8002EEB8(s32);
void func_8002F82C(s32);
void func_8002FE28(s32);
void func_80030044(s32);
void func_80030210(s32);
void func_800302B4(s32);
void func_800303B8(u8);
void func_80030734(u8);
void func_80030880(u8);
void func_80030A04(u8);
void func_80030B08(u8);
void func_80030C70(u8);
void arcadeUpdateNameEntryCursor(u8);
void func_80030FB0(u8);

void arcadeDispatchEntities(void) {
    u8 i = 0;

    do {
        switch (D_8004BCD0[i].unk18) {
        case 1:
            func_8002CD64(i);
            break;
        case 2:
            func_8002D6FC(i);
            break;
        case 3:
            func_8002E158(i);
            break;
        case 19:
            func_8002E3D4(i);
            break;
        case 13:
            arcadeUpdatePlayerEntity(i);
            break;
        case 26:
            func_8002E794(i);
            break;
        case 30:
            func_8002E8A0(i);
            break;
        case 29:
            func_8002E9DC(i);
            break;
        case 27:
            func_8002E6E0(i);
            break;
        case 18:
            func_8002EB40(i);
            break;
        case 21:
            func_8002EC04(i);
            break;
        case 22:
            func_8002EEB8(i);
            break;
        case 23:
            func_8002F82C(i);
            break;
        case 24:
            func_8002FE28(i);
            break;
        case 25:
            func_80030044(i);
            break;
        case 20:
            func_80030210(i);
            break;
        case 5:
            func_800302B4(i);
            break;
        case 6:
            func_800303B8(i);
            break;
        case 7:
            func_80030734(i);
            break;
        case 11:
            func_80030880(i);
            break;
        case 12:
            func_80030A04(i);
            break;
        case 9:
            arcadeUpdateNameEntryCursor(i);
            break;
        case 4:
            func_80030B08(i);
            break;
        case 15:
            func_80030C70(i);
            break;
        case 10:
            func_80030FB0(i);
            break;
        }
    } while (++i < 0x50);
}

extern ArcadeEntity D_8004A6D8;

void arcadeSpawnStage4Enemies(void) {
    u8 i;

    i = 0;
    if ((D_8004C6DC & 1) == 0) {
        D_8004A308[1] = 1;
        D_8004A308[2] = -1;
        if ((D_8004C6DC / 350) & 1) {
            D_8004A308[3] = 1;
        } else {
            D_8004A308[3] = -1;
        }
    } else {
        do {
            D_8004A308[i++] = 0;
        } while (i < 4);
    }
    if (D_8004C6DC % 120 == 0 && arcadeCountEntitiesByType(4) < 5) {
        i = arcadeFindFreeEntityAfterPlayer();
        D_8004BCD0[i] = D_8004A6D8;
        if (arcadeRand() > 0x4000) {
            if ((D_8004C6DC / 350) & 1) {
                D_8004BCD0[i].unk0 = 40.0f;
            } else {
                D_8004BCD0[i].unk0 = 280.0f;
            }
        } else {
            D_8004BCD0[i].unk4 = 127.0f;
            if (arcadeRand() > 0x4000) {
                D_8004BCD0[i].unk1C = 1;
                D_8004BCD0[i].unk0 = 40.0f;
            } else {
                D_8004BCD0[i].unk1C = 2;
                D_8004BCD0[i].unk0 = 280.0f;
            }
        }
    }
}

void arcadeSpawnStage2Enemies(void) {
    u8 idx;
    u8 r;

    if (D_8004C6DC % 200 == 0 && arcadeCountEntitiesByType(2) < 5) {
        idx = arcadeFindFreeEntityAfterPlayer();
        D_8004BCD0[idx] = D_8004A3D8;
        D_8004BCD0[idx].unk1A = 0;
        D_8004BCD0[idx].unk8 = -0.5f;
        D_8004BCD0[idx].unk0 = 244.0f;
        r = arcadeRand() & 7;
        if (r >= 4) {
            r = 1;
        }
        D_8004BCD0[idx].unk0 = D_8004A318[r * 2];
        D_8004BCD0[idx].unk4 = D_8004A318[r * 2 + 1];
        if (160.0f < D_8004BCD0[D_8004C71F].unk0) {
            D_8004BCD0[idx].unk1A = 1 - D_8004BCD0[idx].unk1A;
            D_8004BCD0[idx].unk8 = -D_8004BCD0[idx].unk8;
            D_8004BCD0[idx].unk0 = 320.0f - D_8004BCD0[idx].unk0;
        }
    }
    if (D_8004C718 == 0) {
        arcadeStopSound(0);
        D_8004C718 = 1;
        D_8004C708 = 1;
        D_8004C71D = 2;
        D_8004BCD0[arcadeFindEntityByType(0x17)].unk19 = 8;
    }
}

s32 _sprintf(char *, const char *, ...);
extern u8 D_8004A82C[5][3];
extern u8 D_8004BCEC;

void arcadeDrawNameRegistration(Gfx **arg0) {
    s32 i;
    Gfx *g;
    char buf[0x50];

    g = *arg0;
    if (D_8004C724 == 3) {
        arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
        arcadeSetTextPosition(0x78, 0x3B);
        _sprintf(buf, "NAME %.3s", D_8004A774);
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0xA0, 0x41);
        _sprintf(buf, "---");
        arcadeDrawString(&g, buf);
        if (D_8004C6DC < 0x708) {
            arcadeSetTextPosition(0x60, 0x7B);
            _sprintf(buf, "REGI TIME <%02d>", 0x1E - D_8004C6DC / 0x3C);
        } else {
            arcadeSetTextPosition(0x40, 0x7B);
            _sprintf(buf, "YOUR NAME WAS");
            arcadeDrawString(&g, buf);
            arcadeSetTextPosition(0xB0, 0x7B);
            _sprintf(buf, "REGISTERED.");
        }
        arcadeDrawString(&g, buf);
        arcadeSetTextColor(0xFF, 0, 0, 0xFF);
        arcadeSetTextPosition(0x58, 0x2B);
        _sprintf(buf, "NAME REGISTRATION");
        arcadeDrawString(&g, buf);
        arcadeSetTextColor(0, 0xFF, 0, 0xFF);
        arcadeSetTextPosition(0x58, 0x4B);
        _sprintf(buf, "A B C D E F G H I J");
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0x58, 0x5B);
        _sprintf(buf, "K L M N O P Q R S T");
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0x58, 0x6B);
        _sprintf(buf, "U V W X Y Z . -");
        arcadeDrawString(&g, buf);
        arcadeSetTextPosition(0xD4, 0x6B);
        _sprintf(buf, "ba");
        arcadeDrawString(&g, buf);
    }
    arcadeSetTextColor(0xFF, 0, 0, 0xFF);
    for (i = 0; i < 5; i++) {
        if (i == 3) {
            arcadeSetTextColor(0xFF, 0xFF, 0, 0xFF);
        }
        arcadeSetTextPosition(0x38, 0x8B + i * 0x10);
        if (i == D_8004BCD0[0].unk1C && (D_8004C6DC & 0x20) && D_8004C724 == 3) {
            _sprintf(buf, "%.3s", D_8004A82C[i]);
        } else {
            _sprintf(buf, "%.3s  %06d  %.3s", D_8004A82C[i], D_8004A74C[i], D_8004A778[i]);
        }
        arcadeDrawString(&g, buf);
    }
    arcadeSetTextColor(0, 0xFF, 0, 0xFF);
    arcadeSetTextPosition(0xB8, 0xDB);
    _sprintf(buf, "CREDIT 00");
    arcadeDrawString(&g, buf);
    *arg0 = g;
}

void arcadeSetStageTextColor(s8 arg0) {
    if (arg0 == D_8004A768) {
        arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    } else if (D_8004C722 == 2) {
        arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
    } else {
        arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
    }
}

extern s32 D_8004A83C;
extern u8 D_8003DA90[];
typedef struct ArcadeGfxSlot {
    u8 pad[0x18];
} ArcadeGfxSlot;
extern ArcadeGfxSlot D_8004BBF0[];
#define ArcL8_P6D0 (*(void **)&D_8004C6D0)

void arcadeDrawHud(Gfx **arg0) {
    s32 i;
    Gfx *g;
    char buf[0x50];
    char *p;
    u8 n;

    g = *arg0;
    p = (char *)g++;
    ((Gfx *)p)->words.w0 = 0xED000000; ((Gfx *)p)->words.w1 = 0x5003C0;
    p = buf;
    D_8004C6D4 = 0x400;
    D_8004C719 = 8;
    ArcL8_P6D0 = D_8003DA90;
    D_8004C71A = 8;
    func_80005A90(&D_8004BBF0[D_807444FC], ArcL8_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    dlAppendTextureLoad(&g, &D_8004BBF0[D_807444FC]);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    if (D_8004A83C == 0) { // FAKE: empty guard steers regalloc
    }
    for (i = 0; i < D_8004C71C; i++) {
        dlAppendTextureRectangle(&g, i * 0x20 + 0x360, 0x4C);
    }
    arcadeSetTextColor(0xFF, 0, 0, 0xFF);
    if ((D_8004C6D8 & 0x10) || D_8004C724 == 0) {
        arcadeSetTextPosition(0x48, 0x13);
        _sprintf(p, "1UP");
        arcadeDrawString(&g, p);
    }
    arcadeSetTextPosition(0x78, 0x13);
    _sprintf(p, "HIGH SCORE");
    arcadeDrawString(&g, p);
    arcadeSetTextColor(0, 0, 0xFF, 0xFF);
    arcadeSetTextPosition(0xD8, 0x1B);
    _sprintf(p, "L=%02d", D_8004A76C);
    arcadeDrawString(&g, p);
    arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    arcadeSetTextPosition(0x38, 0x1B);
    _sprintf(p, "%06d    %06d", D_8004A748, D_8004A760);
    arcadeDrawString(&g, p);
    if (D_8004C724 == 5 || D_8004C724 == 4) {
        if (D_8004A764 != 0) {
            if (D_8004C722 == 2) {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            } else if (D_8004C722 == 4) {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
            }
            arcadeSetTextPosition(0x78, 0xA3);
            _sprintf(p, "GAME OVER");
            arcadeDrawString(&g, p);
        }
        if (D_8004C724 == 4) {
            if (D_8004A768 == 0 || D_8004C722 == 4) {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else if (D_8004C722 == 2) {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            } else {
                arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
            }
            arcadeSetStageTextColor(0);
            arcadeSetTextPosition(0x88, 0x8B);
            _sprintf(p, "RETURN");
            arcadeDrawString(&g, p);
            arcadeSetStageTextColor(1);
            arcadeSetTextPosition(0x68, 0x9B);
            _sprintf(p, "DELETE HISCORE");
            arcadeDrawString(&g, p);
            arcadeSetStageTextColor(2);
            arcadeSetTextPosition(0x68, 0xAB);
            _sprintf(p, "EXIT DK ARCADE");
            arcadeDrawString(&g, p);
        }
        if (D_8004C722 == 2) {
            if (D_8004C71E < 0xA) {
                arcadeSetTextColor(0, 0, 0xFF, 0xFF);
            } else {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            }
        } else if (D_8004C722 == 4) {
            if (D_8004C71E < 0xA) {
                arcadeSetTextColor(0xF0, 0x30, 0, 0xFF);
            } else {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            }
        } else {
            if (D_8004C71E < 0xA) {
                arcadeSetTextColor(0xFF, 0, 0, 0xFF);
            } else {
                arcadeSetTextColor(0x60, 0xE0, 0xFF, 0xFF);
            }
        }
        arcadeSetTextPosition(0xE0, 0x30);
        if (D_8004C71E > 0) {
            i = D_8004C71E;
        } else {
            i = 0;
        }
        _sprintf(p, "%02d00", i);
        arcadeDrawString(&g, p);
    }
    if (D_8004C724 == 2) {
        n = (D_8004C723 & 3) + 1;
        arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
        arcadeSetTextPosition(0x48, 0xD7);
        _sprintf(p, "HOW HIGH CAN YOU GET ?");
        arcadeDrawString(&g, p);
        arcadeSetTextPosition(0x58, 0xC9);
        _sprintf(p, "@%% m");
        arcadeDrawString(&g, p);
        if (n >= 2) {
            arcadeSetTextPosition(0x58, 0xAD);
            _sprintf(p, "%%) m");
            arcadeDrawString(&g, p);
        }
        if (n >= 3) {
            arcadeSetTextPosition(0x58, 0x91);
            _sprintf(p, "&%% m");
            arcadeDrawString(&g, p);
        }
        if (n >= 4) {
            arcadeSetTextPosition(0x50, 0x75);
            _sprintf(p, "!)) m");
            arcadeDrawString(&g, p);
        }
    }
    if (D_8004C724 == 3) {
        arcadeDrawNameRegistration(&g);
    }
    if (D_8004C724 == 0) {
        if (!(D_8004C6DC & 0x200)) {
            arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
            arcadeSetTextPosition(0x70, 0x33);
            _sprintf(p, "INSERT COIN");
            arcadeDrawString(&g, p);
            arcadeSetTextPosition(0x68, 0x43);
            _sprintf(p, "PLAYER    COIN");
            arcadeDrawString(&g, p);
            arcadeSetTextPosition(0x78, 0x53);
            _sprintf(p, "1        1");
            arcadeDrawString(&g, p);
            arcadeSetTextPosition(0x38, 0x7B);
            _sprintf(p, "RANK  SCORE  NAME");
            arcadeDrawString(&g, p);
            arcadeDrawNameRegistration(&g);
            arcadeSetTextColor(0xFF, 0, 0, 0xFF);
            arcadeSetTextPosition(0x78, 0x63);
            _sprintf(p, "2        2");
            arcadeDrawString(&g, p);
        } else {
            if (D_8004C6DC & 0x182) {
                arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
            } else {
                arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
            }
            arcadeSetTextPosition(0x68, 0xD7);
            _sprintf(p, "c NINTENDO 1981");
            arcadeDrawString(&g, p);
        }
    }
    *arg0 = g;
    D_8004A83C++;
}

