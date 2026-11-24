#include "common.h"

#include "actor.h"
#include "race.h"
#include "sched.h"
#include "proto/global/103AB0_view_effects.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/11BC10_effect_update.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/15050_heap.h"
#include "proto/global/166A0_random.h"
#include "proto/global/17800_matrix_rotation.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/61AA0_render_caches.h"
#include "proto/global/63EC0_effect_water.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/6AD90_collision.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/80150_barrels.h"
#include "proto/global/89250_effect_spawn.h"
#include "proto/global/8CA50_anim_list.h"
#include "proto/global/8D3E0_actor_list.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/CC800_player_setup.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/EFDC0_player_state_enter.h"
#include "proto/global/F56F0_player_weapon.h"
#include "proto/global/FCCD0_slot_queue.h"

// This TU's .data (0x80750270-0x80750278 + 8-byte TU pad).
u8 sProjectileShortLivedFlag = 0;
f32 sProjectileGravity = -2.5f;

// Second component (0x178) of the ridden vehicle actors (race/52B0 passes it as `motion`): the model
// lean angles actorInterpolateAngles eases and the hop vehicleUpdateMotion consumes.
typedef struct VehicleMotion {
    s16 boneYaw;
    s16 bonePitch;
    u8 jumpQueued;
} VehicleMotion;

void actorSnapToBone(Actor **actorRef) {
    f32 boneY;
    PlayerState *playerState;

    playerState = (*actorRef)->customState;
    actorGetNodePos(playerState->actor, 9, &(*actorRef)->x, &boneY, &(*actorRef)->z);
    if ((*actorRef)->y < boneY) {
        (*actorRef)->y = boneY;
    }
    (*actorRef)->yaw = playerState->actor->yaw;
    actorUpdateModelMatrix(*actorRef, 0);
}

void actorSyncTransformFromParent(Actor **actorRef) {
    PlayerState *playerState;
    Actor *parent;
    RaceParticipant *vehicleState;

    playerState = (*actorRef)->customState;
    parent = playerState->actor;
    if (parent != NULL) {
        vehicleState = parent->customState;
        if (vehicleState->raceStatus < 5) {
            (*actorRef)->x = playerState->actor->x;
            (*actorRef)->y = playerState->actor->y;
            (*actorRef)->z = playerState->actor->z;
            (*actorRef)->yaw = playerState->actor->yaw;
            (*actorRef)->roll = playerState->actor->roll;
            (*actorRef)->pitch = playerState->actor->pitch;
            (*actorRef)->waterY = playerState->actor->waterY;
            if (playerState->actor->actorType == 0x12E) {
                (*actorRef)->speedXZ = playerState->actor->speedXZ * 10.0f;
            } else {
                (*actorRef)->speedXZ = playerState->actor->speedXZ;
            }
        } else {
            (*actorRef)->speedXZ = 0.0f;
        }
    }
    actorUpdateModelMatrix(*actorRef, 0);
}

s32 mathPickCloserTargetPoint3D(f32 x, f32 y, f32 z, TargetVec3f *segAStart, TargetVec3f *segAEnd, TargetVec3f *segBStart, TargetVec3f *segBEnd, f32 *outX, f32 *outY, f32 *outZ) {
    f32 bz;
    f32 by;
    f32 bx;
    f32 az;
    f32 ay;
    f32 ax;
    camClosestPointOnSegment(x, y, z, segAStart->x, segAStart->y, segAStart->z, segAEnd->x, segAEnd->y, segAEnd->z, &ax, &ay, &az);
    camClosestPointOnSegment(x, y, z, segBStart->x, segBStart->y, segBStart->z, segBEnd->x, segBEnd->y, segBEnd->z, &bx, &by, &bz);
    if (((x - ax) * (x - ax) + (y - ay) * (y - ay) + (z - az) * (z - az)) <
        ((z - bz) * (z - bz) + ((x - bx) * (x - bx) + (y - by) * (y - by)))) {
        *outX = ax;
        *outY = ay;
        *outZ = az;
        return 0;
    }
    *outX = bx;
    *outY = by;
    *outZ = bz;
    return 1;
}

extern PlayerStruct *gPlayerSlots;
extern Actor *gCurrentActor;
extern u8 gEffectSpriteGlowRed;

void actorSpawnNodeEffectFacingCamera(s32 node, u8 alphaMax) {
    f32 tgt;
    f32 cur;
    s16 diff;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    actorGetNodePos(gCurrentActor, node, &nodeX, &nodeY, &nodeZ);
    tgt = nodeX - gPlayerSlots->camX;
    tgt = (s16)(mathAtan2(gPlayerSlots->camZ - nodeZ, tgt) * 651.8986f + 1024.0f) & 0xFFF;
    cur = gCurrentActor->yaw;
    if (cur < tgt) {
        diff = tgt - cur;
    } else {
        diff = cur - tgt;
    }
    if (diff > 0x800) {
        diff = 0x1000 - diff;
    }
    if (diff < 0x384) {
        f32 fv0;
        f32 scale;
        u8 alpha;
        f32 vol;
        f32 af;

        fv0 = (1024.0f - diff) * 0.0014285714f;
        if (fv0 < 1.0f) {
            scale = fv0;
        } else {
            scale = 1.0f;
        }
        af = (u32)alphaMax;
        alpha = (u32)(scale * af);
        if (alpha != 0) {
            vol = 3.3f;
            if (gCurrentActor->sub4 != NULL) {
                vol *= gCurrentActor->sub4->scaleY;
            }
            effectSetColor(0xFF, 0xFF, 0xFF, alpha);
            effectCreateAtActorBone(&gEffectSpriteGlowRed, vol, gCurrentActor, node, 2);
        }
    }
}

extern Actor *gCurrentActor;


typedef struct OwnerLinkState {
    Actor *owner;
    Actor *notifyActor;
    s32 glowStartFrame;
} OwnerLinkState;

extern s32 gCurrentMap;
extern Actor *gActivePlayerActor;

#define PICK_MAX(a, b) ((a) < (b) ? (b) : (a))
#define PICK_MIN(a, b) ((a) < (b) ? (a) : (b))

void mountedBarrelUpdate(void) {
    f32 boneX;
    f32 boneY;
    f32 boneZ;
    f32 rotY[4][4];
    f32 rotX[4][4];
    f32 pitch;
    f64 ratio;
    f32 sparkScale;
    f32 glow;
    OwnerLinkState *link;
    PlayerState *playerState;
    Actor *owner;
    AnimSlot *model;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    BoneRotation *buf;
    u32 frame;

    link = gCurrentActor->customState;
    owner = link->owner;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->sub4->boneRotations = heapAlloc(0x10);
        buf = gCurrentActor->sub4->boneRotations;
        buf->weight = -0x80;
        buf->bone = 1;
        buf->rotX = 0;
        buf->rotY = 0;
        buf->rotZ = 0;
        buf[1].weight = 0;
        gCurrentActor->yaw = 0;
        if (owner->actorType == 0xC5) {
            gCurrentActor->tintR = 0xFF;
            gCurrentActor->tintG = 0xFF;
            gCurrentActor->tintB = 0xFF;
            gCurrentActor->flags |= 0x800000;
        }
        link->glowStartFrame = 0;
    }
    buf = gCurrentActor->sub4->boneRotations;
    switch (owner->collisionFlags) {
    case 1:
        playerState = owner->customState;
        buf->rotX = playerState->aimPitch;
        if ((owner->contactFlags & 5) || playerState->attachmentExitTimer == 1 || (owner->state == 0x42 && playerState->hitActorType != 0x31) || owner->state == 0x87) {
            actorAppendCallback(link->notifyActor, gCurrentActor, 0x2000000, 0, 0, 0);
            playerState->isHoldingObject = 0;
            actorDespawn(gCurrentActor);
            sfxStopChannel(0x48, 0);
            sfxStopSlotSound(gActivePlayerActor, 0);
            slotQueueCancel(5, 0);
            playerState->attachmentExitTimer = 0;
            if (!(playerState->stateFlags2 & 4)) {
                playerKongHolsterGun(owner);
            }
        }
        if (playerState->thrustApplied != 0 || (camIsCutsceneActive() && gFrameCounter % 5 == 0)) {
            ratio = (0, owner->speedY > 0.0 ? owner->speedY : 0.0);  // FAKE: comma routes the select through the shared f64 ternary temp (M-208 adjsave 4.67 over udiv 3.33): sparkScale $f2, lightAdd 0.0 in $f16 at 0x920
            if (gFrameCounter & 1) {
                effectSpawnActorBone(owner, 1, (f32)(ratio / 150.0 * 0.12) + 0.3);
            } else {
                effectSpawnActorBone(owner, 2, (f32)(ratio / 150.0 * 0.12) + 0.3);
            }
            playerState->thrustApplied = 0;
            link->glowStartFrame = gFrameCounter;
        }
        if (gCurrentMap == 0x5C) {
            frame = gFrameCounter;
            glow = (30.0 - (s32)(frame - link->glowStartFrame)) / 30.0 * 100.0;
            if (glow > 0.0) {
                lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, glow, 0, 0xFF, 0xC8, 0xC8);
            }
        }
        break;
    case 0x40:
        model = owner->sub4->model;
        switch (model->animId) {
        case 0x113:
            if (model->frame < 70.0f) {
                sparkScale = PICK_MIN(PICK_MAX(0.1, (model->frame - 39.0f) / 30.0), 0.49);
            } else {
                sparkScale = 0.5f;
            }
            break;
        case 0x12C:
            sparkScale = PICK_MAX(0.5 - model->frame / 50.0f, 0.01);
            break;
        case 0x12F:
        case 0x130:
            sparkScale = 0.25f;
            break;
        case 0x12D:
        case 0x12E:
            sparkScale = 0.0f;
            break;
        default:
            sparkScale = 0.5f;
            break;
        }
        buf->rotX = 0;
        if (!(owner->flags & 4) || owner->state == 0x3C) {
            actorDespawn(gCurrentActor);
        } else if (sparkScale > 0.05) {
            if (gFrameCounter & 1) {
                effectSpawnActorBone(owner, 1, sparkScale);
            } else {
                effectSpawnActorBone(owner, 2, sparkScale);
            }
        }
        break;
    }
    actorGetNodePos(owner, 1, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
    actorGetNodePos(owner, 0xB, &boneX, &boneY, &boneZ);
    mathNudgeCoords(gCurrentActor->x, gCurrentActor->z, &boneX, &boneZ);
    pitch = mathAtan2(boneX - gCurrentActor->x, boneZ - gCurrentActor->z);
    if (owner->collisionFlags == 0x40) {
        actorGetNodePos(owner, 0xC, &nodeX, &nodeY, &nodeZ);
        owner->moveYaw = mathAngleBetweenPoints2D(nodeX, nodeZ, gCurrentActor->x, gCurrentActor->z);
        matrixMakeRotationY(rotY, (owner->moveYaw * 360) / 4096);
    } else {
        matrixMakeRotationY(rotY, (owner->yaw * 360) / 4096);
    }
    matrixMakeRotationX(rotX, -90.0f);
    guMtxCatF(rotY, rotX, rotY);
    guAlignF(rotX, pitch * 57.295776f + 180.0f, boneX - gCurrentActor->x, boneY - gCurrentActor->y, boneZ - gCurrentActor->z);
    guMtxCatF(rotY, rotX, gCurrentActor->modelMtx);
    actorUpdateModelMatrix(gCurrentActor, 1);
}



