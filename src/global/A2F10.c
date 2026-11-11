#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_actorDespawn // FAKE: callee prototype steer
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

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;
extern u16 gActiveActorCount;
extern ActorEntry gActiveActors[];

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


void actorTriggerRampWithSfx(void) {
    Actor *actor;
    Actor **p;
    s16 i;
    s16 *event;
    u32 flags;

    actor = gCurrentActor;
    p = &gCurrentActor; // FAKE: re-read of gCurrentActor through a pointer (actor = *p below)
    if (!(actor->flags & 0x10)) {
        actor->flags &= ~4;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x407, 0.0f, 0.0f);
        scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
        actor = gCurrentActor;
    }
    for (i = 0; i < gActorGlobalState.unk254; i++) {
        event = gActorGlobalState.unk278[i];
        if (*event == 0) {
            flags = actor->flags; // FAKE: flags copied through a temp before the or (load order)
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
    if (0.0f == actor->sub4->model->speed) {
        actor->flags &= ~4;
        actor = *p;
    }
    actorUpdateModelMatrix(actor, 0);
}

void actorSpawnNodeEntryAtActor(s32 arg0, s16 arg1) {
    Actor *actor;

    actor = gCurrentActor;
    actorSpawnNodeEntryScaled(arg0, actor->x, actor->y, actor->z, 0, 0, arg1, actor);
}

void actorPlaceAttachedChildren(s16 arg0) {
    Actor *actor;
    s16 i;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (actor->parentActor == gCurrentActor) {
            actorAppendMoveTarget3D(gCurrentActor, actor, gCurrentActor->x,
                                           gCurrentActor->y + (f32)arg0, gCurrentActor->z, 2, 1);
        }
    }
}

