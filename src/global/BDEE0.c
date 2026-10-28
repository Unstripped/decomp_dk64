#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;

typedef struct BDEE0Node {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x12];
    /* 0x24 */ f32 unk24;
} BDEE0Node;

typedef struct BDEE0Sub1C {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ u16 unk6;
} BDEE0Sub1C;

typedef struct BDEE0Sub4 {
    /* 0x00 */ BDEE0Node *unk0;
    /* 0x04 */ u8 pad4[0x18];
    /* 0x1C */ BDEE0Sub1C *unk1C;
    /* 0x20 */ u8 pad20[0x44];
    /* 0x64 */ u16 unk64;
} BDEE0Sub4;

// Actor view whose unk178 is a s16 array (func_806B91E0, func_806BA130, func_806BA240).
typedef struct BDEE0ActorAlt {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ BDEE0Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x68];
    /* 0x070 */ s16 unk70;
    /* 0x072 */ u8 pad72[0x4E];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x2C];
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x42];
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[0x42];
    /* 0x178 */ s16 *unk178;
} BDEE0ActorAlt;

#define BDEE0AA ((BDEE0ActorAlt *)D_807FBB40)

typedef struct BDEE0View90 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ Actor *unk4;
    /* 0x08 */ u8 pad8[0xE];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 pad18[2];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u8 pad1E[0x10];
    /* 0x2E */ s16 unk2E;
} BDEE0View90;

#define BDEE0S90 ((BDEE0View90 *)D_807FDC90)

typedef struct BDEE0View98 {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ u16 unk28;
    /* 0x2A */ s16 unk2A;
} BDEE0View98;

#define BDEE0S98 ((BDEE0View98 *)D_807FDC98)

typedef struct BDEE0View9C {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
} BDEE0View9C;

#define BDEE0S9C ((BDEE0View9C *)D_807FDC9C)

