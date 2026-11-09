#include "common.h"

#include "actor.h"
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void actorUpdateModelMatrix(Actor *, s32);

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

void actorSnapToBone(Actor **arg0) {
    f32 sp2C;
    ProjectileActorSub174 *temp_v1;

    temp_v1 = (*arg0)->customState;
    actorGetNodePos(temp_v1->unk88, 9, &(*arg0)->x, &sp2C, &(*arg0)->z);
    if ((*arg0)->y < sp2C) {
        (*arg0)->y = sp2C;
    }
    (*arg0)->yaw = temp_v1->unk88->yaw;
    actorUpdateModelMatrix(*arg0, 0);
}

void actorSyncTransformFromParent(ProjectileActorSync **arg0) {
    ProjectileActorSync *temp_a2;
    ProjectileActorSub174 *temp_v0;
    ProjectileActorSync *temp_v1;
    ProjectileActorSub174 *temp_a1;

    temp_a2 = *arg0;
    temp_v0 = temp_a2->unk174;
    temp_v1 = (ProjectileActorSync *)temp_v0->unk88;
    if (temp_v1 != NULL) {
        temp_a1 = temp_v1->unk174;
        if (temp_a1->unk34 < 5) {
            temp_a2->unk7C = temp_v1->unk7C;
            (*arg0)->unk80 = ((ProjectileActorSync *)temp_v0->unk88)->unk80;
            (*arg0)->unk84 = ((ProjectileActorSync *)temp_v0->unk88)->unk84;
            (*arg0)->unkE6 = ((ProjectileActorSync *)temp_v0->unk88)->unkE6;
            (*arg0)->unkE8 = ((ProjectileActorSync *)temp_v0->unk88)->unkE8;
            (*arg0)->unkE4 = ((ProjectileActorSync *)temp_v0->unk88)->unkE4;
            (*arg0)->unkAC = ((ProjectileActorSync *)temp_v0->unk88)->unkAC;
            temp_v1 = (ProjectileActorSync *)temp_v0->unk88;
            if (temp_v1->unk58 == 0x12E) {
                (*arg0)->unkB8 = temp_v1->unkB8 * 10.0f;
            } else {
                (*arg0)->unkB8 = temp_v1->unkB8;
            }
            temp_a2 = *arg0;
        } else {
            temp_a2 = *arg0;
            temp_a2->unkB8 = 0.0f;
            temp_a2 = *arg0;
        }
    }
    actorUpdateModelMatrix((Actor *)temp_a2, 0);
}

typedef struct TargetVec3f {
    f32 x, y, z;
} TargetVec3f;
void camClosestPointOnSegment(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);
s32 mathPickCloserTargetPoint3D(f32 arg0, f32 arg1, f32 arg2, TargetVec3f *arg3, TargetVec3f *arg4, TargetVec3f *arg5, TargetVec3f *arg6, f32 *arg7, f32 *arg8, f32 *arg9) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    camClosestPointOnSegment(arg0, arg1, arg2, arg3->x, arg3->y, arg3->z, arg4->x, arg4->y, arg4->z, &sp48, &sp4C, &sp50);
    camClosestPointOnSegment(arg0, arg1, arg2, arg5->x, arg5->y, arg5->z, arg6->x, arg6->y, arg6->z, &sp54, &sp58, &sp5C);
    if (((arg0 - sp48) * (arg0 - sp48) + (arg1 - sp4C) * (arg1 - sp4C) + (arg2 - sp50) * (arg2 - sp50)) <
        ((arg2 - sp5C) * (arg2 - sp5C) + ((arg0 - sp54) * (arg0 - sp54) + (arg1 - sp58) * (arg1 - sp58)))) {
        *arg7 = sp48;
        *arg8 = sp4C;
        *arg9 = sp50;
        return 0;
    }
    *arg7 = sp54;
    *arg8 = sp58;
    *arg9 = sp5C;
    return 1;
}

typedef struct PlayerCameraXZView {
    u8 pad0[0x210];
    f32 unk210;
    u8 pad214[4];
    f32 unk218;
} PlayerCameraXZView;
f32 mathAtan2(f32, f32);
void effectSetColor(s32, s32, s32, s32);
s32 effectCreateAtActorBone(void *, f32, Actor *, s32, s32);
struct PlayerTrackEntry;
extern struct PlayerTrackEntry *gPlayerSlots;
extern Actor *gCurrentActor;
extern u8 D_80720054;

void actorSpawnNodeEffectFacingCamera(s32 arg0, u8 arg1) {
    f32 tgt;
    f32 cur;
    s16 diff;
    f32 sp48;
    f32 sp44;
    f32 sp40;

    actorGetNodePos(gCurrentActor, arg0, &sp48, &sp44, &sp40);
    tgt = sp48 - ((PlayerCameraXZView *)gPlayerSlots)->unk210;
    tgt = (s16)(mathAtan2(((PlayerCameraXZView *)gPlayerSlots)->unk218 - sp40, tgt) * 651.8986f + 1024.0f) & 0xFFF;
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
        af = (u32)arg1;
        alpha = (u32)(scale * af) & 0xFF;
        if (alpha != 0) {
            vol = 3.3f;
            if (gCurrentActor->sub4 != NULL) {
                vol *= gCurrentActor->sub4->scaleY;
            }
            effectSetColor(0xFF, 0xFF, 0xFF, alpha);
            effectCreateAtActorBone(&D_80720054, vol, gCurrentActor, arg0, 2);
        }
    }
}

extern Actor *gCurrentActor;

f32 mathAtan2(f32, f32);

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
void sfxStopChannel(s32, s32);
void slotQueueCancel(s32, s32);
void playerKongStopSoundByState(void *);
void effectSpawnActorBone(void *, s32, f32);
s32 mathNudgeCoords(f32, f32, f32 *, f32 *);
void matrixMakeRotationY(f32 (*)[4], f32);
void matrixMakeRotationX(void *, s32);
s32 camIsCutsceneActive(void);
void lightAdd(f32, f32, s32, f32, f32, f32, f32, s32, s32, s32, s32);
void actorDespawn(Actor *);
void sfxStopSlotSound(Actor *, s32);
void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void *heapAlloc(s32);

#define PICK_MAX(a, b) ((a) < (b) ? (b) : (a))
#define PICK_MIN(a, b) ((a) < (b) ? (a) : (b))

