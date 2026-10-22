#include "common.h"

typedef struct BossC_6240_17C {
    char pad[4];
    u8 unk4;
    u8 pad5;
    s16 unk6;
    s16 unk8;
} BossC_6240_17C;

typedef struct BossC_6240_Actor40 {
    char pad[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xF4];
    BossC_6240_17C *unk17C;
} BossC_6240_Actor40;

extern BossC_6240_Actor40 *D_807FBB40;
extern u32 D_8076A064;

s32 func_80611A44(void);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_8002A240(void) {
    BossC_6240_17C *s0 = D_807FBB40->unk17C;
    f32 sp20;
    if (s0->unk4 != 0) {
        s0->unk4--;
        sp20 = (f32)(func_80612794((s16)(s32)(((f64)(u32)s0->unk4 / 10.0) * (s0->unk8 - (s0->unk8 + 0x400)) + (s0->unk8 + 0x400))) * 20.0);
        D_807FBB40->unk7C += sp20 * func_80612794(s0->unk6);
        D_807FBB40->unk84 += sp20 * func_80612790(s0->unk6);
        if (s0->unk4 == 0) {
            s0->unk8 += 0x400;
        }
    } else if (((func_80611A44() >> 15) % 1000) >= 941) {
        s0->unk4 = 10;
    }
    D_807FBB40->unk80 += 8.0 * (f64)func_80612794((s16)(s32)((f64)(u32)D_8076A064 * 200.0));
}
void *func_8067ADB4(s32);
void func_8067AB20(void *, void *, s32, s32, void *, s32);

void func_8002A41C(u8 arg0) {
    void *target;
    f32 sp2C[2];

    switch (arg0) {
    case 0:
        target = func_8067ADB4(0x61);
        if (target != NULL) {
            func_8067AB20(D_807FBB40, target, 0x01000000, 1, sp2C, 0);
        }
        break;
    case 1:
        target = func_8067ADB4(0x60);
        if (target != NULL) {
            func_8067AB20(D_807FBB40, target, 0x01000000, 1, sp2C, 0);
        }
        target = func_8067ADB4(0x61);
        if (target != NULL) {
            func_8067AB20(D_807FBB40, target, 0x01000000, 3, sp2C, 0);
        }
        break;
    case 2:
        target = func_8067ADB4(0x60);
        if (target != NULL) {
            func_8067AB20(D_807FBB40, target, 0x01000000, 1, sp2C, 0);
        }
        target = func_8067ADB4(0x61);
        if (target != NULL) {
            func_8067AB20(D_807FBB40, target, 0x01000000, 2, sp2C, 0);
        }
        break;
    }
}

extern u8 D_80720120[];

void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714C08(void *, f32, void *, s32, s32);

void func_8002A55C(u8 arg0, f32 arg1) {
    if (!(arg0 & D_8076A064)) {
        func_807149B8(1);
        func_807149C8(0xFF, 0xD7, 0x58, 0xFF);
        func_80714C08(D_80720120, arg1, D_807FBB40, 1, 0);
    }
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/func_8002A5CC.s")

typedef struct BossC_6240_Actor {
    char pad[0x7C];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
    f32 unk88;
    char pad8C[4];
    f32 unk90;
} BossC_6240_Actor;

extern BossC_6240_Actor *D_807FBB4C;
s32 func_80725BA4(s16, s16, s32);

void func_8002A8B8(s32 arg0) {
    if (!func_80725BA4((s32)D_807FBB4C->unk7C, (s32)D_807FBB4C->unk84, arg0)) {
        D_807FBB4C->unk7C = D_807FBB4C->unk88;
        D_807FBB4C->unk84 = D_807FBB4C->unk90;
    }
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/func_8002A92C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_800362F0.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_800362FC.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036308.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_8003631C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036334.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036340.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036354.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036388.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_8003639C.s")
