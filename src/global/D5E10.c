#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern u16 D_807FD63C;

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D1110.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D11FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D1238.s")

void func_806D1270(void) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D1278.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D12CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D1420.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D1568.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D19A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D1B60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D1D3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D1D84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D1DEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D1E90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D1F28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D205C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D21E4.s")

typedef struct G09Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ struct G09ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[6];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0x52];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[4];
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x88];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ void *unk174;
} G09Actor;

typedef struct G09ActorSub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} G09ActorSub4;

#define G09_A ((G09Actor *)D_807FBB40)

s32 func_806DF6D4();
void func_80614E78(Actor *, s32);

void func_806D2238(void) {
    func_806DF6D4(1);
    if (G09_A->unk155 == 0) {
        func_80614E78(D_807FBB40, 0);
        G09_A->unk155 = 1;
        G09_A->unk60 &= ~4;
    }
}

void func_806D22A0(void) {
    func_806DF6D4(1);
}

void func_806D22C0(void) {
    func_806DF6D4(0x62);
    switch (G09_A->unk155) {
        case 1:
        case 2:
            G09_A->unk155++;
            break;
        case 0:
        case 0x3C:
        case 0x3D:
            break;
        default:
            G09_A->unk155++;
    }
}

void *func_80610FE8(s32);
void actorRegisterGlobalCallback(ActorCallbackNode *);

void func_806D2330(void *arg0) {
    ActorCallbackNode *node;

    node = func_80610FE8(0x14);
    node->callback = arg0;
    node->unk8 = (s32)D_807FBB48;
    node->unk4 = 1;
    actorRegisterGlobalCallback(node);
}

void actorSnapToBone();

void func_806D2378(void) {
    func_806D2330(&actorSnapToBone);
}

typedef struct G09Player {
    /* 0x000 */ u8 pad0[0x54];
    /* 0x054 */ f32 unk54;
    /* 0x058 */ u8 pad58[0x30];
    /* 0x088 */ G09Actor *unk88;
    /* 0x08C */ u8 unk8C;
    /* 0x08D */ u8 pad8D[0x35];
    /* 0x0C2 */ s16 unkC2;
    /* 0x0C4 */ u8 padC4[0x12C];
    /* 0x1F0 */ s32 unk1F0;
} G09Player;

#define G09_P ((G09Player *)D_807FD580)

extern s32 D_8076A0A8;
s32 func_80629148();
void func_806CC970();
void func_806CC948();

void func_806D239C(void) {
    func_806D2378();
    switch (D_8076A0A8) {
        case 0x37:
            func_806DF6D4(0x5F);
            func_806CC970();
            return;
        case 0x6A:
            func_806DF6D4(0x60);
            func_806CC970();
            return;
        case 0x4D:
        case 0x81:
        case 0x82:
            if ((G09_P->unk1F0 & 8) && (func_80629148() != 0)) {
                G09_P->unk88->unk154 = 0xA;
                G09_A->unk155++;
            }
            func_806DF6D4(0x5B);
            func_806CC970();
            return;
        default:
            func_806DF6D4(0x5C);
            G09_A->unkC0 = G09_A->unkC8;
            func_806CC948();
            return;
    }
}

void func_806D24A8(void) {
    func_806D2378();
    func_806DF6D4(0x5D);
    G09_A->unkC0 = G09_A->unkC8;
    func_806CC948();
}

void func_806CFD68();
void func_806CFECC();

void func_806D24E4(void) {
    func_806D2378();
    switch (G09_A->unk155) {
        case 0:
            func_806DF6D4(0x5E);
            func_806CC948();
            return;
        case 1:
            G09_A->unkC0 = G09_P->unk54;
            func_806CFECC();
            G09_A->unk155++;
            func_806DF6D4(0x5E);
            func_806CFD68();
            func_806CC948();
            return;
        case 2:
            func_806CC948();
            func_806DF6D4(0x5E);
            func_806CFD68();
            return;
        case 3:
            func_806DF6D4(0x5C);
            func_806CC948();
            return;
    }
}

void func_806D25CC(void) {
    switch (D_8076A0A8) {
        case 0x6A:
            func_806DF6D4(0x60);
            func_806CC970();
            break;
        case 0x37:
            func_806DF6D4(0x5F);
            func_806CC970();
            break;
        case 0x4D:
            func_806DF6D4(0x5B);
            func_806CC970();
            break;
        default:
            func_806DF6D4(0x5C);
            G09_A->unkC0 = G09_A->unkC8;
            func_806CC948();
            break;
    }
}

void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_806F4D70(u8, f32, f32, f32, f32);

void func_806D266C(void) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    func_806D2378();
    func_806D25CC();
    actorGetNodePos(D_807FBB40, 3, &sp2C, &sp28, &sp24);
    func_806F4D70(D_807FC929, sp2C, sp28, sp24, 25.0f);
}

void func_806D26D8(void) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    func_806D2378();
    func_806D25CC();
    actorGetNodePos(D_807FBB40, 2, &sp2C, &sp28, &sp24);
    func_806F4D70(D_807FC929, sp2C, sp28, sp24, 25.0f);
}

void actorSyncTransformFromParent();

