#include "common.h"
#include "actor.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/12E800_behaviour.h"
#include "proto/global/166A0_random.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/42630_cutscene_interp.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/89250_effect_spawn.h"
#include "proto/global/A7710_countdown_timer.h"
#include "proto/global/CB230_spotlight_follower.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

typedef struct SpotlightActorState { // Actor 0x178 component of the spotlight actors (types 0xF0, 0xF9)
    /* 0x0 */ s16 brightness;
    /* 0x2 */ u8 unk2;
} SpotlightActorState;

typedef struct SpotlightActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ SpotlightActorState *light;
} SpotlightActor;

f32 sqrtf(f32);

void actorUpdateNearestSpotlight(void) {
    SpotlightActorState *light;
    s32 best;
    Actor *found;
    s16 i;
    Actor *actor;
    f32 lightTarget[3];
    f32 lightPos[3];
    f32 dx;
    f32 dy;
    f32 dz;
    s32 distSq;

    light = ((SpotlightActor *)gCurrentActor)->light;
    found = NULL;
    best = 999999;
    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (actor->actorType == 0xF0 || actor->actorType == 0xF9) {
            dx = actor->x - gPrimaryPlayerActor->x;
            dy = actor->y - gPrimaryPlayerActor->y;
            dz = actor->z - gPrimaryPlayerActor->z;
            distSq = dx * dx + dy * dy + dz * dz;
            if (distSq < best) {
                best = distSq;
                found = actor;
            }
        }
    }
    if (found != gCurrentActor) {
        gCurrentActor->state = 0x40;
        return;
    }
    switch (gCurrentActor->actorType) {
        case 0xF0:
            if (gCurrentActor->flags & 0x100) {
                actorGetNodePos(gCurrentActor, 1, lightPos, &lightPos[1], &lightPos[2]);
            } else {
                lightPos[0] = gCurrentActor->x;
                lightPos[1] = gCurrentActor->y;
                lightPos[2] = gCurrentActor->z;
            }
            dx = gCurrentActor->x - gPrimaryPlayerActor->x;
            dy = gCurrentActor->y - gPrimaryPlayerActor->y;
            dz = gCurrentActor->z - gPrimaryPlayerActor->z;
            if (dx * dx + dy * dy + dz * dz > 40000.0f && (gCurrentActor->flags & 0x100)) {
                actorGetNodePos(gCurrentActor, 2, lightTarget, &lightTarget[1], &lightTarget[2]);
            } else {
                lightTarget[0] = gPrimaryPlayerActor->x;
                lightTarget[1] = gPrimaryPlayerActor->y;
                lightTarget[2] = gPrimaryPlayerActor->z;
            }
            lightSetFovAngles(30.0f, 80.0f);
            break;
        case 0xF9:
            lightPos[0] = gCurrentActor->x;
            lightPos[1] = gCurrentActor->y;
            lightPos[2] = gCurrentActor->z;
            lightTarget[0] = mathSinF(gCurrentActor->yaw) * 40.0f + gCurrentActor->x;
            lightTarget[1] = gCurrentActor->y - 20.0f;
            lightTarget[2] = mathCosF(gCurrentActor->yaw) * 40.0f + gCurrentActor->z;
            lightSetFovAngles(20.0f, 40.0f);
            break;
    }
    light->brightness = mathSinF(gFrameCounter * 130) * 35.0 + 220.0;
    lightAdd(lightPos[0], lightPos[1], lightPos[2], lightTarget[0], lightTarget[1], lightTarget[2], 0.0f, 1, light->brightness, light->brightness, light->brightness);
}

