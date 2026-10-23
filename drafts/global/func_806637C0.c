// func_806637C0 (src/global/684C0.c): 98% match, 2-instruction scheduling difference in prologue/loop delay slot
#include "common.h"
#include "actor.h"

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
void *func_80610FE8(s32);

void func_806637C0(R1F67890_Actor *arg0) {
    s32 *temp_v0;
    s32 temp_s2;
    s32 var_s0;
    R1F67890_ZoneNode **var_s1;
    R1F67890_ZoneNode *temp_v0_2;
    R1F67890_Zone *temp_s3;

    var_s1 = &D_807F9410;
    temp_v0 = (s32 *)(arg0->unk54 + (u8 *)arg0);
    temp_s2 = *temp_v0;
    temp_s3 = (R1F67890_Zone *)(temp_v0 + 1);
    *var_s1 = NULL;
    if (temp_s2 > 0) {
        var_s0 = 0;
        do {
            temp_v0_2 = func_80610FE8(sizeof(R1F67890_ZoneNode));
            *var_s1 = temp_v0_2;
            var_s1 = &temp_v0_2->next;
            temp_v0_2->unk0 = &temp_s3[var_s0++];
            temp_v0_2->subList = NULL;
            temp_v0_2->next = NULL;
        } while (var_s0 != temp_s2);
    }
}
