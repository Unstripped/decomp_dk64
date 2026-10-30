#include "common.h"

typedef struct BossA_Struct_807FBB40 {
    u8 pad0[0x7C];
    f32 unk7C;
    u8 pad80[4];
    f32 unk84;
} BossA_Struct_807FBB40;

typedef struct BossA_Struct_807FDC9C {
    u8 pad0[6];
    s16 unk6;
} BossA_Struct_807FDC9C;

typedef struct BossA_Struct_807FBB44 {
    u8 pad0[0xC8];
    f32 unkC8;
    u8 padCC[0x12A - 0xCC];
    s16 unk12A;
} BossA_Struct_807FBB44;

extern BossA_Struct_807FBB40 *D_807FBB40;
extern BossA_Struct_807FDC9C *D_807FDC9C;
extern BossA_Struct_807FBB44 *D_807FBB44;

f32 func_80612790(s16);
f32 func_80612794(s16);
void spawnNodeSpawnById(s16, s16, s16, s16, s32, s32, s32);

void func_8002C520(s16 arg0, s16 arg1, s16 arg2) {
    f32 pad;
    f32 sinVal;
    f32 fArg1;

    sinVal = func_80612794(arg2);
    fArg1 = arg1;
    spawnNodeSpawnById(
        arg0,
        sinVal * fArg1 + D_807FBB40->unk7C,
        D_807FDC9C->unk6,
        func_80612790(arg2) * fArg1 + D_807FBB40->unk84,
        0, 0, 0
    );
    D_807FBB44->unkC8 *= 2;
    D_807FBB44->unk12A = 0x7D0;
}

typedef struct BossA_Struct_807FDC90 {
    u8 pad0[0x1A];
    u16 unk1A;
    u8 pad1C[0x28 - 0x1C];
    s32 unk28;
} BossA_Struct_807FDC90;

extern BossA_Struct_807FDC90 *D_807FDC90;

s32 randomNonNegative(void);
void camStartPath(void *, s32, s32);

void func_8002C5F4(void) {
    func_8002C520(2, ((randomNonNegative() >> 15) % 100) + 300, (randomNonNegative() >> 15) % 4096);
    func_8002C520(3, ((randomNonNegative() >> 15) % 100) + 300, (randomNonNegative() >> 15) % 4096);
    func_8002C520(4, ((randomNonNegative() >> 15) % 100) + 300, (randomNonNegative() >> 15) % 4096);

    if (!(D_807FDC90->unk1A & 0x8000)) {
        D_807FDC90->unk1A |= 0x8000;
        camStartPath(D_807FBB44, 2, 1);
    }
}

void animSetLoopLimit(void *, s32, s32);
void animSetFinished(void *, s32, s32);
void animSetFrameAndSubframe(void *, s32, s16, f32);

void func_8002C748(arg0)
u8 arg0;
{
    D_807FDC90->unk28 = 2;
    animSetLoopLimit(D_807FBB40, arg0, 1);
    animSetFinished(D_807FBB40, arg0, 1);
    animSetFrameAndSubframe(D_807FBB40, arg0, D_807FDC90->unk28 & 0xF, 0.0f);
}

void bossAnimFrameBounceStep(void) {
    u16 var_t1 = 0;
    u8 var_t0;
    u8 val;
    var_t0 = D_807FDC90->unk28 & 0x80;
    val = D_807FDC90->unk28 & 0xF;
    if (var_t0) {
        val += 1;
        if (val >= 2) {
            var_t0 = 0;
        } else {
            var_t1 = 0x8000;
        }
    } else {
        val -= 1;
        if (val <= 0) {
            var_t0 = 0x80;
        } else {
            var_t1 = 0x8000;
        }
    }
    animSetFrameAndSubframe(D_807FBB40, 0, (s16)val, 0.0f);
    animSetFrameAndSubframe(D_807FBB40, 1, (s16)val, 0.0f);
    D_807FDC90->unk28 = var_t1 | val | var_t0;
}

typedef struct BossA_Struct_807FDC94 {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x15E - 0x88];
    u8 unk15E;
} BossA_Struct_807FDC94;

extern BossA_Struct_807FDC94 *D_807FDC94;

s32 randomNonNegative(void);
void projectileGetTargetCoords(void *, s32);
void projectileAimAndSpawn(s32, s16, f32, f32, f32, f32, f32, void *);

