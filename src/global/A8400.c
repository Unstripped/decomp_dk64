#include "common.h"
#include "actor.h"
#include "resqueue.h"
#include "proto/global/100180.h"
#include "proto/global/103AB0.h"
#include "proto/global/112080.h"
#include "proto/global/119370.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/201B0.h"
#include "proto/global/70FD0.h"
#include "proto/global/90D80.h"
#include "proto/global/A8400.h"

void func_806A3700(s32 unused0, s32 unused1) {
}

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
    /* 0x9C */ u8 pad9C[0x4];
    /* 0xA0 */ struct SpriteDrawNode *unkA0;
} SpriteDrawNode;

typedef struct DrawListHead {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[0xB];
    /* 0x0C */ SpriteDrawNode *unkC;
    /* 0x10 */ u8 pad10[0x8];
    /* 0x18 */ f32 unk18;
} DrawListHead;

typedef struct DrawActor {
    /* 0x00 */ u8 pad0[0x11];
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 pad12[0x32];
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
} DrawActor;

extern u8 gGfxBufferIndex;
extern u16 D_8075A740;

f32 sinApprox(f32);

void textBoxRenderNode(Gfx **gdl, DrawActor *pos, DrawListHead *source, SpriteDrawNode *drawNode) {
    union { u16 h; u8 b; u8 text[8]; } str;
    f32 mtx[4][4];
    f32 tmp[4][4];
    f32 angle;
    f32 halfW;
    f32 halfH;
    Gfx *dl;
    SpriteModel *mdl;
    f32 scale;

    dl = *gdl;
    str.h = D_8075A740;
    mdl = &drawNode->unk10;
    guMtxIdentF(mtx);
    if ((mdl->unk0 != 0) && (drawNode->unk2 != 0)) {
        halfW = (f32) drawNode->unk0 * 0.5f * 4.0f;
        halfH = source->unk18 * 0.5f * 4.0f;
        guTranslateF(tmp, -halfW, -halfH, 0.0f);
        guMtxCatF(mtx, tmp, mtx);
        mdl->unk88 = (f32) ((f64) mdl->unk88 + 0.418879032135009766);
        if ((mdl->unk0 & 8) != 0) {
            angle = (f32) ((f64) mdl->unk88 * 0.5);
            if (angle <= 6.2831855f) {
                guRotateF(tmp, angle * 57.295776f, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
            }
        }
        if ((mdl->unk0 & 4) != 0) {
            angle = mdl->unk88;
            if (angle <= 6.2831855f) {
                scale = sinApprox(angle - 1.5707964f) + 1.0f;
                scale = 0.25f * scale + 1.0f;
            } else {
                scale = 1.0f;
            }
            guScaleF(tmp, scale, scale, 1.0f);
            guMtxCatF(mtx, tmp, mtx);
        }
        if ((mdl->unk0 & 2) != 0) {
            f32 jitterX;
            f32 jitterY;
            jitterX = (4.0f * sinApprox(mdl->unk88)) * ((20.0f - (f32) ((randomNonNegative() >> 15) % 40)) / 20.0f);
            jitterY = (4.0f * sinApprox(mdl->unk88)) * ((20.0f - (f32) ((randomNonNegative() >> 15) % 40)) / 20.0f);
            guTranslateF(tmp, jitterX, jitterY, 0.0f);
            guMtxCatF(mtx, tmp, mtx);
        }
        guTranslateF(tmp, halfW, halfH, 0.0f);
        guMtxCatF(mtx, tmp, mtx);
    }
    guScaleF(tmp, 1.0, 1.0, 1.0);
    guMtxCatF(mtx, tmp, mtx);
    guTranslateF(tmp, (f32) (((f64) pos->unk44 + (f64) drawNode->unk4) * 4.0), (f32) (((f64) pos->unk48 + (f64) drawNode->unk8) * 4.0), 0.0f);
    guMtxCatF(mtx, tmp, mtx);
    guMtxF2L(mtx, (Mtx *) ((u8 *) mdl + (gGfxBufferIndex << 6) + 8));
    gSPMatrix(dl++, (u8 *) mdl + (gGfxBufferIndex << 6) + 8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 0x28, 0x28, 0xFF, drawNode->unk3);
    str.b = mdl->unk2;
    *gdl = textDrawStringVtx(dl, 6, 0, 0, str.text, 0);
}


void renderAppendNodeChain(Gfx **gdl, DrawActor *drawActor, DrawListHead *head, u8 checkLast, u8 *stop) {
    Gfx *dl;
    s32 i;
    SpriteDrawNode *node;

    dl = *gdl;
    node = head->unkC;
    i = 0;
    while (node != NULL && *stop == 0) {
        if (checkLast && (i == drawActor->unk11)) {
            *stop = 1;
        }
        if (head->unk0 & 1) {
            textBoxRenderNode(&dl, drawActor, head, node);
        }
        node = node->unkA0;
        i++;
    }
    *gdl = dl;
}

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }


