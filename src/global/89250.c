#include "common.h"
#include "actor.h"

typedef struct Struct_5390 {
    f32 arr[3];
} Struct_5390;

typedef struct Actor174_5390 {
    f32 unk0;
    u16 unk4;
    u8 unk6;
} Actor174_5390;

typedef struct Actor338 {
    u8 pad[0x338];
    void *unk338;
} Actor338;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Struct_5390 D_8074E88C;
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

s32 actorSpawn();
void actorDespawn(Actor *);
void sfxAllocateChannel(s32, f32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
s32 randomLcgNext(void);
s32 randomNonNegative(void);
void actorScriptStart(Actor *, s32);
void actorUpdateModelMatrix(Actor *, s32);
void triggerZoneCheckEntry(Actor *);
s32 func_80665AAC(Actor *);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void actorCopyPoseAndScale(Actor *, Actor *, f32);
void effectSpawnBoneWhite(Actor *actor, s16 bone, f32 scale, f32 posX, f32 posY, f32 posZ, s32 moveSpeed);
void effectSpawnBoneDefault(Actor *actor, s16 bone, f32 scale, f32 posX, f32 posY, f32 posZ, s32 moveSpeed);
void effectSpawnBone(Actor *actor, s16 bone, f32 scale, f32 posX, f32 posY, f32 posZ, s32 moveSpeed);
void effectActorCheckGroundScaleSpawn(Actor *);
void effectSpawnDebrisParticles(Actor *actor, f32 scaleParam, f32 posX, f32 posY, f32 posZ);
void animSetSpeed(Actor *, s32, f32);
void animSetLoopLimit(Actor *, s32, s32);
s32 animIsPlaying(Actor *, s32);
void actorSpawnAttachedTo(Actor *);
void func_80714950();
void func_8071495C(void);
void func_8071496C(s32);
void func_8071498C(void (*)(void));
void func_80714998(s8);
void func_807149B8(s8);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714A28(s32);
void func_80714C08(void *, f32, Actor *, s32, s32);
Actor338 *func_80714CC0(void *, f32, f32, f32, f32);
void func_80717930(void);
void func_80717D4C(void);
void effectShrinkAndVelocityUpdate(void);
void effectFadeOutMatrixUpdate(void);
void effectGroundDecalSpinUpdate(void);
void effectTumbleBounceUpdate(void);
void effectDecelerateDriftUpdate(void);
void timedEffectCountdownTick(void);
void effectSpiralRiseUpdate(void);
void effectSpriteMotionUpdate(void);
void effectFollowParentUpdate(void);
void effectFloorFallUpdate(void);
void effectActorOrbitFollowUpdate(void);
void func_8071E110(void *, s32, s32, f32, f32, s32);
void effectArcAroundActorUpdate(void);
void effectBurstParticleUpdate(void);
void func_8071EFDC(void);

void effectSpawnActorBone(s32 lifetime, u8 bone, f32 scale) {
    func_807149B8(1);
    func_8071498C(effectFollowParentUpdate);
    func_80714950(lifetime);
    func_80714A28(4);
    func_80714C08(&D_80720120, scale, gCurrentActor, bone, 0);
}

void effectSpawnRandomBoneDebris(u8 minBone, u8 maxBone) {
    f32 scale;
    u8 bone;

    if (!(gFrameCounter & 3)) {
        scale = (f32)(gCurrentActor->unk4->unk38 / 0.15);
        bone = ((randomNonNegative() >> 15) % 0x7FFF) % ((maxBone - minBone) + 1) + minBone;
        func_80714998(3);
        func_807149C8(0xE6, 0xE6, 0xE6, 0xE6);
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
    actorSpawn(0xFF, actorType, parent);
    gSpawnedActor->unk11C = (s32)parent;
    gSpawnedActor->unk4->unk34 = scaleXZ;
    gSpawnedActor->unk4->unk3C = scaleXZ;
    gSpawnedActor->unk4->unk38 = scaleY;
    gSpawnedActor->x = posX;
    gSpawnedActor->y = posY;
    gSpawnedActor->z = posZ;
    if ((parent != NULL) && (parent->collisionFlags & 1)) {
        if (fastGrow != 0) {
            gSpawnedActor->yawSpeed = 0xF;
            *(f64*)&gSpawnedActor->splineT = 1.11;
            gSpawnedActor->unk15F = 1;
            return;
        }
        gSpawnedActor->yawSpeed = 0x19;
        *(f64*)&gSpawnedActor->splineT = 1.09;
        return;
    }
    gSpawnedActor->yawSpeed = 0x20;
    *(f64*)&gSpawnedActor->splineT = 1.07;
    gSpawnedActor->unk15F = 0;
}

extern s32 D_8071FF58;
void effectWobbleScaleUpdate(void);

void effectSpawnSmoke(u8 bone) {
    if (!(gFrameCounter & 0x1F)) {
        func_80714998(2);
        func_807149B8(1);
        func_807149FC(0x3C);
        func_8071498C(effectWobbleScaleUpdate);
        if (bone) {
            func_80714C08(&D_8071FF58, 0.05f, gCurrentActor, (u8)bone, 0);
        } else {
            func_80714CC0(&D_8071FF58, 0.05f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
    }
}

void effectSpawnBurst(u8 useAltRange) {
    if (useAltRange) {
        func_80714950(((s32)(randomNonNegative() >> 15) % 10) + 0x8008);
    } else {
        func_80714950(((s32)(randomNonNegative() >> 15) % 8) + 6);
    }
    func_807149FC(2);
    func_8071498C(func_80717930);
    func_807149B8(1);
    func_80714A28(4);
    func_80714C08(&D_8072139C, (f32)(((f64)((s32)(randomNonNegative() >> 15) % 50) / 80.0) + 0.1), gCurrentActor, 8, 0);
}

void effectSpawnBoneDebris(s16 bone, s8 direction) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    f32 scale;

    scale = (f32)(gCurrentActor->unk4->unk38 / 0.15);
    actorGetNodePos(gCurrentActor, bone, &nodeX, &nodeY, &nodeZ);
    func_80714950((((s32)(randomNonNegative() >> 15) % 100) + 0x190) * direction);
    func_8071498C(func_80717D4C);
    func_807149B8(1);
    func_80714CC0(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3],
                   (f32)((f64)scale * 0.8),
                   (f32)((randomNonNegative() >> 15) % 20) + (nodeX - 10.0f),
                   nodeY,
                   (f32)((randomNonNegative() >> 15) % 20) + (nodeZ - 10.0f));
}

void func_8071F2F8(void);

void effectSpawnBoneDebrisScaled(s16 bone, s16 baseSpeed, s16 lifetime) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    f32 scale;
    f64 duration;

    scale = (f32)((f64)gCurrentActor->unk4->unk38 / 0.15);
    actorGetNodePos(gCurrentActor, bone, &nodeX, &nodeY, &nodeZ);
    func_80714950(baseSpeed + (lifetime << 16));
    func_8071498C(func_8071F2F8);
    func_807149B8(1);
    if (((f64)lifetime * 0.02) < 2.0) {
        duration = 2.0;
    } else {
        duration = (f64)lifetime * 0.02;
    }
    func_807149FC((s32)duration);
    func_80714CC0(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3],
                   (f32)((f64)scale * 0.8),
                   (f32)((randomNonNegative() >> 15) % 60) + (nodeX - 30.0f),
                   nodeY,
                   (f32)((randomNonNegative() >> 15) % 60) + (nodeZ - 30.0f));
}

