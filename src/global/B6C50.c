#include "common.h"
#include "actor.h"
#include "proto/global/119370.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/80150.h"
#include "proto/global/89250.h"
#include "proto/global/A7710.h"
#include "proto/global/B6C50.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern s32 D_8072030C;
extern u32 gFrameCounter;

f32 mathCosF(s16);
f32 mathSinF(s16);

void func_806B1F50(void) {
    u8 tint;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0xA0;
        gCurrentActor->flags |= 0x400;
        gCurrentActor->state = 0;
        gCurrentActor->unk155 = 0;
        actorSpawn(0x73, 0x7D);
        gBehaviourWorkState->unk4 = gSpawnedActor;
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.3f);
        gSpawnedActor->x = mathSinF(gCurrentActor->yaw) * 14.0f + gCurrentActor->x;
        gSpawnedActor->z = mathCosF(gCurrentActor->yaw) * 14.0f + gCurrentActor->z;
        actorClearNodeFlag(gSpawnedActor, 3);
        actorClearNodeFlag(gSpawnedActor, 1);
        actorUpdateFloorContactAndTilt(gSpawnedActor, 14.0f);
        gCurrentActor->flags2 &= 0xFFBF;
        gSpawnedActor->flags |= 0x1000;
        effectSetDepth(1);
        effectSetDuration(-1);
        effectSetMaxDistance(gSpawnedActor->drawDistance * 0.75);
        effectCreateAtActorBone(&D_8072030C, 0.28f, gSpawnedActor, 1, 2);
        actorScriptStart(gCurrentActor, 0x300);
        sfxPlayActorSound(gCurrentActor, 0x135, 0x64, 0, 0, 0x78, 1.0f, 0);
    }
    if (gActorGlobalState.unk15 != 0 || gActorGlobalState.bossFightPhase == 9) {
        gCurrentActor->parentActor->state = 0;
        camStartPath(gCurrentActor, 6, 5);
        gCurrentActor->unk144 = 1;
        gCurrentActor->state = 0x37;
        gCurrentActor->unk155 = 0;
    } else if (gActorGlobalState.bossFightPhase == 4) {
        gCurrentActor->unk155++;
    }
    switch (gCurrentActor->state) {
        case 0x27:
            break;
        case 0:
            if (currentActorTestClearFlag() != 0) {
                hudSpawnCountdownTimer(0xDC, 0x2A, 0x1E);
                actorSetStateTwo(gCurrentActor->parentActor);
                gCurrentActor->state = 7;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 0x37:
            switch (gCurrentActor->unk155) {
                case 0x3C:
                    gCurrentActor->flags &= ~4;
                    gCurrentActor->flags2 &= 0xFFBF;
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xED, 0xFF, 0x7F, 0x14);
                    tagBarrelSpawnSmokeAndPuffs(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, gCurrentActor->sub4->scaleY * 2 / 0.15, 0, 1);
                    actorDespawn(gBehaviourTargetActor);
                    gCurrentActor->unk155++;
                    break;
                case 0x64:
                    actorDespawn(gCurrentActor->parentActor);
                    gCurrentActor->state = 0x40;
                    sfxAllocateChannel(0x2A, 1.0f);
                default:
                    gCurrentActor->unk155++;
                    break;
            }
            break;
        default:
            if (gCurrentActor->parentActor != NULL && gCurrentActor->parentActor->state == 5) {
                gCurrentActor->callbackMask &= ~0x8000;
                sfxStopSlotSound(gCurrentActor, 0);
                func_80726EE0(0);
                effectFreeByResource(gBehaviourTargetActor);
                actorDespawn(gCurrentActor->parentActor);
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155 = 0;
                camStartPath(gCurrentActor, 3, 1);
                actorScriptStart(gCurrentActor, 0x307);
                gCurrentActor->yaw += 0x800;
                gCurrentActor->z += 5.0f;
            }
            if (gCurrentActor->unk155 != 0 && actorTableContains(gBehaviourTargetActor) != 0 && gFrameCounter % 7 == 0) {
                tint = -gCurrentActor->unk155 * 0x1E + 0xB4;
                effectSetMode(3);
                effectSetColor(tint, tint, tint, gCurrentActor->alpha);
                effectSpawnBoneDefault(gBehaviourTargetActor, 1, 1.0f, 0.0f, 0.0f, 0.0f, -0x96);
                break;
            }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern Actor *gPrimaryPlayerActor;
extern s32 D_80720340;

f32 sqrtf(f32);

void func_806B24B8(void) {
    Actor *found;
    f32 dx;
    f32 dz;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        found = actorFindByType(0x110);
        if (found != NULL) {
            gBehaviourWorkState->unk4 = found;
        }
        gBehaviourExtraState->actorState = 0x23;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x599, 0.0f, 0.0f);
        gCurrentActor->flags2 &= 0xFFBF;
        sfxPlayActorSound(gCurrentActor, 0x139, 0x78, 0, 1, 0x3C, 0.56f, 0);
        gCurrentActor->flags |= 0x400;
    }
    if (gFrameCounter % 10 == 0) {
        effectSetDepth(1);
        effectCreateAtActorBone(&D_80720340, gCurrentActor->sub4->scaleY * 6.66666667 * 0.9, gCurrentActor, 1, 2);
    }
    if (actorTableContains(gBehaviourTargetActor) == 0) {
        gBehaviourWorkState->unk4 = gPrimaryPlayerActor;
        gBehaviourTargetActor = gBehaviourWorkState->unk4;
    }
    if (gActorGlobalState.unk15 != 0 || gActorGlobalState.bossFightPhase == 9) {
        gCurrentActor->unk144 = 1;
        gCurrentActor->state = 0x40;
        tagBarrelSpawnSmokeAndPuffs(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, gCurrentActor->sub4->scaleY / 0.15, 0, 1);
    }
    if (gCurrentActor->state == 0x23) {
        if (gCurrentActor->movePitch == 0) {
            dx = gCurrentActor->x - gBehaviourTargetActor->x;
            dz = gCurrentActor->z - gBehaviourTargetActor->z;
            if (sqrtf(dx * dx + dz * dz) < 30.0f) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x2CA, 0xFF, 0x7F, 0x14);
                gCurrentActor->movePitch = 1;
            }
        }
        actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
    } else {
        behaviourUpdateContactAndState(0x1F8);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
