#include "common.h"
#include "actor.h"
#define PROTO_SKIP_actorTrackBoneTowardTarget // FAKE: callee prototype steer (owner 1295B0 takes one u8 and never reads a1; the extra `sel` argument keeps sel in a1 across the call, see func_806B13B4)
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/89250.h"
#include "proto/global/8CA50.h"
#include "proto/global/AA960.h"
#include "proto/global/B5EC0.h"
#include "proto/global/CEAE0.h"

extern Actor *gCurrentActor;
extern s32 sEffectSparkConfig;

void actorSpawnGroundEffectAtNode(u8 nodeIndex) {
    f32 x;
    f32 y;
    f32 z;

    actorGetNodePos(gCurrentActor, nodeIndex, &x, &y, &z);
    effectSpawnScatterRandom(&sEffectSparkConfig, 0, 1.0f, 3, 5, 0x28, x, gCurrentActor->floorY, z);
    actorSpawnEffectChild(x, gCurrentActor->floorY, z, 0.05f, 0.04f, gCurrentActor, 0);
}

void func_806B1290(void) {
    if (gBehaviourWorkState->stepCount >= 0x65
        && (((gBehaviourWorkState->flags & 0x80) && (randomNonNegative() >> 15) % 1000 >= 0x3D5)
            || ((randomNonNegative() >> 15) % 1000 >= 0x3DF && (gCurrentActor->flags & 0x100)))) {
        gCurrentActor->state = 0x28;
        gCurrentActor->unk155 = 0;
    }
}

void func_806B1348(void) {
    if (gBehaviourWorkState->stepCount >= 0x65 && gActorGlobalState.bossFightPhase == 2 && behaviourIsTargetWithinAngle(0x2710) != 0) {
        gCurrentActor->state = 0x27;
        gCurrentActor->unk155 = 0;
    }
}

extern s32 gCurrentMap;

void actorTrackBoneTowardTarget();

