#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "render.h"
#include "sched.h"
#include "proto/global/15050.h"
#include "proto/global/61AA0.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"


extern u8 gSegment6Override;

void renderSetSegment6Override(u8 enabled) {
    gSegment6Override = enabled;
}

extern Gfx D_80748310[6][2];

void renderReplaceSegment6Commands(Gfx *start, void *end) { // end: one past the last command
    while (start != end) {
        s32 found = 0;
        s32 i = 0;

        while (i < 6 && !found) {
            if (start->words.w0 == D_80748310[i][0].words.w0 && start->words.w1 == D_80748310[i][0].words.w1) {
                found = 1;
            } else {
                i++;
            }
        }
        if (found) {
            gSPDisplayList(start++, 0x06000000 + i * 0x10);
        } else {
            start++;
        }
    }
}

extern PlayerStruct *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s32 gCurrentMap;
#define R2A_SQ(x) ((x) * (x))

void renderCalcPlayerDistanceAlpha(f32 x, f32 y, f32 z, f32 maxDist, s16 actorType, s16 *outAlpha) {
    s32 pad;
    f32 dist;
    f32 fadeStart;
    f32 fadeEnd;

    dist = sqrtf(R2A_SQ(x - gPlayerSlots[gCurrentPlayerIndex].eyeX) + R2A_SQ(y - gPlayerSlots[gCurrentPlayerIndex].eyeY) + R2A_SQ(z - gPlayerSlots[gCurrentPlayerIndex].eyeZ));
    if (gCurrentMap == 0x26) {
        maxDist = renderAdjustActorDistance(actorType, maxDist);
        if (maxDist < dist) {
            *outAlpha = 0;
            return;
        }
    }
    fadeEnd = renderScaleDistanceByFov(maxDist);
    fadeStart = (fadeEnd * 3.0f) / 4;
    if (dist < fadeStart) {
        *outAlpha = 0xFF;
        return;
    }
    *outAlpha = ((dist - fadeStart) / (fadeEnd - fadeStart)) * 255.0f;
    if (*outAlpha >= 0x100) {
        *outAlpha = 0xFF;
    }
    *outAlpha = 0xFF - *outAlpha;
}

extern f32 D_807F6940;

f32 renderAdjustActorDistance(s16 actorType, f32 dist) {
    if ((actorType == 0xB2) || (actorType == 0x253)) {
        dist += (600.0 - dist) * D_807F6940;
    }
    return dist;
}

extern Gfx D_80748370[6][2];
extern Gfx D_807483D0[6][2];

Gfx *renderSetSegment6AndFog(Gfx *gdl, s16 fogAlpha, u8 override) {
    if (fogAlpha == 0xFF) {
        if (gSegment6Override != 0 || override) {
            gSPSegment(gdl++, 6, osVirtualToPhysical(&D_80748310));
        } else {
            gSPSegment(gdl++, 6, osVirtualToPhysical(&D_80748370));
        }
    } else {
        gDPSetFogColor(gdl++, 0, 0, 0, fogAlpha);
        gSPSegment(gdl++, 6, osVirtualToPhysical(&D_807483D0));
    }
    return gdl;
}

extern f32 D_807F5FDC;
extern f32 D_807F5FE0;

f32 renderScaleDistanceByFov(f32 dist) {
    if (gPlayerSlots[gCurrentPlayerIndex].fov == 45.0) {
        return dist;
    }
    return (dist / D_807F5FDC) * D_807F5FE0;
}

typedef struct {
    s32 lastUsedFrame;
    s16 assetId;
    s16 pad6;
    void *texture;
} BillboardCacheEntry;
extern BillboardCacheEntry gBillboardCache[4];
extern u16 gBillboardFlags;

void billboardCacheInit(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        gBillboardCache[i].lastUsedFrame = -1;
    }
    gBillboardFlags = 0;
}

extern u8 gBillboardQueueCount;

