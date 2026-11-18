#include "common.h"
#include "model.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "proto/global/136820.h"
#include "proto/global/15050.h"
#include "proto/global/17800.h"
#include "proto/global/36880.h"
#include "proto/global/54150.h"
#include "proto/global/5E020.h"

void modelSlotAllocAnimBuffers(ModelData **outAnim, ModelAssetHeader *asset) {
    Mtx *mtx1;
    u32 frameSize;
    Mtx *mtx0;
    u8 *data;
    u32 dataSize;
    ModelData *anim;
    u32 mtxCount;
    u8 *nodeTable;
    s32 j;
    ModelAnimEntry *entry;

    if (asset->unk64 != asset->unk68) {
        anim = heapAlloc(sizeof(ModelData));
        *outAnim = anim;
        frameSize = *(u32 *)(asset->unk68 + (u8 *)asset);
        anim->frames[0] = heapAlloc(frameSize);
        anim->frames[1] = heapAlloc(frameSize);
        data = asset->unk68 + (u8 *)asset;
        dataSize = *(u32 *)(data + 4);
        memcpy(anim->frames[0], data + 8, dataSize);
        memcpy(anim->frames[1], data + 8, dataSize);
        mtxCount = (frameSize - dataSize) / sizeof(Mtx);
        mtx0 = (Mtx *)(anim->frames[0] + dataSize);
        mtx1 = (Mtx *)(anim->frames[1] + dataSize);
        for (; mtxCount != 0; mtxCount--) {
            guMtxIdent(mtx0);
            guMtxIdent(mtx1);
            mtx0++;
            mtx1++;
        }
        nodeTable = asset->unk64 + (u8 *)asset;
        for (j = 0; j < 10; j++) {
            entry = &anim->entries[j];
            entry->unk0 = (ModelAnimNodeHeader *)(nodeTable + ((u32 *)nodeTable)[j]);
            entry->unk4 = 0.0f;
            entry->unk8 = 0;
            entry->unkA = 0;
            entry->unkE = 0;
            entry->unkF = 0;
            entry->unk10 = 0;
            entry->keyIndex = 0;
            entry->unkC = 1;
            entry->unk12 = 0;
            entry->unk13 = 0;
        }
    } else {
        *outAnim = NULL;
    }
}

extern ModelSlot *gModelSlots;

u32 modelSlotDataSize(s16 slot) {
    ModelAssetHeader *asset = gModelSlots[slot].unk24;

    return *(u32 *)(asset->unk68 + (u8 *)asset);
}

void modelSlotCopyData(u8 *src, s16 slot) {
    ModelAssetHeader *asset;
    ModelData *anim;
    u32 size;
    f32 x;
    f32 y;
    f32 z;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    f32 scale;
    f32 yOffset;

    asset = gModelSlots[slot].unk24;
    anim = gModelSlots[slot].unk78;
    size = *(u32 *)(asset->unk68 + (u8 *)asset);
    memcpy(anim->frames[0], src, size);
    memcpy(anim->frames[1], src, size);
    modelSlotGetTransformVectors(slot, &x, &y, &z, &rotX, &rotY, &rotZ, &scale, &yOffset, 0);
    modelSlotTransformBoundsAndNodes(slot, x, y, z, rotX, rotY, rotZ, scale, yOffset, 0, 0, 0, 0, 1);
}


void modelSlotFree(ModelData *anim) {
    if (anim != NULL) {
        heapFreeDeferred(anim->frames[0]);
        heapFreeDeferred(anim->frames[1]);
        mtxCopyQueueCancelGroup(anim);
        heapFree(anim);
    }
}

extern u8 *gModelAnimSrcFrame;
extern u8 *gModelAnimDstFrame;
extern ModelData *gModelAnimStepGroup;
extern u8 gModelAnimChanged;
extern u8 gGfxBufferIndex;

u8 modelSlotStepAnimations(s16 modelId) {
    ModelData *group;
    s32 i;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    gModelAnimChanged = 0;
    if (group != NULL) {
        gModelAnimSrcFrame = group->frames[gGfxBufferIndex];
        gModelAnimDstFrame = group->frames[gGfxBufferIndex ^ 1];
        gModelAnimStepGroup = group;
        for (i = 0; i < 10; i++) {
            if (group->entries[i].unkE == 1) {
                modelAnimEntryStep(&group->entries[i]);
                gModelAnimChanged = 1;
            }
        }
        mtxCopyQueueFlush(group);
    }
    return gModelAnimChanged;
}


