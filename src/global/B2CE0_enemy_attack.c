#include "common.h"
#include "actor.h"
#include "proto/global/103AB0_view_effects.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/11BC10_effect_update.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/12E800_behaviour.h"
#include "proto/global/166A0_random.h"
#include "proto/global/17800_matrix_rotation.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/42630_cutscene_interp.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/61AA0_render_caches.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/6AD90_collision.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/89250_effect_spawn.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/AA960_pickup_drops.h"
#include "proto/global/B1F60_enemy_patrol.h"
#include "proto/global/B2CE0_enemy_attack.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/EFDC0_player_state_enter.h"

// Second component (Actor+0x178) of the actor kind run by behaviourProjectileEnemyUpdate (set once at init).
typedef struct PatrolState {
    /* 0x00 */ s16 nearDistSq; // enemyAggroStateUpdate (12E800) leaves state 0x34 for 0x24 once the squared target distance is below it
    /* 0x02 */ u8 unk2;
} PatrolState;

typedef struct PatrolActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ PatrolState *patrol;
} PatrolActor;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;

extern u8 gEffectSpriteBlast[];

void behaviourTumbleDebrisUpdate(void) {
    f32 transMtx[4][4];
    f32 rotMtx[4][4];

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->speedXZ = (randomNonNegative() >> 15) % 50 + 0x46;
        gCurrentActor->speedY = gCurrentActor->speedXZ * 2;
        gCurrentActor->accelY = -30.0f;
        gCurrentActor->terminalSpeedY = -220.0f;
        gCurrentActor->yawSpeed = (randomNonNegative() >> 15) % 400 + 200;
    }
    gCurrentActor->yaw += gCurrentActor->yawSpeed;
    if (gCurrentActor->yawSpeed > 0) {
        gCurrentActor->yawSpeed -= 10;
    }
    collisionSetQueryMode(1);
    actorApplyGravity();
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 10, 10, 1, 200, 0x80, 0, 1.0f);
    if (gCurrentActor->debrisUpright != 0) {
        actorUpdateModelMatrix(gCurrentActor, 0);
    } else {
        guTranslateF(transMtx, 0, -30.0f, 0);
        matrixMakeRotationX(rotMtx, 180.0f);
        guMtxCatF(transMtx, rotMtx, transMtx);
        guTranslateF(rotMtx, 0, 30.0f, 0);
        guMtxCatF(transMtx, rotMtx, gCurrentActor->modelMtx);
        actorUpdateModelMatrix(gCurrentActor, 1);
    }
    if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x56, 0xB4, 0x96, 1, 0x4B, 0.3f, 0);
        gCurrentActor->speedXZ = gCurrentActor->speedXZ * 0.6;
        gCurrentActor->speedY = gCurrentActor->speedXZ * 3.0f;
        return;
    }
    if ((gCurrentActor->contactFlags & 1) && (gCurrentActor->prevContactFlags & 1)) {
        effectCreateAtPosition(gEffectSpriteBlast, 1.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        actorDespawn(gCurrentActor);
    }
}

void actorSpawnChildAtNode(s32 actorType, s16 angleOffset, s16 nodeIndex, s16 yawSpeed) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    if (actorSpawn(0xED, actorType) != 0) {
        actorGetNodePos(gCurrentActor, nodeIndex, &nodeX, &nodeY, &nodeZ);
        gSpawnedActor->floorY = gCurrentActor->floorY;
        gSpawnedActor->yaw = gCurrentActor->yaw + angleOffset;
        gSpawnedActor->moveYaw = gSpawnedActor->yaw;
        gSpawnedActor->yawSpeed = yawSpeed;
        gSpawnedActor->x = nodeX;
        gSpawnedActor->y = nodeY;
        gSpawnedActor->z = nodeZ;
        actorSetUniformScale(gSpawnedActor, gCurrentActor->sub4->scaleY);
    }
}


