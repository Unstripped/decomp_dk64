#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/35000.h"
#include "proto/global/70FD0.h"
#include "proto/global/7CA80.h"
#include "proto/global/AA960.h"
#include "proto/global/B1F60.h"


extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern s32 gCurrentMap;
extern PlayerStruct *gPlayerSlots;


void actorPatrolFollowerUpdate(s16 targetId, u8 skipStep, u16 movementFlags) {
    Actor *actor;

    if (targetId != 0 && (gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0)) {
        actor = gCurrentActor;
        if (actor->state != 0x37) {
            actor->speedY = 200.0f;
            behaviourCalculateDamageForce(gActorGlobalState.targetActor, targetId);
        }
    }
    if (gCurrentActor->state) {}  // FAKE: an IL-only use that lets uopt colour the targetId parameter (range 0 is left uncoloured without it)
    actor = gCurrentActor;
    switch (gCurrentActor->state) {
        case 1:
        case 0x10:
        case 0x15:
        case 0x23:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, (actor->contactFlags & 1) ? movementFlags : (movementFlags | 2), 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, movementFlags, 0.0f);
            break;
        case 0x37:
            switch (actor->unk155) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, movementFlags | 0x4200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(actor);
                    if (skipStep != 0) {
                        gCurrentActor->unk155 = 2;
                        break;
                    }
                    gCurrentActor->speedY = 100.0f;
                    actor = gCurrentActor;  // FAKE: re-read into the actor local so the reloaded pointer colours a2
                    actor->unk155++;
                case 2:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, movementFlags | 0x4200, 0.0f);
                    break;
                case 3:
                    behaviourFadeOutWithinZone(0xA);
                    break;
                case 4:
                    actor->state = 0x40;
                    break;
            }
            break;
        default:
            behaviourUpdateContactAndState(gBehaviourAnimState->animId1);
            break;
    }
    switch (gCurrentActor->state) {
        case 2:
        case 3:
            patrolPathStep(gCurrentActor->state, 1);
        default:
            enemyAggroStateUpdate(0x4C90, gBehaviourAnimState->animId1, gBehaviourAnimState->animId2);
        case 0x37:
        case 0x40:
            break;
    }
}

