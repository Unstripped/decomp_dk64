#include "common.h"
#include "actor.h"

extern u8 D_807444FC;

extern u8 D_807444F0;
extern u8 D_807444EC;
extern s8 D_807444C0;
extern s32 gCurrentMap;

f32 cameraStepAspectScale(void) {
    static f32 sc = 1.0f; // D_80747CD0: a function-local static so uopt treats it as non-aliased
    f32 target;
    f32 step;
    s32 flag;

    target = 1.0f;
    if (D_807444F0 != 1 && D_807444EC == 1) {
        step = 999.0f;
    } else {
        step = 0.02f;
    }
    flag = D_807444EC == 1;
    if (flag) {
        flag = gCurrentMap != 0x50;
    }
    if (D_807444C0 != 0 && !flag) {
        target = target * 1.2;
    }
    if (sc < target) {
        sc += step;
        if (target < sc) {
            sc = target;
        }
    } else {
        sc -= step;
        if (sc < target) {
            sc = target;
        }
    }
    return sc;
}

u8 *D_807F5DE0;
struct MapBspNode *D_807F5DE4;
s32 D_807F5DE8;
void *D_807F5DEC;
f32 D_807F5DF0[12];


void frustumCalculateCornerRays(f32 arg0, f32 arg1, f32 arg2) {
    f32 scale;
    f32 sp54;
    f32 spB0[4][4];
    f32 sp70[4][4];
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp58;
    s32 i;

    sp58 = arg0 * 0.5;
    sp54 = sp58 * arg1;
    guRotateF(spB0, sp58, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(spB0, 0.0f, 0.0f, (-arg2), &sp64, &sp68, &sp6C);
    guRotateF(sp70, sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DF0[0], &D_807F5DF0[1], &D_807F5DF0[2]);
    guRotateF(sp70, -sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DF0[3], &D_807F5DF0[4], &D_807F5DF0[5]);
    guRotateF(spB0, -sp58, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(spB0, 0.0f, 0.0f, (-arg2), &sp64, &sp68, &sp6C);
    guRotateF(sp70, sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DF0[6], &D_807F5DF0[7], &D_807F5DF0[8]);
    guRotateF(sp70, -sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DF0[9], &D_807F5DF0[10], &D_807F5DF0[11]);
    for (i = 0; i < 4; i++) {
        scale = (-arg2) / D_807F5DF0[i * 3 + 2];
        D_807F5DF0[i * 3] *= scale;
        D_807F5DF0[i * 3 + 1] *= scale;
        D_807F5DF0[i * 3 + 2] = (-arg2);
    }
}

extern f32 D_807F5E20[];
extern f32 D_807F5E24[];
extern f32 D_807F5E28[];

s32 matrix4Invert(f32 (*)[4], f32 (*)[4]);

void frustumCornersTransformByInverse(Mtx *arg0) {
    f32 sp98[4][4];
    f32 sp58[4][4];
    s32 i;

    guMtxL2F(sp98, arg0);
    matrix4Invert(sp58, sp98);
    for (i = 0; i < 4; i++) {
        guMtxXFMF(sp58, D_807F5DF0[i * 3], D_807F5DF0[i * 3 + 1], D_807F5DF0[i * 3 + 2], &D_807F5E20[i * 3], &D_807F5E24[i * 3], &D_807F5E28[i * 3]);
    }
}

typedef struct PlanePoly {
    /* 0x00 */ s16 v[12];
    /* 0x18 */ u8 type;
    /* 0x19 */ u8 pad19[7];
    /* 0x20 */ f64 a;
    /* 0x28 */ f64 b;
    /* 0x30 */ f64 c;
    /* 0x38 */ f64 d;
} PlanePoly; /* 0x40 */

void polyFlipWinding(PlanePoly *);
void planePolyCalcEquation(PlanePoly *);

void frustumOrientPolyNormals(f32 arg0, f32 arg1, f32 arg2, PlanePoly *arg3, f32 *arg4) {
    s32 i;
    f32 xs[5];
    f32 ys[5];
    f32 zs[5];
    PlanePoly *poly;
    poly = arg3;
    for (i = 0; i < 4; i++) {
        poly++;
        poly[-1].v[0] = arg0;
        poly[-1].v[1] = arg1;
        poly[-1].v[2] = arg2;
        poly[-1].type = 3;
    }
    arg3[0].v[3] = arg4[0];
    arg3[0].v[4] = arg4[1];
    arg3[0].v[5] = arg4[2];
    arg3[0].v[6] = arg4[3];
    arg3[0].v[7] = arg4[4];
    arg3[0].v[8] = arg4[5];
    xs[0] = arg4[6];
    ys[0] = arg4[7];
    zs[0] = arg4[8];
    arg3[1].v[3] = arg4[6];
    arg3[1].v[4] = arg4[7];
    arg3[1].v[5] = arg4[8];
    arg3[1].v[6] = arg4[0];
    arg3[1].v[7] = arg4[1];
    arg3[1].v[8] = arg4[2];
    xs[1] = arg4[9];
    ys[1] = arg4[10];
    zs[1] = arg4[11];
    arg3[2].v[3] = arg4[9];
    arg3[2].v[4] = arg4[10];
    arg3[2].v[5] = arg4[11];
    arg3[2].v[6] = arg4[6];
    arg3[2].v[7] = arg4[7];
    arg3[2].v[8] = arg4[8];
    xs[2] = arg4[0];
    ys[2] = arg4[1];
    zs[2] = arg4[2];
    arg3[3].v[3] = arg4[3];
    arg3[3].v[4] = arg4[4];
    arg3[3].v[5] = arg4[5];
    arg3[3].v[6] = arg4[9];
    arg3[3].v[7] = arg4[10];
    arg3[3].v[8] = arg4[11];
    xs[3] = arg4[0];
    ys[3] = arg4[1];
    zs[3] = arg4[2];
    arg3[4].type = 4;
    arg3[4].v[0] = arg4[6];
    arg3[4].v[1] = arg4[7];
    arg3[4].v[2] = arg4[8];
    arg3[4].v[3] = arg4[9];
    arg3[4].v[4] = arg4[10];
    arg3[4].v[5] = arg4[11];
    arg3[4].v[6] = arg4[0];
    arg3[4].v[7] = arg4[1];
    arg3[4].v[8] = arg4[2];
    arg3[4].v[9] = arg4[3];
    arg3[4].v[10] = arg4[4];
    arg3[4].v[11] = arg4[5];
    zs[4] = arg2;
    ys[4] = arg1;
    xs[4] = arg0;
    poly = arg3;
    for (i = 0; i < 5; poly++, i++) {
        planePolyCalcEquation(poly);
        if (poly->d + (poly->a * xs[i] + poly->b * ys[i] + poly->c * zs[i]) < (0, 0.0)) {}  // LAYOUT: second use of the sum makes it a coloured candidate (f0) and keeps its tree order for LFTR
        if (poly->d + (poly->a * xs[i] + poly->b * ys[i] + poly->c * zs[i]) < (0, 0.0)) {
            polyFlipWinding(poly);
            planePolyCalcEquation(poly);
        }
    }
}

void polyFlipWinding(PlanePoly *arg0) {
    s16 a0;
    s16 a1;
    s16 a2;

    switch (arg0->type) {
        case 3:
            a0 = arg0->v[0];
            a1 = arg0->v[1];
            a2 = arg0->v[2];
            arg0->v[0] = arg0->v[3];
            arg0->v[1] = arg0->v[4];
            arg0->v[2] = arg0->v[5];
            arg0->v[3] = a0;
            arg0->v[4] = a1;
            arg0->v[5] = a2;
            break;
        case 4:
            a0 = arg0->v[0];
            a1 = arg0->v[1];
            a2 = arg0->v[2];
            arg0->v[0] = arg0->v[6];
            arg0->v[1] = arg0->v[7];
            arg0->v[2] = arg0->v[8];
            arg0->v[6] = a0;
            arg0->v[7] = a1;
            arg0->v[8] = a2;
            break;
    }
}

void planePolyCalcEquation(PlanePoly *arg0) {
    PlanePoly *p;

    arg0->a = (arg0->v[1] * (f64)(arg0->v[5] - arg0->v[8]) + arg0->v[4] * (f64)(arg0->v[8] - arg0->v[2]))
            + arg0->v[7] * (f64)(arg0->v[2] - arg0->v[5]);
    arg0->b = (arg0->v[2] * (f64)(arg0->v[3] - arg0->v[6]) + arg0->v[5] * (f64)(arg0->v[6] - arg0->v[0]))
            + arg0->v[8] * (f64)(arg0->v[0] - arg0->v[3]);

    arg0->c = (arg0->v[0] * (f64)(arg0->v[4] - arg0->v[7]) + arg0->v[3] * (f64)(arg0->v[7] - arg0->v[1]))
            + arg0->v[6] * (f64)(arg0->v[1] - arg0->v[4]);
    p = arg0;
    p->d = -((p->v[0] * ((f64)p->v[4] * p->v[8] - (f64)p->v[7] * p->v[5]) + p->v[3] * ((f64)p->v[7] * p->v[2] - (f64)p->v[1] * p->v[8])) + p->v[6] * ((f64)p->v[1] * p->v[5] - p->v[4] * (f64)p->v[2]));
}

typedef struct MapNodeEffects {
    /* 0x00 */ struct MapNodeEffects *unk0;
    /* 0x04 */ struct MapNodeEffects *unk4;
    /* 0x08 */ u8 pad8[0x68];
    /* 0x70 */ s16 unk70[0x1C];
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ u8 unkAC[0x19];
    /* 0xC5 */ u8 unkC5;
} MapNodeEffects;

void mapSurfaceEffectInit(s16);

void mapNodeTreeInitSurfaceEffects(MapNodeEffects *arg0, s32 *arg1) {
    s32 i;
    s32 temp;

    for (;;) {
        if (arg0 == NULL) {
            break;
        }
        for (i = 0; i < arg0->unkC5; i++) {
            mapSurfaceEffectInit(arg0->unk70[i]);
            temp = arg0->unkAC[i] + 1;
            if (*arg1 < temp) {
                *arg1 = temp;
            }
        }
        mapNodeTreeInitSurfaceEffects(arg0->unk0, arg1);
        arg0 = arg0->unk4;
    }
}

typedef struct MapOffsetSlot {
    /* 0x00 */ Mtx mtx[2];
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[3];
} MapOffsetSlot; /* 0x90 */

extern MapOffsetSlot *D_807F5FB8;
extern s32 D_807F5FBC;
extern u8 D_807F5FC0;
void *heapAlloc(s32);

void mapOffsetSlotsInit(s32 arg0) {
    s32 i;

    if (arg0 == 0) {
        D_807F5FB8 = NULL;
        D_807F5FBC = 0;
        return;
    }
    D_807F5FB8 = heapAlloc(arg0 * 0x90);
    D_807F5FBC = arg0;
    for (i = 0; i < arg0; i++) {
        D_807F5FB8[i].unk80 = 0.0f;
        D_807F5FB8[i].unk84 = 0.0f;
        D_807F5FB8[i].unk88 = 0.0f;
        D_807F5FB8[i].unk8C = 1;
    }
    D_807F5FC0 = 0;
}

void mapOffsetSlotSetEnabled(s16 arg0, u8 arg1) {
    D_807F5FB8[arg0].unk8C = arg1;
}

extern s32 gMapChunkCount;

void mapOffsetSlotsUpdate(void) {
    s32 i;

    D_807F5FC0 = 0;
    for (i = 0; i < D_807F5FBC; i++) {
        if (D_807F5FB8[i].unk80 != 0.0) {
            guTranslate(&D_807F5FB8[i].mtx[D_807444FC], 0.0f, gMapChunkCount != 0 ? D_807F5FB8[i].unk80 * 3.0f : D_807F5FB8[i].unk80, 0.0f);
        }
        if (D_807F5FB8[i].unk80 != D_807F5FB8[i].unk84) {
            D_807F5FC0 = 1;
            if (D_807F5FB8[i].unk80 < D_807F5FB8[i].unk84) {
                D_807F5FB8[i].unk80 += D_807F5FB8[i].unk88;
                if (D_807F5FB8[i].unk84 < D_807F5FB8[i].unk80) {
                    D_807F5FB8[i].unk80 = D_807F5FB8[i].unk84;
                }
            } else {
                D_807F5FB8[i].unk80 -= D_807F5FB8[i].unk88;
                if (D_807F5FB8[i].unk80 < D_807F5FB8[i].unk84) {
                    D_807F5FB8[i].unk80 = D_807F5FB8[i].unk84;
                }
            }
        }
    }
}

f32 mapOffsetSlotGetValue(s8 arg0) {
    return D_807F5FB8[arg0].unk80;
}

void mapOffsetSlotSetTarget(s32 arg0, f32 arg1, f32 arg2) {
    D_807F5FB8[arg0].unk84 = arg1;
    D_807F5FB8[arg0].unk88 = arg2;
}

void mapOffsetSlotAddTarget(s32 arg0, f32 arg1, f32 arg2) {
    D_807F5FB8[arg0].unk84 += arg1;
    D_807F5FB8[arg0].unk88 = arg2;
}

void mapOffsetSlotsGetTargets(f32 *arg0) {
    s32 i;
    s32 n;

    n = D_807F5FBC;
    for (i = 0; i < n; i++) {
        arg0[i] = D_807F5FB8[i].unk84;
    }
}

void mapOffsetSlotsSetValues(f32 *arg0) {
    s32 i;

    for (i = 0; i < D_807F5FBC; i++) {
        D_807F5FB8[i].unk84 = arg0[i];
        D_807F5FB8[i].unk80 = arg0[i];
    }
}

typedef struct MapTreeLinks {
    struct MapTreeLinks *unk0;
    struct MapTreeLinks *unk4;
} MapTreeLinks;

typedef struct MapVisNodeNew {
    u8 pad0;
    u8 unk1;
    u8 pad2[2];
    s32 unk4;
    s32 unk8;
    struct MapVisNodeNew *unkC;
    struct MapVisNodeNew *unk10;
} MapVisNodeNew;


MapVisNodeNew *mapTreeCloneShape(MapTreeLinks *arg0) {
    MapVisNodeNew *node;

    if (arg0 == NULL) {
        return NULL;
    }
    node = heapAlloc(0x14);
    node->unk4 = 0;
    node->unk8 = 0;
    node->unk1 = 3;
    node->unkC = mapTreeCloneShape(arg0->unk0);
    node->unk10 = mapTreeCloneShape(arg0->unk4);
    return node;
}

typedef struct MapBspNode {
    struct MapBspNode *unk0;
    struct MapBspNode *unk4;
    u8 pad8[0xC];
    struct MapBspNode *unk14;
    u8 pad18[6];
    s16 unk1E;
    u8 pad20[4];
    u8 unk24;
    u8 pad25[0x93];
    u8 unkB8;
} MapBspNode;

typedef struct MapVisNode {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    MapBspNode *unk4;
    s32 unk8;
    struct MapVisNode *unkC;
    struct MapVisNode *unk10;
} MapVisNode;

void func_8062BB2C(MapBspNode *, MapVisNode *, u8);

extern MapVisNode *D_807F5E60;

void modelPendingCountsReset(void);
void modelPendingEntriesProcess(void);
void csFreeTrackedModels(void);

void func_8062BAE4(void) {
    modelPendingCountsReset();
    func_8062BB2C(D_807F5DE4, D_807F5E60, 1);
    modelPendingEntriesProcess();
    csFreeTrackedModels();
}

void modelPendingQueueInsert(MapBspNode *, u8);
void mapChunkUpdateModelNodes(void);

void func_8062BB2C(MapBspNode *arg0, MapVisNode *arg1, u8 arg2) {
    MapBspNode *next;

    if (arg0 == NULL) {
        return;
    }
    if (arg1->unk1 == 3) {
        func_8062BB2C(arg0->unk0, arg1->unkC, 0);
        func_8062BB2C(arg0->unk4, arg1->unk10, 0);
        return;
    }
    switch (arg0->unkB8) {
        case 2:
            mapChunkUpdateModelNodes();
            break;
        case 1:
            arg0 = arg1->unk4;
            while (arg0 != NULL) {
                next = arg0->unk14;
                modelPendingQueueInsert(arg0, arg2);
                arg0 = next;
            }
            break;
        case 0:
            switch (arg1->unk1) {
                case 1:
                case 2:
                    if (arg1->unk0 != 0) {
                        func_8062BB2C(arg0->unk4, arg1->unk10, arg2);
                        func_8062BB2C(arg0->unk0, arg1->unkC, 0);
                    } else {
                        func_8062BB2C(arg0->unk0, arg1->unkC, arg2);
                        func_8062BB2C(arg0->unk4, arg1->unk10, 0);
                    }
                    break;
                case 0:
                    if (arg1->unk0 != 0) {
                        func_8062BB2C(arg0->unk0, arg1->unkC, arg2);
                        func_8062BB2C(arg0->unk4, arg1->unk10, arg2);
                    } else {
                        func_8062BB2C(arg0->unk4, arg1->unk10, arg2);
                        func_8062BB2C(arg0->unk0, arg1->unkC, arg2);
                    }
                    break;
            }
            break;
    }
}

extern MapBspNode *D_807F5FF4;

u8 func_8062BDB0(void *, MapBspNode *, MapVisNode *, f32, f32, f32, s32);
s32 func_80668E9C(void *, s16, f32, f32, f32, s32);

u8 func_8062BCC8(void *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    u8 result;
    MapBspNode *item;

    result = func_8062BDB0(arg0, D_807F5DE4, D_807F5E60, arg1, arg2, arg3, arg4);
    item = D_807F5FF4;
    while (item != NULL) {
        if (item->unk24 == 1) {
            result |= func_80668E9C(arg0, item->unk1E, arg1, arg2, arg3, arg4);
        }
        item = item->unk14;
    }
    return result;
}

u8 mapChunkCheckActorCollision(void *, f32, f32, f32, s32);

u8 func_8062BDB0(void *arg0, MapBspNode *arg1, MapVisNode *arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    u8 result;
    s32 other;
    MapBspNode *item;

    result = 0;
    switch (arg1->unkB8) {
        case 2:
            return mapChunkCheckActorCollision(arg0, arg3, arg4, arg5, arg6);
        case 1:
            item = arg2->unk4;
            while (item != NULL) {
                if (item->unk24 == 1) {
                    result |= func_80668E9C(arg0, item->unk1E, arg3, arg4, arg5, arg6);
                }
                item = item->unk14;
            }
            return result;
        case 0:
            result = func_8062BDB0(arg0, arg1->unk0, arg2->unkC, arg3, arg4, arg5, arg6);
            other = func_8062BDB0(arg0, arg1->unk4, arg2->unk10, arg3, arg4, arg5, arg6);
            return result | other;
    }
    return 0;
}

typedef struct PlayerCamera {
    u8 pad0[0x129];
    u8 unk129;
} PlayerCamera;

typedef struct ViewportRect {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} ViewportRect;

typedef struct PlayerViewState {
    u8 unk0;
    u8 pad1[3];
    PlayerCamera *unk4;
    u8 pad8[0x214];
    s32 unk21C;
    s32 unk220;
    s32 unk224;
    u8 pad228[0xC];
    f32 unk234;
    f32 unk238;
    f32 unk23C;
    u8 pad240[0x40];
    f32 unk280;
    u8 pad284[4];
    f32 unk288;
    f32 unk28C;
    u8 pad290[0x5A];
    u8 unk2EA;
    u8 pad2EB[5];
} PlayerViewState;

#define PLAYER_VIEW(i) (((PlayerViewState *)gPlayerSlots)[i])

extern Gfx D_1000118;
extern u8 D_80750AB4;
extern u8 D_807F5FEC;
extern u8 D_807F5FED;
extern u8 gCurrentPlayerIndex;
extern void *gPlayerSlots;

void mapFrameBegin(s32);
void mapFrameEnd(void);
f32 cameraStepAspectScale(void);
Gfx *mapRenderPlayerView(Gfx *, s32, s32, s32, f32, f32, f32, f32, f32, f32);
ViewportRect *cameraFindViewportEntry(u8);

Gfx *playerViewsRender(Gfx *gfx, s32 arg1) {
    s32 i;
    u8 alpha;
    ViewportRect *vp;

    mapFrameBegin(arg1);
    gDPPipeSync(gfx++);
    if (D_807F5FED != 0) {
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, G_MDSFT_PIPELINE, 1, G_PM_1PRIMITIVE);
    } else {
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, G_MDSFT_PIPELINE, 1, G_PM_NPRIMITIVE);
    }
    for (i = 0; i < D_80750AB4; i++) {
        if (PLAYER_VIEW(i).unk0 != 0) {
            gCurrentPlayerIndex = i;
            gfx = mapRenderPlayerView(gfx, PLAYER_VIEW(i).unk21C, PLAYER_VIEW(i).unk220, PLAYER_VIEW(i).unk224,
                                PLAYER_VIEW(i).unk234, PLAYER_VIEW(i).unk238, PLAYER_VIEW(i).unk23C,
                                PLAYER_VIEW(i).unk28C, PLAYER_VIEW(i).unk280 * cameraStepAspectScale(),
                                PLAYER_VIEW(i).unk288);
            D_807F5FEC = 0;
        }
        if (PLAYER_VIEW(i).unk0 == 0 || PLAYER_VIEW(i).unk2EA != 0) {
            alpha = PLAYER_VIEW(i).unk4->unk129;
            vp = cameraFindViewportEntry(i);
            gSPDisplayList(gfx++, &D_1000118);
            gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, 0, G_OFF);
            gDPPipeSync(gfx++);
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0xFF - alpha);
            gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPFillRectangle(gfx++, vp->unk4, vp->unk6, vp->unk8, vp->unkA);
            gDPPipeSync(gfx++);
        }
    }
    mapFrameEnd();
    gDPPipeSync(gfx++);
    return gfx;
}