void behaviourSearchlightScan(f32 distOffset, f32 radius) {
    f32 node1X;
    f32 node1Y;
    f32 node1Z;
    f32 node2X;
    f32 node2Y;
    f32 node2Z;
    s16 angle;

    actorGetNodePos(gCurrentActor, 1, &node1X, &node1Y, &node1Z);
    actorGetNodePos(gCurrentActor, 2, &node2X, &node2Y, &node2Z);
    angle = mathAngleBetweenPoints2D(node2X, node2Z, node1X, node1Z);
    lensFlareAddSource(node1X, node1Y, node1Z, node2X, node2Y, node2Z, 0.6f, 0xFF, 0xFF, 0xFF);
    node1X = mathSinF(angle) * distOffset + gCurrentActor->x; // ORIG: target stores the light X/Z into node1X/node1Z's homes (swc1 $f4,0x64(sp) at 0x48c, swc1 $f16,0x5c(sp) at 0x4c0; &node1X/&node1Z = sp+0x64/0x5c at 0x3dc/0x3c8); separate locals grow the frame 0x68 -> 0x70
    node1Z = mathCosF(angle) * distOffset + gCurrentActor->z;
    lightAdd(node1X, gCurrentActor->y, node1Z, 0.0f, 0.0f, 0.0f, radius, 0, 0xFF, 0xFF, 0xFF);
    if (gCurrentActor->state != 0) {
        if (SQ(gBehaviourTargetActor->x - node1X) + SQ(gBehaviourTargetActor->y - gCurrentActor->y) + SQ(gBehaviourTargetActor->z - node1Z) < SQ(radius)) {
            gCurrentActor->yaw = mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->z);
            playerStateQueueCallback(0x43, gCurrentActor, 0);
            gCurrentActor->state = 0;
            gCurrentActor->subState = 0;
        }
    }
}

extern s32 gCurrentMap;

void behaviourMeleePatrolEnemyUpdate(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0x1FD, 0x1FB, 0x1FC);
        actorAllocBoneRotations(3, 1);
        actorClearNodeFlag(gCurrentActor, 3);
        if (gCurrentMap == 0xA5) {
            gCurrentActor->interactionType = 1;
        }
    }
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
    if ((gCurrentActor->state != 0x32) || (gActorGlobalState.damaged != 0)) {
        if (((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.damaged != 0)) && (gCurrentActor->state != 0x37)) {
            if (gCurrentActor->health < -1) {
                behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x202);
                gCurrentActor->speedY = 250.0f;
            } else {
                behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x201);
                gCurrentActor->speedY = 200.0f;
            }
            gBehaviourWorkState->acceleration = 2;
            gCurrentActor->callbackMask &= ~0x8000;
        } else if (gActorGlobalState.bossFightPhase == 4) {
            behaviourSpawnExplosionAndSound(0x1FF, 0x31, gActorGlobalState.targetActor);
        } else if (gActorGlobalState.bossFightPhase == 5) {
            behaviourSpawnExplosionAndSound(0x200, 0x32, gActorGlobalState.targetActor);
            gCurrentActor->speedY = 220.0f;
        }
    }
    switch (gCurrentActor->state) {
    case 0x31:
        if ((gCurrentActor->subState != 0) || (gCurrentActor->sub4->model->speed == 0.0f)) {
            actorSetDefaultState(0x1FB);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x32:
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gCurrentActor->moveYaw, 7.0f);
        switch (gCurrentActor->subState) {
        case 0:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
            break;
        case 1:
            gCurrentActor->speedY = 200.0f;
            gCurrentActor->speedXZ = 120.0f;
            gCurrentActor->subState++;
            /* fallthrough */
        case 2:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 3:
            actorSetDefaultState(0x1FB);
            break;
        }
        break;
    case 0x11:
        actorTrackBoneTowardTarget(5);
        switch (gCurrentActor->subState) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x1FD);
            gCurrentActor->subState++;
            /* fallthrough */
        case 1:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            if (gCurrentActor->speedXZ < 1.0f) {
                gCurrentActor->subState++;
            }
            break;
        case 2:
            behaviourUpdateShadowAlpha();
            if ((randomNonNegative() >> 15) % 1000 >= 996) {
                actorSetDefaultState(0x1FB);
            }
            break;
        }
        break;
    case 0x27:
        actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
        switch (gCurrentActor->subState) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x1FE);
            gCurrentActor->subState = 1;
            break;
        case 2:
            gCurrentActor->interactionType = 2;
            break;
        case 3:
            gCurrentActor->interactionType = 1;
            break;
        case 4:
            actorSetDefaultState(0x1FB);
            break;
        }
        break;
    case 1:
        if (behaviourCheckRandomAnimTrigger() != 0) {
            gCurrentActor->state = 0x11;
            gCurrentActor->subState = 0;
        }
        /* fallthrough */
    case 0x23:
        if ((gActorGlobalState.bossFightPhase == 2) && (behaviourIsTargetWithinAngle(0x2710) != 0)) {
            gCurrentActor->state = 0x27;
            gCurrentActor->subState = 0;
        }
        /* fallthrough */
    case 0x10:
        actorTrackBoneTowardTarget((gCurrentActor->state == 1) ? 2 : 0);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        actorTrackBoneTowardTarget((gCurrentActor->state == 0x35) ? 2 : 3);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
        break;
    case 0x37:
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gCurrentActor->moveYaw, 7.0f);
        switch (gCurrentActor->subState) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            if ((gCurrentMap == 0xA5) && (gCurrentActor->bonusPicked != 0)) {
                csModelStateSetFirstByte(0, 0xA);
            }
            sfxSpawnTableNodes(gCurrentActor);
            gCurrentActor->subState++;
            /* fallthrough */
        case 2:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            behaviourFadeOutWithinZone(8);
            break;
        case 3:
            gCurrentActor->state = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        behaviourUpdateContactAndState(0x1FB);
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
        /* fallthrough */
    default:
        enemyAggroStateUpdate(0x6400, 0x1FB, 0x1FC);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void behaviourTryStartShot(void) {
    if ((randomNonNegative() >> 15) % 1000 >= 981 && behaviourIsTargetWithinAngle(0xFA0) != 0 && !(gBehaviourWorkState->flags & 0x80)) {
        gCurrentActor->state = 0x25;
        gCurrentActor->subState = 0;
    }
}

