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

extern BossC_6240_Actor40 *gCurrentActor;
extern u32 gFrameCounter;

s32 randomNonNegative(void);
f32 mathCosF(s16);
f32 mathSinF(s16);

void bossPufftossBobStep(void) {
    BossC_6240_17C *s0 = gCurrentActor->unk17C;
    f32 sinVal;
    if (s0->unk4 != 0) {
        s0->unk4--;
        sinVal = (f32)(mathSinF((s16)(((f64)s0->unk4 / 10.0) * (s0->unk8 - (s0->unk8 + 0x400)) + (s0->unk8 + 0x400))) * 20.0);
        gCurrentActor->unk7C += sinVal * mathSinF(s0->unk6);
        gCurrentActor->unk84 += sinVal * mathCosF(s0->unk6);
        if (s0->unk4 == 0) {
            s0->unk8 += 0x400;
        }
    } else if (((randomNonNegative() >> 15) % 1000) >= 941) {
        s0->unk4 = 10;
    }
    gCurrentActor->unk80 += 8.0 * (f64)mathSinF((s16)((f64)gFrameCounter * 200.0));
}
void *actorFindByType(s32);
void func_8067AB20(void *, void *, s32, s32, void *, s32);

void bossPufftossNotifyLaser(u8 targetIndex) {
    void *target;
    f32 targetPos[2];

    switch (targetIndex) {
    case 0:
        target = actorFindByType(0x61);
        if (target != NULL) {
            func_8067AB20(gCurrentActor, target, 0x01000000, 1, targetPos, 0);
        }
        break;
    case 1:
        target = actorFindByType(0x60);
        if (target != NULL) {
            func_8067AB20(gCurrentActor, target, 0x01000000, 1, targetPos, 0);
        }
        target = actorFindByType(0x61);
        if (target != NULL) {
            func_8067AB20(gCurrentActor, target, 0x01000000, 3, targetPos, 0);
        }
        break;
    case 2:
        target = actorFindByType(0x60);
        if (target != NULL) {
            func_8067AB20(gCurrentActor, target, 0x01000000, 1, targetPos, 0);
        }
        target = actorFindByType(0x61);
        if (target != NULL) {
            func_8067AB20(gCurrentActor, target, 0x01000000, 2, targetPos, 0);
        }
        break;
    }
}

extern u8 D_80720120[];

void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714C08(void *, f32, void *, s32, s32);

void bossPufftossSpawnGlow(u8 sparkleInterval, f32 scale) {
    if (!(sparkleInterval & gFrameCounter)) {
        func_807149B8(1);
        func_807149C8(0xFF, 0xD7, 0x58, 0xFF);
        func_80714C08(D_80720120, scale, gCurrentActor, 1, 0);
    }
}

void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void func_8071498C(void *);
void func_80714950(void *);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_80714998(s32);
void func_8071EDEC(void);
void effectPuffRiseUpdate(void);
extern void *D_8074E880[];

