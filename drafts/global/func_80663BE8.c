// func_80663BE8 (src/global/684C0.c): 100% logic match, regalloc only: a2/v1 swap on var_a2 and v1/v0 on var_v1
#include "common.h"
#include "actor.h"

typedef struct R1F67890_Actor {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[0x156 - 0x58];
    u8 unk156;
} R1F67890_Actor;

typedef struct R1F67890_SubNode {
    R1F67890_Actor *actor;
    s32 unk4;
    struct Actor *spawnedActor;
    struct R1F67890_SubNode *next;
} R1F67890_SubNode;

typedef struct R1F67890_ZoneNode {
    void *unk0;
    R1F67890_SubNode *subList;
    struct R1F67890_ZoneNode *next;
} R1F67890_ZoneNode;

extern R1F67890_ZoneNode *D_807F9410;
void heapFree(void *);

void func_80663BE8(Actor *arg0) {
    R1F67890_ZoneNode *var_a2;
    R1F67890_SubNode **var_v1;
    R1F67890_SubNode *var_a0;

    for (var_a2 = D_807F9410; var_a2 != NULL; var_a2 = var_a2->next) {
        for (var_v1 = &var_a2->subList, var_a0 = *var_v1; var_a0 != NULL; ) {
            if (arg0 == var_a0->spawnedActor) {
                *var_v1 = var_a0->next;
                heapFree(var_a0);
                return;
            }
            var_v1 = &var_a0->next;
            var_a0 = var_a0->next;
        }
    }
}
