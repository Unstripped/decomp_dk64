#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "sched.h"
#include "proto/boot/3D20_sprintf.h"
#include "proto/global/100180_text_font.h"
#include "proto/global/103AB0_view_effects.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/11BC10_effect_update.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/15050_heap.h"
#include "proto/global/166A0_random.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/61AA0_render_caches.h"
#include "proto/global/684C0_trigger_zone.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/6AD90_collision.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/8CA50_anim_list.h"
#include "proto/global/8D3E0_actor_list.h"
#include "proto/global/90D80_render_callbacks.h"
#include "proto/global/A2F10.h"
#include "proto/global/AA960_pickup_drops.h"
#include "proto/global/EFDC0_player_state_enter.h"

// This TU's .data (0x807503B0-0x807503EC + 4-byte TU pad), in address order. actorBannerTextRender reads the
// name table D_807503B0 for banner ids 0x1E..0x26.
extern const char D_8075A410[];
extern const char D_8075A418[];
extern const char D_8075A420[];
extern const char D_8075A428[];
extern const char D_8075A430[];
extern const char D_8075A438[];
extern const char D_8075A440[];
extern const char D_8075A444[];
extern const char D_8075A44C[];
const char *D_807503B0[9] = {
    D_8075A410, D_8075A418, D_8075A420, D_8075A428, D_8075A430,
    D_8075A438, D_8075A440, D_8075A444, D_8075A44C,
};
u8 gActorGroupFirstAnimFrames[12] = { 1, 1, 1, 0, 0, 0, 2, 2, 2, 3, 3, 3 };
u8 gActorGroupSecondAnimFrames[12] = { 2, 2, 2, 0, 0, 0, 3, 3, 3, 1, 1, 1 };

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern u32 gFrameDelta;
extern u8 gBossRoundNumber;

#define WRITE_GFX(pkt, _w0, _w1)                                               \
    {                                                                          \
        Gfx *_g = (Gfx *)(pkt);                                                \
        _g->words.w0 = (_w0);                                                  \
        _g->words.w1 = (_w1);                                                  \
    }


void actorTriggerRampWithSfx(void) {
    Actor *actor;
    s16 i;
    s16 *event;
    u32 flags;

    actor = gCurrentActor;
    if (!(actor->flags & 0x10)) {
        actor->flags &= ~4;
        controllerAnimSetStateIfChanged(gCurrentActor, 0x407, 0.0f, 0.0f);
        scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
        actor = gCurrentActor;
    }
    for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
        event = gActorGlobalState.volumeTriggerQueueId[i];
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
    if (actor->sub4->model->speed == 0.0f) {
        actor->flags &= ~4;
    }
    actor = gCurrentActor;
    actorUpdateModelMatrix(actor, 0);
}

void actorSpawnNodeEntryAtActor(s32 actorType, s16 roll) {
    Actor *actor;

    actor = gCurrentActor;
    actorSpawnNodeEntryScaled(actorType, actor->x, actor->y, actor->z, 0, 0, roll, actor);
}

