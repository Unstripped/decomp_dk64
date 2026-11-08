#include "common.h"
#include "actor.h"

extern u8 gGfxBufferIndex;
extern u8 gViewportCount;
extern s16 sEffectPendingZOffset;

void *heapAlloc(s32);
u32 randomLcgNext(void);


typedef struct EffectGridNode {
    void *unk0;
    s32 unk4;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s32 unk18;
    void *unk1C;
    void *unk20;
    struct EffectGridNode *unk24;
} EffectGridNode;

typedef struct EffectNode {
    u8 pad0[0x20];
    u8 itemCount;
    u8 pad21[0x317];
    s32 resource;
    u8 pad33C[0x33];
    u8 mode;
    u8 pad370[0x14];
    void *allocation;
    u8 pad388[4];
    u16 flags;
    u8 pad38E[0xA];
    struct EffectNode *previous;
    struct EffectNode *next;
} EffectNode;


extern EffectGridNode *sEffectGridHead;
extern EffectNode *sEffectListHead;
extern EffectNode *sEffectListTail;
extern s8 sEffectPendingColorR;
extern s8 sEffectPendingColorG;
extern s8 sEffectPendingColorB;
extern s8 sEffectPendingColorA;
extern s32 sEffectPendingDuration;
extern s32 sEffectPendingCallback;
extern s8 sEffectPendingDepth;
extern s16 sEffectPendingAngle;
extern u8 sEffectPendingMode;
extern s8 sEffectPendingFade;
extern f32 sEffectPendingScaleX;
extern f32 sEffectPendingScaleY;
extern s8 sEffectPendingHasScale;
extern s32 sEffectPendingSpeed;
extern s32 sEffectPendingParam;
extern u16 sEffectPendingFlags;
extern s16 sEffectPendingLifetime;
extern s16 sEffectPendingMaxDist;
extern s16 sEffectPendingBoundsMinX;
extern s16 sEffectPendingBoundsMinY;
extern s16 sEffectPendingBoundsMaxX;
extern s16 sEffectPendingBoundsMaxY;

void effectResetState(void);

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
            if (targetId == node->unk4) {
                return (s32) node->unk0;
            }
            node = node->unk24;
        } while (node != NULL);
    }
    return (s32) sEffectGridHead->unk0;
}

void effectGridGetByteDimensions(EffectGridNode *grid, u8 *outW, u8 *outH) {
    *outW = ((u8 *) grid)[4];
    *outH = ((u8 *) grid)[5];
}

void effectGridGetCellDimensions(EffectGridNode *grid, s16 *outCellW, s16 *outCellH) {
    *outCellW = grid->unkE;
    *outCellH = grid->unk10;
}

void effectGridGetScaledDimensions(EffectGridNode *grid, s16 *outScaledW, s16 *outScaledH) {
    s16 pad0;
    s16 pad1;
    u8 byteW;
    u8 byteH;
    effectGridGetByteDimensions(grid, &byteW, &byteH);
    effectGridGetCellDimensions(grid, outScaledW, outScaledH);
    *outScaledW *= byteW;
    *outScaledH *= byteH;
}

