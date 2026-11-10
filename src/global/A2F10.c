#include "common.h"
#include "actor.h"
#define PROTO_SKIP_actorAppendCallbackPayloadA70C // FAKE: callee prototype steer
#define PROTO_SKIP_actorDespawn // FAKE: callee prototype steer
#define PROTO_SKIP_actorSpawnNodeEntryScaled // FAKE: callee prototype steer
#define PROTO_SKIP_actorTableContains // PROTO: Type Actor *  of this argument  is incompatible with type vo
#define PROTO_SKIP_animGetNodeByIndex // PROTO: 'unkC' undefined; reoccurrences will not be reported.
#define PROTO_SKIP_playerStateQueueCallback // FAKE: callee prototype steer
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/103AB0.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/684C0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/8CA50.h"
#include "proto/global/8D3E0.h"
#include "proto/global/90D80.h"
#include "proto/global/A2F10.h"
#include "proto/global/AA960.h"
#include "proto/global/EFDC0.h"

typedef struct ActorTail {
    /* 0x000 */ u8 pad0[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x58];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ u8 padE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x6F];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
} ActorTail;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;
extern u16 gActiveActorCount;
extern ActorEntry gActiveActors[];

void actorSpawnNodeEntryScaled(s16, s32, s32, s32, s16, u8, s16, s32); // FAKE: callee prototype steer
void actorAppendCallbackPayloadA70C(Actor *, Actor *, s32, f32, f32, s32, s32); // FAKE: callee prototype steer

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern u32 gFrameDelta;
extern u8 D_80750AD4;
s32 actorDespawn(Actor *); // FAKE: callee prototype steer

#define WRITE_GFX(pkt, _w0, _w1)                                               \
    {                                                                          \
        Gfx *_g = (Gfx *)(pkt);                                                \
        _g->words.w0 = (_w0);                                                  \
        _g->words.w1 = (_w1);                                                  \
    }

typedef struct ActorSub4Head {
    /* 0x00 */ void *unk0;
} ActorSub4Head;

typedef struct ActorSub4Node {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} ActorSub4Node;


