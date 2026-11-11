#include "common.h"
#include "compiler/ido/memory.h"
#include "proto/global/15050.h"
#include "proto/global/2F550.h"
#include "proto/global/70FD0.h"
#include "proto/global/79890.h"
#include "proto/global/7CA80.h"

typedef struct CollisionSphereNode {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[8];
    struct CollisionSphereNode *next;
} CollisionSphereNode;

typedef struct CollisionHitSub140 {
    u8 pad0[0x8C];
    CollisionSphereNode *unk8C;
} CollisionHitSub140;

typedef struct CollisionHitElem {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} CollisionHitElem;

typedef struct CollisionHitCallback {
    s32 type;
    u8 pad4[4];
    void *actor;
    s32 count;
    CollisionHitElem *elems;
    struct CollisionHitCallback *next;
} CollisionHitCallback;

typedef struct CollisionHitActor {
    u8 pad0[0x64];
    u32 unk64;
    u8 pad68[0x14];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x6C];
    s16 arcYawMin;
    s16 arcYawMax;
    u8 padF8[4];
    u8 hasArcBounds;
    u8 unkFD;
    u8 padFE[0x3E];
    CollisionHitCallback *callbacks;
    CollisionHitSub140 *unk140;
} CollisionHitActor;

extern u8 D_807FB606;
s32 collisionSpheresOverlap(s32, s32, s32, s32, s32, s32, s32, s32);

u8 actorCollisionGetNodeHitPoint(CollisionHitActor *self, CollisionHitActor *other, f32 *outX, f32 *outZ) {
    CollisionHitCallback *cb;
    f32 posX_f;
    f32 posY_f;
    f32 posZ_f;
    s32 posX;
    s32 posY;
    s32 posZ;
    CollisionHitElem *elem;
    CollisionSphereNode *node;
    CollisionHitSub140 *sub140;
    s32 i;
    s32 j;
    f32 elemX_f;
    s32 pad2[1];
    s8 foundCb;
    u8 matched;

    cb = self->callbacks;
    matched = 0;
    foundCb = 0;
    D_807FB606 = 0;
    sub140 = self->unk140;
    actorUpdateCollisionSpheres(self, 1);
    if (!actorTableContains((Actor *)other)) {
        return 0;
    }

    posX_f = other->unk7C;
    posY_f = other->unk80;
    posZ_f = other->unk84;

    if (cb != NULL) {
        do {
            if (cb->type == 0x8000 && cb->actor == other) {
                elem = cb->elems;
                foundCb = 1;
                for (j = 0; j < cb->count; j++, elem++) {
                    elemX_f = elem->unk0;
                    node = sub140->unk8C;
                    for (i = elem->unk14 - 1; i != 0; i--) {
                        node = node->next;
                    }
                    if (collisionSpheresOverlap((s32)(posX_f * 8.0f), (s32)(posY_f * 8.0f), (s32)(posZ_f * 8.0f), (s32)(elemX_f * 8.0f),
                                      node->unk10, node->unk14, node->unk18, node->unk1C)) {
                        matched = 1;
                        collisionNodeLocalToWorldXZ(self, elem, outX, outZ);
                    }
                    func_806755A8((s32)(posX_f * 8.0f), (s32)(posZ_f * 8.0f), node->unk10, node->unk18, &other->arcYawMin, &other->arcYawMax);
                    other->hasArcBounds = 1;
                    other->unkFD = 1;
                }
            }
            cb = cb->next;
        } while (cb != NULL && !(u8)foundCb);  // FAKE: s8 foundCb + (u8) read: keeps `foundCb = 1` off the shared u8 constant-1 web (li t2 ring temp) while the loop test stays lbu
    }

    if (D_807FB606 != 0) {
        other->unk64 |= 0x100;
    }
    return matched;
}

typedef struct CollisionSphereNodeFull {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[4];
    u16 unk24;
    u8 unk26;
    u8 unk27;
    struct CollisionSphereNodeFull *next;
} CollisionSphereNodeFull;

typedef struct CollisionSub140Full {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x7C];
    CollisionSphereNodeFull *unk8C;
} CollisionSub140Full;

