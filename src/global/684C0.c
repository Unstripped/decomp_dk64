#include "common.h"
#include "actor.h"

typedef struct TriggerZoneActor {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[0x24];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x156 - 0x88];
    u8 unk156;
} TriggerZoneActor;

typedef struct TriggerZoneData {
    s16 xMin;
    s16 yMin;
    s16 zMin;
    s16 xMax;
    s16 yMax;
    s16 zMax;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} TriggerZoneData;

typedef struct TriggerZoneSubNode {
    TriggerZoneActor *actor;
    s32 unk4;
    struct Actor *spawnedActor;
    struct TriggerZoneSubNode *next;
} TriggerZoneSubNode;

typedef struct TriggerZoneNode {
    TriggerZoneData *zone;
    TriggerZoneSubNode *subList;
    struct TriggerZoneNode *next;
} TriggerZoneNode;

extern TriggerZoneNode *D_807F9410;
extern Actor *gSpawnedActor;
void *heapAlloc(s32);
s32 triggerZoneContainsActor();
void triggerZoneSpawnTrigger();

void triggerZoneInit(TriggerZoneActor *actor) {
    s32 i;
    TriggerZoneNode **link;
    s32 zoneCount;
    TriggerZoneData *zones;
    TriggerZoneNode *newNode;

    link = &D_807F9410;
    zoneCount = *(s32 *)(actor->unk54 + (u8 *)actor);
    zones = (TriggerZoneData *)((s32 *)(actor->unk54 + (u8 *)actor) + 1);
    *link = NULL;
    for (i = 0; i < zoneCount; i++) {
        newNode = heapAlloc(sizeof(TriggerZoneNode));
        *link = newNode;
        link = &newNode->next;
        newNode->zone = &zones[i];
        newNode->subList = NULL;
        newNode->next = NULL;
    }
}

void triggerZoneCheckEntry(TriggerZoneActor *actor) {
    TriggerZoneNode *node;
    TriggerZoneSubNode **subLink;
    TriggerZoneSubNode *subNode;
    TriggerZoneSubNode *newNode;
    for (node = D_807F9410; node != NULL; node = node->next) {
        if ((f32)node->zone->xMin <= actor->unk7C &&
            (f32)node->zone->yMin <= actor->unk80 &&
            (f32)node->zone->zMin <= actor->unk84 &&
            actor->unk7C <= (f32)node->zone->xMax &&
            actor->unk80 <= (f32)node->zone->yMax &&
            actor->unk84 <= (f32)node->zone->zMax) {
            if (triggerZoneContainsActor(actor, node->subList) == 0) {
                triggerZoneSpawnTrigger(actor, node->zone);
                subLink = &node->subList;
                subNode = *subLink;
                if (subNode != NULL) {
                    do {
                        subLink = &subNode->next;
                        subNode = subNode->next;
                    } while (subNode != NULL);
                }
                newNode = heapAlloc(sizeof(TriggerZoneSubNode));
                *subLink = newNode;
                newNode->actor = actor;
                newNode->unk4 = actor->unk54;
                newNode->spawnedActor = gSpawnedActor;
                newNode->next = NULL;
            }
        }
    }
}

typedef struct TriggerSpawnSub174 {
    u8 pad0[0xC];
    s16 unkC;
    u8 unkE;
    u8 unkF;
} TriggerSpawnSub174;

s32 controllerLookupStateByHash(TriggerZoneActor *);
s32 actorSpawn(s32, s32);

s32 triggerZoneContainsActor(TriggerZoneActor *actor, TriggerZoneSubNode *subNode) {
    while (subNode != NULL) {
        if (actor == subNode->actor && subNode->unk4 == actor->unk54) {
            return 1;
        }
        subNode = subNode->next;
    }
    return 0;
}

void triggerZoneSpawnTrigger(TriggerZoneActor *actor, TriggerZoneData *zone) {
    TriggerSpawnSub174 *spawnState;

    actorSpawn(0x7B, controllerLookupStateByHash(actor));
    gSpawnedActor->parentActor = (s32)actor;
    spawnState = gSpawnedActor->customState;
    spawnState->unkE = zone->unkE;
    spawnState->unkC = zone->unkC;
    spawnState->unkF = zone->unkF;
    actor->unk156++;
}

void actorDespawn(Actor *);
void heapFree(void *);

void triggerZoneUpdate(void) {
    TriggerZoneNode *node;
    TriggerZoneSubNode **subListPtr;
    TriggerZoneSubNode *subNode;
    TriggerZoneSubNode *toFree;
    TriggerZoneActor *actor;
    TriggerZoneData *zone;
    for (node = D_807F9410; node != NULL; node = node->next) {
        for (subListPtr = &node->subList, subNode = *subListPtr; subNode != NULL; ) {
            zone = node->zone;
            actor = subNode->actor;
            if (actor->unk7C < (f32)zone->xMin ||
                actor->unk80 < (f32)zone->yMin ||
                actor->unk84 < (f32)zone->zMin ||
                (f32)zone->xMax < actor->unk7C ||
                (f32)zone->yMax < actor->unk80 ||
                (f32)zone->zMax < actor->unk84) {
                actor->unk156--;
                actorDespawn(subNode->spawnedActor);
                toFree = subNode;
                *subListPtr = subNode->next;
                subNode = subNode->next;
                heapFree(toFree);
            } else {
                subListPtr = &subNode->next;
                subNode = subNode->next;
            }
        }
    }
}

void triggerZoneRemoveSpawned(Actor *spawnedActor) {
    TriggerZoneNode *node;
    TriggerZoneSubNode **subListPtr;
    TriggerZoneSubNode *subNode;
    Actor *spawned;

    for (node = D_807F9410; node != NULL; node = node->next) {
        for (subListPtr = &node->subList, subNode = *subListPtr; subNode != NULL; ) {
            spawned = subNode->spawnedActor;
            if (spawnedActor == spawned) {
                *subListPtr = subNode->next;
                heapFree(subNode);
                return;
            }
            subListPtr = &subNode->next;
            subNode = subNode->next;
        }
    }
}
