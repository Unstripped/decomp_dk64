#include "common.h"
#include "proto/boss/3840_script.h"
#include "proto/boss/DAA0_spawner_follower.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/166A0_random.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/6AD90_collision.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/8D3E0_actor_list.h"
#include "proto/global/8F050_actor_config.h"
#include "proto/global/8F4B0.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/CC800_player_setup.h"
#include "proto/global/F56F0_player_weapon.h"

// DAA0: hidden translation-unit boundary at 0x80031AA0 (C920's .data/.rodata end 16-/8-aligned before it)
s16 gBossSideOffsetX[4] = { 0, 0x26C, 0, -0x26C };
s16 gBossSideOffsetZ[4] = { 0x26C, 0, -0x26C, 0 };
s16 gBossSideYaw[4] = { 0x800, 0xC00, 0, 0x400 };
s16 gBossSideAimOffsetX[4] = { 0, -0x4B, 0, 0x4B };
s16 gBossSideAimOffsetZ[4] = { -0x4B, 0, 0x4B, 0 };
s8 gBossFollowerRaisedMask = -1;
s16 gBossFollowerPitch = 0;
s8 gBossRaisedMaskSteps[4] = { 7, 3, 1, 0 };
s8 gBossRaisedMaskStep = 0;
u8 gBossSavedPlayerCollisionMode = 0xFF;
f32 gBossSpawnerSpinFrame = 0.0f;
s8 gBossSpawnerPrevBounceDir = 0;
s8 gBossKongOrder[5] = { 2, 3, 4, 0, 1 };
s16 gBossKongActorTypes[5] = { 2, 3, 4, 5, 6 };
u8 gBossKongSegmentFlags[5] = { 2, 1, 3, 4, 0 };
s16 gBossFollowerSpawnIds[4] = { 0xDC, 0xDD, 0xDE, 0xDF };

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
    /* 0x0C */ s16 aggroTimer; // light flash + weatherTriggerLightningFlash when it runs out
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
extern s8 gBossKongsFreed;
extern f32 gBossFollowerPlayerDistSq;

