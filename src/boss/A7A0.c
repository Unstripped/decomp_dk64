#include "common.h"

typedef struct BossC_A7A0_178 {
    s32 unk0;
    u8 pad4[0x10];
    u8 unk14;
} BossC_A7A0_178;

typedef struct BossC_A7A0_Actor {
    char pad[0x58];
    s32 unk58;
    s32 pad5C;
    s32 unk60;
    char pad64[0xB8];
    struct BossC_A7A0_Actor *unk11C;
    char pad120[8];
    s16 unk128;
    char pad12A[0x1A];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x12];
    s16 unk168;
    char pad16A[0xE];
    BossC_A7A0_178 *unk178;
} BossC_A7A0_Actor;

typedef struct BossC_A7A0_BB70 {
    char pad[0x15];
    u8 unk15;
    char pad16[0x1E6];
    BossC_A7A0_Actor *unk1FC;
    u8 unk200;
} BossC_A7A0_BB70;

extern BossC_A7A0_BB70 D_807FBB70;
extern BossC_A7A0_Actor *D_807FBB40;
extern BossC_A7A0_Actor *D_807FBB4C;
void func_806782C0(BossC_A7A0_Actor *);
void func_806319C4(BossC_A7A0_Actor *, s32);

typedef struct {
    BossC_A7A0_Actor *actor;
    s32 pad;
} BossC_A7A0_Entry;

extern BossC_A7A0_Entry D_807FB930[];
extern u16 D_807FBB34;

void bossResetMinions(BossC_A7A0_Actor *arg0) {
    s16 i;
    BossC_A7A0_Actor *actor;

    for (i = 0; i < D_807FBB34; i++) {
        actor = D_807FB930[i].actor;
        if ((arg0 == NULL || actor != arg0) && actor->unk58 == 0xDE) {
            actor->unk60 &= ~0x8000;
            actor->unk154 = 1;
            actor->unk155 = 0;
        }
    }
}

void bossPhaseTick(void) {
    BossC_A7A0_Actor *other;
    s16 timer;

    if (!(D_807FBB40->unk60 & 0x10)) {
        bossResetMinions(D_807FBB40);
        D_807FBB40->unk168 = 0x258;
        D_807FBB40->unk144 = 2;
    }
    if (D_807FBB4C->unk154 != 0x67) {
        timer = D_807FBB40->unk168;
        if (timer != 0) {
            D_807FBB40->unk168 = timer - 1;
        } else {
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk155 = 0;
        }
    }
    if (((D_807FBB70.unk15 != 0) || (D_807FBB70.unk200 == 9)) &&
        ((other = D_807FBB70.unk1FC)->unk154 == 0x2B) &&
        (other->unk155 == 3)) {
        D_807FBB40->unk154 = 1;
        D_807FBB40->unk155 = 0;
        D_807FBB40->unk11C->unk154 = 0x64;
        D_807FBB40->unk11C->unk155 = 0;
        other->unk155 = 0;
        other->unk154 = 0x31;
    }
    if (D_807FBB40->unk154 == 1) {
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk128 -= 10;
        if (D_807FBB40->unk128 < 0) {
            func_806782C0(D_807FBB40);
        }
    }
    func_806319C4(D_807FBB40, 0);
}


void func_80614EBC(BossC_A7A0_Actor *, s32);
void func_80614D90(BossC_A7A0_Actor *);
void func_80613CA8(s32, s16, f32, f32);

void func_8002E9B8(arg0, arg1)
s32 arg0;
s16 arg1;
{
    BossC_A7A0_178 *sp1C = D_807FBB40->unk178;

    func_80614EBC(D_807FBB40, arg0);
    func_80614D90(D_807FBB40);
    func_80613CA8(sp1C->unk0, arg1, 0.0f, 6.0f);
}

typedef struct BossC_A7A0_DC9C {
    char pad[0xC];
    u8 unkC;
} BossC_A7A0_DC9C;

extern BossC_A7A0_DC9C *D_807FDC9C;
void func_8072B324(BossC_A7A0_Actor *, s32);

void func_8002EA14(void) {
    BossC_A7A0_178 *sp1C = D_807FBB40->unk178;

    func_8002E9B8(0x406, 0x674);
    func_8072B324(D_807FBB40, D_807FDC9C->unkC + (sp1C->unk14 * 10) + 15);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/A7A0/func_8002EA7C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/A7A0/D_80036840.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/A7A0/D_80036850.s")
