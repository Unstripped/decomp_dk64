#include "common.h"

typedef struct BossC_6240_17C {
    char pad[4];
    u8 unk4;
    u8 pad5;
    s16 unk6;
    s16 unk8;
} BossC_6240_17C;

typedef struct BossC_6240_178 {
    char pad0[0x12];
    u16 unk12;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    char pad17[1];
    u8 unk18;
    char pad19[3];
    s32 unk1C;
} BossC_6240_178;

typedef struct BossC_6240_Sub4_0 {
    char pad[4];
    f32 unk4;
} BossC_6240_Sub4_0;

typedef struct BossC_6240_SubActor4 {
    BossC_6240_Sub4_0 *unk0;
    char pad4[0x64 - 4];
    u16 unk64;
} BossC_6240_SubActor4;

typedef struct BossC_6240_Actor40 {
    char pad0[4];
    BossC_6240_SubActor4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x6E - 0x64];
    s16 unk6E;
    char pad70[0xC];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x1C];
    f32 unkA4;
    char padA8[0x10];
    f32 unkB8;
    char padBC[4];
    f32 unkC0;
    f32 unkC4;
    char padC8[4];
    u8 unkCC;
    char padCD[0xE6 - 0xCD];
    s16 unkE6;
    char padE8[0x132 - 0xE8];
    s16 unk132;
    s16 unk134;
    char pad136[0xE];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x16A - 0x156];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    char pad16D[0xB];
    BossC_6240_178 *unk178;
    BossC_6240_17C *unk17C;
} BossC_6240_Actor40;

typedef struct BossC_6240_Sub1FC {
    char pad[0x5C];
    u16 unk5C;
} BossC_6240_Sub1FC;

typedef struct BossC_6240_BB70 {
    char pad0[0x15];
    u8 unk15;
    char pad16[0x1FC - 0x16];
    BossC_6240_Sub1FC *unk1FC;
    u8 unk200;
} BossC_6240_BB70;

typedef struct BossC_6240_C924 {
    char pad0[0x2C0];
    u8 unk2C0;
} BossC_6240_C924;

typedef struct BossC_6240_D580 {
    char pad0[0xD4];
    s16 unkD4;
    char padD6[0x1D8 - 0xD6];
    f32 unk1D8;
} BossC_6240_D580;

typedef struct BossC_6240_DC90 {
    char pad0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
    char pad10[6];
    s16 unk16;
    char pad18[2];
    u16 unk1A;
    char pad1C[9];
    u8 unk25;
    char pad26[2];
    u8 unk28[4];
    s16 unk2C;
} BossC_6240_DC90;

typedef struct BossC_6240_Sub4 {
    char pad[0x10];
    s16 unk10;
} BossC_6240_Sub4;

typedef struct BossC_6240_DC94 {
    char pad0[4];
    BossC_6240_Sub4 **unk4;
    char pad8[0x74];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} BossC_6240_DC94;

typedef struct BossC_6240_DC98 {
    char pad0[0x30];
    f32 unk30;
    char pad34[0x46 - 0x34];
    u16 unk46;
} BossC_6240_DC98;

typedef struct BossC_6240_DC9C {
    char pad0[0xC];
    u8 unkC;
} BossC_6240_DC9C;

typedef struct BossC_6240_SubA0 {
    char pad[0xA0];
    s16 unkA0;
    s16 unkA2;
    s16 unkA4;
} BossC_6240_SubA0;

typedef struct BossC_6240_DCA0 {
    char pad0[0x14];
    BossC_6240_SubA0 *unk14;
    char pad18[0xC];
    u8 unk24[1];
} BossC_6240_DCA0;

extern BossC_6240_Actor40 *D_807FBB40;
extern u32 D_8076A064;

