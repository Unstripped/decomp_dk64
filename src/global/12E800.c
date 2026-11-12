#include "common.h"
#include "actor.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/127B00.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/AA960.h"
#include "proto/global/CEAE0.h"
#include "proto/global/FCCD0.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern void *gPlayerSlots;

typedef struct D1S174 {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ u32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[4];
    /* 0x1F8 */ u32 unk1F8;
} D1S174;


extern u8 gGameMode;
extern s32 gCurrentMap;

void behaviourFrameBegin(void) {
    gBehaviourWorkState = gCurrentActor->customState;
    gBehaviourTargetActor = gBehaviourWorkState->unk4;
    gBehaviourExtraState = (gBehaviourAnimState = gBehaviourWorkState->node);
    D_807FDCA0 = gBehaviourAnimState->zone;
    gBehaviourWorkState->stepCount++;
    if (gCurrentActor->flags & 0x20000000) {
        if (gCurrentActor->state != 0x37 && gCurrentActor->state != 0x36) {
            if (gBehaviourTargetActor->sub4->model->animId != gBehaviourWorkState->unk16) {
                gCurrentActor->flags &= ~0x20000000;
            }
        }
    }
    if (gCurrentActor->collisionFlags & 2) {
        if ((gGameMode == 1 && (gBehaviourAnimState->flags & 8)) || (gBehaviourTargetActor != NULL && gBehaviourTargetActor->state == 0x42)) {
            if (gCurrentActor->state >= 0x23 && gCurrentActor->state < 0x36) {
                gCurrentActor->unk144 = 1;
                gCurrentActor->state = 0x3A;
                gCurrentActor->unk155 = 0;
            }
        }
        if (gActorGlobalState.unk1B) {
            if (gCurrentActor->state != 0x39) {
                if (gBehaviourAnimState->flags & 0x800) {
                    gActorGlobalState.unk15 = 1;
                } else {
                    actorGlobalStateClearEvents();
                    gCurrentActor->callbackMask = 0;
                    gCurrentActor->flags &= 0xFFFD7FFF;
                    gCurrentActor->unk144 = 1;
                    gCurrentActor->state = 0x39;
                    gCurrentActor->unk155 = 0;
                    actorScriptStart(gCurrentActor, gBehaviourAnimState->animId2);
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0x14);
                    gCurrentActor->speedY = -220.0f;
                }
            }
        }
        if ((gBehaviourAnimState->flags & 0x4000) && (gCurrentActor->contactFlags & 4)) {
            if (gCurrentActor->y + gCurrentActor->eyeHeight < gCurrentActor->waterY) {
                gActorGlobalState.unk15 = 1;
            }
        }
        if (gCurrentMap == 0x30) {
            if (gBehaviourTargetActor->collisionFlags & 1) {
                if ((((PlayerState *)gBehaviourTargetActor->customState)->stateFlags ^ ((PlayerState *)gBehaviourTargetActor->customState)->prevStateFlags) & 0x100000) {
                    sfxStopSlotSound(gCurrentActor, 0);
                    gCurrentActor->state = 0;
                    gCurrentActor->unk155 = 0;
                    gActorGlobalState.unk15 = 1;
                }
            }
        }
    }
    if (gCurrentActor->actorType != 0xAF && gCurrentActor->state == 0x37 && gCurrentActor->callbackMask != 0) {
        gCurrentActor->callbackMask = 0;
    }
    collisionClearFlags();
}

void actorApplyGravity(void) {
    gCurrentActor->speedY = gCurrentActor->speedY + gCurrentActor->accelY;
    if (gCurrentActor->speedY < gCurrentActor->terminalSpeedY) {
        gCurrentActor->speedY = gCurrentActor->terminalSpeedY;
    }
}

void actorTurnTowardTarget(u8 mode, f32 targetX, f32 targetZ, u16 flags) {
    s16 *cur = &gCurrentActor->yaw;
    s16 *cur2 = &gCurrentActor->moveYaw;
    s16 *tgt = &gBehaviourWorkState->unk8;
    f32 spd;
    u8 s;
    s16 dist;
    s32 e;

    switch (mode) {
        case 1:
            if (gBehaviourWorkState->unk22-- == 0) {
                s = gBehaviourWorkState->unk21;
                *tgt = *cur + ((((randomNonNegative() >> 15) % (s * 2)) - s) << 15) / 0x168;
                gBehaviourWorkState->unk22 = gBehaviourWorkState->unk23;
                gBehaviourAnimState->flags &= ~0x2000;
                if (gCurrentActor->yaw & 1) {
                    gBehaviourWorkState->unk24 = (randomNonNegative() >> 15) % 0xB4;
                }
            }
            break;
        case 0x24:
            *tgt = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, targetX, targetZ);
            break;
        case 2:
        case 3:
        case 4:
        case 0x15:
        case 0x23:
        case 0x26:
        case 0x33:
        case 0x34:
        case 0x42:
        case 0x45:
        case 0x5B:
            *tgt = mathAngleBetweenPoints2D(targetX, targetZ, gCurrentActor->x, gCurrentActor->z);
            break;
        case 0x10:
            *tgt = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, targetX, targetZ);
            break;
        case 0x35:
            if ((randomNonNegative() >> 15) % 0x1E == 0) {
                gBehaviourWorkState->unk24 = (randomNonNegative() >> 15) % 0xB4;
            }
        case 7:
            *tgt = mathAngleBetweenPoints2D(gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, gCurrentActor->x, gCurrentActor->z);
            break;
        case 0:
            *tgt = *cur;
            break;
    }
    dist = mathAngleSignedDistance(*tgt, *cur);
    if (!(flags & 0x100) && mode != 0x37) {
        if (flags & 4) {
            spd = gBehaviourWorkState->unk1E;
        } else {
            spd = (gBehaviourWorkState->flags & 0x80)
                ? (gBehaviourWorkState->unk1E / 2)
                : (gBehaviourWorkState->unk1E /
                   (((0.1 < gCurrentActor->speedXZ / 30.0 ? gCurrentActor->speedXZ / 30.0 : 0.1) < 2.0)
                        ? (0.1 < gCurrentActor->speedXZ / 30.0 ? gCurrentActor->speedXZ / 30.0 : 0.1)
                        : 2.0));
        }
        *cur = mathAngleEaseToward(*cur, *tgt, spd);
        if ((gCurrentActor->contactFlags & 1) || (flags & 0x80) || (gCurrentActor->collisionFlags & 0x40)) {
            *cur2 = mathAngleEaseToward(*cur2, *cur, gBehaviourWorkState->unk1F);
        }
    }
    if (flags & 0x40) {
        gCurrentActor->pitch = (((dist > -0x320 ? dist : -0x320) < 0x320 ? (dist > -0x320 ? dist : -0x320) : 0x320) - gCurrentActor->pitch) * 0.1 + gCurrentActor->pitch;
    }
    if (flags & 4) {
        if (dist != 0) {
            f32 t = dist * gBehaviourAnimState->unk2C;
            f32 a = 0.0f < t ? t : -t;

            scriptSetActorRampTarget(gCurrentActor, a > 1.0 ? 1.0 : a, 0.0f);
        }
    }
}

