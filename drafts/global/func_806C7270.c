// func_806C7270 (src/global/CBEA0.c): Player rev8: re-derived: remaining diff = N=t>>1 is a coloured uopt candidate (a0, adjsave 1.5) while the target keeps it a ugen ring temp (t9) shared by compare and sll across the beqz, plus mul.s operand order (frac direct = diff*frac fixes it but then lui t4 / sll t9 move: full 11). Tried new: local `j = t >> 1` of 6 widths and assign-in-condition (count +2, full 47-52), typed shift counts (`>> 1U` etc. give 2 sra), mini TU study (every spelling of compare+index keeps N coloured; a call between makes it a0 with spills), frac direct + joins. No spelling leaves N un-shared with one sra. PREVIOUS: W2Int 2026-11-03 (revisit 7 wave 2): stage 6, 6 diff lines, score unchanged (full=6 shape=0). NEW: `k = (u8)(t & 1);` replaces the `k = k & 0xFF` FAKE at the same score 6 (FAKE-free). Re-derived: target sra t9/slti/andi a0/sll t2 = `t>>1` is a ugen RING temp (no uopt candidate) and `andi a0`; ours has candidate ushr{269} (adjsave 1.5, forbidden v0/v1) coloured a0, so andi falls to t1. mul.s operand order is fixed by using `frac` directly (no `(x0 = frac)` assignment-in-expression: target mul.s f6,f0) but then the `lui t4` hoist moves; adding `if (frac == 0) {}` restores the hoist and forces a `swc1 f0,44(sp)` into the nop slot (full 6, shape 1: 5 sra-block lines + 1). Tried new: cast/wrapper chains {s32,u32,u8,s16,u16,s8,&0xFF,&0x7FFF,+0,|0} at compare x index sites (121), t/k declared types 6x6 x 4 k spellings, k/frac/e statement order x 4 frac spellings x 4 use forms (240), 420 s dead-test annealer on the frac-direct form. Untested: any spelling that leaves t>>1 un-shared yet emits one sra (known: (t&~1)*4 and (u32)t>>1 give two sra).
typedef struct R1C2CB_Entry {
    s16 unk0;
    s16 unk2;
    s8 unk4;
    s8 unk5;
} R1C2CB_Entry;

extern R1C2CB_Entry D_807506D0[];

typedef struct R1C2CB_Pair {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ f32 unk4;
} R1C2CB_Pair;

extern Actor *D_807FBB40;
extern s8 D_80750754;
extern s16 D_80750758;
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
    s32 k;

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
            k = (u8)(t & 1);
            frac = (f64)(f32)k * 0.5;
            D_807FC8E8 = e[0].unk0 + (e[1].unk0 - e[0].unk0) * (x0 = frac);
            D_807FC8EC = e[0].unk4 + (e[1].unk4 - e[0].unk4) * x0;
        } else {
            D_807FC8E8 = 1.0f;
            D_807FC8EC = 1.0f;
        }
    }
    renderCallbacksRegister(func_806C75A4, actor, 3);
}