typedef struct CollisionCheckActor {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[4];
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u8 pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x8C];
    void *riderList;
    u8 pad118[0x28];
    CollisionSub140Full *unk140;
    u8 unk144;
} CollisionCheckActor;

typedef struct CollisionActorEntry {
    CollisionCheckActor *actor;
    s32 unk4;
} CollisionActorEntry;

extern u16 gActiveActorCount;
extern CollisionActorEntry gActiveActors[];
struct CollisionHitRecordNode;
struct CollisionMtxOwner;
struct CollisionMtxNode;
extern struct CollisionHitRecordNode *D_807FB620;
extern struct CollisionHitRecordNode *D_807FB624;
extern s32 D_807FB628;

s32 collisionSpheresOverlap(s32, s32, s32, s32, s32, s32, s32, s32);

void actorCollisionCheckNodeSpheres(CollisionCheckActor *self) {
    s32 i;
    CollisionCheckActor *actor;
    CollisionSub140Full *actor_sub140;
    s32 sub_unk0;
    s32 sub_unk4;
    s32 sub_unk8;
    s32 sub_unkC;
    CollisionSphereNodeFull *node1;
    CollisionSphereNodeFull *node2;
    s32 node1Idx;
    s32 node2Idx;
    CollisionSub140Full *sub140;
    f32 dist;
    f32 hitLocalX;
    f32 hitLocalY;
    f32 hitLocalZ;
    s32 s0;
    u16 mask1;
    u16 mask2;
    CollisionActorEntry *entry;

    sub140 = self->unk140;
    sub_unk0 = 0;
    if (sub_unk0) {} // FAKE: raises sub_unk0's colouring priority so it gets s7 while unk4 is loaded first
    sub_unk4 = sub140->unk4;
    sub_unk0 = sub140->unk0;
    sub_unk8 = sub140->unk8;
    sub_unkC = sub140->unkC;
    i = 0;
    if (gActiveActorCount > 0) {
        entry = gActiveActors;
        do {
            D_807FB620 = NULL;
            D_807FB624 = NULL;
            D_807FB628 = 0;
            actor = entry->actor;
            s0 = 0;
            actor_sub140 = actor->unk140;
            if (actor->riderList != NULL && (actor->unk60 & 0x40) && actorRiderListContains(actor, self)) {
                s0 = 1;
            }
            if ((self->unk60 & 0x80) && actorRiderListContains(self, actor)) {
                s0 = 1;
            }
            if ((actor->unk60 & 0x2000) == 0 &&
                sub140 != actor_sub140 &&
                actor->unk144 != 1 &&
                (actor->unk60 & 0x10) &&
                s0 == 0 &&
                collisionSpheresOverlap(sub_unk0, sub_unk4, sub_unk8, sub_unkC,
                              actor_sub140->unk0, actor_sub140->unk4, actor_sub140->unk8, actor_sub140->unkC)) {
                actorUpdateCollisionSpheres(self, 0);
                node1Idx = 1;
                actorUpdateCollisionSpheres(actor, 0);
                for (node1 = sub140->unk8C; node1 != NULL; node1 = node1->next, node1Idx++) {
                    if (node1->unk26 != 0 && (node1->unk27 & 8) == 0) {
                        node2Idx = 1;
                        for (node2 = actor_sub140->unk8C; node2 != NULL; node2 = node2->next, node2Idx++) {
                            if (node2->unk26 != 0 && (node2->unk27 & 8) == 0) {
                                if (collisionSpheresOverlap(node1->unk10, node1->unk14, node1->unk18, node1->unk1C,
                                                  node2->unk10, node2->unk14, node2->unk18, node2->unk1C)) {
                                    mask1 = ~node1->unk24;
                                    mask2 = ~node2->unk24;
                                    if ((mask1 & actor->unk5C) && (mask2 & self->unk5C)) {
                                        dist = collisionPointToSphereDistance(sub_unk0, sub_unk4, sub_unk8,
                                                             node2->unk10, node2->unk14, node2->unk18, node2->unk1C);
                                        collisionWorldToNodeLocal((struct CollisionMtxOwner *)actor_sub140, self->unk7C, self->unk80, self->unk84, (struct CollisionMtxNode *)node2,
                                                      &hitLocalX, &hitLocalY, &hitLocalZ);
                                        collisionHitRecordAppend(self->unk54, dist, hitLocalX, hitLocalY, hitLocalZ, node1Idx, node2Idx);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (D_807FB620 != NULL) {
                collisionHitRecordsFlush((s32)self, actor);
            }
            i++; entry++; // LAYOUT: one line keeps the entry/i spill-store order
        } while (i < gActiveActorCount);
    }
}

typedef struct CollisionMtxOwner {
    u8 pad0[0x70];
    void *unk70;
    Mtx *unk74[2];
} CollisionMtxOwner;

typedef struct CollisionMtxNode {
    u8 pad0[0x20];
    s32 unk20;
} CollisionMtxNode;

extern u8 gGfxBufferIndex;

void collisionWorldToNodeLocal(CollisionMtxOwner *owner, f32 worldX, f32 worldY, f32 worldZ, CollisionMtxNode *node, f32 *outX, f32 *outY, f32 *outZ) {
    float worldMtx[4][4];
    float invMtx[4][4];
    u32 mtxIndex;
    Mtx *mtx;

    mtx = owner->unk74[gGfxBufferIndex];
    mtxIndex = node->unk20;
    if (mtxIndex == -1) {
        memcpy(worldMtx, owner->unk70, sizeof(worldMtx));
    } else {
        guMtxL2F(worldMtx, (Mtx *)(((mtxIndex >> 6) << 6) + (u8 *)mtx));
    }
    matrix4Invert(invMtx, worldMtx);
    guMtxXFMF(invMtx, worldX, worldY, worldZ, outX, outY, outZ);
}

f32 collisionPointToSphereDistance(s32 ptX, s32 ptY, s32 ptZ, s32 sphereX, s32 sphereY, s32 sphereZ, s32 sphereRadius) {
    f32 dz;
    f32 dx;
    f32 dy;
    f32 surfaceDist;
    f32 clampedDist;

    dx = (f32) (ptX - sphereX);
    dy = (f32) (ptY - sphereY);
    dz = (f32) (ptZ - sphereZ);
    surfaceDist = sqrtf((dx * dx) + (dy * dy) + (dz * dz)) - (f32) sphereRadius;
    clampedDist = surfaceDist;
    if ((f64) surfaceDist < 0.0) {
        clampedDist = 0.0f;
    }
    return clampedDist / (f32)8;
}

typedef struct CollisionHitRecordNode {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    struct CollisionHitRecordNode *next;
} CollisionHitRecordNode;

extern CollisionHitRecordNode *D_807FB620;
extern CollisionHitRecordNode *D_807FB624;
extern s32 D_807FB628;

void collisionHitRecordAppend(s32 hitType, f32 dist, f32 localX, f32 localY, f32 localZ, s32 node1Idx, s32 node2Idx) {
    CollisionHitRecordNode *recordNode;

    recordNode = heapAlloc(sizeof(CollisionHitRecordNode));
    recordNode->unk0 = dist;
    recordNode->unk4 = localX;
    recordNode->unk8 = localY;
    recordNode->unkC = localZ;
    recordNode->unk10 = node1Idx;
    recordNode->unk14 = node2Idx;
    recordNode->unk18 = hitType;
    recordNode->next = NULL;
    if (D_807FB620 != NULL) {
        D_807FB624->next = recordNode;
    } else {
        D_807FB620 = recordNode;
    }
    D_807FB624 = recordNode;
    D_807FB628 += 1;
}

typedef struct CollisionHitRecord {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} CollisionHitRecord;


void collisionHitRecordsFlush(s32 selfId, void *otherActor) {
    CollisionHitRecord *arr;
    s32 i;
    CollisionHitRecordNode *node;
    CollisionHitRecordNode *next;

    arr = heapAlloc(D_807FB628 * sizeof(CollisionHitRecord));
    node = D_807FB620;
    for (i = 0; i < D_807FB628; i++) {
        arr[i].unk0 = node->unk0;
        arr[i].unk4 = node->unk4;
        arr[i].unk8 = node->unk8;
        arr[i].unkC = node->unkC;
        arr[i].unk10 = node->unk10;
        arr[i].unk14 = node->unk14;
        arr[i].unk18 = node->unk18;
        next = node->next;
        heapFree(node);
        node = next;
    }
    actorAppendCallback(otherActor, selfId, 0x8000, 0, D_807FB628, arr);
}

typedef struct CollisionNodeLink {
    u8 pad0[0x20];
    s32 unk20;
    u8 pad24[0x4];
    struct CollisionNodeLink *next;
} CollisionNodeLink;

typedef struct CollisionNodeSub140 {
    u8 pad0[0x70];
    void *unk70;
    Mtx *unk74[2];
    u8 pad7C[0x10];
    CollisionNodeLink *unk8C;
} CollisionNodeSub140;

typedef struct CollisionLocalOwner {
    u8 pad0[0x140];
    CollisionNodeSub140 *unk140;
} CollisionLocalOwner;

typedef struct CollisionHitRecordRef {
    u8 pad0[0x4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[0x4];
    s32 unk14;
} CollisionHitRecordRef;

void collisionNodeLocalToWorldXZ(CollisionLocalOwner *owner, CollisionHitRecordRef *recordRef, f32 *outWorldX, f32 *outWorldZ) {
    s32 i;
    CollisionNodeLink *node;
    Mtx *mtx;
    float modelMtx[4][4];
    u32 mtxIndex;
    f32 worldX;
    f32 worldY;
    f32 worldZ;

    node = owner->unk140->unk8C;
    for (i = recordRef->unk14 - 1; i != 0; i--) {
        node = node->next;
    }
    mtx = owner->unk140->unk74[gGfxBufferIndex ^ 1];
    mtxIndex = node->unk20;
    if (mtxIndex == -1) {
        memcpy(modelMtx, owner->unk140->unk70, sizeof(modelMtx));
        guMtxXFMF(modelMtx, recordRef->unk4, recordRef->unk8, recordRef->unkC, &worldX, &worldY, &worldZ);
    } else {
        guMtxXFML((Mtx *)(((mtxIndex >> 6) << 6) + (u8 *)mtx), recordRef->unk4, recordRef->unk8, recordRef->unkC, &worldX, &worldY, &worldZ);
    }
    *outWorldX = worldX;
    *outWorldZ = worldZ;
}

s32 mathAsinFixed(s32);
void func_806742C0(s16, s16, s16 *, s16 *);

void func_806755A8(s32 x1, s32 y1, s32 x2, s32 y2, s16 *outMinAngle, s16 *outMaxAngle) {
    s32 pad1;
    s32 pad2;
    f32 dist;
    s16 angle;
    s32 dx;
    s32 dy;
    s32 abs_val;

    dx = x2 - x1;
    if (dx > 0) {
        abs_val = dx;
    } else {
        abs_val = -dx;
    }
    if (abs_val < 0x2711) {
        dy = y2 - y1;
        if (dy > 0) {
            abs_val = dy;
        } else {
            abs_val = -dy;
        }
        if (abs_val < 0x2711) {
            dist = sqrtf((f32)((dx * dx) + (dy * dy)));
            if ((f64)dist != 0.0) {
                if (dx >= 0 && dy >= 0) {
                    angle = (s16)(mathAsinFixed((s32)(((f64)dx * 65535.9) / (f64)dist)) >> 4);
                }
                if (dx >= 0 && dy < 0) {
                    angle = (s16)((mathAsinFixed((s32)(((f64)(y1 - y2) * 65535.9) / (f64)dist)) >> 4) + 0x400);
                }
                if (dx < 0 && dy < 0) {
                    angle = (s16)((mathAsinFixed((s32)(((f64)(x1 - x2) * 65535.9) / (f64)dist)) >> 4) + 0x800);
                }
                if (dx < 0 && dy >= 0) {
                    angle = (s16)((mathAsinFixed((s32)(((f64)dy * 65535.9) / (f64)dist)) >> 4) + 0xC00);
                }
                func_806742C0(angle + 0x400, angle - 0x400, outMinAngle, outMaxAngle);
            }
        }
    }
}
