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
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
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
s32 sfxPlayFromActorWithAltitudeCheck();

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

typedef struct G13Player {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[0x20];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0xC];
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A[0x12];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 pad60[8];
    /* 0x68 */ f32 unk68;
} G13Player;

typedef struct G13Actor {
    /* 0x000 */ u8 pad0[0xB8];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x1C];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ u8 padE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0xC];
    /* 0x0FC */ u8 unkFC;
    /* 0x0FD */ u8 padFD[0x57];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G13Actor;

#define G13_P ((G13Player *)D_807FD580)
#define G13_A ((G13Actor *)D_807FBB40)

void func_806D59E4(void) {
    switch (G13_A->unk155) {
        case 0:
            G13_P->unk30 = G13_P->unk30 / 1.8;
            G13_A->unk155++;
            G13_P->unk5C = D_80767CC0 - 0x64;
        case 1:
            func_806DF6D4(9);
            G13_P->unk30 = 10.0f;
            func_806CD8EC();
            func_806DF494(&G13_A->unkEE, G13_A->unkE6, (s16)(s32)(G13_P->unk48 * 1.25));
            break;
        case 2:
            if ((u32)(D_80767CC0 - G13_P->unk5C) < 0x32) {
                G13_A->unk154 = 0x28;
                G13_A->unk155 = 0;
                func_80614E78(D_807FBB40, 0x41);
            }
            break;
    }
    func_806CC948();
    func_806319C4(D_807FBB40, 0);
}

void func_806D5B44(void) {
    switch (G13_A->unk155) {
        case 0:
            G13_P->unk30 = G13_P->unk30 / 1.8;
            if (D_8074E77C[D_807FC929] == 3) {
                G13_A->unkB8 = 50.0f;
            }
            G13_A->unk155++;
        case 1:
            func_806DF6D4(0xA);
            func_806DF494(&G13_A->unkEE, G13_A->unkE6, (s16)(s32)(G13_P->unk48 * 1.25));
            break;
        case 2:
            func_806DF6D4(0xA);
            G13_P->unk30 = 50.0f;
            func_806CD8EC();
            func_806DF494(&G13_A->unkEE, G13_A->unkE6, (s16)(s32)(G13_P->unk48 * 1.25));
            break;
    }
    func_806CC948();
    func_806319C4(D_807FBB40, 0);
}

extern f32 D_807531FC[];