Gfx *renderTextureSprite(Gfx *dl, s32 mtx, u8 alpha, s32 frame) {
    void *tex;

    tex = texCacheFindOrLoad(frame + 0x52);
    WRITE_GFX(dl++, 0xE7000000, 0);
    WRITE_GFX(dl++, 0xFA000000, (alpha & 0xFF) | 0xFFFFFF00);
    WRITE_GFX(dl++, 0xDA380002, mtx);
    gfxDrawTexturedTileGridSimple(&dl, tex, 3, 0x60, 0x40, 0x20, 0x20, 0.0f, 0.0f, 96.0f, 64.0f, 0.0f, 0.0f, 1, 8);
    WRITE_GFX(dl++, 0xD8380002, 0x40);
    WRITE_GFX(dl++, 0xE7000000, 0);
    return dl;
}

f32 mathCosF(s16);
f32 mathSinF(s16);

typedef struct MotionAngles {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
} MotionAngles;

void mathAddWaveOffset(f32 *x, f32 *y, f32 t, f32 amp, MotionAngles *angles) {
    *x += (t * amp) * 24.0f * mathSinF((s16) ((s16) ((s32) ((f32) angles->unk38 + (t * 3000.0f))) & 0xFFF));
    *y += (t * amp) * 16.0f * mathCosF((s16) ((s16) ((s32) ((f32) angles->unk3A + (t * 3000.0f))) & 0xFFF));
}

extern u8 gGfxBufferIndex;

typedef struct SpriteAnim {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 *unk34;
} SpriteAnim;


Gfx *textBoxRenderTail(Gfx *dl, SpriteAnim *anim, s32 frame) {
    f32 mtx[4][4];
    f32 step[4][4];
    f32 x;
    f32 y;
    u8 cnt;
    u8 i;

    cnt = ((anim->unk20 < 0.32) ? anim->unk20 : 0.32) * 12.5;
    for (i = 1; i <= cnt; i++) {
        x = (anim->unk2C - anim->unk24) * (i * 0.08) + anim->unk24;
        y = (anim->unk30 - anim->unk28) * (i * 0.08) + anim->unk28;
        guTranslateF(mtx, -48.0f, -32.0f, 0);
        guScaleF(step, i * 0.08 * 1.9f * 4.0 * 0.5, i * 0.08 * 1.9f * 4.0 * 0.5, 1.0f);
        guMtxCatF(mtx, step, mtx);
        mathAddWaveOffset(&x, &y, i * 0.08, 1.0f, (MotionAngles *) anim);
        guTranslateF(step, x * 4.0f, y * 4.0f, 0.0f);
        guMtxCatF(mtx, step, mtx);
        guMtxF2L(mtx, (Mtx *) (anim->unk34 + ((i * 2 + gGfxBufferIndex) << 6)));
        dl = renderTextureSprite(dl, (s32) (anim->unk34 + ((i * 2 + gGfxBufferIndex) << 6)), ((i * 300 * 0.08) > 150.0) ? 150.0 : (i * 300 * 0.08), frame);
    }
    return dl;
}