void lightFlushQueued(void);
void mapDistributeEntries(MapBspNode *);
void renderEntryListFreeTranslucent(void);
void mapChunkAnimateTextures(u8);
void mapChunkResetFlags(void);
void lightApplyToActors(void);
void effectUpdateNodes(void);

void mapFrameBegin(s32 arg0) {
    lightFlushQueued();
    mapDistributeEntries(D_807F5FF4);
    renderEntryListFreeTranslucent();
    if (gMapChunkCount == 0) {
        mapChunkAnimateTextures(0xFF);
    }
    mapChunkResetFlags();
    lightApplyToActors();
    effectUpdateNodes();
    D_807F5FEC = 1;
}

void mapChunkReleaseAndAdvance(void);
void mapChunkFreeHiddenBuffers(void);
void mapChunkFreeIdleBuffers(void);
void mapChunkUpdateAssetStreaming(void);
void mapChunkSetIndexOverride(s8);
void mapSurfaceEffectsUpdate(void);
void mapOffsetSlotsUpdate(void);
void modelSlotsStepSegmentCommands(void);
void displayListFreeQueueProcess(void);

void mapFrameEnd(void) {
    if (gMapChunkCount != 0) {
        mapChunkReleaseAndAdvance();
        mapChunkFreeHiddenBuffers();
        mapChunkFreeIdleBuffers();
        mapChunkUpdateAssetStreaming();
        mapChunkSetIndexOverride(0);
    }
    mapSurfaceEffectsUpdate();
    mapOffsetSlotsUpdate();
    modelSlotsStepSegmentCommands();
    displayListFreeQueueProcess();
}

