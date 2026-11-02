// func_806C7270 (src/global/CBEA0.c): W4IntA: stage 6, 6 diff lines (was 9). New lever: named k = t & 1 + no-code 'k = k & 0xFF;' FAKE (adds uopt references) fixed lui t4/addiu la ring temps (9 -> 6). Left: sra a0 (t>>1 candidate coloured a0) vs target ring t9 + andi a0 (k not a candidate: ours andi t1), mul.s f8 operand order (x0*diff vs diff*x0; swapping the source operand fixes it but reverts the integer part to 11). Tried: k type x nocode defs (1-2) x position (4.9k), frac/x0 spelling x statement order grid (1.3k), no-code defs on t/e/frac/x0/k at every point (700), deadsweep 3.9k dead tests.
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
            k = t & 1;
            k = k & 0xFF; // FAKE: no-code def, adds uopt references to k (moves lui/la ring temps)
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
