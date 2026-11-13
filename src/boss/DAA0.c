#include "common.h"
#define PROTO_SKIP_bossSpawnParticleRing // FAKE: callee prototype steer
#define PROTO_SKIP_sfxAllocateChannel // FAKE: callee prototype steer
#define PROTO_SKIP_sfxPlayOnFreeSlot // FAKE: callee prototype steer
#include "proto/boss/3840.h"
#include "proto/boss/DAA0.h"
#include "proto/global/1295B0.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/5E2F0.h"
#include "proto/global/6AD90.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/8D3E0.h"
#include "proto/global/8F050.h"
#include "proto/global/8F4B0.h"
#include "proto/global/936B0.h"
#include "proto/global/CC800.h"
#include "proto/global/F56F0.h"

// DAA0: hidden translation-unit boundary at 0x80031AA0 (C920's .data/.rodata end 16-/8-aligned before it)
s16 D_80035B00[4] = { 0, 0x26C, 0, -0x26C };
s16 D_80035B08[4] = { 0x26C, 0, -0x26C, 0 };
s16 D_80035B10[4] = { 0x800, 0xC00, 0, 0x400 };
s16 D_80035B18[4] = { 0, -0x4B, 0, 0x4B };
s16 D_80035B20[4] = { -0x4B, 0, 0x4B, 0 };
s8 D_80035B28 = -1;
s16 D_80035B2C = 0;
s8 D_80035B30[4] = { 7, 3, 1, 0 };
s8 D_80035B34 = 0;
u8 D_80035B38 = 0xFF;
f32 D_80035B3C = 0.0f;
s8 D_80035B40 = 0;
s8 D_80035B44[5] = { 2, 3, 4, 0, 1 };
s16 D_80035B4C[5] = { 2, 3, 4, 5, 6 };
u8 D_80035B58[5] = { 2, 1, 3, 4, 0 };
s16 D_80035B60[4] = { 0xDC, 0xDD, 0xDE, 0xDF };
s8 D_80035B68 = 0;
s8 D_80035B6C = 0;

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

typedef struct BossSpawnState {
    Actor *unk0;
    s8 unk4;
    s8 unk5;
} BossSpawnState;

typedef struct BossSpawnerState {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s8 unk12;
    s8 unk13;
    s8 unk14;
    s8 unk15;
    s8 unk16;
    s8 unk17;
} BossSpawnerState;

extern Actor *gSpawnedActor;
extern u8 D_807FBDC4;
extern s8 D_80036DC0;
extern f32 D_80036DC4;

void sfxPlayOnFreeSlot();  // FAKE: callee prototype steer
s32 sfxAllocateChannel();  // FAKE: callee prototype steer
void bossSpawnParticleRing(u16, s16, s16, s16, s16, u8); // FAKE: callee prototype steer