extern u8 D_80770629[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void behaviourSetAnimIds(s32, s32, s32);
void func_80724CA4(s32, s32);
void actorClearNodeFlag(void *, s32);
void func_8072D714(s32, s32);
void func_8072DEA8();
void actorSetDefaultState();
void actorSetTargetSpeed(Actor *, s32);
void actorScriptStart(void *, s32);
s32 actorMoveWithinZone(u8, f32, f32, s32, f32);
void func_8072A450();
s32 randomNonNegative(void);
void actorUpdateAnimSpeedFromSpeed();
s32 func_8072E54C();
s32 func_8072DE10(u16);
void func_8072DC7C(s32);
void func_8072B7CC();
void behaviourFrameBegin(void);
void func_8072C918(s32, s32, s32);
void func_8072D13C(u32, s32);
void actorUpdateModelMatrix(Actor *, s32);
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxSpawnTableNodes(void *);
void sfxStopSlotSound(Actor *, s32);

void func_806B91E0(void) {
    u16 sp36 = 0;
    s16 *sp30 = BDEE0AA->unk178;

    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        behaviourSetAnimIds(0x321, 0x322, 0x323);
        func_80724CA4(0x11, 1);
        actorClearNodeFlag(D_807FBB40, 4);
        *sp30 = BDEE0S9C->unkA * 10;
    }
    if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
        D_807FDC90->unk2C = 0x1388;
        func_8072D714(D_807FBB70.unk1FC, 0x327);
        D_807FBB40->unk138 &= 0xFFFF7FFF;
    } else if (D_807FBB70.unk200 == 4) {
        func_8072DEA8(0x325, 0x31, D_807FBB70.unk1FC);
    } else if (D_807FBB70.unk200 == 5) {
        func_8072DEA8(0x326, 0x31, D_807FBB70.unk1FC);
    }
    switch (D_807FBB40->unk154) {
    case 0x18:
        switch (D_807FBB40->unk155[0]) {
        case 0:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                D_807FBB40->unk155[0]++;
                D_807FDC90->unk2C = 0xD;
            }
            BDEE0AA->unk4->unk1C->unk6 += 0x7D0;
            break;
        case 1:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
                break;
            }
            if (BDEE0S90->unk2E != 0) {
                D_807FBB40->unk155[0] = 0;
                BDEE0S90->unk2E--;
                D_807FDC90->unk2C = 0xA;
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1BA, 0x96, 0x7F, 0);
                break;
            }
            actorSetDefaultState(0x322);
            break;
        }
        break;
    case 0x31:
        if ((D_807FBB40->unk155[0] != 0) || (BDEE0AA->unk4->unk0->unk24 == 0.0f)) {
            actorSetDefaultState(0x322);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x11:
        switch (D_807FBB40->unk155[0]) {
        case 0:
            actorSetTargetSpeed(D_807FBB40, 0);
            actorScriptStart(D_807FBB40, 0x321);
            D_807FBB40->unk155[0]++;
        case 1:
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
            if (D_807FBB40->unkB8 < 1.0f) {
                D_807FBB40->unk155[0]++;
            }
            break;
        case 2:
            func_8072A450();
            if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x322);
            }
            break;
        }
        break;
    case 0x27:
        BDEE0AA->unk4->unk1C->unk6 -= D_807FBB40->unkB8 * 50.0f;
        actorMoveWithinZone(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0x200, 0.0f);
        switch (D_807FBB40->unk155[0]) {
        case 0:
            actorSetTargetSpeed(D_807FBB40, 0);
            actorScriptStart(D_807FBB40, 0x324);
            D_807FBB40->unk155[0] = 1;
            break;
        case 2:
            D_807FBB40->unk132 = 2;
            break;
        case 3:
            D_807FBB40->unk132 = 1;
            break;
        case 4:
            actorSetDefaultState(0x322);
            break;
        }
        break;
    case 1:
        if (func_8072E54C() != 0) {
            D_807FBB40->unk154 = 0x11;
            D_807FBB40->unk155[0] = 0;
        }
    case 0x23:
        if (D_807FBB70.unk200 == 2) {
            if (func_8072DE10(0x2710) != 0) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155[0] = 0;
            }
        }
    case 0x10:
        if ((D_807FBB40->unk154 != 0x11) && (D_807FBB40->unk154 != 0x27)) {
            if (D_807FBB40->unk155[0] == 0) {
                *sp30 = BDEE0S9C->unkA * 2;
                D_807FBB40->unk155[0] = 1;
            }
            if (*sp30 != 0) {
                (*sp30)--;
            } else {
                sp36 = 0x20;
                actorUpdateAnimSpeedFromSpeed(0);
                if (D_807FBB40->unkB8 != 0.0f) {
                    D_807FBB40->unkB8 = D_807FBB40->unkB8 - 1.0f;
                } else {
                    D_807FBB40->unk154 = 0x18;
                    D_807FBB40->unk155[0] = 0;
                    D_807FBB40->unk155[0] = 1;
                    D_807FDC90->unk2C = 0;
                    BDEE0S90->unk2E = 4;
                }
            }
        }
        BDEE0AA->unk4->unk1C->unk6 -= D_807FBB40->unkB8 * 50.0f;
        actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, sp36, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        actorMoveWithinZone(D_807FBB40->unk154, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, 0, 0.0f);
        break;
    case 0x37:
        BDEE0AA->unk4->unk1C->unk6 -= D_807FDC90->unk2C;
        if (D_807FDC90->unk2C != 0) {
            D_807FDC90->unk2C -= 0x32;
        }
        switch (D_807FBB40->unk155[0]) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(D_807FBB40);
            D_807FBB40->unk155[0]++;
        case 2:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            func_8072DC7C(8);
            break;
        case 3:
            D_807FBB40->unk154 = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        func_8072B7CC(0x322);
        break;
    }
    if (D_807FBB40->unkB8 != 0.0f) {
        if (BDEE0AA->unk70 == -1) {
            sfxPlayActorSound(D_807FBB40, 0x10A, 0, 1, 1, 0xFF, 1.0f, 0);
        } else {
            f64 t = ((f64)D_807FBB40->unkB8 * 0.6) / 40.0;
            u8 idx = D_80770629[BDEE0AA->unk70 * 2];

            D_80770B68[idx] = (t < 0.0 ? 0.0 : t) + 0.4;
            D_80770BC0[idx] = 1.0f;
        }
    } else {
        sfxStopSlotSound(D_807FBB40, 1);
    }
    switch (D_807FBB40->unk154) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        func_8072D13C(D_807FBB40->unk154, 1);
    default:
        func_8072C918(0x57E4, 0x322, 0x323);
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}


