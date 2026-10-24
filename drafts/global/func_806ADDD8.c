// func_806ADDD8 (src/global/B1F60.c): parked NON_MATCHING. Only diff: spill of the switch value is sw t1,0x28(sp)/lbu a0,0x2B(sp) vs expected 0x2C/0x2F. 'u32 k = 0x31A' local makes uopt keep the constant in a1 (matches). Any extra local (pad, or s32 temp holding unk154) moves the spill to 0x2C but grows the frame 56->64. Stage 5.
#include "actor.h"

typedef struct M3Sub0 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
} M3Sub0;

typedef struct M3Sub4 {
    /* 0x00 */ M3Sub0 *unk0;
    /* 0x04 */ u8 pad4[0x60];
    /* 0x64 */ u16 unk64;
} M3Sub4;

typedef struct M3Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ M3Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[6];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x14];
    /* 0x080 */ f32 unk80;
    /* 0x084 */ u8 pad84[0x20];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[0x2A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x42];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[0x20];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} M3Actor;

extern M3Actor *D_807FBB40;
s32 func_80611A44(void);
void func_80614EBC(M3Actor *, s32);
void func_806319C4(M3Actor *, s32);
void func_80729B00(void);
u32 func_8072AB74(u8, f32, f32, s32, f32);
typedef struct M3State98 {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ u16 unk28;
} M3State98;

s32 func_8072E22C(s32);
void func_8072B7CC(s32);

void func_806ADDD8(void) {
    u32 k = 0x31A;

    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 |= 0x40;
        ((M3State98 *)D_807FDC98)->unk28 = k;
    }
    switch (D_807FBB40->unk154) {
        case 0:
        case 1:
            if (func_8072E22C(0x12C) != 0) {
                func_80614EBC(D_807FBB40, k);
                D_807FBB40->unk154 = 0x23;
                D_807FBB40->unk155 = 0;
            }
            break;
        case 4:
            if (D_807FBB40->unk4->unk64 != 0x319) {
                D_807FBB40->unk154 = 0x23;
                D_807FBB40->unk155 = 0;
            } else if (func_8072E22C(0x64) != 0) {
                func_80614EBC(D_807FBB40, 0x31B);
                D_807FBB40->unk154 = 0x1E;
                D_807FBB40->unk155 = 0;
            }
            break;
        case 0x1E:
            if (D_807FBB40->unk4->unk64 == k) {
                D_807FBB40->unk154 = 0x23;
                D_807FBB40->unk155 = 0;
            }
            break;
        case 0x23:
            if (D_807FBB40->unk4->unk64 == k && D_807FBB40->unk4->unk0->unk4 > 4.0f) {
                func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
            }
            if (func_8072E22C(0x12C) == 0) {
                func_80614EBC(D_807FBB40, 0x31C);
                D_807FBB40->unk154 = 0;
                D_807FBB40->unk155 = 0;
            }
            break;
        default:
            func_8072B7CC(k);
            break;
    }
    func_806319C4(D_807FBB40, 0);
}
