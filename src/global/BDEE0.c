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

// Actor view whose unk178 is a s16 array (behaviourArmadilloPatrol, behaviourArmadilloInitRollState, behaviourArmadilloAimAndShoot).
typedef struct BDEE0ActorAlt {
    /* 0x000 */ Actor base;
    /* 0x178 */ s16 *unk178;
} BDEE0ActorAlt;

#define BDEE0AA ((BDEE0ActorAlt *)gCurrentActor)

extern u8 D_80770629[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];


void behaviourArmadilloPatrol(void) {
    u16 animFlags = 0;
    s16 *heightTarget = BDEE0AA->unk178;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0x321, 0x322, 0x323);
        func_80724CA4(0x11, 1);
        actorClearNodeFlag(gCurrentActor, 4);
        *heightTarget = gBehaviourExtraState->unkAWide * 10;
    }
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
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
        switch (gCurrentActor->unk155) {
        case 0:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->unk155++;
                gBehaviourWorkState->timer = 0xD;
            }
            gCurrentActor->sub4->boneRotations->rotZ += 0x7D0;
            break;
        case 1:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
                break;
            }
            if (gBehaviourWorkState->unk2E != 0) {
                gCurrentActor->unk155 = 0;
                gBehaviourWorkState->unk2E--;
                gBehaviourWorkState->timer = 0xA;
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1BA, 0x96, 0x7F, 0);
                break;
            }
            actorSetDefaultState(0x322);
            break;
        }
        break;
    case 0x31:
        if ((gCurrentActor->unk155 != 0) || (gCurrentActor->sub4->model->speed == 0.0f)) {
            actorSetDefaultState(0x322);
        }
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4300, 0.0f);
        break;
    case 0x11:
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x321);
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
                actorSetDefaultState(0x322);
            }
            break;
        }
        break;
    case 0x27:
        gCurrentActor->sub4->boneRotations->rotZ -= gCurrentActor->speedXZ * 50.0f;
        actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x324);
            gCurrentActor->unk155 = 1;
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
            gCurrentActor->unk155 = 0;
        }
    case 0x23:
        if (gActorGlobalState.bossFightPhase == 2) {
            if (behaviourIsTargetWithinAngle(0x2710) != 0) {
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155 = 0;
            }
        }
    case 0x10:
        if ((gCurrentActor->state != 0x11) && (gCurrentActor->state != 0x27)) {
            if (gCurrentActor->unk155 == 0) {
                *heightTarget = gBehaviourExtraState->unkAWide * 2;
                gCurrentActor->unk155 = 1;
            }
            if (*heightTarget != 0) {
                (*heightTarget)--;
            } else {
                animFlags = 0x20;
                actorUpdateAnimSpeedFromSpeed(0);
                if (gCurrentActor->speedXZ != 0.0f) {
                    gCurrentActor->speedXZ = gCurrentActor->speedXZ - 1.0f;
                } else {
                    gCurrentActor->state = 0x18;
                    gCurrentActor->unk155 = 0;
                    gCurrentActor->unk155 = 1;
                    gBehaviourWorkState->timer = 0;
                    gBehaviourWorkState->unk2E = 4;
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
        actorMoveWithinZone(gCurrentActor->state, (f32)gBehaviourWorkState->targetX, (f32)gBehaviourWorkState->targetZ, 0, 0.0f);
        break;
    case 0x37:
        gCurrentActor->sub4->boneRotations->rotZ -= gBehaviourWorkState->timer;
        if (gBehaviourWorkState->timer != 0) {
            gBehaviourWorkState->timer -= 0x32;
        }
        switch (gCurrentActor->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
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
        behaviourUpdateContactAndState(0x322);
        break;
    }
    if (gCurrentActor->speedXZ != 0.0f) {
        if (gCurrentActor->soundSlots[1] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x10A, 0, 1, 1, 0xFF, 1.0f, 0);
        } else {
            f64 t = ((f64)gCurrentActor->speedXZ * 0.6) / 40.0;
            u8 idx = D_80770629[gCurrentActor->soundSlots[1] * 2];

            D_80770B68[idx] = (t < 0.0 ? 0.0 : t) + 0.4;
            D_80770BC0[idx] = 1.0f;
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

extern void *D_8074E880[];

void actorSpawnRandomParticleNearActor(u8 particleType, s8 yOffset) {
    s32 pad;
    s32 randC;
    s32 randB;
    s32 randA;

    switch (particleType) {
        case 0:
            effectSetCallback(effectPuffRiseUpdate);
            break;
        case 1:
            effectSetSpeed(-0x258);
            effectSetCallback(func_80717D4C);
            break;
    }
    effectSetDepth(1);
    randA = randomNonNegative();
    randB = randomNonNegative();
    randC = randomNonNegative();
    effectCreateAtPosition(D_8074E880[((randA >> 15) % 1000) % 3], (f32)(((randB >> 15) % 256) * 0.001953125 + 0.5), (f32)((randC >> 15) % 6) + (gCurrentActor->x - 3.0f), gCurrentActor->y + (f32)yOffset, (f32)((randomNonNegative() >> 15) % 6) + (gCurrentActor->z - 3.0f));
}

extern u8 D_80750628[];

s32 actorBuildNodeAlignedMatrix(u8 nodeLookupIdx, u8 yOffset, f32 x, f32 y, f32 z) {
    f32 spA[4][4];
    f32 spB[4][4];
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    u8 node;

    node = D_80750628[nodeLookupIdx];
    if (node) {
        f32 ang;

        actorGetNodePos(D_807FDCA0->occupant, node, &nodeX, &nodeY, &nodeZ);
        mathNudgeCoords(x, z, &nodeX, &nodeZ);
        ang = mathAtan2(nodeX - x, nodeZ - z);
        guTranslateF(spA, 0.0f, -yOffset, 0.0f);
        matrixMakeRotationY(spB, (gCurrentActor->yaw * 0x168) / 4096);
        guMtxCatF(spA, spB, spA);
        matrixMakeRotationX(spB, -90.0f);
        guMtxCatF(spA, spB, spA);
        guAlignF(spB, (ang * 57.295776f) + 180.0f, nodeX - x, nodeY - y, nodeZ - z);
        guMtxCatF(spA, spB, spA);
        guTranslateF(spB, 0.0f, yOffset, 0.0f);
        guMtxCatF(spA, spB, spA);
        guScaleF(spB, gCurrentActor->sub4->scaleX, gCurrentActor->sub4->scaleY, gCurrentActor->sub4->scaleZ);
        guMtxCatF(spA, spB, spA);
        guTranslateF(spB, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        guMtxCatF(spA, spB, gCurrentActor->modelMtx);
        return 1;
    }
    return 0;
}


void behaviourArmadilloInitRollState(void) {
    gCurrentActor->collisionFlags = 2;
    gCurrentActor->state = 0x23;
    gCurrentActor->unk155 = 0;
    gCurrentActor->health = 1;
    gCurrentActor->interactionType = 1;
    gBehaviourWorkState->unk4 = gPrimaryPlayerActor;
    actorScriptStart(gCurrentActor, gBehaviourAnimState->animId2);
    gCurrentActor->yaw = ((randomNonNegative() >> 15) % 1024) + gPrimaryPlayerActor->yaw - 0x200;
    gCurrentActor->speedXZ = ((randomNonNegative() >> 15) % 100) + 0x32;
    gCurrentActor->speedY = ((randomNonNegative() >> 15) % 150) + 0x64;
}

extern PlayerStruct *gPlayerSlots;

extern u8 D_8071FB34[];

s32 behaviourArmadilloAimAndShoot(u8 action, s16 animId) {
    s16 *p;
    Actor *tgt;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    u8 node;
    s32 anim;

    p = BDEE0AA->unk178;
    tgt = D_807FDCA0->occupant;
    if (tgt != NULL && tgt->state == 0x23 && D_807FDCA0->unk20 < 10) {
        if (gCurrentActor->state != 0x15 && gCurrentActor->state != 0x17) {
            gCurrentActor->collisionFlags = 0x80;
            gCurrentActor->state = 0x15;
            gCurrentActor->unk155 = 0;
            actorScriptStart(gCurrentActor, 0);
            gCurrentActor->interactionType = 2;
            p[3] = gCurrentActor->x;
            p[4] = gCurrentActor->z;
        }
    }
    if (gCurrentActor->state == 0x15 && (tgt == NULL || tgt->state != 0x23)) {
        behaviourArmadilloInitRollState();
    }
    if (gCurrentActor->state == 0x15) {
        node = gBehaviourExtraState->unkA;
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
            gCurrentActor->movePitch = gCurrentActor->movePitch - 1;
        }
        if (tgt->unk155 != 0) {
            if (tgt->unk155 == 1 && gActorGlobalState.bossFightPhase == 2 && actorIsTargetWithinAngleDeg(tgt, gPrimaryPlayerActor, 0x1F40) != 0) {
                if (gPlayerSlots->unk2C0 == 1) {
                    playerStateQueueCallback(0x32, gCurrentActor, 0);
                } else {
                    if (((randomNonNegative() >> 15) % 1000) >= 0x1F5) {
                        anim = 0x21F;
                    } else {
                        anim = 0x21E;
                    }
                    actorScriptStart(tgt, anim);
                    tgt->unk155 = 2;
                }
            } else if (gActorGlobalState.bossFightPhase == 4) {
                gBehaviourWorkState->unk16 = gBehaviourTargetActor->sub4->model->animId;
                gCurrentActor->flags |= 0x20000000;
                if (gCurrentActor->movePitch == 0) {
                    gCurrentActor->movePitch = 0x28;
                    effectCreateAtPosition(D_8071FB34, 2.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                    sfxPlayOnFreeSlot(0x1CA, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    actorScriptStart(tgt, 0x220);
                    tgt->unk155 = 2;
                    tgt->health = tgt->health - 1;
                    if (tgt->health == 0) {
                        tgt->state = 0x37;
                        tgt->unk155 = 0;
                    }
                }
            }
        }
        D_807FDCA0->unk20 = D_807FDCA0->unk20 + 1;
        actorGetNodePos(tgt, node, &nodeX, &nodeY, &nodeZ);
        if (gBehaviourWorkState->flags & 0x80) {
            if (!(gBehaviourWorkState->unk1C & 0x80)) {
                gCurrentActor->speedY = 300.0f;
            }
            if (gCurrentActor->speedY > 0.0f) {
                return 0;
            }
            gCurrentActor->unk144 = 0x24;
            if (animId != 0) {
                controllerAnimSetStateIfChanged(gCurrentActor, animId, 0.0f, 4.0f);
            }
            p[0] = (-p[0]) * 0.1 + p[0];
            p[1] = (-p[1]) * 0.1 + p[1];
            if (node < 0xB) {
                gCurrentActor->yaw = tgt->yaw;
            }
            gCurrentActor->x = nodeX;
            gCurrentActor->z = nodeZ;
            gCurrentActor->y = nodeY;
            if (actorBuildNodeAlignedMatrix(node, action, nodeX, nodeY, nodeZ) != 0) {
                return 1;
            }
        }
    }
    return 0;
}


void behaviourArmadilloMoveTowardTarget(f32 speedMultiplier) {
    s16 *p;
    f32 x;
    f32 z;
    u8 sel;
    s32 flags;

    sel = gCurrentActor->state;
    p = BDEE0AA->unk178;
    x = gBehaviourWorkState->targetX;
    z = gBehaviourWorkState->targetZ;
    switch (sel) {
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
            if (!(actorMoveWithinZone(sel, x, z, flags, 0.0f) & 1) && gCurrentActor->hasArcBounds == 0) {
                *p = *p + speedMultiplier;
            }
            break;
        case 0x37:
            switch (gCurrentActor->unk155) {
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
    u8 arg = gCurrentActor->state;

    switch (arg) {
        case 0x15:
        case 0x37:
        case 0x40:
            break;
        case 2:
        case 3:
            patrolPathStep(arg, 0);
        default:
            enemyAggroStateUpdate(0x2710, 0, 0);
    }
}

typedef struct BDEE0Sub178 {
    /* 0x0 */ s16 rollPhase;
    /* 0x2 */ s16 side;
    /* 0x4 */ u16 tilt;
} BDEE0Sub178;

// Actor view whose unk178 is a BDEE0Sub178 (func_806BA93C, behaviourFairyWanderUpdate).
typedef struct BDEE0Actor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BDEE0Sub178 *unk178;
} BDEE0Actor;
#define BDEE0A ((BDEE0Actor *)gCurrentActor)

f32 cosApprox(f32);

void func_806BA93C(sideOffset, rollAmount, pivotZ)
u8 sideOffset;
u8 rollAmount;
u8 pivotZ;
{
    BDEE0Sub178 *rock;
    f32 modelMtx[4][4];
    f32 rotMtx[4][4];
    s16 sgn;
    s32 dir;
    f32 stepDist;
    s16 yawOffset;

    rock = BDEE0A->unk178;
    if (gBehaviourExtraState->unkA && behaviourArmadilloAimAndShoot(0x64, 0)) {
        return;
    }
    if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) && gCurrentActor->state != 0x37) {
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
        if (gCurrentActor->unk155 == 0) {
            gBehaviourWorkState->timer += rock->tilt;
            if (gBehaviourWorkState->timer == 0x196 || gBehaviourWorkState->timer == 0x244 || gBehaviourWorkState->timer == 0x307 || gBehaviourWorkState->timer == 0x3B1 || gBehaviourWorkState->timer == 0x45C || gBehaviourWorkState->timer == 0x508) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x17D, 0x9B, (s16)(rock->tilt + 0x5A), 0);
            }
            rock->tilt--;
            if (rock->tilt < 2) {
                gCurrentActor->unk155++;
                dir = rock->tilt; // FAKE: dead store (dir is reassigned before use) steers regalloc
                rock->tilt = 0;
                gBehaviourWorkState->scale = 0.0f;
            }
        }
        break;
    }
    if (rock->rollPhase >= 0x801) {
        stepDist = sqrtf((1.0 - cosApprox(0.7853982f)) * (2 * (f32)(sideOffset * 2) * (f32)(sideOffset * 2)));
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
    matrixMakeRotationZ(rotMtx, mathSinF(rock->rollPhase) * (f32)(sgn * rollAmount));
    guMtxCatF(modelMtx, rotMtx, modelMtx);
    if (gCurrentActor->state == 0x37) {
        matrixMakeRotationY(rotMtx, (f32)(sgn * gBehaviourWorkState->timer));
    } else {
        matrixMakeRotationY(rotMtx, mathSinF(rock->rollPhase - 0x400) * (f32)(-sgn * 0x2D));
    }
    guMtxCatF(modelMtx, rotMtx, modelMtx);
    if (gCurrentActor->state == 0x37) {
        switch (gCurrentActor->unk155) {
        case 1:
            gBehaviourWorkState->timer = mathAngleEaseToward((gBehaviourWorkState->timer << 12) / 0x168, 0, 3.0f) * 0x168 / 4096;
            rock->rollPhase = rock->rollPhase + (-rock->rollPhase) * 0.3;
            guTranslateF(rotMtx, 0.0f, 0.0f, (f32)-pivotZ);
            guMtxCatF(modelMtx, rotMtx, modelMtx);
            matrixMakeRotationX(rotMtx, (f32)rock->tilt);
            guMtxCatF(modelMtx, rotMtx, modelMtx);
            guTranslateF(rotMtx, 0.0f, 0.0f, (f32)pivotZ);
            gBehaviourWorkState->scale += 2.0f;
            rock->tilt = (f32)rock->tilt + gBehaviourWorkState->scale;
            if (rock->tilt >= 0x5B) {
                rock->tilt = 0x5A;
                if (gBehaviourWorkState->scale < 3.0f) {
                    gCurrentActor->unk155++;
                } else {
                    sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x1B1, (u32)(gBehaviourWorkState->scale * 255.0f / 20.0f), (s32)(gBehaviourWorkState->scale + 100.0f), 0, 0x3C, 0.3f, 0);
                    gBehaviourWorkState->scale = -(gBehaviourWorkState->scale * 0.5);
                }
            }
            break;
        case 2:
            guTranslateF(rotMtx, 0.0f, 0.0f, (f32)-pivotZ);
            guMtxCatF(modelMtx, rotMtx, modelMtx);
            matrixMakeRotationX(rotMtx, 90.0f);
            guMtxCatF(modelMtx, rotMtx, modelMtx);
            guTranslateF(rotMtx, 0.0f, 0.0f, (f32)pivotZ);
            break;
        }
        guMtxCatF(modelMtx, rotMtx, modelMtx);
    }
    guTranslateF(rotMtx, (f32)(-sgn * sideOffset), 0.0f, 0.0f);
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
    if (gBehaviourWorkState->unk2E != 0) {
        gBehaviourWorkState->unk2E--;
        gCurrentActor->hasArcBounds = 0;
        if (gBehaviourWorkState->unk2E == 0 && gBehaviourTargetActor == gPrimaryPlayerActor) {
            gCurrentActor->unk144 = 0x24;
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
            gCurrentActor->unk155 = 0;
        case 0x23:
            switch (gCurrentActor->unk155) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x202, 0.0f);
                    break;
                default:
                    gCurrentActor->unk155 = 1;
                    goto join;
                join:
                case 1:
                    if (gCurrentActor->sub4->animId != 0x21C) {
                        actorScriptStart(gCurrentActor, 0x21C);
                    }
                    actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
                    break;
                case 2:
                    break;
            }
            break;
        case 0x37:
            playerSetLargeModeScale(0.3f);
            gCurrentActor->state = 0x40;
            break;
    }
    D_807FDCA0->unk20 = 0;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct BDEE0Sub174 {
    /* 0x00 */ struct BDEE0Sub174Hdr *unk0;
    /* 0x04 */ Actor *occupant;
    /* 0x08 */ u8 pad8[0x26];
    /* 0x2E */ s16 spawnDelay;
} BDEE0Sub174;

typedef struct BDEE0Sub174Hdr {
    /* 0x00 */ u8 pad0[0x46];
    /* 0x46 */ u16 flags;
} BDEE0Sub174Hdr;

extern Actor *gSpawnedActor;


s32 actorSpawnJitteredChild(u8 actorType, s16 animId, s16 subId, Actor *occupant) {
    BDEE0Sub174 *v;
    s32 r3;
    s32 r2;
    s32 r1;

    if (gBehaviourWorkState->timer != 0) {
        actorSpawnRandomParticleNearActor(0, 0xA);
        gBehaviourWorkState->timer--;
        return 0;
    }
    r1 = randomNonNegative();
    r2 = randomNonNegative();
    r3 = randomNonNegative();
    if (spawnNodeSpawnById(actorType,
                      (s16)((f32)((r1 >> 15) % 10) + (gCurrentActor->x - 5.0f)),
                      (s16)(gCurrentActor->y + 5.0f),
                      (s16)((f32)((r2 >> 15) % 10) + (gCurrentActor->z - 5.0f)),
                      ((r3 >> 15) % 1024) + gCurrentActor->yaw - 0x200,
                      animId, subId) != 0) {
        gSpawnedActor->state = 0x17;
        gSpawnedActor->unk155 = 0;
        v = gSpawnedActor->customState;
        v->spawnDelay = 0x1E;
        if (occupant != NULL) {
            v->unk0->flags &= ~8;
            v->occupant = occupant;
        }
        gSpawnedActor->unk144 = 1;
        gSpawnedActor->drawDistance = 0x3E8;
        return 1;
    }
    return 0;
}


void behaviourFairyPlaySound(void) {
    sfxPlayActorSound(gCurrentActor, 0x11F, 0, 0, 0, 0xFF, 1.0f, 0);
    sfxAllocateChannel(0x3B, 1.0f);
}

typedef struct BDEE0Tbl {
    u8 b[11];
} BDEE0Tbl;

extern PlayerState *gActivePlayerState;
extern s32 gGlobalCutsceneFlags;
extern Actor *gCamActor;
extern BDEE0Tbl D_80750638;

void behaviourFairyWanderUpdate(void) {
    s16 i;
    s16 x;
    s16 y;
    BDEE0Tbl tbl;
    u8 t;
    s32 w;

    x = (randomNonNegative() >> 15) % 100 + 0x64;
    y = (randomNonNegative() >> 15) % 250 + 0xC8;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->cullMarginX = 0x3C;
        gCurrentActor->cullMarginY = 0x3C;
        gCurrentActor->drawDistance = 0x3E8;
        gCurrentActor->state = 0;
        gCurrentActor->unk155 = 0;
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
        switch (gCurrentActor->unk155) {
        case 0:
            if (gBehaviourWorkState->timer-- < 0x3C) {
                gCurrentActor->flags |= 0x400;
                actorScriptStart(gCurrentActor, 0x3DD);
                gCurrentActor->unk155++;
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
        if (actorSpawnJitteredChild(0x2A, x, y, NULL) != 0) {
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
        actorSpawnJitteredChild(0x28, x, y, NULL);
        if (actorSpawnJitteredChild(0x29, (s16)(x + 0x28), (s16)(y + 0x50), NULL) != 0) {
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
        actorSpawnJitteredChild(0x2B, x, y, NULL);
        if (actorSpawnJitteredChild(0x2C, (s16)(x + 0x28), (s16)(y + 0x50), NULL) != 0) {
            gCurrentActor->state++;
        }
        break;
    case 7:
        if (spawnNodeHasActor(0x2B) == 0 && spawnNodeHasActor(0x2C) == 0) {
            csSendActorMessagePayload(0x11, 1);
            spawnNodeSpawnById(0x2D, mathSinF(gCurrentActor->yaw) * 80.0f + gCurrentActor->x, gCurrentActor->y, mathCosF(gCurrentActor->yaw) * 80.0f + gCurrentActor->z, gCurrentActor->yaw, 0, 0);
            D_807FDCA0->occupant = gSpawnedActor;
            camStartPath(gCurrentActor, 0x1F, 1);
            gCurrentActor->state++;
            gBehaviourWorkState->timer = 0x1E;
            gCurrentActor->unk155 = 0xA;
        }
        break;
    case 8:
        if (gBehaviourWorkState->timer != 0) {
            gBehaviourWorkState->timer--;
        } else {
            tbl = D_80750638;
            t = 0xA - gCurrentActor->unk155;
            if (gCurrentActor->unk155 == 0xA) {
                behaviourFairyPlaySound();
            }
            if (gCurrentActor->unk155) {
                actorSpawnJitteredChild((u8)(tbl.b[gCurrentActor->unk155--] + 0x22), (s16)(t * 8 + 0x64), (s16)(t * 20 + 0xFA), D_807FDCA0->occupant);
            } else {
                gCurrentActor->flags &= 0xFFFF7FFF;
                gCurrentActor->unk144 = 1;
                gCurrentActor->state++;
                camSetTarget(gCamActor, gCurrentActor, 4, 0x1129, 0x264, 0, 0, 0xAF, 0, 0, 1.0f);
                camSetTargetFocusActor(gCamActor, gPrimaryPlayerActor);
            }
            gBehaviourWorkState->timer = 0xF;
        }
        break;
    case 9:
        w = gCurrentActor->alpha - 0xA;
        if (w < 0) {
            gCurrentActor->alpha = 0;
        } else {
            gCurrentActor->alpha = w;
        }
        if (spawnNodeHasActor(0x2D) == 0) {
            csSendActorMessagePayload(0x11, 0xFF);
            camReturnToFollow(gCamActor, gPrimaryPlayerActor);
            func_80726EE0(0);
            gGlobalCutsceneFlags &= ~1;
            if (gPlayerSlots->unk2C0 != 1) {
                playerSetSizeMode(gPrimaryPlayerActor, 1);
                gActivePlayerState->scaleChangeRate = 0.05f;
            }
            gCurrentActor->state++;
            sfxStopChannel(0x68, 0);
            csModelStateSetFirstByte(0x7C, 0xA);
            gPrimaryPlayerActor->drawDistance = 0x1F4;
            gPrimaryPlayerActor->flags &= ~0x400;
            gCurrentActor->unk144 = 0x24;
            camStartPath(gCurrentActor, 0x1F, 5);
        }
        break;
    case 10:
        w = gCurrentActor->alpha + 0xA;
        if (w >= 0x100) {
            gCurrentActor->alpha = 0xFF;
        } else {
            gCurrentActor->alpha = w;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void behaviourFairyIdle1(void) {
    behaviourFairyUpdate();
    if (gBehaviourExtraState->unkA == 0 || behaviourArmadilloAimAndShoot(0, 0x446) == 0) {
        actorPatrolFollowerUpdate(0x2ED, 1, 0);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}

void behaviourFairyIdle2(void) {
    behaviourFairyUpdate();
    if (gBehaviourExtraState->unkA == 0 || behaviourArmadilloAimAndShoot(0x32, 0x44E) == 0) {
        actorPatrolFollowerUpdate(0x2EC, 1, 0);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}

void behaviourFairyIdle3(void) {
    behaviourFairyUpdate();
    if (gBehaviourExtraState->unkA == 0 || behaviourArmadilloAimAndShoot(0x14, 0x44A) == 0) {
        actorPatrolFollowerUpdate(0x2EE, 1, 0);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}


void behaviourFairyIdle4(void) {
    behaviourFairyUpdate();
    func_806BA93C(0x24, 0x14, 0x1E);
}