void effectGridRegister(EffectGridNode *grid) {
    EffectGridNode *last;
    EffectGridNode *newNode;
    s32 byteOffset;
    s32 count;
    s32 i;

    newNode = sEffectGridHead;
    byteOffset = 0xB;
    last = NULL;
    while (newNode != NULL) {
        last = newNode;
        if (grid == newNode->unk0) {
            return;
        }
        newNode = newNode->unk24;
    }

    newNode = heapAlloc(0x28);
    newNode->unk24 = NULL;
    newNode->unk0 = grid;
    newNode->unk4 = (s32) grid->unk0;
    effectGridGetByteDimensions(grid, &newNode->unk8, &newNode->unk9);
    ((u8 *) newNode)[0xA] = ((u8 *) grid)[0x6];
    ((u8 *) newNode)[byteOffset] = ((u8 *) grid)[0x7];
    ((u8 *) newNode)[0x10] = ((u8 *) grid)[0x8];
    ((u8 *) newNode)[0x11] = ((u8 *) grid)[0x9];
    ((u8 *) newNode)[0x12] = ((u8 *) grid)[0xA];
    ((u8 *) newNode)[0x13] = ((u8 *) grid)[0xB];
    ((u8 *) newNode)[0x14] = ((u8 *) grid)[0xC];
    ((u8 *) newNode)[0x15] = ((u8 *) grid)[0xD];
    effectGridGetCellDimensions(grid, &newNode->unkC, &newNode->unkE);
    newNode->unk16 = grid->unk12;
    newNode->unk18 = -1;

    if (sEffectGridHead != NULL) {
        last->unk24 = newNode;
    } else {
        sEffectGridHead = newNode;
    }

    count = newNode->unk8 * newNode->unk9 * newNode->unk16;
    newNode->unk1C = heapAlloc(count * 8);
    for (i = 0; i < count; i++) {
        ((s32 *) ((u8 *) newNode->unk1C + (i * 8)))[1] = -1;
    }
    newNode->unk20 = (u8 *) grid + 0x14;
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

void effectSetCallback(s32 callback) {
    sEffectPendingCallback = callback;
}

void effectSetMode(s8 mode) {
    sEffectPendingMode = mode;
}

void effectSetMaxDistance(s16 val) {
    sEffectPendingMaxDist = val;
}

void effectSetDepth(s8 val) {
    sEffectPendingDepth = val;
}

void effectSetColor(s8 r, s8 g, s8 b, s8 a) {
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
    u16 *temp = &sEffectPendingFlags;

    *temp = *temp | flagBits;
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
    s32 temp;
    u16 new_var;

    sEffectPendingColorA = 0;
    sEffectPendingDuration = 1;
    sEffectPendingCallback = 0;
    sEffectPendingDepth = 0;
    sEffectPendingMode = 1;
    sEffectPendingAngle = 0;
    sEffectPendingFade = 0;
    sEffectPendingHasScale = 0;
    temp = gHiResScale * 0xA;
    new_var = 0;
    sEffectPendingSpeed = new_var;
    sEffectPendingParam = new_var;
    sEffectPendingFlags = 0;
    sEffectPendingLifetime = -1;
    sEffectPendingBoundsMinX = temp;
    sEffectPendingBoundsMinY = temp;
    sEffectPendingBoundsMaxX = gHiResScale * 0x135;
    sEffectPendingBoundsMaxY = gHiResScale * 0xE5;
    sEffectPendingMaxDist = 0x258;
}

void modelSlotGetNodePos();
EffectNode *effectCreate(s32 asset, f32 scale, f32 posX, f32 posY, f32 posZ, void *owner, s32 boneIndex, s32 subIndex, u8 flags);

void effectCreateAtModelNode(s32 asset, f32 scale, s32 modelSlot, s32 nodeIndex, u8 flags) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    modelSlotGetNodePos(modelSlot, 1, nodeIndex, &nodeX, &nodeY, &nodeZ);
    effectCreate(asset, scale, nodeX, nodeY, nodeZ, NULL, modelSlot, nodeIndex, (s32) flags);
}

void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);

void effectCreateAtActorBone(s32 asset, f32 scale, void *actor, s32 boneIndex, u8 flags) {
    f32 boneX;
    f32 boneY;
    f32 boneZ;
    u16 new_var;

    actorGetNodePos(actor, boneIndex, &boneX, &boneY, &boneZ);
    new_var = ((Actor *) actor)->flags & 0x200;
    if ((!new_var && (((Actor *) actor)->sub4 != NULL)) && (sEffectPendingFlags & 0x80)) {
        effectFlagsOr(0x40);
    }
    effectCreate(asset, scale, boneX, boneY, boneZ, actor, 0, boneIndex, (s32) flags);
}

void effectCreateAtPosition(s32 asset, f32 scale, f32 x, f32 y, f32 z) {
    effectCreate(asset, scale, x, y, z, NULL, 0, 0, 0);
}

extern s32 gGlobalOverlayFlags;
void effectBuildGridVertices(EffectNode *);
#define UA1_D08_FIELD(type, effect, offset) (*(type *)((u8 *)(effect) + (offset)))

