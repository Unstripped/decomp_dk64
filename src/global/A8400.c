#include "common.h"
#include "actor.h"

void func_806A3700(s32 arg0, s32 arg1) {
}

#ifdef NON_MATCHING
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

void func_806A370C(s32 *arg0, void *arg1, void *arg2, void *arg3) {
    u16 spE8;
    f32 spA8[4][4];
    f32 sp68[4][4];
    f32 sp60;
    f32 sp5C;
    f32 sp4C;
    f32 sp38;
    f32 tmp;
    SpriteDrawNode *node;
    SpriteModel *mdl;
    Gfx *dl;

    dl = (Gfx *) *arg0;
    node = arg3;
    spE8 = D_8075A740;
    guMtxIdentF(spA8);
    mdl = &node->unk10;
    if ((mdl->unk0 != 0) && (mdl->unk2 != 0)) {
        sp60 = (f32) node->unk0 * 0.5f * 4.0f;
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
    guTranslateF(sp68, (f32) (((f64) ((DrawPos *) arg1)->unk44 + (f64) node->unk4) * 4.0), (f32) (((f64) ((DrawPos *) arg1)->unk48 + (f64) node->unk8) * 4.0), 0.0f);
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A370C.s")
#endif

void func_806A370C(s32 *, void *, void *, void *);

typedef struct DrawActor {
    /* 0x00 */ u8 pad0[0x11];
    /* 0x11 */ u8 unk11;
} DrawActor;

typedef struct DrawNode {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ struct DrawNode *unkA0;
} DrawNode;

typedef struct DrawListHead {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[0xB];
    /* 0x0C */ struct DrawNode *unkC;
} DrawListHead;

void renderAppendNodeChain(s32 *arg0, DrawActor *arg1, DrawListHead *arg2, u8 arg3, u8 *arg4) {
    s32 sp44;
    s32 i;
    DrawNode *node;

    sp44 = *arg0;
    node = arg2->unkC;
    i = 0;
    while (node != NULL && *arg4 == 0) {
        if (arg3 && (i == arg1->unk11)) {
            *arg4 = 1;
        }
        if (arg2->unk0 & 1) {
            func_806A370C(&sp44, arg1, arg2, node);
        }
        node = node->unkA0;
        i++;
    }
    *arg0 = sp44;
}

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

s32 texCacheFindOrLoad(s32);
void func_80702464(Gfx **, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, s32, s32);

Gfx *renderTextureSprite(Gfx *arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 tex;

    tex = texCacheFindOrLoad((arg3 + 0x52) & 0xFFFF);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xFA000000, (arg2 & 0xFF) | 0xFFFFFF00);
    WRITE_GFX(arg0++, 0xDA380002, arg1);
    func_80702464(&arg0, tex, 3, 0x60, 0x40, 0x20, 0x20, 0.0f, 0.0f, 96.0f, 64.0f, 0.0f, 0.0f, 1, 8);
    WRITE_GFX(arg0++, 0xD8380002, 0x40);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    return arg0;
}

f32 func_80612790(s16);
f32 func_80612794(s16);

typedef struct MotionAngles {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
} MotionAngles;

void mathAddWaveOffset(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, MotionAngles *arg4) {
    *arg0 += (arg2 * arg3) * 24.0f * func_80612794((s16) ((s16) ((s32) ((f32) arg4->unk38 + (arg2 * 3000.0f))) & 0xFFF));
    *arg1 += (arg2 * arg3) * 16.0f * func_80612790((s16) ((s16) ((s32) ((f32) arg4->unk3A + (arg2 * 3000.0f))) & 0xFFF));
}

extern u8 D_807444FC;

typedef struct SpriteAnim {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 *unk34;
} SpriteAnim;


s32 func_806A3E9C(s32 arg0, SpriteAnim *arg1, s32 arg2) {
    f32 spE8[4][4];
    f32 spA8[4][4];
    f32 spA4;
    f32 spA0;
    u8 cnt;
    u32 i;
    s32 tmp;
    s32 idx;

    cnt = (u8) (u32) ((((f64) arg1->unk20 < 0.320000000000000007) ? (f64) arg1->unk20 : 0.320000000000000007) * 12.5);
    if (arg0 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    i = 1;
    if (D_807444FC == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    idx = 1;
    if (cnt > 0) {
        do {
            spA4 = (f32) ((f64) (arg1->unk2C - arg1->unk24) * ((f64) i * 0.0800000000000000017) + (f64) arg1->unk24);
            spA0 = (f32) ((f64) (arg1->unk30 - arg1->unk28) * ((f64) i * 0.0800000000000000017) + (f64) arg1->unk28);
            guTranslateF(spE8, -48.0f, -32.0f, 0);
            guScaleF(spA8, (f32) (((f64) i * 0.0800000000000000017) * 1.9f * 4.0 * 0.5), (f32) (((f64) i * 0.0800000000000000017) * 1.9f * 4.0 * 0.5), 1.0f);
            guMtxCatF(spE8, spA8, spE8);
            mathAddWaveOffset(&spA4, &spA0, (f32) ((f64) i * 0.0800000000000000017), 1.0f, (MotionAngles *) arg1);
            guTranslateF(spA8, spA4 * 4.0f, spA0 * 4.0f, 0.0f);
            guMtxCatF(spE8, spA8, spE8);
            guMtxF2L(spE8, (Mtx *) (arg1->unk34 + ((idx * 2 + D_807444FC) << 6)));
            tmp = (s32) renderTextureSprite((Gfx *) arg0, (s32) (arg1->unk34 + ((idx * 2 + D_807444FC) << 6)), (u32) ((((f64) (idx * 300) * 0.0800000000000000017) > 150.0) ? 150.0 : ((f64) (idx * 300) * 0.0800000000000000017)), arg2);
            i = (i + 1) & 0xFF;
            idx = i;
            arg0 = tmp;
            if (D_807444FC && D_807444FC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        } while (cnt >= idx);
    }
    return arg0;
}

#ifdef NON_MATCHING
typedef struct ScreenBounds {
    /* 0x000 */ u8 pad0[0x270];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ u8 pad278[0x2F0 - 0x278];
} ScreenBounds;

extern ScreenBounds *D_807FC924;
extern u8 D_807FC929;
extern u8 D_807444FC;
extern Gfx D_1000118;
extern Mtx D_20000C0;

void *heapAlloc(s32);
void heapFreeDeferred(void *);
s32 func_806A3E9C();

typedef struct UINode UINode;

struct UINode {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ UINode *unk1C;
};

typedef struct UIState {
    /* 0x000 */ u8 pad0[0x4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x4];
    /* 0x00C */ UINode *unkC;
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
} UIState;

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
    UIState *state;
    UINode *node;
    f32 scale;
    f32 alpha;
    s32 i;

    state = arg1->unk174;
    node = state->unkC;
    stop = 0;
    dl = heapAlloc(0x4000);
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
    dl = renderTextureSprite(dl, (s32) (state->unk34 + (D_807444FC << 6)), (u8) alpha, half);
    if (state->unk1D != 0) {
        WRITE_GFX(dl++, ((s32) (state->unk48 * 4.0f) & 0xFFF) | 0xED000000 | (((s32) (state->unk44 * 4.0f) & 0xFFF) << 12),
                  (((s32) (state->unk4C * 4.0f) & 0xFFF) << 12) | ((s32) (state->unk50 * 4.0f) & 0xFFF));
    }
    i = 0;
    while (((s32) state->unk10 >= i) && (node != NULL) && (stop == 0)) {
        WRITE_GFX(dl++, 0xE7000000, 0);
        renderAppendNodeChain((s32 *) &dl, (DrawActor *) state, (DrawListHead *) node, (u8) (i == state->unk10), &stop);
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A4284.s")
#endif

void func_8071495C(void);
void func_80714998(s32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714A68(s16, s16, s16, s16);
void *func_80714CC0(void *, f32, f32, f32, f32);
extern void *D_80755390[];

typedef struct SpriteObject {
    /* 0x000 */ u8 pad0[0x340];
    /* 0x340 */ f32 unk340;
    /* 0x344 */ f32 unk344;
    /* 0x348 */ u8 pad348[0x18];
    /* 0x360 */ f32 unk360;
    /* 0x364 */ u8 pad364[9];
    /* 0x36D */ u8 unk36D;
    /* 0x36E */ u8 pad36E[0x20];
    /* 0x38E */ s16 unk38E;
    /* 0x390 */ s16 unk390;
    /* 0x392 */ s16 unk392;
    /* 0x394 */ s16 unk394;
} SpriteObject;

typedef struct SpriteObjectSlot {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ SpriteObject *unk4;
} SpriteObjectSlot;

typedef struct SpriteRow {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[1];
    /* 0x03 */ u8 unk3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ SpriteObjectSlot unk10;
} SpriteRow;

typedef struct SpriteVector {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x28];
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
} SpriteVector;

void func_806A495C(SpriteRow *arg0, SpriteVector *arg1, SpriteVector *arg2) {
    SpriteObjectSlot *slot = &arg0->unk10;
    f32 sp38 = (f32) arg0->unk0 * 0.5f;
    f32 sp34 = arg0->unk4;
    f32 sp30 = arg0->unk8;

    if (slot->unk4 == NULL) {
        func_807149FC(-1);
        func_807149B8(0);
        func_8071495C();
        func_80714998(2);
        func_80714A68((s16) (s32) arg2->unk44, (s16) (s32) arg2->unk48, (s16) (s32) arg2->unk4C,
                      (s16) (s32) arg2->unk50);
        slot->unk4 = func_80714CC0(D_80755390[slot->unk0], 1.0f, arg2->unk44, arg2->unk48, 1);
        if (slot->unk2 != 0) {
            slot->unk4->unk360 *= -1.0f;
        }
    }
    sp34 += sp38;
    slot->unk4->unk340 = (f32) (((f64) arg2->unk44 + sp34) * 4.0);
    slot->unk4->unk344 = (f32) (((f64) arg2->unk48 + (sp30 + (arg1->unk18 * 0.5f))) * 4.0);
    slot->unk4->unk36D = arg0->unk3;
    slot->unk4->unk38E = (s16) (s32) arg2->unk44;
    slot->unk4->unk390 = (s16) (s32) arg2->unk48;
    slot->unk4->unk392 = (s16) (s32) arg2->unk4C;
    slot->unk4->unk394 = (s16) (s32) arg2->unk50;
}

typedef struct SpriteNode {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x94];
    /* 0xA0 */ struct SpriteNode *unkA0;
} SpriteNode;

typedef struct SpriteChainState {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 pad13[0xA];
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 pad1E[0x37];
    /* 0x55 */ u8 unk55;
} SpriteChainState;

typedef struct SpriteHolder {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[7];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ SpriteNode *unkC;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ f32 unk14;
} SpriteHolder;

typedef struct ActorStateView {
    /* 0x000 */ u8 pad0[0x154];
    /* 0x154 */ u8 unk154;
} ActorStateView;

void func_806A4B84(f32 arg0, ActorStateView *arg1, SpriteChainState *arg2, SpriteHolder *arg3, u8 arg4, u8 *arg5) {
    f32 var_fs0;
    s32 var_a0;
    s32 var_s3;
    u8 var_a0_2;
    u8 temp;
    SpriteNode *node;

    node = arg3->unkC;
    var_s3 = 0;
    var_fs0 = ((f64) 136.8f - arg3->unk14) / 2.0;
    while (node != NULL && *arg5 == 0) {
        if (arg4 && var_s3 == arg2->unk11) {
            if (!(arg2->unk55 & 4)) {
                *arg5 = 1;
            }
            if (arg1->unk154 == 1) {
                if (var_s3 == 0 && node->unk2 == 0) {
                    func_806A3700(arg2->unk4, arg3->unk8);
                }
                temp = node->unk2;
                if (temp != 0xFF) {
                    var_a0 = 0x96;
                    if (arg2->unk55 & 2) {
                        var_a0 = (s32) (var_a0 * 0.5);
                    }
                    if (!(arg2->unk55 & 4) && (var_a0 < (0xFF - node->unk2))) {
                        node->unk2 = node->unk2 + var_a0;
                    } else {
                        node->unk2 = 0xFF;
                        if (node->unkA0 != NULL) {
                            arg2->unk11++;
                        } else {
                            arg2->unk11 = 0;
                            arg2->unk10++;
                            *arg5 = 1;
                            if (arg3->unk10 != 0) {
                                arg1->unk154 = 3;
                                arg2->unk12 = arg3->unk10;
                            }
                        }
                    }
                }
            }
        }
        if (arg2->unk1D < node->unk2) {
            var_a0_2 = arg2->unk1D;
        } else {
            var_a0_2 = node->unk2;
        }
        node->unk4 = var_fs0;
        node->unk8 = arg0;
        node->unk3 = var_a0_2;
        if (arg3->unk0 & 2) {
            func_806A495C((SpriteRow *) node, (SpriteVector *) arg3, (SpriteVector *) arg2);
        }
        var_fs0 += (f32) node->unk0;
        node = node->unkA0;
        var_s3++;
    }
}

#ifdef NON_MATCHING
typedef struct ChainNode ChainNode;

typedef struct ChainState {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ ChainNode *unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 pad13;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x4];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[0x1C];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
} ChainState;

struct ChainNode {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ ChainNode *unk1C;
};

void func_8070D9AC(ChainNode *);
void func_8070E808(Actor *, void *);

void func_806A4DDC(Actor *arg0) {
    ChainState *state;
    ChainNode *node;
    ChainNode *cur;
    f32 acc;
    f32 dt;
    f32 sum;
    f32 lim;
    f64 wide;
    f64 high;
    u8 stop;
    u8 mode;
    s32 i;

    state = arg0->unk174;
    node = state->unkC;
    stop = 0;
    dt = state->unk20;
    lim = (f32) ((f64) (1.0f - dt) * 1.47058823529411775);
    if (lim > 1.0f) {
        lim = 1.0f;
    }
    state->unk40 = lim;
    mathAddWaveOffset(&arg0->unk7C, &arg0->unk80, dt, lim, (MotionAngles *) state);
    wide = (f64) (state->unk20 * 136.8f) * 0.5;
    state->unk44 = arg0->unk7C - wide;
    high = (f64) (state->unk20 * 79.799995f) * 0.5;
    state->unk48 = arg0->unk80 - high;
    state->unk4C = arg0->unk7C + wide;
    state->unk50 = arg0->unk80 + high;
    lim = (f32) D_807FC924->unk270;
    if (lim < state->unk44) {
        state->unk44 = state->unk44;
    } else {
        state->unk44 = lim;
    }
    sum = (f32) D_807FC924->unk272;
    if (sum < state->unk48) {
        state->unk48 = state->unk48;
    } else {
        state->unk48 = sum;
    }
    dt = (f32) D_807FC924->unk274;
    if (state->unk4C < dt) {
        state->unk4C = state->unk4C;
    } else {
        state->unk4C = dt;
    }
    sum = (f32) D_807FC924->unk276;
    if (state->unk50 < sum) {
        state->unk50 = state->unk50;
    } else {
        state->unk50 = sum;
    }
    acc = state->unk14;
    i = 0;
    while (((s32) state->unk10 >= i) && (node != NULL) && (stop == 0)) {
        cur = node;
        dt = cur->unk18;
        sum = acc + dt;
        if (((f64) sum > 73.79999542236328) && (arg0->unk154 == 1)) {
            arg0->unk154 = 2;
            state->unk18 = (f32) ((f64) sum - 73.79999542236328);
            stop = 1;
        } else if ((sum < 0.0f) && (arg0->unk154 == 2)) {
            state->unk14 = state->unk14 + dt;
            state->unk10 = state->unk10 - 1;
            state->unkC = cur->unk1C;
            acc = sum;
            node = cur->unk1C;
            func_8070D9AC(cur);
            i--;
        } else {
            func_806A4B84(acc, (ActorStateView *) arg0, (SpriteChainState *) state, (SpriteHolder *) cur, (u8) (i == state->unk10), &stop);
            if (stop == 0) {
                node = node->unk1C;
                acc = sum;
            }
        }
        i++;
    }
    mode = arg0->unk154;
    if (mode == 3) {
        if (state->unk12 != 0) {
            state->unk12 = state->unk12 - 1;
            mode = arg0->unk154;
        } else {
            mode = arg0->unk154 = 1;
        }
    }
    if ((mode == 1) && (node == NULL)) {
        func_8070E808(arg0, state->unk4);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A4DDC.s")
#endif

#ifdef NON_MATCHING
typedef struct SpriteFrameNode {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ u8 unk2C;
} SpriteFrameNode;

typedef struct SpriteActorData {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[0x54];
    /* 0x58 */ u32 unk58;
    /* 0x5C */ u8 pad5C[0x20];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0xD6];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[0x1D];
    /* 0x17C */ SpriteFrameNode *unk17C;
} SpriteActorData;

typedef struct SpriteSub {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ SpriteActorData *unk4;
    /* 0x08 */ u8 pad8[0x18];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[0x8];
    /* 0x3C */ u8 unk3C;
} SpriteSub;

typedef struct PositionView {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
} PositionView;

typedef struct MapBounds {
    /* 0x000 */ u8 pad0[0x270];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
} MapBounds;

extern u8 D_807FC929;
extern s16 D_80744490;

void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
s32 func_80613448(void *);
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

#define CURRENT_BOUNDS ((MapBounds *) ((u8 *) D_807FC924 + (D_807FC929 * 0x2F0)))
#define CLAMP_TO_BOUNDS(x, l, h) ((x) < (l) ? (l) : ((h) < (x) ? (h) : (x)))

struct SpriteBehaviour;

void func_806A5174(Actor *arg0, struct SpriteBehaviour *arg1, f32 arg2) {
    f32 sp7C, sp78;
    s32 sp74;
    f32 lo, hi;
    f32 sp68, sp64, sp60;

    sp74 = 0;
    switch (((SpriteSub *) arg1)->unk4->unk58) {
    case 0x22:
    case 0x2E:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
    case 0xDA:
    case 0x100:
        ((SpriteSub *) arg1)->unk3C = 1;
        ((SpriteSub *) arg1)->unk24 = (f32) CURRENT_BOUNDS->unk274;
        ((SpriteSub *) arg1)->unk28 = (f32) CURRENT_BOUNDS->unk276;
        break;
    case 0xFE:
        sp74 = ((SpriteSub *) arg1)->unk4->unk17C->unk2C;
        break;
    default:
        if (((SpriteSub *) arg1)->unk4->unk0 != 0) {
            switch (func_80613448(((SpriteSub *) arg1)->unk4)) {
            case 0x11:
            case 0x12:
            case 0x1D:
            case 0x1F:
            case 0x2E:
            case 0x3D:
            case 0x45:
            case 0x5E:
            case 0x62:
                sp74 = 1;
                break;
            case 0x13:
            case 0x17:
            case 0x3E:
            case 0x56:
            case 0x65:
                sp74 = 2;
                break;
            case 0x35:
                sp74 = 3;
                break;
            case 0x1:
            case 0x2:
            case 0x3:
            case 0x4:
            case 0x5:
            case 0x6:
            case 0x7:
            case 0x8:
            case 0xA:
            case 0xB:
            case 0xC:
            case 0xD:
            case 0xE:
            case 0xF:
            case 0x10:
                sp74 = 6;
                break;
            case 0x18:
                sp74 = 9;
                break;
            }
        }
        break;
    }
    if ((((SpriteSub *) arg1)->unk4->unk0 == 0) && (((SpriteSub *) arg1)->unk3C == 0)) {
        ((SpriteSub *) arg1)->unk3C = 1;
        ((SpriteSub *) arg1)->unk24 = (f32) CURRENT_BOUNDS->unk270;
        ((SpriteSub *) arg1)->unk28 = (f32) CURRENT_BOUNDS->unk272;
    }
    if (((SpriteSub *) arg1)->unk3C == 0) {
        if (sp74 == 0) {
            sp68 = ((SpriteSub *) arg1)->unk4->unk7C;
            sp64 = ((SpriteSub *) arg1)->unk4->unk80 + 1.5 * ((SpriteSub *) arg1)->unk4->unk15E;
            sp60 = ((SpriteSub *) arg1)->unk4->unk84;
        } else {
            actorGetNodePos(((SpriteSub *) arg1)->unk4, sp74, &sp68, &sp64, &sp60);
        }
        if (camProjectToScreen(sp68, sp64, sp60, &sp7C, &sp78, 0, 1.0f, D_807FC929) != 0) {
            sp7C = ((SpriteSub *) arg1)->unk24;
            sp78 = ((SpriteSub *) arg1)->unk28;
        }
        sp7C = CLAMP_TO_BOUNDS(sp7C, (f32) (CURRENT_BOUNDS->unk270 - 0x64), (f32) (CURRENT_BOUNDS->unk274 + 0x64));
        sp78 = CLAMP_TO_BOUNDS(sp78, (f32) (CURRENT_BOUNDS->unk272 - 0x64), (f32) (CURRENT_BOUNDS->unk276 + 0x64));
        ((SpriteSub *) arg1)->unk24 = sp7C;
        ((SpriteSub *) arg1)->unk28 = sp78;
    }
    sp7C = ((SpriteSub *) arg1)->unk24;
    sp78 = ((SpriteSub *) arg1)->unk28;
    if (((f32) D_80744490 * 0.5f) < sp7C) {
        sp7C = sp7C - 131.1999969482421875;
    } else {
        sp7C = sp7C + 131.1999969482421875;
    }
    if (sp78 > 60.7999992370605469) {
        sp78 = sp78 - 60.7999992370605469;
    }
    sp7C = (f32) CLAMP_TO_BOUNDS((f64) sp7C, (f64) CURRENT_BOUNDS->unk270 + 91.1999969482421875 + 5.0,
                           (f64) CURRENT_BOUNDS->unk274 - 96.1999969482421875);
    sp78 = (f32) CLAMP_TO_BOUNDS((f64) sp78, (f64) CURRENT_BOUNDS->unk272 + 60.7999992370605469 + 5.0,
                           (f64) CURRENT_BOUNDS->unk276 - 65.7999992370605469);
    ((SpriteSub *) arg1)->unk2C = ((sp7C - ((SpriteSub *) arg1)->unk2C) * arg2) + ((SpriteSub *) arg1)->unk2C;
    ((SpriteSub *) arg1)->unk30 = ((sp78 - ((SpriteSub *) arg1)->unk30) * arg2) + ((SpriteSub *) arg1)->unk30;
    ((PositionView *) arg0)->unk7C = (((((SpriteSub *) arg1)->unk2C - ((SpriteSub *) arg1)->unk24) * ((SpriteSub *) arg1)->unk20) + ((SpriteSub *) arg1)->unk24);
    ((PositionView *) arg0)->unk80 = (((((SpriteSub *) arg1)->unk30 - ((SpriteSub *) arg1)->unk28) * ((SpriteSub *) arg1)->unk20) + ((SpriteSub *) arg1)->unk28);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A5174.s")
#endif

typedef struct ChainRowNode {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u8 *unkC;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ struct ChainRowNode *unk1C;
} ChainRowNode;

typedef struct ChainRowHead {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ ChainRowNode *unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ f32 unk14;
} ChainRowHead;

void renderCalcChainCenterOffset(ChainRowHead *arg0) {
    ChainRowNode *node;
    s32 sum;

    sum = 0;
    node = arg0->unkC;
    if (node == NULL) {
        return;
    }
    if (node->unkC[2] != 0) {
        return;
    }
    while (node != NULL) {
        sum = (s32)((f32)sum + node->unk18);
        node = node->unk1C;
    }
    if ((f64)sum < 79.7999954223632812) {
        arg0->unk14 = (79.7999954223632812 - (f64)sum) * 0.5;
    } else {
        arg0->unk14 = 6.0f;
    }
}

#ifdef NON_MATCHING
typedef struct SpriteBehaviour {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x2];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ void *unkC;
    /* 0x10 */ u8 pad10[0x4];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x1];
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 pad1E[0x2];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[0x10];
    /* 0x34 */ void *unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ u8 pad3C[0x19];
    /* 0x55 */ u8 unk55;
} SpriteBehaviour;

extern Actor *D_807FBB40;
extern u16 D_807ECD58;
extern u16 D_807ECD66;
extern u8 D_807503F0;

void *heapAlloc(s32);
void camResumePath(void);
void func_806A4DDC(Actor *);
void func_806A5174(Actor *, SpriteBehaviour *, f32);
void resNodeListFree(SpriteBehaviour *);
void resQueueRemove(void *);
void renderCallbacksRegister(void *, void *, s32);

void func_806A5868(void) {
    SpriteBehaviour *sub;
    f32 sp18;
    u8 state;
    u8 v0;
    f32 f;

    sub = D_807FBB40->unk174;
    sp18 = 0.05f;
    if (!(D_807FBB40->unk60 & 0x10)) {
        sp18 = 1.0f;
        sub->unk34 = heapAlloc(0x280);
        sub->unk55 = 0;
    } else if (!(sub->unk55 & 1)) {
        if (D_807FBB40->unk154 != 4 && D_807FBB40->unk154 != 5) {
            if (15.0 < (f64)sub->unk0) {
                v0 = sub->unk55;
                if (D_807ECD66 & 0x4000) {
                    v0 = (sub->unk55 |= 1);
                }
                if (D_807ECD58 & 0x2000) {
                    sub->unk55 = v0 | 2;
                } else {
                    sub->unk55 = v0 & 0xFFFD;
                }
                v0 = sub->unk55;
                if (v0 & 2) {
                    sub->unk55 = v0 & 0xFFFB;
                } else if (D_807ECD58 == 0x8000) {
                    sub->unk55 = v0 | 4;
                } else {
                    sub->unk55 = v0 & 0xFFFB;
                }
                if (sub->unk55 & 1) {
                    camResumePath();
                    D_807FBB40->unk154 = 5;
                }
            }
        }
    }
    sub->unk38 = sub->unk38 + 0x14;
    sub->unk3A = sub->unk3A + 0x32;
    state = D_807FBB40->unk154;
    if (state == 0) {
        if (sub->unk0 < 0x1E) {
            sub->unk0 = sub->unk0 + 1;
        } else {
            D_807FBB40->unk154 = 1;
            sub->unk1D = D_807503F0;
            func_8070E808(D_807FBB40, sub->unk4);
            renderCalcChainCenterOffset((ChainRowHead *)sub);
        }
    } else if (state == 2) {
        f = 2.0f;
        if (sub->unk55 & 4) {
            f = f * 3.0f;
        } else if (sub->unk55 & 2) {
            f = f * 0.5f;
        }
        if (f >= sub->unk18) {
            f = sub->unk18;
        }
        sub->unk18 = sub->unk18 - f;
        sub->unk14 = sub->unk14 - f;
        if ((f64)sub->unk18 < 0.0001) {
            D_807FBB40->unk154 = 1;
        }
    } else if (state == 4) {
        if (sub->unk1D != 0) {
            sub->unk1D -= (sub->unk1D < 0x34) ? sub->unk1D : 0x33;
        } else if (sub->unk0 == 0) {
            D_807FBB40->unk154 = 5;
        } else {
            if (sub->unkC != NULL) {
                resNodeListFree(sub);
            }
            sub->unk0 = sub->unk0 - 1;
        }
    } else if (state == 5) {
        resQueueRemove(sub->unk4);
    }
    if (D_807FBB40->unk154 != 5) {
        sub->unk20 = (f32)sub->unk0 * 0.033333335f;
        func_806A5174(D_807FBB40, sub, sp18);
        if (sub->unk0 != 0) {
            func_806A4DDC(D_807FBB40);
            renderCallbacksRegister(func_806A4284, D_807FBB40, 3);
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A5868.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/D_8075A740.s")