extern s16 gVehicleWaterJumpSpeed;
void func_8002F490(void *);


void vehicleUpdateMotion(vehicle, motion, applyBuoyancy, tilt)
RaceParticipant *vehicle;
VehicleMotion *motion;
u8 applyBuoyancy;
u8 tilt;
{
    s32 turnScale;
    s32 kongState;
    f32 drag;
    f32 turnRate;
    f32 speedGain;
    s16 tiltRoll;
    s16 tiltPitch;
    u8 inWater;
    u8 onGround;
    f32 velX;
    f32 velZ;
    f32 thrust;
    s16 slopeAngle;
    s16 slopeRange;
    Actor *pl;

    pl = gPlayerSlots[vehicle->playerIdx].actor;
    kongState = pl->actorType;
    tiltRoll = 0;
    tiltPitch = 0;
    inWater = gCurrentActor->y <= gCurrentActor->waterY + 1.0f;
    onGround = gCurrentActor->contactFlags & 1;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x10400;
        gCurrentActor->state = 0;
        gCurrentActor->subState = 0;
        gCurrentActor->speedXZ = 0.0f;
        vehicle->raceStatus = 0;
        vehicle->statusStep = 0;
        if (vehicle->isCpu == 0) {
            gCurrentActor->collisionMode = 0x3C;
            gCurrentActor->accelY = -20.0f;
        } else {
            gCurrentActor->collisionMode |= 0x18;
            gCurrentActor->accelY = -30.0f;
        }
        gCurrentActor->terminalSpeedY = -900.0f;
        gCurrentActor->arcSpeedCapMax = 0x12C;
    }
    velX = mathSinF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ;
    velZ = mathCosF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ;
    if (inWater) {
        thrust = vehicle->throttle * 50.0f;
        drag = 1.0f / (kongState == 2 ? 5000.0f : 10000.0f) * (gCurrentActor->speedXZ * gCurrentActor->speedXZ) + vehicle->brake;
        if (vehicle->throttle != 0.0f) {
            drag = drag + 30.0f;
        } else {
            drag = drag + 3.0f;
        }
    } else {
        if (onGround) {
            thrust = vehicle->throttle * 4.0f;
            drag = vehicle->brake + gCurrentActor->speedXZ * gCurrentActor->speedXZ * 0.00002f + 2;
        } else {
            thrust = vehicle->throttle * 2;
            drag = vehicle->brake + gCurrentActor->speedXZ * gCurrentActor->speedXZ * 0.00002f + 2;
        }
    }
    velX += mathSinF(vehicle->heading) * thrust;
    velZ += mathCosF(vehicle->heading) * thrust;
    gCurrentActor->speedXZ = sqrtf(velX * velX + velZ * velZ);
    gCurrentActor->moveYaw = (mathAtan2(velX, velZ) * 4096.0 / 6.2831854820251465);
    if (onGround) {
        slopeRange = 0x400 - gCurrentActor->floorSlopePitch;
        slopeAngle = mathAngleSignedDistance(gCurrentActor->floorSlopeYaw, vehicle->heading);
        tiltRoll = (mathCosF(slopeAngle) * slopeRange);
        tiltPitch = (mathSinF(slopeAngle) * slopeRange);
    } else if (!tilt) {
        gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, 0, 4.0f);
        gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, 0, 5.0f);
    }
    turnRate = vehicle->steerGain * vehicle->steer;
    if (tilt) {
        tiltPitch = tiltPitch + turnRate * 200.0f;
        tiltPitch &= 0xFFF;
        if (inWater || onGround) {
            tiltRoll = tiltRoll + (vehicle->throttle * -50.0f + gCurrentActor->speedXZ * -0.5);
            tiltRoll &= 0xFFF;
        } else {
            tiltRoll = gCurrentActor->roll;
        }
        gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, tiltRoll, 4.0f);
        gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, tiltPitch, 5.0f);
    }
    gCurrentActor->speedXZ = gCurrentActor->speedXZ - drag;
    if (gCurrentActor->speedXZ < 0.0f) {
        gCurrentActor->speedXZ = 0.0f;
    }
    speedGain = gCurrentActor->speedXZ - gCurrentActor->prevSpeedXZ;
    if (speedGain < 0.0f) {
        speedGain = 0.0f;
    }
    if (kongState == 2) {
        turnScale = -0x1E;
    } else {
        turnScale = -0x28;
    }
    vehicle->heading = vehicle->heading + turnRate * turnScale * (1.0 + speedGain * 0.05);
    vehicle->heading = vehicle->heading & 0xFFF;
    if (applyBuoyancy) {
        if (gCurrentActor->y < gCurrentActor->waterY) {
            if (inWater) {}  // FAKE: block split in the waterY live range (adjsave 12/6 below speedY 15/5): waterY $f2 at 0x1370/0x14e8, speedY $f0 at 0x13b8
            gCurrentActor->speedY = gCurrentActor->speedY + ((gCurrentActor->waterY - gCurrentActor->y) * 3.0f + 15.0f);
            if ((gCurrentActor->speedY > 0.0f ? gCurrentActor->speedY : -gCurrentActor->speedY) > 20.0f) {
                gCurrentActor->speedY = gCurrentActor->speedY - gCurrentActor->speedY / 12.0f;
            }
        }
    }
    gCurrentActor->speedY = gCurrentActor->speedY + gCurrentActor->accelY;
    if (motion->jumpQueued != 0) {
        motion->jumpQueued = 0;
        if (inWater) {
            if (kongState == 2) {
                gCurrentActor->speedY = 200.0f;
            } else {
                gCurrentActor->speedY = gVehicleWaterJumpSpeed;
            }
        } else if (onGround) {
            gCurrentActor->speedY = gCurrentActor->speedY + 200.0f;
        }
    }
    if (gCurrentActor->speedY < gCurrentActor->terminalSpeedY) {
        gCurrentActor->speedY = gCurrentActor->terminalSpeedY;
    }
    if (kongState == 0) {}  // FAKE: dead use keeps the kongState piece bb 44..66 positive (Q1179): a0 from 0x12cc to 0x1434 beside the constant 2 in v1
    actorStepPhysics(gCurrentActor, gCurrentActor->yaw, vehicle->heading);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (!applyBuoyancy) {
        if (gCurrentActor->y < gCurrentActor->waterY) {
            gCurrentActor->y = gCurrentActor->waterY;
            gCurrentActor->speedY = gCurrentActor->accelY;
        }
    }
    if (gGlobalOverlayFlags & 0x2000) {
        func_8002F490(vehicle);
    }
    if (onGround && !(gCurrentActor->prevContactFlags & 1)) {
        gCurrentActor->speedY = -10.0f;
    }
    gCurrentActor->yaw = (vehicle->heading + vehicle->yawOffset) & 0xFFF;
}


void actorInterpolateAngles(u8 resetting, RaceParticipant *vehicle, VehicleMotion *motion) {
    f32 pitchGoal;
    f32 yawGoal;
    BoneRotation *angles;

    angles = gCurrentActor->sub4->boneRotations;
    if (resetting) {
        pitchGoal = 500.0f;
        yawGoal = 0.0f;
    } else {
        pitchGoal = 0.0f;
        yawGoal = vehicle->steer * (400.0 - 0.7 * gCurrentActor->speedXZ);
    }
    motion->bonePitch = mathAngleEaseToward(motion->bonePitch, (s16)pitchGoal, 5.0f);
    motion->boneYaw = mathAngleEaseToward(motion->boneYaw, (s32)yawGoal & 0xFFF, 3.0f);
    angles->weight = -0x80;
    angles->bone = 1;
    angles->rotX = (u16)motion->bonePitch * 16;
    angles->rotY = (u16)motion->boneYaw * 16;
    angles->rotZ = 0;
    angles[1].weight = 0;
}


void actorAllocSubBuffer(Actor *actor, s32 count) {
    actor->sub4->boneRotations = heapAlloc(count * 8);
    heapClearBlock(actor->sub4->boneRotations);
}


void actorInitAnimations(Actor *actor, Actor *owner) {
    u8 volume;
    PlayerState *ownerState;

    volume = 0;
    ownerState = owner->customState;
    playerStateQueueCallback(0x4C, actor, ownerState->playerIndex);
    if (gCurrentMap == 0x6F) {
        volume = 0x3C;
    }
    sfxPlayActorSound(actor, 0x115, volume, 1, 0, 0xFF, 1.0f, 0);
    sfxPlayActorSound(actor, 0x116, volume, 1, 1, 0xFF, 1.0f, 0);
    animSetSpeed(actor, 0, 1.0f);
    animSetLoopLimit(actor, 0, -1);
    actorAllocSubBuffer(actor, 2);
    actorCopyPoseAndScale(actor, owner, 0.15f);
}

extern s16 gSfxSourceVoice[];
extern f32 gSfxVoicePitch[];
extern f32 gSfxVoiceModCounter[];

void vehicleUpdateEngineSound(vehicle, motion)
RaceParticipant *vehicle;
VehicleMotion *motion;
{
    s16 idx;

    idx = gSfxSourceVoice[gCurrentActor->soundSlots[0]];
    if (gCurrentActor->y < gCurrentActor->waterY + 4.0f) {
        gSfxVoicePitch[idx] = gCurrentActor->speedXZ / 300.0 + 1.0;
        gSfxVoiceModCounter[idx] = 1.0f;
    } else {
        gSfxVoicePitch[idx] = vehicle->throttle + 1.2;
        gSfxVoiceModCounter[idx] = 5.0f;
    }

    idx = gSfxSourceVoice[gCurrentActor->soundSlots[1]];
    if (gCurrentActor->y < gCurrentActor->waterY + 4.0f) {
        if (gSfxVoiceModCounter[idx] == 0.0f) {
            gSfxVoicePitch[idx] = ((u32)randomLcgNext() / 4294967295.0 * 0.05 + 0.975) * (0.2 + gCurrentActor->speedXZ / 300.0);
            gSfxVoiceModCounter[idx] = 1.0f;
        }
    } else {
        gSfxVoicePitch[idx] = vehicle->throttle * 1.5 + 0.2;
        gSfxVoiceModCounter[idx] = 8.0f;
    }
}


