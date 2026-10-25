// func_806D205C (src/global/D5E10.c): near-miss stage 6: equivalent C. diffs: sp1C at sp+0x24 vs 0x1C (target has 8-byte hole between sp1C and sp2C, mine puts it below sp1C); $v0 vs $v1 for &D_807FD580 (fixed only if func_806EB0C0 returns s32, which breaks func_806D1F28). Local u16 sp1C[3] init gives .data template reloc instead of D_80750FB0
#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern u16 D_807FD63C;

typedef struct G08Slot {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x32];
} G08Slot;

typedef struct G08Player {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 pad26[6];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0xC];
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A[6];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[0x16];
    /* 0x68 */ f32 unk68;
    /* 0x6C */ u8 pad6C[0x184];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0x48];
    /* 0x23C */ u16 unk23C;
} G08Player;

typedef struct G08Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
    /* 0x66 */ u8 pad66[0x12];
    /* 0x78 */ s32 unk78;
} G08Sub4;

typedef struct G08Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G08Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x62];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0x12];
    /* 0x080 */ f32 unk80;
    /* 0x084 */ u8 pad84[0x28];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[8];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x1C];
    /* 0x0E4 */ u8 unkE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x54];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0xF];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G08Actor;

#define G08_P ((G08Player *)D_807FD580)
#define G08_A48 ((G08Actor *)D_807FBB48)
#define G08_A40 ((G08Actor *)D_807FBB40)

extern u32 D_807FBB60;
extern G08Slot D_807FD63A[];
s32 func_806DF6D4();
void func_806319C4();
void func_806CFF9C();
void func_806EB0C0();
void func_806CC8B8();
void func_806CC8F0();
void func_806C8D20();
s32 func_806D850C();
void func_80614E78(Actor *, s32);
s32 func_80629148();
void func_805FF898();

s32 func_807143E8();
s32 func_80600340();
void func_80688D20(s16, s16, s32, f32);

void func_806D205C(void) {
    s16 sp2C[2];
    u16 sp1C[3] = { 0x1C, 0x86, 0x6B };

    func_806EB0C0(0x3C, 0, D_807FC929);
    G08_P->unk4 = 0.0f;
    G08_P->unk30 = 20.0f;
    if (!(G08_A40->unk6A & 4)) {
        func_806CC8B8();
    } else {
        func_806D850C();
        if (!(G08_A40->unk6C & 4)) {
            func_80614E78(D_807FBB4C, 0x34);
        }
        G08_A40->unkC0 = G08_A40->unkC0 * 0.25;
        func_806CC8F0();
    }
    if ((func_80629148() != 0) || (G08_P->unk23C--, (G08_P->unk23C == 0))) {
        if (func_807143E8() == 0) {
            func_80688D20(sp2C[1], (s16)func_80600340(sp1C, 3, sp2C), 7, 2.0f);
        }
        func_805FF898();
        G08_A40->unk155++;
    }
    func_806319C4(D_807FBB40, 0);
}