void actorPlaceAttachedChildren(s16 yOffset) {
    Actor *actor;
    s16 i;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (actor->parentActor == gCurrentActor) {
            actorAppendMoveTarget3D(gCurrentActor, actor, gCurrentActor->x,
                                           gCurrentActor->y + (f32)yOffset, gCurrentActor->z, 2, 1);
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

int actorIsTargetInRange(Actor *target, f32 height, f32 rangeSq) {
    return target->y - 8.0f <= gCurrentActor->y &&
           gCurrentActor->y < target->y + height &&
           rangeSq > (target->x - gCurrentActor->x) *
                      (target->x - gCurrentActor->x) +
                  (target->z - gCurrentActor->z) *
                      (target->z - gCurrentActor->z) &&
           target->collisionMode != 1;
}

s32 actorTypeToNodeIndex(s32 actorType) {
    switch (actorType) {
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
    /* 0x000 */ f32 radiusScale;
    /* 0x004 */ u8 pad4[8];
    /* 0x00C */ u16 hostRadius;
    /* 0x00E */ u8 padE[2];
    /* 0x010 */ u8 red;
    /* 0x011 */ u8 green;
    /* 0x012 */ u8 blue;
} LightPulseState;

extern u8 gSplitScreenMode;
extern s32 gCurrentMap;
extern u8 gPlayerCount;
extern PlayerStruct *gPlayerSlots;


void actorLightPulseUpdate(void) {
    u16 lightRadius;
    f32 rangeSq;
    u8 despawned;
    PlayerState *hostState;
    u8 isAttached;
    Actor *host;
    s32 *hostFlags;
    LightPulseState *light;
    Actor *attachedTo;
    f32 wobble;
    PlayerState *playerState;
    s32 callbackId;
    s32 i;
    Actor *target;

    lightRadius = 0x12C;
    despawned = 0;
    isAttached = 0;
    attachedTo = gCurrentActor->parentActor;
    light = gCurrentActor->customState;
    if (attachedTo != NULL && (attachedTo->collisionFlags & 1)) {
        host = attachedTo;
        isAttached = 1;
    } else {
        host = gPrimaryPlayerActor;
    }
    hostState = host->customState;
    if (gPlayerCount >= 2 && gSplitScreenMode == 1) {
        playerState = gPrimaryPlayerActor->customState;
        hostFlags = &playerState->stateFlags;
    } else {
        hostFlags = &hostState->stateFlags;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        light->hostRadius = host->collision->radius;
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
        switch (controllerLookupModelAssetId(gCurrentActor)) {
        case 0xAD:
            light->red = 0xFF;
            light->green = 0xFF;
            light->blue = 0x32;
            break;
        case 0xAE:
            light->red = 0xFF;
            light->green = 0x32;
            light->blue = 0x32;
            break;
        case 0xD1:
            light->red = 0xCA;
            light->green = 0x5B;
            light->blue = 0xFF;
            break;
        case 0xD0:
            light->red = 0;
            light->green = 0x96;
            light->blue = 0xFF;
            break;
        case 0xCF:
            light->red = 0x32;
            light->green = 0xFF;
            light->blue = 0x32;
            break;
        }
        if (isAttached) {
            light->radiusScale = 2.0f;
        } else {
            light->radiusScale = 1.5f;
        }
        if (gCurrentActor->hasOwnHitNode != 0) {
            actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 1.0f, 0);
        }
    }
    if (camIsCutsceneActive() != 0) {
        camStartShake(hostState->camActor, 0xA, 0xA);
    }
    gCurrentActor->sub4->scaleX *= gCurrentActor->splineT;
    gCurrentActor->sub4->scaleZ = gCurrentActor->sub4->scaleX;
    gCurrentActor->sub4->scaleY *= 1.04;
    wobble = mathSinF(gCurrentActor->moveYaw);
    gCurrentActor->sub4->scaleY += 0.01 * wobble;
    gCurrentActor->moveYaw += 0x1F4;
    gCurrentActor->yaw += 0x32;
    gCurrentActor->state++;
    if (gCurrentActor->state == gCurrentActor->yawSpeed) {
        animSetFinished(gCurrentActor, 0, 0);
    } else if (gCurrentActor->yawSpeed < gCurrentActor->state) {
        lightRadius = 0x12C - (gCurrentActor->state - gCurrentActor->yawSpeed) * 0x28;
        if (animIsPlaying(gCurrentActor, 0) == 0) {
            despawned = 1;
            *hostFlags &= ~0x02000000;
            actorSetCollisionRadius(host, light->hostRadius);
            actorGetOrSetNodeScale(host, actorTypeToNodeIndex(host->actorType), 0.0f);
            actorDespawn(gCurrentActor);
        }
    }
    lightSetFlags(1);
    lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f,
             0.0f, 0.0f, gCurrentActor->sub4->scaleX * lightRadius * light->radiusScale, 0,
             light->red, light->green, light->blue);
    if (gCurrentMap != 0x4C) {
        if (!isAttached || gCurrentActor->hasOwnHitNode != 0) {
            callbackId = 0x2E;
            if (mpIsMatchType(0) != 0) {
                callbackId = 0xE;
            }
            rangeSq = gCurrentActor->sub4->scaleX * lightRadius;
            rangeSq = rangeSq * rangeSq;
            for (i = 0; i < gPlayerCount; i++) {
                target = gPlayerSlots[i].actor;
                if (isAttached &&
                    (i == hostState->playerIndex || target->state == 0x84)) {
                    continue;
                }
                if (actorIsTargetInRange(target, target->eyeHeight, rangeSq) != 0) {
                    playerStateQueueCallback(callbackId, gCurrentActor, i);
                }
            }
            if (gCurrentActor->hasOwnHitNode != 0) {
                actorSetCollisionRadius(
                    gCurrentActor,
                    2.0 * ((gCurrentActor->sub4->scaleX * lightRadius) * 6.66666667));
                actorGetOrSetNodeScale(
                    gCurrentActor, 1,
                    (gCurrentActor->sub4->scaleX * lightRadius) * 6.66666667);
            }
        } else if (despawned == 0) {
            actorSetCollisionRadius(
                gCurrentActor->parentActor,
                2.0 * ((gCurrentActor->sub4->scaleX * lightRadius) * 6.66666667));
            actorGetOrSetNodeScale(
                gCurrentActor->parentActor, actorTypeToNodeIndex(host->actorType),
                (gCurrentActor->sub4->scaleX * lightRadius) * 6.66666667);
            actorOrNodeFlags(host, actorTypeToNodeIndex(host->actorType), 3);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


s32 actorIsTargetInCylinder(s16 x, s16 y, s16 z, s16 height, f32 radius) {
    Actor *actor;
    f32 dx;
    f32 dz;

    actor = gPrimaryPlayerActor;
    dx = actor->x - x;
    dz = actor->z - z;
    if (dx * dx + dz * dz < radius * radius && y <= actor->y &&
        actor->y < y + height) {
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
                 (u32)(gCurrentActor->tintR * fade),
                 (u32)(gCurrentActor->tintG * fade),
                 (u32)(gCurrentActor->tintB * fade));
        gCurrentActor->sub4->scaleX = gCurrentActor->sub4->scaleX * gCurrentActor->splineT;
        gCurrentActor->sub4->scaleZ = gCurrentActor->sub4->scaleZ * gCurrentActor->splineT;
    }
    switch (gCurrentActor->state) {
    case 0:
        if (gCurrentActor->yawSpeed == 0) {
            gCurrentActor->sub4->scaleX =
                gCurrentActor->sub4->scaleX * gCurrentActor->splineT;
            gCurrentActor->sub4->scaleZ =
                gCurrentActor->sub4->scaleZ * gCurrentActor->splineT;
        }
        if (gCurrentActor->sub4->model->speed == 0.0f ||
            gCurrentActor->sub4->model->frame > 5.0f) {
            gCurrentActor->state = 1;
            animSetFinished(gCurrentActor, 0, 0);
        }
        break;
    case 1:
        if ((gCurrentActor->sub4->model->speed == 0.0f && animGetNodeByIndex(gCurrentActor, 0)->frame >= 0xE) ||
            gCurrentActor->sub4->model->frame > 9.0f) {
            gCurrentActor->state = 2;
            if (gCurrentActor->wavesLeft != 0 && actorSpawn(0x102, gCurrentActor->movePitch) != 0) {
                if (gCurrentActor->sub4->model->frame > 9.0f) {
                    controllerAnimSetStateIfChanged(gSpawnedActor, 0x4F9, 0.0f, 0.0f);
                    scriptSetActorRampTarget(gSpawnedActor, gCurrentActor->sub4->speed, 0.0f);
                }
                actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleY);
                gSpawnedActor->movePitch = gCurrentActor->movePitch;
                gSpawnedActor->sub4->scaleX = gCurrentActor->sub4->scaleX + 0.02;
                gSpawnedActor->sub4->scaleZ = gCurrentActor->sub4->scaleZ + 0.02;
                gSpawnedActor->wavesLeft = gCurrentActor->wavesLeft - 1;
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
        if (actorIsTargetInCylinder(gCurrentActor->x, gCurrentActor->y - 20.0f,
                          gCurrentActor->z, height,
                          gCurrentActor->sub4->scaleX * (f32)radius) != 0 &&
            actorIsTargetInCylinder(gCurrentActor->x, gCurrentActor->y - 20.0f,
                          gCurrentActor->z, height,
                          gCurrentActor->sub4->scaleX * (f32)(radius - 0x14)) == 0) {
            playerStateQueueCallback(0x2E, gCurrentActor, 0);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


Gfx *renderScaledSprite(Gfx *dl, Actor *actor) {
    f32 scale;

    scale = actor->floorSlopeFactor;
    gSPDisplayList(dl++, &D_1000118);
    gDPSetCombineMode(dl++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gSPMatrix(dl++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, actor->yaw);
    return renderRotatedSprite(dl, actor->bannerId + 0x61, 0, 2, 0x28, 0x33, actor->x, actor->y, scale, scale, 0, 0.0f);
}

const char D_8075A410[7] = "DONKEY";
const char D_8075A418[6] = "DIDDY";
const char D_8075A420[6] = "LANKY";
const char D_8075A428[5] = "TINY";
const char D_8075A430[7] = "CHUNKY";
const char D_8075A438[5] = "KING";
const char D_8075A440[3] = "K.";
const char D_8075A444[5] = "ROOL";
const char D_8075A44C[5] = "KONG";

Gfx *actorBannerTextRender(Gfx *dl, Actor *actor) {
    f32 scale;
    f32 mtx[4][4];
    f32 translate[4][4];
    Mtx *mtxBuf;
    u8 text[0x10];
    s16 width;
    u8 font;
    u8 centered;
    f64 size;
    s32 sel;

    if (actor->floorSlopeFactor - 2.0 < 0.01) {
        size = 0.01;
    } else {
        size = actor->floorSlopeFactor - 2.0;
    }
    scale = size * 0.3;
    centered = 0;
    WRITE_GFX(dl++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(dl++, 0xE200001C, 0x00504240);
    WRITE_GFX(dl++, 0xE7000000, 0);
    WRITE_GFX(dl++, 0xFA000000, (actor->yaw & 0xFF) | 0xFFFFFF00);
    dl = playerViewSetPrimaryViewport(dl);
    mtxBuf = heapAlloc(0x40);
    heapFreeDeferred(mtxBuf);
    font = 1;
    sel = actor->bannerId;
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
        _sprintf(text, D_807503B0[sel - 0x1E]);
        break;
    default:
        if (sel & 0x80) {
            font = 3;
            scale = 4.0 - scale;
            _sprintf(text, "%d", 0xA - (sel & 0x3F));
        } else if (sel & 0x40) {
            font = 3;
            scale = 4.0 - scale;
            _sprintf(text, "%d", 8 - (sel & 0x3F));
        } else {
            _sprintf(text, "%d", sel);
        }
        break;
    }
    width = textGetStringWidth(font, text);
    if (centered != 0) {
        actor->x = (0x140 - width) << 1;
    }
    guScaleF(mtx, scale, scale, 1.0f);
    guTranslateF(translate, actor->x + 2.0 * width, actor->y * 4.0f, 0.0f);
    guMtxCatF(mtx, translate, mtx);
    guMtxF2L(mtx, mtxBuf);
    WRITE_GFX(dl++, 0xDA380003, (u32)mtxBuf);
    return textDrawStringVtx(dl, font, width * -2, 0, text, 0);
}
void actorUpdateBannerFade(void) {
    f32 ratio;
    s16 sfx;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->moveYaw = gCurrentActor->splineT;
    }
    if (gFrameDelta * 0.5 < gCurrentActor->splineT) {
        gCurrentActor->splineT -= gFrameDelta * 0.5;
        ratio = gCurrentActor->splineT / (f32)gCurrentActor->moveYaw;
        gCurrentActor->floorSlopeFactor = ratio * -8.0 + 12.0;
        gCurrentActor->yaw = 255.0f * ratio;
        if (gCurrentActor->bannerId >= 0x14 && gCurrentActor->bannerId < 0x1E) {
            renderCallbacksRegister(renderScaledSprite, gCurrentActor, 3);
        } else {
            renderCallbacksRegister(actorBannerTextRender, gCurrentActor, 3);
        }
        if (gCurrentActor->bannerId == 0 && (s16)gCurrentActor->splineT == 3) {
            actorSpawn(0x104, 0);
            gSpawnedActor->splineT = gCurrentActor->moveYaw;
            gSpawnedActor->bannerId = gBossRoundNumber;
            gSpawnedActor->y = 80.0f;
            gSpawnedActor->x = 640.0f;
            sfxPlayOnFreeSlot(gBossRoundNumber + 0x3F3, 0x7FFF, 63.0f, 1.0f, 0, 0);
            return;
        }
        if (gCurrentActor->bannerId >= 0x1E && gCurrentActor->bannerId < 0x25 && (s16)gCurrentActor->splineT == 5) {
            actorSpawn(0x104, 0);
            gSpawnedActor->splineT = gCurrentActor->moveYaw;
            if (gCurrentActor->bannerId == 0x23) {
                gSpawnedActor->bannerId = 0x24;
            } else if (gCurrentActor->bannerId == 0x24) {
                gSpawnedActor->bannerId = 0x25;
            } else {
                gSpawnedActor->bannerId = 0x26;
            }
            gSpawnedActor->y = 80.0f;
            gSpawnedActor->x = 500.0f;
        }
    } else {
        if ((gCurrentActor->bannerId & 0xC0) != 0 && (gCurrentActor->bannerId & 0x3F) != 0) {
            sfx = 0x3FC - (gCurrentActor->bannerId & 0x3F);
            actorSpawn(0x104, 0);
            gSpawnedActor->splineT = gCurrentActor->moveYaw;
            gSpawnedActor->bannerId = (gCurrentActor->bannerId & 0xC0) + (gCurrentActor->bannerId & 0x3F) - 1;
            if (gCurrentActor->bannerId & 0x80) {
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
    f32 speedXZ;
    f32 moveYaw;
    f32 speedY;
} LaunchParams;

typedef struct {
    s32 pitchSpeed;
    s32 rollSpeed;
} SpinState;

typedef struct ActorModel {
    /* 0x000 */ u8 pad0[0x20];
    /* 0x020 */ u8 boneCount;
} ActorModel;

extern f32 gSpinningActorGravity;


void actorUpdateSpinAndVelocity(void) {
    SpinState *spin;
    s32 pad;

    spin = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->speedXZ = ((LaunchParams *)gCurrentActor->spawnData)->speedXZ;
        gCurrentActor->moveYaw = ((LaunchParams *)gCurrentActor->spawnData)->moveYaw;
        gCurrentActor->speedY = ((LaunchParams *)gCurrentActor->spawnData)->speedY;
        gCurrentActor->collisionMode = 1;
        spin->pitchSpeed = (randomNonNegative() >> 15) % 0x46;
        spin->rollSpeed = (randomNonNegative() >> 15) % 0xC8;
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    gCurrentActor->speedY += gSpinningActorGravity;
    gCurrentActor->roll += spin->rollSpeed;
    gCurrentActor->pitch += spin->pitchSpeed;
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
    f32 z;
    f32 y;
    f32 x;
    u8 padC[0x24];
} NodePosition;


extern f32 gFallAndBurstGravity;
extern EffectGridAsset gEffectSpriteSmokeCloud;

void actorFallAndBurstUpdate(void) {
    NodePosition pos;
    s32 i;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->collisionMode = 0x1C;
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
    gCurrentActor->speedY += gFallAndBurstGravity;
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
            actorGetNodePos(gCurrentActor, i, &pos.x, &pos.y, &pos.z);
            effectSetStartDelay(i);
            effectSetDepth(1);
            effectSetCallback(effectSpinBillboardingUpdate);
            effectSetColor(0xFF, 0xFF, 0xFF, 0x96);
            effectCreateAtPosition(&gEffectSpriteSmokeCloud, 1.5f, pos.x, pos.y, pos.z);
        }
        actorDespawn(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void actorUpdateModelMatrixCurrent(void) {
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorShadowFollowUpdate(void) {
    PlayerState *parentState;

    parentState = gCurrentActor->parentActor->customState;
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
    gCurrentActor->alpha = MIN(MAX(parentState->statusEffectTimer, 0), 0xFF);
    if (gCurrentActor->alpha == 0 || gCurrentActor->parentActor->state != 0x7C) {
        actorDespawn(gCurrentActor);
    } else {
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}


void actorSpawnAttachedTo(Actor *parent) {
    actorSpawn(0x6A, controllerLookupModelAssetId(parent));
    gSpawnedActor->parentActor = parent;
    parent->contactFlags |= 0x800;
}

extern u8 gGfxBufferIndex;

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
        controllerAnimLoadStateAsset1(gCurrentActor, controllerLookupModelAssetId(gCurrentActor));
        sub->parentInstanceId = gCurrentActor->parentActor->instanceId;
        sub->parent = gCurrentActor->parentActor;
        sub->parentType = gCurrentActor->parentActor->actorType;
    }
    if (!actorTableContains(sub->parent) || sub->parentInstanceId != gCurrentActor->parentActor->instanceId) {
        actorDespawn(gCurrentActor);
        return;
    }
    if (!(actorFloorIsReflective(sub->parent) && sub->parentType == gCurrentActor->parentActor->actorType
          && actorIsActive(sub->parent) && (sub->parent->flags2 & 0x40))) {
        actorDespawn(gCurrentActor);
        sub->parent->contactFlags &= 0xF7FF;
        return;
    }
    gCurrentActor->alpha = 0xFF;
    gCurrentActor->segmentFlags = sub->parent->segmentFlags;
    gCurrentActor->x = sub->parent->x;
    gCurrentActor->y = sub->parent->y;
    gCurrentActor->meshFloorY = sub->parent->meshFloorY;
    gCurrentActor->z = sub->parent->z;
    gCurrentActor->flags |= 0x200;
    gCurrentActor->boneMtx = gCurrentActor->sub4->boneMtx[gGfxBufferIndex];
    memcpy(gCurrentActor->boneMtx, gCurrentActor->parentActor->boneMtx, ((ActorModel *)gCurrentActor->animState)->boneCount << 6);
    guMtxIdentF(mtx1);
    mtx1[1][1] = -1.0f;
    guTranslateF(mtx2, -gCurrentActor->x, -gCurrentActor->meshFloorY, -gCurrentActor->z);
    guMtxCatF(mtx2, mtx1, mtx1);
    guMtxF2L(mtx1, &mtxL);
    guTranslateF(mtx2, gCurrentActor->x, gCurrentActor->meshFloorY, gCurrentActor->z);
    dst = gCurrentActor->boneMtx;
    for (i = 0; i < ((ActorModel *)gCurrentActor->animState)->boneCount; i++) {
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
        controllerAnimLoadStateAsset1(gCurrentActor, controllerLookupModelAssetId(gCurrentActor));
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
        sub->parent->mirrorCount--;
        return;
    }
    gCurrentActor->alpha = sub->alpha;
    gCurrentActor->segmentFlags = gCurrentActor->parentActor->segmentFlags;
    gCurrentActor->x = gCurrentActor->parentActor->x;
    gCurrentActor->y = gCurrentActor->parentActor->y;
    gCurrentActor->meshFloorY = gCurrentActor->parentActor->meshFloorY;
    gCurrentActor->z = gCurrentActor->parentActor->z;
    gCurrentActor->flags |= 0x200;
    gCurrentActor->boneMtx = gCurrentActor->sub4->boneMtx[gGfxBufferIndex];
    memcpy(gCurrentActor->boneMtx, gCurrentActor->parentActor->boneMtx, ((ActorModel *)gCurrentActor->animState)->boneCount << 6);
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
    for (i = 0; i < ((ActorModel *)gCurrentActor->animState)->boneCount; i++) {
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



void animSetChannelFrames(void *actor, u8 frame0, u8 frame1) {
    animSetLoopLimit(actor, 0, 1);
    animSetFinished(actor, 0, 1);
    animSetFrameAndSubframe(actor, 0, frame0, 0.0f);
    animSetLoopLimit(actor, 1, 1);
    animSetFinished(actor, 1, 1);
    animSetFrameAndSubframe(actor, 1, frame1, 0.0f);
}


void actorSetGroupState(u8 group, u8 state) {
    Actor *actor;
    s16 i;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (actor->actorType == 0x94 && actor->formationIndex / 3 == group) {
            actor->state = state;
            actor->subState = 0;
        }
    }
}

typedef struct BoneFrameState {
    f32 *frames;
} BoneFrameState;

void actorSetNodeValuesForFrame(BoneFrameState *state) {
    BoneVector *dst;
    s16 i;

    dst = gCurrentActor->sub4->boneOffsets;
    for (i = 0; i < 7; i++) {
        dst->z = (f64) state->frames[i * 0x34 + gCurrentActor->yawSpeed];
        dst++;
    }
}



void actorGroupBoneFrameUpdate(void) {
    BoneFrameState *state;
    s16 i;
    u8 entry;
    f32 spacing;
    f32 scaleRatio;
    BoneFrameState *childState;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x400;
        actorAllocBoneOffsets(0, 7);
        for (i = 0; i < 7; i++) {
            gCurrentActor->sub4->boneOffsets[i].bone = i;
            gCurrentActor->sub4->boneOffsets[i].lastBone = 0xFF;
        }
        if (gCurrentActor->formationIndex == 0) {
            scaleRatio = gCurrentActor->sub4->scaleY / 0.15;
            state->frames = assetLoad(0x13, 6, 1, 1);
            entry = 0;
            animSetChannelFrames(gCurrentActor, gActorGroupFirstAnimFrames[entry], gActorGroupSecondAnimFrames[entry++]);
            spacing = 75.0f * scaleRatio;
            for (i = 1; i < 12; i++) {
                actorSpawn(0x94, 0xE1);
                childState = gSpawnedActor->customState;
                childState->frames = state->frames;
                gSpawnedActor->formationIndex = i;
                gSpawnedActor->yaw = gCurrentActor->yaw + ((u16)(i / 3) << 10);
                gSpawnedActor->x = gCurrentActor->x - mathSinF(gSpawnedActor->yaw) * spacing;
                gSpawnedActor->y = gCurrentActor->y + (u8)(i % 3) * 17;
                gSpawnedActor->z = gCurrentActor->z - mathCosF(gSpawnedActor->yaw) * spacing;
                actorSetUniformScale(gSpawnedActor, gCurrentActor->sub4->scaleY);
                animSetChannelFrames(gSpawnedActor, gActorGroupFirstAnimFrames[entry], gActorGroupSecondAnimFrames[entry++]);
            }
            gCurrentActor->x -= spacing * mathSinF(gCurrentActor->yaw);
            gCurrentActor->z -= spacing * mathCosF(gCurrentActor->yaw);
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
        actorSetNodeValuesForFrame(state);
        gCurrentActor->yawSpeed++;
        if (gCurrentActor->yawSpeed == 11) {
            gCurrentActor->state++;
        }
        break;
    case 3:
        actorSetNodeValuesForFrame(state);
        gCurrentActor->yawSpeed++;
        if (gCurrentActor->yawSpeed >= 52) {
            gCurrentActor->yawSpeed = ((randomNonNegative() >> 15) % 1000) % 3;
            gCurrentActor->state = 0;
        }
        break;
    case 10:
        gCurrentActor->yawSpeed = 11;
        actorSetNodeValuesForFrame(state);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
