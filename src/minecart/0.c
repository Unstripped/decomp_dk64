#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/112080_resource_parse.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/11BC10_effect_update.h"
#include "proto/global/126260_command_queue.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/12E800_behaviour.h"
#include "proto/global/15050_heap.h"
#include "proto/global/166A0_random.h"
#include "proto/global/17800_matrix_rotation.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/9DD70.h"
#include "proto/global/A7710_countdown_timer.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/EFDC0_player_state_enter.h"
#include "proto/global/FCCD0_slot_queue.h"
#include "proto/minecart/0.h"

// A track point is a TargetVec3f (mathPickCloserTargetPoint3D's point type).
typedef TargetVec3f MinecartTrackPoint;

// Track cursor of a minecart, the cart actor customState (minecart/25F0.c views part of it).
typedef struct MinecartCart {
    /* 0x00 */ s16 jumpHeight;
    /* 0x02 */ s16 yawDeltaOverride;
    /* 0x04 */ Actor *rider;
    /* 0x08 */ u8 riderPlayer; // player index of the rider (playerStateQueueCallback)
    /* 0x09 */ char pad9[3];
    /* 0x0C */ MinecartTrackPoint *prevPoint;
    /* 0x10 */ s16 pointIndex;
    /* 0x12 */ char pad12[2];
    /* 0x14 */ f32 tilt;
    /* 0x18 */ f32 tiltTarget;
    /* 0x1C */ f32 tiltReturnRate;
    /* 0x20 */ f32 tiltRate;
    /* 0x24 */ f32 tiltAccel;
    /* 0x28 */ f32 tiltRateMax;
    /* 0x2C */ f32 junctionBlend;
    /* 0x30 */ u8 *route; // track indices ending in 0xFF; bits 0x80 and 0x40 shift the lane
    /* 0x34 */ u8 *routeCursor;
    /* 0x38 */ char pad38[1];
    /* 0x39 */ u8 peakTilt;
    /* 0x3A */ u8 passBySfxTimer;
    /* 0x3B */ u8 pad3B;
    /* 0x3C */ s16 prevTargetDist;
    /* 0x3E */ u8 targetSpeed;
    /* 0x3F */ u8 laneOffset;
    /* 0x40 */ u8 junctionOffset;
    /* 0x41 */ u8 junctionPoint;
    /* 0x42 */ u8 branchSide;
} MinecartCart;

// A junction branch: on reaching point atPoint the route becomes {track, nextTrack}, nextTrack entered at point startPoint.
typedef struct MinecartElem {
    u8 atPoint;
    u8 nextTrack;
    u8 startPoint;
    u8 track;
} MinecartElem;

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern PlayerStruct *gPlayerSlots;
extern PlayerState *gActivePlayerState;
extern s32 gCurrentMap;
extern u16 gMinigameCoinCount;
extern s16 gCarryMinFallSpeed;
extern f32 gDefaultAccelY;
extern s16 gLadderJumpSpeed;
extern s32 gMinecartTrackCount;
extern EffectGridAsset gSparkEffectSprite;
extern struct GfSndState *gSfxFreeSlotHandles[];
extern s16 gSfxSourceVoice[];
extern f32 gSfxVoicePitch[];

