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
extern s8 D_807506A4;
extern s8 D_80750660;
extern u8 D_807FC8D0;

s32 actorSpawn();

// customState of the ring actors (type 0xCD) spawned by func_806BD170
typedef struct RingState {
    /* 0x00 */ s16 timer;
    /* 0x02 */ s8 ringIdx;
    /* 0x04 */ Actor *node;
} RingState;

// second component of the ring node actor: the model actor spawned in actorNodeRingUpdate
typedef struct RingNodeModel {
    /* 0x00 */ Actor *unk0;
} RingNodeModel;

typedef struct RingNodeActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ RingNodeModel *unk178;
} RingNodeActor;

void func_806BD170(void) {
    Actor *activeRingActor;
    s16 i;
    s16 activeRingIdx;
    s16 count; // FAKE: unused count keeps the s5 allocation, pre-existing, now tagged
    s16 pos;
    RingState *sub;

    activeRingIdx = -1;
    i = 0;
    count = 0;
    for (; i < 8; i++) {
        if (flagGet(i + 0x1BC, 0) == 0) {
            actorSpawn(0x14E, 0xCD);
            gSpawnedActor->drawDistance = 0x7D0;
            gSpawnedActor->flags |= 0x800400;
            pos = i * 0x200 + 0x104;
            gSpawnedActor->flags &= 0xFFFF7FFF;
            gSpawnedActor->tintR = 0xFF;
            gSpawnedActor->tintG = 0xFF;
            gSpawnedActor->tintB = 0xFF;
            gSpawnedActor->alpha = 0xFF;
            gSpawnedActor->x = mathSinF(pos) * 270.0f + gCurrentActor->x;
            gSpawnedActor->z = mathCosF(pos) * 270.0f + gCurrentActor->z;
            gSpawnedActor->y = 100.0f;
            gSpawnedActor->yaw = pos;
            gSpawnedActor->unk146 = 0;
            gSpawnedActor->state = 0;
            sub = gSpawnedActor->customState;
            sub->timer = 0;
            sub->node = gCurrentActor;
            sub->ringIdx = i;
            if (flagGet(D_80744710[i], 0) != 0) {
                activeRingIdx = i;
                activeRingActor = gSpawnedActor;
                activeRingActor->state = 5;
                count++;
            }
        }
    }
    D_807506A4 = 0;
    if (flagGet(0x1BB, 0) == 0) {
        activeRingIdx = -1;
    }
    if (D_80750660 == 0 && activeRingIdx != -1) {
        activeRingActor->unk146 = 1;
        activeRingActor->state = 1;
        D_80750660 = 1;
        D_807FC8D0 = activeRingIdx;
    }
}

extern s16 D_8076A0A6;
extern s8 D_807506B4;
extern s8 D_807506A8[];
extern f32 D_807FC8D4;
extern Actor *gCamActor;

void actorNodeRingUpdate(void) {
    RingNodeModel *nodePtr = ((RingNodeActor *)gCurrentActor)->unk178;
    f32 dx;
    f32 dz;
    u8 shakeMagnitude;
    u16 shakeDuration;
    s16 v3 = D_8076A0A6;
    s16 idx;
    s8 *cnt = &D_807506B4; // FAKE: address local for D_807506B4, shifts the t1/t2 temp numbering from 0x2b4 on
    s8 n;

    if (!(gCurrentActor->flags & 0x10)) {
        if (func_806BDD2C() != 0) {
            gCurrentActor->state = 0x40;
            return;
        }
        gCurrentActor->drawDistance = 0x7D0;
        gCurrentActor->flags |= 0x400;
        v3 = 0;
        D_807506B4 = 0; actorSpawn(0x73, 0xC4, &gCurrentActor); // LAYOUT: one line keeps as1 order of the sb zero to D_807506B4 in the jal delay slot
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleY);
        gSpawnedActor->renderFlags |= 0x20;
        gSpawnedActor->flags |= 0x400;
        gSpawnedActor->drawDistance = 0x7D0;
        nodePtr->unk0 = gSpawnedActor;
        D_807FC8D4 = 1000.0f;
        func_806BD170();
        gCurrentActor->state = 0;
        if (D_80750660 != 0) {
            D_80750660 = 0;
        }
        if (flagGet(0x1BB, 0) == 0) {
            gCurrentActor->state = 1;
        }
    }
    idx = -1;
    if (v3 != 0) {
        idx = 0;
        while (!(v3 & 1)) {
            v3 >>= 1;
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
        n = *cnt;
        if (idx == D_807506A8[n]) {
            n++;
            D_807506B4 = n;
            if (D_807506A8[n] == -1) {
                sfxPlayOnFreeSlot(0x1DA, 0x7FFF, 63.0f, 1.0f, 5, 0);
                flagSet(0x28, 1, 1);
                flagSet(0x26, 1, 1);
                if (D_807506B4 == -1) {} // FAKE: dead test triggers constant web for -1 in v0
                D_807506B4 = -1;
            }
        } else {
            D_807506B4 = 0;
        }
    }
    D_8076A0A6 = 0;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

// per-ring cutscene model ids, copied whole to the stack before indexing
typedef struct RingModelIds {
    /* 0x00 */ s8 b[8];
} RingModelIds;

extern s16 D_80750664[];
extern s16 D_80750684[];
extern RingModelIds D_807506B8;
extern u8 D_80720A7C;

void func_806BD7B0(void) {
    RingState *st = gCurrentActor->customState;
    f32 sparkX;
    f32 sparkY;
    f32 sparkZ;
    RingNodeModel *p;
    s32 limit;
    RingModelIds cutsceneModelIds;

    switch (gCurrentActor->state) {
        case 5:
            if (D_807506A4 != 0 && camIsCutsceneActive() == 0) {
                st->timer++;
                if (st->timer >= 0x29) {
                    D_807506A4 = 0;
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
                gCurrentActor->unk146 = 1;
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
                        cutsceneModelIds = D_807506B8;
                        gCurrentActor->state = 4;
                        sfxAllocateChannel(0x7D, 1.0f);
                        actorScriptStart(st->node, D_80750684[st->ringIdx]);
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
            if (func_806BDD2C() != 0) {
                p = ((RingNodeActor *)st->node)->unk178;
                p->unk0->y += 5.0;
                if (st->timer == 0x10E) {
                    flagSet(0x315, 1, 0);
                    menuTransitionToMap(D_80750664[14], D_80750664[15]);
                }
            }
            limit = 0xB4;
            if (st->ringIdx == 2 || st->ringIdx == 7) {
                if (func_806BDD2C() == 0) {
                    limit = 0x5A;
                }
            }
            st->timer++;
            if (limit == st->timer) {
                if (st->ringIdx == 2 || st->ringIdx == 7) {
                    flagSet(st->ringIdx + 0x1BC, 1, 0);
                    if (func_806BDD2C() == 0) {
                        camResumePath();
                        sfxStopChannel(0x7D, 1);
                        D_807506A4 = 1;
                    }
                } else {
                    menuTransitionToMap(D_80750664[st->ringIdx * 2], D_80750664[st->ringIdx * 2 + 1]);
                }
            }
            break;
        case 0:
            break;
    }
    gCurrentActor->eyeHeight = 0x28;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

s32 func_806BDD2C(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (flagGet(i + 0x1BC, 0) == 0) {
            return 0;
        }
    }
    return 1;
}
