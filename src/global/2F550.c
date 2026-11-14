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
f32 sFrustumCornerRays[12];


void frustumCalculateCornerRays(f32 fovY, f32 aspect, f32 depth) {
    f32 scale;
    f32 halfYaw;
    f32 pitchMtx[4][4];
    f32 yawMtx[4][4];
    f32 dirZ;
    f32 dirY;
    f32 dirX;
    f32 halfPitch;
    s32 i;

    halfPitch = fovY * 0.5;
    halfYaw = halfPitch * aspect;
    guRotateF(pitchMtx, halfPitch, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(pitchMtx, 0.0f, 0.0f, (-depth), &dirX, &dirY, &dirZ);
    guRotateF(yawMtx, halfYaw, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(yawMtx, dirX, dirY, dirZ, &sFrustumCornerRays[0], &sFrustumCornerRays[1], &sFrustumCornerRays[2]);
    guRotateF(yawMtx, -halfYaw, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(yawMtx, dirX, dirY, dirZ, &sFrustumCornerRays[3], &sFrustumCornerRays[4], &sFrustumCornerRays[5]);
    guRotateF(pitchMtx, -halfPitch, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(pitchMtx, 0.0f, 0.0f, (-depth), &dirX, &dirY, &dirZ);
    guRotateF(yawMtx, halfYaw, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(yawMtx, dirX, dirY, dirZ, &sFrustumCornerRays[6], &sFrustumCornerRays[7], &sFrustumCornerRays[8]);
    guRotateF(yawMtx, -halfYaw, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(yawMtx, dirX, dirY, dirZ, &sFrustumCornerRays[9], &sFrustumCornerRays[10], &sFrustumCornerRays[11]);
    for (i = 0; i < 4; i++) {
        scale = (-depth) / sFrustumCornerRays[i * 3 + 2];
        sFrustumCornerRays[i * 3] *= scale;
        sFrustumCornerRays[i * 3 + 1] *= scale;
        sFrustumCornerRays[i * 3 + 2] = (-depth);
    }
}

extern f32 D_807F5E20[];
extern f32 D_807F5E24[];
extern f32 D_807F5E28[];


void frustumCornersTransformByInverse(Mtx *mtx) {
    f32 viewMtx[4][4];
    f32 invMtx[4][4];
    s32 i;

    guMtxL2F(viewMtx, mtx);
    matrix4Invert(invMtx, viewMtx);
    for (i = 0; i < 4; i++) {
        guMtxXFMF(invMtx, sFrustumCornerRays[i * 3], sFrustumCornerRays[i * 3 + 1], sFrustumCornerRays[i * 3 + 2], &D_807F5E20[i * 3], &D_807F5E24[i * 3], &D_807F5E28[i * 3]);
    }
}



void frustumOrientPolyNormals(f32 eyeX, f32 eyeY, f32 eyeZ, PlanePoly *planes, f32 *corners) {
    s32 i;
    f32 xs[5];
    f32 ys[5];
    f32 zs[5];
    PlanePoly *poly;
    poly = planes;
    for (i = 0; i < 4; i++) {
        poly++;
        poly[-1].v[0][0] = eyeX;
        poly[-1].v[0][1] = eyeY;
        poly[-1].v[0][2] = eyeZ;
        poly[-1].type = 3;
    }
    planes[0].v[1][0] = corners[0];
    planes[0].v[1][1] = corners[1];
    planes[0].v[1][2] = corners[2];
    planes[0].v[2][0] = corners[3];
    planes[0].v[2][1] = corners[4];
    planes[0].v[2][2] = corners[5];
    xs[0] = corners[6];
    ys[0] = corners[7];
    zs[0] = corners[8];
    planes[1].v[1][0] = corners[6];
    planes[1].v[1][1] = corners[7];
    planes[1].v[1][2] = corners[8];
    planes[1].v[2][0] = corners[0];
    planes[1].v[2][1] = corners[1];
    planes[1].v[2][2] = corners[2];
    xs[1] = corners[9];
    ys[1] = corners[10];
    zs[1] = corners[11];
    planes[2].v[1][0] = corners[9];
    planes[2].v[1][1] = corners[10];
    planes[2].v[1][2] = corners[11];
    planes[2].v[2][0] = corners[6];
    planes[2].v[2][1] = corners[7];
    planes[2].v[2][2] = corners[8];
    xs[2] = corners[0];
    ys[2] = corners[1];
    zs[2] = corners[2];
    planes[3].v[1][0] = corners[3];
    planes[3].v[1][1] = corners[4];
    planes[3].v[1][2] = corners[5];
    planes[3].v[2][0] = corners[9];
    planes[3].v[2][1] = corners[10];
    planes[3].v[2][2] = corners[11];
    xs[3] = corners[0];
    ys[3] = corners[1];
    zs[3] = corners[2];
    planes[4].type = 4;
    planes[4].v[0][0] = corners[6];
    planes[4].v[0][1] = corners[7];
    planes[4].v[0][2] = corners[8];
    planes[4].v[1][0] = corners[9];
    planes[4].v[1][1] = corners[10];
    planes[4].v[1][2] = corners[11];
    planes[4].v[2][0] = corners[0];
    planes[4].v[2][1] = corners[1];
    planes[4].v[2][2] = corners[2];
    planes[4].v[3][0] = corners[3];
    planes[4].v[3][1] = corners[4];
    planes[4].v[3][2] = corners[5];
    zs[4] = eyeZ;
    ys[4] = eyeY;
    xs[4] = eyeX;
    poly = planes;
    for (i = 0; i < 5; poly++, i++) {
        planePolyCalcEquation(poly);
        if (poly->d + (poly->a * xs[i] + poly->b * ys[i] + poly->c * zs[i]) < (0, 0.0)) {}  // FAKE: second use of the sum makes it a coloured candidate (f0) and keeps its tree order for LFTR
        if (poly->d + (poly->a * xs[i] + poly->b * ys[i] + poly->c * zs[i]) < 0.0) {
            polyFlipWinding(poly);
            planePolyCalcEquation(poly);
        }
    }
}

void polyFlipWinding(PlanePoly *poly) {
    s16 x;
    s16 y;
    s16 z;

    switch (poly->type) {
        case 3:
            x = poly->v[0][0];
            y = poly->v[0][1];
            z = poly->v[0][2];
            poly->v[0][0] = poly->v[1][0];
            poly->v[0][1] = poly->v[1][1];
            poly->v[0][2] = poly->v[1][2];
            poly->v[1][0] = x;
            poly->v[1][1] = y;
            poly->v[1][2] = z;
            break;
        case 4:
            x = poly->v[0][0];
            y = poly->v[0][1];
            z = poly->v[0][2];
            poly->v[0][0] = poly->v[2][0];
            poly->v[0][1] = poly->v[2][1];
            poly->v[0][2] = poly->v[2][2];
            poly->v[2][0] = x;
            poly->v[2][1] = y;
            poly->v[2][2] = z;
            break;
    }
}

void planePolyCalcEquation(PlanePoly *poly) {
    poly->a = (poly->v[0][1] * (f64)(poly->v[1][2] - poly->v[2][2]) + poly->v[1][1] * (f64)(poly->v[2][2] - poly->v[0][2]))
            + poly->v[2][1] * (f64)(poly->v[0][2] - poly->v[1][2]);
    poly->b = (poly->v[0][2] * (f64)(poly->v[1][0] - poly->v[2][0]) + poly->v[1][2] * (f64)(poly->v[2][0] - poly->v[0][0]))
            + poly->v[2][2] * (f64)(poly->v[0][0] - poly->v[1][0]);

    poly->c = (poly->v[0][0] * (f64)(poly->v[1][1] - poly->v[2][1]) + poly->v[1][0] * (f64)(poly->v[2][1] - poly->v[0][1]))
            + poly->v[2][0] * (f64)(poly->v[0][1] - poly->v[1][1]);
    poly->d = -((poly->v[0][0] * ((f64)poly->v[1][1] * poly->v[2][2] - (f64)poly->v[2][1] * poly->v[1][2]) + poly->v[1][0] * ((f64)poly->v[2][1] * poly->v[0][2] - (f64)poly->v[0][1] * poly->v[2][2])) + poly->v[2][0] * ((f64)poly->v[0][1] * poly->v[1][2] - poly->v[1][1] * (f64)poly->v[0][2]));
}



void mapNodeTreeInitSurfaceEffects(MapBspNode *node, s32 *slotCount) {
    s32 i;
    s32 count;

    for (;;) {
        if (node == NULL) {
            break;
        }
        for (i = 0; i < node->unkC5; i++) {
            mapSurfaceEffectInit(node->unk70[i]);
            count = node->unkAC[i] + 1;
            if (*slotCount < count) {
                *slotCount = count;
            }
        }
        mapNodeTreeInitSurfaceEffects(node->child0, slotCount);
        node = node->child1;
    }
}

typedef struct MapOffsetSlot {
    /* 0x00 */ Mtx mtx[2];
    /* 0x80 */ f32 value;
    /* 0x84 */ f32 target;
    /* 0x88 */ f32 speed;
    /* 0x8C */ u8 enabled;
    /* 0x8D */ u8 pad8D[3];
} MapOffsetSlot; /* 0x90 */

extern MapOffsetSlot *sMapOffsetSlots;
extern s32 sMapOffsetSlotCount;
extern u8 sMapOffsetSlotsMoving;

void mapOffsetSlotsInit(s32 count) {
    s32 i;

    if (count == 0) {
        sMapOffsetSlots = NULL;
        sMapOffsetSlotCount = 0;
        return;
    }
    sMapOffsetSlots = heapAlloc(count * 0x90);
    sMapOffsetSlotCount = count;
    for (i = 0; i < count; i++) {
        sMapOffsetSlots[i].value = 0.0f;
        sMapOffsetSlots[i].target = 0.0f;
        sMapOffsetSlots[i].speed = 0.0f;
        sMapOffsetSlots[i].enabled = 1;
    }
    sMapOffsetSlotsMoving = 0;
}

void mapOffsetSlotSetEnabled(s16 slot, u8 enabled) {
    sMapOffsetSlots[slot].enabled = enabled;
}

extern s32 gMapChunkCount;

void mapOffsetSlotsUpdate(void) {
    s32 i;

    sMapOffsetSlotsMoving = 0;
    for (i = 0; i < sMapOffsetSlotCount; i++) {
        if (sMapOffsetSlots[i].value != 0.0) {
            guTranslate(&sMapOffsetSlots[i].mtx[gGfxBufferIndex], 0.0f, gMapChunkCount != 0 ? sMapOffsetSlots[i].value * 3.0f : sMapOffsetSlots[i].value, 0.0f);
        }
        if (sMapOffsetSlots[i].value != sMapOffsetSlots[i].target) {
            sMapOffsetSlotsMoving = 1;
            if (sMapOffsetSlots[i].value < sMapOffsetSlots[i].target) {
                sMapOffsetSlots[i].value += sMapOffsetSlots[i].speed;
                if (sMapOffsetSlots[i].target < sMapOffsetSlots[i].value) {
                    sMapOffsetSlots[i].value = sMapOffsetSlots[i].target;
                }
            } else {
                sMapOffsetSlots[i].value -= sMapOffsetSlots[i].speed;
                if (sMapOffsetSlots[i].value < sMapOffsetSlots[i].target) {
                    sMapOffsetSlots[i].value = sMapOffsetSlots[i].target;
                }
            }
        }
    }
}

f32 mapOffsetSlotGetValue(s8 slot) {
    return sMapOffsetSlots[slot].value;
}

void mapOffsetSlotSetTarget(s32 slot, f32 target, f32 speed) {
    sMapOffsetSlots[slot].target = target;
    sMapOffsetSlots[slot].speed = speed;
}

void mapOffsetSlotAddTarget(s32 slot, f32 delta, f32 speed) {
    sMapOffsetSlots[slot].target += delta;
    sMapOffsetSlots[slot].speed = speed;
}

void mapOffsetSlotsGetTargets(f32 *out) {
    s32 i;
    s32 n;

    n = sMapOffsetSlotCount;
    for (i = 0; i < n; i++) {
        out[i] = sMapOffsetSlots[i].target;
    }
}

void mapOffsetSlotsSetValues(f32 *values) {
    s32 i;

    for (i = 0; i < sMapOffsetSlotCount; i++) {
        sMapOffsetSlots[i].target = values[i];
        sMapOffsetSlots[i].value = values[i];
    }
}



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
        if (gPlayerSlots[i].active != 0) {
            gCurrentPlayerIndex = i;
            gfx = mapRenderPlayerView(gfx, gPlayerSlots[i].eyeX, gPlayerSlots[i].eyeY, gPlayerSlots[i].eyeZ,
                                gPlayerSlots[i].unk234, gPlayerSlots[i].unk238, gPlayerSlots[i].unk23C,
                                gPlayerSlots[i].prevFov, gPlayerSlots[i].unk280 * cameraStepAspectScale(),
                                gPlayerSlots[i].farClip);
            D_807F5FEC = 0;
        }
        if (gPlayerSlots[i].active == 0 || gPlayerSlots[i].unk2EA != 0) {
            alpha = gPlayerSlots[i].actor->alpha;
            vp = cameraFindViewportEntry(i);
            gSPDisplayList(gfx++, &D_1000118);
            gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, 0, G_OFF);
            gDPPipeSync(gfx++);
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0xFF - alpha);
            gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPFillRectangle(gfx++, vp->left, vp->top, vp->right, vp->bottom);
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
extern Mtx D_2000180;


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

void viewportSetFromRect(s16 *vp, s32 left, s32 top, s32 right, s32 bottom) {
    vp[0] = (right - left) * 2;
    vp[1] = (bottom - top) * 2;
    vp[2] = 0x1FF;
    vp[3] = 0;
    vp[4] = ((left + right) / 2) * 4;
    vp[5] = ((top + bottom) / 2) * 4;
    vp[6] = 0x1FF;
    vp[7] = 0;
}

extern RenderEntry *D_807F5FF8;
extern u8 D_807F6009;


Gfx *func_8062CA0C(Gfx *gfx, f32 camX, f32 camY, f32 camZ) {
    D_807F6009 = 0xFF;
    return renderEntryListBuildDisplayList(gfx, D_807F5FF8, camX, camY, camZ, 0x30030, -1, 0);
}


extern RenderEntry *D_807F5FFC;


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
            D_807F5E64 += node->unk6E;
            if (renderMask & 0x10) {
                gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
                gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                gfx = mapViewDrawPass(gfx, node, 1);
                gfx = fogRender(gfx);
                gfx = mapChunkEmitSegmentCommands(gfx, 0xFF);
                if (node->dl != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)node->dl));
                }
                if (node->unkC != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)node->unkC));
                }
                if (node->unk14 != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)node->unk14));
                }
                if (node->unk10 != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)node->unk10));
                }
                if (node->unk18 != -1) {
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)node->unk18));
                }
                gfx = mapViewDrawPass(gfx, node, 2);
            }
            gfx = spriteListRender(gfx, vis->sprites);
            gfx = billboardRenderQueued(gfx, -1);
            D_807F6009 = 0xFF;
            gfx = renderEntryListBuildDisplayList(gfx, vis->entries, camX, camY, camZ, renderMask, -1, 0);
            if (renderMask & 0x10) {
                gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
                gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                gfx = mapViewDrawPass(gfx, node, 3);
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




Gfx *mapViewDrawPass(Gfx *gfx, MapBspNode *view, u8 pass) {
    s32 i;
    u8 idx;

    for (i = 0; i < view->unkC5; i++) {
        if (pass == view->unkB9[i] && (view->unk88[i] == -1 || mapChunkIsActive(view->unk88[i]) != 0)) {
            gfx = mapSurfaceEffectDraw(gfx, view->unk70[i]);
            gSPClearGeometryMode(gfx++, G_CULL_BACK);
            idx = view->unkAC[i];
            if (sMapOffsetSlots[idx].value != 0.0 && sMapOffsetSlots[idx].enabled != 0) {
                gSPMatrix(gfx++, osVirtualToPhysical(&sMapOffsetSlots[idx].mtx[gGfxBufferIndex]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
                gSPDisplayList(gfx++, osVirtualToPhysical(view->unk1C[i]));
                gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
            } else {
                gSPDisplayList(gfx++, osVirtualToPhysical(view->unk1C[i]));
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

extern f32 sViewPlane[];

void planeFromTwoPoints(f32 fromX, f32 fromY, f32 fromZ, f32 toX, f32 toY, f32 toZ) {
    sViewPlane[0] = toX - fromX;
    sViewPlane[1] = toY - fromY;
    sViewPlane[2] = toZ - fromZ;
    sViewPlane[3] = -(((sViewPlane[0] * fromX) + (sViewPlane[1] * fromY)) + (sViewPlane[2] * fromZ));
}




s32 mapBspBoxInFrustum(s16 minX, s16 minY, s16 minZ, s16 maxX, s16 maxY, s16 maxZ, f32 x, f32 y, f32 z, f32 range, PlanePoly *planes) {
    s32 in1;
    s32 in2;
    s32 behind;
    s32 i;
    f64 d;
    s32 pad0;

    if ((((f32)minX * sViewPlane[0] + (f32)minY * sViewPlane[1]) + (f32)minZ * sViewPlane[2]) + sViewPlane[3] < 0.0 &&
        (((f32)minX * sViewPlane[0] + (f32)minY * sViewPlane[1]) + maxZ * sViewPlane[2]) + sViewPlane[3] < 0.0 &&
        (((f32)minX * sViewPlane[0] + maxY * sViewPlane[1]) + (f32)minZ * sViewPlane[2]) + sViewPlane[3] < 0.0 &&
        (((f32)minX * sViewPlane[0] + maxY * sViewPlane[1]) + maxZ * sViewPlane[2]) + sViewPlane[3] < 0.0 &&
        ((maxX * sViewPlane[0] + (f32)minY * sViewPlane[1]) + (f32)minZ * sViewPlane[2]) + sViewPlane[3] < 0.0 &&
        ((maxX * sViewPlane[0] + (f32)minY * sViewPlane[1]) + maxZ * sViewPlane[2]) + sViewPlane[3] < 0.0 &&
        ((maxX * sViewPlane[0] + maxY * sViewPlane[1]) + (f32)minZ * sViewPlane[2]) + sViewPlane[3] < 0.0 &&
        ((maxX * sViewPlane[0] + maxY * sViewPlane[1]) + maxZ * sViewPlane[2]) + sViewPlane[3] < 0.0) {
        return 0;
    }
    if ((f32)minX <= x && x <= (f32)maxX && (f32)minY <= y && y <= (f32)maxY && (f32)minZ <= z && z <= (f32)maxZ) {
        return 1;
    }
    in1 = 0;
    in2 = 0;
    behind = 0;
    for (i = 0; i < 5 && behind == 0; i++) {
        d = ((planes[i].a * minX + planes[i].b * minY) + planes[i].c * minZ) + planes[i].d;
        if (d < 0.00) {
            in1 = 1;
        }
        d = ((planes[i].a * minX + planes[i].b * maxY) + planes[i].c * minZ) + planes[i].d;
        if (d < 0.00) {
            in2 = 1;
        }
        if (in1 != 0 && in2 != 0) {
            behind = 1;
        }
    }
    if (behind == 0 && boxMinCornerDistance(minX, minY, minZ, maxX, maxY, maxZ, x, y, z) < range) {
        return 1;
    }
    for (i = 0; i < 5; i++) {
        if (clipPolyToBox(i, minX, minY, minZ, maxX, maxY, maxZ, planes) != 0) {
            return 1;
        }
    }
    return 0;
}

f32 boxMinCornerDistance(s16 minX, s16 minY, s16 minZ, s16 maxX, s16 maxY, s16 maxZ, f32 x, f32 y, f32 z) {
    f32 dy1Sq;
    f32 dist;
    f32 best;
    f32 pad;
    f32 dz0Sq;
    f32 dy0Sq;
    f32 dx0Sq;
    f32 dz1Sq;

    best = (f32)minX;
    dx0Sq = (best - x) * (best - x);
    dy0Sq = (((f32)minY - y) * ((f32)minY - y));
    dz0Sq = (((f32)minZ - z) * ((f32)minZ - z));
    dy1Sq = (((f32)maxY - y) * ((f32)maxY - y));
    dz1Sq = (((f32)maxZ - z) * ((f32)maxZ - z));
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
    if (((((f32)maxX - x) * ((f32)maxX - x)) + dy0Sq) + dz0Sq < best) {
        best = ((((f32)maxX - x) * ((f32)maxX - x)) + dy0Sq) + dz0Sq;
    }
    if (((((f32)maxX - x) * ((f32)maxX - x)) + dy0Sq) + dz1Sq < best) {
        best = ((((f32)maxX - x) * ((f32)maxX - x)) + dy0Sq) + dz1Sq;
    }
    if (((((f32)maxX - x) * ((f32)maxX - x)) + dy1Sq) + dz0Sq < best) {
        best = ((((f32)maxX - x) * ((f32)maxX - x)) + dy1Sq) + dz0Sq;
    }
    if (((((f32)maxX - x) * ((f32)maxX - x)) + dy1Sq) + dz1Sq < best) {
        best = ((((f32)maxX - x) * ((f32)maxX - x)) + dy1Sq) + dz1Sq;
    }
    return sqrtf(best);
}



s32 clipPolyToBox(s32 planeIdx, s16 minX, s16 minY, s16 minZ, s16 maxX, s16 maxY, s16 maxZ, PlanePoly *planes) {
    s16 bufA[12][3];
    s16 bufB[12][3];
    s32 count;
    char pad;

    clipPolyAgainstAxis(planes[planeIdx].v, bufA, planes[planeIdx].type, &count, 0, minX, 0);
    if (count == 0) {
        return 0;
    }
    clipPolyAgainstAxis(bufA, bufB, count, &count, 0, maxX, 1);
    if (count == 0) {
        return 0;
    }
    clipPolyAgainstAxis(bufB, bufA, count, &count, 1, minY, 0);
    if (count == 0) {
        return 0;
    }
    clipPolyAgainstAxis(bufA, bufB, count, &count, 1, maxY, 1);
    if (count == 0) {
        return 0;
    }
    clipPolyAgainstAxis(bufB, bufA, count, &count, 2, minZ, 0);
    if (count == 0) {
        return 0;
    }
    clipPolyAgainstAxis(bufA, bufB, count, &count, 2, maxZ, 1);
    if (count != 0) {
        return 1;
    }
    return 0;
}


void clipPolyAgainstAxis(s16 (*src)[3], s16 (*dst)[3], s32 srcCount, s32 *dstCount, u8 axis, f64 bound, u8 isMax) {
    s32 i;
    s16 (*prev)[3];
    s16 hit[3];
    s16 (*cur)[3];
    s16 (*last)[3];

    *dstCount = 0;
    prev = &src[srcCount - 1];
    i = 0;
    if (srcCount > 0) {
        cur = src;
        do {
            last = cur;
            if (clipVertexTestAxis(*cur, axis, bound, isMax) != 0) {
                if (clipVertexTestAxis(*prev, axis, bound, isMax) != 0) {
                    clipVertexAppend(cur, dstCount, dst);
                } else {
                    clipEdgeIntersectAxis(*prev, *cur, axis, bound, hit);
                    clipVertexAppend(hit, dstCount, dst);
                    clipVertexAppend(cur, dstCount, dst);
                }
            } else if (clipVertexTestAxis(*prev, axis, bound, isMax) != 0) {
                clipEdgeIntersectAxis(*prev, *cur, axis, bound, hit);
                clipVertexAppend(hit, dstCount, dst);
            }
            i++;
            cur++;
            prev = last;
        } while (i != srcCount);
    }
}

s32 clipVertexTestAxis(s16 *vtx, u8 axis, f64 bound, u8 isMax) {
    f64 coord;

    switch (axis) {
        case 0:
            coord = vtx[0];
            break;
        case 1:
            coord = vtx[1];
            break;
        case 2:
            coord = vtx[2];
            break;
    }
    switch (isMax) {
        case 0:
            if (bound <= coord) {
                return 1;
            }
            break;
        case 1:
            if (coord <= bound) {
                return 1;
            }
            break;
    }
    return 0;
}


void clipVertexAppend(void *vtx, s32 *count, void *dst) {
    memcpy((u8 *)dst + *count * 6, vtx, 6);
    *count += 1;
    if (*count >= 0xD) {
        faultSetMessage(1, 0, 0, 0);
    }
}

void clipEdgeIntersectAxis(s16 *from, s16 *to, u8 axis, f64 bound, s16 *out) {
    f32 t;

    switch (axis) {
        case 0:
            t = (bound - from[0]) / (to[0] - from[0]);
            out[1] = (to[1] - from[1]) * t + from[1];
            out[2] = (to[2] - from[2]) * t + from[2];
            out[0] = bound;
            break;
        case 1:
            t = (bound - from[1]) / (to[1] - from[1]);
            out[0] = (to[0] - from[0]) * t + from[0];
            out[2] = (to[2] - from[2]) * t + from[2];
            out[1] = bound;
            break;
        case 2:
            t = (bound - from[2]) / (to[2] - from[2]);
            out[0] = (to[0] - from[0]) * t + from[0];
            out[1] = (to[1] - from[1]) * t + from[1];
            out[2] = bound;
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
    n[0] = n[0] * 20; // FAKE: int literal 20 (the other two use 20.0f) recolours the node plane loads (f8/f18 instead of f10/f4); pre-existing, now tagged
    n[1] = n[1] * 20.0f;
    n[2] = n[2] * 20.0f;
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
    } while ((f32 *)((u8 *)D_807F5E20 + i * 12) < sViewPlane);
    return 1;
}


typedef struct MapChunkAnim {
    /* 0x00 */ u8 segment;
    /* 0x01 */ u8 chunk;
    /* 0x02 */ u8 frameDelay;
    /* 0x03 */ u8 frameCount;
    /* 0x04 */ u8 timer;
    /* 0x05 */ u8 frame;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ void *texture;
    /* 0x0C */ s32 textureIds[1];
    /* 0x10 */ u8 pad10[0x6C];
} MapChunkAnim; /* 0x7C */

extern u8 sMapChunkAnimCount;
extern MapChunkAnim *sMapChunkAnims;

Gfx *mapChunkEmitSegmentCommands(Gfx *gfx, u8 chunk) {
    s32 i;

    for (i = 0; i < sMapChunkAnimCount; i++) {
        if (chunk == sMapChunkAnims[i].chunk) {
            gSPSegment(gfx++, sMapChunkAnims[i].segment, sMapChunkAnims[i].texture);
        }
    }
    return gfx;
}



void mapChunkAnimateTextures(u8 chunk) {
    s32 i;
    s32 reload;

    for (i = 0; i < sMapChunkAnimCount; i++) {
        if (chunk == sMapChunkAnims[i].chunk) {
            reload = 0;
            sMapChunkAnims[i].timer++;
            if (sMapChunkAnims[i].timer == sMapChunkAnims[i].frameDelay) {
                sMapChunkAnims[i].timer = 0;
                sMapChunkAnims[i].frame++;
                if (sMapChunkAnims[i].frame == sMapChunkAnims[i].frameCount) {
                    sMapChunkAnims[i].frame = 0;
                }
                reload = 1;
            }
            if (sMapChunkAnims[i].texture == NULL) {
                reload = 1;
            }
            if (reload) {
                if (sMapChunkAnims[i].texture != NULL) {
                    assetFreeBuffer(sMapChunkAnims[i].texture, 0x7E3, 5);
                }
                sMapChunkAnims[i].texture = assetLoad(7, sMapChunkAnims[i].textureIds[sMapChunkAnims[i].frame], 0, 0);
            }
        }
    }
}




void mapChunkFreeHiddenBuffers(void) {
    s32 i;

    for (i = 0; i < sMapChunkAnimCount; i++) {
        if (mapChunkIsVisible(sMapChunkAnims[i].chunk) == 0) {
            if (sMapChunkAnims[i].texture != NULL) {
                assetFreeBuffer(sMapChunkAnims[i].texture, 0x7FB, 5);
                sMapChunkAnims[i].texture = NULL;
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
extern s32 sMapSoundEmitterCount;
extern LevelSoundEmitter *sMapSoundEmitters;

void mapHeaderLoad(MapFileHeader *header) {
    s32 bspOff;
    s32 dlOff;
    s32 dlEndOff;
    s32 emitterOff;
    s32 trackOff;
    s32 chunkAnimOff;
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
    trackOff = header->unk40;
    bspOff = header->unk30;
    dlOff = header->dlBase;
    dlEndOff = header->unk38;
    emitterOff = header->unk44;
    chunkAnimOff = header->unk48;
    D_807F5FD0 = *(s32 *)(D_807F5DE0 + trackOff) + 1;
    gMinecartTrackPoints = (TargetVec3f **)(D_807F5DE0 + trackOff + 4);
    sMapSoundEmitterCount = *(s32 *)(D_807F5DE0 + emitterOff);
    sMapSoundEmitters = (LevelSoundEmitter *)(D_807F5DE0 + emitterOff + 4);
    sMapChunkAnimCount = *(s32 *)(D_807F5DE0 + chunkAnimOff);
    sMapChunkAnims = (MapChunkAnim *)(D_807F5DE0 + chunkAnimOff + 4);
    D_807F5DE4 = (MapBspNode *)(D_807F5DE0 + bspOff);
    D_807F5DE8 = (s32)(D_807F5DE0 + dlEndOff);
    D_807F5DEC = D_807F5DE0 + dlOff;
    lightSetTargetColor(1.0f, 1.0f, 1.0f, -1);
    lightCopyTargetColors(-1);
    matrixCacheInit(header->unkE << 10);
    mapTreeRelocate((MapBspNode *)((s32)D_807F5DE0 + bspOff), (s32)D_807F5DE0 + bspOff, (s32)D_807F5DE0 + dlOff);
    displayListResolveTextureImages((Gfx *)(D_807F5DE0 + dlOff), (Gfx *)(D_807F5DE0 + dlEndOff));
    mapRelocateOffsetTable((s32)(D_807F5DE0 + trackOff));
    mapSurfaceEffectsReset();
    mapNodeTreeInitSurfaceEffects(D_807F5DE4, &effectSlotCount);
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


void mapRelocateOffsetTable(s32 base) {
    s32 i;
    u8 *point;

    if (D_807F5FD0 != 0) {
        for (i = 0; i <= D_807F5FD0; i++) {
            point = (u8 *)gMinecartTrackPoints[i];
            gMinecartTrackPoints[i] = (TargetVec3f *)(point + base);
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


void mapTreeRelocate(MapBspNode *node, s32 base, s32 dlBase) {
    s32 i;

    if (node == NULL) {
        return;
    }
    switch (node->kind) {
        case 0:
            node->child0 = (MapBspNode *)((s32)node->child0 + base);
            node->child1 = (MapBspNode *)((s32)node->child1 + base);
            mapTreeRelocate(node->child0, base, dlBase);
            mapTreeRelocate(node->child1, base, dlBase);
            return;
        case 1:
        case 2:
            break;
        default:
            return;
    }
    if (node->dl != -1) {
        node->dl += dlBase;
    }
    if (node->unkC != -1) {
        node->unkC += dlBase;
    }
    if (node->unk10 != -1) {
        node->unk10 += dlBase;
    }
    if (node->unk14 != -1) {
        node->unk14 += dlBase;
    }
    if (node->unk18 != -1) {
        node->unk18 += dlBase;
    }
    for (i = 0; i < node->unkC5; i++) {
        node->unk1C[i] = (void *)((s32)node->unk1C[i] + dlBase);
    }
}

void matrix3SwapRows(f32 (*mtx)[3], s32 pivot0, s32 pivot1, s32 pivot2) {
    f32 t;
    s32 i;

    if (pivot0 != 0) {
        i = 0;
        if (pivot1 == 0) {
            for (i = 0; i < 3; i++) {
                t = mtx[pivot1][i];
                mtx[pivot1][i] = mtx[pivot0][i];
                mtx[pivot0][i] = t;
            }
            pivot1 = pivot0;
        } else {
            for (i = 0; i < 3; i++) {
                t = mtx[pivot2][i];
                mtx[pivot2][i] = mtx[pivot0][i];
                mtx[pivot0][i] = t;
            }
            pivot2 = pivot0;
        }
    }
    if (pivot1 != 1) {
        for (i = 0; i < 3; i++) {
            t = mtx[pivot2][i];
            mtx[pivot2][i] = mtx[pivot1][i];
            mtx[pivot1][i] = t;
        }
    }
}


s32 matrix3InvertEliminateRest(f32 (*mtx)[3], f32 (*out)[3], s32 pivot0) {
    s32 rowA;
    s32 rowB;
    s32 p;
    s32 q;
    s32 j;
    f32 t;
    f32 u;

    if (pivot0 == 0) {
        rowA = 1;
        rowB = 2;
    } else if (pivot0 == 1) {
        rowA = 0;
        rowB = 2;
    } else {
        rowA = 0;
        rowB = 1;
    }
    t = mtx[rowA][1];
    if (t < 0.0f) {
        t = -t;
    }
    u = mtx[rowB][1];
    if (u < 0.0f) {
        u = -u;
    }
    if (u < t) {
        p = rowA;
    } else {
        p = rowB;
    }
    if (p == rowA) {
        q = rowB;
    } else {
        q = rowA;
    }
    if (mtx[p][1] < 1e-8 && mtx[p][1] > -1e-8) {
        return 0;
    }
    t = 1.0 / mtx[p][1];
    mtx[p][1] = 1.0f;
    mtx[p][2] *= t;
    out[p][p] = t;
    out[p][pivot0] *= t;
    for (j = 0; j < 3; j++) {
        if (j != p) {
            t = mtx[j][1];
            mtx[j][1] = 0.0f;
            t = -t;
            mtx[j][2] += t * mtx[p][2];
            out[j][p] = out[p][p] * t;
            out[j][pivot0] += t * out[p][pivot0];
        }
    }
    if (mtx[q][2] < 1e-8 && mtx[q][2] > -1e-8) {
        return 0;
    }
    t = 1.0 / mtx[q][2];
    mtx[q][2] = 1.0f;
    out[q][q] = t;
    out[q][pivot0] *= t;
    out[q][p] *= t;
    for (j = 0; j < 3; j++) {
        if (j != q) {
            t = mtx[j][2];
            mtx[j][2] = 0.0f;
            t = -t;
            out[j][pivot0] += t * out[q][pivot0];
            out[j][p] += t * out[q][p];
            out[j][q] += t * out[q][q];
        }
    }
    matrix3SwapRows(out, pivot0, p, q);
    return 1;
}


s32 matrix3Invert(f32 (*mtx)[3], f32 (*out)[3]) {
    s32 p;
    s32 j;
    f32 t;
    f32 u;
    f32 v;

    out[2][2] = 1.0f;
    out[2][1] = 0.0f;
    out[2][0] = 0.0f;
    out[1][2] = 0.0f;
    out[1][1] = 1.0f;
    out[1][0] = 0.0f;
    out[0][2] = 0.0f;
    out[0][1] = 0.0f;
    out[0][0] = 1.0f;
    t = mtx[0][0];
    if (t < 0.0f) {
        t = -t;
    }
    u = mtx[1][0];
    if (u < 0.0f) {
        u = -u;
    }
    v = mtx[2][0];
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
    if (mtx[p][0] < 1e-8 && mtx[p][0] > -1e-8) {
        return 0;
    }
    v = 1.0 / mtx[p][0];
    mtx[p][0] = 1.0f;
    mtx[p][1] *= v;
    mtx[p][2] *= v;
    out[p][p] = v;
    for (j = 0; j < 3; j++) {
        if (j != p) {
            v = mtx[j][0];
            mtx[j][0] = 0.0f;
            v = -v;
            mtx[j][1] += v * mtx[p][1];
            mtx[j][2] += v * mtx[p][2];
            out[j][p] = out[p][p] * v;
        }
    }
    if (matrix3InvertEliminateRest(mtx, out, p) == 0) {
        return 0;
    }
    return 1;
}


s32 matrix4NormalizeProjective(f32 (*mtx)[4], f32 *outOffset, f32 *outScale, s32 *outSwapRow) {
    f32 max;
    f32 abs;
    s32 i;
    s32 j;
    f32 tmp;

    *outSwapRow = -1;
    abs = mtx[3][3] > 0.0f ? mtx[3][3] : -mtx[3][3];
    if (abs < 1e-8) {
        max = 0.0f;
        for (i = 0; i < 4; i++) {
            if (max < mtx[i][3]) {
                *outSwapRow = i;
                max = mtx[i][3];
            } else if (mtx[i][3] < -max) {
                *outSwapRow = i;
                max = -mtx[i][3];
            }
        }
        if (*outSwapRow < 0) {
            return 0;
        }
        for (j = 0; j < 4; j++) {
            tmp = mtx[3][j];
            mtx[3][j] = mtx[*outSwapRow][j];
            mtx[*outSwapRow][j] = tmp;
        }
    }
    outOffset[0] = -mtx[0][3];
    outOffset[1] = -mtx[1][3];
    outOffset[2] = -mtx[2][3];
    *outScale = 1.0 / mtx[3][3];
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;
    mtx[3][3] = 1.0f;
    mtx[3][0] *= *outScale;
    mtx[3][1] *= *outScale;
    mtx[3][2] *= *outScale;
    for (i = 0; i < 3; i++) {
        mtx[0][i] += outOffset[0] * mtx[3][i];
        mtx[1][i] += outOffset[1] * mtx[3][i];
        mtx[2][i] += outOffset[2] * mtx[3][i];
    }
    return 1;
}


s32 matrix4Invert(f32 (*out)[4], f32 (*mtx)[4]) {
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
            m[i][k] = mtx[i][k];
            out[i][k] = 0.0f;
        }
    }
    out[0][0] = 1.0f;
    out[1][1] = 1.0f;
    out[2][2] = 1.0f;
    out[3][3] = 1.0f;
    flag = m[0][3] == 0.0; if (flag) { flag = m[1][3] == 0.0; // LAYOUT: the first test and the nested if on one line (split onto separate lines, fdiff fails)
        if (flag) {
            flag = m[2][3] == 0.0;
            if (flag) {
                flag = m[3][3] == 1.0;
            }
        }
    }
    if (!flag) {
        if (!matrix4NormalizeProjective(m, w, &scale, &idx)) {
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
            out[i][k] = inv[i][k];
        }
    }
    for (i = 0; i < 3; i++) {
        for (k = 0; k < 3; k++) {
            out[3][i] -= v[k] * inv[k][i];
        }
    }
    if (!flag) {
        for (i = 0; i < 4; i++) {
            out[i][3] += w[0] * out[i][0] + w[1] * out[i][1] + w[2] * out[i][2];
            out[i][3] *= scale;
        }
        if (idx >= 0) {
            for (i = 0; i < 4; i++) {
                tmp = out[i][3];
                out[i][3] = out[i][idx];
                out[i][idx] = tmp;
            }
        }
    }
    return 1;
}