void actorAttachChildCallbacks(void) {
    Actor *actor;
    s16 i;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (actor->parentActor == gCurrentActor) {
            actorAppendCallback(actor, gCurrentActor, 0x2000000, 1, 0, NULL);
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

s32 actorTypeToNodeIndex(s32 arg0) {
    switch (arg0) {
    case 2:
        return 0xB;
    case 3:
        return 0xE;
    case 5:
    case 6:
    case 7:
        return 0xA;
    case 4:
        return 0xD;
    }
    return 0;
}

typedef struct LightPulseState {
    /* 0x000 */ f32 unk0;
    /* 0x004 */ u8 pad4[8];
    /* 0x00C */ u16 unkC;
    /* 0x00E */ u8 padE[2];
    /* 0x010 */ u8 unk10;
    /* 0x011 */ u8 unk11;
    /* 0x012 */ u8 unk12;
} LightPulseState;

extern u8 gSplitScreenMode;
extern s32 gCurrentMap;
extern u8 gPlayerCount;
extern PlayerStruct *gPlayerSlots;

f32 mathSinF(s16);

void actorLightPulseUpdate(void) {
    u16 lightRadius;
    f32 rangeSq;
    u8 despawned;
    PlayerState *hostState;
    u8 isAttached[4]; // FAKE: flag kept in memory (array) so its loads are not CSE'd into the loop; element 3 = byte 0x7F
    Actor *host;
    s32 *hostFlags;
    LightPulseState *light;
    Actor *attachedTo;
    f32 wobble;
    s32 pad;
    s32 callbackId;
    s32 i;
    Actor *target;

    lightRadius = 0x12C;
    despawned = 0;
    isAttached[3] = 0;
    attachedTo = (Actor *)gCurrentActor->parentActor;
    light = (LightPulseState *)gCurrentActor->customState;
    if (attachedTo != NULL && (attachedTo->collisionFlags & 1)) {
        host = attachedTo;
        isAttached[3] = 1;
    } else {
        host = gPrimaryPlayerActor;
    }
    hostState = (PlayerState *)host->customState;
    if (gPlayerCount >= 2 && gSplitScreenMode == 1) {
        attachedTo = (Actor *)gPrimaryPlayerActor->customState; // FAKE: reuses attachedTo for the player state pointer (register reuse)
        hostFlags = &((PlayerState *)attachedTo)->stateFlags;
    } else {
        hostFlags = &hostState->stateFlags;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        light->unkC = (u16)host->collision->radius;
        gCurrentActor->drawDistance = 0x3E8;
        gCurrentActor->flags |= 0x400;
        animSetLoopLimit(gCurrentActor, 0, 1);
        animSetSpeed(gCurrentActor, 0, 1.0f);
        animSetFinished(gCurrentActor, 0, 1);
        *hostFlags |= 0x02000000;
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        switch (controllerLookupStateByHash(gCurrentActor)) {
        case 0xAD:
            light->unk10 = 0xFF;
            light->unk11 = 0xFF;
            light->unk12 = 0x32;
            break;
        case 0xAE:
            light->unk10 = 0xFF;
            light->unk11 = 0x32;
            light->unk12 = 0x32;
            break;
        case 0xD1:
            light->unk10 = 0xCA;
            light->unk11 = 0x5B;
            light->unk12 = 0xFF;
            break;
        case 0xD0:
            light->unk10 = 0;
            light->unk11 = 0x96;
            light->unk12 = 0xFF;
            break;
        case 0xCF:
            light->unk10 = 0x32;
            light->unk11 = 0xFF;
            light->unk12 = 0x32;
            break;
        }
        if (isAttached[3] != 0) {
            light->unk0 = 2.0f;
        } else {
            light->unk0 = 1.5f;
        }
        if (gCurrentActor->unk15F != 0) {
            actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 1.0f, 0);
        }
    }
    if (camIsCutsceneActive() != 0) {
        camStartShake(hostState->camActor, 0xA, 0xA);
    }
    gCurrentActor->sub4->scaleX =
        gCurrentActor->sub4->scaleX * gCurrentActor->splineT;
    gCurrentActor->sub4->scaleZ = gCurrentActor->sub4->scaleX;
    gCurrentActor->sub4->scaleY = gCurrentActor->sub4->scaleY * 1.04;
    wobble = mathSinF(gCurrentActor->moveYaw);
    gCurrentActor->sub4->scaleY = gCurrentActor->sub4->scaleY + 0.01 * (f64)wobble;
    gCurrentActor->moveYaw += 0x1F4;
    gCurrentActor->yaw += 0x32;
    gCurrentActor->state++;
    if (gCurrentActor->state == gCurrentActor->yawSpeed) {
        animSetFinished(gCurrentActor, 0, 0);
    } else if (gCurrentActor->yawSpeed < gCurrentActor->state) {
        lightRadius = 0x12C - (gCurrentActor->state - gCurrentActor->yawSpeed) * 0x28;
        if (animIsPlaying(gCurrentActor, 0) == 0) {
            despawned = 1;
            *hostFlags &= 0xFDFFFFFF;
            actorSetCollisionRadius(host, (f32)light->unkC);
            actorGetOrSetNodeScale(host, actorTypeToNodeIndex(host->actorType), 0.0f);
            actorDespawn(gCurrentActor);
        }
    }
    lightSetFlags(1);
    lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f,
             0.0f, 0.0f, gCurrentActor->sub4->scaleX * (f32)lightRadius * light->unk0, 0,
             light->unk10, light->unk11, light->unk12);
    if (gCurrentMap != 0x4C) {
        if (isAttached[3] == 0 || gCurrentActor->unk15F != 0) {
            callbackId = 0x2E;
            if (func_80714608(0) != 0) {
                callbackId = 0xE;
            }
            rangeSq = gCurrentActor->sub4->scaleX * (f32)lightRadius;
            rangeSq = rangeSq * rangeSq;
            for (i = 0; i < gPlayerCount; i++) {
                target = gPlayerSlots[i].actor;
                if (isAttached[3] == 0 ||
                    (i != hostState->playerIndex && target->state != 0x84)) {
                    if (actorIsTargetInRange(target, (f32)target->eyeHeight, rangeSq) !=
                        0) {
                        playerStateQueueCallback(callbackId, gCurrentActor, i);
                    }
                    if (gPlayerCount && gPlayerCount) {}  // FAKE: steers uopt to PRE-reload the loop count
                }
            }
            if (gCurrentActor->unk15F != 0) {
                actorSetCollisionRadius(
                    gCurrentActor,
                    (f32)(2.0 * ((f64)(gCurrentActor->sub4->scaleX * (f32)lightRadius) *
                                 6.66666667)));
                actorGetOrSetNodeScale(
                    gCurrentActor, 1,
                    (f32)((f64)(gCurrentActor->sub4->scaleX * (f32)lightRadius) *
                          6.66666667));
            }
        } else if (despawned == 0) {
            actorSetCollisionRadius((Actor *)gCurrentActor->parentActor,
                          (f32)(2.0 * ((f64)(gCurrentActor->sub4->scaleX * (f32)lightRadius) *
                                       6.66666667)));
            actorGetOrSetNodeScale(
                (Actor *)gCurrentActor->parentActor, actorTypeToNodeIndex(host->actorType),
                (f32)((f64)(gCurrentActor->sub4->scaleX * (f32)lightRadius) * 6.66666667));
            actorOrNodeFlags(host, actorTypeToNodeIndex(host->actorType), 3);
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

extern u8 gGameMode;
extern s32 gGlobalCutsceneFlags;


void actorShockwaveUpdate(void) {
    u8 height;
    u16 radius;
    f32 fade;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    f32 prevY;

    height = (gCurrentActor->movePitch == 0xBB) ? 0x28 : 0x23;
    radius = (gCurrentActor->movePitch == 0x6A) ? 0x78 : 0x190;
    if (gGameMode == 1) {
        actorDespawn(gCurrentActor);
    }
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->drawDistance = 0x3E8;
        gCurrentActor->flags |= 0x400;
        animSetLoopLimit(gCurrentActor, 0, 1);
        animSetSpeed(gCurrentActor, 0, 0.5f);
        animSetFinished(gCurrentActor, 0, 1);
        gCurrentActor->moveYaw = 0x3C;
    }
    if (gCurrentActor->yawSpeed != 0) {
        fade = 1.0f;
        if (gCurrentActor->moveYaw < 0x1E) {
            fade = gCurrentActor->moveYaw / 30.0;
        }
        lightSetFlags(1);
        lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f,
                 gCurrentActor->sub4->scaleX * 300.0f, 0,
                 (u32)((f32)gCurrentActor->tintR * fade),
                 (u32)((f32)gCurrentActor->tintG * fade),
                 (u32)((f32)gCurrentActor->tintB * fade));
        gCurrentActor->sub4->scaleX = (f32)((f64)gCurrentActor->sub4->scaleX * gCurrentActor->splineT);
        gCurrentActor->sub4->scaleZ = (f32)((f64)gCurrentActor->sub4->scaleZ * gCurrentActor->splineT);
    }
    switch (gCurrentActor->state) {
    case 0:
        if (gCurrentActor->yawSpeed == 0) {
            gCurrentActor->sub4->scaleX =
                (f32)((f64)gCurrentActor->sub4->scaleX * gCurrentActor->splineT);
            gCurrentActor->sub4->scaleZ =
                (f32)((f64)gCurrentActor->sub4->scaleZ * gCurrentActor->splineT);
        }
        if (gCurrentActor->sub4->model->speed == 0.0f ||
            gCurrentActor->sub4->model->frame > 5.0f) {
            gCurrentActor->state = 1;
            animSetFinished(gCurrentActor, 0, 0);
        }
        break;
    case 1:
        if ((gCurrentActor->sub4->model->speed == 0.0f && animGetNodeByIndex(gCurrentActor, 0)->unkC >= 0xE) ||
            gCurrentActor->sub4->model->frame > 9.0f) {
            gCurrentActor->state = 2;
            if (gCurrentActor->unk15F != 0 && actorSpawn(0x102, gCurrentActor->movePitch) != 0) {
                if (gCurrentActor->sub4->model->frame > 9.0f) {
                    controllerAnimSetStateIfChanged(gSpawnedActor, 0x4F9, 0.0f, 0.0f);
                    scriptSetActorRampTarget(gSpawnedActor, gCurrentActor->sub4->unk48, 0.0f);
                }
                actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleY);
                gSpawnedActor->movePitch = gCurrentActor->movePitch;
                gSpawnedActor->sub4->scaleX = (f32)((f64)gCurrentActor->sub4->scaleX + 0.02);
                gSpawnedActor->sub4->scaleZ = (f32)((f64)gCurrentActor->sub4->scaleZ + 0.02);
                gSpawnedActor->unk15F = gCurrentActor->unk15F - 1;
                gSpawnedActor->splineT = gCurrentActor->splineT;
            }
        }
        break;
    case 2:
        if (animIsPlaying(gCurrentActor, 0) == 0) {
            gCurrentActor->state = 3;
            if (gCurrentActor->yawSpeed != 0) {
                gCurrentActor->flags &= ~4;
            } else {
                actorDespawn(gCurrentActor);
            }
        }
        break;
    case 3:
        gCurrentActor->moveYaw--;
        if (gCurrentActor->moveYaw == 0) {
            actorDespawn(gCurrentActor);
            break;
        }
    }
    if (gCurrentActor->movePitch != 0x6A && !(gGlobalCutsceneFlags & 2)) {
        if ((gCurrentActor->flags & 4) && (gCurrentActor->flags & 0x10)) {
            prevY = gCurrentActor->y;
            actorGetNodePos(gCurrentActor, 1, &nodeX, &nodeY, &nodeZ);
            nodeY += 50.0f;
            if (collisionCheckGroundAtPoint(nodeX, nodeZ, &nodeY) != 0) {
                if (((nodeY < prevY) ? (prevY - nodeY) : (nodeY - prevY)) < 40.0f || !(gCurrentActor->flags & 0x10)) {
                    gCurrentActor->y = nodeY;
                }
            }
        }
    }
    if (gCurrentActor->yawSpeed == 0 || gCurrentActor->state != 3) {
        if (actorIsTargetInCylinder((s16)gCurrentActor->x, (s16)(gCurrentActor->y - 20.0f),
                          (s16)gCurrentActor->z, height,
                          gCurrentActor->sub4->scaleX * (f32)radius) != 0 &&
            actorIsTargetInCylinder((s16)gCurrentActor->x, (s16)(gCurrentActor->y - 20.0f),
                          (s16)gCurrentActor->z, height,
                          gCurrentActor->sub4->scaleX * (f32)(radius - 0x14)) == 0) {
            playerStateQueueCallback(0x2E, gCurrentActor, 0);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void renderScaledSprite(Gfx *arg0, Actor *arg1) {
    f32 scale;

    scale = arg1->floorSlopeFactor;
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
    f32 scale;
    f32 mtx[4][4];
    f32 translate[4][4];
    void *mtxBuf;
    char text[0x10];
    s16 width;
    u8 font;
    u8 centered;
    f64 size;
    s32 sel;

    if (((f64)arg1->floorSlopeFactor - 2.0) < 0.01) {
        size = 0.01;
    } else {
        size = (f64)arg1->floorSlopeFactor - 2.0;
    }
    scale = (f32)(size * 0.3);
    centered = 0;
    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xFA000000, (arg1->yaw & 0xFF) | 0xFFFFFF00);
    arg0 = func_8070068C(arg0);
    mtxBuf = heapAlloc(0x40);
    heapFreeDeferred(mtxBuf);
    font = 1;
    sel = arg1->unk15F;
    switch (sel ^ 0) { // FAKE: keeps the switch selector copy (v0) out of copy propagation
    case 0:
        _sprintf(text, "ROUND");
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
        centered = 1;
        _sprintf(text, D_80750338[sel]);
        break;
    default:
        if (sel & 0x80) {
            font = 3;
            scale = (f32)(4.0 - (f64)scale);
            _sprintf(text, "%d", 0xA - (sel & 0x3F));
        } else if (sel & 0x40) {
            font = 3;
            scale = (f32)(4.0 - (f64)scale);
            _sprintf(text, "%d", 8 - (sel & 0x3F));
        } else {
            _sprintf(text, "%d", sel);
        }
        break;
    }
    width = textGetStringWidth(font, text);
    if (centered != 0) {
        arg1->x = (f32)((0x140 - width) << 1);
    }
    guScaleF(mtx, scale, scale, 1.0f);
    guTranslateF(translate, (f32)((f64)arg1->x + 2.0 * (f64)width),
                 arg1->y * 4.0f, 0.0f);
    guMtxCatF(mtx, translate, mtx);
    guMtxF2L(mtx, (Mtx *)mtxBuf);
    WRITE_GFX(arg0++, 0xDA380003, (u32)mtxBuf);
    return textDrawStringVtx(arg0, (s16)font, (s16)(width * -2), 0, (u8 *)text, 0);
}
void actorUpdateBannerFade(void) {
    f32 ratio;
    s16 sfx;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->moveYaw =
            (s16)gCurrentActor->splineT;
    }
    if ((f64)(u32)gFrameDelta * 0.5 < gCurrentActor->splineT) {
        gCurrentActor->splineT -=
            (f64)(u32)gFrameDelta * 0.5;
        ratio = (f32)(gCurrentActor->splineT /
                      (f64)(f32)gCurrentActor->moveYaw);
        gCurrentActor->floorSlopeFactor =
            (f32)((f64)ratio * -8.0 + 12.0);
        gCurrentActor->yaw = (s16)(255.0f * ratio);
        if (gCurrentActor->unk15F >= 0x14 &&
            gCurrentActor->unk15F < 0x1E) {
            renderCallbacksRegister(renderScaledSprite, gCurrentActor, 3);
        } else {
            renderCallbacksRegister(actorBannerTextRender, gCurrentActor, 3);
        }
        if (gCurrentActor->unk15F == 0 &&
            (s16)gCurrentActor->splineT == 3) {
            actorSpawn(0x104, 0);
            gSpawnedActor->splineT =
                (f64)gCurrentActor->moveYaw;
            gSpawnedActor->unk15F = D_80750AD4;
            gSpawnedActor->y = 80.0f;
            gSpawnedActor->x = 640.0f;
            sfxPlayOnFreeSlot((s16)(D_80750AD4 + 0x3F3), 0x7FFF, 63.0f, 1.0f, 0,
                          0);
            return;
        }
        if (gCurrentActor->unk15F >= 0x1E &&
            gCurrentActor->unk15F < 0x25 &&
            (s16)gCurrentActor->splineT == 5) {
            actorSpawn(0x104, 0);
            gSpawnedActor->splineT =
                (f64)gCurrentActor->moveYaw;
            if (gCurrentActor->unk15F == 0x23) {
                gSpawnedActor->unk15F = 0x24;
            } else if (gCurrentActor->unk15F == 0x24) {
                gSpawnedActor->unk15F = 0x25;
            } else {
                gSpawnedActor->unk15F = 0x26;
            }
            gSpawnedActor->y = 80.0f;
            gSpawnedActor->x = 500.0f;
        }
    } else {
        if ((gCurrentActor->unk15F & 0xC0) != 0 &&
            (gCurrentActor->unk15F & 0x3F) != 0) {
            sfx = 0x3FC - (gCurrentActor->unk15F & 0x3F);
            actorSpawn(0x104, 0);
            gSpawnedActor->splineT =
                (f64)gCurrentActor->moveYaw;
            gSpawnedActor->unk15F =
                (gCurrentActor->unk15F & 0xC0) +
                (gCurrentActor->unk15F & 0x3F) - 1;
            if (gCurrentActor->unk15F & 0x80) {
                sfx += 2;
            }
            sfxPlayOnFreeSlot(sfx, 0x7FFF, 63.0f, 1.0f, 0, 0);
            gSpawnedActor->y = 80.0f;
            gSpawnedActor->x = 600.0f;
        }
        actorDespawn(gCurrentActor);
    }
}

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

typedef struct ActorModel {
    /* 0x000 */ u8 pad0[0x20];
    /* 0x020 */ u8 unk20;
} ActorModel;

extern f32 D_80750394;


void actorUpdateSpinAndVelocity(void) {
    SubStateView *sub;
    s32 pad;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->speedXZ = ((Position3f *)gCurrentActor->spawnData)->unk0;
        gCurrentActor->moveYaw = ((Position3f *)gCurrentActor->spawnData)->unk4;
        gCurrentActor->speedY = ((Position3f *)gCurrentActor->spawnData)->unk8;
        gCurrentActor->unk144 = 1;
        sub->unk0 = (randomNonNegative() >> 15) % 0x46;
        sub->unk4 = (randomNonNegative() >> 15) % 0xC8;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    gCurrentActor->speedY += D_80750394;
    gCurrentActor->roll += sub->unk4;
    gCurrentActor->pitch += sub->unk0;
    if (gCurrentActor->hasArcBounds != 0 || ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1))) {
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
extern f32 D_80750398;
extern u8 D_80720BE8;

void actorFallAndBurstUpdate(void) {
    NodePosition pos;
    s32 i;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk144 = 0x1C;
        gCurrentActor->speedY = 0.0f;
        gCurrentActor->drawDistance = 0x7D0;
        gCurrentActor->floorY = 99999.0f;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    }
    if (camIsCutsceneActive() != 0) {
        gCurrentActor->interactionType = 2;
    } else {
        gCurrentActor->interactionType = 1;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    gCurrentActor->speedY += D_80750398;
    if (gCurrentActor->floorY != 99999.0f) {
        billboardSetFlags(1);
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x18, 0x18, 1, 0x96, 0xB4, 0, 1.0f);
    } else {
        actorDespawn(gCurrentActor);
    }
    if (gActorGlobalState.bossFightPhase == 4 || gCurrentActor->hasArcBounds != 0
        || ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1))) {
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

    sub = gCurrentActor->parentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags &= 0xFFFF7FFF;
        gCurrentActor->alpha = 0xFF;
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        gCurrentActor->splineT = (f64) gCurrentActor->parentActor->eyeHeight * 0.1 * 0.15;
    }
    gCurrentActor->x = gCurrentActor->parentActor->x;
    gCurrentActor->y = gCurrentActor->parentActor->y;
    gCurrentActor->z = gCurrentActor->parentActor->z;
    if (gCurrentActor->alpha & 8) {
        gCurrentActor->sub4->scaleX = (gCurrentActor->splineT * 0.8 - gCurrentActor->sub4->scaleX) * 0.3 + gCurrentActor->sub4->scaleX;
    } else {
        gCurrentActor->sub4->scaleX = (gCurrentActor->splineT * 1.2 - gCurrentActor->sub4->scaleX) * 0.3 + gCurrentActor->sub4->scaleX;
    }
    gCurrentActor->sub4->scaleZ = gCurrentActor->sub4->scaleX;
    gCurrentActor->alpha = MIN(MAX(sub->unk200, 0), 0xFF);
    if (gCurrentActor->alpha == 0 || gCurrentActor->parentActor->state != 0x7C) {
        actorDespawn(gCurrentActor);
    } else {
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}


