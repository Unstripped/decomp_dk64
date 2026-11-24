#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/61AA0_render_caches.h"
#include "proto/global/8CA50_anim_list.h"
#include "proto/global/8F050_actor_config.h"

// Per-actor-type override-model rule (actorProximityUpdate): mode 0 = multiplayer anim frame,
// 1 = load the override model beyond `range`, 2 = load it within `range`.
typedef struct ActorOverrideModelConfig {
    s16 actorType;
    s16 modelAssetId;
    f32 range;
    u8 mode;
    u8 unk9;
    s16 unkA;
    s32 animSlots[2];
} ActorOverrideModelConfig;

// This TU's .data (0x80750100-0x8075018C + 4-byte TU pad).
ActorOverrideModelConfig gActorOverrideModelConfigs[7] = {
    { 178, 25, 200.0f, 1, 0, 0, { -1, -1 } },
    { 2, 5, 200.0f, 0, 0, 0, { 1, 2 } },
    { 3, 3, 200.0f, 0, 0, 0, { 2, -1 } },
    { 6, 15, 200.0f, 0, 0, 0, { 1, 2 } },
    { 4, 8, 200.0f, 0, 0, 0, { 1, -1 } },
    { 5, 11, 200.0f, 0, 0, 0, { 1, 2 } },
    { 7, 219, 200.0f, 0, 0, 0, { 1, -1 } },
};


void animStopAtFrame(Actor *actor, s32 animSlot, s32 frame) {
    animSetLoopLimit(actor, animSlot, -1);
    animSetFinished(actor, animSlot, 1);
    animSetFrameAndSubframe(actor, animSlot, frame, 0.0f);
}

s32 actorConfigLookup(s32 actorType, s32 *outIndex) {
    s32 found;

    found = 0;
    *outIndex = 0;
    do {
        if (actorType == gActorOverrideModelConfigs[*outIndex].actorType) {
            found = 1;
        } else {
            (*outIndex)++;
        }
    } while (*outIndex < sizeof(gActorOverrideModelConfigs) / sizeof(gActorOverrideModelConfigs[0]) && !found);
    return found;
}

void actorConfigApplyAnimFrame(Actor *actor, s32 cfgIndex, s32 frame) {
    s32 i;
    s32 animSlot;

    if (actor->overrideModel == NULL) {
        actor->overrideModel = controllerAnimStateLoadAsset(actor, gActorOverrideModelConfigs[cfgIndex].modelAssetId, 0);
    }
    for (i = 0; i < 2; i++) {
        animSlot = gActorOverrideModelConfigs[cfgIndex].animSlots[i];
        if (animSlot != -1) {
            animStopAtFrame(actor, animSlot, frame);
        }
    }
}


void actorConfigApplyAnimFrameByType(Actor *actor, s32 actorType, s32 frame) {
    s32 cfgIndex;

    if (actorConfigLookup(actorType, &cfgIndex)) {
        actorConfigApplyAnimFrame(actor, cfgIndex, frame);
    }
}

extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;


void actorProximityUpdate(void) {
    PlayerState *playerState;
    s32 cfgIndex;
    s32 pad[3];
    s32 i;
    Actor *actor;
    f32 distSq;
    f32 scaledRange;
    s32 frame;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x2000) && (actor->flags & 0x100)) {
            distSq = ((actor->z - gPlayerSlots->camZ) * (actor->z - gPlayerSlots->camZ)) +
                     (((actor->x - gPlayerSlots->camX) * (actor->x - gPlayerSlots->camX)) +
                      ((actor->y - gPlayerSlots->camY) * (actor->y - gPlayerSlots->camY)));
            if (actorConfigLookup(actor->actorType, &cfgIndex) != 0) {
                scaledRange = renderScaleDistanceByFov(gActorOverrideModelConfigs[cfgIndex].range);
                switch (gActorOverrideModelConfigs[cfgIndex].mode) {
                case 0:
                    if (gPlayerCount >= 2) {
                        playerState = actor->customState;
                        frame = gMpSettings.playerControllerSlots[playerState->playerIndex];
                        if (frame >= 0) {
                            actorConfigApplyAnimFrame(actor, cfgIndex, frame);
                        }
                    }
                    break;
                case 1:
                    if (scaledRange * scaledRange < distSq) {
                        if (actor->overrideModel == NULL) {
                            actor->overrideModel = controllerAnimStateLoadAsset(actor, gActorOverrideModelConfigs[cfgIndex].modelAssetId, 0);
                        }
                    } else if (actor->overrideModel != NULL) {
                        controllerAnimFreeModel(actor, 1);
                    }
                    break;
                case 2:
                    if (distSq < scaledRange * scaledRange) {
                        if (actor->overrideModel == NULL) {
                            actor->overrideModel = controllerAnimStateLoadAsset(actor, gActorOverrideModelConfigs[cfgIndex].modelAssetId, 0);
                        }
                    } else if (actor->overrideModel != NULL) {
                        controllerAnimFreeModel(actor, 1);
                    }
                    break;
                }
            }
        }
    }
}

void actorSetSegmentFlag(Actor *actor, u8 bit) {
    actor->segmentFlags |= (1 << bit);
}

void actorClearSegmentFlag(Actor *actor, u8 bit) {
    actor->segmentFlags &= ~(1 << bit);
}
