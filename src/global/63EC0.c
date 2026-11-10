#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/2F550.h"
#include "proto/global/55B20.h"
#include "proto/global/5E2F0.h"
#include "proto/global/63EC0.h"
#include "proto/global/6AD90.h"

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

typedef struct EffectSubNode {
    /* 0x00 */ f32 texScale;
    /* 0x04 */ f32 waveFreqX;
    /* 0x08 */ f32 waveFreqZ;
    /* 0x0C */ f32 waveAmpX;
    /* 0x10 */ f32 waveAmpZ;
    /* 0x14 */ s32 waveSpeedX;
    /* 0x18 */ s32 waveSpeedZ;
    /* 0x1C */ f32 wobbleFreqX;
    /* 0x20 */ f32 wobbleFreqZ;
    /* 0x24 */ f32 wobbleAmpX;
    /* 0x28 */ f32 wobbleAmpZ;
    /* 0x2C */ s32 wobbleSpeedX;
    /* 0x30 */ s32 wobbleSpeedZ;
    /* 0x34 */ f32 tileScrollStepS;
    /* 0x38 */ f32 tileScrollStepT;
    /* 0x3C */ f32 tileScrollS;
    /* 0x40 */ f32 tileScrollT;
    /* 0x44 */ s16 gridStep;
    /* 0x46 */ s16 minX;
    /* 0x48 */ s16 minZ;
    /* 0x4A */ s16 maxX;
    /* 0x4C */ s16 maxZ;
    /* 0x4E */ s16 surfaceY;
    /* 0x50 */ s16 chunkIds[8];
    /* 0x60 */ u8 pad60;
    /* 0x61 */ u8 r;
    /* 0x62 */ u8 g;
    /* 0x63 */ u8 b;
    /* 0x64 */ u8 alphaBase;
    /* 0x65 */ u8 alphaRange;
    /* 0x66 */ u8 type;
    /* 0x67 */ u8 chunkCount;
    /* 0x68 */ u8 useLights;
    /* 0x69 */ u8 pad69[3];
} EffectSubNode; /* 0x6C */

typedef struct EffectNode {
    EffectSubNode *sub;
    f32 level;
    f32 targetLevel;
    f32 levelStep;
    f32 targetAmpX;
    f32 targetAmpZ;
    f32 ampStep;
    Vtx *meshVtx[2];
    Gfx *meshGdl[2];
    s16 gridStep;
    u8 pad2E[2];
    s32 wavePhaseX;
    s32 wavePhaseZ;
    s32 wobblePhaseX;
    s32 wobblePhaseZ;
    s16 scissorLeft;
    s16 scissorTop;
    s16 scissorRight;
    s16 scissorBottom;
    s16 vtxCount;
    u8 unk4A;
    u8 primAlpha;
    u8 flags;
    u8 forceVisible;
    u8 pad4E[2];
    struct EffectNode *next;
} EffectNode;

typedef struct EffectTableEntry {
    void (*fn0)(u8);
    void (*fn1)();
    void (*fn2)(EffectNode *);
    void *res0;
    void *res1;
    union {
        u32 flags;
        struct {
            u8 loaded;
            u8 pad15;
            u8 drawPass;
            u8 pad17;
        };
    };
} EffectTableEntry;

typedef struct TextureCacheEntry {
    void *texture;
    u8 pad4[0x14];
} TextureCacheEntry;

typedef struct EffectTableFlags {
    u8 heightMode;
    u8 pad1[0x17];
} EffectTableFlags;

typedef struct EffectBufferEntry {
    /* 0x000 */ u8 state;
    /* 0x001 */ u8 pad1[2];
    /* 0x003 */ u8 lightMode;
    /* 0x004 */ u8 pad4[0x68 - 0x4];
    /* 0x068 */ s32 clipLeft;
    /* 0x06C */ s32 clipTop;
    /* 0x070 */ s32 clipRight;
    /* 0x074 */ s32 clipBottom;
    /* 0x078 */ u8 pad78[0x88 - 0x78];
    /* 0x088 */ u8 bspBounds[0x1C8 - 0x88];
} EffectBufferEntry; /* 0x1C8 */

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