typedef struct D1Tbl8075EB80 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 pad16[2];
} D1Tbl8075EB80; // size = 0x18

extern D1Tbl8075EB80 D_8075EB80[];

void behaviourUpdateShadowAlpha(void) {
    u8 a;
    u8 b;
    u8 c;
    D1Tbl8075EB80 *e;
    ActorSub4 *sub;

    if (!(gCurrentActor->flags & 0x1000000) && (gCurrentActor->flags & 4)) {
        if (!(gBehaviourAnimState->flags & 0x100)) {
            a = (gCurrentActor->alpha * 0.7);
            sub = gCurrentActor->sub4;
            e = &D_8075EB80[gBehaviourAnimState->entryIndex];
            b = (sub->scaleX * e->unk14 * gBehaviourAnimState->unk30);
            c = (sub->scaleZ * e->unk15 * gBehaviourAnimState->unk30);
            billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, b, c, 1, 0x12C, a, gCurrentActor->yaw, 1.0f);
        }
    }
}


extern u8 D_80720120[];
extern u16 D_80744508;

void behaviourCheckGroundImpactEffects(void) {
    if (gCurrentActor->collisionFlags & 2) {
        if (collisionIsGroundImpact() || collisionIsHeavyGroundImpact()) {
            if (collisionIsHeavyGroundImpact()) {
                effectCreateAtPosition(&D_80720120, gCurrentActor->sub4->scaleY * 6.66666666999999968, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
            gCurrentActor->state = 0x40;
            D_80744508++;
        }
    }
}

void actorUpdateStationaryTimer(void) {
    if (!(gBehaviourWorkState->flags & 0x40)) {
        if (gCurrentActor->x == gCurrentActor->prevX && gCurrentActor->z == gCurrentActor->prevZ) {
            gBehaviourWorkState->unk38++;
            if (gBehaviourWorkState->unk38 >= 0x1F) {
                gBehaviourWorkState->flags |= 0x40;
            }
        } else {
            gBehaviourWorkState->unk38 = 0;
        }
    }
}


void actorSetPitchVelocity(s16 arg0, f32 arg1, f32 arg2, f32 arg3, u16 arg4) {
    gCurrentActor->speedY = mathSinF(gCurrentActor->movePitch) * -arg3;
    actorMoveWithinZone(arg0, arg1, arg2, (arg4 & 0xFFFF) | 0x1080, 0.5 * gCurrentActor->eyeHeight);
}

void actorPitchEaseTowardPoint(s16 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, f32 arg6, f32 arg7, u16 arg8) {
    gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, (mathCalculatePitchAngle(arg2, arg3, arg4, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, arg5) * 2048.0 / 3.14159274101257324), arg6);
    gCurrentActor->movePitch = mathAngleEaseToward(gCurrentActor->movePitch, (mathCalculatePitchAngle(arg2, arg1 + arg3, arg4, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, arg5) * 2048.0 / 3.14159274101257324), arg6);
    actorSetPitchVelocity(arg0, arg2, arg4, arg7, arg8);
}

void func_8072AA80(void) {
    s16 lim;
    s32 rnd;
    s32 base;

    if (gBehaviourExtraState->unkAWide != 0) {
        lim = gBehaviourExtraState->y + gCurrentActor->eyeHeight + gBehaviourExtraState->unkAWide;
    } else {
        lim = (s16)gCurrentActor->waterY - gCurrentActor->eyeHeight;
    }
    rnd = (randomNonNegative() >> 15) % 0x7FFF;
    base = gBehaviourExtraState->y + gCurrentActor->eyeHeight;
    gBehaviourWorkState->targetY = rnd % (lim - base + 1) + base;
}

// Zone.unk19 is s8; this site reads it as u8 (lbu), so the view stays.
typedef struct E3DcA0 {
    /* 0x00 */ u8 pad0[0x19];
    /* 0x19 */ u8 unk19;
} E3DcA0;

#define E3CA0 ((E3DcA0 *)D_807FDCA0)


u32 actorMoveWithinZone(u8 state, f32 centerX, f32 centerZ, u16 flags, f32 floorYOffset) {
    f32 area;
    s16 zoneYaw;
    s16 *yawPtr;
    f32 pad0;
    f32 pad1;
    u8 result;

    area = gCurrentActor->sub4->scaleY / 0.15;
    result = 0;
    yawPtr = &gBehaviourWorkState->unk8;
    gBehaviourWorkState->unk1C = gBehaviourWorkState->flags;
    gBehaviourWorkState->flags &= 0xBD7F;
    if ((gCurrentActor->x - centerX) * (gCurrentActor->x - centerX) + (gCurrentActor->z - centerZ) * (gCurrentActor->z - centerZ) < 1600.0f * area) {
        gBehaviourWorkState->flags |= 0x80;
        if (mathAngleDistance(*yawPtr, gCurrentActor->yaw) >= 0x191) {
            gCurrentActor->speedXZ *= gBehaviourAnimState->unk34;
        }
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    if (gCurrentActor->speedXZ != 0.0f || (flags & 4)) {
        actorTurnTowardTarget(state, centerX, centerZ, flags);
    }
    if (!(flags & 0x1001)) {
        actorApplyGravity();
    }
    if (!(gBehaviourAnimState->flags & 0x200)) {
        collisionSetQueryMode(2);
    }
    if (E3CA0->unk19 == 1 && (state != 0x37 || !(gBehaviourAnimState->flags & 0x10))) {
        collisionSetQueryMode(1);
    }
    if (flags & 0x4000) {
        gCurrentActor->hasArcBounds = 0;
    }
    if (state != 0x37 && !(gBehaviourWorkState->flags & 2)) {
        actorStepPhysics(gCurrentActor, gCurrentActor->moveYaw, gCurrentActor->yaw);
    }
    if (flags & 2) {
        if (!(flags & 1)) {
            actorApplyVelocityCustom(gCurrentActor, 0, gCurrentActor->speedY);
        }
        actorUpdateFloorContactAndTilt(gCurrentActor, floorYOffset);
        if (!(flags & 0x2000)) {
            behaviourCheckGroundImpactEffects();
        }
        if (!(flags & 0x10)) {
            behaviourUpdateShadowAlpha();
        }
        return 0;
    }
    if (!(flags & 0x20)) {
        actorApproachTargetSpeed(flags);
    }
    if (flags & 0x800) {
        actorApplyVelocityCustom(gCurrentActor, 0, gCurrentActor->speedY);
    } else if (flags & 1) {
        actorApplyVelocityCustom(gCurrentActor, gCurrentActor->speedXZ, 0);
    } else {
        actorApplyVelocity(gCurrentActor);
    }
    if (!(flags & 8)) {
        actorUpdateFloorContactAndTilt(gCurrentActor, floorYOffset);
    } else if (E3CA0->unk19 != 1 && (flags & 0x10)) {
        collisionCheckActorFloor(gCurrentActor, gCurrentActor->x, gCurrentActor->prevY, gCurrentActor->z, &gCurrentActor->floorY);
    }
    if (!(flags & 0x2000)) {
        behaviourCheckGroundImpactEffects();
    }
    if (!(flags & 0x10)) {
        behaviourUpdateShadowAlpha();
    }
    gCurrentActor->hasArcBounds = 0;
    gCurrentActor->collisionHit = 0;
    if ((gBehaviourAnimState->flags & 0x20) || (gCurrentActor->collisionFlags & 0x40)) {
        return 0;
    }
    if (state == 0x37 && (gBehaviourAnimState->flags & 0x10)) {
        if (polygonContainsPoint2D(gCurrentActor->x, gCurrentActor->z, D_807FDCA0) == 0) {
            gCurrentActor->speedXZ = ((gCurrentActor->speedXZ >= 0.0f) ? 1 : -1) * 30;
            return 0;
        }
        gBehaviourWorkState->flags |= 0x4000;
        if (0) {} // FAKE: dead guard keeps a uopt block boundary
        return 0;
    }
    if (polygonContainsPoint2D(gCurrentActor->x, gCurrentActor->z, D_807FDCA0) != 0) {
        gBehaviourWorkState->flags |= 0x4000;
        if (zoneCheckActorInside(gCurrentActor, gCurrentActor->prevX, gCurrentActor->prevZ, D_807FDCA0, &zoneYaw) == 0) {
            if (polygonContainsPoint2D(mathSinF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ + gCurrentActor->x, mathCosF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ + gCurrentActor->z, D_807FDCA0) == 0) {
                if (gBehaviourWorkState->unk22-- == 0) {
                    *yawPtr += 0x800;
                    *yawPtr &= 0xFFF;
                    gBehaviourWorkState->unk22 = gBehaviourWorkState->unk23 * 4;
                }
            }
        } else if (state == 0x37 || state == 0) {
            gCurrentActor->speedXZ = 0.0f;
            gCurrentActor->x = gBehaviourWorkState->unk10;
            gCurrentActor->z = gBehaviourWorkState->unk14;
            return 0;
        }
        gBehaviourWorkState->unk10 = gCurrentActor->x;
        gBehaviourWorkState->unk14 = gCurrentActor->z;
    } else {
        result = 1;
        gBehaviourWorkState->flags |= 0x200;
        gCurrentActor->x = gBehaviourWorkState->unk10;
        gCurrentActor->z = gBehaviourWorkState->unk14;
        if (gBehaviourWorkState->unk22-- == 0) {
            *yawPtr += 0x800;
            *yawPtr &= 0xFFF;
            gBehaviourWorkState->unk22 = gBehaviourWorkState->unk23 * 6;
        }
    }
    return result;
}

typedef struct D1Unk174 {
    /* 0x00 */ u8 pad0[0x26];
    /* 0x26 */ s16 unk26;
} D1Unk174;

void actorSetTargetSpeed(Actor *actor, s32 speed) {
    D1Unk174 *s = actor->customState;
    s->unk26 = speed;
}


void actorUpdateAnimSpeedFromSpeed(u16 flags) {
    f32 t;

    t = (gCurrentActor->speedXZ * gBehaviourAnimState->unk38 > 3.0) ? 3.0 : gCurrentActor->speedXZ * gBehaviourAnimState->unk38;
    if (gCurrentActor->contactFlags & 4) {
        t *= 0.5;
    }
    if (!(gBehaviourAnimState->unk3C < t)) {
        t = gBehaviourAnimState->unk3C;
    }
    if (!((flags & 0x400) && t < 1.0)) {
        if (!(flags & 0x200) && t != gCurrentActor->sub4->unk48) {
            scriptSetActorRampTarget(gCurrentActor, t, 0.0f);
        }
    }
}


void actorApproachTargetSpeed(u16 flags) {
    s32 spd;
    f32 tgt;

    spd = gBehaviourWorkState->unk26;
    if (gCurrentActor->speedXZ < -60.0f) {
        if ((gCurrentActor->contactFlags & 1) && (gFrameCounter % 5) == 0) {
            behaviourSpawnDropParticle();
        }
    }
    tgt = spd;
    if (tgt != gCurrentActor->speedXZ) {
        if (gCurrentActor->speedXZ < tgt) {
            gCurrentActor->speedXZ = (tgt < gCurrentActor->speedXZ + gBehaviourWorkState->unk35) ? tgt : gCurrentActor->speedXZ + gBehaviourWorkState->unk35;
        } else if (tgt < gCurrentActor->speedXZ) {
            gCurrentActor->speedXZ = (gCurrentActor->speedXZ - gBehaviourWorkState->unk35 < tgt) ? tgt : gCurrentActor->speedXZ - gBehaviourWorkState->unk35;
        }
    }
    actorUpdateAnimSpeedFromSpeed(flags);
}

void actorSetBehaviourState(u8 state, s16 speed, s32 scriptId) {
    gCurrentActor->state = state;
    gCurrentActor->unk155 = 0;
    if (scriptId != gCurrentActor->sub4->animId) {
        actorScriptStart(gCurrentActor, scriptId);
    }
    actorSetTargetSpeed(gCurrentActor, speed);
}

void actorAddPulsingLight(void) {
    u32 phase;
    f32 x;
    f32 base;

    mathSinF((((gFrameCounter % 0xFFF) * 4) % 0xFFF));
    mathCosF((((gFrameCounter % 0xFFF) * 4) % 0xFFF));
    phase = (gFrameCounter * 4) % 150;
    base = 100.0f;
    if (phase > 75) {
        x = (phase - 75) + base;
    } else {
        x = base + 50.0 - phase;
    }
    lightAdd(gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z, 0.0f, 0.0f, 0.0f, x, 0, 0xFF, 0xFF, 0xFF);
}

void behaviourSetAnimIds(s16 anim0, s16 anim1, s16 anim2) {
    gBehaviourAnimState->animId0 = anim0;
    gBehaviourAnimState->animId1 = anim1;
    gBehaviourAnimState->animId2 = anim2;
}

extern u8 D_8071FC58[];

void behaviourUpdateContactAndState(s32 arg0) {
    actorUpdatePrevContactFlags(gCurrentActor);
    switch (gCurrentActor->state) {
        case 9:
            gBehaviourAnimState->flags |= 0x2040;
            gBehaviourAnimState->flags &= 0xFFF7;
            gBehaviourWorkState->unk22 = 0x64;
            gCurrentActor->state = 1;
            gCurrentActor->unk155 = 0;
            gCurrentActor->speedXZ = (((randomNonNegative() >> 0xF) % 50) + 0x3C);
            break;
        case 8:
            switch (gCurrentActor->unk155) {
                case 0:
                    gCurrentActor->unk15F = pathPlaybackStart(gCurrentActor, gBehaviourExtraState->yaw, 0, 0.0f, 0.0f, 0.0f, 0);
                    pathPlaybackSetSpeed(gCurrentActor->unk15F, (gBehaviourExtraState->targetSpeed * 0.1));
                    pathPlaybackSetLooping(gCurrentActor->unk15F, 1);
                    pathPlaybackSetLoopLimit(gCurrentActor->unk15F, -1);
                    pathPlaybackSetActive(gCurrentActor->unk15F, 1);
                    gCurrentActor->unk155++;
                case 1:
                    pathPlaybackAdvance(gCurrentActor->unk15F);
                    pathPlaybackGetPosition(gCurrentActor->unk15F, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
                    if (gBehaviourAnimState->unk38 != 0.0f) {
                        gCurrentActor->speedXZ = sqrtf(((gCurrentActor->x - gCurrentActor->prevX) * (gCurrentActor->x - gCurrentActor->prevX)) + ((gCurrentActor->y - gCurrentActor->prevY) * (gCurrentActor->y - gCurrentActor->prevY)) + ((gCurrentActor->z - gCurrentActor->prevZ) * (gCurrentActor->z - gCurrentActor->prevZ))) * 40.0f;
                        actorUpdateAnimSpeedFromSpeed(0);
                        func_8072E320(6.0f);
                    } else {
                        func_8072E320(0.0f);
                    }
                    break;
            }
            break;
        case 0x1C:
            switch (gCurrentActor->unk155) {
                case 0:
                    if (zoneFindBestReachablePoint(2, gCurrentActor, D_807FDCA0, &gBehaviourWorkState->targetX, &gBehaviourWorkState->targetY, &gBehaviourWorkState->targetZ) == 0) {
                        gCurrentActor->state = gBehaviourExtraState->actorState;
                        gCurrentActor->unk155 = 0;
                        break;
                    }
                    gCurrentActor->unk155 = 1;
                case 1:
                    actorPitchEaseTowardPoint(2, 0, gBehaviourWorkState->targetX, gBehaviourWorkState->targetY, gBehaviourWorkState->targetZ, 0x1E, 3.3f, 100.0f, 0x2240);
                    if (((gCurrentActor->z - gBehaviourWorkState->targetZ) * (gCurrentActor->z - gBehaviourWorkState->targetZ)) + (((gCurrentActor->x - gBehaviourWorkState->targetX) * (gCurrentActor->x - gBehaviourWorkState->targetX)) + ((gCurrentActor->y - gBehaviourWorkState->targetY) * (gCurrentActor->y - gBehaviourWorkState->targetY))) < 225.0f) {
                        actorScriptStart(gCurrentActor, gBehaviourAnimState->animId0);
                        gCurrentActor->unk155 = 2;
                    }
                    break;
                case 2:
                    if (((randomNonNegative() >> 0xF) % 1000) >= 0x3E4) {
                        actorScriptStart(gCurrentActor, gBehaviourAnimState->animId2);
                        gCurrentActor->unk155 = 3;
                    }
                    break;
                case 4:
                    actorSetDefaultState(gBehaviourAnimState->animId1);
                    break;
            }
            break;
        case 0x39:
            scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorMoveWithinZone(0, 0.0f, 0.0f, 0x202, 0.0f);
                    gCurrentActor->sub4->scaleY = gCurrentActor->sub4->scaleY * 0.7;
                    gCurrentActor->sub4->scaleX = gCurrentActor->sub4->scaleX * 1.07;
                    gCurrentActor->sub4->scaleZ = gCurrentActor->sub4->scaleZ * 1.07;
                    if (gCurrentActor->sub4->scaleY < 0.01) {
                        gCurrentActor->unk155 = 1;
                    }
                    break;
                case 1:
                    behaviourFadeOutWithinZone(0xA);
                    break;
                case 2:
                    gCurrentActor->state = 0x40;
                    D_80744508++;
                    break;
            }
            break;
        case 0:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x202, 0.0f);
            if (gCurrentActor->unk155 == 0) {
                actorSetTargetSpeed(gCurrentActor, 0);
                actorScriptStart(gCurrentActor, gBehaviourAnimState->animId0);
                gCurrentActor->unk155 = 1;
            }
            func_80724E48(0);
            break;
        case 0x19:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x202, 0.0f);
            if ((gBehaviourWorkState->timer % 15) == 0) {
                gBehaviourWorkState->unk24 = (randomNonNegative() >> 0xF) % 180;
            }
            func_80724E48(2);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, gBehaviourAnimState->animId0);
                    gCurrentActor->unk155 = 1;
                    break;
                case 1:
                    if (gBehaviourWorkState->timer != 0) {
                        gBehaviourWorkState->timer = gBehaviourWorkState->timer - 1;
                    } else {
                        actorSetDefaultState(gBehaviourAnimState->animId1);
                    }
                    break;
            }
            break;
        case 0x17:
            if ((gCurrentActor->contactFlags & 1) || (gCurrentActor->hasArcBounds != 0)) {
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkD);
                gCurrentActor->speedXZ = gBehaviourWorkState->unk26;
                gBehaviourWorkState->flags &= 0xFFFD;
                gCurrentActor->state = 0x23;
                gCurrentActor->unk155 = 0;
                actorScriptStart(gCurrentActor, gBehaviourAnimState->animId2);
            } else {
                gCurrentActor->yaw = gCurrentActor->yaw + (gCurrentActor->speedXZ * 2);
                actorMoveWithinZone(0x17, 0.0f, 0.0f, (gBehaviourWorkState->flags & 2) ? 0x1020 : 0x20, 0.0f);
            }
            break;
        case 0x3A:
            if (gCurrentActor->unk155 == 0) {
                if (gActorGlobalState.unk15 == 0) {
                    scriptSetActorRampTarget(gCurrentActor, 0.0f, 8.0f);
                    actorSetTargetSpeed(gCurrentActor, 0);
                }
                gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
            } else if ((gGameMode == 0) && (gBehaviourTargetActor->state != 0x42)) {
                gCurrentActor->interactionType = 1;
                gCurrentActor->unk144 = 0x24;
                gCurrentActor->state = gBehaviourExtraState->actorState;
                gCurrentActor->unk155 = 0;
                actorScriptStart(gCurrentActor, gBehaviourAnimState->animId1);
                scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
            }
            break;
        case 0x16:
            if (gCurrentActor->unk155 == 0) {
                gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
            } else {
                gCurrentActor->yaw += 0x64;
                if (gFrameCounter & 1) {
                    gCurrentActor->y += 1.0f;
                }
                if (gPrimaryPlayerActor->state != 0x67) {
                    actorQueueDelayedCallback(gCurrentActor, 0, 8, 0, 0, 0, 1);
                }
            }
            break;
        case 0x36:
            switch (gCurrentActor->unk155) {
                case 0:
                    gCurrentActor->flags &= 0xFFFD7FFF;
                    gCurrentActor->callbackMask &= 0xFFFF7FFF;
                    gCurrentActor->alpha = 0;
                    gBehaviourWorkState->unk39 = 0x5A;
                    gBehaviourWorkState->unk2E = gCurrentActor->sub4->scaleY * gCurrentActor->collision->scaledRadius;
                    gCurrentActor->y -= gBehaviourWorkState->unk2E;
                    gCurrentActor->unk72 = 0;
                    gCurrentActor->unk155++;
                    break;
                case 1:
                    effectSetCallback(func_80717D4C);
                    effectSetDepth(1);
                    effectSetSpeed(-0x28 - (((randomNonNegative() >> 0xF) % 10000) % 120));
                    effectCreateAtPosition(D_8071FC58, 0.5f, ((((randomNonNegative() >> 0xF) % 20) + gBehaviourExtraState->x) - 0xA), gBehaviourExtraState->y, ((((randomNonNegative() >> 0xF) % 20) + gBehaviourExtraState->z) - 0xA));
                    if (gBehaviourWorkState->unk39 != 0) {
                        f32 t;

                        gBehaviourWorkState->unk39 = gBehaviourWorkState->unk39 - 1;
                        t = gBehaviourWorkState->unk39 / 90.0f;
                        gCurrentActor->y = gBehaviourExtraState->y + (((gBehaviourExtraState->y - gBehaviourWorkState->unk2E) - gBehaviourExtraState->y) * t);
                        if (gCurrentActor->soundSlots[0] == -1) {
                            gCurrentActor->soundSlots[0] = sfxSlotAllocateActor(gCurrentActor, 0x131, 0, 0, 0xFF, 1.0f, 0);
                        }
                        gCurrentActor->unk74 = gBehaviourExtraState->y - gCurrentActor->y;
                        gCurrentActor->unk72 = gCurrentActor->unk72 + 1;
                        gCurrentActor->yaw = gCurrentActor->yaw + ((gBehaviourExtraState->y - gCurrentActor->y) * 60.0f);
                        gCurrentActor->alpha = (-255.0f * t) + 255.0f;
                    } else {
                        sfxStopSlotSound(gCurrentActor, 0);
                        gCurrentActor->state = gBehaviourExtraState->actorState;
                        gCurrentActor->unk155 = 0;
                        gCurrentActor->flags |= 0x28000;
                        gCurrentActor->callbackMask |= 0x8000;
                        gCurrentActor->alpha = 0xFF;
                        gCurrentActor->y = gBehaviourExtraState->y;
                    }
                    break;
            }
            break;
        case 0x3D:
            actorSetBehaviourState(0x3F, 0, arg0);
            break;
        case 0x3E:
            actorSetBehaviourState(1, gBehaviourExtraState->targetSpeed, arg0);
            break;
        case 0x3F:
            func_80724E48(0);
            break;
    }
}