void actorTriggerRampWithSfx(void) {
    Actor *actor;
    Actor **p;
    s16 i;
    s16 *event;
    u32 flags;

    actor = gCurrentActor;
    p = &gCurrentActor;
    if (!(actor->flags & 0x10)) {
        actor->flags &= ~4;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x407, 0.0f, 0.0f);
        scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
        actor = gCurrentActor;
    }
    for (i = 0; i < gActorGlobalState.unk254; i++) {
        event = gActorGlobalState.unk278[i];
        if (*event == 0) {
            flags = actor->flags;
            actor->flags = flags | 4;
            controllerAnimSetState(gCurrentActor, 0x407, 0.0f, 0.0f);
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
            switch (actorListFindIdByActor(gCurrentActor)) {
            case 5:
                sfxPlayOnFreeSlot(0x1D7, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            case 6:
                sfxPlayOnFreeSlot(0x1D8, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            case 7:
                sfxPlayOnFreeSlot(0x1D9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                break;
            case 8:
                sfxPlayOnFreeSlot(0x1DA, 0x7FFF, 63.0f, 1.0f, 2, 0);
                break;
            case 9:
                sfxPlayOnFreeSlot(0x1DB, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            case 10:
                sfxPlayOnFreeSlot(0x1DC, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            }
            actor = gCurrentActor;
        }
    }
    if (0.0f == ((ActorSub4Node *)((ActorSub4Head *)actor->sub4)->unk0)->unk24) {
        actor->flags &= ~4;
        actor = *p;
    }
    actorUpdateModelMatrix(actor, 0);
}

void actorSpawnNodeEntryAtActor(s32 arg0, s16 arg1) {
    Actor *actor;

    actor = gCurrentActor;
    actorSpawnNodeEntryScaled(arg0, *(s32 *)&actor->x, *(s32 *)&actor->y,
                  *(s32 *)&actor->z, 0, 0, arg1, (s32)actor);
}

void actorPlaceAttachedChildren(s16 arg0) {
    Actor *actor;
    s16 i;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if ((s32)actor->parentActor == (s32)gCurrentActor) {
            actorAppendCallbackPayloadA70C(gCurrentActor, actor, *(s32 *)&gCurrentActor->x,
                          gCurrentActor->y + (f32)arg0, gCurrentActor->z, 2,
                          1);
        }
    }
}

void actorAttachChildCallbacks(void) {
    Actor *actor;
    s16 i;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if ((s32)actor->parentActor == (s32)gCurrentActor) {
            actorAppendCallback(actor, (s32)gCurrentActor, 0x2000000, 1, 0, NULL);
        }
    }
}

int actorIsTargetInRange(Actor *arg0, f32 arg1, f32 arg2) {
    return arg0->y - 8.0f <= gCurrentActor->y &&
           gCurrentActor->y < arg0->y + arg1 &&
           arg2 > (arg0->x - gCurrentActor->x) *
                      (arg0->x - gCurrentActor->x) +
                  (arg0->z - gCurrentActor->z) *
                      (arg0->z - gCurrentActor->z) &&
           arg0->unk144 != 1;
}

s32 func_8069E724(s32 arg0) {
    switch (arg0 - 2) {
    case 0:
        return 0xB;
    case 1:
        return 0xE;
    case 3:
    case 4:
    case 5:
        return 0xA;
    case 2:
        return 0xD;
    }
    return 0;
}

typedef struct ActorState174 {
    /* 0x000 */ f32 unk0;
    /* 0x004 */ u8 pad4[8];
    /* 0x00C */ u16 unkC;
    /* 0x00E */ u8 padE[2];
    /* 0x010 */ u8 unk10;
    /* 0x011 */ u8 unk11;
    /* 0x012 */ u8 unk12;
    /* 0x013 */ u8 pad13[0xF1];
    /* 0x104 */ void *unk104;
    /* 0x108 */ u8 pad108[0x9C];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x4B];
    /* 0x1F0 */ u32 unk1F0;
} ActorState174;

typedef struct PlayerSlotView {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ Actor *actor;
    /* 0x008 */ u8 pad8[0x2E8];
} PlayerSlotView;

typedef struct ActorHeadingView {
    /* 0x000 */ u8 pad0[0xEE];
    /* 0x0EE */ s16 unkEE;
} ActorHeadingView;

typedef struct ActorF64View160 {
    /* 0x000 */ u8 pad0[0x160];
    /* 0x160 */ f64 unk160;
} ActorF64View160;

extern u8 gSplitScreenMode;
extern s32 gCurrentMap;
extern u8 gPlayerCount;
extern PlayerSlotView *gPlayerSlots;

f32 mathSinF(s16);
void playerStateQueueCallback(s32, void *, s32); // FAKE: callee prototype steer

void func_8069E774(void) {
    u16 sp8E;
    f32 sp88;
    u8 sp87;
    ActorState174 *sp80;
    u8 sp7F[4]; // FAKE: flag kept in memory (array) so its loads are not CSE'd into the loop; element 3 = byte 0x7F
    Actor *sp78;
    u32 *sp74;
    ActorState174 *node;
    Actor *temp_v0;
    f32 sp68;
    s32 padB1;
    s32 sp60;
    s32 i;
    Actor *target;

    sp8E = 0x12C;
    sp87 = 0;
    sp7F[3] = 0;
    temp_v0 = (Actor *)gCurrentActor->parentActor;
    node = (ActorState174 *)gCurrentActor->customState;
    if (temp_v0 != NULL && (temp_v0->collisionFlags & 1)) {
        sp78 = temp_v0;
        sp7F[3] = 1;
    } else {
        sp78 = gPrimaryPlayerActor;
    }
    sp80 = (ActorState174 *)sp78->customState;
    if (gPlayerCount >= 2 && gSplitScreenMode == 1) {
        temp_v0 = (Actor *)gPrimaryPlayerActor->customState;
        sp74 = &((ActorState174 *)temp_v0)->unk1F0;
    } else {
        sp74 = &sp80->unk1F0;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        node->unkC = (u16)sp78->collision->radius;
        gCurrentActor->drawDistance = 0x3E8;
        gCurrentActor->flags |= 0x400;
        animSetLoopLimit(gCurrentActor, 0, 1);
        animSetSpeed(gCurrentActor, 0, 1.0f);
        animSetFinished(gCurrentActor, 0, 1);
        *sp74 |= 0x02000000;
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        switch (controllerLookupStateByHash(gCurrentActor)) {
        case 0xAD:
            node->unk10 = 0xFF;
            node->unk11 = 0xFF;
            node->unk12 = 0x32;
            break;
        case 0xAE:
            node->unk10 = 0xFF;
            node->unk11 = 0x32;
            node->unk12 = 0x32;
            break;
        case 0xD1:
            node->unk10 = 0xCA;
            node->unk11 = 0x5B;
            node->unk12 = 0xFF;
            break;
        case 0xD0:
            node->unk10 = 0;
            node->unk11 = 0x96;
            node->unk12 = 0xFF;
            break;
        case 0xCF:
            node->unk10 = 0x32;
            node->unk11 = 0xFF;
            node->unk12 = 0x32;
            break;
        }
        if (sp7F[3] != 0) {
            node->unk0 = 2.0f;
        } else {
            node->unk0 = 1.5f;
        }
        if (gCurrentActor->unk15F != 0) {
            actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 1.0f, 0);
        }
    }
    if (camIsCutsceneActive() != 0) {
        camStartShake(sp80->unk104, 0xA, 0xA);
    }
    gCurrentActor->sub4->scaleX =
        gCurrentActor->sub4->scaleX * ((ActorF64View160 *)gCurrentActor)->unk160;
    gCurrentActor->sub4->scaleZ = gCurrentActor->sub4->scaleX;
    gCurrentActor->sub4->scaleY = gCurrentActor->sub4->scaleY * 1.04;
    sp68 = mathSinF(((ActorHeadingView *)gCurrentActor)->unkEE);
    gCurrentActor->sub4->scaleY = gCurrentActor->sub4->scaleY + 0.01 * (f64)sp68;
    ((ActorHeadingView *)gCurrentActor)->unkEE += 0x1F4;
    gCurrentActor->yaw += 0x32;
    gCurrentActor->state++;
    if (gCurrentActor->state == gCurrentActor->yawSpeed) {
        animSetFinished(gCurrentActor, 0, 0);
    } else if (gCurrentActor->yawSpeed < gCurrentActor->state) {
        sp8E = 0x12C - (gCurrentActor->state - gCurrentActor->yawSpeed) * 0x28;
        if (animIsPlaying(gCurrentActor, 0) == 0) {
            sp87 = 1;
            *sp74 &= 0xFDFFFFFF;
            actorSetCollisionRadius(sp78, (f32)node->unkC);
            actorGetOrSetNodeScale(sp78, func_8069E724(sp78->actorType), 0.0f);
            actorDespawn(gCurrentActor);
        }
    }
    lightSetFlags(1);
    lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f,
             0.0f, 0.0f, gCurrentActor->sub4->scaleX * (f32)sp8E * node->unk0, 0,
             node->unk10, node->unk11, node->unk12);
    if (gCurrentMap != 0x4C) {
        if (sp7F[3] == 0 || gCurrentActor->unk15F != 0) {
            sp60 = 0x2E;
            if (func_80714608(0) != 0) {
                sp60 = 0xE;
            }
            sp88 = gCurrentActor->sub4->scaleX * (f32)sp8E;
            sp88 = sp88 * sp88;
            for (i = 0; i < gPlayerCount; i++) {
                target = gPlayerSlots[i].actor;
                if (sp7F[3] == 0 ||
                    (i != sp80->unk1A4 && target->state != 0x84)) {
                    if (actorIsTargetInRange(target, (f32)target->eyeHeight, sp88) !=
                        0) {
                        playerStateQueueCallback((s16)sp60, gCurrentActor, i & 0xFF);
                    }
                    if (gPlayerCount && gPlayerCount) {}  // FAKE: steers uopt to PRE-reload the loop count
                }
            }
            if (gCurrentActor->unk15F != 0) {
                actorSetCollisionRadius(
                    gCurrentActor,
                    (f32)(2.0 * ((f64)(gCurrentActor->sub4->scaleX * (f32)sp8E) *
                                 6.66666667)));
                actorGetOrSetNodeScale(
                    gCurrentActor, 1,
                    (f32)((f64)(gCurrentActor->sub4->scaleX * (f32)sp8E) *
                          6.66666667));
            }
        } else if (sp87 == 0) {
            actorSetCollisionRadius((Actor *)gCurrentActor->parentActor,
                          (f32)(2.0 * ((f64)(gCurrentActor->sub4->scaleX * (f32)sp8E) *
                                       6.66666667)));
            actorGetOrSetNodeScale(
                (Actor *)gCurrentActor->parentActor, func_8069E724(sp78->actorType),
                (f32)((f64)(gCurrentActor->sub4->scaleX * (f32)sp8E) * 6.66666667));
            actorOrNodeFlags(sp78, func_8069E724(sp78->actorType), 3);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


s32 actorIsTargetInCylinder(s16 arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4) {
    Actor *actor;
    f32 dx;
    f32 dz;

    actor = gPrimaryPlayerActor;
    dx = actor->x - arg0;
    dz = actor->z - arg2;
    if (dx * dx + dz * dz < arg4 * arg4 && arg1 <= actor->y &&
        actor->y < arg1 + arg3) {
        return 1;
    }
    return 0;
}

typedef struct ModelNodeView {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 padE[0x16];
    /* 0x24 */ f32 unk24;
} ModelNodeView;

typedef struct ModelSubView {
    /* 0x00 */ ModelNodeView *unk0;
    /* 0x04 */ u8 pad4[0x30];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ u8 pad40[0x8];
    /* 0x48 */ f32 unk48;
} ModelSubView;

typedef struct ActorView {
    /* 0x000 */ u8 pad0[0x4];
    /* 0x004 */ ModelSubView *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x66];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x38];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x28];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0xA];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
} ActorView;

