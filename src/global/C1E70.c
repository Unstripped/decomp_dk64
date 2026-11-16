#include "common.h"
#include "actor.h"
#define PROTO_SKIP_actorSpawn // PROTO: this call passes a third argument (a2 = &gCurrentActor), the shared prototype takes two
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/42630.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/C1E70.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

extern Actor *gSpawnedActor;
extern s16 D_80744710[];
s8 sRingActiveStarted = 0;
// per ring: the (map, exit) pair menuTransitionToMap loads when that ring's cutscene ends; pair 7
// is the destination once every ring is cleared (rings 2 and 7 never transition, so pair 2 is -1, -1).
// A flat s16 array, not a { map, exit } struct array: the struct indexing shifts the ugen temps (Q0167).
s16 sRingExits[] = { 0x22, 8, 0x22, 7, -1, -1, 0x22, 5, 0x22, 4, 0x22, 0x12, 0x22, 0x12, 0x99, 9 };
// actorScriptStart id the ring node plays when ring [i] is cleared (only [0..7] are read)
s16 sRingNodeScripts[] = { 0x2F2, 0x2F1, 0x2F3, 0x2F2, 0x2F1, 0x2F2, 0x2F2, 0x2F1, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4 };
// set when ring 2 or 7 finishes without leaving the map: the waiting (state 5) active ring may start
s8 sRingNextReady = 0;
extern s8 D_807FC8D0;

s32 actorSpawn();

// customState of the ring actors (type 0xCD) spawned by actorNodeRingSpawnRings
typedef struct RingState {
    /* 0x00 */ s16 timer;
    /* 0x02 */ s8 ringIdx;
    /* 0x04 */ Actor *node;
} RingState;

// second component of the ring node actor: the model actor spawned in actorNodeRingUpdate
typedef struct RingNodeModel {
    /* 0x00 */ Actor *modelActor;
} RingNodeModel;

typedef struct RingNodeActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ RingNodeModel *model;
} RingNodeActor;

void actorNodeRingSpawnRings(void) {
    Actor *activeRingActor;
    s16 i;
    s16 activeRingIdx;
    s16 activeRingCount; // ORIG: the target keeps this never-read counter: move s5,zero at 0x60 and addiu s5,s5,1 + sll/sra at 0x1a8-0x1b8 in the active-ring arm
    s16 angle;
    RingState *ring;

    activeRingIdx = -1;
    i = 0;
    activeRingCount = 0;
    for (; i < 8; i++) { // FAKE: i = 0 written before activeRingCount = 0 (empty for-init) keeps move s1,zero ahead of move s5,zero at 0x5c
        if (flagGet(i + 0x1BC, 0) == 0) {
            actorSpawn(0x14E, 0xCD);
            gSpawnedActor->drawDistance = 0x7D0;
            gSpawnedActor->flags |= 0x800400;
            gSpawnedActor->flags &= ~0x8000;
            gSpawnedActor->tintR = 0xFF;
            gSpawnedActor->tintG = 0xFF;
            gSpawnedActor->tintB = 0xFF;
            gSpawnedActor->alpha = 0xFF;
            angle = i * 0x200 + 0x104;
            gSpawnedActor->x = mathSinF(angle) * 270.0f + gCurrentActor->x;
            gSpawnedActor->z = mathCosF(angle) * 270.0f + gCurrentActor->z;
            gSpawnedActor->y = 100.0f;
            gSpawnedActor->yaw = angle;
            gSpawnedActor->segmentFlags = 0;
            gSpawnedActor->state = 0;
            ring = gSpawnedActor->customState;
            ring->timer = 0;
            ring->node = gCurrentActor;
            ring->ringIdx = i;
            if (flagGet(D_80744710[i], 0) != 0) {
                activeRingIdx = i;
                activeRingActor = gSpawnedActor;
                activeRingActor->state = 5;
                activeRingCount++;
            }
        }
    }
    sRingNextReady = 0;
    if (flagGet(0x1BB, 0) == 0) {
        activeRingIdx = -1;
    }
    if (sRingActiveStarted == 0 && activeRingIdx != -1) {
        activeRingActor->segmentFlags = 1;
        activeRingActor->state = 1;
        sRingActiveStarted = 1;
        D_807FC8D0 = activeRingIdx;
    }
}

