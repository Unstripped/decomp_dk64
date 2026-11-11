#include "common.h"
#include "actor.h"
#define PROTO_SKIP_behaviourUpdateContactAndState // PROTO: The number of arguments doesn't agree with the number in the
#include "proto/global/103AB0.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/166A0.h"
#include "proto/global/17800.h"
#include "proto/global/19A00.h"
#include "proto/global/35000.h"
#include "proto/global/42630.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/936B0.h"
#include "proto/global/AA960.h"
#include "proto/global/B1F60.h"
#include "proto/global/B2CE0.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"

typedef struct B2CE0Sub178 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
} B2CE0Sub178;

// Actor plus its component pointers (0x174 on).
typedef struct B2CE0Actor {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ B2CE0Sub178* unk178;
} B2CE0Actor;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;

extern u8 D_8071FBC8[];
void behaviourUpdateContactAndState();
extern u16 gActiveActorCount;
extern ActorEntry gActiveActors[];

void func_806ADFE0(void) {
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
    if (gCurrentActor->unk15F != 0) {
        actorUpdateModelMatrix(gCurrentActor, 0);
    } else {
        guTranslateF(transMtx, 0, -30.0f, 0);
        matrixMakeRotationX(rotMtx, 180.0f);
        guMtxCatF(transMtx, rotMtx, transMtx);
        guTranslateF(rotMtx, 0, 30.0f, 0.0f);
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
        effectCreateAtPosition(D_8071FBC8, 1.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        actorDespawn(gCurrentActor);
    }
}

void actorSpawnChildAtNode(s32 actorType, s16 angleOffset, s16 nodeIndex, s16 extraParam) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    if (actorSpawn(0xED, actorType) != 0) {
        actorGetNodePos(gCurrentActor, nodeIndex, &nodeX, &nodeY, &nodeZ);
        gSpawnedActor->floorY = gCurrentActor->floorY;
        gSpawnedActor->yaw = gCurrentActor->yaw + angleOffset;
        gSpawnedActor->moveYaw = gSpawnedActor->yaw;
        gSpawnedActor->yawSpeed = extraParam;
        gSpawnedActor->x = nodeX;
        gSpawnedActor->y = nodeY;
        gSpawnedActor->z = nodeZ;
        actorSetUniformScale(gSpawnedActor, gCurrentActor->sub4->scaleY);
    }
}


void func_806AE394(f32 distOffset, f32 radius) {
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
    node1X = mathSinF(angle) * distOffset + gCurrentActor->x;
    node1Z = mathCosF(angle) * distOffset + gCurrentActor->z;
    lightAdd(node1X, gCurrentActor->y, node1Z, 0.0f, 0.0f, 0.0f, radius, 0, 0xFF, 0xFF, 0xFF);
    if (gCurrentActor->state != 0) {
        if ((gBehaviourTargetActor->x - node1X) * (gBehaviourTargetActor->x - node1X) + (gBehaviourTargetActor->y - gCurrentActor->y) * (gBehaviourTargetActor->y - gCurrentActor->y) + (gBehaviourTargetActor->z - node1Z) * (gBehaviourTargetActor->z - node1Z) < radius * radius) {
            gCurrentActor->yaw = mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->z);
            playerStateQueueCallback(0x43, gCurrentActor, 0);
            gCurrentActor->state = 0;
            gCurrentActor->unk155 = 0;
        }
    }
}

extern s32 gCurrentMap;