void modelAnimEntryStep(ModelAnimEntry *entry) {
    modelAnimEntryAdvance(entry);
    modelAnimEntryBuildNodeMatrices(entry);
}

// Head of one matrix record of an animation node; node->keyCount ModelBKeys follow it.
// Both offsets are relative to the animation frame buffers (ModelData.frames).
typedef struct ModelBTrack {
    /* 0x00 */ u32 mtxOffset; // the node's output Mtx
    /* 0x04 */ u32 mtxPairOffset; // two f32 4x4 matrices composed before and after the key transform
} ModelBTrack;

// One key of a matrix record: scale, rotation (degrees), translation.
typedef struct ModelBKey {
    /* 0x00 */ f32 scaleX;
    /* 0x04 */ f32 scaleY;
    /* 0x08 */ f32 scaleZ;
    /* 0x0C */ f32 rotX;
    /* 0x10 */ f32 rotY;
    /* 0x14 */ f32 rotZ;
    /* 0x18 */ f32 posX;
    /* 0x1C */ f32 posY;
    /* 0x20 */ f32 posZ;
} ModelBKey; // size = 0x24


void modelAnimEntryBuildNodeMatrices(ModelAnimEntry *entry) {
    ModelAnimNodeHeader *node;
    s16 stride;
    s32 i;
    u8 *p;
    u8 *srcBase;
    u8 *dstBase;
    u8 *dst;
    u8 *src;
    ModelBTrack *track;

    node = entry->unk0;
    stride = node->keyCount * sizeof(ModelBKey) + sizeof(ModelBTrack);
    srcBase = gModelAnimSrcFrame;
    dstBase = gModelAnimDstFrame;
    p = (u8 *)(node + 1);
    for (i = 0; i < node->matrixCount; i++) {
        track = (ModelBTrack *)p;
        modelAnimEntryBuildKeyMatrix(entry->keyIndex, entry->unk4, track, (ModelBKey *)(track + 1), entry->unk13);
        dst = dstBase + track->mtxOffset;
        if (entry->unkE == 0) {
            src = srcBase + track->mtxOffset;
            mtxCopyQueuePush(gModelAnimStepGroup, src, dst);
        } else {
            mtxCopyQueueCancelDest(dst);
        }
        p += stride;
    }
}

void modelAnimEntryQueueMatrixCopies(ModelData *group, ModelAnimEntry *entry) {
    ModelAnimNodeHeader *node;
    s16 stride;
    s32 i;
    u8 *p;
    u8 *srcBase;
    u8 *dstBase;
    u8 *dst;
    ModelBTrack *track;

    node = entry->unk0;
    p = (u8 *)(entry->unk0 + 1);
    stride = node->keyCount * sizeof(ModelBKey) + sizeof(ModelBTrack);
    srcBase = gModelAnimSrcFrame = group->frames[gGfxBufferIndex ^ 1];
    dstBase = gModelAnimDstFrame = group->frames[gGfxBufferIndex];
    for (i = 0; i < node->matrixCount; i++) {
        track = (ModelBTrack *)p;
        dst = dstBase + track->mtxOffset;
        mtxCopyQueuePush(group, srcBase + track->mtxOffset, dst);
        p += stride;
    }
}


