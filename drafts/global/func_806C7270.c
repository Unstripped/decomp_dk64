// func_806C7270 (src/global/CBEA0.c): Stage 6 (QS2 revisit 2): shape=0, 9 text rows all register-only: target sra->t9 (uncolored ring temp) + andi->a0 (colored cand, hoisted into beqz delay slot), ours sra->a0 (cand 85 colored) + andi->t9 (ring, cand 95 never colored); lui hi(D_8075075C) t4 vs t2; sll t2 vs t1; first mul.s operands (frac first with in-expr '(x0 = frac)'). Retried (all same/worse): inline D_8075075C[t>>1] w/o e, e after frac, base ptr var before if, (x0=frac) in 1st/2nd mul, unnamed t, t as register/u32/s16, decl order, int var k = t&1 before the if (k stays ring temp, sra still a0), deadsweep round 1 with locals (3752 variants, none better), prior permuter 2x600s.
typedef struct R1C2CB_Entry {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s8 unk4;
    /* 0x5 */ s8 unk5;
} R1C2CB_Entry;

typedef struct R1C2CB_Pair {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ f32 unk4;
} R1C2CB_Pair;

extern Actor *D_807FBB40;
extern s8 D_80750754;
extern s16 D_80750758;
extern R1C2CB_Entry D_807506D0[];
extern s8 D_807506D5[];
extern R1C2CB_Pair D_8075075C[];
extern s16 D_807FC8E0;
extern s16 D_807FC8E2;
extern s16 D_807FC8E4;
extern f32 D_807FC8E8;
extern f32 D_807FC8EC;
extern u8 *D_807FC8F0;

u8 *assetLoad(s32, s32, s32, s32);
void renderCallbacksRegister(void *, void *, s32);
Gfx *func_806C75A4(Gfx *, Actor *);

void func_806C7270(void) {
    f32 frac;
    f32 x0;
    f32 y0;
    R1C2CB_Pair *e;
    Actor *actor;
    s32 i;
    s32 t;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FC8F0 = assetLoad(0x13, 7, 1, 1);
        D_807FC8E0 = 0;
        for (i = 0; D_807FC8F0[i] != 0x2A; i++) {
            if (D_807FC8F0[i] == 0xA) {
                D_807FC8F0[i] = 0;
                D_807FC8E0++;
            }
        }
        if (D_80750754 == -2) {
            D_807FC8E4 = 0x320;
            D_80750754 = -1;
            D_807FC8E2 = 0;
            D_807FC8E8 = 0;
        } else if (D_80750754 == -1) {
            D_807FC8E4 = 0x3C;
            D_807FC8E2 = 0;
            D_807FC8E8 = 0;
        }
    }
    actor = D_807FBB40;
    if (D_807FC8E2 > 0) {
        D_807FC8E2--;
    }
    if (D_807FC8E2 == 0) {
        D_807FC8E2 = 0;
        D_807FC8E4--;
        if (D_807FC8E4 <= 0) {
            if (D_80750754 >= 0) {
                D_80750758 += D_807506D5[D_80750754 * 6];
            }
            if (D_80750758 >= D_807FC8E0) {
                D_80750758 = 0;
            }
            D_80750754++;
            D_807FC8E2 = D_807506D0[D_80750754].unk0;
            D_807FC8E4 = D_807506D0[D_80750754].unk2;
        }
    }
    if (D_807FC8E2 < 0xB) {
        D_807FC8E8 -= 0.1f;
        if (D_807FC8E8 < 0.0f) {
            D_807FC8E8 = 0.0f;
        }
        D_807FC8EC = 1;
    } else {
        t = D_807506D0[D_80750754].unk0 - D_807FC8E2;
        if ((t >> 1) < 0x16) {
            e = &D_8075075C[t >> 1];
            frac = (f64)(f32)(t & 1) * 0.5;
            D_807FC8E8 = e[0].unk0 + (e[1].unk0 - e[0].unk0) * (x0 = frac);
            D_807FC8EC = e[0].unk4 + (e[1].unk4 - e[0].unk4) * x0;
        } else {
            D_807FC8E8 = 1.0f;
            D_807FC8EC = 1.0f;
        }
    }
    renderCallbacksRegister(func_806C75A4, actor, 3);
}