void func_8068EF54(void) {
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 spD4[4][4];
    f32 sp94[4][4];
    f32 sp90;
    f64 ratio;
    f32 var;
    f32 glow;
    OwnerLinkState *sp7C;
    OwnerPlayerState *sp78;
    Actor *sp74;
    OwnerModelInfo *model;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    ActorSub4Buf *buf;

    sp7C = gCurrentActor->customState;
    sp74 = sp7C->unk0;
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
        if (sp74->actorType == 0xC5) {
            gCurrentActor->tintR = 0xFF;
            gCurrentActor->tintG = 0xFF;
            gCurrentActor->tintB = 0xFF;
            gCurrentActor->flags |= 0x800000;
        }
        sp7C->unk8 = 0;
    }
    buf = ((ActorSub4BufView *)gCurrentActor->sub4)->unk1C;
    switch (sp74->collisionFlags) {
    case 1:
        sp78 = sp74->customState;
        buf->unk2 = sp78->unk1A0;
        if ((sp74->contactFlags & 5) || sp78->unk240 == 1 || (sp74->state == 0x42 && sp78->unkBC != 0x31) || sp74->state == 0x87) {
            actorAppendCallback(sp7C->unk4, (s32)gCurrentActor, 0x2000000, 0, 0, 0);
            sp78->unk1A3 = 0;
            actorDespawn(gCurrentActor);
            sfxStopChannel(0x48, 0);
            sfxStopSlotSound(gActivePlayerActor, 0);
            slotQueueCancel(5, 0);
            sp78->unk240 = 0;
            if (!(sp78->unk1F4 & 4)) {
                playerKongStopSoundByState(sp74);
            }
        }
        if (sp78->unk1A2 != 0 || (camIsCutsceneActive() && gFrameCounter % 5 == 0)) {
            ratio = (0, sp74->speedY > 0.0 ? sp74->speedY : 0.0);  // FAKE: comma steers FP candidate order
            if (gFrameCounter & 1) {
                effectSpawnActorBone(sp74, 1, (f32)(ratio / 150.0 * 0.12) + 0.3);
            } else {
                effectSpawnActorBone(sp74, 2, (f32)(ratio / 150.0 * 0.12) + 0.3);
            }
            sp78->unk1A2 = 0;
            sp7C->unk8 = gFrameCounter;
        }
        if (gCurrentMap == 0x5C) {
            if (gFrameCounter && gFrameCounter) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            glow = (30.0 - (f64)(s32)(gFrameCounter - sp7C->unk8)) / 30.0 * 100.0;
            if (glow > 0.0) {
                lightAdd(gCurrentActor->x, gCurrentActor->y, *(s32 *)&gCurrentActor->z, 0.0f, 0.0f, 0.0f, glow, 0, 0xFF, 0xC8, 0xC8);
            }
        }
        break;
    case 0x40:
        model = *(OwnerModelInfo **)sp74->sub4;
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
        if (!(sp74->flags & 4) || sp74->state == 0x3C) {
            actorDespawn(gCurrentActor);
        } else if (var > 0.05) {
            if (gFrameCounter & 1) {
                effectSpawnActorBone(sp74, 1, var);
            } else {
                effectSpawnActorBone(sp74, 2, var);
            }
        }
        break;
    }
    actorGetNodePos(sp74, 1, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
    actorGetNodePos(sp74, 0xB, &sp11C, &sp118, &sp114);
    mathNudgeCoords(gCurrentActor->x, gCurrentActor->z, &sp11C, &sp114);
    sp90 = mathAtan2(sp11C - gCurrentActor->x, sp114 - gCurrentActor->z);
    if (sp74->collisionFlags == 0x40) {
        actorGetNodePos(sp74, 0xC, &sp6C, &sp68, &sp64);
        sp74->moveYaw = mathAngleBetweenPoints2D(sp6C, sp64, gCurrentActor->x, gCurrentActor->z);
        matrixMakeRotationY(spD4, (sp74->moveYaw * 360) / 4096);
    } else {
        matrixMakeRotationY(spD4, (sp74->yaw * 360) / 4096);
    }
    matrixMakeRotationX(sp94, 0xC2B40000);
    guMtxCatF(spD4, sp94, spD4);
    guAlignF(sp94, sp90 * 57.295776f + 180.0f, sp11C - gCurrentActor->x, sp118 - gCurrentActor->y, sp114 - gCurrentActor->z);
    guMtxCatF(spD4, sp94, (f32(*)[4])((u8 *)gCurrentActor + 0xC));
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

typedef struct PlayerActorRef {
    u8 pad0[4];
    Actor *actor;
    u8 pad8[0x2F0 - 8];
} PlayerActorRef;

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
extern struct PlayerTrackEntry *gPlayerSlots;
f32 mathCosF(s16);
f32 mathSinF(s16);
s32 mathAngleSignedDistance(s16, s16);
s16 mathAngleEaseToward(s16, s16, f32);
void actorStepPhysics(Actor *, s16, s16);
void actorApplyVelocity(Actor *);
void actorUpdateFloorContactAndTilt(Actor *, f32);
void func_8002F490(void *);


#define S ((ActorMoveState *)arg0)
void func_8068F72C(arg0, arg1, arg2, arg3)
void *arg0;
s32 arg1;
u8 arg2;
u8 arg3;
{
    f32 fa0;
    s32 sp58;
    f32 sp54;
    f32 sp50;
    f32 fv0;
    s16 sp4A;
    s16 sp48;
    u8 fl[4];
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s16 temp_v0;
    s16 sp34;
    ActorMoveView *pl;

    pl = (ActorMoveView *)((PlayerActorRef *)gPlayerSlots)[S->unk28].actor;
    sp58 = pl->unk58;
    sp4A = 0;
    sp48 = 0;
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
    sp40 = mathSinF(ACTOR_MOVE_VIEW->unkEE) * ACTOR_MOVE_VIEW->unkB8;
    sp3C = mathCosF(ACTOR_MOVE_VIEW->unkEE) * ACTOR_MOVE_VIEW->unkB8;
    if (fl[3] != 0) {
        sp38 = S->unk4 * 50.0f;
        if (sp58 == 2) {
            fa0 = 5000.0f;
        } else {
            fa0 = 10000.0f;
        }
        sp54 = 1.0f / fa0 * (ACTOR_MOVE_VIEW->unkB8 * ACTOR_MOVE_VIEW->unkB8) + S->unk8;
        if (S->unk4 != 0.0f) {
            sp54 = sp54 + 30.0f;
        } else {
            sp54 = sp54 + 3.0f;
        }
    } else {
        fv0 = 2.0f;
        if (fl[2] != 0) {
            sp38 = S->unk4 * 4.0f;
            sp54 = S->unk8 + ACTOR_MOVE_VIEW->unkB8 * ACTOR_MOVE_VIEW->unkB8 * 0.00002f + fv0;
        } else {
            sp38 = S->unk4 * fv0;
            sp54 = S->unk8 + ACTOR_MOVE_VIEW->unkB8 * ACTOR_MOVE_VIEW->unkB8 * 0.00002f + fv0;
        }
    }
    sp40 += mathSinF(S->unk0) * sp38;
    sp3C += mathCosF(S->unk0) * sp38;
    ACTOR_MOVE_VIEW->unkB8 = sqrtf(sp40 * sp40 + sp3C * sp3C);
    ACTOR_MOVE_VIEW->unkEE = (s16)(s32)(mathAtan2(sp40, sp3C) * 4096.0 / 6.2831854820251465);
    if (fl[2] != 0) {
        sp34 = 0x400 - ACTOR_MOVE_VIEW->unkDE;
        temp_v0 = mathAngleSignedDistance(ACTOR_MOVE_VIEW->unkDC, S->unk0);
        fv0 = (f32)sp34;
        sp4A = (s16)(s32)(mathCosF(temp_v0) * fv0);
        sp48 = (s16)(s32)(mathSinF(temp_v0) * fv0);
    } else if (!arg3) {
        ACTOR_MOVE_VIEW->unkE8 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE8, 0, 4.0f);
        ACTOR_MOVE_VIEW->unkE4 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE4, 0, 5.0f);
    }
    sp50 = S->unk10 * S->unkC;
    if (arg3) {
        sp48 = (s32)((f32)sp48 + sp50 * 200.0f);
        sp48 &= 0xFFF;
        if (fl[3] != 0 || fl[2] != 0) {
            sp4A = (s32)((f64)sp4A + ((f64)(S->unk4 * -50.0f) + (f64)ACTOR_MOVE_VIEW->unkB8 * -0.5));
            sp4A &= 0xFFF;
        } else {
            sp4A = ACTOR_MOVE_VIEW->unkE8;
        }
        ACTOR_MOVE_VIEW->unkE8 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE8, sp4A, 4.0f);
        ACTOR_MOVE_VIEW->unkE4 = mathAngleEaseToward(ACTOR_MOVE_VIEW->unkE4, sp48, 5.0f);
    }
    ACTOR_MOVE_VIEW->unkB8 = ACTOR_MOVE_VIEW->unkB8 - sp54;
    sp40 = ACTOR_MOVE_VIEW->unkB8;
    if (sp40 < 0.0f) {
        ACTOR_MOVE_VIEW->unkB8 = 0.0f;
        sp40 = ACTOR_MOVE_VIEW->unkB8;
    }
    fv0 = sp40 - ACTOR_MOVE_VIEW->unkBC;
    if (fv0 < 0.0f) {
        fv0 = 0.0f;
    }
    if (sp58 == 2) {
        sp48 = -0x1E;
    } else {
        if (sp48 && sp48) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        sp48 = -0x28;
    }
    S->unk0 = (s32)((f64)S->unk0 + (f64)(sp50 * (f32)sp48) * (1.0 + (f64)fv0 * 0.05));
    S->unk0 = S->unk0 & 0xFFF;
    if (arg2) {
        fa0 = ACTOR_MOVE_VIEW->unk80;
        sp54 = ACTOR_MOVE_VIEW->unkAC;
        if (fa0 < sp54) {
            if (fl[3] != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            ACTOR_MOVE_VIEW->unkC0 = ACTOR_MOVE_VIEW->unkC0 + ((sp54 - fa0) * 3.0f + 15.0f);
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
            if (sp58 == 2) {
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
    if (sp58 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    actorStepPhysics(gCurrentActor, ACTOR_MOVE_VIEW->unkE6, S->unk0);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (!arg2) {
        if (ACTOR_MOVE_VIEW->unk80 < ACTOR_MOVE_VIEW->unkAC) {
            ACTOR_MOVE_VIEW->unk80 = ACTOR_MOVE_VIEW->unkAC;
            ACTOR_MOVE_VIEW->unkC0 = ACTOR_MOVE_VIEW->unkC4;
            if (S->unk4 && S->unk4) {}  // FAKE: dead test steers the FP colouring of the unkAC load in the !arg2 block
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



void actorInterpolateAngles(u8 arg0, ProjectileAngleTarget *arg1, ProjectileAngleStep *arg2) {
    f32 var_fv0;
    f32 var_fv1;
    ProjectileAngleSub1C *temp_v1;

    temp_v1 = ((ProjectileActorSub4 *)gCurrentActor->sub4)->unk1C;
    if (arg0) {
        var_fv0 = 500.0f;
        var_fv1 = 0.0f;
    } else {
        var_fv0 = 0.0f;
        var_fv1 = (f32)((f64)arg1->unkC * (400.0 - (0.7 * (f64)gCurrentActor->speedXZ)));
    }
    arg2->unk2 = mathAngleEaseToward(arg2->unk2, (s16)(s32)var_fv0, 5.0f);
    arg2->unk0 = mathAngleEaseToward(arg2->unk0, (s16)((s32)var_fv1 & 0xFFF), 3.0f);
    temp_v1->unk0 = -0x80;
    temp_v1->unk1 = 1;
    temp_v1->unk2 = (u16)arg2->unk2 * 16;
    temp_v1->unk4 = (u16)arg2->unk0 * 16;
    temp_v1->unk6 = 0;
    temp_v1->unk8 = 0;
}

void heapClearBlock(void *);

void actorAllocSubBuffer(Actor *arg0, s32 arg1) {
    ((ProjectileActorBase *)arg0)->unk4->unk1C = heapAlloc(arg1 * 8);
    heapClearBlock(((ProjectileActorBase *)arg0)->unk4->unk1C);
}

void playerStateQueueCallback(s32, Actor *, u8);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void animSetSpeed(Actor *, s32, f32);
void animSetLoopLimit(Actor *, s32, s32);
void actorCopyPoseAndScale(Actor *, Actor *, f32);

void actorInitAnimations(Actor *arg0, Actor *arg1) {
    u8 sp37[4];
    ProjectileActorSub174 *temp_v0;

    sp37[3] = 0;
    temp_v0 = arg1->customState;
    playerStateQueueCallback(0x4C, arg0, temp_v0->unk1A4);
    if (gCurrentMap == 0x6F) {
        sp37[3] = 0x3C;
    }
    sfxPlayActorSound(arg0, 0x115, sp37[3], 1, 0, 0xFF, 1.0f, 0);
    sfxPlayActorSound(arg0, 0x116, sp37[3], 1, 1, 0xFF, 1.0f, 0);
    animSetSpeed(arg0, 0, 1.0f);
    animSetLoopLimit(arg0, 0, -1);
    actorAllocSubBuffer(arg0, 2);
    actorCopyPoseAndScale(arg0, arg1, 0.15f);
}

typedef struct FloatAt4View {
    u8 pad0[4];
    f32 unk4;
} FloatAt4View;
extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];
u32 randomLcgNext(void);

void func_80690190(arg0, arg1)
FloatAt4View *arg0;
s16 arg1;
{
    s16 idx;

    idx = D_80770628[gCurrentActor->soundSlot];
    if (gCurrentActor->y < gCurrentActor->waterY + 4.0f) {
        D_80770B68[idx] = ((f64)gCurrentActor->speedXZ / 300.0) + 1.0;
        D_80770BC0[idx] = 1.0f;
    } else {
        D_80770B68[idx] = (f64)arg0->unk4 + 1.2;
        D_80770BC0[idx] = 5.0f;
    }

    idx = D_80770628[*(s16 *)gCurrentActor->unk70];
    if (gCurrentActor->y < gCurrentActor->waterY + 4.0f) {
        if (D_80770BC0[idx] == 0.0f) {
            D_80770B68[idx] = (((f64)(u32)randomLcgNext() / 4294967295.0) * 0.05 + 0.975) * (0.2 + ((f64)gCurrentActor->speedXZ / 300.0));
            D_80770BC0[idx] = 1.0f;
        }
    } else {
        D_80770B68[idx] = ((f64)arg0->unk4 * 1.5) + 0.2;
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

SpawnCoord *func_806C96C4(s32);

void actorInitFromSpawnPoint(SpawnPointActor *arg0, ProjectileActorSub174 *arg1) {
    SpawnCoord *temp_v0;
    s16 temp;

    temp_v0 = func_806C96C4(arg1->unk36);
    arg0->unk7C = temp_v0->x;
    arg0->unk80 = temp_v0->y;
    arg0->unk84 = temp_v0->z;
    temp = (u32)temp_v0->yaw * 16.062746f;
    arg0->unkE6 = temp;
    arg0->unkEE = temp;
    arg1->unk0 = temp;
}

void actorSpawn(s32, s32);
void actorInitAnimations(Actor *, Actor *);
extern Actor *gSpawnedActor;

void actorSpawnChildActor(Actor *arg0) {
    ProjectileActorSub174 *sp24 = arg0->customState;
    ProjectileActorSub174 *temp_v0;
    s32 pad;
    Actor *temp_a0;

    actorSpawn(0x13F, 0xDA);
    temp_a0 = gSpawnedActor;
    temp_v0 = temp_a0->customState;
    temp_v0->unk28 = sp24->unk1A4;
    actorInitAnimations(temp_a0, arg0);
    temp_v0->unk35 = 0;
    temp_v0->unk27 = 0;
    temp_v0->unk0 = arg0->yaw;
    sp24->unk88 = temp_a0;
    temp_a0->flags &= ~0x20000;
}

typedef struct PlayerInteractionState {
    u8 pad0[0xF3];
    u8 unkF3;
} PlayerInteractionState;

typedef struct PlayerActor104 {
    u8 pad0[0x174];
    PlayerInteractionState *unk174;
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

typedef struct PlayerInteractionEntry {
    u8 pad0[4];
    PlayerInteractionActor *actor;
    u8 pad8[0x2F0 - 8];
} PlayerInteractionEntry;

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

struct PlayerTrackEntry;
extern u8 gGameMode;
extern f32 D_80750300;
extern Actor *gPrimaryPlayerActor;
void camSetTargetScaled(void *, Actor *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_8068F72C();
void func_80690190();
void lensFlareAddSource(f32, f32, s32, f32, f32, f32, f32, s32, s32, s32);
s32 flagGet(s32, s32);

void actorUpdatePlayerInteraction(void) {
    ProjectileActorSub174 *sp5C;
    PlayerInteractionActor *playerActor;
    PlayerActorSub174 *sp54;
    s32 sp50;
    PlayerInteractionState *sp4C;
    u8 sp4B;
    f32 sp44;
    f32 sp40;
    s32 sp3C;

    sp5C = G_PLAYER_INTERACT_ACTOR->unk174;
    sp50 = (s32)G_PLAYER_INTERACT_ACTOR->unk178;
    playerActor = ((PlayerInteractionEntry *)gPlayerSlots)[sp5C->unk28].actor;
    sp54 = playerActor->unk174;
    sp4C = sp54->unk104->unk174;
    sp4B = G_PLAYER_INTERACT_ACTOR->unk6A & 1;
    sp5C->unk34 = 2;
    func_80690190(sp5C, sp50, sp54);
    if (gGameMode == 0 && sp4C->unkF3 != 4) {
        camSetTargetScaled(sp54->unk104, gCurrentActor, 4, 0x800, 0xA0, 0, 6, 0x12C, 0x8F, 0, 0.2f);
    }
    func_8068F72C(sp5C, sp50, 1, 1);
    actorInterpolateAngles(sp4B, (ProjectileAngleTarget *)sp5C, (ProjectileAngleStep *)sp50);
    if (!(G_PLAYER_INTERACT_ACTOR->unk60 & 0x10)) {
        G_PLAYER_INTERACT_ACTOR->unkC4 = D_80750300;
        G_PLAYER_INTERACT_ACTOR->unk144 = 0x3C;
        playerStateQueueCallback(0x4C, gCurrentActor, sp54->unk1A4);
    }
    if (camIsCutsceneActive() == 0 || (camIsCutsceneActive() != 0 && (gPrimaryPlayerActor->contactFlags & 0x100))) {
        actorGetNodePos(gCurrentActor, 1, &sp44, &sp40, (f32 *)&sp3C);
        lightAdd(sp44, sp40, sp3C, 0.0f, 0.0f, 0.0f, 300.0f, 0, 0xFF, 0xFF, 0xFF);
        if (flagGet(0x6B, 2) == 0) {
            if (camIsCutsceneActive() != 0 && (gPrimaryPlayerActor->contactFlags & 0x100)) {
                actorGetNodePos(gCurrentActor, 2, &sp44, &sp40, (f32 *)&sp3C);
                lensFlareAddSource(sp44, sp40, sp3C, 0.0f, 0.0f, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF);
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
void projectileSetTargetCoords(f32 arg0, f32 arg1, f32 arg2) {
    D_807FC7B0 = arg0;
    D_807FC7B4 = arg1;
    D_807FC7B8 = arg2;
}

#include "actor.h"

void projectileCalculateTrajectoryAndSpawn(s16, s16, s16, f32, f32, f32, f32, f32, s32);
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
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, void *);
typedef struct {
    s16 unk0;
    char pad2[6];
    f32 unk8;
    f32 unkC;
    u8 pad10;
    u8 unk11;
} ProjectileTrackerSub174;
extern s32 gCamActor;
void waterRippleStart(f32, f32, f32, f32, f32, f32);
void camStartShake(s32, s32, s32);
void effectSetDepth(s32);
void effectSetSpeed(s32);
void effectSetMode(s32);
void effectSetCallback(void *);
void effectCreateAtPosition(void *, f32, f32, f32, f32);
extern u8 D_80750AD0;

void projectileGetTargetCoords(Actor *arg0, s32 arg1) {
    actorGetNodePos(arg0, arg1, &D_807FC7B0, &D_807FC7B4, &D_807FC7B8);
}

void projectileSpawnNodeEntry(s16 arg0, s16 arg1, f32 arg2, s16 arg3, f32 arg4, f32 arg5, s32 arg6) {
    ProjectileSpawnParams sp28;

    sp28.unk0 = (f32)(((f64)arg3 / 4095.0) * 6.28318548202514648);
    sp28.unk4 = arg4;
    sp28.unkC = arg2;
    sp28.unk8 = arg5;
    sp28.unk10 = (f32)arg1;
    sp28.unk14 = (f32)(u32)D_80750270;
    actorListSpawnNodeEntry(arg0, D_807FC7B0, D_807FC7B4, D_807FC7B8, 0, arg2, arg6, &sp28);
    D_80750270 = 0;
}

void projectileCalculateTrajectoryAndSpawn(s16 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8) {
    f32 sp2C;
    f32 sp28;

    sp2C = sqrtf(((arg4 - D_807FC7B0) * (arg4 - D_807FC7B0)) + ((arg5 - D_807FC7B4) * (arg5 - D_807FC7B4)) + ((arg6 - D_807FC7B8) * (arg6 - D_807FC7B8)));
    sp28 = arg5 - D_807FC7B4;
    projectileSpawnNodeEntry(arg1, arg2, arg3, arg0, sqrtf(((arg4 - D_807FC7B0) * (arg4 - D_807FC7B0)) + ((arg6 - D_807FC7B8) * (arg6 - D_807FC7B8))) / (sp2C / arg7), sp28 / (sp2C / arg7), arg8);
}

void projectileAimAndSpawn(s16 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7) {
    projectileCalculateTrajectoryAndSpawn(mathAngleBetweenPoints2D(arg3, arg5, D_807FC7B0, D_807FC7B8), arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

s16 mathAngleDistance(s16, s16);
void projectileClampAngleAndSpawn(s16 arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, s32 arg9) {
    s16 sp3C;
    s16 sp38;
    s16 var_s0;

    var_s0 = mathAngleBetweenPoints2D(arg5, arg7, D_807FC7B0, D_807FC7B8);
    if (arg1 < mathAngleDistance(arg0, var_s0)) {
        sp3C = (arg0 - arg1) & 0xFFF;
        sp38 = (arg0 + arg1) & 0xFFF;
        if (mathAngleDistance(var_s0, sp3C) < mathAngleDistance(var_s0, sp38)) {
            var_s0 = sp3C;
        } else {
            var_s0 = sp38;
        }
    }
    projectileCalculateTrajectoryAndSpawn(var_s0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

void projectileAimFromActorAndSpawn(s16 arg0, s16 arg1, f32 arg2, Actor *arg3, s32 arg4, f32 arg5, s32 arg6) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    actorGetNodePos(arg3, arg4, &sp34, &sp30, &sp2C);
    projectileAimAndSpawn(arg0, arg1, arg2, sp34, sp30, sp2C, arg5, arg6);
}

typedef struct OwnerPlayerStateView {
    u8 pad0[0x104];
    Actor *unk104;
} OwnerPlayerStateView;
typedef struct OwnerKongStateView {
    u8 pad0[0xF3];
    u8 unkF3;
} OwnerKongStateView;
typedef struct ProjectileHomingState {
    u8 pad0[0x14];
    f32 unk14;
    u8 pad18[4];
    Actor *unk1C;
} ProjectileHomingState;
extern u32 gGlobalOverlayFlags;
void func_800268C0(s32);
void effectLifetimeCountdownUpdate(void);
s32 projectileFindHomingTarget();

void projectileSteerTowardTarget(arg0, arg1, arg2, arg3)
u16 arg0;
Actor *arg1;
void *arg2;
u8 arg3;
{
    OwnerPlayerStateView *temp_a; // named pointer-chain locals: colour the two chain loads into v0/v1
    Actor *sp78;
    s16 sp76;
    s16 temp_lo;
    s16 pad74;
    s16 sp70;
    s16 sp6E;
    s16 sp6C;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 dist;
    f64 pad58;
    OwnerKongStateView *temp_t4;
    ProjectileHomingState *sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 var_fv0;
    f32 ratio;

    sp50 = arg1->customState;
    if (!((f64)arg1->speedXZ < 0.1)) {
        if (arg2 != 0) {
            temp_a = ((Actor *)arg1->parentActor)->customState;
            temp_t4 = temp_a->unk104->customState;
            if (temp_t4->unkF3 == 3) {
                effectSetCallback(effectLifetimeCountdownUpdate);
                effectSetSpeed(0x32);
                effectCreateAtPosition(arg2, sp50->unk14, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        if (projectileFindHomingTarget(arg0, (void **)&sp78, arg1, 0, *(u8 *)&arg3, arg3 == 0, &sp4C, &sp48, &sp44) != 0) { // FAKE: address-taken byte read keeps the arg3 lbu in a ring temp (candidate left uncoloured)
            sp76 = mathAngleBetweenPoints2D(sp4C, sp44, arg1->x, arg1->z);
            temp_lo = mathAngleDistance(sp76, arg1->moveYaw) / 10;
            sp70 = (arg1->moveYaw + temp_lo) & 0xFFF;
            sp6E = (arg1->moveYaw - temp_lo) & 0xFFF;
            sp6C = mathAngleDistance(sp70, sp76);
            if (sp6C < mathAngleDistance(sp6E, sp76)) {
                arg1->moveYaw = sp70;
            } else {
                arg1->moveYaw = sp6E;
            }
            if (arg3 == 0) {
                temp_fv0 = sp4C - arg1->x;
                temp_fv1 = sp44 - arg1->z;
                dist = sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1));
                if (dist < 100.0f) {
                    sp50->unk1C = sp78;
                    if ((sp78 != NULL) && (gGlobalOverlayFlags & 0x04000000)) {
                        func_800268C0(0x80);
                    }
                }
                ratio = dist / (arg1->speedXZ * 0.025f);
                if (sp78 != NULL) {
                    var_fv0 = (f64)sp78->eyeHeight * 0.5;
                } else {
                    var_fv0 = 0.0f;
                }
                arg1->speedY = (((sp48 + var_fv0) - arg1->y) / ratio) / 0.025f;
            }
        } else if (sp50->unk1C != NULL) {
            if (gGlobalOverlayFlags & 0x04000000) {
                func_800268C0(4);
            }
            sp50->unk1C = NULL;
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

typedef struct PlayerAimView {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[0x228 - 0x21C];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
    u8 pad234[0x2F0 - 0x234];
} PlayerAimView;

extern ModelSlotPosTypeView *gModelSlots;
extern s32 D_80747D70;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
f32 mathCosF(s16);
f32 mathSinF(s16);

s32 projectileFindHomingTarget(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
u16 arg0;
void **arg1;
Actor *arg2;
u8 arg3;
u8 arg4;
u8 arg5;
f32 *arg6;
f32 *arg7;
f32 *arg8;
{
    s32 padTop[2];
    s32 ret;
    s32 i;
    Actor *a;
    u8 v1;
    s32 j;
    PlayerAimView *pl;
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
    f32 x1;
    f32 y1;
    f32 z1;
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
    if (arg3) {
        best = 0.92f;
    }
    *arg1 = NULL;
    if (arg3) {
        idx = ((ProjectileActorSub174 *)arg2->customState)->unk1A4;
        pl = &((PlayerAimView *)gPlayerSlots)[idx];
        x1 = pl->unk228;
        y1 = pl->unk22C;
        z1 = pl->unk230;
        ox = pl->unk210;
        oy = pl->unk214;
        oz = pl->unk218;
    } else {
        scale = arg2->speedXZ * 0.025f;
        x1 = mathSinF(arg2->moveYaw) * scale + arg2->x;
        z1 = mathCosF(arg2->moveYaw) * scale + arg2->z;
        y1 = arg2->y + arg2->speedY * 0.025f;
        ox = arg2->x;
        oy = arg2->y;
        oz = arg2->z;
    }
    d[0] = x1 - ox;
    d[1] = y1 - oy;
    d[2] = z1 - oz;
    len = sqrtf((d[0] * d[0] + d[1] * d[1]) + d[2] * d[2]);
    if (len == 0.0) {
        len = 0.1f;
    }
    dirX = d[0] / len;
    dirY = d[1] / len;
    dirZ = d[2] / len;
    for (i = 0; i < gActiveActorCount; i++) {
        a = gActiveActors[i].actor;
        if (arg2 != a && (!(a->collisionFlags & 2) || a->state != 0x37) && (a->collisionFlags & arg0)) {
            if (arg4 == 0 || ((oy < a->y) ? (a->y - oy) : -(a->y - oy)) < 30.0f) {
                v1 = 1;
                if (a->collisionFlags & 1) {
                    sub = a->customState;
                    v1 = *(u8 *)&((PlayerAimView *)gPlayerSlots)[sub->unk1A4];
                }
                if (v1 != 0) {
                    tmp = (f32)((f64)a->y + (f64)a->eyeHeight * 0.5);
                    d[0] = a->x - ox;
                    t = tmp - oy;
                    d[1] = t;
                    d[2] = a->z - oz;
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
                        d2x = a->x - ox;
                        d2z = a->z - oz;
                        if (sqrtf(d2x * d2x + t * t + d2z * d2z) < 1000.0f) {
                            best = dot;
                            *arg1 = a;
                            ret = 1;
                            *arg6 = a->x;
                            *arg7 = a->y;
                            *arg8 = a->z;
                        }
                    }
                }
            }
        }
    }
    if (arg5 != 0) {
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
                            *arg1 = NULL;
                            *arg6 = px;
                            *arg7 = py;
                            ret = 1;
                            *arg8 = pz;
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

void effectSetColor(s32, s32, s32, s32);
extern s32 sEffectSparkConfig;
void func_80717D4C(void);
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

void projectileSpawnWithShockwave(s16 arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    actorSpawn(0x102, arg0);
    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, arg1);
    *(s16 *)((u8 *)gSpawnedActor + 0xF0) = arg0;
    gSpawnedActor->tintR = arg2;
    gSpawnedActor->tintG = arg3;
    gSpawnedActor->tintB = arg4;
    gSpawnedActor->unk15F = arg5;
    gSpawnedActor->yawSpeed = 1;
    *(f64 *)&gSpawnedActor->splineT = (f64)arg6;
    if (arg7 != 0.0f) {
        waterRippleStart(gCurrentActor->x, gCurrentActor->z, arg7, 2.0f, arg8, arg9);
    }
    camStartShake(gCamActor, 0x50, 0x14);
}

void projectileSpawnActor107(u8 arg0, u8 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    ProjectileTrackerSub174 *sub;

    actorSpawn(0x107, 0);
    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.15f);
    sub = gSpawnedActor->customState;
    sub->unk11 = arg0;
    sub->unk8 = arg2;
    sub->unkC = arg3;
    sub->unk0 = arg1;
    gSpawnedActor->y = *(f32 *)gCurrentActor->unkA8;
    gSpawnedActor->unk15F = arg4;
    gSpawnedActor->yawSpeed = arg5;
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

typedef struct PlayerCameraPosView {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} PlayerCameraPosView;

#define PROJECTILE_BOUNCE_ACTOR ((ProjectileBounceActor *)gCurrentActor)

extern u8 D_80720340;
extern u8 D_8072038C;
extern u32 gGameFrameCounter;
extern s16 D_80750344;
extern u8 D_807FBB85;
void billboardSetFlags(s16);
void effectLightPulseOscillate(void);
void effectSpinBillboardingUpdate(void);
void func_8071BC80(void);
void effectSetMaxDistance(s32);
void effectSetDuration(s32);
void actorSetCollisionRadius(Actor *, f32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void actorUpdatePrevContactFlags(Actor *);
void billboardSubmit(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void effectSetFlags(s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
s32 effectCreateAtActorBone(void *, f32, Actor *, s32, s32);

void projectileBounceParticleUpdate(void *arg0) {
    f32 sp48;
    ProjectileBounceState *temp_s3;
    s32 var_s1;
    u32 var_a0;
    f32 sp64;

    temp_s3 = PROJECTILE_BOUNCE_ACTOR->unk174;
    sp64 = PROJECTILE_BOUNCE_ACTOR->unk124->unkC;
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
        temp_s3->unk13 = (u8)(u32)PROJECTILE_BOUNCE_ACTOR->unk124->unk10;
        if (temp_s3->unk13 != 0) {
            var_a0 = 0xC8;
        } else {
            var_a0 = 0x3C;
        }
        sp48 = var_a0;
        actorSetCollisionRadius(gCurrentActor, sp48);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 35.0f, -1);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, sp48, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetMaxDistance(1000);
        effectSetFlags(4);
        effectCreateAtActorBone(arg0, sp64, gCurrentActor, 1, 2);
        if (temp_s3->unk13 >= 0xB) {
            PROJECTILE_BOUNCE_ACTOR->unk132 = 2;
        }
        temp_s3->unk0 = gGameFrameCounter;
        if (temp_s3->unk13 == 5) {
            temp_s3->unk0 = temp_s3->unk0 - D_80750344 + 0x1E;
        }
        temp_s3->unk12 = 0;
        PROJECTILE_BOUNCE_ACTOR->unk60 |= 0x80000;
        PROJECTILE_BOUNCE_ACTOR->unkEC = 0;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    if (PROJECTILE_BOUNCE_ACTOR->unk144 & 8) {
        actorUpdateFloorContactAndTilt(gCurrentActor, temp_s3->unk13 != 0 ? sp64 * 6.0 * 4.0 : 0.0);
    }
    if (temp_s3->unk13 >= 0xA) {
        if (temp_s3->unk13 == 0x1E) {
            billboardSetFlags(3);
        }
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x320, 0x78, 0, 1.0f);
        if (PROJECTILE_BOUNCE_ACTOR->unk6A & 1) {
            if (temp_s3->unk12 == 0) {
                switch (temp_s3->unk13) {
                case 11:
                    projectileSpawnActor107(0, 0, 5.0f, 2.0f, 1, 0);
                    break;
                case 20:
                    projectileSpawnActor107(1, 7, 5.0f, 3.0f, 0xC8, 0x20);
                    break;
                }
                camStartShake(gCamActor, 0xA, 0x14);
                temp_s3->unk12 = 2;
            } else {
                temp_s3->unk12 = temp_s3->unk12 - 1;
            }
        }
    } else {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x78, 0x78, 0, 1.0f);
        if ((PROJECTILE_BOUNCE_ACTOR->unk6A & 1) && temp_s3->unk12 == 0 && (PROJECTILE_BOUNCE_ACTOR->unk144 & 8)) {
            temp_s3->unk12 = 0xA;
        }
        if (temp_s3->unk12 != 0) {
            effectSetDepth(1);
            effectSetDuration(1);
            effectSetCallback(effectSpinBillboardingUpdate);
            effectCreateAtPosition(&D_80720340, PROJECTILE_BOUNCE_ACTOR->unk124->unkC, PROJECTILE_BOUNCE_ACTOR->unk7C, PROJECTILE_BOUNCE_ACTOR->unk80, PROJECTILE_BOUNCE_ACTOR->unk84);
            temp_s3->unk12 = temp_s3->unk12 - 1;
        }
    }
    if (PROJECTILE_BOUNCE_ACTOR->unkEC == 0) {
        f32 dx = PROJECTILE_BOUNCE_ACTOR->unk7C - ((PlayerCameraPosView *)gPlayerSlots)->unk210;
        f32 dy = PROJECTILE_BOUNCE_ACTOR->unk80 - ((PlayerCameraPosView *)gPlayerSlots)->unk214;
        dx = dx * dx;
        dx = dy * dy + dx;
        dy = PROJECTILE_BOUNCE_ACTOR->unk84 - ((PlayerCameraPosView *)gPlayerSlots)->unk218;
        dx = dy * dy + dx;
        if (dx < 20000.0f) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x128, 0xFF, 0x7F, 0);
            PROJECTILE_BOUNCE_ACTOR->unkEC = PROJECTILE_BOUNCE_ACTOR->unkEC + 1;
        }
    }
    if (PROJECTILE_BOUNCE_ACTOR->unkFC != 0 || temp_s3->unk12 == 1 || D_807FBB85 != 0) {
        effectSetDepth(1);
        effectSetDuration(1);
        if (PROJECTILE_BOUNCE_ACTOR->unk58 != 0x3B && temp_s3->unk13 != 0x63) {
            effectSetSpeed(0x100FA);
            effectSetCallback(effectLightPulseOscillate);
        }
        effectCreateAtPosition(&D_80720340, 2.0 * PROJECTILE_BOUNCE_ACTOR->unk124->unkC, PROJECTILE_BOUNCE_ACTOR->unk7C, PROJECTILE_BOUNCE_ACTOR->unk80, PROJECTILE_BOUNCE_ACTOR->unk84);
        if (temp_s3->unk13 < 0xA) {
            for (var_s1 = -0x12C; var_s1 != 0x12C; var_s1 += 0x32) {
                effectSetDepth(1);
                effectSetDuration(2);
                effectSetSpeed((PROJECTILE_BOUNCE_ACTOR->unkEE + var_s1) % 4095);
                effectSetCallback(func_8071BC80);
                effectCreateAtPosition(&D_8072038C, PROJECTILE_BOUNCE_ACTOR->unk124->unkC * 0.5, PROJECTILE_BOUNCE_ACTOR->unk7C, PROJECTILE_BOUNCE_ACTOR->unk80, PROJECTILE_BOUNCE_ACTOR->unk84);
            }
        }
        sfxPlayAtPositionPooled(PROJECTILE_BOUNCE_ACTOR->unk7C, PROJECTILE_BOUNCE_ACTOR->unk80, PROJECTILE_BOUNCE_ACTOR->unk84, 0xF6, 0xFF, 0x7F, 0x1E, 0x1E, 0.7f, 0);
        actorDespawn(gCurrentActor);
    }
    if (temp_s3->unk0 + D_80750344 < gGameFrameCounter) {
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
void effectGrowExpandMatrixUpdate(void);
s32 randomNonNegative(void);

void projectileSparkleUpdate(s32 arg0) {
    SparkleParticleState *sp2C;

    sp2C = (SparkleParticleState *)G_SPARKLE_ACTOR->unk174;
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
        switch ((u8)arg0) {
        case 0:
            effectSetColor(0xFF, 0xD7, 0x58, 0xFF);
            effectCreateAtActorBone(&D_80720120, G_SPARKLE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
            break;
        case 1:
            effectSetColor(0xC8, 0xC8, 0xFA, 0x9B);
            effectCreateAtActorBone(&D_80720BE8, G_SPARKLE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
            break;
        }
        sp2C->unk13 = (u8)(u32)G_SPARKLE_ACTOR->unk124->unk10;
        sp2C->unk0 = gGameFrameCounter;
        sp2C->unk12 = 0;
        G_SPARKLE_ACTOR->unk60 |= 0x80000;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    if ((G_SPARKLE_ACTOR->unk6A & 1) || (G_SPARKLE_ACTOR->unkFC != 0) || (D_807FBB85 != 0) || ((u32)(sp2C->unk0 + 24) < gGameFrameCounter)) {
        actorDespawn(gCurrentActor);
    }
}

void projectileBounceParticleUpdate(void *);
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

typedef struct PlayerTrackEntry {
    u8 pad0[0x4];
    PlayerTrackActor *actor;
    u8 pad8[0x2F0 - 0x8];
} PlayerTrackEntry;

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
extern PlayerTrackEntry *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 D_8072029C;
extern u8 D_80720BA0;
extern s16 D_8075035C;
extern s16 D_80750370;

void effectLifetimeCountdownUpdate(void);
void effectRadialSprayUpdate(void);
void camStartShakeFromPoint(s32, s32, s32, f32, f32, f32, f32, f32);
void actorSpawnSparkleBurst(void);
void projectileSteerTowardTarget(s32, Actor *, void *, s32);
s32 actorGetFloorSnapped(void);
s32 collisionGetStateByte(void);

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
    u32 *sp44;
    u8 unkFC;
    Actor *other;

    sp44 = (u32 *)G_PROJECTILE_ACTOR->unk174;
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
        *sp44 = gGameFrameCounter;
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
    if ((u32)(*sp44 + D_80750344) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

extern u8 D_807200A0;
extern u8 D_8071FB34;
extern s16 D_80750350;
extern s16 D_80750364;
s32 actorAngleInArc(Actor *, s16);

void projectileHomingUpdate(void) {
    ProjectileActorExtra *sp44;
    s16 var_a0;
    u8 flag;
    s32 sp3C;
    s32 var_s1;

    sp44 = (ProjectileActorExtra *)G_PROJECTILE_ACTOR->unk174;
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
        sp44->unk14 = G_PROJECTILE_ACTOR->unk124->unkC;
        sp44->unk0 = gGameFrameCounter;
        G_PROJECTILE_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ACTOR->unk16F = 0x3C;
        sp44->unk13 = (u8)(u32)G_PROJECTILE_ACTOR->unk124->unk10;
        sp44->unk1C = 0;
    }
    sp3C = D_80750350;
    if (sp44->unk13 & 2) {
        var_a0 = 2;
        if (gPlayerCount >= 2) {
            var_a0 = 3;
        }
        projectileSteerTowardTarget(var_a0, gCurrentActor, &D_807200A0, 0);
    }
    if (sp44->unk13 & 4) {
        sp3C = D_80750364;
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
        (G_PROJECTILE_ACTOR->unk124->unk14 != 0.0f && (u32)(sp44->unk0 + 1) < gGameFrameCounter)) {
        effectSetDepth(1);
        effectSetSpeed(0x1006E);
        effectSetCallback(effectLightPulseOscillate);
        effectCreateAtPosition(&D_8071FB34, 0.45f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x8D, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
        if (D_80750AD0 == 0) {
            for (var_s1 = 0; var_s1 != 0xC; var_s1 += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + var_s1);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_807200EC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
    }
    if (gPlayerCount >= 2) {
        sp3C = (s32)((f32)sp3C * 1.4f);
    }
    if (gCurrentMap == 0x10) {
        sp3C = (s32)((f64)sp3C * 1.2);
    }
    if ((u32)(sp44->unk0 + sp3C) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

void projectileMultiplayerUpdate(void) {
    ProjectileActorExtra *sp44;
    s32 var_a0;
    s32 sp3C;
    s32 var_s1;
    sp44 = (ProjectileActorExtra *)G_PROJECTILE_ACTOR->unk174;
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
        sp44->unk14 = G_PROJECTILE_ACTOR->unk124->unkC;
        sp44->unk0 = gGameFrameCounter;
        G_PROJECTILE_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ACTOR->unk16F = 0x3C;
        sp44->unk13 = (u8)(u32)G_PROJECTILE_ACTOR->unk124->unk10;
        sp44->unk1C = 0;
    }
    sp3C = D_8075035C;
    if (sp44->unk13 & 2) {
        var_a0 = 2;
        if (gPlayerCount >= 2) {
            var_a0 = 3;
        }
        projectileSteerTowardTarget(var_a0, gCurrentActor, &D_8072029C, 0);
    }
    if (sp44->unk13 & 4) {
        sp3C = D_80750370;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (G_PROJECTILE_ACTOR->unkFD != 0 ||
        actorGetFloorSnapped() != 0 ||
        ((G_PROJECTILE_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) ||
        D_807FBB85 != 0 ||
        (G_PROJECTILE_ACTOR->unk124->unk14 != 0.0f && (u32)(sp44->unk0 + 1) < gGameFrameCounter)) {
        if (D_80750AD0 == 0) {
            for (var_s1 = 0; var_s1 != 0xC; var_s1 += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x05000000 + var_s1);
                effectSetMode(1);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_80720BA0, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x91, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
    }
    if (gPlayerCount >= 2) {
        sp3C = (s32)((f32)sp3C * 1.4f);
    }
    if ((u32)(sp44->unk0 + sp3C) < gGameFrameCounter) {
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
        camStartShakeFromPoint(gPlayerSlots[i].actor->unk174->unk104, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
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
s16 mathAngleArcMidpoint(s16, s16);

void projectileBounceExplodeScaledUpdate(void) {
    ProjectileBounceExplodeState *sp64;
    s16 t;
    u8 flag;
    f32 sp5C;
    s32 var_s0;
    f32 sp3C;
    s32 var_a0;

    sp64 = BOUNCE_EXPLODE_ACTOR->unk174;
    flag = 0;
    sp5C = BOUNCE_EXPLODE_ACTOR->unk124->unkC * 2.5f;
    if (!(BOUNCE_EXPLODE_ACTOR->unk60 & 0x10)) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF4, 0xFF, 0x7F, 5);
        BOUNCE_EXPLODE_ACTOR->unk6A &= 0xFFFE;
        BOUNCE_EXPLODE_ACTOR->unkEE = (s16)((BOUNCE_EXPLODE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        BOUNCE_EXPLODE_ACTOR->unkB8 = (f32)(((f64)(BOUNCE_EXPLODE_ACTOR->unk124->unk4 / (f32)4)) * 2.6);
        BOUNCE_EXPLODE_ACTOR->unkB8 *= sp5C;
        BOUNCE_EXPLODE_ACTOR->unkC0 = BOUNCE_EXPLODE_ACTOR->unk124->unk8;
        BOUNCE_EXPLODE_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, sp5C * 60.0);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, sp5C * 50.0, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        sp64->unk13 = (u8)(u32)BOUNCE_EXPLODE_ACTOR->unk124->unk10;
        effectSetDuration(-1);
        effectSetDepth(1);
        sp64->unk0 = gGameFrameCounter;
        if (sp64->unk13 >= 0xCA) {
            effectSetSpeed(0xA);
            effectSetCallback(effectLightPulseOscillate);
        }
        if (sp64->unk13 >= 0xCB) {
            BOUNCE_EXPLODE_ACTOR->unkC0 = 250.0f * sp5C;
            sp64->unk0 -= D_80750348 - D_8075034C;
        } else {
            BOUNCE_EXPLODE_ACTOR->unkC0 = 200.0f * sp5C;
        }
        effectCreateAtActorBone(&D_80720268, BOUNCE_EXPLODE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        sp64->unk4 = 0;
        BOUNCE_EXPLODE_ACTOR->unk60 |= 0x01080000;
        BOUNCE_EXPLODE_ACTOR->unkFA = 0x2328;
        var_a0 = (u32)(60.0f * sp5C);
        BOUNCE_EXPLODE_ACTOR->unk16E = var_a0;
        BOUNCE_EXPLODE_ACTOR->unk16F = var_a0;
        sp64->unk1C = 0;
        sp64->unk20 = 0;
    }
    if ((u32)(sp64->unk0 + 5) < gGameFrameCounter) {
        BOUNCE_EXPLODE_ACTOR->unk60 &= ~0x00080000;
    }
    var_a0 = 2;
    if (gPlayerCount >= 2) {
        var_a0 = 3;
    }
    projectileSteerTowardTarget(var_a0, gCurrentActor, NULL, 1);
    actorUpdatePrevContactFlags(gCurrentActor);
    if (BOUNCE_EXPLODE_ACTOR->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, BOUNCE_EXPLODE_ACTOR->unkEE) == 0) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        var_a0 = mathAngleArcMidpoint(BOUNCE_EXPLODE_ACTOR->arcYawMin, BOUNCE_EXPLODE_ACTOR->arcYawMax);
        t = BOUNCE_EXPLODE_ACTOR->unkEE;
        t = (t + 0x800) & 0xFFF;
        var_a0 += (s16)(var_a0 - t);
        BOUNCE_EXPLODE_ACTOR->unkEE = var_a0;
        if (BOUNCE_EXPLODE_ACTOR->unkEE < 0) {
            BOUNCE_EXPLODE_ACTOR->unkEE += 0xFFF;
        }
        if (BOUNCE_EXPLODE_ACTOR->unkEE >= 0x1000) {
            BOUNCE_EXPLODE_ACTOR->unkEE -= 0xFFF;
        }
        if (actorAngleInArc(gCurrentActor, BOUNCE_EXPLODE_ACTOR->unkEE) == 0) {
            flag = 1;
        }
    }
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    BOUNCE_EXPLODE_ACTOR->unkC0 += D_807502E4 * sp5C;
    if (BOUNCE_EXPLODE_ACTOR->unkC0 < (f32)D_807502D0) {
        BOUNCE_EXPLODE_ACTOR->unkC0 = (f32)D_807502D0;
    }
    if ((BOUNCE_EXPLODE_ACTOR->unk6A & 1) && !(BOUNCE_EXPLODE_ACTOR->unk6C & 1)) {
        switch (sp64->unk4) {
        case 0:
            BOUNCE_EXPLODE_ACTOR->unkC0 = 200.0f * sp5C;
            break;
        case 1:
            sp3C = 100.0f * sp5C;
            BOUNCE_EXPLODE_ACTOR->unkC0 = 150.0f * sp5C;
            actorSetCollisionRadius(gCurrentActor, sp3C);
            actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, sp3C, -1);
            break;
        case 2:
            sp3C = 150.0f * sp5C;
            BOUNCE_EXPLODE_ACTOR->unkC0 = 100.0f * sp5C;
            actorSetCollisionRadius(gCurrentActor, sp3C);
            actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, sp3C, -1);
            break;
        case 3:
            BOUNCE_EXPLODE_ACTOR->unkC0 = 80.0f * sp5C;
            break;
        }
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        sp64->unk4++;
        BOUNCE_EXPLODE_ACTOR->unkB8 = ((f64)BOUNCE_EXPLODE_ACTOR->unkB8 / 3.0) * 2.5;
    }
    if (D_807200EC && D_807200EC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if ((BOUNCE_EXPLODE_ACTOR->unk6A & 1) && (BOUNCE_EXPLODE_ACTOR->unk6C & 1)) {
        sp64->unk20++;
    } else {
        sp64->unk20 = 0;
    }
    if (sp64->unk20 == 4) {
        gActorGlobalState.unk15 = 1;
    }
    if (BOUNCE_EXPLODE_ACTOR->unk124->unk14 != 0.0f && (u32)(sp64->unk0 + 1) < gGameFrameCounter) {
        gActorGlobalState.unk15 = 1;
    }
    if ((BOUNCE_EXPLODE_ACTOR->unk64 & 0x100) || flag != 0) {
        gActorGlobalState.unk15 = 1;
    }
    if ((((BOUNCE_EXPLODE_ACTOR->unk6A & 1) && sp64->unk4 == 4) || gActorGlobalState.unk15 != 0) && BOUNCE_EXPLODE_ACTOR->unk154 == 0) {
        sp3C = 250.0f * sp5C;
        if (sp64->unk13 != 0xCA) {
            effectSetDepth(1);
            effectSetSpeed(0x100D2);
            effectSetCallback(effectLightPulseOscillate);
            effectCreateAtPosition(&D_80720120, 2.0f, gCurrentActor->x, gCurrentActor->y + 22.0f, gCurrentActor->z);
            actorSpawnSparkleBurst();
            if (D_80750AD0 == 0) {
                for (var_s0 = 0; var_s0 != 12; var_s0++) {
                    effectSetDepth(1);
                    effectSetSpeed(0x0B010000 + var_s0);
                    effectSetCallback(effectRadialSprayUpdate);
                    effectCreateAtPosition(&D_807200EC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                }
            }
        }
        var_s0 = 0;
        if (gPlayerCount > 0) {
            do {
                camStartShakeFromPoint(gPlayerSlots[var_s0].actor->unk174->unk104, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
                var_s0++;
            } while (var_s0 < gPlayerCount);
        }
        actorSetCollisionRadius(gCurrentActor, sp3C);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, sp3C, -1);
        BOUNCE_EXPLODE_ACTOR->unk154 = 1;
    } else if (BOUNCE_EXPLODE_ACTOR->unk154 != 0) {
        if (BOUNCE_EXPLODE_ACTOR->unk154++ == 2) {
            if (sp64->unk13 != 0xCA) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF6, 0xFF, 0x7F, 0x1E);
            }
            actorDespawn(gCurrentActor);
            D_80029FA0--;
        }
    }
    if ((u32)(sp64->unk0 + D_80750348) < gGameFrameCounter) {
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

void projectileSpawnExplosion(void);
extern u8 D_807201A0;

extern u8 D_80720268;
extern s16 mathAngleArcMidpoint(s16, s16);

void projectileBounceExplodeGreenUpdate(void) {
    ProjectileBeamActorExtra *sp4C;
    s32 pad48;
    u8 sp47;
    s32 pad40;
    s16 temp_v0;
    f32 temp_fv0;

    sp4C = (ProjectileBeamActorExtra *)G_PROJECTILE_BEAM_ACTOR->unk174;
    sp47 = 0;
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
        sp4C->unk0 = gGameFrameCounter;
        sp4C->unk4 = 0;
        G_PROJECTILE_BEAM_ACTOR->unk60 |= 0x80000;
        G_PROJECTILE_BEAM_ACTOR->unkFA = 0x2328;
        sp4C->unk13 = (u8)(u32)G_PROJECTILE_BEAM_ACTOR->unk124->unk10;
        if (sp4C->unk13 == 0x63) {
            sp4C->unk4 = 2;
        }
        sp4C->unk1C = 0;
    }
    if ((u32)(sp4C->unk0 + 10) < gGameFrameCounter) {
        G_PROJECTILE_BEAM_ACTOR->unk60 &= 0xFFF7FFFF;
    }
    projectileSteerTowardTarget(1, gCurrentActor, 0, 1);
    actorUpdatePrevContactFlags(gCurrentActor);
    if (G_PROJECTILE_BEAM_ACTOR->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, G_PROJECTILE_BEAM_ACTOR->unkEE) == 0) {
        s16 angle;
        s16 diff;
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, 0xFF, 0x7F, 0x1E);
        temp_v0 = mathAngleArcMidpoint(G_PROJECTILE_BEAM_ACTOR->arcYawMin, G_PROJECTILE_BEAM_ACTOR->arcYawMax);
        angle = G_PROJECTILE_BEAM_ACTOR->unkEE;
        angle = (angle + 0x800) & 0xFFF;
        diff = temp_v0 - angle;
        G_PROJECTILE_BEAM_ACTOR->unkEE = temp_v0 + diff;
        if (G_PROJECTILE_BEAM_ACTOR->unkEE < 0) {
            G_PROJECTILE_BEAM_ACTOR->unkEE += 0xFFF;
        }
        if (G_PROJECTILE_BEAM_ACTOR->unkEE >= 0x1000) {
            G_PROJECTILE_BEAM_ACTOR->unkEE -= 0xFFF;
        }
        if (actorAngleInArc(gCurrentActor, G_PROJECTILE_BEAM_ACTOR->unkEE) == 0) {
            sp47 = 1;
        }
    }
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 10, 10, 1, 0x4B, 0x78, 0, 1.0f);
    G_PROJECTILE_BEAM_ACTOR->unkC0 += D_807502E4;
    temp_fv0 = (f32)D_807502D0;
    if (G_PROJECTILE_BEAM_ACTOR->unkC0 < temp_fv0) {
        G_PROJECTILE_BEAM_ACTOR->unkC0 = temp_fv0;
    }
    if ((G_PROJECTILE_BEAM_ACTOR->unk6A & 1) && !(G_PROJECTILE_BEAM_ACTOR->unk6C & 1)) {
        switch (sp4C->unk4) {
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
        sp4C->unk4++;
        G_PROJECTILE_BEAM_ACTOR->unkB8 = (f32)(((f64)G_PROJECTILE_BEAM_ACTOR->unkB8 / 3.0) * 2.5);
    }
    if ((G_PROJECTILE_BEAM_ACTOR->unk64 & 0x100) || sp47 != 0) {
        D_807FBB85 = 1;
    }
    if (((G_PROJECTILE_BEAM_ACTOR->unk6A & 1) && sp4C->unk4 == 4) || D_807FBB85 != 0) {
        projectileSpawnExplosion();
        actorDespawn(gCurrentActor);
    }
    if ((u32)(sp4C->unk0 + D_80750344) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

void projectileBeamUpdate(void) {
    ProjectileBeamActorExtra *sp44;
    s32 var_a0;
    s32 sp3C;
    s32 var_s1;
    sp44 = (ProjectileBeamActorExtra *)G_PROJECTILE_BEAM_ACTOR->unk174;
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
        sp44->unk14 = G_PROJECTILE_BEAM_ACTOR->unk124->unkC;
        sp44->unk0 = gGameFrameCounter;
        G_PROJECTILE_BEAM_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_BEAM_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_BEAM_ACTOR->unk16F = 0x3C;
        sp44->unk13 = (u8)(u32)G_PROJECTILE_BEAM_ACTOR->unk124->unk10;
        sp44->unk1C = 0;
    }
    sp3C = D_80750358;
    if (sp44->unk13 & 2) {
        var_a0 = 2;
        if (gPlayerCount >= 2) {
            var_a0 = 3;
        }
        projectileSteerTowardTarget(var_a0, gCurrentActor, &D_807201A0, 0);
    }
    if (sp44->unk13 & 4) {
        sp3C = D_8075036C;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (actorGetFloorSnapped() != 0 ||
        G_PROJECTILE_BEAM_ACTOR->unkFD != 0 ||
        ((G_PROJECTILE_BEAM_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) ||
        D_807FBB85 != 0 ||
        (G_PROJECTILE_BEAM_ACTOR->unk124->unk14 != 0.0f && (u32)(sp44->unk0 + 1) < gGameFrameCounter)) {
        effectSetDepth(1);
        effectSetSpeed(0x1006E);
        effectSetCallback(effectLightPulseOscillate);
        effectCreateAtPosition(&D_8071FB34, 0.45f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1E5, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
        if (D_80750AD0 == 0) {
            for (var_s1 = 0; var_s1 != 0xC; var_s1 += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + var_s1);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_807200EC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
    }
    if (gPlayerCount >= 2) {
        sp3C = (s32)((f32)sp3C * 1.4f);
    }
    if ((u32)(sp44->unk0 + sp3C) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}


void projectileImpactExplosionUpdate(void) {
    ProjectileActorExtra *sp34;
    s32 var_a0;
    s32 sp2C;
    u8 sp2B;

    sp34 = (ProjectileActorExtra *)G_PROJECTILE_ACTOR->unk174;
    sp2B = 0;
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
        sp34->unk14 = G_PROJECTILE_ACTOR->unk124->unkC;
        sp34->unk0 = gGameFrameCounter;
        G_PROJECTILE_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ACTOR->unk16F = 0x3C;
        sp34->unk13 = (u8)(u32)G_PROJECTILE_ACTOR->unk124->unk10;
        sp34->unk1C = 0;
    }
    sp2C = D_80750358;
    if (sp34->unk13 & 2) {
        var_a0 = 2;
        if (gPlayerCount >= 2) {
            var_a0 = 3;
        }
        projectileSteerTowardTarget(var_a0, gCurrentActor, &D_80720268, 0);
    }
    if (sp34->unk13 & 4) {
        sp2C = D_8075036C;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (!gCurrentActor->state && (G_PROJECTILE_ACTOR->unkFD != 0 || (G_PROJECTILE_ACTOR->unk6A & 1) || D_807FBB85 != 0)) {
        sp2B = 1;
    } else if (gCurrentActor->state) {
        if (gCurrentActor->state++ == 2) {
            actorDespawn(gCurrentActor);
        }
    }
    if (gPlayerCount >= 2) {
        sp2C = (s32)((f32)sp2C * 1.4f);
    }
    if ((u32)(sp34->unk0 + sp2C) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
    if (sp2B != 0) {
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
void controllerAnimSetStateIfChanged(Actor *, s32, f32, f32);
void scriptSetActorRampTarget(Actor *, f32, f32);


void projectileRotatingLightUpdate(f32, u8);

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
    ProjectileActorExtra *sp44;
    s32 var_a0;
    s32 sp3C;

    sp44 = (ProjectileActorExtra *)G_PROJECTILE_ACTOR->unk174;
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
        sp44->unk14 = G_PROJECTILE_ACTOR->unk124->unkC;
        sp44->unk0 = gGameFrameCounter;
        G_PROJECTILE_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ACTOR->unk16F = 0x3C;
        sp44->unk13 = (u8)(u32)G_PROJECTILE_ACTOR->unk124->unk10;
        sp44->unk1C = 0;
    }
    sp3C = D_80750360;
    if (sp44->unk13 & 2) {
        var_a0 = 2;
        if (gPlayerCount >= 2) {
            var_a0 = 3;
        }
        projectileSteerTowardTarget(var_a0, gCurrentActor, &D_807206A8, 0);
    }
    if (sp44->unk13 & 4) {
        sp3C = D_80750374;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (G_PROJECTILE_ACTOR->unkFD != 0 ||
        actorGetFloorSnapped() != 0 ||
        ((G_PROJECTILE_ACTOR->unk6A & 1) && collisionGetStateByte() == 1) ||
        D_807FBB85 != 0 ||
        (G_PROJECTILE_ACTOR->unk124->unk14 != 0.0f && (u32)(sp44->unk0 + 1) < gGameFrameCounter)) {
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
        sp3C = (s32)((f32)sp3C * 1.4f);
    }
    if ((u32)(sp44->unk0 + sp3C) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

s32 actorIsActiveType2B(Actor *arg0) {
    if (arg0->actorType != 0x2B) {
        return 1;
    }
    if (arg0->state == 0) {
        return 1;
    }
    return 0;
}

void projectileMatrixRotationUpdate(void) {
    ProjectileRotActorExtra *temp_s2;
    s32 var_a0;
    s32 sp84;
    f32 sp44[4][4];
    temp_s2 = G_PROJECTILE_ROT_ACTOR->unk174;
    if (!(G_PROJECTILE_ROT_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_ROT_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ROT_ACTOR->unkEE = (s16)((G_PROJECTILE_ROT_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ROT_ACTOR->unkE6 = (s16)G_PROJECTILE_ROT_ACTOR->unkEE;
        G_PROJECTILE_ROT_ACTOR->unkB8 = G_PROJECTILE_ROT_ACTOR->unk124->unk4;
        G_PROJECTILE_ROT_ACTOR->unkC0 = G_PROJECTILE_ROT_ACTOR->unk124->unk8;
        G_PROJECTILE_ROT_ACTOR->unk144 = 0x3C;
        temp_s2->unk0 = gGameFrameCounter;
        G_PROJECTILE_ROT_ACTOR->unk60 |= 0x01080000;
        G_PROJECTILE_ROT_ACTOR->unk16E = 0x3C;
        G_PROJECTILE_ROT_ACTOR->unk16F = 0x3C;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x404, 0.0f, 1.0f);
        temp_s2->unk8 = -(mathAtan2(G_PROJECTILE_ROT_ACTOR->unkC0, G_PROJECTILE_ROT_ACTOR->unkB8) * 57.295776f);
        temp_s2->unk10 = 0;
        temp_s2->unkC = (f32)((u32)(randomLcgNext() % 3600U) / 10U);
        temp_s2->unk13 = (u8)(u32)G_PROJECTILE_ROT_ACTOR->unk124->unk10;
        temp_s2->unk1C = 0;
    }
    sp84 = D_80750354;
    if (temp_s2->unk13 & 2) {
        var_a0 = 2;
        if (gPlayerCount >= 2) {
            var_a0 = 3;
        }
        projectileSteerTowardTarget(var_a0, gCurrentActor, 0, 0);
    }
    if (temp_s2->unk13 & 4) {
        sp84 = D_80750368;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    switch (G_PROJECTILE_ROT_ACTOR->unk154) {
    case 0:
        if (G_PROJECTILE_ROT_ACTOR->unkFD != 0 || (G_PROJECTILE_ROT_ACTOR->unk124->unk14 != 0.0f && (u32)(temp_s2->unk0 + 1) < gGameFrameCounter)) {
            scriptSetActorRampTarget(gCurrentActor, 0.5f, 0);
            controllerAnimSetStateIfChanged(gCurrentActor, 0x406, 0, 0.0f);
            G_PROJECTILE_ROT_ACTOR->unkB8 = 0.0f;
            G_PROJECTILE_ROT_ACTOR->unkC0 = 0.0f;
            G_PROJECTILE_ROT_ACTOR->unk154 = 1;
            temp_s2->unk10 = 0x3C;
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
        temp_s2->unk0 = gGameFrameCounter;
        if (!--temp_s2->unk10) {
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
        sp84 = (s32)((f32)sp84 * 1.4f);
    }
    if ((u32)(temp_s2->unk0 + sp84) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
    guRotateF((void *)((u8 *)gCurrentActor + 0xC), temp_s2->unkC, 0.0f, 0.0f, 1.0f);
    guRotateF(sp44, temp_s2->unk8, 1.0f, 0.0f, 0.0f);
    guMtxCatF((void *)((u8 *)gCurrentActor + 0xC), sp44, (void *)((u8 *)gCurrentActor + 0xC));
    actorUpdateModelMatrix(gCurrentActor, 1);
}

extern u8 D_8072006C;
void effectSpawnBoneWhite(Actor *, s16, f32, f32, f32, f32, s32);
void lightSetFlags(s32);

void projectileRotatingLightUpdate(f32 arg0, u8 arg1) {
    ProjectileRotActorExtra *temp_s2;
    ActorSub4 *temp_v0;
    u8 sp97;
    u8 sp96;
    u8 sp95;
    f32 sp4C[4][4];
    s32 sp48;

    temp_s2 = G_PROJECTILE_ROT_ACTOR->unk174;
    if (!(G_PROJECTILE_ROT_ACTOR->unk60 & 0x10)) {
        if (arg1 == 1) {
            sfxPlayAtPositionPooled(G_PROJECTILE_ROT_ACTOR->unk7C, G_PROJECTILE_ROT_ACTOR->unk80, G_PROJECTILE_ROT_ACTOR->unk84, 0x306, 0xFF, 0x7F, 0, 0, 0.3f, 0);
        }
        G_PROJECTILE_ROT_ACTOR->unk6A &= 0xFFFE;
        G_PROJECTILE_ROT_ACTOR->unkEE = (s16)((G_PROJECTILE_ROT_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_ROT_ACTOR->unkE6 = G_PROJECTILE_ROT_ACTOR->unkEE;
        G_PROJECTILE_ROT_ACTOR->unkB8 = G_PROJECTILE_ROT_ACTOR->unk124->unk4;
        G_PROJECTILE_ROT_ACTOR->unkC0 = G_PROJECTILE_ROT_ACTOR->unk124->unk8;
        G_PROJECTILE_ROT_ACTOR->unk132 = (u8)(u32)G_PROJECTILE_ROT_ACTOR->unk124->unk10;
        temp_v0 = G_PROJECTILE_ROT_ACTOR->unk4;
        temp_v0->scaleX = 2.0 * temp_v0->scaleX;
        temp_v0 = G_PROJECTILE_ROT_ACTOR->unk4;
        temp_v0->scaleY = 2.0 * temp_v0->scaleY;
        temp_v0 = G_PROJECTILE_ROT_ACTOR->unk4;
        temp_v0->scaleZ = 2.0 * temp_v0->scaleZ;
        temp_s2->unk8 = -(mathAtan2(G_PROJECTILE_ROT_ACTOR->unkC0, G_PROJECTILE_ROT_ACTOR->unkB8) * 57.295776f);
        G_PROJECTILE_ROT_ACTOR->unk144 = 0x3C;
        temp_s2->unk0 = gGameFrameCounter;
        temp_s2->unk12 = 0;
        G_PROJECTILE_ROT_ACTOR->unk60 |= 0x80000;
        temp_s2->unk10 = 0;
    }
    sp48 = arg1;
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, arg0);
    if (sp48 != 0) {
        if (sp48 == 1) {
            sp97 = 0xFF;
            sp96 = 0;
            sp95 = 0;
        }
    } else {
        sp97 = 0xFF;
        sp96 = 0xFF;
        sp95 = 0xFF;
    }
    lightSetFlags(1);
    lightAdd(G_PROJECTILE_ROT_ACTOR->unk7C, G_PROJECTILE_ROT_ACTOR->unk80, *(s32 *)&G_PROJECTILE_ROT_ACTOR->unk84, 0.0f, 0.0f, 0.0f, 80.0f, 0, sp97, sp96, sp95);
    if (sp48 == 1) {
        if (!temp_s2->unk12 && ((G_PROJECTILE_ROT_ACTOR->unk6A & 1) || G_PROJECTILE_ROT_ACTOR->unkFD != 0 || D_807FBB85 != 0)) {
            effectSetSpeed(0x1006E);
            effectSetCallback(effectLightPulseOscillate);
            effectCreateAtPosition(&D_8072006C, 1.2f, G_PROJECTILE_ROT_ACTOR->unk7C, G_PROJECTILE_ROT_ACTOR->unk80, G_PROJECTILE_ROT_ACTOR->unk84);
            effectSpawnBoneWhite(0, 0, 0.8f, G_PROJECTILE_ROT_ACTOR->unk7C, G_PROJECTILE_ROT_ACTOR->unk80, G_PROJECTILE_ROT_ACTOR->unk84, -0x50);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF6, 0xFF, 0x3F, 0x14);
            temp_s2->unk12 = 2;
        } else if (temp_s2->unk12) {
            if (--temp_s2->unk12 == 0) {
                actorDespawn(gCurrentActor);
            }
        }
        if ((u32)(temp_s2->unk0 + D_80750344) < gGameFrameCounter) {
            actorDespawn(gCurrentActor);
        }
    }
}

void actorApplyTransformAndRender(void) {
    ProjectileRotSub174 *sp1C;

    sp1C = gCurrentActor->customState;
    projectileRotatingLightUpdate(0.0f, 1);
    matrixMakeRotationX((u8 *)gCurrentActor + 0xC, sp1C->unk8);
    actorUpdateModelMatrix(gCurrentActor, 1);
}

extern u8 D_8071FBC8;
extern u8 D_8071FC40;
extern u8 D_80720804;
void effectProjectileDriftUpdate(void);

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
    ProjectileBeamActorExtra *sp54;
    s32 var_s0;
    sp54 = (ProjectileBeamActorExtra *)G_PROJECTILE_PARTICLE_ACTOR->unk174;
    if (!(G_PROJECTILE_PARTICLE_ACTOR->unk60 & 0x10)) {
        G_PROJECTILE_PARTICLE_ACTOR->unkFA = 0x270F;
        G_PROJECTILE_PARTICLE_ACTOR->unk6E = -2;
        G_PROJECTILE_PARTICLE_ACTOR->unk6A &= -2;
        G_PROJECTILE_PARTICLE_ACTOR->unkEE = (s16)((G_PROJECTILE_PARTICLE_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_PROJECTILE_PARTICLE_ACTOR->unkB8 = G_PROJECTILE_PARTICLE_ACTOR->unk124->unk4;
        G_PROJECTILE_PARTICLE_ACTOR->unkC0 = G_PROJECTILE_PARTICLE_ACTOR->unk124->unk8;
        sp54->unk13 = (u8)(u32)G_PROJECTILE_PARTICLE_ACTOR->unk124->unk10;
        G_PROJECTILE_PARTICLE_ACTOR->unk144 = 0x3C;
        actorSetCollisionRadius(gCurrentActor, 110.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 100.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectCreateAtActorBone(&D_80720804, G_PROJECTILE_PARTICLE_ACTOR->unk124->unkC, gCurrentActor, 1, 2);
        sp54->unk0 = gGameFrameCounter;
        G_PROJECTILE_PARTICLE_ACTOR->unk60 |= 0x80000;
        if (sp54->unk13 != 0xA) {
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
    if (((G_PROJECTILE_PARTICLE_ACTOR->hasArcBounds != 0) && ((u32)(gGameFrameCounter - sp54->unk0) >= 6)) || D_807FBB85 != 0) {
        if ((D_807FBB85 != 0) && (sp54->unk13 != 0xA)) {
            effectSetDepth(1);
            effectSetSpeed(0x100D2);
            effectSetCallback(effectLightPulseOscillate);
            effectCreateAtPosition(&D_80720120, 2.0f, gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z);
            camStartShakeFromPoint(((PlayerTrackActor *)gPrimaryPlayerActor)->unk174->unk104, 7, 0x16, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
            actorSpawnSparkleBurst();
            for (var_s0 = 0; var_s0 != 12; var_s0 += 2) {
                effectSetDepth(1);
                effectSetSpeed(0x0B000000 + var_s0);
                effectSetCallback(effectRadialSprayUpdate);
                effectCreateAtPosition(&D_807206DC, 0.35f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
        }
        if (sp54->unk13 != 0xA) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3C, 0xFF, 0x7F, 0x1E);
        }
        actorDespawn(gCurrentActor);
    }
    if ((u32)(sp54->unk0 + D_80750344) < gGameFrameCounter) {
        actorDespawn(gCurrentActor);
    }
}

extern f32 D_80750274;
void effectSetAngle(s16);

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
    u32 *sp74;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fv0;
    s32 var_s1;

    sp74 = (u32 *)G_PROJECTILE_HOMING_ACTOR->unk174;
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
        *sp74 = gGameFrameCounter;
        G_PROJECTILE_HOMING_ACTOR->unk60 |= 0x80000;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 4.0f);
    G_PROJECTILE_HOMING_ACTOR->unkC0 += D_80750274;
    temp_fv0 = (f32)D_807502D0;
    if (G_PROJECTILE_HOMING_ACTOR->unkC0 < temp_fv0) {
        G_PROJECTILE_HOMING_ACTOR->unkC0 = temp_fv0;
    }
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 14, 14, 1, 150, 120, 0, 1.0f);
    var_s1 = 0;
    if ((G_PROJECTILE_HOMING_ACTOR->unk6A & 1) || ((G_PROJECTILE_HOMING_ACTOR->hasArcBounds != 0) && ((u32)(gGameFrameCounter - *sp74) >= 6)) || D_807FBB85 != 0) {
        do {
            temp_fs2 = ((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0;
            temp_fs3 = ((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0;
            temp_fs4 = ((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0;
            effectSetAngle(var_s1);
            effectSetDepth(1);
            if (var_s1 == 0) {
                effectSetSpeed(0x1006E);
                effectSetCallback(effectLightPulseOscillate);
            } else {
                effectSetCallback(func_80717D4C);
                effectSetSpeed(-150 - ((randomNonNegative() >> 15) % 50));
            }
            effectCreateAtPosition(&D_80720340, 1.6f, gCurrentActor->x + temp_fs2, gCurrentActor->y + temp_fs3, gCurrentActor->z + temp_fs4);
            var_s1 += 2;
        } while (var_s1 != 16);
        camStartShake(gCamActor, 20, 15);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x3C, 0xFF, 0x7F, 0x1E);
        actorDespawn(gCurrentActor);
    }
    if ((u32)(*sp74 + D_80750344) < gGameFrameCounter) {
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
void collisionQueryActorFloor(Actor *, u8 *, f32 *, u8 *, void *, s32);
void collisionSetQueryMode(s32);
void effectSpawnScatterRandom(void *, s32, f32, s32, s32, s32, s32, s32, s32);

void projectileFallBounceUpdate(void) {
    u32 *temp_v0;
    s16 i;
    u8 sp79;
    u8 sp78;
    u8 sp77;
    f32 sp70;
    f32 sp6C;
    s32 flag;
    f64 var_fv1;
    PlayerStateTrackView *sub;
    u8 temp_v1_2;
    f64 temp_fv0_2;
    f32 temp_fv0;

    temp_v0 = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        temp_fv0 = gCurrentActor->y;
        gCurrentActor->peakY = temp_fv0;
        gCurrentActor->prevPeakY = temp_fv0;
        if (gGlobalOverlayFlags & 0x80000) {
            gCurrentActor->unk144 = 0x3C;
        } else {
            gCurrentActor->unk144 = 0x1C;
        }
        *temp_v0 = gGameFrameCounter;
        gCurrentActor->flags |= 0x80000;
        collisionQueryActorFloor(gCurrentActor, &sp79, &sp70, &sp78, &sp6C, sp77);
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
            flag = gCurrentActor->contactFlags & 1;
            if (flag != 0 && !(gCurrentActor->prevContactFlags & 1)) {
                temp_v1_2 = gCurrentActor->unk155[0];
                if (temp_v1_2 < 2) {
                    gCurrentActor->unk155[0] = temp_v1_2 + 1;
                    gCurrentActor->speedY = (f32)((f64)(gCurrentActor->prevPeakY - gCurrentActor->y) * 1.5);
                    camStartShake(((CameraShakeTargetView *)gActivePlayerState)->unk104, 0xA, 0x14);
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1C1, 0xFF, 0x7F, 0x1E);
                    effectSpawnScatterRandom(&sEffectSparkConfig, 0, 1.0f, 4, 0x14, 0x96, (s32)gCurrentActor->x, (s32)gCurrentActor->y, (s32)gCurrentActor->z);
                    flag = gCurrentActor->contactFlags & 1;
                }
            }
            if (flag == 0) {
                temp_fv0_2 = (f64)gCurrentActor->speedY * 0.5;
                if (temp_fv0_2 > 0.0) {
                    var_fv1 = temp_fv0_2;
                } else {
                    var_fv1 = -temp_fv0_2;
                }
                gCurrentActor->roll = (s16)(s32)((f64)gCurrentActor->roll - var_fv1);
            }
            gCurrentActor->speedY = gCurrentActor->speedY + gCurrentActor->accelY;
            temp_fv0 = (f32)D_807502D0;
            if (gCurrentActor->speedY < temp_fv0) {
                gCurrentActor->speedY = temp_fv0;
            }
        }
        temp_fv0 = gCurrentActor->sub4->scaleY * 300.0f;
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, (s16)(s32)temp_fv0, (s16)(s32)temp_fv0, 1, 0x96, 0x96, 0, 1.0f);
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

void tagBarrelSpawnActorSmokePuffs(s32, s32);
void actorSetUniformScale(Actor *, f32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
void effectFollowParentUpdate(void);

void projectileChaseTargetUpdate(void) {
    ProjectileChaseState *sp44;
    s16 temp_v0;
    s16 sp40;

    sp44 = CHASE_ACTOR->unk174;
    projectileRotatingLightUpdate(15.0f, 0);
    if (gCurrentMap == 0x6F) {
        if (CHASE_ACTOR->unk80 < CHASE_ACTOR->unkAC) {
            CHASE_ACTOR->unk80 = CHASE_ACTOR->unkAC;
            CHASE_ACTOR->unkC0 = CHASE_ACTOR->unkC4;
        }
    }
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 100, 100, 1, 0x4B, 0x78, 0, 1.0f);
    if (!(CHASE_ACTOR->unk60 & 0x10)) {
        sp44->unk18 = (s32)CHASE_ACTOR->unkB8;
        CHASE_ACTOR->unk12A = 1000;
        CHASE_ACTOR->unk60 |= 0x400;
        sp44->unk0 += 0x78;
        if (CHASE_ACTOR->unk6E == -1) {
            sfxPlayActorSound(gCurrentActor, 0x114, 0x1E, 1, 0, 0xFF, 1.0f, 0);
            D_80770B68[D_80770628[CHASE_ACTOR->unk6E]] = 0.75f;
            D_80770BC0[D_80770628[CHASE_ACTOR->unk6E]] = 1.0f;
        }
        sp44->unk10 = 0xF;
        sp44->unk11 = 0;
        actorSetUniformScale(gCurrentActor, (f64)CHASE_ACTOR->unk124->unkC * 0.15);
    }
    sp44->unk11++;
    if (sp44->unk10 < sp44->unk11) {
        sfxPlayAtPositionPooled(CHASE_ACTOR->unk7C, CHASE_ACTOR->unk80, CHASE_ACTOR->unk84, 0x15B, 0xFF, 0x6E, 0, 0x1E, 0.3f, 0);
        sp44->unk11 = 0;
        if (sp44->unk10 >= 3) {
            sp44->unk10--;
            if (gCurrentMap && gCurrentMap) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
    }
    if ((u32)(sp44->unk0 - 100) < gGameFrameCounter) {
        CHASE_ACTOR->unk60 &= ~0x80000;
    }
    if (((u32)(sp44->unk0 + D_80750344) < gGameFrameCounter) || ((CHASE_ACTOR->unkFD != 0) && (CHASE_ACTOR->unk58 != 0xA9)) || (D_807FBB85 != 0)) {
        tagBarrelSpawnActorSmokePuffs(0, 1);
        sfxStopSlotSound(gCurrentActor, 0);
        actorDespawn(gCurrentActor);
        if ((CHASE_ACTOR->unk11C != NULL) && (CHASE_ACTOR->unk11C->unk58 == 0xB9) && (CHASE_ACTOR->unk11C->unk154 != 0x37)) {
            if (gCurrentMap && gCurrentMap) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            CHASE_ACTOR->unk11C->unk155++;
        }
    }
    temp_v0 = mathAngleBetweenPoints2D(CHASE_TARGET->unk7C, CHASE_TARGET->unk84, CHASE_ACTOR->unk7C, CHASE_ACTOR->unk84);
    if (temp_v0 < CHASE_ACTOR->unkE6) {
        sp40 = CHASE_ACTOR->unkE6 - temp_v0;
    } else {
        sp40 = temp_v0 - CHASE_ACTOR->unkE6;
    }
    CHASE_ACTOR->unkE6 = mathAngleEaseToward(CHASE_ACTOR->unkE6, temp_v0, 10.0f);
    switch (CHASE_ACTOR->unk154) {
    case 0:
        if (sp40 > 1000) {
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
        if (CHASE_ACTOR->unkB8 + 20.0f < sp44->unk18) {
            CHASE_ACTOR->unkB8 += 20.0f;
        } else {
            CHASE_ACTOR->unkB8 = sp44->unk18;
        }
        CHASE_ACTOR->unkEE = mathAngleEaseToward(CHASE_ACTOR->unkEE, CHASE_ACTOR->unkE6, 1.0f);
        CHASE_ACTOR->unkF0 = mathAngleEaseToward(CHASE_ACTOR->unkF0, (s16)(s32)(((f64)mathCalculatePitchAngle(CHASE_TARGET->unk7C, CHASE_TARGET->unk80 + (f32)(u32)CHASE_TARGET->unk15E, CHASE_TARGET->unk84, CHASE_ACTOR->unk7C, CHASE_ACTOR->unk80, CHASE_ACTOR->unk84, 20) * 2048.0) / 3.1415927410125732), 30.0f);
        CHASE_ACTOR->unkC0 = mathSinF(CHASE_ACTOR->unkF0) * -CHASE_ACTOR->unkB8;
        sp44->unk8 = -(mathAtan2(CHASE_ACTOR->unkC0, CHASE_ACTOR->unkB8) * 57.295776f);
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


void projectileChaseTargetUpdate(void);

void projectileChaseReflectUpdate(void) {
    s16 temp_v0;
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
    temp_v0 = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax);
    t = gCurrentActor->moveYaw;
    t = (t + 0x800) & 0xFFF;
    gCurrentActor->moveYaw = temp_v0 + (s16)(temp_v0 - t);
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