void behaviourProjectileEnemyUpdate(void) {
    PatrolState *patrolState;
    f32 scaleFactor;

    patrolState = ((PatrolActor *)gCurrentActor)->patrol;
    scaleFactor = gCurrentActor->sub4->scaleY / 0.15;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        patrolState->nearDistSq = 0x2710;
        patrolState->unk2 = 0x20;
        behaviourSetAnimIds(0x2AD, 0x2AB, 0x2AC);
        actorAllocBoneRotations(2, 1);
    }
    if (gCurrentActor->state != 0x32 || gActorGlobalState.damaged != 0) {
        if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.damaged != 0) && gCurrentActor->state != 0x37) {
            behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x2AE);
            gBehaviourWorkState->timer = 0x1C2;
        } else if (gActorGlobalState.bossFightPhase == 4) {
            behaviourSpawnExplosionAndSound(0x2B2, 0x31, gActorGlobalState.targetActor);
            gCurrentActor->speedXZ = 0.0f;
        } else if (gActorGlobalState.bossFightPhase == 5) {
            behaviourSpawnExplosionAndSound(0x2B1, 0x31, gActorGlobalState.targetActor);
            gCurrentActor->speedXZ = 0.0f;
        }
    }
    switch (gCurrentActor->state) {
        case 0x31:
            if (gCurrentActor->subState != 0 || gCurrentActor->sub4->model->speed == 0.0f) {
                actorSetDefaultState(0x2AB);
            }
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
            break;
        case 0x11:
            actorTrackBoneTowardTarget(5);
            switch (gCurrentActor->subState) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, 0x2B0);
                    gCurrentActor->subState = 1;
                    /* fallthrough */
                case 1:
                    actorMoveWithinZone(0x11, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
                    if (gCurrentActor->speedXZ < 1.0f) {
                        gCurrentActor->subState++;
                    }
                    break;
                case 2:
                    behaviourTryStartShot();
                    behaviourUpdateShadowAlpha();
                    if ((randomNonNegative() >> 15) % 1000 >= 991 && gCurrentActor->sub4->model->animId != 0x4C4) {
                        actorSetDefaultState(0x2AB);
                    }
            }
            break;
        case 0x27:
            switch (gCurrentActor->subState) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    gCurrentActor->speedXZ = 0.0f;
                    actorScriptStart(gCurrentActor, 0x2B4);
                    gCurrentActor->subState = 1;
                    break;
                case 2:
                    gCurrentActor->interactionType = 2;
                    break;
                case 3:
                    gCurrentActor->interactionType = 1;
                    break;
                case 4:
                    actorSetDefaultState(0x2AB);
                    break;
            }
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            break;
        case 0x25:
            actorTrackBoneTowardTarget(0);
            switch (gCurrentActor->subState) {
                case 0:
                    actorScriptStart(gCurrentActor, 0x2B3);
                    gCurrentActor->subState = 1;
                    break;
                case 2:
                    projectileGetTargetCoords(gCurrentActor, 2);
                    projectileSpawnNodeEntry(0x32, 0x63, scaleFactor * 0.4, gCurrentActor->yaw, 300.0f, 280.0f, gCurrentActor);
                    gCurrentActor->subState = 3;
                    break;
                case 4:
                    actorSetDefaultState(0x2AB);
                    break;
            }
            break;
        case 1:
            if (behaviourCheckRandomAnimTrigger() != 0) {
                gCurrentActor->state = 0x11;
                gCurrentActor->subState = 0;
            }
            /* fallthrough */
        case 0x23:
            if (gActorGlobalState.bossFightPhase == 2 && behaviourIsTargetWithinAngle(0x1388) != 0) {
                gCurrentActor->state = 0x27;
                gCurrentActor->subState = 0;
            }
            /* fallthrough */
        case 0x10:
            behaviourTryStartShot();
            actorTrackBoneTowardTarget(gCurrentActor->state == 1 ? 2 : 0);
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            actorTrackBoneTowardTarget(gCurrentActor->state == 0x35 ? 2 : 3);
            actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
            break;
        case 0x37:
            switch (gCurrentActor->subState) {
                case 0:
                    gCurrentActor->yaw += gBehaviourWorkState->timer;
                    gBehaviourWorkState->timer = gBehaviourWorkState->timer * 0.95;
                    break;
                case 1:
                    sfxSpawnTableNodes(gCurrentActor);
                    gCurrentActor->subState++;
                    /* fallthrough */
                case 2:
                    behaviourFadeOutWithinZone(5);
                    break;
                case 3:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        case 0x40:
            break;
        default:
            behaviourUpdateContactAndState(0x2AB);
            break;
    }
    switch (gCurrentActor->state) {
        case 0x24:
        case 0x25:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->state, 1);
            /* fallthrough */
        default:
            enemyAggroStateUpdate(0x6400, 0x2AB, 0x2AC);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void behaviourSearchlightGuardUpdate(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0x2C0, 0x2C1, 0x2C1);
        actorAllocBoneRotations(0xE, 1);
        gBehaviourWorkState->flags |= 0x800;
        gCurrentActor->flags |= 0x400;
    }
    behaviourSearchlightScan(40.0f, 70.0f);
    if (gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.damaged != 0) {
        gCurrentActor->state = 0x3A;
        gCurrentActor->subState = 0;
    }
    switch (gCurrentActor->state) {
        case 0x11:
            actorTrackBoneTowardTarget(2);
            switch (gCurrentActor->subState) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, 0x2C0);
                    gCurrentActor->subState++;
                    /* fallthrough */
                case 1:
                    actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
                    if (gCurrentActor->speedXZ < 1.0f) {
                        gCurrentActor->subState++;
                    }
                    break;
                case 2:
                    behaviourUpdateShadowAlpha();
                    if ((randomNonNegative() >> 15) % 1000 >= 996) {
                        actorSetDefaultState(0x1FB);
                    }
                    break;
            }
            break;
        case 1:
            if (behaviourCheckRandomAnimTrigger() != 0) {
                gCurrentActor->state = 0x11;
                gCurrentActor->subState = 0;
            }
            actorTrackBoneTowardTarget(gCurrentActor->state == 1 ? 2 : 0);
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            actorTrackBoneTowardTarget(gCurrentActor->state == 0x35 ? 2 : 3);
            actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
            break;
        case 0x37:
            gCurrentActor->state = 0x40;
            break;
        default:
            behaviourUpdateContactAndState(0x2C0);
            break;
    }
    switch (gCurrentActor->state) {
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->state, 1);
            break;
        case 0x31:
        case 0x37:
        case 0x40:
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern EffectGridAsset gEffectSpriteShardGold;

