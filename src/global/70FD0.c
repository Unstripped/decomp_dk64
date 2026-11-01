#include "common.h"
#include "actor.h"

typedef struct DynamicBuffer {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ void *unk18;
    /* 0x1C */ u8 pad1C[4];
} DynamicBuffer; // size = 0x20

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
extern s32 D_807FB540;
extern s16 D_807FB544;
extern u8 D_807FB546;
extern u8 D_807FB549;
extern u8 D_807FB604;

void *heapAlloc(s32);
void heapFree(void *);

void dynamicBufferPurgeExpired(void);
void collisionBuildSlotBoxes(s32, s32, f32, f32, f32, f32, f32, f32, f32);
void collisionTransformNode(s32, s32, f32, f32, f32, f32, f32, f32, f32);
void dynamicBufferFree(DynamicBuffer *);
void collisionBufferCacheUpdate(void);
void collisionPurgeExpiredBuffers(void);
s32 collisionIsTriangleDegenerate(CollisionTri *);
s8 collisionTriangleSlopeClass(s16 *);
s16 func_8066D4DC();
s32 collisionBuildPlane(CollisionBox *);
void actorSub140Free(ActorSub140 *);
void actorSetNodeValue(Actor *, s32, u16);
void actorOrNodeFlags(Actor *, s32, u8);
void actorClearNodeFlags(Actor *, s32, u8);
ActorSub140 *actorSub140Alloc(f32, f32, f32, f32, f32, f32, s32, s32, s32);
void actorFreeModelNodeList(Actor *);
void actorSetNodeFlag(Actor *, s32);
void actorClearNodeFlag(Actor *, s32);
void actorClearAllNodeFlags(Actor *);
ModelNode *actorGetModelNodeByIndex(Actor *, s32);
ActorSub140 *actorSetCollisionRadius(Actor *, f32);
void actorSub140SetVectors(Actor *, f32, f32, f32, f32);
void actorUpdateModelMatrices(Actor *);
void actorSub140BuildBoxes(ActorSub140 *);
s32 collisionBuildBoxFromMatrix(f32 *, CollisionBox *);
void actorSub140TransformTriangles(ActorSub140 *);
u8 actorSetTargetAngleAndCheck(s32, s16);
void actorClearTargetAngle(void);
u8 actorCheckTargetAngle();

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

