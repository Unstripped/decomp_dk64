// func_806A370C (src/global/A8400.c): stage 6: instruction stream matches modulo regalloc/stack. Expected frame 0xF0 with an arg home area for all four params ABOVE the frame (sw a0,0xF0 .. sw a3,0xFC) and matrices at 0x68/0xA8; built frame 0xE0 with a0-a2 homed at 0xE0-0xE8 and no a3 home, matrices at 0x5C/0x9C. Local declaration order spE8,spA8,sp68,sp60,sp5C,sp4C,sp38 chosen to match ascending offsets but the base offset stays 0x10-0x20 low.
typedef struct A8R2bMdl {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x8C];
    /* 0x98 */ f32 unk98;
} A8R2bMdl;

typedef struct A8R2bDrawNode {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x4];
    /* 0x10 */ A8R2bMdl unk10;
} A8R2bDrawNode;

typedef struct A8R2bSrc {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
} A8R2bSrc;

typedef struct A8R2bPos {
    /* 0x00 */ u8 pad0[0x44];
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
} A8R2bPos;

extern u8 D_807444FC;
extern u16 D_8075A740;

f32 func_80612D1C(f32);
s32 func_80611A44(void);
Gfx *textDrawStringVtx(Gfx *, s32, s32, s32, u16 *, s32);

void func_806A370C(s32 *arg0, void *arg1, void *arg2, void *arg3) {
    u16 spE8;
    f32 spA8[4][4];
    f32 sp68[4][4];
    f32 sp60;
    f32 sp5C;
    f32 sp4C;
    f32 sp38;
    f32 tmp;
    A8R2bDrawNode *node;
    A8R2bMdl *mdl;
    Gfx *dl;

    dl = (Gfx *) *arg0;
    node = arg3;
    spE8 = D_8075A740;
    guMtxIdentF(spA8);
    mdl = &node->unk10;
    if ((mdl->unk0 != 0) && (mdl->unk2 != 0)) {
        sp60 = (f32) node->unk0 * 0.5f * 4.0f;
        sp5C = ((A8R2bSrc *) arg2)->unk18 * 0.5f * 4.0f;
        guTranslateF(sp68, -sp60, -sp5C, 0.0f);
        guMtxCatF(spA8, sp68, spA8);
        mdl->unk98 = (f32) ((f64) mdl->unk98 + 0.320000000000000007);
        if ((mdl->unk0 & 8) != 0) {
            tmp = (f32) ((f64) mdl->unk98 * 0.5);
            if (tmp <= 6.2831855f) {
                guRotateF(sp68, tmp * 57.295776f, 0.0f, 0.0f, 1.0f);
                guMtxCatF(spA8, sp68, spA8);
            }
        }
        if ((mdl->unk0 & 4) != 0) {
            tmp = mdl->unk98;
            if (tmp <= 6.2831855f) {
                tmp = (0.25f * (func_80612D1C(tmp - 1.5707964f) + 1.0f)) + 1.0f;
            } else {
                tmp = 1.0f;
            }
            guScaleF(sp68, tmp, tmp, 1.0f);
            guMtxCatF(spA8, sp68, spA8);
        }
        if ((mdl->unk0 & 2) != 0) {
            sp38 = func_80612D1C(mdl->unk98);
            sp4C = ((20.0f - (f32) ((func_80611A44() >> 15) % 40)) / 20.0f) * (4.0f * sp38);
            sp38 = func_80612D1C(mdl->unk98);
            guTranslateF(sp68, sp4C, ((20.0f - (f32) ((func_80611A44() >> 15) % 40)) / 20.0f) * (4.0f * sp38), 0.0f);
            guMtxCatF(spA8, sp68, spA8);
        }
        guTranslateF(sp68, sp60, sp5C, 0.0f);
        guMtxCatF(spA8, sp68, spA8);
    }
    guScaleF(sp68, 1.0f, 1.0f, 1.0f);
    guMtxCatF(spA8, sp68, spA8);
    guTranslateF(sp68, (f32) (((f64) ((A8R2bPos *) arg1)->unk44 + (f64) node->unk4) * 4.0), (f32) (((f64) ((A8R2bPos *) arg1)->unk48 + (f64) node->unk8) * 4.0), 0.0f);
    guMtxCatF(spA8, sp68, spA8);
    guMtxF2L(spA8, (Mtx *) ((u8 *) mdl + (D_807444FC << 6) + 8));
    dl[0].words.w0 = 0xDA380003;
    dl[0].words.w1 = (u32) ((u8 *) mdl + (D_807444FC << 6) + 8);
    dl[1].words.w0 = 0xE7000000;
    dl[1].words.w1 = 0;
    dl[2].words.w0 = 0xFA000000;
    dl[2].words.w1 = node->unk3 | 0x2828FF00;
    spE8 = mdl->unk2;
    *arg0 = (s32) textDrawStringVtx(&dl[3], 6, 0, 0, &spE8, 0);
}