void func_806D2744(s32 arg0) {
    func_806D2330(&actorSyncTransformFromParent);
    func_806DF6D4(arg0);
    G09_A->unk6C = G09_A->unk6A;
}

void func_806D2784(void) {
    func_806D2744(0x61);
}

void func_805FF8F8(void);
s32 func_8061CB98();
void func_80614EBC(Actor *, s32);

void func_806D27A4(void) {
    func_806D2744(0x63);
    if (func_8061CB98(5) != 0) {
        if (G09_A->unk4->unk64 != 0x3B0) {
            func_80614EBC(D_807FBB40, 0x3B0);
        }
        if ((func_80629148() != 0) || (G09_A->unk155 != 0)) {
            func_805FF8F8();
        }
    }
}

void func_806EB0C0();

void func_806D281C(void) {
    s16 *sp;

    sp = G09_P->unk88->unk174;
    if (G09_A->unk155 != 0) {
        G09_A->unk154 = 0x6D;
        G09_A->unk155 = 0;
    } else {
        func_806EB0C0(0x3C, 0, D_807FC929, sp);
    }
    *sp += G09_P->unkC2;
    if (G09_P->unkC2 >= 8) {
        G09_P->unkC2 -= 7;
    } else if (G09_P->unkC2 < -7) {
        G09_P->unkC2 += 7;
    } else {
        G09_P->unkC2 = 0;
    }
    func_806D2744(1);
}

void func_806D28E4(void) {
    func_806D2744(0x64);
}

void func_806319C4();
void func_806CFF9C();

void func_806D2904(void) {
    func_806319C4(D_807FBB40, 0);
    if (G09_A->unk155++ >= 0xC9) {
        func_806CFF9C(D_807FBB40);
    }
}

typedef struct G09Sub568 {
    /* 0x0 */ u8 pad0[2];
    /* 0x2 */ u8 unk2;
} G09Sub568;

extern G09Sub568 *D_807FD568;
s32 func_805FCA64();
void renderCallbacksRegister();
void func_806FF01C();
void func_806FF75C();

void func_806D2954(s16 arg0) {
    if ((G09_P->unk8C != 0) && (func_805FCA64() != 0)) {
        if (D_807FD568->unk2 == 7) {
            arg0 = 0xF;
            renderCallbacksRegister(&func_806FF75C, D_807FBB40, 5);
        } else {
            arg0 = 0xE;
            renderCallbacksRegister(&func_806FF01C, D_807FBB40, 5);
        }
    }
    if (G09_A->unk155 != 0) {
        arg0 = 5;
        G09_A->unk155--;
    }
    func_806DF6D4(arg0);
}

void func_806FF32C();
void func_806FF358();

void func_806D2A14(s16 arg0) {
    if (G09_A->unk155 != 0) {
        arg0 = 5;
        G09_A->unk155--;
    }
    if (func_805FCA64(arg0) != 0) {
        if (func_806DF6D4(arg0) == 0) {
            renderCallbacksRegister(&func_806FF358, D_807FBB40, 3);
        }
        renderCallbacksRegister(&func_806FF32C, D_807FBB40, 3);
    }
}

s32 actorSpawn();
void func_806FFB2C();

void func_806D2AA0(s16 arg0) {
    func_806DF6D4(1);
    if (G09_A->unk155 < 6) {
        renderCallbacksRegister(&func_806FFB2C, D_807FBB40, 3);
        G09_A->unk155++;
    } else {
        G09_A->unk154 = arg0;
        G09_A->unk155 = 0;
    }
    if (G09_A->unk155 == 2) {
        actorSpawn(0xCA, 0x8D);
        G09_P->unk88 = (G09Actor *)D_807FBB44;
        *(void **)((G09Actor *)D_807FBB44)->unk174 = D_807FD580;
        G09_P->unk1F0 |= 0x8000;
    }
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D2B90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D2BB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D2BD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D2C54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D2CAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D2D38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D2DC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D2E9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3224.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D32C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D332C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D34B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3530.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3608.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D36CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D374C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D37CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D38AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3A38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3AC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3AE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3B08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3B28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3B48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3BC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3CD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3D5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3DE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D3FA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D4010.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D423C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D428C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D45A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D4758.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D491C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D4A70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D4C7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D4DE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D5008.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D5218.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D5300.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D57F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D5834.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D59E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D5B44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D5CCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D61B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D6558.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D69A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D6B00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D6F0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D6F64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D7098.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D7170.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D7238.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D72D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D7510.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D7704.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D7878.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D79E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D7A28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D7DF8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D7E88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D7F48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D7FE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D8070.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D80A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D8308.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D850C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D87FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D8A64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D8B08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D8FCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D9134.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D9184.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D91A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D9320.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D97A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D9820.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D9924.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D9940.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D9AD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D9D58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D9FD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DA320.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DA3E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DA4D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DA7EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DA89C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DA94C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DAA14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DAADC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DABE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DADA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DAF5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DB08C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DB0C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DB3AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DB670.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DBB04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DC170.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DC3A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DC410.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DCA7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DCF60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DD24C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DD874.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DDAB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DE264.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DE930.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DE9F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DEAA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DECD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DED44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DF050.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DF1A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DF280.s")