void actorInitFromSpawnPoint(Actor *actor, RaceParticipant *vehicle) {
    G01Pos *spawn;
    s16 yaw;

    spawn = mapGetSpawnPoint(vehicle->place);
    actor->x = spawn->x;
    actor->y = spawn->y;
    actor->z = spawn->z;
    yaw = spawn->yaw * 16.062746f;
    actor->yaw = yaw;
    actor->moveYaw = yaw;
    vehicle->heading = yaw;
}

extern Actor *gSpawnedActor;

void actorSpawnChildActor(Actor *parent) {
    PlayerState *parentState = parent->customState;
    RaceParticipant *vehicle;
    s32 pad;
    Actor *child;

    actorSpawn(0x13F, 0xDA);
    child = gSpawnedActor;
    vehicle = child->customState;
    vehicle->playerIdx = parentState->playerIndex;
    actorInitAnimations(child, parent);
    vehicle->statusStep = 0;
    vehicle->isCpu = 0;
    vehicle->heading = parent->yaw;
    parentState->actor = child;
    child->flags &= ~0x20000;
}


typedef struct VehicleActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ VehicleMotion *motion;
} VehicleActor;
#define VEHICLE_ACTOR ((VehicleActor *)gCurrentActor)

extern u8 gGameMode;
extern f32 gVehicleGravity;
extern Actor *gPrimaryPlayerActor;