ModelNodeView *animGetNodeByIndex(void *, s32);
extern u8 gGameMode;
extern s32 gGlobalCutsceneFlags;

#define CUR_ACTOR ((ActorView *)gCurrentActor)
#define SPAWNED_ACTOR ((ActorView *)gSpawnedActor)

void actorShockwaveUpdate(void) {
    u8 sp67;
    u16 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;

    sp67 = (CUR_ACTOR->unkF0 == 0xBB) ? 0x28 : 0x23;
    sp64 = (CUR_ACTOR->unkF0 == 0x6A) ? 0x78 : 0x190;
    if (gGameMode == 1) {
        actorDespawn((Actor *)gCurrentActor);
    }
    if (!(CUR_ACTOR->unk60 & 0x10)) {
        CUR_ACTOR->unk12A = 0x3E8;
        CUR_ACTOR->unk60 |= 0x400;
        animSetLoopLimit(gCurrentActor, 0, 1);
        animSetSpeed(gCurrentActor, 0, 0.5f);
        animSetFinished(gCurrentActor, 0, 1);
        CUR_ACTOR->unkEE = 0x3C;
    }
    if (CUR_ACTOR->unk168 != 0) {
        sp60 = 1.0f;
        if (CUR_ACTOR->unkEE < 0x1E) {
            sp60 = CUR_ACTOR->unkEE / 30.0;
        }
        lightSetFlags(1);
        lightAdd(CUR_ACTOR->unk7C, CUR_ACTOR->unk80, CUR_ACTOR->unk84, 0.0f, 0.0f, 0.0f,
                 CUR_ACTOR->unk4->unk34 * 300.0f, 0,
                 (u32)((f32)CUR_ACTOR->unk16A * sp60),
                 (u32)((f32)CUR_ACTOR->unk16B * sp60),
                 (u32)((f32)CUR_ACTOR->unk16C * sp60));
        CUR_ACTOR->unk4->unk34 = (f32)((f64)CUR_ACTOR->unk4->unk34 * CUR_ACTOR->unk160);
        CUR_ACTOR->unk4->unk3C = (f32)((f64)CUR_ACTOR->unk4->unk3C * CUR_ACTOR->unk160);
    }
    switch (CUR_ACTOR->unk154) {
    case 0:
        if (CUR_ACTOR->unk168 == 0) {
            CUR_ACTOR->unk4->unk34 =
                (f32)((f64)CUR_ACTOR->unk4->unk34 * CUR_ACTOR->unk160);
            CUR_ACTOR->unk4->unk3C =
                (f32)((f64)CUR_ACTOR->unk4->unk3C * CUR_ACTOR->unk160);
        }
        if (CUR_ACTOR->unk4->unk0->unk24 == 0.0f ||
            CUR_ACTOR->unk4->unk0->unk4 > 5.0f) {
            CUR_ACTOR->unk154 = 1;
            animSetFinished(gCurrentActor, 0, 0);
        }
        break;
    case 1:
        if ((CUR_ACTOR->unk4->unk0->unk24 == 0.0f && animGetNodeByIndex(CUR_ACTOR, 0)->unkC >= 0xE) ||
            CUR_ACTOR->unk4->unk0->unk4 > 9.0f) {
            CUR_ACTOR->unk154 = 2;
            if (CUR_ACTOR->unk15F != 0 && actorSpawn(0x102, CUR_ACTOR->unkF0) != 0) {
                if (CUR_ACTOR->unk4->unk0->unk4 > 9.0f) {
                    controllerAnimSetStateIfChanged(gSpawnedActor, 0x4F9, 0.0f, 0.0f);
                    scriptSetActorRampTarget(gSpawnedActor, CUR_ACTOR->unk4->unk48, 0.0f);
                }
                actorCopyPoseAndScale(gSpawnedActor, CUR_ACTOR, CUR_ACTOR->unk4->unk38);
                SPAWNED_ACTOR->unkF0 = CUR_ACTOR->unkF0;
                SPAWNED_ACTOR->unk4->unk34 = (f32)((f64)CUR_ACTOR->unk4->unk34 + 0.02);
                SPAWNED_ACTOR->unk4->unk3C = (f32)((f64)CUR_ACTOR->unk4->unk3C + 0.02);
                SPAWNED_ACTOR->unk15F = CUR_ACTOR->unk15F - 1;
                SPAWNED_ACTOR->unk160 = CUR_ACTOR->unk160;
            }
        }
        break;
    case 2:
        if (animIsPlaying(CUR_ACTOR, 0) == 0) {
            CUR_ACTOR->unk154 = 3;
            if (CUR_ACTOR->unk168 != 0) {
                CUR_ACTOR->unk60 &= ~4;
            } else {
                actorDespawn((Actor *)CUR_ACTOR);
            }
        }
        break;
    case 3:
        CUR_ACTOR->unkEE--;
        if (CUR_ACTOR->unkEE == 0) {
            actorDespawn((Actor *)CUR_ACTOR);
            break;
        }
    }
    if (CUR_ACTOR->unkF0 != 0x6A && !(gGlobalCutsceneFlags & 2)) {
        if ((CUR_ACTOR->unk60 & 4) && (CUR_ACTOR->unk60 & 0x10)) {
            sp50 = CUR_ACTOR->unk80;
            actorGetNodePos((Actor *)CUR_ACTOR, 1, &sp5C, &sp58, &sp54);
            sp58 += 50.0f;
            if (collisionCheckGroundAtPoint(sp5C, sp54, &sp58) != 0) {
                if (((sp58 < sp50) ? (sp50 - sp58) : (sp58 - sp50)) < 40.0f || !(CUR_ACTOR->unk60 & 0x10)) {
                    CUR_ACTOR->unk80 = sp58;
                }
            }
        }
    }
    if (CUR_ACTOR->unk168 == 0 || CUR_ACTOR->unk154 != 3) {
        if (actorIsTargetInCylinder((s16)CUR_ACTOR->unk7C, (s16)(CUR_ACTOR->unk80 - 20.0f),
                          (s16)CUR_ACTOR->unk84, sp67,
                          CUR_ACTOR->unk4->unk34 * (f32)sp64) != 0 &&
            actorIsTargetInCylinder((s16)CUR_ACTOR->unk7C, (s16)(CUR_ACTOR->unk80 - 20.0f),
                          (s16)CUR_ACTOR->unk84, sp67,
                          CUR_ACTOR->unk4->unk34 * (f32)(sp64 - 0x14)) == 0) {
            playerStateQueueCallback(0x2E, CUR_ACTOR, 0);
        }
    }
    actorUpdateModelMatrix(CUR_ACTOR, 0);
}

