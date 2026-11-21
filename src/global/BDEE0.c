#include "common.h"
#include "sched.h"
#include "actor.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/166A0.h"
#include "proto/global/17800.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/42630.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/89250.h"
#include "proto/global/AA960.h"
#include "proto/global/B1F60.h"
#include "proto/global/BDEE0.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

// Actor view whose second component (0x178) is an s16 block: [0] roll phase (behaviourArmadilloPatrol counts it
// down as a timer), [1] side, [3]/[4] x/z saved on entering state 0x15 (behaviourArmadilloPatrol,
// behaviourAttachToZoneOccupant, behaviourArmadilloMoveTowardTarget).
typedef struct ArmadilloActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ s16 *rollState;
} ArmadilloActor;

#define ARMADILLO_ACTOR ((ArmadilloActor *)gCurrentActor)

extern s16 gSfxSourceVoice[];
extern f32 gSfxVoicePitch[];
extern f32 gSfxVoiceModCounter[];

// The fairy cutscene's spawn order: entry i (counted down from 10) is the spawn-node id - 0x22 of the i-th child.
typedef struct FairySpawnOrder {
    u8 nodeOffset[11];
} FairySpawnOrder;

u8 D_80750620[8] = { 0x08, 0x05, 0x04, 0x07, 0x06, 0x01, 0x00, 0x00 }; // unreferenced; ends at sAttachAlignTargetNodes
u8 sAttachAlignTargetNodes[16] = {
    0x00, 0x08, 0x01, 0x01, 0x08, 0x04, 0x08, 0x06, 0x01, 0x02, 0x03, 0x05, 0x07, 0x00, 0x00, 0x00,
};
FairySpawnOrder gFairySpawnOrder = { { 0x00, 0x07, 0x05, 0x08, 0x06, 0x04, 0x01, 0x03, 0x02, 0x0A, 0x09 } };


