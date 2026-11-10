#include "common.h"
#include "actor.h"
#define PROTO_SKIP_actorUpdatePrevContactFlags // PROTO: The number of arguments doesn't agree with the number in the
#include "proto/global/166A0.h"
#include "proto/global/35000.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7CA80.h"
#include "proto/global/CEAE0.h"


typedef struct ActorPhysicsWork {
    char pad0[0x64];
    u32 unk64;
    char pad68[0x86];
    s16 unkEE;
    char padF0[2];
    s16 unkF2;
    s16 arcYawMin;
    s16 arcYawMax;
    s16 unkF8;
    s16 unkFA;
    u8 hasArcBounds;
} ActorPhysicsWork;

void actorUpdatePrevContactFlags(void);

void actorStepPhysics(Actor *self, s16 targetYaw, s16 targetPitch) {
    ActorPhysicsWork *actor = (ActorPhysicsWork *)self;

    actorUpdatePrevContactFlags();
    func_80665ACC((Actor *)actor);
    if (actor->hasArcBounds != 0) {
        mathAngleClampToArc(actor->unkEE, targetYaw, actor->arcYawMin, actor->arcYawMax, &actor->unkF2);
        actor->unkFA = func_80672134(actor->arcYawMin, actor->arcYawMax, targetPitch, actor->unkF8);
        if ((actor->unk64 & 0x200) && (actor->unk64 & 0x100)) {
            actor->unkFA = 0;
        }
        actor->unkEE = actor->unkF2;
    }
}

typedef struct ActorVelocityWork {
    char pad0[0x4];
    ActorSub4 *unk4;
    char pad8[0x54];
    u16 unk5C;
    char pad5E[2];
    u32 unk60;
    char pad64[6];
    u16 unk6A;
    char pad6C[0x10];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x30];
    f32 unkB8;
    char padBC[4];
    f32 unkC0;
    char padC4[0x16];
    s16 unkDA;
    char padDC[0x12];
    s16 unkEE;
    char padF0[0xA];
    s16 unkFA;
    u8 hasArcBounds;
} ActorVelocityWork;

f32 mathCosF(s16);
f32 mathSinF(s16);
extern u32 gFrameDelta;

void actorApplyVelocity(ActorVelocityWork *actor) {
    f32 pad;
    f32 scaleFactor;
    f32 fv1;
    f32 moveSpeed;

    moveSpeed = actor->unkB8;
    if (actor->hasArcBounds != 0) {
        if ((f32)actor->unkFA < moveSpeed) {
            moveSpeed = actor->unkFA;
        }
    }
    scaleFactor = (f64)((actor->unk4 != NULL) ? actor->unk4->scaleY : 0.15f) * 0.16666666675;
    if ((actor->unk5C & 4) && (actor->unk6A & 4)) {
        scaleFactor = (f64)scaleFactor * 0.5;
    }
    moveSpeed *= scaleFactor;
    if (actor->unk6A & 1) {
        if (mathSinF(actor->unkDA) > 0.0f) {
            fv1 = mathSinF(actor->unkDA);
        } else {
            fv1 = -mathSinF(actor->unkDA);
        }
        moveSpeed *= fv1;
    }
    if (actor->unk60 & 0x400000) {
        moveSpeed = (f64)moveSpeed * ((f64)(u32)gFrameDelta * 0.5);
    }
    actor->unk7C += moveSpeed * mathSinF(actor->unkEE);
    actor->unk84 += moveSpeed * mathCosF(actor->unkEE);
    actor->unk80 += actor->unkC0 * scaleFactor;
}

typedef struct ActorVelocityCustomWork {
    char pad0[0x4];
    ActorSub4 *unk4;
    char pad8[0x58];
    u32 unk60;
    char pad64[0x6];
    u16 unk6A;
    char pad6C[0x10];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x52];
    s16 unkDA;
    char padDC[0x12];
    s16 unkEE;
    char padF0[0xA];
    s16 unkFA;
    u8 hasArcBounds;
} ActorVelocityCustomWork;


