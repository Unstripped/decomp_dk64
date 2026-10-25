#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern s32 D_8076A0A8;
extern u8 D_8074E77C[];

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F09F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F0B34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F0C18.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F0D68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1048.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F10E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1250.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F12FC.s")

void func_806E225C();

void func_806F1350(s32 arg0) {
    func_806E225C(0, 1);
}

void func_806F1378(s32 arg0) {}

typedef struct F5AActorSub4 {
    u8 pad0[0x88];
    s32 unk88;
} F5AActorSub4;

void func_80614FD8(f32 *);

void func_806F1380(Actor *arg0) {
    f32 temp;

    func_80614FD8(&temp);
    ((F5AActorSub4 *)arg0->unk4)->unk88 = (s32)(arg0->unkB8 - temp);
}

typedef struct F5APlayerState {
    u8 pad0[0x4C];
    s16 unk4C;
} F5APlayerState;

#define F5A_PS ((F5APlayerState *)D_807FD580)

void func_80614F28(u8 *);
s32 func_806CD9A0(Actor *, f32, f32, s16, s16);

void func_806F13C8(Actor *arg0) {
    u8 temp;

    func_80614F28(&temp);
    ((F5AActorSub4 *)arg0->unk4)->unk88 =
        func_806CD9A0(arg0, arg0->unkB8, arg0->unkB8, F5A_PS->unk4C, D_807FD584) - temp;
}

typedef struct F5APlayerCoefficient {
    f32 value;
    u8 pad4[0x30];
} F5APlayerCoefficient;

extern F5APlayerCoefficient D_807FD618[];
void func_806CFF9C(void);

void func_806F142C(void) {
    f32 value;

    func_806CFF9C();
    value = D_807FBB40->unkB8;
    D_807FBB40->unkB8 =
        D_807FD618[D_807FC929].value * (value - (value / 2)) + (value / 2);
}

void func_806D0150(Actor *);

void func_806F149C(Actor *arg0) {
    func_806D0150(arg0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F14BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1668.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1768.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1858.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F18F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1990.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1A18.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1AE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1B58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1B90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1C04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1EB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F22A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F2754.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F2A40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F2C48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F2EDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F2FC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3190.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3760.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F37BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F386C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3950.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F397C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F39E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3BEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3DB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3DC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3E0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F4528.s")