#undef SPAWNED_ACTOR

void renderScaledSprite(Gfx *arg0, Actor *arg1) {
    f32 scale;

    scale = ((ActorTail *)arg1)->unkE0;
    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(arg0++, 0xE200001C, 0x00504340);
    WRITE_GFX(arg0++, 0xDA380007, (u32)&D_20000C0);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xFA000000, (arg1->yaw & 0xFF) | 0xFFFFFF00);
    renderRotatedSprite(arg0, (u16)(arg1->unk15F + 0x61), 0, 2, 0x28, 0x33,
                  (s32)arg1->x, (s32)arg1->y, scale, scale, 0, 0.0f);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A410.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A418.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A420.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A428.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A430.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A438.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A440.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A444.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A2F10/D_8075A44C.s")

extern char *D_80750338[];

Gfx *actorBannerTextRender(Gfx *arg0, Actor *arg1) {
    f32 spFC;
    f32 spBC[4][4];
    f32 sp7C[4][4];
    void *sp78;
    char sp68[0x10];
    s16 sp66;
    u8 sp65;
    u8 sp64;
    s32 sp2C;
    f64 scale;
    s32 sel;

    if (((f64)((ActorTail *)arg1)->unkE0 - 2.0) < 0.01) {
        scale = 0.01;
    } else {
        scale = (f64)((ActorTail *)arg1)->unkE0 - 2.0;
    }
    spFC = (f32)(scale * 0.3);
    sp64 = 0;
    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xFA000000, (arg1->yaw & 0xFF) | 0xFFFFFF00);
    arg0 = func_8070068C(arg0);
    sp78 = heapAlloc(0x40);
    heapFreeDeferred(sp78);
    sp65 = 1;
    sel = arg1->unk15F;
    switch (sel ^ 0) { // FAKE: keeps the switch selector copy (v0) out of copy propagation
    case 0:
        _sprintf(sp68, "ROUND");
        break;
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
        sp64 = 1;
        _sprintf(sp68, D_80750338[sel]);
        break;
    default:
        if (sel & 0x80) {
            sp65 = 3;
            spFC = (f32)(4.0 - (f64)spFC);
            _sprintf(sp68, "%d", 0xA - (sel & 0x3F));
        } else if (sel & 0x40) {
            sp65 = 3;
            spFC = (f32)(4.0 - (f64)spFC);
            _sprintf(sp68, "%d", 8 - (sel & 0x3F));
        } else {
            _sprintf(sp68, "%d", sel);
        }
        break;
    }
    sp66 = textGetStringWidth(sp2C = sp65, sp68);
    if (sp64 != 0) {
        arg1->x = (f32)((0x140 - sp66) << 1);
    }
    guScaleF(spBC, spFC, spFC, 1.0f);
    guTranslateF(sp7C, (f32)((f64)arg1->x + 2.0 * (f64)sp66),
                 arg1->y * 4.0f, 0.0f);
    guMtxCatF(spBC, sp7C, spBC);
    guMtxF2L(spBC, (Mtx *)sp78);
    WRITE_GFX(arg0++, 0xDA380003, (u32)sp78);
    return textDrawStringVtx(arg0, (s16)sp2C, (s16)(sp66 * -2), 0, (u8 *)sp68, 0);
}
void actorUpdateBannerFade(void) {
    f32 ratio;
    s16 sp22;

    if (!(((ActorTail *)gCurrentActor)->unk60 & 0x10)) {
        ((ActorTail *)gCurrentActor)->unkEE =
            (s16)((ActorTail *)gCurrentActor)->unk160;
    }
    if ((f64)(u32)gFrameDelta * 0.5 < ((ActorTail *)gCurrentActor)->unk160) {
        ((ActorTail *)gCurrentActor)->unk160 -=
            (f64)(u32)gFrameDelta * 0.5;
        ratio = (f32)(((ActorTail *)gCurrentActor)->unk160 /
                      (f64)(f32)((ActorTail *)gCurrentActor)->unkEE);
        ((ActorTail *)gCurrentActor)->unkE0 =
            (f32)((f64)ratio * -8.0 + 12.0);
        ((ActorTail *)gCurrentActor)->unkE6 = (s16)(255.0f * ratio);
        if (((ActorTail *)gCurrentActor)->unk15F >= 0x14 &&
            ((ActorTail *)gCurrentActor)->unk15F < 0x1E) {
            renderCallbacksRegister(renderScaledSprite, gCurrentActor, 3);
        } else {
            renderCallbacksRegister(actorBannerTextRender, gCurrentActor, 3);
        }
        if (((ActorTail *)gCurrentActor)->unk15F == 0 &&
            (s16)(s32)((ActorTail *)gCurrentActor)->unk160 == 3) {
            actorSpawn(0x104, 0);
            ((ActorTail *)gSpawnedActor)->unk160 =
                (f64)((ActorTail *)gCurrentActor)->unkEE;
            ((ActorTail *)gSpawnedActor)->unk15F = D_80750AD4;
            ((ActorTail *)gSpawnedActor)->unk80 = 80.0f;
            ((ActorTail *)gSpawnedActor)->unk7C = 640.0f;
            sfxPlayOnFreeSlot((s16)(D_80750AD4 + 0x3F3), 0x7FFF, 63.0f, 1.0f, 0,
                          0);
            return;
        }
        if (((ActorTail *)gCurrentActor)->unk15F >= 0x1E &&
            ((ActorTail *)gCurrentActor)->unk15F < 0x25 &&
            (s16)(s32)((ActorTail *)gCurrentActor)->unk160 == 5) {
            actorSpawn(0x104, 0);
            ((ActorTail *)gSpawnedActor)->unk160 =
                (f64)((ActorTail *)gCurrentActor)->unkEE;
            if (((ActorTail *)gCurrentActor)->unk15F == 0x23) {
                ((ActorTail *)gSpawnedActor)->unk15F = 0x24;
            } else if (((ActorTail *)gCurrentActor)->unk15F == 0x24) {
                ((ActorTail *)gSpawnedActor)->unk15F = 0x25;
            } else {
                ((ActorTail *)gSpawnedActor)->unk15F = 0x26;
            }
            ((ActorTail *)gSpawnedActor)->unk80 = 80.0f;
            ((ActorTail *)gSpawnedActor)->unk7C = 500.0f;
        }
    } else {
        if ((((ActorTail *)gCurrentActor)->unk15F & 0xC0) != 0 &&
            (((ActorTail *)gCurrentActor)->unk15F & 0x3F) != 0) {
        sp22 = 0x3FC - (((ActorTail *)gCurrentActor)->unk15F & 0x3F);
        actorSpawn(0x104, 0);
        ((ActorTail *)gSpawnedActor)->unk160 =
            (f64)((ActorTail *)gCurrentActor)->unkEE;
        ((ActorTail *)gSpawnedActor)->unk15F =
            (((ActorTail *)gCurrentActor)->unk15F & 0xC0) +
            (((ActorTail *)gCurrentActor)->unk15F & 0x3F) - 1;
        if (((ActorTail *)gCurrentActor)->unk15F & 0x80) {
            sp22 += 2;
        }
        sfxPlayOnFreeSlot(sp22, 0x7FFF, 63.0f, 1.0f, 0, 0);
        ((ActorTail *)gSpawnedActor)->unk80 = 80.0f;
        ((ActorTail *)gSpawnedActor)->unk7C = 600.0f;
        }
        actorDespawn(gCurrentActor);
    }
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} NodeQuad;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Position3f;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    /* 0x00C */ s16 unkC;
    /* 0x00E */ u8 unkE;
    /* 0x00F */ u8 unkF;
    u8 pad10[0x1F0];
    s16 unk200;
} SubStateView;

