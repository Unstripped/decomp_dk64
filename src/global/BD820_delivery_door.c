#include "common.h"
#include "actor.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/11BC10_effect_update.h"
#include "proto/global/12E800_behaviour.h"
#include "proto/global/166A0_random.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/36880_model_slot.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/63810_light_queue.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/BD820_delivery_door.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

extern void *gPuffSprites[];
extern EffectGridAsset sEffectSparkConfig;


void effectSpawnRandomParticleAtPoint(s16 x, s16 y, s16 z, s16 lifetime) {
    effectSetCallback(effectWispWanderUpdate);
    effectSetDuration(-1);
    effectSetDepth(1);
    effectSetStartDelay(lifetime);
    effectCreateAtPosition(gPuffSprites[(randomNonNegative() >> 15) % 1000 % 3], 1.8f, x, y, z);
}

void effectSpawnSinkingSpark(s16 x, s16 y, s16 z) {
    effectSetFrameDelay(2);
    effectSetCallback(effectSinkBySpeedUpdate);
    effectSetSpeed(-0x28);
    effectSetDepth(1);
    effectSetColor(0xFF, 0xFF, 0xFF, 0xC8);
    effectCreateAtPosition(&sEffectSparkConfig, 2.0f, x, y, z);
}

extern s16 gCsModelIds[];


void bananaDeliveryDoorUnlockSequence(void) {
    f64 t;

    switch (gCurrentActor->state) {
        case 1:
            switch (gCurrentActor->subState) {
                case 0:
                    gCurrentActor->speedY = 0.0f;
                    actorScriptStart(gCurrentActor, 0x290);
                    gCurrentActor->subState++;
                    break;
                case 2:
                    if (gCurrentActor->y > -20.0f) {
                        gCurrentActor->y = gCurrentActor->y - gCurrentActor->speedY;
                    }
                    t = gCurrentActor->speedY + 0.5;
                    gCurrentActor->speedY = (t < 8.0) ? t : 8.0;
                    break;
            }
            break;
        case 2:
            effectSpawnRandomParticleAtPoint(0x258, 0x64, 0x1E5, 0x64);
            effectSpawnRandomParticleAtPoint(0x258, 0x96, 0x1E5, 0x64);
            effectSpawnRandomParticleAtPoint(0x258, 0xC8, 0x1E5, 0x67);
            effectSpawnRandomParticleAtPoint(0x258, 0xFA, 0x1E5, 0x68);
            effectSpawnRandomParticleAtPoint(0x258, 0x12C, 0x1E5, 0x6C);
            effectSpawnRandomParticleAtPoint(0x258, 0x15E, 0x1E5, 0x6E);
            effectSpawnRandomParticleAtPoint(0x258, 0x190, 0x1E5, 0x73);
            effectSpawnRandomParticleAtPoint(0x258, 0x1C2, 0x1E5, 0x74);
            gCurrentActor->state++;
            gBehaviourWorkState->timer = 0x46;
            break;
        case 3:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->state = 0x40;
            }
            if (gBehaviourWorkState->timer < 0x28) {
                modelSlotOrFlags(4, 0x10);
                modelSlotOrFlags(6, 0x10);
                modelSlotClearFlags(5, 0x10);
                modelSlotClearFlags(7, 0x10);
                if ((gBehaviourWorkState->timer < 0x15 && (randomNonNegative() >> 15) % 1000 < 0x12C) || gCurrentActor->state == 0x40) {
                    if (gCurrentActor->state == 0x40) {
                        modelSlotOrFlags(5, 0x10);
                        modelSlotOrFlags(7, 0x10);
                        sfxPlayOnFreeSlot(0x1D0, 0x58EF, 63.0f, 1.0f, 0, 0);
                        sfxAllocateChannel(0x3A, 1.0f);
                        effectSpawnSinkingSpark(0xBD, 0xAA, 0x2FB);
                        effectSpawnSinkingSpark(0x19A, 0xA6, 0x2F8);
                    }
                    actorSetTargetSlotByte(gCsModelIds[4], 0);
                    actorSetTargetSlotByte(gCsModelIds[6], 0);
                    lightSetColor(0.15f, 0.15f, 0.15f, 0);
                } else if (gBehaviourWorkState->timer >= 0x15) {
                    actorSetTargetSlotByte(gCsModelIds[4], 9);
                    actorSetTargetSlotByte(gCsModelIds[6], 9);
                    lightSetColor(0.2f, 0.2f, 0.2f, 0);
                } else {
                    actorSetTargetSlotByte(gCsModelIds[4], 8);
                    actorSetTargetSlotByte(gCsModelIds[6], 8);
                    lightSetColor(0.3f, 0.3f, 0.3f, 0);
                }
            }
            break;
    }
}

void bananaDeliveryDoorLockUpdate(void) {
    s16 i;
    f32 scale;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        scale = (gBehaviourExtraState->scale / 255.0) * 0.75;
        gCurrentActor->sub4->scaleX = scale;
        gCurrentActor->sub4->scaleY = scale;
        gCurrentActor->sub4->scaleZ = scale;
        if (mapHasCollectedSufficientItems() != 0) {
            gCurrentActor->state = 0x40;
        } else {
            gCurrentActor->drawDistance = 0x3E8;
            gCurrentActor->cullMarginX = 0x3C;
            gCurrentActor->cullMarginY = 0x3C;
            controllerAnimSetStateIfChanged(gCurrentActor, 0x482, 0.0f, 0.0f);
        }
        modelSlotOrFlags(5, 0x10);
        modelSlotOrFlags(7, 0x10);
    }
    for (i = 0; i < gActorGlobalState.volumeTriggerQueueCount; i++) {
        if (gActorGlobalState.volumeTriggerQueueOp[i] == 3) {
            gCurrentActor->state = gActorGlobalState.volumeTriggerQueueId[i][1];
            gCurrentActor->subState = 0;
        }
    }
    bananaDeliveryDoorUnlockSequence();
    actorUpdateModelMatrix(gCurrentActor, 0);
}
