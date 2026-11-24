#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "model.h"
#include "cutscene.h"
#include "map.h"
#include "collision.h"
#include "heap.h"
#include "sched.h"
#include "proto/boot/30E0_gunzip.h"
#include "proto/global/15050_heap.h"
#include "proto/global/166A0_random.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2F550_map_render.h"
#include "proto/global/36880_model_slot.h"
#include "proto/global/5E020_hash_table.h"
#include "proto/global/6AD90_collision.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/79890_collision_hit.h"
#include "proto/global/7BBD0_actor_collision.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/FE40_asset_dma.h"

// This TU's .data (0x80748E40-0x80748E42 + 14-byte TU pad).
s16 sModelSlotExpireCursor = 0;

typedef struct BufferCacheEntry {
    /* 0x00 */ void *tris;
    /* 0x04 */ void *rawTris;
    /* 0x08 */ u32 lastUsedFrame;
    /* 0x0C */ s32 romAddr;
    /* 0x10 */ s32 size;
    /* 0x14 */ s32 triCount;
} BufferCacheEntry; // size = 0x18

typedef struct CollisionTri {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 y0;
    /* 0x04 */ s16 z0;
    /* 0x06 */ s16 x1;
    /* 0x08 */ s16 y1;
    /* 0x0A */ s16 z1;
    /* 0x0C */ s16 x2;
    /* 0x0E */ s16 y2;
    /* 0x10 */ s16 z2;
} CollisionTri; // size = 0x12

extern BufferCacheEntry *sStaticCollisionCells;
extern s32 sStaticCollisionCellCount;
extern Actor *sWallProbeActor;
extern s16 sWallProbeYaw;
extern u8 sWallProbeOk;
extern u8 sStaticCollisionResident;
extern u8 sWallProbeActive;



extern u8 gGfxBufferIndex;
extern ModelSlot *gModelSlots;



typedef struct CollisionAssetTri {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 y0;
    /* 0x04 */ s16 z0;
    /* 0x06 */ s16 x1;
    /* 0x08 */ s16 y1;
    /* 0x0A */ s16 z1;
    /* 0x0C */ s16 x2;
    /* 0x0E */ s16 y2;
    /* 0x10 */ s16 z2;
    /* 0x12 */ u8 flags;
    /* 0x13 */ u8 partId;
    /* 0x14 */ s8 bone;
} CollisionAssetTri;


void collisionBuildSlotBoxes(s32 slot, ModelAssetHeader *asset, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale) {
    s8 lastBone;
    ModelData *anim;
    s32 count;
    CollisionAssetTri *entry;
    CollisionBox *out;
    f32 slotMtx[4][4];
    f32 tmpMtx[4][4];
    f32 boneMtx[4][4];
    f32 boneWorldMtx[4][4];
    s32 i;
    DynamicBuffer *buf;
    u8 *animFrame;
    u8 *boneTable;

    lastBone = -1;
    buf = &gModelSlots[slot].boxBuffer;
    anim = gModelSlots[slot].anim;
    if (anim != NULL) {
        animFrame = anim->frames[gGfxBufferIndex];
    } else {
        animFrame = NULL;
    }
    boneTable = asset->bonesOff + (u8 *)asset;
    buf->scaledRadius = (s32)((f32)asset->collisionRadius * scale * 8.0f * 1.5);
    buf->scaledX = (s32)(x * 8.0f);
    buf->scaledY = (s32)(y * 8.0f);
    buf->scaledZ = (s32)(z * 8.0f);
    count = *(s32 *)(asset->boxesOff + (u8 *)asset);
    if (count != 0) {
        buf->flags |= 2;
        if (!(buf->flags & 1)) {
            buf->box_start = heapAlloc(count * 0x58);
        }
        entry = (CollisionAssetTri *)(asset->boxesOff + (u8 *)asset + 4);
        out = buf->box_start;
        guScaleF(slotMtx, scale, scale, scale);
        guRotateF(tmpMtx, rotX, 1.0f, 0.0f, 0.0f);
        guMtxCatF(slotMtx, tmpMtx, slotMtx);
        guRotateF(tmpMtx, rotY, 0.0f, 1.0f, 0.0f);
        guMtxCatF(slotMtx, tmpMtx, slotMtx);
        guRotateF(tmpMtx, rotZ, 0.0f, 0.0f, 1.0f);
        guMtxCatF(slotMtx, tmpMtx, slotMtx);
        guTranslateF(tmpMtx, x, y, z);
        guMtxCatF(slotMtx, tmpMtx, slotMtx);
        for (i = 0; i < count; i++) {
            if (entry->bone == -1) {
                if (collisionTransformTriangle(entry, out, slotMtx) != 0) {
                    out++;
                }
            } else {
                if (lastBone != entry->bone) {
                    modelBuildBoneChainMatrix((s32 *)(boneTable + (entry->bone << 5)), animFrame, boneMtx);
                    guMtxCatF(boneMtx, slotMtx, boneWorldMtx);
                    lastBone = entry->bone;
                }
                if (collisionTransformTriangle(entry, out, boneWorldMtx) != 0) {
                    out++;
                }
            }
            entry++;
        }
        buf->box_end = out;
    } else {
        buf->box_start = NULL;
        buf->box_end = NULL;
    }
    buf->flags |= 1;
    buf->timestamp = gFrameCounter;
}

