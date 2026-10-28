#include "common.h"

typedef struct BossD_Actor {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
    u8 padF0[0x144 - 0xF0];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 pad155[0x160 - 0x155];
    f64 unk160;
} BossD_Actor;

typedef struct BossD_Sub178 {
    u8 pad0[0x14];
    u8 unk14;
} BossD_Sub178;

typedef struct BossD_D580 {
    u8 pad0[0x1D8];
    f32 unk1D8;
    u8 pad1DC[0x1F4 - 0x1DC];
    s32 unk1F4;
    u8 pad1F8[0x1FE - 0x1F8];
    s16 unk1FE;
} BossD_D580;

typedef struct BossD_DC90 {
    u8 pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 pad10[0x1A - 0x10];
    u16 unk1A;
} BossD_DC90;

extern BossD_Actor *D_807FBB40;
extern BossD_Actor *D_807FBB4C;
extern BossD_D580 *D_807FD580;
extern BossD_DC90 *D_807FDC90;
extern void *gCamActor;

void func_800290D4(s32);
s32 playerStateQueueCallback(s32, void *, s32);
void zoneEntryGetPosition(s32, s32, void *, void *, void *);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void actorScriptStart(void *, s32);
s32 camIsCutsceneActive(void);
void camEndPath(void *);
void camSetTarget(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_806CFF9C(void *);
void camReturnToFollow(void *, void *);
void func_8063DA40(s32, s16);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_80030920(s32 arg0) {
    s16 temp_t7;

    D_807FD580->unk1FE = 1;
    func_800290D4(1);
    D_807FBB40->unk144 = 0x24;
    playerStateQueueCallback(0x19, D_807FBB40, 0);
    zoneEntryGetPosition(1, 8, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
    D_807FDC90->unkA = D_807FBB40->unk7C;
    D_807FDC90->unkC = D_807FBB40->unk80;
    D_807FDC90->unkE = D_807FBB40->unk84;
    zoneEntryGetPosition(1, 0x20, &D_807FBB4C->unk7C, &D_807FBB4C->unk80, &D_807FBB4C->unk84);
    D_807FBB4C->unkE6 = mathAngleBetweenPoints2D(D_807FBB40->unk7C, D_807FBB40->unk84, D_807FBB4C->unk7C, D_807FBB4C->unk84);
    temp_t7 = D_807FBB4C->unkE6 + 0x800;
    D_807FBB40->unkE6 = temp_t7;
    D_807FBB40->unkEE = temp_t7;
    actorScriptStart(D_807FBB40, 0x3F9);
    if (camIsCutsceneActive() != 0) {
        camEndPath(gCamActor);
    }
    camSetTarget(gCamActor, D_807FBB4C, 4, 0x800, 0x5A, 0, 0x46, 0x64, 0x3A, 0, 0.3f);
}
void func_80030AE0(BossD_Sub178 *arg0) {
    func_800290D4(0);
    D_807FD580->unk1F4 = 0;
    if (D_807FBB4C->unk154 != 0x36) {
        func_806CFF9C(D_807FBB4C);
    }
    camReturnToFollow(gCamActor, D_807FBB4C);
    D_807FD580->unk1D8 = 0.01f;
    func_8063DA40(0xB, (arg0->unk14 <= 0) ? 0 : 4);
    func_8063DA40(0xC, (arg0->unk14 < 2) ? 0 : 4);
    func_8063DA40(0xD, (arg0->unk14 < 3) ? 0 : 4);
    func_8063DA40(0xE, (arg0->unk14 < 4) ? 0 : 4);
    func_8063DA40(0xA, 0xA);
}

void func_80030C30(f32 arg0) {
    D_807FBB40->unk7C = (f32) (((f64) (D_807FBB4C->unk7C - (f32) D_807FDC90->unkA) * D_807FBB40->unk160) + (f64) D_807FDC90->unkA);
    D_807FBB40->unk80 = (f32) (((f64) (D_807FBB4C->unk80 - (f32) D_807FDC90->unkC) * D_807FBB40->unk160) + (f64) D_807FDC90->unkC);
    D_807FBB40->unk84 = (f32) (((f64) (D_807FBB4C->unk84 - (f32) D_807FDC90->unkE) * D_807FBB40->unk160) + (f64) D_807FDC90->unkE);
    D_807FBB40->unk160 += arg0;
    if (D_807FBB40->unk160 > 0.8) {
        D_807FBB40->unk160 = 0.8;
    }
}

void func_80030D50(void) {
    s32 pad[1];
    f32 sp20;
    sp20 = func_80612794((s16) (s32) (D_807FBB40->unk160 * 10240.0));
    D_807FBB40->unk7C += (80.0f * func_80612794(D_807FBB40->unkE6 + 0x400)) * sp20;
    sp20 = func_80612794((s16) (s32) (D_807FBB40->unk160 * 10240.0));
    D_807FBB40->unk84 += (80.0f * func_80612790(D_807FBB40->unkE6 + 0x400)) * sp20;
}

void func_80030E58(void) {
    D_807FDC90->unk1A |= 1;
    func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x2E2, 0xFF, 0x65, 0, 0, 0.0f, 0);
}

typedef struct BsB2_Sub178 {
    u8 pad0[0x14];
    u8 unk14;
    u8 unk15;
    u8 unk16;
} BsB2_Sub178;

typedef struct BsB2_Actor {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xCC - 0xBC];
    u8 unkCC;
    u8 padCD[0xE6 - 0xCD];
    s16 unkE6;
    u8 padE8[0xEC - 0xE8];
    s16 unkEC;
    s16 unkEE;
    u8 padF0[0x110 - 0xF0];
    u8 unk110;
    u8 pad111[0x128 - 0x111];
    s16 unk128;
    u8 pad12A[0x132 - 0x12A];
    s16 unk132;
    u8 pad134[0x144 - 0x134];
    u8 unk144;
    u8 pad145[1];
    s16 unk146;
    u8 pad148[0x154 - 0x148];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x160 - 0x156];
    f64 unk160;
    u8 pad168[0x178 - 0x168];
    BsB2_Sub178 *unk178;
} BsB2_Actor;

