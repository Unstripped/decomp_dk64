#include "common.h"
#include "actor.h"
#include "map.h"
#include "proto/global/15050.h"
#include "proto/global/17B90.h"
#include "proto/global/684C0.h"
#include "proto/global/7CA80.h"

typedef struct TriggerZoneData {
    s16 xMin;
    s16 yMin;
    s16 zMin;
    s16 xMax;
    s16 yMax;
    s16 zMax;
    s16 planeOffset;
    u8 axisFlags;
    u8 alpha;
} TriggerZoneData;

typedef struct TriggerZoneSubNode {
    Actor *actor;
    s32 instanceId;
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

void triggerZoneInit(MapFileHeader *header) {
    s32 i;
    TriggerZoneNode **link;
    s32 zoneCount;
    TriggerZoneData *zones;
    TriggerZoneNode *newNode;

    link = &D_807F9410;
    zoneCount = *(s32 *)(header->unk54 + (u8 *)header);
    zones = (TriggerZoneData *)((s32 *)(header->unk54 + (u8 *)header) + 1);
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

void triggerZoneCheckEntry(Actor *actor) {
    TriggerZoneNode *node;
    TriggerZoneSubNode **subLink;
    TriggerZoneSubNode *subNode;
    TriggerZoneSubNode *newNode;
    for (node = D_807F9410; node != NULL; node = node->next) {
        if ((f32)node->zone->xMin <= actor->x &&
            (f32)node->zone->yMin <= actor->y &&
            (f32)node->zone->zMin <= actor->z &&
            actor->x <= (f32)node->zone->xMax &&
            actor->y <= (f32)node->zone->yMax &&
            actor->z <= (f32)node->zone->zMax) {
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
                newNode->instanceId = actor->instanceId;
                newNode->spawnedActor = gSpawnedActor;
                newNode->next = NULL;
            }
        }
    }
}


s32 triggerZoneContainsActor(Actor *actor, TriggerZoneSubNode *subNode) {
    while (subNode != NULL) {
        if (actor == subNode->actor && subNode->instanceId == actor->instanceId) {
            return 1;
        }
        subNode = subNode->next;
    }
    return 0;
}

void triggerZoneSpawnTrigger(Actor *actor, TriggerZoneData *zone) {
    MirrorActorState *spawnState;

    actorSpawn(0x7B, controllerLookupStateByHash(actor));
    gSpawnedActor->parentActor = actor;
    spawnState = gSpawnedActor->customState;
    spawnState->axisFlags = zone->axisFlags;
    spawnState->planeOffset = zone->planeOffset;
    spawnState->alpha = zone->alpha;
    actor->unk156++;
}


void triggerZoneUpdate(void) {
    TriggerZoneNode *node;
    TriggerZoneSubNode **subListPtr;
    TriggerZoneSubNode *subNode;
    TriggerZoneSubNode *toFree;
    Actor *actor;
    TriggerZoneData *zone;
    for (node = D_807F9410; node != NULL; node = node->next) {
        for (subListPtr = &node->subList, subNode = *subListPtr; subNode != NULL; ) {
            zone = node->zone;
            actor = subNode->actor;
            if (actor->x < (f32)zone->xMin ||
                actor->y < (f32)zone->yMin ||
                actor->z < (f32)zone->zMin ||
                (f32)zone->xMax < actor->x ||
                (f32)zone->yMax < actor->y ||
                (f32)zone->zMax < actor->z) {
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