typedef struct D1S174b {
    /* 0x000 */ u8 pad0[0xD4];
    /* 0x0D4 */ s16 unkD4;
    /* 0x0D6 */ u8 padD6[0x11A];
    /* 0x1F0 */ u32 unk1F0;
} D1S174b;

typedef struct D1PlayerView {
    /* 0x000 */ u8 pad0[0x2C0];
    /* 0x2C0 */ u8 unk2C0;
} D1PlayerView;


extern u8 gPlayerCount;
extern u32 gGlobalOverlayFlags;

u8 behaviourCheckTargetCollisionMode(u8 checkMode, u8 *outTarget) {
    D1S174b *st = gBehaviourTargetActor->customState;
    u8 ret;
    u8 t;

    *outTarget = 1;
    if (gCurrentActor->collisionFlags & 2) {
        if (gCurrentActor->state != 0x15 &&
            ((gBehaviourTargetActor->actorType == 6 && ((D1PlayerView *)gPlayerSlots)->unk2C0 == 2 && gPlayerCount == 1) ||
             ((gBehaviourTargetActor->collisionFlags & 1) && (st->unk1F0 & 0x10)))) {
            ret = 7;
        } else if (gBehaviourWorkState->unk37 == 7 && checkMode != 0 && !(gBehaviourWorkState->flags & 0x200) && gBehaviourWorkState->unk20 == 0) {
            gBehaviourWorkState->unk20 = 0x10;
            if (zoneFindBestReachablePoint(0x81, gCurrentActor, D_807FDCA0, &gBehaviourWorkState->targetX, &gBehaviourWorkState->targetY, &gBehaviourWorkState->targetZ) == 0) {
                ret = 0x10;
            } else {
                ret = 7;
            }
        } else {
            if (gBehaviourWorkState->unk20 != 0) {
                gBehaviourWorkState->unk20 = gBehaviourWorkState->unk20 - 1;
            }
            if ((gBehaviourTargetActor->collisionFlags & 1) && st->unkD4 != 0 && !(gGlobalOverlayFlags & 0x100000)) {
                ret = 1;
                *outTarget = 0;
            } else if (gBehaviourWorkState->flags & 0x400) {
                ret = gBehaviourWorkState->unk37;
            } else {
                t = gBehaviourExtraState->actorState;
                if (t == 7) {
                    ret = 1;
                } else {
                    ret = t;
                }
            }
        }
    } else {
        ret = gBehaviourExtraState->actorState;
    }
    if (ret == 9) {
        ret = 1;
    }
    return ret;
}