void modelAnimEntryBuildKeyMatrix(u8 key, f32 t, ModelBTrack *track, ModelBKey *keys, u8 scaleMode)
{
    u8 *frame;
    f32 rx;
    f32 ry;
    f32 rz;
    f32 tx;
    f32 ty;
    f32 tz;
    f32 sx;
    f32 sy;
    f32 sz;
    f32 factor;
    f32 next;
    f32 prev;
    f32 next2;
    f32 prev2;
    s32 pad[2];
    f32 work[4][4];
    f32 mtx[4][4];

    frame = gModelAnimSrcFrame;
    next = keys[key + 1].rotX;
    prev = keys[key].rotX;
    rx = next - prev;
    if (rx < -180.0) {
        rx += 360.0;
    } else if (rx > 180.0) {
        rx -= 360.0;
    }
    rx *= t;
    rx += prev;
    next = keys[key + 1].rotY;
    prev = keys[key].rotY;
    ry = next - prev;
    if (ry < -180.0) {
        ry += 360.0;
    } else if (ry > 180.0) {
        ry -= 360.0;
    }
    ry *= t;
    ry += prev;
    next = keys[key + 1].rotZ;
    prev = keys[key].rotZ;
    rz = next - prev;
    if (rz < -180.0) {
        rz += 360.0;
    } else if (rz > 180.0) {
        rz -= 360.0;
    }
    rz *= t;
    rz += prev;
    tx = keys[key + 1].posX - keys[key].posX;
    tx *= t;
    tx += keys[key].posX;
    ty = keys[key + 1].posY - keys[key].posY;
    ty *= t;
    ty += keys[key].posY;
    tz = keys[key + 1].posZ - keys[key].posZ;
    tz *= t;
    tz += keys[key].posZ;
    next2 = keys[key + 1].scaleX;
    prev2 = keys[key].scaleX;
    sx = (next2 - prev2) * t + prev2;
    next2 = keys[key + 1].scaleY;
    prev2 = keys[key].scaleY;
    sy = (next2 - prev2) * t + prev2;
    next2 = keys[key + 1].scaleZ;
    prev2 = keys[key].scaleZ;
    sz = (next2 - prev2) * t + prev2;
    factor = (scaleMode >> 4 & 0xF) * 0.125;
    switch (scaleMode & 0xF) {
    case 0:
        break;
    case 1:
        tx *= factor;
        break;
    case 2:
        ty *= factor;
        break;
    case 3:
        tz *= factor;
        break;
    case 4:
        rx *= factor;
        break;
    case 5:
        ry *= factor;
        break;
    case 6:
        rz *= factor;
        break;
    case 7:
        sx *= factor;
        break;
    case 8:
        sy *= factor;
        break;
    case 9:
        sz *= factor;
        break;
    }
    memcpy(work, frame + track->mtxPairOffset, sizeof(work));
    guScaleF(mtx, sx, sy, sz);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationZ(mtx, rz);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationY(mtx, ry);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationX(mtx, rx);
    guMtxCatF(work, mtx, work);
    guTranslateF(mtx, tx, ty, tz);
    guMtxCatF(work, mtx, work);
    memcpy(mtx, frame + track->mtxPairOffset + sizeof(mtx), sizeof(mtx));
    guMtxCatF(work, mtx, work);
    guMtxF2L(work, (Mtx *)(frame + track->mtxOffset));
}

extern u32 gFrameDelta;

