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

typedef struct G08Slot {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x32];
} G08Slot;

typedef struct G08Player {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 pad26[6];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0xC];
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A[6];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[0x16];
    /* 0x68 */ f32 unk68;
    /* 0x6C */ u8 pad6C[0x184];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0x48];
    /* 0x23C */ u16 unk23C;
} G08Player;

typedef struct G08Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
    /* 0x66 */ u8 pad66[0x12];
    /* 0x78 */ s32 unk78;
} G08Sub4;

typedef struct G08Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G08Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x62];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0x12];
    /* 0x080 */ f32 unk80;
    /* 0x084 */ u8 pad84[0x28];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[8];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x1C];
    /* 0x0E4 */ u8 unkE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x54];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0xF];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G08Actor;

#define G08_P ((G08Player *)D_807FD580)
#define G08_A48 ((G08Actor *)D_807FBB48)
#define G08_A40 ((G08Actor *)D_807FBB40)

extern u32 D_807FBB60;
extern G08Slot D_807FD63A[];
s32 func_806DF6D4();
void func_806319C4();
void func_806CFF9C();
void func_806EB0C0();
void func_806CC8B8();
void func_806CC8F0();
void func_806C8D20();

void func_806D1110(void) {
    func_806EB0C0(0x3C, 0, D_807FC929);
    func_806DF6D4(0xB);
    G08_A48->unkB8 = G08_P->unk4;
    G08_A48->unkEE = G08_P->unkA;
    G08_A48->unkE6 = G08_P->unkA;
    func_806CC8F0();
    if (!(D_807FD63A[D_807FC929].unk0 & 0x200C)) {
        func_806CFF9C(D_807FBB40);
        func_806C8D20(D_807FBB40);
    } else {
        G08_A40->unk144 = 1;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D11FC(void) {
    if (D_807FBB40->unkAC < D_807FBB40->unk80 + 4.5f) {
        D_807FBB40->unk80 = D_807FBB40->unkAC - 4.5f;
    }
}

void func_806D1238(void) {
    func_806DF6D4(0x66);
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D1270(void) {
}

void func_806D1278(void) {
    func_806DF6D4(1);
    if (!(D_807FD580->unk1F0 & 0x10000)) {
        func_806CFF9C(D_807FBB40);
    }
    func_806319C4(D_807FBB40, 0);
}

f32 func_806CD898(f32, f32, f32);
void func_80614EBC(Actor *, s32);

void func_806D12CC(void) {
    G08_A40->unkC0 = func_806CD898(G08_A40->unkC0, 50.0f, 4.0f);
    switch (G08_A40->unk155) {
        case 0:
            G08_P->unk24 = 0;
            G08_P->unk38 = 100.0f;
            func_806DF6D4(0x67);
            func_806CC8F0();
            G08_A40->unk155++;
            break;
        case 1:
            func_806CC8F0();
            if ((G08_A40->unkB8 > 10.0f) && (G08_A40->unk4->unk64 != 0x317)) {
                func_80614EBC(D_807FBB40, 0x317);
            } else if ((G08_A40->unkB8 == 0.0f) && (G08_A40->unk4->unk64 != 0x314)) {
                func_80614EBC(D_807FBB40, 0x314);
            }
            func_806DF6D4(0x67);
            break;
    }
    func_806D11FC();
    func_806319C4(D_807FBB40, 0);
}

void func_806DF494();
s32 func_806D1080(f32, f32);
void func_806CC948();

void func_806D1420(void) {
    G08Actor *a;

    G08_P->unk24 = 0;
    if (G08_A40->unk155 == 0) {
        G08_P->unk48 = 0xA;
        G08_A40->unkC4 = -8.0f;
        G08_A40->unkE8 = func_806D1080(G08_A40->unkB8, G08_A40->unkC0);
        func_806DF494(G08_A40->unkE4, 0, 0x32);
        func_806DF494(&G08_A40->unkE8, (s16)func_806D1080(G08_A40->unkB8, G08_A40->unkC0), 0xA);
        func_806DF6D4(0x6A);
        a = G08_A40;
        a->unkEE = a->unkE6;
        func_806CC948(a);
    }
    if ((G08_A40->unk80 + 4.0f < G08_A40->unkAC) && (G08_A40->unkC0 < 0.0f)) {
        G08_A40->unk154 = 0x7F;
        G08_A40->unk155 = 0;
        G08_P->unk1C = 2.0f;
    }
    func_806319C4(D_807FBB40, 0);
}

extern f32 D_80753AFC[];
extern s16 D_80753A78[];
f32 sqrtf(f32);
void func_80614D00(void *, f32, f32);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void func_806CC5DC();
void func_806CC638(f32);

void func_806D1568(void) {
    f64 temp0;
    f64 temp1;
    f32 temp2;

    G08_P->unk24++;
    G08_P->unk2C = D_80753AFC[D_807FD584];
    switch (G08_A40->unk155) {
        case 0:
            func_806DF6D4(0x4C);
            temp2 = -G08_A40->unkC0 * 0.125;
            G08_A40->unkC0 = func_806CD898(G08_A40->unkC0, 0.0f, temp2);
            if (G08_P->unk24 >= 6) {
                if ((G08_A40->unkB8 != 0.0f) || (G08_P->unk10 != 0)) {
                    G08_A40->unk155 = 3;
                } else {
                    G08_A40->unk155 = 2;
                }
                G08_A40->unk4->unk78 &= ~0x4000;
            }
            func_806CC5DC();
            break;
        case 1:
            func_806DF494(&G08_A40->unkE8, (s16)func_806D1080(G08_A40->unkB8, G08_A40->unkC0), 0x32);
            G08_P->unk38 = 500.0f;
            func_806DF6D4(0x57);
            func_806CC638(0.0f);
            if (G08_P->unk10 == 0) {
                G08_A40->unk155 = 3;
            }
            break;
        case 2:
            func_806DF6D4(0x55);
            func_806CC638(0.0f);
            if (G08_A40->unk154 == 0x7F) {
                if (G08_A40->unkB8 != 0.0f) {
                    G08_P->unk18 = 0;
                    G08_A40->unk155 = 3;
                } else {
                    if (G08_P->unk50 != 0) {
                        G08_P->unk50--;
                        if (G08_P->unk50 == 0) {
                            func_80614EBC(D_807FBB40, 0x315);
                        }
                    }
                }
                if (G08_A40->unkAC < G08_A40->unk80 + 4.0f) {
                    G08_A40->unk154 = 0x7E;
                    G08_A40->unk155 = 0;
                }
            }
            break;
        case 3:
            func_806DF6D4(0x56);
            func_806CC638(0.0f);
            temp0 = G08_A40->unkB8 / 200.0;
            temp1 = G08_A40->unkC0 / 200.0;
            func_80614D00(D_807FBB40, sqrtf(temp0 * temp0 + temp1 * temp1), 5.0f);
            if ((G08_A40->unkB8 == 0.0f) || (G08_P->unk18 != 0)) {
                G08_P->unk50 = D_80753A78[D_807FD584];
                func_80614D00(D_807FBB40, 0.5f, G08_P->unk50);
                G08_A40->unk155 = 2;
            }
            if (G08_A40->unkAC < G08_A40->unk80 + 4.0f) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x10, 0xFF, 0x7F, 1);
                if (G08_A40->unkC0 > 150.0f) {
                    G08_A40->unk154 = 0x82;
                    G08_A40->unk155 = 0;
                    func_80614EBC(D_807FBB40, 0);
                } else {
                    G08_A40->unk154 = 0x7E;
                    G08_A40->unk155 = 0;
                }
            }
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806CD424(s16, f32, f32);
void func_806CD8EC();
void func_806CC970();

void func_806D19A8(void) {
    G08_A40->unkC0 = func_806CD898(G08_A40->unkC0, 50.0f, 4.0f);
    switch (G08_A40->unk155) {
        case 0:
            G08_P->unk48 = 0x50;
            func_806DF6D4(0x68);
            func_806CD8EC();
            func_806CC970();
            break;
        case 1:
            G08_P->unk68 = 200.0f;
            G08_P->unk2C = 40.0f;
            func_806CD424(G08_A40->unkE6, G08_P->unk68, G08_P->unk68);
            func_806DF6D4(0x68);
            func_806CC970();
            break;
        case 2:
            func_806DF6D4(0x68);
            func_806CD424(G08_A40->unkE6, G08_P->unk4, G08_P->unk68);
            func_806CC970();
            break;
        case 3:
            func_806DF6D4(0x68);
            func_806CC8F0();
            if (G08_A40->unkAC < G08_A40->unk80 + 4.0f) {
                G08_A40->unk154 = 0x7E;
                G08_A40->unk155 = 0;
            } else {
                G08_A40->unk154 = 0x7F;
                G08_A40->unk155 = 0;
            }
            break;
    }
    func_806D11FC();
    func_806319C4(D_807FBB40, 0);
}

void func_806CC920();

void func_806D1B60(void) {
    switch (G08_A40->unk155) {
        case 0:
            func_806DF6D4(0x69);
            func_806CD8EC();
            func_806CC970();
            G08_P->unk12 = G08_A40->unkE8;
            G08_P->unk14 = G08_A40->unkE6;
            break;
        case 1:
            G08_P->unk2C = 40.0f;
            G08_P->unk10 = 0xA;
            G08_P->unk38 = 200.0f;
            func_806DF6D4(0x69);
            func_806CC638(0.0f);
            break;
        case 2:
            func_806DF6D4(0x69);
            func_806CD424(G08_A40->unkE6, G08_P->unk4, G08_P->unk68);
            func_806CC970();
            break;
        case 3:
            func_806DF6D4(0x69);
            func_806CC920();
            if (G08_A40->unkAC < G08_A40->unk80 + 4.0f) {
                G08_A40->unk154 = 0x7E;
                G08_A40->unk155 = 0;
                func_80614EBC(D_807FBB40, 0x317);
            } else {
                G08_A40->unk154 = 0x7F;
                G08_A40->unk155 = 3;
                func_80614EBC(D_807FBB40, 0x318);
                G08_P->unk38 = 300.0f;
                G08_P->unk10 = 0xF;
            }
            break;
    }
    func_806D11FC();
    func_806319C4(D_807FBB40, 0);
}

void func_806D1D3C(void) {
    G08_P->unk4 = 0.0f;
    func_806DF6D4(0x65);
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D1D84(void) {
    G08_P->unk4 = 0.0f;
    G08_P->unk30 = 20.0f;
    func_806EB0C0(0x3C, 0, D_807FC929);
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_805FF8F8();
s32 func_80629148();

void func_806D1DEC(void) {
    G08_P->unk4 = 0.0f;
    G08_P->unk30 = 20.0f;
    func_806CC8B8();
    if ((func_80629148() != 0) || (G08_A40->unk155 == 1) || (G08_P->unk23C--, (G08_P->unk23C == 0))) {
        func_805FF8F8();
    }
    func_806319C4(D_807FBB40, 0);
}

void func_805FF898();

void func_806D1E90(void) {
    G08_P->unk4 = 0.0f;
    G08_P->unk30 = 20.0f;
    func_806EB0C0(0x3C, 0, D_807FC929);
    func_806CC8B8();
    if (G08_A40->unk155 != 0) {
        func_805FF898(D_807FBB40);
        G08_A40->unk155++;
    }
    func_806319C4(D_807FBB40, 0);
}

void hudSpawnTextScreen(s32);
s32 func_806D850C();
void func_80614E78(Actor *, s32);

void func_806D1F28(void) {
    G08_P->unk4 = 0.0f;
    G08_P->unk30 = 20.0f;
    func_806EB0C0(0x3C, 0, D_807FC929);
    if (!(G08_A40->unk6A & 4)) {
        func_806CC8B8();
    } else {
        func_806D850C();
        if (!(G08_A40->unk6C & 4)) {
            func_80614E78(D_807FBB4C, 0x34);
        }
        G08_A40->unkC0 = G08_A40->unkC0 * 0.25;
        func_806CC8B8();
    }
    if ((func_80629148() != 0) || (G08_P->unk23C--, (G08_P->unk23C == 0))) {
        hudSpawnTextScreen(0);
        G08_A40->unk155++;
    }
    func_806319C4(D_807FBB40, 0);
}

#ifdef NON_MATCHING
s32 func_807143E8();
s32 func_80600340();
void func_80688D20(s16, s16, s32, f32);

void func_806D205C(void) {
    s16 sp2C[2];
    u16 sp1C[3] = { 0x1C, 0x86, 0x6B };

    func_806EB0C0(0x3C, 0, D_807FC929);
    G08_P->unk4 = 0.0f;
    G08_P->unk30 = 20.0f;
    if (!(G08_A40->unk6A & 4)) {
        func_806CC8B8();
    } else {
        func_806D850C();
        if (!(G08_A40->unk6C & 4)) {
            func_80614E78(D_807FBB4C, 0x34);
        }
        G08_A40->unkC0 = G08_A40->unkC0 * 0.25;
        func_806CC8F0();
    }
    if ((func_80629148() != 0) || (G08_P->unk23C--, (G08_P->unk23C == 0))) {
        if (func_807143E8() == 0) {
            func_80688D20(sp2C[1], (s16)func_80600340(sp1C, 3, sp2C), 7, 2.0f);
        }
        func_805FF898();
        G08_A40->unk155++;
    }
    func_806319C4(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D205C.s")
#endif

void func_806D21E4(void) {
    func_806DF6D4(0);
    if (!(D_807FBB60 & 0x4000) && !(D_807FBB60 & 0x8000)) {
        func_806CFF9C(D_807FBB40);
    }
    func_806319C4(D_807FBB40, 0);
}

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

void func_806D2B90(void) {
    func_806D2AA0(4);
}

void func_806D2BB0(void) {
    func_806D2AA0(5);
}

typedef struct G10Sub4 {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0x28];
    /* 0x64 */ u16 unk64;
} G10Sub4;

typedef struct G10Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G10Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x5C];
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[2];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0xC];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x14];
    /* 0x09C */ f32 unk9C;
    /* 0x0A0 */ u8 padA0[4];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0xC];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x18];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ u8 padE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[8];
    /* 0x0F8 */ s16 unkF8;
    /* 0x0FA */ u8 padFA[0x4A];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0xF];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G10Actor;

