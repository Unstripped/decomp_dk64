#include "common.h"
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
s16 gBossSideOffsetX[4] = { 0, 0x26C, 0, -0x26C };
s16 gBossSideOffsetZ[4] = { 0x26C, 0, -0x26C, 0 };
s16 gBossSideYaw[4] = { 0x800, 0xC00, 0, 0x400 };
s16 gBossSideAimOffsetX[4] = { 0, -0x4B, 0, 0x4B };
s16 gBossSideAimOffsetZ[4] = { -0x4B, 0, 0x4B, 0 };
s8 gBossFollowerRaisedMask = -1;
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

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

// customState of each follower actor 0xA6 spawned by bossSpawnerUpdate (8 of them: 4 sides x 2).
typedef struct BossFollowerLink {
    /* 0x00 */ Actor *parent; // the spawner; its customState is the BossSpawnerState
    /* 0x04 */ s8 slot; // side index 0-3
    /* 0x05 */ s8 mirrored; // 1 for the second follower of a pair (opposite side, dark tint)
} BossFollowerLink;

// customState of the spawner actor (bossSpawnerUpdate); bossFollowerActorUpdate reads it through link->parent.
typedef struct BossSpawnerState {
    /* 0x00 */ f32 baseY; // hover centre (y = baseY + 5 sin(yaw))
    /* 0x04 */ f32 lift; // 0..1, stepped by liftSpeed; drives the followers roll
    /* 0x08 */ f32 liftSpeed;
    /* 0x0C */ s16 aggroTimer; // light flash + enemyAggroEnable when it runs out
    /* 0x0E */ s16 introTimer;
    /* 0x10 */ s16 stepTimer; // frames/bounces in the current subState (reset on change)
    /* 0x12 */ s8 phase; // 0-3, advanced after each 3-hit round
    /* 0x13 */ s8 subState;
    /* 0x14 */ s8 side; // active side 0-3 (gBossSideOffsetX/gBossSideOffsetZ/gBossSideYaw tables)
    /* 0x15 */ s8 repeatCount;
    /* 0x16 */ s8 hitCount;
    /* 0x17 */ s8 fireFlag; // set for one frame per bounce in subState 3: side-0 follower fires
} BossSpawnerState;

extern Actor *gSpawnedActor;
extern s8 D_80036DC0;
extern f32 gBossFollowerPlayerDistSq;

