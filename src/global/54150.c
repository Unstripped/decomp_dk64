#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "proto/global/136820.h"
#include "proto/global/15050.h"
#include "proto/global/17800.h"
#include "proto/global/36880.h"
#include "proto/global/54150.h"
#include "proto/global/5E020.h"

typedef struct ModelAnimNodeHeader {
    u8 keyCount;
    u8 times[0x38];
    u8 matrixCount;
    u8 pad3A[2];
} ModelAnimNodeHeader;


void modelSlotAllocAnimBuffers(ModelData **outModel, u8 *animAsset) {
    u8 *p2;
    u32 n;
    u8 *p1;
    u8 *src;
    u32 size;
    ModelData *m;
    u32 i;

    if (*(u32 *)(animAsset + 0x68) != *(u32 *)(animAsset + 0x64)) {
        m = heapAlloc(0xD0);
        *outModel = m;
        n = *(u32 *)(animAsset + *(u32 *)(animAsset + 0x68));
        m->frames[0] = heapAlloc(n);
        m->frames[1] = heapAlloc(n);
        src = animAsset + *(u32 *)(animAsset + 0x68);
        size = *(u32 *)(src + 4);
        memcpy(m->frames[0], src + 8, size);
        memcpy(m->frames[1], src + 8, size);
        i = (n - size) >> 6;
        p1 = m->frames[0] + size;
        p2 = m->frames[1] + size;
        for (; i != 0; i--) {
            guMtxIdent((Mtx *)p1);
            guMtxIdent((Mtx *)p2);
            p1 += 0x40;
            p2 += 0x40;
        }
        {
            u8 *q = animAsset + *(u32 *)(animAsset + 0x64);
            s32 j;

            for (j = 0; j < 10; j++) {
                ModelAnimEntry *v = &m->entries[j];
                v->unk0 = q + *(u32 *)(q + j * 4);
                v->unk4 = 0.0f;
                v->unk8 = 0;
                v->unkA = 0;
                v->unkE = 0;
                v->unkF = 0;
                v->unk10 = 0;
                v->unk11 = 0;
                v->unkC = 1;
                v->unk12 = 0;
                v->unk13 = 0;
            }
        }
    } else {
        *outModel = NULL;
    }
}

typedef struct ModelAnimEntryRaw {
    ModelAnimNodeHeader *unk0;
    f32 unk4;
    u8 pad8[6];
    u8 unkE;
    u8 padF[2];
    u8 unk11;
    u8 pad12;
    u8 unk13;
} ModelAnimEntryRaw;

extern ModelSlot *gModelSlots;

u32 modelSlotDataSize(s16 slot) {
    ModelAssetHeader *p = gModelSlots[slot].unk24;

    return *(u32 *)(p->unk68 + (u8 *)p);
}

void modelSlotCopyData(u8 *src, s16 slot) {
    ModelAssetHeader *obj;
    ModelData *dst;
    s32 n;
    f32 x;
    f32 y;
    f32 z;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;

    obj = gModelSlots[slot].unk24;
    dst = gModelSlots[slot].unk78;
    n = *(s32 *)(obj->unk68 + (u8 *)obj);
    memcpy(dst->frames[0], src, n);
    memcpy(dst->frames[1], src, n);
    modelSlotGetTransformVectors(slot, &x, &y, &z, &a, &b, &c, &d, &e, 0);
    modelSlotTransformBoundsAndNodes(slot, x, y, z, a, b, c, d, e, 0, 0, 0, 0, 1);
}


void modelSlotFree(ModelData *anim) {
    if (anim != NULL) {
        heapFreeDeferred(anim->frames[0]);
        heapFreeDeferred(anim->frames[1]);
        mtxCopyQueueCancelGroup(anim);
        heapFree(anim);
    }
}

extern u32 D_807F6BE0;
extern u32 D_807F6BE4;
extern u32 D_807F6BE8;
extern u8 D_807F6BEC;
extern u8 gGfxBufferIndex;