#define G10_A ((G10Actor *)D_807FBB40)

extern u8 D_807463B8;
s32 func_8061CB50();
void func_806C9F74();
void sfxStopSlotSound();

void func_806D2BD0(void) {
    func_806D2954(0xC);
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
    if ((func_8061CB50() != 0) && (G10_A->unk6E != -1)) {
        sfxStopSlotSound(D_807FBB40, 0);
    }
    if (D_807463B8 == 3) {
        func_806C9F74(D_807FBB40);
    }
}

void func_806D2C54(void) {
    func_806D2A14(0x10);
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
    if (D_807463B8 == 3) {
        func_806C9F74(D_807FBB40);
    }
}

typedef struct G10Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ u8 pad8[2];
    /* 0x00A */ s16 unkA;
    /* 0x00C */ s16 unkC;
    /* 0x00E */ s16 unkE;
    /* 0x010 */ u8 pad10[0x1C];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ u8 pad30[0x12];
    /* 0x042 */ u8 unk42;
    /* 0x043 */ u8 pad43[0xD];
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[2];
    /* 0x054 */ f32 unk54;
    /* 0x058 */ u8 pad58[0xAC];
    /* 0x104 */ s32 unk104;
    /* 0x108 */ u8 pad108[0x98];
    /* 0x1A0 */ u16 unk1A0;
    /* 0x1A2 */ u8 unk1A2;
    /* 0x1A3 */ u8 pad1A3[0x4D];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0x4C];
    /* 0x240 */ u8 unk240;
} G10Player;

