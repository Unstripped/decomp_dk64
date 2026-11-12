#include "common.h"
#include "compiler/ido/memory.h"
#include "proto/global/15050.h"
#include "proto/global/2F550.h"
#include "proto/global/70FD0.h"
#include "proto/global/79890.h"
#include "proto/global/7CA80.h"

typedef struct CollisionHitRecord {
    f32 dist;
    f32 localX;
    f32 localY;
    f32 localZ;
    s32 sourceNodeIndex;
    s32 nodeIndex;
    s32 sourceId;
} CollisionHitRecord;

typedef struct CollisionHitRecordNode {
    f32 dist;
    f32 localX;
    f32 localY;
    f32 localZ;
    s32 sourceNodeIndex;
    s32 nodeIndex;
    s32 sourceId;
    struct CollisionHitRecordNode *next;
} CollisionHitRecordNode;


extern u8 D_807FB606;
extern u16 gActiveActorCount;
extern ActorEntry gActiveActors[];
extern CollisionHitRecordNode *gCollisionHitListHead;
extern CollisionHitRecordNode *gCollisionHitListTail;
extern s32 gCollisionHitCount;
extern u8 gGfxBufferIndex;
s32 collisionSpheresOverlap(s32, s32, s32, s32, s32, s32, s32, s32);

u8 actorCollisionGetNodeHitPoint(Actor *self, Actor *other, f32 *outX, f32 *outZ) {
    ActorCallbackNode *cb;
    f32 otherX;
    f32 otherY;
    f32 otherZ;
    s32 pad[3];
    CollisionHitRecord *hit;
    ModelNode *node;
    ActorSub140 *collision;
    s32 i;
    s32 j;
    f32 hitDist;
    s32 pad2;
    u8 foundCb;
    u8 matched;

    cb = self->callbacks;
    matched = 0;
    foundCb = 0;
    D_807FB606 = 0;
    collision = self->collision;
    actorUpdateCollisionSpheres(self, 1);
    if (!actorTableContains(other)) {
        return 0;
    }

    otherX = other->x;
    otherY = other->y;
    otherZ = other->z;

    while (cb != NULL && !foundCb) {
        if ((s32)cb->callback == 0x8000 && cb->source == other) { // callback holds the s32 type for actor-attached nodes (actorAllocCallbackNode)
            hit = cb->unk10;
            for (j = 0; j < cb->unkC; j++, hit++) {
                hitDist = hit->dist;
                node = collision->nodes;
                for (i = hit->nodeIndex - 1; i != 0; i--) {
                    node = node->next;
                }
                if (collisionSpheresOverlap(otherX * 8.0f, otherY * 8.0f, otherZ * 8.0f, hitDist * 8.0f,
                                            node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius)) {
                    matched = 1;
                    collisionNodeLocalToWorldXZ(self, hit, outX, outZ);
                }
                collisionComputeArcYawBounds(otherX * 8.0f, otherZ * 8.0f, node->scaledX, node->scaledZ, &other->arcYawMin, &other->arcYawMax);
                other->hasArcBounds = 1;
                other->collisionHit = 1;
            }
            foundCb = 1;
        }
        cb = cb->next;
    }

    if (D_807FB606 != 0) {
        other->renderFlags |= 0x100;
    }
    return matched;
}

