#include "common.h"

#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_effectSetColor // FAKE: callee prototype steer
#define PROTO_SKIP_lensFlareAddSource // FAKE: callee prototype steer
#define PROTO_SKIP_lightAdd // FAKE: callee prototype steer
#define PROTO_SKIP_matrixMakeRotationX // FAKE: callee prototype steer
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

typedef struct ProjectileActorSub174 {
    s16 unk0;
    u8 pad2[0x25];
    u8 unk27;
    u8 unk28;
    u8 pad29[0xB];
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 pad37[0x88 - 0x37];
    Actor *unk88;
    u8 pad8C[0x1A4 - 0x8C];
    u8 unk1A4;
} ProjectileActorSub174;

typedef struct ProjectileActorSync {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[0x7C - 0x5C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xAC - 0x88];
    f32 unkAC;
    u8 padB0[0xB8 - 0xB0];
    f32 unkB8;
    u8 padBC[0xE4 - 0xBC];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[0x174 - 0xEA];
    void *unk174;
} ProjectileActorSync;

void actorSnapToBone(Actor **actorRef) {
    f32 boneY;
    ProjectileActorSub174 *sub;

    sub = (*actorRef)->customState;
    actorGetNodePos(sub->unk88, 9, &(*actorRef)->x, &boneY, &(*actorRef)->z);
    if ((*actorRef)->y < boneY) {
        (*actorRef)->y = boneY;
    }
    (*actorRef)->yaw = sub->unk88->yaw;
    actorUpdateModelMatrix(*actorRef, 0);
}

void actorSyncTransformFromParent(ProjectileActorSync **actorRef) {
    ProjectileActorSync *self;
    ProjectileActorSub174 *sub;
    ProjectileActorSync *parent;
    ProjectileActorSub174 *parentSub;

    self = *actorRef;
    sub = self->unk174;
    parent = (ProjectileActorSync *)sub->unk88;
    if (parent != NULL) {
        parentSub = parent->unk174;
        if (parentSub->unk34 < 5) {
            self->unk7C = parent->unk7C;
            (*actorRef)->unk80 = ((ProjectileActorSync *)sub->unk88)->unk80;
            (*actorRef)->unk84 = ((ProjectileActorSync *)sub->unk88)->unk84;
            (*actorRef)->unkE6 = ((ProjectileActorSync *)sub->unk88)->unkE6;
            (*actorRef)->unkE8 = ((ProjectileActorSync *)sub->unk88)->unkE8;
            (*actorRef)->unkE4 = ((ProjectileActorSync *)sub->unk88)->unkE4;
            (*actorRef)->unkAC = ((ProjectileActorSync *)sub->unk88)->unkAC;
            parent = (ProjectileActorSync *)sub->unk88;
            if (parent->unk58 == 0x12E) {
                (*actorRef)->unkB8 = parent->unkB8 * 10.0f;
            } else {
                (*actorRef)->unkB8 = parent->unkB8;
            }
            self = *actorRef;
        } else {
            self = *actorRef;
            self->unkB8 = 0.0f;
            self = *actorRef;
        }
    }
    actorUpdateModelMatrix((Actor *)self, 0);
}

typedef struct TargetVec3f {
    f32 x, y, z;
} TargetVec3f;
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

void effectSetColor(s32, s32, s32, s32); // FAKE: callee prototype steer
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
        s32 alpha;
        f32 vol;
        f32 af;

        fv0 = (1024.0f - diff) * 0.0014285714f;
        if (fv0 < 1.0f) {
            scale = fv0;
        } else {
            scale = 1.0f;
        }
        af = (u32)alphaMax;
        alpha = (u32)(scale * af) & 0xFF;
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


typedef struct OwnerPlayerState {
    u8 pad0[0xBC];
    s16 unkBC;
    u8 padBE[0x1A0 - 0xBE];
    u16 unk1A0;
    u8 unk1A2;
    u8 unk1A3;
    u8 pad1A4[0x1F4 - 0x1A4];
    u32 unk1F4;
    u8 pad1F8[0x240 - 0x1F8];
    u8 unk240;
} OwnerPlayerState;

typedef struct OwnerLinkState {
    Actor *unk0;
    Actor *unk4;
    s32 unk8;
} OwnerLinkState;

typedef struct OwnerModelInfo {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[8];
    s16 unk10;
} OwnerModelInfo;

typedef struct ActorSub4Buf {
    s8 unk0;
    u8 unk1;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u8 unk8;
} ActorSub4Buf;

typedef struct ActorSub4BufView {
    u8 pad0[0x1C];
    ActorSub4Buf *unk1C;
} ActorSub4BufView;

