#include "common.h"
#define PROTO_SKIP_controllerAnimFreeSub // FAKE: callee prototype steer (header has K&R decl)
#include "actor.h"
#include "sched.h"
#include "proto/global/17B90.h"
#include "proto/global/61AA0.h"
#include "proto/global/8CA50.h"
#include "proto/global/8F050.h"

typedef struct ActorConfig8F050 {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    u8 unk8;
    u8 unk9;
    s16 unkA;
    s32 unkC[2];
} ActorConfig8F050;

extern ActorConfig8F050 D_80750100[];


void animStopAtFrame(Actor *actor, s32 animSlot, s32 frame) {
    animSetLoopLimit(actor, animSlot, -1);
    animSetFinished(actor, animSlot, 1);
    animSetFrameAndSubframe(actor, animSlot, frame, 0.0f);
}

s32 actorConfigLookup(s32 actorType, s32 *outIndex) {
    ActorConfig8F050 *cfg;
    s32 found;
    u32 i;
    u32 next;

    if (actorType && actorType && actorType) {} // FAKE: extra uses keep actorType in $a0 (no uopt move $a2,$a0)
    cfg = D_80750100;
    found = 0;
    *outIndex = 0;
    i = 0; do { // FAKE: same line puts move v0,zero after the %lo addiu (as1 line-ordered schedule)
        next = i + 1;
        if (actorType == cfg[i].unk0) {
            found = 1;
            next = i;
        } else {
            *outIndex = next;
            i = next;
        }
    } while (next < 7 && !found);
    return found;
}

void actorConfigApplyAnimFrame(Actor *actor, s32 cfgIndex, s32 frame) {
    s32 i;
    s32 animSlot;

    if (actor->overrideModel == NULL) {
        actor->overrideModel = controllerAnimStateLoadAsset(actor, D_80750100[cfgIndex].unk2, 0);
    }
    for (i = 0; i < 2; i++) {
        animSlot = D_80750100[cfgIndex].unkC[i];
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

typedef struct ProximityActorEntry {
    Actor *actor;
    u32 unk4;
} ProximityActorEntry;

extern u16 gActiveActorCount;
extern ProximityActorEntry gActiveActors[];
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern s32 D_807552F4[];

void controllerAnimFreeSub(Actor *, u8); // FAKE: callee prototype steer (header has K&R decl)

void actorProximityUpdate(void) {
    PlayerState *playerState;
    s32 cfgIndex;
    s32 pad[3];
    s32 i;
    Actor *actor;
    f32 dist_sq;
    f32 r;
    s32 frame;

    for (i = 0; i < (s32)gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x2000) && (actor->flags & 0x100)) {
            dist_sq = ((actor->z - gPlayerSlots->camZ) * (actor->z - gPlayerSlots->camZ)) +
                      (((actor->x - gPlayerSlots->camX) * (actor->x - gPlayerSlots->camX)) +
                       ((actor->y - gPlayerSlots->camY) * (actor->y - gPlayerSlots->camY)));
            if (actorConfigLookup(actor->actorType, &cfgIndex) != 0) {
                r = renderScaleDistanceByFov(D_80750100[cfgIndex].unk4);
                switch (D_80750100[cfgIndex].unk8) {
                case 0:
                    if (gPlayerCount >= 2) {
                        playerState = actor->customState;
                        frame = D_807552F4[playerState->playerIndex];
                        if (frame >= 0) {
                            actorConfigApplyAnimFrame(actor, cfgIndex, frame);
                        }
                    }
                    break;
                case 1:
                    if (r * r < dist_sq) {
                        if (actor->overrideModel == NULL) {
                            actor->overrideModel = controllerAnimStateLoadAsset(actor, D_80750100[cfgIndex].unk2, 0);
                        }
                    } else if (actor->overrideModel != NULL) {
                        controllerAnimFreeSub(actor, 1);
                    }
                    break;
                case 2:
                    if (dist_sq < r * r) {
                        if (actor->overrideModel == NULL) {
                            actor->overrideModel = controllerAnimStateLoadAsset(actor, D_80750100[cfgIndex].unk2, 0);
                        }
                    } else if (actor->overrideModel != NULL) {
                        controllerAnimFreeSub(actor, 1);
                    }
                    break;
                }
            }
        }
    }
}

void func_8068A764(Actor *actor, u8 bit) {
    actor->unk146 |= (1 << bit);
}

void func_8068A784(Actor *actor, u8 bit) {
    actor->unk146 &= ~(1 << bit);
}
