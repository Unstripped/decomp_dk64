#include "common.h"
#include "actor.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/42630.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/80150.h"
#include "proto/global/89250.h"
#include "proto/global/936B0.h"
#include "proto/global/A2F10.h"
#include "proto/global/AA960.h"
#include "proto/global/B7490.h"
#include "proto/global/CEAE0.h"

// Per-type view: 0x178 is this actor type's second component pointer (see Actor).
typedef struct B7490Actor {
    /* 0x000 */ Actor base;
    /* 0x178 */ void *typeState;
} B7490Actor;

#define B7490A ((B7490Actor *)gCurrentActor)
#define B7490MAXD(a, b) ((a) < (b) ? (b) : (a))

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern PlayerState *gActivePlayerState;
extern s32 gCurrentMap;
extern EffectGridAsset D_8072073C;
extern s16 gFlyPatrolShotInterval;


void behaviourSwimLungeUpdate(void) {
    u8 flag;
    s32 st;

    behaviourFrameBegin();
    if (((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0)) && (gCurrentActor->state != 0x37)) {
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x2E1);
        gBehaviourAnimState->flags |= 8;
    }
    effectSpawnSparks(0x1F, 0);
    st = gCurrentActor->state;
    switch (st) {
        case 0x27:
            flag = 0;
            switch (gCurrentActor->unk155) {
                case 0:
                    actorScriptStart(gCurrentActor, 0x2E0);
                    gCurrentActor->unk155 = 1;
                    break;
                case 2:
                    flag = 1;
                    gCurrentActor->speedXZ = 150.0f;
                    gCurrentActor->interactionType = 2;
                    break;
                case 3:
                    gCurrentActor->interactionType = 1;
                    flag = 1;
                    break;
                case 4:
                    actorSetDefaultState(0x2DE);
                    break;
            }
            st = gCurrentActor->state;
            if (flag) {
                actorSetPitchVelocity(st, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 100.0f, 0x2240);
            }
            break;
        case 1:
            gCurrentActor->pitch += 800.0f * mathSinF(gBehaviourWorkState->stepCount * 10);
            if (((randomNonNegative() >> 15) % 1000) >= 0x3D5) {
                behaviourPickRandomTargetY();
            }
            actorPitchEaseTowardPoint(gCurrentActor->state, 0, gBehaviourTargetActor->x, gBehaviourWorkState->targetY, gBehaviourTargetActor->z, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x10:
        case 0x23:
            gCurrentActor->pitch += 800.0f * mathSinF(gBehaviourWorkState->stepCount * 15);
            actorPitchEaseTowardPoint(gCurrentActor->state, 0, gBehaviourTargetActor->x, ((gCurrentActor->waterY - gCurrentActor->eyeHeight) < gBehaviourTargetActor->y) ? (gCurrentActor->waterY - gCurrentActor->eyeHeight) : gBehaviourTargetActor->y, gBehaviourTargetActor->z, 0x1E, 3.3f, 100.0f, 0x2040);
            if (gActorGlobalState.bossFightPhase == 2) {
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            actorPitchEaseTowardPoint(st, 0, gBehaviourWorkState->targetX, (gBehaviourWorkState->targetY < (gCurrentActor->waterY - gCurrentActor->eyeHeight)) ? gBehaviourWorkState->targetY : (gCurrentActor->waterY - gCurrentActor->eyeHeight), gBehaviourWorkState->targetZ, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x37:
            switch (gCurrentActor->unk155) {
                case 0:
                    gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, 0, 7.0f);
                    break;
                case 1:
                    behaviourFadeOutWithinZone(0x14);
                    break;
                case 2:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        default:
            behaviourUpdateContactAndState(0x2DE);
            break;
    }
    st = gCurrentActor->state;
    switch (st) {
        case 0x31:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->state, 1);
        default:
            enemyAggroStateUpdate(0x6400, 0x2DE, 0x2DE);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorEmptyStub(void) {
}

void behaviourSwimShooterUpdate(void) {
    behaviourFrameBegin();
    effectSpawnSparks(0x1F, 2);
    if (((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0)) && (gCurrentActor->state != 0x37)) {
        gBehaviourAnimState->flags |= 8;
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x2E7);
    } else if (gActorGlobalState.bossFightPhase == 4) {
        behaviourSpawnExplosionAndSound(0x2E5, 0x31, gActorGlobalState.targetActor);
        gCurrentActor->speedXZ = 0.0f;
    }
    switch (gCurrentActor->state) {
        case 0x31:
            effectSpawnSparks(0x1F, 2);
            if ((gCurrentActor->unk155 != 0) || (gCurrentActor->sub4->model->speed == 0.0f)) {
                actorSetDefaultState(0x2E2);
            }
            break;
        case 0x27:
            switch (gCurrentActor->unk155) {
                case 0:
                    actorScriptStart(gCurrentActor, 0x2E6);
                    gCurrentActor->unk155 = 1;
                    break;
                case 2:
                    gCurrentActor->interactionType = 2;
                    break;
                case 3:
                    gCurrentActor->interactionType = 1;
                    break;
                case 4:
                    actorSetDefaultState(0x2E2);
                    break;
            }
            break;
        case 0x25:
            switch (gCurrentActor->unk155) {
                case 0:
                    actorScriptStart(gCurrentActor, 0x2E4);
                    gCurrentActor->unk155 = 1;
                    break;
                case 2:
                    projectileGetTargetCoords(gCurrentActor, 1);
                    projectileSpawnNodeEntry(0x112, 0, 0.3f, gCurrentActor->yaw, 300.0f, mathSinF(gCurrentActor->roll) * 300.0f, gCurrentActor);
                    effectSpawnSparks(1, 1);
                    break;
                case 3:
                    actorSetDefaultState(0x2E2);
                    break;
            }
            break;
        case 1:
            actorEmptyStub();
            gCurrentActor->pitch += 800.0f * mathSinF(gBehaviourWorkState->stepCount * 10);
            if (((randomNonNegative() >> 15) % 1000) >= 0x3D5) {
                behaviourPickRandomTargetY();
            }
            actorPitchEaseTowardPoint(gCurrentActor->state, 0, gBehaviourTargetActor->x, gBehaviourWorkState->targetY, gBehaviourTargetActor->z, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x10:
        case 0x23:
            actorEmptyStub();
            actorPitchEaseTowardPoint(gCurrentActor->state, 0, gBehaviourTargetActor->x, ((gCurrentActor->waterY - gCurrentActor->eyeHeight) < gBehaviourTargetActor->y) ? (gCurrentActor->waterY - gCurrentActor->eyeHeight) : gBehaviourTargetActor->y, gBehaviourTargetActor->z, 0x1E, 3.3f, 100.0f, 0x2040);
            if (gActorGlobalState.bossFightPhase == 2) {
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 2:
        case 3:
            gCurrentActor->interactionType = 2;
        case 7:
        case 0x35:
            actorEmptyStub();
            actorPitchEaseTowardPoint(gCurrentActor->state, 0, gBehaviourWorkState->targetX, (gBehaviourWorkState->targetY < (gCurrentActor->waterY - gCurrentActor->eyeHeight)) ? gBehaviourWorkState->targetY : (gCurrentActor->waterY - gCurrentActor->eyeHeight), gBehaviourWorkState->targetZ, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        case 0x37:
            switch (gCurrentActor->unk155) {
                case 0:
                    gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, 0, 7.0f);
                    break;
                case 1:
                    behaviourFadeOutWithinZone(0x14);
                    break;
                case 2:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        default:
            behaviourUpdateContactAndState(0x2E2);
            break;
    }
    switch (gCurrentActor->state) {
        case 0x31:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->state, 1);
            break;
        default:
            enemyAggroStateUpdate(0x6400, 0x2E2, 0x2E2);
            break;
    }
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void behaviourTimedScriptCycleUpdate(void) {
    f32 dx;
    f32 dy;
    f32 dz;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->renderFlags |= 0x24;
        gCurrentActor->flags |= 0x400;
        gBehaviourWorkState->timer = 0x5A;
        gCurrentActor->state = 0;
        gCurrentActor->unk155 = 0;
        actorUpdatePrevContactFlags(gCurrentActor);
        actorClearNodeFlag(gCurrentActor, 1);
    }
    dx = gCurrentActor->x - gBehaviourTargetActor->x;
    dy = gCurrentActor->y - gBehaviourTargetActor->y;
    dz = gCurrentActor->z - gBehaviourTargetActor->z;
    if (dx * dx + dy * dy + dz * dz > 90000.0f) {
        gCurrentActor->flags |= 0x80000000;
    } else {
        gCurrentActor->flags &= 0x7FFFFFFF;
    }
    switch (gCurrentActor->state) {
        case 0:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                actorScriptStart(gCurrentActor, 0x35D);
                scriptSetActorRampTarget(gCurrentActor, 0.5f, 0.0f);
                gCurrentActor->state = 1;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 1:
            if (gCurrentActor->unk155 != 0) {
                gCurrentActor->state = 2;
                gCurrentActor->unk155 = 0;
                gBehaviourWorkState->timer = 0x5A;
            }
            break;
        case 2:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->interactionType = 2;
                scriptSetActorRampTarget(gCurrentActor, 0.5f, 0.0f);
                gCurrentActor->state = 3;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 3:
            if (gCurrentActor->unk155 != 0) {
                gCurrentActor->interactionType = 1;
                gCurrentActor->state = 0;
                gCurrentActor->unk155 = 0;
                gBehaviourWorkState->timer = 0x5A;
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorSwellBurstUpdate(void) {
    f32 dx;
    f32 rangeSq;
    f32 scaleMultiplier;
    u8 st;
    s16 i;

    rangeSq = gCurrentActor->sub4->scaleY * 800.0f;
    scaleMultiplier = 1.1f;
    if (gCurrentMap == 0xC7) {
        if (!(gPrimaryPlayerActor->contactFlags & 4)) {
            rangeSq = 0.0f;
            scaleMultiplier = 0.4f;
        } else {
            rangeSq *= 0.75;
            scaleMultiplier = 0.7f;
        }
    }
    rangeSq *= rangeSq;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->renderFlags |= 4;
        actorUpdatePrevContactFlags(gCurrentActor);
    }
    if (((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0)) && (gCurrentActor->state != 0x27)) {
        gCurrentActor->state = 0x27;
        gCurrentActor->unk155 = 0;
    } else if (gCurrentActor->state != 0x27) {
        dx = gBehaviourTargetActor->x - gCurrentActor->x;
        if (dx * dx + (gBehaviourTargetActor->y - gCurrentActor->y) * (gBehaviourTargetActor->y - gCurrentActor->y) + (gBehaviourTargetActor->z - gCurrentActor->z) * (gBehaviourTargetActor->z - gCurrentActor->z) < rangeSq) {
            gCurrentActor->state = 0x27;
            gCurrentActor->unk155 = 0;
        }
    }
    effectSpawnSparks(0x1F, 0);
    switch (gCurrentActor->state) {
        case 4:
            actorMoveWithinZone(0, 0.0f, 0.0f, 2, 0.0f);
            if (gCurrentActor->y < gCurrentActor->waterY) {
                gCurrentActor->y = gCurrentActor->waterY;
                gCurrentActor->speedY = gCurrentActor->accelY;
            }
        case 0:
            actorTurnTowardActorYaw(0xA, gBehaviourTargetActor);
            break;
        case 0x27:
            switch (gCurrentActor->unk155) {
                case 0:
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1C2, 0xFF, 0x7F, 0);
                    gBehaviourWorkState->scale = 2.0 * gCurrentActor->sub4->scaleY;
                    gCurrentActor->unk155++;
                case 1:
                    if (gBehaviourWorkState->scale > gCurrentActor->sub4->scaleY) {
                        actorSetUniformScale(gCurrentActor, gCurrentActor->sub4->scaleY * 1.01);
                    } else {
                        for (i = 0; i < 0xC; i++) {
                            effectSetDepth(1);
                            effectSetDuration(2);
                            effectSetSpeed(i + 0x0B020000);
                            effectSetCallback(effectRadialSprayUpdate);
                            effectSetFrameDelay(1);
                            effectCreateAtPosition(&D_8072073C, 2.0 * gCurrentActor->sub4->scaleY, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                        }
                        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3D, 0xFF, 0x7F, 0);
                        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x35C, 0xFF, 0x7F, 0, 0x32, 0.3f, 0);
                        tagBarrelSpawnActorSmokePuffs(0, 1);
                        actorGetOrSetNodeScale(gCurrentActor, 1, gCurrentActor->collision->scaledRadius * scaleMultiplier);
                        actorSetCollisionRadius(gCurrentActor, gCurrentActor->collision->scaledRadius * scaleMultiplier);
                        gCurrentActor->flags &= ~4;
                        gCurrentActor->unk155++;
                    }
                    break;
                case 5:
                    gCurrentActor->state = 0x40;
                    break;
                default:
                    gCurrentActor->unk155++;
            }
            break;
        case 2:
        case 3:
            actorPitchEaseTowardPoint(gCurrentActor->state, 0, gBehaviourWorkState->targetX, (gBehaviourWorkState->targetY < (gCurrentActor->waterY - gCurrentActor->eyeHeight)) ? gBehaviourWorkState->targetY : (gCurrentActor->waterY - gCurrentActor->eyeHeight), gBehaviourWorkState->targetZ, 0x1E, 3.3f, 100.0f, 0x2040);
            break;
        default:
            behaviourUpdateContactAndState(0x32E);
            break;
    }
    st = gCurrentActor->state;
    if (st == 2 || st == 3) {
        patrolPathStep(st, 1);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void projectileSpawnFromActorNode(u8 nodeIndex) {
    projectileGetTargetCoords(gCurrentActor, nodeIndex);
    projectileSpawnNodeEntry(0x32, 1, 0.3f, gCurrentActor->moveYaw, 80.0f, 0.0f, gCurrentActor);
}

void projectileAimAtTargetFromActor(void) {
    projectileSetTargetCoords(gCurrentActor->x, gCurrentActor->y - 5.0f, gCurrentActor->z);
    projectileAimAndSpawn(0x51, 1, 0.3f, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, 80.0f, gCurrentActor);
}


void projectileSpawnScriptedInRange(void) {
    switch (gCurrentActor->unk155) {
        case 0:
            if (behaviourIsTargetWithinRadiusAndAngle(0x96, 0x96)) {
                actorScriptStart(gCurrentActor, 0x253);
                gCurrentActor->unk155 = 1;
            }
            break;
        case 2:
            projectileSpawnFromActorNode(2);
            gCurrentActor->unk155 = 3;
            break;
    }
}

void projectileSpawnWithTimer(void) {
    if (gBehaviourWorkState->timer != 0) {
        gBehaviourWorkState->timer--;
        return;
    }
    if (behaviourIsTargetWithinRadiusAndAngle(0x96, 0x96)) {
        projectileSpawnFromActorNode(1);
        gBehaviourWorkState->timer = gFlyPatrolShotInterval;
    }
}

void projectileAimAndSpawnWithTimer(void) {
    if (gBehaviourWorkState->timer != 0) {
        gBehaviourWorkState->timer--;
        if (gFrameCounter & 1) {
            projectileAimAtTargetFromActor();
        }
    } else if (behaviourIsTargetWithinRadiusAndAngle(0x96, 0x96)) {
        gBehaviourWorkState->timer = 0x14;
    }
}

void behaviourCheckZoneReachAndSpawn(void) {
    if (gBehaviourWorkState->timer != 0) {
        gBehaviourWorkState->timer--;
        return;
    }
    if (zoneCanReachPoint(gCurrentActor, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, gBehaviourZone) && behaviourIsTargetWithinRadiusAndAngle(0x96, 0x96)) {
        gCurrentActor->state = 0x26;
        gCurrentActor->unk155 = 0;
    }
}


void behaviourRandomZoneWander(void) {
    if (((randomNonNegative() >> 15) % 1000) >= 0x3E4) {
        gCurrentActor->state = 0x1C;
        gCurrentActor->unk155 = 0;
    }
}

s32 actorFlyTowardPosition(BehaviourWorkState *targetPos, u8 action) {
    f32 dz;
    f32 dx;
    f32 dist;
    f32 t;
    f32 dy;

    dz = targetPos->targetZ - gCurrentActor->z;
    dx = targetPos->targetX - gCurrentActor->x;
    dist = sqrtf(dz * dz + dx * dx);
    t = B7490MAXD(dist / B7490MAXD(gCurrentActor->speedXZ, 0.0001), 0.0001);
    gCurrentActor->speedY = 0.0f;
    dy = (gCurrentActor->y < targetPos->targetY) ? 0.0f : gCurrentActor->y - targetPos->targetY;
    gCurrentActor->accelY = -(dy / t);
    gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, ((mathCalculatePitchAngle(targetPos->targetX, targetPos->targetY, targetPos->targetZ, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x46) * 2048.0) / 3.1415927410125732), 3.3f);
    return actorMoveWithinZone(action, targetPos->targetX, targetPos->targetZ, 0x2E0, 0.0f);
}


void actorSpawnPeriodicBoneEffect(void) {
    u8 pad;
    u8 col;
    f32 f;
    u32 period;

    switch (gCurrentActor->health) {
        case 2:
            col = 0xC8;
            period = 0x20;
            f = 0.5f;
            break;
        case 1:
            period = 0x18;
            col = 0x64;
            f = 1.0f;
            break;
        case 0:
            period = 8;
            col = 0x32;
            f = 1.5f;
            break;
        default:
            period = 0;
    }
    if ((period != 0) && ((gFrameCounter % period) == 0)) {
        effectSetFrameDelay(3);
        effectSetColor(col, col, col, gCurrentActor->alpha);
        effectSpawnBoneDefault(gCurrentActor, 1, f, 0.0f, 0.0f, 0.0f, -0x50);
    }
}

// Second component (Actor 0x178) of the fly-patrol actor types (behaviourFlyPatrolWithCallback,
// actorAirPatrolStep and its caller behaviourEnemyBatUpdate).
typedef struct FlyPatrolComponent {
    /* 0x00 */ s16 hoverHeight; // above the spawn node's y; seeded from SpawnNode unkA
} FlyPatrolComponent;

void behaviourFlyPatrolWithCallback(void (*callback)(void), u16 animId1, u16 animId2, s16 sfxId) {
    FlyPatrolComponent *patrol;
    s16 targetX;
    s16 targetZ;

    patrol = B7490A->typeState;
    if (sfxId != 0 && gCurrentActor->state != 0x37 && gCurrentActor->soundSlots[0] == -1) {
        sfxPlayActorSound(gCurrentActor, sfxId, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    if (!(gCurrentActor->flags & 0x10)) {
        patrol->hoverHeight = gBehaviourExtraState->unkA;
        if (gBehaviourExtraState->unkB == 0) {
            gBehaviourExtraState->unkB = 0x28;
        }
    }
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, animId1);
        gCurrentActor->speedY = 300.0f;
        patrol->hoverHeight = 0;
        gBehaviourWorkState->timer = 0x2BC;
    }
    targetX = gBehaviourWorkState->targetX;
    targetZ = gBehaviourWorkState->targetZ;
    switch (gCurrentActor->state) {
        case 1:
        case 0x10:
        case 0x23:
            targetX = gBehaviourTargetActor->x;
            targetZ = gBehaviourTargetActor->z;
            /* fallthrough */
        case 2:
        case 3:
        case 7:
        case 0x35:
            if (gCurrentActor->y < gBehaviourExtraState->y + patrol->hoverHeight) {
                gCurrentActor->y += gBehaviourExtraState->unkB * 0.03125;
            } else if (camIsCutsceneActive() == 0 && callback != NULL) {
                callback();
            }
            actorMoveWithinZone(gCurrentActor->state, targetX, targetZ, 0x2C1, 0.0f);
            gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, 0, 5.0f);
            break;
        case 0x26:
            switch (gCurrentActor->unk155) {
                case 0:
                    gBehaviourWorkState->targetX = gBehaviourTargetActor->x;
                    gBehaviourWorkState->targetY = gBehaviourTargetActor->y;
                    gBehaviourWorkState->targetZ = gBehaviourTargetActor->z;
                    gCurrentActor->unk155++;
                    gBehaviourWorkState->timer = 0x64;
                    /* fallthrough */
                case 1:
                    if ((actorFlyTowardPosition(gBehaviourWorkState, 0x23) & 1) || gCurrentActor->y < gBehaviourWorkState->targetY + 0xF) {
                        gCurrentActor->state = gBehaviourExtraState->actorState;
                        gCurrentActor->unk155 = 0;
                    }
                    break;
            }
            break;
        case 0x37:
            gCurrentActor->yaw += gBehaviourWorkState->timer;
            gBehaviourWorkState->timer = ((gBehaviourWorkState->timer - 0x11) < 0) ? 0 : (gBehaviourWorkState->timer - 0x11);
            if (gBehaviourWorkState->timer == 0) {
                sfxStopSlotSound(gCurrentActor, 0);
            }
            switch (gCurrentActor->unk155) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(gCurrentActor);
                    if (gCurrentActor->actorType == 0x11D) {
                        gCurrentActor->unk155 = 3;
                        break;
                    }
                    gCurrentActor->speedY = 50.0f;
                    gCurrentActor->unk155++;
                    /* fallthrough */
                case 2:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x222, 0.0f);
                    break;
                case 3:
                    behaviourFadeOutWithinZone(0xA);
                    break;
                case 4:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        case 0x40:
            break;
        default:
            behaviourUpdateContactAndState(animId2);
            break;
    }
    switch (gCurrentActor->state) {
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->state, 1);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void behaviourFlyPatrolState(void) {
    behaviourFrameBegin();
    behaviourFlyPatrolWithCallback(behaviourCheckZoneReachAndSpawn, 0x251, 0x250, 0x10E);
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
}

void behaviourFlyPatrolState2(void) {
    behaviourFrameBegin();
    behaviourFlyPatrolWithCallback(projectileSpawnWithTimer, 0x251, 0x250, 0x10E);
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
}

void behaviourFlyPatrolState3(void) {
    behaviourFrameBegin();
    behaviourFlyPatrolWithCallback(projectileSpawnScriptedInRange, 0x254, 0x252, 0x108);
    actorSpawnPeriodicBoneEffect();
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
}

void behaviourFlyPatrolState4(void) {
    behaviourFrameBegin();
    behaviourFlyPatrolWithCallback(behaviourCheckZoneReachAndSpawn, 0x251, 0x250, 0x10E);
    if (gCurrentActor->state != 0x37) {
        projectileAimAndSpawnWithTimer();
    }
}

extern f32 gAirPatrolAccelY;

void actorAirPatrolStep(u8 action, s16 animId1, s16 animId2) {
    FlyPatrolComponent *patrol;
    s32 pad1;
    s32 pad2;
    s16 targetHeight;

    patrol = B7490A->typeState;
    if (!(gCurrentActor->flags & 0x10)) {
        func_80724CA4(1, 1);
        gBehaviourWorkState->scale = gCurrentActor->sub4->scaleY;
        gCurrentActor->speedXZ = gBehaviourExtraState->targetSpeed;
        patrol->hoverHeight = gBehaviourExtraState->unkA;
        gCurrentActor->accelY = gAirPatrolAccelY;
    }
    targetHeight = gBehaviourExtraState->y + patrol->hoverHeight;
    if (((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0)) && (action != 0x37)) {
        gCurrentActor->state = 0x37;
        gCurrentActor->unk155 = 0;
    }
    switch (action) {
        case 2:
        case 3:
            if (gCurrentActor->unk155 == 0) {
                actorScriptStart(gCurrentActor, animId1);
                gCurrentActor->unk155++;
            }
            actorMoveWithinZone(action, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0xE1, 0.0f);
            if (gCurrentActor->y < targetHeight) {
                if (gCurrentActor->unk155 == 2) {
                    gCurrentActor->y += (f32) gBehaviourExtraState->unkB * 0.03125;
                } else {
                    gCurrentActor->y += (f32) gBehaviourExtraState->unkB * 0.015625;
                }
            }
            gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, 0, 5.0f);
            break;
        case 0x26:
            switch (gCurrentActor->unk155) {
                case 0:
                case 1:
                case 2:
                    actorScriptStart(gCurrentActor, animId2);
                    gCurrentActor->unk155 = 3;
                case 3:
                    actorFlyTowardPosition(gBehaviourWorkState, 0x26);
                    break;
            }
            break;
        case 0x37:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x22, 0.0f);
            if (gCurrentActor->contactFlags & 1) {
                gCurrentActor->state = 0x40;
            }
            break;
        case 0x40:
            break;
        default:
            behaviourUpdateContactAndState(animId1);
            break;
    }
    switch (action) {
        case 2:
        case 3:
            patrolPathStep(action, 1);
            break;
        case 0x26:
            if (patrolPathStep(action, 1) != 0) {
                gCurrentActor->state = gBehaviourExtraState->actorState;
                gCurrentActor->unk155 = 0;
            }
            break;
    }
}

void behaviourEnemyBatUpdate(void) {
    f64 pad;
    FlyPatrolComponent *patrol;
    s32 deltaHeight;

    patrol = B7490A->typeState;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x400;
        gBehaviourAnimState->flags |= 0x40;
        gCurrentActor->tintR = 0xFA;
        gCurrentActor->tintG = 0xFA;
        gCurrentActor->tintB = 0xFA;
        actorSpawnNodeEntryAtActor(0x2D, 0x44);
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x2C1, 0xFF, 0x7F, 0, 0x14, 0.0f, 0);
    }
    deltaHeight = gBehaviourWorkState->targetY - gBehaviourExtraState->y;
    patrol->hoverHeight = (deltaHeight < 0) ? 0 : deltaHeight;
    if ((gActorGlobalState.bossFightPhase == 9) && (gCurrentActor->state != 0x37)) {
        gCurrentActor->state = 0x37;
        gCurrentActor->unk155 = 0;
        actorScriptStart(gCurrentActor, 0x248);
        actorAttachChildCallbacks();
        sfxAllocateChannel(0x14, 1.0f);
        csModelStateSetFirstByte(0x7F, 0xA);
    }
    if ((gCurrentActor->state != 0x37) && (gCurrentActor->state != 0x40)) {
        actorPlaceAttachedChildren(-0x1E);
    }
    actorSetUniformScale(gCurrentActor, (gBehaviourWorkState->scale - gCurrentActor->sub4->scaleX) * 0.05 + gCurrentActor->sub4->scaleX);
    if (gBehaviourWorkState->timer != 0) {
        gBehaviourWorkState->timer--;
        if (gFrameCounter & 4) {
            gCurrentActor->flags |= 0x800000;
        } else {
            gCurrentActor->flags &= 0xFF7FFFFF;
        }
    } else {
        gCurrentActor->interactionType = 1;
        gCurrentActor->flags &= 0xFF7FFFFF;
        if (gActorGlobalState.bossFightPhase == 4) {
            gCurrentActor->interactionType = 2;
            gBehaviourWorkState->timer = 0x1E;
            gBehaviourWorkState->scale *= 0.7;
            behaviourSpawnPuffParticle();
            camStartPath(gCurrentActor, 3, 5);
            if (gCurrentActor->health & 1) {
                actorScriptStart(gCurrentActor, 0x24A);
            } else {
                actorScriptStart(gCurrentActor, 0x249);
            }
        }
    }
    actorAirPatrolStep(gCurrentActor->state, 0x247, 0x246);
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void behaviourEnemyFlyStep(void) {
    behaviourFrameBegin();
    actorAirPatrolStep(gCurrentActor->state, 0x23D, 0x23E);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void behaviourEnemyFlyIdle(void) {
    s32 inWaterFlag;
    s16 alphaDelta;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0x30C, 0x30B, 0x30D);
        gCurrentActor->flags &= 0xFFFF7FFF;
    }
    if (gCurrentMap == 0xA6) {
        inWaterFlag = gActivePlayerState->stateFlags & 0x40;
        if ((inWaterFlag != 0) && (gCurrentActor->alpha == 0)) {
            gBehaviourWorkState->timer = 0xA;
            gCurrentActor->unk144 = 0x24;
        } else if ((inWaterFlag == 0) && (gCurrentActor->alpha == 0xFF)) {
            gBehaviourWorkState->timer = -0xA;
            gCurrentActor->unk144 = 1;
        }
        alphaDelta = gBehaviourWorkState->timer;
        if (alphaDelta != 0) {
            gCurrentActor->alpha += alphaDelta;
            if (gCurrentActor->alpha >= 0x100) {
                gCurrentActor->alpha = 0xFF;
                gBehaviourWorkState->timer = 0;
            } else if (gCurrentActor->alpha < 0) {
                gCurrentActor->alpha = 0;
                gBehaviourWorkState->timer = 0;
            }
        }
    }
    behaviourFlyPatrolWithCallback((gFrameCounter & 1) ? behaviourCheckZoneReachAndSpawn : behaviourRandomZoneWander, 0x30E, 0x30B, 0);
}

