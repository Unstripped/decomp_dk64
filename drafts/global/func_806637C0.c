// func_806637C0 (src/global/684C0.c): 99% match, for loop fixed delay slot; single instruction scheduling diff remaining in prologue (addiu s3 vs sw zero)
#include "common.h"
#include "actor.h"

typedef struct R2F684C0_Actor {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[0x156 - 0x58];
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
    void *unk0;
    R2F684C0_SubNode *subList;
    struct R2F684C0_ZoneNode *next;
} R2F684C0_ZoneNode;

extern R2F684C0_ZoneNode *D_807F9410;
void *func_80610FE8(s32);

void func_806637C0(R2F684C0_Actor *arg0) {
    s32 var_s0;
    R2F684C0_ZoneNode **var_s1;
    s32 temp_s2;
    R2F684C0_Zone *temp_s3;
    R2F684C0_ZoneNode *temp_v0_2;
    s32 *temp_v0;

    var_s1 = &D_807F9410;
    temp_v0 = (s32 *)(arg0->unk54 + (u8 *)arg0);
    temp_s2 = *temp_v0;
    temp_s3 = (R2F684C0_Zone *)(temp_v0 + 1);
    *var_s1 = NULL;
    for (var_s0 = 0; var_s0 < temp_s2; var_s0++) {
        temp_v0_2 = func_80610FE8(sizeof(R2F684C0_ZoneNode));
        *var_s1 = temp_v0_2;
        var_s1 = &temp_v0_2->next;
        temp_v0_2->unk0 = &temp_s3[var_s0];
        temp_v0_2->subList = NULL;
        temp_v0_2->next = NULL;
    }
}