// Junction tables: 25F0's gMinecartJunctionTable sits in this TU's .data, below 0's own table.
MinecartElem D_80028B90[4] = { { 0xFF, 0, 0, 0 }, { 0xFF, 0, 0, 0 }, { 0x0B, 0x01, 0x09, 0x04 }, { 0x22, 0x01, 0x19, 0x06 } };
MinecartElem D_80028BA0[4] = { { 0x08, 0x00, 0x0C, 0x05 }, { 0x18, 0x00, 0x23, 0x07 }, { 0x10, 0x02, 0x0D, 0x0A }, { 0x20, 0x02, 0x01, 0x08 } };
MinecartElem D_80028BB0[4] = { { 0x0C, 0x01, 0x11, 0x0B }, { 0x18, 0x01, 0x21, 0x09 }, { 0x06, 0x03, 0x05, 0x0C }, { 0x12, 0x03, 0x0E, 0x0E } };
MinecartElem D_80028BC0[4] = { { 0x04, 0x02, 0x07, 0x0D }, { 0x0D, 0x02, 0x13, 0x0F }, { 0xFF, 0, 0, 0 }, { 0xFF, 0, 0, 0 } };
MinecartElem *gMinecartJunctionTable[4] = { D_80028B90, D_80028BA0, D_80028BB0, D_80028BC0 };
MinecartElem D_80028BE0[4] = { { 0x0C, 0x11, 0x09, 0x17 }, { 0x23, 0x11, 0x19, 0x15 }, { 0xFF, 0, 0, 0 }, { 0xFF, 0, 0, 0 } };
MinecartElem D_80028BF0[4] = { { 0x10, 0x12, 0x0D, 0x1B }, { 0x20, 0x12, 0x01, 0x19 }, { 0x08, 0x10, 0x0D, 0x16 }, { 0x18, 0x10, 0x24, 0x14 } };
MinecartElem D_80028C00[4] = { { 0x06, 0x13, 0x06, 0x1F }, { 0x12, 0x13, 0x0F, 0x1D }, { 0x0C, 0x11, 0x11, 0x1A }, { 0x18, 0x11, 0x01, 0x18 } };
MinecartElem D_80028C10[4] = { { 0xFF, 0, 0, 0 }, { 0xFF, 0, 0, 0 }, { 0x05, 0x12, 0x07, 0x1E }, { 0x0E, 0x12, 0x13, 0x1C } };
MinecartElem *sMinecartJunctionTable[4] = { D_80028BE0, D_80028BF0, D_80028C00, D_80028C10 };
void *sMinecartWheelEffect = NULL;
// Track routes: point indices ending in 0xFF.
u8 D_80028C34[8] = { 0x00, 0x01, 0x03, 0x04, 0x06, 0x07, 0x09, 0xFF };
u8 sMinecartDefaultRoute[4] = { 0x00, 0xFF };
u8 D_80028C40[8] = { 0x00, 0x01, 0x03, 0x04, 0x07, 0xFF };
u8 D_80028C48[8] = { 0x00, 0x81, 0x43, 0x87, 0xFF };
u8 sMinecartReversedRoute[8] = { 0x87, 0x43, 0x81, 0x00, 0xFF };

void minecartTriggerLoss(u8 useCutsceneCam, u8 textIndex) {
    sfxPlayOnFreeSlot(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
    textSpawnMarkerChecked(0x81, 0, 0x78, textTableGetString(0x1A, textIndex, 1), 0, 0x28, 8, 8);
    gCurrentActor->parentActor->state = 0;
    sfxAllocateChannel(0x28, 1.0f);
    playerStateQueueCallback(0x44, NULL, 0);
    gCurrentActor->state++;
    if (useCutsceneCam != 0) {
        camStartPath(gPrimaryPlayerActor, 5, 5);
    }
}

void minecartTriggerWin(u8 useCutsceneCam, u8 textIndex) {
    textSpawnMarkerChecked(0x81, 0, 0x78, textTableGetString(0x1A, textIndex, 1), 0, 0x28, 8, 8);
    gCurrentActor->parentActor->state = 0;
    sfxAllocateChannel(0x2A, 1.0f);
    playerStateQueueCallback(0x43, NULL, 0);
    gCurrentActor->state++;
    if (useCutsceneCam != 0) {
        camStartPath(gPrimaryPlayerActor, 5, 5);
    }
}

void minecartSpawnWheelEffect(MinecartCart *cart, u8 side, u8 probabilityThreshold) {
    if ((randomLcgNext() & 0xFF) >= probabilityThreshold && cart->jumpHeight == 0) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8A, 0x96, 0x7F, 0x32);
        effectSetSpeed((s32)gCurrentActor);
        effectSetCallback(effectTimedLightIntensityFade);
        sMinecartWheelEffect = effectCreateAtActorBone(&gSparkEffectSprite, 0.4f, gCurrentActor, side + 7, 2);
    }
}

void minecartStepSpeedToTarget(MinecartCart *cart) {
    u32 targetSpeedInt = cart->targetSpeed;
    f32 nextSpeed;
    f32 targetSpeed = targetSpeedInt;

    if (targetSpeed != gCurrentActor->speedXZ) {
        if (gCurrentActor->speedXZ < targetSpeed) {
            nextSpeed = gCurrentActor->speedXZ + 8.0f;
            if (targetSpeed < nextSpeed) {
                gCurrentActor->speedXZ = targetSpeed;
                return;
            }
            gCurrentActor->speedXZ = nextSpeed;
            return;
        }
        if (targetSpeed < gCurrentActor->speedXZ) {
            nextSpeed = gCurrentActor->speedXZ - 8.0f;
            if (nextSpeed < targetSpeed) {
                gCurrentActor->speedXZ = targetSpeed;
                return;
            }
            gCurrentActor->speedXZ = nextSpeed;
        }
    }
}