typedef struct ScreenBounds {
    /* 0x000 */ u8 pad0[0x270];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ u8 pad278[0x2F0 - 0x278];
} ScreenBounds;

extern ScreenBounds *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern u8 gGfxBufferIndex;
extern Gfx D_1000118;
extern Mtx D_20000C0;


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

Gfx *textBoxRender(Gfx *gdl, Actor *actor) {
    /* pad* are unused slots above the live locals; with scale/alpha/isLast
       (register-allocated, kept above dl so they cost no below-dl slot) they
       reproduce the original stack frame (0x148, dl 0x98, start 0x94, spA0 0xA0,
       spE0 0xE0, half 0x132, stop 0x13B). */
    s32 padA;
    f32 alpha;
    f32 padH;
    u8 stop;
    s16 padC;
    f32 scale;
    s16 half;
    f64 padE;
    Gfx *padF;
    u8 isLast;
    f32 mtx[4][4];
    f32 tmp[4][4];
    s32 padN;
    Gfx *dl;
    Gfx *start;
    UIState *state;
    UINode *node;
    s32 i;

    state = actor->customState;
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
    guTranslateF(mtx, -48.0f, -32.0f, 0.0f);
    guScaleF(tmp, scale, scale, 1.0f);
    guMtxCatF(mtx, tmp, mtx);
    guTranslateF(tmp, actor->x * 4.0f, actor->y * 4.0f, 0.0f);
    guMtxCatF(mtx, tmp, mtx);
    guMtxF2L(mtx, (Mtx *) (state->unk34 + (gGfxBufferIndex << 6)));
    WRITE_GFX(dl++, 0xE7000000, 0);
    WRITE_GFX(dl++, ((s32) ((f32) gPlayerSlots->unk272 * 4.0f) & 0xFFF) | 0xED000000 | (((s32) ((f32) gPlayerSlots->unk270 * 4.0f) & 0xFFF) << 12),
              ((s32) ((f32) gPlayerSlots->unk276 * 4.0f) & 0xFFF) | (((s32) ((f32) gPlayerSlots->unk274 * 4.0f) & 0xFFF) << 12));
    dl = textBoxRenderTail(dl, (SpriteAnim *) state, half);
    alpha = (state->unk20 * 150.0f * 2 > 150.0f) ? 150.0f : state->unk20 * 150.0f * 2;
    dl = renderTextureSprite(dl, (s32) (state->unk34 + (gGfxBufferIndex << 6)), (u8) alpha, half);
    if (state->unk1D != 0) {
        WRITE_GFX(dl++, 0xE7000000, 0);
        WRITE_GFX(dl++, ((s32) (state->unk48 * 4.0f) & 0xFFF) | 0xED000000 | (((s32) (state->unk44 * 4.0f) & 0xFFF) << 12),
                  ((s32) (state->unk50 * 4.0f) & 0xFFF) | (((s32) (state->unk4C * 4.0f) & 0xFFF) << 12));
    }
    i = 0;
    while (((s32) state->unk10 >= i) && (node != NULL) && (stop == 0)) {
        isLast = (i == state->unk10);
        WRITE_GFX(dl++, 0xE7000000, 0);
        renderAppendNodeChain(&dl, (DrawActor *) state, (DrawListHead *) node, isLast, &stop);
        if (!stop) {
            node = node->unk1C;
        }
        i++;
    }
    WRITE_GFX(dl++, 0xE7000000, 0);
    if (state->unk1D != 0) {
        WRITE_GFX(dl++, 0xED000000 | (((s32) ((f32) gPlayerSlots[gCurrentPlayerIndex].unk270 * 4.0f) & 0xFFF) << 12) | ((s32) ((f32) gPlayerSlots[gCurrentPlayerIndex].unk272 * 4.0f) & 0xFFF),
                  (((s32) ((f32) gPlayerSlots[gCurrentPlayerIndex].unk274 * 4.0f) & 0xFFF) << 12) | ((s32) ((f32) gPlayerSlots[gCurrentPlayerIndex].unk276 * 4.0f) & 0xFFF));
    }
    state->unk1C = state->unk1C + 1;
    state->unk1C = state->unk1C % 16;
    WRITE_GFX(dl++, 0xDF000000, 0);
    WRITE_GFX(gdl++, 0xDE000000, (u32) start);
    return gdl;
}

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

