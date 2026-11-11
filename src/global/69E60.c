#include "common.h"
#include "actor.h"
#include "proto/global/166A0.h"
#include "proto/global/35000.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7CA80.h"
#include "proto/global/CEAE0.h"


void actorStepPhysics(Actor *actor, s16 targetYaw, s16 targetPitch) {
    actorUpdatePrevContactFlags(actor);
    func_80665ACC(actor);
    if (actor->hasArcBounds != 0) {
        mathAngleClampToArc(actor->moveYaw, targetYaw, actor->arcYawMin, actor->arcYawMax, &actor->unkF2);
        actor->unkFA = func_80672134(actor->arcYawMin, actor->arcYawMax, targetPitch, actor->unkF8);
        if ((actor->renderFlags & 0x200) && (actor->renderFlags & 0x100)) {
            actor->unkFA = 0;
        }
        actor->moveYaw = actor->unkF2;
    }
}

extern u32 gFrameDelta;

void actorApplyVelocity(Actor *actor) {
    f32 pad;
    f32 scaleFactor;
    f32 fv1;
    f32 moveSpeed;

    moveSpeed = actor->speedXZ;
    if (actor->hasArcBounds != 0) {
        if ((f32)actor->unkFA < moveSpeed) {
            moveSpeed = actor->unkFA;
        }
    }
    scaleFactor = (f64)((actor->sub4 != NULL) ? actor->sub4->scaleY : 0.15f) * 0.16666666675;
    if ((actor->collisionFlags & 4) && (actor->contactFlags & 4)) {
        scaleFactor = (f64)scaleFactor * 0.5;
    }
    moveSpeed *= scaleFactor;
    if (actor->contactFlags & 1) {
        if (mathSinF(actor->floorTiltPitch) > 0.0f) {
            fv1 = mathSinF(actor->floorTiltPitch);
        } else {
            fv1 = -mathSinF(actor->floorTiltPitch);
        }
        moveSpeed *= fv1;
    }
    if (actor->flags & 0x400000) {
        moveSpeed = (f64)moveSpeed * ((f64)(u32)gFrameDelta * 0.5);
    }
    actor->x += moveSpeed * mathSinF(actor->moveYaw);
    actor->z += moveSpeed * mathCosF(actor->moveYaw);
    actor->y += actor->speedY * scaleFactor;
}


void actorApplyVelocityCustom(Actor *actor, f32 speedXZ, f32 speedY) {
    f32 scaleFactor;
    f32 scale;

    if (actor->hasArcBounds != 0) {
        if ((f32)actor->unkFA < speedXZ) {
            speedXZ = actor->unkFA;
        }
    }
    if (actor->sub4 != NULL) {
        scale = actor->sub4->scaleY;
    } else {
        scale = 0.15f;
    }
    scaleFactor = (f64)scale * 0.16666666675;
    speedXZ *= scaleFactor;
    if (actor->contactFlags & 1) {
        speedXZ *= (mathSinF(actor->floorTiltPitch) > 0.0f) ? mathSinF(actor->floorTiltPitch) : -mathSinF(actor->floorTiltPitch);
    }
    if (actor->flags & 0x400000) {
        speedXZ = (f64)speedXZ * ((f64)(u32)gFrameDelta * 0.5);
    }
    actor->x += speedXZ * mathSinF(actor->moveYaw);
    actor->z += speedXZ * mathCosF(actor->moveYaw);
    actor->y += speedY * scaleFactor;
}

extern u8 D_80748E00;
extern u8 D_80748E04;

void actorSkipFloorSnap(void) {
    D_80748E00 = 1;
}

u8 actorGetFloorSnapped(void) {
    return D_80748E04;
}




typedef struct {
    s16 slopeDivisor;
    u8 maxPitchDegAlt;
    u8 maxPitchDeg;
    u8 pad4[2];
    u8 minPitchDeg;
    u8 pad7[3];
} ActorTiltTableEntry;

extern ActorTiltTableEntry D_80748D40[];
extern ActorTiltTableEntry D_80748DA4;
extern PlayerState *gActivePlayerState;
extern Actor *gCurrentActor;
extern s32 gCurrentMap;