u8 modelSlotStepAnimations(s16 modelId) {
    ModelData *group;
    u8 *p;
    s32 i;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    D_807F6BEC = 0;
    if (group != NULL) {
        D_807F6BE0 = ((u32 *)group)[gGfxBufferIndex];
        D_807F6BE4 = ((u32 *)group)[gGfxBufferIndex ^ 1];
        D_807F6BE8 = (u32)group;
        i = 0;
        p = (u8 *)group;
        for (; i != 0xC8; i += 0x14) {
            if (((ModelAnimEntry *)(p + 8))->unkE == 1) {
                modelAnimEntryStep(p + 8);
                D_807F6BEC = 1;
            }
            p += 0x14;
        }
        mtxCopyQueueFlush((s32)group);
    }
    return D_807F6BEC;
}


void modelAnimEntryStep(void *entry) {
    modelAnimEntryAdvance(entry);
    modelAnimEntryBuildNodeMatrices(entry);
}

typedef struct ModelBTrack {
    u8 *unk0;
    u8 *unk4;
} ModelBTrack;

typedef struct ModelBKey {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} ModelBKey; /* 0x24 */


void modelAnimEntryBuildNodeMatrices(ModelAnimEntryRaw *entry) {
    ModelAnimNodeHeader *node;
    s16 stride;
    s32 i;
    u8 *p;
    u32 srcBase;
    u32 dstBase;
    u32 dst;
    u32 src;

    node = entry->unk0;
    stride = node->keyCount * 0x24 + 8;
    srcBase = D_807F6BE0;
    dstBase = D_807F6BE4;
    i = 0;
    p = (u8 *)(node + 1);
    while (i < node->matrixCount) {
        modelAnimEntryBuildKeyMatrix(entry->unk11, entry->unk4, p, p + 8, entry->unk13);
        dst = *(u32 *)p + dstBase;
        if (entry->unkE == 0) {
            src = *(u32 *)p + srcBase;
            mtxCopyQueuePush(D_807F6BE8, src, dst);
        } else {
            mtxCopyQueueCancelDest(dst);
        }
        i++;
        p += stride;
    }
}

void modelAnimEntryQueueMatrixCopies(u32 *group, u32 *entry) {
    ModelAnimNodeHeader *node;
    s16 stride;
    s32 i;
    u8 *p;
    u32 srcBase;
    u32 dstBase;
    u32 dst;

    node = (ModelAnimNodeHeader *)*entry;
    stride = node->keyCount * 0x24 + 8;
    srcBase = D_807F6BE0 = group[gGfxBufferIndex ^ 1];
    dstBase = D_807F6BE4 = group[gGfxBufferIndex];
    if (gGfxBufferIndex == 0) {}  // FAKE: deadsweep dead statement (extends gGfxBufferIndex live range: v1 not v0, address temps a2/a3)
    p = (u8 *)(node + 1);
    i = 0;
    while (i < node->matrixCount) {
        dst = *(u32 *)p + dstBase;
        mtxCopyQueuePush(group, *(u32 *)p + srcBase, dst);
        i++;
        p += stride;
    }
    if (gGfxBufferIndex && gGfxBufferIndex) {}  // FAKE: deadsweep dead statement (extends gGfxBufferIndex live range: v1 not v0, address temps a2/a3)
}