EffectNode *effectCreate(s32 asset, f32 scale, f32 posX, f32 posY, f32 posZ, void *owner, s32 boneIndex, s32 subIndex, u8 flags) {
    EffectNode *effect;
    EffectGridNode *node;
    s32 found;
    s32 i;

    effectGridRegister((EffectGridNode *)asset);
    node = sEffectGridHead;
    found = 0;
    if (node != NULL) {
        do {
            if (node->unk0 == (void *)asset) {
                found = 1;
            } else {
                node = node->unk24;
            }
        } while ((found == 0) && (node != NULL));
    }
    if (found == 0) {
        effectResetState();
        return NULL;
    }
    effect = heapAlloc(0x3A0);
    if (sEffectListHead != NULL) {
        sEffectListTail->next = effect;
        effect->previous = sEffectListTail;
    } else {
        sEffectListHead = effect;
        effect->previous = NULL;
    }
    sEffectListTail = effect;
    if ((u8) sEffectPendingFade != 0) {
        posX *= 4.0f;
        posY *= 4.0f;
        posZ *= 4.0f;
        scale *= 4.0f;
        sEffectPendingScaleX *= 4.0f;
        sEffectPendingScaleY *= 4.0f;
    }
    UA1_D08_FIELD(f32, effect, 0x340) = posX;
    UA1_D08_FIELD(f32, effect, 0x344) = posY;
    UA1_D08_FIELD(f32, effect, 0x348) = posZ;
    if ((u8) sEffectPendingHasScale != 0) {
        UA1_D08_FIELD(f32, effect, 0x360) = sEffectPendingScaleX;
        UA1_D08_FIELD(f32, effect, 0x364) = sEffectPendingScaleY;
    } else {
        UA1_D08_FIELD(f32, effect, 0x360) = scale;
        UA1_D08_FIELD(f32, effect, 0x364) = scale;
    }
    if ((u8) sEffectPendingColorA != 0) {
        UA1_D08_FIELD(u8, effect, 0x36A) = *(u8 *)&sEffectPendingColorR;
        UA1_D08_FIELD(u8, effect, 0x36B) = *(u8 *)&sEffectPendingColorG;
        UA1_D08_FIELD(u8, effect, 0x36C) = *(u8 *)&sEffectPendingColorB;
        UA1_D08_FIELD(u8, effect, 0x36D) = *(u8 *)&sEffectPendingColorA;
    } else {
        UA1_D08_FIELD(u8, effect, 0x36A) = *((u8 *)node + 0x10);
        UA1_D08_FIELD(u8, effect, 0x36B) = *((u8 *)node + 0x11);
        UA1_D08_FIELD(u8, effect, 0x36C) = *((u8 *)node + 0x12);
        UA1_D08_FIELD(u8, effect, 0x36D) = *((u8 *)node + 0x13);
    }
    UA1_D08_FIELD(u8, effect, 0x36E) = *(u8 *)&sEffectPendingDepth;
    effect->mode = *(u8 *)&sEffectPendingFade;
    UA1_D08_FIELD(s16, effect, 0x368) = sEffectPendingAngle;
    UA1_D08_FIELD(s32, effect, 0x380) = *((u8 *)node + 9) * *((u8 *)node + 8);
    UA1_D08_FIELD(u8, effect, 0x334) = flags;
    effect->resource = (s32)owner;
    UA1_D08_FIELD(s16, effect, 0x33C) = boneIndex;
    UA1_D08_FIELD(s8, effect, 0x33E) = subIndex;
    UA1_D08_FIELD(s16, effect, 0x34E) = sEffectPendingParam;
    UA1_D08_FIELD(u8, effect, 0x350) = sEffectPendingMode;
    UA1_D08_FIELD(u8, effect, 0x351) = 0;
    UA1_D08_FIELD(s32, effect, 0x354) = sEffectPendingDuration;
    UA1_D08_FIELD(s32, effect, 0x358) = 0;
    UA1_D08_FIELD(s32, effect, 0x35C) = sEffectPendingSpeed;
    if (gGlobalOverlayFlags & 0x100) {
        UA1_D08_FIELD(s16, effect, 0x34C) = 0x7D0;
    } else {
        UA1_D08_FIELD(s16, effect, 0x34C) = sEffectPendingMaxDist;
    }
    UA1_D08_FIELD(EffectGridNode *, effect, 0x330) = node;
    effect->next = NULL;
    UA1_D08_FIELD(s32, effect, 0x328) = sEffectPendingCallback;
    effect->allocation = NULL;
    UA1_D08_FIELD(s16, effect, 0x388) = sEffectPendingLifetime;
    UA1_D08_FIELD(s8, effect, 0x38A) = -1;
    effect->flags = sEffectPendingFlags;
    UA1_D08_FIELD(s16, effect, 0x38E) = sEffectPendingBoundsMinX;
    UA1_D08_FIELD(s16, effect, 0x390) = sEffectPendingBoundsMinY;
    UA1_D08_FIELD(s16, effect, 0x392) = sEffectPendingBoundsMaxX;
    UA1_D08_FIELD(s16, effect, 0x394) = sEffectPendingBoundsMaxY;
    for (i = 0; i < gViewportCount; i++) {
        ((void **)effect)[i * 2] = heapAlloc(0x200);
        ((void **)effect)[i * 2 + 1] = heapAlloc(0x200);
    }
    *((u8 *)effect + 0x20) = gViewportCount;
    effectBuildGridVertices(effect);
    effectResetState();
    return effect;
}
#undef UA1_D08_FIELD