void behaviourArmadilloPatrol(void) {
    u16 animFlags = 0;
    s16 *rollState = ARMADILLO_ACTOR->rollState;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0x321, 0x322, 0x323);
        actorAllocBoneRotations(0x11, 1);
        actorClearNodeFlag(gCurrentActor, 4);
        *rollState = gBehaviourExtraState->unkAWide * 10;
    }
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.damaged != 0) && gCurrentActor->state != 0x37) {
        gBehaviourWorkState->timer = 0x1388;
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x327);
        gCurrentActor->callbackMask &= 0xFFFF7FFF;
    } else if (gActorGlobalState.bossFightPhase == 4) {
        behaviourSpawnExplosionAndSound(0x325, 0x31, gActorGlobalState.targetActor);
    } else if (gActorGlobalState.bossFightPhase == 5) {
        behaviourSpawnExplosionAndSound(0x326, 0x31, gActorGlobalState.targetActor);
    }
    switch (gCurrentActor->state) {
    case 0x18:
        switch (gCurrentActor->subState) {
        case 0:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->subState++;
                gBehaviourWorkState->timer = 0xD;
            }
            gCurrentActor->sub4->boneRotations->rotZ += 0x7D0;
            break;
        case 1:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
                break;
            }
            if (gBehaviourWorkState->countdown != 0) {
                gCurrentActor->subState = 0;
                gBehaviourWorkState->countdown--;
                gBehaviourWorkState->timer = 0xA;
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1BA, 0x96, 0x7F, 0);
                break;
            }
            actorSetDefaultState(0x322);
            break;
        }
        break;
    case 0x31:
        if ((gCurrentActor->subState != 0) || (gCurrentActor->sub4->model->speed == 0.0f)) {
            actorSetDefaultState(0x322);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x11:
        switch (gCurrentActor->subState) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x321);
            gCurrentActor->subState++;
        case 1:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            if (gCurrentActor->speedXZ < 1.0f) {
                gCurrentActor->subState++;
            }
            break;
        case 2:
            behaviourUpdateShadowAlpha();
            if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x322);
            }
            break;
        }
        break;
    case 0x27:
        gCurrentActor->sub4->boneRotations->rotZ -= gCurrentActor->speedXZ * 50.0f;
        actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
        switch (gCurrentActor->subState) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x324);
            gCurrentActor->subState = 1;
            break;
        case 2:
            gCurrentActor->interactionType = 2;
            break;
        case 3:
            gCurrentActor->interactionType = 1;
            break;
        case 4:
            actorSetDefaultState(0x322);
            break;
        }
        break;
    case 1:
        if (behaviourCheckRandomAnimTrigger() != 0) {
            gCurrentActor->state = 0x11;
            gCurrentActor->subState = 0;
        }
    case 0x23:
        if (gActorGlobalState.bossFightPhase == 2) {
            if (behaviourIsTargetWithinAngle(0x2710) != 0) {
                gCurrentActor->state = 0x27;
                gCurrentActor->subState = 0;
            }
        }
    case 0x10:
        if ((gCurrentActor->state != 0x11) && (gCurrentActor->state != 0x27)) {
            if (gCurrentActor->subState == 0) {
                *rollState = gBehaviourExtraState->unkAWide * 2;
                gCurrentActor->subState = 1;
            }
            if (*rollState != 0) {
                (*rollState)--;
            } else {
                animFlags = 0x20;
                actorUpdateAnimSpeedFromSpeed(0);
                if (gCurrentActor->speedXZ != 0.0f) {
                    gCurrentActor->speedXZ = gCurrentActor->speedXZ - 1.0f;
                } else {
                    gCurrentActor->state = 0x18;
                    gCurrentActor->subState = 0; // ORIG: the target stores 0 (sb zero,341(t9) at 0x6e8) before the 1 (sb t2,341(t3) at 0x6f0)
                    gCurrentActor->subState = 1;
                    gBehaviourWorkState->timer = 0;
                    gBehaviourWorkState->countdown = 4;
                }
            }
        }
        gCurrentActor->sub4->boneRotations->rotZ -= gCurrentActor->speedXZ * 50.0f;
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, animFlags, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
        break;
    case 0x37:
        gCurrentActor->sub4->boneRotations->rotZ -= gBehaviourWorkState->timer;
        if (gBehaviourWorkState->timer != 0) {
            gBehaviourWorkState->timer -= 0x32;
        }
        switch (gCurrentActor->subState) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            sfxSpawnTableNodes(gCurrentActor);
            gCurrentActor->subState++;
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
        behaviourUpdateContactAndState(0x322);
        break;
    }
    if (gCurrentActor->speedXZ != 0.0f) {
        if (gCurrentActor->soundSlots[1] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x10A, 0, 1, 1, 0xFF, 1.0f, 0);
        } else {
            f64 t = (gCurrentActor->speedXZ * 0.6) / 40.0;
            u8 voice = gSfxSourceVoice[gCurrentActor->soundSlots[1]];

            gSfxVoicePitch[voice] = (t < 0.0 ? 0.0 : t) + 0.4;
            gSfxVoiceModCounter[voice] = 1.0f;
        }
    } else {
        sfxStopSlotSound(gCurrentActor, 1);
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
        enemyAggroStateUpdate(0x57E4, 0x322, 0x323);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void behaviourArmadilloUpdateMatrix(void) {
    behaviourFrameBegin();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern void *gPuffSprites[];

void actorSpawnRandomParticleNearActor(u8 particleType, s8 yOffset) {
    s32 pad;
    s32 randX;
    s32 randScale;
    s32 randSprite;

    switch (particleType) {
        case 0:
            effectSetCallback(effectPuffRiseUpdate);
            break;
        case 1:
            effectSetSpeed(-0x258);
            effectSetCallback(effectSinkBySpeedUpdate);
            break;
    }
    effectSetDepth(1);
    randSprite = randomNonNegative();
    randScale = randomNonNegative();
    randX = randomNonNegative();
    effectCreateAtPosition(gPuffSprites[((randSprite >> 15) % 1000) % 3], ((randScale >> 15) % 256) * 0.001953125 + 0.5, ((randX >> 15) % 6) + (gCurrentActor->x - 3.0f), gCurrentActor->y + yOffset, ((randomNonNegative() >> 15) % 6) + (gCurrentActor->z - 3.0f));
}

s32 actorBuildNodeAlignedMatrix(u8 nodeLookupIdx, u8 yOffset, f32 x, f32 y, f32 z) {
    f32 modelMtx[4][4];
    f32 stepMtx[4][4];
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    u8 node;

    node = sAttachAlignTargetNodes[nodeLookupIdx];
    if (node) {
        f32 ang;

        actorGetNodePos(gBehaviourZone->occupant, node, &nodeX, &nodeY, &nodeZ);
        mathNudgeCoords(x, z, &nodeX, &nodeZ);
        ang = mathAtan2(nodeX - x, nodeZ - z);
        guTranslateF(modelMtx, 0.0f, -yOffset, 0.0f);
        matrixMakeRotationY(stepMtx, (gCurrentActor->yaw * 0x168) / 4096);
        guMtxCatF(modelMtx, stepMtx, modelMtx);
        matrixMakeRotationX(stepMtx, -90.0f);
        guMtxCatF(modelMtx, stepMtx, modelMtx);
        guAlignF(stepMtx, (ang * 57.295776f) + 180.0f, nodeX - x, nodeY - y, nodeZ - z);
        guMtxCatF(modelMtx, stepMtx, modelMtx);
        guTranslateF(stepMtx, 0.0f, yOffset, 0.0f);
        guMtxCatF(modelMtx, stepMtx, modelMtx);
        guScaleF(stepMtx, gCurrentActor->sub4->scaleX, gCurrentActor->sub4->scaleY, gCurrentActor->sub4->scaleZ);
        guMtxCatF(modelMtx, stepMtx, modelMtx);
        guTranslateF(stepMtx, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        guMtxCatF(modelMtx, stepMtx, gCurrentActor->modelMtx);
        return 1;
    }
    return 0;
}


void behaviourArmadilloInitRollState(void) {
    gCurrentActor->collisionFlags = 2;
    gCurrentActor->state = 0x23;
    gCurrentActor->subState = 0;
    gCurrentActor->health = 1;
    gCurrentActor->interactionType = 1;
    gBehaviourWorkState->targetActor = gPrimaryPlayerActor;
    actorScriptStart(gCurrentActor, gBehaviourAnimState->animId2);
    gCurrentActor->yaw = ((randomNonNegative() >> 15) % 1024) + gPrimaryPlayerActor->yaw - 0x200;
    gCurrentActor->speedXZ = ((randomNonNegative() >> 15) % 100) + 0x32;
    gCurrentActor->speedY = ((randomNonNegative() >> 15) % 150) + 0x64;
}

extern PlayerStruct *gPlayerSlots;

extern u8 gEffectSpriteImpactFlash[];

s32 behaviourAttachToZoneOccupant(u8 yOffset, s16 animId) {
    s16 *rollState;
    Actor *tgt;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    u8 node;
    s32 anim;

    rollState = ARMADILLO_ACTOR->rollState;
    tgt = gBehaviourZone->occupant;
    if (tgt != NULL && tgt->state == 0x23 && gBehaviourZone->attachedCount < 10) {
        if (gCurrentActor->state != 0x15 && gCurrentActor->state != 0x17) {
            gCurrentActor->collisionFlags = 0x80;
            gCurrentActor->state = 0x15;
            gCurrentActor->subState = 0;
            actorScriptStart(gCurrentActor, 0);
            gCurrentActor->interactionType = 2;
            rollState[3] = gCurrentActor->x;
            rollState[4] = gCurrentActor->z;
        }
    }
    if (gCurrentActor->state == 0x15 && (tgt == NULL || tgt->state != 0x23)) {
        behaviourArmadilloInitRollState();
    }
    if (gCurrentActor->state == 0x15) {
        node = gBehaviourExtraState->attachNode;
        if (node == 5 || node == 7) {
            if ((tgt->sub4->animId == 0x21E || tgt->sub4->animId == 0x21F) && tgt->sub4->model->frame >= 4.0f && tgt->sub4->model->frame <= 12.0f) {
                gCurrentActor->interactionType = 4;
            } else {
                gCurrentActor->interactionType = 2;
            }
        }
        if (node == 1) {
            gCurrentActor->interactionType = 8;
        }
        if (gCurrentActor->movePitch != 0) {
            gCurrentActor->movePitch--;
        }
        if (tgt->subState != 0) {
            if (tgt->subState == 1 && gActorGlobalState.bossFightPhase == 2 && actorIsTargetWithinAngleDeg(tgt, gPrimaryPlayerActor, 0x1F40) != 0) {
                if (gPlayerSlots->sizeMode == 1) {
                    playerStateQueueCallback(0x32, gCurrentActor, 0);
                } else {
                    if (((randomNonNegative() >> 15) % 1000) >= 0x1F5) {
                        anim = 0x21F;
                    } else {
                        anim = 0x21E;
                    }
                    actorScriptStart(tgt, anim);
                    tgt->subState = 2;
                }
            } else if (gActorGlobalState.bossFightPhase == 4) {
                gBehaviourWorkState->targetAnimId = gBehaviourTargetActor->sub4->model->animId;
                gCurrentActor->flags |= 0x20000000;
                if (gCurrentActor->movePitch == 0) {
                    gCurrentActor->movePitch = 0x28;
                    effectCreateAtPosition(gEffectSpriteImpactFlash, 2.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                    sfxPlayOnFreeSlot(0x1CA, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    actorScriptStart(tgt, 0x220);
                    tgt->subState = 2;
                    tgt->health--;
                    if (tgt->health == 0) {
                        tgt->state = 0x37;
                        tgt->subState = 0;
                    }
                }
            }
        }
        gBehaviourZone->attachedCount++;
        actorGetNodePos(tgt, node, &nodeX, &nodeY, &nodeZ);
        if (gBehaviourWorkState->flags & 0x80) {
            if (!(gBehaviourWorkState->prevFlags & 0x80)) {
                gCurrentActor->speedY = 300.0f;
            }
            if (gCurrentActor->speedY > 0.0f) {
                return 0;
            }
            gCurrentActor->collisionMode = 0x24;
            if (animId != 0) {
                controllerAnimSetStateIfChanged(gCurrentActor, animId, 0.0f, 4.0f);
            }
            rollState[0] = (-rollState[0]) * 0.1 + rollState[0];
            rollState[1] = (-rollState[1]) * 0.1 + rollState[1];
            if (node < 0xB) {
                gCurrentActor->yaw = tgt->yaw;
            }
            gCurrentActor->x = nodeX;
            gCurrentActor->z = nodeZ;
            gCurrentActor->y = nodeY;
            if (actorBuildNodeAlignedMatrix(node, yOffset, nodeX, nodeY, nodeZ) != 0) {
                return 1;
            }
        }
    }
    return 0;
}


void behaviourArmadilloMoveTowardTarget(f32 speedMultiplier) {
    s16 *rollState;
    f32 x;
    f32 z;
    u8 state;
    s32 flags;

    state = gCurrentActor->state;
    rollState = ARMADILLO_ACTOR->rollState;
    x = gBehaviourWorkState->targetX;
    z = gBehaviourWorkState->targetZ;
    switch (state) {
        case 1:
        case 0x10:
        case 0x15:
        case 0x23:
            x = gBehaviourTargetActor->x;
            z = gBehaviourTargetActor->z;
        case 2:
        case 3:
        case 7:
        case 0x35:
            if (gCurrentActor->hasArcBounds != 0) {
                flags = 0x10;
            } else {
                flags = 0x810;
            }
            if (!(actorMoveWithinZone(state, x, z, flags, 0.0f) & 1) && gCurrentActor->hasArcBounds == 0) {
                *rollState = *rollState + speedMultiplier;
            }
            break;
        case 0x37:
            switch (gCurrentActor->subState) {
                case 2:
                    behaviourFadeOutWithinZone(10);
                    break;
                case 3:
                    gCurrentActor->state = 0x40;
                    break;
            }
            break;
        case 4:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x12, 0.0f);
            break;
        default:
            behaviourUpdateContactAndState(0);
            break;
    }
}


void behaviourArmadilloStepPatrol(void) {
    u8 state = gCurrentActor->state;

    switch (state) {
        case 0x15:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(state, 0);
        default:
            enemyAggroStateUpdate(0x2710, 0, 0);
    }
}

// Second component (0x178) of the rocking idle (behaviourRockingWalk): the s16 block ArmadilloActor.rollState indexes.
typedef struct RockTiltState {
    /* 0x0 */ s16 rollPhase;
    /* 0x2 */ s16 side;
    /* 0x4 */ u16 tilt;
} RockTiltState;

// Actor view whose second component is a RockTiltState (behaviourRockingWalk).
typedef struct RockingActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ RockTiltState *rock;
} RockingActor;
#define ROCKING_ACTOR ((RockingActor *)gCurrentActor)

void behaviourRockingWalk(sideOffset, rollAmount, pivotZ)
u8 sideOffset;
u8 rollAmount;
u8 pivotZ;
{
    RockTiltState *rock;
    f32 modelMtx[4][4];
    f32 rotMtx[4][4];
    s16 sgn;
    s32 dir = 0;
    f32 stepDist;
    s16 yawOffset;

    rock = ROCKING_ACTOR->rock;
    if (gBehaviourExtraState->attachNode && behaviourAttachToZoneOccupant(0x64, 0)) {
        return;
    }
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.damaged != 0) && gCurrentActor->state != 0x37) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1CA, 0xFF, 0x7F, 0x32);
        behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0);
        gBehaviourWorkState->timer = 0xA6;
        rock->tilt = 0x32;
    }
    behaviourArmadilloMoveTowardTarget(gCurrentActor->speedXZ * 5.0f);
    switch (gCurrentActor->state) {
    case 4:
        rock->rollPhase = rock->rollPhase + (-rock->rollPhase) * 0.3;
        break;
    case 0x37:
        actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x12, 0.0f);
        if (gCurrentActor->subState == 0) {
            gBehaviourWorkState->timer += rock->tilt;
            if (gBehaviourWorkState->timer == 0x196 || gBehaviourWorkState->timer == 0x244 || gBehaviourWorkState->timer == 0x307 || gBehaviourWorkState->timer == 0x3B1 || gBehaviourWorkState->timer == 0x45C || gBehaviourWorkState->timer == 0x508) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x17D, 0x9B, rock->tilt + 0x5A, 0);
            }
            rock->tilt--;
            if (rock->tilt < 2) {
                gCurrentActor->subState++;
                rock->tilt = 0;
                gBehaviourWorkState->scale = 0.0f;
            }
        }
        break;
    }
    if (rock->rollPhase >= 0x801) {
        stepDist = sqrtf((1.0 - cosApprox(0.7853982f)) * (2 * (f32)(sideOffset * 2) * (sideOffset * 2)));
        if (rock->side) {
            dir = 1;
        } else {
            dir = -1;
        }
        rock->rollPhase -= 0x800;
        rock->side ^= 1;
        yawOffset = dir << 8;
        gCurrentActor->x += gCurrentActor->sub4->scaleY * stepDist * mathSinF(gCurrentActor->yaw + yawOffset);
        gCurrentActor->z += gCurrentActor->sub4->scaleY * stepDist * mathCosF(gCurrentActor->yaw + yawOffset);
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x1B1, 0xFF, 0x7F, 0xA, 0x3C, 0.3f, 0);
    }
    behaviourArmadilloStepPatrol();
    if (rock->side) {
        sgn = -1;
    } else {
        sgn = 1;
    }
    guTranslateF(modelMtx, sgn * sideOffset, 0.0f, 0.0f);
    matrixMakeRotationZ(rotMtx, mathSinF(rock->rollPhase) * (sgn * rollAmount));
    guMtxCatF(modelMtx, rotMtx, modelMtx);
    if (gCurrentActor->state == 0x37) {
        matrixMakeRotationY(rotMtx, sgn * gBehaviourWorkState->timer);
    } else {
        matrixMakeRotationY(rotMtx, mathSinF(rock->rollPhase - 0x400) * (-sgn * 0x2D));
    }
    guMtxCatF(modelMtx, rotMtx, modelMtx);
    if (gCurrentActor->state == 0x37) {
        switch (gCurrentActor->subState) {
        case 1:
            gBehaviourWorkState->timer = mathAngleEaseToward((gBehaviourWorkState->timer << 12) / 0x168, 0, 3.0f) * 0x168 / 4096;
            rock->rollPhase = rock->rollPhase + (-rock->rollPhase) * 0.3;
            guTranslateF(rotMtx, 0.0f, 0.0f, -pivotZ);
            guMtxCatF(modelMtx, rotMtx, modelMtx);
            matrixMakeRotationX(rotMtx, rock->tilt);
            guMtxCatF(modelMtx, rotMtx, modelMtx);
            guTranslateF(rotMtx, 0.0f, 0.0f, pivotZ);
            gBehaviourWorkState->scale += 2.0f;
            rock->tilt = rock->tilt + gBehaviourWorkState->scale;
            if (rock->tilt >= 0x5B) {
                rock->tilt = 0x5A;
                if (gBehaviourWorkState->scale < 3.0f) {
                    gCurrentActor->subState++;
                } else {
                    sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x1B1, gBehaviourWorkState->scale * 255.0f / 20.0f, gBehaviourWorkState->scale + 100.0f, 0, 0x3C, 0.3f, 0);
                    gBehaviourWorkState->scale = -(gBehaviourWorkState->scale * 0.5);
                }
            }
            break;
        case 2:
            guTranslateF(rotMtx, 0.0f, 0.0f, -pivotZ);
            guMtxCatF(modelMtx, rotMtx, modelMtx);
            matrixMakeRotationX(rotMtx, 90.0f);
            guMtxCatF(modelMtx, rotMtx, modelMtx);
            guTranslateF(rotMtx, 0.0f, 0.0f, pivotZ);
            break;
        }
        guMtxCatF(modelMtx, rotMtx, modelMtx);
    }
    guTranslateF(rotMtx, -sgn * sideOffset, 0.0f, 0.0f);
    guMtxCatF(modelMtx, rotMtx, gCurrentActor->modelMtx);
    actorUpdateModelMatrix(gCurrentActor, 1);
}