void func_806AE588(void) {
    s32 sel;
    s32 sw;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0x1FD, 0x1FB, 0x1FC);
        func_80724CA4(3, 1);
        actorClearNodeFlag(gCurrentActor, 3);
        if (gCurrentMap == 0xA5) {
            gCurrentActor->interactionType = 1;
        }
    }
    func_8072881C(0, &gBehaviourWorkState->unk28);
    sel = gCurrentActor->state;
    if ((sel != 0x32) || (gActorGlobalState.unk15 != 0)) {
        if (((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0)) && (sel != 0x37)) {
            if (gCurrentActor->health < -1) {
                behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x202);
                gCurrentActor->speedY = 250.0f;
            } else {
                behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x201);
                gCurrentActor->speedY = 200.0f;
            }
            gBehaviourWorkState->unk35 = 2;
            gCurrentActor->callbackMask &= 0xFFFF7FFF;
        } else if (gActorGlobalState.bossFightPhase == 4) {
            behaviourSpawnExplosionAndSound(0x1FF, 0x31, gActorGlobalState.targetActor);
        } else if (gActorGlobalState.bossFightPhase == 5) {
            behaviourSpawnExplosionAndSound(0x200, 0x32, gActorGlobalState.targetActor);
            gCurrentActor->speedY = 220.0f;
        }
    }
    sel = gCurrentActor->state;
    sw = sel;
    switch (sel) {
    case 0x31:
        if ((gCurrentActor->unk155 != 0) || (gCurrentActor->sub4->model->speed == 0.0f)) {
            actorSetDefaultState(0x1FB);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x32:
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gCurrentActor->moveYaw, 7.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
            break;
        case 1:
            gCurrentActor->speedY = 200.0f;
            gCurrentActor->speedXZ = 120.0f;
            gCurrentActor->unk155++;
        case 2:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 3:
            actorSetDefaultState(0x1FB);
            break;
        }
        break;
    case 0x11:
        func_80724E48(5);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x1FD);
            gCurrentActor->unk155++;
        case 1:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            if (gCurrentActor->speedXZ < 1.0f) {
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            behaviourUpdateShadowAlpha();
            if ((randomNonNegative() >> 0xF) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x1FB);
            }
            break;
        }
        break;
    case 0x27:
        actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x1FE);
            gCurrentActor->unk155 = 1;
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
            gCurrentActor->unk155 = 0;
        }
    case 0x23:
        if ((gActorGlobalState.bossFightPhase == 2) && (behaviourIsTargetWithinAngle(0x2710) != 0)) {
            gCurrentActor->state = 0x27;
            gCurrentActor->unk155 = 0;
        }
        sel = gCurrentActor->state;
    case 0x10:
        func_80724E48((sel == 1) ? 2 : 0);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_80724E48((sw == 0x35) ? 2 : 3);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
        break;
    case 0x37:
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gCurrentActor->moveYaw, 7.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            if ((gCurrentMap == 0xA5) && (gCurrentActor->unk15F != 0)) {
                csModelStateSetFirstByte(0, 0xA);
            }
            sfxSpawnTableNodes(gCurrentActor);
            gCurrentActor->unk155++;
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
        behaviourUpdateContactAndState(0x1FB, sel);
        break;
    }
    sel = gCurrentActor->state;
    switch (sel) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        patrolPathStep(gCurrentActor->state, 1);
    default:
        enemyAggroStateUpdate(0x6400, 0x1FB, 0x1FC);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806AEE08(void) {
    if ((randomNonNegative() >> 15) % 1000 >= 0x3D5 && behaviourIsTargetWithinAngle(0xFA0) != 0 && !(gBehaviourWorkState->flags & 0x80)) {
        gCurrentActor->state = 0x25;
        gCurrentActor->unk155 = 0;
    }
}