typedef struct L8062C29CPlayer {
    u8 pad0[4];
    void *unk4;
    Mtx unk8[2];
    Mtx unk88[2];
    u8 pad108[0x80];
    u16 unk188;
    u8 pad18A[6];
    u8 unk190[2][0x20];
    u32 unk1D0[2][4];
    Gfx unk1F0[2][2];
    u8 pad210[0x40];
    s16 unk250[2][8];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 pad278[0x78];
} L8062C29CPlayer;

#define L8062C29CP (((L8062C29CPlayer *)gPlayerSlots)[gCurrentPlayerIndex])
#define L8062C29CF(x) (*(f32 *)&(x))

extern s32 D_807F5E64;
extern f32 D_807F5FB4;
extern f32 D_807F5FB0;
extern f32 D_807F5FAC;
extern f32 D_807F5FA8;
extern f32 D_807F5FE0;
extern f32 D_807F5FDC;
extern u8 D_807F5E68[];
extern struct MapDistributeEntry *D_807F5FF0;
extern s32 D_807FBB60;
extern Mtx D_2000180;

f32 cosApprox(f32);
void frustumCalculateCornerRays(f32, f32, f32);
void planeFromTwoPoints(f32, f32, f32, f32, f32, f32);
void frustumOrientPolyNormals(f32, f32, f32, PlanePoly *, f32 *);
void mapTreeFrameUpdate(MapBspNode *, MapVisNode *, struct MapDistributeEntry *, f32, f32, f32, u8, u8, u8);
Gfx *actorBuildLightDisplayList(Gfx *, void *, s16);
Gfx *gfxDrawPlayerViewBackground(Gfx *, s16);
Gfx *fogApply(Gfx *);
void mapSetClipBounds();
Gfx *mapTreeRender(Gfx *, MapBspNode *, MapVisNode *, f32, f32, f32, s32);
void viewportSetFromRect(s16 *, s32, s32, s32, s32);

Gfx *mapRenderPlayerView(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    Gfx *dl;
    s32 pad2[1];
    s32 pad[24];

    dl = &L8062C29CP.unk1F0[D_807444FC][0];
    D_807F5E64 = 0;
    D_807F5FB4 = arg7;
    D_807F5FB0 = arg8;
    D_807F5FAC = arg9;
    D_807F5FA8 = D_807F5FAC;
    D_807F5FE0 = cosApprox(arg7 * 0.01745329238f);
    D_807F5FE0 = (D_807F5FE0 - D_807F5FDC) * 3.0 + D_807F5FDC;
    planeFromTwoPoints(L8062C29CF(arg1), L8062C29CF(arg2), L8062C29CF(arg3), arg4, arg5, arg6);
    frustumCalculateCornerRays(D_807F5FB4, D_807F5FB0, D_807F5FA8);
    frustumCornersTransformByInverse(&L8062C29CP.unk8[D_807444FC]);
    frustumOrientPolyNormals(L8062C29CF(arg1), L8062C29CF(arg2), L8062C29CF(arg3), (PlanePoly *)D_807F5E68, D_807F5E20);
    mapTreeFrameUpdate(D_807F5DE4, D_807F5E60, D_807F5FF0, L8062C29CF(arg1), L8062C29CF(arg2), L8062C29CF(arg3), 0, !D_807F5FEC, D_80750AB4 >= 2);
    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
    gfx = actorBuildLightDisplayList(gfx, L8062C29CP.unk4, gCurrentPlayerIndex);
    gSPSegment(gfx++, 5, osVirtualToPhysical(dl));
    gDPSetTileSize(dl++, 0, L8062C29CP.unk1D0[D_807444FC][0] & 0xFFF, L8062C29CP.unk1D0[D_807444FC][1] & 0xFFF,
                   (L8062C29CP.unk1D0[D_807444FC][0] + 0x7C) & 0xFFF, (L8062C29CP.unk1D0[D_807444FC][1] + 0x7C) & 0xFFF);
    gSPEndDisplayList(dl++);
    viewportSetFromRect(L8062C29CP.unk250[D_807444FC], L8062C29CP.unk270, L8062C29CP.unk272, L8062C29CP.unk274, L8062C29CP.unk276);
    gSPPerspNormalize(gfx++, L8062C29CP.unk188);
    gSPViewport(gfx++, osVirtualToPhysical(&L8062C29CP.unk250[D_807444FC]));
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, L8062C29CP.unk270, L8062C29CP.unk272, L8062C29CP.unk274, L8062C29CP.unk276);
    gSPLookAtX(gfx++, osVirtualToPhysical(&L8062C29CP.unk190[D_807444FC]));
    gSPLookAtY(gfx++, osVirtualToPhysical(&L8062C29CP.unk190[D_807444FC]) + 0x10);
    mapSetClipBounds(L8062C29CP.unk270, L8062C29CP.unk272, L8062C29CP.unk274, L8062C29CP.unk276);
    gfx = gfxDrawPlayerViewBackground(fogApply(gfx), gCurrentPlayerIndex);
    gSPMatrix(gfx++, osVirtualToPhysical(&L8062C29CP.unk88[D_807444FC]), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gfx++, osVirtualToPhysical(&L8062C29CP.unk8[D_807444FC]), G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(gfx++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gfx = mapTreeRender(gfx, D_807F5DE4, D_807F5E60, L8062C29CF(arg1), L8062C29CF(arg2), L8062C29CF(arg3), D_807FBB60);
    gDPPipeSync(gfx++);
    return gfx;
}

void viewportSetFromRect(s16 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0[0] = (arg3 - arg1) * 2;
    arg0[1] = (arg4 - arg2) * 2;
    arg0[2] = 0x1FF;
    arg0[3] = 0;
    arg0[4] = ((arg1 + arg3) / 2) * 4;
    arg0[5] = ((arg2 + arg4) / 2) * 4;
    arg0[6] = 0x1FF;
    arg0[7] = 0;
}

extern s32 D_807F5FF8;
extern u8 D_807F6009;

Gfx *renderEntryListBuildDisplayList(Gfx *, s32, f32, f32, f32, s32, s32, s32);

void func_8062CA0C(Gfx *arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_807F6009 = 0xFF;
    renderEntryListBuildDisplayList(arg0, D_807F5FF8, arg1, arg2, arg3, 0x30030, -1, 0);
}

struct MapViewEntries;

typedef struct MapLeafLists {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x52];
    s16 unk6E;
} MapLeafLists;

extern s32 D_807F5FFC;