void minecartPlayerCartUpdate(u8 startPoint, u8 *route, s16 yawDeltaOverride, u8 maxTiltLimit) {
    s32 pad;
    PlayerState *playerState;
    MinecartCart *cart;
    s32 flags;
    s32 pad2[9];
    f32 nodePos[3];

    cart = gCurrentActor->customState;
    playerState = gPlayerSlots->actor->customState;
    flags = gCurrentActor->flags;
    if (!(flags & 0x10)) {
        gCurrentActor->flags = flags | 0x1400;
        if (gCurrentMap == 6 || gCurrentMap == 0x37 || gCurrentMap == 0x6A) {
            slotQueueUpdate(0xB, 1, 0);
            gMinigameCoinCount = 0;
        }
    }
    if (cart->rider == NULL) {
        cart->rider = gPlayerSlots->actor;
        cart->riderPlayer = 0;
    }
    switch (gCurrentActor->state) {
    case 0:
        if ((cart->rider->x - gCurrentActor->x) * (cart->rider->x - gCurrentActor->x) +
            (cart->rider->y - gCurrentActor->y) * (cart->rider->y - gCurrentActor->y) +
            (cart->rider->z - gCurrentActor->z) * (cart->rider->z - gCurrentActor->z) < 400.0f) {
            cart->routeCursor = route;
            cart->pointIndex = startPoint;
            cart->route = route;
            playerStateQueueCallback(0x45, gCurrentActor, cart->riderPlayer);
            gCurrentActor->state++;
        } else {
            actorUpdateModelMatrix(gCurrentActor, 0);
            break;
        }
        /* fallthrough */
    case 1:
        minecartFollowTrack(cart, yawDeltaOverride, maxTiltLimit);
        camSetTargetScaled(playerState->camActor, gCurrentActor, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
        gCurrentActor->state++;
        break;

    case 2:
        actorGetNodePos(gCurrentActor, 9, &cart->rider->x, &cart->rider->y, &cart->rider->z);
        gCurrentActor->state++;
        if (gCurrentActor->yawSpeed == 0 && gCurrentMap != 6) {
            gCurrentActor->yawSpeed = 2;
        }
        /* fallthrough */
    case 3:
    case 5:
        if (gCurrentActor->yawSpeed == 0 && camIsCutsceneActive() != 0) {
            gCurrentActor->yawSpeed = 1;
        }
        if (gCurrentActor->yawSpeed == 1 && gCurrentActor->subState == 0) {
            if (camIsCutsceneActive() != 0) {
                playerState->stateFlags |= 8;
            } else {
                camSetTargetScaled(playerState->camActor, gCurrentActor, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
                playerState->stateFlags &= ~8;
                cart->targetSpeed = 0x3C;
                gCurrentActor->subState++;
            }
        }
        actorSpawnNodeEffectFacingCamera(6, 0xFF);
        minecartStepSpeedToTarget(cart);
        minecartFollowTrack(cart, yawDeltaOverride, maxTiltLimit);
        actorGetNodePos(gCurrentActor, 5, &nodePos[0], &nodePos[1], &nodePos[2]);
        commandQueuePush(gCurrentActor, nodePos[0], nodePos[1], nodePos[2], 0xFF, 0xFF, 0xFF, 0xFF, 0);
        commandQueuePush(cart->rider, nodePos[0], nodePos[1], nodePos[2], 0xFF, 0xFF, 0xFF, 0xFF, 0);
        break;
    }
}

void minecartUpdateHeadlight(void) {
    f32 lightAim[3];
    f32 lightPos[3];

    if (gActivePlayerState->stateFlags & 0x10000002) {
        actorGetNodePos(gCurrentActor, 2, &lightPos[0], &lightPos[1], &lightPos[2]);
        actorGetNodePos(gCurrentActor, 1, &lightAim[0], &lightAim[1], &lightAim[2]);
    } else {
        actorGetNodePos(gCurrentActor, 1, &lightPos[0], &lightPos[1], &lightPos[2]);
        actorGetNodePos(gCurrentActor, 2, &lightAim[0], &lightAim[1], &lightAim[2]);
    }
    lightSetDistanceThreshold(0xC8);
    lightSetFovAngles(20.0f, 40.0f);
    lightAdd(lightPos[0], lightPos[1], lightPos[2], lightAim[0], lightAim[1], lightAim[2], 0.0f, 1, 0xFF, 0xFF, 0xFF);
}

void minecartUpdateHeadlightAndSpeed(void) {
    MinecartCart *cart = gCurrentActor->customState;

    if (!(gCurrentActor->flags & 0x10)) {
        cart->tiltAccel = 0.1f;
        cart->tiltRateMax = 5.0f;
    }
    minecartPlayerCartUpdate(1, (gCurrentMap == 6) ? D_80028C34 : sMinecartDefaultRoute, 0x7FFF, 0x23);
    minecartUpdateHeadlight();
}

void minecartUpdatePhysics(void) {
    s32 pad0;
    s32 pad1;
    s16 prevJumpHeight;
    MinecartCart *cart;
    f32 scaleFactor = gCurrentActor->sub4->scaleY * 0.16666666675;

    cart = gCurrentActor->customState;
    prevJumpHeight = cart->jumpHeight;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->terminalSpeedY = gCarryMinFallSpeed;
        cart->tiltAccel = 3.0f;
        cart->tiltRateMax = 12.0f;
    }
    if (cart->pointIndex == 0x90) {
        gCurrentActor->speedXZ = 130.0f;
        gCurrentActor->accelY = gDefaultAccelY * 0.6;
        if (cart->jumpHeight == 0) {
            gCurrentActor->speedY = gLadderJumpSpeed * 1.6;
        }
    } else {
        gCurrentActor->accelY = gDefaultAccelY;
    }
    cart->jumpHeight += gCurrentActor->speedY * scaleFactor;
    actorApplyGravity();
    if (cart->jumpHeight < 0) {
        cart->jumpHeight = 0;
        if (prevJumpHeight != 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8B, 0xFF, 0x7F, 0x1E);
        }
    }
    minecartPlayerCartUpdate(3, D_80028C40, cart->yawDeltaOverride, 0x19);
    if (gPrimaryPlayerActor->chunkIndex != 0x12 && gPrimaryPlayerActor->chunkIndex != 0xB) {
        minecartUpdateHeadlight();
    }
    if (gCurrentActor->state != 0) {
        actorGetNodePos(gCurrentActor, 9, &cart->rider->x, &cart->rider->y, &cart->rider->z);
    }
}

