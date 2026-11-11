#include "common.h"
#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_sfxPlayAtPositionPooled // FAKE: callee prototype steer
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/5E2F0.h"
#include "proto/global/684C0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8CA50.h"
#include "proto/global/A2F10.h"

typedef struct ScaleTierTable {
    f32 arr[3];
} ScaleTierTable;

typedef struct ScaleGrowthState {
    f32 baseScaleY;
    u16 growthTicks;
    u8 tierIndex;
} ScaleGrowthState;

typedef struct EffectOwnerView {
    u8 pad[0x338];
    void *ownerActor;
} EffectOwnerView;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern ScaleTierTable D_8074E88C;
extern void *D_8074E880[];
extern u32 gFrameCounter;
extern u8 D_80750AD0;
extern s32 D_8071FC0C;
extern s32 D_8071FE08;
extern s32 D_8071FED0;
extern s32 D_8071FF18;
extern s32 D_8071FF40;
extern s32 sEffectSparkConfig;
extern s32 D_8072006C;
extern s32 D_80720120;
extern s32 D_80720558;
extern s32 D_8072073C;
extern s32 D_80720B58;
extern s32 D_807210EC;
extern s32 D_80721158;
extern s32 D_8072139C;


void effectSpawnActorBone(Actor *owner, u8 bone, f32 scale) {
    effectSetDepth(1);
    effectSetCallback(effectFollowParentUpdate);
    effectSetSpeed((s32)owner);
    effectSetFlags(4);
    effectCreateAtActorBone(&D_80720120, scale, gCurrentActor, bone, 0);
}

void effectSpawnRandomBoneDebris(u8 minBone, u8 maxBone) {
    f32 scale;
    u8 bone;

    if (!(gFrameCounter & 3)) {
        scale = gCurrentActor->sub4->scaleY / 0.15;
        bone = ((randomNonNegative() >> 15) % 0x7FFF) % ((maxBone - minBone) + 1) + minBone;
        effectSetMode(3);
        effectSetColor(0xE6, 0xE6, 0xE6, 0xE6);
        effectSpawnBoneDefault(gCurrentActor, bone, scale, 0.0f, 0.0f, 0.0f, -0x78);
    }
}

void actorSpawnEffectChild(f32 posX, f32 posY, f32 posZ, f32 scaleXZ, f32 scaleY, Actor *parent, u8 fastGrow) {
    s32 actorType = 0xAD;

    if (parent != NULL) {
        switch (parent->actorType) {
        case 5:
        case 0xF4:
            actorType = 0xD1;
            break;
        case 4:
        case 0xF3:
            actorType = 0xD0;
            break;
        case 6:
        case 0xF5:
            actorType = 0xCF;
            break;
        case 3:
        case 0xF2:
            actorType = 0xAE;
            break;
        }
    }
    actorSpawn(0xFF, actorType);
    gSpawnedActor->parentActor = parent;
    gSpawnedActor->sub4->scaleX = scaleXZ;
    gSpawnedActor->sub4->scaleZ = scaleXZ;
    gSpawnedActor->sub4->scaleY = scaleY;
    gSpawnedActor->x = posX;
    gSpawnedActor->y = posY;
    gSpawnedActor->z = posZ;
    if ((parent != NULL) && (parent->collisionFlags & 1)) {
        if (fastGrow != 0) {
            gSpawnedActor->yawSpeed = 0xF;
            gSpawnedActor->splineT = 1.11;
            gSpawnedActor->unk15F = 1;
        } else {
            gSpawnedActor->yawSpeed = 0x19;
            gSpawnedActor->splineT = 1.09;
        }
    } else {
        gSpawnedActor->yawSpeed = 0x20;
        gSpawnedActor->splineT = 1.07;
        gSpawnedActor->unk15F = 0;
    }
}

extern s32 D_8071FF58;

