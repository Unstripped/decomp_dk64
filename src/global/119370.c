#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/119370.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17800.h"
#include "proto/global/2F550.h"
#include "proto/global/35000.h"
#include "proto/global/36880.h"
#include "proto/global/450.h"
#include "proto/global/55B20.h"
#include "proto/global/5E2F0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"

extern u8 gGfxBufferIndex;
extern u8 gViewportCount;
extern s16 sEffectPendingZOffset;



typedef struct EffectGridAsset {
    /* 0x00 */ s32 id;
    /* 0x04 */ u8 width;
    /* 0x05 */ u8 height;
    /* 0x06 */ u8 format;
    /* 0x07 */ u8 size;
    /* 0x08 */ u8 red;
    /* 0x09 */ u8 green;
    /* 0x0A */ u8 blue;
    /* 0x0B */ u8 alpha;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ s16 cellW;
    /* 0x10 */ s16 cellH;
    /* 0x12 */ s16 frameCount;
    /* 0x14 */ u8 data[1];
} EffectGridAsset;

typedef struct EffectGridSlot {
    s32 buffer;
    s32 frame;
} EffectGridSlot;

typedef struct EffectGridNode {
    /* 0x00 */ EffectGridAsset *asset;
    /* 0x04 */ s32 id;
    /* 0x08 */ u8 width;
    /* 0x09 */ u8 height;
    /* 0x0A */ u8 format;
    /* 0x0B */ u8 size;
    /* 0x0C */ s16 cellW;
    /* 0x0E */ s16 cellH;
    /* 0x10 */ u8 red;
    /* 0x11 */ u8 green;
    /* 0x12 */ u8 blue;
    /* 0x13 */ u8 alpha;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ s16 frameCount;
    /* 0x18 */ s32 lastUsedFrame;
    /* 0x1C */ EffectGridSlot *slots;
    /* 0x20 */ u8 *data;
    /* 0x24 */ struct EffectGridNode *next;
} EffectGridNode;

struct EffectNode;
typedef void (*EffectCallback)(struct EffectNode *effect, u8 *chunkFound);

typedef struct EffectNode {
    /* 0x000 */ Gfx *displayLists[4][2];
    /* 0x020 */ u8 viewportCount;
    /* 0x021 */ u8 displayListIndex;
    /* 0x022 */ u8 pad22[6];
    /* 0x028 */ Vtx vertices[16];
    /* 0x128 */ Mtx matrices[4][2];
    /* 0x328 */ EffectCallback callback;
    /* 0x32C */ u8 state;
    /* 0x32D */ u8 freePending;
    /* 0x32E */ u8 pad32E[2];
    /* 0x330 */ EffectGridNode *grid;
    /* 0x334 */ u8 anchorType;
    /* 0x335 */ u8 pad335[3];
    /* 0x338 */ Actor *owner;
    /* 0x33C */ s16 boneIndex;
    /* 0x33E */ u8 subIndex;
    /* 0x33F */ u8 pad33F;
    /* 0x340 */ f32 x;
    /* 0x344 */ f32 y;
    /* 0x348 */ f32 z;
    /* 0x34C */ s16 maxDistance;
    /* 0x34E */ s16 param;
    /* 0x350 */ u8 frameDelay;
    /* 0x351 */ u8 frameTimer;
    /* 0x352 */ u8 pad352[2];
    /* 0x354 */ s32 duration;
    /* 0x358 */ s32 durationTimer;
    /* 0x35C */ s32 speed;
    /* 0x360 */ f32 scaleX;
    /* 0x364 */ f32 scaleY;
    /* 0x368 */ s16 startDelay;
    /* 0x36A */ u8 red;
    /* 0x36B */ u8 green;
    /* 0x36C */ u8 blue;
    /* 0x36D */ u8 alpha;
    /* 0x36E */ u8 depth;
    /* 0x36F */ u8 mode;
    /* 0x370 */ s32 frames[4];
    /* 0x380 */ s32 frameCount;
    /* 0x384 */ void *allocation;
    /* 0x388 */ s16 chunkFilter;
    /* 0x38A */ s8 chunk;
    /* 0x38B */ u8 pad38B;
    /* 0x38C */ u16 flags;
    /* 0x38E */ s16 minX;
    /* 0x390 */ s16 minY;
    /* 0x392 */ s16 maxX;
    /* 0x394 */ s16 maxY;
    /* 0x396 */ u8 pad396[2];
    /* 0x398 */ struct EffectNode *previous;
    /* 0x39C */ struct EffectNode *next;
} EffectNode;