void func_8072C870(u8 state, u8 subState, s32 param) {
    if (state == 7) {
        if (zoneFindBestReachablePoint(1, gCurrentActor, D_807FDCA0, &gBehaviourWorkState->targetX, &gBehaviourWorkState->targetY, &gBehaviourWorkState->targetZ) == 0) {
            state = 0x10;
            actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkD);
        }
    }
    gBehaviourWorkState->unk36 = state;
    actorSetBehaviourState(state, subState, param);
}

typedef struct C1Act {
    /* 0x000 */ Actor base;
    /* 0x178 */ s16 *unk178; // second component pointer
} C1Act;

#define C1B40 ((C1Act *)gCurrentActor)

void enemyAggroStateUpdate(s32 aggroDist, s32 arg1, s32 arg2) {
    D1S174 *st;
    s32 dist;
    u8 pad0;
    u8 type;
    u8 hasTarget;
    s16 ang;
    u32 ret;
    s32 near;
    Actor *me;

    st = gBehaviourTargetActor->customState;
    me = gCurrentActor;
#define SQ(x) ((x) * (x))
    dist = (SQ(me->x - gBehaviourTargetActor->x) + SQ(me->y - gBehaviourTargetActor->y) + SQ(me->z - gBehaviourTargetActor->z));
    near = dist < aggroDist;
    if (near == 0) {
        near = (gBehaviourAnimState->flags & 4) != 0;
    }
    if (gBehaviourWorkState->unk8 < me->moveYaw) {
        ang = me->moveYaw - gBehaviourWorkState->unk8;
    } else {
        ang = gBehaviourWorkState->unk8 - me->moveYaw;
    }
    if ((zoneCanReachPoint(me, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, D_807FDCA0) != 0) && !(gBehaviourAnimState->flags & 0x2000) && !(st->unk1F0 & 0x8000)) {
        gBehaviourWorkState->flags |= 0x400;
    } else {
        gBehaviourWorkState->flags &= 0xFBFF;
    }
    ret = behaviourCheckTargetCollisionMode(dist < 0x1388, &hasTarget);
    type = ret;
    if (ang != 0) {} // FAKE: class-2 dead use of ang reorders colouring (Q0589)
    switch (gCurrentActor->state) {
        case 1:
        case 2:
        case 3:
            if (gCurrentActor->sub4->animId == gBehaviourAnimState->animId0) {
                actorScriptStart(gCurrentActor, gBehaviourAnimState->animId1);
            }
            if (gBehaviourWorkState->unk26 != gBehaviourExtraState->targetSpeed) {
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
            }
        case 4:
        case 0x11:
        case 0x19:
            if ((near & 0xFF) && (gCurrentActor->flags & 0x100) && (hasTarget != 0) && (gBehaviourWorkState->flags & 0x400)) {
                if (gBehaviourWorkState->flags & 0x800) {
                    if (behaviourIsTargetWithinAngle(0x2710) != 0) {
                        actorSetBehaviourState(type, gBehaviourExtraState->unkD, arg2);
                        return;
                    }
                }
                if (!(gBehaviourWorkState->flags & 0x800)) {
                    actorSetBehaviourState(type, gBehaviourExtraState->unkD, arg2);
                    return;
                }
            }
            break;
        case 0x34:
            me = (Actor *)C1B40->unk178; // FAKE: reuses me for the second component pointer
            if (dist < *(s16 *)me) {
                actorSetBehaviourState(0x24, 0, arg1);
                return;
            }
        case 0x23:
            if ((ret ^ 0) == gBehaviourWorkState->unk36) { // FAKE: flips beq operand order (field left)
            } else if ((hasTarget == 0) || ((s32)ret >= 7)) {
                func_8072C870(type, gBehaviourExtraState->unkD, arg2);
                return;
            }
            if (near & 0xFF) {
                if (!(gBehaviourWorkState->flags & 0x400)) {
                    actorSetBehaviourState(0x35, (gBehaviourExtraState->targetSpeed * 0.667), arg1);
                    gBehaviourWorkState->unk20 = 0x3C;
                    gBehaviourWorkState->targetX = gBehaviourTargetActor->prevX;
                    gBehaviourWorkState->targetY = gBehaviourTargetActor->prevY;
                    gBehaviourWorkState->targetZ = gBehaviourTargetActor->prevZ;
                    return;
                }
                if (gBehaviourWorkState->unk26 < gBehaviourExtraState->unkD) {
                    actorSetBehaviourState(type, gBehaviourExtraState->unkD, arg2);
                    return;
                }
            } else {
                actorSetBehaviourState(gBehaviourExtraState->actorState, gBehaviourExtraState->targetSpeed, arg1);
                return;
            }
            break;
        case 0x33:
            if ((!(near & 0xFF) || !(gBehaviourWorkState->flags & 0x400)) && (gCurrentActor->contactFlags & 1)) {
                actorSetBehaviourState(gBehaviourExtraState->actorState, gBehaviourExtraState->targetSpeed, arg1);
                return;
            }
            break;
        case 7:
            if ((SQ(gCurrentActor->z - gBehaviourWorkState->targetZ) + SQ(gCurrentActor->x - gBehaviourWorkState->targetX)) < 400.0f) {
                if (!(gBehaviourWorkState->flags & 0x80)) {
                    actorSetDefaultState(gBehaviourAnimState->animId1);
                } else {
                    func_8072C870(7, gBehaviourExtraState->unkD, arg2);
                }
            }
        case 0x10:
            if (type != gBehaviourWorkState->unk36) {
                func_8072C870(type, gBehaviourExtraState->unkD, arg2);
            }
            if (near & 0xFF) {
                if (!(gBehaviourWorkState->flags & 0x400)) {
                    actorSetBehaviourState(gBehaviourExtraState->actorState, gBehaviourExtraState->targetSpeed, arg1);
                    return;
                }
            } else {
                actorSetBehaviourState(gBehaviourExtraState->actorState, gBehaviourExtraState->targetSpeed, arg1);
                return;
            }
            break;
        case 0x35:
            if (gBehaviourWorkState->flags & 0x400) {
                actorSetBehaviourState(type, gBehaviourExtraState->unkD, arg2);
                return;
            }
            near = (gBehaviourWorkState->unk20-- == 0);
            if (near) {
                actorSetBehaviourState(gBehaviourExtraState->actorState, gBehaviourExtraState->targetSpeed, arg1);
            }
            break;
    }
}

