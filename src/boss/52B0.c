#include "common.h"

typedef struct {
    char pad0[0x38];
    f32 unk38;
} BossB_Sub44;

typedef struct {
    char pad0[4];
    BossB_Sub44 *unk4;
    char pad8[0x80 - 8];
    f32 unk80;
} BossB_ActorBB44;

typedef struct {
    char pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} BossB_ActorBB40;

extern BossB_ActorBB40 *D_807FBB40;
extern BossB_ActorBB44 *D_807FBB44;

void func_80691830(s32, f32, s32, s32, s32, s32, f32, f32, f32, f32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_80613C48(void *, s16, f32, f32);
void func_80614D00(void *, f32, f32);

void func_800292B0(f32 arg0) {
    f32 zero = 0.0f;

    func_80691830(0x6A, 1.2f, 0, 0x96, 0xFF, 0xB, 1.015f, zero, zero, zero);
    func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x221, 0x80, 0x7F, 1, 0, 0.3f, 0);
    D_807FBB44->unk80 = D_807FBB40->unk80;
    D_807FBB44->unk4->unk38 *= arg0;
    func_80613C48(D_807FBB44, 0x4F9, zero, zero);
    func_80614D00(D_807FBB44, 1.5f, zero);
}


s32 func_80611A44(void);
void func_807149B8(s32);
void func_80714998(s32);
void func_807149C8(s32, s32, s32, s32);
void func_8068588C(void *, s16, f32, f32, f32, f32, s32);

void func_800293C0(void) {
    func_80611A44();
    func_807149B8(1);
    func_80714998(3);
    func_807149C8(0x78, 0x78, 0x78, 0xC8);
    func_8068588C(D_807FBB40, (((func_80611A44() >> 15) % 0x7FFF) % 16) + 3, 2.0f, 0.0f, 0.0f, 0.0f, -0x96);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/func_80029468.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036160.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_8003616C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036178.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036188.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_8003619C.s")