extern EffectGridNode *sEffectGridHead;
extern EffectNode *sEffectListHead;
extern EffectNode *sEffectListTail;
extern u8 sEffectPendingColorR;
extern u8 sEffectPendingColorG;
extern u8 sEffectPendingColorB;
extern u8 sEffectPendingColorA;
extern s32 sEffectPendingDuration;
extern EffectCallback sEffectPendingCallback;
extern u8 sEffectPendingDepth;
extern s16 sEffectPendingAngle;
extern u8 sEffectPendingMode;
extern u8 sEffectPendingFade;
extern f32 sEffectPendingScaleX;
extern f32 sEffectPendingScaleY;
extern u8 sEffectPendingHasScale;
extern s32 sEffectPendingSpeed;
extern s32 sEffectPendingParam;
extern u16 sEffectPendingFlags;
extern s16 sEffectPendingLifetime;
extern s16 sEffectPendingMaxDist;
extern s16 sEffectPendingBoundsMinX;
extern s16 sEffectPendingBoundsMinY;
extern s16 sEffectPendingBoundsMaxX;
extern s16 sEffectPendingBoundsMaxY;


void effectResetLists(void) {
    sEffectGridHead = NULL;
    sEffectListHead = NULL;
    sEffectListTail = NULL;
    effectResetState();
}

s32 effectGridFindByTargetId(s32 targetId) {
    EffectGridNode *node = sEffectGridHead;

    if (node != NULL) {
        do {
            if (targetId == node->id) {
                return (s32) node->asset;
            }
            node = node->next;
        } while (node != NULL);
    }
    return (s32) sEffectGridHead->asset;
}

void effectGridGetByteDimensions(EffectGridAsset *asset, u8 *outW, u8 *outH) {
    *outW = asset->width;
    *outH = asset->height;
}

void effectGridGetCellDimensions(EffectGridAsset *asset, s16 *outCellW, s16 *outCellH) {
    *outCellW = asset->cellW;
    *outCellH = asset->cellH;
}

void effectGridGetScaledDimensions(EffectGridAsset *asset, s16 *outScaledW, s16 *outScaledH) {
    s16 pad0;
    s16 pad1;
    u8 byteW;
    u8 byteH;
    effectGridGetByteDimensions(asset, &byteW, &byteH);
    effectGridGetCellDimensions(asset, outScaledW, outScaledH);
    *outScaledW *= byteW;
    *outScaledH *= byteH;
}

void effectGridRegister(EffectGridAsset *asset) {
    EffectGridNode *last;
    EffectGridNode *newNode;
    s32 pad;
    s32 count;
    s32 i;

    newNode = sEffectGridHead;
    last = NULL;
    while (newNode != NULL) {
        last = newNode;
        if (asset == newNode->asset) {
            return;
        }
        newNode = newNode->next;
    }

    newNode = heapAlloc(sizeof(EffectGridNode));
    newNode->next = NULL;
    newNode->asset = asset;
    newNode->id = asset->id;
    effectGridGetByteDimensions(asset, &newNode->width, &newNode->height);
    newNode->format = asset->format;
    newNode->size = asset->size;
    newNode->red = asset->red;
    newNode->green = asset->green;
    newNode->blue = asset->blue;
    newNode->alpha = asset->alpha;
    newNode->unk14 = asset->unkC;
    newNode->unk15 = asset->unkD;
    effectGridGetCellDimensions(asset, &newNode->cellW, &newNode->cellH);
    newNode->frameCount = asset->frameCount;
    newNode->lastUsedFrame = -1;

    if (sEffectGridHead != NULL) {
        last->next = newNode;
    } else {
        sEffectGridHead = newNode;
    }

    count = newNode->width * newNode->height * newNode->frameCount;
    newNode->slots = heapAlloc(count * 8);
    for (i = 0; i < count; i++) {
        newNode->slots[i].frame = -1;
    }
    newNode->data = asset->data;
}

void effectSetParam(s32 param) {
    sEffectPendingParam = param;
}

void effectSetSpeed(s32 initSpeed) {
    sEffectPendingSpeed = initSpeed;
}

void effectEnableFade(void) {
    sEffectPendingFade = 1;
}

void effectSetAngle(s16 val) {
    sEffectPendingAngle = val;
}

void effectSetZOffset(s16 val) {
    sEffectPendingZOffset = val;
}