void actorSpawnAttachedTo(Actor *arg0) {
    actorSpawn(0x6A, controllerLookupStateByHash(arg0));
    gSpawnedActor->parentActor = arg0;
    arg0->contactFlags |= 0x800;
}

extern u8 gGfxBufferIndex;

typedef struct MirrorActorState {
    /* 0x00 */ Actor *parent;
    /* 0x04 */ s32 parentInstanceId;
    /* 0x08 */ u32 parentType;
    /* 0x0C */ s16 planeOffset;
    /* 0x0E */ u8 axisFlags;
    /* 0x0F */ u8 alpha;
} MirrorActorState;

void actorMirrorParentModelY(void) {
    Mtx mtxL;
    float mtx1[4][4];
    float mtx3[4][4];
    float mtx2[4][4];
    MirrorActorState *sub;
    Mtx *dst;
    s32 i;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x8100000;
        gCurrentActor->flags &= 0xFFFF7FFF;
        controllerAnimLoadStateAsset1(gCurrentActor, controllerLookupStateByHash(gCurrentActor));
        sub->parentInstanceId = gCurrentActor->parentActor->instanceId;
        sub->parent = gCurrentActor->parentActor;
        sub->parentType = gCurrentActor->parentActor->actorType;
    }
    if (!actorTableContains(sub->parent) || sub->parentInstanceId != gCurrentActor->parentActor->instanceId) {
        actorDespawn(gCurrentActor);
        return;
    }
    if (!(func_80665AAC(sub->parent) && sub->parentType == gCurrentActor->parentActor->actorType
          && actorIsActive(sub->parent) && (sub->parent->flags2 & 0x40))) {
        actorDespawn(gCurrentActor);
        sub->parent->contactFlags &= 0xF7FF;
        return;
    }
    gCurrentActor->alpha = 0xFF;
    gCurrentActor->unk146 = sub->parent->unk146;
    gCurrentActor->x = sub->parent->x;
    gCurrentActor->y = sub->parent->y;
    gCurrentActor->unkA8 = sub->parent->unkA8;
    gCurrentActor->z = sub->parent->z;
    gCurrentActor->flags |= 0x200;
    gCurrentActor->boneMtx = gCurrentActor->sub4->boneMtx[gGfxBufferIndex];
    memcpy(gCurrentActor->boneMtx, gCurrentActor->parentActor->boneMtx, ((ActorModel *)gCurrentActor->animState)->unk20 << 6);
    guMtxIdentF(mtx1);
    mtx1[1][1] = -1.0f;
    guTranslateF(mtx2, -gCurrentActor->x, -gCurrentActor->unkA8, -gCurrentActor->z);
    guMtxCatF(mtx2, mtx1, mtx1);
    guMtxF2L(mtx1, &mtxL);
    guTranslateF(mtx2, gCurrentActor->x, gCurrentActor->unkA8, gCurrentActor->z);
    dst = gCurrentActor->boneMtx;
    for (i = 0; i < ((ActorModel *)gCurrentActor->animState)->unk20; i++) {
        guMtxL2F(mtx3, dst);
        guMtxCatF(mtx3, mtx1, mtx3);
        guMtxCatF(mtx3, mtx2, mtx3);
        guMtxF2L(mtx3, dst);
        dst++;
    }
}