void modelAnimEntryBuildKeyMatrix(u8 key, f32 t, ModelBTrack *track, u8 *keys, u8 scaleMode)
{
    u32 off;
    f32 x;
    f32 y;
    f32 z;
    f32 tx;
    f32 ty;
    f32 tz;
    f32 sx;
    f32 sy;
    f32 sz;
    f32 next;
    f32 prev;
    f32 next2;
    f32 prev2;
    s32 pad[3];
    float work[4][4];
    float mtx[4][4];

    off = D_807F6BE0;
    next = ((ModelBKey *)keys)[key + 1].unkC;
    prev = ((ModelBKey *)keys)[key].unkC;
    x = next - prev;
    if (-180.0 > x) {
        x += 360.0;
    } else if (180.0 < x) {
        x -= 360.0;
    }
    x *= t;
    x += prev;
    next = ((ModelBKey *)keys)[key + 1].unk10;
    prev = ((ModelBKey *)keys)[key].unk10;
    y = next - prev;
    if (y < -180.0) {
        y += 360.0;
    } else if (y > 180.0) {
        y -= 360.0;
    }
    y *= t;
    y += prev;
    next = ((ModelBKey *)keys)[key + 1].unk14;
    prev = ((ModelBKey *)keys)[key].unk14;
    z = next - prev;
    if (z < -180.0) {
        z += 360.0;
    } else if (180.0 < z) {
        z -= 360.0;
    }
    z *= t;
    z += prev;
    tx = ((ModelBKey *)keys)[key + 1].unk18 - ((ModelBKey *)keys)[key].unk18;
    tx *= t;
    tx += ((ModelBKey *)keys)[key].unk18;
    ty = ((ModelBKey *)keys)[key + 1].unk1C - ((ModelBKey *)keys)[key].unk1C;
    ty *= t;
    ty += ((ModelBKey *)keys)[key].unk1C;
    tz = ((ModelBKey *)keys)[key + 1].unk20 - ((ModelBKey *)keys)[key].unk20;
    tz *= t;
    tz += ((ModelBKey *)keys)[key].unk20;
    next2 = ((ModelBKey *)keys)[key + 1].unk0;
    prev2 = ((ModelBKey *)keys)[key].unk0;
    sx = (next2 - prev2) * t + prev2;
    next2 = ((ModelBKey *)keys)[key + 1].unk4;
    prev2 = ((ModelBKey *)keys)[key].unk4;
    sy = (next2 - prev2) * t + prev2;
    next2 = ((ModelBKey *)keys)[key + 1].unk8;
    prev2 = ((ModelBKey *)keys)[key].unk8;
    sz = (next2 - prev2) * t + prev2;
    switch (scaleMode & 0xF) {
    case 0:
        break;
    case 1:
        tx *= (f32)((scaleMode >> 4 & 0xF) * 0.125);
        break;
    case 2:
        ty *= (f32)((scaleMode >> 4 & 0xF) * 0.125);
        break;
    case 3:
        tz *= (f32)((scaleMode >> 4 & 0xF) * 0.125);
        break;
    case 4:
        x *= (f32)((scaleMode >> 4 & 0xF) * 0.125);
        break;
    case 5:
        y *= (f32)((scaleMode >> 4 & 0xF) * 0.125);
        break;
    case 6:
        z *= (f32)((scaleMode >> 4 & 0xF) * 0.125);
        break;
    case 7:
        sx *= (f32)((scaleMode >> 4 & 0xF) * 0.125);
        break;
    case 8:
        sy *= (f32)((scaleMode >> 4 & 0xF) * 0.125);
        break;
    case 9:
        sz = ((next2 - prev2) * t + prev2) * (f32)((scaleMode >> 4 & 0xF) * 0.125);
        break;
    }
    memcpy(work, track->unk4 + off, 0x40);
    guScaleF(mtx, sx, sy, sz);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationZ(mtx, z);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationY(mtx, y);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationX(mtx, x);
    guMtxCatF(work, mtx, work);
    guTranslateF(mtx, tx, ty, tz);
    guMtxCatF(work, mtx, work);
    memcpy(mtx, track->unk4 + 0x40 + off, 0x40);
    guMtxCatF(work, mtx, work);
    guMtxF2L(work, (Mtx *)(off + track->unk0));
}

typedef struct ModelAnimEntryView {
    ModelAnimNodeHeader *unk0;
    f32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    s8 unk11;
    u8 unk12;
    u8 unk13;
} ModelAnimEntryView;