void effectSetCallback(void *callback) {
    sEffectPendingCallback = (EffectCallback)callback;
}

void effectSetMode(u8 mode) {
    sEffectPendingMode = mode;
}

void effectSetMaxDistance(s16 val) {
    sEffectPendingMaxDist = val;
}

void effectSetDepth(u8 val) {
    sEffectPendingDepth = val;
}

void effectSetColor(u8 r, u8 g, u8 b, u8 a) {
    sEffectPendingColorR = r;
    sEffectPendingColorG = g;
    sEffectPendingColorB = b;
    sEffectPendingColorA = a;
}

void effectSetDuration(s32 duration) {
    sEffectPendingDuration = duration;
}

void effectSetScale(f32 scaleX, f32 scaleY) {
    sEffectPendingScaleX = scaleX;
    sEffectPendingScaleY = scaleY;
    sEffectPendingHasScale = 1;
}

void effectSetFlags(s16 flags) {
    sEffectPendingFlags = flags;
}

void effectFlagsOr(u8 flagBits) {
    sEffectPendingFlags |= flagBits;
}

void effectSetLifetime(s16 val) {
    sEffectPendingLifetime = val;
}

void effectSetBounds(s16 minX, s16 minY, s16 maxX, s16 maxY) {
    sEffectPendingBoundsMinX = minX;
    sEffectPendingBoundsMinY = minY;
    sEffectPendingBoundsMaxX = maxX;
    sEffectPendingBoundsMaxY = maxY;
}

extern u8 gHiResScale;

void effectResetState(void) {
    s32 minBound;

    sEffectPendingColorA = 0;
    sEffectPendingDuration = 1;
    sEffectPendingCallback = NULL;
    sEffectPendingDepth = 0;
    sEffectPendingMode = 1;
    sEffectPendingAngle = 0;
    sEffectPendingFade = 0;
    sEffectPendingHasScale = 0;
    minBound = gHiResScale * 10;
    sEffectPendingSpeed = 0;
    sEffectPendingParam = 0;
    sEffectPendingFlags = 0;
    sEffectPendingLifetime = -1;
    sEffectPendingBoundsMinX = minBound;
    sEffectPendingBoundsMinY = minBound;
    sEffectPendingBoundsMaxX = gHiResScale * 0x135;
    sEffectPendingBoundsMaxY = gHiResScale * 0xE5;
    sEffectPendingMaxDist = 0x258;
}


void effectCreateAtModelNode(void *asset, f32 scale, s32 modelSlot, s32 nodeIndex, u8 flags) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    modelSlotGetNodePos(modelSlot, 1, nodeIndex, &nodeX, &nodeY, &nodeZ);
    effectCreate((s32)asset, scale, nodeX, nodeY, nodeZ, NULL, modelSlot, nodeIndex, (s32) flags);
}


// no return statement: the original falls off the end and callers read effectCreate's result in v0
void *effectCreateAtActorBone(void *asset, f32 scale, void *actor, s32 boneIndex, u8 flags) {
    f32 boneX;
    f32 boneY;
    f32 boneZ;
    u16 ownerHidden;

    actorGetNodePos(actor, boneIndex, &boneX, &boneY, &boneZ);
    ownerHidden = ((Actor *)actor)->flags & 0x200; // FAKE: u16 temp keeps the reloaded actor pointer in v1
    if (!ownerHidden && ((Actor *)actor)->sub4 != NULL && (sEffectPendingFlags & 0x80)) {
        effectFlagsOr(0x40);
    }
    effectCreate((s32)asset, scale, boneX, boneY, boneZ, actor, 0, boneIndex, (s32) flags);
}

void *effectCreateAtPosition(void *asset, f32 scale, f32 x, f32 y, f32 z) {
    return effectCreate((s32)asset, scale, x, y, z, NULL, 0, 0, 0);
}

extern s32 gGlobalOverlayFlags;