void actorMirrorParentModelAxis(void) {
    Mtx mtxL;
    float mtx1[4][4];
    float mtx3[4][4];
    float mtx2[4][4];
    MirrorActorState *sub;
    Mtx *dst;
    s32 i;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x8100000;
        gCurrentActor->flags &= 0xFFFF7FFF;
        controllerAnimLoadStateAsset1(gCurrentActor, controllerLookupStateByHash(gCurrentActor));
        sub->parentInstanceId = gCurrentActor->parentActor->instanceId;
        sub->parent = gCurrentActor->parentActor;
        sub->parentType = gCurrentActor->parentActor->actorType;
    }
    if (!actorTableContains(sub->parent) || sub->parentInstanceId != gCurrentActor->parentActor->instanceId) {
        actorDespawn(gCurrentActor);
        triggerZoneRemoveSpawned(gCurrentActor);
        return;
    }
    if (!(sub->parentType == gCurrentActor->parentActor->actorType && actorIsActive(sub->parent)
          && (sub->parent->flags2 & 0x80))) {
        actorDespawn(gCurrentActor);
        triggerZoneRemoveSpawned(gCurrentActor);
        sub->parent->unk156--;
        return;
    }
    gCurrentActor->alpha = sub->alpha;
    gCurrentActor->unk146 = gCurrentActor->parentActor->unk146;
    gCurrentActor->x = gCurrentActor->parentActor->x;
    gCurrentActor->y = gCurrentActor->parentActor->y;
    gCurrentActor->unkA8 = gCurrentActor->parentActor->unkA8;
    gCurrentActor->z = gCurrentActor->parentActor->z;
    gCurrentActor->flags |= 0x200;
    gCurrentActor->boneMtx = gCurrentActor->sub4->boneMtx[gGfxBufferIndex];
    memcpy(gCurrentActor->boneMtx, gCurrentActor->parentActor->boneMtx, ((ActorModel *)gCurrentActor->animState)->unk20 << 6);
    guMtxIdentF(mtx1);
    if (sub->axisFlags & 1) {
        mtx1[0][0] = -1.0f;
        guTranslateF(mtx2, -sub->planeOffset, 0.0f, 0.0f);
        guMtxCatF(mtx2, mtx1, mtx1);
        guMtxF2L(mtx1, &mtxL);
        guTranslateF(mtx2, sub->planeOffset, 0.0f, 0.0f);
    } else {
        mtx1[2][2] = -1.0f;
        guTranslateF(mtx2, 0.0f, 0.0f, -sub->planeOffset);
        guMtxCatF(mtx2, mtx1, mtx1);
        guMtxF2L(mtx1, &mtxL);
        guTranslateF(mtx2, 0.0f, 0.0f, sub->planeOffset);
    }
    dst = gCurrentActor->boneMtx;
    for (i = 0; i < ((ActorModel *)gCurrentActor->animState)->unk20; i++) {
        guMtxL2F(mtx3, dst);
        guMtxCatF(mtx3, mtx1, mtx3);
        guMtxCatF(mtx3, mtx2, mtx3);
        guMtxF2L(mtx3, dst);
        dst++;
    }
    {
        f32 localX;
        f32 localY;
        f32 localZ;

        guMtxXFMF(mtx1, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, &localX, &localY, &localZ);
        guMtxXFMF(mtx2, localX, localY, localZ, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
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
            actor->unk155 = 0;
        }
    }
}

