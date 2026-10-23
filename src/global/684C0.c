#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/684C0/func_806637C0.s")

typedef struct R2F684C0_Actor {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[0x24];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x156 - 0x88];
    u8 unk156;
} R2F684C0_Actor;

typedef struct R2F684C0_Zone {
    s16 xMin;
    s16 yMin;
    s16 zMin;
    s16 xMax;
    s16 yMax;
    s16 zMax;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} R2F684C0_Zone;

typedef struct R2F684C0_SubNode {
    R2F684C0_Actor *actor;
    s32 unk4;
    struct Actor *spawnedActor;
    struct R2F684C0_SubNode *next;
} R2F684C0_SubNode;

typedef struct R2F684C0_ZoneNode {
    R2F684C0_Zone *zone;
    R2F684C0_SubNode *subList;
    struct R2F684C0_ZoneNode *next;
} R2F684C0_ZoneNode;

extern R2F684C0_ZoneNode *D_807F9410;
extern Actor *D_807FBB44;
void *func_80610FE8(s32);
s32 func_806639CC();
void func_80663A0C();

void func_80663844(R2F684C0_Actor *arg0) {
    R2F684C0_ZoneNode *node;
    R2F684C0_SubNode **var_s0;
    R2F684C0_SubNode *subNode;
    R2F684C0_SubNode *newNode;

    for (node = D_807F9410; node != NULL; node = node->next) {
        if ((f32)node->zone->xMin <= arg0->unk7C &&
            (f32)node->zone->yMin <= arg0->unk80 &&
            (f32)node->zone->zMin <= arg0->unk84 &&
            arg0->unk7C <= (f32)node->zone->xMax &&
            arg0->unk80 <= (f32)node->zone->yMax &&
            arg0->unk84 <= (f32)node->zone->zMax) {
            if (func_806639CC(arg0, node->subList) == 0) {
                func_80663A0C(arg0, node->zone);
                var_s0 = &node->subList;
                subNode = *var_s0;
                if (subNode != NULL) {
                    do {
                        var_s0 = &subNode->next;
                        subNode = subNode->next;
                    } while (subNode != NULL);
                }
                newNode = func_80610FE8(sizeof(R2F684C0_SubNode));
                *var_s0 = newNode;
                newNode->actor = arg0;
                newNode->unk4 = arg0->unk54;
                newNode->spawnedActor = D_807FBB44;
                newNode->next = NULL;
            }
        }
    }
}

typedef struct R1F67890_Actor {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[0x156 - 0x58];
    u8 unk156;
} R1F67890_Actor;

typedef struct R1F67890_Zone {
    s16 xMin;
    s16 yMin;
    s16 zMin;
    s16 xMax;
    s16 yMax;
    s16 zMax;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} R1F67890_Zone;

typedef struct R1F67890_Sub174 {
    u8 pad0[0xC];
    s16 unkC;
    u8 unkE;
    u8 unkF;
} R1F67890_Sub174;

typedef struct R1F67890_SubNode {
    R1F67890_Actor *actor;
    s32 unk4;
    struct Actor *spawnedActor;
    struct R1F67890_SubNode *next;
} R1F67890_SubNode;

s32 func_80613448(R1F67890_Actor *);
s32 actorSpawn(s32, s32);

s32 func_806639CC(R1F67890_Actor *arg0, R1F67890_SubNode *arg1) {
    while (arg1 != NULL) {
        if (arg0 == arg1->actor && arg1->unk4 == arg0->unk54) {
            return 1;
        }
        arg1 = arg1->next;
    }
    return 0;
}

void func_80663A0C(R1F67890_Actor *arg0, R1F67890_Zone *arg1) {
    R1F67890_Sub174 *temp_v1;

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

void func_80663A80(void) {
    R2F684C0_ZoneNode *node;
    R2F684C0_SubNode **subListPtr;
    R2F684C0_SubNode *subNode;
    R2F684C0_SubNode *temp_a0;
    R2F684C0_Actor *actor;
    R2F684C0_Zone *zone;

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/684C0/func_80663BE8.s")
