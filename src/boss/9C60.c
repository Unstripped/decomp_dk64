#include "common.h"

typedef struct BossC_9C60_Sub0 {
    char pad[0x10];
    s16 unk10;
    char pad12[0x12];
    f32 unk24;
} BossC_9C60_Sub0;

typedef struct BossC_9C60_Sub4 {
    BossC_9C60_Sub0 *unk0;
    char pad4[0x34];
    f32 unk38;
    char pad3C[0xC];
    f32 unk48;
} BossC_9C60_Sub4;

typedef struct BossC_9C60_Actor {
    char pad[4];
    BossC_9C60_Sub4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0xB8];
    struct BossC_9C60_Actor *unk11C;
    char pad120[0x58];
    struct BossC_9C60_Actor **unk178;
} BossC_9C60_Actor;

extern BossC_9C60_Actor *D_807FBB40;
extern BossC_9C60_Actor *D_807FBB44;

void func_80677FA8(s32, s32);
void func_8067B238(BossC_9C60_Actor *, BossC_9C60_Actor *, f32);
void func_806782C0(void *);
void func_806319C4(BossC_9C60_Actor *, s32);
void func_8002DC60(void) {
    BossC_9C60_Actor **sp1C = D_807FBB40->unk178;

    func_80677FA8(0xDD, 0xE3);
    D_807FBB44->unk60 |= 0x400;
    D_807FBB44->unk11C = D_807FBB40;
    *sp1C = D_807FBB44;
    func_8067B238(D_807FBB44, D_807FBB40, D_807FBB40->unk4->unk38);
}

void func_8002DCE0(void) {
    func_8067B238(D_807FBB40, D_807FBB40->unk11C, D_807FBB40->unk4->unk38);
    D_807FBB40->unk4->unk48 = D_807FBB40->unk11C->unk4->unk48;
    if (D_807FBB40->unk4->unk0->unk10 == 0x675 && D_807FBB40->unk4->unk0->unk24 == 0.0f) {
        func_806782C0(D_807FBB40);
    }
    func_806319C4(D_807FBB40, 0);
}

typedef struct BossC_9C60_Target {
    char pad[0x58];
    s32 unk58;
} BossC_9C60_Target;

typedef struct {
    BossC_9C60_Target *actor;
    s32 pad;
} BossC_9C60_Entry;

extern BossC_9C60_Entry D_807FB930[];
extern u16 D_807FBB34;

void func_806782C0(void *);

void func_8002DD7C(void) {
    s16 i;
    BossC_9C60_Target *actor;

    for (i = 0; i < D_807FBB34; i++) {
        actor = D_807FB930[i].actor;
        if (actor->unk58 == 0xAA) {
            func_806782C0(actor);
        }
    }
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/func_8002DE04.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036750.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036768.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036774.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036780.s")