typedef struct BsB2_DC90 {
    u8 pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 pad10[0x1A - 0x10];
    u16 unk1A;
    u8 pad1C[0x25 - 0x1C];
    u8 unk25;
} BsB2_DC90;

typedef struct BsB2_D580 {
    u8 pad0[0xD4];
    s16 unkD4;
    u8 padD6[0x1F0 - 0xD6];
    s32 unk1F0;
} BsB2_D580;

typedef struct BsB2_C924 {
    u8 pad0[0x2C0];
    u8 unk2C0;
} BsB2_C924;

typedef struct BsB2_DC98 {
    u8 pad0[0x20];
    u8 (*unk20)[2];
} BsB2_DC98;

typedef struct BsB2_DC9C {
    u8 pad0[0xC];
    u8 unkC;
} BsB2_DC9C;

extern u8 *D_80035AC0[];
extern u8 D_80035ACF[];
extern f32 D_80035AD4[];
extern f32 D_80035AE4[];
extern u8 D_807FBD70;
extern BsB2_C924 *D_807FC924;
extern BsB2_DC98 *D_807FDC98;
extern BsB2_DC9C *D_807FDC9C;

void behaviourFrameBegin(void);
void func_80028878(u8 *);
void camSetSecondTarget(void *, s32, s32);
void func_80724CA4(s32, s32);
void func_806D0430(f32);
void flagSet(s32, s32, s32);
void camStartPath(void *, s32, u8);
void func_80641874(s32, s32);
void actorSetTargetSpeed(void *, s32);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void func_80614D00(void *, f32, f32);
void func_806D0468(void *, s32);
s32 func_806C9974(s32, s32);
void func_80614E78(void *, s32);
void func_8072CFE8(s16 *, s16 *, s16 *);
void actorSetGroupState(u8, s32);
s16 func_806CC10C(s16, s16);
s16 func_806CC190(s16, s16, f32);
s32 currentActorTestClearFlag(void);
s32 func_80027BA8(u8 *, s32, f32);
void billboardSetFlags(s32);
void func_8065D254(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 func_8072881C(s32, void *);
void actorUpdateModelMatrix(void *, s32);

#define BsBA ((BsB2_Actor *)D_807FBB40)
#define BsBP ((BsB2_Actor *)D_807FBB4C)
#define BsBS ((BsB2_DC90 *)D_807FDC90)
#define BsBD ((BsB2_D580 *)D_807FD580)

void func_80030EC4(void) {
    BsB2_Sub178 *sp178;
    u8 *sp28;
    s16 sp50[3];

    sp178 = BsBA->unk178;
    sp28 = D_80035AC0[sp178->unk14];
    behaviourFrameBegin();
    func_80028878(sp28);
    if (!(BsBA->unk60 & 0x10)) {
        camSetSecondTarget(gCamActor, 0, 0);
        BsBA->unk146 = 5;
        BsBA->unk154 = 0x1E;
        BsBA->unk155 = 0;
        BsBA->unkCC = 0;
        func_80724CA4(2, 1);
        BsBA->unk110 = 0;
        BsBA->unk60 &= ~0x8000;
        func_806D0430(0.45f);
        func_800290D4(0);
        flagSet(0x5F, 0, 2);
    }
    if (BsBS->unk1A & 1) {
        BsBA->unk128 -= (sp178->unk14 > 0) ? 10 : 5;
        if (BsBA->unk128 < 0) {
            BsBA->unk128 = 0;
            BsBS->unk1A &= ~1;
        }
    } else if (BsBA->unk154 != 0x29 && (BsBD->unk1F0 & 0x40) && BsBA->unk128 < 0xFF) {
        if (!(BsBS->unk1A & 0x8000)) {
            camStartPath(BsBA, 2, 1);
            BsBS->unk1A |= 0x8000;
        } else {
            func_80641874(2, 0);
        }
        BsBA->unk128 += 5;
        if (BsBA->unk128 >= 0x100) {
            BsBA->unk128 = 0xFF;
        }
    }
    if (D_807FC924->unk2C0 != 1 && (BsBA->unk154 == 0x42 || BsBA->unk154 == 0x27)) {
        BsBA->unk144 = 1;
        actorSetTargetSpeed(BsBA, 0);
        BsBA->unk154 = 0x29;
        BsBA->unk155 = 0;
        BsBA->unk155 = 1;
    }
    switch (BsBA->unk154) {
    case 0x29:
        switch (BsBA->unk155) {
        case 0:
            actorMoveWithinZone(0, (f32)BsBS->unkA, (f32)BsBS->unkE, 0x309, 0.0f);
            break;
        case 1:
            if (sp178->unk14 >= 2) {
                func_80030E58();
            }
            BsBA->unk132 = 4;
            func_80030920((s32)sp178);
            func_80614D00(BsBA, D_80035AE4[sp178->unk14], 0.0f);
            BsBA->unk155++;
            break;
        case 3:
            BsBA->unk160 = 0.0;
            BsBA->unk155++;
            /* fallthrough */
        case 4:
            func_80030C30(D_80035AD4[sp178->unk14]);
            if (sp178->unk14 == 3) {
                func_80030D50();
            }
            break;
        case 5:
            BsBA->unk155++;
            break;
        case 6:
            if (D_807FBD70 == 5 && BsBP->unk154 == 0x24 && BsBA->unk160 > 0.79) {
                if (sp178->unk14 == 3) {
                    BsBA->unk154 = 0x37;
                    BsBA->unk155 = 0;
                    actorScriptStart(BsBP, 0);
                    actorScriptStart(BsBA, 0);
                    camStartPath(BsBA, 0x16, 1);
                    flagSet(0x1B0, 1, 0);
                } else {
                    BsBA->unk128 = 0xFF;
                    BsBA->unk132 = 1;
                    BsBA->unk155 = 8;
                    camStartPath(BsBA, 0x17, 1);
                    actorScriptStart(BsBA, 0);
                }
                func_80641874(2, 0xFF);
            }
            func_80030C30(D_80035AD4[sp178->unk14]);
            if (sp178->unk14 == 3) {
                func_80030D50();
            }
            break;
        case 7:
            BsBA->unk128 = 0xFF;
            BsBD->unkD4 = 0x12C;
            camStartPath(BsBA, 0x18, 1);
            func_80641874(2, 0xFF);
            func_80614D00(BsBA, 1.0f, 0.0f);
            actorScriptStart(BsBA, 0);
            BsBA->unk155 = 0xA;
            break;
        case 8:
            if (camIsCutsceneActive() == 0) {
                BsBA->unk155++;
            }
            break;
        case 9:
            sp178->unk15 = 0;
            sp178->unk14++;
            sp28 = D_80035AC0[sp178->unk14];
            /* fallthrough */
        case 10:
        case 11:
        case 12:
            if (camIsCutsceneActive() == 0) {
                func_806D0468(BsBP, 1);
                actorSetTargetSpeed(BsBA, D_807FDC9C->unkC);
                if (BsBA->unk132 != 1) {
                    if (func_806C9974(0, -1) != 0) {
                        func_80614E78(BsBP, 0x27);
                        BsBP->unk154 = 0x36;
                        BsBP->unk155 = 0;
                    }
                    BsBA->unk132 = 1;
                    sp178->unk15 = sp178->unk16;
                }
                func_80030AE0((BossD_Sub178 *)sp178);
                BsBA->unk154 = sp28[sp178->unk15];
                sp178->unk15++;
                BsBA->unk155 = 0;
                actorScriptStart(BsBA, 0x3E4);
                func_80030E58();
            }
            break;
        }
        break;
    case 0x28:
        func_80030E58();
        BsBA->unk154 = sp28[sp178->unk15];
        sp178->unk15++;
        BsBA->unk155 = 0;
        break;
    case 0x27:
        switch (BsBA->unk155) {
        case 0:
            func_8072CFE8(&sp50[2], &sp50[1], &sp50[0]);
            actorSetGroupState(D_80035ACF[D_807FDC98->unk20[BsBS->unk25 & 0x7F][0]], 1);
            BsBA->unkEC = mathAngleBetweenPoints2D((f32)sp50[2], (f32)sp50[0], BsBA->unk7C, BsBA->unk84);
            if (func_806CC10C(BsBA->unkE6, BsBA->unkEC) < 0) {
                actorScriptStart(BsBA, 0x401);
            } else {
                actorScriptStart(BsBA, 0x402);
            }
            actorSetTargetSpeed(BsBA, 0);
            BsBA->unk155++;
            break;
        case 1:
            BsBA->unkE6 = func_806CC190(BsBA->unkE6, (s16)(BsBA->unkEC + 0x800), 10.0f);
            actorMoveWithinZone(0, (f32)BsBS->unkA, (f32)BsBS->unkE, 0x309, 0.0f);
            break;
        case 2:
            BsBA->unkEE = BsBA->unkE6;
            BsBA->unkB8 = -150.0f;
            BsBA->unk155++;
            /* fallthrough */
        case 3:
            actorMoveWithinZone(0, (f32)BsBS->unkA, (f32)BsBS->unkE, 0x309, 0.0f);
            break;
        case 4:
            BsBA->unkB8 = BsBA->unkB8 * -1.0f;
            BsBA->unkE6 += 0x800;
            BsBA->unkEE = BsBA->unkE6;
            actorSetTargetSpeed(BsBA, D_807FDC9C->unkC);
            BsBA->unk154 = sp28[sp178->unk15];
            sp178->unk15++;
            BsBA->unk155 = 0;
            break;
        }
        break;
    case 0x1E:
        sp178->unk14 = 0;
        sp178->unk15 = 0;
        BsBA->unk154 = sp28[sp178->unk15];
        sp178->unk15++;
        BsBA->unk155 = 0;
        BsBA->unkB8 = (f32)(u32)D_807FDC9C->unkC;
        break;
    case 0:
        switch (BsBA->unk155) {
        case 0:
            actorScriptStart(BsBA, 0x3EA);
            BsBA->unk155++;
            break;
        case 2:
            BsBA->unk154 = sp28[sp178->unk15];
            sp178->unk15++;
            BsBA->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (BsBA->unk155) {
        case 0:
            BsBA->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                BsBP->unk60 &= ~4;
                camStartPath(BsBA, 0x1A, 1);
                BsBA->unk155++;
            }
            break;
        }
        break;
    default:
        func_80027BA8(sp28, 0x19, 0.0f);
        break;
    }
    if (BsBA->unk60 & 4) {
        billboardSetFlags(1);
        func_8065D254(BsBA, 0x3C8, 0x40, 0x40, 0x3C, 0x3C, 1, 0x12C, 0xB4, 0, 1.0f);
    }
    if (func_8072881C(0, (u8 *)D_807FDC90 + 0x28) != 0) {
        func_8072881C(0x81, (u8 *)D_807FDC90 + 0x28);
    }
    actorUpdateModelMatrix(BsBA, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/func_80031AA0.s")

#ifdef NON_MATCHING
typedef struct BsB_Sub4_0 {
    char pad0[4];
    f32 unk4;
    char pad8[8];
    s16 unk10;
} BsB_Sub4_0;

typedef struct BsB_Sub4 {
    BsB_Sub4_0 *unk0;
} BsB_Sub4;

typedef struct BsB_Sub174_0_174 {
    char pad0[4];
    f32 unk4;
    char pad8[0xA];
    s8 unk12;
    char pad13[1];
    s8 unk14;
    char pad15[2];
    s8 unk17;
} BsB_Sub174_0_174;

typedef struct BsB_Sub174_0 {
    char pad0[0x7C];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
    char pad88[0xCC];
    u8 unk154;
    char pad155[0x1F];
    BsB_Sub174_0_174 *unk174;
} BsB_Sub174_0;

typedef struct BsB_Sub174 {
    BsB_Sub174_0 *unk0;
    s8 unk4;
    s8 unk5;
} BsB_Sub174;

typedef struct BsB_Actor {
    char pad0[4];
    BsB_Sub4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5C];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    char padEA[0x40];
    s16 unk12A;
    char pad12C[0x18];
    u8 unk144;
    char pad145[0x25];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    char pad16D[7];
    BsB_Sub174 *unk174;
} BsB_Actor;

void func_80613C48(void *, s16, f32, f32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_80614644(void *, void *, f32);
void actorDespawn(void *);
void projectileSetTargetCoords(f32, f32, f32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);
extern s16 D_80035B00[];
extern s16 D_80035B08[];
extern s16 D_80035B10[];
extern s16 D_80035B18[];
extern s16 D_80035B20[];
extern s8 D_80035B28;
extern s16 D_80035B2C;
extern f32 D_80035B3C;
extern s16 D_80035B74;
extern f32 D_80036DC4;

#define ACTOR ((BsB_Actor *)D_807FBB40)

void func_80032B08(void) {
    BsB_Sub174 *sub174 = ACTOR->unk174;
    BsB_Sub174_0_174 *sp30 = sub174->unk0->unk174;
    BsB_Sub4_0 *sub4_0 = ACTOR->unk4->unk0;

    if (sub174->unk5 == 0) {
        f32 dx = D_807FBB4C->unk7C - ACTOR->unk7C;
        f32 dz = D_807FBB4C->unk84 - ACTOR->unk84;
        D_80036DC4 = dx * dx + dz * dz;
    }
    if (!(ACTOR->unk60 & 0x10)) {
        func_80613C48(ACTOR, sub174->unk4 + 0x668, 0.0f, 0.0f);
        ACTOR->unk12A = 0xFA0;
    }
    if (D_80035B28 & (1 << sub174->unk4)) {
        ACTOR->unkE8 = (s16)((s32)((f64)sp30->unk4 * 1024.0) - 0x400);
        ACTOR->unkE4 = D_80035B2C;
        if (sub4_0 != NULL) {
            if (D_80035B3C != sub4_0->unk4) {
                func_80614644(ACTOR, sub4_0, D_80035B3C);
            }
        }
    } else {
        ACTOR->unkE8 = 0;
        if (sub4_0 != NULL) {
            s32 v0 = sub174->unk4 + 0x66B;
            if (v0 != sub4_0->unk10) {
                func_80613C48(ACTOR, v0, 0.0f, 0.0f);
                func_80609140(0x38D, 0x7D00, 63.0f, 1.0f, 0, 0);
            } else {
                func_80614644(ACTOR, sub4_0, sub4_0->unk4 + 0.75f);
            }
            if (sub174->unk4 == 1) {
                if (sub4_0->unk4 > 24.0f) {
                    sub4_0->unk4 = 24.0f;
                }
                if (sub4_0->unk4 > 15.0f) {
                    ACTOR->unk80 -= 10.0f;
                }
            } else {
                if (sub4_0->unk4 > 37.0f) {
                    sub4_0->unk4 = 37.0f;
                }
                if (sub4_0->unk4 > 26.0f) {
                    ACTOR->unk80 -= 10.0f;
                }
            }
            if ((f64)ACTOR->unk80 < 0.0) {
                func_80609140(0x384, 0x7D00, 63.0f, 1.0f, 0, 0);
                actorDespawn(ACTOR);
            }
        }
    }
    if (sub174->unk5 == 0) {
        ACTOR->unk144 = 0xC;
        if (sub174->unk4 == 0) {
            if (sp30->unk17 == 1) {
                s16 temp_v1;
                if (sub174->unk0->unk154 == 0) {
                    D_80035B74 = 0x28;
                }
                temp_v1 = D_80035B74 - 1;
                D_80035B74 = temp_v1;
                if (temp_v1 < 0) {
                    f32 x = ACTOR->unk7C + D_80035B18[sp30->unk14];
                    f32 y = ACTOR->unk80 + 270.0f;
                    f32 z = ACTOR->unk84 + D_80035B20[sp30->unk14];
                    D_80035B74 = 0xA;
                    projectileSetTargetCoords(x, y, z);
                    projectileAimAndSpawn(0x2C, 1, 0.25f, D_807FBB4C->unk7C, D_807FBB4C->unk80, D_807FBB4C->unk84, 2400.0f, ACTOR);
                }
            } else {
                D_80035B74 = 0;
            }
        }
        ACTOR->unk7C = D_80035B00[sp30->unk14] + sub174->unk0->unk7C;
        ACTOR->unk84 = D_80035B08[sp30->unk14] + sub174->unk0->unk84;
        ACTOR->unkE6 = D_80035B10[sp30->unk14];
    } else {
        s32 var_v0;
        ACTOR->unk144 = 1;
        var_v0 = sp30->unk14 + 2;
        if (var_v0 >= 4) {
            var_v0 -= 4;
        }
        ACTOR->unk7C = D_80035B00[var_v0] + sub174->unk0->unk7C;
        ACTOR->unk84 = D_80035B08[var_v0] + sub174->unk0->unk84;
        ACTOR->unkE6 = D_80035B10[var_v0];
        ACTOR->unk60 |= 0x800000;
        ACTOR->unk16A = 0x23;
        ACTOR->unk16B = 0x23;
        ACTOR->unk16C = 0x46;
        if (sp30->unk12 != 1) {
            ACTOR->unk60 &= ~4;
        } else {
            ACTOR->unk60 |= 4;
        }
    }
    actorUpdateModelMatrix(ACTOR, 0);
}
#undef ACTOR
#else

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/func_80032B08.s")
#endif

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/D_80036A90.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/D_80036AA8.s")