typedef struct MatrixArray {
    f32 *unk0;
} MatrixArray;

void actorSetNodeValuesForFrame(MatrixArray *arg0) {
    BoneVector *dst;
    s16 i;

    dst = gCurrentActor->sub4->boneOffsets;
    for (i = 0; i < 7; i++) {
        dst->z = (f64) arg0->unk0[i * 0x34 + gCurrentActor->yawSpeed];
        dst++;
    }
}

f32 mathCosF(s16);
extern u8 D_807503D4[];
extern u8 D_807503E0[];


void func_806A112C(void) {
    SubStateView *sub;
    s16 i;
    u8 n;
    f32 d;
    f32 val;
    SubStateView *sub2;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x400;
        func_80724D28(0, 7);
        for (i = 0; i < 7; i++) {
            ((u8 *) gCurrentActor->sub4->boneOffsets)[i * 0x10] = i;
            ((u8 *) gCurrentActor->sub4->boneOffsets)[i * 0x10 + 1] = 0xFF;
        }
        if (gCurrentActor->unk15F == 0) {
            val = (f32) ((f64) gCurrentActor->sub4->scaleY / 0.15);
            sub->unk0 = assetLoad(0x13, 6, 1, 1);
            n = 0;
            animSetChannelFrames(gCurrentActor, D_807503D4[n], D_807503E0[n++]);
            d = 75.0f * val;
            for (i = 1; i < 12; i++) {
                actorSpawn(0x94, 0xE1);
                sub2 = gSpawnedActor->customState;
                sub2->unk0 = sub->unk0;
                gSpawnedActor->unk15F = i;
                gSpawnedActor->yaw = gCurrentActor->yaw + ((u16)(i / 3) << 10);
                gSpawnedActor->x = gCurrentActor->x -
                    mathSinF(gSpawnedActor->yaw) * d;
                gSpawnedActor->y = gCurrentActor->y +
                    (f32) ((u8) (i % 3) * 17);
                gSpawnedActor->z = gCurrentActor->z -
                    mathCosF(gSpawnedActor->yaw) * d;
                actorSetUniformScale(gSpawnedActor, gCurrentActor->sub4->scaleY);
                animSetChannelFrames(gSpawnedActor, D_807503D4[n], D_807503E0[n++]);
            }
            gCurrentActor->x -= d * mathSinF(gCurrentActor->yaw);
            gCurrentActor->z -= d * mathCosF(gCurrentActor->yaw);
        }
    }
    switch (gCurrentActor->state) {
    case 1:
        gCurrentActor->yawSpeed++;
        if (gCurrentActor->yawSpeed == 7) {
            gCurrentActor->state++;
            gCurrentActor->yawSpeed = 0;
        }
        break;
    case 2:
        actorSetNodeValuesForFrame((MatrixArray *) sub);
        gCurrentActor->yawSpeed++;
        if (gCurrentActor->yawSpeed == 11) {
            gCurrentActor->state++;
        }
        break;
    case 3:
        actorSetNodeValuesForFrame((MatrixArray *) sub);
        gCurrentActor->yawSpeed++;
        if (gCurrentActor->yawSpeed >= 52) {
            gCurrentActor->yawSpeed = ((randomNonNegative() >> 15) % 1000) % 3;
            gCurrentActor->state = 0;
        }
        break;
    case 10:
        gCurrentActor->yawSpeed = 11;
        actorSetNodeValuesForFrame((MatrixArray *) sub);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