void actorUpdatePlayerInteraction(void) {
    RaceParticipant *vehicle;
    Actor *playerActor;
    PlayerState *playerState;
    VehicleMotion *motion;
    CamState *camState;
    u8 resetting;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    vehicle = gCurrentActor->customState;
    motion = VEHICLE_ACTOR->motion;
    playerActor = gPlayerSlots[vehicle->playerIdx].actor;
    playerState = playerActor->customState;
    camState = playerState->camActor->customState;
    resetting = gCurrentActor->contactFlags & 1;
    vehicle->raceStatus = 2;
    vehicleUpdateEngineSound(vehicle, motion);
    if (gGameMode == 0 && camState->mode != 4) {
        camSetTargetScaled(playerState->camActor, gCurrentActor, 4, 0x800, 0xA0, 0, 6, 0x12C, 0x8F, 0, 0.2f);
    }
    vehicleUpdateMotion(vehicle, motion, 1, 1);
    actorInterpolateAngles(resetting, vehicle, motion);
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->accelY = gVehicleGravity;
        gCurrentActor->collisionMode = 0x3C;
        playerStateQueueCallback(0x4C, gCurrentActor, playerState->playerIndex);
    }
    if (camIsCutsceneActive() == 0 || (camIsCutsceneActive() != 0 && (gPrimaryPlayerActor->contactFlags & 0x100))) {
        actorGetNodePos(gCurrentActor, 1, &nodeX, &nodeY, &nodeZ);
        lightAdd(nodeX, nodeY, nodeZ, 0.0f, 0.0f, 0.0f, 300.0f, 0, 0xFF, 0xFF, 0xFF);
        if (flagGet(0x6B, 2) == 0) {
            if (camIsCutsceneActive() != 0 && (gPrimaryPlayerActor->contactFlags & 0x100)) {
                actorGetNodePos(gCurrentActor, 2, &nodeX, &nodeY, &nodeZ);
                lensFlareAddSource(nodeX, nodeY, nodeZ, 0.0f, 0.0f, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF);
            }
            if (camIsCutsceneActive() == 0) {
                gPrimaryPlayerActor->contactFlags &= ~0x100;
            }
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorClearSubState(void) {
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void projectileSetSpawnFlag(void) {
    sProjectileShortLivedFlag = 1;
}

extern f32 gProjectileSpawnX;
extern f32 gProjectileSpawnY;
extern f32 gProjectileSpawnZ;
void projectileSetTargetCoords(f32 x, f32 y, f32 z) {
    gProjectileSpawnX = x;
    gProjectileSpawnY = y;
    gProjectileSpawnZ = z;
}


// Actor.spawnData of the projectile actors (projectileSpawnNodeEntry fills it; actorListSpawnNodeEntry copies it).
typedef struct ProjectileSpawnParams {
    f32 angle;
    f32 speedXZ;
    f32 speedY;
    f32 scale;
    f32 param;
    f32 shortLived;
    f32 pad18[2];
} ProjectileSpawnParams;

// customState of actor 0x107, filled by projectileSpawnSpriteRing from its parameters.
typedef struct ProjectileTrackerState {
    s16 value;
    char pad2[6];
    f32 rate;
    f32 limit;
    u8 pad10;
    u8 mode;
} ProjectileTrackerState;

extern u8 gMultiplayerReducedEffects;

void projectileGetTargetCoords(Actor *actor, s32 node) {
    actorGetNodePos(actor, node, &gProjectileSpawnX, &gProjectileSpawnY, &gProjectileSpawnZ);
}

void projectileSpawnNodeEntry(s16 type, s16 param, f32 speed, s16 yaw, f32 horizSpeed, f32 vertSpeed, Actor *owner) {
    ProjectileSpawnParams params;

    params.angle = (yaw / 4095.0) * 6.28318548202514648;
    params.speedXZ = horizSpeed;
    params.scale = speed;
    params.speedY = vertSpeed;
    params.param = param;
    params.shortLived = (f32)(u32)sProjectileShortLivedFlag;
    actorListSpawnNodeEntry(type, gProjectileSpawnX, gProjectileSpawnY, gProjectileSpawnZ, 0, speed, owner, &params);
    sProjectileShortLivedFlag = 0;
}

void projectileCalculateTrajectoryAndSpawn(s16 yaw, s16 type, s16 param, f32 speed, f32 targetX, f32 targetY, f32 targetZ, f32 flightTime, Actor *owner) {
    f32 dist;
    f32 dy;

    dist = sqrtf(((targetX - gProjectileSpawnX) * (targetX - gProjectileSpawnX)) + ((targetY - gProjectileSpawnY) * (targetY - gProjectileSpawnY)) + ((targetZ - gProjectileSpawnZ) * (targetZ - gProjectileSpawnZ)));
    dy = targetY - gProjectileSpawnY;
    projectileSpawnNodeEntry(type, param, speed, yaw, sqrtf(((targetX - gProjectileSpawnX) * (targetX - gProjectileSpawnX)) + ((targetZ - gProjectileSpawnZ) * (targetZ - gProjectileSpawnZ))) / (dist / flightTime), dy / (dist / flightTime), owner);
}

void projectileAimAndSpawn(s16 type, s16 param, f32 speed, f32 targetX, f32 targetY, f32 targetZ, f32 flightTime, Actor *owner) {
    projectileCalculateTrajectoryAndSpawn(mathAngleBetweenPoints2D(targetX, targetZ, gProjectileSpawnX, gProjectileSpawnZ), type, param, speed, targetX, targetY, targetZ, flightTime, owner);
}

void projectileClampAngleAndSpawn(s16 centerYaw, s16 maxSpread, s16 type, s16 param, f32 speed, f32 targetX, f32 targetY, f32 targetZ, f32 flightTime, Actor *owner) {
    s16 lowYaw;
    s16 highYaw;
    s16 yaw;

    yaw = mathAngleBetweenPoints2D(targetX, targetZ, gProjectileSpawnX, gProjectileSpawnZ);
    if (maxSpread < mathAngleDistance(centerYaw, yaw)) {
        lowYaw = (centerYaw - maxSpread) & 0xFFF;
        highYaw = (centerYaw + maxSpread) & 0xFFF;
        if (mathAngleDistance(yaw, lowYaw) < mathAngleDistance(yaw, highYaw)) {
            yaw = lowYaw;
        } else {
            yaw = highYaw;
        }
    }
    projectileCalculateTrajectoryAndSpawn(yaw, type, param, speed, targetX, targetY, targetZ, flightTime, owner);
}

void projectileAimFromActorAndSpawn(s16 type, s16 param, f32 speed, Actor *target, s32 node, f32 flightTime, Actor *owner) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    actorGetNodePos(target, node, &nodeX, &nodeY, &nodeZ);
    projectileAimAndSpawn(type, param, speed, nodeX, nodeY, nodeZ, flightTime, owner);
}

// customState of the projectile actors. Each per-kind update below uses part of it.
typedef struct ProjectileState {
    /* 0x00 */ u32 spawnFrame; // gGameFrameCounter at spawn: lifetime checks
    /* 0x04 */ u8 bounceCount;
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ f32 pitchDeg; // model pitch from the velocity (degrees)
    /* 0x0C */ f32 rollDeg; // random model roll (degrees)
    /* 0x10 */ u8 counter;
    /* 0x11 */ u8 tick;
    /* 0x12 */ u8 cooldown;
    /* 0x13 */ u8 param; // ProjectileSpawnParams.param
    /* 0x14 */ f32 scale; // ProjectileSpawnParams.scale
    /* 0x18 */ s16 baseSpeed;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ Actor *target; // homing target
    /* 0x20 */ u8 groundFrames; // consecutive frames on the floor
} ProjectileState;
void func_800268C0(s32);

void projectileSteerTowardTarget(collisionMask, proj, trailEffect, straight)
u16 collisionMask;
Actor *proj;
void *trailEffect;
u8 straight;
{
    PlayerState *ownerState; // named pointer-chain locals: colour the two chain loads into v0/v1
    Actor *target;
    s16 targetYaw;
    s16 yawStep;
    s16 pad74;
    s16 yawPlus;
    s16 yawMinus;
    s16 plusDist;
    f32 dx;
    f32 dz;
    f32 dist;
    f64 pad58;
    CamState *camState;
    ProjectileState *homing;
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    f32 heightOffset;
    f32 steps;

    homing = proj->customState;
    if (!(proj->speedXZ < 0.1)) {
        if (trailEffect != 0) {
            ownerState = proj->parentActor->customState;
            camState = ownerState->camActor->customState;
            if (camState->mode == 3) {
                effectSetCallback(effectLifetimeCountdownUpdate);
                effectSetSpeed(0x32);
                effectCreateAtPosition(trailEffect, homing->scale, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        if (projectileFindHomingTarget(collisionMask, &target, proj, 0, straight, straight == 0, &targetX, &targetY, &targetZ) != 0) {
            targetYaw = mathAngleBetweenPoints2D(targetX, targetZ, proj->x, proj->z);
            yawStep = mathAngleDistance(targetYaw, proj->moveYaw) / 10;
            yawPlus = (proj->moveYaw + yawStep) & 0xFFF;
            yawMinus = (proj->moveYaw - yawStep) & 0xFFF;
            plusDist = mathAngleDistance(yawPlus, targetYaw);
            if (plusDist < mathAngleDistance(yawMinus, targetYaw)) {
                proj->moveYaw = yawPlus;
            } else {
                proj->moveYaw = yawMinus;
            }
            if (!straight) {
                dx = targetX - proj->x;
                dz = targetZ - proj->z;
                dist = sqrtf((dx * dx) + (dz * dz));
                if (dist < 100.0f) {
                    homing->target = target;
                    if ((target != NULL) && (gGlobalOverlayFlags & 0x04000000)) {
                        func_800268C0(0x80);
                    }
                }
                steps = dist / (proj->speedXZ * 0.025f);
                if (target != NULL) {
                    heightOffset = target->eyeHeight * 0.5;
                } else {
                    heightOffset = 0.0f;
                }
                proj->speedY = (((targetY + heightOffset) - proj->y) / steps) / 0.025f;
            }
        } else if (homing->target != NULL) {
            if (gGlobalOverlayFlags & 0x04000000) {
                func_800268C0(4);
            }
            homing->target = NULL;
        }
    }
}

extern ModelSlot *gModelSlots;
extern s32 gModelSlotCount;

s32 projectileFindHomingTarget(u16 collisionMask, Actor **outTarget, Actor *proj, u8 useAim, u8 levelOnly, u8 includeModels, f32 *outX, f32 *outY, f32 *outZ) {
    s32 padTop[2];
    s32 ret;
    s32 i;
    Actor *actor;
    u8 active;
    s32 j;
    s32 pad;
    u8 idx;
    PlayerState *playerState;
    f32 delta[3];
    f32 toTarget[3];
    f32 padA4[1];
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    f32 pad94[1];
    f32 best;
    f32 pad8C[1];
    f32 ox;
    f32 oy;
    f32 oz;
    f32 px;
    f32 py;
    f32 pz;
    f32 aimX;
    f32 aimY;
    f32 aimZ;
    f32 scale;
    f32 len;
    f32 dot;
    f32 targetDy;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d2x;
    f32 d2z;
    f32 targetY;

    ret = 0;
    best = 0.7f;
    if (useAim) {
        best = 0.92f;
    }
    *outTarget = NULL;
    if (useAim) {
        idx = ((PlayerState *)proj->customState)->playerIndex;
        aimX = gPlayerSlots[idx].focusX;
        aimY = gPlayerSlots[idx].focusY;
        aimZ = gPlayerSlots[idx].focusZ;
        ox = gPlayerSlots[idx].camX;
        oy = gPlayerSlots[idx].camY;
        oz = gPlayerSlots[idx].camZ;
    } else {
        scale = proj->speedXZ * 0.025f;
        aimX = mathSinF(proj->moveYaw) * scale + proj->x;
        aimZ = mathCosF(proj->moveYaw) * scale + proj->z;
        aimY = proj->y + proj->speedY * 0.025f;
        ox = proj->x;
        oy = proj->y;
        oz = proj->z;
    }
    delta[0] = aimX - ox;
    delta[1] = aimY - oy;
    delta[2] = aimZ - oz;
    len = sqrtf((delta[0] * delta[0] + delta[1] * delta[1]) + delta[2] * delta[2]);
    if (len == 0.0) {
        len = 0.1f;
    }
    dirX = delta[0] / len;
    dirY = delta[1] / len;
    dirZ = delta[2] / len;
    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (proj != actor && (!(actor->collisionFlags & 2) || actor->state != 0x37) && (actor->collisionFlags & collisionMask)) {
            if (levelOnly == 0 || ((oy < actor->y) ? (actor->y - oy) : -(actor->y - oy)) < 30.0f) {
                active = 1;
                if (actor->collisionFlags & 1) {
                    playerState = actor->customState;
                    active = gPlayerSlots[playerState->playerIndex].active;
                }
                if (active != 0) {
                    targetY = (f32)((f64)actor->y + (f64)actor->eyeHeight * 0.5);
                    delta[0] = actor->x - ox;
                    targetDy = targetY - oy;
                    delta[1] = targetDy;
                    delta[2] = actor->z - oz;
                    len = sqrtf((delta[0] * delta[0] + delta[1] * delta[1]) + delta[2] * delta[2]);
                    if (len == 0.0) {
                        len = 0.1f;
                    }
                    toTarget[0] = delta[0] / len;
                    toTarget[1] = delta[1] / len;
                    toTarget[2] = delta[2] / len;
                    dot = (toTarget[0] * dirX + toTarget[1] * dirY) + toTarget[2] * dirZ;
                    if (dot < 0.0) {
                        dot = 0.0f;
                    }
                    if (best < dot) {
                        d2x = actor->x - ox;
                        d2z = actor->z - oz;
                        if (sqrtf(d2x * d2x + targetDy * targetDy + d2z * d2z) < 1000.0f) {
                            best = dot;
                            *outTarget = actor;
                            ret = 1;
                            *outX = actor->x;
                            *outY = actor->y;
                            *outZ = actor->z;
                        }
                    }
                }
            }
        }
    }
    if (includeModels != 0) {
        if (gModelSlotCount > 0) {
            j = 0; do { // LAYOUT: init and do on one line (one as1 line) steers the loop-limit candidate priority
                switch (gModelSlots[j].modelType) {
                    case 0x125:
                    case 0x126:
                    case 0x127:
                    case 0x128:
                    case 0x129:
                        px = gModelSlots[j].x;
                        py = gModelSlots[j].y + 10.0;
                        pz = gModelSlots[j].z;
                        dx = px - ox;
                        dy = py - oy;
                        dz = pz - oz;
                        delta[0] = dx;
                        delta[1] = dy;
                        delta[2] = dz;
                        len = sqrtf((delta[0] * delta[0] + delta[1] * delta[1]) + delta[2] * delta[2]);
                        if (len == 0.0) {
                            len = 0.1f;
                        }
                        toTarget[0] = delta[0] / len;
                        toTarget[1] = delta[1] / len;
                        toTarget[2] = delta[2] / len;
                        dot = (toTarget[0] * dirX + toTarget[1] * dirY) + toTarget[2] * dirZ;
                        if (dot < 0.0) {
                            dot = 0.0f;
                        }
                        if (best < dot && sqrtf(dx * dx + dy * dy + dz * dz) < 800.0f) {
                            best = dot;
                            *outTarget = NULL;
                            *outX = px;
                            *outY = py;
                            ret = 1;
                            *outZ = pz;
                        }
                        break;
                    default:
                        break;
                }
                j++;
            } while (j < gModelSlotCount);
        }
    }
    return ret;
}

extern s32 sEffectSparkConfig;
void actorSpawnSparkleBurst(void) {
    s32 count;
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;

    if (gMultiplayerReducedEffects != 0) {
        count = 3;
    } else {
        count = 6;
    }
    for (i = 0; i < count; i++) {
        dx = (f32)(((f64)(u32)((randomLcgNext() / 10000) % 200) / 5.0) - 20.0);
        dy = (f32)(((f64)(u32)((randomLcgNext() / 10000) % 200) / 5.0) - 20.0);
        dz = (f32)(((f64)(u32)((randomLcgNext() / 10000) % 200) / 5.0) - 20.0);
        effectSetDepth(1);
        effectSetColor(0x8C, 0x8C, 0x8C, 0x64);
        effectSetSpeed(i * -0x14);
        effectSetFrameDelay(3);
        effectSetCallback(effectSinkBySpeedUpdate);
        effectCreateAtPosition(&sEffectSparkConfig, 2.0f, gCurrentActor->x + dx, gCurrentActor->y + 42.0f + dy, gCurrentActor->z + dz);
    }
}

void projectileSpawnWithShockwave(s16 pitch, f32 scale, u8 red, u8 green, u8 blue, u8 alpha, f32 growth, f32 rippleSize, f32 rippleSpeed, f32 rippleDecay) {
    actorSpawn(0x102, pitch);
    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, scale);
    gSpawnedActor->movePitch = pitch;
    gSpawnedActor->tintR = red;
    gSpawnedActor->tintG = green;
    gSpawnedActor->tintB = blue;
    gSpawnedActor->wavesLeft = alpha;
    gSpawnedActor->yawSpeed = 1;
    gSpawnedActor->splineT = growth;
    if (rippleSize != 0.0f) {
        waterRippleStart(gCurrentActor->x, gCurrentActor->z, rippleSize, 2.0f, rippleSpeed, rippleDecay);
    }
    camStartShake(gCamActor, 0x50, 0x14);
}

void projectileSpawnSpriteRing(u8 mode, u8 value, f32 rate, f32 limit, u8 alpha, u8 spin) {
    ProjectileTrackerState *tracker;

    actorSpawn(0x107, 0);
    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.15f);
    tracker = gSpawnedActor->customState;
    tracker->mode = mode;
    tracker->rate = rate;
    tracker->limit = limit;
    tracker->value = value;
    gSpawnedActor->y = gCurrentActor->meshFloorY;
    gSpawnedActor->ringCountdown = alpha;
    gSpawnedActor->yawSpeed = spin;
}



extern u8 gEffectSpriteExplosion;
extern u8 gEffectSpriteEmber;
extern s16 gProjectileLifetime;

void projectileBounceParticleUpdate(void *effectCfg) {
    f32 radius;
    ProjectileState *state;
    s32 yawOffset;
    u32 radiusPick;
    f32 scale;

    state = gCurrentActor->customState;
    scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->prevPeakY = gCurrentActor->peakY = gCurrentActor->y;
        gCurrentActor->soundSlots[0] = -2;
        gCurrentActor->contactFlags &= ~1;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->yaw = gCurrentActor->moveYaw;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        if (gCurrentActor->parentActor != NULL && gCurrentActor->parentActor->actorType == 0xD2) {
            gCurrentActor->collisionMode = 0x24;
        } else {
            gCurrentActor->collisionMode = 0x3C;
        }
        state->param = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        if (state->param != 0) {
            radiusPick = 0xC8;
        } else {
            radiusPick = 0x3C;
        }
        radius = radiusPick;
        actorSetCollisionRadius(gCurrentActor, radius);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 35.0f, -1);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, radius, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetMaxDistance(1000);
        effectSetFlags(4);
        effectCreateAtActorBone(effectCfg, scale, gCurrentActor, 1, 2);
        if (state->param >= 0xB) {
            gCurrentActor->interactionType = 2;
        }
        state->spawnFrame = gGameFrameCounter;
        if (state->param == 5) {
            state->spawnFrame = state->spawnFrame - gProjectileLifetime + 0x1E;
        }
        state->cooldown = 0;
        gCurrentActor->flags |= 0x80000;
        gCurrentActor->flybySfxStage = 0;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    if (gCurrentActor->collisionMode & 8) {
        actorUpdateFloorContactAndTilt(gCurrentActor, state->param != 0 ? scale * 6.0 * 4.0 : 0.0);
    }
    if (state->param >= 0xA) {
        if (state->param == 0x1E) {
            billboardSetFlags(3);
        }
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x320, 0x78, 0, 1.0f);
        if (gCurrentActor->contactFlags & 1) {
            if (state->cooldown == 0) {
                switch (state->param) {
                case 11:
                    projectileSpawnSpriteRing(0, 0, 5.0f, 2.0f, 1, 0);
                    break;
                case 20:
                    projectileSpawnSpriteRing(1, 7, 5.0f, 3.0f, 0xC8, 0x20);
                    break;
                }
                camStartShake(gCamActor, 0xA, 0x14);
                state->cooldown = 2;
            } else {
                state->cooldown--;
            }
        }
    } else {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x78, 0x78, 0, 1.0f);
        if ((gCurrentActor->contactFlags & 1) && state->cooldown == 0 && (gCurrentActor->collisionMode & 8)) {
            state->cooldown = 0xA;
        }
        if (state->cooldown != 0) {
            effectSetDepth(1);
            effectSetDuration(1);
            effectSetCallback(effectSpinBillboardingUpdate);
            effectCreateAtPosition(&gEffectSpriteExplosion, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            state->cooldown--;
        }
    }
    if (gCurrentActor->flybySfxStage == 0) {
        f32 dist;
        f32 d;

        dist = gCurrentActor->x - gPlayerSlots->camX;
        dist = dist * dist;
        d = gCurrentActor->y - gPlayerSlots->camY;
        dist = dist + d * d;
        d = gCurrentActor->z - gPlayerSlots->camZ;
        dist = dist + d * d;
        if (dist < 20000.0f) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x128, 0xFF, 0x7F, 0);
            gCurrentActor->flybySfxStage++;
        }
    }
    if (gCurrentActor->hasArcBounds != 0 || state->cooldown == 1 || gActorGlobalState.damaged != 0) {
        effectSetDepth(1);
        effectSetDuration(1);
        if (gCurrentActor->actorType != 0x3B && state->param != 0x63) {
            effectSetSpeed(0x100FA);
            effectSetCallback(effectLightPulseOscillate);
        }
        effectCreateAtPosition(&gEffectSpriteExplosion, 2.0 * ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        if (state->param < 0xA) {
            for (yawOffset = -0x12C; yawOffset != 0x12C; yawOffset += 0x32) {
                effectSetDepth(1);
                effectSetDuration(2);
                effectSetSpeed((gCurrentActor->moveYaw + yawOffset) % 4095);
                effectSetCallback(effectRandomPitchDriftUpdate);
                effectCreateAtPosition(&gEffectSpriteEmber, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale * 0.5, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xF6, 0xFF, 0x7F, 0x1E, 0x1E, 0.7f, 0);
        actorDespawn(gCurrentActor);
    }
    if (state->spawnFrame + gProjectileLifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}



extern EffectGridAsset gEffectSpriteFireBurst;
extern EffectGridAsset gEffectSpriteSmokeCloud;

void projectileSparkleUpdate(u8 silver) {
    ProjectileState *state;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->soundSlots[0] = -2;
        gCurrentActor->contactFlags &= ~1;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 40.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 30.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(1);
        effectSetFrameDelay(2);
        effectSetDepth(1);
        effectSetCallback(effectGrowExpandMatrixUpdate);
        effectSetSpeed((randomNonNegative() >> 15) % 360);
        effectSetMaxDistance(2000);
        switch (silver) {
        case 0:
            effectSetColor(0xFF, 0xD7, 0x58, 0xFF);
            effectCreateAtActorBone(&gEffectSpriteFireBurst, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
            break;
        case 1:
            effectSetColor(0xC8, 0xC8, 0xFA, 0x9B);
            effectCreateAtActorBone(&gEffectSpriteSmokeCloud, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
            break;
        }
        state->param = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->spawnFrame = gGameFrameCounter;
        state->cooldown = 0;
        gCurrentActor->flags |= 0x80000;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    if ((gCurrentActor->contactFlags & 1) || (gCurrentActor->hasArcBounds != 0) || (gActorGlobalState.damaged != 0) || (state->spawnFrame + 24 < gGameFrameCounter)) {
        actorDespawn(gCurrentActor);
    }
}

extern u8 gEffectSpriteFlame;

void projectileSparkleUpdateGold(void) {
    projectileSparkleUpdate(0);
}

void projectileSparkleUpdateSilver(void) {
    projectileSparkleUpdate(1);
}

void projectileSpawnParticleEffect(void) {
    projectileBounceParticleUpdate(&gEffectSpriteFlame);
}


extern u8 gEffectSpriteMelonSpin;
extern u8 gEffectSpriteMelonSplat;
extern s16 gCarryMinFallSpeed;
extern f32 gCarryGravity;
extern u8 gEffectSpritePeanutShard;
extern u8 gPlayerCount;
extern u8 gEffectSpriteGrape;
extern u8 gEffectSpriteGrapeShard;
extern s16 gMultiplayerShotLifetime;
extern s16 gMultiplayerShotLongLifetime;


void projectileSpawnParticleEffect2(void) {
    projectileBounceParticleUpdate(&gEffectSpriteFlame);
}

void projectileSpawnParticleEffect3(void) {
    projectileBounceParticleUpdate(&gEffectSpriteFlame);
}

void projectileSpawnParticleEffectWithScale(void) {
    ProjectileState *state;
    f32 minSpeedY;

    state = gCurrentActor->customState;
    projectileBounceParticleUpdate(&gEffectSpriteFlame);
    if (state->param == 1) {
        gCurrentActor->speedY += gCarryGravity;
        minSpeedY = (f32)gCarryMinFallSpeed;
        if (gCurrentActor->speedY < minSpeedY) {
            gCurrentActor->speedY = minSpeedY;
        }
    }
}


void projectileDespawnOrExplode(void) {
    ProjectileState *state;
    u8 arcBounds;
    Actor *parent;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 50.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectCreateAtActorBone(&gEffectSpriteMelonSpin, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->spawnFrame = gGameFrameCounter;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 10, 10, 1, 0x96, 0x78, 0, 1.0f);
    arcBounds = gCurrentActor->hasArcBounds;
    if (arcBounds != 0 || (gCurrentActor->contactFlags & 1) || gActorGlobalState.damaged != 0 || gActorGlobalState.bossFightPhase == 9) {
        parent = gCurrentActor->parentActor;
        if (parent == NULL || parent->actorType != 0x2E || (parent->actorType == 0x2E && (arcBounds != 0 || (gCurrentActor->contactFlags & 1)))) {
            effectSetDepth(0);
            effectSetDuration(1);
            effectSetCallback(effectLifetimeCountdownUpdate);
            effectSetSpeed(0xC);
            effectCreateAtPosition(&gEffectSpriteMelonSplat, 0.75f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x61, 0xFF, 0x7F, 0x1E, 0, 0.0f, 0);
        actorDespawn(gCurrentActor);
    }
    if (state->spawnFrame + gProjectileLifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

extern u8 gEffectSpritePeanut;
extern u8 gEffectSpriteImpactFlash;
extern s16 gHomingShotLifetime;
extern s16 gHomingShotLongLifetime;

void projectileHomingUpdate(void) {
    ProjectileState *state;
    s16 collisionMask;
    u8 hit;
    s32 lifetime;
    s32 i;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 50.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&gEffectSpritePeanut, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->shadowScale[0] = 0x3C;
        gCurrentActor->shadowScale[1] = 0x3C;
        state->param = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = gHomingShotLifetime;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &gEffectSpritePeanut, 0);
    }
    if (state->param & 4) {
        lifetime = gHomingShotLongLifetime;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (gCurrentMap == 0xCC) {
        gCurrentActor->arcSpeedCap = 0x2328;
        hit = gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->moveYaw) == 0;
    } else {
        hit = gCurrentActor->collisionHit;
    }
    if (hit ||
        actorGetFloorSnapped() != 0 ||
        ((gCurrentActor->contactFlags & 1) && collisionGetFloorSource() == 1) ||
        gActorGlobalState.damaged != 0 ||
        (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && state->spawnFrame + 1 < gGameFrameCounter)) {
        effectSetDepth(1);
        effectSetSpeed(0x1006E);
        effectSetCallback(effectLightPulseOscillate);
        effectCreateAtPosition(&gEffectSpriteImpactFlash, 0.45f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8D, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
        if (gMultiplayerReducedEffects == 0) {
            for (i = 0; i != 0xC; i += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + i);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&gEffectSpritePeanutShard, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
    }
    if (gPlayerCount >= 2) {
        lifetime *= 1.4f;
    }
    if (gCurrentMap == 0x10) {
        lifetime *= 1.2;
    }
    if (state->spawnFrame + lifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

void projectileMultiplayerUpdate(void) {
    ProjectileState *state;
    s32 collisionMask;
    s32 lifetime;
    s32 i;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&gEffectSpriteGrape, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->shadowScale[0] = 0x3C;
        gCurrentActor->shadowScale[1] = 0x3C;
        state->param = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = gMultiplayerShotLifetime;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &gEffectSpriteGrape, 0);
    }
    if (state->param & 4) {
        lifetime = gMultiplayerShotLongLifetime;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (gCurrentActor->collisionHit != 0 ||
        actorGetFloorSnapped() != 0 ||
        ((gCurrentActor->contactFlags & 1) && collisionGetFloorSource() == 1) ||
        gActorGlobalState.damaged != 0 ||
        (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && state->spawnFrame + 1 < gGameFrameCounter)) {
        if (gMultiplayerReducedEffects == 0) {
            for (i = 0; i != 0xC; i += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x05000000 + i);
                effectSetFrameDelay(1);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&gEffectSpriteGrapeShard, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x91, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
    }
    if (gPlayerCount >= 2) {
        lifetime *= 1.4f;
    }
    if (state->spawnFrame + lifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

void projectileSpawnExplosion(void) {
    s32 i;

    effectSetDepth(1);
    effectSetSpeed(0x1006E);
    effectSetCallback(effectLightPulseOscillate);
    effectCreateAtPosition(&gEffectSpriteFireBurst, 2.0f, gCurrentActor->x, gCurrentActor->y + 22.0f, gCurrentActor->z);

    for (i = 0; i < gPlayerCount; i++) {
        camStartShakeFromPoint(((PlayerState *)gPlayerSlots[i].actor->customState)->camActor, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
    }

    actorSpawnSparkleBurst();

    if (gMultiplayerReducedEffects == 0) {
        for (i = 0; i < 12; i++) {
            effectSetDepth(1);
            effectSetSpeed(0x0B010000 + i);
            effectSetCallback(effectRadialSprayUpdate);
            effectCreateAtPosition(&gEffectSpritePeanutShard, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
    }

    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF6, 0xFF, 0x7F, 0x1E);
}



extern u8 gEffectSpriteOrangeGrenade;
extern s16 gBounceExplodeLifetime;
extern s16 gBounceExplodeShortLifetime;
extern s8 D_80029FA0;

void projectileBounceExplodeScaledUpdate(void) {
    ProjectileState *state;
    s16 reverseYaw;
    u8 outOfArc;
    u8 shadowScale;
    f32 scale;
    s32 i;
    f32 radius;
    s16 midYaw;
    s16 collisionMask;

    state = gCurrentActor->customState;
    outOfArc = 0;
    scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale * 2.5f;
    if (!(gCurrentActor->flags & 0x10)) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF4, 0xFF, 0x7F, 5);
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ / 4 * 2.6;
        gCurrentActor->speedXZ *= scale;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x3C;
        actorSetCollisionRadius(gCurrentActor, scale * 60.0);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, scale * 50.0, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        state->param = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        effectSetDuration(-1);
        effectSetDepth(1);
        state->spawnFrame = gGameFrameCounter;
        if (state->param >= 0xCA) {
            effectSetSpeed(0xA);
            effectSetCallback(effectLightPulseOscillate);
        }
        if (state->param >= 0xCB) {
            gCurrentActor->speedY = 250.0f * scale;
            state->spawnFrame -= gBounceExplodeLifetime - gBounceExplodeShortLifetime;
        } else {
            gCurrentActor->speedY = 200.0f * scale;
        }
        effectCreateAtActorBone(&gEffectSpriteOrangeGrenade, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->bounceCount = 0;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->arcSpeedCap = 0x2328;
        shadowScale = 60.0f * scale;
        gCurrentActor->shadowScale[0] = shadowScale;
        gCurrentActor->shadowScale[1] = shadowScale;
        state->target = NULL;
        state->groundFrames = 0;
    }
    if (state->spawnFrame + 5 < gGameFrameCounter) {
        gCurrentActor->flags &= ~0x00080000;
    }
    collisionMask = 2;
    if (gPlayerCount >= 2) {
        collisionMask = 3;
    }
    projectileSteerTowardTarget(collisionMask, gCurrentActor, NULL, 1);
    actorUpdatePrevContactFlags(gCurrentActor);
    if (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->moveYaw) == 0) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        midYaw = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax);
        reverseYaw = (gCurrentActor->moveYaw + 0x800) & 0xFFF;
        midYaw += (s16)(midYaw - reverseYaw);
        gCurrentActor->moveYaw = midYaw;
        if (gCurrentActor->moveYaw < 0) {
            gCurrentActor->moveYaw += 0xFFF;
        }
        if (gCurrentActor->moveYaw >= 0x1000) {
            gCurrentActor->moveYaw -= 0xFFF;
        }
        if (actorAngleInArc(gCurrentActor, gCurrentActor->moveYaw) == 0) {
            outOfArc = 1;
        }
    }
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    gCurrentActor->speedY += gCarryGravity * scale;
    if (gCurrentActor->speedY < gCarryMinFallSpeed) {
        gCurrentActor->speedY = gCarryMinFallSpeed;
    }
    if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
        switch (state->bounceCount) {
        case 0:
            gCurrentActor->speedY = 200.0f * scale;
            break;
        case 1:
            radius = 100.0f * scale;
            gCurrentActor->speedY = 150.0f * scale;
            actorSetCollisionRadius(gCurrentActor, radius);
            actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, radius, -1);
            break;
        case 2:
            radius = 150.0f * scale;
            gCurrentActor->speedY = 100.0f * scale;
            actorSetCollisionRadius(gCurrentActor, radius);
            actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, radius, -1);
            break;
        case 3:
            gCurrentActor->speedY = 80.0f * scale;
            break;
        }
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        state->bounceCount++;
        gCurrentActor->speedXZ = gCurrentActor->speedXZ / 3.0 * 2.5;
    }
    if ((gCurrentActor->contactFlags & 1) && (gCurrentActor->prevContactFlags & 1)) {
        state->groundFrames++;
    } else {
        state->groundFrames = 0;
    }
    if (state->groundFrames == 4) {
        gActorGlobalState.damaged = 1;
    }
    if (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && state->spawnFrame + 1 < gGameFrameCounter) {
        gActorGlobalState.damaged = 1;
    }
    if ((gCurrentActor->renderFlags & 0x100) || outOfArc != 0) {
        gActorGlobalState.damaged = 1;
    }
    if ((((gCurrentActor->contactFlags & 1) && state->bounceCount == 4) || gActorGlobalState.damaged != 0) && gCurrentActor->state == 0) {
        radius = 250.0f * scale;
        if (state->param != 0xCA) {
            effectSetDepth(1);
            effectSetSpeed(0x100D2);
            effectSetCallback(effectLightPulseOscillate);
            effectCreateAtPosition(&gEffectSpriteFireBurst, 2.0f, gCurrentActor->x, gCurrentActor->y + 22.0f, gCurrentActor->z);
            actorSpawnSparkleBurst();
            if (gMultiplayerReducedEffects == 0) {
                for (i = 0; i != 12; i++) {
                    effectSetDepth(1);
                    effectSetSpeed(0x0B010000 + i);
                    effectSetCallback(effectRadialSprayUpdate);
                    effectCreateAtPosition(&gEffectSpritePeanutShard, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                }
            }
        }
        for (i = 0; i < gPlayerCount; i++) {
            camStartShakeFromPoint(((PlayerState *)gPlayerSlots[i].actor->customState)->camActor, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
        }
        actorSetCollisionRadius(gCurrentActor, radius);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, radius, -1);
        gCurrentActor->state = 1;
    } else if (gCurrentActor->state != 0) {
        if (gCurrentActor->state++ == 2) {
            if (state->param != 0xCA) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF6, 0xFF, 0x7F, 0x1E);
            }
            actorDespawn(gCurrentActor);
            D_80029FA0--;
        }
    }
    if (state->spawnFrame + gBounceExplodeLifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
        D_80029FA0--;
    }
}


extern s16 gShotLifetime;
extern s16 gShotLongLifetime;

extern u8 gEffectSpritePineapple;


void projectileBounceExplodeGreenUpdate(void) {
    ProjectileState *state;
    s32 pad48;
    u8 outOfArc;
    s32 pad40;
    s16 midYaw;
    f32 minSpeed;

    state = gCurrentActor->customState;
    outOfArc = 0;
    if (!(gCurrentActor->flags & 0x10)) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF4, 0xFF, 0x7F, 5);
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ / 4 * 2.6;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetColor(0, 0xFF, 0, 0xFF);
        effectCreateAtActorBone(&gEffectSpriteOrangeGrenade, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->spawnFrame = gGameFrameCounter;
        state->bounceCount = 0;
        gCurrentActor->flags |= 0x80000;
        gCurrentActor->arcSpeedCap = 0x2328;
        state->param = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        if (state->param == 0x63) {
            state->bounceCount = 2;
        }
        state->target = NULL;
    }
    if (state->spawnFrame + 10 < gGameFrameCounter) {
        gCurrentActor->flags &= 0xFFF7FFFF;
    }
    projectileSteerTowardTarget(1, gCurrentActor, NULL, 1);
    actorUpdatePrevContactFlags(gCurrentActor);
    if (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->moveYaw) == 0) {
        s16 reverseYaw;
        s16 diff;

        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        midYaw = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax);
        reverseYaw = (gCurrentActor->moveYaw + 0x800) & 0xFFF;
        diff = midYaw - reverseYaw;
        gCurrentActor->moveYaw = midYaw + diff;
        if (gCurrentActor->moveYaw < 0) {
            gCurrentActor->moveYaw += 0xFFF;
        }
        if (gCurrentActor->moveYaw >= 0x1000) {
            gCurrentActor->moveYaw -= 0xFFF;
        }
        if (actorAngleInArc(gCurrentActor, gCurrentActor->moveYaw) == 0) {
            outOfArc = 1;
        }
    }
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 10, 10, 1, 0x4B, 0x78, 0, 1.0f);
    gCurrentActor->speedY += gCarryGravity;
    minSpeed = gCarryMinFallSpeed;
    if (gCurrentActor->speedY < minSpeed) {
        gCurrentActor->speedY = minSpeed;
    }
    if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
        switch (state->bounceCount) {
            case 0:
                gCurrentActor->speedY = 200.0f;
                break;
            case 1:
                gCurrentActor->speedY = 150.0f;
                break;
            case 2:
                gCurrentActor->speedY = 100.0f;
                actorSetCollisionRadius(gCurrentActor, 200.0f);
                actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 180.0f, -1);
                break;
            case 3:
                gCurrentActor->speedY = 80.0f;
                break;
        }
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        state->bounceCount++;
        gCurrentActor->speedXZ = gCurrentActor->speedXZ / 3.0 * 2.5;
    }
    if ((gCurrentActor->renderFlags & 0x100) || outOfArc != 0) {
        gActorGlobalState.damaged = 1;
    }
    if (((gCurrentActor->contactFlags & 1) && state->bounceCount == 4) || gActorGlobalState.damaged != 0) {
        projectileSpawnExplosion();
        actorDespawn(gCurrentActor);
    }
    if (state->spawnFrame + gProjectileLifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

void projectileBeamUpdate(void) {
    ProjectileState *state;
    s32 collisionMask;
    s32 lifetime;
    s32 i;
    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&gEffectSpritePineapple, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->shadowScale[0] = 0x3C;
        gCurrentActor->shadowScale[1] = 0x3C;
        state->param = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = gShotLifetime;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &gEffectSpritePineapple, 0);
    }
    if (state->param & 4) {
        lifetime = gShotLongLifetime;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (actorGetFloorSnapped() != 0 ||
        gCurrentActor->collisionHit != 0 ||
        ((gCurrentActor->contactFlags & 1) && collisionGetFloorSource() == 1) ||
        gActorGlobalState.damaged != 0 ||
        (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && state->spawnFrame + 1 < gGameFrameCounter)) {
        effectSetDepth(1);
        effectSetSpeed(0x1006E);
        effectSetCallback(effectLightPulseOscillate);
        effectCreateAtPosition(&gEffectSpriteImpactFlash, 0.45f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1E5, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
        if (gMultiplayerReducedEffects == 0) {
            for (i = 0; i != 0xC; i += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + i);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&gEffectSpritePeanutShard, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
    }
    if (gPlayerCount >= 2) {
        lifetime *= 1.4f;
    }
    if (state->spawnFrame + lifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}


void projectileImpactExplosionUpdate(void) {
    ProjectileState *state;
    s32 collisionMask;
    s32 lifetime;
    u8 exploding;

    state = gCurrentActor->customState;
    exploding = 0;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&gEffectSpriteOrangeGrenade, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->shadowScale[0] = 0x3C;
        gCurrentActor->shadowScale[1] = 0x3C;
        state->param = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = gShotLifetime;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &gEffectSpriteOrangeGrenade, 0);
    }
    if (state->param & 4) {
        lifetime = gShotLongLifetime;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (!gCurrentActor->state && (gCurrentActor->collisionHit != 0 || (gCurrentActor->contactFlags & 1) || gActorGlobalState.damaged != 0)) {
        exploding = 1;
    } else if (gCurrentActor->state) {
        if (gCurrentActor->state++ == 2) {
            actorDespawn(gCurrentActor);
        }
    }
    if (gPlayerCount >= 2) {
        lifetime *= 1.4f;
    }
    if (state->spawnFrame + lifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
    if (exploding != 0) {
        projectileSpawnExplosion();
        actorSetCollisionRadius(gCurrentActor, 250.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 250.0f, -1);
        gCurrentActor->state = 1;
    }
}

extern u8 gEffectSpriteCoconut;
extern EffectGridAsset gEffectSpriteCoconutShard;
extern s16 gCoconutShotLifetime;
extern s16 gCoconutShotLongLifetime;
extern s16 gFeatherShotLifetime;
extern s16 gFeatherShotLongLifetime;


void projectileRotatingUpdate(void) {
    ProjectileState *state;
    s32 collisionMask;
    s32 lifetime;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 50.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&gEffectSpriteCoconut, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->shadowScale[0] = 0x3C;
        gCurrentActor->shadowScale[1] = 0x3C;
        state->param = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = gCoconutShotLifetime;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &gEffectSpriteCoconut, 0);
    }
    if (state->param & 4) {
        lifetime = gCoconutShotLongLifetime;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (gCurrentActor->collisionHit != 0 ||
        actorGetFloorSnapped() != 0 ||
        ((gCurrentActor->contactFlags & 1) && collisionGetFloorSource() == 1) ||
        gActorGlobalState.damaged != 0 ||
        (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && state->spawnFrame + 1 < gGameFrameCounter)) {
        effectSetDepth(1);
        effectSetSpeed(0x1006E);
        effectSetCallback(effectLightPulseOscillate);
        effectCreateAtPosition(&gEffectSpriteImpactFlash, 0.45f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xFF, 0xFF, 0x7F, 5);
        actorDespawn(gCurrentActor);
        if (gMultiplayerReducedEffects == 0) {
            s32 i;
            for (i = 0; i != 0xC; i += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + i);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&gEffectSpriteCoconutShard, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
    }
    if (gPlayerCount >= 2) {
        lifetime *= 1.4f;
    }
    if (state->spawnFrame + lifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

s32 actorIsActiveType2B(Actor *actor) {
    if (actor->actorType != 0x2B) {
        return 1;
    }
    if (actor->state == 0) {
        return 1;
    }
    return 0;
}

void projectileMatrixRotationUpdate(void) {
    ProjectileState *state;
    s32 collisionMask;
    s32 lifetime;
    f32 pitchMtx[4][4];
    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->yaw = gCurrentActor->moveYaw;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x3C;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->shadowScale[0] = 0x3C;
        gCurrentActor->shadowScale[1] = 0x3C;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x404, 0.0f, 1.0f);
        state->pitchDeg = -(mathAtan2(gCurrentActor->speedY, gCurrentActor->speedXZ) * 57.295776f);
        state->counter = 0;
        state->rollDeg = randomLcgNext() % 3600 / 10;
        state->param = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = gFeatherShotLifetime;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, NULL, 0);
    }
    if (state->param & 4) {
        lifetime = gFeatherShotLongLifetime;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    switch (gCurrentActor->state) {
    case 0:
        if (gCurrentActor->collisionHit != 0 || (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && state->spawnFrame + 1 < gGameFrameCounter)) {
            scriptSetActorRampTarget(gCurrentActor, 0.5f, 0.0f);
            controllerAnimSetStateIfChanged(gCurrentActor, 0x406, 0.0f, 0.0f);
            gCurrentActor->speedXZ = 0.0f;
            gCurrentActor->speedY = 0.0f;
            gCurrentActor->state = 1;
            state->counter = 0x3C;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x308, 0xFF, 0x7F, 5);
            if (gMultiplayerReducedEffects != 0) {
                actorDespawn(gCurrentActor);
                return;
            }
        }
        break;
    case 1:
        gCurrentActor->callbackMask = 0;
        gCurrentActor->collisionMode = 1;
        state->spawnFrame = gGameFrameCounter;
        if (!--state->counter) {
            scriptSetActorRampTarget(gCurrentActor, 0.5f, 0.0f);
            controllerAnimSetStateIfChanged(gCurrentActor, 0x405, 0.0f, 10.0f);
            gCurrentActor->state++;
        }
        break;
    case 2:
        gCurrentActor->speedY -= 20.0f;
        if (gCurrentActor->speedY < -150.0f) {
            gCurrentActor->speedY = -150.0f;
        }
        break;
    }
    if (((gCurrentActor->contactFlags & 1) && collisionGetFloorSource() == 1) || gActorGlobalState.damaged != 0) {
        actorDespawn(gCurrentActor);
    }
    if (gPlayerCount >= 2) {
        lifetime *= 1.4f;
    }
    if (state->spawnFrame + lifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
    guRotateF(gCurrentActor->modelMtx, state->rollDeg, 0.0f, 0.0f, 1.0f);
    guRotateF(pitchMtx, state->pitchDeg, 1.0f, 0.0f, 0.0f);
    guMtxCatF(gCurrentActor->modelMtx, pitchMtx, gCurrentActor->modelMtx);
    actorUpdateModelMatrix(gCurrentActor, 1);
}

extern u8 gSparkEffectSprite;

void projectileRotatingLightUpdate(f32 floorOffset, u8 variant) {
    ProjectileState *state;
    s32 pad;
    u8 red;
    u8 green;
    u8 blue;
    f32 pad4C[4][4];
    s32 pad2;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        if (variant == 1) {
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x306, 0xFF, 0x7F, 0, 0, 0.3f, 0);
        }
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->yaw = gCurrentActor->moveYaw;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->interactionType = (u8)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        gCurrentActor->sub4->scaleX = 2.0 * gCurrentActor->sub4->scaleX;
        gCurrentActor->sub4->scaleY = 2.0 * gCurrentActor->sub4->scaleY;
        gCurrentActor->sub4->scaleZ = 2.0 * gCurrentActor->sub4->scaleZ;
        state->pitchDeg = -(mathAtan2(gCurrentActor->speedY, gCurrentActor->speedXZ) * 57.295776f);
        gCurrentActor->collisionMode = 0x3C;
        state->spawnFrame = gGameFrameCounter;
        state->cooldown = 0;
        gCurrentActor->flags |= 0x80000;
        state->counter = 0;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, floorOffset);
    if (variant != 0) {
        if (variant == 1) {
            red = 0xFF;
            green = 0;
            blue = 0;
        }
    } else {
        red = 0xFF;
        green = 0xFF;
        blue = 0xFF;
    }
    lightSetFlags(1);
    lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, 80.0f, 0, red, green, blue);
    if (variant == 1) {
        if (!state->cooldown && ((gCurrentActor->contactFlags & 1) || gCurrentActor->collisionHit != 0 || gActorGlobalState.damaged != 0)) {
            effectSetSpeed(0x1006E);
            effectSetCallback(effectLightPulseOscillate);
            effectCreateAtPosition(&gSparkEffectSprite, 1.2f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            effectSpawnBoneWhite(0, 0, 0.8f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, -0x50);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF6, 0xFF, 0x3F, 0x14);
            state->cooldown = 2;
        } else if (state->cooldown) {
            if (--state->cooldown == 0) {
                actorDespawn(gCurrentActor);
            }
        }
        if (state->spawnFrame + gProjectileLifetime < gGameFrameCounter) {
            actorDespawn(gCurrentActor);
        }
    }
}

void actorApplyTransformAndRender(void) {
    ProjectileState *state;

    state = gCurrentActor->customState;
    projectileRotatingLightUpdate(0.0f, 1);
    matrixMakeRotationX(gCurrentActor->modelMtx, state->pitchDeg);
    actorUpdateModelMatrix(gCurrentActor, 1);
}

extern EffectGridAsset gEffectSpriteBlast;
extern EffectGridAsset gEffectSpriteBubble;
extern EffectGridAsset gEffectSpriteCannonball;



void projectileParticleSpawnerTick(void) {
    ProjectileState *state;
    s32 i;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->arcSpeedCap = 0x270F;
        gCurrentActor->soundSlots[0] = -2;
        gCurrentActor->contactFlags &= ~1;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        state->param = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        gCurrentActor->collisionMode = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 110.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 100.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectCreateAtActorBone(&gEffectSpriteCannonball, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x80000;
        if (state->param != 0xA) {
            effectSetFrameDelay(2);
            effectSetDepth(1);
            effectCreateAtPosition(&gEffectSpriteBlast, 1.5f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 14, 14, 1, 150, 120, 0, 1.0f);
    if (gCurrentActor->contactFlags & 4) {
        effectSetDepth(1);
        effectSetDuration(-1);
        effectSetCallback(effectProjectileDriftUpdate);
        effectSetSpeed((s32)gCurrentActor);
        effectCreateAtPosition(&gEffectSpriteBubble, 0.3f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    }
    if (((gCurrentActor->hasArcBounds != 0) && ((gGameFrameCounter - state->spawnFrame) >= 6)) || gActorGlobalState.damaged != 0) {
        if ((gActorGlobalState.damaged != 0) && (state->param != 0xA)) {
            effectSetDepth(1);
            effectSetSpeed(0x100D2);
            effectSetCallback(effectLightPulseOscillate);
            effectCreateAtPosition(&gEffectSpriteFireBurst, 2.0f, gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z);
            camStartShakeFromPoint(((PlayerState *)gPrimaryPlayerActor->customState)->camActor, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
            actorSpawnSparkleBurst();
            for (i = 0; i != 12; i += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + i);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&gEffectSpriteCoconutShard, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        if (state->param != 0xA) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3C, 0xFF, 0x7F, 0x1E);
        }
        actorDespawn(gCurrentActor);
    }
    if (state->spawnFrame + gProjectileLifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}




void projectileHomingParticleUpdate(void) {
    ProjectileState *state;
    f32 jitterX;
    f32 jitterY;
    f32 jitterZ;
    f32 minSpeed;
    s32 i;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->arcSpeedCap = 0x270F;
        gCurrentActor->soundSlots[0] = -2;
        gCurrentActor->contactFlags &= ~1;
        gCurrentActor->moveYaw = (((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 0x1C;
        actorSetCollisionRadius(gCurrentActor, 110.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 100.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectCreateAtActorBone(&gEffectSpriteCannonball, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x80000;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    gCurrentActor->speedY += sProjectileGravity;
    minSpeed = gCarryMinFallSpeed;
    if (gCurrentActor->speedY < minSpeed) {
        gCurrentActor->speedY = minSpeed;
    }
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 14, 14, 1, 150, 120, 0, 1.0f);
    if ((gCurrentActor->contactFlags & 1) || ((gCurrentActor->hasArcBounds != 0) && ((gGameFrameCounter - state->spawnFrame) >= 6)) || gActorGlobalState.damaged != 0) {
        for (i = 0; i != 16; i += 2) {
            jitterX = ((randomNonNegative() >> 15) % 8191 / 200.0) - 20.0;
            jitterY = ((randomNonNegative() >> 15) % 8191 / 200.0) - 20.0;
            jitterZ = ((randomNonNegative() >> 15) % 8191 / 200.0) - 20.0;
            effectSetStartDelay(i);
            effectSetDepth(1);
            if (i == 0) {
                effectSetSpeed(0x1006E);
                effectSetCallback(effectLightPulseOscillate);
            } else {
                effectSetCallback(effectSinkBySpeedUpdate);
                effectSetSpeed(-150 - ((randomNonNegative() >> 15) % 50));
            }
            effectCreateAtPosition(&gEffectSpriteExplosion, 1.6f, gCurrentActor->x + jitterX, gCurrentActor->y + jitterY, gCurrentActor->z + jitterZ);
        }
        camStartShake(gCamActor, 20, 15);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3C, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
    }
    if (state->spawnFrame + gProjectileLifetime < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}


extern f32 gDefaultAccelY;
extern PlayerState *gActivePlayerState;

void projectileFallBounceUpdate(void) {
    u32 *spawnFrame;
    s16 i;
    u8 floorType;
    u8 floorFlags;
    u8 floorMisc;
    f32 floorY;
    f32 floorNormal;
    s32 onGround;
    f64 rollStep;
    PlayerState *sub;
    u8 bounces;
    f64 rollSpeed;
    f32 value;

    spawnFrame = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        value = gCurrentActor->y;
        gCurrentActor->peakY = value;
        gCurrentActor->prevPeakY = value;
        if (gGlobalOverlayFlags & 0x80000) {
            gCurrentActor->collisionMode = 0x3C;
        } else {
            gCurrentActor->collisionMode = 0x1C;
        }
        *spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x80000;
        collisionQueryActorFloor(gCurrentActor, &floorType, &floorY, &floorFlags, &floorNormal, floorMisc);
        gCurrentActor->accelY = gDefaultAccelY - (f32)(((randomNonNegative() >> 15) % 32767) % 10);
        gCurrentActor->contactFlags &= 0xFFFE;
    }
    if (gActorGlobalState.bossFightPhase == 5) {
        sub = gActorGlobalState.targetActor->customState;
        if (sub->actor != NULL && (sub->actor->actorType == 0x1D || sub->actor->actorType == 0x50)) {
            camStartShake(sub->camActor, 0xA, 0x14);
            playerStateQueueCallback(0x34, gCurrentActor, 0);
            effectSpawnScatterRandom(&sEffectSparkConfig, 0, 1.0f, 4, 0x14, 0x96, (s32)gCurrentActor->x, (s32)gCurrentActor->y, (s32)gCurrentActor->z);
            actorDespawn(gCurrentActor);
        }
    } else {
        for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
            if (gActorGlobalState.volumeTriggerQueueOp[i] == 1) {
                gCurrentActor->state = 1;
            }
        }
        if (gCurrentActor->state == 1) {
            collisionSetQueryMode(1);
            actorUpdatePrevContactFlags(gCurrentActor);
            actorApplyVelocity(gCurrentActor);
            actorUpdateFloorContactAndTilt(gCurrentActor, (f32)(((f64)mathCosF((s16)(gCurrentActor->roll + 0x800)) * 0.5 + 0.5) * 15.0));
            onGround = gCurrentActor->contactFlags & 1;
            if (onGround != 0 && !(gCurrentActor->prevContactFlags & 1)) {
                bounces = gCurrentActor->subState;
                if (bounces < 2) {
                    gCurrentActor->subState = bounces + 1;
                    gCurrentActor->speedY = (f32)((f64)(gCurrentActor->prevPeakY - gCurrentActor->y) * 1.5);
                    camStartShake(gActivePlayerState->camActor, 0xA, 0x14);
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1C1, 0xFF, 0x7F, 0x1E);
                    effectSpawnScatterRandom(&sEffectSparkConfig, 0, 1.0f, 4, 0x14, 0x96, (s32)gCurrentActor->x, (s32)gCurrentActor->y, (s32)gCurrentActor->z);
                    onGround = gCurrentActor->contactFlags & 1;
                }
            }
            if (onGround == 0) {
                rollSpeed = (f64)gCurrentActor->speedY * 0.5;
                if (rollSpeed > 0.0) {
                    rollStep = rollSpeed;
                } else {
                    rollStep = -rollSpeed;
                }
                gCurrentActor->roll = (s16)(s32)((f64)gCurrentActor->roll - rollStep);
            }
            gCurrentActor->speedY = gCurrentActor->speedY + gCurrentActor->accelY;
            value = (f32)gCarryMinFallSpeed;
            if (gCurrentActor->speedY < value) {
                gCurrentActor->speedY = value;
            }
        }
        value = gCurrentActor->sub4->scaleY * 300.0f;
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, (s16)(s32)value, (s16)(s32)value, 1, 0x96, 0x96, 0, 1.0f);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}




void projectileChaseTargetUpdate(void) {
    ProjectileState *state;
    s16 targetYaw;
    s16 yawDiff;
    Actor *parent;

    state = gCurrentActor->customState;
    projectileRotatingLightUpdate(15.0f, 0);
    if (gCurrentMap == 0x6F) {
        if (gCurrentActor->y < gCurrentActor->waterY) {
            gCurrentActor->y = gCurrentActor->waterY;
            gCurrentActor->speedY = gCurrentActor->accelY;
        }
    }
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 100, 100, 1, 0x4B, 0x78, 0, 1.0f);
    if (!(gCurrentActor->flags & 0x10)) {
        state->baseSpeed = gCurrentActor->speedXZ;
        gCurrentActor->drawDistance = 1000;
        gCurrentActor->flags |= 0x400;
        state->spawnFrame += 0x78;
        if (gCurrentActor->soundSlots[0] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x114, 0x1E, 1, 0, 0xFF, 1.0f, 0);
            gSfxVoicePitch[gSfxSourceVoice[gCurrentActor->soundSlots[0]]] = 0.75f;
            gSfxVoiceModCounter[gSfxSourceVoice[gCurrentActor->soundSlots[0]]] = 1.0f;
        }
        state->counter = 0xF;
        state->tick = 0;
        actorSetUniformScale(gCurrentActor, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale * 0.15);
    }
    state->tick++;
    if (state->counter < state->tick) {
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x15B, 0xFF, 0x6E, 0, 0x1E, 0.3f, 0);
        state->tick = 0;
        if (state->counter >= 3) {
            state->counter--;
        }
    }
    if (state->spawnFrame - 100 < gGameFrameCounter) {
        gCurrentActor->flags &= ~0x80000;
    }
    if ((state->spawnFrame + gProjectileLifetime < gGameFrameCounter) || ((gCurrentActor->collisionHit != 0) && (gCurrentActor->actorType != 0xA9)) || (gActorGlobalState.damaged != 0)) {
        tagBarrelSpawnActorSmokePuffs(0, 1);
        sfxStopSlotSound(gCurrentActor, 0);
        actorDespawn(gCurrentActor);
        parent = gCurrentActor->parentActor;
        if (parent != NULL && parent->actorType == 0xB9 && parent->state != 0x37) {
            parent->subState++;
        }
    }
    targetYaw = mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->z);
    if (targetYaw < gCurrentActor->yaw) {
        yawDiff = gCurrentActor->yaw - targetYaw;
    } else {
        yawDiff = targetYaw - gCurrentActor->yaw;
    }
    gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, targetYaw, 10.0f);
    switch (gCurrentActor->state) {
    case 0:
        if (yawDiff > 1000) {
            gCurrentActor->state = 1;
            gCurrentActor->subState = 0;
        }
        /* fallthrough */
    case 2:
        if (gCurrentActor->state == 2) {
            if (gCurrentActor->speedXZ > 100.0f) {
                gCurrentActor->state = 0;
            }
        }
        if (gCurrentActor->speedXZ + 20.0f < state->baseSpeed) {
            gCurrentActor->speedXZ += 20.0f;
        } else {
            gCurrentActor->speedXZ = state->baseSpeed;
        }
        gCurrentActor->moveYaw = mathAngleEaseToward(gCurrentActor->moveYaw, gCurrentActor->yaw, 1.0f);
        gCurrentActor->movePitch = mathAngleEaseToward(gCurrentActor->movePitch, mathCalculatePitchAngle(gPrimaryPlayerActor->x, gPrimaryPlayerActor->y + gPrimaryPlayerActor->eyeHeight, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 20) * 2048.0 / 3.1415927410125732, 30.0f);
        gCurrentActor->speedY = mathSinF(gCurrentActor->movePitch) * -gCurrentActor->speedXZ;
        state->pitchDeg = -(mathAtan2(gCurrentActor->speedY, gCurrentActor->speedXZ) * 57.295776f);
        break;
    case 1:
        if (gCurrentActor->speedXZ - 10.0f > 5.0f) {
            gCurrentActor->speedXZ -= 10.0f;
        } else {
            gCurrentActor->speedXZ = 5.0f;
        }
        if (gCurrentActor->speedXZ <= 5.0f) {
            gCurrentActor->state = 2;
            gCurrentActor->subState = 0;
        }
        break;
    }
    if (gCurrentActor->actorType == 0x59) {
        effectSetDepth(1);
        effectSetCallback(effectFollowParentUpdate);
        effectSetMaxDistance(1000);
        effectSetSpeed((s32)gCurrentActor);
        effectCreateAtActorBone(&gEffectSpriteFireBurst, 1.0f, gCurrentActor, 1, 0);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}



void projectileChaseReflectUpdate(void) {
    s16 midYaw;
    s16 t;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->arcSpeedCap = 0x2328;
    }
    projectileChaseTargetUpdate();
    if (!gCurrentActor->hasArcBounds) {
        return;
    }
    if (actorAngleInArc(gCurrentActor, gCurrentActor->moveYaw)) {
        return;
    }
    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
    midYaw = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax);
    t = gCurrentActor->moveYaw;
    t = (t + 0x800) & 0xFFF;
    gCurrentActor->moveYaw = midYaw + (s16)(midYaw - t);
}

void actorAppendActiveCallback8(void) {
    s16 i;

    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;

        if (actor->collisionFlags & 4) {
            actorAppendCallback(actor, gCurrentActor, 8, 0, 0, NULL);
        }
    }
}
