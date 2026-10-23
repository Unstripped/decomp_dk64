// func_80663BE8 (src/global/684C0.c): 100% logic match; node in a2 vs v1 outer pointer; tested K&R, register, param counts, dummy variables
#include "common.h"
#include "actor.h"

typedef struct R2F684C0_Actor {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[0x156 - 0x58];
    u8 unk156;
} R2F684C0_Actor;

typedef struct R2F684C0_SubNode {
    R2F684C0_Actor *actor;
    s32 unk4;
    struct Actor *spawnedActor;
    struct R2F684C0_SubNode *next;
} R2F684C0_SubNode;

typedef struct R2F684C0_ZoneNode {
    void *unk0;
    R2F684C0_SubNode *subList;
    struct R2F684C0_ZoneNode *next;
} R2F684C0_ZoneNode;

extern R2F684C0_ZoneNode *D_807F9410;
void heapFree(void *);

void func_80663BE8(Actor *arg0) {
    R2F684C0_ZoneNode *var_a2;
    R2F684C0_SubNode **var_v1;
    R2F684C0_SubNode *var_a0;

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