void textBoxRowUpdateIcon(SpriteRow *row, SpriteVector *holder, SpriteVector *chain) {
    SpriteObjectSlot *slot = &row->unk10;
    f32 halfW = (f32) row->unk0 * 0.5f;
    f32 x = row->unk4;
    f32 y = row->unk8;

    if (slot->unk4 == NULL) {
        effectSetDuration(-1);
        effectSetDepth(0);
        effectEnableFade();
        effectSetMode(2);
        effectSetBounds((s16) (s32) chain->unk44, (s16) (s32) chain->unk48, (s16) (s32) chain->unk4C,
                      (s16) (s32) chain->unk50);
        slot->unk4 = effectCreateAtPosition(D_80755390[slot->unk0], 1.0f, chain->unk44, chain->unk48, 1);
        if (slot->unk2 != 0) {
            slot->unk4->unk360 *= -1.0f;
        }
    }
    x += halfW;
    slot->unk4->unk340 = (f32) (((f64) chain->unk44 + x) * 4.0);
    slot->unk4->unk344 = (f32) (((f64) chain->unk48 + (y + (holder->unk18 * 0.5f))) * 4.0);
    slot->unk4->unk36D = row->unk3;
    slot->unk4->unk38E = (s16) (s32) chain->unk44;
    slot->unk4->unk390 = (s16) (s32) chain->unk48;
    slot->unk4->unk392 = (s16) (s32) chain->unk4C;
    slot->unk4->unk394 = (s16) (s32) chain->unk50;
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

void textBoxRowUpdateNodes(f32 y, Actor *actor, SpriteChainState *chain, SpriteHolder *holder, u8 isLast, u8 *stop) {
    f32 x;
    s32 step;
    s32 i;
    u8 alpha;
    u8 prevAlpha;
    SpriteNode *node;

    node = holder->unkC;
    i = 0;
    x = ((f64) 136.8f - holder->unk14) / 2.0;
    while (node != NULL && *stop == 0) {
        if (isLast && i == chain->unk11) {
            if (!(chain->unk55 & 4)) {
                *stop = 1;
            }
            if (actor->state == 1) {
                if (i == 0 && node->unk2 == 0) {
                    func_806A3700(chain->unk4, holder->unk8);
                }
                prevAlpha = node->unk2;
                if (prevAlpha != 0xFF) {
                    step = 0x96;
                    if (chain->unk55 & 2) {
                        step = (s32) (step * 0.5);
                    }
                    if (!(chain->unk55 & 4) && (step < (0xFF - node->unk2))) {
                        node->unk2 = node->unk2 + step;
                    } else {
                        node->unk2 = 0xFF;
                        if (node->unkA0 != NULL) {
                            chain->unk11++;
                        } else {
                            chain->unk11 = 0;
                            chain->unk10++;
                            *stop = 1;
                            if (holder->unk10 != 0) {
                                actor->state = 3;
                                chain->unk12 = holder->unk10;
                            }
                        }
                    }
                }
            }
        }
        if (chain->unk1D < node->unk2) {
            alpha = chain->unk1D;
        } else {
            alpha = node->unk2;
        }
        node->unk4 = x;
        node->unk8 = y;
        node->unk3 = alpha;
        if (holder->unk0 & 2) {
            textBoxRowUpdateIcon((SpriteRow *) node, (SpriteVector *) holder, (SpriteVector *) chain);
        }
        x += (f32) node->unk0;
        node = node->unkA0;
        i++;
    }
}


typedef struct ChainState {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ ResRow *unkC;
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



void textBoxUpdateRows(Actor *actor) {
    ChainState *state;
    ResRow *node;
    ResRow *cur;
    u8 stop;
    u8 pad[0x90];
    f32 acc;
    f32 dt;
    f32 lim;
    u8 mode;
    u8 last;
    s32 i;

    state = actor->customState;
    node = state->unkC;
    stop = 0;
    lim = (f32) ((f64) (1.0f - state->unk20) * 1.47058823529411775);
    if (lim > 1.0f) {
        lim = 1.0f;
    }
    state->unk40 = lim;
    mathAddWaveOffset(&actor->x, &actor->y, state->unk20, lim, (MotionAngles *) state);
    state->unk44 = actor->x - (f64) (state->unk20 * 136.8f) * 0.5;
    state->unk48 = actor->y - (f64) (state->unk20 * 79.799995f) * 0.5;
    state->unk4C = actor->x + (f64) (state->unk20 * 136.8f) * 0.5;
    state->unk50 = actor->y + (f64) (state->unk20 * 79.799995f) * 0.5;
    state->unk44 = ((f32) gPlayerSlots->unk270 < state->unk44) ? state->unk44 : (f32) gPlayerSlots->unk270;
    state->unk48 = ((f32) gPlayerSlots->unk272 < state->unk48) ? state->unk48 : (f32) gPlayerSlots->unk272;
    state->unk4C = (state->unk4C < (f32) gPlayerSlots->unk274) ? state->unk4C : (f32) gPlayerSlots->unk274;
    state->unk50 = (state->unk50 < (f32) gPlayerSlots->unk276) ? state->unk50 : (f32) gPlayerSlots->unk276;
    acc = state->unk14;
    i = 0;
    while (((s32) state->unk10 >= i) && (node != NULL) && (stop == 0)) {
        last = (i == state->unk10);
        dt = node->height;
        if (((f64) (acc + dt) > 73.79999542236328) && (actor->state == 1)) {
            actor->state = 2;
            state->unk18 = (f32) ((f64) (acc + dt) - 73.79999542236328);
            stop = 1;
        } else if (((acc + dt) < 0.0f) && (actor->state == 2)) {
            state->unk14 = state->unk14 + dt;
            state->unkC = node->next;
            state->unk10--;
            i--;
            acc = acc + dt;
            cur = node;
            node = node->next;
            resNodeFree(cur);
        } else {
            textBoxRowUpdateNodes(acc, actor, (SpriteChainState *) state, (SpriteHolder *) node, last, &stop);
            if (stop == 0) {
                node = node->next;
                acc = acc + dt;
            }
        }
        i++;
    }
    mode = actor->state;
    if (mode == 3) {
        if (state->unk12 != 0) {
            state->unk12 = state->unk12 - 1;
            mode = actor->state;
        } else {
            mode = actor->state = 1;
            if (acc && acc) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
    }
    if ((mode == 1) && (node == NULL)) {
        resQueueProcessNext(actor, state->unk4);
    }
}

typedef struct SpriteFrameNode {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ u8 unk2C;
} SpriteFrameNode;

typedef struct SpriteActorData {
    /* 0x000 */ Actor base;
    /* 0x178 */ void *unk178;
    /* 0x17C */ SpriteFrameNode *unk17C;
} SpriteActorData;

typedef struct SpriteBehaviour {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x2];
    /* 0x04 */ SpriteActorData *unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ void *unkC;
    /* 0x10 */ u8 pad10[0x4];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x1];
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 pad1E[0x2];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ void *unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ u8 unk3C;
    /* 0x3D */ u8 pad3D[0x18];
    /* 0x55 */ u8 unk55;
} SpriteBehaviour;

typedef struct MapBounds {
    /* 0x000 */ u8 pad0[0x270];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
} MapBounds;

extern struct ScreenBounds *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s16 gScreenWidth;


#define SPRITE_BOUNDS ((MapBounds *) ((u8 *) gPlayerSlots + (gCurrentPlayerIndex * 0x2F0)))
#define CLAMP_TO_BOUNDS(x, l, h) ((x) < (l) ? (l) : ((h) < (x) ? (h) : (x)))

void textBoxUpdatePosition(Actor *actor, SpriteBehaviour *sub, f32 step) {
    f32 screenX, screenY;
    s32 nodeIndex;
    SpriteFrameNode *node;
    s32 pad;
    f32 posX, posY, posZ;

    nodeIndex = 0;
    switch (sub->unk4->base.actorType) {
    case 0x22:
    case 0x2E:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
    case 0xDA:
    case 0x100:
        sub->unk3C = 1;
        sub->unk24 = (f32) SPRITE_BOUNDS->unk274;
        sub->unk28 = (f32) SPRITE_BOUNDS->unk276;
        break;
    case 0xFE:
        node = sub->unk4->unk17C;
        nodeIndex = node->unk2C;
        break;
    default:
        if (sub->unk4->base.animState != NULL) {
            switch (controllerLookupStateByHash(&sub->unk4->base)) {
            case 0x11:
            case 0x12:
            case 0x1D:
            case 0x1F:
            case 0x2E:
            case 0x3D:
            case 0x45:
            case 0x5E:
            case 0x62:
                nodeIndex = 1;
                break;
            case 0x13:
            case 0x17:
            case 0x3E:
            case 0x56:
            case 0x65:
                nodeIndex = 2;
                break;
            case 0x35:
                nodeIndex = 3;
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
                nodeIndex = 6;
                break;
            case 0x18:
                nodeIndex = 9;
                break;
            }
        }
        break;
    }
    if ((sub->unk4->base.animState == NULL) && (sub->unk3C == 0)) {
        sub->unk3C = 1;
        sub->unk24 = (f32) SPRITE_BOUNDS->unk270;
        sub->unk28 = (f32) SPRITE_BOUNDS->unk272;
    }
    if (sub->unk3C == 0) {
        if (nodeIndex == 0) {
            posX = sub->unk4->base.x;
            posY = sub->unk4->base.y + 1.5 * sub->unk4->base.eyeHeight;
            posZ = sub->unk4->base.z;
        } else {
            actorGetNodePos(&sub->unk4->base, nodeIndex, &posX, &posY, &posZ);
        }
        if (camProjectToScreen(posX, posY, posZ, &screenX, &screenY, 0, 1.0f, gCurrentPlayerIndex) != 0) {
            screenX = sub->unk24;
            screenY = sub->unk28;
        }
        screenX = CLAMP_TO_BOUNDS(screenX, (f32) (SPRITE_BOUNDS->unk270 - 0x64), (f32) (SPRITE_BOUNDS->unk274 + 0x64));
        screenY = CLAMP_TO_BOUNDS(screenY, (f32) (SPRITE_BOUNDS->unk272 - 0x64), (f32) (SPRITE_BOUNDS->unk276 + 0x64));
        sub->unk24 = screenX;
        sub->unk28 = screenY;
    }
    screenX = sub->unk24;
    screenY = sub->unk28;
    if (((f32) gScreenWidth * 0.5f) < screenX) {
        screenX = screenX - 131.1999969482421875;
    } else {
        screenX = screenX + 131.1999969482421875;
    }
    if (screenY > 60.7999992370605469) {
        screenY = screenY - 60.7999992370605469;
    }
    screenX = (f32) CLAMP_TO_BOUNDS((f64) screenX, (f64) SPRITE_BOUNDS->unk270 + 91.1999969482421875 + 5.0,
                           (f64) SPRITE_BOUNDS->unk274 - 96.1999969482421875);
    screenY = (f32) CLAMP_TO_BOUNDS((f64) screenY, (f64) SPRITE_BOUNDS->unk272 + 60.7999992370605469 + 5.0,
                           (f64) SPRITE_BOUNDS->unk276 - 65.7999992370605469);
    sub->unk2C = ((screenX - sub->unk2C) * step) + sub->unk2C;
    sub->unk30 = ((screenY - sub->unk30) * step) + sub->unk30;
    actor->x = (((sub->unk2C - sub->unk24) * sub->unk20) + sub->unk24);
    actor->y = (((sub->unk30 - sub->unk28) * sub->unk20) + sub->unk28);
}

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

void renderCalcChainCenterOffset(ChainRowHead *head) {
    ChainRowNode *node;
    s32 sum;

    sum = 0;
    node = head->unkC;
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
        head->unk14 = (79.7999954223632812 - (f64)sum) * 0.5;
    } else {
        head->unk14 = 6.0f;
    }
}