void effectSpawnSmoke(u8 bone) {
    if (!(gFrameCounter & 0x1F)) {
        effectSetMode(2);
        effectSetDepth(1);
        effectSetDuration(0x3C);
        effectSetCallback(effectWobbleScaleUpdate);
        if (bone) {
            effectCreateAtActorBone(&D_8071FF58, 0.05f, gCurrentActor, bone, 0);
        } else {
            effectCreateAtPosition(&D_8071FF58, 0.05f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
    }
}

void effectSpawnBurst(u8 useAltRange) {
    if (useAltRange) {
        effectSetSpeed(((randomNonNegative() >> 15) % 10) + 0x8008);
    } else {
        effectSetSpeed(((randomNonNegative() >> 15) % 8) + 6);
    }
    effectSetDuration(2);
    effectSetCallback(func_80717930);
    effectSetDepth(1);
    effectSetFlags(4);
    effectCreateAtActorBone(&D_8072139C, (f32)(((f64)((randomNonNegative() >> 15) % 50) / 80.0) + 0.1), gCurrentActor, 8, 0);
}

void effectSpawnBoneDebris(s16 bone, s8 direction) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    f32 scale;

    scale = (f32)(gCurrentActor->sub4->scaleY / 0.15);
    actorGetNodePos(gCurrentActor, bone, &nodeX, &nodeY, &nodeZ);
    effectSetSpeed((((randomNonNegative() >> 15) % 100) + 0x190) * direction);
    effectSetCallback(func_80717D4C);
    effectSetDepth(1);
    effectCreateAtPosition(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3],
                   (f32)((f64)scale * 0.8),
                   (f32)((randomNonNegative() >> 15) % 20) + (nodeX - 10.0f),
                   nodeY,
                   (f32)((randomNonNegative() >> 15) % 20) + (nodeZ - 10.0f));
}


void effectSpawnBoneDebrisScaled(s16 bone, s16 baseSpeed, s16 lifetime) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    f32 scale;
    f64 duration;

    scale = (f32)((f64)gCurrentActor->sub4->scaleY / 0.15);
    actorGetNodePos(gCurrentActor, bone, &nodeX, &nodeY, &nodeZ);
    effectSetSpeed(baseSpeed + (lifetime << 16));
    effectSetCallback(func_8071F2F8);
    effectSetDepth(1);
    if (((f64)lifetime * 0.02) < 2.0) {
        duration = 2.0;
    } else {
        duration = (f64)lifetime * 0.02;
    }
    effectSetDuration((s32)duration);
    effectCreateAtPosition(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3],
                   (f32)((f64)scale * 0.8),
                   (f32)((randomNonNegative() >> 15) % 60) + (nodeX - 30.0f),
                   nodeY,
                   (f32)((randomNonNegative() >> 15) % 60) + (nodeZ - 30.0f));
}

extern s32 D_8071FC40;

void effectSpawnAuraBurst(u8 rate) {
    u32 i;
    f32 x, y, z;

    if ((((u32)randomLcgNext() / 10000) % rate) == 0) {
        if (D_80750AD0 == 0) {
            for (i = 0; i < 4; i++) {
                x = (f32)(((f64)(f32)((u32)randomLcgNext() / 10000 % 200) / 10.0) - 5.0);
                y = (f32)(((f64)(f32)((u32)randomLcgNext() / 10000 % 200) / 10.0) - 5.0);
                z = (f32)(((f64)(f32)((u32)randomLcgNext() / 10000 % 200) / 10.0) - 5.0);
                effectSetDepth(1);
                effectSetSpeed(1);
                effectSetDuration(-1);
                effectSetCallback(effectWobbleRiseUpdate);
                effectSetFlags(4);
                effectCreateAtPosition(&D_8071FC40, 0.0f, gCurrentActor->x + x, gCurrentActor->y + y, gCurrentActor->z + z);
            }
        }
    }
}

