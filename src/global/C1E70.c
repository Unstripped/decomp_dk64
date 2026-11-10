#include "common.h"
#include "actor.h"
#define PROTO_SKIP_actorScriptStart // FAKE: callee prototype steer
#define PROTO_SKIP_actorSpawn // PROTO: The number of arguments doesn't agree with the number in the
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
f32 mathCosF(s16);
f32 mathSinF(s16);

typedef struct R1C0C1Sub174 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s8 unk2;
    /* 0x04 */ Actor *unk4;
} R1C0C1Sub174;

#define R1C0C1_SPAWNED_146 (((R1C0C1Spawned *)gSpawnedActor)->unk146)
typedef struct R1C0C1Spawned {
    /* 0x000 */ u8 pad0[0x146];
    /* 0x146 */ s16 unk146;
} R1C0C1Spawned;

void func_806BD170(void) {
    Actor *activeRingActor;
    s16 i;
    s16 activeRingIdx;
    s16 count;
    s16 pos;
    R1C0C1Sub174 *sub;

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
            R1C0C1_SPAWNED_146 = 0;
            gSpawnedActor->state = 0;
            sub = gSpawnedActor->customState;
            sub->unk0 = 0;
            sub->unk4 = gCurrentActor;
            sub->unk2 = i;
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
        ((R1C0C1Spawned *)activeRingActor)->unk146 = 1;
        activeRingActor->state = 1;
        D_80750660 = 1;
        D_807FC8D0 = activeRingIdx;
    }
}

extern s16 D_8076A0A6;
extern s8 D_807506B4;
extern s8 D_807506A8[];
extern f32 D_807FC8D4;
extern s32 gCamActor;

s32 actorScriptStart(void *, s32);  // FAKE: callee prototype steer

typedef struct RingNodePtr178 {
    /* 0x00 */ Actor *unk0;
} RingNodePtr178;

typedef struct RingNodeSub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} RingNodeSub4;

typedef struct RingNodeActor178 {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ RingNodePtr178 *unk178;
} RingNodeActor178;

void actorNodeRingUpdate(void) {
    RingNodePtr178 *nodePtr = ((RingNodeActor178 *)gCurrentActor)->unk178;
    f32 dx;
    f32 dz;
    u8 shakeMagnitude;
    u16 shakeDuration;
    s16 v3 = D_8076A0A6;
    s16 idx;
    s8 *cnt = &D_807506B4;
    s8 n;

    if (!(gCurrentActor->flags & 0x10)) {
        if (func_806BDD2C() != 0) {
            gCurrentActor->state = 0x40;
            return;
        }
        gCurrentActor->drawDistance = 0x7D0;
        gCurrentActor->flags |= 0x400;
        v3 = 0;
        D_807506B4 = 0; actorSpawn(0x73, 0xC4, &gCurrentActor);
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
                gCurrentActor->unk155[0] = 0;
            }
            break;
        case 3:
            if (gCurrentActor->unk155[0] & 1) {
                gCurrentActor->unk155[0]++;
                shakeMagnitude = 0xF; shakeDuration = 0x28;
            }
            break;
    }
    if (camIsCutsceneActive() == 0) {
        if (((RingNodeSub4 *)gCurrentActor->sub4)->unk64 != 0x2F0) {
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


typedef struct R1C0C1Ptr178 {
    /* 0x00 */ Actor *unk0;
} R1C0C1Ptr178;

typedef struct R1C0C1Act178 {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ R1C0C1Ptr178 *unk178;
} R1C0C1Act178;

typedef struct R1C0C1Blob8 {
    /* 0x00 */ s8 b[8];
} R1C0C1Blob8;

extern s16 D_80750664[];
extern s16 D_80750684[];
extern R1C0C1Blob8 D_807506B8;
extern u8 D_80720A7C;


void func_806BD7B0(void) {
    R1C0C1Sub174 *st = gCurrentActor->customState;
    f32 sparkX;
    f32 sparkY;
    f32 sparkZ;
    R1C0C1Ptr178 *p;
    s32 limit;
    R1C0C1Blob8 cutsceneModelIds;

    switch (gCurrentActor->state) {
        case 5:
            if (D_807506A4 != 0 && camIsCutsceneActive() == 0) {
                st->unk0++;
                if (st->unk0 >= 0x29) {
                    D_807506A4 = 0;
                    gCurrentActor->state = 1;
                }
            } else {
                st->unk0 = 0;
            }
            break;
        case 1:
            st->unk0 = 0;
            gCurrentActor->state = 2;
            break;
        case 2:
            if (D_807FC8D4 < 160000.0) {
                gCurrentActor->state = 3;
                st->unk0 = 0;
                sfxAllocateChannel(0x3B, 1.0f);
                sfxPlayOnFreeSlot(0x258, 0x7FFF, 63.0f, 1.0f, 5, 0);
                camStartPath(gCurrentActor, 0, 1);
                actorScriptStart(gCurrentActor, 0x291);
                gCurrentActor->unk155[0] = 0;
                ((R1C0C1Spawned *)gCurrentActor)->unk146 = 1;
            }
            break;
        case 3:
            if (gCurrentActor->unk155[0] == 1) {
                gCurrentActor->unk155[0]++;
            } else if (gCurrentActor->unk155[0] == 2) {
                sfxStopChannel(0x3B, 1);
                gCurrentActor->alpha -= 8;
                if (gCurrentActor->alpha <= 0) {
                    gCurrentActor->alpha = 0;
                    st->unk0++;
                    if (st->unk0 == 1) {
                        sfxPlayOnFreeSlot(0x1F6, 0x7FFF, 63.0f, 1.0f, 5, 0);
                    }
                    if (st->unk0 >= 0xB) {
                        cutsceneModelIds = D_807506B8;
                        gCurrentActor->state = 4;
                        sfxAllocateChannel(0x7D, 1.0f);
                        actorScriptStart(st->unk4, D_80750684[st->unk2]);
                        st->unk0 = 0;
                        st->unk4->state = 3;
                        st->unk4->unk155[0] = 0;
                        camStartPath(0, 1, 1);
                        csModelStateSetFirstByte(cutsceneModelIds.b[st->unk2], 2);
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
                p = ((R1C0C1Act178 *)st->unk4)->unk178;
                p->unk0->y += 5.0;
                if (st->unk0 == 0x10E) {
                    flagSet(0x315, 1, 0);
                    menuTransitionToMap(D_80750664[14], D_80750664[15]);
                }
            }
            limit = 0xB4;
            if (st->unk2 == 2 || st->unk2 == 7) {
                if (func_806BDD2C() == 0) {
                    limit = 0x5A;
                }
            }
            st->unk0++;
            if (limit == st->unk0) {
                if (st->unk2 == 2 || st->unk2 == 7) {
                    flagSet(st->unk2 + 0x1BC, 1, 0);
                    if (func_806BDD2C() == 0) {
                        camResumePath();
                        sfxStopChannel(0x7D, 1);
                        D_807506A4 = 1;
                    }
                } else {
                    menuTransitionToMap(D_80750664[st->unk2 * 2], D_80750664[st->unk2 * 2 + 1]);
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
