#include "common.h"

typedef struct {
    char pad[0x20];
    u8 *unk20;
} BossB_Struct_DC98;

typedef struct {
    char pad[0x11];
    u8 unk11;
} BossB_Struct_DC9C;

extern BossB_Struct_DC98 *D_807FDC98;
extern BossB_Struct_DC9C *D_807FDC9C;

void heapFree(void *);
void *func_80610FE8(s32);

void func_80027840(u8 *arg0) {
    s16 i;
    u8 *dst;

    if (D_807FDC98->unk20 != NULL) {
        heapFree(D_807FDC98->unk20);
    }
    D_807FDC9C->unk11 = *arg0;
    D_807FDC98->unk20 = func_80610FE8(*arg0 * 2);
    dst = D_807FDC98->unk20;
    for (i = 0; i < *arg0; i++) {
        dst[0] = arg0[i + 1];
        dst[1] = 0;
        dst += 2;
    }
}

typedef struct {
    char pad0[8];
    f32 unk8;
    f32 unkC;
} BossB_Struct_800278F4;

void func_800278F4(BossB_Struct_800278F4 *arg0, f32 arg1, s16 arg2, s16 arg3) {
    arg0->unkC += ((f32)arg2 - arg0->unkC) * arg1;
    arg0->unk8 += ((f32)arg3 - arg0->unk8) * arg1;
}

typedef struct {
    char pad0[0x15];
    u8 unk15;
} BossB_Struct_80027950;

typedef struct {
    char pad0[0x25];
    u8 unk25;
} BossB_Struct_DC90;

extern BossB_Struct_DC90 *D_807FDC90;

s32 func_80611A44(void);

void func_80027950(BossB_Struct_80027950 *arg0, u8 *arg1) {
    u8 prev = D_807FDC90->unk25;
    do {
        s32 rand = func_80611A44() >> 15;
        u8 offset = arg0->unk15;
        D_807FDC90->unk25 = arg1[offset] + ((rand % 65536) % (arg1[offset + 1] - arg1[offset] + 1));
    } while (D_807FDC90->unk25 == prev);
    arg0->unk15 += 2;
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/3840/func_80027A30.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/3840/func_80027BA8.s")

void func_805FF8F8(void);

void func_80028458(void) {
    func_805FF8F8();
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/3840/func_80028478.s")

typedef struct {
    char pad0[0x11C];
    s32 unk11C;
} BossB_Struct_807FBB40;

extern BossB_Struct_807FBB40 *D_807FBB40;

void func_806A2A10(s32, s32, s32);
void func_806A2B08(s32);

void func_80028680(void) {
    func_806A2A10(-0x7F83, 0xD2, 0xB4);
    func_806A2B08(D_807FBB40->unk11C);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/3840/func_800286B8.s")

void func_8073129C(s32, s32, s32);

void func_80028820(void) {
    func_8073129C(0x51, 0, 2);
    func_8073129C(0x52, 0, 2);
    func_8073129C(0x53, 0, 2);
    func_8073129C(0x54, 0, 2);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/3840/func_80028878.s")

void func_8066EA64(void *, s32);
void func_8066EA90(void *, s32);

void func_800290D4(arg0)
u8 arg0;
{
    if (arg0) {
        func_8066EA64(D_807FBB40, 2);
        func_8066EA64(D_807FBB40, 3);
    } else {
        func_8066EA90(D_807FBB40, 2);
        func_8066EA90(D_807FBB40, 3);
    }
}

typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    u8 unk4;
    u8 unk5;
} BossB_Struct_800359D0;

extern BossB_Struct_800359D0 D_800359D0[];
extern s32 D_8076A0A8;

s32 func_8073110C(s16, s32);

void func_80029140(s16 *arg0) {
    s16 i = 0;
    while (D_800359D0[i].unk0 != 0 && D_8076A0A8 != D_800359D0[i].unk0) {
        i++;
    }
    if (D_800359D0[i].unk0 != 0 && D_800359D0[i].unk4 == *arg0) {
        if (func_8073110C(D_800359D0[i].unk2, 2) != 0) {
            *arg0 = D_800359D0[i].unk5;
        }
    }
}

void func_8002920C(void) {
    s16 i = 0;
    while (D_800359D0[i].unk0 != 0 && D_8076A0A8 != D_800359D0[i].unk0) {
        i++;
    }
    if (D_800359D0[i].unk0 != 0) {
        func_8073129C(D_800359D0[i].unk2, 1, 2);
    }
}