void func_806AD54C(void) {
    Actor *found;
    f32 dx;
    f32 dz;
    s32 dir;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        func_80724CA4(2, 1);
        behaviourSetAnimIds(0x1F8, 0x1F8, 0x1F9);
        if (gCurrentMap == 0x68 || gCurrentMap == 0x88 || gCurrentMap == 0x89) {
            gCurrentActor->interactionType = 2;
        }
    }
    if (gCurrentActor->interactionType == 2 && gCurrentActor->state != 0x36) {
        found = actorFindByType(0x11A);
        if (found != NULL) {
            if (found->state != 0) {
                if (!(gBehaviourWorkState->flags & 0x8000)) {
                    dx = found->x - gCurrentActor->x;
                    dz = found->z - gCurrentActor->z;
                    if ((dx * dx) + (dz * dz) < 1600.0f) {
                        dir = (((found->yaw - gCurrentActor->yaw) & 0xFFF) > 0x800) ? 1 : -1;
                        gCurrentActor->speedXZ = gBehaviourExtraState->unkD * 1.8;
                        gCurrentActor->yaw += dir * 0x190;
                        gCurrentActor->moveYaw = gCurrentActor->yaw;
                        gBehaviourWorkState->flags |= 0x8000;
                        gCurrentActor->state = 0x10;
                        gCurrentActor->unk155 = 0;
                    }
                }
            } else {
                gBehaviourWorkState->flags &= 0x7FFF;
            }
        }
    }
    actorPatrolFollowerUpdate(0x1FA, 0, 0);
    func_80724E48((gCurrentActor->state == 0x23) ? 0 : 2);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806AD7AC(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        func_80724CA4(2, 1);
        behaviourSetAnimIds(0x1F8, 0x1F8, 0x1F9);
    }
    actorPatrolFollowerUpdate(0x1FA, 0, 0);
    func_80724E48((gCurrentActor->state == 0x23) ? 0 : 2);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorFollowLinkedNodeFadeUpdate(void) {
    Actor *linked;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->sub4->scaleX = 0.05f;
        gCurrentActor->sub4->scaleZ = 0.05f;
        gCurrentActor->sub4->scaleY = 2.0f;
        gCurrentActor->flags |= 0x400;
    }
    switch (gCurrentActor->state) {
        case 0:
            linked = gCurrentActor->parentActor;
            if (linked == NULL || (linked->contactFlags & 1)) {
                gCurrentActor->state = 1;
                gCurrentActor->flags &= ~0x8000;
            } else {
                actorGetNodePos(linked, 2, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
                gCurrentActor->roll = gCurrentActor->parentActor->roll;
            }
            break;
        case 1:
            if (gCurrentActor->alpha >= 0xB) {
                gCurrentActor->alpha -= 0xA;
            } else {
                actorDespawn(gCurrentActor);
            }
            break;
    }
    gCurrentActor->yaw = gPlayerSlots->unk2C8 & 0xFFF;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorSpawnLinkedFollower(void) {
    actorSpawn(0x118, 0xC0);
    gSpawnedActor->parentActor = gCurrentActor;
    gSpawnedActor->drawDistance = 0x7D0;
}

void func_806AD9F4(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x200;
        behaviourSetAnimIds(0x2F4, 0x2F4, 0x2F4);
        if (gCurrentActor->y != gCurrentActor->floorY) {
            gCurrentActor->state = 0x1E;
            actorScriptStart(gCurrentActor, 0x2F8);
            actorSpawnLinkedFollower();
        }
    }
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x2F7);
        actorSetTargetSpeed(gCurrentActor, 0);
        gCurrentActor->speedXZ = -200.0f;
    } else if (gActorGlobalState.bossFightPhase == 4) {
        gCurrentActor->interactionType = 2;
        behaviourSpawnExplosionAndSound(0x2F6, 0x27, gActorGlobalState.targetActor);
        gCurrentActor->speedXZ *= 2;
        gBehaviourWorkState->timer = 0x1F4;
    }
    switch (gCurrentActor->state) {
        case 0x1E:
            actorMoveWithinZone(0, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x4202, 0.0f);
            if (gCurrentActor->unk155 != 0) {
                actorSetDefaultState(0x2F4);
            }
            break;
        case 0x27:
            actorMoveWithinZone(0, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x4300, 0.0f);
            gCurrentActor->yaw += gBehaviourWorkState->timer;
            if (gBehaviourWorkState->timer >= 0x15) {
                gBehaviourWorkState->timer -= 0x14;
            } else {
                gBehaviourWorkState->timer = 0;
                gCurrentActor->moveYaw = gCurrentActor->yaw;
            }
            if (gCurrentActor->unk155 != 0 && gBehaviourWorkState->timer == 0) {
                gCurrentActor->interactionType = 1;
                actorSetDefaultState(0x2F4);
            }
            break;
        case 0x28:
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, 0x2F5);
                    gCurrentActor->unk155++;
                case 1:
                    actorMoveWithinZone(0, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x4200, 0.0f);
                    if (gCurrentActor->speedXZ < 1.0f) {
                        gCurrentActor->unk155++;
                    }
                    break;
                case 3:
                    actorSetDefaultState(0x2F4);
                    break;
            }
            break;
        case 1:
            if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                if (gCurrentActor->contactFlags & 1) {
                    gCurrentActor->state = 0x28;
                    gCurrentActor->unk155 = 0;
                }
            }
        default:
            actorPatrolFollowerUpdate(0, 1, 0);
            break;
    }
    func_8072881C(0, &gBehaviourWorkState->unk28);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806ADDD8(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x40;
        gBehaviourAnimState->animId1 = 0x31A;
    }
    switch (gCurrentActor->state) {
        case 0:
        case 1:
            if (actorIsTargetWithinDistance(0x12C) != 0) {
                actorScriptStart(gCurrentActor, 0x31A);
                gCurrentActor->state = 0x23;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 4:
            if (gCurrentActor->sub4->animId != 0x319) {
                gCurrentActor->state = 0x23;
                gCurrentActor->unk155 = 0;
            } else if (actorIsTargetWithinDistance(0x64) != 0) {
                actorScriptStart(gCurrentActor, 0x31B);
                gCurrentActor->state = 0x1E;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 0x1E:
            if (gCurrentActor->sub4->animId == 0x31A) {
                gCurrentActor->state = 0x23;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 0x23:
            if (gCurrentActor->sub4->animId == 0x31A && gCurrentActor->sub4->model->frame > 4.0f) {
                actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
            }
            if (actorIsTargetWithinDistance(0x12C) == 0) {
                actorScriptStart(gCurrentActor, 0x31C);
                gCurrentActor->state = 0;
                gCurrentActor->unk155 = 0;
            }
            break;
        default:
            behaviourUpdateContactAndState(0x31A);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