void func_806AEE84(void) {
    B2CE0Sub178 *patrolState;
    f32 scaleFactor;

    patrolState = ((B2CE0Actor *)gCurrentActor)->unk178;
    scaleFactor = gCurrentActor->sub4->scaleY / 0.15;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        patrolState->unk0 = 0x2710;
        patrolState->unk2 = 0x20;
        behaviourSetAnimIds(0x2AD, 0x2AB, 0x2AC);
        func_80724CA4(2, 1);
    }
    if (gCurrentActor->state != 0x32 || gActorGlobalState.unk15 != 0) {
        if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
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
            if (gCurrentActor->unk155 != 0 || gCurrentActor->sub4->model->speed == 0.0f) {
                actorSetDefaultState(0x2AB);
            }
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
            break;
        case 0x11:
            func_80724E48(5);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, 0x2B0);
                    gCurrentActor->unk155 = 1;
                case 1:
                    actorMoveWithinZone(0x11, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
                    if (gCurrentActor->speedXZ < 1.0f) {
                        gCurrentActor->unk155++;
                    }
                    break;
                case 2:
                    func_806AEE08();
                    behaviourUpdateShadowAlpha();
                    if ((randomNonNegative() >> 15) % 1000 >= 0x3DF && gCurrentActor->sub4->model->animId != 0x4C4) {
                        actorSetDefaultState(0x2AB);
                    }
            }
            break;
        case 0x27:
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    gCurrentActor->speedXZ = 0.0f;
                    actorScriptStart(gCurrentActor, 0x2B4);
                    gCurrentActor->unk155 = 1;
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
            func_80724E48(0);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorScriptStart(gCurrentActor, 0x2B3);
                    gCurrentActor->unk155 = 1;
                    break;
                case 2:
                    projectileGetTargetCoords(gCurrentActor, 2);
                    projectileSpawnNodeEntry(0x32, 0x63, scaleFactor * 0.4, gCurrentActor->yaw, 300.0f, 280.0f, gCurrentActor);
                    gCurrentActor->unk155 = 3;
                    break;
                case 4:
                    actorSetDefaultState(0x2AB);
                    break;
            }
            break;
        case 1:
            if (behaviourCheckRandomAnimTrigger() != 0) {
                gCurrentActor->state = 0x11;
                gCurrentActor->unk155 = 0;
            }
        case 0x23:
            if (gActorGlobalState.bossFightPhase == 2 && behaviourIsTargetWithinAngle(0x1388) != 0) {
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155 = 0;
            }
        case 0x10:
            func_806AEE08();
            func_80724E48(gCurrentActor->state == 1 ? 2 : 0);
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_80724E48(gCurrentActor->state == 0x35 ? 2 : 3);
            actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
            break;
        case 0x37:
            switch (gCurrentActor->unk155) {
                case 0:
                    gCurrentActor->yaw += gBehaviourWorkState->timer;
                    gBehaviourWorkState->timer = gBehaviourWorkState->timer * 0.95;
                    break;
                case 1:
                    sfxSpawnTableNodes(gCurrentActor);
                    gCurrentActor->unk155++;
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
        default:
            enemyAggroStateUpdate(0x6400, 0x2AB, 0x2AC);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806AF688(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0x2C0, 0x2C1, 0x2C1);
        func_80724CA4(0xE, 1);
        gBehaviourWorkState->flags |= 0x800;
        gCurrentActor->flags |= 0x400;
    }
    func_806AE394(40.0f, 70.0f);
    if (gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) {
        gCurrentActor->state = 0x3A;
        gCurrentActor->unk155 = 0;
    }
    switch (gCurrentActor->state) {
        case 0x11:
            func_80724E48(2);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, 0x2C0);
                    gCurrentActor->unk155++;
                case 1:
                    actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
                    if (gCurrentActor->speedXZ < 1.0f) {
                        gCurrentActor->unk155++;
                    }
                    break;
                case 2:
                    behaviourUpdateShadowAlpha();
                    if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                        actorSetDefaultState(0x1FB);
                    }
                    break;
            }
            break;
        case 1:
            if (behaviourCheckRandomAnimTrigger() != 0) {
                gCurrentActor->state = 0x11;
                gCurrentActor->unk155 = 0;
            }
            func_80724E48(gCurrentActor->state == 1 ? 2 : 0);
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_80724E48(gCurrentActor->state == 0x35 ? 2 : 3);
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

extern u8 D_8072073C;

void effectSpawnActorParticleBurst(u8 nodeIndex) {
    s16 i;
    f32 temp;

    for (i = 0; i < 7; i++) {
        temp = gCurrentActor->sub4->scaleY / 0.15;
        effectSetDepth(1);
        effectSetDuration(10);
        effectSetCallback(effectTumbleBounceUpdate);
        effectSetMode(2);
        effectSetSpeed(0);
        effectCreateAtActorBone(&D_8072073C, temp * 0.15, gCurrentActor, nodeIndex, 0);
    }
}