void bossSpawnerUpdate(void) {
    f32 dx;
    s32 pad;
    s32 k;
    s32 i;
    BossSpawnerState *s;
    s8 prevSubState;
    s8 hitPlayer;
    s8 bounceDir;
    s8 spawnParticle;
    s8 topReached;
    BossSpawnState *st;
    s32 cutsceneId;
    f32 lx;
    f32 lz;
    s16 j;
    static s16 D_80035B70 = 0;

    s = gCurrentActor->customState;
    topReached = 0;
    spawnParticle = 0;
    hitPlayer = 0;
    if (!(gCurrentActor->flags & 0x10)) {
        D_80035B28 = 0xF;
        D_80035B34 = 0;
        D_80035B3C = 0.0f;
        s->unkC = 0x1E;
        s->unkE = 1;
        s->unk0 = gCurrentActor->y;
        s->unk14 = 0;
        D_80035B6C = 0;
        s->unk12 = 0;
        D_80035B70 = 5;
        for (i = 0; i != 8; i++) {
            if (actorSpawn(0xA6, D_80035B60[i >> 1]) != 0) {
                st = gSpawnedActor->customState;
                st->unk0 = gCurrentActor;
                st->unk4 = i >> 1;
                st->unk5 = i & 1;
                gSpawnedActor->y = gCurrentActor->y + 50.0f;
                gSpawnedActor->sub4->scaleX = 0.1;
                gSpawnedActor->sub4->scaleY = 0.1;
                gSpawnedActor->sub4->scaleZ = 0.1;
                gSpawnedActor->flags |= 0x400;
            }
        }
        D_80036DC4 = 160000.0f;
        D_80036DC0 = 0;
        if (gPrimaryPlayerActor != NULL) {
            gPrimaryPlayerActor->state = 0x77;
            gPrimaryPlayerActor->unk155 = 0;
        }
        gCurrentActor->drawDistance = 0x7D0;
        collisionCheckActorFloor(gCurrentActor, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, &gCurrentActor->floorY);
        gCurrentActor->state = 2;
        camStartPath(0, 3, 1);
    }
    switch (gCurrentActor->state) {
    case 0:
        gPrimaryPlayerActor->x = gCurrentActor->x;
        gPrimaryPlayerActor->y = gCurrentActor->y;
        gPrimaryPlayerActor->z = gCurrentActor->z;
        if (D_80035B38 == -1) {
            D_80035B38 = gPrimaryPlayerActor->unk144;
        }
        gPrimaryPlayerActor->flags &= ~4;
        gPrimaryPlayerActor->unk144 = 1;
        if (D_807FBDC4 != 0) {
            cutsceneId = D_80035B44[D_80036DC0];
            gCurrentActor->unk146 = 0;
            for (i = 4; D_80036DC0 < i; i--) {
                func_8068A764(gCurrentActor, D_80035B58[D_80035B44[i]]);
            }
            D_80036DC0++;
            cutsceneId = D_80035B4C[cutsceneId];
            playerSetKongByActorType(cutsceneId);
            playerKongStopAudioChannels(gPrimaryPlayerActor, cutsceneId);
            gPrimaryPlayerActor->state = 0xC;
            gPrimaryPlayerActor->unk155 = 0;
            actorAppendCallbackPayloadAAB8(gCurrentActor, gPrimaryPlayerActor, 0, 180.0f, 0x46);
            gCurrentActor->state = 1;
            gPrimaryPlayerActor->unk144 = D_80035B38;
        }
        break;
    case 1:
        gPrimaryPlayerActor->flags |= 4;
        dx = gPrimaryPlayerActor->x - gCurrentActor->x;
        lz = gPrimaryPlayerActor->z - gCurrentActor->z;
        if (dx > 700.0 || dx < -700.0 || lz > 700.0 || lz < -700.0) {
            if (D_80036DC0 < 5) {
                gCurrentActor->state = 0;
                camStartPath(0, 2, 1);
            } else {
                mapRequestTransition(0x2A, 2);
                gCurrentActor->state = 3;
            }
        }
        break;
    case 2:
        s->unkE--;
        if (s->unkE < 0) {
            gCurrentActor->state = 0;
            playerSetKongByActorType(4);
            playerKongStopAudioChannels(gPrimaryPlayerActor, 4);
            s->unk13 = 1;
        }
        break;
    case 3:
        break;
    }
    gCurrentActor->yaw += 0x32;
    gCurrentActor->yaw &= 0xFFF;
    gCurrentActor->y = mathSinF(gCurrentActor->yaw) * 5.0 + s->unk0;
    if (gPrimaryPlayerActor->state == 0x45 && gPrimaryPlayerActor->unk155 >= 2 && D_80036DC4 < 10000.0) {
        hitPlayer = 1;
    }
    bounceDir = 0;
    s->unk4 += s->unk8;
    if (s->unk4 > 1.0f) {
        s->unk4 = 1.0f;
        bounceDir = 1;
    }
    if (s->unk4 < 0) {
        s->unk4 = 0;
        bounceDir = -1;
    }
    if (bounceDir != 0 && camIsCutsceneActive() == 0) {
        s->unk10++;
    }
    s->unk17 = 0;
    prevSubState = s->unk13;
    switch (s->unk13) {
    case 0:
        i = 5;
        if (s->unk12 == 2) {
            j = 0xC;
            s->unk8 = -0.2f;
        } else {
            i = 0x3C;
            j = 4;
            s->unk8 = -0.1f;
        }
        if (i < s->unk10) {
            s->unk15++;
            if (s->unk15 < j) {
                s->unk13 = 1;
                sfxPlayOnFreeSlot(0x37D, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                if (s->unk12 == 2) {
                    sfxPlayOnFreeSlot(0x381, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                } else {
                    sfxPlayOnFreeSlot(0x37F, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                }
            } else {
                s->unk13 = 2;
                s->unk15 = 0;
            }
        }
        if (bounceDir != 0 && D_80035B40 == 0) {
            spawnParticle = 1;
            D_80035B2C = 0;
        }
        break;
    case 1:
        switch (s->unk12) {
        case 2:
            i = 0xA;
            s->unk8 = 0.2f;
            break;
        case 3:
            i = 0x3C;
            s->unk8 = 0.1f;
            break;
        default:
            i = 0xB4;
            s->unk8 = 0.1f;
            break;
        }
        if (bounceDir == 1) {
            topReached = 1;
            if (i < s->unk10) {
                s->unk13 = 0;
                s->unk15++;
                sfxPlayOnFreeSlot(0x17D, 0x3E80, 0x427C0000, 0x3F800000, 0, 0);
            }
            if (hitPlayer != 0) {
                sfxPlayOnFreeSlot(0x97, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                s->unk16++;
                s->unk15 = 0;
                s->unk13 = 2;
                if (s->unk16 == 3) {
                    sfxPlayOnFreeSlot(0x385, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                    s->unk16 = 0;
                    camPausePath();
                    if (D_80035B68 == 0) {} // FAKE: dead test steers uopt colouring/ring (case 1 arm)
                    s->unk13 = 4;
                } else {
                    sfxPlayOnFreeSlot(0x38E, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                    sfxPlayOnFreeSlot(0x383, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                }
            }
        }
        break;
    case 2:
        s->unk8 = -0.1f;
        if (s->unk10 >= 0x5B) {
            s->unk15++;
            if (s->unk15 < 3) {
                s->unk13 = 3;
                sfxPlayOnFreeSlot(0x37D, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                sfxPlayOnFreeSlot(0x380, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
            } else {
                s->unk13 = 0;
                s->unk15 = 0;
            }
        }
        if (bounceDir != 0 && D_80035B40 == 0) {
            spawnParticle = 1;
        }
        break;
    case 3:
        s->unk8 = 0.1f;
        if (s->unk10 >= 0x1F) {
            s->unk13 = 2;
            sfxPlayOnFreeSlot(0x17D, 0x3E80, 0x427C0000, 0x3F800000, 0, 0);
        }
        if (bounceDir != 0) {
            s->unk17 = 1;
        }
        break;
    case 4:
        D_80035B3C += 1.0;
        if (D_80035B3C > 24.0) {
            D_80035B3C = 24.0f;
            s->unk10++;
            D_80035B2C = mathSinF(s->unk10 << 5) * 200.0f;
            if (s->unk10 == 0x3F) {
                D_80035B3C = 0.0f;
                D_80035B2C = 0;
                D_80035B28 = D_80035B30[D_80035B34];
                D_80035B34 += 1;
                s->unk13 = 5;
            }
        }
        break;
    case 5:
        s->unk10++;
        if (s->unk10 >= 0x3D) {
            s->unk8 = -0.1f;
            camResumePath();
            s->unk13 = 0;
            s->unk12++;
            if (s->unk12 == 1) {
                func_80724994(1, 7, 0, 0, 0);
            }
            if (s->unk12 == 3) {
                s->unk13 = 7;
            }
        }
        break;
    case 6:
        s->unk8 = -0.1f;
        if (bounceDir == -1) {
            topReached = 1;
            if (D_80035B70 < s->unk10) {
                sfxPlayOnFreeSlot(0x17D, 0x3E80, 0x427C0000, 0x3F800000, 0, 0);
                D_80035B70++;
                s->unk10 = 0;
                if (D_80035B70 >= 0x10) {
                    D_80035B70 += 1;
                }
                if (D_80035B70 >= 0x1A) {
                    D_80035B70 = (randomLcgNext() & 3) + 4;
                    s->unk13 = 1;
                    s->unk15++;
                    sfxPlayOnFreeSlot(0x37F, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                    sfxPlayOnFreeSlot(0x381, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                }
                spawnParticle = 1;
            }
            D_80035B68 = 0x1E;
        }
        break;

    case 7:
        s->unk10++;
        s->unk8 = -0.1f;
        if (s->unk10 >= 0x10) {
            for (j = 0; j < 4; j++) {
                actorDespawn(actorListFindActorById(j));
            }
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->alpha = 0;
            camStartPath(0, 4, 1);
            s->unk13 = 8;
        }
        break;
    case 8:
        s->unk8 = -0.1f;
        if (D_807FBDC4 != 0) {
            sfxAllocateChannel(0x35, 0x3F800000);
            bossSpawnParticleRing(0x13D, gCurrentActor->x, gCurrentActor->y + 200.0f, gCurrentActor->z + 40.0f, 0x800, 1);
            s->unk13 = 9;
        }
        break;
    case 9:
        break;
    }
    if (s->unk12 == 3 && s->unk13 == 0) {
        if (s->unk15 < 2) {
            s->unk13 = 6;
        } else {
            s->unk15 = 0x14;
        }
    }
    if (prevSubState != s->unk13) {
        s->unk10 = 0;
    }
    if (spawnParticle != 0) {
        if (s->unk12 == 2 || s->unk12 == 3) {
            s->unk14++;
        } else {
            dx = randomFloat(); // FAKE: dx reused as the randomFloat temp (randomFloat() inline fails fdiff)
            s->unk14 += (s32)(dx * 2.99f) + 1;
        }
        k = s->unk14;
        if (k >= 4) {
            s->unk14 = k - 4;
        }
    }
    D_80035B68++;
    if (topReached != 0) {
        cutsceneId = (D_80035B68 & 0x1F) - 0x10; // FAKE: cutsceneId reused as the light level (a separate s32 level local fails fdiff)
        i = cutsceneId;
        k = s->unk14;
        if (cutsceneId < 0) {
            i = -cutsceneId;
        }
        if (i >= 0x10) {
            i = 0xF;
        }
        cutsceneId = (i << 4) & 0xFF;
        if (cutsceneId && cutsceneId) {} // FAKE: pins the cutsceneId def before the lx/lz loads
        lx = D_80035B00[k] * 0.33 + gCurrentActor->x;
        lz = D_80035B08[k] * 0.33 + gCurrentActor->z;
        lightAdd(lx, 400.0f, lz, lx, 300.0f, lz, 200.0f, 0, cutsceneId, cutsceneId, cutsceneId);
        if (s->unk12 == 1) {
            k = s->unk14 + 2;
            if (k >= 4) {
                k -= 4;
            }
            lx = D_80035B00[k] * 0.33 + gCurrentActor->x;
            lz = D_80035B08[k] * 0.33 + gCurrentActor->z;
            lightAdd(lx, 400.0f, lz, lx, 300.0f, lz, 200.0f, 0, cutsceneId, cutsceneId, cutsceneId);
        }
    }
    s->unkC--;
    if (s->unkC < 0) {
        s->unkC = (randomLcgNext() & 0x7F) + 0x5A;
        lightSetColor(0.5f, 0.5f, 0.5f, -1);
        enemyAggroEnable();
    }
    D_80035B40 = bounceDir;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct BossParentState {
    char pad0[4];
    f32 unk4;
    char pad8[0xA];
    s8 unk12;
    char pad13[1];
    s8 unk14;
    char pad15[2];
    s8 unk17;
} BossParentState;

typedef struct BossFollowerLink {
    Actor *unk0;
    s8 unk4;
    s8 unk5;
} BossFollowerLink;

void bossFollowerActorUpdate(void) {
    BossFollowerLink *link = gCurrentActor->customState;
    BossParentState *parentState = link->unk0->customState;
    AnimSlot *anim = gCurrentActor->sub4->model;
    static s16 D_80035B74 = 0x78; // function-local static (only user; shadows the file-scope definition, which the .data carve moves here) keeps uopt from pointerizing D_80035B74

    if (link->unk5 == 0) {
        f32 dx = gPrimaryPlayerActor->x - gCurrentActor->x;
        f32 dz = gPrimaryPlayerActor->z - gCurrentActor->z;
        D_80036DC4 = dx * dx + dz * dz;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        controllerAnimSetStateIfChanged(gCurrentActor, link->unk4 + 0x668, 0.0f, 0.0f);
        gCurrentActor->drawDistance = 0xFA0;
    }
    if (D_80035B28 & (1 << link->unk4)) {
        gCurrentActor->roll = (s16)(parentState->unk4 * 1024.0) - 0x400;
        gCurrentActor->pitch = D_80035B2C;
        if (anim != NULL) {
            if (D_80035B3C != anim->frame) {
                controllerApplyMotionWindow(gCurrentActor, anim, D_80035B3C);
            }
        }
    } else {
        gCurrentActor->roll = 0;
        if (anim != NULL) {
            s32 animId = link->unk4 + 0x66B;
            if (animId != anim->animId) {
                controllerAnimSetStateIfChanged(gCurrentActor, animId, 0.0f, 0.0f);
                sfxPlayOnFreeSlot(0x38D, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
            } else {
                controllerApplyMotionWindow(gCurrentActor, anim, anim->frame + 0.75f);
            }
            if (link->unk4 == 1) {
                if (anim->frame > 24.0f) {
                    anim->frame = 24.0f;
                }
                if (anim->frame > 15.0f) {
                    gCurrentActor->y -= 10.0f;
                }
            } else {
                if (anim->frame > 37.0f) {
                    anim->frame = 37.0f;
                }
                if (anim->frame > 26.0f) {
                    gCurrentActor->y -= 10.0f;
                    if (anim->animId == 1) {} // FAKE: steers uopt colouring (const 35 -> a1)
                }
            }
            if (gCurrentActor->y < 0.0) {
                sfxPlayOnFreeSlot(0x384, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                actorDespawn(gCurrentActor);
            }
        }
    }
    if (link->unk5 == 0) {
        gCurrentActor->unk144 = 0xC;
        if (link->unk4 == 0) {
            if (parentState->unk17 == 1) {
                if (link->unk0->state == 0) {
                    D_80035B74 = 0x28;
                }
                D_80035B74--;
                if (D_80035B74 < 0) {
                    f32 zo = D_80035B20[parentState->unk14];
                    f32 xo = D_80035B18[parentState->unk14];
                    D_80035B74 = 0xA;
                    projectileSetTargetCoords(gCurrentActor->x + xo, gCurrentActor->y + 270.0f, gCurrentActor->z + zo);
                    projectileAimAndSpawn(0x2C, 1, 0.25f, gPrimaryPlayerActor->x, gPrimaryPlayerActor->y, gPrimaryPlayerActor->z, 2400.0f, gCurrentActor);
                }
            } else {
                D_80035B74 = 0;
            }
        }
        gCurrentActor->x = D_80035B00[parentState->unk14] + link->unk0->x;
        gCurrentActor->z = D_80035B08[parentState->unk14] + link->unk0->z;
        gCurrentActor->yaw = D_80035B10[parentState->unk14];
    } else {
        s32 oppSide;
        gCurrentActor->unk144 = 1;
        oppSide = parentState->unk14 + 2;
        if (oppSide >= 4) {
            oppSide -= 4;
        }
        gCurrentActor->x = D_80035B00[oppSide] + link->unk0->x;
        if (D_80035B18) {}  // FAKE: deadsweep dead statement (steers uopt)
        gCurrentActor->z = D_80035B08[oppSide] + link->unk0->z;
        gCurrentActor->yaw = D_80035B10[oppSide];
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0x23;
        if (link->unk5 && link->unk5) {} // FAKE: steers uopt colouring (const 35 -> a1)
        gCurrentActor->tintG = 0x23;
        gCurrentActor->tintB = 0x46;
        if (parentState->unk12 != 1) {
            gCurrentActor->flags &= ~4;
        } else {
            gCurrentActor->flags |= 4;
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