void minecartReverseTrackBehaviour(void) {
    s32 padA;
    f32 scaleFactor;
    s16 prevJumpHeight;
    s16 i;
    s16 j;
    s16 pointCount;
    MinecartTrackPoint tmp;
    MinecartCart *cart;

    scaleFactor = gCurrentActor->sub4->scaleY * 0.16666666675;
    cart = gCurrentActor->customState;
    prevJumpHeight = cart->jumpHeight;
    if (!(gCurrentActor->flags & 0x10)) {
        actorSetUniformScale(gPrimaryPlayerActor, 0.12f);
        gCurrentActor->accelY = gDefaultAccelY;
        gCurrentActor->terminalSpeedY = gCarryMinFallSpeed;
        cart->tiltAccel = 0.1f;
        cart->tiltRateMax = 5.0f;
    }
    cart->jumpHeight += gCurrentActor->speedY * scaleFactor;
    actorApplyGravity();
    if (cart->jumpHeight < 0) {
        cart->jumpHeight = 0;
        if (prevJumpHeight != 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8B, 0xFF, 0x7F, 0x1E);
        }
    }
    if (gPrimaryPlayerActor->contactFlags & 0x100) {
        gPrimaryPlayerActor->contactFlags &= ~0x100;
        gCurrentActor->yawSpeed = 2;
    }
    minecartPlayerCartUpdate(1, D_80028C48, 0x7FFF, 0x23);
    minecartUpdateHeadlight();
    if (*cart->routeCursor >= 7 && camIsCutsceneActive() != 0 && gCurrentActor->state != 5) {
        gCurrentActor->speedXZ = 300.0f;
    }
    if (gCurrentActor->state == 4) {
        for (i = 0; i < gMinecartTrackCount; i++) {
            pointCount = gMinecartTrackPoints[i + 1] - gMinecartTrackPoints[i];
            for (j = 0; j < pointCount / 2; j++) {
                tmp = gMinecartTrackPoints[i][j];
                gMinecartTrackPoints[i][j] = gMinecartTrackPoints[i][pointCount - j - 1];
                gMinecartTrackPoints[i][pointCount - j - 1] = tmp;
            }
        }
        cart->routeCursor = sMinecartReversedRoute;
        cart->pointIndex = 2;
        gCurrentActor->state = 5;
        cart->prevPoint = NULL;
    }
    if (gCurrentActor->state != 0) {
        actorGetNodePos(gCurrentActor, 9, &cart->rider->x, &cart->rider->y, &cart->rider->z);
    }
}