extern s32 gCurrentMap;

void effectWaterInitNodes(u8 *mapData) {
    u8 pad[0x1C];
    s32 i;
    EffectSubNode *base;
    EffectNode **pNextNode;
    s32 count;

    for (i = 0; i < 9; i++) {
        D_80748A90[i].loaded = 0;
    }

    pNextNode = &gEffectNodeList;
    if (gCurrentMap == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    gEffectNodeList = NULL;
    count = *(u8 *)(mapData + *(s32 *)(mapData + 0x4C) + 3);
    gWaterRippleActive = 0;

    if (count == (count * 0)) {  // FAKE: extra use of count steers the v0/v1 pick
        return;
    }

    base = (EffectSubNode *)(mapData + *(s32 *)(mapData + 0x4C) + 4);
    for (i = 0; i < count; i++) {
        EffectNode *node = heapAlloc(sizeof(EffectNode));
        s32 gridDimX;
        s32 gridDimZ;
        s32 gdlCmdCount;
        u8 waterType;
        EffectTableEntry *typeEntry;

        *pNextNode = node;
        node->sub = &base[i];
        node->gridStep = base[i].gridStep;
        node->level = 0.0f;
        node->levelStep = 0.0f;
        node->targetLevel = 0.0f;
        node->wavePhaseX = 0;
        node->wavePhaseZ = 0;
        node->wobblePhaseX = 0;
        node->wobblePhaseZ = 0;
        node->unk4A = 0;
        node->primAlpha = 0;
        node->targetAmpX = base[i].waveAmpX;
        node->targetAmpZ = base[i].waveAmpZ;
        node->ampStep = 0.0f;
        node->forceVisible = 0;
        pNextNode = &node->next;

        if (((gCurrentMap == 0x53) || (gCurrentMap == 0xC5)) && (i == 0)) {
            node->forceVisible = 1;
        }

        gridDimX = ((s32)(base[i].maxX - base[i].minX) / base[i].gridStep) + 1;
        gridDimZ = ((s32)(base[i].maxZ - base[i].minZ) / base[i].gridStep) + 1;
        node->vtxCount = (gridDimX + 1) * (gridDimZ + 1);

        node->meshVtx[0] = heapAlloc(node->vtxCount * sizeof(Vtx));
        effectWaterSetMeshPositionsUV(node->meshVtx[0], node);
        effectWaterSetMeshHeightsAlpha(node->meshVtx[0], node);

        node->meshVtx[1] = heapAlloc(node->vtxCount * sizeof(Vtx));
        effectWaterSetMeshPositionsUV(node->meshVtx[1], node);
        effectWaterSetMeshHeightsAlpha(node->meshVtx[1], node);

        gdlCmdCount = (gridDimX * gridDimZ) + (((gridDimX / 16) + 1) * gridDimZ * 2);
        gdlCmdCount += 0xC8;
        node->meshGdl[0] = heapAlloc(gdlCmdCount * sizeof(Gfx));
        node->meshGdl[1] = heapAlloc(gdlCmdCount * sizeof(Gfx));

        waterType = base[i].type;
        typeEntry = &D_80748A90[waterType];
        if (typeEntry->loaded == 0) {
            typeEntry->fn0(waterType);
            typeEntry->loaded = 1;
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
        node->targetAmpX = targetX;
        node->targetAmpZ = targetY;
        node->ampStep = targetZ;
    }
}

void effectNodeApproachTargetPos(EffectNode *node) {
    if (node->sub->waveAmpX < node->targetAmpX) {
        node->sub->waveAmpX += node->ampStep;
        if (node->targetAmpX < node->sub->waveAmpX) {
            node->sub->waveAmpX = node->targetAmpX;
        }
    } else {
        node->sub->waveAmpX -= node->ampStep;
        if (node->sub->waveAmpX < node->targetAmpX) {
            node->sub->waveAmpX = node->targetAmpX;
        }
    }

    if (node->sub->waveAmpZ < node->targetAmpZ) {
        node->sub->waveAmpZ += node->ampStep;
        if (node->targetAmpZ < node->sub->waveAmpZ) {
            node->sub->waveAmpZ = node->targetAmpZ;
        }
    } else {
        node->sub->waveAmpZ -= node->ampStep;
        if (node->sub->waveAmpZ < node->targetAmpZ) {
            node->sub->waveAmpZ = node->targetAmpZ;
        }
    }
}

u8 effectGetTableFlag(EffectNode *node) {
    return D_80748AA5[node->sub->type].heightMode;
}

void effectUpdateNodes(void) {
    EffectNode *node = gEffectNodeList;

    if (node != NULL) {
        do {
            node->flags = 0;
            effectNodeApproachTargetPos(node);
            node = node->next;
        } while (node != NULL);
    }
    if (!(gGlobalPauseFlags & 2)) {
        waterRippleStep();
    }
}

extern f32 D_807F5FAC;
extern PlayerStruct *gPlayerSlots;

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
            if (effectCheckTargetActive(node->sub) != 0 && !(node->flags & 1)) {
                baseHeight = (f32)node->sub->surfaceY + node->level;
                maxWaveHeight = node->sub->waveAmpZ + node->sub->waveAmpX;
                if (node->sub->chunkCount == 1) {
                    bspBounds = &gMapChunks[node->sub->chunkIds[0]].bspBounds[0];
                } else {
                    if (hasInvertedMtx == 0) {
                        guMtxL2F(playerMtx, &gPlayerSlots[playerIndex].viewMtx[gGfxBufferIndex]);
                        hasInvertedMtx = 1;
                        matrix4Invert(invPlayerMtx, playerMtx);
                    }
                    bspBounds = frustumBounds;
                    effectNodeComputeBounds(node, camX, camY, camZ, playerIndex, invPlayerMtx, frustumBounds);
                }
                if (mapBspBoxInFrustum(node->sub->minX, (s16)(baseHeight - maxWaveHeight), node->sub->minZ, node->sub->maxX,
                                  (s32)(baseHeight + maxWaveHeight), node->sub->maxZ, camX, camY, camZ, D_807F5FAC, bspBounds) != 0 || node->forceVisible != 0) {
                    if ((f64)node->sub->wobbleAmpX != 0.0 || (f64)node->sub->wobbleAmpZ != 0.0) {
                        effectWaterSetMeshPositionsUV(node->meshVtx[gGfxBufferIndex], node);
                    }
                    if ((f64)node->sub->waveAmpX != 0.0 || (f64)node->sub->waveAmpZ != 0.0) {
                        effectWaterSetMeshHeightsAlpha(node->meshVtx[gGfxBufferIndex], node);
                    }
                    effectWaterSetMeshColors(node->meshVtx[gGfxBufferIndex], node);
                    node->flags |= 1;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}

void effectNodeComputeBounds(EffectNode *node, f32 camX, f32 camY, f32 camZ, u8 playerIndex, void *invMtx, void *outBounds) {
    s32 rectLeft = 0;
    s32 rectTop = 0;
    s32 rectRight = 0;
    s32 rectBottom = 0;
    s32 outMinX;
    s32 outMinY;
    s32 outMaxX;
    s32 outMaxY;
    s32 i;
    s32 idx;
    f32 frustumWork[4][3];
    EffectSubNode *target = node->sub;

    for (i = 0; i < target->chunkCount; i++) {
        idx = target->chunkIds[i];
        if (gMapChunks[idx].state == 1) {
            mapRectIntersect(rectLeft, rectTop, rectRight, rectBottom, gMapChunks[idx].clipLeft, gMapChunks[idx].clipTop, gMapChunks[idx].clipRight, gMapChunks[idx].clipBottom, &outMinX, &outMinY, &outMaxX, &outMaxY);
            rectLeft = outMinX;
            rectTop = outMinY;
            rectRight = outMaxX;
            rectBottom = outMaxY;
        }
    }
    mapScreenRectBuildFrustum(rectLeft, rectTop, rectRight, rectBottom, camX, camY, camZ, playerIndex, invMtx, outBounds, frustumWork);
    node->scissorLeft = rectLeft;
    node->scissorTop = rectTop;
    node->scissorRight = rectRight;
    node->scissorBottom = rectBottom;
}

s32 effectCheckTargetActive(EffectSubNode *subNode) {
    s32 i;

    for (i = 0; i < subNode->chunkCount; i++) {
        if (gMapChunks[subNode->chunkIds[i]].state == 1) {
            return 1;
        }
    }
    return 0;
}

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern u8 D_807F78C0[];
extern f32 D_807F7EEC;
extern f32 D_807F7EF0;
extern f32 D_807F7EF4;

void func_8065C990(void *, void *, s32, void *, s32, s32);

void effectWaterApplyLights(f32 camX, f32 camY, f32 camZ) {
    EffectNode *node;
    EffectSubNode *target;
    s8 lightCount;
    s16 chunkIdx;
    s32 lights;
    Vtx *vtxBuffer;
    u8 flags;

    node = gEffectNodeList;
    if (node != NULL) {
        do {
            flags = node->flags;
            if ((flags & 1) && !(flags & 2)) {
                target = node->sub;
                chunkIdx = target->chunkIds[0];
                if (target->useLights != 0) {
                    lights = lightCollectVolumesInBounds(camX, camY, camZ, target->minX,
                                           (s32)(((f32)target->surfaceY + node->level) - (target->waveAmpZ + target->waveAmpX)), target->minZ, target->maxX,
                                           (s32)(((f32)target->surfaceY + node->level) + (target->waveAmpZ + target->waveAmpX)), target->maxZ, chunkIdx, &lightCount);
                    D_807F7EEC = D_8076A0B4[chunkIdx];
                    D_807F7EF0 = D_8076A0B8[chunkIdx];
                    D_807F7EF4 = D_8076A0BC[chunkIdx];
                    if (gGlobalPauseFlags & 0x10) {
                        vtxBuffer = node->meshVtx[gGfxBufferIndex];
                        func_8065C990(vtxBuffer, vtxBuffer + node->vtxCount, 1, &D_807F78C0, lights, gMapChunks[chunkIdx].lightMode == 1);
                    }
                    node->flags |= 2;
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
        if ((water->flags & 1) && (waterType == D_80748A90[water->sub->type].drawPass)) {
            gdl = effectWaterSetScissor(gdl, water);
            gSPDisplayList(gdl++, osVirtualToPhysical(water->meshGdl[gGfxBufferIndex]));
            if (!(water->flags & 4)) {
                effectWaterBuildMeshGdl(water->meshGdl[gGfxBufferIndex], water->meshVtx[gGfxBufferIndex], water);
                water->flags |= 4;
            }
        }
        water = water->next;
    }
    return gdl;
}

Gfx *effectWaterSetScissor(Gfx *gdl, EffectNode *water) {
    s32 index;

    gDPPipeSync(gdl++);
    if (water->sub->chunkCount == 1) {
        index = water->sub->chunkIds[0];
        gDPSetScissor(gdl++, G_SC_NON_INTERLACE, gMapChunks[index].clipLeft, gMapChunks[index].clipTop, gMapChunks[index].clipRight, gMapChunks[index].clipBottom);
    } else {
        gDPSetScissor(gdl++, G_SC_NON_INTERLACE, water->scissorLeft, water->scissorTop, water->scissorRight, water->scissorBottom);
    }
    return gdl;
}

typedef struct EffectMeshBuilderEntry {
    Gfx *(*fn)(void *, EffectNode *, u8);
    u8 pad4[0x14];
} EffectMeshBuilderEntry;

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
    gdl = D_80748A94[water->sub->type].fn(vtxBuf, water, water->sub->type);
    countX = ((water->sub->maxX - water->sub->minX) / water->gridStep) + 1;
    countZ = ((water->sub->maxZ - water->sub->minZ) / water->gridStep) + 1;
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

    step = water->gridStep;
    minX = water->sub->minX;
    maxX = water->sub->maxX;
    minZ = water->sub->minZ;
    maxZ = water->sub->maxZ;
    baseHeight = (f32)water->sub->surfaceY + water->level;
    heightScale = water->sub->waveAmpZ + water->sub->waveAmpX;
    alphaMax = water->sub->alphaRange;
    alphaBase = water->sub->alphaBase;
    flag = D_80748AA5[water->sub->type].heightMode;
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

void effectWaterSetMeshColors(Vtx *vtx, EffectNode *water) {
    u8 r;
    EffectSubNode *sub;
    u8 g;
    u8 b;
    s32 minX;
    s32 minZ;
    s32 maxX;
    s32 maxZ;
    s32 step;
    u32 total;
    s32 count;

    r = water->sub->r;
    sub = water->sub;
    g = sub->g;
    b = sub->b;
    minX = sub->minX;
    minZ = sub->minZ;
    maxX = sub->maxX;
    maxZ = sub->maxZ;
    step = water->gridStep;
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

#define WATER_ABS(x) ((x) > 0 ? (x) : -(x))

f32 sqrtf(f32);

f32 effectWaterGetHeightAt(EffectNode *water, s32 worldX, s32 worldZ, u8 type) {
    s32 phaseOffX;
    s32 phaseOffZ;
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
        phaseOffX = (s32)(water->sub->waveFreqX * (f32)worldX);
        phaseOffZ = (s32)(water->sub->waveFreqZ * (f32)worldZ);
        return ((f32)water->sub->surfaceY + water->level + (water->sub->waveAmpX * mathSinF((s16)((water->wavePhaseX + phaseOffX) % 4095)))) + (mathSinF((s16)((water->wavePhaseZ + phaseOffZ) % 4095)) * water->sub->waveAmpZ);

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
                baseH = (f32)water->sub->surfaceY + water->level;
                r = baseH + h;
            } else if ((f64)diff > 150.0) {
                baseH = (f32)water->sub->surfaceY + water->level;
                r = baseH;
            } else {
                baseH = (f32)water->sub->surfaceY + water->level;
                r = (f32)((f64)baseH + ((f64)h + ((0.0 - (f64)h) * (((f64)diff - 50.0) / 100))));
            }
        } else {
            baseH = (f32)water->sub->surfaceY + water->level;
            r = baseH;
        }

        if (type == 2) {
            edgeDist = (f32)WATER_ABS(worldX - water->sub->minX);

            dz = (f32)WATER_ABS(worldX - water->sub->maxX);
            if (dz < edgeDist) edgeDist = dz;

            dz = (f32)WATER_ABS(worldZ - water->sub->maxZ);
            if (dz < edgeDist) edgeDist = dz;

            dz = (f32)WATER_ABS(worldZ - water->sub->minZ);
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
#undef WATER_ABS

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

    step = water->gridStep;
    minX = water->sub->minX;
    maxX = water->sub->maxX;
    minZ = water->sub->minZ;
    maxZ = water->sub->maxZ;
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
            offX = (s32)(water->sub->wobbleFreqX * (f32)x);
            offZ = (s32)(water->sub->wobbleFreqZ * (f32)z);
            posX = (mathSinF((water->wobblePhaseX + offX) & 0xFFF) * water->sub->wobbleAmpX) + (f32)x;
            posZ = (mathSinF((water->wobblePhaseZ + offZ) & 0xFFF) * water->sub->wobbleAmpZ) + (f32)z;
            vtx->v.ob[0] = posX * 3;
            vtx->v.ob[2] = posZ * 3;
            tcX = (s32)((f32)x * water->sub->texScale);
            tcZ = (s32)((f32)z * water->sub->texScale);
            vtx->v.tc[0] = tcX % 0x7FFF;
            vtx->v.tc[1] = tcZ % 0x7FFF;
            vtx++;
            x += step;
        }
        z += step;
    }
}

s32 mathBitwiseNot(s32 val) {
    return ~val;
}

extern s8 D_80746834;
extern OSMesgQueue D_807655F0;
extern OSIoMesg D_807ECE00;

void effectUpdateAndDispatch(void) {
    u32 dmaBuf[6];
    u32 pad[4];
    u32 *dmaWords;
    EffectNode *node;
    u32 romAddr;

    dmaWords = dmaBuf;
    node = gEffectNodeList;
    if ((u32)dmaWords & 7) {
        dmaWords++;
    }
    romAddr = mathBitwiseNot(-0xF81);
    osWritebackDCache(dmaWords, 0x10);
    osPiStartDma(&D_807ECE00, 0, 0, romAddr, dmaWords, 0x10, &D_807655F0);
    D_80746834 = 6;
    osRecvMesg(&D_807655F0, NULL, OS_MESG_BLOCK);
    D_80746834 = 0;
    osInvalDCache(dmaWords, 0x10);
    dmaWords[0] -= 0x3E0EF0F0;
    dmaWords[1] -= 0x3E0EF0F0;
    if (dmaWords[0] != 0x3050A14A || dmaWords[1] != 0xBCFCF506) {
        dmaWords = (u32 *)randomLcgNext();
        romAddr = randomLcgNext();
        osPiStartDma(&D_807ECE00, 0, 0, (u32)dmaWords & 0xFFFF, (void *)((romAddr & 0xFFFFE) + 0x80500000), (randomLcgNext() & 0xFF) + 0x100, &D_807655F0);
    }
    if (node != NULL) {
        do {
            f32 target = node->targetLevel;
            if (target != node->level) {
                if (node->level < target) {
                    node->level += node->levelStep;
                    if (target < node->level) {
                        node->level = target;
                    }
                } else {
                    node->level -= node->levelStep;
                    if (node->level < target) {
                        node->level = target;
                    }
                }
            }
            D_80748A90[node->sub->type].fn2(node);
            node = node->next;
        } while (node != NULL);
    }
}

void effectNodeSetSubVal(s32 nodeIndex, u8 val) {
    EffectNode *node = gEffectNodeList;
    while (node != NULL && nodeIndex != 0) {
        node = node->next;
        nodeIndex--;
    }
    if (node != NULL) {
        node->sub->alphaBase = val;
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
        return node->primAlpha;
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
        node->primAlpha = val;
    }
}

void effectNodeSetTargetAndStep(s32 nodeIndex, f32 target, f32 step) {
    EffectNode *node = gEffectNodeList;
    while (node != NULL && nodeIndex != 0) {
        node = node->next;
        nodeIndex--;
    }
    if (node != NULL) {
        node->targetLevel = target;
        node->levelStep = step;
    }
}

void effectNodeAddTargetAndStep(s32 nodeIndex, f32 delta, f32 step) {
    EffectNode *node = gEffectNodeList;
    while (node != NULL && nodeIndex != 0) {
        node = node->next;
        nodeIndex--;
    }
    if (node != NULL) {
        node->targetLevel += delta;
        node->levelStep = step;
    }
}

void effectNodeCopyValues(f32 *dst) {
    EffectNode *node = gEffectNodeList;
    s32 i;
    for (i = 0; node != NULL && i < 32; i++) {
        dst[i] = node->targetLevel;
        node = node->next;
    }
}

void effectNodeSetValues(f32 *src) {
    EffectNode *node = gEffectNodeList;
    s32 i;
    for (i = 0; node != NULL && i < 32; i++) {
        node->targetLevel = src[i];
        node->level = node->targetLevel;
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
        return node->level;
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
    D_80748A9C[tableIndex].texture = assetLoad(7, 0x3C5, 1, 0);
}

Gfx *effectBuildGdlTexture32x32RGBA(Gfx *dlist, EffectNode *node, u8 tableIndex) {
    gDPPipeSync(dlist++);
    gDPLoadTextureBlock(dlist++, D_80748A9C[tableIndex].texture, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 14, 14);
    WRITE_GFX(dlist++, 0xFC20FE04, 0xFF13F3FF);
    WRITE_GFX(dlist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(dlist++, 0xD9000000, 0);
    WRITE_GFX(dlist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(dlist++, 0xE3000F00, 0);
    WRITE_GFX(dlist++, 0xD7000902, 0xFFFFFFFF);
    WRITE_GFX(dlist++, 0xE200001C, 0x0C184A50);
    WRITE_GFX(dlist++, 0xF2000000 | ((s32)node->sub->tileScrollS & 0xFFF), 0x0107C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0101785E);
    WRITE_GFX(dlist++, (((s32)node->sub->tileScrollT & 0xFFF) | 0xF2000000) | (((s32)node->sub->tileScrollT & 0xFFF) << 12), 0x0207C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0201745D);
    return dlist;
}

Gfx *effectBuildGdlTexture32x32RGBAWithPrim(Gfx *dlist, EffectNode *node, u8 tableIndex) {
    gDPPipeSync(dlist++);
    gDPLoadTextureBlock(dlist++, D_80748A9C[tableIndex].texture, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 14, 14);
    WRITE_GFX(dlist++, 0xFC20FE04, 0xFF0FF3FF);
    gDPSetPrimColor(dlist++, 0, 0, 0, 0, 0, node->sub->alphaBase);
    WRITE_GFX(dlist++, 0xE3000A01, 0x00100000);
    WRITE_GFX(dlist++, 0xD9000000, 0);
    WRITE_GFX(dlist++, 0xD9FFFFFF, 0x00210005);
    WRITE_GFX(dlist++, 0xE3000F00, 0);
    WRITE_GFX(dlist++, 0xD7000902, 0xFFFFFFFF);
    WRITE_GFX(dlist++, 0xE200001C, 0xC8104A50);
    WRITE_GFX(dlist++, 0xF2000000 | ((s32)node->sub->tileScrollS & 0xFFF), 0x0107C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0101785E);
    WRITE_GFX(dlist++, (((s32)node->sub->tileScrollT & 0xFFF) | 0xF2000000) | (((s32)node->sub->tileScrollT & 0xFFF) << 12), 0x0207C07C);
    WRITE_GFX(dlist++, 0xF5181000, 0x0201745D);
    return dlist;
}

void effectNodeStepUVAndPos(EffectNode *node) {
    node->sub->tileScrollS -= node->sub->tileScrollStepS;
    if (node->sub->tileScrollS < 0.0) {
        node->sub->tileScrollS = 255.0f;
    }
    node->sub->tileScrollT -= node->sub->tileScrollStepT;
    if (node->sub->tileScrollT < 0.0) {
        node->sub->tileScrollT = 255.0f;
    }
    node->wavePhaseX += node->sub->waveSpeedX;
    node->wavePhaseZ += node->sub->waveSpeedZ;
    node->wobblePhaseX += node->sub->wobbleSpeedX;
    node->wobblePhaseZ += node->sub->wobbleSpeedZ;
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
    WRITE_GFX(dlist++, 0xF2000000 | ((s32)node->sub->tileScrollS & 0xFFF), 0x000FC0FC);
    WRITE_GFX(dlist++, 0xF5181000, 0x0101785E);
    gDPLoadTLUT_pal16(dlist++, 0, entry->res1);
    gDPSetTextureLUT(dlist++, G_TT_RGBA16);
    return dlist;
}

void effectNodeUpdateAlphaOffset(EffectNode *node) {
    node->sub->tileScrollS -= node->sub->tileScrollStepS;
    if (node->sub->tileScrollS < 0.0) {
        node->sub->tileScrollS = 255.0f;
    }
    node->wavePhaseX += node->sub->waveSpeedX;
    node->wavePhaseZ += node->sub->waveSpeedZ;
    node->wobblePhaseX += node->sub->wobbleSpeedX;
    node->wobblePhaseZ += node->sub->wobbleSpeedZ;
}

void effectInitTextureTable0(u8 tableIndex) {
    D_80748A9C[tableIndex].texture = assetLoad(0x19, 0xF0, 1, 0);
}

Gfx *effectBuildMipmapGdl(Gfx *glist, s32 unusedParam, u8 tableIndex) {
    WRITE_GFX(glist++, 0xE7000000, 0);
    WRITE_GFX(glist++, 0xFD100000, D_80748A9C[tableIndex].texture);
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
    D_80748A9C[tableIndex].texture = assetLoad(0x19, 0xAF4, 1, 0);
}

void effectBuildMipmapGdlWrapper(Gfx *glist, s32 unusedParam, u8 tableIndex) {
    effectBuildMipmapGdl(glist, unusedParam, tableIndex);
}

void effectNoopCallback2(s32 unused) {
}

void effectInitTextureTable2(u8 tableIndex) {
    D_80748A9C[tableIndex].texture = assetLoad(0x19, 0x75C, 1, 0);
}

Gfx *effectBuildMipmapGdlDup(Gfx *glist, s32 unusedParam, u8 tableIndex) {
    WRITE_GFX(glist++, 0xE7000000, 0);
    WRITE_GFX(glist++, 0xFD100000, D_80748A9C[tableIndex].texture);
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
    D_80748A9C[tableIndex].texture = assetLoad(7, 0x3B9, 1, 0);
}

Gfx *effectBuildSingleTextureGdl(Gfx *glist, EffectSubNode **pSubNode, u8 tableIndex) {
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_80748A9C[tableIndex].texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 0, 0);
    WRITE_GFX(glist++, 0xFC121824, 0xFF33FFFF);
    WRITE_GFX(glist++, 0xE3000A01, 0);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x00552230);
    WRITE_GFX(glist++, 0xF2000000 | ((s32)(*pSubNode)->tileScrollS & 0xFFF), 0x0007C07C);
    WRITE_GFX(glist++, 0xF5101000, 0x0101785E);
    return glist;
}

void effectInitTextureTable4(u8 tableIndex) {
    D_80748A9C[tableIndex].texture = assetLoad(7, 0x3D2, 1, 0);
}

Gfx *effectBuildSingleTextureGdlDup(Gfx *glist, EffectSubNode **pSubNode, u8 tableIndex) {
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_80748A9C[tableIndex].texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 0, 0);
    WRITE_GFX(glist++, 0xFC121824, 0xFF33FFFF);
    WRITE_GFX(glist++, 0xE3000A01, 0);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    WRITE_GFX(glist++, 0xE3000F00, 0x00010000);
    WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x00552230);
    WRITE_GFX(glist++, 0xF2000000 | ((s32)(*pSubNode)->tileScrollS & 0xFFF), 0x0007C07C);
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

    gDPSetPrimColor(glist++, 0, node->primAlpha, 255, 255, 255, 100);
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
    node->sub->tileScrollS -= node->sub->tileScrollStepS;
    if (node->sub->tileScrollS < 0.0) {
        node->sub->tileScrollS = 255.0f;
    }
    node->sub->tileScrollT -= node->sub->tileScrollStepT;
    if (node->sub->tileScrollT < 0.0) {
        node->sub->tileScrollT = 255.0f;
    }
    node->wavePhaseX += node->sub->waveSpeedX;
    node->wavePhaseZ += node->sub->waveSpeedZ;
    node->wobblePhaseX += node->sub->wobbleSpeedX;
    node->wobblePhaseZ += node->sub->wobbleSpeedZ;
}