void modelSlotBuildTransformMatrix(s16 slot, s8 bone, f32 (*outMtx)[4]) {
    f32 posX;
    f32 posY;
    f32 posZ;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    f32 scale;
    f32 yOffset;
    s32 pad;
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    u8 *animFrame;
    u8 *boneTable;
    ModelData *anim;
    ModelAssetHeader *asset;

    anim = gModelSlots[slot].anim;
    if (anim != NULL) {
        animFrame = anim->frames[gGfxBufferIndex];
    } else {
        animFrame = NULL;
    }
    asset = gModelSlots[slot].asset;
    boneTable = asset->bonesOff + (u8 *)asset;
    modelSlotGetTransformVectors(slot, &posX, &posY, &posZ, &rotX, &rotY, &rotZ, &scale, &yOffset, 0);
    guScaleF(mtx, scale, scale, scale);
    guRotateF(tmpMtx, rotX, 1.0f, 0.0f, 0.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guRotateF(tmpMtx, rotY, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guRotateF(tmpMtx, rotZ, 0.0f, 0.0, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guTranslateF(tmpMtx, posX, posY, posZ);
    if (bone != -1) {
        guMtxCatF(mtx, tmpMtx, mtx);
        modelBuildBoneChainMatrix((s32 *)((bone << 5) + boneTable), animFrame, outMtx);
        guMtxCatF(outMtx, mtx, outMtx);
        return;
    }
    guMtxCatF(mtx, tmpMtx, outMtx);
}

void modelBuildBoneChainMatrix(s32 *boneOffsets, u8 *base, f32 (*outMtx)[4]) {
    s32 i;
    Mtx mtx;

    i = 1;
    memcpy(&mtx, boneOffsets[0] + base, 0x40);
    if (boneOffsets[1] != -1) {
        do {
            guMtxCatL(&mtx, (Mtx *)(boneOffsets[i] + base), &mtx);
        } while (boneOffsets[++i] != -1);
    }
    guMtxL2F(outMtx, &mtx);
}

void collisionTransformNode(s32 slot, ModelAssetHeader *asset, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale) {
    collisionBuildSlotBoxes(slot, asset, x, y, z, rotX, rotY, rotZ, scale);
}

void dynamicBufferFree(DynamicBuffer *buf) {
    if (buf->box_start != NULL && (buf->flags & 1)) {
        heapFree(buf->box_start);
    }
    buf->flags &= ~1;
}

extern s32 gCurrentMap;
extern s32 D_807FB530;


void collisionInitStaticCache(MapFileHeader *header) {
    u8 *data;
    void *compressed;
    u8 *gzOut;
    u8 *gzIn;
    s32 *cellHeader;
    u8 *next;
    u8 *cellStart;
    s32 relativeOffset;
    s32 i;
    s32 cellEnd;
    s32 pad1;
    s32 assetSize;
    s32 pad2;
    void *gzWork;

    cellEnd = 4;
    data = assetLoad(2, gCurrentMap, 1, 0);
    sStaticCollisionResident = 0;
    if (header->gzipFlags & 1) {
        compressed = data;
        data = heapAlloc(header->staticCollisionSize);
        gzWork = heapAlloc(0x2400);
        gzOut = data;
        gzIn = compressed;
        gunzip(&gzIn, &gzOut, gzWork);
        heapFree(gzWork);
        assetSetImmediateFree();
        assetFreeBuffer(compressed, 0x14C, 0xA);
        sStaticCollisionResident = 1;
    }
    assetSize = assetGetSize(2, gCurrentMap);
    D_807FB530 = *(s32 *)data;
    sStaticCollisionCells = heapAlloc(0x1518);
    cellHeader = (s32 *)(data + 4);
    sStaticCollisionCellCount = header->staticCellsX * header->staticCellsZ;
    for (i = 0; i < sStaticCollisionCellCount; i++) {
        cellStart = data + cellEnd + 4;
        cellEnd = *cellHeader;
        next = data + cellEnd;
        if (sStaticCollisionResident != 0) {
            sStaticCollisionCells[i].rawTris = cellStart;
        } else {
            sStaticCollisionCells[i].rawTris = NULL;
        }
        sStaticCollisionCells[i].tris = NULL;
        relativeOffset = cellStart - data;
        sStaticCollisionCells[i].romAddr = assetSize + relativeOffset;
        sStaticCollisionCells[i].size = (data + cellEnd) - cellStart;
        cellHeader = (s32 *)next;
        sStaticCollisionCells[i].lastUsedFrame = 0;
        sStaticCollisionCells[i].triCount = (next - cellStart) / 24;
    }
    if (sStaticCollisionResident == 0) {
        assetSetImmediateFree();
        assetFreeBuffer(data, 0x17C, 0xA);
    }
}


typedef struct CollisionStaticTriIn {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 y0;
    /* 0x04 */ s16 z0;
    /* 0x06 */ s16 x1;
    /* 0x08 */ s16 y1;
    /* 0x0A */ s16 z1;
    /* 0x0C */ s16 x2;
    /* 0x0E */ s16 y2;
    /* 0x10 */ s16 z2;
    /* 0x12 */ s16 normalYaw;
    /* 0x14 */ u8 normalYawFlipped;
    /* 0x15 */ u8 boundaryCondition;
    /* 0x16 */ u8 flags;
} CollisionStaticTriIn;

typedef struct CollisionStaticTriOut {
    /* 0x00 */ s64 nx;
    /* 0x08 */ s64 ny;
    /* 0x10 */ s64 nz;
    /* 0x18 */ s64 d;
    /* 0x20 */ f32 len;
    /* 0x24 */ s16 minY;
    /* 0x26 */ s16 maxY;
} CollisionStaticTriOut;

void collisionLoadStaticCell(s32 cell) {
    u32 size;
    s32 pad;
    CollisionStaticTriOut *dst;
    CollisionStaticTriIn *src;
    s32 cnt;

    if (sStaticCollisionCells[cell].tris == NULL && cell < sStaticCollisionCellCount) {
        size = sStaticCollisionCells[cell].size;
        if (size != 0) {
            if (sStaticCollisionResident == 0) {
                sStaticCollisionCells[cell].rawTris = heapAlloc(size);
                dmaReadAssetDecompress(sStaticCollisionCells[cell].romAddr, sStaticCollisionCells[cell].rawTris, &size, 0, 0, 0, 0);
            }
            cnt = sStaticCollisionCells[cell].triCount;
            sStaticCollisionCells[cell].tris = heapAlloc(cnt * sizeof(CollisionStaticTriOut));
            src = sStaticCollisionCells[cell].rawTris;
            dst = sStaticCollisionCells[cell].tris;
            for (; cnt != 0; cnt--) {
                if (collisionBuildStaticTri(src, dst) != 0) {
                    dst++;
                }
                src++;
            }
        }
    }
    sStaticCollisionCells[cell].lastUsedFrame = gFrameCounter;
}

extern s32 gModelSlotCount;


void modelSlotExpireNextBuffers(void) {
    DynamicBuffer *buf;
    ModelTriBuffer *triBuf;

    if (gModelSlotCount != 0) {
        sModelSlotExpireCursor++;
        if (sModelSlotExpireCursor >= gModelSlotCount) {
            sModelSlotExpireCursor = 0;
        }
        buf = &gModelSlots[sModelSlotExpireCursor].boxBuffer;
        if ((buf->flags & 1) && ((gFrameCounter - buf->timestamp) >= 0x1F)) {
            dynamicBufferFree(buf);
        }
        triBuf = &gModelSlots[sModelSlotExpireCursor].triBuffer;
        if ((triBuf->flags & 1) && ((gFrameCounter - triBuf->timestamp) >= 0x1F)) {
            modelSlotTriBufferRelease(triBuf);
        }
    }
}

void collisionBufferCacheUpdate(void) {
    collisionPurgeExpiredBuffers();
    dynamicBufferPurgeExpired();
}

void collisionPurgeExpiredBuffers(void) {
    s32 i;

    for (i = 0; i < sStaticCollisionCellCount; i++) {
        if (sStaticCollisionCells[i].tris != NULL && (gFrameCounter - sStaticCollisionCells[i].lastUsedFrame) >= 0x15) {
            if (sStaticCollisionResident == 0) {
                heapFree(sStaticCollisionCells[i].rawTris);
                sStaticCollisionCells[i].rawTris = NULL;
            }
            heapFree(sStaticCollisionCells[i].tris);
            sStaticCollisionCells[i].tris = NULL;
        }
    }
}

s32 collisionTransformTriangle(CollisionAssetTri *tri, CollisionBox *out, f32 (*mtx)[4]) {
    u8 axisOut[4];
    s16 verts[10];
    f32 x0;
    f32 y0;
    f32 z0;
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;

    guMtxXFMF(mtx, (f32)tri->x0, (f32)tri->y0, (f32)tri->z0, &x0, &y0, &z0);
    verts[0] = (s32)x0;
    verts[1] = (s32)y0;
    verts[2] = (s32)z0;
    guMtxXFMF(mtx, (f32)tri->x1, (f32)tri->y1, (f32)tri->z1, &x1, &y1, &z1);
    verts[3] = (s32)x1;
    verts[4] = (s32)y1;
    verts[5] = (s32)z1;
    guMtxXFMF(mtx, (f32)tri->x2, (f32)tri->y2, (f32)tri->z2, &x2, &y2, &z2);
    verts[6] = (s32)x2;
    verts[7] = (s32)y2;
    verts[8] = (s32)z2;
    if (collisionIsTriangleDegenerate((CollisionTri *)verts) != 0) {
        return 0;
    }
    if (tri->flags & 1) {
        out->pushable = 1;
    } else {
        out->pushable = 0;
    }
    if (tri->flags & 2) {
        out->partId = tri->partId;
    } else {
        out->partId = 0;
    }
    if (tri->flags & 4) {
        out->damageSurface = 1;
    } else {
        out->damageSurface = 0;
    }
    if (tri->flags & 8) {
        out->boundaryCondition = 5;
    } else {
        out->boundaryCondition = 0xFF;
    }
    out->mtxIndex = tri->bone;
    out->x0 = (s32)(x0 * 8.0f);
    out->y0 = (s32)(y0 * 8.0f);
    out->z0 = (s32)(z0 * 8.0f);
    out->x1 = (s32)(x1 * 8.0f);
    out->y1 = (s32)(y1 * 8.0f);
    out->z1 = (s32)(z1 * 8.0f);
    out->x2 = (s32)(x2 * 8.0f);
    out->y2 = (s32)(y2 * 8.0f);
    out->z2 = (s32)(z2 * 8.0f);
    verts[9] = collisionTriangleNormalYaw(verts, axisOut);
    out->slopeClass = collisionTriangleSlopeClass(verts);
    out->normalYaw = verts[9];
    out->normalFlipped = axisOut[0];
    return collisionBuildPlane(out);
}

s32 collisionIsTriangleDegenerate(CollisionTri *tri) {
    s16 x2;
    s16 x1;
    s16 x0;

    x1 = tri->x1;
    x0 = tri->x0;
    if ((x1 == x0) && (tri->y0 == tri->y1) && (tri->z0 == tri->z1)) {
        return 1;
    }
    x2 = tri->x2;
    if ((x1 == x2) && (tri->y2 == tri->y1) && (tri->z2 == tri->z1)) {
        return 1;
    }
    if ((x2 == x0) && (tri->y0 == tri->y2) && (tri->z0 == tri->z2)) {
        return 1;
    }
    return 0;
}


s8 collisionTriangleSlopeClass(s16 *a) {
    f32 v2[3];
    f32 v1[3];
    f32 cross[3];
    f32 len;
    f32 angle;
    f32 temp;

    v2[0] = a[6] - a[0];
    v2[1] = a[7] - a[1];
    v2[2] = a[8] - a[2];
    v1[0] = a[3] - a[0];
    v1[1] = a[4] - a[1];
    v1[2] = a[5] - a[2];
    cross[0] = (v2[1] * v1[2]) - (v2[2] * v1[1]);
    cross[1] = (v2[2] * v1[0]) - (v2[0] * v1[2]);
    cross[2] = (v2[0] * v1[1]) - (v2[1] * v1[0]);

    len = sqrtf((cross[0] * cross[0]) + (cross[2] * cross[2]));
    if (((f64)len < 0.01) && ((f64)len > -0.01)) {
        angle = 1.57f;
    } else {
        if (0.0f < cross[1]) {
            temp = cross[1];
        } else {
            temp = -cross[1];
        }
        angle = mathAtan2(temp, len);
    }

    if ((f64)(f32)((f64)angle * 57.29577791868205) < 10.0) {
        return 1;
    }
    if ((f64)(f32)((f64)angle * 57.29577791868205) < 45.0) {
        return 2;
    }
    return 0;
}

s16 collisionTriangleNormalYaw(verts, outFlag)
s16 *verts;
u8 *outFlag;
{
    f32 edgeA[3];
    f32 edgeB[3];
    f32 normal[3];
    f32 unitNormal[3];
    f32 probe[4];
    f32 len;
    f32 absX;
    f32 absZ;
    f32 angle;
    f32 planeD;
    f32 dist;
    f32 nx;
    f32 ny;
    f32 nz;
    s16 yaw;

    edgeA[0] = verts[6] - verts[0];
    edgeA[1] = verts[7] - verts[1];
    edgeA[2] = verts[8] - verts[2];

    edgeB[0] = verts[3] - verts[0];
    edgeB[1] = verts[4] - verts[1];
    edgeB[2] = verts[5] - verts[2];

    normal[0] = edgeA[1] * edgeB[2] - edgeA[2] * edgeB[1];
    normal[1] = edgeA[2] * edgeB[0] - edgeA[0] * edgeB[2];
    normal[2] = edgeA[0] * edgeB[1] - edgeA[1] * edgeB[0];

    len = sqrtf(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    if ((f64)len < 0.01) {
        len = 0.01f;
    }
    len = 1.0f / len;

    unitNormal[0] = normal[0] * len;
    unitNormal[1] = normal[1] * len;
    unitNormal[2] = normal[2] * len;

    if (normal[0] >= 0.0f) {
        absX = normal[0];
    } else {
        absX = 0.0 - normal[0];
    }

    if (normal[2] >= 0.0f) {
        absZ = normal[2];
    } else {
        absZ = 0.0 - normal[2];
    }

    if ((f64)absZ < 0.01 && (f64)absZ > -0.01) {
        angle = 1.57f;
    } else {
        angle = mathAtan2(absX, absZ);
    }

    if (0.0 <= (f64)normal[0] && 0.0 <= (f64)normal[2]) {
        yaw = (s32)((f64)(f32)((f64)angle * 57.29577791868205) * 11.375);
    }
    if (0.0 <= (f64)normal[0] && (f64)normal[2] < 0.0) {
        yaw = (s32)((180.0 - (f64)(f32)((f64)angle * 57.29577791868205)) * 11.375);
    }
    if ((f64)normal[0] < 0.0 && (f64)normal[2] < 0.0) {
        yaw = (s32)(((f64)(f32)((f64)angle * 57.29577791868205) + 180.0) * 11.375);
    }
    if ((f64)normal[0] < 0.0 && 0.0 <= (f64)normal[2]) {
        yaw = (s32)((360.0 - (f64)(f32)((f64)angle * 57.29577791868205)) * 11.375);
    }

    unitNormal[0] *= 20.0f;
    unitNormal[1] *= 20.0f;
    unitNormal[2] *= 20.0f;
    probe[0] = verts[0] + unitNormal[0];
    probe[1] = verts[1] + unitNormal[1];
    probe[2] = verts[2] + unitNormal[2];
    edgeA[0] = verts[0] - verts[3];
    edgeA[1] = verts[1] - verts[4];
    edgeA[2] = verts[2] - verts[5];
    edgeB[0] = verts[0] - verts[6];
    edgeB[1] = verts[1] - verts[7];
    edgeB[2] = verts[2] - verts[8];
    nx = edgeA[1] * edgeB[2] - edgeA[2] * edgeB[1];
    ny = edgeA[2] * edgeB[0] - edgeA[0] * edgeB[2];
    nz = edgeA[0] * edgeB[1] - edgeA[1] * edgeB[0];
    planeD = -((nz * (f32)verts[5]) + ((ny * (f32)verts[4]) + (nx * verts[3])));
    dist = (nx * probe[0]) + (ny * probe[1]) + (nz * probe[2]) + planeD;

    if ((!(0.0 < (f64)dist) || !(0.0 < (f64)planeD)) && (!((f64)dist < 0.0) || !((f64)planeD < 0.0))) {
        yaw -= 0x800;
        if (yaw < 0) {
            yaw += 0xFFF;
        }
        *outFlag = 1;
    } else {
        *outFlag = 0;
    }

    return yaw;
}


s32 collisionBuildStaticTri(void *inData, void *outData) {
    CollisionBox work;
    CollisionStaticTriIn *in = inData;
    CollisionStaticTriOut *out = outData;
    s16 y1;
    s16 y;
    s16 y2;

    work.x0 = in->x0;
    work.y0 = in->y0;
    work.z0 = in->z0;
    work.x1 = in->x1;
    work.y1 = in->y1;
    work.z1 = in->z1;
    work.x2 = in->x2;
    work.y2 = in->y2;
    work.z2 = in->z2;

    work.x0 *= 8; work.y0 *= 8; work.z0 *= 8;
    work.x1 *= 8; work.y1 *= 8; work.z1 *= 8;
    work.x2 *= 8; work.y2 *= 8; work.z2 *= 8;

    work.normalYaw = in->normalYaw;
    work.normalFlipped = in->normalYawFlipped;
    work.pushable = 0;
    work.partId = 0;
    if (in->flags & 4) {
        work.damageSurface = 1;
    } else {
        work.damageSurface = 0;
    }
    work.boundaryCondition = in->boundaryCondition;
    work.slopeClass = 1;
    collisionBuildPlane(&work);

    out->nx = work.nx;
    out->ny = work.ny;
    out->nz = work.nz;
    out->d = work.d;
    out->len = work.len;

    y1 = in->y1;
    y = in->y0;
    if (y < y1) {
        out->minY = y;
    } else {
        out->minY = y1;
    }
    y = out->minY;
    y2 = in->y2;
    if (y < y2) {
        out->minY = y;
    } else {
        out->minY = y2;
    }
    if (y1 == 0) {} // FAKE: extends y1 so it interferes with y2 and takes $a0

    y1 = in->y1;
    y = in->y0;
    if (y1 < y) {
        out->maxY = y;
    } else {
        out->maxY = y1;
    }
    y2 = in->y2;
    y = out->maxY;
    if (y2 < y) {
        if (y2 == 0) {} // FAKE: extra use raises y2 priority so it takes $v0
        out->maxY = y;
    } else {
        out->maxY = y2;
    }

    return 1;
}

s32 collisionBuildPlane(CollisionBox *box) {
    s64 d1[3];
    s64 d2[3];
    s64 ax;
    s64 ay;
    s64 az;

    d1[0] = box->x0 - box->x1;
    d1[1] = box->y0 - box->y1;
    d1[2] = box->z0 - box->z1;
    d2[0] = box->x0 - box->x2;
    d2[1] = box->y0 - box->y2;
    d2[2] = box->z0 - box->z2;
    box->nx = d1[1] * d2[2] - d1[2] * d2[1];
    box->ny = d1[2] * d2[0] - d1[0] * d2[2];
    box->nz = d1[0] * d2[1] - d1[1] * d2[0];
    box->d = -(box->nx * box->x1 + box->ny * box->y1 + box->nz * box->z1);
    box->len = sqrtf((f32)(box->nx * box->nx + box->ny * box->ny + box->nz * box->nz));
    if (box->len == 0.0) {
        return 0;
    }
    if (box->nx >= 0) {
        ax = box->nx;
    } else {
        ax = 0 - box->nx;
    }
    if (box->ny >= 0) {
        ay = box->ny;
    } else {
        ay = 0 - box->ny;
    }
    if (box->nz >= 0) {
        az = box->nz;
    } else {
        az = 0 - box->nz;
    }
    if (az >= ax && az >= ay) {
        box->axis = 0;
    }
    if (ay >= ax && ay >= az) {
        box->axis = 1;
    }
    if (ax >= ay && ax >= az) {
        box->axis = 2;
    }
    return 1;
}

void actorSub140Free(ActorSub140 *sub) {
    void *temp;
    ModelNode *curr8C;
    ModelNode *next8C;
    ModelSubNode *curr90;
    ModelSubNode *next90;

    if (sub != NULL) {
        curr8C = sub->nodes;
        if (curr8C != NULL) {
            do {
                next8C = curr8C->next;
                heapFree(curr8C);
                curr8C = next8C;
            } while (next8C != NULL);
        }
        curr90 = sub->subNodes;
        if (curr90 != NULL) {
            do {
                next90 = curr90->next;
                heapFree(curr90);
                curr90 = next90;
            } while (next90 != NULL);
        }
        temp = sub->boxes;
        if (temp != NULL) {
            heapFree(temp);
        }
        temp = sub->triangles;
        if (temp != NULL) {
            heapFree(temp);
        }
        heapFree(sub);
    }
}

typedef struct ActorSub140Tri {
    /* 0x00 */ f32 x[9];
    /* 0x24 */ f32 out[9];
    /* 0x48 */ u32 boneOffset[3];
    /* 0x54 */ s16 id;
    /* 0x56 */ u8 enabled;
    /* 0x57 */ u8 pad57;
} ActorSub140Tri; // size = 0x58

typedef struct ActorSub140SrcTri {
    /* 0x00 */ f32 x[9];
    /* 0x24 */ s32 boneOffset;
    /* 0x28 */ s16 id;
    /* 0x2A */ u8 enabled;
    /* 0x2B */ u8 pad2B;
} ActorSub140SrcTri; // size = 0x2C

ActorSub140 *actorSub140CreateFromData(f32 x, f32 y, f32 z, f32 scale, f32 radius, f32 height, void *boxBounds, Mtx *mtx0, Mtx *mtx1, u8 *data) {
    ActorSub140 *sub140;
    ModelNode **link;
    ModelSubNode **subLink;
    s32 n;
    s32 i;
    s32 pad1;
    s32 pad[10];
    void *triBase;
    s32 pad50;
    ActorSub140SrcTri *srcTri;
    ActorSub140Tri *tri;
    s32 count;
    ModelNode *node;
    ModelSubNode *subnode;

    sub140 = actorSub140Alloc(x, y, z, scale, radius, height, boxBounds, mtx0, mtx1);
    if (data != NULL) {
        n = *(s32 *)data;
        data += 4;
        link = &sub140->nodes;
        i = 0;
        if (n > 0) {
            do {
                node = heapAlloc(sizeof(ModelNode));
                node->next = NULL;
                node->x = *(f32 *)data;
                node->y = *((f32 *)data + 1);
                node->z = *((f32 *)data + 2);
                node->scale = *((f32 *)data + 3);
                node->mtxOffset = *((s32 *)data + 4);
                node->active = 1;
                node->ignoredCollisionFlags = 0;
                node->collisionSkipFlags = 0;
                data += 0x14;
                *link = node;
                link = &node->next;
                i++;
            } while (i != n);
            i = 0;
        }

        n = *(s32 *)data;
        data += 4;
        if (n > 0) {
            subLink = &sub140->subNodes;
            do {
                subnode = heapAlloc(sizeof(ModelSubNode));
                subnode->next = NULL;
                subnode->x = *(f32 *)data;
                subnode->y = *((f32 *)data + 1);
                subnode->z = *((f32 *)data + 2);
                subnode->mtxOffset = *((s32 *)data + 3);
                data += 0x10;
                *subLink = subnode;
                subLink = &subnode->next;
                i++;
            } while (i != n);
            i = 0;
        }

        count = *(s32 *)data;
        data += 4;
        sub140->boxCount = count;
        if (count != 0) {
            srcTri = heapAlloc(count * sizeof(ActorSub140SrcTri));
            sub140->boxes = srcTri;
            sub140->box_start = heapAlloc(count * sizeof(ActorSub140Tri));
            sub140->box_end = sub140->box_start;
        }
        if (count > 0) {
            do {
                f32 *rec = (f32 *)data;
                s32 k = 0;
                s32 j = 0;
                f32 *dst = srcTri->x;
                f32 *src = (f32 *)data;
                do {
                    *dst++ = src[0];
                    j += 2; // FAKE: split increments raise j/k/src priority (v0/v1/a0/a1 roles)
                    j--;
                    k += 1;
                    k += 1;
                    k += 1;
                    src += 1;
                    src += 2;
                    dst[2] = src[-2];
                    dst[5] = src[-1];
                } while (j != 3);
                srcTri->id = *(s32 *)(rec + k);
                srcTri->boneOffset = *(s32 *)(rec + (k + 1));
                srcTri->enabled = 1;
                data += 0x2C;
                srcTri++;
            } while (++i != count);
            i = 0;
        }

        count = *(s32 *)data;
        data += 4;
        sub140->triangleCount = count;
        if (count != 0) {
            sub140->triangles = heapAlloc(count * sizeof(ActorSub140Tri));
            triBase = sub140->triangles;
        }
        if (count > 0) {
            tri = triBase;
            do {
                f32 *rec = (f32 *)data;
                s32 k = 0;
                s32 j = 0;
                f32 *dst = tri->x;
                f32 *src = (f32 *)data;
                do {
                    *dst++ = src[0];
                    j += 2; // FAKE: split increments raise j/k/src priority (v0/v1/a0/a1 roles)
                    j--;
                    k += 1;
                    k += 1;
                    k += 1;
                    src += 1;
                    src += 2;
                    dst[2] = src[-2];
                    dst[5] = src[-1];
                } while (j != 3);
                tri->id = *(s32 *)(rec + k);
                tri->boneOffset[0] = *(s32 *)(rec + (k + 1));
                tri->boneOffset[1] = *(s32 *)(rec + (k + 2));
                tri->boneOffset[2] = *(s32 *)(rec + (k + 3));
                tri->enabled = 1;
                data += 0x34;
                tri++;
            } while (++i != count);
        }
    }
    return sub140;
}

void actorSetNodeValue(Actor *actor, s32 index, u16 value) {
    ModelNode *node;

    node = actorGetModelNodeByIndex(actor, index);
    if (node != NULL) {
        node->ignoredCollisionFlags = value;
    }
}

void actorOrNodeFlags(Actor *actor, s32 index, u8 flags) {
    ModelNode *node;

    node = actorGetModelNodeByIndex(actor, index);
    if (node != NULL) {
        node->collisionSkipFlags |= flags;
    }
}

void actorClearNodeFlags(Actor *actor, s32 index, u8 flags) {
    ModelNode *node;

    node = actorGetModelNodeByIndex(actor, index);
    if (node != NULL) {
        node->collisionSkipFlags &= ~flags;
    }
}

void actorSetBoxEnableById(Actor *actor, s32 id, u8 value) {
    ActorSub140 *sub;
    ActorSub140SrcTri *ent;
    s32 i;

    sub = actor->collision;
    if (actor->collision != NULL) { // FAKE: second read of unk140 keeps the sub copy in $v0
        ent = sub->boxes;
        for (i = 0; i < sub->boxCount; i++) {
            if (id == ent[i].id) {
                ent[i].enabled = value;
            }
        }
    }
}

void actorSetTriangleEnableById(Actor *actor, s32 id, u8 enabled) {
    ActorSub140 *sub;
    ActorSub140Tri *ent;
    s32 i;

    sub = actor->collision;
    if (actor->collision != NULL) { // FAKE: second read of unk140 keeps the sub copy in $v0
        ent = sub->triangles;
        for (i = 0; i < sub->triangleCount; i++) {
            if (id == ent[i].id) {
                ent[i].enabled = enabled;
            }
        }
    }
}

ActorSub140 *actorSub140Alloc(f32 x, f32 y, f32 z, f32 scale, f32 radius, f32 height, void *boxBounds, Mtx *mtx0, Mtx *mtx1) {
    ActorSub140 *sub;

    sub = (ActorSub140 *)heapAlloc(sizeof(ActorSub140));
    sub->scaledX = (s32) (x * 8.0f);
    sub->scaledY = (s32) (y * 8.0f);
    sub->scaledZ = (s32) (z * 8.0f);
    sub->radius = radius;
    sub->height = height;
    sub->scaledRadius = (s32) (radius * scale * 8.0f);
    sub->scaledHeight = (s32) (height * scale * 8.0f);
    sub->modelMtxF = boxBounds;
    sub->nodeMtx[0] = mtx0;
    sub->nodeMtx[1] = mtx1;
    sub->spheresFrame = -1;
    sub->posFrame = -2;
    sub->subNodesFrame = -1;
    sub->mtxFrame = -1;
    sub->slotPushDist = 0;
    sub->hasSlotHit = 0;
    sub->hasPushTarget = 0;
    sub->nodes = NULL;
    sub->subNodes = NULL;
    sub->triangleCount = 0;
    sub->triangles = NULL;
    sub->boxCount = 0;
    sub->boxes = NULL;
    sub->box_start = 0;
    sub->box_end = 0;
    sub->unkAC = 0;
    return sub;
}



void actorAppendModelSubNode(Actor *actor, f32 x, f32 y, f32 z, s32 value) {
    f32 pad[3];
    ActorSub140 *sub;
    ModelSubNode *node;
    ModelSubNode **head;
    ModelSubNode *curr;

    sub = actor->collision;
    node = (ModelSubNode *)heapAlloc(sizeof(ModelSubNode));
    node->next = NULL;
    head = (ModelSubNode **)&sub->subNodes;
    node->x = x;
    node->y = y;
    node->z = z;
    node->mtxOffset = value;
    node->scaledX = 0;
    node->scaledY = 0;
    node->scaledZ = 0;
    curr = (ModelSubNode *)sub->subNodes;
    if (curr != NULL) {
        do {
            head = &curr->next;
            curr = curr->next;
        } while (curr != NULL);
    }
    *head = node;
}

void actorAppendModelNode(Actor *actor, f32 x, f32 y, f32 z, f32 scale, s32 mtxOffset) {
    f32 pad[3];
    ActorSub140 *sub;
    ModelNode *node;
    ModelNode **head;
    ModelNode *curr;

    sub = actor->collision;
    node = heapAlloc(sizeof(ModelNode));
    node->next = NULL;
    head = &sub->nodes;
    node->x = x;
    node->y = y;
    node->z = z;
    node->scale = scale;
    node->mtxOffset = mtxOffset;
    node->scaledX = 0;
    node->scaledY = 0;
    node->scaledZ = 0;
    node->scaledRadius = 0;
    node->active = 1;
    node->ignoredCollisionFlags = 0;
    node->collisionSkipFlags = 0;
    curr = sub->nodes;
    if (curr != NULL) {
        do {
            head = &curr->next;
            curr = curr->next;
        } while (curr != NULL);
    }
    *head = node;
}


void actorFreeModelNodeList(Actor *actor) {
    ActorSub140 *sub;
    ModelNode *node;
    ModelNode *next;

    sub = actor->collision;
    if (sub != NULL) {
        node = sub->nodes;
        if (node != NULL) {
            do {
                next = node->next;
                heapFree(node);
                node = next;
            } while (node != NULL);
        }
        sub->nodes = NULL;
    }
}

f32 actorGetOrSetNodeScale(Actor *actor, s32 index, f32 scale) {
    ActorSub140 *sub = actor->collision;
    ModelNode *node;

    index--;
    node = sub->nodes;
    while (index-- && node != NULL) {
        node = node->next;
    }
    if (node != NULL) {
        if (scale != -1.0f) {
            node->scale = scale;
        }
        return node->scale;
    }
    return -1.0f;
}

void actorSetNodeFlag(Actor *actor, s32 nodeIndex) {
    ModelNode *node = actorGetModelNodeByIndex(actor, nodeIndex);

    if (node != NULL) {
        node->active = 1;
    }
}

void actorClearNodeFlag(Actor *actor, s32 nodeIndex) {
    ModelNode *node = actorGetModelNodeByIndex(actor, nodeIndex);

    if (node != NULL) {
        node->active = 0;
    }
}

void actorClearAllNodeFlags(Actor *actor) {
    ActorSub140 *sub = actor->collision;
    ModelNode *node;

    if (sub != NULL) {
        node = sub->nodes;
        if (node != NULL) {
            do {
                node->active = 0;
                node = node->next;
            } while (node != NULL);
        }
    }
}

ModelNode *actorGetModelNodeByIndex(Actor *actor, s32 index) {
    ActorSub140 *sub;
    ModelNode *node;

    sub = actor->collision;
    index--;
    if (sub != NULL) {
        node = sub->nodes;
        while (index != 0 && node != NULL) {
            index--;
            node = node->next;
        }
        if (node != NULL) {
            return node;
        }
        return NULL;
    }
    return NULL;
}

ActorSub140 *actorSetCollisionRadius(Actor *actor, f32 radius) {
    ActorSub140 *sub = actor->collision;
    sub->radius = radius;
    return sub;
}

void actorSub140SetVectors(Actor *actor, f32 x, f32 y, f32 z, f32 scale) {
    ActorSub140 *sub = actor->collision;

    if (actor->renderFlags & 0x800) {
        scale = actor->collisionScaleOverride;
    }
    sub->scaledX = (s32)(x * 8.0f);
    sub->scaledY = (s32)(y * 8.0f);
    sub->scaledZ = (s32)(z * 8.0f);
    sub->scaledRadius = (s32)(sub->radius * scale * 8.0f);
    sub->scaledHeight = (s32)(sub->height * scale * 8.0f);
}

void actorUpdateModelMatrices(Actor *actor) {
    ActorSub140 *sub;

    sub = actor->collision;
    if (sub != NULL) {
        if (!(actor->flags & 0x80000000) || !(actor->flags & 0x10)) {
            actorSub140BuildBoxes(sub);
        }
        if (!(actor->renderFlags & 8) || !(actor->flags & 0x10)) {
            actorSub140TransformTriangles(actor->collision);
        }
    }
}

void actorSub140BuildBoxes(ActorSub140 *sub) {
    s32 pad[1];
    s32 i;
    ActorSub140SrcTri *ent;
    Mtx *mtx;
    u8 bufIdx;
    f32 boundsMtx[4][4];
    s32 k;
    s32 pad2[14];
    CollisionBox *box;
    f32 tri[9];

    if (sub->boxes != NULL) {
        if (gFrameCounter == sub->mtxFrame) {
            bufIdx = gGfxBufferIndex;
        } else {
            bufIdx = gGfxBufferIndex ^ 1;
        }
        mtx = sub->nodeMtx[bufIdx];
        ent = sub->boxes;
        box = sub->box_start;
        for (i = 0; i < sub->boxCount; i++) {
            for (k = 0; k < 3; k++) {
                if (ent->boneOffset == -1) {
                    memcpy(boundsMtx, sub->modelMtxF, sizeof(boundsMtx));
                    guMtxXFMF(boundsMtx, ent->x[k], ent->x[k + 3], ent->x[k + 6], &tri[k], &tri[k + 3], &tri[k + 6]);
                } else {
                    guMtxXFML(&mtx[(u32)ent->boneOffset >> 6], ent->x[k], ent->x[k + 3], ent->x[k + 6], &tri[k], &tri[k + 3], &tri[k + 6]);
                }
            }
            if (collisionBuildBoxFromMatrix(tri, box) != 0) {
                if (ent->enabled == 0) {
                    box->slopeClass = 0;
                }
                if (ent->boneOffset == -1) {
                    box->mtxIndex = -1;
                } else {
                    box->mtxIndex = (u32)ent->boneOffset >> 6;
                }
                box++;
            }
            ent++;
        }
        sub->box_end = box;
    }
}

s32 collisionBuildBoxFromMatrix(f32 *m, CollisionBox *box) {
    u8 axisOut[4];
    s16 yaw;
    s16 verts[9];

    verts[0] = m[0];
    verts[1] = m[3];
    verts[2] = m[6];
    verts[3] = m[1];
    verts[4] = m[4];
    verts[5] = m[7];
    verts[6] = m[2];
    verts[7] = m[5];
    verts[8] = m[8];

    if (collisionIsTriangleDegenerate((CollisionTri *)verts) != 0) {
        return 0;
    }

    box->x0 = (s32)(m[0] * 8.0f);
    box->y0 = (s32)(m[3] * 8.0f);
    box->z0 = (s32)(m[6] * 8.0f);
    box->x1 = (s32)(m[1] * 8.0f);
    box->y1 = (s32)(m[4] * 8.0f);
    box->z1 = (s32)(m[7] * 8.0f);
    box->x2 = (s32)(m[2] * 8.0f);
    box->y2 = (s32)(m[5] * 8.0f);
    box->z2 = (s32)(m[8] * 8.0f);

    yaw = collisionTriangleNormalYaw(verts, axisOut);
    box->slopeClass = collisionTriangleSlopeClass(verts);
    box->pushable = 0;
    box->partId = 0;
    box->damageSurface = 0;
    box->boundaryCondition = 0xFF;
    box->normalYaw = yaw;
    box->normalFlipped = axisOut[0];
    collisionBuildPlane(box);
    return 1;
}

void actorSub140TransformTriangles(ActorSub140 *sub) {
    ActorSub140Tri *first;
    s32 i;
    u8 bufIdx;
    ActorSub140Tri *curr;
    Mtx *mtx;
    f32 boundsMtx[4][4];
    s32 j;

    first = sub->triangles;
    if (first != NULL) {
        if (gFrameCounter == sub->mtxFrame) {
            bufIdx = gGfxBufferIndex;
        } else {
            bufIdx = gGfxBufferIndex ^ 1;
        }
        mtx = sub->nodeMtx[bufIdx];
        curr = first;
        for (i = 0; i < sub->triangleCount; i++) {
            for (j = 0; j < 3; j++) {
                if (curr->boneOffset[j] == -1) {
                    memcpy(boundsMtx, sub->modelMtxF, sizeof(boundsMtx));
                    guMtxXFMF(boundsMtx, curr->x[j], curr->x[j + 3], curr->x[j + 6], &curr->out[j], &curr->out[j + 3], &curr->out[j + 6]);
                } else {
                    guMtxXFML(&mtx[curr->boneOffset[j] >> 6], curr->x[j], curr->x[j + 3], curr->x[j + 6], &curr->out[j], &curr->out[j + 3], &curr->out[j + 6]);
                }
            }
            curr++;
        }
    }
}

u8 actorSetTargetAngleAndCheck(Actor *actor, s16 angle) {
    s16 arcMin;
    s16 arcMax;
    u8 actorHit;

    sWallProbeYaw = angle;
    sWallProbeActor = actor;
    sWallProbeOk = 1;
    sWallProbeActive = 1;
    actorCheckTargetAngle(actor, &arcMin, &arcMax, &actorHit);
    return sWallProbeOk;
}

u8 actorClearTargetAngle(Actor *actor, s16 *arcMin, s16 *arcMax, u8 *hit) {
    sWallProbeActive = 0;
    return actorCheckTargetAngle(actor, arcMin, arcMax, hit);
}

extern PlayerStruct *gPlayerSlots;
extern u8 gCollisionHit;
extern u8 sDamageSurfaceContact;
extern u8 sBoundaryTwoSided;
extern u8 gCollisionArcWidened;

void func_80672E90(s32, s32, s32);

u8 actorCheckTargetAngle(Actor *actor, s16 *arcMin, s16 *arcMax, u8 *actorHit) {
    s32 pad;
    u8 boundsHit;
    u8 slotHit;
    ActorSub140 *sub;

    boundsHit = 0;
    slotHit = 0;
    sub = actor->collision;
    if (actor->flags & 0x10000) {
        *arcMin = 0;
        *arcMax = 0xFFF;
    }
    if ((sub == NULL) || !(actor->flags & 0x10)) {
        *actorHit = 0;
        return 0;
    }
    func_80672E90(sub->scaledX, sub->scaledY, sub->scaledZ);
    actorSetCameraBoundaryMode(actor->actorType);
    sDamageSurfaceContact = 0;
    gCollisionHit = 0;
    sBoundaryTwoSided = 0;
    gCollisionArcWidened = 0;
    if (actor->collisionMode & 0x20) {
        actorCollisionCheckNodeSpheres(actor);
    }
    if (actor->collisionMode & 8) {
        boundsHit = actorCheckTargetAngleBounds(actor, arcMin, arcMax);
        slotHit = actorCollideModelSlots(actor, arcMin, arcMax);
        *actorHit = actorCheckCollisionsAgainstActiveActors(actor, arcMin, arcMax);
    } else {
        *actorHit = 0;
    }
    actorQueueCollisionCallbacks(actor);
    actor->collisionHit = gCollisionHit;
    if (gCollisionArcWidened != 0) {
        actor->renderFlags |= 0x100;
    } else {
        actor->renderFlags &= ~0x100;
    }
    return (boundsHit != 0) || (slotHit != 0);
}

void actorQueueCollisionCallbacks(Actor *actor) {
    if (sDamageSurfaceContact) {
        if (actor->collisionFlags & 1) {
            PlayerState *player = actor->customState;
            if (player->surfaceTimer == 0) {
                if (sDamageSurfaceContact & 1) {
                    actorQueueDelayedCallback(actor, 0, 8, 0, 0, 0, 1);
                }
                if (sDamageSurfaceContact & 2) {
                    actorQueueDelayedCallback(actor, 0, 8, 0, 0, 0, 1);
                }
            }
        }
    }
}

s32 collisionSpheresOverlap(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80673708(s32, s32, s32, s32, CollisionBox *, CollisionBox *, s16 *, s16 *);
extern u8 sPushToFullThreshold;
extern u8 gCollisionDeferredPush;
extern u8 gCollisionDeferredHit;
extern u8 gCollisionResolvePass;
extern u8 sCollisionHitPart;
extern u8 gCollisionNearestFound;

u8 actorCollideModelSlots(Actor *actor, s16 *arcMin, s16 *arcMax) {
    u8 result;
    ModelNode *node;
    DynamicBuffer *buf;
    CsState *hit;
    s32 i;
    ActorSub140 *sub;
    u8 savedFlags;
    u8 ret;
    u8 flag;

    result = 0;
    sub = actor->collision;
    sub->hasSlotHit = 0;
    sPushToFullThreshold = 0;
    for (i = 0; i < gModelSlotCount; i++) {
        buf = &gModelSlots[i].boxBuffer;
        if (buf->flags & 2) {
            if (collisionSpheresOverlap(sub->scaledX, sub->scaledY, sub->scaledZ, sub->scaledRadius, buf->scaledX, buf->scaledY, buf->scaledZ, buf->scaledRadius) != 0) {
                if (!(buf->flags & 1)) {
                    collisionTransformNode(i, gModelSlots[i].asset, gModelSlots[i].x, gModelSlots[i].y, gModelSlots[i].z, gModelSlots[i].rotX, gModelSlots[i].rotY, gModelSlots[i].rotZ, gModelSlots[i].scale);
                } else {
                    buf->timestamp = gFrameCounter;
                }
                if (!(actor->collisionFlags & 1) || playerSlotMatchesSizeMask(gModelSlots[i].asset->flags, ((PlayerState *)actor->customState)->playerIndex) == 0) {
                    actorUpdateCollisionSpheres(actor, 0);
                    flag = 1;
                    node = sub->nodes;
                    gCollisionDeferredPush = 0;
                    savedFlags = sDamageSurfaceContact;
                    hit = gModelSlots[i].csState;
                    if (hit != NULL) {
                        if (hit->deferredPush != 0) {
                            gCollisionDeferredPush = 1;
                            gCollisionResolvePass = 0;
                        }
                        flag = gModelSlots[i].csState->collisionEnabled;
                    }
                    if ((gCollisionDeferredPush == 0 || (actor->collisionMode & 0x10)) && flag != 0) {
                        gCollisionDeferredHit = 0;
                        ret = 0;
                        while (node != NULL && gCollisionDeferredHit == 0) {
                            if (node->active != 0 && node->scaledRadius != 0 && !(node->collisionSkipFlags & 6)) {
                                ret |= func_80673708(node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius, buf->box_start, buf->box_end, arcMin, arcMax);
                            }
                            node = node->next;
                        }
                        result |= ret;
                        if (sCollisionHitPart != 0) {
                            if (gModelSlots[i].csState != NULL) {
                                gModelSlots[i].csState->hitId = sCollisionHitPart;
                                gModelSlots[i].csState->hitActorType = actor->actorType;
                            }
                        }
                        if (gCollisionDeferredHit != 0) {
                            actorBuildCollisionHit(i, actor, buf->box_start);
                        }
                        if (gModelSlots[i].csState != NULL && gModelSlots[i].csState->contactCallbacks == 0) {
                            sDamageSurfaceContact = savedFlags;
                        }
                        if (ret && gCollisionDeferredPush == 0 && gCollisionNearestFound != 0) {
                            actorUpdateSubActorOffsets(actor, 0);
                        }
                    }
                }
            }
        }
    }
    return result;
}


extern s32 gCollisionPlanePointX;
extern s32 gCollisionPlanePointY;
extern s32 gCollisionPlanePointZ;
extern s32 gCollisionPlaneDist;
extern CollisionBox *gCollisionHitBox;
s32 func_806744A8(CollisionBox *, s32, s32, s32, s32);

void actorBuildCollisionHit(s32 slot, Actor *actor, CollisionBox *boxes) {
    ActorSub140 *sub;
    f32 pad[7];
    f32 mtx[4][4];
    f32 mtxC[4][4];
    f32 inv[4][4];
    s32 pad2;
    s32 useActorPos;
    u8 ok;
    f32 x[3];
    f32 y[3];
    f32 z[3];
    f32 px;
    f32 py;
    f32 pz;
    s32 i;

    sub = actor->collision;
    useActorPos = 0;
    ok = func_806744A8(gCollisionHitBox, sub->scaledX, sub->scaledY, sub->scaledZ, sub->scaledRadius);
    modelSlotUpdateFacingTrigger(slot);
    if (ok != 0) {
        sub->hitMtxIndex = gCollisionHitBox->mtxIndex;
        sub->hitBoxIndex = gCollisionHitBox - boxes;
        modelSlotBuildTransformMatrix(slot, gCollisionHitBox->mtxIndex, mtx);
        matrix4Invert(inv, mtx);
        if (gModelSlots[slot].csState != NULL && (gModelSlots[slot].csState->modelFlags & 0x24)) {
            useActorPos = 1;
        }
        if (useActorPos != 0) {
            px = actor->x;
            py = actor->y;
            pz = actor->z;
        } else {
            px = (f32)gCollisionPlanePointX / 8;
            py = (f32)gCollisionPlanePointY / 8;
            pz = (f32)gCollisionPlanePointZ / 8;
        }
        if (!(actor->flags & 0x800)) {
            guMtxXFMF(inv, px, py, pz, &sub->hitPosX, &sub->hitPosY, &sub->hitPosZ);
        }
        x[0] = (f32)gCollisionHitBox->x0 / 8;
        y[0] = (f32)gCollisionHitBox->y0 / 8;
        z[0] = (f32)gCollisionHitBox->z0 / 8;
        x[1] = (f32)gCollisionHitBox->x1 / 8;
        y[1] = (f32)gCollisionHitBox->y1 / 8;
        z[1] = (f32)gCollisionHitBox->z1 / 8;
        x[2] = (f32)gCollisionHitBox->x2 / 8;
        y[2] = (f32)gCollisionHitBox->y2 / 8;
        z[2] = (f32)gCollisionHitBox->z2 / 8;
        for (i = 0; i < 3; i++) {
            guMtxXFMF(inv, x[i], y[i], z[i], &sub->hitTriX[i], &sub->hitTriY[i], &sub->hitTriZ[i]);
        }
        sub->hitSlotId = gModelSlots[slot].id;
        sub->hitRadius = gCollisionPlaneDist;
        if (sub->hitRadius < 0x14) {
            sub->hitRadius = 0x14;
        }
        sub->maxPushDist = actorGetCollisionThreshold(actor);
        sub->hitNormalYaw = gCollisionHitBox->normalYaw;
        if (gCollisionHitBox->normalFlipped != 0) {
            sub->hitNormalYaw -= 0x800;
        }
        if (sub->hitNormalYaw < 0) {
            sub->hitNormalYaw += 0x1000;
        }
        sub->hasSlotHit = 1;
        if (actor->collisionFlags & 1) {
            actorReflectCollisionAngle(actor, gCollisionHitBox, sub);
        }
    }
}

void actorReflectCollisionAngle(Actor *actor, CollisionBox *box, ActorSub140 *coll) {
    PlayerState *sub = actor->customState;
    s64 total;
    s64 x_prod;
    s64 y_prod;
    sub->wallNormalYaw = box->normalYaw;
    y_prod = box->ny * coll->scaledY;
    x_prod = box->nx * coll->scaledX;
    total = (box->nz * coll->scaledZ) + x_prod + y_prod + box->d;
    if (box->d > 0) {
        if (total <= 0) {
            sub->wallNormalYaw += 0x800;
        }
    } else if (total >= 0) {
        sub->wallNormalYaw += 0x800;
    }
    sub->wallNormalYaw &= 0xFFF;
}

s32 actorGetCollisionThreshold(Actor *actor) {
    switch (actor->actorType) {
    case 5: {
        PlayerState *sub = actor->customState;
        if (gPlayerSlots[sub->playerIndex].sizeMode == 1) {
            return 0x32;
        }
        return 0x14;
    }
    case 3:
        return 0x32;
    case 2:
        return 0x32;
    case 4:
        return 0x32;
    case 21:
        return 0x12C;
    default:
        return 0x32;
    }
}

extern Actor *gCurrentActor;

void modelSlotUpdateFacingTrigger(s32 slot) {
    s16 yaw;
    s32 inArc;
    s32 kind;
    CsState *sub;
    s16 yawDiff;
    f32 posX;
    f32 posY;
    f32 posZ;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    f32 scale;
    f32 yOffset;
    f32 mtx[4][4];
    f32 tmp[4][4];
    f32 inv[4][4];
    f32 px;
    f32 py;
    f32 pz;
    f32 localX;
    f32 localY;
    f32 localZ;
    f32 minusX;
    f32 minusY;
    f32 minusZ;
    f32 plusX;
    f32 plusY;
    f32 plusZ;
    f32 minusDist;
    s16 arcMax;
    s16 arcMin;
    s16 pad;
    f32 angle;

    inArc = 0;
    if (gModelSlots[slot].csState != NULL && gCollisionHitBox->pushable != 0) {
        sub = gModelSlots[slot].csState;
        kind = sub->pushMode;
        switch (kind) {
        case 0:
            break;
        case 1:
            sub->pushContact = 1;
            yaw = gCollisionHitBox->normalYaw;
            if (gCollisionHitBox->normalFlipped != 0) {
                yaw -= 0x800;
            }
            if (yaw < 0) {
                yaw += 0x1000;
            }
            yawDiff = yaw - gCurrentActor->yaw;
            if (yawDiff < 0) {
                yawDiff = -yawDiff;
            }
            if (yawDiff >= 0x801) {
                yawDiff = 0xFFF - yawDiff;
            }
            arcMax = sub->pushArcMax;
            arcMin = sub->pushArcMin;
            if (arcMax >= arcMin) {
                if (gCurrentActor->yaw >= arcMin && arcMax >= gCurrentActor->yaw) {
                    inArc = 1;
                }
            } else if (gCurrentActor->yaw >= arcMin || arcMax >= gCurrentActor->yaw) {
                inArc = 1;
            }
            if (yawDiff < 0x258 && inArc != 0) {
                angle = (yaw / 4095.0) * 6.2831854820251465;
                yaw = 0; // FAKE: dead store to angle's operand kills store-forwarding so angle stays a variable (spilled to its own home 0x44)
                sub->pushDirX = sinApprox(angle);
                sub->pushDirZ = cosApprox(angle);
                sub->pushInput = 1;
                return;
            }
            break;
        case 2:
            sub->pushContact = 1;
            yaw = gCollisionHitBox->normalYaw;
            if (gCollisionHitBox->normalFlipped != 0) {
                yaw -= 0x800;
            }
            if (yaw < 0) {
                yaw += 0x1000;
            }
            yawDiff = yaw - gCurrentActor->yaw;
            if (yawDiff < 0) {
                yawDiff = -yawDiff;
            }
            if (yawDiff >= 0x801) {
                yawDiff = 0xFFF - yawDiff;
            }
            arcMax = sub->pushArcMax;
            arcMin = sub->pushArcMin;
            if (arcMax >= arcMin) {
                if (gCurrentActor->yaw >= arcMin && arcMax >= gCurrentActor->yaw) {
                    inArc = 1;
                }
            } else if (gCurrentActor->yaw >= arcMin || arcMax >= gCurrentActor->yaw) {
                inArc = 1;
            }
            if (yawDiff < 0x258 && inArc != 0) {
                modelSlotGetTransformVectors(slot, &posX, &posY, &posZ, &rotX, &rotY, &rotZ, &scale, &yOffset, 0);
                guScaleF(mtx, scale, scale, scale);
                guRotateF(tmp, rotX, 1.0f, 0.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, rotY, 0.0f, 1.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, rotZ, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
                guTranslateF(tmp, posX, posY, posZ);
                guMtxCatF(mtx, tmp, mtx);
                matrix4Invert(inv, mtx);
                px = (f32)gCollisionPlanePointX / 8;
                py = (f32)gCollisionPlanePointY / 8;
                pz = (f32)gCollisionPlanePointZ / 8;
                guMtxXFMF(inv, px, py, pz, &localX, &localY, &localZ);
                guScaleF(mtx, scale, scale, scale);
                guRotateF(tmp, rotX, 1.0f, 0.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, rotY + 1.0, 0.0f, 1.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, rotZ, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
                guTranslateF(tmp, posX, posY, posZ);
                guMtxCatF(mtx, tmp, mtx);
                guMtxXFMF(mtx, localX, localY, localZ, &plusX, &plusY, &plusZ);
                guScaleF(mtx, scale, scale, scale);
                guRotateF(tmp, rotX, 1.0f, 0.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, rotY - 1.0, 0.0f, 1.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, rotZ, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
                guTranslateF(tmp, posX, posY, posZ);
                guMtxCatF(mtx, tmp, mtx);
                guMtxXFMF(mtx, localX, localY, localZ, &minusX, &minusY, &minusZ);
                minusDist = camDistance3D(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, minusX, minusY, minusZ);
                if (minusDist < camDistance3D(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, plusX, plusY, plusZ)) {
                    sub->pushInput = 1;
                    return;
                }
                sub->pushInput = 2;
            }
            break;
        }
    }
}

extern u8 D_807FB603;
s32 func_806738D0(s32, s32, s32, s32, CollisionBox *, CollisionBox *);

s32 actorResolveModelSlotCollision(Actor *actor) {
    ActorSub140 *sub;
    s8 pad;
    s16 slot;
    DynamicBuffer *buf;
    f32 px[3];
    f32 py[3];
    f32 pz[3];
    f32 x;
    f32 y;
    f32 z;
    f32 pad1[8];
    f32 mtx[4][4];
    f32 pad2[16];
    f32 e1[3];
    f32 e2[3];
    f32 n[3];
    f32 out[3];
    s32 i;
    f32 scale;
    s32 ret;
    ModelNode *node;
    f32 inv;
    CsState *hit;

    {
        u8 kind;

        kind = 0;
        sub = actor->collision;
        ret = 0;
        slot = hashTableLookup(sub->hitSlotId);
        if (slot != -1) {
            buf = &gModelSlots[slot].boxBuffer;
            if (!(buf->flags & 1)) {
                return 0;
            }
            D_807FB603 = buf->unk14;
            gCollisionDeferredPush = 1;
            gCollisionResolvePass = 1;
            sDamageSurfaceContact = 0;
            func_80672E90(sub->scaledX, sub->scaledY, sub->scaledZ);
            actorSetCameraBoundaryMode(actor->actorType);
            hit = gModelSlots[slot].csState;
            if (hit != NULL) {
                if (hit->modelFlags & 4) {
                    kind = 1;
                }
                if (hit->modelFlags & 8) {
                    kind = 2;
                }
                if (hit->modelFlags & 0x10) {
                    kind = 3;
                }
                if (hit->modelFlags & 0x20) {
                    kind = 4;
                }
            }
            if (hit != NULL && hit->prevPushInput != 0) {
                ret = func_80673708(sub->scaledX, sub->scaledY, sub->scaledZ, sub->hitRadius, buf->box_start, buf->box_end, &actor->arcYawMin, &actor->arcYawMax) & 0xFF;
            } else {
                actorSetTargetAngleBounds(buf->box_start + sub->hitBoxIndex);
                switch (kind) {
                case 0:
                    ret = func_806738D0(sub->scaledX, sub->scaledY, sub->scaledZ, sub->hitRadius, buf->box_start, buf->box_end) & 0xFF;
                    func_80673708(sub->scaledX, sub->scaledY, sub->scaledZ, sub->hitRadius, buf->box_start, buf->box_end, &actor->arcYawMin, &actor->arcYawMax);
                    break;
                case 1:
                case 2:
                    ret = func_80673708(sub->scaledX, sub->scaledY, sub->scaledZ, sub->hitRadius, buf->box_start, buf->box_end, &actor->arcYawMin, &actor->arcYawMax) & 0xFF;
                    break;
                case 3:
                case 4:
                    ret = func_80673708(sub->scaledX, sub->scaledY, sub->scaledZ, 0x64, buf->box_start, buf->box_end, &actor->arcYawMin, &actor->arcYawMax) & 0xFF;
                    break;
                }
            }
            if (sCollisionHitPart != 0 && hit != NULL) {
                gModelSlots[slot].csState->hitId = sCollisionHitPart;
                gModelSlots[slot].csState->hitActorType = actor->actorType;
            }
            if (gModelSlots[slot].csState != NULL && gModelSlots[slot].csState->contactCallbacks != 0) {
                actorQueueCollisionCallbacks(actor);
            }
            if (hit != NULL && hit->prevPushInput != 0 && gPlayerPadState[playerFindIndexByActor(actor)].stickMag > 30.0) {
                ret = 1;
            }
            if (actor->collisionFlags & 1) {
                actorCalcPlaneContactPoint(actor, slot, sub);
            }
            if (ret != 0) {
                modelSlotBuildTransformMatrix(slot, sub->hitMtxIndex, mtx);
                guMtxXFMF(mtx, sub->hitPosX, sub->hitPosY, sub->hitPosZ, &x, &y, &z);
                if (kind == 1 || kind == 4) {
                    actor->x = x;
                    actor->z = z;
                } else {
                    for (i = 0; i < 3; i++) {
                        guMtxXFMF(mtx, sub->hitTriX[i], sub->hitTriY[i], sub->hitTriZ[i], &px[i], &py[i], &pz[i]);
                    }
                    e1[0] = px[2] - px[0];
                    e1[1] = py[2] - py[0];
                    e1[2] = pz[2] - pz[0];
                    e2[0] = px[1] - px[0];
                    e2[1] = py[1] - py[0];
                    e2[2] = pz[1] - pz[0];
                    n[0] = (e1[1] * e2[2]) - (e1[2] * e2[1]);
                    n[1] = (e1[2] * e2[0]) - (e1[0] * e2[2]);
                    n[2] = (e1[0] * e2[1]) - (e1[1] * e2[0]);
                    inv = 1.0f / sqrtf(((n[0] * n[0]) + (n[1] * n[1])) + (n[2] * n[2]));
                    out[0] = n[0] * inv;
                    out[1] = n[1] * inv;
                    out[2] = n[2] * inv;
                    if (sub->slotPushDist != 0) {
                        gCollisionPlaneDist = sub->slotPushDist + 5;
                        if (sub->maxPushDist < gCollisionPlaneDist) {
                            gCollisionPlaneDist = sub->maxPushDist;
                        }
                    } else {
                        gCollisionPlaneDist = sub->hitRadius;
                        if (gCollisionPlaneDist < 0xF) {
                            gCollisionPlaneDist = 0xF;
                        }
                        if (sub->maxPushDist < gCollisionPlaneDist) {
                            gCollisionPlaneDist = sub->maxPushDist;
                        }
                    }
                    if (kind == 3) {
                        gCollisionPlaneDist = 0x46;
                    }
                    sub->slotPushDist = gCollisionPlaneDist;
                    scale = (f32)gCollisionPlaneDist / 8;
                    out[0] = out[0] * scale;
                    out[1] = out[1] * scale;
                    out[2] = out[2] * scale;
                    if (kind == 3 || actorCheckPointInAngleArc(actor, x - out[0], z - out[2]) != 0) {
                        actor->x = x - out[0];
                        actor->z = z - out[2];
                    }
                }
            } else {
                node = sub->nodes;
                while (node != NULL) {
                    if (node->active != 0) {
                        i = func_80673708(node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius, buf->box_start, buf->box_end, &actor->arcYawMin, &actor->arcYawMax); ret = (ret | i) & 0xFF; // LAYOUT: same-line call-result keeps 'or ret,ret,v0' operand order and no extra result var
                    }
                    node = node->next;
                }
            }
        }
    }
    return ret;
}

extern s16 gKongNormalWallContactOffsets[];
extern s16 gKongWallContactOffsets[];
extern u8 gCurrentPlayerIndex;
extern s16 gCurrentCharacterIndex;

void actorCalcPlaneContactPoint(Actor *actor, s16 slot, ActorSub140 *hit) {
    f32 mtx[4][4];
    f32 originX;
    f32 originY;
    f32 originZ;
    s32 i;
    f32 triX[3];
    f32 triY[3];
    f32 triZ[3];
    f32 normal[3];
    f32 v1[3];
    f32 v2[3];
    f32 inv_len;
    f32 norm[3];
    f32 out[3];
    PlayerState *player;
    f32 radius;
    f32 scale;

    player = actor->customState;
    if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) {
        radius = gKongNormalWallContactOffsets[gCurrentCharacterIndex];
    } else {
        radius = gKongWallContactOffsets[gCurrentCharacterIndex];
    }

    modelSlotBuildTransformMatrix(slot, hit->hitMtxIndex, mtx);
    guMtxXFMF(mtx, hit->hitPosX, hit->hitPosY, hit->hitPosZ, &originX, &originY, &originZ);

    for (i = 0; i < 3; i++) {
        guMtxXFMF(mtx, hit->hitTriX[i], hit->hitTriY[i], hit->hitTriZ[i], &triX[i], &triY[i], &triZ[i]);
    }

    v1[0] = triX[2] - triX[0];
    v1[1] = triY[2] - triY[0];
    v1[2] = triZ[2] - triZ[0];

    v2[0] = triX[1] - triX[0];
    v2[1] = triY[1] - triY[0];
    v2[2] = triZ[1] - triZ[0];

    normal[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    normal[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    normal[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

    inv_len = 1.0f / sqrtf((normal[0] * normal[0]) + (normal[1] * normal[1]) + (normal[2] * normal[2]));
    norm[0] = normal[0] * inv_len;
    norm[1] = normal[1] * inv_len;
    norm[2] = normal[2] * inv_len;

    scale = radius / 8;
    out[0] = norm[0] * scale;
    out[1] = norm[1] * scale;
    out[2] = norm[2] * scale;

    player->wallContactX = originX - out[0];
    player->wallContactZ = originZ - out[2];
    player->stateStep = 1;
}

extern s16 sHitBoxYawMin;
extern s16 sHitBoxYawMax;
extern s16 sHitBoxBackYawMin;
extern s16 sHitBoxBackYawMax;

void actorSetTargetAngleBounds(CollisionBox *box) {
    s16 yaw;

    yaw = box->normalYaw;
    sHitBoxYawMin = yaw - 0x32;
    if (sHitBoxYawMin < 0) {
        sHitBoxYawMin += 0xFFF;
    }
    sHitBoxYawMax = yaw + 0x32;
    if (sHitBoxYawMin >= 0x1000) {
        sHitBoxYawMax -= 0xFFF;
    }
    sHitBoxBackYawMin = sHitBoxYawMin + 0x800;
    if (sHitBoxBackYawMin >= 0x1000) {
        sHitBoxBackYawMin -= 0xFFF;
    }
    sHitBoxBackYawMax = sHitBoxYawMax + 0x800;
    if (sHitBoxBackYawMax >= 0x1000) {
        sHitBoxBackYawMax -= 0xFFF;
    }
}

u8 func_806730A4(s32, s32, s32, s32);
u8 func_806734E4(s32, s32, s32, s32, s16 *, s16 *);
s32 actorCheckTargetAngleBounds(Actor *actor, s16 *arcMin, s16 *arcMax) {
    s32 pad0;
    s32 pad1;
    ActorSub140 *sub = actor->collision;
    ModelNode *node;
    u8 ret = 0;

    sub->hasPushTarget = 0;
    sPushToFullThreshold = 0;

    if (func_806730A4(sub->scaledX, sub->scaledY, sub->scaledZ, sub->scaledRadius) != 0) {
        if (actor->renderFlags & 0x80) {
            sBoundaryTwoSided = 1;
        }
        actorUpdateCollisionSpheres(actor, 0);
        node = sub->nodes;
        while (node != NULL) {
            if (node->active != 0 && node->scaledRadius != 0 && !(node->collisionSkipFlags & 1)) {
                ret |= func_806734E4(node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius, arcMin, arcMax);
            }
            node = node->next;
        }
        if ((ret != 0 || sBoundaryTwoSided != 0) && gCollisionNearestFound != 0) {
            actorUpdateCollisionExtents(actor);
        }
        sBoundaryTwoSided = 0;
    }
    return ret;
}

extern PlayerState *gActivePlayerState;
extern s32 gCollisionNearestTri;
extern s16 gCollisionNearestTriIndex;

CollisionBox *collisionBuildHitBox(s32, s16); // asm (77B90): returns the hit box left in s0

void actorUpdateFacingAndOffset(CollisionBox *box, s32 unused1, s32 unused2, s32 unused3) {
    s16 facingDist;
    s32 offsetX;
    s32 pad2C;
    s32 prevThreshold;
    s32 backDist;
    ActorSub140 *sub;
    f32 cosYaw;
    s32 threshold;

    facingDist = mathAngleDistance(box->normalYaw, sWallProbeYaw);
    backDist = mathAngleDistance((box->normalYaw + 0x800) & 0xFFF, sWallProbeYaw);
    if ((facingDist < 0x321) || (backDist < 0x321)) {
        mathAngleDistance(box->normalYaw, gActivePlayerState->wallNormalYaw);
        mathAngleDistance((box->normalYaw + 0x800) & 0xFFF, gActivePlayerState->wallNormalYaw);
        sub = sWallProbeActor->collision;
        func_806744A8(box, sub->scaledX, sub->scaledY, sub->scaledZ, sub->scaledRadius);
        prevThreshold = gCollisionPlaneDist;
        offsetX = (s32)(mathSinF(sWallProbeYaw) * 20.0f);
        cosYaw = mathCosF(sWallProbeYaw);
        sub = sWallProbeActor->collision;
        func_806744A8(box, sub->scaledX + offsetX, sub->scaledY, sub->scaledZ + (s32)(cosYaw * 20.0f), sub->scaledRadius);
        threshold = gCollisionPlaneDist;
        if (prevThreshold - 2 < threshold) {
            sWallProbeOk = 0;
        }
    }
}

void actorUpdateCollisionExtents(Actor *actor) {
    s32 pad4C;
    PlayerState *player;
    f32 radius;
    f32 nz;
    f32 ny;
    f32 nx;

    if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) {
        radius = gKongNormalWallContactOffsets[gCurrentCharacterIndex];
    } else {
        radius = gKongWallContactOffsets[gCurrentCharacterIndex];
    }
    if (actor->collisionFlags & 1) {
        f32 scale;
        f32 hitX;
        f32 hitZ;

        player = actor->customState;
        actorComputeBoxNormal(actor, &nx, &ny, &nz, 1);
        scale = radius / 8;
        hitX = (f32)gCollisionPlanePointX / 8;
        hitZ = (f32)gCollisionPlanePointZ / 8;
        nx *= scale;
        ny *= scale;
        nz *= scale;
        player->wallContactX = hitX - nx;
        player->wallContactZ = hitZ - nz;
        player->stateStep = 1;
        actorReflectCollisionAngle(actor, collisionBuildHitBox(gCollisionNearestTri, gCollisionNearestTriIndex), actor->collision);
    }
    actorUpdateSubActorOffsets(actor, 1);
}

void actorUpdateSubActorOffsets(Actor *actor, u8 useHitBox) {
    if (gCollisionPlaneDist < actorGetPlayerThreshold(actor)) {
        ActorSub140 *sub = actor->collision;
        f32 targetX;
        f32 scale;
        f32 targetZ;
        f32 normalZ;
        f32 normalY;
        f32 normalX;

        actorComputeBoxNormal(actor, &normalX, &normalY, &normalZ, useHitBox);
        targetX = (f32)gCollisionPlanePointX / 8;
        targetZ = (f32)gCollisionPlanePointZ / 8;
        if (sPushToFullThreshold != 0) {
            scale = (f32)actorGetPlayerThreshold(actor) / 8;
            normalX *= scale;
            normalZ *= scale;
        } else {
            scale = (f32)(gCollisionPlaneDist + 6) / 8;
            normalX *= scale;
            normalZ *= scale;
        }
        sub->pushTargetX = targetX - normalX;
        sub->pushTargetZ = targetZ - normalZ;
        sub->hasPushTarget = 1;
    }
}

extern CollisionBox *gCollisionNearestBox;

void actorComputeBoxNormal(Actor *actor, f32 *outX, f32 *outY, f32 *outZ, u8 useHitBox) {
    CollisionBox *box;
    f32 padA;
    ActorSub140 *sub;
    f32 v1[3];
    f32 v2[3];
    f32 n[3];
    f32 padB;
    f32 x[3];
    f32 y[3];
    f32 z[3];
    f32 invLen;

    sub = actor->collision;
    if (useHitBox) {
        box = collisionBuildHitBox(gCollisionNearestTri, gCollisionNearestTriIndex);
    } else {
        box = gCollisionNearestBox;
    }
    x[0] = (f32)box->x0 / 8;
    y[0] = (f32)box->y0 / 8;
    z[0] = (f32)box->z0 / 8;
    x[1] = (f32)box->x1 / 8;
    y[1] = (f32)box->y1 / 8;
    z[1] = (f32)box->z1 / 8;
    x[2] = (f32)box->x2 / 8;
    y[2] = (f32)box->y2 / 8;
    z[2] = (f32)box->z2 / 8;

    v1[0] = x[2] - x[0];
    v1[1] = y[2] - y[0];
    v1[2] = z[2] - z[0];
    v2[0] = x[1] - x[0];
    v2[1] = y[1] - y[0];
    v2[2] = z[1] - z[0];

    n[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    n[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    n[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

    invLen = 1.0f / sqrtf((n[0] * n[0]) + (n[1] * n[1]) + (n[2] * n[2]));
    *outX = n[0] * invLen;
    *outY = n[1] * invLen;
    *outZ = n[2] * invLen;

    func_806744A8(box, sub->scaledX, sub->scaledY, sub->scaledZ, sub->scaledRadius);
    if (useHitBox) {
        if (actor->flags & 0x800) {
            gCollisionPlanePointX = sub->boxContactX;
            gCollisionPlanePointZ = sub->boxContactZ;
        }
        sub->boxContactX = gCollisionPlanePointX;
        sub->boxContactZ = gCollisionPlanePointZ;
    }
}

s32 actorGetPlayerThreshold(Actor *actor) {
    PlayerState *player;

    switch (actor->actorType) {
    case 5:
        player = actor->customState; // type 5: the player actor's state
        if (gPlayerSlots[player->playerIndex].sizeMode != 1) {
            return 0x14;
        }
        return 0x32;
    case 3:
        return 0x32;
    case 2:
        return 0x32;
    default:
        return 0x32;
    }
}

void actorUpdateCollisionSpheres(Actor *actor, u8 force) {
    f32 scale = 0.15f;
    ActorSub140 *sub = actor->collision;
    f32 outX;
    f32 outY;
    f32 outZ;
    f32 mtx[4][4];
    ModelNode *node;
    Mtx *base;
    u8 idx;

    if (force != 0 || sub->spheresFrame != sub->posFrame) {
        if (actor->sub4 != NULL) {
            scale = actor->sub4->scaleY;
        }
        if (actor->renderFlags & 0x800) {
            scale = actor->collisionScaleOverride;
        }
        if (gFrameCounter == sub->mtxFrame) {
            idx = gGfxBufferIndex;
        } else {
            idx = gGfxBufferIndex ^ 1;
        }
        node = sub->nodes;
        base = sub->nodeMtx[idx];
        while (node != NULL) {
            switch (node->mtxOffset) {
            case -1:
                memcpy(mtx, sub->modelMtxF, sizeof(mtx));
                guMtxXFMF(mtx, node->x, node->y, node->z, &outX, &outY, &outZ);
                break;
            default:
                guMtxXFML(&base[(u32)node->mtxOffset >> 6], node->x, node->y, node->z, &outX, &outY, &outZ);
                break;
            }
            node->scaledX = outX * 8.0f;
            node->scaledY = outY * 8.0f;
            node->scaledZ = outZ * 8.0f;
            node->scaledRadius = node->scale * scale * 8.0f;
            node = node->next;
        }
        sub->spheresFrame = sub->posFrame;
    }
}

void actorUpdateNodePositions(ActorSub140 *sub, u8 force) {
    ModelSubNode *node;
    u8 bufIdx;
    f32 outX;
    f32 outY;
    f32 outZ;
    f32 mtx[4][4];
    Mtx *mtxBase;

    if (force || (gFrameCounter != sub->subNodesFrame)) {
        if (gFrameCounter == sub->mtxFrame) {
            bufIdx = gGfxBufferIndex;
        } else {
            bufIdx = gGfxBufferIndex ^ 1;
        }
        node = sub->subNodes;
        mtxBase = sub->nodeMtx[bufIdx];
        while (node != NULL) {
            switch (node->mtxOffset) {
            case -1:
                memcpy(mtx, sub->modelMtxF, sizeof(mtx));
                guMtxXFMF(mtx, node->x, node->y, node->z, &outX, &outY, &outZ);
                break;
            default:
                guMtxXFML(&mtxBase[(u32)node->mtxOffset >> 6], node->x, node->y, node->z, &outX, &outY, &outZ);
                break;
            }
            node->scaledX = outX * 8.0f;
            node->scaledY = outY * 8.0f;
            node->scaledZ = outZ * 8.0f;
            node = node->next;
        }
        sub->subNodesFrame = gFrameCounter;
    }
}

s32 actorGetNodePos(Actor *actor, s32 index, f32 *outX, f32 *outY, f32 *outZ) {
    s32 pad0;
    s32 pad1;
    s32 pad2;
    ActorSub140 *sub;
    ModelSubNode *node;
    s32 count;

    sub = actor->collision;
    if (sub != NULL) {
        actorUpdateNodePositions(sub, 1);
        node = actor->collision->subNodes;
        count = index - 1;
        while (node != NULL && count != 0) {
            count--;
            node = node->next;
        }
        if (node == NULL) {
            *outZ = 0.0f;
            *outY = 0.0f;
            *outX = 0.0f;
            return 0;
        }
        *outX = (f32)node->scaledX / 8;
        *outY = (f32)node->scaledY / 8;
        *outZ = (f32)node->scaledZ / 8;
        return 1;
    }
    return 0;
}
void actorGetSubNodePos(Actor *actor, s32 index, f32 *outX, f32 *outY, f32 *outZ) {
    s32 count = index - 1;
    ModelSubNode *node = actor->collision->subNodes;

    while (node != NULL && count != 0) {
        count--;
        node = node->next;
    }
    *outX = node->x;
    *outY = node->y;
    *outZ = node->z;
}

s32 actorStepSubNodeList(Actor *actor, s32 index) {
    ActorSub140 *sub = actor->collision;
    u8 bufIdx;
    s32 base;
    ModelSubNode *node;

    if (gFrameCounter == sub->mtxFrame) {
        bufIdx = gGfxBufferIndex;
    } else {
        bufIdx = gGfxBufferIndex ^ 1;
    }
    base = (s32)sub->nodeMtx[bufIdx]; // matrix-buffer base address for the byte offsets in node->unk18

    node = sub->subNodes;
    index--;
    while (index != 0) {
        index--;
        node = node->next;
    }

    return (((u32)node->mtxOffset >> 6) << 6) + base;
}


u8 collisionTestSphere(f32 x, f32 y, f32 z, f32 radius, s16 *arcMin, s16 *arcMax, u8 testSlots, u16 boundaryMode) {
    u8 ret;

    x *= 8.0f;
    y *= 8.0f;
    z *= 8.0f;
    *arcMin = 0;
    *arcMax = 0xFFF;
    radius *= 8.0f;
    gCollisionArcWidened = 0;
    func_80672E90(x, y, z);
    actorSetCameraBoundaryMode(boundaryMode);
    if (testSlots != 0) {
        ret = func_806734E4((s32)x, (s32)y, (s32)z, (s32)radius, arcMin, arcMax);
        ret |= collisionTestSphereSlots(x, y, z, radius, arcMin, arcMax);
    } else {
        ret = func_806730A4(x, y, z, (s32)radius);
        if (ret == 0) {
            ret = collisionTestSphereSlots(x, y, z, radius, arcMin, arcMax);
        }
    }
    return ret;
}
extern s32 sColliderActorType;



u8 collisionTestSphereSlots(f32 fx, f32 fy, f32 fz, f32 fradius, s16 *arcMin, s16 *arcMax) {
    s32 x;
    s32 y;
    s32 z;
    s32 radius;
    u8 result;
    s32 i;
    DynamicBuffer *buf;
    CsState *hitInfo;

    result = 0;
    gCollisionDeferredPush = 0;
    i = 0;
    if (gModelSlotCount > 0) {
        do {
            buf = &gModelSlots[i].boxBuffer;
            if (buf->box_start != NULL &&
                (sColliderActorType != 0xBC || (gModelSlots[i].triBuffer.flags & 2))) {
                x = fx;
                y = fy;
                z = fz;
                radius = fradius;
                if (collisionSpheresOverlap(x, y, z, radius,
                                  buf->scaledX,
                                  buf->scaledY,
                                  buf->scaledZ,
                                  buf->scaledRadius) != 0 &&
                    (buf->flags & 1) &&
                    ((hitInfo = gModelSlots[i].csState) == NULL || hitInfo->collisionEnabled != 0)) {
                    result |= func_80673708(x, y, z, radius, buf->box_start, buf->box_end, arcMin, arcMax);
                }
            }
            i++;
        } while (i < gModelSlotCount);
    }
    return result;
}


s16 mathAngleArcProximityScale(s16 angle, s16 arcMin, s16 arcMax, s16 maxValue) {
    s16 opposite;
    f32 ratio;
    s16 bisect;
    s16 diff1;
    s16 diff2;

    if (arcMin >= angle) {
        if (arcMax >= angle && arcMin >= arcMax) {
            return 0x270F;
        }
    } else if (arcMax >= angle || arcMin >= arcMax) {
        return 0x270F;
    }

    opposite = arcMax + 0x800;
    if (opposite >= 0x1000) {
        opposite -= 0x1000;
    }

    bisect = mathAngleArcMidpoint(angle, arcMin);
    if ((angle - bisect) > 0) {
        diff1 = angle - bisect;
    } else {
        diff1 = -(angle - bisect);
    }
    if (diff1 >= 0x800) {
        diff1 = 0xFFF - diff1;
    }
    if ((opposite - bisect) > 0) {
        diff2 = opposite - bisect;
    } else {
        diff2 = -(opposite - bisect);
    }
    if (diff2 >= 0x800) {
        diff2 = 0xFFF - diff2;
    }

    if (diff1 != 0) {
        ratio = (f32)diff2 / (f32)diff1;
    } else {
        ratio = 0.0f;
    }

    if (ratio > 1.0) {
        ratio = 1.0f;
    }
    if (ratio < 0.2) {
        ratio = 0.0f;
    }
    return (s16)(s32)((f32)maxValue * ratio);
}



s32 actorCheckPointInAngleArc(Actor *actor, f32 x, f32 z) {
    s32 px;
    s32 pz;
    s32 actorX;
    s32 actorZ;
    s32 dx;
    s32 dz;
    f32 dist;
    s16 angle;

    actorX = (s32)(actor->prevX * 8.0f);
    actorZ = (s32)(actor->prevZ * 8.0f);
    px = (s32)(x * 8.0f);
    pz = (s32)(z * 8.0f);
    dx = px - actorX;
    dz = pz - actorZ;
    dist = sqrtf((f32)((dx * dx) + (dz * dz)));
    if ((f64)dist == 0.0) {
        return 1;
    }
    if (dx >= 0 && dz >= 0) {
        angle = (s16)(mathAsinFixed((s32)(((f64)dx * 65535.9) / (f64)dist)) >> 4);
    }
    if (dx >= 0 && dz < 0) {
        angle = (mathAsinFixed((s32)(((f64)(actorZ - pz) * 65535.9) / (f64)dist)) >> 4) + 0x400;
    }
    if (dx < 0 && dz < 0) {
        angle = (mathAsinFixed((s32)(((f64)(actorX - px) * 65535.9) / (f64)dist)) >> 4) + 0x800;
    }
    if (dx < 0 && dz >= 0) {
        angle = (mathAsinFixed((s32)(((f64)dz * 65535.9) / (f64)dist)) >> 4) + 0xC00;
    }
    return actorAngleInArc(actor, angle) ? 1 : 0;
}



s32 actorAngleInArc(Actor *actor, s16 angle) {
    s16 clamp[2];

    return mathAngleClampToArc(clamp[0], angle, actor->arcYawMin, actor->arcYawMax, &clamp[1]);
}


s32 mathAngleInArcWithMargin(s16 arcMin, s16 arcMax, s16 angle, s16 margin) {
    s16 clamp[2];

    return mathAngleClampToArcWithMargin(clamp[0], angle, arcMin, arcMax, &clamp[1], margin);
}

s32 actorAngleInArcWithMargin(Actor *actor, s16 angle, s16 margin) {
    s16 clamp[2];

    return mathAngleClampToArcWithMargin(clamp[0], angle, actor->arcYawMin, actor->arcYawMax, &clamp[1], margin);
}

s32 mathAngleClampToArc(s16 unused, s16 angle, s16 arcMin, s16 arcMax, s16 *out) {
    return mathAngleClampToArcWithMargin(unused, angle, arcMin, arcMax, out, 10);
}


s32 mathAngleClampToArcWithMargin(s32 unused, s16 angle, s16 arcMin, s16 arcMax, s16 *out, s16 margin) {
    s16 innerMin;
    s16 innerMax;
    s16 wrapMin;
    s16 wrapMax;
    u8 wrapCase;

    innerMin = arcMin + margin;
    innerMax = arcMax - margin;
    wrapMin = innerMin;
    wrapMax = innerMax;
    if (arcMax >= arcMin) {
        if (innerMin < innerMax && angle >= innerMin && innerMax >= angle) {
            *out = angle;
            return 1;
        }
        *out = mathAngleNearestArcPoint(arcMin, arcMax, angle);
    } else {
        wrapCase = 0;
        if (innerMin >= 0x1000) {
            wrapMin = innerMin - 0x1000;
            wrapCase = 1;
        }
        if (innerMax < 0) {
            wrapMax = innerMax + 0x1000;
            wrapCase += 2;
        }

        switch (wrapCase) {
        default:
            return 0;
        case 0:
            if (angle >= wrapMin || wrapMax >= angle) {
                *out = angle;
                return 1;
            }
            *out = mathAngleNearestArcPoint(arcMin, arcMax, angle);
            break;
        case 1:
        case 2:
            if (wrapMin < wrapMax && angle >= wrapMin && wrapMax >= angle) {
                *out = angle;
                return 1;
            }
            *out = mathAngleNearestArcPoint(arcMin, arcMax, angle);
            break;
        case 3:
            *out = mathAngleNearestArcPoint(arcMin, arcMax, angle);
            break;
        }
    }

    return 0;
}


s16 mathAngleNearestArcPoint(s16 arcMin, s16 arcMax, s16 angle) {
    s32 diffMin;
    s32 diffMax;
    s16 distMin;
    s16 nearMin;
    s16 nearMax;
    s16 distMax;
    s16 result;

    nearMin = arcMin + 10;
    nearMax = arcMax - 10;
    diffMin = arcMin - angle;
    if (diffMin > 0) {
        distMin = diffMin;
    } else {
        distMin = -diffMin;
    }
    diffMax = arcMax - angle;
    if (distMin >= 0x801) {
        distMin = 0xFFF - distMin;
    }
    if (diffMax > 0) {
        distMax = diffMax;
    } else {
        distMax = -diffMax;
    }
    if (distMax >= 0x801) {
        distMax = 0xFFF - distMax;
    }
    if (distMax >= distMin) {
        if (nearMin >= 0x1000) {
            nearMin -= 0xFFF;
        }
        result = nearMin;
    } else {
        if (nearMax < 0) {
            nearMax += 0xFFF;
        }
        result = nearMax;
    }
    if (arcMax >= arcMin) {
        if ((result < arcMin) || (arcMax < result)) {
            result = mathAngleArcMidpoint(arcMin, arcMax);
        }
    } else if ((result < arcMin) && (arcMax < result)) {
        result = mathAngleArcMidpoint(arcMin, arcMax);
    }
    return result;
}

s16 mathAngleArcMidpoint(s16 start, s16 end) {
    s16 mid;
    s16 wrapped;

    if (end >= start) {
        return (start + end) >> 1;
    }
    mid = ((end - start + 0xFFF) / 2) + start;
    wrapped = mid;
    if (mid >= 0x1000) {
        wrapped = mid - 0xFFF;
    }
    return wrapped;
}



void actorTouchSub140Timestamp(Actor *actor) {
    ActorSub140 *sub = actor->collision;
    if (sub != NULL) {
        sub->mtxFrame = gFrameCounter;
    }
}


void actorUpdateMovementFlags(Actor *actor) {
    ActorSub140 *sub;

    if (actor->collisionMode & 8) {
        sub = actor->collision;
        if (sub->hasSlotHit != 0) {
            actor->hasArcBounds |= actorResolveModelSlotCollision(actor);
        } else {
            sub->slotPushDist = 0;
        }
        if (actor->flags & 0x20) {
            if (actor->collision->hasPushTarget != 0 && actorCheckPointInAngleArc(actor, actor->collision->pushTargetX, actor->collision->pushTargetZ) != 0) {
                actor->x = actor->collision->pushTargetX;
                actor->z = actor->collision->pushTargetZ;
            }
        }
    } else {
        sub = actor->collision;
        if (sub != NULL) {
            sub->hasSlotHit = 0;
        }
    }
}

u8 actorHasActiveMovementFlags(Actor *actor) {
    return actor->attachMode != 0
        || actor->collision->hasSlotHit != 0
        || actor->collision->hasPushTarget != 0
        || (actor->contactFlags & 8) != 0
        || (actor->contactFlags & 0x400) != 0;
}

void actorClearMovementFlags(Actor *actor) {
    ActorSub140 *sub;

    sub = actor->collision;
    actor->attachMode = 0;
    if (sub != NULL) {
        sub->hasSlotHit = 0;
        actor->collision->hasPushTarget = 0;
    }
    actor->contactFlags &= ~8;
    actor->contactFlags &= ~0x400;
    actor->renderFlags |= 0x2000;
}

extern s16 sCollisionTriMinYMargin;
extern s16 sCollisionTriMaxYMargin;

void actorSetCameraBoundaryMode(s32 mode) {
    sColliderActorType = mode;
    if (mode != 0 && mode != 0xBC) {
        sCollisionTriMinYMargin = 2;
        sCollisionTriMaxYMargin = 10;
    } else {
        sCollisionTriMinYMargin = 100;
        sCollisionTriMaxYMargin = 100;
    }
}

extern Actor *gPrimaryPlayerActor;

s32 actorCheckCameraBoundaryCondition(s8 condition) {
    PlayerState *state;

    switch (condition) {
    case 0:
        if (sColliderActorType == 0xBC) {
            return 1;
        }
        break;
    case 1:
        if (sColliderActorType != 0xBC) {
            return 1;
        }
        break;
    case 2:
        if (sColliderActorType != 5 || gPlayerSlots->sizeMode == 1) {
            return 1;
        }
        break;
    case 3:
        if (sColliderActorType == 5 && gPlayerSlots->sizeMode != 1) {
            return 1;
        }
        break;
    case 4:
        if (sColliderActorType == 8) {
            return 1;
        }
        break;
    case 5:
        sPushToFullThreshold = 1;
        return 1;
    case 6:
        state = gPrimaryPlayerActor->customState;
        if (sColliderActorType == 3 && state->isHoldingObject != 0) {
            return 1;
        }
        break;
    case 7:
        state = gPrimaryPlayerActor->customState;
        if (sColliderActorType == 6 && (gPlayerSlots->sizeMode != 1 || state->targetScale[0] != state->currentScale[0])) {
            return 1;
        }
        break;
    case 8:
        if (sColliderActorType == 9) {
            return 1;
        }
        break;
    }
    return 0;
}

static void actorBoundaryStub(void) {
}

s32 actorRng(void) {
    return randomLcgNext();
}
