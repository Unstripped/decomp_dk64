#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "heap.h"
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

typedef struct BufferCacheEntry {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0xC];
} BufferCacheEntry; // size = 0x18

typedef struct CollisionTri {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
} CollisionTri; // size = 0x12

typedef struct CollisionBox {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A;
    /* 0x4B */ u8 unk4B;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 unk4D;
    /* 0x4E */ s8 unk4E;
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 pad52[0x58 - 0x52];
} CollisionBox; // size = 0x58

extern s32 gFrameCounter;
extern BufferCacheEntry *D_807FB534;
extern s32 D_807FB538;
extern Actor *D_807FB540;
extern s16 D_807FB544;
extern u8 D_807FB546;
extern u8 D_807FB549;
extern u8 D_807FB604;



typedef struct ModelSlotAsset {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ s32 unk60;
} ModelSlotAsset;

typedef struct ModelSlotTriBuffer {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x18];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25[3];
} ModelSlotTriBuffer;

typedef struct ModelSlotHitInfo {
    /* 0x00 */ u8 pad0[0x50];
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 unk53;
    /* 0x54 */ u8 pad54[8];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ u8 pad60[0xE];
    /* 0x6E */ u8 unk6E;
    /* 0x6F */ u8 unk6F;
    /* 0x70 */ u8 unk70;
    /* 0x71 */ u8 pad71[0x17];
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[7];
    /* 0x9B */ u8 unk9B;
} ModelSlotHitInfo;

typedef struct ModelSlot {
    /* 0x00 */ f32 unk0[9];
    /* 0x24 */ ModelSlotAsset *unk24;
    /* 0x28 */ DynamicBuffer unk28;
    /* 0x48 */ ModelSlotTriBuffer unk48;
    /* 0x70 */ u8 pad70[8];
    /* 0x78 */ s32 *unk78;
    /* 0x7C */ struct ModelSlotHitInfo *unk7C;
    /* 0x80 */ u8 pad80[8];
    /* 0x88 */ s16 unk88;
    /* 0x8A */ u8 pad8A[6];
} ModelSlot; // size = 0x90

extern u8 gGfxBufferIndex;
extern ModelSlot *gModelSlots;


typedef struct ModelCollisionAsset {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 pad24[0x28];
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ u8 pad50[0x10];
    /* 0x60 */ s32 unk60;
} ModelCollisionAsset;

typedef struct CollisionSlotBuffer {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ u8 *unk18;
    /* 0x1C */ u8 *unk1C;
} CollisionSlotBuffer;

#define MODEL_COLLISION_ASSET ((ModelCollisionAsset *)arg1)


void collisionBuildSlotBoxes(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    s32 off;
    s32 *anim;
    s32 count;
    u8 *entry;
    u8 *out;
    f32 sp124[4][4];
    f32 spE4[4][4];
    f32 spA4[4][4];
    f32 sp64[4][4];
    s32 i;
    CollisionSlotBuffer *buf;
    s32 sp58;
    u8 *sp54;
    s8 lastBone;
    s8 bone;

    off = arg0 * sizeof(ModelSlot);
    anim = ((ModelSlot *)((u8 *)gModelSlots + off))->unk78;
    lastBone = -1;
    buf = (CollisionSlotBuffer *)&gModelSlots[arg0].unk28;
    if (anim != NULL) {
        sp58 = anim[gGfxBufferIndex];
    } else {
        sp58 = 0;
    }
    sp54 = (u8 *)(MODEL_COLLISION_ASSET->unk60 + arg1);
    buf->unkC = (s32)((f32)MODEL_COLLISION_ASSET->unk20 * arg8 * 8.0f * 1.5);
    buf->unk0 = (s32)(arg2 * 8.0f);
    buf->unk4 = (s32)(arg3 * 8.0f);
    buf->unk8 = (s32)(arg4 * 8.0f);
    count = *(s32 *)(MODEL_COLLISION_ASSET->unk4C + arg1);
    if (count != 0) {
        buf->unk15 |= 2;
        if (!(buf->unk15 & 1)) {
            buf->unk18 = heapAlloc(count * 0x58);
        }
        entry = (u8 *)(MODEL_COLLISION_ASSET->unk4C + arg1) + 4;
        out = buf->unk18;
        guScaleF(sp124, arg8, arg8, arg8);
        guRotateF(spE4, arg5, 1.0f, 0.0f, 0.0f);
        guMtxCatF(sp124, spE4, sp124);
        guRotateF(spE4, arg6, 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp124, spE4, sp124);
        guRotateF(spE4, arg7, 0.0f, 0, 1.0f);
        guMtxCatF(sp124, spE4, sp124);
        guTranslateF(spE4, arg2, arg3, arg4);
        guMtxCatF(sp124, spE4, sp124);
        i = 0;
        if (count > 0) {
            do {
                bone = entry[0x14];
                if ((bone ^ 0) == -1) { // FAKE: ^ 0 steers bne operand order
                    if (collisionTransformTriangle(entry, out, sp124) != 0) {
                        out += 0x58;
                    }
                } else {
                    if (lastBone != bone) {
                        modelBuildBoneChainMatrix((bone << 5) + sp54, sp58, spA4);
                        guMtxCatF(spA4, sp124, sp64);
                        lastBone = entry[0x14];
                    }
                    if (collisionTransformTriangle(entry, out, sp64) != 0) {
                        out += 0x58;
                    }
                }
                i++;
                entry += 0x16;
            } while (i != count);
        }
        buf->unk1C = out;
    } else {
        buf->unk18 = NULL;
        buf->unk1C = NULL;
    }
    buf->unk15 |= 1;
    buf->unk10 = gFrameCounter;
}