void bossSpawnerUpdate(void) {
    f32 r;
    s32 level;
    s32 k;
    s32 i;
    BossSpawnerState *state;
    s8 prevSubState;
    s8 hitPlayer;
    s8 bounceDir;
    s8 spawnParticle;
    s8 topReached;
    BossFollowerLink *link;
    s32 cutsceneId;
    f32 x;
    f32 z;
    s16 j;
    static s8 sLightPulseTimer = 0;
    static s8 D_80035B6C = 0;
    static s16 sBounceLimit = 0;

    state = gCurrentActor->customState;
    topReached = 0;
    spawnParticle = 0;
    hitPlayer = 0;
    if (!(gCurrentActor->flags & 0x10)) {
        gBossFollowerRaisedMask = 0xF;
        D_80035B34 = 0;
        D_80035B3C = 0.0f;
        state->aggroTimer = 0x1E;
        state->introTimer = 1;
        state->baseY = gCurrentActor->y;
        state->side = 0;
        D_80035B6C = 0;
        state->phase = 0;
        sBounceLimit = 5;
        for (i = 0; i != 8; i++) {
            if (actorSpawn(0xA6, D_80035B60[i >> 1]) != 0) {
                link = gSpawnedActor->customState;
                link->parent = gCurrentActor;
                link->slot = i >> 1;
                link->mirrored = i & 1;
                gSpawnedActor->y = gCurrentActor->y + 50.0f;
                gSpawnedActor->sub4->scaleX = 0.1;
                gSpawnedActor->sub4->scaleY = 0.1;
                gSpawnedActor->sub4->scaleZ = 0.1;
                gSpawnedActor->flags |= 0x400;
            }
        }
        gBossFollowerPlayerDistSq = 160000.0f;
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
        if (gActorGlobalState.volumeTriggerQueueCount != 0) {
            cutsceneId = D_80035B44[D_80036DC0];
            gCurrentActor->segmentFlags = 0;
            for (i = 4; D_80036DC0 < i; i--) {
                func_8068A764(gCurrentActor, D_80035B58[D_80035B44[i]]);
            }
            D_80036DC0++;
            cutsceneId = D_80035B4C[cutsceneId];
            playerSetKongByActorType(cutsceneId);
            playerKongStopAudioChannels(gPrimaryPlayerActor, cutsceneId);
            gPrimaryPlayerActor->state = 0xC;
            gPrimaryPlayerActor->unk155 = 0;
            actorAppendPlayerLaunch(gCurrentActor, gPrimaryPlayerActor, 0, 180.0f, 0x46);
            gCurrentActor->state = 1;
            gPrimaryPlayerActor->unk144 = D_80035B38;
        }
        break;
    case 1:
        gPrimaryPlayerActor->flags |= 4;
        x = gPrimaryPlayerActor->x - gCurrentActor->x;
        z = gPrimaryPlayerActor->z - gCurrentActor->z;
        if (x > 700.0 || x < -700.0 || z > 700.0 || z < -700.0) {
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
        state->introTimer--;
        if (state->introTimer < 0) {
            gCurrentActor->state = 0;
            playerSetKongByActorType(4);
            playerKongStopAudioChannels(gPrimaryPlayerActor, 4);
            state->subState = 1;
        }
        break;
    case 3:
        break;
    }
    gCurrentActor->yaw += 0x32;
    gCurrentActor->yaw &= 0xFFF;
    gCurrentActor->y = mathSinF(gCurrentActor->yaw) * 5.0 + state->baseY;
    if (gPrimaryPlayerActor->state == 0x45 && gPrimaryPlayerActor->unk155 >= 2 && gBossFollowerPlayerDistSq < 10000.0) {
        hitPlayer = 1;
    }
    bounceDir = 0;
    state->lift += state->liftSpeed;
    if (state->lift > 1.0f) {
        state->lift = 1.0f;
        bounceDir = 1;
    }
    if (state->lift < 0) {
        state->lift = 0;
        bounceDir = -1;
    }
    if (bounceDir != 0 && camIsCutsceneActive() == 0) {
        state->stepTimer++;
    }
    state->fireFlag = 0;
    prevSubState = state->subState;
    switch (state->subState) {
    case 0:
        i = 5;
        if (state->phase == 2) {
            j = 0xC;
            state->liftSpeed = -0.2f;
        } else {
            i = 0x3C;
            j = 4;
            state->liftSpeed = -0.1f;
        }
        if (i < state->stepTimer) {
            state->repeatCount++;
            if (state->repeatCount < j) {
                state->subState = 1;
                sfxPlayOnFreeSlot(0x37D, 0x7D00, 63.0, 1.0, 0, 0);
                if (state->phase == 2) {
                    sfxPlayOnFreeSlot(0x381, 0x7D00, 63.0, 1.0, 0, 0);
                } else {
                    sfxPlayOnFreeSlot(0x37F, 0x7D00, 63.0, 1.0, 0, 0);
                }
            } else {
                state->subState = 2;
                state->repeatCount = 0;
            }
        }
        if (bounceDir != 0 && D_80035B40 == 0) {
            spawnParticle = 1;
            D_80035B2C = 0;
        }
        break;
    case 1:
        switch (state->phase) {
        case 2:
            i = 0xA;
            state->liftSpeed = 0.2f;
            break;
        case 3:
            i = 0x3C;
            state->liftSpeed = 0.1f;
            break;
        default:
            i = 0xB4;
            state->liftSpeed = 0.1f;
            break;
        }
        if (bounceDir == 1) {
            topReached = 1;
            if (i < state->stepTimer) {
                state->subState = 0;
                state->repeatCount++;
                sfxPlayOnFreeSlot(0x17D, 0x3E80, 63.0, 1.0, 0, 0);
            }
            if (hitPlayer != 0) {
                sfxPlayOnFreeSlot(0x97, 0x7D00, 63.0, 1.0, 0, 0);
                state->hitCount++;
                state->repeatCount = 0;
                state->subState = 2;
                if (state->hitCount == 3) {
                    sfxPlayOnFreeSlot(0x385, 0x7D00, 63.0, 1.0, 0, 0);
                    state->hitCount = 0;
                    camPausePath();
                    state->subState = 4;
                } else {
                    sfxPlayOnFreeSlot(0x38E, 0x7D00, 63.0, 1.0, 0, 0);
                    sfxPlayOnFreeSlot(0x383, 0x7D00, 63.0, 1.0, 0, 0);
                }
            }
        }
        break;
    case 2:
        state->liftSpeed = -0.1f;
        if (state->stepTimer >= 0x5B) {
            state->repeatCount++;
            if (state->repeatCount < 3) {
                state->subState = 3;
                sfxPlayOnFreeSlot(0x37D, 0x7D00, 63.0, 1.0, 0, 0);
                sfxPlayOnFreeSlot(0x380, 0x7D00, 63.0, 1.0, 0, 0);
            } else {
                state->subState = 0;
                state->repeatCount = 0;
            }
        }
        if (bounceDir != 0 && D_80035B40 == 0) {
            spawnParticle = 1;
        }
        break;
    case 3:
        state->liftSpeed = 0.1f;
        if (state->stepTimer >= 0x1F) {
            state->subState = 2;
            sfxPlayOnFreeSlot(0x17D, 0x3E80, 63.0, 1.0, 0, 0);
        }
        if (bounceDir != 0) {
            state->fireFlag = 1;
        }
        break;
    case 4:
        D_80035B3C += 1.0;
        if (D_80035B3C > 24.0) {
            D_80035B3C = 24.0f;
            state->stepTimer++;
            D_80035B2C = mathSinF(state->stepTimer << 5) * 200.0f;
            if (state->stepTimer == 0x3F) {
                D_80035B3C = 0.0f;
                D_80035B2C = 0;
                gBossFollowerRaisedMask = D_80035B30[D_80035B34];
                D_80035B34 += 1;
                state->subState = 5;
            }
        }
        break;
    case 5:
        state->stepTimer++;
        if (state->stepTimer >= 0x3D) {
            state->liftSpeed = -0.1f;
            camResumePath();
            state->subState = 0;
            state->phase++;
            if (state->phase == 1) {
                func_80724994(1, 7, 0, 0, 0);
            }
            if (state->phase == 3) {
                state->subState = 7;
            }
        }
        break;
    case 6:
        state->liftSpeed = -0.1f;
        if (bounceDir == -1) {
            topReached = 1;
            if (sBounceLimit < state->stepTimer) {
                sfxPlayOnFreeSlot(0x17D, 0x3E80, 63.0, 1.0, 0, 0);
                sBounceLimit++;
                state->stepTimer = 0;
                if (sBounceLimit >= 0x10) {
                    sBounceLimit += 1;
                }
                if (sBounceLimit >= 0x1A) {
                    sBounceLimit = (randomLcgNext() & 3) + 4;
                    state->subState = 1;
                    state->repeatCount++;
                    sfxPlayOnFreeSlot(0x37F, 0x7D00, 63.0, 1.0, 0, 0);
                    sfxPlayOnFreeSlot(0x381, 0x7D00, 63.0, 1.0, 0, 0);
                }
                spawnParticle = 1;
            }
            sLightPulseTimer = 0x1E;
        }
        break;

    case 7:
        state->stepTimer++;
        state->liftSpeed = -0.1f;
        if (state->stepTimer >= 0x10) {
            for (j = 0; j < 4; j++) {
                actorDespawn(actorListFindActorById(j));
            }
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->alpha = 0;
            camStartPath(0, 4, 1);
            state->subState = 8;
        }
        break;
    case 8:
        state->liftSpeed = -0.1f;
        if (gActorGlobalState.volumeTriggerQueueCount != 0) {
            sfxAllocateChannel(0x35, 1.0);
            bossSpawnParticleRing(0x13D, gCurrentActor->x, gCurrentActor->y + 200.0f, gCurrentActor->z + 40.0f, 0x800, 1);
            state->subState = 9;
        }
        break;
    case 9:
        break;
    }
    if (state->phase == 3 && state->subState == 0) {
        if (state->repeatCount < 2) {
            state->subState = 6;
        } else {
            state->repeatCount = 0x14;
        }
    }
    if (prevSubState != state->subState) {
        state->stepTimer = 0;
    }
    if (spawnParticle != 0) {
        if (state->phase == 2 || state->phase == 3) {
            state->side++;
        } else {
            r = randomFloat();
            state->side += (s32)(r * 2.99f) + 1;
        }
        k = state->side;
        if (k >= 4) {
            state->side = k - 4;
        }
    }
    sLightPulseTimer++;
    if (topReached != 0) {
        level = (sLightPulseTimer & 0x1F) - 0x10;
        i = level;
        k = state->side;
        if (level < 0) {
            i = -level;
        }
        if (i >= 0x10) {
            i = 0xF;
        }
        level = (i << 4) & 0xFF;
        if (level && level) {} // FAKE: pins the level def before the x/z loads
        x = gBossSideOffsetX[k] * 0.33 + gCurrentActor->x;
        z = gBossSideOffsetZ[k] * 0.33 + gCurrentActor->z;
        lightAdd(x, 400.0f, z, x, 300.0f, z, 200.0f, 0, level, level, level);
        if (state->phase == 1) {
            k = state->side + 2;
            if (k >= 4) {
                k -= 4;
            }
            x = gBossSideOffsetX[k] * 0.33 + gCurrentActor->x;
            z = gBossSideOffsetZ[k] * 0.33 + gCurrentActor->z;
            lightAdd(x, 400.0f, z, x, 300.0f, z, 200.0f, 0, level, level, level);
        }
    }
    state->aggroTimer--;
    if (state->aggroTimer < 0) {
        state->aggroTimer = (randomLcgNext() & 0x7F) + 0x5A;
        lightSetColor(0.5f, 0.5f, 0.5f, -1);
        enemyAggroEnable();
    }
    D_80035B40 = bounceDir;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bossFollowerActorUpdate(void) {
    BossFollowerLink *link = gCurrentActor->customState;
    BossSpawnerState *parentState = link->parent->customState;
    AnimSlot *anim = gCurrentActor->sub4->model;
    static s16 sFireCooldown = 0x78; // function-local static (only user; shadows the file-scope definition, which the .data carve moves here) keeps uopt from pointerizing D_80035B74

    if (link->mirrored == 0) {
        f32 dx = gPrimaryPlayerActor->x - gCurrentActor->x;
        f32 dz = gPrimaryPlayerActor->z - gCurrentActor->z;
        gBossFollowerPlayerDistSq = dx * dx + dz * dz;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        controllerAnimSetStateIfChanged(gCurrentActor, link->slot + 0x668, 0.0f, 0.0f);
        gCurrentActor->drawDistance = 0xFA0;
    }
    if (gBossFollowerRaisedMask & (1 << link->slot)) {
        gCurrentActor->roll = (s16)(parentState->lift * 1024.0) - 0x400;
        gCurrentActor->pitch = D_80035B2C;
        if (anim != NULL) {
            if (D_80035B3C != anim->frame) {
                controllerApplyMotionWindow(gCurrentActor, anim, D_80035B3C);
            }
        }
    } else {
        gCurrentActor->roll = 0;
        if (anim != NULL) {
            s32 animId = link->slot + 0x66B;
            if (animId != anim->animId) {
                controllerAnimSetStateIfChanged(gCurrentActor, animId, 0.0f, 0.0f);
                sfxPlayOnFreeSlot(0x38D, 0x7D00, 63.0, 1.0, 0, 0);
            } else {
                controllerApplyMotionWindow(gCurrentActor, anim, anim->frame + 0.75f);
            }
            if (link->slot == 1) {
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
                sfxPlayOnFreeSlot(0x384, 0x7D00, 63.0, 1.0, 0, 0);
                actorDespawn(gCurrentActor);
            }
        }
    }
    if (link->mirrored == 0) {
        gCurrentActor->unk144 = 0xC;
        if (link->slot == 0) {
            if (parentState->fireFlag == 1) {
                if (link->parent->state == 0) {
                    sFireCooldown = 0x28;
                }
                sFireCooldown--;
                if (sFireCooldown < 0) {
                    f32 zo = gBossSideAimOffsetZ[parentState->side];
                    f32 xo = gBossSideAimOffsetX[parentState->side];
                    sFireCooldown = 0xA;
                    projectileSetTargetCoords(gCurrentActor->x + xo, gCurrentActor->y + 270.0f, gCurrentActor->z + zo);
                    projectileAimAndSpawn(0x2C, 1, 0.25f, gPrimaryPlayerActor->x, gPrimaryPlayerActor->y, gPrimaryPlayerActor->z, 2400.0f, gCurrentActor);
                }
            } else {
                sFireCooldown = 0;
            }
        }
        gCurrentActor->x = gBossSideOffsetX[parentState->side] + link->parent->x;
        gCurrentActor->z = gBossSideOffsetZ[parentState->side] + link->parent->z;
        gCurrentActor->yaw = gBossSideYaw[parentState->side];
    } else {
        s32 oppSide;
        gCurrentActor->unk144 = 1;
        oppSide = parentState->side + 2;
        if (oppSide >= 4) {
            oppSide -= 4;
        }
        gCurrentActor->x = gBossSideOffsetX[oppSide] + link->parent->x;
        if (gBossSideAimOffsetX) {}  // FAKE: deadsweep dead statement (steers uopt)
        gCurrentActor->z = gBossSideOffsetZ[oppSide] + link->parent->z;
        gCurrentActor->yaw = gBossSideYaw[oppSide];
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0x23;
        if (link->mirrored && link->mirrored) {} // FAKE: steers uopt colouring (const 35 -> a1)
        gCurrentActor->tintG = 0x23;
        gCurrentActor->tintB = 0x46;
        if (parentState->phase != 1) {
            gCurrentActor->flags &= ~4;
        } else {
            gCurrentActor->flags |= 4;
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