void minecartApplyJunction(MinecartCart *cart, MinecartElem **junctionTable, u8 minTrack, u8 maxTrack) {
    u8 i = 0;
    s32 found = 0;
    u8 curTrack = *cart->routeCursor;

    for (; i < 4 && found == 0; i++) {
        if ((cart->branchSide == 1 && i < 2) || (cart->branchSide == 2 && i >= 2)) {
            MinecartElem *elem = &junctionTable[curTrack - minTrack][i];

            if (curTrack >= minTrack && curTrack <= maxTrack && cart->pointIndex == elem->atPoint) {
                heapFree(cart->route);
                found = 1;
                cart->route = heapAlloc(3);
                cart->routeCursor = cart->route;
                cart->routeCursor[0] = elem->track;
                cart->routeCursor[1] = elem->nextTrack;
                cart->routeCursor[2] = 0xFF;
                cart->junctionPoint = elem->startPoint;
                cart->pointIndex = 1;
            }
        }
    }
}

void minecartPlayerCartJunctionBehaviour(void) {
    MinecartCart *cart;
    PlayerState *playerState;
    f32 camHeight;
    f32 scale;

    cart = gCurrentActor->customState;
    playerState = gPrimaryPlayerActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        cart->route = heapAlloc(3);
        cart->route[0] = 0x10;
        cart->route[1] = 0xFF;
        cart->tiltAccel = 3.0f;
        cart->tiltRateMax = 12.0f;
        gCurrentActor->yawSpeed = 3;
        playerState->stateFlags |= 8;
        camStartPath(gCurrentActor, 0, 1);
        actorScriptStart(gCurrentActor, 0);
    }
    if (gCurrentActor->state != 5 && gCurrentActor->state != 6) {
        camHeight = (gPlayerSlots->camY - gCurrentActor->y) - 100.0f;
        scale = camHeight / 650.0 * 0.15 + .15; // ORIG: target keeps two separate 0.15 doubles at .rodata+0x58/+0x60 (lo16 0x58 at 0x10cc, lo16 0x60 at 0x10d8)
        actorSetUniformScale(gCurrentActor, scale);
        actorSetUniformScale(gPrimaryPlayerActor, scale);
    }
    if (playerState->stateFlags & 8) {
        cart->targetSpeed = 3;
    }
    if (gCurrentActor->state < 5) {
        minecartPlayerCartUpdate(0x16, cart->route, 0, 0x19);
    }
    if (camIsCutsceneActive() == 0) {
        camSetFixedView(playerState->camActor, 322.0f, 900.0f, 268.0f, 325.0f, -9000.0f, 500.0f, 0);
    }
    switch (gCurrentActor->state) {
    case 1:
    case 2:
    case 3:
        if (gCurrentActor->sub4->animId == 0x292) {
            minecartTriggerWin(1, 0x14);
            gCurrentActor->state = 5;
        } else if (gCurrentActor->parentActor != NULL && gCurrentActor->parentActor->state == 5) {
            spawnNodesSetRespawnHold(0);
            minecartTriggerLoss(1, 0xE);
            gCurrentActor->state = 5;
            break;
        }
        minecartApplyJunction(cart, sMinecartJunctionTable, 0x10, 0x13);
        actorGetNodePos(gCurrentActor, 9, &cart->rider->x, &cart->rider->y, &cart->rider->z);
        break;
    case 4:
        gCurrentActor->state = 3;
        cart->routeCursor--;
        break;
    case 5:
        actorSetUniformScale(gCurrentActor, 0.15f);
        actorSetUniformScale(gPrimaryPlayerActor, 0.225f);
        gCurrentActor->pitch = 0;
        gCurrentActor->state++;
        break;
    case 10:
        sfxAllocateChannel(0x5A, 1.0f);
        hudSpawnCountdownTimer(0x78, 0x78, (gCurrentMap == 0x4D) ? 0x1E : (gCurrentMap == 0x81) ? 0x2D : 0x3C);
        hudCountdownTimerStart(gCurrentActor->parentActor);
        playerState->stateFlags &= ~8;
        gCurrentActor->state = 3;
        break;
    }
}

void minecartRampTiltRate(MinecartCart *cart) {
    cart->tiltRate += cart->tiltAccel;
    if (cart->tiltRateMax < cart->tiltRate) {
        cart->tiltRate = cart->tiltRateMax;
    }
}