void behaviourFairyUpdate(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->tintR = 0xFA;
        gCurrentActor->tintG = 0xFA;
        gCurrentActor->tintB = 0xFA;
    }
    if (gCurrentActor->state == 0x17) {
        actorSpawnRandomParticleNearActor(0, 0);
    }
    if (gBehaviourWorkState->countdown != 0) {
        gBehaviourWorkState->countdown--;
        gCurrentActor->hasArcBounds = 0;
        if (gBehaviourWorkState->countdown == 0 && gBehaviourTargetActor == gPrimaryPlayerActor) {
            gCurrentActor->collisionMode = 0x24;
        }
    }
}


void behaviourFairyInitPlayerScale(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        playerSetLargeModeScale(0.525f);
        gPrimaryPlayerActor->flags |= 0x400;
        gPrimaryPlayerActor->drawDistance = 0x7D0;
        gCurrentActor->flags &= ~4;
        actorSetUniformScale(gCurrentActor, 1.0f);
        gCurrentActor->unk15F = 0;
        gCurrentActor->yaw = mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->z);
        actorScriptStart(gCurrentActor, 0x21B);
        gBehaviourAnimState->flags |= 8;
        gBehaviourAnimState->animId1 = 0x21C;
    }
    switch (gCurrentActor->state) {
        case 4:
            gCurrentActor->state = 0x23;
            gCurrentActor->subState = 0;
        case 0x23:
            switch (gCurrentActor->subState) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
                    break;
                join:
                case 1:
                    if (gCurrentActor->sub4->animId != 0x21C) {
                        actorScriptStart(gCurrentActor, 0x21C);
                    }
                    actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
                    break;
                case 2:
                    break;
                default:
                    gCurrentActor->subState = 1;
                    goto join;
            }
            break;
        case 0x37:
            playerSetLargeModeScale(0.3f);
            gCurrentActor->state = 0x40;
            break;
    }
    gBehaviourZone->attachedCount = 0;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern Actor *gSpawnedActor;