s32 randomNonNegative(void);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_8002A240(void) {
    BossC_6240_17C *s0 = D_807FBB40->unk17C;
    f32 sp20;
    if (s0->unk4 != 0) {
        s0->unk4--;
        sp20 = (f32)(func_80612794((s16)(s32)(((f64)(u32)s0->unk4 / 10.0) * (s0->unk8 - (s0->unk8 + 0x400)) + (s0->unk8 + 0x400))) * 20.0);
        D_807FBB40->unk7C += sp20 * func_80612794(s0->unk6);
        D_807FBB40->unk84 += sp20 * func_80612790(s0->unk6);
        if (s0->unk4 == 0) {
            s0->unk8 += 0x400;
        }
    } else if (((randomNonNegative() >> 15) % 1000) >= 941) {
        s0->unk4 = 10;
    }
    D_807FBB40->unk80 += 8.0 * (f64)func_80612794((s16)(s32)((f64)(u32)D_8076A064 * 200.0));
}
void *actorFindByType(s32);
void func_8067AB20(void *, void *, s32, s32, void *, s32);

void func_8002A41C(u8 arg0) {
    void *target;
    f32 sp2C[2];

    switch (arg0) {
    case 0:
        target = actorFindByType(0x61);
        if (target != NULL) {
            func_8067AB20(D_807FBB40, target, 0x01000000, 1, sp2C, 0);
        }
        break;
    case 1:
        target = actorFindByType(0x60);
        if (target != NULL) {
            func_8067AB20(D_807FBB40, target, 0x01000000, 1, sp2C, 0);
        }
        target = actorFindByType(0x61);
        if (target != NULL) {
            func_8067AB20(D_807FBB40, target, 0x01000000, 3, sp2C, 0);
        }
        break;
    case 2:
        target = actorFindByType(0x60);
        if (target != NULL) {
            func_8067AB20(D_807FBB40, target, 0x01000000, 1, sp2C, 0);
        }
        target = actorFindByType(0x61);
        if (target != NULL) {
            func_8067AB20(D_807FBB40, target, 0x01000000, 2, sp2C, 0);
        }
        break;
    }
}

extern u8 D_80720120[];

void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714C08(void *, f32, void *, s32, s32);

void func_8002A55C(u8 arg0, f32 arg1) {
    if (!(arg0 & D_8076A064)) {
        func_807149B8(1);
        func_807149C8(0xFF, 0xD7, 0x58, 0xFF);
        func_80714C08(D_80720120, arg1, D_807FBB40, 1, 0);
    }
}

void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void func_8071498C(void *);
void func_80714950(void *);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_80714998(s32);
void func_8071EDEC(void);
void func_8071720C(void);
extern void *D_8074E880[];

void bossSpawnSparkles(void) {
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    s32 pad[1];
    s16 i;
    s32 r1;

    actorGetNodePos(D_807FBB40, 1, &sp6C, &sp68, &sp64);
    sp6C += (f32)(((randomNonNegative() >> 15) % 80) - 40);
    sp68 += (f32)(((randomNonNegative() >> 15) % 100) + 50);
    sp64 += (f32)(((randomNonNegative() >> 15) % 80) - 40);
    func_807149B8(1);
    func_8071498C(func_8071EDEC);
    func_80714950(D_807FBB40);
    func_807149C8(0xFF, 0xD7, 0x58, 0xFF);
    func_80714CC0(D_80720120, 1.5f, sp6C, sp68, sp64);
    for (i = 0; i < 4; i++) {
        func_80714998(2);
        func_8071498C(func_8071720C);
        func_807149B8(1);
        r1 = randomNonNegative();
        func_80714C08(D_8074E880[((r1 >> 15) % 1000) % 3], 1.5f, D_807FBB40, ((randomNonNegative() >> 15) % 32767 % 22) + 2, 0);
    }
}

typedef struct BossC_6240_Actor {
    char pad[0x7C];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
    f32 unk88;
    char pad8C[4];
    f32 unk90;
    char pad94[0x154 - 0x94];
    u8 unk154;
} BossC_6240_Actor;

extern BossC_6240_Actor *D_807FBB4C;
s32 polygonContainsPoint2D(s16, s16, s32);