void func_8002C8B4(void) {
    projectileGetTargetCoords(D_807FBB40, 1);
    projectileAimAndSpawn(
        0x116,
        ((randomNonNegative() >> 15) % 3) + 1,
        1.0f,
        D_807FDC94->unk7C,
        D_807FDC94->unk80 + (f32)D_807FDC94->unk15E,
        D_807FDC94->unk84,
        300.0f,
        D_807FBB40
    );
}

typedef struct BossSwayState {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} BossSwayState;

typedef struct BossModelInfo {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
} BossModelInfo;

typedef struct BossActor {
    char pad0[4];
    BossModelInfo *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x18];
    f32 unkA0;
    f32 unkA4;
    char padA8[0x18];
    f32 unkC0;
    char padC4[0x22];
    s16 unkE6;
    s16 unkE8;
    char padEA[4];
    s16 unkEE;
    char padF0[0x42];
    s16 unk132;
    s16 unk134;
    char pad136[0xE];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[8];
    u8 unk15E;
    char pad15F[0x19];
    BossSwayState *unk178;
} BossActor;

typedef struct BossWorkState {
    char pad0[0x28];
    s32 unk28;
    s16 unk2C;
} BossWorkState;

typedef struct BossLayoutData {
    char pad0[0x30];
    f32 unk30;
    char pad34[0x12];
    u16 unk46;
} BossLayoutData;

typedef struct BossConfig {
    char pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    char padA[3];
    u8 unkD;
} BossConfig;

typedef struct BossActorPos {
    char pad0[0x7C];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
} BossActorPos;

extern BossLayoutData *D_807FDC98;
extern u8 D_807FBD70;
extern u8 D_807FBB85;
extern s32 D_807FBD6C;
extern void *gCamActor;