void func_806B9CB0(void) {
    behaviourFrameBegin();
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_80714950(s32);
void func_8071498C(void *);
void func_807149B8(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_8071720C(void);
void func_80717D4C(void);
extern void *D_8074E880[];

void actorSpawnRandomParticleNearActor(u8 arg0, s8 arg1) {
    s32 pad;
    s32 sp28;
    s32 sp24;
    s32 sp20;

    switch (arg0) {
        case 0:
            func_8071498C(func_8071720C);
            break;
        case 1:
            func_80714950(-0x258);
            func_8071498C(func_80717D4C);
            break;
    }
    func_807149B8(1);
    sp20 = randomNonNegative();
    sp24 = randomNonNegative();
    sp28 = randomNonNegative();
    func_80714CC0(D_8074E880[((sp20 >> 15) % 1000) % 3], (f32)(((sp24 >> 15) % 256) * 0.001953125 + 0.5), (f32)((sp28 >> 15) % 6) + (D_807FBB40->unk7C - 3.0f), D_807FBB40->unk80 + (f32)arg1, (f32)((randomNonNegative() >> 15) % 6) + (D_807FBB40->unk84 - 3.0f));
}

extern u8 D_80750628[];
typedef struct BDEE0DCA0 {
    u8 pad0[0x1C];
    s32 unk1C;
    u8 unk20;
} BDEE0DCA0;

extern BDEE0DCA0 *D_807FDCA0;
s32 actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_80611A70(f32, f32, f32 *, f32 *);
f32 func_80611BB4(f32, f32);
void matrixMakeRotationX(f32 (*)[4], f32);
void matrixMakeRotationY(f32 (*)[4], f32);

s32 actorBuildNodeAlignedMatrix(u8 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 spA[4][4];
    f32 spB[4][4];
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    u8 node;

    node = D_80750628[arg0];
    if (node) {
        f32 ang;

        actorGetNodePos(*(Actor **)&D_807FDCA0->unk1C, node, &sp3C, &sp38, &sp34);
        func_80611A70(arg2, arg4, &sp3C, &sp34);
        ang = func_80611BB4(sp3C - arg2, sp34 - arg4);
        guTranslateF(spA, 0.0f, -arg1, 0.0f);
        matrixMakeRotationY(spB, (D_807FBB40->unkE6 * 0x168) / 4096);
        guMtxCatF(spA, spB, spA);
        matrixMakeRotationX(spB, -90.0f);
        guMtxCatF(spA, spB, spA);
        guAlignF(spB, (ang * 57.295776f) + 180.0f, sp3C - arg2, sp38 - arg3, sp34 - arg4);
        guMtxCatF(spA, spB, spA);
        guTranslateF(spB, 0.0f, arg1, 0.0f);
        guMtxCatF(spA, spB, spA);
        guScaleF(spB, D_807FBB40->unk4->unk34, D_807FBB40->unk4->unk38, D_807FBB40->unk4->unk3C);
        guMtxCatF(spA, spB, spA);
        guTranslateF(spB, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        guMtxCatF(spA, spB, (f32 (*)[4])((u8 *)D_807FBB40 + 0xC));
        return 1;
    }
    return 0;
}


void func_806BA130(void) {
    D_807FBB40->unk5C = 2;
    D_807FBB40->unk154 = 0x23;
    D_807FBB40->unk155[0] = 0;
    BDEE0AA->unk134 = 1;
    D_807FBB40->unk132 = 1;
    BDEE0S90->unk4 = D_807FBB4C;
    actorScriptStart(D_807FBB40, BDEE0S98->unk2A);
    D_807FBB40->unkE6 = ((randomNonNegative() >> 15) % 1024) + D_807FBB4C->unkE6 - 0x200;
    D_807FBB40->unkB8 = ((randomNonNegative() >> 15) % 100) + 0x32;
    BDEE0AA->unkC0 = ((randomNonNegative() >> 15) % 150) + 0x64;
}

typedef struct BDEE0DC924 {
    u8 pad0[0x2C0];
    u8 unk2C0;
} BDEE0DC924;

extern BDEE0DC924 *D_807FC924;
s32 func_806BA240(u8, s16);

typedef struct BDEE0DCA0Tgt {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ Actor *unk1C;
    /* 0x20 */ u8 unk20;
} BDEE0DCA0Tgt;

#define BDEE0DCA0T ((BDEE0DCA0Tgt *)D_807FDCA0)

extern u8 D_8071FB34[];
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_80613C48(void *, s16, f32, f32);
s32 playerStateQueueCallback(s32, void *, s32);
s32 func_8072DCF4(void *, void *, s32);

s32 func_806BA240(u8 arg0, s16 arg1) {
    s16 *p;
    Actor *tgt;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    u8 node;
    s32 var;

    p = BDEE0AA->unk178;
    tgt = BDEE0DCA0T->unk1C;
    if (tgt != NULL && tgt->unk154 == 0x23 && BDEE0DCA0T->unk20 < 10) {
        if (D_807FBB40->unk154 != 0x15 && D_807FBB40->unk154 != 0x17) {
            D_807FBB40->unk5C = 0x80;
            D_807FBB40->unk154 = 0x15;
            D_807FBB40->unk155[0] = 0;
            actorScriptStart(D_807FBB40, 0);
            D_807FBB40->unk132 = 2;
            p[3] = D_807FBB40->unk7C;
            p[4] = D_807FBB40->unk84;
        }
    }
    if (D_807FBB40->unk154 == 0x15 && (tgt == NULL || tgt->unk154 != 0x23)) {
        func_806BA130();
    }
    if (D_807FBB40->unk154 == 0x15) {
        node = D_807FDC9C->unkA;
        if (node == 5 || node == 7) {
            if ((((BDEE0Sub4 *)tgt->unk4)->unk64 == 0x21E || ((BDEE0Sub4 *)tgt->unk4)->unk64 == 0x21F) && ((BDEE0Sub4 *)tgt->unk4)->unk0->unk4 >= 4.0f && ((BDEE0Sub4 *)tgt->unk4)->unk0->unk4 <= 12.0f) {
                D_807FBB40->unk132 = 4;
            } else {
                D_807FBB40->unk132 = 2;
            }
        }
        if (node == 1) {
            D_807FBB40->unk132 = 8;
        }
        if (BDEE0AA->unkF0 != 0) {
            BDEE0AA->unkF0 = BDEE0AA->unkF0 - 1;
        }
        if (tgt->unk155[0] != 0) {
            if (tgt->unk155[0] == 1 && D_807FBD70 == 2 && func_8072DCF4(tgt, D_807FBB4C, 0x1F40) != 0) {
                if (D_807FC924->unk2C0 == 1) {
                    playerStateQueueCallback(0x32, D_807FBB40, 0);
                } else {
                    if (((randomNonNegative() >> 15) % 1000) >= 0x1F5) {
                        var = 0x21F;
                    } else {
                        var = 0x21E;
                    }
                    actorScriptStart(tgt, var);
                    tgt->unk155[0] = 2;
                }
            } else if (D_807FBD70 == 4) {
                BDEE0S90->unk16 = ((BDEE0Sub4 *)D_807FDC94->unk4)->unk0->unk10;
                D_807FBB40->unk60 |= 0x20000000;
                if (BDEE0AA->unkF0 == 0) {
                    BDEE0AA->unkF0 = 0x28;
                    func_80714CC0(D_8071FB34, 2.0f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
                    func_80609140(0x1CA, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    actorScriptStart(tgt, 0x220);
                    tgt->unk155[0] = 2;
                    ((BDEE0ActorAlt *)tgt)->unk134 = ((BDEE0ActorAlt *)tgt)->unk134 - 1;
                    if (((BDEE0ActorAlt *)tgt)->unk134 == 0) {
                        tgt->unk154 = 0x37;
                        tgt->unk155[0] = 0;
                    }
                }
            }
        }
        BDEE0DCA0T->unk20 = BDEE0DCA0T->unk20 + 1;
        actorGetNodePos(tgt, node, &sp4C, &sp48, &sp44);
        if (BDEE0S90->unk1A & 0x80) {
            if (!(BDEE0S90->unk1C & 0x80)) {
                BDEE0AA->unkC0 = 300.0f;
            }
            if (BDEE0AA->unkC0 > 0.0f) {
                return 0;
            }
            D_807FBB40->unk144 = 0x24;
            if (arg1 != 0) {
                func_80613C48(D_807FBB40, arg1, 0.0f, 4.0f);
            }
            p[0] = (-p[0]) * 0.1 + p[0];
            p[1] = (-p[1]) * 0.1 + p[1];
            if (node < 0xB) {
                D_807FBB40->unkE6 = tgt->unkE6;
            }
            D_807FBB40->unk7C = sp4C;
            D_807FBB40->unk84 = sp44;
            D_807FBB40->unk80 = sp48;
            if (actorBuildNodeAlignedMatrix(node, arg0, sp4C, sp48, sp44) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

void func_8072B7CC(s32);

void func_806BA76C(f32 arg0) {
    s16 *p;
    f32 x;
    f32 z;
    u8 sel;
    s32 flags;

    sel = D_807FBB40->unk154;
    p = BDEE0AA->unk178;
    x = D_807FDC90->unkA;
    z = D_807FDC90->unkE;
    switch (sel) {
        case 1:
        case 0x10:
        case 0x15:
        case 0x23:
            x = D_807FDC94->unk7C;
            z = D_807FDC94->unk84;
        case 2:
        case 3:
        case 7:
        case 0x35:
            if (D_807FBB40->unkFC != 0) {
                flags = 0x10;
            } else {
                flags = 0x810;
            }
            if (!(actorMoveWithinZone(sel, x, z, flags & 0xFFFF, 0.0f) & 1) && D_807FBB40->unkFC == 0) {
                *p = *p + arg0;
            }
            break;
        case 0x37:
            switch (D_807FBB40->unk155[0]) {
                case 2:
                    func_8072DC7C(10);
                    break;
                case 3:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        case 4:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x12, 0.0f);
            break;
        default:
            func_8072B7CC(0);
            break;
    }
}


void func_806BA8C8(void) {
    u8 arg = D_807FBB40->unk154;
    s32 sel = arg;

    switch (sel) {
        case 0x15:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            func_8072D13C(arg, 0);
        default:
            func_8072C918(0x2710, 0, 0);
    }
}

typedef struct BDEE0Sub178 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u16 unk4;
} BDEE0Sub178;

// Actor view whose unk178 is a BDEE0Sub178 (func_806BA93C, func_806BB874).
typedef struct BDEE0Actor {
    /* 0x000 */ u8 pad0[0xC];
    /* 0x00C */ f32 unkC[4][4];
    /* 0x04C */ u8 pad4C[0xE4];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[0x22];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ BDEE0Sub178 *unk178;
} BDEE0Actor;
#define BDEE0A ((BDEE0Actor *)D_807FBB40)

void func_806BA76C(f32);
void func_806BA8C8(void);
f32 cosApprox(f32);
f32 func_80612790(s16);
f32 func_80612794(s16);
s32 func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void matrixMakeRotationZ(f32 (*)[4], f32);
s16 func_806CC190(s16, s16, f32);

void func_806BA93C(arg0, arg1, arg2)
u8 arg0;
u8 arg1;
u8 arg2;
{
    BDEE0Sub178 *s1;
    f32 spA4[4][4];
    f32 sp64[4][4];
    s16 sgn;
    s32 dir;
    f32 sp58;
    s16 a;

    s1 = BDEE0A->unk178;
    if (D_807FDC9C->unkA && func_806BA240(0x64, 0)) {
        return;
    }
    {
        if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1CA, 0xFF, 0x7F, 0x32);
            func_8072D714(D_807FBB70.unk1FC, 0);
            D_807FDC90->unk2C = 0xA6;
            s1->unk4 = 0x32;
        }
        func_806BA76C(D_807FBB40->unkB8 * 5.0f);
        switch (D_807FBB40->unk154) {
        case 4:
            s1->unk0 = s1->unk0 + (-s1->unk0) * 0.3;
            break;
        case 0x37:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x12, 0.0f);
            if (BDEE0A->unk155 == 0) {
                D_807FDC90->unk2C += s1->unk4;
                if (D_807FDC90->unk2C == 0x196 || D_807FDC90->unk2C == 0x244 || D_807FDC90->unk2C == 0x307 || D_807FDC90->unk2C == 0x3B1 || D_807FDC90->unk2C == 0x45C || D_807FDC90->unk2C == 0x508) {
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x17D, 0x9B, (s16)(s1->unk4 + 0x5A), 0);
                }
                s1->unk4--;
                if (s1->unk4 < 2) {
                    BDEE0A->unk155++;
                    dir = s1->unk4;
                    s1->unk4 = 0;
                    D_807FDC90->unk30 = 0.0f;
                }
            }
            break;
        }
        if (s1->unk0 >= 0x801) {
            sp58 = sqrtf((1.0 - cosApprox(0.7853982f)) * (2 * (f32)(arg0 * 2) * (f32)(arg0 * 2)));
            if (s1->unk2) {
                dir = 1;
            } else {
                dir = -1;
            }
            s1->unk0 -= 0x800;
            s1->unk2 ^= 1;
            a = dir << 8;
            D_807FBB40->unk7C += D_807FBB40->unk4->unk38 * sp58 * func_80612794(D_807FBB40->unkE6 + a);
            D_807FBB40->unk84 += D_807FBB40->unk4->unk38 * sp58 * func_80612790(D_807FBB40->unkE6 + a);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x1B1, 0xFF, 0x7F, 0xA, 0x3C, 0.3f, 0);
        }
        func_806BA8C8();
        if (s1->unk2) {
            sgn = -1;
        } else {
            sgn = 1;
        }
        guTranslateF(spA4, sgn * arg0, 0.0f, 0.0f);
        matrixMakeRotationZ(sp64, func_80612794(s1->unk0) * (f32)(sgn * arg1));
        guMtxCatF(spA4, sp64, spA4);
        if (D_807FBB40->unk154 == 0x37) {
            matrixMakeRotationY(sp64, (f32)(sgn * D_807FDC90->unk2C));
        } else {
            matrixMakeRotationY(sp64, func_80612794(s1->unk0 - 0x400) * (f32)(-sgn * 0x2D));
        }
        guMtxCatF(spA4, sp64, spA4);
        if (D_807FBB40->unk154 == 0x37) {
            switch (BDEE0A->unk155) {
            case 1:
                D_807FDC90->unk2C = func_806CC190((D_807FDC90->unk2C << 12) / 0x168, 0, 3.0f) * 0x168 / 4096;
                s1->unk0 = s1->unk0 + (-s1->unk0) * 0.3;
                guTranslateF(sp64, 0.0f, 0.0f, (f32)-arg2);
                guMtxCatF(spA4, sp64, spA4);
                matrixMakeRotationX(sp64, (f32)s1->unk4);
                guMtxCatF(spA4, sp64, spA4);
                guTranslateF(sp64, 0.0f, 0.0f, (f32)arg2);
                D_807FDC90->unk30 += 2.0f;
                s1->unk4 = (f32)s1->unk4 + D_807FDC90->unk30;
                if (s1->unk4 >= 0x5B) {
                    s1->unk4 = 0x5A;
                    if (D_807FDC90->unk30 < 3.0f) {
                        BDEE0A->unk155++;
                    } else {
                        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x1B1, (u32)(D_807FDC90->unk30 * 255.0f / 20.0f), (s32)(D_807FDC90->unk30 + 100.0f), 0, 0x3C, 0.3f, 0);
                        D_807FDC90->unk30 = -(D_807FDC90->unk30 * 0.5);
                    }
                }
                break;
            case 2:
                guTranslateF(sp64, 0.0f, 0.0f, (f32)-arg2);
                guMtxCatF(spA4, sp64, spA4);
                matrixMakeRotationX(sp64, 90.0f);
                guMtxCatF(spA4, sp64, spA4);
                guTranslateF(sp64, 0.0f, 0.0f, (f32)arg2);
                break;
            }
            guMtxCatF(spA4, sp64, spA4);
        }
        guTranslateF(sp64, (f32)(-sgn * arg0), 0.0f, 0.0f);
        guMtxCatF(spA4, sp64, BDEE0A->unkC);
        actorUpdateModelMatrix(D_807FBB40, 1);
    }
}

void func_806BB32C(void) {
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk16A = 0xFA;
        D_807FBB40->unk16B = 0xFA;
        D_807FBB40->unk16C = 0xFA;
    }
    if (D_807FBB40->unk154 == 0x17) {
        actorSpawnRandomParticleNearActor(0, 0);
    }
    if (BDEE0S90->unk2E != 0) {
        BDEE0S90->unk2E--;
        D_807FBB40->unkFC = 0;
        if (BDEE0S90->unk2E == 0 && D_807FDC94 == D_807FBB4C) {
            D_807FBB40->unk144 = 0x24;
        }
    }
}

void func_806D0430(f32);
void actorSetUniformScale(Actor *, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_806BB400(void) {
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_806D0430(0.525f);
        D_807FBB4C->unk60 |= 0x400;
        D_807FBB4C->unk12A = 0x7D0;
        D_807FBB40->unk60 &= ~4;
        actorSetUniformScale(D_807FBB40, 1.0f);
        D_807FBB40->unk15F = 0;
        D_807FBB40->unkE6 = mathAngleBetweenPoints2D(D_807FBB4C->unk7C, D_807FBB4C->unk84, D_807FBB40->unk7C, D_807FBB40->unk84);
        actorScriptStart(D_807FBB40, 0x21B);
        D_807FDC98->unk46 |= 8;
        ((BDEE0View98 *)D_807FDC98)->unk28 = 0x21C;
    }
    switch (D_807FBB40->unk154) {
        case 4:
            D_807FBB40->unk154 = 0x23;
            D_807FBB40->unk155[0] = 0;
        case 0x23:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
                    break;
                default:
                    D_807FBB40->unk155[0] = 1;
                    goto join;
                join:
                case 1:
                    if (((BDEE0Sub4 *)D_807FBB40->unk4)->unk64 != 0x21C) {
                        actorScriptStart(D_807FBB40, 0x21C);
                    }
                    actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
                    break;
                case 2:
                    break;
            }
            break;
        case 0x37:
            func_806D0430(0.3f);
            D_807FBB40->unk154 = 0x40;
            break;
    }
    D_807FDCA0->unk20 = 0;
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct BDEE0Sub174 {
    /* 0x00 */ struct BDEE0Sub174Hdr *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[0x26];
    /* 0x2E */ s16 unk2E;
} BDEE0Sub174;

typedef struct BDEE0Sub174Hdr {
    /* 0x00 */ u8 pad0[0x46];
    /* 0x46 */ u16 unk46;
} BDEE0Sub174Hdr;

extern Actor *D_807FBB44;

s32 spawnNodeSpawnById(u8, s16, s16, s16, s32, s32, s32);

s32 actorSpawnJitteredChild(u8 arg0, s16 arg1, s16 arg2, s32 arg3) {
    BDEE0Sub174 *v;
    s32 r3;
    s32 r2;
    s32 r1;

    if (D_807FDC90->unk2C != 0) {
        actorSpawnRandomParticleNearActor(0, 0xA);
        D_807FDC90->unk2C--;
        return 0;
    }
    r1 = randomNonNegative();
    r2 = randomNonNegative();
    r3 = randomNonNegative();
    if (spawnNodeSpawnById(arg0,
                      (s16)((f32)((r1 >> 15) % 10) + (D_807FBB40->unk7C - 5.0f)),
                      (s16)(D_807FBB40->unk80 + 5.0f),
                      (s16)((f32)((r2 >> 15) % 10) + (D_807FBB40->unk84 - 5.0f)),
                      ((r3 >> 15) % 1024) + D_807FBB40->unkE6 - 0x200,
                      arg1, arg2) != 0) {
        D_807FBB44->unk154 = 0x17;
        D_807FBB44->unk155[0] = 0;
        v = D_807FBB44->unk174;
        v->unk2E = 0x1E;
        if (arg3 != 0) {
            v->unk0->unk46 &= ~8;
            v->unk4 = arg3;
        }
        D_807FBB44->unk144 = 1;
        D_807FBB44->unk12A = 0x3E8;
        return 1;
    }
    return 0;
}

void sfxAllocateChannel(s32, f32);

void func_806BB81C(void) {
    sfxPlayActorSound(D_807FBB40, 0x11F, 0, 0, 0, 0xFF, 1.0f, 0);
    sfxAllocateChannel(0x3B, 1.0f);
}

typedef struct BDEE0Tbl {
    u8 b[11];
} BDEE0Tbl;

typedef struct BDEE0DD580 {
    u8 pad0[0x1D8];
    f32 unk1D8;
} BDEE0DD580;

extern BDEE0DD580 *D_807FD580;
extern s32 D_807FBB68;
extern s32 gCamActor;
extern BDEE0Tbl D_80750638;

void func_806BB81C();
s32 spawnNodeHasActor(s32);
void func_80641874(s32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void camStartPath(void *, s32, s32);
void camSetTarget(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void camSetTargetFocusActor(s32, void *);
void camReturnToFollow(s32, void *);
void func_80726EE0(s32);
void func_806D0468(void *, s32);
void csModelStateSetFirstByte(s32, s32);
void func_80686F90(s32, s16, s16);
void sfxStopChannel();

void func_806BB874(void) {
    s16 i;
    s16 x;
    s16 y;
    BDEE0Tbl tbl;
    u8 t;
    s32 w;

    x = (randomNonNegative() >> 15) % 100 + 0x64;
    y = (randomNonNegative() >> 15) % 250 + 0xC8;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        BDEE0A->unk130 = 0x3C;
        BDEE0A->unk131 = 0x3C;
        D_807FBB40->unk12A = 0x3E8;
        D_807FBB40->unk154 = 0;
        BDEE0A->unk155 = 0;
        actorScriptStart(D_807FBB40, 0x3DC);
        D_807FDC90->unk2C = 0x78;
        D_807FBB40->unk64 |= 0x20;
    }
    switch (D_807FBB40->unk154) {
    case 0: {
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 3) {
                D_807FBB40->unk154++;
            }
        }
        break;
    }
    case 1:
        switch (BDEE0A->unk155) {
        case 0:
            if (D_807FDC90->unk2C-- < 0x3C) {
                D_807FBB40->unk60 |= 0x400;
                actorScriptStart(D_807FBB40, 0x3DD);
                BDEE0A->unk155++;
            }
            break;
        case 2:
            func_80686F90(0, (randomNonNegative() >> 15) % 2048 + D_807FBB40->unkE6 - 0x400, (randomNonNegative() >> 15) % 1024);
            break;
        case 3:
            D_807FBB68 |= 1;
            sfxAllocateChannel(0x68, 1.0f);
            D_807FDC90->unk2C = 0x32;
            func_806BB81C();
            D_807FBB40->unk154++;
            break;
        }
        break;
    case 2:
        if (actorSpawnJitteredChild(0x2A, x, y, 0) != 0) {
            D_807FBB40->unk154++;
        }
        break;
    case 3:
        if (spawnNodeHasActor(0x2A) == 0) {
            D_807FDC90->unk2C = 0xA;
            D_807FBB40->unk154++;
        }
        break;
    case 4:
        func_806BB81C();
        actorSpawnJitteredChild(0x28, x, y, 0);
        if (actorSpawnJitteredChild(0x29, (s16)(x + 0x28), (s16)(y + 0x50), 0) != 0) {
            D_807FBB40->unk154++;
        }
        break;
    case 5:
        if (spawnNodeHasActor(0x28) == 0 && spawnNodeHasActor(0x29) == 0) {
            D_807FDC90->unk2C = 0xA;
            D_807FBB40->unk154++;
        }
        break;
    case 6:
        func_806BB81C();
        actorSpawnJitteredChild(0x2B, x, y, 0);
        if (actorSpawnJitteredChild(0x2C, (s16)(x + 0x28), (s16)(y + 0x50), 0) != 0) {
            D_807FBB40->unk154++;
        }
        break;
    case 7:
        if (spawnNodeHasActor(0x2B) == 0 && spawnNodeHasActor(0x2C) == 0) {
            func_80641874(0x11, 1);
            spawnNodeSpawnById(0x2D, func_80612794(D_807FBB40->unkE6) * 80.0f + D_807FBB40->unk7C, D_807FBB40->unk80, func_80612790(D_807FBB40->unkE6) * 80.0f + D_807FBB40->unk84, D_807FBB40->unkE6, 0, 0);
            D_807FDCA0->unk1C = (s32)D_807FBB44;
            camStartPath(D_807FBB40, 0x1F, 1);
            D_807FBB40->unk154++;
            D_807FDC90->unk2C = 0x1E;
            BDEE0A->unk155 = 0xA;
        }
        break;
    case 8:
        if (D_807FDC90->unk2C != 0) {
            D_807FDC90->unk2C--;
        } else {
            tbl = D_80750638;
            t = 0xA - BDEE0A->unk155;
            if (BDEE0A->unk155 == 0xA) {
                func_806BB81C();
            }
            if (BDEE0A->unk155) {
                actorSpawnJitteredChild((u8)(tbl.b[BDEE0A->unk155--] + 0x22), (s16)(t * 8 + 0x64), (s16)(t * 20 + 0xFA), D_807FDCA0->unk1C);
            } else {
                D_807FBB40->unk60 &= 0xFFFF7FFF;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk154++;
                camSetTarget(gCamActor, D_807FBB40, 4, 0x1129, 0x264, 0, 0, 0xAF, 0, 0, 1.0f);
                camSetTargetFocusActor(gCamActor, D_807FBB4C);
            }
            D_807FDC90->unk2C = 0xF;
        }
        break;
    case 9: {
        w = D_807FBB40->unk128 - 0xA;
        if (w < 0) {
            D_807FBB40->unk128 = 0;
        } else {
            D_807FBB40->unk128 = w;
        }
        if (spawnNodeHasActor(0x2D) == 0) {
            func_80641874(0x11, 0xFF);
            camReturnToFollow(gCamActor, D_807FBB4C);
            func_80726EE0(0);
            D_807FBB68 &= ~1;
            if (D_807FC924->unk2C0 != 1) {
                func_806D0468(D_807FBB4C, 1);
                D_807FD580->unk1D8 = 0.05f;
            }
            D_807FBB40->unk154++;
            sfxStopChannel(0x68, 0);
            csModelStateSetFirstByte(0x7C, 0xA);
            D_807FBB4C->unk12A = 0x1F4;
            D_807FBB4C->unk60 &= ~0x400;
            D_807FBB40->unk144 = 0x24;
            camStartPath(D_807FBB40, 0x1F, 5);
        }
        break;
    }
    case 10: {
        w = D_807FBB40->unk128 + 0xA;
        if (w >= 0x100) {
            D_807FBB40->unk128 = 0xFF;
        } else {
            D_807FBB40->unk128 = w;
        }
        break;
    }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_806AD260();

void func_806BC080(void) {
    func_806BB32C();
    if (D_807FDC9C->unkA == 0 || func_806BA240(0, 0x446) == 0) {
        func_806AD260(0x2ED, 1, 0);
        actorUpdateModelMatrix(D_807FBB40, 0);
    }
}

void func_806BC0E4(void) {
    func_806BB32C();
    if (D_807FDC9C->unkA == 0 || func_806BA240(0x32, 0x44E) == 0) {
        func_806AD260(0x2EC, 1, 0);
        actorUpdateModelMatrix(D_807FBB40, 0);
    }
}

void func_806BC148(void) {
    func_806BB32C();
    if (D_807FDC9C->unkA == 0 || func_806BA240(0x14, 0x44A) == 0) {
        func_806AD260(0x2EE, 1, 0);
        actorUpdateModelMatrix(D_807FBB40, 0);
    }
}

void func_806BA93C();

void func_806BC1AC(void) {
    func_806BB32C();
    func_806BA93C(0x24, 0x14, 0x1E);
}
