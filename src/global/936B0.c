#include "common.h"

#include "actor.h"
#include "race.h"
#include "sched.h"
#include "proto/global/103AB0.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17800.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/63EC0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/80150.h"
#include "proto/global/89250.h"
#include "proto/global/8CA50.h"
#include "proto/global/8D3E0.h"
#include "proto/global/936B0.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/FCCD0.h"

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
extern u8 D_80720054;

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
            effectCreateAtActorBone(&D_80720054, vol, gCurrentActor, node, 2);
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

void func_8068EF54(void) {
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
        buf->rotX = playerState->unk1A0;
        if ((owner->contactFlags & 5) || playerState->unk240 == 1 || (owner->state == 0x42 && playerState->hitActorType != 0x31) || owner->state == 0x87) {
            actorAppendCallback(link->notifyActor, gCurrentActor, 0x2000000, 0, 0, 0);
            playerState->isHoldingObject = 0;
            actorDespawn(gCurrentActor);
            sfxStopChannel(0x48, 0);
            sfxStopSlotSound(gActivePlayerActor, 0);
            slotQueueCancel(5, 0);
            playerState->unk240 = 0;
            if (!(playerState->stateFlags2 & 4)) {
                playerKongStopSoundByState(owner);
            }
        }
        if (playerState->unk1A2 != 0 || (camIsCutsceneActive() && gFrameCounter % 5 == 0)) {
            ratio = (0, owner->speedY > 0.0 ? owner->speedY : 0.0);  // FAKE: comma steers FP candidate order
            if (gFrameCounter & 1) {
                effectSpawnActorBone(owner, 1, (f32)(ratio / 150.0 * 0.12) + 0.3);
            } else {
                effectSpawnActorBone(owner, 2, (f32)(ratio / 150.0 * 0.12) + 0.3);
            }
            playerState->unk1A2 = 0;
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



extern s16 D_8075033C;
extern u32 gGlobalOverlayFlags;
void func_8002F490(void *);


void vehicleUpdateMotion(vehicle, motion, applyBuoyancy, tilt)
RaceParticipant *vehicle;
VehicleMotion *motion;
u8 applyBuoyancy;
u8 tilt;
{
    f32 tmpA;
    s32 kongState;
    f32 drag;
    f32 turnRate;
    f32 tmpB;
    s16 tiltPitch;
    s16 tiltRoll;
    u8 fl[4]; // FAKE: flag array keeps fl[2]/fl[3] memory-resident (sb/lbu at sp) instead of two register locals
    f32 velX;
    f32 velZ;
    f32 thrust;
    s16 slopeAngle;
    s16 slopeRange;
    Actor *pl;

    pl = gPlayerSlots[vehicle->playerIdx].actor;
    kongState = pl->actorType;
    tiltPitch = 0;
    tiltRoll = 0;
    fl[3] = gCurrentActor->y <= gCurrentActor->waterY + 1.0f;
    fl[2] = gCurrentActor->contactFlags & 1;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x10400;
        gCurrentActor->state = 0;
        gCurrentActor->unk155 = 0;
        gCurrentActor->speedXZ = 0.0f;
        vehicle->raceStatus = 0;
        vehicle->unk35 = 0;
        if (vehicle->isCpu == 0) {
            gCurrentActor->unk144 = 0x3C;
            gCurrentActor->accelY = -20.0f;
        } else {
            gCurrentActor->unk144 |= 0x18;
            gCurrentActor->accelY = -30.0f;
        }
        gCurrentActor->terminalSpeedY = -900.0f;
        gCurrentActor->unkF8 = 0x12C;
    }
    velX = mathSinF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ;
    velZ = mathCosF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ;
    if (fl[3] != 0) {
        thrust = vehicle->throttle * 50.0f;
        if (kongState == 2) {
            tmpA = 5000.0f;
        } else {
            tmpA = 10000.0f;
        }
        drag = 1.0f / tmpA * (gCurrentActor->speedXZ * gCurrentActor->speedXZ) + vehicle->brake;
        if (vehicle->throttle != 0.0f) {
            drag = drag + 30.0f;
        } else {
            drag = drag + 3.0f;
        }
    } else {
        tmpB = 2.0f;
        if (fl[2] != 0) {
            thrust = vehicle->throttle * 4.0f;
            drag = vehicle->brake + gCurrentActor->speedXZ * gCurrentActor->speedXZ * 0.00002f + tmpB;
        } else {
            thrust = vehicle->throttle * tmpB;
            drag = vehicle->brake + gCurrentActor->speedXZ * gCurrentActor->speedXZ * 0.00002f + tmpB;
        }
    }
    velX += mathSinF(vehicle->heading) * thrust;
    velZ += mathCosF(vehicle->heading) * thrust;
    gCurrentActor->speedXZ = sqrtf(velX * velX + velZ * velZ);
    gCurrentActor->moveYaw = (mathAtan2(velX, velZ) * 4096.0 / 6.2831854820251465);
    if (fl[2] != 0) {
        slopeRange = 0x400 - gCurrentActor->floorSlopePitch;
        slopeAngle = mathAngleSignedDistance(gCurrentActor->floorSlopeYaw, vehicle->heading);
        tmpB = slopeRange;
        tiltPitch = (mathCosF(slopeAngle) * tmpB);
        tiltRoll = (mathSinF(slopeAngle) * tmpB);
    } else if (!tilt) {
        gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, 0, 4.0f);
        gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, 0, 5.0f);
    }
    turnRate = vehicle->steerGain * vehicle->steer;
    if (tilt) {
        tiltRoll = tiltRoll + turnRate * 200.0f;
        tiltRoll &= 0xFFF;
        if (fl[3] != 0 || fl[2] != 0) {
            tiltPitch = tiltPitch + (vehicle->throttle * -50.0f + gCurrentActor->speedXZ * -0.5);
            tiltPitch &= 0xFFF;
        } else {
            tiltPitch = gCurrentActor->roll;
        }
        gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, tiltPitch, 4.0f);
        gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, tiltRoll, 5.0f);
    }
    gCurrentActor->speedXZ = gCurrentActor->speedXZ - drag;
    velX = gCurrentActor->speedXZ;
    if (velX < 0.0f) {
        gCurrentActor->speedXZ = 0.0f;
        velX = gCurrentActor->speedXZ;
    }
    tmpB = velX - gCurrentActor->prevSpeedXZ;
    if (tmpB < 0.0f) {
        tmpB = 0.0f;
    }
    if (kongState == 2) {
        tiltRoll = -0x1E;
    } else {
        if (tiltRoll && tiltRoll) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        tiltRoll = -0x28;
    }
    vehicle->heading = vehicle->heading + turnRate * tiltRoll * (1.0 + tmpB * 0.05);
    vehicle->heading = vehicle->heading & 0xFFF;
    if (applyBuoyancy) {
        tmpA = gCurrentActor->y;
        drag = gCurrentActor->waterY;
        if (tmpA < drag) {
            if (fl[3] != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            gCurrentActor->speedY = gCurrentActor->speedY + ((gCurrentActor->waterY - tmpA) * 3.0f + 15.0f);
            tmpB = gCurrentActor->speedY;
            if (tmpB > 0.0f) {
                tmpA = tmpB;
            } else {
                tmpA = -tmpB;
            }
            if (tmpA > 20.0f) {
                gCurrentActor->speedY = tmpB - tmpB / 12.0f;
            }
        }
    }
    gCurrentActor->speedY = gCurrentActor->speedY + gCurrentActor->accelY;
    if (motion->jumpQueued != 0) {
        motion->jumpQueued = 0;
        if (fl[3] != 0) {
            if (kongState == 2) {
                gCurrentActor->speedY = 200.0f;
            } else {
                gCurrentActor->speedY = D_8075033C;
            }
        } else if (fl[2] != 0) {
            gCurrentActor->speedY = gCurrentActor->speedY + 200.0f;
        }
    }
    tmpB = gCurrentActor->terminalSpeedY;
    if (gCurrentActor->speedY < tmpB) {
        gCurrentActor->speedY = tmpB;
    }
    if (kongState == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
    if (fl[2] != 0 && !(gCurrentActor->prevContactFlags & 1)) {
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

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void vehicleUpdateEngineSound(vehicle, motion)
RaceParticipant *vehicle;
VehicleMotion *motion;
{
    s16 idx;

    idx = D_80770628[gCurrentActor->soundSlots[0]];
    if (gCurrentActor->y < gCurrentActor->waterY + 4.0f) {
        D_80770B68[idx] = gCurrentActor->speedXZ / 300.0 + 1.0;
        D_80770BC0[idx] = 1.0f;
    } else {
        D_80770B68[idx] = vehicle->throttle + 1.2;
        D_80770BC0[idx] = 5.0f;
    }

    idx = D_80770628[gCurrentActor->soundSlots[1]];
    if (gCurrentActor->y < gCurrentActor->waterY + 4.0f) {
        if (D_80770BC0[idx] == 0.0f) {
            D_80770B68[idx] = ((u32)randomLcgNext() / 4294967295.0 * 0.05 + 0.975) * (0.2 + gCurrentActor->speedXZ / 300.0);
            D_80770BC0[idx] = 1.0f;
        }
    } else {
        D_80770B68[idx] = vehicle->throttle * 1.5 + 0.2;
        D_80770BC0[idx] = 8.0f;
    }
}


void actorInitFromSpawnPoint(Actor *actor, RaceParticipant *vehicle) {
    G01Pos *spawn;
    s16 yaw;

    spawn = func_806C96C4(vehicle->place);
    actor->x = spawn->unk0;
    actor->y = spawn->unk2;
    actor->z = spawn->unk4;
    yaw = (u32)spawn->unk6 * 16.062746f;
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
    vehicle->unk35 = 0;
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
extern f32 D_80750300;
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
    if (gGameMode == 0 && camState->unkF3 != 4) {
        camSetTargetScaled(playerState->camActor, gCurrentActor, 4, 0x800, 0xA0, 0, 6, 0x12C, 0x8F, 0, 0.2f);
    }
    vehicleUpdateMotion(vehicle, motion, 1, 1);
    actorInterpolateAngles(resetting, vehicle, motion);
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->accelY = D_80750300;
        gCurrentActor->unk144 = 0x3C;
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

extern u8 sProjectileShortLivedFlag;
void projectileSetSpawnFlag(void) {
    sProjectileShortLivedFlag = 1;
}

extern f32 D_807FC7B0;
extern f32 D_807FC7B4;
extern f32 D_807FC7B8;
void projectileSetTargetCoords(f32 x, f32 y, f32 z) {
    D_807FC7B0 = x;
    D_807FC7B4 = y;
    D_807FC7B8 = z;
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
extern Actor *gCamActor;
extern u8 D_80750AD0;

void projectileGetTargetCoords(Actor *actor, s32 node) {
    actorGetNodePos(actor, node, &D_807FC7B0, &D_807FC7B4, &D_807FC7B8);
}

void projectileSpawnNodeEntry(s16 type, s16 param, f32 speed, s16 yaw, f32 horizSpeed, f32 vertSpeed, Actor *owner) {
    ProjectileSpawnParams params;

    params.angle = (f32)(((f64)yaw / 4095.0) * 6.28318548202514648);
    params.speedXZ = horizSpeed;
    params.scale = speed;
    params.speedY = vertSpeed;
    params.param = (f32)param;
    params.shortLived = (f32)(u32)sProjectileShortLivedFlag;
    actorListSpawnNodeEntry(type, D_807FC7B0, D_807FC7B4, D_807FC7B8, 0, speed, owner, &params);
    sProjectileShortLivedFlag = 0;
}

void projectileCalculateTrajectoryAndSpawn(s16 yaw, s16 type, s16 param, f32 speed, f32 targetX, f32 targetY, f32 targetZ, f32 flightTime, Actor *owner) {
    f32 dist;
    f32 dy;

    dist = sqrtf(((targetX - D_807FC7B0) * (targetX - D_807FC7B0)) + ((targetY - D_807FC7B4) * (targetY - D_807FC7B4)) + ((targetZ - D_807FC7B8) * (targetZ - D_807FC7B8)));
    dy = targetY - D_807FC7B4;
    projectileSpawnNodeEntry(type, param, speed, yaw, sqrtf(((targetX - D_807FC7B0) * (targetX - D_807FC7B0)) + ((targetZ - D_807FC7B8) * (targetZ - D_807FC7B8))) / (dist / flightTime), dy / (dist / flightTime), owner);
}

void projectileAimAndSpawn(s16 type, s16 param, f32 speed, f32 targetX, f32 targetY, f32 targetZ, f32 flightTime, Actor *owner) {
    projectileCalculateTrajectoryAndSpawn(mathAngleBetweenPoints2D(targetX, targetZ, D_807FC7B0, D_807FC7B8), type, param, speed, targetX, targetY, targetZ, flightTime, owner);
}

void projectileClampAngleAndSpawn(s16 centerYaw, s16 maxSpread, s16 type, s16 param, f32 speed, f32 targetX, f32 targetY, f32 targetZ, f32 flightTime, Actor *owner) {
    s16 lowYaw;
    s16 highYaw;
    s16 yaw;

    yaw = mathAngleBetweenPoints2D(targetX, targetZ, D_807FC7B0, D_807FC7B8);
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
extern u32 gGlobalOverlayFlags;
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
    if (!((f64)proj->speedXZ < 0.1)) {
        if (trailEffect != 0) {
            ownerState = proj->parentActor->customState;
            camState = ownerState->camActor->customState;
            if (camState->unkF3 == 3) {
                effectSetCallback(effectLifetimeCountdownUpdate);
                effectSetSpeed(0x32);
                effectCreateAtPosition(trailEffect, homing->scale, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        if (projectileFindHomingTarget(collisionMask, (void **)&target, proj, 0, *(u8 *)&straight, straight == 0, &targetX, &targetY, &targetZ) != 0) { // FAKE: address-taken byte read keeps the arg3 lbu in a ring temp (candidate left uncoloured)
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
            if (straight == 0) {
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
                    heightOffset = (f64)target->eyeHeight * 0.5;
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

s32 projectileFindHomingTarget(collisionMask, outTarget, proj, useAim, levelOnly, includeModels, outX, outY, outZ)
u16 collisionMask;
void **outTarget;
Actor *proj;
u8 useAim;
u8 levelOnly;
u8 includeModels;
f32 *outX;
f32 *outY;
f32 *outZ;
{
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

    if (D_80750AD0 != 0) {
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
        effectSetMode(3);
        effectSetCallback(func_80717D4C);
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
    gSpawnedActor->unk15F = alpha;
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
    gSpawnedActor->y = gCurrentActor->unkA8;
    gSpawnedActor->unk15F = alpha;
    gSpawnedActor->yawSpeed = spin;
}



extern u8 D_80720340;
extern u8 D_8072038C;
extern s16 D_80750344;

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
        gCurrentActor->contactFlags = gCurrentActor->contactFlags & ~1;
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->yaw = gCurrentActor->moveYaw;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        if (gCurrentActor->parentActor != NULL && gCurrentActor->parentActor->actorType == 0xD2) {
            gCurrentActor->unk144 = 0x24;
        } else {
            gCurrentActor->unk144 = 0x3C;
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
            state->spawnFrame = state->spawnFrame - D_80750344 + 0x1E;
        }
        state->cooldown = 0;
        gCurrentActor->flags |= 0x80000;
        gCurrentActor->unkEC = 0;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    if (gCurrentActor->unk144 & 8) {
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
                state->cooldown = state->cooldown - 1;
            }
        }
    } else {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x78, 0x78, 0, 1.0f);
        if ((gCurrentActor->contactFlags & 1) && state->cooldown == 0 && (gCurrentActor->unk144 & 8)) {
            state->cooldown = 0xA;
        }
        if (state->cooldown != 0) {
            effectSetDepth(1);
            effectSetDuration(1);
            effectSetCallback(effectSpinBillboardingUpdate);
            effectCreateAtPosition(&D_80720340, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            state->cooldown = state->cooldown - 1;
        }
    }
    if (gCurrentActor->unkEC == 0) {
        f32 dx = gCurrentActor->x - gPlayerSlots->camX;
        f32 dy = gCurrentActor->y - gPlayerSlots->camY;
        dx = dx * dx; // FAKE: dx/dy reused as the running sum; a separate dz local adds 8 bytes to the frame and reorders the sum (35 rows)
        dx = dy * dy + dx;
        dy = gCurrentActor->z - gPlayerSlots->camZ;
        dx = dy * dy + dx;
        if (dx < 20000.0f) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x128, 0xFF, 0x7F, 0);
            gCurrentActor->unkEC = gCurrentActor->unkEC + 1;
        }
    }
    if (gCurrentActor->hasArcBounds != 0 || state->cooldown == 1 || gActorGlobalState.unk15 != 0) {
        effectSetDepth(1);
        effectSetDuration(1);
        if (gCurrentActor->actorType != 0x3B && state->param != 0x63) {
            effectSetSpeed(0x100FA);
            effectSetCallback(effectLightPulseOscillate);
        }
        effectCreateAtPosition(&D_80720340, 2.0 * ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        if (state->param < 0xA) {
            for (yawOffset = -0x12C; yawOffset != 0x12C; yawOffset += 0x32) {
                effectSetDepth(1);
                effectSetDuration(2);
                effectSetSpeed((gCurrentActor->moveYaw + yawOffset) % 4095);
                effectSetCallback(func_8071BC80);
                effectCreateAtPosition(&D_8072038C, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale * 0.5, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xF6, 0xFF, 0x7F, 0x1E, 0x1E, 0.7f, 0);
        actorDespawn(gCurrentActor);
    }
    if (state->spawnFrame + D_80750344 < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}



extern u8 D_80720120;
extern u8 D_80720BE8;

void projectileSparkleUpdate(s32 silver) {
    ProjectileState *state;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= (gCurrentActor->soundSlots[0] = -2);
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 40.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 30.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(1);
        effectSetMode(2);
        effectSetDepth(1);
        effectSetCallback(effectGrowExpandMatrixUpdate);
        effectSetSpeed((s32)(randomNonNegative() >> 15) % 360);
        effectSetMaxDistance(2000);
        switch ((u8)silver) {
        case 0:
            effectSetColor(0xFF, 0xD7, 0x58, 0xFF);
            effectCreateAtActorBone(&D_80720120, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
            break;
        case 1:
            effectSetColor(0xC8, 0xC8, 0xFA, 0x9B);
            effectCreateAtActorBone(&D_80720BE8, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
            break;
        }
        state->param = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->spawnFrame = gGameFrameCounter;
        state->cooldown = 0;
        gCurrentActor->flags |= 0x80000;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    if ((gCurrentActor->contactFlags & 1) || (gCurrentActor->hasArcBounds != 0) || (gActorGlobalState.unk15 != 0) || ((u32)(state->spawnFrame + 24) < gGameFrameCounter)) {
        actorDespawn(gCurrentActor);
    }
}

extern u8 D_807201D4;

void projectileSparkleUpdateGold(void) {
    projectileSparkleUpdate(0);
}

void projectileSparkleUpdateSilver(void) {
    projectileSparkleUpdate(1);
}

void projectileSpawnParticleEffect(void) {
    projectileBounceParticleUpdate(&D_807201D4);
}


extern u8 D_80720020;
extern u8 D_807202D0;
extern s16 D_807502D0;
extern f32 D_807502E4;
extern u8 D_807200EC;
extern u8 gPlayerCount;
extern u8 D_8072029C;
extern u8 D_80720BA0;
extern s16 D_8075035C;
extern s16 D_80750370;


void projectileSpawnParticleEffect2(void) {
    projectileBounceParticleUpdate(&D_807201D4);
}

void projectileSpawnParticleEffect3(void) {
    projectileBounceParticleUpdate(&D_807201D4);
}

void projectileSpawnParticleEffectWithScale(void) {
    ProjectileState *state;
    f32 minSpeedY;

    state = gCurrentActor->customState;
    projectileBounceParticleUpdate(&D_807201D4);
    if (state->param == 1) {
        gCurrentActor->speedY += D_807502E4;
        minSpeedY = (f32)D_807502D0;
        if (gCurrentActor->speedY < minSpeedY) {
            gCurrentActor->speedY = minSpeedY;
        }
    }
}


void projectileDespawnOrExplode(void) {
    ProjectileState *state;
    u8 arcBounds;
    Actor *other;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 50.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectCreateAtActorBone(&D_80720020, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->spawnFrame = gGameFrameCounter;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 10, 10, 1, 0x96, 0x78, 0, 1.0f);
    arcBounds = gCurrentActor->hasArcBounds;
    if (arcBounds != 0 || (gCurrentActor->contactFlags & 1) || gActorGlobalState.unk15 != 0 || gActorGlobalState.bossFightPhase == 9) {
        other = gCurrentActor->parentActor;
        if (other == NULL || other->actorType != 0x2E || (other->actorType == 0x2E && (arcBounds != 0 || (gCurrentActor->contactFlags & 1)))) {
            effectSetDepth(0);
            effectSetDuration(1);
            effectSetCallback(effectLifetimeCountdownUpdate);
            effectSetSpeed(0xC);
            effectCreateAtPosition(&D_807202D0, 0.75f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x61, 0xFF, 0x7F, 0x1E, 0, 0.0f, 0);
        actorDespawn(gCurrentActor);
    }
    if ((u32)(state->spawnFrame + D_80750344) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

extern u8 D_807200A0;
extern u8 D_8071FB34;
extern s16 D_80750350;
extern s16 D_80750364;

void projectileHomingUpdate(void) {
    ProjectileState *state;
    s16 collisionMask;
    u8 hit;
    s32 lifetime;
    s32 i;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 50.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&D_807200A0, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->unk16E[0] = 0x3C;
        gCurrentActor->unk16E[1] = 0x3C;
        state->param = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = D_80750350;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &D_807200A0, 0);
    }
    if (state->param & 4) {
        lifetime = D_80750364;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (gCurrentMap == 0xCC) {
        gCurrentActor->unkFA = 0x2328;
        hit = (u8)(gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->moveYaw) == 0);
    } else {
        hit = gCurrentActor->collisionHit;
    }
    if (hit ||
        actorGetFloorSnapped() != 0 ||
        ((gCurrentActor->contactFlags & 1) && collisionGetStateByte() == 1) ||
        gActorGlobalState.unk15 != 0 ||
        (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && (u32)(state->spawnFrame + 1) < gGameFrameCounter)) {
        effectSetDepth(1);
        effectSetSpeed(0x1006E);
        effectSetCallback(effectLightPulseOscillate);
        effectCreateAtPosition(&D_8071FB34, 0.45f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8D, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
        if (D_80750AD0 == 0) {
            for (i = 0; i != 0xC; i += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + i);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_807200EC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
    }
    if (gPlayerCount >= 2) {
        lifetime = (s32)((f32)lifetime * 1.4f);
    }
    if (gCurrentMap == 0x10) {
        lifetime = (s32)((f64)lifetime * 1.2);
    }
    if ((u32)(state->spawnFrame + lifetime) < gGameFrameCounter) {
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
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&D_8072029C, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->unk16E[0] = 0x3C;
        gCurrentActor->unk16E[1] = 0x3C;
        state->param = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = D_8075035C;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &D_8072029C, 0);
    }
    if (state->param & 4) {
        lifetime = D_80750370;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (gCurrentActor->collisionHit != 0 ||
        actorGetFloorSnapped() != 0 ||
        ((gCurrentActor->contactFlags & 1) && collisionGetStateByte() == 1) ||
        gActorGlobalState.unk15 != 0 ||
        (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && (u32)(state->spawnFrame + 1) < gGameFrameCounter)) {
        if (D_80750AD0 == 0) {
            for (i = 0; i != 0xC; i += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x05000000 + i);
                effectSetMode(1);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_80720BA0, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x91, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
    }
    if (gPlayerCount >= 2) {
        lifetime = (s32)((f32)lifetime * 1.4f);
    }
    if ((u32)(state->spawnFrame + lifetime) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

void projectileSpawnExplosion(void) {
    s32 i;

    effectSetDepth(1);
    effectSetSpeed(0x1006E);
    effectSetCallback(effectLightPulseOscillate);
    effectCreateAtPosition(&D_80720120, 2.0f, gCurrentActor->x, gCurrentActor->y + 22.0f, gCurrentActor->z);

    for (i = 0; i < gPlayerCount; i++) {
        camStartShakeFromPoint(((PlayerState *)gPlayerSlots[i].actor->customState)->camActor, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
    }

    actorSpawnSparkleBurst();

    if (D_80750AD0 == 0) {
        for (i = 0; i < 12; i++) {
            effectSetDepth(1);
            effectSetSpeed(0x0B010000 + i);
            effectSetCallback(effectRadialSprayUpdate);
            effectCreateAtPosition(&D_807200EC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
    }

    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF6, 0xFF, 0x7F, 0x1E);
}



extern u8 D_80720268;
extern s16 D_80750348;
extern s16 D_8075034C;
extern s8 D_80029FA0;

void projectileBounceExplodeScaledUpdate(void) {
    ProjectileState *state;
    s16 yaw;
    u8 outOfArc;
    f32 scale;
    s32 i;
    f32 radius;
    s32 value;

    state = gCurrentActor->customState;
    outOfArc = 0;
    scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale * 2.5f;
    if (!(gCurrentActor->flags & 0x10)) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF4, 0xFF, 0x7F, 5);
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = (f32)(((f64)(((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ / (f32)4)) * 2.6);
        gCurrentActor->speedXZ *= scale;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, scale * 60.0);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, scale * 50.0, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        state->param = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        effectSetDuration(-1);
        effectSetDepth(1);
        state->spawnFrame = gGameFrameCounter;
        if (state->param >= 0xCA) {
            effectSetSpeed(0xA);
            effectSetCallback(effectLightPulseOscillate);
        }
        if (state->param >= 0xCB) {
            gCurrentActor->speedY = 250.0f * scale;
            state->spawnFrame -= D_80750348 - D_8075034C;
        } else {
            gCurrentActor->speedY = 200.0f * scale;
        }
        effectCreateAtActorBone(&D_80720268, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->bounceCount = 0;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->unkFA = 0x2328;
        value = (u32)(60.0f * scale);
        gCurrentActor->unk16E[0] = value;
        gCurrentActor->unk16E[1] = value;
        state->target = NULL;
        state->groundFrames = 0;
    }
    if ((u32)(state->spawnFrame + 5) < gGameFrameCounter) {
        gCurrentActor->flags &= ~0x00080000;
    }
    value = 2;
    if (gPlayerCount >= 2) {
        value = 3;
    }
    projectileSteerTowardTarget(value, gCurrentActor, NULL, 1);
    actorUpdatePrevContactFlags(gCurrentActor);
    if (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->moveYaw) == 0) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        value = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax);
        yaw = gCurrentActor->moveYaw;
        yaw = (yaw + 0x800) & 0xFFF;
        value += (s16)(value - yaw);
        gCurrentActor->moveYaw = value;
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
    gCurrentActor->speedY += D_807502E4 * scale;
    if (gCurrentActor->speedY < (f32)D_807502D0) {
        gCurrentActor->speedY = (f32)D_807502D0;
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
        gCurrentActor->speedXZ = ((f64)gCurrentActor->speedXZ / 3.0) * 2.5;
    }
    if ((gCurrentActor->contactFlags & 1) && (gCurrentActor->prevContactFlags & 1)) {
        state->groundFrames++;
    } else {
        state->groundFrames = 0;
    }
    if (state->groundFrames == 4) {
        gActorGlobalState.unk15 = 1;
    }
    if (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && (u32)(state->spawnFrame + 1) < gGameFrameCounter) {
        gActorGlobalState.unk15 = 1;
    }
    if ((gCurrentActor->renderFlags & 0x100) || outOfArc != 0) {
        gActorGlobalState.unk15 = 1;
    }
    if ((((gCurrentActor->contactFlags & 1) && state->bounceCount == 4) || gActorGlobalState.unk15 != 0) && gCurrentActor->state == 0) {
        radius = 250.0f * scale;
        if (state->param != 0xCA) {
            effectSetDepth(1);
            effectSetSpeed(0x100D2);
            effectSetCallback(effectLightPulseOscillate);
            effectCreateAtPosition(&D_80720120, 2.0f, gCurrentActor->x, gCurrentActor->y + 22.0f, gCurrentActor->z);
            actorSpawnSparkleBurst();
            if (D_80750AD0 == 0) {
                for (i = 0; i != 12; i++) {
                    effectSetDepth(1);
                    effectSetSpeed(0x0B010000 + i);
                    effectSetCallback(effectRadialSprayUpdate);
                    effectCreateAtPosition(&D_807200EC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                }
            }
        }
        i = 0;
        if (gPlayerCount > 0) {
            do {
                camStartShakeFromPoint(((PlayerState *)gPlayerSlots[i].actor->customState)->camActor, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
                i++;
            } while (i < gPlayerCount);
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
    if ((u32)(state->spawnFrame + D_80750348) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
        D_80029FA0--;
    }
}


extern s16 D_80750358;
extern s16 D_8075036C;

extern u8 D_807201A0;

extern u8 D_80720268;

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
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = (f32)((f64)(((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ / (f32)4) * 2.6);
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetColor(0, 0xFF, 0, 0xFF);
        effectCreateAtActorBone(&D_80720268, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->spawnFrame = gGameFrameCounter;
        state->bounceCount = 0;
        gCurrentActor->flags |= 0x80000;
        gCurrentActor->unkFA = 0x2328;
        state->param = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        if (state->param == 0x63) {
            state->bounceCount = 2;
        }
        state->target = NULL;
    }
    if ((u32)(state->spawnFrame + 10) < gGameFrameCounter) {
        gCurrentActor->flags &= 0xFFF7FFFF;
    }
    projectileSteerTowardTarget(1, gCurrentActor, 0, 1);
    actorUpdatePrevContactFlags(gCurrentActor);
    if (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->moveYaw) == 0) {
        s16 angle;
        s16 diff;
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        midYaw = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax);
        angle = gCurrentActor->moveYaw;
        angle = (angle + 0x800) & 0xFFF;
        diff = midYaw - angle;
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
    gCurrentActor->speedY += D_807502E4;
    minSpeed = (f32)D_807502D0;
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
        gCurrentActor->speedXZ = (f32)(((f64)gCurrentActor->speedXZ / 3.0) * 2.5);
    }
    if ((gCurrentActor->renderFlags & 0x100) || outOfArc != 0) {
        gActorGlobalState.unk15 = 1;
    }
    if (((gCurrentActor->contactFlags & 1) && state->bounceCount == 4) || gActorGlobalState.unk15 != 0) {
        projectileSpawnExplosion();
        actorDespawn(gCurrentActor);
    }
    if ((u32)(state->spawnFrame + D_80750344) < gGameFrameCounter) {
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
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&D_807201A0, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->unk16E[0] = 0x3C;
        gCurrentActor->unk16E[1] = 0x3C;
        state->param = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = D_80750358;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &D_807201A0, 0);
    }
    if (state->param & 4) {
        lifetime = D_8075036C;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (actorGetFloorSnapped() != 0 ||
        gCurrentActor->collisionHit != 0 ||
        ((gCurrentActor->contactFlags & 1) && collisionGetStateByte() == 1) ||
        gActorGlobalState.unk15 != 0 ||
        (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && (u32)(state->spawnFrame + 1) < gGameFrameCounter)) {
        effectSetDepth(1);
        effectSetSpeed(0x1006E);
        effectSetCallback(effectLightPulseOscillate);
        effectCreateAtPosition(&D_8071FB34, 0.45f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1E5, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
        if (D_80750AD0 == 0) {
            for (i = 0; i != 0xC; i += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + i);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_807200EC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
    }
    if (gPlayerCount >= 2) {
        lifetime = (s32)((f32)lifetime * 1.4f);
    }
    if ((u32)(state->spawnFrame + lifetime) < gGameFrameCounter) {
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
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&D_80720268, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->unk16E[0] = 0x3C;
        gCurrentActor->unk16E[1] = 0x3C;
        state->param = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = D_80750358;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &D_80720268, 0);
    }
    if (state->param & 4) {
        lifetime = D_8075036C;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (!gCurrentActor->state && (gCurrentActor->collisionHit != 0 || (gCurrentActor->contactFlags & 1) || gActorGlobalState.unk15 != 0)) {
        exploding = 1;
    } else if (gCurrentActor->state) {
        if (gCurrentActor->state++ == 2) {
            actorDespawn(gCurrentActor);
        }
    }
    if (gPlayerCount >= 2) {
        lifetime = (s32)((f32)lifetime * 1.4f);
    }
    if ((u32)(state->spawnFrame + lifetime) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
    if (exploding != 0) {
        projectileSpawnExplosion();
        actorSetCollisionRadius(gCurrentActor, 250.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 250.0f, -1);
        gCurrentActor->state = 1;
    }
}

extern u8 D_807206A8;
extern u8 D_807206DC;
extern s16 D_80750360;
extern s16 D_80750374;
extern s16 D_80750354;
extern s16 D_80750368;


void projectileRotatingUpdate(void) {
    ProjectileState *state;
    s32 collisionMask;
    s32 lifetime;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 50.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&D_807206A8, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->scale = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->unk16E[0] = 0x3C;
        gCurrentActor->unk16E[1] = 0x3C;
        state->param = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = D_80750360;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &D_807206A8, 0);
    }
    if (state->param & 4) {
        lifetime = D_80750374;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (gCurrentActor->collisionHit != 0 ||
        actorGetFloorSnapped() != 0 ||
        ((gCurrentActor->contactFlags & 1) && collisionGetStateByte() == 1) ||
        gActorGlobalState.unk15 != 0 ||
        (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && (u32)(state->spawnFrame + 1) < gGameFrameCounter)) {
        effectSetDepth(1);
        effectSetSpeed(0x1006E);
        effectSetCallback(effectLightPulseOscillate);
        effectCreateAtPosition(&D_8071FB34, 0.45f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xFF, 0xFF, 0x7F, 5);
        actorDespawn(gCurrentActor);
        if (D_80750AD0 == 0) {
            s32 i;
            for (i = 0; i != 0xC; i += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + i);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_807206DC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
    }
    if (gPlayerCount >= 2) {
        lifetime = (s32)((f32)lifetime * 1.4f);
    }
    if ((u32)(state->spawnFrame + lifetime) < gGameFrameCounter) {
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
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->yaw = (s16)gCurrentActor->moveYaw;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->unk144 = 0x3C;
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x01080000;
        gCurrentActor->unk16E[0] = 0x3C;
        gCurrentActor->unk16E[1] = 0x3C;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x404, 0.0f, 1.0f);
        state->pitchDeg = -(mathAtan2(gCurrentActor->speedY, gCurrentActor->speedXZ) * 57.295776f);
        state->counter = 0;
        state->rollDeg = (f32)((u32)(randomLcgNext() % 3600U) / 10U);
        state->param = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        state->target = NULL;
    }
    lifetime = D_80750354;
    if (state->param & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, 0, 0);
    }
    if (state->param & 4) {
        lifetime = D_80750368;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    switch (gCurrentActor->state) {
    case 0:
        if (gCurrentActor->collisionHit != 0 || (((ProjectileSpawnParams *)gCurrentActor->spawnData)->shortLived != 0.0f && (u32)(state->spawnFrame + 1) < gGameFrameCounter)) {
            scriptSetActorRampTarget(gCurrentActor, 0.5f, 0);
            controllerAnimSetStateIfChanged(gCurrentActor, 0x406, 0, 0.0f);
            gCurrentActor->speedXZ = 0.0f;
            gCurrentActor->speedY = 0.0f;
            gCurrentActor->state = 1;
            state->counter = 0x3C;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x308, 0xFF, 0x7F, 5);
            if (D_80750AD0 != 0) {
                actorDespawn(gCurrentActor);
                return;
            }
        }
        break;
    case 1:
        gCurrentActor->callbackMask = 0;
        gCurrentActor->unk144 = 1;
        state->spawnFrame = gGameFrameCounter;
        if (!--state->counter) {
            scriptSetActorRampTarget(gCurrentActor, 0.5f, 0);
            controllerAnimSetStateIfChanged(gCurrentActor, 0x405, 0, 10.0f);
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
    if (((gCurrentActor->contactFlags & 1) && collisionGetStateByte() == 1) || gActorGlobalState.unk15 != 0) {
        actorDespawn(gCurrentActor);
    }
    if (gPlayerCount >= 2) {
        lifetime = (s32)((f32)lifetime * 1.4f);
    }
    if ((u32)(state->spawnFrame + lifetime) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
    guRotateF(gCurrentActor->modelMtx, state->rollDeg, 0.0f, 0.0f, 1.0f);
    guRotateF(pitchMtx, state->pitchDeg, 1.0f, 0.0f, 0.0f);
    guMtxCatF(gCurrentActor->modelMtx, pitchMtx, gCurrentActor->modelMtx);
    actorUpdateModelMatrix(gCurrentActor, 1);
}

extern u8 D_8072006C;

void projectileRotatingLightUpdate(f32 floorOffset, u8 variant) {
    ProjectileState *state;
    s32 pad;
    u8 red;
    u8 green;
    u8 blue;
    f32 pad4C[4][4];
    s32 mode;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        if (variant == 1) {
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x306, 0xFF, 0x7F, 0, 0, 0.3f, 0);
        }
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->yaw = gCurrentActor->moveYaw;
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->interactionType = (u8)(u32)((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        gCurrentActor->sub4->scaleX = 2.0 * gCurrentActor->sub4->scaleX;
        gCurrentActor->sub4->scaleY = 2.0 * gCurrentActor->sub4->scaleY;
        gCurrentActor->sub4->scaleZ = 2.0 * gCurrentActor->sub4->scaleZ;
        state->pitchDeg = -(mathAtan2(gCurrentActor->speedY, gCurrentActor->speedXZ) * 57.295776f);
        gCurrentActor->unk144 = 0x3C;
        state->spawnFrame = gGameFrameCounter;
        state->cooldown = 0;
        gCurrentActor->flags |= 0x80000;
        state->counter = 0;
    }
    mode = variant;
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, floorOffset);
    if (mode != 0) {
        if (mode == 1) {
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
    if (mode == 1) {
        if (!state->cooldown && ((gCurrentActor->contactFlags & 1) || gCurrentActor->collisionHit != 0 || gActorGlobalState.unk15 != 0)) {
            effectSetSpeed(0x1006E);
            effectSetCallback(effectLightPulseOscillate);
            effectCreateAtPosition(&D_8072006C, 1.2f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            effectSpawnBoneWhite(0, 0, 0.8f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, -0x50);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF6, 0xFF, 0x3F, 0x14);
            state->cooldown = 2;
        } else if (state->cooldown) {
            if (--state->cooldown == 0) {
                actorDespawn(gCurrentActor);
            }
        }
        if ((u32)(state->spawnFrame + D_80750344) < gGameFrameCounter) {
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

extern u8 D_8071FBC8;
extern u8 D_8071FC40;
extern u8 D_80720804;



void projectileParticleSpawnerTick(void) {
    ProjectileState *state;
    s32 i;
    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unkFA = 0x270F;
        gCurrentActor->soundSlots[0] = -2;
        gCurrentActor->contactFlags &= -2;
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        state->param = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->param;
        gCurrentActor->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 110.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 100.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectCreateAtActorBone(&D_80720804, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x80000;
        if (state->param != 0xA) {
            effectSetMode(2);
            effectSetDepth(1);
            effectCreateAtPosition(&D_8071FBC8, 1.5f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
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
        effectCreateAtPosition(&D_8071FC40, 0.3f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    }
    if (((gCurrentActor->hasArcBounds != 0) && ((gGameFrameCounter - state->spawnFrame) >= 6)) || gActorGlobalState.unk15 != 0) {
        if ((gActorGlobalState.unk15 != 0) && (state->param != 0xA)) {
            effectSetDepth(1);
            effectSetSpeed(0x100D2);
            effectSetCallback(effectLightPulseOscillate);
            effectCreateAtPosition(&D_80720120, 2.0f, gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z);
            camStartShakeFromPoint(((PlayerState *)gPrimaryPlayerActor->customState)->camActor, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
            actorSpawnSparkleBurst();
            for (i = 0; i != 12; i += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + i);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_807206DC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        if (state->param != 0xA) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3C, 0xFF, 0x7F, 0x1E);
        }
        actorDespawn(gCurrentActor);
    }
    if (state->spawnFrame + D_80750344 < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

extern f32 D_80750274;



void projectileHomingParticleUpdate(void) {
    ProjectileState *state;
    f32 jitterX;
    f32 jitterY;
    f32 jitterZ;
    f32 minSpeed;
    s32 i;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unkFA = 0x270F;
        gCurrentActor->soundSlots[0] = -2;
        gCurrentActor->contactFlags &= -2;
        gCurrentActor->moveYaw = (s16)((((ProjectileSpawnParams *)gCurrentActor->spawnData)->angle / 6.2831855f) * 4095.0f);
        gCurrentActor->speedXZ = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->speedY = ((ProjectileSpawnParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->unk144 = 0x1C;
        actorSetCollisionRadius(gCurrentActor, 110.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 100.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectCreateAtActorBone(&D_80720804, ((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale, gCurrentActor, 1, 2);
        state->spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x80000;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    gCurrentActor->speedY += D_80750274;
    minSpeed = D_807502D0;
    if (gCurrentActor->speedY < minSpeed) {
        gCurrentActor->speedY = minSpeed;
    }
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 14, 14, 1, 150, 120, 0, 1.0f);
    i = 0;
    if ((gCurrentActor->contactFlags & 1) || ((gCurrentActor->hasArcBounds != 0) && ((gGameFrameCounter - state->spawnFrame) >= 6)) || gActorGlobalState.unk15 != 0) {
        do {
            jitterX = ((randomNonNegative() >> 15) % 8191 / 200.0) - 20.0;
            jitterY = ((randomNonNegative() >> 15) % 8191 / 200.0) - 20.0;
            jitterZ = ((randomNonNegative() >> 15) % 8191 / 200.0) - 20.0;
            effectSetAngle(i);
            effectSetDepth(1);
            if (i == 0) {
                effectSetSpeed(0x1006E);
                effectSetCallback(effectLightPulseOscillate);
            } else {
                effectSetCallback(func_80717D4C);
                effectSetSpeed(-150 - ((randomNonNegative() >> 15) % 50));
            }
            effectCreateAtPosition(&D_80720340, 1.6f, gCurrentActor->x + jitterX, gCurrentActor->y + jitterY, gCurrentActor->z + jitterZ);
            i += 2;
        } while (i != 16);
        camStartShake(gCamActor, 20, 15);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3C, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
    }
    if (state->spawnFrame + D_80750344 < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}


extern f32 D_807502F8;
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
            gCurrentActor->unk144 = 0x3C;
        } else {
            gCurrentActor->unk144 = 0x1C;
        }
        *spawnFrame = gGameFrameCounter;
        gCurrentActor->flags |= 0x80000;
        collisionQueryActorFloor(gCurrentActor, &floorType, &floorY, &floorFlags, &floorNormal, floorMisc);
        gCurrentActor->accelY = D_807502F8 - (f32)(((randomNonNegative() >> 15) % 32767) % 10);
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
                bounces = gCurrentActor->unk155;
                if (bounces < 2) {
                    gCurrentActor->unk155 = bounces + 1;
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
            value = (f32)D_807502D0;
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
    Actor *other;

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
        state->baseSpeed = (s32)gCurrentActor->speedXZ;
        gCurrentActor->drawDistance = 1000;
        gCurrentActor->flags |= 0x400;
        state->spawnFrame += 0x78;
        if (gCurrentActor->soundSlots[0] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x114, 0x1E, 1, 0, 0xFF, 1.0f, 0);
            D_80770B68[D_80770628[gCurrentActor->soundSlots[0]]] = 0.75f;
            D_80770BC0[D_80770628[gCurrentActor->soundSlots[0]]] = 1.0f;
        }
        state->counter = 0xF;
        state->tick = 0;
        actorSetUniformScale(gCurrentActor, (f64)((ProjectileSpawnParams *)gCurrentActor->spawnData)->scale * 0.15);
    }
    state->tick++;
    if (state->counter < state->tick) {
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x15B, 0xFF, 0x6E, 0, 0x1E, 0.3f, 0);
        state->tick = 0;
        if (state->counter >= 3) {
            state->counter--;
        }
    }
    if ((u32)(state->spawnFrame - 100) < gGameFrameCounter) {
        gCurrentActor->flags &= ~0x80000;
    }
    if (((u32)(state->spawnFrame + D_80750344) < gGameFrameCounter) || ((gCurrentActor->collisionHit != 0) && (gCurrentActor->actorType != 0xA9)) || (gActorGlobalState.unk15 != 0)) {
        tagBarrelSpawnActorSmokePuffs(0, 1);
        sfxStopSlotSound(gCurrentActor, 0);
        actorDespawn(gCurrentActor);
        other = gCurrentActor->parentActor;
        if (other != NULL && other->actorType == 0xB9 && other->state != 0x37) {
            other->unk155++;
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
            gCurrentActor->unk155 = 0;
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
        gCurrentActor->movePitch = mathAngleEaseToward(gCurrentActor->movePitch, (s16)(s32)(((f64)mathCalculatePitchAngle(gPrimaryPlayerActor->x, gPrimaryPlayerActor->y + (f32)(u32)gPrimaryPlayerActor->eyeHeight, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 20) * 2048.0) / 3.1415927410125732), 30.0f);
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
            gCurrentActor->unk155 = 0;
        }
        break;
    }
    if (gCurrentActor->actorType == 0x59) {
        effectSetDepth(1);
        effectSetCallback(effectFollowParentUpdate);
        effectSetMaxDistance(1000);
        effectSetSpeed((s32)gCurrentActor);
        effectCreateAtActorBone(&D_80720120, 1.0f, gCurrentActor, 1, 0);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}



void projectileChaseReflectUpdate(void) {
    s16 midYaw;
    s16 t;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unkFA = 0x2328;
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
