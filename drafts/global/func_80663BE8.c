// func_80663BE8 (src/global/684C0.c): 100% logic and control flow match (30 insns); node gets $v1 instead of $a2 due to temporary register allocation
#include "common.h"
#include "actor.h"

typedef struct R6A_Actor {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[0x156 - 0x58];
    u8 unk156;
} R6A_Actor;

typedef struct R6A_SubNode {
    R6A_Actor *actor;
    s32 unk4;
    struct Actor *spawnedActor;
    struct R6A_SubNode *next;
} R6A_SubNode;

typedef struct R6A_ZoneNode {
    void *zone;
    R6A_SubNode *subList;
    struct R6A_ZoneNode *next;
} R6A_ZoneNode;

extern R6A_ZoneNode *D_807F9410;
void heapFree(void *);

void func_80663BE8(Actor *arg0) {
    R6A_ZoneNode *node;
    R6A_SubNode **subListPtr;
    R6A_SubNode *subNode;

    for (node = D_807F9410; node != NULL; node = node->next) {
        for (subListPtr = &node->subList, subNode = *subListPtr; subNode != NULL; ) {
            if (arg0 == subNode->spawnedActor) {
                *subListPtr = subNode->next;
                heapFree(subNode);
                return;
            }
            subListPtr = &subNode->next;
            subNode = subNode->next;
        }
    }
}
