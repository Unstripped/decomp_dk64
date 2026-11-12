#include "common.h"
#include "actor.h"
#include "proto/global/1332B0.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/6AD90.h"
#include "proto/global/7CA80.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern void *gPlayerSlots;

u8 func_8072E5B0(void) {
    Actor *player = gPrimaryPlayerActor;

    return !(player->contactFlags & 1) && !(player->attachMode == 1) && !(player->state == 0x63);
}

// One action a volume trigger fires: an 8-byte callback payload sent to the actor of a hook.
typedef struct VolumeTriggerAction {
    /* 0x0 */ s16 hookIndex; // index into D_807557A0
    /* 0x2 */ u8 payload[8];
} VolumeTriggerAction; // size = 0xA

// Volume trigger record as stored in the map asset (table 0x12): a vertical cylinder.
typedef struct VolumeTriggerDef {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 radius;
    /* 0x08 */ s16 height; // -1: no vertical bound
    /* 0x0A */ s16 id; // also the flag index passed to flagTryTriggerOnce
    /* 0x0C */ u8 mode; // 0: on entry, 1: on exit, 2: while inside
    /* 0x0D */ u8 startEnabled;
    /* 0x0E */ u8 actionCount;
    /* 0x0F */ u8 padF;
    /* 0x10 */ VolumeTriggerAction actions[4];
} VolumeTriggerDef; // size = 0x38

typedef struct VolumeTrigger {
    /* 0x00 */ VolumeTriggerDef def;
    /* 0x38 */ u8 wasOutside;
    /* 0x39 */ u8 enabled;
} VolumeTrigger; // size = 0x3A

typedef struct {
    /* 0x00 */ s16 count;
    /* 0x04 */ VolumeTrigger *entries;
} VolumeTriggerTable;

extern VolumeTriggerTable *D_80755A14;

void volumeTriggerTableLoad(s16 *data) {
    VolumeTriggerDef *src;
    VolumeTrigger *e;
    s16 i;

    D_80755A14->count = 0;
    D_80755A14->entries = NULL;
    if (data != NULL) {
        src = (VolumeTriggerDef *)(data + 1);
        D_80755A14->count = *data;
        for (i = 0; i < D_80755A14->count; i++, src++) {
            if (i == 0) {
                D_80755A14->entries = heapAlloc(D_80755A14->count * sizeof(VolumeTrigger));
                e = D_80755A14->entries;
            } else {
                e++;
            }
            e->def = *src;
            e->wasOutside = 0;
            e->enabled = e->def.startEnabled;
        }
    }
}

// Receiver of the actions of a volume trigger: an actor found by type at map load.
typedef struct {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ u16 actorType;
    /* 0x04 */ u8 pad4[3];
    /* 0x07 */ u8 subtype; // callback subtype
    /* 0x08 */ Actor *actor;
    /* 0x0C */ s32 (*condition)(void); // NULL: always fire
} VolumeTriggerHook; // size = 0x10

extern VolumeTriggerHook D_807557A0[];

void volumeTriggerTableInit(s32 mapId) {
    VolumeTriggerHook *hook;
    s32 i;
    s32 hookCount = 0x27;
    s32 pad[2];
    Actor *actor;
    void *buf;

    buf = assetLoad(0x12, mapId, 1, 0);
    volumeTriggerTableLoad(buf);
    if (buf != NULL) {
        assetFreeBuffer(buf, 0xC1, 0x3D);
    }
    hook = D_807557A0;
    for (i = 0; i < hookCount; i++, hook++) {
        actorFindActiveByType(hook->actorType, &actor);
        hook->actor = actor;
    }
}

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

s32 actorFindActiveByType(s16 actorType, Actor **outActor) {
    s32 found = 0;
    s32 i = 0;
    Actor *actor;

    while (!found && i < gActiveActorCount) {
        actor = gActiveActors[i].actor;
        if (actor->actorType == actorType) {
            found = 1;
        } else {
            i++;
        }
    }
    *outActor = actor;
    return found;
}

extern s16 D_807FDCB8;
extern s16 D_807FDCBA;
extern s16 D_807FDCBC;