void behaviourEnemyFlySwoop(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x60;
        gBehaviourAnimState->flags &= 0xFFF7;
        gCurrentActor->speedXZ = ((randomNonNegative() >> 15) % 100) + 0x12C;
        gCurrentActor->y += (randomNonNegative() >> 15) % 30;
        gCurrentActor->flags &= 0xFFFF7FFF;
        gCurrentActor->alpha = 0;
        gCurrentActor->unkEC = ((randomNonNegative() >> 15) % 7) + 0xF;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocityCustom(gCurrentActor, gCurrentActor->speedXZ, 0.0f);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    switch (gCurrentActor->state) {
    case 6:
        gCurrentActor->alpha += gCurrentActor->unkEC;
        if (gCurrentActor->alpha >= 0xFF) {
            gCurrentActor->alpha = 0xFF;
            gCurrentActor->state = 0x37;
        }
        break;
    case 0x37:
        gCurrentActor->alpha -= gCurrentActor->unkEC;
        if (gCurrentActor->alpha < 0) {
            gCurrentActor->state = 0x3C;
            gCurrentActor->alpha = 0;
        }
        break;
    default:
        behaviourUpdateContactAndState(0x333);
        break;
    }
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

// Second component (Actor 0x178) of the behaviourEnemyFlyReturn actor type: the point it flies toward,
// re-picked around zone entry 1 or taken from the player while it chases.
typedef struct FlyWanderState {
    /* 0x00 */ f32 targetX;
    /* 0x04 */ f32 targetY;
    /* 0x08 */ f32 targetZ;
    /* 0x0C */ f32 homeY;
    /* 0x10 */ s16 retargetTimer;
    /* 0x12 */ s16 chaseTimer;
} FlyWanderState;

extern u16 gEnemyDefeatCount;

void behaviourEnemyFlyReturn(void) {
    f32 pad;
    f32 zoneX;
    f32 zoneY;
    f32 zoneZ;
    f32 dist;
    s16 angle;
    FlyWanderState *state;

    state = B7490A->typeState;
    behaviourFrameBegin();
    if ((gCurrentActor->state != 0x40) && (gCurrentActor->state != 0x37) && ((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0))) {
        sfxStopSlotSound(gCurrentActor, 0);
        actorScriptStart(gCurrentActor, 0x331);
        gCurrentActor->state = 0x37;
        gCurrentActor->unk155 = 0;
        sfxPlayFromActorWithAltitudeCheck(gPrimaryPlayerActor, 0x16, 0xFF, 0x7F, 0x1E);
    }
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x20;
        gBehaviourAnimState->flags &= 0xFFF7;
        gCurrentActor->speedXZ = 40.0f;
        gCurrentActor->state = 0x23;
        gCurrentActor->unk155 = 0;
        gCurrentActor->unkEC = ((randomNonNegative() >> 15) % 7) + 0xF;
        state->targetX = gCurrentActor->x;
        state->targetY = gCurrentActor->y;
        state->targetZ = gCurrentActor->z;
        state->retargetTimer = 1;
        state->homeY = gCurrentActor->y;
        state->chaseTimer = (randomLcgNext() & 0xFF) + 0x78;
    }
    if ((gCurrentActor->state != 0x37) && (gCurrentActor->soundSlots[0] == -1)) {
        sfxPlayActorSound(gCurrentActor, 0x10E, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    switch (gCurrentActor->state) {
        case 0x26:
            state->targetX = gPrimaryPlayerActor->x;
            state->targetY = gPrimaryPlayerActor->y;
            state->targetZ = gPrimaryPlayerActor->z;
            state->chaseTimer = (randomLcgNext() & 0xFF) + 0x78;
        case 0x23:
            gCurrentActor->yaw -= mathAngleSignedDistance(mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, state->targetX, state->targetZ) + 0x800, gCurrentActor->yaw) >> 4;
            state->retargetTimer--;
            if (state->retargetTimer <= 0) {
                zoneEntryGetPosition(1, 0, &zoneX, &zoneY, &zoneZ);
                state->retargetTimer = (randomLcgNext() & 0x3F) + 0xF;
                angle = mathAngleBetweenPoints2D(zoneX, zoneZ, state->targetX, state->targetZ);
                angle += ((randomLcgNext() & 7) << 8) + 0x400;
                dist = randomFloat() * 180.0;
                state->targetX = (mathSinF(angle) * dist) + zoneX;
                state->targetY = state->homeY;
                state->targetZ = (mathCosF(angle) * dist) + zoneZ;
                gCurrentActor->state = 0x23;
            }
            if (gCurrentActor->state == 0x23) {
                state->chaseTimer--;
                if (state->chaseTimer <= 0) {
                    state->retargetTimer = 0x3C;
                    gCurrentActor->state = 0x26;
                }
            }
            zoneY = (state->targetY - gCurrentActor->y) * 0.0625; // ORIG: zoneY's home (sp+100, a3 into zoneEntryGetPosition at 0x2fb0) also holds the clamped climb step (swc1 at 0x311c/0x313c/0x3164, lwc1 at 0x31a0)
            if (zoneY > 8.0) {
                zoneY = 8.0f;
            }
            if (zoneY < -8.0) {
                zoneY = -8.0f;
            }
            gCurrentActor->x += mathSinF(gCurrentActor->yaw) * 8.0;
            gCurrentActor->y += zoneY;
            gCurrentActor->z += mathCosF(gCurrentActor->yaw) * 8.0;
            break;
        case 0x37:
            gCurrentActor->flags &= 0xFFFF7FFF;
            gCurrentActor->alpha -= 8;
            gCurrentActor->y -= 10.0;
            if (gCurrentActor->alpha < 0) {
                gCurrentActor->alpha = 0;
                gCurrentActor->state = 0x40;
                gCurrentActor->unk155 = 0;
                gCurrentActor->unk144 = 1;
                if (gCurrentMap == 0xA7) {
                    gEnemyDefeatCount++;
                    if ((gEnemyDefeatCount == 5) && (flagGet(0x15F, 0) == 0)) {
                        csModelStateSetFirstByte(4, 0xA);
                    }
                }
            }
            break;
        default:
            behaviourUpdateContactAndState(0x32F);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