EffectNode *effectCreate(s32 asset, f32 scale, f32 posX, f32 posY, f32 posZ, void *owner, s32 boneIndex, s32 subIndex, u8 flags) {
    EffectNode *effect;
    EffectGridNode *node;
    s32 found;
    s32 i;

    effectGridRegister((EffectGridAsset *)asset);
    node = sEffectGridHead;
    found = 0;
    if (node != NULL) {
        do {
            if (node->asset == (EffectGridAsset *)asset) {
                found = 1;
            } else {
                node = node->next;
            }
        } while ((found == 0) && (node != NULL));
    }
    if (found == 0) {
        effectResetState();
        return NULL;
    }
    effect = heapAlloc(sizeof(EffectNode));
    if (sEffectListHead != NULL) {
        sEffectListTail->next = effect;
        effect->previous = sEffectListTail;
    } else {
        sEffectListHead = effect;
        effect->previous = NULL;
    }
    sEffectListTail = effect;
    if (sEffectPendingFade != 0) {
        posX *= 4.0f;
        posY *= 4.0f;
        posZ *= 4.0f;
        scale *= 4.0f;
        sEffectPendingScaleX *= 4.0f;
        sEffectPendingScaleY *= 4.0f;
    }
    effect->x = posX;
    effect->y = posY;
    effect->z = posZ;
    if (sEffectPendingHasScale != 0) {
        effect->scaleX = sEffectPendingScaleX;
        effect->scaleY = sEffectPendingScaleY;
    } else {
        effect->scaleX = scale;
        effect->scaleY = scale;
    }
    if (sEffectPendingColorA != 0) {
        effect->red = sEffectPendingColorR;
        effect->green = sEffectPendingColorG;
        effect->blue = sEffectPendingColorB;
        effect->alpha = sEffectPendingColorA;
    } else {
        effect->red = node->red;
        effect->green = node->green;
        effect->blue = node->blue;
        effect->alpha = node->alpha;
    }
    effect->depth = sEffectPendingDepth;
    effect->mode = sEffectPendingFade;
    effect->startDelay = sEffectPendingAngle;
    effect->frameCount = node->width * node->height;
    effect->anchorType = flags;
    effect->owner = owner;
    effect->boneIndex = boneIndex;
    effect->subIndex = subIndex;
    effect->param = sEffectPendingParam;
    effect->frameDelay = sEffectPendingMode;
    effect->frameTimer = 0;
    effect->duration = sEffectPendingDuration;
    effect->durationTimer = 0;
    effect->speed = sEffectPendingSpeed;
    if (gGlobalOverlayFlags & 0x100) {
        effect->maxDistance = 0x7D0;
    } else {
        effect->maxDistance = sEffectPendingMaxDist;
    }
    effect->grid = node;
    effect->next = NULL;
    effect->callback = sEffectPendingCallback;
    effect->allocation = NULL;
    effect->chunkFilter = sEffectPendingLifetime;
    effect->chunk = -1;
    effect->flags = sEffectPendingFlags;
    effect->minX = sEffectPendingBoundsMinX;
    effect->minY = sEffectPendingBoundsMinY;
    effect->maxX = sEffectPendingBoundsMaxX;
    effect->maxY = sEffectPendingBoundsMaxY;
    for (i = 0; i < gViewportCount; i++) {
        effect->displayLists[i][0] = heapAlloc(0x200);
        effect->displayLists[i][1] = heapAlloc(0x200);
    }
    effect->viewportCount = gViewportCount;
    effectBuildGridVertices(effect);
    effectResetState();
    return effect;
}


void effectBuildGridVertices(EffectNode *effect) {
    EffectGridNode *node;
    Vtx *vertex;
    s32 column;
    s32 row;
    s32 vertexIndex;
    s32 startX;
    s32 x;
    s32 y;

    node = effect->grid;
    vertexIndex = 0;
    if (node->width == 0) {} // FAKE: gives width the first candidate index (a1)
    if (node->height == 0) {} // FAKE: gives height the second candidate index (a2)
    node = effect->grid; // FAKE: kill splits the width/height webs so they reload in the arms
    x = -(node->width * node->cellW) / 2;
    startX = x;
    if (effect->mode == 0) {
        y = -(node->height * node->cellH) / 2;
    } else {
        y = (node->height * node->cellH) / 2;
    }
    for (row = 0; row < node->height; row++) {
        x = startX;
        column = 0;
        if (node->width > 0) {
            vertex = effect->vertices + vertexIndex;
            do {
                vertex[0].v.ob[0] = x;
                vertex[0].v.ob[1] = y;
                vertex[0].v.ob[2] = 0;
                vertex[0].v.tc[0] = 0;
                vertex[0].v.tc[1] = 0;
                vertex[1].v.ob[0] = node->cellW + x;
                vertex[1].v.ob[1] = y;
                vertex[1].v.ob[2] = 0;
                vertex[1].v.tc[0] = node->cellW << 5;
                vertex[1].v.tc[1] = 0;
                vertex[2].v.ob[0] = x;
                vertexIndex += 2;
                vertex += 2;
                if (effect->mode == 0) {
                    vertex[0].v.ob[1] = node->cellH + y;
                } else {
                    vertex[0].v.ob[1] = y - node->cellH;
                }
                vertex[0].v.ob[2] = 0;
                vertex[0].v.tc[0] = 0;
                vertexIndex += 1;
                vertex += 1;
                vertex[-1].v.tc[1] = node->cellH << 5;
                vertex[0].v.ob[0] = node->cellW + x;
                if (effect->mode == 0) {
                    vertex[0].v.ob[1] = node->cellH + y;
                } else {
                    vertex[0].v.ob[1] = y - node->cellH;
                }
                vertex[0].v.ob[2] = 0;
                vertex[0].v.tc[0] = node->cellW << 5;
                vertexIndex += 1;
                vertex += 1;
                vertex[-1].v.tc[1] = node->cellH << 5;
                x += node->cellW;
                column++;
            } while (column < node->width);
        }
        if (effect->mode == 0) {
            y += node->cellH;
        } else {
            y -= node->cellH;
        }
    }
}