void actorApplyVelocityCustom(ActorVelocityCustomWork *actor, f32 speedXZ, f32 speedY) {
    f32 scaleFactor;
    f32 scale;

    if (actor->hasArcBounds != 0) {
        if ((f32)actor->unkFA < speedXZ) {
            speedXZ = actor->unkFA;
        }
    }
    if (actor->unk4 != NULL) {
        scale = actor->unk4->scaleY;
    } else {
        scale = 0.15f;
    }
    scaleFactor = (f64)scale * 0.16666666675;
    speedXZ *= scaleFactor;
    if (actor->unk6A & 1) {
        speedXZ *= (mathSinF(actor->unkDA) > 0.0f) ? mathSinF(actor->unkDA) : -mathSinF(actor->unkDA);
    }
    if (actor->unk60 & 0x400000) {
        speedXZ = (f64)speedXZ * ((f64)(u32)gFrameDelta * 0.5);
    }
    actor->unk7C += speedXZ * mathSinF(actor->unkEE);
    actor->unk84 += speedXZ * mathCosF(actor->unkEE);
    actor->unk80 += speedY * scaleFactor;
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
    s16 unk0;
    char pad2[0x24];
    s16 unk26;
} CameraStateView;

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 pad4[2];
    u8 unk6;
    u8 pad7[3];
} ActorTiltTableEntry;

extern ActorTiltTableEntry D_80748D40[];
extern ActorTiltTableEntry D_80748DA4;
extern CameraStateView *gActivePlayerState;
extern Actor *gCurrentActor;
extern s32 gCurrentMap;