Gfx *mapViewDrawPass(Gfx *, struct MapViewEntries *, u8);
Gfx *mapChunksRender(Gfx *, MapBspNode *, f32, f32, f32, s32);
Gfx *fogRender(Gfx *);
struct RawGfxCmd;
struct RawGfxCmd *mapChunkEmitSegmentCommands();
Gfx *spriteListRender(Gfx *, s32);
Gfx *billboardRenderQueued(Gfx *, s16);

#define MAP_LEAF(o) ((MapLeafLists *)(o))

Gfx *mapTreeRender(Gfx *gfx, MapBspNode *arg1, MapVisNode *arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    Gfx *sp84;

    if (arg1 == NULL) {
        return gfx;
    }
    if (arg2->unk1 == 3) {
        return gfx;
    }
    switch (arg1->unkB8) {
        case 2:
            gfx = mapChunksRender(gfx, arg1, arg3, arg4, arg5, arg6);
            break;
        case 1:
            D_807F5E64 += MAP_LEAF(arg1)->unk6E;
            if (arg6 & 0x10) {
                gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
                gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                gfx = mapViewDrawPass(gfx, (struct MapViewEntries *)arg1, 1);
                gfx = fogRender(gfx);
                gfx = (Gfx *)mapChunkEmitSegmentCommands((struct RawGfxCmd *)gfx, 0xFF);
                if (MAP_LEAF(arg1)->unk8 != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)MAP_LEAF(arg1)->unk8));
                }
                if (MAP_LEAF(arg1)->unkC != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)MAP_LEAF(arg1)->unkC));
                }
                if (MAP_LEAF(arg1)->unk14 != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)MAP_LEAF(arg1)->unk14));
                }
                if (MAP_LEAF(arg1)->unk10 != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)MAP_LEAF(arg1)->unk10));
                }
                if (MAP_LEAF(arg1)->unk18 != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)MAP_LEAF(arg1)->unk18));
                }
                gfx = mapViewDrawPass(gfx, (struct MapViewEntries *)arg1, 2);
            }
            gfx = spriteListRender(gfx, arg2->unk8);
            gfx = billboardRenderQueued(gfx, -1);
            D_807F6009 = 0xFF;
            gfx = renderEntryListBuildDisplayList(gfx, (s32)arg2->unk4, arg3, arg4, arg5, arg6, -1, 0);
            if (arg6 & 0x10) {
                gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
                gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                gfx = mapViewDrawPass(gfx, (struct MapViewEntries *)arg1, 3);
                gDPPipeSync(gfx++);
            }
            gfx = renderEntryListBuildDisplayList(gfx, D_807F5FFC, arg3, arg4, arg5, arg6, -1, 0);
            break;
        case 0:
            switch (arg2->unk1) {
                case 1:
                case 2:
                    if (arg2->unk0 != 0) {
                        return mapTreeRender(gfx, arg1->unk4, arg2->unk10, arg3, arg4, arg5, arg6);
                    } else {
                        return mapTreeRender(gfx, arg1->unk0, arg2->unkC, arg3, arg4, arg5, arg6);
                    }
                case 0:
                    if (arg2->unk0 != 0) {
                        gfx = mapTreeRender(gfx, arg1->unk0, arg2->unkC, arg3, arg4, arg5, arg6);
                        return mapTreeRender(gfx, arg1->unk4, arg2->unk10, arg3, arg4, arg5, arg6);
                    } else {
                        gfx = mapTreeRender(gfx, arg1->unk4, arg2->unk10, arg3, arg4, arg5, arg6);
                        return mapTreeRender(gfx, arg1->unk0, arg2->unkC, arg3, arg4, arg5, arg6);
                    }
                default:
                    break;
            }
    }
    return gfx;
}

typedef struct MapViewEntries {
    u8 pad0[0x1C];
    void *unk1C[21];
    s16 unk70[12];
    s16 unk88[18];
    u8 unkAC[13];
    u8 unkB9[12];
    u8 unkC5;
} MapViewEntries;


s32 mapChunkIsActive(s16);
Gfx *mapSurfaceEffectDraw(Gfx *, s16);

Gfx *mapViewDrawPass(Gfx *gfx, MapViewEntries *arg1, u8 arg2) {
    s32 i;
    u8 idx;

    for (i = 0; i < arg1->unkC5; i++) {
        if (arg2 == arg1->unkB9[i] && (arg1->unk88[i] == -1 || mapChunkIsActive(arg1->unk88[i]) != 0)) {
            gfx = mapSurfaceEffectDraw(gfx, arg1->unk70[i]);
            gSPClearGeometryMode(gfx++, G_CULL_BACK);
            idx = arg1->unkAC[i];
            if (D_807F5FB8[idx].unk80 != 0.0 && D_807F5FB8[idx].unk8C != 0) {
                gSPMatrix(gfx++, osVirtualToPhysical((u8 *)D_807F5FB8 + idx * 0x90 + (D_807444FC << 6)),
                          G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
                gSPDisplayList(gfx++, osVirtualToPhysical(arg1->unk1C[i]));
                gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
            } else {
                gSPDisplayList(gfx++, osVirtualToPhysical(arg1->unk1C[i]));
            }
            gDPPipeSync(gfx++);
        }
    }
    return gfx;
}

u8 func_8062D0CC(MapBspNode *, MapVisNode *, s32, u8);

void func_8062D094(s32 arg0, u8 arg1) {
    func_8062D0CC(D_807F5DE4, D_807F5E60, arg0, arg1);
}

void mapChunkMarkRenderEntry(s32, u8);
void renderEntrySetDistanceOverride(MapBspNode *, s32, s32, u8, u8 *);

u8 func_8062D0CC(MapBspNode *arg0, MapVisNode *arg1, s32 arg2, u8 arg3) {
    u8 unused;
    u8 sp26;

    sp26 = 0;
    if (arg0 == NULL) {
        return 0;
    }
    switch (arg0->unkB8) {
        case 2:
            mapChunkMarkRenderEntry(arg2, arg3);
            return 1;
        case 1:
            renderEntrySetDistanceOverride(arg1->unk4, arg2, 0, arg3, &sp26);
            return sp26;
        case 0:
            if (func_8062D0CC(arg0->unk0, arg1->unkC, arg2, arg3) != 0) {
                return 1;
            }
            return func_8062D0CC(arg0->unk4, arg1->unk10, arg2, arg3);
    }
}

s32 func_807142D8(void);
void mapTreeResolveNodeAssets(MapBspNode *, MapVisNode *);

void func_8062D1A8(void) {
    if (func_807142D8() == 0) {
        mapTreeResolveNodeAssets(D_807F5DE4, D_807F5E60);
    }
}

void modelNodeListSyncFlags(MapBspNode *);
void mapChunkResolveNodeAssets(void);

void mapTreeResolveNodeAssets(MapBspNode *arg0, MapVisNode *arg1) {
    for (;;) {
        if (arg0 == NULL) {
            return;
        }
        switch (arg0->unkB8) {
            case 2:
                mapChunkResolveNodeAssets();
                return;
            case 1:
                modelNodeListSyncFlags(arg1->unk4);
                return;
            case 0:
                mapTreeResolveNodeAssets(arg0->unk0, arg1->unkC);
                arg0 = arg0->unk4;
                arg1 = arg1->unk10;
                break;
            default:
                return;
        }
    }
}

MapBspNode *renderEntryRemove(MapBspNode *, s32, s32, u8 *);
void mapPurgeNodeList(s32, s16 *, u8);

void func_8062D26C(s32 arg0) {
    u8 sp1F;
    s16 sp1C;

    renderEntryRemove(NULL, arg0, 1, &sp1F);
    mapPurgeNodeList(arg0, &sp1C, 1);
}

u8 mapTreePurgeNodeList(MapBspNode *, MapVisNode *, s32, s16 *, u8);

void mapPurgeNodeList(s32 arg0, s16 *arg1, u8 arg2) {
    mapTreePurgeNodeList(D_807F5DE4, D_807F5E60, arg0, arg1, arg2);
}

u8 mapChunkPurgeNodeList(s32, s16 *, u8);

u8 mapTreePurgeNodeList(MapBspNode *arg0, MapVisNode *arg1, s32 arg2, s16 *arg3, u8 arg4) {
    u8 sp27;

    if (arg0 == NULL) {
        return 0;
    }
    switch (arg0->unkB8) {
        case 2:
            return mapChunkPurgeNodeList(arg2, arg3, arg4);
        case 1:
            arg1->unk4 = renderEntryRemove(arg1->unk4, arg2, 0, &sp27);
            return sp27;
        case 0:
            if (mapTreePurgeNodeList(arg0->unk0, arg1->unkC, arg2, arg3, arg4) != 0 && arg4 == 0) {
                return 1;
            }
            return mapTreePurgeNodeList(arg0->unk4, arg1->unk10, arg2, arg3, arg4);
    }
    return 0;
}

typedef struct MapDistributeEntry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ struct MapDistributeEntry *unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 pad23;
    /* 0x24 */ u8 unk24;
} MapDistributeEntry;

void mapTreeDistributeEntries(MapBspNode *, MapVisNode *, MapDistributeEntry *);

void mapDistributeEntries(MapBspNode *arg0) {
    mapTreeDistributeEntries(D_807F5DE4, D_807F5E60, (MapDistributeEntry *)arg0);
}

s32 renderEntryAddOrUpdate(s32, u8, s32, f32, f32, f32, s32, s32, s32, s32, s32);
u8 mapBspPlaneSideTest(void *, u8 *, f32, f32, f32);
void renderEntryListFree(s32);
void mapChunkUpdateEntryNode(MapDistributeEntry *);

