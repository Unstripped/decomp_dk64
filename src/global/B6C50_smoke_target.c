#include "common.h"
#include "actor.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/12E800_behaviour.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2C910.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/80150_barrels.h"
#include "proto/global/89250_effect_spawn.h"
#include "proto/global/A7710_countdown_timer.h"
#include "proto/global/B6C50_smoke_target.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern EffectGridAsset gEffectSpriteFuseSpark;


void timedSmokeTargetHostUpdate(void) {
    u8 tint;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0xA0;
        gCurrentActor->flags |= 0x400;
        gCurrentActor->state = 0;
        gCurrentActor->subState = 0;
        actorSpawn(0x73, 0x7D);
        gBehaviourWorkState->targetActor = gSpawnedActor;
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.3f);
        gSpawnedActor->x = gCurrentActor->x + mathSinF(gCurrentActor->yaw) * 14.0f;
        gSpawnedActor->z = gCurrentActor->z + mathCosF(gCurrentActor->yaw) * 14.0f;
        actorClearNodeFlag(gSpawnedActor, 3);
        actorClearNodeFlag(gSpawnedActor, 1);
        actorUpdateFloorContactAndTilt(gSpawnedActor, 14.0f);
        gCurrentActor->flags2 &= ~0x40;
        gSpawnedActor->flags |= 0x1000;
        effectSetDepth(1);
        effectSetDuration(-1);
        effectSetMaxDistance(gSpawnedActor->drawDistance * 0.75);
        effectCreateAtActorBone(&gEffectSpriteFuseSpark, 0.28f, gSpawnedActor, 1, 2);
        actorScriptStart(gCurrentActor, 0x300);
        sfxPlayActorSound(gCurrentActor, 0x135, 0x64, 0, 0, 0x78, 1.0f, 0);
    }
    if (gActorGlobalState.damaged != 0 || gActorGlobalState.bossFightPhase == 9) {
        gCurrentActor->parentActor->state = 0;
        camStartPath(gCurrentActor, 6, 5);
        gCurrentActor->collisionMode = 1;
        gCurrentActor->state = 0x37;
        gCurrentActor->subState = 0;
    } else if (gActorGlobalState.bossFightPhase == 4) {
        gCurrentActor->subState++;
    }
    switch (gCurrentActor->state) {
        case 0:
            if (currentActorTestClearFlag() != 0) {
                hudSpawnCountdownTimer(0xDC, 0x2A, 0x1E);
                hudCountdownTimerStart(gCurrentActor->parentActor);
                gCurrentActor->state = 7;
                gCurrentActor->subState = 0;
            }
            break;
        case 0x27:
            break;
        case 0x37:
            switch (gCurrentActor->subState) {
                case 0x3C:
                    gCurrentActor->flags &= ~4;
                    gCurrentActor->flags2 &= ~0x40;
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xED, 0xFF, 0x7F, 0x14);
                    tagBarrelSpawnSmokeAndPuffs(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, gCurrentActor->sub4->scaleY * 2 / 0.15, 0, 1);
                    actorDespawn(gBehaviourTargetActor);
                    gCurrentActor->subState++;
                    break;
                case 0x64:
                    actorDespawn(gCurrentActor->parentActor);
                    gCurrentActor->state = 0x40;
                    sfxAllocateChannel(0x2A, 1.0f);
                    // fall through
                default:
                    gCurrentActor->subState++;
                    break;
            }
            break;
        default:
            if (gCurrentActor->parentActor != NULL && gCurrentActor->parentActor->state == 5) {
                gCurrentActor->callbackMask &= ~0x8000;
                sfxStopSlotSound(gCurrentActor, 0);
                spawnNodesSetRespawnHold(0);
                effectFreeByResource(gBehaviourTargetActor);
                actorDespawn(gCurrentActor->parentActor);
                gCurrentActor->state = 0x27;
                gCurrentActor->subState = 0;
                camStartPath(gCurrentActor, 3, 1);
                actorScriptStart(gCurrentActor, 0x307);
                gCurrentActor->yaw += 0x800;
                gCurrentActor->z += 5.0f;
            }
            if (gCurrentActor->subState != 0 && actorTableContains(gBehaviourTargetActor) != 0 && gFrameCounter % 7 == 0) {
                tint = (6 - gCurrentActor->subState) * 30;
                effectSetFrameDelay(3);
                effectSetColor(tint, tint, tint, gCurrentActor->alpha);
                effectSpawnBoneDefault(gBehaviourTargetActor, 1, 1.0f, 0.0f, 0.0f, 0.0f, -0x96);
            }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern Actor *gPrimaryPlayerActor;
extern s32 gEffectSpriteExplosion;

f32 sqrtf(f32);

void smokeTargetChaserUpdate(void) {
    Actor *found;
    f32 dx;
    f32 dz;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        found = actorFindByType(0x110);
        if (found != NULL) {
            gBehaviourWorkState->targetActor = found;
        }
        gBehaviourExtraState->actorState = 0x23;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x599, 0.0f, 0.0f);
        gCurrentActor->flags2 &= ~0x40;
        sfxPlayActorSound(gCurrentActor, 0x139, 0x78, 0, 1, 0x3C, 0.56f, 0);
        gCurrentActor->flags |= 0x400;
    }
    if (gFrameCounter % 10 == 0) {
        effectSetDepth(1);
        effectCreateAtActorBone(&gEffectSpriteExplosion, gCurrentActor->sub4->scaleY * 6.66666667 * 0.9, gCurrentActor, 1, 2);
    }
    if (actorTableContains(gBehaviourTargetActor) == 0) {
        gBehaviourWorkState->targetActor = gPrimaryPlayerActor;
        gBehaviourTargetActor = gBehaviourWorkState->targetActor;
    }
    if (gActorGlobalState.damaged != 0 || gActorGlobalState.bossFightPhase == 9) {
        gCurrentActor->collisionMode = 1;
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
