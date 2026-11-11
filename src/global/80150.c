#include "common.h"
#include "sched.h"
#include "actor.h"
#define PROTO_SKIP_actorDespawn // FAKE: callee prototype steer
#define PROTO_SKIP_flagGet // FAKE: callee prototype steer
#include "proto/global/100180.h"
#include "proto/global/103AB0.h"
#include "proto/global/104F0.h"
#include "proto/global/10D2D0.h"
#include "proto/global/112080.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1292F0.h"
#include "proto/global/1295B0.h"
#include "proto/global/131B0.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2DE90.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/450.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/80150.h"
#include "proto/global/8CA50.h"
#include "proto/global/8D3E0.h"
#include "proto/global/8F050.h"
#include "proto/global/90D80.h"
#include "proto/global/936B0.h"
#include "proto/global/9DD70.h"
#include "proto/global/A7710.h"
#include "proto/global/AA960.h"
#include "proto/global/ACDC0.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/F56F0.h"
#include "proto/global/FCCD0.h"

typedef struct ActorMapFlag {
    u16 map;
    u8 listId;
    s16 flag;
} ActorMapFlag;



typedef struct ActorAnimLookup {
    struct {
        s16 unk0;
        s16 unk2;
    } arr[5];
} ActorAnimLookup;


typedef struct KongActionEntry {
    s16 model;
    s16 kongIndex;
    u8 action;
    u8 unk5;
} KongActionEntry;

extern Actor *gCurrentActor;
extern ActorGlobalState gActorGlobalState;
extern PlayerState *gActivePlayerState;
extern Actor *gPrimaryPlayerActor;
extern u16 *gActorScriptIndexTable;
extern s32 gCurrentMap;
extern s32 D_8071FE08;
extern u8 gPlayerCharacterId;
extern ActorMapFlag D_8074E7A0[];
extern s16 D_8074E7E0[];
extern KongActionEntry D_8074E814[];
extern ActorAnimLookup D_8074E834;
extern s32 sKongNameTextIds[];
extern u8 D_80720120;
extern u8 D_80720340;
extern u8 D_8072038C;

s32 actorDespawn(Actor *);  // FAKE: callee prototype steer
s32 flagGet(s16, s32);  // FAKE: callee prototype steer

s32 tagBarrelIsSpecial(Actor *actor) {
    s32 count = 4; // FAKE: value-named constant local steers regalloc (literal 4: mismatch)
    s32 listId = actorListFindIdByActor(actor);
    s32 i;

    for (i = 0; i < count; i++) {
        if (gCurrentMap == D_8074E7A0[i].map && listId == D_8074E7A0[i].listId) {
            return flagGet(D_8074E7A0[i].flag, 0);
        }
    }
    return 0;
}


typedef struct ActorB4C8Spawn {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s32 unk14;
    s32 unk18;
} ActorB4C8Spawn;

typedef struct ActorB4C8State {
    Actor *rider;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 timer;
    u8 camPath;
} ActorB4C8State;


extern u8 D_8071FBC8;