void bossSpawnerUpdate(void) {
    f32 r;
    f32 dx;
    s32 side;
    s32 i; // FAKE: the loop counter reused as the case 0/1 step threshold and the light level (refined in place to the intensity): one merged uopt range keeps the counter, the thresholds and the light magnitude in $t0 (a separate threshold or light-level local recolours the function)
    BossSpawnerState *state;
    s8 prevSubState;
    s8 hitPlayer;
    s8 bounceDir;
    s8 spawnParticle;
    s8 topReached;
    BossFollowerLink *link;
    s32 kong;
    f32 x;
    f32 z; // FAKE: the case 1 player offset reused as the light position: a separate dz recolours the case-1 offsets (z $f0 -> $f2, the cvt.d.s temp $f2 -> $f0 at 0x3f4-0x434)
    s16 j; // FAKE: the case 7 loop counter reused as the case 0 repeat limit: the merged range colours the limit $a1 (0x650/0x668/0x6a0), a separate limit takes $v0
    static s8 sLightPulseTimer = 0;
    static s8 D_80035B6C = 0;
    static s16 sBounceLimit = 0;

    state = gCurrentActor->customState;
    topReached = 0;
    spawnParticle = 0;
    hitPlayer = 0;
    if (!(gCurrentActor->flags & 0x10)) {
        gBossFollowerRaisedMask = 0xF;
        gBossRaisedMaskStep = 0;
        gBossSpawnerSpinFrame = 0.0f;
        state->aggroTimer = 0x1E;
        state->introTimer = 1;
        state->baseY = gCurrentActor->y;
        state->side = 0;
        D_80035B6C = 0;
        state->phase = 0;
        sBounceLimit = 5;
        for (i = 0; i != 8; i++) {
            if (actorSpawn(0xA6, gBossFollowerSpawnIds[i >> 1]) != 0) {
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
        gBossKongsFreed = 0;
        if (gPrimaryPlayerActor != NULL) {
            gPrimaryPlayerActor->state = 0x77;
            gPrimaryPlayerActor->subState = 0;
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
        if (gBossSavedPlayerCollisionMode == -1) {
            gBossSavedPlayerCollisionMode = gPrimaryPlayerActor->collisionMode;
        }
        gPrimaryPlayerActor->flags &= ~4;
        gPrimaryPlayerActor->collisionMode = 1;
        if (gActorGlobalState.volumeTriggerQueueCount != 0) {
            kong = gBossKongOrder[gBossKongsFreed];
            gCurrentActor->segmentFlags = 0;
            for (i = 4; gBossKongsFreed < i; i--) {
                actorSetSegmentFlag(gCurrentActor, gBossKongSegmentFlags[gBossKongOrder[i]]);
            }
            gBossKongsFreed++;
            kong = gBossKongActorTypes[kong];
            playerSetKongByActorType(kong);
            playerKongStopAudioChannels(gPrimaryPlayerActor, kong);
            gPrimaryPlayerActor->state = 0xC;
            gPrimaryPlayerActor->subState = 0;
            actorAppendPlayerLaunch(gCurrentActor, gPrimaryPlayerActor, 0, 180.0f, 0x46);
            gCurrentActor->state = 1;
            gPrimaryPlayerActor->collisionMode = gBossSavedPlayerCollisionMode;
        }
        break;
    case 1:
        gPrimaryPlayerActor->flags |= 4;
        dx = gPrimaryPlayerActor->x - gCurrentActor->x;
        z = gPrimaryPlayerActor->z - gCurrentActor->z;
        if (dx > 700.0 || dx < -700.0 || z > 700.0 || z < -700.0) {
            if (gBossKongsFreed < 5) {
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
    if (gPrimaryPlayerActor->state == 0x45 && gPrimaryPlayerActor->subState >= 2 && gBossFollowerPlayerDistSq < 10000.0) {
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
        if (state->phase == 2) {
            i = 5;
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
        if (bounceDir != 0 && gBossSpawnerPrevBounceDir == 0) {
            spawnParticle = 1;
            gBossFollowerPitch = 0;
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
        if (bounceDir != 0 && gBossSpawnerPrevBounceDir == 0) {
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
        gBossSpawnerSpinFrame += 1.0;
        if (gBossSpawnerSpinFrame > 24.0) {
            gBossSpawnerSpinFrame = 24.0f;
            state->stepTimer++;
            gBossFollowerPitch = mathSinF(state->stepTimer << 5) * 200.0f;
            if (state->stepTimer == 0x3F) {
                gBossSpawnerSpinFrame = 0.0f;
                gBossFollowerPitch = 0;
                gBossFollowerRaisedMask = gBossRaisedMaskSteps[gBossRaisedMaskStep];
                gBossRaisedMaskStep += 1;
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
                spawnNodesSendVolumeTrigger(1, 7, 0, 0, 0);
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
        side = state->side;
        if (side >= 4) {
            state->side = side - 4;
        }
    }
    sLightPulseTimer++;
    if (topReached != 0) {
        i = (sLightPulseTimer & 0x1F) - 0x10;
        side = state->side;
        if (i < 0) {
            i = -i;
        }
        if (i >= 0x10) {
            i = 0xF;
        }
        i <<= 4;
        if (gCurrentActor) {} // FAKE: ends the block after i <<= 4 so the intensity spill takes the second temp slot 0x44 (sw/lw v0 at 0xeec/0xf3c; without it 0x48)
        x = gBossSideOffsetX[side] * 0.33 + gCurrentActor->x;
        z = gBossSideOffsetZ[side] * 0.33 + gCurrentActor->z;
        lightAdd(x, 400.0f, z, x, 300.0f, z, 200.0f, 0, i, i, i);
        if (state->phase == 1) {
            side = state->side + 2;
            if (side >= 4) {
                side -= 4;
            }
            x = gBossSideOffsetX[side] * 0.33 + gCurrentActor->x;
            z = gBossSideOffsetZ[side] * 0.33 + gCurrentActor->z;
            lightAdd(x, 400.0f, z, x, 300.0f, z, 200.0f, 0, i, i, i);
        }
    }
    state->aggroTimer--;
    if (state->aggroTimer < 0) {
        state->aggroTimer = (randomLcgNext() & 0x7F) + 0x5A;
        lightSetColor(0.5f, 0.5f, 0.5f, -1);
        weatherTriggerLightningFlash();
    }
    gBossSpawnerPrevBounceDir = bounceDir;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bossFollowerActorUpdate(void) {
    BossFollowerLink *link = gCurrentActor->customState;
    BossSpawnerState *parentState = link->parent->customState;
    AnimSlot *anim = gCurrentActor->sub4->model;
    s32 id; // FAKE: one local for the anim id and the opposite side merges their uopt ranges (opposite side $v0 ahead of its *2 index $v1)
    static s16 sFireCooldown = 0x78; // function-local static (its only user) keeps uopt from pointerizing D_80035B74 (Q0498)

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
        gCurrentActor->pitch = gBossFollowerPitch;
        if (anim != NULL) {
            if (gBossSpawnerSpinFrame != anim->frame) {
                controllerApplyMotionWindow(gCurrentActor, anim, gBossSpawnerSpinFrame);
            }
        }
    } else {
        gCurrentActor->roll = 0;
        if (anim != NULL) {
            id = link->slot + 0x66B;
            if (id != anim->animId) {
                controllerAnimSetStateIfChanged(gCurrentActor, id, 0.0f, 0.0f);
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
                }
            }
            if (gCurrentActor->y < 0.0) {
                sfxPlayOnFreeSlot(0x384, 0x7D00, 63.0, 1.0, 0, 0);
                actorDespawn(gCurrentActor);
            }
        }
    }
    if (link->mirrored == 0) {
        gCurrentActor->collisionMode = 0xC;
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
        gCurrentActor->collisionMode = 1;
        id = parentState->side + 2;
        if (id >= 4) {
            id -= 4;
        }
        gCurrentActor->x = gBossSideOffsetX[id] + link->parent->x;
        gCurrentActor->z = gBossSideOffsetZ[id] + link->parent->z;
        gCurrentActor->yaw = gBossSideYaw[id];
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0x23;
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