void patrolGetNextWaypointPos(s16 *outX, s16 *outY, s16 *outZ) {
    s32 temp;
    u8 idx;
    s32 v;
    u8 new_var;

    new_var = gBehaviourWorkState->unk25 & 0x7F;
    temp = new_var + 1;
    idx = (temp < gBehaviourExtraState->pathCount) ? temp : 0;
    v = gBehaviourAnimState->path[idx][0];
    *outX = D_807FDCA0->entries[v].x;
    *outY = D_807FDCA0->entries[v].y;
    *outZ = D_807FDCA0->entries[v].z;
}

s32 patrolGetTargetAngle(void) {
    u8 idx;
    u8 key;
    s16 x;
    s16 y;
    s16 z;

    idx = gBehaviourWorkState->unk25 & 0x7F;
    key = gBehaviourAnimState->path[idx][0];
    patrolGetNextWaypointPos(&x, &y, &z);
    return mathAngleBetweenPoints2D(x, z, D_807FDCA0->entries[key].x, D_807FDCA0->entries[key].z);
}

u8 patrolPathStep(u8 state, u8 flags) {
    u8 dir;
    u8 pad;
    u8 key;
    u8 type;
    s16 x;
    s16 y;
    s16 z;
    u8 moved;
    u8 next;
    u8 idx;
    u8 nextKey;
    s32 v;

    idx = gBehaviourWorkState->unk25;
    dir = idx;
    dir &= 0x80;
    idx &= 0x7F;
    key = gBehaviourAnimState->path[idx][0];
    type = gBehaviourAnimState->path[idx][1];
    x = D_807FDCA0->entries[key].x;
    y = D_807FDCA0->entries[key].y;
    z = D_807FDCA0->entries[key].z;
    moved = ((gCurrentActor->x - x) * (gCurrentActor->x - x)) + ((gCurrentActor->z - z) * (gCurrentActor->z - z)) <
            (D_807FDCA0->entries[key].radius * D_807FDCA0->entries[key].radius);
    if ((flags & 1) && gCurrentActor->x == gCurrentActor->prevX && gCurrentActor->z == gCurrentActor->prevZ) {
        if (gBehaviourWorkState) {} // FAKE: two uopt blocks in idx's live range drop its priority below key's (key t2, idx t3)
        gBehaviourWorkState->unk20++;
        if (gBehaviourWorkState->unk20++ > 0x10) {
            moved = 1;
            gBehaviourWorkState->unk20 = 0;
        }
    } else {
        gBehaviourWorkState->unk20 = 0;
    }
    switch (state) {
        case 0x49:
            v = idx + 1;
            next = (v < gBehaviourExtraState->pathCount) ? v : 0;
            v = gBehaviourAnimState->path[next][0];
            v = mathAngleBetweenPoints2D(D_807FDCA0->entries[v].x, D_807FDCA0->entries[v].z, x, z);
            gCurrentActor->moveYaw = v;
            gCurrentActor->yaw = v;
        case 0x42:
        case 0x5B:
            gBehaviourWorkState->targetX = x;
            gBehaviourWorkState->targetY = y;
            gBehaviourWorkState->targetZ = z;
            break;
        case 2:
        case 0x26:
        case 0x60:
            if (moved) {
                if (type == 6) {
                    gBehaviourWorkState->unk25 = D_807FDCA0->entries[key].height;
                } else if (idx + 1 < gBehaviourExtraState->pathCount) {
                    gBehaviourWorkState->unk25 = idx + 1;
                } else {
                    gBehaviourWorkState->unk25 = 0;
                }
            } else {
                gBehaviourWorkState->targetX = x;
                gBehaviourWorkState->targetY = y;
                gBehaviourWorkState->targetZ = z;
            }
            break;
        case 3:
            if (moved) {
                if (dir) {
                    if (idx > 0) {
                        idx--;
                    } else {
                        idx++;
                        dir = 0;
                    }
                } else if (idx < gBehaviourExtraState->pathCount - 1) {
                    idx++;
                } else {
                    idx--;
                    dir = 0x80;
                }
                gBehaviourWorkState->unk25 = dir | idx;
            } else {
                gBehaviourWorkState->targetX = x;
                gBehaviourWorkState->targetY = y;
                gBehaviourWorkState->targetZ = z;
            }
            break;
    }
    idx = gBehaviourWorkState->unk25 & 0x7F;
    if (moved) {
        gBehaviourWorkState->flags |= 4;
        switch (type) {
            case 1:
                nextKey = gBehaviourAnimState->path[idx][0];
                v = patrolGetTargetAngle();
                gCurrentActor->moveYaw = v;
                gCurrentActor->yaw = v;
                gCurrentActor->x = D_807FDCA0->entries[nextKey].x;
                gCurrentActor->y = D_807FDCA0->entries[nextKey].y;
                gCurrentActor->z = D_807FDCA0->entries[nextKey].z;
                break;
            case 2:
                gCurrentActor->state = 0x26;
                gCurrentActor->unk155 = 0;
                break;
            case 4:
                gCurrentActor->state = 0x19;
                gCurrentActor->unk155 = 0;
                gBehaviourWorkState->timer = D_807FDCA0->entries[key].height;
                break;
            case 5:
                actorSetTargetSpeed(gCurrentActor, D_807FDCA0->entries[key].height);
                break;
            case 7:
                gCurrentActor->state = 0x3B;
                moved = 0;
                break;
            case 8:
                gCurrentActor->state = 0x13;
                gCurrentActor->unk155 = 0;
                break;
            case 3:
                if (gCurrentActor->actorType == 0xAF) {
                    gCurrentActor->state = 0x37;
                    gCurrentActor->unk155 = 0;
                }
                D_80744508++;
                gCurrentActor->state = 0x40;
                break;
        }
    } else {
        gBehaviourWorkState->flags &= 0xFFFB;
    }
    return moved;
}

