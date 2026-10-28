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

void func_80024D90(void);
void arcadeDispatchEntities(void);
void func_800259D0(Gfx **);
void arcadeRenderEntities(Gfx **);
void func_8002AFA4(Gfx **, s32);
void arcadeInitStage(void);
#define ArcR1_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
Gfx *func_806FD490(Gfx *, s32, s16, s16, s32);
extern s16 D_8004C72E;
extern s16 D_8004C732;
extern u8 D_8004C725;
extern u8 D_8004C726;
extern u8 D_8004C727;
extern u8 D_8004C728;

void controllerStartRead(void);
void controllerUpdate(void);
void func_80610044(Gfx *, s32, s32, s32, s32, s32);
Gfx *func_80704484(Gfx *, s32);
void func_805FE71C(Gfx *, u8, s32 *, s32);
void func_805FE7B4(Gfx *, u8 *, s32 *, s32);
Gfx *func_805FE4D4(Gfx *);
void arcadeDispatchState(Gfx **);
void func_8002419C(u8 *, Gfx **);

extern u8 D_807444FC;
extern Gfx *D_8076A050[];
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern s32 D_8076A064;
extern u8 *D_8076A048;
extern u8 D_80767CE8;
extern u8 D_8076A0B1;
extern f32 D_807FD888;
extern u8 D_807444EC;
extern void *D_8076A080;
extern Gfx D_1000090;
extern Gfx D_1000040;

void func_80024000(void) {
    Gfx *sp2C;
    u8 *sp28;

    controllerStartRead();
    func_80610044(D_8076A050[D_807444FC], D_8076A088, 3, 1, 0x4D2, 1);
    D_807444FC ^= 1;
    D_8076A064++;
    D_8076A048 = (u8 *)&D_80767CE8 + D_807444FC * 0x11B0;
    controllerUpdate();
    if ((D_8076A0B1 & 1) && D_807FD888 == 31.0f) {
        sp2C = D_8076A050[D_807444FC];
    } else {
        func_8002419C(D_8076A048, &sp2C);
    }
    sp2C = func_80704484(sp2C, 0);
    if (D_807444EC != 3) {
        sp28 = D_8076A048 + 0xDB0;
        func_805FE71C(sp2C, D_807444FC, &D_8076A088, 0);
        func_805FE7B4((Gfx *)sp28, D_8076A048, &D_8076A08C, 1);
    } else {
        func_805FE71C(sp2C, D_807444FC, &D_8076A088, 1);
    }
}

