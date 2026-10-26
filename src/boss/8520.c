#include "common.h"

typedef struct BossA_Struct_807FBB40 {
    u8 pad0[0x7C];
    f32 unk7C;
    u8 pad80[4];
    f32 unk84;
} BossA_Struct_807FBB40;

typedef struct BossA_Struct_807FDC9C {
    u8 pad0[6];
    s16 unk6;
} BossA_Struct_807FDC9C;

typedef struct BossA_Struct_807FBB44 {
    u8 pad0[0xC8];
    f32 unkC8;
    u8 padCC[0x12A - 0xCC];
    s16 unk12A;
} BossA_Struct_807FBB44;

extern BossA_Struct_807FBB40 *D_807FBB40;
extern BossA_Struct_807FDC9C *D_807FDC9C;
extern BossA_Struct_807FBB44 *D_807FBB44;

f32 func_80612790(s16);
f32 func_80612794(s16);
void spawnNodeSpawnById(s16, s16, s16, s16, s32, s32, s32);

void func_8002C520(s16 arg0, s16 arg1, s16 arg2) {
    f32 pad;
    f32 sinVal;
    f32 fArg1;

    sinVal = func_80612794(arg2);
    fArg1 = arg1;
    spawnNodeSpawnById(
        arg0,
        sinVal * fArg1 + D_807FBB40->unk7C,
        D_807FDC9C->unk6,
        func_80612790(arg2) * fArg1 + D_807FBB40->unk84,
        0, 0, 0
    );
    D_807FBB44->unkC8 *= 2;
    D_807FBB44->unk12A = 0x7D0;
}

typedef struct BossA_Struct_807FDC90 {
    u8 pad0[0x1A];
    u16 unk1A;
    u8 pad1C[0x28 - 0x1C];
    s32 unk28;
} BossA_Struct_807FDC90;

extern BossA_Struct_807FDC90 *D_807FDC90;

s32 func_80611A44(void);
void func_8061CC40(void *, s32, s32);

void func_8002C5F4(void) {
    s32 rand;

    rand = func_80611A44();
    func_8002C520(2, ((rand >> 15) % 100) + 300, (func_80611A44() >> 15) % 4096);

    rand = func_80611A44();
    func_8002C520(3, ((rand >> 15) % 100) + 300, (func_80611A44() >> 15) % 4096);

    rand = func_80611A44();
    func_8002C520(4, ((rand >> 15) % 100) + 300, (func_80611A44() >> 15) % 4096);

    if (!(D_807FDC90->unk1A & 0x8000)) {
        D_807FDC90->unk1A |= 0x8000;
        func_8061CC40(D_807FBB44, 2, 1);
    }
}

void animSetLoopLimit(void *, s32, s32);
void animSetFinished(void *, s32, s32);
void animSetFrameAndSubframe(void *, s32, s16, f32);

void func_8002C748(arg0)
u8 arg0;
{
    D_807FDC90->unk28 = 2;
    animSetLoopLimit(D_807FBB40, arg0, 1);
    animSetFinished(D_807FBB40, arg0, 1);
    animSetFrameAndSubframe(D_807FBB40, arg0, D_807FDC90->unk28 & 0xF, 0.0f);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/8520/func_8002C7CC.s")

typedef struct BossA_Struct_807FDC94 {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x15E - 0x88];
    u8 unk15E;
} BossA_Struct_807FDC94;

extern BossA_Struct_807FDC94 *D_807FDC94;

s32 func_80611A44(void);
void projectileGetTargetCoords(void *, s32);
void projectileAimAndSpawn(s32, s16, f32, f32, f32, f32, f32, void *);

void func_8002C8B4(void) {
    projectileGetTargetCoords(D_807FBB40, 1);
    projectileAimAndSpawn(
        0x116,
        ((func_80611A44() >> 15) % 3) + 1,
        1.0f,
        D_807FDC94->unk7C,
        D_807FDC94->unk80 + (f32)D_807FDC94->unk15E,
        D_807FDC94->unk84,
        300.0f,
        D_807FBB40
    );
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/8520/func_8002C964.s")