void volumeTriggerUpdateAll(void) {
    s32 pad[2];
    s32 i;
    VolumeTrigger *e;
    s16 *idPtr;
    s32 j;
    s32 delayed;
    s32 k;
    VolumeTriggerAction *action;

    for (k = 0; k < gActorGlobalState.unk254; k++) {
        idPtr = gActorGlobalState.unk278[k];
        switch (gActorGlobalState.unk258[k]) {
            case 1:
                volumeTriggerSetEnabled(*idPtr, 1);
                break;
            case 2:
                volumeTriggerSetEnabled(*idPtr, 0);
                break;
        }
    }
    e = D_80755A14->entries;
    for (i = 0; i < D_80755A14->count; i++, e++) {
        if (volumeTriggerUpdate(e)) {
            for (j = 0; j < e->def.actionCount; j++) {
                action = &e->def.actions[j];
                if (D_807557A0[e->def.actions[j].hookIndex].condition == NULL || D_807557A0[e->def.actions[j].hookIndex].condition()) { // FAKE: condition reads hookIndex via e->def.actions[j], the body via action: keeps the hook address recomputed after the call (no CSE)
                    delayed = D_807557A0[action->hookIndex].actorType == 0xA ? 1 : 0;
                    actorAppendCallbackMemcpy8(gCurrentActor, D_807557A0[action->hookIndex].actor, 0x01000000, D_807557A0[action->hookIndex].subtype, e->def.actions[j].payload, delayed);
                    D_807FDCB8 = e->def.x;
                    D_807FDCBA = e->def.y;
                    D_807FDCBC = e->def.z;
                }
            }
        }
    }
}

typedef struct {
    /* 0x0 */ u8 active;
    /* 0x4 */ Actor *actor;
    /* 0x8 */ u8 pad8[0x2E8];
} PlayerSlot; // size = 0x2F0

extern u8 gPlayerCount;
extern s16 gCurrentLevelIndex;

s32 volumeTriggerUpdate(VolumeTrigger *trigger) {
    u8 inside = 0;
    f32 distSq;
    u8 result = 0;
    PlayerSlot *player;
    u8 i;

    for (i = 0; i < gPlayerCount; i++) {
        player = &((PlayerSlot *)gPlayerSlots)[i];
        if (player->active) {
            if (trigger->def.height == -1 || ((f32)trigger->def.y <= player->actor->y && player->actor->y < (f32)(trigger->def.y + trigger->def.height))) {
                distSq = ((f32)trigger->def.z - player->actor->z) * ((f32)trigger->def.z - player->actor->z) + ((f32)trigger->def.x - player->actor->x) * ((f32)trigger->def.x - player->actor->x);
                if (distSq < (f32)(trigger->def.radius * trigger->def.radius)) {
                    inside = 1;
                }
            }
        }
    }
    switch (trigger->def.mode) {
        case 0:
            if (inside && trigger->wasOutside == 1 && trigger->enabled) {
                result = 1;
            }
            break;
        case 1:
            if (!inside && !trigger->wasOutside && trigger->enabled) {
                result = 1;
            }
            break;
        case 2:
            if (inside && trigger->enabled) {
                result = 1;
            }
            break;
    }
    if (result && !flagTryTriggerOnce(gCurrentLevelIndex, trigger->def.id)) {
        result = 0;
    }
    if (inside) {
        trigger->wasOutside = 0;
    } else {
        trigger->wasOutside = 1;
    }
    return result;
}

void volumeTriggerSetEnabled(s32 triggerId, u8 enabled) {
    s32 found = 0;
    VolumeTrigger *e = D_80755A14->entries;
    s32 i;

    for (i = 0; i < D_80755A14->count && !found; i++, e++) {
        if (triggerId == e->def.id) {
            e->enabled = enabled;
            found = 1;
        }
    }
}

void volumeTriggerSetPosition(s32 triggerId, s16 x, s16 y, s16 z) {
    s32 found = 0;
    VolumeTrigger *e = D_80755A14->entries;
    s32 i;

    for (i = 0; i < D_80755A14->count && !found; i++, e++) {
        if (triggerId == e->def.id) {
            e->def.x = x;
            e->def.y = y;
            e->def.z = z;
            found = 1;
        }
    }
}