void actorUpdateFloorContactAndTilt(Actor *actor, f32 floorYOffset) {
    f32 floorY;
    u8 hasFloor;
    f32 waterY;
    u8 hasWater;
    f32 heightAboveFloor;
    f32 scale;
    s32 yawDelta;
    s16 effectiveTilt;
    s16 targetTiltYaw;
    s16 targetPitchLimit;
    s16 diff;
    ActorTiltTableEntry *tiltEntry;
    f32 easeRate;

    collisionQueryActorFloor(actor, &hasFloor, &floorY, &hasWater, &waterY, 0);
    if (actor->collisionFlags & 1) {
        func_806D09E8(actor);
    }
    heightAboveFloor = actor->y - actor->floorY;
    actor->contactFlags &= ~1;
    actor->distToFloor = heightAboveFloor - floorYOffset;
    if ((heightAboveFloor <= floorYOffset) || ((actor->prevContactFlags & 1) && (actor->speedY < 0.0f))) {
        if ((gCurrentActor->contactFlags & 0x200) || (gCurrentMap == 0x27) || (gCurrentMap == 0x6F) || (gCurrentMap == 0xB9)) {
            if (actor->distToFloor < 0.5) {
                if (actor->sub4 != NULL) {
                    scale = actor->sub4->scaleY;
                } else {
                    scale = 0.15f;
                }
                actor->y = actor->floorY + floorYOffset;
                actor->distToFloor = 0.0f;
                actor->contactFlags |= 1;
                actor->speedY = (actor->floorY + floorYOffset - actor->prevY) * (f32)(40.0 / (scale * 6.66666667));
            }
        } else if (actor->distToFloor < 5.0f) {
            actor->distToFloor = 0.0f;
            actor->y = actor->floorY + floorYOffset;
            actor->contactFlags |= 1;
            if (actor->speedY < -10.0f) {
                actor->speedY = -10.0f;
            }
        }
    }
    D_80748E04 = 0;
    if (hasFloor && !(actor->contactFlags & 1) && (D_80748E00 == 0)) {
        if (actor->speedY > 0.0f) {
            actor->speedY = 0.0f;
        }
        actor->y = floorY + actor->speedY * 0.025;
        D_80748E04 = 1;
    }
    D_80748E00 = 0;
    easeRate = (actor->flags & 0x40000) ? 0.2 : 1.0;
    effectiveTilt = (actor->contactFlags & 1) ? actor->floorTiltPitch : 0x400;
    targetTiltYaw = actor->floorTiltYaw;
    tiltEntry = &D_80748D40[actor->floorSlopeType];
    switch (gCurrentMap) {
    case 0x52:
        gActivePlayerState->unk26 = 0x14;
        /* fallthrough */
    case 0xE:
        if (actor->contactFlags & 0x200) {
            tiltEntry = &D_80748DA4;
        }
        break;
    }
    if (actor->floorSlopePitch >= 0x3F4) {
        actor->floorSlopeYaw = targetTiltYaw;
    }
    if (effectiveTilt >= 0x3F4) {
        targetTiltYaw = actor->floorSlopeYaw;
    }
    targetPitchLimit = (s16)((tiltEntry->minPitchDeg << 12) / 360);
    if (targetPitchLimit < effectiveTilt) {
        targetPitchLimit = effectiveTilt;
    }
    diff = yawDelta = mathAngleSignedDistance(actor->floorSlopeYaw, targetTiltYaw);
    if (((yawDelta > 0) ? yawDelta : -yawDelta) >= 0x6AB) {
        if (actor->floorSlopePitch >= 0x3C8) {
            actor->floorSlopePitch = 0x400;
            actor->floorSlopeYaw = targetTiltYaw;
        } else {
            diff = mathAngleSignedDistance(actor->floorSlopePitch, 0x400);
            diff *= easeRate;
            actor->floorSlopePitch += diff;
            actor->floorSlopePitch &= 0xFFF;
        }
    } else {
        diff *= easeRate;
        actor->floorSlopeYaw += diff;
        actor->floorSlopeYaw &= 0xFFF;
        diff = mathAngleSignedDistance(actor->floorSlopePitch, targetPitchLimit);
        diff *= easeRate;
        actor->floorSlopePitch += diff;
        actor->floorSlopePitch &= 0xFFF;
    }
    if (!(actor->contactFlags & 0x20)) {
        targetPitchLimit = tiltEntry->maxPitchDeg;
    } else {
        targetPitchLimit = tiltEntry->maxPitchDegAlt;
    }
    targetPitchLimit = (s16)((targetPitchLimit << 12) / 360);
    if (targetPitchLimit < effectiveTilt) {
        actor->floorSlopeFactor = 0.0f;
    } else {
        actor->floorSlopeFactor = (0x400 - effectiveTilt) / tiltEntry->slopeDivisor;
    }
}
extern u8 D_80748D48[][10];

u8 func_80665AAC(Actor *actor) {
    return D_80748D48[actor->floorSurfaceType][0];
}

void func_80665ACC(Actor *actor) {
    actor->flags |= 2;
    actor->flags |= 0x20;
}