extern u32 gFrameDelta;

void modelAnimEntryAdvance(ModelAnimEntryView *entry) {
    ModelAnimNodeHeader *node;
    u32 limit;
    f32 rate;
    f32 step;
    s32 whole;
    s32 loops;

    node = entry->unk0;
    rate = (f32)((f64)((f32)(node->times[entry->unk11 + 1] - node->times[entry->unk11]) * entry->unk4 + (f32)(u32)node->times[entry->unk11]) / 300.0);
    step = (f32)entry->unkC * rate;
    if (gFrameDelta < 4) {
        limit = gFrameDelta;
    } else {
        limit = 4;
    }
    if (entry->unk12 & 1) {
        step = (f64)step * ((f64)limit * 0.5);
    }
    switch (entry->unkF) {
    case 0:
        entry->unk4 += step;
        whole = entry->unk4;
        entry->unk11 += whole;
        entry->unk4 -= (f32)whole;
        if (entry->unk11 < node->keyCount - 1) {
            return;
        }
        entry->unk8 += entry->unk11 / (node->keyCount - 1);
        if (entry->unk8 >= entry->unkA && entry->unkA != -1) {
            entry->unk4 = 1.0f;
            entry->unk11 = node->keyCount - 2;
            entry->unkE = 0;
            if (entry->unk10 == 1) {
                entry->unkF = 1;
            }
        } else {
            switch (entry->unk10) {
            case 0:
                entry->unk11 = entry->unk11 % (node->keyCount - 1);
                break;
            case 1:
                loops = entry->unk11 / (node->keyCount - 1);
                if (loops != 0) {
                    entry->unkF = 1;
                    entry->unk11 = node->keyCount - 2;
                    entry->unk4 = 1.0f;
                }
                break;
            }
        }
        break;
    case 1:
        entry->unk4 -= step;
        if (entry->unk4 < 0.0) {
            whole = (s32)entry->unk4 - 1;
            entry->unk11 += whole;
            entry->unk4 -= (f32)whole;
        }
        if (entry->unk11 < 0) {
            entry->unk8 += (-entry->unk11) / node->keyCount + 1;
            if (entry->unk8 >= entry->unkA && entry->unkA != -1) {
                if (entry->unk10 == 1) {
                    entry->unkF = 0;
                }
                entry->unk4 = 0.0f;
                entry->unk11 = 0;
                entry->unkE = 0;
            } else {
                switch (entry->unk10) {
                case 0:
                    entry->unk11 = (-entry->unk11) % (node->keyCount - 1);
                    if (entry->unk11 != 0) {
                        entry->unk11 = node->keyCount - entry->unk11 - 1;
                    }
                    break;
                case 1:
                    loops = (-entry->unk11) / node->keyCount + 1;
                    if (loops) {
                        entry->unkF = 0;
                        entry->unk11 = 0;
                        entry->unk4 = 0.0f;
                    }
                    break;
                }
            }
        }
        break;
    }
}


typedef struct MtxCopyRequest {
    s32 group;
    s32 src;
    s32 dst;
    u8 bufferIndex;
    u8 padD[3];
} MtxCopyRequest;

extern MtxCopyRequest D_807F6960[];

void mtxCopyQueueReset(void) {
    s32 i;

    for (i = 0; i < 0x28; i++) {
        D_807F6960[i].group = 0;
    }
}

void mtxCopyQueuePush(s32 group, s32 src, s32 dst) {
    s32 found;
    s32 i;

    found = 0;
    i = 0;
    while (found == 0 && i < 0x28) {
        if (D_807F6960[i].group == 0) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found != 0) {
        D_807F6960[i].group = group;
        D_807F6960[i].src = src;
        D_807F6960[i].dst = dst;
        D_807F6960[i].bufferIndex = gGfxBufferIndex ^ 1;
        return;
    }
    faultSetMessage(0xB, 0, 0, 0);
}