void billboardCacheEvictStale(void) {
    s32 i;

    gBillboardQueueCount = 0;
    for (i = 0; i < 4; i++) {
        if (gBillboardCache[i].lastUsedFrame != -1 && (gFrameCounter - gBillboardCache[i].lastUsedFrame) >= 21) {
            assetFreeBuffer(gBillboardCache[i].texture, 0x65, 0x4D);
            gBillboardCache[i].lastUsedFrame = -1;
        }
    }
}

void billboardSetFlags(s16 flags) {
    gBillboardFlags = flags;
}

typedef struct {
    Mtx matrices[2];
    Vtx verts[2][4];
    u16 renderFlags;
    u8 cacheIndex;
    u8 texWidth;
    u8 texHeight;
    u8 texFormat;
    u8 alpha;
    s8 layer;
} BillboardData;
extern BillboardData gBillboardQueue[16];
extern u8 gGfxBufferIndex;


void billboardSubmit(Actor *actor, s16 assetId, s16 texWidth, s16 texHeight, s16 halfWidth, s16 halfHeight, u8 texFormat, s16 fadeDistance, u8 alpha, s16 rotY, f32 xRatio) {
    s32 found;
    s32 i;
    f32 scale;
    f32 mtx1[4][4];
    f32 mtx2[4][4];
    f32 groundY;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    found = FALSE;
    i = 0;
    if (gBillboardQueueCount == 15) {
        gBillboardFlags = 0;
        return;
    }
    if ((actor->floorY > 32767.0f) || (actor->floorY < -32768.0f)) {
        gBillboardFlags = 0;
        return;
    }

    do {
        if ((gBillboardCache[i].lastUsedFrame != -1) && (assetId == gBillboardCache[i].assetId)) {
            found = TRUE;
        } else {
            i++;
        }
    } while ((i < 4) && !found);

    if (!found) {
        i = 0;
        found = FALSE;
        if ((u32)gBillboardCache[i].lastUsedFrame == 0xFFFFFFFF) {} // FAKE: dead read of the typed -1 pushes its constant load ahead of the loop-2 induction setup
        while ((i < 4) && !found) {
            if ((u32)gBillboardCache[i].lastUsedFrame == 0xFFFFFFFF) { // FAKE: unsigned spelling of the -1 sentinel steers the compare
                found = TRUE;
            } else {
                i++;
            }
        }

        if (!found) {
            return;
        }
        gBillboardCache[i].texture = assetLoad(7, assetId, 0, 0);
        gBillboardCache[i].assetId = assetId;
    }
    gBillboardCache[i * 1].lastUsedFrame = gFrameCounter; // FAKE: no-op index multiply keeps this address from being CSEd with the loop IV
    gBillboardQueue[gBillboardQueueCount].cacheIndex = i;
    gBillboardQueue[gBillboardQueueCount].alpha = alpha;
    if (actor->renderFlags & 0x40) {
        gBillboardFlags |= 1;
    }
    gBillboardQueue[gBillboardQueueCount].renderFlags = gBillboardFlags;
    gBillboardQueue[gBillboardQueueCount].layer = actor->chunkIndex;

    billboardSetVertex(&gBillboardQueue[gBillboardQueueCount].verts[gGfxBufferIndex][0], -(halfWidth * xRatio), -halfHeight, 0, 0);
    billboardSetVertex(&gBillboardQueue[gBillboardQueueCount].verts[gGfxBufferIndex][1], halfWidth, -halfHeight, texWidth - 1, 0);
    billboardSetVertex(&gBillboardQueue[gBillboardQueueCount].verts[gGfxBufferIndex][2], -(halfWidth * xRatio), halfHeight, 0, texHeight - 1);
    billboardSetVertex(&gBillboardQueue[gBillboardQueueCount].verts[gGfxBufferIndex][3], halfWidth, halfHeight, texWidth - 1, texHeight - 1);

    groundY = actor->floorY;
    if ((gBillboardFlags & 2) && (actor->contactFlags & 2) && (actor->waterY <= actor->y)) {
        f32 diff1 = (actor->y > actor->waterY) ? (actor->y - actor->waterY) : -(actor->y - actor->waterY);
        f32 diff2 = (actor->y > actor->floorY) ? (actor->y - actor->floorY) : -(actor->y - actor->floorY);
        if (diff1 < diff2) {
            groundY = actor->waterY;
        }
    }
    scale = 1.0 - (actor->y - groundY) / fadeDistance;
    if (scale < 0.0) {
        scale = 0.0f;
    }
    guScaleF(mtx1, scale, scale, scale);

    guRotateF(mtx2, (rotY * 360) / 4095, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx1, mtx2, mtx1);
    if (actor->flags & 2) {
        if (actor->floorTiltPitch < 1000) {
            guRotateF(mtx2, -(actor->floorTiltYaw / 4095.0 * 360.0), 0.0f, 1.0f, 0.0f);
            guMtxCatF(mtx1, mtx2, mtx1);
        }
        guRotateF(mtx2, 90.0 - actor->floorTiltPitch / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
        guMtxCatF(mtx1, mtx2, mtx1);
        if (actor->floorTiltPitch < 1000) {
            guRotateF(mtx2, actor->floorTiltYaw / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
            guMtxCatF(mtx1, mtx2, mtx1);
        }
    }

    if (actor->floorNodeId) {
        actorGetNodePos(actor, actor->floorNodeId, &nodeX, &nodeY, &nodeZ);
        guTranslateF(mtx2, nodeX, actor->floorY, nodeZ);
    } else {
        guTranslateF(mtx2, actor->x, groundY, actor->z);
    }
    guMtxCatF(mtx1, mtx2, mtx1);

    guMtxF2L(mtx1, &gBillboardQueue[gBillboardQueueCount].matrices[gGfxBufferIndex]);

    gBillboardQueue[gBillboardQueueCount].texWidth = texWidth;
    gBillboardQueue[gBillboardQueueCount].texHeight = texHeight;
    gBillboardQueue[gBillboardQueueCount].texFormat = texFormat;
    gBillboardQueueCount++;
    gBillboardFlags = 0;
}

void billboardSetVertex(Vtx *vtx, s16 x, s16 z, s16 s, s16 t) {
    vtx->v.ob[0] = x;
    vtx->v.ob[1] = 0;
    vtx->v.ob[2] = z;
    vtx->v.tc[0] = s << 5;
    vtx->v.tc[1] = t << 5;
}

Gfx *billboardRenderQueued(Gfx *gdl, s16 layer) {
    s32 i;
    u8 *prevTex;
    s32 blendMode;
    s32 found;
    u8 *curTex;

    i = 0;
    prevTex = NULL;
    blendMode = 1;
    found = 0;
    while (i < gBillboardQueueCount && found == 0) {
        if (layer == gBillboardQueue[i].layer) {
            found = 1;
        }
        i++;
    }
    if (found == 0) {
        return gdl;
    }

    gDPPipeSync(gdl++);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_L, 3, 29, 0x504DD8);
    gSPClearGeometryMode(gdl++, -1);
    gSPSetGeometryMode(gdl++, 0x200405);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_H, 20, 2, 0);
    gSPTexture(gdl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombine(gdl++, 0x119623, 0xFF2FFFFF);

    for (i = 0; i < gBillboardQueueCount; i++) {
        if (layer == gBillboardQueue[i].layer) {
            BillboardData *bb;

            gDPPipeSync(gdl++);
            bb = &gBillboardQueue[i * 1]; // FAKE: no-op index multiply keeps this address from being CSEd with the loop IV
            if (blendMode != 0 && (gBillboardQueue[i].renderFlags & 1)) {
                gSPSetOtherMode(gdl++, G_SETOTHERMODE_L, 3, 29, 0x504240);
                blendMode = 0;
            }
            if (blendMode == 0 && !(gBillboardQueue[i].renderFlags & 1)) {
                gSPSetOtherMode(gdl++, G_SETOTHERMODE_L, 3, 29, 0x504DD8);
                blendMode = 1;
            }
            gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, gBillboardQueue[i].alpha);
            curTex = gBillboardCache[gBillboardQueue[i].cacheIndex].texture;
            if (curTex != prevTex) {
                prevTex = curTex;
                switch (gBillboardQueue[i].texFormat) {
                case 0:
                    gDPLoadTextureBlock_4b(
                        gdl++,
                        curTex + 0x80000000,
                        G_IM_FMT_IA,
                        gBillboardQueue[i].texWidth,
                        gBillboardQueue[i].texHeight,
                        0,
                        G_TX_CLAMP,
                        G_TX_CLAMP,
                        0,
                        0,
                        0,
                        0
                    );
                    break;
                case 1:
                    gDPLoadTextureBlock(
                        gdl++,
                        (u8 *)gBillboardCache[gBillboardQueue[i].cacheIndex].texture + 0x80000000,
                        G_IM_FMT_IA,
                        G_IM_SIZ_8b,
                        gBillboardQueue[i].texWidth,
                        gBillboardQueue[i].texHeight,
                        0,
                        G_TX_CLAMP,
                        G_TX_CLAMP,
                        0,
                        0,
                        0,
                        0
                    );
                    break;
                }
            }
            gSPMatrix(gdl++, osVirtualToPhysical(&bb->matrices[gGfxBufferIndex]), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPVertex(gdl++, osVirtualToPhysical(&bb->verts[gGfxBufferIndex][0]), 4, 0);
            gSP2Triangles(gdl++, 0, 3, 1, 0, 0, 2, 3, 0);
            gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
        }
    }
    gDPPipeSync(gdl++);
    return gdl;
}


typedef struct MatrixCacheNode {
    f32 lightR;
    f32 lightG;
    f32 lightB;
    u32 lastUsedFrame;
    s32 allocSize;
    struct MatrixCacheNode *hashNext;
    struct MatrixCacheNode *hashPrev;
    struct MatrixCacheNode *listNext;
    struct MatrixCacheNode *listPrev;
    s16 cellId;
    s16 vtxCount;
    u8 subType;
    u8 lightCount;
    u8 pad2A[6];
    LightTrigger lights[1];
} MatrixCacheNode;

extern MatrixCacheNode *gMatrixCacheBuckets[100];
extern MatrixCacheNode *gMatrixCacheHead;
extern MatrixCacheNode *gMatrixCacheTail;
extern u32 gMatrixCacheBytes;
extern u16 gMatrixCacheCount;
extern u32 gMatrixCacheLimit;

void matrixCacheInit(s32 limit) {
    s32 i;
    for (i = 0; i < 100; i++) {
        gMatrixCacheBuckets[i] = NULL;
    }
    gMatrixCacheHead = NULL;
    gMatrixCacheTail = NULL;
    gMatrixCacheBytes = 0;
    gMatrixCacheCount = 0;
    if (mapIsBonusOrSpecial()) {
        gMatrixCacheLimit = limit + 0x70000;
    } else {
        gMatrixCacheLimit = limit;
    }
}


s32 mapIsBonusOrSpecial(void) {
    if ((gCurrentMap == 6) || (gCurrentMap == 8) || (gCurrentMap == 0x37) || (gCurrentMap == 0x53) || (gCurrentMap == 0x6A) || (gCurrentMap == 0xC4) || (gCurrentMap == 0xC5)) {
        return 0;
    }
    return 1;
}

extern s16 D_807F9058;
extern s16 D_807F905A;

void matrixCacheResetStats(void) {
    D_807F9058 = 0;
    D_807F905A = 0;
}

extern f32 *gChunkLightR;
extern f32 *gChunkLightG;
extern f32 *gChunkLightB;
extern LightTrigger gLightCandidates[];

#define DIFF(a, b) (((b) < (a)) ? ((a) - (b)) : -((a) - (b)))

void *matrixCacheLookup(s32 lightCount, s32 chunkIndex, s16 cellId, u8 subType) {
    MatrixCacheNode *node;
    s32 i;
    s32 j;
    u8 mismatch;
    LightTrigger *cached;
    LightTrigger *cand;

    D_807F9058++;
    node = gMatrixCacheBuckets[matrixCacheHash(lightCount, cellId, subType)];
    while (node != NULL) {
        if (lightCount == node->lightCount && cellId == node->cellId && node->subType == subType) {
            if (node->lightR == gChunkLightR[chunkIndex] && node->lightG == gChunkLightG[chunkIndex] && node->lightB == gChunkLightB[chunkIndex]) {
                i = 0;
                mismatch = 0;
                for (; !mismatch && i < lightCount; i++) {
                    mismatch = 1;
                    for (j = 0; mismatch && j < lightCount; j++) {
                        cand = &gLightCandidates[j];
                        cached = &node->lights[i];
                        if (cand->type == 1) {
                            if (cached->x == cand->x && cached->y == cand->y && cached->z == cand->z &&
                                DIFF(cand->dirX, cached->dirX) < 0.05 &&
                                DIFF(cand->dirY, cached->dirY) < 0.05 &&
                                DIFF(cand->dirZ, cached->dirZ) < 0.05 &&
                                DIFF(cand->r, cached->r) < 0.05 &&
                                DIFF(cand->g, cached->g) < 0.05 &&
                                DIFF(cand->b, cached->b) < 0.05 &&
                                cached->cosOuter == cand->cosOuter && cached->cosInner == cand->cosInner) {
                                mismatch = 0;
                            }
                        } else if (cached->x == cand->x && cached->y == cand->y && cached->z == cand->z &&
                                   DIFF(cand->r, cached->r) < 0.05 &&
                                   DIFF(cand->g, cached->g) < 0.05 &&
                                   DIFF(cand->b, cached->b) < 0.05 &&
                                   cached->invFalloffLength == cand->invFalloffLength) {
                            mismatch = 0;
                        }
                    }
                }
                if (!mismatch) {
                    LightTrigger *lights = node->lights;
                    node->lastUsedFrame = gFrameCounter;
                    D_807F905A++;
                    if (node->listPrev != NULL) {
                        if (node->listNext == NULL) {
                            gMatrixCacheTail = node->listPrev;
                        }
                        node->listPrev->listNext = node->listNext;
                        if (node->listNext != NULL) {
                            node->listNext->listPrev = node->listPrev;
                        }
                        gMatrixCacheHead->listPrev = node;
                        node->listPrev = NULL;
                        node->listNext = gMatrixCacheHead;
                        gMatrixCacheHead = node;
                    }
                    node = NULL; // FAKE: redefining node stops uopt forwarding node->lights into the return, keeping it in a0
                    return &lights[lightCount];
                }
            }
        }
        node = node->hashNext;
    }
    return NULL;
}

void *matrixCacheInsert(s32 lightCount, s32 chunkIndex, s16 cellId, u8 subType, s32 vtxCount, u8 insertAtTail) {
    LightTrigger *lights;
    s32 allocSize;
    s32 pad;
    MatrixCacheNode *node;
    MatrixCacheNode **bucket;
    MatrixCacheNode *head;

    allocSize = lightCount * sizeof(LightTrigger) + vtxCount * sizeof(Vtx) + 0x30;
    node = heapAlloc(allocSize);

    bucket = &gMatrixCacheBuckets[matrixCacheHash(lightCount, cellId, subType)];
    head = *bucket;
    *bucket = node;
    node->hashNext = head;
    if (head != NULL) {
        head->hashPrev = node;
    }
    node->hashPrev = NULL;

    lights = node->lights;
    node->lightR = gChunkLightR[chunkIndex];
    node->lightG = gChunkLightG[chunkIndex];
    node->lightB = gChunkLightB[chunkIndex];
    node->cellId = cellId;
    node->lightCount = lightCount;
    node->subType = subType;
    memcpy(lights, gLightCandidates, lightCount * sizeof(LightTrigger));
    node->lastUsedFrame = gFrameCounter;
    node->vtxCount = vtxCount;
    gMatrixCacheBytes += allocSize;
    gMatrixCacheCount++;
    node->allocSize = allocSize;

    if (insertAtTail == 0) {
        node->listNext = gMatrixCacheHead;
        if (gMatrixCacheHead != NULL) {
            gMatrixCacheHead->listPrev = node;
        }
        node->listPrev = NULL;
        gMatrixCacheHead = node;
        if (gMatrixCacheTail == NULL) {
            gMatrixCacheTail = node;
        }
    } else {
        node->listPrev = gMatrixCacheTail;
        if (gMatrixCacheTail != NULL) {
            gMatrixCacheTail->listNext = node;
        }
        node->listNext = NULL;
        gMatrixCacheTail = node;
        if (gMatrixCacheHead == NULL) {
            gMatrixCacheHead = node;
        }
    }

    return &lights[lightCount];
}

s32 matrixCacheEvict(u8 checkLimit, s16 minAge) {
    s32 pad[5];
    u8 evictedAny;
    MatrixCacheNode *node;
    MatrixCacheNode *next;
    MatrixCacheNode **bucket;

    node = gMatrixCacheTail;
    evictedAny = 0;
    if (checkLimit) {
        minAge = 1;
    }

    while (1) {
        if (checkLimit && gMatrixCacheBytes <= gMatrixCacheLimit) {
            break;
        }
        if (node == NULL) {
            break;
        }
        next = node->listPrev;
        if ((!checkLimit && gMatrixCacheBytes > gMatrixCacheLimit) || minAge < (gFrameCounter - node->lastUsedFrame)) {
            if (node == gMatrixCacheTail) {
                gMatrixCacheTail = node->listPrev;
            }
            if (node == gMatrixCacheHead) {
                gMatrixCacheHead = node->listNext;
            }
            if (node->listNext != NULL) {
                node->listNext->listPrev = node->listPrev;
            }
            if (node->listPrev != NULL) {
                node->listPrev->listNext = node->listNext;
            }
            gMatrixCacheBytes -= node->allocSize;
            gMatrixCacheCount--;
            bucket = &gMatrixCacheBuckets[matrixCacheHash(node->lightCount, node->cellId, node->subType)];
            if (node == *bucket) {
                *bucket = node->hashNext;
                if (node->hashNext != NULL) {
                    node->hashNext->hashPrev = NULL;
                }
            } else {
                if (node->hashNext != NULL) {
                    node->hashNext->hashPrev = node->hashPrev;
                }
                if (node->hashPrev != NULL) {
                    node->hashPrev->hashNext = node->hashNext;
                }
            }
            if ((gFrameCounter - node->lastUsedFrame) >= 2) {
                heapFree(node);
                evictedAny = 1;
            } else {
                heapFreeDeferred(node);
            }
        }
        node = next;
    }
    return evictedAny;
}


s32 matrixCacheDecayLimit(void) {
    gMatrixCacheLimit = (gMatrixCacheLimit * 3) >> 2;
    if (gMatrixCacheLimit < 0x10000) {
        return 0;
    }
    return matrixCacheEvict(1, 0);
}

s32 matrixCacheHash(s32 lightCount, s16 cellId, u8 subType) {
    return (cellId * 16 + lightCount * 4 + subType) % 100;
}

extern u32 D_807F9068;

void matrixCacheSetDefaultLimit(void) {
    if (gMatrixCacheLimit != 0x9C40) {
        D_807F9068 = gMatrixCacheLimit;
    }
    gMatrixCacheLimit = 0x9C40;
}

void matrixCacheRestoreLimit(void) {
    gMatrixCacheLimit = D_807F9068;
}
