// func_806A370C (src/global/A8400.c): stage 6 (SA84a): best = arg3 used directly (no node local; a0-a3 all homed, frame 0xF0 ok), u8 spE8[8] buffer (sh/sb at 0xE8), 3x gbi-style SA84a_GFX(dl++,..) macro puts dl in s3. Remaining: s0/s1 swap (&spA8 s0, mdl s1 expected), stack slots of sp60/sp5C/sp4C/sp38 (need 1+3+4 reserved words, hidden temp word count 1 too high so pads grow frame), 0.0f args as int 0
typedef struct SpriteModel {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x8C];
    /* 0x98 */ f32 unk98;
} SpriteModel;

typedef struct SpriteDrawNode {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x4];
    /* 0x10 */ SpriteModel unk10;
} SpriteDrawNode;

typedef struct SpriteSource {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
} SpriteSource;

typedef struct DrawPos {
    /* 0x00 */ u8 pad0[0x44];
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
} DrawPos;

extern u8 D_807444FC;
extern u16 D_8075A740;

f32 sinApprox(f32);
s32 randomNonNegative(void);
Gfx *textDrawStringVtx(Gfx *, s32, s32, s32, u16 *, s32);

#define SA84a_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

void func_806A370C(s32 *arg0, void *arg1, void *arg2, void *arg3) {
    u8 spE8[8];
    f32 spA8[4][4];
    f32 sp68[4][4];
    f32 sp60;
    f32 sp5C;
    f32 sp4C;
    f32 tmp;
    SpriteModel *mdl;
    Gfx *dl;
    f32 sp38;

    dl = (Gfx *) *arg0;
    *(u16 *) spE8 = D_8075A740;
    guMtxIdentF(spA8);
    mdl = &((SpriteDrawNode *) arg3)->unk10;
    if ((mdl->unk0 != 0) && (mdl->unk2 != 0)) {
        sp60 = (f32) ((SpriteDrawNode *) arg3)->unk0 * 0.5f * 4.0f;
        sp5C = ((SpriteSource *) arg2)->unk18 * 0.5f * 4.0f;
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
                tmp = (0.25f * (sinApprox(tmp - 1.5707964f) + 1.0f)) + 1.0f;
            } else {
                tmp = 1.0f;
            }
            guScaleF(sp68, tmp, tmp, 1.0f);
            guMtxCatF(spA8, sp68, spA8);
        }
        if ((mdl->unk0 & 2) != 0) {
            sp38 = sinApprox(mdl->unk98);
            sp4C = ((20.0f - (f32) ((randomNonNegative() >> 15) % 40)) / 20.0f) * (4.0f * sp38);
            sp38 = sinApprox(mdl->unk98);
            guTranslateF(sp68, sp4C, ((20.0f - (f32) ((randomNonNegative() >> 15) % 40)) / 20.0f) * (4.0f * sp38), 0.0f);
            guMtxCatF(spA8, sp68, spA8);
        }
        guTranslateF(sp68, sp60, sp5C, 0.0f);
        guMtxCatF(spA8, sp68, spA8);
    }
    guScaleF(sp68, 1.0f, 1.0f, 1.0f);
    guMtxCatF(spA8, sp68, spA8);
    guTranslateF(sp68, (f32) (((f64) ((DrawPos *) arg1)->unk44 + (f64) ((SpriteDrawNode *) arg3)->unk4) * 4.0), (f32) (((f64) ((DrawPos *) arg1)->unk48 + (f64) ((SpriteDrawNode *) arg3)->unk8) * 4.0), 0.0f);
    guMtxCatF(spA8, sp68, spA8);
    guMtxF2L(spA8, (Mtx *) ((u8 *) mdl + (D_807444FC << 6) + 8));
    SA84a_GFX(dl++, 0xDA380003, (u32) ((u8 *) mdl + (D_807444FC << 6) + 8));
    SA84a_GFX(dl++, 0xE7000000, 0);
    SA84a_GFX(dl++, 0xFA000000, ((SpriteDrawNode *) arg3)->unk3 | 0x2828FF00);
    spE8[0] = mdl->unk2;
    *arg0 = (s32) textDrawStringVtx(dl, 6, 0, 0, (u16 *) spE8, 0);
}
