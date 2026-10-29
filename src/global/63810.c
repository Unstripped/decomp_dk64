#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/63810/func_8065EB10.s")

typedef struct RenderB63810_LightEntry {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 pad19[3];
} RenderB63810_LightEntry;

extern s16 D_80748A84;
extern s32 D_8076A0A8;
extern Actor *D_807FBB4C;
extern s32 D_807FBB60;
extern s32 D_807FBB68;
extern RenderB63810_LightEntry D_807F9070[];

void lightSetFlags(u8);
void lightSetTargetId(s16);
void lightSetRadius(s16);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, u8, u8, u8, u8);

void func_8065EFF0(void) {
    s32 i;

    if (D_8076A0A8 == 0x30 && !(((Struct807FD580 *)D_807FBB4C->unk174)->unk1F0 & 0x100000)) {
        D_80748A84 = 0;
        return;
    }

    if (!(D_807FBB60 & 2)) {
        for (i = 0; i < D_80748A84; i++) {
            if (!(D_807FBB68 & 4)) {
                lightSetFlags(2);
            }
            lightSetTargetId(D_807F9070[i].unk12);
            lightSetRadius(D_807F9070[i].unk14);
            lightAdd(D_807F9070[i].unk4, D_807F9070[i].unk8, D_807F9070[i].unkC, 0.0f, 0.0f, 0.0f, D_807F9070[i].unk10, 0, D_807F9070[i].unk16, D_807F9070[i].unk17, D_807F9070[i].unk18);
        }
    }
    D_80748A84 = 0;
}

typedef struct ActorSlotEntry {
    u8 pad0[0x20];
    u8 *unk20;
    u8 pad24[0x62];
    s16 unk86;
    u8 pad88[0x8];
} ActorSlotEntry;

extern ActorSlotEntry *D_807F6000;
s32 hashTableLookup(s32);

void actorSetTargetSlotByte(s32 arg0, u8 arg1) {
    u8 *volatile sp1C;
    s16 temp_a0;
    s32 temp_v0;
    u8 *temp_v1;

    temp_v0 = hashTableLookup(arg0);
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