void bossClampPosition(s32 arg0) {
    if (!polygonContainsPoint2D((s32)D_807FBB4C->unk7C, (s32)D_807FBB4C->unk84, arg0)) {
        D_807FBB4C->unk7C = D_807FBB4C->unk88;
        D_807FBB4C->unk84 = D_807FBB4C->unk90;
    }
}


extern u8 *D_80035A20[][5];
extern u8 *D_80035A34[];
extern u8 D_800362F0[];
extern u8 D_8071FB34[];
extern f32 D_807502E8;
extern f32 D_807502FC;
extern s32 D_8076A0A8;
extern s32 D_8076D1F8;
extern s32 gCamActor;
extern void *D_807FBB44;
extern BossC_6240_BB70 D_807FBB70;
extern BossC_6240_C924 *D_807FC924;
extern BossC_6240_D580 *D_807FD580;
extern BossC_6240_DC90 *D_807FDC90;
extern BossC_6240_DC94 *D_807FDC94;
extern BossC_6240_DC98 *D_807FDC98;
extern BossC_6240_DC9C *D_807FDC9C;
extern BossC_6240_DCA0 *D_807FDCA0;

void func_80027840(void *);
void bossScriptStep(u8 *, s32, f32);
void bossSpawnParticleRing(s32, s16, s16, s16, s32, s32);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_80613C48(void *, s16, f32, f32);
void func_80614D00(void *, f32, f32);
void actorScriptStart(void *, s32);
void camSetTargetFocusActor(s32, void *);
void camSetTarget(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 camIsCutsceneActive(void);
void camStartPath(void *, s32, s32);
void camReturnToFollow(s32, void *);
void camSetFollowMode(s32);
void camSetSecondTarget(s32, s32, s32);
s32 currentActorTestClearFlag(void);
void currentActorClearFlag(void);
void actorUpdateModelMatrix(void *, s32);
void func_8063DA40(s16, s32);
f32 effectNodeGetValue(s32);
void screenShakeStop(void);
void actorApplyVelocityCustom(void *, f32, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void collisionCheckActorFloor(void *, f32, f32, f32, void *);
void actorGetOrSetNodeScale(void *, s32, f32);
s32 actorTableContains(void *);
void func_80686F90(s32, s16, s16);
void func_806871DC(s32);
void projectileGetTargetCoords(void *, s32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);
void projectileClampAngleAndSpawn(s16, s32, s32, s32, f32, f32, f32, f32, f32, void *);
void projectileSpawnWithShockwave(s32, f32, s32, s32, s32, s32, f32, f32, f32, f32);
void loadModelAssetTable(void);
void func_806D0430(f32);
void func_806D0468(void *, s32);
void func_806FB370(s32, s32, s32);
void effectFreeAll(void);
void func_8072881C(s32, void *);
void behaviourFrameBegin(void);
void actorApplyGravity(void);
void actorTurnTowardTarget(s32, f32, f32, s32);
void func_8072A450(void);
s32 actorMoveWithinZone(s32, f32, f32, s32, f32);
void actorSetTargetSpeed(void *, u8);
s32 func_8072D13C(s32, s32);
s32 flagGet(s32, s32);
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, void *);
void n_alSndpStop(s32);


void func_8002A92C(void) {
    BossC_6240_178 *state;
    BossC_6240_17C *sp88;
    u8 *sp84;
    f32 sp80;
    u8 sp7F;
    u8 sp7E;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    u16 roll;
    s16 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;

    state = D_807FBB40->unk178;
    sp88 = D_807FBB40->unk17C;
    sp84 = D_80035A20[(D_8076A0A8 == 0xC5) ? 0 : 1][state->unk14];
    sp80 = D_807FBB40->unk80;
    sp7E = sp7F = 1;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        camSetSecondTarget(gCamActor, 0, 0);
        func_806FB370(5, 0, 1);
        currentActorClearFlag();
        func_806D0430(1.2f);
        loadModelAssetTable();
        D_807FBB40->unkCC = 2;
        func_80027840(&D_800362F0);
        D_807FDC98->unk30 = 3.0f;
        D_807FBB40->unkB8 = 0.0f;
        D_807FBB40->unk60 |= 0x800000;
        D_807FDC98->unk46 |= 0x20;
        state->unk1C = 0;
        D_807FBB40->unk154 = sp84[state->unk15++];
        D_807FBB40->unk155 = 0;
    }
    D_807FD580->unkD4 = (D_807FD580->unkD4 < 50) ? D_807FD580->unkD4 : 50;
    D_807FBB40->unk16A = (u8) (u32) (((f64) func_80612794((s16) (D_8076A064 * 0x64)) * 50.0) + 200.0);
    D_807FBB40->unk16B = (u8) D_807FBB40->unk16A;
    D_807FBB40->unk16C = (u8) D_807FBB40->unk16A;
    if (D_807FBB40->unk154 == 0x55) {
        D_807FBB40->unk132 = 2;
    } else {
        D_807FBB40->unk132 = 1;
    }
    D_807FBB40->unk144 = 0x24;
    if (D_807FBB70.unk200 == 4) {
        if (state->unk14 == 3) {
            actorGetOrSetNodeScale(D_807FBB40, 1, 200.0f);
            func_8002A41C(0);
            D_807FBB40->unk154 = 0x56;
            D_807FBB40->unk155 = 0;
            actorScriptStart(D_807FBB40, 0x2D1);
            D_807FDC90->unk2C = 0x12C;
        } else {
            effectFreeAll();
            screenShakeStop();
            D_807FBB40->unk154 = 0x4D;
            D_807FBB40->unk155 = 0;
            D_807FBB40->unkC4 = (f32) D_807502FC;
            actorScriptStart(D_807FBB40, 0x2CD);
            D_807FDC90->unkC = -0x2BC;
            state->unk15 = 0;
            state->unk14++;
            sp84 = D_80035A34[state->unk14];
            if ((state->unk14 == 3) && (D_8076A0A8 == 0xC5)) {
                camStartPath(D_807FBB40, 8, 1);
            } else {
                camStartPath(D_807FBB40, 2, 1);
            }
        }
    } else if ((D_807FBB70.unk200 == 5) && (D_807FC924->unk2C0 != 1)) {
        sp6C = 0x14B;
        actorScriptStart(D_807FBB40, 0x2D2);
        actorGetNodePos(D_807FBB40, 2, &sp78, &sp74, &sp70);
        if (D_807FBB40->unk134 == 1) {
            D_807FDC90->unk1A |= 0x8000;
        }
        D_807FDC90->unk16 = (s16) (*D_807FDC94->unk4)->unk10;
        D_807FBB40->unk60 |= 0x20000000;
        func_80714CC0(&D_8071FB34, 2.0f, ((randomNonNegative() >> 0xF) % 30 + sp78) - 15.0f, ((randomNonNegative() >> 0xF) % 30 + sp74) - 15.0f, ((randomNonNegative() >> 0xF) % 30 + sp70) - 15.0f);
        func_80609140(0x1CA, 0x7FFF, 63.0f, 1.0f, 0, 0);
        roll = (randomNonNegative() >> 0xF) % 2048;
        if (roll < 0x2A8) {
            sp6C = 0x14E;
        } else if (roll < 0x550) {
            sp6C = 0x14D;
        }
        if (state->unk1C != 0) {
            n_alSndpStop(state->unk1C);
        }
        n_alSndpPlay(D_8076D1F8, sp6C, 0x7FFF, 0x3F, 1.0f, 0, &state->unk1C);
    } else if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (actorTableContains(D_807FBB70.unk1FC) != 0) && (D_807FBB70.unk1FC->unk5C == 1)) {
        func_806D0468(D_807FBB4C, 2);
        func_8002A41C(1);
        func_8063DA40(0, 0xA);
        camSetFollowMode(gCamActor);
        camStartPath(D_807FBB40, 8, 1);
        D_807FBB40->unk154 = 0x37;
        D_807FBB40->unk155 = 0;
        D_807FBB40->unk60 &= ~4;
    }
    if (!(state->unk12 & 1) && (effectNodeGetValue(1) > 640.0f) && (D_807FBB4C->unk154 != 0x42)) {
        if (D_807FC924->unk2C0 != 1) {
            func_806D0468(D_807FBB4C, 1);
            D_807FD580->unk1D8 = 0.1f;
        }
        camStartPath(D_807FBB40, 0xA, 1);
        state->unk12 |= 1;
        state->unk14 = 4;
        state->unk15 = 0;
        sp84 = D_80035A20[(D_8076A0A8 == 0xC5) ? 0 : 1][state->unk14];
        D_807FBB40->unk154 = sp84[state->unk15];
        state->unk15 += 1;
        D_807FBB40->unk155 = 0;
    }
    switch (D_807FBB40->unk154) {
    case 0x6A:
        break;
    case 0x56:
        sp7E = 0;
        D_807FBB40->unk132 = 4;
        actorMoveWithinZone(0x45, 606.0f, 566.0f, 0x292, 0.0f);
        if (D_807FBB40->unk155 == 1) {
            bossClampPosition((s32)D_807FDCA0->unk24);
        }
        if ((D_807FBB40->unk155 == 0) && (D_807FBB4C->unk154 == 0x42)) {
            D_807FBB40->unk155 = 1;
            camSetTarget(gCamActor, D_807FBB40, 4, 0xD48, 0x320, 0, 0, 0xC8, 0x64, 0, 0.03f);
            camSetTargetFocusActor(gCamActor, D_807FBB4C);
        }
        if (!(D_807FDC90->unk1A & 0x8000)) {
            if (D_807FDC90->unk2C != 0) {
                if (D_807FDC90->unk2C == 100) {
                    func_8002A41C(2);
                }
                if (D_807FDC90->unk2C < 21) {
                    D_807FBB40->unk60 |= 0x20000000;
                }
                if (D_807FDC90->unk2C == 20) {
                    if (D_807FC924->unk2C0 != 1) {
                        D_807FD580->unkD4 = 0x64;
                    }
                    camReturnToFollow(gCamActor, D_807FBB4C);
                    func_806D0468(D_807FBB4C, 1);
                    D_807FD580->unk1D8 = 0.04f;
                }
                D_807FDC90->unk2C--;
                break;
            } else {
                D_807FBB40->unk60 &= 0xDFFFFFFF;
                actorGetOrSetNodeScale(D_807FBB40, 1, 64.0f);
                func_8002A41C(1);
                state->unk15 = state->unk16;
                D_807FBB40->unk154 = sp84[state->unk15++];
                D_807FBB40->unk155 = 0;
            }
            break;
        }
        break;
    case 0x37:
        sp7F = 0;
        sp7E = 0;
        D_807FBB40->unk132 = 4;
        bossClampPosition((s32)D_807FDCA0->unk24);
        if ((D_807FBB40->unk155 == 0) && (currentActorTestClearFlag() != 0)) {
            D_807FBB40->unk155 += 1;
            bossSpawnParticleRing(0xEC, D_807FDCA0->unk14->unkA0, D_807FDCA0->unk14->unkA2 + 0x14, D_807FDCA0->unk14->unkA4, 0x5DC, 4);
        }
        break;
    case 0x27:
        sp7E = 0;
        switch (D_807FBB40->unk155) {
        case 0:
            if ((D_8076A0A8 == 0xC5) || (flagGet(0x69, 2) != 0)) {
                if (D_8076A0A8 == 0xC5) {
                    D_807FBB40->unk60 &= ~4;
                } else {
                    actorScriptStart(D_807FBB40, 0x2C6);
                }
                D_807FBB40->unk155 = 6;
            } else {
                func_80613C48(D_807FBB40, 0x539, 0, 0);
                func_80614D00(D_807FBB40, 0, 0);
                D_807FBB40->unk155 = 1;
            }
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(D_807FBB40, 0x2C4);
                func_80614D00(D_807FBB40, 0.5f, 0);
                D_807FBB40->unk155 = 2;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                D_807FDC90->unkC = 0x1F4;
                actorScriptStart(D_807FBB40, 0x2C5);
                D_807FBB40->unk155 = 4;
            }
            break;
        case 5:
            if ((D_807FBB40->unkA4 + 180.0f) < D_807FBB40->unk80) {
                D_807FBB40->unk154 = 0x11;
                D_807FBB40->unk155 = 0;
            }
            D_807FBB40->unk80 += ((D_807FBB40->unkA4 + 200.0f) - D_807FBB40->unk80) * 0.12;
            break;
        case 6:
            if (currentActorTestClearFlag() != 0) {
                D_807FBB40->unk154 = sp84[state->unk15++];
                D_807FBB40->unk155 = 0;
            }
            break;
        }
        break;
    case 0x2B:
        D_807FBB40->unk132 = 2;
        switch (D_807FBB40->unk155) {
        case 0:
            actorScriptStart(D_807FBB40, 0x2CF);
            D_807FBB40->unk155 = 1;
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                func_8063DA40(0, 1);
                D_807FBB40->unk154 = sp84[state->unk15++];
                D_807FBB40->unk155 = 0;
            }
            break;
        }
        break;
    case 0x29:
        D_807FBB40->unk132 = 2;
        switch (D_807FBB40->unk155) {
        case 0:
            actorScriptStart(D_807FBB40, 0x2CE);
            D_807FBB40->unk155 = 1;
            break;
        case 2:
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x14A, 0xFF, 0x7F, 0, 0, 0, 0);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x221, 0xFF, 0x7F, 0, 0, 0, 0);
            projectileSpawnWithShockwave(0xBB, 0.14f, 0xFF, 0x96, 0x64, 6, 1.04f, 40.0f, 8.0f, 600.0f);
            func_80613C48(D_807FBB44, 0x4F9, 0, 0);
            func_80614D00(D_807FBB44, 0.5f, 0);
            D_807FBB40->unk154 = sp84[state->unk15++];
            D_807FBB40->unk155 = 0;
            break;
        }
        break;
    case 0x28:
        actorTurnTowardTarget(0x23, 606.0f, 566.0f, 0);
        switch (D_807FBB40->unk155) {
        case 0:
            D_807FDC90->unk25 += 4;
            func_8072D13C(0x42, 0);
            D_807FDC90->unk25 -= 4;
            actorScriptStart(D_807FBB40, 0x2CB);
            D_807FBB40->unk155 = 1;
            D_807FDC90->unk2C = 0;
            break;
        case 2:
            func_80686F90(2, (s16) ((((s32) (randomNonNegative() >> 0xF) % 2048) + D_807FBB40->unkE6) - 0x400), (s16) ((s32) (randomNonNegative() >> 0xF) % 2048));
            /* fallthrough */
        case 3:
            bossSpawnSparkles();
            break;
        case 5:
            projectileGetTargetCoords(D_807FBB40, 1);
            if (D_807FDC90->unk2C != 0) {
                projectileAimAndSpawn(0x51, 1, (f32) (((f64) ((s32) (randomNonNegative() >> 0xF) % 10) / 20.0) + 0.8), (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkC, (f32) D_807FDC90->unkE, 500.0f, D_807FBB40);
            } else {
                projectileAimAndSpawn(0x1E, 0x14, 0.2f, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkC, (f32) D_807FDC90->unkE, 500.0f, D_807FBB40);
            }
            D_807FDC90->unk2C = 1;
            break;
        case 7:
            D_807FBB40->unk154 = sp84[state->unk15++];
            D_807FBB40->unk155 = 0;
            break;
        }
        break;
    case 0x2A:
    case 0x2C:
        sp7E = 0;
        D_807FBB40->unk132 = 2;
        switch (D_807FBB40->unk155) {
        case 0:
            D_807FDC90->unk25 += 4;
            D_807FBB40->unk155 = 1;
            /* fallthrough */
        case 1:
            actorMoveWithinZone(0x42, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkE, 0x291, 0.0f);
            if (func_8072D13C(0x42, 0) != 0) {
                D_807FBB40->unkC0 = 100.0f;
                actorScriptStart(D_807FBB40, 0x2C8);
                D_807FBB40->unk155 = 2;
                D_807FDC90->unk25 -= 4;
                if (D_807FBB40->unk154 == 0x2C) {
                    camStartPath(D_807FBB40, 6, 1);
                }
            }
            break;
        case 2:
            actorMoveWithinZone(0x45, 606.0f, 566.0f, 0x292, 0.0f);
            break;
        case 3:
            D_807FBB40->unk154 = sp84[state->unk15++];
            D_807FBB40->unk155 = 0;
            break;
        }
        break;
    case 0x48:
        D_807FBB40->unk132 = 2;
        switch (D_807FBB40->unk155) {
        case 0:
            actorScriptStart(D_807FBB40, 0x2C9);
            D_807FDC90->unk2C = (s16) *(state->unk15 + sp84);
            state->unk15 += 1;
            D_807FBB40->unk155 = 1;
            /* fallthrough */
        case 1:
            if (D_807FDC90->unk2C != 0) { D_807FDC90->unk2C--;
            } else {
                D_807FBB40->unk154 = sp84[state->unk15++];
                D_807FBB40->unk155 = 0;
            }
            break;
        }
        break;
    case 0x43:
        D_807FBB40->unk132 = 2;
        switch (D_807FBB40->unk155) {
        case 0:
            actorScriptStart(D_807FBB40, 0x2CA);
            D_807FBB40->unk155 = 1;
            break;
        case 2:
            if ((D_807FBB40->unkA4 + 180.0f) < D_807FBB40->unk80) {
                actorSetTargetSpeed(D_807FBB40, D_807FDC9C->unkC);
                D_807FBB40->unk154 = sp84[state->unk15++];
                D_807FBB40->unk155 = 0;
            }
            D_807FBB40->unk80 += ((D_807FBB40->unkA4 + 200.0f) - D_807FBB40->unk80) * 0.12;
            sp7E = 0;
            break;
        }
        break;
    case 0x11:
        actorMoveWithinZone(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, 0x293, 0.0f);
        if (currentActorTestClearFlag() != 0) {
            D_807FBB40->unk154 = sp84[state->unk15++];
            D_807FBB40->unk155 = 0;
        }
        break;
    case 0x46:
        actorMoveWithinZone(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, 0x293, 0.0f);
        switch (D_807FBB40->unk155) {
        case 0:
            state->unk18 = sp84[state->unk15++];
            sp88->unk6 = (s16) (mathAngleBetweenPoints2D(606.0f, 566.0f, D_807FBB40->unk7C, D_807FBB40->unk84) + 0x400);
            D_807FBB40->unk155 = 1;
            /* fallthrough */
        case 1:
            actorScriptStart(D_807FBB40, 0x2C7);
            D_807FBB40->unk155 = 2;
            break;
        case 2:
            func_8002A55C(0, (f32) (((f64) D_807FBB40->unk4->unk0->unk4 * 0.06) + 2.0));
            break;
        case 3:
            projectileGetTargetCoords(D_807FBB40, 1);
            projectileClampAngleAndSpawn(D_807FBB40->unkE6, 0x320, 0x1E, 0xB, 1.2f, D_807FDC94->unk7C, D_807FDC94->unk80 + 30.0f, D_807FDC94->unk84, (f32) ((state->unk14 * 0x50) + 0x2BC), D_807FBB40);
            D_807FBB40->unk155 = 4;
            break;
        case 5:
            if (state->unk18--) {
                D_807FBB40->unk155 = 1;
            } else {
                D_807FBB40->unk154 = sp84[state->unk15++];
                D_807FBB40->unk155 = 0;
            }
            break;
        }
        func_8002A240();
        break;
    case 0x4D:
        sp7E = 0;
        switch (D_807FBB40->unk155) {
        case 1:
            func_8002A55C(3, 3.0f);
            break;
        case 2:
            sp7F = 0;
            actorApplyGravity();
            D_807FBB40->unk80 = (f32) (D_807FBB40->unk80 + D_807FBB40->unkC0);
            if (D_807FBB40->unk80 < (f32) D_807FDC90->unkC) {
                D_807FBB40->unk155 = 3;
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0xC, 0xFF, 0x50, 0, 0, 0, 0);
            }
            if ((D_8076A0A8 == 0xC5) && (state->unk14 == 3) && (currentActorTestClearFlag() != 0)) {
                bossSpawnParticleRing(0x4A, D_807FDCA0->unk14->unkA0, D_807FDCA0->unk14->unkA2 + 0x14, D_807FDCA0->unk14->unkA4, 0x5DC, 4);
            }
            break;
        case 3:
            sp7F = 0;
            if (currentActorTestClearFlag() != 0) {
                if ((D_8076A0A8 == 0xC5) && (state->unk14 == 3)) {
                    D_807FBB40->unk154 = 0x37;
                    D_807FBB40->unk155 = 1;
                } else {
                    D_807FBB40->unkC4 = (f32) D_807502E8;
                    actorScriptStart(D_807FBB40, 0x2CC);
                    D_807FBB40->unk155 = 4;
                    D_807FDC90->unkC = 0xC8;
                }
            }
            break;
        case 4:
            func_806871DC(0);
            sp7F = 0;
            D_807FBB40->unk80 = ((D_807FDC90->unkC + 5) - D_807FBB40->unk80) * 0.12 + D_807FBB40->unk80;
            actorTurnTowardTarget(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0);
            if ((D_807FDC90->unkC - 300) < D_807FBB40->unk80) {
                if (D_807FBB40->unk6E == -1) {
                    sfxPlayActorSound(D_807FBB40, 0x10F, 0, 1, 0, 0xFF, 0.8f, 0);
                }
                func_80613C48(D_807FBB40, 0x53D, 0, 24.0f);
            }
            if (D_807FDC90->unkC < D_807FBB40->unk80) {
                actorScriptStart(D_807FBB40, 0x2D0);
                D_807FBB40->unk155 = 5;
            }
            break;
        case 5:
            func_806871DC(0);
            break;
        case 6:
            func_806871DC(1);
            break;
        case 7:
            actorSetTargetSpeed(D_807FBB40, D_807FDC9C->unkC);
            D_807FBB40->unk154 = 0x11;
            D_807FBB40->unk155 = 0;
            break;
        }
        break;
    case 0x42:
        D_807FBB40->unk144 = 1;
        if (D_807FBB40->unk4->unk64 != 0x2C6) {
            actorScriptStart(D_807FBB40, 0x2C6);
        }
        /* fallthrough */
    default:
        bossScriptStep(sp84, 0x291, 0);
        break;
    }
    if (sp7E != 0) {
        if (D_807FBB40->unk80 < D_807FDC90->unkC) {
            D_807FBB40->unk80 = (D_807FDC90->unkC - sp80) * 0.03 + sp80;
            D_807FBB40->unkC0 = 0.0f;
        } else {
            actorApplyGravity();
            if ((f32) D_807FDC90->unkC < D_807FBB40->unk80) {
                actorApplyVelocityCustom(D_807FBB40, 0, D_807FBB40->unkC0);
            }
        }
    }
    func_8072881C(0, D_807FDC90->unk28);
    if (sp7F != 0) {
        actorGetNodePos(D_807FBB40, D_807FBB40->unkCC, &sp68, &sp64, &sp60);
        collisionCheckActorFloor(D_807FBB40, sp68, sp64, sp60, &D_807FBB40->unkA4);
        func_8072A450();
    }
    if (camIsCutsceneActive() != 0) {
        D_807FBB40->unk144 = 1;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_800362F0.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_800362FC.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036308.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_8003631C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036334.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036340.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036354.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036388.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_8003639C.s")