void modelSlotBuildTransformMatrix(s16 arg0, s8 arg1, f32 (*arg2)[4]) {
    f32 posX;
    f32 posY;
    f32 posZ;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    f32 scale;
    s32 flags;
    s32 pad;
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    s32 boneMtx;
    void *bones;
    ModelSlot *entry;

    entry = (ModelSlot *)((u8 *)gModelSlots + arg0 * sizeof(ModelSlot));
    if (entry->unk78 != NULL) {
        boneMtx = entry->unk78[gGfxBufferIndex];
    } else {
        boneMtx = 0;
    }
    bones = entry->unk24->unk60 + (u8 *)entry->unk24;
    modelSlotGetTransformVectors(arg0, &posX, &posY, &posZ, &rotX, &rotY, &rotZ, &scale, &flags, 0);
    guScaleF(mtx, scale, scale, scale);
    guRotateF(tmpMtx, rotX, 1.0f, 0.0f, 0.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guRotateF(tmpMtx, rotY, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guRotateF(tmpMtx, rotZ, 0.0f, 0, 1.0f);
    guMtxCatF(mtx, tmpMtx, mtx);
    guTranslateF(tmpMtx, posX, posY, posZ);
    if (arg1 != -1) {
        guMtxCatF(mtx, tmpMtx, mtx);
        modelBuildBoneChainMatrix((arg1 << 5) + (u8 *)bones, boneMtx, arg2);
        guMtxCatF(arg2, mtx, arg2);
        return;
    }
    guMtxCatF(mtx, tmpMtx, arg2);
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

void collisionTransformNode(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    collisionBuildSlotBoxes(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

void dynamicBufferFree(DynamicBuffer *buf) {
    if (buf->unk18 != NULL && (buf->unk15 & 1)) {
        heapFree(buf->unk18);
    }
    buf->unk15 &= ~1;
}

typedef struct CollisionStaticHeader {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[5];
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 padA[6];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} CollisionStaticHeader;

typedef struct CollisionStaticCellEntry {
    /* 0x00 */ void *unk0;
    /* 0x04 */ u8 *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} CollisionStaticCellEntry;

extern s32 gCurrentMap;
extern s32 D_807FB530;


void collisionInitStaticCache(CollisionStaticHeader *arg0) {
    u8 *data;
    void *compressed;
    void *gzOut;
    void *gzIn;
    s32 *cellHeader;
    u8 *var_v1;
    u8 *cellStart;
    s32 relativeOffset;
    s32 i;
    s32 cellEnd;
    s32 elem_size;
    s32 assetSize;
    s32 d1;
    void *gzWork;

    cellEnd = 4;
    data = assetLoad(2, gCurrentMap, 1, 0);
    D_807FB549 = 0;
    if (arg0->unk9 & 1) {
        compressed = data;
        data = heapAlloc(arg0->unk0);
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
    elem_size = 24;
    D_807FB538 = arg0->unk10 * arg0->unk12;
    for (i = 0; i < D_807FB538; i++) {
        cellStart = data + cellEnd + 4;
        cellEnd = *cellHeader;
        if (D_807FB549 != 0) {
            ((CollisionStaticCellEntry *)D_807FB534)[i].unk4 = cellStart;
        } else {
            ((CollisionStaticCellEntry *)D_807FB534)[i].unk4 = NULL;
        }
        ((CollisionStaticCellEntry *)D_807FB534)[i].unk0 = NULL;
        relativeOffset = cellStart - data;
        ((CollisionStaticCellEntry *)D_807FB534)[i].unkC = assetSize + relativeOffset;
        ((CollisionStaticCellEntry *)D_807FB534)[i].unk10 = (data + cellEnd) - cellStart;
        cellHeader = (s32 *)(data + cellEnd);
        ((CollisionStaticCellEntry *)D_807FB534)[i].unk8 = 0;
        ((CollisionStaticCellEntry *)D_807FB534)[i].unk14 = ((s32)(data + cellEnd) - (s32)cellStart) / elem_size; // FAKE: s32 casts steer the register pick of the subtraction (v1 vs t-reg)
    }
    if (D_807FB549 == 0) {
        assetSetImmediateFree();
        assetFreeBuffer(data, 0x17C, 0xA);
    }
}

typedef struct CollisionStaticCellView {
    void *unk0;
    void *unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} CollisionStaticCellView;

#define COLLISION_STATIC_CELLS ((CollisionStaticCellView *)D_807FB534)


void collisionLoadStaticCell(s32 arg0) {
    s32 sp54;
    s32 pad;
    void *s2;
    void *s1;
    s32 cnt;

    if (COLLISION_STATIC_CELLS[arg0].unk0 == NULL && arg0 < D_807FB538) {
        sp54 = COLLISION_STATIC_CELLS[arg0].unk10;
        if (sp54 != 0) {
            if (D_807FB549 == 0) {
                COLLISION_STATIC_CELLS[arg0].unk4 = heapAlloc(sp54);
                dmaReadAssetDecompress(COLLISION_STATIC_CELLS[arg0].unkC, COLLISION_STATIC_CELLS[arg0].unk4, &sp54, 0, 0, 0, 0);
            }
            cnt = COLLISION_STATIC_CELLS[arg0].unk14;
            COLLISION_STATIC_CELLS[arg0].unk0 = heapAlloc(cnt * 0x28);
            s1 = COLLISION_STATIC_CELLS[arg0].unk4;
            s2 = COLLISION_STATIC_CELLS[arg0].unk0;
            for (; cnt != 0; cnt--) {
                if (collisionBuildStaticTri(s1, s2) != 0) {
                    s2 = (void *)((u8 *)s2 + 0x28);
                }
                s1 = (void *)((u8 *)s1 + 0x18);
            }
        }
    }
    COLLISION_STATIC_CELLS[arg0].unk8 = gFrameCounter;
}

extern s32 D_80747D70;
extern s16 D_80748E40;


void modelSlotExpireNextBuffers(void) {
    DynamicBuffer *a0;
    ModelSlotTriBuffer *a1;

    if (D_80747D70 != 0) {
        D_80748E40++;
        if (D_80748E40 >= D_80747D70) {
            D_80748E40 = 0;
        }
        a0 = &gModelSlots[D_80748E40].unk28;
        if ((a0->unk15 & 1) && ((u32)(gFrameCounter - a0->unk10) >= 0x1F)) {
            dynamicBufferFree(a0);
        }
        a1 = &gModelSlots[D_80748E40].unk48;
        if ((a1->unk24 & 1) && ((u32)(gFrameCounter - a1->unk8) >= 0x1F)) {
            modelSlotTriBufferRelease(a1);
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
        if (D_807FB534[i].unk0 != NULL && (u32)(gFrameCounter - D_807FB534[i].unk8) >= 0x15) {
            if (D_807FB549 == 0) {
                heapFree(D_807FB534[i].unk4);
                D_807FB534[i].unk4 = NULL;
            }
            heapFree(D_807FB534[i].unk0);
            D_807FB534[i].unk0 = NULL;
        }
    }
}

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

s32 collisionTransformTriangle(u8 *arg0, u8 *arg1, f32 (*arg2)[4]) {
#define COLLISION_TRI_IN ((CollisionAssetTri *)arg0)
#define COLLISION_TRI_OUT ((CollisionBox *)arg1)
    u8 sp6C[4];
    s16 sp58[10];
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    guMtxXFMF(arg2, (f32)COLLISION_TRI_IN->unk0, (f32)COLLISION_TRI_IN->unk2, (f32)COLLISION_TRI_IN->unk4, &sp54, &sp50, &sp4C);
    sp58[0] = (s32)sp54;
    sp58[1] = (s32)sp50;
    sp58[2] = (s32)sp4C;
    guMtxXFMF(arg2, (f32)COLLISION_TRI_IN->unk6, (f32)COLLISION_TRI_IN->unk8, (f32)COLLISION_TRI_IN->unkA, &sp48, &sp44, &sp40);
    sp58[3] = (s32)sp48;
    sp58[4] = (s32)sp44;
    sp58[5] = (s32)sp40;
    guMtxXFMF(arg2, (f32)COLLISION_TRI_IN->unkC, (f32)COLLISION_TRI_IN->unkE, (f32)COLLISION_TRI_IN->unk10, &sp3C, &sp38, &sp34);
    sp58[6] = (s32)sp3C;
    sp58[7] = (s32)sp38;
    sp58[8] = (s32)sp34;
    if (collisionIsTriangleDegenerate((CollisionTri *)sp58) != 0) {
        return 0;
    }
    if (COLLISION_TRI_IN->unk12 & 1) {
        COLLISION_TRI_OUT->unk4D = 1;
    } else {
        COLLISION_TRI_OUT->unk4D = 0;
    }
    if (COLLISION_TRI_IN->unk12 & 2) {
        COLLISION_TRI_OUT->unk4F = COLLISION_TRI_IN->unk13;
    } else {
        COLLISION_TRI_OUT->unk4F = 0;
    }
    if (COLLISION_TRI_IN->unk12 & 4) {
        COLLISION_TRI_OUT->unk51 = 1;
    } else {
        COLLISION_TRI_OUT->unk51 = 0;
    }
    if (COLLISION_TRI_IN->unk12 & 8) {
        COLLISION_TRI_OUT->unk50 = 5;
    } else {
        COLLISION_TRI_OUT->unk50 = 0xFF;
    }
    COLLISION_TRI_OUT->unk4E = COLLISION_TRI_IN->unk14;
    COLLISION_TRI_OUT->unk24 = (s32)(sp54 * 8.0f);
    COLLISION_TRI_OUT->unk28 = (s32)(sp50 * 8.0f);
    COLLISION_TRI_OUT->unk2C = (s32)(sp4C * 8.0f);
    COLLISION_TRI_OUT->unk30 = (s32)(sp48 * 8.0f);
    COLLISION_TRI_OUT->unk34 = (s32)(sp44 * 8.0f);
    COLLISION_TRI_OUT->unk38 = (s32)(sp40 * 8.0f);
    COLLISION_TRI_OUT->unk3C = (s32)(sp3C * 8.0f);
    COLLISION_TRI_OUT->unk40 = (s32)(sp38 * 8.0f);
    COLLISION_TRI_OUT->unk44 = (s32)(sp34 * 8.0f);
    sp58[9] = collisionTriangleNormalYaw(sp58, sp6C);
    COLLISION_TRI_OUT->unk4B = collisionTriangleSlopeClass(sp58);
    COLLISION_TRI_OUT->unk48 = sp58[9];
    COLLISION_TRI_OUT->unk4C = sp6C[0];
    return collisionBuildPlane(COLLISION_TRI_OUT);
#undef COLLISION_TRI_IN
#undef COLLISION_TRI_OUT
}

s32 collisionIsTriangleDegenerate(CollisionTri *arg0) {
    s16 x2;
    s16 x1;
    s16 x0;

    x1 = arg0->unk6;
    x0 = arg0->unk0;
    if ((x1 == x0) && (arg0->unk2 == arg0->unk8) && (arg0->unk4 == arg0->unkA)) {
        return 1;
    }
    x2 = arg0->unkC;
    if ((x1 == x2) && (arg0->unkE == arg0->unk8) && (arg0->unk10 == arg0->unkA)) {
        return 1;
    }
    if ((x2 == x0) && (arg0->unk2 == arg0->unkE) && (arg0->unk4 == arg0->unk10)) {
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

s16 collisionTriangleNormalYaw(arg0, arg1)
s16 *arg0;
u8 *arg1;
{
    f32 sp9C[3];
    f32 sp90[3];
    f32 sp84[3];
    f32 sp78[3];
    f32 sp68[4];
    f32 len;
    f32 var_fa0;
    f32 var_fa1;
    f32 angle;
    f32 sp54;
    f32 dist;
    f32 temp_ft5;
    f32 sp38;
    f32 sp34;
    s16 var_v1;

    sp9C[0] = arg0[6] - arg0[0];
    sp9C[1] = arg0[7] - arg0[1];
    sp9C[2] = arg0[8] - arg0[2];

    sp90[0] = arg0[3] - arg0[0];
    sp90[1] = arg0[4] - arg0[1];
    sp90[2] = arg0[5] - arg0[2];

    sp84[0] = sp9C[1] * sp90[2] - sp9C[2] * sp90[1];
    sp84[1] = sp9C[2] * sp90[0] - sp9C[0] * sp90[2];
    sp84[2] = sp9C[0] * sp90[1] - sp9C[1] * sp90[0];

    len = sqrtf(sp84[0] * sp84[0] + sp84[1] * sp84[1] + sp84[2] * sp84[2]);
    if ((f64)len < 0.01) {
        len = 0.01f;
    }
    len = 1.0f / len;

    sp78[0] = sp84[0] * len;
    sp78[1] = sp84[1] * len;
    sp78[2] = sp84[2] * len;

    if (sp84[0] >= 0.0f) {
        var_fa0 = sp84[0];
    } else {
        var_fa0 = 0.0 - sp84[0];
    }

    if (sp84[2] >= 0.0f) {
        var_fa1 = sp84[2];
    } else {
        var_fa1 = 0.0 - sp84[2];
    }

    if ((f64)var_fa1 < 0.01 && (f64)var_fa1 > -0.01) {
        angle = 1.57f;
    } else {
        angle = mathAtan2(var_fa0, var_fa1);
    }

    if (0.0 <= (f64)sp84[0] && 0.0 <= (f64)sp84[2]) {
        var_v1 = (s32)((f64)(f32)((f64)angle * 57.29577791868205) * 11.375);
    }
    if (0.0 <= (f64)sp84[0] && (f64)sp84[2] < 0.0) {
        var_v1 = (s32)((180.0 - (f64)(f32)((f64)angle * 57.29577791868205)) * 11.375);
    }
    if ((f64)sp84[0] < 0.0 && (f64)sp84[2] < 0.0) {
        var_v1 = (s32)(((f64)(f32)((f64)angle * 57.29577791868205) + 180.0) * 11.375);
    }
    if ((f64)sp84[0] < 0.0 && 0.0 <= (f64)sp84[2]) {
        var_v1 = (s32)((360.0 - (f64)(f32)((f64)angle * 57.29577791868205)) * 11.375);
    }

    sp78[0] *= 20.0f;
    sp78[1] *= 20.0f;
    sp78[2] *= 20.0f;
    sp68[0] = arg0[0] + sp78[0];
    sp68[1] = arg0[1] + sp78[1];
    sp68[2] = arg0[2] + sp78[2];
    sp9C[0] = arg0[0] - arg0[3];
    sp9C[1] = arg0[1] - arg0[4];
    sp9C[2] = arg0[2] - arg0[5];
    sp90[0] = arg0[0] - arg0[6];
    sp90[1] = arg0[1] - arg0[7];
    sp90[2] = arg0[2] - arg0[8];
    temp_ft5 = sp9C[1] * sp90[2] - sp9C[2] * sp90[1];
    sp38 = sp9C[2] * sp90[0] - sp9C[0] * sp90[2];
    sp34 = sp9C[0] * sp90[1] - sp9C[1] * sp90[0];
    sp54 = -((sp34 * (f32)arg0[5]) + ((sp38 * (f32)arg0[4]) + (temp_ft5 * arg0[3])));
    dist = (temp_ft5 * sp68[0]) + (sp38 * sp68[1]) + (sp34 * sp68[2]) + sp54;

    if ((!(0.0 < (f64)dist) || !(0.0 < (f64)sp54)) && (!((f64)dist < 0.0) || !((f64)sp54 < 0.0))) {
        var_v1 -= 0x800;
        if (var_v1 < 0) {
            var_v1 += 0xFFF;
        }
        *arg1 = 1;
    } else {
        *arg1 = 0;
    }

    return var_v1;
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

typedef struct CollisionBoxWork {
    /* 0x00 */ s64 nx;
    /* 0x08 */ s64 ny;
    /* 0x10 */ s64 nz;
    /* 0x18 */ s64 d;
    /* 0x20 */ f32 len;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A;
    /* 0x4B */ u8 unk4B;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 unk4D;
    /* 0x4E */ u8 pad4E;
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 pad52[0x58 - 0x52];
} CollisionBoxWork;

s32 collisionBuildStaticTri(void *arg0, void *arg1) {
#define COLLISION_TRI_IN ((CollisionStaticTriIn *)arg0)
#define COLLISION_TRI_OUT ((CollisionStaticTriOut *)arg1)
    CollisionBoxWork work;
    s32 pad[2];
    s16 temp_a0;
    s16 temp_v1;
    s16 temp_v0;

    work.unk24 = COLLISION_TRI_IN->unk0;
    work.unk28 = COLLISION_TRI_IN->unk2;
    work.unk2C = COLLISION_TRI_IN->unk4;
    work.unk30 = COLLISION_TRI_IN->unk6;
    work.unk34 = COLLISION_TRI_IN->unk8;
    work.unk38 = COLLISION_TRI_IN->unkA;
    work.unk3C = COLLISION_TRI_IN->unkC;
    work.unk40 = COLLISION_TRI_IN->unkE;
    work.unk44 = COLLISION_TRI_IN->unk10;

    work.unk24 *= 8; work.unk28 *= 8; work.unk2C *= 8;
    work.unk30 *= 8; work.unk34 *= 8; work.unk38 *= 8;
    work.unk3C *= 8; work.unk40 *= 8; work.unk44 *= 8;

    work.unk48 = COLLISION_TRI_IN->unk12;
    work.unk4C = COLLISION_TRI_IN->unk14;
    work.unk4D = 0;
    work.unk4F = 0;
    if (COLLISION_TRI_IN->unk16 & 4) {
        work.unk51 = 1;
    } else {
        work.unk51 = 0;
    }
    work.unk50 = COLLISION_TRI_IN->unk15;
    work.unk4B = 1;
    collisionBuildPlane((CollisionBox *)&work);

    COLLISION_TRI_OUT->nx = work.nx;
    COLLISION_TRI_OUT->ny = work.ny;
    COLLISION_TRI_OUT->nz = work.nz;
    COLLISION_TRI_OUT->d = work.d;
    COLLISION_TRI_OUT->len = work.len;

    temp_a0 = COLLISION_TRI_IN->unk8;
    temp_v1 = COLLISION_TRI_IN->unk2;
    if (temp_v1 < temp_a0) {
        COLLISION_TRI_OUT->unk24 = temp_v1;
    } else {
        COLLISION_TRI_OUT->unk24 = temp_a0;
    }
    temp_v1 = COLLISION_TRI_OUT->unk24;
    temp_v0 = COLLISION_TRI_IN->unkE;
    if (temp_v1 < temp_v0) {
        COLLISION_TRI_OUT->unk24 = temp_v1;
    } else {
        COLLISION_TRI_OUT->unk24 = temp_v0;
    }
    if (temp_a0 == 0) {} // FAKE: extends temp_a0 so it interferes with temp_v0 and takes $a0

    temp_a0 = COLLISION_TRI_IN->unk8;
    temp_v1 = COLLISION_TRI_IN->unk2;
    if (temp_a0 < temp_v1) {
        COLLISION_TRI_OUT->unk26 = temp_v1;
    } else {
        COLLISION_TRI_OUT->unk26 = temp_a0;
    }
    temp_v0 = COLLISION_TRI_IN->unkE;
    temp_v1 = COLLISION_TRI_OUT->unk26;
    if (temp_v0 < temp_v1) {
        if (temp_v0 == 0) {} // FAKE: extra use raises temp_v0 priority so it takes $v0
        COLLISION_TRI_OUT->unk26 = temp_v1;
    } else {
        COLLISION_TRI_OUT->unk26 = temp_v0;
    }

    return 1;
#undef COLLISION_TRI_IN
#undef COLLISION_TRI_OUT
}

typedef struct CollisionBoxPlaneView {
    /* 0x00 */ s64 nx;
    /* 0x08 */ s64 ny;
    /* 0x10 */ s64 nz;
    /* 0x18 */ s64 d;
    /* 0x20 */ f32 len;
    /* 0x24 */ s32 x0;
    /* 0x28 */ s32 y0;
    /* 0x2C */ s32 z0;
    /* 0x30 */ s32 x1;
    /* 0x34 */ s32 y1;
    /* 0x38 */ s32 z1;
    /* 0x3C */ s32 x2;
    /* 0x40 */ s32 y2;
    /* 0x44 */ s32 z2;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 axis;
} CollisionBoxPlaneView;

s32 collisionBuildPlane(CollisionBox *arg) {
#define COLLISION_PLANE ((CollisionBoxPlaneView *)arg)
    s64 d1[3];
    s64 d2[3];
    s64 ax;
    s64 ay;
    s64 az;

    d1[0] = COLLISION_PLANE->x0 - COLLISION_PLANE->x1;
    d1[1] = COLLISION_PLANE->y0 - COLLISION_PLANE->y1;
    d1[2] = COLLISION_PLANE->z0 - COLLISION_PLANE->z1;
    d2[0] = COLLISION_PLANE->x0 - COLLISION_PLANE->x2;
    d2[1] = COLLISION_PLANE->y0 - COLLISION_PLANE->y2;
    d2[2] = COLLISION_PLANE->z0 - COLLISION_PLANE->z2;
    COLLISION_PLANE->nx = d1[1] * d2[2] - d1[2] * d2[1];
    COLLISION_PLANE->ny = d1[2] * d2[0] - d1[0] * d2[2];
    COLLISION_PLANE->nz = d1[0] * d2[1] - d1[1] * d2[0];
    COLLISION_PLANE->d = -(COLLISION_PLANE->nx * COLLISION_PLANE->x1 + COLLISION_PLANE->ny * COLLISION_PLANE->y1 + COLLISION_PLANE->nz * COLLISION_PLANE->z1);
    COLLISION_PLANE->len = sqrtf((f32)(COLLISION_PLANE->nx * COLLISION_PLANE->nx + COLLISION_PLANE->ny * COLLISION_PLANE->ny + COLLISION_PLANE->nz * COLLISION_PLANE->nz));
    if (COLLISION_PLANE->len == 0.0) {
        return 0;
    }
    if (COLLISION_PLANE->nx >= 0) {
        ax = COLLISION_PLANE->nx;
    } else {
        ax = 0 - COLLISION_PLANE->nx;
    }
    if (COLLISION_PLANE->ny >= 0) {
        ay = COLLISION_PLANE->ny;
    } else {
        ay = 0 - COLLISION_PLANE->ny;
    }
    if (COLLISION_PLANE->nz >= 0) {
        az = COLLISION_PLANE->nz;
    } else {
        az = 0 - COLLISION_PLANE->nz;
    }
    if (az >= ax && az >= ay) {
        COLLISION_PLANE->axis = 0;
    }
    if (ay >= ax && ay >= az) {
        COLLISION_PLANE->axis = 1;
    }
    if (ax >= ay && ax >= az) {
        COLLISION_PLANE->axis = 2;
    }
    return 1;
#undef COLLISION_PLANE
}

void actorSub140Free(ActorSub140 *arg0) {
    void *temp;
    ModelNode *curr8C;
    ModelNode *next8C;
    ModelSubNode *curr90;
    ModelSubNode *next90;

    if (arg0 != NULL) {
        curr8C = arg0->nodes;
        if (curr8C != NULL) {
            do {
                next8C = curr8C->next;
                heapFree(curr8C);
                curr8C = next8C;
            } while (next8C != NULL);
        }
        curr90 = arg0->subNodes;
        if (curr90 != NULL) {
            do {
                next90 = curr90->next;
                heapFree(curr90);
                curr90 = next90;
            } while (next90 != NULL);
        }
        temp = arg0->boxes;
        if (temp != NULL) {
            heapFree(temp);
        }
        temp = arg0->triangles;
        if (temp != NULL) {
            heapFree(temp);
        }
        heapFree(arg0);
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

typedef struct ActorSphereNodeSrc {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0x20 - 0x10];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ struct ActorSphereNodeSrc *next;
} ActorSphereNodeSrc;

typedef struct ActorPointNode {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0xC];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ struct ActorPointNode *next;
} ActorPointNode;

ActorSub140 *actorSub140CreateFromData(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 *arg9) {
    ActorSub140 *sub140;
    void *s2;
    s32 s3;
    s32 i;
    s32 one;
    s32 pad[10];
    void *tmp;
    void *sp54;
    s32 pad50;
    u8 *a3;
    ActorSphereNodeSrc *node;
    ActorPointNode *subnode;

    sub140 = actorSub140Alloc(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    if (arg9 != NULL) {
        s3 = *(s32 *)arg9;
        arg9 += 4;
        s2 = &sub140->nodes;
        i = 0;
        if (s3 > 0) {
            one = 1;
            do {
                node = (ActorSphereNodeSrc *)heapAlloc(sizeof(ActorSphereNodeSrc));
                node->next = NULL;
                node->unk0 = *(f32 *)arg9;
                node->unk4 = *((f32 *)arg9 + 1);
                node->unk8 = *((f32 *)arg9 + 2);
                node->unkC = *((f32 *)arg9 + 3);
                node->unk20 = *((s32 *)arg9 + 4);
                node->unk26 = one;
                node->unk24 = 0;
                node->unk27 = 0;
                arg9 += 0x14;
                *(void **)s2 = node;
                s2 = &node->next;
                i++;
            } while (i != s3);
            i = 0;
        }

        s3 = *(s32 *)arg9;
        one = 1;
        arg9 += 4;
        if (s3 > 0) {
            s2 = &sub140->subNodes;
            do {
                subnode = (ActorPointNode *)heapAlloc(sizeof(ActorPointNode));
                subnode->next = NULL;
                subnode->unk0 = *(f32 *)arg9;
                subnode->unk4 = *((f32 *)arg9 + 1);
                subnode->unk8 = *((f32 *)arg9 + 2);
                subnode->unk18 = *((s32 *)arg9 + 3);
                arg9 += 0x10;
                *(void **)s2 = subnode;
                s2 = &subnode->next;
                i++;
            } while (i != s3);
            i = 0;
        }

        s2 = (void *)*(s32 *)arg9;
        arg9 += 4;
        sub140->boxCount = (s32)s2;
        if (s2 != NULL) {
            sub140->boxes = (a3 = heapAlloc((s32)s2 * sizeof(ActorSub140SrcTri)));
            sub140->unkA4 = (s32)heapAlloc((s32)s2 * sizeof(ActorSub140Tri));
            sub140->unkA8 = sub140->unkA4;
        }
        if ((s32)s2 > 0) {
            do {
                f32 *t0 = (f32 *)arg9;
                s32 k = 0;
                s32 j = 0;
                f32 *dst = (f32 *)a3;
                f32 *src = (f32 *)arg9;
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
                *(s16 *)(a3 + 0x28) = *(s32 *)(t0 + k);
                *(s32 *)(a3 + 0x24) = *(s32 *)(t0 + (k + 1));
                *(u8 *)(a3 + 0x2A) = one;
                arg9 += 0x2C;
                a3 += 0x2C;
            } while (++i != (s32)s2);
            i = 0;
        }

        s2 = (void *)*(s32 *)arg9;
        arg9 += 4;
        sub140->triangleCount = (s32)s2;
        if (s2 != NULL) {
            tmp = heapAlloc((s32)s2 * sizeof(ActorSub140Tri));
            sub140->triangles = tmp;
            sp54 = tmp;
        }
        if ((s32)s2 > 0) {
            a3 = (u8 *)sp54;
            do {
                f32 *t0 = (f32 *)arg9;
                s32 k = 0;
                s32 j = 0;
                f32 *dst = (f32 *)a3;
                f32 *src = (f32 *)arg9;
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
                *(s16 *)(a3 + 0x54) = *(s32 *)(t0 + k);
                *(s32 *)(a3 + 0x48) = *(s32 *)(t0 + (k + 1));
                *(s32 *)(a3 + 0x4C) = *(s32 *)(t0 + (k + 2));
                *(s32 *)(a3 + 0x50) = *(s32 *)(t0 + (k + 3));
                *(u8 *)(a3 + 0x56) = one;
                arg9 += 0x34;
                a3 += 0x58;
            } while (++i != (s32)s2);
        }
    }
    return sub140;
}

void actorSetNodeValue(Actor *arg0, s32 arg1, u16 arg2) {
    ModelNode *node;

    node = actorGetModelNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk24 = arg2;
    }
}

void actorOrNodeFlags(Actor *arg0, s32 arg1, u8 arg2) {
    ModelNode *node;

    node = actorGetModelNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk27 |= arg2;
    }
}

void actorClearNodeFlags(Actor *arg0, s32 arg1, u8 arg2) {
    ModelNode *node;

    node = actorGetModelNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk27 &= ~arg2;
    }
}

void func_8066E664(Actor *arg0, s32 arg1, u8 arg2) {
    ActorSub140 *sub;
    ActorSub140SrcTri *ent;
    s32 i;

    sub = arg0->collision;
    if (arg0->collision != NULL) { // FAKE: second read of unk140 keeps the sub copy in $v0
        ent = sub->boxes;
        for (i = 0; i < sub->boxCount; i++) {
            if (arg1 == ent[i].unk28) {
                ent[i].unk2A = arg2;
            }
        }
    }
}

void func_8066E6C8(Actor *arg0, s32 arg1, u8 arg2) {
    ActorSub140 *sub;
    ActorSub140Tri *ent;
    s32 i;

    sub = arg0->collision;
    if (arg0->collision != NULL) { // FAKE: second read of unk140 keeps the sub copy in $v0
        ent = sub->triangles;
        for (i = 0; i < sub->triangleCount; i++) {
            if (arg1 == ent[i].unk54) {
                ent[i].unk56 = arg2;
            }
        }
    }
}

ActorSub140 *actorSub140Alloc(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    ActorSub140 *sub;

    sub = (ActorSub140 *)heapAlloc(sizeof(ActorSub140));
    sub->scaledX = (s32) (arg0 * 8.0f);
    sub->scaledY = (s32) (arg1 * 8.0f);
    sub->scaledZ = (s32) (arg2 * 8.0f);
    sub->radius = arg4;
    sub->height = arg5;
    sub->scaledRadius = (s32) (arg4 * arg3 * 8.0f);
    sub->scaledHeight = (s32) (arg5 * arg3 * 8.0f);
    sub->boxBounds = (void *)arg6;
    sub->unk74[0] = (Mtx *)arg7;
    sub->unk74[1] = (Mtx *)arg8;
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



void actorAppendModelSubNode(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    f32 pad[3];
    ActorSub140 *sub;
    ModelSubNode *node;
    ModelSubNode **head;
    ModelSubNode *curr;

    sub = arg0->collision;
    node = (ModelSubNode *)heapAlloc(sizeof(ModelSubNode));
    node->next = NULL;
    head = (ModelSubNode **)&sub->subNodes;
    node->x = arg1;
    node->y = arg2;
    node->z = arg3;
    node->unk18 = arg4;
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

void actorAppendModelNode(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 pad[3];
    ActorSub140 *sub;
    ModelNode *node;
    ModelNode **head;
    ModelNode *curr;

    sub = arg0->collision;
    node = (ModelNode *)heapAlloc(sizeof(ModelNode));
    node->next = NULL;
    head = (ModelNode **)&sub->nodes;
    node->x = arg1;
    node->y = arg2;
    node->z = arg3;
    node->scale = arg4;
    node->unk20 = arg5;
    node->unk10 = 0;
    node->unk14 = 0;
    node->matrixIndex = 0;
    node->unk1C = 0;
    node->active = 1;
    node->unk24 = 0;
    node->unk27 = 0;
    curr = (ModelNode *)sub->nodes;
    if (curr != NULL) {
        do {
            head = &curr->next;
            curr = curr->next;
        } while (curr != NULL);
    }
    *head = node;
}


void actorFreeModelNodeList(Actor *arg0) {
    ActorSub140 *sub;
    ModelNode *node;
    ModelNode *next;

    sub = arg0->collision;
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

f32 actorGetOrSetNodeScale(Actor *arg0, s32 arg1, f32 arg2) {
    ActorSub140 *sub = arg0->collision;
    ModelNode *node;

    arg1--;
    node = sub->nodes;
    while (arg1-- && node != NULL) {
        node = node->next;
    }
    if (node != NULL) {
        if (arg2 != -1.0f) {
            node->scale = arg2;
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

ModelNode *actorGetModelNodeByIndex(Actor *arg0, s32 arg1) {
    ActorSub140 *sub;
    ModelNode *node;

    sub = arg0->collision;
    arg1--;
    if (sub != NULL) {
        node = sub->nodes;
        while (arg1 != 0 && node != NULL) {
            arg1--;
            node = node->next;
        }
        if (node != NULL) {
            return node;
        }
        return NULL;
    }
    return NULL;
}

ActorSub140 *actorSetCollisionRadius(Actor *arg0, f32 arg1) {
    ActorSub140 *sub = arg0->collision;
    sub->radius = arg1;
    return sub;
}

void actorSub140SetVectors(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    ActorSub140 *sub = arg0->collision;

    if (arg0->renderFlags & 0x800) {
        arg4 = arg0->unk120;
    }
    sub->scaledX = (s32)(arg1 * 8.0f);
    sub->scaledY = (s32)(arg2 * 8.0f);
    sub->scaledZ = (s32)(arg3 * 8.0f);
    sub->scaledRadius = (s32)(sub->radius * arg4 * 8.0f);
    sub->scaledHeight = (s32)(sub->height * arg4 * 8.0f);
}

void actorUpdateModelMatrices(Actor *arg0) {
    ActorSub140 *sub;
    s32 flags;

    sub = arg0->collision;
    if (sub != NULL) {
        flags = arg0->flags;
        if (!(flags & 0x80000000) || !(flags & 0x10)) {
            actorSub140BuildBoxes(sub);
        }
        if (!(arg0->renderFlags & 8) || !(arg0->flags & 0x10)) {
            actorSub140TransformTriangles(arg0->collision);
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

    none = -1;
    if (sub->boxes != NULL) {
        if (gFrameCounter == sub->unk88) {
            bufIdx = gGfxBufferIndex;
        } else {
            bufIdx = (gGfxBufferIndex ^ 1);
        }
        mtx = sub->unk74[bufIdx];
        ent = sub->boxes;
        box = (CollisionBox *)sub->unkA4;
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
                        memcpy(boundsMtx, sub->boxBounds, 0x40);
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
        sub->unkA8 = (s32)box;
    }
}

s32 collisionBuildBoxFromMatrix(f32 *arg0, CollisionBox *arg1) {
    u8 sp34[4];
    s16 sp32;
    s16 sp20[9];

    sp20[0] = arg0[0];
    sp20[1] = arg0[3];
    sp20[2] = arg0[6];
    sp20[3] = arg0[1];
    sp20[4] = arg0[4];
    sp20[5] = arg0[7];
    sp20[6] = arg0[2];
    sp20[7] = arg0[5];
    sp20[8] = arg0[8];

    if (collisionIsTriangleDegenerate((CollisionTri *)sp20) != 0) {
        return 0;
    }

    arg1->unk24 = (s32)(arg0[0] * 8.0f);
    arg1->unk28 = (s32)(arg0[3] * 8.0f);
    arg1->unk2C = (s32)(arg0[6] * 8.0f);
    arg1->unk30 = (s32)(arg0[1] * 8.0f);
    arg1->unk34 = (s32)(arg0[4] * 8.0f);
    arg1->unk38 = (s32)(arg0[7] * 8.0f);
    arg1->unk3C = (s32)(arg0[2] * 8.0f);
    arg1->unk40 = (s32)(arg0[5] * 8.0f);
    arg1->unk44 = (s32)(arg0[8] * 8.0f);

    sp32 = collisionTriangleNormalYaw(sp20, sp34, arg0);
    arg1->unk4B = collisionTriangleSlopeClass(sp20);
    arg1->unk4D = 0;
    arg1->unk4F = 0;
    arg1->unk51 = 0;
    arg1->unk50 = 0xFF;
    arg1->unk48 = sp32;
    arg1->unk4C = sp34[0];
    collisionBuildPlane(arg1);
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
        mtx = sub->unk74[bufIdx];
        curr = first;
        for (i = 0; i < sub->triangleCount; i++) {
            for (j = 0; j < 3; j++) {
                boneOffset = curr->boneOffset[j];
                if ((boneOffset ^ 0) == -1) { // FAKE: ^ 0 steers bne operand order
                    memcpy(boundsMtx, sub->boxBounds, 0x40);
                    guMtxXFMF(boundsMtx, curr->x[j], curr->x[j + 3], curr->x[j + 6], &curr->out[j], &curr->out[j + 3], &curr->out[j + 6]);
                } else {
                    guMtxXFML((Mtx *)((((boneOffset >> 6) << 6)) + (u8 *)mtx), curr->x[j], curr->x[j + 3], curr->x[j + 6], &curr->out[j], &curr->out[j + 3], &curr->out[j + 6]);
                }
            }
            curr++;
        }
    }
}

u8 actorSetTargetAngleAndCheck(Actor *arg0, s16 arg1) {
    s16 arcMin;
    s16 arcMax;
    s8 actorHit;

    D_807FB544 = arg1;
    D_807FB540 = arg0;
    D_807FB546 = 1;
    D_807FB604 = 1;
    actorCheckTargetAngle(arg0, &arcMin, &arcMax, &actorHit);
    return D_807FB546;
}

u8 actorClearTargetAngle(struct CollisionActor *actor, s16 *arcMin, s16 *arcMax, s8 *hit) {
    D_807FB604 = 0;
    return actorCheckTargetAngle(actor, arcMin, arcMax, hit);
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} ActorSub140State;

typedef struct {
    u8 pad0[0xD4];
    s16 unkD4;
    u8 padD6[0xE0 - 0xD6];
    f32 unkE0;
    f32 unkE4;
    u8 unkE8;
    u8 padE9[1];
    s16 unkEA;
    u8 padEC[0x1A4 - 0xEC];
    u8 unk1A4;
} ActorSub174State;

typedef struct CollisionPlane {
    s64 unk0;
    s64 unk8;
    s64 unk10;
    s64 unk18;
    u8 pad20[0x48 - 0x20];
    s16 unk48;
} CollisionPlane;

typedef struct CollisionVec3i {
    s32 x;
    s32 y;
    s32 z;
} CollisionVec3i;

typedef struct CollisionActor {
    u8 pad0[0x58];
    s32 unk58;
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u32 unk64;
    u8 pad68[0xFD - 0x68];
    u8 unkFD;
    u8 padFE[0x140 - 0xFE];
    ActorSub140State *unk140;
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    ActorSub174State *unk174;
} CollisionActor;

typedef struct {
    u8 pad[0x2C0];
    u8 unk2C0;
    u8 pad2[0x2F0 - 0x2C1];
} KongPlayerData;
extern KongPlayerData *gPlayerSlots;
extern u8 D_807FB547;
extern u8 D_807FB602;
extern u8 D_807FB605;
extern u8 D_807FB606;

void func_80672E90(s32, s32, s32);

u8 actorCheckTargetAngle(CollisionActor *arg0, s16 *arg1, s16 *arg2, s8 *arg3) {
    s32 pad;
    u8 boundsHit;
    u8 slotHit;
    ActorSub140State *state;

    boundsHit = 0;
    slotHit = 0;
    state = arg0->unk140;
    if (arg0->unk60 & 0x10000) {
        *arg1 = 0;
        *arg2 = 0xFFF;
    }
    if ((state == NULL) || !(arg0->unk60 & 0x10)) {
        *arg3 = 0;
        return 0;
    }
    func_80672E90(state->unk0, state->unk4, state->unk8);
    actorSetCameraBoundaryMode(arg0->unk58);
    D_807FB602 = 0;
    D_807FB547 = 0;
    D_807FB605 = 0;
    D_807FB606 = 0;
    if (arg0->unk144 & 0x20) {
        actorCollisionCheckNodeSpheres(arg0);
    }
    if (arg0->unk144 & 8) {
        boundsHit = actorCheckTargetAngleBounds(arg0, arg1, arg2);
        slotHit = actorCollideModelSlots(arg0, arg1, arg2);
        *arg3 = actorCheckCollisionsAgainstActiveActors(arg0, arg1, arg2);
    } else {
        *arg3 = 0;
    }
    actorQueueCollisionCallbacks(arg0);
    arg0->unkFD = D_807FB547;
    if (D_807FB606 != 0) {
        arg0->unk64 |= 0x100;
    } else {
        arg0->unk64 &= ~0x100;
    }
    return (boundsHit != 0) || (slotHit != 0);
}

void actorQueueCollisionCallbacks(CollisionActor *arg0) {
    if (D_807FB602) {
        if (arg0->unk5C & 1) {
            ActorSub174State *sub = arg0->unk174;
            if (sub->unkD4 == 0) {
                if (D_807FB602 & 1) {
                    actorQueueDelayedCallback(arg0, 0, 8, 0, 0, 0, 1);
                }
                if (D_807FB602 & 2) {
                    actorQueueDelayedCallback(arg0, 0, 8, 0, 0, 0, 1);
                }
            }
        }
    }
}

typedef struct ActorSphereNodeHit {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 pad20[6];
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ struct ActorSphereNodeHit *next;
} ActorSphereNodeHit;

struct ActorTargetWork;
s32 collisionSpheresOverlap(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80673708(s32, s32, s32, s32, s32, s32, s16 *, s16 *);
extern u8 D_807FB548;
extern u8 D_807FB5FD;
extern u8 D_807FB5FF;
extern u8 D_807FB600;
extern u8 D_807FB601;
extern u8 D_807FB61C;

u8 actorCollideModelSlots(CollisionActor *arg0, s16 *arg1, s16 *arg2) {
    u8 result;
    ActorSphereNodeHit *node;
    DynamicBuffer *buf;
    ModelSlotHitInfo *hit;
    s32 i;
    ActorSub140 *sub;
    u8 savedFlags;
    u8 ret;
    u8 flag;

    result = 0;
    sub = (ActorSub140 *)arg0->unk140;
    sub->unk6C = 0;
    D_807FB548 = 0;
    for (i = 0; i < D_80747D70; i++) {
        buf = &gModelSlots[i].unk28;
        if (buf->unk15 & 2) {
            if (collisionSpheresOverlap(sub->scaledX, sub->scaledY, sub->scaledZ, sub->scaledRadius, buf->unk0, buf->unk4, buf->unk8, buf->unkC) != 0) {
                if (!(buf->unk15 & 1)) {
                    collisionTransformNode(i, (s32)gModelSlots[i].unk24, gModelSlots[i].unk0[0], gModelSlots[i].unk0[1], gModelSlots[i].unk0[2], gModelSlots[i].unk0[4], gModelSlots[i].unk0[5], gModelSlots[i].unk0[6], gModelSlots[i].unk0[3]);
                } else {
                    buf->unk10 = gFrameCounter;
                }
                if (!(arg0->unk5C & 1) || playerSlotMatchesSizeMask(*(s32 *)gModelSlots[i].unk24, arg0->unk174->unk1A4) == 0) {
                    actorUpdateCollisionSpheres(arg0, 0);
                    flag = 1;
                    node = (ActorSphereNodeHit *)sub->nodes;
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
                    if ((D_807FB5FD == 0 || (arg0->unk144 & 0x10)) && flag != 0) {
                        D_807FB5FF = 0;
                        ret = 0;
                        while (node != NULL && D_807FB5FF == 0) {
                            if (node->unk26 != 0 && node->unk1C != 0 && !(node->unk27 & 6)) {
                                ret |= func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, (s32)buf->unk18, buf->unk1C, arg1, arg2);
                            }
                            node = node->next;
                        }
                        result |= ret;
                        if (D_807FB601 != 0) {
                            if (gModelSlots[i].unk7C != NULL) {
                                gModelSlots[i].unk7C->unk5C = D_807FB601;
                                gModelSlots[i].unk7C->unk5E = arg0->unk58;
                            }
                        }
                        if (D_807FB5FF != 0) {
                            actorBuildCollisionHit(i, arg0, (s32)buf->unk18);
                        }
                        if (gModelSlots[i].unk7C != NULL && gModelSlots[i].unk7C->unk6E == 0) {
                            D_807FB602 = savedFlags;
                        }
                        if (ret && D_807FB5FD == 0 && D_807FB61C != 0) {
                            actorUpdateSubActorOffsets((struct ActorTargetWork *)arg0, 0);
                        }
                    }
                }
            }
        }
    }
    return result;
}


typedef struct ActorHitState {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x26 - 0x10];
    s16 unk26;
    f32 unk28[3];
    f32 unk34[3];
    f32 unk40[3];
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    s16 unk58;
    s8 unk5A;
    s32 unk5C;
    u8 pad60[4];
    s16 unk64;
    s16 unk66;
    u8 pad68[4];
    u8 unk6C;
} ActorHitState;

typedef struct ActorHitView {
    u8 pad0[0x5C];
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x140 - 0x88];
    ActorHitState *unk140;
} ActorHitView;

extern s32 D_807FB5C4;
extern s32 D_807FB5C8;
extern s32 D_807FB5CC;
extern s32 D_807FB5D0;
extern CollisionBox *D_807FB5D8;
struct ActorFacingWork;
s32 func_806744A8(struct ActorFacingWork *, s32, s32, s32, s32);

void actorBuildCollisionHit(s32 arg0, ActorHitView *arg1, CollisionBox *arg2) {
    ActorHitState *sub;
    f32 pad[7];
    f32 mtx[4][4];
    f32 mtxC[4][4];
    f32 inv[4][4];
    s32 off;
    s32 hit;
    u8 ok;
    f32 x[3];
    f32 y[3];
    f32 z[3];
    f32 px;
    f32 py;
    f32 pz;
    s32 i;

    sub = arg1->unk140;
    hit = 0;
    ok = func_806744A8((struct ActorFacingWork *)D_807FB5D8, sub->unk0, sub->unk4, sub->unk8, sub->unkC);
    func_8066FE08(arg0);
    if (ok != 0) {
        sub->unk5A = D_807FB5D8->unk4E;
        sub->unk58 = D_807FB5D8 - arg2;
        modelSlotBuildTransformMatrix(arg0, D_807FB5D8->unk4E, mtx);
        matrix4Invert(inv, mtx);
        off = arg0 * 0x90;
        if (gModelSlots[arg0].unk7C != NULL && (gModelSlots[arg0].unk7C->unk9B & 0x24)) {
            hit = 1;
        }
        if (hit != 0) {
            px = arg1->unk7C;
            py = arg1->unk80;
            pz = arg1->unk84;
        } else {
            px = (f32)D_807FB5C4 / 8;
            py = (f32)D_807FB5C8 / 8;
            pz = (f32)D_807FB5CC / 8;
        }
        if (!(arg1->unk60 & 0x800)) {
            guMtxXFMF(inv, px, py, pz, &sub->unk4C, &sub->unk50, &sub->unk54);
        }
        x[0] = (f32)D_807FB5D8->unk24 / 8;
        y[0] = (f32)D_807FB5D8->unk28 / 8;
        z[0] = (f32)D_807FB5D8->unk2C / 8;
        x[1] = (f32)D_807FB5D8->unk30 / 8;
        y[1] = (f32)D_807FB5D8->unk34 / 8;
        z[1] = (f32)D_807FB5D8->unk38 / 8;
        x[2] = (f32)D_807FB5D8->unk3C / 8;
        y[2] = (f32)D_807FB5D8->unk40 / 8;
        z[2] = (f32)D_807FB5D8->unk44 / 8;
        for (i = 0; i < 3; i++) {
            guMtxXFMF(inv, x[i], y[i], z[i], &sub->unk28[i], &sub->unk34[i], &sub->unk40[i]);
        }
        sub->unk26 = ((ModelSlot *)((u8 *)gModelSlots + off))->unk88;
        sub->unk5C = D_807FB5D0;
        if (sub->unk5C < 0x14) {
            sub->unk5C = 0x14;
        }
        sub->unk64 = actorGetCollisionThreshold((CollisionActor *)arg1);
        sub->unk66 = D_807FB5D8->unk48;
        if (D_807FB5D8->unk4C != 0) {
            sub->unk66 -= 0x800;
        }
        if (sub->unk66 < 0) {
            sub->unk66 += 0x1000;
        }
        sub->unk6C = 1;
        if (arg1->unk5C & 1) {
            actorReflectCollisionAngle((CollisionActor *)arg1, (CollisionPlane *)D_807FB5D8, (CollisionVec3i *)sub);
        }
    }
}

void actorReflectCollisionAngle(CollisionActor *arg0, CollisionPlane *arg1, CollisionVec3i *arg2) {
    ActorSub174State *sub = arg0->unk174;
    s64 total;
    s64 x_prod;
    s64 y_prod;
    sub->unkEA = arg1->unk48;
    y_prod = arg1->unk8 * arg2->y;
    x_prod = arg1->unk0 * arg2->x;
    total = (arg1->unk10 * arg2->z) + x_prod + y_prod + arg1->unk18;
    if (arg1->unk18 > 0) {
        if (total <= 0) {
            sub->unkEA += 0x800;
        }
    } else if (total >= 0) {
        sub->unkEA += 0x800;
    }
    sub->unkEA &= 0xFFF;
}

s32 actorGetCollisionThreshold(CollisionActor *arg0) {
    switch (arg0->unk58) {
    case 5: {
        ActorSub174State *sub = arg0->unk174;
        if (gPlayerSlots[sub->unk1A4].unk2C0 == 1) {
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
f32 sinApprox(f32);
f32 cosApprox(f32);

void func_8066FE08(s32 arg0) {
    s16 var_v1;
    s16 temp_a1;
    s32 var_a3;
    s32 temp_v0;
    ModelSlotHitInfo *sub;
    s16 var_a0;
    f32 sp160;
    f32 sp15C;
    f32 sp158;
    f32 sp154;
    f32 sp150;
    f32 sp14C;
    f32 sp148;
    s32 sp144;
    f32 mtx[4][4];
    f32 tmp[4][4];
    f32 inv[4][4];
    f32 px;
    f32 py;
    f32 pz;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s16 temp_a2;
    s16 temp_v0b;
    s16 padW;
    f32 sp44;

    var_a3 = 0;
    if (gModelSlots[arg0].unk7C != NULL && D_807FB5D8->unk4D != 0) {
        sub = gModelSlots[arg0].unk7C;
        temp_v0 = sub->unk50;
        if (temp_v0 != 0)
        switch (temp_v0) {
        case 1:
            sub->unk51 = 1;
            var_v1 = D_807FB5D8->unk48;
            if (D_807FB5D8->unk4C != 0) {
                var_v1 -= 0x800;
            }
            if (var_v1 < 0) {
                var_v1 += 0x1000;
            }
            temp_a1 = gCurrentActor->yaw;
            var_a0 = (s16)(var_v1 - temp_a1);
            var_v1 = (1 | var_a3) ? var_v1 : var_v1 + 1; // FAKE: redefines var_v1 (always-true condition folds) so uopt does not forward var_a0's store into the sign test
            if (var_a0 < 0) {
                var_a0 = (s16)-var_a0;
            }
            if (var_a0 >= 0x801) {
                var_a0 = (s16)(0xFFF - var_a0);
            }
            temp_a2 = sub->unk8A;
            if (var_a0) {} // FAKE: dead use raises var_a0 adjsave so it is coloured before temp_a1/temp_a2
            temp_v0b = sub->unk88;
            if (temp_a2 >= temp_v0b) {
                if (temp_a1 >= temp_v0b && temp_a2 >= temp_a1) {
                    var_a3 = 1;
                }
            } else if (temp_a1 >= temp_v0b || temp_a2 >= temp_a1) {
                var_a3 = 1;
            }
            if (var_a0 < 0x258 && var_a3 != 0) {
                sp44 = (f32)(((f64)var_v1 / 4095.0) * 6.2831854820251465);
                var_v1 = 0; // FAKE: dead store to sp44's operand kills store-forwarding so sp44 stays a variable (spilled to its own home 0x44)
                sub->unk8C = sinApprox(sp44);
                sub->unk90 = cosApprox(sp44);
                sub->unk52 = 1;
                return;
            }
            break;
        case 2:
            sub->unk51 = 1;
            var_v1 = D_807FB5D8->unk48;
            if (D_807FB5D8->unk4C != 0) {
                var_v1 -= 0x800;
            }
            if (var_v1 < 0) {
                var_v1 += 0x1000;
            }
            temp_a1 = gCurrentActor->yaw;
            var_a0 = (s16)(var_v1 - temp_a1);
            var_v1 = 0; // FAKE: dead store (var_v1 unused below) so uopt does not forward var_a0's store into the sign test
            if (var_a0 < 0) {
                var_a0 = (s16)-var_a0;
            }
            if (var_a0 >= 0x801) {
                var_a0 = (s16)(0xFFF - var_a0);
            }
            temp_a2 = sub->unk8A;
            if (var_a0) {} // FAKE: dead use raises var_a0 adjsave so it is coloured before temp_a1/temp_a2
            temp_v0b = sub->unk88;
            if (temp_a2 >= temp_v0b) {
                if (temp_a1 >= temp_v0b && temp_a2 >= temp_a1) {
                    var_a3 = 1;
                }
            } else if (temp_a1 >= temp_v0b || temp_a2 >= temp_a1) {
                var_a3 = 1;
            }
            if (var_a0 < 0x258 && var_a3 != 0) {
                modelSlotGetTransformVectors(arg0, &sp160, &sp15C, &sp158, &sp154, &sp150, &sp14C, &sp148, &sp144, 0);
                guScaleF(mtx, sp148, sp148, sp148);
                guRotateF(tmp, sp154, 1.0f, 0.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, sp150, 0.0f, 1.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, sp14C, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
                guTranslateF(tmp, sp160, sp15C, sp158);
                guMtxCatF(mtx, tmp, mtx);
                matrix4Invert(inv, mtx);
                px = (f32)D_807FB5C4 / 8;
                py = (f32)D_807FB5C8 / 8;
                pz = (f32)D_807FB5CC / 8;
                guMtxXFMF(inv, px, py, pz, &sp74, &sp70, &sp6C);
                guScaleF(mtx, sp148, sp148, sp148);
                guRotateF(tmp, sp154, 1.0f, 0.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, (f32)((f64)sp150 + 1.0), 0.0f, 1.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, sp14C, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
                guTranslateF(tmp, sp160, sp15C, sp158);
                guMtxCatF(mtx, tmp, mtx);
                guMtxXFMF(mtx, sp74, sp70, sp6C, &sp5C, &sp58, &sp54);
                guScaleF(mtx, sp148, sp148, sp148);
                guRotateF(tmp, sp154, 1.0f, 0.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, (f32)((f64)sp150 - 1.0), 0.0f, 1.0f, 0.0f);
                guMtxCatF(mtx, tmp, mtx);
                guRotateF(tmp, sp14C, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
                guTranslateF(tmp, sp160, sp15C, sp158);
                guMtxCatF(mtx, tmp, mtx);
                guMtxXFMF(mtx, sp74, sp70, sp6C, &sp68, &sp64, &sp60);
                sp50 = (f32)camDistance3D((s32)gCurrentActor->x, (s32)gCurrentActor->y, (s32)gCurrentActor->z, (s32)sp68, (s32)sp64, (s32)sp60);
                if (sp50 < (f32)camDistance3D((s32)gCurrentActor->x, (s32)gCurrentActor->y, (s32)gCurrentActor->z, (s32)sp5C, (s32)sp58, (s32)sp54)) {
                    sub->unk52 = 1;
                    return;
                }
                sub->unk52 = 2;
            }
            break;
        }
    }
}

typedef struct ActorSphereNodeQuery {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 pad20[6];
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 pad27;
    /* 0x28 */ struct ActorSphereNodeQuery *unk28;
} ActorSphereNodeQuery;

typedef struct ActorHitSubView {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x26 - 0xC];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ f32 unk28[3];
    /* 0x34 */ f32 unk34[3];
    /* 0x40 */ f32 unk40[3];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s8 unk5A;
    /* 0x5B */ u8 pad5B;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ u8 pad66[0x8C - 0x66];
    /* 0x8C */ ActorSphereNodeQuery *unk8C;
} ActorHitSubView;

typedef struct ActorHitRecord {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ u8 pad4[0x30];
} ActorHitRecord; // size = 0x34

extern u8 D_807FB603;
extern ActorHitRecord D_807FD614[];
s32 func_806738D0(s32, s32, s32, s32, s32, s32);
struct ActorPlaneContactView;
struct ActorHitPlane;

s32 actorResolveModelSlotCollision(arg0)
Actor *arg0;
{
    ActorHitSubView *sub;
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
    ActorSphereNodeQuery *node;
    f32 inv;
    ModelSlotHitInfo *hit;

    {
        u8 kind;

        kind = 0;
        sub = (ActorHitSubView *)arg0->collision;
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
            func_80672E90(sub->unk0, sub->unk4, sub->unk8);
            actorSetCameraBoundaryMode(arg0->actorType);
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
                ret = func_80673708(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, (s32)buf->unk18, buf->unk1C, &arg0->arcYawMin, &arg0->arcYawMax) & 0xFF;
            } else {
                actorSetTargetAngleBounds((s32)buf->unk18 + sub->unk58 * 0x58);
                switch (kind) {
                case 0:
                    ret = func_806738D0(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, (s32)buf->unk18, buf->unk1C) & 0xFF;
                    func_80673708(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, (s32)buf->unk18, buf->unk1C, &arg0->arcYawMin, &arg0->arcYawMax);
                    break;
                case 1:
                case 2:
                    ret = func_80673708(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, (s32)buf->unk18, buf->unk1C, &arg0->arcYawMin, &arg0->arcYawMax) & 0xFF;
                    break;
                case 3:
                case 4:
                    ret = func_80673708(sub->unk0, sub->unk4, sub->unk8, 0x64, (s32)buf->unk18, buf->unk1C, &arg0->arcYawMin, &arg0->arcYawMax) & 0xFF;
                    break;
                }
            }
            if (D_807FB601 != 0 && hit != NULL) {
                gModelSlots[slot].unk7C->unk5C = D_807FB601;
                gModelSlots[slot].unk7C->unk5E = arg0->actorType;
            }
            if (gModelSlots[slot].unk7C != NULL && gModelSlots[slot].unk7C->unk6E != 0) {
                actorQueueCollisionCallbacks((CollisionActor *)arg0);
            }
            if (hit != NULL && hit->unk53 != 0 && D_807FD614[playerFindIndexByActor(arg0)].unk0 > 30.0) {
                ret = 1;
            }
            if (arg0->collisionFlags & 1) {
                actorCalcPlaneContactPoint((struct ActorPlaneContactView *)arg0, slot, (struct ActorHitPlane *)sub);
            }
            if (ret != 0) {
                modelSlotBuildTransformMatrix(slot, sub->unk5A, mtx);
                guMtxXFMF(mtx, sub->unk4C, sub->unk50, sub->unk54, &x, &y, &z);
                if (kind == 1 || kind == 4) {
                    arg0->x = x;
                    arg0->z = z;
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
                    if (kind == 3 || actorCheckPointInAngleArc((Actor *)arg0, x - out[0], z - out[2]) != 0) {
                        arg0->x = x - out[0];
                        arg0->z = z - out[2];
                    }
                }
            } else {
                node = sub->unk8C;
                while (node != NULL) {
                    if (node->unk26 != 0) {
                        i = func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, (s32)buf->unk18, buf->unk1C, &arg0->arcYawMin, &arg0->arcYawMax); ret = (ret | i) & 0xFF; // LAYOUT: same-line call-result keeps 'or ret,ret,v0' operand order and no extra result var
                    }
                    node = node->unk28;
                }
            }
        }
    }
    return ret;
}

typedef struct ActorHitPlane {
    u8 pad0[0x28];
    f32 unk28[3];
    f32 unk34[3];
    f32 unk40[3];
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    u8 pad58[2];
    s8 unk5A;
} ActorHitPlane;

typedef struct ActorPlaneContactState {
    u8 pad0[0xE0];
    f32 unkE0;
    f32 unkE4;
    u8 unkE8;
} ActorPlaneContactState;

typedef struct ActorPlaneContactView {
    u8 pad0[0x174];
    ActorPlaneContactState *unk174;
} ActorPlaneContactView;

extern s16 D_80753D50[];
extern s16 D_80753D60[];
extern u8 gCurrentPlayerIndex;
extern s16 gCurrentCharacterIndex;

void actorCalcPlaneContactPoint(ActorPlaneContactView *arg0, s16 arg1, ActorHitPlane *arg2) {
    f32 mtx[4][4];
    f32 spCC;
    f32 spC8;
    f32 spC4;
    s32 i;
    f32 spB4[3];
    f32 spA8[3];
    f32 sp9C[3];
    f32 normal[3];
    f32 v1[3];
    f32 v2[3];
    f32 inv_len;
    f32 norm[3];
    f32 out[3];
    ActorPlaneContactState *sub;
    f32 sp54;
    f32 scale;

    sub = arg0->unk174;
    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
        sp54 = D_80753D50[gCurrentCharacterIndex];
    } else {
        sp54 = D_80753D60[gCurrentCharacterIndex];
    }

    modelSlotBuildTransformMatrix(arg1, arg2->unk5A, mtx);
    guMtxXFMF(mtx, arg2->unk4C, arg2->unk50, arg2->unk54, &spCC, &spC8, &spC4);

    for (i = 0; i < 3; i++) {
        guMtxXFMF(mtx, arg2->unk28[i], arg2->unk34[i], arg2->unk40[i], &spB4[i], &spA8[i], &sp9C[i]);
    }

    v1[0] = spB4[2] - spB4[0];
    v1[1] = spA8[2] - spA8[0];
    v1[2] = sp9C[2] - sp9C[0];

    v2[0] = spB4[1] - spB4[0];
    v2[1] = spA8[1] - spA8[0];
    v2[2] = sp9C[1] - sp9C[0];

    normal[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    normal[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    normal[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

    inv_len = 1.0f / sqrtf((normal[0] * normal[0]) + (normal[1] * normal[1]) + (normal[2] * normal[2]));
    norm[0] = normal[0] * inv_len;
    norm[1] = normal[1] * inv_len;
    norm[2] = normal[2] * inv_len;

    scale = sp54 / 8;
    out[0] = norm[0] * scale;
    out[1] = norm[1] * scale;
    out[2] = norm[2] * scale;

    sub->unkE0 = spCC - out[0];
    sub->unkE4 = spC4 - out[2];
    sub->unkE8 = 1;
}

typedef struct ActorTargetBounds {
    u8 pad0[0x48];
    s16 unk48;
} ActorTargetBounds;

extern s16 D_807FB5EC;
extern s16 D_807FB5EE;
extern s16 D_807FB5F0;
extern s16 D_807FB5F2;

void actorSetTargetAngleBounds(ActorTargetBounds *arg0) {
    s16 yaw;

    yaw = arg0->unk48;
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

typedef struct ActorTargetSub174 {
    u8 pad[0x1A4];
    u8 unk1A4;
} ActorTargetSub174;

typedef struct ActorTargetNode8C {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[6];
    u8 unk26;
    u8 unk27;
    struct ActorTargetNode8C *next;
} ActorTargetNode8C;

typedef struct ActorTargetNode {
    f32 x;
    f32 y;
    f32 z;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u32 unk18;
    struct ActorTargetNode *next;
} ActorTargetNode;

typedef struct ActorTargetSub140 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0xC];
    f32 unk1C;
    f32 unk20;
    u8 unk24;
    u8 pad25[0x74 - 0x25];
    s32 unk74[2];
    u8 pad7C[0xC];
    s32 unk88;
    ActorTargetNode8C *unk8C;
    ActorTargetNode *unk90;
} ActorTargetSub140;

typedef struct ActorTargetWork {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[0x64 - 0x5C];
    u32 unk64;
    u8 pad68[0x140 - 0x68];
    ActorTargetSub140 *unk140;
    u8 pad144[0x174 - 0x144];
    ActorTargetSub174 *unk174;
} ActorTargetWork;


u8 func_806730A4(s32, s32, s32, s32);
s32 func_806734E4();
s32 actorCheckTargetAngleBounds(ActorTargetWork *arg0, s32 arg1, s32 arg2) {
    s32 pad0;
    s32 pad1;
    ActorTargetSub140 *sub = arg0->unk140;
    ActorTargetNode8C *node;
    u8 ret = 0;

    sub->unk24 = 0;
    D_807FB548 = 0;

    if (func_806730A4(sub->unk0, sub->unk4, sub->unk8, sub->unkC) != 0) {
        if (arg0->unk64 & 0x80) {
            D_807FB605 = 1;
        }
        actorUpdateCollisionSpheres(arg0, 0);
        node = sub->unk8C;
        while (node != NULL) {
            if (node->unk26 != 0 && node->unk1C != 0 && !(node->unk27 & 1)) {
                ret |= func_806734E4(node->unk10, node->unk14, node->unk18, node->unk1C, arg1, arg2);
            }
            node = node->next;
        }
        if ((ret != 0 || D_807FB605 != 0) && D_807FB61C != 0) {
            actorUpdateCollisionExtents(arg0);
        }
        D_807FB605 = 0;
    }
    return ret;
}

typedef struct PlayerContext {
    u8 pad0[0xEA];
    s16 unkEA;
} PlayerContext;

typedef struct ActorFacingSub174 {
    u8 pad0[0xE0];
    f32 unkE0;
    f32 unkE4;
    u8 unkE8;
    u8 padE9[0x1A4 - 0xE9];
    u8 unk1A4;
} ActorFacingSub174;

typedef struct ActorFacingWork {
    u8 pad0[0x48];
    s16 unk48;
    u8 pad4A[0x58 - 0x4A];
    s32 unk58;
    u16 unk5C;
    u8 pad5E[0x64 - 0x5E];
    u32 unk64;
    u8 pad68[0x140 - 0x68];
    ActorTargetSub140 *unk140;
    u8 pad144[0x174 - 0x144];
    ActorFacingSub174 *unk174;
} ActorFacingWork;

extern PlayerContext *gActivePlayerState;
extern s32 D_807FB5DC;
extern s16 D_807FB5F6;

s32 func_806744A8(ActorFacingWork *, s32, s32, s32, s32);
f32 mathCosF(s16);
f32 mathSinF(s16);
s32 func_806732A8(s32, s16);

void actorUpdateFacingAndOffset(ActorFacingWork *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 facingDist;
    s32 offsetX;
    s32 pad2C;
    s32 prevThreshold;
    s32 temp;
    ActorTargetSub140 *sub;
    f32 cosYaw;
    s32 threshold;

    facingDist = mathAngleDistance(arg0->unk48, D_807FB544);
    temp = mathAngleDistance((arg0->unk48 + 0x800) & 0xFFF, D_807FB544);
    if ((facingDist < 0x321) || (temp < 0x321)) {
        mathAngleDistance(arg0->unk48, gActivePlayerState->unkEA);
        mathAngleDistance((arg0->unk48 + 0x800) & 0xFFF, gActivePlayerState->unkEA);
        sub = ((ActorFacingWork *)D_807FB540)->unk140;
        func_806744A8(arg0, sub->unk0, sub->unk4, sub->unk8, sub->unkC);
        prevThreshold = D_807FB5D0;
        offsetX = (s32)(mathSinF(D_807FB544) * 20.0f);
        cosYaw = mathCosF(D_807FB544);
        sub = ((ActorFacingWork *)D_807FB540)->unk140;
        func_806744A8(arg0, sub->unk0 + offsetX, sub->unk4, sub->unk8 + (s32)(cosYaw * 20.0f), sub->unkC);
        threshold = D_807FB5D0;
        if (prevThreshold - 2 < threshold) {
            D_807FB546 = 0;
        }
    }
}

void actorUpdateCollisionExtents(ActorTargetWork *arg0) {
    s32 pad4C;
    ActorFacingSub174 *sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
        sp44 = D_80753D50[gCurrentCharacterIndex];
    } else {
        sp44 = D_80753D60[gCurrentCharacterIndex];
    }
    if (((ActorFacingWork *)arg0)->unk5C & 1) {
        f32 scale;
        f32 temp_c4;
        f32 temp_cc;

        sp48 = ((ActorFacingWork *)arg0)->unk174;
        actorComputeBoxNormal(arg0, &sp38, &sp3C, &sp40, 1);
        scale = sp44 / 8;
        temp_c4 = (f32)D_807FB5C4 / 8;
        temp_cc = (f32)D_807FB5CC / 8;
        sp38 *= scale;
        sp3C *= scale;
        sp40 *= scale;
        sp48->unkE0 = temp_c4 - sp38;
        sp48->unkE4 = temp_cc - sp40;
        sp48->unkE8 = 1;
        actorReflectCollisionAngle((CollisionActor *)arg0, (CollisionPlane *)func_806732A8(D_807FB5DC, D_807FB5F6), (CollisionVec3i *)arg0->unk140);
    }
    actorUpdateSubActorOffsets(arg0, 1);
}

void actorUpdateSubActorOffsets(ActorTargetWork *arg0, u8 arg1) {
    if (D_807FB5D0 < actorGetPlayerThreshold(arg0)) {
        ActorTargetSub140 *sub = arg0->unk140;
        f32 targetX;
        f32 scale;
        f32 targetZ;
        f32 normalZ;
        f32 normalY;
        f32 normalX;

        actorComputeBoxNormal(arg0, &normalX, &normalY, &normalZ, arg1);
        targetX = (f32)D_807FB5C4 / (f32)8;
        targetZ = (f32)D_807FB5CC / (f32)8;
        if (D_807FB548 != 0) {
            scale = (f32)actorGetPlayerThreshold(arg0) / (f32)8;
            normalX *= scale;
            normalZ *= scale;
        } else {
            scale = (f32)(D_807FB5D0 + 6) / (f32)8;
            normalX *= scale;
            normalZ *= scale;
        }
        sub->unk1C = targetX - normalX;
        sub->unk20 = targetZ - normalZ;
        sub->unk24 = 1;
    }
}

typedef struct ActorBoxFlagsView {
    u8 pad0[0x60];
    u32 unk60;
} ActorBoxFlagsView;

typedef struct ActorBoxSub140View {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0xB0 - 0x10];
    s32 unkB0;
    s32 unkB4;
} ActorBoxSub140View;

extern CollisionBox *D_807FB5D4;

struct ActorTargetWork;
void actorComputeBoxNormal(struct ActorTargetWork *arg0, f32 *arg1, f32 *arg2, f32 *arg3, u8 arg4) {
    CollisionBox *box;
    f32 padA;
    ActorBoxSub140View *sub;
    f32 v1[3];
    f32 v2[3];
    f32 n[3];
    f32 padB;
    f32 x[3];
    f32 y[3];
    f32 z[3];
    f32 inv_len;

    sub = (ActorBoxSub140View *)arg0->unk140;
    if (arg4) {
        box = (CollisionBox *)func_806732A8(D_807FB5DC, D_807FB5F6);
    } else {
        box = D_807FB5D4;
    }
    x[0] = (f32)box->unk24 / 8;
    y[0] = (f32)box->unk28 / 8;
    z[0] = (f32)box->unk2C / 8;
    x[1] = (f32)box->unk30 / 8;
    y[1] = (f32)box->unk34 / 8;
    z[1] = (f32)box->unk38 / 8;
    x[2] = (f32)box->unk3C / 8;
    y[2] = (f32)box->unk40 / 8;
    z[2] = (f32)box->unk44 / 8;

    v1[0] = x[2] - x[0];
    v1[1] = y[2] - y[0];
    v1[2] = z[2] - z[0];
    v2[0] = x[1] - x[0];
    v2[1] = y[1] - y[0];
    v2[2] = z[1] - z[0];

    n[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    n[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    n[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

    inv_len = 1.0f / sqrtf((n[0] * n[0]) + (n[1] * n[1]) + (n[2] * n[2]));
    *arg1 = n[0] * inv_len;
    *arg2 = n[1] * inv_len;
    *arg3 = n[2] * inv_len;

    func_806744A8((ActorFacingWork *)box, sub->unk0, sub->unk4, sub->unk8, sub->unkC);
    if (arg4) {
        if (((ActorBoxFlagsView *)arg0)->unk60 & 0x800) {
            D_807FB5C4 = sub->unkB0;
            D_807FB5CC = sub->unkB4;
        }
        sub->unkB0 = D_807FB5C4;
        sub->unkB4 = D_807FB5CC;
    }
}

s32 actorGetPlayerThreshold(ActorTargetWork *arg0) {
    ActorTargetSub174 *sub;

    switch (arg0->unk58) {
    case 5:
        sub = arg0->unk174;
        if (gPlayerSlots[sub->unk1A4].unk2C0 != 1) {
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

typedef struct ActorSphereUpdateView {
    u8 pad0[4];
    ActorSub4 *sub4;
    u8 pad8[0x64 - 8];
    u32 renderFlags;
    u8 pad68[0x120 - 0x68];
    f32 unk120;
    u8 pad124[0x140 - 0x124];
    ActorSub140 *collision;
} ActorSphereUpdateView;

void actorUpdateCollisionSpheres(ActorSphereUpdateView *actor, u8 force) {
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
        base = (s32)sub->unk74[idx];
        if (base) {} // FAKE: raises base coloring priority (swaps s5/s6)
        while (node != NULL) {
            if (node->unk20 == -1) {
                memcpy(mtx, sub->boxBounds, 0x40);
                guMtxXFMF(mtx, node->x, node->y, node->z, &outX, &outY, &outZ);
            } else {
                guMtxXFML((Mtx *)((((u32)node->unk20 >> 6) << 6) + base), node->x, node->y, node->z, &outX, &outY, &outZ);
            }
            node->unk10 = outX * 8.0f;
            node->unk14 = outY * 8.0f;
            node->matrixIndex = outZ * 8.0f;
            node->unk1C = node->scale * scale * 8.0f;
            node = node->next;
        }
        sub->unk7C = sub->unk80;
    }
}

typedef struct ActorSub140PointView {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0xC];
    f32 unk1C;
    f32 unk20;
    u8 unk24;
    u8 pad25[0x70 - 0x25];
    void *unk70;
    s32 unk74[2];
    u8 pad7C[0x84 - 0x7C];
    s32 unk84;
    s32 unk88;
    ActorTargetNode8C *unk8C;
    ActorTargetNode *unk90;
} ActorSub140PointView;

void actorUpdateNodePositions(ActorSub140PointView *sub, u8 force) {
    ActorTargetNode *node;
    u8 bufIdx;
    f32 outX;
    f32 outY;
    f32 outZ;
    f32 mtx[4][4];
    s32 mtxBase;

    if (force || (gFrameCounter != sub->unk84)) {
        if (gFrameCounter == sub->unk88) {
            bufIdx = gGfxBufferIndex;
        } else {
            bufIdx = gGfxBufferIndex ^ 1;
        }
        node = sub->unk90;
        mtxBase = sub->unk74[bufIdx];
        if (node != NULL) {
            if (mtxBase) {} // FAKE: raises mtx_base register priority so -1 gets s5, mtx_base s6
            do {
                if (node->unk18 == -1) {
                    memcpy(&mtx, sub->unk70, sizeof(mtx));
                    guMtxXFMF(mtx, node->x, node->y, node->z, &outX, &outY, &outZ);
                } else {
                    guMtxXFML((Mtx *)(((node->unk18 >> 6) << 6) + mtxBase), node->x, node->y, node->z, &outX, &outY, &outZ);
                }
                node->unkC = (s32)(outX * 8.0f);
                node->unk10 = (s32)(outY * 8.0f);
                node->unk14 = (s32)(outZ * 8.0f);
                node = node->next;
            } while (node != NULL);
        }
        sub->unk84 = gFrameCounter;
    }
}

s32 actorGetNodePos(Actor *actor, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
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
        count = arg1 - 1;
        while (node != NULL && count != 0) {
            count--;
            node = node->next;
        }
        if (node == NULL) {
            *arg4 = 0.0f;
            *arg3 = 0.0f;
            *arg2 = 0.0f;
            return 0;
        }
        *arg2 = (f32)node->unkC / (f32)8;
        *arg3 = (f32)node->unk10 / (f32)8;
        *arg4 = (f32)node->unk14 / (f32)8;
        return 1;
    }
    return 0;
}
void actorGetSubNodePos(ActorTargetWork *arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    s32 count = arg1 - 1;
    ActorTargetNode *node = arg0->unk140->unk90;

    while (node != NULL && count != 0) {
        count--;
        node = node->next;
    }
    *arg2 = node->x;
    *arg3 = node->y;
    *arg4 = node->z;
}

s32 actorStepSubNodeList(ActorTargetWork *arg0, s32 arg1) {
    ActorTargetSub140 *sub = arg0->unk140;
    u8 val;
    s32 base;
    ActorTargetNode *node;

    if (gFrameCounter == sub->unk88) {
        val = gGfxBufferIndex;
    } else {
        val = gGfxBufferIndex ^ 1;
    }
    base = sub->unk74[val];

    node = sub->unk90;
    arg1--;
    while (arg1 != 0) {
        arg1--;
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

typedef struct ModelSlotBufferView {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[5];
    u8 unk15;
    u8 pad16[2];
    s32 unk18;
    s32 unk1C;
} ModelSlotBufferView;



u8 collisionTestSphereSlots(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 *arg4, s16 *arg5) {
    s32 x;
    s32 y;
    s32 z;
    s32 radius;
    u8 result;
    s32 i;
    ModelSlotBufferView *buf;
    ModelSlotHitInfo *hitInfo;

    result = 0;
    D_807FB5FD = 0;
    i = 0;
    if (D_80747D70 > 0) {
        do {
            buf = (ModelSlotBufferView *)&gModelSlots[i].unk28;
            if (buf->unk18 != 0 &&
                (D_807FB53C != 0xBC || (gModelSlots[i].unk48.unk24 & 2))) {
                x = arg0;
                y = arg1;
                z = arg2;
                radius = arg3;
                if (collisionSpheresOverlap(x, y, z, radius,
                                  buf->unk0,
                                  buf->unk4,
                                  buf->unk8,
                                  buf->unkC) != 0 &&
                    (buf->unk15 & 1) &&
                    ((hitInfo = gModelSlots[i].unk7C) == NULL || hitInfo->unk70 != 0)) {
                    result |= func_80673708(x, y, z, radius, buf->unk18, buf->unk1C, arg4, arg5);
                }
            }
            i++;
        } while (i < D_80747D70);
    }
    return result;
}


s16 func_80672134(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 opposite;
    f32 ratio;
    s16 bisect;
    s16 diff1;
    s16 diff2;

    if (arg1 >= arg0) {
        if (arg2 >= arg0 && arg1 >= arg2) {
            return 0x270F;
        }
    } else if (arg2 >= arg0 || arg1 >= arg2) {
        return 0x270F;
    }

    opposite = arg2 + 0x800;
    if (opposite >= 0x1000) {
        opposite -= 0x1000;
    }

    bisect = mathAngleArcMidpoint(arg0, arg1);
    if ((arg0 - bisect) > 0) {
        diff1 = arg0 - bisect;
    } else {
        diff1 = -(arg0 - bisect);
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
    return (s16)(s32)((f32)arg3 * ratio);
}


s32 mathAsinFixed(s32);

s32 actorCheckPointInAngleArc(Actor *arg0, f32 arg1, f32 arg2) {
    s32 sp28;
    s32 sp24;
    s32 sp44;
    s32 sp40;
    s32 sp20;
    s32 sp1C;
    f32 sp34;
    s16 var_a2;

    sp44 = (s32)(arg0->prevX * 8.0f);
    sp40 = (s32)(arg0->prevZ * 8.0f);
    sp28 = (s32)(arg1 * 8.0f);
    sp24 = (s32)(arg2 * 8.0f);
    sp20 = sp28 - sp44;
    sp1C = sp24 - sp40;
    sp34 = sqrtf((f32)((sp20 * sp20) + (sp1C * sp1C)));
    if ((f64)sp34 == 0.0) {
        return 1;
    }
    if (sp20 >= 0 && sp1C >= 0) {
        var_a2 = (s16)(mathAsinFixed((s32)(((f64)sp20 * 65535.9) / (f64)sp34)) >> 4);
    }
    if (sp20 >= 0 && sp1C < 0) {
        var_a2 = (mathAsinFixed((s32)(((f64)(sp40 - sp24) * 65535.9) / (f64)sp34)) >> 4) + 0x400;
    }
    if (sp20 < 0 && sp1C < 0) {
        var_a2 = (mathAsinFixed((s32)(((f64)(sp44 - sp28) * 65535.9) / (f64)sp34)) >> 4) + 0x800;
    }
    if (sp20 < 0 && sp1C >= 0) {
        var_a2 = (mathAsinFixed((s32)(((f64)sp1C * 65535.9) / (f64)sp34)) >> 4) + 0xC00;
    }
    return actorAngleInArc(arg0, var_a2) ? 1 : 0;
}

typedef struct ActorMotionSub140 {
    u8 pad0[0x1C];
    f32 unk1C;
    f32 unk20;
    u8 unk24;
    u8 pad25[0x3B];
    s32 unk60;
    u8 pad64[8];
    u8 unk6C;
    u8 pad6D[0x1B];
    s32 unk88;
} ActorMotionSub140;

typedef struct ActorMotionSub174 {
    u8 pad0[0x1A3];
    u8 unk1A3;
    u8 pad1A4[0x1C];
    f32 unk1C0;
    u8 pad1C4[8];
    f32 unk1CC;
} ActorMotionSub174;



s32 actorAngleInArc(Actor *arg0, s16 arg1) {
    s16 clamp[2];

    return mathAngleClampToArc(clamp[0], arg1, arg0->arcYawMin, arg0->arcYawMax, &clamp[1]);
}


s32 mathAngleInArcWithMargin(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 clamp[2];

    return mathAngleClampToArcWithMargin(clamp[0], arg2, arg0, arg1, &clamp[1], arg3);
}

s32 actorAngleInArcWithMargin(Actor *arg0, s16 arg1, s16 arg2) {
    s16 clamp[2];

    return mathAngleClampToArcWithMargin(clamp[0], arg1, arg0->arcYawMin, arg0->arcYawMax, &clamp[1], arg2);
}

s32 mathAngleClampToArc(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 *arg4) {
    return mathAngleClampToArcWithMargin(arg0, arg1, arg2, arg3, arg4, 10);
}


s32 mathAngleClampToArcWithMargin(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 *arg4, s16 arg5) {
    s16 innerMin;
    s16 innerMax;
    s16 wrapMin;
    s16 wrapMax;
    u8 wrapCase;

    innerMin = arg2 + arg5;
    innerMax = arg3 - arg5;
    wrapMin = innerMin;
    wrapMax = innerMax;
    if (arg3 >= arg2) {
        if (innerMin < innerMax && arg1 >= innerMin && innerMax >= arg1) {
            *arg4 = arg1;
            return 1;
        }
        *arg4 = mathAngleNearestArcPoint(arg2, arg3, arg1);
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
            if (arg1 >= wrapMin || wrapMax >= arg1) {
                *arg4 = arg1;
                return 1;
            }
            *arg4 = mathAngleNearestArcPoint(arg2, arg3, arg1);
            break;
        case 1:
        case 2:
            if (wrapMin < wrapMax && arg1 >= wrapMin && wrapMax >= arg1) {
                *arg4 = arg1;
                return 1;
            }
            *arg4 = mathAngleNearestArcPoint(arg2, arg3, arg1);
            break;
        case 3:
            *arg4 = mathAngleNearestArcPoint(arg2, arg3, arg1);
            break;
        }
    }

    return 0;
}


s16 mathAngleNearestArcPoint(s16 arg0, s16 arg1, s16 arg2) {
    s32 diffMin;
    s32 diffMax;
    s16 distMin;
    s16 nearMin;
    s16 nearMax;
    s16 distMax;
    s16 result;

    nearMin = arg0 + 10;
    nearMax = arg1 - 10;
    diffMin = arg0 - arg2;
    if (diffMin > 0) {
        distMin = diffMin;
    } else {
        distMin = -diffMin;
    }
    diffMax = arg1 - arg2;
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
    if (arg1 >= arg0) {
        if ((result < arg0) || (arg1 < result)) {
            result = mathAngleArcMidpoint(arg0, arg1);
        }
    } else if ((result < arg0) && (arg1 < result)) {
        result = mathAngleArcMidpoint(arg0, arg1);
    }
    return result;
}

s16 mathAngleArcMidpoint(s16 arg0, s16 arg1) {
    s16 mid;
    s16 wrapped;

    if (arg1 >= arg0) {
        return (arg0 + arg1) >> 1;
    }
    mid = ((arg1 - arg0 + 0xFFF) / 2) + arg0;
    wrapped = mid;
    if (mid >= 0x1000) {
        wrapped = mid - 0xFFF;
    }
    return wrapped;
}



void actorTouchSub140Timestamp(Actor *actor) {
    ActorMotionSub140 *sub = actor->collision;
    if (sub != NULL) {
        sub->unk88 = gFrameCounter;
    }
}


void actorUpdateMovementFlags(Actor *arg0) {
    ActorMotionSub140 *sub;

    if (arg0->unk144 & 8) {
        sub = arg0->collision;
        if (sub->unk6C != 0) {
            arg0->hasArcBounds |= actorResolveModelSlotCollision();
        } else {
            sub->unk60 = 0;
        }
        if (arg0->flags & 0x20) {
            sub = arg0->collision;
            if (sub->unk24 != 0 && actorCheckPointInAngleArc(arg0, sub->unk1C, sub->unk20) != 0) {
                sub = arg0->collision;
                arg0->x = sub->unk1C;
                arg0->z = sub->unk20;
            }
        }
    } else {
        sub = arg0->collision;
        if (sub != NULL) {
            sub->unk6C = 0;
        }
    }
}

u8 actorHasActiveMovementFlags(Actor *arg0) {
    return arg0->attachMode != 0
        || arg0->collision->unk6C != 0
        || arg0->collision->unk24 != 0
        || (arg0->contactFlags & 8) != 0
        || (arg0->contactFlags & 0x400) != 0;
}

void actorClearMovementFlags(Actor *arg0) {
    ActorMotionSub140 *sub;

    sub = arg0->collision;
    arg0->attachMode = 0;
    if (sub != NULL) {
        sub->unk6C = 0;
        arg0->collision->unk24 = 0;
    }
    arg0->contactFlags &= ~8;
    arg0->contactFlags &= ~0x400;
    arg0->renderFlags |= 0x2000;
}

extern s16 D_807FB5F8;
extern s16 D_807FB5FA;

void actorSetCameraBoundaryMode(s32 arg0) {
    D_807FB53C = arg0;
    if (arg0 != 0 && arg0 != 0xBC) {
        D_807FB5F8 = 2;
        D_807FB5FA = 10;
    } else {
        D_807FB5F8 = 100;
        D_807FB5FA = 100;
    }
}

extern Actor *gPrimaryPlayerActor;

s32 actorCheckCameraBoundaryCondition(s8 arg0) {
    ActorMotionSub174 *state;

    switch (arg0) {
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