void effectSpawnActorParticleBurst(u8 nodeIndex) {
    s16 i;
    f32 scaleFactor;

    for (i = 0; i < 7; i++) {
        scaleFactor = gCurrentActor->sub4->scaleY / 0.15;
        effectSetDepth(1);
        effectSetDuration(10);
        effectSetCallback(effectTumbleBounceUpdate);
        effectSetFrameDelay(2);
        effectSetSpeed(0);
        effectCreateAtActorBone(&gEffectSpriteShardGold, scaleFactor * 0.15, gCurrentActor, nodeIndex, 0);
    }
}

void behaviourArmoredEnemyUpdate(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->segmentFlags = -1;
        behaviourSetAnimIds(0x2D9, 0x2D7, 0x2D8);
        actorAllocBoneRotations(2, 1);
        gCurrentActor->attackArc = 0x1770;
    }
    if (((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.damaged != 0)) && (gCurrentActor->state != 0x37)) {
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x2DD);
        gBehaviourWorkState->acceleration = 2;
        gCurrentActor->callbackMask &= ~0x8000;
    } else if ((gActorGlobalState.bossFightPhase == 4) || (gActorGlobalState.bossFightPhase == 5)) {
        if (gCurrentActor->segmentFlags & 1) {
            gBehaviourWorkState->turnRate = 0xF;
            gBehaviourWorkState->moveYawRate = 0xF;
            gCurrentActor->attackArc = -1;
            actorSpawnChildAtNode(0xC2, 0x800, 1, 0x190);
            gSpawnedActor->debrisUpright = 1;
            effectSpawnActorParticleBurst(1);
        } else if (gCurrentActor->segmentFlags & 2) {
            effectSpawnActorParticleBurst(2);
        }
        gCurrentActor->segmentFlags *= 2;
        behaviourSpawnExplosionAndSound(0x2DC, 0x31, gActorGlobalState.targetActor);
        gBehaviourWorkState->targetSpeed = 0;
        gCurrentActor->speedXZ = 0.0f;
    }
    switch (gCurrentActor->state) {
    case 0x31:
        if ((gCurrentActor->subState != 0) || (gCurrentActor->sub4->model->speed == 0.0f)) {
            actorSetDefaultState(0x2D7);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
        break;
    case 0x11:
        actorTrackBoneTowardTarget(5);
        switch (gCurrentActor->subState) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x2D9);
            gCurrentActor->subState++;
            /* fallthrough */
        case 1:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            if (gCurrentActor->speedXZ < 1.0f) {
                gCurrentActor->subState++;
            }
            break;
        case 2:
            behaviourUpdateShadowAlpha();
            if ((randomNonNegative() >> 15) % 1000 >= 996) {
                actorSetDefaultState(0x2D7);
            }
            break;
        }
        break;
    case 0x27:
        if (gCurrentActor->attackArc < 0xFFFF) {
            actorTurnTowardActorYaw(0xA, gBehaviourTargetActor);
        }
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
        switch (gCurrentActor->subState) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            if ((gCurrentActor->sub4->scaleY > 0.18) && ((randomNonNegative() >> 15) % 1000 >= 501)) {
                actorScriptStart(gCurrentActor, 0x2DB);
            } else {
                actorScriptStart(gCurrentActor, 0x2DA);
            }
            gCurrentActor->subState = 1;
            break;
        case 2:
            gCurrentActor->interactionType = 2;
            break;
        case 3:
            gCurrentActor->interactionType = 1;
            break;
        case 4:
            actorSetDefaultState(0x2D7);
            break;
        }
        break;
    case 1:
        if (behaviourCheckRandomAnimTrigger() != 0) {
            gCurrentActor->state = 0x11;
            gCurrentActor->subState = 0;
        }
        /* fallthrough */
    case 0x23:
        if ((gActorGlobalState.bossFightPhase == 2) && (behaviourIsTargetWithinAngle(gCurrentActor->attackArc) != 0)) {
            gCurrentActor->state = 0x27;
            gCurrentActor->subState = 0;
        }
        /* fallthrough */
    case 0x10:
        actorTrackBoneTowardTarget((gCurrentActor->state == 1) ? 2 : 0);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        actorTrackBoneTowardTarget((gCurrentActor->state == 0x35) ? 2 : 3);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
        break;
    case 0x37:
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gCurrentActor->moveYaw, 7.0f);
        switch (gCurrentActor->subState) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(gCurrentActor);
            gCurrentActor->subState++;
            /* fallthrough */
        case 2:
            behaviourFadeOutWithinZone(8);
            break;
        case 3:
            gCurrentActor->state = 0x40;
            break;
        }
        break;
    case 0x40:
        break;
    default:
        behaviourUpdateContactAndState(0x2D7);
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
        /* fallthrough */
    default:
        enemyAggroStateUpdate(0x6400, 0x2D7, 0x2D8);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void behaviourSimplePatrolEnemyUpdate(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0, 0x31E, 0x31F);
    }
    actorPatrolFollowerUpdate(0x320, 0, 0);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void behaviourAmbushEnemyUpdate(void) {
    behaviourFrameBegin();
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.damaged != 0) && gCurrentActor->state != 0x37) {
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x37A);
        gCurrentActor->callbackMask &= ~0x8000;
    }
    switch (gCurrentActor->state) {
        case 4:
            if (gCurrentActor->sub4->animId == 0x378) {
                gCurrentActor->state = 0x23;
                gCurrentActor->subState = 0;
            } else if (actorIsTargetWithinDistance(0x64) != 0
                       && zoneCanReachPoint(gCurrentActor, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, gBehaviourZone) != 0) {
                actorScriptStart(gCurrentActor, 0x37B);
                gCurrentActor->state = 0x23;
                gCurrentActor->subState = 0;
                effectSpawnOctagonRing(0.7f, gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z);
            }
            break;
        case 0x23:
            switch (gCurrentActor->subState) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->chaseSpeed);
                    gCurrentActor->subState++;
                    /* fallthrough */
                case 1:
                    if ((randomNonNegative() >> 15) % 1000 >= 996) {
                        gCurrentActor->subState++;
                        actorScriptStart(gCurrentActor, 0x379);
                        actorSetTargetSpeed(gCurrentActor, 0);
                    } else {
                        if (gCurrentActor->sub4->animId == 0x378) {
                            actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
                        } else {
                            actorTurnTowardActorYaw(0xA, gBehaviourTargetActor);
                        }
                        if (actorIsTargetWithinDistance(0xC8) == 0
                            || zoneCanReachPoint(gCurrentActor, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, gBehaviourZone) == 0) {
                            actorScriptStart(gCurrentActor, 0x37C);
                            gCurrentActor->state = 4;
                            gCurrentActor->subState = 0;
                            actorSetTargetSpeed(gCurrentActor, 0);
                        }
                    }
                    break;
                case 2:
                    actorMoveWithinZone(0, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
                    break;
            }
            break;
        case 0x37:
            switch (gCurrentActor->subState) {
                case 0:
                    actorMoveWithinZone(0, 0.0f, 0.0f, 0x200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(gCurrentActor);
                    gCurrentActor->subState++;
                    /* fallthrough */
                case 2:
                    behaviourFadeOutWithinZone(0xA);
                    break;
                case 3:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        default:
            behaviourUpdateContactAndState(0x378);
            break;
    }
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

s32 behaviourDetectNearbyExplosive(void) {
    s32 found;
    s16 i;
    Actor *other;
    f32 dx;
    f32 dy;
    f32 dz;

    found = 0;
    for (i = 0; !found && i < gActiveActorCount; i++) {
        other = gActiveActors[i].actor;
        if (other->actorType == 0x29) {
            dx = other->x - gCurrentActor->x;
            dy = other->y - gCurrentActor->y;
            dz = other->z - gCurrentActor->z;
            if (dx * dx + dy * dy + dz * dz < 10000.0f) {
                gCurrentActor->state = 0x28;
                found = 1;
                gCurrentActor->subState = 0;
            }
        }
    }
    return found;
}

extern Actor *gPrimaryPlayerActor;

void behaviourExplosiveAwareEnemyUpdate(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        f64 cullMargin;

        cullMargin = gCurrentActor->sub4->scaleY / 0.15 * 100.0;
        gCurrentActor->cullMarginX = cullMargin > 255.0 ? 255.0 : cullMargin;
        cullMargin = gCurrentActor->sub4->scaleY / 0.15 * 100.0;
        gCurrentActor->cullMarginY = cullMargin > 255.0 ? 255.0 : cullMargin;
        behaviourSetAnimIds(0x35E, 0x35F, 0x360);
    }
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.damaged != 0) && gCurrentActor->state != 0x37) {
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x367);
        gCurrentActor->callbackMask &= ~0x8000;
    } else if (gActorGlobalState.bossFightPhase == 4) {
        behaviourSpawnExplosionAndSound(0x365, 0x31, gActorGlobalState.targetActor);
    } else if (gActorGlobalState.bossFightPhase == 5) {
        behaviourSpawnExplosionAndSound(0x366, 0x31, gActorGlobalState.targetActor);
    }
    if (gCurrentActor->state == 4) {
        gCurrentActor->state = 1;
    }
    switch (gCurrentActor->state) {
        case 0x37:
            gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gCurrentActor->moveYaw, 7.0f);
            switch (gCurrentActor->subState) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(gCurrentActor);
                    gCurrentActor->subState++;
                    /* fallthrough */
                case 2:
                    behaviourFadeOutWithinZone(8);
                    break;
                case 3:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        case 0x31:
            if (gCurrentActor->subState != 0 || gCurrentActor->sub4->model->speed == 0.0f) {
                actorSetDefaultState(0x35F);
            }
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
            break;
        case 0x27:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            switch (gCurrentActor->subState) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, (gFrameCounter & 1) ? 0x362 : 0x361);
                    gCurrentActor->subState = 1;
                    break;
                case 2:
                    gCurrentActor->interactionType = gCurrentActor->sub4->animId == 0x362 ? 4 : 2;
                    break;
                case 3:
                    gCurrentActor->interactionType = gCurrentActor->sub4->animId == 0x362 ? 8 : 1;
                    break;
                case 4:
                    gCurrentActor->interactionType = 1;
                    actorSetDefaultState(0x35F);
                    break;
            }
            break;
        case 0x28:
            actorTurnTowardActorYaw(0xA, gBehaviourTargetActor);
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            switch (gCurrentActor->subState) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, 0x363);
                    gCurrentActor->subState = 1;
                    break;
                case 2:
                    gCurrentActor->subState++;
                    break;
                case 4:
                    gBehaviourWorkState->targetActor = gPrimaryPlayerActor;
                    actorSetDefaultState(0x35F);
                    break;
            }
            break;
        case 0x11:
            if (behaviourDetectNearbyExplosive() == 0) {
                switch (gCurrentActor->subState) {
                    case 0:
                        actorSetTargetSpeed(gCurrentActor, 0);
                        actorScriptStart(gCurrentActor, 0x35E);
                        gCurrentActor->subState++;
                        /* fallthrough */
                    case 1:
                        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
                        if (gCurrentActor->speedXZ < 1.0f) {
                            gCurrentActor->subState++;
                        }
                        break;
                    case 2:
                        behaviourUpdateShadowAlpha();
                        if ((randomNonNegative() >> 15) % 1000 >= 996) {
                            actorSetDefaultState(0x35F);
                        }
                        break;
                }
            }
            break;
        case 1:
            if (behaviourCheckRandomAnimTrigger() != 0) {
                gCurrentActor->state = 0x11;
                gCurrentActor->subState = 0;
            }
            /* fallthrough */
        case 0x23:
            if (actorIsTargetWithinDistance(0x50) != 0 && behaviourIsTargetWithinAngle(0x1770) != 0) {
                gCurrentActor->state = 0x27;
                gCurrentActor->subState = 0;
            }
            /* fallthrough */
        case 0x10:
            behaviourDetectNearbyExplosive();
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
            break;
        default:
            behaviourUpdateContactAndState(0x2D7);
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
            /* fallthrough */
        default:
            enemyAggroStateUpdate(0x6400, 0x35F, 0x360);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