void minecartFollowTrack(MinecartCart *cart, s16 yawDeltaOverride, u8 maxTiltLimit) {
    u8 i;
    u8 busySlots;
    s8 prevTiltSign;
    MinecartTrackPoint *targetPt;
    MinecartTrackPoint *prevPrevPt;
    f32 rearTargetPt[3];
    f32 frontTargetPt[3];
    f32 rearNodePos[3];
    f32 frontNodePos[3];
    s32 limit;
    f32 rollDelta;
    s16 waypointAngle;
    s16 pointCount;
    f32 horizDist;
    f32 predX, predY, predZ;
    f32 stepDist;
    f32 tiltLimit;
    f64 slopeFactor;
    f32 mtxTilt[4][4];
    u8 j;
    u8 busySlots2;
    s16 oldYaw;
    s8 lateralShift;
    u8 trackIndex;
    s16 yawDelta;
    f32 junctionX, junctionY, junctionZ;
    MinecartTrackPoint *junctionPt;
    f32 absTilt;

    prevPrevPt = cart->prevPoint;
    oldYaw = gCurrentActor->yaw;
    lateralShift = 0;
    trackIndex = (*cart->routeCursor + cart->laneOffset) & ~0xC0;
    actorUpdatePrevContactFlags(gCurrentActor);
    if (cart->routeCursor != NULL && prevPrevPt == NULL) {
        gCurrentActor->collisionMode = 0x24;
        targetPt = &gMinecartTrackPoints[trackIndex][cart->pointIndex++];
        gCurrentActor->x = targetPt->x;
        gCurrentActor->y = targetPt->y;
        gCurrentActor->z = targetPt->z;
        gCurrentActor->floorY = targetPt->y;
        targetPt++;
        gCurrentActor->yaw = mathAngleBetweenPoints2D(targetPt->x, targetPt->z, gCurrentActor->x, gCurrentActor->z);
        gCurrentActor->roll = mathAtan2(gCurrentActor->y - targetPt->y,
                                        sqrtf((gCurrentActor->x - targetPt->x) * (gCurrentActor->x - targetPt->x) +
                                              (gCurrentActor->z - targetPt->z) * (gCurrentActor->z - targetPt->z))) *
                              2048.0 / 3.1415927410125732;
        cart->prevPoint = targetPt - 2;
        sfxPlayActorSound(gCurrentActor, 0x113, 0, 1, 0, 0xFF, 1.0f, 0);
        cart->junctionPoint = 1;
    }
    targetPt = &gMinecartTrackPoints[trackIndex][cart->pointIndex];
    if (cart->pointIndex >= 2) {
        prevPrevPt = targetPt - 2;
    }
    if (gCurrentActor->speedXZ < 0.0f && gCurrentActor->x == targetPt[-1].x && gCurrentActor->z == targetPt[-1].z && cart->pointIndex >= 2) {
        cart->pointIndex--;
        targetPt--;
    }
    actorGetNodePos(gCurrentActor, 3, &frontNodePos[0], &frontNodePos[1], &frontNodePos[2]);
    actorGetNodePos(gCurrentActor, 4, &rearNodePos[0], &rearNodePos[1], &rearNodePos[2]);
    stepDist = gCurrentActor->sub4->scaleY * gCurrentActor->speedXZ * 0.16666666675;
    if (gCurrentMap == 0x4D || gCurrentMap == 0x81 || gCurrentMap == 0x82) {
        stepDist *= 1.8;
    } else {
        if (2.0 * mathSinF(gCurrentActor->roll) + 1.0 < 0.6) {
            slopeFactor = 0.6;
        } else {
            slopeFactor = 2.0 * mathSinF(gCurrentActor->roll) + 1.0;
        }
        stepDist *= 2.5 * slopeFactor;
    }
    waypointAngle = mathAngleBetweenPoints2D(targetPt->x, targetPt->z, targetPt[-1].x, targetPt[-1].z);
    if (cart->jumpHeight == 0) {
        gSfxVoicePitch[gSfxSourceVoice[gCurrentActor->soundSlots[0]]] = stepDist / 15.0 + 0.7;
    } else {
        gSfxVoicePitch[gSfxSourceVoice[gCurrentActor->soundSlots[0]]] = 0.0f;
    }
    if (gCurrentActor->movePitch != 0) {
        gCurrentActor->movePitch--;
        mathPickCloserTargetPoint3D(frontNodePos[0], frontNodePos[1], frontNodePos[2], targetPt, targetPt + 1, targetPt + 1, targetPt + 2, &frontTargetPt[0], &frontTargetPt[1], &frontTargetPt[2]);
        mathPickCloserTargetPoint3D(rearNodePos[0], rearNodePos[1], rearNodePos[2], targetPt - 1, targetPt, targetPt, targetPt + 1, &rearTargetPt[0], &rearTargetPt[1], &rearTargetPt[2]);
    } else {
        mathPickCloserTargetPoint3D(frontNodePos[0], frontNodePos[1], frontNodePos[2], targetPt - 1, targetPt, targetPt, targetPt + 1, &frontTargetPt[0], &frontTargetPt[1], &frontTargetPt[2]);
        mathPickCloserTargetPoint3D(rearNodePos[0], rearNodePos[1], rearNodePos[2], prevPrevPt, prevPrevPt + 1, targetPt - 1, targetPt, &rearTargetPt[0], &rearTargetPt[1], &rearTargetPt[2]);
    }
    gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, (f32)mathAngleBetweenPoints2D(frontTargetPt[0], frontTargetPt[2], rearTargetPt[0], rearTargetPt[2]), 1.7f);
    horizDist = sqrtf((frontTargetPt[0] - rearTargetPt[0]) * (frontTargetPt[0] - rearTargetPt[0]) + (frontTargetPt[2] - rearTargetPt[2]) * (frontTargetPt[2] - rearTargetPt[2]));
    rollDelta = gCurrentActor->roll;
    gCurrentActor->roll = mathAtan2(rearTargetPt[1] - frontTargetPt[1], horizDist) * 2048.0 / 3.1415927410125732;
    rollDelta -= gCurrentActor->roll;
    if (rollDelta > 2048.0f) {
        rollDelta -= 4096.0f;
    }
    if (rollDelta <= -2048.0f) {
        rollDelta += 4096.0f;
    }
    if (rollDelta > 25.0f) {
        busySlots = 0;
        for (i = 0; i < 0x14; i++) {
            if (gSfxFreeSlotHandles[i] != 0) {
                busySlots++;
            }
        }
        if (busySlots < 5) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x20, 0xFF, 0x7F, 0x14);
        }
    }
    predX = mathSinF(waypointAngle) * stepDist + gCurrentActor->x;
    predZ = mathCosF(waypointAngle) * stepDist + gCurrentActor->z;
    predY = gCurrentActor->floorY;
    if (mathPickCloserTargetPoint3D(predX, predY, predZ, targetPt - 1, targetPt, targetPt, targetPt + 1, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z) != 0) {
        cart->pointIndex++;
    }
    gCurrentActor->y += cart->jumpHeight;
    pointCount = gMinecartTrackPoints[trackIndex + 1] - gMinecartTrackPoints[trackIndex];
    if (gMinecartTrackCount == trackIndex + 1) {
        limit = pointCount - 1;
    } else {
        limit = pointCount;
    }
    if (cart->pointIndex >= limit) {
        cart->routeCursor++;
        if (*cart->routeCursor == 0xFF) {
            gCurrentActor->state++;
        }
        if (gActivePlayerState->cartDamage != 0 && cart->rider == gPrimaryPlayerActor) {
            cart->laneOffset = gActivePlayerState->cartDamage;
            gActivePlayerState->cartDamage = 0;
        } else if (gCurrentMap == 0x6A) {
            gCurrentActor->movePitch = 0x1E;
            cart->junctionBlend = 0.0f;
            if (*cart->routeCursor & 0x80) {
                cart->laneOffset >>= 1;
            } else if (!(*cart->routeCursor & 0x40)) {
                cart->laneOffset = 0;
            } else {
                cart->laneOffset <<= 1;
            }
            if (cart->laneOffset & 0x80) {
                cart->laneOffset = 0;
            }
        } else {
            cart->laneOffset = 0;
        }
        cart->pointIndex = cart->junctionPoint;
        cart->prevPoint = targetPt - 1;
        cart->junctionPoint = 1;
    }
    if (cart->junctionBlend != 0.0f) {
        i = (*cart->routeCursor + cart->junctionOffset) & 0x3F; // FAKE: sfx slot counter i reused as the junction track index (a dedicated local moves junctionPt from v1 to v0)
        junctionPt = &gMinecartTrackPoints[i][cart->pointIndex];
        mathPickCloserTargetPoint3D(predX, predY, predZ, junctionPt - 1, junctionPt, junctionPt, junctionPt + 1, &junctionX, &junctionY, &junctionZ);
        gCurrentActor->x += (junctionX - gCurrentActor->x) * cart->junctionBlend;
        gCurrentActor->z += (junctionZ - gCurrentActor->z) * cart->junctionBlend;
        cart->junctionBlend -= 0.06;
        if (cart->junctionBlend < 0.0f) {
            cart->junctionBlend = 0.0f;
        }
    }
    prevTiltSign = (cart->tilt > 0.0f) ? 1 : ((cart->tilt < 0.0f) ? -1 : 0);
    if (yawDeltaOverride == 0x7FFF) {
        yawDelta = gCurrentActor->yaw - oldYaw;
        if (yawDelta >= 0x801) {
            yawDelta -= 0x1000;
        }
    } else {
        yawDelta = yawDeltaOverride;
    }
    tiltLimit = MIN(maxTiltLimit, (yawDelta > 0 ? yawDelta : -yawDelta) * stepDist * 0.25);
    cart->tiltTarget += (tiltLimit - cart->tiltTarget) * 0.2;
    if (yawDelta >= 0x1F && yawDelta < 0x5A) {
        if (cart->tilt < tiltLimit) {
            minecartRampTiltRate(cart);
            cart->tilt += cart->tiltRate;
            if (tiltLimit < cart->tilt) {
                cart->tilt = tiltLimit;
            }
        }
    } else if (yawDelta < -0x1E && yawDelta >= -0x59) {
        if (-tiltLimit < cart->tilt) {
            minecartRampTiltRate(cart);
            cart->tilt -= cart->tiltRate;
            if (cart->tilt < -tiltLimit) {
                cart->tilt = -tiltLimit;
            }
        }
    }
    if (cart->tilt > 1.0f) {
        lateralShift = 0x20;
        minecartSpawnWheelEffect(cart, 1, 0xE6);
    } else if (cart->tilt < -1.0f) {
        lateralShift = -0x20;
        minecartSpawnWheelEffect(cart, 0, 0xE6);
    } else {
        minecartSpawnWheelEffect(cart, gFrameCounter & 1, 0xFA);
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
    if (lateralShift != 0) {
        if (cart->tiltTarget < 10.0f) {
            cart->tiltRate = 0.0f;
            if (cart->tilt > 0.0f) {
                cart->tilt -= cart->tiltReturnRate;
                if (cart->tilt < 0.0f) {
                    cart->tilt = 0.0f;
                }
            } else if (cart->tilt < 0.0f) {
                cart->tilt += cart->tiltReturnRate;
                if (cart->tilt > 0.0f) {
                    cart->tilt = 0.0f;
                }
            }
            cart->tiltReturnRate = MIN(cart->tiltReturnRate + 0.5, 10.0);
        } else {
            cart->tiltReturnRate = 0.0f;
            busySlots2 = 0;
            for (j = 0; j < 0x14; j++) {
                if (gSfxFreeSlotHandles[j] != 0) {
                    busySlots2++;
                }
            }
            if (busySlots2 < 5) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x21, 0xFF, 0x7F, 0x14);
            }
        }
        guTranslateF(gCurrentActor->modelMtx, lateralShift, 0.0f, 0.0f);
        matrixMakeRotationZ(mtxTilt, cart->tilt);
        guMtxCatF(gCurrentActor->modelMtx, mtxTilt, gCurrentActor->modelMtx);
        guTranslateF(mtxTilt, -lateralShift, 0.0f, 0.0f);
        guMtxCatF(gCurrentActor->modelMtx, mtxTilt, gCurrentActor->modelMtx);
        actorUpdateModelMatrix(gCurrentActor, 1);
        absTilt = (cart->tilt > 0.0f) ? cart->tilt : -cart->tilt;
        if (cart->peakTilt < absTilt) {
            if (cart->tilt > 0.0f) {
                cart->peakTilt = cart->tilt;
            } else {
                cart->peakTilt = -cart->tilt;
            }
        }
    }
    if (((cart->tilt > 0.0f) ? 1 : ((cart->tilt < 0.0f) ? -1 : 0)) != prevTiltSign) {
        if (cart->peakTilt != 0 && cart->jumpHeight == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8B, (cart->peakTilt / maxTiltLimit) * 0x7F + 0x80, 0x7F, 0x1E);
            cart->peakTilt = 0;
        }
    }
    actorUpdateFloorContactAndTilt(gCurrentActor, 0);
}