extern u16 D_8076A0A6;
extern f32 D_807FC8D4;


void actorNodeRingUpdate(void) {
    static s8 sRingSequence[] = { 3, 10, 1, 8, 2, 11, 0, 9, -1, 0, 0, 0 };
    static s8 sRingSequencePos = 0;
    RingNodeModel *nodePtr = ((RingNodeActor *)gCurrentActor)->model;
    f32 dx;
    f32 dz;
    u8 shakeMagnitude;
    u16 shakeDuration;
    s16 ringHits = D_8076A0A6;
    s16 idx;

    if (!(gCurrentActor->flags & 0x10)) {
        if (ringAllCleared() != 0) {
            gCurrentActor->state = 0x40;
            return;
        }
        gCurrentActor->drawDistance = 0x7D0;
        gCurrentActor->flags |= 0x400;
        ringHits = 0;
        sRingSequencePos = 0;
        actorSpawn(0x73, 0xC4, &gCurrentActor);
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleY);
        gSpawnedActor->renderFlags |= 0x20;
        gSpawnedActor->flags |= 0x400;
        gSpawnedActor->drawDistance = 0x7D0;
        nodePtr->modelActor = gSpawnedActor;
        D_807FC8D4 = 1000.0f;
        actorNodeRingSpawnRings();
        gCurrentActor->state = 0;
        if (sRingActiveStarted != 0) {
            sRingActiveStarted = 0;
        }
        if (flagGet(0x1BB, 0) == 0) {
            gCurrentActor->state = 1;
        }
    }
    idx = -1;
    if (ringHits != 0) {
        idx = 0;
        while (!(ringHits & 1)) {
            ringHits >>= 1;
            idx++;
        }
    }
    dx = gCurrentActor->x - gPrimaryPlayerActor->x;
    dz = gCurrentActor->z - gPrimaryPlayerActor->z;
    shakeDuration = 0;
    D_807FC8D4 = dx * dx + dz * dz;
    switch (gCurrentActor->state) {
        case 1:
            actorScriptStart(gCurrentActor, 0x2EF);
            gCurrentActor->state = 2;
            camStartPath(gPrimaryPlayerActor, 2, 1);
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                sfxAllocateChannel(0x7D, 1.0f);
                actorScriptStart(gCurrentActor, 0x2F1);
                gCurrentActor->state = 3;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 3:
            if (gCurrentActor->unk155 & 1) {
                gCurrentActor->unk155++;
                shakeMagnitude = 0xF; shakeDuration = 0x28; // LAYOUT: one line keeps the sh of shakeDuration to sp+0x28 at 0x510 (split lines move it one slot later)
            }
            break;
    }
    if (camIsCutsceneActive() == 0) {
        if (gCurrentActor->sub4->animId != 0x2F0) {
            actorScriptStart(gCurrentActor, 0x2F0);
        }
    }
    if (shakeDuration) {
        camStartShake(gCamActor, shakeMagnitude, shakeDuration);
    }
    if (idx >= 0) {
        if (idx == sRingSequence[sRingSequencePos]) {
            sRingSequencePos++;
            if (sRingSequence[sRingSequencePos] == -1) {
                sfxPlayOnFreeSlot(0x1DA, 0x7FFF, 63.0f, 1.0f, 5, 0);
                flagSet(0x28, 1, 1);
                flagSet(0x26, 1, 1);
                sRingSequencePos = -1;
            }
        } else {
            sRingSequencePos = 0;
        }
    }
    D_8076A0A6 = 0;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

// per-ring cutscene model ids, copied whole to the stack before indexing
typedef struct RingModelIds {
    /* 0x00 */ s8 b[8];
} RingModelIds;

RingModelIds sRingCutsceneModelIds = { { 0x0E, 0x0F, 0x10, 0x11, 0x0A, 0x0B, 0x0C, 0x0D } };
extern u8 D_80720A7C;

