#include "common.h"
#include "actor.h"
#define PROTO_SKIP_actorDespawn // FAKE: callee prototype steer
#define PROTO_SKIP_actorQueueDelayedCallback // FAKE: callee prototype steer
#define PROTO_SKIP_actorScriptStart // PROTO: The number of arguments doesn't agree with the number in the
#define PROTO_SKIP_actorStepPhysics // FAKE: callee prototype steer
#define PROTO_SKIP_effectCreateAtPosition // FAKE: callee prototype steer
#define PROTO_SKIP_effectSetDepth // FAKE: callee prototype steer
#define PROTO_SKIP_effectSetMode // FAKE: callee prototype steer
#define PROTO_SKIP_effectZSpinMatrixUpdate // PROTO: not a function here
#define PROTO_SKIP_flagGet // FAKE: callee prototype steer
#define PROTO_SKIP_func_806C7BAC // FAKE: callee prototype steer
#define PROTO_SKIP_mapGetConfigValue // FAKE: callee prototype steer
#define PROTO_SKIP_mathAngleClampToArc // FAKE: callee prototype steer
#define PROTO_SKIP_randomLcgNext // FAKE: callee prototype steer
#define PROTO_SKIP_sfxPlayFromActorWithAltitudeCheck // FAKE: callee prototype steer
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
    u8 unk2;
    s16 unk4;
} ActorMapFlag;

typedef struct TagBarrelState {
    /* 0x00 */ u8 pad0[0x6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    union {
        f32 unkC;
        struct {
            u8 unkC_b;
            u8 unkD;
        };
    };
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
} TagBarrelState;

typedef struct ActorD580 {
    /* 0x000 */ u8 pad0[0xCA];
    /* 0x0CA */ u8 unkCA;
} ActorD580;

typedef struct ActorAnimLookup {
    struct {
        s16 unk0;
        s16 unk2;
    } arr[5];
} ActorAnimLookup;

typedef struct ActorGroup5 {
    u8 pad0[8];
    Actor *unk8[5];
} ActorGroup5;

typedef struct ActorKongAction {
    u8 pad0[4];
    u8 unk4;
    u8 unk5;
} ActorKongAction;

extern Actor *gCurrentActor;
extern ActorGlobalState gActorGlobalState;
extern ActorD580 *gActivePlayerState;
extern void *gPrimaryPlayerActor;
extern u16 *gActorScriptIndexTable;
extern s32 gCurrentMap;
extern s32 D_8071FE08;
extern u8 gPlayerCharacterId;
extern ActorMapFlag D_8074E7A0[];
extern s16 D_8074E7E0[];
extern ActorKongAction D_8074E814[];
extern ActorAnimLookup D_8074E834;
extern s32 D_8074E85C[];
extern u8 D_80720120;
extern u8 D_80720340;
extern u8 D_8072038C;

s32 mapGetConfigValue(s32, s32);  // FAKE: callee prototype steer
void actorScriptStart();
s32 actorDespawn(Actor *);  // FAKE: callee prototype steer
void effectSetMode(u32);  // FAKE: callee prototype steer
void effectSetDepth(u32);  // FAKE: callee prototype steer
void effectCreateAtPosition(void *, f32, f32, f32, f32); // FAKE: callee prototype steer
s32 flagGet(s16, s32);  // FAKE: callee prototype steer

s32 tagBarrelIsSpecial(void *actor) {
    s32 count = 4;
    s32 val = actorListFindIdByActor(actor);
    s32 i;

    for (i = 0; i < count; i++) {
        if (gCurrentMap == D_8074E7A0[i].map && val == D_8074E7A0[i].unk2) {
            return flagGet(D_8074E7A0[i].unk4, 0);
        }
    }
    return 0;
}


typedef struct ActorB4C8Sub4 {
    u8 pad0[0x1C];
    struct ActorB4C8Sub4Data *unk1C;
} ActorB4C8Sub4;

typedef struct ActorB4C8Sub4Data {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
} ActorB4C8Sub4Data;

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
    Actor *unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 unk14;
    u8 unk15;
} ActorB4C8State;

typedef struct ActorB4C8PeerState {
    u8 pad0[0xB0];
    f32 unkB0;
    f32 unkB4;
    f32 unkB8;
} ActorB4C8PeerState;

extern u8 D_8071FBC8;
void actorQueueDelayedCallback(Actor *, Actor *, s32, s32, s32, s32, s32);  // FAKE: callee prototype steer