extern u32 gFrameCounter;
extern PlayerStruct *gPlayerSlots;

void effectUpdateAll(u8 pGlist) {
    EffectNode *effect;
    u8 chunkFound;
    EffectGridNode *node2;
    s32 i;
    s32 offset2;

    effect = sEffectListHead;
    for (; effect != NULL; effect = effect->next) {
        if (effect->startDelay == 0) {
            effect->state = 0;
            effect->freePending = 0;
            effect->displayListIndex = 0;
            effect->grid->lastUsedFrame = gFrameCounter;
            effect->flags &= 0xFFEF;
            switch (effect->anchorType) {
            case 1:
                modelSlotGetNodePos(effect->boneIndex, 1, effect->subIndex,
                                    &effect->x, &effect->y,
                                    &effect->z);
                break;
            case 2: {
                if ((effect->owner->flags & 0x200) != 0 || effect->owner->sub4 == NULL) {
                    actorGetNodePos(effect->owner, effect->subIndex, &effect->x,
                                    &effect->y, &effect->z);
                } else {
                    effect->flags |= 0x10;
                }
                break;
            }
            }
            chunkFound = 0;
            if (!pGlist || (effect->flags & 1)) {
                if (effect->callback != NULL) {
                    effect->callback(effect, &chunkFound);
                }
            } else if (effect->callback != NULL) {
                if (gViewportCount > 0) {
                    i = 0;
                    do {
                        if (gPlayerSlots[i].unk0 != 0) {
                            memcpy(&effect->matrices[i][gGfxBufferIndex], &effect->matrices[i][gGfxBufferIndex ^ 1], sizeof(Mtx));
                        }
                        i++;
                    } while (i < gViewportCount);
                }
                effect->state = 3;
            }
            if (effect->param == effect->grid->frameCount) {
                effect->param = 0;
                effect->durationTimer = effect->durationTimer + 1;
                if (effect->durationTimer == effect->duration &&
                    effect->duration != -1) {
                    effect->freePending = 1;
                }
            }
            if (chunkFound != 0) {
                effect->freePending = 1;
            }
            if (effect->freePending != 0) {
                effectFreeAndUnlink(effect);
            } else {
                if (gViewportCount >= 2) {
                    i = 1;
                    do {
                        if (gPlayerSlots[i].unk0 != 0) {
                            memcpy(&effect->matrices[i][gGfxBufferIndex], &effect->matrices[0][gGfxBufferIndex], sizeof(Mtx));
                        }
                        i++;
                    } while (i < gViewportCount);
                }
                if (effect->state != 3) {
                    if (gViewportCount > 0) {
                        i = 0;
                        do {
                            if (gPlayerSlots[i].unk0 != 0) {
                                effectComputeTransformMatrix(&effect->matrices[i][gGfxBufferIndex],
                                              effect->state,
                                              effect->scaleX,
                                              effect->scaleY,
                                              gPlayerSlots[i].unk21C,
                                              gPlayerSlots[i].unk220,
                                              gPlayerSlots[i].unk224,
                                              effect->x,
                                              effect->y,
                                              effect->z, effect->mode);
                            }
                            i++;
                        } while (i < gViewportCount);
                    }
                    effect->state = 3;
                }
                if (effect->mode == 0) {
                    s32 renderArg;
                    if (effect->flags & 4) {
                        renderArg = 4;
                        if (!(effect->flags & 8)) {
                            effect->chunk = mapChunkFindByPosition(
                                effect->x, effect->y,
                                effect->z, 0);
                        }
                    } else {
                        renderArg = 1;
                    }
                    renderEntryAddOrUpdate(0, 5, effect, effect->x,
                                           effect->y,
                                           effect->z,
                                           effect->maxDistance, 0, 1, -1, renderArg);
                } else {
                    renderEntryAddOrUpdate(0, 5, effect, effect->x,
                                           effect->y,
                                           effect->z, 0, 0, 1, -1, 3);
                }
                effectLoadFrameAssets((s16 *)effect->grid->data,
                              effect->grid->unk15,
                              effect->grid->slots,
                              effect->frameCount, effect->param,
                              effect->frames);
                if (!pGlist || (effect->flags & 1)) {
                    effect->frameTimer = effect->frameTimer + 1;
                    if (effect->frameTimer == effect->frameDelay) {
                        effect->param = effect->param + 1;
                        effect->frameTimer = 0;
                    }
                }
            }
            effect->flags |= 8;
        } else {
            if (!pGlist || (effect->flags & 1)) {
                effect->startDelay = effect->startDelay - 1;
            }
        }
    }
    for (node2 = sEffectGridHead; node2 != NULL; node2 = node2->next) {
        if (gFrameCounter - node2->lastUsedFrame >= 0xB) {
            continue;
        }
        if (node2->lastUsedFrame == -1) {
            continue;
        }
        if (node2->frameCount * node2->width * node2->height > 0) {
            i = 0;
            offset2 = 0;
            do {
                if (node2 && node2) {} // FAKE: raises node2 priority above offset2 (node2 -> s1, offset2 -> s2)
                if (((s32 *)((u8 *)node2->slots + offset2))[1] != -1) {
                    if (gFrameCounter - node2->lastUsedFrame == 0xA) {
                        assetFreeBuffer(((s32 *)((u8 *)node2->slots + offset2))[0], 0x319, 0x1F);
                        ((s32 *)((u8 *)node2->slots + offset2))[1] = -1;
                    }
                }
                i++;
                offset2 += 8;
            } while (i < node2->frameCount * node2->width * node2->height);
        }
    }
}


