#include "common.h"
#include "actor.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/2F550.h"
#include "proto/global/55B20.h"
#include "proto/global/5E2F0.h"
#include "proto/global/63EC0.h"
#include "proto/global/6AD90.h"

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

typedef struct EffectSubNode {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x10];
    s32 unk2C;
    s32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    u8 pad44[0xC];
    union {
        struct {
            u8 pad50[0x14];
            u8 val;
            u8 pad65;
        };
        s16 unk50[11];
    };
    u8 unk66;
    u8 unk67;
} EffectSubNode;

typedef struct EffectNode {
    union {
        EffectSubNode *sub;
        EffectSubNode *target;
        EffectSubNode *unk0;
    };
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 x;
    f32 y;
    f32 z;
    void *dl[2];
    void *vtx[2];
    s16 unk2C;
    u8 pad2E[2];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    u8 pad48[2];
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 pad4D[3];
    struct EffectNode *next;
} EffectNode;

typedef struct EffectTableEntry {
    void (*fn0)();
    void (*fn1)();
    void (*fn2)(EffectNode *);
    void *res0;
    void *res1;
    union {
        u32 flags;
        struct {
            u8 pad14[2];
            u8 unk16;
            u8 pad17;
        };
    };
} EffectTableEntry;

typedef struct TextureCacheEntry {
    void *unk0;
    u8 pad4[0x14];
} TextureCacheEntry;

typedef struct EffectTableFlags {
    u8 unk0;
    u8 pad1[0x17];
} EffectTableFlags;

typedef struct EffectBufferEntry {
    u8 unk0;
    u8 pad1[0x1C7];
} EffectBufferEntry;


extern EffectNode *gEffectNodeList;
extern EffectTableEntry D_80748A90[];
extern TextureCacheEntry D_80748A9C[];
extern EffectTableFlags D_80748AA5[];
extern EffectBufferEntry *gMapChunks;
extern s32 gGlobalPauseFlags;
extern u8 gGfxBufferIndex;
extern u8 gWaterRippleActive;
extern f32 gWaterRippleCenter[2];
extern f32 gWaterRippleMaxAmplitude;
extern f32 gWaterRippleAmplitude;
extern f32 gWaterRippleAmplitudeRate;
extern f32 gWaterRippleRadius;
extern f32 gWaterRippleRadiusRate;
extern f32 gWaterRippleMaxRadius;
extern f32 gWaterRippleFalloffStart;

typedef struct WaterTargetData {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x30];
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50[11];
    u8 unk66;
    u8 unk67;
    u8 unk68;
    u8 pad69[3];
} WaterTargetData;

typedef struct WaterNodeData {
    WaterTargetData *target;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 x;
    f32 y;
    f32 z;
    void *dl[2];
    void *vtx[2];
    s16 unk2C;
    u8 pad2E[2];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 pad4E[2];
    struct WaterNodeData *next;
} WaterNodeData;

typedef struct WaterTypeEntry {
    void (*func)(u8);
    u8 pad4[0x10];
    u8 unk14;
    u8 pad15[3];
} WaterTypeEntry;

extern s32 gCurrentMap;


void effectWaterInitNodes(u8 *mapData) {
    u8 pad[0x1C];
    s32 i;
    WaterTargetData *base;
    WaterNodeData **pNextNode;
    s32 count;

    for (i = 0; i < 9; i++) {
        ((WaterTypeEntry *)D_80748A90)[i].unk14 = 0;
    }

    pNextNode = (WaterNodeData **)&gEffectNodeList;
    if (gCurrentMap == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    gEffectNodeList = NULL;
    count = *(u8 *)(mapData + *(s32 *)(mapData + 0x4C) + 3);
    gWaterRippleActive = 0;

    if (count == (count * 0)) {  // FAKE: extra use of count steers the v0/v1 pick
        return;
    }

    base = (WaterTargetData *)(mapData + *(s32 *)(mapData + 0x4C) + 4);
    for (i = 0; i < count; i++) {
        WaterNodeData *node = heapAlloc(0x54);
        s32 gridDimX;
        s32 gridDimZ;
        s32 totalVtxCount;
        u8 waterType;
        WaterTypeEntry *entry2;

        *pNextNode = node;
        node->target = &base[i];
        node->unk2C = base[i].unk44;
        node->unk4 = 0.0f;
        node->unkC = 0.0f;
        node->unk8 = 0.0f;
        node->unk30 = 0;
        node->unk34 = 0;
        node->unk38 = 0;
        node->unk3C = 0;
        node->unk4A = 0;
        node->unk4B = 0;
        node->x = base[i].unkC;
        node->y = base[i].unk10;
        node->z = 0.0f;
        node->unk4D = 0;
        pNextNode = &node->next;

        if (((gCurrentMap == 0x53) || (gCurrentMap == 0xC5)) && (i == 0)) {
            node->unk4D = 1;
        }

        gridDimX = ((s32)(base[i].unk4A - base[i].unk46) / base[i].unk44) + 1;
        gridDimZ = ((s32)(base[i].unk4C - base[i].unk48) / base[i].unk44) + 1;
        node->unk48 = (gridDimX + 1) * (gridDimZ + 1);

        node->dl[0] = heapAlloc(node->unk48 * 0x10);
        effectWaterSetMeshPositionsUV((Vtx *)node->dl[0], (EffectNode *)node);
        effectWaterSetMeshHeightsAlpha((Vtx *)node->dl[0], (EffectNode *)node);

        node->dl[1] = heapAlloc(node->unk48 * 0x10);
        effectWaterSetMeshPositionsUV((Vtx *)node->dl[1], (EffectNode *)node);
        effectWaterSetMeshHeightsAlpha((Vtx *)node->dl[1], (EffectNode *)node);

        totalVtxCount = (gridDimX * gridDimZ) + (((gridDimX / 16) + 1) * gridDimZ * 2);
        totalVtxCount += 0xC8;
        node->vtx[0] = heapAlloc(totalVtxCount << 3);
        node->vtx[1] = heapAlloc(totalVtxCount * 8);

        waterType = base[i].unk66;
        entry2 = (WaterTypeEntry *)D_80748A90 + waterType;
        if (entry2->unk14 == 0) {
            entry2->func(waterType);
            entry2->unk14 = 1;
        }
        node->next = NULL;
    }
}

void effectNodeSetTargetPosition(s32 nodeIndex, f32 targetX, f32 targetY, f32 targetZ) {
    EffectNode *node = gEffectNodeList;

    if (node != NULL && nodeIndex != 0) {
        do {
            node = node->next;
            nodeIndex--;
            if (node == NULL) {
                break;
            }
        } while (nodeIndex != 0);
    }
    if (node != NULL) {
        node->x = targetX;
        node->y = targetY;
        node->z = targetZ;
    }
}

void effectNodeApproachTargetPos(EffectNode *node) {
    if (node->target->unkC < node->x) {
        node->target->unkC += node->z;
        if (node->x < node->target->unkC) {
            node->target->unkC = node->x;
        }
    } else {
        node->target->unkC -= node->z;
        if (node->target->unkC < node->x) {
            node->target->unkC = node->x;
        }
    }

    if (node->target->unk10 < node->y) {
        node->target->unk10 += node->z;
        if (node->y < node->target->unk10) {
            node->target->unk10 = node->y;
        }
    } else {
        node->target->unk10 -= node->z;
        if (node->target->unk10 < node->y) {
            node->target->unk10 = node->y;
        }
    }
}

u8 effectGetTableFlag(EffectNode *node) {
    return D_80748AA5[node->target->unk66].unk0;
}

void effectUpdateNodes(void) {
    EffectNode *node = gEffectNodeList;

    if (node != NULL) {
        do {
            node->unk4C = 0;
            effectNodeApproachTargetPos(node);
            node = node->next;
        } while (node != NULL);
    }
    if (!(gGlobalPauseFlags & 2)) {
        waterRippleStep();
    }
}

typedef struct WaterTargetUpdateView {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x10];
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x1A];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50[1];
    u8 pad52[0x15];
    u8 unk67;
} WaterTargetUpdateView;

