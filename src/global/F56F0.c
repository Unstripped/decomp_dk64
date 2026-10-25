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

typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} F5BSlot;


typedef struct {
    u8 pad0[0x8E];
    u8 unk8E;
} F5BPlayerState;

typedef struct {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x54];
    f32 unkB8;
    u8 padBC[0x2A];
    s16 unkE6;
    u8 padE8[6];
    s16 unkEE;
} F5BActor;

typedef struct {
    u8 pad0[0xC];
    f32 unkC;
} F5BAccel;

#define F5B_PLAYER_STATE ((F5BPlayerState *)D_807FD580)

extern u16 D_80752F40[];
extern f32 func_80612790(s16);

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F18F4.s")

void func_806F1990(s32 arg0, F5BSlot *arg1, s32 *arg2) {
    u16 temp_v0;

    temp_v0 = D_80752F40[F5B_PLAYER_STATE->unk8E];
    arg1[*arg2].unk0 = 0x7F;
    arg1[*arg2].unk1 = 1;
    arg1[*arg2].unk2 = temp_v0;
    arg1[*arg2].unk4 = temp_v0;
    arg1[*arg2].unk6 = 0;
    *arg2 += 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1A18.s")

f32 func_806F1AE0(F5BActor *arg0, F5BAccel *arg1, f32 arg2) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = func_80612790((s16)(arg0->unkE6 - arg0->unkEE)) * (arg0->unkB8 * 0.0076923077f);
    temp_fa0 = temp_fv1 - arg1->unkC;
    arg1->unkC = temp_fv1;
    return (temp_fa0 + temp_fv1) * arg2;
}

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

typedef struct {
    s16 unk0;
    u8 pad2[2];
    void *unk4;
} F5DListEntry;

extern u8 D_807FD716;

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3190.s")

void func_806F4528(void *);

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3760.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F37BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F386C.s")

typedef struct {
    s16 unk0;
    u8 pad2[2];
    void *unk4;
} F5DDeferredEntry;

void heapFreeDeferred(void *);

void func_806F3950(F5DDeferredEntry *arg0) {
    heapFreeDeferred(arg0->unk4);
    arg0->unk0 = 0;
}


void func_806F386C(u8, s32, s32, s16, s32);

void func_806F397C(s32 arg0, s32 arg1, s16 arg2, s16 arg3) {
    s32 var_v0;

    if (arg2 & 0x8000) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    arg2 &= 0x7FFF;
    func_806F386C((u8) arg2, arg0, arg1, arg3, var_v0);
    D_807FD716 = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F39E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3BEC.s")

void func_806F3DB0(void) {
    D_807FD716 |= 2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3DC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3E0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F4528.s")