void func_806AFB58(void) {
    s32 sel;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk146 = -1;
        behaviourSetAnimIds(0x2D9, 0x2D7, 0x2D8);
        func_80724CA4(2, 1);
        gCurrentActor->unkEC = 0x1770;
    }
    if (((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0)) && (gCurrentActor->state != 0x37)) {
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x2DD);
        gBehaviourWorkState->unk35 = 2;
        gCurrentActor->callbackMask &= 0xFFFF7FFF;
    } else if ((gActorGlobalState.bossFightPhase == 4) || (gActorGlobalState.bossFightPhase == 5)) {
        if (gCurrentActor->unk146 & 1) {
            gBehaviourWorkState->unk1E = 0xF;
            gBehaviourWorkState->unk1F = 0xF;
            gCurrentActor->unkEC = -1;
            actorSpawnChildAtNode(0xC2, 0x800, 1, 0x190);
            gSpawnedActor->unk15F = 1;
            effectSpawnActorParticleBurst(1);
        } else if (gCurrentActor->unk146 & 2) {
            effectSpawnActorParticleBurst(2);
        }
        gCurrentActor->unk146 = gCurrentActor->unk146 * 2;
        behaviourSpawnExplosionAndSound(0x2DC, 0x31, gActorGlobalState.targetActor);
        gBehaviourWorkState->unk26 = 0;
        gCurrentActor->speedXZ = 0.0f;
    }
    sel = gCurrentActor->state;
    switch (gCurrentActor->state) {
    case 0x31:
        if ((gCurrentActor->unk155 != 0) || (gCurrentActor->sub4->model->speed == 0.0f)) {
            actorSetDefaultState(0x2D7);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
        break;
    case 0x11:
        func_80724E48(5);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x2D9);
            gCurrentActor->unk155++;
        case 1:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            if (gCurrentActor->speedXZ < 1.0f) {
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            behaviourUpdateShadowAlpha();
            if ((randomNonNegative() >> 0xF) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x2D7);
            }
            break;
        }
        break;
    case 0x27:
        if (gCurrentActor->unkEC < 0xFFFF) {
            actorTurnTowardActorYaw(0xA, gBehaviourTargetActor);
        }
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            if ((gCurrentActor->sub4->scaleY > 0.18) && ((randomNonNegative() >> 0xF) % 1000 >= 0x1F5)) {
                actorScriptStart(gCurrentActor, 0x2DB);
            } else {
                actorScriptStart(gCurrentActor, 0x2DA);
            }
            gCurrentActor->unk155 = 1;
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
            gCurrentActor->unk155 = 0;
        }
    case 0x23:
        if ((gActorGlobalState.bossFightPhase == 2) && (behaviourIsTargetWithinAngle(gCurrentActor->unkEC) != 0)) {
            gCurrentActor->state = 0x27;
            gCurrentActor->unk155 = 0;
        }
        sel = gCurrentActor->state;
    case 0x10:
        func_80724E48((sel == 1) ? 2 : 0);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        func_80724E48((sel == 0x35) ? 2 : 3);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
        break;
    case 0x37:
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gCurrentActor->moveYaw, 7.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(gCurrentActor);
            gCurrentActor->unk155++;
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
        behaviourUpdateContactAndState(0x2D7, sel);
        break;
    }
    sel = gCurrentActor->state;
    switch (sel) {
    case 0x31:
    case 0x37:
    case 0x40:
        break;
    case 2:
    case 3:
        patrolPathStep(gCurrentActor->state, 1);
    default:
        enemyAggroStateUpdate(0x6400, 0x2D7, 0x2D8);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806B02EC(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0, 0x31E, 0x31F);
    }
    actorPatrolFollowerUpdate(0x320, 0, 0);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806B0354(void) {
    behaviourFrameBegin();
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x37A);
        gCurrentActor->callbackMask &= ~0x8000;
    }
    switch (gCurrentActor->state) {
        case 4:
            if (gCurrentActor->sub4->animId == 0x378) {
                gCurrentActor->state = 0x23;
                gCurrentActor->unk155 = 0;
            } else if (actorIsTargetWithinDistance(0x64) != 0
                       && zoneCanReachPoint(gCurrentActor, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, D_807FDCA0) != 0) {
                actorScriptStart(gCurrentActor, 0x37B);
                gCurrentActor->state = 0x23;
                gCurrentActor->unk155 = 0;
                effectSpawnOctagonRing(0.7f, gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z);
            }
            break;
        case 0x23:
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkD);
                    gCurrentActor->unk155++;
                case 1:
                    if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                        gCurrentActor->unk155++;
                        actorScriptStart(gCurrentActor, 0x379);
                        actorSetTargetSpeed(gCurrentActor, 0);
                    } else {
                        if (gCurrentActor->sub4->animId == 0x378) {
                            actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
                        } else {
                            actorTurnTowardActorYaw(0xA, gBehaviourTargetActor);
                        }
                        if (actorIsTargetWithinDistance(0xC8) == 0
                            || zoneCanReachPoint(gCurrentActor, gBehaviourTargetActor->x, gBehaviourTargetActor->y, gBehaviourTargetActor->z, D_807FDCA0) == 0) {
                            actorScriptStart(gCurrentActor, 0x37C);
                            gCurrentActor->state = 4;
                            gCurrentActor->unk155 = 0;
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
            switch (gCurrentActor->unk155) {
                case 0:
                    actorMoveWithinZone(0, 0.0f, 0.0f, 0x200, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(gCurrentActor);
                    gCurrentActor->unk155++;
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
    func_8072881C(0, &gBehaviourWorkState->unk28);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

s32 func_806B0770(void) {
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
                gCurrentActor->unk155 = 0;
            }
        }
    }
    return found;
}

extern s32 gFrameCounter;
extern Actor *gPrimaryPlayerActor;

void func_806B0848(void) {
    s32 sel;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        f64 d;
        f64 m = 255.0;

        d = gCurrentActor->sub4->scaleY / 0.15 * 100.0;
        if (d > m) gCurrentActor->cullMarginX = m; else gCurrentActor->cullMarginX = d; // LAYOUT: one line keeps as1's order of the li t2/t0 rounding-mode pair
        d = gCurrentActor->sub4->scaleY / 0.15 * 100.0;
        if (d > m) gCurrentActor->cullMarginY = m; else gCurrentActor->cullMarginY = d; // LAYOUT: one line keeps as1's order of the li t7/t5 rounding-mode pair
        behaviourSetAnimIds(0x35E, 0x35F, 0x360);
    }
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x367);
        gCurrentActor->callbackMask &= 0xFFFF7FFF;
    } else if (gActorGlobalState.bossFightPhase == 4) {
        behaviourSpawnExplosionAndSound(0x365, 0x31, gActorGlobalState.targetActor);
    } else if (gActorGlobalState.bossFightPhase == 5) {
        behaviourSpawnExplosionAndSound(0x366, 0x31, gActorGlobalState.targetActor);
    }
    sel = gCurrentActor->state;
    if (sel == 4) {
        gCurrentActor->state = 1;
        sel = gCurrentActor->state;
    }
    switch (sel) {
        case 0x37:
            gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gCurrentActor->moveYaw, 7.0f);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(gCurrentActor);
                    gCurrentActor->unk155++;
                case 2:
                    behaviourFadeOutWithinZone(8);
                    break;
                case 3:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        case 0x31:
            if (gCurrentActor->unk155 != 0 || gCurrentActor->sub4->model->speed == 0.0f) {
                actorSetDefaultState(0x35F);
            }
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4200, 0.0f);
            break;
        case 0x27:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, (gFrameCounter & 1) ? 0x362 : 0x361);
                    gCurrentActor->unk155 = 1;
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
            switch (gCurrentActor->unk155) {
                case 0:
                    actorSetTargetSpeed(gCurrentActor, 0);
                    actorScriptStart(gCurrentActor, 0x363);
                    gCurrentActor->unk155 = 1;
                    break;
                case 2:
                    gCurrentActor->unk155++;
                    break;
                case 4:
                    gBehaviourWorkState->unk4 = gPrimaryPlayerActor;
                    actorSetDefaultState(0x35F);
                    break;
            }
            break;
        case 0x11:
            if (func_806B0770() == 0) {
                switch (gCurrentActor->unk155) {
                    case 0:
                        actorSetTargetSpeed(gCurrentActor, 0);
                        actorScriptStart(gCurrentActor, 0x35E);
                        gCurrentActor->unk155++;
                    case 1:
                        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
                        if (gCurrentActor->speedXZ < 1.0f) {
                            gCurrentActor->unk155++;
                        }
                        break;
                    case 2:
                        behaviourUpdateShadowAlpha();
                        if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                            actorSetDefaultState(0x35F);
                        }
                        break;
                }
            }
            break;
        case 1:
            if (behaviourCheckRandomAnimTrigger() != 0) {
                gCurrentActor->state = 0x11;
                gCurrentActor->unk155 = 0;
            }
        case 0x23:
            if (actorIsTargetWithinDistance(0x50) != 0 && behaviourIsTargetWithinAngle(0x1770) != 0) {
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155 = 0;
            }
        case 0x10:
            func_806B0770();
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
        default:
            enemyAggroStateUpdate(0x6400, 0x35F, 0x360);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
