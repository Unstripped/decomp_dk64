#include "common.h"

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/func_800330D0.s")

typedef struct {
    u8 pad0[0x38];
    f32 unk38;
    u8 pad3C[0x64 - 0x3C];
    u16 unk64;
} BossE_F0D0_SubStruct;

typedef struct {
    u8 pad0[0x4];
    BossE_F0D0_SubStruct *unk4;
    u8 pad8[0x7C - 0x8];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x128 - 0x88];
    s16 unk128;
    u8 pad12A[0x154 - 0x12A];
    u8 unk154;
    u8 unk155;
} BossE_F0D0_Actor;

typedef struct {
    u8 pad0[0x14];
    u8 unk14;
    u8 unk15;
    u8 unk16;
} BossE_F0D0_Sub14;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[4];
} BossE_F0D0_FDCA0_Sub;

typedef struct {
    u8 pad0[0x14];
    BossE_F0D0_FDCA0_Sub *unk14;
} BossE_F0D0_FDCA0;

extern BossE_F0D0_Actor *D_807FBB40;
extern BossE_F0D0_Actor *D_807FBB4C;
extern BossE_F0D0_FDCA0 *D_807FDCA0;
void func_80614EBC(void *, s32);
void func_80614D90(void *);
void func_80714998(s32);
void func_8071498C(void *);
void func_807149B8(s32);
void func_80714950(s32);
s32 func_80611A44(void);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_806782C0(void *);
void func_806EB0C0(s32, void *, s32);
void func_8061EF4C(void *, s32, s32, f32, f32, f32, f32, f32);
extern void *D_807F5D10;
extern void *D_8071720C;
extern void *D_8074E880[];
void func_8003340C(u8 *arg0) {
    s32 temp_v0;

    temp_v0 = D_807FBB40->unk4->unk64;
    if (temp_v0 != 0x223 && arg0[3] == arg0[1]) {
        func_80614EBC(D_807FBB40, 0x223);
        func_80614D90(D_807FBB40);
        return;
    }
    if (temp_v0 != 0x224 && arg0[3] != arg0[1]) {
        func_80614EBC(D_807FBB40, 0x224);
        func_80614D90(D_807FBB40);
    }
}

f32 func_80612794(s16);
s16 func_80665DE0(f32, f32, f32, f32);
s16 func_806CC190(s16, s16, f32);

typedef struct {
    u8 pad0[4];
    f32 unk4;
} Boss2D_SubSub0;

typedef struct {
    Boss2D_SubSub0 *unk0;
} Boss2D_SubStruct;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} Boss2D_Node;

void func_800334A4(u8 *arg0, f32 arg1) {
    f64 val;
    f32 temp_f;

    val = (f64)(((Boss2D_SubStruct *)D_807FBB40->unk4)->unk0->unk4 * arg1);

    temp_f = (f32)(1.0 + (f64)func_80612794((s16)(s32)((f32)(1.0 - (1.0 < val ? 1.0 : val)) * 1024.0f + 3072.0f)));

    D_807FBB40->unk7C = (f32)((Boss2D_Node *)D_807FDCA0->unk14)[arg0[1]].unk0 + (f32)(((Boss2D_Node *)D_807FDCA0->unk14)[arg0[0]].unk0 - ((Boss2D_Node *)D_807FDCA0->unk14)[arg0[1]].unk0) * temp_f;
    D_807FBB40->unk84 = (f32)((Boss2D_Node *)D_807FDCA0->unk14)[arg0[1]].unk4 + (f32)(((Boss2D_Node *)D_807FDCA0->unk14)[arg0[0]].unk4 - ((Boss2D_Node *)D_807FDCA0->unk14)[arg0[1]].unk4) * temp_f;

    *(s16 *)((u8 *)D_807FBB40 + 0xE6) = func_806CC190(*(s16 *)((u8 *)D_807FBB40 + 0xE6), func_80665DE0(((Boss2D_Node *)D_807FDCA0->unk14)[arg0[1]].unk0, ((Boss2D_Node *)D_807FDCA0->unk14)[arg0[1]].unk4, ((Boss2D_Node *)D_807FDCA0->unk14)[arg0[0]].unk0, ((Boss2D_Node *)D_807FDCA0->unk14)[arg0[0]].unk4), 10.0f);
}

void func_800336C0(void) {
    f32 sp24;

    sp24 = (f32) ((f64) D_807FBB40->unk4->unk38 / 0.15);
    func_80714998(2);
    func_8071498C(&D_8071720C);
    func_807149B8(1);
    func_80714950(1);
    func_80714CC0(D_8074E880[((func_80611A44() >> 15) % 1000) % 3], (f32) (f64) sp24, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/func_80033784.s")

void func_80690814(void *, s32);
void func_80690A28(s32, s32, f32, f32, f32, f32, f32, void *);
void func_8003392C(u8 *arg0) {
    func_80690814(D_807FBB40, 1);
    func_80690A28(0x2C, 2, D_807FBB40->unk4->unk38, D_807FDCA0->unk14[arg0[3]].unk0, D_807FDCA0->unk14[arg0[3]].unk2, D_807FDCA0->unk14[arg0[3]].unk4, 1200.0f, D_807FBB40);
}

s32 func_800339D8(BossE_F0D0_Sub14 *arg0, u8 *arg1) {
    if ((D_807FBB4C->unk80 < (D_807FBB40->unk80 - 10.0f)) && (arg0->unk14 < 5)) {
        arg0->unk15 = arg0->unk16;
        D_807FBB40->unk154 = arg1[arg0->unk15];
        arg0->unk15++;
        D_807FBB40->unk155 = 0;
        func_80614EBC(D_807FBB40, 0);
        return 1;
    }
    return 0;
}


void func_80033A80(s8 arg0) {
    D_807FBB40->unk128 += arg0;
    if (D_807FBB40->unk128 < 0) {
        D_807FBB40->unk128 = 0;
        D_807FBB40->unk155++;
    } else if (D_807FBB40->unk128 >= 0x100) {
        D_807FBB40->unk128 = 0xFF;
        D_807FBB40->unk155++;
    }
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/func_80033AF0.s")

void func_8003575C(void) {
    f32 dx, dz;

    switch (D_807FBB40->unk155) {
    case 1:
        if (D_807FBB40->unk154 == 0) {
            dx = D_807FBB4C->unk7C - D_807FBB40->unk7C;
            dz = D_807FBB4C->unk84 - D_807FBB40->unk84;
            if (dx * dx + dz * dz < 4225.0f) {
                if (D_807FBB4C->unk154 != 0x31) {
                    func_806EB0C0(0x2E, D_807FBB40, 0);
                }
                D_807FBB40->unk154++;
            }
        }
        break;
    case 3:
        func_806782C0(D_807FBB40);
        break;
    }
    func_8061EF4C(D_807F5D10, 5, 0x14, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 200.0f, 400.0f);
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C10.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C18.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C20.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C28.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C30.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C40.s")
