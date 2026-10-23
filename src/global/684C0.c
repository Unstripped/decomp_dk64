#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/684C0/func_806637C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/684C0/func_80663844.s")

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
extern Actor *D_807FBB44;

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/684C0/func_80663A80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/684C0/func_80663BE8.s")
