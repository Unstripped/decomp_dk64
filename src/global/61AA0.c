#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_assetLoad // FAKE: callee prototype steer
#include "proto/global/15050.h"
#include "proto/global/61AA0.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"


extern u8 gSegment6Override;

void renderSetSegment6Override(u8 segment) {
    gSegment6Override = segment;
}

extern Gfx D_80748310[6][2];

void renderReplaceSegment6Commands(Gfx *start, Gfx *end) {
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

    dist = sqrtf(R2A_SQ(x - gPlayerSlots[gCurrentPlayerIndex].unk21C) + R2A_SQ(y - gPlayerSlots[gCurrentPlayerIndex].unk220) + R2A_SQ(z - gPlayerSlots[gCurrentPlayerIndex].unk224));
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
    *outAlpha = (s32)(((dist - fadeStart) / (fadeEnd - fadeStart)) * 255.0f);
    if (*outAlpha >= 0x100) {
        *outAlpha = 0xFF;
    }
    *outAlpha = 0xFF - *outAlpha;
}

extern f32 D_807F6940;

f32 renderAdjustActorDistance(s16 actorType, f32 dist) {
    if ((actorType == 0xB2) || (actorType == 0x253)) {
        dist = (f64)dist + (600.0 - (f64)dist) * (f64)D_807F6940;
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
    if ((f64)gPlayerSlots[gCurrentPlayerIndex].fov == 45.0) {
        return dist;
    }
    return (dist / D_807F5FDC) * D_807F5FE0;
}

typedef struct {
    s32 lastUsedFrame;
    s16 assetId;
    s16 unk6;
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
extern s32 gFrameCounter;

void billboardCacheEvictStale(void) {
    s32 i;

    gBillboardQueueCount = 0;
    for (i = 0; i < 4; i++) {
        if (gBillboardCache[i].lastUsedFrame != -1 && (u32)(gFrameCounter - gBillboardCache[i].lastUsedFrame) >= 21) {
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

void *assetLoad(s32, s32, s32, s32); // FAKE: callee prototype steer

void billboardSubmit(Actor *actor, s16 assetId, s16 texWidth, s16 texHeight, s16 halfWidth, s16 halfHeight, u8 texFormat, s16 fadeDistance, u8 flags, s16 rotY, f32 xRatio) {
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
        found = FALSE; // FAKE: redundant reset (found is already FALSE) steers loop-2 codegen
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
    gBillboardQueue[gBillboardQueueCount].alpha = flags;
    if (actor->renderFlags & 0x40) {
        gBillboardFlags |= 1;
    }
    gBillboardQueue[gBillboardQueueCount].renderFlags = gBillboardFlags;
    gBillboardQueue[gBillboardQueueCount].layer = actor->chunkIndex;

    billboardSetVertex(&gBillboardQueue[gBillboardQueueCount].verts[gGfxBufferIndex][0], (s16)-((f32)halfWidth * xRatio), -halfHeight, 0, 0);
    billboardSetVertex(&gBillboardQueue[gBillboardQueueCount].verts[gGfxBufferIndex][1], halfWidth, -halfHeight, texWidth - 1, 0);
    billboardSetVertex(&gBillboardQueue[gBillboardQueueCount].verts[gGfxBufferIndex][2], (s16)-((f32)halfWidth * xRatio), halfHeight, 0, texHeight - 1);
    billboardSetVertex(&gBillboardQueue[gBillboardQueueCount].verts[gGfxBufferIndex][3], halfWidth, halfHeight, texWidth - 1, texHeight - 1);

    groundY = actor->floorY;
    if ((gBillboardFlags & 2) && (actor->contactFlags & 2) && (actor->waterY <= actor->y)) {
        f32 diff1 = (actor->y > actor->waterY) ? (actor->y - actor->waterY) : -(actor->y - actor->waterY);
        f32 diff2 = (actor->y > actor->floorY) ? (actor->y - actor->floorY) : -(actor->y - actor->floorY);
        if (diff1 < diff2) {
            groundY = actor->waterY;
        }
    }
    scale = 1.0 - (f64)((actor->y - groundY) / (f32)fadeDistance);
    if (scale < 0.0) {
        scale = 0.0f;
    }
    guScaleF(mtx1, scale, scale, scale);

    guRotateF(mtx2, (f32)((rotY * 360) / 4095), 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx1, mtx2, mtx1);
    if (actor->flags & 2) {
        if (actor->floorTiltPitch < 1000) {
            guRotateF(mtx2, -((f64)actor->floorTiltYaw / 4095.0 * 360.0), 0.0f, 1.0f, 0.0f);
            guMtxCatF(mtx1, mtx2, mtx1);
        }
        guRotateF(mtx2, 90.0 - (f64)actor->floorTiltPitch / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
        guMtxCatF(mtx1, mtx2, mtx1);
        if (actor->floorTiltPitch < 1000) {
            guRotateF(mtx2, (f64)actor->floorTiltYaw / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
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

    i = 0;
    if (gBillboardQueueCount > 0) {
        do {
            if (layer == gBillboardQueue[i].layer) {
                BillboardData *bb;

                gDPPipeSync(gdl++);
                bb = &gBillboardQueue[i * 1]; // FAKE: no-op index multiply keeps this address from being CSEd with the loop IV
                if (blendMode != 0) {
                    if (gBillboardQueue[i].renderFlags & 1) {
                        gSPSetOtherMode(gdl++, G_SETOTHERMODE_L, 3, 29, 0x504240);
                        blendMode = 0;
                    }
                }
                if (blendMode == 0) {
                    if (!(gBillboardQueue[i].renderFlags & 1)) {
                        gSPSetOtherMode(gdl++, G_SETOTHERMODE_L, 3, 29, 0x504DD8);
                        blendMode = 1;
                    }
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
            i++;
        } while (i < gBillboardQueueCount);
    }
    gDPPipeSync(gdl++);
    return gdl;
}


typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    u8 unk3E;
    u8 pad3F;
} MatrixCacheSub;

typedef struct MatrixCacheNode {
    f32 camX;
    f32 camY;
    f32 camZ;
    s32 lastUsedFrame;
    s32 allocSize;
    struct MatrixCacheNode *hash_next;
    struct MatrixCacheNode *hash_prev;
    struct MatrixCacheNode *list_next;
    struct MatrixCacheNode *list_prev;
    s16 modelId;
    s16 matrixCount;
    u8 subType;
    u8 count;
    u8 pad2A[6];
    MatrixCacheSub sub[1];
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

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern MatrixCacheSub D_807F78C0[];

#define DIFF(a, b) (((b) < (a)) ? ((a) - (b)) : -((a) - (b)))

void *matrixCacheLookup(s32 count, s32 camIndex, s16 modelId, u8 subType) {
    MatrixCacheNode *node;
    s32 i;
    s32 j;
    u8 mismatch;
    MatrixCacheSub *a;
    MatrixCacheSub *b;

    D_807F9058++;
    node = gMatrixCacheBuckets[matrixCacheHash(count, modelId, subType)];
    while (node != NULL) {
        if (count == node->count && modelId == node->modelId && node->subType == subType) {
            if (node->camX == D_8076A0B4[camIndex] && node->camY == D_8076A0B8[camIndex]) {
                if (node->camZ == D_8076A0BC[camIndex]) {
                    i = 0;
                    mismatch = 0;
                    for (; !mismatch && i < count; i++) {
                        mismatch = 1;
                        for (j = 0; mismatch && j < count; j++) {
                            b = &D_807F78C0[j];
                            a = &node->sub[i];
                            if (b->unk3E == 1) {
                                if (a->unk38 == b->unk38 && a->unk3A == b->unk3A && a->unk3C == b->unk3C &&
                                    (double)DIFF(b->unkC, a->unkC) < 0.05 &&
                                    (double)DIFF(b->unk10, a->unk10) < 0.05 &&
                                    (double)DIFF(b->unk14, a->unk14) < 0.05 &&
                                    (double)DIFF(b->unk2C, a->unk2C) < 0.05 &&
                                    (double)DIFF(b->unk30, a->unk30) < 0.05 &&
                                    (double)DIFF(b->unk34, a->unk34) < 0.05 &&
                                    a->unk0 == b->unk0 && a->unk4 == b->unk4) {
                                    mismatch = 0;
                                }
                            } else if (a->unk38 == b->unk38 && a->unk3A == b->unk3A && a->unk3C == b->unk3C &&
                                       (double)DIFF(b->unk2C, a->unk2C) < 0.05 &&
                                       (double)DIFF(b->unk30, a->unk30) < 0.05 &&
                                       (double)DIFF(b->unk34, a->unk34) < 0.05 &&
                                       a->unk1C == b->unk1C) {
                                mismatch = 0;
                            }
                        }
                    }
                    if (!mismatch) {
                        MatrixCacheSub *sub = node->sub;
                        node->lastUsedFrame = gFrameCounter;
                        D_807F905A++;
                        if (node->list_prev != NULL) {
                            if (node->list_next == NULL) {
                                gMatrixCacheTail = node->list_prev;
                            }
                            node->list_prev->list_next = node->list_next;
                            if (node->list_next != NULL) {
                                node->list_next->list_prev = node->list_prev;
                            }
                            gMatrixCacheHead->list_prev = node;
                            node->list_prev = NULL;
                            node->list_next = gMatrixCacheHead;
                            gMatrixCacheHead = node;
                        }
                        node = NULL; // FAKE: redefining node stops uopt forwarding node->sub into the return, keeping it in a0
                        return &sub[count];
                    }
                }
            }
        }
        node = node->hash_next;
    }
    return 0;
}

void *matrixCacheInsert(s32 count, s32 camIndex, s16 modelId, u8 subType, s32 matrixCount, u8 insertAtTail) {
    MatrixCacheSub *dest;
    s32 allocSize;
    s32 pad;
    MatrixCacheNode *node;
    MatrixCacheNode **bucket;
    MatrixCacheNode *head;

    allocSize = count * sizeof(MatrixCacheSub) + (matrixCount * 0x10) + 0x30;
    node = heapAlloc(allocSize);

    bucket = &gMatrixCacheBuckets[matrixCacheHash(count, modelId, subType)];
    head = *bucket;
    *bucket = node;
    node->hash_next = head;
    if (head != NULL) {
        head->hash_prev = node;
    }
    node->hash_prev = NULL;

    dest = node->sub;
    node->camX = D_8076A0B4[camIndex];
    node->camY = D_8076A0B8[camIndex];
    node->camZ = D_8076A0BC[camIndex];
    node->modelId = modelId;
    node->count = count;
    node->subType = subType;
    memcpy(dest, D_807F78C0, count * sizeof(MatrixCacheSub));
    node->lastUsedFrame = gFrameCounter;
    node->matrixCount = matrixCount;
    gMatrixCacheBytes += allocSize;
    gMatrixCacheCount++;
    node->allocSize = allocSize;

    if (insertAtTail == 0) {
        node->list_next = gMatrixCacheHead;
        if (gMatrixCacheHead != NULL) {
            gMatrixCacheHead->list_prev = node;
        }
        node->list_prev = NULL;
        gMatrixCacheHead = node;
        if (gMatrixCacheTail == NULL) {
            gMatrixCacheTail = node;
        }
    } else {
        node->list_prev = gMatrixCacheTail;
        if (gMatrixCacheTail != NULL) {
            gMatrixCacheTail->list_next = node;
        }
        node->list_next = NULL;
        gMatrixCacheTail = node;
        if (gMatrixCacheHead == NULL) {
            gMatrixCacheHead = node;
        }
    }

    return &dest[count];
}

s32 matrixCacheEvict(u8 checkLimit, s16 minAge) {
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 pad4;
    u8 evictedAny;
    MatrixCacheNode *node;
    MatrixCacheNode *next;
    MatrixCacheNode **bucket;
    u32 cond;

    cond = checkLimit; // FAKE: u32 copy of the u8 parameter steers the compares' register
    node = gMatrixCacheTail;
    evictedAny = 0;
    if (cond != 0) {
        minAge = 1;
    }

    while (1) {
        if (cond != 0) {
            if (!(gMatrixCacheLimit < gMatrixCacheBytes)) {
                break;
            }
        }
        if (node == NULL) {
            break;
        }
        next = node->list_prev;
        if ((cond == 0 && gMatrixCacheLimit < gMatrixCacheBytes) || (u32)minAge < (u32)(gFrameCounter - node->lastUsedFrame)) {
            if (node == gMatrixCacheTail) {
                gMatrixCacheTail = node->list_prev;
            }
            if (node == gMatrixCacheHead) {
                gMatrixCacheHead = node->list_next;
            }
            if (node->list_next != NULL) {
                node->list_next->list_prev = node->list_prev;
            }
            if (node->list_prev != NULL) {
                node->list_prev->list_next = node->list_next;
            }
            gMatrixCacheBytes -= node->allocSize;
            gMatrixCacheCount--;
            bucket = &gMatrixCacheBuckets[matrixCacheHash(node->count, node->modelId, node->subType)];
            if (node == *bucket) {
                *bucket = node->hash_next;
                if (node->hash_next != NULL) {
                    node->hash_next->hash_prev = NULL;
                }
            } else {
                if (node->hash_next != NULL) {
                    node->hash_next->hash_prev = node->hash_prev;
                }
                if (node->hash_prev != NULL) {
                    node->hash_prev->hash_next = node->hash_next;
                }
            }
            if ((u32)(gFrameCounter - node->lastUsedFrame) >= 2) {
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

s32 matrixCacheHash(s32 count, s16 modelId, u8 subType) {
    return (modelId * 16 + count * 4 + subType) % 100;
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