typedef struct Fx119AEffectVertex {
    s16 x;
    s16 y;
    s16 z;
    s16 flag;
    s16 s;
    s16 t;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Fx119AEffectVertex;

void effectBuildGridVertices(EffectNode *effect) {
    EffectGridNode *node;
    Fx119AEffectVertex *vertex;
    s32 column;
    s32 row;
    s32 vertexIndex;
    s32 startX;
    s32 x;
    s32 y;
    node = *(EffectGridNode **)((u8 *)effect + 0x330);
    vertexIndex = 0;
    if (node->unk8 == 0) {} // FAKE: gives unk8 the first candidate index (a1)
    if (node->unk9 == 0) {} // FAKE: gives unk9 the second candidate index (a2)
    node = *(EffectGridNode **)((u8 *)effect + 0x330); // FAKE: kill splits the unk8/unk9 webs so they reload in the arms
    x = -(node->unk8 * node->unkC) / 2;
    startX = x;
    if (effect->mode == 0) {
        y = -(node->unk9 * node->unkE) / 2;
    } else {
        y = (node->unk9 * node->unkE) / 2;
    }
    for (row = 0; row < node->unk9; row++) {
        x = startX;
        column = 0;
        if (node->unk8 > 0) {
            vertex = (Fx119AEffectVertex *)((u8 *)effect + 0x28) + vertexIndex;
            do {
                    vertex[0].x = x;
                    vertex[0].y = y;
                    vertex[0].z = 0;
                    vertex[0].s = 0;
                    vertex[0].t = 0;
                    vertex[1].x = node->unkC + x;
                    vertex[1].y = y;
                    vertex[1].z = 0;
                    vertex[1].s = node->unkC << 5;
                    vertex[1].t = 0;
                    vertex[2].x = x;
                    vertexIndex += 2;
                    vertex += 2;
                    if (effect->mode == 0) {
                        vertex[0].y = node->unkE + y;
                    } else {
                        vertex[0].y = y - node->unkE;
                    }
                    vertex[0].z = 0;
                    vertex[0].s = 0;
                    vertexIndex += 1;
                    vertex += 1;
                    vertex[-1].t = node->unkE << 5;
                    vertex[0].x = node->unkC + x;
                    if (effect->mode == 0) {
                        vertex[0].y = node->unkE + y;
                    } else {
                        vertex[0].y = y - node->unkE;
                    }
                    vertex[0].z = 0;
                    vertex[0].s = node->unkC << 5;
                    vertexIndex += 1;
                    vertex += 1;
                    vertex[-1].t = node->unkE << 5;
                    x += node->unkC;
                    column++;
                } while (column < node->unk8);
            }
            if (effect->mode == 0) {
                y += node->unkE;
            } else {
                y -= node->unkE;
            }
    }
}

#define UA1_D08_FIELD(type, effect, offset) (*(type *)((u8 *)(effect) + (offset)))
extern u32 gFrameCounter;
extern s32 gPlayerSlots;
void assetFreeBuffer(s32, s32, s32);
s16 mapChunkFindByPosition(f32, f32, f32, s32);
s32 renderEntryAddOrUpdate(s32, u8, void *, f32, f32, f32, s32, s32, s32, s32, s32);
void effectLoadFrameAssets(s16 *, u8, u8 *, s32, s32, s32 *);
void effectFreeAndUnlink(EffectNode *);
void effectComputeTransformMatrix(Mtx *, u8, f32, f32, f32, f32, f32, f32, f32, f32, u8);

void effectUpdateAll(u8 pGlist) {
    EffectNode *effect;
    u8 chunkFound;
    EffectGridNode *node2;
    s32 i;
    s32 offset;
    s32 offset2;

    effect = sEffectListHead;
    for (; effect != NULL; effect = effect->next) {
        if (UA1_D08_FIELD(s16, effect, 0x368) == 0) {
            UA1_D08_FIELD(u8, effect, 0x32C) = 0;
            UA1_D08_FIELD(u8, effect, 0x32D) = 0;
            UA1_D08_FIELD(u8, effect, 0x21) = 0;
            UA1_D08_FIELD(s32, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x18) = gFrameCounter;
            effect->flags &= 0xFFEF;
            switch (UA1_D08_FIELD(u8, effect, 0x334)) {
            case 1:
                modelSlotGetNodePos(UA1_D08_FIELD(s16, effect, 0x33C), 1, UA1_D08_FIELD(u8, effect, 0x33E),
                                    (f32 *)((u8 *)effect + 0x340), (f32 *)((u8 *)effect + 0x344),
                                    (f32 *)((u8 *)effect + 0x348));
                break;
            case 2: {
                if ((UA1_D08_FIELD(Actor *, effect, 0x338)->flags & 0x200) != 0 || UA1_D08_FIELD(Actor *, effect, 0x338)->sub4 == NULL) {
                    actorGetNodePos(UA1_D08_FIELD(Actor *, effect, 0x338), UA1_D08_FIELD(u8, effect, 0x33E), (f32 *)((u8 *)effect + 0x340),
                                    (f32 *)((u8 *)effect + 0x344), (f32 *)((u8 *)effect + 0x348));
                } else {
                    effect->flags |= 0x10;
                }
                break;
            }
            }
            chunkFound = 0;
            if (!pGlist || (effect->flags & 1)) {
                if (UA1_D08_FIELD(void *, effect, 0x328) != NULL) {
                    ((void (*)(void *, u8 *))UA1_D08_FIELD(void *, effect, 0x328))(effect, &chunkFound);
                }
            } else if (UA1_D08_FIELD(void *, effect, 0x328) != NULL) {
                if (gViewportCount > 0) {
                    i = 0;
                    offset = 0;
                    do {
                        if (((u8 *)gPlayerSlots)[offset] != 0) {
                            memcpy((u8 *)effect + i * 0x80 + gGfxBufferIndex * 0x40 + 0x128,
                                   (u8 *)effect + i * 0x80 + (gGfxBufferIndex ^ 1) * 0x40 + 0x128, 0x40);
                        }
                        i++;
                        offset += 0x2F0;
                    } while (i < gViewportCount);
                }
                UA1_D08_FIELD(u8, effect, 0x32C) = 3;
            }
            if (UA1_D08_FIELD(s16, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x16) ==
                UA1_D08_FIELD(s16, effect, 0x34E)) {
                UA1_D08_FIELD(s16, effect, 0x34E) = 0;
                UA1_D08_FIELD(s32, effect, 0x358) = UA1_D08_FIELD(s32, effect, 0x358) + 1;
                if (UA1_D08_FIELD(s32, effect, 0x354) == UA1_D08_FIELD(s32, effect, 0x358) &&
                    -1 != UA1_D08_FIELD(s32, effect, 0x354)) {
                    UA1_D08_FIELD(u8, effect, 0x32D) = 1;
                }
            }
            if (chunkFound != 0) {
                UA1_D08_FIELD(u8, effect, 0x32D) = 1;
            }
            if (UA1_D08_FIELD(u8, effect, 0x32D) != 0) {
                effectFreeAndUnlink(effect);
            } else {
                if (gViewportCount >= 2) {
                    i = 1;
                    offset = 0x2F0;
                    do {
                        if (((u8 *)gPlayerSlots)[offset] != 0) {
                            memcpy((u8 *)effect + i * 0x80 + gGfxBufferIndex * 0x40 + 0x128,
                                   (u8 *)effect + gGfxBufferIndex * 0x40 + 0x128, 0x40);
                        }
                        i++;
                        offset += 0x2F0;
                    } while (i < gViewportCount);
                }
                if (UA1_D08_FIELD(u8, effect, 0x32C) != 3) {
                    if (gViewportCount > 0) {
                        i = 0;
                        offset = 0;
                        do {
                            if (((u8 *)gPlayerSlots)[offset] != 0) {
                                effectComputeTransformMatrix((Mtx *)((u8 *)effect + i * 0x80 + gGfxBufferIndex * 0x40 + 0x128),
                                              UA1_D08_FIELD(u8, effect, 0x32C),
                                              UA1_D08_FIELD(f32, effect, 0x360),
                                              UA1_D08_FIELD(f32, effect, 0x364),
                                              UA1_D08_FIELD(f32, (u8 *)gPlayerSlots + offset, 0x21C),
                                              UA1_D08_FIELD(f32, (u8 *)gPlayerSlots + offset, 0x220),
                                              UA1_D08_FIELD(f32, (u8 *)gPlayerSlots + offset, 0x224),
                                              UA1_D08_FIELD(f32, effect, 0x340),
                                              UA1_D08_FIELD(f32, effect, 0x344),
                                              UA1_D08_FIELD(f32, effect, 0x348), effect->mode);
                            }
                            i++;
                            offset += 0x2F0;
                        } while (i < gViewportCount);
                    }
                    UA1_D08_FIELD(u8, effect, 0x32C) = 3;
                }
                if (effect->mode == 0) {
                    s32 renderArg;
                    if (effect->flags & 4) {
                        renderArg = 4;
                        if (!(effect->flags & 8)) {
                            UA1_D08_FIELD(s8, effect, 0x38A) = mapChunkFindByPosition(
                                UA1_D08_FIELD(f32, effect, 0x340), UA1_D08_FIELD(f32, effect, 0x344),
                                UA1_D08_FIELD(f32, effect, 0x348), 0);
                        }
                    } else {
                        renderArg = 1;
                    }
                    renderEntryAddOrUpdate(0, 5, effect, UA1_D08_FIELD(f32, effect, 0x340),
                                           UA1_D08_FIELD(f32, effect, 0x344),
                                           UA1_D08_FIELD(f32, effect, 0x348),
                                           UA1_D08_FIELD(s16, effect, 0x34C), 0, 1, -1, renderArg);
                } else {
                    renderEntryAddOrUpdate(0, 5, effect, UA1_D08_FIELD(f32, effect, 0x340),
                                           UA1_D08_FIELD(f32, effect, 0x344),
                                           UA1_D08_FIELD(f32, effect, 0x348), 0, 0, 1, -1, 3);
                }
                effectLoadFrameAssets((s16 *)UA1_D08_FIELD(void *, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x20),
                              UA1_D08_FIELD(u8, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x15),
                              (u8 *)UA1_D08_FIELD(void *, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x1C),
                              UA1_D08_FIELD(s32, effect, 0x380), UA1_D08_FIELD(s16, effect, 0x34E),
                              &UA1_D08_FIELD(s32, effect, 0x370));
                if (!pGlist || (effect->flags & 1)) {
                    UA1_D08_FIELD(u8, effect, 0x351) = UA1_D08_FIELD(u8, effect, 0x351) + 1;
                    if (UA1_D08_FIELD(u8, effect, 0x350) == UA1_D08_FIELD(u8, effect, 0x351)) {
                        UA1_D08_FIELD(s16, effect, 0x34E) = UA1_D08_FIELD(s16, effect, 0x34E) + 1;
                        UA1_D08_FIELD(u8, effect, 0x351) = 0;
                    }
                }
            }
            effect->flags |= 8;
        } else {
            if (!pGlist || (effect->flags & 1)) {
                UA1_D08_FIELD(s16, effect, 0x368) = UA1_D08_FIELD(s16, effect, 0x368) - 1;
            }
        }
    }
    for (node2 = sEffectGridHead; node2 != NULL; node2 = node2->unk24) {
        if (gFrameCounter - node2->unk18 >= 0xB) {
            continue;
        }
        if (node2->unk18 == -1) {
            continue;
        }
        if (node2->unk16 * node2->unk8 * node2->unk9 > 0) {
            i = 0;
            offset2 = 0;
            do {
                if (node2 && node2) {} // FAKE: raises node2 priority above offset2 (node2 -> s1, offset2 -> s2)
                if (((s32 *)((u8 *)node2->unk1C + offset2))[1] != -1) {
                    if (gFrameCounter - node2->unk18 == 0xA) {
                        assetFreeBuffer(((s32 *)((u8 *)node2->unk1C + offset2))[0], 0x319, 0x1F);
                        ((s32 *)((u8 *)node2->unk1C + offset2))[1] = -1;
                    }
                }
                i++;
                offset2 += 8;
            } while (i < node2->unk16 * node2->unk8 * node2->unk9);
        }
    }
}
#undef UA1_D08_FIELD

void effectFreeAndUnlink(EffectNode *);

void effectFreeByResource(s32 resource) {
    EffectNode *effect;

    effect = sEffectListHead;
    if (effect != NULL) {
        do {
            if (resource == effect->resource) {
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

void renderEntryRemove(s32, s32, s32, void *);
void func_8062D26C(void *);
void heapFreeDeferred(void *);

void effectFreeAndUnlink(EffectNode *effect) {
    u8 layer;
    s32 prevNode;
    s32 i;
    EffectNode *previous;
    EffectNode *next;
    EffectNode *buffer;

    if (effect->mode == 0) {
        if (effect->flags & 4) {
            renderEntryRemove(0, (s32)effect, 4, &layer - 8);
        } else {
            func_8062D26C(effect);
        }
    } else {
        renderEntryRemove(0, (s32)effect, 3, &layer - 8);
    }
    prevNode = (s32)effect->allocation;
    if (prevNode != 0) {
        heapFreeDeferred((void *)prevNode);
    }
    i = 0;
    buffer = effect;
    while (i < effect->itemCount) {
        heapFreeDeferred(((void **)buffer)[0]);
        heapFreeDeferred(((void **)buffer)[1]);
        i += 1;
        buffer = (EffectNode *)((u8 *)buffer + 8);
    }
    if (osCicId != 0x17D9) {
        osSetTime((s64)(s32)randomLcgNext());
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

typedef struct EffectRouteEntry {
    s32 value;
    s32 column;
} EffectRouteEntry;

s32 assetLoad(s32, s16, s32, s32);

void effectLoadFrameAssets(s16 *effect, u8 inX, u8 *inY, s32 inZ, s32 screenX, s32 *screenY) {
    u8 category;
    s32 i;
    s32 index;
    s32 value;
    s32 *out;
    EffectRouteEntry *entry;

    i = 0;
    if (inZ > 0) {
        out = screenY;
        index = inZ * screenX;
        entry = (EffectRouteEntry *)inY;
        entry += index;
        do {
            if (entry->column == -1) {
                if (inX) {
                    category = 0x19;
                } else {
                    category = 7;
                }
                value = assetLoad(category, effect[index + i], 0, 0);
                *out = value;
                entry->value = value;
            } else {
                *out = entry->value;
            }
            i += 1;
            out += 1;
            entry += 1;
            (entry + (-1))->column = screenX;
        } while (i != inZ);
    }
}

s32 mathAsinFixed(s32);
void matrixMakeRotationZ(f32 (*)[4], f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
f32 distance3D(f32, f32, f32, f32, f32, f32);

void effectComputeTransformMatrix(Mtx *dst, u8 x, f32 y, f32 z, f32 scaleX, f32 scaleY, f32 pitch, f32 yaw, f32 roll, f32 mode, u8 depthScale) {
    f32 pad[2];
    f32 distance;
    f32 value;
    f32 absValue;
    s32 angle;
    s32 temp;
    f32 scale[4][4];
    f32 transform[4][4];
    Mtx mtx;

    if (depthScale == 0) {
        distance = distance3D(scaleX, scaleY, pitch, yaw, roll, mode);
        value = distance;
        if ((f64)distance < 0.1) {
            value = 1.0f;
        }
        distance = (scaleY - roll) / value;
        if (distance > 0.0f) {
            absValue = distance;
        } else {
            absValue = -distance;
        }
        temp = mathAsinFixed((s32)((f64)absValue * 65536.0)) >> 4;
        angle = temp;
        if (distance >= 0.0f) {
            angle = 0xFFF - temp;
        }
        if (x != 2) {
            guScaleF(scale, y, z, 0.0f);
        } else {
            guScaleF(scale, 1.0f, 1.0f, 1.0f);
        }
        guRotateF(transform, (f32)(((f64)angle / 4095.0) * 360.0), 1.0f, 0.0f, 0.0f);
        guMtxCatF(scale, transform, scale);
        value = mathAngleBetweenPointsRad(scaleX, pitch, yaw, mode);
        guRotateF(transform, value * 57.295776f, 0.0f, 1.0f, 0.0f);
        guMtxCatF(scale, transform, scale);
        guTranslateF(transform, yaw, roll, mode);
        guMtxCatF(scale, transform, scale);
    } else {
        if (x != 2) {
            guScaleF(scale, y, z, 0.0f);
        } else {
            guScaleF(scale, 1.0f, 1.0f, 1.0f);
        }
        matrixMakeRotationZ(transform, (f32)sEffectPendingZOffset);
        guMtxCatF(scale, transform, scale);
        guTranslateF(transform, yaw, roll, mode);
        guMtxCatF(scale, transform, scale);
    }
    if ((x == 1) || (x == 2)) {
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

typedef struct EffectTextureNode {
    u8 pad0[0xA];
    u8 unkA;
    u8 unkB;
    s16 unkC;
    s16 unkE;
    u8 pad10[4];
    u8 unk14;
} EffectTextureNode;

typedef struct EffectDrawView {
    u8 pad0[0x21];
    u8 unk21;
    u8 pad22[6];
    Vtx unk28[48];
    u8 pad328[8];
    EffectTextureNode *unk330;
    u8 pad334[0xC];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x1E];
    u8 unk36A;
    u8 unk36B;
    u8 unk36C;
    u8 unk36D;
    u8 unk36E;
    u8 unk36F;
    void *unk370[4];
    s32 unk380;
    u8 pad384[4];
    s16 unk388;
    s8 unk38A;
    u8 pad38B;
    u16 unk38C;
    s16 unk38E;
    s16 unk390;
    s16 unk392;
    s16 unk394;
} EffectDrawView;

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
Gfx *gfxInit2DDisplayList(Gfx *);
void lightSampleColorAtPosition(f32, f32, f32, s16, u8 *, u8 *, u8 *, s16);
s32 mapChunkContainsPoint(s16, s16, s16);
s32 mapChunkIsInUse(s16);

Gfx *effectGridBuildDisplayList(EffectDrawView *drawView, Gfx *inGlist, s16 alpha) {
    s32 i;
    u8 red;
    u8 green;
    u8 blue;
    f32 colorRed = 1.0f;
    f32 colorGreen = 1.0f;
    f32 colorBlue = 1.0f;
    Gfx *glist;

    if (drawView->unk38C & 0x50) {
        return inGlist;
    }
    if ((((gPrimaryPlayerActor->state == 0x83) || (gPrimaryPlayerActor->state == 0x67)) && !(drawView->unk38C & 0x20)) || (((gGlobalPauseFlags & 0x100002) == 0x100002) && !(drawView->unk38C & 0x100))) {
        return inGlist;
    }
    if (alpha == -1) {
        alpha = drawView->unk38A;
    }
    if (drawView->unk388 != -1) {
        if (drawView->unk36F != 0) {
            if (mapChunkContainsPoint((s16)((f64)drawView->unk340 * 0.25), (s16)((f64)drawView->unk344 * 0.25), drawView->unk388) == 0) {
                return inGlist;
            }
        } else if (alpha != drawView->unk388) {
            return inGlist;
        }
    }
    glist = ((Gfx *(*)[2])drawView)[drawView->unk21][gGfxBufferIndex];
    drawView->unk21++;
    EFFECT_WRITE_GFX(inGlist++, 0xDE000000, osVirtualToPhysical(glist));
    EFFECT_WRITE_GFX(glist++, 0xE7000000, 0);
    EFFECT_WRITE_GFX(glist++, 0xE3000A01, 0);
    EFFECT_WRITE_GFX(glist++, 0xD9000000, 0);
    EFFECT_WRITE_GFX(glist++, 0xE3001801, 0xC0);
    if (drawView->unk36E != 0) {
        EFFECT_WRITE_GFX(glist++, 0xD9FFFFFF, 0x200005);
        EFFECT_WRITE_GFX(glist++, 0xE200001C, 0x504B50);
    } else {
        EFFECT_WRITE_GFX(glist++, 0xD9FFFFFF, 0x200004);
        EFFECT_WRITE_GFX(glist++, 0xE200001C, 0x504240);
    }
    EFFECT_WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    EFFECT_WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);

    if (drawView->unk330->unk14 == 0 && mapChunkIsInUse(alpha)) {
        lightSampleColorAtPosition(drawView->unk340, drawView->unk344, drawView->unk348, 0, &red, &green, &blue, alpha);
        colorRed = (f32)((f64)red / 255.0);
        colorGreen = (f32)((f64)green / 255.0);
        colorBlue = (f32)((f64)blue / 255.0);
    }
    gDPSetPrimColor(glist++, 0, 0, (u32)((f32)drawView->unk36A * colorRed), (u32)((f32)drawView->unk36B * colorGreen), (u32)((f32)drawView->unk36C * colorBlue), drawView->unk36D);
    if (drawView->unk36F != 0) {
        EFFECT_WRITE_GFX(glist++, 0xDA380007, &D_20000C0);
        EFFECT_WRITE_GFX(glist++, 0xDA380003, &D_2000180);
        glist = gfxInit2DDisplayList(glist);
        if (drawView->unk388 == -1) {
            EFFECT_WRITE_GFX(glist++, 0xED000000 | (((s32)((f32)drawView->unk38E * 4.0f) & 0xFFF) << 12) | ((s32)((f32)drawView->unk390 * 4.0f) & 0xFFF), (((s32)((f32)drawView->unk392 * 4.0f) & 0xFFF) << 12) | ((s32)((f32)drawView->unk394 * 4.0f) & 0xFFF));
        }
    }
    EFFECT_WRITE_GFX(glist++, 0xDA380000, osVirtualToPhysical((u8 *)drawView + (gCurrentPlayerIndex << 7) + (gGfxBufferIndex << 6) + 0x128));

    for (i = 0; i < drawView->unk380; i++) {
        if (D_807F6009 != 5 || D_807F600C != (s32)drawView->unk370[i]) {
            EFFECT_WRITE_GFX(glist++, 0xE7000000, 0);
            switch (drawView->unk330->unkB) {
                case 0:
                    gDPLoadTextureBlock_4b(glist++, drawView->unk370[i], drawView->unk330->unkA, drawView->unk330->unkC, drawView->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 1:
                    gDPLoadTextureBlock(glist++, drawView->unk370[i], drawView->unk330->unkA, G_IM_SIZ_8b, drawView->unk330->unkC, drawView->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 2:
                    gDPLoadTextureBlock(glist++, drawView->unk370[i], drawView->unk330->unkA, G_IM_SIZ_16b, drawView->unk330->unkC, drawView->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 3:
                    gDPLoadTextureBlock(glist++, drawView->unk370[i], drawView->unk330->unkA, G_IM_SIZ_32b, drawView->unk330->unkC, drawView->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
            }
            D_807F600C = (s32)drawView->unk370[i];
        }
        EFFECT_WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical(drawView->unk28 + (i << 2)));
        EFFECT_WRITE_GFX(glist++, 0x06000206, 0x406);
    }
    EFFECT_WRITE_GFX(glist++, 0xD8380002, 0x40);
    EFFECT_WRITE_GFX(glist++, 0xE7000000, 0);
    EFFECT_WRITE_GFX(glist++, 0xE3001801, 0);
    if (drawView->unk36F != 0) {
        EFFECT_WRITE_GFX(glist++, 0xDA380007, &D_2000000);
        EFFECT_WRITE_GFX(glist++, 0xDA380005, &D_2000200);
        if (drawView->unk388 == -1) {
            EFFECT_WRITE_GFX(glist++, 0xED000000, ((((s32)((f32)gScreenWidth * 4.0f) & 0xFFF) << 12) | ((s32)((f32)gScreenHeight * 4.0f) & 0xFFF)));
        }
    }
    EFFECT_WRITE_GFX(glist++, 0xE7000000, 0);
    EFFECT_WRITE_GFX(glist++, 0xDF000000, 0);
    D_807F6009 = 5;
    return inGlist;
}