void behaviourFrameBegin(void);
s32 flagGet(s32, s32);
void func_8067E278(s32, s32);
void func_8072D714(s32, s32);
void actorSetUniformScale(void *, f32);
void actorSpawnLinkedFollower(void);
void actorScriptStart(void *, s32);
void func_80613C48(void *, s16, f32, f32);
s32 sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
s32 currentActorTestClearFlag(void);
void actorSetTargetSpeed(void *, s32);
void camSetSecondTarget(void *, s32, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s16 func_806CC190(s16, s16, s32);
s32 spawnNodeHasActor(s32);
s32 camIsCutsceneActive(void);
void func_8072D9D4(void);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void func_806AD260(s32, s32, s32);
void bossAnimFrameBounceStep(void);
void actorUpdateModelMatrix(void *, s32);

#define A40 ((BossActor *)D_807FBB40)
#define DC90 ((BossWorkState *)D_807FDC90)
#define DC94 ((BossActorPos *)D_807FDC94)
#define DC9C ((BossConfig *)D_807FDC9C)

void func_8002C964(void) {
    BossSwayState *sp3C;

    sp3C = A40->unk178;
    behaviourFrameBegin();
    if (!(A40->unk60 & 0x10)) {
        func_8002C748(0);
        func_8002C748(1);
        D_807FDC98->unk30 = 2.5f;
        D_807FDC98->unk46 &= 0xFFF7;
        D_807FDC98->unk46 |= 0x200;
        A40->unk60 |= 0x400;
        A40->unk132 = 4;
        A40->unk154 = 0x1E;
        actorSetUniformScale(D_807FBB40, 2.0 * A40->unk4->unk34);
        actorSpawnLinkedFollower();
    }
    if (((D_807FBD70 == 9) || (D_807FBB85 != 0)) && (A40->unk154 != 0x37)) {
        if (flagGet(0xF7, 0) != 0) {
            func_8067E278(0, 1);
            A40->unk154 = 0x40;
        } else {
            camStartPath(D_807FBB40, 6, 1);
            A40->unkC0 = 200.0f;
            func_8072D714(D_807FBD6C, 0x2F7);
        }
    }
    switch (A40->unk154) {
    case 0x28:
        switch (A40->unk155) {
        case 0:
            camStartPath(D_807FBB40, 8, 1);
            actorScriptStart(D_807FBB40, 0);
            func_80613C48(D_807FBB40, 0x589, 0.0f, 0.0f);
            DC90->unk2C = 0;
            A40->unk155 = 1;
            A40->unk144 = 1;
            sfxPlayAtPositionPooled(A40->unk7C, A40->unk80, A40->unk84, 0x2FC, 0xFF, 0x7F, 0, 0, 0.0f, 0);
        case 1:
            DC90->unk2C += 8;
            if (DC90->unk2C >= 0x259) {
                A40->unk155 = 2;
            }
            A40->unk80 += 2.0f;
            A40->unkE6 += DC90->unk2C;
            actorSetUniformScale(D_807FBB40, ((0.3 - A40->unk4->unk38) * 0.05) + A40->unk4->unk38);
            break;
        case 2: {
            s16 v;
            DC90->unk2C -= 0x14;
            v = DC90->unk2C;
            if (v < 0) {
                DC90->unk2C = 0;
                v = DC90->unk2C;
            }
            A40->unkE6 += v;
            if (currentActorTestClearFlag() != 0) {
                A40->unk155 = 3;
                A40->unk60 &= ~4;
            }
            break;
        }
        case 3:
            if (currentActorTestClearFlag() != 0) {
                A40->unk15E = 0xA;
                DC90->unk28 |= 0x8000;
                A40->unk132 = 1;
                A40->unk154 = 0x23;
                actorSetTargetSpeed(D_807FBB40, DC9C->unkD);
                A40->unk144 = 0x24;
                actorScriptStart(D_807FBB40, 0x2F4);
            }
            break;
        }
        break;
    case 0x1E:
        switch (A40->unk155) {
        case 0:
            if (currentActorTestClearFlag() != 0) {
                DC90->unk28 |= 0x8000;
                A40->unk155 = 1;
            }
            break;
        case 2:
            if ((A40->unk80 - A40->unkA4) > 300.0f) {
                A40->unk80 -= 10.0f;
            } else {
                DC90->unk28 |= 0x8000;
                A40->unk155 = 3;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                A40->unk154 = 0x27;
                A40->unk155 = 0;
                camSetSecondTarget(gCamActor, 0, 0);
            }
            break;
        }
        break;
    case 0x27:
        A40->unkE6 = func_806CC190(A40->unkE6, mathAngleBetweenPoints2D(DC94->unk7C, DC94->unk84, A40->unk7C, A40->unk84), 0x41000000);
        switch (A40->unk155) {
        case 0:
            func_8002C5F4();
            A40->unk155 = 1;
            break;
        case 1:
            if ((spawnNodeHasActor(2) == 0) && (spawnNodeHasActor(3) == 0) && (spawnNodeHasActor(4) == 0)) {
                A40->unk155 = 2;
                DC90->unk2C = 0x96;
                DC90->unk28 |= 0x8000;
                A40->unk132 = 8;
                actorScriptStart(D_807FBB40, 0x2FA);
            }
            if ((camIsCutsceneActive() == 0) && ((randomNonNegative() >> 15) % 1000 >= 0x3E4)) {
                actorScriptStart(D_807FBB40, 0x2FD);
                A40->unk155 = 3;
            }
            break;
        case 2:
            if ((DC90->unk2C != 0) && (D_807FBD70 != 4)) {
                DC90->unk2C -= 1;
            } else {
                if (D_807FBD70 == 4) {
                    actorScriptStart(D_807FBB40, 0x2FC);
                    func_8072D9D4();
                    sp3C->unk2 = 0x96;
                    sp3C->unk4 = 0x800;
                    A40->unkEE = A40->unkE6;
                    if (A40->unk134 == 1) {
                        A40->unk154 = 0x28;
                        A40->unk155 = 0;
                    }
                }
                A40->unk132 = 4;
                DC90->unk28 |= 0x8000;
                A40->unk155 = 0;
            }
            break;
        case 4:
            A40->unk155 = 1;
            func_8002C8B4();
            break;
        }
        break;
    case 0x23:
        actorMoveWithinZone(0x23, DC94->unk7C, DC94->unk84, 0, 0.0f);
        break;
    case 0x37:
        func_806AD260(0x2F7, 1, 0);
        break;
    }
    if (sp3C->unk2 > 0) {
        sp3C->unk0 = func_80612794(sp3C->unk4) * sp3C->unk2;
        sp3C->unk4 += 0x32;
        sp3C->unk2 -= 1;
        A40->unkE8 = -sp3C->unk0;
        A40->unk7C = func_80612794(A40->unkEE) * sp3C->unk0 + DC9C->unk4;
        A40->unk84 = func_80612790(A40->unkEE) * sp3C->unk0 + DC9C->unk8;
        A40->unk80 = DC9C->unk6 - sqrtf(0x1C390 - sp3C->unk0 * sp3C->unk0);
    }
    if (DC90->unk28 & 0x8000) {
        bossAnimFrameBounceStep();
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

