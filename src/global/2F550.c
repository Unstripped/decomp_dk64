#include "common.h"
#include "map.h"
#include "render.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/109660.h"
#include "proto/global/117190.h"
#include "proto/global/126260.h"
#include "proto/global/136820.h"
#include "proto/global/15050.h"
#include "proto/global/2F550.h"
#include "proto/global/35000.h"
#include "proto/global/36880.h"
#include "proto/global/41090.h"
#include "proto/global/42630.h"
#include "proto/global/55B20.h"
#include "proto/global/5DE10.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/63810.h"
#include "proto/global/63EC0.h"
#include "proto/global/67890.h"
#include "proto/global/684C0.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/CC800.h"

extern u8 gGfxBufferIndex;

extern u8 D_807444F0;
extern u8 gGameMode;
extern s8 D_807444C0;
extern s32 gCurrentMap;

f32 cameraStepAspectScale(void) {
    static f32 sc = 1.0f; // D_80747CD0: a function-local static so uopt treats it as non-aliased
    f32 target;
    f32 step;
    s32 flag;

    target = 1.0f;
    if (D_807444F0 != 1 && gGameMode == 1) {
        step = 999.0f;
    } else {
        step = 0.02f;
    }
    flag = gGameMode == 1;
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
    f32 halfYaw;
    f32 pitchMtx[4][4];
    f32 yawMtx[4][4];
    f32 dirZ;
    f32 dirY;
    f32 dirX;
    f32 halfPitch;
    s32 i;

    halfPitch = arg0 * 0.5;
    halfYaw = halfPitch * arg1;
    guRotateF(pitchMtx, halfPitch, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(pitchMtx, 0.0f, 0.0f, (-arg2), &dirX, &dirY, &dirZ);
    guRotateF(yawMtx, halfYaw, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(yawMtx, dirX, dirY, dirZ, &D_807F5DF0[0], &D_807F5DF0[1], &D_807F5DF0[2]);
    guRotateF(yawMtx, -halfYaw, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(yawMtx, dirX, dirY, dirZ, &D_807F5DF0[3], &D_807F5DF0[4], &D_807F5DF0[5]);
    guRotateF(pitchMtx, -halfPitch, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(pitchMtx, 0.0f, 0.0f, (-arg2), &dirX, &dirY, &dirZ);
    guRotateF(yawMtx, halfYaw, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(yawMtx, dirX, dirY, dirZ, &D_807F5DF0[6], &D_807F5DF0[7], &D_807F5DF0[8]);
    guRotateF(yawMtx, -halfYaw, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(yawMtx, dirX, dirY, dirZ, &D_807F5DF0[9], &D_807F5DF0[10], &D_807F5DF0[11]);
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


void frustumCornersTransformByInverse(Mtx *arg0) {
    f32 viewMtx[4][4];
    f32 invMtx[4][4];
    s32 i;

    guMtxL2F(viewMtx, arg0);
    matrix4Invert(invMtx, viewMtx);
    for (i = 0; i < 4; i++) {
        guMtxXFMF(invMtx, D_807F5DF0[i * 3], D_807F5DF0[i * 3 + 1], D_807F5DF0[i * 3 + 2], &D_807F5E20[i * 3], &D_807F5E24[i * 3], &D_807F5E28[i * 3]);
    }
}



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
        if (poly->d + (poly->a * xs[i] + poly->b * ys[i] + poly->c * zs[i]) < (0, 0.0)) {}  // FAKE: second use of the sum makes it a coloured candidate (f0) and keeps its tree order for LFTR
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
            guTranslate(&D_807F5FB8[i].mtx[gGfxBufferIndex], 0.0f, gMapChunkCount != 0 ? D_807F5FB8[i].unk80 * 3.0f : D_807F5FB8[i].unk80, 0.0f);
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


typedef struct MapBspNode {
    struct MapBspNode *child0;
    struct MapBspNode *child1;
    u8 pad8[0x4C - 0x8];
    /* 0x4C */ f32 unk4C; /* split plane normal x */
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58; /* split plane d */
    /* 0x5C */ s16 unk5C[3];
    /* 0x62 */ s16 unk62[3];
    /* 0x68 */ s16 unk68[3];
    u8 pad6E[0xA0 - 0x6E];
    /* 0xA0 */ s16 unkA0; /* bounds min x/y/z, max x/y/z */
    /* 0xA2 */ s16 unkA2;
    /* 0xA4 */ s16 unkA4;
    /* 0xA6 */ s16 unkA6;
    /* 0xA8 */ s16 unkA8;
    /* 0xAA */ s16 unkAA;
    u8 padAC[0xB8 - 0xAC];
    /* 0xB8 */ u8 kind; /* 0 split node, 1 leaf (MapLeafLists/MapViewEntries), 2 map chunks */
} MapBspNode;

typedef struct MapVisNode {
    u8 camSide; /* mapBspPlaneSideTest of the camera against the split plane */
    u8 visMode; /* 0 both children drawn, 1/2 one side only, 3 culled */
    u8 pad2[2];
    struct RenderEntry *entries; /* render entry list */
    struct SpriteDisplayNode *sprites; /* sprite chain built from entries */
    struct MapVisNode *child0;
    struct MapVisNode *child1;
} MapVisNode;

MapVisNode *mapTreeCloneShape(MapBspNode *bsp) {
    MapVisNode *node;

    if (bsp == NULL) {
        return NULL;
    }
    node = heapAlloc(sizeof(MapVisNode));
    node->entries = NULL;
    node->sprites = NULL;
    node->visMode = 3;
    node->child0 = mapTreeCloneShape(bsp->child0);
    node->child1 = mapTreeCloneShape(bsp->child1);
    return node;
}


extern MapVisNode *D_807F5E60;


void func_8062BAE4(void) {
    modelPendingCountsReset();
    func_8062BB2C(D_807F5DE4, D_807F5E60, 1);
    modelPendingEntriesProcess();
    csFreeTrackedModels();
}


void func_8062BB2C(MapBspNode *node, MapVisNode *vis, u8 allowDefault) {
    RenderEntry *entry;
    RenderEntry *next;

    if (node == NULL) {
        return;
    }
    if (vis->visMode == 3) {
        func_8062BB2C(node->child0, vis->child0, 0);
        func_8062BB2C(node->child1, vis->child1, 0);
        return;
    }
    switch (node->kind) {
        case 2:
            mapChunkUpdateModelNodes();
            break;
        case 1:
            entry = vis->entries;
            while (entry != NULL) {
                next = entry->unk14;
                modelPendingQueueInsert(entry, allowDefault);
                entry = next;
            }
            break;
        case 0:
            switch (vis->visMode) {
                case 1:
                case 2:
                    if (vis->camSide != 0) {
                        func_8062BB2C(node->child1, vis->child1, allowDefault);
                        func_8062BB2C(node->child0, vis->child0, 0);
                    } else {
                        func_8062BB2C(node->child0, vis->child0, allowDefault);
                        func_8062BB2C(node->child1, vis->child1, 0);
                    }
                    break;
                case 0:
                    if (vis->camSide != 0) {
                        func_8062BB2C(node->child0, vis->child0, allowDefault);
                        func_8062BB2C(node->child1, vis->child1, allowDefault);
                    } else {
                        func_8062BB2C(node->child1, vis->child1, allowDefault);
                        func_8062BB2C(node->child0, vis->child0, allowDefault);
                    }
                    break;
            }
            break;
    }
}

extern struct RenderEntry *D_807F5FF4;


u8 func_8062BCC8(Actor *actor, f32 x, f32 z, f32 y, f32 *outFloorY) {
    u8 result;
    RenderEntry *item;

    result = func_8062BDB0(actor, D_807F5DE4, D_807F5E60, x, z, y, outFloorY);
    item = D_807F5FF4;
    while (item != NULL) {
        if (item->unk24 == 1) {
            result |= collisionTestDynamicActorFloor(actor, item->unk1E, x, z, y, outFloorY);
        }
        item = item->unk14;
    }
    return result;
}


u8 func_8062BDB0(Actor *actor, MapBspNode *node, MapVisNode *vis, f32 x, f32 z, f32 y, f32 *outFloorY) {
    u8 result;
    u8 other;
    RenderEntry *item;

    result = 0;
    switch (node->kind) {
        case 2:
            return mapChunkCheckActorCollision(actor, x, z, y, outFloorY);
        case 1:
            item = vis->entries;
            while (item != NULL) {
                if (item->unk24 == 1) {
                    result |= collisionTestDynamicActorFloor(actor, item->unk1E, x, z, y, outFloorY);
                }
                item = item->unk14;
            }
            return result;
        case 0:
            result = func_8062BDB0(actor, node->child0, vis->child0, x, z, y, outFloorY);
            other = func_8062BDB0(actor, node->child1, vis->child1, x, z, y, outFloorY);
            return result | other;
    }
    return 0;
}

extern Gfx D_1000118;
extern u8 gViewportCount;
extern u8 D_807F5FEC;
extern u8 D_807F5FED;
extern u8 gCurrentPlayerIndex;
extern PlayerStruct *gPlayerSlots;


Gfx *playerViewsRender(Gfx *gfx, void *frame) {
    s32 i;
    u8 alpha;
    G00Entry *vp;

    mapFrameBegin(frame);
    gDPPipeSync(gfx++);
    if (D_807F5FED != 0) {
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, G_MDSFT_PIPELINE, 1, G_PM_1PRIMITIVE);
    } else {
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, G_MDSFT_PIPELINE, 1, G_PM_NPRIMITIVE);
    }
    for (i = 0; i < gViewportCount; i++) {
        if (gPlayerSlots[i].unk0 != 0) {
            gCurrentPlayerIndex = i;
            gfx = mapRenderPlayerView(gfx, gPlayerSlots[i].unk21C, gPlayerSlots[i].unk220, gPlayerSlots[i].unk224,
                                gPlayerSlots[i].unk234, gPlayerSlots[i].unk238, gPlayerSlots[i].unk23C,
                                gPlayerSlots[i].prevFov, gPlayerSlots[i].unk280 * cameraStepAspectScale(),
                                gPlayerSlots[i].farClip);
            D_807F5FEC = 0;
        }
        if (gPlayerSlots[i].unk0 == 0 || gPlayerSlots[i].unk2EA != 0) {
            alpha = gPlayerSlots[i].actor->alpha;
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



void mapFrameBegin(void *frame) {
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


extern s32 D_807F5E64;
extern f32 D_807F5FB4;
extern f32 D_807F5FB0;
extern f32 D_807F5FAC;
extern f32 D_807F5FA8;
extern f32 D_807F5FE0;
extern f32 D_807F5FDC;
extern PlanePoly gFrustumPlanes[];
extern struct RenderEntry *D_807F5FF0;
extern s32 gGlobalPauseFlags;
extern Mtx D_2000180;

f32 cosApprox(f32);

Gfx *mapRenderPlayerView(Gfx *gfx, f32 eyeX, f32 eyeY, f32 eyeZ, f32 atX, f32 atY, f32 atZ, f32 fov, f32 aspect, f32 farClip) {
    Gfx *dl;
    s32 pad[25];

    dl = gPlayerSlots[gCurrentPlayerIndex].hiliteDl[gGfxBufferIndex];
    D_807F5E64 = 0;
    D_807F5FB4 = fov;
    D_807F5FB0 = aspect;
    D_807F5FAC = farClip;
    D_807F5FA8 = D_807F5FAC;
    D_807F5FE0 = cosApprox(fov * 0.01745329238f);
    D_807F5FE0 = (D_807F5FE0 - D_807F5FDC) * 3.0 + D_807F5FDC;
    planeFromTwoPoints(eyeX, eyeY, eyeZ, atX, atY, atZ);
    frustumCalculateCornerRays(D_807F5FB4, D_807F5FB0, D_807F5FA8);
    frustumCornersTransformByInverse(&gPlayerSlots[gCurrentPlayerIndex].viewMtx[gGfxBufferIndex]);
    frustumOrientPolyNormals(eyeX, eyeY, eyeZ, gFrustumPlanes, D_807F5E20);
    mapTreeFrameUpdate(D_807F5DE4, D_807F5E60, D_807F5FF0, eyeX, eyeY, eyeZ, 0, !D_807F5FEC, gViewportCount >= 2);
    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
    gfx = actorBuildLightDisplayList(gfx, gPlayerSlots[gCurrentPlayerIndex].actor, gCurrentPlayerIndex);
    gSPSegment(gfx++, 5, osVirtualToPhysical(dl));
    gDPSetHilite1Tile(dl++, 0, &gPlayerSlots[gCurrentPlayerIndex].hilite[gGfxBufferIndex], 32, 32);
    gSPEndDisplayList(dl++);
    viewportSetFromRect(gPlayerSlots[gCurrentPlayerIndex].viewport[gGfxBufferIndex].vp.vscale, gPlayerSlots[gCurrentPlayerIndex].rect[0], gPlayerSlots[gCurrentPlayerIndex].rect[1], gPlayerSlots[gCurrentPlayerIndex].rect[2], gPlayerSlots[gCurrentPlayerIndex].rect[3]);
    gSPPerspNormalize(gfx++, gPlayerSlots[gCurrentPlayerIndex].perspNorm);
    gSPViewport(gfx++, osVirtualToPhysical(&gPlayerSlots[gCurrentPlayerIndex].viewport[gGfxBufferIndex]));
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, gPlayerSlots[gCurrentPlayerIndex].rect[0], gPlayerSlots[gCurrentPlayerIndex].rect[1], gPlayerSlots[gCurrentPlayerIndex].rect[2], gPlayerSlots[gCurrentPlayerIndex].rect[3]);
    gSPLookAtX(gfx++, osVirtualToPhysical(&gPlayerSlots[gCurrentPlayerIndex].lookAt[gGfxBufferIndex]));
    gSPLookAtY(gfx++, osVirtualToPhysical(&gPlayerSlots[gCurrentPlayerIndex].lookAt[gGfxBufferIndex]) + 0x10);
    mapSetClipBounds(gPlayerSlots[gCurrentPlayerIndex].rect[0], gPlayerSlots[gCurrentPlayerIndex].rect[1], gPlayerSlots[gCurrentPlayerIndex].rect[2], gPlayerSlots[gCurrentPlayerIndex].rect[3]);
    gfx = gfxDrawPlayerViewBackground(fogApply(gfx), gCurrentPlayerIndex);
    gSPMatrix(gfx++, osVirtualToPhysical(&gPlayerSlots[gCurrentPlayerIndex].projMtx[gGfxBufferIndex]), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gfx++, osVirtualToPhysical(&gPlayerSlots[gCurrentPlayerIndex].viewMtx[gGfxBufferIndex]), G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(gfx++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gfx = mapTreeRender(gfx, D_807F5DE4, D_807F5E60, eyeX, eyeY, eyeZ, gGlobalPauseFlags);
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

extern RenderEntry *D_807F5FF8;
extern u8 D_807F6009;


Gfx *func_8062CA0C(Gfx *gfx, f32 camX, f32 camY, f32 camZ) {
    D_807F6009 = 0xFF;
    return renderEntryListBuildDisplayList(gfx, D_807F5FF8, camX, camY, camZ, 0x30030, -1, 0);
}

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

extern RenderEntry *D_807F5FFC;

#define MAP_LEAF(o) ((MapLeafLists *)(o))

Gfx *mapTreeRender(Gfx *gfx, MapBspNode *node, MapVisNode *vis, f32 camX, f32 camY, f32 camZ, s32 renderMask) {
    Gfx *pad;

    if (node == NULL) {
        return gfx;
    }
    if (vis->visMode == 3) {
        return gfx;
    }
    switch (node->kind) {
        case 2:
            gfx = mapChunksRender(gfx, node, camX, camY, camZ, renderMask);
            break;
        case 1:
            D_807F5E64 += MAP_LEAF(node)->unk6E;
            if (renderMask & 0x10) {
                gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
                gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                gfx = mapViewDrawPass(gfx, (struct MapViewEntries *)node, 1);
                gfx = fogRender(gfx);
                gfx = mapChunkEmitSegmentCommands(gfx, 0xFF);
                if (MAP_LEAF(node)->unk8 != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)MAP_LEAF(node)->unk8));
                }
                if (MAP_LEAF(node)->unkC != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)MAP_LEAF(node)->unkC));
                }
                if (MAP_LEAF(node)->unk14 != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)MAP_LEAF(node)->unk14));
                }
                if (MAP_LEAF(node)->unk10 != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)MAP_LEAF(node)->unk10));
                }
                if (MAP_LEAF(node)->unk18 != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)MAP_LEAF(node)->unk18));
                }
                gfx = mapViewDrawPass(gfx, (struct MapViewEntries *)node, 2);
            }
            gfx = spriteListRender(gfx, vis->sprites);
            gfx = billboardRenderQueued(gfx, -1);
            D_807F6009 = 0xFF;
            gfx = renderEntryListBuildDisplayList(gfx, vis->entries, camX, camY, camZ, renderMask, -1, 0);
            if (renderMask & 0x10) {
                gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
                gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                gfx = mapViewDrawPass(gfx, (struct MapViewEntries *)node, 3);
                gDPPipeSync(gfx++);
            }
            gfx = renderEntryListBuildDisplayList(gfx, D_807F5FFC, camX, camY, camZ, renderMask, -1, 0);
            break;
        case 0:
            switch (vis->visMode) {
                case 1:
                case 2:
                    if (vis->camSide != 0) {
                        return mapTreeRender(gfx, node->child1, vis->child1, camX, camY, camZ, renderMask);
                    } else {
                        return mapTreeRender(gfx, node->child0, vis->child0, camX, camY, camZ, renderMask);
                    }
                case 0:
                    if (vis->camSide != 0) {
                        gfx = mapTreeRender(gfx, node->child0, vis->child0, camX, camY, camZ, renderMask);
                        return mapTreeRender(gfx, node->child1, vis->child1, camX, camY, camZ, renderMask);
                    } else {
                        gfx = mapTreeRender(gfx, node->child1, vis->child1, camX, camY, camZ, renderMask);
                        return mapTreeRender(gfx, node->child0, vis->child0, camX, camY, camZ, renderMask);
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



Gfx *mapViewDrawPass(Gfx *gfx, MapViewEntries *arg1, u8 arg2) {
    s32 i;
    u8 idx;

    for (i = 0; i < arg1->unkC5; i++) {
        if (arg2 == arg1->unkB9[i] && (arg1->unk88[i] == -1 || mapChunkIsActive(arg1->unk88[i]) != 0)) {
            gfx = mapSurfaceEffectDraw(gfx, arg1->unk70[i]);
            gSPClearGeometryMode(gfx++, G_CULL_BACK);
            idx = arg1->unkAC[i];
            if (D_807F5FB8[idx].unk80 != 0.0 && D_807F5FB8[idx].unk8C != 0) {
                gSPMatrix(gfx++, osVirtualToPhysical((u8 *)D_807F5FB8 + idx * 0x90 + (gGfxBufferIndex << 6)),
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


void func_8062D094(void *targetId, u8 forceInfiniteDist) {
    func_8062D0CC(D_807F5DE4, D_807F5E60, targetId, forceInfiniteDist);
}


u8 func_8062D0CC(MapBspNode *node, MapVisNode *vis, void *targetId, u8 forceInfiniteDist) {
    u8 pad;
    u8 found;

    found = 0;
    if (node == NULL) {
        return 0;
    }
    switch (node->kind) {
        case 2:
            mapChunkMarkRenderEntry(targetId, forceInfiniteDist);
            return 1;
        case 1:
            renderEntrySetDistanceOverride(vis->entries, targetId, 0, forceInfiniteDist, &found);
            return found;
        case 0:
            if (func_8062D0CC(node->child0, vis->child0, targetId, forceInfiniteDist) != 0) {
                return 1;
            }
            return func_8062D0CC(node->child1, vis->child1, targetId, forceInfiniteDist);
    }
}


void func_8062D1A8(void) {
    if (func_807142D8() == 0) {
        mapTreeResolveNodeAssets(D_807F5DE4, D_807F5E60);
    }
}


void mapTreeResolveNodeAssets(MapBspNode *node, MapVisNode *vis) {
    for (;;) {
        if (node == NULL) {
            return;
        }
        switch (node->kind) {
            case 2:
                mapChunkResolveNodeAssets();
                return;
            case 1:
                modelNodeListSyncFlags(vis->entries);
                return;
            case 0:
                mapTreeResolveNodeAssets(node->child0, vis->child0);
                node = node->child1;
                vis = vis->child1;
                break;
            default:
                return;
        }
    }
}


void func_8062D26C(void *targetId) {
    u8 removed;
    s16 chunk;

    renderEntryRemove(NULL, targetId, 1, &removed);
    mapPurgeNodeList(targetId, &chunk, 1);
}


s32 mapPurgeNodeList(void *targetId, s16 *outChunk, u8 all) {
    return mapTreePurgeNodeList(D_807F5DE4, D_807F5E60, targetId, outChunk, all);
}


u8 mapTreePurgeNodeList(MapBspNode *node, MapVisNode *vis, void *targetId, s16 *outChunk, u8 all) {
    u8 removed;

    if (node == NULL) {
        return 0;
    }
    switch (node->kind) {
        case 2:
            return mapChunkPurgeNodeList(targetId, outChunk, all);
        case 1:
            vis->entries = renderEntryRemove(vis->entries, targetId, 0, &removed);
            return removed;
        case 0:
            if (mapTreePurgeNodeList(node->child0, vis->child0, targetId, outChunk, all) != 0 && all == 0) {
                return 1;
            }
            return mapTreePurgeNodeList(node->child1, vis->child1, targetId, outChunk, all);
    }
    return 0;
}


void mapDistributeEntries(RenderEntry *entries) {
    mapTreeDistributeEntries(D_807F5DE4, D_807F5E60, entries);
}


void mapTreeDistributeEntries(MapBspNode *node, MapVisNode *vis, RenderEntry *entries) {
    s32 pad;
    RenderEntry *listA;
    RenderEntry *listB;
    u8 pad2;
    u8 side;

    listA = NULL;
    listB = NULL;
    if (node == NULL) {
        return;
    }
    switch (node->kind) {
        case 2:
            while (entries != NULL) {
                mapChunkUpdateEntryNode(entries);
                entries = entries->unk14;
            }
            break;
        case 1:
            while (entries != NULL) {
                vis->entries = renderEntryAddOrUpdate(vis->entries, entries->unk24, entries->unk0, entries->unk4, entries->unk8, entries->unkC, entries->unk1C, entries->unk1E, entries->unk22, entries->unk20, 0);
                entries = entries->unk14;
            }
            break;
        case 0:
            while (entries != NULL) {
                if (mapBspPlaneSideTest(node, &side, entries->unk4, entries->unk8, entries->unkC) != 0) {
                    listB = renderEntryAddOrUpdate(listB, entries->unk24, entries->unk0, entries->unk4, entries->unk8, entries->unkC, entries->unk1C, entries->unk1E, entries->unk22, entries->unk20, 0);
                } else {
                    listA = renderEntryAddOrUpdate(listA, entries->unk24, entries->unk0, entries->unk4, entries->unk8, entries->unkC, entries->unk1C, entries->unk1E, entries->unk22, entries->unk20, 0);
                }
                entries = entries->unk14;
            }
            mapTreeDistributeEntries(node->child0, vis->child0, listA);
            mapTreeDistributeEntries(node->child1, vis->child1, listB);
            renderEntryListFree(listA);
            renderEntryListFree(listB);
            break;
    }
}



void mapTreeFrameUpdate(MapBspNode *node, MapVisNode *vis, RenderEntry *entries, f32 camX, f32 camY, f32 camZ, u8 noCull, u8 keepLists, u8 all) {
    RenderEntry *listA;
    RenderEntry *listB;
    s32 kind;
    RenderEntry *closest;
    u8 pad2;
    u8 side;

    listA = NULL;
    listB = NULL;
    if (node == NULL) {
        return;
    }
    if (noCull == 0 && mapNodeBoxInFrustum(node, camX, camY, camZ) == 0) {
        vis->visMode = 3;
        return;
    }
    kind = node->kind;
    if (kind != 0) {
        if (kind != 1) {
            if (kind == 2) {
                vis->visMode = 0;
                mapChunkFrameUpdate(camX, camY, camZ);
                if (keepLists == 0) {
                    mapChunkClearNodeFlags(all);
                    if (entries != NULL) {
                        do {
                            mapChunkUpdateEntryNode(entries);
                            entries = entries->unk14;
                        } while (entries != NULL);
                    }
                    mapChunkFreeNodeLists(all);
                    mapChunkRebuildNodeLists(camX, camY, camZ, all);
                    mapChunkBuildSpriteChains(camX, camY, camZ, all);
                    D_807F5FFC = renderEntryListSortByDistance(D_807F5FFC, camX, camY, camZ, &closest);
                }
            }
        } else {
            vis->visMode = 0;
            if (keepLists == 0) {
                renderEntryListClearTouched(vis->entries);
                if (entries != NULL) {
                    do {
                        vis->entries = renderEntryAddOrUpdate(vis->entries, entries->unk24, entries->unk0, entries->unk4, entries->unk8, entries->unkC, entries->unk1C, entries->unk1E, entries->unk22, entries->unk20, 0);
                        entries = entries->unk14;
                    } while (entries != NULL);
                }
                vis->entries = renderEntryListPurgeUntouched(vis->entries);
                vis->entries = renderEntryListSortByDistance(vis->entries, camX, camY, camZ, &closest);
                vis->sprites = spriteListBuildDisplayChain(vis->entries, 0, camX, camY, camZ);
                D_807F5FFC = renderEntryListSortByDistance(D_807F5FFC, camX, camY, camZ, &closest);
            }
        }
    } else {
        if (entries != NULL) {
            do {
                if (mapBspPlaneSideTest(node, &side, entries->unk4, entries->unk8, entries->unkC) != 0) {
                    listB = renderEntryAddOrUpdate(listB, entries->unk24, entries->unk0, entries->unk4, entries->unk8, entries->unkC, entries->unk1C, entries->unk1E, entries->unk22, entries->unk20, 0);
                } else {
                    listA = renderEntryAddOrUpdate(listA, entries->unk24, entries->unk0, entries->unk4, entries->unk8, entries->unkC, entries->unk1C, entries->unk1E, entries->unk22, entries->unk20, 0);
                }
                entries = entries->unk14;
            } while (entries != NULL);
        }
        vis->camSide = mapBspPlaneSideTest(node, &vis->visMode, camX, camY, camZ);
        if (noCull) {
            mapTreeFrameUpdate(node->child0, vis->child0, listA, camX, camY, camZ, noCull, keepLists, all);
            mapTreeFrameUpdate(node->child1, vis->child1, listB, camX, camY, camZ, noCull, keepLists, all);
        } else {
            if (vis->visMode != 0) {
                if (vis->visMode == 1 || vis->visMode == 2) {
                    if (vis->camSide != 0) {
                        mapTreeFrameUpdate(node->child1, vis->child1, listB, camX, camY, camZ, noCull, keepLists, all);
                    } else {
                        mapTreeFrameUpdate(node->child0, vis->child0, listA, camX, camY, camZ, noCull, keepLists, all);
                    }
                }
            } else {
                mapTreeFrameUpdate(node->child0, vis->child0, listA, camX, camY, camZ, noCull, keepLists, all);
                mapTreeFrameUpdate(node->child1, vis->child1, listB, camX, camY, camZ, noCull, keepLists, all);
            }
        }
        renderEntryListFree(listA);
        renderEntryListFree(listB);
    }
}


s32 mapNodeBoxInFrustum(MapBspNode *node, f32 camX, f32 camY, f32 camZ) {
    return mapBspBoxInFrustum(node->unkA0, node->unkA2, node->unkA4, node->unkA6, node->unkA8, node->unkAA, camX, camY, camZ, D_807F5FA8, gFrustumPlanes);
}

extern f32 D_807F5E50[];

void planeFromTwoPoints(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    D_807F5E50[0] = arg3 - arg0;
    D_807F5E50[1] = arg4 - arg1;
    D_807F5E50[2] = arg5 - arg2;
    D_807F5E50[3] = -(((D_807F5E50[0] * arg0) + (D_807F5E50[1] * arg1)) + (D_807F5E50[2] * arg2));
}




s32 mapBspBoxInFrustum(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, PlanePoly *arg10) {
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
        d = ((arg10[i].a * arg0 + arg10[i].b * arg1) + arg10[i].c * arg2) + arg10[i].d;
        if (d < 0.00) {
            in1 = 1;
        }
        d = ((arg10[i].a * arg0 + arg10[i].b * arg4) + arg10[i].c * arg2) + arg10[i].d;
        if (d < 0.00) {
            if (arg4 && arg4) {} // FAKE: lowers arg4's cvt candidate priority (FP colouring of the head)
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
    f32 dy1Sq;
    f32 dist;
    f32 best;
    f32 pad;
    f32 dz0Sq;
    f32 dy0Sq;
    f32 dx0Sq;
    f32 dz1Sq;

    best = (f32)arg0;
    dx0Sq = (best - arg6) * (best - arg6);
    dy0Sq = (((f32)arg1 - arg7) * ((f32)arg1 - arg7));
    dz0Sq = (((f32)arg2 - arg8) * ((f32)arg2 - arg8));
    dy1Sq = (((f32)arg4 - arg7) * ((f32)arg4 - arg7));
    dz1Sq = (((f32)arg5 - arg8) * ((f32)arg5 - arg8));
    best = (dx0Sq + dy0Sq) + dz0Sq;
    dist = (dx0Sq + dy0Sq) + dz1Sq;
    if (dist < best) {
        best = dist;
    }
    if ((dx0Sq + dy1Sq) + dz0Sq < best) {
        best = (dx0Sq + dy1Sq) + dz0Sq;
    }
    if ((dx0Sq + dy1Sq) + dz1Sq < best) {
        best = (dx0Sq + dy1Sq) + dz1Sq;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + dy0Sq) + dz0Sq < best) {
        best = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + dy0Sq) + dz0Sq;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + dy0Sq) + dz1Sq < best) {
        best = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + dy0Sq) + dz1Sq;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + dy1Sq) + dz0Sq < best) {
        best = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + dy1Sq) + dz0Sq;
    }
    if (((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + dy1Sq) + dz1Sq < best) {
        best = ((((f32)arg3 - arg6) * ((f32)arg3 - arg6)) + dy1Sq) + dz1Sq;
    }
    return sqrtf(best);
}



s32 clipPolyToBox(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, PlanePoly *arg7) {
    s16 bufA[0x24];
    s16 bufB[0x24];
    s32 count;
    char pad;

    clipPolyAgainstAxis(arg7[arg0].v, bufA, arg7[arg0].type, &count, 0, arg1, 0);
    if (count == 0) {
        return 0;
    }
    clipPolyAgainstAxis(bufA, bufB, count, &count, 0, arg4, 1);
    if (count == 0) {
        return 0;
    }
    clipPolyAgainstAxis(bufB, bufA, count, &count, 1, arg2, 0);
    if (count == 0) {
        return 0;
    }
    clipPolyAgainstAxis(bufA, bufB, count, &count, 1, arg5, 1);
    if (count == 0) {
        return 0;
    }
    clipPolyAgainstAxis(bufB, bufA, count, &count, 2, arg3, 0);
    if (count == 0) {
        return 0;
    }
    clipPolyAgainstAxis(bufA, bufB, count, &count, 2, arg6, 1);
    if (count != 0) {
        return 1;
    }
    return 0;
}


void clipPolyAgainstAxis(s16 *arg0, s16 *arg1, s32 arg2, s32 *arg3, u8 arg4, f64 arg5, u8 arg6) {
    s32 i;
    s16 *prev;
    s16 hit[3];
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
                    clipEdgeIntersectAxis(prev, cur, arg4, arg5, hit);
                    clipVertexAppend(hit, arg3, arg1);
                    clipVertexAppend(cur, arg3, arg1);
                }
            } else if (clipVertexTestAxis(prev, arg4, arg5, arg6) != 0) {
                clipEdgeIntersectAxis(prev, cur, arg4, arg5, hit);
                clipVertexAppend(hit, arg3, arg1);
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



u8 mapBspPlaneSideTest(MapBspNode *node, u8 *outVisMode, f32 x, f32 y, f32 z) {
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
    *outVisMode = mapBspPlaneDistanceCheck(node, x, y, z);
    nz = node->unk54;
    ny = node->unk50;
    nx = node->unk4C;
    d = node->unk58;
    ea[0] = node->unk5C[2] - node->unk5C[0];
    ea[1] = node->unk62[2] - node->unk62[0];
    ea[2] = node->unk68[2] - node->unk68[0];
    eb[0] = node->unk5C[1] - node->unk5C[0];
    eb[1] = node->unk62[1] - node->unk62[0];
    eb[2] = node->unk68[1] - node->unk68[0];
    c[0] = ea[1] * eb[2] - ea[2] * eb[1];
    c[1] = ea[2] * eb[0] - ea[0] * eb[2];
    c[2] = ea[0] * eb[1] - ea[1] * eb[0];
    len = sqrtf(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    n[0] = c[0] / len;
    n[1] = c[1] / len;
    n[2] = c[2] / len;
    n[0] = n[0] * 20.000f;  // FAKE: separate (uncoloured) 20.0f literal web
    n[1] = n[1] * 20.0f;
    n[2] = n[2] * 20.00f;  // FAKE: separate (uncoloured) 20.0f literal web
    p[0] = node->unk5C[0] + n[0];
    p[1] = node->unk62[0] + n[1];
    p[2] = node->unk68[0] + n[2];
    s1 = nx * x + ny * y + nz * z + d;
    if (s1 > 0.0) {
        if (ny > 0.0f) {}  // FAKE: colours nx/ny/nz f14/f16/f18
        if (nx * p[0] + ny * p[1] + nz * p[2] + d > 0.0) {
            if (nx && nx) {}  // FAKE: nx coloured before nz
            return 0;
        }
    }
    if (s1 < 0.0) {
        if (nx * p[0] + ny * p[1] + nz * p[2] + d < 0.0) {
            return 0;
        }
    }
    return 1;
}

s32 mapBspPlaneDistanceCheck(MapBspNode *node, f32 x, f32 y, f32 z) {
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
    dot = node->unk4C * x + node->unk50 * y + node->unk54 * z + node->unk58;
    len = sqrtf(node->unk4C * node->unk4C + node->unk50 * node->unk50 + node->unk54 * node->unk54);
    if (dot && dot) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    dist = dot / len;
    absd = dist;
    if (dist < 0.0) {
        absd = 0.0 - dist;
    }
    if (absd > 300.0) {
        return 2;
    }
    nx = node->unk4C;
    ny = node->unk50;
    nz = node->unk54;
    do {
        dx = *(f32 *)((u8 *)D_807F5E20 + i * 12) - x; // FAKE: byte-offset corner address keeps base+offset addu order (Q0175)
        dy = *(f32 *)((u8 *)D_807F5E20 + i * 12 + 4) - y;
        dz = *(f32 *)((u8 *)D_807F5E20 + i * 12 + 8) - z;
        if (dx) {}  // FAKE: lowers dx priority (extra block in its range)
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


typedef struct MapChunkAnim {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ void *unk8;
    /* 0x0C */ s32 unkC[1];
    /* 0x10 */ u8 pad10[0x6C];
} MapChunkAnim; /* 0x7C */

extern u8 sMapChunkAnimCount;
extern MapChunkAnim *sMapChunkAnims;

Gfx *mapChunkEmitSegmentCommands(Gfx *gfx, u8 chunk) {
    s32 i;

    for (i = 0; i < sMapChunkAnimCount; i++) {
        if (chunk == sMapChunkAnims[i].unk1) {
            gSPSegment(gfx++, sMapChunkAnims[i].unk0, sMapChunkAnims[i].unk8);
        }
    }
    return gfx;
}



void mapChunkAnimateTextures(u8 arg0) {
    s32 i;
    s32 flag;

    for (i = 0; i < sMapChunkAnimCount; i++) {
        if (arg0 == sMapChunkAnims[i].unk1) {
            flag = 0;
            sMapChunkAnims[i].unk4++;
            if (sMapChunkAnims[i].unk4 == sMapChunkAnims[i].unk2) {
                sMapChunkAnims[i].unk4 = 0;
                sMapChunkAnims[i].unk5++;
                if (sMapChunkAnims[i].unk5 == sMapChunkAnims[i].unk3) {
                    sMapChunkAnims[i].unk5 = 0;
                }
                flag = 1;
            }
            if (sMapChunkAnims[i].unk8 == NULL) {
                flag = 1;
            }
            if (flag) {
                if (sMapChunkAnims[i].unk8 != NULL) {
                    assetFreeBuffer(sMapChunkAnims[i].unk8, 0x7E3, 5);
                }
                sMapChunkAnims[i].unk8 = assetLoad(7, sMapChunkAnims[i].unkC[sMapChunkAnims[i].unk5], 0, 0);
            }
        }
    }
}




void mapChunkFreeHiddenBuffers(void) {
    s32 i;

    for (i = 0; i < sMapChunkAnimCount; i++) {
        if (mapChunkIsVisible(sMapChunkAnims[i].unk1) == 0) {
            if (sMapChunkAnims[i].unk8 != NULL) {
                assetFreeBuffer(sMapChunkAnims[i].unk8, 0x7FB, 5);
                sMapChunkAnims[i].unk8 = NULL;
            }
        }
    }
}


extern f32 gGfxFarClip;
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
extern s32 *gMinecartTrackPoints;
extern s32 sMapSoundEmitterCount;
extern LevelSoundEmitter *sMapSoundEmitters;

struct MapRelocNode;

void mapHeaderLoad(MapFileHeader *header) {
    s32 off30;
    s32 off34;
    s32 off38;
    s32 off44;
    s32 off40;
    s32 off48;
    s32 pad[5];
    s32 effectSlotCount;

    D_807F5DE0 = (u8 *)header;
    effectSlotCount = 0;
    D_807F5FDC = cosApprox(0.7853981853f);
    fogSetParams(header->unk8 & 1);
    renderSetSegment6Override((header->unk8 >> 1) & 1);
    gGfxFarClip = header->unkA;
    D_807FB5E0 = header->unk14 << 3;
    D_807FB5E4 = header->unk16 << 3;
    D_807FB5E8 = header->unk10;
    D_807FB5EA = header->unk12;
    D_807F9450 = header->unk1C;
    D_807F9452 = header->unk1E;
    D_807F9454 = header->unk18;
    D_807F9456 = header->unk1A;
    D_807FD574 = header->unk20;
    D_807FD576 = header->unk22;
    D_807FD578 = header->unk24;
    D_807F5FE4 = header->unk26;
    D_807F5FE6 = header->unk28;
    D_807F5FE8 = header->unk2A;
    D_807F5FEA = header->unk2C;
    off40 = header->unk40;
    off30 = header->unk30;
    off34 = header->dlBase;
    off38 = header->unk38;
    off44 = header->unk44;
    off48 = header->unk48;
    D_807F5FD0 = *(s32 *)(D_807F5DE0 + off40) + 1;
    gMinecartTrackPoints = (s32 *)(D_807F5DE0 + off40 + 4);
    sMapSoundEmitterCount = *(s32 *)(D_807F5DE0 + off44);
    sMapSoundEmitters = (LevelSoundEmitter *)(D_807F5DE0 + off44 + 4);
    sMapChunkAnimCount = *(s32 *)(D_807F5DE0 + off48);
    sMapChunkAnims = (MapChunkAnim *)(D_807F5DE0 + off48 + 4);
    D_807F5DE4 = (MapBspNode *)(D_807F5DE0 + off30);
    D_807F5DE8 = (s32)(D_807F5DE0 + off38);
    D_807F5DEC = D_807F5DE0 + off34;
    lightSetTargetColor(1.0f, 1.0f, 1.0f, -1);
    lightCopyTargetColors(-1);
    matrixCacheInit(header->unkE << 10);
    mapTreeRelocate((struct MapRelocNode *)(s32)(D_807F5DE0 + off30), (s32)(D_807F5DE0 + off30), (s32)(D_807F5DE0 + off34)); // FAKE: (s32) hop on arg0 makes the shared sum land in a1 then copy to a0
    displayListResolveTextureImages((Gfx *)(D_807F5DE0 + off34), (Gfx *)(D_807F5DE0 + off38));
    mapRelocateOffsetTable((s32)(D_807F5DE0 + off40));
    mapSurfaceEffectsReset();
    mapNodeTreeInitSurfaceEffects((MapNodeEffects *)D_807F5DE4, &effectSlotCount);
    mapOffsetSlotsInit(effectSlotCount);
    D_807F5E60 = mapTreeCloneShape(D_807F5DE4);
    mapChunksInitFromMapData(header);
    collisionInitStaticCache(header);
    collisionBuildCellTable(header);
    effectWaterInitNodes(header);
    actorTargetTableLoad(header);
    triggerZoneInit(header);
    func_8062F318();
}


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
                t = gMinecartTrackPoints[i];
                gMinecartTrackPoints[i] = t + arg0;
                i++;
            } while (D_807F5FD0 >= i);
        }
    }
}


s32 mapGetSoundEmitters(LevelSoundEmitter **outEmitters) {
    *outEmitters = sMapSoundEmitters;
    return sMapSoundEmitterCount;
}

void displayListResolveTextureImages(Gfx *cmd, Gfx *end) {
    u32 w;

    for (; cmd != end; cmd++) {
        w = cmd->words.w0;
        if ((w >> 24) == (0, 0xFD)) { // FAKE: comma-wrapped G_SETTIMG constant orders the compare (bnel t6,s2); the empty statement below colours end before the constant ($s1/$s2) (Q0434)
            if (((cmd->words.w1 << 4) >> 28) == 0) {
                cmd->words.w1 = (u32)assetLoad(0x19, cmd->words.w1, 1, 0); // the command word now holds the loaded address
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