#define G10_P ((G10Player *)D_807FD580)

extern f32 D_80753A5C[];
void func_806EAB44();

void func_806D2CAC(void) {
    G10_P->unk2C = D_80753AFC[D_807FD584];
    func_806D2954(0xD);
    func_806CC638(D_80753A5C[D_807FD584]);
    if (func_806D850C() != 0) {
        func_806EAB44(D_807FBB40, 1);
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D2D38(void) {
    G10_P->unk2C = D_80753AFC[D_807FD584];
    func_806D2A14(0x11);
    func_806CC638(D_80753A5C[D_807FD584]);
    if (func_806D850C() != 0) {
        func_806EAB44(D_807FBB40, 1);
    }
    func_806319C4(D_807FBB40, 0);
}

extern u32 D_8076A064;
s8 func_806CDD24(void *, f32, f32, s32);
s8 func_806CE174(void *, f32, f32, s32);

void func_806D2DC4(void) {
    s32 sel = 0x13;

    G10_A->unkEE = G10_A->unkE6;
    G10_A->unk64 |= 0x200;
    if (G10_A->unk155 != 0) {
        G10_A->unk155--;
        sel = 0x14;
    }
    if ((D_8076A064 >= 2) && (func_806DF6D4(sel) == 0)) {
        s8 temp = func_806CDD24(D_807FBB40, G10_A->unkB8, G10_P->unk4, 1);

        if (temp != 0xC) {
            G10_A->unk154 = temp ^ 0;
            G10_A->unk155 = 0;
        }
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

#ifdef NON_MATCHING
extern f32 D_807536E4[];
extern s32 D_807FBB68;
void func_80687400();
s32 func_806F8AD4();
void func_806F91B4();
f32 func_806F46B0(s16);
void sfxPlayFromActorWithAltitudeCheck();

typedef struct G10Actor4C {
    /* 0x000 */ u8 pad0[0x12C];
    /* 0x12C */ s16 unk12C;
} G10Actor4C;

void func_806D2E9C(void) {
    f32 v;
    f32 r;
    s32 sel;

    if (D_807FBB68 & 2) {
        f64 t = (G10_A->unk80 - 120.0f) * 0.5;

        v = (t > 0.0) ? t : 0.0;
        if (G10_A->unk7C < 590.0f - v) {
            G10_A->unk7C = 590.0f - v;
        }
        if (987.0f + v < G10_A->unk7C) {
            G10_A->unk7C = 987.0f + v;
        }
        if (G10_A->unk84 < 571.0f - v) {
            G10_A->unk84 = 571.0f - v;
        }
        if (965.0f + v < G10_A->unk84) {
            G10_A->unk84 = 965.0f + v;
        }
        G10_A->unk144 &= 0xFFF7;
    }
    func_806DF6D4(0x1B);
    r = func_806F46B0(((G10Actor4C *)D_807FBB4C)->unk12C);
    sel = 0x7E;
    if (r < G10_A->unk80) {
        G10_A->unkC4 = D_807536E4[D_807FD584];
        if (G10_A->unkC0 > 0.0f) {
            G10_A->unkC0 = G10_A->unkC0 * 0.7;
        }
    }
    if (G10_P->unk1A2 != 0) {
        s32 x = G10_P->unk1A0;

        if (x >= 0x8000) {
            x -= 0x10000;
        }
        x += 0x9E8;
        if (x >= 0x7D1) {
            sel = 0x7D;
        } else if (x < -0x7D0) {
            sel = 0x80;
        } else {
            sel = 0x7F;
        }
    }
    if ((sel != G10_A->unk4->unk64) && (G10_A->unk4->unk64 != 0x81)) {
        func_80614EBC(D_807FBB40, sel);
    }
    if ((G10_P->unk1F0 & 0x40000000) && (G10_P->unk240 == 0)) {
        func_80687400();
        G10_P->unk240 = 0x1E;
    }
    if (G10_P->unk240 != 0) {
        G10_P->unk240--;
    }
    if ((G10_A->unk6A & 1) || (G10_P->unk240 == 1)) {
        if (D_807FBB68 & 2) {
            G10_A->unk144 |= 8;
        }
        func_806CFF9C(D_807FBB40);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 1, 0xFF, 0x7F, 0x1E);
    }
    if (func_8061CB50() == 0) {
        func_806CC948();
        if ((func_806F8AD4(5, D_807FC929) != 0) && !(G10_P->unk1F0 & 0x10000)) {
            func_806F91B4(5, D_807FC929, -1);
        }
    }
    func_806319C4(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D2E9C.s")
#endif

void func_806D3224(void) {
    G10_A->unkEE = G10_A->unkE6;
    if (func_806DF6D4(0x1D) == 0) {
        s8 temp = func_806CE174(D_807FBB40, G10_A->unkB8, G10_P->unk4, 1);

        if (temp != 0x5D) {
            G10_A->unk154 = temp ^ 0;
            G10_A->unk155 = 0;
        }
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D32C0(void) {
    if ((D_8076A0A8 == 0x4E) || (D_8076A0A8 == 0x4F) || (D_8076A0A8 == 0x83)) {
        func_806DF6D4(0x1F);
    } else {
        func_806DF6D4(0x1E);
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

extern f32 D_807531E0[];
s32 func_806CC14C(s16, s16);

void func_806D332C(void) {
    f32 f;

    if (G10_A->unk155 == 0) {
        G10_A->unk155++;
        G10_P->unkC = -1;
        G10_P->unkE = -1;
    }
    if (func_806DF6D4(0x13) == 0) {
        s8 temp = func_806CDD24(D_807FBB40, G10_A->unkB8, G10_P->unk4, 1);

        if (temp != 0xD) {
            G10_A->unk154 = temp ^ 0;
            G10_A->unk155 = 0;
        }
    }
    if ((func_8061CB50() == 0) && ((f = D_807531E0[D_807FD584]) < G10_A->unkB8) && (f < G10_P->unk4) &&
        (G10_P->unkC >= 0) && (func_806CC14C(G10_P->unkC, G10_P->unkA) >= 0x401) &&
        (func_806CC14C(G10_A->unkEE, G10_P->unkA) >= 0x539)) {
        G10_A->unk154 = 0xE;
        G10_A->unk155 = 0;
        func_806CC948();
    } else {
        func_806CC8B8();
    }
    G10_P->unkC = G10_P->unkE;
    G10_P->unkE = G10_P->unkA;
    func_806319C4(D_807FBB40, 0);
}

void func_806D34B4(void) {
    if (func_806DF6D4(0x1C) == 0) {
        s8 temp = func_806CE174(D_807FBB40, G10_A->unkB8, G10_P->unk4, 1);

        if (temp != 0x5E) {
            G10_A->unk154 = temp ^ 0;
            G10_A->unk155 = 0;
        }
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D3530(void) {
    if (((G10_A->unk9C - G10_A->unk80) > 50.0f) && (G10_A->unkB4 > 250.0f)) {
        G10_P->unk42++;
    } else {
        G10_P->unk42 = 0;
    }
    if ((G10_P->unk42++ >= 0xB) || (G10_A->unk80 < -10.0f)) {
        func_806EB0C0(0x2D, 0, D_807FC929);
    }
}

extern s32 D_807FBB64;

void func_806D3608(void) {
    f32 temp = G10_A->unk4->unk38 / 0.15;

    if (!(D_807FBB64 & 0x40000) && (func_8061CB50() == 0)) {
        if (D_8076A0A8 == 0xE) {
            func_806D3530();
            return;
        }
        if ((290.0f * temp) < (G10_A->unk9C - G10_A->unk80)) {
            func_806EB0C0(0x2C, 0, D_807FC929);
        }
    }
}

void func_806CFE7C();
void func_806D3608();

void func_806D36CC(void) {
    switch (G10_A->unk155) {
        case 0:
            func_806DF6D4(0x20);
            func_806D3608();
            break;
        case 1:
            func_806DF6D4(0x31);
            func_806CFE7C();
            break;
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D374C(void) {
    switch (G10_A->unk155) {
        case 0:
            func_806DF6D4(0x20);
            func_806D3608();
            break;
        case 1:
            func_806DF6D4(0x32);
            func_806CFE7C();
            break;
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D37CC(void) {
    if (G10_A->unk155 == 0) {
        func_806DF6D4(0x20);
        func_806CC8B8();
        if (G10_A->unk6A & 1) {
            if (G10_A->unkE0 != 0.0f) {
                func_806CFF9C(D_807FBB40);
            } else {
                func_806CFE7C(D_807FBB40);
                func_806EB0C0(0x35, 0, D_807FC929);
            }
        }
    } else {
        func_806DF6D4(0x20);
        G10_P->unk4 = 0.0f;
        G10_A->unkB8 = 0.0f;
        func_806CC8B8();
    }
    func_806319C4(D_807FBB40, 0);
}

void func_80685210(f32, s32, s32);
void func_806224CC(s32, void *);

void func_806D38AC(s32 arg0) {
    func_80685210(0.5f, 0x64, 5);
    G10_A->unkF8 = 0x12C;
    if ((G10_A->unk80 - G10_A->unkA4) > 5.0f) {
        if (G10_A->unkC4 == -260.0f) {
            func_806CFE7C(D_807FBB40);
        } else if (G10_A->unkC4 != -30.0f) {
            G10_A->unk6A |= 0x1000;
        } else {
            f32 g = G10_A->unkC0;

            if (g > 0.0f) {
                G10_A->unkC0 = 0.0f;
            } else {
                G10_A->unkC0 = g;
            }
        }
        G10_A->unk154 = 0x14;
        G10_A->unk155 = 0;
        G10_P->unk54 = G10_A->unkC0;
        G10_P->unk50 = 0;
        func_80614E78(D_807FBB40, 0x67);
    }
    func_806DF6D4(arg0);
    func_806CC8B8();
    if (!(G10_A->unk6A & 0x200)) {
        func_806CFF9C(D_807FBB40);
        sfxStopSlotSound(D_807FBB40, 0);
        func_806224CC(G10_P->unk104, D_807FBB40);
    }
    func_806319C4(D_807FBB40, 0);
}

void func_8061C464(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);

void func_806D3A38(void) {
    if (G10_A->unk155 == 0) {
        func_8061C464(G10_P->unk104, D_807FBB40, 4, 0x800, 0x32, 0, 5, 0x32, 0x14, 0, 0.2f);
        G10_A->unk155++;
    }
    func_806D38AC(0x3D);
}

void func_806D3AC8(void) {
    func_806D38AC(0x3D);
}

typedef struct G11Actor {
    /* 0x000 */ u8 pad0[0x45];
    /* 0x045 */ u8 unk45;
    /* 0x046 */ u8 pad46[0x12];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xE];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x4C];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x1C];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ u8 padE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[2];
    /* 0x0EA */ s16 unkEA;
    /* 0x0EC */ u8 padEC[2];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ struct G11Actor *unk174;
} G11Actor;

typedef struct G11Player {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[0x20];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u8 pad42[0xA];
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 pad4E[2];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[2];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x2C];
    /* 0x88 */ G11Actor *unk88;
} G11Player;

typedef struct G11Pad {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ u8 pad4[0x30];
} G11Pad;

#define G11_P ((G11Player *)D_807FD580)
#define G11_A ((G11Actor *)D_807FBB40)

extern G11Pad D_807FD618[];
void func_806D38AC();

void func_806D3AE8(void) {
    func_806D38AC(0x3D);
}

void func_806D3B08(void) {
    func_806D38AC(0x3D);
}

void func_806D3B28(void) {
    func_806D38AC(0x3D);
}

void func_806D3B48(void) {
    G11_P->unk4 = 0.0f;
    func_806CC8B8();
    G11_A->unk155++;
    if (G11_A->unk155 == 0x32) {
        G11Actor *e = G11_P->unk88->unk174;
        e->unk45 = 1;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D3530();

void func_806D3BC8(void) {
    func_806DF6D4(0x3E);
    func_806CC8B8();
    switch (G11_A->unk155) {
        case 0:
            G11_A->unkC0 = G11_P->unk54;
            G11_A->unk155++;
            break;
        case 1:
            if (D_8076A0A8 == 0xE) {
                func_806D3530();
            }
            break;
        case 2:
            if (G11_A->unk6A & 1) {
                G11_A->unk6A &= ~0x1000;
                func_806CFE7C();
                G11_A->unk154 = 0xF;
                G11_A->unk155 = 0;
                func_80614E78(D_807FBB40, 0x5E);
            } else {
                func_806D3530();
            }
            break;
    }
    func_806319C4(D_807FBB40, 0);
}


void func_806D3CD4(void) {
    func_80685210(0.5f, 0x64, 5);
    func_806DF6D4(0x3C);
    func_806CC8B8();
    if (G11_A->unkB8 == 0.0f && G11_A->unkE0 == 0.0f) {
        func_806CFF9C(D_807FBB40);
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D3D5C(void) {
    func_80685210(0.5f, 0x64, 5);
    func_806DF6D4(0x3B);
    func_806CC8B8();
    if (G11_A->unkB8 == 0.0f && G11_A->unkE0 == 0.0f) {
        func_806CFF9C(D_807FBB40);
    }
    func_806319C4(D_807FBB40, 0);
}

extern f32 D_8075327C[];
extern s16 D_80753298[];
void func_806DF5A0(s16 *, s16, s16, s16);

void func_806D3DE4(void) {
    switch (G11_A->unk155) {
        case 0:
            func_806DF6D4(0x41);
            func_80614E78(D_807FBB40, 5);
            G11_P->unk30 = D_8075327C[D_807FD584];
            func_806CD8EC();
            func_806CC948();
            G11_A->unk155++;
            break;
        case 1:
            func_806DF6D4(0x41);
            func_806CD8EC();
            func_806CC948();
            break;
        case 2:
            func_806DF6D4(0x41);
            func_806CD8EC();
            func_806DF5A0(&G11_A->unkE6, G11_P->unkA, D_80753298[D_807FD584], 0xC00);
            func_806CC948();
            break;
        case 3:
            func_806DF6D4(0x41);
            func_806DF5A0(&G11_A->unkE6, G11_P->unkA, D_80753298[D_807FD584], 0xC00);
            if (G11_P->unk4 == 0.0f) {
                func_806CFF9C(D_807FBB40);
            }
            func_806CC8B8();
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D3FA0(void) {
    if (D_807FD618[D_807FC929].unk0 != 0.0f) {
        G11_A->unkEA = G11_P->unkA;
    } else {
        G11_A->unkEA = G11_A->unkE6;
    }
}

extern u8 D_8074E77C[];
extern s32 D_80767CC0;
extern f32 D_80753604[];

void func_806D4010(void) {
    switch (G11_A->unk155) {
        case 0:
            func_806DF6D4(0x2C);
            func_806CC8B8();
            break;
        case 1:
            G11_A->unkC0 = G11_P->unk54;
            func_806CFECC();
            func_806D3FA0();
            G11_A->unk155++;
            func_806DF6D4(0x21);
            func_806CFD68();
            func_806CC8B8();
            break;
        case 2:
            func_806CC8B8();
            if (G11_A->unk58 == 5) {
                func_806DF6D4(0x22);
            } else {
                func_806DF6D4(0x21);
            }
            func_806CFD68();
            break;
        case 3:
            if (*(u16 *)((u8 *)&D_807FD63C + D_807FC929 * 0x34) & 0x8000) {
                G11_P->unk58 = D_80767CC0;
            }
            if ((u32)(D_80767CC0 - G11_P->unk58) < 0xA && D_8074E77C[D_807FC929] == 1 && G11_A->unkE0 == 0.0f) {
                G11_A->unk154 = 0x1A;
                G11_A->unk155 = 0;
                G11_P->unk54 = D_80753604[D_807FD584];
                G11_P->unk50 = 0;
                func_80614E78(D_807FBB40, 0x13);
            }
            func_806DF6D4(0x30);
            func_806CC8B8();
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D423C(void) {
    G11_A->unkC0 = G11_P->unk54;
    func_806DF6D4(5);
    func_806CC8F0();
    func_806319C4(D_807FBB40, 0);
}

extern f32 D_80753234[];

void func_806D428C(void) {
    switch (G11_A->unk155) {
        case 0:
            func_806DF6D4(0x2C);
            if (G11_P->unk3C != 0) {
                func_806CC948();
                G11_P->unk3C--;
            } else {
                func_806CC8B8();
            }
            break;
        case 1:
            if (G11_P->unk3C != 0) {
                G11_P->unk2C = 0.0f;
                func_806CC8B8();
                G11_P->unk3C--;
                G11_A->unkEA = G11_A->unkE6;
            } else {
                func_806D3FA0();
                func_806CC8B8();
            }
            G11_A->unkC0 = G11_P->unk54;
            func_806CFECC();
            G11_A->unk155++;
            func_806DF6D4(0x21);
            func_806CFD68();
            break;
        case 2:
            if (G11_P->unk3C != 0) {
                G11_P->unk2C = 0.0f;
                func_806CC8B8();
                G11_P->unk3C--;
            } else {
                G11_P->unk2C = D_80753234[D_807FD584];
                func_806CC8B8();
            }
            if (G11_A->unk58 == 5) {
                func_806DF6D4(0x22);
            } else {
                func_806DF6D4(0x21);
            }
            func_806D3608();
            func_806CFD68();
            break;
        case 3:
            G11_P->unk3C = 0;
            if (*(u16 *)((u8 *)&D_807FD63C + D_807FC929 * 0x34) & 0x8000) {
                G11_P->unk58 = D_80767CC0;
            }
            if ((u32)(D_80767CC0 - G11_P->unk58) < 0xA && D_8074E77C[D_807FC929] == 1 && G11_A->unkE0 == 0.0f) {
                G11_A->unk154 = 0x1A;
                G11_A->unk155 = 0;
                G11_P->unk54 = D_80753604[D_807FD584];
                G11_P->unk50 = 0;
                func_80614E78(D_807FBB40, 0x13);
            }
            func_806DF6D4(0x30);
            func_806CC8B8();
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

u8 func_806CE4E4(Actor *, f32, f32, s32);

void func_806D45A4(void) {
    switch (G11_A->unk155) {
        case 0:
            func_806DF6D4(0x2C);
            func_806CC8B8();
            break;
        case 1:
            G11_A->unkC0 = G11_P->unk54;
            func_806CFECC();
            func_806D3FA0();
            G11_A->unk155++;
            func_806DF6D4(0x21);
            func_806CFD68();
            func_806CC8B8();
            break;
        case 2:
            func_806CC8B8();
            if (G11_A->unk58 == 5) {
                func_806DF6D4(0x22);
            } else {
                func_806DF6D4(0x21);
            }
            func_806D3608();
            func_806CFD68();
            break;
        case 3:
            G11_P->unk4C = -1;
            G11_A->unk154 = func_806CE4E4(D_807FBB40, G11_A->unkB8, G11_P->unk4, 1);
            G11_A->unk155 = 0;
            if (G11_A->unk154 == 0x3F) {
                G11_A->unk155 = 1;
            }
            func_806DF6D4(0x46);
            func_806CC8B8();
            break;
    }
    func_806319C4(D_807FBB40, 0);
}


#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D4758.s")

void func_806D491C(void) {
    switch (G11_A->unk155) {
        case 0:
            func_806DF6D4(0x26);
            func_806CC8B8();
            break;
        case 1:
            G11_A->unkC0 = G11_P->unk54;
            func_806CFECC();
            func_806D3FA0();
            G11_A->unk155++;
            func_806DF6D4(0x25);
            func_806CFD68();
            func_806CC8B8();
            break;
        case 2:
            func_806CC8B8();
            func_806DF6D4(0x25);
            func_806CFD68();
            func_806D3608();
            break;
        case 3:
            if (*(u16 *)((u8 *)&D_807FD63C + D_807FC929 * 0x34) & 0x8000) {
                G11_P->unk58 = D_80767CC0;
            }
            func_806DF6D4(0x34);
            func_806CC8B8();
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

typedef struct G12Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ u8 pad8[0x28];
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[4];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[2];
    /* 0x03E */ s16 unk3E;
    /* 0x040 */ s16 unk40;
    /* 0x042 */ u8 pad42[6];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0xA];
    /* 0x054 */ f32 unk54;
    /* 0x058 */ u8 pad58[4];
    /* 0x05C */ u32 unk5C;
    /* 0x060 */ u8 pad60[8];
    /* 0x068 */ f32 unk68;
    /* 0x06C */ u8 pad6C[0x98];
    /* 0x104 */ s32 unk104;
    /* 0x108 */ u8 pad108[0xEC];
    /* 0x1F4 */ s32 unk1F4;
} G12Player;

#define G12_P ((G12Player *)D_807FD580)

void func_806F142C();

#ifdef NON_MATCHING
void func_806D4A70(void) {
    switch (G08_A40->unk155) {
    case 0:
        if (G12_P->unk3E != 0) {
            func_806CC14C(G08_A40->unkEE, G12_P->unk40);
            func_806CD424(G12_P->unk40, 50.0f, G12_P->unk38);
            G12_P->unk3E--;
        }
        func_806CC8B8();
        if (G08_A40->unkC0 <= -15.0f) {
            G08_A40->unkC0 = -15.0f;
            G08_A40->unk155++;
        }
        func_806DF6D4(0x24);
        if (G08_A40->unk6A & 1) {
            func_806F142C(D_807FBB40);
        }
        break;
    case 1:
        func_806DF6D4(0x24);
        if (G12_P->unk3E != 0) {
            func_806CC14C(G08_A40->unkEE, G12_P->unk40);
            func_806CD424(G12_P->unk40, 30.0f, G12_P->unk38);
            G12_P->unk3E--;
        }
        func_806CC8F0();
        if (G08_A40->unk6A & 1) {
            func_806F142C(D_807FBB40);
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 1, 0xFF, 0x7F, 0x1E);
        }
        break;
    case 2:
        G08_A40->unkC4 = -4.0f;
        func_806DF6D4(0x24);
        func_806CC8B8();
        if (G08_A40->unk6A & 1) {
            func_806F142C(D_807FBB40);
        }
        break;
    }
    func_806319C4(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D4A70.s")
#endif

extern f32 D_80753620[];
extern f32 D_8075363C[];
void func_806D3FA0(void);
void func_806CFDEC();

void func_806D4C7C(void) {
    switch (G08_A40->unk155) {
    case 0:
        func_80614D00(D_807FBB40, 1.0f, 0.0f);
        func_806DF6D4(0x2C);
        func_806CC8B8();
        break;
    case 1:
        G08_A40->unkC0 = G12_P->unk54;
        G08_A40->unkC4 = D_8075363C[D_807FD584];
        G08_A40->unk155++;
        func_806D3FA0();
        func_806DF6D4(0x2B);
        G12_P->unk38 = D_80753620[D_807FD584];
        func_806CC8B8();
        break;
    case 2:
        func_806CC8B8();
        func_806DF6D4(0x2B);
        func_806CFDEC();
        func_806D3608();
        break;
    case 3:
        func_806DF6D4(0x2B);
        func_806CFE7C();
        func_806CC8B8();
        break;
    case 4:
        func_806DF6D4(0x30);
        func_806CFE7C();
        func_806CC8B8();
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

extern f32 D_80753674[];
extern f32 D_80753690[];
extern f32 D_807536C8[];
extern f32 D_807536E4[];
void func_806CF878();
void func_806CFDA8();

void func_806D4DE4(void) {
    func_806CF878();
    switch (G08_A40->unk155) {
    case 0:
        func_80614D00(D_807FBB40, 1.0f, 0.0f);
        func_806DF6D4(0x2C);
        func_806CC8B8();
        break;
    case 1:
        G08_A40->unkC0 = D_80753674[D_807FD584];
        G08_A40->unkC4 = D_80753690[D_807FD584];
        func_806D3FA0();
        G08_A40->unk155++;
        func_806DF6D4(0x2B);
        func_806CC8B8();
        break;
    case 2:
        func_806CC8B8();
        func_806DF6D4(0x2D);
        func_806D3608();
        break;
    case 3:
        func_806DF6D4(0x36);
        func_806CC8B8();
        break;
    case 4:
        func_806DF6D4(0x36);
        func_806CC8B8();
        break;
    case 5:
        G08_A40->unkC0 = G12_P->unk54;
        G08_A40->unkC4 = D_807536E4[D_807FD584];
        G08_A40->unk155++;
        func_806DF6D4(0x2B);
        G12_P->unk38 = D_807536C8[D_807FD584];
        func_806CC8B8();
        break;
    case 6:
        func_806CC8B8();
        func_806DF6D4(0x2C);
        func_806CFDA8();
        func_806D3608();
        break;
    case 7:
        func_806DF6D4(0x30);
        func_806CFE7C();
        func_806CC8B8();
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_80685708();
void func_8061F0B0(s32, s32, s32);

void func_806D5008(void) {
    switch (G08_A40->unk155) {
    case 0:
        G08_A40->unkB8 = 0.0f;
        G08_A40->unkC0 = 0.0f;
        func_806DF6D4(0x2E);
        func_806CC970();
        break;
    case 1:
        func_806DF6D4(0x2E);
        G08_A40->unkC4 = -30.0f;
        G08_A40->unkB8 = 0.0f;
        G08_A40->unkC0 = -100.0f;
        G08_A40->unk155++;
        func_806CC948();
        break;
    case 2:
        func_806DF6D4(0x2E);
        func_806D3608();
        func_806CC948();
        break;
    case 3:
        func_806DF6D4(0x2E);
        if (!(G08_A40->unk6A & 4)) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x96, 0xFF, 0x7F, 0x19);
            func_80685708(D_807FBB40, ((u8 *)D_807FD568)[1]);
            func_8061F0B0(G10_P->unk104, 0x14, (u16)(((u8 *)D_807FD568)[1] * 5));
        }
        func_80614D00(D_807FBB40, 1.0f, 0.0f);
        G08_A40->unk155++;
        func_806CC948();
        break;
    case 4:
        func_806DF6D4(0x2E);
        func_806CC948();
        break;
    case 5:
        func_806DF6D4(0x2F);
        G08_A40->unk155++;
        func_806CC8B8();
        break;
    case 6:
        func_806DF6D4(0x2F);
        func_806CC8B8();
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D5218(void) {
    switch (G08_A40->unk155) {
    case 0:
        G08_P->unk30 = G08_P->unk30 / 1.8;
        G08_A40->unk155++;
    case 1:
        func_806DF6D4(5);
        func_806CC8B8();
        func_806DF494(&G08_A40->unkEE, G08_A40->unkE6, (s16)(G08_P->unk48 * 1.25));
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

extern f32 D_80750FC0;
extern s32 D_80750FC4;
extern s32 D_80750FC8;
extern s32 D_80750FCC;
extern s32 D_80750FD0;
extern u8 D_80750FD4;
extern f32 D_80750FD8;
extern s32 D_8074E880[];
extern f32 D_8075352C[];
s32 func_80611A44();
void func_80714950(s32);
void func_8071498C(void *);
void func_807149B8(s32);
void func_80714CC0(s32, f32, f32, f32, f32);
void func_80717D4C();

void func_806D5300(void) {
    f32 pad;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 scale;
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    if (G08_A40->unk155 < 2 || D_80750FD8 < G08_A40->unkB8) {
        scale = D_807FBB40->unk4->unk38 / 0.15;
        actorGetNodePos(D_807FBB40, 7, &sp90, &sp8C, &sp88);
        for (i = 0; i < D_80750FD4; i++) {
            x = (func_80611A44() >> 15) % 10000 % D_80750FC8 - D_80750FC8 / 2;
            y = (func_80611A44() >> 15) % 10000 % D_80750FCC - D_80750FCC / 2;
            z = (func_80611A44() >> 15) % 10000 % D_80750FD0 - D_80750FD0 / 2;
            func_80714950(D_80750FC4);
            func_8071498C(&func_80717D4C);
            func_807149B8(1);
            func_80714CC0(D_8074E880[func_80611A44() % 10000 % 3], D_80750FC0 * scale, x * scale + sp90, y * scale + sp8C, z * scale + sp88);
        }
    }
    switch (G08_A40->unk155) {
    case 0:
        func_806DF6D4(5);
        G12_P->unk4 = 0.0f;
        break;
    case 1:
        func_806DF6D4(5);
        G08_A40->unkEE = G08_A40->unkE6;
        if (!(G12_P->unk1F4 & 8)) {
            G08_A40->unkB8 = 140.0f;
        }
        G12_P->unk30 = 6.0f;
        G08_A40->unk155++;
        break;
    case 2:
        if (D_807FBB40->unkFC != 0) {
            f32 t = D_8075352C[D_807FD584];

            if (t < G08_A40->unkB8 && !(G12_P->unk1F4 & 8)) {
                G08_A40->unkB8 = t;
                G12_P->unk68 = D_8075352C[D_807FD584];
            }
        }
        func_806DF6D4(5);
        break;
    case 3:
        G08_A40->unkB8 = 0.0f;
        func_806DF6D4(5);
        func_806F142C(D_807FBB40);
        break;
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D57F0(void) {
    func_806DF6D4(1);
    G08_P->unk4 = 0.0f;
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}


void func_806D5834(void) {
    switch (G08_A40->unk155) {
    case 0:
        G12_P->unk30 = G12_P->unk30 / 1.8;
        G08_A40->unk155++;
        G12_P->unk5C = D_80767CC0 - 0x64;
        G12_P->unk48 = 0x50;
    case 1:
        func_806DF6D4(9);
        G12_P->unk30 = 10.0f;
        func_806CD8EC();
        func_806DF494(&G08_A40->unkEE, G08_A40->unkE6, (s16)(G12_P->unk48 * 1.25));
        break;
    case 2:
        if ((u32)(D_80767CC0 - G12_P->unk5C) < 0x32) {
            if (D_8074E77C[D_807FC929] == 2) {
                do {
                    G08_A40->unk154 = 0x27;
                    G08_A40->unk155 = 0;
                    func_80614E78(D_807FBB40, 0x40);
                } while (0);
            } else {
                G08_A40->unk154 = 0x28;
                G08_A40->unk155 = 0;
                func_80614E78(D_807FBB40, 0x41);
            }
        }
        break;
    }
    func_806CC948();
    func_806319C4(D_807FBB40, 0);
}

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