void actorUpdateFloorContactAndTilt(Actor *actor, f32 floorYOffset) {
    f32 floorY;
    u8 hasFloor;
    f32 waterY;
    u8 hasWater;
    f32 heightAboveFloor;
    f32 scale;
    s32 tmpd;
    s16 effectiveTilt;
    s16 targetTiltYaw;
    s16 targetPitchLimit;
    s16 diff;
    ActorTiltTableEntry *tiltEntry;
    f32 easeRate;

    collisionQueryActorFloor((Actor *)actor, &hasFloor, &floorY, &hasWater, &waterY, 0);
    if (actor->collisionFlags & 1) {
        func_806D09E8((Actor *)actor);
    }
    heightAboveFloor = actor->y - actor->floorY;
    actor->contactFlags &= ~1;
    actor->distToFloor = heightAboveFloor - floorYOffset;
    if ((heightAboveFloor <= floorYOffset) || ((actor->prevContactFlags & 1) && (actor->speedY < 0.0f))) {
        if ((gCurrentActor->contactFlags & 0x200) || ((u32)gCurrentMap == 0x27) || ((u32)gCurrentMap == 0x6F) || ((u32)gCurrentMap == 0xB9)) {
            if ((f64)actor->distToFloor < 0.5) {
                if (actor->sub4 != NULL) {
                    scale = actor->sub4->scaleY;
                } else {
                    scale = 0.15f;
                }
                actor->y = actor->floorY + floorYOffset;
                actor->distToFloor = 0.0f;
                actor->contactFlags |= 1;
                actor->speedY = (actor->floorY + floorYOffset - actor->prevY) * (f32)(40.0 / ((f64)scale * 6.66666667));
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
        actor->y = (f64)floorY + (f64)actor->speedY * 0.025;
        D_80748E04 = 1;
    }
    D_80748E00 = 0;
    easeRate = (actor->flags & 0x40000) ? 0.2 : 1.0;
    effectiveTilt = (actor->contactFlags & 1) ? actor->floorTiltPitch : 0x400;
    targetTiltYaw = actor->floorTiltYaw;
    tiltEntry = &D_80748D40[actor->floorSlopeType];
    switch ((u32)gCurrentMap) {
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
    targetPitchLimit = (s16)((tiltEntry->unk6 << 12) / 360);
    if (targetPitchLimit < effectiveTilt) {
        targetPitchLimit = effectiveTilt;
    }
    diff = tmpd = mathAngleSignedDistance(actor->floorSlopeYaw, targetTiltYaw);
    if (((tmpd > 0) ? tmpd : -tmpd) >= 0x6AB) {
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
        targetPitchLimit = tiltEntry->unk3;
    } else {
        targetPitchLimit = tiltEntry->unk2;
    }
    targetPitchLimit = (s16)((targetPitchLimit << 12) / 360);
    if (targetPitchLimit < effectiveTilt) {
        actor->floorSlopeFactor = 0.0f;
    } else {
        actor->floorSlopeFactor = (f32)((0x400 - effectiveTilt) / tiltEntry->unk0);
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
        angleRad = (f64)mathAtan2(y1 - y2, x1 - x2) + 4.71238911151885986;
    } else if (x2 < x1 && y2 >= y1) {
        angleRad = 4.71238911151885986 - (f64)mathAtan2(y2 - y1, x1 - x2);
    }
    return angleRad * 57.29577637f;
}

s32 mathAsinFixed(s32);

s16 mathAngleDiscrete(f32 x1, f32 y1, f32 x2, f32 y2, f32 dist) {
    s16 angleDiscrete;

    if ((f64)dist < 1.0) {
        dist = 1.0f;
    }
    if (x2 <= x1 && y2 <= y1) {
        angleDiscrete = mathAsinFixed((s32)(((f64)(x1 - x2) * 65535.9) / (f64)dist)) >> 4;
    } else if (x2 <= x1 && y1 < y2) {
        angleDiscrete = (mathAsinFixed((s32)(((f64)(y2 - y1) * 65535.9) / (f64)dist)) >> 4) + 0x400;
    } else if (x1 < x2 && y1 < y2) {
        angleDiscrete = (mathAsinFixed((s32)(((f64)(x2 - x1) * 65535.9) / (f64)dist)) >> 4) + 0x800;
    } else if (x1 < x2 && y2 <= y1) {
        angleDiscrete = (mathAsinFixed((s32)(((f64)(y1 - y2) * 65535.9) / (f64)dist)) >> 4) + 0xC00;
    }
    return angleDiscrete;
}

s16 mathAngleBetweenPoints2D(f32 x1, f32 y1, f32 x2, f32 y2) {
    f32 dx = x1 - x2;
    f32 dy = y1 - y2;

    return mathAngleDiscrete(x1, y1, x2, y2, sqrtf((dx * dx) + (dy * dy)));
}

f32 mathAngleBetweenPointsRad(f32 x1, f32 y1, f32 x2, f32 y2) {
    return (f64)(mathAngleBetweenPoints2D(x1, y1, x2, y2) * 3.141592741f) * 0.00048828125;
}


f32 mathCalculatePitchAngle(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, s16 minDist) {
    f32 dx = x1 - x2;
    f32 dz = z1 - z2;
    f32 dist = sqrtf((dx * dx) + (dz * dz));
    f32 f_arg6 = minDist;
    f32 max_dist;

    if (dist < f_arg6) {
        max_dist = f_arg6;
    } else {
        max_dist = dist;
    }
    return mathAtan2(y2 - y1, max_dist);
}

typedef struct ActorSubNodeData {
    f32 unk0;
    f32 unk4;
    u8 unk8[1];
} ActorSubNodeData;

typedef struct ActorSubNodeWrapper {
    char pad[0xC];
    ActorSubNodeData *unkC;
} ActorSubNodeWrapper;

typedef struct ActorScaleConfig {
    char pad[0x14];
    s32 unk14;
    s32 unk18;
    char pad2[0x1C];
    f32 unk38;
} ActorScaleConfig;

typedef struct ActorTransformWork {
    ActorSubNodeWrapper *unk0;
    ActorScaleConfig *unk4;
    char pad[4];
    u8 unkC[1];
} ActorTransformWork;


void actorSub140CreateFromModel(ActorTransformWork *actor) {
    f32 fv0;
    f32 fv1;
    f32 ft4;
    void *v1;
    s32 a1;
    s32 t0;

    fv0 = 0.0f;
    fv1 = 0.0f;
    ft4 = 1.0f;
    v1 = NULL;
    a1 = 0;
    t0 = 0;
    if (actor->unk0 != NULL) {
        fv0 = actor->unk0->unkC->unk0;
        fv1 = actor->unk0->unkC->unk4;
        v1 = &actor->unk0->unkC->unk8;
    }
    if (actor->unk4 != NULL) {
        ft4 = actor->unk4->unk38;
        a1 = actor->unk4->unk14;
        t0 = actor->unk4->unk18;
    }
    actorSub140CreateFromData(0.0f, 0.0f, 0.0f, ft4, fv0, fv1, &actor->unkC, a1, t0, v1);
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