f32 mathAngleBetweenPointsDeg(s32 x1, s32 y1, s32 x2, s32 y2) {
    f32 angleRad;

    if (x2 >= x1 && y2 >= y1) {
        angleRad = mathAtan2(y2 - y1, x2 - x1) + 1.570796371f;
    } else if (x2 >= x1 && y2 < y1) {
        angleRad = 1.570796371f - mathAtan2(y1 - y2, x2 - x1);
    } else if (x2 < x1 && y2 < y1) {
        angleRad = mathAtan2(y1 - y2, x1 - x2) + 4.71238911151885986;
    } else if (x2 < x1 && y2 >= y1) {
        angleRad = 4.71238911151885986 - mathAtan2(y2 - y1, x1 - x2);
    }
    return angleRad * 57.29577637f;
}

s32 mathAsinFixed(s32);

s16 mathAngleDiscrete(f32 x1, f32 y1, f32 x2, f32 y2, f32 dist) {
    s16 angleDiscrete;

    if (dist < 1.0) {
        dist = 1.0f;
    }
    if (x2 <= x1 && y2 <= y1) {
        angleDiscrete = mathAsinFixed((s32)((x1 - x2) * 65535.9 / dist)) >> 4;
    } else if (x2 <= x1 && y1 < y2) {
        angleDiscrete = (mathAsinFixed((s32)((y2 - y1) * 65535.9 / dist)) >> 4) + 0x400;
    } else if (x1 < x2 && y1 < y2) {
        angleDiscrete = (mathAsinFixed((s32)((x2 - x1) * 65535.9 / dist)) >> 4) + 0x800;
    } else if (x1 < x2 && y2 <= y1) {
        angleDiscrete = (mathAsinFixed((s32)((y1 - y2) * 65535.9 / dist)) >> 4) + 0xC00;
    }
    return angleDiscrete;
}

s16 mathAngleBetweenPoints2D(f32 x1, f32 y1, f32 x2, f32 y2) {
    f32 dx = x1 - x2;
    f32 dy = y1 - y2;

    return mathAngleDiscrete(x1, y1, x2, y2, sqrtf((dx * dx) + (dy * dy)));
}

f32 mathAngleBetweenPointsRad(f32 x1, f32 y1, f32 x2, f32 y2) {
    return mathAngleBetweenPoints2D(x1, y1, x2, y2) * 3.141592741f * 0.00048828125;
}


f32 mathCalculatePitchAngle(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, s16 minDist) {
    f32 dx = x1 - x2;
    f32 dz = z1 - z2;
    f32 dist = sqrtf((dx * dx) + (dz * dz));
    f32 minDistF = minDist;
    f32 clampedDist;

    if (dist < minDistF) {
        clampedDist = minDistF;
    } else {
        clampedDist = dist;
    }
    return mathAtan2(y2 - y1, clampedDist);
}

typedef struct ActorSubNodeData {
    f32 radius;
    f32 height;
    u8 nodes[1];
} ActorSubNodeData;

typedef struct ActorSubNodeWrapper {
    char pad[0xC];
    ActorSubNodeData *collision;
} ActorSubNodeWrapper;

ActorSub140 *actorSub140CreateFromModel(Actor *actor) {
    ActorSubNodeWrapper *model;
    f32 radius;
    f32 height;
    f32 scale;
    u8 *nodeData;
    s32 boneMtx0;
    s32 boneMtx1;

    radius = 0.0f;
    height = 0.0f;
    scale = 1.0f;
    nodeData = NULL;
    boneMtx0 = 0;
    boneMtx1 = 0;
    model = actor->animState;
    if (model != NULL) {
        radius = model->collision->radius;
        height = model->collision->height;
        nodeData = model->collision->nodes;
    }
    if (actor->sub4 != NULL) {
        scale = actor->sub4->scaleY;
        boneMtx0 = (s32)actor->sub4->boneMtx[0];
        boneMtx1 = (s32)actor->sub4->boneMtx[1];
    }
    return actorSub140CreateFromData(0.0f, 0.0f, 0.0f, scale, radius, height, actor->modelMtx, boneMtx0, boneMtx1, nodeData);
}


extern s32 gFrameCounter;

void actorUpdatePositionAndSub140(Actor *actor) {
    f32 x;
    f32 y;
    f32 z;
    f32 scale;

    x = actor->x;
    y = actor->y;
    z = actor->z;
    if (actor->sub4 != NULL) {
        renderEntryAddOrUpdate(0, 0, actor, x, y, z, actor->drawDistance, 0, 1, -1, 1);
    }
    if (actor->collision != NULL) {
        if (actor->sub4 != NULL) {
            scale = actor->sub4->scaleY;
        } else {
            scale = 0.15f;
        }
        actorSub140SetVectors(actor, x, y, z, scale);
        actor->collision->unk80 = gFrameCounter;
    }
}