void modelAnimEntryAdvance(ModelAnimEntry *entry) {
    ModelAnimNodeHeader *node;
    u32 limit;
    f32 rate;
    f32 step;
    s32 whole;
    s32 loops;

    node = entry->unk0;
    rate = ((node->times[entry->keyIndex + 1] - node->times[entry->keyIndex]) * entry->unk4 + node->times[entry->keyIndex]) / 300.0;
    step = entry->unkC * rate;
    if (gFrameDelta < 4) {
        limit = gFrameDelta;
    } else {
        limit = 4;
    }
    if (entry->unk12 & 1) {
        step *= limit * 0.5;
    }
    switch (entry->unkF) {
    case 0:
        entry->unk4 += step;
        whole = entry->unk4;
        entry->keyIndex += whole;
        entry->unk4 -= whole;
        if (entry->keyIndex < node->keyCount - 1) {
            return;
        }
        entry->unk8 += entry->keyIndex / (node->keyCount - 1);
        if (entry->unk8 >= entry->unkA && entry->unkA != -1) {
            entry->unk4 = 1.0f;
            entry->keyIndex = node->keyCount - 2;
            entry->unkE = 0;
            if (entry->unk10 == 1) {
                entry->unkF = 1;
            }
        } else {
            switch (entry->unk10) {
            case 0:
                entry->keyIndex = entry->keyIndex % (node->keyCount - 1);
                break;
            case 1:
                loops = entry->keyIndex / (node->keyCount - 1);
                if (loops != 0) {
                    entry->unkF = 1;
                    entry->keyIndex = node->keyCount - 2;
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
            entry->keyIndex += whole;
            entry->unk4 -= whole;
        }
        if (entry->keyIndex < 0) {
            entry->unk8 += (-entry->keyIndex) / node->keyCount + 1;
            if (entry->unk8 >= entry->unkA && entry->unkA != -1) {
                if (entry->unk10 == 1) {
                    entry->unkF = 0;
                }
                entry->unk4 = 0.0f;
                entry->keyIndex = 0;
                entry->unkE = 0;
            } else {
                switch (entry->unk10) {
                case 0:
                    entry->keyIndex = (-entry->keyIndex) % (node->keyCount - 1);
                    if (entry->keyIndex != 0) {
                        entry->keyIndex = node->keyCount - entry->keyIndex - 1;
                    }
                    break;
                case 1:
                    loops = (-entry->keyIndex) / node->keyCount + 1;
                    if (loops != 0) {
                        entry->unkF = 0;
                        entry->keyIndex = 0;
                        entry->unk4 = 0.0f;
                    }
                    break;
                }
            }
        }
        break;
    }
}


// One deferred 4x4 matrix copy (mtxCopyQueueFlush runs it when its gfx buffer comes round).
typedef struct MtxCopyRequest {
    /* 0x00 */ ModelData *group;
    /* 0x04 */ void *src;
    /* 0x08 */ void *dst;
    /* 0x0C */ u8 bufferIndex;
    /* 0x0D */ u8 padD[3];
} MtxCopyRequest;

extern MtxCopyRequest gMtxCopyQueue[0x28];

void mtxCopyQueueReset(void) {
    s32 i;

    for (i = 0; i < 0x28; i++) {
        gMtxCopyQueue[i].group = NULL;
    }
}

void mtxCopyQueuePush(ModelData *group, void *src, void *dst) {
    s32 found;
    s32 i;

    found = 0;
    i = 0;
    while (found == 0 && i < 0x28) {
        if (gMtxCopyQueue[i].group == NULL) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found != 0) {
        gMtxCopyQueue[i].group = group;
        gMtxCopyQueue[i].src = src;
        gMtxCopyQueue[i].dst = dst;
        gMtxCopyQueue[i].bufferIndex = gGfxBufferIndex ^ 1;
        return;
    }
    faultSetMessage(0xB, 0, 0, 0);
}


void mtxCopyQueueCancelDest(void *dst) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (gMtxCopyQueue[i].group != NULL && gMtxCopyQueue[i].dst == dst) {
            gMtxCopyQueue[i].group = NULL;
        }
    }
}


void mtxCopyQueueCancelGroup(ModelData *group) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (gMtxCopyQueue[i].group == group) {
            gMtxCopyQueue[i].group = NULL;
        }
    }
}



void mtxCopyQueueFlush(ModelData *group) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (gMtxCopyQueue[i].group == group && gMtxCopyQueue[i].bufferIndex == gGfxBufferIndex) {
            memcpy(gMtxCopyQueue[i].dst, gMtxCopyQueue[i].src, sizeof(Mtx));
            gMtxCopyQueue[i].group = NULL;
            gModelAnimChanged = 1;
        }
    }
}

void modelAnimEntrySetUnk13(s16 modelId, s16 index, u8 channel, f32 scale) {
    ModelData *group;
    ModelAnimEntry *entry;
    u8 level;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        level = 8.0f * scale;
        if (level >= 16) {
            level = 15;
        }
        entry->unk13 = (level << 4) + channel;
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
        entry->keyIndex = 0;
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
        entry->keyIndex = key;
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
    s32 active;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        if (group->entries[index].unkE == 1) {
            active = 1;
        } else {
            active = 0;
        }
        return active;
    }
    return 0;
}

void modelAnimEntryGetState(s16 modelId, s16 index, s16 *outKey, f32 *outTime, u8 *outState) {
    ModelData *group;
    ModelAnimEntry *entry;

    group = gModelSlots[hashTableLookup(modelId)].unk78;
    if (group != NULL) {
        entry = &group->entries[index];
        *outTime = entry->unk4;
        *outKey = entry->keyIndex;
        *outState = entry->unkF;
    }
}
