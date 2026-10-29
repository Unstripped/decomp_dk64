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
extern Actor *D_807FBB44;
void *func_80610FE8(s32);
s32 triggerZoneContainsActor();
void triggerZoneSpawnTrigger();

void triggerZoneInit(TriggerZoneActor *arg0) {
    s32 var_s0;
    TriggerZoneNode **var_s1;
    s32 temp_s2;
    TriggerZoneData *temp_s3;
    TriggerZoneNode *temp_v0_2;

    var_s1 = &D_807F9410;
    temp_s2 = *(s32 *)(arg0->unk54 + (u8 *)arg0);
    temp_s3 = (TriggerZoneData *)((s32 *)(arg0->unk54 + (u8 *)arg0) + 1);
    *var_s1 = NULL;
    for (var_s0 = 0; var_s0 < temp_s2; var_s0++) {
        temp_v0_2 = func_80610FE8(sizeof(TriggerZoneNode));
        *var_s1 = temp_v0_2;
        var_s1 = &temp_v0_2->next;
        temp_v0_2->zone = &temp_s3[var_s0];
        temp_v0_2->subList = NULL;
        temp_v0_2->next = NULL;
    }
}

void triggerZoneCheckEntry(TriggerZoneActor *arg0) {
    TriggerZoneNode *node;
    TriggerZoneSubNode **var_s0;
    TriggerZoneSubNode *subNode;
    TriggerZoneSubNode *newNode;
    for (node = D_807F9410; node != NULL; node = node->next) {
        if ((f32)node->zone->xMin <= arg0->unk7C &&
            (f32)node->zone->yMin <= arg0->unk80 &&
            (f32)node->zone->zMin <= arg0->unk84 &&
            arg0->unk7C <= (f32)node->zone->xMax &&
            arg0->unk80 <= (f32)node->zone->yMax &&
            arg0->unk84 <= (f32)node->zone->zMax) {
            if (triggerZoneContainsActor(arg0, node->subList) == 0) {
                triggerZoneSpawnTrigger(arg0, node->zone);
                var_s0 = &node->subList;
                subNode = *var_s0;
                if (subNode != NULL) {
                    do {
                        var_s0 = &subNode->next;
                        subNode = subNode->next;
                    } while (subNode != NULL);
                }
                newNode = func_80610FE8(sizeof(TriggerZoneSubNode));
                *var_s0 = newNode;
                newNode->actor = arg0;
                newNode->unk4 = arg0->unk54;
                newNode->spawnedActor = D_807FBB44;
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

s32 func_80613448(TriggerZoneActor *);
s32 actorSpawn(s32, s32);

s32 triggerZoneContainsActor(TriggerZoneActor *arg0, TriggerZoneSubNode *arg1) {
    while (arg1 != NULL) {
        if (arg0 == arg1->actor && arg1->unk4 == arg0->unk54) {
            return 1;
        }
        arg1 = arg1->next;
    }
    return 0;
}

void triggerZoneSpawnTrigger(TriggerZoneActor *arg0, TriggerZoneData *arg1) {
    TriggerSpawnSub174 *temp_v1;

    actorSpawn(0x7B, func_80613448(arg0));
    D_807FBB44->unk11C = (s32)arg0;
    temp_v1 = D_807FBB44->unk174;
    temp_v1->unkE = arg1->unkE;
    temp_v1->unkC = arg1->unkC;
    temp_v1->unkF = arg1->unkF;
    arg0->unk156++;
}

void actorDespawn(Actor *);
void heapFree(void *);

void triggerZoneUpdate(void) {
    TriggerZoneNode *node;
    TriggerZoneSubNode **subListPtr;
    TriggerZoneSubNode *subNode;
    TriggerZoneSubNode *temp_a0;
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
                temp_a0 = subNode;
                *subListPtr = subNode->next;
                subNode = subNode->next;
                heapFree(temp_a0);
            } else {
                subListPtr = &subNode->next;
                subNode = subNode->next;
            }
        }
    }
}

void func_80663BE8(Actor *arg0) {
    TriggerZoneNode *node;
    TriggerZoneSubNode **subListPtr;
    TriggerZoneSubNode *subNode;
    Actor *spawned;

    for (node = D_807F9410; node != NULL; node = node->next) {
        for (subListPtr = &node->subList, subNode = *subListPtr; subNode != NULL; ) {
            spawned = subNode->spawnedActor;
            if (arg0 == spawned) {
                *subListPtr = subNode->next;
                heapFree(subNode);
                return;
            }
            subListPtr = &subNode->next;
            subNode = subNode->next;
        }
    }
}