void mtxCopyQueueCancelDest(s32 dst) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (D_807F6960[i].group != 0 && D_807F6960[i].dst == dst) {
            D_807F6960[i].group = 0;
        }
    }
}


void mtxCopyQueueCancelGroup(s32 group) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (D_807F6960[i].group == group) {
            D_807F6960[i].group = 0;
        }
    }
}



void mtxCopyQueueFlush(s32 group) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (D_807F6960[i].group == group && D_807F6960[i].bufferIndex == gGfxBufferIndex) {
            memcpy((void *)D_807F6960[i].dst, (void *)D_807F6960[i].src, 0x40);
            D_807F6960[i].group = 0;
            D_807F6BEC = 1;
        }
    }
}

void modelAnimEntrySetUnk13(s16 modelId, s16 index, u8 base, f32 scale) {
    ModelData *group;
    ModelAnimEntry *entry;
    u32 value;
    s32 level;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        value = (u32)(8.0f * scale);
        level = value & 0xFF;
        if ((u8)value >= 0x10) {
            level = 0xF;
        }
        entry->unk13 = (level << 4) + base;
    }
}

void modelAnimEntryStart(s16 modelId, s16 index, s16 value) {
    ModelData *group;
    ModelAnimEntry *entry;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        entry->unkA = value;
        entry->unkE = 1;
        entry->unk8 = 0;
    }
}

void modelAnimEntryStop(s16 modelId, s16 index) {
    ModelData *group;
    ModelAnimEntry *entry;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        entry->unkE = 0;
        modelAnimEntryQueueMatrixCopies(group, entry);
    }
}

void modelAnimEntryClearTime(s16 modelId, s16 index) {
    ModelData *group;
    ModelAnimEntry *entry;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        entry->unk11 = 0;
        entry->unk4 = 0.0f;
    }
}

void modelAnimEntrySetUnkC(s16 modelId, s16 index, s16 value) {
    ModelData *group;
    ModelAnimEntry *entry;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        entry->unkC = value;
    }
}

s16 modelAnimEntryGetUnkC(s16 modelId, s16 index) {
    ModelData *group;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        return group->entries[index].unkC;
    }
    return 0;
}

void modelAnimEntrySetTime(s16 modelId, s16 index, s16 key, f32 time) {
    ModelData *group;
    ModelAnimEntry *entry;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        entry->unk4 = time;
        entry->unk11 = key;
    }
}

void modelAnimEntrySetUnkF(s16 modelId, s16 index, s16 value) {
    ModelData *group;
    ModelAnimEntry *entry;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        entry->unkF = value;
    }
}

void modelAnimEntrySetUnk10(s16 modelId, s16 index, s16 value) {
    ModelData *group;
    ModelAnimEntry *entry;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        entry->unk10 = value;
    }
}

void modelAnimEntryResetFrame(s16 modelId, s16 index, s16 value) {
    ModelData *group;
    ModelAnimEntry *entry;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        entry->unk8 = 0;
        entry->unkA = value;
    }
}

void modelAnimEntrySetUnk12(s16 modelId, s16 index, s16 value) {
    ModelData *group;
    ModelAnimEntry *entry;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        entry->unk12 = value;
    }
}

u8 modelAnimEntryIsActive(s16 modelId, s16 index) {
    ModelData *group;
    s32 flag;
    u8 result;

    result = 0;
    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        flag = 0;
        if (group->entries[index].unkE == 1) {
            flag = 1;
        } else {
            flag = 0;
        }
        return flag;
    } else {
        return result;
    }
}

void modelAnimEntryGetState(s16 modelId, s16 index, s16 *outKey, f32 *outTime, u8 *outState) {
    ModelData *group;
    ModelAnimEntry *entry;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        *outTime = entry->unk4;
        *outKey = entry->unk11;
        *outState = entry->unkF;
    }
}