extern f32 D_807F5FAC;
extern void *gPlayerSlots;

void effectWaterUpdateMeshes(f32 camX, f32 camY, f32 camZ, u8 playerIndex) {
    EffectNode *node;
    u8 *bspBounds;
    s32 hasInvertedMtx;
    f32 maxWaveHeight;
    f32 baseHeight;
    s32 pad1;
    u8 frustumBounds[0x138];
    u32 pad[2];
    f32 playerMtx[4][4];
    f32 invPlayerMtx[4][4];

    node = gEffectNodeList;
    hasInvertedMtx = 0;

    if (node != NULL) {
        do {
            if (effectCheckTargetActive(node->target) != 0 && !(node->unk4C & 1)) {
                baseHeight = (f32)((WaterTargetUpdateView *)node->target)->unk4E + node->unk4;
                maxWaveHeight = ((WaterTargetUpdateView *)node->target)->unk10 + ((WaterTargetUpdateView *)node->target)->unkC;
                if (((WaterTargetUpdateView *)node->target)->unk67 == 1) {
                    bspBounds = (u8 *)&gMapChunks[((WaterTargetUpdateView *)node->target)->unk50[0]] + 0x88;
                } else {
                    if (hasInvertedMtx == 0) {
                        guMtxL2F(playerMtx, (Mtx *)((u8 *)gPlayerSlots + (playerIndex * 0x2F0) + (gGfxBufferIndex << 6) + 8));
                        hasInvertedMtx = 1;
                        matrix4Invert(invPlayerMtx, playerMtx);
                    }
                    bspBounds = frustumBounds;
                    effectNodeComputeBounds(node, camX, camY, camZ, playerIndex, invPlayerMtx, frustumBounds);
                }
                if (mapBspBoxInFrustum(((WaterTargetUpdateView *)node->target)->unk46, (s16)(baseHeight - maxWaveHeight), ((WaterTargetUpdateView *)node->target)->unk48, ((WaterTargetUpdateView *)node->target)->unk4A,
                                  (s32)(baseHeight + maxWaveHeight), ((WaterTargetUpdateView *)node->target)->unk4C, camX, camY, camZ, D_807F5FAC, bspBounds) != 0 || node->pad4D[0] != 0) {
                    if ((f64)((WaterTargetUpdateView *)node->target)->unk24 != 0.0 || (f64)((WaterTargetUpdateView *)node->target)->unk28 != 0.0) {
                        effectWaterSetMeshPositionsUV(node->dl[gGfxBufferIndex], node);
                    }
                    if ((f64)((WaterTargetUpdateView *)node->target)->unkC != 0.0 || (f64)((WaterTargetUpdateView *)node->target)->unk10 != 0.0) {
                        effectWaterSetMeshHeightsAlpha(node->dl[gGfxBufferIndex], node);
                    }
                    effectWaterSetMeshColors((Vtx *)node->dl[gGfxBufferIndex], node);
                    node->unk4C |= 1;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}

void effectNodeComputeBounds(EffectNode *node, f32 camX, f32 camY, f32 camZ, u8 playerIndex, void *invMtx, void *outBounds) {
    s32 s2 = 0;
    s32 s3 = 0;
    s32 s4 = 0;
    s32 s5 = 0;
    s32 outMinX;
    s32 outMinY;
    s32 outMaxX;
    s32 outMaxY;
    s32 i;
    s32 idx;
    u8 frustumWork[0x30];
    EffectSubNode *target = node->target;

    for (i = 0; i < target->unk67; i++) {
        idx = target->unk50[i];
        if (((u8 *)gMapChunks + idx * 0x1C8)[0] == 1) {
            mapRectIntersect(s2, s3, s4, s5, *(s32 *)(((u8 *)&gMapChunks[idx]) + 0x68), *(s32 *)(((u8 *)&gMapChunks[idx]) + 0x6C), *(s32 *)(((u8 *)&gMapChunks[idx]) + 0x70), *(s32 *)(((u8 *)&gMapChunks[idx]) + 0x74), &outMinX, &outMinY, &outMaxX, &outMaxY);
            s2 = outMinX;
            s3 = outMinY;
            s4 = outMaxX;
            s5 = outMaxY;
        }
    }
    mapScreenRectBuildFrustum(s2, s3, s4, s5, camX, camY, camZ, playerIndex, invMtx, outBounds, frustumWork);
    node->unk40 = s2;
    node->unk42 = s3;
    node->unk44 = s4;
    node->unk46 = s5;
}

s32 effectCheckTargetActive(EffectSubNode *subNode) {
    s32 i;

    for (i = 0; i < subNode->unk67; i++) {
        if (gMapChunks[subNode->unk50[i]].unk0 == 1) {
            return 1;
        }
    }
    return 0;
}

typedef struct WaterTargetRenderView {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x32];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50[11];
    u8 unk66;
    u8 unk67;
    u8 unk68;
} WaterTargetRenderView;

typedef struct WaterNodeRenderView {
    WaterTargetRenderView *target;
    f32 unk4;
    u8 pad8[8];
    f32 x;
    f32 y;
    f32 z;
    s32 unk1C[4];
    u8 pad2C[0x14];
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    u8 pad4A[2];
    u8 unk4C;
    u8 pad4D[3];
    struct WaterNodeRenderView *next;
} WaterNodeRenderView;

typedef struct EffectBufferEntryView {
    u8 unk0;
    u8 pad1[2];
    u8 unk3;
    u8 pad4[0x1C4];
} EffectBufferEntryView;

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern u8 D_807F78C0[];
extern f32 D_807F7EEC;
extern f32 D_807F7EF0;
extern f32 D_807F7EF4;

void func_8065C990(s32, s32, s32, void *, s32, s32);

void effectWaterApplyLights(f32 camX, f32 camY, f32 camZ) {
    WaterNodeRenderView *node;
    WaterTargetRenderView *target;
    u8 lightCount;
    s16 s1;
    s32 v0;
    s32 vtxBuffer;
    u8 flags;

    node = (WaterNodeRenderView *)gEffectNodeList;
    if (node != NULL) {
        do {
            flags = node->unk4C;
            if ((flags & 1) && !(flags & 2)) {
                target = node->target;
                s1 = target->unk50[0];
                if (target->unk68 != 0) {
                    v0 = lightCollectVolumesInBounds(camX, camY, camZ, target->unk46,
                                           (s32)(((f32)target->unk4E + node->unk4) - (target->unk10 + target->unkC)), target->unk48, target->unk4A,
                                           (s32)(((f32)target->unk4E + node->unk4) + (target->unk10 + target->unkC)), target->unk4C, s1, &lightCount);
                    D_807F7EEC = D_8076A0B4[s1];
                    D_807F7EF0 = D_8076A0B8[s1];
                    D_807F7EF4 = D_8076A0BC[s1];
                    if (gGlobalPauseFlags & 0x10) {
                        vtxBuffer = node->unk1C[gGfxBufferIndex];
                        func_8065C990(vtxBuffer, vtxBuffer + node->unk48 * 16, 1, &D_807F78C0, v0, ((EffectBufferEntryView *)gMapChunks)[s1].unk3 == 1);
                    }
                    node->unk4C |= 2;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}

Gfx *effectWaterRenderSurfaces(Gfx *gdl, s32 viewMode, u8 waterType) {
    EffectNode *water;

    water = gEffectNodeList;
    while (water != NULL) {
        if ((water->unk4C & 1) && (waterType == D_80748A90[water->unk0->unk66].unk16)) {
            gdl = effectWaterSetScissor(gdl, water);
            gSPDisplayList(gdl++, osVirtualToPhysical(water->vtx[gGfxBufferIndex]));
            if (!(water->unk4C & 4)) {
                effectWaterBuildMeshGdl(water->vtx[gGfxBufferIndex], water->dl[gGfxBufferIndex], water);
                water->unk4C |= 4;
            }
        }
        water = water->next;
    }
    return gdl;
}

typedef struct EffectBufferEntryRect {
    u8 pad[0x68];
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
} EffectBufferEntryRect;

#define EFFECT_BUFFER_RECT(off) ((EffectBufferEntryRect *)((u32)gMapChunks + (off)))

Gfx *effectWaterSetScissor(Gfx *gdl, EffectNode *water) {
    s32 index;
    s32 offset;

    gDPPipeSync(gdl++);
    if (water->sub->unk67 == 1) {
        index = water->sub->unk50[0];
        offset = index * 0x1C8;
        {
            Gfx *_g = (Gfx *)gdl++;

            _g->words.w0 = ((s32)(EFFECT_BUFFER_RECT(offset)->unk6C * 4.0f) & 0xFFF) | 0xED000000 | (((s32)(EFFECT_BUFFER_RECT(offset)->unk68 * 4.0f) & 0xFFF) << 12);
            _g->words.w1 = ((s32)(EFFECT_BUFFER_RECT(offset)->unk74 * 4.0f) & 0xFFF) | (((s32)(EFFECT_BUFFER_RECT(offset)->unk70 * 4.0f) & 0xFFF) << 12);
        }
    } else {
        gDPSetScissor(gdl++, G_SC_NON_INTERLACE, water->unk40, water->unk42, water->unk44, water->unk46);
    }
    return gdl;
}
#undef EFFECT_BUFFER_RECT

typedef struct EffectMeshBuilderEntry {
    Gfx *(*fn)(void *, EffectNode *, u8);
    u8 pad4[0x14];
} EffectMeshBuilderEntry;

typedef struct EffectMeshTarget {
    u8 pad0[0x46];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    u8 pad4E[0x66 - 0x4E];
    u8 unk66;
} EffectMeshTarget;

extern EffectMeshBuilderEntry D_80748A94[];
extern s32 D_807F93EC;

void effectWaterBuildMeshGdl(void *vtxBuf, void *rawVtx, EffectNode *water) {
    s32 vtxStart;
    s32 vtxNext;
    s32 countX;
    Gfx *gdl;
    s32 x;
    s32 countZ;
    s32 segLen;
    s32 i;
    s32 k;
    u8 done;
    s32 total;

    D_807F93EC = 0;
    gdl = D_80748A94[((EffectMeshTarget *)water->unk0)->unk66].fn(vtxBuf, water, ((EffectMeshTarget *)water->unk0)->unk66);
    countX = ((((EffectMeshTarget *)water->unk0)->unk4A - ((EffectMeshTarget *)water->unk0)->unk46) / water->unk2C) + 1;
    countZ = ((((EffectMeshTarget *)water->unk0)->unk4C - ((EffectMeshTarget *)water->unk0)->unk48) / water->unk2C) + 1;
    total = (countX + 1) * (countZ + 1);
    vtxNext = countX + 1;
    vtxStart = 0;
    x = 0;
    done = 0;
    do {
        segLen = (countX - x + 1) >= 17 ? 16 : (countX - x + 1);
        gSPVertex(gdl++, osVirtualToPhysical(vtxStart * 16 + (u8 *)rawVtx), segLen, 0);
        gSPVertex(gdl++, osVirtualToPhysical(vtxNext * 16 + (u8 *)rawVtx), segLen, 16);
        k = 0;
        for (i = 0; i < segLen - 1; i++) {
            gSP2Triangles(gdl++, k + 1, k, k + 16, 0, k + 16, k + 17, k + 1, 0);
            D_807F93EC += 2;
            k++;
        }
        x += segLen - 1;
        vtxStart += segLen - 1; vtxNext += segLen - 1; // LAYOUT: same source line steers as1 scheduling of the two addu
        if (x == countX) {
            x = 0;
            vtxStart++;
            vtxNext++;
        }
        if (vtxNext == total) {
            done = 1;
        }
    } while (!done);
    gDPPipeSync(gdl++);
    gDPSetTextureLUT(gdl++, G_TT_NONE);
    gSPEndDisplayList(gdl++);
}

typedef struct WaterHeightView {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x46 - 0x14];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    u8 pad50[0x64 - 0x50];
    u8 unk64;
    u8 unk65;
    u8 unk66;
} WaterHeightView;


#define WATER_HEIGHT ((WaterHeightView *)water->unk0)
void effectWaterSetMeshHeightsAlpha(Vtx *vtx, EffectNode *water) {
    s32 countX;
    s32 countZ;
    s16 maxX;
    s16 maxZ;
    s16 step;
    s16 minX;
    s16 minZ;
    s16 x;
    s16 z;
    s32 j;
    s32 i;
    f32 baseHeight;
    f32 heightScale;
    f32 h;
    u8 alphaMax;
    u8 alphaBase;
    u8 flag;

    step = water->unk2C;
    minX = WATER_HEIGHT->unk46;
    maxX = WATER_HEIGHT->unk4A;
    minZ = WATER_HEIGHT->unk48;
    maxZ = WATER_HEIGHT->unk4C;
    baseHeight = (f32)WATER_HEIGHT->unk4E + water->unk4;
    heightScale = WATER_HEIGHT->unk10 + WATER_HEIGHT->unkC;
    alphaMax = WATER_HEIGHT->unk65;
    alphaBase = WATER_HEIGHT->unk64;
    flag = D_80748AA5[WATER_HEIGHT->unk66].unk0;
    countX = ((maxX - minX) / step) + 1;
    countZ = ((maxZ - minZ) / step) + 1;
    z = minZ;
    for (j = 0; j <= countZ; j++) {
        x = minX;
        for (i = 0; i <= countX; i++) {
            if (maxX < x) {
                x = maxX;
            }
            if (maxZ < z) {
                z = maxZ;
            }
            h = effectWaterGetHeightAt(water, x, z, flag);
            vtx->v.ob[1] = h * 3.0f;
            vtx->v.cn[3] = (u32)(((h - baseHeight) / heightScale) * (f32)alphaMax + (f32)alphaBase);
            vtx++;
            x += step;
        }
        z += step;
    }
}
#undef WATER_HEIGHT

typedef struct WaterEffectSubNode {
    u8 pad[0x46];
    s16 minX;
    s16 minZ;
    s16 maxX;
    s16 maxZ;
    u8 pad2[0x61 - 0x4E];
    u8 r;
    u8 g;
    u8 b;
} WaterEffectSubNode;

void effectWaterSetMeshColors(Vtx *vtx, EffectNode *water) {
    u8 r;
    WaterEffectSubNode *sub;
    u8 g;
    u8 b;
    s32 minX;
    s32 minZ;
    s32 maxX;
    s32 maxZ;
    s32 step;
    u32 total;
    s32 count;

    r = ((WaterEffectSubNode *)water->sub)->r;
    sub = (WaterEffectSubNode *)water->sub;
    g = sub->g;
    b = sub->b;
    minX = sub->minX;
    minZ = sub->minZ;
    maxX = sub->maxX;
    maxZ = sub->maxZ;
    step = water->unk2C;
    total = (((maxX - minX) / step) + 2) * (((maxZ - minZ) / step) + 2);
    count = total - 1;
    if (total != 0) {
        do {
            vtx->v.cn[0] = r;
            vtx->v.cn[1] = g;
            vtx->v.cn[2] = b;
            vtx++;
        } while (count--);
    }
}

f32 mathSinF(s16);

typedef struct WaterHeightView2 {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[0x46 - 0x14];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
} WaterHeightView2;

#define WATER_SUB ((WaterHeightView2 *)water->unk0)
#define WATER_ABS(x) ((x) > 0 ? (x) : -(x))

f32 sqrtf(f32);

f32 effectWaterGetHeightAt(EffectNode *water, s32 worldX, s32 worldZ, u8 type) {
    s32 temp1;
    s32 temp;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 diff;
    f32 h;
    f32 r;
    f32 baseH;
    f32 edgeDist;

    switch (type) {
    case 0:
        temp1 = (s32)(WATER_SUB->unk4 * (f32)worldX);
        temp = (s32)(WATER_SUB->unk8 * (f32)worldZ);
        return ((f32)WATER_SUB->unk4E + water->unk4 + (WATER_SUB->unkC * mathSinF((s16)((water->unk30 + temp1) % 4095)))) + (mathSinF((s16)((water->unk34 + temp) % 4095)) * WATER_SUB->unk10);

    case 1:
    case 2:
        if (gWaterRippleActive != 0) {
            dz = (f32)worldZ - gWaterRippleCenter[1];
            dx = (f32)worldX - gWaterRippleCenter[0];
            dist = sqrtf((dz * dz) + (dx * dx));
            if (dist < gWaterRippleRadius) {
                diff = gWaterRippleRadius - dist;
            } else {
                diff = -(gWaterRippleRadius - dist);
            }
            if (gWaterRippleRadius < gWaterRippleFalloffStart) {
                h = gWaterRippleAmplitude;
            } else if (gWaterRippleMaxRadius < gWaterRippleRadius) {
                h = 0.0f;
            } else {
                h = (f32)((f64)gWaterRippleAmplitude + ((0.0 - (f64)gWaterRippleAmplitude) * (f64)((gWaterRippleRadius - gWaterRippleFalloffStart) / (gWaterRippleMaxRadius - gWaterRippleFalloffStart))));
            }
            if ((f64)diff < 50.0) {
                baseH = (f32)WATER_SUB->unk4E + water->unk4;
                r = baseH + h;
            } else if ((f64)diff > 150.0) {
                baseH = (f32)WATER_SUB->unk4E + water->unk4;
                r = baseH;
            } else {
                baseH = (f32)WATER_SUB->unk4E + water->unk4;
                r = (f32)((f64)baseH + ((f64)h + ((0.0 - (f64)h) * (((f64)diff - 50.0) / (100.0 * 1.0)))));  // FAKE: folds to 100.0 but keeps the constant out of the sibling-branch CSE (steers f-reg pick)
            }
        } else {
            baseH = (f32)WATER_SUB->unk4E + water->unk4;
            r = baseH;
        }

        if (type == 2) {
            edgeDist = (f32)WATER_ABS(worldX - WATER_SUB->unk46);

            dz = (f32)WATER_ABS(worldX - WATER_SUB->unk4A);
            if (dz < edgeDist) edgeDist = dz;

            dz = (f32)WATER_ABS(worldZ - WATER_SUB->unk4C);
            if (dz < edgeDist) edgeDist = dz;

            dz = (f32)WATER_ABS(worldZ - WATER_SUB->unk48);
            if (dz < edgeDist) edgeDist = dz;

            if ((f64)edgeDist < 100.0) {
                r = (f32)((f64)baseH + ((f64)(r - baseH) * ((f64)edgeDist / 100.0)));
            }
        }
        return r;

    default:
        return 0.0f;
    }
}
#undef WATER_SUB
#undef WATER_ABS

typedef struct WaterWaveView {
    f32 unk0;
    u8 pad4[0x18];
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x46 - 0x2C];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
} WaterWaveView;

#define WATER_WAVE ((WaterWaveView *)water->unk0)
void effectWaterSetMeshPositionsUV(Vtx *vtx, EffectNode *water) {
    s32 countX;
    s32 countZ;
    s16 maxX;
    s16 maxZ;
    s16 step;
    s16 minX;
    s16 minZ;
    s16 x;
    s16 z;
    s32 j;
    s32 i;
    s16 posX;
    s16 posZ;
    s32 offX;
    s32 offZ;
    s32 tcX;
    s32 tcZ;

    step = water->unk2C;
    minX = WATER_WAVE->unk46;
    maxX = WATER_WAVE->unk4A;
    minZ = WATER_WAVE->unk48;
    maxZ = WATER_WAVE->unk4C;
    countX = ((maxX - minX) / step) + 1;
    countZ = ((maxZ - minZ) / step) + 1;
    z = minZ;
    for (j = 0; j <= countZ; j++) {
        x = minX;
        for (i = 0; i <= countX; i++) {
            if (maxX < x) {
                x = maxX;
            }
            if (maxZ < z) {
                z = maxZ;
            }
            offX = (s32)(WATER_WAVE->unk1C * (f32)x);
            offZ = (s32)(WATER_WAVE->unk20 * (f32)z);
            posX = (mathSinF((water->unk38 + offX) & 0xFFF) * WATER_WAVE->unk24) + (f32)x;
            posZ = (mathSinF((water->unk3C + offZ) & 0xFFF) * WATER_WAVE->unk28) + (f32)z;
            vtx->v.ob[0] = posX * 3;
            vtx->v.ob[2] = posZ * 3;
            tcX = (s32)((f32)x * WATER_WAVE->unk0);
            tcZ = (s32)((f32)z * WATER_WAVE->unk0);
            vtx->v.tc[0] = tcX % 0x7FFF;
            vtx->v.tc[1] = tcZ % 0x7FFF;
            vtx++;
            x += step;
        }
        z += step;
    }
}
#undef WATER_WAVE

s32 mathBitwiseNot(s32 val) {
    return ~val;
}

extern s8 D_80746834;
extern OSMesgQueue D_807655F0;
extern OSIoMesg D_807ECE00;

void effectUpdateAndDispatch(void) {
    u32 dmaBuf[6];
    u32 pad[4];
    u32 *s1;
    EffectNode *s0;
    u32 s2;

    s1 = dmaBuf;
    s0 = gEffectNodeList;
    if ((u32)s1 & 7) {
        s1++;
    }
    s2 = mathBitwiseNot(-0xF81);
    osWritebackDCache(s1, 0x10);
    osPiStartDma(&D_807ECE00, 0, 0, s2, s1, 0x10, &D_807655F0);
    D_80746834 = 6;
    osRecvMesg(&D_807655F0, NULL, 1);
    D_80746834 = 0;
    osInvalDCache(s1, 0x10);
    s1[0] -= 0x3E0EF0F0;
    s1[1] -= 0x3E0EF0F0;
    if (s1[0] != 0x3050A14A || s1[1] != 0xBCFCF506) {
        s1 = (u32 *)randomLcgNext();
        s2 = randomLcgNext();
        osPiStartDma(&D_807ECE00, 0, 0, (u32)s1 & 0xFFFF, (void *)((s2 & 0xFFFFE) + 0x80500000), (randomLcgNext() & 0xFF) + 0x100, &D_807655F0);
    }
    if (s0 != NULL) {
        do {
            f32 target = s0->unk8;
            if (target != s0->unk4) {
                if (s0->unk4 < target) {
                    s0->unk4 += s0->unkC;
                    if (target < s0->unk4) {
                        s0->unk4 = target;
                    }
                } else {
                    s0->unk4 -= s0->unkC;
                    if (s0->unk4 < target) {
                        s0->unk4 = target;
                    }
                }
            }
            D_80748A90[s0->sub->unk66].fn2(s0);
            s0 = s0->next;
        } while (s0 != NULL);
    }
}

void effectNodeSetSubVal(s32 nodeIndex, u8 val) {
    EffectNode *node = gEffectNodeList;
    while (node != NULL && nodeIndex != 0) {
        node = node->next;
        nodeIndex--;
    }
    if (node != NULL) {
        node->sub->val = val;
    }
}

void effectNodeSetUnk4A(s32 nodeIndex, u8 val) {
    EffectNode *node = gEffectNodeList;
    while (node != NULL && nodeIndex != 0) {
        node = node->next;
        nodeIndex--;
    }
    if (node != NULL) {
        node->unk4A = val;
    }
}

u8 effectNodeGetUnk4B(s32 nodeIndex) {
    EffectNode *node = gEffectNodeList;
    while (node != NULL && nodeIndex != 0) {
        node = node->next;
        nodeIndex--;
    }
    if (node != NULL) {
        return node->unk4B;
    }
    return 0;
}

void effectNodeSetUnk4B(s32 nodeIndex, u8 val) {
    EffectNode *node = gEffectNodeList;
    while (node != NULL && nodeIndex != 0) {
        node = node->next;
        nodeIndex--;
    }
    if (node != NULL) {
        node->unk4B = val;
    }
}

void effectNodeSetTargetAndStep(s32 nodeIndex, f32 target, f32 step) {
    EffectNode *node = gEffectNodeList;
    while (node != NULL && nodeIndex != 0) {
        node = node->next;
        nodeIndex--;
    }
    if (node != NULL) {
        node->unk8 = target;
        node->unkC = step;
    }
}

void effectNodeAddTargetAndStep(s32 nodeIndex, f32 delta, f32 step) {
    EffectNode *node = gEffectNodeList;
    while (node != NULL && nodeIndex != 0) {
        node = node->next;
        nodeIndex--;
    }
    if (node != NULL) {
        node->unk8 += delta;
        node->unkC = step;
    }
}

void effectNodeCopyValues(f32 *dst) {
    EffectNode *node = gEffectNodeList;
    s32 i;
    for (i = 0; node != NULL && i < 32; i++) {
        dst[i] = node->unk8;
        node = node->next;
    }
}

void effectNodeSetValues(f32 *src) {
    EffectNode *node = gEffectNodeList;
    s32 i;
    for (i = 0; node != NULL && i < 32; i++) {
        node->unk8 = src[i];
        node->unk4 = node->unk8;
        node = node->next;
    }
}

f32 effectNodeGetValue(s32 nodeIndex) {
    EffectNode *node = gEffectNodeList;
    while (node != NULL && nodeIndex != 0) {
        node = node->next;
        nodeIndex--;
    }
    if (node != NULL) {
        return node->unk4;
    }
    return 0.0f;
}

void waterRippleStart(f32 centerX, f32 centerZ, f32 maxAmplitude, f32 amplitudeRate, f32 radiusRate, f32 maxRadius) {
    if (gWaterRippleActive == 0) {
        gWaterRippleCenter[0] = centerX;
        gWaterRippleCenter[1] = centerZ;
        gWaterRippleAmplitude = 0.0f;
        gWaterRippleMaxAmplitude = maxAmplitude;
        gWaterRippleAmplitudeRate = amplitudeRate;
        gWaterRippleRadius = 0.0f;
        gWaterRippleRadiusRate = radiusRate;
        gWaterRippleMaxRadius = maxRadius;
        gWaterRippleFalloffStart = (maxRadius * 2) / 3.0f;
        gWaterRippleActive = 1;
    }
}

void waterRippleStep(void) {
    if (gWaterRippleActive != 0) {
        gWaterRippleAmplitude += gWaterRippleAmplitudeRate;
        if (gWaterRippleMaxAmplitude < gWaterRippleAmplitude) {
            gWaterRippleAmplitude = gWaterRippleMaxAmplitude;
        }
        gWaterRippleRadius += gWaterRippleRadiusRate;
        if (gWaterRippleMaxRadius < gWaterRippleRadius) {
            gWaterRippleActive = 0;
        }
    }
}

void waterRippleStop(void) {
    gWaterRippleActive = 0;
}

void effectInitTextureTableRGBA32(u8 tableIndex) {
    D_80748A9C[tableIndex].unk0 = assetLoad(7, 0x3C5, 1, 0);
}

Gfx *effectBuildGdlTexture32x32RGBA(Gfx *dlist, EffectNode *node, u8 tableIndex) {
    gDPPipeSync(dlist++);
    gDPLoadTextureBlock(dlist++, D_80748A9C[tableIndex].unk0, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 14, 14);
    WRITE_GFX(dlist++, 0xFC20FE04, 0xFF13F3FF);
    WRITE_GFX(dlist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(dlist++, 0xD9000000, 0);
    WRITE_GFX(dlist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(dlist++, 0xE3000F00, 0);
    WRITE_GFX(dlist++, 0xD7000902, 0xFFFFFFFF);
    WRITE_GFX(dlist++, 0xE200001C, 0x0C184A50);
    WRITE_GFX(dlist++, 0xF2000000 | ((s32)node->sub->unk3C & 0xFFF), 0x0107C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0101785E);
    WRITE_GFX(dlist++, (((s32)node->sub->unk40 & 0xFFF) | 0xF2000000) | (((s32)node->sub->unk40 & 0xFFF) << 12), 0x0207C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0201745D);
    return dlist;
}

Gfx *effectBuildGdlTexture32x32RGBAWithPrim(Gfx *dlist, EffectNode *node, u8 tableIndex) {
    gDPPipeSync(dlist++);
    gDPLoadTextureBlock(dlist++, D_80748A9C[tableIndex].unk0, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 14, 14);
    WRITE_GFX(dlist++, 0xFC20FE04, 0xFF0FF3FF);
    gDPSetPrimColor(dlist++, 0, 0, 0, 0, 0, node->sub->val);
    WRITE_GFX(dlist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(dlist++, 0xD9000000, 0);
    WRITE_GFX(dlist++, 0xD9FFFFFF, 0x00210005);
    WRITE_GFX(dlist++, 0xE3000F00, 0);
    WRITE_GFX(dlist++, 0xD7000902, 0xFFFFFFFF);
    WRITE_GFX(dlist++, 0xE200001C, 0xC8104A50);
    WRITE_GFX(dlist++, 0xF2000000 | ((s32)node->sub->unk3C & 0xFFF), 0x0107C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0101785E);
    WRITE_GFX(dlist++, (((s32)node->sub->unk40 & 0xFFF) | 0xF2000000) | (((s32)node->sub->unk40 & 0xFFF) << 12), 0x0207C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0201745D);
    return dlist;
}

void effectNodeStepUVAndPos(EffectNode *node) {
    node->sub->unk3C -= node->sub->unk34;
    if (node->sub->unk3C < 0.0) {
        node->sub->unk3C = 255.0f;
    }
    node->sub->unk40 -= node->sub->unk38;
    if (node->sub->unk40 < 0.0) {
        node->sub->unk40 = 255.0f;
    }
    node->unk30 += node->sub->unk14;
    node->unk34 += node->sub->unk18;
    node->unk38 += node->sub->unk2C;
    node->unk3C += node->sub->unk30;
}

void effectInitTextureTableCI4(u8 tableIndex) {
    D_80748A90[tableIndex].res0 = assetLoad(0x19, 0x2EE, 1, 0);
    D_80748A90[tableIndex].res1 = assetLoad(0x19, 0x2EF, 1, 0);
}

Gfx *effectBuildGdlTexture64x64CI4(Gfx *dlist, EffectNode *node, u8 tableIndex) {
    EffectTableEntry *entry = &D_80748A90[tableIndex];
    gDPPipeSync(dlist++);
    gDPLoadTextureBlock_4b(dlist++, entry->res0, G_IM_FMT_CI, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, 0, 0);
    WRITE_GFX(dlist++, 0xFC121824, 0xFF33FFFF);
    WRITE_GFX(dlist++, 0xE3000A01, 0);
    WRITE_GFX(dlist++, 0xD9000000, 0);
    WRITE_GFX(dlist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(dlist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(dlist++, 0xD7000002, 0xFFFFFFFF);
    WRITE_GFX(dlist++, 0xE200001C, 0x00552230);
    WRITE_GFX(dlist++, 0xF2000000 | ((s32)node->sub->unk3C & 0xFFF), 0x000FC0FC);
    WRITE_GFX(dlist++, 0xF5181000, 0x0101785E);
    gDPLoadTLUT_pal16(dlist++, 0, entry->res1);
    gDPSetTextureLUT(dlist++, G_TT_RGBA16);
    return dlist;
}

void effectNodeUpdateAlphaOffset(EffectNode *node) {
    node->sub->unk3C -= node->sub->unk34;
    if (node->sub->unk3C < 0.0) {
        node->sub->unk3C = 255.0f;
    }
    node->unk30 += node->sub->unk14;
    node->unk34 += node->sub->unk18;
    node->unk38 += node->sub->unk2C;
    node->unk3C += node->sub->unk30;
}

void effectInitTextureTable0(u8 tableIndex) {
    D_80748A9C[tableIndex].unk0 = assetLoad(0x19, 0xF0, 1, 0);
}

Gfx *effectBuildMipmapGdl(Gfx *glist, s32 unusedParam, u8 tableIndex) {
    WRITE_GFX(glist++, 0xE7000000, 0);
    WRITE_GFX(glist++, 0xFD100000, D_80748A9C[tableIndex].unk0);
    WRITE_GFX(glist++, 0xF5100000, 0x07000000);
    WRITE_GFX(glist++, 0xE6000000, 0);
    WRITE_GFX(glist++, 0xF3000000, 0x0754F000);
    WRITE_GFX(glist++, 0xF5101000, 0x00014050);
    WRITE_GFX(glist++, 0xF2002002, 0x0007E07E);
    WRITE_GFX(glist++, 0xF5100900, 0x01010441);
    WRITE_GFX(glist++, 0xF2002002, 0x0103E03E);
    WRITE_GFX(glist++, 0xF5100540, 0x0200C832);
    WRITE_GFX(glist++, 0xF2002002, 0x0201E01E);
    WRITE_GFX(glist++, 0xF5100350, 0x03008C23);
    WRITE_GFX(glist++, 0xF2002002, 0x0300E00E);
    WRITE_GFX(glist++, 0xFC26A004, 0x1F1093FF);
    WRITE_GFX(glist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7001802, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x0C192230);
    return glist;
}

void effectNoopCallback1(s32 unused) {
}

void effectInitTextureTable1(u8 tableIndex) {
    D_80748A9C[tableIndex].unk0 = assetLoad(0x19, 0xAF4, 1, 0);
}

void effectBuildMipmapGdlWrapper(Gfx *glist, s32 unusedParam, u8 tableIndex) {
    effectBuildMipmapGdl(glist, unusedParam, tableIndex);
}

void effectNoopCallback2(s32 unused) {
}

void effectInitTextureTable2(u8 tableIndex) {
    D_80748A9C[tableIndex].unk0 = assetLoad(0x19, 0x75C, 1, 0);
}

Gfx *effectBuildMipmapGdlDup(Gfx *glist, s32 unusedParam, u8 tableIndex) {
    WRITE_GFX(glist++, 0xE7000000, 0);
    WRITE_GFX(glist++, 0xFD100000, D_80748A9C[tableIndex].unk0);
    WRITE_GFX(glist++, 0xF5100000, 0x07000000);
    WRITE_GFX(glist++, 0xE6000000, 0);
    WRITE_GFX(glist++, 0xF3000000, 0x0754F000);
    WRITE_GFX(glist++, 0xF5101000, 0x00014050);
    WRITE_GFX(glist++, 0xF2002002, 0x0007E07E);
    WRITE_GFX(glist++, 0xF5100900, 0x01010441);
    WRITE_GFX(glist++, 0xF2002002, 0x0103E03E);
    WRITE_GFX(glist++, 0xF5100540, 0x0200C832);
    WRITE_GFX(glist++, 0xF2002002, 0x0201E01E);
    WRITE_GFX(glist++, 0xF5100350, 0x03008C23);
    WRITE_GFX(glist++, 0xF2002002, 0x0300E00E);
    WRITE_GFX(glist++, 0xFC26A004, 0x1F1093FF);
    WRITE_GFX(glist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7001802, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x0C192230);
    return glist;
}

void effectNoopCallback3(s32 unused) {
}

void effectInitTextureTable3(u8 tableIndex) {
    D_80748A9C[tableIndex].unk0 = assetLoad(7, 0x3B9, 1, 0);
}

Gfx *effectBuildSingleTextureGdl(Gfx *glist, EffectSubNode **pSubNode, u8 tableIndex) {
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_80748A9C[tableIndex].unk0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 0, 0);
    WRITE_GFX(glist++, 0xFC121824, 0xFF33FFFF);
    WRITE_GFX(glist++, 0xE3000A01, 0);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x00552230);
    WRITE_GFX(glist++, 0xF2000000 | ((s32)(*pSubNode)->unk3C & 0xFFF), 0x0007C07C);
    WRITE_GFX(glist++, 0xF5101000, 0x0101785E);
    return glist;
}

void effectInitTextureTable4(u8 tableIndex) {
    D_80748A9C[tableIndex].unk0 = assetLoad(7, 0x3D2, 1, 0);
}

Gfx *effectBuildSingleTextureGdlDup(Gfx *glist, EffectSubNode **pSubNode, u8 tableIndex) {
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_80748A9C[tableIndex].unk0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 0, 0);
    WRITE_GFX(glist++, 0xFC121824, 0xFF33FFFF);
    WRITE_GFX(glist++, 0xE3000A01, 0);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x00552230);
    WRITE_GFX(glist++, 0xF2000000 | ((s32)(*pSubNode)->unk3C & 0xFFF), 0x0007C07C);
    WRITE_GFX(glist++, 0xF5101000, 0x0101785E);
    return glist;
}

void effectInitTextureTableDual(u8 tableIndex) {
    D_80748A90[tableIndex].res0 = assetLoad(7, 0x3BA, 1, 0);
    D_80748A90[tableIndex].res1 = assetLoad(7, 0x3DB, 1, 0);
}

extern s32 D_80748B68;

Gfx *effectBuildMultiBlockTextureGdl(Gfx *glist, EffectNode *node, u8 tableIndex) {
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_80748A90[tableIndex].res0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 14, 14);
    gDPLoadMultiBlock(glist++, D_80748A90[tableIndex].res1, 256, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, D_80748B68, D_80748B68);

    gDPSetPrimColor(glist++, 0, node->unk4B, 255, 255, 255, 100);
    WRITE_GFX(glist++, 0xFC272C03, 0x1FFC93FB);
    WRITE_GFX(glist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0);
    WRITE_GFX(glist++, 0xD7000802, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x0C184A50);

    return glist;
}

void effectNodeUpdateDualAlphaOffset(EffectNode *node) {
    node->sub->unk3C -= node->sub->unk34;
    if (node->sub->unk3C < 0.0) {
        node->sub->unk3C = 255.0f;
    }
    node->sub->unk40 -= node->sub->unk38;
    if (node->sub->unk40 < 0.0) {
        node->sub->unk40 = 255.0f;
    }
    node->unk30 += node->sub->unk14;
    node->unk34 += node->sub->unk18;
    node->unk38 += node->sub->unk2C;
    node->unk3C += node->sub->unk30;
}