void func_806D5CCC(void) {
    func_806DF494(&G13_A->unkE6, G13_A->unkEE, G13_P->unk48);
    func_806D3608();
    switch (D_8074E77C[D_807FC929]) {
        case 1:
            switch (G13_A->unk155) {
                case 0:
                    func_806CFECC();
                    func_806DF6D4(0x17);
                    func_806CC948();
                    break;
                case 1:
                    func_806CFECC();
                    func_806DF6D4(0x16);
                    func_806CC948();
                    break;
            }
            break;
        case 0:
            switch (G13_A->unk155) {
                case 0:
                    G13_P->unk30 = 7.0f;
                    G13_P->unk2C = 8.0f;
                    G13_P->unk48 = 0x12C;
                    func_806DF6D4(0x15);
                    G13_P->unk4 = 0.0f;
                    func_806CC8B8();
                    break;
                case 1:
                    G13_A->unkB8 = D_807531FC[D_807FD584];
                    G13_P->unk2C = 20.0f;
                    G13_P->unk38 = D_807531FC[D_807FD584];
                    func_806DF6D4(0x15);
                    func_806CC948();
                    break;
                case 2:
                    G13_A->unkC0 = 150.0f;
                    G13_P->unk2C = 20.0f;
                    G13_P->unk38 = 200.0f;
                    func_806DF6D4(0x15);
                    G13_P->unk4 = 200.0f;
                    func_806CC8B8();
                    G13_A->unk155++;
                    break;
                case 3:
                    G13_A->unkB8 = 200.0f;
                    G13_P->unk38 = 200.0f;
                    func_806DF6D4(0x15);
                    func_806CC948();
                    break;
            }
            break;
        default:
        case 3:
            switch (G13_A->unk155) {
                case 0:
                    G13_P->unk28 = 0;
                    G13_P->unk30 = 0.2f;
                    G13_P->unk2C = 8.0f;
                    G13_P->unk48 = 0x12C;
                    func_806DF6D4(0x15);
                    func_806CC948();
                    break;
                case 1:
                    G13_P->unk30 = 20.0f;
                    G13_P->unk2C = 20.0f;
                    G13_P->unk38 = D_807531FC[D_807FD584];
                    func_806DF6D4(0x15);
                    func_806CC948();
                    break;
                case 2:
                    G13_P->unk28 = 1;
                    if ((u32)(D_80767CC0 - G13_P->unk5C) < 0x14) {
                        G13_A->unk154 = 0x26;
                        G13_A->unk155 = 0;
                        func_80614E78(D_807FBB40, 0x3F);
                    }
                    func_806DF6D4(0x15);
                    func_806CC8B8();
                    break;
            }
            break;
        case 6:
            switch (G13_A->unk155) {
                case 0:
                    G13_P->unk28 = 0;
                    G13_P->unk2C = 20.0f;
                    G13_P->unk48 = 0x12C;
                    func_806DF6D4(0x15);
                    G13_P->unk30 = 10.0f;
                    func_806CD8EC();
                    func_806CC948();
                    break;
                case 1:
                    G13_P->unk2C = 30.0f;
                    G13_P->unk68 = D_807531FC[D_807FD584];
                    func_806CD424(G13_A->unkE6, G13_P->unk68, G13_P->unk68);
                    func_806DF6D4(0x15);
                    func_806CC948();
                    break;
                case 2:
                    G13_P->unk28 = 1;
                    func_806DF6D4(0x15);
                    func_806CC8B8();
                    break;
            }
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

extern s16 D_80753558[];
extern s16 D_80753568[];
void func_806CBE90();
void func_806CC8A8();

void func_806D61B8(void) {
    func_806DF494(&G13_A->unkE6, G13_A->unkEE, G13_P->unk48);
    func_806D3608();
    switch (G13_A->unk155) {
        case 0:
            G13_P->unk30 = 0.2f;
            G13_P->unk2C = 10.0f;
            G13_P->unk48 = 0x32;
            G13_P->unk68 = D_80753568[D_807FD584];
            func_806DF6D4(0x18);
            if (G13_A->unkE0 != 0.0f) {
                G13_P->unk30 = 20.0f;
                func_806CD8EC();
            } else {
                func_806CD424(G13_A->unkE6, G13_P->unk68, G13_P->unk68);
            }
            func_806CBE90();
            func_806CC948();
            func_806DF494(&G13_A->unkEE, G13_A->unkE6, G13_P->unk48);
            if (G13_A->unkFC != 0) {
                G13_A->unkB8 = G13_A->unkB8 * 0.9;
            }
            break;
        case 1:
            func_806DF6D4(0x18);
            func_806CC948();
            G13_A->unkC0 = 150.0f;
            G13_A->unk155++;
            break;
        case 2:
            func_806DF6D4(0x18);
            func_806CD424(G13_A->unkE6, G13_P->unk68, G13_P->unk68);
            func_806CC948();
            func_806DF494(&G13_A->unkEE, G13_A->unkE6, G13_P->unk48);
            break;
        case 3:
            G13_P->unk30 = D_80753558[D_807FD584];
            if (D_8074E77C[D_807FC929] == 0) {
                func_806DF6D4(0x19);
            } else {
                func_806DF6D4(0x19);
            }
            func_806CC8B8();
            break;
        case 4:
            G13_P->unk30 = D_80753558[D_807FD584];
            if (D_8074E77C[D_807FC929] == 0) {
                func_806DF6D4(0x19);
            } else {
                func_806DF6D4(0x19);
            }
            func_806CC8B8();
            if (G13_P->unk4 != 0.0f) {
                func_806CFF9C(D_807FBB40);
            }
            break;
        case 5:
            func_806DF6D4(5);
            G13_A->unkEE = (G13_A->unkE6 + 0x800) % 4096;
            func_806CC8A8();
            func_806CBE90();
            func_806CC948();
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

extern s16 D_80753548[];
s32 func_806725A0();

void func_806D6558(void) {
    func_806D3608();
    switch (G13_A->unk155) {
        case 0:
            G13_P->unk30 = 20.0f;
            func_806CD8EC();
            func_806CC970();
            break;
        case 1:
            func_806DF6D4(0x1A);
            if (G13_P->unk68 < G13_A->unkB8) {
                G13_P->unk68 = G13_A->unkB8;
            }
            if (G13_A->unkFC != 0) {
                if (D_8075352C[D_807FD584] < G13_A->unkB8) {
                    G13_A->unkB8 = D_8075352C[D_807FD584];
                    G13_P->unk68 = D_8075352C[D_807FD584];
                }
            }
            if (G13_A->unkFC != 0 && func_806725A0(D_807FBB40, G13_A->unkE6) == 0) {
                func_80614E78(D_807FBB40, 0x49);
                G13_A->unkEE = (G13_A->unkE6 + 0x800) % 4096;
                G13_A->unk155 = 3;
                G13_A->unkB8 = D_8075352C[D_807FD584];
                G13_P->unk68 = D_8075352C[D_807FD584];
                break;
            }
            func_806CBE90();
            if (G13_A->unkE0 != 0.0f) {
                G13_P->unk30 = 20.0f;
                func_806CD8EC();
            } else {
                func_806CD424(G13_A->unkE6, G13_P->unk68, G13_P->unk38);
            }
            func_806CC948();
            break;
        case 2:
            func_806DF6D4(0x1A);
            if (G13_A->unkFC != 0 && func_806725A0(D_807FBB40, G13_A->unkE6) == 0) {
                func_80614E78(D_807FBB40, 0x49);
                G13_A->unkEE = (G13_A->unkE6 + 0x800) % 4096;
                G13_A->unk155++;
                G13_A->unkB8 = D_8075352C[D_807FD584];
                G13_P->unk68 = D_8075352C[D_807FD584];
                break;
            }
            func_806DF494(&G13_A->unkE6, G13_A->unkEE, G13_P->unk48);
            func_806CBE90();
            func_806CD8EC();
            func_806CC948();
            G13_P->unk30 = D_80753548[D_807FD584];
            break;
        case 3:
            func_806DF6D4(5);
            G13_A->unkEE = (G13_A->unkE6 + 0x800) % 4096;
            func_806CC8A8();
            func_806CBE90();
            func_806CC948();
            break;
        case 4:
            func_806DF6D4(5);
            G13_A->unkEE = (G13_A->unkE6 + 0x800) % 4096;
            G13_P->unk30 = 5.0f;
            func_806CD8EC();
            func_806CC8A8();
            func_806CBE90();
            func_806CC948();
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

typedef struct G14Anim {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ f32 unk4;
} G14Anim;

typedef struct G14Actor {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u32 unk64;
    /* 0x68 */ u8 pad68[0x18];
    /* 0x80 */ f32 unk80;
    /* 0x84 */ u8 pad84[0x28];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[8];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x24];
    /* 0xE0 */ f32 unkE0;
    /* 0xE4 */ u8 padE4[2];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[4];
    /* 0xF4 */ s16 unkF4;
    /* 0xF6 */ s16 unkF6;
    /* 0xF8 */ u8 padF8[4];
    /* 0xFC */ u8 unkFC;
    /* 0xFD */ u8 padFD[0x2B];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ u8 pad12A[0x1A];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0x10];
    /* 0x155 */ u8 unk155;
} G14Actor;

typedef struct G14Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ u8 pad8[2];
    /* 0x00A */ s16 unkA;
    /* 0x00C */ u8 padC[0x1C];
    /* 0x028 */ s16 unk28;
    /* 0x02A */ u8 pad2A[6];
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[4];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[0xC];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0x1E];
    /* 0x068 */ f32 unk68;
    /* 0x06C */ u8 pad6C[0x70];
    /* 0x0DC */ G14Actor *unkDC;
    /* 0x0E0 */ u8 padE0[0x3C];
    /* 0x11C */ u8 unk11C;
    /* 0x11D */ u8 pad11D[0x86];
    /* 0x1A3 */ u8 unk1A3;
    /* 0x1A4 */ u8 pad1A4[0x7A];
    /* 0x21E */ u16 unk21E;
} G14Player;

#define G14_A ((G14Actor *)D_807FBB40)
#define G14_P ((G14Player *)D_807FD580)

extern f32 D_8075305C[];
extern f32 D_807530F0[];
extern f32 D_80753144[];
extern s16 D_807538C8[];
s16 func_806CC190(s16, s16, f32);
void effectSpawnJointBeam();
void effectSpawnRandomBoneDebris();
void func_80712830(Actor *, u8);
s32 func_806119A0(void);
void func_80714998(s32);

s32 func_806D69A4(void) {
    if (G14_A->unkFC != 0) {
        if (func_806CC14C(G14_A->unkE6, ((((G14_A->unkF6 - G14_A->unkF4) & 0xFFF) / 2) + G14_A->unkF4 + 0x800) & 0xFFF) < 0x2BC) {
            if (G14_A->unkB8 > 150.0f) {
                func_80614E78(D_807FBB40, 0x49);
                G14_A->unkEE = (G14_A->unkE6 + 0x800) % 4096;
                G14_A->unk155 = 2;
                G14_A->unkB8 = D_8075352C[D_807FD584];
                G14_P->unk68 = D_8075352C[D_807FD584];
                if (!G14_A->unkEE) {
                }
                return 1;
            }
            func_806CFF9C(D_807FBB40);
            return 1;
        }
        func_806DF494(&G14_A->unkE6, G14_A->unkEE, G14_P->unk48);
    }
    return 0;
}

void func_80714C08(void *, f32, void *, s32, s32);
void func_8071B2EC();
extern u8 D_8071FF18;

void func_806D6B00(void) {
    func_806D3608();
    switch (G14_A->unk155) {
    case 0:
        G14_P->unk28 = 0;
        func_806DF6D4(0x1A);
        if (G14_P->unk68 < G14_A->unkB8) {
            G14_P->unk68 = G14_A->unkB8;
        }
        if (func_806D69A4() != 0) {
            break;
        }
        func_806CBE90();
        if (G14_A->unkE0 != 0.0f) {
            G14_P->unk30 = 20.0f;
            func_806CD8EC();
        } else {
            func_806CD424(G14_A->unkE6, G14_P->unk68, G14_P->unk38);
        }
        func_806CC948();
        break;
    case 1:
        func_806DF6D4(0x1A);
        if (func_806D69A4() != 0) {
            break;
        }
        func_806DF494(&G14_A->unkE6, G14_A->unkEE, G14_P->unk48);
        func_806CBE90();
        func_806CD8EC();
        func_806CC948();
        G14_P->unk30 = D_80753548[D_807FD584];
        if (G14_A->unkB8 > 20.0f) {
            if (func_806119A0() % 3U == 0) {
                func_8071498C(&func_8071B2EC);
                func_80714998(2);
                func_807149B8(1);
                func_80714C08(&D_8071FF18, 0.2f, D_807FBB40, 2, 0);
            }
            if (func_806119A0() % 3U == 0) {
                func_8071498C(&func_8071B2EC);
                func_80714998(2);
                func_807149B8(1);
                func_80714C08(&D_8071FF18, 0.2f, D_807FBB40, 3, 0);
            }
            if (func_806119A0() % 3U == 0) {
                func_8071498C(&func_8071B2EC);
                func_80714998(2);
                func_807149B8(1);
                func_80714C08(&D_8071FF18, 0.2f, D_807FBB40, 9, 0);
            }
            if (func_806119A0() % 3U == 0) {
                func_8071498C(&func_8071B2EC);
                func_80714998(2);
                func_807149B8(1);
                func_80714C08(&D_8071FF18, 0.2f, D_807FBB40, 0xA, 0);
            }
        }
        break;
    case 2:
        func_806DF6D4(5);
        G14_A->unkEE = (G14_A->unkE6 + 0x800) % 4096;
        func_806CC8A8();
        func_806CBE90();
        func_806CC948();
        break;
    case 3:
        func_806DF6D4(5);
        G14_A->unkEE = (G14_A->unkE6 + 0x800) % 4096;
        G14_P->unk30 = 5.0f;
        func_806CD8EC();
        func_806CC8A8();
        func_806CBE90();
        func_806CC948();
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D6F0C(void) {
    func_806DF494(&G14_A->unkE6, G14_A->unkEE, G14_P->unk48);
    func_806DF6D4(8);
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D6F64(void) {
    func_806EB0C0(0x3C, 0, D_807FC929);
    G14_A->unk64 |= 0x200;
    switch (G14_A->unk155) {
    case 0:
        func_806DF6D4(3);
        G14_P->unk4 = D_8075305C[D_807FD584];
        G14_P->unkA = G14_A->unkEE;
        func_806DF494(&G14_A->unkE6, (s16)((G14_A->unkEE + 0x800) & 0xFFF), (s16)(G14_P->unk48 * 2));
        break;
    case 1:
        func_806DF6D4(3);
        G14_P->unk4 = 0.0f;
        G14_A->unkB8 = 0.0f;
        break;
    case 2:
        func_806CFF9C(D_807FBB40);
        break;
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D7098(void) {
    func_806DF6D4(3);
    G14_A->unk64 |= 0x200;
    switch (G14_A->unk155) {
    case 0:
        G14_A->unkE6 = func_806CC190(G14_A->unkE6, (s16)(G14_P->unkDC->unkE6 + 0x800), 8.0f);
        G14_P->unk4 = 0.0f;
        G14_A->unkB8 = 0.0f;
        func_806CC8B8();
        break;
    case 1:
        func_806CFF9C(D_807FBB40);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D7170(void) {
    func_806EB0C0(0x3C, 0, D_807FC929);
    func_806DF6D4(3);
    switch (G14_A->unk155) {
    case 0:
        G14_P->unk4 = 0.0f;
        G14_A->unkB8 = 0.0f;
        func_806CC8B8();
        break;
    case 1:
        effectSpawnJointBeam(1, 4, 5, 8);
        break;
    case 2:
        effectSpawnRandomBoneDebris(1, 8);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D7238(void) {
    func_806EB0C0(0x5C, 0, D_807FC929);
    func_806DF6D4(3);
    G14_A->unk144 = 1;
    G14_P->unk4 = 0.0f;
    G14_A->unkB8 = 0.0f;
    func_806CC8B8();
    if (G14_P->unk21E == 0) {
        func_80712830(D_807FBB40, D_807FC929);
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D72D4(void) {
    G14Actor *a;

    func_806EB0C0(0x3C, 0, D_807FC929);
    G14_A->unk64 |= 0x200;
    a = G14_A;
    switch (a->unk155) {
    case 0:
        func_806DF6D4(3);
        G14_P->unk4 = D_807530F0[D_807FD584];
        G14_P->unkA = G14_A->unkEE;
        G14_A->unkE6 = func_806CC190(G14_A->unkE6, (s16)(G14_P->unkDC->unkE6 + 0x800), 8.0f);
        func_806CC8B8();
        break;
    case 1:
        func_806DF6D4(3);
        G14_P->unk4 = 0.0f;
        if (D_8074E77C[D_807FC929] == 4) {
            f32 t = ((G14Anim **)D_807FBB40->unk4)[0]->unk4;

            if (t >= 29.0f && t < 33.0f) {
                G14_A->unkEE = (G14_A->unkE6 + 0x800) & 0xFFF;
                G14_A->unkB8 = 150.0f;
                func_806CC948();
                break;
            }
            if (t >= 48.0f) {
                G14_A->unkEE = G14_A->unkE6;
                G14_A->unkB8 = 60.0f;
                func_806CC948();
                break;
            }
        }
        G14_A->unkB8 = 0.0f;
        func_806CC8B8();
        break;
    case 2:
        G14_A->unkB8 = 0.0f;
        func_806CFF9C(D_807FBB40);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D7510(void) {
    G14_A->unk64 |= 0x200;
    switch (G14_A->unk155) {
    case 0:
        func_806EB0C0(0x3C, 0, D_807FC929);
        func_806DF6D4(4);
        func_806DF494(&G14_A->unkE6, (s16)((G14_A->unkEE + 0x800) & 0xFFF), (s16)(G14_P->unk48 * 2));
        if (G14_A->unkFC != 0) {
            G14_A->unkB8 = G14_A->unkB8 * 0.5;
        }
        break;
    case 1:
        func_806EB0C0(0x3C, 0, D_807FC929);
        G14_P->unk4 = 0.0f;
        if (G14_A->unkFC != 0) {
            G14_A->unkB8 = G14_A->unkB8 * 0.5;
        }
        break;
    case 2:
        G14_A->unkB8 = 0.0f;
        func_806EB0C0(0x18, 0, D_807FC929);
        break;
    }
    if (G14_A->unkAC < D_807538C8[D_807FD584] + G14_A->unk80) {
        G14_A->unk80 = G14_A->unkAC - D_807538C8[D_807FD584];
    }
    G14_P->unk4 = 0.0f;
    G14_P->unk30 = 2.0f;
    func_806CC8F0();
    func_806319C4(D_807FBB40, 0);
}

void func_806D7704(void) {
    func_806EB0C0(0x3C, 0, D_807FC929);
    G14_A->unk64 |= 0x200;
    switch (G14_A->unk155) {
    case 0:
        G14_A->unkB8 = D_80753144[D_807FD584];
        func_806DF6D4(5);
        G14_P->unk4 = D_80753144[D_807FD584];
        if (G14_P->unk1A3 != 0) {
            sfxStopSlotSound(D_807FBB40, 0);
            G14_P->unk1A3 = 0;
        }
        G14_P->unkA = G14_A->unkEE;
        func_806DF494(&G14_A->unkE6, (s16)((G14_A->unkEE + 0x800) & 0xFFF), (s16)(G14_P->unk48 * 2));
        break;
    case 1:
        func_806DF6D4(3);
        G14_A->unkB8 = 0.0f;
        break;
    case 2:
        func_806DF6D4(3);
        func_806CFF9C(D_807FBB40);
        break;
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_807248B0(Actor *, f32);

void func_806D7878(void) {
    f64 t = D_807FBB40->unk4->unk38;

    func_807248B0(D_807FBB40, (0.001 - t) * 0.01 + t);
    G14_A->unk128 -= 0x14;
    if (G14_A->unk128 < 0) {
        G14_A->unk128 = 0;
    }
    func_806EB0C0(0x3C, 0, D_807FC929);
    switch (G14_A->unk155) {
    case 0:
        func_806CC8B8();
        break;
    case 1:
        func_806CC8B8();
        if (G14_P->unk11C-- == 0) {
            G14_A->unk155++;
        }
        break;
    case 2:
        if (D_8076A0A8 != 0x52 && D_8076A0A8 != 0xE) {
            func_80712830(D_807FBB40, D_807FC929);
        }
        G14_A->unk155++;
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D79E4(void) {
    func_806EB0C0(0x3C, 0, D_807FC929);
    func_806CC948();
    func_806319C4(D_807FBB40, 0);
}

typedef struct G15PlayerB {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ u8 pad8[2];
    /* 0x00A */ s16 unkA;
    /* 0x00C */ u8 padC[0x3C];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0xD2];
    /* 0x11C */ u8 unk11C;
    /* 0x11D */ u8 unk11D;
    /* 0x11E */ u8 pad11E[0xD2];
    /* 0x1F0 */ s32 unk1F0;
} G15PlayerB;

#define G15_PB ((G15PlayerB *)D_807FD580)

extern s32 D_807FBB68;
extern f32 D_80753024[];
extern f32 D_80753094[];
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_80627948(void *, s32, s32, s32);
void func_806CF918();
s32 func_80714608(s32);
void func_807149C8(s32, s32, s32, s32);
void effectSpawnBoneDefault(void *, s16, f32, f32, f32, f32, s32);

void func_806D7A28(void) {
    u8 flag;
    u8 v2;

    func_806EB0C0(0x3C, 0, D_807FC929);
    func_806DF6D4(1);
    switch (G08_A40->unk155) {
        case 0:
            G08_A40->unkC4 = D_80753024[D_807FD584];
            if (D_807FBB68 & 2) {
                func_80609140(0x424, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
            if (D_807FC928 == 1) {
                func_80627948(D_807FBB4C, 0xC, 0x25, 0x85);
            }
            G08_A40->unk155++;
        case 1:
            G08_P->unk4 = D_80753094[D_807FD584];
            G15_PB->unkA = G08_A40->unkEE;
            func_806DF494(&G08_A40->unkE6, (s16)((G08_A40->unkEE + 0x800) & 0xFFF), (s16)(G15_PB->unk48 * 2));
            func_806CC8B8();
            G15_PB->unk11C = 0xF;
            G15_PB->unk11D = 0;
            break;
        case 2:
            G08_A40->unk155++;
            G08_A40->unkB8 = 0.0f;
            func_806CC970();
            break;
        case 3:
            flag = func_80714608(0);
            if (G15_PB->unk11C == 0 && G15_PB->unk11D == 0) {
                if (!flag) {
                    func_806CF918(G15_PB->unk11C, (u32)flag);
                }
                G15_PB->unk11D = 1;
            } else {
                G15_PB->unk11C = G15_PB->unk11C - 1;
            }
            if (G15_PB->unk11D != 0) {
                v2 = G15_PB->unk11C;
                if (v2 >= 0xBF) {
                    if (!flag && v2 % 3 == 0) {
                        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, (s16)(((v2 & 2) / 2) + 0x57), 0xFF, 0x7F, 0x1E);
                    }
                } else if (flag) {
                    func_80712830(D_807FBB40, D_807FC929);
                }
            }
            if ((G15_PB->unk1F0 & 0x1000) && !(D_8076A064 & 3)) {
                func_807149C8(0x64, 0x64, 0x64, 0xC8);
                func_80714998(2);
                effectSpawnBoneDefault(D_807FBB40, (s16)(((func_80611A44() >> 15) % 32767) % 8 + 1), 0.4f, 0.0f, 0.0f, 0.0f, -0x50);
            }
            G08_A40->unkB8 = 0.0f;
            func_806CC970();
            break;
        default:
            if (D_807FC928 >= 2) {
                func_80712830(D_807FBB40, D_807FC929);
            }
            G15_PB->unk1F0 &= ~0x1000;
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D7DF8(void) {
    switch (G08_A40->unk155) {
        case 0:
            func_806DF6D4(0x45);
            G08_P->unk4 = 0.0f;
            break;
        case 1:
            func_806DF6D4(0x44);
            G08_P->unk4 = 0.0f;
            break;
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D7E88(void) {
    s16 new_var;
    u8 v;

    switch (G08_A40->unk155) {
        case 0:
            func_806DF6D4(0x46);
            G08_P->unk4 = 0.0f;
            break;
        case 1:
            if (func_806DF6D4(0x46) == 0) {
                v = func_806CE4E4(D_807FBB40, G08_A40->unkB8, G08_P->unk4, 1);
                new_var = v;
                if (v != 0x3F) {
                    G08_A40->unk154 = new_var;
                    G08_A40->unk155 = 0;
                }
            }
            break;
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D7F48(void) {
    u32 r;
    s16 v;

    func_806CBE90();
    if (func_806DF6D4(0x46) == 0) {
        r = func_806CE4E4(D_807FBB40, G08_A40->unkB8, G08_P->unk4, 1);
        if (r != 0x40) {
            v = r;
            G08_A40->unk154 = v;
            G08_A40->unk155 = 0;
            if (v == 0x3F) {
                G08_A40->unk155 = 1;
            }
        }
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D7FE8(void) {
    switch (G08_A40->unk155) {
        case 0:
            func_806DF6D4(1);
            break;
        case 1:
            G08_A40->unk154 = 0x3C;
            G08_A40->unk155 = 1;
            func_80614E78(D_807FBB40, 0xB);
            break;
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806D8070(void) {
    func_806DF6D4(1);
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

extern f32 D_80753454[];
extern f32 D_80753470[];
extern f32 D_8075348C[];
extern s16 D_807534A8[];
extern f32 D_80753738[];
void func_806CFE30();

void func_806D80A8(void) {
    switch (G08_A40->unk155) {
        case 0:
            func_80614D00(D_807FBB40, 1.0f, 0);
            func_806DF6D4(0x47);
            func_806CC948();
            func_806CD8EC();
            G08_P->unk2C = D_80753470[D_807FD584];
            G08_P->unk30 = D_8075348C[D_807FD584];
            G08_P->unk38 = D_80753454[D_807FD584];
            G08_P->unk48 = D_807534A8[D_807FD584];
            break;
        case 1:
            G08_A40->unkC0 = *(f32 *)((u8 *)D_807FD580 + 0x54);
            G08_A40->unkC4 = D_80753738[D_807FD584];
            G08_A40->unkB8 = 0.0f;
            G08_A40->unk155++;
            func_806DF6D4(0x47);
            func_806CFE30();
            func_806CC948();
            break;
        case 2:
            func_806DF494(&G08_A40->unkE6, G08_A40->unkEE, 0x32);
            func_806CFE30();
            func_806D3608();
            func_806CC8B8();
            func_806DF494(&G08_A40->unkE6, G08_A40->unkEE, 0x32);
            func_806DF6D4(0x47);
            break;
        case 3:
            func_806DF6D4(0x35);
            if (D_807FD618[D_807FC929].unk0 != 0.0f) {
                func_80614D00(D_807FBB40, 3.0f, 0.0f);
            }
            G08_P->unk4 = 0.0f;
            func_806CFE7C();
            func_806CC8B8();
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

extern f32 D_80753770[];
extern f32 D_807537A8[];
extern f32 D_807537C4[];
#define G15_EA(a) (*(s16 *)((u8 *)(a) + 0xEA))

void func_806D8308(void) {
    switch (G08_A40->unk155) {
        case 0:
            G15_EA(D_807FBB40) = G08_A40->unkEE;
            func_80614D00(D_807FBB40, 1.0f, 0);
            func_806DF6D4(0x48);
            func_806CC948();
            break;
        case 1:
            G08_A40->unkC0 = *(f32 *)((u8 *)D_807FD580 + 0x54);
            G08_A40->unkC4 = D_807537A8[D_807FD584];
            G08_A40->unkB8 = D_80753770[D_807FD584];
            G15_EA(D_807FBB40) = G08_A40->unkEE;
            G08_A40->unk155++;
            func_806DF6D4(0x48);
            func_806CFE30();
            func_806CC948();
            break;
        case 2:
            func_806CFE30();
            func_806D3608();
            func_806CC948();
            func_806DF6D4(0x48);
            break;
        case 3:
            G08_P->unk30 = D_807537C4[D_807FD584];
            func_806DF6D4(0x33);
            func_806CFE7C();
            func_806CC8B8();
            break;
        case 4:
            if (G08_P->unk4 > 10.0f) {
                func_806CFF9C(D_807FBB40);
            }
            G08_P->unk30 = D_807537C4[D_807FD584];
            func_806DF6D4(0x33);
            func_806CFE7C();
            func_806CC8B8();
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

typedef struct G15Actor {
    /* 0x00 */ u8 pad0[0x80];
    /* 0x80 */ f32 unk80;
    /* 0x84 */ u8 pad84[0x20];
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[0x10];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0x22];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[0x6C];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G15Actor;

typedef struct G15PlayerEntry {
    /* 0x000 */ u8 pad0[0x2C0];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F];
} G15PlayerEntry;

#define G15_A ((G15Actor *)D_807FBB40)

extern G15PlayerEntry *D_807FC924;
extern s16 D_8075387C[];
extern s16 D_8075388C[];
extern s16 D_807538B8[];
extern s16 D_807539DC[];
extern s16 D_807539EC[];
s32 func_806E770C();
void func_80613AF8(Actor *, s32, f32, f32);

s32 func_806D850C(void) {
    f32 sp2C;
    f32 lim;
    s32 idx;

    if (D_807FC924[D_807FC929].unk2C0 == 1) {
        sp2C = D_8075388C[D_807FD584];
    } else {
        sp2C = D_807538C8[D_807FD584];
    }
    if (G15_A->unk154 == 0x4E && func_806E770C() != 0 && G15_A->unk155 != 0 &&
        G15_A->unk80 + sp2C < G15_A->unkAC - 10.0f) {
        G08_P->unk12 = D_807539EC[D_807FD584];
        G08_P->unk14 = G15_A->unkE6;
        G08_P->unk10 = (s32)(D_807539DC[D_807FD584] * 0.5);
        G15_A->unk154 = 0x4F;
        G15_A->unk155 = 1;
        if (G15_A->unkC0 > 0.0f) {
            G15_A->unkC0 = 0.0f;
        }
        func_80614E78(D_807FBB40, 0x36);
        func_80613AF8(D_807FBB40, 0x31, 0, 8.0f);
        func_80614D00(D_807FBB40, 0.5f, 0);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x10, 0xFF, 0x7F, 1);
    }
    if (G15_A->unkAC < G15_A->unk80 + sp2C) {
        G15_A->unk80 = G15_A->unkAC - sp2C;
    }
    idx = D_807FC929;
    lim = (D_807FC924[idx].unk2C0 == 1) ? D_8075387C[D_807FD584] : D_807538B8[D_807FD584];
    if (G15_A->unkAC - G15_A->unkA4 < lim) {
        func_806EB0C0(2, 0, idx);
        return 1;
    }
    return 0;
}

typedef struct G15Sub4 {
    /* 0x00 */ u8 pad0[0x48];
    /* 0x48 */ f32 unk48;
} G15Sub4;

typedef struct G15ActorB {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ G15Sub4 *unk4;
    /* 0x08 */ u8 pad8[0x58];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u8 pad64[0x50];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0x91];
    /* 0x155 */ u8 unk155;
} G15ActorB;

#define G15_B ((G15ActorB *)D_807FBB40)

extern f32 D_80753988[];
extern f32 D_807539A4[];

void func_806D87FC(void) {
    f32 fa0;
    f32 fv1;
    f32 fv0;
    f32 fa1;

    fa0 = G15_B->unkC0;
    fv1 = D_807539A4[D_807FD584];
    fa1 = D_80753988[D_807FD584];
    if (fa0 < 0.0f) {
        fv0 = -fa0 / 3.0f;
        if (!(fv0 < fv1)) {
            fv1 = fv0;
        }
    }
    if (G15_B->unkB4 == 0.0f && (f64)fa0 < -0.1) {
        G15_B->unkC0 = -0.1f;
        fa0 = G15_B->unkC0;
    }
    fa0 = G15_B->unkC0;
    G15_B->unkC0 = func_806CD898(fa0, fa1, fv1);
    G08_P->unk24 = 0;
    switch (G15_B->unk155) {
        case 0:
            func_806DF6D4(0x4E);
            func_806CC8F0();
            break;
        case 1:
            func_806DF6D4(0x4D);
            func_806CC8F0();
            if (G15_B->unkB8 != 0.0f) {
                func_80614E78(D_807FBB40, 0x3A);
                G15_B->unk155 = 2;
            }
            break;
        default:
            func_806DF6D4(0x4D);
            func_806CC8F0();
            if (G15_B->unkB8 == 0.0f) {
                func_80614E78(D_807FBB40, 0x33);
                G15_B->unk155 = 1;
            } else {
                fv0 = G08_P->unk4 * 1.5 / 40.0;
                if (G15_B->unk4->unk48 < fv0) {
                    func_80614D00(D_807FBB40, fv0, 0.0f);
                } else {
                    func_80614D00(D_807FBB40, fv0, 5.0f);
                }
            }
            break;
    }
    func_806D850C();
    G15_B->unk60 &= ~1;
    func_806319C4(D_807FBB40, 0);
}

void func_806D8A64(void) {
    G08Actor *a;

    G08_P->unk24 = 0;
    a = G08_A40;
    switch (a->unk155) {
        case 0:
            func_80614D00(a, 1.0f, 0);
            func_806DF6D4(0x4B);
            func_806CC8B8();
            a = G08_A40;
            break;
        case 1:
            a->unkE8 = 0;
            *(s16 *)G08_A40->unkE4 = 0;
            func_806CFF9C(D_807FBB40);
            a = G08_A40;
            break;
    }
    func_806319C4(a, 0);
}

typedef struct G16Player {
    /* 0x00 */ u8 pad0[0x10];
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
    /* 0x3C */ u8 pad3C[0x14];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[2];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u8 pad58[0x14];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ s16 unk70;
    /* 0x72 */ u8 pad72[0x3E];
    /* 0xB0 */ f32 unkB0;
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x48];
    /* 0x104 */ s32 unk104;
} G16Player;

typedef struct G16Sub4 {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0xC];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ u8 pad4C[0x2C];
    /* 0x78 */ s32 unk78;
} G16Sub4;

typedef struct G16Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G16Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[6];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x24];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[8];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x1C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0xC];
    /* 0x0FC */ u8 unkFC;
    /* 0x0FD */ u8 padFD[0x47];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0x10];
    /* 0x155 */ u8 unk155;
} G16Actor;

#define G16_P ((G16Player *)D_807FD580)
#define G16_A ((G16Actor *)D_807FBB40)

#ifdef NON_MATCHING
extern s16 D_80753A88[];
extern f32 D_80753AE0[];
void effectSpawnAuraBurst(u8);
void func_806D0EBC(void *);

void func_806D8B08(void) {
    s16 v;
    f32 t;
    f32 fv0;

    G16_P->unk24 = G16_P->unk24 + 1;
    G16_P->unk2C = D_80753AFC[D_807FD584];
    switch (G16_A->unk155) {
        case 0:
            func_806DF6D4(0x4C);
            t = D_80753A5C[D_807FD584];
            G16_A->unkC0 = func_806CD898(G16_A->unkC0, t, G16_P->unk1C);
            if (t <= G16_A->unkC0) {
                if (G16_A->unkB8 != 0.0f || G16_P->unk10 != 0) {
                    G16_A->unk155 = 3;
                } else {
                    G16_A->unk155 = 2;
                }
                G16_A->unk4->unk78 &= ~0x4000;
            }
            func_806CC5DC();
            effectSpawnAuraBurst(1);
            goto end;
        case 1:
            func_806DF6D4(0x4F);
            func_806CC638(0.0f);
            if (G16_P->unk10 == 0) {
                G16_A->unk155 = 3;
            }
            t = G16_P->unk10 / 7.5 + 1.0;
            if (G16_A->unk4->unk48 < t) {
                func_80614D00(D_807FBB40, t, 0.0f);
            } else {
                func_80614D00(D_807FBB40, t, 15.0f);
            }
            effectSpawnAuraBurst(2);
            fv0 = G16_A->unkAC;
            if (fv0 < (f32)D_807538C8[D_807FD584] + G16_A->unk80) {
                G16_A->unk80 = fv0 - (f32)D_807538C8[D_807FD584];
            }
            goto end;
        default:
            func_806DF6D4(0x54);
            func_806CC638(D_80753A5C[D_807FD584]);
            if (G16_A->unkB8 != 0.0f) {
                G16_P->unk18 = 0;
                G16_A->unk155 = 3;
            } else {
                if (G16_P->unk50 != 0) {
                    G16_P->unk50 = G16_P->unk50 - 1;
                    if (G16_P->unk50 == 0) {
                        func_80614E78(D_807FBB40, 0x34);
                    }
                }
            }
            func_806D0EBC(D_807FBB40);
            goto end;
        case 3:
            func_806DF6D4(0x50);
            func_806CC638(0.0f);
            break;
        case 4:
            func_806DF6D4(0x51);
            G16_P->unk12 = G16_A->unkE8;
            G16_P->unk14 = G16_A->unkE6;
            G16_P->unk38 = D_80753AE0[D_807FD584];
            G16_P->unk10 = D_80753A88[D_807FD584];
            func_806CC638(0.0f);
            G16_A->unk155 = G16_A->unk155 + 1;
            break;
        case 5:
            func_806DF6D4(0x51);
            func_806CC638(0.0f);
            break;
        case 6:
            func_806DF6D4(0x52);
            func_806CC638(0.0f);
            break;
        case 7:
            func_806DF6D4(0x51);
            func_806CC638(0.0f);
            break;
        case 8:
            func_806DF6D4(0x53);
            func_806CC638(0.0f);
            break;
    }
    if (G16_A->unkB8 == 0.0f || G16_P->unk18 != 0) {
        G16_P->unk50 = D_80753A78[D_807FD584];
        func_80614D00(D_807FBB40, 0.5f, (f32)G16_P->unk50);
        G16_A->unk155 = 2;
    }
    func_806D0EBC(D_807FBB40);
end:
    func_806319C4(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806D8B08.s")
#endif

void func_806D8FCC(void) {
    G16_P->unk24 = 0;
    G16_A->unkE4 = 0;
    G16_A->unkE8 = 0;
    switch (G16_A->unk155) {
        case 0:
            func_806D3FA0();
            func_806DF6D4(0x21);
            func_806CC8F0();
            break;
        case 1:
            func_806CC8B8();
            G16_A->unkC0 = G16_P->unk54;
            func_806CFECC();
            G16_A->unk155 = G16_A->unk155 + 1;
            func_806DF6D4(0x21);
            func_806CFD68();
            break;
        case 2:
            func_806CC8B8();
            func_806DF6D4(0x21);
            if (G16_A->unk58 == 5) {
                func_806DF6D4(0x22);
            } else {
                func_806DF6D4(0x21);
            }
            func_806CFD68();
            break;
        case 3:
            func_806CC8B8();
            func_806DF6D4(0x30);
            func_806CFE7C();
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D9134(void) {
    func_806DF6D4(1);
    G08_A40->unkB8 = 0.0f;
    G08_A40->unkC0 = 0.0f;
    func_806CC970();
    func_806319C4(D_807FBB40, 0);
}

void func_806D9184(void) {
    func_806D9134();
}

extern s32 D_8072014C;
void func_806CFF1C();
void func_807149FC(s32);

void func_806D91A4(void) {
    s32 n;
    u16 nv;
    u16 b;
    s32 z;

    if (G16_A->unkFC) {
        G16_A->unkB8 = 0.0f;
        func_806CFF1C(D_807FBB40);
    }
    if (G16_A->unkFC || ((G16_A->unk6A & 1) && !(G16_A->unk6C & 1))) {
        func_806224CC(G16_P->unk104, D_807FBB40);
    }
    if (!(G16_A->unk6A & 1)) {
        func_807149B8(1);
        func_807149FC(1);
        func_80714C08(&D_8072014C, 0.8f, D_807FBB40, 1, 0);
    }
    nv = G16_A->unk6C;
    b = nv;
    z = (b == 0);
    n = (G16_A->unk6A & b & 1) ? 2 : 1;
    if (((z ^ 0) & G16_A->unk6A) & 1) {
        G16_A->unkB8 = G16_A->unkB8 * 0.25;
    }
    if (z) {
    }
    if (G16_A->unkB8 < (f32)n) {
        G16_A->unkB8 = 0.0f;
    } else {
        G16_A->unkB8 = G16_A->unkB8 - (f32)n;
    }
    func_806DF6D4(1);
    func_806CC948();
    func_806319C4(D_807FBB40, 0);
}

f32 func_80611BB4(f32, f32);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void func_80617770(void *, s32, s32);
extern f32 D_80753CD0[];
extern f32 D_80753250[];
#define G16_E ((G16Actor *)D_807FBB4C)

void func_806D9320(void) {
    f32 pad;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 dz;
    f32 dx;
    f32 fa0;
    f32 fv0;
    s32 n;
    u16 nv;
    u16 b;
    s32 z;

    switch (G16_A->unk155) {
        case 0:
            G16_A->unk60 &= 0xFFBFFFFF;
            if (G16_A->unkFC || ((G16_A->unk6A & 1) && !(G16_A->unk6C & 1))) {
                func_806224CC(G16_P->unk104, D_807FBB40);
            }
            if (!(G16_A->unk6A & 1)) {
                func_807149B8(1);
                func_807149FC(1);
                func_80714C08(&D_8072014C, 0.8f, D_807FBB40, 1, 0);
            }
            nv = G16_A->unk6C;
            b = nv;
            z = (b == 0);
            n = (G16_A->unk6A & b & 1) ? 2 : 1;
            if (z) {
            }
            if (((z ^ 0) & G16_A->unk6A) & 1) {
                G16_A->unkB8 = G16_A->unkB8 * 0.25;
            }
            if (G16_A->unkB8 < (f32)n) {
                G16_A->unkB8 = 0.0f;
            } else {
                G16_A->unkB8 = G16_A->unkB8 - (f32)n;
            }
            G16_A->unkE8 = func_80611BB4(G16_A->unkB8, G16_A->unkC0) * 4096.0f / 6.2831855f;
            G16_A->unkE6 = (mathAngleBetweenPoints2D(G16_A->unk7C, G16_A->unk84, G16_P->unkB0, G16_P->unkB8) + 0x800) % 4095;
            G16_A->unkEE = G16_A->unkE6;
            temp_fa1 = G16_P->unkB4 - G16_E->unk80;
            temp_fa1 = temp_fa1 / (G16_E->unk4->unk38 * 0.16666666675);
            dx = G16_P->unkB8 - G16_E->unk84;
            dz = G16_P->unkB0 - G16_E->unk7C;
            temp_ft4 = sqrtf(dx * dx + dz * dz) / (G16_E->unk4->unk38 * 0.16666666675);
            fa0 = G16_E->unkB8;
            if (fa0 == 0.0) {
                fa0 = 1.0f;
            }
            fv0 = temp_ft4 / fa0 - 1.0f;
            if (fv0 < 1.0f) {
                fv0 = 1.0f;
            }
            G16_E->unkC0 = (0.0 - (D_80753CD0[D_807FD584] * 0.5 * (fv0 * fv0) - temp_fa1)) / fv0;
            G16_E->unkC4 = -0.001f;
            if (fv0 < 2.0f || fa0 < 2.0) {
                func_806CFE7C();
                G16_A->unk155 = G16_A->unk155 + 1;
            }
            if (G16_A->unkFC) {
                G16_A->unkB8 = 0.0f;
                func_806CFE7C();
                G16_A->unk155 = G16_A->unk155 + 1;
            }
            func_806DF6D4(1);
            break;
        case 1:
            func_806DF6D4(0x20);
            func_80614E78(D_807FBB40, 0x23);
            G16_A->unkE8 = 0;
            func_806CFE7C();
            G16_A->unk155 = G16_A->unk155 + 1;
            break;
        case 2:
            func_806DF6D4(0x20);
            break;
        case 3:
            func_80617770(D_807FBB40, 0x10, 0);
            G16_P->unk30 = D_80753250[D_807FD584];
            G16_A->unk155 = G16_A->unk155 + 1;
        case 4:
            func_806CD8EC();
            func_806DF6D4(0x30);
            break;
    }
    func_806CC948();
    func_806319C4(D_807FBB40, 0);
}

void func_806D97A4(void) {
    func_806DF6D4(5);
    if (G16_A->unkC0 < 0.0f) {
        G16_P->unk6C = 0.0f;
    }
    func_806CD424(G16_P->unk70, G16_P->unk6C, G16_P->unk38);
    func_806CC948();
    func_806319C4(D_807FBB40, 0);
}

void func_806D9820(void) {
    f32 t;
    f32 v;

    func_806DF6D4(0x4A);
    switch (G16_A->unk155) {
        case 0:
            if (G16_P->unk38 < G16_A->unkB8) {
                func_806CD8EC();
                func_806CC948();
            } else {
                func_806CC8B8();
            }
            t = G16_A->unkB8 * 0.025;
            v = (t > 1.0) ? t : 1.0;
            func_80614D00(D_807FBB40, v, 0.0f);
            break;
        case 1:
            func_806CC8B8();
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D9924(Actor *arg0) {
    ((G16Actor *)arg0)->unkE8 = 0;
    ((G16Actor *)arg0)->unkE4 = 0;
    arg0->unk60 &= ~1;
}

s32 func_8061CB80();
void mapChunkSetIndexOverride(s32);
void sfxAllocateChannel(s32, f32);

void func_806D9940(void) {
    s32 ch;
    f32 vol;

    func_806DF6D4(1);
    if (G16_A->unk155 < 3 ||
        (func_8061CB80() != 0 && (func_8061CB98(7) != 0 || func_8061CB98(0) != 0 || func_8061CB98(4) != 0 ||
                                  func_8061CB98(9) != 0 || func_8061CB98(8) != 0))) {
        mapChunkSetIndexOverride(1);
    }
    switch (G16_A->unk155) {
        case 0:
            if (!(D_807FBB68 & 2)) {
                G16_A->unk144 = 1;
            }
            break;
        case 1:
            vol = 1.0f;
            ch = 0xA;
            switch (G16_A->unk58) {
                case 2:
                    ch = 0xB;
                    break;
                case 5:
                    ch = 0xD;
                    break;
                case 4:
                    ch = 0xC;
                    if (!(D_807FBB68 & 2)) {
                        vol = 0.82f;
                    }
                    break;
                case 6:
                    ch = 9;
                    break;
            }
            sfxAllocateChannel(ch, vol);
            G16_A->unk155 = G16_A->unk155 + 1;
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

typedef struct G17Sub4 {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34;
} G17Sub4;

typedef struct G17Actor {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ G17Sub4 *unk4;
    /* 0x08 */ u8 pad8[0x58];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u8 pad64[6];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x30];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
    /* 0xC8 */ u8 padC8[0x1E];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0x38];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ u8 pad12A[0x2A];
    /* 0x154 */ s8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x12];
    /* 0x168 */ s16 unk168;
} G17Actor;

typedef struct G17Obj {
    /* 0x00 */ u8 pad0[0x54];
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
} G17Obj;

typedef struct G17Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ u8 pad8[2];
    /* 0x00A */ s16 unkA;
    /* 0x00C */ u8 padC[0x20];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[0x14];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0x2E];
    /* 0x078 */ f32 unk78;
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ s16 unk80;
    /* 0x082 */ u8 pad82[0x3E];
    /* 0x0C0 */ s16 unkC0;
    /* 0x0C2 */ u8 padC2[0xEA];
    /* 0x1AC */ G17Obj *unk1AC;
    /* 0x1B0 */ G17Obj *unk1B0;
    /* 0x1B4 */ s32 unk1B4;
    /* 0x1B8 */ s16 unk1B8;
    /* 0x1BA */ u8 pad1BA[0x66];
    /* 0x220 */ f32 unk220;
    /* 0x224 */ u8 pad224[4];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ u8 pad230[4];
    /* 0x234 */ f32 unk234;
    /* 0x238 */ f32 unk238;
    /* 0x23C */ u16 unk23C;
    /* 0x23E */ u8 pad23E[4];
    /* 0x242 */ u16 unk242;
} G17Player;

#define G17_A ((G17Actor *)D_807FBB40)
#define G17_P ((G17Player *)D_807FD580)

extern f32 D_807FBC58;
void func_806CA2AC(void);
s32 actorTableContains(void *);
void actorAppendCallback(void *, void *, s32, s32, s32, s32);
void func_8067A784(void *, void *, s16, f32, s32);
void func_806CEC04(void *);
extern f32 D_807533B8[];
#define G17_B48 ((G17Actor *)D_807FBB48)
void func_806CEE64(f32);
void func_806CF0D0(void);
void func_806CEED8(void);
s16 func_806CE928(Actor *, f32, f32, s32);

void func_80717100();
extern u8 D_8071FC8C;
void func_805FF9AC(u16, s16, s16, s16);
f32 func_80612794(s16);
void sfxSetChannelTempo(s32, f32);
void sfxStopChannel(s32, s32);

void func_806D9AD4(void) {
    f32 pad;
    f32 sp28;
    s32 sel;

    func_806DF6D4(1);
    sel = G17_A->unk155;
    if (sel == 1 || sel == 2) {
        func_80611A44();
        sp28 = (s32)(func_80611A44() >> 15) % 30 + G17_A->unk80;
        func_80611A44();
        func_807149B8(1);
        func_80714950((G17_P->unk23C << 16) + (s32)(15.0 * (G17_A->unk128 / 255.0)));
        func_8071498C(func_80717100);
        func_80714CC0((s32)&D_8071FC8C, 0.5f, G17_A->unk7C, sp28, G17_A->unk84);
        sel = G17_A->unk155;
    }
    switch (sel) {
    case 0:
        G17_P->unk23C = 0;
        G17_A->unk155++;
        G17_A->unk60 &= 0xFFFF7FFF;
        G17_A->unk128 = 0xFF;
        break;
    case 1:
        G17_P->unk23C += 0x1E;
        if (G17_P->unk23C >= 0x191) {
            G17_P->unk23C = 0x190;
        }
        if (G17_P->unk23C == 0xD2) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x264, 0xFF, 0x64, 0x19);
        }
        if (G17_P->unk23C >= 0x12D) {
            D_807FD580->unk1F0 &= ~0x40;
            G17_A->unk128 -= 5;
            if (G17_A->unk128 < 0xA) {
                G17_A->unk155++;
            }
        }
        break;
    case 2:
        func_805FF9AC(G17_P->unk242, 0, 0, 3);
        G17_A->unk155++;
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D9D58(void) {
    f32 v;

    switch (G17_A->unk155) {
    case 0:
        G17_A->unkC0 = 0.0f;
        G17_A->unkB8 = 0.0f;
        G17_P->unk30 = 1.0f;
        G17_P->unk2C = 3.0f;
        G17_A->unkC4 = 2.0f;
        G17_P->unk23C = 0;
        G17_P->unk238 = G17_A->unk80;
        G17_A->unk155++;
        break;
    case 1:
        func_806DF6D4(0x43);
        func_806DF494(&G17_A->unkE6, G17_A->unkEE, 0x32);
        G17_A->unk80 = G17_P->unk238;
        func_806CC8B8();
        if (G17_P->unk238 - G17_A->unk168 > 50.0f) {
            G17_A->unk80 -= 1.0;
        }
        G17_P->unk238 = G17_A->unk80;
        G17_A->unk80 = func_80612794((s16)G17_P->unk23C) * 10.0 + G17_P->unk238;
        G17_P->unk23C += 0x64;
        if (G17_A->unk168 < G17_A->unk80) {
            v = G17_A->unk80 - G17_A->unk168;
        } else {
            v = -(G17_A->unk80 - G17_A->unk168);
        }
        if (v < 150.0) {
            G17_A->unkC4 = 2.0 * ((G17_A->unk168 - G17_A->unk80) / 150.0);
        }
        if (G17_A->unk168 <= G17_A->unk80) {
            G17_A->unkC0 = 0.0f;
            G17_A->unkC4 = -0.01f;
        }
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806D9FD0(void) {
    switch (G17_A->unk155) {
    case 0:
        G17_A->unkC0 = 0.0f;
        G17_A->unkB8 = 0.0f;
        G17_P->unk30 = 2.0f;
        G17_P->unk2C = 5.0f;
        break;
    case 1:
        func_806DF494(&G17_A->unkE6, G17_A->unkEE, 0x32);
        func_806DF6D4(0x43);
        G17_A->unkC4 -= 0.036;
        func_806CC8B8();
        sfxSetChannelTempo(0x6B, 0.995f);
        if (G17_A->unkC0 <= 0.0f && G17_A->unkC4 < 0.0f) {
            G17_A->unkC0 = 0.0f;
            G17_A->unkC4 = -0.01f;
            G17_A->unk168 = 0;
            G17_A->unk155++;
        }
        if (*(u16 *)((u8 *)&D_807FD63C + D_807FC929 * 0x34) & 0x2000) {
            G17_A->unk155 = 3;
            G17_A->unkC4 = -1.0f;
        }
        break;
    case 2:
        func_806DF494(&G17_A->unkE6, G17_A->unkEE, 0x32);
        func_806DF6D4(0x43);
        func_806DF494(&G17_A->unkE6, G17_A->unkEE, 0x32);
        G17_A->unk168++;
        G17_A->unk80 += func_80612794(G17_A->unk168 << 5) * 0.25;
        func_806CC8F0();
        sfxSetChannelTempo(0x6B, 0.995f);
        G17_P->unkC0--;
        if (G17_P->unkC0 < 0 || (*(u16 *)((u8 *)&D_807FD63C + D_807FC929 * 0x34) & 0x2000)) {
            G17_A->unk155++;
        }
        break;
    case 3:
        func_80614EBC(D_807FBB40, 0x16A);
        func_806DF6D4(0x43);
        func_806CC8B8();
        G17_A->unk155++;
        break;
    case 4:
        G17_A->unkC4 -= 1.0f;
        func_806DF6D4(0x43);
        func_806CC8B8();
        break;
    case 5:
        sfxStopChannel(0x6B, 0);
        func_806DF6D4(0x43);
        func_806CC8B8();
        break;
    case 6:
        sfxStopChannel(0x6B, 0);
        func_806DF6D4(0x43);
        func_806CC8B8();
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

void func_806DA320(void) {
    f32 v;
    if ((f64)D_807FBC58 != 0.0) {
        v = D_807FBC58;
    } else {
        v = G17_A->unkB8;
    }
    func_80614D00(D_807FBB40, v / 25.0f + 0.25, 2.0f);
    func_806DF6D4(0x49);
    if (!(G17_A->unk6A & 0x10)) {
        func_806CFF9C(D_807FBB40);
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806DA3E4(void) {
    func_806CA2AC();
    func_806DF6D4(5);
    G17_A->unkB8 = 0.0f;
    G17_A->unk7C = (G17_P->unk22C - G17_A->unk7C) * 0.2 + G17_A->unk7C;
    G17_A->unk84 = (G17_P->unk234 - G17_A->unk84) * 0.2 + G17_A->unk84;
    func_806DF494(&G17_A->unkE6, (s16)mathAngleBetweenPoints2D(G17_P->unk220, G17_P->unk228, G17_A->unk7C, G17_A->unk84), 0x32);
    func_806CC970();
    func_806319C4(D_807FBB40, 0);
}

void func_806DA4D8(void) {
    f64 new_var;

    if (actorTableContains(G17_P->unk1B0) == 0 || G17_P->unk1B0->unk54 != G17_P->unk1B4) {
        G17_P->unk1AC = NULL;
        G17_P->unk1B0 = NULL;
        func_806CFF9C(D_807FBB40);
        func_806CC8B8();
        func_806319C4(D_807FBB40, 0);
        return;
    }
    switch (G17_A->unk155) {
    case 0:
        G17_A->unkB8 = 0.0f;
        G17_P->unk4 = 0.0f;
        func_806CEC04(G17_P->unk1B0);
        G17_A->unk7C += G17_P->unk78;
        G17_A->unk84 += G17_P->unk7C;
        G17_A->unkE6 = G17_P->unk80;
        G17_A->unk155++;
        break;
    case 1:
        G17_A->unk7C += G17_P->unk78;
        G17_A->unk84 += G17_P->unk7C;
        G17_A->unkE6 = G17_P->unk80;
        break;
    case 2:
        G17_P->unk1AC = G17_P->unk1B0;
        G17_P->unk1B8 = G17_P->unk1AC->unk58;
        actorAppendCallback(G17_P->unk1AC, D_807FBB40, 0x2000, 1, 0, 0);
        func_806CEE64(0.4f);
        func_806CEED8();
        G17_A->unk155++;
        break;
    case 3:
        func_806DF6D4(5);
        func_806CEE64(0.4f);
        func_806CEED8();
        break;
    case 4:
        func_806DF6D4(5);
        func_8067A784(D_807FBB40, G17_P->unk1AC, G17_B48->unkE6, G17_A->unk4->unk34 * (D_807533B8[D_807FD584] * 3.0) / (new_var = 0.15), 0);
        G17_A->unk155++;
        break;
    case 5:
        func_806DF6D4(5);
        break;
    case 6:
        G17_P->unk1AC = G17_P->unk1B0;
        G17_P->unk1B8 = G17_P->unk1AC->unk58;
        actorAppendCallback(G17_P->unk1AC, D_807FBB40, 0x2000, 1, 0, 0);
        func_806CEE64(0.4f);
        func_806CEED8();
        G17_A->unk155 = 3;
        break;
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806DA7EC(void) {
    func_806DF6D4(6);
    if (D_807FD618[D_807FC929].unk0 != 0.0f) {
        func_80614D00(D_807FBB40, 3.0f, 0.0f);
    }
    func_806DF494(&G17_A->unkE6, G17_P->unkA, G17_P->unk48);
    G17_P->unk4 = 0.0f;
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806DA89C(void) {
    func_806DF6D4(7);
    if (D_807FD618[D_807FC929].unk0 != 0.0f) {
        func_80614D00(D_807FBB40, 2.0f, 0.0f);
    }
    func_806DF494(&G17_A->unkE6, G17_P->unkA, G17_P->unk48);
    G17_P->unk4 = 0.0f;
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806DA94C(void) {
    D_807FD580->unk1F0 &= 0xFEFFFFFF;
    func_806CEE64(1.0f);
    func_806CF0D0();
    func_806CEED8();
    G17_A->unk154 = func_806CE928(D_807FBB40, G17_A->unkB8, G17_P->unk4, 1);
    G17_A->unk155 = 0;
    func_806DF6D4(0x37);
    if (!(G17_A->unk6A & 1)) {
        func_806D3608();
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

void func_806DAA14(void) {
    D_807FD580->unk1F0 &= 0xFEFFFFFF;
    func_806CEE64(1.0f);
    func_806CF0D0();
    func_806CEED8();
    G17_A->unk154 = func_806CE928(D_807FBB40, G17_A->unkB8, G17_P->unk4, 1);
    G17_A->unk155 = 0;
    func_806DF6D4(0x37);
    if (!(G17_A->unk6A & 1)) {
        func_806D3608();
    }
    func_806CC8B8();
    func_806319C4(D_807FBB40, 0);
}

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

typedef struct L6Actor {
    /* 0x000 */ u8 pad0[0x6A];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x14];
    /* 0x080 */ f32 unk80;
    /* 0x084 */ u8 pad84[0x28];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[0xA5];
    /* 0x155 */ u8 unk155;
} L6Actor;

typedef struct L6Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ u8 padA[0x82];
    /* 0x08C */ u8 unk8C;
    /* 0x08D */ u8 pad8D[7];
    /* 0x094 */ f32 unk94;
    /* 0x098 */ u8 pad98[8];
    /* 0x0A0 */ u8 padA0[0x60];
    /* 0x100 */ s32 unk100;
} L6Player;

#define L6_A ((L6Actor *)D_807FBB40)
#define L6_P ((L6Player *)D_807FD580)

extern s16 D_80753CA4[];
extern f32 D_80753C30[];
extern f32 D_80753C4C[];
extern f32 D_80753C68[];
extern u8 func_807300BC;
void func_806DC3A4(f32);

void func_806DD24C(void) {
    ActorCallbackNode *node;
    s32 pad[1];
    f32 sp1C;
    f32 f;
    f64 d;

    if (L6_A->unk155 != 0 && (!(L6_A->unk6A & 0x40) || ((L6_A->unk6A & 4) && (f64)(L6_A->unkAC - L6_A->unk80) > 3.0))) {
        func_806CFF1C(D_807FBB40);
        if (L6_P->unk8C != 0) {
            func_806D374C();
            return;
        }
        func_806D36CC();
        return;
    }
    L6_P->unk100 = D_80753CA4[D_807FD584];
    node = func_80610FE8(0x14);
    node->callback = &func_807300BC;
    node->unk8 = (s32)D_807FBB48;
    node->unk4 = 1;
    actorRegisterGlobalCallback(node);
    switch (L6_A->unk155) {
    case 0:
        func_806DF6D4(5);
        L6_P->unk94 = 0.0f;
        break;
    case 1:
        if (func_806DF6D4(0x59) == 0) {
            switch (L6_P->unk8) {
            case 1:
                sp1C = D_80753C30[D_807FD584];
                L6_A->unk155 = 3;
                func_80614E78(D_807FBB48, 0x71);
                break;
            case 0:
                sp1C = D_80753C68[D_807FD584];
                break;
            case -1:
                sp1C = D_80753C4C[D_807FD584];
                L6_A->unk155 = 4;
                func_80614E78(D_807FBB48, 0x72);
                break;
            }
            func_806DC3A4(sp1C);
            func_80614D00(D_807FBB40, 1.0f, 0.0f);
        }
        break;
    case 2:
        if (func_806DF6D4(0x59) == 0) {
            if (L6_P->unk94 == 0.0f && L6_P->unk4 == 0.0f) {
                L6_A->unk155 = 1;
                func_80614E78(D_807FBB48, 0x73);
            } else if (L6_P->unk94 > 0.0f && L6_P->unk4 > 0.0f) {
                L6_A->unk155 = 3;
                func_80614E78(D_807FBB48, 0x71);
            } else if (L6_P->unk94 < 0.0f && L6_P->unk4 < 0.0f) {
                L6_A->unk155 = 4;
                func_80614E78(D_807FBB48, 0x72);
            }
            func_806DC3A4(D_80753C68[D_807FD584]);
            d = L6_P->unk94 * 0.025;
            if (d > 0.0) {
                f = d;
            } else {
                f = -d;
            }
            func_80614D00(D_807FBB40, f, 0.0f);
        }
        break;
    case 3:
        if (func_806DF6D4(0x59) == 0) {
            if (L6_P->unk94 <= 0.0f) {
                L6_A->unk155 = 2;
            }
            switch (L6_P->unk8) {
            case -1:
                sp1C = D_80753C4C[D_807FD584] * 2;
                break;
            case 0:
                sp1C = D_80753C68[D_807FD584];
                break;
            case 1:
                sp1C = D_80753C30[D_807FD584];
                break;
            }
            func_806DC3A4(sp1C);
            d = L6_P->unk94 * 0.025;
            if (d > 0.0) {
                f = d;
            } else {
                f = -d;
            }
            func_80614D00(D_807FBB40, f, 0.0f);
        }
        break;
    case 4:
        if (func_806DF6D4(0x59) == 0) {
            if (L6_P->unk94 >= 0.0f) {
                L6_A->unk155 = 2;
            }
            switch (L6_P->unk8) {
            case -1:
                sp1C = D_80753C4C[D_807FD584];
                break;
            case 0:
                sp1C = D_80753C68[D_807FD584];
                break;
            case 1:
                sp1C = D_80753C30[D_807FD584];
                break;
            }
            func_806DC3A4(sp1C);
            d = L6_P->unk94 * 0.025;
            if (d > 0.0) {
                f = d;
            } else {
                f = -d;
            }
            func_80614D00(D_807FBB40, f, 0.0f);
        }
        break;
    }
    func_806CC970();
}


#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DD874.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DDAB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DE264.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DE930.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DE9F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/D5E10/func_806DEAA4.s")

typedef struct G20Actor {
    /* 0x000 */ u8 pad0[0x155];
    /* 0x155 */ u8 unk155;
} G20Actor;

#define G20_A ((G20Actor *)D_807FBB40)

void func_8061CB08();

void func_806DECD4(void) {
    if (G20_A->unk155 == 1) {
        func_8061CB08();
        G20_A->unk155++;
        func_806CFF9C(D_807FBB40);
    }
    func_806319C4(D_807FBB40, 0);
}

typedef struct G20Sub4 {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
} G20Sub4;

typedef struct G20Sub174 {
    /* 0x000 */ u8 pad0[0x1A4];
    /* 0x1A4 */ u8 unk1A4;
} G20Sub174;

typedef struct G20Light {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ u8 unk1E;
} G20Light;

typedef struct G20ActorE {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G20Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x80];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x32];
    /* 0x11C */ void *unk11C;
    /* 0x120 */ u8 pad120[0xC];
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[0x26];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ void *unk174;
} G20ActorE;

#define G20_E40 ((G20ActorE *)D_807FBB40)
#define G20_E44 ((G20ActorE *)D_807FBB44)

s32 func_806F8EB4();
void func_8061CC40(void *, s32, s32);
void func_8067B238(void *, void *, f32);
void lightGetColor(f32 *, f32 *, f32 *, s16);
void lightSetColor(f32, f32, f32, s16);
void func_80629174();
void effectSpawnKongRing();
void func_80709464(u8);
void func_806F8BC4(s32, s32, s32);
extern s32 D_80750FE0;
extern s32 D_80750FF0;

void func_806DED44(void) {
    G20Light *light;
    G20Sub174 *owner;
    s32 col;
    s32 *p;
    s32 sel;
    s32 a1;

    func_806DF6D4(1);
    func_806D9924(D_807FBB40);
    sel = G20_E40->unk155;
    switch (sel) {
    case 0:
        if (func_806F8EB4() == 0x14) {
            a1 = 0x1A;
        } else {
            a1 = 0x11;
        }
        func_8061CC40(D_807FBB40, a1, 5);
        G20_E40->unk155 = 1;
        break;
    case 1:
        D_807FBB60 &= 0xFFFEFFCF;
        actorSpawn(0x141, 0x3D);
        func_8067B238(D_807FBB44, D_807FBB40, G20_E40->unk4->unk38 * 2);
        G20_E44->unk60 |= 0x40000000;
        G20_E44->unkE6 += 0x800;
        G20_E44->unkE6 &= 0xFFF;
        G20_E44->unk11C = D_807FBB40;
        func_80614EBC(D_807FBB44, 0x2B7);
        light = G20_E44->unk174;
        light->unk10 = D_807FBB40;
        light->unk18 = G20_E40->unk12C;
        col = light->unk18;
        if (col == -1) {
            light->unk18 = 0;
            col = 0;
        }
        light->unk16 = G20_E40->unkE8;
        light->unk14 = G20_E40->unkE4;
        lightGetColor(&light->unk0, &light->unk4, &light->unk8, col);
        lightSetColor(1.0f, 1.0f, 1.0f, ((s16 *)light)[0x1A / 2]);
        actorSpawn(0x136, 0xA8);
        func_8067B238(D_807FBB44, D_807FBB40, G20_E40->unk4->unk34);
        G20_E44->unk60 |= 0x40000000;
        light->unkC = D_807FBB44;
        light->unk1E = func_806F8EB4() == 0x14;
        G20_E40->unk155 = 2;
        break;
    case 2:
        if (func_80629148()) {
            func_80629174();
            effectSpawnKongRing();
            sfxAllocateChannel(0x3B, 1.0f);
            G20_E40->unk155 = 3;
        }
    case 3:
        if (func_80629148()) {
            owner = G20_E40->unk174;
            func_80629174();
            func_806CFF9C(D_807FBB40);
            func_80709464(owner->unk1A4);
            p = &D_80750FE0;
            do {
                func_806F91B4(*p, 0, 0x270F);
                func_806F8BC4(*p, 0, 0);
            } while (++p != &D_80750FF0);
        }
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

typedef struct G20Block {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[0x2E9];
    /* 0x2EA */ u8 unk2EA;
    /* 0x2EB */ u8 unk2EB;
    /* 0x2EC */ u8 pad2EC[4];
} G20Block;

typedef struct G20ActorC {
    /* 0x000 */ u8 pad0[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0xC4];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ u8 pad12A[0x4A];
    /* 0x174 */ G20Sub174 *unk174;
} G20ActorC;

#define G20_C ((G20ActorC *)D_807FBB40)

#define G20_BLK ((G20Block *)D_807FC924)
extern u8 D_80750AB8;

void func_806DF050(void) {
    G20Sub174 *sub = G20_C->unk174;
    s32 step;
    s16 cur;

    func_806EB0C0(0x5C, 0, D_807FC929);
    if (D_80750AB8 == 0) {
        G20_BLK[sub->unk1A4].unk2EA = 1;
    }
    G20_BLK[sub->unk1A4].unk2EB = 1;
    G20_C->unk60 &= 0xFFFF7FFF;
    cur = G20_C->unk128;
    step = (cur < 4) ? cur : 4;
    G20_C->unk128 = cur - step;
    if (G20_C->unk128 == 0) {
        if (D_80750AB8 == 0) {
            G20_BLK[sub->unk1A4].unk0 = 0;
        }
        G20_C->unk60 &= ~4;
    }
    func_806CC948();
    func_806319C4(D_807FBB40, 0);
}

typedef struct G20Target {
    /* 0x000 */ u8 pad0[0x220];
    /* 0x220 */ f32 unk220;
    /* 0x224 */ u8 pad224[4];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ f32 unk234;
} G20Target;

typedef struct G20ActorB {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G20Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x74];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ u8 padE6[0x8E];
    /* 0x174 */ G20Target *unk174;
} G20ActorB;

#define G20_B ((G20ActorB *)D_807FBB40)

void func_806DF1A0(void) {
    G20Target *t = G20_B->unk174;

    G20_B->unk4->unk34 *= 0.92;
    G20_B->unk4->unk38 = G20_B->unk4->unk34;
    G20_B->unk4->unk3C = G20_B->unk4->unk34;
    G20_B->unk7C += (t->unk22C - G20_B->unk7C) * 0.125f;
    G20_B->unk80 += (t->unk230 - G20_B->unk80) * 0.125f;
    G20_B->unk84 += (t->unk234 - G20_B->unk84) * 0.125f;
    G20_B->unkE4 += 0xFF;
    func_806319C4(D_807FBB40, 0);
}

typedef struct G20ActorD {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G20Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x74];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ u8 padE6[0x6E];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ G20Target *unk174;
} G20ActorD;

#define G20_D ((G20ActorD *)D_807FBB40)

void func_806DF280(void) {
    G20Target *t = G20_D->unk174;

    G20_D->unk4->unk34 *= 1.08;
    if (G20_D->unk4->unk34 > 0.15) {
        G20_D->unk4->unk34 = 0.15f;
        G20_D->unk154 = 0xC;
        G20_D->unk155 = 0;
        G20_D->unkE4 = -0xFF;
    }
    G20_D->unk4->unk38 = G20_D->unk4->unk34;
    G20_D->unk4->unk3C = G20_D->unk4->unk34;
    G20_D->unk7C += t->unk220;
    G20_D->unk84 += t->unk228;
    G20_D->unkE4 += 0xFF;
    G20_D->unkE4 &= 0xFFF;
    func_806319C4(D_807FBB40, 0);
}
