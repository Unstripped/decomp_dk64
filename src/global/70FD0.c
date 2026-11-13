#define PROTO_SKIP_actorCalcPlaneContactPoint
#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "cutscene.h"
#include "map.h"
#include "collision.h"
#include "heap.h"
#include "sched.h"
#include "proto/boot/30E0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/2F550.h"
#include "proto/global/36880.h"
#include "proto/global/5E020.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/79890.h"
#include "proto/global/7BBD0.h"
#include "proto/global/7CA80.h"
#include "proto/global/CEAE0.h"
#include "proto/global/FE40.h"
void actorCalcPlaneContactPoint(Actor *actor, s16 slot, ActorSub140 *hit);


typedef struct BufferCacheEntry {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
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

extern BufferCacheEntry *D_807FB534;
extern s32 D_807FB538;
extern Actor *D_807FB540;
extern s16 D_807FB544;
extern u8 D_807FB546;
extern u8 D_807FB549;
extern u8 D_807FB604;



extern u8 gGfxBufferIndex;
extern ModelSlot *gModelSlots;



typedef struct CollisionAssetTri {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ s8 unk14;
} CollisionAssetTri;


void collisionBuildSlotBoxes(s32 slot, ModelAssetHeader *asset, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale) {
    s32 off;
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
    s8 lastBone;

    off = slot * sizeof(ModelSlot);
    anim = ((ModelSlot *)((u8 *)gModelSlots + off))->unk78; // FAKE: byte-offset spelling keeps gModelSlots in v1 and the slot * 0x90 product in v0 (gModelSlots[slot].unk78 swaps them)
    lastBone = -1;
    buf = &gModelSlots[slot].unk28;
    if (anim != NULL) {
        animFrame = anim->frames[gGfxBufferIndex];
    } else {
        animFrame = 0;
    }
    boneTable = asset->unk60 + (u8 *)asset;
    buf->unkC = (s32)((f32)asset->unk20 * scale * 8.0f * 1.5);
    buf->unk0 = (s32)(x * 8.0f);
    buf->unk4 = (s32)(y * 8.0f);
    buf->unk8 = (s32)(z * 8.0f);
    count = *(s32 *)(asset->unk4C + (u8 *)asset);
    if (count != 0) {
        buf->unk15 |= 2;
        if (!(buf->unk15 & 1)) {
            buf->box_start = heapAlloc(count * 0x58);
        }
        entry = (CollisionAssetTri *)(asset->unk4C + (u8 *)asset + 4);
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
        i = 0;
        if (count > 0) {
            do {
                if (entry->unk14 == -1) {
                    if (collisionTransformTriangle(entry, out, slotMtx) != 0) {
                        out++;
                    }
                } else {
                    if (lastBone != entry->unk14) {
                        modelBuildBoneChainMatrix((s32 *)((entry->unk14 << 5) + boneTable), animFrame, boneMtx);
                        guMtxCatF(boneMtx, slotMtx, boneWorldMtx);
                        lastBone = entry->unk14;
                    }
                    if (collisionTransformTriangle(entry, out, boneWorldMtx) != 0) {
                        out++;
                    }
                }
                i++;
                entry++;
            } while (i != count);
        }
        buf->box_end = out;
    } else {
        buf->box_start = NULL;
        buf->box_end = NULL;
    }
    buf->unk15 |= 1;
    buf->unk10 = gFrameCounter;
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
    ModelSlot *entry;

    entry = (ModelSlot *)((u8 *)gModelSlots + slot * sizeof(ModelSlot)); // FAKE: byte-offset spelling keeps the slot * 0x90 product in t9 and gModelSlots in t8 (&gModelSlots[slot] swaps them)
    if (entry->unk78 != NULL) {
        animFrame = entry->unk78->frames[gGfxBufferIndex];
    } else {
        animFrame = 0;
    }
    boneTable = entry->unk24->unk60 + (u8 *)entry->unk24;
    modelSlotGetTransformVectors(slot, &posX, &posY, &posZ, &rotX, &rotY, &rotZ, &scale, &yOffset, 0);
    guScaleF(mtx, scale, scale, scale);
    guRotateF(tmpMtx, rotX, 1.0f, 0.0f, 0.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guRotateF(tmpMtx, rotY, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guRotateF(tmpMtx, rotZ, 0.0f, 0, 1.0f); // FAKE: int 0 makes this call load a2/a3 with li 0; with 0.0f both copy the zero CSE'd in $f0, which then moves to callee-saved $f20 (extra sdc1/ldc1)
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
    if (buf->box_start != NULL && (buf->unk15 & 1)) {
        heapFree(buf->box_start);
    }
    buf->unk15 &= ~1;
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
    D_807FB549 = 0;
    if (header->unk9 & 1) {
        compressed = data;
        data = heapAlloc(header->unk0);
        gzWork = heapAlloc(0x2400);
        gzOut = data;
        gzIn = compressed;
        gunzip(&gzIn, &gzOut, gzWork);
        heapFree(gzWork);
        assetSetImmediateFree();
        assetFreeBuffer(compressed, 0x14C, 0xA);
        D_807FB549 = 1;
    }
    assetSize = assetGetSize(2, gCurrentMap);
    D_807FB530 = *(s32 *)data;
    D_807FB534 = heapAlloc(0x1518);
    cellHeader = (s32 *)(data + 4);
    D_807FB538 = header->unk10 * header->unk12;
    for (i = 0; i < D_807FB538; i++) {
        cellStart = data + cellEnd + 4;
        cellEnd = *cellHeader;
        next = data + cellEnd;
        if (D_807FB549 != 0) {
            D_807FB534[i].unk4 = cellStart;
        } else {
            D_807FB534[i].unk4 = NULL;
        }
        D_807FB534[i].unk0 = NULL;
        relativeOffset = cellStart - data;
        D_807FB534[i].unkC = assetSize + relativeOffset;
        D_807FB534[i].unk10 = (data + cellEnd) - cellStart;
        cellHeader = (s32 *)next;
        D_807FB534[i].unk8 = 0;
        D_807FB534[i].unk14 = (next - cellStart) / 24;
    }
    if (D_807FB549 == 0) {
        assetSetImmediateFree();
        assetFreeBuffer(data, 0x17C, 0xA);
    }
}


void collisionLoadStaticCell(s32 cell) {
    s32 size;
    s32 pad;
    void *dst;
    void *src;
    s32 cnt;

    if (D_807FB534[cell].unk0 == NULL && cell < D_807FB538) {
        size = D_807FB534[cell].unk10;
        if (size != 0) {
            if (D_807FB549 == 0) {
                D_807FB534[cell].unk4 = heapAlloc(size);
                dmaReadAssetDecompress(D_807FB534[cell].unkC, D_807FB534[cell].unk4, &size, 0, 0, 0, 0);
            }
            cnt = D_807FB534[cell].unk14;
            D_807FB534[cell].unk0 = heapAlloc(cnt * 0x28);
            src = D_807FB534[cell].unk4;
            dst = D_807FB534[cell].unk0;
            for (; cnt != 0; cnt--) {
                if (collisionBuildStaticTri(src, dst) != 0) {
                    dst = (void *)((u8 *)dst + 0x28);
                }
                src = (void *)((u8 *)src + 0x18);
            }
        }
    }
    D_807FB534[cell].unk8 = gFrameCounter;
}

extern s32 gModelSlotCount;
extern s16 D_80748E40;


void modelSlotExpireNextBuffers(void) {
    DynamicBuffer *buf;
    ModelTriBuffer *triBuf;

    if (gModelSlotCount != 0) {
        D_80748E40++;
        if (D_80748E40 >= gModelSlotCount) {
            D_80748E40 = 0;
        }
        buf = &gModelSlots[D_80748E40].unk28;
        if ((buf->unk15 & 1) && ((gFrameCounter - buf->unk10) >= 0x1F)) {
            dynamicBufferFree(buf);
        }
        triBuf = &gModelSlots[D_80748E40].unk48;
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

    for (i = 0; i < D_807FB538; i++) {
        if (D_807FB534[i].unk0 != NULL && (gFrameCounter - D_807FB534[i].unk8) >= 0x15) {
            if (D_807FB549 == 0) {
                heapFree(D_807FB534[i].unk4);
                D_807FB534[i].unk4 = NULL;
            }
            heapFree(D_807FB534[i].unk0);
            D_807FB534[i].unk0 = NULL;
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

    guMtxXFMF(mtx, (f32)tri->unk0, (f32)tri->unk2, (f32)tri->unk4, &x0, &y0, &z0);
    verts[0] = (s32)x0;
    verts[1] = (s32)y0;
    verts[2] = (s32)z0;
    guMtxXFMF(mtx, (f32)tri->unk6, (f32)tri->unk8, (f32)tri->unkA, &x1, &y1, &z1);
    verts[3] = (s32)x1;
    verts[4] = (s32)y1;
    verts[5] = (s32)z1;
    guMtxXFMF(mtx, (f32)tri->unkC, (f32)tri->unkE, (f32)tri->unk10, &x2, &y2, &z2);
    verts[6] = (s32)x2;
    verts[7] = (s32)y2;
    verts[8] = (s32)z2;
    if (collisionIsTriangleDegenerate((CollisionTri *)verts) != 0) {
        return 0;
    }
    if (tri->unk12 & 1) {
        out->unk4D = 1;
    } else {
        out->unk4D = 0;
    }
    if (tri->unk12 & 2) {
        out->unk4F = tri->unk13;
    } else {
        out->unk4F = 0;
    }
    if (tri->unk12 & 4) {
        out->unk51 = 1;
    } else {
        out->unk51 = 0;
    }
    if (tri->unk12 & 8) {
        out->unk50 = 5;
    } else {
        out->unk50 = 0xFF;
    }
    out->unk4E = tri->unk14;
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
    out->unk4B = collisionTriangleSlopeClass(verts);
    out->unk48 = verts[9];
    out->unk4C = axisOut[0];
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


typedef struct CollisionStaticTriIn {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
} CollisionStaticTriIn;

typedef struct CollisionStaticTriOut {
    /* 0x00 */ s64 nx;
    /* 0x08 */ s64 ny;
    /* 0x10 */ s64 nz;
    /* 0x18 */ s64 d;
    /* 0x20 */ f32 len;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
} CollisionStaticTriOut;

s32 collisionBuildStaticTri(void *inData, void *outData) {
    CollisionBox work;
    CollisionStaticTriIn *in = inData;
    CollisionStaticTriOut *out = outData;
    s16 y1;
    s16 y;
    s16 y2;

    work.x0 = in->unk0;
    work.y0 = in->unk2;
    work.z0 = in->unk4;
    work.x1 = in->unk6;
    work.y1 = in->unk8;
    work.z1 = in->unkA;
    work.x2 = in->unkC;
    work.y2 = in->unkE;
    work.z2 = in->unk10;

    work.x0 *= 8; work.y0 *= 8; work.z0 *= 8;
    work.x1 *= 8; work.y1 *= 8; work.z1 *= 8;
    work.x2 *= 8; work.y2 *= 8; work.z2 *= 8;

    work.unk48 = in->unk12;
    work.unk4C = in->unk14;
    work.unk4D = 0;
    work.unk4F = 0;
    if (in->unk16 & 4) {
        work.unk51 = 1;
    } else {
        work.unk51 = 0;
    }
    work.unk50 = in->unk15;
    work.unk4B = 1;
    collisionBuildPlane(&work);

    out->nx = work.nx;
    out->ny = work.ny;
    out->nz = work.nz;
    out->d = work.d;
    out->len = work.len;

    y1 = in->unk8;
    y = in->unk2;
    if (y < y1) {
        out->unk24 = y;
    } else {
        out->unk24 = y1;
    }
    y = out->unk24;
    y2 = in->unkE;
    if (y < y2) {
        out->unk24 = y;
    } else {
        out->unk24 = y2;
    }
    if (y1 == 0) {} // FAKE: extends y1 so it interferes with y2 and takes $a0

    y1 = in->unk8;
    y = in->unk2;
    if (y1 < y) {
        out->unk26 = y;
    } else {
        out->unk26 = y1;
    }
    y2 = in->unkE;
    y = out->unk26;
    if (y2 < y) {
        if (y2 == 0) {} // FAKE: extra use raises y2 priority so it takes $v0
        out->unk26 = y;
    } else {
        out->unk26 = y2;
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
    /* 0x54 */ s16 unk54;
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 pad57;
} ActorSub140Tri; // size = 0x58

typedef struct ActorSub140SrcTri {
    /* 0x00 */ f32 x[9];
    /* 0x24 */ u32 boneOffset;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B;
} ActorSub140SrcTri; // size = 0x2C

ActorSub140 *actorSub140CreateFromData(f32 x, f32 y, f32 z, f32 scale, f32 radius, f32 height, void *boxBounds, Mtx *mtx0, Mtx *mtx1, u8 *data) {
    ActorSub140 *sub140;
    void *link;
    s32 n;
    s32 i;
    s32 pad1;
    s32 pad[10];
    void *tris;
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
                node->unk24 = 0;
                node->unk27 = 0;
                data += 0x14;
                *(void **)link = node;
                link = &node->next;
                i++;
            } while (i != n);
            i = 0;
        }

        n = *(s32 *)data;
        data += 4;
        if (n > 0) {
            link = &sub140->subNodes;
            do {
                subnode = heapAlloc(sizeof(ModelSubNode));
                subnode->next = NULL;
                subnode->x = *(f32 *)data;
                subnode->y = *((f32 *)data + 1);
                subnode->z = *((f32 *)data + 2);
                subnode->unk18 = *((s32 *)data + 3);
                data += 0x10;
                *(void **)link = subnode;
                link = &subnode->next;
                i++;
            } while (i != n);
            i = 0;
        }

        count = *(s32 *)data;
        data += 4;
        sub140->boxCount = count;
        if (count != 0) {
            sub140->boxes = (srcTri = heapAlloc(count * sizeof(ActorSub140SrcTri)));
            sub140->unkA4 = heapAlloc(count * sizeof(ActorSub140Tri));
            sub140->unkA8 = sub140->unkA4;
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
                srcTri->unk28 = *(s32 *)(rec + k);
                srcTri->boneOffset = *(s32 *)(rec + (k + 1));
                srcTri->unk2A = 1;
                data += 0x2C;
                srcTri++;
            } while (++i != count);
            i = 0;
        }

        count = *(s32 *)data;
        data += 4;
        sub140->triangleCount = count;
        if (count != 0) {
            tris = heapAlloc(count * sizeof(ActorSub140Tri));
            sub140->triangles = tris;
            triBase = tris;
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
                tri->unk54 = *(s32 *)(rec + k);
                tri->boneOffset[0] = *(s32 *)(rec + (k + 1));
                tri->boneOffset[1] = *(s32 *)(rec + (k + 2));
                tri->boneOffset[2] = *(s32 *)(rec + (k + 3));
                tri->unk56 = 1;
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
        node->unk24 = value;
    }
}

void actorOrNodeFlags(Actor *actor, s32 index, u8 flags) {
    ModelNode *node;

    node = actorGetModelNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk27 |= flags;
    }
}

void actorClearNodeFlags(Actor *actor, s32 index, u8 flags) {
    ModelNode *node;

    node = actorGetModelNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk27 &= ~flags;
    }
}

void func_8066E664(Actor *actor, s32 id, u8 value) {
    ActorSub140 *sub;
    ActorSub140SrcTri *ent;
    s32 i;

    sub = actor->collision;
    if (actor->collision != NULL) { // FAKE: second read of unk140 keeps the sub copy in $v0
        ent = sub->boxes;
        for (i = 0; i < sub->boxCount; i++) {
            if (id == ent[i].unk28) {
                ent[i].unk2A = value;
            }
        }
    }
}

void func_8066E6C8(Actor *actor, s32 id, u8 enabled) {
    ActorSub140 *sub;
    ActorSub140Tri *ent;
    s32 i;

    sub = actor->collision;
    if (actor->collision != NULL) { // FAKE: second read of unk140 keeps the sub copy in $v0
        ent = sub->triangles;
        for (i = 0; i < sub->triangleCount; i++) {
            if (id == ent[i].unk54) {
                ent[i].unk56 = enabled;
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
    sub->unk7C = -1;
    sub->unk80 = -2;
    sub->unk84 = -1;
    sub->unk88 = -1;
    sub->unk60 = 0;
    sub->unk6C = 0;
    sub->unk24 = 0;
    sub->nodes = NULL;
    sub->subNodes = NULL;
    sub->triangleCount = 0;
    sub->triangles = NULL;
    sub->boxCount = 0;
    sub->boxes = NULL;
    sub->unkA4 = 0;
    sub->unkA8 = 0;
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
    node->unk18 = value;
    node->unkC = 0;
    node->unk10 = 0;
    node->unk14 = 0;
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
    node->unk24 = 0;
    node->unk27 = 0;
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
        scale = actor->unk120;
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
    s32 none;
    s32 i;
    ActorSub140SrcTri *ent;
    Mtx *mtx;
    u8 bufIdx;
    float boundsMtx[4][4];
    f32 *src;
    f32 *outZ;
    f32 *outX;
    f32 *outY;
    u32 boneOffset;
    s32 padB[10];
    CollisionBox *box;
    f32 boxZ[3];
    f32 boxY[3];
    f32 boxX[3];
    s32 padE[5];

    none = -1; // FAKE: value-named -1 local keeps the constant in $s6 for both bone compares
    if (sub->boxes != NULL) {
        if (gFrameCounter == sub->unk88) {
            bufIdx = gGfxBufferIndex;
        } else {
            bufIdx = (gGfxBufferIndex ^ 1);
        }
        mtx = sub->nodeMtx[bufIdx];
        ent = sub->boxes;
        box = sub->unkA4;
        i = 0;
        if (sub->boxCount > 0) {
            do {
                if (sub == 0) {} // FAKE
                src = ent->x;
                outX = boxX;
                outY = boxY;
                outZ = boxZ;
                do {
                    boneOffset = ent->boneOffset;
                    if (none == boneOffset) {
                        memcpy(boundsMtx, sub->modelMtxF, 0x40);
                        guMtxXFMF(boundsMtx, src[0], src[3], src[6], outX, outY, outZ);
                    } else {
                        guMtxXFML((Mtx *)(((boneOffset >> 6) << 6) + (u8 *)mtx), src[0], src[3], src[6], outX, outY, outZ);
                    }
                    outZ++;
                    src++;
                    outX++;
                    outY++;
                } while (outZ != (f32 *)&box); // FAKE: sentinel = addiu fp,sp,0x8C (the frame slot after boxZ at sp+0x80), steers a lone hoisted constant
                if (collisionBuildBoxFromMatrix(boxX, box) != 0) {
                    if (ent->unk2A == 0) {
                        box->unk4B = 0;
                    }
                    if (ent->boneOffset == none) {
                        box->unk4E = none;
                    } else {
                        box->unk4E = (s8)(ent->boneOffset >> 6);
                    }
                    box++;
                }
                ent++;
                i++;
            } while (i < sub->boxCount);
        }
        sub->unkA8 = box;
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
    box->unk4B = collisionTriangleSlopeClass(verts);
    box->unk4D = 0;
    box->unk4F = 0;
    box->unk51 = 0;
    box->unk50 = 0xFF;
    box->unk48 = yaw;
    box->unk4C = axisOut[0];
    collisionBuildPlane(box);
    return 1;
}

void actorSub140TransformTriangles(ActorSub140 *sub) {
    ActorSub140Tri *first;
    s32 i;
    u8 bufIdx;
    ActorSub140Tri *curr;
    Mtx *mtx;
    float boundsMtx[4][4];
    s32 j;
    u32 boneOffset;

    first = sub->triangles;
    if (first != NULL) {
        if (gFrameCounter == sub->unk88) {
            bufIdx = gGfxBufferIndex;
        } else {
            bufIdx = (gGfxBufferIndex ^ 1);
        }
        mtx = sub->nodeMtx[bufIdx];
        curr = first;
        for (i = 0; i < sub->triangleCount; i++) {
            for (j = 0; j < 3; j++) {
                boneOffset = curr->boneOffset[j];
                if ((boneOffset ^ 0) == -1) { // FAKE: ^ 0 steers bne operand order
                    memcpy(boundsMtx, sub->modelMtxF, 0x40);
                    guMtxXFMF(boundsMtx, curr->x[j], curr->x[j + 3], curr->x[j + 6], &curr->out[j], &curr->out[j + 3], &curr->out[j + 6]);
                } else {
                    guMtxXFML((Mtx *)((((boneOffset >> 6) << 6)) + (u8 *)mtx), curr->x[j], curr->x[j + 3], curr->x[j + 6], &curr->out[j], &curr->out[j + 3], &curr->out[j + 6]);
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

    D_807FB544 = angle;
    D_807FB540 = actor;
    D_807FB546 = 1;
    D_807FB604 = 1;
    actorCheckTargetAngle(actor, &arcMin, &arcMax, &actorHit);
    return D_807FB546;
}

u8 actorClearTargetAngle(Actor *actor, s16 *arcMin, s16 *arcMax, u8 *hit) {
    D_807FB604 = 0;
    return actorCheckTargetAngle(actor, arcMin, arcMax, hit);
}

extern PlayerStruct *gPlayerSlots;
extern u8 D_807FB547;
extern u8 D_807FB602;
extern u8 D_807FB605;
extern u8 D_807FB606;

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
    D_807FB602 = 0;
    D_807FB547 = 0;
    D_807FB605 = 0;
    D_807FB606 = 0;
    if (actor->unk144 & 0x20) {
        actorCollisionCheckNodeSpheres(actor);
    }
    if (actor->unk144 & 8) {
        boundsHit = actorCheckTargetAngleBounds(actor, arcMin, arcMax);
        slotHit = actorCollideModelSlots(actor, arcMin, arcMax);
        *actorHit = actorCheckCollisionsAgainstActiveActors(actor, arcMin, arcMax);
    } else {
        *actorHit = 0;
    }
    actorQueueCollisionCallbacks(actor);
    actor->collisionHit = D_807FB547;
    if (D_807FB606 != 0) {
        actor->renderFlags |= 0x100;
    } else {
        actor->renderFlags &= ~0x100;
    }
    return (boundsHit != 0) || (slotHit != 0);
}

void actorQueueCollisionCallbacks(Actor *actor) {
    if (D_807FB602) {
        if (actor->collisionFlags & 1) {
            PlayerState *player = actor->customState;
            if (player->surfaceTimer == 0) {
                if (D_807FB602 & 1) {
                    actorQueueDelayedCallback(actor, 0, 8, 0, 0, 0, 1);
                }
                if (D_807FB602 & 2) {
                    actorQueueDelayedCallback(actor, 0, 8, 0, 0, 0, 1);
                }
            }
        }
    }
}

s32 collisionSpheresOverlap(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80673708(s32, s32, s32, s32, CollisionBox *, CollisionBox *, s16 *, s16 *);
extern u8 D_807FB548;
extern u8 D_807FB5FD;
extern u8 D_807FB5FF;
extern u8 D_807FB600;
extern u8 D_807FB601;
extern u8 D_807FB61C;

u8 actorCollideModelSlots(Actor *actor, s16 *arcMin, s16 *arcMax) {
    u8 result;
    ModelNode *node;
    DynamicBuffer *buf;
    CsStateFull *hit;
    s32 i;
    ActorSub140 *sub;
    u8 savedFlags;
    u8 ret;
    u8 flag;

    result = 0;
    sub = actor->collision;
    sub->unk6C = 0;
    D_807FB548 = 0;
    for (i = 0; i < gModelSlotCount; i++) {
        buf = &gModelSlots[i].unk28;
        if (buf->unk15 & 2) {
            if (collisionSpheresOverlap(sub->scaledX, sub->scaledY, sub->scaledZ, sub->scaledRadius, buf->unk0, buf->unk4, buf->unk8, buf->unkC) != 0) {
                if (!(buf->unk15 & 1)) {
                    collisionTransformNode(i, gModelSlots[i].unk24, gModelSlots[i].x, gModelSlots[i].y, gModelSlots[i].z, gModelSlots[i].rotY, gModelSlots[i].unk14, gModelSlots[i].unk18, gModelSlots[i].scale);
                } else {
                    buf->unk10 = gFrameCounter;
                }
                if (!(actor->collisionFlags & 1) || playerSlotMatchesSizeMask(gModelSlots[i].unk24->unk0, ((PlayerState *)actor->customState)->playerIndex) == 0) {
                    actorUpdateCollisionSpheres(actor, 0);
                    flag = 1;
                    node = sub->nodes;
                    D_807FB5FD = 0;
                    savedFlags = D_807FB602;
                    hit = gModelSlots[i].unk7C;
                    if (hit != NULL) {
                        if (hit->unk6F != 0) {
                            D_807FB5FD = 1;
                            D_807FB600 = 0;
                        }
                        flag = gModelSlots[i].unk7C->unk70;
                    }
                    if ((D_807FB5FD == 0 || (actor->unk144 & 0x10)) && flag != 0) {
                        D_807FB5FF = 0;
                        ret = 0;
                        while (node != NULL && D_807FB5FF == 0) {
                            if (node->active != 0 && node->scaledRadius != 0 && !(node->unk27 & 6)) {
                                ret |= func_80673708(node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius, buf->box_start, buf->box_end, arcMin, arcMax);
                            }
                            node = node->next;
                        }
                        result |= ret;
                        if (D_807FB601 != 0) {
                            if (gModelSlots[i].unk7C != NULL) {
                                gModelSlots[i].unk7C->unk5C = D_807FB601;
                                gModelSlots[i].unk7C->unk5E = actor->actorType;
                            }
                        }
                        if (D_807FB5FF != 0) {
                            actorBuildCollisionHit(i, actor, buf->box_start);
                        }
                        if (gModelSlots[i].unk7C != NULL && gModelSlots[i].unk7C->unk6E == 0) {
                            D_807FB602 = savedFlags;
                        }
                        if (ret && D_807FB5FD == 0 && D_807FB61C != 0) {
                            actorUpdateSubActorOffsets(actor, 0);
                        }
                    }
                }
            }
        }
    }
    return result;
}


extern s32 D_807FB5C4;
extern s32 D_807FB5C8;
extern s32 D_807FB5CC;
extern s32 D_807FB5D0;
extern CollisionBox *D_807FB5D8;
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
    ok = func_806744A8(D_807FB5D8, sub->scaledX, sub->scaledY, sub->scaledZ, sub->scaledRadius);
    func_8066FE08(slot);
    if (ok != 0) {
        sub->unk5A = D_807FB5D8->unk4E;
        sub->unk58 = D_807FB5D8 - boxes;
        modelSlotBuildTransformMatrix(slot, D_807FB5D8->unk4E, mtx);
        matrix4Invert(inv, mtx);
        if (gModelSlots[slot].unk7C != NULL && (gModelSlots[slot].unk7C->unk9B & 0x24)) {
            useActorPos = 1;
        }
        if (useActorPos != 0) {
            px = actor->x;
            py = actor->y;
            pz = actor->z;
        } else {
            px = (f32)D_807FB5C4 / 8;
            py = (f32)D_807FB5C8 / 8;
            pz = (f32)D_807FB5CC / 8;
        }
        if (!(actor->flags & 0x800)) {
            guMtxXFMF(inv, px, py, pz, &sub->unk4C, &sub->unk50, &sub->unk54);
        }
        x[0] = (f32)D_807FB5D8->x0 / 8;
        y[0] = (f32)D_807FB5D8->y0 / 8;
        z[0] = (f32)D_807FB5D8->z0 / 8;
        x[1] = (f32)D_807FB5D8->x1 / 8;
        y[1] = (f32)D_807FB5D8->y1 / 8;
        z[1] = (f32)D_807FB5D8->z1 / 8;
        x[2] = (f32)D_807FB5D8->x2 / 8;
        y[2] = (f32)D_807FB5D8->y2 / 8;
        z[2] = (f32)D_807FB5D8->z2 / 8;
        for (i = 0; i < 3; i++) {
            guMtxXFMF(inv, x[i], y[i], z[i], &sub->unk28[i], &sub->unk34[i], &sub->unk40[i]);
        }
        sub->unk26 = gModelSlots[slot].id;
        sub->unk5C = D_807FB5D0;
        if (sub->unk5C < 0x14) {
            sub->unk5C = 0x14;
        }
        sub->unk64 = actorGetCollisionThreshold(actor);
        sub->unk66 = D_807FB5D8->unk48;
        if (D_807FB5D8->unk4C != 0) {
            sub->unk66 -= 0x800;
        }
        if (sub->unk66 < 0) {
            sub->unk66 += 0x1000;
        }
        sub->unk6C = 1;
        if (actor->collisionFlags & 1) {
            actorReflectCollisionAngle(actor, D_807FB5D8, sub);
        }
    }
}

void actorReflectCollisionAngle(Actor *actor, CollisionBox *box, ActorSub140 *coll) {
    PlayerState *sub = actor->customState;
    s64 total;
    s64 x_prod;
    s64 y_prod;
    sub->unkEA = box->unk48;
    y_prod = box->ny * coll->scaledY;
    x_prod = box->nx * coll->scaledX;
    total = (box->nz * coll->scaledZ) + x_prod + y_prod + box->d;
    if (box->d > 0) {
        if (total <= 0) {
            sub->unkEA += 0x800;
        }
    } else if (total >= 0) {
        sub->unkEA += 0x800;
    }
    sub->unkEA &= 0xFFF;
}

s32 actorGetCollisionThreshold(Actor *actor) {
    switch (actor->actorType) {
    case 5: {
        PlayerState *sub = actor->customState;
        if (gPlayerSlots[sub->playerIndex].unk2C0 == 1) {
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

void func_8066FE08(s32 slot) {
    s16 yaw;
    s16 actorYaw;
    s32 inArc;
    s32 kind;
    CsStateFull *sub;
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
    if (gModelSlots[slot].unk7C != NULL && D_807FB5D8->unk4D != 0) {
        sub = gModelSlots[slot].unk7C;
        kind = sub->unk50;
        switch (kind) {
        case 0:
            break;
        case 1:
            sub->unk51 = 1;
            yaw = D_807FB5D8->unk48;
            if (D_807FB5D8->unk4C != 0) {
                yaw -= 0x800;
            }
            if (yaw < 0) {
                yaw += 0x1000;
            }
            actorYaw = gCurrentActor->yaw;
            yawDiff = (s16)(yaw - actorYaw);
            yaw = (1 | inArc) ? yaw : yaw + 1; // FAKE: redefines yaw (always-true condition folds) so uopt does not forward yawDiff's store into the sign test
            if (yawDiff < 0) {
                yawDiff = (s16)-yawDiff;
            }
            if (yawDiff >= 0x801) {
                yawDiff = (s16)(0xFFF - yawDiff);
            }
            arcMax = sub->unk8A;
            if (yawDiff) {} // FAKE: dead use raises yawDiff adjsave so it is coloured before actorYaw/arcMax
            arcMin = sub->unk88;
            if (arcMax >= arcMin) {
                if (actorYaw >= arcMin && arcMax >= actorYaw) {
                    inArc = 1;
                }
            } else if (actorYaw >= arcMin || arcMax >= actorYaw) {
                inArc = 1;
            }
            if (yawDiff < 0x258 && inArc != 0) {
                angle = (f32)(((f64)yaw / 4095.0) * 6.2831854820251465);
                yaw = 0; // FAKE: dead store to angle's operand kills store-forwarding so angle stays a variable (spilled to its own home 0x44)
                sub->unk8C = sinApprox(angle);
                sub->unk90 = cosApprox(angle);
                sub->unk52 = 1;
                return;
            }
            break;
        case 2:
            sub->unk51 = 1;
            yaw = D_807FB5D8->unk48;
            if (D_807FB5D8->unk4C != 0) {
                yaw -= 0x800;
            }
            if (yaw < 0) {
                yaw += 0x1000;
            }
            actorYaw = gCurrentActor->yaw;
            yawDiff = (s16)(yaw - actorYaw);
            yaw = 0; // FAKE: dead store (yaw unused below) so uopt does not forward yawDiff's store into the sign test
            if (yawDiff < 0) {
                yawDiff = (s16)-yawDiff;
            }
            if (yawDiff >= 0x801) {
                yawDiff = (s16)(0xFFF - yawDiff);
            }
            arcMax = sub->unk8A;
            if (yawDiff) {} // FAKE: dead use raises yawDiff adjsave so it is coloured before actorYaw/arcMax
            arcMin = sub->unk88;
            if (arcMax >= arcMin) {
                if (actorYaw >= arcMin && arcMax >= actorYaw) {
                    inArc = 1;
                }
            } else if (actorYaw >= arcMin || arcMax >= actorYaw) {
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
                px = (f32)D_807FB5C4 / 8;
                py = (f32)D_807FB5C8 / 8;
                pz = (f32)D_807FB5CC / 8;
                guMtxXFMF(inv, px, py, pz, &localX, &localY, &localZ);
                guScaleF(mtx, scale, scale, scale);
                guRotateF(tmp, rotX, 1.0f, 0.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, (f32)((f64)rotY + 1.0), 0.0f, 1.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, rotZ, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
                guTranslateF(tmp, posX, posY, posZ);
                guMtxCatF(mtx, tmp, mtx);
                guMtxXFMF(mtx, localX, localY, localZ, &plusX, &plusY, &plusZ);
                guScaleF(mtx, scale, scale, scale);
                guRotateF(tmp, rotX, 1.0f, 0.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, (f32)((f64)rotY - 1.0), 0.0f, 1.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, rotZ, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
                guTranslateF(tmp, posX, posY, posZ);
                guMtxCatF(mtx, tmp, mtx);
                guMtxXFMF(mtx, localX, localY, localZ, &minusX, &minusY, &minusZ);
                minusDist = (f32)camDistance3D((s32)gCurrentActor->x, (s32)gCurrentActor->y, (s32)gCurrentActor->z, (s32)minusX, (s32)minusY, (s32)minusZ);
                if (minusDist < (f32)camDistance3D((s32)gCurrentActor->x, (s32)gCurrentActor->y, (s32)gCurrentActor->z, (s32)plusX, (s32)plusY, (s32)plusZ)) {
                    sub->unk52 = 1;
                    return;
                }
                sub->unk52 = 2;
            }
            break;
        }
    }
}

typedef struct ActorHitRecord {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ u8 pad4[0x30];
} ActorHitRecord; // size = 0x34

extern u8 D_807FB603;
extern ActorHitRecord D_807FD614[];
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
    CsStateFull *hit;

    {
        u8 kind;

        kind = 0;
        sub = actor->collision;
        ret = 0;
        slot = hashTableLookup(sub->unk26);
        if (slot != -1) {
            buf = &gModelSlots[slot].unk28;
            if (!(buf->unk15 & 1)) {
                return 0;
            }
            D_807FB603 = buf->unk14;
            D_807FB5FD = 1;
            D_807FB600 = 1;
            D_807FB602 = 0;
            func_80672E90(sub->scaledX, sub->scaledY, sub->scaledZ);
            actorSetCameraBoundaryMode(actor->actorType);
            hit = gModelSlots[slot].unk7C;
            if (hit != NULL) {
                if (hit->unk9B & 4) {
                    kind = 1;
                }
                if (hit->unk9B & 8) {
                    kind = 2;
                }
                if (hit->unk9B & 0x10) {
                    kind = 3;
                }
                if (hit->unk9B & 0x20) {
                    kind = 4;
                }
            }
            if (hit != NULL && hit->unk53 != 0) {
                ret = func_80673708(sub->scaledX, sub->scaledY, sub->scaledZ, sub->unk5C, buf->box_start, buf->box_end, &actor->arcYawMin, &actor->arcYawMax) & 0xFF;
            } else {
                actorSetTargetAngleBounds(buf->box_start + sub->unk58);
                switch (kind) {
                case 0:
                    ret = func_806738D0(sub->scaledX, sub->scaledY, sub->scaledZ, sub->unk5C, buf->box_start, buf->box_end) & 0xFF;
                    func_80673708(sub->scaledX, sub->scaledY, sub->scaledZ, sub->unk5C, buf->box_start, buf->box_end, &actor->arcYawMin, &actor->arcYawMax);
                    break;
                case 1:
                case 2:
                    ret = func_80673708(sub->scaledX, sub->scaledY, sub->scaledZ, sub->unk5C, buf->box_start, buf->box_end, &actor->arcYawMin, &actor->arcYawMax) & 0xFF;
                    break;
                case 3:
                case 4:
                    ret = func_80673708(sub->scaledX, sub->scaledY, sub->scaledZ, 0x64, buf->box_start, buf->box_end, &actor->arcYawMin, &actor->arcYawMax) & 0xFF;
                    break;
                }
            }
            if (D_807FB601 != 0 && hit != NULL) {
                gModelSlots[slot].unk7C->unk5C = D_807FB601;
                gModelSlots[slot].unk7C->unk5E = actor->actorType;
            }
            if (gModelSlots[slot].unk7C != NULL && gModelSlots[slot].unk7C->unk6E != 0) {
                actorQueueCollisionCallbacks(actor);
            }
            if (hit != NULL && hit->unk53 != 0 && D_807FD614[playerFindIndexByActor(actor)].unk0 > 30.0) {
                ret = 1;
            }
            if (actor->collisionFlags & 1) {
                actorCalcPlaneContactPoint(actor, slot, sub);
            }
            if (ret != 0) {
                modelSlotBuildTransformMatrix(slot, sub->unk5A, mtx);
                guMtxXFMF(mtx, sub->unk4C, sub->unk50, sub->unk54, &x, &y, &z);
                if (kind == 1 || kind == 4) {
                    actor->x = x;
                    actor->z = z;
                } else {
                    for (i = 0; i < 3; i++) {
                        guMtxXFMF(mtx, sub->unk28[i], sub->unk34[i], sub->unk40[i], &px[i], &py[i], &pz[i]);
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
                    if (sub->unk60 != 0) {
                        D_807FB5D0 = sub->unk60 + 5;
                        if (sub->unk64 < D_807FB5D0) {
                            D_807FB5D0 = sub->unk64;
                        }
                    } else {
                        D_807FB5D0 = sub->unk5C;
                        if (D_807FB5D0 < 0xF) {
                            D_807FB5D0 = 0xF;
                        }
                        if (sub->unk64 < D_807FB5D0) {
                            D_807FB5D0 = sub->unk64;
                        }
                    }
                    if (kind == 3) {
                        D_807FB5D0 = 0x46;
                    }
                    sub->unk60 = D_807FB5D0;
                    scale = (f32)D_807FB5D0 / 8;
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

extern s16 D_80753D50[];
extern s16 D_80753D60[];
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
    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
        radius = D_80753D50[gCurrentCharacterIndex];
    } else {
        radius = D_80753D60[gCurrentCharacterIndex];
    }

    modelSlotBuildTransformMatrix(slot, hit->unk5A, mtx);
    guMtxXFMF(mtx, hit->unk4C, hit->unk50, hit->unk54, &originX, &originY, &originZ);

    for (i = 0; i < 3; i++) {
        guMtxXFMF(mtx, hit->unk28[i], hit->unk34[i], hit->unk40[i], &triX[i], &triY[i], &triZ[i]);
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

    player->unkE0 = originX - out[0];
    player->unkE4 = originZ - out[2];
    player->stateStep = 1;
}

extern s16 D_807FB5EC;
extern s16 D_807FB5EE;
extern s16 D_807FB5F0;
extern s16 D_807FB5F2;

void actorSetTargetAngleBounds(CollisionBox *box) {
    s16 yaw;

    yaw = box->unk48;
    D_807FB5EC = yaw - 0x32;
    if (D_807FB5EC < 0) {
        D_807FB5EC += 0xFFF;
    }
    D_807FB5EE = yaw + 0x32;
    if (D_807FB5EC >= 0x1000) {
        D_807FB5EE -= 0xFFF;
    }
    D_807FB5F0 = D_807FB5EC + 0x800;
    if (D_807FB5F0 >= 0x1000) {
        D_807FB5F0 -= 0xFFF;
    }
    D_807FB5F2 = D_807FB5EE + 0x800;
    if (D_807FB5F2 >= 0x1000) {
        D_807FB5F2 -= 0xFFF;
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

    sub->unk24 = 0;
    D_807FB548 = 0;

    if (func_806730A4(sub->scaledX, sub->scaledY, sub->scaledZ, sub->scaledRadius) != 0) {
        if (actor->renderFlags & 0x80) {
            D_807FB605 = 1;
        }
        actorUpdateCollisionSpheres(actor, 0);
        node = sub->nodes;
        while (node != NULL) {
            if (node->active != 0 && node->scaledRadius != 0 && !(node->unk27 & 1)) {
                ret |= func_806734E4(node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius, arcMin, arcMax);
            }
            node = node->next;
        }
        if ((ret != 0 || D_807FB605 != 0) && D_807FB61C != 0) {
            actorUpdateCollisionExtents(actor);
        }
        D_807FB605 = 0;
    }
    return ret;
}

extern PlayerState *gActivePlayerState;
extern s32 D_807FB5DC;
extern s16 D_807FB5F6;

CollisionBox *func_806732A8(s32, s16); // asm (77B90): returns the hit box left in s0

void actorUpdateFacingAndOffset(CollisionBox *box, s32 unused1, s32 unused2, s32 unused3) {
    s16 facingDist;
    s32 offsetX;
    s32 pad2C;
    s32 prevThreshold;
    s32 backDist;
    ActorSub140 *sub;
    f32 cosYaw;
    s32 threshold;

    facingDist = mathAngleDistance(box->unk48, D_807FB544);
    backDist = mathAngleDistance((box->unk48 + 0x800) & 0xFFF, D_807FB544);
    if ((facingDist < 0x321) || (backDist < 0x321)) {
        mathAngleDistance(box->unk48, gActivePlayerState->unkEA);
        mathAngleDistance((box->unk48 + 0x800) & 0xFFF, gActivePlayerState->unkEA);
        sub = D_807FB540->collision;
        func_806744A8(box, sub->scaledX, sub->scaledY, sub->scaledZ, sub->scaledRadius);
        prevThreshold = D_807FB5D0;
        offsetX = (s32)(mathSinF(D_807FB544) * 20.0f);
        cosYaw = mathCosF(D_807FB544);
        sub = D_807FB540->collision;
        func_806744A8(box, sub->scaledX + offsetX, sub->scaledY, sub->scaledZ + (s32)(cosYaw * 20.0f), sub->scaledRadius);
        threshold = D_807FB5D0;
        if (prevThreshold - 2 < threshold) {
            D_807FB546 = 0;
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

    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
        radius = D_80753D50[gCurrentCharacterIndex];
    } else {
        radius = D_80753D60[gCurrentCharacterIndex];
    }
    if (actor->collisionFlags & 1) {
        f32 scale;
        f32 hitX;
        f32 hitZ;

        player = actor->customState;
        actorComputeBoxNormal(actor, &nx, &ny, &nz, 1);
        scale = radius / 8;
        hitX = (f32)D_807FB5C4 / 8;
        hitZ = (f32)D_807FB5CC / 8;
        nx *= scale;
        ny *= scale;
        nz *= scale;
        player->unkE0 = hitX - nx;
        player->unkE4 = hitZ - nz;
        player->stateStep = 1;
        actorReflectCollisionAngle(actor, func_806732A8(D_807FB5DC, D_807FB5F6), actor->collision);
    }
    actorUpdateSubActorOffsets(actor, 1);
}

void actorUpdateSubActorOffsets(Actor *actor, u8 useHitBox) {
    if (D_807FB5D0 < actorGetPlayerThreshold(actor)) {
        ActorSub140 *sub = actor->collision;
        f32 targetX;
        f32 scale;
        f32 targetZ;
        f32 normalZ;
        f32 normalY;
        f32 normalX;

        actorComputeBoxNormal(actor, &normalX, &normalY, &normalZ, useHitBox);
        targetX = (f32)D_807FB5C4 / 8;
        targetZ = (f32)D_807FB5CC / 8;
        if (D_807FB548 != 0) {
            scale = (f32)actorGetPlayerThreshold(actor) / 8;
            normalX *= scale;
            normalZ *= scale;
        } else {
            scale = (f32)(D_807FB5D0 + 6) / 8;
            normalX *= scale;
            normalZ *= scale;
        }
        sub->unk1C = targetX - normalX;
        sub->unk20 = targetZ - normalZ;
        sub->unk24 = 1;
    }
}

extern CollisionBox *D_807FB5D4;

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
        box = func_806732A8(D_807FB5DC, D_807FB5F6);
    } else {
        box = D_807FB5D4;
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
            D_807FB5C4 = sub->unkB0;
            D_807FB5CC = sub->unkB4;
        }
        sub->unkB0 = D_807FB5C4;
        sub->unkB4 = D_807FB5CC;
    }
}

s32 actorGetPlayerThreshold(Actor *actor) {
    PlayerState *player;

    switch (actor->actorType) {
    case 5:
        player = actor->customState; // type 5: the player actor's state
        if (gPlayerSlots[player->playerIndex].unk2C0 != 1) {
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
    s32 base;
    u8 idx;

    if (force != 0 || sub->unk7C != sub->unk80) {
        if (actor->sub4 != NULL) {
            scale = actor->sub4->scaleY;
        }
        if (actor->renderFlags & 0x800) {
            scale = actor->unk120;
        }
        if (gFrameCounter == sub->unk88) {
            idx = gGfxBufferIndex;
        } else {
            idx = gGfxBufferIndex ^ 1;
        }
        node = sub->nodes;
        base = (s32)sub->nodeMtx[idx];
        if (base) {} // FAKE: raises base coloring priority (swaps s5/s6)
        while (node != NULL) {
            if (node->mtxOffset == -1) {
                memcpy(mtx, sub->modelMtxF, 0x40);
                guMtxXFMF(mtx, node->x, node->y, node->z, &outX, &outY, &outZ);
            } else {
                guMtxXFML((Mtx *)((((u32)node->mtxOffset >> 6) << 6) + base), node->x, node->y, node->z, &outX, &outY, &outZ);
            }
            node->scaledX = outX * 8.0f;
            node->scaledY = outY * 8.0f;
            node->scaledZ = outZ * 8.0f;
            node->scaledRadius = node->scale * scale * 8.0f;
            node = node->next;
        }
        sub->unk7C = sub->unk80;
    }
}

void actorUpdateNodePositions(ActorSub140 *sub, u8 force) {
    ModelSubNode *node;
    u8 bufIdx;
    f32 outX;
    f32 outY;
    f32 outZ;
    f32 mtx[4][4];
    u8 *mtxBase;

    if (force || (gFrameCounter != sub->unk84)) {
        if (gFrameCounter == sub->unk88) {
            bufIdx = gGfxBufferIndex;
        } else {
            bufIdx = gGfxBufferIndex ^ 1;
        }
        node = sub->subNodes;
        mtxBase = (u8 *)sub->nodeMtx[bufIdx];
        if (node != NULL) {
            if (mtxBase) {} // FAKE: raises mtx_base register priority so -1 gets s5, mtx_base s6
            do {
                if (node->unk18 == -1) {
                    memcpy(&mtx, sub->modelMtxF, sizeof(mtx));
                    guMtxXFMF(mtx, node->x, node->y, node->z, &outX, &outY, &outZ);
                } else {
                    guMtxXFML((Mtx *)(mtxBase + (((u32)node->unk18 >> 6) << 6)), node->x, node->y, node->z, &outX, &outY, &outZ);
                }
                node->unkC = outX * 8.0f;
                node->unk10 = outY * 8.0f;
                node->unk14 = outZ * 8.0f;
                node = node->next;
            } while (node != NULL);
        }
        sub->unk84 = gFrameCounter;
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
        *outX = (f32)node->unkC / 8;
        *outY = (f32)node->unk10 / 8;
        *outZ = (f32)node->unk14 / 8;
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

    if (gFrameCounter == sub->unk88) {
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

    return (((u32)node->unk18 >> 6) << 6) + base;
}


u8 collisionTestSphere(f32 x, f32 y, f32 z, f32 radius, s16 *arcMin, s16 *arcMax, u8 testSlots, u16 boundaryMode) {
    u8 ret;

    x *= 8.0f;
    y *= 8.0f;
    z *= 8.0f;
    *arcMin = 0;
    *arcMax = 0xFFF;
    radius *= 8.0f;
    D_807FB606 = 0;
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
extern s32 D_807FB53C;



u8 collisionTestSphereSlots(f32 fx, f32 fy, f32 fz, f32 fradius, s16 *arcMin, s16 *arcMax) {
    s32 x;
    s32 y;
    s32 z;
    s32 radius;
    u8 result;
    s32 i;
    DynamicBuffer *buf;
    CsStateFull *hitInfo;

    result = 0;
    D_807FB5FD = 0;
    i = 0;
    if (gModelSlotCount > 0) {
        do {
            buf = &gModelSlots[i].unk28;
            if (buf->box_start != NULL &&
                (D_807FB53C != 0xBC || (gModelSlots[i].unk48.flags & 2))) {
                x = fx;
                y = fy;
                z = fz;
                radius = fradius;
                if (collisionSpheresOverlap(x, y, z, radius,
                                  buf->unk0,
                                  buf->unk4,
                                  buf->unk8,
                                  buf->unkC) != 0 &&
                    (buf->unk15 & 1) &&
                    ((hitInfo = gModelSlots[i].unk7C) == NULL || hitInfo->unk70 != 0)) {
                    result |= func_80673708(x, y, z, radius, buf->box_start, buf->box_end, arcMin, arcMax);
                }
            }
            i++;
        } while (i < gModelSlotCount);
    }
    return result;
}


s16 func_80672134(s16 angle, s16 arcMin, s16 arcMax, s16 maxValue) {
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

typedef struct ActorMotionSub174 {
    u8 pad0[0x1A3];
    u8 unk1A3;
    u8 pad1A4[0x1C];
    f32 unk1C0;
    u8 pad1C4[8];
    f32 unk1CC;
} ActorMotionSub174;



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
        sub->unk88 = gFrameCounter;
    }
}


void actorUpdateMovementFlags(Actor *actor) {
    ActorSub140 *sub;

    if (actor->unk144 & 8) {
        sub = actor->collision;
        if (sub->unk6C != 0) {
            actor->hasArcBounds |= actorResolveModelSlotCollision(actor);
        } else {
            sub->unk60 = 0;
        }
        if (actor->flags & 0x20) {
            if (actor->collision->unk24 != 0 && actorCheckPointInAngleArc(actor, actor->collision->unk1C, actor->collision->unk20) != 0) {
                actor->x = actor->collision->unk1C;
                actor->z = actor->collision->unk20;
            }
        }
    } else {
        sub = actor->collision;
        if (sub != NULL) {
            sub->unk6C = 0;
        }
    }
}

u8 actorHasActiveMovementFlags(Actor *actor) {
    return actor->attachMode != 0
        || actor->collision->unk6C != 0
        || actor->collision->unk24 != 0
        || (actor->contactFlags & 8) != 0
        || (actor->contactFlags & 0x400) != 0;
}

void actorClearMovementFlags(Actor *actor) {
    ActorSub140 *sub;

    sub = actor->collision;
    actor->attachMode = 0;
    if (sub != NULL) {
        sub->unk6C = 0;
        actor->collision->unk24 = 0;
    }
    actor->contactFlags &= ~8;
    actor->contactFlags &= ~0x400;
    actor->renderFlags |= 0x2000;
}

extern s16 D_807FB5F8;
extern s16 D_807FB5FA;

void actorSetCameraBoundaryMode(s32 mode) {
    D_807FB53C = mode;
    if (mode != 0 && mode != 0xBC) {
        D_807FB5F8 = 2;
        D_807FB5FA = 10;
    } else {
        D_807FB5F8 = 100;
        D_807FB5FA = 100;
    }
}

extern Actor *gPrimaryPlayerActor;

s32 actorCheckCameraBoundaryCondition(s8 condition) {
    ActorMotionSub174 *state;

    switch (condition) {
    case 0:
        if (D_807FB53C == 0xBC) {
            return 1;
        }
        break;
    case 1:
        if (D_807FB53C != 0xBC) {
            return 1;
        }
        break;
    case 2:
        if (D_807FB53C != 5 || gPlayerSlots->unk2C0 == 1) {
            return 1;
        }
        break;
    case 3:
        if (D_807FB53C == 5 && gPlayerSlots->unk2C0 != 1) {
            return 1;
        }
        break;
    case 4:
        if (D_807FB53C == 8) {
            return 1;
        }
        break;
    case 5:
        D_807FB548 = 1;
        return 1;
    case 6:
        state = gPrimaryPlayerActor->customState;
        if (D_807FB53C == 3 && state->unk1A3 != 0) {
            return 1;
        }
        break;
    case 7:
        state = gPrimaryPlayerActor->customState;
        if (D_807FB53C == 6 && (gPlayerSlots->unk2C0 != 1 || state->unk1CC != state->unk1C0)) {
            return 1;
        }
        break;
    case 8:
        if (D_807FB53C == 9) {
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