typedef struct ModelSlot {
    /* 0x00 */ u8 pad0[0x24];
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

extern u8 D_807444FC;
extern ModelSlot *D_807F6000;

void modelSlotGetTransformVectors(s32, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, s32 *, u8);
void modelBuildBoneChainMatrix();

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

s32 collisionTransformTriangle(u8 *, u8 *, f32 (*)[4]);

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

    off = arg0 * 0x90;
    anim = ((ModelSlot *)((u8 *)D_807F6000 + off))->unk78;
    buf = (CollisionSlotBuffer *)((0, off) + (s32)D_807F6000); // FAKE: comma operand steers addu operand order
    if (D_807F6000 && D_807F6000) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    lastBone = -1;
    buf = (CollisionSlotBuffer *)((u8 *)buf + 0x28);
    if (anim != NULL) {
        sp58 = anim[D_807444FC];
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
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    s32 spD0;
    s32 pad;
    f32 sp8C[4][4];
    f32 sp4C[4][4];
    s32 sp48;
    void *sp44;
    ModelSlot *entry;

    entry = (ModelSlot *)((u8 *)D_807F6000 + arg0 * sizeof(ModelSlot));
    if (entry->unk78 != NULL) {
        sp48 = entry->unk78[D_807444FC];
    } else {
        sp48 = 0;
    }
    sp44 = entry->unk24->unk60 + (u8 *)entry->unk24;
    modelSlotGetTransformVectors(arg0, &spEC, &spE8, &spE4, &spE0, &spDC, &spD8, &spD4, &spD0, 0);
    guScaleF(sp8C, spD4, spD4, spD4);
    guRotateF(sp4C, spE0, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp8C, sp4C, sp8C);
    guRotateF(sp4C, spDC, 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp8C, sp4C, sp8C);
    guRotateF(sp4C, spD8, 0.0f, 0, 1.0f);
    guMtxCatF(sp8C, sp4C, sp8C);
    guTranslateF(sp4C, spEC, spE8, spE4);
    if (arg1 != -1) {
        guMtxCatF(sp8C, sp4C, sp8C);
        modelBuildBoneChainMatrix((arg1 << 5) + (u8 *)sp44, sp48, arg2);
        guMtxCatF(arg2, sp8C, arg2);
        return;
    }
    guMtxCatF(sp8C, sp4C, arg2);
}

void modelBuildBoneChainMatrix(s32 *arg0, u8 *arg1, f32 (*arg2)[4]) {
    s32 i;
    Mtx sp38;

    i = 1;
    memcpy(&sp38, arg0[0] + arg1, 0x40);
    if (arg0[1] != -1) {
        do {
            guMtxCatL(&sp38, (Mtx *)(arg0[i] + arg1), &sp38);
        } while (arg0[++i] != -1);
    }
    guMtxL2F(arg2, &sp38);
}

void collisionTransformNode(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    collisionBuildSlotBoxes(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

void dynamicBufferFree(DynamicBuffer *arg0) {
    if (arg0->unk18 != NULL && (arg0->unk15 & 1)) {
        heapFree(arg0->unk18);
    }
    arg0->unk15 &= ~1;
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

void *assetLoad(s32, s32, s32, s32);
s32 assetGetSize(s32, s32);
void assetSetImmediateFree(void);
void assetFreeBuffer(void *, s32, s32);
void gunzip(void *, void *, void *);

void collisionInitStaticCache(CollisionStaticHeader *arg0) {
    u8 *var_s0;
    void *sp60;
    void *sp5C;
    void *sp58;
    s32 *var_a2;
    u8 *var_v1;
    u8 *temp_a0;
    s32 temp_lo;
    s32 var_a3;
    s32 var_s1;
    s32 elem_size;
    s32 sp38;
    s32 d1;
    void *sp30;

    var_s1 = 4;
    var_s0 = assetLoad(2, gCurrentMap, 1, 0);
    D_807FB549 = 0;
    if (arg0->unk9 & 1) {
        sp60 = var_s0;
        var_s0 = heapAlloc(arg0->unk0);
        sp30 = heapAlloc(0x2400);
        sp5C = var_s0;
        sp58 = sp60;
        gunzip(&sp58, &sp5C, sp30);
        heapFree(sp30);
        assetSetImmediateFree();
        assetFreeBuffer(sp60, 0x14C, 0xA);
        D_807FB549 = 1;
    }
    sp38 = assetGetSize(2, gCurrentMap);
    D_807FB530 = *(s32 *)var_s0;
    D_807FB534 = heapAlloc(0x1518);
    var_a2 = (s32 *)(var_s0 + 4);
    elem_size = 24;
    D_807FB538 = arg0->unk10 * arg0->unk12;
    for (var_a3 = 0; var_a3 < D_807FB538; var_a3++) {
        temp_a0 = var_s0 + var_s1 + 4;
        var_s1 = *var_a2;
        if (D_807FB549 != 0) {
            ((CollisionStaticCellEntry *)D_807FB534)[var_a3].unk4 = temp_a0;
        } else {
            ((CollisionStaticCellEntry *)D_807FB534)[var_a3].unk4 = NULL;
        }
        ((CollisionStaticCellEntry *)D_807FB534)[var_a3].unk0 = NULL;
        ((CollisionStaticCellEntry *)D_807FB534)[var_a3].unkC = (0, sp38) + (temp_a0 - var_s0); // FAKE: comma steers addu operand order (sp38 first)
        ((CollisionStaticCellEntry *)D_807FB534)[var_a3].unk10 = (var_s0 + var_s1) - temp_a0;
        var_a2 = (s32 *)(var_s0 + var_s1);
        ((CollisionStaticCellEntry *)D_807FB534)[var_a3].unk8 = 0;
        ((CollisionStaticCellEntry *)D_807FB534)[var_a3].unk14 = ((s32)(var_s0 + var_s1) - (s32)temp_a0) / elem_size; // FAKE: s32 casts steer the register pick of the subtraction (v1 vs t-reg)
    }
    if (D_807FB549 == 0) {
        assetSetImmediateFree();
        assetFreeBuffer(var_s0, 0x17C, 0xA);
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

void dmaReadAssetDecompress(s32, void *, void *, s32, s32, s32, s32);
s32 collisionBuildStaticTri(void *, void *);

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

void modelSlotTriBufferRelease(ModelSlotTriBuffer *);

void modelSlotExpireNextBuffers(void) {
    DynamicBuffer *a0;
    ModelSlotTriBuffer *a1;

    if (D_80747D70 != 0) {
        D_80748E40++;
        if (D_80748E40 >= D_80747D70) {
            D_80748E40 = 0;
        }
        a0 = &D_807F6000[D_80748E40].unk28;
        if ((a0->unk15 & 1) && ((u32)(gFrameCounter - a0->unk10) >= 0x1F)) {
            dynamicBufferFree(a0);
        }
        a1 = &D_807F6000[D_80748E40].unk48;
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
    sp58[9] = func_8066D4DC(sp58, sp6C);
    COLLISION_TRI_OUT->unk4B = collisionTriangleSlopeClass(sp58);
    COLLISION_TRI_OUT->unk48 = sp58[9];
    COLLISION_TRI_OUT->unk4C = sp6C[0];
    return collisionBuildPlane(COLLISION_TRI_OUT);
#undef COLLISION_TRI_IN
#undef COLLISION_TRI_OUT
}

s32 collisionIsTriangleDegenerate(CollisionTri *arg0) {
    s16 temp_a1;
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = arg0->unk6;
    temp_v1 = arg0->unk0;
    if ((temp_v0 == temp_v1) && (arg0->unk2 == arg0->unk8) && (arg0->unk4 == arg0->unkA)) {
        return 1;
    }
    temp_a1 = arg0->unkC;
    if ((temp_v0 == temp_a1) && (arg0->unkE == arg0->unk8) && (arg0->unk10 == arg0->unkA)) {
        return 1;
    }
    if ((temp_a1 == temp_v1) && (arg0->unk2 == arg0->unkE) && (arg0->unk4 == arg0->unk10)) {
        return 1;
    }
    return 0;
}

f32 func_80611BB4(f32, f32);

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
        angle = func_80611BB4(temp, len);
    }

    if ((f64)(f32)((f64)angle * 57.29577791868205) < 10.0) {
        return 1;
    }
    if ((f64)(f32)((f64)angle * 57.29577791868205) < 45.0) {
        return 2;
    }
    return 0;
}

#ifdef NON_MATCHING

s16 func_8066D4DC(arg0, arg1)
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
        angle = func_80611BB4(var_fa0, var_fa1);
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
    sp34 = sp90[1] * sp9C[0] - sp9C[1] * sp90[0];
    sp38 = sp90[0] * sp9C[2] - sp90[2] * sp9C[0];

    sp54 = -((temp_ft5 * arg0[3]) + (sp38 * (f32)arg0[4]) + ((f32)arg0[5] * sp34));

    dist = (temp_ft5 * sp68[0]) + (sp38 * sp68[1]) + (sp68[2] * sp34) + sp54;

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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066D4DC.s")
#endif


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
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
} CollisionStaticTriOut;

typedef struct CollisionBoxWork {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ f32 unk20;
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
    CollisionBoxWork sp28;
    s32 pad[2];
    s16 temp_a0;
    s16 temp_v1;
    s16 temp_v0;

    sp28.unk24 = COLLISION_TRI_IN->unk0;
    sp28.unk28 = COLLISION_TRI_IN->unk2;
    sp28.unk2C = COLLISION_TRI_IN->unk4;
    sp28.unk30 = COLLISION_TRI_IN->unk6;
    sp28.unk34 = COLLISION_TRI_IN->unk8;
    sp28.unk38 = COLLISION_TRI_IN->unkA;
    sp28.unk3C = COLLISION_TRI_IN->unkC;
    sp28.unk40 = COLLISION_TRI_IN->unkE;
    sp28.unk44 = COLLISION_TRI_IN->unk10;

    sp28.unk24 *= 8; sp28.unk28 *= 8; sp28.unk2C *= 8;
    sp28.unk30 *= 8; sp28.unk34 *= 8; sp28.unk38 *= 8;
    sp28.unk3C *= 8; sp28.unk40 *= 8; sp28.unk44 *= 8;

    sp28.unk48 = COLLISION_TRI_IN->unk12;
    sp28.unk4C = COLLISION_TRI_IN->unk14;
    sp28.unk4D = 0;
    sp28.unk4F = 0;
    if (COLLISION_TRI_IN->unk16 & 4) {
        sp28.unk51 = 1;
    } else {
        sp28.unk51 = 0;
    }
    sp28.unk50 = COLLISION_TRI_IN->unk15;
    sp28.unk4B = 1;
    collisionBuildPlane((CollisionBox *)&sp28);

    *(s64 *)&COLLISION_TRI_OUT->unk0 = *(s64 *)&sp28.unk0;
    *(s64 *)&COLLISION_TRI_OUT->unk8 = *(s64 *)&sp28.unk8;
    *(s64 *)&COLLISION_TRI_OUT->unk10 = *(s64 *)&sp28.unk10;
    *(s64 *)&COLLISION_TRI_OUT->unk18 = *(s64 *)&sp28.unk18;
    COLLISION_TRI_OUT->unk20 = sp28.unk20;

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
        curr8C = arg0->unk8C;
        if (curr8C != NULL) {
            do {
                next8C = curr8C->next;
                heapFree(curr8C);
                curr8C = next8C;
            } while (next8C != NULL);
        }
        curr90 = arg0->unk90;
        if (curr90 != NULL) {
            do {
                next90 = curr90->next;
                heapFree(curr90);
                curr90 = next90;
            } while (next90 != NULL);
        }
        temp = arg0->unkA0;
        if (temp != NULL) {
            heapFree(temp);
        }
        temp = arg0->unk98;
        if (temp != NULL) {
            heapFree(temp);
        }
        heapFree(arg0);
    }
}

typedef struct ActorSub140Tri {
    /* 0x00 */ f32 x[9];
    /* 0x24 */ f32 out[9];
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 pad57;
} ActorSub140Tri; // size = 0x58

typedef struct ActorSub140SrcTri {
    /* 0x00 */ u8 pad0[0x28];
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
    register ActorSub140 *sub140;
    register void *s2;
    register s32 s3;
    register s32 i;
    register s32 one;
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
        s2 = &sub140->unk8C;
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
            s2 = &sub140->unk90;
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
        sub140->unk9C = (s32)s2;
        if (s2 != NULL) {
            sub140->unkA0 = (a3 = heapAlloc((s32)s2 * sizeof(ActorSub140SrcTri)));
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
        sub140->unk94 = (s32)s2;
        if (s2 != NULL) {
            tmp = heapAlloc((s32)s2 * sizeof(ActorSub140Tri));
            sub140->unk98 = tmp;
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
    ModelNode *temp_v0;

    temp_v0 = actorGetModelNodeByIndex(arg0, arg1);
    if (temp_v0 != NULL) {
        temp_v0->unk24 = arg2;
    }
}

void actorOrNodeFlags(Actor *arg0, s32 arg1, u8 arg2) {
    ModelNode *temp_v0;

    temp_v0 = actorGetModelNodeByIndex(arg0, arg1);
    if (temp_v0 != NULL) {
        temp_v0->unk27 |= arg2;
    }
}

void actorClearNodeFlags(Actor *arg0, s32 arg1, u8 arg2) {
    ModelNode *temp_v0;

    temp_v0 = actorGetModelNodeByIndex(arg0, arg1);
    if (temp_v0 != NULL) {
        temp_v0->unk27 &= ~arg2;
    }
}

void func_8066E664(Actor *arg0, s32 arg1, u8 arg2) {
    ActorSub140 *sub;
    ActorSub140SrcTri *ent;
    s32 i;

    sub = arg0->unk140;
    if (arg0->unk140 != NULL) { // FAKE: second read of unk140 keeps the sub copy in $v0
        ent = sub->unkA0;
        for (i = 0; i < sub->unk9C; i++) {
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

    sub = arg0->unk140;
    if (arg0->unk140 != NULL) { // FAKE: second read of unk140 keeps the sub copy in $v0
        ent = sub->unk98;
        for (i = 0; i < sub->unk94; i++) {
            if (arg1 == ent[i].unk54) {
                ent[i].unk56 = arg2;
            }
        }
    }
}

ActorSub140 *actorSub140Alloc(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    ActorSub140 *temp_v0;

    temp_v0 = (ActorSub140 *)heapAlloc(sizeof(ActorSub140));
    temp_v0->unk0 = (s32) (arg0 * 8.0f);
    temp_v0->unk4 = (s32) (arg1 * 8.0f);
    temp_v0->unk8 = (s32) (arg2 * 8.0f);
    temp_v0->unk14 = arg4;
    temp_v0->unk18 = arg5;
    temp_v0->unkC = (s32) (arg4 * arg3 * 8.0f);
    temp_v0->unk10 = (s32) (arg5 * arg3 * 8.0f);
    temp_v0->unk70 = arg6;
    temp_v0->unk74 = arg7;
    temp_v0->unk78 = arg8;
    temp_v0->unk7C = -1;
    temp_v0->unk80 = -2;
    temp_v0->unk84 = -1;
    temp_v0->unk88 = -1;
    temp_v0->unk60 = 0;
    temp_v0->unk6C = 0;
    temp_v0->unk24 = 0;
    temp_v0->unk8C = NULL;
    temp_v0->unk90 = NULL;
    temp_v0->unk94 = 0;
    temp_v0->unk98 = NULL;
    temp_v0->unk9C = 0;
    temp_v0->unkA0 = NULL;
    temp_v0->unkA4 = 0;
    temp_v0->unkA8 = 0;
    temp_v0->unkAC = 0;
    return temp_v0;
}

typedef struct ActorModelSubNode {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ struct ActorModelSubNode *next;
} ActorModelSubNode;

typedef struct ActorModelNode {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ struct ActorModelNode *next;
} ActorModelNode;

void actorAppendModelSubNode(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    f32 pad[3];
    ActorSub140 *sub;
    ActorModelSubNode *node;
    ActorModelSubNode **head;
    ActorModelSubNode *curr;

    sub = arg0->unk140;
    node = (ActorModelSubNode *)heapAlloc(sizeof(ActorModelSubNode));
    node->next = NULL;
    head = (ActorModelSubNode **)&sub->unk90;
    node->unk0 = arg1;
    node->unk4 = arg2;
    node->unk8 = arg3;
    node->unk18 = arg4;
    node->unkC = 0;
    node->unk10 = 0;
    node->unk14 = 0;
    curr = (ActorModelSubNode *)sub->unk90;
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
    ActorModelNode *node;
    ActorModelNode **head;
    ActorModelNode *curr;

    sub = arg0->unk140;
    node = (ActorModelNode *)heapAlloc(sizeof(ActorModelNode));
    node->next = NULL;
    head = (ActorModelNode **)&sub->unk8C;
    node->unk0 = arg1;
    node->unk4 = arg2;
    node->unk8 = arg3;
    node->unkC = arg4;
    node->unk20 = arg5;
    node->unk10 = 0;
    node->unk14 = 0;
    node->unk18 = 0;
    node->unk1C = 0;
    node->unk26 = 1;
    node->unk24 = 0;
    node->unk27 = 0;
    curr = (ActorModelNode *)sub->unk8C;
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

    sub = arg0->unk140;
    if (sub != NULL) {
        node = sub->unk8C;
        if (node != NULL) {
            do {
                next = node->next;
                heapFree(node);
                node = next;
            } while (node != NULL);
        }
        sub->unk8C = NULL;
    }
}

f32 actorGetOrSetNodeScale(Actor *arg0, s32 arg1, f32 arg2) {
    ActorSub140 *sub = arg0->unk140;
    ModelNode *node;

    arg1--;
    node = sub->unk8C;
    while (arg1-- && node != NULL) {
        node = node->next;
    }
    if (node != NULL) {
        if (arg2 != -1.0f) {
            node->unkC = arg2;
        }
        return node->unkC;
    }
    return -1.0f;
}

void actorSetNodeFlag(Actor *arg0, s32 arg1) {
    ModelNode *node = actorGetModelNodeByIndex(arg0, arg1);

    if (node != NULL) {
        node->unk26 = 1;
    }
}

void actorClearNodeFlag(Actor *arg0, s32 arg1) {
    ModelNode *node = actorGetModelNodeByIndex(arg0, arg1);

    if (node != NULL) {
        node->unk26 = 0;
    }
}

void actorClearAllNodeFlags(Actor *arg0) {
    ActorSub140 *sub = arg0->unk140;
    ModelNode *node;

    if (sub != NULL) {
        node = sub->unk8C;
        if (node != NULL) {
            do {
                node->unk26 = 0;
                node = node->next;
            } while (node != NULL);
        }
    }
}

ModelNode *actorGetModelNodeByIndex(Actor *arg0, s32 arg1) {
    ActorSub140 *sub;
    ModelNode *node;

    sub = arg0->unk140;
    arg1--;
    if (sub != NULL) {
        node = sub->unk8C;
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
    ActorSub140 *sub = arg0->unk140;
    sub->unk14 = arg1;
    return sub;
}

void actorSub140SetVectors(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    ActorSub140 *sub = arg0->unk140;

    if (arg0->unk64 & 0x800) {
        arg4 = *(f32 *)arg0->unk120;
    }
    sub->unk0 = (s32)(arg1 * 8.0f);
    sub->unk4 = (s32)(arg2 * 8.0f);
    sub->unk8 = (s32)(arg3 * 8.0f);
    sub->unkC = (s32)(sub->unk14 * arg4 * 8.0f);
    sub->unk10 = (s32)(sub->unk18 * arg4 * 8.0f);
}

void actorUpdateModelMatrices(Actor *arg0) {
    ActorSub140 *sub;
    s32 temp_v0;

    sub = arg0->unk140;
    if (sub != NULL) {
        temp_v0 = arg0->unk60;
        if (!(temp_v0 & 0x80000000) || !(temp_v0 & 0x10)) {
            actorSub140BuildBoxes(sub);
        }
        if (!(arg0->unk64 & 8) || !(arg0->unk60 & 0x10)) {
            actorSub140TransformTriangles(arg0->unk140);
        }
    }
}

void actorSub140BuildBoxes(ActorSub140 *arg0) {
    s32 neg1; // FAKE: one -1 variable shares the compares and the s8 store in one register
    s32 i;
    ActorSub140SrcTri *ent;
    Mtx *mtx;
    u8 var_v1;
    float spCC[4][4];
    f32 *var_s0;
    f32 *var_s1;
    f32 *var_s2;
    f32 *var_s3;
    u32 unk24;
    s32 padB[10];
    CollisionBox *box;
    f32 sp80[3];
    f32 sp74[3];
    f32 sp68[3];
    s32 padE[5];

    neg1 = -1;
    if (arg0->unkA0 != NULL) {
        if (gFrameCounter == arg0->unk88) {
            var_v1 = D_807444FC;
        } else {
            var_v1 = (D_807444FC ^ 1);
        }
        mtx = ((Mtx **)&arg0->unk74)[var_v1];
        ent = arg0->unkA0;
        box = (CollisionBox *)arg0->unkA4;
        i = 0;
        if (arg0->unk9C > 0) {
            do {
                if (arg0 == 0) {} // FAKE
                var_s0 = (f32 *)ent;
                var_s2 = sp68;
                var_s3 = sp74;
                var_s1 = sp80;
                do {
                    unk24 = *(s32 *)((u8 *)ent + 0x24);
                    if ((unk24 ^ 0) == neg1) { // FAKE: ^ 0 steers bne operand order
                        memcpy(spCC, (void *)arg0->unk70, 0x40);
                        guMtxXFMF(spCC, var_s0[0], var_s0[3], var_s0[6], var_s2, var_s3, var_s1);
                    } else {
                        guMtxXFML((Mtx *)(((unk24 >> 6) << 6) + (u8 *)mtx), var_s0[0], var_s0[3], var_s0[6], var_s2, var_s3, var_s1);
                    }
                    var_s1++;
                    var_s0++;
                    var_s2++;
                    var_s3++;
                } while (var_s1 != (f32 *)&box); // FAKE: sentinel = addiu fp,sp,0x8C (the frame slot after sp80), steers a lone hoisted constant
                if (collisionBuildBoxFromMatrix(sp68, box) != 0) {
                    if (*(u8 *)((u8 *)ent + 0x2A) == 0) {
                        box->unk4B = 0;
                    }
                    if (*(u32 *)((u8 *)ent + 0x24) == neg1) {
                        box->unk4E = neg1;
                    } else {
                        box->unk4E = (s8)(*(u32 *)((u8 *)ent + 0x24) >> 6);
                    }
                    box = (CollisionBox *)((u8 *)box + 0x58);
                }
                ent = (ActorSub140SrcTri *)((u8 *)ent + 0x2C);
                i++;
            } while (i < arg0->unk9C);
        }
        arg0->unkA8 = (s32)box;
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

    sp32 = func_8066D4DC(sp20, sp34, arg0);
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

void actorSub140TransformTriangles(ActorSub140 *arg0) {
    ActorSub140Tri *first;
    s32 i;
    u8 var_v1;
    ActorSub140Tri *curr;
    Mtx *mtx;
    float sp6C[4][4];
    s32 j;
    u32 unk48;

    first = arg0->unk98;
    if (first != NULL) {
        if (gFrameCounter == arg0->unk88) {
            var_v1 = D_807444FC;
        } else {
            var_v1 = (D_807444FC ^ 1);
        }
        mtx = ((Mtx **)&arg0->unk74)[var_v1];
        curr = first;
        for (i = 0; i < arg0->unk94; i++) {
            for (j = 0; j < 3; j++) {
                unk48 = (&curr->unk48)[j];
                if ((unk48 ^ 0) == -1) { // FAKE: ^ 0 steers bne operand order
                    memcpy(sp6C, (void *)arg0->unk70, 0x40);
                    guMtxXFMF(sp6C, curr->x[j], curr->x[j + 3], curr->x[j + 6], &curr->out[j], &curr->out[j + 3], &curr->out[j + 6]);
                } else {
                    guMtxXFML((Mtx *)((((unk48 >> 6) << 6)) + (u8 *)mtx), curr->x[j], curr->x[j + 3], curr->x[j + 6], &curr->out[j], &curr->out[j + 3], &curr->out[j + 6]);
                }
            }
            curr = (ActorSub140Tri *)((u8 *)curr + 0x58);
        }
    }
}

u8 actorSetTargetAngleAndCheck(s32 arg0, s16 arg1) {
    s16 sp1E;
    s16 sp1C;
    s8 sp1B;

    D_807FB544 = arg1;
    D_807FB540 = arg0;
    D_807FB546 = 1;
    D_807FB604 = 1;
    actorCheckTargetAngle(arg0, &sp1E, &sp1C, &sp1B);
    return D_807FB546;
}

void actorClearTargetAngle(void) {
    D_807FB604 = 0;
    actorCheckTargetAngle();
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

typedef struct {
    s64 unk0;
    s64 unk8;
    s64 unk10;
    s64 unk18;
    u8 pad20[0x48 - 0x20];
    s16 unk48;
} CollisionPlane;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} CollisionVec3i;

typedef struct {
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
void actorSetCameraBoundaryMode(s32);
void actorCollisionCheckNodeSpheres(CollisionActor *);
s32 actorCheckTargetAngleBounds();
u8 actorCollideModelSlots(CollisionActor *, s16 *, s16 *);
s8 actorCheckCollisionsAgainstActiveActors(CollisionActor *, s16 *, s16 *);
void actorQueueCollisionCallbacks(CollisionActor *);
void actorQueueDelayedCallback();

u8 actorCheckTargetAngle(CollisionActor *arg0, s16 *arg1, s16 *arg2, s8 *arg3) {
    s32 pad;
    u8 sp23;
    u8 sp22;
    ActorSub140State *temp_v0;

    sp23 = 0;
    sp22 = 0;
    temp_v0 = arg0->unk140;
    if (arg0->unk60 & 0x10000) {
        *arg1 = 0;
        *arg2 = 0xFFF;
    }
    if ((temp_v0 == NULL) || !(arg0->unk60 & 0x10)) {
        *arg3 = 0;
        return 0;
    }
    func_80672E90(temp_v0->unk0, temp_v0->unk4, temp_v0->unk8);
    actorSetCameraBoundaryMode(arg0->unk58);
    D_807FB602 = 0;
    D_807FB547 = 0;
    D_807FB605 = 0;
    D_807FB606 = 0;
    if (arg0->unk144 & 0x20) {
        actorCollisionCheckNodeSpheres(arg0);
    }
    if (arg0->unk144 & 8) {
        sp23 = actorCheckTargetAngleBounds(arg0, arg1, arg2);
        sp22 = actorCollideModelSlots(arg0, arg1, arg2);
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
    return (sp23 != 0) || (sp22 != 0);
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
void actorUpdateSubActorOffsets(struct ActorTargetWork *, u8);
void actorUpdateCollisionSpheres();
void actorBuildCollisionHit();
s32 func_80674ADC(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80673708(s32, s32, s32, s32, s32, s32, s16 *, s16 *);
s32 func_806D0964(s32, u8);
extern u8 D_807FB548;
extern u8 D_807FB5FD;
extern u8 D_807FB5FF;
extern u8 D_807FB600;
extern u8 D_807FB601;
extern u8 D_807FB61C;

#define SLOT0 ((ModelSlot *)((0, i * sizeof(ModelSlot)) + (s32)D_807F6000)) // FAKE: comma operand steers addu operand order
#define SLOT ((ModelSlot *)((u8 *)D_807F6000 + i * sizeof(ModelSlot)))
u8 actorCollideModelSlots(CollisionActor *arg0, s16 *arg1, s16 *arg2) {
    u8 sp77;
    ActorSphereNodeHit *node;
    DynamicBuffer *buf;
    u8 *hit;
    s32 i;
    ActorSub140 *sub;
    u8 sp5F;
    u8 ret;
    u8 flag;

    sp77 = 0;
    sub = (ActorSub140 *)arg0->unk140;
    sub->unk6C = 0;
    D_807FB548 = 0;
    for (i = 0; i < D_80747D70; i++) {
        buf = &SLOT0->unk28;
        if (buf->unk15 & 2) {
            if (func_80674ADC(sub->unk0, sub->unk4, sub->unk8, sub->unkC, ((s32 *)buf)[0], ((s32 *)buf)[1], ((s32 *)buf)[2], ((s32 *)buf)[3]) != 0) {
                if (!(buf->unk15 & 1)) {
                    collisionTransformNode(i, (s32)(*SLOT).unk24, ((f32 *)&(*SLOT))[0], ((f32 *)&(*SLOT))[1], ((f32 *)&(*SLOT))[2], ((f32 *)&(*SLOT))[4], ((f32 *)&(*SLOT))[5], ((f32 *)&(*SLOT))[6], ((f32 *)&(*SLOT))[3]);
                } else {
                    buf->unk10 = gFrameCounter;
                }
                if (!(arg0->unk5C & 1) || func_806D0964(*(s32 *)(*SLOT).unk24, arg0->unk174->unk1A4) == 0) {
                    actorUpdateCollisionSpheres(arg0, 0);
                    flag = 1;
                    node = (ActorSphereNodeHit *)sub->unk8C;
                    D_807FB5FD = 0;
                    sp5F = D_807FB602;
                    hit = (u8 *)(*SLOT).unk7C;
                    if (hit != NULL) {
                        if (hit[0x6F] != 0) {
                            D_807FB5FD = 1;
                            D_807FB600 = 0;
                        }
                        flag = ((u8 *)(*SLOT).unk7C)[0x70];
                    }
                    if ((D_807FB5FD == 0 || (arg0->unk144 & 0x10)) && flag != 0) {
                        D_807FB5FF = 0;
                        ret = 0;
                        while (node != NULL && D_807FB5FF == 0) {
                            if (node->unk26 != 0 && node->unk1C != 0 && !(node->unk27 & 6)) {
                                ret |= func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, ((s32 *)buf)[6], ((s32 *)buf)[7], arg1, arg2);
                            }
                            node = node->next;
                        }
                        sp77 |= ret;
                        if (D_807FB601 != 0) {
                            if ((*SLOT).unk7C != NULL) {
                                ((u8 *)(*SLOT).unk7C)[0x5C] = D_807FB601;
                                *(s16 *)(&((u8 *)(*SLOT).unk7C)[0x5E]) = arg0->unk58;
                            }
                        }
                        if (D_807FB5FF != 0) {
                            actorBuildCollisionHit(i, arg0, ((s32 *)buf)[6]);
                        }
                        if ((*SLOT).unk7C != NULL && ((u8 *)(*SLOT).unk7C)[0x6E] == 0) {
                            D_807FB602 = sp5F;
                        }
                        if (ret && D_807FB5FD == 0 && D_807FB61C != 0) {
                            actorUpdateSubActorOffsets((struct ActorTargetWork *)arg0, 0);
                        }
                    }
                }
            }
        }
    }
    return sp77;
}
#undef SLOT0
#undef SLOT

typedef struct ModelSlotHitInfo {
    u8 pad0[0x9B];
    u8 unk9B;
} ModelSlotHitInfo;

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
s32 matrix4Invert(f32 (*)[4], f32 (*)[4]); // FAKE: non-void return flips the $v0/$v1 pick in actorBuildCollisionHit
void modelSlotBuildTransformMatrix(s16, s8, f32 [4][4]);
void func_8066FE08();
struct ActorFacingWork;
s32 func_806744A8(struct ActorFacingWork *, s32, s32, s32, s32);
void actorReflectCollisionAngle(CollisionActor *, CollisionPlane *, CollisionVec3i *);
s32 actorGetCollisionThreshold(CollisionActor *);

void actorBuildCollisionHit(arg0, arg1, arg2)
s32 arg0;
ActorHitView *arg1;
CollisionBox *arg2;
{
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
        if (D_807F6000[arg0].unk7C != NULL && (D_807F6000[arg0].unk7C->unk9B & 0x24)) {
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
        sub->unk26 = *(s16 *)((u8 *)D_807F6000 + off + 0x88);
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

#ifdef NON_MATCHING
typedef struct ModelSlotHitRecord {
    u8 pad0[0x50];
    u8 unk50;
    u8 unk51;
    u8 unk52;
    u8 pad53[0x88 - 0x53];
    s16 unk88;
    s16 unk8A;
    f32 unk8C;
    f32 unk90;
} ModelSlotHitRecord;

extern Actor *D_807FBB40;
f32 sinApprox(f32);
f32 cosApprox(f32);
s32 camDistance3D(s32, s32, s32, s32, s32, s32);

void func_8066FE08(s32 arg0) {
    s16 var_v1;
    s16 temp_a1;
    s32 var_a3;
    s32 temp_v0;
    ModelSlotHitRecord *sub;
    s32 var_a0; // FAKE: s32 so `var_a0 = temp_a0` needs no re-extension; the (s16) casts below re-narrow
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
    s16 temp_a0;
    s16 padW; // FAKE: unused filler word, keeps the frame layout
    f32 sp44;

    var_a3 = 0;
    if (D_807F6000[arg0].unk7C != NULL && D_807FB5D8->unk4D != 0) {
        sub = (ModelSlotHitRecord *)D_807F6000[arg0].unk7C;
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
            temp_a1 = D_807FBB40->unkE6;
            temp_a0 = var_v1 - temp_a1;
            var_a0 = temp_a0;
            if (temp_a0 < 0) {
                var_a0 = (s16)-temp_a0;
            }
            if (var_a0 >= 0x801) {
                var_a0 = (s16)(0xFFF - var_a0);
            }
            temp_a2 = sub->unk8A;
            if (var_a0 && var_a0 && var_a0) {} // FAKE: dead uses raise var_a0 adjsave so it is coloured before temp_a1/temp_a2
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
            temp_a1 = D_807FBB40->unkE6;
            temp_a0 = var_v1 - temp_a1;
            var_a0 = temp_a0;
            if (temp_a0 < 0) {
                var_a0 = (s16)-temp_a0;
            }
            if (var_a0 >= 0x801) {
                var_a0 = (s16)(0xFFF - var_a0);
            }
            temp_a2 = sub->unk8A;
            if (var_a0 && var_a0 && var_a0) {} // FAKE: dead uses raise var_a0 adjsave so it is coloured before temp_a1/temp_a2
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
                sp50 = (f32)camDistance3D((s32)D_807FBB40->unk7C, (s32)D_807FBB40->unk80, (s32)D_807FBB40->unk84, (s32)sp68, (s32)sp64, (s32)sp60);
                if (sp50 < (f32)camDistance3D((s32)D_807FBB40->unk7C, (s32)D_807FBB40->unk80, (s32)D_807FBB40->unk84, (s32)sp5C, (s32)sp58, (s32)sp54)) {
                    sub->unk52 = 1;
                    return;
                }
                sub->unk52 = 2;
            }
            break;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/70FD0/func_8066FE08.s")
#endif

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

typedef struct ModelSlotHitView {
    /* 0x00 */ u8 pad0[0x53];
    /* 0x53 */ u8 unk53;
    /* 0x54 */ u8 pad54[8];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ u8 pad60[0xE];
    /* 0x6E */ u8 unk6E;
    /* 0x6F */ u8 pad6F[0x2C];
    /* 0x9B */ u8 unk9B;
} ModelSlotHitView;

typedef struct ActorHitRecord {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ u8 pad4[0x30];
} ActorHitRecord; // size = 0x34

extern u8 D_807FB603;
extern ActorHitRecord D_807FD614[];
s32 hashTableLookup();
s32 func_806738D0(s32, s32, s32, s32, s32, s32);
u8 playerFindIndexByActor(Actor *);
void actorSetTargetAngleBounds();
struct ActorPlaneContactView;
struct ActorHitPlane;
void actorCalcPlaneContactPoint(struct ActorPlaneContactView *, s16, struct ActorHitPlane *);
struct ActorMotionWork;
s32 actorCheckPointInAngleArc(struct ActorMotionWork *, f32, f32);

s32 actorResolveModelSlotCollision(arg0)
Actor *arg0;
{
    ActorHitSubView *sub;
    s8 pm;
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
    ModelSlotHitView *hit;

    {
        u8 kind;

        kind = 0;
    pm = kind; // FAKE: s8 pad read pairs with slot so the s16 sits at +0 of its word
        sub = (ActorHitSubView *)arg0->unk140;
        ret = 0;
        slot = hashTableLookup(sub->unk26);
        if (slot != -1) {
            buf = &D_807F6000[slot].unk28;
            if (!(buf->unk15 & 1)) {
                return 0;
            }
            D_807FB603 = buf->unk14;
            D_807FB5FD = 1;
            D_807FB600 = 1;
            D_807FB602 = 0;
            func_80672E90(sub->unk0, sub->unk4, sub->unk8);
            actorSetCameraBoundaryMode(arg0->unk58);
            hit = (ModelSlotHitView *)D_807F6000[slot].unk7C;
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
                ret = func_80673708(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, ((s32 *)buf)[6], ((s32 *)buf)[7], &arg0->unkF4, &arg0->unkF6) & 0xFF;
            } else {
                actorSetTargetAngleBounds(((s32 *)buf)[6] + sub->unk58 * 0x58);
                switch (kind) {
                case 0:
                    ret = func_806738D0(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, ((s32 *)buf)[6], ((s32 *)buf)[7]) & 0xFF;
                    func_80673708(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, ((s32 *)buf)[6], ((s32 *)buf)[7], &arg0->unkF4, &arg0->unkF6);
                    break;
                case 1:
                case 2:
                    ret = func_80673708(sub->unk0, sub->unk4, sub->unk8, sub->unk5C, ((s32 *)buf)[6], ((s32 *)buf)[7], &arg0->unkF4, &arg0->unkF6) & 0xFF;
                    break;
                case 3:
                case 4:
                    ret = func_80673708(sub->unk0, sub->unk4, sub->unk8, 0x64, ((s32 *)buf)[6], ((s32 *)buf)[7], &arg0->unkF4, &arg0->unkF6) & 0xFF;
                    break;
                }
            }
            if (D_807FB601 != 0 && hit != NULL) {
                ((ModelSlotHitView *)D_807F6000[slot].unk7C)->unk5C = D_807FB601;
                ((ModelSlotHitView *)D_807F6000[slot].unk7C)->unk5E = arg0->unk58;
            }
            if (D_807F6000[slot].unk7C != NULL && ((ModelSlotHitView *)D_807F6000[slot].unk7C)->unk6E != 0) {
                actorQueueCollisionCallbacks((CollisionActor *)arg0);
            }
            if (hit != NULL && hit->unk53 != 0 && D_807FD614[playerFindIndexByActor(arg0)].unk0 > 30.0) {
                ret = 1;
            }
            if (arg0->unk5C & 1) {
                actorCalcPlaneContactPoint((struct ActorPlaneContactView *)arg0, slot, (struct ActorHitPlane *)sub);
            }
            if (ret != 0) {
                modelSlotBuildTransformMatrix(slot, sub->unk5A, mtx);
                guMtxXFMF(mtx, sub->unk4C, sub->unk50, sub->unk54, &x, &y, &z);
                if (kind == 1 || kind == 4) {
                    arg0->unk7C = x;
                    arg0->unk84 = z;
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
                    if (kind == 3 || actorCheckPointInAngleArc((struct ActorMotionWork *)arg0, x - out[0], z - out[2]) != 0) {
                        arg0->unk7C = x - out[0];
                        arg0->unk84 = z - out[2];
                    }
                }
            } else {
                node = sub->unk8C;
                while (node != NULL) {
                    if (node->unk26 != 0) {
                        i = func_80673708(node->unk10, node->unk14, node->unk18, node->unk1C, ((s32 *)buf)[6], ((s32 *)buf)[7], &arg0->unkF4, &arg0->unkF6); ret = (ret | i) & 0xFF; // FAKE: i as call-result temp keeps 'or ret,ret,v0' operand order and no extra result var
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
extern s16 D_807FD584;

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
        sp54 = D_80753D50[D_807FD584];
    } else {
        sp54 = D_80753D60[D_807FD584];
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

typedef struct {
    u8 pad0[0x48];
    s16 unk48;
} ActorTargetBounds;

extern s16 D_807FB5EC;
extern s16 D_807FB5EE;
extern s16 D_807FB5F0;
extern s16 D_807FB5F2;

void actorSetTargetAngleBounds(ActorTargetBounds *arg0) {
    s16 temp_v0;

    temp_v0 = arg0->unk48;
    D_807FB5EC = temp_v0 - 0x32;
    if (D_807FB5EC < 0) {
        D_807FB5EC += 0xFFF;
    }
    D_807FB5EE = temp_v0 + 0x32;
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
void actorUpdateCollisionExtents(ActorTargetWork *);
s32 actorGetPlayerThreshold(ActorTargetWork *);
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

s32 mathAngleDistance(s16, s16);
s32 func_806744A8(ActorFacingWork *, s32, s32, s32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
s32 func_806732A8(s32, s16);
void actorUpdateSubActorOffsets(ActorTargetWork *, u8);
void actorComputeBoxNormal(ActorTargetWork *, f32 *, f32 *, f32 *, s32);

void actorUpdateFacingAndOffset(ActorFacingWork *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 sp36;
    s32 sp30;
    s32 pad2C;
    s32 sp28;
    s32 temp;
    ActorTargetSub140 *sub;
    f32 temp_f0;
    s32 temp_v1;

    sp36 = mathAngleDistance(arg0->unk48, D_807FB544);
    temp = mathAngleDistance((s16)((arg0->unk48 + 0x800) & 0xFFF), D_807FB544);
    if ((sp36 < 0x321) || (temp < 0x321)) {
        mathAngleDistance(arg0->unk48, gActivePlayerState->unkEA);
        mathAngleDistance((s16)((arg0->unk48 + 0x800) & 0xFFF), gActivePlayerState->unkEA);
        sub = ((ActorFacingWork *)D_807FB540)->unk140;
        func_806744A8(arg0, sub->unk0, sub->unk4, sub->unk8, sub->unkC);
        sp28 = D_807FB5D0;
        sp30 = (s32)(func_80612794(D_807FB544) * 20.0f);
        temp_f0 = func_80612790(D_807FB544);
        sub = ((ActorFacingWork *)D_807FB540)->unk140;
        func_806744A8(arg0, sub->unk0 + sp30, sub->unk4, sub->unk8 + (s32)(temp_f0 * 20.0f), sub->unkC);
        temp_v1 = D_807FB5D0;
        if (sp28 - 2 < temp_v1) {
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
        sp44 = D_80753D50[D_807FD584];
    } else {
        sp44 = D_80753D60[D_807FD584];
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
        f32 temp_fa0;
        f32 scale;
        f32 temp_fa1;
        f32 sp2C;
        f32 sp28;
        f32 sp24;

        actorComputeBoxNormal(arg0, &sp24, &sp28, &sp2C, arg1);
        temp_fa0 = (f32)D_807FB5C4 / (f32)8;
        temp_fa1 = (f32)D_807FB5CC / (f32)8;
        if (D_807FB548 != 0) {
            scale = (f32)actorGetPlayerThreshold(arg0) / (f32)8;
            sp24 *= scale;
            sp2C *= scale;
        } else {
            scale = (f32)(D_807FB5D0 + 6) / (f32)8;
            sp24 *= scale;
            sp2C *= scale;
        }
        sub->unk1C = temp_fa0 - sp24;
        sub->unk20 = temp_fa1 - sp2C;
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

void actorComputeBoxNormal(arg0, arg1, arg2, arg3, arg4)
ActorTargetWork *arg0;
f32 *arg1;
f32 *arg2;
f32 *arg3;
volatile u8 arg4; // FAKE: reload arg4 from its stack home after the calls
{
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
    if (arg4 != 0) {
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
    if (arg4 != 0) {
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

    if (arg0->unk58 == 2) {
        goto ret_32_2;
    }
    if (arg0->unk58 == 3) {
        goto ret_32_1;
    }
    if (arg0->unk58 != 5) {
        goto ret_32_3;
    }
    sub = arg0->unk174;
    if (gPlayerSlots[sub->unk1A4].unk2C0 != 1) {
        return 0x14;
    }
    return 0x32;
ret_32_1:
    return 0x32;
ret_32_2:
    return 0x32;
ret_32_3:
    return 0x32;
}

typedef struct ActorSphereNode {
    f32 x;
    f32 y;
    f32 z;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u32 unk20;
    u8 pad24[4];
    struct ActorSphereNode *unk28;
} ActorSphereNode;

typedef struct ActorSub140SphereView {
    u8 pad0[0x70];
    void *unk70;
    s32 unk74[2];
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    ActorSphereNode *unk8C;
} ActorSub140SphereView;

typedef struct ActorSphereUpdateView {
    u8 pad0[4];
    f32 *unk4;
    u8 pad8[0x64 - 8];
    u32 unk64;
    u8 pad68[0x120 - 0x68];
    f32 unk120;
    u8 pad124[0x140 - 0x124];
    ActorSub140SphereView *unk140;
} ActorSphereUpdateView;

void actorUpdateCollisionSpheres(arg0, arg1)
ActorSphereUpdateView *arg0;
u8 arg1;
{
    f32 scale = 0.15f;
    ActorSub140SphereView *sub = arg0->unk140;
    f32 sp_b4;
    f32 sp_b0;
    f32 sp_ac;
    f32 mtx[4][4];
    ActorSphereNode *node;
    s32 base;
    u8 idx;

    if (arg1 != 0 || sub->unk7C != sub->unk80) {
        if (arg0->unk4 != NULL) {
            scale = arg0->unk4[0xE];
        }
        if (arg0->unk64 & 0x800) {
            scale = arg0->unk120;
        }
        if (gFrameCounter == sub->unk88) {
            idx = D_807444FC;
        } else {
            idx = D_807444FC ^ 1;
        }
        node = sub->unk8C;
        base = sub->unk74[idx];
        if (base) {} // FAKE: raises base coloring priority (swaps s5/s6)
        while (node != NULL) {
            if (node->unk20 == -1) {
                memcpy(mtx, sub->unk70, 0x40);
                guMtxXFMF(mtx, node->x, node->y, node->z, &sp_b4, &sp_b0, &sp_ac);
            } else {
                guMtxXFML((Mtx *)(((node->unk20 >> 6) << 6) + base), node->x, node->y, node->z, &sp_b4, &sp_b0, &sp_ac);
            }
            node->unk10 = sp_b4 * 8.0f;
            node->unk14 = sp_b0 * 8.0f;
            node->unk18 = sp_ac * 8.0f;
            node->unk1C = node->unkC * scale * 8.0f;
            node = node->unk28;
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

void actorUpdateNodePositions(ActorSub140PointView *arg0, u8 arg1) {
    ActorTargetNode *node;
    u8 var_v0;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 mtx[4][4];
    s32 mtx_base;

    if (arg1 || (gFrameCounter != arg0->unk84)) {
        if (gFrameCounter == arg0->unk88) {
            var_v0 = D_807444FC;
        } else {
            var_v0 = D_807444FC ^ 1;
        }
        node = arg0->unk90;
        mtx_base = arg0->unk74[var_v0];
        if (node != NULL) {
            if (mtx_base) {} // FAKE: raises mtx_base register priority so -1 gets s5, mtx_base s6
            do {
                if (node->unk18 == -1) {
                    memcpy(&mtx, arg0->unk70, sizeof(mtx));
                    guMtxXFMF(mtx, node->x, node->y, node->z, &spA4, &spA0, &sp9C);
                } else {
                    guMtxXFML((Mtx *)(((node->unk18 >> 6) << 6) + mtx_base), node->x, node->y, node->z, &spA4, &spA0, &sp9C);
                }
                node->unkC = (s32)(spA4 * 8.0f);
                node->unk10 = (s32)(spA0 * 8.0f);
                node->unk14 = (s32)(sp9C * 8.0f);
                node = node->next;
            } while (node != NULL);
        }
        arg0->unk84 = gFrameCounter;
    }
}

s32 actorGetNodePos(ActorTargetWork *arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    s32 pad0;
    s32 pad1;
    s32 pad2;
    ActorTargetSub140 *sub;
    ActorTargetNode *node;
    s32 count;

    sub = arg0->unk140;
    if (sub != NULL) {
        actorUpdateNodePositions(sub, 1);
        node = arg0->unk140->unk90;
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
        val = D_807444FC;
    } else {
        val = D_807444FC ^ 1;
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

u8 collisionTestSphereSlots(f32, f32, f32, f32, s16 *, s16 *);

s32 collisionTestSphere(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 *arg4, s16 *arg5, u8 arg6, u16 arg7) {
    u8 ret;

    arg0 *= 8.0f;
    arg1 *= 8.0f;
    arg2 *= 8.0f;
    *arg4 = 0;
    *arg5 = 0xFFF;
    arg3 *= 8.0f;
    D_807FB606 = 0;
    func_80672E90(arg0, arg1, arg2);
    actorSetCameraBoundaryMode(arg7);
    if (arg6 != 0) {
        ret = func_806734E4((s32)arg0, (s32)arg1, (s32)arg2, (s32)arg3, arg4, arg5);
        ret |= collisionTestSphereSlots(arg0, arg1, arg2, arg3, arg4, arg5);
    } else {
        ret = func_806730A4(arg0, arg1, arg2, (s32)arg3);
        if (ret == 0) {
            ret = collisionTestSphereSlots(arg0, arg1, arg2, arg3, arg4, arg5);
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

typedef struct ModelSlotHitEnableView {
    u8 pad0[0x70];
    u8 unk70;
} ModelSlotHitEnableView;


u8 collisionTestSphereSlots(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 *arg4, s16 *arg5) {
    s32 temp_ft0;
    s32 temp_ft1;
    s32 temp_ft2;
    s32 temp_ft3;
    u8 var_fp;
    s32 var_s6;
    void *temp_s0;
    ModelSlotHitEnableView *temp_v0;

    var_fp = 0;
    D_807FB5FD = 0;
    var_s6 = 0;
    if (D_80747D70 > 0) {
        do {
            temp_s0 = (void *)((0, var_s6 * 0x90) + (s32)D_807F6000); // FAKE: (0, off) + (s32)G steers addu operand order
            if ((temp_s0 = (void *)((u8 *)temp_s0 + 0x28), *(s32 *)((u8 *)temp_s0 + 0x18)) != 0 &&
                (D_807FB53C != 0xBC || (*(u8 *)((u8 *)D_807F6000 + var_s6 * 0x90 + 0x6C) & 2))) { // FAKE: comma advances temp_s0 before the branch without a val local
                temp_ft0 = arg0;
                temp_ft1 = arg1;
                temp_ft2 = arg2;
                temp_ft3 = arg3;
                if (func_80674ADC(temp_ft0, temp_ft1, temp_ft2, temp_ft3,
                                  *(s32 *)((u8 *)temp_s0 + 0x0),
                                  *(s32 *)((u8 *)temp_s0 + 0x4),
                                  *(s32 *)((u8 *)temp_s0 + 0x8),
                                  *(s32 *)((u8 *)temp_s0 + 0xC)) != 0 &&
                    (*(u8 *)((u8 *)temp_s0 + 0x15) & 1) &&
                    ((temp_v0 = *(ModelSlotHitEnableView **)((u8 *)D_807F6000 + var_s6 * 0x90 + 0x7C)) == NULL || temp_v0->unk70 != 0)) {
                    var_fp |= func_80673708(temp_ft0, temp_ft1, temp_ft2, temp_ft3, *(s32 *)((u8 *)temp_s0 + 0x18), *(s32 *)((u8 *)temp_s0 + 0x1C), arg4, arg5);
                }
            }
            var_s6++;
        } while (var_s6 < D_80747D70);
    }
    return var_fp;
}

s16 mathAngleArcMidpoint();

s16 func_80672134(arg0, arg1, arg2, arg3)
s16 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
{
    s16 var_a3;
    f32 var_fv1;
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

    var_a3 = arg2 + 0x800;
    if (var_a3 >= 0x1000) {
        var_a3 -= 0x1000;
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
    if ((var_a3 - bisect) > 0) {
        diff2 = var_a3 - bisect;
    } else {
        diff2 = -(var_a3 - bisect);
    }
    if (diff2 >= 0x800) {
        diff2 = 0xFFF - diff2;
    }

    if (diff1 != 0) {
        var_fv1 = (f32)diff2 / (f32)diff1;
    } else {
        var_fv1 = 0.0f;
    }

    if (var_fv1 > 1.0) {
        var_fv1 = 1.0f;
    }
    if (var_fv1 < 0.2) {
        var_fv1 = 0.0f;
    }
    return (s16)(s32)((f32)arg3 * var_fv1);
}

typedef struct ActorPosXZView {
    u8 pad0[0x88];
    f32 unk88;
    u8 pad8C[4];
    f32 unk90;
} ActorPosXZView;

struct ActorMotionWork;
s32 func_80611E60(s32);
s32 actorAngleInArc(struct ActorMotionWork *, s16);

s32 actorCheckPointInAngleArc(struct ActorMotionWork *arg0, f32 arg1, f32 arg2) {
    s32 sp28;
    s32 sp24;
    s32 sp44;
    s32 sp40;
    s32 sp20;
    s32 sp1C;
    f32 sp34;
    s16 var_a2;

    sp44 = (s32)(((ActorPosXZView *)arg0)->unk88 * 8.0f);
    sp40 = (s32)(((ActorPosXZView *)arg0)->unk90 * 8.0f);
    sp28 = (s32)(arg1 * 8.0f);
    sp24 = (s32)(arg2 * 8.0f);
    sp20 = sp28 - sp44;
    sp1C = sp24 - sp40;
    sp34 = sqrtf((f32)((sp20 * sp20) + (sp1C * sp1C)));
    if ((f64)sp34 == 0.0) {
        return 1;
    }
    if (sp20 >= 0 && sp1C >= 0) {
        var_a2 = (s16)(func_80611E60((s32)(((f64)sp20 * 65535.9) / (f64)sp34)) >> 4);
    }
    if (sp20 >= 0 && sp1C < 0) {
        var_a2 = (func_80611E60((s32)(((f64)(sp40 - sp24) * 65535.9) / (f64)sp34)) >> 4) + 0x400;
    }
    if (sp20 < 0 && sp1C < 0) {
        var_a2 = (func_80611E60((s32)(((f64)(sp44 - sp28) * 65535.9) / (f64)sp34)) >> 4) + 0x800;
    }
    if (sp20 < 0 && sp1C >= 0) {
        var_a2 = (func_80611E60((s32)(((f64)sp1C * 65535.9) / (f64)sp34)) >> 4) + 0xC00;
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

typedef struct ActorMotionWork {
    u8 pad0[0x60];
    u32 unk60;
    u32 unk64;
    u16 unk68;
    u16 unk6A;
    u8 pad6C[0x10];
    f32 unk7C;
    u8 pad80[4];
    f32 unk84;
    u8 pad88[0x6C];
    s16 unkF4;
    s16 unkF6;
    u8 padF8[4];
    u8 unkFC;
    u8 padFD[0x13];
    u8 unk110;
    u8 pad111[0x2F];
    ActorMotionSub140 *unk140;
    u8 unk144;
    u8 pad145[0x2F];
    ActorMotionSub174 *unk174;
} ActorMotionWork;

void mathAngleClampToArc();

s32 actorAngleInArc(arg0, arg1)
ActorMotionWork *arg0;
s16 arg1;
{
    s16 sp24[2];

    mathAngleClampToArc(sp24[0], arg1, arg0->unkF4, arg0->unkF6, &sp24[1]);
}

s32 mathAngleClampToArcWithMargin();

void mathAngleInArcWithMargin(arg0, arg1, arg2, arg3)
s16 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
{
    s16 sp24[2];

    mathAngleClampToArcWithMargin(sp24[0], arg2, arg0, arg1, &sp24[1], arg3);
}

void actorAngleInArcWithMargin(arg0, arg1, arg2)
ActorMotionWork *arg0;
s16 arg1;
s16 arg2;
{
    s16 sp24[2];

    mathAngleClampToArcWithMargin(sp24[0], arg1, arg0->unkF4, arg0->unkF6, &sp24[1], arg2);
}

void mathAngleClampToArc(arg0, arg1, arg2, arg3, arg4)
s16 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
s16 *arg4;
{
    mathAngleClampToArcWithMargin(arg0, arg1, arg2, arg3, arg4, 10);
}

s16 mathAngleNearestArcPoint(s16, s16, s16);

s32 mathAngleClampToArcWithMargin(arg0, arg1, arg2, arg3, arg4, arg5)
s32 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
s16 *arg4;
s16 arg5;
{
    s16 temp_t0;
    s16 temp_t1;
    s16 var_t2;
    s16 var_t3;
    u8 var_a0;

    temp_t0 = arg2 + arg5;
    temp_t1 = arg3 - arg5;
    var_t2 = temp_t0;
    var_t3 = temp_t1;
    if (arg3 >= arg2) {
        if (temp_t0 < temp_t1 && arg1 >= temp_t0 && temp_t1 >= arg1) {
            *arg4 = arg1;
            return 1;
        }
        *arg4 = mathAngleNearestArcPoint(arg2, arg3, arg1);
        goto ret_0;
    }

    var_a0 = 0;
    if (temp_t0 >= 0x1000) {
        var_t2 = temp_t0 - 0x1000;
        var_a0 = 1;
    }
    if (temp_t1 < 0) {
        var_t3 = temp_t1 + 0x1000;
        var_a0 += 2;
    }

    switch (var_a0) {
    default:
        return 0;
    case 0:
        if (arg1 >= var_t2 || var_t3 >= arg1) {
            *arg4 = arg1;
            return 1;
        }
        *arg4 = mathAngleNearestArcPoint(arg2, arg3, arg1);
        break;
    case 1:
    case 2:
        if (var_t2 < var_t3 && arg1 >= var_t2 && var_t3 >= arg1) {
            *arg4 = arg1;
            return 1;
        }
        *arg4 = mathAngleNearestArcPoint(arg2, arg3, arg1);
        break;
    case 3:
        *arg4 = mathAngleNearestArcPoint(arg2, arg3, arg1);
        break;
    }

ret_0:
    return 0;
}


s16 mathAngleNearestArcPoint(arg0, arg1, arg2)
s16 arg0;
s16 arg1;
s16 arg2;
{
    s32 temp_v0;
    s32 temp_v1;
    s16 var_a0;
    s16 var_a3;
    s16 var_t0;
    s16 var_v0;
    s16 var_v1;

    var_a3 = arg0 + 10;
    var_t0 = arg1 - 10;
    temp_v0 = arg0 - arg2;
    if (temp_v0 > 0) {
        var_a0 = temp_v0;
    } else {
        var_a0 = -temp_v0;
    }
    temp_v1 = arg1 - arg2;
    if (var_a0 >= 0x801) {
        var_a0 = 0xFFF - var_a0;
    }
    if (temp_v1 > 0) {
        var_v0 = temp_v1;
    } else {
        var_v0 = -temp_v1;
    }
    if (var_v0 >= 0x801) {
        var_v0 = 0xFFF - var_v0;
    }
    if (var_v0 >= var_a0) {
        if (var_a3 >= 0x1000) {
            var_a3 -= 0xFFF;
        }
        var_v1 = var_a3;
    } else {
        if (var_t0 < 0) {
            var_t0 += 0xFFF;
        }
        var_v1 = var_t0;
    }
    if (arg1 >= arg0) {
        if ((var_v1 < arg0) || (arg1 < var_v1)) {
            var_v1 = mathAngleArcMidpoint(arg0, arg1);
        }
    } else if ((var_v1 < arg0) && (arg1 < var_v1)) {
        var_v1 = mathAngleArcMidpoint(arg0, arg1);
    }
    return var_v1;
}

s16 mathAngleArcMidpoint(arg0, arg1)
s16 arg0;
s16 arg1;
{
    s16 temp_v0;
    s16 var_v1;

    if (arg1 >= arg0) {
        return (arg0 + arg1) >> 1;
    }
    temp_v0 = ((arg1 - arg0 + 0xFFF) / 2) + arg0;
    var_v1 = temp_v0;
    if (temp_v0 >= 0x1000) {
        var_v1 = temp_v0 - 0xFFF;
    }
    return var_v1;
}



void actorTouchSub140Timestamp(ActorMotionWork *arg0) {
    ActorMotionSub140 *temp_v0 = arg0->unk140;
    if (temp_v0 != NULL) {
        temp_v0->unk88 = gFrameCounter;
    }
}

s32 actorResolveModelSlotCollision();
s32 actorCheckPointInAngleArc(ActorMotionWork *, f32, f32);

void actorUpdateMovementFlags(ActorMotionWork *arg0) {
    ActorMotionSub140 *temp_v0;

    if (arg0->unk144 & 8) {
        temp_v0 = arg0->unk140;
        if (temp_v0->unk6C != 0) {
            arg0->unkFC |= actorResolveModelSlotCollision();
        } else {
            temp_v0->unk60 = 0;
        }
        if (arg0->unk60 & 0x20) {
            temp_v0 = arg0->unk140;
            if (temp_v0->unk24 != 0 && actorCheckPointInAngleArc(arg0, temp_v0->unk1C, temp_v0->unk20) != 0) {
                temp_v0 = arg0->unk140;
                arg0->unk7C = temp_v0->unk1C;
                arg0->unk84 = temp_v0->unk20;
            }
        }
    } else {
        temp_v0 = arg0->unk140;
        if (temp_v0 != NULL) {
            temp_v0->unk6C = 0;
        }
    }
}

u8 actorHasActiveMovementFlags(ActorMotionWork *arg0) {
    return arg0->unk110 != 0
        || arg0->unk140->unk6C != 0
        || arg0->unk140->unk24 != 0
        || (arg0->unk6A & 8) != 0
        || (arg0->unk6A & 0x400) != 0;
}

void actorClearMovementFlags(ActorMotionWork *arg0) {
    ActorMotionSub140 *temp_v0;

    temp_v0 = arg0->unk140;
    arg0->unk110 = 0;
    if (temp_v0 != NULL) {
        temp_v0->unk6C = 0;
        arg0->unk140->unk24 = 0;
    }
    arg0->unk6A &= ~8;
    *(u16*)((u8*)arg0 + 0x6A) &= ~0x400;
    arg0->unk64 |= 0x2000;
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

extern ActorMotionWork *D_807FBB4C;

s32 actorCheckCameraBoundaryCondition(s8 arg0) {
    ActorMotionSub174 *temp_v0;

    switch (arg0) {
    case 0:
        if (D_807FB53C == 0xBC) {
            return 1;
        }
        goto ret_0;
    case 1:
        if (D_807FB53C != 0xBC) {
            return 1;
        }
        goto ret_0;
    case 2:
        if (D_807FB53C != 5 || gPlayerSlots->unk2C0 == 1) {
            return 1;
        }
        goto ret_0;
    case 3:
        if (D_807FB53C == 5 && gPlayerSlots->unk2C0 != 1) {
            return 1;
        }
        goto ret_0;
    case 4:
        if (D_807FB53C == 8) {
            return 1;
        }
        goto ret_0;
    case 5:
        D_807FB548 = 1;
        return 1;
    case 6:
        temp_v0 = D_807FBB4C->unk174;
        if (D_807FB53C == 3 && temp_v0->unk1A3 != 0) {
            return 1;
        }
        goto ret_0;
    case 7:
        temp_v0 = D_807FBB4C->unk174;
        if (D_807FB53C == 6 && (gPlayerSlots->unk2C0 != 1 || temp_v0->unk1CC != temp_v0->unk1C0)) {
            return 1;
        }
        goto ret_0;
    case 8:
        if (D_807FB53C == 9) {
            return 1;
        }
        goto ret_0;
    }
ret_0:
    return 0;
}

static void actorBoundaryStub(void) {
}
s32 randomLcgNext(void);

s32 actorRng(void) {
    return randomLcgNext();
}