void bossSpawnSparkles(void) {
    f32 sparkX;
    f32 sparkY;
    f32 sparkZ;
    s16 i;

    actorGetNodePos(gCurrentActor, 1, &sparkX, &sparkY, &sparkZ);
    sparkX += (f32)(((randomNonNegative() >> 15) % 80) - 40);
    sparkY += (f32)(((randomNonNegative() >> 15) % 100) + 50);
    sparkZ += (f32)(((randomNonNegative() >> 15) % 80) - 40);
    func_807149B8(1);
    func_8071498C(func_8071EDEC);
    func_80714950(gCurrentActor);
    func_807149C8(0xFF, 0xD7, 0x58, 0xFF);
    func_80714CC0(D_80720120, 1.5f, sparkX, sparkY, sparkZ);
    for (i = 0; i < 4; i++) {
        func_80714998(2);
        func_8071498C(effectPuffRiseUpdate);
        func_807149B8(1);
        func_80714C08(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3], 1.5f, gCurrentActor, ((randomNonNegative() >> 15) % 32767 % 22) + 2, 0);
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

void bossClampPosition(s32 radius) {
    if (!polygonContainsPoint2D((s32)D_807FBB4C->unk7C, (s32)D_807FBB4C->unk84, radius)) {
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
extern s32 gCurrentMap;
extern s32 D_8076D1F8;
extern s32 gCamActor;
extern void *gSpawnedActor;
extern BossC_6240_BB70 D_807FBB70;
extern BossC_6240_C924 *gPlayerSlots;
extern BossC_6240_D580 *gActivePlayerState;
extern BossC_6240_DC90 *gBehaviourWorkState;
extern BossC_6240_DC94 *gBehaviourTargetActor;
extern BossC_6240_DC98 *gBehaviourAnimState;
extern BossC_6240_DC9C *gBehaviourExtraState;
extern BossC_6240_DCA0 *D_807FDCA0;

void bossInitScriptData(void *);
void bossScriptStep(u8 *, s32, f32);
void bossSpawnParticleRing(s32, s16, s16, s16, s32, s32);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void func_80613C48(void *, s16, f32, f32);
void scriptSetActorRampTarget(void *, f32, f32);
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
void csModelStateSetFirstByte(s16, s32);
f32 effectNodeGetValue(s32);
void waterRippleStop(void);
void actorApplyVelocityCustom(void *, f32, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void collisionCheckActorFloor(void *, f32, f32, f32, void *);
void actorGetOrSetNodeScale(void *, s32, f32);
s32 actorTableContains(void *);
void effectSpawnChildAtNode(s32, s16, s16);
void effectSpawnActorBoneEffects(s32);
void projectileGetTargetCoords(void *, s32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);
void projectileClampAngleAndSpawn(s16, s32, s32, s32, f32, f32, f32, f32, f32, void *);
void projectileSpawnWithShockwave(s32, f32, s32, s32, s32, s32, f32, f32, f32, f32);
void loadModelAssetTable(void);
void playerSetLargeModeScale(f32);
void playerSetSizeMode(void *, s32);
void slotQueueSetDisplayMode(s32, s32, s32);
void effectFreeAll(void);
void func_8072881C(s32, void *);
void behaviourFrameBegin(void);
void actorApplyGravity(void);
void actorTurnTowardTarget(s32, f32, f32, s32);
void func_8072A450(void);
s32 actorMoveWithinZone(s32, f32, f32, s32, f32);
void actorSetTargetSpeed(void *, u8);
s32 patrolPathStep(s32, s32);
s32 flagGet(s32, s32);
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, void *);
void n_alSndpStop(s32);


void bossPufftossStep(void) {
    BossC_6240_178 *state;
    BossC_6240_17C *state17C;
    u8 *scriptData;
    f32 prevY;
    u8 checkFloor;
    u8 updateY;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    u16 roll;
    s16 sndId;
    f32 floorCheckX;
    f32 floorCheckY;
    f32 floorCheckZ;

    state = gCurrentActor->unk178;
    state17C = gCurrentActor->unk17C;
    scriptData = D_80035A20[(gCurrentMap == 0xC5) ? 0 : 1][state->unk14];
    prevY = gCurrentActor->unk80;
    updateY = checkFloor = 1;
    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        camSetSecondTarget(gCamActor, 0, 0);
        slotQueueSetDisplayMode(5, 0, 1);
        currentActorClearFlag();
        playerSetLargeModeScale(1.2f);
        loadModelAssetTable();
        gCurrentActor->unkCC = 2;
        bossInitScriptData(&D_800362F0);
        gBehaviourAnimState->unk30 = 3.0f;
        gCurrentActor->unkB8 = 0.0f;
        gCurrentActor->unk60 |= 0x800000;
        gBehaviourAnimState->unk46 |= 0x20;
        state->unk1C = 0;
        gCurrentActor->unk154 = scriptData[state->unk15++];
        gCurrentActor->unk155 = 0;
    }
    gActivePlayerState->unkD4 = (gActivePlayerState->unkD4 < 50) ? gActivePlayerState->unkD4 : 50;
    gCurrentActor->unk16A = (u8) (((f64) mathSinF((s16) (gFrameCounter * 0x64)) * 50.0) + 200.0);
    gCurrentActor->unk16B = gCurrentActor->unk16A;
    gCurrentActor->unk16C = gCurrentActor->unk16A;
    if (gCurrentActor->unk154 == 0x55) {
        gCurrentActor->unk132 = 2;
    } else {
        gCurrentActor->unk132 = 1;
    }
    gCurrentActor->unk144 = 0x24;
    if (D_807FBB70.unk200 == 4) {
        if (state->unk14 == 3) {
            actorGetOrSetNodeScale(gCurrentActor, 1, 200.0f);
            bossPufftossNotifyLaser(0);
            gCurrentActor->unk154 = 0x56;
            gCurrentActor->unk155 = 0;
            actorScriptStart(gCurrentActor, 0x2D1);
            gBehaviourWorkState->unk2C = 0x12C;
        } else {
            effectFreeAll();
            waterRippleStop();
            gCurrentActor->unk154 = 0x4D;
            gCurrentActor->unk155 = 0;
            gCurrentActor->unkC4 = (f32) D_807502FC;
            actorScriptStart(gCurrentActor, 0x2CD);
            gBehaviourWorkState->unkC = -0x2BC;
            state->unk15 = 0;
            state->unk14++;
            scriptData = D_80035A34[state->unk14];
            if ((state->unk14 == 3) && (gCurrentMap == 0xC5)) {
                camStartPath(gCurrentActor, 8, 1);
            } else {
                camStartPath(gCurrentActor, 2, 1);
            }
        }
    } else if ((D_807FBB70.unk200 == 5) && (gPlayerSlots->unk2C0 != 1)) {
        sndId = 0x14B;
        actorScriptStart(gCurrentActor, 0x2D2);
        actorGetNodePos(gCurrentActor, 2, &nodeX, &nodeY, &nodeZ);
        if (gCurrentActor->unk134 == 1) {
            gBehaviourWorkState->unk1A |= 0x8000;
        }
        gBehaviourWorkState->unk16 = (s16) (*gBehaviourTargetActor->unk4)->unk10;
        gCurrentActor->unk60 |= 0x20000000;
        func_80714CC0(&D_8071FB34, 2.0f, ((randomNonNegative() >> 0xF) % 30 + nodeX) - 15.0f, ((randomNonNegative() >> 0xF) % 30 + nodeY) - 15.0f, ((randomNonNegative() >> 0xF) % 30 + nodeZ) - 15.0f);
        sfxPlayOnFreeSlot(0x1CA, 0x7FFF, 63.0f, 1.0f, 0, 0);
        roll = (randomNonNegative() >> 0xF) % 2048;
        if (roll < 0x2A8) {
            sndId = 0x14E;
        } else if (roll < 0x550) {
            sndId = 0x14D;
        }
        if (state->unk1C != 0) {
            n_alSndpStop(state->unk1C);
        }
        n_alSndpPlay(D_8076D1F8, sndId, 0x7FFF, 0x3F, 1.0f, 0, &state->unk1C);
    } else if (((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0)) && (actorTableContains(D_807FBB70.unk1FC) != 0) && (D_807FBB70.unk1FC->unk5C == 1)) {
        playerSetSizeMode(D_807FBB4C, 2);
        bossPufftossNotifyLaser(1);
        csModelStateSetFirstByte(0, 0xA);
        camSetFollowMode(gCamActor);
        camStartPath(gCurrentActor, 8, 1);
        gCurrentActor->unk154 = 0x37;
        gCurrentActor->unk155 = 0;
        gCurrentActor->unk60 &= ~4;
    }
    if (!(state->unk12 & 1) && (effectNodeGetValue(1) > 640.0f) && (D_807FBB4C->unk154 != 0x42)) {
        if (gPlayerSlots->unk2C0 != 1) {
            playerSetSizeMode(D_807FBB4C, 1);
            gActivePlayerState->unk1D8 = 0.1f;
        }
        camStartPath(gCurrentActor, 0xA, 1);
        state->unk12 |= 1;
        state->unk14 = 4;
        state->unk15 = 0;
        scriptData = D_80035A20[(gCurrentMap == 0xC5) ? 0 : 1][state->unk14];
        gCurrentActor->unk154 = scriptData[state->unk15];
        state->unk15 += 1;
        gCurrentActor->unk155 = 0;
    }
    switch (gCurrentActor->unk154) {
    case 0x6A:
        break;
    case 0x56:
        updateY = 0;
        gCurrentActor->unk132 = 4;
        actorMoveWithinZone(0x45, 606.0f, 566.0f, 0x292, 0.0f);
        if (gCurrentActor->unk155 == 1) {
            bossClampPosition((s32)D_807FDCA0->unk24);
        }
        if ((gCurrentActor->unk155 == 0) && (D_807FBB4C->unk154 == 0x42)) {
            gCurrentActor->unk155 = 1;
            camSetTarget(gCamActor, gCurrentActor, 4, 0xD48, 0x320, 0, 0, 0xC8, 0x64, 0, 0.03f);
            camSetTargetFocusActor(gCamActor, D_807FBB4C);
        }
        if (!(gBehaviourWorkState->unk1A & 0x8000)) {
            if (gBehaviourWorkState->unk2C != 0) {
                if (gBehaviourWorkState->unk2C == 100) {
                    bossPufftossNotifyLaser(2);
                }
                if (gBehaviourWorkState->unk2C < 21) {
                    gCurrentActor->unk60 |= 0x20000000;
                }
                if (gBehaviourWorkState->unk2C == 20) {
                    if (gPlayerSlots->unk2C0 != 1) {
                        gActivePlayerState->unkD4 = 0x64;
                    }
                    camReturnToFollow(gCamActor, D_807FBB4C);
                    playerSetSizeMode(D_807FBB4C, 1);
                    gActivePlayerState->unk1D8 = 0.04f;
                }
                gBehaviourWorkState->unk2C--;
            } else {
                gCurrentActor->unk60 &= 0xDFFFFFFF;
                actorGetOrSetNodeScale(gCurrentActor, 1, 64.0f);
                bossPufftossNotifyLaser(1);
                state->unk15 = state->unk16;
                gCurrentActor->unk154 = scriptData[state->unk15++];
                gCurrentActor->unk155 = 0;
            }
        }
        break;
    case 0x37:
        checkFloor = 0;
        updateY = 0;
        gCurrentActor->unk132 = 4;
        bossClampPosition((s32)D_807FDCA0->unk24);
        if ((gCurrentActor->unk155 == 0) && (currentActorTestClearFlag() != 0)) {
            gCurrentActor->unk155 += 1;
            bossSpawnParticleRing(0xEC, D_807FDCA0->unk14->unkA0, D_807FDCA0->unk14->unkA2 + 0x14, D_807FDCA0->unk14->unkA4, 0x5DC, 4);
        }
        break;
    case 0x27:
        updateY = 0;
        switch (gCurrentActor->unk155) {
        case 0:
            if ((gCurrentMap == 0xC5) || (flagGet(0x69, 2) != 0)) {
                if (gCurrentMap == 0xC5) {
                    gCurrentActor->unk60 &= ~4;
                } else {
                    actorScriptStart(gCurrentActor, 0x2C6);
                }
                gCurrentActor->unk155 = 6;
            } else {
                func_80613C48(gCurrentActor, 0x539, 0, 0);
                scriptSetActorRampTarget(gCurrentActor, 0, 0);
                gCurrentActor->unk155 = 1;
            }
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gCurrentActor, 0x2C4);
                scriptSetActorRampTarget(gCurrentActor, 0.5f, 0);
                gCurrentActor->unk155 = 2;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                gBehaviourWorkState->unkC = 0x1F4;
                actorScriptStart(gCurrentActor, 0x2C5);
                gCurrentActor->unk155 = 4;
            }
            break;
        case 5:
            if ((gCurrentActor->unkA4 + 180.0f) < gCurrentActor->unk80) {
                gCurrentActor->unk154 = 0x11;
                gCurrentActor->unk155 = 0;
            }
            gCurrentActor->unk80 += ((gCurrentActor->unkA4 + 200.0f) - gCurrentActor->unk80) * 0.12;
            break;
        case 6:
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->unk154 = scriptData[state->unk15++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x2B:
        gCurrentActor->unk132 = 2;
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x2CF);
            gCurrentActor->unk155 = 1;
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                csModelStateSetFirstByte(0, 1);
                gCurrentActor->unk154 = scriptData[state->unk15++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x29:
        gCurrentActor->unk132 = 2;
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x2CE);
            gCurrentActor->unk155 = 1;
            break;
        case 2:
            sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x14A, 0xFF, 0x7F, 0, 0, 0, 0);
            sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x221, 0xFF, 0x7F, 0, 0, 0, 0);
            projectileSpawnWithShockwave(0xBB, 0.14f, 0xFF, 0x96, 0x64, 6, 1.04f, 40.0f, 8.0f, 600.0f);
            func_80613C48(gSpawnedActor, 0x4F9, 0, 0);
            scriptSetActorRampTarget(gSpawnedActor, 0.5f, 0);
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x28:
        actorTurnTowardTarget(0x23, 606.0f, 566.0f, 0);
        switch (gCurrentActor->unk155) {
        case 0:
            gBehaviourWorkState->unk25 += 4;
            patrolPathStep(0x42, 0);
            gBehaviourWorkState->unk25 -= 4;
            actorScriptStart(gCurrentActor, 0x2CB);
            gCurrentActor->unk155 = 1;
            gBehaviourWorkState->unk2C = 0;
            break;
        case 2:
            effectSpawnChildAtNode(2, (s16) ((((s32) (randomNonNegative() >> 0xF) % 2048) + gCurrentActor->unkE6) - 0x400), (s16) ((s32) (randomNonNegative() >> 0xF) % 2048));
            /* fallthrough */
        case 3:
            bossSpawnSparkles();
            break;
        case 5:
            projectileGetTargetCoords(gCurrentActor, 1);
            if (gBehaviourWorkState->unk2C != 0) {
                projectileAimAndSpawn(0x51, 1, (f32) (((f64) ((s32) (randomNonNegative() >> 0xF) % 10) / 20.0) + 0.8), (f32) gBehaviourWorkState->unkA, (f32) gBehaviourWorkState->unkC, (f32) gBehaviourWorkState->unkE, 500.0f, gCurrentActor);
            } else {
                projectileAimAndSpawn(0x1E, 0x14, 0.2f, (f32) gBehaviourWorkState->unkA, (f32) gBehaviourWorkState->unkC, (f32) gBehaviourWorkState->unkE, 500.0f, gCurrentActor);
            }
            gBehaviourWorkState->unk2C = 1;
            break;
        case 7:
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x2A:
    case 0x2C:
        updateY = 0;
        gCurrentActor->unk132 = 2;
        switch (gCurrentActor->unk155) {
        case 0:
            gBehaviourWorkState->unk25 += 4;
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:
            actorMoveWithinZone(0x42, (f32) gBehaviourWorkState->unkA, (f32) gBehaviourWorkState->unkE, 0x291, 0.0f);
            if (patrolPathStep(0x42, 0) != 0) {
                gCurrentActor->unkC0 = 100.0f;
                actorScriptStart(gCurrentActor, 0x2C8);
                gCurrentActor->unk155 = 2;
                gBehaviourWorkState->unk25 -= 4;
                if (gCurrentActor->unk154 == 0x2C) {
                    camStartPath(gCurrentActor, 6, 1);
                }
            }
            break;
        case 2:
            actorMoveWithinZone(0x45, 606.0f, 566.0f, 0x292, 0.0f);
            break;
        case 3:
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x48:
        gCurrentActor->unk132 = 2;
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x2C9);
            gBehaviourWorkState->unk2C = (s16) *(state->unk15 + scriptData);
            state->unk15 += 1;
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:
            if (gBehaviourWorkState->unk2C != 0) {
                gBehaviourWorkState->unk2C--;
            } else {
                gCurrentActor->unk154 = scriptData[state->unk15++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x43:
        gCurrentActor->unk132 = 2;
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x2CA);
            gCurrentActor->unk155 = 1;
            break;
        case 2:
            if ((gCurrentActor->unkA4 + 180.0f) < gCurrentActor->unk80) {
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkC);
                gCurrentActor->unk154 = scriptData[state->unk15++];
                gCurrentActor->unk155 = 0;
            }
            gCurrentActor->unk80 += ((gCurrentActor->unkA4 + 200.0f) - gCurrentActor->unk80) * 0.12;
            updateY = 0;
            break;
        }
        break;
    case 0x11:
        actorMoveWithinZone(0x45, gBehaviourTargetActor->unk7C, gBehaviourTargetActor->unk84, 0x293, 0.0f);
        if (currentActorTestClearFlag() != 0) {
            gCurrentActor->unk154 = scriptData[state->unk15++];
            gCurrentActor->unk155 = 0;
        }
        break;
    case 0x46:
        actorMoveWithinZone(0x45, gBehaviourTargetActor->unk7C, gBehaviourTargetActor->unk84, 0x293, 0.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            state->unk18 = scriptData[state->unk15++];
            state17C->unk6 = (s16) (mathAngleBetweenPoints2D(606.0f, 566.0f, gCurrentActor->unk7C, gCurrentActor->unk84) + 0x400);
            gCurrentActor->unk155 = 1;
            /* fallthrough */
        case 1:
            actorScriptStart(gCurrentActor, 0x2C7);
            gCurrentActor->unk155 = 2;
            break;
        case 2:
            bossPufftossSpawnGlow(0, (f32) (((f64) gCurrentActor->unk4->unk0->unk4 * 0.06) + 2.0));
            break;
        case 3:
            projectileGetTargetCoords(gCurrentActor, 1);
            projectileClampAngleAndSpawn(gCurrentActor->unkE6, 0x320, 0x1E, 0xB, 1.2f, gBehaviourTargetActor->unk7C, gBehaviourTargetActor->unk80 + 30.0f, gBehaviourTargetActor->unk84, (f32) ((state->unk14 * 0x50) + 0x2BC), gCurrentActor);
            gCurrentActor->unk155 = 4;
            break;
        case 5:
            if (state->unk18--) {
                gCurrentActor->unk155 = 1;
            } else {
                gCurrentActor->unk154 = scriptData[state->unk15++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        bossPufftossBobStep();
        break;
    case 0x4D:
        updateY = 0;
        switch (gCurrentActor->unk155) {
        case 1:
            bossPufftossSpawnGlow(3, 3.0f);
            break;
        case 2:
            checkFloor = 0;
            actorApplyGravity();
            gCurrentActor->unk80 = (f32) (gCurrentActor->unk80 + gCurrentActor->unkC0);
            if (gCurrentActor->unk80 < (f32) gBehaviourWorkState->unkC) {
                gCurrentActor->unk155 = 3;
                sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0xC, 0xFF, 0x50, 0, 0, 0, 0);
            }
            if ((gCurrentMap == 0xC5) && (state->unk14 == 3) && (currentActorTestClearFlag() != 0)) {
                bossSpawnParticleRing(0x4A, D_807FDCA0->unk14->unkA0, D_807FDCA0->unk14->unkA2 + 0x14, D_807FDCA0->unk14->unkA4, 0x5DC, 4);
            }
            break;
        case 3:
            checkFloor = 0;
            if (currentActorTestClearFlag() != 0) {
                if ((gCurrentMap == 0xC5) && (state->unk14 == 3)) {
                    gCurrentActor->unk154 = 0x37;
                    gCurrentActor->unk155 = 1;
                } else {
                    gCurrentActor->unkC4 = (f32) D_807502E8;
                    actorScriptStart(gCurrentActor, 0x2CC);
                    gCurrentActor->unk155 = 4;
                    gBehaviourWorkState->unkC = 0xC8;
                }
            }
            break;
        case 4:
            effectSpawnActorBoneEffects(0);
            checkFloor = 0;
            gCurrentActor->unk80 = ((gBehaviourWorkState->unkC + 5) - gCurrentActor->unk80) * 0.12 + gCurrentActor->unk80;
            actorTurnTowardTarget(0x23, gBehaviourTargetActor->unk7C, gBehaviourTargetActor->unk84, 0);
            if ((gBehaviourWorkState->unkC - 300) < gCurrentActor->unk80) {
                if (gCurrentActor->unk6E == -1) {
                    sfxPlayActorSound(gCurrentActor, 0x10F, 0, 1, 0, 0xFF, 0.8f, 0);
                }
                func_80613C48(gCurrentActor, 0x53D, 0, 24.0f);
            }
            if (gBehaviourWorkState->unkC < gCurrentActor->unk80) {
                actorScriptStart(gCurrentActor, 0x2D0);
                gCurrentActor->unk155 = 5;
            }
            break;
        case 5:
            effectSpawnActorBoneEffects(0);
            break;
        case 6:
            effectSpawnActorBoneEffects(1);
            break;
        case 7:
            actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkC);
            gCurrentActor->unk154 = 0x11;
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x42:
        gCurrentActor->unk144 = 1;
        if (gCurrentActor->unk4->unk64 != 0x2C6) {
            actorScriptStart(gCurrentActor, 0x2C6);
        }
        /* fallthrough */
    default:
        bossScriptStep(scriptData, 0x291, 0);
        break;
    }
    if (updateY != 0) {
        if (gCurrentActor->unk80 < gBehaviourWorkState->unkC) {
            gCurrentActor->unk80 = (gBehaviourWorkState->unkC - prevY) * 0.03 + prevY;
            gCurrentActor->unkC0 = 0.0f;
        } else {
            actorApplyGravity();
            if ((f32) gBehaviourWorkState->unkC < gCurrentActor->unk80) {
                actorApplyVelocityCustom(gCurrentActor, 0, gCurrentActor->unkC0);
            }
        }
    }
    func_8072881C(0, gBehaviourWorkState->unk28);
    if (checkFloor != 0) {
        actorGetNodePos(gCurrentActor, gCurrentActor->unkCC, &floorCheckX, &floorCheckY, &floorCheckZ);
        collisionCheckActorFloor(gCurrentActor, floorCheckX, floorCheckY, floorCheckZ, &gCurrentActor->unkA4);
        func_8072A450();
    }
    if (camIsCutsceneActive() != 0) {
        gCurrentActor->unk144 = 1;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
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
