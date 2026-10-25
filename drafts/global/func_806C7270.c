// func_806C7270 (src/global/CBEA0.c): Stage 6, 9 diff pairs (was 17): remaining sra/andi regs (target: sra->t9 temp, andi->a0; ours sra->a0 cand 85, andi->t9), lui hi(D_8075075C) t2 vs t4 (position now matches), sll temp reg, first mul.s operand order. Found: no x0/y0 loads (e[0] repeated, 'e0 + diff*frac') fixes y0/x0 load order + add order; in-expression '(x0 = frac)' on the first mul and 'x0' in the second hoists the lui into place (statement 'x0 = frac;' does nothing, dead-store dropped) but flips first mul.s operands. Temp pool order seen: t4,t9,t2,t1; target has sra/slti uncolored temp and andi colored a0: 85 (t>>1) must lose a0 - k/i locals, odd local, t&=1, if-swap, e/frac before the if, flat f32 array, 2x600s permuter all failed. Reloc-only D_8075C3E0 vs .rodata.
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

u8 *func_8066B0F8(s32, s32, s32, s32);
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
        D_807FC8F0 = func_8066B0F8(0x13, 7, 1, 1);
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
