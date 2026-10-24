// func_806A4284 (src/global/A8400.c): stage 6: identical instruction sequence but uopt swaps state<->node (s2<->s1), cascading into temp/FP regs; frame 0x148 and every stack offset (dl 0x98, start 0x94, spA0 0xA0, spE0 0xE0, half 0x132, stop 0x13B) already reproduced via the pad* locals
typedef struct A8R2bBounds {
    /* 0x000 */ u8 pad0[0x270];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ u8 pad278[0x2F0 - 0x278];
} A8R2bBounds;

extern A8R2bBounds *D_807FC924;
extern u8 D_807FC929;
extern u8 D_807444FC;
extern Gfx D_1000118;
extern Mtx D_20000C0;

void *func_80610FE8(s32);
void heapFreeDeferred(void *);
s32 func_806A3E9C();

typedef struct L7bNode L7bNode;

struct L7bNode {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ L7bNode *unk1C;
};

typedef struct L7bState {
    /* 0x000 */ u8 pad0[0x4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x4];
    /* 0x00C */ L7bNode *unkC;
    /* 0x010 */ u8 unk10;
    /* 0x011 */ u8 pad11[0xB];
    /* 0x01C */ u8 unk1C;
    /* 0x01D */ u8 unk1D;
    /* 0x01E */ u8 pad1E[0x2];
    /* 0x020 */ f32 unk20;
    /* 0x024 */ u8 pad24[0x10];
    /* 0x034 */ u8 *unk34;
    /* 0x038 */ u8 pad38[0x8];
    /* 0x040 */ f32 unk40;
    /* 0x044 */ f32 unk44;
    /* 0x048 */ f32 unk48;
    /* 0x04C */ f32 unk4C;
    /* 0x050 */ f32 unk50;
} L7bState;

Gfx *func_806A4284(Gfx *arg0, Actor *arg1) {
    /* Unused slots below/above the live locals: they reproduce the original
       stack frame (0x148, dl 0x98, start 0x94, spA0 0xA0, spE0 0xE0,
       half 0x132, stop 0x13B).  Only the frame layout depends on them. */
    s32 padA;
    f32 padH[2];
    u8 stop;
    s16 padC;
    f32 padM;
    s16 half;
    f64 padE;
    Gfx *padF;
    u8 padB;
    f32 spE0[4][4];
    f32 spA0[4][4];
    s32 padN;
    Gfx *dl;
    Gfx *start;
    L7bState *state;
    L7bNode *node;
    f32 scale;
    f32 alpha;
    s32 i;

    state = arg1->unk174;
    node = state->unkC;
    stop = 0;
    dl = func_80610FE8(0x4000);
    heapFreeDeferred(dl);
    start = dl;
    WRITE_GFX(dl++, 0xDE000000, (u32) &D_1000118);
    WRITE_GFX(dl++, 0xDA380007, (u32) &D_20000C0);
    WRITE_GFX(dl++, 0xE7000000, 0);
    WRITE_GFX(dl++, 0xE200001C, 0x504240);
    WRITE_GFX(dl++, 0xE3000A01, 0);
    WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(dl++, 0xD9000000, 0);
    WRITE_GFX(dl++, 0xD9FFFFFF, 0x200004);
    half = state->unk1C / 2;
    scale = (f32) ((1.0 - (f64) state->unk40 * 0.5) * (f64) state->unk20 * 1.9f * 4.0);
    guTranslateF(spE0, -48.0f, -32.0f, 0.0f);
    guScaleF(spA0, scale, scale, 1.0f);
    guMtxCatF(spE0, spA0, spE0);
    guTranslateF(spA0, arg1->unk7C * 4.0f, arg1->unk80 * 4.0f, 0.0f);
    guMtxCatF(spE0, spA0, spE0);
    guMtxF2L(spE0, (Mtx *) (state->unk34 + (D_807444FC << 6)));
    WRITE_GFX(dl++, 0xE7000000, 0);
    WRITE_GFX(dl++, ((s32) ((f32) D_807FC924->unk272 * 4.0f) & 0xFFF) | 0xED000000 | (((s32) ((f32) D_807FC924->unk270 * 4.0f) & 0xFFF) << 12),
              (((s32) ((f32) D_807FC924->unk274 * 4.0f) & 0xFFF) << 12) | ((s32) ((f32) D_807FC924->unk276 * 4.0f) & 0xFFF));
    dl = (Gfx *) func_806A3E9C(dl, state, half);
    alpha = state->unk20 * 150.0f * 2.0f;
    if (alpha > 150.0f) {
        alpha = 150.0f;
    }
    dl = func_806A3C6C(dl, (s32) (state->unk34 + (D_807444FC << 6)), (u8) alpha, half);
    if (state->unk1D != 0) {
        WRITE_GFX(dl++, ((s32) (state->unk48 * 4.0f) & 0xFFF) | 0xED000000 | (((s32) (state->unk44 * 4.0f) & 0xFFF) << 12),
                  (((s32) (state->unk4C * 4.0f) & 0xFFF) << 12) | ((s32) (state->unk50 * 4.0f) & 0xFFF));
    }
    i = 0;
    while (((s32) state->unk10 >= i) && (node != NULL) && (stop == 0)) {
        WRITE_GFX(dl++, 0xE7000000, 0);
        func_806A3B78((s32 *) &dl, (M7Actor *) state, (M7Sub *) node, (u8) (i == state->unk10), &stop);
        if (stop == 0) {
            node = node->unk1C;
        }
        i++;
    }
    WRITE_GFX(dl++, 0xE7000000, 0);
    if (state->unk1D != 0) {
        WRITE_GFX(dl++, ((s32) ((f32) D_807FC924[D_807FC929].unk272 * 4.0f) & 0xFFF) | 0xED000000 | (((s32) ((f32) D_807FC924[D_807FC929].unk270 * 4.0f) & 0xFFF) << 12),
                  (((s32) ((f32) D_807FC924[D_807FC929].unk274 * 4.0f) & 0xFFF) << 12) | ((s32) ((f32) D_807FC924[D_807FC929].unk276 * 4.0f) & 0xFFF));
    }
    state->unk1C = state->unk1C + 1;
    state->unk1C = state->unk1C % 16;
    WRITE_GFX(dl++, 0xDF000000, 0);
    arg0->words.w0 = 0xDE000000;
    arg0->words.w1 = (u32) start;
    return arg0 + 1;
}