void effectSpawnSparks(u8 frameMask, u8 bone) {
    if (!(frameMask & gFrameCounter)) {
        effectSetCallback(effectWobbleRiseUpdate);
        effectSetDepth(1);
        effectSetDuration(-1);
        effectSetFlags(4);
        if (bone) {
            effectCreateAtActorBone(&D_8071FC40, 0.0f, gCurrentActor, bone, 0);
        } else {
            effectCreateAtPosition(&D_8071FC40, 0.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
    }
}

void effectSpawnRing(void) {
    f32 scale;
    s32 i;

    scale = (f32)(gCurrentActor->sub4->scaleY / 0.15);
    effectSetDepth(0);
    effectSetDuration(1);
    effectCreateAtPosition(&D_8071FE08, (f32)((f64)scale * 0.75), gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    for (i = 0; i < 7; i++) {
        effectSetDepth(1);
        effectSetDuration(0xA);
        effectSetCallback(effectTumbleBounceUpdate);
        effectSetMode(2);
        effectSetSpeed(0);
        effectCreateAtPosition(&D_8072073C, (f32)((f64)scale * 0.15), gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    }
}

void func_80685210(f32 scale, s16 speedThreshold, s16 bone) {
    if (((gFrameCounter % 3) == 0) && ((f32)speedThreshold < gCurrentActor->speedXZ)) {
        effectSetMode(2);
        effectSetDepth(1);
        effectSetCallback(func_80717D4C);
        effectSetSpeed(-0x32);
        effectSetFlags(4);
        effectCreateAtActorBone(&D_8071FF18, scale, gCurrentActor, bone, 0);
    }
}

void effectSpawnOctagonRing(f32 scale, f32 posX, f32 posY, f32 posZ) {
    s16 sector;

    for (sector = 0; sector < 8; sector++) {
        effectSetCallback(effectDecelerateDriftUpdate);
        effectSetSpeed(sector);
        effectSetDepth(1);
        effectSetColor(0xFF, 0xFF, 0xFF, 0xC8);
        effectCreateAtPosition(&sEffectSparkConfig, scale, posX, posY, posZ);
    }
}

void actorScaleGrowthUpdate(void) {
    ScaleGrowthState *extraData = gCurrentActor->customState;
    ScaleTierTable scales = D_8074E88C;

    if (!(gCurrentActor->flags & 0x10)) {
        extraData->baseScaleY = gCurrentActor->sub4->scaleY;
    }
    extraData->growthTicks++;
    switch (gCurrentActor->state) {
    case 0:
        gCurrentActor->sub4->scaleY = scales.arr[extraData->tierIndex] * (extraData->baseScaleY * (f32)(u32)extraData->growthTicks * 0.33333334f);
        if ((f32)(u32)extraData->growthTicks > 3.0f) {
            gCurrentActor->state = 1;
            extraData->growthTicks = 0;
            animSetLoopLimit(gCurrentActor, 0, 1);
            animSetSpeed(gCurrentActor, 0, 0.5f);
        }
        break;
    case 1:
        if (animIsPlaying(gCurrentActor, 0) == 0) {
            actorDespawn(gCurrentActor);
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void effectSpawnMultiTierRing(f32 scale, u8 tier, f32 posX, f32 posY, f32 posZ) {
    s32 sector;

    if (D_80750AD0 == 0) {
        if (tier > 0) {
            effectSpawnOctagonRing(scale, posX, posY, posZ);
        }
        if (tier >= 2) {
            for (sector = 0; sector < 8; sector++) {
                effectSetCallback(timedEffectCountdownTick);
                effectSetSpeed(sector);
                effectSetDepth(1);
                effectSetDuration(-1);
                effectSetColor(0xFF, 0xFF, 0xFF, 0xFF);
                effectCreateAtPosition(&D_8071FF40, (f32)((f64)scale * 0.5), posX, posY, posZ);
            }
        }
        if (tier >= 3) {
            for (sector = 0; sector < 9; sector++) {
                effectSetCallback(effectSpiralRiseUpdate);
                effectSetSpeed(sector);
                effectSetDepth(1);
                effectSetDuration(-1);
                effectSetColor(0xFF, 0xFF, 0xFF, 0xFF);
                effectCreateAtPosition(D_8074E880[sector % 3], scale, posX, posY, posZ);
            }
        }
    }
}

typedef struct MultiTierRingParams {
    s32 a[4];
} MultiTierRingParams;

extern MultiTierRingParams D_8074E898;

void effectSpawnMultiTierRingWithActor(Actor *actor, u8 tier) {
    s32 pad0[1];
    MultiTierRingParams params;
    f32 actorScale;
    ScaleGrowthState *growthState;
    s32 pad1[1];

    actorScale = actor->sub4->scaleY / 0.15;
    params = D_8074E898;
    if (tier) {
        effectSpawnMultiTierRing(actorScale * 0.36, tier, actor->x, actor->y + 4.0f, actor->z);
        actorSpawn(0x145, params.a[tier]);
        actorCopyPoseAndScale(gSpawnedActor, actor, actor->sub4->scaleY * 0.5f);
        growthState = gSpawnedActor->customState;
        growthState->tierIndex = tier - 1;
    }
}

void effectSpawnBoneWhite(Actor *actor, s16 bone, f32 scale, f32 posX, f32 posY, f32 posZ, s32 moveSpeed) {
    effectSetMode(2);
    effectSetColor(0xFF, 0xFF, 0xFF, 0xC8);
    effectSpawnBoneDefault(actor, bone, scale, posX, posY, posZ, moveSpeed);
}

void effectSpawnBoneDefault(Actor *actor, s16 bone, f32 scale, f32 posX, f32 posY, f32 posZ, s32 moveSpeed) {
    effectSetDepth(1);
    effectSpawnBone(actor, bone, scale, posX, posY, posZ, moveSpeed);
}

void effectSpawnBone(Actor *actor, s16 bone, f32 scale, f32 posX, f32 posY, f32 posZ, s32 moveSpeed) {
    EffectOwnerView *effect;

    if (actor != NULL && bone != 0) {
        actorGetNodePos(actor, bone, &posX, &posY, &posZ);
    }
    effectSetCallback(effectShrinkAndVelocityUpdate);
    effectSetSpeed(moveSpeed);
    effect = effectCreateAtPosition(&sEffectSparkConfig, scale, posX, posY + 5.0f, posZ);
    effect->ownerActor = actor;
}

void effectSpawnScatter(f32 scale, f32 posX, f32 posY, f32 posZ) {
    s32 pad[2];
    s32 randX;
    if (((randomNonNegative() >> 15) % 100) >= 51) {
        effectSetMode(2);
        effectSetSpeed((randomNonNegative() >> 15) % 360);
        effectSetDepth(1);
        effectSetColor(0x9B, 0x9B, 0x9B, 0xC8);
        effectSetCallback(effectSpriteMotionUpdate);
        randX = randomNonNegative();
        effectCreateAtPosition(&sEffectSparkConfig, scale, (f32)(((randX >> 15) % 100000) % 10) + (posX - 5.0f), posY, (f32)(((randomNonNegative() >> 15) % 100000) % 10) + (posZ - 5.0f));
    }
}

void effectSpawnScatterRandom(void *texture, u8 colorMode, f32 scale, u8 count, u8 spread, s16 baseSpeed, s16 posX, s16 posY, s16 posZ) {
    s16 idx;
    s8 dx;
    s8 dz;

    for (idx = 0; idx < count; idx++) {
        dx = ((randomNonNegative() >> 15) % 32767 % (spread * 2)) + (-spread);
        dz = ((randomNonNegative() >> 15) % 32767 % (spread * 2)) + (-spread);
        effectSetSpeed(-baseSpeed - ((randomNonNegative() >> 15) % 80));
        effectSetCallback(func_807180F4);
        effectSetDepth(1);
        effectSetMode(2);
        if (colorMode) {
            effectSetAngle((s16)colorMode);
        }
        effectCreateAtPosition(texture, scale, (f32)(posX + dx), (f32)posY, (f32)(posZ + dz));
    }
}

void actorUpdateEffects(Actor *actor) {
    if (!(actor->renderFlags & 4)) {
        if ((actor->flags & 0x10) && ((actor->contactFlags ^ actor->prevContactFlags) & 4)) {
            effectSpawnDebrisParticles(actor, 0.0f, actor->x, actor->waterY, actor->z);
        }
        if (actor->contactFlags & 4) {
            effectActorCheckGroundScaleSpawn(actor);
        }
    }
    if ((actor->flags2 & 0x40) && func_80665AAC(actor) && !(actor->contactFlags & 0x800) && (actor->floorY <= actor->y)) {
        actorSpawnAttachedTo(actor);
    }
    if (actor->flags2 & 0x80) {
        triggerZoneCheckEntry(actor);
    }
}

void effectSpawnActorScale(Actor *actor) {
    s32 pad;
    f32 scale;

    scale = (actor->sub4 != NULL) ? (f64)actor->sub4->scaleY / 0.15 : 1.0;
    effectSetMode(3);
    effectSetDepth(1);
    effectSetDuration(1);
    effectSetCallback(effectGroundDecalSpinUpdate);
    effectSetFlags(4);
    effectSetColor(0xC8, 0xFF, 0xFF, 0xC8);
    ((EffectOwnerView *)effectCreateAtPosition(&D_8071FED0, (f64) scale * 0.6, actor->x, actor->waterY, actor->z))->ownerActor = actor;
}

extern PlayerStruct *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s16 D_80753A08[];
extern s16 D_80753A18[];

void effectActorCheckGroundScaleSpawn(Actor *actor) {
    f32 floorYOffset;
    u8 shouldSpawn;
    shouldSpawn = 0;
    if (actor->animState != NULL && actor->sub4 != NULL) {
        if (actor->collisionFlags == 1) {
            if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
                floorYOffset = D_80753A08[actor->actorType];
            } else {
                floorYOffset = D_80753A18[actor->actorType];
            }
        } else {
            floorYOffset = (f32)(u32)actor->eyeHeight;
        }
        if ((actor->waterY - floorYOffset) <= actor->y) {
            if (!(gFrameCounter & 3)) {
                shouldSpawn = (f64)actor->speedXZ != 0.0;
                if (actor->pathFollow != NULL && actor->pathFollow->unk10 != 0) {
                    shouldSpawn = 1;
                }
            }
            if (shouldSpawn) {
                effectSetSpeed(1);
            } else if (((f64)actor->speedXZ == 0.0) && ((gFrameCounter % 24 == 0) || ((f64)actor->prevSpeedXZ != 0.0))) {
                shouldSpawn = 1;
            }
            if (shouldSpawn) {
                effectSpawnActorScale(actor);
            }
        }
    }
}

void effectSpawnBurstParticles(Actor *actor) {
    f32 scale;
    f32 scale01;
    u8 count;
    u8 i;

    scale = (actor->sub4 != NULL) ? (f64)actor->sub4->scaleY / 0.15 : 1.0;
    if (actor->actorType == 0x1E) {
        scale *= 2;
        effectSpawnBoneDefault(actor, 0, 4.0f, actor->x, actor->y, actor->z, -0x96);
        actorDespawn(actor);
    }
    sfxPlayFromActorWithAltitudeCheck(actor, 0xC, 0xFF, 0x7F, 1);
    effectSetDepth(1);
    effectSetDuration(1);
    effectSetColor(0xFF, 0xFF, 0xFF, 0xFF);
    effectCreateAtPosition(&D_8071FC0C, (f64)scale * 0.65, actor->x, actor->waterY + 15.0f, actor->z);
    if (D_80750AD0 == 0) {
        count = (randomLcgNext() & 3) + 4;
        i = 0;
        if (count > 0) {
            scale01 = (f64)scale * 0.1;
            do {
                effectSetDepth(1);
                effectSetDuration(-1);
                effectSetCallback(effectFloorFallUpdate);
                effectSetFlags(4);
                effectCreateAtPosition(&D_80720B58, scale01, actor->x, actor->waterY, actor->z);
                i++;
            } while (i < count);
        }
    }
}

void particleInitDefaultState(void) {
    effectSetDepth(1);
    effectSetDuration(0x14);
    effectSetCallback(effectFadeOutMatrixUpdate);
    effectSetColor(0xFF, 0xFF, 0xFF, 0xC8);
    effectSetFlags(4);
}

extern s32 D_8071FBF4;

void effectSpawnDebrisParticles(Actor *actor, f32 scaleParam, f32 posX, f32 posY, f32 posZ) {
    f32 f;
    f32 scale;

    if (actor != NULL) {
        scale = (actor->sub4 != NULL) ? (f64)actor->sub4->scaleY / 0.15 : 1.0;
        if (actor->contactFlags & 4) {
            f32 limit;

            if (actor->speedY > -10.0f || (actor->contactFlags & actor->prevContactFlags & 1)) {
                f = 0.0f;
            } else {
                f = actor->prevPeakY - actor->y;
            }
            limit = (actor->waterY - actor->floorY) * 2;
            f = (f < limit ? f : limit) < 0.0f ? 0.0f : (f < limit ? f : limit);

            if (actor->actorType == 0x29 || actor->actorType == 0x32) {
                sfxPlayFromActorWithAltitudeCheck(actor, 0x2C7, 0xFF, 0x7F, 1);
            } else if (f < 10.0f) {
                sfxPlayFromActorWithAltitudeCheck(actor, 0x10, (u8)((f64)f * 25.5), 0x7F, 1);
            } else if (f < 20.0f) {
                sfxPlayFromActorWithAltitudeCheck(actor, 0xF, 0xFF, 0x7F, 1);
            } else {
                effectSpawnBurstParticles(actor);
            }
        }
    } else {
        scale = scaleParam;
    }
    particleInitDefaultState();
    effectCreateAtPosition(&D_8071FBF4, (f32)((f64)scale * 0.3), posX, posY, posZ);
    particleInitDefaultState();
    effectSetAngle(2);
    effectCreateAtPosition(&D_8071FBF4, (f32)((f64)scale * 0.05),
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + posX - (f32)(u8)(15.0f * scale),
        posY,
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + posZ - (f32)(u8)(15.0f * scale));
    particleInitDefaultState();
    effectSetAngle(4);
    effectCreateAtPosition(&D_8071FBF4, (f32)((f64)scale * 0.05),
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + posX - (f32)(u8)(15.0f * scale),
        posY,
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + posZ - (f32)(u8)(15.0f * scale));
}

void effectSpawnActorOrbitParticles(Actor *actor) {
    s32 i;

    for (i = 0; i < 16; i++) {
        effectSetDepth(1);
        effectSetDuration(-1);
        effectSetSpeed((s32)actor);
        effectSetCallback(effectActorOrbitFollowUpdate);
        effectCreateAtPosition(D_8074E880[i % 3], 0.7f, actor->x, actor->y, actor->z);
    }
}

void effectSpawnRingBursts(Actor *actor, f32 radius, f32 arcHeight, s32 moveSpeed) {
    s32 i;

    for (i = 0; i < 3; i++) {
        effectSetDepth(1);
        effectSetDuration(-1);
        effectSetSpeed((s32)actor);
        effectSetCallback(effectArcAroundActorUpdate);
        func_8071E110(effectCreateAtPosition(D_8074E880[i], 0.7f, actor->x, actor->y, actor->z), 1, (u16)(i * 1365.3334f), radius, arcHeight, moveSpeed);
    }
    for (i = 0; i < 3; i++) {
        effectSetDepth(1);
        effectSetDuration(-1);
        effectSetSpeed((s32)actor);
        effectSetCallback(effectArcAroundActorUpdate);
        func_8071E110(effectCreateAtPosition(D_8074E880[i], 0.7f, actor->x, actor->y, actor->z), 0, (u16)(i * 1365.3334f), radius, arcHeight, moveSpeed);
    }
}

void effectSpawnBurstParticleCluster(Actor *actor) {
    s32 i;

    for (i = 0; i < 30; i++) {
        effectSetDepth(1);
        effectSetDuration(1);
        effectSetCallback(effectBurstParticleUpdate);
        effectSetAngle((s16)(i / 7));
        effectCreateAtPosition((void *)D_8074E880[i % 3], 1.4f, actor->x, actor->y + 10.0f, actor->z);
    }
}

void effectSpawnParticleRingAtPosition(f32 posX, f32 posY, f32 posZ, s32 speed) {
    s32 i;
    s32 shift;
    s32 count;

    count = (D_80750AD0 != 0) ? 3 : 16;
    shift = (D_80750AD0 != 0) ? 0 : 2;

    for (i = 0; i < count; i++) {
        effectSetDepth(1);
        effectSetDuration(1);
        effectSetCallback(func_80717930);
        effectSetAngle(i >> shift);
        effectSetSpeed(speed);
        effectCreateAtPosition(D_8074E880[i % 3], 0.5f, posX, posY, posZ);
    }
}

void effectSpawnChildAtNode(u8 node, s16 rotY, s16 rotZ) {
    actorSpawn(0x109, 0xC0);
    if (node) {
        actorGetNodePos(gCurrentActor, node, &gSpawnedActor->x, &gSpawnedActor->y, &gSpawnedActor->z);
    } else {
        gSpawnedActor->x = gCurrentActor->x;
        gSpawnedActor->y = gCurrentActor->y;
        gSpawnedActor->z = gCurrentActor->z;
    }
    gSpawnedActor->yaw = rotY;
    gSpawnedActor->roll = rotZ;
    gSpawnedActor->sub4->scaleY *= 0.01;
}

void effectActorGrowthTick(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = ((randomNonNegative() >> 15) % 75) + 0xB4;
        gCurrentActor->tintB = 0x28;
        gCurrentActor->alpha = 0xFF;
    }
    if ((f64)gCurrentActor->sub4->scaleY > 1.0) {
        gCurrentActor->alpha -= 0x28;
        if (gCurrentActor->alpha < 0) {
            actorDespawn(gCurrentActor);
        }
    } else {
        gCurrentActor->sub4->scaleY = (f32)(gCurrentActor->sub4->scaleY * 1.8);
        gCurrentActor->sub4->scaleX = (f32)(gCurrentActor->sub4->scaleX * 1.1);
        gCurrentActor->sub4->scaleZ = (f32)(gCurrentActor->sub4->scaleZ * 1.1);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void effectSpawnActorBoneEffects(u8 effectType) {
    u8 startBone;
    s16 idx;
    u8 bone;

    startBone = ((gFrameCounter & 3) * 4) + 3;
    for (idx = 0; idx < 4; idx++) {
        bone = startBone;
        if (startBone == 0x10) {
            bone = 0x14;
        } else if (bone == 0x11) {
            bone = 0x15;
        } else {
            bone = startBone;
        }

        switch (effectType) {
        case 3:
            if (bone < 10) {
                break;
            }
            /* fallthrough */
        case 1:
            effectSetMode(1);
            effectSetColor(0xB4, 0xB4, 0xB4, 0xC8);
            effectSpawnBoneDefault(gCurrentActor, bone, 2.0f, 0.0f, 0.0f, 0.0f, -0x78);
            break;

        case 2:
            if (bone < 10) {
                break;
            }
            /* fallthrough */
        case 0:
            effectSetDepth(1);
            effectSetCallback(func_80717D4C);
            effectSetSpeed(-0x3E8);
            effectSetColor(0xFF, 0xD7, 0x58, 0xFF);
            effectCreateAtActorBone(&D_80720120, (f32)(((f64)((randomNonNegative() >> 15) % 100) / 30.0) + 1.0), gCurrentActor, bone, 0);
            break;
        }
        startBone++;
    }
}

void func_80687400(void) {
    sfxPlayOnFreeSlot(0x2D4, 0x7FFF, 63.0f, 1.0f, 0, 0);
    effectSetDuration(0xC8);
    effectEnableFade();
    effectSetCallback(func_8071EFDC);
    effectCreateAtPosition(&D_80721158, 1.0f, 160.0f, 120.0f, -10.0f);
}

void actorSpawnAttachment(Actor *parent, f32 scaleMultiplier) {
    actorSpawn(0xB3, 0x5D);
    gSpawnedActor->flags |= 0x400;
    actorScriptStart(gSpawnedActor, 0x334);
    actorCopyPoseAndScale(gSpawnedActor, parent, parent->sub4->scaleY * scaleMultiplier);
}


void effectSpawnKongRing(void) {
    s32 boneIndex;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    f32 baseScale;
    f32 spawnX;
    s16 angle;
    s32 i;

    angle = (randomNonNegative() >> 15) % 4096;
    baseScale = (f32)(gCurrentActor->sub4->scaleY * (20.0 / 3.0));
    switch (gCurrentActor->actorType) {
    case 2:
    case 5:
        boneIndex = 15;
        break;
    case 3:
    case 4:
    case 6:
        boneIndex = 13;
        break;
    default:
        return;
    }

    actorGetNodePos(gCurrentActor, boneIndex, &nodeX, &nodeY, &nodeZ);
    for (i = 0; i < 64; i++) {
        angle += (randomNonNegative() >> 15) % 1024;
        angle &= 0xFFF;
        effectSetMode(2);
        effectSetDepth(1);
        effectSetCallback(func_80717D4C);
        effectSetSpeed((s32)((f32)((((randomNonNegative() >> 15) % 0x7FFF) % 51) + 100) * baseScale));
        effectSetAngle((s16)((f32)i * (1.0f / 3.0f)));
        effectSetFlags(0x20);
        spawnX = (mathSinF(angle) * (baseScale * 18.0f)) + nodeX;
        effectCreateAtPosition((void *)D_8074E880[i % 3], baseScale * 0.3f, spawnX, nodeY, (mathCosF(angle) * (baseScale * 18.0f)) + nodeZ);
    }
}

void effectSpawnBoneSparkAttached(u8 bone) {
    effectSetDepth(1);
    effectCreateAtActorBone(&D_8072006C, 1.0f, gCurrentActor, bone, 0);
}

void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32); // FAKE: callee prototype steer
extern s32 D_80720B24;

void effectSpawnJointBeam(u8 minBoneA, u8 maxBoneA, u8 minBoneB, u8 maxBoneB) {
    f32 posAX;
    f32 posAY;
    f32 posAZ;
    f32 posBX;
    f32 posBY;
    f32 posBZ;
    f32 beamAngle;
    f32 screenAX;
    f32 screenAY;
    f32 screenBX;
    f32 screenBY;
    f32 screenDist;
    u8 bones[4];

    bones[1] = ((randomNonNegative() >> 15) % 0x7FFF) % ((maxBoneA - minBoneA) + 1) + minBoneA;
    bones[0] = ((randomNonNegative() >> 15) % 0x7FFF) % ((maxBoneB - minBoneB) + 1) + minBoneB;
    actorGetNodePos(gCurrentActor, bones[1], &posAX, &posAY, &posAZ);
    actorGetNodePos(gCurrentActor, bones[0], &posBX, &posBY, &posBZ);
    camProjectToScreen(posAX, posAY, posAZ, &screenAX, &screenAY, 0, 1.0f, 0);
    camProjectToScreen(posBX, posBY, posBZ, &screenBX, &screenBY, 0, 1.0f, 0);
    {
        f32 temp = (f32)(((s32)(mathAngleBetweenPoints2D(screenBX, screenBY, screenAX, screenAY) * 360) / 4096) + 90);
        beamAngle = temp;
        if (temp < 270.0f) {
            beamAngle = temp + 180.0f;
        }
    }
    screenDist = sqrtf(((screenAX - screenBX) * (screenAX - screenBX)) + ((screenAY - screenBY) * (screenAY - screenBY)));
    effectSetDepth(1);
    effectSetDuration(1);
    effectSetSpeed((s32)beamAngle);
    effectSetCallback(func_8071E028);
    effectCreateAtPosition(&D_80720B24, (f32)((f64)screenDist * 0.008), (f32)((f64)(posAX + posBX) * 0.5), (f32)((f64)(posAY + posBY) * 0.5), (f32)((f64)(posAZ + posBZ) * 0.5));
    if (((randomNonNegative() >> 15) % 1000) & 1) {
        lightSetFlags(1);
        lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, 150.0f, 0, 150, 100, 255);
    }
    if ((gCurrentActor->actorType == 0xB9) && (((randomNonNegative() >> 15) % 1000) >= 0x385)) {
        effectSpawnBoneSparkAttached((((randomNonNegative() >> 15) % 0x7FFF) % 10) + 13);
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, (((randomNonNegative() >> 15) % 1000) >= 501) ? 0x8A : 0xA1, 0xFF, 0x7F, 0x28, 0, 0.3f, 0);
    }
}

void func_80687C48(void) {
    sfxPlayOnFreeSlot(0xF2, 0x7FFF, 63.0f, 1.0f, 0, 0);
    sfxAllocateChannel(0x97, 1.0f);
    effectSetDuration(0xC8);
    effectEnableFade();
    effectSetCallback(func_8071EFDC);
    effectCreateAtPosition(&D_80720558, 1.0f, 160.0f, 120.0f, -10.0f);
}

void func_80687CC8(void) {
    sfxPlayOnFreeSlot(0xF2, 0x7FFF, 63.0f, 1.0f, 0, 0);
    sfxAllocateChannel(0x97, 1.0f);
    effectSetDuration(0xC8);
    effectEnableFade();
    effectSetCallback(func_8071EFDC);
    effectCreateAtPosition(&D_807210EC, 1.0f, 160.0f, 120.0f, -10.0f);
}