extern s32 D_8071FC40;
void effectWobbleRiseUpdate(void);

void effectSpawnAuraBurst(u8 rate) {
    s32 i;
    f32 x, y, z;

    if ((((u32)randomLcgNext() / 10000) % rate) == 0) {
        if (D_80750AD0 == 0) {
            for (i = 0; i != 4U; i++) {
                x = (f32)(((f64)(f32)((u32)randomLcgNext() / 10000 % 200) / 10.0) - 5.0);
                y = (f32)(((f64)(f32)((u32)randomLcgNext() / 10000 % 200) / 10.0) - 5.0);
                z = (f32)(((f64)(f32)((u32)randomLcgNext() / 10000 % 200) / 10.0) - 5.0);
                func_807149B8(1);
                func_80714950(1);
                func_807149FC(-1);
                func_8071498C(effectWobbleRiseUpdate);
                func_80714A28(4);
                func_80714CC0(&D_8071FC40, 0.0f, gCurrentActor->x + x, gCurrentActor->y + y, gCurrentActor->z + z);
            }
        }
    }
}

void effectSpawnSparks(u8 frameMask, u8 bone) {
    if (!(frameMask & gFrameCounter)) {
        func_8071498C(effectWobbleRiseUpdate);
        func_807149B8(1);
        func_807149FC(-1);
        func_80714A28(4);
        if (bone) {
            func_80714C08(&D_8071FC40, 0.0f, gCurrentActor, (u8)bone, 0);
        } else {
            func_80714CC0(&D_8071FC40, 0.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
    }
}

void effectSpawnRing(void) {
    f32 temp;
    s32 i;

    temp = (f32)(gCurrentActor->unk4->unk38 / 0.15);
    func_807149B8(0);
    func_807149FC(1);
    func_80714CC0(&D_8071FE08, (f32)((f64)temp * 0.75), gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    for (i = 0; i < 7; i++) {
        func_807149B8(1);
        func_807149FC(0xA);
        func_8071498C(effectTumbleBounceUpdate);
        func_80714998(2);
        func_80714950(0);
        func_80714CC0(&D_8072073C, (f32)((f64)temp * 0.15), gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    }
}

void func_80685210(f32 scale, s16 speedThreshold, s16 bone) {
    if (((gFrameCounter % 3) == 0) && ((f32)speedThreshold < gCurrentActor->speedXZ)) {
        func_80714998(2);
        func_807149B8(1);
        func_8071498C(func_80717D4C);
        func_80714950(-0x32);
        func_80714A28(4);
        func_80714C08(&D_8071FF18, scale, gCurrentActor, bone, 0);
    }
}

void effectSpawnOctagonRing(f32 scale, f32 posX, f32 posY, f32 posZ) {
    s16 sector;

    for (sector = 0; sector < 8; sector++) {
        func_8071498C(effectDecelerateDriftUpdate);
        func_80714950(sector);
        func_807149B8(1);
        func_807149C8(0xFF, 0xFF, 0xFF, 0xC8);
        func_80714CC0(&sEffectSparkConfig, scale, posX, posY, posZ);
    }
}

void actorScaleGrowthUpdate(void) {
    Actor174_5390 *extraData = gCurrentActor->unk174;
    Struct_5390 scales = D_8074E88C;

    if (!(gCurrentActor->flags & 0x10)) {
        extraData->unk0 = gCurrentActor->unk4->unk38;
    }
    extraData->unk4++;
    switch (gCurrentActor->state) {
    case 0:
        gCurrentActor->unk4->unk38 = scales.arr[extraData->unk6] * (extraData->unk0 * (f32)(u32)extraData->unk4 * 0.33333334f);
        if ((f32)(u32)extraData->unk4 > 3.0f) {
            gCurrentActor->state = 1;
            extraData->unk4 = 0;
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
    s32 tierCount;
    s32 sector;

    tierCount = tier;
    if (D_80750AD0 == 0) {
        if (tierCount > 0) {
            effectSpawnOctagonRing(scale, posX, posY, posZ);
        }
        if (tierCount >= 2) {
            for (sector = 0; sector < 8; sector++) {
                func_8071498C(timedEffectCountdownTick);
                func_80714950(sector);
                func_807149B8(1);
                func_807149FC(-1);
                func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
                func_80714CC0(&D_8071FF40, (f32)((f64)scale * 0.5), posX, posY, posZ);
            }
        }
        if (tierCount >= 3) {
            for (sector = 0; sector < 9; sector++) {
                func_8071498C(effectSpiralRiseUpdate);
                func_80714950(sector);
                func_807149B8(1);
                func_807149FC(-1);
                func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
                func_80714CC0(D_8074E880[sector % 3], scale, posX, posY, posZ);
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
    void *sub;
    s32 pad1[1];

    actorScale = (f32)((f64)actor->unk4->unk38 / 0.15);
    params = D_8074E898;
    if (tier) {
        effectSpawnMultiTierRing((f32)((f64)actorScale * 0.36), tier, actor->x, actor->y + 4.0f, actor->z);
        actorSpawn(0x145, params.a[tier]);
        actorCopyPoseAndScale(gSpawnedActor, actor, actor->unk4->unk38 * 0.5f);
        sub = gSpawnedActor->unk174;
        ((Actor174_5390 *)sub)->unk6 = tier - 1;
    }
}

void effectSpawnBoneWhite(Actor *actor, s16 bone, f32 scale, f32 posX, f32 posY, f32 posZ, s32 moveSpeed) {
    func_80714998(2);
    func_807149C8(0xFF, 0xFF, 0xFF, 0xC8);
    effectSpawnBoneDefault(actor, bone, scale, posX, posY, posZ, moveSpeed);
}

void effectSpawnBoneDefault(Actor *actor, s16 bone, f32 scale, f32 posX, f32 posY, f32 posZ, s32 moveSpeed) {
    func_807149B8(1);
    effectSpawnBone(actor, bone, scale, posX, posY, posZ, moveSpeed);
}

void effectSpawnBone(Actor *actor, s16 bone, f32 scale, f32 posX, f32 posY, f32 posZ, s32 moveSpeed) {
    Actor338 *temp;

    if (actor != NULL && bone != 0) {
        actorGetNodePos(actor, bone, &posX, &posY, &posZ);
    }
    func_8071498C(effectShrinkAndVelocityUpdate);
    func_80714950(moveSpeed);
    temp = func_80714CC0(&sEffectSparkConfig, scale, posX, posY + 5.0f, posZ);
    temp->unk338 = actor;
}

void effectSpawnScatter(f32 scale, f32 posX, f32 posY, f32 posZ) {
    s32 pad[2];
    s32 randVal;
    s32 mod100k;
    s32 mod10;
    if (((randomNonNegative() >> 15) % 100) >= 51) {
        func_80714998(2);
        func_80714950((randomNonNegative() >> 15) % 360);
        func_807149B8(1);
        func_807149C8(0x9B, 0x9B, 0x9B, 0xC8);
        func_8071498C(effectSpriteMotionUpdate);
        randVal = randomNonNegative();
        mod100k = 100000;
        mod10 = 10;
        func_80714CC0(&sEffectSparkConfig, scale, (f32)(((randVal >> 15) % mod100k) % mod10) + (posX - 5.0f), posY, (f32)(((randomNonNegative() >> 15) % mod100k) % mod10) + (posZ - 5.0f));
    }
}
void func_807180F4(void);

void effectSpawnScatterRandom(void *texture, u8 colorMode, f32 scale, u8 count, u8 spread, s16 baseSpeed, s16 posX, s16 posY, s16 posZ) {
    s16 idx;
    s8 dx;
    s8 dz;

    idx = 0;
    if (count > 0) {
        do {
            dx = ((randomNonNegative() >> 15) % 32767 % (spread * 2)) + (-spread);
            dz = ((randomNonNegative() >> 15) % 32767 % (spread * 2)) + (-spread);
            func_80714950(-baseSpeed - ((randomNonNegative() >> 15) % 80));
            func_8071498C(func_807180F4);
            func_807149B8(1);
            func_80714998(2);
            if (colorMode) {
                func_8071496C((s16)colorMode);
            }
            func_80714CC0(texture, scale, (f32)(posX + dx), (f32)posY, (f32)(posZ + dz));
            idx = (s16)(idx + 1);
        } while (idx < count);
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

    scale = (actor->unk4 != NULL) ? (f64)actor->unk4->unk38 / 0.15 : 1.0;
    func_80714998(3);
    func_807149B8(1);
    func_807149FC(1);
    func_8071498C(effectGroundDecalSpinUpdate);
    func_80714A28(4);
    func_807149C8(0xC8, 0xFF, 0xFF, 0xC8);
    ((Actor338 *)func_80714CC0(&D_8071FED0, (f64) scale * 0.6, actor->x, actor->waterY, actor->z))->unk338 = actor;
}

typedef struct EffectPlayerData {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F0 - 0x2C1];
} EffectPlayerData;

typedef struct ActorFloorContact {
    u8 pad0[0x10];
    s16 unk10;
} ActorFloorContact;

extern EffectPlayerData *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s16 D_80753A08[];
extern s16 D_80753A18[];

void effectActorCheckGroundScaleSpawn(Actor *actor) {
    register f32 floorYOffset;
    u8 shouldSpawn;
    shouldSpawn = 0;
    if (*(void **)actor->unk00 != NULL && actor->unk4 != NULL) {
        if (actor->collisionFlags == 1) {
            if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
                floorYOffset = D_80753A08[actor->actorType];
            } else {
                floorYOffset = D_80753A18[actor->actorType];
            }
        } else {
            floorYOffset = (f32)(u32)actor->unk15E;
        }
        if ((actor->waterY - floorYOffset) <= actor->y) {
            if (!(gFrameCounter & 3)) {
                shouldSpawn = (f64)actor->speedXZ != 0.0;
                if (*(ActorFloorContact **)actor->unk118 != NULL && (*(ActorFloorContact **)actor->unk118)->unk10 != 0) {
                    shouldSpawn = 1;
                }
            }
            if (shouldSpawn) {
                func_80714950(1);
            } else if (((f64)actor->speedXZ == 0.0) && (((u32)gFrameCounter % 24 == 0) || ((f64)actor->prevSpeedXZ != 0.0))) {
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

    scale = (actor->unk4 != NULL) ? (f64)actor->unk4->unk38 / 0.15 : 1.0;
    if (actor->actorType == 0x1E) {
        scale *= 2;
        effectSpawnBoneDefault(actor, 0, 4.0f, actor->x, actor->y, actor->z, -0x96);
        actorDespawn(actor);
    }
    sfxPlayFromActorWithAltitudeCheck(actor, 0xC, 0xFF, 0x7F, 1);
    func_807149B8(1);
    func_807149FC(1);
    func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
    func_80714CC0(&D_8071FC0C, (f64)scale * 0.65, actor->x, actor->waterY + 15.0f, actor->z);
    if (D_80750AD0 == 0) {
        count = (randomLcgNext() & 3) + 4;
        i = 0;
        if (count > 0) {
            scale01 = (f64)scale * 0.1;
            do {
                func_807149B8(1);
                func_807149FC(-1);
                func_8071498C(effectFloorFallUpdate);
                func_80714A28(4);
                func_80714CC0(&D_80720B58, scale01, actor->x, actor->waterY, actor->z);
                i++;
            } while (i < count);
        }
    }
}

void particleInitDefaultState(void) {
    func_807149B8(1);
    func_807149FC(0x14);
    func_8071498C(effectFadeOutMatrixUpdate);
    func_807149C8(0xFF, 0xFF, 0xFF, 0xC8);
    func_80714A28(4);
}

extern s32 D_8071FBF4;

void effectSpawnDebrisParticles(Actor *actor, f32 scaleParam, f32 posX, f32 posY, f32 posZ) {
    f32 f;
    f32 scale;

    if (actor != NULL) {
        scale = (actor->unk4 != NULL) ? (f64)actor->unk4->unk38 / 0.15 : 1.0;
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
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.3), posX, posY, posZ);
    particleInitDefaultState();
    func_8071496C(2);
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.05),
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + posX - (f32)(u8)(15.0f * scale),
        posY,
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + posZ - (f32)(u8)(15.0f * scale));
    particleInitDefaultState();
    func_8071496C(4);
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.05),
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + posX - (f32)(u8)(15.0f * scale),
        posY,
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + posZ - (f32)(u8)(15.0f * scale));
}

void effectSpawnActorOrbitParticles(Actor *actor) {
    s32 i;

    for (i = 0; i < 16; i++) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(actor);
        func_8071498C(effectActorOrbitFollowUpdate);
        func_80714CC0((void *)D_8074E880[i % 3], 0.7f, actor->x, actor->y, actor->z);
    }
}

void effectSpawnRingBursts(Actor *actor, f32 radius, f32 arcHeight, s32 moveSpeed) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(actor);
        func_8071498C(effectArcAroundActorUpdate);
        func_8071E110(func_80714CC0((void *)D_8074E880[i], 0.7f, actor->x, actor->y, actor->z), 1, (u16)(i * 1365.3334f), radius, arcHeight, moveSpeed);
    }
    for (i = 0; i != 3; i++) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(actor);
        func_8071498C(effectArcAroundActorUpdate);
        func_8071E110(func_80714CC0((void *)D_8074E880[i], 0.7f, actor->x, actor->y, actor->z), 0, (u16)(i * 1365.3334f), radius, arcHeight, moveSpeed);
    }
}

void effectSpawnBurstParticleCluster(Actor *actor) {
    s32 i;

    for (i = 0; i < 30; i++) {
        func_807149B8(1);
        func_807149FC(1);
        func_8071498C(effectBurstParticleUpdate);
        func_8071496C((s16)(i / 7));
        func_80714CC0((void *)D_8074E880[i % 3], 1.4f, actor->x, actor->y + 10.0f, actor->z);
    }
}

void effectSpawnParticleRingAtPosition(f32 posX, f32 posY, f32 posZ, void *param) {
    s32 i;
    s32 shift;
    s32 count;

    count = (D_80750AD0 != 0) ? 3 : 16;
    shift = (D_80750AD0 != 0) ? 0 : 2;

    for (i = 0; i < count; i++) {
        func_807149B8(1);
        func_807149FC(1);
        func_8071498C(func_80717930);
        func_8071496C((s16)(i >> shift));
        func_80714950(param);
        func_80714CC0((void *)D_8074E880[i % 3], 0.5f, posX, posY, posZ);
    }
}

void effectSpawnChildAtNode(u8 node, s16 rotY, s16 rotZ) {
    u8 temp;

    actorSpawn(0x109, 0xC0);
    temp = node;
    if (temp) {
        actorGetNodePos(gCurrentActor, temp, &gSpawnedActor->x, &gSpawnedActor->y, &gSpawnedActor->z);
    } else {
        gSpawnedActor->x = gCurrentActor->x;
        gSpawnedActor->y = gCurrentActor->y;
        gSpawnedActor->z = gCurrentActor->z;
    }
    gSpawnedActor->yaw = rotY;
    gSpawnedActor->roll = rotZ;
    gSpawnedActor->unk4->unk38 = (f32)(gSpawnedActor->unk4->unk38 * 0.01);
}

void effectActorGrowthTick(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = ((randomNonNegative() >> 15) % 75) + 0xB4;
        gCurrentActor->tintB = 0x28;
        gCurrentActor->unk128 = 0xFF;
    }
    if ((f64)gCurrentActor->unk4->unk38 > 1.0) {
        gCurrentActor->unk128 -= 0x28;
        if (gCurrentActor->unk128 < 0) {
            actorDespawn(gCurrentActor);
        }
    } else {
        gCurrentActor->unk4->unk38 = (f32)(gCurrentActor->unk4->unk38 * 1.8);
        gCurrentActor->unk4->unk34 = (f32)(gCurrentActor->unk4->unk34 * 1.1);
        gCurrentActor->unk4->unk3C = (f32)(gCurrentActor->unk4->unk3C * 1.1);
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

        switch (effectType + 0U) {  // FAKE: +0U types the selector u32 (separate const-1 web) and keeps andi s3 hoisted
        case 3:
            if (bone < 10) {
                break;
            }
            /* fallthrough */
        case 1:
            func_80714998(1);
            func_807149C8(0xB4, 0xB4, 0xB4, 0xC8);
            effectSpawnBoneDefault(gCurrentActor, bone, 2.0f, 0.0f, 0.0f, 0.0f, -0x78);
            break;

        case 2:
            if (bone < 10) {
                break;
            }
            /* fallthrough */
        case 0:
            func_807149B8(1);
            func_8071498C(func_80717D4C);
            func_80714950(-0x3E8);
            func_807149C8(0xFF, 0xD7, 0x58, 0xFF);
            func_80714C08(&D_80720120, (f32)(((f64)((randomNonNegative() >> 15) % 100) / 30.0) + 1.0), gCurrentActor, bone, 0);
            break;
        }
        startBone++;
    }
}

void func_80687400(void) {
    sfxPlayOnFreeSlot(0x2D4, 0x7FFF, 63.0f, 1.0f, 0, 0);
    func_807149FC(0xC8);
    func_8071495C();
    func_8071498C(func_8071EFDC);
    func_80714CC0(&D_80721158, 1.0f, 160.0f, 120.0f, -10.0f);
}

void actorSpawnAttachment(Actor *parent, f32 scaleMultiplier) {
    actorSpawn(0xB3, 0x5D);
    gSpawnedActor->flags |= 0x400;
    actorScriptStart(gSpawnedActor, 0x334);
    actorCopyPoseAndScale(gSpawnedActor, parent, parent->unk4->unk38 * scaleMultiplier);
}

f32 mathCosF(s16);
f32 mathSinF(s16);

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
    baseScale = (f32)(gCurrentActor->unk4->unk38 * (20.0 / 3.0));
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
        func_80714998(2);
        func_807149B8(1);
        func_8071498C(func_80717D4C);
        func_80714950((void *)(s32)((f32)((((randomNonNegative() >> 15) % 0x7FFF) % 51) + 100) * baseScale));
        func_8071496C((s16)(s32)((f32)i * (1.0f / 3.0f)));
        func_80714A28(0x20);
        spawnX = (mathSinF(angle) * (baseScale * 18.0f)) + nodeX;
        func_80714CC0((void *)D_8074E880[i % 3], baseScale * 0.3f, spawnX, nodeY, (mathCosF(angle) * (baseScale * 18.0f)) + nodeZ);
    }
}

