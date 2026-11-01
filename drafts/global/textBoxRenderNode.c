// textBoxRenderNode (src/global/A8400.c): W2Frame: stage 6, 283 insns text, frame 0xF0 match; remaining 6 diff blocks: (1) FP ring in unk0&4 branch: expected mtc1 0.25->f16, add.s f18; ours 0.25->f18 add f16 (mul operands swapped); (2) sinApprox spill temp at sp+0x38 expected, ours 0x3C (hidden-temp order: spill is 5th of 7 hidden words in target, 4th in ours; any extra named/pad word grows frame 0xF0->0xF8). Levers applied this round: split unk0&4 var into fa (load) + res (result) (fixes f0/f2 colouring and frame), dropped named sp38 (sin inline: temp), decl order fa,sp60,sp5C,dl,mdl,res,sp4C. Tried: 8x8 E1/E2 expression spellings, 7! decl perms, pads 1-6 (frame grows), operand order of 0.25 expr (no effect).
#include "common.h"
#include "actor.h"

typedef struct SpriteModel {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x7C];
    /* 0x88 */ f32 unk88;
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

void textBoxRenderNode(s32 *arg0, void *arg1, void *arg2, void *arg3) {
    union { u16 h; u8 b; u8 pad[8]; } spE8;
    f32 spA8[4][4];
    f32 sp68[4][4];
    f32 fa;
    f32 sp60;
    f32 sp5C;
    Gfx *dl;
    SpriteModel *mdl;
    f32 res;
    f32 sp4C;

    dl = (Gfx *) *arg0;
    spE8.h = D_8075A740;
    mdl = &((SpriteDrawNode *) arg3)->unk10;
    guMtxIdentF(spA8);
    if ((mdl->unk0 != 0) && (((SpriteDrawNode *) arg3)->unk2 != 0)) {
        sp60 = (f32) ((SpriteDrawNode *) arg3)->unk0 * 0.5f * 4.0f;
        sp5C = ((SpriteSource *) arg2)->unk18 * 0.5f * 4.0f;
        guTranslateF(sp68, -sp60, -sp5C, 0.0f);
        guMtxCatF(spA8, sp68, spA8);
        mdl->unk88 = (f32) ((f64) mdl->unk88 + 0.320000000000000007);
        if ((mdl->unk0 & 8) != 0) {
            fa = (f32) ((f64) mdl->unk88 * 0.5);
            if (fa <= 6.2831855f) {
                guRotateF(sp68, fa * 57.295776f, 0.0f, 0.0f, 1.0f);
                guMtxCatF(spA8, sp68, spA8);
            }
        }
        if ((mdl->unk0 & 4) != 0) {
            fa = mdl->unk88;
            if (fa <= 6.2831855f) {
                res = (0.25f * (sinApprox(fa - 1.5707964f) + 1.0f)) + 1.0f;
            } else {
                res = 1.0f;
            }
            guScaleF(sp68, res, res, 1.0f);
            guMtxCatF(spA8, sp68, spA8);
        }
        if ((mdl->unk0 & 2) != 0) {
            sp4C = (4.0f * sinApprox(mdl->unk88)) * ((20.0f - (f32) ((randomNonNegative() >> 15) % 40)) / 20.0f);
            guTranslateF(sp68, sp4C, (4.0f * sinApprox(mdl->unk88)) * ((20.0f - (f32) ((randomNonNegative() >> 15) % 40)) / 20.0f), 0.0f);
            guMtxCatF(spA8, sp68, spA8);
        }
        guTranslateF(sp68, sp60, sp5C, 0.0f);
        guMtxCatF(spA8, sp68, spA8);
    }
    guScaleF(sp68, 1.0, 1.0, 1.0);
    guMtxCatF(spA8, sp68, spA8);
    guTranslateF(sp68, (f32) (((f64) ((DrawPos *) arg1)->unk44 + (f64) ((SpriteDrawNode *) arg3)->unk4) * 4.0), (f32) (((f64) ((DrawPos *) arg1)->unk48 + (f64) ((SpriteDrawNode *) arg3)->unk8) * 4.0), 0.0f);
    guMtxCatF(spA8, sp68, spA8);
    guMtxF2L(spA8, (Mtx *) ((u8 *) mdl + (D_807444FC << 6) + 8));
    gSPMatrix(dl++, (u8 *) mdl + (D_807444FC << 6) + 8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 0x28, 0x28, 0xFF, ((SpriteDrawNode *) arg3)->unk3);
    spE8.b = mdl->unk2;
    *arg0 = (s32) textDrawStringVtx(dl, 6, 0, 0, (u16 *) &spE8, 0);
}