void effectFreeByResource(Actor *owner) {
    EffectNode *effect;

    effect = sEffectListHead;
    if (effect != NULL) {
        do {
            if (owner == effect->owner) {
                effectFreeAndUnlink(effect);
            }
            effect = effect->next;
        } while (effect != NULL);
    }
}

void effectFreeAll(void) {
    EffectNode *effect;
    EffectNode *next;

    effect = sEffectListHead;
    if (effect != NULL) {
        do {
            next = effect->next;
            effectFreeAndUnlink(effect);
            effect = next;
        } while (next != NULL);
    }
}


void effectFreeAndUnlink(EffectNode *effect) {
    void *allocation;
    s32 i;
    u8 found;
    EffectNode *previous;
    EffectNode *next;

    if (effect->mode == 0) {
        if (effect->flags & 4) {
            renderEntryRemove(NULL, effect, 4, &found);
        } else {
            func_8062D26C(effect);
        }
    } else {
        renderEntryRemove(NULL, effect, 3, &found);
    }
    allocation = effect->allocation;
    if (allocation != NULL) {
        heapFreeDeferred(allocation);
    }
    for (i = 0; i < effect->viewportCount; i++) {
        heapFreeDeferred(effect->displayLists[i][0]);
        heapFreeDeferred(effect->displayLists[i][1]);
    }
    if (osCicId != 0x17D9) {
        osSetTime((s32)randomLcgNext());
    }
    previous = effect->previous;
    next = effect->next;
    heapFreeDeferred(effect);
    if (previous != NULL) {
        previous->next = next;
    } else {
        sEffectListHead = next;
    }
    if (next != NULL) {
        next->previous = previous;
    } else {
        sEffectListTail = previous;
    }
}

void effectLoadFrameAssets(s16 *assetIds, u8 altCategory, EffectGridSlot *slots, s32 count, s32 frame, s32 *outFrames) {
    u8 category;
    s32 i;
    s32 index;
    s32 buffer;
    s32 *out;
    EffectGridSlot *slot;

    i = 0;
    if (count > 0) {
        out = outFrames;
        index = count * frame;
        slot = slots;
        slot += index;
        do {
            if (slot->frame == -1) {
                if (altCategory) {
                    category = 0x19;
                } else {
                    category = 7;
                }
                buffer = assetLoad(category, assetIds[index + i], 0, 0);
                *out = buffer;
                slot->buffer = buffer;
            } else {
                *out = slot->buffer;
            }
            i += 1;
            out += 1;
            slot += 1;
            slot[-1].frame = frame;
        } while (i != count);
    }
}