s32 actorSpawnJitteredChild(u8 nodeId, s16 speed, s16 speedY, Actor *target) {
    BehaviourWorkState *childState;
    s32 randYaw;
    s32 randZ;
    s32 randX;

    if (gBehaviourWorkState->timer != 0) {
        actorSpawnRandomParticleNearActor(0, 0xA);
        gBehaviourWorkState->timer--;
        return 0;
    }
    randX = randomNonNegative();
    randZ = randomNonNegative();
    randYaw = randomNonNegative();
    if (spawnNodeSpawnById(nodeId,
                      ((randX >> 15) % 10) + (gCurrentActor->x - 5.0f),
                      gCurrentActor->y + 5.0f,
                      ((randZ >> 15) % 10) + (gCurrentActor->z - 5.0f),
                      ((randYaw >> 15) % 1024) + gCurrentActor->yaw - 0x200,
                      speed, speedY) != 0) {
        gSpawnedActor->state = 0x17;
        gSpawnedActor->subState = 0;
        childState = gSpawnedActor->customState;
        childState->countdown = 0x1E;
        if (target != NULL) {
            childState->node->flags &= ~8;
            childState->targetActor = target;
        }
        gSpawnedActor->collisionMode = 1;
        gSpawnedActor->drawDistance = 0x3E8;
        return 1;
    }
    return 0;
}