void spotlightFollowerStep(s16 yOffset, s16 stopDist, u16 flags) {
    u16 dist;
    f32 dx;
    f32 dz;

    behaviourFrameBegin();
    dx = gCurrentActor->x - gBehaviourTargetActor->x;
    dz = gCurrentActor->z - gBehaviourTargetActor->z;
    dist = sqrtf(dx * dx + dz * dz);
    if (!(gCurrentActor->flags & 0x10)) {
        SpotlightActorState *light = ((SpotlightActor *)gCurrentActor)->light;
        gCurrentActor->renderFlags |= 4;
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        light->unk2 = 0;
        light->brightness = 0xFF;
        gBehaviourAnimState->minAnimSpeed = 1.0f;
        if (gCurrentActor->actorType == 0xF0) {
            sfxPlayActorSound(gCurrentActor, 0x132, 0, 0, 0, 0xA0, 1.0f, 0);
        }
    }
    if (dist - stopDist < 0) {
        dist = 0;
    } else {
        dist = dist - stopDist;
    }
    actorSetTargetSpeed(gCurrentActor, dist * 2.0);
    actorPitchEaseTowardPoint(0x23, yOffset, gBehaviourTargetActor->x, gBehaviourTargetActor->y + yOffset * 3.0, gBehaviourTargetActor->z, 0x1E, 3.3f, 100.0f, flags | 0x2000);
    gCurrentActor->y += 0.5 * mathSinF(gFrameCounter * 40);
    actorUpdateNearestSpotlight();
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void spotlightFollowerSubmergedUpdate(void) {
    gCurrentActor->waterY = 99999.0f;
    spotlightFollowerStep(0, 0xA, 0x44);
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
}

void spotlightFollowerUpdate(void) {
    spotlightFollowerStep(0xA, 0x14, 0x240);
}

extern Actor *gSpawnedActor;

void timedWarpTargetUpdate(void) {
    f32 ratio;
    f32 x;
    f32 y;
    f32 z;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->drawDistance = 0x7D0;
        gCurrentActor->cullMarginX = 0xFF;
        gCurrentActor->cullMarginY = 0xFF;
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->state = 0x27;
        gCurrentActor->subState = 0;
        gBehaviourWorkState->scale = gCurrentActor->sub4->scaleY;
        gBehaviourWorkState->countdown = 0x96;
        gBehaviourAnimState->flags |= 0x60;
        hudSpawnCountdownTimer(0xDC, 0x2A, 0x64);
        hudCountdownTimerStart(gSpawnedActor);
    }
    if (gBehaviourWorkState->flags & 0x80) {
        gCurrentActor->flags |= 0x400;
    } else {
        gCurrentActor->flags &= ~0x400;
    }
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
    switch (gCurrentActor->state) {
        case 0:
            if (gBehaviourWorkState->timer != 0) {
                ratio = (f32)gBehaviourWorkState->timer / (f32)gBehaviourWorkState->countdown;
                actorGetNodePos(gCurrentActor, 2, &x, &y, &z);
                actorSetUniformScale(gPrimaryPlayerActor, ratio * 0.13 + 0.02);
                gPrimaryPlayerActor->x += (x - gPrimaryPlayerActor->x) * 0.05;
                gPrimaryPlayerActor->y += (y - gPrimaryPlayerActor->y) * 0.05;
                gPrimaryPlayerActor->z += (z - gPrimaryPlayerActor->z) * 0.05;
                gBehaviourWorkState->timer--;
                if (gBehaviourWorkState->timer == 0) {
                    mapSaveSlotAndTransition(0x33, 0, 0, 1);
                }
            }
            break;
        case 0x27:
            if (gBehaviourWorkState->countdown != 0) {
                gCurrentActor->y += 2.0f;
                gBehaviourWorkState->countdown--;
                actorSetUniformScale(gCurrentActor, gBehaviourWorkState->scale + (0.01 - gBehaviourWorkState->scale) * (gBehaviourWorkState->countdown / 150.0));
            } else {
                gCurrentActor->state = 2;
                gCurrentActor->subState = 0;
            }
            break;
        case 2:
            if (gActorGlobalState.bossFightPhase == 4) {
                actorScriptStart(gCurrentActor, 0);
                scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
                gCurrentActor->state = 0;
                gCurrentActor->subState = 0;
                camRequestPathLength();
                gBehaviourWorkState->timer = camStartPath(gCurrentActor, 0x18, 1) - 0x1E;
                gBehaviourWorkState->countdown = gBehaviourWorkState->timer;
                gCurrentActor->collisionMode = 1;
            } else {
                switch (gCurrentActor->subState) {
                    case 5:
                        actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
                        gCurrentActor->subState = 0;
                        break;
                    case 3:
                        actorSetTargetSpeed(gCurrentActor, 0);
                        actorScriptStart(gCurrentActor, 0x2BB);
                        gCurrentActor->subState = 4;
                    case 4:
                    case 0:
                        effectSpawnSparks(3, 1);
                        if (gCurrentActor->subState == 0) {
                            if ((randomNonNegative() >> 15) % 1000 >= 991) {
                                gCurrentActor->subState = 3;
                            }
                        }
                        if (gCurrentActor->parentActor->state == 5 || gPrimaryPlayerActor->actorType != 3) {
                            actorScriptStart(gCurrentActor, 0x2BA);
                            scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
                            csModelStateSetFirstByte(0x33, 0);
                            actorDespawn(gCurrentActor->parentActor);
                            gCurrentActor->subState = 1;
                        }
                        actorPitchEaseTowardPoint(2, 0, gBehaviourWorkState->targetX, gBehaviourWorkState->targetY, gBehaviourWorkState->targetZ, 0x46, 30.0f, 100.0f, 0x200);
                        patrolPathStep(2, 0);
                        break;
                    case 1:
                        behaviourFadeOutWithinZone(5);
                        break;
                    case 2:
                        gCurrentActor->state = 0x3B;
                        break;
                }
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