s32 mathAsinFixed(s32);

void effectComputeTransformMatrix(Mtx *dst, u8 state, f32 scaleX, f32 scaleY, f32 camX, f32 camY, f32 camZ, f32 x, f32 y, f32 z, u8 mode) {
    f32 pad[2];
    f32 distance;
    f32 value;
    f32 absValue;
    s32 angle;
    s32 asinAngle;
    f32 scale[4][4];
    f32 transform[4][4];
    Mtx mtx;

    if (mode == 0) {
        distance = distance3D(camX, camY, camZ, x, y, z);
        value = distance;
        if ((f64)distance < 0.1) {
            value = 1.0f;
        }
        distance = (camY - y) / value;
        if (distance > 0.0f) {
            absValue = distance;
        } else {
            absValue = -distance;
        }
        asinAngle = mathAsinFixed((s32)((f64)absValue * 65536.0)) >> 4;
        angle = asinAngle;
        if (distance >= 0.0f) {
            angle = 0xFFF - asinAngle;
        }
        if (state != 2) {
            guScaleF(scale, scaleX, scaleY, 0.0f);
        } else {
            guScaleF(scale, 1.0f, 1.0f, 1.0f);
        }
        guRotateF(transform, (f32)(((f64)angle / 4095.0) * 360.0), 1.0f, 0.0f, 0.0f);
        guMtxCatF(scale, transform, scale);
        value = mathAngleBetweenPointsRad(camX, camZ, x, z);
        guRotateF(transform, value * 57.295776f, 0.0f, 1.0f, 0.0f);
        guMtxCatF(scale, transform, scale);
        guTranslateF(transform, x, y, z);
        guMtxCatF(scale, transform, scale);
    } else {
        if (state != 2) {
            guScaleF(scale, scaleX, scaleY, 0.0f);
        } else {
            guScaleF(scale, 1.0f, 1.0f, 1.0f);
        }
        matrixMakeRotationZ(transform, (f32)sEffectPendingZOffset);
        guMtxCatF(scale, transform, scale);
        guTranslateF(transform, x, y, z);
        guMtxCatF(scale, transform, scale);
    }
    if ((state == 1) || (state == 2)) {
        guMtxF2L(scale, &mtx);
        guMtxCatL(dst, &mtx, dst);
    } else {
        guMtxF2L(scale, dst);
    }
}

f32 distance3D(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2) {
    f32 x;
    f32 y;
    f32 z;

    x = x1 - x2;
    y = y1 - y2;
    z = z1 - z2;
    return sqrtf((x * x) + (y * y) + (z * z));
}

#define EFFECT_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

extern Actor *gPrimaryPlayerActor;
extern s32 gGlobalPauseFlags;
extern u8 D_807F6009;
extern s32 D_807F600C;
extern u8 gCurrentPlayerIndex;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern Mtx D_2000000;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern Mtx D_2000200;

