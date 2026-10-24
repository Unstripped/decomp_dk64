#include "common.h"
#include "actor.h"

void func_806A3700(s32 arg0, s32 arg1) {
}

#ifdef NON_MATCHING
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
Gfx *func_806FC530(Gfx *, s32, s32, s32, u16 *, s32);

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
    *arg0 = (s32) func_806FC530(&dl[3], 6, 0, 0, &spE8, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A370C.s")
#endif

void func_806A370C(s32 *, void *, void *, void *);

typedef struct M7Actor {
    /* 0x00 */ u8 pad0[0x11];
    /* 0x11 */ u8 unk11;
} M7Actor;

typedef struct M7Node {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ struct M7Node *unkA0;
} M7Node;

typedef struct M7Sub {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[0xB];
    /* 0x0C */ struct M7Node *unkC;
} M7Sub;

void func_806A3B78(s32 *arg0, M7Actor *arg1, M7Sub *arg2, u8 arg3, u8 *arg4) {
    s32 sp44;
    s32 i;
    M7Node *node;

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

Gfx *func_806A3C6C(Gfx *arg0, s32 arg1, u8 arg2, s32 arg3) {
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

typedef struct M7Angle {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
} M7Angle;

void func_806A3DA0(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, M7Angle *arg4) {
    *arg0 += (arg2 * arg3) * 24.0f * func_80612794((s16) ((s16) ((s32) ((f32) arg4->unk38 + (arg2 * 3000.0f))) & 0xFFF));
    *arg1 += (arg2 * arg3) * 16.0f * func_80612790((s16) ((s16) ((s32) ((f32) arg4->unk3A + (arg2 * 3000.0f))) & 0xFFF));
}

#ifdef NON_MATCHING
extern u8 D_807444FC;

typedef struct A8R2bAnim {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 *unk34;
} A8R2bAnim;


s32 func_806A3E9C(s32 arg0, A8R2bAnim *arg1, s32 arg2) {
    f32 spE8[4][4];
    f32 spA8[4][4];
    f32 spA4;
    f32 spA0;
    f32 scale;
    s32 cnt;
    s32 i;
    s32 idx;
    s32 ret;
    s32 off;

    ret = arg0;
    cnt = (u8) (u32) ((((f64) arg1->unk20 < 0.320000000000000007) ? (f64) arg1->unk20 : 0.320000000000000007) * 12.5);
    i = 1;
    idx = 1;
    if (cnt > 0) {
        do {
            spA4 = (f32) ((f64) (arg1->unk2C - arg1->unk24) * ((f64) i * 0.0800000000000000017) + (f64) arg1->unk24);
            spA0 = (f32) ((f64) (arg1->unk30 - arg1->unk28) * ((f64) i * 0.0800000000000000017) + (f64) arg1->unk28);
            guTranslateF(spE8, -48.0f, -32.0f, 0.0f);
            scale = (f32) (((f64) i * 0.0800000000000000017) * 1.9f * 4.0 * 0.5);
            guScaleF(spA8, scale, scale, 1.0f);
            guMtxCatF(spE8, spA8, spE8);
            func_806A3DA0(&spA4, &spA0, (f32) ((f64) i * 0.0800000000000000017), 1.0f, (M7Angle *) arg1);
            guTranslateF(spA8, spA4 * 4.0f, spA0 * 4.0f, 0.0f);
            guMtxCatF(spE8, spA8, spE8);
            off = idx * 2;
            guMtxF2L(spE8, (Mtx *) (arg1->unk34 + ((off + D_807444FC) << 6)));
            ret = (s32) func_806A3C6C((Gfx *) ret, (s32) (arg1->unk34 + ((off + D_807444FC) << 6)), (u32) ((((f64) (idx * 300) * 0.0800000000000000017) > 150.0) ? 150.0 : ((f64) (idx * 300) * 0.0800000000000000017)) & 0xFF, arg2);
            i = (i + 1) & 0xFF;
            idx = i;
        } while (cnt >= idx);
    }
    return ret;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A3E9C.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A4284.s")

#ifdef NON_MATCHING
void func_8071495C(void);
void func_80714998(s32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714A68(s16, s16, s16, s16);
void *func_80714CC0(void *, f32, f32, f32, f32);
extern void *D_80755390[];

typedef struct M7Model {
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
} M7Model;

typedef struct M7ModelSlot {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ M7Model *unk4;
} M7ModelSlot;

typedef struct M7Sprite {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[1];
    /* 0x03 */ u8 unk3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ M7ModelSlot unk10;
} M7Sprite;

typedef struct M7Vector {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x28];
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
} M7Vector;

void func_806A495C(M7Sprite *arg0, M7Vector *arg1, M7Vector *arg2) {
    f32 sp38 = (f32) arg0->unk0 * 0.5f;
    f32 sp34 = arg0->unk4;
    f32 sp30 = arg0->unk8;
    M7ModelSlot *slot = &arg0->unk10;
    M7Model *model;

    if (slot->unk4 == NULL) {
        func_807149FC(-1);
        func_807149B8(0);
        func_8071495C();
        func_80714998(2);
        func_80714A68((s16) (s32) arg2->unk44, (s16) (s32) arg2->unk48, (s16) (s32) arg2->unk4C,
                      (s16) (s32) arg2->unk50);
        model = func_80714CC0(D_80755390[slot->unk0], 1.0f, arg2->unk44, arg2->unk48, 1.0f);
        slot->unk4 = model;
        if (slot->unk2 != 0) {
            model->unk360 *= -1.0f;
        }
    }
    slot->unk4->unk340 = (f32) (((f64) arg2->unk44 + (sp34 + sp38)) * 4.0);
    slot->unk4->unk344 = (f32) (((f64) arg2->unk48 + (sp30 + (arg1->unk18 * 0.5f))) * 4.0);
    slot->unk4->unk36D = arg0->unk3;
    slot->unk4->unk38E = (s16) (s32) arg2->unk44;
    slot->unk4->unk390 = (s16) (s32) arg2->unk48;
    slot->unk4->unk392 = (s16) (s32) arg2->unk4C;
    slot->unk4->unk394 = (s16) (s32) arg2->unk50;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A495C.s")
#endif

#ifdef NON_MATCHING
typedef struct M7Node2 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x94];
    /* 0xA0 */ struct M7Node2 *unkA0;
} M7Node2;

typedef struct M7State {
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
} M7State;

typedef struct M7Holder {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[7];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ M7Node2 *unkC;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ f32 unk14;
} M7Holder;

typedef struct M7Player {
    /* 0x000 */ u8 pad0[0x154];
    /* 0x154 */ u8 unk154;
} M7Player;

void func_806A4B84(f32 arg0, M7Player *arg1, M7State *arg2, M7Holder *arg3, u8 arg4, u8 *arg5) {
    f32 var_fs0;
    s32 var_a0;
    s32 var_s3;
    s16 temp16;
    u8 var_a0_2;
    u8 temp;
    M7Node2 *node;

    node = arg3->unkC;
    var_s3 = 0;
    var_fs0 = ((f64) 136.8f - arg3->unk14) * 0.5;
    while (node != NULL && *arg5 == 0) {
        if (arg4 != 0 && var_s3 == arg2->unk11) {
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
                    if (!(arg2->unk55 & 4) && (var_a0 < (0xFF - temp))) {
                        node->unk2 = temp + var_a0;
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
            func_806A495C((M7Sprite *) node, (M7Vector *) arg3, (M7Vector *) arg2);
        }
        temp16 = node->unk0;
        node = node->unkA0;
        var_s3++;
        var_fs0 += (f32) temp16;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A4B84.s")
#endif

#ifdef NON_MATCHING
typedef struct A8R2bNode A8R2bNode;

typedef struct A8R2bState {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ A8R2bNode *unkC;
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
} A8R2bState;

struct A8R2bNode {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ A8R2bNode *unk1C;
};

typedef struct A8R2bBounds {
    /* 0x000 */ u8 pad0[0x270];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
} A8R2bBounds;

extern A8R2bBounds *D_807FC924;

void func_8070D9AC(A8R2bNode *);
void func_8070E808(Actor *, void *);

void func_806A4DDC(Actor *arg0) {
    A8R2bState *state;
    A8R2bNode *node;
    A8R2bNode *cur;
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
    func_806A3DA0(&arg0->unk7C, &arg0->unk80, dt, lim, (M7Angle *) state);
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
            func_806A4B84(acc, (M7Player *) arg0, (M7State *) state, (M7Holder *) cur, (u8) (i == state->unk10), &stop);
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A5174.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A57C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A5868.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/D_8075A740.s")