void func_8002D7E8(s16);

void behaviourCalculateDamageForce(Actor *attacker, s32 scriptId) {
    f64 pad;
    f64 f;
    s32 mask;
    f64 raw;
    f32 rounded;
    f32 x;
    f32 cur;

    mask = 0xFFFF7FFF;
    if (attacker != NULL) {
        raw = (gCurrentActor->health - 1) * -0.6;
        f = (2.0 < raw) ? 2.0 : raw;
        gCurrentActor->moveYaw = (attacker->moveYaw + 0x800) & 0xFFF;
        if (attacker == gBehaviourTargetActor) {
            if (mathAngleDistance(attacker->moveYaw, attacker->yaw) > 0x400) {
                gCurrentActor->moveYaw += 0x800;
            }
        }
        actorSetBehaviourState(0x37, 0, scriptId);
        rounded = (f + 0.5);
        cur = attacker->speedXZ;
        x = 66.0f * rounded;
        gCurrentActor->speedXZ = -(((x < attacker->speedXZ ? attacker->speedXZ : x) < 150.0f) ? (x < attacker->speedXZ ? attacker->speedXZ : x) : 150.0f);
        if (attacker->sub4 != NULL) {
            gCurrentActor->speedXZ = gCurrentActor->speedXZ * (attacker->sub4->scaleY / 0.15);
        }
    } else {
        actorSetBehaviourState(0x37, 0, scriptId);
        gCurrentActor->speedXZ = -60.0f;
    }
    gCurrentActor->callbackMask &= mask;
    gCurrentActor->flags &= 0xFFFF7FFF;
    if (attacker == NULL || attacker == gBehaviourTargetActor || attacker->actorType == 0x2B) {
        behaviourSpawnPuffParticle();
    }
    D_80744508++;
    if (gCurrentMap == 0xBF) {
        func_8002D7E8(gCurrentActor->actorType);
    }
}

