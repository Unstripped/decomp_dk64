// func_806B7EA0 (src/global/BC3B0.c): stage 6: behaviourally equal, frame 0x48 and all code matched; only regalloc in block after unk2E check: D_807FBB40 pointer temp lands in v1 (target a0) and D_807FDC94 pointer in v0 (target v1), plus lui t0/t8 order after func_806A2A10. Tried s16/s32/u8 temps, ternary arg, local removal, nested ifs; permuter 300s no gain
#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern u8 D_807FBD70;

typedef struct R1BSub174 {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ s16 unk2C;
} R1BSub174;

typedef struct R1BView {
    /* 0x000 */ u8 pad0[0x6E];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0x104];
    /* 0x174 */ R1BSub174 *unk174;
    /* 0x178 */ f32 *unk178;
} R1BView;

typedef struct R1BCursor {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 vx;
    /* 0xC */ f32 vy;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ f32 unk18;
} R1BCursor;

void func_806B7BB8(void *);
void func_806B7C74(R1BCursor *, f32, f32);
void func_806B76B0();
void func_806B7830();

typedef struct R1BDC90 {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
} R1BDC90;

typedef struct R1BDC9C {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
} R1BDC9C;

#define R1BA ((R1BView *)D_807FBB40)
#define R1BS90 ((R1BDC90 *)D_807FDC90)
#define R1BS9C ((R1BDC9C *)D_807FDC9C)

extern s32 D_807FBB64;
extern s32 D_807FBB68;

void func_80729B00(void);
void func_806A2A10(s32, s32, u8, s32 *);
s32 func_8061CB50(void);
s32 func_8061CC00(void);
void func_80609140(s32, s32, f32, f32, s32, s32);
void actorSetStateTwo(s32);
s16 func_80672A70(s16, s16);
void func_8061CC40(void *, s32, s32);
void func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
void renderCallbacksRegister(void *, void *, s32);

void func_806B7EA0(void) {
    R1BCursor *c;
    f32 sp40;
    f32 sp3C;
    c = (R1BCursor *)R1BA->unk178;
    func_80729B00();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 |= 0x60;
        D_807FBB64 |= 2;
        func_806A2A10(0xDC, 0x2A, R1BS9C->unkA ? R1BS9C->unkA : 10, &D_807FBB64);
        if (R1BS9C->unkA != 0) {
            R1BS90->unk2E = 0xF;
        } else {
            R1BS90->unk2E = 0x78;
        }
        if (R1BS9C->unkA != 0) {
            c->unk18 = R1BS9C->unkA;
        } else {
            c->unk18 = 10.0f;
        }
    }
    if (R1BS90->unk2E != 0) {
        if (func_8061CB50() == 0) {
            R1BS90->unk2E = R1BS90->unk2E - 1;
        }
        if (R1BS90->unk2E != 0) {
            return;
        }
        D_807FBB40->unk154 = 0x23;
        D_807FBB40->unk155[0] = 0;
        func_80609140(0x1A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
        actorSetStateTwo(D_807FBB40->unk11C);
        D_807FBB68 |= 1;
        D_807FBB64 |= 2;
    }
    if (((Actor *)D_807FBB40->unk11C)->unk154 == 5 && D_807FBB40->unk154 != 0x11) {
        if (D_807FDC94->unkFC != 0) {
            D_807FDC94->unkE6 = func_80672A70(D_807FDC94->unkF4, D_807FDC94->unkF6);
        }
        func_8061CC40(0, 6, 5);
        D_807FBB40->unk154 = 0x11;
        D_807FBB40->unk155[0] = 0;
        c->unk10 = (s32)D_807FDC94->unk7C;
        c->unk12 = (s32)(D_807FDC94->unk80 + (u32)D_807FDC94->unk15E);
        c->unk14 = (s32)D_807FDC94->unk84;
        R1BS90->unk2C = 0x14;
    }
    R1BA->unk6E = R1BA->unk6E + 1;
    if (c->unk18 < (f32)R1BA->unk6E) {
        func_80609140(0x15B, 0x7FFF, 63.0f, 1.0f, 0, 0x80);
        R1BA->unk6E = 0;
        if (c->unk18 > 2.0f) {
            c->unk18 -= 0.18;
        }
    }
    if (D_807FBB40->unk154 != 0x11) {
        if (D_807FBB40->unk154 == 0x23 && func_8061CC00() == 0) {
            func_80626F8C(D_807FDC94->unk7C, D_807FDC94->unk80 + (u32)D_807FDC94->unk15E, D_807FDC94->unk84, &sp40, &sp3C, 0, 1.0f, 0);
            func_806B7C74(c, sp40, sp3C);
        }
    } else {
        if (func_8061CC00() == 0) {
            renderCallbacksRegister(func_806B7830, D_807FBB40, 3);
        }
        if (R1BS90->unk2C != 0) {
            R1BS90->unk2C = R1BS90->unk2C - 1;
            if (R1BS90->unk2C == 5) {
                func_80609140(0x175, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        } else {
            func_806B7BB8(c);
            R1BS90->unk2E = 0x64;
            if (R1BS9C->unkA != 0) {
                c->unk18 = R1BS9C->unkA;
            } else {
                c->unk18 = 10.0f;
            }
        }
        func_80626F8C(c->unk10, c->unk12, c->unk14, &c->x, &c->y, 0, 1.0f, 0);
    }
    if (func_8061CC00() == 0) {
        renderCallbacksRegister(func_806B76B0, D_807FBB40, 3);
    }
}