void func_806B13B4(u8 spawnSfxNodes) {
    s32 sel;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        if (gCurrentMap == 0x43) {
            gBehaviourExtraState->unkD = 0x82;
            gBehaviourAnimState->flags |= 0x40;
        }
        behaviourSetAnimIds(0x205, 0x203, 0x204);
        func_80724CA4(2, 1);
    }
    sel = gCurrentActor->state;
    if (sel == 0x27) {
        gCurrentActor->interactionType = 2;
        sel = gCurrentActor->state;
    } else if (sel != 0x32) {
        gCurrentActor->interactionType = 1;
        sel = gCurrentActor->state;
    }
    if (sel != 0x32 || gActorGlobalState.unk15 != 0) {
        if ((gActorGlobalState.bossFightPhase == 9 || gActorGlobalState.unk15 != 0) && sel != 0x37) {
            if (gCurrentActor->health < -1) {
                behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x20C);
                gCurrentActor->speedY = 250.0f;
            } else {
                behaviourCalculateDamageForce(gActorGlobalState.targetActor, 0x20B);
                gCurrentActor->speedY = 200.0f;
            }
            gBehaviourWorkState->unk35 = 2;
            gCurrentActor->callbackMask &= 0xFFFF7FFF;
            sel = gCurrentActor->state;
        } else if (gActorGlobalState.bossFightPhase == 4) {
            behaviourSpawnExplosionAndSound(0x209, 0x31, gActorGlobalState.targetActor);
            sel = gCurrentActor->state;
        } else if (gActorGlobalState.bossFightPhase == 5) {
            behaviourSpawnExplosionAndSound(0x20A, 0x32, gActorGlobalState.targetActor);
            gCurrentActor->speedY = 220.0f;
            gCurrentActor->interactionType = 8;
            sel = gCurrentActor->state;
        }
    }
    sel = gCurrentActor->state;
    switch (sel) {
    case 0x31:
        if (gCurrentActor->unk155 != 0 || gCurrentActor->sub4->model->speed == 0.0f) {
            actorSetDefaultState(0x203);
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
            gCurrentActor->interactionType = 1;
            actorSetDefaultState(0x203);
            break;
        }
        break;
    case 0x28:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x20D);
            gCurrentActor->unk155 = 1;
            break;
        case 2:
            actorSpawnGroundEffectAtNode(1);
            actorSpawnGroundEffectAtNode(2);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1D5, 0xFF, 0x7F, 1);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x25A, 0xFF, 0x7F, 1);
            gCurrentActor->unk155 = 3;
            break;
        case 4:
            actorSetDefaultState(0x203);
            break;
        }
        break;
    case 0x11:
        actorTrackBoneTowardTarget(5);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            actorScriptStart(gCurrentActor, 0x205);
            gCurrentActor->unk155 += 1;
        case 1:
            actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
            if (gCurrentActor->speedXZ < 1.0f) {
                gCurrentActor->unk155 += 1;
            }
            break;
        case 2:
            behaviourUpdateShadowAlpha();
            if ((randomNonNegative() >> 15) % 1000 >= 0x3E4) {
                actorSetDefaultState(0x203);
            }
            break;
        }
        break;
    case 0x27:
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x200, 0.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            if ((randomNonNegative() >> 15) % 1000 >= 0x259) {
                actorScriptStart(gCurrentActor, 0x208);
                gCurrentActor->unk155 = 5;
            } else {
                actorScriptStart(gCurrentActor, 0x206);
                gCurrentActor->unk155 = 1;
            }
            break;
        case 1:
            if (gBehaviourWorkState->flags & 0x100) {
                actorClearNodeFlag(gCurrentActor, 2);
                actorClearNodeFlag(gCurrentActor, 3);
            }
            break;
        case 2:
            if (gBehaviourWorkState->flags & 0x100) {
                gBehaviourWorkState->flags &= 0xFEFF;
                actorScriptStart(gCurrentActor, 0x207);
                gCurrentActor->unk155 = 3;
            } else {
                actorSetDefaultState(0x203);
            }
            break;
        case 3:
            if (gBehaviourWorkState->flags & 0x100) {
                gBehaviourWorkState->flags &= 0xFEFF;
                actorScriptStart(gCurrentActor, 0x208);
                gCurrentActor->unk155 = 5;
            }
            break;
        case 4:
            actorSetDefaultState(0x203);
            break;
        case 5:
            gCurrentActor->interactionType = 4;
            break;
        }
        break;
    case 1:
        if (behaviourCheckRandomAnimTrigger() != 0) {
            gCurrentActor->state = 0x11;
            gCurrentActor->unk155 = 0;
        }
    case 0x10:
    case 0x23:
        if (camIsCutsceneActive() == 0) {
            func_806B1290();
            func_806B1348();
        }
        actorTrackBoneTowardTarget((u8)(gCurrentActor->state == 1 ? 2 : 0));
        actorMoveWithinZone(gCurrentActor->state, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
        break;
    case 2:
    case 3:
    case 7:
    case 0x35:
        actorTrackBoneTowardTarget((u8)(sel == 0x35 ? 2 : 3), sel);
        actorMoveWithinZone(gCurrentActor->state, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
        break;
    case 0x37:
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gCurrentActor->moveYaw, 7.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x200, 0.0f);
            break;
        case 1:
            if (spawnSfxNodes != 0) {
                sfxSpawnTableNodes(gCurrentActor);
            }
            gCurrentActor->unk155 += 1;
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
        behaviourUpdateContactAndState(0x203);
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
        enemyAggroStateUpdate(0x6400, 0x203, 0x204);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorSetAnimStartFrame(u8 frame) {
    animSetLoopLimit(gCurrentActor, 0, 1);
    animSetFinished(gCurrentActor, 0, 1);
    animSetFrameAndSubframe(gCurrentActor, 0, frame, 0.0f);
}

extern u8 gCurrentWorldId;
extern s32 D_80750600[];


void func_806B1DD4(u8 mode) {
    u8 flag;
    s32 worldIndex;

    if (!(gCurrentActor->flags & 0x10)) {
        flag = 0;
        worldIndex = mapGetWorldIndex(gCurrentWorldId);
        if (worldIndex != 9 && worldIndex != 0xA) {
            worldIndex = mapGetHubWorldIndex(gCurrentWorldId, 1);
            flag = flagGridSumRows(0x1D5, worldIndex, worldIndex, D_80750600[mode]) == 0;
        }
        actorSetAnimStartFrame(flag != 0 ? mode : 5);
        gCurrentActor->unk15F = flag;
    }
    func_806B13B4(gCurrentActor->unk15F);
}

void b5ec0SetMode4(void) {
    func_806B1DD4(4);
}

void b5ec0SetMode2(void) {
    func_806B1DD4(2);
}

void b5ec0SetMode3(void) {
    func_806B1DD4(3);
}

void b5ec0SetMode0(void) {
    func_806B1DD4(0);
}

void b5ec0SetMode1(void) {
    func_806B1DD4(1);
}
