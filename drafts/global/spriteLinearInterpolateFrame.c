// spriteLinearInterpolateFrame (src/global/CBEA0.c): stage 6 park, full=6 text=6 reloc=0 shape=0; ugen record edit (292/293 r1=25, 300/302 r1=4, del 301, 310 r2=25, 318 r2=38/r3=32) gives full=0; target kept t>>1 in ring temp t9 because k (t&1) took a0; direct frac matches mul.s but drops as1 lui t4 hoist
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

void spriteLinearInterpolateFrame(void) {
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
            D_807FC8EC = e[0].unk4 + (e[1].unk4 - e[0].unk4) * frac;
        } else {
            D_807FC8E8 = 1.0f;
            D_807FC8EC = 1.0f;
        }
    }
    renderCallbacksRegister(func_806C75A4, actor, 3);
}