void mapTreeDistributeEntries(MapBspNode *arg0, MapVisNode *arg1, MapDistributeEntry *arg2) {
    s32 pad;
    s32 listA;
    s32 listB;
    s32 sp58;

    listA = 0;
    listB = 0;
    if (arg0 == NULL) {
        return;
    }
    switch (arg0->unkB8) {
        case 2:
            if (arg2 != NULL) {
                do {
                    mapChunkUpdateEntryNode(arg2);
                    arg2 = arg2->unk14;
                } while (arg2 != NULL);
            }
            break;
        case 1:
            if (arg2 != NULL) {
                do {
                    arg1->unk4 = (MapBspNode *)renderEntryAddOrUpdate((s32)arg1->unk4, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                    arg2 = arg2->unk14;
                } while (arg2 != NULL);
            }
            break;
        case 0:
            if (arg2 != NULL) {
                do {
                    if (mapBspPlaneSideTest(arg0, (u8 *)&sp58 + 2, arg2->unk4, arg2->unk8, arg2->unkC) != 0) {
                        listB = renderEntryAddOrUpdate(listB, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                    } else {
                        listA = renderEntryAddOrUpdate(listA, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                    }
                    arg2 = arg2->unk14;
                } while (arg2 != NULL);
            }
            mapTreeDistributeEntries(arg0->unk0, arg1->unkC, (MapDistributeEntry *)listA);
            mapTreeDistributeEntries(arg0->unk4, arg1->unk10, (MapDistributeEntry *)listB);
            renderEntryListFree(listA);
            renderEntryListFree(listB);
            break;
    }
}

typedef struct MapNodeBounds {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ s16 unkA2;
    /* 0xA4 */ s16 unkA4;
    /* 0xA6 */ s16 unkA6;
    /* 0xA8 */ s16 unkA8;
    /* 0xAA */ s16 unkAA;
} MapNodeBounds;


s32 mapNodeBoxInFrustum(MapBspNode *, f32, f32, f32);
void mapChunkFrameUpdate(f32, f32, f32);
void mapChunkClearNodeFlags(u8);
void mapChunkFreeNodeLists(u8);
void mapChunkRebuildNodeLists(f32, f32, f32, u8);
void mapChunkBuildSpriteChains(f32, f32, f32, u8);
s32 renderEntryListSortByDistance(s32, f32, f32, f32, void *);
void renderEntryListClearTouched(s32);
s32 renderEntryListPurgeUntouched(s32);
s32 spriteListBuildDisplayChain(s32, s32, f32, f32, f32);

void mapTreeFrameUpdate(MapBspNode *arg0, MapVisNode *arg1, MapDistributeEntry *arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8) {
    s32 listA;
    s32 listB;
    s32 kind;
    s32 sp58;
    s16 sp56;

    if (0) {
        mapChunkUpdateEntryNode((MapDistributeEntry *)&arg6);
    }
    listA = 0;
    listB = 0;
    if (arg0 == NULL) {
        return;
    }
    if (arg6 == 0 && mapNodeBoxInFrustum(arg0, arg3, arg4, arg5) == 0) {
        arg1->unk1 = 3;
        return;
    }
    kind = arg0->unkB8;
    if (kind != 0) {
        if (kind != 1) {
            if (kind == 2) {
                arg1->unk1 = 0;
                mapChunkFrameUpdate(arg3, arg4, arg5);
                if (arg7 == 0) {
                    mapChunkClearNodeFlags(arg8);
                    if (arg2 != NULL) {
                        do {
                            mapChunkUpdateEntryNode(arg2);
                            arg2 = arg2->unk14;
                        } while (arg2 != NULL);
                    }
                    mapChunkFreeNodeLists(arg8);
                    mapChunkRebuildNodeLists(arg3, arg4, arg5, arg8);
                    mapChunkBuildSpriteChains(arg3, arg4, arg5, arg8);
                    D_807F5FFC = renderEntryListSortByDistance(D_807F5FFC, arg3, arg4, arg5, &sp58);
                }
            }
        } else {
            arg1->unk1 = 0;
            if (arg7 == 0) {
                renderEntryListClearTouched((s32)arg1->unk4);
                if (arg2 != NULL) {
                    do {
                        arg1->unk4 = (MapBspNode *)renderEntryAddOrUpdate((s32)arg1->unk4, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                        arg2 = arg2->unk14;
                    } while (arg2 != NULL);
                }
                arg1->unk4 = (MapBspNode *)renderEntryListPurgeUntouched((s32)arg1->unk4);
                arg1->unk4 = (MapBspNode *)renderEntryListSortByDistance((s32)arg1->unk4, arg3, arg4, arg5, &sp58);
                arg1->unk8 = spriteListBuildDisplayChain((s32)arg1->unk4, 0, arg3, arg4, arg5);
                D_807F5FFC = renderEntryListSortByDistance(D_807F5FFC, arg3, arg4, arg5, &sp58);
            }
        }
    } else {
        if (arg2 != NULL) {
            do {
                if (mapBspPlaneSideTest(arg0, (u8 *)&sp56, arg2->unk4, arg2->unk8, arg2->unkC) != 0) {
                    listB = renderEntryAddOrUpdate(listB, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                } else {
                    listA = renderEntryAddOrUpdate(listA, arg2->unk24, arg2->unk0, arg2->unk4, arg2->unk8, arg2->unkC, arg2->unk1C, arg2->unk1E, arg2->unk22, arg2->unk20, 0);
                }
                arg2 = arg2->unk14;
            } while (arg2 != NULL);
        }
        arg1->unk0 = mapBspPlaneSideTest(arg0, &arg1->unk1, arg3, arg4, arg5);
        if (arg6 != 0) {
            mapTreeFrameUpdate(arg0->unk0, arg1->unkC, (MapDistributeEntry *)listA, arg3, arg4, arg5, arg6, arg7, arg8);
            mapTreeFrameUpdate(arg0->unk4, arg1->unk10, (MapDistributeEntry *)listB, arg3, arg4, arg5, arg6, arg7, arg8);
        } else {
            if (arg1->unk1 != 0) {
                if (arg1->unk1 == 1 || arg1->unk1 == 2) {
                    if (arg1->unk0 != 0) {
                        mapTreeFrameUpdate(arg0->unk4, arg1->unk10, (MapDistributeEntry *)listB, arg3, arg4, arg5, arg6, arg7, arg8);
                    } else {
                        mapTreeFrameUpdate(arg0->unk0, arg1->unkC, (MapDistributeEntry *)listA, arg3, arg4, arg5, arg6, arg7, arg8);
                    }
                }
            } else {
                mapTreeFrameUpdate(arg0->unk0, arg1->unkC, (MapDistributeEntry *)listA, arg3, arg4, arg5, arg6, arg7, arg8);
                mapTreeFrameUpdate(arg0->unk4, arg1->unk10, (MapDistributeEntry *)listB, arg3, arg4, arg5, arg6, arg7, arg8);
            }
        }
        renderEntryListFree(listA);
        renderEntryListFree(listB);
    }
}

s32 mapBspBoxInFrustum(s16, s16, s16, s16, s16, s16, f32, f32, f32, f32, void *);

s32 mapNodeBoxInFrustum(MapBspNode *arg0, f32 arg1, f32 arg2, f32 arg3) {
    MapNodeBounds *box;

    box = (MapNodeBounds *)arg0;
    return mapBspBoxInFrustum(box->unkA0, box->unkA2, box->unkA4, box->unkA6, box->unkA8, box->unkAA, arg1, arg2, arg3, D_807F5FA8, D_807F5E68);
}

extern f32 D_807F5E50[];

void planeFromTwoPoints(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    D_807F5E50[0] = arg3 - arg0;
    D_807F5E50[1] = arg4 - arg1;
    D_807F5E50[2] = arg5 - arg2;
    D_807F5E50[3] = -(((D_807F5E50[0] * arg0) + (D_807F5E50[1] * arg1)) + (D_807F5E50[2] * arg2));
}


typedef struct ClipPlane {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[7];
    /* 0x20 */ f64 unk20;
    /* 0x28 */ f64 unk28;
    /* 0x30 */ f64 unk30;
    /* 0x38 */ f64 unk38;
} ClipPlane;


f32 boxMinCornerDistance(s16, s16, s16, s16, s16, s16, f32, f32, f32);
s32 clipPolyToBox(s32, s16, s16, s16, s16, s16, s16, void *);

s32 mapBspBoxInFrustum(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, void *arg10) {
    s32 in1;
    s32 in2;
    s32 behind;
    s32 i;
    f64 d;
    s32 pad0;

    if ((((f32)arg0 * D_807F5E50[0] + (f32)arg1 * D_807F5E50[1]) + (f32)arg2 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        (((f32)arg0 * D_807F5E50[0] + (f32)arg1 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        (((f32)arg0 * D_807F5E50[0] + arg4 * D_807F5E50[1]) + (f32)arg2 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        (((f32)arg0 * D_807F5E50[0] + arg4 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        ((arg3 * D_807F5E50[0] + (f32)arg1 * D_807F5E50[1]) + (f32)arg2 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        ((arg3 * D_807F5E50[0] + (f32)arg1 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        ((arg3 * D_807F5E50[0] + arg4 * D_807F5E50[1]) + (f32)arg2 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        ((arg3 * D_807F5E50[0] + arg4 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) + D_807F5E50[3] < 0.0) {
        return 0;
    }
    in1 = 0;
    in2 = 0;
    behind = 0;
    if ((f32)arg0 <= arg6 && arg6 <= (f32)arg3 && (f32)arg1 <= arg7 && arg7 <= (f32)arg4 && (f32)arg2 <= arg8 && arg8 <= (f32)arg5) {
        return 1;
    }
    for (i = 0; i < 5 && behind == 0; i++) {
        d = ((((ClipPlane *)arg10)[i].unk20 * arg0 + ((ClipPlane *)arg10)[i].unk28 * arg1) + ((ClipPlane *)arg10)[i].unk30 * arg2) + ((ClipPlane *)arg10)[i].unk38;
        if (d < 0.00) {
            in1 = 1;
        }
        d = ((((ClipPlane *)arg10)[i].unk20 * arg0 + ((ClipPlane *)arg10)[i].unk28 * arg4) + ((ClipPlane *)arg10)[i].unk30 * arg2) + ((ClipPlane *)arg10)[i].unk38;
        if (d < 0.00) {
            if (arg4 && arg4) {} // LAYOUT: lowers arg4's cvt candidate priority (FP colouring of the head)
            in2 = 1;
        }
        if (in1 != 0 && in2 != 0) {
            behind = 1;
        }
    }
    if (behind == 0 && boxMinCornerDistance(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) < arg9) {
        return 1;
    }
    for (i = 0; i < 5; i++) {
        if (clipPolyToBox(i, arg0, arg1, arg2, arg3, arg4, arg5, arg10) != 0) {
            return 1;
        }
    }
    return 0;
}

f32 boxMinCornerDistance(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, f32 arg6, f32 arg7, f32 arg8) {
    f32 new_var;
    f32 sp30;
    f32 var_fs0;
    f32 sp58;
    f32 temp_fs1;
    f32 sp38;
    f32 sp3C;
    f32 temp_fs2;

    var_fs0 = (f32)arg0;
    sp3C = (var_fs0 - arg6) * (var_fs0 - arg6);
    sp38 = (((f32)arg1 - arg7) * ((f32)arg1 - arg7));
    temp_fs1 = (((f32)arg2 - arg8) * ((f32)arg2 - arg8));
    new_var = (((f32)arg4 - arg7) * ((f32)arg4 - arg7));
    temp_fs2 = (((f32)arg5 - arg8) * ((f32)arg5 - arg8));
    var_fs0 = (sp3C + sp38) + temp_fs1;
    sp30 = (sp58 = (sp3C + sp38) + temp_fs2);
    if (sp30 < var_fs0) {
        var_fs0 = sp30;
    }
    if ((sp3C + new_var) + temp_fs1 < var_fs0) {
        var_fs0 = (sp3C + new_var) + temp_fs1;
    }
    if ((sp3C + new_var) + temp_fs2 < var_fs0) {
        var_fs0 = (sp3C + new_var) + temp_fs2;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs1 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs1;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs2 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + sp38) + temp_fs2;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + new_var) + temp_fs1 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + new_var) + temp_fs1;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + new_var) + temp_fs2 < var_fs0) {
        var_fs0 = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + new_var) + temp_fs2;
    }
    return sqrtf(var_fs0);
}


void clipPolyAgainstAxis(s16 *, s16 *, s32, s32 *, u8, f64, u8);

s32 clipPolyToBox(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, void *arg7) {
    s16 sp88[0x24];
    s16 sp40[0x24];
    s32 sp3C;
    char pad;

    clipPolyAgainstAxis((s16 *)((u8 *)arg7 + (arg0 << 6)), sp88, ((ClipPlane *)((u8 *)arg7 + (arg0 << 6)))->unk18, &sp3C, 0, arg1, 0);
    if (sp3C == 0) {
        return 0;
        do {
        } while (0);
    }
    clipPolyAgainstAxis(sp88, sp40, sp3C, &sp3C, 0, arg4, 1);
    if (sp3C == 0) {
        return 0;
    }
    clipPolyAgainstAxis(sp40, sp88, sp3C, &sp3C, 1, arg2, 0);
    if (sp3C == 0) {
        return 0;
    }
    clipPolyAgainstAxis(sp88, sp40, sp3C, &sp3C, 1, arg5, 1);
    if (sp3C == 0) {
        return 0;
    }
    clipPolyAgainstAxis(sp40, sp88, sp3C, &sp3C, 2, arg3, 0);
    if (sp3C == 0) {
        return 0;
    }
    clipPolyAgainstAxis(sp88, sp40, sp3C, &sp3C, 2, arg6, 1);
    if (sp3C != 0) {
        return 1;
    }
    return 0;
}

s32 clipVertexTestAxis(s16 *, u8, f64, u8);
void clipVertexAppend(void *, s32 *, void *);
void clipEdgeIntersectAxis(s16 *, s16 *, u8, f64, s16 *);

void clipPolyAgainstAxis(s16 *arg0, s16 *arg1, s32 arg2, s32 *arg3, u8 arg4, f64 arg5, u8 arg6) {
    s32 i;
    s16 *prev;
    s16 sp60[3];
    s16 *cur;
    s16 *last;

    *arg3 = 0;
    prev = (s16 *)(arg2 * 6 + (s32)arg0 - 6);
    i = 0;
    if (arg2 > 0) {
        cur = arg0;
        do {
            last = cur;
            if (clipVertexTestAxis(cur, arg4, arg5, arg6) != 0) {
                if (clipVertexTestAxis(prev, arg4, arg5, arg6) != 0) {
                    clipVertexAppend(cur, arg3, arg1);
                } else {
                    clipEdgeIntersectAxis(prev, cur, arg4, arg5, sp60);
                    clipVertexAppend(sp60, arg3, arg1);
                    clipVertexAppend(cur, arg3, arg1);
                }
            } else if (clipVertexTestAxis(prev, arg4, arg5, arg6) != 0) {
                clipEdgeIntersectAxis(prev, cur, arg4, arg5, sp60);
                clipVertexAppend(sp60, arg3, arg1);
            }
            i++;
            cur += 3;
            prev = last;
        } while (i != arg2);
    }
}

s32 clipVertexTestAxis(s16 *arg0, u8 arg1, f64 arg2, u8 arg3) {
    f64 coord;

    switch (arg1) {
        case 0:
            coord = arg0[0];
            break;
        case 1:
            coord = arg0[1];
            break;
        case 2:
            coord = arg0[2];
            break;
    }
    switch (arg3) {
        case 0:
            if (arg2 <= coord) {
                return 1;
            }
            break;
        case 1:
            if (coord <= arg2) {
                return 1;
            }
            break;
    }
    return 0;
}

void faultSetMessage(s32, s32, s32, s32);

void clipVertexAppend(void *arg0, s32 *arg1, void *arg2) {
    memcpy((u8 *)arg2 + *arg1 * 6, arg0, 6);
    *arg1 += 1;
    if (*arg1 >= 0xD) {
        faultSetMessage(1, 0, 0, 0);
    }
}

void clipEdgeIntersectAxis(s16 *arg0, s16 *arg1, u8 arg2, f64 arg3, s16 *arg4) {
    f32 t;

    switch (arg2) {
        case 0:
            t = (arg3 - arg0[0]) / (arg1[0] - arg0[0]);
            arg4[1] = (arg1[1] - arg0[1]) * t + arg0[1];
            arg4[2] = (arg1[2] - arg0[2]) * t + arg0[2];
            arg4[0] = arg3;
            break;
        case 1:
            t = (arg3 - arg0[1]) / (arg1[1] - arg0[1]);
            arg4[0] = (arg1[0] - arg0[0]) * t + arg0[0];
            arg4[2] = (arg1[2] - arg0[2]) * t + arg0[2];
            arg4[1] = arg3;
            break;
        case 2:
            t = (arg3 - arg0[2]) / (arg1[2] - arg0[2]);
            arg4[0] = (arg1[0] - arg0[0]) * t + arg0[0];
            arg4[1] = (arg1[1] - arg0[1]) * t + arg0[1];
            arg4[2] = arg3;
            break;
    }
}

typedef struct Bsp_Plane {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ s16 unk5C[3];
    /* 0x62 */ s16 unk62[3];
    /* 0x68 */ s16 unk68[3];
} Bsp_Plane;

s32 mapBspPlaneDistanceCheck(Bsp_Plane *, f32, f32, f32);


#define arg0 ((Bsp_Plane *)arg0v)
u8 mapBspPlaneSideTest(void *arg0v, u8 *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 ea[3];
    f32 eb[3];
    f32 c[3];
    f32 n[3];
    f32 len;
    f32 p[3];
    f64 s1;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 d;
    *arg1 = mapBspPlaneDistanceCheck(arg0, arg2, arg3, arg4);
    nz = arg0->unk54;
    ny = arg0->unk50;
    nx = arg0->unk4C;
    d = arg0->unk58;
    ea[0] = arg0->unk5C[2] - arg0->unk5C[0];
    ea[1] = arg0->unk62[2] - arg0->unk62[0];
    ea[2] = arg0->unk68[2] - arg0->unk68[0];
    eb[0] = arg0->unk5C[1] - arg0->unk5C[0];
    eb[1] = arg0->unk62[1] - arg0->unk62[0];
    eb[2] = arg0->unk68[1] - arg0->unk68[0];
    c[0] = ea[1] * eb[2] - ea[2] * eb[1];
    c[1] = ea[2] * eb[0] - ea[0] * eb[2];
    c[2] = ea[0] * eb[1] - ea[1] * eb[0];
    len = sqrtf(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    n[0] = c[0] / len;
    n[1] = c[1] / len;
    n[2] = c[2] / len;
    n[0] = n[0] * 20.000f;  // LAYOUT: separate (uncoloured) 20.0f literal web
    n[1] = 20.0f * n[1];
    n[2] = n[2] * 20.00f;  // LAYOUT: separate (uncoloured) 20.0f literal web
    p[0] = arg0->unk5C[0] + n[0];
    p[1] = arg0->unk62[0] + n[1];
    p[2] = arg0->unk68[0] + n[2];
    s1 = nx * arg2 + ny * arg3 + nz * arg4 + d;
    if (s1 > 0.0) {
        if (ny > 0.0f) {}  // LAYOUT: colours nx/ny/nz f14/f16/f18
        if (nx * p[0] + ny * p[1] + nz * p[2] + d > 0.0) {
            if (nx && nx) {}  // LAYOUT: nx coloured before nz
            return 0;
        }
    }
    if (s1 < 0.0) {
        if (nx * p[0] + ny * p[1] + p[2] * nz + d < 0.0) {
            return 0;
        }
    }
    return 1;
}
#undef arg0

s32 mapBspPlaneDistanceCheck(Bsp_Plane *arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 pad[14];
    s32 i;
    f64 dot;
    f32 len;
    f64 dist;
    f64 d;
    f64 t;
    f64 absd;
    f64 nx;
    f64 ny;
    f64 nz;
    f64 dx;
    f64 dy;
    f64 dz;

    i = 0;
    dot = arg0->unk4C * arg1 + arg0->unk50 * arg2 + arg0->unk54 * arg3 + arg0->unk58;
    len = sqrtf(arg0->unk4C * arg0->unk4C + arg0->unk50 * arg0->unk50 + arg0->unk54 * arg0->unk54);
    if (dot && dot) {}  // LAYOUT: dead reference steers uopt candidate priority
    dist = dot / len;
    absd = dist;
    if (dist < 0.0) {
        absd = 0.0 - dist;
    }
    if (absd > 300.0) {
        return 2;
    }
    nx = arg0->unk4C;
    ny = arg0->unk50;
    nz = arg0->unk54;
    do {
        dx = *(f32 *)((u8 *)D_807F5E20 + i * 12 + 0) - arg1;
        dy = *(f32 *)((u8 *)D_807F5E20 + i * 12 + 4) - arg2;
        dz = *(f32 *)((u8 *)D_807F5E20 + i * 12 + 8) - arg3;
        if (dx) {}  // LAYOUT: lowers dx priority (extra block in its range)
        d = nx * dx + ny * dy + nz * dz;
        if (d > 0.01 || d < -0.01) {
            t = dot / d;
            if (t <= 0.0 && 0.0 - t <= 1.0) {
                return 0;
            }
        }
        i++;
    } while ((f32 *)((u8 *)D_807F5E20 + i * 12) < D_807F5E50);
    return 1;
}


typedef struct MapChunkRecord {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[6];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x70];
} MapChunkRecord; /* 0x7C */

extern u8 D_807F5FC1;
extern MapChunkRecord *D_807F5FC4;

typedef struct RawGfxCmd {
    u32 unk0;
    u32 unk4;
} RawGfxCmd;

RawGfxCmd *mapChunkEmitSegmentCommands(arg0, arg1)
RawGfxCmd *arg0;
u8 arg1;
{
    RawGfxCmd *q;
    MapChunkRecord *c;
    s32 i;
    s32 sel;

    for (i = 0; i < D_807F5FC1; i++) {
        sel = arg1;
        c = (MapChunkRecord *)((u8 *)D_807F5FC4 + i * 0x7C);
        if (sel == c->unk1) {
            q = arg0++;
            q->unk0 = ((c->unk0 * 4) & 0xFFFF) | 0xDB060000;
            q->unk4 = D_807F5FC4[i].unk8;
        }
    }
    return arg0;
}

typedef struct MapChunkAnim {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC[1];
    /* 0x10 */ u8 pad10[0x6C];
} MapChunkAnim; /* 0x7C */

void assetFreeBuffer(s32, s32, s32);
s32 assetLoad(s32, s32, s32, s32);

#define MAP_CHUNK_ANIM ((MapChunkAnim *)D_807F5FC4)[i]

void mapChunkAnimateTextures(u8 arg0) {
    s32 i;
    s32 flag;

    for (i = 0; i < D_807F5FC1; i++) {
        if (arg0 == MAP_CHUNK_ANIM.unk1) {
            flag = 0;
            MAP_CHUNK_ANIM.unk4++;
            if (MAP_CHUNK_ANIM.unk4 == MAP_CHUNK_ANIM.unk2) {
                MAP_CHUNK_ANIM.unk4 = 0;
                MAP_CHUNK_ANIM.unk5++;
                if (MAP_CHUNK_ANIM.unk5 == MAP_CHUNK_ANIM.unk3) {
                    MAP_CHUNK_ANIM.unk5 = 0;
                }
                flag = 1;
            }
            if (MAP_CHUNK_ANIM.unk8 == 0) {
                flag = 1;
            }
            if (flag) {
                if (MAP_CHUNK_ANIM.unk8 != 0) {
                    assetFreeBuffer(MAP_CHUNK_ANIM.unk8, 0x7E3, 5);
                }
                MAP_CHUNK_ANIM.unk8 = assetLoad(7, MAP_CHUNK_ANIM.unkC[MAP_CHUNK_ANIM.unk5], 0, 0);
            }
        }
    }
}

#undef MAP_CHUNK_ANIM


s32 mapChunkIsVisible(u8);

void mapChunkFreeHiddenBuffers(void) {
    s32 i;

    for (i = 0; i < D_807F5FC1; i++) {
        if (mapChunkIsVisible(D_807F5FC4[i].unk1) == 0) {
            if (D_807F5FC4[i].unk8 != 0) {
                assetFreeBuffer(D_807F5FC4[i].unk8, 0x7FB, 5);
                D_807F5FC4[i].unk8 = 0;
            }
        }
    }
}

typedef struct MapFileHeader {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 pad9;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 pad3C[4];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
} MapFileHeader;

#define MAP_HDR ((MapFileHeader *)arg0)

extern f32 D_807444C4;
extern s32 D_807FB5E0;
extern s32 D_807FB5E4;
extern s16 D_807FB5E8;
extern s16 D_807FB5EA;
extern s16 D_807F9450;
extern s16 D_807F9452;
extern s16 D_807F9454;
extern s16 D_807F9456;
extern s16 D_807FD574;
extern s16 D_807FD576;
extern s16 D_807FD578;
extern s16 D_807F5FE4;
extern s16 D_807F5FE6;
extern s16 D_807F5FE8;
extern s16 D_807F5FEA;
extern s32 D_807F5FD0;
extern s32 *D_807F5FD4;
extern s32 D_807F5FC8;
extern s32 D_807F5FCC;

void fogSetParams(u8);
void renderSetSegment6Override(u8);
void lightSetTargetColor(f32, f32, f32, s16);
void lightCopyTargetColors(s16);
void matrixCacheInit(s32);
struct MapRelocNode;
void mapTreeRelocate(struct MapRelocNode *, s32, s32);
void displayListResolveTextureImages();
void mapRelocateOffsetTable(s32);
void mapSurfaceEffectsReset(void);
void mapChunksInitFromMapData(void *);
void collisionInitStaticCache(void *);
void collisionBuildCellTable(void *);
void effectWaterInitNodes(void *);
void actorTargetTableLoad(void *);
void triggerZoneInit(void *);
void func_8062F318(void);

void mapHeaderLoad(s32 arg0) {
    s32 off30;
    s32 off34;
    s32 off38;
    s32 off44;
    s32 off40;
    s32 off48;
    s32 pad[5];
    s32 sp28;

    D_807F5DE0 = (u8 *)arg0;
    sp28 = 0;
    D_807F5FDC = cosApprox(0.7853981853f);
    fogSetParams(MAP_HDR->unk8 & 1);
    renderSetSegment6Override((MAP_HDR->unk8 >> 1) & 1);
    D_807444C4 = MAP_HDR->unkA;
    D_807FB5E0 = MAP_HDR->unk14 << 3;
    D_807FB5E4 = MAP_HDR->unk16 << 3;
    D_807FB5E8 = MAP_HDR->unk10;
    D_807FB5EA = MAP_HDR->unk12;
    D_807F9450 = MAP_HDR->unk1C;
    D_807F9452 = MAP_HDR->unk1E;
    D_807F9454 = MAP_HDR->unk18;
    D_807F9456 = MAP_HDR->unk1A;
    D_807FD574 = MAP_HDR->unk20;
    D_807FD576 = MAP_HDR->unk22;
    D_807FD578 = MAP_HDR->unk24;
    D_807F5FE4 = MAP_HDR->unk26;
    D_807F5FE6 = MAP_HDR->unk28;
    D_807F5FE8 = MAP_HDR->unk2A;
    D_807F5FEA = MAP_HDR->unk2C;
    off40 = MAP_HDR->unk40;
    off30 = MAP_HDR->unk30;
    off34 = MAP_HDR->unk34;
    off38 = MAP_HDR->unk38;
    off44 = MAP_HDR->unk44;
    off48 = MAP_HDR->unk48;
    D_807F5FD0 = *(s32 *)(D_807F5DE0 + off40) + 1;
    D_807F5FD4 = (s32 *)(D_807F5DE0 + off40 + 4);
    D_807F5FC8 = *(s32 *)(D_807F5DE0 + off44);
    D_807F5FCC = (s32)(D_807F5DE0 + off44 + 4);
    D_807F5FC1 = *(s32 *)(D_807F5DE0 + off48);
    D_807F5FC4 = (MapChunkRecord *)(D_807F5DE0 + off48 + 4);
    D_807F5DE4 = (MapBspNode *)(D_807F5DE0 + off30);
    D_807F5DE8 = (s32)(D_807F5DE0 + off38);
    D_807F5DEC = D_807F5DE0 + off34;
    lightSetTargetColor(1.0f, 1.0f, 1.0f, -1);
    lightCopyTargetColors(-1);
    matrixCacheInit(MAP_HDR->unkE << 10);
    mapTreeRelocate((struct MapRelocNode *)(s32)(D_807F5DE0 + off30), (s32)(D_807F5DE0 + off30), (s32)(D_807F5DE0 + off34));
    displayListResolveTextureImages(D_807F5DE0 + off34, D_807F5DE0 + off38);
    mapRelocateOffsetTable((s32)(D_807F5DE0 + off40));
    mapSurfaceEffectsReset();
    mapNodeTreeInitSurfaceEffects((MapNodeEffects *)D_807F5DE4, &sp28);
    mapOffsetSlotsInit(sp28);
    D_807F5E60 = (MapVisNode *)mapTreeCloneShape((MapTreeLinks *)D_807F5DE4);
    mapChunksInitFromMapData((void *)arg0);
    collisionInitStaticCache((void *)arg0);
    collisionBuildCellTable((void *)arg0);
    effectWaterInitNodes((void *)arg0);
    actorTargetTableLoad((void *)arg0);
    triggerZoneInit((void *)arg0);
    func_8062F318();
}

#undef MAP_HDR

void func_8062F318(void) {
    D_807F5FED = 1;
}


void mapRelocateOffsetTable(s32 arg0) {
    s32 i;
    s32 t;

    if (D_807F5FD0 != 0) {
        i = 0;
        if (D_807F5FD0 >= 0) {
            do {
                t = D_807F5FD4[i];
                D_807F5FD4[i] = t + arg0;
                i++;
            } while (D_807F5FD0 >= i);
        }
    }
}


s32 func_8062F388(s32 *arg0) {
    *arg0 = D_807F5FCC;
    return D_807F5FC8;
}

void displayListResolveTextureImages(RawGfxCmd *arg0, RawGfxCmd *arg1) {
    u32 w;

    for (; arg0 != arg1; arg0++) {
        w = arg0->unk0;
        if ((w >> 24) == (0, 0xFD)) {
            if (((arg0->unk4 << 4) >> 28) == 0) {
                arg0->unk4 = assetLoad(0x19, arg0->unk4, 1, 0);
            }
            ;
        }
    }
}

typedef struct MapRelocNode {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C[1];
    /* 0x20 */ u8 pad20[0x98];
    /* 0xB8 */ u8 unkB8;
    /* 0xB9 */ u8 padB9[0xC];
    /* 0xC5 */ u8 unkC5;
} MapRelocNode;

void mapTreeRelocate(MapRelocNode *arg0, s32 arg1, s32 arg2) {
    s32 i;

    if (arg0 == NULL) {
        return;
    }
    switch (arg0->unkB8) {
        case 0:
            arg0->unk0 += arg1;
            arg0->unk4 += arg1;
            mapTreeRelocate((MapRelocNode *)arg0->unk0, arg1, arg2);
            mapTreeRelocate((MapRelocNode *)arg0->unk4, arg1, arg2);
            return;
        case 1:
        case 2:
            break;
        default:
            return;
    }
    if (arg0->unk8 != -1) {
        arg0->unk8 += arg2;
    }
    if (arg0->unkC != -1) {
        arg0->unkC += arg2;
    }
    if (arg0->unk10 != -1) {
        arg0->unk10 += arg2;
    }
    if (arg0->unk14 != -1) {
        arg0->unk14 += arg2;
    }
    if (arg0->unk18 != -1) {
        arg0->unk18 += arg2;
    }
    for (i = 0; i < arg0->unkC5; i++) {
        arg0->unk1C[i] += arg2;
    }
}

void matrix3SwapRows(f32 (*arg0)[3], s32 arg1, s32 arg2, s32 arg3) {
    f32 t;
    s32 i;

    if (arg1 != 0) {
        i = 0;
        if (arg2 == 0) {
            for (i = 0; i < 3; i++) {
                t = arg0[arg2][i];
                arg0[arg2][i] = arg0[arg1][i];
                arg0[arg1][i] = t;
            }
            arg2 = arg1;
        } else {
            for (i = 0; i < 3; i++) {
                t = arg0[arg3][i];
                arg0[arg3][i] = arg0[arg1][i];
                arg0[arg1][i] = t;
            }
            arg3 = arg1;
        }
    }
    if (arg2 != 1) {
        for (i = 0; i < 3; i++) {
            t = arg0[arg3][i];
            arg0[arg3][i] = arg0[arg2][i];
            arg0[arg2][i] = t;
        }
    }
}

void matrix3SwapRows(f32 (*)[3], s32, s32, s32);

s32 func_8062F640(f32 (*arg0)[3], f32 (*arg1)[3], s32 arg2) {
    s32 r0;
    s32 r1;
    s32 p;
    s32 q;
    s32 j;
    f32 t;
    f32 u;

    if (arg2 == 0) {
        r0 = 1;
        r1 = 2;
    } else if (arg2 == 1) {
        r0 = 0;
        r1 = 2;
    } else {
        r0 = 0;
        r1 = 1;
    }
    t = arg0[r0][1];
    if (t < 0.0f) {
        t = -t;
    }
    u = arg0[r1][1];
    if (u < 0.0f) {
        u = -u;
    }
    if (u < t) {
        p = r0;
    } else {
        p = r1;
    }
    if (p == r0) {
        q = r1;
    } else {
        q = r0;
    }
    if (arg0[p][1] < 1e-8 && arg0[p][1] > -1e-8) {
        return 0;
    }
    t = 1.0 / arg0[p][1];
    arg0[p][1] = 1.0f;
    arg0[p][2] *= t;
    arg1[p][p] = t;
    arg1[p][arg2] *= t;
    for (j = 0; j < 3; j++) {
        if (j != p) {
            t = arg0[j][1];
            arg0[j][1] = 0.0f;
            t = -t;
            arg0[j][2] += t * arg0[p][2];
            arg1[j][p] = arg1[p][p] * t;
            arg1[j][arg2] += t * arg1[p][arg2];
        }
    }
    if (arg0[q][2] < 1e-8 && arg0[q][2] > -1e-8) {
        return 0;
    }
    t = 1.0 / arg0[q][2];
    arg0[q][2] = 1.0f;
    arg1[q][q] = t;
    arg1[q][arg2] *= t;
    arg1[q][p] *= t;
    for (j = 0; j < 3; j++) {
        if (j != q) {
            t = arg0[j][2];
            arg0[j][2] = 0.0f;
            t = -t;
            arg1[j][arg2] += t * arg1[q][arg2];
            arg1[j][p] += t * arg1[q][p];
            arg1[j][q] += t * arg1[q][q];
        }
    }
    matrix3SwapRows(arg1, arg2, p, q);
    return 1;
}


s32 matrix3Invert(f32 (*arg0)[3], f32 (*arg1)[3]) {
    s32 p;
    s32 j;
    f32 t;
    f32 u;
    f32 v;

    arg1[2][2] = 1.0f;
    arg1[2][1] = 0.0f;
    arg1[2][0] = 0.0f;
    arg1[1][2] = 0.0f;
    arg1[1][1] = 1.0f;
    arg1[1][0] = 0.0f;
    arg1[0][2] = 0.0f;
    arg1[0][1] = 0.0f;
    arg1[0][0] = 1.0f;
    t = arg0[0][0];
    if (t < 0.0f) {
        t = -t;
    }
    u = arg0[1][0];
    if (u < 0.0f) {
        u = -u;
    }
    v = arg0[2][0];
    if (v < 0.0f) {
        v = -v;
    }
    if (u < t) {
        if (v < t) {
            p = 0;
        } else {
            p = 2;
        }
    } else {
        if (v < u) {
            p = 1;
        } else {
            p = 2;
        }
    }
    if (arg0[p][0] < 1e-8 && arg0[p][0] > -1e-8) {
        return 0;
    }
    v = 1.0 / arg0[p][0];
    arg0[p][0] = 1.0f;
    arg0[p][1] *= v;
    arg0[p][2] *= v;
    arg1[p][p] = v;
    for (j = 0; j < 3; j++) {
        if (j != p) {
            v = arg0[j][0];
            arg0[j][0] = 0.0f;
            v = -v;
            arg0[j][1] += v * arg0[p][1];
            arg0[j][2] += v * arg0[p][2];
            arg1[j][p] = arg1[p][p] * v;
        }
    }
    if (func_8062F640(arg0, arg1, p) == 0) {
        return 0;
    }
    return 1;
}


s32 func_8062FBC8(f32 (*arg0)[4], f32 *arg1, f32 *arg2, s32 *arg3) {
    f32 max;
    f32 abs;
    s32 i;
    s32 j;
    f32 tmp;

    *arg3 = -1;
    abs = arg0[3][3] > 0.0f ? arg0[3][3] : -arg0[3][3];
    if (abs < 1e-8) {
        max = 0.0f;
        for (i = 0; i < 4; i++) {
            if (max < arg0[i][3]) {
                *arg3 = i;
                max = arg0[i][3];
            } else if (arg0[i][3] < -max) {
                *arg3 = i;
                max = -arg0[i][3];
            }
        }
        if (*arg3 < 0) {
            return 0;
        }
        for (j = 0; j < 4; j++) {
            tmp = arg0[3][j];
            arg0[3][j] = arg0[*arg3][j];
            arg0[*arg3][j] = tmp;
        }
    }
    arg1[0] = -arg0[0][3];
    arg1[1] = -arg0[1][3];
    arg1[2] = -arg0[2][3];
    *arg2 = 1.0 / arg0[3][3];
    arg0[0][3] = 0.0f;
    arg0[1][3] = 0.0f;
    arg0[2][3] = 0.0f;
    arg0[3][3] = 1.0f;
    arg0[3][0] *= *arg2;
    arg0[3][1] *= *arg2;
    arg0[3][2] *= *arg2;
    for (i = 0; i < 3; i++) {
        arg0[0][i] += arg1[0] * arg0[3][i];
        arg0[1][i] += arg1[1] * arg0[3][i];
        arg0[2][i] += arg1[2] * arg0[3][i];
    }
    return 1;
}


s32 matrix4Invert(f32 (*arg0)[4], f32 (*arg1)[4]) {
    f32 m[4][4];
    f32 n[4][3];
    f32 inv[3][3];
    f32 scale;
    s32 i;
    s32 k;
    f32 w[3];
    f32 tmp;
    f32 v[3];
    s32 idx;
    s32 flag;

    for (i = 0; i < 4; i++) {
        for (k = 0; k < 4; k++) {
            m[i][k] = arg1[i][k];
            arg0[i][k] = 0.0f;
        }
    }
    arg0[0][0] = 1.0f;
    arg0[1][1] = 1.0f;
    arg0[2][2] = 1.0f;
    arg0[3][3] = 1.0f;
    flag = m[0][3] == 0.0; if (flag) { flag = m[1][3] == 0.0;
        if (flag) {
            flag = m[2][3] == 0.0;
            if (flag) {
                flag = m[3][3] == 1.0;
            }
        }
    }
    if (!flag) {
        if (!func_8062FBC8(m, w, &scale, &idx)) {
            return 0;
        }
    }
    v[0] = m[3][0];
    v[1] = m[3][1];
    v[2] = m[3][2];
    for (i = 0; i < 3; i++) {
        for (k = 0; k < 3; k++) {
            n[i][k] = m[i][k];
        }
    }
    if (!matrix3Invert(n, inv)) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        for (k = 0; k < 3; k++) {
            arg0[i][k] = inv[i][k];
        }
    }
    for (i = 0; i < 3; i++) {
        for (k = 0; k < 3; k++) {
            arg0[3][i] -= v[k] * inv[k][i];
        }
    }
    if (!flag) {
        for (i = 0; i < 4; i++) {
            arg0[i][3] += w[0] * arg0[i][0] + w[1] * arg0[i][1] + w[2] * arg0[i][2];
            arg0[i][3] *= scale;
        }
        if (idx >= 0) {
            for (i = 0; i < 4; i++) {
                tmp = arg0[i][3];
                arg0[i][3] = arg0[i][idx];
                arg0[i][idx] = tmp;
            }
        }
    }
    return 1;
}