void actorRingUpdate(void) {
    RingState *st = gCurrentActor->customState;
    f32 sparkX;
    f32 sparkY;
    f32 sparkZ;
    RingNodeModel *nodeModel;
    s32 limit;
    RingModelIds cutsceneModelIds;

    switch (gCurrentActor->state) {
        case 5:
            if (sRingNextReady != 0 && camIsCutsceneActive() == 0) {
                st->timer++;
                if (st->timer >= 0x29) {
                    sRingNextReady = 0;
                    gCurrentActor->state = 1;
                }
            } else {
                st->timer = 0;
            }
            break;
        case 1:
            st->timer = 0;
            gCurrentActor->state = 2;
            break;
        case 2:
            if (D_807FC8D4 < 160000.0) {
                gCurrentActor->state = 3;
                st->timer = 0;
                sfxAllocateChannel(0x3B, 1.0f);
                sfxPlayOnFreeSlot(0x258, 0x7FFF, 63.0f, 1.0f, 5, 0);
                camStartPath(gCurrentActor, 0, 1);
                actorScriptStart(gCurrentActor, 0x291);
                gCurrentActor->unk155 = 0;
                gCurrentActor->segmentFlags = 1;
            }
            break;
        case 3:
            if (gCurrentActor->unk155 == 1) {
                gCurrentActor->unk155++;
            } else if (gCurrentActor->unk155 == 2) {
                sfxStopChannel(0x3B, 1);
                gCurrentActor->alpha -= 8;
                if (gCurrentActor->alpha <= 0) {
                    gCurrentActor->alpha = 0;
                    st->timer++;
                    if (st->timer == 1) {
                        sfxPlayOnFreeSlot(0x1F6, 0x7FFF, 63.0f, 1.0f, 5, 0);
                    }
                    if (st->timer >= 0xB) {
                        cutsceneModelIds = sRingCutsceneModelIds;
                        gCurrentActor->state = 4;
                        sfxAllocateChannel(0x7D, 1.0f);
                        actorScriptStart(st->node, sRingNodeScripts[st->ringIdx]);
                        st->timer = 0;
                        st->node->state = 3;
                        st->node->unk155 = 0;
                        camStartPath(0, 1, 1);
                        csModelStateSetFirstByte(cutsceneModelIds.b[st->ringIdx], 2);
                    }
                }
                if (gCurrentActor->alpha < 0x80) {
                    gCurrentActor->y -= 6.0;
                }
            } else {
                effectSetSpeed(0x10064);
                effectSetCallback(effectLightFlickerDecay);
                effectSetColor(0xFF, 0xFF, 0xFF, 0xFF);
                sparkX = randomFloat() * 30.0 + gCurrentActor->x;
                sparkY = randomFloat() * 30.0 + (gCurrentActor->y + 20.0);
                sparkZ = randomFloat() * 30.0 + gCurrentActor->z;
                effectCreateAtPosition(&D_80720A7C, 1.2f, sparkX, sparkY, sparkZ);
            }
            break;
        case 4:
            if (ringAllCleared() != 0) {
                nodeModel = ((RingNodeActor *)st->node)->model;
                nodeModel->modelActor->y += 5.0;
                if (st->timer == 0x10E) {
                    flagSet(0x315, 1, 0);
                    menuTransitionToMap(sRingExits[7 * 2], sRingExits[7 * 2 + 1]);
                }
            }
            limit = 0xB4;
            if (st->ringIdx == 2 || st->ringIdx == 7) {
                if (ringAllCleared() == 0) {
                    limit = 0x5A;
                }
            }
            st->timer++;
            if (st->timer == limit) {
                if (st->ringIdx == 2 || st->ringIdx == 7) {
                    flagSet(st->ringIdx + 0x1BC, 1, 0);
                    if (ringAllCleared() == 0) {
                        camResumePath();
                        sfxStopChannel(0x7D, 1);
                        sRingNextReady = 1;
                    }
                } else {
                    menuTransitionToMap(sRingExits[st->ringIdx * 2], sRingExits[st->ringIdx * 2 + 1]);
                }
            }
            break;
        case 0:
            break;
    }
    gCurrentActor->eyeHeight = 0x28;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

s32 ringAllCleared(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (flagGet(i + 0x1BC, 0) == 0) {
            return 0;
        }
    }
    return 1;
}