typedef struct {
    /* 0x000 */ struct ActorModel *unk0;
    /* 0x004 */ struct ActorSub4View *unk4;
    /* 0x008 */ void *unk8;
    /* 0x00C */ u8 padC[0x50];
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 pad5E[2];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x6];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ u8 padAC[0xC];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ f32 unkBC;
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x20];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0xC];
    /* 0x0FC */ u8 unkFC;
    /* 0x0FD */ u8 padFD[0x1F];
    /* 0x11C */ struct SiblingActor *unk11C;
    /* 0x120 */ u8 pad120[4];
    /* 0x124 */ Position3f *unk124;
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[6];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[0x10];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[1];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xC];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0xA];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
    /* 0x16D */ u8 pad16D[7];
    /* 0x174 */ SubStateView *unk174;
} AttachedActor;

typedef struct ActorSub4View {
    /* 0x000 */ u8 pad0[0x24];
    /* 0x024 */ NodeQuad *unk24;
    /* 0x028 */ u8 pad28[0xC];
    /* 0x034 */ f32 unk34;
    /* 0x038 */ f32 unk38;
    /* 0x03C */ f32 unk3C;
} ActorSub4View;

typedef struct ActorModel {
    /* 0x000 */ u8 pad0[0x20];
    /* 0x020 */ u8 unk20;
} ActorModel;

typedef struct {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xC];
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x20];
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ u8 padAC[0x9A];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xE];
    /* 0x156 */ u8 unk156;
} ParentActor;

typedef struct SiblingActor {
    /* 0x000 */ u8 pad0[8];
    /* 0x008 */ void *unk8;
    /* 0x00C */ u8 padC[0x48];
    /* 0x054 */ s32 unk54;
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0x20];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x20];
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ u8 padAC[0x9A];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0xC];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[9];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[0x14];
    /* 0x174 */ void *unk174;
    /* 0x178 */ u8 pad178[0x88];
    /* 0x200 */ s16 unk200;
} SiblingActor;

extern f32 D_80750394;

#define ATTACHED_ACTOR ((AttachedActor *) gCurrentActor)