Gfx *effectGridBuildDisplayList(EffectNode *effect, Gfx *inGlist, s16 chunk) {
    s32 i;
    u8 red;
    u8 green;
    u8 blue;
    f32 colorRed = 1.0f;
    f32 colorGreen = 1.0f;
    f32 colorBlue = 1.0f;
    Gfx *glist;

    if (effect->flags & 0x50) {
        return inGlist;
    }
    if ((((gPrimaryPlayerActor->state == 0x83) || (gPrimaryPlayerActor->state == 0x67)) && !(effect->flags & 0x20)) || (((gGlobalPauseFlags & 0x100002) == 0x100002) && !(effect->flags & 0x100))) {
        return inGlist;
    }
    if (chunk == -1) {
        chunk = effect->chunk;
    }
    if (effect->chunkFilter != -1) {
        if (effect->mode != 0) {
            if (mapChunkContainsPoint((s16)((f64)effect->x * 0.25), (s16)((f64)effect->y * 0.25), effect->chunkFilter) == 0) {
                return inGlist;
            }
        } else if (chunk != effect->chunkFilter) {
            return inGlist;
        }
    }
    glist = effect->displayLists[effect->displayListIndex][gGfxBufferIndex];
    effect->displayListIndex++;
    EFFECT_WRITE_GFX(inGlist++, 0xDE000000, osVirtualToPhysical(glist));
    gDPPipeSync(glist++);
    EFFECT_WRITE_GFX(glist++, 0xE3000A01, 0);
    EFFECT_WRITE_GFX(glist++, 0xD9000000, 0);
    EFFECT_WRITE_GFX(glist++, 0xE3001801, 0xC0);
    if (effect->depth != 0) {
        EFFECT_WRITE_GFX(glist++, 0xD9FFFFFF, 0x200005);
        EFFECT_WRITE_GFX(glist++, 0xE200001C, 0x504B50);
    } else {
        EFFECT_WRITE_GFX(glist++, 0xD9FFFFFF, 0x200004);
        EFFECT_WRITE_GFX(glist++, 0xE200001C, 0x504240);
    }
    EFFECT_WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    EFFECT_WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);

    if (effect->grid->unk14 == 0 && mapChunkIsInUse(chunk)) {
        lightSampleColorAtPosition(effect->x, effect->y, effect->z, 0, &red, &green, &blue, chunk);
        colorRed = (f32)((f64)red / 255.0);
        colorGreen = (f32)((f64)green / 255.0);
        colorBlue = (f32)((f64)blue / 255.0);
    }
    gDPSetPrimColor(glist++, 0, 0, (u32)((f32)effect->red * colorRed), (u32)((f32)effect->green * colorGreen), (u32)((f32)effect->blue * colorBlue), effect->alpha);
    if (effect->mode != 0) {
        EFFECT_WRITE_GFX(glist++, 0xDA380007, &D_20000C0);
        EFFECT_WRITE_GFX(glist++, 0xDA380003, &D_2000180);
        glist = gfxInit2DDisplayList(glist);
        if (effect->chunkFilter == -1) {
            EFFECT_WRITE_GFX(glist++, 0xED000000 | (((s32)((f32)effect->minX * 4.0f) & 0xFFF) << 12) | ((s32)((f32)effect->minY * 4.0f) & 0xFFF), (((s32)((f32)effect->maxX * 4.0f) & 0xFFF) << 12) | ((s32)((f32)effect->maxY * 4.0f) & 0xFFF));
        }
    }
    EFFECT_WRITE_GFX(glist++, 0xDA380000, osVirtualToPhysical(&effect->matrices[gCurrentPlayerIndex][gGfxBufferIndex]));

    for (i = 0; i < effect->frameCount; i++) {
        if (D_807F6009 != 5 || D_807F600C != effect->frames[i]) {
            gDPPipeSync(glist++);
            switch (effect->grid->size) {
                case 0:
                    gDPLoadTextureBlock_4b(glist++, effect->frames[i], effect->grid->format, effect->grid->cellW, effect->grid->cellH, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 1:
                    gDPLoadTextureBlock(glist++, effect->frames[i], effect->grid->format, G_IM_SIZ_8b, effect->grid->cellW, effect->grid->cellH, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 2:
                    gDPLoadTextureBlock(glist++, effect->frames[i], effect->grid->format, G_IM_SIZ_16b, effect->grid->cellW, effect->grid->cellH, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 3:
                    gDPLoadTextureBlock(glist++, effect->frames[i], effect->grid->format, G_IM_SIZ_32b, effect->grid->cellW, effect->grid->cellH, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
            }
            D_807F600C = effect->frames[i];
        }
        EFFECT_WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical(effect->vertices + (i << 2)));
        EFFECT_WRITE_GFX(glist++, 0x06000206, 0x406);
    }
    EFFECT_WRITE_GFX(glist++, 0xD8380002, 0x40);
    gDPPipeSync(glist++);
    EFFECT_WRITE_GFX(glist++, 0xE3001801, 0);
    if (effect->mode != 0) {
        EFFECT_WRITE_GFX(glist++, 0xDA380007, &D_2000000);
        EFFECT_WRITE_GFX(glist++, 0xDA380005, &D_2000200);
        if (effect->chunkFilter == -1) {
            EFFECT_WRITE_GFX(glist++, 0xED000000, ((((s32)((f32)gScreenWidth * 4.0f) & 0xFFF) << 12) | ((s32)((f32)gScreenHeight * 4.0f) & 0xFFF)));
        }
    }
    gDPPipeSync(glist++);
    gSPEndDisplayList(glist++);
    D_807F6009 = 5;
    return inGlist;
}