void actorCollisionCheckNodeSpheres(Actor *self) {
    s32 i;
    Actor *actor;
    ActorSub140 *otherCollision;
    s32 selfX;
    s32 selfY;
    s32 selfZ;
    s32 selfRadius;
    ModelNode *node1;
    ModelNode *node2;
    s32 node1Idx;
    s32 node2Idx;
    ActorSub140 *selfCollision;
    f32 dist;
    f32 hitLocalX;
    f32 hitLocalY;
    f32 hitLocalZ;
    s32 isRider;
    u16 mask1;
    u16 mask2;
    ActorEntry *entry;

    selfCollision = self->collision;
    selfX = 0;
    if (selfX) {} // FAKE: raises the colouring priority of selfX so it gets s7 while scaledY is loaded first
    selfY = selfCollision->scaledY;
    selfX = selfCollision->scaledX;
    selfZ = selfCollision->scaledZ;
    selfRadius = selfCollision->scaledRadius;
    i = 0;
    if (gActiveActorCount > 0) {
        entry = gActiveActors;
        do {
            gCollisionHitListHead = NULL;
            gCollisionHitListTail = NULL;
            gCollisionHitCount = 0;
            actor = entry->actor;
            isRider = 0;
            otherCollision = actor->collision;
            if (actor->riderList != NULL && (actor->flags & 0x40) && actorRiderListContains(actor, self)) {
                isRider = 1;
            }
            if ((self->flags & 0x80) && actorRiderListContains(self, actor)) {
                isRider = 1;
            }
            if ((actor->flags & 0x2000) == 0 &&
                selfCollision != otherCollision &&
                actor->unk144 != 1 &&
                (actor->flags & 0x10) &&
                isRider == 0 &&
                collisionSpheresOverlap(selfX, selfY, selfZ, selfRadius,
                              otherCollision->scaledX, otherCollision->scaledY, otherCollision->scaledZ, otherCollision->scaledRadius)) {
                actorUpdateCollisionSpheres(self, 0);
                node1Idx = 1;
                actorUpdateCollisionSpheres(actor, 0);
                for (node1 = selfCollision->nodes; node1 != NULL; node1 = node1->next, node1Idx++) {
                    if (node1->active != 0 && (node1->unk27 & 8) == 0) {
                        node2Idx = 1;
                        for (node2 = otherCollision->nodes; node2 != NULL; node2 = node2->next, node2Idx++) {
                            if (node2->active != 0 && (node2->unk27 & 8) == 0) {
                                if (collisionSpheresOverlap(node1->scaledX, node1->scaledY, node1->scaledZ, node1->scaledRadius,
                                                  node2->scaledX, node2->scaledY, node2->scaledZ, node2->scaledRadius)) {
                                    mask1 = ~node1->unk24;
                                    mask2 = ~node2->unk24;
                                    if ((mask1 & actor->collisionFlags) && (mask2 & self->collisionFlags)) {
                                        dist = collisionPointToSphereDistance(selfX, selfY, selfZ,
                                                             node2->scaledX, node2->scaledY, node2->scaledZ, node2->scaledRadius);
                                        collisionWorldToNodeLocal(otherCollision, self->x, self->y, self->z, node2,
                                                      &hitLocalX, &hitLocalY, &hitLocalZ);
                                        collisionHitRecordAppend(self->instanceId, dist, hitLocalX, hitLocalY, hitLocalZ, node1Idx, node2Idx);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (gCollisionHitListHead != NULL) {
                collisionHitRecordsFlush(self, actor);
            }
            i++; entry++; // LAYOUT: one line keeps the entry/i spill-store order
        } while (i < gActiveActorCount);
    }
}

void collisionWorldToNodeLocal(ActorSub140 *owner, f32 worldX, f32 worldY, f32 worldZ, ModelNode *node, f32 *outX, f32 *outY, f32 *outZ) {
    float worldMtx[4][4];
    float invMtx[4][4];
    u32 mtxIndex;
    Mtx *mtx;

    mtx = owner->nodeMtx[gGfxBufferIndex];
    mtxIndex = node->mtxOffset;
    if (mtxIndex == -1) {
        memcpy(worldMtx, owner->modelMtxF, sizeof(worldMtx));
    } else {
        guMtxL2F(worldMtx, &mtx[mtxIndex >> 6]);
    }
    matrix4Invert(invMtx, worldMtx);
    guMtxXFMF(invMtx, worldX, worldY, worldZ, outX, outY, outZ);
}

f32 collisionPointToSphereDistance(s32 ptX, s32 ptY, s32 ptZ, s32 sphereX, s32 sphereY, s32 sphereZ, s32 sphereRadius) {
    f32 dz;
    f32 dx;
    f32 dy;
    f32 surfaceDist;

    dx = ptX - sphereX;
    dy = ptY - sphereY;
    dz = ptZ - sphereZ;
    surfaceDist = sqrtf((dx * dx) + (dy * dy) + (dz * dz)) - sphereRadius;
    if (surfaceDist < 0.0) {
        surfaceDist = 0.0f;
    }
    return surfaceDist / 8;
}

void collisionHitRecordAppend(s32 sourceId, f32 dist, f32 localX, f32 localY, f32 localZ, s32 node1Idx, s32 node2Idx) {
    CollisionHitRecordNode *recordNode;

    recordNode = heapAlloc(sizeof(CollisionHitRecordNode));
    recordNode->dist = dist;
    recordNode->localX = localX;
    recordNode->localY = localY;
    recordNode->localZ = localZ;
    recordNode->sourceNodeIndex = node1Idx;
    recordNode->nodeIndex = node2Idx;
    recordNode->sourceId = sourceId;
    recordNode->next = NULL;
    if (gCollisionHitListHead != NULL) {
        gCollisionHitListTail->next = recordNode;
    } else {
        gCollisionHitListHead = recordNode;
    }
    gCollisionHitListTail = recordNode;
    gCollisionHitCount += 1;
}

void collisionHitRecordsFlush(Actor *self, Actor *otherActor) {
    CollisionHitRecord *records;
    s32 i;
    CollisionHitRecordNode *node;
    CollisionHitRecordNode *next;

    records = heapAlloc(gCollisionHitCount * sizeof(CollisionHitRecord));
    node = gCollisionHitListHead;
    for (i = 0; i < gCollisionHitCount; i++) {
        records[i].dist = node->dist;
        records[i].localX = node->localX;
        records[i].localY = node->localY;
        records[i].localZ = node->localZ;
        records[i].sourceNodeIndex = node->sourceNodeIndex;
        records[i].nodeIndex = node->nodeIndex;
        records[i].sourceId = node->sourceId;
        next = node->next;
        heapFree(node);
        node = next;
    }
    actorAppendCallback(otherActor, self, 0x8000, 0, gCollisionHitCount, records);
}

void collisionNodeLocalToWorldXZ(Actor *owner, CollisionHitRecord *record, f32 *outWorldX, f32 *outWorldZ) {
    s32 i;
    ModelNode *node;
    Mtx *mtx;
    float modelMtx[4][4];
    u32 mtxIndex;
    f32 worldX;
    f32 worldY;
    f32 worldZ;

    node = owner->collision->nodes;
    for (i = record->nodeIndex - 1; i != 0; i--) {
        node = node->next;
    }
    mtx = owner->collision->nodeMtx[gGfxBufferIndex ^ 1];
    mtxIndex = node->mtxOffset;
    if (mtxIndex == -1) {
        memcpy(modelMtx, owner->collision->modelMtxF, sizeof(modelMtx));
        guMtxXFMF(modelMtx, record->localX, record->localY, record->localZ, &worldX, &worldY, &worldZ);
    } else {
        guMtxXFML(&mtx[mtxIndex >> 6], record->localX, record->localY, record->localZ, &worldX, &worldY, &worldZ);
    }
    *outWorldX = worldX;
    *outWorldZ = worldZ;
}

void func_806742C0(s16, s16, s16 *, s16 *);

void collisionComputeArcYawBounds(s32 x1, s32 y1, s32 x2, s32 y2, s16 *outMinAngle, s16 *outMaxAngle) {
    s32 pad1;
    s32 pad2;
    f32 dist;
    s16 angle;
    s32 dx;
    s32 dy;
    s32 absDelta;

    dx = x2 - x1;
    if (dx > 0) {
        absDelta = dx;
    } else {
        absDelta = -dx;
    }
    if (absDelta < 0x2711) {
        dy = y2 - y1;
        if (dy > 0) {
            absDelta = dy;
        } else {
            absDelta = -dy;
        }
        if (absDelta < 0x2711) {
            dist = sqrtf(dx * dx + dy * dy);
            if (dist != 0.0) {
                if (dx >= 0 && dy >= 0) {
                    angle = mathAsinFixed(dx * 65535.9 / dist) >> 4;
                }
                if (dx >= 0 && dy < 0) {
                    angle = (mathAsinFixed((y1 - y2) * 65535.9 / dist) >> 4) + 0x400;
                }
                if (dx < 0 && dy < 0) {
                    angle = (mathAsinFixed((x1 - x2) * 65535.9 / dist) >> 4) + 0x800;
                }
                if (dx < 0 && dy >= 0) {
                    angle = (mathAsinFixed(dy * 65535.9 / dist) >> 4) + 0xC00;
                }
                func_806742C0(angle + 0x400, angle - 0x400, outMinAngle, outMaxAngle);
            }
        }
    }
}