void tagBarrelInitPeerState(void) {
    ActorB4C8State *sub = gCurrentActor->customState;
    PlayerState *peer;
    s32 i;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->sub4->boneRotations = heapAlloc(0x10);
        gCurrentActor->sub4->boneRotations[0].weight = 0x7F;
        gCurrentActor->sub4->boneRotations[0].bone = 2;
        gCurrentActor->sub4->boneRotations[0].rotX = (u32)((((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk0 * 65536.0f) / 360.0f);
        gCurrentActor->sub4->boneRotations[0].rotY = 0;
        gCurrentActor->sub4->boneRotations[0].rotZ = 0;
        gCurrentActor->sub4->boneRotations[1].weight = 0;
        sub->unk4 = ((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk4;
        sub->unk8 = ((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk8;
        sub->unkC = ((ActorB4C8Spawn *)gCurrentActor->spawnData)->unkC;
        sub->unk10 = ((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk10;
        sub->camPath = ((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk14;
        if (((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk18 == 1) {
            if (tagBarrelIsSpecial(gCurrentActor) == 0) {
                gCurrentActor->state = 0x14;
                gCurrentActor->unk144 = 1;
                gCurrentActor->flags &= ~0x8000;
                gCurrentActor->alpha = 0;
            }
        }
        if (gCurrentMap == 0x22) {
            gCurrentActor->flags |= 0x400;
        }
        if (gCurrentMap == 0xC7) {
            gCurrentActor->drawDistance = 0x226;
        }
    }
    if (gActorGlobalState.bossFightPhase == 4) {
        sub->rider = gActorGlobalState.targetActor;
        gCurrentActor->state = 1;
        if (0) {} // FAKE: empty branch steers uopt web colouring (gActorGlobalState address takes v1 not v0)
        sub->timer = 0xA;
        gCurrentActor->unk144 = 1;
        sub->rider->yaw = gCurrentActor->yaw;
        camStartPath(NULL, sub->camPath, 1);
    }
    switch (gCurrentActor->state) {
        case 1:
            if (--sub->timer == 6) {
                scriptSetActorRampTarget(gCurrentActor, 1.0f, 0);
                controllerAnimSetState(gCurrentActor, 0x346, 0, 0.0f);
            }
            if (sub->timer == 0) {
                gCurrentActor->state = 2;
            }
            break;
        case 2:
            actorAppendCallback(sub->rider, gCurrentActor, 0x40, 1, 0, 0);
            peer = sub->rider->customState;
            peer->unkB0 = sub->unk8;
            peer->unkB4 = sub->unkC;
            peer->unkB8 = sub->unk10;
            actorAppendCallbackPayloadAAB8(gCurrentActor, sub->rider, gCurrentActor->yaw, 0.0f, sub->unk4);
            actorQueueDelayedCallback(gCurrentActor, gCurrentActor, 0x800, 2, 0, 0, 0xA);
            effectSetMode(2);
            effectSetDepth(1);
            effectCreateAtActorBone(&D_8071FBC8, 2.0f, gCurrentActor, 1, 2);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x17, 0xFF, 0x7F, 0x19, 0x1E, 0.3f, 0);
            gCurrentActor->state++;
            sub->timer = 4;
            break;
        case 3:
            if (sub->timer-- == 0) {
                gCurrentActor->state = 0;
            }
            break;
        case 0:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            break;
        case 20:
            for (i = 0; i < gActorGlobalState.unk254; i++) {
                if (gActorGlobalState.unk258[i] == 1) {
                    gCurrentActor->unk144 = 2;
                    gCurrentActor->state = 0x15;
                }
            }
            if (tagBarrelIsSpecial(gCurrentActor) != 0) {
                gCurrentActor->alpha = 0xFF;
                gCurrentActor->flags |= 0x8000;
                gCurrentActor->state = 0;
            }
            break;
        case 21:
            gCurrentActor->alpha += 10;
            if (gCurrentActor->alpha >= 0xF1) {
                gCurrentActor->flags |= 0x8000;
                gCurrentActor->state = 0;
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (sub) {} // FAKE: extends sub across the final call so it takes a saved register
}

void tagBarrelPeerUpdate(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->drawDistance = 0x7D0;
    }
    tagBarrelInitPeerState();
}



void tagBarrelAnimSetSpeed(s32 spawnType) {
    if (!(gCurrentActor->flags & 0x10) && (spawnType == 0x13)) {
        animSetSpeed(gCurrentActor, 0, 0.5f);
        animSetLoopMode(gCurrentActor, 0, 0);
        animSetDirection(gCurrentActor, 0, 0);
        animSetLoopLimit(gCurrentActor, 0, -1);
    }
    switch (gCurrentActor->state) {
        case 0:
            break;
        case 10:
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x31, 0xFF, 0x7F, 1);
            effectSetDepth(0);
            effectSetDuration(1);
            effectCreateAtPosition(&D_8071FE08, 0.5f, gCurrentActor->x, gCurrentActor->y + 7.0f, gCurrentActor->z);
            actorListSpawnNodeEntryDefault(spawnType, gCurrentActor->x, gCurrentActor->y + 8.3, gCurrentActor->z, 0, 1.0f, gCurrentActor);
            gCurrentActor->state++;
            break;
        case 11:
            if (gActorGlobalState.unk38 != 0) {
                gCurrentActor->state = 0x14;
            }
            break;
        case 20:
            if (spawnType == 0x95) {
                gCurrentActor->yawSpeed = 0x1E;
                gCurrentActor->state = 0x15;
            }
            break;
        case 21:
            if (gCurrentActor->yawSpeed != 0) {
                gCurrentActor->yawSpeed--;
            } else {
                gCurrentActor->state = 0xA;
            }
            break;
    }
    if (spawnType == 0x13) {
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}

void tagBarrelSpawnType13A(void) {
    tagBarrelAnimSetSpeed(0x13);
}

void tagBarrelSpawnType13B(void) {
    tagBarrelAnimSetSpeed(0x13);
}

void tagBarrelSpawnType13C(void) {
    tagBarrelAnimSetSpeed(0x13);
}

void tagBarrelSpawnType13D(void) {
    tagBarrelAnimSetSpeed(0x13);
}

void tagBarrelSpawnType13E(void) {
    tagBarrelAnimSetSpeed(0x13);
}

void tagBarrelSpawnType13F(void) {
    tagBarrelAnimSetSpeed(0x13);
}


void tagBarrelCheckPlayerState(void) {
    PlayerState *extra;
    s32 released = 0;

    extra = gPrimaryPlayerActor->customState;
    if ((gActorGlobalState.unk38 != 0) && (extra->stateFlags & 0x200000)) {
        released = 1;
    }
    if (!(gCurrentActor->flags & 0x10) || released) {
        actorListSpawnNodeEntryDefault(0x55, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0, 1.0f, gCurrentActor);
    }
}

void tagBarrelSpawnType95(void) {
    tagBarrelAnimSetSpeed(0x95);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    gCurrentActor->y = gCurrentActor->floorY;
}

typedef struct TagBarrelFallState {
    /* 0x0 */ u8 inRange;
    /* 0x1 */ u8 falling;
} TagBarrelFallState;

void tagBarrelCheckProximity(void) {
    u8 triggered;
    TagBarrelFallState *state;

    triggered = 0;
    state = gCurrentActor->customState;
    tagBarrelCheckProximityAndFall(0x13, &state->inRange, &state->falling, &triggered);
}

typedef struct TagBarrelProximityState {
    /* 0x0 */ s16 spawnType;
    /* 0x2 */ u8 inRange;
    /* 0x3 */ u8 falling;
    /* 0x4 */ u8 triggered;
} TagBarrelProximityState;

void tagBarrelInitDrawDistanceAndState(void) {
    TagBarrelProximityState *state = gCurrentActor->customState;
    s16 i;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->drawDistance = 0x7D0;
        state->spawnType = 0x1A;
    }
    for (i = 0; i < gActorGlobalState.unk254; i++) {
        switch (gActorGlobalState.unk258[i]) {
        case 1:
            state->spawnType = 0x60;
            break;
        case 2:
            state->spawnType = 0;
            break;
        case 3:
            state->spawnType = 0x1A;
            break;
        }
    }
    if (state->spawnType != 0) {
        if (tagBarrelCheckProximityAndFall(state->spawnType, &state->inRange, &state->falling, &state->triggered)) {
            state->spawnType = 0x1A;
        }
    } else {
        if (gActorGlobalState.unk38 != 0) {
            state->triggered = 1;
        }
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}

void tagBarrelCheckProximity1A(void) {
    TagBarrelProximityState *state = gCurrentActor->customState;

    tagBarrelCheckProximityAndFall(0x1A, &state->inRange, &state->falling, &state->triggered);
}

extern u8 gPlayerCount;
extern PlayerStruct *gPlayerSlots;

s32 tagBarrelCheckProximityAndFall(s32 spawnType, u8 *inRange, u8 *falling, u8 *triggered) {
    volatile u8 spawn; // FAKE: force stack home
    s32 pad[2];
    u8 i;
    f32 minDist;
    f32 dz;
    f32 dx;
    f32 dist;

    spawn = 0;
    minDist = 99999.0f;
    if (gCurrentActor->flags & 0x10) {
        animSetSpeed(gCurrentActor, 0, 0.5f);
        animSetLoopMode(gCurrentActor, 0, 0);
        animSetDirection(gCurrentActor, 0, 0);
        animSetLoopLimit(gCurrentActor, 0, -1);
        if (gActorGlobalState.unk38 != 0 || *inRange != 0 || *triggered != 0) {
            *triggered = 0;
            spawn = 1;
        }
        if (spawn != 0) {
            i = 0;
            if (gPlayerCount > 0) {
                do {
                    if (gPlayerSlots[i].unk0 != 0) {
                        Actor *player = gPlayerSlots[i].actor;
                        dz = player->z - gCurrentActor->z;
                        dx = player->x - gCurrentActor->x;
                        dist = sqrtf((dz * dz) + (dx * dx));
                        if (dist < minDist) {
                            minDist = dist;
                        }
                    }
                    i++;
                } while (i < gPlayerCount);
            }
            if (minDist > 12.0) {
                *inRange = 0;
            } else {
                *inRange = 1;
                spawn = 0;
            }
        }
    } else {
        spawn = 1;
        *inRange = 0;
        gCurrentActor->speedY = -10.0f;
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        if (actorHasActiveMovementFlags(gCurrentActor) != 0) {
            *falling = 1;
        } else {
            *falling = 0;
        }
    }
    if (spawn != 0) {
        actorListSpawnNodeEntryDefault(spawnType, gCurrentActor->x, gCurrentActor->y + 8.3, gCurrentActor->z, 0, 1.0f, gCurrentActor);
        if (gCurrentActor->flags & 0x10) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x31, 0xFF, 0x7F, 1);
            effectSetDepth(0);
            effectSetDuration(1);
            effectCreateAtPosition(&D_8071FE08, 0.5f, gCurrentActor->x, gCurrentActor->y + 7.0f, gCurrentActor->z);
        }
    }
    if (*falling != 0) {
        gCurrentActor->speedY = -10.0f;
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    return spawn;
}

typedef struct ActorC2B8State {
    u8 soundPlaying;
    u8 pad1[3];
    f32 targetSpeed;
    u8 pushed;
} ActorC2B8State;




void tagBarrelRotateUpdate(void) {
    ActorC2B8State *state;
    f32 speed;
    f32 target;
    s16 yaw;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags2 |= 4;
        gCurrentActor->flags |= 0x80;
        state->soundPlaying = 0;
        state->pushed = 0;
        state->targetSpeed = 0.0f;
    }
    if (!(gCurrentActor->flags2 & 4)) {
        gCurrentActor->speedXZ = 0.0f;
    }
    if (gActorGlobalState.unk90 != 0) {
        state->pushed = 1;
    }
    if (gActorGlobalState.unk91 != 0) {
        if (state->soundPlaying == 0) {
            sfxPlayActorSound(gCurrentActor, 0x10C, 0, 1, 0, 0xFF, 1.0f, 0);
            state->soundPlaying = 1;
        }
        state->targetSpeed = (f64) gActorGlobalState.unk94 / 1.1;
        gCurrentActor->moveYaw = gActorGlobalState.unk92;
        speed = gCurrentActor->speedXZ;
        if (speed < state->targetSpeed) {
            gCurrentActor->speedXZ = speed + 0.8;
            target = state->targetSpeed;
            if (target < gCurrentActor->speedXZ) {
                gCurrentActor->speedXZ = target;
            }
        } else {
            gCurrentActor->speedXZ = speed - 1.5;
            if (gCurrentActor->speedXZ < 0.0f) {
                gCurrentActor->speedXZ = 0.0f;
            }
        }
        gCurrentActor->unkFA = 0x64;
        yaw = gCurrentActor->moveYaw;
        actorStepPhysics(gCurrentActor, yaw, yaw);
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        gCurrentActor->y = gCurrentActor->floorY;
        if (state->pushed == 0) {
            gCurrentActor->unk144 = 0x3C;
        }
    } else {
        if ((state->soundPlaying != 0) && ((f64) gCurrentActor->speedXZ == 0.0)) {
            state->soundPlaying = 0;
            sfxStopSlotSound(gCurrentActor, 0);
        }
        state->targetSpeed = 0.0f;
        speed = gCurrentActor->speedXZ;
        if (speed < 0.0f) {
            gCurrentActor->speedXZ = speed + 0.8;
            target = state->targetSpeed;
            if (target < gCurrentActor->speedXZ) {
                gCurrentActor->speedXZ = target;
            }
        } else {
            gCurrentActor->speedXZ = speed - 1.5;
            if (gCurrentActor->speedXZ < 0.0f) {
                gCurrentActor->speedXZ = 0.0f;
            }
        }
        gCurrentActor->unkFA = 0x64;
        yaw = gCurrentActor->moveYaw;
        actorStepPhysics(gCurrentActor, yaw, yaw);
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        if (state->pushed == 0) {
            if (((f64) gCurrentActor->speedXZ == 0.0) || !(gCurrentActor->flags & 0x10)) {
                gCurrentActor->unk144 = 2;
            } else {
                gCurrentActor->unk144 = 0x3C;
            }
        }
        gCurrentActor->y = gCurrentActor->floorY;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorTransformCameraUpdateA(void) {
    actorTransformCameraUpdate();
}

void actorTransformCameraUpdateB(void) {
    actorTransformCameraUpdate();
}

void actorTransformCameraUpdateC(void) {
    actorTransformCameraUpdate();
}

void textMarkerUpdateMatrixWrapper(void) {
    textMarkerUpdateMatrix();
}

void actorTransformCameraUpdateD(void) {
    actorTransformCameraUpdate();
}

extern Actor *gSpawnedActor;
typedef struct ActorC71CState {
    /* 0x00 */ struct Actor *holder;
    /* 0x04 */ s32 throwFrame;
    /* 0x08 */ f32 pitch;
    /* 0x0C */ s32 settleTimer;
    /* 0x10 */ f32 holdYaw;
    /* 0x14 */ f32 spin;
    /* 0x18 */ u8 waterBounces;
    /* 0x19 */ u8 bounceCooldown;
    /* 0x1A */ u16 groundBounces;
    /* 0x1C */ f32 floatBaseY;
    /* 0x20 */ s32 floatFrame;
    /* 0x24 */ f32 floatVelY;
    /* 0x28 */ f32 floatPitch;
    /* 0x2C */ u32 timer;
    /* 0x30 */ u8 tipDir;
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ f32 sinkSpeed;
    /* 0x38 */ u8 prevState;
    /* 0x39 */ u8 released;
    /* 0x3A */ u8 fadeTimer;
} ActorC71CState;


extern s32 gGlobalOverlayFlags;
extern s16 gCurrentCharacterIndex;
extern u32 gFrameCounter;
extern s8 D_80029FA0;
extern u8 D_8071FC40;
extern u8 D_8072030C;
extern s16 D_807502D0;
extern f32 D_807502E4;
extern s16 D_80753444[];

f32 sinApprox(f32);

void actorTransformCameraUpdate(void) {
    ActorC71CState *state;
    f32 mtx[4][4];
    f32 rot[4][4];
    f32 bob;
    f32 brightness;
    s16 yaw;
    PlayerState *holderState;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unkFA = 0x270F;
        state->prevState = 0;
        state->released = 0;
        if (gCurrentActor->actorType == 0x1A) {
            gCurrentActor->flags |= 0x1000;
            effectSetDepth(1);
            effectSetDuration(-1);
            effectSetMaxDistance(gCurrentActor->drawDistance * 0.75);
            effectCreateAtActorBone(&D_8072030C, 0.14f, gCurrentActor, 1, 2);
            actorClearNodeFlag(gCurrentActor, 3);
        }
        gCurrentActor->floorY = 99999.0f;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        if (actorHasActiveMovementFlags(gCurrentActor)) {
            gCurrentActor->state = 2;
            gCurrentActor->flags2 |= 1;
            state->settleTimer = 0x1E;
            gCurrentActor->unk144 = 2;
            state->pitch = 360.0f;
            state->spin = 0.0f;
        }
        gCurrentActor->flags2 |= 0x40;
    }

    if (gActorGlobalState.unk24 != 0) {
        if (state->released == 0) {
            state->holder = gActorGlobalState.unk28;
            gCurrentActor->state = 1;
            state->pitch = 360.0f;
            actorCallbackMaskDisable(gCurrentActor, 0x8000);
            actorCollisionEventsCancel(state->holder, 1);
            gCurrentActor->unk144 = 0x2C;
            animationOwnerFreeBuffer(gCurrentActor);
        } else {
            actorReleaseFromPlayerHold(gCurrentActor);
        }
    }

    if (gActorGlobalState.unk25 != 0) {
        gCurrentActor->state = 2;
        state->settleTimer = 0x1E;
        gCurrentActor->unk144 = 0x3C;
        actorCallbackMaskEnable(gCurrentActor, 0x8000);
    }

    if (((gActorGlobalState.unk15 != 0) || (gActorGlobalState.bossFightPhase == 9)) && (state->released == 0)) {
        gCurrentActor->state = 4;
        actorReleaseFromPlayerHold(gCurrentActor);
    }

    if (state->released != 0 && (gActorGlobalState.unk15 != 0 || gActorGlobalState.bossFightPhase == 9)) {
        gCurrentActor->unk144 = 1;
    }

    if (gActorGlobalState.unk2C != 0) {
        gCurrentActor->state = 3;
        gCurrentActor->unk144 = 0x3C;
        actorCallbackMaskEnable(gCurrentActor, 0x8000);
        gCurrentActor->yaw = gActorGlobalState.unk36;
        gCurrentActor->moveYaw = gActorGlobalState.unk36;
        gCurrentActor->speedY = gActorGlobalState.unk30;
        state->throwFrame = gFrameCounter;
        state->waterBounces = 0;
        state->groundBounces = 0;
        gCurrentActor->speedXZ = gActorGlobalState.unk34;
        actorCollisionEventsCancel(state->holder, 1);
    }

    actorUpdatePrevContactFlags(gCurrentActor);
    switch (gCurrentActor->state) {
    case 0:
        gCurrentActor->unk144 = 2;
        state->pitch = 360.0f;
        state->spin = 0.0f;
        func_8066E6C8(gCurrentActor, 0, 1);
        func_8066E6C8(gCurrentActor, 1, 0);
        gCurrentActor->flags2 |= 1;
        break;
    case 1:
        func_8066E6C8(gCurrentActor, 0, 0);
        func_8066E6C8(gCurrentActor, 1, 0);
        holderState = state->holder->customState;
        state->pitch = holderState->holdPitch;
        if (state->pitch < 0.0) {
            state->pitch += 360.0;
        }
        state->holdYaw = state->holder->yaw / 4095.0 * 360.0;
        gCurrentActor->flags2 &= ~1;
        break;
    case 2:
        func_8066E6C8(gCurrentActor, 0, 1);
        func_8066E6C8(gCurrentActor, 1, 0);
        if (--state->settleTimer == 0) {
            gCurrentActor->state = 0;
        } else if (actorHasActiveMovementFlags(gCurrentActor)) {
            state->settleTimer = 0x1E;
        }
        state->pitch += 16.0;
        if (state->pitch > 360.0) {
            state->pitch = 360.0f;
        }
        gCurrentActor->speedY = -200.0f;
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->flags2 |= 1;
        break;
    case 3:
        func_8066E6C8(gCurrentActor, 0, 1);
        func_8066E6C8(gCurrentActor, 1, 1);
        gCurrentActor->speedY += D_807502E4;
        if (gCurrentActor->speedY < D_807502D0) {
            gCurrentActor->speedY = D_807502D0;
        }
        state->spin -= 10.0f;
        if (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->yaw) == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x23, 0xFF, 0x7F, 1);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x17, 0xFF, 0x7F, 1);
            gCurrentActor->state = 8;
        }
        gCurrentActor->flags2 &= ~1;
        break;
    case 4:
        state->released = 1;
        gCurrentActor->state = 8;
        break;
    case 5:
        func_8066E6C8(gCurrentActor, 0, 1);
        func_8066E6C8(gCurrentActor, 1, 1);
        state->floatPitch -= 3.0;
        if (state->floatPitch < 270.0) {
            state->floatPitch = 270.0f;
        }
        bob = sinApprox((f32)state->floatFrame / 12.6);
        gCurrentActor->y = state->floatBaseY + (f32)(bob * 1.5);
        bob = sinApprox((f32)state->floatFrame / 9.34);
        state->pitch = state->floatPitch + bob * 7.0f;
        state->floatFrame++;
        bob = -5.0 - state->floatVelY;
        bob = bob / -5.0;
        bob = bob * -0.5;
        if (gActorGlobalState.unk39 == 0) {
            bob = -0.5 - bob;
            bob = 0.0 - bob;
        }
        state->floatVelY += bob;
        gCurrentActor->y += state->floatVelY;
        if (--state->timer == 0 || state->timer == 5 || state->timer == 10 ||
            state->timer == 15 || state->timer == 20 || state->timer == 26) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x55, 0xFF, 0xA7 - state->timer * 2, 0);
        }
        if (state->timer == 0 || gCurrentActor->waterY < gCurrentActor->floorY) {
            gCurrentActor->state = 6;
            if (sinApprox((f32)state->floatFrame / 9.34) > 0.0) {
                state->tipDir = 1;
            } else {
                state->tipDir = 0;
            }
            state->sinkSpeed = 0.1f;
        }
        gCurrentActor->speedY = 0.0f;
        gCurrentActor->speedXZ = 35.0f;
        gCurrentActor->flags2 |= 1;
        pathFollowUpdateHeading(gCurrentActor, 0);
        if (gCurrentActor->pathFollow->unkC == 0) {
            gCurrentActor->moveYaw = gCurrentActor->pathFollow->unkE;
            gCurrentActor->speedXZ = gCurrentActor->pathFollow->unk10;
        } else {
            gCurrentActor->speedXZ = 0.0f;
        }
        if (gCurrentActor->hasArcBounds != 0) {
            yaw = gCurrentActor->moveYaw;
            mathAngleClampToArc(yaw, yaw, gCurrentActor->arcYawMin, gCurrentActor->arcYawMax, &gCurrentActor->unkF2);
            gCurrentActor->moveYaw = gCurrentActor->unkF2;
        }
        break;
    case 6:
        if ((randomLcgNext() / 100000 % 3) == 0) {
            effectSetDepth(1);
            effectSetDuration(-1);
            effectSetCallback(effectWobbleRiseUpdate);
            effectCreateAtPosition(&D_8071FC40, 0.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
        if (state->tipDir != 0) {
            if (state->tipDir == 1) {
                state->pitch += 1.5;
                if (state->pitch > 360.0) {
                    state->pitch = 360.0f;
                }
            }
        } else {
            state->pitch -= 1.5;
            if (state->pitch < 0.0) {
                state->pitch = 0.0f;
            }
        }
        state->timer++;
        if ((state->timer & 3) == 0 && state->timer < 29) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x55, 0xC0 - state->timer * 6, state->timer * 2 + 0x50, 0);
        }
        state->sinkSpeed += 2.0;
        if (state->sinkSpeed > 40.0) {
            state->sinkSpeed = 40.0f;
        }
        gCurrentActor->speedY = -state->sinkSpeed;
        gCurrentActor->speedXZ = 0.0f;
        if (gCurrentActor->distToFloor < 0.5) {
            gCurrentActor->state = 7;
            state->timer = 0x78;
        }
        gCurrentActor->flags2 &= ~1;
        break;
    case 7:
        gCurrentActor->y -= 0.15;
        if (--state->timer == 0) {
            gCurrentActor->state = 4;
        }
        gCurrentActor->flags2 &= ~1;
        break;
    case 8:
        if ((gGlobalOverlayFlags & 1) && camIsCutsceneActive()) {
            actorDespawn(gCurrentActor);
        } else {
            switch (gCurrentActor->actorType) {
            case 0x1A:
                tagBarrelSpawnActorSmokePuffs(1, 1);
                gCurrentActor->flags &= ~0x8000;
                gCurrentActor->alpha = 0;
                gCurrentActor->state = 9;
                state->fadeTimer = 0x14;
                if (!(gGlobalOverlayFlags & 1)) {
                    actorSetNodeFlag(gCurrentActor, 3);
                }
                actorClearNodeFlag(gCurrentActor, 1);
                actorClearNodeFlag(gCurrentActor, 2);
                break;
            case 0x95:
                actorSpawn(0xDE, 0xE5);
                actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.15f);
                gSpawnedActor->parentActor = gCurrentActor->parentActor;
                gCurrentActor->parentActor = NULL;
                gSpawnedActor->y = gCurrentActor->floorY;
                goto block_despawn;
            case 0x85:
                D_80029FA0--;
            default:
            block_despawn:
                tagBarrelDespawnEffects();
                actorDespawn(gCurrentActor);
                break;
            }
        }
        break;
    case 9:
        if (state->fadeTimer == 0) {
            actorDespawn(gCurrentActor);
        } else {
            state->fadeTimer--;
        }
        brightness = state->fadeTimer / 20.0f * 200.0;
        if (brightness > 130.0) {
            brightness = 200.0f;
        }
        lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, brightness, 0, 0xFF, 0xFF, 0xFF);
        camStartShakeFromPoint(((PlayerState *)gPrimaryPlayerActor->customState)->camActor, 5, 10, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
        break;
    }

    if (gCurrentActor->state == 2 || gCurrentActor->state == 3 || gCurrentActor->state == 5 || gCurrentActor->state == 6) {
        if (gCurrentActor->state != 5) {
            gCurrentActor->moveYaw = gCurrentActor->yaw;
        }
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 7.0f);
        if (gCurrentActor->state == 2 && state->pitch == 360.0f && (gCurrentActor->y - gCurrentActor->prevY) < -2.0f && (gGlobalOverlayFlags & 1)) {
            actorReleaseFromPlayerHold(gCurrentActor);
            gCurrentActor->state = 4;
            state->released = 1;
        }
        if (gCurrentActor->state == 3 && gCurrentActor->actorType == 0x1A && D_80753444[gCurrentCharacterIndex] < gFrameCounter - state->throwFrame) {
            gCurrentActor->state = 4;
        }
        if (gCurrentActor->state == 3 && (gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
            gCurrentActor->speedY = 140.0f;
            state->groundBounces++;
            if ((gCurrentActor->actorType == 0x1A && state->groundBounces == 4) || (gCurrentActor->actorType == 0x95 && state->groundBounces == 2)) {
                gCurrentActor->state = 4;
            }
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x32, 0xFF, 0x7F, 1);
        }
        if (gCurrentActor->state == 2 && (gCurrentActor->contactFlags & 4)) {
            gCurrentActor->state = 5;
            gCurrentActor->y = gCurrentActor->waterY;
            state->timer = 1000;
            state->floatBaseY = gCurrentActor->y - 1.5;
            state->floatFrame = 0;
            state->floatPitch = state->pitch;
        }
        if (gCurrentActor->state == 5) {
            state->floatBaseY = gCurrentActor->waterY;
        }
        if (gCurrentActor->state == 3 && (gCurrentActor->contactFlags & 4) && state->bounceCooldown == 0) {
            switch (state->waterBounces) {
            case 0:
                gCurrentActor->speedY = 180.0f;
                break;
            case 1:
                gCurrentActor->speedY = 140.0f;
                break;
            case 2:
                gCurrentActor->speedY = 100.0f;
                break;
            default:
                gCurrentActor->state = 5;
                gCurrentActor->y = gCurrentActor->waterY;
                state->timer = 1000;
                state->floatBaseY = gCurrentActor->y - 1.5;
                state->floatFrame = 0;
                state->floatPitch = state->pitch;
                break;
            }
            state->waterBounces++;
            state->bounceCooldown = 3;
            gCurrentActor->speedXZ -= 20.0;
        } else if (state->bounceCooldown != 0) {
            state->bounceCooldown--;
        }
        gCurrentActor->floorSlopeYaw = 0x3FF;
        gCurrentActor->floorSlopePitch = 0x3FF;
    } else {
        gCurrentActor->attachMode = 0;
        gCurrentActor->contactFlags &= ~0x408;
    }

    state->prevState = gCurrentActor->state;
    if (gCurrentActor->state != 9) {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
    }
    guScaleF(mtx, gCurrentActor->sub4->scaleX, gCurrentActor->sub4->scaleY, gCurrentActor->sub4->scaleZ);
    guRotateF(rot, state->spin, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx, rot, mtx);
    guRotateF(rot, gCurrentActor->yaw / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx, rot, mtx);
    guRotateF(rot, state->pitch - gActorGlobalState.unkF0, 1.0f, 0.0f, 0.0f);
    guMtxCatF(mtx, rot, mtx);
    guRotateF(rot, (state->holdYaw + 90.0f) - gActorGlobalState.unkF4, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx, rot, mtx);

    if (gCurrentActor->state == 3) {
        if (gCurrentActor->floorSlopePitch < 1000) {
            guRotateF(rot, -(gCurrentActor->floorSlopeYaw / 4095.0 * 360.0), 0.0f, 1.0f, 0.0f);
            guMtxCatF(mtx, rot, mtx);
        }
        guRotateF(rot, 90.0 - gCurrentActor->floorSlopePitch / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
        guMtxCatF(mtx, rot, mtx);
        if (gCurrentActor->floorSlopePitch < 1000) {
            guRotateF(rot, gCurrentActor->floorSlopeYaw / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
            guMtxCatF(mtx, rot, mtx);
        }
    }
    guTranslateF(rot, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    guMtxCatF(mtx, rot, gCurrentActor->modelMtx);
}

extern s32 D_8071FE64;
extern s32 D_8071FE88;
extern s32 D_8071FEAC;

void tagBarrelDespawnEffects(void) {
    s32 pad;
    f32 scale;
    s32 kind;
    s32 i;

    scale = (f64) gCurrentActor->sub4->scaleY / 0.15;
    rumbleRequest(0, 0xB4, 0xA);
    effectSetDepth(0);
    effectSetDuration(1);
    effectCreateAtPosition(&D_8071FE08, (f64) scale * 0.75, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x23, 0xFF, 0x7F, 1);

    for (i = 0; i != 7; i++) {
        kind = ((s32) ((u32)randomLcgNext() / 10000U)) % 3;
        effectSetDepth(1);
        effectSetDuration(0xA);
        effectSetCallback(effectTumbleBounceUpdate);
        effectSetMode(2);
        effectSetSpeed(2);
        switch (kind) {
        case 0:
            effectCreateAtPosition(&D_8071FE64, (f64) scale * 0.25, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            break;
        case 1:
            effectCreateAtPosition(&D_8071FE88, (f64) scale * 0.25, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            break;
        case 2:
            effectCreateAtPosition(&D_8071FEAC, (f64) scale * 0.25, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            break;
        }
    }
}

void tagBarrelSpawnSmokeAndPuffs(f32 x, f32 y, f32 z, f32 scale, u8 spray, u8 playSound) {
    f64 scaleD;
    f32 puffScale;
    f32 dy;
    f32 dx;
    f32 dz;
    s32 i;

    if (playSound != 0) {
        sfxPlayAtPositionPooled(x, y, z, 0xF6, 0xFF, 0x7F, 0x19, 0x1E, 0.3f, 0);
    }
    effectSetDepth(1);
    effectSetCallback(effectPuffExpandFadeUpdate);
    effectCreateAtPosition(&D_80720120, 0.0f, x, y + 5.0f, z);
    scaleD = (f64) scale;
    puffScale = scaleD * 1.5;
    for (i = 0; i < 5; i++) {
        dx = (f32) (((s32) (randomNonNegative() >> 15) % 20) - 10) * scale;
        dy = (f32) (((s32) (randomNonNegative() >> 15) % 20) - 10) * scale;
        dz = (f32) (((s32) (randomNonNegative() >> 15) % 20) - 10) * scale;
        effectSetAngle(4);
        effectSetDepth(1);
        effectSetDuration(1);
        effectSetCallback(effectSpinBillboardingUpdate);
        effectCreateAtPosition(&D_80720340, puffScale, x + dx, y + dy, z + dz);
    }
    effectSetAngle(4);
    effectSetDepth(1);
    effectSetDuration(1);
    effectSetCallback(effectSpinBillboardingUpdate);
    effectCreateAtPosition(&D_80720340, puffScale, x, y, z);
    if (spray != 0) {
        for (i = 0; i != 12; i++) {
            effectSetDepth(1);
            effectSetDuration(2);
            effectSetSpeed(i + 0x0B020000);
            effectSetCallback(effectRadialSprayUpdate);
            effectSetMode(1);
            effectCreateAtPosition(&D_8072038C, (f32)(scaleD * 0.5), x, y, z);
        }
    }
}

void tagBarrelSpawnActorSmokePuffs(u8 spray, u8 playSound) {
    tagBarrelSpawnSmokeAndPuffs(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, (f32) ((f64) gCurrentActor->sub4->scaleY / 0.15), spray, playSound);
}

void tagBarrelSpawnNodeSmokePuffs(s32 unused, u8 node, f32 scale) {
    f32 x;
    f32 y;
    f32 z;

    actorGetNodePos(gCurrentActor, node, &x, &y, &z);
    tagBarrelSpawnSmokeAndPuffs(x, y, z, scale, 0, 1);
}

typedef struct TransformBarrelState {
    s16 timer;
    s16 unk2;
    Actor *player;
    s16 wobbleFrame;
    s16 unkA;
    f32 baseScale;
    f32 scale;
    f32 baseY;
    s16 spinSpeed;
    s16 setsFlag;
    u8 refillCount;
} TransformBarrelState;

void tagBarrelResetMovement(void) {
    TransformBarrelState *state = gCurrentActor->customState;

    gCurrentActor->sub4->scaleX = state->baseScale;
    gCurrentActor->sub4->scaleY = state->baseScale;
    gCurrentActor->sub4->scaleZ = state->baseScale;
    gCurrentActor->y = state->baseY;
    state->wobbleFrame = 0;
    state->spinSpeed = 0;
    state->scale = state->baseScale;
    gCurrentActor->state = 0;
    gCurrentActor->unk144 = 2;
    gCurrentActor->flags &= ~0x200000;
}

void tagBarrelTriggerRecoil(void) {
    tagBarrelResetMovement();
    gCurrentActor->state = 0x14;
    gCurrentActor->unk144 = 1;
    gCurrentActor->flags &= ~0x8000;
    gCurrentActor->alpha = 0;
    slotQueueCancel(5, 0);
}

void tagBarrelCheckRecoil(void) {
    s16 i;

    for (i = 0; i < gActorGlobalState.unk254; i++) {
        if (gActorGlobalState.unk258[i] == 1 && *gActorGlobalState.unk278[i] == 0xFF) {
            tagBarrelTriggerRecoil();
        }
    }
}

void tagBarrelUpdateRecoilState0(void) {
    transformBarrelUpdate();
    if (gCurrentActor->state == 0) {
        tagBarrelCheckRecoil();
    }
}

void transformBarrelInitScale(void) {
    s16 i;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->sub4->scaleX = (f32)(gCurrentActor->sub4->scaleX * 1.5);
        gCurrentActor->sub4->scaleY = (f32)(gCurrentActor->sub4->scaleY * 1.5);
        gCurrentActor->sub4->scaleZ = (f32)(gCurrentActor->sub4->scaleZ * 1.5);
        gCurrentActor->drawDistance = 0x7D0;
    }
    if (gCurrentActor->state == 0) {
        for (i = 0; i < gActorGlobalState.unk254; i++) {
            if (gActorGlobalState.unk258[i] == 1) {
                effectSetDepth(0);
                effectSetDuration(1);
                effectCreateAtPosition(&D_8071FE08, 0.5f, gCurrentActor->x, gCurrentActor->y + 7.0f, gCurrentActor->z);
                actorDespawn(gCurrentActor);
            }
        }
    }
    transformBarrelUpdate();
}

void tagBarrelUpdateAndCheckRecoil(void) {
    transformBarrelUpdate();
    tagBarrelCheckRecoil();
}

void transformBarrelWrapperUpdateA(void) {
    transformBarrelUpdate();
}

void transformBarrelWrapperUpdateB(void) {
    transformBarrelUpdate();
}

void transformBarrelWrapperUpdateC(void) {
    transformBarrelUpdate();
}

void transformBarrelUpdateNear(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->drawDistance = 0x320;
    }
    transformBarrelUpdate();
}

void transformBarrelWrapperUpdateD(void) {
    transformBarrelUpdate();
}

typedef struct TransformBarrelEntry {
    u8 map;
    u8 listId;
    u8 count;
} TransformBarrelEntry;



extern TransformBarrelEntry D_8074E7BC[];
extern u8 gPlayerInventoryTable[][0x5E];

extern s32 gGlobalPauseFlags;
extern s32 gGlobalCutsceneFlags;


void transformBarrelUpdate(void) {
    TransformBarrelState *state;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    PlayerState *playerState;
    s32 ret;
    s16 i;
    s16 entry;
    s16 entryCount = 8; // FAKE: value-named constant local steers the loop bound (literal 8: mismatch)
    u8 found;
    Actor *player;
    PlayerState *activePlayerState;
    s32 hide;
    s32 channel;
    PlayerState *riderState;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        entry = 0;
        found = 0;
        ret = actorListFindIdByActor(gCurrentActor);
        if (gPrimaryPlayerActor) {} // FAKE: raises &gPrimaryPlayerActor candidate priority
        state->refillCount = 0;
        do {
            if (gCurrentMap == D_8074E7BC[entry].map && ret == D_8074E7BC[entry].listId) {
                found = 1;
                state->refillCount = D_8074E7BC[entry].count;
            } else {
                entry++;
            }
        } while (!found && entry < entryCount);

        if (*(s32 *)gCurrentActor->spawnData == 1) {
            if (tagBarrelIsSpecial(gCurrentActor) == 0) {
                gCurrentActor->state = 0x14;
                gCurrentActor->unk144 = 1;
                gCurrentActor->flags &= ~0x8000;
                gCurrentActor->alpha = 0;
            }
        }
        gCurrentActor->floorY = gCurrentActor->y;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        gCurrentActor->flags |= 2;
        state->scale = gCurrentActor->sub4->scaleY;
        state->baseScale = gCurrentActor->sub4->scaleY;
        state->wobbleFrame = 0;
        state->spinSpeed = 0;
        state->baseY = gCurrentActor->y;
        if (gCurrentActor->actorType == 0x12 || gCurrentActor->actorType == 0x81) {
            state->setsFlag = ((s32 *)gCurrentActor->spawnData)[1];
        }
    }
    actorUpdatePrevContactFlags(gCurrentActor);

    if (gCurrentActor->state == 0 && gActorGlobalState.bossFightPhase == 4) {
        playerState = gPrimaryPlayerActor->customState;

        sfxStopChannel(0x6B, 1);
        if (gCurrentActor->actorType != 0x60) {
            sfxAllocateChannel(0xF, 1.0f);
        }
        if (state->setsFlag != 0) {
            ret = -1;

            if (gCurrentActor->actorType == 0x12) {
                ret = 0xF;
            } else if (gCurrentActor->actorType == 0x81) {
                ret = 0x10;
            }
            if (ret >= 0) {
                flagSet(ret, 1, 1);
            }
            playerState->unk1FD = 1;
        }
        if (gGlobalCutsceneFlags & 2) {
            state->timer = 0x1E;
        } else {
            switch (gCurrentActor->actorType) {
            case 0x60:
                state->timer = 0x32;
                break;
            case 0x38:
                state->timer = 0x1E;
                break;
            default:
                state->timer = 0x64;
                break;
            }
        }
        if (state->refillCount != 0) {
            s32 queued = slotQueueGetValue(5, playerState->playerIndex);
            s32 step = slotQueueGetCountStep(5) * state->refillCount;

            if (queued < step) {
                slotQueueAddValue(5, playerState->playerIndex, (s16)(step - queued));
            }
        }
        gCurrentActor->state = 1;
        gCurrentActor->unk144 = 1;
        state->player = gActorGlobalState.targetActor;
        gCurrentActor->flags |= 0x200000;
        if (!(gGlobalOverlayFlags & 0x2000)) {
            if (state->player->collisionFlags & 1) {
                riderState = state->player->customState;

                if (riderState->actor != NULL) {
                    actorDespawn(riderState->actor);
                    riderState->actor = NULL;
                    camSetFollowMode(riderState->camActor);
                }
            }
        }
        state->player->unk144 = 1;
    }

    if (gCurrentActor->state < 0x14) {
        s32 itemCount = 0;
        s32 allowed = 0;

        if (gPlayerCharacterId < 5) {
            itemCount = gPlayerInventoryTable[gPlayerCharacterId][0];
        }
        player = gPrimaryPlayerActor;
        if (player->actorType == 5 && gCurrentActor->actorType == 0x28 && itemCount > 0) {
            allowed = 1;
        }
        if (player->actorType == 6 && gCurrentActor->actorType == 0x19 && itemCount > 0) {
            allowed = 1;
        }
        if (player->actorType == 6 && gCurrentActor->actorType == 0x60 && itemCount > 0) {
            allowed = 1;
        }
        if (player->actorType == 4 && gCurrentActor->actorType == 0x38 && itemCount >= 3) {
            allowed = 1;
        }
        if (player->actorType == 2 && gCurrentActor->actorType == 0x39 && itemCount >= 2) {
            allowed = 1;
        }
        if (player->actorType == 4 && gCurrentActor->actorType == 0x81) {
            allowed = 1;
        }
        if (gCurrentActor->actorType == 0x12) {
            allowed = 1;
        }
        if (gCurrentActor->actorType == 0x84 && player->actorType == 9 && (activePlayerState = player->customState)->actor == NULL) {
            allowed = 1;
        }
        if (allowed != 0) {
            gCurrentActor->flags |= 0x8000;
            *(u16 *)&gCurrentActor->interactionType = 1; // FAKE: unsigned u16 store keeps constant 1 out of the hoisted-constant web
        } else {
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->alpha = 0x78;
            gCurrentActor->interactionType = 2;
        }
    } else {
        gCurrentActor->interactionType = 1;
    }
    if (gActivePlayerState->unkCA != 0) {
        gCurrentActor->interactionType = 2;
    }

    switch (gCurrentActor->state) {
    case 0:
        if (gCurrentActor->actorType != 0x12 && gCurrentActor->actorType != 0x81 && gCurrentActor->actorType != 0x84) {
            animSetSpeed(gCurrentActor, 0, 0.5f);
            animSetLoopMode(gCurrentActor, 0, 0);
            animSetEndFrame(gCurrentActor, 0, 9);
            animSetLoopLimit(gCurrentActor, 0, 0x32);
        }
        break;

    case 1:
        if (state->timer < 0x1E) {
            switch (gCurrentActor->actorType) {
            case 0x19:
            case 0x60:
                state->scale += (gCurrentActor->actorType == 0x19) ? 0.004 : 0.008;
                gCurrentActor->y += 0.6;
                if ((gCurrentActor->y - state->baseY) > 25.0f) {
                    gCurrentActor->y = state->baseY + 25.0f;
                }
                break;
            case 0x28:
                state->scale -= 0.001;
                gCurrentActor->y += 0.6;
                if ((gCurrentActor->y - state->baseY) > 25.0f) {
                    gCurrentActor->y = state->baseY + 25.0f;
                }
                break;
            case 0x12:
            case 0x81:
            case 0x84:
                state->scale += 0.006;
                break;
            }
        }
        gCurrentActor->sub4->scaleX = sinApprox(state->wobbleFrame * 0.11) * 0.1 + state->scale;
        gCurrentActor->sub4->scaleY = sinApprox(state->wobbleFrame * 0.2352) * 0.1 + state->scale;
        gCurrentActor->sub4->scaleZ = sinApprox(state->wobbleFrame * 0.176) * 0.1 + state->scale;
        state->wobbleFrame++;
        if (gCurrentActor->actorType != 0x12 && gCurrentActor->actorType != 0x81 && gCurrentActor->actorType != 0x84) {
            gCurrentActor->yaw += state->spinSpeed;
            state->spinSpeed += 10;
            if (state->spinSpeed >= 0x65) {
                state->spinSpeed = 0x64;
            }
        }
        actorAppendMoveTarget3D(gCurrentActor, state->player, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 2, 1);
        state->timer--;
        if (state->timer == 0) {
            state->timer = 0xC;
            gCurrentActor->state = 2;
            if (gCurrentActor->actorType != 0x12 && gCurrentActor->actorType != 0x81 && gCurrentMap != 0x52 && !(gGlobalOverlayFlags & 1)) {
                slotQueueUpdate(5, 1, 0);
            }
        }
        break;

    case 2:
        state->timer--;
        if (state->timer == 0) {
            gCurrentActor->state = 3;
        }
        break;

    case 3: {
        s16 sound = 0;
        if (gPrimaryPlayerActor->actorType == 9) {}  // FAKE: dead compare steers uopt constant-web (0x81/0x84) colouring order
        switch (gCurrentActor->actorType) {
        case 0x28:
            sound = 0x10;
            sfxPlayOnFreeSlot(0x1A5, 0x58EF, 63.0f, 1.0f, 0, 0);
            break;
        case 0x19:
            sound = 0x11;
            sfxPlayOnFreeSlot(0xC7, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        case 0x12:
            sound = 0x24;
            sfxPlayOnFreeSlot(0x2EC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            gGlobalPauseFlags |= 0x400;
            break;
        case 0x39:
            sound = 0x47;
            break;
        case 0x38:
            sound = 0x49;
            break;
        case 0x81:
            sound = 0x7C;
            gGlobalPauseFlags |= 0x400;
            break;
        }
        if (sound != 0 && !(gGlobalCutsceneFlags & 2) && gCurrentMap != 3 && gCurrentMap != 0x11 && gCurrentMap != 0x52 && gCurrentMap != 0xD1) {
            if (gPlayerCharacterId) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            sfxAllocateChannel(sound, 1.0f);
        }
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x9C, 0xFF, 0x7F, 0);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x9D, 0xFF, 0x7F, 0);
        if (gCurrentActor->actorType != 0x12 && gCurrentActor->actorType != 0x81 && gCurrentActor->actorType != 0x84) {
            animResetEndFrame(gCurrentActor, 0);
            animSetFrameAndSubframe(gCurrentActor, 0, 0xA, 0.0f);
        }
        actorGetNodePos(gCurrentActor, 1, &nodeX, &nodeY, &nodeZ);
        actorAppendCallback(state->player, gCurrentActor, 0x40, 1, 0, NULL);
        {
            s16 angle;
            if (gCurrentActor->actorType == 0x12) {
                angle = gPlayerSlots->unk2C8 & 0xFFF;
            } else {
                angle = state->player->yaw;
            }
            actorAppendCallbackPayloadAAB8(gCurrentActor, state->player, angle, -40.0f, 0);
        }
        actorSetInteractionTimer(state->player);
        tagBarrelDespawnEffects();
        gCurrentActor->state = 4;
        if (gCurrentActor->actorType == 0x39) {
            sfxPlayOnFreeSlot(0x231, 0x58EF, 63.0f, 1.0f, 0, 0);
        }
        if (gCurrentActor->actorType == 0x38) {
            sfxPlayOnFreeSlot(0xD4, 0x58EF, 63.0f, 1.0f, 0, 0);
        }
        break;
    }

    case 4: {
        playerState = state->player->customState;
        hide = 0;

        switch (gCurrentActor->actorType) {
        case 0x19:
        case 0x28:
        case 0x60:
            if (gPlayerSlots[playerState->playerIndex].unk2C0 != 1) {
                hide = 1;
            }
            break;
        case 0x39:
            if (playerState->stateFlags & 0x10) {
                hide = 1;
            }
            break;
        case 0x38:
            if (playerState->stateFlags & 0x20) {
                hide = 1;
            }
            break;
        case 0x12:
            if (gPrimaryPlayerActor->actorType == 8) {
                hide = 1;
            }
            break;
        case 0x81:
            if (gPrimaryPlayerActor->actorType == 9) {
                hide = 1;
            }
            break;
        case 0x84:
            if (playerState->actor != NULL) {
                hide = 1;
            }
            break;
        }

        if (hide != 0) {
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->alpha = 0;
        } else {
            gGlobalPauseFlags &= ~0x400;
            if (gCurrentActor->actorType != 0x60) {
                channel = 0;
                switch (gCurrentActor->actorType) {
                case 0x38:
                    channel = 0x49;
                    break;
                case 0x81:
                    channel = 0x7C;
                    break;
                case 0x39:
                    channel = 0x47;
                    break;
                case 0x12:
                    channel = 0x24;
                    break;
                case 0x19:
                    channel = 0x11;
                    break;
                case 0x28:
                    channel = 0x10;
                    break;
                }
                sfxStopChannel(channel, 0);
                sfxAllocateChannel(0xF, 1.0f);
            }
            gCurrentActor->state = 5;
            if ((gGlobalCutsceneFlags & 2) && gCurrentActor->actorType == 0x19) {
                state->timer = 1;
            } else {
                state->timer = 0x5A;
            }
        }
        break;
    }

    case 5:
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->alpha = 0;
        state->timer--;
        if (state->timer == 0) {
            if (gCurrentMap == 0xCE) {
                tagBarrelTriggerRecoil();
            } else {
                tagBarrelResetMovement();
            }
            if (gCurrentActor->actorType != 0x12 && gCurrentActor->actorType != 0x81) {
                slotQueueCancel(5, 0);
            }
            if (gCurrentActor->actorType == 0x60) {
                actorDespawn(gCurrentActor);
            }
        }
        break;

    case 20:
        for (i = 0; i < gActorGlobalState.unk254; i++) {
            if (gActorGlobalState.unk258[i] == 1 && *gActorGlobalState.unk278[i] != 0xFF) {
                gCurrentActor->unk144 = 2;
                gCurrentActor->state = 0x15;
            }
        }
        break;

    case 21:
        gCurrentActor->alpha += 10;
        if (gCurrentActor->alpha >= 0xF1) {
            gCurrentActor->flags |= 0x8000;
            gCurrentActor->state = 0;
        }
        break;
    }

    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, (s32)(gCurrentActor->sub4->scaleX * 100.0f), (s32)(gCurrentActor->sub4->scaleZ * 100.0f), 1, 0x64, (u32)(gCurrentActor->alpha * 0.5), 0, 1.0f);
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void tagBarrelDespawnOnKongDeselect(void) {
    s16 i;

    for (i = 0; i < gActorGlobalState.unk254; i++) {
        if (gActorGlobalState.unk258[i] == 1 && *gActorGlobalState.unk278[i] == 1) {
            tagBarrelDespawnEffects();
            actorDespawn(gCurrentActor);
        }
    }
}

typedef struct ActorFB6CSpawnData {
    s32 frequency;
    s32 amplitude;
    s32 mode;
    s32 hidden;
} ActorFB6CSpawnData;


typedef struct ActorFB6CState {
    Actor *rider;
    u32 phase;
    f32 baseY;
    f32 pitch;
    f32 amplitude;
    f32 frequency;
    s16 baseYaw;
    u8 launchDelay;
    u8 animDelay;
    u8 mode;
} ActorFB6CState;

extern Actor *gActivePlayerActor;
extern s32 gGlobalCutsceneFlags;
typedef struct TagBarrelInputPad {
    u8 pad0[0x2C];
    u16 unk2C;
    s8 unk2E;
    s8 unk2F;
    u8 unk30;
} TagBarrelInputPad;
extern TagBarrelInputPad gPlayerPadState;

f32 mathCosF(s16);
f32 mathSinF(s16);

void tagBarrelParticleUpdate(void) {
    f64 pad;
    f32 dirX;
    f32 dirZ;
    Actor *cam;
    s32 pad2;
    s16 viewYaw;
    ActorFB6CState *sub;
    s32 param;
    f32 camY;
    s16 i;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->drawDistance = 0x320;
        gCurrentActor->cullMarginX = 0x14;
        gCurrentActor->cullMarginY = 0x14;
        sub->pitch = 90.0f;
        sub->baseY = gCurrentActor->y;
        sub->frequency = (f64)((ActorFB6CSpawnData *)gCurrentActor->spawnData)->frequency / 200.0;
        sub->amplitude = ((ActorFB6CSpawnData *)gCurrentActor->spawnData)->amplitude;
        sub->phase = ((f64)sub->frequency != 0.0) ? (4.71238899230957031 / (f64)sub->frequency) : (f64)0;
        sub->mode = ((ActorFB6CSpawnData *)gCurrentActor->spawnData)->mode;
        sub->baseYaw = gCurrentActor->yaw;
        gCurrentActor->floorY = 99999.0f;
        collisionCheckGroundAtPoint(gCurrentActor->x, gCurrentActor->z, &gCurrentActor->floorY);
        if (sub->mode == 3) {
            gCurrentActor->interactionType = 2;
        } else {
            gCurrentActor->interactionType = 1;
        }
        if (((ActorFB6CSpawnData *)gCurrentActor->spawnData)->hidden == 1) {
            gCurrentActor->state = 0x14;
            gCurrentActor->unk144 = 1;
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->alpha = 0;
        }
    }
    if (gActorGlobalState.bossFightPhase == 4) {
        sub->rider = gActorGlobalState.targetActor;
        gCurrentActor->state = 1;
        gCurrentActor->unk144 = 1;
        gCurrentActor->flags |= 0x400;
        sub->animDelay = 2;
        if (sub->mode == 3) {
            sub->launchDelay = 1;
        } else {
            sub->launchDelay = 2;
        }
    }
    switch (gCurrentActor->state) {
    case 0:
        tagBarrelDespawnOnKongDeselect();
        break;
    case 1:
        gCurrentActor->flags |= 0x8000;
        switch (sub->mode) {
        case 0:
        case 4:
            if (sub->mode == 0) {
                gCurrentActor->y = sinApprox((f32)sub->phase * sub->frequency) * sub->amplitude + (sub->baseY + sub->amplitude);
            } else {
                gCurrentActor->y = sinApprox((f32)sub->phase * sub->frequency) * sub->amplitude + sub->baseY;
            }
            actorAppendMoveTarget3D(gCurrentActor, sub->rider, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 2, 1);
            viewYaw = gCurrentActor->yaw;
            sub->phase++;
            break;
        case 2:
            gCurrentActor->yaw = (gCurrentActor->yaw + (s32)(sub->frequency * 200.0f)) & 0xFFF;
            viewYaw = (gCurrentActor->yaw + (s32)(sub->frequency * 200.0f)) & 0xFFF;
            break;
        case 1:
            gCurrentActor->yaw = ((s16)(sinApprox((f32)sub->phase * sub->frequency) * ((sub->amplitude * 4096.0f) / 360.0f)) + sub->baseYaw) & 0xFFF;
            sub->phase++;
            viewYaw = ((s16)(sinApprox((f32)sub->phase * sub->frequency) * ((sub->amplitude * 4096.0f) / 360.0f)) + sub->baseYaw) & 0xFFF;
            break;
        case 3:
            viewYaw = gCurrentActor->yaw;
            break;
        }
        dirX = mathSinF(viewYaw) * 50.0f;
        dirZ = mathCosF(viewYaw) * 50.0f;
        if (sub->animDelay == 1) {
            controllerAnimLoadStateAsset(gCurrentActor, 0x75);
        }
        if (sub->animDelay) {
            sub->animDelay--;
        }
        if (sub->launchDelay) {
            sub->launchDelay--;
        }
        if (((gPlayerPadState.unk2C & 0xE000) || sub->mode == 3) && sub->launchDelay == 0) {
            PlayerState *riderState;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x18, 0xFF, 0x7F, 1);
            riderState = sub->rider->customState;
            controllerAnimFreeStateAsset(gCurrentActor);
            if (!(gGlobalCutsceneFlags & 2)) {
                if (sub->mode == 3) {
                    param = 0x64;
                } else {
                    param = 0x32;
                }
                camSetTargetScaled(riderState->camActor, sub->rider, 4, 0x800, param, 0, 0, 0x1E, 0x14, 0x50, 0.3f);
            }
            gActivePlayerActor->yaw = gCurrentActor->yaw;
            gActivePlayerActor->moveYaw = gCurrentActor->yaw;
            actorAppendCallback(sub->rider, gCurrentActor, 0x40, 1, 0, 0);
            if (gGlobalCutsceneFlags & 2) {
                param = 0x1F4;
            } else {
                param = 0x2BC;
            }
            actorAppendCallbackPayloadAAB8(gCurrentActor, sub->rider, gCurrentActor->yaw, 0.0f, param);
            actorQueueDelayedCallback(gCurrentActor, gCurrentActor, 0x800, 2, 0, 0, 0xA);
            effectSetMode(2);
            effectCreateAtActorBone(&D_8071FBC8, 1.6f, gCurrentActor, 1, 2);
            gCurrentActor->flags &= ~0x400;
            gCurrentActor->state = 2;
            gCurrentActor->unk155 = 0x1E;
        } else {
            cam = ((PlayerState *)sub->rider->customState)->camActor;
            switch (sub->mode) {
            case 0:
                camY = sinApprox((f32)sub->phase * sub->frequency) * sub->amplitude + (sub->baseY + sub->amplitude);
                break;
            case 4:
                camY = sinApprox((f32)sub->phase * sub->frequency) * sub->amplitude + sub->baseY;
                break;
            default:
                camY = gCurrentActor->y;
                break;
            }
            if (gGlobalCutsceneFlags & 2) {
                param = 0;
            } else {
                param = 1;
            }
            camSetFixedView(
                cam,
                (f64)gCurrentActor->x - (f64)dirX / 5.0,
                camY,
                (f64)gCurrentActor->z - (f64)dirZ / 5.0,
                gCurrentActor->x + dirX,
                camY,
                gCurrentActor->z + dirZ,
                param
            );
            if (camIsCutsceneActive() == 0) {
                renderCallbacksRegister(func_806FF01C, gPrimaryPlayerActor, 3);
            }
        }
        break;
    case 2:
        tagBarrelDespawnOnKongDeselect();
        gCurrentActor->unk155--;
        if (gCurrentActor->unk155 == 0) {
            gCurrentActor->y = sub->baseY;
            sub->phase = ((f64)sub->frequency != 0.0) ? (4.71238899230957031 / (f64)sub->frequency) : (f64)0;
            gCurrentActor->yaw = sub->baseYaw;
            gCurrentActor->state = 0;
        }
        break;
    case 20:
        for (i = 0; i < gActorGlobalState.unk254; i++) {
            if (gActorGlobalState.unk258[i] == 1 && *gActorGlobalState.unk278[i] == 0) {
                gCurrentActor->unk144 = 2;
                gCurrentActor->state = 0x15;
            }
        }
        break;
    case 21:
        gCurrentActor->alpha += 10;
        if (gCurrentActor->alpha >= 0xF1) {
            gCurrentActor->flags |= 0x8000;
            gCurrentActor->state = 0;
        }
        break;
    }
    if (gCurrentMap == 0xCB) {
        gCurrentActor->flags |= 0x400;
    }
    guRotateF(gCurrentActor->modelMtx, sub->pitch, 1.0f, 0, 0.0f);
    actorUpdateModelMatrix(gCurrentActor, 1);
}




void tagBarrelUpdateInteractable(void) {
    if (1 != gPlayerSlots->unk2C0 || (gActivePlayerState->stateFlags2 & 0x40) || gPlayerCharacterId >= 5) {
        gCurrentActor->interactionType = 4;
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->alpha = 0x7F;
    } else if (1 == gPlayerSlots->unk2C0 && !(gActivePlayerState->stateFlags & 0x40) && gPlayerCharacterId < 5) {
        gCurrentActor->flags |= 0x8000;
        gCurrentActor->interactionType = 1;
    }
    if (gActivePlayerState->unkCA != 0) {
        gCurrentActor->interactionType = 4;
    }
}

void tagBarrelCheckPlayerCollision(void) {
    if (gPlayerCharacterId >= 5) {
        gCurrentActor->interactionType = 4;
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->alpha = 0x7F;
    } else {
        gCurrentActor->flags |= 0x8000;
        gCurrentActor->interactionType = 1;
    }
    if (gActivePlayerState->unkCA != 0) {
        gCurrentActor->interactionType = 4;
    }
}

u8 tagBarrelGetKongType(void) {
    u8 ret = 0x64;

    switch (gCurrentMap) {
    case 0x1A:
        if (actorListFindIdByActor(gCurrentActor) == 0xD || actorListFindIdByActor(gCurrentActor) == 0xF) {
            ret = 2;
        }
        break;
    case 0x3B:
        if (actorListFindIdByActor(gCurrentActor) == 3) {
            ret = 2;
        }
        break;
    case 0x30:
        if (actorListFindIdByActor(gCurrentActor) == 0x12) {
            ret = 2;
        }
        break;
    case 0xAD:
    case 0xC3:
        ret = 2;
        break;
    }
    return ret;
}

typedef struct TagBarrelActorState {
    /* 0x00 */ f32 baseY;
    /* 0x04 */ s16 bobPhase;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 flagIndex;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 timer;
    /* 0x0E */ u8 unkE;
} TagBarrelActorState;

typedef struct TagBarrelSpawnParams {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0xC];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} TagBarrelSpawnParams;

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;


extern Vec3f D_8074E7D4;
extern u8 gScreenRenderFlags;
extern u8 D_8071FC58[];


extern s16 D_80750390;

void tagBarrelActorUpdate(void) {
    s16 kong;
    s16 pad0;
    f32 coord[3];
    s32 i;
    Vec3f offset;
    s16 *ptr;
    s16 spawnFlag;
    f32 dist;
    u8 hidden;
    TagBarrelActorState *sub;
    f32 scaleFactor;
    u32 val;
    f32 sizeScale;
    s16 angle;
    f32 yOffset;

    sub = gCurrentActor->customState;
    if (gCurrentMap == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    offset = D_8074E7D4;
    hidden = 0;
    if (!(gCurrentActor->flags & 0x10)) {
        scaleFactor = gCurrentActor->sub4->scaleX / 0.15;
        gCurrentActor->floorY = gCurrentActor->y;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        gCurrentActor->attachMode = 0;
        gCurrentActor->flags |= 2;
        sub->baseY = gCurrentActor->y;
        sub->bobPhase = 0;
        sub->unk6 = ((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk0;
        sub->flagIndex = ((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk8;
        sub->unkE = 0;
        if (gCurrentActor->actorType == 0x1C) {
            if (flagGet(func_8073195C(sub->flagIndex), 0)) {
                actorDespawn(gCurrentActor);
            }
        }
        gCurrentActor->interactionType = 1;
        if (((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk1C == 1.0 || ((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk1C == 2.0) {
            gCurrentActor->state = 0xA;
            sub->timer = 0x14;
            gCurrentActor->sub4->scaleX = 0.02f;
            gCurrentActor->sub4->scaleY = 0.02f;
            gCurrentActor->sub4->scaleZ = 0.02f;
            if (((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk1C == 2.0) {
                sub->unkC = 1;
            } else {
                sub->unkC = 0;
            }
        } else if (((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk4 == 1) {
            gCurrentActor->state = 0x14;
            gCurrentActor->unk144 = 1;
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->alpha = 0;
        } else {
            gCurrentActor->state = 0;
        }
        scaleFactor -= 1.0;
        if (scaleFactor < 0.0) {
            scaleFactor = 0.0f;
        }
        val = (u32)(80.0f * scaleFactor + 20.0f);
        gCurrentActor->cullMarginX = val;
        gCurrentActor->cullMarginY = val;
    }
    for (i = 0; i < gActorGlobalState.unk254; i++) {
        ptr = gActorGlobalState.unk278[i];
        switch (*ptr) {
            case 2:
                sub->unkE = 0x8C;
                break;
            default:
                break;
        }
    }
    if (sub->unkE != 0) {
        sub->unkE--;
        sub->baseY += 1.0;
        actorListSetPosByActor(gCurrentActor, gCurrentActor->x, sub->baseY, gCurrentActor->z);
    }
    if (gCurrentActor->state != 0x14 && gCurrentActor->state != 0x15) {
        tagBarrelCheckPlayerCollision();
    }
    if (gCurrentMap == 0xAA) {
        if (gCurrentActor->state != 0xA && gCurrentActor->state != 0xB && gCurrentActor->state != 0xC && gCurrentActor->state != 0x1E) {
            if (gActivePlayerState->stateFlags & 0x40) {
                gCurrentActor->unk144 = 2;
                gCurrentActor->flags |= 0x8000;
            } else {
                hidden = 1;
                gCurrentActor->unk144 = 1;
                gCurrentActor->flags &= ~0x8000;
                gCurrentActor->alpha = 0;
            }
        }
    }
    if ((gCurrentActor->flags & 0x100) && (gCurrentActor->state == 0 || gCurrentActor->state == 1 || (gCurrentActor->state >= 0xA && gCurrentActor->state < 0xD)) && hidden == 0) {
        dist = (gPlayerSlots->camZ - gCurrentActor->z) * (gPlayerSlots->camZ - gCurrentActor->z) +
               ((gPlayerSlots->camX - gCurrentActor->x) * (gPlayerSlots->camX - gCurrentActor->x) +
                (gPlayerSlots->camY - gCurrentActor->y) * (gPlayerSlots->camY - gCurrentActor->y));
        if (dist < 40000.0f) {
            sizeScale = gCurrentActor->sub4->scaleX / 0.15;
            coord[2] = (randomNonNegative() >> 15) % (s32)(30.0f * sizeScale) - 15.0 * sizeScale + gCurrentActor->x;
            coord[1] = (randomNonNegative() >> 15) % (s32)(30.0f * sizeScale) - 15.0 * sizeScale + gCurrentActor->y;
            coord[0] = (randomNonNegative() >> 15) % (s32)(30.0f * sizeScale) - 15.0 * sizeScale + gCurrentActor->z;
            effectSetDepth(1);
            effectSetFlags(4);
            if (gCurrentActor->state == 0) {
                effectSetCallback(effectZSpinMatrixUpdate);
                effectCreateAtPosition(D_8071FC58, 0.5f, coord[2], coord[1], coord[0]);
            } else {
                effectSetSpeed((s32)(gCurrentActor->sub4->scaleX * 100.0f) + (sub->unk8 << 16));
                effectSetCallback(effectOrbitXZUpdate);
                effectCreateAtPosition(D_8071FC58, 0.5f, gCurrentActor->x, coord[1], gCurrentActor->z);
            }
        }
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    switch (gCurrentActor->state) {
    case 0:
        if (gActorGlobalState.bossFightPhase == 4) {
            gCurrentActor->state = 1;
            gCurrentActor->unk144 = 1;
            sub->unk8 = 0;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x261, 0xFF, 0x64, 1);
            camStartPath(NULL, 0x1F, 5);
            if (actorFindByType(0x25) != NULL) {
                actorSetCustomFloat(gCurrentActor, 6, 1.0f);
            } else {
                actorSetCustomFloat(gCurrentActor, 6, 0.0f);
            }
        } else {
            for (i = 0; i < gActorGlobalState.unk254; i++) {
                if (gActorGlobalState.unk258[i] == 1 && *gActorGlobalState.unk278[i] == 1) {
                    gCurrentActor->state = 0x14;
                    gCurrentActor->unk144 = 1;
                    gCurrentActor->flags &= ~0x8000;
                    gCurrentActor->alpha = 0;
                }
            }
        }
        break;
    case 1:
        sub->unk8 += 0x1E;
        if (sub->unk8 >= 0x191) {
            sub->unk8 = 0x190;
        }
        gCurrentActor->yaw += sub->unk8;
        if (sub->unk8 >= 0xC9) {
            gCurrentActor->sub4->scaleX -= 0.005;
            gCurrentActor->sub4->scaleY -= 0.005;
            gCurrentActor->sub4->scaleZ -= 0.005;
            if (gCurrentActor->sub4->scaleX < 0.02) {
                gCurrentActor->state = 2;
            }
        }
        break;
    case 2:
        actorSetCustomFloat(gCurrentActor, 7, 1.0f);
        if (!(gScreenRenderFlags & 1) || gCurrentActor->actorType != 0x6B) {
            mapSaveSlotAndTransition(sub->unk6, 0, 0, 3);
        }
        actorDespawn(gCurrentActor);
        break;
    case 10:
        if (sub->timer != 0) {
            sub->timer -= 1;
        }
        if (sub->timer == 5) {
            gCurrentActor->unk144 = 1;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x262, 0xFF, 0x64, 1);
        }
        if (sub->timer == 0) {
            gCurrentActor->sub4->scaleX += 0.005;
            gCurrentActor->sub4->scaleY += 0.005;
            gCurrentActor->sub4->scaleZ += 0.005;
            if (gCurrentActor->sub4->scaleX >= 0.15) {
                gCurrentActor->state = 0xB;
            }
            scaleFactor = (0.15 - gCurrentActor->sub4->scaleX) / 0.13;
            sub->unk8 = (s32)(scaleFactor * 400.0f);
            gCurrentActor->yaw += sub->unk8;
        }
        break;
    case 11:
        sub->timer = 0x32;
        sub->unk8 = 0;
        actorAppendCallback(gPrimaryPlayerActor, gCurrentActor, 0x40, 1, 0, 0);
        if (((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk18 == 1.0) {
            angle = D_80750390;
        } else {
            angle = 0xB4;
        }
        actorAppendCallbackPayloadAAB8(gCurrentActor, gPrimaryPlayerActor, (s16)((gCurrentActor->yaw + 0x800) & 0xFFF), (f32)angle, 0);
        if (((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk18 == 1.0) {
            PlayerState *playerState = gPrimaryPlayerActor->customState;
            playerMountBarrel(gPrimaryPlayerActor, 0);
            playerState->isHoldingObject = 1;
            playerState->hitActorType = 0x31;
            playerState->hitActorId = -1;
            sfxAllocateChannel(0x48, 1.0f);
        }
        actorSetCustomFloat(gCurrentActor, 1, 0.0f);
        actorSetCustomInt(gCurrentActor, 7, 0);
        if (sub->unkC != 0) {
            gCurrentActor->state = 0xC;
            if (tagBarrelGetKongType() == 2) {
                camStartPath(gPrimaryPlayerActor, 0x26, 5);
            }
        } else {
            gCurrentActor->interactionType = 1;
            gCurrentActor->state = 0x1E;
        }
        break;
    case 12:
        sub->timer--;
        if (sub->timer < 0x28) {
            offset.x = (randomLcgNext() / 1000 % 50 - 25.0) / 5.0;
            offset.y = (randomLcgNext() / 1000 % 50 - 25.0) / 5.0;
            offset.z = (randomLcgNext() / 1000 % 50 - 25.0) / 5.0;
        }
        if (sub->timer == 0) {
            tagBarrelDespawnEffects();
            if (sub->flagIndex != 0) {
                spawnFlag = func_8073195C(sub->flagIndex);
            } else {
                spawnFlag = -1;
            }
            kong = tagBarrelGetKongType();
            switch (gCurrentMap) {
            case 0xBC:
                flagSet(0x28, 1, 2);
                break;
            case 0xBA:
                flagSet(0x32, 1, 2);
                break;
            default:
                yOffset = -8.0f;
                if (gCurrentMap == 0xAD) {
                    yOffset = -10.0f;
                }
                actorSpawnNodeEntryScaled(0x2D, gCurrentActor->x, gCurrentActor->y + yOffset, gCurrentActor->z, 0, kong, spawnFlag, 0);
                sfxAllocateChannel(0x14, 1.0f);
                actorDespawn(gCurrentActor);
                break;
            }
        }
        break;
    case 20:
        for (i = 0; i < gActorGlobalState.unk254; i++) {
            if (gActorGlobalState.unk258[i] == 1 && *gActorGlobalState.unk278[i] == 0) {
                gCurrentActor->unk144 = 2;
                gCurrentActor->state = 0x15;
                sfxAllocateChannel(0x28, 1.0f);
            }
        }
        break;
    case 21:
        gCurrentActor->alpha += 0xA;
        if (gCurrentActor->alpha >= 0xF1) {
            gCurrentActor->flags |= 0x8000;
            gCurrentActor->state = 0;
        }
        break;
    case 30:
        sub->timer--;
        if (sub->timer == 0) {
            gCurrentActor->unk144 = 2;
            gCurrentActor->state = 0;
        }
        break;
    }
    if (gCurrentActor->state != 0x14) {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
    }
    gCurrentActor->yaw += 0x50;
    gCurrentActor->y = mathSinF(sub->bobPhase) * 5.0 + sub->baseY;
    sub->bobPhase += 0x3C;
    guTranslateF(gCurrentActor->modelMtx, offset.x, offset.y, offset.z);
    actorUpdateModelMatrix(gCurrentActor, 1);
}


void tagBarrelCheckDespawn(void) {
    TagBarrelActorState *sub = gCurrentActor->customState;

    if (!(gCurrentActor->flags & 0x10)) {
        if (flagGet(0x302, 0) != 0) {
            actorDespawn(gCurrentActor);
            return;
        }
    }
    tagBarrelActorUpdate();
    if (gCurrentActor->state == 0xC && sub->timer < 3) {
        flagSet(D_8074E7E0[sub->flagIndex], 1, 2);
        tagBarrelDespawnEffects();
        actorDespawn(gCurrentActor);
    }
}

void tagBarrelUpdateStateCheck(void) {
    TagBarrelActorState *sub = gCurrentActor->customState;
    s32 flag;
    s32 count;
    s32 i;

    tagBarrelActorUpdate();
    if (flagGet(0x17F, 0) == 0) {
        gCurrentActor->state = 0x14;
        gCurrentActor->unk144 = 1;
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->alpha = 0;
    } else {
        if (flagGet(0x187, 0) == 0) {
            count = 0;
            if (gCurrentActor->state == 0xB) {
                i = 0;
                do {
                    count += (flagGet((s16)(i + 0x182), 0) != 0);
                } while (++i != 4);
                if (count == 4) {
                    camStartPath(gPrimaryPlayerActor, 3, 1);
                    flagSet(0x187, 1, 0);
                }
            }
        }
        switch (sub->unk6) {
        case 0xB1:
            flag = 0x182;
            break;
        case 0xB6:
            flag = 0x183;
            break;
        case 0xB4:
            flag = 0x184;
            break;
        case 0xB5:
            flag = 0x185;
            break;
        }
        if (flagGet(flag, 0) != 0) {
            sub->unkC = 1;
            sub->flagIndex = 0;
            if (gCurrentActor->state == 0) {
                gCurrentActor->state = 0x14;
                gCurrentActor->unk144 = 1;
                gCurrentActor->flags &= ~0x8000;
                gCurrentActor->alpha = 0;
            }
        } else if (gCurrentActor->state == 0x14) {
            gCurrentActor->unk144 = 2;
            gCurrentActor->state = 0x15;
        }
    }
    if (gCurrentActor->state == 0xC && sub->timer < 3) {
        tagBarrelDespawnEffects();
        actorDespawn(gCurrentActor);
    }
}

typedef struct RocketbarrelState {
    s16 timer;
    s16 pad2;
    Actor *rider;
} RocketbarrelState;


extern u8 gPlayerInventoryTable[][0x5E];
extern s16 D_80750390;


void rocketbarrelUpdate(void) {
    RocketbarrelState *state;
    s32 pad[3];

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->floorY = 99999.0f;
        collisionCheckGroundAtPoint(gCurrentActor->x, gCurrentActor->z, &gCurrentActor->floorY);
        if (1 == *(s32 *)gCurrentActor->spawnData) {
            if (tagBarrelIsSpecial(gCurrentActor) == 0) {
                gCurrentActor->state = 0x14;
                gCurrentActor->unk144 = 1;
                gCurrentActor->flags &= ~0x8000;
                gCurrentActor->alpha = 0;
            }
        }
    }
    if ((gCurrentActor->state == 0) && (gActorGlobalState.bossFightPhase == 4)) {
        state->timer = 0xA;
        gCurrentActor->state = 1;
        gCurrentActor->unk144 = 1;
        state->rider = gActorGlobalState.targetActor;
        gCurrentActor->flags |= 0x200000;
        switch (gCurrentMap) {
        case 0x11:
        case 0xC9:
        case 0xCC:
            break;
        default:
            sfxAllocateChannel(0x48, 1.0f);
            break;
        }
    }
    switch (gCurrentActor->state) {
    case 0: {
        s32 itemCount;
        if (gPlayerCharacterId < 5) {
            itemCount = gPlayerInventoryTable[gPlayerCharacterId][0];
        }
        if (gPrimaryPlayerActor->actorType == 3 && itemCount >= 2) {
            gCurrentActor->flags |= 0x8000;
            gCurrentActor->interactionType = 1;
        } else {
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->alpha = 0x78;
            gCurrentActor->interactionType = 2;
        }
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
        break;
    }
    case 1:
        state->timer--;
        if (state->timer == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1C6, 0xFF, 0x7F, 0);
            gCurrentActor->state = 2;
            slotQueueUpdate(5, (gGlobalCutsceneFlags & 2) ? 0 : 1, 0);
        }
        break;
    case 2:
        tagBarrelDespawnEffects();
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->alpha = 0;
        actorAppendCallback(state->rider, gCurrentActor, 0x40, 1, 0, 0);
        actorAppendCallbackPayloadAAB8(gCurrentActor, state->rider, state->rider->yaw, (f32) D_80750390, 0);
        playerMountBarrel(state->rider, gCurrentActor);
        gActivePlayerState->isHoldingObject = 1;
        gCurrentActor->state = 3;
        break;
    case 3:
        if (gActorGlobalState.unk0 != 0) {
            gCurrentActor->flags |= 0x8000;
            gCurrentActor->unk144 = 2;
            gCurrentActor->flags &= ~0x200000;
            gCurrentActor->state = 0;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        break;
    case 20: {
        s16 i;
        for (i = 0; i < gActorGlobalState.unk254; i++) {
            if (gActorGlobalState.unk258[i] == 1) {
                gCurrentActor->unk144 = 2;
                gCurrentActor->state = 0x15;
            }
        }
        break;
    }
    case 21:
        gCurrentActor->alpha += 10;
        if (gCurrentActor->alpha >= 0xF1) {
            gCurrentActor->flags |= 0x8000;
            gCurrentActor->state = 0;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct CannonState {
    u8 shotsLeft;
    u8 resetTimer;
    u8 active;
    u8 used;
    Actor *rider;
    s16 aimYaw;
} CannonState;



extern f32 D_8074E7F4;
extern f32 D_8074E7F8;
extern f32 D_8074E7FC;
extern f32 D_8074E800;
extern f32 D_8074E804;
extern f32 D_8074E808;
extern u8 D_8074E810;

f32 cosApprox(f32);

void cannonUpdate(void) {
    CannonState *sub = gCurrentActor->customState;
    Actor *cam;
    f32 sinOff;
    f32 cosOff;
    s32 i;
    u8 resetFlag = 0;
    u8 latchFlag = 0;
    Actor *child;
    f32 x;
    f32 y;
    f32 pitch;
    f32 sinV;
    f32 z;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->interactionType = 1;
        sub->active = 0;
        sub->aimYaw = 0;
        sub->resetTimer = 0;
        sub->used = 0;
    }
    if (gCurrentActor->state == 2 || gCurrentActor->state == 3) {
        cam = ((PlayerState *)sub->rider->customState)->camActor;
        sub->aimYaw = sub->aimYaw - (f64)gPlayerPadState.unk2E * 0.08 * D_8074E7F8 * 4096.0 / 360.0;
        sub->aimYaw = sub->aimYaw & 0xFFF;
        sinOff = mathSinF(sub->aimYaw) * D_8074E7F4;
        cosOff = mathCosF(sub->aimYaw) * D_8074E7F4;
        D_8074E804 = D_8074E804 - (f64)gPlayerPadState.unk2F * 0.04 * D_8074E800;
        if (D_8074E804 > 50.0) {
            D_8074E804 = 50.0f;
        }
        if (D_8074E804 < -50.0) {
            D_8074E804 = -50.0f;
        }
        x = gCurrentActor->x;
        z = gCurrentActor->z;
        y = gCurrentActor->y + D_8074E7FC;
        camSetFixedView(cam, x, y, z, x + sinOff, y + D_8074E804, gCurrentActor->z + cosOff, 0);
        if (camIsCutsceneActive() == 0) {
            renderCallbacksRegister(func_806FF01C, gPrimaryPlayerActor, 3);
            renderCallbacksRegister(func_806FEF7C, gPrimaryPlayerActor, 3);
        }
        func_8066E6C8(gCurrentActor, 0, 0);
    } else {
        func_8066E6C8(gCurrentActor, 0, 1);
    }
    if (sub->active != 0) {
        renderCallbacksRegister(renderRemainingShotsHUD, sub, 3);
    }
    child = gCurrentActor->parentActor;
    if (child != NULL && sub->active != 0 && child->state == 5 && sub->resetTimer == 0) {
        sub->resetTimer = 0x1E;
    }
    if (sub->resetTimer != 0) {
        sub->resetTimer--;
        if (sub->resetTimer == 0) {
            resetFlag = 1;
        }
    }
    for (i = 0; i < gActorGlobalState.unk254; i++) {
        if (gActorGlobalState.unk258[i] == 1) {
            latchFlag = 1;
            sub->used = 1;
        }
    }
    if (resetFlag != 0 || latchFlag != 0) {
        sub->active = 0;
        if (gCurrentActor->state == 2 || gCurrentActor->state == 3) {
            gCurrentActor->state = 3;
        } else {
            gCurrentActor->state = 0;
            gCurrentActor->unk144 = 2;
        }
        child = gCurrentActor->parentActor;
        if (child != NULL) {
            actorDespawn(child);
            gCurrentActor->parentActor = NULL;
        }
        if (resetFlag) {
            csModelStateSetFirstByte(0x30, 0);
            csModelStateSetFirstByte(0x2F, 0);
            csModelStateSetFirstByte(0x31, 0);
        }
    }
    switch (gCurrentActor->state) {
    case 0:
        gCurrentActor->interactionType = 1;
        if (gActorGlobalState.bossFightPhase == 5 && sub->used == 0) {
            gCurrentActor->state = 1;
            gCurrentActor->interactionType = 2;
        }
        break;
    case 1:
        if (gActorGlobalState.bossFightPhase == 4) {
            gCurrentActor->state = 2;
            sub->shotsLeft = 6;
            sub->rider = gActorGlobalState.targetActor;
            if (sub->active == 0) {
                csModelStateSetFirstByte(0x30, 0xA);
                sub->active = 1;
                hudSpawnCountdownTimer(0xC8, 0x20, D_8074E810);
                actorSetStateTwo(gSpawnedActor);
                gCurrentActor->flags |= 0x200000;
            }
            gCurrentActor->flags &= ~4;
            gCurrentActor->unk144 = 1;
        }
        break;
    case 2:
        if ((gPlayerPadState.unk2C & 0x2000) && actorCountOwnedByClass(gCurrentActor, 4, 0) == 0 && sub->shotsLeft != 0) {
            projectileSetTargetCoords(gCurrentActor->x, gCurrentActor->y + D_8074E7FC, gCurrentActor->z);
            x = gPlayerSlots->focusZ - gPlayerSlots->camZ; // FAKE: x/y reused for the focus-camera dz/dx (own dz/dx locals: 8 words FPR diff)
            y = gPlayerSlots->focusX - gPlayerSlots->camX;
            pitch = mathAtan2(gPlayerSlots->focusY - gPlayerSlots->camY, sqrtf(x * x + y * y));
            sinV = sinApprox(pitch) * D_8074E808;
            y = cosApprox(pitch) * D_8074E808; // FAKE: y reused for the cosine term (own cosV local: 8 words FPR diff at 0x70a0)
            projectileSpawnNodeEntry(0x4A, 0, 0.6f, sub->aimYaw, y, sinV, gCurrentActor);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x17, 0xFF, 0x7F, 0x19);
            sub->shotsLeft--;
            if (sub->shotsLeft == 0) {
                gCurrentActor->state = 3;
            }
        }
        break;
    case 3:
        if (actorCountOwnedByClass(gCurrentActor, 4, 0) == 0) {
            actorAppendCallback(sub->rider, gCurrentActor, 0x40, 1, 0, 0);
            actorAppendMoveTarget3D(gCurrentActor, sub->rider, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z - 42.0f, 2, 1);
            sub->rider->flags &= ~8;
            playerResumeLocomotion(sub->rider);
            gCurrentActor->flags |= 4;
            gCurrentActor->state = 0;
            gCurrentActor->unk144 = 2;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct TagBarrelData {
    /* 0x00 */ Actor *player;
    /* 0x04 */ u16 timer;
    /* 0x06 */ s8 selected;
    /* 0x07 */ s8 previous;
    /* 0x08 */ Actor *kongs[5];
    /* 0x1C */ Actor *marker;
    /* 0x20 */ s8 direction;
    /* 0x21 */ u8 pad21;
    /* 0x22 */ s16 baseYaw;
    /* 0x24 */ f32 baseY;
    /* 0x28 */ s16 bobPhase;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 lightR;
    /* 0x30 */ f32 lightG;
    /* 0x34 */ f32 lightB;
    /* 0x38 */ s16 playerYaw;
    /* 0x3A */ u8 pad3A[2];
    /* 0x3C */ u32 frames;
} TagBarrelData;



void tagBarrelOrbitKongs(void *data) {
    TagBarrelData *arg = data;
    f32 centerX = gCurrentActor->x;
    f32 centerY = gCurrentActor->y - 10.0f;
    f32 centerZ = gCurrentActor->z;
    s32 i;
    f32 blend;
    f32 glow;
    f32 clamped;
    s16 baseYaw;
    s16 yaw;
    u8 u;
    u8 *cursor;
    Actor *kong;

    blend = (f32)(u32)arg->timer / 20.0f;
    baseYaw = gCurrentActor->yaw;
    baseYaw = (s16)(s32)(baseYaw + (819.2 * arg->selected)) & 0xFFF;
    baseYaw = (s16)(s32)(baseYaw - (819.2 * blend) * arg->direction) & 0xFFF;
    u = ((u8)(s32)(baseYaw & 0x7FFF) & 0xFFF); // FAKE: dead narrowing chain burns ugen ring temps (loop-start register ring)
    u = ((u8)((s16)(u & 0xFFF) & 0xFFFF) & 0x7FFF); // FAKE: ring temps
    u = (s32)(((u8)(u & 0xFFFF) & 0xFF) & 0x7FFF); // FAKE: ring temps
    u = (u32)u; // FAKE: ring temps
    i = 0;
    cursor = (u8 *)data;
    do {
        kong = *(Actor **)(cursor + 8); // FAKE: byte-pointer walk over the kong array steers the loop induction variable
        yaw = (s16)((s32)(4096.0 - (i * 819.2)) + baseYaw) & 0xFFF;
        kong->x = (mathSinF(yaw) * 45.0f) + centerX;
        kong->z = (mathCosF(yaw) * 45.0f) + centerZ;
        cursor += 4;
        kong->y = centerY;
        if (i == arg->selected) {
            glow = 1.0f - blend;
        } else if (i == arg->previous) {
            glow = blend;
        } else {
            glow = 0;
        }
        glow = (f64)glow - 0.6;
        i++;
        glow = (f64)glow * 2.5;
        if (glow < 0) {
            glow = 0.0f;
        } else {
            if (glow > 1.0f) {
                clamped = 1.0f;
            } else {
                clamped = glow;
            }
            glow = clamped;
        }
        kong->unk15F = (u32)((12.0f * glow) + 3.0f);
    } while (i != 5);
}

void actorScriptStartByKongIndex(void *actor, u16 *kongIndex, s32 index) {
    index = index * 7;
    index += *kongIndex - 2;
    actorScriptStart(actor, gActorScriptIndexTable[index]);
}




void tagBarrelSpawnKongs(TagBarrelData *orbit) {
    s32 i;
    s32 actorType;
    s16 model;
    u16 *kongIndex;
    s32 script;
    actorSpawn(0x136, 0xA8);
    orbit->marker = gSpawnedActor;
    gSpawnedActor->x = gCurrentActor->x + mathSinF(gCurrentActor->yaw) * 35.0f;
    gSpawnedActor->y = (gCurrentActor->y - 10.0f) - 2.0f;
    gSpawnedActor->z = gCurrentActor->z + mathCosF(gCurrentActor->yaw) * 35.0f;

    for (i = 0; i < 5; i++) {
        if (flagGet(mapGetConfigValue(gCurrentActor->actorType, i), 0)) {
            actorType = 0x13C;
            model = D_8074E814[i].model;
        } else {
            actorType = 0x13D;
            model = 0xD2;
        }
        actorSpawn(actorType, model);
        orbit->kongs[i] = gSpawnedActor;
        gSpawnedActor->yaw = gCurrentActor->yaw;
        gSpawnedActor->flags |= 0x40000000;
        if (actorType == 0x13C) {
            kongIndex = gSpawnedActor->customState;
            *kongIndex = D_8074E814[i].kongIndex;
            playerKongStopAudioChannels(gSpawnedActor, *kongIndex);
            script = (i == orbit->selected) ? 0x8B : 0x8A;
            actorScriptStartByKongIndex(gSpawnedActor, kongIndex, script);
        } else {
            u8 *blankIndex = gSpawnedActor->customState;
            *blankIndex = i;
        }
    }
    tagBarrelOrbitKongs(orbit);
}

void tagBarrelUpdateSelectedKong(void) {
    ActorAnimLookup anims;
    u8 *kongIndex;

    if (!(gCurrentActor->flags & 0x10)) {
        anims = D_8074E834;
        kongIndex = gCurrentActor->customState;
        gCurrentActor->flags |= 0x1000;
        animSetLoopLimit(gCurrentActor, 0, 1);
        animSetFinished(gCurrentActor, 0, 1);
        animSetFrameAndSubframe(gCurrentActor, 0, anims.arr[*kongIndex].unk2, 0.0f);
        actorScriptStart(gCurrentActor, 0x329);
    }
    gCurrentActor->tintA = gCurrentActor->unk15F;
    gCurrentActor->yaw += 0x32;
    gCurrentActor->yaw &= 0xFFF;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct ActorExtra3158 {
    u16 kind;
    u16 pad2;
    void (*callback)(Actor *, BoneRotation *, s32 *);
    u32 lastFrame;
} ActorExtra3158;

typedef struct ActorView3158 {
    Actor base;
    void *unk178;
} ActorView3158;



void tagBarrelInteractiveUpdate(void) {
    s32 count;
    ActorExtra3158 *extra;

    count = 0;
    extra = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x1000;
        gCurrentActor->sub4->boneRotations = heapAlloc(0x100);
        heapClearBlock(gCurrentActor->sub4->boneRotations);
        func_806C8220(0, ((ActorView3158 *)gCurrentActor)->unk178, extra->kind);
        switch (extra->kind) {
        case 2:
            extra->callback = playerWeaponAimTarget;
            break;
        case 3:
            extra->callback = playerWeaponInitCrosshair;
            break;
        case 5:
            extra->callback = playerWeaponSpawnProjectile;
            break;
        }
    } else {
        if (extra->callback != NULL) {
            extra->callback(gCurrentActor, gCurrentActor->sub4->boneRotations, &count);
        }
    }
    gCurrentActor->sub4->boneRotations[count].weight = 0;
    gCurrentActor->tintA = gCurrentActor->unk15F;
    gCurrentActor->yaw = mathAngleBetweenPoints2D(gPlayerSlots->camX, gPlayerSlots->camZ, gCurrentActor->x, gCurrentActor->z);
    if (func_8072881C(0, &extra->lastFrame) != 0) {
        if (extra->kind == 3 || extra->kind == 5) {
            func_8072881C(0x81, &extra->lastFrame);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


s32 tagBarrelCheckKongFlag(s32 kongType, s32 setFlag) {
    struct KongFlagInfo {
        s32 value;
        s32 isSet;
        s32 found;
        s32 pad;
    } info;
    struct KongFlagInfo *p = &info;
    s32 ret;

    info.isSet = 0;
    switch (gCurrentMap) {
    default:
        return 0;
    case 7:
    case 26:
    case 30:
    case 38:
    case 42:
    case 48:
        info.found = func_805FEF10(&info.value);
        if (info.found != 0) {
            info.isSet = flagGet(info.value, 0);
            if (setFlag != 0 && info.isSet == 0) {
                flagSet(info.value, 1, 0);
                camStartPath(gPrimaryPlayerActor, 0x19, 4);
                gCurrentActor->unk144 = 1;
                gCurrentActor->unk155 = 0xB;
            }
        }
        ret = p->found != 0; // FAKE: no explicit return: ret/v0 web, operands read via ilod p
        if (ret != 0) {
            return p->isSet == 0;
        }
    }
}

extern s32 D_8074E848[];
extern s32 gGlobalPauseFlags;


void tagBarrelStartSelection(TagBarrelData *data) {
    s32 pad1[2];
    Actor *player;
    PlayerState *playerState;
    s32 pad;
    s32 light;

    switch (gCurrentActor->unk155) {
    case 0xB:
        if (camIsCutsceneActive() == 0) {
            gCurrentActor->unk144 = 2;
            gCurrentActor->unk155 = 0;
        }
        break;
    case 0:
    case 0xA:
        if (gActorGlobalState.bossFightPhase == 4) {
            data->player = gActorGlobalState.targetActor;
            data->player->unk144 = 1;
            ((PlayerState *)data->player->customState)->stateFlags |= 0x20000000;
            gCurrentActor->unk155 = 1;
            data->timer = 2;
            data->frames = 0;
        }
        break;
    case 1:
        if (data->timer != 0) {
            data->timer--;
        } else {
            player = data->player;
            light = player->chunkIndex;
            playerState = player->customState;
            if (light == -1) {
                light = 0;
            }
            playerRestoreKongState(data->player, playerState);
            playerRevertAnimalTransformation(data->player, playerState);
            lightGetColor(&data->lightR, &data->lightG, &data->lightB, (s16)light);
            lightSetColor(1.0f, 1.0f, 1.0f, (s16)light);
            gCurrentActor->yaw = data->baseYaw;
            gCurrentActor->unk144 = 1;
            light = (s16)player->actorType;
            gGlobalPauseFlags &= 0xFFFCFFCF;
            data->selected = 0;
            if (light != D_8074E814[data->selected].kongIndex) {
                do {
                    data->selected++;
                } while (light != D_8074E814[data->selected].kongIndex);
            }
            data->previous = data->selected;
            if (gCurrentMap != 0x11) {
                sfxAllocateChannel(0x65, 1.0f);
                sfxSetChannelParam(0x65, 0x7E - D_8074E848[data->selected], 1);
            }
            flagSet(mapGetConfigValue(gCurrentActor->actorType, data->selected), 1, 0);
            tagBarrelSpawnKongs(data);
            camSaveYaw(playerState->camActor);
            data->playerYaw = player->yaw;
            player->yaw = gCurrentActor->yaw;
            eepromSavePlayerData();
            camStartPath(gCurrentActor, 0xE, 0xC);
            func_8061B650(playerState->camActor);
            slotQueueClearAllFlags();
            gCurrentActor->state = 1;
            gCurrentActor->unk155 = 0;
        }
        break;
    }
}








void tagBarrelUpdateSelection(TagBarrelData *data) {
    s32 pad1;
    u16 prevTimer;
    s32 value;
    s32 pad2[3];
    Actor *player;
    PlayerState *playerState;
    s32 light;
    s32 i;
    s32 timedOut;
    s32 isKong;
    s32 kong;

    value = data->timer;
    prevTimer = value;
    if (value != 0) {
        data->timer = value - 1;
        tagBarrelOrbitKongs(data);
        value = data->timer;
    }
    data->frames++;
    if (value == 0 && hudCanRender() != 0) {
        isKong = data->kongs[data->selected]->actorType == 0x13C;
        timedOut = data->frames >= 9001;
        if (((gPlayerPadState.unk30 >= 0x29) && !timedOut) || !isKong) {
            data->timer = 20;
            if (data->kongs[data->selected]->actorType == 0x13C) {
                actorScriptStartByKongIndex(data->kongs[data->selected], data->kongs[data->selected]->customState, 0x8C);
            }
            data->previous = data->selected;
            if (isKong) {
                data->direction = (gPlayerPadState.unk2E >= 0) ? 1 : -1;
            }
            data->selected += data->direction;
            if (data->selected < 0) {
                data->selected = 4;
            } else if (data->selected >= 5) {
                data->selected = 0;
            }
            if (data->kongs[data->selected]->actorType == 0x13C) {
                actorScriptStartByKongIndex(data->kongs[data->selected], data->kongs[data->selected]->customState, 0x8B);
            }
        } else {
            if (!timedOut && prevTimer != 0) {
                sfxSetChannelParam(0x65, 0x7E - D_8074E848[data->selected], 3);
                sfxSetChannelParam(0x65, D_8074E848[data->selected], 2);
                return;
            }
            if (((timedOut && isKong) || (gPlayerPadState.unk2C & 0xE000)) && screenWipeGetState() == 0) {
                if (isKong) {
                    player = data->player;
                    playerState = player->customState;
                    light = player->chunkIndex;
                    if (light == -1) {
                        light = 0;
                    }
                    lightSetColor(data->lightR, data->lightG, data->lightB, light);
                    gGlobalPauseFlags |= 0x30030;
                    sfxStopChannel(0x48, 0);
                    sfxStopChannel(0x6B, 0);
                    sfxStopChannel(0x49, 0);
                    sfxStopChannel(0x47, 0);
                    sfxStopChannel(0x65, 0);
                    actorDespawn(data->marker);
                    data->marker = NULL;
                    for (i = 0; i < 5; i++) {
                        actorDespawn(data->kongs[i]);
                        data->kongs[i] = NULL;
                    }
                    gCurrentActor->state = 2;
                    gCurrentActor->unk155 = 0;
                    data->timer = 30;
                    playerState->stateFlags &= ~0x20000000;
                    kong = D_8074E814[data->selected].kongIndex;
                    playerSetKongByActorType(kong);
                    playerKongStopAudioChannels(player, kong);
                    playerState->gunDrawn = 0;
                    player->yaw = data->playerYaw;
                    camRestoreYaw(playerState->camActor);
                    camResetPlayer(player, 0);
                    screenWipeStart(3);
                    healthRefill(0);
                    gPlayerSlots->unk2E2 |= 0x11;
                    return;
                }
                sfxPlayOnFreeSlot(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
    }
}

u8 *tagBarrelGetKongName(TagBarrelData *data, s32 slot) {
    s32 isKong = data->kongs[slot]->actorType == 0x13C;
    u8 *ret = NULL;

    if (isKong) {
        ret = textTableGetString(2, sKongNameTextIds[slot], 1);
    }
    return ret;
}

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern s16 gScreenWidth;
extern s16 gScreenHeight;


Gfx *tagBarrelRenderSelectionHud(Gfx *gfx, Actor *actor) {
    u8 padF8[0xC];
    f32 blend;
    s32 pad244;
    f32 textY;
    f32 pad1;
    f32 pad2;
    f32 prevExcess;
    f32 fade;
    f32 alphaExcess;
    f32 prevHalf;
    f32 prevRamp;
    f32 half;
    f32 alphaRamp;
    f32 textX;
    f32 prevX;
    f32 alpha;
    f32 prevAlpha;
    f32 clamped;
    f32 pad3;
    s32 pad4;
    TagBarrelData *data;
    s32 pad5;
    u8 pad70[0x38];
    u8 *text;
    s16 arrowY;

    data = actor->customState;
    textY = (gScreenHeight - 0x1E) * 4.0;
    if (actor->state != 1) {
        return gfx;
    }
    gSPDisplayList(gfx++, &D_1000118);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gSPMatrix(gfx++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    arrowY = textY;
    gfx = renderRotatedSprite(gfx, (u16)(((u32)(gFrameCounter >> 1) % 12) + 0x83), 0, 2, 0x20, 0x10, 0xA0, arrowY, 5.0f, 5.0f, 0, 0.0f);
    gfx = renderRotatedSprite(gfx, (u16)(((u32)(gFrameCounter >> 1) % 12) + 0x83), 0, 2, 0x20, 0x10, (gScreenWidth - 0x28) * 4.0, arrowY, 5.0f, 5.0f, 0xB4, 0.0f);
    blend = (f32)(u32)data->timer * 0.05f;
    text = tagBarrelGetKongName(data, data->selected);
    textY -= (f32) textGetFontHeight(1) * 1.2f;
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    if (text != NULL) {
        fade = 1.0f - blend;
        half = fade * 0.5f;
        textX = half;
        if (data->direction < 0) {
            textX = 1.0f - half;
        }
        alphaRamp = 2.0f * fade;
        textX *= (f32)gScreenWidth * 4.0f;
        if (alphaRamp < 1.0f) {
            alpha = 0.0f;
        } else {
            alphaExcess = alphaRamp - 1.0f;
            if (alphaExcess > 1.0f) {
                clamped = 1.0f;
            } else {
                clamped = alphaExcess;
            }
            alpha = clamped;
        }
        alpha *= 255.0f;
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, (u32)alpha);
        gfx = hudDrawScaledText(gfx, textX, textY, 0.6f, text);
    }
    if (data->timer != 0) {
        text = tagBarrelGetKongName(data, data->previous);
        if (text != NULL) {
            prevHalf = 0.5f * blend;
            prevX = prevHalf;
            if (data->direction > 0) {
                prevX = 1.0f - prevHalf;
            }
            prevRamp = 2.0f * blend;
            prevX *= (f32)gScreenWidth * 4.0f;
            if (prevRamp < 1.0f) {
                prevAlpha = 0.0f;
            } else {
                prevExcess = prevRamp - 1.0f;
                if (prevExcess > 1.0f) {
                    clamped = 1.0f;
                } else {
                    clamped = prevExcess;
                }
                prevAlpha = clamped;
            }
            prevAlpha *= 255.0f;
            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, (u32)prevAlpha);
            gfx = hudDrawScaledText(gfx, prevX, textY, 0.6f, text);
        }
    }
    return gfx;
}

void tagBarrelInitUnlockedKongs(Actor *actor) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (flagGet(mapGetConfigValue(actor->actorType, i), 0)) {
            func_8068A764(actor, D_8074E814[i].action);
        }
    }
}


extern u8 D_8071FC8C[];

void tagBarrelUpdate(void) {
    TagBarrelData *sub = gCurrentActor->customState;

    if (!(gCurrentActor->flags & 0x10)) {
        sub->baseYaw = gCurrentActor->yaw;
        sub->baseY = gCurrentActor->y;
        gCurrentActor->unk146 = 0;
        gCurrentActor->eyeHeight = 0;
        effectSetMode(2);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetMaxDistance(0x3E8);
        effectSetFlags(4);
        effectCreateAtPosition(&D_8071FC8C, 1.3f, gCurrentActor->x, (f32)((f64)gCurrentActor->y + 13.0), gCurrentActor->z);
        if (mapIsBossArena()) {
            gCurrentActor->drawDistance = 0x7D0;
        } else {
            gCurrentActor->drawDistance = 0x15E;
        }
        gCurrentActor->floorY = gCurrentActor->y;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        gCurrentActor->attachMode = 0;
        gCurrentActor->flags |= 2;
    }
    tagBarrelInitUnlockedKongs(gCurrentActor);
    tagBarrelUpdateInteractable();
    actorUpdatePrevContactFlags(gCurrentActor);
    switch (gCurrentActor->state) {
    case 0:
        if (sub->timer != 0) {
            sub->timer--;
            if (sub->timer == 0) {
                gCurrentActor->unk144 = 2;
            }
        } else {
            tagBarrelStartSelection(sub);
        }
        if (gCurrentActor->unk155 == 0xA) {
            if (gPrimaryPlayerActor->contactFlags & 4 || playerSpawnAllPlayers() != 0) {
                gCurrentActor->unk155 = 0;
            } else if (gPrimaryPlayerActor->attachMode != 1 && (gPrimaryPlayerActor->contactFlags & gPrimaryPlayerActor->prevContactFlags & 1)) {
                tagBarrelCheckKongFlag(gPrimaryPlayerActor->actorType, 1);
            }
        }
        break;
    case 1:
        tagBarrelUpdateSelection(sub);
        renderCallbacksRegister(tagBarrelRenderSelectionHud, gCurrentActor, 3);
        break;
    case 2:
        if (sub->timer != 0) {
            sub->timer--;
        } else {
            actorAppendCallbackPayloadAAB8(gCurrentActor, sub->player, sub->playerYaw, 180.0f, 0x46);
            actorAppendCallback(sub->player, gCurrentActor, 0x40, 1, 0, 0);
            slotQueuePopActiveMask();
            gCurrentActor->state = 0;
            gCurrentActor->unk155 = 0;
            if (tagBarrelCheckKongFlag(gPrimaryPlayerActor->actorType, 0) != 0) {
                gCurrentActor->unk155 = 0xA;
            }
            sub->timer = 0x1E;
        }
        break;
    }
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x64, 0x78, 0, 1.0f);
    if (gCurrentActor->state != 1) {
        gCurrentActor->yaw += 0x32;
        gCurrentActor->yaw &= 0xFFF;
        gCurrentActor->y = mathSinF(sub->bobPhase) * 5.0f + sub->baseY;
        sub->bobPhase += 0x32;
        sub->bobPhase &= 0xFFF;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void tagBarrelWrapperUpdateA(void) {
    tagBarrelUpdate();
}

void tagBarrelWrapperUpdateB(void) {
    tagBarrelUpdate();
}

void tagBarrelWrapperUpdateC(void) {
    tagBarrelUpdate();
}