void behaviourFairyPlaySound(void) {
    sfxPlayActorSound(gCurrentActor, 0x11F, 0, 0, 0, 0xFF, 1.0f, 0);
    sfxAllocateChannel(0x3B, 1.0f);
}

extern PlayerState *gActivePlayerState;
extern s32 gGlobalCutsceneFlags;

void behaviourFairyWanderUpdate(void) {
    s16 i;
    s16 speed;
    s16 speedY;
    FairySpawnOrder order;
    u8 step;
    s32 alpha;

    speed = (randomNonNegative() >> 15) % 100 + 0x64;
    speedY = (randomNonNegative() >> 15) % 250 + 0xC8;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->cullMarginX = 0x3C;
        gCurrentActor->cullMarginY = 0x3C;
        gCurrentActor->drawDistance = 0x3E8;
        gCurrentActor->state = 0;
        gCurrentActor->subState = 0;
        actorScriptStart(gCurrentActor, 0x3DC);
        gBehaviourWorkState->timer = 0x78;
        gCurrentActor->renderFlags |= 0x20;
    }
    switch (gCurrentActor->state) {
    case 0:
        for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
            if (gActorGlobalState.volumeTriggerQueueOp[i] == 3) {
                gCurrentActor->state++;
            }
        }
        break;
    case 1:
        switch (gCurrentActor->subState) {
        case 0:
            if (gBehaviourWorkState->timer-- < 0x3C) {
                gCurrentActor->flags |= 0x400;
                actorScriptStart(gCurrentActor, 0x3DD);
                gCurrentActor->subState++;
            }
            break;
        case 2:
            effectSpawnChildAtNode(0, (randomNonNegative() >> 15) % 2048 + gCurrentActor->yaw - 0x400, (randomNonNegative() >> 15) % 1024);
            break;
        case 3:
            gGlobalCutsceneFlags |= 1;
            sfxAllocateChannel(0x68, 1.0f);
            gBehaviourWorkState->timer = 0x32;
            behaviourFairyPlaySound();
            gCurrentActor->state++;
            break;
        }
        break;
    case 2:
        if (actorSpawnJitteredChild(0x2A, speed, speedY, NULL) != 0) {
            gCurrentActor->state++;
        }
        break;
    case 3:
        if (spawnNodeHasActor(0x2A) == 0) {
            gBehaviourWorkState->timer = 0xA;
            gCurrentActor->state++;
        }
        break;
    case 4:
        behaviourFairyPlaySound();
        actorSpawnJitteredChild(0x28, speed, speedY, NULL);
        if (actorSpawnJitteredChild(0x29, speed + 0x28, speedY + 0x50, NULL) != 0) {
            gCurrentActor->state++;
        }
        break;
    case 5:
        if (spawnNodeHasActor(0x28) == 0 && spawnNodeHasActor(0x29) == 0) {
            gBehaviourWorkState->timer = 0xA;
            gCurrentActor->state++;
        }
        break;
    case 6:
        behaviourFairyPlaySound();
        actorSpawnJitteredChild(0x2B, speed, speedY, NULL);
        if (actorSpawnJitteredChild(0x2C, speed + 0x28, speedY + 0x50, NULL) != 0) {
            gCurrentActor->state++;
        }
        break;
    case 7:
        if (spawnNodeHasActor(0x2B) == 0 && spawnNodeHasActor(0x2C) == 0) {
            csSendActorMessagePayload(0x11, 1);
            spawnNodeSpawnById(0x2D, mathSinF(gCurrentActor->yaw) * 80.0f + gCurrentActor->x, gCurrentActor->y, mathCosF(gCurrentActor->yaw) * 80.0f + gCurrentActor->z, gCurrentActor->yaw, 0, 0);
            gBehaviourZone->occupant = gSpawnedActor;
            camStartPath(gCurrentActor, 0x1F, 1);
            gCurrentActor->state++;
            gBehaviourWorkState->timer = 0x1E;
            gCurrentActor->subState = 0xA;
        }
        break;
    case 8:
        if (gBehaviourWorkState->timer != 0) {
            gBehaviourWorkState->timer--;
        } else {
            order = gFairySpawnOrder;
            step = 0xA - gCurrentActor->subState;
            if (gCurrentActor->subState == 0xA) {
                behaviourFairyPlaySound();
            }
            if (gCurrentActor->subState) {
                actorSpawnJitteredChild(order.nodeOffset[gCurrentActor->subState--] + 0x22, step * 8 + 0x64, step * 20 + 0xFA, gBehaviourZone->occupant);
            } else {
                gCurrentActor->flags &= ~0x8000;
                gCurrentActor->collisionMode = 1;
                gCurrentActor->state++;
                camSetTarget(gCamActor, gCurrentActor, 4, 0x1129, 0x264, 0, 0, 0xAF, 0, 0, 1.0f);
                camSetTargetFocusActor(gCamActor, gPrimaryPlayerActor);
            }
            gBehaviourWorkState->timer = 0xF;
        }
        break;
    case 9:
        alpha = gCurrentActor->alpha - 0xA;
        if (alpha < 0) {
            gCurrentActor->alpha = 0;
        } else {
            gCurrentActor->alpha = alpha;
        }
        if (spawnNodeHasActor(0x2D) == 0) {
            csSendActorMessagePayload(0x11, 0xFF);
            camReturnToFollow(gCamActor, gPrimaryPlayerActor);
            spawnNodesSetRespawnHold(0);
            gGlobalCutsceneFlags &= ~1;
            if (gPlayerSlots->sizeMode != 1) {
                playerSetSizeMode(gPrimaryPlayerActor, 1);
                gActivePlayerState->scaleChangeRate = 0.05f;
            }
            gCurrentActor->state++;
            sfxStopChannel(0x68, 0);
            csModelStateSetFirstByte(0x7C, 0xA);
            gPrimaryPlayerActor->drawDistance = 0x1F4;
            gPrimaryPlayerActor->flags &= ~0x400;
            gCurrentActor->collisionMode = 0x24;
            camStartPath(gCurrentActor, 0x1F, 5);
        }
        break;
    case 10:
        alpha = gCurrentActor->alpha + 0xA;
        if (alpha >= 0x100) {
            gCurrentActor->alpha = 0xFF;
        } else {
            gCurrentActor->alpha = alpha;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void behaviourFairyIdle1(void) {
    behaviourFairyUpdate();
    if (gBehaviourExtraState->attachNode == 0 || behaviourAttachToZoneOccupant(0, 0x446) == 0) {
        actorPatrolFollowerUpdate(0x2ED, 1, 0);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}

void behaviourFairyIdle2(void) {
    behaviourFairyUpdate();
    if (gBehaviourExtraState->attachNode == 0 || behaviourAttachToZoneOccupant(0x32, 0x44E) == 0) {
        actorPatrolFollowerUpdate(0x2EC, 1, 0);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}

void behaviourFairyIdle3(void) {
    behaviourFairyUpdate();
    if (gBehaviourExtraState->attachNode == 0 || behaviourAttachToZoneOccupant(0x14, 0x44A) == 0) {
        actorPatrolFollowerUpdate(0x2EE, 1, 0);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}


void behaviourFairyIdle4(void) {
    behaviourFairyUpdate();
    behaviourRockingWalk(0x24, 0x14, 0x1E);
}