extern u32 gFrameCounter;
extern s32 gCurrentMap;
extern Actor *gActivePlayerActor;
void matrixMakeRotationX(void *, s32); // FAKE: callee prototype steer
void lightAdd(f32, f32, s32, f32, f32, f32, f32, s32, s32, s32, s32); // FAKE: callee prototype steer

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
    f32 var;
    f32 glow;
    OwnerLinkState *link;
    OwnerPlayerState *playerState;
    Actor *owner;
    OwnerModelInfo *model;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    ActorSub4Buf *buf;

    link = gCurrentActor->customState;
    owner = link->unk0;
    if (!(gCurrentActor->flags & 0x10)) {
        ((ActorSub4BufView *)gCurrentActor->sub4)->unk1C = heapAlloc(0x10);
        buf = ((ActorSub4BufView *)gCurrentActor->sub4)->unk1C;
        buf->unk0 = -0x80;
        buf->unk1 = 1;
        buf->unk2 = 0;
        buf->unk4 = 0;
        buf->unk6 = 0;
        buf->unk8 = 0;
        gCurrentActor->yaw = 0;
        if (owner->actorType == 0xC5) {
            gCurrentActor->tintR = 0xFF;
            gCurrentActor->tintG = 0xFF;
            gCurrentActor->tintB = 0xFF;
            gCurrentActor->flags |= 0x800000;
        }
        link->unk8 = 0;
    }
    buf = ((ActorSub4BufView *)gCurrentActor->sub4)->unk1C;
    switch (owner->collisionFlags) {
    case 1:
        playerState = owner->customState;
        buf->unk2 = playerState->unk1A0;
        if ((owner->contactFlags & 5) || playerState->unk240 == 1 || (owner->state == 0x42 && playerState->unkBC != 0x31) || owner->state == 0x87) {
            actorAppendCallback(link->unk4, (s32)gCurrentActor, 0x2000000, 0, 0, 0);
            playerState->unk1A3 = 0;
            actorDespawn(gCurrentActor);
            sfxStopChannel(0x48, 0);
            sfxStopSlotSound(gActivePlayerActor, 0);
            slotQueueCancel(5, 0);
            playerState->unk240 = 0;
            if (!(playerState->unk1F4 & 4)) {
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
            link->unk8 = gFrameCounter;
        }
        if (gCurrentMap == 0x5C) {
            if (gFrameCounter && gFrameCounter) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            glow = (30.0 - (f64)(s32)(gFrameCounter - link->unk8)) / 30.0 * 100.0;
            if (glow > 0.0) {
                lightAdd(gCurrentActor->x, gCurrentActor->y, *(s32 *)&gCurrentActor->z, 0.0f, 0.0f, 0.0f, glow, 0, 0xFF, 0xC8, 0xC8);
            }
        }
        break;
    case 0x40:
        model = *(OwnerModelInfo **)owner->sub4;
        switch (model->unk10) {
        case 0x113:
            if (model->unk4 < 70.0f) {
                var = PICK_MIN(PICK_MAX(0.1, (model->unk4 - 39.0f) / 30.0), 0.49);
            } else {
                var = 0.5f;
            }
            break;
        case 0x12C:
            var = PICK_MAX(0.5 - model->unk4 / 50.0f, 0.01);
            break;
        case 0x12F:
        case 0x130:
            var = 0.25f;
            break;
        case 0x12D:
        case 0x12E:
            var = 0.0f;
            break;
        default:
            var = 0.5f;
            break;
        }
        buf->unk2 = 0;
        if (!(owner->flags & 4) || owner->state == 0x3C) {
            actorDespawn(gCurrentActor);
        } else if (var > 0.05) {
            if (gFrameCounter & 1) {
                effectSpawnActorBone(owner, 1, var);
            } else {
                effectSpawnActorBone(owner, 2, var);
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
    matrixMakeRotationX(rotX, 0xC2B40000);
    guMtxCatF(rotY, rotX, rotY);
    guAlignF(rotX, pitch * 57.295776f + 180.0f, boneX - gCurrentActor->x, boneY - gCurrentActor->y, boneZ - gCurrentActor->z);
    guMtxCatF(rotY, rotX, gCurrentActor->modelMtx);
    actorUpdateModelMatrix(gCurrentActor, 1);
}


typedef struct ActorMoveState {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[0x27 - 0x14];
    u8 unk27;
    u8 unk28;
    u8 pad29[0x34 - 0x29];
    u8 unk34;
    u8 unk35;
} ActorMoveState;

typedef struct ActorMoveStepFlag {
    u8 pad0[4];
    u8 unk4;
} ActorMoveStepFlag;

typedef struct ActorMoveView {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[4];
    u32 unk60;
    u8 pad64[6];
    u16 unk6A;
    u16 unk6C;
    u8 pad6E[0x80 - 0x6E];
    f32 unk80;
    u8 pad84[0xAC - 0x84];
    f32 unkAC;
    u8 padB0[0xB8 - 0xB0];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 padCC[0xDC - 0xCC];
    s16 unkDC;
    s16 unkDE;
    u8 padE0[4];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[4];
    s16 unkEE;
    u8 padF0[8];
    s16 unkF8;
    u8 padFA[0x144 - 0xFA];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
} ActorMoveView;

#define ACTOR_MOVE_VIEW ((ActorMoveView *)gCurrentActor)

extern s16 D_8075033C;
extern u32 gGlobalOverlayFlags;
f32 mathCosF(s16);
f32 mathSinF(s16);
void func_8002F490(void *);


#define S ((ActorMoveState *)arg0)
void func_8068F72C(arg0, arg1, applyBuoyancy, tilt)
void *arg0;
s32 arg1;
u8 applyBuoyancy;
u8 tilt;
{
    f32 fa0;
    s32 kongState;
    f32 drag;
    f32 turnRate;
    f32 fv0;
    s16 tiltPitch;
    s16 tiltRoll;
    u8 fl[4];
    f32 velX;
    f32 velZ;
    f32 thrust;
    s16 slopeAngle;
    s16 slopeRange;
    ActorMoveView *pl;

    pl = (ActorMoveView *)gPlayerSlots[S->unk28].actor;
    kongState = pl->unk58;
    tiltPitch = 0;
    tiltRoll = 0;
    fl[3] = ACTOR_MOVE_VIEW->unk80 <= ACTOR_MOVE_VIEW->unkAC + 1.0f;
    fl[2] = ACTOR_MOVE_VIEW->unk6A & 1;
    if (!(ACTOR_MOVE_VIEW->unk60 & 0x10)) {
        ACTOR_MOVE_VIEW->unk60 |= 0x10400;
        ACTOR_MOVE_VIEW->unk154 = 0;
        ACTOR_MOVE_VIEW->unk155 = 0;
        ACTOR_MOVE_VIEW->unkB8 = 0.0f;
        S->unk34 = 0;
        S->unk35 = 0;
        if (S->unk27 == 0) {
            ACTOR_MOVE_VIEW->unk144 = 0x3C;
            ACTOR_MOVE_VIEW->unkC4 = -20.0f;
        } else {
            ACTOR_MOVE_VIEW->unk144 |= 0x18;
            ACTOR_MOVE_VIEW->unkC4 = -30.0f;
        }
        ACTOR_MOVE_VIEW->unkC8 = -900.0f;
        ACTOR_MOVE_VIEW->unkF8 = 0x12C;
    }
    velX = mathSinF(ACTOR_MOVE_VIEW->unkEE) * ACTOR_MOVE_VIEW->unkB8;
    velZ = mathCosF(ACTOR_MOVE_VIEW->unkEE) * ACTOR_MOVE_VIEW->unkB8;
    if (fl[3] != 0) {
        thrust = S->unk4 * 50.0f;
        if (kongState == 2) {
            fa0 = 5000.0f;
        } else {
            fa0 = 10000.0f;
        }
        drag = 1.0f / fa0 * (ACTOR_MOVE_VIEW->unkB8 * ACTOR_MOVE_VIEW->unkB8) + S->unk8;
        if (S->unk4 != 0.0f) {
            drag = drag + 30.0f;
        } else {
            drag = drag + 3.0f;
        }
    } else {
        fv0 = 2.0f;
        if (fl[2] != 0) {
            thrust = S->unk4 * 4.0f;
            drag = S->unk8 + ACTOR_MOVE_VIEW->unkB8 * ACTOR_MOVE_VIEW->unkB8 * 0.00002f + fv0;
        } else {
            thrust = S->unk4 * fv0;
            drag = S->unk8 + ACTOR_MOVE_VIEW->unkB8 * ACTOR_MOVE_VIEW->unkB8 * 0.00002f + fv0;
        }
    }
    velX += mathSinF(S->unk0) * thrust;
    velZ += mathCosF(S->unk0) * thrust;
    ACTOR_MOVE_VIEW->unkB8 = sqrtf(velX * velX + velZ * velZ);
    ACTOR_MOVE_VIEW->unkEE = (s16)(s32)(mathAtan2(velX, velZ) * 4096.0 / 6.2831854820251465);
    if (fl[2] != 0) {
        slopeRange = 0x400 - ACTOR_MOVE_VIEW->unkDE;
        slopeAngle = mathAngleSignedDistance(ACTOR_MOVE_VIEW->unkDC, S->unk0);
        fv0 = (f32)slopeRange;
        tiltPitch = (s16)(s32)(mathCosF(slopeAngle) * fv0);
        tiltRoll = (s16)(s32)(mathSinF(slopeAngle) * fv0);
    } else if (!tilt) {
        ACTOR_MOVE_VIEW->unkE8 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE8, 0, 4.0f);
        ACTOR_MOVE_VIEW->unkE4 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE4, 0, 5.0f);
    }
    turnRate = S->unk10 * S->unkC;
    if (tilt) {
        tiltRoll = (s32)((f32)tiltRoll + turnRate * 200.0f);
        tiltRoll &= 0xFFF;
        if (fl[3] != 0 || fl[2] != 0) {
            tiltPitch = (s32)((f64)tiltPitch + ((f64)(S->unk4 * -50.0f) + (f64)ACTOR_MOVE_VIEW->unkB8 * -0.5));
            tiltPitch &= 0xFFF;
        } else {
            tiltPitch = ACTOR_MOVE_VIEW->unkE8;
        }
        ACTOR_MOVE_VIEW->unkE8 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE8, tiltPitch, 4.0f);
        ACTOR_MOVE_VIEW->unkE4 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE4, tiltRoll, 5.0f);
    }
    ACTOR_MOVE_VIEW->unkB8 = ACTOR_MOVE_VIEW->unkB8 - drag;
    velX = ACTOR_MOVE_VIEW->unkB8;
    if (velX < 0.0f) {
        ACTOR_MOVE_VIEW->unkB8 = 0.0f;
        velX = ACTOR_MOVE_VIEW->unkB8;
    }
    fv0 = velX - ACTOR_MOVE_VIEW->unkBC;
    if (fv0 < 0.0f) {
        fv0 = 0.0f;
    }
    if (kongState == 2) {
        tiltRoll = -0x1E;
    } else {
        if (tiltRoll && tiltRoll) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        tiltRoll = -0x28;
    }
    S->unk0 = (s32)((f64)S->unk0 + (f64)(turnRate * (f32)tiltRoll) * (1.0 + (f64)fv0 * 0.05));
    S->unk0 = S->unk0 & 0xFFF;
    if (applyBuoyancy) {
        fa0 = ACTOR_MOVE_VIEW->unk80;
        drag = ACTOR_MOVE_VIEW->unkAC;
        if (fa0 < drag) {
            if (fl[3] != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            ACTOR_MOVE_VIEW->unkC0 = ACTOR_MOVE_VIEW->unkC0 + ((ACTOR_MOVE_VIEW->unkAC - fa0) * 3.0f + 15.0f);
            fv0 = ACTOR_MOVE_VIEW->unkC0;
            if (fv0 > 0.0f) {
                fa0 = fv0;
            } else {
                fa0 = -fv0;
            }
            if (fa0 > 20.0f) {
                ACTOR_MOVE_VIEW->unkC0 = fv0 - fv0 / 12.0f;
            }
        }
    }
    ACTOR_MOVE_VIEW->unkC0 = ACTOR_MOVE_VIEW->unkC0 + ACTOR_MOVE_VIEW->unkC4;
    if (((ActorMoveStepFlag *)arg1)->unk4 != 0) {
        ((ActorMoveStepFlag *)arg1)->unk4 = 0;
        if (fl[3] != 0) {
            if (kongState == 2) {
                ACTOR_MOVE_VIEW->unkC0 = 200.0f;
            } else {
                ACTOR_MOVE_VIEW->unkC0 = (f32)D_8075033C;
            }
        } else if (fl[2] != 0) {
            ACTOR_MOVE_VIEW->unkC0 = ACTOR_MOVE_VIEW->unkC0 + 200.0f;
        }
    }
    fv0 = ACTOR_MOVE_VIEW->unkC8;
    if (ACTOR_MOVE_VIEW->unkC0 < fv0) {
        ACTOR_MOVE_VIEW->unkC0 = fv0;
    }
    if (kongState == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    actorStepPhysics(gCurrentActor, ACTOR_MOVE_VIEW->unkE6, S->unk0);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (!applyBuoyancy) {
        if (ACTOR_MOVE_VIEW->unk80 < ACTOR_MOVE_VIEW->unkAC) {
            ACTOR_MOVE_VIEW->unk80 = ACTOR_MOVE_VIEW->unkAC;
            ACTOR_MOVE_VIEW->unkC0 = ACTOR_MOVE_VIEW->unkC4;
        }
    }
    if (gGlobalOverlayFlags & 0x2000) {
        func_8002F490(arg0);
    }
    if (fl[2] != 0 && !(ACTOR_MOVE_VIEW->unk6C & 1)) {
        ACTOR_MOVE_VIEW->unkC0 = -10.0f;
    }
    ACTOR_MOVE_VIEW->unkE6 = (S->unk0 + S->unk2) & 0xFFF;
}
#undef S

typedef struct ProjectileActorSub4 {
    u8 pad0[0x1C];
    void *unk1C;
} ProjectileActorSub4;

typedef struct ProjectileActorBase {
    u8 pad0[4];
    ProjectileActorSub4 *unk4;
} ProjectileActorBase;

typedef struct ProjectileAngleTarget {
    u8 pad0[0xC];
    f32 unkC;
} ProjectileAngleTarget;

typedef struct ProjectileAngleStep {
    s16 unk0;
    s16 unk2;
} ProjectileAngleStep;

typedef struct ProjectileAngleSub1C {
    s8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
} ProjectileAngleSub1C;



void actorInterpolateAngles(u8 resetting, ProjectileAngleTarget *target, ProjectileAngleStep *step) {
    f32 pitchGoal;
    f32 yawGoal;
    ProjectileAngleSub1C *angles;

    angles = ((ProjectileActorSub4 *)gCurrentActor->sub4)->unk1C;
    if (resetting) {
        pitchGoal = 500.0f;
        yawGoal = 0.0f;
    } else {
        pitchGoal = 0.0f;
        yawGoal = (f32)((f64)target->unkC * (400.0 - (0.7 * (f64)gCurrentActor->speedXZ)));
    }
    step->unk2 = mathAngleEaseToward(step->unk2, (s16)(s32)pitchGoal, 5.0f);
    step->unk0 = mathAngleEaseToward(step->unk0, (s16)((s32)yawGoal & 0xFFF), 3.0f);
    angles->unk0 = -0x80;
    angles->unk1 = 1;
    angles->unk2 = (u16)step->unk2 * 16;
    angles->unk4 = (u16)step->unk0 * 16;
    angles->unk6 = 0;
    angles->unk8 = 0;
}


void actorAllocSubBuffer(Actor *actor, s32 count) {
    ((ProjectileActorBase *)actor)->unk4->unk1C = heapAlloc(count * 8);
    heapClearBlock(((ProjectileActorBase *)actor)->unk4->unk1C);
}


void actorInitAnimations(Actor *actor, Actor *owner) {
    u8 volume;
    ProjectileActorSub174 *ownerState;

    volume = 0;
    ownerState = owner->customState;
    playerStateQueueCallback(0x4C, actor, ownerState->unk1A4);
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

typedef struct FloatAt4View {
    u8 pad0[4];
    f32 unk4;
} FloatAt4View;
extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void func_80690190(state, unused)
FloatAt4View *state;
s16 unused;
{
    s16 idx;

    idx = D_80770628[gCurrentActor->soundSlots[0]];
    if (gCurrentActor->y < gCurrentActor->waterY + 4.0f) {
        D_80770B68[idx] = ((f64)gCurrentActor->speedXZ / 300.0) + 1.0;
        D_80770BC0[idx] = 1.0f;
    } else {
        D_80770B68[idx] = (f64)state->unk4 + 1.2;
        D_80770BC0[idx] = 5.0f;
    }

    idx = D_80770628[gCurrentActor->soundSlots[1]];
    if (gCurrentActor->y < gCurrentActor->waterY + 4.0f) {
        if (D_80770BC0[idx] == 0.0f) {
            D_80770B68[idx] = (((f64)(u32)randomLcgNext() / 4294967295.0) * 0.05 + 0.975) * (0.2 + ((f64)gCurrentActor->speedXZ / 300.0));
            D_80770BC0[idx] = 1.0f;
        }
    } else {
        D_80770B68[idx] = ((f64)state->unk4 * 1.5) + 0.2;
        D_80770BC0[idx] = 8.0f;
    }
}

typedef struct SpawnCoord {
    s16 x;
    s16 y;
    s16 z;
    u8 yaw;
} SpawnCoord;

typedef struct SpawnPointActor {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
} SpawnPointActor;


void actorInitFromSpawnPoint(SpawnPointActor *actor, ProjectileActorSub174 *state) {
    SpawnCoord *spawn;
    s16 yaw;

    spawn = func_806C96C4(state->unk36);
    actor->unk7C = spawn->x;
    actor->unk80 = spawn->y;
    actor->unk84 = spawn->z;
    yaw = (u32)spawn->yaw * 16.062746f;
    actor->unkE6 = yaw;
    actor->unkEE = yaw;
    state->unk0 = yaw;
}

extern Actor *gSpawnedActor;

void actorSpawnChildActor(Actor *parent) {
    ProjectileActorSub174 *parentState = parent->customState;
    ProjectileActorSub174 *childState;
    s32 pad;
    Actor *child;

    actorSpawn(0x13F, 0xDA);
    child = gSpawnedActor;
    childState = child->customState;
    childState->unk28 = parentState->unk1A4;
    actorInitAnimations(child, parent);
    childState->unk35 = 0;
    childState->unk27 = 0;
    childState->unk0 = parent->yaw;
    parentState->unk88 = child;
    child->flags &= ~0x20000;
}

typedef struct PlayerActor104 {
    u8 pad0[0x174];
    CamState *unk174;
} PlayerActor104;

typedef struct PlayerActorSub174 {
    u8 pad0[0x104];
    PlayerActor104 *unk104;
    u8 pad108[0x1A4 - 0x108];
    u8 unk1A4;
} PlayerActorSub174;

typedef struct PlayerInteractionActor {
    u8 pad0[0x174];
    PlayerActorSub174 *unk174;
} PlayerInteractionActor;

typedef struct ActorPlayerInteraction {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[0xC4 - 0x6C];
    f32 unkC4;
    u8 padC8[0x144 - 0xC8];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    ProjectileActorSub174 *unk174;
    void *unk178;
} ActorPlayerInteraction;
#define G_PLAYER_INTERACT_ACTOR ((ActorPlayerInteraction *)gCurrentActor)

extern u8 gGameMode;
extern f32 D_80750300;
extern Actor *gPrimaryPlayerActor;
void lensFlareAddSource(f32, f32, s32, f32, f32, f32, f32, s32, s32, s32); // FAKE: callee prototype steer

void actorUpdatePlayerInteraction(void) {
    ProjectileActorSub174 *state;
    PlayerInteractionActor *playerActor;
    PlayerActorSub174 *playerState;
    s32 angleStep;
    CamState *camState;
    u8 resetting;
    f32 nodeX;
    f32 nodeY;
    s32 nodeZ;

    state = G_PLAYER_INTERACT_ACTOR->unk174;
    angleStep = (s32)G_PLAYER_INTERACT_ACTOR->unk178;
    playerActor = (PlayerInteractionActor *)gPlayerSlots[state->unk28].actor;
    playerState = playerActor->unk174;
    camState = playerState->unk104->unk174;
    resetting = G_PLAYER_INTERACT_ACTOR->unk6A & 1;
    state->unk34 = 2;
    func_80690190(state, angleStep, playerState);
    if (gGameMode == 0 && camState->unkF3 != 4) {
        camSetTargetScaled(playerState->unk104, gCurrentActor, 4, 0x800, 0xA0, 0, 6, 0x12C, 0x8F, 0, 0.2f);
    }
    func_8068F72C(state, angleStep, 1, 1);
    actorInterpolateAngles(resetting, (ProjectileAngleTarget *)state, (ProjectileAngleStep *)angleStep);
    if (!(G_PLAYER_INTERACT_ACTOR->unk60 & 0x10)) {
        G_PLAYER_INTERACT_ACTOR->unkC4 = D_80750300;
        G_PLAYER_INTERACT_ACTOR->unk144 = 0x3C;
        playerStateQueueCallback(0x4C, gCurrentActor, playerState->unk1A4);
    }
    if (camIsCutsceneActive() == 0 || (camIsCutsceneActive() != 0 && (gPrimaryPlayerActor->contactFlags & 0x100))) {
        actorGetNodePos(gCurrentActor, 1, &nodeX, &nodeY, (f32 *)&nodeZ);
        lightAdd(nodeX, nodeY, nodeZ, 0.0f, 0.0f, 0.0f, 300.0f, 0, 0xFF, 0xFF, 0xFF);
        if (flagGet(0x6B, 2) == 0) {
            if (camIsCutsceneActive() != 0 && (gPrimaryPlayerActor->contactFlags & 0x100)) {
                actorGetNodePos(gCurrentActor, 2, &nodeX, &nodeY, (f32 *)&nodeZ);
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

extern u8 D_80750270;
void projectileSetSpawnFlag(void) {
    D_80750270 = 1;
}

extern f32 D_807FC7B0;
extern f32 D_807FC7B4;
extern f32 D_807FC7B8;
void projectileSetTargetCoords(f32 x, f32 y, f32 z) {
    D_807FC7B0 = x;
    D_807FC7B4 = y;
    D_807FC7B8 = z;
}

#include "actor.h"

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} ProjectileSpawnParams;
typedef struct {
    s16 unk0;
    char pad2[6];
    f32 unk8;
    f32 unkC;
    u8 pad10;
    u8 unk11;
} ProjectileTrackerSub174;
extern s32 gCamActor;
extern u8 D_80750AD0;

void projectileGetTargetCoords(Actor *actor, s32 node) {
    actorGetNodePos(actor, node, &D_807FC7B0, &D_807FC7B4, &D_807FC7B8);
}

void projectileSpawnNodeEntry(s16 type, s16 param, f32 speed, s16 yaw, f32 horizSpeed, f32 vertSpeed, s32 flags) {
    ProjectileSpawnParams params;

    params.unk0 = (f32)(((f64)yaw / 4095.0) * 6.28318548202514648);
    params.unk4 = horizSpeed;
    params.unkC = speed;
    params.unk8 = vertSpeed;
    params.unk10 = (f32)param;
    params.unk14 = (f32)(u32)D_80750270;
    actorListSpawnNodeEntry(type, D_807FC7B0, D_807FC7B4, D_807FC7B8, 0, speed, flags, &params);
    D_80750270 = 0;
}

void projectileCalculateTrajectoryAndSpawn(s16 yaw, s16 type, s16 param, f32 speed, f32 targetX, f32 targetY, f32 targetZ, f32 flightTime, s32 flags) {
    f32 dist;
    f32 dy;

    dist = sqrtf(((targetX - D_807FC7B0) * (targetX - D_807FC7B0)) + ((targetY - D_807FC7B4) * (targetY - D_807FC7B4)) + ((targetZ - D_807FC7B8) * (targetZ - D_807FC7B8)));
    dy = targetY - D_807FC7B4;
    projectileSpawnNodeEntry(type, param, speed, yaw, sqrtf(((targetX - D_807FC7B0) * (targetX - D_807FC7B0)) + ((targetZ - D_807FC7B8) * (targetZ - D_807FC7B8))) / (dist / flightTime), dy / (dist / flightTime), flags);
}

void projectileAimAndSpawn(s16 type, s16 param, f32 speed, f32 targetX, f32 targetY, f32 targetZ, f32 flightTime, s32 flags) {
    projectileCalculateTrajectoryAndSpawn(mathAngleBetweenPoints2D(targetX, targetZ, D_807FC7B0, D_807FC7B8), type, param, speed, targetX, targetY, targetZ, flightTime, flags);
}

void projectileClampAngleAndSpawn(s16 centerYaw, s16 maxSpread, s16 type, s16 param, f32 speed, f32 targetX, f32 targetY, f32 targetZ, f32 flightTime, s32 flags) {
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
    projectileCalculateTrajectoryAndSpawn(yaw, type, param, speed, targetX, targetY, targetZ, flightTime, flags);
}

void projectileAimFromActorAndSpawn(s16 type, s16 param, f32 speed, Actor *target, s32 node, f32 flightTime, s32 flags) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    actorGetNodePos(target, node, &nodeX, &nodeY, &nodeZ);
    projectileAimAndSpawn(type, param, speed, nodeX, nodeY, nodeZ, flightTime, flags);
}

typedef struct OwnerPlayerStateView {
    u8 pad0[0x104];
    Actor *unk104;
} OwnerPlayerStateView;
typedef struct ProjectileHomingState {
    u8 pad0[0x14];
    f32 unk14;
    u8 pad18[4];
    Actor *unk1C;
} ProjectileHomingState;
extern u32 gGlobalOverlayFlags;
void func_800268C0(s32);

void projectileSteerTowardTarget(collisionMask, proj, trailEffect, straight)
u16 collisionMask;
Actor *proj;
void *trailEffect;
u8 straight;
{
    OwnerPlayerStateView *ownerState; // named pointer-chain locals: colour the two chain loads into v0/v1
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
    ProjectileHomingState *homing;
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    f32 heightOffset;
    f32 steps;

    homing = proj->customState;
    if (!((f64)proj->speedXZ < 0.1)) {
        if (trailEffect != 0) {
            ownerState = ((Actor *)proj->parentActor)->customState;
            camState = ownerState->unk104->customState;
            if (camState->unkF3 == 3) {
                effectSetCallback(effectLifetimeCountdownUpdate);
                effectSetSpeed(0x32);
                effectCreateAtPosition(trailEffect, homing->unk14, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
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
                    homing->unk1C = target;
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
        } else if (homing->unk1C != NULL) {
            if (gGlobalOverlayFlags & 0x04000000) {
                func_800268C0(4);
            }
            homing->unk1C = NULL;
        }
    }
}

typedef struct ModelSlotPosTypeView {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x84 - 0xC];
    s16 unk84;
    u8 pad86[0x90 - 0x86];
} ModelSlotPosTypeView;

extern ModelSlotPosTypeView *gModelSlots;
extern s32 D_80747D70;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
f32 mathCosF(s16);
f32 mathSinF(s16);

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
    PlayerStruct *pl;
    u8 idx;
    ProjectileActorSub174 *sub;
    f32 d[3];
    f32 n[3];
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
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d2x;
    f32 d2z;
    f32 tmp;

    ret = 0;
    best = 0.7f;
    if (useAim) {
        best = 0.92f;
    }
    *outTarget = NULL;
    if (useAim) {
        idx = ((ProjectileActorSub174 *)proj->customState)->unk1A4;
        pl = &gPlayerSlots[0] + idx; // FAKE: base-plus-index spelling keeps the target t8/t9 ring order
        aimX = pl->focusX;
        aimY = pl->focusY;
        aimZ = pl->focusZ;
        ox = pl->camX;
        oy = pl->camY;
        oz = pl->camZ;
    } else {
        scale = proj->speedXZ * 0.025f;
        aimX = mathSinF(proj->moveYaw) * scale + proj->x;
        aimZ = mathCosF(proj->moveYaw) * scale + proj->z;
        aimY = proj->y + proj->speedY * 0.025f;
        ox = proj->x;
        oy = proj->y;
        oz = proj->z;
    }
    d[0] = aimX - ox;
    d[1] = aimY - oy;
    d[2] = aimZ - oz;
    len = sqrtf((d[0] * d[0] + d[1] * d[1]) + d[2] * d[2]);
    if (len == 0.0) {
        len = 0.1f;
    }
    dirX = d[0] / len;
    dirY = d[1] / len;
    dirZ = d[2] / len;
    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (proj != actor && (!(actor->collisionFlags & 2) || actor->state != 0x37) && (actor->collisionFlags & collisionMask)) {
            if (levelOnly == 0 || ((oy < actor->y) ? (actor->y - oy) : -(actor->y - oy)) < 30.0f) {
                active = 1;
                if (actor->collisionFlags & 1) {
                    sub = actor->customState;
                    active = gPlayerSlots[sub->unk1A4].unk0;
                }
                if (active != 0) {
                    tmp = (f32)((f64)actor->y + (f64)actor->eyeHeight * 0.5);
                    d[0] = actor->x - ox;
                    t = tmp - oy;
                    d[1] = t;
                    d[2] = actor->z - oz;
                    len = sqrtf((d[0] * d[0] + d[1] * d[1]) + d[2] * d[2]);
                    if (len == 0.0) {
                        len = 0.1f;
                    }
                    n[0] = d[0] / len;
                    n[1] = d[1] / len;
                    n[2] = d[2] / len;
                    dot = (n[0] * dirX + n[1] * dirY) + n[2] * dirZ;
                    if (dot < 0.0) {
                        dot = 0.0f;
                    }
                    if (best < dot) {
                        d2x = actor->x - ox;
                        d2z = actor->z - oz;
                        if (sqrtf(d2x * d2x + t * t + d2z * d2z) < 1000.0f) {
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
        if (D_80747D70 > 0) {
            j = 0; do { // LAYOUT: init and do on one line (one as1 line) steers the loop-limit candidate priority
                switch (((ModelSlotPosTypeView *)((u8 *)gModelSlots + j))->unk84) {
                    case 0x125:
                    case 0x126:
                    case 0x127:
                    case 0x128:
                    case 0x129:
                        px = ((ModelSlotPosTypeView *)((u8 *)gModelSlots + j))->unk0;
                        py = ((ModelSlotPosTypeView *)((u8 *)gModelSlots + j))->unk4 + 10.0;
                        pz = ((ModelSlotPosTypeView *)((u8 *)gModelSlots + j))->unk8;
                        dx = px - ox;
                        dy = py - oy;
                        dz = pz - oz;
                        d[0] = dx;
                        d[1] = dy;
                        d[2] = dz;
                        len = sqrtf((d[0] * d[0] + d[1] * d[1]) + d[2] * d[2]);
                        if (len == 0.0) {
                            len = 0.1f;
                        }
                        n[0] = d[0] / len;
                        n[1] = d[1] / len;
                        n[2] = d[2] / len;
                        dot = (n[0] * dirX + n[1] * dirY) + n[2] * dirZ;
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
                j += 0x90;
            } while (j < D_80747D70 * 0x90);
        }
    }
    return ret;
}

void effectSetColor(s32, s32, s32, s32); // FAKE: callee prototype steer
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

void projectileSpawnActor107(u8 mode, u8 value, f32 rate, f32 limit, u8 alpha, u8 spin) {
    ProjectileTrackerSub174 *sub;

    actorSpawn(0x107, 0);
    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.15f);
    sub = gSpawnedActor->customState;
    sub->unk11 = mode;
    sub->unk8 = rate;
    sub->unkC = limit;
    sub->unk0 = value;
    gSpawnedActor->y = gCurrentActor->unkA8;
    gSpawnedActor->unk15F = alpha;
    gSpawnedActor->yawSpeed = spin;
}

typedef struct ProjectileSpawnCfg {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} ProjectileSpawnCfg;

typedef struct ProjectileBounceState {
    u32 unk0;
    u8 pad4[0xE];
    u8 unk12;
    u8 unk13;
} ProjectileBounceState;

typedef struct ActorTypeView {
    u8 pad0[0x58];
    s32 unk58;
} ActorTypeView;

typedef struct ProjectileBounceActor {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[4];
    u32 unk60;
    u8 pad64[6];
    u16 unk6A;
    u8 pad6C[2];
    s16 unk6E;
    u8 pad70[0xC];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x9C - 0x88];
    f32 unk9C;
    f32 unkA0;
    u8 padA4[0xB8 - 0xA4];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0xE6 - 0xC4];
    s16 unkE6;
    u8 padE8[4];
    s16 unkEC;
    s16 unkEE;
    u8 padF0[0xFC - 0xF0];
    u8 unkFC;
    u8 padFD[0x11C - 0xFD];
    ActorTypeView *unk11C;
    u8 pad120[4];
    ProjectileSpawnCfg *unk124;
    u8 pad128[0x132 - 0x128];
    s16 unk132;
    u8 pad134[0x144 - 0x134];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    ProjectileBounceState *unk174;
} ProjectileBounceActor;

#define PROJECTILE_BOUNCE_ACTOR ((ProjectileBounceActor *)gCurrentActor)

extern u8 D_80720340;
extern u8 D_8072038C;
extern u32 gGameFrameCounter;
extern s16 D_80750344;
extern u8 D_807FBB85;

void projectileBounceParticleUpdate(void *effectCfg) {
    f32 radius;
    ProjectileBounceState *state;
    s32 yawOffset;
    u32 radiusPick;
    f32 cfg;

    state = PROJECTILE_BOUNCE_ACTOR->unk174;
    cfg = PROJECTILE_BOUNCE_ACTOR->unk124->unkC;
    if (!(PROJECTILE_BOUNCE_ACTOR->unk60 & 0x10)) {
        PROJECTILE_BOUNCE_ACTOR->unkA0 = PROJECTILE_BOUNCE_ACTOR->unk9C = PROJECTILE_BOUNCE_ACTOR->unk80;
        PROJECTILE_BOUNCE_ACTOR->unk6E = -2;
        PROJECTILE_BOUNCE_ACTOR->unk6A = PROJECTILE_BOUNCE_ACTOR->unk6A & ~1;
        PROJECTILE_BOUNCE_ACTOR->unkEE = (s16)((PROJECTILE_BOUNCE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        PROJECTILE_BOUNCE_ACTOR->unkE6 = PROJECTILE_BOUNCE_ACTOR->unkEE;
        PROJECTILE_BOUNCE_ACTOR->unkB8 = PROJECTILE_BOUNCE_ACTOR->unk124->unk4;
        PROJECTILE_BOUNCE_ACTOR->unkC0 = PROJECTILE_BOUNCE_ACTOR->unk124->unk8;
        if (PROJECTILE_BOUNCE_ACTOR->unk11C != NULL && PROJECTILE_BOUNCE_ACTOR->unk11C->unk58 == 0xD2) {
            PROJECTILE_BOUNCE_ACTOR->unk144 = 0x24;
        } else {
            PROJECTILE_BOUNCE_ACTOR->unk144 = 0x3C;
        }
        state->unk13 = (u8)(u32)PROJECTILE_BOUNCE_ACTOR->unk124->unk10;
        if (state->unk13 != 0) {
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
        effectCreateAtActorBone(effectCfg, cfg, gCurrentActor, 1, 2);
        if (state->unk13 >= 0xB) {
            PROJECTILE_BOUNCE_ACTOR->unk132 = 2;
        }
        state->unk0 = gGameFrameCounter;
        if (state->unk13 == 5) {
            state->unk0 = state->unk0 - D_80750344 + 0x1E;
        }
        state->unk12 = 0;
        PROJECTILE_BOUNCE_ACTOR->unk60 |= 0x80000;
        PROJECTILE_BOUNCE_ACTOR->unkEC = 0;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    if (PROJECTILE_BOUNCE_ACTOR->unk144 & 8) {
        actorUpdateFloorContactAndTilt(gCurrentActor, state->unk13 != 0 ? cfg * 6.0 * 4.0 : 0.0);
    }
    if (state->unk13 >= 0xA) {
        if (state->unk13 == 0x1E) {
            billboardSetFlags(3);
        }
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x320, 0x78, 0, 1.0f);
        if (PROJECTILE_BOUNCE_ACTOR->unk6A & 1) {
            if (state->unk12 == 0) {
                switch (state->unk13) {
                case 11:
                    projectileSpawnActor107(0, 0, 5.0f, 2.0f, 1, 0);
                    break;
                case 20:
                    projectileSpawnActor107(1, 7, 5.0f, 3.0f, 0xC8, 0x20);
                    break;
                }
                camStartShake(gCamActor, 0xA, 0x14);
                state->unk12 = 2;
            } else {
                state->unk12 = state->unk12 - 1;
            }
        }
    } else {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x78, 0x78, 0, 1.0f);
        if ((PROJECTILE_BOUNCE_ACTOR->unk6A & 1) && state->unk12 == 0 && (PROJECTILE_BOUNCE_ACTOR->unk144 & 8)) {
            state->unk12 = 0xA;
        }
        if (state->unk12 != 0) {
            effectSetDepth(1);
            effectSetDuration(1);
            effectSetCallback(effectSpinBillboardingUpdate);
            effectCreateAtPosition(&D_80720340, PROJECTILE_BOUNCE_ACTOR->unk124->unkC, PROJECTILE_BOUNCE_ACTOR->unk7C, PROJECTILE_BOUNCE_ACTOR->unk80, PROJECTILE_BOUNCE_ACTOR->unk84);
            state->unk12 = state->unk12 - 1;
        }
    }
    if (PROJECTILE_BOUNCE_ACTOR->unkEC == 0) {
        f32 dx = PROJECTILE_BOUNCE_ACTOR->unk7C - gPlayerSlots->camX;
        f32 dy = PROJECTILE_BOUNCE_ACTOR->unk80 - gPlayerSlots->camY;
        dx = dx * dx;
        dx = dy * dy + dx;
        dy = PROJECTILE_BOUNCE_ACTOR->unk84 - gPlayerSlots->camZ;
        dx = dy * dy + dx;
        if (dx < 20000.0f) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x128, 0xFF, 0x7F, 0);
            PROJECTILE_BOUNCE_ACTOR->unkEC = PROJECTILE_BOUNCE_ACTOR->unkEC + 1;
        }
    }
    if (PROJECTILE_BOUNCE_ACTOR->unkFC != 0 || state->unk12 == 1 || D_807FBB85 != 0) {
        effectSetDepth(1);
        effectSetDuration(1);
        if (PROJECTILE_BOUNCE_ACTOR->unk58 != 0x3B && state->unk13 != 0x63) {
            effectSetSpeed(0x100FA);
            effectSetCallback(effectLightPulseOscillate);
        }
        effectCreateAtPosition(&D_80720340, 2.0 * PROJECTILE_BOUNCE_ACTOR->unk124->unkC, PROJECTILE_BOUNCE_ACTOR->unk7C, PROJECTILE_BOUNCE_ACTOR->unk80, PROJECTILE_BOUNCE_ACTOR->unk84);
        if (state->unk13 < 0xA) {
            for (yawOffset = -0x12C; yawOffset != 0x12C; yawOffset += 0x32) {
                effectSetDepth(1);
                effectSetDuration(2);
                effectSetSpeed((PROJECTILE_BOUNCE_ACTOR->unkEE + yawOffset) % 4095);
                effectSetCallback(func_8071BC80);
                effectCreateAtPosition(&D_8072038C, PROJECTILE_BOUNCE_ACTOR->unk124->unkC * 0.5, PROJECTILE_BOUNCE_ACTOR->unk7C, PROJECTILE_BOUNCE_ACTOR->unk80, PROJECTILE_BOUNCE_ACTOR->unk84);
            }
        }
        sfxPlayAtPositionPooled(PROJECTILE_BOUNCE_ACTOR->unk7C, PROJECTILE_BOUNCE_ACTOR->unk80, PROJECTILE_BOUNCE_ACTOR->unk84, 0xF6, 0xFF, 0x7F, 0x1E, 0x1E, 0.7f, 0);
        actorDespawn(gCurrentActor);
    }
    if (state->unk0 + D_80750344 < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

typedef struct SparkleParticleState {
    u32 unk0;
    char pad4[0xE];
    u8 unk12;
    u8 unk13;
} SparkleParticleState;

typedef struct SparkleConfig124 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} SparkleConfig124;

typedef struct SparkleProjectileActor {
    u8 pad0[0x60];
    u32 unk60;
    u32 unk64;
    u16 unk68;
    u16 unk6A;
    u8 pad6C[2];
    s16 unk6E;
    u8 pad70[0xB8 - 0x70];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFC - 0xF0];
    u8 unkFC;
    u8 padFD[0x124 - 0xFD];
    SparkleConfig124 *unk124;
    u8 pad128[0x144 - 0x128];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    void *unk174;
} SparkleProjectileActor;

#define G_SPARKLE_ACTOR ((SparkleProjectileActor *)gCurrentActor)

extern u8 D_80720120;
extern u8 D_80720BE8;

void projectileSparkleUpdate(s32 silver) {
    SparkleParticleState *state;

    state = (SparkleParticleState *)G_SPARKLE_ACTOR->unk174;
    if (!(G_SPARKLE_ACTOR->unk60 & 0x10)) {
        G_SPARKLE_ACTOR->unk6A &= (G_SPARKLE_ACTOR->unk6E = -2);
        G_SPARKLE_ACTOR->unkEE = (s16)((G_SPARKLE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_SPARKLE_ACTOR->unkB8 = G_SPARKLE_ACTOR->unk124->unk4;
        G_SPARKLE_ACTOR->unkC0 = G_SPARKLE_ACTOR->unk124->unk8;
        G_SPARKLE_ACTOR->unk144 = 0x3C;
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
            effectCreateAtActorBone(&D_80720120, G_SPARKLE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
            break;
        case 1:
            effectSetColor(0xC8, 0xC8, 0xFA, 0x9B);
            effectCreateAtActorBone(&D_80720BE8, G_SPARKLE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
            break;
        }
        state->unk13 = (u8)(u32)G_SPARKLE_ACTOR->unk124->unk10;
        state->unk0 = gGameFrameCounter;
        state->unk12 = 0;
        G_SPARKLE_ACTOR->unk60 |= 0x80000;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    if ((G_SPARKLE_ACTOR->unk6A & 1) || (G_SPARKLE_ACTOR->unkFC != 0) || (D_807FBB85 != 0) || ((u32)(state->unk0 + 24) < gGameFrameCounter)) {
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

#include "actor.h"

typedef struct ProjectileConfig124 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} ProjectileConfig124;

typedef struct PlayerTrackActorSub {
    u8 pad0[0x104];
    s32 unk104;
} PlayerTrackActorSub;

typedef struct PlayerTrackActor {
    u8 pad0[0x174];
    PlayerTrackActorSub *unk174;
} PlayerTrackActor;

typedef struct ProjectileActorExtra {
    u32 unk0;
    u8 pad4[0x13 - 4];
    u8 unk13;
    f32 unk14;
    u8 pad18[4];
    s32 unk1C;
} ProjectileActorExtra;

typedef struct ProjectilePhysicsActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[0x7C - 0x6C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFA - 0xF0];
    s16 unkFA;
    u8 hasArcBounds;
    u8 unkFD;
    u8 padFE[0x11C - 0xFE];
    Actor *unk11C;
    u8 pad120[4];
    ProjectileConfig124 *unk124;
    u8 pad128[0x144 - 0x128];
    u8 unk144;
    u8 pad145[0x16E - 0x145];
    u8 unk16E;
    u8 unk16F;
    u8 pad170[0x174 - 0x170];
    void *unk174;
} ProjectilePhysicsActor;

extern u8 D_80720020;
extern u8 D_807202D0;
extern s16 D_807502D0;
extern f32 D_807502E4;
extern ActorGlobalState gActorGlobalState;
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
    ProjectileActorExtra *extra;
    f32 temp;

    extra = (ProjectileActorExtra *)gCurrentActor->customState;
    projectileBounceParticleUpdate(&D_807201D4);
    if (extra->unk13 == 1) {
        ((ProjectilePhysicsActor *)gCurrentActor)->unkC0 += D_807502E4;
        temp = (f32)D_807502D0;
        if (((ProjectilePhysicsActor *)gCurrentActor)->unkC0 < temp) {
            ((ProjectilePhysicsActor *)gCurrentActor)->unkC0 = temp;
        }
    }
}

#define G_PROJECTILE_ACTOR ((ProjectilePhysicsActor *)gCurrentActor)

void projectileDespawnOrExplode(void) {
    u32 *spawnFrame;
    u8 unkFC;
    Actor *other;

    spawnFrame = (u32 *)G_PROJECTILE_ACTOR->unk174;
    if (!(G_PROJECTILE_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ACTOR->unkEE = (s16)((G_PROJECTILE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ACTOR->unkB8 = G_PROJECTILE_ACTOR->unk124->unk4;
        G_PROJECTILE_ACTOR->unkC0 = G_PROJECTILE_ACTOR->unk124->unk8;
        G_PROJECTILE_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 50.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectCreateAtActorBone(&D_80720020, G_PROJECTILE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        *spawnFrame = gGameFrameCounter;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 10, 10, 1, 0x96, 0x78, 0, 1.0f);
    unkFC = G_PROJECTILE_ACTOR->hasArcBounds;
    if (unkFC != 0 || (G_PROJECTILE_ACTOR->unk6A & 1) || gActorGlobalState.unk15 != 0 || gActorGlobalState.unk200 == 9) {
        other = G_PROJECTILE_ACTOR->unk11C;
        if (other == NULL || other->actorType != 0x2E || (other->actorType == 0x2E && (unkFC != 0 || (G_PROJECTILE_ACTOR->unk6A & 1)))) {
            effectSetDepth(0);
            effectSetDuration(1);
            effectSetCallback(effectLifetimeCountdownUpdate);
            effectSetSpeed(0xC);
            effectCreateAtPosition(&D_807202D0, 0.75f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x61, 0xFF, 0x7F, 0x1E, 0, 0.0f, 0);
        actorDespawn(gCurrentActor);
    }
    if ((u32)(*spawnFrame + D_80750344) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

extern u8 D_807200A0;
extern u8 D_8071FB34;
extern s16 D_80750350;
extern s16 D_80750364;

void projectileHomingUpdate(void) {
    ProjectileActorExtra *extra;
    s16 collisionMask;
    u8 flag;
    s32 lifetime;
    s32 i;

    extra = (ProjectileActorExtra *)G_PROJECTILE_ACTOR->unk174;
    if (!(G_PROJECTILE_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ACTOR->unkEE = (s16)((G_PROJECTILE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ACTOR->unkB8 = G_PROJECTILE_ACTOR->unk124->unk4;
        G_PROJECTILE_ACTOR->unkC0 = G_PROJECTILE_ACTOR->unk124->unk8;
        G_PROJECTILE_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 50.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&D_807200A0, G_PROJECTILE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        extra->unk14 = G_PROJECTILE_ACTOR->unk124->unkC;
        extra->unk0 = gGameFrameCounter;
        G_PROJECTILE_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ACTOR->unk16F = 0x3C;
        extra->unk13 = (u8)(u32)G_PROJECTILE_ACTOR->unk124->unk10;
        extra->unk1C = 0;
    }
    lifetime = D_80750350;
    if (extra->unk13 & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &D_807200A0, 0);
    }
    if (extra->unk13 & 4) {
        lifetime = D_80750364;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (gCurrentMap == 0xCC) {
        G_PROJECTILE_ACTOR->unkFA = 0x2328;
        flag = (u8)(G_PROJECTILE_ACTOR->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, G_PROJECTILE_ACTOR->unkEE) == 0);
    } else {
        flag = G_PROJECTILE_ACTOR->unkFD;
    }
    if (flag ||
        actorGetFloorSnapped() != 0 ||
        ((G_PROJECTILE_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) ||
        D_807FBB85 != 0 ||
        (G_PROJECTILE_ACTOR->unk124->unk14 != 0.0f && (u32)(extra->unk0 + 1) < gGameFrameCounter)) {
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
    if ((u32)(extra->unk0 + lifetime) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

void projectileMultiplayerUpdate(void) {
    ProjectileActorExtra *extra;
    s32 collisionMask;
    s32 lifetime;
    s32 i;
    extra = (ProjectileActorExtra *)G_PROJECTILE_ACTOR->unk174;
    if (!(G_PROJECTILE_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ACTOR->unkEE = (s16)((G_PROJECTILE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ACTOR->unkB8 = G_PROJECTILE_ACTOR->unk124->unk4;
        G_PROJECTILE_ACTOR->unkC0 = G_PROJECTILE_ACTOR->unk124->unk8;
        G_PROJECTILE_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&D_8072029C, G_PROJECTILE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        extra->unk14 = G_PROJECTILE_ACTOR->unk124->unkC;
        extra->unk0 = gGameFrameCounter;
        G_PROJECTILE_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ACTOR->unk16F = 0x3C;
        extra->unk13 = (u8)(u32)G_PROJECTILE_ACTOR->unk124->unk10;
        extra->unk1C = 0;
    }
    lifetime = D_8075035C;
    if (extra->unk13 & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &D_8072029C, 0);
    }
    if (extra->unk13 & 4) {
        lifetime = D_80750370;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (G_PROJECTILE_ACTOR->unkFD != 0 ||
        actorGetFloorSnapped() != 0 ||
        ((G_PROJECTILE_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) ||
        D_807FBB85 != 0 ||
        (G_PROJECTILE_ACTOR->unk124->unk14 != 0.0f && (u32)(extra->unk0 + 1) < gGameFrameCounter)) {
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
    if ((u32)(extra->unk0 + lifetime) < gGameFrameCounter) {
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
        camStartShakeFromPoint(((PlayerTrackActor *)gPlayerSlots[i].actor)->unk174->unk104, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
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

typedef struct ProjectileBounceExplodeState {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[0x13 - 0x05];
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 pad14[0x1C - 0x14];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 unk20;
} ProjectileBounceExplodeState;

typedef struct ProjectileSpawnCfgEx {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} ProjectileSpawnCfgEx;

typedef struct ProjectileBounceExplodeActor {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u32 unk64;
    /* 0x68 */ u16 unk68;
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u16 unk6C;
    /* 0x6E */ u8 pad6E[0x7C - 0x6E];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0xB8 - 0x88];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0xEE - 0xC4];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[4];
    /* 0xF4 */ s16 arcYawMin;
    /* 0xF6 */ s16 arcYawMax;
    /* 0xF8 */ u8 padF8[2];
    /* 0xFA */ s16 unkFA;
    /* 0xFC */ u8 hasArcBounds;
    /* 0xFD */ u8 unkFD;
    /* 0xFE */ u8 padFE[0x124 - 0xFE];
    /* 0x124 */ ProjectileSpawnCfgEx *unk124;
    /* 0x128 */ u8 pad128[0x144 - 0x128];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0x154 - 0x145];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x16E - 0x155];
    /* 0x16E */ u8 unk16E;
    /* 0x16F */ u8 unk16F;
    /* 0x170 */ u8 pad170[4];
    /* 0x174 */ ProjectileBounceExplodeState *unk174;
} ProjectileBounceExplodeActor;

#define BOUNCE_EXPLODE_ACTOR ((ProjectileBounceExplodeActor *)gCurrentActor)

extern u8 D_80720268;
extern s16 D_80750348;
extern s16 D_8075034C;
extern s8 D_80029FA0;

void projectileBounceExplodeScaledUpdate(void) {
    ProjectileBounceExplodeState *state;
    s16 yaw;
    u8 outOfArc;
    f32 scale;
    s32 i;
    f32 radius;
    s32 value;

    state = BOUNCE_EXPLODE_ACTOR->unk174;
    outOfArc = 0;
    scale = BOUNCE_EXPLODE_ACTOR->unk124->unkC * 2.5f;
    if (!(BOUNCE_EXPLODE_ACTOR->unk60 & 0x10)) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF4, 0xFF, 0x7F, 5);
        BOUNCE_EXPLODE_ACTOR->unk6A &= 0xFFFE;
        BOUNCE_EXPLODE_ACTOR->unkEE = (s16)((BOUNCE_EXPLODE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        BOUNCE_EXPLODE_ACTOR->unkB8 = (f32)(((f64)(BOUNCE_EXPLODE_ACTOR->unk124->unk4 / (f32)4)) * 2.6);
        BOUNCE_EXPLODE_ACTOR->unkB8 *= scale;
        BOUNCE_EXPLODE_ACTOR->unkC0 = BOUNCE_EXPLODE_ACTOR->unk124->unk8;
        BOUNCE_EXPLODE_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, scale * 60.0);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, scale * 50.0, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        state->unk13 = (u8)(u32)BOUNCE_EXPLODE_ACTOR->unk124->unk10;
        effectSetDuration(-1);
        effectSetDepth(1);
        state->unk0 = gGameFrameCounter;
        if (state->unk13 >= 0xCA) {
            effectSetSpeed(0xA);
            effectSetCallback(effectLightPulseOscillate);
        }
        if (state->unk13 >= 0xCB) {
            BOUNCE_EXPLODE_ACTOR->unkC0 = 250.0f * scale;
            state->unk0 -= D_80750348 - D_8075034C;
        } else {
            BOUNCE_EXPLODE_ACTOR->unkC0 = 200.0f * scale;
        }
        effectCreateAtActorBone(&D_80720268, BOUNCE_EXPLODE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        state->unk4 = 0;
        BOUNCE_EXPLODE_ACTOR->unk60 |= 0x01080000;
        BOUNCE_EXPLODE_ACTOR->unkFA = 0x2328;
        value = (u32)(60.0f * scale);
        BOUNCE_EXPLODE_ACTOR->unk16E = value;
        BOUNCE_EXPLODE_ACTOR->unk16F = value;
        state->unk1C = 0;
        state->unk20 = 0;
    }
    if ((u32)(state->unk0 + 5) < gGameFrameCounter) {
        BOUNCE_EXPLODE_ACTOR->unk60 &= ~0x00080000;
    }
    value = 2;
    if (gPlayerCount >= 2) {
        value = 3;
    }
    projectileSteerTowardTarget(value, gCurrentActor, NULL, 1);
    actorUpdatePrevContactFlags(gCurrentActor);
    if (BOUNCE_EXPLODE_ACTOR->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, BOUNCE_EXPLODE_ACTOR->unkEE) == 0) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        value = mathAngleArcMidpoint(BOUNCE_EXPLODE_ACTOR->arcYawMin, BOUNCE_EXPLODE_ACTOR->arcYawMax);
        yaw = BOUNCE_EXPLODE_ACTOR->unkEE;
        yaw = (yaw + 0x800) & 0xFFF;
        value += (s16)(value - yaw);
        BOUNCE_EXPLODE_ACTOR->unkEE = value;
        if (BOUNCE_EXPLODE_ACTOR->unkEE < 0) {
            BOUNCE_EXPLODE_ACTOR->unkEE += 0xFFF;
        }
        if (BOUNCE_EXPLODE_ACTOR->unkEE >= 0x1000) {
            BOUNCE_EXPLODE_ACTOR->unkEE -= 0xFFF;
        }
        if (actorAngleInArc(gCurrentActor, BOUNCE_EXPLODE_ACTOR->unkEE) == 0) {
            outOfArc = 1;
        }
    }
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    BOUNCE_EXPLODE_ACTOR->unkC0 += D_807502E4 * scale;
    if (BOUNCE_EXPLODE_ACTOR->unkC0 < (f32)D_807502D0) {
        BOUNCE_EXPLODE_ACTOR->unkC0 = (f32)D_807502D0;
    }
    if ((BOUNCE_EXPLODE_ACTOR->unk6A & 1) && !(BOUNCE_EXPLODE_ACTOR->unk6C & 1)) {
        switch (state->unk4) {
        case 0:
            BOUNCE_EXPLODE_ACTOR->unkC0 = 200.0f * scale;
            break;
        case 1:
            radius = 100.0f * scale;
            BOUNCE_EXPLODE_ACTOR->unkC0 = 150.0f * scale;
            actorSetCollisionRadius(gCurrentActor, radius);
            actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, radius, -1);
            break;
        case 2:
            radius = 150.0f * scale;
            BOUNCE_EXPLODE_ACTOR->unkC0 = 100.0f * scale;
            actorSetCollisionRadius(gCurrentActor, radius);
            actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, radius, -1);
            break;
        case 3:
            BOUNCE_EXPLODE_ACTOR->unkC0 = 80.0f * scale;
            break;
        }
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        state->unk4++;
        BOUNCE_EXPLODE_ACTOR->unkB8 = ((f64)BOUNCE_EXPLODE_ACTOR->unkB8 / 3.0) * 2.5;
    }
    if ((BOUNCE_EXPLODE_ACTOR->unk6A & 1) && (BOUNCE_EXPLODE_ACTOR->unk6C & 1)) {
        state->unk20++;
    } else {
        state->unk20 = 0;
    }
    if (state->unk20 == 4) {
        gActorGlobalState.unk15 = 1;
    }
    if (BOUNCE_EXPLODE_ACTOR->unk124->unk14 != 0.0f && (u32)(state->unk0 + 1) < gGameFrameCounter) {
        gActorGlobalState.unk15 = 1;
    }
    if ((BOUNCE_EXPLODE_ACTOR->unk64 & 0x100) || outOfArc != 0) {
        gActorGlobalState.unk15 = 1;
    }
    if ((((BOUNCE_EXPLODE_ACTOR->unk6A & 1) && state->unk4 == 4) || gActorGlobalState.unk15 != 0) && BOUNCE_EXPLODE_ACTOR->unk154 == 0) {
        radius = 250.0f * scale;
        if (state->unk13 != 0xCA) {
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
                camStartShakeFromPoint(((PlayerTrackActor *)gPlayerSlots[i].actor)->unk174->unk104, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
                i++;
            } while (i < gPlayerCount);
        }
        actorSetCollisionRadius(gCurrentActor, radius);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, radius, -1);
        BOUNCE_EXPLODE_ACTOR->unk154 = 1;
    } else if (BOUNCE_EXPLODE_ACTOR->unk154 != 0) {
        if (BOUNCE_EXPLODE_ACTOR->unk154++ == 2) {
            if (state->unk13 != 0xCA) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF6, 0xFF, 0x7F, 0x1E);
            }
            actorDespawn(gCurrentActor);
            D_80029FA0--;
        }
    }
    if ((u32)(state->unk0 + D_80750348) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
        D_80029FA0--;
    }
}


#include "actor.h"

typedef struct ProjectileBeamConfig124 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} ProjectileBeamConfig124;

typedef struct ProjectileBeamActorExtra {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[0x13 - 0x05];
    /* 0x13 */ u8 unk13;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ s32 unk1C;
} ProjectileBeamActorExtra;

typedef struct ProjectileBeamActor {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u32 unk64;
    /* 0x68 */ u16 unk68;
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u16 unk6C;
    /* 0x6E */ u8 pad6E[0x7C - 0x6E];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0xB8 - 0x88];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0xEE - 0xC4];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[4];
    /* 0xF4 */ s16 arcYawMin;
    /* 0xF6 */ s16 arcYawMax;
    /* 0xF8 */ u8 padF8[2];
    /* 0xFA */ s16 unkFA;
    /* 0xFC */ u8 hasArcBounds;
    /* 0xFD */ u8 unkFD;
    /* 0xFE */ u8 padFE[0x124 - 0xFE];
    /* 0x124 */ ProjectileBeamConfig124 *unk124;
    /* 0x128 */ u8 pad128[0x144 - 0x128];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0x154 - 0x145];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x16E - 0x155];
    /* 0x16E */ u8 unk16E;
    /* 0x16F */ u8 unk16F;
    /* 0x170 */ u8 pad170[4];
    /* 0x174 */ void *unk174;
} ProjectileBeamActor;

#define G_PROJECTILE_BEAM_ACTOR ((ProjectileBeamActor *)gCurrentActor)

extern s16 D_80750358;
extern s16 D_8075036C;

extern u8 D_807201A0;

extern u8 D_80720268;

void projectileBounceExplodeGreenUpdate(void) {
    ProjectileBeamActorExtra *state;
    s32 pad48;
    u8 outOfArc;
    s32 pad40;
    s16 midYaw;
    f32 minSpeed;

    state = (ProjectileBeamActorExtra *)G_PROJECTILE_BEAM_ACTOR->unk174;
    outOfArc = 0;
    if (!(G_PROJECTILE_BEAM_ACTOR->unk60 & 0x10)) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF4, 0xFF, 0x7F, 5);
        G_PROJECTILE_BEAM_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_BEAM_ACTOR->unkEE = (s16)((G_PROJECTILE_BEAM_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_BEAM_ACTOR->unkB8 = (f32)((f64)(G_PROJECTILE_BEAM_ACTOR->unk124->unk4 / (f32)4) * 2.6);
        G_PROJECTILE_BEAM_ACTOR->unkC0 = G_PROJECTILE_BEAM_ACTOR->unk124->unk8;
        G_PROJECTILE_BEAM_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetColor(0, 0xFF, 0, 0xFF);
        effectCreateAtActorBone(&D_80720268, G_PROJECTILE_BEAM_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        state->unk0 = gGameFrameCounter;
        state->unk4 = 0;
        G_PROJECTILE_BEAM_ACTOR->unk60 |= 0x80000;
        G_PROJECTILE_BEAM_ACTOR->unkFA = 0x2328;
        state->unk13 = (u8)(u32)G_PROJECTILE_BEAM_ACTOR->unk124->unk10;
        if (state->unk13 == 0x63) {
            state->unk4 = 2;
        }
        state->unk1C = 0;
    }
    if ((u32)(state->unk0 + 10) < gGameFrameCounter) {
        G_PROJECTILE_BEAM_ACTOR->unk60 &= 0xFFF7FFFF;
    }
    projectileSteerTowardTarget(1, gCurrentActor, 0, 1);
    actorUpdatePrevContactFlags(gCurrentActor);
    if (G_PROJECTILE_BEAM_ACTOR->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, G_PROJECTILE_BEAM_ACTOR->unkEE) == 0) {
        s16 angle;
        s16 diff;
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        midYaw = mathAngleArcMidpoint(G_PROJECTILE_BEAM_ACTOR->arcYawMin, G_PROJECTILE_BEAM_ACTOR->arcYawMax);
        angle = G_PROJECTILE_BEAM_ACTOR->unkEE;
        angle = (angle + 0x800) & 0xFFF;
        diff = midYaw - angle;
        G_PROJECTILE_BEAM_ACTOR->unkEE = midYaw + diff;
        if (G_PROJECTILE_BEAM_ACTOR->unkEE < 0) {
            G_PROJECTILE_BEAM_ACTOR->unkEE += 0xFFF;
        }
        if (G_PROJECTILE_BEAM_ACTOR->unkEE >= 0x1000) {
            G_PROJECTILE_BEAM_ACTOR->unkEE -= 0xFFF;
        }
        if (actorAngleInArc(gCurrentActor, G_PROJECTILE_BEAM_ACTOR->unkEE) == 0) {
            outOfArc = 1;
        }
    }
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 10, 10, 1, 0x4B, 0x78, 0, 1.0f);
    G_PROJECTILE_BEAM_ACTOR->unkC0 += D_807502E4;
    minSpeed = (f32)D_807502D0;
    if (G_PROJECTILE_BEAM_ACTOR->unkC0 < minSpeed) {
        G_PROJECTILE_BEAM_ACTOR->unkC0 = minSpeed;
    }
    if ((G_PROJECTILE_BEAM_ACTOR->unk6A & 1) && !(G_PROJECTILE_BEAM_ACTOR->unk6C & 1)) {
        switch (state->unk4) {
            case 0:
                G_PROJECTILE_BEAM_ACTOR->unkC0 = 200.0f;
                break;
            case 1:
                G_PROJECTILE_BEAM_ACTOR->unkC0 = 150.0f;
                break;
            case 2:
                G_PROJECTILE_BEAM_ACTOR->unkC0 = 100.0f;
                actorSetCollisionRadius(gCurrentActor, 200.0f);
                actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 180.0f, -1);
                break;
            case 3:
                G_PROJECTILE_BEAM_ACTOR->unkC0 = 80.0f;
                break;
        }
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        state->unk4++;
        G_PROJECTILE_BEAM_ACTOR->unkB8 = (f32)(((f64)G_PROJECTILE_BEAM_ACTOR->unkB8 / 3.0) * 2.5);
    }
    if ((G_PROJECTILE_BEAM_ACTOR->unk64 & 0x100) || outOfArc != 0) {
        D_807FBB85 = 1;
    }
    if (((G_PROJECTILE_BEAM_ACTOR->unk6A & 1) && state->unk4 == 4) || D_807FBB85 != 0) {
        projectileSpawnExplosion();
        actorDespawn(gCurrentActor);
    }
    if ((u32)(state->unk0 + D_80750344) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

void projectileBeamUpdate(void) {
    ProjectileBeamActorExtra *extra;
    s32 collisionMask;
    s32 lifetime;
    s32 i;
    extra = (ProjectileBeamActorExtra *)G_PROJECTILE_BEAM_ACTOR->unk174;
    if (!(G_PROJECTILE_BEAM_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_BEAM_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_BEAM_ACTOR->unkEE = (s16)((G_PROJECTILE_BEAM_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_BEAM_ACTOR->unkB8 = G_PROJECTILE_BEAM_ACTOR->unk124->unk4;
        G_PROJECTILE_BEAM_ACTOR->unkC0 = G_PROJECTILE_BEAM_ACTOR->unk124->unk8;
        G_PROJECTILE_BEAM_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&D_807201A0, G_PROJECTILE_BEAM_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        extra->unk14 = G_PROJECTILE_BEAM_ACTOR->unk124->unkC;
        extra->unk0 = gGameFrameCounter;
        G_PROJECTILE_BEAM_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_BEAM_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_BEAM_ACTOR->unk16F = 0x3C;
        extra->unk13 = (u8)(u32)G_PROJECTILE_BEAM_ACTOR->unk124->unk10;
        extra->unk1C = 0;
    }
    lifetime = D_80750358;
    if (extra->unk13 & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &D_807201A0, 0);
    }
    if (extra->unk13 & 4) {
        lifetime = D_8075036C;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (actorGetFloorSnapped() != 0 ||
        G_PROJECTILE_BEAM_ACTOR->unkFD != 0 ||
        ((G_PROJECTILE_BEAM_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) ||
        D_807FBB85 != 0 ||
        (G_PROJECTILE_BEAM_ACTOR->unk124->unk14 != 0.0f && (u32)(extra->unk0 + 1) < gGameFrameCounter)) {
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
    if ((u32)(extra->unk0 + lifetime) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}


void projectileImpactExplosionUpdate(void) {
    ProjectileActorExtra *extra;
    s32 collisionMask;
    s32 lifetime;
    u8 exploding;

    extra = (ProjectileActorExtra *)G_PROJECTILE_ACTOR->unk174;
    exploding = 0;
    if (!(G_PROJECTILE_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ACTOR->unkEE = (s16)((G_PROJECTILE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ACTOR->unkB8 = G_PROJECTILE_ACTOR->unk124->unk4;
        G_PROJECTILE_ACTOR->unkC0 = G_PROJECTILE_ACTOR->unk124->unk8;
        G_PROJECTILE_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&D_80720268, G_PROJECTILE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        extra->unk14 = G_PROJECTILE_ACTOR->unk124->unkC;
        extra->unk0 = gGameFrameCounter;
        G_PROJECTILE_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ACTOR->unk16F = 0x3C;
        extra->unk13 = (u8)(u32)G_PROJECTILE_ACTOR->unk124->unk10;
        extra->unk1C = 0;
    }
    lifetime = D_80750358;
    if (extra->unk13 & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &D_80720268, 0);
    }
    if (extra->unk13 & 4) {
        lifetime = D_8075036C;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (!gCurrentActor->state && (G_PROJECTILE_ACTOR->unkFD != 0 || (G_PROJECTILE_ACTOR->unk6A & 1) || D_807FBB85 != 0)) {
        exploding = 1;
    } else if (gCurrentActor->state) {
        if (gCurrentActor->state++ == 2) {
            actorDespawn(gCurrentActor);
        }
    }
    if (gPlayerCount >= 2) {
        lifetime = (s32)((f32)lifetime * 1.4f);
    }
    if ((u32)(extra->unk0 + lifetime) < gGameFrameCounter) {
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



typedef struct ProjectileRotSub174 {
    u8 pad0[8];
    s32 unk8;
} ProjectileRotSub174;

typedef struct ProjectileRotActorExtra {
    u32 unk0;
    u8 pad4[4];
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 pad11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
    u8 pad18[4];
    s32 unk1C;
} ProjectileRotActorExtra;

typedef struct ProjectileRotActor {
    u8 pad0[4];
    ActorSub4 *unk4;
    u8 pad8[0x60 - 8];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[0x7C - 0x6C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xC0 - 0xBC];
    f32 unkC0;
    u8 padC4[0xE6 - 0xC4];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
    u8 padF0[0xFD - 0xF0];
    u8 unkFD;
    u8 padFE[0x124 - 0xFE];
    ProjectileConfig124 *unk124;
    u8 pad128[0x132 - 0x128];
    s16 unk132;
    u8 pad134[4];
    s32 unk138;
    u8 pad13C[0x144 - 0x13C];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 pad155[0x16E - 0x155];
    u8 unk16E;
    u8 unk16F;
    u8 pad170[4];
    void *unk174;
} ProjectileRotActor;

#define G_PROJECTILE_ROT_ACTOR ((ProjectileRotActor *)gCurrentActor)


void projectileRotatingUpdate(void) {
    ProjectileActorExtra *extra;
    s32 collisionMask;
    s32 lifetime;

    extra = (ProjectileActorExtra *)G_PROJECTILE_ACTOR->unk174;
    if (!(G_PROJECTILE_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ACTOR->unkEE = (s16)((G_PROJECTILE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ACTOR->unkB8 = G_PROJECTILE_ACTOR->unk124->unk4;
        G_PROJECTILE_ACTOR->unkC0 = G_PROJECTILE_ACTOR->unk124->unk8;
        G_PROJECTILE_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 50.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 40.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetFlags(4);
        effectCreateAtActorBone(&D_807206A8, G_PROJECTILE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        extra->unk14 = G_PROJECTILE_ACTOR->unk124->unkC;
        extra->unk0 = gGameFrameCounter;
        G_PROJECTILE_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ACTOR->unk16F = 0x3C;
        extra->unk13 = (u8)(u32)G_PROJECTILE_ACTOR->unk124->unk10;
        extra->unk1C = 0;
    }
    lifetime = D_80750360;
    if (extra->unk13 & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, &D_807206A8, 0);
    }
    if (extra->unk13 & 4) {
        lifetime = D_80750374;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (G_PROJECTILE_ACTOR->unkFD != 0 ||
        actorGetFloorSnapped() != 0 ||
        ((G_PROJECTILE_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) ||
        D_807FBB85 != 0 ||
        (G_PROJECTILE_ACTOR->unk124->unk14 != 0.0f && (u32)(extra->unk0 + 1) < gGameFrameCounter)) {
        effectSetDepth(1);
        effectSetSpeed(0x1006E);
        effectSetCallback(effectLightPulseOscillate);
        effectCreateAtPosition(&D_8071FB34, 0.45f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xFF, 0xFF, 0x7F, 5);
        actorDespawn(gCurrentActor);
        if (D_80750AD0 == 0) {
            s32 var_s0;
            for (var_s0 = 0; var_s0 != 0xC; var_s0 += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + var_s0);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_807206DC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
    }
    if (gPlayerCount >= 2) {
        lifetime = (s32)((f32)lifetime * 1.4f);
    }
    if ((u32)(extra->unk0 + lifetime) < gGameFrameCounter) {
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
    ProjectileRotActorExtra *extra;
    s32 collisionMask;
    s32 lifetime;
    f32 pitchMtx[4][4];
    extra = G_PROJECTILE_ROT_ACTOR->unk174;
    if (!(G_PROJECTILE_ROT_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_ROT_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ROT_ACTOR->unkEE = (s16)((G_PROJECTILE_ROT_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ROT_ACTOR->unkE6 = (s16)G_PROJECTILE_ROT_ACTOR->unkEE;
        G_PROJECTILE_ROT_ACTOR->unkB8 = G_PROJECTILE_ROT_ACTOR->unk124->unk4;
        G_PROJECTILE_ROT_ACTOR->unkC0 = G_PROJECTILE_ROT_ACTOR->unk124->unk8;
        G_PROJECTILE_ROT_ACTOR->unk144 = 0x3C;
        extra->unk0 = gGameFrameCounter;
        G_PROJECTILE_ROT_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ROT_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ROT_ACTOR->unk16F = 0x3C;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x404, 0.0f, 1.0f);
        extra->unk8 = -(mathAtan2(G_PROJECTILE_ROT_ACTOR->unkC0, G_PROJECTILE_ROT_ACTOR->unkB8) * 57.295776f);
        extra->unk10 = 0;
        extra->unkC = (f32)((u32)(randomLcgNext() % 3600U) / 10U);
        extra->unk13 = (u8)(u32)G_PROJECTILE_ROT_ACTOR->unk124->unk10;
        extra->unk1C = 0;
    }
    lifetime = D_80750354;
    if (extra->unk13 & 2) {
        collisionMask = 2;
        if (gPlayerCount >= 2) {
            collisionMask = 3;
        }
        projectileSteerTowardTarget(collisionMask, gCurrentActor, 0, 0);
    }
    if (extra->unk13 & 4) {
        lifetime = D_80750368;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    switch (G_PROJECTILE_ROT_ACTOR->unk154) {
    case 0:
        if (G_PROJECTILE_ROT_ACTOR->unkFD != 0 || (G_PROJECTILE_ROT_ACTOR->unk124->unk14 != 0.0f && (u32)(extra->unk0 + 1) < gGameFrameCounter)) {
            scriptSetActorRampTarget(gCurrentActor, 0.5f, 0);
            controllerAnimSetStateIfChanged(gCurrentActor, 0x406, 0, 0.0f);
            G_PROJECTILE_ROT_ACTOR->unkB8 = 0.0f;
            G_PROJECTILE_ROT_ACTOR->unkC0 = 0.0f;
            G_PROJECTILE_ROT_ACTOR->unk154 = 1;
            extra->unk10 = 0x3C;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x308, 0xFF, 0x7F, 5);
            if (D_80750AD0 != 0) {
                actorDespawn(gCurrentActor);
                return;
            }
        }
        break;
    case 1:
        G_PROJECTILE_ROT_ACTOR->unk138 = 0;
        G_PROJECTILE_ROT_ACTOR->unk144 = 1;
        extra->unk0 = gGameFrameCounter;
        if (!--extra->unk10) {
            scriptSetActorRampTarget(gCurrentActor, 0.5f, 0);
            controllerAnimSetStateIfChanged(gCurrentActor, 0x405, 0, 10.0f);
            G_PROJECTILE_ROT_ACTOR->unk154++;
        }
        break;
    case 2:
        G_PROJECTILE_ROT_ACTOR->unkC0 -= 20.0f;
        if (G_PROJECTILE_ROT_ACTOR->unkC0 < -150.0f) {
            G_PROJECTILE_ROT_ACTOR->unkC0 = -150.0f;
        }
        break;
    }
    if (((G_PROJECTILE_ROT_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) || D_807FBB85 != 0) {
        actorDespawn(gCurrentActor);
    }
    if (gPlayerCount >= 2) {
        lifetime = (s32)((f32)lifetime * 1.4f);
    }
    if ((u32)(extra->unk0 + lifetime) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
    guRotateF(gCurrentActor->modelMtx, extra->unkC, 0.0f, 0.0f, 1.0f);
    guRotateF(pitchMtx, extra->unk8, 1.0f, 0.0f, 0.0f);
    guMtxCatF(gCurrentActor->modelMtx, pitchMtx, gCurrentActor->modelMtx);
    actorUpdateModelMatrix(gCurrentActor, 1);
}

extern u8 D_8072006C;

void projectileRotatingLightUpdate(f32 floorOffset, u8 variant) {
    ProjectileRotActorExtra *extra;
    ActorSub4 *sub4;
    u8 red;
    u8 green;
    u8 blue;
    f32 pad4C[4][4];
    s32 mode;

    extra = G_PROJECTILE_ROT_ACTOR->unk174;
    if (!(G_PROJECTILE_ROT_ACTOR->unk60 & 0x10)) {
        if (variant == 1) {
            sfxPlayAtPositionPooled(G_PROJECTILE_ROT_ACTOR->unk7C, G_PROJECTILE_ROT_ACTOR->unk80, G_PROJECTILE_ROT_ACTOR->unk84, 0x306, 0xFF, 0x7F, 0, 0, 0.3f, 0);
        }
        G_PROJECTILE_ROT_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ROT_ACTOR->unkEE = (s16)((G_PROJECTILE_ROT_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ROT_ACTOR->unkE6 = G_PROJECTILE_ROT_ACTOR->unkEE;
        G_PROJECTILE_ROT_ACTOR->unkB8 = G_PROJECTILE_ROT_ACTOR->unk124->unk4;
        G_PROJECTILE_ROT_ACTOR->unkC0 = G_PROJECTILE_ROT_ACTOR->unk124->unk8;
        G_PROJECTILE_ROT_ACTOR->unk132 = (u8)(u32)G_PROJECTILE_ROT_ACTOR->unk124->unk10;
        sub4 = G_PROJECTILE_ROT_ACTOR->unk4;
        sub4->scaleX = 2.0 * sub4->scaleX;
        sub4 = G_PROJECTILE_ROT_ACTOR->unk4;
        sub4->scaleY = 2.0 * sub4->scaleY;
        sub4 = G_PROJECTILE_ROT_ACTOR->unk4;
        sub4->scaleZ = 2.0 * sub4->scaleZ;
        extra->unk8 = -(mathAtan2(G_PROJECTILE_ROT_ACTOR->unkC0, G_PROJECTILE_ROT_ACTOR->unkB8) * 57.295776f);
        G_PROJECTILE_ROT_ACTOR->unk144 = 0x3C;
        extra->unk0 = gGameFrameCounter;
        extra->unk12 = 0;
        G_PROJECTILE_ROT_ACTOR->unk60 |= 0x80000;
        extra->unk10 = 0;
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
    lightAdd(G_PROJECTILE_ROT_ACTOR->unk7C, G_PROJECTILE_ROT_ACTOR->unk80, *(s32 *)&G_PROJECTILE_ROT_ACTOR->unk84, 0.0f, 0.0f, 0.0f, 80.0f, 0, red, green, blue);
    if (mode == 1) {
        if (!extra->unk12 && ((G_PROJECTILE_ROT_ACTOR->unk6A & 1) || G_PROJECTILE_ROT_ACTOR->unkFD != 0 || D_807FBB85 != 0)) {
            effectSetSpeed(0x1006E);
            effectSetCallback(effectLightPulseOscillate);
            effectCreateAtPosition(&D_8072006C, 1.2f, G_PROJECTILE_ROT_ACTOR->unk7C, G_PROJECTILE_ROT_ACTOR->unk80, G_PROJECTILE_ROT_ACTOR->unk84);
            effectSpawnBoneWhite(0, 0, 0.8f, G_PROJECTILE_ROT_ACTOR->unk7C, G_PROJECTILE_ROT_ACTOR->unk80, G_PROJECTILE_ROT_ACTOR->unk84, -0x50);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF6, 0xFF, 0x3F, 0x14);
            extra->unk12 = 2;
        } else if (extra->unk12) {
            if (--extra->unk12 == 0) {
                actorDespawn(gCurrentActor);
            }
        }
        if ((u32)(extra->unk0 + D_80750344) < gGameFrameCounter) {
            actorDespawn(gCurrentActor);
        }
    }
}

void actorApplyTransformAndRender(void) {
    ProjectileRotSub174 *state;

    state = gCurrentActor->customState;
    projectileRotatingLightUpdate(0.0f, 1);
    matrixMakeRotationX(gCurrentActor->modelMtx, state->unk8);
    actorUpdateModelMatrix(gCurrentActor, 1);
}

extern u8 D_8071FBC8;
extern u8 D_8071FC40;
extern u8 D_80720804;

typedef struct ProjectileParticleActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[2];
    s16 unk6E;
    u8 pad70[0x7C - 0x70];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFA - 0xF0];
    s16 unkFA;
    u8 hasArcBounds;
    u8 padFD[0x124 - 0xFD];
    ProjectileBeamConfig124 *unk124;
    u8 pad128[0x144 - 0x128];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    void *unk174;
} ProjectileParticleActor;

#define G_PROJECTILE_PARTICLE_ACTOR ((ProjectileParticleActor *)gCurrentActor)

void projectileParticleSpawnerTick(void) {
    ProjectileBeamActorExtra *extra;
    s32 i;
    extra = (ProjectileBeamActorExtra *)G_PROJECTILE_PARTICLE_ACTOR->unk174;
    if (!(G_PROJECTILE_PARTICLE_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_PARTICLE_ACTOR->unkFA = 0x270F;
        G_PROJECTILE_PARTICLE_ACTOR->unk6E = -2;
        G_PROJECTILE_PARTICLE_ACTOR->unk6A &= -2;
        G_PROJECTILE_PARTICLE_ACTOR->unkEE = (s16)((G_PROJECTILE_PARTICLE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_PARTICLE_ACTOR->unkB8 = G_PROJECTILE_PARTICLE_ACTOR->unk124->unk4;
        G_PROJECTILE_PARTICLE_ACTOR->unkC0 = G_PROJECTILE_PARTICLE_ACTOR->unk124->unk8;
        extra->unk13 = (u8)(u32)G_PROJECTILE_PARTICLE_ACTOR->unk124->unk10;
        G_PROJECTILE_PARTICLE_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 110.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 100.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectCreateAtActorBone(&D_80720804, G_PROJECTILE_PARTICLE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        extra->unk0 = gGameFrameCounter;
        G_PROJECTILE_PARTICLE_ACTOR->unk60 |= 0x80000;
        if (extra->unk13 != 0xA) {
            effectSetMode(2);
            effectSetDepth(1);
            effectCreateAtPosition(&D_8071FBC8, 1.5f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 14, 14, 1, 150, 120, 0, 1.0f);
    if (G_PROJECTILE_PARTICLE_ACTOR->unk6A & 4) {
        effectSetDepth(1);
        effectSetDuration(-1);
        effectSetCallback(effectProjectileDriftUpdate);
        effectSetSpeed((s32)gCurrentActor);
        effectCreateAtPosition(&D_8071FC40, 0.3f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    }
    if (((G_PROJECTILE_PARTICLE_ACTOR->hasArcBounds != 0) && ((u32)(gGameFrameCounter - extra->unk0) >= 6)) || D_807FBB85 != 0) {
        if ((D_807FBB85 != 0) && (extra->unk13 != 0xA)) {
            effectSetDepth(1);
            effectSetSpeed(0x100D2);
            effectSetCallback(effectLightPulseOscillate);
            effectCreateAtPosition(&D_80720120, 2.0f, gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z);
            camStartShakeFromPoint(((PlayerTrackActor *)gPrimaryPlayerActor)->unk174->unk104, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
            actorSpawnSparkleBurst();
            for (i = 0; i != 12; i += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + i);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_807206DC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        if (extra->unk13 != 0xA) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3C, 0xFF, 0x7F, 0x1E);
        }
        actorDespawn(gCurrentActor);
    }
    if ((u32)(extra->unk0 + D_80750344) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

extern f32 D_80750274;

typedef struct ProjectileHomingActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[2];
    s16 unk6E;
    u8 pad70[0x7C - 0x70];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFA - 0xF0];
    s16 unkFA;
    u8 hasArcBounds;
    u8 padFD[0x124 - 0xFD];
    ProjectileBeamConfig124 *unk124;
    u8 pad128[0x144 - 0x128];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    void *unk174;
} ProjectileHomingActor;

#define G_PROJECTILE_HOMING_ACTOR ((ProjectileHomingActor *)gCurrentActor)

void projectileHomingParticleUpdate(void) {
    u32 *spawnFrame;
    f32 jitterX;
    f32 jitterY;
    f32 jitterZ;
    f32 minSpeed;
    s32 i;

    spawnFrame = (u32 *)G_PROJECTILE_HOMING_ACTOR->unk174;
    if (!(G_PROJECTILE_HOMING_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_HOMING_ACTOR->unkFA = 0x270F;
        G_PROJECTILE_HOMING_ACTOR->unk6E = -2;
        G_PROJECTILE_HOMING_ACTOR->unk6A &= -2;
        G_PROJECTILE_HOMING_ACTOR->unkEE = (s16)((G_PROJECTILE_HOMING_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_HOMING_ACTOR->unkB8 = G_PROJECTILE_HOMING_ACTOR->unk124->unk4;
        G_PROJECTILE_HOMING_ACTOR->unkC0 = G_PROJECTILE_HOMING_ACTOR->unk124->unk8;
        G_PROJECTILE_HOMING_ACTOR->unk144 = 0x1C;
        actorSetCollisionRadius(gCurrentActor, 110.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 100.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectCreateAtActorBone(&D_80720804, G_PROJECTILE_HOMING_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        *spawnFrame = gGameFrameCounter;
        G_PROJECTILE_HOMING_ACTOR->unk60 |= 0x80000;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    G_PROJECTILE_HOMING_ACTOR->unkC0 += D_80750274;
    minSpeed = (f32)D_807502D0;
    if (G_PROJECTILE_HOMING_ACTOR->unkC0 < minSpeed) {
        G_PROJECTILE_HOMING_ACTOR->unkC0 = minSpeed;
    }
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 14, 14, 1, 150, 120, 0, 1.0f);
    i = 0;
    if ((G_PROJECTILE_HOMING_ACTOR->unk6A & 1) || ((G_PROJECTILE_HOMING_ACTOR->hasArcBounds != 0) && ((u32)(gGameFrameCounter - *spawnFrame) >= 6)) || D_807FBB85 != 0) {
        do {
            jitterX = ((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0;
            jitterY = ((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0;
            jitterZ = ((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0;
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
    if ((u32)(*spawnFrame + D_80750344) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

typedef struct PlayerStateTrackView {
    u8 pad0[0x88];
    Actor *unk88;
    u8 pad8C[0x104 - 0x8C];
    s32 unk104;
} PlayerStateTrackView;

typedef struct PlayerActorTrackView {
    u8 pad0[0x174];
    PlayerStateTrackView *unk174;
} PlayerActorTrackView;

typedef struct CameraShakeTargetView {
    u8 pad0[0x104];
    s32 unk104;
} CameraShakeTargetView;

typedef struct ActorBounceCountView {
    u8 pad0[0x155];
    u8 unk155;
} ActorBounceCountView;

extern f32 D_807502F8;
extern void *gActivePlayerState;

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
    PlayerStateTrackView *sub;
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
    if (gActorGlobalState.unk200 == 5) {
        sub = ((PlayerActorTrackView *)gActorGlobalState.targetActor)->unk174;
        if (sub->unk88 != NULL && (sub->unk88->actorType == 0x1D || sub->unk88->actorType == 0x50)) {
            camStartShake(sub->unk104, 0xA, 0x14);
            playerStateQueueCallback(0x34, gCurrentActor, 0);
            effectSpawnScatterRandom(&sEffectSparkConfig, 0, 1.0f, 4, 0x14, 0x96, (s32)gCurrentActor->x, (s32)gCurrentActor->y, (s32)gCurrentActor->z);
            actorDespawn(gCurrentActor);
        }
    } else {
        for (i = 0; i < gActorGlobalState.unk254; i++) {
            if (gActorGlobalState.unk258[i] == 1) {
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
                    camStartShake(((CameraShakeTargetView *)gActivePlayerState)->unk104, 0xA, 0x14);
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

typedef struct ProjectileSpawnScaleView {
    u8 pad0[0xC];
    f32 unkC;
} ProjectileSpawnScaleView;

typedef struct ProjectileChaseState {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 pad12[6];
    /* 0x18 */ s16 unk18;
} ProjectileChaseState;

typedef struct ProjectileChaseActor {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[4];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u8 pad64[0x6E - 0x64];
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ u8 pad70[0x7C - 0x70];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0xAC - 0x88];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[0xB8 - 0xB0];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
    /* 0xC8 */ u8 padC8[0xE6 - 0xC8];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[0xEE - 0xE8];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ s16 unkF0;
    /* 0xF2 */ u8 padF2[0xFD - 0xF2];
    /* 0xFD */ u8 unkFD;
    /* 0xFE */ u8 padFE[0x11C - 0xFE];
    /* 0x11C */ struct ProjectileChaseActor *unk11C;
    /* 0x120 */ u8 pad120[4];
    /* 0x124 */ struct ProjectileSpawnScaleView *unk124;
    /* 0x128 */ u8 pad128[2];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x154 - 0x12C];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x15E - 0x156];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[0x174 - 0x15F];
    /* 0x174 */ ProjectileChaseState *unk174;
} ProjectileChaseActor;

#define CHASE_ACTOR ((ProjectileChaseActor *)gCurrentActor)
#define CHASE_TARGET ((ProjectileChaseActor *)gPrimaryPlayerActor)


void projectileChaseTargetUpdate(void) {
    ProjectileChaseState *state;
    s16 targetYaw;
    s16 yawDiff;
    ProjectileChaseActor *other;

    state = CHASE_ACTOR->unk174;
    projectileRotatingLightUpdate(15.0f, 0);
    if (gCurrentMap == 0x6F) {
        if (CHASE_ACTOR->unk80 < CHASE_ACTOR->unkAC) {
            CHASE_ACTOR->unk80 = CHASE_ACTOR->unkAC;
            CHASE_ACTOR->unkC0 = CHASE_ACTOR->unkC4;
        }
    }
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 100, 100, 1, 0x4B, 0x78, 0, 1.0f);
    if (!(CHASE_ACTOR->unk60 & 0x10)) {
        state->unk18 = (s32)CHASE_ACTOR->unkB8;
        CHASE_ACTOR->unk12A = 1000;
        CHASE_ACTOR->unk60 |= 0x400;
        state->unk0 += 0x78;
        if (CHASE_ACTOR->unk6E == -1) {
            sfxPlayActorSound(gCurrentActor, 0x114, 0x1E, 1, 0, 0xFF, 1.0f, 0);
            D_80770B68[D_80770628[CHASE_ACTOR->unk6E]] = 0.75f;
            D_80770BC0[D_80770628[CHASE_ACTOR->unk6E]] = 1.0f;
        }
        state->unk10 = 0xF;
        state->unk11 = 0;
        actorSetUniformScale(gCurrentActor, (f64)CHASE_ACTOR->unk124->unkC * 0.15);
    }
    state->unk11++;
    if (state->unk10 < state->unk11) {
        sfxPlayAtPositionPooled(CHASE_ACTOR->unk7C, CHASE_ACTOR->unk80, CHASE_ACTOR->unk84, 0x15B, 0xFF, 0x6E, 0, 0x1E, 0.3f, 0);
        state->unk11 = 0;
        if (state->unk10 >= 3) {
            state->unk10--;
        }
    }
    if ((u32)(state->unk0 - 100) < gGameFrameCounter) {
        CHASE_ACTOR->unk60 &= ~0x80000;
    }
    if (((u32)(state->unk0 + D_80750344) < gGameFrameCounter) || ((CHASE_ACTOR->unkFD != 0) && (CHASE_ACTOR->unk58 != 0xA9)) || (D_807FBB85 != 0)) {
        tagBarrelSpawnActorSmokePuffs(0, 1);
        sfxStopSlotSound(gCurrentActor, 0);
        actorDespawn(gCurrentActor);
        other = CHASE_ACTOR->unk11C;
        if (other != NULL && other->unk58 == 0xB9 && other->unk154 != 0x37) {
            CHASE_ACTOR->unk11C->unk155++;
        }
    }
    targetYaw = mathAngleBetweenPoints2D(CHASE_TARGET->unk7C, CHASE_TARGET->unk84, CHASE_ACTOR->unk7C, CHASE_ACTOR->unk84);
    if (targetYaw < CHASE_ACTOR->unkE6) {
        yawDiff = CHASE_ACTOR->unkE6 - targetYaw;
    } else {
        yawDiff = targetYaw - CHASE_ACTOR->unkE6;
    }
    CHASE_ACTOR->unkE6 = mathAngleEaseToward(CHASE_ACTOR->unkE6, targetYaw, 10.0f);
    switch (CHASE_ACTOR->unk154) {
    case 0:
        if (yawDiff > 1000) {
            CHASE_ACTOR->unk154 = 1;
            CHASE_ACTOR->unk155 = 0;
        }
        /* fallthrough */
    case 2:
        if (CHASE_ACTOR->unk154 == 2) {
            if (CHASE_ACTOR->unkB8 > 100.0f) {
                CHASE_ACTOR->unk154 = 0;
            }
        }
        if (CHASE_ACTOR->unkB8 + 20.0f < state->unk18) {
            CHASE_ACTOR->unkB8 += 20.0f;
        } else {
            CHASE_ACTOR->unkB8 = state->unk18;
        }
        CHASE_ACTOR->unkEE = mathAngleEaseToward(CHASE_ACTOR->unkEE, CHASE_ACTOR->unkE6, 1.0f);
        CHASE_ACTOR->unkF0 = mathAngleEaseToward(CHASE_ACTOR->unkF0, (s16)(s32)(((f64)mathCalculatePitchAngle(CHASE_TARGET->unk7C, CHASE_TARGET->unk80 + (f32)(u32)CHASE_TARGET->unk15E, CHASE_TARGET->unk84, CHASE_ACTOR->unk7C, CHASE_ACTOR->unk80, CHASE_ACTOR->unk84, 20) * 2048.0) / 3.1415927410125732), 30.0f);
        CHASE_ACTOR->unkC0 = mathSinF(CHASE_ACTOR->unkF0) * -CHASE_ACTOR->unkB8;
        state->unk8 = -(mathAtan2(CHASE_ACTOR->unkC0, CHASE_ACTOR->unkB8) * 57.295776f);
        break;
    case 1:
        if (CHASE_ACTOR->unkB8 - 10.0f > 5.0f) {
            CHASE_ACTOR->unkB8 -= 10.0f;
        } else {
            CHASE_ACTOR->unkB8 = 5.0f;
        }
        if (CHASE_ACTOR->unkB8 <= 5.0f) {
            CHASE_ACTOR->unk154 = 2;
            CHASE_ACTOR->unk155 = 0;
        }
        break;
    }
    if (CHASE_ACTOR->unk58 == 0x59) {
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
        G_PROJECTILE_ACTOR->unkFA = 0x2328;
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

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

void actorAppendActiveCallback8(void) {
    s16 i;

    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;

        if (actor->collisionFlags & 4) {
            actorAppendCallback(actor, (s32)gCurrentActor, 8, 0, 0, NULL);
        }
    }
}