void behaviourSetFloorAndState40(void) {
    gCurrentActor->unk144 = 1;
    gCurrentActor->state = 0x40;
    D_80744508++;
}

extern u8 D_8071FB34[];

void behaviourSpawnPuffParticle(void) {
    effectCreateAtPosition(&D_8071FB34, 0.55f, gCurrentActor->x, gCurrentActor->y + gCurrentActor->eyeHeight * 0.5, gCurrentActor->z);
}


void sfxPlayAtFBD6CPosition(void) {
    effectCreateAtPosition(&D_8071FB34, 0.55f, gActorGlobalState.targetActor->x, gActorGlobalState.targetActor->y, gActorGlobalState.targetActor->z);
}

extern u8 D_8071FF18;

void behaviourSpawnDropParticle(void) {
    effectSetMode(2);
    effectSetDepth(1);
    effectSetCallback(func_80717D4C);
    effectSetSpeed(-0x28 - ((randomNonNegative() >> 15) % 15));
    effectCreateAtPosition(&D_8071FF18, (((randomNonNegative() >> 15) % 1000) / 2000.0 + 0.5), gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
}

extern u8 gCurrentPlayerIndex;

void behaviourAddSlotQueueValueB(s32 value) {
    u8 cnt;
    s16 i;

    if (slotQueueGetValue(0xB, gCurrentPlayerIndex) >= 4) {
        cnt = 3;
    } else {
        cnt = slotQueueGetValue(0xB, gCurrentPlayerIndex);
    }
    slotQueueAddValue(0xB, gCurrentPlayerIndex, -cnt);
    slotQueueUpdate(0xB, 0, 0);
    sfxAllocateChannel(0x41, 1.0f);
    for (i = 0; i < cnt; i++) {
        actorSpawnNodeEntryScaled(0x36, gPrimaryPlayerActor->x, gPrimaryPlayerActor->y, gPrimaryPlayerActor->z, gPrimaryPlayerActor->yaw + i * 200 - 200, 1, -1, 0);
    }
}

void behaviourFadeOutWithinZone(u8 step) {
    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x32, 0.0f);
    gCurrentActor->alpha -= step;
    if (gCurrentActor->alpha < 0) {
        gCurrentActor->unk155++;
        gCurrentActor->alpha = 0;
    }
}