void effectSpawnBoneSparkAttached(bone)
u8 bone;
{
    func_807149B8(1);
    func_80714C08(&D_8072006C, 1.0f, gCurrentActor, bone, 0);
}

void camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void lightSetFlags(s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_8071E028(void);
extern s32 D_80720B24;

void effectSpawnJointBeam(minBoneA, maxBoneA, minBoneB, maxBoneB)
u8 minBoneA;
u8 maxBoneA;
u8 minBoneB;
u8 maxBoneB;
{
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
    func_807149B8(1);
    func_807149FC(1);
    func_80714950((s32)beamAngle);
    func_8071498C(func_8071E028);
    func_80714CC0(&D_80720B24, (f32)((f64)screenDist * 0.008), (f32)((f64)(posAX + posBX) * 0.5), (f32)((f64)(posAY + posBY) * 0.5), (f32)((f64)(posAZ + posBZ) * 0.5));
    if (((randomNonNegative() >> 15) % 1000) & 1) {
        lightSetFlags(1);
        lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, 150.0f, 0, 150, 100, 255);
    }
    if ((gCurrentActor->actorType == 0xB9) && (((randomNonNegative() >> 15) % 1000) >= 0x385)) {
        effectSpawnBoneSparkAttached((((randomNonNegative() >> 15) % 0x7FFF) % 10) + 13 & 0xFF);
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, (((randomNonNegative() >> 15) % 1000) >= 501) ? 0x8A : 0xA1, 0xFF, 0x7F, 0x28, 0, 0.3f, 0);
    }
}

void func_80687C48(void) {
    sfxPlayOnFreeSlot(0xF2, 0x7FFF, 63.0f, 1.0f, 0, 0);
    sfxAllocateChannel(0x97, 1.0f);
    func_807149FC(0xC8);
    func_8071495C();
    func_8071498C(func_8071EFDC);
    func_80714CC0(&D_80720558, 1.0f, 160.0f, 120.0f, -10.0f);
}

void func_80687CC8(void) {
    sfxPlayOnFreeSlot(0xF2, 0x7FFF, 63.0f, 1.0f, 0, 0);
    sfxAllocateChannel(0x97, 1.0f);
    func_807149FC(0xC8);
    func_8071495C();
    func_8071498C(func_8071EFDC);
    func_80714CC0(&D_807210EC, 1.0f, 160.0f, 120.0f, -10.0f);
}