void actorUpdateSpinAndVelocity(void) {
    SubStateView *sub;
    s32 pad;

    sub = ATTACHED_ACTOR->unk174;
    if (!(ATTACHED_ACTOR->unk60 & 0x10)) {
        ATTACHED_ACTOR->unkB8 = ATTACHED_ACTOR->unk124->unk0;
        ATTACHED_ACTOR->unkEE = ATTACHED_ACTOR->unk124->unk4;
        ATTACHED_ACTOR->unkC0 = ATTACHED_ACTOR->unk124->unk8;
        ATTACHED_ACTOR->unk144 = 1;
        sub->unk0 = (randomNonNegative() >> 15) % 0x46;
        sub->unk4 = (randomNonNegative() >> 15) % 0xC8;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    ATTACHED_ACTOR->unkC0 += D_80750394;
    ATTACHED_ACTOR->unkE8 += sub->unk4;
    ATTACHED_ACTOR->unkE4 += sub->unk0;
    if (ATTACHED_ACTOR->unkFC != 0 || ((ATTACHED_ACTOR->unk6A & 1) && !(ATTACHED_ACTOR->unk6C & 1))) {
        actorDespawn(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorUpdateSpinAndVelocityWrapperA(void) {
    actorUpdateSpinAndVelocity();
}

void actorUpdateSpinAndVelocityWrapperB(void) {
    actorUpdateSpinAndVelocity();
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x24];
} NodePosition;

extern void *gCamActor;
extern u8 gBossFightPhase;
extern f32 D_80750398;
extern u8 D_80720BE8;

void actorFallAndBurstUpdate(void) {
    NodePosition pos;
    s32 i;

    if (!(ATTACHED_ACTOR->unk60 & 0x10)) {
        ATTACHED_ACTOR->unk144 = 0x1C;
        ATTACHED_ACTOR->unkC0 = 0.0f;
        ATTACHED_ACTOR->unk12A = 0x7D0;
        ATTACHED_ACTOR->unkA4 = 99999.0f;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    }
    if (camIsCutsceneActive() != 0) {
        ATTACHED_ACTOR->unk132 = 2;
    } else {
        ATTACHED_ACTOR->unk132 = 1;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    ATTACHED_ACTOR->unkC0 += D_80750398;
    if (ATTACHED_ACTOR->unkA4 != 99999.0f) {
        billboardSetFlags(1);
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x18, 0x18, 1, 0x96, 0xB4, 0, 1.0f);
    } else {
        actorDespawn(gCurrentActor);
    }
    if (gBossFightPhase == 4 || ATTACHED_ACTOR->unkFC != 0
        || ((ATTACHED_ACTOR->unk6A & 1) && !(ATTACHED_ACTOR->unk6C & 1))) {
        camStartShake(gCamActor, 0xF, 0xF);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x162, 0xE1, 0x3C, 1);
        for (i = 1; i != 7; i++) {
            actorGetNodePos(gCurrentActor, i, &pos.unk8, &pos.unk4, &pos.unk0);
            effectSetAngle(i);
            effectSetDepth(1);
            effectSetCallback(effectSpinBillboardingUpdate);
            effectSetColor(0xFF, 0xFF, 0xFF, 0x96);
            effectCreateAtPosition(&D_80720BE8, 1.5f, pos.unk8, pos.unk4, pos.unk0);
        }
        actorDespawn(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void actorUpdateModelMatrixCurrent(void) {
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorShadowFollowUpdate(void) {
    SubStateView *sub;
    s32 temp;
    s32 v;

    sub = ATTACHED_ACTOR->unk11C->unk174;
    if (!(ATTACHED_ACTOR->unk60 & 0x10)) {
        ATTACHED_ACTOR->unk60 &= 0xFFFF7FFF;
        ATTACHED_ACTOR->unk128 = 0xFF;
        ATTACHED_ACTOR->unk60 |= 0x800000;
        ATTACHED_ACTOR->unk16A = 0xFF;
        ATTACHED_ACTOR->unk16B = 0xFF;
        ATTACHED_ACTOR->unk16C = 0xFF;
        ATTACHED_ACTOR->unk160 = (f64) ATTACHED_ACTOR->unk11C->unk15E * 0.1 * 0.15;
    }
    ATTACHED_ACTOR->unk7C = ATTACHED_ACTOR->unk11C->unk7C;
    ATTACHED_ACTOR->unk80 = ATTACHED_ACTOR->unk11C->unk80;
    ATTACHED_ACTOR->unk84 = ATTACHED_ACTOR->unk11C->unk84;
    if (ATTACHED_ACTOR->unk128 & 8) {
        ATTACHED_ACTOR->unk4->unk34 = (ATTACHED_ACTOR->unk160 * 0.8 - ATTACHED_ACTOR->unk4->unk34) * 0.3 + ATTACHED_ACTOR->unk4->unk34;
    } else {
        ATTACHED_ACTOR->unk4->unk34 = (ATTACHED_ACTOR->unk160 * 1.2 - ATTACHED_ACTOR->unk4->unk34) * 0.3 + ATTACHED_ACTOR->unk4->unk34;
    }
    ATTACHED_ACTOR->unk4->unk3C = ATTACHED_ACTOR->unk4->unk34;
    temp = sub->unk200;
    v = temp > 0 ? temp : 0;
    if (v < 0xFF) {
        v = temp > 0 ? temp : 0;
        ATTACHED_ACTOR->unk128 = v;
    } else {
        ATTACHED_ACTOR->unk128 = 0xFF;
    }
    if (ATTACHED_ACTOR->unk128 == 0 || ATTACHED_ACTOR->unk11C->unk154 != 0x7C) {
        actorDespawn(gCurrentActor);
    } else {
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}


void actorSpawnAttachedTo(Actor *arg0) {
    actorSpawn(0x6A, controllerLookupStateByHash(arg0));
    gSpawnedActor->parentActor = (s32) arg0;
    arg0->contactFlags |= 0x800;
}

s32 actorTableContains(Actor *);
extern u8 gGfxBufferIndex;

void actorMirrorParentModelY(void) {
    Mtx mtxL;
    float mtx1[4][4];
    float mtx3[4][4];
    float mtx2[4][4];
    SubStateView *sub;
    Mtx *dst;
    s32 i;

    sub = ATTACHED_ACTOR->unk174;
    if (!(ATTACHED_ACTOR->unk60 & 0x10)) {
        ATTACHED_ACTOR->unk60 |= 0x8100000;
        ATTACHED_ACTOR->unk60 &= 0xFFFF7FFF;
        controllerAnimLoadStateAsset1(gCurrentActor, controllerLookupStateByHash(gCurrentActor));
        sub->unk4 = ATTACHED_ACTOR->unk11C->unk54;
        sub->unk0 = (s32) ATTACHED_ACTOR->unk11C;
        sub->unk8 = ATTACHED_ACTOR->unk11C->unk58;
    }
    if (!actorTableContains((Actor *) sub->unk0) || sub->unk4 != ATTACHED_ACTOR->unk11C->unk54) {
        actorDespawn(gCurrentActor);
        return;
    }
    if (!(func_80665AAC((Actor *) sub->unk0) && sub->unk8 == ATTACHED_ACTOR->unk11C->unk58
          && actorIsActive((Actor *) sub->unk0) && (((ParentActor *) sub->unk0)->unk68 & 0x40))) {
        actorDespawn(gCurrentActor);
        ((ParentActor *) sub->unk0)->unk6A &= 0xF7FF;
        return;
    }
    {
        ATTACHED_ACTOR->unk128 = 0xFF;
        ATTACHED_ACTOR->unk146 = ((ParentActor *) sub->unk0)->unk146;
        ATTACHED_ACTOR->unk7C = ((ParentActor *) sub->unk0)->unk7C;
        ATTACHED_ACTOR->unk80 = ((ParentActor *) sub->unk0)->unk80;
        ATTACHED_ACTOR->unkA8 = ((ParentActor *) sub->unk0)->unkA8;
        ATTACHED_ACTOR->unk84 = ((ParentActor *) sub->unk0)->unk84;
        ATTACHED_ACTOR->unk60 |= 0x200;
        ATTACHED_ACTOR->unk8 = ((void **) ((u8 *) ATTACHED_ACTOR->unk4 + 0x14))[gGfxBufferIndex];
        memcpy(ATTACHED_ACTOR->unk8, ATTACHED_ACTOR->unk11C->unk8, ATTACHED_ACTOR->unk0->unk20 << 6);
        guMtxIdentF(mtx1);
        mtx1[1][1] = -1.0f;
        guTranslateF(mtx2, -ATTACHED_ACTOR->unk7C, -ATTACHED_ACTOR->unkA8, -ATTACHED_ACTOR->unk84);
        guMtxCatF(mtx2, mtx1, mtx1);
        guMtxF2L(mtx1, &mtxL);
        guTranslateF(mtx2, ATTACHED_ACTOR->unk7C, ATTACHED_ACTOR->unkA8, ATTACHED_ACTOR->unk84);
        dst = ATTACHED_ACTOR->unk8;
        for (i = 0; i < ATTACHED_ACTOR->unk0->unk20; i++) {
            guMtxL2F(mtx3, dst);
            guMtxCatF(mtx3, mtx1, mtx3);
            guMtxCatF(mtx3, mtx2, mtx3);
            guMtxF2L(mtx3, dst);
            dst++;
        }
    }
}



void actorMirrorParentModelAxis(void) {
    Mtx mtxL;
    float mtx1[4][4];
    float mtx3[4][4];
    float mtx2[4][4];
    SubStateView *sub;
    Mtx *dst;
    s32 i;

    sub = ATTACHED_ACTOR->unk174;
    if (!(ATTACHED_ACTOR->unk60 & 0x10)) {
        ATTACHED_ACTOR->unk60 |= 0x8100000;
        ATTACHED_ACTOR->unk60 &= 0xFFFF7FFF;
        controllerAnimLoadStateAsset1(gCurrentActor, controllerLookupStateByHash(gCurrentActor));
        sub->unk4 = ATTACHED_ACTOR->unk11C->unk54;
        sub->unk0 = (s32) ATTACHED_ACTOR->unk11C;
        sub->unk8 = ATTACHED_ACTOR->unk11C->unk58;
    }
    if (!actorTableContains((Actor *) sub->unk0) || sub->unk4 != ATTACHED_ACTOR->unk11C->unk54) {
        actorDespawn(gCurrentActor);
        triggerZoneRemoveSpawned(gCurrentActor);
        return;
    }
    if (!(sub->unk8 == ATTACHED_ACTOR->unk11C->unk58 && actorIsActive((Actor *) sub->unk0)
          && (((ParentActor *) sub->unk0)->unk68 & 0x80))) {
        actorDespawn(gCurrentActor);
        triggerZoneRemoveSpawned(gCurrentActor);
        ((ParentActor *) sub->unk0)->unk156--;
        return;
    }
    ATTACHED_ACTOR->unk128 = sub->unkF;
    ATTACHED_ACTOR->unk146 = ATTACHED_ACTOR->unk11C->unk146;
    ATTACHED_ACTOR->unk7C = ATTACHED_ACTOR->unk11C->unk7C;
    ATTACHED_ACTOR->unk80 = ATTACHED_ACTOR->unk11C->unk80;
    ATTACHED_ACTOR->unkA8 = ATTACHED_ACTOR->unk11C->unkA8;
    ATTACHED_ACTOR->unk84 = ATTACHED_ACTOR->unk11C->unk84;
    ATTACHED_ACTOR->unk60 |= 0x200;
    ATTACHED_ACTOR->unk8 = ((void **) ((u8 *) ATTACHED_ACTOR->unk4 + 0x14))[gGfxBufferIndex];
    memcpy(ATTACHED_ACTOR->unk8, ATTACHED_ACTOR->unk11C->unk8, ATTACHED_ACTOR->unk0->unk20 << 6);
    guMtxIdentF(mtx1);
    if (sub->unkE & 1) {
        mtx1[0][0] = -1.0f;
        guTranslateF(mtx2, -sub->unkC, 0.0f, 0.0f);
        guMtxCatF(mtx2, mtx1, mtx1);
        guMtxF2L(mtx1, &mtxL);
        guTranslateF(mtx2, sub->unkC, 0.0f, 0.0f);
    } else {
        mtx1[2][2] = -1.0f;
        guTranslateF(mtx2, 0.0f, 0.0f, -sub->unkC);
        guMtxCatF(mtx2, mtx1, mtx1);
        guMtxF2L(mtx1, &mtxL);
        guTranslateF(mtx2, 0.0f, 0.0f, sub->unkC);
    }
    dst = ATTACHED_ACTOR->unk8;
    for (i = 0; i < ATTACHED_ACTOR->unk0->unk20; i++) {
        guMtxL2F(mtx3, dst);
        guMtxCatF(mtx3, mtx1, mtx3);
        guMtxCatF(mtx3, mtx2, mtx3);
        guMtxF2L(mtx3, dst);
        dst++;
    }
    {
        f32 sp58;
        f32 sp54;
        f32 sp50;

        guMtxXFMF(mtx1, ATTACHED_ACTOR->unk7C, ATTACHED_ACTOR->unk80, ATTACHED_ACTOR->unk84, &sp58, &sp54, &sp50);
        guMtxXFMF(mtx2, sp58, sp54, sp50, &ATTACHED_ACTOR->unk7C, &ATTACHED_ACTOR->unk80, &ATTACHED_ACTOR->unk84);
    }
}



void animSetChannelFrames(void *arg0, u8 arg1, u8 arg2) {
    animSetLoopLimit(arg0, 0, 1);
    animSetFinished(arg0, 0, 1);
    animSetFrameAndSubframe(arg0, 0, arg1, 0.0f);
    animSetLoopLimit(arg0, 1, 1);
    animSetFinished(arg0, 1, 1);
    animSetFrameAndSubframe(arg0, 1, arg2, 0.0f);
}


void actorSetGroupState(u8 arg0, u8 arg1) {
    Actor *actor;
    s16 i;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (actor->actorType == 0x94 && actor->unk15F / 3 == arg0) {
            actor->state = arg1;
            actor->unk155[0] = 0;
        }
    }
}

typedef struct MatrixArray {
    f32 *unk0;
} MatrixArray;

void actorSetNodeValuesForFrame(MatrixArray *arg0) {
    NodeQuad *dst;
    s16 i;

    dst = ATTACHED_ACTOR->unk4->unk24;
    for (i = 0; i < 7; i++) {
        dst->unkC = (f64) arg0->unk0[i * 0x34 + ATTACHED_ACTOR->unk168];
        dst++;
    }
}

f32 mathCosF(s16);
extern u8 D_807503D4[];
extern u8 D_807503E0[];

#define ATTACHED_ACTOR_SPAWNED ((AttachedActor *) gSpawnedActor)

void func_806A112C(void) {
    SubStateView *sub;
    s16 i;
    u8 n;
    f32 d;
    f32 val;
    SubStateView *sub2;

    sub = ATTACHED_ACTOR->unk174;
    if (!(ATTACHED_ACTOR->unk60 & 0x10)) {
        ATTACHED_ACTOR->unk60 |= 0x400;
        func_80724D28(0, 7);
        for (i = 0; i < 7; i++) {
            ((u8 *) ATTACHED_ACTOR->unk4->unk24)[i * 0x10] = i;
            ((u8 *) ATTACHED_ACTOR->unk4->unk24)[i * 0x10 + 1] = 0xFF;
        }
        if (ATTACHED_ACTOR->unk15F == 0) {
            val = (f32) ((f64) ATTACHED_ACTOR->unk4->unk38 / 0.15);
            sub->unk0 = assetLoad(0x13, 6, 1, 1);
            n = 0;
            animSetChannelFrames(gCurrentActor, D_807503D4[n], D_807503E0[n++]);
            d = 75.0f * val;
            for (i = 1; i < 12; i++) {
                actorSpawn(0x94, 0xE1);
                sub2 = ATTACHED_ACTOR_SPAWNED->unk174;
                sub2->unk0 = sub->unk0;
                ATTACHED_ACTOR_SPAWNED->unk15F = i;
                ATTACHED_ACTOR_SPAWNED->unkE6 = ATTACHED_ACTOR->unkE6 + ((u16)(i / 3) << 10);
                ATTACHED_ACTOR_SPAWNED->unk7C = ATTACHED_ACTOR->unk7C -
                    mathSinF(ATTACHED_ACTOR_SPAWNED->unkE6) * d;
                ATTACHED_ACTOR_SPAWNED->unk80 = ATTACHED_ACTOR->unk80 +
                    (f32) ((u8) (i % 3) * 17);
                ATTACHED_ACTOR_SPAWNED->unk84 = ATTACHED_ACTOR->unk84 -
                    mathCosF(ATTACHED_ACTOR_SPAWNED->unkE6) * d;
                actorSetUniformScale(gSpawnedActor, ATTACHED_ACTOR->unk4->unk38);
                animSetChannelFrames(gSpawnedActor, D_807503D4[n], D_807503E0[n++]);
            }
            ATTACHED_ACTOR->unk7C -= d * mathSinF(ATTACHED_ACTOR->unkE6);
            ATTACHED_ACTOR->unk84 -= d * mathCosF(ATTACHED_ACTOR->unkE6);
        }
    }
    switch (ATTACHED_ACTOR->unk154) {
    case 1:
        ATTACHED_ACTOR->unk168++;
        if (ATTACHED_ACTOR->unk168 == 7) {
            ATTACHED_ACTOR->unk154++;
            ATTACHED_ACTOR->unk168 = 0;
        }
        break;
    case 2:
        actorSetNodeValuesForFrame((MatrixArray *) sub);
        ATTACHED_ACTOR->unk168++;
        if (ATTACHED_ACTOR->unk168 == 11) {
            ATTACHED_ACTOR->unk154++;
        }
        break;
    case 3:
        actorSetNodeValuesForFrame((MatrixArray *) sub);
        ATTACHED_ACTOR->unk168++;
        if (ATTACHED_ACTOR->unk168 >= 52) {
            ATTACHED_ACTOR->unk168 = ((randomNonNegative() >> 15) % 1000) % 3;
            ATTACHED_ACTOR->unk154 = 0;
        }
        break;
    case 10:
        ATTACHED_ACTOR->unk168 = 11;
        actorSetNodeValuesForFrame((MatrixArray *) sub);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