s32 actorIsTargetWithinAngleDeg(Actor *self, Actor *target, u16 maxDiff) {
    f32 deg = mathAngleBetweenPointsDeg(target->x, target->z, self->x, self->z);
    s16 a = self->yaw / 4095.0 * 65536.0;
    f32 t = 360.0 - deg;
    s16 b = t / 360.0 * 65536.0;
    s32 diff;

    if (a < b) {
        diff = b - a;
    } else {
        diff = a - b;
    }
    if (diff < maxDiff) {
        if (camIsCutsceneActive() == 0) {
            return 1;
        }
    }
    return 0;
}

s32 behaviourIsTargetWithinAngle(u16 maxDiff) {
    return actorIsTargetWithinAngleDeg(gCurrentActor, gBehaviourTargetActor, maxDiff);
}

void actorSetDefaultState(s32 scriptId) {
    gCurrentActor->state = gBehaviourExtraState->actorState;
    gCurrentActor->unk155 = 0;
    actorScriptStart(gCurrentActor, scriptId);
    actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
}

void behaviourSpawnExplosionAndSound(s32 scriptId, u8 state, Actor *attacker) {
    f32 speed;

    behaviourSpawnPuffParticle();
    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1CA, 0xFF, 0x7F, 0x14);
    if (attacker != NULL) {
        if (attacker->collisionFlags & 4) {
            gCurrentActor->moveYaw = (attacker->moveYaw + 0x800) & 0xFFF;
        } else {
            gCurrentActor->moveYaw = (attacker->yaw + 0x800) & 0xFFF;
        }
        actorSetBehaviourState(state, 0, scriptId);
        speed = attacker->speedXZ;
        gCurrentActor->speedXZ = -(((speed > 60.0f ? speed : 60.0f) < 150.0f) ? (speed > 60.0f ? speed : 60.0f) : 150.0f);
    } else {
        actorSetBehaviourState(state, 0, scriptId);
    }
    if (attacker == gBehaviourTargetActor) {
        gBehaviourWorkState->unk16 = gBehaviourTargetActor->sub4->model->animId;
        gCurrentActor->flags |= 0x20000000;
    }
}

void actorRollEaseZero(void) {
    gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, 0, 5.0f);
    gCurrentActor->pitch = gCurrentActor->pitch + (-gCurrentActor->pitch) * 0.1;
}

u8 behaviourIsTargetWithinRadiusAndAngle(s32 radius, s16 maxAngle) {
    u8 close;
    s16 ang;
    s16 diff;

    close = (((gBehaviourTargetActor->x - gCurrentActor->x) * (gBehaviourTargetActor->x - gCurrentActor->x) + (gBehaviourTargetActor->z - gCurrentActor->z) * (gBehaviourTargetActor->z - gCurrentActor->z)) < (radius * radius));
    ang = mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->z);
    if (ang < gCurrentActor->yaw) {
        diff = gCurrentActor->yaw - ang;
    } else {
        diff = ang - gCurrentActor->yaw;
    }
    if (diff > 0x800) {
        diff = 0x1000 - diff;
    }
    return diff < maxAngle && close && gBehaviourTargetActor->state != 0x42;
}

void actorTurnTowardActorYaw(u8 rate, Actor *target) {
    gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, mathAngleBetweenPoints2D(target->x, target->z, gCurrentActor->x, gCurrentActor->z), rate);
}

u8 actorIsTargetWithinDistance(u16 radius) {
    f32 dx = gCurrentActor->x - gBehaviourTargetActor->x;
    f32 dy = gCurrentActor->y - gBehaviourTargetActor->y;
    f32 dz = gCurrentActor->z - gBehaviourTargetActor->z;

    return (dx * dx + dy * dy + dz * dz) < (radius * radius);
}

void actorGetNodePosOrPosition(Actor *actor, f32 *outX, f32 *outY, f32 *outZ) {
    if (actor->floorNodeId) {
        actorGetNodePos(actor, actor->floorNodeId, outX, outY, outZ);
    } else {
        *outX = actor->x;
        *outY = actor->y;
        *outZ = actor->z;
    }
}

#define E2_MAX(a, b) ((a) > (b) ? (a) : (b))
#define E2_MIN(a, b) ((a) < (b) ? (a) : (b))

void func_8072E320(f32 arg0) {
    f32 v;

    gCurrentActor->moveYaw = gCurrentActor->yaw;
    gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, gCurrentActor->prevX, gCurrentActor->prevZ), 3.3f);
    v = E2_MIN(E2_MAX(mathAngleSignedDistance(gCurrentActor->yaw, gCurrentActor->moveYaw) * arg0, -900.0f), 900.0f);
    gCurrentActor->pitch = (v - gCurrentActor->pitch) * 0.1 + gCurrentActor->pitch;
    gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, mathCalculatePitchAngle(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, gCurrentActor->prevX, gCurrentActor->prevY, gCurrentActor->prevZ, 0x1E) * 2048.0 / 3.1415927f, 3.3f);
}

u8 behaviourCheckRandomAnimTrigger(void) {
    return !(gBehaviourAnimState->flags & 0x2000) && (((randomNonNegative() >> 15) % 1000) >= 0x3E4);
}