extern Actor *gCurrentActor;
extern u16 D_807ECD58;
extern u16 D_807ECD66;
extern u8 D_807503F0;


void textBoxUpdate(void) {
    SpriteBehaviour *sub;
    f32 stepSize;
    s32 flags;
    f32 speed;

    sub = gCurrentActor->customState;
    stepSize = 0.05f;
    if (!(gCurrentActor->flags & 0x10)) {
        stepSize = 1.0f;
        sub->unk34 = heapAlloc(0x280);
        sub->unk55 = 0;
    } else {
        flags = sub->unk55;
        if (!(flags & 1)) {
            if (gCurrentActor->state != 4 && gCurrentActor->state != 5) {
                if (15.0 < (f64)sub->unk0) {
                    if (D_807ECD66 & 0x4000) {
                        sub->unk55 = flags | 1;
                        flags = sub->unk55;
                    }
                    if (D_807ECD58 & 0x2000) {
                        sub->unk55 = flags | 2;
                    } else {
                        sub->unk55 = flags & 0xFFFD;
                    }
                    flags = sub->unk55;
                    if (!(flags & 2) && D_807ECD58 == 0x8000) {
                        sub->unk55 = flags | 4;
                    } else {
                        sub->unk55 = flags & 0xFFFB;
                    }
                    if (sub->unk55 & 1) {
                        camResumePath();
                        gCurrentActor->state = 5;
                    }
                }
            }
        }
    }
    sub->unk38 = sub->unk38 + 0x14;
    sub->unk3A = sub->unk3A + 0x32;
    switch (gCurrentActor->state) {
    case 0:
        if (sub->unk0 < 0x1E) {
            sub->unk0 = sub->unk0 + 1;
        } else {
            gCurrentActor->state = 1;
            sub->unk1D = D_807503F0;
            resQueueProcessNext(gCurrentActor, &sub->unk4->base);
            renderCalcChainCenterOffset((ChainRowHead *)sub);
        }
        break;
    case 2:
        speed = 2.0f;
        if (sub->unk55 & 4) {
            speed = speed * 3.0f;
        } else if (sub->unk55 & 2) {
            speed = speed * 0.5f;
        }
        if (!(speed < sub->unk18)) {
            speed = sub->unk18;
        }
        sub->unk14 = sub->unk14 - speed;
        sub->unk18 = sub->unk18 - speed;
        if ((f64)sub->unk18 < 0.0001) {
            gCurrentActor->state = 1;
        }
        break;
    case 4:
        if (sub->unk1D) {
            sub->unk1D -= (sub->unk1D >= 0x34) ? 0x33 : sub->unk1D;
        } else if (sub->unk0 != 0) {
            if (sub->unkC != NULL) {
                resNodeListFree(sub);
            }
            sub->unk0 = sub->unk0 - 1;
        } else {
            gCurrentActor->state = 5;
        }
        break;
    case 5:
        resQueueRemove(&sub->unk4->base);
        break;
    }
    if (gCurrentActor->state != 5) {
        sub->unk20 = (f32)sub->unk0 * 0.033333335f;
        textBoxUpdatePosition(gCurrentActor, sub, stepSize);
        if (sub->unk0 != 0) {
            textBoxUpdateRows(gCurrentActor);
            renderCallbacksRegister(textBoxRender, gCurrentActor, 3);
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/D_8075A740.s")