void func_8002419C(u8 *arg0, Gfx **arg1) {
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

void arcadeDrawString(Gfx **arg0, s32 arg1) {
    Gfx *g = *arg0;

    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200004);
    gDPSetPrimColor(g++, 0, 0, D_8004C725, D_8004C726, D_8004C727, D_8004C728);
    ArcR1_WRITE_GFX(g++, 0xFC119623, 0xFF2FFFFF);
    ArcR1_WRITE_GFX(g++, 0xE200001C, 0x00504240);
    *arg0 = func_806FD490(g, 2, D_8004C72E, D_8004C732, arg1);
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
void func_80024E84(Gfx **);
void arcadeStageIntroLoop(Gfx **);
void arcadeGameplayLoop(Gfx **);
void func_800255F4(Gfx **);
void arcadeAttractLoop(Gfx **);
void arcadeDemoLoop(Gfx **);
void func_800319D4(Gfx **);
extern s32 D_8004A78C[];
extern s32 D_8004A790;
extern s32 D_8004C6D8;

void arcadeDispatchState(Gfx **arg0) {
    Gfx *sp1C = *arg0;

    if (D_8004A78C[0] != 0) {
        D_8004A78C[0] = 0;
        D_8004C722 = 1;
        func_80024D90();
        arcadeLoadHighScores();
    }
    switch (D_8004C724) {
    case 0:
        func_80024E84(&sp1C);
        break;
    case 1:
        arcadeStageIntroLoop(&sp1C);
        break;
    case 5:
        arcadeGameplayLoop(&sp1C);
        break;
    case 4:
        func_800255F4(&sp1C);
        break;
    case 3:
        arcadeAttractLoop(&sp1C);
        break;
    default:
        arcadeDemoLoop(&sp1C);
        break;
    }
    func_800319D4(&sp1C);
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
    func_800259D0(&sp1C);
    arcadeDispatchEntities();
    arcadeRenderEntities(&sp1C);
    if (D_8004C6DC >= 0x7BD) {
        if (D_8004A740 != 0) {
            arcadeExit();
        } else {
            func_80024D90();
        }
    }
    *arg0 = sp1C;
}
extern ArcadeEntity D_8004A538;
extern u8 D_800424D0[];
void func_80024D90(void) {
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
void func_80024E84(Gfx **arg0) {
    Gfx *sp24;
    s32 i;
    s32 idx;

    sp24 = *arg0;
    D_8004C6DC++;
    func_800259D0(&sp24);
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

void func_800257D8(void);
void arcadeStageIntroLoop(Gfx **arg0) {
    Gfx *sp1C = *arg0;
    arcadeDispatchEntities();
    func_800259D0(&sp1C);
    arcadeRenderEntities(&sp1C);
    if (D_8004C6DC++ >= 0x2F9) {
        func_800257D8();
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
void func_8002549C(void);
void func_800311E0(void);
void func_800313B8(void);
void arcadeGameplayLoop(Gfx **arg0) {
    Gfx *sp34 = *arg0;

    func_800259D0(&sp34);
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
        D_8004BCE9[arcadeFindEntityByType(0xD) << 5] = 2;
    }
    arcadeDispatchEntities();
    arcadeRenderEntities(&sp34);
    if (D_8004C71D == 0) {
        if (D_8004C722 == 2) {
            func_800313B8();
        }
        if (D_8004C722 == 4) {
            func_800311E0();
        }
        if (D_807ECD48 & 0x1000) {
            func_8002549C();
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

void func_8002549C(void) {
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

void func_8060C8AC(s32);
void func_800255F4(Gfx **arg0) {
    Gfx *sp2C;

    sp2C = *arg0;
    func_800259D0(&sp2C);
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
                func_8060C8AC(2);
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
void func_800257D8(void) {
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
    func_800259D0(&sp1C);
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
void func_80026680();
void func_800268AC();
void func_80026EF4();
void func_800275E8();
void func_80027A38();
typedef struct ArcR2_Entity {
    void *ptr;
} ArcR2_Entity;
typedef struct ArcR2_Struct48 {
    s32 words[12];
} ArcR2_Struct48;
extern ArcR2_Struct48 D_8004A798;
extern u8 D_8004C719;
extern u8 D_8004C71A;
extern u8 D_807444FC;
extern u8 D_8004BB00[];
extern u8 D_80032C20[];
extern u8 D_80032DF8[];
void func_80005A90(void *, void *, s32, u8, u8, u8, s32, s32, s32, s32);
void func_8070E8F0(s32 *, void *);
void func_8070F2C8(s32, s16, s32, u8);
void func_80025C08();
void func_8070F2FC(s32 *, s16, s16);
void arcadeStopSound(s32);
extern s32 D_8076D1F8;
void func_800259D0(arg0)
Gfx **arg0;
{
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
            func_80026680(&sp4C);
        }
        break;
    case 1:
    case 4:
    case 5:
        switch (D_8004C722) {
        case 1:
            func_800268AC(&sp4C);
            break;
        case 2:
            func_80026EF4(&sp4C);
            break;
        case 3:
            func_800275E8(&sp4C);
            break;
        default:
            func_80027A38(&sp4C);
            break;
        }
        break;
    }
    *arg0 = sp4C;
}

#ifdef NON_MATCHING
#define ArcA1_D6D0 (*(void **)&D_8004C6D0)
void func_80025C08(arg0, arg1, arg2, arg3)
s32 *arg0;
s32 arg1;
s32 arg2;
s32 arg3;
{
    s32 i;
    s32 sp60;

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
    func_8070E8F0(&sp60, D_8004BB30 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    for (i = 0; i < arg3 / 4; i++) {
        func_8070F2FC(&sp60, arg1 * 4, (s32)((f64)(arg2 + 8 + i * 4) * 4.0));
    }
    D_8004C71A = arg3 % 4;
    if (D_8004C71A != 0) {
        switch (D_8004C71A) {
        case 1:
            func_8070E8F0(&sp60, D_8004BB60 + D_807444FC * 0x18);
            break;
        case 2:
            func_8070E8F0(&sp60, D_8004BB90 + D_807444FC * 0x18);
            break;
        case 3:
            func_8070E8F0(&sp60, D_8004BBC0 + D_807444FC * 0x18);
            break;
        }
        func_8070F2C8(0x400, D_8004C6D6, 0, 0);
        func_8070F2FC(&sp60, arg1 * 4, (s32)((f64)(i * 4 + arg2 + 8) * 4.0));
    }
    *arg0 = sp60;
}
#else

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80025C08.s")
#endif

void func_80026050(arg0)
Gfx **arg0;
{
    Gfx *sp2C;
    s32 sp28;

    sp2C = *arg0;
    func_80025C08(&sp2C, 0x70, 0x1C, 0x2E);
    func_80025C08(&sp2C, 0x80, 0x1C, 0x2E);
    func_80025C08(&sp2C, 0xB0, 0x38, 0x12);
    if (D_8004C724 == 1) {
        if (D_8004C6DC < 0x190) {
            sp28 = 0x82 - (((s32) (D_8004C6DC - 0x3C) / 20) * 8);
            if (sp28 >= 0x83) {
                sp28 = 0x82;
            }
            if (sp28 < 0x22) {
                sp28 = 0x22;
            }
            func_80025C08(&sp2C, 0xA0, 0x51, sp28);
            func_80025C08(&sp2C, 0xB0, 0x51, sp28);
        }
    } else {
        func_80025C08(&sp2C, 0x88, 0x50, 4);
        func_80025C08(&sp2C, 0x88, 0x5B, 0xC);
        func_80025C08(&sp2C, 0xE8, 0x53, 0xE);
        func_80025C08(&sp2C, 0x50, 0x70, 0xE);
        func_80025C08(&sp2C, 0x78, 0x6E, 0x12);
        func_80025C08(&sp2C, 0xD8, 0x69, 8);
        func_80025C08(&sp2C, 0xD8, 0x7D, 8);
        func_80025C08(&sp2C, 0x70, 0x87, 5);
        func_80025C08(&sp2C, 0x70, 0x99, 8);
        func_80025C08(&sp2C, 0xA8, 0x89, 0x16);
        func_80025C08(&sp2C, 0xE8, 0x8D, 0xE);
        func_80025C08(&sp2C, 0x50, 0xAA, 0xE);
        func_80025C08(&sp2C, 0x90, 0xA6, 0x15);
        func_80025C08(&sp2C, 0x80, 0xC1, 4);
        func_80025C08(&sp2C, 0x80, 0xD1, 8);
        func_80025C08(&sp2C, 0xE8, 0xC7, 0xE);
    }
    *arg0 = sp2C;
}

void func_8002628C(arg0)
Gfx **arg0;
{
    Gfx *sp24;

    sp24 = *arg0;
    func_80025C08(&sp24, 0x38, 0xBD, 0x1C);
    func_80025C08(&sp24, 0x100, 0xBD, 0x1C);
    func_80025C08(&sp24, 0x40, 0x9B, 0x1C);
    func_80025C08(&sp24, 0xF8, 0x9B, 0x1C);
    func_80025C08(&sp24, 0x48, 0x7A, 0x1A);
    func_80025C08(&sp24, 0xF0, 0x7A, 0x1A);
    func_80025C08(&sp24, 0x50, 0x58, 0x1C);
    func_80025C08(&sp24, 0xE8, 0x58, 0x1C);
    if (D_8004C708 == 0) {
        func_80025C08(&sp24, 0x98, 0xBD, 0x1C);
        func_80025C08(&sp24, 0x78, 0x9B, 0x1C);
        func_80025C08(&sp24, 0xC0, 0x9B, 0x1C);
        func_80025C08(&sp24, 0x98, 0x7A, 0x1A);
        func_80025C08(&sp24, 0x70, 0x58, 0x1C);
        func_80025C08(&sp24, 0xC8, 0x58, 0x1C);
    }
    *arg0 = sp24;
}

void func_800263EC(arg0)
Gfx **arg0;
{
    Gfx *sp24;

    sp24 = *arg0;
    func_80025C08(&sp24, 0x70, 0x1C, 0x31);
    func_80025C08(&sp24, 0x80, 0x1C, 0x31);
    func_80025C08(&sp24, 0xB0, 0x38, 0x15);
    func_80025C08(&sp24, 0xD0, 0x54, 0x15);
    func_80025C08(&sp24, 0x100, 0x62, 0x1C);
    func_80025C08(&sp24, 0xB8, 0x77, 0x15);
    func_80025C08(&sp24, 0x40, 0x7E, 0x2A);
    func_80025C08(&sp24, 0x70, 0x7E, 0x38);
    func_80025C08(&sp24, 0x80, 0x7E, 0x38);
    func_80025C08(&sp24, 0xE8, 0x85, 0x15);
    func_80025C08(&sp24, 0x100, 0xA8, 0xE);
    func_80025C08(&sp24, 0x38, 0xAF, 0x1C);
    *arg0 = sp24;
}

void func_80026518(arg0)
Gfx **arg0;
{
    Gfx *sp24;

    sp24 = *arg0;
    func_80025C08(&sp24, 0x70, 0x1C, 0x31);
    func_80025C08(&sp24, 0x80, 0x1C, 0x31);
    func_80025C08(&sp24, 0xB0, 0x38, 0x15);
    func_80025C08(&sp24, 0x48, 0xBD, 0x1C);
    func_80025C08(&sp24, 0x80, 0xBD, 0x1C);
    func_80025C08(&sp24, 0xB8, 0xBD, 0x1C);
    func_80025C08(&sp24, 0xF0, 0xBD, 0x1C);
    func_80025C08(&sp24, 0x70, 0x9A, 0x1C);
    func_80025C08(&sp24, 0xC0, 0x9A, 0x1C);
    func_80025C08(&sp24, 0x48, 0x77, 0x1C);
    func_80025C08(&sp24, 0x80, 0x77, 0x1C);
    func_80025C08(&sp24, 0xB8, 0x77, 0x1C);
    func_80025C08(&sp24, 0xF0, 0x77, 0x1C);
    func_80025C08(&sp24, 0x40, 0x62, 0xE);
    func_80025C08(&sp24, 0xF8, 0x62, 0xE);
    *arg0 = sp24;
}

#ifdef NON_MATCHING
#define ArcA1_P6D0 (*(void **)&D_8004C6D0)
void func_80026680(Gfx **arg0) {
    Gfx *sp94;
    ArcR2_Struct48 sp64;
    s32 i;
    s32 j;
    s32 row;

    sp64 = D_8004A798;
    sp94 = *arg0;
    D_8004C719 = 8;
    D_8004C71A = 8;
    D_8004C6D4 = 0x400;
    if (D_8004C6DC & 0x182) ArcA1_P6D0 = D_80032C20;
    else ArcA1_P6D0 = D_80032DF8;
    func_80005A90(D_8004BB00 + D_807444FC * 0x18, ArcA1_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_8070E8F0((s32 *)&sp94, D_8004BB00 + D_807444FC * 0x18);
    func_8070F2C8(0x400, ((s16 *)&D_8004C6D4)[1], 0, 0);
    for (i = 0; i < 12; i++) {
        row = sp64.words[i];
        for (j = 0; j < 25; j++) {
            if ((1 << j) & row) {
                func_8070F2FC((s32 *)&sp94, 0x3E0 - (j << 5), (s32)((f64)(i * 8 + 0x3F) * 4.0));
            }
        }
    }
    *arg0 = sp94;
}
#else

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80026680.s")
#endif

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800268AC.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80026EF4.s")

void func_800274E0(arg0, arg1, arg2, arg3)
Gfx **arg0;
u8 arg1;
u8 arg2;
s16 arg3;
{
    u8 i;
    Gfx *sp40;

    sp40 = *arg0;
    i = arg1;
    if (arg1 < arg2) {
        do {
            func_8070F2FC((s32 *)&sp40, (s16) ((i << 5) + 0xC0), (s16) (s32) ((((f64) arg3 * 0.875) + 8.0) * 4.0));
            i++;
        } while (i < arg2);
    }
    *arg0 = sp40;
}

#ifdef NON_MATCHING
#define ArcA1_P6D0 (*(void **)&D_8004C6D0)
typedef struct ArcA1_Pt {
    u8 x;
    u8 y;
    s16 z;
} ArcA1_Pt;
typedef struct ArcA1_Bar {
    f32 x;
    f32 y;
    f32 vy;
} ArcA1_Bar;
extern u8 D_80032F40[];
extern u8 D_80034568[];
extern ArcA1_Pt D_8004A7C8[];
extern u8 D_8004BC50[];
extern ArcA1_Bar D_8004BC88[];
void func_800275E8(Gfx **arg0) {
    s32 pad[2];
    Gfx *sp90;
    s32 i;
    s32 j;
    ArcA1_Pt *pt;
    ArcA1_Bar *bar;

    D_8004C719 = 2;
    D_8004C71A = 8;
    D_8004C6D4 = 0x400;
    ArcA1_P6D0 = D_80032F40;
    sp90 = *arg0;
    func_80005A90(D_8004BC50 + D_807444FC * 0x18, D_80032F40, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_8070E8F0((s32 *)&sp90, D_8004BC50 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    i = 0x28;
    do {
        func_8070F2FC((s32 *)&sp90, 0x15C, (s32)((f64)(s32)((f64)i + 51.625 + 8.0) * 4.0));
        i += 8;
    } while (i < 0xA0);
    i = 0x28;
    do {
        func_8070F2FC((s32 *)&sp90, 0x25C, (s32)((f64)(s32)((f64)i + 51.625 + 8.0) * 4.0));
        i += 8;
    } while (i != 0xA0);
    D_8004C719 = 8;
    D_8004C71A = 0xA;
    D_8004C6D4 = 0x492;
    ArcA1_P6D0 = D_80034568;
    func_80005A90(D_8004BB00 + D_807444FC * 0x18, D_80034568, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_8070E8F0((s32 *)&sp90, D_8004BB00 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    pt = D_8004A7C8;
    do {
        func_800274E0(&sp90, pt->x, pt->y, pt->z);
        pt++;
    } while (pt < D_8004A7C8 + 21);
    bar = D_8004BC88;
    do {
        j = 0;
        if (D_8004C71D == 0 && D_8004C724 == 5) {
            bar->y = bar->y + bar->vy;
            if (bar->y < 99.0f) {
                bar->y = bar->y + 144.0f;
            }
            if (bar->y > 243.0f) {
                bar->y = bar->y - 144.0f;
            }
        }
        do {
            func_8070F2FC((s32 *)&sp90, (s32)((bar->x + 40.0f + (f32)j) * 4.0f), (s32)(((f64)bar->y * 0.875 + 8.0) * 4.0));
            j += 8;
        } while (j != 0x10);
        bar++;
    } while (bar != (ArcA1_Bar *)D_8004BCD0);
    func_800263EC(&sp90);
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
extern u8 D_8004BC50[];
void func_80027A38(Gfx **arg0) {
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
    func_8070E8F0((s32 *)&sp6C, D_8004BB00 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    x = 0x220;
    do {
        func_8070F2FC((s32 *)&sp6C, x, 0xE0);
        x += step;
    } while (x < 0x2E0);
    x = 0xC0;
    do {
        func_8070F2FC((s32 *)&sp6C, x, 0x380);
        x += step;
    } while (x < 0x440);
    i = 1;
    do {
        if (i != 6 && i != 7 && i != 0x13 && i != 0x14) {
            func_8070F2FC((s32 *)&sp6C, (s16)((i << 5) + 0xC0), 0x268);
        }
        i += one;
    } while (i < 0x1B);
    ArcA3_P6D0 = D_80032CA8;
    func_80005A90(D_8004BC20 + D_807444FC * 0x18, ArcA3_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_8070E8F0((s32 *)&sp6C, D_8004BC20 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    x = 0xE0;
    do {
        func_8070F2FC((s32 *)&sp6C, x, 0x150);
        x += step;
    } while (x < 0x420);
    i = 0;
    do {
        if (i < 0xC || i >= 0x10) {
            func_8070F2FC((s32 *)&sp6C, (s16)((i << 5) + 0xC0), 0x1DC);
        }
        i += one;
    } while (i < 0x1C);
    x = 0xE0;
    do {
        func_8070F2FC((s32 *)&sp6C, x, 0x2F4);
        x += step;
    } while (x < 0x420);
    ArcA3_P6D0 = D_800342B8;
    func_80005A90(D_8004BC50 + D_807444FC * 0x18, ArcA3_P6D0, 0, D_8004C719, D_8004C719, D_8004C71A, 0, 2, 0, 0);
    func_8070E8F0((s32 *)&sp6C, D_8004BC50 + D_807444FC * 0x18);
    func_8070F2C8(0x400, D_8004C6D6, 0, 0);
    x = 0x240;
    do {
        for (i = 0x9F; (i ^ 0) != 0x87; i -= 8) {
            func_8070F2FC((s32 *)&sp6C, x, (s16)(s32)((((f64)i * 0.875) + 8.0) * 4.0));
        }
        x += step;
    } while (x != 0x2C0);
    func_80026518(&sp6C);
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
void func_80027F0C(void) {
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
    i = D_8004C71F & 0;
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
    D_8004BCD0[i] = D_8004A718; D_8004BCD0[i].unk1C = 2; D_8004BCD0[i].unk4 = 65.0f; i--; D_8004BCD0[i] = D_8004A718; D_8004BCD0[i].unk1C = 3;
    D_8004BCD0[i].unk0 = 48.0f;
    D_8004BCD0[i].unk4 = 65.0f;
    D_8004C708 = 7;
}

typedef struct ArcA3_Tbl16 {
    u8 b[16];
} ArcA3_Tbl16;
extern ArcA3_Tbl16 D_8004A81C;
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
void func_8002843C(void) {
    s32 bit;
    s32 idx;
    s32 i;
    ArcA3_Tbl16 tbl;

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
s32 func_80029EFC(s32, s32);
s32 arcadeCheckStage4Collision(s32, s32);


s32 arcadeCheckStage1Ladders(s32, s32);
s32 arcadeCheckStage2Ladders(s32, s32);
s32 arcadeCheckStage3Ladders(s32, s32);
s32 arcadeCheckStage4Ladders(s32, s32);


void func_80005A90(void *, void *, s32, u8, u8, u8, s32, s32, s32, s32);
void func_8070E8F0(s32 *, void *);
void func_8070F2C8(s32, s16, s32, u8);
void func_8070F2FC(s32 *, s16, s16);
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

void func_80027F0C(void);
void func_8002843C(void);
void func_800289F0(void);
void func_800290F0(void);

extern ArcadeEntity D_8004A478;
extern ArcadeEntity D_8004A598;
extern ArcadeEntity D_8004A3D8;
typedef struct ArcA4_Bar {
    f32 x;
    f32 y;
    f32 vy;
} ArcA4_Bar;
#ifndef NON_MATCHING
extern ArcA4_Bar D_8004BC88[];
#endif
void func_800289F0(void) {
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
    i = D_8004C71F & 0;
    i = i + 0x24;
    p = &D_8004BCD0[i]; *p = D_8004A478;
    p->unk0 = 144.0f;
    i--;
    p = &D_8004BCD0[i]; *p = D_8004A478;
    p->unk1B = 1;
    p->unk4 = 238.0f;
    i--;
    p = &D_8004BCD0[i]; *p = D_8004A478;
    p->unk1B = 1;
    p->unk0 = 144.0f;
    p->unk4 = 238.0f;
    i--;
    p = &D_8004BCD0[i]; *p = D_8004A618;
    p->unk14 = D_80038FE8;
    p->unk0 = 260.0f;
    p->unk4 = 103.0f;
    i--;
    p = &D_8004BCD0[i]; *p = D_8004A618;
    p->unk14 = D_800391F0;
    p->unk0 = 60.0f;
    p->unk4 = 135.0f;
    i = arcadeFindFreeEntity();
    p = &D_8004BCD0[i]; *p = D_8004A3D8;
    p->unk1A = 1;
    p->unk8 = 0.5f;
    p->unk0 = 114.0f;
    p->unk4 = 135.0f;
    i = arcadeFindFreeEntity();
    p = &D_8004BCD0[i]; *p = D_8004A3D8;
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
void func_800290F0(void) {
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
        func_80027F0C();
        break;
    case 2:
        func_8002843C();
        break;
    case 3:
        func_800289F0();
        break;
    default:
        func_800290F0();
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

extern ArcA4_Bar D_8004BCAC[];

s32 func_80029EFC(s32 arg0, s32 arg1) {
    s32 ret;
    ArcA4_Bar *bar;
    ArcA4_Bar *end;

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
        end = (ArcA4_Bar *)(s32)&D_8004BCAC;
        for (bar = (ArcA4_Bar *)D_8004BC88; ; ) {
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
        end = (ArcA4_Bar *)D_8004BCD0;
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
        return func_80029EFC(arg0, arg1);
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
    var_v0 = (s32) D_8004BCD4;
    if (var_v0 == 0x61) {
        var_v0 = 0x57;
    } else {
        var_v0 = 0x74;
    }
    if (arcadeCheckLadderBounds(arg0, arg1, 0x44, 0x57, var_v0, 0x7F)) {
        return 1;
    }
    var_v0 = (s32) D_8004BCF4;
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

void func_8002AFA4(Gfx **arg0, s32 arg1) {
    s32 sp4C;
    s32 off;

    {
        f32 scale;
        if (D_8004A338[D_8004BCD0[arg1].unk18] & 1) {
            scale = 1024.0f;
        } else {
            scale = 1170.2858f;
    }
    off = arg1 * 0x18;
    func_80005A90(D_8004AC00 + D_807444FC * 0x780 + off, D_8004BCD0[arg1].unk14, 0, D_8004BCD0[arg1].unk1E, D_8004BCD0[arg1].unk1E, D_8004BCD0[arg1].unk1F, 0, 2, 0, 0);
    sp4C = (s32)*arg0;
    func_8070E8F0(&sp4C, D_8004AC00 + D_807444FC * 0x780 + off);
    func_8070F2C8(0x400, (s32)scale, (u8)(D_8004BCD0[arg1].unk1A & 1), D_8004BCD0[arg1].unk1B);
    }
    if (D_8004A338[D_8004BCD0[arg1].unk18] & 2) {
        func_8070F2FC(&sp4C, (s32)(D_8004BCD0[arg1].unk0 - (f32)(u32)D_8004A358[D_8004BCD0[arg1].unk18]) * 4, (s32)((f64)(D_8004BCD0[arg1].unk4 - (f32)(u32)D_8004A378[D_8004BCD0[arg1].unk18]) * 0.875 + 8.0) * 4);
    } else {
        if (D_8004BCD0[arg1].unk18 == 2) {
            off = (s32)D_8004BCD0[arg1].unk10;
            if (off >= 3) {
                off = 5 - off;
            }
        } else {
            off = 0;
        }
        func_8070F2FC(&sp4C, (s32)(D_8004BCD0[arg1].unk0 - (f32)(u32)D_8004A358[D_8004BCD0[arg1].unk18]) * 4, (s32)(((f64)(D_8004BCD0[arg1].unk4 - (f32)off - (f32)(u32)D_8004A378[D_8004BCD0[arg1].unk18]) * 0.875 + 8.0) * 4.0));
    }
    *arg0 = (Gfx *)sp4C;
}

void arcadeRenderEntities(Gfx **arg0) {
    s32 i;
    Gfx *sp38;
    sp38 = *arg0;
    for (i = 0; i < 80; i++) {
        if (D_8004BCD0[i].unk18 != 0 && D_8004BCD0[i].unk14 != 0) {
            if (D_8004BCD0[i].unk18 >= 8 || D_8004C71D < 2) {
                func_8002AFA4(&sp38, i);
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

#ifdef NON_MATCHING
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

void func_8002B390(s32 arg0) {
    s32 val;
    ArcadeEntity *ptr = &D_8004BCD0[arg0];
    s32 b;
    s32 t;
    s32 s4;
    s32 s0;
    f32 fs0;
    f32 y;

    b = D_8004BCD0[arg0].unk1A & 2;
    D_8004BCD0[arg0].unk1A = b / 2 | b;
    D_8004BCD0[arg0].unk1B = 0;
    val = (s32)D_8004BCD0[arg0].unk10;
    if (D_8004BCD0[arg0].unk19 == 2) {
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
                    func_80024D90();
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
                func_800257D8();
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
            t = (s32)D_8004BCD0[arg0].unk10 & 3;
            if (t == 2) {
                ptr->unk1A ^= 1;
                t = (s32)D_8004BCD0[arg0].unk10 & 3;
            }
            if (t == 1) {
                D_8004BCD0[arg0].unk1B = !D_8004BCD0[arg0].unk1B;
            }
        }
    } else {
        D_8004BCD0[arg0].unk14 = D_8003D170;
    }
}
#else

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002B390.s")
#endif

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002B89C.s")

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

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002CD64.s")

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
extern s32 D_8004A318[][2];
extern u8 D_8004BCE9[];

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002D6FC.s")

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
            if (D_8004BCD0[arg0].unk4 - *(f32 *)((u8 *)&D_8004BCD4 + (D_8004C71F << 5)) < 4.0f && D_8004BCD0[arg0].unk4 - *(f32 *)((u8 *)&D_8004BCD4 + (D_8004C71F << 5)) > -8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002E3D4.s")

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

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8002EEB8.s")

extern u8 D_800473B8[];
extern u8 D_80048380[];
extern u8 D_80049348[];
extern u8 D_8003B180[];
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
            D_8004BCD0[arg0].unk1A = ((cnt & 0x20) / 32) == (((cnt & 0x20) / 32) * 0);
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
                func_800257D8();
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
            D_8004BCD0[arg0].unk1A = ((cnt & 0x20) / 32) == (((cnt & 0x20) / 32) * 0);
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
            D_8004BCD0[arg0].unk1A = (((s32)D_8004BCD0[arg0].unk10 & 0x20) / 32) == ((((s32)D_8004BCD0[arg0].unk10 & 0x20) / 32) * 0);
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
    s32 cond;

    if (0.0f == D_8004BCD0[arg0].unk10) {
        n_alSndpPlay(D_8076D1F8, 0x45, 0x7FFF, 0x3F, 1.0f, 0, 0);
    }
    cond = 0;
    if (D_8004BCD0[arg0].unk10 > 40.0f) {
        cond = 1;
    }
    D_8004BCD0[arg0].unk10 += 1.0f;
    if (cond) {
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
            if (D_8004BCD0[arg0].unk4 - *(f32 *)((u8 *)&D_8004BCD4 + (D_8004C71F << 5)) < 4.0f && D_8004BCD0[arg0].unk4 - *(f32 *)((u8 *)&D_8004BCD4 + (D_8004C71F << 5)) > -8.0f) {
                arcadeKillPlayer();
            }
        }
    }
}

void func_80030C70(u8 arg0) {
    s32 temp_v1;

    if (460.0f < D_8004BCD0[arcadeFindEntityByType(0x17)].unk10) {
        return;
    }
    temp_v1 = D_8004BCD0[arg0].unk1C;
    D_8004BCD0[arg0].unk1C = (D_8004BCD0[arg0].unk1A = (temp_v1 / 8) & 1, temp_v1 + 1);
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_80030CEC.s")

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
void func_8002B89C(s32);
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
void func_80030CEC(u8);
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
            func_8002B89C(i);
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
            func_80030CEC(i);
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

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800311E0.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800313B8.s")

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_8003159C.s")

void arcadeSetStageTextColor(s8 arg0) {
    if (arg0 == D_8004A768) {
        arcadeSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    } else if (D_8004C722 == 2) {
        arcadeSetTextColor(0xFF, 0xA0, 0x10, 0xFF);
    } else {
        arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
    }
}

#pragma GLOBAL_ASM("asm/arcade/nonmatchings/0/func_800319D4.s")
