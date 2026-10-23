#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/63810/func_8065EB10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/63810/func_8065EFF0.s")

typedef struct ActorSlotEntry {
    u8 pad0[0x20];
    u8 *unk20;
    u8 pad24[0x62];
    s16 unk86;
    u8 pad88[0x8];
} ActorSlotEntry;

extern ActorSlotEntry *D_807F6000;
s32 func_80659470(s32);

void actorSetTargetSlotByte(s32 arg0, u8 arg1) {
    u8 *volatile sp1C;
    s16 temp_a0;
    s32 temp_v0;
    u8 *temp_v1;

    temp_v0 = func_80659470(arg0);
    if (temp_v0 != -1) {
        temp_v1 = (u8 *)D_807F6000 + (temp_v0 * 0x90);
        temp_a0 = *(s16 *)(temp_v1 + 0x86);
        if (temp_a0 != 1) {
            if (temp_a0 == 2) {
                sp1C = *(u8 **)(temp_v1 + 0x20) + 0x5B;
            }
        } else {
            sp1C = *(u8 **)(temp_v1 + 0x20) + 0xC3;
        }
        *sp1C = arg1;
    }
}