void tagBarrelInitPeerState(void) {
    ActorB4C8State *sub = gCurrentActor->customState;
    ActorB4C8PeerState *peer;
    s32 i;

    if (!(gCurrentActor->flags & 0x10)) {
        ((ActorB4C8Sub4 *)gCurrentActor->sub4)->unk1C = heapAlloc(0x10);
        ((ActorB4C8Sub4 *)gCurrentActor->sub4)->unk1C->unk0 = 0x7F;
        ((ActorB4C8Sub4 *)gCurrentActor->sub4)->unk1C->unk1 = 2;
        ((ActorB4C8Sub4 *)gCurrentActor->sub4)->unk1C->unk2 = (u32)((((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk0 * 65536.0f) / 360.0f);
        ((ActorB4C8Sub4 *)gCurrentActor->sub4)->unk1C->unk4 = 0;
        ((ActorB4C8Sub4 *)gCurrentActor->sub4)->unk1C->unk6 = 0;
        ((ActorB4C8Sub4 *)gCurrentActor->sub4)->unk1C->unk8 = 0;
        sub->unk4 = ((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk4;
        sub->unk8 = ((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk8;
        sub->unkC = ((ActorB4C8Spawn *)gCurrentActor->spawnData)->unkC;
        sub->unk10 = ((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk10;
        sub->unk15 = ((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk14;
        if (1 == ((ActorB4C8Spawn *)gCurrentActor->spawnData)->unk18) {
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
    if (gActorGlobalState.unk200 == 4) {
        sub->unk0 = (Actor *)gActorGlobalState.targetActor;
        gCurrentActor->state = 1;
        if (0) {} // FAKE: empty branch steers uopt web colouring (gActorGlobalState address takes v1 not v0)
        sub->unk14 = 0xA;
        gCurrentActor->unk144 = 1;
        sub->unk0->yaw = gCurrentActor->yaw;
        camStartPath(NULL, sub->unk15, 1);
    }
    switch (gCurrentActor->state) {
        case 1:
            if (--sub->unk14 == 6) {
                scriptSetActorRampTarget(gCurrentActor, 1.0f, 0);
                controllerAnimSetState(gCurrentActor, 0x346, 0, 0.0f);
            }
            if (sub->unk14 == 0) {
                gCurrentActor->state = 2;
            }
            break;
        case 2:
            actorAppendCallback(sub->unk0, (s32)gCurrentActor, 0x40, 1, 0, 0);
            peer = sub->unk0->customState;
            peer->unkB0 = sub->unk8;
            peer->unkB4 = sub->unkC;
            peer->unkB8 = sub->unk10;
            actorAppendCallbackPayloadAAB8((s32)gCurrentActor, sub->unk0, gCurrentActor->yaw, 0.0f, sub->unk4);
            actorQueueDelayedCallback(gCurrentActor, gCurrentActor, 0x800, 2, 0, 0, 0xA);
            effectSetMode(2);
            effectSetDepth(1);
            effectCreateAtActorBone(&D_8071FBC8, 2.0f, gCurrentActor, 1, 2);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x17, 0xFF, 0x7F, 0x19, 0x1E, 0.3f, 0);
            gCurrentActor->state++;
            sub->unk14 = 4;
            break;
        case 3:
            if (sub->unk14-- == 0) {
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

s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, u8);  // FAKE: callee prototype steer
extern u8 D_807FBBA8;


void tagBarrelAnimSetSpeed(s32 arg0) {
    if (!(gCurrentActor->flags & 0x10) && (arg0 == 0x13)) {
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
            actorListSpawnNodeEntryDefault(arg0, gCurrentActor->x, gCurrentActor->y + 8.3, gCurrentActor->z, 0, 1.0f, gCurrentActor);
            gCurrentActor->state++;
            break;
        case 11:
            if (D_807FBBA8 != 0) {
                gCurrentActor->state = 0x14;
            }
            break;
        case 20:
            if (arg0 == 0x95) {
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
    if (arg0 == 0x13) {
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
    char *extra;
    s32 var_v1 = 0;

    extra = (char *)((Actor *)gPrimaryPlayerActor)->customState;
    if ((D_807FBBA8 != 0) && (*(s32 *) (extra + 0x1F0) & 0x200000)) {
        var_v1 = 1;
    }
    if (!(gCurrentActor->flags & 0x10) || var_v1) {
        actorListSpawnNodeEntryDefault(0x55, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0, 1.0f, gCurrentActor);
    }
}

void tagBarrelSpawnType95(void) {
    tagBarrelAnimSetSpeed(0x95);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    gCurrentActor->y = gCurrentActor->floorY;
}

void tagBarrelCheckProximity(void) {
    u8 sp1F;
    u8 *ptr;

    sp1F = 0;
    ptr = gCurrentActor->customState;
    tagBarrelCheckProximityAndFall(0x13, ptr, ptr + 1, &sp1F);
}

void tagBarrelInitDrawDistanceAndState(void) {
    u8 *t0 = gCurrentActor->customState;
    s16 i;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->drawDistance = 0x7D0;
        *(s16 *)t0 = 0x1A;
    }
    for (i = 0; i < gActorGlobalState.unk254; i++) {
        switch (gActorGlobalState.unk258[i]) {
        case 1:
            *(s16 *)t0 = 0x60;
            break;
        case 2:
            *(s16 *)t0 = 0;
            break;
        case 3:
            *(s16 *)t0 = 0x1A;
            break;
        }
    }
    if (*(s16 *)t0 != 0) {
        if (tagBarrelCheckProximityAndFall(*(s16 *)t0, t0 + 2, t0 + 3, t0 + 4)) {
            *(s16 *)t0 = 0x1A;
        }
    } else {
        if (gActorGlobalState.unk38 != 0) {
            t0[4] = 1;
        }
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}

void tagBarrelCheckProximity1A(void) {
    u8 *ptr = gCurrentActor->customState;
    tagBarrelCheckProximityAndFall(0x1A, ptr + 2, ptr + 3, ptr + 4);
}

extern u8 gPlayerCount;
extern struct PlayerData *gPlayerSlots;
typedef struct TagBarrelPlayerEntry {
    u8 unk0;
    u8 pad1[3];
    Actor *player;
    u8 pad8[0x2F0 - 8];
} TagBarrelPlayerEntry;
#define TAG_BARREL_PLAYER_TABLE ((TagBarrelPlayerEntry *)gPlayerSlots)

s32 tagBarrelCheckProximityAndFall(s32 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    volatile u8 sp47; // FAKE: force stack home
    s32 pad[2];
    u8 var_a0;
    f32 var_fs0;
    f32 temp_f0;
    f32 temp_f1;
    sp47 = 0;
    var_fs0 = 99999.0f;
    if (gCurrentActor->flags & 0x10) {
        animSetSpeed(gCurrentActor, 0, 0.5f);
        animSetLoopMode(gCurrentActor, 0, 0);
        animSetDirection(gCurrentActor, 0, 0);
        animSetLoopLimit(gCurrentActor, 0, -1);
        if (D_807FBBA8 != 0 || *arg1 != 0 || *arg3 != 0) {
            *arg3 = 0;
            sp47 = 1;
        }
        if (sp47 != 0) {
            var_a0 = 0;
            if ((s32)gPlayerCount > 0) {
                do {
                    if (TAG_BARREL_PLAYER_TABLE[var_a0].unk0 != 0) {
                        Actor *player = TAG_BARREL_PLAYER_TABLE[var_a0].player;
                        temp_f0 = player->z - gCurrentActor->z;
                        temp_f1 = player->x - gCurrentActor->x;
                        temp_f0 = sqrtf((temp_f0 * temp_f0) + (temp_f1 * temp_f1));
                        if (temp_f0 < var_fs0) {
                            var_fs0 = temp_f0;
                        }
                    }
                    var_a0++;
                } while (var_a0 < gPlayerCount);
            }
            if ((f64)var_fs0 > 12.0) {
                *arg1 = 0;
            } else {
                *arg1 = 1;
                sp47 = 0;
            }
        }
    } else {
        sp47 = 1;
        *arg1 = 0;
        gCurrentActor->speedY = -10.0f;
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        if (actorHasActiveMovementFlags(gCurrentActor) != 0) {
            *arg2 = 1;
        } else {
            *arg2 = 0;
        }
    }
    if (sp47 != 0) {
        actorListSpawnNodeEntryDefault(arg0, gCurrentActor->x, (f32)((f64)gCurrentActor->y + 8.3), gCurrentActor->z, 0, 1.0f, gCurrentActor);
        if (gCurrentActor->flags & 0x10) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x31, 0xFF, 0x7F, 1);
            effectSetDepth(0);
            effectSetDuration(1);
            effectCreateAtPosition(&D_8071FE08, 0.5f, gCurrentActor->x, gCurrentActor->y + 7.0f, gCurrentActor->z);
        }
    }
    if (*arg2 != 0) {
        gCurrentActor->speedY = -10.0f;
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    return sp47;
}

typedef struct ActorC2B8State {
    u8 unk0;
    u8 pad1[3];
    f32 unk4;
    u8 unk8;
} ActorC2B8State;



void actorStepPhysics(Actor *, s16, s16); // FAKE: callee prototype steer

void tagBarrelRotateUpdate(void) {
    ActorC2B8State *temp_v0;
    f32 temp_fv1;
    f32 temp_fv0;
    s16 temp_a1;

    temp_v0 = (ActorC2B8State *) gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags2 |= 4;
        gCurrentActor->flags |= 0x80;
        temp_v0->unk0 = 0;
        temp_v0->unk8 = 0;
        temp_v0->unk4 = 0.0f;
    }
    if (!(gCurrentActor->flags2 & 4)) {
        gCurrentActor->speedXZ = 0.0f;
    }
    if (gActorGlobalState.unk90 != 0) {
        temp_v0->unk8 = 1;
    }
    if (gActorGlobalState.unk91 != 0) {
        if (temp_v0->unk0 == 0) {
            sfxPlayActorSound(gCurrentActor, 0x10C, 0, 1, 0, 0xFF, 1.0f, 0);
            temp_v0->unk0 = 1;
        }
        temp_v0->unk4 = (f64) gActorGlobalState.unk94 / 1.1;
        gCurrentActor->moveYaw = gActorGlobalState.unk92;
        temp_fv1 = gCurrentActor->speedXZ;
        if (temp_fv1 < temp_v0->unk4) {
            gCurrentActor->speedXZ = temp_fv1 + 0.8;
            temp_fv0 = temp_v0->unk4;
            if (temp_fv0 < gCurrentActor->speedXZ) {
                gCurrentActor->speedXZ = temp_fv0;
            }
        } else {
            gCurrentActor->speedXZ = temp_fv1 - 1.5;
            if (gCurrentActor->speedXZ < 0.0f) {
                gCurrentActor->speedXZ = 0.0f;
            }
        }
        gCurrentActor->unkFA = 0x64;
        temp_a1 = gCurrentActor->moveYaw;
        actorStepPhysics(gCurrentActor, temp_a1, temp_a1);
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        gCurrentActor->y = gCurrentActor->floorY;
        if (temp_v0->unk8 == 0) {
            gCurrentActor->unk144 = 0x3C;
        }
    } else {
        if ((temp_v0->unk0 != 0) && ((f64) gCurrentActor->speedXZ == 0.0)) {
            temp_v0->unk0 = 0;
            sfxStopSlotSound(gCurrentActor, 0);
        }
        temp_v0->unk4 = 0.0f;
        temp_fv1 = gCurrentActor->speedXZ;
        if (temp_fv1 < 0.0f) {
            gCurrentActor->speedXZ = temp_fv1 + 0.8;
            temp_fv0 = temp_v0->unk4;
            if (temp_fv0 < gCurrentActor->speedXZ) {
                gCurrentActor->speedXZ = temp_fv0;
            }
        } else {
            gCurrentActor->speedXZ = temp_fv1 - 1.5;
            if (gCurrentActor->speedXZ < 0.0f) {
                gCurrentActor->speedXZ = 0.0f;
            }
        }
        gCurrentActor->unkFA = 0x64;
        temp_a1 = gCurrentActor->moveYaw;
        actorStepPhysics(gCurrentActor, temp_a1, temp_a1);
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        if (temp_v0->unk8 == 0) {
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
typedef f32 ActorC71CMtxF[4][4];

typedef struct ActorC71CState {
    /* 0x00 */ struct Actor *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
} ActorC71CState;

typedef struct ActorC71CSub118 {
    u8 pad0[0xC];
    u8 unkC;
    u8 padD;
    s16 unkE;
    s16 unk10;
} ActorC71CSub118;


extern s32 gGlobalOverlayFlags;
extern u8 D_807FBBA9;
extern f32 D_807FBC60;
extern f32 D_807FBC64;
extern s16 gCurrentCharacterIndex;
extern u32 gFrameCounter;
extern s8 D_80029FA0;
extern u8 D_8071FC40;
extern u8 D_8072030C;
extern s16 D_807502D0;
extern f32 D_807502E4;
extern s16 D_80753444[];

u32 randomLcgNext(void); // FAKE: callee prototype steer
f32 sinApprox(f32);
void mathAngleClampToArc(s16, s16, s16, s16, s16 *); // FAKE: callee prototype steer

void actorTransformCameraUpdate(void) {
    ActorC71CState *temp_s1;
    ActorC71CMtxF spB4;
    ActorC71CMtxF sp74;
    f32 var_fv0;
    f32 var_fv0_2;
    s16 temp_a0;
    u8 *tp;

    temp_s1 = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unkFA = 0x270F;
        temp_s1->unk38 = 0;
        temp_s1->unk39 = 0;
        if (gCurrentActor->actorType == 0x1A) {
            gCurrentActor->flags |= 0x1000;
            effectSetDepth(1);
            effectSetDuration(-1);
            effectSetMaxDistance((s16)((f64)gCurrentActor->drawDistance * 0.75));
            effectCreateAtActorBone(&D_8072030C, 0.14f, gCurrentActor, 1, 2);
            actorClearNodeFlag(gCurrentActor, 3);
        }
        gCurrentActor->floorY = 99999.0f;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        if (actorHasActiveMovementFlags(gCurrentActor)) {
            gCurrentActor->state = 2;
            gCurrentActor->flags2 |= 1;
            temp_s1->unkC = 0x1E;
            gCurrentActor->unk144 = 2;
            temp_s1->unk8 = 360.0f;
            temp_s1->unk14 = 0.0f;
        }
        gCurrentActor->flags2 |= 0x40;
    }

    if (gActorGlobalState.unk24 != 0) {
        if (temp_s1->unk39 == 0) {
            temp_s1->unk0 = gActorGlobalState.unk28;
            gCurrentActor->state = 1;
            temp_s1->unk8 = 360.0f;
            actorCallbackMaskDisable(gCurrentActor, 0x8000);
            actorCollisionEventsCancel(temp_s1->unk0, 1);
            gCurrentActor->unk144 = 0x2C;
            animationOwnerFreeBuffer(gCurrentActor);
        } else {
            actorReleaseFromPlayerHold(gCurrentActor);
        }
    }

    if (gActorGlobalState.unk25 != 0) {
        gCurrentActor->state = 2;
        temp_s1->unkC = 0x1E;
        gCurrentActor->unk144 = 0x3C;
        actorCallbackMaskEnable(gCurrentActor, 0x8000);
    }

    if (((gActorGlobalState.unk15 != 0) || (gActorGlobalState.unk200 == 9)) && (temp_s1->unk39 == 0)) {
        gCurrentActor->state = 4;
        actorReleaseFromPlayerHold(gCurrentActor);
    }

    if (temp_s1->unk39 != 0 && (gActorGlobalState.unk15 != 0 || gActorGlobalState.unk200 == 9)) {
        gCurrentActor->unk144 = 1;
    }

    if (gActorGlobalState.unk2C != 0) {
        gCurrentActor->state = 3;
        gCurrentActor->unk144 = 0x3C;
        actorCallbackMaskEnable(gCurrentActor, 0x8000);
        gCurrentActor->yaw = gActorGlobalState.unk36;
        gCurrentActor->moveYaw = gActorGlobalState.unk36;
        gCurrentActor->speedY = gActorGlobalState.unk30;
        temp_s1->unk4 = gFrameCounter;
        temp_s1->unk18 = 0;
        temp_s1->unk1A = 0;
        gCurrentActor->speedXZ = gActorGlobalState.unk34;
        actorCollisionEventsCancel(temp_s1->unk0, 1);
    }

    actorUpdatePrevContactFlags(gCurrentActor);
    switch (gCurrentActor->state) {
    case 0:
        gCurrentActor->unk144 = 2;
        temp_s1->unk8 = 360.0f;
        temp_s1->unk14 = 0.0f;
        func_8066E6C8(gCurrentActor, 0, 1);
        func_8066E6C8(gCurrentActor, 1, 0);
        gCurrentActor->flags2 |= 1;
        break;
    case 1:
        func_8066E6C8(gCurrentActor, 0, 0);
        func_8066E6C8(gCurrentActor, 1, 0);
        tp = (u8 *)temp_s1->unk0->customState;
        temp_s1->unk8 = *(f32 *)(tp + 0x1BC);
        if (temp_s1->unk8 < 0.0) {
            temp_s1->unk8 += 360.0;
        }
        temp_s1->unk10 = ((f64)temp_s1->unk0->yaw / 4095.0) * 360.0;
        gCurrentActor->flags2 &= ~1;
        break;
    case 2:
        func_8066E6C8(gCurrentActor, 0, 1);
        func_8066E6C8(gCurrentActor, 1, 0);
        if (--temp_s1->unkC == 0) {
            gCurrentActor->state = 0;
        } else if (actorHasActiveMovementFlags(gCurrentActor)) {
            temp_s1->unkC = 0x1E;
        }
        temp_s1->unk8 += 16.0;
        if (temp_s1->unk8 > 360.0) {
            temp_s1->unk8 = 360.0f;
        }
        gCurrentActor->speedY = -200.0f;
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->flags2 |= 1;
        break;
    case 3:
        func_8066E6C8(gCurrentActor, 0, 1);
        func_8066E6C8(gCurrentActor, 1, 1);
        gCurrentActor->speedY += D_807502E4;
        if (gCurrentActor->speedY < (f32)D_807502D0) {
            gCurrentActor->speedY = (f32)D_807502D0;
        }
        temp_s1->unk14 -= 10.0f;
        if (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->yaw) == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x23, 0xFF, 0x7F, 1);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x17, 0xFF, 0x7F, 1);
            gCurrentActor->state = 8;
        }
        gCurrentActor->flags2 &= ~1;
        break;
    case 4:
        temp_s1->unk39 = 1;
        gCurrentActor->state = 8;
        break;
    case 5:
        func_8066E6C8(gCurrentActor, 0, 1);
        func_8066E6C8(gCurrentActor, 1, 1);
        temp_s1->unk28 -= 3.0;
        if (temp_s1->unk28 < 270.0) {
            temp_s1->unk28 = 270.0f;
        }
        var_fv0 = sinApprox((f32)temp_s1->unk20 / 12.6);
        gCurrentActor->y = temp_s1->unk1C + (f32)(var_fv0 * 1.5);
        var_fv0 = sinApprox((f32)temp_s1->unk20 / 9.34);
        temp_s1->unk8 = temp_s1->unk28 + var_fv0 * 7.0f;
        temp_s1->unk20++;
        var_fv0 = (f32) (-5.0 - temp_s1->unk24);
        var_fv0 = (f32) (var_fv0 / -5.0);
        var_fv0 = (f32) (var_fv0 * -0.5);
        if (D_807FBBA9 == 0) {
            var_fv0 = (f32) (-0.5 - var_fv0);
            var_fv0 = (f32) (0.0 - var_fv0);
        }
        temp_s1->unk24 += var_fv0;
        gCurrentActor->y += temp_s1->unk24;
        if (--temp_s1->unk2C == 0 || temp_s1->unk2C == 5 || temp_s1->unk2C == 10 ||
            temp_s1->unk2C == 15 || temp_s1->unk2C == 20 || temp_s1->unk2C == 26) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x55, 0xFF, (s16)(0xA7 - temp_s1->unk2C * 2), 0);
        }
        if (temp_s1->unk2C == 0 || gCurrentActor->waterY < gCurrentActor->floorY) {
            gCurrentActor->state = 6;
            if (sinApprox((f32)temp_s1->unk20 / 9.34) > 0.0) {
                temp_s1->unk30 = 1;
            } else {
                temp_s1->unk30 = 0;
            }
            temp_s1->unk34 = 0.1f;
        }
        gCurrentActor->speedY = 0.0f;
        gCurrentActor->speedXZ = 35.0f;
        gCurrentActor->flags2 |= 1;
        pathFollowUpdateHeading(gCurrentActor, 0);
        if ((*(ActorC71CSub118 **)gCurrentActor->unk118)->unkC == 0) {
            gCurrentActor->moveYaw = (*(ActorC71CSub118 **)gCurrentActor->unk118)->unkE;
            gCurrentActor->speedXZ = (f32)(*(ActorC71CSub118 **)gCurrentActor->unk118)->unk10;
        } else {
            gCurrentActor->speedXZ = 0.0f;
        }
        if (gCurrentActor->hasArcBounds != 0) {
            temp_a0 = gCurrentActor->moveYaw;
            mathAngleClampToArc(temp_a0, temp_a0, gCurrentActor->arcYawMin, gCurrentActor->arcYawMax, &gCurrentActor->unkF2);
            gCurrentActor->moveYaw = gCurrentActor->unkF2;
        }
        break;
    case 6:
        if (((randomLcgNext() / 100000) % 3) == 0) {
            effectSetDepth(1);
            effectSetDuration(-1);
            effectSetCallback(effectWobbleRiseUpdate);
            effectCreateAtPosition(&D_8071FC40, 0.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        }
        if (temp_s1->unk30 != 0) {
            if (temp_s1->unk30 == 1) {
                temp_s1->unk8 += 1.5;
                if (temp_s1->unk8 > 360.0) {
                    temp_s1->unk8 = 360.0f;
                }
            }
        } else {
            temp_s1->unk8 -= 1.5;
            if (temp_s1->unk8 < 0.0) {
                temp_s1->unk8 = 0.0f;
            }
        }
        temp_s1->unk2C++;
        if ((temp_s1->unk2C & 3) == 0 && (u32)temp_s1->unk2C < 29) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x55, (0xC0 - temp_s1->unk2C * 6) & 0xFF, (s16)(temp_s1->unk2C * 2 + 0x50), 0);
        }
        temp_s1->unk34 += 2.0;
        if (temp_s1->unk34 > 40.0) {
            temp_s1->unk34 = 40.0f;
        }
        gCurrentActor->speedY = -temp_s1->unk34;
        gCurrentActor->speedXZ = 0.0f;
        if ((f64)gCurrentActor->distToFloor < 0.5) {
            gCurrentActor->state = 7;
            temp_s1->unk2C = 0x78;
        }
        gCurrentActor->flags2 &= ~1;
        break;
    case 7:
        gCurrentActor->y -= 0.15;
        if (--temp_s1->unk2C == 0) {
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
                temp_s1->unk3A = 0x14;
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
                gCurrentActor->parentActor = 0;
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
        if (temp_s1->unk3A == 0) {
            actorDespawn(gCurrentActor);
        } else {
            temp_s1->unk3A--;
        }
        var_fv0_2 = ((f32)temp_s1->unk3A / 20.0f) * 200.0;
        if (var_fv0_2 > 130.0) {
            var_fv0_2 = 200.0f;
        }
        lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, var_fv0_2, 0, 0xFF, 0xFF, 0xFF);
        camStartShakeFromPoint(*(s32 *)((u8 *)((Actor *)gPrimaryPlayerActor)->customState + 0x104), 5, 10, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
        break;
    }

    if (gCurrentActor->state == 2 || gCurrentActor->state == 3 || gCurrentActor->state == 5 || gCurrentActor->state == 6) {
        if (gCurrentActor->state != 5) {
            gCurrentActor->moveYaw = gCurrentActor->yaw;
        }
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 7.0f);
        if (gCurrentActor->state == 2 && temp_s1->unk8 == 360.0f && (gCurrentActor->y - gCurrentActor->prevY) < -2.0f && (gGlobalOverlayFlags & 1)) {
            actorReleaseFromPlayerHold(gCurrentActor);
            gCurrentActor->state = 4;
            temp_s1->unk39 = 1;
        }
        if (gCurrentActor->state == 3 && gCurrentActor->actorType == 0x1A && (u32)D_80753444[gCurrentCharacterIndex] < (u32)(gFrameCounter - temp_s1->unk4)) {
            gCurrentActor->state = 4;
        }
        if (gCurrentActor->state == 3 && (gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
            gCurrentActor->speedY = 140.0f;
            temp_s1->unk1A++;
            if ((gCurrentActor->actorType == 0x1A && temp_s1->unk1A == 4) || (gCurrentActor->actorType == 0x95 && temp_s1->unk1A == 2)) {
                gCurrentActor->state = 4;
            }
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x32, 0xFF, 0x7F, 1);
        }
        if (gCurrentActor->state == 2 && (gCurrentActor->contactFlags & 4)) {
            gCurrentActor->state = 5;
            gCurrentActor->y = gCurrentActor->waterY;
            temp_s1->unk2C = 1000;
            temp_s1->unk1C = gCurrentActor->y - 1.5;
            temp_s1->unk20 = 0;
            temp_s1->unk28 = temp_s1->unk8;
        }
        if (gCurrentActor->state == 5) {
            temp_s1->unk1C = gCurrentActor->waterY;
        }
        if (gCurrentActor->state == 3 && (gCurrentActor->contactFlags & 4) && temp_s1->unk19 == 0) {
            switch (temp_s1->unk18) {
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
                temp_s1->unk2C = 1000;
                temp_s1->unk1C = gCurrentActor->y - 1.5;
                temp_s1->unk20 = 0;
                temp_s1->unk28 = temp_s1->unk8;
                break;
            }
            temp_s1->unk18++;
            temp_s1->unk19 = 3;
            gCurrentActor->speedXZ -= 20.0;
        } else if (temp_s1->unk19 != 0) {
            temp_s1->unk19--;
        }
        gCurrentActor->floorSlopeYaw = 0x3FF;
        gCurrentActor->floorSlopePitch = 0x3FF;
    } else {
        gCurrentActor->attachMode = 0;
        gCurrentActor->contactFlags &= ~0x408;
    }

    temp_s1->unk38 = gCurrentActor->state;
    if (gCurrentActor->state != 9) {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
    }
    guScaleF(spB4, gCurrentActor->sub4->scaleX, gCurrentActor->sub4->scaleY, gCurrentActor->sub4->scaleZ);
    guRotateF(sp74, temp_s1->unk14, 0.0f, 1.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);
    guRotateF(sp74, ((f64)gCurrentActor->yaw / 4095.0) * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);
    guRotateF(sp74, temp_s1->unk8 - D_807FBC60, 1.0f, 0.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);
    guRotateF(sp74, (temp_s1->unk10 + 90.0f) - D_807FBC64, 0.0f, 1.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);

    if (gCurrentActor->state == 3) {
        if (gCurrentActor->floorSlopePitch < 1000) {
            guRotateF(sp74, -(((f64)gCurrentActor->floorSlopeYaw / 4095.0) * 360.0), 0.0f, 1.0f, 0.0f);
            guMtxCatF(spB4, sp74, spB4);
        }
        guRotateF(sp74, 90.0 - ((f64)gCurrentActor->floorSlopePitch / 4095.0) * 360.0, 1.0f, 0.0f, 0.0f);
        guMtxCatF(spB4, sp74, spB4);
        if (gCurrentActor->floorSlopePitch < 1000) {
            guRotateF(sp74, ((f64)gCurrentActor->floorSlopeYaw / 4095.0) * 360.0, 0.0f, 1.0f, 0.0f);
            guMtxCatF(spB4, sp74, spB4);
        }
    }
    guTranslateF(sp74, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    guMtxCatF(spB4, sp74, (float (*)[4])((u8 *)gCurrentActor + 0xC));
}

extern s32 D_8071FE64;
extern s32 D_8071FE88;
extern s32 D_8071FEAC;

void tagBarrelDespawnEffects(void) {
    void (*sp5C)(void);
    f32 temp_fs0;
    s32 temp_s0;
    s32 var_s1;

    temp_fs0 = (f64) gCurrentActor->sub4->scaleY / 0.15;
    rumbleRequest(0, 0xB4, 0xA);
    effectSetDepth(0);
    effectSetDuration(1);
    effectCreateAtPosition(&D_8071FE08, (f64) temp_fs0 * 0.75, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x23, 0xFF, 0x7F, 1);

    for (var_s1 = 0; var_s1 != 7; var_s1++) {
        temp_s0 = ((s32) (randomLcgNext() / 10000U)) % 3;
        effectSetDepth(1);
        effectSetDuration(0xA);
        effectSetCallback(effectTumbleBounceUpdate);
        effectSetMode(2);
        effectSetSpeed(2);
        switch (temp_s0) {
        case 0:
            effectCreateAtPosition(&D_8071FE64, (f64) temp_fs0 * 0.25, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            break;
        case 1:
            effectCreateAtPosition(&D_8071FE88, (f64) temp_fs0 * 0.25, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            break;
        case 2:
            effectCreateAtPosition(&D_8071FEAC, (f64) temp_fs0 * 0.25, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            break;
        }
    }
}

void tagBarrelSpawnSmokeAndPuffs(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    f64 sp80;
    f32 sp7C;
    f32 temp_fs2;
    f32 temp_fs1;
    f32 temp_fs0;
    s32 var_s0;

    if (arg5 != 0) {
        sfxPlayAtPositionPooled(arg0, arg1, arg2, 0xF6, 0xFF, 0x7F, 0x19, 0x1E, 0.3f, 0);
    }
    effectSetDepth(1);
    effectSetCallback(effectPuffExpandFadeUpdate);
    effectCreateAtPosition(&D_80720120, 0.0f, arg0, arg1 + 5.0f, arg2);
    sp80 = (f64) arg3;
    sp7C = sp80 * 1.5;
    for (var_s0 = 0; var_s0 < 5; var_s0++) {
        temp_fs1 = (f32) (((s32) (randomNonNegative() >> 15) % 20) - 10) * arg3;
        temp_fs2 = (f32) (((s32) (randomNonNegative() >> 15) % 20) - 10) * arg3;
        temp_fs0 = (f32) (((s32) (randomNonNegative() >> 15) % 20) - 10) * arg3;
        effectSetAngle(4);
        effectSetDepth(1);
        effectSetDuration(1);
        effectSetCallback(effectSpinBillboardingUpdate);
        effectCreateAtPosition(&D_80720340, sp7C, arg0 + temp_fs1, arg1 + temp_fs2, arg2 + temp_fs0);
    }
    effectSetAngle(4);
    effectSetDepth(1);
    effectSetDuration(1);
    effectSetCallback(effectSpinBillboardingUpdate);
    effectCreateAtPosition(&D_80720340, sp7C, arg0, arg1, arg2);
    if (arg4 != 0) {
        for (var_s0 = 0; var_s0 != 12; var_s0++) {
            effectSetDepth(1);
            effectSetDuration(2);
            effectSetSpeed(var_s0 + 0x0B020000);
            effectSetCallback(effectRadialSprayUpdate);
            effectSetMode(1);
            effectCreateAtPosition(&D_8072038C, (f32)(sp80 * 0.5), arg0, arg1, arg2);
        }
    }
}

void tagBarrelSpawnActorSmokePuffs(arg0, arg1)
u8 arg0;
u8 arg1;
{
    tagBarrelSpawnSmokeAndPuffs(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, (f32) ((f64) gCurrentActor->sub4->scaleY / 0.15), arg0, arg1);
}

void tagBarrelSpawnNodeSmokePuffs(s32 arg0, u8 arg1, f32 arg2) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    actorGetNodePos(gCurrentActor, arg1, &sp2C, &sp28, &sp24);
    tagBarrelSpawnSmokeAndPuffs(sp2C, sp28, sp24, arg2, 0, 1);
}

void tagBarrelResetMovement(void) {
    TagBarrelState *temp_v0 = gCurrentActor->customState;

    gCurrentActor->sub4->scaleX = temp_v0->unkC;
    gCurrentActor->sub4->scaleY = temp_v0->unkC;
    gCurrentActor->sub4->scaleZ = temp_v0->unkC;
    gCurrentActor->y = temp_v0->unk14;
    temp_v0->unk8 = 0;
    temp_v0->unk18 = 0;
    temp_v0->unk10 = temp_v0->unkC;
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
    u8 unk0;
    u8 unk1;
    u8 unk2;
} TransformBarrelEntry;

typedef struct TransformBarrelPlayerStruct {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2C8 - 0x2C1];
    s16 unk2C8;
    u8 pad2CA[0x2F0 - 0x2CA];
} TransformBarrelPlayerStruct;

typedef struct TransformBarrelPlayerState {
    /* 0x000 */ u8 pad0[0x88];
    /* 0x088 */ Actor *unk88;
    /* 0x08C */ u8 pad8C[0x104 - 0x8C];
    /* 0x104 */ s32 unk104;
    /* 0x108 */ u8 pad108[0x1A4 - 0x108];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x1F0 - 0x1A5];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0x1FD - 0x1F4];
    /* 0x1FD */ u8 unk1FD;
} TransformBarrelPlayerState;

typedef struct TransformBarrelState {
    s16 unk0;
    s16 unk2;
    Actor *unk4;
    s16 unk8;
    s16 unkA;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    u8 unk1C;
} TransformBarrelState;

extern TransformBarrelEntry D_8074E7BC[];
extern u8 gPlayerInventoryTable[][0x5E];

extern s32 gGlobalPauseFlags;
extern s32 gGlobalCutsceneFlags;


void transformBarrelUpdate(void) {
    TransformBarrelState *var_t0;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    TransformBarrelPlayerState *playerState;
    s32 ret;
    s16 i;
    s16 sp8C;
    s16 sp8A = 8;
    u8 sp89;
    Actor *player;
    TransformBarrelPlayerState *activePlayerState;
    s32 var_v1_2;
    s32 var_a0c;
    TransformBarrelPlayerState *ps3;

    var_t0 = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        sp8C = 0;
        sp89 = 0;
        ret = actorListFindIdByActor(gCurrentActor);
        if ((Actor *)gPrimaryPlayerActor) {} // FAKE: raises &gPrimaryPlayerActor candidate priority
        var_t0->unk1C = 0;
        do {
            if (gCurrentMap == D_8074E7BC[sp8C].unk0 && ret == D_8074E7BC[sp8C].unk1) {
                sp89 = 1;
                var_t0->unk1C = D_8074E7BC[sp8C].unk2;
            } else {
                sp8C++;
            }
        } while (!sp89 && sp8C < sp8A);

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
        var_t0->unk10 = gCurrentActor->sub4->scaleY;
        var_t0->unkC = gCurrentActor->sub4->scaleY;
        var_t0->unk8 = 0;
        var_t0->unk18 = 0;
        var_t0->unk14 = gCurrentActor->y;
        if (((u32)gCurrentActor->actorType) == 0x12 || ((u32)gCurrentActor->actorType) == 0x81) {
            var_t0->unk1A = ((s32 *)gCurrentActor->spawnData)[1];
        }
    }
    actorUpdatePrevContactFlags(gCurrentActor);

    if (gCurrentActor->state == 0 && gActorGlobalState.unk200 == 4) {
        playerState = ((Actor *)gPrimaryPlayerActor)->customState;

        sfxStopChannel(0x6B, 1);
        if (((u32)gCurrentActor->actorType) != 0x60) {
            sfxAllocateChannel(0xF, 1.0f);
        }
        if (var_t0->unk1A != 0) {
            ret = -1;

            if (((u32)gCurrentActor->actorType) == 0x12) {
                ret = 0xF;
            } else if (((u32)gCurrentActor->actorType) == 0x81) {
                ret = 0x10;
            }
            if (ret >= 0) {
                flagSet(ret, 1, 1);
            }
            playerState->unk1FD = 1;
        }
        if (gGlobalCutsceneFlags & 2) {
            var_t0->unk0 = 0x1E;
        } else {
            switch (((u32)gCurrentActor->actorType)) {
            case 0x60:
                var_t0->unk0 = 0x32;
                break;
            case 0x38:
                var_t0->unk0 = 0x1E;
                break;
            default:
                var_t0->unk0 = 0x64;
                break;
            }
        }
        if (var_t0->unk1C != 0) {
            s32 temp_s0 = slotQueueGetValue(5, playerState->unk1A4);
            s32 temp_lo = slotQueueGetCountStep(5) * var_t0->unk1C;

            if (temp_s0 < temp_lo) {
                slotQueueAddValue(5, playerState->unk1A4, (s16)(temp_lo - temp_s0));
            }
        }
        gCurrentActor->state = 1;
        gCurrentActor->unk144 = 1;
        var_t0->unk4 = (Actor *)gActorGlobalState.targetActor;
        gCurrentActor->flags |= 0x200000;
        if (!(gGlobalOverlayFlags & 0x2000)) {
            if (var_t0->unk4->collisionFlags & 1) {
                ps3 = var_t0->unk4->customState;

                if (ps3->unk88 != NULL) {
                    actorDespawn(ps3->unk88);
                    ps3->unk88 = NULL;
                    camSetFollowMode(ps3->unk104);
                }
            }
        }
        var_t0->unk4->unk144 = 1;
    }

    if (gCurrentActor->state < 0x14) {
        s32 var_a0 = 0;
        s32 var_a1 = 0;

        if (gPlayerCharacterId < 5) {
            var_a0 = gPlayerInventoryTable[gPlayerCharacterId][0];
        }
        player = gPrimaryPlayerActor;
        if (((u32)player->actorType) == 5 && ((u32)gCurrentActor->actorType) == 0x28 && var_a0 > 0) {
            var_a1 = 1;
        }
        if (((u32)player->actorType) == 6 && ((u32)gCurrentActor->actorType) == 0x19 && var_a0 > 0) {
            var_a1 = 1;
        }
        if (((u32)player->actorType) == 6 && ((u32)gCurrentActor->actorType) == 0x60 && var_a0 > 0) {
            var_a1 = 1;
        }
        if (((u32)player->actorType) == 4 && ((u32)gCurrentActor->actorType) == 0x38 && var_a0 >= 3) {
            var_a1 = 1;
        }
        if (((u32)player->actorType) == 2 && ((u32)gCurrentActor->actorType) == 0x39 && var_a0 >= 2) {
            var_a1 = 1;
        }
        if (((u32)player->actorType) == 4 && ((u32)gCurrentActor->actorType) == 0x81) {
            var_a1 = 1;
        }
        if (((u32)gCurrentActor->actorType) == 0x12) {
            var_a1 = 1;
        }
        if (((u32)gCurrentActor->actorType) == 0x84 && ((u32)player->actorType) == 9 && (activePlayerState = player->customState)->unk88 == NULL) {
            var_a1 = 1;
        }
        if (var_a1 != 0) {
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
        if (((u32)gCurrentActor->actorType) != 0x12 && ((u32)gCurrentActor->actorType) != 0x81 && ((u32)gCurrentActor->actorType) != 0x84) {
            animSetSpeed(gCurrentActor, 0, 0.5f);
            animSetLoopMode(gCurrentActor, 0, 0);
            animSetEndFrame(gCurrentActor, 0, 9);
            animSetLoopLimit(gCurrentActor, 0, 0x32);
        }
        break;

    case 1:
        if (var_t0->unk0 < 0x1E) {
            switch (((u32)gCurrentActor->actorType)) {
            case 0x19:
            case 0x60:
                var_t0->unk10 += (((u32)gCurrentActor->actorType) == 0x19) ? 0.004 : 0.008;
                gCurrentActor->y += 0.6;
                if ((gCurrentActor->y - var_t0->unk14) > 25.0f) {
                    gCurrentActor->y = var_t0->unk14 + 25.0f;
                }
                break;
            case 0x28:
                var_t0->unk10 -= 0.001;
                gCurrentActor->y += 0.6;
                if ((gCurrentActor->y - var_t0->unk14) > 25.0f) {
                    gCurrentActor->y = var_t0->unk14 + 25.0f;
                }
                break;
            case 0x12:
            case 0x81:
            case 0x84:
                var_t0->unk10 += 0.006;
                break;
            }
        }
        gCurrentActor->sub4->scaleX = sinApprox(var_t0->unk8 * 0.11) * 0.1 + var_t0->unk10;
        gCurrentActor->sub4->scaleY = sinApprox(var_t0->unk8 * 0.2352) * 0.1 + var_t0->unk10;
        gCurrentActor->sub4->scaleZ = sinApprox(var_t0->unk8 * 0.176) * 0.1 + var_t0->unk10;
        var_t0->unk8++;
        if (((u32)gCurrentActor->actorType) != 0x12 && ((u32)gCurrentActor->actorType) != 0x81 && ((u32)gCurrentActor->actorType) != 0x84) {
            gCurrentActor->yaw += var_t0->unk18;
            var_t0->unk18 += 10;
            if (var_t0->unk18 >= 0x65) {
                var_t0->unk18 = 0x64;
            }
        }
        actorAppendCallbackPayloadA70C(gCurrentActor, var_t0->unk4, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 2, 1);
        var_t0->unk0--;
        if (var_t0->unk0 == 0) {
            var_t0->unk0 = 0xC;
            gCurrentActor->state = 2;
            if (((u32)gCurrentActor->actorType) != 0x12 && ((u32)gCurrentActor->actorType) != 0x81 && gCurrentMap != 0x52 && !(gGlobalOverlayFlags & 1)) {
                slotQueueUpdate(5, 1, 0);
            }
        }
        break;

    case 2:
        var_t0->unk0--;
        if (var_t0->unk0 == 0) {
            gCurrentActor->state = 3;
        }
        break;

    case 3: {
        s16 sp62 = 0;
        if (((u32)((Actor *)gPrimaryPlayerActor)->actorType) == 9) {}  // FAKE: dead compare steers uopt constant-web (0x81/0x84) colouring order
        switch (((u32)gCurrentActor->actorType)) {
        case 0x28:
            sp62 = 0x10;
            sfxPlayOnFreeSlot(0x1A5, 0x58EF, 63.0f, 1.0f, 0, 0);
            break;
        case 0x19:
            sp62 = 0x11;
            sfxPlayOnFreeSlot(0xC7, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        case 0x12:
            sp62 = 0x24;
            sfxPlayOnFreeSlot(0x2EC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            gGlobalPauseFlags |= 0x400;
            break;
        case 0x39:
            sp62 = 0x47;
            break;
        case 0x38:
            sp62 = 0x49;
            break;
        case 0x81:
            sp62 = 0x7C;
            gGlobalPauseFlags |= 0x400;
            break;
        }
        if (sp62 != 0 && !(gGlobalCutsceneFlags & 2) && gCurrentMap != 3 && gCurrentMap != 0x11 && gCurrentMap != 0x52 && gCurrentMap != 0xD1) {
            if (gPlayerCharacterId) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            sfxAllocateChannel(sp62, 1.0f);
        }
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x9C, 0xFF, 0x7F, 0);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x9D, 0xFF, 0x7F, 0);
        if (((u32)gCurrentActor->actorType) != 0x12 && ((u32)gCurrentActor->actorType) != 0x81 && ((u32)gCurrentActor->actorType) != 0x84) {
            animResetEndFrame(gCurrentActor, 0);
            animSetFrameAndSubframe(gCurrentActor, 0, 0xA, 0.0f);
        }
        actorGetNodePos(gCurrentActor, 1, &spA0, &sp9C, &sp98);
        actorAppendCallback(var_t0->unk4, (s32)gCurrentActor, 0x40, 1, 0, NULL);
        {
            s16 angle;
            if (((u32)gCurrentActor->actorType) == 0x12) {
                angle = ((TransformBarrelPlayerStruct *)gPlayerSlots)->unk2C8 & 0xFFF;
            } else {
                angle = var_t0->unk4->yaw;
            }
            actorAppendCallbackPayloadAAB8((s32)gCurrentActor, var_t0->unk4, angle, -40.0f, 0);
        }
        actorSetInteractionTimer(var_t0->unk4);
        tagBarrelDespawnEffects();
        gCurrentActor->state = 4;
        if (((u32)gCurrentActor->actorType) == 0x39) {
            sfxPlayOnFreeSlot(0x231, 0x58EF, 63.0f, 1.0f, 0, 0);
        }
        if (((u32)gCurrentActor->actorType) == 0x38) {
            sfxPlayOnFreeSlot(0xD4, 0x58EF, 63.0f, 1.0f, 0, 0);
        }
        break;
    }

    case 4: {
        playerState = var_t0->unk4->customState;
        var_v1_2 = 0;

        switch (((u32)gCurrentActor->actorType)) {
        case 0x19:
        case 0x28:
        case 0x60:
            if (((TransformBarrelPlayerStruct *)gPlayerSlots)[playerState->unk1A4].unk2C0 != 1) {
                var_v1_2 = 1;
            }
            break;
        case 0x39:
            if (playerState->unk1F0 & 0x10) {
                var_v1_2 = 1;
            }
            break;
        case 0x38:
            if (playerState->unk1F0 & 0x20) {
                var_v1_2 = 1;
            }
            break;
        case 0x12:
            if (((u32)((Actor *)gPrimaryPlayerActor)->actorType) == 8) {
                var_v1_2 = 1;
            }
            break;
        case 0x81:
            if (((u32)((Actor *)gPrimaryPlayerActor)->actorType) == 9) {
                var_v1_2 = 1;
            }
            break;
        case 0x84:
            if (playerState->unk88 != NULL) {
                var_v1_2 = 1;
            }
            break;
        }

        if (var_v1_2 != 0) {
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->alpha = 0;
        } else {
            gGlobalPauseFlags &= ~0x400;
            if (((u32)gCurrentActor->actorType) != 0x60) {
                var_a0c = 0;
                switch (((u32)gCurrentActor->actorType)) {
                case 0x38:
                    var_a0c = 0x49;
                    break;
                case 0x81:
                    var_a0c = 0x7C;
                    break;
                case 0x39:
                    var_a0c = 0x47;
                    break;
                case 0x12:
                    var_a0c = 0x24;
                    break;
                case 0x19:
                    var_a0c = 0x11;
                    break;
                case 0x28:
                    var_a0c = 0x10;
                    break;
                }
                sfxStopChannel(var_a0c, 0);
                sfxAllocateChannel(0xF, 1.0f);
            }
            gCurrentActor->state = 5;
            if ((gGlobalCutsceneFlags & 2) && ((u32)gCurrentActor->actorType) == 0x19) {
                var_t0->unk0 = 1;
            } else {
                var_t0->unk0 = 0x5A;
            }
        }
        break;
    }

    case 5:
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->alpha = 0;
        var_t0->unk0--;
        if (var_t0->unk0 == 0) {
            if (gCurrentMap == 0xCE) {
                tagBarrelTriggerRecoil();
            } else {
                tagBarrelResetMovement();
            }
            if (((u32)gCurrentActor->actorType) != 0x12 && ((u32)gCurrentActor->actorType) != 0x81) {
                slotQueueCancel(5, 0);
            }
            if (((u32)gCurrentActor->actorType) == 0x60) {
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
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} ActorFB6CSpawnData;

typedef struct ActorFB6CCamHolder {
    u8 pad0[0x104];
    s32 unk104;
} ActorFB6CCamHolder;

typedef struct ActorFB6CState {
    Actor *unk0;
    u32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
} ActorFB6CState;

extern Actor *gActivePlayerActor;
extern s32 gGlobalCutsceneFlags;
extern u16 D_807FD63C;

f32 mathCosF(s16);
f32 mathSinF(s16);

void tagBarrelParticleUpdate(void) {
    f64 pad;
    f32 sp5C;
    f32 sp58;
    s32 sp54;
    s32 pad2;
    s16 sp4E;
    ActorFB6CState *sub;
    s32 var_v0;
    f32 var_fa1;
    s16 i;

    sub = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->drawDistance = 0x320;
        gCurrentActor->cullMarginX = 0x14;
        gCurrentActor->cullMarginY = 0x14;
        sub->unkC = 90.0f;
        sub->unk8 = gCurrentActor->y;
        sub->unk14 = (f64)((ActorFB6CSpawnData *)gCurrentActor->spawnData)->unk0 / 200.0;
        sub->unk10 = ((ActorFB6CSpawnData *)gCurrentActor->spawnData)->unk4;
        sub->unk4 = ((f64)sub->unk14 != 0.0) ? (4.71238899230957031 / (f64)sub->unk14) : (f64)0;
        sub->unk1C = ((ActorFB6CSpawnData *)gCurrentActor->spawnData)->unk8;
        sub->unk18 = gCurrentActor->yaw;
        gCurrentActor->floorY = 99999.0f;
        collisionCheckGroundAtPoint(gCurrentActor->x, gCurrentActor->z, &gCurrentActor->floorY);
        if (sub->unk1C == 3) {
            gCurrentActor->interactionType = 2;
        } else {
            gCurrentActor->interactionType = 1;
        }
        if (((ActorFB6CSpawnData *)gCurrentActor->spawnData)->unkC == 1) {
            gCurrentActor->state = 0x14;
            gCurrentActor->unk144 = 1;
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->alpha = 0;
        }
    }
    if (gActorGlobalState.unk200 == 4) {
        sub->unk0 = (Actor *)gActorGlobalState.targetActor;
        gCurrentActor->state = 1;
        gCurrentActor->unk144 = 1;
        gCurrentActor->flags |= 0x400;
        sub->unk1B = 2;
        if (sub->unk1C == 3) {
            sub->unk1A = 1;
        } else {
            sub->unk1A = 2;
        }
    }
    switch (gCurrentActor->state) {
    case 0:
        tagBarrelDespawnOnKongDeselect();
        break;
    case 1:
        gCurrentActor->flags |= 0x8000;
        switch (sub->unk1C) {
        case 0:
        case 4:
            if (sub->unk1C == 0) {
                gCurrentActor->y = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + (sub->unk8 + sub->unk10);
            } else {
                gCurrentActor->y = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + sub->unk8;
            }
            actorAppendCallbackPayloadA70C(gCurrentActor, sub->unk0, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 2, 1);
            sp4E = gCurrentActor->yaw;
            sub->unk4++;
            break;
        case 2:
            gCurrentActor->yaw = (gCurrentActor->yaw + (s32)(sub->unk14 * 200.0f)) & 0xFFF;
            sp4E = (gCurrentActor->yaw + (s32)(sub->unk14 * 200.0f)) & 0xFFF;
            break;
        case 1:
            gCurrentActor->yaw = ((s16)(sinApprox((f32)sub->unk4 * sub->unk14) * ((sub->unk10 * 4096.0f) / 360.0f)) + sub->unk18) & 0xFFF;
            sub->unk4++;
            sp4E = ((s16)(sinApprox((f32)sub->unk4 * sub->unk14) * ((sub->unk10 * 4096.0f) / 360.0f)) + sub->unk18) & 0xFFF;
            break;
        case 3:
            sp4E = gCurrentActor->yaw;
            break;
        }
        sp5C = mathSinF(sp4E) * 50.0f;
        sp58 = mathCosF(sp4E) * 50.0f;
        if (sub->unk1B == 1) {
            controllerAnimLoadStateAsset(gCurrentActor, 0x75);
        }
        if (sub->unk1B) {
            sub->unk1B--;
        }
        if (sub->unk1A) {
            sub->unk1A--;
        }
        if (((D_807FD63C & 0xE000) || sub->unk1C == 3) && sub->unk1A == 0) {
            ActorFB6CCamHolder *temp_s0_2;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x18, 0xFF, 0x7F, 1);
            temp_s0_2 = sub->unk0->customState;
            controllerAnimFreeStateAsset(gCurrentActor);
            if (!(gGlobalCutsceneFlags & 2)) {
                if (sub->unk1C == 3) {
                    var_v0 = 0x64;
                } else {
                    var_v0 = 0x32;
                }
                camSetTargetScaled(temp_s0_2->unk104, sub->unk0, 4, 0x800, var_v0, 0, 0, 0x1E, 0x14, 0x50, 0.3f);
            }
            gActivePlayerActor->yaw = gCurrentActor->yaw;
            gActivePlayerActor->moveYaw = gCurrentActor->yaw;
            actorAppendCallback(sub->unk0, (s32)gCurrentActor, 0x40, 1, 0, 0);
            if (gGlobalCutsceneFlags & 2) {
                var_v0 = 0x1F4;
            } else {
                var_v0 = 0x2BC;
            }
            actorAppendCallbackPayloadAAB8((s32)gCurrentActor, sub->unk0, gCurrentActor->yaw, 0.0f, var_v0);
            actorQueueDelayedCallback(gCurrentActor, gCurrentActor, 0x800, 2, 0, 0, 0xA);
            effectSetMode(2);
            effectCreateAtActorBone(&D_8071FBC8, 1.6f, gCurrentActor, 1, 2);
            gCurrentActor->flags &= ~0x400;
            gCurrentActor->state = 2;
            gCurrentActor->unk155[0] = 0x1E;
        } else {
            sp54 = ((ActorFB6CCamHolder *)sub->unk0->customState)->unk104;
            switch (sub->unk1C) {
            case 0:
                var_fa1 = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + (sub->unk8 + sub->unk10);
                break;
            case 4:
                var_fa1 = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + sub->unk8;
                break;
            default:
                var_fa1 = gCurrentActor->y;
                break;
            }
            if (gGlobalCutsceneFlags & 2) {
                var_v0 = 0;
            } else {
                var_v0 = 1;
            }
            camSetFixedView(
                sp54,
                (f64)gCurrentActor->x - (f64)sp5C / 5.0,
                var_fa1,
                (f64)gCurrentActor->z - (f64)sp58 / 5.0,
                gCurrentActor->x + sp5C,
                var_fa1,
                gCurrentActor->z + sp58,
                var_v0
            );
            if (camIsCutsceneActive() == 0) {
                renderCallbacksRegister(func_806FF01C, gPrimaryPlayerActor, 3);
            }
        }
        break;
    case 2:
        tagBarrelDespawnOnKongDeselect();
        gCurrentActor->unk155[0]--;
        if (gCurrentActor->unk155[0] == 0) {
            gCurrentActor->y = sub->unk8;
            sub->unk4 = ((f64)sub->unk14 != 0.0) ? (4.71238899230957031 / (f64)sub->unk14) : (f64)0;
            gCurrentActor->yaw = sub->unk18;
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
    guRotateF((float (*)[4])&gCurrentActor->unk08[4], sub->unkC, 1.0f, 0, 0.0f);
    actorUpdateModelMatrix(gCurrentActor, 1);
}

typedef struct PlayerStateD580 {
    /* 0x000 */ char unk0[0xCA];
    /* 0x0CA */ u8 unkCA;
    /* 0x0CB */ char unkCB[0x1F0 - 0xCB];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
} PlayerStateD580;

typedef struct PlayerData {
    /* 0x000 */ u8 unk0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 unk21C[0xA4];
    /* 0x2C0 */ u8 unk2C0;
} PlayerData;

extern PlayerData *gPlayerSlots;

void tagBarrelUpdateInteractable(void) {
    s32 one = 1;

    if (one != gPlayerSlots->unk2C0 || (((PlayerStateD580 *)gActivePlayerState)->unk1F4 & 0x40) || gPlayerCharacterId >= 5) {
        gCurrentActor->interactionType = 4;
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->alpha = 0x7F;
    } else if (one == gPlayerSlots->unk2C0 && !(((PlayerStateD580 *)gActivePlayerState)->unk1F0 & 0x40) && gPlayerCharacterId < 5) {
        gCurrentActor->flags |= 0x8000;
        gCurrentActor->interactionType = one;
    }
    if (((PlayerStateD580 *)gActivePlayerState)->unkCA != 0) {
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
    /* 0x00 */ f32 unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
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

typedef struct TagBarrelPlayerState {
    u8 pad0[0xBC];
    s16 unkBC;
    s16 unkBE;
    u8 padC0[0x1A3 - 0xC0];
    u8 unk1A3;
} TagBarrelPlayerState;

extern Vec3f D_8074E7D4;
extern u8 gScreenRenderFlags;
extern u8 gBossFightPhase;
extern u8 D_807FBDC4;
extern u8 D_8071FC58[];
extern s32 effectZSpinMatrixUpdate;


extern s16 D_80750390;
void func_806C7BAC(void *, Actor *); // FAKE: callee prototype steer

void tagBarrelActorUpdate(void) {
    s16 kong;
    s16 pad0;
    f32 coord[3];
    s32 i;
    Vec3f sp90;
    s16 *ptr;
    s16 sp8A;
    f32 dist;
    u8 sp83;
    TagBarrelActorState *sub;
    f32 temp_f;
    u32 val;
    f32 temp_f2;
    s16 angle;
    f32 yOffset;

    sub = (TagBarrelActorState *)gCurrentActor->customState;
    if (gCurrentMap == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    sp90 = D_8074E7D4;
    sp83 = 0;
    if (!(gCurrentActor->flags & 0x10)) {
        temp_f = (f64)gCurrentActor->sub4->scaleX / 0.15;
        gCurrentActor->floorY = gCurrentActor->y;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        gCurrentActor->attachMode = 0;
        gCurrentActor->flags |= 2;
        sub->unk0 = gCurrentActor->y;
        sub->unk4 = 0;
        sub->unk6 = ((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk0;
        sub->unkA = ((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk8;
        sub->unkE = 0;
        if (gCurrentActor->actorType == 0x1C) {
            if (flagGet(func_8073195C(sub->unkA), 0)) {
                actorDespawn(gCurrentActor);
            }
        }
        gCurrentActor->interactionType = 1;
        if (((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk1C == 1.0 || ((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk1C == 2.0) {
            gCurrentActor->state = 0xA;
            sub->unkD = 0x14;
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
        temp_f = (f64)temp_f - 1.0;
        if ((f64)temp_f < 0.0) {
            temp_f = 0.0f;
        }
        val = (u32)(80.0f * temp_f + 20.0f);
        gCurrentActor->cullMarginX = val;
        gCurrentActor->cullMarginY = val;
    }
    for (i = 0; i < D_807FBDC4; i++) {
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
        sub->unk0 = (f64)sub->unk0 + 1.0;
        actorListSetPosByActor(gCurrentActor, gCurrentActor->x, sub->unk0, gCurrentActor->z);
    }
    if (gCurrentActor->state != 0x14 && gCurrentActor->state != 0x15) {
        tagBarrelCheckPlayerCollision();
    }
    if (gCurrentMap == 0xAA) {
        if (gCurrentActor->state != 0xA && gCurrentActor->state != 0xB && gCurrentActor->state != 0xC && gCurrentActor->state != 0x1E) {
            if (((PlayerStateD580 *)gActivePlayerState)->unk1F0 & 0x40) {
                gCurrentActor->unk144 = 2;
                gCurrentActor->flags |= 0x8000;
            } else {
                sp83 = 1;
                gCurrentActor->unk144 = 1;
                gCurrentActor->flags &= ~0x8000;
                gCurrentActor->alpha = 0;
            }
        }
    }
    if ((gCurrentActor->flags & 0x100) && (gCurrentActor->state == 0 || gCurrentActor->state == 1 || (gCurrentActor->state >= 0xA && gCurrentActor->state < 0xD)) && sp83 == 0) {
        dist = (gPlayerSlots->unk218 - gCurrentActor->z) * (gPlayerSlots->unk218 - gCurrentActor->z) +
               ((gPlayerSlots->unk210 - gCurrentActor->x) * (gPlayerSlots->unk210 - gCurrentActor->x) +
                (gPlayerSlots->unk214 - gCurrentActor->y) * (gPlayerSlots->unk214 - gCurrentActor->y));
        if (dist < 40000.0f) {
            temp_f2 = (f64)gCurrentActor->sub4->scaleX / 0.15;
            coord[2] = ((f64)((randomNonNegative() >> 15) % (s32)(30.0f * temp_f2)) - (15.0 * (f64)temp_f2)) + gCurrentActor->x;
            coord[1] = ((f64)((randomNonNegative() >> 15) % (s32)(30.0f * temp_f2)) - (15.0 * (f64)temp_f2)) + gCurrentActor->y;
            coord[0] = ((f64)((randomNonNegative() >> 15) % (s32)(30.0f * temp_f2)) - (15.0 * (f64)temp_f2)) + gCurrentActor->z;
            effectSetDepth(1);
            effectSetFlags(4);
            if (gCurrentActor->state == 0) {
                effectSetCallback(&effectZSpinMatrixUpdate);
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
        if (gBossFightPhase == 4) {
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
            for (i = 0; i < D_807FBDC4; i++) {
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
            gCurrentActor->sub4->scaleX = (f64)gCurrentActor->sub4->scaleX - 0.005;
            gCurrentActor->sub4->scaleY = (f64)gCurrentActor->sub4->scaleY - 0.005;
            gCurrentActor->sub4->scaleZ = (f64)gCurrentActor->sub4->scaleZ - 0.005;
            if ((f64)gCurrentActor->sub4->scaleX < 0.02) {
                gCurrentActor->state = 2;
            }
        }
        break;
    case 2:
        actorSetCustomFloat(gCurrentActor, 7, 1.0f);
        if (!(gScreenRenderFlags & 1) || gCurrentActor->actorType != 0x6B) {
            func_805FF9AC(sub->unk6, 0, 0, 3);
        }
        actorDespawn(gCurrentActor);
        break;
    case 10:
        if (sub->unkD != 0) {
            sub->unkD -= 1;
        }
        if (sub->unkD == 5) {
            gCurrentActor->unk144 = 1;
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x262, 0xFF, 0x64, 1);
        }
        if (sub->unkD == 0) {
            gCurrentActor->sub4->scaleX = (f64)gCurrentActor->sub4->scaleX + 0.005;
            gCurrentActor->sub4->scaleY = (f64)gCurrentActor->sub4->scaleY + 0.005;
            gCurrentActor->sub4->scaleZ = (f64)gCurrentActor->sub4->scaleZ + 0.005;
            if ((f64)gCurrentActor->sub4->scaleX >= 0.15) {
                gCurrentActor->state = 0xB;
            }
            temp_f = (0.15 - (f64)gCurrentActor->sub4->scaleX) / 0.13;
            sub->unk8 = (s32)(temp_f * 400.0f);
            gCurrentActor->yaw += sub->unk8;
        }
        break;
    case 11:
        sub->unkD = 0x32;
        sub->unk8 = 0;
        actorAppendCallback(gPrimaryPlayerActor, (s32)gCurrentActor, 0x40, 1, 0, 0);
        if (((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk18 == 1.0) {
            angle = D_80750390;
        } else {
            angle = 0xB4;
        }
        actorAppendCallbackPayloadAAB8((s32)gCurrentActor, gPrimaryPlayerActor, (s16)((gCurrentActor->yaw + 0x800) & 0xFFF), (f32)angle, 0);
        if (((TagBarrelSpawnParams *)gCurrentActor->spawnData)->unk18 == 1.0) {
            TagBarrelPlayerState *playerState = ((Actor *)gPrimaryPlayerActor)->customState;
            func_806C7BAC(gPrimaryPlayerActor, 0);
            playerState->unk1A3 = 1;
            playerState->unkBC = 0x31;
            playerState->unkBE = -1;
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
        sub->unkD--;
        if (sub->unkD < 0x28) {
            sp90.x = ((f64)(u32)((randomLcgNext() / 1000) % 50) - 25.0) / 5.0;
            sp90.y = ((f64)(u32)((randomLcgNext() / 1000) % 50) - 25.0) / 5.0;
            sp90.z = ((f64)(u32)((randomLcgNext() / 1000) % 50) - 25.0) / 5.0;
        }
        if (sub->unkD == 0) {
            tagBarrelDespawnEffects();
            if (sub->unkA != 0) {
                sp8A = func_8073195C(sub->unkA);
            } else {
                sp8A = -1;
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
                actorSpawnNodeEntryScaled(0x2D, gCurrentActor->x, gCurrentActor->y + yOffset, gCurrentActor->z, 0, kong, sp8A, 0);
                sfxAllocateChannel(0x14, 1.0f);
                actorDespawn(gCurrentActor);
                break;
            }
        }
        break;
    case 20:
        for (i = 0; i < D_807FBDC4; i++) {
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
        sub->unkD--;
        if (sub->unkD == 0) {
            gCurrentActor->unk144 = 2;
            gCurrentActor->state = 0;
        }
        break;
    }
    if (gCurrentActor->state != 0x14) {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
    }
    gCurrentActor->yaw += 0x50;
    gCurrentActor->y = (mathSinF(sub->unk4) * 5.0) + (f64)sub->unk0;
    sub->unk4 += 0x3C;
    guTranslateF((f32 (*)[4])((u8 *)gCurrentActor + 0xC), sp90.x, sp90.y, sp90.z);
    actorUpdateModelMatrix(gCurrentActor, 1);
}


void tagBarrelCheckDespawn(void) {
    TagBarrelState *sub = gCurrentActor->customState;

    if (!(gCurrentActor->flags & 0x10)) {
        if (flagGet(0x302, 0) != 0) {
            actorDespawn(gCurrentActor);
            return;
        }
    }
    tagBarrelActorUpdate();
    if (gCurrentActor->state == 0xC && sub->unkD < 3) {
        flagSet(D_8074E7E0[sub->unkA], 1, 2);
        tagBarrelDespawnEffects();
        actorDespawn(gCurrentActor);
    }
}

void tagBarrelUpdateStateCheck(void) {
    TagBarrelState *sub = gCurrentActor->customState;
    s32 sp28;
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
            sp28 = 0x182;
            break;
        case 0xB6:
            sp28 = 0x183;
            break;
        case 0xB4:
            sp28 = 0x184;
            break;
        case 0xB5:
            sp28 = 0x185;
            break;
        }
        if (flagGet(sp28, 0) != 0) {
            sub->unkC_b = 1;
            sub->unkA = 0;
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
    if (gCurrentActor->state == 0xC && sub->unkD < 3) {
        tagBarrelDespawnEffects();
        actorDespawn(gCurrentActor);
    }
}

typedef struct RocketbarrelState {
    s16 unk0;
    s16 pad2;
    Actor *unk4;
} RocketbarrelState;

typedef struct PlayerStateD580Grab {
    u8 pad0[0x1A3];
    u8 unk1A3;
} PlayerStateD580Grab;

extern u8 gPlayerInventoryTable[][0x5E];
extern s16 D_80750390;

void func_806C7BAC(void *, Actor *); // FAKE: callee prototype steer

void rocketbarrelUpdate(void) {
    RocketbarrelState *var_v1;
    s32 pad[3];

    var_v1 = (RocketbarrelState *)gCurrentActor->customState;
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
    if ((gCurrentActor->state == 0) && (gActorGlobalState.unk200 == 4)) {
        var_v1->unk0 = 0xA;
        gCurrentActor->state = 1;
        gCurrentActor->unk144 = 1;
        var_v1->unk4 = (Actor *)gActorGlobalState.targetActor;
        gCurrentActor->flags |= 0x200000;
        if ((gCurrentMap == 0x11) || (gCurrentMap == 0xC9) || (gCurrentMap == 0xCC)) {
        } else {
            sfxAllocateChannel(0x48, 1.0f);
        }
    }
    switch (gCurrentActor->state) {
    case 0: {
        s32 sp44;
        if (gPlayerCharacterId < 5) {
            sp44 = gPlayerInventoryTable[gPlayerCharacterId][0];
        }
        if (((Actor *)gPrimaryPlayerActor)->actorType == 3 && sp44 >= 2) {
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
        var_v1->unk0--;
        if (var_v1->unk0 == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1C6, 0xFF, 0x7F, 0);
            gCurrentActor->state = 2;
            slotQueueUpdate(5, (gGlobalCutsceneFlags & 2) ? 0 : 1, 0);
        }
        break;
    case 2:
        tagBarrelDespawnEffects();
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->alpha = 0;
        actorAppendCallback(var_v1->unk4, (s32)gCurrentActor, 0x40, 1, 0, 0);
        actorAppendCallbackPayloadAAB8((s32)gCurrentActor, var_v1->unk4, var_v1->unk4->yaw, (f32) D_80750390, 0);
        func_806C7BAC(var_v1->unk4, gCurrentActor);
        ((PlayerStateD580Grab *)gActivePlayerState)->unk1A3 = 1;
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
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    Actor *unk4;
    s16 unk8;
} CannonState;

typedef struct CannonCamHolder {
    u8 pad0[0x104];
    void *unk104;
} CannonCamHolder;

typedef struct CannonPlayerView {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} CannonPlayerView;

extern f32 D_8074E7F4;
extern f32 D_8074E7F8;
extern f32 D_8074E7FC;
extern f32 D_8074E800;
extern f32 D_8074E804;
extern f32 D_8074E808;
extern u8 D_8074E810;
extern s8 D_807FD63E;
extern s8 D_807FD63F;

f32 cosApprox(f32);

void cannonUpdate(void) {
    CannonState *sub = gCurrentActor->customState;
    void *cam;
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
        sub->unk2 = 0;
        sub->unk8 = 0;
        sub->unk1 = 0;
        sub->unk3 = 0;
    }
    if (gCurrentActor->state == 2 || gCurrentActor->state == 3) {
        cam = ((CannonCamHolder *)sub->unk4->customState)->unk104;
        sub->unk8 = sub->unk8 - (f64)D_807FD63E * 0.08 * D_8074E7F8 * 4096.0 / 360.0;
        sub->unk8 = sub->unk8 & 0xFFF;
        sinOff = mathSinF(sub->unk8) * D_8074E7F4;
        cosOff = mathCosF(sub->unk8) * D_8074E7F4;
        D_8074E804 = D_8074E804 - (f64)D_807FD63F * 0.04 * D_8074E800;
        if (D_8074E804 > 50.0) {
            D_8074E804 = 50.0f;
        }
        if (D_8074E804 < -50.0) {
            D_8074E804 = -50.0f;
        }
        x = gCurrentActor->x;
        z = gCurrentActor->z;
        y = gCurrentActor->y + D_8074E7FC;
        camSetFixedView((s32)cam, x, y, z, x + sinOff, y + D_8074E804, gCurrentActor->z + cosOff, 0);
        if (camIsCutsceneActive() == 0) {
            renderCallbacksRegister(func_806FF01C, gPrimaryPlayerActor, 3);
            renderCallbacksRegister(func_806FEF7C, gPrimaryPlayerActor, 3);
        }
        func_8066E6C8(gCurrentActor, 0, 0);
    } else {
        func_8066E6C8(gCurrentActor, 0, 1);
    }
    if (sub->unk2 != 0) {
        renderCallbacksRegister(renderRemainingShotsHUD, sub, 3);
    }
    child = (Actor *)gCurrentActor->parentActor;
    if (child != 0 && sub->unk2 != 0 && child->state == 5 && sub->unk1 == 0) {
        sub->unk1 = 0x1E;
    }
    if (sub->unk1 != 0) {
        sub->unk1--;
        if (sub->unk1 == 0) {
            resetFlag = 1;
        }
    }
    for (i = 0; i < gActorGlobalState.unk254; i++) {
        if (gActorGlobalState.unk258[i] == 1) {
            latchFlag = 1;
            sub->unk3 = 1;
        }
    }
    if (resetFlag != 0 || latchFlag != 0) {
        sub->unk2 = 0;
        if (gCurrentActor->state == 2 || gCurrentActor->state == 3) {
            gCurrentActor->state = 3;
        } else {
            gCurrentActor->state = 0;
            gCurrentActor->unk144 = 2;
        }
        child = (Actor *)gCurrentActor->parentActor;
        if (child != 0) {
            actorDespawn(child);
            gCurrentActor->parentActor = 0;
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
        if (gActorGlobalState.unk200 == 5 && sub->unk3 == 0) {
            gCurrentActor->state = 1;
            gCurrentActor->interactionType = 2;
        }
        break;
    case 1:
        if (gActorGlobalState.unk200 == 4) {
            gCurrentActor->state = 2;
            sub->unk0 = 6;
            sub->unk4 = (Actor *)gActorGlobalState.targetActor;
            if (sub->unk2 == 0) {
                csModelStateSetFirstByte(0x30, 0xA);
                sub->unk2 = 1;
                hudSpawnCountdownTimer(0xC8, 0x20, D_8074E810);
                actorSetStateTwo(gSpawnedActor);
                gCurrentActor->flags |= 0x200000;
            }
            gCurrentActor->flags &= ~4;
            gCurrentActor->unk144 = 1;
        }
        break;
    case 2:
        if ((D_807FD63C & 0x2000) && actorCountOwnedByClass(gCurrentActor, 4, 0) == 0 && sub->unk0 != 0) {
            projectileSetTargetCoords(gCurrentActor->x, gCurrentActor->y + D_8074E7FC, gCurrentActor->z);
            x = ((CannonPlayerView *)gPlayerSlots)->unk230 - ((CannonPlayerView *)gPlayerSlots)->unk218;
            y = ((CannonPlayerView *)gPlayerSlots)->unk228 - ((CannonPlayerView *)gPlayerSlots)->unk210;
            pitch = mathAtan2(((CannonPlayerView *)gPlayerSlots)->unk22C - ((CannonPlayerView *)gPlayerSlots)->unk214, sqrtf(x * x + y * y));
            sinV = sinApprox(pitch) * D_8074E808;
            y = cosApprox(pitch) * D_8074E808;
            projectileSpawnNodeEntry(0x4A, 0, 0.6f, sub->unk8, y, sinV, (s32)gCurrentActor);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x17, 0xFF, 0x7F, 0x19);
            sub->unk0--;
            if (sub->unk0 == 0) {
                gCurrentActor->state = 3;
            }
        }
        break;
    case 3:
        if (actorCountOwnedByClass(gCurrentActor, 4, 0) == 0) {
            actorAppendCallback(sub->unk4, (s32)gCurrentActor, 0x40, 1, 0, 0);
            actorAppendCallbackPayloadA70C(gCurrentActor, sub->unk4, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z - 42.0f, 2, 1);
            sub->unk4->flags &= ~8;
            playerResumeLocomotion(sub->unk4);
            gCurrentActor->flags |= 4;
            gCurrentActor->state = 0;
            gCurrentActor->unk144 = 2;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct TagBarrelOrbitKong {
    u8 pad0[4];
    u16 unk4;
    s8 unk6;
    s8 unk7;
    Actor *unk8[5];
    Actor *unk1C;
    s8 unk20;
} TagBarrelOrbitKong;


void tagBarrelOrbitKongs(void *arg0) {
    TagBarrelOrbitKong *arg = (TagBarrelOrbitKong *)arg0;
    f32 sp70 = gCurrentActor->x;
    f32 sp6C = gCurrentActor->y - 10.0f;
    f32 sp68 = gCurrentActor->z;
    s32 var_s1;
    f32 temp_fs1;
    f32 var_fv0;
    f32 var_fv1;
    s16 temp_s5;
    s16 temp_t0;
    u8 u;
    u8 *var_s3;
    Actor *temp_s2;

    temp_fs1 = (f32)(u32)arg->unk4 / 20.0f;
    temp_s5 = gCurrentActor->yaw;
    temp_s5 = (s16)(s32)(temp_s5 + (819.2 * arg->unk6)) & 0xFFF;
    temp_s5 = (s16)(s32)(temp_s5 - (819.2 * temp_fs1) * arg->unk20) & 0xFFF;
    u = ((u8)(s32)(temp_s5 & 0x7FFF) & 0xFFF); // FAKE: dead narrowing chain burns ugen ring temps (loop-start register ring)
    u = ((u8)((s16)(u & 0xFFF) & 0xFFFF) & 0x7FFF); // FAKE: ring temps
    u = (s32)(((u8)(u & 0xFFFF) & 0xFF) & 0x7FFF); // FAKE: ring temps
    u = (u32)u; // FAKE: ring temps
    var_s1 = 0;
    var_s3 = (u8 *)arg0;
    do {
        temp_s2 = *(Actor **)(var_s3 + 8);
        temp_t0 = (s16)((s32)(4096.0 - (var_s1 * 819.2)) + temp_s5) & 0xFFF;
        temp_s2->x = (mathSinF(temp_t0) * 45.0f) + sp70;
        temp_s2->z = (mathCosF(temp_t0) * 45.0f) + sp68;
        var_s3 += 4;
        temp_s2->y = sp6C;
        if (var_s1 == arg->unk6) {
            var_fv0 = 1.0f - temp_fs1;
        } else if (var_s1 == arg->unk7) {
            var_fv0 = temp_fs1;
        } else {
            var_fv0 = 0;
        }
        var_fv0 = (f64)var_fv0 - 0.6;
        var_s1++;
        var_fv0 = (f64)var_fv0 * 2.5;
        if (var_fv0 < 0) {
            var_fv0 = 0.0f;
        } else {
            if (var_fv0 > 1.0f) {
                var_fv1 = 1.0f;
            } else {
                var_fv1 = var_fv0;
            }
            var_fv0 = var_fv1;
        }
        temp_s2->unk15F = (u32)((12.0f * var_fv0) + 3.0f);
    } while (var_s1 != 5);
}

void actorScriptStartByKongIndex(void *arg0, u16 *arg1, s32 arg2) {
    arg2 = arg2 * 7;
    arg2 += *arg1 - 2;
    actorScriptStart(arg0, gActorScriptIndexTable[arg2], arg2);
}

typedef struct TagBarrelSpawnArgs {
    u8 pad0[6];
    s8 unk6;
    u8 pad7;
    Actor *unk8[5];
    Actor *unk1C;
} TagBarrelSpawnArgs;

typedef struct KongActionEntry {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    u8 unk5;
} KongActionEntry;


void tagBarrelSpawnKongs(TagBarrelSpawnArgs *arg0) {
    s32 i;
    s32 actorType;
    s16 model;
    u16 *temp_s0;
    s32 var_a2;
    s32 flag = 0x40000000;
    actorSpawn(0x136, 0xA8);
    arg0->unk1C = gSpawnedActor;
    gSpawnedActor->x = gCurrentActor->x + mathSinF(gCurrentActor->yaw) * 35.0f;
    gSpawnedActor->y = (gCurrentActor->y - 10.0f) - 2.0f;
    gSpawnedActor->z = gCurrentActor->z + mathCosF(gCurrentActor->yaw) * 35.0f;

    for (i = 0; i < 5; i++) {
        if (flagGet(mapGetConfigValue(gCurrentActor->actorType, i), 0)) {
            actorType = 0x13C;
            model = ((KongActionEntry *)D_8074E814)[i].unk0;
        } else {
            actorType = 0x13D;
            model = 0xD2;
        }
        actorSpawn(actorType, model);
        arg0->unk8[i] = gSpawnedActor;
        gSpawnedActor->yaw = gCurrentActor->yaw;
        gSpawnedActor->flags |= flag;
        if (actorType == 0x13C) {
            temp_s0 = gSpawnedActor->customState;
            *temp_s0 = ((KongActionEntry *)D_8074E814)[i].unk2;
            playerKongStopAudioChannels(gSpawnedActor, *temp_s0);
            var_a2 = (i == arg0->unk6) ? 0x8B : 0x8A;
            actorScriptStartByKongIndex(gSpawnedActor, temp_s0, var_a2);
        } else {
            u8 *temp = gSpawnedActor->customState;
            *temp = i;
        }
    }
    tagBarrelOrbitKongs(arg0);
}

void tagBarrelUpdateSelectedKong(void) {
    ActorAnimLookup sp2C;
    u8 *sp28;

    if (!(gCurrentActor->flags & 0x10)) {
        sp2C = D_8074E834;
        sp28 = gCurrentActor->customState;
        gCurrentActor->flags |= 0x1000;
        animSetLoopLimit(gCurrentActor, 0, 1);
        animSetFinished(gCurrentActor, 0, 1);
        animSetFrameAndSubframe(gCurrentActor, 0, sp2C.arr[*sp28].unk2, 0.0f);
        actorScriptStart(gCurrentActor, 0x329);
    }
    gCurrentActor->tintA = gCurrentActor->unk15F;
    gCurrentActor->yaw += 0x32;
    gCurrentActor->yaw &= 0xFFF;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct ActorExtra3158 {
    u16 unk0;
    u16 pad2;
    void (*unk4)(Actor *, void *, s32 *);
    u8 unk8[1];
} ActorExtra3158;

typedef struct ActorSub4View3158 {
    u8 pad0[0x1C];
    void *unk1C;
} ActorSub4View3158;

typedef struct ActorView3158 {
    u8 pad0[0xC0];
    f32 unkC0;
    u8 padC4[0x146 - 0xC4];
    s16 unk146;
    u8 pad148[0x168 - 0x148];
    s16 unk168;
    u8 pad16A[0x178 - 0x16A];
    void *unk178;
} ActorView3158;



void tagBarrelInteractiveUpdate(void) {
    s32 sp3C;
    ActorExtra3158 *extra;
    u8 *extra8;

    sp3C = 0;
    extra = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x1000;
        ((ActorSub4View3158 *)gCurrentActor->sub4)->unk1C = heapAlloc(0x100);
        heapClearBlock(((ActorSub4View3158 *)gCurrentActor->sub4)->unk1C);
        func_806C8220(0, ((ActorView3158 *)gCurrentActor)->unk178, extra->unk0);
        switch (extra->unk0) {
        case 2:
            extra->unk4 = playerWeaponAimTarget;
            break;
        case 3:
            extra->unk4 = playerWeaponInitCrosshair;
            break;
        case 5:
            extra->unk4 = playerWeaponSpawnProjectile;
            break;
        }
    } else {
        if (extra->unk4 != NULL) {
            extra->unk4(gCurrentActor, ((ActorSub4View3158 *)gCurrentActor->sub4)->unk1C, &sp3C);
        }
    }
    *((u8 *)((ActorSub4View3158 *)gCurrentActor->sub4)->unk1C + sp3C * 8) = 0;
    gCurrentActor->tintA = gCurrentActor->unk15F;
    gCurrentActor->yaw = mathAngleBetweenPoints2D(gPlayerSlots->unk210, gPlayerSlots->unk218, gCurrentActor->x, gCurrentActor->z);
    extra8 = extra->unk8;
    if (func_8072881C(0, extra8) != 0) {
        if (extra->unk0 == 3 || extra->unk0 == 5) {
            func_8072881C(0x81, extra8);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


s32 tagBarrelCheckKongFlag(s32 arg0, s32 arg1) {
    struct KongFlagInfo {
        char unk0[2];
        s16 unk2;
        s32 unk4;
        s32 unk8;
        s32 unkC;
    } sp20;
    struct KongFlagInfo *p = &sp20;
    s32 ret;

    sp20.unk4 = 0;
    switch (gCurrentMap) {
    default:
        return 0;
    case 7:
    case 26:
    case 30:
    case 38:
    case 42:
    case 48:
        sp20.unk8 = func_805FEF10(&sp20);
        if (sp20.unk8 != 0) {
            sp20.unk4 = flagGet(sp20.unk2, 0);
            if (arg1 != 0 && sp20.unk4 == 0) {
                flagSet(sp20.unk2, 1, 0);
                camStartPath(gPrimaryPlayerActor, 0x19, 4);
                gCurrentActor->unk144 = 1;
                gCurrentActor->unk155[0] = 0xB;
            }
        }
        ret = p->unk8 != 0; // FAKE: no explicit return: ret/v0 web, operands read via ilod p
        if (ret != 0) {
            return p->unk4 == 0;
        }
    }
}

typedef struct TagBarrelDataN3 {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ s8 unk6;
    /* 0x07 */ s8 unk7;
    /* 0x08 */ Actor *unk8[5];
    /* 0x1C */ Actor *unk1C;
    /* 0x20 */ s8 unk20;
    /* 0x21 */ u8 pad21;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u8 pad3A[2];
    /* 0x3C */ u32 unk3C;
} TagBarrelDataN3;

typedef struct TagBarrelKongSub {
    u8 pad0[0x104];
    Actor *unk104;
    u8 pad108[0x1F0 - 0x108];
    s32 unk1F0;
} TagBarrelKongSub;

typedef struct TagBarrelActorKong {
    u8 pad0[0x5A];
    s16 unk5A;
    u8 pad5C[0x12C - 0x5C];
    s16 unk12C;
} TagBarrelActorKong;

struct TagBarrelData;
extern s32 D_8074E848[];
extern s32 gGlobalPauseFlags;


void tagBarrelStartSelection(struct TagBarrelData *arg0_in) {
#define arg0 ((TagBarrelDataN3 *)arg0_in)
    TagBarrelActorKong *kong;
    f32 dummy;
    Actor *sp34;
    TagBarrelKongSub *sp30;
    s32 sp28_pad;
    s32 sp28;

    switch (gCurrentActor->unk155[0]) {
    case 0xB:
        if (camIsCutsceneActive() == 0) {
            gCurrentActor->unk144 = 2;
            gCurrentActor->unk155[0] = 0;
        }
        break;
    case 0:
    case 0xA:
        if (gActorGlobalState.unk200 == 4) {
            arg0->unk0 = (Actor *)gActorGlobalState.targetActor;
            arg0->unk0->unk144 = 1;
            ((TagBarrelKongSub *)arg0->unk0->customState)->unk1F0 |= 0x20000000;
            gCurrentActor->unk155[0] = 1;
            arg0->unk4 = 2;
            arg0->unk3C = 0;
        }
        break;
    case 1:
        if (arg0->unk4 != 0) {
            arg0->unk4--;
        } else {
            sp34 = arg0->unk0;
            sp28 = ((TagBarrelActorKong *)sp34)->unk12C;
            sp30 = sp34->customState;
            if (sp28 == -1) {
                sp28 = 0;
            }
            playerRestoreKongState(arg0->unk0, sp30);
            playerRevertAnimalTransformation(arg0->unk0, sp30);
            lightGetColor(&arg0->unk2C, &arg0->unk30, &arg0->unk34, (s16)sp28);
            kong = (TagBarrelActorKong *)sp34;
            lightSetColor(dummy = 1.0f, 1.0f, 1.0f, (s16)sp28);
            gCurrentActor->yaw = arg0->unk22;
            gCurrentActor->unk144 = 1;
            sp28 = kong->unk5A;
            gGlobalPauseFlags &= 0xFFFCFFCF;
            arg0->unk6 = 0;
            if (sp28 != ((KongActionEntry *)D_8074E814)[arg0->unk6].unk2) {
                do {
                    arg0->unk6++;
                } while (sp28 != ((KongActionEntry *)D_8074E814)[arg0->unk6].unk2);
            }
            arg0->unk7 = arg0->unk6;
            if (gCurrentMap != 0x11) {
                sfxAllocateChannel(0x65, 1.0f);
                sfxSetChannelParam(0x65, 0x7E - D_8074E848[arg0->unk6], 1);
            }
            flagSet(mapGetConfigValue(gCurrentActor->actorType, arg0->unk6), 1, 0);
            tagBarrelSpawnKongs((TagBarrelSpawnArgs *)arg0);
            camSaveYaw(sp30->unk104);
            arg0->unk38 = sp34->yaw;
            sp34->yaw = gCurrentActor->yaw;
            eepromSavePlayerData();
            camStartPath(gCurrentActor, 0xE, 0xC);
            func_8061B650(sp30->unk104);
            slotQueueClearAllFlags();
            gCurrentActor->state = 1;
            gCurrentActor->unk155[0] = 0;
        }
        break;
    }
#undef arg0
}

typedef struct TagBarrelInputPad {
    u8 pad0[0x2C];
    u16 unk2C;
    s8 unk2E;
    s8 unk2F;
    u8 unk30;
} TagBarrelInputPad;
extern TagBarrelInputPad gPlayerPadState;

typedef struct TagBarrelPlayerData {
    u8 pad0[0x2E2];
    u16 unk2E2;
} TagBarrelPlayerData;

typedef struct TagBarrelDataN4 {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ s8 unk6;
    /* 0x07 */ s8 unk7;
    /* 0x08 */ Actor *unk8[5];
    /* 0x1C */ Actor *unk1C;
    /* 0x20 */ s8 unk20;
    /* 0x21 */ u8 pad21;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u8 pad3A[2];
    /* 0x3C */ u32 unk3C;
} TagBarrelDataN4;

typedef struct TagBarrelKongSubState {
    u8 pad0[0x8C];
    u8 unk8C;
    u8 pad8D[0x104 - 0x8D];
    Actor *unk104;
    u8 pad108[0x1F0 - 0x108];
    u32 unk1F0;
} TagBarrelKongSubState;

typedef struct TagBarrelOrbitActor {
    u8 pad0[0x12C];
    s16 unk12C;
} TagBarrelOrbitActor;


struct TagBarrelData;

void tagBarrelUpdateSelection(struct TagBarrelData *arg0_in) {
    TagBarrelDataN4 *arg0 = (TagBarrelDataN4 *)arg0_in;
    u16 sp4A;
    s32 var_s0;
    s32 pad2;
    s32 pad[2];
    Actor *sp34;
    TagBarrelKongSubState *sp30;
    s32 light;
    s32 sp28;

    var_s0 = arg0->unk4;
    sp4A = var_s0;
    if (var_s0 != 0) {
        arg0->unk4 = var_s0 - 1;
        tagBarrelOrbitKongs(arg0);
        var_s0 = arg0->unk4;
    }
    arg0->unk3C++;
    if (var_s0 == 0 && hudCanRender() != 0) {
        var_s0 = ((Actor *)arg0->unk8[arg0->unk6])->actorType == 0x13C;
        sp28 = arg0->unk3C >= 9001;
        if (((gPlayerPadState.unk30 >= 0x29) && !sp28) || !var_s0) {
            arg0->unk4 = 20;
            if (((Actor *)arg0->unk8[arg0->unk6])->actorType == 0x13C) {
                actorScriptStartByKongIndex(arg0->unk8[arg0->unk6], (u16 *)((Actor *)arg0->unk8[arg0->unk6])->customState, 0x8C);
            }
            arg0->unk7 = arg0->unk6;
            if (var_s0) {
                arg0->unk20 = (gPlayerPadState.unk2E >= 0) ? 1 : -1;
            }
            arg0->unk6 += arg0->unk20;
            if (arg0->unk6 < 0) {
                arg0->unk6 = 4;
            } else if (arg0->unk6 >= 5) {
                arg0->unk6 = 0;
            }
            if (((Actor *)arg0->unk8[arg0->unk6])->actorType == 0x13C) {
                actorScriptStartByKongIndex(arg0->unk8[arg0->unk6], (u16 *)((Actor *)arg0->unk8[arg0->unk6])->customState, 0x8B);
            }
        } else {
            if (!sp28 && sp4A != 0) {
                sfxSetChannelParam(0x65, 0x7E - D_8074E848[arg0->unk6], 3);
                sfxSetChannelParam(0x65, D_8074E848[arg0->unk6], 2);
                return;
            }
            if (((sp28 && var_s0) || (gPlayerPadState.unk2C & 0xE000)) && screenWipeGetState() == 0) {
                if (var_s0) {
                    sp34 = arg0->unk0;
                    sp30 = sp34->customState;
                    light = ((TagBarrelOrbitActor *)sp34)->unk12C;
                    if (light == -1) {
                        light = 0;
                    }
                    lightSetColor(arg0->unk2C, arg0->unk30, arg0->unk34, (s16)light);
                    gGlobalPauseFlags |= 0x30030;
                    sfxStopChannel(0x48, 0);
                    sfxStopChannel(0x6B, 0);
                    sfxStopChannel(0x49, 0);
                    sfxStopChannel(0x47, 0);
                    sfxStopChannel(0x65, 0);
                    actorDespawn(arg0->unk1C);
                    arg0->unk1C = NULL;
                    for (sp28 = 0; sp28 < 5; sp28++) {
                        actorDespawn(arg0->unk8[sp28]);
                        arg0->unk8[sp28] = NULL;
                    }
                    gCurrentActor->state = 2;
                    gCurrentActor->unk155[0] = 0;
                    arg0->unk4 = 30;
                    sp30->unk1F0 &= ~0x20000000;
                    var_s0 = ((KongActionEntry *)D_8074E814)[arg0->unk6].unk2;
                    playerSetKongByActorType(var_s0);
                    playerKongStopAudioChannels(sp34, var_s0);
                    *(u8 *)((u8 *)sp30 + 0x8C) = 0;
                    sp34->yaw = arg0->unk38;
                    camRestoreYaw(sp30->unk104);
                    camResetPlayer(sp34, 0);
                    screenWipeStart(3);
                    healthRefill(0);
                    ((TagBarrelPlayerData *)gPlayerSlots)->unk2E2 |= 0x11;
                    return;
                }
                sfxPlayOnFreeSlot(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
    }
}

s32 tagBarrelIsKongUnlocked(ActorGroup5 *arg0, s32 arg1) {
    s32 type = arg0->unk8[arg1]->actorType;
    s32 ret = 0;

    if ((type ^ 0x13C) == 0) {
        ret = textTableGetString(2, D_8074E85C[arg1], 1);
    }
    return ret;
}

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern s16 gScreenWidth;
extern s16 gScreenHeight;


Gfx *tagBarrelRenderSelectionHud(Gfx *arg0, Actor *arg1) {
    u8 padF8[0xC];
    f32 spF8;
    s32 pad244;
    f32 spF0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_v0;
    TagBarrelDataN3 *temp_s1;
    s32 spX;
    u8 pad70[0x38];
    s32 sp6C;
    s16 sp44;

    temp_s1 = (TagBarrelDataN3 *)arg1->customState;
    spF0 = (f32)((f64)(gScreenHeight - 0x1E) * 4.0);
    if (arg1->state != 1) {
        return arg0;
    }
    gSPDisplayList(arg0++, &D_1000118);
    gDPSetCombineMode(arg0++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gSPMatrix(arg0++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(arg0++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    sp44 = (s16)(s32)spF0;
    arg0 = renderRotatedSprite(arg0, (u16)(((u32)(gFrameCounter >> 1) % 12) + 0x83), 0, 2, 0x20, 0x10, 0xA0, sp44, 5.0f, 5.0f, 0, 0.0f);
    arg0 = renderRotatedSprite(arg0, (u16)(((u32)(gFrameCounter >> 1) % 12) + 0x83), 0, 2, 0x20, 0x10, (s32)((f64)(gScreenWidth - 0x28) * 4.0), sp44, 5.0f, 5.0f, 0xB4, 0.0f);
    spF8 = (f32)(u32)temp_s1->unk4 * 0.05f;
    sp6C = tagBarrelIsKongUnlocked((ActorGroup5 *)temp_s1, temp_s1->unk6);
    spF0 -= (f32) textGetFontHeight(1) * 1.2f;
    gDPSetCombineLERP(arg0++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    if (sp6C != 0) {
        temp_fv0 = 1.0f - spF8;
        temp_fv1 = temp_fv0 * 0.5f;
        var_fa0 = temp_fv1;
        if (temp_s1->unk20 < 0) {
            var_fa0 = 1.0f - temp_fv1;
        }
        temp_fv1_2 = 2.0f * temp_fv0;
        var_fa0 *= (f32)gScreenWidth * 4.0f;
        if (temp_fv1_2 < 1.0f) {
            var_fv0 = 0.0f;
        } else {
            temp_fv0_2 = temp_fv1_2 - 1.0f;
            if (temp_fv0_2 > 1.0f) {
                var_fv1 = 1.0f;
            } else {
                var_fv1 = temp_fv0_2;
            }
            var_fv0 = var_fv1;
        }
        var_fv0 *= 255.0f;
        gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, (u32)var_fv0);
        arg0 = hudDrawScaledText(arg0, (s16)(s32)var_fa0, (s16)(s32)spF0, 0.6f, sp6C);
    }
    if (temp_s1->unk4 != 0) {
        sp6C = tagBarrelIsKongUnlocked((ActorGroup5 *)temp_s1, temp_s1->unk7);
        if (sp6C != 0) {
            temp_fv0_3 = 0.5f * spF8;
            var_fa0_2 = temp_fv0_3;
            if (temp_s1->unk20 > 0) {
                var_fa0_2 = 1.0f - temp_fv0_3;
            }
            temp_fv0_4 = 2.0f * spF8;
            var_fa0_2 *= (f32)gScreenWidth * 4.0f;
            if (temp_fv0_4 < 1.0f) {
                var_fv0_2 = 0.0f;
            } else {
                temp_fa1 = temp_fv0_4 - 1.0f;
                if (temp_fa1 > 1.0f) {
                    var_fv1 = 1.0f;
                } else {
                    var_fv1 = temp_fa1;
                }
                var_fv0_2 = var_fv1;
            }
            var_fv0_2 *= 255.0f;
            gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, (u32)var_fv0_2);
            arg0 = hudDrawScaledText(arg0, (s16)(s32)var_fa0_2, (s16)(s32)spF0, 0.6f, sp6C);
        }
    }
    return arg0;
}

void tagBarrelInitUnlockedKongs(Actor *arg0) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (flagGet(mapGetConfigValue(arg0->actorType, i), 0)) {
            func_8068A764(arg0, D_8074E814[i].unk4);
        }
    }
}

typedef struct TagBarrelData {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ s8 unk6;
    /* 0x07 */ s8 unk7;
    /* 0x08 */ Actor *unk8[5];
    /* 0x1C */ Actor *unk1C;
    /* 0x20 */ s8 unk20;
    /* 0x21 */ u8 pad21;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u8 pad3A[2];
    /* 0x3C */ u32 unk3C;
} TagBarrelData;

extern u8 D_8071FC8C[];

void tagBarrelUpdate(void) {
    Actor *actor = gCurrentActor;
    TagBarrelData *sub = actor->customState;

    if (!(actor->flags & 0x10)) {
        sub->unk22 = actor->yaw;
        sub->unk24 = gCurrentActor->y;
        *(s16 *)&gCurrentActor->unk145[1] = 0;
        gCurrentActor->eyeHeight = 0;
        effectSetMode(2);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetMaxDistance(0x3E8);
        effectSetFlags(4);
        actor = gCurrentActor;
        effectCreateAtPosition(&D_8071FC8C, 1.3f, actor->x, (f32)((f64)actor->y + 13.0), actor->z);
        if (mapIsBossArena()) {
            gCurrentActor->drawDistance = 0x7D0;
        } else {
            gCurrentActor->drawDistance = 0x15E;
        }
        actor = gCurrentActor;
        actor->floorY = actor->y;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        gCurrentActor->attachMode = 0;
        actor = gCurrentActor;
        actor->flags |= 2;
        actor = gCurrentActor;
    }
    tagBarrelInitUnlockedKongs(actor);
    tagBarrelUpdateInteractable();
    actorUpdatePrevContactFlags(gCurrentActor);
    actor = gCurrentActor;
    switch (actor->state) {
    case 0:
        if (sub->unk4 != 0) {
            sub->unk4--;
            if (sub->unk4 == 0) {
                gCurrentActor->unk144 = 2;
            }
        } else {
            tagBarrelStartSelection(sub);
        }
        actor = gCurrentActor;
        if (actor->unk155[0] == 0xA) {
            if (((Actor *)gPrimaryPlayerActor)->contactFlags & 4 || playerSpawnAllPlayers() != 0) {
                actor = gCurrentActor;
                actor->unk155[0] = 0;
            } else if (((Actor *)gPrimaryPlayerActor)->attachMode != 1 && (((Actor *)gPrimaryPlayerActor)->contactFlags & ((Actor *)gPrimaryPlayerActor)->prevContactFlags & 1)) {
                tagBarrelCheckKongFlag(((Actor *)gPrimaryPlayerActor)->actorType, 1);
            }
        }
        actor = gCurrentActor;
        break;
    case 1:
        tagBarrelUpdateSelection(sub);
        renderCallbacksRegister(tagBarrelRenderSelectionHud, gCurrentActor, 3);
        actor = gCurrentActor;
        break;
    case 2:
        if (sub->unk4 != 0) {
            sub->unk4--;
        } else {
            actorAppendCallbackPayloadAAB8((s32)actor, sub->unk0, sub->unk38, 180.0f, 0x46);
            actorAppendCallback(sub->unk0, (s32)gCurrentActor, 0x40, 1, 0, 0);
            slotQueuePopActiveMask();
            gCurrentActor->state = 0;
            gCurrentActor->unk155[0] = 0;
            if (tagBarrelCheckKongFlag(((Actor *)gPrimaryPlayerActor)->actorType, 0) != 0) {
                gCurrentActor->unk155[0] = 0xA;
            }
            sub->unk4 = 0x1E;
        }
        actor = gCurrentActor;
        break;
    }
    billboardSubmit(actor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x64, 0x78, 0, 1.0f);
    actor = gCurrentActor;
    if (actor->state != 1) {
        actor->yaw += 0x32;
        actor = gCurrentActor;
        actor->yaw &= 0xFFF;
        gCurrentActor->y = mathSinF(sub->unk28) * 5.0f + sub->unk24;
        sub->unk28 += 0x32;
        sub->unk28 &= 0xFFF;
        actor = gCurrentActor;
    }
    actorUpdateModelMatrix(actor, 0);
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
