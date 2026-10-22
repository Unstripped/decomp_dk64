#include "common.h"

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/func_8002F100.s")

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
} BossE_B100_Sub20;

typedef struct {
    u8 pad0[0x20];
    BossE_B100_Sub20 *unk20;
    u8 pad24[0x38 - 0x24];
    f32 unk38;
} BossE_B100_Sub4;

typedef struct {
    u8 pad0[0x14];
    u8 unk14;
} BossE_B100_Sub178;

typedef struct {
    u8 pad0[0x178];
    BossE_B100_Sub178 *unk178;
} BossE_B100_Sub11C;

typedef struct BossE_B100_Actor {
    u8 pad0[0x4];
    BossE_B100_Sub4 *unk4;
    u8 pad8[0x60 - 0x8];
    s32 unk60;
    u8 pad64[0x11C - 0x64];
    void *unk11C;
    u8 pad120[0x132 - 0x120];
    s16 unk132;
    s16 unk134;
    s32 unk138;
    u8 pad13C[0x144 - 0x13C];
    u8 unk144;
    u8 pad145[0x15F - 0x145];
    u8 unk15F;
    u8 pad160[0x17C - 0x160];
    struct BossE_B100_Actor **unk17C;
} BossE_B100_Actor;

extern BossE_B100_Actor *D_807FBB40;
extern BossE_B100_Actor *D_807FBB44;
extern u8 D_807FBD70;
extern s32 D_8076A064;

void func_8068842C(s32, s32, s32);
void func_80688460(s32, s32, s32);
void func_806883F4(s32, s32, s32, f32);
void func_8002FB7C();
void func_8002FC98();
void func_80677FA8(s32, s32);
void func_8067B238(void *, void *, f32);
void func_80614EBC(void *, s32);
void func_80724DB0(s32, s32, void *);
void func_8072DA60(void);
void func_806319C4(void *, s32);

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/func_8002FB7C.s")
void func_8002FC48(arg0, arg1)
s32 arg0;
u8 arg1;
{
    func_8068842C(arg0, 0, 1);
    func_80688460(arg0, 0, 1);
    func_806883F4(arg0, 0, arg1, 0.0f);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/func_8002FC98.s")


void func_8002FDF8(arg0, arg1)
s32 arg0;
u8 arg1;
{
    s32 v0;
    s32 temp_a1;

    if (D_807FBB40->unk15F == 2) {
        v0 = 4;
    } else {
        v0 = arg1;
    }
    func_8002FB7C(v0 & 0xFF);
    if (D_807FBD70 == 4) {
        func_8002FC98(arg0, 0xF, 0, 0);
        temp_a1 = (0xA - D_807FBB40->unk134) & 0xFF;
        func_8002FC48(D_807FBB40, temp_a1);
        func_80614EBC(D_807FBB40, 0x415);
    }
    if (D_807FBD70 == 5 || D_807FBD70 == 4) {
        func_8072DA60();
    }
}

void func_8002FEC0(arg0, arg1, arg2)
BossE_B100_Actor **arg0;
u8 arg1;
s32 arg2;
{
    func_80677FA8(0xE5, arg2);
    func_8067B238(D_807FBB44, D_807FBB40, D_807FBB40->unk4->unk38);
    D_807FBB44->unk60 |= 0x1400;
    D_807FBB44->unk11C = D_807FBB40;
    D_807FBB44->unk144 = D_807FBB40->unk144;
    D_807FBB44->unk60 = D_807FBB40->unk60;
    arg0[arg1] = D_807FBB44;
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/func_8002FF74.s")
void func_80030888(void) {
    BossE_B100_Sub11C *sp1C;
    BossE_B100_Sub178 *sp18;
    s32 var_v0;

    sp1C = D_807FBB40->unk11C;
    sp18 = sp1C->unk178;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724DB0(2, 1, sp1C);
    }
    var_v0 = (D_807FBB40->unk15F == 1) ? sp18->unk14 : 0;
    func_8002FDF8(sp1C, (u8)var_v0);
    func_806319C4(D_807FBB40, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368C0.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368E4.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368F8.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036910.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036950.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036968.s")
